#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#pragma extref_floatconvert

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);


//PROTOTIPO DE LAS FUNCIONES
void CursorOn(bool visible, DWORD size);
void CursorOff();
void gotoxy(int x,int y);
void dibujarCuadro(int x1,int y1,int x2,int y2);
void limpia();
void menu();
void ingreso();
void actualizar();
void eliminar();
void consultar();
void deposito();
void retiro();
void libreta();


//ESTRUCTURA SOCIO Y SUS RESPECTIVAS VARIABLES
struct socio{
	char nombre[35];
	char cedula[15];
	char ciudad[20];
	char telefono[20];
};

//ESTRUCTURA TRANSACCIONES Y SUS RESPECTIVAS VARIABLES
struct transacciones{
	char cedula[15];
	char nombre[35];
	char fecha[15];
	float valorinicial;
	float transacc;
};

//ESTRUCTURA FECHAE Y SUS RESPECTIVAS VARIABLES
struct fechae{
	char cedulaf[15];
	char nombref[35];
	char fechaf[15];
	char tipof[10];
	float transaccf;
	float saldof;
};


//FUNCION PRINCIPAL MAIN: EN ESTA FUNCION PRINCIPAL AQUI SE LLAMAN A LOS DEMAS METODOS
int main(){
	system("mode con: cols=80 lines=25");
	system("COLOR 70");
	dibujarCuadro(1,1,78,24); //Cuadro grande
	dibujarCuadro(2,2,77,4); //Cuadro titulo
	gotoxy(16,3);
	cout << "     S I S T E M A        B A N C A R I O";
	menu();
	return 0;
}


//FUNCION MENU: IMPRIME LAS OPCIONES DEL MENU PRINCIPAL POR PANTALLA, Y PERMITE QUE EL USUARIO INGRESE UNA OPCIÓN
void menu(){
	char op,op2;
	limpia();
	CursorOn(1,10);
	do{
		gotoxy(4,6); cout << "SOCIOS                           CUENTA                           CERRAR";
		gotoxy(4,9); cout << "MENU PRINCIPAL";
		gotoxy(4,11); cout << "(1) Socios";
		gotoxy(4,13); cout << "(2) Cuenta";
		gotoxy(4,15); cout << "(3) Cerrar";
		gotoxy(4,18); cout << "Ingrese opcion: ";
		cin >> op;
		
		if(op!='1' && op!='2' && op!='3'){
			gotoxy(4,22); cout << "Error al ingresar valores. Presione una tecla para volver a ingresar..";
			CursorOff();
			getch();
			gotoxy(4,22); cout << "                                                                       ";
			gotoxy(4,18); cout << "                                                                       ";
			CursorOn(1,10);	
		}
			
	}while(op!='1' && op!='2' && op!='3');
	
	
	if (op=='1'){
			limpia();
			do{
				gotoxy(4,6); cout << "SOCIOS                           CUENTA                           CERRAR";
				gotoxy(4,8); cout << "1. Registrar";
				gotoxy(4,10); cout << "2. Actualizar";
				gotoxy(4,12); cout << "3. Eliminar";
				gotoxy(4,14); cout << "4. Consultar";
				gotoxy(4,16); cout << "5. Volver";
				gotoxy(4,20); cout << "Ingrese opcion: ";
				cin >> op2;
				
				if(op2!='1' && op2!='2' && op2!='3' && op2!='4' && op2!='5'){
					gotoxy(4,22); cout << "Error al ingresar valores. Presione una tecla para volver a ingresar..";
					CursorOff();
					getch();
					gotoxy(4,22); cout << "                                                                       ";
					gotoxy(4,20); cout << "                                      ";
					CursorOn(1,10);	
				}
			
			}while(op2!='1' && op2!='2' && op2!='3' && op2!='4' && op2!='5');
		
		if (op2=='1') ingreso();   //AQUÍ SE LLAMA AL MÉTODO INGRESO
		if (op2=='2') actualizar();   //AQUÍ SE LLAMA AL MÉTODO ACTUALIZAR
		if (op2=='3') eliminar();     //AQUÍ SE LLAMA AL MÉTODO ELIMINAR
		if (op2=='4') consultar();    //AQUÍ SE LLAMA AL MÉTODO CONSULTAR
		if (op2=='5') menu();
	}	
	
	
	if (op=='2'){
			limpia();
			do{
			gotoxy(4,6); cout << "SOCIOS                           CUENTA                           CERRAR";
			gotoxy(37,8); cout << "TRANSACCIONES";
			gotoxy(37,10); cout << "1. Deposito";
			gotoxy(37,12); cout << "2. Retiro";
			gotoxy(37,14); cout << "3. Movimientos";
			gotoxy(37,16); cout << "4. Volver";

			gotoxy(37,19); cout << "Ingrese opcion: ";
			cin >> op2;
			
			if(op2!='1' && op2!='2' && op2!='3'&& op2!='4') {
				gotoxy(4,22); cout << "Error al ingresar valores. Presione una tecla para volver a ingresar..";
				CursorOff();
				getch();
				gotoxy(4,22); cout << "                                                                       ";
				gotoxy(37,19); cout << "                             ";
				CursorOn(1,10);	
			}
			
	}while(op2!='1' && op2!='2' && op2!='3' && op2!='4');
	
		if (op2=='1') deposito();         
		if (op2=='2') retiro();
		if (op2=='3') libreta();
		if (op2=='4') menu();
	}
	
	
	if (op=='3')
		exit(0);
	
}


