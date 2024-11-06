
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <thread> 
#include <chrono>
//#include "windows.h";
using namespace std;

/*    https://emojidb.org/simbolos-aesthetic-emojis
⋆｡𖦹°⭒˚｡⋆⋆｡𖦹°⭒˚｡⋆
☆━━─────「✦」─────━━☆

૮₍˶ᵔ ᵕ ᵔ˶₎ა
˗ˋˏ ♡ ˎˊ˗
*ੈ✩‧₊˚༺☆༻*ੈ✩‧₊˚
๋ ࣭ ⭑๋ ࣭ ⭑
⋆.˚✮🎧✮˚.⋆

────୨ৎ────
╔═.✵.══════════╗

╚══════════.✵.═╝
╭══• ೋ•✧๑♡๑✧•ೋ •══╮

╰══• ೋ•✧๑♡๑✧•ೋ •══╯
╔═══════════════╗

╚═══════════════╝
┌───── •✧✧• ─────┐

└───── •✧✧• ─────┘
☆
ೕ(˃̵ᴗ˂̵ ๑)
(╥﹏╥)

╰(*°▽°*)╯
ヾ(￣▽￣) Bye~Bye~

⋆⭒˚.⋆🪐 ⋆⭒˚.⋆
⋆｡‧˚ʚ🍓ɞ˚‧｡⋆
(∩^o^)⊃━☆
 ∧,,,∧ ~ ┏━━━━━━━━━━━━━━━━━━┓
( ̳•·• ̳)~ 
/   づ ~ ┗━━━━━━━━━━━━━━━━━━┛
*/

/* TODO LIST:
    - Crear nuevos objetos con cada partida 
    - Poner condicional de numero en menu y coordenas
    - Ingresar nombre
    - Poder jugar más de una partida (también tendria que haber una opcion para salir del juego, rendirte, y empezar de nuevo)
    - Que se guarde la partida anterior (récord tiempo)?? 
    - si pierde, que sw muestren todas las minas
    - Ponerle cronometro (lloré)
*/

/*
mTablero: 
    -1 = BOMBA
    [0-9] = numero

mPrint_Tablero:
   
   -3 = no volteado
   -2 = Bomba
   -1 = bandera
   [0-9] = numero
*/

class cPartida {
private:
    string mNombre;
    int mTamanio;
    int mBombas;
    vector<int> mX_bombas;
    vector<int> mY_bombas;
    int **mTablero;
    int **mPrintTablero;
    bool mContinuarPartida = true;
    int mBanderasColocadas = 0;

public:
    cPartida(int i, string Nombre) {
        mNombre = Nombre;
        if (i == 1) {mTamanio = 6; mBombas = 3 + rand() % 3;}
        else if (i == 2) {mTamanio = 8; mBombas = 8 + rand() % 5;}
        else if (i == 3) {mTamanio = 10; mBombas = 15 + rand() % 6;}
        else {
            cout << endl << "              Opción no valida" <<  endl;
            cout << " ∧,,,∧ ~ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
            cout << "( ̳•·• ̳)~   Dificultad 'Facil' por defecto" << endl;
            cout << "/   づ ~ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"<< endl ;
            mTamanio = 6; mBombas = 3 + rand() % 3;}

        // crear tableros
        mTablero = new int*[mTamanio];
        mPrintTablero = new int*[mTamanio];
        for (int i = 0; i < mTamanio; i++){
            mTablero[i] = new int[mTamanio];
            mPrintTablero[i] = new int[mTamanio];}

        // llenar tableros
        for (int i = 0; i < mTamanio; i++) {
            for (int j = 0; j < mTamanio; j++) {
                mTablero[i][j] = 0;
                mPrintTablero[i][j] = -3;}
        }
    }

