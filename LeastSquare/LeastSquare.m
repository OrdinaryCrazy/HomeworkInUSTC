X = [0.25,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5];
Y = [1.284,1.648,2.117,2.718,3.427,2.798,3.534,4.456,5.465,5.894];
Matrix = [];
for j = 1:length(X)
    Matrix = [Matrix,[sin(X(j));cos(X(j))]];
end
Result = inv(Matrix * Matrix') * (Matrix * Y');
fprintf("a = %.15f,b = %.15f\n",Result(1),Result(2));
Distance = 0;
for j = 1:length(X)
    Distance = Distance + (Result(1) * Matrix(1,j) + Result(2) * Matrix(2,j) - Y(j))^2;
end
fprintf("均方误差：%.15f\n",Distance / double(length(X)));