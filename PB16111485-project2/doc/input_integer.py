import numpy as np
output = open("./PB16111485-project2/ex1/input/input.txt",'w')
input_integer = np.random.randint(5,200,size=(31,1))
for integer in input_integer:
    output.write(str(integer[0]) + "\n")
output.close()