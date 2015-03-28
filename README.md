Snake Game in C
==

The classic snake game that a lot of us were addicted to playing on our cellphones, made for DOS using `C/C++` language with Borland's Turbo C & graphics.h library 

[![Watch On YouTube](http://i.imgur.com/tTlvkg4.png)](https://youtu.be/j2-9hhOSbMk)

https://www.youtube.com/watch?v=j2-9hhOSbMk

The project started as a hobby project to explore my `C/C++` skills and I along with my friends used it as my project for the Computer Graphics course at my university

Originally posted on [TechBirbal](https://web.archive.org/web/20100104105759/http://techbirbal.com/viewtopic.php?f=36&t=1884) on Wed, Feb 20, 2008 by me, under my alias [`ju_s_t4u`](https://web.archive.org/web/20081224015638/http://www.techbirbal.com/memberlist.php?mode=viewprofile&u=1050&sid=5cbebf484d9009ba19c09f5be2e5b9d2). Unfortunately, this great site was discontinued by its owner, hence only archived links available


> *You may need to install [DosBox](http://www.dosbox.com/) to compile and/or play the game.*  

Introduction
--

This is the classic version of the most popular mobile and computer game named “SNAKE”. The main objective of this game is to feed an increasing length of a snake with food particles which are found at random positions, picking up bonus mongooses that occur at regular intervals.  

![Classic Snake Game](http://www.gralon.net/articles/illustrations/8114-snake.jpg)

The game starts with selecting one of the three difficulty levels followed by a screen which asks the user to select whether he wishes to play a bounded game or an unbounded game. These concepts are discussed later in the synopsis.


Features Of the Game
--

- A very user-friendly game
- Simple and easy game to understand
- Explanations provided in the game as and when required
- 3 different difficulty modes
- 2 different gaming arenas
- 3 Chances for each user
- Presence of bonuses in the game to increase scores
- Presentations of score card in a precise tabular form

Description
--
The “snake game” is a game made in C++ language. This is a game which is quite easy to play. The game is a classic representation of the snake game which appears as an inbuilt game feature in most of the leading mobile handsets like Nokia.

The "snake game" is one of the simplest game concepts ever, and just like Tetris it's very addictive. There are a lot of variations of this game written in Flash, a relatively easy game to code, with an ability that when keys are pressed in rapid succession they are all registered. This is necessary if you want to have full control of the snake at all times.

Your goal is to move the snake and eat as many "food" blocks as possible. There is only one food block at any given time. When the food is eaten, the snake grows in length. If you hit the snake itself the game is over.

Depending on the mode selection, the game modifies itself and hence gives the user choices as he is free to select the difficulty level, the game arena that he can select a bounded or an unbounded region. 

Each user gets 3 chances. After the snake consumes a food particle, the score increases. After picking up 15 food particles, a bonus mongoose appears. This Bonus is present only for a limited time. Once the user picks up a bonus, his points increase by 5.

If the user wishes to quit the game anytime, He or she can press the ‘X’ key on the keyboard. This would directly exit the game.

Different modes used in the game
--
- **Easy mode**: Here the box size in which the snake is allowed to move around freely is larger in size as compared to the other two modes. Hence, the user finds it a lot easier to control the snake. Chances for the snake to die are quite less

- **Medium mode**: Here the box size in which the snake is allowed to move around freely is larger in size as compared to the hard mode and smaller than in easy mode. Chances for the snake to die are moderate

- **Hard mode**: Here the box size in which the snake is allowed to move around freely is smallest. Chances for the snake to die are highest

Different Gaming Arena
--

- **Unbounded mode**: Here, during the process of travelling, if the snake hits the boundary wall, it does not die, instead it comes out from the opposite wall as though there is a continuation in the movement.

- **Bounded mode**: Here, during the process of travelling, if the snake hits the boundary wall, the snake dies, and this is counted as a loss of life. This is a tougher mode as compared to the unbounded mode.

