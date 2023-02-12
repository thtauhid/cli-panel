#include <iostream>
#include <string>
#include <ctime>
#include <sqlite3.h>

using namespace std;

class Installer
{
	// Installs Node.js
	void installNode()
	{
		system("sudo apt-get update");
		system("sudo apt-get install nodejs");
		system("sudo apt-get install npm");

		// TODO: Create entry in db for node & npm version
	};

	// Installs PHP
	void installPhp()
	{
		system("sudo apt-get update");
		system("sudo apt-get install php");
		system("sudo apt-get install php-fpm");
		system("sudo apt-get install php-mysql");
		system("sudo apt-get install php-curl");
		system("sudo apt-get install php-gd");
		system("sudo apt-get install php-mbstring");
		system("sudo apt-get install php-xml");
		system("sudo apt-get install php-xmlrpc");
		system("sudo apt-get install php-soap");
		system("sudo apt-get install php-intl");
		system("sudo apt-get install php-zip");

		// TODO: Create entry in db for php version
		// TODO: Create entry in db for all php extensions
	};

	// Installs Nginx
	void installNginx()
	{
		system("sudo apt-get update");
		system("sudo apt-get install nginx");

		// TODO: Create entry in db for nginx version
	};

	// Installs MySQL
	void installMysql()
	{
		system("sudo apt-get update");
		system("sudo apt-get install mysql-server");

		// TODO: Create entry in db for mysql version
	};

	// Installs PM2
	void installPm2()
	{
		system("sudo npm install -g pm2");

		// TODO: Create entry in db for pm2 version
	};

	// Installs Let's Encrypt Certbot
	void installCertbot()
	{
		system("sudo apt-get update");
		system("sudo apt-get install software-properties-common");
		system("sudo add-apt-repository universe");
		system("sudo add-apt-repository ppa:certbot/certbot");
		system("sudo apt-get update");
		system("sudo apt-get install certbot python-certbot-nginx");

		// TODO: Create entry in db for certbot version
	};

	void preInstallScreen(int stack)
	{
		switch (stack)
		{
		case 1: // node + nginx + pm2 + certbot
			cout << "The following software will be installed:" << endl
				 << "+---------------------+" << endl
				 << "| Software            |" << endl
				 << "+---------------------+" << endl
				 << "| Node.js             |" << endl
				 << "| NPM                 |" << endl
				 << "| Nginx               |" << endl
				 << "| PM2                 |" << endl
				 << "| Certbot             |" << endl
				 << "+---------------------+" << endl;

			break;
		case 2: // php + mysql + nginx + certbot
			cout << "The following software will be installed:" << endl
				 << "+---------------------+" << endl
				 << "| Software            |" << endl
				 << "+---------------------+" << endl
				 << "| PHP                 |" << endl
				 << "| PHP-FPM             |" << endl
				 << "| PHP-MySQL           |" << endl
				 << "| PHP-Curl            |" << endl
				 << "| PHP-GD              |" << endl
				 << "| PHP-MBString        |" << endl
				 << "| PHP-XML             |" << endl
				 << "| PHP-XMLRPC          |" << endl
				 << "| PHP-SOAP            |" << endl
				 << "| PHP-Intl            |" << endl
				 << "| PHP-Zip             |" << endl
				 << "| MySQL               |" << endl
				 << "| Nginx               |" << endl
				 << "| Certbot             |" << endl
				 << "+---------------------+" << endl;
			break;
		default:
			break;
		}
	}

public:
	Installer()
	{
		// db connection
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;

		// Create Connection
		rc = sqlite3_open("cli-panel.db", &db);
		if (rc)
		{
			fprintf(stderr, "Can't open database: %s", sqlite3_errmsg(db));
			exit(0);
		}

		// Create softwares table
		const char *sql = "CREATE TABLE IF NOT EXISTS softwares(id INTEGER PRIMARY KEY AUTOINCREMENT, software TEXT NOT NULL, version TEXT NOT NULL, created_at TEXT NOT NULL);";

		// Execute SQL statement
		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s", zErrMsg);
			sqlite3_free(zErrMsg);
			exit(0);
		}

