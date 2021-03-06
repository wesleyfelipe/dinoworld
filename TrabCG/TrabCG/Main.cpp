#include <iostream>
#include <map>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "Manager.h"
#include "split.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

GLint m_mouseX, m_mouseY;
GLint lastX = 400, lastY = 300;
GLfloat yaw;
GLfloat pitch;
Camera camera(glm::vec3(0, 3, -10), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.01f, 1000.0f);
double previous_seconds;
int frame_count;

void mouse_callback(double xpos, double ypos);

enum modelos_enum { 
	chao = 0, 
	brachiosaurus = 1, 
	triceratops = 2, 
	trex = 3, 
	spinosaurus = 4, 
	ankylosaurus = 5, 
	ouranosaurus = 6,
	albertossaurus = 7,
	gallimimus = 8
};
std::map<int, Object> modelos;
std::map<int, Object>::iterator modeloSelecionadoIt;

Object initModel(modelos_enum idModelo, Manager manager, Shader *shader, std::string objPath, std::string texturePath, glm::vec3 rotation, glm::vec3 scale) {
	Object temp = manager.BuildObject(objPath, texturePath, texturePath, shader);
	temp.SetRot(rotation);
	temp.SetScale(scale);
	temp.id = idModelo;
	return temp;
}

Object initChaoModelo(Manager manager, Shader *shader) {
	return initModel(modelos_enum::chao, manager, shader, "../res/chao/plane.obj", "../res/chao/grass.jpg", glm::vec3(0,0,0), glm::vec3(10, 1, 10));
}

Object initBrachiosaurusModelo(Manager manager, Shader *shader) {
	return initModel(modelos_enum::brachiosaurus, manager, shader, "../res/brachiosaurus/brac.obj", "../res/brachiosaurus/brach.png", glm::vec3(-1.5, -3, 0), glm::vec3(0.5, 0.5, 0.5));
}

Object initTriceratopsModelo(Manager manager, Shader *shader) {
	return initModel(modelos_enum::triceratops, manager, shader, "../res/triceratops/trike.obj", "../res/triceratops/trike.png", glm::vec3(-1.5, -3, 0), glm::vec3(0.5, 0.5, 0.5));
}

Object initTrexModelo(Manager manager, Shader *shader) {
	return initModel(modelos_enum::trex, manager, shader, "../res/trex/trex.obj", "../res/trex/Trex.png", glm::vec3(0, 3, 0), glm::vec3(0.5, 0.5, 0.5));
}

Object initSpinosaurusModelo(Manager manager, Shader *shader) {
	return initModel(modelos_enum::spinosaurus, manager, shader, "../res/spinosaurus/spino.obj", "../res/spinosaurus/Spino.png", glm::vec3(0, 3, 0), glm::vec3(0.5, 0.5, 0.5));
}

Object initAnkylosaurusModelo(Manager manager, Shader *shader) {
	return initModel(modelos_enum::ankylosaurus, manager, shader, "../res/ankylosaurus/anky.obj", "../res/ankylosaurus/Anky.png", glm::vec3(0, 3, 0), glm::vec3(0.5, 0.5, 0.5));
}

Object initOuranosaurusModelo(Manager manager, Shader *shader) {
	return initModel(modelos_enum::ouranosaurus, manager, shader, "../res/ouranosaurus/oran.obj", "../res/ouranosaurus/ouran.png", glm::vec3(-1.5, 3, 0), glm::vec3(0.5, 0.5, 0.5));
}

Object initAlbertosaurus(Manager manager, Shader *shader) {
	return initModel(modelos_enum::albertossaurus, manager, shader, "../res/albertosaurus/albert.obj", "../res/albertosaurus/am.png", glm::vec3(-1.5, -3, 0), glm::vec3(0.5, 0.5, 0.5));
}

Object initGallimimus(Manager manager, Shader *shader) {
	return initModel(modelos_enum::gallimimus, manager, shader, "../res/gallimimus/galli.obj", "../res/gallimimus/gali.png", glm::vec3(-1.5, -3, 0), glm::vec3(0.5, 0.5, 0.5));
}

