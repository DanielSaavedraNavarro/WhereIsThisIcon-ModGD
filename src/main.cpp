#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

class $modify(WhereIsThisIconCreatorLayer, CreatorLayer) {
    bool init() {
        if (!CreatorLayer::init())
            return false;

        auto sprite = CCSprite::create("infoMenu.png"_spr);

        if (!sprite)
            return true;

        sprite->setScale(0.8f);

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(WhereIsThisIconCreatorLayer::onWhereIsThisIcon)
        );

        button->setID("where-is-this-icon-button"_spr);

        auto menu = CCMenu::create();
        menu->setPosition({300.f, 40.f});

        menu->addChild(button);
        this->addChild(menu);

        return true;
    }

    void onWhereIsThisIcon(CCObject*) {
        log::info("Where Is This Icon clicked!");
    }
};