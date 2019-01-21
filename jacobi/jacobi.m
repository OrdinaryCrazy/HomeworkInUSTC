A = [3,2,5,4,6;
    2,1,3,-7,8;
    5,3,2,5,-4;
    4,-7,5,1,3;
    6,8,-4,3,8];
%********************************************
Maxtimes = 100;
n = 5;
e = 1e-7;
V = diag(diag(ones(n)));
for i = 1:Maxtimes
    Nodiag = abs(A) - diag(diag(A));
    Max = max(reshape(Nodiag,numel(A),1));
    [p,q] = find(Nodiag == Max);
    if A(p(1),q(1)) ~= 0
        s = (A(q(1),q(1)) - A(p(1),p(1)))/(2 * A(p(1),q(1)));
        if s >= 0
            t = 1 / (s + sqrt(1 + s^2));
        else
            t = 1 / (s - sqrt(1 + s^2));
        end
        c = 1/sqrt(1 + t^2);
        d = t * c;
    else
        c = 1;
        d = 0;
    end
    Q = diag(diag(ones(n)));
    Q(p(1),p(1)) = c;
    Q(q(1),q(1)) = c;
    Q(p(1),q(1)) = d;
    Q(q(1),p(1)) = -d;
    A = Q' * A * Q;
    V = V * Q;
    if norm(A - diag(diag(A)),2) < e
        break;
    end
end
diag_A = diag(A);
for i = 1:n
    fprintf("r%d = %f\t, v1( ",i,diag_A(i));
    for j = 1:n - 1
        fprintf("%f ,",V(i,j));
    end
    fprintf("%f )\n",V(i,j));
end