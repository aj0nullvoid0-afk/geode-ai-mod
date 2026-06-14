# Geometry Dash AI Learner

## Overview

Welcome to the Geometry Dash AI Learner mod! This innovative mod brings artificial intelligence to Geometry Dash, allowing an AI agent to learn and master levels through evolutionary algorithms.

## What is NEAT?

NEAT (NeuroEvolution of Augmenting Topologies) is a genetic algorithm that evolves neural networks. Unlike traditional machine learning approaches that require pre-defined network architectures, NEAT evolves both the weights and the structure of neural networks over generations. This makes it particularly well-suited for game AI, where the optimal strategy is often unknown.

## How Does It Work?

1. **Population**: The mod creates a population of AI agents (neural networks), each with a random initial structure.
2. **Evaluation**: Each agent is tested on a Geometry Dash level. The further it progresses and the longer it survives, the higher its fitness score.
3. **Selection**: Agents with higher fitness scores are selected for breeding.
4. **Breeding**: Selected agents produce offspring with slight mutations, creating the next generation.
5. **Evolution**: Over many generations, the population evolves to develop increasingly sophisticated strategies for playing the game.

## Features

- **Real-time Evolution**: Watch the AI improve in real-time as it learns to navigate obstacles.
- **Grid-based Vision**: The AI perceives the game world through a 7x7 (or configurable) grid, similar to how a human player might focus on nearby threats.
- **Configurable Parameters**: Adjust population size, vision grid size, and fitness weights to customize the learning process.
- **Statistics**: Track generation progress, average fitness, and best fitness scores.

## Getting Started

1. Install the mod from the Geode mod menu.
2. Select a Geometry Dash level.
3. Enable the AI training from the mod menu.
4. Observe as the AI learns and improves!

## Tips for Best Results

- **Start with simpler levels**: Easier levels allow the AI to learn faster and achieve higher fitness scores.
- **Adjust population size**: Larger populations explore more solutions but take longer to evaluate. Smaller populations are faster but may converge prematurely.
- **Monitor statistics**: Use the displayed statistics to gauge the AI's progress and adjust settings as needed.

## Technical Details

The mod is implemented in C++ using the Geode SDK, which provides hooks into Geometry Dash's game engine. The NEAT algorithm is implemented as a lightweight, header-only library, making it easy to integrate and modify.

## Known Limitations

- The AI currently only controls the jump action. Future versions may support additional actions.
- Vision is limited to a grid-based representation. More sophisticated perception systems could improve performance.
- The AI is trained on a single level at a time. Training on multiple levels simultaneously is a future enhancement.

## Future Enhancements

- Multi-action control (e.g., changing game modes).
- Improved vision system with object type and velocity information.
- Neural network visualization.
- Level generation and testing on procedurally generated levels.
- Transfer learning between levels.

## Feedback and Contributions

We welcome feedback, bug reports, and contributions! Please visit the [GitHub repository](https://github.com/manus-ai/geode-ai-mod) to report issues or contribute to the project.

---

**Enjoy watching the AI learn and master Geometry Dash!**
