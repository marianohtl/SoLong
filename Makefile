CC := gcc
CFLAGS := -g3
INCLUDES := -I minilibx-linux -I gnl
LIBRARIES := -L minilibx-linux -lmlx -lXext -lX11
GNL := gnl/get_next_line.o gnl/get_next_line_utils.o

a.out: main.c libmlx.a $(GNL)
	$(CC) $(CFLAGS) $(INCLUDES) $< $(GNL)  $(LIBRARIES) -o $@

gnl/get_next_line.o:
	$(CC) $(CFLAGS) -c $(@:%.o=%.c) -o $@ -D BUFFER_SIZE=256

gnl/get_next_line_utils.o:
	$(CC) $(CFLAGS) -c $(@:%.o=%.c) -o $@ -D BUFFER_SIZE=256

libmlx.a:
	$(MAKE) -C minilibx-linux/
