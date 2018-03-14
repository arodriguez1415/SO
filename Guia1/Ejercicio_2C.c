#include <stdio.h>
#include <unistd.h> //incluye fork()
#include <sys/wait.h> //incluye waitpid()

#define times 2

int arrayfull(int *);

int main(void){
	int pid[times] = {0};
	int i;
	int storage;
	char * programas[] = {"/home/b0ltii/Escritorio/SO/Guia1/programa1","/home/b0ltii/Escritorio/SO/Guia1/programa2"};
	//Como podemos ver, execl() requiere como primer argumento el path absoluto al programa ejecutable, los argumentos
	//siguientes son arg[0], arg[1]...

	//En esta ejecucion,el padre va creando a los hijos los cuales corren al simultaneo con el
	//Al finalizar la ejecucion de ambos hijos, el padre finaliza. Esta espera se debe a "waitpid(pid[i],&storage,WUNTRACED);"

	for(i = 0; i < times ; i++){
		pid[i] = fork();
		if(pid[i] == 0){
			execl(programas[i],"NULL",NULL);
		}
		else if(pid[i] > 0)
			printf(">>>Volvemos al padre\n");
		else
			printf("No se pudo crear el hijo\n");
	}

	if(arrayfull(pid)){
		for(i = 0; i < times ; i++){
			waitpid(pid[i],&storage,WUNTRACED);
		}
		printf("Procesos finalizados\n");
	}	
	return 0;
}


int arrayfull(int * array){
	int i;
	for(i = 0; i < times ; i++){
		if(array[i] == 0)
			return 0;
	}
	return 1;
}