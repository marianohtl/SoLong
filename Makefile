CC := gcc
CFLAGS := -Wall -Wextra -Werror -O2
INCLUDES := -I minilibx-linux -I gnl
LIBRARIES := -L minilibx-linux -lmlx -lXext -lX11
GNL := gnl/get_next_line.o gnl/get_next_line_utils.o
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes
NAME := so_long

SOURCES := \
	error_handler.c \
	initializers.c \
	linked_list.c \
	main.c \
	maps_utils.c \
	maps.c \
	movement_utils.c \
	movement.c \
	search.c \
	search_utils.c \
	utils.c \
	validation.c
OBJECTS := $(SOURCES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJECTS) minilibx-linux/libmlx.a $(GNL)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(GNL) $(LIBRARIES) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LIBRARIES) -D BUFFER_SIZE=256

clean:
	rm -f $(OBJECTS) $(GNL)
	$(MAKE) -C minilibx-linux/ clean

fclean: clean
	rm -f $(NAME)

re: | fclean all

minilibx-linux/libmlx.a:
	$(MAKE) -C minilibx-linux/

run_valgrind: $(NAME)
	mkdir -p valgrind_log
	for MAP in $$(find maps -type f); \
	do \
	echo $${MAP}; \
	valgrind $(VALGRIND_FLAGS) --log-file=valgrind_log/$$(basename $${MAP%.ber}).log ./$< $${MAP}; \
	echo ; \
	done
	valgrind $(VALGRIND_FLAGS) --log-file=valgrind_log/do_not_exist.log ./$< maps/invalid/do_not_exist.ber || echo DONE

.PHONY: all clean fclean re
