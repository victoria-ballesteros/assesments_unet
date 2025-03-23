%% Asignación 1 - Problema 3
% Datos

w = [0.017, 0.087, 0.174, 1.11, 1.74, 4.09, 5.45, 5.96, 0.025, 0.111, 0.211, 0.999, 3.02, 4.28, 4.58, 4.68, 0.020, 0.085, 0.171, 1.29, 3.04, 4.29, 5.30, 0.020, 0.119, 0.210, 1.32, 3.34, 5.48, 0.025, 0.233, 0.783, 1.35, 1.69, 2.75, 4.83, 5.53];
r = [0.154, 0.296, 0.363, 0.531, 2.23, 3.58, 3.52, 2.40, 0.23, 0.375, 0.366, 0.771, 2.01, 3.28, 2.96, 5.10, 0.181, 0.260, 0.334, 0.87, 3.59, 3.40, 3.88, 0.180, 0.299, 0.428, 1.15, 2.83, 4.15, 0.234, 0.537, 1.47, 2.48, 1.44, 1.84, 4.66, 6.94];
[wSorted, idx] = sort(w);
rSorted = r(idx);

%% a)

% Metodo (Minimos cuadrados - Lineal)
disp('Calculo de coeficientes mediante minimos cuadrados, con aproximacion polinomica lineal.');
line = polyfit(log(wSorted), log(rSorted), 1);
rFit = exp(polyval(line, log(wSorted)));
a = line(1);
fprintf('a: %.4f\n', a);
b = exp(line(2));
fprintf('a: %.4f\n', b);

%% b)

% Grafico lineal

figure;
hold on;
scatter(wSorted, rSorted, 'filled');
plot(wSorted, rFit, 'r');
xlabel('W (Peso de las larvas)'), ylabel('R (Consumo de oxígeno)');
legend('Datos originales', 'Curva ajustada');
title('r = bw^a');
hold off;

%% c)

% Error lineal

errorLineal = sum((rSorted - rFit).^2);
fprintf('El error asociado es: %.20f\n', errorLineal);

%% d)

% Metodo (Minimos Cuadrados - Cuadratico)
disp('Calculo de coeficientes mediante minimos cuadrados, con aproximacion polinomica cuadratica.');
line = polyfit(log(wSorted), log(rFit), 2);
rFitCuadratic = exp(polyval(line, log(wSorted)));
a = line(2);
fprintf('a: %.4f\n', a);
b = exp(line(3));
fprintf('a: %.4f\n', b);

% Grafico cuadratico

figure;
hold on;
scatter(wSorted, rSorted, 'filled');
plot(wSorted, rFitCuadratic, 'r');
xlabel('W (Peso de las larvas)'), ylabel('R (Consumo de oxígeno)');
legend('Datos MCL', 'Curva ajustada');
title('r = bw^a');
hold off;

% Error cuadratico

errorCuadratico = sum((rSorted - rFitCuadratic).^2);
fprintf('El error asociado es: %.20f\n', errorCuadratico);
line = polyfit(log(wSorted), log(rFit), 2);
rFitCuadratic = exp(polyval(line, log(wSorted)));

%% e)

% Diferencia de error

magnitudDiferencia = abs(errorLineal - errorCuadratico);

if errorLineal == errorCuadratico
    fprintf('Los errores son iguales.');
else
    if errorLineal < errorCuadratico
        fprintf('El error lineal es menor. Produce la mejor aproximacion.\n');
        fprintf('Error lineal: %.4f\n', errorLineal);
        fprintf('Error cuadrático: %.4f\n', errorCuadratico);
    else
        fprintf('El error cuadrático es menor. Produce la mejor aproximacion.\n');
        fprintf('Error lineal: %.4f\n', errorLineal);
        fprintf('Error cuadrático: %.4f\n', errorCuadratico);
    end
    fprintf('Magnitud de la diferencia: %.20f\n', magnitudDiferencia);
end