%% Pregunta 1

f = @(x) 4*x^3 + 3*x^2 + 2*x + 1;

x = [0 2 4 8];

error = 0;

for i = 0:8
    [dd, val] = polynewton(x, f(i), i);
    error = error + (f(i) - val);
end

disp(error);

%% Pregunta 2

a = 0.1235*10^-4;
b = 0.9477*10^-6;
c = 0.1942*10^5;

resp = a * b * c

%% Pregunta 3

for i = 0:10
    P = 1 - (2*i) / 3
end

%% Pregunta 4

f = @(x) 2^-x - x;
a = 0;
b = 1;
tol = 10^-5;

[r, iter] = biseccion(f, a, b, tol, 50);

disp(r);

%% Pregunta 5

f = @(x) cos(x + sqrt(2)) - x*(x/2 + sqrt(2));
df = @(x) - x - sin(x + 2^(1/2)) - 2^(1/2);
x0 = -0.5;
tol = 10^-5;

[r, iter] = newtonra(f, df, x0, tol, 50);

r(iter)

fprintf("%.4f", r(iter))

%% Pregunta 6

f = @(x) exp(1)^x - 3*x^2;
x0 = 3;
x1 = 5;
tol = 10^-5;

[r, iter] = secante(f, x0, x1, tol, 50);
r

%% Pregunta 7

f = @(x) sin(x);
x = [0.30 0.32 0.33 0.35];
y = f(x);

[coef, val] = polylagrange(x, y, sin(0.34));

val

%% Pregunta 8

x = [1.8 2.0 2.2 2.4 2.6];
y = [0.5815 0.5767 0.556 0.5202 0.4708];

[dd, val] = polynewton(x, y, 2.5);

val

%% Pregunta 9

x = [1.0 3.0 5.0 7.0 10.0 12.0 13.0 16.0 18.0 20.0];
y = [4.0 5.0 6.0 5.0 8.0 7.0 6.0 9.0 12.0 11.0];

line = polyfit(x, y, 1);
yFit = polyval(line, x);

error = sum(y - yFit).^2

%% Pregunta 10

f = @(t) 9*(exp(1)^(-0.7*t))*cos(4*t) - 3.5;
a = 0;
b = 1;
tol = 0.000001;

[r, iter] = biseccion(f, a, b, tol, 50);
r
