import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Set secret_key
app.secret_key = os.urandom(24)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")



@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():

    if request.method == "POST":

        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Check if the birthday already exists in the database
        existing_birthday = db.execute("SELECT * FROM birthdays WHERE name = ? AND month = ? AND day = ?", name, month, day)

        if existing_birthday:
            # If the birthday already exists, show an error message
            flash("Error: That birthday already exists.")
        else:
            # If the birthday doesn't exist, add it to the database
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        #db = get_db()
        birthdays = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdays=birthdays)

