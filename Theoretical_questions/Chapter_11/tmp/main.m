mu_values = [0.8, 1.6, 2.0, 2.4];
m = 64;
theta = linspace(0, 2*pi, 1000);
C = exp(1i * theta) - 1;

figure;

for k = 1:length(mu_values)
    mu = mu_values(k);
    eigens = zeros(1, m+1);
    for I = 0:m
        eigens(I+1) = -mu/2 * (3 - 4*exp(-2i*pi*I/m) + exp(-4i*pi*I/m)) + mu^2/2 * (1 - 2*exp(-2i*pi*I/m) + exp(-4i*pi*I/m));
    end
    subplot(2, 2, k);
    scatter(real(eigens), imag(eigens), 'r');
    hold on;
    plot(real(C), imag(C));
    hold off;
    grid on;
    xlabel('Real Part');
    ylabel('Imaginary Part');
    title(['Eigenvalues for \mu = ', num2str(mu)]);
end