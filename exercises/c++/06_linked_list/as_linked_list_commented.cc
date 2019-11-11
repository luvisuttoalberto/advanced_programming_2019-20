#include <iostream>
#include <memory>
#include "ap_error.h"

enum class method {push_back, push_front}

template <class T>
class List{
	struct node{ //here we can read all the data of the nesting class
		//why a nested struct? the user doesn't need to know the details: for example the implementation of a node
		//so we put this in the private part of the list
		std::unique_ptr<node> next;
		T value;
		node(const T& v, node * p):  next{p}, value{v} {} //here it's indifferent to put before value or next; the values do not depends on each other. But the compiler gives a warning if we swap them, it could cause an error, so better to do it like this
		node(T&& v, node * p): next{p}, value{std::move(v)} {}
		node(const std::unique_ptr<node>& p): value{p->value}{
			if(p->next){
				next = std::make_unique<node>(p->next);
			}
		}
	};

	std::unique_ptr<node> head;

	void push_back(const T& v);
	void push_back(T&& v);

	void push_front(const T& v){
		//all this could be done in one line
		/*
		auto h = head.release();
		auto new_node = new node{v,h};
		head.reset(new_node);
		*/

		//head.reset(new node{v, head.release()}); // this is pre c++14

		head = std::make_unique<node>(v, head.release());//this since c++14




	}
	void push_front(T&& v);

	node * tail(){//notice that this function will cause segmentation fault if we call it with an empty head
		//but there is no problem because we call this function only after controlling if there is already a head or not
		auto tmp = head.get();
		while(tmp->next){
			tmp = tmp->next.get();
		}
		return tmp;
	}

public:
	//with or without the l is the same here
	List() noexcept = default; // default constructor
	List(List&& l) noexcept = default; // one feature of the move semantic is that they don't throw exceptions
	List& operator=(List&& l) noexcept = default; 

	List(const List& l);
	List& operator=(const List& l);//it would be a mistake to put noexcept here in the copy semantic: in general, noexcept is put in move semantic, not in copy semanti

	void insert(const T& v, const method m); // here you are going to call the copy semantic
	void insert(T&& v, const method m);  // here you are going to call the move semantic

	//friend std::ostream& operator<<(std::ostream&, const List&);//our function is templated so this is not good
	//so we do the following
	template <class O>
	friend std::ostream& operator<<(std::ostream&, const List<O>&);//this function has a template down there so we need a template here too
	//andyou can't use the T because it would get in conflict with before used template
};

template <class T>
void List<T>::insert(const T& v, const method m){
	if(head == nullptr){ // or simply (!head)
		//head.reset(new node{v,nullptr});
		head = std::make_unique<node>(v, nullptr); //the difference here is that the = will be the move assignment; it will call a new and pass this values: it will be shown next lesson
		return;
	}
	switch(m){
	case method::push_back:
		push_back(v);
		break;

	case method::push_front:
		push_front(v);
		break;
	default:
		AP_ERROR(false) << "Unknown insertion method";
		break;
	};

}

template <class T>
void List<T>::push_back(const T& v){
	node * last = tail();
	//last -> next.reset(new node{v, nullptr});
	last->next = std::make_unique<node>(v, nullptr);//c++ 14 style, but won't compile. Why? We will see when we compile. Thanks to the dick (Edo questa è per te)
}


template<class T>
std::ostream& operator<< (std::ostream& os, const List<T>& l){
	//I enter this while loop only if I have at least one node, otherwise the following returns nullptr
	auto tmp = l.head.get();
	while(tmp){//equal to while(tmp!=nullptr)
		os << tmp->value << " " ;
		tmp = tmp->next.get();
	}
	return os;
}

template <class T>
List<T>::List(const List& l){
	/*
	auto tmp = l.head.get();
	while(tmp){
		insert(tmp->value, method::push_back)
		tmp = tmp->next.get();
	}
	*/ 
	// or
	head = std::make_unique<node>(l.head);
}




int main(){

	try{
		List<int> l{};
		l.insert(4,method::push_back);
		l.insert(5,method::push_back);
		l.insert(3,method::push_front);
		std::cout << l << std::endl;

		auto ol = l;

		l.insert(14,method::push_front);
		
		std::cout << l << std::endl;
		std::cout << ol << std::endl;


	}catch(std::exception& e){
		std::cerr<<e.what() << std::endl;
	}catch(...){
		std::cerr<<"Unknown exception" << std::endl;
	}



	return 0;
}