function [x, iter] = gaussSeidel(A, b, x0, tol, maxIter)
    % A: Matriz de coeficientes
    % b: Vector de constantes
    % x0: Vector inicial (puede ser un vector de ceros)
    % tol: Tolerancia para el criterio de parada
    % maxIter: Número máximo de iteraciones permitidas
    
    n = length(b); % Número de ecuaciones
    x = x0; % Inicialización del vector solución
    iter = 0; % Contador de iteraciones
    
    % Iteración de Gauss-Seidel
    while iter < maxIter
        x_old = x; % Guardar el vector solución anterior
        for i = 1:n
            % Sumar las contribuciones de las variables anteriores y posteriores
            sum1 = A(i, 1:i-1) * x(1:i-1);
            sum2 = A(i, i+1:n) * x_old(i+1:n);
            
            % Actualizar la solución de la variable i
            x(i) = (b(i) - sum1 - sum2) / A(i, i);
        end
        
        % Incrementar el contador de iteraciones
        iter = iter + 1;
        
        % Verificar la convergencia
        if norm(x - x_old, inf) < tol
            break;
        end
    end
    
    % Verificar si el método alcanzó la solución dentro del número máximo de iteraciones
    if iter == maxIter
        disp('El método no convergió dentro del número máximo de iteraciones');
    end
end