#include "license.h"

License::License(std::string name, unsigned int salary):name{name},salary{salary}{
	if(get_guildname().empty()){
		throw std::runtime_error("Computer sagt nein!");
	}
	if(get_salary() <= 0){
		throw std::runtime_error("Computer sagt nein!");
	}
}

std::string License::get_guildname() const{
	return name;
}

unsigned int License::get_salary() const{
	return salary;
}

bool License::valid() const{
	if(counter <= 3){
		return true;
	}
	return false;
}

bool License::use(){
	if(valid()){
		counter++;
		return true;
	}
	return false;
}

std::ostream& License::print(std::ostream& o) const{
	o << "[License for " << get_guildname() << ", Salary: " << get_salary() << ", Used: " << counter << "]";
	return o;
}


std::ostream& operator<<(std::ostream& o, const License& l){
	return l.print(o);
}

