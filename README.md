# [VIDEOGAME-TITLE] Developing for Fun
I don't really know how this personal project will turn out, just thought it would be fun to give game development a shot

# Event Clock Class
11/16/2021 - Haven't exactly touched this library in a year, but the intent was to create an object that will execute a function after a specified amount of time. Now that I think about it, could probably due for some new features an optimization.

# The Main Game - Title Pending
11/16/2021 - So I'm starting this log in the middle of my project. Though I do have a personal book logging my progress, I am not exactly inclined to detail what I done so far as it will take a while to get up to speed.
As of right now, I recently moved my developer tools into it's own class to clean up the main file and to make adding features a bit easier. Currently planning on creating a class for general equations to save time on level design.

## To Do List:
1) Make a ganeral equations class for ground and platform collision
- All equations must come with their first derivative
2) Review platNObj.cpp and try to optimize the code and hyave the platform slope be recognized
- Player only sees slope of ground when sliding
3) Create and format level files
- Will most likely need to be C++ classes as the engine needs to know which equation and coefficients needs to be used where
- Each level might also have unique equations so I must plan for that as well
- Planning on only loading the level file the player is on to save on compiling time
4) Add obsticles: trees, rocks, bumps on the ground
- May want to use matrecies to rotate the object collision
- Probably goint to use equations for object collisions as well
- Player must be able to ride over them if angle of impact isn't too perpendicular
5) Level scrolling
6) Level select screen <br>
<dl>
  <dd>?) No plans as of yet<dd/>
  <dd>Uh) Art... other than essays, not my strongest skill<dd/>
<dl/>
- Gonna try to keep it as simple as possible, thi8nking maybe flat-ish colors
