CC = g++
CFLAGS = -c
LDFLAGS = -L./ -lfreeimage

default: as2

Light.o: Light.cpp Light.h
	${CC} ${CFLAGS} -c -g Light.cpp

Matrix.o: Matrix.cpp Matrix.h
	${CC} ${CFLAGS} -c -g Matrix.cpp

GeometricPrimitive.o: GeometricPrimitive.cpp GeometricPrimitive.h
	${CC} ${CFLAGS} -c -g GeometricPrimitive.cpp
	
Point.o: Point.cpp Point.h
	${CC} ${CFLAGS} -c -g Point.cpp

Ray.o: Ray.cpp Ray.h
	${CC} ${CFLAGS} -c -g Ray.cpp
	
Sampler.o: Sampler.cpp Sampler.h
	${CC} ${CFLAGS} -c -g Sampler.cpp

Shape.o: Shape.cpp Shape.h
	${CC} ${CFLAGS} -c -g Shape.cpp
	
Vector.o: Vector.cpp Vector.h
	${CC} ${CFLAGS} -c -g Vector.cpp

Transformation.o: Transformation.cpp Transformation.h
	${CC} ${CFLAGS} -c -g Transformation.cpp

LocalGeo.o: LocalGeo.cpp LocalGeo.h
	${CC} ${CFLAGS} -c -g LocalGeo.cpp

Camera.o: Camera.cpp Camera.h
	${CC} ${CFLAGS} -c -g Camera.cpp

Color.o: Color.cpp Color.h
	${CC} ${CFLAGS} -c -g Color.cpp

BRDF.o: BRDF.cpp BRDF.h
	${CC} ${CFLAGS} -c -g BRDF.cpp

AggregatePrimitive.o: AggregatePrimitive.cpp AggregatePrimitive.h
	${CC} ${CFLAGS} -c -g AggregatePrimitive.cpp

LocalGeo.o: LocalGeo.cpp LocalGeo.h
	${CC} ${CFLAGS} -c -g LocalGeo.cpp

Intersection.o: Intersection.cpp Intersection.h
	${CC} ${CFLAGS} -c -g Intersection.cpp

RayTracer.o: RayTracer.cpp RayTracer.h
	${CC} ${CFLAGS} -c -g RayTracer.cpp

Material.o: Material.cpp Material.h
	${CC} ${CFLAGS} -c -g Material.cpp




as2.o : as2.cpp Light.h Matrix.o GeometricPrimitive.h Point.h Ray.h Sampler.o Shape.h Vector.h Point.h Transformation.h LocalGeo.h Color.h BRDF.h AggregatePrimitive.h Intersection.h RayTracer.h Material.h 
	${CC} ${CFLAGS} -c -g as2.cpp

as2: as2.o Light.o Matrix.o GeometricPrimitive.o Point.o Ray.o Sampler.o Shape.o Vector.o Point.o Transformation.o LocalGeo.o Camera.o Color.o BRDF.o AggregatePrimitive.o Intersection.o RayTracer.o Material.o
	${CC} ${CFLAGS} -g as2.o Light.o Matrix.o GeometricPrimitive.o Point.o Ray.o Sampler.o Shape.o Vector.o Point.o Transformation.o LocalGeo.o Camera.o Color.o BRDF.o AggregatePrimitive.o Intersection.o RayTracer.o Material.o$(LDFLAGS) -o as2

clean: 
	rm -rf *.o *~ as2