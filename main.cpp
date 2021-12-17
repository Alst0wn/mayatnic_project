#include <iostream>
#include "SDL.h"
#include <cmath>
#include <vector>
#define pi acos(-1)

using namespace std;

const int WIDTH = 800, HEIGHT = 600, TPS=60;
double SCALE = 120, g = -9.81;

class vec {
public:
    double x, y, p, t;
    vec(double x, double y, double p, double t): x(x), y(y), p(p), t(t){}
    vec(): x(0), y(0), p(0), t(0){}
    vec operator + (const vec &s) {return vec(x+s.x, y+s.y, p+s.p, t+s.t);}
    vec operator * (double c) {return vec(c*x, c*y, c*p, c*t);}
    vec operator= (const vec &s) {
        x = s.x;
        y=s.y;
        p = s.p;
        t=s.t;
        return *this;
    }
};

vec f (double a, double b, double c, double d, double e, vec v) {//функция в диффуре
    return vec((e*sin(v.t)-2*b*sin(v.t-v.p)*(cos(v.t-v.p)*b/2/a*v.x*v.x+v.y*v.y)-b*d/2/a*sin(v.p)*cos(v.t-v.p))/(2*c-b*b*cos(v.t-v.p)*cos(v.t-v.p)/2/a), (d*sin(v.p)+2*b*sin(v.t-v.p)*(cos(v.t-v.p)*b/2/c*v.y*v.y+v.x*v.x)-b*e/2/c*sin(v.t)*cos(v.t-v.p))/(2*a-b*b*cos(v.t-v.p)*cos(v.t-v.p)/2/c), v.y, v.x);
}

vec RKstep (double a, double b, double c, double d, double e, vec start) { //шаг метода Рунге-Кутты
    vec k1, k2, k3, k4;
    const double stepsize = 0.0005;
    k1 = f(a, b, c, d, e, start);
    k2 = f(a, b, c, d, e, start+k1*(0.5)*stepsize);
    k3 = f(a, b, c, d, e, start+k2*(0.5)*stepsize);
    k4 = f(a, b, c, d, e, start+k3*stepsize);
    return start+(k1+k2*2+k3*2+k4)*(double(1)/double(6))*stepsize;
}

void drawMaya(SDL_Renderer* renderer, vec data, int xpos, int ypos, double L, double l, double SCALE) {
    SDL_RenderDrawLine(renderer, xpos, ypos, xpos+L*SCALE*sin(data.p), ypos+L*SCALE*cos(data.p));
    SDL_RenderDrawLine(renderer, xpos+L*SCALE*sin(data.p), ypos+L*SCALE*cos(data.p), xpos+L*SCALE*sin(data.p)+l*SCALE*sin(data.t), ypos+L*SCALE*cos(data.p)+l*SCALE*cos(data.t));
}

class CApp {
private:
	bool Running;
	SDL_Surface* surface;
	SDL_Window* window;
	SDL_Renderer* renderer;
	vec data;
	double L, l, M, m, a, b, c, d, e;
public:
	CApp(double L, double l, double M, double m): L(L), l(l), M(M), m(m) {
		Running = true;
		window = NULL;
		renderer = NULL;
		data = vec();
		a = M*L*L/6+m*L*L/2;
        b = m*l*L/4;
        c = m*l*l/6;
        d = (M/2+m)*g*L;
        e = m*g*l/2;
	}

	void setData(vec d) {
        data = d;
	}

    bool OnInit()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Mayatnic", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        // Check that the window was successfully created
        if (window == NULL) {
            // In the case that the window could not be made...
            std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
            return false;
        }
        return true;
    }

    void OnEvent(SDL_Event* Event) {
        if (Event->type == SDL_QUIT) Running = false;
    }

    void OnLoop() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 148, 0, 29, SDL_ALPHA_OPAQUE);
        drawMaya(renderer, data, WIDTH/2, HEIGHT/2, L, l, SCALE);
        for (int i=1; i<10; i++) {
        data = RKstep(a,b,c,d,e,data);};
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/TPS);
    }

    void OnCleanup() {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    int OnExecute() {
		if(OnInit() == false) return -1;
		SDL_Event Event;
        while(Running) {
            while(SDL_PollEvent(&Event)) {
                OnEvent(&Event);
            }
            OnLoop();
        }
		OnCleanup();
		return 0;
	}
};

int main(int argv, char** args) {
    double L, l, M, m;
    const double g = 9.81;
    L=1; l=1; m=1; M=1;
    CApp a(L, l, M, m);
    a.setData(vec(0, 0, -pi/2, -pi/3));
    a.OnExecute();
    return 0;
}