// FUNCION INGRESO DE DATOS: ESTA FUNCIÓN PERMITE INGRESAR LOS DATOS DEL SOCIO, Y LA CREACIÓN DE LOS ARCHIVOS QUE LOS LLAMAREMOS ARCHIVO BINARIO Y SOCIOS, QUE ALMACENARÁN ESTOS DATOS PARA QUE UNA VEZ SE CIERRE EL PROGRAMA, ESTOS QUEDEN GUARDADOS.
void ingreso(){
	FILE *pa, *pa2;                                              //AQUI SE CREAN 2 VARIABLEs DE TIPO APUNTADOR CON EL NOMBRE PA Y PA2. ES DECIR, UNA VARIABLE PARA CADA ARCHIVO..
	char r;                                                      //..LA CUEAL VA A CONTENER LA DIRECCION FISICA DE LOS ARCHIVOS UTILIZADOS
	socio nuevo, lista[50];                                      //AQUÍ SE CREAN DOS OBJETOS DE LA CLASES CLIENTE, UNO ES NUEVO Y EL OTRO ES UN ARRAY O VECTOR LLAMADO LISTA..
	limpia();                                                    //..EL OBJETO NUEVO NOS PERMITERÁ ALMACENAR LOS DATOS EN LAS VARIABLES, PARA LUEGO GUARDARLOS EN EL ARCHIVO, MÁS ABAJO SE INDICE LA LINEA DONDE SE GUARDAN.
	if (((pa = fopen("Archivo Binario","a+b"))==NULL) || ((pa2 = fopen("Socios","a+b"))==NULL))         //FUNCION FOPEN: PERMITE CREAR Y/O ABRIR UN ARCHIVO, SE CREAN 2 ARCHIVOS, UNO BINARIO Y EL OTRO DE TEXTO , EL DE TEXTO PERMITE LEER LOS CARACTERES DEL TECLADO NORMAL
	{ cout << "No se puede abrir el archivo";
		return ;
		}

	int encontro=1,i,ultimo,res;

	rewind(pa); 
	i=0;
	
	while(!feof(pa))                                             //CON ESTE WHILE, SE VA A RECORRER TODO EL ARCHIVO, USAMOS LA FUNCION FEOF PARA RECORRER, LA CUAL RETORNA UN VALOR DISTINTO A CERO SI Y SOLO SI EL INDICADOR A LLEGADO AL FINAL DEL ARCHIVO
	{ if(fread(&nuevo, sizeof(socio), 1, pa)){                   //LA FUNCION FREAD, DEVUELVE EL NUMERO DE ELEMENTOS LEIDOS EN EL ARCHIVO, POR LO TANTO ESTE NUMERO NOS SIRVE PARA INDICARLE AL ARRAY CUANTAS POSICIONES TENDRÁ
		lista[i]=nuevo;                                          //TODA LA INFORMACION ALMACENADA EN NUEVO SE LA GUARDARA EN EL ARRAY LISTA..
		i++;}                                                    //.. ESTO SE LO HACE PARA LUEGO COMPARAR
	}

	fflush(stdin);
	gotoxy(4,8);cout << "REGISTRO DE SOCIOS";
	gotoxy(4,10);cout << "Nombres y apellidos:  "; gets(nuevo.nombre);

	gotoxy(4,12);cout << "DNI:                  ";
		res=i;
		do{
			gotoxy(26,12); gets(nuevo.cedula);
			//proceso de busqueda de la informaci¢n
			ultimo=res-1;
			i=0;
			encontro=1;
			while (i<=ultimo && encontro){
				if (strcmp(lista[i].cedula,nuevo.cedula)==0) encontro=0;              //COMPARA EL DNI INGRESADO POR TECLADO , CON LOS DNI DEL ARRAY LISTA
				else i++;
			}
			if (i<=ultimo){
				gotoxy(26,12);cout << "                              ";
				gotoxy(4,22);cout << "DNI ya ingresado. Ingrese nuevamente.";}
			else {gotoxy(4,22); cout << "                                               ";
			}
		}
		while(i<=ultimo);

	gotoxy(4,14);cout << "Ciudad:               "; gets(nuevo.ciudad);
	gotoxy(4,16);cout << "Telefono:             "; gets(nuevo.telefono);
	
	do{
		CursorOff();
		gotoxy(4,22);cout << "¨Registrar Nuevo Socio? Si[s] / No [n]: "; 
		r=getch();
	}while(r!='S' && r!='s' && r!='N' && r!='n');
	
	
	if (r=='s' || r=='S') {
		fwrite(&nuevo, sizeof(socio),1,pa);                                                            //AQUI SE GUARDAN LOS DATOS EN EL ARCHIVO LLAMADO ARCHIVO BINARIO , LA FUNCIÓN FWRITE PERMITE GUARDAR INFORMACIÓN CONTENIDA EN LAS VARIABLES A UN ARCHIVO DESTINO
		fprintf(pa2, "%s %s %s %s\n", nuevo.nombre, nuevo.cedula, nuevo.ciudad, nuevo.telefono);       //AQUI SE GUARDAN LOS DATOS EN EL ARCHIVO DE TEXTO LLAMADO ARCHIVO DATOS, LA FUNCION FPRINTF AL IGUAL QUE LA FWRITE GUARDA INFORMACION EN LAS VARIABLES
		gotoxy(4,22);cout << "                                             "; 
		gotoxy(4,22);cout << "Socio Registrado Correctamente. Presione una tecla para volver..";
	}
	else {
		gotoxy(4,22);cout << "Socio NO Registrado. Presione una tecla para volver..";
	}
	
	fclose(pa);
	fclose(pa2);
	CursorOff();
	getch();
	limpia();
	menu();
}


