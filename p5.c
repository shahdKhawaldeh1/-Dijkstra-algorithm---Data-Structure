#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 9999
#define minus1 -1

void MainMenu(){
    printf("\t\t\t******************************\n");
    printf("\t\t\tPlease choose from the menu bellow \n");
    printf("\t\t\t 1)) Read Data From File!\n");
    printf("\t\t\t 2)) Find  the shortest path\n");
    printf("\t\t\t 3)) Print to a File\n");
    printf("\t\t\t 4)) Exit!!\n");
    printf("\t\t\t******************************\n");
    printf("\n\t\t\tPlease enter an CHOICE: ");

}
// The GRAPHh is represented  by using the standard way : Array of linked list
typedef struct ADJNode* NODE;
typedef struct G* GRAPHh;

GRAPHh ReadGraph();
void DijkstraPoints(GRAPHh);
int VISITED(int visited[], int size);
void printToFile();
char routes[1000];



struct ADJNode
{ // CREATE THE ADJ.LINKED LIST vertex
    //// the string where we want to append
    int D; char city[30]; int DIS; //DESTINATION
    struct ADJNode* NEXT;
}; struct LIST //CREATE THE ADJ.LINKED LIST
{struct ADJNode *head;
};  struct G  {
    int V; struct LIST* ARR;
};

struct ADJNode* NEW
        (int dest, char *city, int distance)
{    ////IN THIS FUNCTION WE ADD A NEW  ADJ.L vertex
    struct ADJNode* newNode =
            (struct ADJNode*) malloc(sizeof(struct ADJNode));
    newNode->D = dest; strcpy(newNode->city, city); newNode->DIS = distance;
    newNode->NEXT = NULL;   return newNode;
}
struct G* CREATE(int num)  {  //TO CREATE THE GRAPH WE NEED TO PASS THE SIZE OF THE ADJ.L
    struct G* graph =
            (struct G*) malloc(sizeof(struct G));
    graph->V = num;
    graph->ARR =
            (struct LIST*) malloc(num * sizeof(struct LIST));
    for ( int k = 0; k < num; ++k){
        //MAKE ALL THE LIST EQUAL NULL UNTIL  ENTERED EDGES IN THE L.L
        //THA ADDITION  USING THE FUNCTION ADD_edge
        graph->ARR[k].head = NULL;
    } return graph;
}

// Adds an edge to an undirected GRAPHh
void AddingInGRAPH(struct G* graph, int src, int dest, char *city, int distance)
{  //To add the EDGE,the SOURCE when adding the DESTINATION adds it to the same DESTINATION as it the SOURCE
    struct ADJNode* newNode = NEW(dest, city, distance); newNode->NEXT = graph->ARR[src].head;
    graph->ARR[src].head = newNode;

//TO ADD THE EDGES IN THE GRAPH  WE ADD IT ( D TO SOURCE)
    newNode = NEW(src, city, distance); newNode->NEXT = graph->ARR[dest].head;
    graph->ARR[dest].head = newNode;
}
void printGraph(struct G* graph)
{ //function th print the graph
    for ( int i = 0;   i < graph->V; ++i)
    {  struct ADJNode* p = graph->ARR[i].head;
        printf("\nThe vertex of the  Adjacency list  %d\n head ", i);
        printf("\n************************************************\n");
        while (p){
            printf("\t\n%d\t\n%s\t\n%d", p->D, p->city, p->DIS);p = p->NEXT;
        }
    }
}
int CHOICE;
int main()
{
    GRAPHh Locations = NULL;do
    {MainMenu();
        scanf("%d", &CHOICE);
        switch(CHOICE)  {
            case 1:
                Locations = ReadGraph();  printGraph(Locations);break;
            case 2:
                DijkstraPoints(Locations); break;
            case 3:
                printToFile(); break;
            case 4: printf("exit!!\n");  break;
        }



    }while(CHOICE != 4);



    return 0;
}

