#include "cutest/CuTest.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Add your tests here
 * A few sample tests
 * are provided
 */


// Tests for integer equals
void TestOne(CuTest *tc) {
  int two = 2;
  int four = 4;
  CuAssertIntEquals(tc, four, two+two);
}

// Test for string equals
void TestTwo(CuTest *tc) {
  char* lol = "lol";
  char* alsoLol = "lol";
  CuAssertStrEquals(tc, lol, alsoLol);
}

/*
Tests for True and False
pay attention to cleanStack function call as
you will be using it in your every test case
*/
void TestTrueFalse(CuTest *tc) {
  Stack* s = makeStack(10);
  CuAssertTrue(tc, isEmpty(s));
  push(s, 1, "black");
  CuAssertFalse(tc, isEmpty(s));
  cleanStack(s);
}


// Tests for Pointer equals
void TestPtrEquals(CuTest *tc) {
  Element* e = NULL;
  CuAssertPtrEquals(tc, NULL, e);
}

void TestPush(CuTest *tc)
{
	Stack* s = makeStack(10);
	push(s,1,"black");
	push(s,98,"white");
	for(int i = 0; i<= s->top; i++)
	{
		printf("The key of first element is %d, The char is %s\n", (s->elements)[i]->key, s->elements[i]->value);
	}
	
	cleanStack(s);
}

void TestisFull(CuTest *tc)
{
	Stack* s = makeStack(10);
	CuAssertTrue(tc,isEmpty(s));
	for(int i = 0; i<10;i++)
	{
		CuAssertTrue(tc,push(s,3,"test"));
	}
	CuAssertTrue(tc,isFull(s));
	printf("The value is %d, the char is %s\n",s->elements[s->top]->key, s->elements[s->top]->value);
	cleanStack(s);
}
void TestCapacity(CuTest *tc)
{
	
	Stack* s = makeStack(10);
	CuAssertTrue(tc,s->capacity == 10);
	cleanStack(s);
}

void testPop(CuTest *tc)
{
	Stack* s = makeStack(10);
	push(s,1,"Red");
	push(s,2,"Green");
	push(s,3,"Blue");
	push(s,4,"Black");
	Element* a = pop(s);
	CuAssertTrue(tc,a->key==4);
	CuAssertTrue(tc,strcmp(a->value,"Black")==0);
	printf("key is %d, value is %s\n",a->key,a->value);
	free(a);
	Element* b = pop(s);
	free(b);
	CuAssertTrue(tc,s->top==1);
	cleanStack(s);
}

void testMultiPop(CuTest *tc)
{
	Stack* s = makeStack(10);
		push(s,1,"Red");
		push(s,2,"Green");
		push(s,3,"Blue");
		push(s,4,"Black");
		push(s,5,"Yellow");
		
	Element** array = multiPop(s,2);
	CuAssertTrue(tc,array[0]->key==5);
	CuAssertTrue(tc,strcmp(array[0]->value,"Yellow")==0);
	CuAssertTrue(tc,array[1]->key==4);
	CuAssertTrue(tc,strcmp(array[1]->value,"Black")==0);
	
	Element** secondArray = multiPop(s,99);
	CuAssertTrue(tc,secondArray[0]->key==3);
	CuAssertTrue(tc,strcmp(secondArray[0]->value,"Blue")==0);
	CuAssertTrue(tc,secondArray[1]->key==2);
	CuAssertTrue(tc,strcmp(secondArray[1]->value,"Green")==0);
	CuAssertTrue(tc,secondArray[2]->key==1);
	CuAssertTrue(tc,strcmp(secondArray[2]->value,"Red")==0);
	for(int i=0;i<2;i++)
	{
		free(array[i]);
	}
	
	for(int j=0;j<3;j++)
	{
		free(secondArray[j]);
	}
	
	//Element** secondArray = multiPop(s,99);
	free(secondArray);
	free(array);
	cleanStack(s);
}


void testPushUnique(CuTest *tc)
{
	Stack* s = makeStack(10);
			push(s,1,"Red");
			push(s,2,"Green");
			push(s,3,"Blue");
			push(s,4,"Black");
			push(s,5,"Yellow");
	CuAssertFalse(tc,pushUnique(s,5,"Yellow"));
	cleanStack(s);
}
void testPeek(CuTest *tc)
{
	Stack* s = makeStack(10);
				push(s,1,"Red");
				push(s,2,"Green");
				push(s,3,"Blue");
				push(s,4,"Black");
				push(s,5,"Yellow");
	Element* e = peek(s);
	CuAssertTrue(tc,e->key==5);
	push(s,6,"Grey");
	Element* newPeek = peek(s);
	CuAssertTrue(tc,newPeek->key==6);
	cleanStack(s);
}

void testSearch(CuTest *tc)
{
	Stack* s = makeStack(10);
					push(s,1,"Red");
					push(s,2,"Green");
					push(s,3,"Blue");
					push(s,4,"Black");
					push(s,5,"Yellow");
	CuAssertTrue(tc,search(s,4,"Black")==2);
	CuAssertTrue(tc,search(s,0,"Black")==-1);
	cleanStack(s);
}


