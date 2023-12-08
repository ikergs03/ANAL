#-----------------------
# IMPORTANTE: The values of the parameters for exercise?_test have to be conveniently adjusted.
# It is assumed that the name of the source files is exercise1.c, exercise2.c,...,exercise.h
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = exercise1 exercise2

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o sorting.o search.o times.o permutations.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -o $@ $@.o sorting.o search.o times.o permutations.o

permutations.o : permutations.c permutations.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

sorting.o : sorting.c sorting.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

search.o : search.c search.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

times.o : times.c times.h add_to_times.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

exercise1_test:
	@echo Running exercise1
	@./exercise1 -size 10 -key 5

#exercise2_test:
#	@echo Running exercise2
#	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 1 -outputFile bin_search_1.log

#exercise2_sorted_test:
#	@echo Running exercise2_sorted
#	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 10000 -outputFile lin_auto_search_10000.log

bin_exercise2_1_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 1 -outputFile bin_search_1.log

bin_exercise2_100_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 100 -outputFile bin_search_100.log

bin_exercise2_10000_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 10000 -outputFile bin_search_10000.log



lin_sorted_exercise2_1_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 1 -outputFile lin_sorted_search_1.log

lin_sorted_exercise2_100_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 100 -outputFile lin_sorted_search_100.log

lin_sorted_exercise2_10000_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 10000 -outputFile lin_sorted_search_10000.log


lin_unsorted_exercise2_1_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 1 -outputFile lin_unsorted_search_1.log

lin_unsorted_exercise2_100_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 100 -outputFile lin_unsorted_search_100.log

lin_unsorted_exercise2_10000_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 10000 -outputFile lin_unsorted_search_10000.log



lin_auto_exercise2_1_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 1 -outputFile lin_auto_search_1.log

lin_auto_exercise2_100_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 100 -outputFile lin_auto_search_100.log

lin_auto_exercise2_10000_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 10000 -outputFile lin_auto_search_10000.log