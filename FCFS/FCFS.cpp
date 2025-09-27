#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Proceso {
    string nombre;
    int at, bt;   //arrival time, burst time
    int ct, tat, wt, rt; //completion time, turnaround time, waiting time, response time
};

int main(){
    string filename;
    cout << "Ingrese el nombre del archivo con los procesos: ";
    cin >> filename;

    ifstream file(filename);

    //si no se pudo abrir se vuelve a pedir el nombre
    while(!file){
        cout << "No se pudo abrir el archivo: " << filename << endl;
        cout << "Ingrese nuevamente el nombre del archivo: ";
        cin >> filename;
        file.open(filename);
    }

    //lectura de procesos
    Proceso procesos[200]; 
    int n = 0;
    string line;

    while(getline(file, line)){
        stringstream ss(line);
        ss >> procesos[n].nombre >> procesos[n].at >> procesos[n].bt;
        n++;
    }
    file.close();

    //algoritmo FCFS
    int tiempo = 0;
    for(int i = 0; i < n; i++){
        //si la CPU esta libre y aun no ha llegado el proceso, hay que esperar
        if(tiempo < procesos[i].at) tiempo = procesos[i].at;

        //ejecutar el proceso seleccionado
        procesos[i].rt = tiempo;
        procesos[i].wt = tiempo - procesos[i].at;
        tiempo += procesos[i].bt;
        procesos[i].ct = tiempo;
        procesos[i].tat = procesos[i].ct - procesos[i].at;
    }

    //salida
    cout << "\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for(int i = 0; i < n; i++){
        cout << procesos[i].nombre << "\t"
            << procesos[i].at << "\t"
            << procesos[i].bt << "\t"
            << procesos[i].ct << "\t"
            << procesos[i].tat << "\t"
            << procesos[i].wt << "\t"
            << procesos[i].rt << "\n";
    }

    return 0;
}
