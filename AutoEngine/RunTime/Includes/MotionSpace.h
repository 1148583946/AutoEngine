#ifndef MOTION_SPACE_H_
#define MOTION_SPACE_H_
#include "Auto.h"
#include "ObjectDefines.h"
#include "Singleton.h"
#include "Mesh.h"
#include "Math/AUMath.h"
#include "Camera.h"
#include "LightManager.h"
USING_MATH
AUTO_BEGIN
/**
* @brief Singleton class
*/
class MotionSpace : public Singleton<MotionSpace>
{
public:
	MotionSpace();
	~MotionSpace();
	void SetWindow(GLFWwindow* glfwWindow);
	void Awake();
	void Start(); 
	void Update(Camera* camera); 
	void FixUpdate();
	void Finish();
};

AUTO_END

#endif // !MOTION_SPACE_H_
