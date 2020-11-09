soc_output = {'status_code': 0, 'stderr': '', 'stdout': ' 0f 10 a7 01 0a 0b c2 7e 14 14 00 e6 28 16 a8 fd\n 52 e7 9b ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff\n'}
soc_output_new = soc_output['stdout'].replace("\n","").split(' ')
inx_s= soc_output_new.index("e6")+1
test_index = soc_output_new.index("e9")
print(test_index)

array = soc_output_new[inx_s:inx_s+6]
s = ':'
result = s.join(array)
print(array)
print(result)