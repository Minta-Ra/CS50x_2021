import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

###################


##########################################################################
@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Display the result by quering the data from database

    # Look at the value - session[user_id]
    wallet = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    stocksFromDb = db.execute("SELECT symbol, shares, price, action FROM stocks WHERE userId = ?", session["user_id"])

    stocks = []

    # Deducting personal shares after we sold
    for stockEntry in stocksFromDb:
        alreadyInside = False
        stock = {"symbol": stockEntry["symbol"], "shares": 0, "action": "buy"}
        for x in stocks:
            if x["symbol"] == stockEntry["symbol"]:
                alreadyInside = True
        if alreadyInside == False:
            for x in stocksFromDb:
                if x["symbol"] == stockEntry["symbol"]:
                    stock["shares"] += x["shares"]
            stocks.append(stock)

    # print("    ")
    # print(stocks)
    # print("    ")

    sumTotal = 0

    for i in stocks:
        # Use lookup() to see current price
        quote = lookup(i["symbol"])
        i["name"] = quote["name"]
        i["price"] = quote["price"]
        # current price * number of shares
        i["total"] = i["price"] * i["shares"]
        sumTotal = sumTotal + i["total"]

    sumMoney = sumTotal + wallet[0]["cash"]

    # Display current stocks data of a current logged in user
    return render_template("index.html", stocks=stocks, wallet=wallet[0], sumMoney=sumMoney)

##########################################################################


##########################################################################
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        # Defining new variables
        symbol = request.form.get("symbol")
        price = lookup(symbol)
        shares = request.form.get("shares")
        wallet = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Error checking
        if not symbol:
            return apology("missing valid symbol", 400)
        if price is None:
            return apology("missing valid symbol", 400)

        # To buy shares - error checking
        try:
            shares = int(shares)
            if shares < 1:
                return apology("provide number of shares you want to buy", 400)
        except ValueError:
            return apology("provide number of shares you want to buy", 400)

        # Calculate total price of of specific shares hold by user
        sharePrice = shares * price["price"]

        # If user cannot afford it
        if sharePrice > wallet:
            return apology("you do not have enough money to buy more shares", 400)

        # Purchase stock as long as user can afford it
        else:
            newWallet = wallet - sharePrice
            db.execute("UPDATE users SET cash = ? WHERE id = ?", newWallet, session["user_id"])

            db.execute("INSERT INTO stocks (userId, symbol, name, shares, price, action, date) VALUES (?, ?, ?, ?, ?, ?, ?)",
                       session["user_id"], symbol.upper(), price["name"], shares, price["price"], "buy", datetime.utcnow())

        flash("You successfully bought new shares!")

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("buy.html")

##########################################################################


##########################################################################
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    stockHistory = db.execute("SELECT * FROM stocks WHERE userId = ?", session["user_id"])
    return render_template("history.html", stocks=stockHistory)

##########################################################################


###################
@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in;    rows[0]["id"] - rows[0] - is the first row; ["id"] - column in that particular row with value of the ID column for that row
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

###################


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

###################


##########################################################################
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # Allows user to lookup at a particular stock quote
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        # if lookup returns none - display error
        if quote is None:
            return apology("missing valid symbol", 400)
        else:
            return render_template("quoteStock.html", symbol=quote["symbol"], name=quote["name"], price=quote["price"])

    else:
        return render_template("quote.html")

##########################################################################


##########################################################################
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Defining variables
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if not username:
            return apology("must provide username", 400)
        # If user is already in the database
        elif len(rows) != 0:
            return apology("this username is already taken", 400)

        elif not password:
            return apology("must provide password", 400)

        elif not confirmation:
            return apology("must provide password confirmation", 400)

        elif not password == confirmation:
            return apology("your passwords do not match", 400)

        # Password with generated hash
        else:
            hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)

            # Add new user to database (into the user's table) / Register the user
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

            flash("You are registered!")
            # Redirect user to home page
            return redirect("/")

    else:
        # User reached route via GET (as by clicking a link or via redirect)
        return render_template("register.html")

##########################################################################


##########################################################################
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        # Defining new variables
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        price = lookup(symbol)
        wallet = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # print(symbol, shares, price, wallet)

        # Error checking
        if not symbol:
            return apology("missing symbol", 400)

        try:
            shares = int(shares)
            if shares < 1:
                return apology("You can sell 1 or more shares", 400)
        except ValueError:
            return apology("You can sell 1 or more shares", 400)

        # User's personal stocks - amount
        personalStocks = db.execute("SELECT shares FROM stocks WHERE userId = ? AND symbol = ?", session["user_id"], symbol)  # [0]

        # Error checking
        if shares > personalStocks[0]["shares"]:
            return apology("You do not have enough shares")

        # print("   ")
        # print(personalStocks, session["user_id"], symbol.upper(), shares, price, "sell")
        # print("   ")

        # How many shares user is selling
        db.execute("INSERT INTO stocks (userId, symbol, name, shares, price, action, date) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   session["user_id"], symbol.upper(), price["name"], - shares, price["price"], "sell", datetime.utcnow())

        # Updated wallet - balance
        updatedWallet = wallet + (price["price"] * shares)

        # print(" ")
        # print(updatedWallet, wallet)
        # print(" ")

        # Update user's cash balance
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updatedWallet, session["user_id"])

        flash("Sold!")

        # Redirect user to home page
        return redirect("/")

    else:
        stocks = db.execute("SELECT symbol FROM stocks WHERE userId = ? GROUP BY symbol", session["user_id"])

        return render_template("sell.html", stocks=stocks)

##########################################################################


###################
def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)