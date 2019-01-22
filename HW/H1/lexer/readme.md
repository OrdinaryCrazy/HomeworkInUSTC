# HW/H1/lexer 下文件说明与使用方法

## 文件说明：

* lexer.c: relop识别器源代码
* makefile：GNUmake脚本

## 使用方法：

1. `make`
2. `./lexer "string to be input"`

### 示例：

```shell
./lexer "<==>" "a<=b"
(relop,LE),start=1 end=2
(relop,EQ),start=2 end=3
(relop,GT),start=3 end=4
(relop,LE),start=2 end=3

```

