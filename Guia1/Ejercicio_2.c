#include <stdio.h>
#include <unistd.h> //incluye fork()
#include <sys/wait.h> //incluye waitpid()

#define TIMES 5

void printfPIDS(int *, int);
int arrayfull(int *);

int main(void){
	int pid[TIMES] = {0};
	int i;
	int storage;

	//En este programa lo que ocurrira es que, el programa padre, creara TIMES hijos, los cuales correran en simultaneo con el padre
	//Dado que usamos fork, los hijos tendran el mismo codigo que el padre, pero no crearan hijos, dado que si el pid que
	//devolvio fork es 0, hicimos break, para que los hijos no creen hijos
	//Cada hijo unicamente conocera a su/sus hermanos mayores, por ello, en la creacion del primer hijo, pid[] esta lleno de ceros
	//el segundo hijo tiene pid[0] != 0 pero los demas son ceros, y asi
	//EL ultimo hermano conoce a todos, pero fork devolvio 0, por ello, pid[TIMES] == 0,  pero los demas son != 0
	//Al final el padre esperara a que todos los hijos finalizen, debido a waitpid en todos, y lanzara un printf diciendo que finalizo

	for(i = 0; i < TIMES ; i++){
		pid[i] = fork();
		if(pid[i] == 0){
			printf("Soy el hijo numero: %d y mi PID es: %d\n", i, getpid());
			sleep(20);
			if(i > 0)
				waitpid(pid[i-1],&storage,WUNTRACED);
			printfPIDS(pid, i);
			break;
		}
		else if(pid[i] > 0)
			printf(">>>Volvemos al padre\n");
		else
			printf("No se pudo crear el hijo\n");
	}

	if(arrayfull(pid)){
		for(i = 0; i < TIMES ; i++){
			waitpid(pid[i],&storage,WUNTRACED);
		}
		printf("Procesos finalizados\n");
	}	
	return 0;
}

void printfPIDS(int * array, int hijo){
	int i;
	printf("Array del hijo %d: ", hijo);
	for(i = 0; i < TIMES ; i++){
		printf(" %d ",array[i]);
	}
	printf("\n");
}

int arrayfull(int * array){
	int i;
	for(i = 0; i < TIMES ; i++){
		if(array[i] == 0)
			return 0;
	}
	return 1;
}