// FUNCION ACTUALIZAR: PERMITE MODIFICAR DATOS DEL SOCIO
void actualizar(){ 
	socio nuevo, lista[50];
  	char cedula[15];
  	int encontro=1,linea,i,ultimo;
  	char r;
  	FILE *pa, *pa2;
  	limpia();
  	if ((pa = fopen("Archivo Binario", "a+b"))== NULL){ 
		cout << "No se puede abrir el archivo.\n";
		return;
    }
  	rewind(pa); i=0;
  	
	while(!feof(pa)){ 
		if(fread(&nuevo, sizeof(socio), 1, pa)){
	 		lista[i]=nuevo;
	 		i++;
		}
  	}
  	fclose(pa);
  

  	//proceso de busqueda de la informaci¢n
  	gotoxy(4,8);cout << "ACTUALIZAR DATOS";
  	gotoxy(4,10);
  	fflush(stdin);
  	cout << "Ingrese Numero De DNI: "; gets(cedula);
  	ultimo=i-1;
  	i=0;
  	while (i<=ultimo && encontro){ 
		if (strcmp(lista[i].cedula,cedula)==0) 
			encontro=0;
    	else 
			i++;
  	}
  	
  	if (i<=ultimo){ 
		do {
			CursorOn(1,10);
		    limpia();
		    gotoxy(4,8);cout << "ACTUALIZAR DATOS";
		    gotoxy(4,10);cout << "1. Nombre:   " << lista[i].nombre;
		    gotoxy(4,12);cout << "2. DNI:      " << lista[i].cedula;
		    gotoxy(4,14);cout << "3. Ciudad:   " << lista[i].ciudad;
		    gotoxy(4,16);cout << "4. Telefono: " << lista[i].telefono;
		    gotoxy(4,20);cout << "Escriba la linea a modificar: ";
	    	
			do{
		       gotoxy(34,20); cin >> linea;
		       if(linea<1 || linea>4) {
		       	gotoxy(34,20);cout << "          ";
		       	gotoxy(4,22);cout << "Opcion no valida. Ingrese nuevamente..";
			   }
		    }while(linea<1 || linea>4);
		    gotoxy(4,22);cout << "                                            ";
		    
			fflush(stdin);
			
		    switch(linea){
			    case 1: gotoxy(4,10 );cout << "                                                       ";
				    gotoxy(4,10 );
				    cout << "1. Nombre:   ";
				    gets(lista[i].nombre);
				    break;
			    case 2: gotoxy(4,12 );cout << "                              ";
				    gotoxy(4,12);
				    cout << "2. DNI:      ";
				    gets(lista[i].cedula);
				    break;
			    case 3: gotoxy(4,14);cout << "                              ";
				    gotoxy(4,14);
				    cout << "3. Ciudad:   ";
				    gets(lista[i].ciudad);
				    break;
			    case 4: gotoxy(4,16);cout << "                              ";
				    gotoxy(4,16);
				    cout << "4. Telefono: ";
				    gets(lista[i].telefono);
		    }
		    gotoxy(4,20);cout << "Actualizacion Correcta.                  ";
		    
			do{
				CursorOff();
				gotoxy(4,22);cout << "¨Desea Seguir Actualizando? Si[s] / No[n]: ";
				r=getch();
			}while(r!='S' && r!='s' && r!='N' && r!='n');
		    
		    
		}while (r!='n' && r!='N');
		
	    // Abrir el archivo para Sobrescribir
	    if (((pa = fopen("Archivo Binario", "wb"))== NULL) || ((pa2 = fopen("Socios", "wb"))== NULL)){ 
			cout << "No se puede abrir el archivo.";
			return;
	    }
	    i=0;
	    
		while(i<=ultimo){ 
			fwrite(&lista[i], sizeof(socio), 1, pa);
	    	fprintf(pa2, "%s %s %s %s\n", lista[i].nombre, lista[i].cedula, lista[i].ciudad, lista[i].telefono);
	      	i++;
	    }
	    fclose(pa);
		fclose(pa2);
	    gotoxy(4,22);cout << "Presione una tecla para volver...                   ";
	    CursorOff();
		getch();
		limpia();
		menu();
  	}
  	
	else{ 
	  	fclose(pa);
		gotoxy(4,22);cout << "Socio NO registrado. Presione una tecla para volver... ";
	    CursorOff();
		getch();
		limpia();
		menu();
  	}
}


//FUNCION ELIMINAR: PERMITE ELIMINAR SOCIOS
void eliminar(){ 
	socio nuevo, lista[50];
  	char cedula[15];
  	char r;
  	int encontro=1,linea,i,ultimo;
  	FILE *pa, *pa2;
  	limpia();
  	
	if ((pa = fopen("Archivo Binario", "a+b"))== NULL)
    { 
		cout << "No se puede abrir el archivo";
		return;
    }
  	rewind(pa); i=0;
  	while(!feof(pa))
  	{ 
		if(fread(&nuevo, sizeof(socio), 1, pa)){
			lista[i]=nuevo;
			i++;
		}
  	}
  	fclose(pa);
 
  	//proceso de busqueda de la informaci¢n
  	gotoxy(4,8);cout << "ELIMINAR DATOS";
  	gotoxy(4,10);
  	fflush(stdin);
  	cout << "Ingrese Numero De DNI: "; gets(cedula);
  	ultimo=i-1;
  	i=0;
  	while (i<=ultimo && encontro)
  	{ 
		if (strcmp(lista[i].cedula,cedula)==0) 
			encontro=0;
    	else 
			i++;
  	}
  	
	if (i<=ultimo)
  	{
	    limpia();
	    gotoxy(4,8);cout << "ELIMINAR SOCIO";
	    gotoxy(4,10);cout << "Nombre:   " << lista[i].nombre;
	    gotoxy(4,12);cout << "DNI:      " << lista[i].cedula;
	    gotoxy(4,14);cout << "Ciudad:   " << lista[i].ciudad;
	    gotoxy(4,16);cout << "Telefono: " << lista[i].telefono;
	    
		do{	
			CursorOff();
			gotoxy(4,22); cout << "¨Desea Eliminarlo? Si[s] / No[n]: ";
			r=getch();
		}while(r!='S' && r!='s' && r!='N' && r!='n');
		
	    if (r=='s' || r=='S'){ 
			while (i<ultimo) {
			    lista[i]=lista[i+1];
			    i++;
			}
			ultimo=i-1;
			
			if (((pa = fopen("Archivo Binario", "wb"))== NULL) || ((pa2 = fopen("Socios", "wb"))== NULL))
			  {	cout << "No se puede abrir el archivo.";
				return;
			  }
			i=0;
			
			while(i<=ultimo)
			{ 
				fwrite(&lista[i], sizeof(socio), 1, pa);
				fprintf(pa2, "%s %s %s %s\n", lista[i].nombre, lista[i].cedula, lista[i].ciudad, lista[i].telefono);
				i++;
			}
			
			fclose(pa);
			fclose(pa2);
			gotoxy(4,22); cout << "                                            ";
			gotoxy(4,22);cout << "Socio Eliminado. Presione una tecla para volver..";
			CursorOff();
			getch();
			limpia();
			menu();
	    }
	    
	    else{
	    	gotoxy(4,22); cout << "                                          ";
			gotoxy(4,22);cout << "Socio NO Eliminado. Presione una tecla para volver..";
			CursorOff();
			getch();
			limpia();
			menu();
		}
  	}
  	
  	else{ 

		gotoxy(4,22);cout << "Socio NO Registrado. Presione una tecla para volver..";
	    CursorOff();
		getch();
		limpia();
		menu();
  	}
  	

}


