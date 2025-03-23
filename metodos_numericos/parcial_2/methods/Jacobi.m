function [x] = Jacobi(A, b, x0, tol, itmax)
    [filas, ~] = size(A);
    x = x0;
    x_old = x;

    for iter = 1:itmax
        for i = 1:filas
            suma = 0;
            for j = 1:filas
                if j ~= i
                    suma = suma + (A(i, j) * x_old(j));
                end
            end
            x(i) = (b(i) - suma) / A(i, i);
        end
        
        if norm(x - x_old, inf) <= tol
            break;
        end
        
        x_old = x;
    end
    
    if iter == itmax
        disp('El método de Jacobi no ha convergido.');
    end
end
