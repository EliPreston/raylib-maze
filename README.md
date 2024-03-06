# Maze creation & Cellular Automota with raylib

### Generating random maze using 2 approaches
1. Graph theory based using algorithms like Prim's/Wilson's (creates a perfect maze)
2. Cellular automota based (does not create a perfect maze - doesn't really create a maze at all, kind of just a cool pattern)
----


#### 1. Graph Theory
##### Wilson's Algorithm 
- Still a WIP, but working for the most part
- Very unoptomized, code needs to be refactored, cleaned, and optimized where possible (I'm not super concerned with crazy optimization)
![Alt Screenshot of a maze created](/img/graph_theory/Wilson_semi_working_v1.png)

##### Prim's Algorithm
- To Be Completed

----

#### 2. Cellular Automation
##### Interesting patterns
1. Mazectric rulestring (B3/S1234 same as 1234/3)

![Alt gif of cells](/img/cell_automation/cell_demo.gif)
- It looks so chopy because at this point in time I had it so that pressing 's' updated the population by one generation each time (so I was repeatedly button mashing 's')

![Alt Screenshot of initial population generated](/img/cell_automation/Initial_population.png)

![Alt Screenshot of grid expanding](/img/cell_automation/Population_expanding.png)

![Alt Screenshot of grid hitting edge of window](/img/cell_automation/Population_reaching_edge.png)

![Alt Screenshot of final resulting grid](/img/cell_automation/Population_fill.png)