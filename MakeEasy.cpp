#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

class MakeEasyParser {
	public:
		bool ProcessFile();
		
		~MakeEasyParser() {}
		explicit MakeEasyParser(std::string _FilePath) : FilePath{_FilePath} {}
	private:
		std::ifstream File;
		std::string FilePath;
};

bool MakeEasyParser::ProcessFile() {
	if(FilePath.empty()) return false;
	
	File.open(FilePath.c_str());
	if(!((bool) File)) {
		std::cerr << "Error al cargar el archivo" << std::endl;
		return false;
	}
	std::string Comand;
	while(!(File.eof())) {
		getline(File,Comand);
		system(Comand.c_str());
	}
	
	return true;
}



int main (int argc,char *argv[]) {
	
	if(argc < 2) {
		std::cerr << "Error Se necesita un archivo que procesar" << std::endl;
		return -1;
	}
	
	MakeEasyParser Parser(argv[1]);
	
	if(!(Parser.ProcessFile())) {
		return -2;
	}
	return 0;
}