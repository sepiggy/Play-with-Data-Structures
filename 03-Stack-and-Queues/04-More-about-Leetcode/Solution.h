//
// Created by hpf on 18-5-8.
//

#include <string>

class Solution {
public:
    bool isValid(std::string s) {
        ArrayStack<char> *stack = new ArrayStack<char>();
        for (int i = 0; i < s.size(); ++i) {
            char c = s.at(i);
            if (c == '(' || c == '[' || c == '{') {
                stack->push(c);
            } else {
                if (stack->isEmpty()) {
                    return false;
                }
                char topChar = stack->pop();
                if (c == ')' && topChar != '(') {
                    return false;
                }
                if (c == ']' && topChar != '[') {
                    return false;
                }
                if (c == '}' && topChar != '{') {
                    return false;
                }
            }
        }
        return stack->isEmpty();
    }
private:
	template<class T>
    class Stack {
    public:
    	int getSize();

    	bool isEmpty();

    	void push(T e);

    	T pop();

    	T peek();
	};
	
    template<class T>
	class Array {
	private:
		T *data;
		int size;
		int capacity;

		void resize(int newCapacity){
		    T *newData = new T[newCapacity];
		    for (int i = 0; i < size; ++i) {
		        newData[i] = data[i];
		    }
		    data = newData;
		    capacity = newCapacity;
		}

	public:
		class Full {
		};

		class Range {
		};

		Array(int capacity) {
		    data = new T[capacity];
		    size = 0;
		    this->capacity = capacity;
		}

		Array() {
		    data = new T[5];
		    size = 0;
		    capacity = 5;
		}

		int getCapacity() {
		    return capacity;
		}

		int getSize() {
		    return size;
		}

		bool isEmpty() {
		    return size == 0;
		}

		void add(int index, T e) {
		    if (index < 0 || index > size) {
		        throw Range();
		    }
		    if (size == capacity) {
		        resize(2 * capacity);
		    }
		    for (int i = size - 1; i >= index; --i) {
		        data[i + 1] = data[i];
		    }
		    data[index] = e;
		    size++;
		}

		void addFirst(T e) {
		    add(0, e);
		}

		void addLast(T e) {
		    add(size, e);
		}

		T get(int index) {
		    if (index < 0 || index >= size) {
		        throw Range();
		    }
		    return data[index];
		}

		void set(int index, T e) {
		    if (index < 0 || index >= size) {
		        throw Range();
		    }
		    data[index] = e;
		}

		bool contains(T e) {
		    for (int i = 0; i < size; ++i) {
		        if (data[i] == e) {
		            return true;
		        }
		    }
		    return false;
		}

		int find(T e) {
		    for (int i = 0; i < size; ++i) {
		        if (data[i] == e) {
		            return i;
		        }
		    }
		    return -1;
		}

		T remove(int index) {
		    if (index < 0 || index >= size) {
		        throw Range();
		    }
		    T ret = data[index];
		    for (int i = index + 1; i < size; ++i) {
		        data[i - 1] = data[i];
		    }
		    size--;
		    if (size == capacity / 4 && capacity / 2 != 0){
		        resize(capacity / 2);
		    }
		    return ret;
		}

		T removeFirst() {
		    return remove(0);
		}

		T removeLast() {
		    return remove(size - 1);
		}

		void removeElement(T e) {
		    int index = find(e);
		    if (index != -1) {
		        remove(index);
		    }
		}

		/**
		 * 打印数组的所有元素
		 */
		void print() {
		    std::cout << "Array: size = " << size << ", capacity = " << getCapacity() << std::endl;
		    toPrint();
		}

		void toPrint() {
		    std::cout << "[";
		    for (int i = 0; i < size; ++i) {
		        std::cout << data[i];
		        if (i != size - 1) {
		            std::cout << ", ";
		        }
		    }
		    std::cout << "]";
		}
	};
    
	template<class T>
	class ArrayStack : public Stack<T> {
	public:
    	ArrayStack(int capacity) {
        	array = new Array<T>(capacity);
    	}

    	ArrayStack() {
    		array = new Array<T>();
    	}

    	~ArrayStack() {
        	delete[] array;
        	array = nullptr;
    	}

    	int getSize() {
        	return array->getSize();
    	}

    	T pop() {
        	return array->removeLast();
    	}

    	T peek() {
        	return array->getLast();
    	}

    	void push(T e) {
        	array->addLast(e);
    	}

    	bool isEmpty() {
        	return array->isEmpty();
    	}

    	/**
     	* 打印数组的所有元素
     	*/
    	void print() {
        	std::cout << "Stack: size = " << array->getSize() << ", capacity = " << array->getCapacity() << std::endl;
        	std::cout << "bottom ";
        	array->toPrint();
        	std::cout << " top" << std::endl;
    	}

	private:
    	Array<T> *array;
	};
	
	
};
