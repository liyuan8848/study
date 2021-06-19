#####
# pypi.org/project/yfinance
#####

import yfinance as yf
msft = yf.Ticker("msft")

# get stock info
print(msft.info)

#get historical market data
hist = msft.history(period="max")

# print(hist)

#show actions (difidends, splits)
# print(msft.actions)

#show dividents
# print(msft.dividends)

#show splits
# print(msft.splits)

#show financials
# print(msft.financials)
# print(msft.quarterly_financials)

# show major holders
# print(msft.major_holders)

# show institutional holders
# print(msft.institutional_holders)

# show balance sheet
# print(msft.balance_sheet)
# print(msft.quarterly_balance_sheet)

# show cashflow
# print(msft.cashflow)
# print(msft.quarterly_cashflow)

# show earnings
# msft.earnings
# msft.quarterly_earnings

#show sustainability
# msft.sustainability

#show analysts recommendations
# msft.recommendations

#show next event (earnings, etc)
# msft.calendar

#show ISIN code 
#ISIN = International Securities Identification Number
# print(msft.isin)

#show options expirations
# print(msft.options)

# get option chain for specific expiration 
#opt = msft.option_chain('YYY-MM-DD')
#data available via : opt.calls, opt.puts

#####
#  to initialize multiple Ticker objects, use
#####


# import yfinance as yf

# tickers = yf.Tickers('msft aapl goog')
# # ^ returns a named tuple of Ticker objects

# # access each ticker using (example)
# tickers.msft.info
# tickers.aapl.history(period="1mo")
# tickers.goog.actions



######
# fetching data for multiple tickers
######

# 

data = yf.download(  # or pdr.get_data_yahoo(...
        # tickers list or string as well
        tickers = "SPY AAPL MSFT",

        # use "period" instead of start/end
        # valid periods: 1d,5d,1mo,3mo,6mo,1y,2y,5y,10y,ytd,max
        # (optional, default is '1mo')
        period = "ytd",

        # fetch data by interval (including intraday if period < 60 days)
        # valid intervals: 1m,2m,5m,15m,30m,60m,90m,1h,1d,5d,1wk,1mo,3mo
        # (optional, default is '1d')
        interval = "1d",

        # group by ticker (to access via data['SPY'])
        # (optional, default is 'column')
        group_by = 'ticker',

        # adjust all OHLC automatically
        # (optional, default is False)
        auto_adjust = True,

        # download pre/post regular market hours data
        # (optional, default is False)
        prepost = True,

        # use threads for mass downloading? (True/False/Integer)
        # (optional, default is True)
        threads = True,

        # proxy URL scheme use use when downloading?
        # (optional, default is None)
        proxy = None
    )

#####
# pandas_datareader override

# If your code uses pandas_datareader and you want to download data faster, you can “hijack” pandas_datareader.data.get_data_yahoo() method to use yfinance while making sure the returned data is in the same format as pandas_datareader’s get_data_yahoo().

#####

import yfinance as yf
yf.pdr_override() # <== that's all it takes :-)

# download dataframe
data = yf.download("SPY", start="2017-01-01", end="2017-04-30")
print(data)

