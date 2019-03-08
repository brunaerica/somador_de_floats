#include <stdio.h>
#include <string.h>
#include <stdlib.h>


 
  int eh_digito(char c){
 if ((c >= '0') && (c <= '9')) return 1;
else return 0;
}

 int eh_ponto(char c){
if(c == '.') return 1;
else return 0;
}

typedef struct {
  int estado_atual;
} fsm, *Fsm; /* fsm = finite state machine */

int opera_fsm(void *this_fsm, char entrada) {
  Fsm maquina = (Fsm) this_fsm;

  switch (maquina->estado_atual) {
    case 0:
      if (eh_digito(entrada)) {
        maquina->estado_atual = 1;
      } else {
        maquina->estado_atual = 5;
      }
      break;

    case 1:
      if (eh_digito(entrada)) {
        maquina->estado_atual = 1;
      }
      else if(eh_ponto(entrada)){
	maquina->estado_atual = 2;
      }
      else if (entrada == ' ' || entrada == '\n'){
	maquina->estado_atual = 4;
      }
      else {
	maquina->estado_atual = 5;	
      }
      break;

    case 2:
      if (eh_digito(entrada)) {
        maquina->estado_atual = 3;
      } 
      else {
        maquina->estado_atual = 5;
      }
      break;

    case 3:
      if (eh_digito(entrada)) {
        maquina->estado_atual = 3;
      } 
      else if (entrada == ' ' || entrada == '\n'){
	maquina->estado_atual = 4;
      }
      else {
	maquina->estado_atual = 5;
      }
      break;
    case 4:
      if(eh_digito(entrada)){
	maquina->estado_atual = 1;
      }
      else{
	maquina->estado_atual = 5;
      }
      break;

    case 5:
      if (entrada == ' ' || entrada == '\n'){
	maquina->estado_atual = 0;	
      }
      else{
	maquina->estado_atual = 5;
      }
      break;

 
  return (maquina->estado_atual);

  }

}

int main() {

 float somatotal=0, encontrei = 0;
  char entrada[200], dig_encontrado[100];
  int a=0, b=0, c=0, j=0;


for(int i=0; i<200; i++) {
  entrada[i] = '\0';
}

do{
 c = getchar();
 entrada[a++] = c;
} while (c!='\n');


fsm maquina;
maquina.estado_atual = 0;
a =0;

while(entrada[a] != '\0'){	
	opera_fsm((void*) (&maquina), entrada[a]);
	
	if(maquina.estado_atual == 0){			
		for(j=0; j<100; j++){
			dig_encontrado[j] = '\0';
		}	
		j=0;
	}
	if(maquina.estado_atual ==1){			
		dig_encontrado[j] = entrada[a];		 
		j++;		
	}
	if(maquina.estado_atual == 2){				
		dig_encontrado[j] = '.';
		j++;		
	}
	if(maquina.estado_atual == 3){
		dig_encontrado[j] = entrada[a];
		j++;			
	}
	if(maquina.estado_atual == 4){
		encontrei = atof(dig_encontrado);
		somatotal = somatotal + encontrei;
		for(j=0; j<100; j++){
			dig_encontrado[j] = '\0';
		}	
		j=0;		
	}	
	a++;
}
	 printf("%g\n", somatotal);
}



