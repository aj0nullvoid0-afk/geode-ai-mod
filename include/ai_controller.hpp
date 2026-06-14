#pragma once

#include <Geode/Geode.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>
#include "neat.hpp"
#include "vision_system.hpp"

using namespace geode::prelude;

class AIController {
public:
    AIController(PlayLayer* playLayer)
        : m_playLayer(playLayer),
          m_visionSystem(7),
          m_population(50, m_visionSystem.getInputCount(), 1),
          m_currentGenomeIndex(0),
          m_currentGeneration(0),
          m_timeAlive(0.0f) {}

    void update(float dt) {
        m_timeAlive += dt;

        if (!m_playLayer || !m_playLayer->m_player1) {
            return;
        }

        // Get current genome
        if (m_currentGenomeIndex >= m_population.genomes.size()) {
            // All genomes in this generation have been tested
            evaluateGeneration();
            m_population.naturalSelection();
            m_currentGenomeIndex = 0;
            m_currentGeneration++;
            return;
        }

        neat::Genome& currentGenome = m_population.genomes[m_currentGenomeIndex];

        // Get vision input
        std::vector<double> vision = m_visionSystem.getVision(m_playLayer);

        // Evaluate neural network
        std::vector<double> output = currentGenome.evaluate(vision);

        // Execute action based on output
        if (!output.empty()) {
            double jumpSignal = output[0];
            executeAction(jumpSignal);
        }
    }

    void onLevelReset() {
        // Move to next genome when level is reset (current one died)
        m_currentGenomeIndex++;
        m_timeAlive = 0.0f;
    }

    const neat::Population& getPopulation() const {
        return m_population;
    }

    int getCurrentGeneration() const {
        return m_currentGeneration;
    }

    double getAverageFitness() const {
        return m_population.getAverageFitness();
    }

    double getBestFitness() const {
        return m_population.getBest().fitness;
    }

private:
    PlayLayer* m_playLayer;
    VisionSystem m_visionSystem;
    neat::Population m_population;
    size_t m_currentGenomeIndex;
    int m_currentGeneration;
    float m_timeAlive;

    void executeAction(double jumpSignal) {
        if (!m_playLayer || !m_playLayer->m_player1) {
            return;
        }

        PlayerObject* player = m_playLayer->m_player1;

        // Threshold for jump action
        const double JUMP_THRESHOLD = 0.5;

        if (jumpSignal > JUMP_THRESHOLD) {
            // Execute jump
            player->pushButton(PlayerButton::Jump);
        } else {
            // Release jump
            player->releaseButton(PlayerButton::Jump);
        }
    }

    void evaluateGeneration() {
        // Calculate fitness for all genomes in current generation
        for (auto& genome : m_population.genomes) {
            // Fitness is based on level progress and time alive
            float progress = m_playLayer->getCurrentPercent() / 100.0f;
            float timeBonus = m_timeAlive * 0.01f; // Small bonus for staying alive

            genome.fitness = progress * 100.0f + timeBonus;
        }
    }
};
