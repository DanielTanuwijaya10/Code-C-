#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int spellsize;
int size[150];
char scott[100][100];
bool find;

struct data{
    char word[100];
    data *left;
    data *rightrotate;
    int height;
};

data *root[100];

int max(int a, int b){
    if (a>b){
        return a;
    } else {
        return b;
    }
}

int height(data *curr){
    if (curr==NULL){
        return 0;
    } else {
        return curr->height;
    }
}

data *rightrotate(data *curr){
    data *leftchild=curr->left;
    data *leftrightchild=leftchild->rightrotate;
    leftchild->rightrotate=curr;
    curr->left=leftrightchild;
    curr->height=max(height(curr->left), height(curr->rightrotate)) + 1;
    leftchild->height=max(height(leftchild->left), height(leftchild->rightrotate)) + 1;
    return leftchild;
}

int getbalance(data *curr){
    if (curr==NULL){
        return 0;
    } else {
        return height(curr->left) - height(curr->rightrotate);
    }
}

data *createdict(char *word){
    data *newword=(data *)malloc(sizeof(data));
    strcpy(newword->word, word);
    newword->left=NULL;
    newword->rightrotate=NULL;
    newword->height=1;
    return newword;
}

data *leftrotate(data *curr){
    data *rightchild=curr->rightrotate;
    data *rightleftchild=rightchild->left;
    rightchild->left=curr;
    curr->rightrotate=rightleftchild;
    curr->height=max(height(curr->left), height(curr->rightrotate)) + 1;
    rightchild->height=max(height(rightchild->left), height(rightchild->rightrotate)) + 1;
    return rightchild;
}

data *insertword(data *curr, char *word){
    if (curr==NULL) {
        return createdict(word);
    }

    if (strcmp(word, curr->word) < 0) {
        curr->left=insertword(curr->left, word);
    } else if (strcmp(word, curr->word) > 0) {
        curr->rightrotate=insertword(curr->rightrotate, word);
    } else {
        return curr;
    }
    curr->height=max(height(curr->left), height(curr->rightrotate)) + 1;
    int counter=getbalance(curr);
    if (counter > 1 && getbalance(curr->left)>=0) {
        return rightrotate(curr);
    } 
	else if (counter < -1 && getbalance(curr->rightrotate)<=0){
        return leftrotate(curr);
    } 
	else if (counter > 1 && getbalance(curr->left)<0) {
        curr->left=leftrotate(curr->left);
        return rightrotate(curr);
    } 
	else if (counter < -1 && getbalance(curr->rightrotate)>0){
        curr->rightrotate=rightrotate(curr->rightrotate);
        return leftrotate(curr);
    }
    return curr;
}

data *tmp(data *curr){
    data *temp=curr->left;
    while (temp->rightrotate) {
        temp=temp->rightrotate;
    }
    return temp;
}

data *insertdict(data *root, char word[]){    
    return insertword(root, word);
}

void printdict(data *curr){
    if (curr!=NULL){
        printdict(curr->left);
        printf("-%s\n", curr->word);
        printdict(curr->rightrotate);
    }
}

data *delword(data *curr, char *word){
    if (!curr){
        return NULL;
    }
    if (strcmp(word, curr->word)>0){
        curr->rightrotate=delword(curr->rightrotate, word);
    } 
    else if (strcmp(word, curr->word)<0){
        curr->left=delword(curr->left, word);
    }
	else {
        if (curr->left==NULL&&curr->rightrotate==NULL){
            free(curr);
            curr=NULL;
            return NULL;
        }
        if (curr->left==NULL){
            data *temp=curr->rightrotate;
            free(curr);
            curr=NULL;
            return temp;
        } 
		if (curr->rightrotate==NULL){
            data *temp=curr->left;
            free(curr);
            curr=NULL;
            return temp;
        }
        data *temp=tmp(curr);
        strcpy(curr->word, temp->word);
        curr->left=delword(curr->left, temp->word);
    }
    curr->height=max(height(curr->left), height(curr->rightrotate)) + 1;
    int temp=getbalance(curr);
    if (temp>1&&getbalance(curr->left)<0){
        curr->left=leftrotate(curr->left);
        return rightrotate(curr);
    }
    if (temp>1&&getbalance(curr->left)>=0){
        return rightrotate(curr);
    }
    if (temp<-1&&getbalance(curr->rightrotate)>0){
        curr->rightrotate=rightrotate(curr->rightrotate);
        return leftrotate(curr);
    }
    if (temp<-1&&getbalance(curr->rightrotate)<=0){
        return leftrotate(curr);
    }
    return curr;
}

data *search(data *curr, char *word){
    if (!curr){
        return NULL;
    } 
	else if (strcmp(word, curr->word) < 0){
        return search(curr->left, word);
    } 
	else if (strcmp(word, curr->word) > 0){
        return search(curr->rightrotate, word);
    } 
	else {
        return curr;
    }
}

data *deldict(data *root, char *word){
    if (root == NULL) {
        return NULL;
    }
    data *look = NULL;
    look = search(root, word);
    if (look == NULL){
        return root;
    }
    root = delword(root, word);
    return root;
}

int main(){
	int a;
	char menu [100], spell[100], word[100];
    scanf("%d", &a);
    for(int i=0;i<a;i++){
        scanf("%s", &menu);
        printf("Case %d:\n",i+1);
        if(strcmp(menu, "ADD")==0){
            scanf("%s %s",&spell,&word);
            find = false;
            for(int j=0;j<spellsize;j++){
                if(strcmp(spell,scott[j])==0){
                    root[j]=insertdict(root[j], word);
                    size[j]++;
                    find=true;
                }
            }
            if(find==false){
                root[spellsize]=NULL;
                root[spellsize]=insertdict(root[spellsize], word);
                strcpy(scott[spellsize], spell);
                size[spellsize]++;
                spellsize++;
            }
            printf("Successfully Added\n");
        } 
		else if(strcmp(menu, "SHOW-ALL")==0){
            for(int j=0;j<spellsize;j++){
                if(strcmp(scott[j], "-")==0) 
					continue;
                printf("%s (%d):\n", scott[j], size[j]);
                printdict(root[j]);
            }
        } 
		else if(strcmp(menu, "SHOW-LANG")==0){
            scanf("%s", &spell);
            find = false;
            for(int j=0;j<spellsize;j++){
                if(strcmp(spell, scott[j])==0){
                    printf("%s (%d):\n", scott[j], size[j]);
                    printdict(root[j]);
                }
            }
            if(find == false){
                printf("%s language not found\n", spell);
            } 
			else {
                printf("Succesfully deleted\n");
            }
        } 
		else if(strcmp(menu, "DEL-LANG")==0){
            scanf("%s", &spell);
            find = false;
            for(int j=0;j<spellsize;j++){
                if(strcmp(scott[j], spell)==0){
                    strcpy(scott[j], "-");
                    find = false;
                }
            }
            if(find == false){
                printf("%s language not found\n", spell);
            } 
			else {
                printf("Succesfully deleted\n");
            }
        } 
		else if(strcmp(menu, "DEL-WORD")==0){
            scanf("%s %s", &spell, &word);
            find = false;
            for(int j=0;j<spellsize;j++){
                if(strcmp(scott[j], spell)==0){
                    data *tmp = root[j];
                    root[j] = deldict(root[j], word);
                    if(tmp != root[j])
                        find = false;
                }
            }
            if(find == false){
                printf("Word (%s) not found\n", word);
            } 
			else{ 
				printf("Succesfully deleted\n");
        
            }
        }
    }
}
