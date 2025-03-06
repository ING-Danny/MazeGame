#include <iostream>
#include <fstream>
#include <conio.h> 
using namespace std;

const int filas = 10;
const int columnas = 10;

int jugadorX, jugadorY;
char laberinto[filas][columnas];
char nombreJugador[40] = "Default1";

void menu();
void mostrarLaberinto();
void moverJugador(char);
void guardarPartida();
void cargarPartida();
void nuevaPartida();
bool verificarVictoria();

int main() {
    srand(time(0));
    menu();
}

void menu() {
    int opcionmenu = 0;
    while (true) {
        cout << "1. Ingresar nombre de Jugador"<<endl;
        cout << "2. Iniciar Juego"<<endl;
        cout << "3. Salir del juego"<<endl;
        cout << "Ingrese una opcion: ";
        cin >> opcionmenu;

        switch (opcionmenu) {
        case 1:
            cout << "Ingrese su nombre: ";
            cin >> nombreJugador;
            break;
        case 2: {
            int opcionNum2;
            cout << "1. Cargar una partida"<<endl;
            cout << "2. Crear una nueva partida"<<endl;
            cout << "Ingrese una opcion: ";
            cin >> opcionNum2;
            if (opcionNum2 == 1) {
                cargarPartida();
            } else {
                nuevaPartida();
            }

            while (true) {
                mostrarLaberinto();
                char movimiento = _getch();

                if (movimiento == 'q') {  
                    guardarPartida();
                    cout << "La partida ha sido guardada correctamente " <<endl;;
                    cout << "Presione una tecla para volver al menu..."<<endl;;
                    _getch();
                    break;  
                }

                moverJugador(movimiento);

                if (verificarVictoria()) {  
                    mostrarLaberinto();
                    cout << "Felicidades, " << nombreJugador << ", has ganado " <<endl; 
                    cout << "Presione una tecla para volver al menu..."<<endl;
                    _getch();
                    break; 
                }
            }
            break;  
        }
        case 3:
            return;
        default:
            cout << "Opcion invalida.\n";
        }
    }
}

void mostrarLaberinto() {
    system("cls");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << laberinto[i][j] << " ";
        }
        cout << endl;
    }
}

void moverJugador(char direccion) {
    int nuevaX = jugadorX, nuevaY = jugadorY;

    if (direccion == 'w') nuevaX--; 
    if (direccion == 's') nuevaX++; 
    if (direccion == 'a') nuevaY--; 
    if (direccion == 'd') nuevaY++; 

    
    if (laberinto[nuevaX][nuevaY] == 'S') {
        jugadorX = nuevaX;
        jugadorY = nuevaY;
        return;
    }

    
    if (nuevaX >= 0 && nuevaX < filas && nuevaY >= 0 && nuevaY < columnas && laberinto[nuevaX][nuevaY] != 'X') {
        
        if (laberinto[jugadorX][jugadorY] != 'S') {
            laberinto[jugadorX][jugadorY] = ' ';
        }

        jugadorX = nuevaX;
        jugadorY = nuevaY;
        laberinto[jugadorX][jugadorY] = 'O';
    }
}

void guardarPartida() {
    ofstream archivo("laberinto.txt");
    if (!archivo) {
        cout << "Error al abrir el archivo para guardar.\n";
        return;
    }

    archivo << nombreJugador << endl;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            archivo << laberinto[i][j];
        }
        archivo << endl;
    }

    archivo.close();
}

void cargarPartida() {
    ifstream archivo("laberinto.txt");
    if (!archivo) {
        cout << "No hay partida guardada.\n";
        return;
    }

    archivo.getline(nombreJugador, 40);

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            archivo.get(laberinto[i][j]);
            if (laberinto[i][j] == 'O') {
                jugadorX = i;
                jugadorY = j;
            }
        }
        archivo.ignore();
    }

    archivo.close();
}

void nuevaPartida() {
    char tempLaberinto[filas][columnas] = {
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', 'O', ' ', ' ', 'X', ' ', ' ', ' ', ' ', 'X'},
        {'X', 'X', 'X', ' ', 'X', ' ', 'X', 'X', ' ', 'X'},
        {'X', ' ', ' ', ' ', 'X', ' ', ' ', 'X', ' ', 'X'},
        {'X', 'X', 'X', ' ', 'X', 'X', ' ', 'X', 'X', 'X'},
        {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'},
        {'X', ' ', 'X', 'X', 'X', 'X', 'X', 'X', ' ', 'X'},
        {'X', ' ', 'X', 'S', ' ', ' ', ' ', ' ', ' ', 'X'},
        {'X', ' ', 'X', 'X', 'X', 'X', 'X', 'X', ' ', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
    };

    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            laberinto[i][j] = tempLaberinto[i][j];

    jugadorX = 1;
    jugadorY = 1;
}

bool verificarVictoria() {
    return laberinto[jugadorX][jugadorY] == 'S';
}
