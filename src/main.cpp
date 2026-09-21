#include <Geode/Geode.hpp>

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
            320.f
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

$on_mod(Loaded) {
    log::info("WHERE IS THIS ICON? loaded!");

    // Prototype: show the challenge when the mod loads.
    WhereIsThisIconLayer::create()->show();
}