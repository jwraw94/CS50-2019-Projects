import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # TO DO
    # Select every symbol and quantity thereof owned by user. Group to show totals.
    portfolio = db.execute(
        "SELECT symbol, SUM(quantity) AS total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])
    current = {}
    total = 0

    # Get current info for each symbol owned by the user.
    for symbol in portfolio:
        current[symbol["symbol"]] = lookup(symbol["symbol"])
        total = (current[symbol["symbol"]]["price"] * symbol["total_shares"]) + total

    # Get current users remaining cash
    row = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
    balance = row[0]["cash"]

    return render_template("index.html", portfolio=portfolio, current=current, balance=balance, total_value=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # TO DO
    # CREATE TABLE 'transactions' ('id' integer PRIMARY KEY NOT NULL, 'user_id' integer NOT NULL, 'symbol' text NOT NULL, 'quantity' integer NOT NULL, 'transaction_cost' integer NOT NULL, 'time' timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP)

    if request.method == "POST":

        # Try and get an int for the amount of shares to buy
        try:
            quantity = int(request.form.get("shares"))
        except:
            return apology("Must be a whole number", 400)

        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        if quote == None:
            return apology("Symbol is invalid", 400)
        elif quantity <= 0:
            return apology("Number of shares must be greater than 0", 400)

        row = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        balance = row[0]["cash"]
        cost = quote["price"]
        transaction_cost = cost * quantity

        # Ensure the user can afford the transaction
        if balance < transaction_cost:
            return apology("You don't have enough money to complete this transaction", 400)

        db.execute("UPDATE users SET cash = cash - :transaction_cost WHERE id = :id",
                   transaction_cost=transaction_cost, id=session["user_id"])
        db.execute("INSERT into 'transactions' (user_id, symbol, quantity, transaction_cost) VALUES (:user_id, :symbol, :quantity, :transaction_cost)",
                   user_id=session["user_id"], symbol=symbol, quantity=quantity, transaction_cost=transaction_cost)

        return redirect("/")

    elif request.method == "GET":
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # TO DO
    history = db.execute(
        "SELECT symbol, quantity, transaction_cost, time FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])

    direction = "BUY"

    # Make it clear if a transaction was a buy or sell
    for record in history:
        if record["quantity"] > 0:
            record["direction"] = "BUY"
        else:
            record["direction"] = "SELL"

    return render_template("history.html", history=history, direction=direction)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User inputs a stock symbol in text field, redirects if valid to quoted page.

    if request.method == "POST":
        # for GET quote. Submit via POST.

        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        if quote == None:
            return apology("Symbol is invalid", 400)
        else:
            return render_template("quoted.html", quote=quote)

    elif request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # TODO
    # Require input of username in text field called username. Give apology if blank, invalid or name taken.

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username is valid
        if not request.form.get("username"):
            return apology("Username is invalid", 400)
        # Ensure password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Must provide password", 400)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords must match", 400)

        # Generate a hash for the users password
        password = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)
        user_entry = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                                username=request.form.get("username"), hash=password)

        # Test if user was able to be entered into DB. If not, username is taken.
        if not user_entry:
            return apology("Username is already taken", 400)

        # Remember which user has logged in
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        sell_quantity = int(request.form.get("shares"))
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        current_value = quote["price"]
        transaction_value = current_value * sell_quantity

        # Select every symbol and quantity thereof owned by user. Group to show totals.
        portfolio = db.execute("SELECT SUM(quantity) AS total_shares FROM transactions WHERE user_id = :user_id and symbol = :symbol GROUP BY symbol",
                               user_id=session["user_id"], symbol=symbol)
        quantity_owned = portfolio[0]["total_shares"]

        if symbol == None:
            return apology("Please enter a valid stock", 403)
        elif sell_quantity > quantity_owned or quantity_owned <= 0:
            return apology("You don't own enough of this stock.", 400)

        # Update the tables to contain info for the new transaction, and also to amend the amount of cash available.
        db.execute("UPDATE users SET cash = cash + :transaction_value WHERE id = :id",
                   transaction_value=transaction_value, id=session["user_id"])
        db.execute("INSERT INTO 'transactions' (user_id, symbol, quantity, transaction_cost) VALUES (:user_id, :symbol, :quantity, :transaction_cost)",
                   user_id=session["user_id"], symbol=symbol, quantity=-sell_quantity, transaction_cost=-transaction_value)
        return redirect("/")

    elif request.method == "GET":
        portfolio = db.execute(
            "SELECT symbol, SUM(quantity) AS total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])
        return render_template("sell.html", portfolio=portfolio)


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """Get stock quote."""
    # Extra requirement for 'personal touch'
    # Allow users to deposit or withdrawl money from their account.

    if request.method == "POST":
        # for GET quote. Submit via POST.

        amount = int(request.form.get("amount"))
        direction = request.form.get("direction")
        row = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        balance = row[0]["cash"]

        if direction == "deposit":
            db.execute("UPDATE users SET cash = cash + :amount WHERE id = :id",
                       amount=amount, id=session["user_id"])
        else:
            if balance < amount:
                return apology("You don't have enough money to withdraw this much.", 400)
            else:
                db.execute("UPDATE users SET cash = cash - :amount WHERE id = :id",
                           amount=amount, id=session["user_id"])

        return redirect("/")

    elif request.method == "GET":
        return render_template("deposit.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
