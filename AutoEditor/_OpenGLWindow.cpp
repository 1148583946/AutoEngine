#include "_OpenGLWindow.h"
#include "OpenGLGather.h"/*
_OpenGLWindow::_OpenGLWindow()
{
}

_OpenGLWindow::~_OpenGLWindow()
{
}

void _OpenGLWindow::_initializeGL()
{

	//����ȫ�ֱ���  
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void _OpenGLWindow::_paintGL()
{
	//������Ļ  
	glClear(GL_COLOR_BUFFER_BIT);
}

void _OpenGLWindow::_resizeGL(int width, int height)
{
}*/
void _initializeGL()
{
	if (!gladLoadGL())
	{
		
	}
	//����ȫ�ֱ���  
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void _paintGL()
{
	//������Ļ  
	glClear(GL_COLOR_BUFFER_BIT);
}

void _resizeGL(int width, int height)
{
}