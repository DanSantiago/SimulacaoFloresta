#include <stdio.h>

#define max 4294967295.
#define vazio ' '
#define arvore 'Y'
#define fogo '*'
#define cinza '.'
#define L 40
#define stepsmax 157

//define o n�mero de simula��es
#define sims 1000

//vari�ves dos contadores
 int contfogo=0, contarvore=0, contvazio=0, contcinza=0, i, j;
 
//vari�veis para a media dos contadores 
 float mfogo[stepsmax+3], marvore[stepsmax+3], mvazio[stepsmax+3], mcinza[stepsmax+3];
 
//vari�veis usadas para controle das simula��es
 int t=0, steps=0, sim=sims;
 
//vari�veis para formar a floresta
 char floresta[L][L+2];
 char pre = 'X';
 float p = 0.65;
 unsigned R=58454585, seed=89974563;

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
  float rn;
  FILE *flo;
 	
	while(sim)
	{
 		t=0; steps=0;

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
 
	  //gerando dados no tempo
		checa();
		
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

		//gerando dados no tempo
		checa();
		
		//coloca "pr� fogo" e transforma em cinza
		transforma(); 
 
		//transforma o "pr� fogo" em fogo e atualiza a lateral do "cilindro"
		atualiza(); 

		//gerando dados no tempo
		checa();

		//repete o looping at� a floresta terminar de queimar 
   	while(steps<stepsmax)
   	{ 
			//coloca "pr� fogo" e transforma em cinza
			transforma(); 
     
			//transforma o "pr� fogo" em fogo e atualiza a lateral do "cilindro"
			atualiza(); 

			//gerando dados no tempo
			checa();
	
   		steps++;
   }
	 sim--; 
	}

	flo = fopen ("Media.dat", "w");
	for(i=0; i<(stepsmax+3); i++)
		fprintf(flo, "%d\t%lf\t%lf\t%lf\t%lf\n", i, marvore[i]/(sims), mvazio[i]/(sims), mcinza[i]/(sims), mfogo[i]/(sims));
	fclose(flo);
}
