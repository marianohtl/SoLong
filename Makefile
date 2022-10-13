CC := gcc
CFLAGS := -g3
INCLUDES := -I minilibx-linux -I gnl
LIBRARIES := -L minilibx-linux -lmlx -lXext -lX11
GNL := gnl/get_next_line.o gnl/get_next_line_utils.o
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log

SOURCES := linked_list.c \
	main.c \
	maps.c \
	search.c \
	utils.c \
	validation.c

a.out: main.c libmlx.a $(GNL)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) $(GNL)  $(LIBRARIES) -o $@

gnl/get_next_line.o:
	$(CC) $(CFLAGS) -c $(@:%.o=%.c) -o $@ -D BUFFER_SIZE=256

gnl/get_next_line_utils.o:
	$(CC) $(CFLAGS) -c $(@:%.o=%.c) -o $@ -D BUFFER_SIZE=256

libmlx.a:
	$(MAKE) -C minilibx-linux/

foo: test.out

test.out: test_validation.c search.c maps.c validation.c linked_list.c $(GNL)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

run_valgrind: a.out
	valgrind $(VALGRIND_FLAGS) ./$< maps/max_map.ber
	# valgrind $(VALGRIND_FLAGS) ./$< maps/valid_map.ber
