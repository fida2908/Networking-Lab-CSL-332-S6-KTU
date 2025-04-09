#include <stdio.h>

int main()
{
    int incoming, outgoing, store=0, bucksize, n;
    printf("Enter the number of input, outgoing and bucket size: ");
    scanf("%d %d %d", &n, &outgoing, &bucksize);

    while(n!=0){
        printf("\nEnter the incoming packet size: ");
        scanf("%d", &incoming);

        if(incoming <= (bucksize-store)){
            store+=incoming;
            printf("Bucket size %d out of %d", store, bucksize);
        }
        else{
            int dropped = incoming-(bucksize-store);
            printf("\n%d packets dropped",dropped);

            store = bucksize;
            printf("Bucket size %d out of %d", store, bucksize);
        }
        store=store-outgoing;
        if(store<0){
            store=0;
        }
        printf("\nAfter outgoing, Bucket size %d out of %d", store, bucksize);
        n--;

    }


}