		// Close Connection
		sqlite3_close(db);
	}

	void getCurrentSoftwares()
	{
		// db connection
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;

		// Create Connection
		rc = sqlite3_open("cli-panel.db", &db);
		if (rc)
		{
			fprintf(stderr, "Can't open database: %s", sqlite3_errmsg(db));
			exit(0);
		}

		// read softwares from db
		const char *sql = "SELECT * FROM softwares";
		sqlite3_stmt *stmt;

		// Prepare SQL statement
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "Failed to fetch data: %s", sqlite3_errmsg(db));
			sqlite3_close(db);
			exit(0);
		}

		// Loop through the results and print them
		// better looking output
		cout << "+-------------------+-------------------+" << endl;
		cout << "| Software          | Version           |" << endl;
		cout << "+-------------------+-------------------+" << endl;
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			cout << "| " << sqlite3_column_text(stmt, 1) << " | " << sqlite3_column_text(stmt, 2) << endl;
		}
		cout << "+-------------------+-------------------+" << endl;

		// Finalize statement
		sqlite3_finalize(stmt);

		// Close connection
		sqlite3_close(db);
	}

	void install()
	{
		int selection;

		cout << endl
			 << "Select your stack" << endl;
		cout << "1. Node.js + Nginx + PM2 + Certbot" << endl;
		cout << "2. PHP + MySQL + Nginx + Certbot" << endl;

		cout << endl
			 << "> ";
		cin >> selection;

		switch (selection)
		{
		case 1:
			preInstallScreen(1);
			installNode();
			installNginx();
			installPm2();
			installCertbot();
			break;
		case 2:
			preInstallScreen(2);
			installPhp();
			installMysql();
			installNginx();
			installCertbot();
			break;
		default:
			cout << "Invalid selection" << endl;
			break;
		}
	}
};

class Domain
{

public:
	Domain()
	{
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;

		// Create Connection
		rc = sqlite3_open("cli-panel.db", &db);
		if (rc)
		{
			fprintf(stderr, "Can't open database: %s", sqlite3_errmsg(db));
			exit(0);
		}

		// Create domains table
		const char *sql = "CREATE TABLE IF NOT EXISTS domains(id INTEGER PRIMARY KEY AUTOINCREMENT, domain TEXT NOT NULL, created_at DATETIME DEFAULT CURRENT_TIMESTAMP, updated_at DATETIME DEFAULT CURRENT_TIMESTAMP);";

		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s", zErrMsg);
			sqlite3_free(zErrMsg);
			exit(0);
		}

		sqlite3_close(db);
	}
	void addDomain()
	{
		string domain;
		cout << "Enter domain name: ";
		cin >> domain;
		cout << "Adding domain " << domain << endl;

		// TODO: Add domain to db

		// connect to db
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;

		// Create Connection
		rc = sqlite3_open("cli-panel.db", &db);
		if (rc)
		{
			fprintf(stderr, "Can't open database: %s", sqlite3_errmsg(db));
			exit(0);
		}

		// Add domain to db
		const char *sql = "INSERT INTO domains(domain) VALUES(?)";
		sqlite3_stmt *stmt;
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s", zErrMsg);
			sqlite3_free(zErrMsg);
			exit(0);
		}

		sqlite3_bind_text(stmt, 1, domain.c_str(), -1, SQLITE_TRANSIENT);

		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE)
		{
			fprintf(stderr, "SQL error: %s", zErrMsg);
			sqlite3_free(zErrMsg);
			exit(0);
		}

		sqlite3_finalize(stmt);

		sqlite3_close(db);
	}
	void viewDomains()
	{
		// init db
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;

		// Create Connection
		rc = sqlite3_open("cli-panel.db", &db);
		if (rc)
		{
			fprintf(stderr, "Can't open database: %s", sqlite3_errmsg(db));
			exit(0);
		}

		// get domains
		const char *sql = "SELECT * FROM domains";
		sqlite3_stmt *stmt;
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s", zErrMsg);
			sqlite3_free(zErrMsg);
			exit(0);
		}

		cout << "Viewing domains" << endl;

		cout << "+---------------------+" << endl
			 << "| ID | Domain         |" << endl
			 << "+---------------------+" << endl;
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			cout << "| " << sqlite3_column_int(stmt, 0) << " | " << sqlite3_column_text(stmt, 1) << endl;
		}

		cout << "+---------------------+" << endl;

		sqlite3_finalize(stmt);

		sqlite3_close(db);
	}
};

class CliPanel
{

public:
	void welcome()
	{
		cout << "Welcome to cli-panel" << endl;
	}

	void selection()
	{
		cout << "0. Install Stack" << endl;
		cout << "1. Add New Domain" << endl;
		cout << "2. View Current Domains" << endl;
		cout << "3. Install Software on domain" << endl;
		cout << "4. Quit";

		cout << endl
			 << "> ";
	}
};

int main()
{

	// sqlite3 *db;

	// Create sqlite3 connection
	// int rc = sqlite3_open("cli-panel.db", &db);

	bool execute = true;
	int input;
	Installer installer = Installer();
	Domain domain = Domain();
	CliPanel cli = CliPanel();
	cli.welcome();

	while (execute)
	{
		cli.selection();
		cin >> input;

		switch (input)
		{
		case 0:
			installer.getCurrentSoftwares();
			installer.install();
			break;
		case 1:
			domain.addDomain();
			break;
		case 2:
			domain.viewDomains();
			break;
		case 3:
			// installSoftware();
			break;
		case 4:
			execute = false;
			break;
		default:
			cout << "Invalid selection" << endl;
			break;
		}
	}

	return 0;
}