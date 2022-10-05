//DANIEL TANUWIJAYA - 2440005883
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 100

struct node{
 char ID[100];
 char name[100];
 char rarity[20];
 char quality[100];
 int price;
 struct node *next;
};

struct node *hash[SIZE];

struct node *createNewNode(char ID[],char name[],char rarity[], char quality[], int price){
 struct node *newNode=(node *)malloc(sizeof(node));
 strcpy(newNode->ID,ID);
 strcpy(newNode->name,name);
 strcpy(newNode->rarity,rarity);
 strcpy(newNode->quality, quality);
 newNode->price = price;
 newNode->next = NULL;
 
 return newNode;
}

int hashFuntion(char id[]){ // ini buat nambahin ascii (jumlahin semua)
 int sum = 0;
 for(int i=0;i<strlen(id);i++){
  sum+= i;
 }
 return sum%SIZE;
}

void push(char ID[], char name[], char rarity[], char quality[], int price){
 int key = hashFuntion(ID);
 struct node *newNode = createNewNode(ID, name, rarity, quality, price);
 if(hash[key] == NULL) hash[key] = newNode;
 else{
  node *curr = hash[key];
  while(curr->next != NULL){
   curr = curr->next;
  }
  curr->next = newNode;
 }
}

void deletes(char ID[]){
 int key = hashFuntion(ID);
 if(hash[key]==NULL){
  printf("Monster not found!\n");
 }else{
  if(strcmp(hash[key]->ID,ID) == 0){
   free(hash[key]);
   hash[key]=NULL;
   printf("Monster has been removed!\n");
   return;
  }else{
   node *curr = hash[key];
   while(curr->next != NULL){
    if(strcmp(curr->next->ID,ID) == 0){
     node *temp = curr->next;
     curr->next = temp->next;
     free(temp);
     printf("Monster has been removed!\n");
    }
    curr = curr->next;
   }
  }
  printf("Monster not found!");
 }
}

void view(){
 for(int i=0;i<SIZE;i++){
  if(hash[i]!=NULL){
   printf("Skin List\n\n");
   node *curr = hash[i];
   while(curr!=NULL){
    printf("ID : %s", curr->ID);
    printf("Name : %s", curr->name);
    printf("Rarity : %s", curr->rarity);
    printf("Quality : %lf", curr->quality);
    printf("Price : %d", curr->price);
    curr = curr->next;
   }
  }
 }
}

int main(){
 int menu;
 do{
  printf("\nGOTradePlus\n");
  printf("===========\n");
  printf("1. View List\n");
  printf("2. Insert Item\n");
  printf("3. Delete Item\n");
  printf("4. Exit\n");
  printf(">> ");
  scanf("%d",&menu); getchar();
  system("cls");
  if(menu == 1){
    NULL;
	}else if(menu == 2){
    	char name[100];
    	do{
    		 printf("Input Skin Name [length must be between 5 - 20] : ");
     		scanf("%[^\n]",&name);
    		 getchar();
    	}while(!(strlen(name)>=5 && strlen(name)<=20));
    
    	int rarity;
    		do{
    		 	printf("Input Skin Rarity [Must Between 1 - 4] : ");
     			scanf("%d",&rarity);
     			getchar();
    		}while(rarity!=1 && rarity!=2 && rarity!=3 && rarity!=4);
    
   		 char quality[100];
   			do{
		    	printf("Input Skin Quality [Factory New || Field-Tested || Battle-Scarred] (Case Sensitive): ");
		   		 scanf("%[^\n]",&quality);
     			getchar();
    		}while(strcmp(quality, "Factory New")!=0 && strcmp(quality, "Field-Tested")!=0 && strcmp(quality, "Battle-Scarred")!=0);
    
    	int price;
    		do{
     			printf("Input Skin Price [Must be higher than 0]: ");
     			scanf("%d",&price);
     			getchar();
    		}while(!(price>0));
    
    	char confirm;
    		do{
     			printf("Do you want to confirm? [Y/N](Case Sensitive):");
     			scanf("%c",&confirm);
     			getchar();
    		}while(confirm!='Y' && confirm!='N');
	}
	else if(menu == 3){
	}
		 
  }
  
 while(menu!=4);
 
 
return 0;
}
