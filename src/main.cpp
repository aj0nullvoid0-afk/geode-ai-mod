#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>
#include <Geode/binding/GameObject.hpp>

#include "neat.hpp"
#include "ai_controller.hpp"
#include "vision_system.hpp"

using namespace geode::prelude;

// Global AI controller instance
AIController* g_aiController = nullptr;

class $modify(PlayLayerHook, PlayLayer) {
    struct Fields {
        AIController* aiController = nullptr;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }

        // Initialize AI controller for this level
        m_fields->aiController = new AIController(this);
        g_aiController = m_fields->aiController;

        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        // Update AI if enabled
        if (m_fields->aiController && Mod::get()->getSettingValue<bool>("enable_ai")) {
            m_fields->aiController->update(dt);
        }
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        // Reset AI state
        if (m_fields->aiController) {
            m_fields->aiController->onLevelReset();
        }
    }

    ~PlayLayerHook() {
        if (m_fields->aiController) {
            delete m_fields->aiController;
            m_fields->aiController = nullptr;
            g_aiController = nullptr;
        }
    }
};

// Entry point
$on_mod(Loaded) {
    log::info("Geometry Dash AI Learner mod loaded!");
}
