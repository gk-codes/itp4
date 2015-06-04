/*
** Author:  Lukas Stanek on 04.06.15.
** File:    Context.cpp
** Project: Turn based Strategy Game
*/

#include "Context.h"
#include "../../libs/mlog.h"
#include "../../tbs.h"
#include "IdleState.h"
#include "SelectedState.h"
#include "MovingState.h"
#include "FightState.h"

using namespace std;

/*
 * Singleton Implementation
 */
std::shared_ptr<Context> Context::instance(new Context());

std::shared_ptr<Context> Context::getInstance() {

//    if(instance == nullptr){
//        instance.reset(new Context());
//    }

    return instance;
}


/*
 * Actual Impl
 */

Context::Context() {
    std::shared_ptr<State> newState;
    newState.reset(new IdleState(getInstance()));
    mStates.push_back(newState);
    newState.reset(new SelectedState(getInstance()));
    mStates.push_back(newState);
    newState.reset(new MovingState(getInstance()));
    mStates.push_back(newState);
    newState.reset(new FightState(getInstance()));
    mStates.push_back(newState);

    newState.reset();

    mCurrentState = mStates[0];
}

void Context::setCurrentState(States s) {
    LOG_F_TRACE(GAME_LOG_PATH, "state size ", mStates.size());
    switch(s){
        case States::STATE_IDLE: mCurrentState = mStates[0]; break;
        case States::STATE_SELECTED: mCurrentState = mStates[1]; break;
        case States::STATE_MOVING: mCurrentState = mStates[2]; break;
        case States::STATE_FIGHT: mCurrentState = mStates[3]; break;
    }
}

std::shared_ptr<State> Context::getCurrentState() {
    return mCurrentState;
}

void Context::injectGameReference(std::shared_ptr<Game> game) {

    for(std::shared_ptr<State> state : mStates){
        state->setGame(game);
    }

}