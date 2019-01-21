number = [5, 10, 20, 40];
for i = 1:length(number)

    fprintf("For n = %d:\n",number(i));
    %*******************************************************
    x = [-5];
    f = [test_function(x(1))];
    max = 0;

    fprintf("\tFor xi = -5 + 10 * (i / %d)\t\t\t\t",number(i));
    for j = 1:number(i)
        x = [x,(-5 + 10 * j / number(i))];
        f = [f,test_function(x(j))];
    end

    %a = [];
    %yl = [];
    %yx = [];
    %*******************************
    y = -5;
    approx = lagrange(number(i) + 1,x,f,y);
    result = test_function(y);
    diff = abs(approx - result);
    if diff > max
        max = diff;
    end
    %*******************************
    for j = 1:500
        y = -5 + (10 * j) / 500;
        approx = lagrange(number(i) + 1,x,f,y);
        result = test_function(y);
        %yx = [yx,y];
        %a = [a,approx];
        %yl = [yl,result];
        diff = abs(approx - result);
        if diff > max
            max = diff;
        end
    end
    disp("maxdiff = " + max);
    %plot(yx,a,'r*',yx,yl,'g-');
    %title("xi = -5 + 10 * (i / n)");
    %legend('Approximation','RealResult');
    %prompt = 'asdas';
    %input(prompt);
    %*******************************************************
    %*******************************************************

    max = 0;
    x = [(-5 * cos(pi / (2 * number(i) + 2)))];
    f = [test_function(x(1))];
    fprintf("\tFor xi = -5 * cos((2 * i + 1) * pi / (2 * %d + 2))\t",number(i));

    for j = 1:number(i)
        x = [x,(-5 * cos((2 * j + 1) * pi / (2 * number(i) + 2)))];
        f = [f,test_function(x(j))];
    end
    
    y = (-5 * cos(pi / (2 * number(i) + 2)));
    approx = lagrange(number(i) + 1,x,f,y);
    result = test_function(y);
    diff = abs(approx - result);
    if diff > max
        max = diff;
    end

    %a = [approx];
    %yl = [result];
    %yx = [y];

    for j = 1:500
        y = -5 + (10 * j) / 500;
        approx = lagrange(number(i) + 1,x,f,y);
        result = test_function(y);
        %a = [a,approx];
        %yx = [yx,y];
        %yl = [yl,result];
        diff = abs(approx - result);
        if diff > max
            max = diff;
        end
    end
    disp("maxdiff = " + max)
    %plot(yx,a,'r*',yx,yl,'g-');
    %title("xi = -5 * cos((2 * i + 1) * pi / (2 * n + 2))");
    %legend('Approximation','RealResult');
    %prompt = 'asdas';
    %input(prompt);
    %*******************************************************
end