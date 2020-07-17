# Each *X*th level folder needs these:
* levelX_map
* levelX_music0.wav
* levelX_music1.wav
* levelX_music2.wav
* levelX_music3.wav
* levelX_tileset.png

*You need to put those to make it playable!*

## What are those?

* levelX_map is representation of tiles in tileset with some IDs that forms a
  map. That IDs stored in `include/BD_map.h`. If you want your to have your own
  tileset and want to give their custom ID, modify the IDs' values and
  recompile. There are already good levels created by me, so you don't have to
  if you want to experience that.
* levelX_musicY.wav is music that plays on that level. There is a timer and at
  some percentages of time next music starts to play. I used it to increase
  tension.
* levelX_tileset.png is consisting from tiles with their different frames. World
  5 has a different color key. level8 and level9 is in World 5. If you want to
  change color keys of levels go to the `get_color_key` function in
  `src/level.c` and modify it. I put a 2 templates representing how should you put
  your textures but in a blurred way because of legal problems. I also put an
  blurred_info_tileset.png to make it explicit what this tile is. Tiles below the info text are
  animation frames of that tile which is represented by the info text.
