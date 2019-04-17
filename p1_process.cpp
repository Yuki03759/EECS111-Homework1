#include "p1_process.h"
#include "sys/wait.h"
#include <vector>

class Node{
    
    public:
    Node (std::string theStudentID, float theGrade, Node* prevNode = NULL, Node* nextNode = NULL){
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
    float getGrade(){
        return grade;
    }
    Node* getPrev(){
        return prev;
    }
    
    Node* getNext(){
        return next;
    }
    
    void setPrev(Node* prevNode){
        prev = prevNode;
    }
    
    void setNext(Node* nextNode){
        next = nextNode;
    }
    
    
    private:
    std::string studentID;
    float grade;
    Node* prev;
    Node* next;
};

class List{
    
    public:
    List(){
        front = NULL;
        back = NULL;
    }
    ~List(){
        
    }
    
    Node* getFront(){
        return front;
    }
    
    Node* getBack(){
        return back;
    }
  
  
    void printList(List* l){
        if(front == NULL){
            std::cout << "Empty List";
        }
        else{
            std::cout << "StudentID\tGrade " << std::endl;
            std::cout << "----------------------------------" << std::endl;
            Node* currentNode = front;
            while(currentNode != NULL){
                std::cout << currentNode -> getStudentID() << '\t';
                std::cout << currentNode -> getGrade() << std::endl;
                currentNode = currentNode -> getNext();
            }
        }
    }
  
    void insert(std::string Student_ID, float Grade){
        Node* newNode =  new Node(Student_ID, Grade, NULL, NULL);
        
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
    Node* front;
    Node* back;
};

void read_file(std::string filename){
    
    std::ifstream ip;
    
    //char* file1 = ( ( pos + "os" + ext ).c_str() );
    
    ip.open("../input/small_os.csv", std::ifstream::in);
    
    List* l = new List();
    
    if(!ip.is_open()) {
        std::cout << "ERROR: File Open" << '\n';
        return;
    }
    
    std::string Student_ID;
    std::string Grade;
    std::string name1;
    std::string name2;
    
    getline(ip, name1, ',');
    getline(ip, name2);
    
    while(!ip.eof()){
        getline(ip, Student_ID, ',');
        getline(ip, Grade);
        if(Student_ID != ""){
            l -> insert( Student_ID.c_str(), std::atof(Grade.c_str()) );
        }
    }
    
    ip.close();
    
    //l -> printList(l);
    
}

void write_file(std::string filename){
    
   std::string file_place = "../output/" + filename + ".txt";
   const char* file_dump = file_place.c_str();
   
   std::ofstream dump(file_dump);
   
   dump << "dumping" << '\n';
   
   dump.close();
   
   
}

void get_statistics(std::string class_name[], int num_processes, int num_threads) {

}

//threading
/*
	if(num_processes >5)
        num_processes = 5;

    int pid = 1;
 
    for(int i = 0; i <num_processes; i++){   
        if (pid > 0)
            pid = fork();
    }
    
    if (pid == 0){
        printf("child pid. (pid: %d)\n", getpid());
        
        exit(0);
    }
    else if (pid > 0){
        
        printf("parent process pid. (pid: %d)\n", getpid());
        for(int i=0; i < num_processes; i++){
            wait(NULL);
        }
    }
*/  