// FUNCION CONSULTAR: REALIZA LA CONSULTA DEL CLIENTE, SE INGRESA EL DNI , Y ESTE NOS MUESTRA TODA LA INFORMACION DEL SOCIO
void consultar(){ 
	socio nuevo, lista[50];
	char cedula[15];
	int encontro=1,linea,i,ultimo;
	FILE *pa;
	limpia();
	if ((pa = fopen("Archivo Binario", "a+b"))== NULL){ 
		cout << "No se puede abrir el archivo.";
		return;
	}
	rewind(pa); i=0;
	while(!feof(pa))
	{ 
		if(fread(&nuevo, sizeof(socio), 1, pa)){
			lista[i]=nuevo;
		 	i++;
		}
	}
	fclose(pa);
 
  	//proceso de busqueda de la informaci¢n
  	gotoxy(4,8);cout << "CONSULTA DE SOCIOS";
  	gotoxy(4,10);
  	fflush(stdin);
  	cout << "Ingrese Numero De DNI: "; gets(cedula);
  	ultimo=i-1;
  	i=0;
  	while (i<=ultimo && encontro)
  	{ 
	  	if (strcmp(lista[i].cedula,cedula)==0) encontro=0;
    	else i++;
  	}
  	if (i<=ultimo)
 	{
	    limpia();
	    gotoxy(4,8);cout << "CONSULTA DE SOCIOS";
	    gotoxy(4,10);cout << "Nombre:   " << lista[i].nombre;
	    gotoxy(4,12);cout << "DNI:      " << lista[i].cedula;
	    gotoxy(4,14);cout << "Ciudad:   " << lista[i].ciudad;
	    gotoxy(4,16);cout << "Telefono: " << lista[i].telefono;
	
	    gotoxy(4,22);cout << "Presione una tecla para volver...                   ";
	    CursorOff();
		getch();
		limpia();
		menu();
  	}
  	
  	else
  	{ 
		gotoxy(4,22);cout << "Socio NO registrado. Presione una tecla para volver... ";
	    CursorOff();
		getch();
		limpia();
		menu();
  	}
}




