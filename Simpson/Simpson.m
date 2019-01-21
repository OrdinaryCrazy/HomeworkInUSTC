N = 12;
last_simpson = 0;
syms x;
result = int(test_function(x),x,1,5);
for i = 1:N
    h = (5 - 1) / 2^i;
    middle = 0;
    for j = 1:( 2^i - 1 )
        if mod(j,2) == 1
            middle = middle + 4 * test_function( 1 + j * h );
        else
            middle = middle + 2 * test_function( 1 + j * h );
        end
    end
    simpson = h / 3 * (test_function(1) + test_function(5) + middle);
    if i == 1
        fprintf("N = %d 时,数值积分值 = %.15f ，误差 = %.15f\n",2^i + 1,simpson,result - simpson);
    else
        fprintf("N = %d 时,数值积分值 = %.15f ，误差 = %.15f\t，阶误差 = %.15f\n",2^i + 1,simpson,result - simpson,log(last_simpson / simpson) / log(2));
    end
    last_simpson = simpson;
end