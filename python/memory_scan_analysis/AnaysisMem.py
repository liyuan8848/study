
import re
import matplotlib.pyplot as plt
result = []
with open("output.txt", "r") as f:
    count = 0
    for line in f:
        if "python /usr/bin/rackmanager/RackManager.py redfish" in line:
            count+=1
            if count == 1:
                print(line, end="")
                tempContent =line.strip()
                re.sub(' +',' ', tempContent)
                print(tempContent)
                newContent = tempContent.split()
                result.append(int(newContent[4][:3]))
            elif count == 3:
                count = 0 
            
print(result)
plt.plot(result,'go')
plt.ylabel("Redfish Memory Usage(m)")
plt.title("Redfish Memory Testing Result")
plt.show()




