#!/bin/bash

DB_NAME="mini_monitor"
USER="mini_user"
export PGPASSWORD="mini_pass"

psql -U "$USER" -h localhost -d postgres -tc "SELECT 1 FROM pg_database WHERE datname = '$DB_NAME'" | grep -q 1 || \
psql -U "$USER" -h localhost -d postgres -c "CREATE DATABASE $DB_NAME"
psql -U "$USER" -h localhost -d $DB_NAME -f db/init.sql

# g++-15 -std=c++20 -Wall -Wextra -Wpedantic src/db_test.cpp -o db_test $(pkg-config --cflags --libs libpqxx libpq)

cmake -DCMAKE_CXX_COMPILER=/usr/bin/g++-15 -S . -B build
cmake --build build

