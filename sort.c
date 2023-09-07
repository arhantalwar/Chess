// implement quick sort
#include<stdio.h>

int sortList(int* all_possible_moves,int first, int last){
    int i,j,pivot,temp;
    if(first<last){
        pivot = first;
        i = first;
        j = last;

        while(i<j){
            while(all_possible_moves[i]<=all_possible_moves[pivot] && i<last){
                i++;
            }

            while(all_possible_moves[j]>all_possible_moves[pivot] && j>first){
                j--;
            }

            if(i<j){
                temp = all_possible_moves[i];
                all_possible_moves[j] = all_possible_moves[i];
                all_possible_moves[i] = temp;
            }
        }

        temp = all_possible_moves[pivot];
        all_possible_moves[pivot] = all_possible_moves[j];
        all_possible_moves[j] = temp;

        sortList(all_possible_moves,first,j-1);
        sortList(all_possible_moves,j+1,last);
    }
}