    void ImprimirPrintTablero() {
        cout << endl << endl << endl;
        if (mContinuarPartida != false){
            cout << " ─  ─  ─  ─  ─ ୨ৎ ─  ─  ─  ─  ─" << endl;
            cout << "   Minas: " << mBombas << endl;
            cout << "   Banderas: " << mBanderasColocadas << "/" << mBombas << endl;
            cout << endl;}
        cout << "    "; // espacio para el índice de las columnas
        for (int i = 0; i < mTamanio; i++) {
            cout << setw(3) << i + 1;}
        cout << endl;
        cout << "   ╭";
        for (int i = 0; i < mTamanio; i++) {
            cout << "───";} //————
        cout << "─" << endl;
        for (int i = 0; i < mTamanio; i++) {
            cout << setw(2) << i + 1 << " |"; // índice de filas
            for (int j = 0; j < mTamanio; j++) {
                if (mPrintTablero[i][j] == -3) {
                    cout << "  " << "▢";} // ■▢
                else if (mPrintTablero[i][j] == -1) {
                    cout << "  " << "\033[1m\033[31mB\033[0m";}
                else if (mPrintTablero[i][j] == -2 && !mContinuarPartida) {
                    cout << "  " << "★";}
                else {
                    if (mPrintTablero[i][j] == 0) { 
                        cout << "  " << "\033[90m0\033[0m";} // gris
                    if (mPrintTablero[i][j] == 1) {
                        cout << "  " << "\033[34m1\033[0m";} // azul
                    if (mPrintTablero[i][j] == 2) { 
                        cout << "  " << "\033[32m2\033[0m";} // verde
                    if (mPrintTablero[i][j] == 3) { 
                        cout << "  " << "\033[95m3\033[0m";} // rosado
                    if (mPrintTablero[i][j] == 4) { 
                        cout << "  " << "\033[0;33m4\033[0m";} // naranja
                    if (mPrintTablero[i][j] == 5) { 
                        cout << "  " << "\033[33m5\033[0m";} // amarillo
                    if (mPrintTablero[i][j] == 6) { 
                        cout << "  " << "\033[31m6\033[0m";} // rojo
                    if (mPrintTablero[i][j] == 7){ 
                        cout << "  " << "\033[95m7\033[0m";} // celeste
                    if (mPrintTablero[i][j] == 8){ 
                        cout << "  " << "\033[33m8\033[0m";} // azul
                    if (mPrintTablero[i][j] == 9){ 
                        cout << "  " << "\033[33m9\033[0m";} // negro
            }} cout << endl;} cout << endl;}

    void LlenarBombas(int x1, int y1) { // x1 y y1 son la primera jugada
        srand(time(nullptr));
        int bombas_colocadas = 0;
        while (bombas_colocadas < mBombas) {
            int x = rand() % mTamanio;
            int y = rand() % mTamanio;
            // verificar que la posición no esté en la primera jugada ni en los alrededores
            bool noAlrededores = !(x >= x1 - 1 && x <= x1 + 1 && y >= y1 - 1 && y <= y1 + 1);
            // colocar bomba solo si la celda está vacía y fuera de los alrededores
            if (mTablero[x][y] != -2 && noAlrededores) {
                mTablero[x][y] = -2;
                mX_bombas.push_back(x);
                mY_bombas.push_back(y);
                bombas_colocadas++;}}}

    void ColocarNumEnTablero(){
        for(int i = 0; i < mBombas; i++){
            int x = mX_bombas[i];
            int y = mY_bombas[i];
            if(x-1<mTamanio && x-1>=0 && y-1<mTamanio && y-1>=0 && (mTablero[x-1][y-1]!=-2)){mTablero[x-1][y-1] += 1;}
            if(x-1<mTamanio && x-1>=0 && y<mTamanio && y>=0 && (mTablero[x-1][y]!=-2)){mTablero[x-1][y] += 1;}
            if(x-1<mTamanio && x-1>=0 && y+1<mTamanio && y+1>=0 && (mTablero[x-1][y+1]!=-2)){mTablero[x-1][y+1] += 1;}
            if(x<mTamanio && x>=0 && y-1<mTamanio && y-1>=0 && (mTablero[x][y-1]!=-2)){mTablero[x][y-1] += 1;}
            if(x<mTamanio && x>=0 && y+1<mTamanio && y+1>=0 && (mTablero[x][y+1]!=-2)){mTablero[x][y+1] += 1;}
            if(x+1<mTamanio && x+1>=0 && y-1<mTamanio && y-1>=0 && (mTablero[x+1][y-1]!=-2)){mTablero[x+1][y-1] += 1;}
            if(x+1<mTamanio && x+1>=0 && y<mTamanio && y>=0 && (mTablero[x+1][y]!=-2) ) {mTablero[x+1][y] += 1;}
            if(x+1<mTamanio && x+1>=0 && y+1<mTamanio && y+1>=0 && (mTablero[x+1][y+1]!=-2)) {mTablero[x+1][y+1] += 1;}}}

