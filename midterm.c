//Garret Feng 886841253
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

//---------------------------- DO NOT TOUCH THIS CODE (lines 8 to 55) -------
// ABSTRACTION LAYER for differences in semaphores between Linux and macOS
//---------------------------- DO NOT TOUCH THIS CODE (lines 8 to 53) -------
#if defined __APPLE__
  #include <dispatch/dispatch.h>    // macOS ONLY
#endif 

#if defined __APPLE__ 
  #define semaphore_t dispatch_semaphore_t
#else 
  #define semaphore_t sem_t
#endif

semaphore_t semPing, semPong, semPyng, semPung;
semaphore_t semBox, semFox, semHouse, semMouse, semHere, semAny;

semaphore_t semaphore_create(semaphore_t* semaphore, unsigned int level) { 
  #if defined __APPLE__
    return dispatch_semaphore_create((long long)(level));
  #else 
    sem_init(semaphore, 0, level);
    return *semaphore;  
  #endif
}

void semaphore_wait(semaphore_t* semaphore) { 
  #if defined __APPLE__
    dispatch_semaphore_wait(*semaphore, DISPATCH_TIME_FOREVER);
  #else 
    sem_wait(semaphore);
  #endif
}

void semaphore_signal(semaphore_t* semaphore) { 
  #if defined __APPLE__
    dispatch_semaphore_signal(*semaphore);
  #else 
    sem_post(semaphore);
  #endif 
}

void semaphore_destroy(semaphore_t* semaphore) { 
  #if defined __APPLE__ 
    dispatch_release(*semaphore);
  #else 
    sem_destroy(semaphore);
  #endif
}
//---------------------------- DO NOT TOUCH THIS CODE (lines 8 to 55) -------

#define PINGS  4
#define PONGS PINGS

//1-3//
void* box(void* x) {       // pinger thread runner (x is not used currently)
  int pings = PINGS;
  while (pings-- > 0) {
    // TODO: call semaphore_wait...
	semaphore_wait(&semBox);
    printf("Not in a box\n");
	semaphore_signal(&semFox);
    // TODO: call semaphore_signal...
  }
  return NULL;
} 

void* fox(void* x) {        // ponger thread runner (x is not used currently)
  int pongs = PONGS;
  while (pongs-- > 0) {
     // TODO: call semaphore_wait...
    semaphore_wait(&semFox);
     printf("  Not with a fox\n"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semHouse);
     
  }
  return NULL;
}

void* house(void* x) {        // punger thread runner (x is not used currently)
  int pungs = PONGS;
  while (pungs-- > 0) {
     // TODO: call semaphore_wait...
    semaphore_wait(&semHouse);
     printf("  Not in a house\n"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semMouse);
     
  }
  return NULL;
}
void* mouse(void* x) {        // punger thread runner (x is not used currently)
  int pyngs = PINGS;
  while (pyngs-- > 0) {
     // TODO: call semaphore_wait...
    semaphore_wait(&semMouse);
     printf("  Not with a mouse\n"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semHere);
     
  }
  return NULL;
}

void* here(void* x) {        // punger thread runner (x is not used currently)
  int pyngs = PINGS;
  while (pyngs-- > 0) {
     // TODO: call semaphore_wait...
    semaphore_wait(&semHere);
     printf("  Not here or there\n"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semAny);
     
  }
  return NULL;
}

void* any(void* x) {        // punger thread runner (x is not used currently)
  int pyngs = PINGS;
  while (pyngs-- > 0) {
     // TODO: call semaphore_wait...
    semaphore_wait(&semAny);
     printf("  Not any where ! \n"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semBox);
     
  }
  return NULL;
}

//1-3//

//4//
// void* ping(void* x) {       // pinger thread runner (x is not used currently)
//   int pings = PINGS;
//   while (pings-- > 0) {
//     // TODO: call semaphore_wait...
//     semaphore_wait(&semPing);
//     printf("1 ");
//     // TODO: call semaphore_signal...
//     semaphore_signal(&semPong);
  
//     semaphore_wait(&semPing);
//     printf("1\n");
//     semaphore_signal(&semPing);
//   }
//   return NULL;
// } 

