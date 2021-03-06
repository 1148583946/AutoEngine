#ifndef GANE_MANAGER_H_
#define GANE_MANAGER_H_

#include "BaseObject.h"
#include "Singleton.h"
AUTO_BEGIN

///Any game manager (eg. AudioManager, dynamicsmanager) that needs serialization
///LevelGameManagers are destroyed and reloaded from the new scene when loading a new scene.
///GlobalGameManagers are run all game period
class GameManager : public Object
{
public:
	REGISTER_DERIVED_ABSTRACT_CLASS(GameManager, Object);
	GameManager();
};

class LevelGameManager : public GameManager
{
public:
	REGISTER_DERIVED_ABSTRACT_CLASS(LevelGameManager, GameManager);
	DECLARE_OBJECT_SERIALIZE(LevelGameManager);
	// Mistake to window GetClassNameW(need chang from Object GetClassName())
	//virtual char const* GetName() const { return GetClassName().c_str(); }
	LevelGameManager();
};

class GlobalGameManager : public GameManager
{
public:
	REGISTER_DERIVED_ABSTRACT_CLASS(GlobalGameManager, GameManager);
	DECLARE_OBJECT_SERIALIZE(GlobalGameManager);
	//virtual char const* GetName() const { return GetClassName().c_str(); }
	GlobalGameManager();
};

AUTO_END
#endif // GANE_MANAGER_H_
