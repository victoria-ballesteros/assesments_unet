function [t, w] = puntomedioedo(f, a, b, alpha, h)
    % Número de pasos
    N = (b-a)/h;
    
    % Vector de tiempos
    t = a:h:b;
    
    % Tamaño del vector de estado
    m = length(alpha);
    
    % Matriz de resultados (cada fila representa un punto en el tiempo)
    w = zeros(N+1, m);
    
    % Condición inicial
    w(1, :) = alpha';

    % Iteración sobre cada paso
    for i = 1:N
        % Evaluar la función en el punto actual
        p1 = f(t(i), w(i, :));
        
        % Calcular el punto medio
        t_mid = t(i) + h/2;
        w_mid = w(i, :)' + (h/2) * p1; % Transponer w(i, :) para la operación de suma
        
        % Evaluar la función en el punto medio
        p2 = f(t_mid, w_mid');
        
        % Actualizar el estado en el siguiente punto de tiempo
        w(i+1, :) = w(i, :) + h * p2';
    end
end
