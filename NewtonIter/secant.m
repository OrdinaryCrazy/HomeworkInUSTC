distance = 1.0E-8;
standard = sqrt(3);
rank = (1 + sqrt(5))/2;
paramforsecant = [-0.1,0.1;-0.2,0.2;-2.0,0.9;0.9,9.0];
for k = 1:length(paramforsecant)
    x0 = paramforsecant(k,1);
    x1 = paramforsecant(k,2);
    fx0 = test_function(x0);
    fx1 = test_function(x1);
    count = 0;
    while(true)
        s = (x1 - x0) / (fx1 - fx0);
        x0 = x1;
        fx0 = fx1;
        x1 = x1 - fx1 * s;
        fx1 = test_function(x1);
        count = count + 1;
        fprintf("第 %d 轮理论收敛阶对0的常数Ｃ = %.10f  ",count,abs((x1 - 0)/((x0 - 0)^rank)));
        fprintf(",对sqrt(3)的常数Ｃ = %.10f  ",abs((x1 - standard)/((x0 - standard)^rank)));
        fprintf(",对-sqrt(3)的常数Ｃ = %.10f\n",abs((x1 + standard)/((x0 + standard)^rank)));
        if(abs(fx1) < distance || abs(x1 - x0) < distance)
            break;
        end
    end
    fprintf("初值 = (%.15f,%.15f)\t，根 = %.15f\t，迭代步数 = %.15f\n",paramforsecant(k,1),paramforsecant(k,2),x1,count);
end