function backward_euler
    solve(-1e6, 3, 0.2, 1);
    figure;
    t = (0:30)/10;
    Ans = exact(-1e6, 1, t);
    plot(t, Ans);
    hold on;
    plot(t, solve(-1e6, 3, 0.1, 1));
    
    solve(-1e6, 3, 0.05, 1);
    solve(-1e6, 3, 0.2, 1.5);
    t = (0:30)/10;
    Ans = exact(-1e6, 1.5, t);
    plot(t, Ans);
    hold on;
    plot(t, solve(-1e6, 3, 0.1, 1.5));
    
    solve(-1e6, 3, 0.05, 1.5);
end

function P = exact(lmd, u0, t)
    P = exp(lmd * t) .* (u0 - 1) + cos(t);
end

function P = step(lmd, k, u, t)
    t1 = t + k;
    P = (u - k * (lmd * cos(t1) + sin(t1))) / (1 - k * lmd);
end

function P = solve(lmd, T, k, u0)
    N = floor(T / k);
    u = zeros(1, N);
    u(1) = u0;
    err = 0;
    for i = 1:N
        u(i+1) = step(lmd, k, u(i), (i-1)*k);
        exact_value = exact(lmd, u0, i*k);
        err = max(err, abs(u(i+1) - exact_value));
    end
    fprintf("k = %f, u0 = %f, err = %e\n", k, u0, err);
    P = u;
end
