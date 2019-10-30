#ifndef ENEMY_H
#define ENEMY_H

#include "circle.h"

class Enemy
{
    Circle body;

public:
    Enemy() {}

    explicit Enemy(Circle body)
    {
        this->body = body;
    }

    Circle& getBody() {
        return body;
    }

    void setBody(Circle body) {
        this->body = body;
    }
};

#endif