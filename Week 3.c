/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CANDIDATES 9

int preferences[MAX_CANDIDATES][MAX_CANDIDATES];  
bool locked[MAX_CANDIDATES][MAX_CANDIDATES];       
char *candidates[MAX_CANDIDATES];                   
int pair_count = 0;                             
int candidate_count = 0;                  

typedef struct {
    int winner;
    int loser;
} pair;

pair pairs[MAX_CANDIDATES * (MAX_CANDIDATES - 1) / 2];  

bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main() {
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            locked[i][j] = false; }}

    printf("Enter number of candidates: ");
    scanf("%d", &candidate_count);

    for (int i = 0; i < candidate_count; i++) {
        candidates[i] = malloc(100 * sizeof(char));  
        printf("Enter name of candidate %d: ", i + 1);
        scanf("%s", candidates[i]);}

    int voter_count;
    printf("Enter number of voters: ");
    scanf("%d", &voter_count);

    int ranks[candidate_count];

    for (int i = 0; i < voter_count; i++) {
        printf("Enter rankings for voter %d (space-separated numbers for preferences):\n", i + 1);
        for (int j = 0; j < candidate_count; j++) {
            scanf("%d", &ranks[j]);}
        record_preferences(ranks);}

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;}

bool vote(int rank, char *name, int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i], name) == 0) {
            ranks[rank] = i;  
            return true;}}
    return false; }

void record_preferences(int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]] += 1;
            preferences[ranks[j]][ranks[i]] -= 1;}}}

void add_pairs(void) {
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            int margin = preferences[i][j] - preferences[j][i];
            if (margin > 0) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;}
             else if (margin < 0) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;}}}}

void sort_pairs(void) {
    for (int i = 0; i < pair_count - 1; i++) {
        for (int j = i + 1; j < pair_count; j++) {
            int margin_i = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            int margin_j = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (margin_i < margin_j) {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;}}}}

bool creates_cycle(int start, int end) {
    if (start == end) return true;  
    for (int i = 0; i < candidate_count; i++) {
        if (locked[start][i] && creates_cycle(i, end)) {
            return true;  }}
    return false;  }

void lock_pairs(void) {
    for (int i = 0; i < pair_count; i++) {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
  
        locked[winner][loser] = true;
        if (creates_cycle(winner, loser)) {
            locked[winner][loser] = false;  }}}

void print_winner(void) {
    for (int i = 0; i < candidate_count; i++) {
        bool is_source = true;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) {
                is_source = false;
                break;}}
        if (is_source) {
            printf("The winner is: %s\n", candidates[i]);
            return;}}}
