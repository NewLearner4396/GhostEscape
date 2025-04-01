#include "AffiliateBar.h"

void AffiliateBar::render() {
    auto  pos = parent_->getRenderPosition() + offset_;
    if(bar_width_percentage_ > 0.7f){
        game_.renderHBar(pos, size_, bar_width_percentage_, color_high_);
    } else if(bar_width_percentage_ > 0.3f){
        game_.renderHBar(pos, size_, bar_width_percentage_, color_medium_);
    } else {
        game_.renderHBar(pos, size_, bar_width_percentage_, color_low_);
    }
}

AffiliateBar* AffiliateBar::addAffiliateBar(Object* parent, glm::vec2 size, Anchor anchor) {
    auto affiliate_bar = new AffiliateBar();
    affiliate_bar->init();
    affiliate_bar->setAnchor(anchor);
    affiliate_bar->setSize(size);
    if (parent) {
        affiliate_bar->setParent(dynamic_cast<ObjectScreen*>(parent));
        parent->safeAddObject(affiliate_bar);
    }
    return affiliate_bar;
}
