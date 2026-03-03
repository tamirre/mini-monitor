# gcc src/db_test.c -o db_test \
# 	-I$(pg_config --includedir) \
# 	-L$(pg_config --libdir) \
# 	-lpq

g++ -std=c++20 -Wall -Wextra -Wpedantic src/db_test.cpp -o db_test $(pkg-config --cflags --libs libpqxx)
# cmake -S . -B build
cmake --build build

