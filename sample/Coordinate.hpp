#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <cmath>
#include <functional>
#include <fstream>
#include <iterator>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>
#include <random>

#include "../CSC.h"
#include "../CSR.h"
#include "../IO.h"

using namespace std;

template <class VALUETYPE>
class Coordinate{
	public:
		VALUETYPE x, y;
		Coordinate(){
			this->x = 0;
			this->y = 0;
		}
		Coordinate(VALUETYPE x, VALUETYPE y){
			this->x = x;
			this->y = y;
		}
		Coordinate(VALUETYPE x, VALUETYPE y, int i){
                        this->x = x;
                        this->y = y;
                }
		VALUETYPE getX() const{
			return this->x;
		}
		VALUETYPE getY() const{
			return this->y;
		}
		void setX(VALUETYPE x){
			this->x = x;
		}
		void setY(VALUETYPE y){
			this->y = y;
		}
		VALUETYPE getMagnitude(){
			return (VALUETYPE)sqrt(this->x * this->x + this->y * this->y);
		}
		VALUETYPE getMagnitude2(){
			return (VALUETYPE)(this->x * this->x + this->y * this->y);
		}
		VALUETYPE getDistance(Coordinate A){
			return (VALUETYPE)sqrt((this->x - A.x)*(this->x - A.x) + (this->y - A.y)*(this->y - A.y));
		}
		Coordinate getUnitVector(){
			return Coordinate(this->x / getMagnitude(), this->y / getMagnitude());
		}
                Coordinate getProjection(Coordinate A, Coordinate B){
			VALUETYPE a1 = A.y - B.y;
			VALUETYPE b1 = B.x - A.x;
			VALUETYPE c1 = B.x * A.y - A.x * B.y;
			VALUETYPE a2 = B.x - A.x;
			VALUETYPE b2 = B.y - A.y;
			VALUETYPE c2 = b2 * this->y + a2 * this->x;
			VALUETYPE det = - a1 * a1 - b1 * b1;
			VALUETYPE nom1 = b2 * c1 - b1 * c2;
			VALUETYPE nom2 = a1 * c2 - a2 * c1;
			VALUETYPE distAB = A.getDistance(B);
			VALUETYPE distA = this->getDistance(A);
			VALUETYPE distB = this->getDistance(B);
			if(distA < distAB){
				return Coordinate( nom1 / det, nom2 / det);
			}else{
				if(distA < distB){
					return A;
				}else{
					return B;
				}
			}
		}
		Coordinate operator*(VALUETYPE v){
			return Coordinate(this->x * v, this->y * v);
		}
		Coordinate operator/(VALUETYPE v){
			return Coordinate(this->x / v, this->y / v);
		}
		Coordinate operator+(Coordinate A){
			return Coordinate(this->x + A.x, this->y + A.y);
		}
		Coordinate operator+(VALUETYPE v){
			return Coordinate(this->x + v, this->y + v);
		}
		Coordinate operator-(Coordinate A){
			return Coordinate(this->x - A.x, this->y - A.y);
		}
		void operator+=(Coordinate A){
			this->x += A.x;
			this->y += A.y;
		}
};
template<class VALUETYPE>
VALUETYPE get_random(VALUETYPE lowerbound, VALUETYPE upperbound){
        return lowerbound + (upperbound-lowerbound) * (random()*1.0) / (RAND_MAX);
}

template<class VALUETYPE>
VALUETYPE get_fixed_random(VALUETYPE lowerbound, VALUETYPE upperbound){
        return lowerbound + (VALUETYPE)fmod(rand(), (upperbound - lowerbound + 1));
}
#endif
