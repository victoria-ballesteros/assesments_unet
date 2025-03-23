function [x, w] = disparonolineal(f, a, b, alpha, beta, h)
    % Función para el método del disparo no lineal
    % f es la función que representa f(x, y, y')
    % [a, b] es el intervalo
    % alpha, beta son las condiciones de frontera
    % h es el tamaño del paso
    
    % Definir el vector de puntos de la red
    N = (b - a) / h;
    x = a:h:b;
    
    % Aproximaciones iniciales de la pendiente t
    t0 = (beta - alpha) / (b - a);
    t1 = 2 * t0;
    
    % Resolver el PVI para las pendientes t0 y t1
    [~, w0] = ode45(@(x, w) sistema(x, w, f), x, [alpha, t0]);
    [~, w1] = ode45(@(x, w) sistema(x, w, f), x, [alpha, t1]);

    % Método de la secante para ajustar la pendiente
    tol = 0.0001; % tolerancia
    while abs(w1(end,1) - beta) > tol
        % Actualizar la pendiente usando el método de la secante
        t_new = t1 - (w1(end,1) - beta) * (t1 - t0) / (w1(end,1) - w0(end,1));
        
        % Resolver con la nueva pendiente
        t0 = t1;
        t1 = t_new;
        w0 = w1;
        [~, w1] = ode45(@(x, w) sistema(x, w, f), x, [alpha, t1]);
    end
    
    % La solución final
    w = w1(:,1);

    % Graficar la solución
    plot(x, w, '-o');
    xlabel('x');
    ylabel('Aproximación y(x)');
    title('Método del disparo no lineal');
end

function dwdx = sistema(x, w, f)
    % Convertir EDO de segundo orden a sistema de primer orden
    dwdx = [w(2); f(x, w(1), w(2))];
end