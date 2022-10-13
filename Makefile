CC := gcc
CFLAGS := -g3
INCLUDES := -I minilibx-linux -I gnl
LIBRARIES := -L minilibx-linux -lmlx -lXext -lX11
GNL := gnl/get_next_line.o gnl/get_next_line_utils.o
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log
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

all: $(NAME)

$(NAME): $(SOURCES) libmlx.a $(GNL)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) $(GNL) $(LIBRARIES) -o $@

gnl/get_next_line.o:
	$(CC) $(CFLAGS) -c $(@:%.o=%.c) -o $@ -D BUFFER_SIZE=256

gnl/get_next_line_utils.o:
	$(CC) $(CFLAGS) -c $(@:%.o=%.c) -o $@ -D BUFFER_SIZE=256

libmlx.a:
	$(MAKE) -C minilibx-linux/

run_valgrind: $(NAME)
	valgrind $(VALGRIND_FLAGS) ./$< maps/valid_map.ber