void printToFile() {
    FILE *out = fopen("routes.txt", "w");  fprintf(out, "%s", routes);
    fclose(out);
}

void DijkstraPoints(GRAPHh g) { char CHOOSE; CHOOSE = '1';
    do{ //as required ,, loop to let the user choose pairs as he like
        int SOURCE; int  DE;  int maxN = g->V; //maxN refers to the number of nodes in the graph
        //let the user enter enter the source
        printf("\t\t Please enter the source:\n"); scanf("%d",&SOURCE);
        if(SOURCE > maxN  ||    SOURCE < 1
        ||  g->ARR[SOURCE].head == NULL)
        { //check if the source is greater than the max or the source is negative the source is null
            printf("This local is not defined !! \n"); return;
        }

        int s = maxN + 1;
        //let the user enter  the destination  and check negative  if its' null
        printf(" \tplease enter the Destination:\n"); scanf("%d", &DE);
        if(DE > maxN || g->ARR[DE].head == NULL || DE < 1){
            printf("\t\tnot found \n");return;
        }

        if(SOURCE == DE){ //if the  user enter source and dis. as the same value
            //from source to source and des. = 0
            printf("zero\n"); return;
        }
        //create array for the visited nodes
        //if the visited num 0 means not visited , if one will be visited
        int visited[s]; int dist[s]; int PREVIOUS[s];
        // Also Creat array  for the previous point before the current node

        for(int k = 0; k <s; k++)  {
            visited[k] = 0;
            if(g->ARR[k].head == NULL){  visited[k] = 1;
            }
            dist[k] = SIZE; PREVIOUS[k] = minus1; //Before searching we didn't now the dia. and the previous
        }
          //the  array of the current distance represents the dis. between the source to source
        int currentPoint = SOURCE; dist[currentPoint] = 0;
        visited[currentPoint] = 1; //the visited nodes will returned to 1
         PREVIOUS[currentPoint] = minus1; //the prev will not change
        int MINdist; int NodeWithMinDistance = SOURCE;


      //initialize head to move thw adj.list to the current point
      // ( in the beginning it's the source and initialize temp for it
        while(!VISITED(visited, s))  {
            NODE Head = g->ARR[currentPoint].head;  NODE p = Head; MINdist = SIZE;
            while(p) {
                if(  dist[p->D] > (dist[currentPoint] + p->DIS)   )
                    dist[p->D] = dist[currentPoint] + p->DIS;
                //if the adj. point for the current is smaller than
                //the sum of ( the current distance and the source with the destination

                if( (visited[p->D] == 0)
                && (MINdist> dist[p->D] ) ) {
                    //check if the min and if the node is visited or not
                    NodeWithMinDistance = p->D; MINdist = dist[p->D];
                } p = p->NEXT;
                //IF THE DIS.  SMALLER THAN THE  DISTANCE FOR THE ADJ.L AND NOT VISITED
                //IT WILL STORE THE DIST IN IT
            }
            if(MINdist == SIZE) currentPoint = PREVIOUS[currentPoint];
             //if the min does not change ( the case was the current point)  return to the prev point (will be visited)
            else {
                PREVIOUS[NodeWithMinDistance] = currentPoint; currentPoint = NodeWithMinDistance;
            }
            if(currentPoint == minus1) {
                printf("\t\tNo solution\n"); break;
            }
            visited[currentPoint] = 1;
        }
        int I = 1; int loc1 = DE; int road[maxN];
        for(int i = 0 ; i < maxN ; i ++)
        {
            road[i] = minus1; visited[i] = 0; PREVIOUS[i] = minus1;
        }
        visited[DE] = 1;  road[0] = DE;
        while(loc1 != SOURCE)   { MINdist = dist[loc1];
            NODE head = g->ARR[loc1].head;
            while(head)
            {if(dist[head->D] < MINdist && visited[head->D] == 0){
                    MINdist = head->DIS; NodeWithMinDistance = head->D;
                } head = head -> NEXT;
            }
            if(MINdist == SIZE )
                loc1 = PREVIOUS[loc1];
            else  {
                PREVIOUS[NodeWithMinDistance] = loc1; loc1 = NodeWithMinDistance; visited[loc1] = 1; road[I] = loc1;
                I++;
            } printf("\t%d\n\n", loc1);
        }
        char LINE[2000] = ""; sprintf(LINE, "\t**Road  started from\t%d\tto\t%d \n", SOURCE, DE);
        for(int i = I - 1; i > 0; i --){
            char DATA[100] = "";  sprintf(DATA, "\t\n%d\t\n%d ", road[i], road[i - 1]);
            NODE Head =  g->  ARR[road[i]].head;
            while(Head)  {
                if(Head->D == road[i - 1])  {strcat(DATA, Head->city);
                    // strncat() is a predefined function used for string handling.
                    strcat(DATA, "\n\0"); strcat(LINE, DATA);
                    break;
                }Head = Head->NEXT;
            }
        }
        strcat(LINE, "\n"); strcat(routes, LINE); printf("%s", routes);
        printf("\t\n**TO RETURN TO THE MEUNE ENTER ANY NUMBER PLEASE **\n"); fflush(stdin);
        scanf("%I", &CHOOSE);
    }while(CHOOSE == '1');
}  int VISITED(int *visited, int size)
{  for(int J = 0 ; J < size; J ++) {
        if(visited[J] == 0){
            return 0;
        }
    }  return 1;
}


