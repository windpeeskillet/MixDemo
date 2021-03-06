#include "DmStraightExpandCtrl.h"
#include "../../../../Mx/Coroutine/MxCoroutine.hpp"
#include "../../../../Mx/GameObject/MxGameObject.h"
#include "../../../../Mx/Time/MxTime.h"

MX_IMPLEMENT_RTTI(DmStraightExpandCtrl, Script)

DmStraightExpandCtrl::DmStraightExpandCtrl(const float _speedSlow,
                                           const float _speedExpand,
                                           const float _waitSec,
                                           const size_t _initCap)
    : speed(_speedSlow),
      speedExpand(_speedExpand),
      waitSec(_waitSec) {
    dmList.reserve(_initCap);
}

void DmStraightExpandCtrl::add(const HGameObject& _dm) {
    dmList.push_back(_dm);
}

void DmStraightExpandCtrl::start() {
    Coroutine::startCoroutine([](MX_YIELD_HANDLE, DmStraightExpandCtrl* _this) {
        yield_return(new Coroutine::WaitForSeconds(_this->waitSec));
        _this->speed = _this->speedExpand;
    }, this);

    //Coroutine::startCoroutine([](MX_YIELD_HANDLE, DmStraightExpandCtrl* _this) {
    //    // bug prone
    //    while(true) {
    //        auto i = 0;
    //        for(const auto& dm : _this->dmList) {
    //            auto& trans = dm->transform();
    //            auto newPos = trans.getPosition() + trans.forward() * _this->speed * Time::DeltaTime();
    //            trans.setPosition(newPos);
    //            if(++i == _this->dmList.size() / 9) {
    //                i = 0;
    //                yield_return(nullptr);
    //            }
    //        }
    //    }
    //}, this);
}

void DmStraightExpandCtrl::update() {
    for(const auto& dm : dmList) {
    //if(!dm->activeSelf())
    //    dmList.erase(dm);
        auto& trans = dm->transform();
        auto newPos = trans.getPosition() + trans.forward() * speed * Time::DeltaTime();
        trans.setPosition(newPos);
    }
}
