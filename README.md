# Maze creation & Cellular Automota with raylib

### Generating random maze using 2 approaches
1. Graph theory based using algorithms like Prim's/Wilson's (creates a perfect maze)
2. Cellular automota based (does not create a perfect maze - doesn't really create a maze at all, kind of just a cool pattern)


#### 1. Graph Theory
##### Wilson's Algorithm 
![Alt Screenshot of a maze created](/img/Wilson_semi_working_v1.png)

##### Prim's Algorithm
- To Be Completed

----

#### 2. Cellular Automation
##### Interesting patterns
1. 
    - Birth: neighbourhood == 3 || neighbourhood == 5 
    - Death: neighbourhood < 1 || neighbourhood > 5

2.  
    - Birth: neighbourhood == 3 || neighbourhood == 4
    - Death: neighbourhood < 1 || neighbourhood > 5