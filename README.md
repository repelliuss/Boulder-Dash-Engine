<p align="center">
  <img width="200" height="200" src="https://b.allthepics.net/rpsLogo.png">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img width="200" height="250" src="https://b.allthepics.net/Screenshot_1.png">
</p>

# Boulder Dash Engine
> An engine for Boulder Dash

[<p align="center"><img src="https://media.giphy.com/media/eiXobdfN1XFTSwGI1s/giphy-downsized-large.gif" width="470" height="280" /></p>](https://www.youtube.com/watch?v=pzB-JUV8MwU)
<p align="center"> <i>Click on the GIF to see the Demonstration Video</i> </p>

## Table of Contents
* [General Info](#general-info)
* [Demonstration Video](#demonstration-video)
* [Screenshots](#screenshots)
* [Features](#features)
* [Libraries](#libraries)
* [How to Get](#how-to-get)
* [Making it Playable](#making-it-playable)
* [Modding](#modding)
* [Compile Yourself](#compile-yourself)
* [Licensing](#licensing)

## General Info
&nbsp;&nbsp;&nbsp;&nbsp;An engine for Boulder Dash that lets you make your own Boulder Dash. **This is not a play-ready project.** You need to have your own textures and music put for legal reasons. I just serve an engine, my own levels and some free assets ready.

&nbsp;&nbsp;&nbsp;&nbsp;I do not own any rights about Boulder Dash brand. All rights are reserved, as are trademarks of their respective owners. You can learn about [the original owners of the Boulder Dash brand here.](https://firststarsoftware.com/) 

## Demonstration Video
This is a demonstration and it just represents the original game assets loaded to engine. [Check out it here!](https://www.youtube.com/watch?v=pzB-JUV8MwU)

## Screenshots
<p align="center"><img src="https://b.allthepics.net/Hourglass.png" width="302" height="180" />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://b.allthepics.net/Waterquake.png" width="302" height="180" /></p>
<p align="center"><img src="https://b.allthepics.net/Pyramid.png" width="302" height="180" />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://b.allthepics.net/WaterClan.png" width="302" height="180" /></p>
<p align="center"> These screensots represent a demonstration with the original game assets loaded. </p>

## Features
* 10 Possible Level
* 4 Difficulty
* Animations
* Sounds
* Save and Load
* GUI
* Windows and Linux Support
* and more!

## Libraries
* [SDL2](https://www.libsdl.org/download-2.0.php)
* [SDL2 Image](https://www.libsdl.org/projects/SDL_image/)
* [SDL2 Mixer](https://www.libsdl.org/projects/SDL_mixer/)
* [SDL2 TTF](https://www.libsdl.org/projects/SDL_ttf/)

## How to Get
* If you want to get *Boulder Dash 2020* on Windows or Linux:
  * [Please click here for further instructions!](https://github.com/repelliuss/Boulder-Dash-Engine/releases/latest)
* Don't forget to see [Making it Playable!](#making-it-playable)

## Making it Playable
Go to the README files at those locations and follow the instructions in them!
* [Resources/Levels](Resources/Levels)
* [Resources/Images](Resources/Images)
* [Resources/Musics](Resources/Musics)

## Modding
You can modify:
* Levels. To do that, you can put your tileset to a tile editor, create your level and get a plain text of the level you created. It should be in the same form as in the [Resources/Levels](Resources/Levels)
* SFXs
* Musics
* Animations
* Textures
* and of course engine itself!

## Compile Yourself
### Linux
#### Dependencies
* For **Ubuntu**:
  * `apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev`
* For others:
  * Please get [libraries](#libraries) for your environment.
#### Building
  ```
  git clone https://github.com/repelliuss/Boulder-Dash-2020.git
  cd Boulder-Dash-2020
  make
  ```
### Windows
* Please get [libraries](#libraries) and configure it yourself for your environment.

## Licensing
### SFX
* step_dirt is made by [TinyWorlds](https://opengameart.org/users/tinyworlds) which is licensed under [CC0](https://creativecommons.org/publicdomain/zero/1.0/).
* gate_open and foe_kill are from [NES Sounds](https://opengameart.org/content/nes-sounds), made by [Baŝto](https://opengameart.org/users/ba%C5%9Dto) which is licensed under [CC0](https://creativecommons.org/publicdomain/zero/1.0/).
* diamond_fell, diamond_pick, life_up, and level_screen_move are obtained from [ZAPSPLAT](https://www.zapsplat.com).
* game_win, game_lose, level_win, level_lose and screen_select made by [Little Robot Sound Factory](https://www.zapsplat.com/author/little-robot-sound-factory/) which is licensed under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).
* I lost the source of stone_fell. Contact me if you know.

### Others
&nbsp;&nbsp;&nbsp;&nbsp; All of the source code and other assets are put under [MIT](LICENSE) license by [repelliuss](https://github.com/repelliuss).  
