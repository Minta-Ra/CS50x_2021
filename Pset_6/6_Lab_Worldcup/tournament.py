# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

#######################################################

    teams = []
    # TODO: Read teams into memory from file
    # filename - name from the command line argument
    filename = sys.argv[1]

    # Open the file
    with open(filename) as file:
        # Read the file as CSV file; one row at a time
        reader = csv.DictReader(file)

        # Loop over all of the data in reader
        for team in reader:
            # Convert rating string to int
            # Using [ ] we accessing the value for the particular key inside of the dictionary
            team["rating"] = int(team["rating"])
            # Add team to the list of teams in line 19. Append takes the value and adds it to the end of the list
            teams.append(team)

#######################################################

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # Keep track how many times team won a tournament
    # Loop over N times
    for i in range(N):
        # Simulate tournament with teams and save the result in winner
        winner = simulate_tournament(teams)
        # If the wimmer is already in my dictionary of counts
        if winner in counts:
            # Increase their number of wins by 1
            counts[winner] += 1
        else:
            # If they never wom before, this is the first win for them, assign their counts to 1
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")

#######################################################


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners

#######################################################


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # As long as there is more than 1 team, keep simulating
    while len(teams) > 1:
        # Set the new value to teams and keep simulationg rounds running the function above
        teams = simulate_round(teams)
    # Once one team left - the only one element in the list of teams - teams[0]
    # Access the name of the teams[0] in the dictionary - ["team"]
    # Return the name of the winning team
    return teams[0]["team"]

#######################################################


if __name__ == "__main__":
    main()