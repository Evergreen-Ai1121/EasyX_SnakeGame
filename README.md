# EasyX_SnakeGame
This is a classic Snake game developed in C++ using the EasyX graphics library. Based on the traditional Snake game, this project implements a dual control interaction mode using both keyboard and mouse through the Windows messaging mechanism, and uses double buffering technology to ensure smooth and flicker-free graphics.

Core Technology Highlights：

Graphics Rendering and Performance Optimization: Utilizing BeginBatchDraw and EndBatchDraw to enable double-buffered rendering effectively solves common 2D game issues such as screen tearing and flickering. By customizing the drawImage function and using bitwise operations along with Bayesian theorem principles to process pixel Alpha channels, transparent background textures are achieved.

Interaction Logic Design:

Message Pump Driven: Asynchronously obtaining user input through peekmessage ensures that game logic remains smooth even when handling high-frequency inputs (such as mouse movement).
Coordinate Quadrant Turning Algorithm: In mouse control logic, by calculating the relative position offset of the click coordinates to the snake's head (Δx, Δy) and comparing absolute values, the turning intent is determined, realizing an intuitive mouse click turning function.

Game Engine Logic: Managing the snake's body coordinates with dynamic arrays implements the classic "snake body following" logic. Based on rectangular collision detection (AABB), apple collection detection, wall collision detection, and self-collision detection are achieved.

Control Guide：

Keyboard Mode: Use arrow keys ↑ ↓ ← → to control the snake's movement direction.

Mouse Mode:
- Left Click: Click the four quadrants around the snake's head, and the snake will automatically turn toward the clicked direction.
- Right Click Function: In the Game Over state, right-click to quickly restart the game.
- Mouse Movement: The cursor dynamically changes style based on its current position relative to the snake's head to guide operation.

Folder Description：

/src: Contains the core C++ source code.

/she: Stores the BMP image resources required by the game (background, snake head, snake body, apple).

Future Optimization Directions：

Add a level system and moving obstacles.

Introduce a local high score recording feature (file I/O).

Optimize the snake body movement algorithm to support smoother, non-grid-based movement.
