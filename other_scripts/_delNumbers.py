file = open('../news_russian_words.csv', 'r')
outfile = open('../news_russian_words_2.csv', 'w')

for line in file:
    tokens = line.split(',')
    if(len(tokens) > 2):
        continue
    if(len(tokens[0].split()) != 1):
        continue
    flag = True
    for c in tokens[0]:
        if c.isdigit():
            flag = False
    if flag:
        outfile.write(tokens[0]  + ',' + tokens[1])
        