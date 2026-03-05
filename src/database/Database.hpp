#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <pqxx/pqxx>

struct Measurement {
	int deviceID;
	std::string deviceName;
	std::string timeStamp;
	float current;
	float voltage;
};

class Database {
	std::unique_ptr<pqxx::connection> conn;
	public:
		Database();
		~Database();
		void init(const std::string& host, const std::string& dbName, const std::string& user, const std::string& password);
		void insertMeasurement(Measurement measurement);
		void cleanDatabaseByID(const int& deviceID);
		void cleanDatabase();
		std::vector<Measurement> getLastMeasurements(const int& count);
};

#endif // DATABASE_HPP
