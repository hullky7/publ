from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

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
    portfolio_symbols = db.execute("SELECT symbol FROM portfolio WHERE id=:id GROUP BY symbol", id=session["user_id"])
    # повний актив - сума акцій і кешу
    total_full = 0
    for symb in portfolio_symbols:
        stock_shares = db.execute("SELECT shares FROM portfolio WHERE id=:id AND symbol =:symbol",
                                  id=session["user_id"], symbol=symb["symbol"])
        symbol = symb["symbol"]
        shares = stock_shares[0]["shares"]
        stack = lookup(symbol)
        price_now = stack["price"]
        total = shares * price_now
        db.execute("UPDATE portfolio SET total=:total, price=:price WHERE id=:id AND symbol=:symbol",
                   symbol=symbol, total=total, price=price_now, id=session["user_id"])
        total_full += total

    cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
    total_full += cash[0]["cash"]
    portfolio_upd = db.execute("SELECT * FROM portfolio WHERE id=:id", id=session["user_id"])
    for i in range(len(portfolio_upd)):
        portfolio_upd[i]["price"] = usd(portfolio_upd[i]["price"])
        portfolio_upd[i]["total"] = usd(portfolio_upd[i]["total"])
    stocks1 = portfolio_upd
    return render_template("index.html", stocks=stocks1, cash=usd(cash[0]["cash"]), total=usd(total_full))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # умова введення символа акцій
        if not request.form.get("symbol"):
            return apology("Must provide stock’s symbol", 400)
        # умова введення кількості акцій
        try:
            share = int(request.form.get("shares"))
        except:
            return apology("Must input a integer number of shares", 400)
        if not share:
            return apology("Must input a number of shares", 400)
        if share <= 0:
            return apology("Must input a integer number of shares", 400)
        stack = lookup(request.form.get("symbol"))
        # правильність введення назви акцій
        if not stack:
            return apology("Invalid or symbol does not exist", 400)
        # ціна n-ої кількості акцій
        share_price = share * stack["price"]
        # гроші на рахунку
        money = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        cash = money[0]["cash"]
        cash_upd = cash - share_price
        # оновлення рахунку
        db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=cash_upd, id=session["user_id"])
        # оновлення портфоліо
        shares = db.execute("SELECT shares FROM portfolio WHERE id=:id AND symbol=:symbol",
                            symbol=stack["symbol"], id=session["user_id"])
        if not shares:
            db.execute("INSERT INTO portfolio (symbol, name, shares, price, total, id) VALUES (:symbol, :name, :shares, :price, :total, :id)",
                       symbol=stack["symbol"], name=stack["name"], shares=share, price=stack["price"], total=share_price, id=session["user_id"])
        else:
            shares_upd = int(shares[0]["shares"] + share)

            db.execute("UPDATE portfolio SET shares=:shares WHERE id=:id AND symbol=:symbol",
                       symbol=stack["symbol"], shares=shares_upd, id=session["user_id"])
        # оновлення історії
        db.execute("INSERT INTO history (symbol, shares, price, id) VALUES (:symbol, :shares, :price, :id)",
                   symbol=stack["symbol"], shares=share, price=stack["price"], id=session["user_id"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM history WHERE id=:id", id=session["user_id"])
    for stock in stocks:
        stock["price"] = usd(stock["price"])
    return render_template("history.html", stocks=stocks)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation password was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password must be the same as confirmation password", 400)

        resultat = db.execute("INSERT INTO users(username, hash) VALUES (:username, :password)",
                              username=request.form.get("username"), password=generate_password_hash(request.form.get("password")))
        if not resultat:
            return apology("Username already exist", 400)

        # remember which user has logged in
        session["user_id"] = resultat
        return redirect("/login")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


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
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

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
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide stock’s symbol", 400)
        row = lookup(request.form.get("symbol"))
        if not row:
            return apology("Invalid symbol", 400)
        row["price"] = usd(row["price"])
        return render_template("quoted.html", stack=row)
    else:
        return render_template("quote.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # умова введення символа акцій
        if not request.form.get("symbol"):
            return apology("Must provide stock’s symbol", 400)
        # умова введення кількості акцій
        try:
            share = int(request.form.get("shares"))
        except:
            return apology("Must input a integer number of shares", 400)
        if not share:
            return apology("Must input a number of shares", 400)
        if share <= 0:
            return apology("Must input a integer number of shares", 400)
        stack = lookup(request.form.get("symbol"))
        symbol = stack["symbol"]
        # оновлення портфоліо
        shares = db.execute("SELECT shares FROM portfolio WHERE id=:id AND symbol=:symbol", symbol=symbol, id=session["user_id"])
        if not shares:
            return apology("You have no shares like this", 400)
        elif share > shares[0]["shares"]:
            return apology("You have no such shares like this", 400)
        else:
            # ціна n-ої кількості акцій
            share_price = share * stack["price"]
            # гроші на рахунку
            money = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
            cash = money[0]["cash"]
            cash_upd = cash + share_price
            # оновлення рахунку
            db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=cash_upd, id=session["user_id"])
            shares_upd = int(shares[0]["shares"] - share)
            db.execute("UPDATE portfolio SET shares=:shares WHERE id=:id AND symbol=:symbol",
                       symbol=stack["symbol"], shares=shares_upd, id=session["user_id"])

            # оновлення історії
            db.execute("INSERT INTO history (symbol, shares, price, id) VALUES (:symbol, :shares, :price, :id)",
                       symbol=stack["symbol"], shares=-share, price=-stack["price"], id=session["user_id"])
        return redirect("/")
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)