function[v] = simpson(f, a, b, n, h, oneOrAnother)
    if oneOrAnother
        if mod(n, 2) ~= 0
            error('El número de subintervalos n debe ser par.');
        end
        x = linspace(a, b, n+1);
        y = f(x);
        v = h/3 * (y(1) + 4*sum(y(2:2:end-1)) + 2*sum(y(3:2:end-2)) + y(end));

    else
        v = integral(f, a, b, 'ArrayValued', true);
    end
    fprintf('La integral aproximada usando el método de Simpson es: %.10f\n', v);
end