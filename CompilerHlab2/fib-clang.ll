; ModuleID = 'fib.c'
source_filename = "fib.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define i32 @fib(i32) #0 { ;如何处理条件指令（跳转）和函数调用
  %2 = alloca i32, align 4          ;int %2
  %3 = alloca i32, align 4          ;int %3
  store i32 %0, i32* %3, align 4    ;可以看作是初始化 %3 = %0,%0是传过来的参数的存储位置
  %4 = load i32, i32* %3, align 4   ;%4 = %3
  %5 = icmp eq i32 %4, 0            ;%5 = %4 == 0
  br i1 %5, label %6, label %7      ;条件跳转
  ;br i1 <cond>, label <iftrue>, label <iffalse>

; <label>:6:                                      ; preds = %1
  store i32 0, i32* %2, align 4     ;%2应该是返回值
  br label %19                      ;无条件跳转

; <label>:7:                                      ; preds = %1
  %8 = load i32, i32* %3, align 4   ;%8 = %3
  %9 = icmp eq i32 %8, 1            ;%9 = %8 == 1
  br i1 %9, label %10, label %11

; <label>:10:                                     ; preds = %7
  store i32 1, i32* %2, align 4     ;返回1
  br label %19

; <label>:11:                                     ; preds = %7
  %12 = load i32, i32* %3, align 4  ;int %12 = %3
  %13 = sub nsw i32 %12, 1          ;%13 = %12 - 1
  %14 = call i32 @fib(i32 %13)
  %15 = load i32, i32* %3, align 4
  %16 = sub nsw i32 %15, 2
  %17 = call i32 @fib(i32 %16)
  %18 = add nsw i32 %14, %17
  store i32 %18, i32* %2, align 4
  br label %19

; <label>:19:                                     ; preds = %11, %10, %6
  %20 = load i32, i32* %2, align 4
  ret i32 %20
}

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main() #0 {     ;如何处理循环
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4       ;int %1 = 0
  store i32 0, i32* %2, align 4       ;int %2 = 0
  store i32 1, i32* %3, align 4       ;int %3 = 1
  br label %4

; <label>:4:                                      ; preds = %12, %0
  %5 = load i32, i32* %3, align 4     ;%5 = %3
  %6 = icmp slt i32 %5, 8             ;%6 = %5 < 8
  br i1 %6, label %7, label %15

; <label>:7:                                      ; preds = %4
  %8 = load i32, i32* %3, align 4
  %9 = call i32 @fib(i32 %8)
  %10 = load i32, i32* %2, align 4
  %11 = add nsw i32 %10, %9
  store i32 %11, i32* %2, align 4     ;%2还是返回值
  br label %12

; <label>:12:                                     ; preds = %7
  %13 = load i32, i32* %3, align 4    ;%13 = %3
  %14 = add nsw i32 %13, 1            ;%14 = %13 + 1
  store i32 %14, i32* %3, align 4     ;%3 = %14 
  br label %4 

; <label>:15:                                     ; preds = %4
  %16 = load i32, i32* %2, align 4
  ret i32 %16
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.1 (tags/RELEASE_601/final)"}
