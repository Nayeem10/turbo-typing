# TURBO-TYPING

This is a simple typing game, playable in both practice and multiplayer modes. Practice mode is available on both Windows and Linux, but multiplayer mode is only supported on Linux.

## Features

- **Practice Mode**: Playable on both Windows and Linux.
- **Multiplayer Mode**: Only playable on Linux. Allows two players to race against each other in real-time.

## Requirements

### Linux

- SDL2
- SDL2_mixer
- SDL2_ttf
- SDL2_image
- XKB

## Installation

### Linux

1. **Install Dependencies**:

    Ensure you have the required libraries installed. You can use the package manager to install them. For example,

    on Debian-based systems:

    ```sh
    sudo apt-get install libsdl2-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-image-dev libxkbcommon-dev
    ```
    on Arch-based systems:

    ```sh
    sudo pacman -S sdl2 sdl2_mixer sdl2_image sdl2_ttf libx11
    ```
    
3. **Build the Game**:

    Navigate to the project directory and build the game using the provided Makefile:

    ```sh
    make
    ```

4. **Build the Server**:

    Compile the server using g++:

    ```sh
    g++ -o server server.c
    ```

## Running the Game

### Practice Mode

To run the game in practice mode, simply execute the main game binary:

    ./main

### Multiplayer Mode

1. **Start the Server**:

    Run the server on one machine:

    ```sh
    ./server
    ```

2. **Configure Client**:

    Update the `constant.h` file with the IP address of the server machine. Change the line with the server IP address to match the server's IP.

    ```c
    #define SERVER_IP "192.168.x.x" // replace with your server's IP address
    ```

3. **Run the Game**:

    Both players need to start the game. Ensure both players are connected; otherwise, the game will remain halted if only one player presses multiplayer mode while the server is on.

    ```sh
    ./main
    ```

## Notes:
You can also change the fps from `constant.h`

    #define FPS x // replace with your desired FPS
   

## Windows Installation (Practice Mode Only)

Currently, there are no specific instructions provided for running the game on Windows. However, you need to ensure you have the SDL2, SDL2_mixer, SDL2_ttf, SDL2_image libraries installed. Follow general SDL2 installation guides for Windows and build the project using a compatible compiler.

## Contribution

Feel free to fork this repository and submit pull requests. For major changes, please open an issue first to discuss what you would like to change.


## Contact

For any issues or questions, please open an issue on this repository.

---

This README provides the basic instructions for setting up and running the TypeRacer game in both practice and multiplayer modes. Ensure you follow the installation steps carefully and update the server IP address as needed for multiplayer mode. Enjoy the game!
