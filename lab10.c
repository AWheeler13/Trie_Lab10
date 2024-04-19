//Adam Wheeler
//CS1 Torosdagli
//Lab 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Trie structure
typedef struct Trie
{	
struct Trie *children[26];
int isWord;
int count;
}Trie;

//initializes a trie struture
Trie *createTrie()
{
  Trie *newTrie = (Trie*)malloc(sizeof(Trie));
  newTrie->isWord = 0;
  newTrie->count = 0;
  for(int i=0;i<26;i++)
    newTrie->children[i]=NULL;
  return newTrie;
}

// Inserts the word to the trie structure
void insert(Trie *pTrie, char *word)
{
  int index;
  Trie *temp = pTrie;
  for(int i=0; word [i] != '\0';i++)
    {
      index = word[i]-'a';
      if(temp->children[index] == NULL)
        temp->children[index] = createTrie();
      temp = temp->children[index];
    }
  temp->isWord = 1;
  temp->count++;
  
}

// computes the number of occurances of the word
int numberOfOccurances(Trie *pTrie, char *word)
{
  Trie *temp = pTrie;
  int i = 0;
  while (word[i] != '\0' && temp->children[word[i] - 'a'] != NULL) {
    temp = temp->children[word[i] - 'a'];
    i++;
  }
  if (word[i] == '\0' && temp->isWord)
    return temp->count;
  else
    return 0;
  
}

// deallocate the trie structure
Trie *deallocateTrie(Trie *pTrie)
{
  if (!pTrie)
    return NULL;
  for (int i = 0; i < 26; i++) {
      if (pTrie->children[i]) {
          deallocateTrie(pTrie->children[i]);
      }
  }
  free(pTrie);
  return NULL;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
  FILE *inFile = fopen(filename, "r");
  if (!inFile) 
  {
    printf("Error opening dictionary file\n");
    return 0;
  }
  int n;
  fscanf(inFile, "%d", &n);
  char temp[100];
  for (int i = 0; i < n; i++) {
      fscanf(inFile, "%s", temp);
      pInWords[i] = (char*)malloc(strlen(temp) + 1);
      strcpy(pInWords[i], temp);
  }
  fclose(inFile);
  return n;
}

int main(void)
{
  char *inWords[256];

  //read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i=0;i<numWords;++i)
  {
    printf("%s\n",inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i=0;i<numWords;i++)
  {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i=0;i<5;i++)
  {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}