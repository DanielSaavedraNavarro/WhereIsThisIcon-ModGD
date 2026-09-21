#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

// ============================================================
// GAME WITI MENU
// ============================================================

class GameWITIMenuLayer : public CCLayer {
public:

    static GameWITIMenuLayer* create() {
        auto ret = new GameWITIMenuLayer();

        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init() {
        if (!CCLayer::init())
            return false;

        this->setTouchEnabled(true);

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // ====================================================
        // OSCURECER EL FONDO
        // ====================================================

        auto overlay = CCLayerColor::create(
            ccc4(0, 0, 0, 150)
        );

        overlay->setContentSize(winSize);
        overlay->setPosition({0.f, 0.f});

        this->addChild(overlay, 0);

        // ====================================================
        // PANEL SQUARE01 - 9 SLICE
        // ====================================================

        auto panel = CCScale9Sprite::createWithSpriteFrameName(
            "square01_001.png"
        );

        if (!panel) {
            log::error(
                "Where Is This Icon?: No se pudo cargar "
                "square01_001.png"
            );

            return true;
        }

        panel->setContentSize({
            420.f,
            280.f
        });

        panel->setPosition({
            winSize.width / 2.f,
            winSize.height / 2.f
        });

        this->addChild(panel, 1);

        // ====================================================
        // BOTÓN X
        // ====================================================

        auto closeSprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_closeBtn_001.png"
            );

        if (closeSprite) {

            closeSprite->setScale(0.65f);

            auto closeButton =
                CCMenuItemSpriteExtra::create(
                    closeSprite,
                    this,
                    menu_selector(
                        GameWITIMenuLayer::onClose
                    )
                );

            auto closeMenu = CCMenu::create();

            closeMenu->setPosition({
                22.f,
                258.f
            });

            closeMenu->addChild(closeButton);

            panel->addChild(closeMenu, 10);
        }

        return true;
    }

    // ========================================================
    // BLOQUEAR TOQUES AL CREATORLAYER
    // ========================================================

    bool ccTouchBegan(
        CCTouch* touch,
        CCEvent* event
    ) override {
        return true;
    }

    // ========================================================
    // CERRAR
    // ========================================================

    void onClose(CCObject*) {
        this->removeFromParentAndCleanup(true);
    }
};


// ============================================================
// CREATOR LAYER
// ============================================================

class $modify(
    WhereIsThisIconCreatorLayer,
    CreatorLayer
) {

    bool init() {

        if (!CreatorLayer::init())
            return false;

        // ====================================================
        // ICONO PERSONALIZADO
        // ====================================================

        auto sprite = CCSprite::create(
            "iconMenu.png"_spr
        );

        if (!sprite)
            return true;

        sprite->setScale(0.225f);

        // ====================================================
        // BOTÓN
        // ====================================================

        auto button =
            CCMenuItemSpriteExtra::create(
                sprite,
                this,
                menu_selector(
                    WhereIsThisIconCreatorLayer::
                    onWhereIsThisIcon
                )
            );

        button->setID(
            "where-is-this-icon-button"_spr
        );

        // ====================================================
        // MENÚ
        // ====================================================

        auto menu = CCMenu::create();

        menu->setID(
            "where-is-this-icon-menu"_spr
        );

        // ====================================================
        // POSICIÓN AL LADO DEL BOTÓN BACK
        // ====================================================

        auto backButton =
            this->getChildByID("back-button");

        if (backButton) {

            auto pos = backButton->getPosition();

            menu->setPosition({
                pos.x +
                backButton->getContentSize().width +
                18.f,

                pos.y
            });

        }
        else {

            auto winSize =
                CCDirector::sharedDirector()->getWinSize();

            menu->setPosition({
                65.f,
                winSize.height - 30.f
            });
        }

        this->addChild(menu, 100);

        menu->addChild(button);

        return true;
    }


    // ========================================================
    // ABRIR GAME WITI MENU
    // ========================================================

    void onWhereIsThisIcon(CCObject*) {

        // No abrir dos paneles
        if (this->getChildByID(
            "game-witi-menu-layer"
        ))
            return;

        auto panel =
            GameWITIMenuLayer::create();

        if (!panel)
            return;

        panel->setID(
            "game-witi-menu-layer"_spr
        );

        // Encima de absolutamente todo
        this->addChild(panel, 1000);
    }
};