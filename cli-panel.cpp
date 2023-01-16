#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Installer
{
	// Installs Node.js
	void installNode()
	{
		system("sudo apt-get update");
		system("sudo apt-get install nodejs");
		system("sudo apt-get install npm");
	};

	// Installs PHP
	void installPhp()
	{
		system("sudo apt-get update");
		system("sudo apt-get install php");
	};

	// Installs Nginx
	void installNginx()
	{
		system("sudo apt-get update");
		system("sudo apt-get install nginx");
	};

	// Installs MySQL
	void installMysql()
	{
		system("sudo apt-get update");
		system("sudo apt-get install mysql-server");
	};

	// Installs PM2
	void installPm2()
	{
		system("sudo npm install -g pm2");
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
	};

public:
	void install()
	{
		int selection;
		cout << endl
			 << "Select your stack" << endl;
		cout << "1. node + nginx + pm2 + certbot" << endl;
		cout << "2. php + mysql + nginx + certbot" << endl;

		cout << endl
			 << "> ";
		cin >> selection;

		switch (selection)
		{
		case 1:
			cout << "Installing node + nginx + pm2 + certbot" << endl;
			installNode();
			installNginx();
			installPm2();
			installCertbot();
			break;
		case 2:
			cout << "Installing php + mysql + nginx + certbot" << endl;
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
	bool execute = true;
	int input;
	Installer installer;
	Domain domain;
	CliPanel cli;

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

	return 0;
}