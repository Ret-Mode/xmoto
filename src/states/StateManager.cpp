/*=============================================================================
XMOTO

This file is part of XMOTO.

XMOTO is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

XMOTO is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with XMOTO; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
=============================================================================*/

#include "StateManager.h"


StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

void StateManager::pushState(GameState* pNewState)
{
  (m_statesStack.back())->leaveAfterPush();

  m_statesStack.push_back(pNewState);
  (m_statesStack.back())->enter();

  /* calculate which state will be rendered */
  std::vector<GameState*>::reverse_iterator stateIterator = m_statesStack.rbegin();
  bool hideState = false;

  while(stateIterator != m_statesStack.rend()){
    (*stateIterator)->setHide(hideState);

    if((*stateIterator)->drawStatesBehind() == false){
      hideState = true;
    }
    
    stateIterator++;
  }
  
}

GameState* StateManager::popState()
{
}

void StateManager::update()
{
  std::vector<GameState*>::reverse_iterator stateIterator = m_statesStack.rbegin();

  while(stateIterator != m_statesStack.rend()){
    (*stateIterator)->update();

    if((*stateIterator)->updateStatesBehind() == false)
      break;
    
    stateIterator++;
  }
}

void StateManager::render()
{
  /* we have to draw states from the bottom of the stack to the top */
  std::vector<GameState*>::iterator stateIterator = m_statesStack.begin();

  while(stateIterator != m_statesStack.end()){
    (*stateIterator)->render();
    
    stateIterator++;
  }
}

void StateManager::input()
{
  std::vector<GameState*>::reverse_iterator stateIterator = m_statesStack.rbegin();

  while(stateIterator != m_statesStack.rend()){
    (*stateIterator)->input();

    if((*stateIterator)->sendInputToStatesBehind() == false)
      break;
    
    stateIterator++;
  }
}