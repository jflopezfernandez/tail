
#include "tail.h"

static size_t lines = 10;

struct queue_node_t {
    const char* line;
    struct queue_node_t* next;
};

static struct queue_node_t* allocate_queue_node(void) {
    struct queue_node_t* queue_node = malloc(sizeof (struct queue_node_t));

    if (queue_node == NULL) {
        fprintf(stderr, "[Error] %s\n", "Memory allocation failure in allocate_queue_node()");
        exit(EXIT_FAILURE);
    }

    return queue_node;
}

static struct queue_node_t* new_queue_node(const char* line) {
    struct queue_node_t* queue_node = allocate_queue_node();

    queue_node->line = strdup(line);

    if (queue_node->line == NULL) {
        fprintf(stderr, "[Error] %s\n", "Memory allocation failure in new_queue_node()");
        exit(EXIT_FAILURE);
    }

    queue_node->next = NULL;

    return queue_node;
}

void free_queue_node(struct queue_node_t* queue_node) {
    free((void *) queue_node->line);
    free((void *) queue_node);
}

static struct queue_node_t* queue_head = NULL;

static struct queue_node_t* queue_tail = NULL;

static size_t queue_length = 0;

void enqueue(struct queue_node_t* queue_node) {
    if (++queue_length <= lines) {
        if (queue_head == NULL) {
            queue_head = queue_node;
            queue_tail = queue_head;

            return;
        }
    } else {
        struct queue_node_t* previous_head_node = queue_head;
        queue_head = queue_head->next;
        free_queue_node(previous_head_node);
    }

    queue_tail->next = queue_node;
    queue_tail       = queue_node;
}

void add_line(const char* line) {
    struct queue_node_t* queue_node = new_queue_node(line);
    enqueue(queue_node);
}

void print_lines_in_queue(void) {
    struct queue_node_t* queue_iterator = queue_head;

    while (queue_iterator) {
        printf("%s", queue_iterator->line);
        queue_iterator = queue_iterator->next;
    }
}

int main(int argc, char **argv)
{
    for (int i = 2; i < argc; ++i) {
        printf("%s\n", argv[i]);
    }

    char input_buffer[512] = { 0 };

    FILE* input_file = fopen(argv[1], "r");

    while (fgets(input_buffer, 512, input_file) != NULL) {
        add_line(input_buffer);
    }

    fclose(input_file);

    print_lines_in_queue();

    return EXIT_SUCCESS;
}
