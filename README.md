# Burnout Paradise Remastered game events analyzer

<img align="left" src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
<img align="left" src="https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54" />
<img align="left" src="https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white" />
<img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" />

A tool for Burnout Paradise Remastered to analyze the game events.


## Usage
1. Run the [main.py](https://github.com/matty-ross/bpr-game-events-analyzer/blob/main/src/server/main.py) script to start a local server.
2. Inject the [game-events.dll](https://github.com/matty-ross/bpr-game-events-analyzer/blob/main/bin/game-events.dll) into the game.
3. Wait until it connects.
4. Start analyzing the game events in the [game_events.py](https://github.com/matty-ross/bpr-game-events-analyzer/blob/main/src/server/game_events.py) script (it is automatically reloaded with every new game event).

## Compiling
A prebuild binary is available [here](https://github.com/matty-ross/bpr-game-events-analyzer/blob/main/bin/game-events.dll). However, you can compile the dll yourself. Just choose the x86 platform and hit compile.
