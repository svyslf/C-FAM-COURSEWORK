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
int beggar(int Nplayers, int *deck, int talkative);