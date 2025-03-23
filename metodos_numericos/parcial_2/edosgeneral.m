function[] = edosgeneral(f, f_exacta, alpha, a, b, h)
    
    function dydt = myODE(t, y)
        dydt = f(t, y);
    end

    tspan = [a b];
    
    for i = 1:length(h)
        [t, w_euler] = euler(f, a, b, alpha, h(i));
        [~, w_eulermejorado] = eulermejorado(f, a, b, alpha, h(i));
        [~, w_puntomedio] = puntomedioedo(f, a, b, alpha, h(i));
        [t_ode45, w_ode45] = ode45(@myODE, tspan, alpha);
        w_exacta = f_exacta(t);
        w_ode45_interpolada = zeros(1,length(t));
        aux = length(t_ode45);
        cont = 1;
        for k = 1:aux
            if abs(t_ode45(k) - t(cont)) < 10^-6
                w_ode45_interpolada(cont) = w_ode45(k);
                cont = cont + 1;
            end
        end
    
        tabla = table(t', w_euler', w_eulermejorado', w_puntomedio, w_ode45_interpolada', w_exacta', 'VariableNames', {'t', 'w(Euler)', 'w(Euler mejorado)', 'w(Punto medio)', 'w(ode45)', 'w_exacta'});
        disp("Intervalo "+i);
        disp(" ");
        disp(tabla);
        disp(" ");
    end
end