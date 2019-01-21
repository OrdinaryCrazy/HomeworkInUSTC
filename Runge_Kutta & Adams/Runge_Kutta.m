a = 0;
b = 1.5;
h = 0.1 / (2^3);
err = [];
z = 3 / (1 + 1.5^3);
for i = 1:4
    x = 0;y = 3;
    m = (b - a)/h;
    for j = 1:m
        K1 = h * f(x      ,y       );
        K2 = h * f(x + h/2,y + K1/2);
        K3 = h * f(x + h/2,y + K2/2);
        K4 = h * f(x + h  ,y + K3  );
        x = x + h;
        y = y + (K1 + 2*K2 + 2*K3 + K4)/6;
    end
    err = [abs(z - y),err];
    h = h * 2;
end
for i = 1:3
    fprintf("h = %.8f,err = %0.15f,ok = %0.15f\n",0.1/(2^(i-1)),err(i),log(err(i)/err(i + 1))/log(2));
end
fprintf("h = %.8f,err = %0.15f\n",0.1/(2^(3)),err(4));