
#define Value int
#define Key int

// Create an empty symbol table.
void ST_init(int maxN);
// Put key-value pair into the table: a[key] = val; .
void ST_put(Key key, Value val);
// Value paired with key: a[key] .
Value ST_get(Key key);
// Is there a value paired with key?
bool ST_contains(Key key);
// Remove key (and its value) from table.
void ST_delete(Key key);
// Is the table empty?
bool ST_empty();
// Number of key-value pairs in the table.
int ST_size();
// Clean up the table memory.
void ST_finish();