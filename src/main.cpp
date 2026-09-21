#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

class $modify(WhereIsThisIconCreatorLayer, CreatorLayer) {
    bool init() {
        if (!CreatorLayer::init())
            return false;

        auto sprite = CCSprite::create("iconMenu.png"_spr);

        if (!sprite) {
            log::error("No se pudo cargar iconMenu.png");
            return true;
        }

        // Tamaño pequeño, como los botones normales de GD
        sprite->setScale(0.65f);

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(
                WhereIsThisIconCreatorLayer::onWhereIsThisIcon
            )
        );

        button->setID("where-is-this-icon-button"_spr);

        // Menú independiente
        auto menu = CCMenu::create();
        menu->setID("where-is-this-icon-menu"_spr);

        // Posición: esquina inferior izquierda
        menu->setPosition({38.f, 38.f});

        // Encima de la decoración
        menu->setZOrder(100);

        menu->addChild(button);
        this->addChild(menu, 100);

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