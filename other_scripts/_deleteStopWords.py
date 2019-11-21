file = open('../news_russian_words_2.csv', 'r')
outfile = open('../news_russian_words_3.csv', 'w')
swFile = open('../stopwords-english')

sw = []

for line in swFile:
    sw.append(line.strip())

for line in file:
    tokens = line.split(',')
    if tokens[0] not in sw:
        outfile.write(tokens[0] + ',' + tokens[1])

    