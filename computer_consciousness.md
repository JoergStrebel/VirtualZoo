# How does a computer program learn concepts of the physical world?

## The conditions of the living
How can a computer program ever understand the world if it does not understand the human condition? How can it develop the so-called common sense that humans and animals naturally possess?
The goal is not to model the rational, deliberative thought process of animals (as much of the symbolic AI tradition has done), but to model System 1, the fast, automatic, intuitive mode of thinking — pattern recognition, perceptual categorization, and habitual action — as opposed to System 2's slow, deliberative reasoning. (System 1 is a concept of D. Kahneman, see https://en.wikipedia.org/wiki/Thinking,_Fast_and_Slow.)

I put forward the hypothesis that a simulation of System 1 can most easily be achieved by simulating embodiment and situation of the computer program in the world.

This embodiment creates the awareness of the following concepts:

* present time, time intervals, past and future; naive understanding of time
* space and location: 
  * where am I? how is my body located to the rest of the world? 
  * orientation, pose (standing, sitting etc.)
  * Inside vs. outside
  * perception of environment and weather
  * perception of noise and sound
* body state and feedback: 
  * energy level, 
  * simple vegetative states (asleep, awake), 
  * affective states (positive/negative valence, arousal)
  * blood circulation - blood pressure
  * temperature - feeling hot or cold
* utility / objective function: what are needs and preferences.
 
Note that this computer program need not be highly intelligent in the deliberative sense — embodiment is a necessary foundation independent of the rational, symbolic thought usually associated with intelligence.


## Misconceptions of AI 
General intelligence cannot be based on language; it must rest on a symbol system whose primitive terms are tied, ultimately, to shared experiences and perception in a common environment. Language is the end of understanding and knowledge representation, not the beginning. 

Symbols play an important role for higher modes of thinking and reasoning, but they cannot do the foundational work alone. This is the essence of Stevan Harnad's *symbol grounding problem* (Harnad, 1990): in a purely symbolic system, the meaning of a symbol is given only by other symbols, producing an unbroken circularity (a "merry-go-round" through the dictionary). Such a system's semantics is parasitic on the meanings in the heads of its designers, not intrinsic to the system itself. So the central design question becomes: how can a researcher build an AI whose primitive terms are grounded in its own perceptual and sensorimotor history, rather than supplied by the modeler?

Perception is the foundation, but the relation between perception and symbols is not direct. Raw perceptual data is high-dimensional and costly to store and process; the brain learns invariants and category boundaries from sensorimotor experience, and only on top of those *categorical representations* does anything symbol-like become useful. Symbols, on this view, are composable tokens bound to categorical representations that are in turn anchored in iconic (sensory) projections. Memory is reorganized over time as these categorical representations evolve, which is why the brain reprocesses memories.

Following Harnad's hybrid proposal, this project adopts a three-layer architecture:

1. **Iconic representations** — analogs of the sensory projection (in our case, the retina and depth buffer). The agent cannot rewrite this layer; it is fixed by the transducers.
2. **Categorical representations** — learned invariants that license category membership decisions ("edible vs. inedible", "obstacle vs. passage") and that pay rent in the utility function: a category is real to the agent only if acting on it changes outcomes.
3. **Symbolic representations** — composable tokens whose primitive terms are bound to categorical representations. New symbols are coined only by composition over existing symbols or by binding to fresh categoricals. No symbol may exist whose definition cycles only through other symbols; every symbol must trace a path back to a transducer event. This is the operational test for grounding.

Logic-only AI is therefore a misconception not because logic has weak semantics — Tarskian model theory gives logic perfectly precise semantics — but because logic is *ungrounded*: the interpretation function that maps formulas to a model is supplied externally by the modeler. Logic gives compositionality and inference, both of which we want at the symbolic layer, but it does not by itself solve the grounding problem.

