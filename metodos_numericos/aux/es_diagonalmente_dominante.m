function edd = es_diagonalmente_dominante(A)
    n = size(A, 1);
    kf = 0;
    for i = 1:n
        sf = sum(abs(A(i, :))) - A(i,i); % suma de elementos de la fila i
        if 2*abs(A(i, i)) > sf
            kf = kf + 1; % fila dominante
        end
    end
    if kf == n
        edd = true; % la matriz es dominante diagonal
    else
        edd = false; % la matriz no es dominante diagonal
    end
end