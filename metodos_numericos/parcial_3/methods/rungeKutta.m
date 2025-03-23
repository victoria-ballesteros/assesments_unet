function [t, y1, y2] = runge_kutta_resorte_masa(h, t_final)
    % Parámetros del sistema
    k = 3.2;  % Constante del resorte (N/m)
    M = 5;    % Masa (kg)
    zeta = 0.5;  % Factor de amortiguamiento
    omega = sqrt(k/M);  % Frecuencia natural no amortiguada (rad/s)

    % Condiciones iniciales
    y1_0 = 0;  % y(0)
    y2_0 = 0;  % y'(0)

    % Número de pasos
    N = round(t_final / h);
    t = linspace(0, t_final, N+1);
    y1 = zeros(1, N+1);  % Posiciones
    y2 = zeros(1, N+1);  % Velocidades
    y1(1) = y1_0;
    y2(1) = y2_0;

    % Funciones del sistema
    f1 = @(t, y1, y2) y2;
    f2 = @(t, y1, y2) -2*zeta*omega*y2 - omega^2*y1 + 1/M;  % F(t) = 1 para 0 <= t <= 1

    % Método de Runge-Kutta de 4to orden
    for i = 1:N
        % k1
        k1_1 = h * f1(t(i), y1(i), y2(i));
        k1_2 = h * f2(t(i), y1(i), y2(i));

        % k2
        k2_1 = h * f1(t(i) + h/2, y1(i) + k1_1/2, y2(i) + k1_2/2);
        k2_2 = h * f2(t(i) + h/2, y1(i) + k1_1/2, y2(i) + k1_2/2);

        % k3
        k3_1 = h * f1(t(i) + h/2, y1(i) + k2_1/2, y2(i) + k2_2/2);
        k3_2 = h * f2(t(i) + h/2, y1(i) + k2_1/2, y2(i) + k2_2/2);

        % k4
        k4_1 = h * f1(t(i) + h, y1(i) + k3_1, y2(i) + k3_2);
        k4_2 = h * f2(t(i) + h, y1(i) + k3_1, y2(i) + k3_2);

        % Actualizar valores
        y1(i+1) = y1(i) + (1/6)*(k1_1 + 2*k2_1 + 2*k3_1 + k4_1);
        y2(i+1) = y2(i) + (1/6)*(k1_2 + 2*k2_2 + 2*k3_2 + k4_2);
    end
end