    void Jugada(int x, int y){
        if (mTablero[x][y] == -2) { // si es una bomba
            MostrarBombas();
            mContinuarPartida = false;
            ImprimirPrintTablero();
            cout << endl << "   ¡Boom! Has encontrado una bomba ╚(x . x)╝" << endl;
            cout << "  ╭════════════════════════════════════════╮" << endl;
            cout << "  |            GAME OVER (╥﹏╥)            |" <<  endl;
            cout << "  ╰════════════════════════════════════════╯" << endl;
            } 
            
        else if (mTablero[x][y] == -1) { // si es una bandera
                cout << "Aquí hay una bandera. Quítala para descubrir la zona ∧,,,∧" << endl;
                mContinuarPartida = true;} 
            
        else{
            if (mTablero[x][y] == 0) {DespejarZona(x, y);}  // si la celda seleccionada es un 0, despejar la zona
            else { // de lo contrario, revelar solo la celda seleccionada
                mPrintTablero[x][y] = mTablero[x][y];}
                ImprimirPrintTablero();}}

    bool VerificarVictoria() {
        for (int i = 0; i < mTamanio; i++) {
            for (int j = 0; j < mTamanio; j++) {
                if (mPrintTablero[i][j] == -3 && mTablero[i][j] != -2) {
                    return false;}}} // aún quedan celdas no descubiertas que no son bombas
        return true;} // todas las celdas restantes son bombas

    void ColocarBandera(int x, int y) {
        if (mPrintTablero[x][y] == -1) { // verifica si ya hay una bandera en esa posición
            cout << "  ⚠️ ADVERTENCIA:  Ya hay una bandera en la posición (" << x + 1 << "," << y + 1 << ")" << endl;}
            
        else if (mPrintTablero[x][y] == -3) { // solo coloca la bandera si la celda está sin descubrir
            mPrintTablero[x][y] = -1;           // marca la celda con una bandera
            mBanderasColocadas++;               // incrementa el contador de banderas
            cout << "  ☑ Bandera colocada en (" << x + 1 << ", " << y + 1 << ")." << endl;}
            
        else if ((mPrintTablero[x][y]!=-1) && (mPrintTablero[x][y]!=-2) && (mPrintTablero[x][y]!=-3)) {
            cout << "  ⚠️ ADVERTENCIA:  No se puede colocar una bandera en una celda ya descubierta" << endl;}}

    void QuitarBandera(int x, int y) {
        if (mPrintTablero[x][y] == -1) {
            mPrintTablero[x][y] = -3;   // restablece la celda a no descubierta
            mBanderasColocadas--;       // decrementa el contador de banderas
            cout << "  ⚠️ ADVERTENCIA:  Has quitado una bandera en (" << x + 1 << "," << y + 1 << ")" << endl;}
        else {cout << "  ⚠️ ADVERTENCIA:  No hay una bandera en (" << x + 1 << "," << y + 1 << ") para quitar" << endl;}}

