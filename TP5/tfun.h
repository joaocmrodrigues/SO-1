
typedef struct {
    long *cnt;	/* pointer to shared counter */
    int n;		/* no of times to increment */
    int id;		/* application-specific thread-id */
} targ_t;

void *tfun(void *arg);