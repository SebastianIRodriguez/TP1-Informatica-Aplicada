clear, clc

[y, Fs] = audioread('Datos_TP1_Problema2/datos_7.wav');
%plot(y(1:1000,1));

Ts = 1/Fs;
c = 340;
L = 0.2;
dTmax = L/(c*Ts);
canal1 = y(:,1);
canal2 = y(:,2);

corr = xcorr(canal1, canal2);

subplot(3,1,1), plot(canal1);
subplot(3,1,2), plot(canal2);
subplot(3,1,3), plot(corr);

[~, i] = max(corr);
%Revisar longitud del ancho de ventana, ver si hay que sumar o restar 1.
desplazamiento = i;

deltaT = desplazamiento * Ts;

theta = asin(c*deltaT/L) * 180 / pi
%plot(a)