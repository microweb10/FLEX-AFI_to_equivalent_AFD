

/* DNI_1: 45567904M NOMBRE_1: Nicolas Herrero, Julian    */
/* DNI_2: 74233276V NOMBRE_2: Gallego Rodriguez, Patricia */

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

const int ktam=20, ktam2=11;

struct AFI{
	bool arcos[ktam][ktam2][ktam];
	bool aceptacion[ktam];
	bool inicial[ktam];
	int estados[ktam];
	char alf[ktam2];
	int nAlf;
	int nEstados;
};


int BuscaPosInt(int vector[],int elem,int nEstados){
	int i=0;
	while((i<nEstados)&&(elem!=vector[i])) i++;
	if(i==nEstados)
		i=-1;
return i;
}


int BuscaPosChar(char vector[],char elem,int nAlf){
	int i=0;
	while((i<nAlf)&&(elem!=vector[i])) i++;
	if(i==nAlf)
		i=-1;
return i;
}

bool ArrayIguales(bool vector1[],bool vector2[]){
	bool res=false;
	int i=0;
	while((vector1[i]==vector2[i])&&(i<ktam)) i++;
	if(i==ktam)
		res=true;
	else
		res=false;
return res;
}

bool ConjuntoVacio(bool vector[]){
	bool res;
	int i=0;
	while((vector[i]==false)&&(i<ktam)) i++;
	if(i==ktam) res=true;
	else res=false;
return res;
}


