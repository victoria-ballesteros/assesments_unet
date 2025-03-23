function [x, y, w] = EDPEliptica(f, a, b, c, d, n, m, f1, f2, f3, f4)
    hx = (b - a) / n;
    hy = (d - c) / m;

    %hx = 0.4;
    %hy = 1/3;

    x = linspace(a, b, n+1);
    y = linspace(c, d, m+1);
    
    w = zeros(n+1, m+1);
    
    % Condiciones de frontera
    % f1 en x = a
    for j = 1:m+1
        w(1, j) = f1(y(j));
    end
    
    % f2 en x = b
    for j = 1:m+1
        w(n+1, j) = f2(y(j));
    end
    
    % f3 en y = c
    for i = 1:n+1
        w(i, 1) = f3(x(i));
    end
    
    % f4 en y = d
    for i = 1:n+1
        w(i, m+1) = f4(x(i));
    end
    
    % Método de Gauss-Seidel para resolver el sistema lineal
    tol = 1e-6;
    max_iter = 10000;
    iter = 0;
    
    while iter < max_iter
        error = 0;
        for i = 2:n
            for j = 2:m
                % Actualizar w(i,j) usando el método de Gauss-Seidel
                w_new = (w(i+1,j) + w(i-1,j)) / hx^2 + (w(i,j+1) + w(i,j-1)) / hy^2 - f(x(i), y(j));
                w_new = w_new / (2 * (1/hx^2 + 1/hy^2));
                
                % Calcular el error (se puede usar el error relativo)
                error = max(error, abs(w_new - w(i,j)));
                
                % Actualizar el valor de w
                w(i,j) = w_new;
            end
        end
        
        iter = iter + 1;
        
        % Si el error es menor que la tolerancia, salimos del bucle
        if error < tol
            break;
        end
    end
    
    if iter == max_iter
        warning('El método de Gauss-Seidel no ha convergido después de %d iteraciones.', max_iter);
    else
        fprintf('El método de Gauss-Seidel ha convergido después de %d iteraciones.\n', iter);
    end
end
