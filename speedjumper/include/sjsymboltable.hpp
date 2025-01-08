#ifndef SJSYMBOLTABLE_HPP
#define SJSYMBOLTABLE_HPP

#include <unordered_map>
#include <string>


enum class VarType{
	BOOL,
	INT
};



class SymbolTable{
	public:
		bool containsbool(const std::string& varname) const {
			if(symbol_table.find(varname) != symbol_table.end()){
				if(symbol_table.at(varname) == VarType::BOOL){
					return true;
				}
			}
			return false;
		}
		bool containsint(const std::string& varname) const {
			if(symbol_table.find(varname) != symbol_table.end()){
				if(symbol_table.at(varname) == VarType::INT){
					return true;
				}
			}
			return false;
		}			
			
			
			
			
		VarType gettype(const std::string& varname) const {
			return symbol_table.at(varname);
		}


		void update_value(VarType type, const std::string& varname){
			symbol_table[varname] = type;
		}


		std::unordered_map<std::string, VarType> gettable() const {return symbol_table;}


	private:
		std::unordered_map<std::string, VarType> symbol_table;

};





#endif