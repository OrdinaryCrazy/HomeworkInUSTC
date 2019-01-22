# HW/H1 问题回答：

## 问题2：

源文件位置：`/HW/H1/main.c`

### -S 参数下编译产生的汇编码：

```assembly
	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"Result is: %d"
	.text
	.globl	main
	.type	main, @function #头文件里printf函数汇编码
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp    #压栈
	movl	$5, -12(%rbp) #a = 5
	movl	-12(%rbp), %eax
	addl	$1, %eax   #b(eax) = a + 1
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	leal	2(%rax), %edx  #b + 2
	movl	-12(%rbp), %eax
	imull	%edx, %eax    #a * (b + 2)
	movl	%eax, -4(%rbp) #将结果保存在c
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi #传参
	movl	$0, %eax
	call	printf@PLT  #调用printf函数
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
```

### -m32 -S  参数下编译产生的汇编码：

```asm
	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"Result is: %d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx    
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	subl	$16, %esp            #压栈
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$5, -20(%ebp)       #a = 5
	movl	-20(%ebp), %edx
	addl	$1, %edx            #b = a + 1
	movl	%edx, -16(%ebp)
	movl	-16(%ebp), %edx
	leal	2(%edx), %ecx       #b + 2
	movl	-20(%ebp), %edx
	imull	%ecx, %edx          #a * (b + 2)
	movl	%edx, -12(%ebp)
	subl	$8, %esp
	pushl	-12(%ebp)           #传参
	leal	.LC0@GOTOFF(%eax), %edx
	pushl	%edx
	movl	%eax, %ebx
	call	printf@PLT         #调用函数
	addl	$16, %esp
	movl	$0, %eax
	leal	-8(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB1:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE1:
	.ident	"GCC: (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
```

## -m64 -S  参数下编译产生的汇编码：（与-S参数下相同）

```assembly
	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"Result is: %d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$5, -12(%rbp)
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	leal	2(%rax), %edx
	movl	-12(%rbp), %eax
	imull	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
```

## 问题3：

主要考虑：通过命令行参数传入要处理的字符串，然后用C语言处理字符串的方式，用字符串索引当作读取头，按照NFA规则判断即可。