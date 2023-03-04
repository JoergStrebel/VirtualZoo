# How does a computer program develop an animal-like sense of situation in the world?

## The conditions of the living
How can a computer program ever understand the world if it does not understand the human condition? How can it develop the so-called common sense that humans and animals naturally possess?
The goal is not to model the rational thought process of animals (as a lot of the symbolic AI crowd is doing), but to model System 1, the emotional mode of thinking in humans. (System 1 is a concept of D. Kahnemann, see https://en.wikipedia.org/wiki/Thinking,_Fast_and_Slow)

I put forward the hypothesis that a simulation of System 1 can most easily be achieved by simulating embodiment and situation of the computer program in the world.

The Awareness of 

* present time, time intervals, past and future; naive understanding of time
* space and location: 
  * where  am I? how is my body located to the rest of the world? 
  * orientation, pose (standing, sitting etc. )
  * Inside vs. outside
  * perception of environment and weather
  * perception of noise and sound
* body state and feedback: 
  * energy level, 
  * simple vegetative states (asleep, awake), 
  * emotional states (happy, aggressive,...)
  *  blood circulation - blood pressure
  *  temperature - feeling hot or cold
* utility / objective function: what are needs and preferences.
 
The above determinants are axioms in the reasoning system of the computer program - these dimensions must be considered as given (even though their particular values may change).

Please note that this computer program does not necessarily be highly intelligent - the embodiment is a necessary concept independent of rational, symbolic thought usually associated with intelligence.

## Misconceptions of AI 
General intelligence cannot be based on language; it must be based on a symbol hypothesis, that in turn relies on shared experiences and perception that in turn rely on a common, shared environment. Language is the end of understanding and knowledge representation, not the beginning. 

Symbols per se only play an important role for higher modes of thinking and reasoning, but they cannot help us on the foundational level of intelligence in an organism. Symbols are the results of the brain's abstraction efforts, i.e. symbols are constructed by the brain based on the perception and knowledge (stored perception). (Models fit in the same category). In the end, we are talking about all kinds of abstract concepts, that are detached from perception (sensory input). So the big question is: how can a researcher create an AI based on perceptual knowledge and not on symbols? All of the good, old-fashioned AI (GOFAI) goes out of the window right there, as it is inherently symbol-based. 

Symbols are created as the highest form of abstracted perception. Storing raw perception data is very costly in terms of space, time and energy, so the brain takes the raw perception data and compresses them on several levels. Symbols are the highest level in this compression hierarchy and it is the job of the memory subsystem in the brain to create these symbols and link them to the more concrete perception data further down the hierarchy. Symbol creation is essentially feature extraction, abstraction and linking. Symbols are a bit like the alphabet used in a ZIP file. Using compressed, abstracted perception has many advantages for further information processing in the brain - it reduces data flow among different brain functions and improves cache efficiency. Moreover, it can be assumed that those compressed perception artifacts are the foundation of language (which is a standardized symbol system for inter-organism communication). 
That's why the brain keeps reprocessing memories, because those are based on compressed perception artifacts (and symbols in the end) and as those artifacts evolve over time with learning, the memory has to be reorganized (compacted, restructured). 

Nothing requires a organism to possess such a sophisticated knowledge management - it can simply rely on raw perception and not introduce all the optimizations described above.

Thus, AI cannot be based on logic alone which is also a misconception from an earlier stage of AI research. Logic is based on an abstract mathematical language and it has only a very weak semantic (in terms of expressiveness). So it has all kinds of issues , esp. how to map concepts / symbols to perception.

The type of Artificial Life which is based on fake genetics is also a misconception, or more like a toy, without any scientific value. Science is far away from understanding how the phenotype emerges from the genotype, so any simulation of that matter must be based on fantasy but not on reality.

Intelligence has only utility value; it helps organisms to survive in a complex and changing environment (which also includes other organisms, good and bad). Defining intelligence in abstract terms, like logic or language puzzles misses the point entirely. The GOFAI will only help us, once our simulated organisms are so complex that they need a symbol system to represent their reasoning and perception. But before, it will not help us.

## The way forward
The idea is to "grow" intelligence by placing a simulated organism in a simulated environment and let it develop more and more sophisticated behaviours to optimize its well-being. The more complex and real-world-like the environment becomes, the more intelligent the organism must become (in the sense of practical intelligence as defined above).

So far, AI research has built systems that are intelligent in a narrow domain, for a single task. If I was an engineer that wanted to build an IT system, that's the right approach. If I want to build a generally-intelligent organism, that approach will probably not succeed.

On this way, the organism needs to solve numerous challenges like navigating the world, finding food, locating and avoid dangers etc. All these tasks happen under constraints, like available energy, knowledge, perception, environment. So, to build such an organism, we need all kinds of clever algorithms, but they all serve a unifying goal and a purpose. 

### Research approach
I am to build a virtual environment in which I can place various organisms that have the ability to explore, learn and develop.

### Main ideas

I would like to design a simulated organism that learns to survive in a simulated environment without being told anything about the environment. The organism has only very limited abilities , basically it knows how to operate its legs and it knows how to eat and it knows how to perceive its environment. 

I don't want to model any specific behavior or capability; I would like to let it develop those capabilities by itself. It knows how to walk, but it does not know where to go. It knows how to eat, but it does not know what is good and bad nutrition. It has a sense of direction, but it does not know any compass, cardinal points, degree of rotation or any other abstraction. It will only orient itself based on its perception. It knows how to sense the environment, but it has no given interpretation of the data (it cannot see / recognize).

All higher-value intellectual capabilities need to be learned. It has a generic reinforcement learning algorithm and it has function modules for specific tasks, i.e. planning, navigation, etc. The reward function models the organisms well-being and energy level.

Actually, I need a reward hierarchy - I need the actual reward and then I need rewards for actions that support the achievement of the actual reward. For example, the reward might be food, but the movement towards the food source is also rewarded.

The generic reinforcement learning algorithm is just an example - any learning algorithm is ok.  Actually, it does not even have to be a learning algorithm, it can also be a fixed function. But it can also be some very complex function based on a highly developed neural network. The point is: these algorithms must have the same APIs so that they can be swapped out and be used interchangeably.
The idea would be to define a core set of function and then equip them with their specific function, which may be based on some learning algorithm. For example, the organism needs to learn what commands to send to its legs to move in a certain relative direction (in the coordinate system of the organism, not some abstract given coordinate system).

The legs can receive commands that control them, so the challenge is to learn a function that receives the desired, relative direction as input and that outputs the necessary motor commands to move the organism in that direction. Whether or not it moves in the right direction depends on the perception system, which can see a desirable destination and which can also determine a comparison between the heading of the organism and the heading of the destination.

The organism does not know where it is in absolute term; it has no built-in GPS that would supply it with world coordinates. It does not even have dead reckoning, i.e. it does not count its steps or track movements via inertial sensors. The organism can only tell its location by looking at its surrounding. 

The brain of a complex organism does not only speak one language - the natural language is only the tip of the iceberg, and its purpose is to communicate on a whole-organism level with other organisms. The brain speaks languages on every level - very low-levels ones for muscle control (like device drivers), higher-levels ones for e.g. memory control.

### The simulated world (environment)
The world is a 2D environment with a rectangular grid structure for internal computations (the grid coordinates are not revealed to the organism). The world is a plain, that consists of ground and small patches of edible food, which are visible to the organism.

A lot of needed concepts are still TODO.

## Conclusion
Modern large language models (e.g. ChatGPT) have a very good command of natural language, but they are only grounded in reality as much as their symbolic (textual) input data is grounded there. For example, the data basis of ChatGPT is based on GPT3 which was trained based on data available in 2021. So ChatGPT as a chatbot has no sense of the current realities.

In my opinion, a different approach is needed for an AI that is truly embedded in our human reality. As our engineering knowledge is not sophisticated enough to directly program it, our best hope is to expose a generic organism to the world and hope that it learns to survive there, and thereby becoming smart.




