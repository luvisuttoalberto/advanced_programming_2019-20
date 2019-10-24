#include <iostream>

void populate_primes(int * array, std::size_t size){
	unsigned int j;
	unsigned int x = 2;
	unsigned int i = 0;
	while(i<size){
		j = 2;
		while(x%j!=0){
			j++;
		}
		if(x==j){
			array[i] = x;
			i++;
		}
		x++;
	}

}

int main(){
	std::size_t cont = 0;
	unsigned int j;
	unsigned int x = 2;
	unsigned int N;
	std::cout << "Insert max number: ";
	std::cin >> N;

	while(x<=N){
		j = 2;
		while(x%j!=0){
			j++;
		}
		if(x==j){
			cont++;
		}
		x++;
	}

	int primes[cont];


	populate_primes(primes, cont);
	for(std::size_t i = 0; i<cont; i++){
		std::cout << primes[i] << std::endl;
	}
	





	return 0;
}