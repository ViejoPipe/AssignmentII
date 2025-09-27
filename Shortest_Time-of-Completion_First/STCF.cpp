#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Proceso {
    int id;
    int llegada;
    int rafaga;
    int restante;
    int finaliza;
    int espera;
    int rt; // primera vez que se ejecuta
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

    int n;
    file >> n; // numero de procesos
    vector<Proceso> procesos(n);

    // leer n procesos
    for(int i = 0; i < n; i++){
        file >> procesos[i].llegada >> procesos[i].rafaga;
        procesos[i].id = i + 1;
        procesos[i].restante = procesos[i].rafaga;
        procesos[i].finaliza = 0;
        procesos[i].espera = 0;
        procesos[i].rt = -1; 
    }

    file.close();

    int tiempo = 0, completados = 0;

    // Algoritmo Shortest Time of Completion First (STCF)
    while(completados < n){
        int idx = -1, minRestante = 1e9;
        for(int i = 0; i < n; ++i){
            if(procesos[i].llegada <= tiempo && procesos[i].restante > 0 && procesos[i].restante < minRestante){
                minRestante = procesos[i].restante;
                idx = i;
            }
        }

        // no hay procesos listos en este instante
        if(idx == -1){
            tiempo++;
            continue;
        }

        // Si es la primera vez que se ejecuta, guardamos RT
        if(procesos[idx].rt == -1) procesos[idx].rt = tiempo;
        
        procesos[idx].restante--;
        tiempo++;
        
        // si termino, actualizar
        if(procesos[idx].restante == 0){
            procesos[idx].finaliza = tiempo;    
            procesos[idx].espera = tiempo - procesos[idx].llegada - procesos[idx].rafaga;
            completados++;
        }
    }

    // salida
    cout << "ID\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for(const auto& p : procesos){
        int retorno = p.finaliza - p.llegada;
        cout << p.id << "\t" << p.llegada << "\t" << p.rafaga
            << "\t" << p.finaliza << "\t" << p.espera
            << "\t" << retorno << "\t" << p.rt << endl;
    }

    return 0;
}
