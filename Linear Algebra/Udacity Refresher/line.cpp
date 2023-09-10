//header files
#include "vector.h"

//represents a 2d line of the form ax + by = k
class TwoDLine{
    public:
        double a, b, k;
        

        TwoDLine(double a, double b, double k): a(a), b(b), k(k){
        }

        Vector get_direc_vec(){
            double direc_vec[2]{b, -a};
            return Vector(direc_vec, 2);
        }

        Vector get_normal_vec(){
            double normal_vec[2]{a, b};
            return Vector(normal_vec, 2);
        }

        Vector get_point_with_x(double x){
            double point[2]{x, (k-a*x)/b};
            return Vector(point, 2);
        }

        Vector get_point_with_y(double y){
            double point[2]{((k-b*y)/a), y};
            return Vector(point, 2);
        }

        bool is_parallel(TwoDLine& other){
            Vector this_direc_vec = get_direc_vec();
            Vector other_normal_vec = other.get_normal_vec();
            if (other_normal_vec.dot(this_direc_vec) != 0){
                return false;
            }

            Vector this_point = get_point_with_x(0);
            Vector other_point = other.get_point_with_x(0);
            Vector diff_vec = this_point - other_point;
            
            cout << diff_vec.toString() << endl;
            cout << other_normal_vec.toString() << endl;

            if (diff_vec.dot(other_normal_vec) == 0){
                return false;
            }
            else{
                return true;
            }
        }

        bool is_equal(TwoDLine& other){
            Vector this_direc_vec = get_direc_vec();
            Vector other_normal_vec = other.get_normal_vec();
            if (other_normal_vec.dot(this_direc_vec) != 0){
                return false;
            }

            Vector this_point = get_point_with_x(0);
            Vector other_point = other.get_point_with_x(0);
            Vector diff_vec = this_point - other_point;
            
            cout << diff_vec.toString() << endl;
            cout << other_normal_vec.toString() << endl;

            if (diff_vec.dot(other_normal_vec) == 0){
                return true;
            }
            else{
                return false;
            }
        }

        Vector get_intersection(TwoDLine& other){
            if (is_parallel(other)){
                throw runtime_error("the given lines are parallel, intersection doesn't exist.");
            }
            if (is_equal(other)){
                throw runtime_error("the given lines are parallel, the lines intersect at infinite points.");
            }
            double x = (other.b*k-b*other.k)/(a*other.b-b*other.a);
            return get_point_with_x(x);
        }

};

int main(){
    TwoDLine first_line = TwoDLine(1., -11., 1.);
    TwoDLine sec_line = TwoDLine(-3., -3., -3.);

    cout << first_line.get_intersection(sec_line).toString() << endl;
}