void initModelos(Manager manager, Shader *shader) {
	//Cria os modelos poss�veis de objetos, inclusive o ch�o
	modelos[modelos_enum::chao] = initChaoModelo(manager, shader);
	modelos[modelos_enum::brachiosaurus] = initBrachiosaurusModelo(manager, shader);
	modelos[modelos_enum::triceratops] = initTriceratopsModelo(manager, shader);
	modelos[modelos_enum::trex] = initTrexModelo(manager, shader);
	modelos[modelos_enum::spinosaurus] = initSpinosaurusModelo(manager, shader);
	modelos[modelos_enum::ankylosaurus] = initAnkylosaurusModelo(manager, shader);
	modelos[modelos_enum::ouranosaurus] = initOuranosaurusModelo(manager, shader);
	modelos[modelos_enum::albertossaurus] = initAlbertosaurus(manager, shader);
	modelos[modelos_enum::gallimimus] = initGallimimus(manager, shader);

	modeloSelecionadoIt = modelos.begin();
	modeloSelecionadoIt++;
}

Manager initCenaFromFile(std::string filePath, Manager manager, Shader *shader) {
	std::ifstream file;
	file.open(filePath.c_str());

	std::string line;
	if (file.is_open()) {

		while (file.good()) {

			getline(file, line);
			vector<std::string> tokens = split(line, ' ');

			if (tokens.size() == 10) {
				//Obtem o objeto pelo id salvo no txt
				Object tempModel = modelos.at(atoi(tokens[0].c_str()));

				//Seta as propriedades de posi��o, rota��o e escala
				tempModel.SetPos(glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str())));
				tempModel.SetRot(glm::vec3(atof(tokens[4].c_str()), atof(tokens[5].c_str()), atof(tokens[6].c_str())));
				tempModel.SetScale(glm::vec3(atof(tokens[7].c_str()), atof(tokens[8].c_str()), atof(tokens[9].c_str())));

				tempModel.SetShader(shader);
				//Adicona na lista de objetos que ser�o desenhados
				manager.ObjectList.push_back(tempModel);
			}

		}

	} else {
		std::cerr << "Unable to load cena: " << filePath << std::endl;
	}
	return manager;
}

void salvarCena(Manager manager) {
	ofstream file;
	file.open("../res/cena.txt");
	for each (Object object in manager.ObjectList){
		file << object.id << " " << object.GetPos().x << " " << object.GetPos().y << " " << object.GetPos().z << " ";
		file << object.getRot().x << " " << object.getRot().y << " " << object.getRot().z << " ";
		file << object.getScale().x << " " << object.getScale().y << " " << object.getScale().z << "\n";
	}
	file.close();
}

