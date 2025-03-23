function[v] = trapecio(f, a, b, n, h, oneOrAnother)
    if oneOrAnother
        x = linspace(a, b, n+1);
        y = f(x);
        v = h * (sum(y) - 0.5*(y(1) + y(end)));
    else
        x = linspace(a, b, n+1);
        y = f(x);
        v = trapz(x, y);
    end
    fprintf('La integral aproximada usando la regla del trapecio es: %.10f\n', v);
end