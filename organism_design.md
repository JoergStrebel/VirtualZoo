# Simulation design

## World design

The parameters of the simulated organism will include the following variables:
* Orientation: the simulation keeps track of the heading - its body is not perfectly symmetrical, but it has a clear shape, that points the organism in a specific direction. 
* Location: the simulation keeps track of the x/y-coordinates. 

The world is a 2D environment with a rectangular grid structure for internal computations (the grid coordinates are not revealed to the organism). The world is a plain, that consists of ground and small patches of edible food, which are visible to the organism. Food which can be poisonous or edible. There are obstacles, i.e. trees, bushes. 

Interaction between 
Kollisionserkennung zwischen Organismus und anderen Objekten in der Welt. Diese Erkennung muss in der Welt stattfinden, NICHT in der Visualierung. Die Visualierung malt nur, ist aber ansonsten "dumm".


## Organism design
I would like to design a simulated organism that learns to survive in a simulated environment without being told anything about the environment. 

The organism has only very limited capabilities:
- Actions:
  - Locomotion: it knows how to move around (i.e. operate its legs). It can move back and forth and it can turn its body (like a turtle).
  - Energy intake: it knows how to eat
  - Communication: it can send and receive messages into the immediate surroundings. A protocol / language / format etc. of those messages will not be predefined.
- Sensors:
  - Visual perception: it knows how to perceive its environment (with realistic physical limitations)
  - Timer: it has a feeling of the passage of time, although only in a sense of the time passed since an event (with certain inaccuracy). It has no pre-defined concept of an absolute time metric.

The internal state of the simulated organism will include the following variables:
* internal body state: 
  * energy level
  * overall assessment of the situation (am I in danger? is this a pleasant situation?)
* knowledge store (generic memory function)
* utility / objective function: what are needs and preferences of the simulated organism

Importantly, the organism does not know its absolute world coordinates or its absolute heading; it does not have GPS nor does it have a compass. If it wants to navigate, it has to rely on its senses and its memory.

Perception:
- the organism can process a stream of incoming stimuli
- those stimuli are created by sensory cells located at dedicated spots on the organism. If a sensory cell fires, the brain then receives the message; the processing of the message depends to the type of stimulus and the learned / programmed reactions to it.


### Visual perception
The organism has a limited, symmetric field of view (e.g. 90°). All objects in its field of view are mapped to a one-dimensional retina. As the organism has a pair of eyes, the visual cortex also provides the depth information of an object. Objects are only seen as contiguous color impressions with a depth information.  


## Cognitive design - ideas
I don't want to model any other specific behavior or capability; I would like to let it develop those capabilities by itself. It knows how to walk, but it does not know where to go. It knows how to eat, but it does not know what is good and bad nutrition. It has a sense of direction, but it does not know any compass, cardinal points, degree of rotation or any other abstraction. It will only orient itself based on its perception. It knows how to sense the environment, but it has no given interpretation of the data (it cannot see / recognize).

All higher-value intellectual capabilities need to be learned. It has a generic reinforcement learning algorithm and it has function modules for specific tasks, i.e. planning, navigation, etc. The reward function models the organisms well-being and energy level.

Actually, I need a reward hierarchy - I need the actual reward and then I need rewards for actions that support the achievement of the actual reward. For example, the reward might be food, but the movement towards the food source is also rewarded.

The generic reinforcement learning algorithm is just an example - any learning algorithm is ok. It can also be some very complex function based on a highly developed neural network. The point is: these algorithms must have the same APIs so that they can be swapped out and be used interchangeably.
The idea would be to define a core set of capabilities and then equip them with their specific learning function, which may be based on some learning algorithm. For example, the organism needs to learn what commands to send to its legs to move in a certain relative direction (in the coordinate system of the organism, not some abstract given coordinate system).

The legs can receive commands that control them, so the challenge is to learn a function that receives the desired, relative direction as input and that outputs the necessary motor commands to move the organism in that direction. Whether or not it moves in the right direction depends on the perception system, which can see a desirable destination and which can also determine a comparison between the heading of the organism and the heading of the destination.

The organism does not know where it is in absolute terms; it has no built-in GPS that would supply it with world coordinates. It does not even have dead reckoning, i.e. it does not count its steps or track movements via inertial sensors. The organism can only tell its location by looking at its surrounding.

The following design principles should be followed:
- Associativity: seeing is recognizing
- Asynchrony: internal processes operate temporally independently
- Distribution: cognitive functions are executed in different centers or areas.  Cognitive functions are realized as ensembles of experts, which need to align to reach the best result. One cognitive function, but several possible implementations. Explainable models are a must.
- Parallelism: there is more than one execution unit for cognitive operations

## Behaviour
So what does the organism do in this simulated world? A few strategies come to mind (in ascending order of complexity; each strategy is extending the one below):
1. React to collisions with world boundaries, otherwise step ahead (working)
2. React to collisions with other objects (work in progress)
3. Look around and identify food sources
4. Move toward food sources

## Open questions
As my organism is a pretty simple one with pretty simple goals, the question is whether it needs to learn any higher-value intellectual capabilities at all. If you look at simple biological organisms like honey bees, they do very well without abstract reasoning or conscious cognitive abilities. 

If I just assume a simple behavioural model like e.g. SOR (https://de.wikipedia.org/wiki/Reiz-Organismus-Reaktions-Modell), it might be enough and there would be little need to learn any abstract concepts at all. The organism just needs to learn a good policy that maps the sensory stimuli to the bodily actions. 

Decision-making is entirely possible without abstract concepts and symbolic reasoning.
So the question is - how complex must the organism be? It should be complex enough to need concept formation, or else I won't learn much towards my research goal. 

## Appendix
### Ideas for later phases
World simulation:
- Day-night rhythm 
- Predators

Organism:
  - Pressure: it can sense force vectors that are applied to its body (also important for collision detection) 





