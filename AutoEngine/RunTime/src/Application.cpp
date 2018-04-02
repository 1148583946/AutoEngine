#include "Application.h"
AUTO_BEGIN

Application * Application::m_pApplication = nullptr;


Application::~Application()
{
	Assert(this == m_pApplication);
	m_pApplication = nullptr;
}
/*
* @Application::run
* this is Engine important funcation
*/
int Application::run()
{
	if (init() == AU_ERROR)
	{
		return AU_ERROR;
	}
	if (runLoop() == AU_ERROR)
	{
		return AU_ERROR;
	}
	return finish();
}

int Application::init()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		ErrorString("Failed to initialize GLAD \n");
		return AU_ERROR;
	}
	return AU_NORMAL;
}

void processInput(GLFWwindow *window)
{
	if (GLGetKey(window, KEY_ESCAPE) == S_PRESS)
		GLCloseWindow(window);
}

int Application::runLoop()
{


	Shader ourShader((AtConfig::shader_path + "AUTO_texture.vs").c_str(), (AtConfig::shader_path + "AUTO_texture.fs").c_str());
	Shader ourShader( AtConfig::shader_path + "AUTO_texture.vs", AtConfig::shader_path + "AUTO_texture.fs" );


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// ���ز���������
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);			//��Ҫ�����������������,Ȼ������Ǵ洢�ڵڶ���������unsigned int��
	glBindTexture(GL_TEXTURE_2D, texture);//������
										  // Ϊ��ǰ�󶨵�����������û��Ʒ�ʽ
										  /*
										  ���һ������
										  GL_REPEAT			��������ԭ��
										  GL_MIRRORED_REPEAT	�������־���
										  GL_CLAMP_TO_EDGE	������������
										  GL_CLAMP_TO_BORDER	��������ʹ��ָ����ɫ
										  */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Ϊ��ǰ�󶨵�����������ù��˷�ʽ
	/*
	GL_NEARSET ѡ���������ɫ(��Ե���)
	GL_LINEAR  �����������긽�����������ؼ����ֵ (��Եģ��)
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	/*
	1.����һ��ͼ���ļ���λ����Ϊ����
	2.��Ҫ����int��Ϊ����2,3,4 ��� �߶� ��ɫͨ������
	*/
	unsigned char *data = stbi_load("Resource/texture/square.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{	/*
		��������
		��һ������ ָ��������Ŀ�� ����GL_TEXTURE_2D��ζ�Ż������뵱ǰ�󶨵����������ͬһ��Ŀ���ϵ�����
		�ڶ������� Ϊ����ָ���༶��Զ����ļ���
		���������� ����OpenGL����ϣ��������洢Ϊ���ָ�ʽ
		���ĸ���������� �������յ�����Ŀ�Ⱥ͸߶�
		���������� ����Ϊ0��ʷ��������
		���ߵڰ˸�����������Դͼ�ĸ�ʽ����������
		���һ��������������ͼ������
		*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	while (!GLShouldCloseWindow(glfwWindow))
	{
		processInput(glfwWindow);

		window.drawWindow();

		// bind Texture
		//Ĭ�Ϸ������һ��uniform sampler2D ��Ҫ�Լ�����glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		// render container
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/*glfwSwapBuffers(glfwWindow);
		glfwPollEvents();*/
		window.runLoopOver();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return AU_NORMAL;
}
int Application::finish()
{
	window.destoryWindow();
	glfwWindow = nullptr;
	return AU_NORMAL;
}

///Static
Application* Application::getInstance()
{
	if (m_pApplication == nullptr)
	{
		m_pApplication = new Application();
	}
	return m_pApplication;
}

///Private
Application::Application()
{
	window = Window();
	glfwWindow = window.createWindow();
	Assert(!m_pApplication);
	m_pApplication = this;
}
AUTO_END
