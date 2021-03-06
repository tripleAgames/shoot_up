#include    "Square.h"
#include    "GameScene.h"
#include    "Utils.h"
#include    "ShootUp.h"
#include    "Line.h"

Square::Square(int line_size) {
}

Square::~Square() {
}

Size Square::get_square_size(int line_size) {
    auto winSize = Director::getInstance()->getVisibleSize();

    if (line_size > 5 || line_size < 4)
        return (Size(0, 0));
    if (line_size == SQUARE_SIZE_LINE_OF_4)
        return (Size(winSize.width / 4, static_cast<float>(winSize.height / SQUARE_SIZE_4_HEIGHT)));
    else if (line_size == SQUARE_SIZE_LINE_OF_5)
        return (Size(winSize.width / 5, static_cast<float>(winSize.height / SQUARE_SIZE_5_HEIGHT)));

    return (Size(0, 0));
}

float *Square::get_rect_size() {
    return (rect_size);
}

int Square::get_square_pv() {
    return (this->square_pv);
}

void Square::reset_square() {
    this->particle_played = 0;
    this->getChildByTag(PROGRESS_CONTENT_TAG)->setVisible(false);
    this->getChildByTag(PROGRESS_BORDER_TAG)->setVisible(false);
    this->square_pv = 0;
    std::string st = StringUtils::format("%i", this->square_pv);
    if (this->star_bonus == 1)
        detach_square();
    if (this->chest_bonus)
        detach_chest();
}

void Square::detach_square() {
    removeChildByTag(STAR_BONUS_TAG);
    this->star_bonus = 0;
}

void Square::detach_chest() {
    this->chest_bonus = false;
}
void Square::assign_point(int pv) {
    if (pv == 0)
        pv = 1;
    this->initial_pv = pv;
    this->square_pv = pv;
    ProgressTimer *progress = ((ProgressTimer *) this->getChildByTag(
            PROGRESS_CONTENT_TAG));
    progress->setPercentage(100);
}

void Square::create_square_components(Square *sq) {
    Sprite *border = Sprite::create("gauges/gauge_border.png");
    border->setTag(PROGRESS_BORDER_TAG);
    border->setVisible(false);
    border->setContentSize(Size(static_cast<float>(sq->getContentSize().width * 0.9),
                                static_cast<float>(sq->getContentSize().height * 0.13)));
    border->setAnchorPoint(Vec2(0, 0));
    border->setPosition(Vec2(static_cast<float>(0 + sq->getContentSize().width * 0.05), 0));
    ProgressTimer *progress = ProgressTimer::create(
            Sprite::create("gauges/gauge_content.png"));
    progress->setVisible(false);
    progress->setTag(PROGRESS_CONTENT_TAG);
    progress->setType(ProgressTimerType::BAR);
    progress->setMidpoint(Vec2(0, 0));
    progress->setBarChangeRate(Vec2(1, 0));
    progress->setPercentage(static_cast<float>(0));
    progress->setPosition(border->getPosition() + border->getContentSize() / 2);
    progress->setScaleX(static_cast<float>(border->getContentSize().width * 0.99 /
                                           progress->getContentSize().width));
    progress->setScaleY(static_cast<float>(border->getContentSize().height * 0.9 /
                                           progress->getContentSize().height));
    sq->addChild(border);
    sq->addChild(progress);
}

Square *Square::create(int line_size) {
    auto winSize = Director::getInstance()->getVisibleSize();
    Square *s = new Square(line_size);
    if (s) {
        s->setAnchorPoint(Vec2(0.5, 0.5));
        s->square_pv = 10;
        s->star_bonus = 0;
        s->chest_bonus = false;
        s->particle_played = 0;
        s->setContentSize(get_square_size(line_size));
        s->rect_size[0] = s->getContentSize().width;
        s->rect_size[1] = s->getContentSize().height;
        std::string st = StringUtils::format("%i", s->square_pv);
        create_square_components(s);
        return (s);
    }
    CC_SAFE_DELETE(s);
    return NULL;
}


