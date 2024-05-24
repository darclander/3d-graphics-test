#include "Window.hpp"
#include <numeric>
#include <vector>

struct vec3 {
	float x;
	float y;
	float z;
};

struct connection {
	int a;
	int b;
};
void rotate(vec3 &point, float x = 1, float y = 1, float z = 1) {
	https://en.wikipedia.org/wiki/Rotation_matrix
    float rad = 0;
    float newX, newY, newZ;

    // Rotation around X axis
    rad = x;
    newY = std::cos(rad) * point.y - std::sin(rad) * point.z;
    newZ = std::sin(rad) * point.y + std::cos(rad) * point.z;
    point.y = newY;
    point.z = newZ;

    // Rotation around Y axis
    rad = y;
    newX = std::cos(rad) * point.x + std::sin(rad) * point.z;
    newZ = -std::sin(rad) * point.x + std::cos(rad) * point.z;
    point.x = newX;
    point.z = newZ;

    // Rotation around Z axis
    rad = z;
    newX = std::cos(rad) * point.x - std::sin(rad) * point.y;
    newY = std::sin(rad) * point.x + std::cos(rad) * point.y;
    point.x = newX;
    point.y = newY;
}


void rotateB(vec3 &point, float x = 1, float y = 1, float z = 1) {
	float rad = 0;


	// https://en.wikipedia.org/wiki/Rotation_matrix
	rad = x;
	point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
	point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

	rad = y;
	point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
	point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;
	
	rad = z;
	point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
	point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;
}

void line(Window &window, float x1, float y1, float x2, float y2) {
	float dx = x2 - x1;
	float dy = y2 - y1;

	float d = std::sqrt(dx * dx + dy * dy);
	float angle = std::atan2(dy, dx);

	for(float i = 0; i < d; i++) {
		window.pixel(x1 + std::cos(angle) * i,
					 y1 + std::sin(angle) * i);
	}
}


int main(int argc, char **argv) {

	Window window = Window();

	std::vector<vec3> points = {
		{100, 100, 100},
		{200, 100, 100},
		{200, 200, 100},
		{100, 200, 100},

		{100, 100, 200},
		{200, 100, 200},
		{200, 200, 200},
		{100, 200, 200}
	};

	std::vector<connection> connections = {
		{0, 4},
		{1, 5},
		{2, 6},
		{3, 7},

		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0},

		{4, 5},
		{5, 6},
		{6, 7},
		{7, 4},	
	};

	// Centeroid
	vec3 c;
	for(auto &p : points) {
		c.x += p.x;
		c.y += p.y;
		c.z += p.z;
	}

	c.x /= points.size();
	c.y /= points.size();
	c.z /= points.size();

	while(true) {
		for (auto &p : points) {
			p.x -= c.x;
			p.y -= c.y;
			p.z -= c.z;
			rotate(p, 0.001f, 0.003f, 0.004f);
			p.x += c.x;
			p.y += c.y;
			p.z += c.z;
			window.pixel(p.x, p.y);
		}
		for (auto &conn : connections) {
			line(window, points[conn.a].x,
						 points[conn.a].y,
						 points[conn.b].x,
						 points[conn.b].y);
		}

		window.render();
		window.clear();
		window.update();
		SDL_Delay(30);
	}

	return 0;
}
