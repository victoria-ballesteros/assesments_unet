function [t, w] = euler(f, a, b, alpha, h)
    N = (b - a) / h;
    t = a:h:b;
    
    w = zeros(length(alpha), N + 1); 
    
    w(:,1) = alpha;
    
    for i = 1:N
        w(:,i+1) = w(:,i) + h * f(t(i), w(:,i));
    end
end
