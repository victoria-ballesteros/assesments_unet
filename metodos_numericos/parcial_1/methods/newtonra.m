function [r, iter] = newtonra(f, df, x0, tol, itmax)
    r = zeros(1, itmax);  % Inicializar un vector para guardar los valores de x1
    for n = 1:1:itmax
        if df(x0) == 0
            error('La derivada es cero en x = %f. El método no puede continuar.', x0);
        end
        
        x1 = x0 - (f(x0) / df(x0));
        r(n) = x1;  % Guardar el valor actual de x1
        
        if abs(x1 - x0) < tol
            iter = n;
            r = r(1:n);  % Recortar el vector r hasta las iteraciones realizadas
            break;
        else
            x0 = x1;
        end
        
        if n == itmax
            disp('El método alcanzó el número máximo de iteraciones sin converger a la tolerancia deseada');
            r = r(1:n);  % Recortar el vector r hasta las iteraciones realizadas
        end
    end
end