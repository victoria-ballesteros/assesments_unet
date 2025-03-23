function [r, iter] = newtonse(F, X0, itmax, tol)
    n = length(X0);
    vars = sym('x', [n, 1]);
    F_sym = F(vars);
    J_sym = jacobian(F_sym, vars);
    iter = 0;
    X = X0(:);
    while iter < itmax
        fx = F(X);
        jx = double(subs(J_sym, vars, num2cell(X)));

        delta_x = -jx \ fx;
        X = X + delta_x;
        iter = iter + 1;

        if norm(delta_x) < tol
            break;
        end
    end

    r = X; 
     if iter == itmax
        warning('newtonse: No convergió en el número máximo de iteraciones.');
    end
end
