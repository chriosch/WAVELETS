% load signals
load signal.txt
load aprox_5.txt
load detail_1.txt
load detail_2.txt
load detail_3.txt
load detail_4.txt
load detail_5.txt

% plot signals
subplot(7,1,1), plot (signal), ylabel('S')
subplot(7,1,2), plot (aprox_5), ylabel('A5')
subplot(7,1,3), plot (detail_5), ylabel('D5')
subplot(7,1,4), plot (detail_4), ylabel('D4')
subplot(7,1,5), plot (detail_3), ylabel('D3')
subplot(7,1,6), plot (detail_2), ylabel('D2')
subplot(7,1,7), plot (detail_1), ylabel('D1')

% free memory
% clear aprox_5
% clear detail_1
% clear detail_2
% clear detail_3
% clear detail_4
% clear detail_5
% clear signal
