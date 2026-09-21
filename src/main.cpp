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

        // Más pequeño
        sprite->setScale(0.45f);

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(
                WhereIsThisIconCreatorLayer::onWhereIsThisIcon
            )
        );

        button->setID("where-is-this-icon-button"_spr);

        auto menu = CCMenu::create();
        menu->setID("where-is-this-icon-menu"_spr);

        // Buscar el botón de salir del CreatorLayer
        auto backButton = this->getChildByID("back-button");

        if (backButton) {
            auto pos = backButton->getPosition();

            // A la derecha del botón de salir
            menu->setPosition({
                pos.x + backButton->getContentSize().width + 20.f,
                pos.y
            });
        }
        else {
            // Fallback por si el ID cambia
            auto winSize = CCDirector::sharedDirector()
                ->getWinSize();

            menu->setPosition({
                55.f,
                winSize.height - 35.f
            });
        }

        // Sobre la decoración
        this->addChild(menu, 100);

        menu->addChild(button);

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