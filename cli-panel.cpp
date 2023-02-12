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
			// TODO: Show what will be installed
			preInstallScreen(1);
			installNode();
			installNginx();
			installPm2();
			installCertbot();
			break;
		case 2:
			// TODO: Show what will be installed
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
	// WIP
	// struct
	// {
	// 	// domain name
	// 	string name;
	// 	// domain path
	// 	string path;
	// 	// added by
	// 	string addedBy;
	// 	// date created
	// 	time_t timeCreated;
	// 	// date updated
	// 	time_t timeUpdated;
	// };

public:
	void addDomain()
	{
		string domain;
		cout << "Enter domain name: ";
		cin >> domain;
		cout << "Adding domain " << domain << endl;
	}
	void viewDomains()
	{
		cout << "Viewing domains" << endl;
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

	// Create sqlite3 connection
	sqlite3 *db;
	int rc;

	rc = sqlite3_open("cli-panel.db", &db);

	if (rc)
	{
		cout << "Unable to connect to DB: " << sqlite3_errmsg(db) << endl;
		exit(0);
	}
	else
	{
		bool execute = true;
		int input;
		Installer installer;
		Domain domain;
		CliPanel cli;
		cout << "Opened database successfully" << endl;
		cli.welcome();

		while (execute)
		{
			cli.selection();
			cin >> input;

			switch (input)
			{
			case 0:
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
	}

	return 0;
}