//FUNCION DEPOSITO
void deposito(){
  	limpia();
  	gotoxy(4,8);cout << "TRANSACCIONES: DEPOSITO";

  	socio nuevo, lista[50];
  	char cedula[15];
  	int encontro=1,i,ultimo;
  	FILE *pa;
  	if ((pa = fopen("Archivo Binario", "a+b"))== NULL)
    { cout << "No se puede abrir el archivo.";
		return;
    }
  	rewind(pa); i=0;
  	while(!feof(pa))
  	{ if(fread(&nuevo, sizeof(socio), 1, pa)){
		lista[i]=nuevo;
		i++;
	}
	}
  	fclose(pa);

  	//proceso de busqueda de la informaci¢n
  	gotoxy(4,10);
  	fflush(stdin);
  	cout << "Ingrese Numero De DNI: "; gets(cedula);
  	ultimo=i-1;
  	i=0;
  	while (i<=ultimo && encontro)
  	{ if (strcmp(lista[i].cedula,cedula)==0) encontro=0;
    	else i++;
  	}
  	if (i<=ultimo)
  	{
    	gotoxy(4,10);cout << "                                              ";
    	gotoxy(4,10);cout << "Cuenta perteneciente a:   " << lista[i].nombre;

  	//Almacenar datos en estructura 2
  	char cedula2[15], nombre[35];
  	strcpy(cedula2,cedula);
  	strcpy(nombre, lista[i].nombre);

  	FILE *da, *da2;
  	transacciones nuevot, listat[50];
  	if (((da = fopen("Archivo Binario 2", "a+b"))== NULL) || ((da2 = fopen("Transaccion", "a+b"))== NULL))
  	{ cout << "No se puede abrir el archivo.";
  		return ;
  	}
  	rewind(da); i=0;
  	while(!feof(da))
  	{ if(fread(&nuevot, sizeof(transacciones), 1, da)){
		listat[i]=nuevot;
		i++;
	 	}
  	}
  	encontro=1;
  	ultimo=i-1;
  	i=0;
  
  	while (i<=ultimo && encontro)
  	{ if (strcmp(listat[i].cedula,cedula2)==0) encontro=0;
    	else i++;
  	}
  	if (i<=ultimo){
		gotoxy(4,12); printf("Saldo:                    $ %6.2f",listat[i].valorinicial);
		gotoxy(4,14); cout << "Valor a depositar:        $  ";
		do{
			//gotoxy(33,14); cin >> %f",&listat[i].transacc);
			gotoxy(33,14); cin >> listat[i].transacc;
			if (listat[i].transacc <= 0)
			{ 
				gotoxy(33,14); cout << "                               ";
			}
		}while(listat[i].transacc <= 0);
		
		listat[i].valorinicial += listat[i].transacc;
		fflush(stdin);
		gotoxy(4,16);cout << "Ingrese fecha:            dd/mm/aaaa"; gotoxy(30,16);gets(listat[i].fecha);
		limpia();
		dibujarCuadro(13,8,63,19);
		gotoxy(20,10);cout << "      COMPROBANTE DE DEPOSITO";
		gotoxy(20,12);cout << "DNI:                " << listat[i].cedula;
		gotoxy(20,13);cout << "Nombre:             " << listat[i].nombre;
		gotoxy(20,14);printf("Monto:              $ %6.2f",listat[i].transacc);
		gotoxy(20,15);printf("Saldo actual:       $ %6.2f",listat[i].valorinicial);
		gotoxy(20,16);cout << "Cajero:             Jose Fuentes";
		gotoxy(20,17);cout << "Fecha:              " << listat[i].fecha;
	
		//Abrir el archivo para sobreescribir
		if (((da = fopen("Archivo Binario 2", "wb"))== NULL) || ((da2 = fopen("Transaccion", "wb"))== NULL)){
			cout << "No se puede abrir el archivo.";
			return;}
		i=0;
		
		while(i<=ultimo){
			fwrite(&listat[i], sizeof(transacciones), 1, da);
			fprintf(da2, "%s %s %s %f %f\n", listat[i].cedula, listat[i].nombre, listat[i].fecha, listat[i].transacc, listat[i].valorinicial);
			i++;
		}
		fclose(da);
		fclose(da2);
	
		//LIBRETA DE AHORROS: PROCESO
	
		int encontro=1,i,ultimo;
		transacciones nuevof, listaf[50];
		FILE *fa, *fa2;
		if ((fa = fopen("Archivo Binario 2", "a+b"))== NULL){
			cout << "No se puede abrir el archivo.";
			return;}
		rewind(fa); i=0;
		while(!feof(fa)){
			if(fread(&nuevof, sizeof(transacciones), 1, fa)){
				listaf[i]=nuevof;
				i++;}
		}
		fclose(fa);
	
		//proceso de busqueda de la informaci¢n
		ultimo=i-1;
		i=0;
		while (i<=ultimo && encontro){
			if (strcmp(listaf[i].cedula,cedula2)==0) encontro=0;
			else i++; 
		}
		
		if (i<=ultimo){
			char f[15], t[10] = "Deposito";
			float tra, sald;
	
			strcpy(f,listaf[i].fecha);
			tra = listaf[i].transacc;
			sald = listaf[i].valorinicial;
	
			//SE CREAN DOS NUEVOS ARCHIVOS PARA PASAR LA INFORMACIÓN
			FILE *ka, *ka2;
			fechae nuevoj;
			if (((ka = fopen("Archivo Binario 3", "a+b"))== NULL) || ((ka2 = fopen("Saldo", "a+b"))== NULL)){
				cout << "No se puede abrir el archivo.";
				return ;
			}
			strcpy(nuevoj.cedulaf,cedula2);
			strcpy(nuevoj.nombref,nombre);
			strcpy(nuevoj.fechaf,f);
			strcpy(nuevoj.tipof,t);
			nuevoj.transaccf = tra;
			nuevoj.saldof = sald;
	
			fwrite(&nuevoj, sizeof(fechae),1,ka);
			fprintf(ka2, "%s %s %s %s %f %f\n", nuevoj.cedulaf, nuevoj.nombref, nuevoj.fechaf,  nuevoj.tipof, nuevoj.transaccf, nuevoj.saldof);
			fclose(ka);
			fclose(ka2);
		}
	}



  	else{
		strcpy(nuevot.cedula,cedula2);
		strcpy(nuevot.nombre,nombre);
	
		nuevot.valorinicial = 0;
		gotoxy(4,12);printf("Saldo:                    $ %6.2f",nuevot.valorinicial);
		gotoxy(4,14);cout << "Valor a depositar:        $  ";
		
		do{
			//gotoxy(33,14); cin >> %f",&nuevot.transacc);
			gotoxy(33,14); cin >> nuevot.transacc;
			if(nuevot.transacc <= nuevot.valorinicial)
				{ gotoxy(33,14);cout << "                           ";}
		}while(nuevot.transacc <= nuevot.valorinicial);
		
		nuevot.valorinicial += nuevot.transacc;
		fflush(stdin);
		gotoxy(4,16);cout << "Fecha:                    dd/mm/aaaa"; gotoxy(30,16); gets(nuevot.fecha);
		limpia();
		dibujarCuadro(13,8,63,19);
		gotoxy(20,10); cout << "      COMPROBANTE DE DEPOSITO";
		gotoxy(20,12);cout << "DNI:            " << nuevot.cedula;
		gotoxy(20,13);cout << "Nombre:         " << nuevot.nombre;
		gotoxy(20,14);printf("Monto:          $ %6.2f",nuevot.transacc);
		gotoxy(20,15);printf("Saldo actual:   $ %6.2f",nuevot.valorinicial);
		gotoxy(20,16);cout << "Cajero:         Jose Fuentes";
		gotoxy(20,17);cout << "Fecha:          ",nuevot.fecha;
	
		fwrite(&nuevot, sizeof(transacciones),1,da);
		fprintf(da2, "%s %s %s %f %f\n", nuevot.cedula, nuevot.nombre, nuevot.fecha, nuevot.transacc, nuevot.valorinicial);
		fclose(da);
		fclose(da2);
	
		//LIBRETA DE AHORROS: PROCESO
	
		int encontro=1,i,ultimo;
		transacciones nuevof, listaf[50];
		FILE *fa;
		if ((fa = fopen("Archivo Binario 2", "a+b"))== NULL){
			cout << "No se puede abrir el archivo.";
			return;}
		rewind(fa); i=0;
		while(!feof(fa)){
			if(fread(&nuevof, sizeof(transacciones), 1, fa)){
				listaf[i]=nuevof;
				i++;}
		}
		fclose(fa);
	
		//proceso de busqueda de la informaci¢n
		ultimo=i-1;
		i=0;
		while (i<=ultimo && encontro){
			if (strcmp(listaf[i].cedula,cedula2)==0) 
				encontro=0;
			else 
				i++; 
			}
		
		if (i<=ultimo){
			char f[15], t[10] = "Deposito";
			float tra, sald;
	
			strcpy(f,listaf[i].fecha);
			tra = listaf[i].transacc;
			sald = listaf[i].valorinicial;
	
			//SE CREAN DOS NUEVOS ARCHIVOS PARA PASAR LA INFORMACIÓN
			FILE *ka, *ka2;
			fechae nuevoj;
			
			if (((ka = fopen("Archivo Binario 3", "a+b"))== NULL) || ((ka2 = fopen("Saldo", "a+b"))== NULL)){
				cout << "No se puede abrir el archivo.";
				return ;
			}
			
			strcpy(nuevoj.cedulaf,cedula2);
			strcpy(nuevoj.nombref,nombre);
			strcpy(nuevoj.fechaf,f);
			strcpy(nuevoj.tipof,t);
			nuevoj.transaccf = tra;
			nuevoj.saldof = sald;
	
			fwrite(&nuevoj, sizeof(fechae),1,ka);
			fprintf(ka2, "%s %s %s %s %f %f\n", nuevoj.cedulaf, nuevoj.nombref, nuevoj.fechaf,  nuevoj.tipof, nuevoj.transaccf, nuevoj.saldof);
			fclose(ka);
			fclose(ka2);
		}
	}

  	gotoxy(4,22);cout << "Presione una tecla para volver... ";
  	CursorOff();
	getch();
	limpia();
	menu();}
  	
	else{
    	gotoxy(4,22);cout << "Socio NO Registrado. Presione una tecla para volver... ";
      	CursorOff();
		getch();
		limpia();
		menu();
	}
}



