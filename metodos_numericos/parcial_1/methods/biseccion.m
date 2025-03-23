function[r, iter] = biseccion(f, a, b, tol, itmax)
    if f(a) * f(b) > 0
        error('La función no cambia de signo en el intervalo dado.');
    end
    for n = 1:1:itmax
        r = (a + b) / 2;  
        if f(r) == 0
            iter = n;
            break;
        end
        if abs(b-a) / 2 < tol
            iter = n;
            break;
        end
        if f(a) * f(r) < 0
            b = r;
        else
            a = r;
        end
        if n == itmax
            disp('El método alcanzó el número máximo de iteraciones sin converger a la tolerancia deseada');
        end
    end
end