#include "guild.h"

Guild::Guild(std::string name, unsigned int fee, unsigned int salary, const std::vector<std::shared_ptr<Person>>& members):name{name}, fee{fee}, salary{salary}{
	
	for(auto p : members){
		this->members[p->get_name()] = p;
	}	
	
	if(name.empty()){
		throw std::runtime_error("Name of guild cannot be empty!");
	}
	if(!(salary > 0 && fee > 0)){
		throw std::runtime_error("Salary and fee must be higher than 0!");
	}
	int count{0};
	for(const auto& p:members){
		for(const auto& q:members){
			if(p == q){
				count++;
			}
		}
		if(count > 1){
			throw std::runtime_error("Duplicate member found in member-list!");
		}
		count = 0;
	}
}

bool Guild::add_member(std::shared_ptr<Person> p){
	return members.insert({p->get_name(), p}).second;
}

bool Guild::remove_member(std::string n){
	return members.erase(n);
}

void Guild::grant_license(std::string n){
	if(!members.count(n)){
		throw std::runtime_error("Person with the specified name ist not a member!");
	}
	if(!members[n]->pay_fee(fee)){
		throw std::runtime_error("Person cannot pay the fee!");
	}
	
	std::unique_ptr<License> l = std::make_unique<License>(name, salary);
	members[n]->receive_license(std::move(l));
}

bool Guild::offer_job(std::shared_ptr<Person> p) const{
	if(members.count(p->get_name())){
		p->work(salary*2);
		return true;
	}
	else if(p->eligible(name)){
		p->work(name);
		return true;
	}
	else{
		return false;
	}
}

std::ostream& Guild::print(std::ostream& o) const{
	bool first{false};
	o << "[" << name << ", License fee: " << fee << ", Job salary: " << salary << ", {";
	for(auto it{members.begin()}; it != members.end(); it++){
		if(first){
			o << ", ";
		}
		first = true;
		o << it->second->get_name();
	}
	o << "}]";
	return o;
}


std::ostream& operator<<(std::ostream& o, const Guild& g){
	return g.print(o);
}
