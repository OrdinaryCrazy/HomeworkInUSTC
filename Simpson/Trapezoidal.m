N = 12;
last_trapezoidal = 0;
syms x;
result = int(test_function(x),x,1,5);
for i = 1:N
    h = (5 - 1) / 2^i;
    middle = 0;
    for j = 1:( 2^i - 1 )
        middle = middle + test_function( 1 + j * h );
    end
    trapezoidal = h * (test_function(1) + test_function(5) + middle);
    if i == 1
        fprintf("N = %d 时,数值积分值 = %.15f ，误差 = %.15f\n",2^i + 1,trapezoidal,result - trapezoidal);
    else
        fprintf("N = %d 时,数值积分值 = %.15f ，误差 = %.15f\t，阶误差 = %.15f\n",2^i + 1,trapezoidal,result - trapezoidal,log(last_trapezoidal / trapezoidal) / log(2));
    end
    last_trapezoidal = trapezoidal;
end