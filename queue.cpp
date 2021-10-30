//queue implementation

#include <iostream>

template <class T>
class Queue{
	private:
		T* queue;
		int space;
		int rear;
		int front;
	public:
		Queue(int QCapacity=10);
		T get_front() const;
		bool is_empty() const;
		void push(T item);
		void pop();

};




template <class T>
Queue<T>::Queue(int Qcapacity):space(Qcapacity+1){
	queue=new T [space];
	rear=-1;
	front=-1;
}




template <class T>
inline T Queue<T>::get_front() const{
	if(is_empty()){
		throw "queue is empty!";
	}
	return queue[(front+1)%space];

}


template <class T>
inline bool Queue<T>::is_empty() const{
	return rear==front;
}



template <class T>
void Queue<T>::push(const T item){
	if((rear+1)%space==front){
		throw "queue is full!";
	}
	rear=(rear+1)%space;
	queue[rear]=item;
}


template <class T>
void Queue<T>::pop(){	
	if(is_empty()){
		throw "queue is empty!";
	}	
	front=(front+1)%space;
	queue[front].~T();

}




int main(){
	Queue <int> q = Queue<int>(5);
	q.push(10);
	q.push(21);
	std::cout<<q.get_front()<<"\n";
	q.push(45);
	std::cout<<q.get_front()<<"\n";
	q.push(21);
	std::cout<<q.get_front()<<"\n";	
	std::cout<<q.is_empty()<<"\n";
	q.pop();
	q.pop();	
	std::cout<<q.get_front()<<"\n";
	q.pop();
	q.pop();
	std::cout<<q.is_empty()<<"\n";
	try{
		q.pop();
	}catch(const char* e){
		std::cout<<e;
	}
	return 0;
}








