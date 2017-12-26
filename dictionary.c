/**
 * Implements a dictionary's functionality.
 */

#include "dictionary.h"

// визначаємо структуру вузла (node)
typedef struct node
{
    char word [LENGTH + 1];
    struct node *next;
} node;

node *hashtable[HASHTABLE_SIZE]; //створюємо масив вказівників на вузол (pointer-to-nodes) розміром HASHTABLE_SIZE

/*
HASH FUNCTION
https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
*/

int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}
//лічильник слів
unsigned int count_word = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int len = strlen(word); // довжина слова

    char word_copy[len + 1]; //масив чарів, у який будемо копіювати слово для перевірки.

    for (int i = 0; i < len; i++)
    {
       word_copy[i] = tolower(word[i]);
    }
    word_copy[len] = '\0';

    int hash = hash_it(word_copy); //визначаємо хеш слова

    node* cursor = hashtable[hash]; //створюємо вказівник на перший вузол кошика (позиція хеш у хештаблиці)

    while (cursor != NULL)
    {
        if (strcmp (cursor->word, word_copy) == 0) //якщо слово в першому вузлі словника таке ж як копія слова
        {
            return true;
        }
        else    //інакше вказівник переходиться на наступний вузол.
        {
            cursor = cursor->next;
        }
    }
    return false;
}
/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    //заповнюємо табличку нулями
    for (int i = 0; i < HASHTABLE_SIZE; i++ )
    {
        hashtable[i] = NULL;
    }
    //open dictionary
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open dictionary!\n");
        return false;
    }

    while (true)
    {
        //виділяємо память під новий node
        node *new_node = malloc(sizeof(node));
        // перевірка на виділення памяті
        if (new_node == NULL)
        {
            unload();
            printf("Could not malloc a new memory!\n");
            return false;
        }
        //прочитати слово з словника і записати його в new_node->word
        fscanf(fp, "%s", new_node->word);
        new_node->next = NULL;

        // якщо кінець файлу, то звільняємо память, яку виділили під новий node
        if (feof(fp))
        {
            free(new_node);
            break;
        }

        count_word ++;

        //створюємо вказівник вузла-голови, який вказує на позицію з номером hash в хештаблиці.
        int hash = hash_it (new_node->word);
        node* head = hashtable[hash];

        //якщо голова пуста - голові присвоюємо новий нод
        if (head == NULL)
        {
            hashtable[hash] = new_node;
        }
        //якщо голова вже є - то додаємо новий нод на початок.
        else
        {
            new_node->next = hashtable[hash];
            hashtable[hash] = new_node;
        }
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (&load != false) //якщо загрузка без помилки то вертаємо кількість слів
    {
        return count_word;
    }
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++) //звільнення памяті,
    {
        node* cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
