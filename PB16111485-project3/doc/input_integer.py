import numpy as np
output = open("./PB16111485-project3/inputA/input_integer.txt",'w')
input_integer = []
while len(input_integer) < 100 :
    tmp = np.random.randint(0,65535)
    if tmp not in input_integer:
        input_integer.extend([tmp])
for integer in input_integer :
    output.write(str(integer) + "\n")

output.close()


