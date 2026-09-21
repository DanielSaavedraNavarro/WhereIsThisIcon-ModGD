#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class WhereIsThisIconLayer : public FLAlertLayer {
protected:
    bool init() {
        if (!FLAlertLayer::init(
            nullptr,
            "WHERE IS THIS ICON?",
            "Find this icon somewhere in Geometry Dash!",
            "OK",
            nullptr,
            320.f,
            false,
            200.f,
            1.f
        )) {
            return false;
        }

        return true;
    }

public:
    static WhereIsThisIconLayer* create() {
        auto ret = new WhereIsThisIconLayer();

        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};


class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        // Obtener el menú donde están los botones inferiores
        auto menu = this->getChildByID("bottom-menu");

        if (!menu) {
            log::error("WHERE IS THIS ICON?: bottom-menu not found!");
            return true;
        }

        // Imagen normal
        auto normalSprite = CCSprite::create("iconMenu.png"_spr);

        if (!normalSprite) {
            log::error("WHERE IS THIS ICON?: iconMenu.png could not be loaded!");
            return true;
        }

        // Imagen al hacer hover/click
        auto selectedSprite = CCSprite::create("iconMenu.png"_spr);

        if (!selectedSprite) {
            selectedSprite = normalSprite;
        }

        // Un pequeño efecto de hover
        selectedSprite->setScale(1.10f);

        auto button = CCMenuItemSpriteExtra::create(
            normalSprite,
            selectedSprite,
            this,
            menu_selector(MenuLayer::onWhereIsThisIcon)
        );

        if (!button) {
            log::error("WHERE IS THIS ICON?: failed to create button!");
            return true;
        }

        button->setID("where-is-this-icon-button"_spr);

        // Añadirlo junto a los otros botones
        menu->addChild(button);

        // Dejar que el layout del menú lo acomode
        menu->updateLayout();

        log::info("WHERE IS THIS ICON?: button added!");

        return true;
    }

    void onWhereIsThisIcon(CCObject*) {
        auto layer = WhereIsThisIconLayer::create();

        if (layer) {
            layer->show();
        }
    }
};


$on_mod(Loaded) {
    log::info("WHERE IS THIS ICON? loaded!");
}