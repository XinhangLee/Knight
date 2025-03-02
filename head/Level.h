//
// Created by lixh1 on 25-2-21.
//

#ifndef LEVEL_H
#define LEVEL_H

#include <common.h>
#include <Elements/Monster.h>

static Position ran_pos();
static int ran_num(int, int);


class Level : public Timer{
protected:
    bool pass[3];
    bool running[3];
public:
    Level();
    ~Level() override;
    virtual void run() {}
    bool getRunning(const int i) const {return running[i];}
    bool getPass(const int i) const {return pass[i];}
    void setPass(const int i) {pass[i] = true;}
};

extern Level *level;

class Level1 final : public Level {
public:
    Level1() = default;
    ~Level1() override = default;
    void run() override;
};

#endif //LEVEL_H
