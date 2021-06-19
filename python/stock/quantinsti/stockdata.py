import pandas as pd

#to fetch financial data
import yfinance as yf

# for visualization
import matplotlib.pyplot as plt
plt.style.use('seaborn-darkgrid')

price_data_apple = yf.download("AAPL", start="2019-01-02", end="2019-03-05", auto_adjust=True)
#set the index to a datetime object 
#price_data_apple.index = pd.to_datetime(price_data_apple.index)

#Display the first 5 rows
#print(price_data_apple)
#print(price_data_apple.tail(5))

#plot the close price
plt.figure(figsize=(10,7))
price_data_apple['Close'].plot()
# Set the title and axes label
plt.title('Apple Price Data', fontsize=14)
plt.xlabel('Year-Month', fontsize=12)
plt.ylabel('Price', fontsize=12)
# Show the plot
plt.show()



