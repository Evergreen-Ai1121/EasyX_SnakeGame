# EasyX_SnakeGame

<div align="center">
  <img src="./she/演示demo.gif" width="25%" alt="贪吃蛇游戏演示">
  <p><em>项目运行演示视频</em></p>
</div>  


## 概述

  这是一款经典的蛇类游戏，使用 C++ 开发，使用 EasyX 图形库。基于传统的《蛇》游戏，该项目通过Windows消息机制实现了双键鼠标交互模式，并采用双缓冲技术确保画面流畅无闪烁。

### 核心技术亮点：

  图形渲染与性能优化：利用 BeginBatchDraw 和 EndBatchDraw 实现双缓冲渲染，有效解决常见的二维游戏问题，如屏幕撕裂和闪烁。通过定制 drawImage 函数，并结合贝叶斯定理处理像素 Alpha 通道，实现了透明背景纹理。

### 交互逻辑设计：

  消息泵驱动：通过窥视信息异步获取用户输入，确保即使处理高频输入（如鼠标移动）时，游戏逻辑依然流畅。 坐标象限转动算法：在鼠标控制逻辑中，通过计算点击坐标与蛇头的相对位置偏移（Δx， Δy）并比较绝对值，确定转动意图，实现直观的鼠标点击转动函数。

### 游戏引擎逻辑：

  用动态数组管理蛇体坐标实现了经典的“蛇体跟随”逻辑。基于矩形碰撞检测（AABB），实现了苹果收集检测、墙体碰撞检测和自碰撞检测。

### 控制指南：

#### 键盘模式：

  使用方向键↑ ↓ ← →控制蛇的移动方向。

#### 鼠标模式：

左键：点击蛇头部周围的四个象限，蛇会自动转向点击的方向。
右键功能：在游戏结束状态下，右键点击即可快速重启游戏。
鼠标移动：光标根据其相对于蛇头的当前位置动态变化样式，以引导操作。

### 文件夹描述：

/src：包含核心的C++源代码。

/she：存储游戏所需的BMP图像资源（背景、蛇头、蛇身、苹果）。

### 未来优化方向：

  增加关卡系统和移动障碍。

  引入本地高分记录功能（文件I/O）。

  优化蛇体运动算法，支持更平滑、非网格式的移动。

---

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
