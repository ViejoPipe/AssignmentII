#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Proceso {
    string nombre;
    int at, bt; //arrival time, burst time
    int ct, tat, wt, rt; //completion time, turnaround time, waiting time, response time
    bool ejecutado;
};

int main(){
    string filename;
    cout << "Ingrese el nombre del archivo con los procesos: ";
    cin >> filename;

    ifstream file(filename);

    while(!file){
        cout << "No se pudo abrir el archivo: " << filename << endl;
        cout << "Ingrese nuevamente el nombre del archivo: ";
        cin >> filename;
        file.open(filename);
    }

    Proceso procesos[200];
    int n = 0;
    string line;

    while(getline(file, line)){
        stringstream ss(line);
        ss >> procesos[n].nombre >> procesos[n].at >> procesos[n].bt;
        procesos[n].ejecutado = false;
        n++;
    }
    file.close();

    int tiempo = 0;
    int ejecutados = 0;

    while(ejecutados < n){
        int idx = -1;

        //buscar proceso disponible con menor BT
        for(int i = 0; i < n; i++){
            if(!procesos[i].ejecutado && procesos[i].at <= tiempo){
                if(idx == -1) idx = i;
                else if(procesos[i].bt < procesos[idx].bt) idx = i;
                //en caso de empate por BT se queda con el primero que aparecio en el archivo
            }
        }

        //si no se encontro proceso disponible, avanzar tiempo al siguiente arrival
        if(idx == -1){
            int menorAT = -1;
            for(int i = 0; i < n; i++){
                if(!procesos[i].ejecutado){
                    if(menorAT == -1 || procesos[i].at < menorAT){
                        menorAT = procesos[i].at;
                        idx = i;
                    }
                }
            }
            tiempo = procesos[idx].at;
        }

        //ejecutar el proceso seleccionado
        procesos[idx].rt = tiempo;
        procesos[idx].wt = tiempo - procesos[idx].at;
        tiempo += procesos[idx].bt;
        procesos[idx].ct = tiempo;
        procesos[idx].tat = procesos[idx].ct - procesos[idx].at;
        procesos[idx].ejecutado = true;
        ejecutados++;
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
