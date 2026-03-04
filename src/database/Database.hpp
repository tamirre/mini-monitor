#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <pqxx/pqxx>

typedef struct Measurement {
	int deviceID;
	std::string deviceName;
	std::string timeStamp;
	float current;
	float voltage;
} Measurement;

class Database {
	std::unique_ptr<pqxx::connection> conn;
	public:
		Database();
		~Database();
		void init(std::string host, std::string dbName, std::string user, std::string password);
		void insertMeasurement(Measurement measurement);
		void cleanDatabase(int deviceID);
		std::vector<Measurement> getLastMeasurements(int count);
};

#endif // DATABASE_HPP
