import tushare as ts 

ts.set_token('d318444bd2e7ae19e7174a9e9dab092e8a3097c883f3821405a2f932')

pro = ts.pro_api()

# df = pro.query('trade_cal',exchange="", start_date='20190101', fields='exchange, cal_date, is_open, pretrade_date',end_date='20200525', is_open='0')

# print(df)


df = pro.daily(ts_code='000001.SZ', start_date='20180701',end_date='20200525')

print(df)