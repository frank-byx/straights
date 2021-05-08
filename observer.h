#ifndef _OBSERVER_H_
#define _OBSERVER_H_

template <typename InfoType, typename StateType>
class Subject;
class TextDisplay;
class Game;

template <typename InfoType, typename StateType>
class Observer {
public:
  virtual void notify(Subject<InfoType, StateType> &whoFrom) = 0;
  virtual ~Observer() = default;
};

#endif