    void DespejarZona(int x, int y) {
        // verifica si la posición está dentro de los límites del tablero
        if (x < 0 || x >= mTamanio || y < 0 || y >= mTamanio) return;
        // si la celda ya está descubierta o es una bomba, no necesita procesarse
        if (mPrintTablero[x][y] != -3 || mTablero[x][y] == -2) return;
        // revela la celda actual en mPrintTablero usando el valor de mTablero
        mPrintTablero[x][y] = mTablero[x][y];
        // si la celda actual no es un 0, no continúa el despegado
        if (mTablero[x][y] != 0)return;
        // despeja todas las celdas alrededor de la posición actual recursivamente
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int newX = x + dx;
                int newY = y + dy;
                // evita la posición central y verifica los límites
                if ((dx != 0 || dy != 0) && newX >= 0 && newX < mTamanio && newY >= 0 && newY < mTamanio) {
                    DespejarZona(newX, newY);}}}} // llama recursivamente a DespejarZona
    
    void MostrarBombas(){
        for (int x=0; x<mTamanio; x++){
            for (int y=0; y<mTamanio; y++){
                if (mTablero[x][y] == -2){
                    mPrintTablero[x][y]=-2;}}}}

    void Iniciarjuego(){
        cout << "     GAME START ╰(*°▽°*)╯    " << endl << endl ;
        ImprimirPrintTablero();

        int x, y;
        do {cout << "→ Ingrese la fila de la primera jugada: " ;
            cin >> x;
            x -= 1;
        } while (x < 0 || x >= mTamanio);

        do {cout << "→ Ingrese la columna de la primera jugada: " ;
            cin >> y;
            y -= 1;
        } while (y < 0 || y >= mTamanio);

        LlenarBombas(x,y);
        ColocarNumEnTablero();
        Jugada(x, y); // realizar la jugada inicial
        Continuar_Jugando();
}

    void Continuar_Jugando(){
        while (mContinuarPartida) {
            // verificar si el jugador ha ganado
            int x,y;

            if (VerificarVictoria()) {
                cout << endl;
                cout << "╭════════════•   •✧๑♡๑✧•   •═════════════╮" << endl;
                cout << "|                                        |" << endl;
                cout << "|   ¡Felicidades! Has ganado el juego    |" <<  endl;
                cout << "|            ٩(๑･ิᴗ･ิ)۶٩(･ิᴗ･ิ๑)۶            |" << endl;
                cout << "|                                        |" << endl;
                cout << "╰════════════•   •✧๑♡๑✧•   •═════════════╯" << endl;
                cout << endl << endl<< " ⋆.˚✮ Regresando al menú... "  << endl << endl;
                this_thread::sleep_for(chrono::seconds(3));
                // Menu();
                break;}
                
            char accion;
            cout << "   ☆ Jugada(j)" << endl;
            cout << "   ☆ Colocar bandera(c)" << endl;
            cout << "   ☆ Quitar bandera(q)" << endl;
            cout << "   ☆ Salir(s)" << endl;
            cout << "   Opcion: " ;
            cin >> accion;
    
            if (accion == 'c') {
                x = PedirCoordenada("   → Ingrese la fila: ");
                if (x == 100){Continuar_Jugando(); break;}
                y = PedirCoordenada("   → Ingrese la columna: ");
                if (y == 100){Continuar_Jugando(); break;}
                ColocarBandera(x, y); // coloca la bandera
                ImprimirPrintTablero();} // imprimir el tablero después de cada acción

            else if (accion == 'q') {
                x = PedirCoordenada("   → Ingrese la fila: ");
                if (x == 100){Continuar_Jugando(); break;}
                y = PedirCoordenada("   → Ingrese la columna: ");
                if (y == 100){Continuar_Jugando(); break;}
                QuitarBandera(x, y); // quita la bandera
                ImprimirPrintTablero();} // imprimir el tablero después de cada acción

            else if (accion == 'j') {
                // pedir las coordenadas para la jugada
                x = PedirCoordenada("   → Ingrese la fila: ");
                if (x == 100){Continuar_Jugando(); break;}
                y = PedirCoordenada("   → Ingrese la columna: ");
                if (y == 100){Continuar_Jugando(); break;}
                Jugada(x, y);}

            else if (accion == 's') {
                mContinuarPartida = false;}

            else {cout << "Opción inválida." << endl;}}

        
            if (!mContinuarPartida) {
            
                cout << endl << endl<< " ⋆.˚✮ Regresando al menú... "  << endl << endl;
                this_thread::sleep_for(chrono::seconds(1));}}

    int PedirCoordenada(const string &mensaje) {
        int coord;
        do {
            cout << mensaje;
            cin >> coord;
            if (coord == 100){
                return coord;}
            coord -= 1; // índices base 0
        } while (coord <= -1 || coord >= mTamanio );
        return coord;}

  ~cPartida() {
      for (int i = 0; i < mTamanio; i++) {
          delete[] mTablero[i];
          delete[] mPrintTablero[i];}
      delete[] mTablero;
      delete[] mPrintTablero;}

    /*
        void get_Tablero(){ //Solo para probar el codigo
            for(int i=0; i<mTamanio; i++){
                for(int j=0; j<mTamanio; j++){
                    cout << setw(3) << mTablero[i][j];}
                cout << endl;}
            cout << endl;}*/
    /*
    void Set_ContinuarPartida(bool continuarPartida) {
        mContinuarPartida = continuarPartida;}
    */
};

