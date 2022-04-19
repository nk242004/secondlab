#include <iostream>
 #include <stdio.h>
 #include <stdlib.h>

using namespace std;














/* MinUnit testing frameworks for C 
 * macroses and initial function declaration 
 */
 #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
 #define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
 #define null NULL
 extern int tests_run;
 void run () ;

 
/* ADT declaration section */
typedef char elementtype;
typedef struct A {
        elementtype element;
        struct A* next;
} celltype;
typedef celltype* LIST;
typedef celltype* position;
/* ADT API section */
LIST MAKENULL (LIST L);
position END (LIST L);
position FIRST (LIST);
position NEXT (position p, LIST L);
LIST INSERT (elementtype x, position p, LIST L);
LIST DELETE (position p, LIST L);
elementtype RETRIEVE (position p, LIST L);
position LOCATE (elementtype x, LIST L);

/* Support functions */
#define newnode() (celltype*)malloc(sizeof(celltype))
#define printlist(L) {for (position _t=L;(_t->next!=null)||(!printf("\n"));_t=_t->next) {printf ("%c,",_t->next->element);}} 
#define NONE (celltype*)null























 int tests_run = 0;
 
 static char * test_makenull() {
     LIST L;
     L = MAKENULL(L);
     mu_assert("test MAKENULL fail: no header of the list", L != null);
     mu_assert("test MAKENULL fail: list not empty", L->next == NONE);     
     return 0;
 }
 
static char * test_end() {
     LIST L;
     position pos = END(MAKENULL(L));
     mu_assert("test END fail: returned not last element of the list", (pos!=null)&&(pos->next == NONE));
     return 0;
 }

static char * test_first() {
     LIST L = MAKENULL(L);
     position pos = FIRST(L);
     mu_assert("test FIRST fail: return not first element of the list", pos == L);          
     return 0;
 }
 
 static char * test_next() {
     LIST L = MAKENULL(L);
     position t = NEXT(FIRST(L), L);
     mu_assert("test NEXT fail: return not next element of the list", t == NONE);
     return 0;
 }

 static char * test_insert() {
     LIST L;
     L = MAKENULL(L);
     elementtype arr[] = {'a','b','c','d'};
     
     INSERT(arr[2], END(L), L);
     position t = L->next;
     mu_assert("test INSERT fail: element not inserted to the list", (t!=null)&&(t->element==arr[2]));
           
     INSERT(arr[3], END(L), L);
     t = END(L);
     mu_assert("test INSERT fail: element not inserted to the end of list", (t!=null)&&(t->element==arr[3]));
     
     INSERT(arr[0], FIRST(L), L);
     t = FIRST(L)->next;
     mu_assert("test INSERT fail: element not inserted to the begin of list", (t!=null)&&(t->element==arr[0]));
     
     INSERT(arr[1], FIRST(L)->next, L);
     position p = FIRST(L);
     int i = 0;
     while (p->next!=null) {
          p = p->next;     
          mu_assert("test INSERT fail: wrong elements order", p->element==arr[i++]);
     }
     mu_assert("test INSERT fail: not all elements inserted", i==4);
           
     return 0;
 }
 
 static char * test_delete() {
     LIST L;
     
     L = MAKENULL(L);
     
     elementtype arr[] = {'a','b','c','d','e'};
     int i;
     for (i =0; i<5; i++)
		INSERT(arr[i], END(L), L);  	   
     
     DELETE(FIRST(L)->next, L);
     position p = FIRST(L);
     
     i = 0;
     
     while ((p->next!=null)&&(i<6)) {
          i++;
          p=p->next;
     }
     
     position t = FIRST(L)->next;
     mu_assert("test DELETE failed: element not deleted", i==4);

     mu_assert("test DELETE failed: wrong element deleted", (t!=null)&&(t->element==arr[0]));
     mu_assert("test DELETE failed: wrong element deleted", (t->next!=null)&&(t->next->element==arr[2]));         
	     
     DELETE(END(L), L);
     t = END(L);
     mu_assert("test DELETE failed: element not deleted from the end of list", (t!=null)&&(t->element==arr[4]));
     
     DELETE(FIRST(L), L);
     t = FIRST(L)->next;
     mu_assert("test DELETE failed: element not deleted from the begin of list", (t!=null)&&(t->element==arr[2]));
     
     return 0;
 }
 
 static char * test_retrieve() {
     LIST L;
     L = MAKENULL(L);
     elementtype arr[] = {'a','b','c'};
     int i;
     for (i =0; i<3; i++)
          INSERT(arr[i], END(L), L);
     
     position t = FIRST(L);
     mu_assert("test RETRIEVE failed: wrong element retrieved", RETRIEVE(t,L)==arr[0]);
     t = NEXT(t, L);
     mu_assert("test RETRIEVE failed: no next element", (t!=null));
     mu_assert("test RETRIEVE failed: wrong element retrieved", RETRIEVE(t,L)==arr[1]);
     t = NEXT(t, L);
     mu_assert("test RETRIEVE failed: no next element", (t!=null));
     mu_assert("test RETRIEVE failed: wrong element retrieved", RETRIEVE(t,L)==arr[2]);
     
     return 0;
 }
 
 static char * test_locate() {
     LIST L;
     L = MAKENULL(L);
     elementtype arr[] = {'a','b','c','d','e'};
     int i;
     for (i =0; i<5; i++)
          INSERT(arr[i], END(L), L);
     
     position t = LOCATE(arr[1], L);
     
     mu_assert("test LOCATE failed: can't locate element position in list", (t!=null));
     mu_assert("test LOCATE failed: wrong position for element located", RETRIEVE(t,L)==arr[1]);
     
     t = LOCATE('x', L);
     
     mu_assert("test LOCATE failed: found a position for a non-existent list element", (t==null));
     
     return 0;
 }
 
 
