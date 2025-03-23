function[x, y, w] = EDPHiperbolica(f, g, l, T, alpha, n, m)
    h = l/m % Valores de x
    k = T/n % Valores de y
    lambda = (alpha*k)/h;
    x = 0:h:l;
    y = 0:k:T;
    d= 2*(1-lambda^2);

    A = diag(d*ones(m-1,1));
    A = A+diag(lambda^2*ones(m-2,1),1)+diag(lambda^2*ones(m-2,1),-1);
    
    w0 = f(x(2:end-1))';
    w1 = w0+k*g(x(2:end-1))';
    w1 = w1';
    
    w = zeros(m-1, n+1);
    w(:,1) = w0;
    w(:,2) = w1;

    for j = 2:n
        w(:,j+1) = A*w(:,j)-w(:,j-1);
    end

    num_filas = size(w, 1);
    num_columnas = size(w, 2);

    filas = cell(num_filas, 1);
    for i = 1:num_filas
        filas{i} = sprintf('X : %.4f', x(i+1));
    end

    columnas = cell(num_columnas, 1);
    K = 0:k:T;
    for j = 1:num_columnas
        columnas{j} = sprintf('K: %.4f', K(j));
    end
    
    Tabla = array2table(w, 'RowNames', filas, 'VariableNames', columnas);
    disp(Tabla);
    
end