Recent neurosymbolic and object-centric world-model research (e.g., Mao et al.'s Neuro-Symbolic Concept Learner, DreamCoder, and slot-attention-style perceptual front-ends) is directly relevant here and partly addresses the integration of layers (1)–(3); this project draws on that line of work rather than dismissing symbolic methods wholesale.

The strand of Artificial Life based on invented "genetics" remains, in my view, of limited scientific value for the present question. Even for real biological genetics the link between genotype and the phenotype that produces intelligent behaviour is poorly understood; a simulation built on fabricated genetics has no obvious means of validation against reality. (This is a methodological objection to using fake genetics to ground claims about intelligence — not a wholesale dismissal of evolutionary computation, which has its own legitimate uses for novelty search and open-ended dynamics.)

General intelligence has, first and foremost, a utility value to the organism; it helps organisms survive in a complex and changing environment (which also includes other organisms, friendly and hostile). Defining intelligence in abstract terms — crystallised intelligence as needed for logic or language puzzles — misses the point. Symbolic methods will earn their keep once our simulated organisms are complex enough to need a compositional symbol system over their categorical representations; before that, they cannot do the foundational work.

## The way forward
The idea is to "grow" intelligence by placing a simulated organism in a simulated environment and letting it develop more and more sophisticated behaviours to optimize its well-being. The more complex and real-world-like the environment becomes, the more intelligent the organism must become (in the sense of practical intelligence as defined above).

So far, AI research has built systems that are intelligent in a narrow domain, for a single task. If the goal is an IT system, that approach is right. If the goal is a generally-intelligent organism, it will probably not succeed.

Along the way the organism must solve numerous challenges: navigating the world, finding food, recognizing and avoiding dangers, and so on. All these tasks happen under constraints — available energy, knowledge, perception, environment. Building such an organism therefore requires an array of algorithms, but they all serve a unifying goal and purpose.

### Research approach and design
I aim to build a virtual environment in which I can place various organisms that have the ability to explore, learn and develop. 

The research questions are: 
- how can a computer program discover and learn concepts of the physical world on its own terms (i.e., without symbols supplied by the modeler)?
- how can we map the internal knowledge representation of the organism to elements of the simulated environment (i.e., how can we understand it)?
- how can we rate the abstraction level of the internal knowledge representation?
- which a-priori priors and pre-defined internal state are required for grounding to succeed, and how minimal can they be made without preventing learning?

Hypotheses:
- the simulated organism develops categorical representations that align with the action-relevant entities in the environment;
- the learned representations grow in complexity commensurate with the complexity of the environment;
- symbols coined by the agent over those categoricals remain grounded under the closure check defined in the architecture above.

Assumptions
- learning is primarily data-driven, but the organism is *not* a tabula rasa. It is equipped with a minimal but non-empty set of priors: fixed sensory transducers, a body schema, a utility function, and inductive biases for space, objects, and time. These priors are made explicit so that their contribution can be assessed.
- learning is feedback-driven and online (reinforcement learning). The reward signal is tied to a real survival/failure cost: organisms can deplete energy and terminate, providing the selection gradient that disciplines what counts as a useful concept.
- learned representations need not be intrinsically white-box, but they must be *post-hoc interpretable*: each categorical representation must be inspectable by exhibiting the iconic (sensory) inputs and invariants that activate it, and each symbol must be auditable for grounding (no symbol whose definition cycles only through other symbols).
- there is no a-priori limit on the complexity of internal representations; the organism can keep accumulating perceptual data and building higher-level abstractions.
- the lifetime of an individual organism is bounded only by failure (energy depletion, fatal collision, etc.); there is no biological evolution and no invented genetics.

The research approach is based on well-designed, quantitative experiments conducted in a simulated environment with clear starting conditions; the organism is placed in a specific environment in which it may freely act according to its learned policy (see http://www.janrecker.com/quantitative-research-in-information-systems/). In this setting, the environment is the manipulated variable (the experimental parameter); the organism's emergent conceptualization and its behaviour (decisions and actions) are both dependent variables observed by the experimenter. The agent's "independence" refers to its operational autonomy under its RL policy, not to the statistical role of its actions in the experimental design.

The approach is phased: both the complexity of the starting conditions and the internal complexity of the agent are increased step-by-step. In a first phase, a simple agent will try to survive in a simple environment. In a later phase, a more complex agent will be placed in a more complex environment. (Organism complexity here refers to richer sensory input and a richer repertoire of poses and movements.)

### How categorical representations are learned
The categorical layer is the load-bearing component of the architecture: iconic inputs are fixed by the transducers and symbols are defined over categoricals, so the entire grounding chain stands or falls on how categoricals are formed. The project commits to a concrete, evaluable mechanism rather than leaving this layer unspecified.

The categorical layer is implemented as a **prototype codebook over short sensorimotor trajectories**, trained online under three combined pressures:

1. **Self-supervised perceptual structure** — a contrastive objective treats temporally adjacent sensorimotor states (a window of iconic frames plus the agent's own motor state) as positive pairs, and randomly sampled distant states as negatives. This forces the embedding to capture invariants that persist across short action sequences (a chair seen from a slightly different angle is "the same thing"), which is the standard sensorimotor-invariance argument for how categorical perception is acquired.
2. **Discrete codebook (VQ-style)** — embeddings are quantised to a finite, growing set of prototypes. Each prototype *is* a candidate categorical representation. Discreteness is what makes the layer auditable: there is a finite list of categories, each with a stored set of activating exemplars (iconic inputs nearest to the prototype). New prototypes are spawned when no existing prototype is within a quantisation threshold; rarely-used prototypes decay.
3. **Utility-weighted refinement (the "pay rent" pressure)** — the contrastive loss is reweighted by the agent's reward prediction error. Trajectory pairs that straddle a reward-relevant transition (e.g., approach-then-collision, search-then-find-food) contribute more to prototype updates than reward-neutral pairs. Prototypes that fail to discriminate reward-relevant outcomes are pruned or merged. This is what stops the codebook from being a generic autoencoder — categories must matter to behaviour or they are forgotten.

Each prototype is automatically annotated for post-hoc interpretation by storing its top-*k* activating iconic exemplars, its average reward signature, and the actions taken by the agent when the prototype was active. This makes the closure test in the next section mechanically checkable rather than aspirational.

This design is deliberately conservative: prototype-plus-contrastive methods are well-understood, the discreteness gives auditability for free, and the utility weighting is the one substantive novelty that ties the mechanism to the project's grounding commitments. Alternative mechanisms (slot-attention front-ends for object-centric categoricals, successor-feature representations for reward-aligned categoricals) are compatible with the layer interface and may be evaluated as variants once the baseline is in place.

#### v1 starter implementation
The full mechanism above is the *target* architecture. For an initial implementation it is preferable to start with the simplest variant that could plausibly pass the closure and behavioural-relevance tests, and only escalate if the simple version visibly fails. A reasonable v1:

- **Representation**: a fixed-length feature vector built directly from the iconic layer — concatenated retina pixels, depth values, and proprioceptive state (heading, energy) over a short window of recent ticks. No learned embedding initially.
- **Categorisation**: online k-means (or a streaming variant such as sequential leader clustering) over those feature vectors. Each cluster centre is a candidate categorical representation. New centres are spawned when a sample exceeds a distance threshold from all existing centres; centres unused for a long time decay.
- **Utility weighting**: each sample's contribution to its centre's update is weighted by the absolute reward prediction error at that tick (or, more simply, by whether the tick is within a short window of a reward event). This is the minimum viable form of the "pay rent" pressure.
- **Inspection**: each centre stores its top-*k* nearest iconic exemplars, the reward statistics of states assigned to it, and a histogram of actions taken while it was active.

This v1 has no neural network, no contrastive training, and no VQ codebook gradient — it is implementable in straight C++ alongside the existing simulator. If the closure test and a basic ablation already produce sensible categories under v1, the more elaborate mechanism is unnecessary. If v1 fails in specific, diagnosable ways (e.g., centres collapse to lighting differences rather than object identity), those failure modes justify escalating to the contrastive embedding or VQ codebook in the target design.

### What counts as evidence of grounding?
To keep the hypotheses falsifiable, the project commits in advance to operational tests:

- **Closure test**: every symbol the agent uses must be reducible — by tracing its definitional chain — to at least one categorical representation, which itself activates on a specifiable subset of iconic inputs. A symbol that fails this trace is ungrounded.
- **Behavioural relevance**: a categorical representation counts as "real" to the agent only if ablating or perturbing it measurably degrades performance on tasks where the corresponding environmental distinction matters.
- **Cross-environment transfer**: grounded categoricals should support better-than-chance behaviour when the agent is moved to environments that share the relevant invariants but differ in surface features.

## Conclusion
Modern large language models (e.g., ChatGPT) have a very good command of natural language, but they are grounded in reality only as much as their textual input data is grounded there — which is to say, parasitically, through the humans who produced the text.

A different approach is needed for an AI that is genuinely embedded in our shared reality. Since our engineering knowledge is not sophisticated enough to program such a system directly, the best available strategy is to expose a generic organism with learning capabilities, and a minimal set of explicit priors, to a simulated world and have it learn to survive there. If the architecture is right, the concepts it develops will be grounded by construction — bound, through categorical representations, to its own sensorimotor history — and only therefore mappable to concepts used by humans.
