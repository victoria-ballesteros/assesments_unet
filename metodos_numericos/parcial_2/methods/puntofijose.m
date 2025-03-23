function [r, iter] = puntofijose(g, x0, itmax, tol)
    iter = 0;
    x = x0;
    fprintf('Iteración\tValor de x1\tValor de x2\n');
    fprintf('--------------------------------------------\n');
    fprintf('%d\t\t%.6f\t%.6f\n', iter, x(1), x(2));
    
    while iter < itmax
        % Evaluar la función G en los valores actuales de x
        x_next = g(x); 
        iter = iter + 1;
        
        % Imprimir el valor en la iteración actual
        fprintf('%d\t\t%.6f\t%.6f\n', iter, x_next(1), x_next(2));
        
        % Verificar la convergencia utilizando la norma infinita
        if norm(x_next - x, Inf) < tol
            break;
        end
        
        x = x_next;
    end
    
    r = x;

    if iter == itmax
        warning('Punto Fijo: No convergió en el número máximo de iteraciones.');
    end
end
