# So Long - 42-SP


![](https://raw.githubusercontent.com/marianohtl/SoLong/master/images/png/Untitled-1.png)

<br>

And thanks for all the fish!
Reading a line from a fd is way too tedious.

<br>

### Summary:

This project is a very small 2D game. Its purpose is to make you work with textures, sprites, and some other very basic gameplay elements.

<br>

### Mandatory part

<br>

| So Long | |
| ----------- | ----------- |
| Function name | so_long |
| Turn in files | Makefile, *.h, *.c, maps |
| Makefile | NAME, all, clean, fclean, re |
| Arguments | A map in format *.ber |
| External functs. |  - open, close, read, write, malloc, free, perror, strerror, exit <br> -  All functions of the math library (-lm compiler option, man man 3 math) <br>  - All functions of the MiniLibX <br> - ft_printf and any equivalent YOU coded |
| Libft authorized | Yes |
| Description | You must create a basic 2D game in which a dolphin escapes Earth after eating some fish. Instead of a dolphin, fish, and the Earth, you can use any character, any collectible and any place you want.  |

<br>

 Your project must comply with the following rules:
* You must use the MiniLibX. Either the version available on the school machines,
or installing it using its sources.
* You have to turn in a Makefile which will compile your source files. It must not
relink.
* Your program has to take as parameter a map description file ending with the .ber
extension.

<br>

## 1 Game

* The player’s goal is to collect every collectible present on the map, then escape
chosing the shortest possible route.
* The W, A, S, and D keys must be used to move the main character.
* The player should be able to move in these 4 directions: up, down, left, right.
* The player should not be able to move into walls.
* At every move, the current number of movements must be displayed in the shell.
* You have to use a 2D view (top-down or profile).
* The game doesn’t have to be real time.
* Although the given examples show a dolphin theme, you can create the world you want.

 <br>
 
If you prefer, you can use ZQSD or the arrow keys on your keyboard to
move your main character.

<br>

## 2 Graphic management

<br>

* Your program has to display the image in a window.
* The management of your window must remain smooth (changing to another window, minimizing, and so forth).
* Pressing ESC must close the window and quit the program in a clean way.
* Clicking on the cross on the window’s frame must close the window and quit the program in a clean way.
* The use of the images of the MiniLibX is mandatory.

<br>

## 3 Map

<br>

* The map has to be constructed with 3 components: walls, collectibles, and free
space.
* The map can be composed of only these 5 characters:
<br> 0 for an empty space,
<br> 1 for a wall,
<br> C for a collectible,
<br> E for a map exit,
<br>P for the player’s starting position.

<br>

Here is a simple valid map:
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

* The map must contain at least 1 exit, 1 collectible, and 1 starting position.

<br>

If the map contains a duplicates characters (exit/start), you should
display an error message.

## Bonus part

<br>

Usually, you would be encouraged to develop your own original extra features. However,
there will be much more interesting graphic projects later. They are waiting for you!!
Don’t lose too much time on this assignment!

You are allowed to use other functions to complete the bonus part as long as their
use is justified during your evaluation. Be smart!

You will get extra points if you:

Make the player lose when they touch an enemy patrol.
* Add some sprite animation.
* Display the movement count directly on screen instead of writing it in the shell.

The bonus part will only be assessed if the mandatory part is PERFECT. Perfect means the mandatory part has been integrally done and works without malfunctioning. If you have not passed ALL the mandatory requirements, your bonus part will not be evaluated at all.

<br>

## Result

<br>

![](https://raw.githubusercontent.com/marianohtl/SoLong/master/images/png/game01.png)

<br>

![](https://raw.githubusercontent.com/marianohtl/SoLong/master/images/png/game02.png)

<br>

![](https://raw.githubusercontent.com/marianohtl/SoLong/master/images/png/game03.png)

