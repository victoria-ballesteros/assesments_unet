function[] = EDPElipticaGeneral(f, a, b, c, d, n, m, f1, f2, f3, f4, f_original)
    [x, y, w] = EDPEliptica(f, a, b, c, d, n, m, f1, f2, f3, f4);
    w_solved = w(2:end,2:end)
  
    [X, Y] = meshgrid(x, y);
    f_solved = f_original(X, Y)
    
    figure;
    tiledlayout(1,2, 'TileSpacing', 'Compact', 'Padding', 'Compact')
    
    nexttile
    surf(X, Y, w');
    title('Aproximación mediante diferencias finitas')
    colorbar;
    colormap("jet");
    nexttile
    surf(X, Y, f_solved);
    title('Solución exacta')
    colormap("jet");
end