//FUNCIÓN RETIRO: PERMITE REALIZAR RETIROS DE LAS CUENTAS DE LOS SOCIOS
void retiro(){
  	limpia();
  	gotoxy(4,8);cout << "TRANSACCIONES: RETIRO";

  	socio nuevo, lista[50];
  	char cedula[15];
  	int encontro=1,i,ultimo;
  	FILE *pa;
  	if ((pa = fopen("Archivo Binario", "a+b"))== NULL)
    { cout << "No se puede abrir el archivo.";
		return;
    }
  	rewind(pa); i=0;
  	while(!feof(pa))
  	{ if(fread(&nuevo, sizeof(socio), 1, pa)){
		lista[i]=nuevo;
	 	i++;
		}
  	}
  	fclose(pa);


  	//proceso de busqueda de la informaci¢n
  	gotoxy(4,10);
  	fflush(stdin);
  	cout << "Ingrese Numero De DNI: "; gets(cedula);
  	ultimo=i-1;
  	i=0;
  	while (i<=ultimo && encontro)
  	{ if (strcmp(lista[i].cedula,cedula)==0) encontro=0;
    	else i++;
  	}
  	if (i<=ultimo)
  	{
    	gotoxy(4,10);cout << "                                              ";
    	gotoxy(4,10);cout << "Cuenta perteneciente a:   " << lista[i].nombre;

  	//Almacenar datos en estructura 2
  	char cedula2[15], nombre[35];
  	strcpy(cedula2,cedula);
  	strcpy(nombre, lista[i].nombre);

  	FILE *da, *da2;
  	transacciones nuevot, listat[50];
  	if (((da = fopen("Archivo Binario 2", "a+b"))== NULL) || ((da2 = fopen("Transaccion", "a+b"))== NULL))
  	{ cout << "No se puede abrir el archivo.";
  		return ;
  	}
  	rewind(da); i=0;
  	
	  while(!feof(da))
  	{ if(fread(&nuevot, sizeof(transacciones), 1, da)){
		listat[i]=nuevot;
		i++;
	}
  	}
  	encontro=1;
  	ultimo=i-1;
  	i=0;
  	while (i<=ultimo && encontro)
  	{ if (strcmp(listat[i].cedula,cedula2)==0) 
		encontro=0;
	else 
		i++;
  	}
  	
	if (i<=ultimo){
		gotoxy(4,12);printf("Saldo:                    $ %6.2f",listat[i].valorinicial);
		gotoxy(4,14);cout << "Valor a retirar:          $  ";
		
		do{
		gotoxy(33,14);cin >> listat[i].transacc;
			if(listat[i].transacc > listat[i].valorinicial || listat[i].transacc < 0){ 
				gotoxy(33,14);cout << "                  ";
			}
		} while(listat[i].transacc > listat[i].valorinicial || listat[i].transacc < 0);
		
		listat[i].valorinicial -= listat[i].transacc;
		fflush(stdin);
		gotoxy(4,16);cout << "Ingrese fecha:            dd/mm/aaaa"; gotoxy(30,16);gets(listat[i].fecha);
		limpia();
		dibujarCuadro(13,8,63,19);
		gotoxy(20,10);cout << "      COMPROBANTE DE RETIRO";
		gotoxy(20,12);cout << "DNI:                " << listat[i].cedula;
		gotoxy(20,13);cout << "Nombre:             " << listat[i].nombre;
		gotoxy(20,14);printf( "Monto:              $ %6.2f",listat[i].transacc);
		gotoxy(20,15);printf("Saldo actual:       $ %6.2f",listat[i].valorinicial);
		gotoxy(20,16);cout << "Cajero:             Jose Fuentes";
		gotoxy(20,17);cout << "Fecha:              ",listat[i].fecha;
	
		//Abrir el archivo para sobreescribir
		if (((da = fopen("Archivo Binario 2", "wb"))== NULL) || ((da2 = fopen("Transaccion", "wb"))== NULL)){
			cout << "No se puede abrir el archivo.";
			return;
		}
		i=0;
		
		while(i<=ultimo){
			fwrite(&listat[i], sizeof(transacciones), 1, da);
			fprintf(da2, "%s %s %s %f %f\n", listat[i].cedula, listat[i].nombre, listat[i].fecha, listat[i].transacc, listat[i].valorinicial);
			i++;
		}
		fclose(da);
		fclose(da2);
	
		//LIBRETA DE AHORROS: PROCESO
	
		int encontro=1,i,ultimo;
		transacciones nuevof, listaf[50];
		FILE *fa;
		if ((fa = fopen("Archivo Binario 2", "a+b"))== NULL){
			cout << "No se puede abrir el archivo.";
			return;}
		rewind(fa); i=0;
		while(!feof(fa)){
			if(fread(&nuevof, sizeof(transacciones), 1, fa)){
				listaf[i]=nuevof;
				i++;}
		}
		fclose(fa);
	
		//proceso de busqueda de la informaci¢n
		ultimo=i-1;
		i=0;
		while (i<=ultimo && encontro){
			if (strcmp(listaf[i].cedula,cedula2)==0) encontro=0;
			else i++; }
		if (i<=ultimo){
			char f[15], t[10] = "Retiro";
			float tra, sald;
	
			strcpy(f,listaf[i].fecha);
			tra = listaf[i].transacc;
			sald = listaf[i].valorinicial;
	
		//SE CREAN DOS NUEVOS ARCHIVOS PARA PASAR LA INFORMACIÓN
			FILE *ka, *ka2;
			fechae nuevoj;
			if (((ka = fopen("Archivo Binario 3", "a+b"))== NULL) || ((ka2 = fopen("Saldo", "a+b"))== NULL)){
				cout << "No se puede abrir el archivo.";
				return ;
			}
			strcpy(nuevoj.cedulaf,cedula2);
			strcpy(nuevoj.nombref,nombre);
			strcpy(nuevoj.fechaf,f);
			strcpy(nuevoj.tipof,t);
			nuevoj.transaccf = tra;
			nuevoj.saldof = sald;
	
			fwrite(&nuevoj, sizeof(fechae),1,ka);
			fprintf(ka2, "%s %s %s %s %f %f\n", nuevoj.cedulaf, nuevoj.nombref, nuevoj.fechaf,  nuevoj.tipof, nuevoj.transaccf, nuevoj.saldof);
			fclose(ka);
			fclose(ka2);
		}
	}


  	else{
		strcpy(nuevot.cedula,cedula2);
		strcpy(nuevot.nombre,nombre);
	
		nuevot.valorinicial = 0;
		gotoxy(4,12);printf("Saldo:                    $ %6.2f",nuevot.valorinicial);
		gotoxy(4,14);cout << "Valor a retirar:          $  ";
		do{
		gotoxy (34,14); cin >> nuevot.transacc;
		if (nuevot.transacc > nuevot.valorinicial || nuevot.transacc < 0)
			{ gotoxy(33,14); cout << "                             ";}
		} while(nuevot.transacc > nuevot.valorinicial || nuevot.transacc < 0);
		nuevot.valorinicial -= nuevot.transacc;
		fflush(stdin);
		gotoxy(4,16);cout << "Fecha:                    dd/mm/aaaa"; gotoxy(30,16); gets(nuevot.fecha);
		limpia();
		dibujarCuadro(13,8,63,19);
		gotoxy(20,10); cout << "      COMPROBANTE DE RETIRO";
		gotoxy(20,12);cout << "DNI:            " << nuevot.cedula;
		gotoxy(20,13);cout << "Nombre:         " << nuevot.nombre;
		gotoxy(20,14);cout << "Monto:          $ %6.2f",nuevot.transacc;
		gotoxy(20,15);cout << "Saldo actual:   $ %6.2f",nuevot.valorinicial;
		gotoxy(20,16);cout << "Cajero:         Jose Fuentes";
		gotoxy(20,17);cout << "Fecha:          " << nuevot.fecha;
	
		fwrite(&nuevot, sizeof(transacciones),1,da);
		fprintf(da2, "%s %s %s %f %f\n", nuevot.cedula, nuevot.nombre, nuevot.fecha, nuevot.transacc, nuevot.valorinicial);
		fclose(da);
		fclose(da2);
	
		//LIBRETA DE AHORROS: PROCESO
	
		int encontro=1,i,ultimo;
		transacciones nuevof, listaf[50];
		FILE *fa;
		if ((fa = fopen("Archivo Binario 2", "a+b"))== NULL){
			cout << "No se puede abrir el archivo.";
			return;}
		rewind(fa); i=0;
		while(!feof(fa)){
			if(fread(&nuevof, sizeof(transacciones), 1, fa)){
				listaf[i]=nuevof;
				i++;}
		}
		fclose(fa);
	
		//proceso de busqueda de la informaci¢n
		ultimo=i-1;
		i=0;
		while (i<=ultimo && encontro){
			if (strcmp(listaf[i].cedula,cedula2)==0) encontro=0;
			else i++; }
		if (i<=ultimo){
			char f[15], t[10] = "Retiro";
			float tra, sald;
	
			strcpy(f,listaf[i].fecha);
			tra = listaf[i].transacc;
			sald = listaf[i].valorinicial;
	
		//SE CREAN DOS NUEVOS ARCHIVOS PARA PASAR LA INFORMACIÓN
			FILE *ka, *ka2;
			fechae nuevoj;
			if (((ka = fopen("Archivo Binario 3", "a+b"))== NULL) || ((ka2 = fopen("Saldo", "a+b"))== NULL)){
				cout << "No se puede abrir el archivo.";
				return ;
			}
			strcpy(nuevoj.cedulaf,cedula2);
			strcpy(nuevoj.nombref,nombre);
			strcpy(nuevoj.fechaf,f);
			strcpy(nuevoj.tipof,t);
			nuevoj.transaccf = tra;
			nuevoj.saldof = sald;
	
			fwrite(&nuevoj, sizeof(fechae),1,ka);
			fprintf(ka2, "%s %s %s %s %f %f\n", nuevoj.cedulaf, nuevoj.nombref, nuevoj.fechaf,  nuevoj.tipof, nuevoj.transaccf, nuevoj.saldof);
			fclose(ka);
		}
	}



  	gotoxy(4,22);cout << "Presione una tecla para volver... ";
  	CursorOff();
	getch();
	limpia();
	menu();}
  
  	else{
    	gotoxy(4,22);cout << "Socio NO Registrado. Presione una tecla para volver... ";
    	CursorOff();
		getch();
		limpia();
		menu();
	}
}


