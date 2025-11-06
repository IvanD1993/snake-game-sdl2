#pragma once
#include "renderer.h"
#include "input.h"
#include "time_utils.h"

struct IState {
    virtual ~IState() = default;
    virtual void onEnter() {}
    virtual void onExit()  {}
    virtual void update(const TimeStep& t, const InputFrame& in) = 0;
    virtual void render(Renderer& r) = 0;
    virtual bool wantsPop() const { return false; } // optional stack system later
};
