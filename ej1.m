R=12;
L=1e-3;
C=1e-6;

x1(1)=0;
x1(2)=0;
x2(1)=0;

T1 = 2*pi*sqrt(L*C) / (100 * sqrt( 1-C*R^2 / (4*L) ) );
T2 = 2*pi*sqrt(L*C) / (15 * sqrt( 1-C*R^2 / (4*L) ) );

T=T1;

l1 = round(3e-3/T1);
u = [ones(l1,1); zeros(l1,1)];

for n=2:1:length(u)   
    x1(n) = x2(n-1)*T + x1(n-1);
    x2(n) = x2(n-1) + (u(n) - R*x2(n-1) - x1(n)/C )*T/L;
end

uc=x1/C;
subplot(2,1,1), plot(0:T:(6e-3)-T,uc);
subplot(2,1,2), plot(0:T:(6e-3)-T,x2);


