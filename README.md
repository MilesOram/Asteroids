# Asteroids
WIP.
Uses SFML library for graphics, 32-bit, C++ 17.

Recreation of Asteroids, with addition that every 30 seconds there is increased asteroid spawn rate and increased fire rate for a period.

Previously built a single-threaded version of this. Current version is multi-threaded and includes:
Lock-free Object pool for GameObjects - allows dynamic resizing at runtime depending on config settings which can also be changed in anticipation of higher/lower demand.
Job System - game loop is divided into the following phases - Update->Collision->Cleanup->Snapshot (rendering occurs during update and collision phases). Phase transition is managed by a job, this job creates all the jobs for the next phase and stores them in a buffer queue, it then waits for other threads to finish and sync with the main thread if needed. It then swaps the buffer and signals all the threads. This new batch of jobs contains the next phase transition job on the end.
Component system - similar to Unity, currently includes collision components (box,circle and polygon) and a pooled object component for objects that belong to a pool
Collision - Uses GJK for all intersection testing (excluding circle-circle) and double dispatch to select the relevant function. Screen is partitioned into a grid, each object uses a phase box to place it in the cells in the grid that it occupies. Could use a spatial hash grid but wanted something that allowed concurrent lock-free insertion and removal, at the cost of a larger memory footprint. The grid allocates a large block of memory which it divides into cells which contain nodes for each object. The nodes also contain the collision tags of that object and the tags it is looking for, the result is a check for 