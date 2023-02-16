#include "person.h"

Person::Person(std::string name, unsigned int wealth):name{name}, wealth{wealth}{
	if(name.empty()){
		throw std::runtime_error("Person Constructor Error");	
	}
}

void Person::work(std::string guild){
	if(eligible(guild)){
		licenses.at(guild)->use();
		work(licenses.at(guild)->get_salary());
	}
	else{
		throw std::runtime_error("No (valid) license found!");
	}
}

void Person::increase_wealth(unsigned int i){
	wealth += i;
}

std::string Person::get_name() const{
	return name;
}

bool Person::pay_fee(unsigned int i){
	if(wealth < i){
		return false;
	}
	else if(!wealth){
		return false;
	}
	else{
		wealth -= i;
		return true;
	}
}

void Person::receive_license(std::unique_ptr<License> l){
	licenses[l->get_guildname()] = std::move(l);
}

void Person::transfer_license(std::string l, std::shared_ptr<Person> p){
	if(licenses.count(l)){
		p->receive_license(std::move(licenses.at(l)));
		licenses.erase(l);
	}
	else{
		throw std::runtime_error("This Person doesn't own a license with the specified name");
	}
}

bool Person::eligible(std::string l) const{
	return licenses.count(l) && licenses.at(l)->valid();
}

std::ostream& Person::print(std::ostream& o) const{
	bool first{false};
	o << get_name() << ", " << wealth << " Coins, {";
	for(auto it{licenses.begin()}; it != licenses.end(); it++){
		if(first){
			o << ", ";
		}
		first = true;
		o << *(it->second);
	}
	o << "}]";
	return o;
}

std::ostream& operator<<(std::ostream& o, const Person& p){
	return p.print(o);
}

Worker::Worker(std::string name, unsigned int wealth):Person(name, wealth){}

void Worker::work(unsigned int i){
	Person::increase_wealth(i);
}

std::ostream& Worker::print(std::ostream& o) const{
	o << "[Worker ";
	return Person::print(o);
}


Superworker::Superworker(unsigned int fee, std::string name, unsigned int wealth):Person(name, wealth), fee{fee}{}

void Superworker::work(unsigned int i){
	Person::increase_wealth(i+fee);
}

std::ostream& Superworker::print(std::ostream& o) const{
	o << "[Superworker "; 
	return Person::print(o);
}



