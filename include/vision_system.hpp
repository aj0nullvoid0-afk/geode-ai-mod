#pragma once

#include <vector>
#include <Geode/Geode.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>
#include <Geode/binding/GameObject.hpp>

using namespace geode::prelude;

class VisionSystem {
public:
    VisionSystem(int gridSize = 7) : m_gridSize(gridSize) {}

    std::vector<double> getVision(PlayLayer* playLayer) {
        std::vector<double> vision;

        if (!playLayer || !playLayer->m_player1) {
            return std::vector<double>(m_gridSize * m_gridSize + 2, 0.0);
        }

        auto player = playLayer->m_player1;
        CCPoint playerPos = player->getPosition();

        // Get grid-based vision
        float cellWidth = 30.0f; // Adjust based on gameplay scale
        float cellHeight = 30.0f;

        for (int y = 0; y < m_gridSize; ++y) {
            for (int x = 0; x < m_gridSize; ++x) {
                // Calculate cell bounds
                float cellX = playerPos.x + (x - m_gridSize / 2) * cellWidth;
                float cellY = playerPos.y + (y - m_gridSize / 2) * cellHeight;

                // Check what's in this cell
                double cellValue = checkCellContent(playLayer, cellX, cellY, cellWidth, cellHeight);
                vision.push_back(cellValue);
            }
        }

        // Add player state features
        vision.push_back(normalizeVelocity(player->getYVelocity()));
        vision.push_back(player->m_isUpsideDown ? 1.0 : 0.0);

        return vision;
    }

    int getGridSize() const { return m_gridSize; }
    int getInputCount() const { return m_gridSize * m_gridSize + 2; }

private:
    int m_gridSize;

    double checkCellContent(PlayLayer* playLayer, float x, float y, float width, float height) {
        if (!playLayer->m_objects) {
            return 0.0; // Empty cell
        }

        CCRect cellRect = CCRectMake(x - width / 2, y - height / 2, width, height);

        for (auto obj : playLayer->m_objects->data()) {
            GameObject* gameObj = dynamic_cast<GameObject*>(obj);
            if (!gameObj) continue;

            CCRect objRect = gameObj->getObjectRect();
            if (cellRect.intersectsRect(objRect)) {
                // Determine cell type based on object
                if (isHazard(gameObj)) {
                    return -1.0; // Hazard
                } else if (isSolid(gameObj)) {
                    return 1.0; // Solid block
                } else if (isJumpable(gameObj)) {
                    return 0.5; // Jumpable platform
                }
            }
        }

        return 0.0; // Empty cell
    }

    bool isHazard(GameObject* obj) {
        // Check for spikes, saws, etc.
        // This is a simplified check; you may need to expand based on object types
        int type = obj->m_objectType;
        return (type == 8 || type == 9 || type == 10); // Example types for hazards
    }

    bool isSolid(GameObject* obj) {
        int type = obj->m_objectType;
        return (type == 1 || type == 2); // Example types for solid blocks
    }

    bool isJumpable(GameObject* obj) {
        int type = obj->m_objectType;
        return (type == 3 || type == 4); // Example types for jumpable platforms
    }

    double normalizeVelocity(double velocity) {
        // Normalize velocity to [-1, 1] range
        return std::tanh(velocity / 100.0);
    }
};
