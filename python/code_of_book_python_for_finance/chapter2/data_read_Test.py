import pandas_datareader.data as web
df=web.get_data_yahoo("msft", start="2017-08-13",end="2019-11-30")

# print(df)
df.tail()
