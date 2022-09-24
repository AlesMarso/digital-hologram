#include "Functor.h"

gui::Functor::~Functor()
{
}

void gui::Functor::SetEvent(uint32_t event_id, uint32_t action_id, Event func)
{
    Action action;
    action[action_id] = func;

    m_Container[event_id] = action;
}

bool gui::Functor::operator()(uint32_t event_id, uint32_t action_id, const EventArgs& args)
{
    if (m_Container.empty())
        return false;

    auto eventIter = m_Container.find(event_id);

    if (eventIter == m_Container.end())
        return false;

    auto actionIter = eventIter->second.find(action_id);

    if (actionIter == eventIter->second.end())
        return false;

    return actionIter->second(args);
}
