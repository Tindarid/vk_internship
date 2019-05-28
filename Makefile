SOURCES=murmurhash.h murmurhash.cpp uniq_counter.h uniq_counter.cpp count_distinct.cpp

all: $(SOURCES)
	g++ $(SOURCES) -o count_distinct

run:
	./count_distinct

clean:
	rm ./count_distinct
