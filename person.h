#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <stdexcept>
#include <memory>
#include <map>
#include <algorithm>
#include "license.h"

class License;

class Person{
	std::string name;	//Name der Person.
	unsigned int wealth; //Vermoegen der Person
	std::map<std::string, std::unique_ptr<License>> licenses; //Map von Lizenzen
	public:
	Person(std::string, unsigned int wealth = 0);
	virtual ~Person() = default;
	void work(std::string);
	virtual void work(unsigned int) = 0;
	void increase_wealth(unsigned int);
	std::string get_name() const;
	bool pay_fee(unsigned int);
	void receive_license(std::unique_ptr<License>);
	void transfer_license(std::string, std::shared_ptr<Person>);
	bool eligible(std::string) const;
	virtual std::ostream& print(std::ostream&) const;
};

std::ostream& operator<<(std::ostream&, const Person&);

class Worker : public Person{
	public:
	Worker(std::string, unsigned int=0);
	void work(unsigned int);
	std::ostream& print(std::ostream&) const;
};

class Superworker : public Person{
	unsigned int fee;
	public:
	Superworker(unsigned int, std::string, unsigned int=0);
	void work(unsigned int);
	std::ostream& print(std::ostream&) const;
};

#endif
