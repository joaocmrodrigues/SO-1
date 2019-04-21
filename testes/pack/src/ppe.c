/* ppe.c
 *  The Hungry Birds Problem - do the simulation with mutexes and conditions variables, guaranteeing NO busy waiting!
 *
Program invocation:
	./ppe <n. babybirds> <n. food portions> <n. refills>

Invocation example:
     ./ppe 3 5 10000
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define MAXBABIES 100



pthread_mutex_t mut;
pthread_cond_t var ;
/////////minhas variaveis globais////
long count = 0 ;
/////////////////////////////////////

int finish = 0;	// termination of simulation (flagged by parent bird)
int foodbits = 0;	// is the current number of bits of food in the "food-teat"

/*struct checkerarg {	// conveys info to checker
	int f;	// number of bits of food of each refill
	long r;	// number of refills - parent bird can then retire!
	int *working;	// ptr to binary state of parent bird
	int *eating;	// ptr to number of babies that are eating at a time
	pthread_mutex_t *mut; // for overall concurrency control to shared data
};*/
struct parentarg {	// conveys info to parent bird
	int f;	// number of bits of food of each refill
	long r;	// number of refills - parent bird can then retire!
	int *working;	// ptr to binary state of parent bird
};
struct babyarg {	// conveys info to baby birds
	int id;	// baby identification
	int *eating;	// ptr to number of babies that are eating at a time
};

//void *checker(void *);	// checker thread
void *parent(void *);	// parent thread
void *baby(void *);	// baby thread


int main(int argc, char *argv[]) {

setbuf(stdout, NULL);
	int B;	// number of babies
	int F;	// number of bits of food of each refill
	long R;	// number of refills - parent bird can then retire!
	int working = 0;	// represents the binary state of parent bird:
	int eating = 0;	// number of babies that are eating at a time
	struct parentarg pa;	// conveys info to parent bird (and checker!)
	//struct checkerarg ca;	// conveys info to parent bird (and checker!)
	struct babyarg ba[MAXBABIES];	// conveys baby identification
	pthread_t  tparent, tbaby[MAXBABIES]; //tchecker,

if( argc != 4) {
	printf("Program invoked with wrong number of arguments.\n");
	printf("Program usage: %s <n. babybirds> <n. food portions> <n. refills>\n", argv[0]);
	exit(-1);
    }
else {
	B = atoi(argv[1]);
	F = atoi(argv[2]);
	R = atoi(argv[3]);
	}
printf("\nSimulation started\n");

// a preencher com o seu código:
pthread_mutex_init(&mut, NULL);
pthread_cond_init(&var, NULL);
// preparar args e criar thread checker (aqui, pôr o membro mut a NULL!)
/*ca.f = F;
ca.r = R;
ca.working = working;
ca.eating = eating ;

pthread_create(&tchecker, NULL, checker , &ca);*/
// preparar args e criar thread parent bird
pa.f = F;
pa.r = R;
pa.working = working;

pthread_create(&tparent, NULL , parent, &pa);
// preparar args e criar threads baby birds
for(int i = 0 ; i < B ; i++){

	ba[i].id = i;
	ba[i].eating = eating;
	pthread_create(&tbaby[i], NULL , baby , &ba[i]);


}

// esperar por thread parent
pthread_join(tparent, NULL);
// esperar por threads baby e recolher os seus resultados. Usar:
long *pbits_eaten;	// get baby bird's eating statistics
for(int i = 0 ; i< B ; i++ ){
	pthread_join(tbaby[i] , (void **)&pbits_eaten);
	
	printf ("\nNumber of bits of food eaten by baby %d / total of bits: %ld / %ld ",i  , *pbits_eaten, (F*R) );
	*pbits_eaten = 0;
}
// Usar: printf ("\nNumber of bits of food eaten by baby %d / total of bits: %ld / %ld ", ? , ?, ? );


// NÃO esperar pelo thread checker, pois é "detached"!
pthread_mutex_destroy(&mut);
printf("\nSimulation finished\n");

exit (0);
} // main()


void *parent(void *arg) {	// parent bird thread
	struct parentarg *pa = (struct parentarg * )arg;
	
	printf ("\n\tParent starting");

// a preencher com o seu código:
	
	
	
		while( pa->r >= 0 ){

			if(foodbits == 0){
				pthread_mutex_lock(&mut);
				printf ("\n\tParent received args f (%d), r (%ld), working (%d)", pa->f , pa->r  , pa->working );

				pa->working = 1;
				foodbits = pa->f;
				pa->r--;
				pa->working = 0;
				pthread_mutex_unlock(&mut);
			}
			
		pa->working = 0;	


		}

	finish = 1;

// Usar: printf ("\n\tParent received args f (%d), r (%ld), working (%d)", ? , ? , ? );
	
	printf ("\n\tParent finishing");

return NULL;
} // parent()


void *baby(void *arg){	// baby thread
	struct babyarg *ba = (struct babyarg *) arg;



	int count=0, *output = malloc(sizeof(int));

	while(finish != 1){

		if(foodbits >0 ){
			pthread_mutex_lock(&mut);
			ba->eating=1;
			foodbits--;
			count++;
			ba->eating = 0;
			pthread_mutex_unlock(&mut);

		}
		
		ba->eating = 0;

		
	}


*output = count;
// a preencher com o seu código:

// Usar: printf ("\n   Baby bird %d beginning",? );
	printf ("\n   Baby bird %d beginning", ba->id );
// Usar: printf ("\n   Baby received args id (%d), eating (%d)",  , ? );
	 printf ("\n   Baby received args id (%d), eating (%d)", ba->id , ba->eating);
// Usar: printf ("\n   Baby bird %d finishing", ? );
	 printf ("\n   Baby bird %d finishing", ba->id );


// Usar: return (?);
	 return (void*)output;


	}
	
 // baby()