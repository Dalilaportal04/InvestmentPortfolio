import random
import string
import json
from datetime import datetime
from itertools import product
from tqdm import tqdm  # Import tqdm for the progress bar

def generate_all_tickers():
    # Create a list of all ticker combinations
    tickers = []
    for length in range(1, 5):  # Ticker length from 1 to 5; ex. A - ZZZZZ
        tickers.extend([''.join(ticker) for ticker in product(string.ascii_uppercase, repeat=length)])

    # Shuffle the list to scramble the order
    random.shuffle(tickers)

    return tickers

def generate_random_price():
    # Generate a skewed random price (most prices are lower, highly skewed to the right)
    mu = 5  # mean of the underlying normal distribution
    sigma = 1.5  # standard deviation of the underlying normal distribution
    price = random.lognormvariate(mu, sigma)  # Log-normal distribution for skewed data
    return min(price, 686000)  # Cap at 686,000

def generate_random_stocks(tickers):
    stocks = []
    today_date = datetime.now().date()

    # Use tqdm to add a progress bar
    for ticker in tqdm(tickers, desc="Generating stocks", unit="ticker"):
        last_price = generate_random_price()

        stock_data = {
            "ticker": ticker,
            "last_price": last_price,
            "date": str(today_date)
        }

        stocks.append(stock_data)

    return stocks

def save_stocks_to_file(stocks, output_file):
    with open(output_file, 'w') as f:
        json.dump(stocks, f, indent=4)

# Generate all tickers (A to ZZZZZ) and shuffle them
tickers = generate_all_tickers()

# Generate the stocks with prices
stocks = generate_random_stocks(tickers)

# Save to a JSON file
save_stocks_to_file(stocks, "../Data/all_stocks.json")

print(f"Generated {len(tickers)} random stocks and saved to 'all_stocks.json'.")
