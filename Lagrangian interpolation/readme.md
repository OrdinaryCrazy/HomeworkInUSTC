

# 计算方法——作业2

***

### 文件说明：

* `lagrange.m`: lagrange插值实现函数

* `test.m`: 测试文件，从这里开始执行

* `test_function.m`: 插值对象函数，这里是 

$$
f(x) = \frac{1}{1 + x ^ 2}
$$

### 测试结果：

```shell
>> test
For n = 5:
	For xi = -5 + 10 * (i / 5)							maxdiff = 0.71151
	For xi = -5 * cos((2 * i + 1) * pi / (2 * 5 + 2))	maxdiff = 0.7895
For n = 10:
	For xi = -5 + 10 * (i / 10)							maxdiff = 2.0237
	For xi = -5 * cos((2 * i + 1) * pi / (2 * 10 + 2))	maxdiff = 0.72194
For n = 20:
	For xi = -5 + 10 * (i / 20)							maxdiff = 60.9911
	For xi = -5 * cos((2 * i + 1) * pi / (2 * 20 + 2))	maxdiff = 0.45153
For n = 40:
	For xi = -5 + 10 * (i / 40)							maxdiff = 104710.3886
	For xi = -5 * cos((2 * i + 1) * pi / (2 * 40 + 2))	maxdiff = 0.24051
```

###  结果分析：

1. 龙格现象影响，导致误差较大，对于第一个函数，由于插值点均匀，在两侧导数大，函数值变化大的部分出现了较大的偏差。
2. 对于第二个函数，因为插值点两边密中间疏，两侧误差小中间误差大。

##### 具体如图：
###### xi = -5 + 10 * (i / 20)	
![](/home/crazy/5-NumericalAnalyse/HW2/A-1.jpg)

![](/home/crazy/5-NumericalAnalyse/HW2/A-2.jpg)

![](/home/crazy/5-NumericalAnalyse/HW2/A-3.jpg)

![](/home/crazy/5-NumericalAnalyse/HW2/A-4.jpg)


###### xi = -5 * cos((2 * i + 1) * pi / (2 * 40 + 2))
![](/home/crazy/5-NumericalAnalyse/HW2/B-1.jpg)

![](/home/crazy/5-NumericalAnalyse/HW2/B-2.jpg)

![](/home/crazy/5-NumericalAnalyse/HW2/B-3.jpg)

![](/home/crazy/5-NumericalAnalyse/HW2/B-4.jpg)

<p align='right'>张劲暾 PB16111485</p>

<p align='right'>2018.9.25</p>

