void riffle(void *L, int len, int size, int N);
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *));
int cmp_int(void* L, void* L_riffled);
int cmp_str(void* L, void* L_riffled);
float average_quality(int N, int shuffles, int trials);