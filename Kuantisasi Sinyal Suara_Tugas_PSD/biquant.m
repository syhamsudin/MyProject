function [I, pq] = biquant(NoBits, Xmin, Xmax, value)
% Fungsi untuk encoding kuantisasi uniform
% NoBits: jumlah bit yang digunakan untuk kuantisasi
% Xmin  : nilai minimum kuantisasi
% Xmax  : nilai maksimum kuantisasi
% value : nilai input yang akan dikuantisasi
% I     : indeks kuantisasi (integer)
% pq    : nilai hasil kuantisasi
%
L = 2^NoBits;                   % Jumlah level kuantisasi
delta = (Xmax - Xmin) / L;        % Besar interval kuantisasi
I = round((value - Xmin) / delta);
if I == L
    I = I - 1;
end
if I < 0
    I = 0;
end
pq = Xmin + I * delta;
end
