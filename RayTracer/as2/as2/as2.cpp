#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <time.h>
#include "Matrix.h"
#include "FreeImage.h"
#include "Vector.h"
#include "Point.h"
#include "Ray.h"
#include "Sampler.h"
#include "Shape.h"
#include "Light.h"
#include "Transformation.h"
#include "LocalGeo.h"
#include "GeometricPrimitive.h"
#include "AggregatePrimitive.h"
#include "BRDF.h"
#include "Color.h"
#include "Intersection.h"

using namespace std;

//****************************************************
// Global Variables
//****************************************************
const double PI = 4.0 * atan(1.0);
string fname = "output.png";
int WIDTH = 512;
int HEIGHT = 512;
vector<Point*> vertices = vector<Point*>(0);
vector<Vector*> normals = vector<Vector*>(0);
vector<GeometricPrimitive*> list = vector<GeometricPrimitive*>(0);
vector<Material*> materials = vector<Material*>(0);
vector<Light*> lights = vector<Light*>(0);
Transformation currentTransform = IDENTITY;
Transformation currentInverseTransform = IDENTITY;
BRDF currentBRDF = BRDF(BLACK, BLACK, Color(0.2, 0.2, 0.2), BLACK, 16);
int MAX_DEPTH = 5;

class RayTracer
{
public:
	int depth = 5;
	AggregatePrimitive ag;
	vector<Light*> lights;
	RayTracer();
	RayTracer(AggregatePrimitive &ag, vector<Light*> lights, int depth);
	void trace(Ray &ray, int depth, Color* color);
};

RayTracer::RayTracer(AggregatePrimitive &ag, vector<Light*> lights, int depth)
{
	this->ag = ag;
	this->lights = lights;
	this->depth = depth;
}

void RayTracer::trace(Ray &ray, int depth, Color* color){
	if (depth >= MAX_DEPTH) {
		*color = BLACK;
		return;
	}
	float thit = INFINITY;
	Intersection in;
	if (!ag.intersect(ray, &thit, &in)){
		*color = BLACK;
		return;
	}
	BRDF brdf = BRDF();
	Color ret = BLACK;
	in.primitive->getBRDF(in.localGeo, &brdf);
	for (int i = 0; i < lights.size(); i++){
		Ray lray;
		Color lcolor;
		lights[i]->generateLightRay(in.localGeo, &lray, &lcolor);

		Vector l, n, v, r;

		if (!ag.intersectP(lray)){
			l = lray.d;
			l.normalize();
			n = in.localGeo.normal;
			v = ray.o - in.localGeo.pos;
			v.normalize();
			r = -1 * l + 2 * (l * n) * n;
			r.normalize();
			ret = ret + (lcolor * brdf.kd * max(l * n, 0)) + (lcolor * brdf.ks * (pow(max(r * v, 0), brdf.p)));
		}
		ret = ret + lcolor * brdf.ka;
	}
	if (brdf.kr.r > 0.001 || brdf.kr.g > 0.001 || brdf.kr.b > 0.001){
		Vector l = -1 * ray.d;
		l.normalize();
		Vector n = in.localGeo.normal;
		Ray reflectRay = Ray(in.localGeo.pos, (-1 * l + 2 * (l*n)*n), 0, 0);
		Color tempColor;
		trace(reflectRay, depth + 1, &tempColor);
		ret = ret + brdf.kr * tempColor;
	}
	*color = ret;
}

class Camera
{
public:
	Point pos;
	Vector lookdir;
	Vector up;
	Vector right;
	Vector u;
	Vector v;
	float fov;
	float F_WIDTH;
	float F_HEIGHT;
	Camera();
	Camera(Point lookfrom, Point lookat, Vector up, float fov);
	void generateRay(Sample &sample, Ray *ray);
	void print();
};

Camera::Camera(){

}

Camera::Camera(Point lookfrom, Point lookat, Vector up, float fov){
	this->pos = lookfrom;
	this->fov = fov;
	this->lookdir = lookat - lookfrom;
	this->right = crossProduct(lookdir, up);
	this->up= crossProduct(right, lookdir);
	this->lookdir.normalize();
	this->right.normalize();
	this->up.normalize();
	this->F_WIDTH = WIDTH;
	this->F_HEIGHT = HEIGHT;
	this->u = tan(fov/180 * PI) * right;
	this->v = tan(fov/180 * PI) * up;
}

void Camera::generateRay(Sample &sample, Ray *ray){
	float a = (2 * (sample.x - WIDTH/2 + 0.5) - 1) / F_HEIGHT;
	float b = (2 * (sample.y - HEIGHT/2 + 0.5) - 1) / F_HEIGHT;
	Point p = Point(a * u.x + b * v.x, a * u.y + b * v.y, a * u.z + b * v.z);
	*ray = Ray(pos, p - pos, 0, INFINITY);
}