//LIBRETA DE AHORROS
void libreta(){
	fechae li,listal[50];
	char cedula[15];
	int i,ultimo,res;
	FILE *fe;
	limpia();
	if ((fe = fopen("Archivo Binario 3", "a+b"))== NULL)
	{ 	cout << "No se puede abrir el archivo.\n";
		return; }
	rewind(fe); i=0;
	while(!feof(fe)){
		if(fread(&li, sizeof(fechae), 1, fe)){
			listal[i] = li;
			i++; }
	}
	fclose(fe);
	res=i;
	gotoxy(4,8); cout << "MOVIMIENTOS";
	fflush(stdin);
	gotoxy(4,10);cout << "Ingrese Numero De DNI: "; gets(cedula);

	ultimo= i-1;
	i = 0;
	limpia();

	while (i<=ultimo){
		if (strcmp(listal[i].cedulaf,cedula)==0){
			gotoxy(4,8);cout << "Cuenta: " << listal[i].nombref;

			if(i<=ultimo){
				gotoxy(4,10); cout << "Fecha";
				gotoxy(4,12); cout << listal[i].fechaf;
				gotoxy(27,10); cout << "Tipo";
				gotoxy(27,12);cout << listal[i].tipof;
				gotoxy(43,10);cout << "Saldo";
				gotoxy(43,12);printf("$%6.2f",listal[i].transaccf);
				gotoxy(60,10) ;cout << "Saldo Total";
				gotoxy(60,12);printf("$%6.2f",listal[i].saldof);
				i++;
				CursorOff();
				gotoxy(4,22); cout << "Presione una tecla..";
				getch();
				limpia();
			}

		}
		else i++;
	}
	
	int encontro=1;
	ultimo = res-1;
	i=0;
	while (i<=ultimo && encontro){
		if (strcmp(listal[i].cedulaf,cedula)==0) 
			encontro=0;
		else 
			i++;
	}
	
	if (encontro==1){
		CursorOff();
		gotoxy(4,22); cout << "Usuario No Registrado o no tiene transacciones realizadas.";
		CursorOff();
		getch();
		limpia();
		menu();
	}
	else{
		CursorOff();
		gotoxy(4,22); cout << "Presione una tecla para volver..";
		CursorOff();
		getch();
		limpia();
		menu();
	}
	
}


