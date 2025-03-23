function [t, w] = eulermejorado(f, a, b, alpha, h)
    N = (b - a) / h;
    t = a:h:b;
    w = zeros(length(alpha), N+1);
    
    w(:,1) = alpha;
    
    for i = 1:N
        p1 = f(t(i), w(:,i));
        w_estimada = w(:,i) + h * p1;
        p2 = f(t(i+1), w_estimada);
        w(:,i+1) = w(:,i) + (h/2) * (p1 + p2);
    end
end
