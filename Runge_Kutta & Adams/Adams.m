a = 0;
b = 1.5;
h = 0.1 / (2^3);
err = [];
z = 3 / (1 + 1.5^3);
for i = 1:4
    x = 0;y = 3;
    m = (b - a)/h;
    %多步格式起始步
    for j = 1:3
        K1 = h * f(x      ,y(j)       );
        K2 = h * f(x + h/2,y(j) + K1/2);
        K3 = h * f(x + h/2,y(j) + K2/2);
        K4 = h * f(x + h  ,y(j) + K3  );
        x = x + h;
        tmpy = y(j) + (K1 + 2*K2 + 2*K3 + K4)/6;
        y = [y,tmpy];
    end
    for j = 4:m
        %预估
        prey = y(4) + h*(55*f(x,y(4))-59*f(x-h,y(3))+37*f(x-2*h,y(2))-9*f(x-3*h,y(1))) / 24;
        %校正
        newy = y(4) + h*(9*f(x+h,prey)+19*f(x,y(4))-5*f(x-h,y(3))+f(x-2*h,y(2))) / 24;
        x = x + h;
        y = [y(2:4),newy];
    end
    err = [abs(z - y(4)),err];
    h = h * 2;
end
for i = 1:3
    fprintf("h = %.8f,err = %0.15f,ok = %0.15f\n",0.1/(2^(i-1)),err(i),log(err(i)/err(i + 1))/log(2));
end
fprintf("h = %.8f,err = %0.15f\n",0.1/(2^(3)),err(4));