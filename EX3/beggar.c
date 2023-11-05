#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#define MAX_SIZE 52
#define Queue_empty INT_MIN

/** @brief 
 * The node to be used in the queue implementation.
 * @param value::integer The value of the node
 * @param next::node The next node  
*/
typedef struct node
{
    int value;
    struct node *next;
} node;

/** @brief 
 * The queue data structure to be constructed using nodes. 
 * @param head::node head node of the queue
 * @param tail::node tail node of the queue
 * @param size::int size of the queue 
*/
typedef struct
{
    node *head;
    node *tail;
    int size;
} queue;

/** @brief 
 * Initialises the queue. 
 * @param *q::queue The queue to initialise
*/
void init_queue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}

/** @brief 
 * Checks if the queue is empty. 
 * @param *q::queue The queue to be checked for emptiness
*/
int is_empty(queue *q)
{
    int is_empty = (q->head == NULL) ? 1 : 0;
    return is_empty;
}

/** @brief 
 * Checks if the queue is full.
 * @param *q::queue The queue to be checked for fullness
*/
int is_full(queue *q)
{
    int is_full = (q->size == MAX_SIZE);
    return is_full;
}

/** @brief 
 * Adds a new node to the queue.
 * @param *q::queue The queue to be added to
 * @param value:int The integer value to add
*/
int enqueue(queue *q, int value)
{
    /* create new node*/
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL)
        return 0;
    newnode->value = value;
    newnode->next = NULL;

    /*connect the tail to new node*/
    if (q->tail != NULL)
    {
        q->tail->next = newnode;
    }
    q->tail = newnode;

    /*Re set head*/
    if (q->head == NULL)
    {
        q->head = newnode;
    }
    q->size++;
    return 1;
}

/** @brief 
 * Removes and returns the removed node.
 * @param *q::queue The queue from which you want to remove a node
*/
int dequeue(queue *q)
{
    if (q->head == NULL)
        return Queue_empty;

    node *tmp = q->head;
    int result = tmp->value;
    q->head = q->head->next;
    if (q->head == NULL)
    {
        q->tail = NULL;
    }
    free(tmp);
    q->size--;
    return result;
}

/** @brief 
 * Return the head without removing it.
 * @param *q::queue The queue to be peeked
*/
int peek_head(queue *q)
{

    if (q->head != NULL)
    {
        return q->head->value;
    }
    return Queue_empty;
}

/** @brief 
 * Return the tail without removing it.
 * @param *q::queue The queue to be peeked
*/
int peek_tail(queue *q)
{
    if (q->tail != NULL)
    {
        return q->tail->value;
    }
    return Queue_empty;
}

/** @brief 
 * Print the entire queue.
 * @param *q::queue The queue to be printed
*/
void print_queue(queue *q)
{
    if (q->head == NULL)
    {
        printf("%s", "This hand is empty!");
    }
    node *tmp = q->head;
    while (tmp != NULL)
    {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

/** @brief 
 * Empty or "destroy" the queue.
 * @param *q::queue The queue to be emptied
*/
void empty_queue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}
/** @brief 
 * The take_turn function handles how every player plays the game.
 * It keeps track of the cards in the queue and the hand of the player that was passed in. 
 * 
 * @param *q::queue The queue to be emptied
 * @param *pile::queue The queue to be emptied
 * 
 * @returns The pile + penalty cards returned as the "reward" or NULL if no penalty was incurred
 * 
*/
queue *take_turn(queue *player, queue *pile)
{
    int top_card_in_pile = peek_tail(pile);
    int top_card_in_hand = peek_head(player);

    int penalty = 0;
    int i;

    if (top_card_in_hand > 10)
    {
        enqueue(pile, dequeue(player));
        return NULL;
    }
    if (top_card_in_pile > 10)
    {
        penalty += top_card_in_pile - 10;

        for (i = 0; i < penalty; i++)
        {
            enqueue(pile, dequeue(player));

            if (is_empty(player) == 1 || top_card_in_hand > 10)
            {
                /* if they put down a penalty card or run out of cards, continue game */
                break;
                return NULL;
            }
        }
    }
    else
    {
        enqueue(pile, dequeue(player));
        return NULL;
    }

    return pile;
}

/** @brief 
 * The finished function checks if the game has finished. 
 * A game finishes if someone has a full hand || if there are enough empty hands. 
 * 
 * @param *players[]::queue The queue of players in the game.
 * @param Nplayers::int The number of players in the game.
 * 
 * @returns Integer value indicating true or false
 * 
*/
int finished(queue *players[], int Nplayers)
{
    int i;
    int empty = 0;
    int over = 0;

    for (i = 0; i < Nplayers; i++)
    {

        if (is_full(players[i]) || is_empty(players[i]))
        {
            over = 1;
        }
        else
        {
            over = 0;
            break;
        }
    }
    return over;
}

/** @brief 
 * The beggar function handles the game loop. 
 * It also deals the cards to the players and distributes rewards to the right player. 
 * 
 * @param *q::queue The queue to be emptied
 * @param *pile::queue The queue to be emptied
 * 
 * @returns The pile + penalty cards returned as the "reward" or NULL if no penalty was incurred.
 * 
*/
int beggar(int Nplayers, int *deck, int talkative)
{
    int i, j;
    queue pile;
    queue *players[Nplayers];
    queue *reward;

    for (i = 0; i < Nplayers; i++)
    /* initialise the player queues that represent each player and their hand */
    {
        players[i] = (queue *)malloc(sizeof(queue));
        init_queue(players[i]);
    }

    for (i = 0; i < MAX_SIZE; i++)
    /* Deal the deck to the players */
    {
        enqueue(players[i % Nplayers], deck[i]);
    }

    init_queue(&pile);
    int current_player = 0;
    int turn=0;
    int previous_player;
    while (finished(players, Nplayers) != 1)
    {

        if (is_empty(players[current_player]) == 1)
        {
            /* ignore players with empty hand by skipping their index */
            current_player = (current_player + 1) % (Nplayers);
            continue;
        }
        reward = take_turn(players[current_player], &pile);
        if (reward != NULL)
        {
            while (is_empty(reward) != 1)
            {
                enqueue(players[previous_player], dequeue(reward));
            }
        }
        if (talkative)
        {
            printf("\n");
            printf("Turn %d: ", turn);
            printf("PILE: ");

            if (is_empty(&pile) == 1)
            {
                printf("Pile is empty! ");
            }
            else
            {
                print_queue(&pile);
            }
            printf("\n");
            for (j = 0; j < Nplayers; j++)
            {
                printf("player %d's hand => ", j);
                print_queue(players[j]);
            }
        }
        turn++;
        previous_player = current_player;
        current_player = (current_player + 1) % (Nplayers);
    };
    
    for (i = 0; i < Nplayers; i++)
    /* Free the player malloced queues after game ends */
    {
        free(players[i]);
        empty_queue(players[i]);
    }
   
    return turn;
}
