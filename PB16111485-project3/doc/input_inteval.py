import numpy as np
output = open("./PB16111485-project3/inputB/input_inteval.txt",'w')
interval_left = []
while len(interval_left) < 30 :
    tmp = np.random.randint(0,24)
    if tmp not in interval_left:
        interval_left.extend([tmp])

    tmp = np.random.randint(30,49)
    if tmp not in interval_left:
        interval_left.extend([tmp])

for left in interval_left :
    if(left < 25):
        right = np.random.randint(left + 1,25)
    else:
        right = np.random.randint(left + 1,50)
    output.write(str(left) + ',' + str(right) + "\n")

output.close()



