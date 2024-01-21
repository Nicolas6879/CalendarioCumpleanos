#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Variables y constantes globales del programa
int diasDelMes[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int diasTranscurridos[13] = {0,0,31,59,90,120,151,181,212,243,273,304,334};
int bisiestoH = 0;
int anioH;
int mesH;
int diaH;
int bifiestoP = 0;
int anioP;
int mesP;
int diaP;
string nombre;
int pediranio();
int pedirMes();
int pedirDia();
string descripciones[12][31]={};
int idDescripciones[12][31]={};

//metodo que pide un año al usuario y lo devuelve como un entero si es correcto
int pedirAnio(){   
    bool anioValido = false;
    int anio = 0;
	while(anioValido==false){
    cout<<"\nIngrese el año: ";
    cin>>anio;
        //Comprueba que la fecha este correcta
        if(anio>0)		{
            anioValido = true;
        }
		else{
            cout<<"\nEl año ingresado debe ser un numero entero positivo, por favor vuelva a ingresarlo.";
        }
    }
    return anio;
}
//metodo que pide un mes al usuario y lo devuelve como un entero si es correcto
int pedirMes(){
	bool mesValido = false;
	int  mes = 0;
	 while(mesValido==false){
    cout<<"\nIngrese el mes: ";
    cin>>mes;
        //Comprueba que la fecha este correcta
        if(mes>0 && mes<13){
            mesValido = true;
            if(anioH%4==0 && anioH%100!=0 && mes==2){
                bisiestoH = 1;
            }
        }
		else{
            cout<<"\nEl mes ingresado debe ser un numero entero positivo entre 1 enero y 12 diciembre.";
        }
    }
    return mes;
}
//metodo que pide un dia al usuario y lo devuelve como un entero si es correcto
int pedirDia(){
	bool diaValido = false;
	int dia = 0;
	 while(diaValido==false){
    cout<<"\nIngrese el dia: ";
    cin>>dia;
        //Comprueba que la fecha este correcta
        if(dia>0 && dia <= diasDelMes[mesP]+bisiestoH){
            diaValido = true;
        }
		else{
            cout<<"\nEl dia ingresado debe ser acorde al mes ingresado.";
        }
    }
    return dia;
}
//Funciones
// metodo que le permite al usuario ingresar la fecha de hoy
void FechaHoy(){
    bisiestoH = 0;
    anioH = pedirAnio();
    anioP = anioH;
    mesH = pedirMes();
    mesP = mesH;
    diaH = pedirDia();
    diaP = diaH;
	}
// metodo que  le permite ingresar al usuario otras fechas  para que el programa las use en diferentes puntos 
void fechaPedida(){
    bifiestoP = 0;
    anioP = pedirAnio();
    mesP = pedirMes();
    diaP = pedirDia();    
}
//guardar cumpleaños
//punto 2 del menu
void guardar(){
	cout<<"\nIngrese la fecha que desea guardar.";
	mesP = pedirMes();
	diaP = pedirDia();
	cout<<"Ingrese el nombre completo de la persona que cumple el mes y dia "<<mesP<<"/"<<diaP<<" : ";
	cin>>nombre;
	descripciones[mesP-1][diaP-1] = descripciones[mesP-1][diaP-1]+nombre+"&";
	idDescripciones[mesP-1][diaP-1] += 1;
}
//eliminar una fecha de cumpleaños
//punto 3 del menu
void editar(){
	cout<<"\nIngrese el mes: ";
	cin>>mesP;
	cout<<"\nIngrese el dia: ";
	cin>>diaP;
	cout<<"\nIngrese el nombre de quien quiere eliminar: ";
	string aux = "";
	cin>>aux;
	aux = aux + "&";
	descripciones[mesP-1][diaP-1] = descripciones[mesP-1][diaP-1].replace(descripciones[mesP-1][diaP-1].find(aux),aux.length(),"");
	idDescripciones [mesP-1][diaP-1] -= 1;    
}
//muestra todos los cumpleaños en las fechas donde hay un cumpleaños
//punto 4 
void mostrarTodosLosCumpleanios(){
		for(int m = 0; m<12; m++){
			for(int d = 0; d < 31; d++){				
				if(idDescripciones[m][d] > 0)
				{
				cout<<"\nEl mes "<<m+1<<" del dia "<<d+1<<" cumplen años: "<<descripciones[m][d]<<endl;
				}
			}
		}
}
//muestra todos los cumopleaños en un mes
//punto 5
void  mostrarCumpleaniosMes(){
		cout<<"Por favor digite el mes a revisar";
		mesP = pedirMes(); 
		for(int d = 0; d<31; d++){			
		 	if(idDescripciones[mesP-1][d] > 0){			
				cout<<"\nEl mes "<<mesP<<" del dia "<<d+1<<" cumplen años: "<<descripciones[mesP-1][d]<<endl;
			}
		}
}
//cuantos dias faltan 
//punto 6 del menu
void diasFaltan(){
	cout<<"\nIngrese la fecha que quiere comparar.";
    	mesP = pedirMes();
    	diaP = pedirDia();
		int diasF = ((diasTranscurridos[mesP]+diaP)-(diasTranscurridos[mesH]+diaH));
		if (diasF<0){
		diasF = diasF + 365;
		}
		cout<<"\nEl dia ingresado cumplen años "<<descripciones[mesP - 1][diaP - 1]<< " y faltan "<<(diasF)<<" dias para esa fecha";
}

void revisar (){
	fstream matrizD ("MatrizDescripciones.txt");
	if (matrizD.is_open()==false){
		ofstream matrizD ("MatrizDescripciones.txt");
		cout<<"\nNo hay registro descripcion creado anteriormente, creando registro..."<<endl;
	}
	else{
		for(int i=0; i<12; i++){
  		 string s="";
  		 matrizD>> s  ;
         string delimiter = "|";
         size_t pos = 0;
         string token;
         int j = 0;
         while ((pos = s.find(delimiter)) != string::npos && j <31){
         token = s.substr(0, pos);
         s.erase(0, pos + delimiter.length());
         descripciones[i][j]= token;
         j++;
         }	
		}
	}
	fstream matrizE ("MatrizEnteros.txt");
	if (matrizE.is_open()==false){
		ofstream matrizE ("MatrizEnteros.txt");
		cout<<"\nNo hay registro entero creado anteriormente, creando registro..."<<endl;
	}
	else{
		for(int i=0; i<12; i++){
  		 	for(int j=0; j<31; j++){
		matrizE>>idDescripciones[i][j]; 	
			}
		}
	}
}

void archivos(){
    cout << "\nMatriz Descripciones guardada en archivo txt";
  	fstream matrizD ("MatrizDescripciones.txt");
  	if (matrizD.is_open()){
   	 for(int i=0; i<12; i++){
   	     for(int j=0; j<31; j++){
            matrizD<<descripciones[i][j];
      		matrizD<<"|";
        	}
        matrizD<<"\n";
    	}
   	 matrizD.close();	
}	
	cout << "\nMatriz Enteros guardada en archivo txt";
	fstream matrizE ("MatrizEnteros.txt");
  	if (matrizE.is_open()){
   	 for(int i=0; i<12; i++){
   	     for(int j=0; j<31; j++){
            matrizE<<idDescripciones[i][j]; 
            matrizE<<" ";
        		}
        matrizE<<"\n";
    	}
   	 matrizE.close();
	}
		cout<<"\nFinalizando programa...";
}

/* Menú
+1 Cambiar fecha de hoy
+2 Guardar un cños
3 editar un cumpleaños
+4 mostrar todos los umpleaños
+5 mostrar los eventos de un mes
6 mostrar la descripción de los eventos de un dia-cuantos dias faltan para ese momentp
7 salir del programa
*/
void MostrarMenu(int numero){
    switch (numero){
	//+mostrar menu
		case 0: cout<<"\nIngrese 1 si quiere cambiar la fecha actual.\nIngrese 2 para guardar un nuevo cumpleaños.\nIngrese 3 si quiere eliminar un cumpleaños.\nIngrese 4 para mostrar todos los cumpleaños guardados.\nIngrese 5 para mostrar los cumpleaños en un mes\nIngrese 6 para mostrar los dias restantes para una fecha\nIngrese 7 para salir del programa.\n\n\t\tOpcion: ";
		cin>>numero;
		MostrarMenu(numero);
		break;
	//+Cambiar fecha hoy
		case 1:
		FechaHoy();
		MostrarMenu(0);
		break;
	//+Guardar un nuevo cumpleaños
		case 2:
		guardar();		
		MostrarMenu(0);
		break;
	//Editar un cumpleaños
		case 3:
		editar();
		MostrarMenu(0);
		break;
	//+Mostrar todos los cumpleaños
		case 4:
		mostrarTodosLosCumpleanios();
		MostrarMenu(0);
		break;
	//+Mostrar los Cumpleaños de un mes
		case 5:
	    mostrarCumpleaniosMes();
		MostrarMenu(0);
		break;
	//Mostrar cuantos dias faltan
		case 6:
		diasFaltan();
		MostrarMenu(0);
		break;
	//Salir del programa.
		case 7:
		break;
	//En caso de que no se haya digitado el numero correcto.	
	default: cout<<"La opcion ingresado no se encuentra disponible.";
	MostrarMenu(0);
	break;
    }
}

int main(){
    revisar();
    cout<<"***Bienvenido al calendario de cumpleaños by : grupo 7***\nPor favor ingrese la fecha de hoy.\n";
    FechaHoy();
    MostrarMenu(0);
    archivos();
    return 0;
}
