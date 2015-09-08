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
	std::cout << "Podaj nazwe pliku z danymi: ";
	std::cin >> file;
	std::cout << std::endl << "Wczytuje...";
	CconnectionMatrix data(file);
	std::cout << "100%";
	std::cout << std::endl << "Przeliczanie wezlow...";
	data.findKnots();
	std::cout << "100%";
	std::cout << std::endl << "Grupowanie linii...";
	const std::vector<Cgroup> &groups = divideIntoGroups(data);
	std::cout << "100%";
	std::cout << std::endl << "Rozpoczeto synchronizacje...";
	sync(data, groups);
	std::cout << "100%";
	std::cout << std::endl << "Zakonczono, sprawdz plik wynikowy.";
	std::cout << std::endl << "Nacisnij enter, aby zakonczyc...";
	std::cin.sync();
	std::cin.get();
	return 0;
}
