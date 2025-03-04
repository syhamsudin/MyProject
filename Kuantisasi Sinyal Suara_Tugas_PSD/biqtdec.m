function pq = biqtdec(NoBits, Xmin, Xmax, I)
% Fungsi untuk mendekode nilai kuantisasi dari indeks
% NoBits: jumlah bit yang digunakan untuk kuantisasi
% Xmin  : nilai minimum kuantisasi
% Xmax  : nilai maksimum kuantisasi
% I     : indeks kuantisasi (integer)
% pq    : nilai hasil kuantisasi (decoded value)
%
L = 2^NoBits;
delta = (Xmax - Xmin) / L;
pq = Xmin + I * delta;
end
