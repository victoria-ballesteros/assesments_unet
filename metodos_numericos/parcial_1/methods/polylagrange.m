function [coef, val] = polylagrange(x, y, t)
    n = length(x);
    coef = zeros(1, n);

    for i = 1:n
        Lk = 1;
        for j = 1:n
            if (j ~= i)
                Lk = conv(Lk, [1 -x(j)]) / (x(i) - x(j));
            end
        end
        coef = coef + y(i) * Lk;
    end
    
    val = polyval(coef, t);
end