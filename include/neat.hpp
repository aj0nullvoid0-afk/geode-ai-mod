#pragma once

#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <memory>

namespace neat {

// ============================================================================
// Lightweight NEAT Implementation
// ============================================================================

class Neuron {
public:
    double activation = 0.0;
    double bias = 0.0;
    int id = 0;
    bool isInput = false;

    Neuron(int id, bool isInput = false) : id(id), isInput(isInput) {}
};

class Connection {
public:
    int fromId;
    int toId;
    double weight;
    bool enabled;
    int innovationNumber;

    Connection(int from, int to, double w, int innovation)
        : fromId(from), toId(to), weight(w), enabled(true), innovationNumber(innovation) {}
};

class Genome {
public:
    std::vector<Neuron> neurons;
    std::vector<Connection> connections;
    double fitness = 0.0;
    int generation = 0;

    Genome() = default;

    Genome(int inputCount, int outputCount) {
        // Create input neurons
        for (int i = 0; i < inputCount; ++i) {
            neurons.emplace_back(i, true);
        }
        // Create output neurons
        for (int i = 0; i < outputCount; ++i) {
            neurons.emplace_back(inputCount + i, false);
        }
    }

    std::vector<double> evaluate(const std::vector<double>& inputs) {
        if (inputs.size() != countInputs()) {
            throw std::runtime_error("Input size mismatch");
        }

        // Set input neuron activations
        for (size_t i = 0; i < inputs.size(); ++i) {
            neurons[i].activation = inputs[i];
        }

        // Evaluate connections (simple feedforward)
        for (const auto& conn : connections) {
            if (!conn.enabled) continue;

            auto it = std::find_if(neurons.begin(), neurons.end(),
                [&](const Neuron& n) { return n.id == conn.fromId; });
            if (it == neurons.end()) continue;

            auto outIt = std::find_if(neurons.begin(), neurons.end(),
                [&](const Neuron& n) { return n.id == conn.toId; });
            if (outIt == neurons.end()) continue;

            double signal = it->activation * conn.weight;
            outIt->activation += signal;
        }

        // Apply activation function to output neurons
        std::vector<double> outputs;
        int inputCount = countInputs();
        for (size_t i = inputCount; i < neurons.size(); ++i) {
            neurons[i].activation = tanh(neurons[i].activation + neurons[i].bias);
            outputs.push_back(neurons[i].activation);
        }

        return outputs;
    }

    int countInputs() const {
        int count = 0;
        for (const auto& n : neurons) {
            if (n.isInput) count++;
        }
        return count;
    }

    int countOutputs() const {
        return neurons.size() - countInputs();
    }

    void mutateWeights(double mutationRate, double mutationPower) {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        std::normal_distribution<> weightDis(0.0, mutationPower);

        for (auto& conn : connections) {
            if (dis(gen) < mutationRate) {
                conn.weight += weightDis(gen);
                conn.weight = std::clamp(conn.weight, -5.0, 5.0);
            }
        }
    }

    void mutateBiases(double mutationRate, double mutationPower) {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        std::normal_distribution<> biasDis(0.0, mutationPower);

        for (auto& neuron : neurons) {
            if (!neuron.isInput && dis(gen) < mutationRate) {
                neuron.bias += biasDis(gen);
                neuron.bias = std::clamp(neuron.bias, -5.0, 5.0);
            }
        }
    }
};

class Population {
public:
    std::vector<Genome> genomes;
    int generation = 0;

    Population(int populationSize, int inputCount, int outputCount) {
        for (int i = 0; i < populationSize; ++i) {
            genomes.emplace_back(inputCount, outputCount);
        }
    }

    void evaluateFitness(std::function<double(const Genome&)> fitnessFunc) {
        for (auto& genome : genomes) {
            genome.fitness = fitnessFunc(genome);
            genome.generation = generation;
        }
    }

    void naturalSelection() {
        // Sort by fitness
        std::sort(genomes.begin(), genomes.end(),
            [](const Genome& a, const Genome& b) {
                return a.fitness > b.fitness;
            });

        // Keep top 50% and breed to fill population
        int keepCount = genomes.size() / 2;
        std::vector<Genome> newGenomes(genomes.begin(), genomes.begin() + keepCount);

        while (newGenomes.size() < genomes.size()) {
            static std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<> dis(0, keepCount - 1);

            Genome child = newGenomes[dis(gen)];
            child.mutateWeights(0.8, 0.5);
            child.mutateBiases(0.5, 0.3);
            newGenomes.push_back(child);
        }

        genomes = newGenomes;
        generation++;
    }

    Genome& getBest() {
        return *std::max_element(genomes.begin(), genomes.end(),
            [](const Genome& a, const Genome& b) {
                return a.fitness < b.fitness;
            });
    }

    double getAverageFitness() const {
        if (genomes.empty()) return 0.0;
        double sum = 0.0;
        for (const auto& g : genomes) {
            sum += g.fitness;
        }
        return sum / genomes.size();
    }
};

} // namespace neat
