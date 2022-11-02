# How to Play Super Peach Sisters

Disclaimer: Please see the 60 page Super-Peach-Sisters-Spec.pdf to read the entire manual of how this game is built, and other intricate requirements.

To see what the game looks like in action:

- macOS: You'll need to have XQuartz and freeGLUT installed to run the program.
    1. Install [XQuartz](https://web.archive.org/web/20220327060726/http://xquartz.org/):
        1. Click the download link, open the downloaded .dmg file, double-click on XQuartz.pkg, and follow the installation instructions.
        2. Log out and log back in again.
        3. To verify the installation, open a Terminal window and run the command `echo $DISPLAY`. That should produce one line of output that ends with `org.xquartz:0`.
    2. Install freeGLUT:
        1. Some Homebrew installation problems seem to be fixed by running the command or by running the commands
        2. Install the [homebrew](https://brew.sh) package manager.
        3. Open a Terminal window and run the command `brew install freeglut`.
        
        ```
        	git -C $(brew --repository homebrew/core) checkout master
        ```
        
        ```
        	rm -rf /usr/local/Homebrew/Library/Taps/homebrew/homebrew-core
        	brew update
        ```
        

# Game play pictures

![Untitled](How%20to%20Play%20Super%20Peach%20Sisters/Untitled.png)

![**Peach can head bonk the red blocks to unlock the FIREBALL and MUSHROOM JUMP powers just like in Super Mario Bros.**](How%20to%20Play%20Super%20Peach%20Sisters/Untitled%201.png)

**Peach can head bonk the red blocks to unlock the FIREBALL and MUSHROOM JUMP powers just like in Super Mario Bros.**

![**Unlock new levels once you cross the first one! Make sure you don’t run out of lives!**](How%20to%20Play%20Super%20Peach%20Sisters/Untitled%202.png)

**Unlock new levels once you cross the first one! Make sure you don’t run out of lives!**

![**Careful! If you get to close the monsters will throw fireballs at Peach! The game keeps track of your powers at the top. Peach has ShootPower! and JumpPower! currently.**](How%20to%20Play%20Super%20Peach%20Sisters/Untitled%203.png)

**Careful! If you get to close the monsters will throw fireballs at Peach! The game keeps track of your powers at the top. Peach has ShootPower! and JumpPower! currently.**

![Untitled](How%20to%20Play%20Super%20Peach%20Sisters/Untitled%204.png)

![Untitled](How%20to%20Play%20Super%20Peach%20Sisters/Untitled%205.png)

Can you beat the game? Discover more hidden features! What happens to a Koopa Troopa (Green Turtle) when you shoot a fire ball at it? How many levels are there to win?
