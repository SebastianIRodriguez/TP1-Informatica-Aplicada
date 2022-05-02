R=12;
L=1e-3;
C=1e-6;

x1(1)=0;
x1(2)=0;
x2(1)=0;

%1000 Hz, 2000 Hz, 3000 Hz, 4000 Hz, 4500 Hz, 4700 Hz, 4800 Hz, 5000
%Hz, 5100 Hz, 5300 Hz, 5500 Hz, 6000 Hz, 7000 Hz, 8000 Hz, 9000 Hz y 10000 Hz.

F=10000;
T = 2*pi*sqrt(L*C) / (100 * sqrt( 1-C*R^2 / (4*L) ) );
abscisas = 0:T:(6e-3)-T;

u = sin(2*pi*F*abscisas);

for n=2:1:length(u)   
    x1(n) = x2(n-1)*T + x1(n-1);
    x2(n) = x2(n-1) + (u(n) - R*x2(n-1) - x1(n)/C )*T/L;
end

uc=x1/C;

posCorte=round(length(abscisas)/2);
plot(abscisas(posCorte:length(abscisas)),uc(posCorte:length(abscisas)));
%subplot(2,1,1), plot(abscisas,uc);
%subplot(2,1,2), plot(abscisas,x2);