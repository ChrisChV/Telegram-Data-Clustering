SRC = ./src
BUILD = $(SRC)/build
LIBS = ./libs
DOC2VEC = $(LIBS)/doc2vec/cpp
DOC2VECLIBS = $(DOC2VEC)/Doc2Vec.o $(DOC2VEC)/NN.o $(DOC2VEC)/TaggedBrownCorpus.o $(DOC2VEC)/TrainModelThread.o $(DOC2VEC)/Vocab.o $(DOC2VEC)/WMD.o
AP = $(LIBS)/affinity-propagation-sparse
APLIBS = $(AP)/ap.o
LANGLIBS = $(LIBS)/langdetect/bin/lib/liblangdetect.so

tgnews: $(BUILD)/main.o $(BUILD)/parser.o $(BUILD)/fileManager.o $(BUILD)/news.o $(BUILD)/newsManager.o $(BUILD)/language.o $(BUILD)/jsonParser.o $(BUILD)/newsDiscriminator.o $(DOC2VECLIBS) $(BUILD)/D2V.o $(BUILD)/classifier.o $(BUILD)/threading.o $(APLIBS) $(LANGLIBS)
	g++ -g -o ./tgnews $(BUILD)/main.o $(BUILD)/parser.o $(BUILD)/fileManager.o $(BUILD)/news.o $(BUILD)/newsManager.o $(BUILD)/language.o $(BUILD)/jsonParser.o $(BUILD)/newsDiscriminator.o $(DOC2VECLIBS) $(BUILD)/D2V.o $(BUILD)/classifier.o $(BUILD)/threading.o $(APLIBS) $(LANGLIBS) -lpthread

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

$(BUILD)/jsonParser.o: $(SRC)/jsonParser.cpp
	g++ -g -c $(SRC)/jsonParser.cpp -o $(BUILD)/jsonParser.o

$(BUILD)/newsDiscriminator.o: $(SRC)/newsDiscriminator.cpp
	g++ -g -c $(SRC)/newsDiscriminator.cpp -o $(BUILD)/newsDiscriminator.o

$(BUILD)/D2V.o: $(SRC)/D2V.cpp
	g++ -g -c $(SRC)/D2V.cpp -o $(BUILD)/D2V.o

$(BUILD)/classifier.o: $(SRC)/classifier.cpp
	g++ -g -c $(SRC)/classifier.cpp -o $(BUILD)/classifier.o

$(BUILD)/threading.o: $(SRC)/threading.cpp
	g++ -g -c $(SRC)/threading.cpp -o $(BUILD)/threading.o

$(AP)/ap.o: $(AP)/ap.cpp
	g++ -g -c $(AP)/ap.cpp -o $(AP)/ap.o

clean:
	rm -f $(BUILD)/*
	rm -f $(APLIBS)
