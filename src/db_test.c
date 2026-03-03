#include <stdio.h>
#include <libpq-fe.h>

int printRes(PGconn* conn) {
    PGresult* res = PQexec(conn, "SELECT * FROM test;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 1;
    }
    /* First, print out the attribute name. */
    int nFields = PQnfields(res);
    for (int i = 0; i < nFields; i++) {
        printf("%-15s", PQfname(res, i));
	}
    printf("\n");
    printf("---------------------------------\n");

    /* Print lines. */
    for (int i = 0; i < PQntuples(res); i++)
    {
        for (int j = 0; j < nFields; j++)
            printf("%-15s", PQgetvalue(res, i, j));
        printf("\n");
    }
	printf("\n");
	return 0;
}

int main() {
    const char *conninfo = "host=localhost dbname=mini_monitor user=mini_user password=mini_pass";

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return 1;
    }

    printf("Connected successfully!\n");
	PGresult *res = PQexec(conn, "INSERT INTO test (name) VALUES ('from_c_program');");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

    res = PQexec(conn, "SELECT * FROM test;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

	printRes(conn);

	res = PQexec(conn, "DELETE FROM test WHERE name = 'from_c_program';");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

	printRes(conn);

    PQclear(res);
    PQfinish(conn);

    return 0;
}
