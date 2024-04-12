#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};


struct Node {
    struct RecordType data;
    struct Node* next;
};

struct HashType {
    struct Node** table; 
    int capacity;        
};
int dataSz = 0;

// Compute the hash function
int hash(int key, int tableSize) {
    return key % tableSize;
}
void initHashTable(struct HashType* hashTable, int capacity) {
    hashTable->capacity = capacity;
    hashTable->table = (struct Node**)malloc(capacity * sizeof(struct Node*));

    for (int i = 0; i < capacity; i++) {
        hashTable->table[i] = NULL;
    }
}
void insert(struct HashType* hashTable, struct RecordType newItem) {
    int index = hash(newItem.id, hashTable->capacity);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newItem;
    newNode->next = hashTable->table[index]; // Insert at the beginning for simplicity
    hashTable->table[index] = newNode;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;
	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
			ppData[i] = pRecord;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		if(pHashArray->table[i] != NULL) {
			printf("%d %c %d %d \n", i, pHashArray->table[i]->data.name, pHashArray->table[i]->data.order, pHashArray->table[i]->data.id);
		}
		pHashArray->table[i] = pHashArray->table[i]->next;
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType hash;
	initHashTable(&hash, recordSz);
	for(int i = 0; i < recordSz; i++) {
		insert(&hash, pRecords[i]);
	}
	displayRecordsInHash(&hash, hash.capacity);

}