/*
cPartida* generarPartida(){
    int i;
    string n;
    cin >> i;
    cin > n;
    auto nueva_partida = new cPartida(i,n); // Que el constructor solo tenga como argumento el nombre de la nueva partida
    return nueva_partida;
}
*/

void Menu();

void Tutorial() {
    int regresar;
    cout <<  endl << endl << "         ⋆｡‧˚ʚ TUTORIAL ɞ˚‧｡⋆      " << endl << endl << endl;
    cout << " ☆ OBJETIVO ☆" <<  endl << endl;
    cout << "   Descubrir todas las casillas libres de minas\n   sin hacer explotar ninguna." << endl << endl << endl <<  endl; 
    cout << " ☆ ¿CÓMO SE JUEGA? ☆"  <<  endl << endl;
    cout << "    1. Selecciona cualquier casilla. Esto\n       abrirá un área inicial del tablero, revelando \n       algunos números y casillas en blanco." << endl << endl;
    cout << "       EJEMPLO: Ingresaste la posición (4,1)" << endl << endl;
    cout << "         " <<"     1  2  3  4  " << endl;
    cout << "         " <<"  ╭───────────── " << endl;
    cout << "         " <<"1 |  ▢  1  ▢  ▢  " << endl;
    cout << "         " <<"2 |  1  0  2  ▢  " << endl;
    cout << "         " <<"3 |  0  0  1  ▢  " << endl;
    cout << "         " <<"4 |  0  0  1  ▢  " << endl << endl << endl ;
    cout << "    2. Cada número en una casilla indica cuántas\n       minas hay en las casillas adyacentes \n       (horizontal, vertical o diagonal)." << endl <<  endl; 
    cout << "      → Si ves un '1', significa que hay una mina \n        en alguna de las ocho casillas alrededor." << endl << endl;
    cout << "         " <<  "    1  2  3  4  " << endl;
    cout << "         " << "  ╭───────────── " << endl;
    cout << "         " << "1 |  ?  ?  ?  ▢  " << endl;
    cout << "         " << "2 |  ?  1  ?  ▢  " << endl;
    cout << "         " << "3 |  ?  ?  ?  ▢  " << endl;
    cout << "         " << "4 |  ▢  ▢  ▢  ▢  " << endl << endl  ;
    cout << "      → Un '0' significa que no hay minas en las\n        casillas cercanas, por lo que estas se\n        abrirán automáticamente." << endl << endl;
    cout << "         " <<  "    1  2  3  4  " << endl;
    cout << "         " << "  ╭───────────── " << endl;
    cout << "         " << "1 |  0  1  ▢  ▢  " << endl;
    cout << "         " << "2 |  1  1  ▢  ▢  " << endl;
    cout << "         " << "3 |  ▢  ▢  ▢  ▢  " << endl;
    cout << "         " << "4 |  ▢  ▢  ▢  ▢  " << endl << endl << endl;
    cout << "    3. Si descubres una mina, pierdes el juego\n        y explotan todas las minas de tablero" << endl << endl;
    cout << "       EJEMPLO: Ingresaste la posición (2,2)" << endl << endl;
    cout << "         " <<"     1  2  3  4  " << endl;
    cout << "         " <<"  ╭───────────── " << endl;
    cout << "         " <<"1 |  ★  ▢  ▢  ★  " << endl;
    cout << "         " <<"2 |  2  ★  ▢  ▢  " << endl;
    cout << "         " <<"3 |  1  1  2  ▢  " << endl;
    cout << "         " <<"4 |  0  0  1  ★  " << endl << endl;
    cout << "         " <<"  -- GAVE OVER -- "<< endl ;

    cout << endl << endl <<  "  ╭══════════════════════════════════════════════╮" << endl;
    cout <<"  |                                              |" << endl;
    cout <<"  |  Ingresa un numero para regresar a menu: " ;
    cin >> regresar;
    bool j = regresar;
    if (j){
        cout << "  |                                              |" << endl;
        cout << "  ╰══════════════════════════════════════════════╯" << endl << endl ;
        Menu();}


    

    
}

