#include <iostream>
#include <ctime>

void swap(int &first,   int &second);
void swap(int *first_p, int *second_p);

void memcopy(int *data1, int *data2, int data_size);

void allocError();

struct Array {
	public: 
		Array(int size = 0, int is_random = 0) : 
			size(size), 
			capacity(size){
				try {
					this->data = new int[size];
				}
				catch (std::bad_alloc) {
					allocError();
				}
				if (!is_random) return;
				
				for (int i = 0 ; i < size; ++i) {
					this->data[i] = std::rand() % 1000;
				}
		};
//---------------------------------------------------------------------------------------------------------
		Array &operator = (Array &other) {
			if (this == &other) return *this;
			
			this->size     = other.size;
			this->capacity = other.capacity;
			int *new_data  = new int [other.size];
			memcopy(this->data, other.data, other.size);
			delete [] this->data;
			try {
				this->data = new_data;
			}
			catch (std::bad_alloc){
				allocError();
			}
			return *this;
		}
		
		Array &operator = (Array &&other) {
			swap(other.size,	 this->size);
			swap(other.capacity, this->capacity);
			swap(other.data, 	 this->data);

			return *this;
		}
//---------------------------------------------------------------------------------------------------------
		Array(const Array &other) {
			this->size = other.size;
			try {
				this->data = new int [size];
			}
			catch (std::bad_alloc) {
				allocError();
			}
			memcopy(this->data, other.data, other.size);
		}
		
		Array(Array &&other) {
			swap(other.size, 	 this->size);
			swap(other.capacity, this->capacity);
			swap(other.data, 	 this->data);
		}
//---------------------------------------------------------------------------------------------------------
		~Array() {
			delete [] this->data;
			this->data = nullptr;
		}
//---------------------------------------------------------------------------------------------------------
		int getSize() const {
			return this->size;
		}
//---------------------------------------------------------------------------------------------------------
		int *getData() const{
			return this->data;
		}
//---------------------------------------------------------------------------------------------------------
		int getCapacity() const {
			return this->capacity;
		}
//---------------------------------------------------------------------------------------------------------
		void resize(int new_size) {
			int *new_data;
			if (this->capacity >= new_size) {
				this->size = new_size;
				return;
			}
			try {
				new_data = new int [new_size];
			}
			catch (std::bad_alloc) {
				allocError();
			}
			memcopy(new_data, this->data, this->size);
			this->capacity = new_size;
			this->size = new_size;
		}
//---------------------------------------------------------------------------------------------------------
		void print() const{
			for (int i = 0; i < this->size; ++i)
				std::cout << this->data[i] << " " ;
			std::cout << std::endl;
		}

	private:
		int size;
		int capacity;
		int *data;
};

void bubbleSort(Array *array);

void heapSort(Array *array);
void buildMaxHeap(Array *array);
void siftDown(Array *array, int elem);

//----------------------------------------------------------------------------------------------------------
// main start here
//----------------------------------------------------------------------------------------------------------
int main() {
	std::srand(std::time(nullptr));
	
	int n = 0;
	std::cin >> n ;
	
	Array first_arr(n, 1);
	std::cout << first_arr.getSize() << std::endl;
	first_arr.print();
	
	bubbleSort(&first_arr);
	first_arr.print();
	
	std::cout << "---------------------------------" << std::endl;
	
	Array second_arr(n, 1);
	second_arr.print();
	
	heapSort(&second_arr);
	second_arr.print();
	
	std::cout << "---------------------------------" << std::endl;
	
	Array a = Array(8, 1);
		  a = Array(5, 1);
	a.print();
	
	std::cout << "---------------------------------" << std::endl;
	Array b = Array(8, 1);
	
	return 0;
}

//---------------------------------------------------------------------------------------------------------
void swap(int &first, int &second) {
	int temp   = first;
		first  = second;
		second = temp;
}

void swap(int *first_p, int *second_p) {
	int *temp_p  = first_p;
		first_p  = second_p;
		second_p = temp_p;
}
//---------------------------------------------------------------------------------------------------------
void memcopy(int *data1, int *data2, int data_size) {
	for (int i = 0; i < data_size; ++i)
		data1[i] = data2[i];
}
//---------------------------------------------------------------------------------------------------------
void allocError() {
	std::cout << "Unable to allocate memory" << std::endl;
	abort();
}
//---------------------------------------------------------------------------------------------------------
void bubbleSort(Array *array){
	int is_swap = 0;
	for 	(int i = 0; i < array->getSize()        ; ++i) {
		for (int j = 0; j < array->getSize() - 1 - i; ++j)
			if 		(array->getData()[j] > array->getData()[j + 1]) { 
				swap(array->getData()[j] , array->getData()[j + 1]);
				is_swap = 1;
			}
			
		if (!is_swap)
			break;
	}
}
//---------------------------------------------------------------------------------------------------------
void heapSort(Array *array) {
	buildMaxHeap(array);
	for (int i = array->getSize() - 1; i > 0; --i) {
		swap(array->getData()[0], array->getData()[i]);
		
		int temp_size = array->getSize();
		array->resize(i);
		siftDown(array, 0);
		array->resize(temp_size);
	}
}
//---------------------------------------------------------------------------------------------------------
void buildMaxHeap(Array *array) {
	for (int i = array->getSize() / 2 - 1; i >= 0; --i) {
		siftDown(array, i);
	}
}
//---------------------------------------------------------------------------------------------------------
void siftDown(Array *array, int elem) {
	while 	(2 * elem + 2 < array->getSize()) {
		int &left_child   = array->getData()[2 * elem + 1];
		int &right_child  = array->getData()[2 * elem + 2];
		int &current_elem = array->getData()[elem];

		if 			(right_child > left_child) {
			if 		(right_child > current_elem) {
				swap(right_child , current_elem);
				elem = 2 * elem + 2;
			}
			else
				break;
		}
		else {
			if 		(left_child > current_elem) {
				swap(left_child , current_elem);
				elem = 2 * elem + 1;
			}
			else
				break;
		}
	}
	
	if (2 * elem + 1 < array->getSize()) {
		if 		(array->getData()[2 * elem + 1] > array->getData()[elem]) {
			swap(array->getData()[2 * elem + 1] , array->getData()[elem]);
		}
	}
}
//---------------------------------------------------------------------------------------------------------