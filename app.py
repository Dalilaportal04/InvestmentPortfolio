from flask import Flask, request, jsonify
import subprocess
import json

app = Flask(__name__)

@app.route('/add_equity', methods=['POST'])
def add_equity():
    data = request.json
    stock_name = data.get('stockName')
    stock_price = data.get('stockPrice')

    if not stock_name or not stock_price:
        return jsonify({'error': 'Invalid input'}), 400

    # Write inputs to a file for processing by C++
    with open('equities.json', 'a') as file:
        json.dump({'stockName': stock_name, 'stockPrice': stock_price}, file)
        file.write('\n')

    # Trigger the C++ program
    try:
        subprocess.run(['g++', 'process_equity.cpp', '-o', 'process_equity'], check=True)
        subprocess.run(['./process_equity'], check=True)
    except subprocess.CalledProcessError as e:
        return jsonify({'error': 'Failed to execute C++ program'}), 500

    return jsonify({'message': 'Equity added successfully!'}), 200

if __name__ == '__main__':
    app.run(debug=True)
