import numpy.random as random
def generate_random_str(randomlength=16):
    """
    生成一个指定长度的随机字符串
    """
    random_str = ''
    base_str = 'ABCDEFGHIGKLMNOPQRSTUVWXYZ'
    length = len(base_str) - 1
    for i in range(randomlength):
        random_str += base_str[random.randint(0, length)]
    return random_str

outputA = open("./PB16111485-project2/ex2/input/inputA.txt",'w')
outputB = open("./PB16111485-project2/ex2/input/inputB.txt",'w')
outputstring = generate_random_str(15)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(10)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(15)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(20)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(15)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(30)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(15)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(40)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(15)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(50)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(15)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(60)
outputA.write(outputstring + "\n")
outputstring = generate_random_str(15)
outputB.write(outputstring + "\n")
outputstring = generate_random_str(25)
outputB.write(outputstring + "\n")
outputstring = generate_random_str(30)
outputB.write(outputstring + "\n")
outputstring = generate_random_str(25)
outputB.write(outputstring + "\n")
outputstring = generate_random_str(45)
outputB.write(outputstring + "\n")
outputstring = generate_random_str(25)
outputB.write(outputstring + "\n")
outputstring = generate_random_str(60)
outputB.write(outputstring + "\n")
outputstring = generate_random_str(25)
outputB.write(outputstring + "\n")
outputstring = generate_random_str(75)
outputB.write(outputstring + "\n")
outputstring = generate_random_str(25)
outputB.write(outputstring + "\n")
outputstring = generate_random_str(90)
outputB.write(outputstring + "\n")
outputstring = generate_random_str(25)
outputB.write(outputstring + "\n")
outputA.close()
outputB.close()
