# Snake Game

Snake Game made by Khoa Nguyen Duc - 2311616.
Based on Raylib library.

## Prerequisites

Before compiling and running this game, you need to have the Raylib library installed on your system.

### Install Raylib

#### Windows
There are two main ways to install Raylib on Windows:

##### Option 1: Using w64devkit (Recommended)
This is the easiest way to set up everything at once:

1. Download w64devkit from [GitHub](https://github.com/skeeto/w64devkit/releases)
   - Download the latest zip file (e.g., `w64devkit-x.x.x.zip`)
2. Extract the zip to `C:\raylib\w64devkit`
3. Download Raylib from [GitHub](https://github.com/raysan5/raylib/releases)
   - Download the latest `raylib-x.x.x_win64_mingw-w64.zip`
4. Extract the zip and move the contents to `C:\raylib\raylib`
5. Add `C:\raylib\w64devkit\bin` to your PATH:
   - Open Control Panel → System → Advanced system settings → Environment Variables
   - Edit the Path variable and add `C:\raylib\w64devkit\bin`

##### Option 2: Manual Installation
If you prefer to use your own MinGW or MSVC:

1. Download Raylib from [GitHub](https://github.com/raysan5/raylib/releases)
   - For MinGW: `raylib-x.x.x_win64_mingw-w64.zip`
   - For MSVC: `raylib-x.x.x_win64_msvc16.zip`
2. Extract to a folder (recommended: `C:\raylib\raylib`)
3. If using MinGW: 
   - Ensure your MinGW installation's bin folder is in your PATH
   - Copy the Raylib DLL from `C:\raylib\raylib\lib` to your project or system32 folder

#### Linux

##### Debian/Ubuntu
```bash
# Install required dependencies
sudo apt update
sudo apt install build-essential git cmake libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

# Clone the repository
git clone https://github.com/raysan5/raylib.git
cd raylib

# Build and install
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install

# Update the dynamic linker's run-time bindings
sudo ldconfig
```

##### Fedora/Red Hat
```bash
# Install required dependencies
sudo dnf install gcc cmake git alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel

# Clone the repository
git clone https://github.com/raysan5/raylib.git
cd raylib

# Build and install
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
```

##### Arch Linux
```bash
# Using pacman (easier)
sudo pacman -S raylib

# Or manual installation
sudo pacman -S git gcc cmake make
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
```

#### macOS

##### Using Homebrew (Recommended)
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install Raylib
brew update
brew install raylib
```

##### Manual Installation
```bash
# Install Xcode command line tools
xcode-select --install

# Install required dependencies (optional but recommended)
brew install cmake

# Clone the repository
git clone https://github.com/raysan5/raylib.git
cd raylib

# Build and install
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
```

##### Verification
To verify the installation, check if raylib library files are in `/usr/local/lib` and headers are in `/usr/local/include`.

## Compiling and Running the Game

### Windows

#### Using Make (with w64devkit or MinGW)
```cmd
mingw32-make RAYLIB_PATH=C:/raylib/raylib OBJS=*.cpp PROJECT_NAME=snake_game
```

#### Using Visual Studio Code Tasks (Recommended)
This project includes VS Code tasks for easy building:
1. Open the project in Visual Studio Code
2. Press `F5` to build and run the game in debug mode

#### Using GCC directly
```cmd
gcc -o snake_game.exe main.cpp Game.cpp Snake.cpp Food.cpp -O2 -I./include -I"C:/raylib/raylib/src" -L"C:/raylib/raylib/src" -lraylib -lopengl32 -lgdi32 -lwinmm
```

### Linux
```bash
# Using make with already installed raylib
make PLATFORM=PLATFORM_DESKTOP RAYLIB_PATH=/usr/local PROJECT_NAME=snake_game OBJS="main.cpp Game.cpp Snake.cpp Food.cpp"

# Or using g++ directly (if raylib is installed system-wide)
g++ -o snake_game main.cpp Game.cpp Snake.cpp Food.cpp -O2 -I./include -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Run the game
./snake_game
```

### macOS
```bash
# Using make with already installed raylib
make PLATFORM=PLATFORM_DESKTOP RAYLIB_PATH=/usr/local PROJECT_NAME=snake_game OBJS="main.cpp Game.cpp Snake.cpp Food.cpp"

# Or using clang directly (if raylib is installed system-wide)
clang++ -o snake_game main.cpp Game.cpp Snake.cpp Food.cpp -O2 -I./include -I/usr/local/include -L/usr/local/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# Run the game
./snake_game
```

## Important Notes for Running the Game

### Assets Folder
The game must be run with the `assets` folder in the same directory as the executable. This folder contains all the textures and fonts required by the game.

## File Structure
- `main.cpp`: Entry point of the game
- `Game.cpp/h`: Game logic
- `Snake.cpp/h`: Snake entity
- `Food.cpp/h`: Food entity
- `assets/`: Contains all game textures and fonts
