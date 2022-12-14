# include <iostream>
using namespace std;

#include <ctime>

//Eigen core
#include <Eigen/Core>
//Algebraic operations of dense matrices (inverse, eigenvalues, etc)
#include <Eigen/Dense>
using namespace Eigen;

#define MATRIX_SIZE 50

// Program demonstrates the use of the basic Eigen type
int main(int argc , char **argv){
    // All vector and matrices in Eigen are Eigen::Matrix, 
    // Its first 3 parameters are: data type, row, collum. 
    // Example Declare a 2*3 float matrix
    Matrix<float, 2, 3> matrix_23;
    // 3D vector the same with matrix 3x1
    Vector3d v_3d;
    // This is the same
    Matrix<float , 3, 1> vd_3d;

    // Define 3x3 zeros matrix
    Matrix3d matrix_33 = Matrix3d::Zero();
    
    // If you are not sure about the size of the matrix, 
    // you can use the dynamic size
    Matrix<double, Dynamic, Dynamic> matrix_dynamic;
    //Simpler way
    MatrixXd matrix_x;

    //---------Operation of the Matrix -----------
    //Input data
    matrix_23 << 1, 2, 3, 4, 5, 6;
    //Output
    cout << "matrix 2x3 from 1 to 6: \n" << matrix_23 << endl;
    // Use () to access elements in the matrix
    cout << "print matrix 2x3: " << endl;
    for(int i=0; i <2; i++){
        for(int j=0; j<3; j++)
        cout << matrix_23(i,j) << "\t";
        cout << endl;
    }
    
    // Multiply a matrix with a vector (actually still matrices and matrices)
    v_3d << 3, 2, 1;
    vd_3d << 4, 5, 6;
    // In Eigen you can't mix two diffirent types of matrices, like this
    // wrong Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d;
    // it should be explicitly converted
    Matrix<double, 2, 1> result = matrix_23.cast<double>() *v_3d;
    cout << "Multiply matrix [1, 2, 3; 4, 5, 6]*[3, 2, 1]=" << result.transpose() << endl;
    // define the float size of the matrix 2x1
    Matrix<float, 2, 1> result2 = matrix_23*vd_3d;
    cout << "Multiply matrix [1, 2, 3; 4, 5, 6]*[4, 5, 6]=" << result2.transpose() << endl;

    //--- Matrix operation
    matrix_33 << 1, 2, 3, 4, 5, 6, 7, 8, 9; //random number of matrix
    cout << "random matrix: \n" << matrix_33 << endl;
    cout << "transpose: \n" << matrix_33.transpose() << endl;
    cout << "sum: " << matrix_33.sum() << endl;
    cout << "trace: " << matrix_33.trace() << endl;
    cout << "times 10: \n" << 10 * matrix_33 << endl;
    cout << "inverse: \n" << matrix_33.inverse() << endl;
    cout << "det: " << matrix_33.determinant() << endl;
    
    // Eigen Values
    // Real sysmetric matrix can guarantee successful diagonalization 
    SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_33.transpose()*matrix_33);
    cout << "Eigen values = \n" << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << endl;
    // the Matrix 3x3:A, Eigen vectors: X, and Eigen value E  equation:
    // A*X = E*X
    
    // Solving the equations
    // The basic equation A*x = B with matrix_NN *x = v_Nd
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = 
                        MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    matrix_NN = matrix_NN*matrix_NN.transpose(); // Guarantee semi-positive definite
    Matrix<double, MATRIX_SIZE, 1> v_Nd = MatrixXd::Random(MATRIX_SIZE, 1);

    // Start timming
    clock_t time_stt = clock();
    // Method 1:  Direct inversion  
    Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse()*v_Nd;
    cout << "time of normal inverse is "  << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;

    // Method 2: QR decomposition 
    time_stt = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time of QR decomposition is "  << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;
    
    // Method 3: Cholesky Decomposition
    time_stt = clock();
    x = matrix_NN.ldlt().solve(v_Nd);
    cout << "time of Cholesky Decomposition is "  << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;

    return 0; 
    }