void Camera::print(){
	cout << "Camera pos: ";
	pos.print();
}

Camera camera;

void loadObj(std::string file) {
	//store variables and set stuff at the end
	Triangle nt = Triangle(Point(0, 0, 0), Point(0, 0, 0), Point(0, 0, 0));
	float x, y, z;
	int va, vb, vc;
	int na, nb, nc;
	string s1, s2, s3;
	std::ifstream inpfile(file);
	if (!inpfile.is_open()) {
		std::cout << "Unable to open file" << std::endl;
	}
	else {
		std::string line;
		while (inpfile.good()) {
			std::vector<std::string> splitline;
			std::string buf;

			std::getline(inpfile, line);
			std::stringstream ss(line);

			while (ss >> buf) {
				splitline.push_back(buf);
			}
			//Ignore blank lines
			if (splitline.size() == 0) {
				continue;
			}

			//Ignore comments
			if (splitline[0][0] == '#') {
				continue;
			}

			//Valid commands:
			//size width height
			//  must be first command of file, controls image size
			else if (!splitline[0].compare("v")) {
				x = atof(splitline[1].c_str()) / 20.0;
				y = atof(splitline[2].c_str()) / 20.0;
				z = atof(splitline[3].c_str()) / 20.0;
				vertices.push_back(new Point(x, y, z));
			}

			else if (!splitline[0].compare("vn")) {
				x = atof(splitline[1].c_str());
				y = atof(splitline[2].c_str());
				z = atof(splitline[3].c_str());
				normals.push_back(new Vector(x, y, z));
			}

			else if (!splitline[0].compare("f")){
				s1 = splitline[1].c_str();
				s2 = splitline[2].c_str();
				s3 = splitline[3].c_str();

				va = atoi(s1.substr(0, s1.find_first_of('/')).c_str()) - 1;
				na = atoi(s1.substr(s1.find_last_of('/') + 1).c_str()) - 1;
				vb = atoi(s2.substr(0, s2.find_first_of('/')).c_str()) - 1;
				nb = atoi(s2.substr(s2.find_last_of('/') + 1).c_str()) - 1;
				vc = atoi(s3.substr(0, s3.find_first_of('/')).c_str()) - 1;
				nc = atoi(s3.substr(s3.find_last_of('/') + 1).c_str()) - 1;
				list.push_back(new GeometricPrimitive(IDENTITY, IDENTITY, new SmoothTriangle(*(vertices[va]), *(vertices[vb]), *(vertices[vc]), *(normals[na]), *(normals[nb]), *(normals[nc])), new Material(currentBRDF)));
			}
			else // command or startofline not recognized, so just ignore
				continue;
		}
		inpfile.close();
	}
}

