a = [ 31, -13,  0,  0,   0, -10,  0, 0,  0;
     -13,  35, -9,  0, -11,   0,  0, 0,  0;
       0,  -9, 31,-10,   0,   0,  0, 0,  0;
       0,   0,-10, 79, -30,   0,  0, 0, -9;
       0,   0,  0,-30,  57,  -7,  0,-5,  0;
       0,   0,  0,  0,  -7,  47,-30, 0,  0;
       0,   0,  0,  0,   0, -30, 41, 0,  0;
       0,   0,  0,  0,  -5,   0,  0,27, -2;
       0,   0,  0, -9,   0,   0,  0,-2, 29
    ];
b = [-15;27;-23;0;-20;12;-7;7;10];
n = 9;
%*************************************************************
s = zeros(1,n);
row_max_index = zeros(1,n);
x = zeros(1,n);
p = [1:1:n];        %交换行序之后的结果
%*************************************************************
[s,row_max_index] = max(a);
for k = 1:n-1
    pivot = k;
    for j = k:n
        if(abs(a(p(pivot),k))/s(p(pivot)) < abs(a(p(j),k))/s(p(j)))
            pivot = j;
        end
    end
    tmp = p(pivot);
    p(pivot) = p(k);
    p(k) = tmp;
    for i = k + 1:n
        z = a(p(i),k) / a(p(k),k);
        a(p(i),k) = z;
        for m = k+1:n
            a(p(i),m) = a(p(i),m) - z * a(p(k),m);
        end
        b(p(i)) = b(p(i)) - z * b(p(k));
    end
end
for i = n:-1:1
    tmp = 0;
    for j = i+1:n
        tmp = tmp + a(p(i),j) * x(j);
    end
    x(i) = (b(p(i)) - tmp) / a(p(i),i);
end
x






