clear; close all; clc; %reset

%% normalisasi Sinyal
load('speech.dat');  % import "speech"

fs = 8000;           % Sampling rate (Hz)
N = length(speech);  % Jumlah sampel
t = (0:N-1)/fs;      % Vektor waktu

% Normalisasi sinyal di rentang -5 hingga 5
speech = 5 * speech / max(abs(speech));

% Rentang kuantisasi
Xmin = -5;
Xmax = 5;

%% Kuantisasi Manual untuk tiap bit
bits = input('Masukkan jumlah bit untuk kuantisasi (misal: 3, 8, atau 15): ');

% Proses kuantisasi 
qspeech = zeros(size(speech));
for i = 1:N
    [I, pq] = biquant(bits, Xmin, Xmax, speech(i));
    qspeech(i) = pq;
end

% Perhitungan SNR dari sinyal yang dikuantisasi
snr_val = calcsnr(speech, qspeech);
disp(['SNR untuk ', num2str(bits), ' bit adalah: ', num2str(snr_val), ' dB']);

% Plot sinyal asli dan sinyal hasil kuantisasi
figure;
subplot(2,1,1);
plot(t, speech, 'b');
xlabel('Waktu (detik)');
ylabel('Amplitudo');
title('Sinyal Asli');
grid on;

subplot(2,1,2);
plot(t, qspeech, 'r');
xlabel('Waktu (detik)');
ylabel('Amplitudo');
title(['Sinyal Kuantisasi dengan ', num2str(bits), ' Bit']);
grid on;

% cek kualitas suara
disp('Memainkan sinyal asli...');
sound(speech/max(abs(speech)), fs);
pause(5);

disp(['Memainkan sinyal kuantisasi dengan ', num2str(bits), ' bit...']);
sound(qspeech/max(abs(qspeech)), fs);

%% Plot SNR vs Jumlah Bit (3-15)
bits_range = 3:15;
snr_values = zeros(1, length(bits_range));

for idx = 1:length(bits_range)
    b = bits_range(idx);
    qspeech_temp = zeros(size(speech));
    
    % Proses kuantisasi untuk tiap bit
    for i = 1:N
        [I, pq] = biquant(b, Xmin, Xmax, speech(i));
        qspeech_temp(i) = pq;
    end
    
    % Perhitungan SNR untuk kuantisasi
    snr_values(idx) = calcsnr(speech, qspeech_temp);
end

% Plot SNR (dB) vs jumlah bit
figure;
plot(bits_range, snr_values, 'b-o', 'LineWidth', 2);
xlabel('Jumlah Bit');
ylabel('SNR (dB)');
title('Plot SNR vs. Jumlah Bit pada Kuantisasi Sinyal Suara');
grid on;
