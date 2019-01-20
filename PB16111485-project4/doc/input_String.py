import numpy as np
import numpy.random as random

def generate_random_str(randomlength=16):
    """
    生成一个指定长度的随机字符串
    """
    random_str = ''
    base_str = 'ABCDEF'
    length = len(base_str) - 1
    for i in range(randomlength):
        random_str += base_str[random.randint(0, length)]
    return random_str

output = open("./PB16111485-project4/input/input_string.txt",'w')
text = generate_random_str(pow(2,5))
pattern = generate_random_str(2)
output.write(text + ',' + pattern + ';')
text = generate_random_str(pow(2,8))
pattern = generate_random_str(3)
output.write(text + ',' + pattern + ';')
text = generate_random_str(pow(2,11))
pattern = generate_random_str(4)
output.write(text + ',' + pattern + ';')
text = generate_random_str(pow(2,14))
pattern = generate_random_str(5)
output.write(text + ',' + pattern + ';')
text = generate_random_str(pow(2,17))
pattern = generate_random_str(6)
output.write(text + ',' + pattern + ';')

output.close()


