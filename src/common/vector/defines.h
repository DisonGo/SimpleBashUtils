#ifndef BASE_LENGTH
#define BASE_LENGTH 1 << 8
#endif  // BASE_LENGTH
#ifndef MAX_LENGTH
#define MAX_LENGTH 10 << 12
#endif  // MAX_LENGTH
#define Vector(type) vector_##type
#define new_vector(type, size) init_##type(size)
#define new_vector_data(type, data, size) init_data_##type(data, size)
