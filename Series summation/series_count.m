function output = series_count(x)
    output = 0;
    if(x > 1 && rem(x,1) == 0)
        for i = 1:x
            output = output + 1/i;
        end
        output = output / x;
    else if(x == 1)
            output = 1;
        else
            line = 1500 * 100;
            for i = 1: line
                output = output + 1/(i * (i + x) * (i + 1));
            end
            output = output * (1 - x) + 1;
        end
    end
end

