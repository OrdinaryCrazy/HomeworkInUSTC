distance = 1.0E-8;
syms x;
fx_diff = diff(test_function(x));
standard = sqrt(3);
paramfornewton = [0.1,0.2,0.9,9.0];
for k = 1:length(paramfornewton)
    x0 = paramfornewton(k);
    fx = test_function(x0);
    count = 0;
    while(true)
        x1 = x0 - fx / subs(fx_diff,x,x0);
        fx = test_function(x1);
        count = count + 1;
        fprintf("第 %d 轮理论收敛阶对0的常数Ｃ = %.10f  ",count,(x1 - 0)/((x0 - 0)^2));
        fprintf(",对sqrt(3)的常数Ｃ = %.10f  ",(x1 - standard)/((x0 - standard)^2));
        fprintf(",对-sqrt(3)的常数Ｃ = %.10f\n",(x1 + standard)/((x0 + standard)^2));
        if(abs(fx) < distance || abs(x1 - x0) < distance)
            break;
        end
        x0 = x1;
    end
    fprintf("初值 = %.15f，根 = %.15f\t，迭代步数 = %.15f\n",paramfornewton(k),x1,count);
end