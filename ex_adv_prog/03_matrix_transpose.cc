#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <iomanip>


template <std::size_t dim>
void print_matrix(std::array<double, dim>& M, unsigned int row, unsigned int col){
	for(int i = 0; i<row; i++){
		for(int j = 0; j<col; j++){
			std::cout << std::setw(20) << M[i*col + j];
		}
		std::cout << "\n";
	}
}

template <std::size_t dim>
void initialize(std::array<double, dim>& M, unsigned int row, unsigned int col){
	for(int i = 0; i<row; i++){
		for(int j = 0; j<col; j++){
			M[i*col + j] = i*10 + j;
		}
	}
}

template <std::size_t dim>
std::array<double, dim> transpose(std::array<double, dim>& M, int row, int col){
	std::array<double, dim> trasposta;
	for(int i = 0; i<dim; i++){
		trasposta[i] = 0;
	}
	for(int i = 0; i<col; i++){
		for(int j=0; j<row; j++){
			if(trasposta[j*col+i]==0){
				trasposta[j*col+i] = M[i*col+j];
			}
		}
	}

	return trasposta;
}


int main(int argc, char * argv[]){
	const unsigned int row = 2;
	const unsigned int col = 3;
	const unsigned int dim = row*col;
	std::array<double, dim> M;
	initialize(M, row, col);
	print_matrix(M, row, col);
	std::array<double, dim> trasposta = transpose(M, row, col);
	print_matrix(trasposta, col, row);




	return 0;
}