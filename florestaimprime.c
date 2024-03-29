#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define max 4294967295.
#define vazio ' '
#define arvore 'Y'
#define fogo '*'
#define cinza '.'
#define L 40
#define stepsmax 157

//define o n�mero de simula��es
#define sims 5

//vari�ves dos contadores
 int contfogo=0, contarvore=0, contvazio=0, contcinza=0, i, j, time=50000;
 
//vari�veis para a media dos contadores 
 float mfogo[stepsmax+3], marvore[stepsmax+3], mvazio[stepsmax+3], mcinza[stepsmax+3];
 
//vari�veis usadas para controle das simula��es
 int t=0, steps=0, sim=sims;
 
//vari�veis para formar a floresta
 char floresta[L][L+2];
 char pre = 'X';
 float p = 0.65;
 unsigned R=58454585, seed=89974563;

//gera o arquivo
FILE *flo;

//fun��o que gera os n�meros aleat�rios para as florestas
float rnumber()
{	
   float rn;

	 R = R*seed;
   rn = R/max;
   return rn;
}

//fun��o que checa os dados e imprime no arquivo
void checa()
{
 for (i=0; i<L; i++)
 {
   for (j=1; j<=L; j++)
   { 	
			if(floresta[i][j]==arvore)
			contarvore++;
			if(floresta[i][j]==vazio)
			contvazio++;
			if(floresta[i][j]==cinza)
			contcinza++;
			if(floresta[i][j]==fogo)
			contfogo++;
   }
 }
 fprintf (flo, "%d\t%lf\t%lf\t%lf\t%lf\n", t, contarvore/(double)(L*L), contvazio/(double)(L*L), contcinza/(double)(L*L), contfogo/(double)(L*L));
 
 marvore[t] += (contarvore/(double)(L*L));
 mvazio[t] += (contvazio/(double)(L*L));
 mcinza[t] += (contcinza/(double)(L*L)); 
 mfogo[t] += (contfogo/(double)(L*L));
 
 t++;
 contfogo=0; 
 contarvore=0; 
 contvazio=0; 
 contcinza=0;
}

//fun��o que imprime a floresta
void imprime()
{
 for (i=0; i<L; i++)
  {
   for (j=1; j<=L; j++)
   		printf("%c ", floresta[i][j]);  	
   		
   printf("\n");
  } 
  usleep(time);  
  system("clear");
}

//fun��o que transforma em pr� fogo e atualiza a lateral do cilindro
void atualiza()
{
 for (i=0; i<L; i++)
 {
   for (j=1; j<=L; j++)
   {
		 if(floresta[i][j]==pre)
		   floresta[i][j]=fogo; 
	 }
	 	 
	 floresta[i][0]=floresta[i][L];
   floresta[i][L+1]=floresta[i][1];
 }	  	
}

//fun��o para transformar em pr� fogo
void transforma()
{
 for (i=0; i<L; i++)
   for (j=0; j<=(L+1); j++)
		 if(floresta[i][j]==fogo)
		 {
		   if(floresta[i-1][j]==arvore && i>0)
		    floresta[i-1][j]=pre;
		   if(floresta[i+1][j]==arvore && i<L)
		    floresta[i+1][j]=pre; 
		   if(floresta[i][j-1]==arvore && j>0)
		    floresta[i][j-1]=pre;	
		   if(floresta[i][j+1]==arvore && j<(L+1))
		    floresta[i][j+1]=pre;	
		   floresta[i][j]=cinza;    
     }	
}

//gera a fun��o main
int main ()
{

  //definindo variaveis locais
  int  k;
  float rn;
  char arquivo[20];
  FILE *media;
 
	while(sim)
	{
 		t=0; steps=0;
	
		//gera o arquivo numerado	
 		for(k=0; k<sim; k++)	
 		{
 			sprintf(arquivo, "floresta%03d.dat", k);
 			flo = fopen(arquivo, "w");
 		}	
 
		//define a matriz floresta 
 		for (i=0; i<L; i++)
 		{
   		for (j=1; j<=L; j++)
   		{ 
    		 rn = rnumber();
     		 if (rn<=p)
     		 floresta [i][j] = arvore;
     		 else
     		 floresta[i][j] = vazio;
      }
    }
 
	  //gerando dados no tempo 0 e imprimindo 
		checa();
 
		//imprimindo a matriz floresta
	 	imprime();
    
		//coloca fogo na primeira linha e atualiza a lateral do "cilindro"
 		for (i=0; i<L; i++)
	  {
   		for (j=1; j<=L; j++)
   		{ 	
    	 	if(i==0 && floresta[i][j] == arvore)
     		floresta[i][j] = fogo;
   		}
   
   		floresta[i][0]=floresta[i][L];
   		floresta[i][L+1]=floresta[i][1];
		}

		//gerando dados no tempo e salvando no arquivo
		checa();
	
		//imprime a matriz floresta depois do fogo na primeira linha
		imprime();

		//coloca "pr� fogo" e transforma em cinza
		transforma(); 
 
		//transforma o "pr� fogo" em fogo e atualiza a lateral do "cilindro"
		atualiza(); 

		//gerando dados no tempo e salvando no arquivo 
		checa();
		
		//imprime a matriz floresta
 		imprime();
 
		//repete o looping at� a floresta terminar de queimar 
   	while(steps<stepsmax)
   	{ 
			//coloca "pr� fogo" e transforma em cinza
			transforma(); 
     
			//transforma o "pr� fogo" em fogo e atualiza a lateral do "cilindro"
			atualiza(); 

			//gerando dados no tempo e salvando no arquivo 
			checa();
	
			//imprime a floresta at� a pen�ltima simula��o
  		for (i=0; i<L; i++)
 	 		{
     		for (j=1; j<=L; j++)
       		printf("%c ", floresta[i][j]);
       	printf("\n");
   		}
   		usleep(time);
   		 		
   		if(steps<(stepsmax-1))
    		system("clear");
    		
   		steps++;
   }
	 fclose(flo);    
	 sim--; 
	}
	sim=sims;
	media = fopen ("Media.dat", "w");
	for(i=0; i<(stepsmax+3); i++)
		fprintf(media, "%d\t%lf\t%lf\t%lf\t%lf\n", i, marvore[i]/(sim), mvazio[i]/(sim), mcinza[i]/(sim), mfogo[i]/(sim));
	fclose(media);
}
