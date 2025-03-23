function [x] = trisolve(L, U, b)
    n = length(b);
    y = zeros(n, 1);
    
    for i = 1:n
        y(i) = b(i) - L(i, 1:i-1) * y(1:i-1);
    end
    
    x = zeros(n, 1);
    
    for i = n:-1:1
        x(i) = (y(i) - U(i, i+1:n) * x(i+1:n)) / U(i, i);
    end
end