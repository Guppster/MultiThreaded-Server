/*
 * This is the main queue structure
 */
typedef struct queue
{
        int capacity;
        int size;
        int front;
        int rear;
        int *elements;
}queue;

/*
 * This method creates a queue with maxElement number of elements and returns it
 */
queue* createQueue(int maxElements)
{
        /*Create a Queue*/
        queue *Q;
        Q = (queue *)malloc(sizeof(queue));

        /* Initialize it's properties */
        Q->elements = (int *)malloc(sizeof(int)*maxElements);
        Q->size = 0;
        Q->capacity = maxElements;
        Q->front = 0;
        Q->rear = -1;

        /*Return the pointer*/
        return Q;
}

/*
 * This method returns 1 if empty, and 0 if not empty
 */
int empty(queue *Q)
{
        if(Q->size == 0)
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

/*This method pops and element off the queue*/
void pop(queue *Q)
{
        if(Q->size != 0)
        {
                Q->size--;
                Q->front++;
                
                if(Q->front == Q->capacity)
                {
                        Q->front = 0;
                }
        }
}

/*Returns the top most element of the queue*/
int peek(queue *Q)
{
        /* Return the element which is at the front*/
        return Q->elements[Q->front];
}

/*Pushes a new element onto the queue*/
void push(queue *Q, int element)
{
        if(Q->size != Q->capacity)
        {
                Q->size++;
                Q->rear = Q->rear + 1;

                if(Q->rear == Q->capacity)
                {
                        Q->rear = 0;
                }

                Q->elements[Q->rear] = element;
        }
}
