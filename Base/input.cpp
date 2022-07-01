#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { // Fonction pour le viewport
	glViewport(0, 0, width, height);
	/*
	*  On prépare le viewport pour OpenGL avec la taille (width et height)
	*  Les deux premiers paramètres définissent l'emplacement du coin inférieur gauche de la fenêtre.
	*  Les deux derniers définissent la largeur et la hauteur de la fenêtre de rendu en pixels, que nous
	*  défini égal à la taille de la fenêtre de GLFW.
	*/
}

void processInput(GLFWwindow* window) // Fonction pour les input (quand on presse une touche)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Escape est la touche ECHAP
		glfwSetWindowShouldClose(window, true); // On met fin à la fenêtre
	
	// Autre exemple, vous avez beaucoup de touche, vous pouvez les trouver avec : GLFW_KEY_ 
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) // GLFW_PRESS permet de vérifier si la touche en question est pressé
		std::cout << "Vous avez appuyé sur la touche C !" << std::endl; // Ptit message 
}


int main() 
{
	int width = 400; // On chois la taille en longeur
	int height = 400; // On choisis la taille en largeur

	glfwInit(); // On prépare GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // On demande une version minimum
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Création de la fenêtre
	GLFWwindow* fenetre = glfwCreateWindow(width, height, "Premiere Fenetre", NULL, NULL); // On peut ignorer les deux derniers paramètres
	if (fenetre == NULL) // Si cela est impossible, alors :
	{
		std::cout << "Failed to create GLFW window" << std::endl; // On envoit un message d'erreur
		glfwTerminate(); // On close le programme
		return -1; // On return
	}
	glfwMakeContextCurrent(fenetre);


	// Préparation de GLAD qui va s'occuper des fonctions pour OpenGL :
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl; // Message d'erreur en cas d'impossibilité de "charger" GLAD
		return -1;  // On return
	}

	glfwSetFramebufferSizeCallback(fenetre, framebuffer_size_callback);
	//Il faut que GLFW call cette fonction à chaque redimensionnement de fenêtre 

	while (!glfwWindowShouldClose(fenetre))//vérifie au début de chaque itération de boucle si GLFW a reçu l'ordre de fermer
	{
		// On met la fonction pour les inputs :
		processInput(fenetre);

		glfwSwapBuffers(fenetre); 
		/*
		* permutera le tampon de couleur (un grand tampon 2D qui contient des valeurs de couleur pour chaque pixel 
		dans la fenêtre de GLFW) qui est utilisé pour le rendu pendant cette itération de rendu et l'affichera comme sortie à l'écran.
		*/
		glfwPollEvents(); 
		/*
		la fonction vérifie si des événements sont déclenchés (comme les événements de saisie au clavier ou de mouvement de la souris), 
		met à jour l'état de la fenêtre et appelle les fonctions correspondantes
		*/
	}

	glfwTerminate();
	/*
	Dès que nous quittons la boucle de rendu, nous aimerions nettoyer/supprimer correctement toutes les ressources de GLFW qui ont été allouées. 
	Nous pouvons le faire via la fonction glfwTerminate que nous appelons à la fin de la fonction principale.
	*/
	return 0;
}