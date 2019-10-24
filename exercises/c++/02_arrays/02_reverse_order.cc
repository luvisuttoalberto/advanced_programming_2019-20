#include <iostream>

template <typename T>
T * init(std::size_t n){
	T * array = new T[n];
	unsigned int i = 0;
	std::cout << "Inserisci gli elementi dell'array: \n";
	while((i<n) && (std::cin >> array[i])){
		i++;
	}
	return array;
}

template <typename T>
void print_array(T * array, std::size_t size_array){
	for(int i = size_array-1; i>=0; i--){
		std::cout << array[i] << std::endl;
	}
}




int main(){

	std::cout << "Inserisci la lunghezza dell'array di int: ";
	std::size_t size_pippo;
	std::cin >> size_pippo;
	int * pippo = init<int>(size_pippo);
	print_array(pippo, size_pippo);
	
	std::cout << "Inserisci la lunghezza dell'array di float: ";
	std::size_t size_pippo_float;
	std::cin >> size_pippo_float;
	float * pippo_float = init<float>(size_pippo_float);
	print_array(pippo_float, size_pippo_float);
	
	delete[] pippo;
	delete[] pippo_float;
	return 0;
}