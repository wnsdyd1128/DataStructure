#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#define endl '\n'
#define _CRT_SECURE_NO_DEPRECATE
using namespace std;

template<typename T>
class List_Node {
	T data;
	List_Node<T>* next;
public:
	List_Node() : data(NULL), next(nullptr) {}
	List_Node(T _data) : data(_data), next(nullptr) {}
	T getData() {
		return data;
	}
	List_Node<T>* getNext() {
		return next;
	}
	void setData(T data) {
		this->data = data;
	}
	void setNext(List_Node<T>* next) {
		this->next = next;
	}
};

template<typename T>
class Linked_List {
	size_t size;
	List_Node<T>* head;
public:
	Linked_List() : size(0), head(nullptr) {}
	size_t getSize() {
		return size;
	}
	bool isEmpty() { // 비어있으면 true 반환
		return size ? false : true;
	}
	void insert(T d) {
		List_Node<T>* node = new List_Node<T>(d);
		if (isEmpty()) { // 비어있을 때
			head = node;
			size++;
			return;
		}
		List_Node<T>* previous = findLocation(d);
		if (previous == head) { // == size가 1일때
			if (head->getData() > node->getData()) { // head와의 비교
				node->setNext(head);
				head = node;
			}
			size++;
			return;
		}
		if (previous->getNext() == nullptr) { // 적절한 위치가 마지막 노드일때
			previous->setNext(node);
			node->setNext(nullptr);
			size++;
			return;
		}
		node->setNext(previous->getNext());
		previous->setNext(node);
		size++;
		return;
	}
	List_Node<T>* findLocation(T _data) { // data가 들어갈 적절한 위치를 찾는 함수
		List_Node<T>* node = head;
		if (_data < head->getData()) // 인자로 넘겨받는 data 자체가 내림차순으로 정렬된 채로 삽입될 때(eg) 10 9 8 7 ...)
			return head;
		while (node->getNext() != nullptr) {
			// node의 data < _data < node의 다음위치의 data라는 부등식을 만족시킬 때 까지 반복
			if (node->getData() <= _data && _data < node->getNext()->getData()) {
				break;
			}
			node = node->getNext();
		}
		return node;
	}
	T deleteData(T data) { 
		// 삭제 성공 시, 삭제된 node의 data를 반환
		// 비어있거나, 찾지 못 했을땐 -1반환
		List_Node<T>* node = head;
		if (isEmpty()) {
			return -1;
		}
		if (head->getData() == data) {
			// 아래의 while문에서 기술했다시피, node의 다음위치를 검사하기에,
			// head를 비교하지 못하게 된다.
			T temp = node->getData();
			List_Node<T>* deleteNode = node;
			head = node->getNext(); // node가 head로 바뀐다. 그러면 원래 head에 있던 것은? => node의 다음에 위치하게 된다.
			delete node;
			size--;
			return temp;
		}
		while (node->getNext() != nullptr) {
			// 교재에 나와있는 포인터 cur을 추가로 사용하는 방식 대신 node의 다음위치를 검사하는 방식을 이용해 약간의 메모리 절약
			// 실제로 효과가 있는지는 잘 모르겠다...
			if (node->getNext()->getData() == data) {
				T temp = node->getNext()->getData();
				List_Node<T>* deleteNode = node->getNext();
				node->setNext(node->getNext()->getNext());
				delete deleteNode;
				size--;
				if (isEmpty()) {
					head = nullptr;
				}
				return temp;
			}
			node = node->getNext();
		}

		if (node == nullptr) { // node가 마지막 위치에 도달했을 때 <=> 원소를 찾지 못했다는 의미
			return -1;
		}
	}
	void printAllData() {
		// 모든 data 출력
		List_Node<T>* node = head;
		while (node != nullptr) {
			cout << node->getData() << endl;
			node = node->getNext();
		}
	}
};
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	Linked_List<int> linkedList;
	for (int i = 10; i >= 1; i--) {
		linkedList.insert(i);
	}
	linkedList.insert(13);
	linkedList.insert(12);
	linkedList.insert(-10);
	linkedList.printAllData();
	cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
	linkedList.deleteData(12);
	linkedList.deleteData(1);
	linkedList.printAllData();
}