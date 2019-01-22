; ModuleID = 'foo_dead_recursive_loop'
source_filename = "foo_dead_recursive_loop"

define void @foo() {
entry:
  call void @foo()
  ret void
}
