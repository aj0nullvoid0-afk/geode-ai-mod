# Development Guide

This document provides detailed information for developers who want to understand, modify, or extend the Geometry Dash AI Learner mod.

## Project Structure

```
geode-ai-mod/
├── src/
│   └── main.cpp                 # Entry point and Geode hooks
├── include/
│   ├── neat.hpp                 # NEAT algorithm implementation
│   ├── vision_system.hpp        # Vision system for AI perception
│   └── ai_controller.hpp        # Main AI controller
├── mod.json                     # Mod metadata and configuration
├── CMakeLists.txt               # Build configuration
├── README.md                    # User documentation
├── about.md                     # In-game mod description
├── LICENSE                      # MIT License
└── DEVELOPMENT.md               # This file
```

## Core Components

### 1. NEAT Algorithm (`include/neat.hpp`)

The NEAT algorithm is implemented as a lightweight, header-only library. Key classes:

- **Neuron**: Represents a single neuron with activation, bias, and ID.
- **Connection**: Represents a synapse between two neurons with weight and enabled status.
- **Genome**: Represents a complete neural network with neurons and connections.
- **Population**: Manages a population of genomes and handles evolution.

#### Key Methods

- `Genome::evaluate(inputs)`: Evaluates the neural network with given inputs.
- `Genome::mutateWeights()`: Mutates connection weights.
- `Genome::mutateBiases()`: Mutates neuron biases.
- `Population::naturalSelection()`: Performs selection and breeding.

### 2. Vision System (`include/vision_system.hpp`)

The vision system provides a grid-based representation of the game world:

- **Grid Size**: Configurable (default 7x7).
- **Cell Values**:
  - `0.0`: Empty space
  - `1.0`: Solid block
  - `-1.0`: Hazard (spike, saw, etc.)
  - `0.5`: Jumpable platform
- **Additional Inputs**: Player Y-velocity and upside-down status.

#### Key Methods

- `getVision(playLayer)`: Returns a vector of vision inputs.
- `checkCellContent()`: Determines what's in a specific cell.
- `isHazard()`, `isSolid()`, `isJumpable()`: Object type checks.

### 3. AI Controller (`include/ai_controller.hpp`)

The AI controller manages the population and controls the AI's interaction with the game:

- **Population Management**: Maintains a population of genomes and tracks generations.
- **Fitness Evaluation**: Calculates fitness based on level progress and time alive.
- **Action Execution**: Translates neural network output to game actions.

#### Key Methods

- `update(dt)`: Called every frame to update AI state and execute actions.
- `onLevelReset()`: Called when the level resets (current genome dies).
- `executeAction()`: Translates neural network output to jump commands.

### 4. Main Entry Point (`src/main.cpp`)

The main entry point sets up Geode hooks and initializes the AI controller:

- **PlayLayerHook**: Hooks into `PlayLayer::init()`, `update()`, and `resetLevel()`.
- **Global AI Controller**: Maintains a reference to the current AI controller.

## Building the Mod

### Prerequisites

- CMake 3.21+
- C++20 compiler
- Geode SDK

### Build Commands

```bash
cd geode-ai-mod
mkdir build
cd build
cmake ..
cmake --build . --config RelWithDebInfo
```

The compiled `.geode` file will be in the `build` directory.

## Extending the Mod

### Adding More Output Actions

To allow the AI to control more actions (e.g., changing game modes):

1. Modify `AIController::executeAction()` to handle multiple outputs.
2. Update the neural network output layer size in `AIController` constructor.
3. Implement the corresponding game actions using Geode hooks.

### Improving the Vision System

To enhance the vision system with more information:

1. Add new features to `VisionSystem::getVision()`.
2. Update `getInputCount()` to reflect the new input size.
3. Modify `checkCellContent()` to extract additional information from game objects.

### Tuning NEAT Parameters

Key parameters in `neat.hpp` that can be tuned:

- **Mutation Rate**: Probability of mutation in `mutateWeights()` and `mutateBiases()`.
- **Mutation Power**: Magnitude of mutations.
- **Selection Pressure**: Percentage of genomes kept in `naturalSelection()`.
- **Weight Bounds**: Clamp values in `mutateWeights()`.

### Adding Visualization

To visualize the neural network or AI state:

1. Create a new UI layer using Geode's UI system.
2. Hook into `PlayLayer::draw()` to render visualizations.
3. Display network topology, activations, or vision grid.

## Testing

### Manual Testing

1. Build the mod.
2. Install it in Geometry Dash.
3. Select a level and enable AI training.
4. Observe the AI's behavior and fitness progression.

### Debugging

- Use `log::info()` and `log::debug()` for logging.
- Check the Geode console for error messages.
- Adjust vision grid size and fitness weights to observe effects.

## Common Issues and Solutions

### Issue: AI doesn't seem to be learning

**Solution**: 
- Check that the fitness function is correctly calculating progress.
- Verify that the vision system is providing meaningful input.
- Increase population size or adjust mutation rates.

### Issue: Mod crashes on startup

**Solution**:
- Ensure Geode SDK is correctly installed.
- Check for null pointer dereferences in hooks.
- Verify that all Geode headers are correctly included.

### Issue: AI only jumps or never jumps

**Solution**:
- Check the output threshold in `executeAction()`.
- Verify that the neural network is being evaluated correctly.
- Increase the initial connection weights or biases.

## Performance Considerations

- **Population Size**: Larger populations = better exploration but slower evaluation.
- **Vision Grid Size**: Larger grids = more input features but higher computational cost.
- **Mutation Rates**: Higher rates = more exploration but less convergence.

## References

- Geode SDK: https://docs.geode-sdk.org/
- NEAT Algorithm: https://en.wikipedia.org/wiki/Neuroevolution_of_augmenting_topologies
- C++ Standard: https://en.cppreference.com/

## Contributing

When contributing, please:

1. Follow the existing code style.
2. Add comments for complex logic.
3. Test changes thoroughly.
4. Update documentation as needed.

---

**Happy developing!**
