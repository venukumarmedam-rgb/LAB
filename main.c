#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
#define lcodelen 2048
#define scodelen 10
int urlCount=0;
struct URL {
    int shortCode;
    char longURL[lcodelen];
    int accessCount;
    int isActive;
    struct URL *next;
}*first=NULL;

int  css(struct URL *p){
    if(p==NULL){
        return 0;
    }else{
        while(p->next!=NULL){
            p=p->next;
        }return p->shortCode+1;
    }
}

int insertlast(struct URL **p,char *longCode){
    if (urlCount >= MAX) return -1;
    struct URL *t,*new=(*p);
    if(first == NULL){
        first=(struct URL*)malloc(sizeof(struct URL));
        first->shortCode=1;
        strcpy(first->longURL,longCode);
        first->accessCount=0;
        first->isActive=1;
        first->next=NULL;
        return first->shortCode;
    }else{
        t=(struct URL*)malloc(sizeof(struct URL));
        t->shortCode=(css((first)));
        strcpy(t->longURL,longCode);
        t->accessCount=0;
        t->isActive=1;
        t->next=NULL;
        while(new->next!=NULL){
            new=new->next;
        }new->next=t;
        new=t;
    }urlCount++;
    return new->shortCode;
}

int check(struct URL *p,int s){int n=1;
    while(p!=NULL){
        if(p->shortCode==s){
            return n;
        }n++;p=p->next;
    }return n;
}

char deleteURL(struct URL **p,int n){
    struct URL *head,*prev=NULL;
    head=(*p);
    int x=-1;
    if(head!=NULL && n==1){
        (*p)=(*p)->next;
        x=head->shortCode;
        free(head);
    }else{
        for(int i=0;i<n-1&&head;i++){
            prev=head;
            head=head->next;
        }if(head){
            prev->next=head->next;
            x=head->shortCode;
            free(head);
        }else{
            printf("invalid pointer\n");
            return x;
        }
    }return x;
}

const char* retrieveURL(struct URL *p,int s) {
    while(p!=NULL){
        if(s==p->shortCode&&p->isActive==1){
            p->accessCount++;
            return p->longURL;
        }
        p=p->next;
    }
    return NULL;
}

void mostAccessedURL(struct URL *p) {
    int max = -1;int i=0;struct URL *x=p;
    int index = -1;
    while (p->next!=NULL) {
        if(p->isActive&&(p->accessCount>max)){
            max=p->accessCount;
            index=i;x=p;
        }i++;
        p=p->next;
    }
    if (index != -1) {
        printf("Most accessed URL: %s (Accessed %d times)\n",x->longURL, max);
    } else {
        printf("No active URLs.\n");
    }
}

void menu(void) {
    printf("\n--- URL Shortening Service ---\n");
    printf("1. Store URL\n");
    printf("2. Retrieve URL\n");
    printf("3. Delete URL\n");
    printf("4. Most Accessed URL\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

int main(void) {
    int choice;int id,shortcode;
    char input[lcodelen];
    while (1) {
        menu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                printf("Enter long URL: ");
                gets(input);
                input[strcspn(input, "\n")] = 0;
                id = insertlast(&first,input);
                if (id != -1)
                    printf("Short code: %d\n", id);
                else
                    printf("head full.\n");
                break;
            case 2:
                printf("Enter short code: ");
                scanf("%d",&shortcode);
                const char *url = retrieveURL(first,shortcode);
                if (url)
                    printf("Original URL: %s\n", url);
                else
                    printf("URL not found or deleted.\n");
                break;
            case 3:
                printf("Enter short code to delete: ");
                scanf("%d",&shortcode);
                if (deleteURL(&first,shortcode))
                    printf("Deleted successfully.\n");
                else
                    printf("URL not found.\n");
                break;
            case 4:
                mostAccessedURL(first);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid option.\n");
        }
    }
    return 0;
}
