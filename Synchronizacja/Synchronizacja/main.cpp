#include "_func.h"
#include "mpolaczen.h"
#include "individual.h"
#include "grupa.h"
#include <iostream>
#include <vector>
#include <string>

int main(void)
{
	//doadac interfejs - zapisywanie i korzystanie ze starych danych
	std::string file;
	std::cout << "Podaj adres pliku z danymi: ";
	//std::cin >> file;
	//file = "inputdatapora0R.dat";//do testow
	file = "testowy.dat";
	std::cout << std::endl << "Wczytuje...";
	CconnectionMatrix data(file);
	data.period() = 15;
	data.delay() = 2;
	std::cout << "100%";
	std::cout << std::endl << "Przeliczanie wezlow...";
	data.findKnots();
	std::cout << "100%";
	std::cout << std::endl << "Grupowanie linii...";
	const std::vector<Cgroup> &groups = divideIntoGroups(data);
	std::cout << "100%";
	std::cout << std::endl << "Rozpoczeto synchronizacje...";
	individual ret(sync(data, groups));
	std::cout << "100%";
	save(ret);
	std::cout << std::endl << "Zakonczono, sprawdz plik wynikowy.";
	std::cout << std::endl << "Nacisnij enter, aby zakonczyc...";
	std::cin.sync();
	std::cin.get();
	return 0;
}
