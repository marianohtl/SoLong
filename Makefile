CC := gcc
CFLAGS := -g3
INCLUDES := -I minilibx-linux
LIBRARIES := -L minilibx-linux -lmlx -lXext -lX11

a.out: main.c libmlx.a
	$(CC) $(CFLAGS) $(INCLUDES) $< $(LIBRARIES) -o $@

libmlx.a:
	$(MAKE) -C minilibx-linux/