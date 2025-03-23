function [x, w] = disparolineal(f, a, b, alpha, beta, h)
    x = a:h:b;

    function dydx = sistema(x, y)
        dydx = [y(2); f(x, y(1), y(2))];
    end

    z1 = 0;
    [~, y1] = ode45(@(x, y) sistema(x, y), x, [alpha z1]);
    
    z2 = 1;
    [~, y2] = ode45(@(x, y) sistema(x, y), x, [alpha z2]);

    y1_b = y1(end, 1);
    y2_b = y2(end, 1);

    z = z1 + (z2 - z1)*(beta - y1_b)/(y2_b - y1_b);

    [~, y] = ode45(@(x, y) sistema(x, y), x, [alpha z]);

    w = y(:, 1);
end

