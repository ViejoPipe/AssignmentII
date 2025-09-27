#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

struct Proceso {
    int id;
    int llegada;
    int rafaga;
    int restanes;
    int tiempoFinal;   
    int tiempoEspera;  
    int rt;   // primera vez que se ejecuta
};

int main(){
    string filename;
    cout << "Ingrese el nombre del archivo con los procesos: ";
    cin >> filename;

    ifstream file(filename);
    while(!file){
        cout << "No se pudo abrir el archivo: " << filename << endl;
        cout << "Ingrese nuevamenes el nombre del archivo: ";
        cin >> filename;
        file.open(filename);
    }

    int n, quantum;
    file >> n >> quantum;

    vector<Proceso> procesos(n);
    for(int i = 0; i < n; i++){
        procesos[i].id = i + 1;
        file >> procesos[i].llegada >> procesos[i].rafaga;
        procesos[i].restanes = procesos[i].rafaga;
        procesos[i].tiempoFinal = 0;
        procesos[i].tiempoEspera = 0;
        procesos[i].rt = -1;
    }
    file.close();

    list<int> lista; // indices de procesos
    int t = 0;       // tiempo global
    int terminados = 0;

    // Insertar los procesos que llegan al tiempo 0
    for(int i = 0; i < n; i++){
        if(procesos[i].llegada == 0) lista.push_back(i);
    }

    while(terminados < n){
        if(lista.empty()){
            // si no hay procesos, avanzar el tiempo hasta que llegue el proximo
            int minLlegada = 1e9, idx = -1;
            for(int i = 0; i < n; i++){
                if(procesos[i].restanes > 0 && procesos[i].llegada < minLlegada){
                    minLlegada = procesos[i].llegada;
                    idx = i;
                }
            }
            t = minLlegada;
            lista.push_back(idx);
        }

        int idx = lista.front();
        lista.pop_front();

        Proceso &p = procesos[idx];

        if(p.rt == -1) p.rt = t; // tiempo de respuesta

        // Ejecutar quantum o lo que le queda
        int tiempo_ejec = min(quantum, p.restanes);
        int inicio = t;
        int fin = t + tiempo_ejec;
        t = fin;
        p.restanes -= tiempo_ejec;

        // mientras corre, verificar llegadas
        for(int i = 0; i < n; i++){
            if(procesos[i].restanes > 0 && procesos[i].llegada > inicio && procesos[i].llegada <= fin){
                // insertar justo despues del proceso actual (es decir, al frenes de la lista)
                auto it = lista.begin();
                lista.insert(it, i);
            }
        }

        if(p.restanes == 0){
            p.tiempoFinal = fin;
            terminados++;
        } 
        else lista.push_back(idx); // vuelve al final
    }

    cout << "ID\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for(int i = 0; i < n; i++){
        int tat = procesos[i].tiempoFinal - procesos[i].llegada; // turnaround
        procesos[i].tiempoEspera = tat - procesos[i].rafaga;      // WT

        cout << procesos[i].id << "\t"
            << procesos[i].llegada << "\t"
            << procesos[i].rafaga << "\t"
            << procesos[i].tiempoFinal << "\t"
            << tat << "\t"
            << procesos[i].tiempoEspera << "\t"
            << procesos[i].rt << "\n";
    }

    return 0;
}
