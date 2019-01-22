; ModuleID = 'gen_fib'
source_filename = "gen_fib"

define i32 @fib(i32) {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %6, label %7

; <label>:6:                                      ; preds = %1
  store i32 0, i32* %2, align 4
  br label %19

; <label>:7:                                      ; preds = %1
  %8 = load i32, i32* %3, align 4
  %9 = icmp eq i32 %8, 1
  br i1 %9, label %10, label %11

; <label>:10:                                     ; preds = %7
  store i32 1, i32* %2, align 4
  br label %19

; <label>:11:                                     ; preds = %7
  %12 = load i32, i32* %3, align 4
  %13 = sub i32 %12, 1
  %14 = call i32 @fib(i32 %13)
  %15 = load i32, i32* %3, align 4
  %16 = sub i32 %15, 2
  %17 = call i32 @fib(i32 %16)
  %18 = add i32 %14, %17
  store i32 %18, i32* %2, align 4
  br label %19

; <label>:19:                                     ; preds = %11, %10, %6
  %20 = load i32, i32* %2, align 4
  ret i32 %20
}

define i32 @main() {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 1, i32* %2, align 4
  br label %3

; <label>:3:                                      ; preds = %11, %0
  %4 = load i32, i32* %2, align 4
  %5 = icmp slt i32 %4, 8
  br i1 %5, label %6, label %14

; <label>:6:                                      ; preds = %3
  %7 = load i32, i32* %2, align 4
  %8 = call i32 @fib(i32 %7)
  %9 = load i32, i32* %1, align 4
  %10 = add i32 %8, %9
  store i32 %10, i32* %1, align 4
  br label %11

; <label>:11:                                     ; preds = %6
  %12 = load i32, i32* %2, align 4
  %13 = add i32 %12, 1
  store i32 %13, i32* %2, align 4
  br label %3

; <label>:14:                                     ; preds = %3
  %15 = load i32, i32* %1, align 4
  ret i32 %15
}