//FUNCION QUE OCULTA EL CURSOR
void CursorOff()
{
  CONSOLE_CURSOR_INFO cursor = {1, FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

//FUNCION PARA QUE APAREZCA EL CURSOR
void CursorOn(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if(size == 0)
	{
		size = 20;
	}
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}


//FUNCION GOTOXY, SIRVE PARA POSICIONAR LOS MENSAJES EN UNA DETERMINADA ZONA DE LA PANTALLA, SE INGRESA COLUMNA Y FILA DE LA PANTALLA, EJEMPLO: gotoxy(4,10); cout << "HOla"); ESTE MENSAJE SE IMPRIMIRÁ EN LA POSICIÓN COLUMNA 4, FILA 10
void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }




//FUNCION QUE DIBUJA UN CUADRO, SE PASAN LOS VALORES DONDE QUEREMOS QUE SE FORME EL CUADRO, EJEMPLO dibujarCuadro(1,1,78,24);
void dibujarCuadro(int x1,int y1,int x2,int y2){
    int i;
    for (i=x1;i<x2;i++){
		gotoxy(i,y1);cout << "Ä" ;//linea horizontal superior
		gotoxy(i,y2);cout << "Ä" ;//linea horizontal inferior
    }

    for (i=y1;i<y2;i++){
		gotoxy(x1,i);cout << "³";//linea vertical izquierda
		gotoxy(x2,i);cout << "³";//linea vertical derecha
    }
    
    gotoxy(x1,y1);cout << "Ú";
    gotoxy(x1,y2);cout << "À";
    gotoxy(x2,y1);cout << "¿";
    gotoxy(x2,y2);cout << "Ù";
}


//FUNCION QUE LIMPIA EL AREA DE LA PANTALLA
void limpia(){
	int i,j;
	for(i=8;i<=23;i++){
		for(j=4;j<=75;j++){
			gotoxy(j,i); cout << " ";}}
}

