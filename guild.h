#ifndef LICENSE_H
#define LICENSE_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include "person.h"
#include "license.h"

class Person;
class License;

class Guild{
	std::string name;	//Name der Gilde.
	unsigned int fee; //Lizenzgebühr
	unsigned int salary;	//Gehalt pro Aufgabe
	std::map<std::string, std::shared_ptr<Person>> members; //Map von Gildenmitgliedern
	public:
	Guild(std::string, unsigned int, unsigned int, const std::vector<std::shared_ptr<Person>>& members = {});
	bool add_member(std::shared_ptr<Person>);
	bool remove_member(std::string);
	void grant_license(std::string);
	bool offer_job(std::shared_ptr<Person>) const;
	std::ostream& print(std::ostream&) const;
};

std::ostream& operator<<(std::ostream&, const Guild&);

#endif
