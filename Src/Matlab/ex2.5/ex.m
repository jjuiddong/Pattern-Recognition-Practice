
x1 = [1 3 5 3];
y1 = [2 1 2 3];
x2 = [6 8 10 8];
y2 = [6 5 6 7];

c1 = cov(x1, y1);
c2 = cov(x2, y2);

m1 = [mean(x1) mean(y1)]';
m2 = [mean(x2) mean(y2)]';

plot(x1,y1, 'o', x2,y2, 'o');
grid on;
hold on;


x = [0:0.1:10 ; zeros(1,101)];
p1 = 0.5;
p2 = 0.5;
c0 =  log(p1) - log(p2) - (1/2) * m1' * inv(c1) * m1 + (1/2) * m2' * inv(c2) * m2;
g12x = (inv(c1) * (m1 - m2))' * x + c0;
x2 = -g12x (inv(c1) * (m1 - m2))' - c0;



%p1 = 0.2;
%p2 = 0.8;
%c0 = log(p1) - log(p2) - (1/2) * m1' * inv(c1) * m1 + (1/2) * m2' * inv(c2) * m2;
%g121 = (inv(c1) * (m1 - m2))' * x + c0;
%plot(x(1,:), g12(1,:), x(1,:), g121(1,:))

