#ifndef HASHTABLE_H
#define HASHTABLE_H

//#includes 
#include <string>

//struct for hash table entries
struct Table_Item {
    std::string key;    //holds the Domain Name
    std::string value;  //holds the IP Address

    bool operator==(const Table_Item& a) const{
        return (key == a.key && value == a.value);
    }
};

class HashTable {
    public:
        //public methods
        unsigned int insert(Table_Item item);
        std::string find(std::string item);
        unsigned int getHash(std::string item);
        unsigned int remove(Table_Item item);
        HashTable();
        ~HashTable();
        
    private:
        //private variables
        unsigned int count; // stores the number of entries
        unsigned int size;  // stores the size of the array
        Table_Item * items;


        //private methods
        void grow();
        unsigned int hash(std::string item);     
        unsigned int getNextPrime(unsigned int N);
        bool isPrime(unsigned int n);
};

//Constructor
HashTable::HashTable() {
    count = 0;
    size = 13;
    items = new Table_Item[size];
}

//Destructor
HashTable::~HashTable(){
    delete[] items;
}

//Rolling hash function for a string based on Java's String.hashCode()
unsigned int HashTable::hash(std::string item) {
    const int p = 31, m = 1e9 + 7;  //constant values for rolling hash
    long p_pow = 1;
    int n = item.size();  //size of string
    unsigned int hash_so_far = 0;

    for (int i = 0; i < n; ++i) {
        hash_so_far = (hash_so_far + (item.at(i) - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return hash_so_far;
}

//getter for testing
unsigned int HashTable::getHash(std::string item) {
    return hash(item);
}

unsigned int HashTable::insert(Table_Item item) {
    //if we are over .5 or higher than we need to grow the table before insertion
    float capacity = count/size;

    if(capacity >= .5) {
        grow();
    }

    //get the index
    unsigned int index = hash(item.key)%size;

    //quadratic probing for table insertion if there is a collision
    if(!items[index].key.empty()) {
        
        for (unsigned int j = 1; j < size; j++) {
 
            // Computing the new hash value
            index = (index + j * j) % size;
            if (items[index].key.empty()) {

                // Break the loop after
                // inserting the value
                // in the table
                items[index].key = item.key;
                items[index].value = item.value;
                break;
            }
        }

        return index;
    }
    
    items[index].key = item.key;
    items[index].value = item.value;

    return index;
}

void HashTable::grow() {
    //grab the old table and data about it
    Table_Item * temp = items;
    unsigned int tempSize = size;
    

    //make a new table and replace class data
    unsigned int newSize = getNextPrime(size);
    items = new Table_Item[newSize];
    size = newSize;

    //go through old table and replace it in new table
    for(unsigned int i = 0; i < tempSize; i++) {
        if(!temp[i].key.empty()) {
            insert(temp[i]);
        }
    }

    //delete old table
    delete [] temp;
}

bool HashTable::isPrime(unsigned int n) {
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;
   
    // This is checked so that we can skip 
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return false;
   
    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;
   
    return true;
}

unsigned int HashTable::getNextPrime(unsigned int N) {
    // Base case
    if (N <= 1)
        return 2;
 
    unsigned int prime = N;
    bool found = false;
 
    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found) {
        prime++;
 
        if (isPrime(prime))
            found = true;
    }
 
    return prime;
}


#endif