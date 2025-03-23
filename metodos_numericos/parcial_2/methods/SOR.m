function [x] = SOR(A, b, x0, tol, w, itmax)
    [filas, ~] = size(A);
    x = x0;
    x_old = x;

    for iter = 1:itmax
        for i = 1:filas
            primera_suma = 0;

            for j = 1:i - 1
                primera_suma = primera_suma + (A(i, j) * x(j));
            end

            segunda_suma = 0;

            for j = i+1:filas
                segunda_suma = segunda_suma + (A(i, j) * x_old(j));
            end

            x(i) = (1 - w)*x_old(i) + (w/A(i, i))* (b(i) - primera_suma - segunda_suma);
        end
        
        if norm(x - x_old, inf) <= tol
            break;
        end
        
        x_old = x;
    end
    
    if iter == itmax
        disp('El método SOR no ha convergido.');
    end

end