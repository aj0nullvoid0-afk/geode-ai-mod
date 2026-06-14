# Geometry Dash AI Learner

A Geode mod for Geometry Dash that implements an AI agent capable of learning to play levels using the NEAT (NeuroEvolution of Augmenting Topologies) algorithm.

## Features

- **NEAT Algorithm**: Evolves neural networks to learn optimal control strategies for playing Geometry Dash.
- **Vision System**: AI perceives the game world through a grid-based vision system that detects obstacles and hazards.
- **Real-time Evolution**: Watch as the AI improves over multiple generations, adapting to different level layouts.
- **Configurable Settings**: Adjust population size, vision grid size, and fitness weights through the mod menu.
- **Statistics Tracking**: Monitor generation progress, average fitness, and best fitness scores.

## Installation

1. Ensure you have Geode installed for Geometry Dash. Download from [https://geode-sdk.org/](https://geode-sdk.org/).
2. Download the latest release of this mod from the [Releases](https://github.com/manus-ai/geode-ai-mod/releases) page.
3. Place the `.geode` file in your Geometry Dash mods folder.
4. Launch Geometry Dash and enable the mod from the Geode menu.

## Building from Source

### Prerequisites

- CMake 3.21 or higher
- C++20 compatible compiler (MSVC, Clang, or GCC)
- Geode SDK installed and configured

### Build Steps

```bash
git clone https://github.com/manus-ai/geode-ai-mod.git
cd geode-ai-mod
mkdir build
cd build
cmake ..
cmake --build . --config RelWithDebInfo
```

The compiled `.geode` file will be in the `build` directory.

## Usage

1. Open Geometry Dash and select a level.
2. Press the Geode mod menu button (default: Tab key on Windows).
3. Navigate to "Geometry Dash AI Learner" and enable "Enable AI Training".
4. Watch the AI learn! The mod will display statistics such as generation number, average fitness, and best fitness.

### Configuration

The following settings can be adjusted in the mod menu:

- **Enable AI Training**: Toggle AI training on/off.
- **Population Size**: Number of AI agents per generation (default: 50).
- **Vision Grid Size**: Size of the AI's vision grid (default: 7x7).
- **Fitness Weight - Progress**: Weight for level completion in fitness calculation (default: 1.0).
- **Fitness Weight - Time Alive**: Weight for time alive in fitness calculation (default: 0.1).

## How It Works

### NEAT Algorithm

The NEAT algorithm evolves both the weights and topology of neural networks. Each "genome" (neural network) is tested on a Geometry Dash level. The more of the level it completes and the longer it survives, the higher its fitness score. Genomes with higher fitness scores are more likely to be selected for breeding, creating the next generation.

### Vision System

The AI perceives the game world through a grid-based vision system. Each cell in the grid represents a small area in the game world and contains information about:

- **Empty**: No obstacles (0.0)
- **Solid Block**: Platforms and walls (1.0)
- **Hazard**: Spikes, saws, and other deadly objects (-1.0)
- **Jumpable**: Platforms that can be jumped on (0.5)

The AI also receives information about its current vertical velocity and whether it's upside down.

### Neural Network Output

The neural network has a single output neuron. If the output exceeds a threshold (0.5), the AI executes a jump. Otherwise, it releases the jump button.

## Architecture

The mod consists of several key components:

- **main.cpp**: Entry point and Geode hooks.
- **neat.hpp**: Lightweight NEAT algorithm implementation.
- **vision_system.hpp**: Grid-based vision system for perceiving the game world.
- **ai_controller.hpp**: Main AI controller that manages the population and evolution.

## Future Enhancements

- Support for multiple output actions (e.g., changing game modes).
- Improved vision system with object type and velocity information.
- Visualization of the neural network's internal state.
- Level generation and testing on procedurally generated levels.
- Hyperparameter optimization for better AI performance.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your improvements.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## References

- Geode SDK Documentation: https://docs.geode-sdk.org/
- NEAT Algorithm: https://en.wikipedia.org/wiki/Neuroevolution_of_augmenting_topologies
- Geometry Dash: https://store.steampowered.com/app/322170/Geometry_Dash/

## Support

For issues, questions, or suggestions, please open an issue on the [GitHub repository](https://github.com/manus-ai/geode-ai-mod/issues).

---

**Developed by**: Manus AI  
**Repository**: https://github.com/manus-ai/geode-ai-mod
