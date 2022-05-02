function [ y ] = convolucion( u, h )
    [uFilas, ~] = size(u);
    [hFilas, ~] = size(h);
    if uFilas == 1
        u=u';
    end
    if hFilas == 1
        h=h';
    end
    col1=[h; zeros(length(u)-1,1)];
    fil1=[h(1), zeros(1, length(u)-1)];
    H = toeplitz(col1,fil1);
    y=H*u;
end