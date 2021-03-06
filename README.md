# MineSweeper 64
![boxart](https://github.com/manfriedn64/minesweeper64/blob/master/screenshots/boxart.png?raw=true)
![title screen](https://github.com/manfriedn64/minesweeper64/blob/master/screenshots/title.png?raw=true)![menu screen](https://github.com/manfriedn64/minesweeper64/blob/master/screenshots/menu.png?raw=true)
![in game screen](https://github.com/manfriedn64/minesweeper64/blob/master/screenshots/game.png?raw=true)![game over screen](https://github.com/manfriedn64/minesweeper64/blob/master/screenshots/lose.png?raw=true)

Here is a simple mine sweeper game for the N64. It's a first homebrew project in order to check the viability of a 640x480 high resolution 2D game for this hardware. Here with the largest game board (1200 sprites of 16x16 pixels) we can achieve at worst 15 frames per seconds when the menu is loaded too. So the conclusion is "maybe". Almost all the 4MB of RAM are used, Expansion Pak is detected just for fun, it's not needed.

## Compatibility

Tested on
 - NTSC hardware (with 64Drive and Everdrive)
 - Project 64
 - Cen64
Should work with a PAL hardware but I did not checked mine yet.

This ROM can take advantage of both the Expansion Pak and the Rumble Pak :
 - Expansion Pak allows for sounds to be played (let be honest: this won't change much the game)
 - Rumble Pak, well it rumbles ! When you reveal a case nearby a bomb or when you loose

# How to play
## With the ROM file
Simply load the file minesweeper64.n64 with you prefered emulator or copy it on your SD card if you have a 64Drive or an Everdrive
## How to compile
First, install the N64 SDK and Sound Tools, then execute :

    run_make.bat

## Controls

- Next Screen = Start Button
- New Game = D-Pad Up and Down to navigate, Left and Right to change values, A to validate
- Pause = Use D-Pad to navigate and A button to validate your choice.
- Move the cursor = D-Pad or Analog stick
- Reveal a case : A button
- Flag / Unflag : B button
- Show debug infos : Z-trigger

## Known issues
After the initial expansion pak screen there is a glitch with one texture swapped by another. I guess why but it does not really bother me so not fixed yet.

## What you could do
In file `minesweeper_main.c` function `revealPanel` has a bit of code commented out. That's because it makes the game crashes and I did not figured out why. It would be something nice to fix in terms of gameplay mechanic (it reveals all the adjacents blank tiles when you reveal one).

