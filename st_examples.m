% STOCKWELL TRANSFORM
%
% The stockwell transform is effectively is a series of Hilbert transforms, 
% where each transform is done a band-pass filtered signal, where the width 
% of the pass-band is  proportional to the center frequency.
%
% Technically, the filtering is done with a Gaussian window in frequency
% space, where the width of the Gaussian is a function of the center
% frequency.
%
% This gives high temporal resolution, low frequency resolution for high
% frequencies, visa versa for low frequencies.
%
% The phase (angle) from the resulting spectrogram is therefore a valid
% instantaneous Hilbert phase (unlike STFT), with an absolute reference
% (unlike wavelet methods).
%
% Performance is likely to be better if the input data length is a power of 2. 
%
%
% Here are some examples:

%% Basic test to check it runs properly
len = 128;
t = 0:len-1;
cross_chirp = cos(2*pi*(10+t/7).*t/len) + cos(2*pi*(len/2.8-t/6.0).*t/len);
[st_matrix_chirps,st_times,st_frequencies] = st(cross_chirp,0,.5,1);
contourf(st_times,st_frequencies,abs(st_matrix_chirps));

%% Some toy examples to get some intuition
% pure sinuisoid
F = 15; % Hz % Try changing this to see the difference in frequency resolution
N = 512;
x = linspace(0,2,N);
y = sin(2*pi*F*(x));
y = [zeros(1,256) y zeros(1,256)]; % zero padding here shows the temporal
% resolution as a function of frequency at the discontinuities

% normalised frequency (Fs=1)
% maxF = 0.5 means only "positive" frequency components are calcualted
% (all thats required for real input signals)
spec = st(y, 0, 0.5, 1);
figure
ax = [];
ax(1) = subplot(121);
imagesc(abs(spec).^2);
set(gca,'YDir','normal')
colorbar
ax(2) = subplot(122);
imagesc(angle(spec));
set(gca,'YDir','normal')
colorbar

linkaxes(ax,'xy')

%% step
N = 512;
y = zeros(1,N);
y(200:300) = 1;

% normalised frequency (Fs=1)
% maxF = 0.5 means only "positive" frequency components are calcualted
% (all thats required for real input signals)
spec = st(y, 0, 0.5, 1);
figure
ax = [];
ax(1) = subplot(121);
imagesc(abs(spec).^2);
set(gca,'YDir','normal')
colorbar
ax(2) = subplot(122);
imagesc(angle(spec));
set(gca,'YDir','normal')
colorbar

linkaxes(ax,'xy')


%% chirp
t = linspace(0,2,2048);
% chirp with noise
y = chirp(t,0,1,150) + 0.01*randn(size(t));
spec = st(y, 0, 0.5, 1);
figure
ax = [];
ax(1) = subplot(121);
imagesc(abs(spec).^2);
set(gca,'YDir','normal')
colorbar
ax(2) = subplot(122);
imagesc(angle(spec));
set(gca,'YDir','normal')
colorbar

linkaxes(ax,'xy')
