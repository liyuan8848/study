# Description : this program uses dual moving average crossover to determine when to buy and sell stock

import pandas as pd 
import numpy as np 
from datetime import datetime 
import matplotlib.pyplot as plt
import yfinance as yf

plt.style.use('fivethirtyeight')

#msft = yf.Ticker("msft")
start_date = "2006-10-02"
end_date = "2011-12-30"
aapl = yf.Ticker("aapl")
# aapl_hist = aapl.history(period="max")
aapl_hist = aapl.history(start = start_date, end = end_date)


#visualize the data
# plt.figure(figsize=(12.5, 4.5))
# plt.plot(aapl_hist["Close"], label = 'AAPL')
# plt.title('AAPL Adj. Close Price History')
# plt.xlabel("Start_date to End_date")
# plt.ylabel('Adj. Close Price USD ($)')
# plt.legend(loc='upper left')
# plt.show()



#Create teh simple moving average with a 30 days window
SMA30 = pd.DataFrame()
SMA30['Adj Close Price'] = aapl_hist['Close'].rolling(window = 30).mean()

#Create teh simple moving average with a 100 days window
SMA100 = pd.DataFrame()
SMA100['Adj Close Price'] = aapl_hist['Close'].rolling(window = 100).mean()



# plt.figure(figsize=(12.5, 4.5))
# plt.plot(aapl_hist["Close"], label = 'AAPL')
# plt.plot(SMA30['Adj Close Price'], label = 'SMA30')
# plt.plot(SMA100['Adj Close Price'], label = 'SMA100')
# plt.title('AAPL Adj. Close Price History')
# plt.xlabel("Start_date to End_date")
# plt.ylabel('Adj. Close Price USD ($)')
# plt.legend(loc='upper left')
# plt.show()

# Create a new data frame to store all the data
data = pd.DataFrame()
data['AAPL'] = aapl_hist['Close']
data['SMA30'] = SMA30['Adj Close Price']
data['SMA100'] = SMA100['Adj Close Price']


# Create a function to signal when to buy and sell the asset/stock
def buy_sell(data):
    sigPriceBuy= []
    sigPriceSell= []
    flag = -1

    for i in range(len(data)):
        if data['SMA30'][i] > data['SMA100'][i]:
            if flag != 1:
                sigPriceBuy.append((data['AAPL'][i]))
                sigPriceSell.append(np.nan)
                flag = 1
            else:
                sigPriceBuy.append(np.nan)
                sigPriceSell.append(np.nan)
        elif data['SMA30'][i] < data['SMA100'][i]:
            if flag != 0:
                sigPriceBuy.append(np.nan)
                sigPriceSell.append((data['AAPL'][i]))
                flag = 0
            else:
                sigPriceBuy.append(np.nan)
                sigPriceSell.append(np.nan)
        else:
            sigPriceBuy.append(np.nan)
            sigPriceSell.append(np.nan)

    return (sigPriceBuy, sigPriceSell)



# Store the buy and sell data into a variable
buy_sell = buy_sell(data)

data['Buy_Signal_Price'] = buy_sell[0]
data['Sell_Signal_Price'] = buy_sell[1]

#show the data

# print(data)


#Visualize the data and the strategy to buy and sell the stock
plt.figure(figsize=(12.6, 4.6))
plt.plot(data["AAPL"], label = "AAPL", alpha = 0.35 )
plt.plot(data["SMA30"], label = "SMA30", alpha = 0.35)
plt.plot(data["SMA100"], label = "SMA100", alpha = 0.35)
plt.scatter(data.index, data['Buy_Signal_Price'], label = "Buy", marker = "^", color = 'green')
plt.scatter(data.index, data['Sell_Signal_Price'], label = "Sell", marker = "v", color = 'red')

plt.title('Apple Adj. Close Price History Buy & Sell Signals')
plt.xlabel("Start_date to End_date")
plt.ylabel('Adj. Close Price USD ($)')
plt.legend(loc='upper left')
plt.show()





# print(SMA100['Adj Close Price'])

# print(aapl_hist["Close"])





