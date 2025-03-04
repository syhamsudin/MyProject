function snr = calcsnr(speech, qspeech)
% Fungsi untuk menghitung Signal-to-Noise Ratio (SNR)
% speech : sinyal asli
% qspeech: sinyal yang telah dikuantisasi
% snr    : nilai SNR dalam dB
%
qerr = speech - qspeech;  % Error akibat kuantisasi
snr = 10 * log10(sum(speech.^2) / sum(qerr.^2));
end
