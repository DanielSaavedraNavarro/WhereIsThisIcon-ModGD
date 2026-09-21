#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(WhereIsThisIconMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto menu = this->getChildByID("bottom-menu");

        if (menu) {
            auto sprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");

            if (sprite) {
                auto button = CCMenuItemSpriteExtra::create(
                    sprite,
                    this,
                    menu_selector(WhereIsThisIconMenuLayer::onWhereIsThisIcon)
                );

                button->setID("where-is-this-icon-button"_spr);

                menu->addChild(button);
                menu->updateLayout();
            }
        }

        return true;
    }

    void onWhereIsThisIcon(CCObject*) {
        FLAlertLayer::create(
            "Where Is This Icon?",
            "¡El botón funciona! :D",
            "OK"
        )->show();
    }
};