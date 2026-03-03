#include <iostream>
#include <pqxx/pqxx>

int main() {
    try {
        pqxx::connection conn(
            "host=localhost dbname=mini_monitor user=mini_user password=mini_pass"
        );

        if (!conn.is_open()) {
            std::cerr << "Failed to open database\n";
            return 1;
        }
        std::cout << "Connected successfully!\n";

        // === Transaction 1: Insert measurement ===
        {
            pqxx::work txn(conn);
            txn.exec(
                "INSERT INTO measurements (device_id, voltage, current) "
                "VALUES ($1, $2, $3)",
                pqxx::params{1, 230.0, 5.0}
            );
            txn.commit();
        }

        std::cout << "Inserted measurement.\n\n";

        // === Transaction 2: Read measurements ===
        {
            pqxx::nontransaction read_txn(conn);
            pqxx::result r = read_txn.exec(
                "SELECT m.device_id, d.name, m.recorded_at, m.voltage, m.current "
                "FROM measurements m "
                "JOIN devices d ON m.device_id = d.id "
                "ORDER BY m.recorded_at DESC LIMIT 10"
            );

            for (const auto& row : r) {
                int device_id = row["device_id"].as<int>();
                std::string name = row["name"].as<std::string>(); 
                std::string ts = row["recorded_at"].c_str();     
                double voltage = row["voltage"].as<double>();
                double current = row["current"].as<double>();

                std::cout
                    << device_id << " | "
                    << name << " | "
                    << ts << " | "
                    << voltage << " | "
                    << current << "\n";
            }
        }

        // === Transaction 3: Delete measurement ===
        {
            pqxx::work txn(conn); // NEW transaction
            txn.exec(
                "DELETE FROM measurements WHERE device_id = $1",
                pqxx::params{1}
            );
            txn.commit();
        }

        std::cout << "Deleted measurement.\n";

    } catch (const std::exception& e) {
        std::cerr << "Database error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
