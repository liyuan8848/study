import plotly.graph_objs as go 
import pandas as pd 
import yfinance as yf

# get the stock data
start_date = "2015-10-02"
end_date = "2020-07-20"
stock = yf.Ticker("msft")


# aapl_hist = aapl.history(period="max")
stock_hist = stock.history(start = start_date, end = end_date)

#print(stock_hist)
# print(type(stock_hist))
# print(stock_hist.index)

# create an interactive candlestick chart

figure = go.Figure(
    data = [
        go.Candlestick(
            x = stock_hist.index,
            low = stock_hist['Low'],
            high = stock_hist['High'],
            close = stock_hist['Close'],
            open = stock_hist['Open'],
            increasing_line_color = 'red',
            decreasing_line_color = 'green'
        )
    ] 

)

#figure.update_layout(xaxis_rangeslider_visible = False)
figure.update_layout(
    title = "Microsoft Stock Price",
    yaxis_title = "MSFT Stock Price USD($)",
    xaxis_title = "Date"
)
figure.show()