// void* pong(void* x) {        // ponger thread runner (x is not used currently)
//   int pongs = PONGS;
//   while (pongs-- > 0) {
//     // TODO: call semaphore_wait...
//     semaphore_wait(&semPong);
//     printf("2 "); 
//     // TODO: call semaphore_signal...
//     semaphore_signal(&semPung);

//     semaphore_wait(&semPong);
//     printf("2 ");
//     semaphore_signal(&semPing);
//   }
//   return NULL;
// }

// void* pung(void* x) {        // punger thread runner (x is not used currently)
//   int pungs = PONGS;
//   while (pungs-- > 0) {
//     // TODO: call semaphore_wait...
//     semaphore_wait(&semPung);
//     printf("3 "); 
//     // TODO: call semaphore_signal...
//     semaphore_signal(&semPyng);

//     semaphore_wait(&semPung);
//     printf("3 ");
//     semaphore_signal(&semPyng);

//     semaphore_wait(&semPung);
//     printf("3 ");
//     semaphore_signal(&semPyng);

//     semaphore_wait(&semPung);
//     printf("3 ");
//     semaphore_signal(&semPong);
//   }
//   return NULL;
// }

// void* pyng(void* x) {        // pynger thread runner (x is not used currently)
//   int pyngs = PINGS;
//   while (pyngs-- > 0) {
//     // TODO: call semaphore_wait...
//     semaphore_wait(&semPyng);
//     printf("4 "); 
//     // TODO: call semaphore_signal...
//     semaphore_signal(&semPung);

//     semaphore_wait(&semPyng);
//     printf("4 ");
//     semaphore_signal(&semPung);

//     semaphore_wait(&semPyng);
//     printf("4 ");
//     semaphore_signal(&semPung);
//   }
//   return NULL;
// }


// //4//


int main(int argc, const char * argv[]) {
  pthread_t pinger, ponger, punger, pynger;
  pthread_t Boxer, Foxer, Houseer, Mouseer, Hereer, Anyer;
  pthread_attr_t attr;
 
  semBox = semaphore_create(&semBox, 1);
  semFox = semaphore_create(&semFox, 0);
  semHouse = semaphore_create(&semHouse, 0);
  semMouse = semaphore_create(&semMouse, 0);
  semHere = semaphore_create(&semHere, 0);
  semAny = semaphore_create(&semAny, 0);

  pthread_attr_init(&attr);
  pthread_create(&Boxer, &attr, box, NULL);    // can create ponger first -- it will wait
  pthread_create(&Foxer, &attr, fox, NULL);
  pthread_create(&Houseer, &attr, house, NULL);
  pthread_create(&Mouseer, &attr, mouse, NULL);
  pthread_create(&Hereer, &attr, here, NULL);
  pthread_create(&Anyer, &attr, any, NULL);

  pthread_join(Boxer, NULL);
  pthread_join(Foxer, NULL);
  pthread_join(Houseer, NULL);
  pthread_join(Mouseer, NULL);
  pthread_join(Hereer, NULL);
  pthread_join(Anyer, NULL);
 
  // TODO: call semaphore_destroy twice
  semaphore_destroy(&semBox);
  semaphore_destroy(&semFox);
  semaphore_destroy(&semHouse);
  semaphore_destroy(&semMouse);
  semaphore_destroy(&semHere);
  semaphore_destroy(&semAny);

//   // TODO: change to print five lines of ping pong using semaphores
  printf("            success!\n"); 
  printf("\n\tdone...\n");
  return 0;
}


//task 1-3//
// ping  pong  pung  pyng
// ping  pong  pung  pyng
// ping  pong  pung  pyng
// ping  pong  pung  pyng
// ping  pong  pung  pyng
//             success!

//         done...



//task 4//
// 1 2 3 4 3 4 3 4 3 2 1
// 1 2 3 4 3 4 3 4 3 2 1
// 1 2 3 4 3 4 3 4 3 2 1
// 1 2 3 4 3 4 3 4 3 2 1
// 1 2 3 4 3 4 3 4 3 2 1
//             success!

//         done...

//midterm//

