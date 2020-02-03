#ifndef __find_if_harcoded // we do this check to avoid double definition of the same macro (possible if we import in the same file different libraries that import this library)
#define __find_if_harcoded


//requires I is Iterator
//*I is of type T
//Here i return and Iterator (sort of a pointer)
//it makes sense to return a pointer when I search for something; do it!

template <typename I, typename T>
I find_if_hardcoded(I first, const I last, const T& value){ 
	// precondition [first, last)
		// we can't verify this!! (For example if the iterators are two pointers from a linked list)
		// So this is left to the user
	while(first != last && *first != value){
		++first;
	}
	return first;
}

//we want to generalize the algorithm
//here you can pass a function or even a class with an operator(T) and returns a bool
template <typename I, typename P>
	//I find_if_template(I first, const I last, bool (*func)(const T&) )
//P has operator(T) and returns a bool
I find_if_template(I first, const I last, P predicate){ //a function that returns a boolean is called a predicate
	// precondition [first, last)
		// we can't verify this!! (For example if the iterators are two pointers from a linked list)
		// So this is left to the user
	while(first != last && !predicate(*first)){
		++first;
	}
	return first;
}

template <typename T>
struct predicate_base{
	//overloading of the () operator
	virtual bool operator()(const T&) const =0; // ==> so this is an abstract class!! I can't predict what will it be
};


//I find_if_template(I first, const I last, bool (*func)(const T&) )
//requires I is an Iterator
//*I is compatible with predicate
template <typename I, typename T>
I find_if_virtual(I first, const I last, const predicate_base<T>& predicate){ //in this way we can accept prediate_base or one of his children (polymorphism)
		//we are going to define after predicate_base
		//a function that returns a boolean is called a predicate
	// precondition [first, last)
		// we can't verify this!! (For example if the iterators are two pointers from a linked list)
		// So this is left to the user
	while(first != last && !predicate(*first)){
		++first;
	}
	return first;
}



#endif