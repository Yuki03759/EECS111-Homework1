#include "p1_process.h"
#include "sys/wait.h"

using namespace std;

void getResult(vector<Node> arr, string filename){
    
    string file_place = "../output/" + filename + "_stats.csv";
    const char* file = file_place.c_str();
    ofstream ofs(file);
    
    double total, sd, mean, median;
    double power = 2.0;
    
    for(int i = 0; i < arr.size(); i++){
        total += arr[i].grade;
    }
   
    mean = total/arr.size();
    
    if(arr.size() % 2 != 0)
    { 
        median = arr[arr.size()/2].grade; 
    }
    else
    {
        median = ( arr[arr.size()/2].grade + arr[arr.size()/2+1].grade )/2;
    }
    
    for(int i = 0; i < arr.size(); i++){
        sd += pow( (arr[i].grade -  mean), power );
    }
    
    sd = sqrt(sd/arr.size());
   
    ofs << "Average,Median,Std. Dev" << "\r\n";
    ofs << fixed << setprecision(3) << mean << ","; 
    ofs << fixed << setprecision(3) << median << ",";
    ofs << fixed << setprecision(3) << sd;
    
    ofs.close();
}

void print_vector(vector<Node> arr){
    
    cout << "Rank\tStudent_ID\tGrade" << '\n';
    cout << "-------------------------------" << '\n';
    
    int count = 0;
    
    for(int i = 0; i < arr.size(); i++){
        cout << ++count << '\t';
        cout << arr[i].studentID << '\t';
        cout << setprecision(12) << arr[i].grade << ' ';
        cout << '\n';
    }
    cout << '\n';
}

void write_file(vector<Node> arr, string filename){
    
   string file_place = "../output/" + filename + "_sorted.csv";
   const char* file = file_place.c_str();
   ofstream ofs(file);
   
   
   int count = 0;
   
    ofs << "Rank,Student ID,Grade" << "\r\n";
    
    for(int i = 0; i < arr.size(); i++){
        ofs << ++count << ',';
        ofs << arr[i].studentID << ',';
        ofs << setprecision(12) << arr[i].grade;
        ofs << "\r\n";
    }
    ofs << "\r\n";
   
   ofs.close();
}

vector<Node> read_file(string filename){
    
    string file = "../input/" + filename + ".csv";
    ifstream ifs(file.c_str());
    
    if(!ifs.is_open()) {
        cout << "ERROR: File Open" << '\n';
        exit(1);
    }
    
    vector<Node> arr;
    
    string Student_ID;
    string Grade;
    double floatGrade;
    
    getline(ifs, Student_ID);

    while(!ifs.eof()){
        getline(ifs, Student_ID, ',');
        getline(ifs, Grade);
        
        if(Student_ID != ""){
            Node info;
            info.studentID = Student_ID;
            floatGrade = atof(Grade.c_str());
            info.grade = floatGrade;
            arr.push_back(info);
        }
    }
    
    ifs.close();    
    
    return arr;
}


void get_statistics(string class_name[], int num_processes, int num_threads) {
    
    if(num_processes >5)
        num_processes = 5;
    
    int pid = 1;
    int i;
    for(i = 0; i <num_processes; i++){   
        if (pid > 0)
            pid = fork();
        else 
            break;
    }
    
    i--;
    
    vector<Node> answer[5];
    
    //thread id
    
    if (pid == 0){
        
        for (int j = 0; j< 5; j++)
        {
            if ( i == j % num_processes )
            {    
                printf("child #%d pid. (pid: %d) doing %s\n", i, getpid(), class_name[j].c_str());
                vector<Node> arr = read_file(class_name[j]);
                answer[j] = threadSort(arr, num_threads, class_name[j]);
                write_file(answer[j], class_name[j]);
                getResult(answer[j], class_name[j]);
            }
        }
        exit(0);
    }
    else if (pid > 0){  
        printf("parent process pid. (pid: %d)\n", getpid());
        for(int i=0; i < num_processes; i++){
            wait(NULL);
        }
    }
}