static char * all_tests() {
     mu_run_test(test_makenull);
     mu_run_test(test_end);
     mu_run_test(test_first);
     mu_run_test(test_next);
     mu_run_test(test_insert);     
     mu_run_test(test_delete);
     mu_run_test(test_retrieve);
     mu_run_test(test_locate);

     return 0;
 }
 
 void run () {
     printf("*** RUN TESTS ***\n");
     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
         printf("*** TESTS FAILED ***\n");
         printf("Tests run: %d\n", tests_run);     
     }
     else {
         printf("*** ALL TESTS PASSED ***\n*** WELL DONE ***\n");
     }

 }













/* 
 * Реалізація однозвязного списку 
 * Типи даних:
   LIST - АТД список, кожен вузол списку складається з двох полів:
        element - елемент, що міститсья в цьому вузлі
        next - позиція наступного вузла списку
   position - позиція елементу в списку
   elementtype - тип значення, що зберігається в елементі списку
     
   допоміжні функції:
   newnode () - створює новий вузол списку типу celltype
   printlist(L) - друкує перелік елементів, що знаходятсья в списку L;
 */ 
 
 
/* 
 * функція створює порожній список  
 */  
LIST MAKENULL (LIST L) {
	L = newnode();

	L->next = NONE;	

	return L;
}
	 
/* 
 * функція повертає позицію останнього елементу 
 * в списку L
 */ 
position END (LIST L) {         
        
	position current = L;
		
	while(current->next != NONE)
	{
		current = current->next;
	}
		
	return current;
}

/* 
 * функція повертає позицію першого елементу в 
 * в списку L
 */
position FIRST (LIST L) { 
    position current = L; 

    return current;
}

/* 
 * функція повертає наступну позицію після 
 * позиції p в списку L
 */
position NEXT (position p, LIST L) {
 	
	position current = L;
		
	while(current != NONE)
	{
		if(p != current)
			current = current->next;
		else 
			break;		
	}
       
    return current->next;
}

/* 
 * функція додає елемент x, в позиції p
 * списку L
 */
LIST INSERT (elementtype x, position p, LIST L) {           
 	position current = L;
	
	while(current != NONE)
	{
		if(p != current)
			current = current->next;
		else
			break;
	}
	position temp = current->next;
	
	current->next = newnode();
	current->next->element = x;

	current->next->next = temp;	  
   
    return L;     
}

/* 
 * функція видалає елемент, що знаходиться на 
 * позиції p в списку L
 */
LIST DELETE (position p, LIST L) {    
         
 	position current = L;	
		
	while(current != NONE)
	{
		if(p != current)
			current = current->next;
		else 
			break;
	}
	
	if(current->next != NONE)
	{
		current = current->next;
		
		current->element = current->next->element;
	    current->next = current->next->next;
	}

	 
    return L;     
}

/* 
 * фунція повертає значення елементу що знаходиться на 
 * позиції p в списку L
 */
elementtype RETRIEVE (position p, LIST L) {
 	position current = L;
		
	while(current != NONE)
	{
		if(p != current)
			current = current->next;
		else 
			break;
	}
	
    return current->next->element;  
}

/* 
 * функція повертає позицію елементу з значенням x в списку L,
 * якщо такого елементу не існує, то повертається NONE
 */
position LOCATE (elementtype x, LIST L) {
		
 	position current = L;
	
	if(current->next == NONE)
		return NONE;
	
	while(current->next != NONE)
	{
		if(x != current->next->element)
		{
			current = current->next;
			continue;
		}
		else
		{
			return current;
		}
		
		break;
	}
    
	return NONE; 
}


 
int main(int argc, char **argv) {     
     run();
     system("PAUSE");
     return 0;
 }