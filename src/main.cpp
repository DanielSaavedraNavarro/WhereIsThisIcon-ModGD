#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;


// ============================================================
// GAME WITI MENU LAYER
// ============================================================

class GameWITIMenuLayer : public CCLayer {

private:
    CreatorLayer* m_creatorLayer = nullptr;
    CCScale9Sprite* m_panel = nullptr;

public:

    static GameWITIMenuLayer* create(
        CreatorLayer* creatorLayer
    ) {
        auto ret = new GameWITIMenuLayer();

        if (ret && ret->init(creatorLayer)) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }


    bool init(CreatorLayer* creatorLayer) {

        if (!CCLayer::init())
            return false;

        m_creatorLayer = creatorLayer;

        auto winSize =
            CCDirector::sharedDirector()->getWinSize();


        // ====================================================
        // DESACTIVAR LOS MENÚS DEL CREATORLAYER
        // ====================================================

        if (m_creatorLayer) {

            auto children =
                m_creatorLayer->getChildren();

            for (unsigned int i = 0;
                 i < children->count();
                 i++) {

                auto child =
                    static_cast<CCNode*>(
                        children->objectAtIndex(i)
                    );

                if (auto menu =
                    typeinfo_cast<CCMenu*>(child)) {

                    menu->setEnabled(false);
                }
            }
        }


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
        // GJ_SQUARE01-HD
        //
        // Textura original del juego:
        // GJ_square01-hd.png
        // ====================================================

        auto panel =
            CCScale9Sprite::create(
                "GJ_square01-hd.png"
            );

        if (!panel) {

            log::error(
                "Where Is This Icon?: "
                "No se pudo cargar GJ_square01-hd.png"
            );

            return true;
        }

        m_panel = panel;


        // ====================================================
        // TAMAÑO
        // ====================================================

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

            auto closeMenu =
                CCMenu::create();


            // X sobre el borde superior izquierdo
            closeMenu->setPosition({
                8.f,
                280.f
            });

            closeMenu->addChild(closeButton);

            panel->addChild(
                closeMenu,
                10
            );
        }


        return true;
    }


    // ========================================================
    // BLOQUEAR TOUCH
    // ========================================================

    bool ccTouchBegan(
        CCTouch* touch,
        CCEvent* event
    ) override {

        // Consumir el touch para que no llegue
        // al CreatorLayer.
        return true;
    }


    // ========================================================
    // CERRAR
    // ========================================================

    void onClose(CCObject*) {

        // Reactivar los menús
        if (m_creatorLayer) {

            auto children =
                m_creatorLayer->getChildren();

            for (unsigned int i = 0;
                 i < children->count();
                 i++) {

                auto child =
                    static_cast<CCNode*>(
                        children->objectAtIndex(i)
                    );

                if (auto menu =
                    typeinfo_cast<CCMenu*>(child)) {

                    menu->setEnabled(true);
                }
            }
        }


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

        auto sprite =
            CCSprite::create(
                "iconMenu.png"_spr
            );

        if (!sprite)
            return true;

        sprite->setScale(0.207f);


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

        button->setPosition({-230.f, 100.f});
        button->setScale(0.75f);


        // ====================================================
        // MENÚ
        // ====================================================

        auto menu = CCMenu::create();

        menu->setID(
            "where-is-this-icon-menu"_spr
        );

        menu->addChild(button);
        this->addChild(menu, 100);


        return true;
    }


    // ========================================================
    // ABRIR GAME WITI MENU
    // ========================================================

    void onWhereIsThisIcon(
        CCObject*
    ) {

        if (this->getChildByID(
            "game-witi-menu-layer"
        ))
            return;


        auto panel =
            GameWITIMenuLayer::create(
                this
            );

        if (!panel)
            return;


        panel->setID(
            "game-witi-menu-layer"_spr
        );


        // Encima de todo
        this->addChild(
            panel,
            1000
        );
    }
};
