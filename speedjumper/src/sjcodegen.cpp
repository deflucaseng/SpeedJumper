#include "include/sjcodegen.hpp"


CodeGenerator::CodeGenerator(const std::vector<std::unique_ptr<Node>>& nodes, const std::string& filename, const std::string& writepath, const std::unordered_map<std::string, VarType> symboltable):cgsymboltable(symboltable){
	try{
		auto out = fmt::output_file("writepath/" + filename);

		//Necessary pre generated steps

		out.print(R"(
section .data
	true_msg db 'true', 0xA
	true_len equ $ - true_msg
	false_msg db 'false', 0xA
	false_len equ $ - false_msg
	newline db 10

section .text
	global _start

_start:)");

	for (const std::unique_ptr<Node>& givennode: nodes){
		nodeconverter(givennode, out);
	}
		//Necessary post generated steps


out.print(R"(
print_true:
	mov ecx, true_msg
	mov edx, true_len
	jmp do_print
print_false:
	mov ecx, false_msg
	mov edx, false_len
do_printL
	mov eax, 4
	mov ebx, 1
	int 0x80
	jmp print_newline
start_num_print:
	mov ecx, buffer
	add ecx, 11
	mov byte [ecx], 0
	dec ecx
	mov ebx, 10
convert_loop:
	xor edx, edx
	div ebx
	add dl, \'0\'
	mov [ecx], dl
	dec ecx
	test eax, eax
	jnz convert_loop
	mov eax, [num_to_print]
	test eax, eax
	jns print_number
	mov byte [ecx], \'-\'
	dec ecx
print_number:
	mov edx, buffer
	add edx, 11
	sub edx, ecx
	inc ecx
	mov eax, 4
	mov ebx, 1
	int 0x80
	jmp print_newline
print_newline:
	mov eax, 4
	mov ebx, 1
	mov ecx, newline
	mov edx, 1
	int 0x80
	jmp [lastknownpos]

section .bss
	num_to_print resd 1
	lastknownpos resd 1
	buffer resb 12
)");

	symboltableconverter(cgsymboltable, out);






	} catch (const std::system_error& e){
		fmt::print(stderr, "Failed to write: {}\n", e.what());
	}



}

void CodeGenerator::symboltableconverter(const std::unordered_map<std::string, VarType> symboltable, auto& out){
	for(const std::pair<std::string, VarType> pair : symboltable){
		out.print("\t{} resd 1\n", pair.first);
	}
}

void CodeGenerator::nodeconverter(const std::unique_ptr<Node>& node, auto& out){
	auto variant = convertToVariant(std::move(node));
	out.print(std::visit(NodeVisitor{*this}, variant));
}


std::string CodeGenerator::displaygen(const std::unique_ptr<DisplayNode>& node){
	std::string displayval = node->getdisplayval();
	switch(node->getdisplaytype()){
		case DisplayNode::DisplayType::BOOLVARIABLE: [[fallthrough]];
		case DisplayNode::DisplayType::INTVARIABLE:
			displayval = "[" + displayval + "]";
	}


	switch(node->getdisplaytype()){ 
		case DisplayNode::DisplayType::INTLITERAL:[[fallthrough]];
		case DisplayNode::DisplayType::INTVARIABLE:
			return fmt::format(R"(
mov eax, {displayval}
mov dword [num_to_print], eax
jmp start_num_print			
)", fmt::arg("displayval", displayval));

		case DisplayNode::DisplayType::BOOLLITERAL:[[fallthrough]];
		case DisplayNode::DisplayType::BOOLVARIABLE:
			return fmt::format(R"(
mov eax, {displayval}
cmp eax, 1
jne print_false
jmp print_true
)", fmt::arg("displayval", displayval));
	}
}
std::string CodeGenerator::endgen(const std::unique_ptr<EndNode>& node){
	return R"(
mov eax, 0x1
mov ebx, 0
int 0x80
)";
}
std::string CodeGenerator::evalassigngen(const std::unique_ptr<EvaluatedAssignNode>& node){
	std::string lhs = node->getlhs();
	std::string rhs = node->getrhs();
	if(cgsymboltable.find(lhs) != cgsymboltable.end()){
		lhs = "["+lhs+"]";
	}else if(lhs == "true" || lhs == "True"){
		lhs = "1";
	}else if(lhs == "false" || lhs == "False"){
		lhs = "0";
	}
	if(cgsymboltable.find(rhs) != cgsymboltable.end()){
		rhs = "["+rhs+"]";
	}else if(rhs == "true" || rhs == "True"){
		rhs = "1";
	}else if(rhs == "false" || rhs == "False"){
		rhs = "0";
	}

	return fmt::format(eval_assign[node->getop()], fmt::arg("lhs", lhs), fmt::arg("rhs", rhs), fmt::arg("var", node->getvar()));

}
std::string CodeGenerator::jumpgen(const std::unique_ptr<JumpNode>& node){
	return fmt::format(R"(
mov eax, [{condition}]
cmp eax, 1
jne command {jumploc}
)", fmt::arg("condition", node->getCondition()), fmt::arg("jumploc", std::to_string(node->getjump_to())));
}


std::string CodeGenerator::simpleassigngen(const std::unique_ptr<SimpleAssignNode>& node){
	std::string value= node->getvalue();
	if(cgsymboltable.find(value) != cgsymboltable.end()){
		value = "["+value+"]";
	}else if(value == "true" || value == "True"){
		value = "1";
	}else if(value == "false" || value == "False"){
		value = "0";
	}
	return fmt::format(R"(
mov eax, {value}
mov dword [{var}], eax
)", fmt::arg("value", value), fmt::arg("var", node->getvar()));

}



