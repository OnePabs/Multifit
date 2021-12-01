//Multifit algorithm implemented in c. Parameters are passed in a file given by the second parameter of argv

#include <stdio.h>
#include <stdlib.h>



typedef struct bin_element bin_element;

struct bin_element {
    int number;
    bin_element* next;
};

struct bin {
    int size;
    bin_element* first_bin_element;
};

//n: number of bins
//cmax: maximum number of elements in a bin
struct bin* createBins(int n, int cmax){
    struct bin* b = (struct bin*)malloc(n*sizeof(struct bin));
    b->size = 0;
    b->first_bin_element = NULL;
    return b;
}


void addElementToBin(struct bin* b, int number){
    if(b->first_bin_element == NULL){
        b->first_bin_element = (struct bin_element*)malloc(sizeof(struct bin_element));
        b->first_bin_element->number = number;
        b->first_bin_element->next = NULL;
    }else{
        struct bin_element* bc;
        for(bc=b->first_bin_element;bc->next!=NULL;bc=bc->next){} //reach the last element of the bin
        bc->next = (struct bin_element*)malloc(sizeof(struct bin_element));
        bc->next->number = number;
        bc->next->next = NULL;
    }
    b->size = b->size + 1;
}

void clearLastElement(struct bin* b){
    if(b->first_bin_element == NULL){
        return;
    }else if(b->first_bin_element->next == NULL){
        //delete first bin element
        free(b->first_bin_element);
        b->first_bin_element = NULL;
        b->size = 0;
    }else{
        //reach the element before last element
        struct bin_element* bc;
        for(
            bc = b->first_bin_element;
            bc->next->next != NULL;
            bc = bc->next
        ){}

        free(bc->next);
        bc->next = NULL;
        b->size = b->size - 1;
    }
}


//b: pointer to an array of bin structures
//n: number of bins in b
void clearBins(struct bin* b, int n){
    //go through every bin
    for(int i=0;i<n;i++){
        //clear the bin's elements
        while((b+i*sizeof(struct bin))->size != 0){
            clearLastElement(b + i*sizeof(struct bin));
        }
    }
}

void deleteBins(struct bin* b){
    free(b);
}

void printBinContents(struct bin* b){
    printf("printing bins\n");
    if(b->first_bin_element == NULL){
        return;
    }else{
        struct bin_element* bc;
        for(bc=b->first_bin_element;bc!=NULL;bc=bc->next){
            printf("%d,",bc->number);
        }
    }
    printf("\n");
}


int main(int argc, char *argv[])
{

    //Parameters (hardcoded for now)
    //S: set of numbers to put in the bins/processors
    //n: number of identical bins/processors
    //K: max number of iterations k
    //Cmin: minimum capacity of a bin 
    //Cmax: maximum capacity of a bin

    int s[] = {1,2,3,4};
    size_t s_size = sizeof(s)/sizeof(s[0]);
    int n=2;
    int k=10;          //heuristic
    int cmin = 4;       //highest number in the set
    int cmax = 1+2+3+4; //sum of all the numbers (final allocation on one bin cannot be bigger than this)

    //sort s in ascending order
    //s is already sorted

    //create and initialize bins
    struct bin* bins = createBins(n,cmax);
    addElementToBin(bins,1);
    printBinContents(bins);
    printBinContents(bins+sizeof(struct bin));
    clearBins(bins,2);
    printBinContents(bins);
    printBinContents(bins+sizeof(struct bin));
    


    /*
    for(int i=0;i<n;i++){
        initBin(bins[i],cmax);
    }
    */

    /*
    //set up temp algorithm variables
    int numIterationsCompleted=0;
    int currentMaxCapacity;
    int isComputationFinished=0;
    
    while(isComputationFinished == 0){
        currentMaxCapacity = (cmin+cmax)/2;

        //place element of S into bins
        int areAllBinsFull=1;
        for(int i=0;i<s_size;i++){
            
            //place ith element of S into the first bin it fits in
            for(int j=0;j<n;j++){
                if( (bins[j].size + s[i]) < currentMaxCapacity){
                    //bin has enough size to take element
                    *(bins[j].elembuff + bins[j].size*sizeof(int));
                    //addNumToBin(bins[j], s[i]);
                    areAllBinsFull = 0;
                    break;
                }
            }
            
            //all bins are full
            if(areAllBinsFull == 1){
                break;
            }
        }

        //update number of iterations
        numIterationsCompleted++;

        //check for stopping condistion
        if(cmin == cmax || numIterationsCompleted==k){
            isComputationFinished=1;
        }else if(areAllBinsFull == 1){
            cmin = currentMaxCapacity;
        }else{
            cmax = currentMaxCapacity;
        }
    }


    printf("Final bin configuration: \n");
    for(int i=0;i<n;i++){
        printf("Bin ");
        fprintf("%d",i);
        printf(": ");
        fprintf("%d,",*(bins[0].elembuff));
        fprintf("%d,",*(bins[1].elembuff));
        printf("\n");
        //printBinContents(bins[i]);
    }


    //free heap memory
    for(int i=0;i<n;i++){
        deleteBin(bins[i],cmax);
    }
    */
}