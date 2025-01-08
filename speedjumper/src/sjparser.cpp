#include "../include/sjparser.hpp"




std::unique_ptr<EndNode> Parser::build_endnode(){
	return std::unique_ptr<EndNode>();

}
std::unique_ptr<JumpNode> Parser::build_jumpnode(std::unique_ptr<JumpToken> jumptoken) {
    if (symbol_table.containsbool(jumptoken->getCondition())) {
        return std::make_unique<JumpNode>(jumptoken->getJumpTo(), jumptoken->getCondition());
    }

    throw std::runtime_error("Condition not previously defined\n");
}
std::unique_ptr<SimpleAssignNode> Parser::build_simpleassignnode(std::unique_ptr<SimpleAssignToken> simpleassigntoken){
	const std::string& temp_value = simpleassigntoken->getValue();
	if(isBool(temp_value) || symbol_table.containsbool(temp_value)){
		symbol_table.update_value(VarType::BOOL, simpleassigntoken->getVariable());
	}else if(isInteger(temp_value) || symbol_table.containsint(temp_value)){
		symbol_table.update_value(VarType::INT, simpleassigntoken->getVariable());
	}else{
		throw std::runtime_error("Undefined variable passed into simple assignment \n");
	}
	return std::make_unique<SimpleAssignNode>(simpleassigntoken->getVariable(), simpleassigntoken->getValue());


}
/* 
For evaluated assign node, we have to make sure the types are compatible with each other, and also that they are 
compatible with the operation being performed. If that is the case then we can continue updating the symbol_table. 
*/


std::unique_ptr<EvaluatedAssignNode> Parser::build_evaluatedassignnode(std::unique_ptr<EvaluatedAssignToken> evaluatedassigntoken){
	const std::string& templhs = evaluatedassigntoken->getLHS();
	const std::string& temprhs = evaluatedassigntoken->getRHS();
	//Case 1 of Boolean Operation

	if((isBool(templhs) || symbol_table.containsbool(templhs)) && 
	(boolean_operations.find(evaluatedassigntoken->getOperator()) != boolean_operations.end()) &&
	isBool(temprhs) || symbol_table.containsbool(temprhs)){
		symbol_table.update_value(VarType::BOOL, evaluatedassigntoken->getVariable());
	}
	// Case 2 of Integer Operation

	else if((isInteger(templhs) || symbol_table.containsint(templhs)) && 
	(integer_operations.find(evaluatedassigntoken->getOperator()) != integer_operations.end()) &&
	isInteger(temprhs) || symbol_table.containsint(temprhs)){
		symbol_table.update_value(VarType::INT, evaluatedassigntoken->getVariable());
	}

	// Case 3 of Numeric Comparison 

	else if((isInteger(templhs) || symbol_table.containsint(templhs)) && 
	(evaluatedassigntoken->getOperator() == Operation::EQUALS || evaluatedassigntoken->getOperator() == Operation::NEQUALS) &&
	isInteger(temprhs) || symbol_table.containsint(temprhs)){
		symbol_table.update_value(VarType::BOOL, evaluatedassigntoken->getVariable());
	}else{
		throw std::runtime_error("Invalid combination of values and operations\n");
	}

	return std::make_unique<EvaluatedAssignNode>(evaluatedassigntoken->getVariable(), 
	evaluatedassigntoken->getLHS(), evaluatedassigntoken->getOperator(), evaluatedassigntoken->getRHS());
}


std::unique_ptr<DisplayNode> Parser::build_displaynode(std::unique_ptr<DisplayToken> displaytoken){
	const std::string& displayval = displaytoken->getDisplayValue();
	if(isBool(displayval)){
		return std::make_unique<DisplayNode>(DisplayNode::DisplayType::BOOLLITERAL, displayval);
	}else if(symbol_table.containsbool(displayval)){
		return std::make_unique<DisplayNode>(DisplayNode::DisplayType::BOOLVARIABLE, displayval);
	}else if(isInteger(displayval)){
		return std::make_unique<DisplayNode>(DisplayNode::DisplayType::INTLITERAL, displayval);
	}else if(symbol_table.containsint(displayval)){
		return std::make_unique<DisplayNode>(DisplayNode::DisplayType::INTVARIABLE, displayval);
	}
	throw std::runtime_error("Cannot display undefined variable\n");
}