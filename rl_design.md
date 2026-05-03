# Reinforcement Learning Design

## Problem framing

The organism explores a 2D world and may discover states that are desirable only upon encounter — the reward function itself grows with experience. This violates the standard RL assumption of a fixed, pre-specified reward. The design resolves this by separating two concerns: a fixed energy-based reward signal that is always present, and a dynamic discovery mechanism that permanently extends the reward function when new rewarding states are found.

## Reward signal

**R(s, a) = ΔEnergy** is the unified reward signal.

- Every locomotion action burns a fixed calorie cost → negative reward.
- Consuming a resource (food source at a Location) yields a positive energy spike → positive reward.
- No separate shaping terms are needed; the energy budget enforces the exploration–exploitation tradeoff physically rather than through hyperparameter tuning.

Energy level is part of the state vector. A low-energy organism cannot afford long exploratory detours and should exploit known resources; a high-energy organism can afford to search. Without energy in the state, the policy cannot condition on this distinction and will behave irrationally near depletion.

## Exploration drive: prediction-error curiosity

The organism maintains a **forward model** of its visual input (the 90-pixel retina). At each timestep the forward model predicts the next retinal observation given the current observation and action. The prediction error is used as an intrinsic exploration bonus:

```
R_intrinsic(s, a) = || predicted_retina(s, a) - actual_retina(s') ||
```

High prediction error signals a novel region; low error signals familiar territory. This bonus is added to the energy-based reward during training and decays naturally as the forward model improves with experience. No explicit novelty counter or count-based term is required.

The forward model is trained online alongside the policy, using the organism's own trajectory as supervised data.

## Discovery: extending the extrinsic reward

When the organism first physically enters a previously-unseen `Location` rectangle, that location is promoted into the permanent extrinsic reward function with a fixed positive reward. This reward persists for all future visits, creating a stable attractor that the policy converges on after exploration.

This handles the discovery of genuinely novel rewarding states without changing the structure of the RL problem: at any point in time the reward function is fixed; it is only extended at discrete discovery events, after which training continues on the updated (but again fixed) reward.

## Cold-start: objects not yet visited

Two complementary mechanisms handle discovery of locations not yet within visual range.

**Visual detection bonus (primary mechanism).** The retina already delivers location-tagged depth pixels. When the organism achieves first visual contact with a new Location rectangle — i.e., at least one retinal pixel carries a depth reading attributed to a previously-unseen location index — a one-time small positive reward is granted. This is smaller than the travel cost to a known food source, but sufficient to bias the policy toward approach. It fires once per object and never again. Given the 640×640 world and the 90° FOV, the majority of the world is coverable within a small number of traversals, making this the dominant cold-start mechanism.

**Generous initial energy (fallback).** For the rare case where a Location is always behind the organism and never enters the FOV by chance, a sufficiently large initial energy reserve allows the organism to survive the random-walk phase until serendipitous visual contact occurs. Once the first detection bonus fires, the visual detection mechanism takes over. No additional mechanism is needed for a world of this scale.

## Policy

The organism learns a single policy that balances:

1. **Curiosity-driven exploration** — visiting novel regions where the forward model has high prediction error.
2. **Exploitation of known rewards** — returning to Locations already in the extrinsic reward function.
3. **Energy conservation** — avoiding unnecessary locomotion when energy is low.

All three objectives are expressed through the combined reward signal `R(s, a) = ΔEnergy + R_intrinsic(s, a)` without separate reward heads or hierarchical structure.

## State vector

| Component | Representation |
|---|---|
| Position (x, y) | Continuous, world coordinates |
| Heading | Radians, [0, 2π) |
| Energy level | Continuous scalar |
| Retina (90 × RGB + distance) | As delivered by `Organism::visual_stimulus()` |
| Pressure sensors (8) | Binary hit/no-hit per sensor |

The retina and pressure sensors give the organism full local perception. Position and heading are included to allow the policy to form a spatial map of known rewarding locations.

## Open questions

- Forward model architecture: a small MLP predicting next retina from current retina + action is the simplest starting point. A convolutional architecture over the 1D retina strip may generalize better.
- Whether to use a model-free policy (e.g. PPO) or model-based RL that explicitly builds a world map. The forward model required for curiosity is already a partial world model, so model-based methods are a natural extension.
- Discount factor γ: should reflect the organism's planning horizon. A low-energy organism effectively has a shorter horizon; making γ a function of energy level is a possible refinement.
