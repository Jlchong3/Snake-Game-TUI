# Snake Game

This is a simple implementation of the Snake Game in the terminal. It is written in C using the `ncurses` library for handling the graphical interface in the terminal.

## Dependencies
- `ncurses` 6.x
  
### Installing Dependencies
#### Ubuntu/Debian:
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```
#### Fedora/Red Hat:
```bash
sudo yum install ncurses-devel
```
#### Arch Linux:
```bash
sudo pacman -S ncurses
```

## How to Compile and Run
Once you have the dependencies installed, follow these steps to compile and run the game:

1. **Clone or Download the Project:**
   If you haven’t cloned the repository yet, clone it to your local machine:
   ```bash
   git clone https://github.com/Jlchong3/Snake-Game-TUI.git snake_game
   cd snake_game
   ```

2. **Compile the Game:**
   Use `make` to compile the source code:
   ```bash
   make
   ```

3. **Run the Game:**
   After compiling, run the game with the following command:
   ```bash
   ./snake
   ```

## Controls
- **Arrow Keys**: Use the arrow keys to control the direction of the snake.
- **q**: Press `q` to quit the game.
- **r**: When the game is over, press `r` to restart the game.

## Gameplay
The objective of the game is to eat the apples that appear on the screen. Every time the snake eats an apple, it grows longer, and the score increases. The game ends if the snake collides with itself or with the walls of the game window.

## Features
- **Snake Movement**: Controlled by the arrow keys.
- **Randomly Generated Apples**: The apples are randomly generated on the game screen.
- **Score Tracking**: Your score increases each time the snake eats an apple.
- **Game Over Screen**: A simple game over screen with the option to retry or quit.

## Future Improvements
- Implement different levels of difficulty.
- Add a high score feature.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
