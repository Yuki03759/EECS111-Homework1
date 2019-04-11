#include "test.h"

template <class Object>
class Node{
    
    public:
    Node (std::string theStudentID, std::string theGrade, Node<Object>* prevNode = NULL, Node<Object>* nextNode = NULL){
        studentID = theStudentID;
        grade = theGrade;
        prev = prevNode;
        next = nextNode;
    }
    
    ~Node(){
        prev = NULL;
        next = NULL;
    }
    std::string getStudentID(){
        return studentID;
    }
    std::string getGrade(){
        return grade;
    }
    Node<Object>* getPrev(){
        return prev;
    }
    
    Node<Object>* getNext(){
        return next;
    }
    
    void setPrev(Node<Object>* prevNode){
        prev = prevNode;
    }
    
    void setNext(Node<Object>* nextNode){
        next = nextNode;
    }
    
    
    private:
    Object key;
    std::string studentID;
    std::string grade;
    Node<Object>* prev;
    Node<Object>* next;
};

template <class Object>
class List{
    
    public:
    List(){
        front = NULL;
        back = NULL;
    }
    ~List(){
        
    }
    
    List<Object>* getFront(){
        return front;
    }
    
    List<Object>* getBack(){
        return back;
    }
  
  
    void printList(List<int>* l){
        if(front == NULL){
            std::cout << "Empty List";
        }
        else{
            std::cout << "StudentID\tGrade " << std::endl;
            std::cout << "----------------------------------" << std::endl;
            Node<Object>* currentNode = front;
            while(currentNode != NULL){
                std::cout << currentNode -> getStudentID() << '\t';
                std::cout << currentNode -> getGrade() << std::endl;
                currentNode = currentNode -> getNext();
            }
        }
    }
  
    void insert(std::string Student_ID, std::string Grade){
        Node<Object>* newNode =  new Node<Object>(Student_ID, Grade, NULL, NULL);
        
        if(front == NULL){
            front = newNode;
            back = newNode;
        }
        else{
            back -> setNext(newNode);
            back = newNode;
        }
        
    }
    
    private:
    Node<Object>* front;
    Node<Object>* back;
};

void read_file(std::string filename){
    
    std::ifstream ip;
    
    ip.open("../input/small_os.csv", std::ifstream::in);
    
    List<int>* l = new List<int>();
    if(!ip.is_open()) 
        std::cout << "ERROR: File Open" << '\n';
    
    std::string Student_ID;
    std::string Grade;
    std::string name1;
    std::string name2;
    
    getline(ip, name1, ',');
    getline(ip, name2);
    
    while(!ip.eof()){
        getline(ip, Student_ID, ',');
        getline(ip, Grade);
        l -> insert( Student_ID, Grade );
    }
    
    ip.close();
    
    l -> printList(l);

}

void get_statistics(std::string class_name[]){
    
}

// This file includes functions that actually perform the
// computation. You can create a thread with these function
// or directly call this function

