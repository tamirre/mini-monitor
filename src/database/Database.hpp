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
		void init(std::string host, std::string dbName, std::string user, std::string password);
		void insertMeasurement(Measurement measurement);
		void cleanDatabaseByID(int deviceID);
		void cleanDatabase();
		std::vector<Measurement> getLastMeasurements(int count);
};

#endif // DATABASE_HPP
