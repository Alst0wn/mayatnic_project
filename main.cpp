vector<double> f (double a, double b, double c, double d, double e, vector<double> calc) {//функция в диффуре
    vector<double> ret;
    ret.push_back()
    return ret
}


vector<double> RKstep (double a, double b, double c, double d, double e, vector<double> start) { //шаг метода Рунге-Кутты
    vector<double> k1, k2, k3, k4;
    const double stepsize = 0.0000001;
    k1 = f(a, b, c, d, e, start);
    k2 = f(a, b, c, d, e, start+stepsize*k1/2);
    k3 = f(a, b, c, d, e, start+stepsize*k2/2);
    k4 = f(a, b, c, d, e, start+stepsize*k3);
    return start+stepsize*(k1+2*k2+2*k3+k4)/6;
}

void render (double L, double l, vector<double> position) {

}

int main() {
 cin >> L >> l >> M >> m;
}
