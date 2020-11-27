all: 
	@echo "make win\t-\tfor windows compilation"
	@echo "make linux\t-\tfor linux compilation"
	@echo "\n"
	@echo "make tl\t-\trun compiled linux program"
	@echo "make tw\t-\trun compiled windows program"

win:
	@echo "compilation for windows"
	g++ -std=c++17 -o html_generate.exe html_generate_win.cpp 

linux:
	@echo "compilation for linux"
	g++ -std=c++17 -o html_generate.exe html_generate_linux.cpp 

tl:
	@echo "Testing Linux program"
	./html_generate.exe

tw:
	@echo "Testing Windows program"
	html_generate.exe