void loadScene(std::string file) {

	//store variables and set stuff at the end
	int width, height;
	float x, y, z, r, g, b;

	std::ifstream inpfile(file.c_str());
	if (!inpfile.is_open()) {
		std::cout << "Unable to open file" << std::endl;
	}
	else {
		std::string line;
		//MatrixStack mst;

		while (inpfile.good()) {
			std::vector<std::string> splitline;
			std::string buf;

			std::getline(inpfile, line);
			std::stringstream ss(line);

			while (ss >> buf) {
				splitline.push_back(buf);
			}
			//Ignore blank lines
			if (splitline.size() == 0) {
				continue;
			}

			//Ignore comments
			if (splitline[0][0] == '#') {
				continue;
			}

			//Valid commands:
			//size width height
			//  must be first command of file, controls image size
			else if (!splitline[0].compare("size")) {
				WIDTH = atoi(splitline[1].c_str());
				HEIGHT = atoi(splitline[2].c_str());
			}
			//maxdepth depth
			//  max # of bounces for ray (default 5)
			else if (!splitline[0].compare("maxdepth")) {
				MAX_DEPTH = atoi(splitline[1].c_str());
			}
			//output filename
			//  output file to write image to 
			else if (!splitline[0].compare("output")) {
				fname = splitline[1];
			}

			//camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
			//  speciﬁes the camera in the standard way, as in homework 2.
			else if (!splitline[0].compare("camera")) {
				camera = Camera(Point(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str())),
								Point(atof(splitline[4].c_str()), atof(splitline[5].c_str()), atof(splitline[6].c_str())), 
								Vector(atof(splitline[7].c_str()), atof(splitline[8].c_str()), atof(splitline[9].c_str())), 
								atof(splitline[10].c_str()));
			}

			//sphere x y z radius
			//  Deﬁnes a sphere with a given position and radius.
			else if (!splitline[0].compare("sphere")) {
				x = atof(splitline[1].c_str());
				y = atof(splitline[2].c_str()); 
				z = atof(splitline[3].c_str());
				r = atof(splitline[4].c_str());
				Sphere *s = new Sphere(Point(x, y, z), r);
				list.push_back(new GeometricPrimitive(currentTransform, currentInverseTransform, s, new Material(currentBRDF)));
				// Create new sphere:
				//   Store 4 numbers
				//   Store current property values
				//   Store current top of matrix stack
			}
			
			//vertex x y z
			//  Deﬁnes a vertex at the given location.
			//  The vertex is put into a pile, starting to be numbered at 0.
			else if (!splitline[0].compare("vertex")) {
				vertices.push_back(new Point(atof(splitline[1].c_str())/2.0, atof(splitline[2].c_str())/2.0, atof(splitline[3].c_str())/2.0));
				// x: atof(splitline[1].c_str()),
				// y: atof(splitline[2].c_str()),
				// z: atof(splitline[3].c_str()));
			}
		
			//tri v1 v2 v3
			//  Create a triangle out of the vertices involved (which have previously been speciﬁed with
			//  the vertex command). The vertices are assumed to be speciﬁed in counter-clockwise order. Your code
			//  should internally compute a face normal for this triangle.
			else if (!splitline[0].compare("tri")) {
				Point v1 = *vertices[atoi(splitline[1].c_str())];
				Point v2 = *vertices[atoi(splitline[2].c_str())];
				Point v3 = *vertices[atoi(splitline[3].c_str())];
				Triangle *tri = new Triangle(v1, v2, v3);
				list.push_back(new GeometricPrimitive(currentTransform, currentInverseTransform, tri, new Material(currentBRDF)));
			}
			//translate x y z
			//  A translation 3-vector
			else if (!splitline[0].compare("translate")) {
				x = atof(splitline[1].c_str());
				y = atof(splitline[2].c_str());
				z = atof(splitline[3].c_str());
				Transformation t = Transformation();
				t.translation(x, y, z);
				Transformation tinv = Transformation();
				tinv.translation(-x, -y, z);
				currentTransform = t * currentTransform;
				currentInverseTransform = currentInverseTransform * tinv;
			}
			//rotate x y z angle
			//  Rotate by angle (in degrees) about the given axis as in OpenGL.
			else if (!splitline[0].compare("rotate")) {
				x = atof(splitline[1].c_str());
				y = atof(splitline[2].c_str());
				z = atof(splitline[3].c_str());
				float angle = atof(splitline[4].c_str());
				Transformation t = Transformation();
				t.rotation(x, y, z, angle);
				Transformation tinv = Transformation();
				tinv.rotation(x, y, z, -angle);
				currentTransform = t * currentTransform;
				currentInverseTransform = currentInverseTransform * tinv;
			}
			//scale x y z
			//  Scale by the corresponding amount in each axis (a non-uniform scaling).
			else if (!splitline[0].compare("scale")) {
				x = atof(splitline[1].c_str());
				y = atof(splitline[2].c_str());
				z = atof(splitline[3].c_str());
				Transformation t = Transformation();
				t.scale(x, y, z);
				Transformation tinv = Transformation();
				tinv.scale(1.0/x, 1.0/y, 1.0/z);
				currentTransform = t * currentTransform;
				currentInverseTransform = currentInverseTransform * tinv;
			}
			// resetTransform
			// reverts the current transform to the identity matrix
			else if (!splitline[0].compare("resetTransform")) {
				currentTransform = Transformation();
				currentInverseTransform = Transformation();
			}

			//directional x y z r g b
			//  The direction to the light source, and the color, as in OpenGL.
			else if (!splitline[0].compare("directional")) {
				x = atof(splitline[1].c_str());
				y = atof(splitline[2].c_str());
				z = atof(splitline[3].c_str());
				r = atof(splitline[4].c_str());
				g = atof(splitline[5].c_str());
				b = atof(splitline[6].c_str());
				lights.push_back(new Light(0, x, y, z, r, g, b));
			}
			//point x y z r g b
			//  The location of a point source and the color, as in OpenGL.
			else if (!splitline[0].compare("point")) {
				x = atof(splitline[1].c_str());
				y = atof(splitline[2].c_str());
				z = atof(splitline[3].c_str());
				r = atof(splitline[4].c_str());
				g = atof(splitline[5].c_str());
				b = atof(splitline[6].c_str());
				lights.push_back(new Light(1, x, y, z, r, g, b));
			}
			else if (!splitline[0].compare("ambient")) {
				r = atof(splitline[1].c_str());
				g = atof(splitline[2].c_str());
				b = atof(splitline[3].c_str());
				currentBRDF.ka = Color(r, g, b);
			}

			//diﬀuse r g b
			//  speciﬁes the diﬀuse color of the surface.
			else if (!splitline[0].compare("diffuse")) {
				r = atof(splitline[1].c_str());
				g = atof(splitline[2].c_str());
				b = atof(splitline[3].c_str());
				currentBRDF.kd = Color(r, g, b);
			}
			//specular r g b 
			//  speciﬁes the specular color of the surface.
			else if (!splitline[0].compare("specular")) {
				r = atof(splitline[1].c_str());
				g = atof(splitline[2].c_str());
				b = atof(splitline[3].c_str());
				currentBRDF.ks = Color(r, g, b);
			}
			//shininess s
			//  speciﬁes the shininess of the surface.
			else if (!splitline[0].compare("shininess")) {
				currentBRDF.p = atof(splitline[1].c_str());
			
			}
			// reflect r g b
			// gives the reflective color of the surface.
			else if (!splitline[0].compare("reflect")) {
				r = atof(splitline[1].c_str());
				g = atof(splitline[2].c_str());
				b = atof(splitline[3].c_str());
				currentBRDF.kr = Color(r, g, b);
			}
			else if (!splitline[0].compare("object")) {
				loadObj(splitline[1].c_str());
			}
			else {
				std::cerr << "Unknown command: " << splitline[0] << std::endl;
			}
		}

		inpfile.close();
	}

}


