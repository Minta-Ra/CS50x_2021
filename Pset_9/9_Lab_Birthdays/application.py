import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        # ##############################################################################
        # Handle form submissions
        name = request.form.get("name")
        if not name:
            return ("Missing name")
        month = request.form.get("month")
        if not month:
            return("Missing month")
        day = request.form.get("day")
        if not day:
            return("Missing day")

        # Add new person (with name, month, day) into SQL database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
        # ##############################################################################

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        ##############################################################################
        dbEntry = db.execute("SELECT * FROM birthdays")
        # Generate output from a template
        return render_template("index.html", dbEntry=dbEntry)
        ##############################################################################