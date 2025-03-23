function [dd, val] = polynewton(x, y, t)
    n = length(x);
    dd = zeros(n, n); 
    dd(:,1) = y(:);

    for j = 2:n
        for i = 1:n-j+1
            dd(i,j) = (dd(i+1,j-1) - dd(i,j-1)) / (x(i+j-1) - x(i));
        end    
    end

    val = dd(1,1); 
    product_term = 1; 

    for i = 2:n
        product_term = product_term * (t - x(i-1)); 
        val = val + dd(1,i) * product_term; 
    end
end