int main (int argc,char **argv){
	AFI afi,afd;
	string lineaString;
	char linea[8];
	char simbolo;
	bool aux[ktam];
	bool transicion,vacia,encontrado;
	int estado1,estado2,i,j,k,a;
	fstream fic;
	if(argc==2){
		fic.open(argv[1],ios::in);
		if(!fic) cout<<"Error al abrir el fichero: "<<argv[1]<<endl;
		else{
			// Inicializo el afi
			for(i=0;i<ktam;i++) afi.aceptacion[i]=false;
			for(i=0;i<ktam;i++) afi.inicial[i]=false;
			for(i=0;i<ktam;i++) afi.estados[i]=0;
			for(i=0;i<ktam2-1;i++) afi.alf[i]=' ';
			afi.alf[ktam2-1]='&';  // Asigno las transiciones vacias al ultimo simbolo
			for(i=0;i<ktam;i++)
				for(j=0;j<ktam2;j++)
					for(k=0;k<ktam;k++)
						afi.arcos[i][j][k]=false;
			for(i=0;i<ktam;i++) afi.arcos[i][ktam2-1][i]=true;  // todo estado es clausura de ?l mismo
			afi.nEstados=0; afi.nAlf=0;
			// fin inicializacion del afi
			while(!fic.eof()){ //leo todo el fichero
				getline(fic,lineaString);  // leemos linea por linea
				strcpy(linea,lineaString.c_str());  // la pasamos a cadena de caracteres
				i=0;
				while(linea[i]!=' ') i++;
				if (i==2) estado1=(((int)linea[0])-48)*10+(((int)linea[1])-48);
				else estado1=(((int)linea[0])-48); // guardamos el estado
				if(BuscaPosInt(afi.estados,estado1,afi.nEstados)==-1){ // Si el estado no estaba creado lo creamos
					afi.estados[afi.nEstados]=estado1; afi.nEstados++;
				}
				i++; // Como estoy en el espacio me situo en el siguiente estado
				transicion=false;
				switch(linea[i]){
					case '!': afi.inicial[BuscaPosInt(afi.estados,estado1,afi.nEstados)]=true;
						  transicion=false;
					break;
					case '#': afi.aceptacion[BuscaPosInt(afi.estados,estado1,afi.nEstados)]=true;
						  transicion=false;
					break;
					case '&': simbolo=afi.alf[ktam2-1];
						  transicion=true;vacia=true;
					break;
					default: simbolo=linea[i]; transicion=true; vacia=false;
						 if(BuscaPosChar(afi.alf,simbolo,afi.nAlf)==-1){// Si simbolo no estaba creado
							afi.alf[afi.nAlf]=simbolo; afi.nAlf++; // lo creamos
						 }
				}
				if(transicion){
					i=i+2;
					j=i;
					while(linea[i]!='\0') i++;
					if (i==(j+2)) estado2=(((int)linea[j])-48)*10+(((int)linea[j+1])-48);
					else estado2=(((int)linea[j])-48); // guardamos el estado
					if(BuscaPosInt(afi.estados,estado2,afi.nEstados)==-1){ // Si el estado no estaba creado...
						afi.estados[afi.nEstados]=estado2; afi.nEstados++; // lo creamos
					}
					if(vacia)
						afi.arcos[BuscaPosInt(afi.estados,estado1,afi.nEstados)][ktam2-1]							[BuscaPosInt(afi.estados,estado2,afi.nEstados)]=true;
					else
						afi.arcos[BuscaPosInt(afi.estados,estado1,afi.nEstados)]								 [BuscaPosChar(afi.alf,simbolo,afi.nAlf)]									 [BuscaPosInt(afi.estados,estado2,afi.nEstados)]=true;
				}
			}
			// Inicializo el afd
			for(i=0;i<ktam;i++) afd.aceptacion[i]=false;
			for(i=0;i<ktam;i++) afd.inicial[i]=false;
			for(i=0;i<ktam;i++) afd.estados[i]=0;
			for(i=0;i<ktam2-1;i++) afd.alf[i]=' ';
			afi.alf[ktam2-1]='&';  // Asigno las transiciones vacias al ultimo simbolo
			for(i=0;i<ktam;i++)
				for(j=0;j<ktam2;j++)
					for(k=0;k<ktam;k++)
						afd.arcos[i][j][k]=false;
			for(i=0;i<ktam;i++) afd.arcos[i][ktam2-1][i]=true;  // todo estado es clausura de ?l mismo
			afd.nEstados=0; afd.nAlf=afi.nAlf;
			for(i=0;i<afi.nAlf;i++) afd.alf[i]=afi.alf[i];  // los simbolos de ambos autom son iguales
			// fin inicializacion del afi
			// Primero creo el estado inicial y su clausura
			afd.estados[afd.nEstados]=afd.nEstados+1; afd.inicial[afd.nEstados]=true; afd.nEstados++;
			for(i=0;i<afi.nEstados;i++)
				if(afi.inicial[i]) // busco los estados iniciales del afi
					for(j=0;j<afi.nEstados;j++)
						if(afi.arcos[i][ktam2-1][j])
							afd.arcos[0][ktam2-1][j]=true; // asigno la clausura del Est Inicial
			// ahora asigno las transiciones
			i=0;
			while(i<afd.nEstados){
				for(j=0;j<afd.nAlf;j++){ // para todos los simbolos del automata
					for(a=0;a<ktam;a++) aux[a]=false;
					for(k=0;k<afi.nEstados;k++)
						if(afd.arcos[i][ktam2-1][k]){ // buscamos la clausura del estado
							for(a=0;a<afi.nEstados;a++)
								if(afi.arcos[k][j][a]) //si existia trans con ese simb
									aux[a]=true;
							}
					// compruebo si dicha clausura ya existe como estado
					encontrado=false;
					for(a=0;((a<afd.nEstados)&&(!encontrado));a++)
						if(ArrayIguales(afd.arcos[a][ktam2-1],aux))
							encontrado=true;
					if(encontrado) // si existia creo la transicion correspondiente
						afd.arcos[i][j][a-1]=true;
					else{
						if(!ConjuntoVacio(aux)){ //creo el nuevo estado y asigno la transicion
							afd.estados[afd.nEstados]=afd.nEstados+1; afd.nEstados++;
							afd.arcos[i][j][afd.nEstados-1]=true;
							// buscamos la clausura del estado
							for(a=0;a<ktam;a++)
								afd.arcos[afd.nEstados-1][ktam2-1][a]=aux[a];
						}
					}
				}
			i++;
			}// Ahora asignamos que estados son de aceptacion en el nuevo afd
			for(i=0;i<afd.nEstados;i++)
				for(j=0;j<ktam;j++)
					if(afd.arcos[i][ktam2-1][j])
						if(afi.aceptacion[j]) afd.aceptacion[i]=true;
			// POR ULTIMO MOSTRAMOS EL AFD RESULTANTE
			for(i=0;i<afd.nEstados;i++) if(afd.inicial[i]) cout<<afd.estados[i]<<" !"<<endl;
			for(i=0;i<afd.nEstados;i++) if(afd.aceptacion[i]) cout<<afd.estados[i]<<" #"<<endl;
			for(i=0;i<afd.nEstados;i++)
				for(j=0;j<afd.nAlf;j++)
					for(k=0;k<afd.nEstados;k++)
						if(afd.arcos[i][j][k]) cout<<afd.estados[i]<<" "<<afd.alf[j]<<" "										   <<afd.estados[k]<<endl;
		}

	}else cout<<"Error: la sintaxis para ejecutar el programa es: afd2afi <NombreFichero>"<<endl;
return 0;
}

