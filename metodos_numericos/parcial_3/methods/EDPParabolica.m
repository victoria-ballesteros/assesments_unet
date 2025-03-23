function [x, y, w] = EDPParabolica(f, l, T, alpha, n, m)
    h = l/m %l/m  
    k = T/n % t/n  
    
    
    lambda = (alpha^2*k)/h^2;
    
    x = 0:h:l;

    d = 1 + 2*lambda;
    A = diag(d*ones(m-1, 1));
    A = A + diag(-lambda*ones(m-2, 1), 1) + diag(-lambda*ones(m-2, 1), -1);

    w0 = f(x(2:end-1));

    w = zeros(m-1, n+1);
    w(:,1) = w0';

    for j = 1:n
        w(:, j+1) = A \ w(:, j);
    end
    
    y= 0:k:T;
    
    
end
