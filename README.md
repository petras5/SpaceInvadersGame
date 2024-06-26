# SpaceInvadersGame

Project for class Object-Oriented Programming in C++: Space Invaders game in SFML
Game features:

1. Space Invaders is a game in which the player controls a laser cannon that moves horizontally at the bottom of the screen. The player uses the cannon to fire projectiles that destroy aliens from the top of the screen (one projectile is enough to destroy one alien). The objective of the game is to destroy all the displayed aliens on the screen using projectiles. By destroying each alien, the player earns a certain number of points (initially, the player has 0 points).
2. Initially, there are 55 aliens on the screen arranged in 5 rows of 11 aliens.
3. The aliens move left and right (all together, as a group). When the aliens (as a group) reach one edge of the screen, they start moving towards the opposite edge of the screen, and with each such change of direction, they also move a little downwards (i.e., towards the laser cannon).
4. The aliens can also occasionally fire projectiles that can destroy the player (each projectile takes one life from the player - initially, the player has three lives). The player's projectiles are of a different color than the aliens' projectiles (they can also have a different shape, although this different shape requirement is not mandatory!). The aliens' projectiles do not affect other aliens (i.e., aliens cannot destroy other aliens!).
5. Although the player initially has three lives, the game immediately ends if the aliens reach the bottom of the screen.
6. There are 3 types of aliens; green ones give 10 points, pink ones give 20, and yellow ones give 30.
7. With each downward movement of the aliens, their speed increases (by 0.1f).
8. During the movement of the aliens, there is an animation; when they move to the left, they are turned with their heads to the left, and when they move to the right, their heads are turned to the right, i.e., when they touch the left or right edge, their display changes.
9. The laser cannon is partially protected by defensive objects that are destroyed after a total of 8 hits by the ship's bullets and the aliens' projectiles. Also, if the aliens descend far enough, they will destroy the barriers (if any remain).
10. If the player destroys all the aliens on the screen, a new set of 55 aliens appears, arranged as at the beginning of the game, but now faster (by 0.5f) and they appear 1 block lower (32px). If these are destroyed, the process repeats.

I have also added a high score which is currently recorded in highscore.txt (you can manually set it to 0 in the file if the current score is too high).
Instructions for the game: The ship is moved with the left and right arrow keys and fires projectiles by pressing the Space key.

Here is yt video for setting up new SFML project in Visual Studio 2022: https://www.youtube.com/watch?v=uTOF55HGyTc&list=PLCTPJ02ObVzat-jR49nwnmggN2E7_zvlw&index=45&ab_channel=PROG-2021 .

Spritesheet design: https://www.kenney.nl/assets/space-shooter-redux
https://www.kenney.nl/assets/platformer-pack-redux
