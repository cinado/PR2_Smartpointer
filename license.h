#ifndef GUILD_H
#define GUILD_H

#include <iostream>
#include <stdexcept>

class License{
	std::string name;	//Name der austellenden Gilde.
	unsigned int salary; //Lohn einer Aufgabe.
	unsigned int counter{0};	//Anzahl der bereits getaetigten Aufgaben.
	public:
	License(std::string, unsigned int);
	std::string get_guildname() const;
	unsigned int get_salary() const;
	bool valid() const;
	bool use();
	std::ostream& print(std::ostream&) const;
};

std::ostream& operator<<(std::ostream&, const License&);

#endif