GRAPHh ReadGraph()
{

    int max = 0;
    char filename[30];
    printf("please enter the file name :\n");
    fflush(stdin);
    //fflush() is typically used for output stream only.
    // Its purpose is to clear (or flush) the output buffer and move the buffered data to console
    gets(filename);
    FILE * INPUT;
    INPUT = fopen(filename, "r");
    int  n1;  int n2;
        char line[300];
        //find the maximum  number to find the size of graph
        while(fgets(line, 300, INPUT))
        {  //converts the string argument str to an integer (type int).
            n1 = atoi(strtok(line, " "));
            n2 = atoi(strtok(NULL, " "));
            if(n1 > max){
                max = n1;
            }
            if(n2 > max){

                max = n2;

            }
        } rewind(INPUT);
        // the rewind function sets the file position to the beginning of the file for the stream pointed to by stream.
        // It also clears the error and end-of-file indicators for stream.
        GRAPHh LOCATIONS = CREATE(max); //create for the graph using the maximum
        int v1 , v2;
        //the size of the graph from zero to the maximum number

        //to read the file cut the string using the space then count the space until the last space
        //then get the number to store the string  with the spaces in the city name

        while(fgets(line, 256, INPUT))
        {//converts the string argument str to an integer (type int).
            v1 = atoi(strtok(line, " "));
            v2 = atoi(strtok(NULL, " ")); char *rem = strtok(NULL, "\n");
            char REM[30];

            strcpy(REM, "");strcpy(REM, rem); rem = NULL;
            int LASTS = 0; int NUM_SPACES = 0;
            for(int i = 0; i  < strlen(REM); i ++  ) //The strlen() function calculates the length of a given string.

            {
                if(REM[i]== ' '){ LASTS = i;  NUM_SPACES ++;
                }   if(REM[i] == '\0'){
                    break;

                }
            }  char CityName[30];
            // strncat() is a predefined function used for string handling.
            strncat(CityName, REM, LASTS);

            if(NUM_SPACES > 1)   {
                strtok(REM, " ");   NUM_SPACES--;
                while(NUM_SPACES != 0)   {
                    strtok(NULL, " ");   NUM_SPACES--;
                    // the  -- operator as a postfix like: var++,
                    // the original value of var is returned first; then var is decreases by 1.
                }
            }else
            {strtok(REM, " ");  NUM_SPACES--;
            }
            int dist = atoi(strtok(NULL, "\0")); AddingInGRAPH(LOCATIONS, v1, v2, CityName, dist);
            strcpy(CityName, "");
        } return LOCATIONS;
    }

