function [ r ] = correlacion( x,y )
[~, ncol] = size(y);
if ncol > 1
    y = fliplr(y);
else
    y = flipud(y);
end

r = convolucion(x, y);
n = -(length(y)-1):1:length(x)-1;

plot(n,r);

end