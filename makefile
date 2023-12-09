CC = g++
F = -std=c++17 -Ofast
TARGET = main

DEFAULT_FLAGS = -DCURRENT_DAY -DTIME_SOLUTIONS

# default - run only current day
all: FLAGS = $(DEFAULT_FLAGS)
all: $(TARGET)

# run all solutions
all_solutions: FLAGS = -DPRINT_ALL
all_solutions: $(TARGET)

# run only solved solutions
solved_solutions: FLAGS = -DPRINT_SOLVED -DPRINT_ALL
solved_solutions: $(TARGET)


# run specific day
day:
	@$(CC) $(F) $(FLAGS) -DPRINT_SPECIFIC_DAY=$(DAY) main.cpp -o $(TARGET)
	@./$(TARGET)
	@rm $(TARGET)

$(TARGET): main.cpp
	@$(CC) $(F) $(FLAGS) main.cpp -o $@
	@./$@
	@rm $@


help:
	@echo "Usage: make [TARGET]"
	@echo "TARGETS:"
	@echo " no target - run only current day"
	@echo " all - run only current day"
	@echo " all_solutions - run all solutions"
	@echo " solved_solutions - run only solved solutions"
	@echo " day DAY=N - run specific day"
	@echo " help - print this help message"

.PHONY: all all_solutions solved_solutions help day