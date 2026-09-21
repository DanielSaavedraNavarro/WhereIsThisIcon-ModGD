#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

class $modify(WhereIsThisIconCreatorLayer, CreatorLayer) {
    bool init() {
        if (!CreatorLayer::init())
            return false;

        auto sprite = CCSprite::create("infoMenu.png"_spr);

        if (!sprite) {
            log::error("No se pudo cargar infoMenu.png");
            return true;
        }

        // Un poco más grande
        sprite->setScale(1.15f);

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(
                WhereIsThisIconCreatorLayer::onWhereIsThisIcon
            )
        );

        button->setID("where-is-this-icon-button"_spr);

        // Menú independiente para poder posicionarlo fácilmente
        auto menu = CCMenu::create();
        menu->setID("where-is-this-icon-menu"_spr);

        // Esquina inferior izquierda
        menu->setPosition({
            35.f,
            35.f
        });

        menu->addChild(button);
        this->addChild(menu);

        return true;
    }

    void onWhereIsThisIcon(CCObject*) {
        FLAlertLayer::create(
            "Where Is This Icon?",
            "El botón funciona correctamente.",
            "OK"
        )->show();
    }
};