//
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +                                                                      +
// + This file is part of enGrid.                                         +
// +                                                                      +
// + Copyright 2008,2009 Oliver Gloth                                     +
// +                                                                      +
// + enGrid is free software: you can redistribute it and/or modify       +
// + it under the terms of the GNU General Public License as published by +
// + the Free Software Foundation, either version 3 of the License, or    +
// + (at your option) any later version.                                  +
// +                                                                      +
// + enGrid is distributed in the hope that it will be useful,            +
// + but WITHOUT ANY WARRANTY; without even the implied warranty of       +
// + MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        +
// + GNU General Public License for more details.                         +
// +                                                                      +
// + You should have received a copy of the GNU General Public License    +
// + along with enGrid. If not, see <http://www.gnu.org/licenses/>.       +
// +                                                                      +
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
#ifndef geometrytools_H
#define geometrytools_H

#include "math/mathvector.h"
#include "math/smallsquarematrix.h"

#include <vtkUnstructuredGrid.h>

namespace GeometryTools
{

/** Converts radians to degrees */
double rad2deg( double rad );

/** Converts degrees to radians */
double deg2rad( double deg );

void rotate(vec3_t g1, vec3_t g2, vec3_t g3, vec3_t &b, double theta);

/** Rotates vector v around vector axis by an angle theta */
vec3_t rotate(vec3_t v, vec3_t axis, double theta);

vec3_t orthogonalVector(vec3_t v);

double intersection(vec3_t x_straight, vec3_t v_straight, 
                    vec3_t x_plane, vec3_t n_plane);

double intersection(vec3_t x_straight, vec3_t v_straight, 
                    vec3_t x_plane, vec3_t u_plane, vec3_t v_plane);

bool intersection (double &k1, double &k2, vec2_t r1, vec2_t u1, vec2_t r2, vec2_t u2);

void sliceTriangle(const vector<vec3_t> &Tin, vec3_t x, vec3_t n, vector<vector<vec3_t> > &Tout);

double tetraVol(vec3_t x1, vec3_t x2, vec3_t x3, vec3_t x4, bool neg = false);

double pyraVol(vec3_t x1, vec3_t x2, vec3_t x3, vec3_t x4, vec3_t x5, bool neg = false);

double prismVol(vec3_t x1, vec3_t x2, vec3_t x3, vec3_t x4, vec3_t x5, vec3_t x6, bool neg = false);

double hexaVol(vec3_t x1, vec3_t x2, vec3_t x3, vec3_t x4, vec3_t x5, vec3_t x6, vec3_t x7, vec3_t x8,  bool neg = false);

double triArea(vec3_t x1, vec3_t x2, vec3_t x3);

double quadArea(vec3_t x1, vec3_t x2, vec3_t x3, vec3_t x4);

vec3_t triNormal(vec3_t x1, vec3_t x2, vec3_t x3);

vec3_t quadNormal(vec3_t x1, vec3_t x2, vec3_t x3, vec3_t x4);

vec3_t triNormal(vtkUnstructuredGrid *grid, vtkIdType p1, vtkIdType p2, vtkIdType p3);

vec3_t quadNormal(vtkUnstructuredGrid *grid, vtkIdType p1, vtkIdType p2, vtkIdType p3, vtkIdType p4);

vec3_t cellNormal(vtkUnstructuredGrid *grid, vtkIdType i);

double cellVA(vtkUnstructuredGrid *grid, vtkIdType cellId, bool neg = false);
  
inline vec2_t turnRight(const vec2_t &v)
{
  vec2_t u;
  u[0] =  v[1];
  u[1] = -v[0];
  return u;
};

inline vec2_t turnLeft(const vec2_t &v)
{
  vec2_t u;
  u[0] = -v[1];
  u[1] =  v[0];
  return u;
};

//polygon must be numbered clockwise
inline bool IsConvex(vec3_t a,vec3_t b,vec3_t c,vec3_t d)
{
  vec3_t u[4];
  u[0]=b-a;
  u[1]=c-b;
  u[2]=d-c;
  u[3]=a-d;
  
  for(int i=0;i<4;i++) {
    vec3_t n=u[i].cross(u[(i+1)%4]);
    if(n[2]>0) return(false);
  }
  return(true);
};

inline bool IsConvex(vec2_t a_2D,vec2_t b_2D,vec2_t c_2D,vec2_t d_2D)
{
  vec3_t a_3D(a_2D[0],a_2D[1]);
  vec3_t b_3D(b_2D[0],b_2D[1]);
  vec3_t c_3D(c_2D[0],c_2D[1]);
  vec3_t d_3D(d_2D[0],d_2D[1]);
  return(IsConvex(a_3D,b_3D,c_3D,d_3D));
};

/** return the angle w.r.t. another 3-vector */
double angle(const vec3_t & u, const vec3_t & v);

/** return the deviation p1->p2->p3 (angle(p2-p1,p3-p2)) */
double deviation(vtkUnstructuredGrid *grid, vtkIdType p1, vtkIdType p2, vtkIdType p3);

/** return the angle p1,p2,p3 (angle(p1-p2,p3-p2)) */
double angle(vtkUnstructuredGrid *grid, vtkIdType p1, vtkIdType p2, vtkIdType p3);

};

#endif