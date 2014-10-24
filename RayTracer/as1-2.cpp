// as2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <typeinfo>

#include <time.h>
#include <math.h>
#include "FreeImage.h"

#define WIDTH 512
#define HEIGHT 512
#define BPP 24

inline float sqr(float x) { return x*x; }

using namespace std;

class Light{
public:
	string type; // point or directional
	vector<float> position; // x y z coordinates
	vector<float> color; // r g b values
	vector<float> normalized_position;
	Light(string type, float x, float y, float z, float r, float g, float b){
		this->type = type;
		position.at(0) = x;
		position.at(1) = y;
		position.at(2) = z;
		color.at(0) = r;
		color.at(1) = g;
		color.at(2) = b;
	}
};

vector<float> add(vector<float> a, vector<float> b){
	int n = a.size();
	vector<float> result(n);
	for (int i = 0; i < n; i++){
		result[i] = (a[i] + b[i]);
	}
	return result;
}

vector<float> subtract(vector<float> a, vector<float> b){
	int n = a.size();
	vector<float> result(n);
	for (int i = 0; i < n; i++){
		result[i] = (a[i] - b[i]);
	}
	return result;
}
// Assumes vectors are the same size
float dot_product(vector<float> a, vector<float> b){
	int n = a.size();
	float total = 0.0;
	for (int i = 0; i < n; i++){
		total += (a[i] * b[i]);
	}
	return total;
}

// Assumes vectors are the same size
vector<float> normalize(vector<float> v){
	int n = v.size();
	float total = 0.0;
	vector<float> result(n);
	for (int i = 0; i < n; i++){
		total += pow(v[i], 2);
	}
	total = sqrt(total);
	for (int i = 0; i < n; i++){
		result[i] = v[i] / total;
	}
	return result;
}

vector<float> reflection(vector<float> l, vector<float> n)
{
	float x = 2 * dot_product(l, n);
	int s = l.size();
	vector<float> result(s);
	for (int i = 0; i < s; i++)
	{
		result[i] = x*n[i] - l[i];
	}
	return result;
}

float ambience[3];
float diffuse[3];
float specular[3];
float p;
bool kd = false;
bool ks = false;
bool ka = false;
Light *lights[10];
int num_lights = 0;

void draw_circle(){
	float radius = 512.0 / 2.2;
	FreeImage_Initialise();

	FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
	RGBQUAD color;

	if (!bitmap)
		exit(1);

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++){
			float x = (i + 0.5 - WIDTH);
			float y = (j + 0.5 - HEIGHT);

			float dist = sqrt(sqr(x) + sqr(y));

			if (dist <= radius){
				float z = sqrt(radius*radius - dist*dist);

				float r = 0.0;
				float g = 0.0;
				float b = 0.0;

				vector<float> n;
				n.at(0) = x;
				n.at(1) = y;
				n.at(2) = z;
				n = normalize(n);
				vector<float> v;
				v.at(0) = 0;
				v.at(1) = 0;
				v.at(2) = 1;
 
				for (int k = 0; k < num_lights; k++){

					vector<float> l;
					if (lights[k]->type == "point"){
						l = normalize(subtract(lights[k]->position, n));
					}
					else { // light must be directional 
						l = lights[k]->normalized_position;
					}

					vector<float> reflect = reflection(l, n);


					//////////// DIFFUSE ////////////////
					if (kd)
					{
						float max_diffuse_comp = fmax(dot_product(l, n), 0.0);
						r += diffuse[0] * lights[k]->color[0] * max_diffuse_comp;
						g += diffuse[1] * lights[k]->color[1] * max_diffuse_comp;
						b += diffuse[2] * lights[k]->color[2] * max_diffuse_comp;

					}

					//////////// SPECULAR //////////////
					if (ks)
					{
						float max_spec_comp = pow(fmax(dot_product(reflect, v), 0.0), p);
						r += specular[0] * lights[k]->color[0] * max_spec_comp;
						g += specular[1] * lights[k]->color[1] * max_spec_comp;
						b += specular[2] * lights[k]->color[2] * max_spec_comp;
					}

					////////// AMBIENT ///////////
					if (ka)
					{
						r += ambience[0] * lights[k]->color[0];
						g += ambience[1] * lights[k]->color[1];
						b += ambience[2] * lights[k]->color[2];
					}
				}
				color.rgbRed = r * 255.0;
				color.rgbGreen = g * 255.0;
				color.rgbBlue = b * 255.0;
				FreeImage_SetPixelColor(bitmap, i, j, &color);
			}
		}
	}
	color.rgbRed = 255;
	color.rgbGreen = 255;
	color.rgbBlue = 255;

	FreeImage_SetPixelColor(bitmap, 10, 400, &color);

	if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
		cout << "Image_successfully_saved!" << endl;

	FreeImage_DeInitialise();

}

int main(int argc, char* argv[])
{
	int i = 1;
	while (i < argc) {
		string flag = string(argv[i]);
		if (flag == "-ka"){
			ambience[0] = atof(argv[i + 1]);
			ambience[1] = atof(argv[i + 2]);
			ambience[2] = atof(argv[i + 3]);
			i += 4;
			ka = true;
		}
		else if (flag == "-kd"){
			diffuse[0] = atof(argv[i + 1]);
			diffuse[1] = atof(argv[i + 2]);
			diffuse[2] = atof(argv[i + 3]);
			i += 4;
			kd = true;
		}
		else if (flag == "-ks"){
			specular[0] = atof(argv[i + 1]);
			specular[1] = atof(argv[i + 2]);
			specular[2] = atof(argv[i + 3]);
			i += 4;
			ks = true;
		}
		else if (flag == "-sp"){
			p = atof(argv[i + 1]);
			i += 2;
		}
		else if (flag == "-pl"){
			float x, y, z, r, g, b;
			x = atof(argv[i + 1]);
			y = atof(argv[i + 2]);
			z = atof(argv[i + 3]);
			r = atof(argv[i + 4]);
			g = atof(argv[i + 5]);
			b = atof(argv[i + 6]);
			lights[num_lights] = new Light("point", x, y, z, r, g, b);
			num_lights++;
			i += 7;
		}
		else if (flag == "-dl"){
			float x, y, z, r, g, b;
			x = -1 * atof(argv[i + 1]);
			y = -1 * atof(argv[i + 2]);
			z = -1 * atof(argv[i + 3]);
			r = atof(argv[i + 4]);
			g = atof(argv[i + 5]);
			b = atof(argv[i + 6]);
			lights[num_lights] = new Light("directional", x, y, z, r, g, b);
			num_lights++;
			i += 7;
		}
		for (int i = 0; i < num_lights; i++){
			lights[i]->normalized_position = normalize(lights[i]->position);
		}

	}

	draw_circle();
	return 0;
}
