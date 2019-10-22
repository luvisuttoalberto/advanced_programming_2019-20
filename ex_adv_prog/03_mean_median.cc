#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void print_vector(const std::vector<T>& v, const std::string& s) {
  std::cout << s << ": ";
  for (const auto& x : v)
    std::cout << x << " ";
  std::cout << std::endl;
}

double mean(std::vector<double> v){
	double mean;
	double sum = 0;
	for(auto i = 0u; i< v.size(); i++){
		sum += v.at(i);
	}
	mean = sum/v.size();
	return mean;
}

double median(std::vector<double>& v){
	double median;
	std::sort(v.begin(), v.end());
	print_vector(v, "Il vettore ordinato è ");
	if(v.size()%2 == 0){
		int pos1 = v.size()/2;
		int pos2 = v.size()/2 + 1;
		std::cout << "Numero pari" << std::endl;
		std::cout 	<< "Le posizioni sono " << pos1 
					<< " e " << pos2 << std::endl;
		std::cout 	<< "I valori sono " << v.at(pos1) << " e "
					<< v.at(pos2) << std::endl;
		median = (v.at(pos1)+v.at(pos2))/2;
	}
	else{
		std::cout << "Numero dispari" << std::endl;
		int pos = (v.size()+1)/2;
		std::cout << "La posizione è " << pos << std::endl;
		median = v.at(pos);
	}
	return median;
}

void init(std::vector<double>& v){
	double x;
	while((std::cin >> x)){
		v.push_back(x);
	}
}

int main(int argc, char * argv[]){
	std::vector<double> temperatures;
	init(temperatures);
	print_vector(temperatures, "The vector is");
	double mean_t = mean(temperatures);
	std::cout << "the mean is " << mean_t << std::endl;
	double median_t = median(temperatures);
	std::cout << "the median is " << median_t << std::endl;
	return 0;
}