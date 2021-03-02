#pragma once

#include <map>
#include <string>
#include <functional>

/**
 * A base class for objects that can be animated based on some parameter of type T.
 * The inherited class can easily create animations of its variables,
 * by creating actions, which are defined with a function
 * that specifies exactly how to animate the object at every instance.
 * Then the inherited class can play/pause/stop each of the created actions
 * in an appropriate moment of the runtime of a game.
 */
template <class T>
class Animatable
{

  protected:

    class Action;

    /**
     * Adds a new action to the animation
     * 
     * @param[in] id
     *  String ID of the action, that will be used to access the action
     * @param[in] action
     *  The action that will be added to the animation
     */
    void AddAction(std::string const& id, Action const&);

    /**
     * Returns a reference to the action
     * with the requested ID
     * 
     * @param[in] id
     *  String ID of the requested action
     * 
     * @return a reference to the requested action
     */
    Action& GetAction(std::string const& id);

    /**
     * Updates animation for next frame,
     * meaning that it updates each action,
     * of which the animation consists.
     * 
     * This function is supposed be called each frame.
     * That's what will keep the animation running.
     */
    void UpdateAnimation();

  private:

    /* Map of registered actions.
       It maps action IDs to the corresponding action objects */
    std::map<std::string, Action> _actionsMap;
};

/**
 * A class for an action, as a part of an animation.
 * An action is a single thing happening in the animation.
 * It acts on a single object with a single function.
 * More specificaly an action consists of a pointer to an object,
 * and a function that describes how that object changes with time.
 * Also actions have durations and can be easily started and stopped.
 */
template <class T>
class Animatable<T>::Action
{

  public:

    /**
     * Creates an action for the given object,
     * defined by the given act function.
     * 
     * @param[in] objPtr
     *  Pointer to the object on which the action will act
     * @param[in] actFunc
     *  Function taking in a pointer to an object, on which to act,
     *  and an instance in the duration of the action, as a number between 0 and 1.
     *  (0 meaning the beginning of the action, 1 meaning the end)
     *  That function is supposed to describe the desired state of the object
     *  at each instance of the action.
     * @param[in] duration
     *  Duration of the action, in frames
     */
    Action(
        T* objPtr,
        std::function<void(T*, float)> actFunc,
        size_t duration
    );

    /**
     * Updates the action for next frame.
     * If the action is currently playing,
     * the act function will be applied to the object.
     */
    void UpdateAction();

    /**
     * Starts playing the action from the beginning.
     * If the action is paused, it can be continued
     * with the Continue() function.
     */
    void Play();

    /**
     * Stops the action
     */
    void Stop();

    /**
     * Pauses the action.
     * Meaning that it can later be continued
     * from the same instance
     */
    void Pause();

    /**
     * Continues the action, if it has been paused,
     * otherwise does nothing.
     */
    void Continue();

  private:

    /// Pointer to the object on which the action acts
    T* _objPtr;

    /// An act function, describing the state of the object at every instance
    std::function<
        void(
            T*, // Pointer to the object on which the act function will act
            float // Instance in the action, a number between 0 and 1
        )
    > _actFunc;

    /// Duration of the action, in frames
    size_t _duration;

    /// Current frame of the action
    size_t _frame;

    /// Tells us whether the action is currently playing
    bool _playing;

    /// Tells us whether the action is currently paused
    bool _paused;
};

template <class T>
void Animatable<T>::AddAction(
    std::string const& id, Action const& action)
{
    if (_actionsMap.find(id) != _actionsMap.end())
    {
        throw "Error: Action with ID " + id + " has already been added to the animation.";
    }
    _actionsMap.insert(typename decltype(_actionsMap)::value_type(id, action));
}

template <class T>
typename Animatable<T>::Action&
Animatable<T>::GetAction(std::string const& id)
{
    if (_actionsMap.find(id) == _actionsMap.end())
    {
        throw "Error: There is no action with ID " + id + " in the animation.";
    }
    return _actionsMap.find(id)->second;
}

template <class T>
void Animatable<T>::UpdateAnimation()
{
    for (auto& idActionPair : _actionsMap)
    {
        Action& action = idActionPair.second;
        action.UpdateAction();
    }
}

template <class T>
Animatable<T>::Action::Action(
    T* objPtr,
    std::function<void(T*, float)> actFunc,
    size_t duration)
    : _objPtr(objPtr),
    _actFunc(actFunc),
    _duration(duration),
    _frame(0),
    _playing(false),
    _paused(false)
{}

template <class T>
void Animatable<T>::Action::UpdateAction()
{
    if (_playing)
    {
        _actFunc(
            _objPtr,
            (float)_frame / (_duration - 1) // duration - 1 because we want the instance to be between 0 and 1 inclusive
        );
        _frame++;
        if (_frame >= _duration)
        {
            _playing = false;
            _frame = 0;
        }
    }
}

template <class T>
void Animatable<T>::Action::Play()
{
    _frame = 0;
    _playing = true;
    _paused = false; // in case it was paused, the pause is lost after replaying
}

template <class T>
void Animatable<T>::Action::Stop()
{
    _playing = false;
    _paused = false;
}

template <class T>
void Animatable<T>::Action::Pause()
{
    _playing = false;
    _paused = true;
}

template <class T>
void Animatable<T>::Action::Continue()
{
    if (_paused)
    {
        _playing = true;
        _paused = false;
    }
}