#include <ctime>
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

bool isBetween(int number, int number2, int number3){
	return number>=number2 and number<number3;
}

string obtenerEstacion(int fecha, char emisferio) {
	string estacion;
	const int otonio = 321;
	const int invierno = 621;
	const int primavera = 921;
	const int verano = 1221;
	if (isBetween(fecha,otonio,invierno)){
		estacion="otoño";
	}
	else{
		if (isBetween(fecha,invierno,primavera)) {
			estacion="invierno";
		}
		else{
			if (isBetween(fecha,primavera,verano)){
				estacion="primavera";
			}
			else{
					estacion="verano";
			}
		}
	}
	if (emisferio=='N'){
		if (estacion=="otoño") {
			estacion="primavera";
		}
		else{
			if (estacion=="primavera"){
				estacion="otoño";
			}
			else{
				if (estacion=="verano"){
					estacion="invierno";
				}
				else{
					estacion="verano";
				}
			}
		}
	}
	return estacion;
}

struct alumno{
	int legajo;
	float primerParcial;
	float segundoParcial;
};

int reporteAlumnos(alumno alumnos[50]){
	int i;
	int notaMin=alumnos[0].segundoParcial;
	int notaMax=alumnos[0].primerParcial;
	int alumnoMin=0;
	int alumnoMax=0;
	int acuNotas=0;
	for (i=1; i<50; i++){
		if (alumnos[i].primerParcial>notaMax){
			notaMax=alumnos[i].primerParcial;
			alumnoMax=i;
		}
		if (alumnos[i].segundoParcial<notaMin){
					notaMin=alumnos[i].segundoParcial;
					alumnoMin=i;
		}
		acuNotas=acuNotas+alumnos[i].primerParcial;
	}
	cout << "Alumno nota Min 2do parcial: " << alumnos[alumnoMin].legajo << endl;
	cout << "Alumno nota Max 1er parcial: " << alumnos[alumnoMax].legajo << endl;
	cout << "Promedio curso 1er parcial: " <<  acuNotas/50.00 << endl;
	return 0;
}

int mostrarAlumnos(alumno alumnos[50]){
	int i;
	for (i = 0; i < 50; ++i) {
		cout << alumnos[i].legajo << '\0';
		cout << alumnos[i].primerParcial << '\0';
		cout << alumnos[i].segundoParcial << endl;
	}
	return 0;
}

int cargaAlumnos(alumno alumnos[50]){
	int i;
	srand((unsigned)time(0));
	for (i = 0; i < 50; ++i) {
		alumnos[i].legajo = i+1;
		alumnos[i].primerParcial = (rand()%10)+1;
		alumnos[i].segundoParcial = (rand()%10)+1;
	}
	return 0;
}

int burbuja(alumno alumnos[50]){
	int i=0;
	int j;
	alumno aux;
	const int n=50;
	bool orden=false;
	while (orden==false and i<n){
		i++;
		orden=true;
		for (j = 0; j <= 50-i; ++j) {
			if ((alumnos[j].primerParcial+alumnos[j].segundoParcial)<(alumnos[j+1].primerParcial+alumnos[j+1].segundoParcial)) {
				aux=alumnos[j];
				alumnos[j]=alumnos[j+1];
				alumnos[j+1]=aux;
				orden=false;
			}
		}
	}
	return 0;
}

struct sProducto {
	int codProd;
	char desc[50];
	int pesoProd;
	int cu;
};

struct sArchivoProducto {
	int codProd;
	char desc[50];
	int cu;
};

int crearFileEnunciado(char* nFile) {
	FILE *productos;
	sProducto producto;
	int i;
	productos = fopen(nFile,"w+b");
	srand((unsigned)time(0));
	if (productos){
		for (i = 0; i < 300; ++i) {
			fseek(productos, 0, SEEK_END);   // non-portable
			producto.codProd = 1+ftell(productos)/sizeof(sProducto);;
			producto.pesoProd = (rand()%20)+1;
			if (producto.pesoProd>15){
				strcpy(producto.desc, "productoPesado");
			}
			else{
				strcpy(producto.desc, "productoLiviano");
			}
			producto.cu = (rand()%10)+1;
			//rewind(productos);
			//fseek(productos,0,SEEK_SET);
			fwrite(&producto,sizeof(sProducto),1,productos);
		}
		fclose(productos);
	}
	else{
		return 1;
	}
	productos = fopen("Productos.dat","r+b");
	fread(&producto,sizeof(sProducto),1,productos);
    while (!feof(productos)){
		cout << producto.codProd << " ";
		cout << producto.desc << " ";
		cout << producto.pesoProd << " ";
		cout << producto.cu << endl;
		fread(&producto,sizeof(sProducto),1,productos);
    }
    fclose(productos);
	return 0;
}

int crearFilesStock(char* nFile) {
		FILE *productos;
		FILE *stockP;
		FILE *stockL;
		sProducto producto;
		sArchivoProducto productoAEscribir;
		productos = fopen(nFile,"r+b");
		stockP = fopen("StockP.dat","w+b");
		stockL = fopen("StockL.dat","w+b");
		fread(&producto,sizeof(sProducto),1,productos);
		while (!feof(productos)){
				productoAEscribir.codProd = producto.codProd;
				strcpy(productoAEscribir.desc, producto.desc);
				productoAEscribir.cu = producto.cu;
				if (producto.pesoProd>15){
					fwrite(&productoAEscribir,sizeof(sArchivoProducto),1,stockP);
				}
				else{
					fwrite(&productoAEscribir,sizeof(sArchivoProducto),1,stockL);
				}
				fread(&producto,sizeof(sProducto),1,productos);
		    }
		fclose(productos);
		fclose(stockP);
		fclose(stockL);
	return 0;
}

int mostrarFileStock(char* nFile){
	FILE *stockF;
	stockF = fopen(nFile,"r+b");
	sArchivoProducto producto;
	fread(&producto,sizeof(sArchivoProducto),1,stockF);
	while (!feof(stockF)){
		cout << producto.codProd << " ";
		cout << producto.desc << " ";
		cout << producto.cu << endl;
		fread(&producto,sizeof(sArchivoProducto),1,stockF);
	}
	fclose(stockF);
	return 0;
}

int main() {
	//Punto1
	cout << obtenerEstacion(921,'N') << endl;

	//Punto2
	alumno alumnos[50];
	cargaAlumnos(alumnos); //no se pide esto
	burbuja(alumnos); //esto tmp
	mostrarAlumnos(alumnos); //esto tmp
	reporteAlumnos(alumnos);

	//Punto3
	char* fileEnunciado = "Productos.dat";
	char* stockP = "StockP.dat";
	char* stockL = "StockL.dat";
	crearFileEnunciado(fileEnunciado);
	crearFilesStock(fileEnunciado);
	mostrarFileStock(stockP);
	mostrarFileStock(stockL);
	return 0;
}

