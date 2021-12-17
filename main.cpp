#include <cmath>
#include <iostream>

struct vec {
    double x, y, p, t;
    vec(double x, double y, double p, double t): x(x), y(y), p(p), t(t){}
    vec operator + (const vec &s) {return vec(x+s.x, y+s.y, p+s.p, t+s.t);}
    vec operator * (double c) {return vec(c*x, c*y, c*p, c*t);}
}




vec f (double a, double b, double c, double d, double e, vec calc) {//функция в диффуре
    vec ret;
    return vec(,,,);
}


vec RKstep (double a, double b, double c, double d, double e, vec start) { //шаг метода Рунге-Кутты
    vec k1, k2, k3, k4;
    const double stepsize = 0.0000001;
    k1 = f(a, b, c, d, e, start);
    k2 = f(a, b, c, d, e, start+k1*(0.5)*stepsize);
    k3 = f(a, b, c, d, e, start+k2*(0.5)*stepsize;
    k4 = f(a, b, c, d, e, start+k3*stepsize);
    return start+(k1+k2*2+k3*2+k4)*(double(1)/double(6))*stepsize;
}

void render (double L, double l, vec position) {

}

int main() {
    double L, l, M, m, a, b, c, d, e;
    cin >> L >> l >> M >> m;
    vector<double> position;
}
