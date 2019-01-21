function output = lagrange(n,x,f,in)
    output = 0;
    for i = 1:n
        l = 1;
        for j = 1:n
            if j ~= i
                l = l * ( (in - x(j)) / (x(i) - x(j)) );
            end
        end
        output = output + l * f(i);
    end
end