#undef main
int main(int argc, char** argv) {

	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Jurassic Park");

	Shader shader("../res/basicShader");

	Manager manager;

	initModelos(manager, &shader);
	//Inicia a cena, carregando do arquivo o que foi salvo. Retorna o gerenciador de objetos
	manager = initCenaFromFile("../res/cena.txt", manager, &shader);

	SDL_Event e;

	bool isRunning = true;
	float counter = 0.0f;
	while (isRunning)
	{
		display.updateFPS();
		GLuint currentFrame = SDL_GetTicks();
		deltaTime = (currentFrame - lastFrame) / 1000;
		lastFrame = currentFrame;

		GLfloat xoffset = m_mouseX - lastX;
		GLfloat yoffset = lastY - m_mouseY;
		lastX = m_mouseX;
		lastY = m_mouseY;

		GLfloat sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		glm::vec3 front;

		while (SDL_PollEvent(&e)){
			int newIndex;
			Object objectToInclude;

			switch (e.type) {
			case SDL_KEYDOWN:
				//Key Press
				switch (e.key.keysym.sym) {
				case SDLK_w:
					camera.setPosition(glm::vec3(camera.position().x, camera.position().y, camera.position().z + (camera.getSpeed() * deltaTime)));
					break;

				case SDLK_s:
					camera.setPosition(glm::vec3(camera.position().x, camera.position().y, camera.position().z - (camera.getSpeed() * deltaTime)));
					break;

				case SDLK_a:
					camera.setPosition(glm::vec3(camera.position().x + (camera.getSpeed() * deltaTime), camera.position().y, camera.position().z));
					break;

				case SDLK_d:
					camera.setPosition(glm::vec3(camera.position().x - (camera.getSpeed() * deltaTime), camera.position().y, camera.position().z));
					break;

				case SDLK_n:
					newIndex = manager.getSelectedObjectIndex() + 1;
					modeloSelecionadoIt = modelos.begin()++;
					if (newIndex < 1) 
						manager.setSelectedObjectIndex(1);
					else if (newIndex >= manager.ObjectList.size())
						manager.setSelectedObjectIndex(1);
					else
						manager.setSelectedObjectIndex(newIndex);
					break;

				case SDLK_m:
					//Obtem um objeto fixo da lista de objetos
					objectToInclude = modelos.at(modelos_enum::brachiosaurus);
					//Posicione ele onde estiver a camera
					objectToInclude.SetPos(glm::vec3(camera.position().x, 0.1, camera.position().z + 10.0));
					objectToInclude.SetShader(&shader);
					//Adiciona na lista de objetos da cena
					manager.ObjectList.push_back(objectToInclude);
					//Deixa o objeto selecionado
					manager.setSelectedObjectIndex(manager.ObjectList.size() - 1);
					break;

				case SDLK_SPACE:
					if (std::next(modeloSelecionadoIt) == modelos.end()) {
						modeloSelecionadoIt = modelos.begin();
						modeloSelecionadoIt++;
					}
					else {
						modeloSelecionadoIt++;
					}

					manager.alterarModeloObjetoSelecionado(modeloSelecionadoIt->second);
					break;

				case SDLK_b:
					manager.setSelectedObjectIndex(-1);
					break;

				case SDLK_x:
					manager.removeSelectedObject();
					break;

				case SDLK_i:
					manager.moverObjetoSelecionadoParaTras();
					break;

				case SDLK_k:
					manager.moverObjetoSelecionadoParaFrente();
					break;

				case SDLK_j:
					manager.moverObjetoSelecionadoEsquerda();
					break;

				case SDLK_l:
					manager.moverObjetoSelecionadoDireita();
					break;

				case SDLK_o:
					manager.rotacionarObjetoSelecionadoParaDireita();
					break;

				case SDLK_u:
					manager.rotacionarObjetoSelecionadoParaEsquerda();
					break;

				case SDLK_KP_PLUS:
				case SDLK_PLUS:
					manager.aumentarObjetoSelecionado();
					break;

				case SDLK_KP_MINUS:
				case SDLK_MINUS:
					manager.reduzirObjetoSelecionado();
					break;

				case SDLK_LEFT:
					front.x = camera.foward().x + 0.05;
					front.y = 0;
					front.z = 1;

					camera.setForward(glm::normalize(front));
					break;

				case SDLK_RIGHT:
					front.x = camera.foward().x - 0.05;
					front.y = 0;
					front.z = 1;

					camera.setForward(front);
					break;

				case SDLK_UP:
					front.x = camera.foward().x;
					front.y = camera.foward().y + 0.05;
					front.z = camera.foward().z;

					camera.setForward(front);
					break;

				case SDLK_DOWN:
					front.x = camera.foward().x;
					front.y = camera.foward().y - 0.05;
					front.z = camera.foward().z;

					camera.setForward(front);
					break;

				case SDLK_ESCAPE:
					isRunning = false;
					salvarCena(manager);
					break;

				default:
					break;
				}

				break;

			case SDL_KEYUP:
				//Key Release
				break;
				
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&m_mouseX, &m_mouseY);
				mouse_callback(m_mouseX, m_mouseY);
				break;
			case SDL_QUIT:
				isRunning = false;
				salvarCena(manager);
				break;
			default:
				break;
			}				
		}

		display.Clear(0.0f, 0.0f, 0.09f, 1.0f);
		
		shader.Bind();

		glm::vec3 lightPos(1.0, 1.0, 1.0);

		//Light
		glUniform3f(glGetUniformLocation(shader.Program(), "light.position"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.Program(), "light.ambient"), 0.9, 0.9, 0.9);
		glUniform3f(glGetUniformLocation(shader.Program(), "light.diffuse"), 0.5, 0.5, 0.5);
		glUniform3f(glGetUniformLocation(shader.Program(), "light.specular"), 1.0, 1.0, 1.0);

		for (int i = 0; i < manager.ObjectList.size(); i++) {
			Object object = manager.ObjectList.at(i);
			glUniform1d(glGetUniformLocation(shader.Program(), "selected"), i == manager.getSelectedObjectIndex());
			//Desenha os objetos na tela
			object.Draw(camera);
		}

		display.SwapBuffers();
		SDL_Delay(1);
		counter += 0.01f;
	}

	return 0;
}

void mouse_callback(double xpos, double ypos)
{		
	//printf("%d - %d \n", xpos, ypos);

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	//camera.setForward(glm::normalize(front));
	//camera.setPosition(glm::vec3(camera.position().x - (camera.getSpeed() * deltaTime), camera.position().y, camera.position().z));
}