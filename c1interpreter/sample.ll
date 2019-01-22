; ModuleID = 'test.c1'
source_filename = "test.c1"

@input_ivar = global i32 0
@input_fvar = global double 0.000000e+00
@output_ivar = global i32 0
@output_fvar = global double 0.000000e+00

declare void @inputInt_impl(i32*)

declare void @inputFloat_impl(double*)

declare void @outputInt_impl(i32*)

declare void @outputFloat_impl(double*)

define void @inputInt() {
entry:
  call void @inputInt_impl(i32* @input_ivar)
  ret void
}

define void @inputFloat() {
entry:
  call void @inputFloat_impl(double* @input_fvar)
  ret void
}

define void @outputInt() {
entry:
  call void @outputInt_impl(i32* @output_ivar)
  ret void
}

define void @outputFloat() {
entry:
  call void @outputFloat_impl(double* @output_fvar)
  ret void
}

define void @main() {
entry:
  store i32 10, i32* @output_ivar
  call void @outputInt()
  ret void
}
