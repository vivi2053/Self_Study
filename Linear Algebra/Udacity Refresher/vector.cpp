//c standard libraries
#include <math.h>

//cpp standard libraries
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

//header files
#include "vector.h"

//macros
#define ll long long
using namespace std;


class Vector{

    public:
        vector<double>  coordinates;
        int dim;
        Vector(vector<double> coords){
            if (coords.size()==0){
                throw runtime_error("The coordinates must be non empty");
            }
            for(int i=0;i<coords.size();i++){
                coordinates.push_back(coords[i]);
            }
            dim = coordinates.size();
        }

        Vector(double coords[], unsigned int size){
            if (size == 0){
                throw runtime_error("The coordinates must be non empty");
            }

            for(int i=0;i<size;i++){
                coordinates.push_back(coords[i]);
            }
            dim = coordinates.size();
        }

        string toString() {
            string repr = "Vector: (";
            for (int i=0;i<dim-1;i++){
                repr += to_string(coordinates[i]);
                repr += ", ";
            }
            repr += to_string(coordinates[dim-1]);
            repr += ")";
            return repr;
        }

        double norm() const{
            double norm = 0;
            for(auto it : this->coordinates){
                norm += (it*it);
            }
            return sqrt(norm);
        }

        double dot(const Vector& other) const{
            check_dim_eq(other);
            double result = 0;
            for(int i=0; i!=this->dim;i++){
                result += this->coordinates[i] * other.coordinates[i];
            }
            return result;
        }

        // Vector cross(const Vector& other) const{
        //     if (this->dim != 3 || other->dim != 3){
        //         throw exception
        //     }
        // }
        double angleBetween(const Vector& other) const{
            check_dim_eq(other);
            double a_norm = norm();
            double b_norm = other.norm();
            double dot_prod = this->dot(other);
            double intermed = dot_prod/(a_norm*b_norm);
            intermed = min(max(-1.0, intermed), 1.0);
            intermed = acos(intermed);
            return intermed;

        }

        bool isParallel(const Vector& other) const{
            check_dim_eq(other);
            double angle = angleBetween(other);
            return (angle < 0.000001 || (M_PI - angle) < 0.000001);
        }

        bool isOrthogonal(const Vector& other) const{
            check_dim_eq(other);
            double angle = angleBetween(other);
            double error_threshold = (M_PI/2)-angle;
            return (error_threshold > -0.000001 && error_threshold < 0.000001);
        }

        tuple<Vector, Vector> getProjections(const Vector& other) const {
            double b_norm = other.norm();
            if (b_norm == 0){
                throw runtime_error("cannot project to a null vector");
            }
            
            double rev_norm = 1/b_norm;
            
            Vector unit_b = other * rev_norm;
            double parallel_norm = dot(unit_b);
            Vector parallel = unit_b * parallel_norm;
            Vector orthogonal = (*this) - parallel;
            return {parallel, orthogonal};
            
        }

        bool operator==(const Vector& other) const {
            if (this->dim != other.dim) {return false;}
            for(int i=0;i<dim;i++){
                if (this->coordinates[i] != other.coordinates[i]){
                    return false;
                }
            }
            return true;
        }

        Vector operator+(const Vector& other) const{
            check_dim_eq(other);
            vector<double> add_vec;
            for(long i=0;i<this->dim;i++){
                add_vec.push_back(this->coordinates[i] + other.coordinates[i]);
            }
            return Vector(add_vec);
        }

        Vector operator-(const Vector& other) const{
            check_dim_eq(other);
            vector<double> add_vec;
            for(int i=0;i<this->dim;i++){
                add_vec.push_back(this->coordinates[i] - other.coordinates[i]);
            }
            return Vector(add_vec);
        }

        Vector operator*(double scalar) const{
            vector<double> add_vec;
            for(int i=0;i<this->dim;i++){
                add_vec.push_back(this->coordinates[i] * scalar);
            }
            return Vector(add_vec);
        }

        Vector operator*(int scalar) const{
            vector<double> add_vec;
            for(int i=0;i<this->dim;i++){
                add_vec.push_back(this->coordinates[i] * (double)scalar);
            }
            return Vector(add_vec);
        }

    private:
        void check_dim_eq(const Vector& other) const{
            if (this->dim != other.dim) {
                throw runtime_error("cannot perform operation since the dimensions are different");
            }
        }
};

// Scalar multiplication with doubles and int
Vector operator*(Vector& vec, const int scalar){
    vector<double> add_vec;
    for(int i=0;i<vec.dim;i++){
        add_vec.push_back(vec.coordinates[i] * scalar);
    }
    return Vector(add_vec);
}

Vector operator*(const int scalar, Vector& vec){
    vector<double> add_vec;
    for(int i=0;i<vec.dim;i++){
        add_vec.push_back(vec.coordinates[i] * scalar);
    }
    return Vector(add_vec);
}

Vector operator*(Vector& vec, const double scalar){
    vector<double> add_vec;
    for(int i=0;i<vec.dim;i++){
        add_vec.push_back(vec.coordinates[i] * scalar);
    }
    return Vector(add_vec);
}

Vector operator*(const double scalar, Vector& vec){
    vector<double> add_vec;
    for(int i=0;i<vec.dim;i++){
        add_vec.push_back(vec.coordinates[i] * scalar);
    }
    return Vector(add_vec);
}


//represents a 3d vector, this class is defined to support cross product since cross product is only defined for 3d vectors
class ThreeDVector: public Vector{
    public:
        vector<double>  coordinates;
        int dim;
        ThreeDVector(vector<double> coords): Vector(coords){
            if (coords.size()!=3){
                throw runtime_error("This vector must have 3 dimensions");
            }

            for(int i=0;i<coords.size();i++){
                coordinates.push_back(coords[i]);
            }

            dim = coordinates.size();
        }

        ThreeDVector(double coords[], unsigned int size): Vector(coords, size){
            if (size == 0){
                throw runtime_error("This vector must have 3 dimensions");
            }

            for(int i=0;i<size;i++){
                coordinates.push_back(coords[i]);
            }
            dim = coordinates.size();
        }

        ThreeDVector cross(ThreeDVector& other){
            vector<double> cp_vec;
            vector<double> vec1 = coordinates;
            vector<double> vec2 = other.coordinates;

            cp_vec.push_back((vec1[1]*vec2[2]) - (vec2[1]*vec1[2]));
            cp_vec.push_back((vec1[2]*vec2[0]) - (vec2[2]*vec1[0]));
            cp_vec.push_back((vec1[0]*vec2[1]) - (vec2[0]*vec1[1]));
            return ThreeDVector(cp_vec);
        }

};
