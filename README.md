## C++ Hash Table Implementation

Hash table implementation in C++. Works on a simple "library system", where it can store, retrieve and delete books from the system with good time complexity and good space complexity if the number of books is of a reasonable size. <br /><br />
This hash table uses linear probing as its collision resolution, and in the best case, provides O(1) get and put functions. With Book objects, the hash function provides fairly unique hash codes, so O(1) is realistic. It could be easily changed to accomodate for primitives though, and generic types too but would lose certainty in the hash values' uniqueness, making O(1) less likely.
