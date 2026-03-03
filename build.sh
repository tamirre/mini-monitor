gcc src/db_test.c -o db_test \
	-I$(pg_config --includedir) \
	-L$(pg_config --libdir) \
	-lpq

# cmake -S . -B build
cmake --build build

