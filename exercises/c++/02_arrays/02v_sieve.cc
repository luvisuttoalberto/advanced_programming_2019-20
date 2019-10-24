#include <iostream>
#include <vector>

int main(){
	std::vector<int> primes;
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
			primes.push_back(x);
		}
		x++;
	}

	for(int i = 0; i<primes.size(); i++){
		std::cout << primes.at(i) << std::endl;
	}



	return 0;
}