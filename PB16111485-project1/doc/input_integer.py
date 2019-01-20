import numpy as np
output = open("./PB16111485-project1/ex1/input/input_integer.txt",'w')
input_integer = np.random.randint(0,65536,size=(pow(2,17),1))
for integer in input_integer:
    output.write(str(integer[0]) + "\n")
output.close()