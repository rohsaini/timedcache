# TimedCache

Timed Cache implementation supports
   - Storing of Key Value pairs in time ordered fashion
   - Purging of outdated keys based on "Time To Live" configured

Scaling Results:
Insertion (180k keys/sec) : Time taken is 290-350 ms
Traversal (180k keys) : 30ms-40ms
Random Key Lookup : 2 us

