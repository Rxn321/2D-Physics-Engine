# 2D-Physics-Engine
Core 2D physics module for my orbital motion simulation project

## Build & run
git clone --recurse-submodules https://github.com/Rxn321/2D-Physics-Engine.git  
cd 2D-Physics-Engine  
mkdir build && cd build  
cmake ..  
cmake --build .  
./Debug/PhysicsEngine.exe  

## Features

- 2D Newtonian gravity
- Multiple-body gravitational interactions
- Collision detection
- Body merging / accretion
- OpenGL rendering
- Gravity-well mesh
- Click-to-spawn bodies
- Fix click-to-spawn world coordinates with the new camera

## Future Stuff

- Interactive camera
- Simulation controls
- Better collision handling for high-speed bodies
- More stable integration method (RK4 vs. semi-implicit Euler)
- Visual polish
- N-body simulation benchmarking and algorithm improvements (Barnes-Hut)
 
 Grav mesh well rn: h(x,z)=−VISUAL_SCALE ∑_i​(G*m_i​​​/r_i​)
​
