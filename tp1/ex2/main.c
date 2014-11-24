#include<stdio.h>

struct rat 
{
  int num;
  int den;
};

int pgcd(int n1, int n2) 
{
  int r;
  while((r = n1 % n2) != 0) {
    n1 = n2;
    n2 = r;
  }
  return n2;
}


struct rat rat_simplifier(struct rat n) {
  int p = pgcd(n.num, n.den);
  n.num = n.num / p;
  n.den = n.den / p;
  return n;
}

struct rat rat_produit(struct rat n1, struct rat n2) 
{
  struct rat n3;
  n3.num = n1.num * n2.num;
  n3.den = n1.den * n2.den;
  
  return rat_simplifier(n3);
}

struct rat rat_somme(struct rat n1, struct rat n2) 
{
  struct rat n3;
  n3.num = n1.num * n2.den + n2.num * n1.den;
  n3.den = n1.den * n2.den;
  
  return rat_simplifier(n3);
}

struct rat rat_plus_petit(struct rat list[]) 
{
  int idx = 0, i = 1;
  
  while(list[i].den != 0) {
    int na = list[idx].num * list[i].den;
    int nm = list[i].num * list[idx].den;

    printf("%d = %d, ", na, nm); 
    if(na < nm) {
      printf("t");
      idx = i;
    }
    i++;
  }
  return list[idx];
}

int main(void)
{
  struct rat n1, n2, n3;
  n1.num = 1;
  n1.den = 2;
  n2.num = 2;
  n2.den = 3;
  
  n3 = rat_somme(n1, n2);
  printf("%d/%d\n", n3.num, n3.den);
  n3 = rat_produit(n1, n2);
  printf("%d/%d\n", n3.num, n3.den);


  struct rat list[] = {{5, 6}, {1, 10}, {2, 3}, {0, 0}};
  n3 = rat_plus_petit(list);
  printf("%d/%d\n", n3.num, n3.den);

  return 0;
}
