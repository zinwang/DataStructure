//array implemetation with array
#include <iostream>
using namespace std;






template <class T>
class stack{
	private:
		T *stk;
		int top;
		int capacity;
	public:
		stack(int stk_capacity=10);
		T  get_top() const;
		bool  is_empty() const;
		void push(T item);
		void pop();


};


template <class T>
stack<T>::stack(int stk_capacity):capacity(stk_capacity){
	stk=new T[stk_capacity];
	top=-1;

}

template <class T>
inline T stack<T>::get_top() const{
	if(is_empty()){
		throw "stack is empty";
	}

	return stk[top];
}


template <class T>
inline bool stack<T>::is_empty() const{
	return top==-1;
}

template <class T>
void stack<T>::push(T item){
	if(top==capacity-1){
		throw "stack overflows!";
	}
	stk[++top]=item;

}

template <class T>
void stack<T>::pop(){
	if(top==-1){	
		throw "stack is empty";
		return;
	}
	stk[top--].~T();
}




int main(){
	
	stack <int> a= stack <int> (20);
	a.push(1);
	a.push(7);
	cout<<a.get_top()<<"\n";
	a.pop();
	a.pop();
	cout<<a.is_empty()<<"\n";
	try{
		a.pop();
	}catch(const char* e){
		cout<<e<<"\n";
	}




	return 0;
}

