#include "Database.hpp"

#include <iostream>

Database::Database()
{

}

Database::~Database()
{

}
void Database::init(std::string host, std::string dbName, std::string user, std::string password)
{
	try {
		std::string conn_str = "host=" + host +
			" dbname=" + dbName +
			" user=" + user +
			" password=" + password;

		conn = std::make_unique<pqxx::connection>(conn_str);
		std::cout << "Connection successfull!" << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Database error: " << e.what() << "\n";
	}
}

void Database::insertMeasurement(Measurement measurement)
{
	try {
		pqxx::work txn(*conn);
		txn.exec("INSERT INTO measurements (device_id, voltage, current) "
				"VALUES ($1, $2, $3)",
				pqxx::params{measurement.deviceID, measurement.voltage, measurement.current});
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Database error: " << e.what() << "\n";
	}
}

void Database::cleanDatabaseByID(int deviceID)
{
	try {
		pqxx::work txn(*conn); 
		txn.exec(
				"DELETE FROM measurements WHERE device_id = $1",
				pqxx::params{deviceID}
				);
		txn.commit();
		std::cout << "Database cleaned for device_id = " << deviceID << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Database error: " << e.what() << "\n";
	}
}

std::vector<Measurement> Database::getLastMeasurements(int count)
{
	std::vector<Measurement> measurements;
	try {
		pqxx::nontransaction read_txn(*conn);
		std::string read_str = 
			"SELECT m.device_id, d.name, m.recorded_at, m.voltage, m.current "
			"FROM measurements m "
			"JOIN devices d ON m.device_id = d.id "
			"ORDER BY m.recorded_at DESC LIMIT " + std::to_string(count);
		pqxx::result r = read_txn.exec(read_str);

		for (const auto& row : r) {
			Measurement m = {
				.deviceID = row["device_id"].as<int>(),
				.deviceName = row["name"].as<std::string>(), 
				.timeStamp = row["recorded_at"].as<std::string>(),     
				.current = row["current"].as<float>(),
				.voltage = row["voltage"].as<float>(),
			};
			measurements.push_back(m);
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Database error: " << e.what() << "\n";
	}
	return measurements;
}

