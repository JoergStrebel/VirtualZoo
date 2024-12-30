# How does a computer program learn concepts of the physical world?

## The conditions of the living
How can a computer program ever understand the world if it does not understand the human condition? How can it develop the so-called common sense that humans and animals naturally possess?
The goal is not to model the rational thought process of animals (as a lot of the symbolic AI crowd is doing), but to model System 1, the emotional mode of thinking in humans. (System 1 is a concept of D. Kahnemann, see https://en.wikipedia.org/wiki/Thinking,_Fast_and_Slow)

I put forward the hypothesis that a simulation of System 1 can most easily be achieved by simulating embodiment and situation of the computer program in the world.

This embodiment creates the awareness of the following concepts:

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
  * blood circulation - blood pressure
  * temperature - feeling hot or cold
* utility / objective function: what are needs and preferences.
 
Please note that this computer program does not necessarily be highly intelligent - the embodiment is a necessary concept independent of rational, symbolic thought usually associated with intelligence.


## Misconceptions of AI 
General intelligence cannot be based on language; it must be based on a symbol hypothesis, that in turn relies on shared experiences and perception that in turn rely on a common, shared environment. Language is the end of understanding and knowledge representation, not the beginning. 

Symbols per se only play an important role for higher modes of thinking and reasoning, but they cannot help us on the foundational level of intelligence in an organism. Symbols are the results of the brain's abstraction efforts, i.e. symbols are constructed by the brain based on the perception and knowledge (stored perception). (Models fit in the same category). In the end, we are talking about all kinds of abstract concepts, that are detached from perception (sensory input). So the big question is: how can a researcher create an AI based on perceptual knowledge and not on symbols? All of the good, old-fashioned AI (GOFAI) goes out of the window right there, as it is inherently symbol-based. 

Symbols are created as the highest form of abstracted perception. Storing raw perception data is very costly in terms of space, time and energy, so the brain takes the raw perception data and compresses them on several levels. Symbols are the highest level in this compression hierarchy and it is the job of the memory subsystem in the brain to create these symbols and link them to the more concrete perception data further down the hierarchy. Symbol creation is essentially feature extraction, abstraction and linking. Symbols are a bit like the alphabet used in a ZIP file. Using compressed, abstracted perception has many advantages for further information processing in the brain - it reduces data flow among different brain functions and improves cache efficiency. Moreover, it can be assumed that those compressed perception artifacts are the foundation of language (which is a standardized symbol system for inter-organism communication). 
That's why the brain keeps reprocessing memories, because those are based on compressed perception artifacts (and symbols in the end) and as those artifacts evolve over time with learning, the memory has to be reorganized (compacted, restructured). 

Nothing requires a organism to possess such a sophisticated knowledge management - it can simply rely on raw perception and not introduce all the optimizations described above.

Thus, AI cannot be based on logic alone which is also a misconception from an earlier stage of AI research. Logic is based on an abstract mathematical language and it has only a very weak semantic (in terms of expressiveness; if a strong expressiveness is desired, the computability of the logic becomes intractable). So it has all kinds of issues , esp. how to map concepts / symbols to perception.

The type of Artificial Life which is based on fake genetics is also a misconception, or more like a toy, without any scientific value. Science is far away from understanding how the phenotype emerges from the genotype, so any simulation of that matter must be based on fantasy but not on reality.

General intelligence has first and foremost a utility value to the organism; it helps organisms to survive in a complex and changing environment (which also includes other organisms, good and bad). Defining intelligence in abstract terms, like crystalline intelligence needed for logic or language puzzles, misses the point entirely. The (symbolic) GOFAI will only help us, once our simulated organisms are so complex that they need a symbol system to represent their reasoning and perception. But before, it will not help us.

## The way forward
The idea is to "grow" intelligence by placing a simulated organism in a simulated environment and let it develop more and more sophisticated behaviours to optimize its well-being. The more complex and real-world-like the environment becomes, the more intelligent the organism must become (in the sense of practical intelligence as defined above).

So far, AI research has built systems that are intelligent in a narrow domain, for a single task. If I was an engineer that wanted to build an IT system, that's the right approach. If I want to build a generally-intelligent organism, that approach will probably not succeed.

On this way, the organism needs to solve numerous challenges like navigating the world, finding food, recognizing and avoid dangers etc. All these tasks happen under constraints, like available energy, knowledge, perception, environment. So, to build such an organism, we need all kinds of clever algorithms, but they all serve a unifying goal and a purpose. 

### Research approach and design
I am to build a virtual environment in which I can place various organisms that have the ability to explore, learn and develop. 

The research questions are: 
- how can a computer program discover and learn concepts of the physical world on its own terms (i.e. without given symbols)?
- how can we map the internal knowledge representation / conceptualization of the organism to elements of the simulated environment (i.e. how can we understand it)?
- how can we rate the abstraction level of the internal knowledge representation?
- what kind of parametrization and pre-defined internal state is needed a-priori for a later successful mapping of internal concepts and external environment?

Hypotheses:
- the simulated organism develops various conceptualizations consistent with the entities in the environment
- the learned concepts are commensurate with the complexity of the environment

Assumptions
- all learning must be data-driven; the simulated organism starts out with as little internal state and capabilities as possible.
- all learning will be based on feedback and will be online (= reinforcement learning).
- all learned models must be human-inspectable and white-box models. The actions of the agent must be explainable in terms of its learned models.
- there will be no limit to the complexity of its internal representations, i. e. the organism can keep on accumulating perceptual data and can build ever more complex abstractions.
- the lifetime of one organism is not limited, hence there will be no genetics and no simulation of a biological evolution.

The research approach is based on well-designed, quantitative experiments that are conducted in a simulated environment with clear starting conditions; they subject the simulated organism to a specific environment in which it can freely make decisions (see http://www.janrecker.com/quantitative-research-in-information-systems/). In this setting, the environment acts as a parameter to the experiments, the conceptualization of the organism acts as a dependent variable and the decisions and actions of the organism as an independent variable.

The research approach is a phased one: both the complexity of the starting conditions and the internal complexity of the agent are increased step-by-step. In a first phase, a simple agent will try to survive in a simple environment. In a later phase, a more complex agent will be put in a more complex environment. (Organism complexity is here relating to more complex sensory input and more complex poses and movements.)

## Conclusion
Modern large language models (e.g. ChatGPT) have a very good command of natural language, but they are only grounded in reality as much as their symbolic (textual) input data is grounded there. 

In my opinion, a different approach is needed for an AI that is truly embedded in our human reality. As our engineering knowledge is not sophisticated enough to directly program it, our best hope is to expose a generic organism  with learning capabilities to the world and hope that it learns to survive there, and thereby becoming smart (i.e. it will develop concepts that can be mapped to concepts used by humans and it will make use of these concepts to decide in its best interest).

