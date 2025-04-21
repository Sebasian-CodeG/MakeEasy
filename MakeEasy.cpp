#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>

class MakeEasyParser {
	public:
		bool ProcessFile(std::string _FilePath);
		
		void ActivateFlagPrintComandEjecution(){
			if(!(FlagPrintComandEjecution)) FlagPrintComandEjecution = {true};
			return;
		}
		
		void ActivateFlagSaveComand(){
			if(!(FlagSaveComandLine)) FlagSaveComandLine= {true};
			return;
		}
		
		~MakeEasyParser() {}
		MakeEasyParser() {}
	private:
		std::string FilePath;
		std::ifstream File;
		
		bool FlagPrintComandEjecution = {false};
		bool FlagSaveComandLine = {false};
		
		void Save(std::string Comand);
};

bool MakeEasyParser::ProcessFile(std::string _FilePath) {
	if(_FilePath.empty()) return false;
	FilePath = _FilePath;
	
	File.open(FilePath.c_str());
	if(!((bool) File)) {
		std::cerr << "Error al cargar el archivo" << std::endl;
		return false;
	}
	
	std::string Comand;
	while(!(File.eof())) {
		getline(File,Comand);
		
		if(FlagPrintComandEjecution) std::cout << "[Comand]: " << Comand << std::endl;
		if(FlagSaveComandLine) Save(Comand);
		
		system(Comand.c_str());
	}
	
	return true;
}

//-Private Functions Class

void MakeEasyParser::Save(std::string Comand){
	std::fstream File;
	static bool FlagSave = {false};
	if(!(FlagSave)) {
		File.open("ComandRegister.txt",std::ios::out);
		FlagSave = {true};
	} else {
		File.open("ComandRegister.txt",std::ios::app);
	}
	
	File << "[Comand]: " << Comand << std::endl;
	File.close();
	return;
}

int main (int argc,char *argv[]) {
	
	if(argc < 2) {
		std::cerr << "Error Se necesita un archivo que procesar" << std::endl;
		return -1;
	}
	
	MakeEasyParser Parser;
	
	for(int Iter = 1; Iter < argc; ++Iter){ //Buscar Comandos de configuracion
		std::string AuxString = argv[Iter];
		if(AuxString == "-p") Parser.ActivateFlagPrintComandEjecution();
		if(AuxString == "-s") Parser.ActivateFlagSaveComand();
	}
	
	for(int Iter = 1; Iter < argc; ++Iter){ //Buscar filtar los archivos de comando
		if(argv[Iter][0] !=  '-')
			if(!(Parser.ProcessFile(argv[Iter]))) return -2;
	}
	
	return 0;
}
