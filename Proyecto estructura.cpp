#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


using namespace std;

struct corredor{
	
 char nombre[20];	
 int camisa;
 float tiempo=0;
int recor;
int promedio;
int total;	
 	
	
	corredor *derecha;
	corredor *izquierdo;
	
	
};


corredor *Raiz=NULL,*aux,*aux1;

 int preorden(corredor *aux2){
  
  	cout<<"Numero de camisa: "<<aux2->camisa<<" "
	    <<"Nombre del Atleta: "<<aux2->nombre<<" "
	    <<"Tiempo: "<<aux2->tiempo<<endl;
  	
	  if(aux2->izquierdo != NULL){
  		
       preorden(aux2->izquierdo);  		
  		
	  }if(aux2->derecha != NULL){
	  	
	  	  preorden(aux2->derecha);  
	  }
        return 0;

  }
  int Registrart(){
  	int camisa;
  	bool paso=false;
  	cout <<"Registrar el numero del corredor: ";
  cin >> camisa;
  	cout<<"\n";
  aux = Raiz;
          
  if (aux->camisa == camisa){  
  	paso=true;
  	aux->recor++;
  	
  	cout << "nombre del atleta: "<<aux->nombre << " "<<"tiempo incluido: "<< aux->tiempo <<" "<<"Ultima vuelta: "<<aux->recor<< endl;
	cout<<"\n";
    cout << "Registre el tiempo de la última vuelta:" << endl;
    cin >> aux->tiempo;
    aux->total+=aux->tiempo;
    
    aux->promedio = aux->total / aux->recor;
  	
  	
  	
  }else if(paso==false ){
  	
  	cout<<" no  esta el atleta en la competencia"<<endl;
  	
  }
  
  
  
  
  
  
}

int Posicionar(){
  	if(aux->camisa < aux1->camisa ){
  if(aux1->izquierdo != NULL){
	       aux1 = aux1->izquierdo;
	         Posicionar();
	   }else
	    aux1->izquierdo = aux;
	    
	  }else if(aux->camisa > aux1->camisa){
	  	 if(aux1->derecha != NULL){
	       aux1 = aux1->derecha;
	         Posicionar();
	   }else
	    aux1->derecha =aux;
	  	
	  }
  	return 0;
  } 





int Registro(){
	
	aux =(struct corredor *) malloc (sizeof(struct corredor));
    cout << "Ingrese el nombre  del atleta"<<endl;
    cin >> aux->nombre;
    cout << "Ingresar el numero  del Atleta: "<<endl;
    cin >> aux->camisa;
    aux->derecha =NULL,aux->izquierdo=NULL;
    if(Raiz==NULL){
    Raiz = aux;	
     aux=NULL;
    free(aux);
    	
	}else {
		aux1 = Raiz;
		Posicionar();		
		
	}
 
 
 	
	
	return 0;
}




int main(){
	
	int datos=0;
	do{
		
		cout<< "Menu" << endl;
        cout<<"1. Registar Atleta" << endl;
        cout<<"2. Registrar tiempo" << endl;
        cout<<"3. Mostrar atleta "<<endl;
        cout<<"4. Promedio del atleta"<<endl;
        cout<<"5. Salir "<<endl;
	   cin>>datos;	
		switch(datos){
		
		 case 1: 
		    Registro();
		    
		 break;
		 
			 case 2: 
			 
		 Registrart();
		 break;
		case 3: 
		  preorden(Raiz);
		break;
		
		
		default:
		       cout<<"Opcion que digitaste no esta disponible";
                break;  
			
		}
		
		
		
		
		
	}while(datos !=5);
	
	

	return 0;
	
}
