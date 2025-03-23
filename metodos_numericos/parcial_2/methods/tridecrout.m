function [L, U] = tridecrout(A)

if size(A,1)~=size(A,2)
    error('A must be a square matrix')
end

% Saco el numero de columnas
n = size(A, 1);

% Inicializo L
L = zeros(n);

% Inicializo U con diagonal de 1
U = eye(n);

% La primera columna de L va ser igual a la primera fila de A
L(:,1) = A(1,:);

%Operaciones con la primera fila de U
U(1, 2:n) = A(1, 2:n) / L(1, 1);

for k=2:n
    for j=2:n
        for i=j:n
            L(i, j)=A(i, j) - dot(L(i, 1:j-1), U(1:j-1, j));
        end
        U(k, j) = (A(k, j) - dot(L(k, 1:k-1), U(1:k-1, j))) / L(k,k);
    end
end
