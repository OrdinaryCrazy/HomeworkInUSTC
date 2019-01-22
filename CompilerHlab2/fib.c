int fib(int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fib(n - 1) + fib(n - 2);
}
int main() {
    int x = 0;
    for (int i = 1; i < 8; ++i) {
        x += fib(i);
    }
    return x;
}