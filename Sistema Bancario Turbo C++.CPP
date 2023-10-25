#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

extern unsigned_floatconvert;
#pragma extref_floatconvert

//Estructura para almacenar en el archivo
struct socio{
	char nombre[35];
	char cedula[15];
	char ciudad[20];
	char telefono[20];
};

struct transacciones{
	char cedula[15];
	char nombre[35];
	char fecha[15];
	float valorinicial;
	float transacc;
};

struct fechae{
	char cedulaf[15];
	char nombref[35];
	char fechaf[15];
	char tipof[10];
	float transaccf;
	float saldof;
};

//DIBUJAR CUADRO
void dibujarCuadro2(int x1,int y1,int x2,int y2)
{

    int i;
    for (i=x1;i<x2;i++)
    {
	gotoxy(i,y1);printf("Ä") ;//linea horizontal superior
	gotoxy(i,y2);printf("Ä") ;//linea horizontal inferior
    }

    for (i=y1;i<y2;i++)
    {
	gotoxy(x1,i);printf("³") ;//linea vertical izquierda
	gotoxy(x2,i);printf("³") ;//linea vertical derecha
    }
    gotoxy(x1,y1);printf("Ú");
    gotoxy(x1,y2);printf("À");
    gotoxy(x2,y1);printf("¿");
    gotoxy(x2,y2);printf("Ù");
}


//FUNCION LIMPIAR AREA
void limpia(){
	int i,j;
	for(i=8;i<=20;i++){
		for(j=4;j<=70;j++){
			gotoxy(j,i); printf(" ");}}
}

// FUNCION INGRESO DE DATOS Y ALMACENAR
void ingreso(){
	FILE *pa;
	char r;
	socio nuevo, lista[50];
	limpia();
	if ((pa = fopen("E2","a+b"))==NULL)
	{ printf("No se puede abrir el archivo.\n");
		return ;
		}

	int encontro=1,i,ultimo,res;

	rewind(pa); i=0;
	while(!feof(pa))
	{ if(fread(&nuevo, sizeof(socio), 1, pa)){
		lista[i]=nuevo;
		i++;}
	}

	fflush(stdin);
	gotoxy(4,8);printf("REGISTRO DE SOCIOS");
	gotoxy(4,10);printf("Nombres y apellidos:  "); gets(nuevo.nombre);

	gotoxy(4,12);printf("C‚dula:               ");
		res=i;
		do{
			gotoxy(26,12); gets(nuevo.cedula);
			//proceso de busqueda de la informaci¢n
			ultimo=res-1;
			i=0;
			encontro=1;
			while (i<=ultimo && encontro){
				if (strcmp(lista[i].cedula,nuevo.cedula)==0) encontro=0;
				else i++;
			}
			if (i<=ultimo){
				gotoxy(26,12);printf("                              ");
				gotoxy(4,19);printf("C‚dula ya ingresada. Ingrese nuevamente.");}
			else {gotoxy(4,19); printf("                                               ");}
		}
		while(i<=ultimo);

	gotoxy(4,14);printf("Ciudad:               "); gets(nuevo.ciudad);
	gotoxy(4,16);printf("Tel‚fono:             "); gets(nuevo.telefono);
	gotoxy(4,19);printf("¨Registrar Nuevo Socio? Si[s] / No [n]: "); r=getch();
	if (r=='s' || r=='S') {
		fwrite(&nuevo, sizeof(socio),1,pa);
		gotoxy(4,19);printf("Socio Registrado Correctamente. Presione una tecla para salir..");}
	else {gotoxy(4,19);printf("Socio NO Registrado. Presione una tecla para salir..");}
	_setcursortype(_NOCURSOR);
	getch();
	limpia();
	fclose(pa); }


