function [a, b] = regrePoten(x, y)
    x_aprox = log(x);
    y_aprox = log(y);
    coef = polyfit(x_aprox, y_aprox, 1);
    a = coef(1);
    b = exp(coef(2));
end