int main(int argc, char *argv[]){
	if (argc == 2){
		loadScene(argv[1]);
		FreeImage_Initialise();
		FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, 24);
		RGBQUAD color;
		Sampler sampler = Sampler(WIDTH, HEIGHT);
		Sample sample;
		sample.x = -1;
		sample.y = 0;
		Ray ray;
		RayTracer raytracer = RayTracer(AggregatePrimitive(list), lights, MAX_DEPTH);
		Color shading = BLACK;
		currentBRDF.ka.print();
		cout << lights.size() << "\n";
		for (int i = 0; i < lights.size(); i++){
			lights[i]->print();
		}
		camera.print();
		while (sampler.generateSample(&sample)){
			camera.generateRay(sample, &ray);
			raytracer.trace(ray, 0, &shading);
			color.rgbRed = min(shading.r * 255, 255);
			color.rgbGreen = min(shading.g * 255, 255);
			color.rgbBlue = min(shading.b * 255, 255);
			FreeImage_SetPixelColor(bitmap, sample.x, sample.y, &color);
		}
		FreeImage_Save(FIF_PNG, bitmap, fname.c_str(), 0);
		/*
		RGBQUAD color;
		Camera cam = Camera(Point(0, 0, 3), Point(0, 0, 0), Vector(0, 1, 0), 60);
		Sphere sphere = Sphere(Point(-0.7, -0.5, 0), 0.6);
		Sphere sphere2 = Sphere(Point(0.7, -0.5, 0), 0.6);
		Sphere sphere3 = Sphere(Point(0.0, 0.7, 0), 0.6);
		Color diff = Color(1, 1, 1);
		BRDF brdftest = BRDF(Color(0.0, 0.6, 0.0), Color(0.8, 0.8, 0.8), Color(0.1, 0.1, 0.1), Color(0.5, 0.5, 0.5), 16);
		BRDF brdftest2 = BRDF(Color(0.6, 0.0, 0.0), Color(0.8, 0.8, 0.8), Color(0.1, 0.1, 0.1), Color(0.5, 0.5, 0.5), 16);
		BRDF brdftest3 = BRDF(Color(0.0, 0.0, 0.6), Color(0.8, 0.8, 0.8), Color(0.1, 0.1, 0.1), Color(0.5, 0.5, 0.5), 16);
		Sampler sampler = Sampler(WIDTH, HEIGHT);
		list.push_back(new GeometricPrimitive(IDENTITY, IDENTITY, &sphere, new Material(brdftest)));
		list.push_back(new GeometricPrimitive(IDENTITY, IDENTITY, &sphere2, new Material(brdftest2)));
		list.push_back(new GeometricPrimitive(IDENTITY, IDENTITY, &sphere3, new Material(brdftest3)));
		lights.push_back(new Light(0, 0, 0, -1, 1, 1, 1));
		AggregatePrimitive ag = AggregatePrimitive(list);
		Ray ray;
		Color shading;
		RayTracer raytracer = RayTracer(ag, lights, 5);
		Sample sample;
		sample.x = -1;
		sample.y = 0;
		while (sampler.generateSample(&sample)){
		cam.generateRay(sample, &ray);
		raytracer.trace(ray, 0, &shading);
		color.rgbRed = min(shading.r * 255, 255);
		color.rgbGreen = min(shading.g * 255, 255);
		color.rgbBlue = min(shading.b * 255, 255);
		FreeImage_SetPixelColor(bitmap, sample.x, sample.y, &color);
		}
		*/
		return 0;
	}
}