// FUNCION MODIFICAR DATOS ALMACENADOS
void modificacion()
{ socio nuevo, lista[50];
  char cedula[15];
  int encontro=1,linea,i,ultimo;
  char r;
  FILE *pa;
  limpia();
  if ((pa = fopen("E2", "a+b"))== NULL)
      { printf("No se puede abrir el archivo.\n");
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
  textcolor(YELLOW);

  //proceso de busqueda de la informaci¢n
  gotoxy(4,8);printf("ACTUALIZAR DATOS");
  gotoxy(4,10);
  fflush(stdin);
  printf("Ingrese N£mero De C‚dula: ");gets(cedula);
  ultimo=i-1;
  i=0;
  while (i<=ultimo && encontro)
  { if (strcmp(lista[i].cedula,cedula)==0) encontro=0;
    else i++;
  }
  if (i<=ultimo)
  { do {
    limpia();
    gotoxy(4,8);printf("ACTUALIZAR DATOS");
    gotoxy(4,10);printf("1. Nombre:   %s\n",lista[i].nombre);
    gotoxy(4,12);printf("2. C‚dula:   %s\n",lista[i].cedula);
    gotoxy(4,14);printf("3. Ciudad:   %s\n",lista[i].ciudad);
    gotoxy(4,16);printf("4. Tel‚fono: %s\n",lista[i].telefono);
    gotoxy(4,18);printf("Escriba la l¡nea a modificar: ");
    do{
       gotoxy(34,18);scanf("%d",&linea);
    }while(linea<1 || linea>4);
    fflush(stdin);
    switch(linea){
    case 1: gotoxy(4,10 );printf("                                                       ");
	    gotoxy(4,10 );
	    printf("1. Nombre:   ");
	    gets(lista[i].nombre);
	    break;
    case 2: gotoxy(4,12 );printf("                              ");
	    gotoxy(4,12 );
	    printf("2. C‚dula:   ");
	    gets(lista[i].cedula);
	    break;
    case 3: gotoxy(4,14);printf("                              ");
	    gotoxy(4,14);
	    printf("3. Ciudad:   ");
	    gets(lista[i].ciudad);
	    break;
    case 4: gotoxy(4,16);printf("                              ");
	    gotoxy(4,16);
	    printf("4. Tel‚fono: ");
	    gets(lista[i].telefono);
    }
    gotoxy(4,18);printf("Actualizaci¢n Correcta.                  ");
    gotoxy(4,20);printf("¨Desea Seguir Actualizando? Si[s] / No[n]: ");r=getch();
    }while (r!='n' && r!='N');
    // Abrir el archivo para Sobrescribir
    if ((pa = fopen("E2", "wb"))== NULL)
      { printf("No se puede abrir el archivo.\n");
	return;
      }
    i=0;
    while(i<=ultimo)
    { fwrite(&lista[i], sizeof(socio), 1, pa);
      i++;
    }
    gotoxy(4,20);printf("Presione una tecla para salir...                   ");
    _setcursortype(_NOCURSOR);
    getch();limpia();
  }
  else
  { gotoxy(4,18);printf("Usuario NO registrado.");
    gotoxy(4,20);printf("Presione una tecla para salir... ");
    _setcursortype(_NOCURSOR);
    getch();limpia();
  }
fclose(pa);

}


//FUNCION ELIMINAR
void eliminar()
{ socio nuevo, lista[50];
  char cedula[15];
  char r;
  int encontro=1,linea,i,ultimo;
  FILE *pa;
  limpia();
  if ((pa = fopen("E2", "a+b"))== NULL)
      { printf("No se puede abrir el archivo.\n");
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
  textcolor(YELLOW);


  //proceso de busqueda de la informaci¢n
  gotoxy(4,8);printf("ELIMINAR DATOS");
  gotoxy(4,10);
  fflush(stdin);
  printf("Ingrese N£mero De C‚dula: ");gets(cedula);
  ultimo=i-1;
  i=0;
  while (i<=ultimo && encontro)
  { if (strcmp(lista[i].cedula,cedula)==0) encontro=0;
    else i++;
  }
  if (i<=ultimo)
  {
    limpia();
    gotoxy(4,8);printf("ELIMINAR DATOS");
    gotoxy(4,10);printf("Nombre:   %s\n",lista[i].nombre);
    gotoxy(4,12);printf("C‚dula:   %s\n",lista[i].cedula);
    gotoxy(4,14);printf("Ciudad:   %s\n",lista[i].ciudad);
    gotoxy(4,16);printf("Tel‚fono: %s\n",lista[i].telefono);
    gotoxy(4,20); printf("¨Desea Eliminarlo? Si[s] / No[n]: ");r=getch();
    if (r=='s' || r=='S')
      { while (i<ultimo) {
	    lista[i]=lista[i+1];
	    i++;
	}
	ultimo=i-1;
	if ((pa = fopen("E2", "wb"))== NULL)
	  {	printf("No se puede abrir el archivo.\n");
		return;
	  }
	i=0;
	while(i<=ultimo)
	{ fwrite(&lista[i], sizeof(socio), 1, pa);
	  i++;
	}
	gotoxy(4,20);printf("Registro Eliminado. Presione una tecla para salir..");
	_setcursortype(_NOCURSOR);
	getch();limpia();
      }
    else{gotoxy(4,20);printf("Registro NO Eliminado. Presione una tecla para salir..");
	_setcursortype(_NOCURSOR);
	getch();limpia();
	}
  }
  else
  { gotoxy(4,18);printf("Usuario NO registrado.");
    gotoxy(4,20);printf("Presione una tecla para salir... ");
    _setcursortype(_NOCURSOR);
    getch();limpia();
  }
fclose(pa);

}



// FUNCION CONSULTAR
void consultar()
{ socio nuevo, lista[50];
  char cedula[15];
  int encontro=1,linea,i,ultimo;
  FILE *pa;
  limpia();
  if ((pa = fopen("E2", "a+b"))== NULL)
      { printf("No se puede abrir el archivo.\n");
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
  textcolor(YELLOW);

  //proceso de busqueda de la informaci¢n
  gotoxy(4,8);printf("CONSULTA DE SOCIOS");
  gotoxy(4,10);
  fflush(stdin);
  printf("Ingrese N£mero De C‚dula: ");gets(cedula);
  ultimo=i-1;
  i=0;
  while (i<=ultimo && encontro)
  { if (strcmp(lista[i].cedula,cedula)==0) encontro=0;
    else i++;
  }
  if (i<=ultimo)
  {
    limpia();
    gotoxy(4,8);printf("CONSULTA DE SOCIOS");
    gotoxy(4,10);printf("Nombre:   %s\n",lista[i].nombre);
    gotoxy(4,12);printf("C‚dula:   %s\n",lista[i].cedula);
    gotoxy(4,14);printf("Ciudad:   %s\n",lista[i].ciudad);
    gotoxy(4,16);printf("Tel‚fono: %s\n",lista[i].telefono);

    gotoxy(4,20);printf("Presione una tecla para salir...                   ");
    _setcursortype(_NOCURSOR);
    getch();limpia();
  }
  else
  { gotoxy(4,18);printf("Usuario NO registrado.");
    gotoxy(4,20);printf("Presione una tecla para salir... ");
    _setcursortype(_NOCURSOR);
    getch();limpia();
  }
fclose(pa);

}




//DEPOSITO
void deposito(){
  limpia();
  gotoxy(4,8);printf("TRANSACCIONES: DEPOSITO");

  socio nuevo, lista[50];
  char cedula[15];
  int encontro=1,i,ultimo;
  FILE *pa;
  if ((pa = fopen("E2", "a+b"))== NULL)
      { printf("No se puede abrir el archivo.\n");
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
  printf("Ingrese N£mero De C‚dula: ");gets(cedula);
  ultimo=i-1;
  i=0;
  while (i<=ultimo && encontro)
  { if (strcmp(lista[i].cedula,cedula)==0) encontro=0;
    else i++;
  }
  if (i<=ultimo)
  {
    gotoxy(4,10);printf("                                              ");
    gotoxy(4,10);printf("Cuenta perteneciente a:   %s\n",lista[i].nombre);

  //Almacenar datos en estructura 2
  char cedula2[15], nombre[35];
  strcpy(cedula2,cedula);
  strcpy(nombre, lista[i].nombre);

  FILE *da;
  transacciones nuevot, listat[50];
  if ((da = fopen("E3","a+b"))==NULL)
  { printf("No se puede abrir el archivo.\n");
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
	gotoxy(4,12);printf("Saldo:                    $ %6.2f",listat[i].valorinicial);
	gotoxy(4,14);printf("Valor a depositar:        $  ");
	do{
		gotoxy(33,14); scanf("%f",&listat[i].transacc);
		if (listat[i].transacc <= 0)
			{ gotoxy(33,14); printf("                               ");}}
	while(listat[i].transacc <= 0);
	listat[i].valorinicial += listat[i].transacc;
	fflush(stdin);
	gotoxy(4,16);printf("Ingrese fecha:            dd/mm/aaaa"); gotoxy(30,16);gets(listat[i].fecha);
	limpia();
	dibujarCuadro2(13,8,63,19);
	gotoxy(20,10);printf("      COMPROBANTE DE DEPOSITO");
	gotoxy(20,12);printf("C‚dula:             %s",listat[i].cedula);
	gotoxy(20,13);printf("Nombre:             %s",listat[i].nombre);
	gotoxy(20,14);printf("Monto:              $ %6.2f",listat[i].transacc);
	gotoxy(20,15);printf("Saldo actual:       $ %6.2f",listat[i].valorinicial);
	gotoxy(20,16);printf("Cajero:             Jose Fuentes");
	gotoxy(20,17);printf("Fecha:              %s",listat[i].fecha);

	//Abrir el archivo para sobreescribir
	if ((da = fopen("E3", "wb"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;}
	i=0;
	while(i<=ultimo){
		fwrite(&listat[i], sizeof(transacciones), 1, da);
		i++;}
	fclose(da);

	//LIBRETA DE AHORROS: PROCESO

	int encontro=1,i,ultimo;
	transacciones nuevof, listaf[50];
	FILE *fa;
	if ((fa = fopen("E3", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
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
		char f[15], t[10] = "Dep¢sito";
		float tra, sald;

		strcpy(f,listaf[i].fecha);
		tra = listaf[i].transacc;
		sald = listaf[i].valorinicial;

	//Crear archivo 3 y pasar datos
		FILE *ka;
		fechae nuevoj;
		if ((ka = fopen("E4","a+b"))==NULL){
			printf("No se puede abrir el archivo.\n");
			return ;
		}
		strcpy(nuevoj.cedulaf,cedula2);
		strcpy(nuevoj.nombref,nombre);
		strcpy(nuevoj.fechaf,f);
		strcpy(nuevoj.tipof,t);
		nuevoj.transaccf = tra;
		nuevoj.saldof = sald;

		fwrite(&nuevoj, sizeof(fechae),1,ka);
		fclose(ka);}}



  else{
	strcpy(nuevot.cedula,cedula2);
	strcpy(nuevot.nombre,nombre);

	nuevot.valorinicial = 0;
	gotoxy(4,12);printf("Saldo:                    $ %6.2f",nuevot.valorinicial);
	gotoxy(4,14);printf("Valor a depositar:        $  ");
	do{
		gotoxy(33,14); scanf("%f",&nuevot.transacc);
		if(nuevot.transacc <= nuevot.valorinicial)
			{ gotoxy(33,14);printf("                           ");}}
	while(nuevot.transacc <= nuevot.valorinicial);
	nuevot.valorinicial += nuevot.transacc;
	fflush(stdin);
	gotoxy(4,16);printf("Fecha:                    dd/mm/aaaa"); gotoxy(30,16); gets(nuevot.fecha);
	limpia();
	dibujarCuadro2(13,8,63,19);
	gotoxy(20,10); printf("      COMPROBANTE DE DEPOSITO");
	gotoxy(20,12);printf("C‚dula:         %s",nuevot.cedula);
	gotoxy(20,13);printf("Nombre:         %s",nuevot.nombre);
	gotoxy(20,14);printf("Monto:          $ %6.2f",nuevot.transacc);
	gotoxy(20,15);printf("Saldo actual:   $ %6.2f",nuevot.valorinicial);
	gotoxy(20,16);printf("Cajero:         Jose Fuentes");
	gotoxy(20,17);printf("Fecha:          %s",nuevot.fecha);

	fwrite(&nuevot, sizeof(transacciones),1,da);
	fclose(da);

	//LIBRETA DE AHORROS: PROCESO

	int encontro=1,i,ultimo;
	transacciones nuevof, listaf[50];
	FILE *fa;
	if ((fa = fopen("E3", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
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
		char f[15], t[10] = "Dep¢sito";
		float tra, sald;

		strcpy(f,listaf[i].fecha);
		tra = listaf[i].transacc;
		sald = listaf[i].valorinicial;

	//Crear archivo 3 y pasar datos
		FILE *ka;
		fechae nuevoj;
		if ((ka = fopen("E4","a+b"))==NULL){
			printf("No se puede abrir el archivo.\n");
			return ;
		}
		strcpy(nuevoj.cedulaf,cedula2);
		strcpy(nuevoj.nombref,nombre);
		strcpy(nuevoj.fechaf,f);
		strcpy(nuevoj.tipof,t);
		nuevoj.transaccf = tra;
		nuevoj.saldof = sald;

		fwrite(&nuevoj, sizeof(fechae),1,ka);
		fclose(ka);}}



  gotoxy(4,20);printf("Presione una tecla para salir... ");
  _setcursortype(_NOCURSOR);
  getch();limpia();}
  else{
      gotoxy(4,18);printf("Usuario NO registrado en el sistema.");
      gotoxy(4,20);printf("Presione una tecla para salir... ");
      _setcursortype(_NOCURSOR);
      getch();limpia();}

}

//RETIRO
void retiro(){
  limpia();
  gotoxy(4,8);printf("TRANSACCIONES: RETIRO");

  socio nuevo, lista[50];
  char cedula[15];
  int encontro=1,i,ultimo;
  FILE *pa;
  if ((pa = fopen("E2", "a+b"))== NULL)
      { printf("No se puede abrir el archivo.\n");
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
  printf("Ingrese N£mero De C‚dula: ");gets(cedula);
  ultimo=i-1;
  i=0;
  while (i<=ultimo && encontro)
  { if (strcmp(lista[i].cedula,cedula)==0) encontro=0;
    else i++;
  }
  if (i<=ultimo)
  {
    gotoxy(4,10);printf("                                              ");
    gotoxy(4,10);printf("Cuenta perteneciente a:   %s\n",lista[i].nombre);

  //Almacenar datos en estructura 2
  char cedula2[15], nombre[35];
  strcpy(cedula2,cedula);
  strcpy(nombre, lista[i].nombre);

  FILE *da;
  transacciones nuevot, listat[50];
  if ((da = fopen("E3","a+b"))==NULL)
  { printf("No se puede abrir el archivo.\n");
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
	gotoxy(4,12);printf("Saldo:                    $ %6.2f",listat[i].valorinicial);
	gotoxy(4,14);printf("Valor a retirar:          $  ");
	do{
	gotoxy(33,14);scanf("%f",&listat[i].transacc);
	if(listat[i].transacc > listat[i].valorinicial || listat[i].transacc < 0)
		{ gotoxy(33,14);printf("                  ");}
	} while(listat[i].transacc > listat[i].valorinicial || listat[i].transacc < 0);
	listat[i].valorinicial -= listat[i].transacc;
	fflush(stdin);
	gotoxy(4,16);printf("Ingrese fecha:            dd/mm/aaaa"); gotoxy(30,16);gets(listat[i].fecha);
	limpia();
	dibujarCuadro2(13,8,63,19);
	gotoxy(20,10);printf("      COMPROBANTE DE RETIRO");
	gotoxy(20,12);printf("C‚dula:             %s",listat[i].cedula);
	gotoxy(20,13);printf("Nombre:             %s",listat[i].nombre);
	gotoxy(20,14);printf("Monto:              $ %6.2f",listat[i].transacc);
	gotoxy(20,15);printf("Saldo actual:       $ %6.2f",listat[i].valorinicial);
	gotoxy(20,16);printf("Cajero:             Jose Fuentes");
	gotoxy(20,17);printf("Fecha:              %s",listat[i].fecha);

	//Abrir el archivo para sobreescribir
	if ((da = fopen("E3", "wb"))== NULL){
		printf("No se puede abrir el archivo.\n");
		return;}
	i=0;
	while(i<=ultimo){
		fwrite(&listat[i], sizeof(transacciones), 1, da);
		i++;}
	fclose(da);

	//LIBRETA DE AHORROS: PROCESO

	int encontro=1,i,ultimo;
	transacciones nuevof, listaf[50];
	FILE *fa;
	if ((fa = fopen("E3", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
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

	//Crear archivo 3 y pasar datos
		FILE *ka;
		fechae nuevoj;
		if ((ka = fopen("E4","a+b"))==NULL){
			printf("No se puede abrir el archivo.\n");
			return ;
		}
		strcpy(nuevoj.cedulaf,cedula2);
		strcpy(nuevoj.nombref,nombre);
		strcpy(nuevoj.fechaf,f);
		strcpy(nuevoj.tipof,t);
		nuevoj.transaccf = tra;
		nuevoj.saldof = sald;

		fwrite(&nuevoj, sizeof(fechae),1,ka);
		fclose(ka);}}


  else{
	strcpy(nuevot.cedula,cedula2);
	strcpy(nuevot.nombre,nombre);

	nuevot.valorinicial = 0;
	gotoxy(4,12);printf("Saldo:                    $ %6.2f",nuevot.valorinicial);
	gotoxy(4,14);printf("Valor a retirar:          $  ");
	do{
	gotoxy (34,14); scanf("%f",&nuevot.transacc);
	if (nuevot.transacc > nuevot.valorinicial || nuevot.transacc < 0)
		{ gotoxy(33,14); printf("                             ");}
	} while(nuevot.transacc > nuevot.valorinicial || nuevot.transacc < 0);
	nuevot.valorinicial -= nuevot.transacc;
	fflush(stdin);
	gotoxy(4,16);printf("Fecha:                    dd/mm/aaaa"); gotoxy(30,16); gets(nuevot.fecha);
	limpia();
	dibujarCuadro2(13,8,63,19);
	gotoxy(20,10); printf("      COMPROBANTE DE RETIRO");
	gotoxy(20,12);printf("C‚dula:         %s",nuevot.cedula);
	gotoxy(20,13);printf("Nombre:         %s",nuevot.nombre);
	gotoxy(20,14);printf("Monto:          $ %6.2f",nuevot.transacc);
	gotoxy(20,15);printf("Saldo actual:   $ %6.2f",nuevot.valorinicial);
	gotoxy(20,16);printf("Cajero:         Jose Fuentes");
	gotoxy(20,17);printf("Fecha:          %s",nuevot.fecha);

	fwrite(&nuevot, sizeof(transacciones),1,da);
	fclose(da);

	//LIBRETA DE AHORROS: PROCESO

	int encontro=1,i,ultimo;
	transacciones nuevof, listaf[50];
	FILE *fa;
	if ((fa = fopen("E3", "a+b"))== NULL){
		printf("No se puede abrir el archivo.\n");
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

	//Crear archivo 3 y pasar datos
		FILE *ka;
		fechae nuevoj;
		if ((ka = fopen("E4","a+b"))==NULL){
			printf("No se puede abrir el archivo.\n");
			return ;
		}
		strcpy(nuevoj.cedulaf,cedula2);
		strcpy(nuevoj.nombref,nombre);
		strcpy(nuevoj.fechaf,f);
		strcpy(nuevoj.tipof,t);
		nuevoj.transaccf = tra;
		nuevoj.saldof = sald;

		fwrite(&nuevoj, sizeof(fechae),1,ka);
		fclose(ka);}}



  gotoxy(4,20);printf("Presione una tecla para salir... ");
  _setcursortype(_NOCURSOR);
  getch();limpia();}
  else{
      gotoxy(4,18);printf("Usuario No Registrado En El Sistema.");
      gotoxy(4,20);printf("Presione una tecla para salir... ");
      _setcursortype(_NOCURSOR);
      getch();limpia();}

}

//LIBRETA DE AHORROS
void libreta(){
	fechae li,listal[50];
	char cedula[15];
	int i,ultimo,res;
	FILE *fe;
	limpia();
	if ((fe = fopen("E4", "a+b"))== NULL)
	{ 	printf("No se puede abrir el archivo.\n");
		return; }
	rewind(fe); i=0;
	while(!feof(fe)){
		if(fread(&li, sizeof(fechae), 1, fe)){
			listal[i] = li;
			i++; }
	}
	fclose(fe);
	res=i;
	gotoxy(4,8); printf("LIBRETA DE AHORROS");
	fflush(stdin);
	gotoxy(4,10);printf("Ingrese N£mero De C‚dula: "); gets(cedula);

	ultimo= i-1;
	i = 0;
	limpia();

	while (i<=ultimo){
		if (strcmp(listal[i].cedulaf,cedula)==0){
			gotoxy(4,8);printf("Cuenta: %s",listal[i].nombref);

			if(i<=ultimo){
				gotoxy(4,10); printf("Fecha");
				gotoxy(4,12); printf("%s",listal[i].fechaf);
				gotoxy(27,10); printf("Tipo");
				gotoxy(27,12);printf("%s",listal[i].tipof);
				gotoxy(43,10);printf("Saldo");
				gotoxy(43,12);printf("$%6.2f",listal[i].transaccf);
				gotoxy(60,10) ;printf("Saldo Total");
				gotoxy(60,12);printf("$%6.2f",listal[i].saldof);
				i++;
				_setcursortype(_NOCURSOR);
				gotoxy(4,20); printf("Presione una tecla para ver las dem s transacciones.");
				getch();
				limpia();
			}

		}
		else i++;}
	int encontro=1;
	ultimo = res-1;
	i=0;
	while (i<=ultimo && encontro){
		if (strcmp(listal[i].cedulaf,cedula)==0) encontro=0;

		else i++;}
	if (encontro==1){
		_setcursortype(_NOCURSOR);
		gotoxy(4,20); printf("Usuario No Registrado o no tiene transacciones realizadas.");
		getch();
		limpia();}
}


//*******************************************************************************

void main(){
	char menu[3][10]= {"SOCIOS","CUENTA","CERRAR"};
	char submenu[6][22]= {"1. REGISTRAR","2. ACTUALIZAR","TRANSACCIONES","1. DEPOSITO","2. RETIRO","3. LIBRETA DE AHORRO"};
	int tecla, col=4, i, indice=0, fila=8, op;
	int a,b;

	//crea una ventana COMPLETA de fondo azul claro
	window(1,1,80,25);
	textbackground(1);//fondo de la pantalla AZUL
	clrscr();

	//Ventana de fondo o sombra NEGRA
	window(4,4,79,24);//crea una ventana en estar cordenadas
	textbackground(BLACK);
	clrscr();

	window(2,2,77,22);//crea una ventana en estar cordenadas
	textbackground(3);//fondo de la pantalla color cian
	textcolor(WHITE);//color de la letra blanca
	clrscr();
	textcolor(BLACK);
	dibujarCuadro2(1,1,75,21);//Cuadro grande
	dibujarCuadro2(2,2,73,4);//Cuadro titulo
	gotoxy(16,3);
	textcolor(0);//establece el color de fondo en blanco
	cprintf("     S I S T E M A        B A N C A R I O");

	//Imprimir menu en pantalla
	textbackground(11);
	textcolor(14);
	for (i=0; i<3;i++){
		gotoxy(col,6);cprintf("%s",menu[i]);
		col+=30;}

	col=4; i=1;

	//Proceso de controlar el movimiento
	do{
		do{_setcursortype(_NOCURSOR);
			textbackground(6);
		       //	textcolor(14);
			gotoxy(col,6);
			cprintf("%s",menu[indice]);
			tecla=getch(); }
		while(tecla!=77 && tecla != 75 && tecla !=13);

		textbackground(11);
		gotoxy(col,6);
		cprintf("%s",menu[indice]);

		//Chequear la tecla presionada
		switch(tecla){
			case 77: if (indice==2){
				col = 4; indice = 0;}
				else { col+=30; indice++; } break;
			case 75: if (indice==0) {
				col = 64; indice = 2; }
				else { col-=30; indice--; } break;
			case 13: if (indice==0){
				for (i=0; i<2;i++){
					gotoxy(4,fila);printf("%s",submenu[i]);
					fila+=2; }
				fila=8;
				gotoxy(4,12);printf("3. CONSULTAR");
				gotoxy(4,14);printf("4. ELIMINAR");
				_setcursortype(_NORMALCURSOR);
				gotoxy(4,16); printf("Ingrese opci¢n: ");
				scanf("%i",&op);

				if (op==1) ingreso();
				if (op==2) modificacion();
				if (op==3) consultar();
				if (op==4) eliminar();
				if (op< 1 || op>4) limpia(); }

				if(indice==1){
					for (i=2; i<6;i++){
					gotoxy(34,fila);printf("%s",submenu[i]);
					fila+=2; }
				fila=8;

				_setcursortype(_NORMALCURSOR);
				gotoxy(34,17); printf("Ingrese opcion: ");
				scanf("%i",&op);

				if (op==1) deposito();
				if (op==2) retiro();
				if(op==3) libreta();
				if (op< 1 || op>3) limpia();
				}


				if (indice==2) i=0;   }
	}while(i);
}