void testClear(CuTest *tc)
{
	Stack* s = makeStack(10);
						push(s,1,"Red");
						push(s,2,"Green");
						push(s,3,"Blue");
						push(s,4,"Black");
						push(s,5,"Yellow");
	clear(s);
	CuAssertTrue(tc,s->top == -1);
	CuAssertTrue(tc,currentSize(s)==0);
	CuAssertTrue(tc,isEmpty(s)==true);
	cleanStack(s);
}
void testReverse(CuTest *tc)
{
	Stack* s = makeStack(10);
							push(s,1,"Red");
							push(s,2,"Green");
							push(s,3,"Blue");
							push(s,4,"Black");
							push(s,5,"Yellow");
	reverse(s);
	CuAssertTrue(tc,s->top ==4);
	CuAssertTrue(tc,s->elements[s->top]->key==1);
	CuAssertTrue(tc,s->elements[0]->key==5);
	CuAssertTrue(tc,s->elements[1]->key==4);
	CuAssertTrue(tc,s->elements[2]->key==3);
	CuAssertTrue(tc,s->elements[3]->key==2);
	CuAssertTrue(tc,s->elements[4]->key==1);
	cleanStack(s);
}


void testResizeGrowth(CuTest *tc)
{
	Stack* s = makeStackG(10,0.5);
	CuAssertTrue(tc,push(s,1,"Red"));
	push(s,2,"Green");
	push(s,3,"Blue");
	push(s,4,"Black");
	push(s,5,"Yellow");
	CuAssertTrue(tc,s->capacity==10);
	push(s,6,"White");
    CuAssertTrue(tc, peek(s)->key==6);
	CuAssertTrue(tc,s->capacity==20);
	Element* pElement = pop(s);
	CuAssertTrue(tc,s->capacity==20);
	CuAssertTrue(tc,pElement->key==6);
	for(int i = 5; i< s->capacity; i++)
	{
	  CuAssertPtrEquals(tc,s->elements[i], NULL);
	}
	free(pElement);
	cleanStack(s);
	
}

void testResizeShrink(CuTest *tc)
{
	Stack* s = makeStackGnS(10,0.5,0.5);
	push(s,1,"Red");
	push(s,2,"Green");
	push(s,3,"Blue");
	push(s,4,"Black");
	push(s,5,"Yellow");
	CuAssertTrue(tc,s->capacity==10);
	push(s,6,"White");
	CuAssertTrue(tc,s->capacity==20);
	Element* pElement = pop(s);
	CuAssertTrue(tc,s->capacity==10);
	CuAssertTrue(tc,pElement->key==6);
	free(pElement);
	cleanStack(s);
	
}

void testMultiPopWithShrink(CuTest *tc)
{
	Stack* s = makeStackGnS(10,0.5,0.5);
	for(int i = 0; i<20; i++)
	{
		push(s,i,"test");
	}
	CuAssertTrue(tc,s->capacity==40);//from 0 to 19;
	Element** array = multiPop(s,7);
	CuAssertTrue(tc,s->capacity==20);
	for(int i = 13; i< s->capacity; i++)
	{
		CuAssertPtrEquals(tc,s->elements[i],NULL);
	}
	CuAssertTrue(tc,s->elements[s->top]->key==12);
	for(int k = 0; k<7; k++)
	{
		CuAssertTrue(tc,array[k]->key == 19-k);
	}
	for(int j=0;j<7;j++)
	{
		free(array[j]);
	}
	free(array);
	cleanStack(s);
	
}

void testExpand(CuTest *tc){
    Stack* s = makeStackG(10,0.5);

    expandCapacity(s);
    CuAssertTrue(tc,s->capacity ==20);
    cleanStack(s);
}




CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();

  /** ADD YOUR TESTS HERE **/
  SUITE_ADD_TEST(suite, TestOne);
  SUITE_ADD_TEST(suite, TestTwo);
  SUITE_ADD_TEST(suite, TestTrueFalse);
  SUITE_ADD_TEST(suite, TestPtrEquals);
  SUITE_ADD_TEST(suite, TestPush);
  SUITE_ADD_TEST(suite, TestisFull);
  SUITE_ADD_TEST(suite, TestCapacity);
  SUITE_ADD_TEST(suite, testPop);
  SUITE_ADD_TEST(suite, testMultiPop);
  SUITE_ADD_TEST(suite, testPushUnique);
  SUITE_ADD_TEST(suite, testPeek);
  SUITE_ADD_TEST(suite, testSearch);
  SUITE_ADD_TEST(suite, testReverse);
  SUITE_ADD_TEST(suite, testResizeGrowth);
  SUITE_ADD_TEST(suite, testResizeShrink);
  SUITE_ADD_TEST(suite, testMultiPopWithShrink);
  //SUITE_ADD_TEST(suite, testExpand);
  return suite;
}

// Don't edit anything below this line

void RunAllTests(void) {
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();
  CuSuite* ourSuite = StrUtilGetSuite();

  CuSuiteAddSuite(suite, ourSuite);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  CuStringDelete(output);
  CuSuiteDelete(suite);
  free(ourSuite);
}

int main(void) {
  RunAllTests();
  return 0;
}
