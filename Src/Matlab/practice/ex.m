
t = [1:20];
y = sin(t);
%plot(t,y);
%grid on;


%A = [1 2 3 4; 5 6 7 8];
%save TestData A
%dir
%save -ascii TestData2.dat A

% transpose = A'
%b = [1 2 3]';
%c = [1 2 3];
%b * c
%'text'

a = [1 2 3];
b = [4 5 6];
%a * b'
%a.* b

%x = [0:0.1:0.5]
%y = 3*(1-x).^2.*exp(-x.^2)

%t = [0:0.1:5];
%y = exp(-2*t) + exp(-1/3*sqrt(t));
%plot(t,y);
%grid on;

%a = [1 2 3 4];
%a(2:3)
%a(2:3) = [20 30];
%a

%a = ones(2,3)
%a = zeros(2,3)
%a = eye(2)
%a = diag([1 2 3])

%a = [1 2 ; 3 4];
%det(a)
%inv(a)
%eig(a)

%a = [1 2 3; 4 5 6; 7 8 9]
%a(1:2, 2:3)
%a(6)

%a = [1 2 ; 3 4];
%a^2
%a.^2

%a = [5 -3 -3; 3 3 -2; 2 -1 2];
%b = [-1; -10; 8];
%x = inv(a) * b
%x = a \ b
%a * x

%disp('ok')

%a = 123;
%disp(['a=' num2str(a)])
%disp(['a=' num2str(a, '%04d')])

%t1=[0:0.1:2*pi];
%y1 = sin(t1);
%t2 = [0:0.6:2*pi];
%y2 = cos(t2);
%plot(t1,y1, t2,y2);
%grid on;

%t=[0:0.1:2*pi];
%y1 = sin(t);
%y2 = cos(t);
%subplot(2,1,1);
%plot(t,y1); grid on;
%title('sin(t)');
%subplot(2,1,2);
%plot(t,y2); grid on;
%title('cos(t)');

t=[0:0.1:2*pi];
y1 = sin(t);
y2 = cos(t);
plot(t,y1,t,y2); grid on;
xlabel('t');
title('sin(t) and cos(t)');
legend('sin(t)', 'cos(t)');
