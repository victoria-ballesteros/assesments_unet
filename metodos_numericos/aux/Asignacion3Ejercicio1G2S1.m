%% Práctica 3 -Ejercicio 1
%% Un Paracaidista de masa M kg salta desde un avión en t = 0. Suponemos que la velocidad vertical inicial del paracaidista es cero en t = 0 y que la caída es vertical. Si el arrastre aerodinámico está dado por  F(aire) = Cv^2 donde C es una constante y v es la velocidad vertical (positiva hacia abajo).
% Queremos calcular la velocidad (variable) utilizando una ecuación diferencial 
% ordinaria de aceleración, determinada por la razón de cambio de la velocidad 
% con respecto al tiempo.

M = 70; %% Kg
C = 0.27; %% Kg/m
h = 0.1; %% Separación de los puntos de red
g = 9.807; %% m/s^2
k = C/M;
a = 0; %% Intervalo de 0 a 20 segundos
b = 5;
alpha = 0; %% Valor de la derivada en y(1)
f = @(t,v) g-k*v^2; %% Función anónima

disp("Método de Euler");
[t_euler, w_euler] = euler(f, a, b, alpha, h);
tabla = array2table([t_euler; w_euler], 'VariableNames', compose("N: %d", 1:length(t_euler)), 'RowNames', {'Tiempo(s)', 'Velocidad(m/s)'});
disp(tabla);
figure;
plot(t_euler, w_euler, '-o', 'DisplayName', 'Euler', 'LineWidth', 1.5);
hold on;
disp("Método de Euler modificado");
[t_euler_modificado, w_euler_modificado] = eulermejorado(f, a, b, alpha, h);
tabla = array2table([t_euler_modificado; w_euler_modificado], 'VariableNames', compose("N: %d", 1:length(t_euler_modificado)), 'RowNames', {'Tiempo(s)', 'Velocidad(m/s)'});
disp(tabla);
plot(t_euler_modificado, w_euler_modificado, '-rx', 'DisplayName', 'Euler', 'LineWidth', 1.5);
hold off;