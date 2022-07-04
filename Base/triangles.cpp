#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	/*
	*  On prépare le viewport pour OpenGL avec la taille (width et height)
	*  Les deux premiers paramètres définissent l'emplacement du coin inférieur gauche de la fenêtre.
	*  Les deux derniers définissent la largeur et la hauteur de la fenêtre de rendu en pixels, que nous
	*  défini égal à la taille de la fenêtre de GLFW.
	*/
}

void processInput(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) 
		std::cout << "Vous avez appuye sur la touche C !" << std::endl; 
}

const char* vertexShaderSource_Triangles_1 = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource_Triangles_1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);;\n"
"}\0";

int main() 
{
	int width = 400; 
	int height = 400; 

	glfwInit(); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Création de la fenêtre
	GLFWwindow* fenetre = glfwCreateWindow(width, height, "Premiere Fenetre", NULL, NULL); 
	if (fenetre == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl; 
		glfwTerminate(); 
		return -1; 
	}
	glfwMakeContextCurrent(fenetre);
	glfwSetFramebufferSizeCallback(fenetre, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl; 
		return -1;
	}


	unsigned int vertexShader_Triangles_1 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader_Triangles_1, 1, &vertexShaderSource_Triangles_1, NULL);
	glCompileShader(vertexShader_Triangles_1);
	// on vérifie s'il y a des erreurs :
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader_Triangles_1, GL_COMPILE_STATUS, &success); //
	if (!success) // Si ce n'est pas un succès
	{
		glGetShaderInfoLog(vertexShader_Triangles_1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		/*
		* Nous définissons d'abord un entier pour indiquer le succès et un conteneur de stockage pour les messages d'erreur.
		Ensuite, nous vérifions si la compilation a réussi avec glGetShaderiv.
		Si la compilation a échoué, nous devons récupérer le message d'erreur avec glGetShaderInfoLog et imprimer le message d'erreur.
		*/
	}

	//Nous les définissons en coordonnées de périphérique normalisées (la région visible d'OpenGL) dans un tableau flottant :
	unsigned int fragmentShader_Triangles_1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_Triangles_1, 1, &fragmentShaderSource_Triangles_1, NULL);
	glCompileShader(fragmentShader_Triangles_1);
	glGetShaderiv(fragmentShader_Triangles_1, GL_COMPILE_STATUS, &success); //
	if (!success) // Si ce n'est pas un succès
	{
		glGetShaderInfoLog(fragmentShader_Triangles_1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram_Triangles_1 = glCreateProgram();
	glAttachShader(shaderProgram_Triangles_1, vertexShader_Triangles_1);
	glAttachShader(shaderProgram_Triangles_1, fragmentShader_Triangles_1);
	glLinkProgram(shaderProgram_Triangles_1);
	/* La fonction glCreateProgram crée un programme et renvoie la référence ID à l'objet programme nouvellement créé.
	Maintenant, nous devons attacher les shaders précédemment compilés à l'objet programme, puis les lier avec glLinkProgram :*/
	glGetProgramiv(shaderProgram_Triangles_1, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram_Triangles_1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM:COMPILATION_FAILED\n" << infoLog << std::endl;;
	}
	glDeleteShader(vertexShader_Triangles_1);
	glDeleteShader(shaderProgram_Triangles_1);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	unsigned int VBO_T1, VAO_T1;
	glGenVertexArrays(1, &VAO_T1);
	glGenBuffers(1, &VBO_T1);
	glBindVertexArray(VAO_T1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_T1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);






	while (!glfwWindowShouldClose(fenetre))
	{
		// On met la fonction pour les inputs :
		processInput(fenetre);

		// RENDERING commands :
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT);

		// Dessine le triangle
		glUseProgram(shaderProgram_Triangles_1);
		glBindVertexArray(VAO_T1); //vu que nous n'avons qu'un seul VAO, il n'est pas nécessaire de le lier à chaque fois, mais nous le ferons pour garder les choses un peu plus organisées
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindVertexArray(0); // no nécessaire d'unbind



		glfwSwapBuffers(fenetre); 

		glfwPollEvents(); 
	}

	glDeleteVertexArrays(1, &VAO_T1);
	glDeleteBuffers(1, &VBO_T1);
	glDeleteProgram(shaderProgram_Triangles_1);

	glfwTerminate();
	return 0;
}