import numpy as np 
import pandas as pd
import requests
import xlsxwriter
import math
from secrets import IEX_CLOUD_API_TOKEN

stocks = pd.read_csv('sp_500_stocks.csv')
#print(stocks)

symbol = 'AAPL'
api_uri = f'https://sandbox.iexapis.com/stable/stock/{symbol}/quote?token={IEX_CLOUD_API_TOKEN}'
data = requests.get(api_uri).json()
print(data)
print(data['latestPrice'])
print(data['marketCap'])

my_columns = ['Ticker', 'Price', 'Market Capitalization', 'Number of Shares to Buy']
final_dataframe = pd.DataFrame(columns = my_columns)
# print(final_dataframe)
# final_dataframe = final_dataframe.append(pd.Series(['AAPL', data['latestPrice'],
# data['marketCap'], 'N/A'], index = my_columns), ignore_index = True)

# print(final_dataframe)

# for symbol in stocks['Ticker']:
#     api_uri = f'https://sandbox.iexapis.com/stable/stock/{symbol}/quote?token={IEX_CLOUD_API_TOKEN}'
#     data = requests.get(api_uri).json()
#     final_dataframe = final_dataframe.append(pd.Series([symbol, data['latestPrice'],
#         data['marketCap'], 'N/A'], index = my_columns), ignore_index = True)

def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(lst), n):
        yield lst[i:i+n]

symbol_groups = list(chunks(stocks['Ticker'], 100))
# print(len(symbol_groups))

symbol_strings = []
for i in range(0, len(symbol_groups)):
    symbol_strings.append(','.join(symbol_groups[i]))

#print(symbol_strings)

for symbol_string in symbol_strings:
    batch_api_call_url = f'https://sandbox.iexapis.com/stable/stock/market/batch/?types=quote&symbols={symbol_string}&token={IEX_CLOUD_API_TOKEN}'
    data = requests.get(batch_api_call_url).json()
    for symbol in symbol_string.split(','):
        final_dataframe = final_dataframe.append(
                                        pd.Series([symbol, 
                                                   data[symbol]['quote']['latestPrice'], 
                                                   data[symbol]['quote']['marketCap'], 
                                                   'N/A'], 
                                                  index = my_columns), 
                                        ignore_index = True)

portfolio_size = input("Enter the value of your portfolio:")

try:
    val = float(portfolio_size)
except ValueError:
    print("That's not a number! \n Try again:")
    portfolio_size = input("Enter the value of your portfolio:")


position_size = float(portfolio_size) / len(final_dataframe.index)
for i in range(0, len(final_dataframe['Ticker'])-1):
    final_dataframe.loc[i,'Number Of Shares to Buy'] = math.floor(position_size / final_dataframe['Price'][i])

print(final_dataframe)