function [x] = eliminacionGaussiana(A)
    [n, m] = size(A);

    if m ~= n + 1
        error('La matriz debe ser una matriz aumentada con n+1 columnas.');
    end

    for i = 1:n-1
        if A(i, i) == 0
            error('Pivote cero encontrado. Se requiere pivoteo.');
        end
        
        for j = i+1:n
            factor = A(j, i) / A(i, i);
            A(j, i:m) = A(j, i:m) - factor * A(i, i:m);
        end
    end

    x = zeros(n, 1);
    x(n) = A(n, end) / A(n, n);

    for i = n-1:-1:1
        x(i) = (A(i, end) - A(i, i+1:n) * x(i+1:n)) / A(i, i);
    end
end

