#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>

using namespace std;
namespace fs = std::filesystem; // c++17 feature

string getFILE_str(string FILE_DIR){
	ifstream read;
	string content = "", buffer;
	read.open(FILE_DIR);
	if(read.fail()){
		cerr<<"ERROR READING THE STRING IN FILE : "<<FILE_DIR<<endl;
		exit(1);
	}
	else
		cout<<"open successfull"<<endl;

	while(!read.eof()){
		getline(read,buffer);
		content = content + buffer + '\n';
	}
	read.close();
	return content + "\n";
}

void writeStrToFileOverwrite(string FILE_DIR, string input){
	ofstream write;
	write.open(FILE_DIR);
	if(write.fail()){
		cerr<<"ERROR WRITING TO FILE : "<<FILE_DIR<<endl;
		exit(1);
	}
	else{
		cout<<"GENERATED THE FILE"<<endl;
	}
	write<<input;
	write.close();
}

void writeStrToFileAppend(string FILE_DIR, string input){
	ofstream write;
	write.open(FILE_DIR, std::ios_base::app);
	if(write.fail()){
		cerr<<"ERROR WRITING TO FILE : "<<FILE_DIR<<endl;
		exit(1);
	}
	else{
		cout<<"GENERATED THE FILE"<<endl;
	}
	write<<input;
	write.close();
}

// erase a substring in the string ( reference | modifies the base element)
string eraseSubStr(string mainStr, const string strErase){
	size_t pos =  mainStr.find(strErase);
	if(pos != string::npos)
		mainStr.erase(pos,strErase.length());

	return mainStr;
}

string getFileExtension(string File){
	int start,
	    last = File.size()-1;
	for(int bi = last; ; --bi){
		if(File[bi] == '.'){
			start = bi;
			break;
		}
	}
	return File.substr(start,last);
}

class files{
public:
	string filePath;
	string fileName;
	string fileSize;
	string fileExt;
	string json;

	files(string fPath, string fName, string fSize, string fExt){
		filePath = fPath;
		fileName = fName;
		fileSize = fSize;
		fileExt  = fExt;
	}

	void display(){
		cout<<"PATH : "<<filePath<<endl;
		cout<<"NAME : "<<fileName<<endl;
		cout<<"SIZE : "<<fileSize<<endl;
		cout<<"TYPE : "<<fileExt<<endl;
	}

	string JSON_STRING(){
		string jsbuffer = 
			"{\n\t\"path\": \""+filePath+"\",\n"+
			"\t\"name\": \""+fileName+"\",\n"+
			"\t\"size\": \""+fileSize+"\",\n"+
			"\t\"type\": \""+fileExt+"\"\n}";

		return jsbuffer;
	}
};


string extimg(map <string,string> &formats, string format){
	return formats[format];
}

int main(){
	//file formats
	map<string,string> myformats;
	myformats[".c"] = "c.png";
	myformats[".cpp"] = "cpp.png";
	myformats[".doc"] = "doc.png";
	myformats[".docx"] = "docx.png";
	myformats[".exe"] = "exe.png";
	myformats[".msi"] = "exe.png";
	myformats[".flv"] = "flv.png";
	myformats[".h"] = "h.png";
	myformats[".html"] = "html.png";
	myformats[".jpg"] = "jpg.png";
	myformats[".jpeg"] = "jpg.png";
	myformats[".mp3"] = "mp3.png";
	myformats[".mp4"] = "mp4.png";
	myformats[".pdf"] = "pdf.png";
	myformats[".png"] = "png.png";
	myformats[".ppt"] = "ppt.png";
	myformats[".pptx"] = "ppt.png";
	myformats[".py"] = "py.png";
	myformats[".txt"] = "txt.png";
	
	string currentDir    = fs::current_path().string();
	string guestDir		 = currentDir + "\\storage\\shared\\";
	string htmlTemplates = currentDir + "\\templates\\";
	string htmlHead      = htmlTemplates + "head.txt",
		   htmlTail		 = htmlTemplates + "tail.txt",
		   htmlGuestFILE = currentDir + "\\views\\guestview.ejs"; 

	vector<files> guestFiles;

	for(const auto& paths: fs::directory_iterator(guestDir)){
		auto buffer = paths;
		guestFiles.push_back(
			files(
				eraseSubStr(buffer.path().string(), currentDir + "\\public"),
				eraseSubStr(buffer.path().string(), guestDir),
				to_string((fs::file_size(buffer)/1024.00)/1024),
				getFileExtension(buffer.path().string())
			)
		);
	}

	string newHtml = getFILE_str(htmlHead), tempsource = "\\images\\format\\";
	for(int i = 0; i < guestFiles.size(); ++i){
		newHtml = newHtml + "\n" +
			"\t\t\t\t<div class=\"download-container\">\n" +
				"\t\t\t\t\t<input type=\"image\" src=\""+ tempsource + extimg(myformats,guestFiles[i].fileExt)+"\" class=\"file-button-link\" onclick=\"window.open('/shared/"+guestFiles[i].fileName+"','__blank');\">\n"+
				"\t\t\t\t\t<span class=\"file-button-name\">"+guestFiles[i].fileName+"</span>\n"+
				"\t\t\t\t\t<p class=\"file-button-size\">"+guestFiles[i].fileSize+" MB</p>\n" +
			"\t\t\t\t</div>";
	}
	newHtml = newHtml + "\n" + getFILE_str(htmlTail);
	writeStrToFileOverwrite(htmlGuestFILE, newHtml);

	cin.get();
	return 0;
}
