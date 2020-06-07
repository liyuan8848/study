import re

inputfile = open('new4.txt')
print(inputfile)
rm_emmc = {}
emmc_data = inputfile.split('\n')
print(emmc_data)
n = len(emmc_data)
print(n)
for i in range(0,n):
    line = emmc_data[i].rstrip()
    print(line)
    if re.search('eMMC Life Time Estimation A', line):
        sdata = line.split(':')
        slc_val = int(sdata[1],base = 16)
        if ( slc_val in [1,2,3,4,5,6,7,8,9,10] ):
            rm_emmc["eMMC Reading"] = "{0}%-{1}% SLC device life time used \n".format((slc_val-1)*10, slc_val*10)
        elif (slc_val == 11):
            rm_emmc["eMMC Reading"] = "Exceed its maximum estimated SLC device life time \n"
        else:
            rm_emmc["eMMC Reading"] = "emmc SLC has Reserved value \n"
    elif re.search('eMMC Life Time Estimation B', line):
        sdata = line.split(':')
        mlc_val = int(sdata[1], base = 16)
        if ( mlc_val in [1,2,3,4,5,6,7,8,9,10] ):
            rm_emmc["eMMC Reading"] += "{0}%-{1}% MLC device life time used \n".format((mlc_val-1)*10, mlc_val*10)
        elif (mlc_val == 11):
            rm_emmc["eMMC Reading"] += "Exceed its maximum estimated MLC device life time \n"
        else:
            rm_emmc["eMMC Reading"] += "eMMC MLC has Reserved value \n"
    elif re.search('eMMC Pre EOL information', line):
        sdata = line.split(':')
        pre_eol_val = int(sdata[1],base = 16)
        if (pre_eol_val == 0):
            rm_emmc["eMMC Reading"] += "eMMC Pre EOL is Not Defined \n"
        elif(pre_eol_val == 1):
            rm_emmc["eMMC Reading"] += "eMMC Pre EOL is Normal \n"
        elif(pre_eol_val == 2):
            rm_emmc["eMMC Reading"] += "eMMC Pre EOL is Warning \n"
        elif(pre_eol_val == 3):
            rm_emmc["eMMC Reading"] += "eMMC Pre EOL is Urgent \n"
        else:
            rm_emmc["eMMC Reading"] += "eMMC Pre EOL is Reserved \n"
    else:
        pass                   

print(rm_emmc)
print(rm_emmc["eMMC Reading"])



# for line in inputfile:
#     line = line.rstrip()
    # if(re.search('eMMC Life Time Estimation A', line)):
    #     sdata = line.split(':')
    #     slc_val = sdata[1]
    #     print(slc_val)
    # elif re.search('eMMC Life Time Estimation B', line):
    #     sdata = line.split(':')
    #     mlc_val = sdata[1]
    #     print(mlc_val)
    # elif re.search('eMMC Pre EOL information', line):
    #     sdata = line.split(':')
    #     pre_eol_val = sdata[1]
    #     print(pre_eol_val)
    # else:
    #     pass
    # if re.search('eMMC Life Time Estimation A', line):
    #     sdata = line.split(':')
    #     slc_val = int(sdata[1], base = 16)
    #     if (slc_val in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]):
    #         rm_emmc["eMMC SLC Reading"] = "{0}%-{1}% SLC device life time used".format((slc_val-1)*10, slc_val*10)
    #     elif (slc_val == 11):
    #         rm_emmc["eMMC SLC Reading"] = "Exceed its maximum estimated SLC device life time"
    #     else:
    #         rm_emmc["eMMC SLC Reading"] = "Reserved value"
    # elif re.search('eMMC Life Time Estimation B', line):
    #     sdata = line.split(':')
    #     mlc_val = int(sdata[1], base = 16)
    #     if ( mlc_val in [1,2,3,4,5,6,7,8,9,10] ):
    #         rm_emmc["eMMC MLC Reading"] = "{0}%-{1}% MLC device life time used".format((mlc_val-1)*10, mlc_val*10)
    #     elif (mlc_val == 11):
    #         rm_emmc["eMMC MLC Reading"] = "Exceed its maximum estimated MLC device life time"
    #     else:
    #         rm_emmc["eMMC SLC Reading"] = "Reserved value"
    # elif re.search('eMMC Pre EOL information', line):
    #     sdata = line.split(':')
    #     pre_eol_val = int(sdata[1],base = 16)
    #     if (pre_eol_val == 0):
    #         rm_emmc["eMMC Pre EOL Info Reading"] = "eMMC Pre EOL is Not Defined"
    #     elif(pre_eol_val == 1):
    #         rm_emmc["eMMC Pre EOL Info Reading"] = "eMMC Pre EOL is Normal"
    #     elif(pre_eol_val == 2):
    #         rm_emmc["eMMC Pre EOL Info Reading"] = "eMMC Pre EOL is Warning"
    #     elif(pre_eol_val == 3):
    #         rm_emmc["eMMC Pre EOL Info Reading"] = "eMMC Pre EOL is Urgent"
    #     else:
    #         rm_emmc["eMMC Pre EOL Info Reading"] = "eMMC Pre EOL is Reserved"
    # else:
    #     pass

# print(rm_emmc)