void Menu(){
    int k;
    cout << endl;
    cout << " ╔═.✵..════════════════════════╗"<< endl;
    cout << " ║                             ║"<< endl;
    cout << " ║            MENU             ║"<< endl;
    cout << " ║                             ║"<< endl;
    cout << " ║  1. Jugar                   ║"<< endl;
    cout << " ║  2. Mejores jugadores       ║" << endl;
    cout << " ║  3. Tutorial                ║" << endl;
    cout << " ║  4. Salir                   ║" << endl;
    cout << " ║                             ║" << endl;
    cout << " ║  Escoge la opcion: ";
    cin >> k;
    cout << " ║                             ║"<< endl;
    cout << " ╚═══════════════════════..✵.══╝" << endl << endl ;

    switch(k) {
        case 1: {
            int i;
            string n;
            cout << " ╭──────────── •✧✧• ────────────╮" << endl;
            cout << " |                              | " << endl; 
            cout << " |            JUGAR             | " << endl; 
            cout << " |                              | " << endl; 
            cout << " |  Selecciona la dificultad    |" <<  endl;
            cout << " |   1. Facil                   | " << endl; 
            cout << " |   2. Medio                   |" << endl; 
            cout << " |   3. Dificil                 |" << endl;
            cout << " |  Ingrese la opcion: ";
            cin >> i;
            cout << " |  Ingrese tu nombre: ";
            cin >> n; 
            cout << " |                              | " << endl; 
            cout << " ╰──────────── •✧✧• ────────────╯" << endl;
            cout << "Ingresa '100' para escojer otra opción" << endl << endl << endl << endl <<  endl;
         
            cPartida partida(i, n);
            partida.Iniciarjuego();

            //Guardar partida en memoria
            Menu();
            break;}
        
        case 2: {
            cout << "Not available yet" << endl;
            Menu();
            break;}
        
        case 3: {
            Tutorial();
            break;}
                
        case 4: {
            cout << endl << " Muchas gracias por jugar" << endl;;
            cout <<  endl <<  "  ヾ(￣3￣) Bye~Bye~ ";
            break;}
        
        default:
            cout << "Opción no valida" << endl;
            Menu();
            break;
        }
    };


int main() {
// SetConsoleOutputCP(CP_UTF8);
    /*
    vector<cPartida*> partidas;
    cPartida* nueva_partida = generarPartida();
    partidas.push_back(nueva_partida);
    */
    cout << endl;
    cout << "BIENVENIDO A BUSCAMINAS (∩^o^)⊃-☆" << endl << endl;
    Menu();
    return 0;
}
