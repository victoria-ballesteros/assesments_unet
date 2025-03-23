function[r, iter] = secante(f, x0, x1, tol, itmax)
    for n = 1:1:itmax
        x2 = x1 - (f(x1) * (x1 - x0)) / (f(x1) - f(x0));
        if abs(x1 - x2) < tol
            r = x2;
            iter = n;
            break;
        else
            x0 = x1;
            x1 = x2;
        end
    end
end