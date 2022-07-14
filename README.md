# HashTable-in-C++
Technical Details
* Uses A Rolling Hash algorithm to hash strings similar to what is used in Java Strings .hash() function
* Quadratic Probing is used to avoid Collisions
* Table size is only prime numbers. When table needs to grow it goes to the next prime number
* Table size is capped at the limit of an Unsigned Int
