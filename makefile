SRC = ./src
BUILD = $(SRC)/build

tgnews: $(BUILD)/main.o $(BUILD)/parser.o $(BUILD)/fileManager.o $(BUILD)/news.o $(BUILD)/newsManager.o $(BUILD)/language.o
	g++ -g -o ./tgnews $(BUILD)/main.o $(BUILD)/parser.o $(BUILD)/fileManager.o $(BUILD)/news.o $(BUILD)/newsManager.o $(BUILD)/language.o

$(BUILD)/main.o: $(SRC)/main.cpp
	g++ -g -c $(SRC)/main.cpp -o $(BUILD)/main.o

$(BUILD)/parser.o: $(SRC)/parser.cpp
	g++ -g -c $(SRC)/parser.cpp -o $(BUILD)/parser.o

$(BUILD)/fileManager.o: $(SRC)/fileManager.cpp
	g++ -g -c $(SRC)/fileManager.cpp -o $(BUILD)/fileManager.o

$(BUILD)/news.o: $(SRC)/News.cpp
	g++ -g -c $(SRC)/News.cpp -o $(BUILD)/news.o

$(BUILD)/newsManager.o: $(SRC)/NewsManager.cpp
	g++ -g -c $(SRC)/NewsManager.cpp -o $(BUILD)/newsManager.o

$(BUILD)/language.o: $(SRC)/language.cpp
	g++ -g -c $(SRC)/language.cpp -o $(BUILD)/language.o

clean:
	rm -f $(BUILD)/*



