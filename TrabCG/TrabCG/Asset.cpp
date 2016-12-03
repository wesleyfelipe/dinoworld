#include "Asset.h"

Asset::Asset()
{
}


Asset::~Asset()
{
}

void Asset::SetMesh(const std::string& meshPath)
{
	std::string name = meshPath.substr(meshPath.find_last_of('/') + 1, meshPath.find_last_of('.') - 1);

	std::cout << name;

	this->m_mesh = new Mesh(meshPath);
}

void Asset::SetShader(Shader* shader)
{
	this->m_shader = shader;
}

void Asset::SetPos(glm::vec3 pos)
{
	this->m_transform.SetPos(pos);
}

void Asset::SetRot(glm::vec3 rot)
{
	this->m_transform.SetRot(rot);
}

void Asset::SetScale(glm::vec3 scale)
{
	this->m_transform.SetScale(scale);
}

void Asset::alterarEscala(float a) {
	float x = this->m_transform.GetScale().x + a;
	float y = this->m_transform.GetScale().y + a;
	float z = this->m_transform.GetScale().z + a;

	this->SetScale(glm::vec3(x, y, z));
}

void Asset::aumentar() {
	this->alterarEscala(0.1);
}

void Asset::reduzir() {
	this->alterarEscala(-0.1);
}

void Asset::mover(float x1, float y1, float z1) {
	float x = this->m_transform.GetPos().x + x1;
	float y = this->m_transform.GetPos().y + y1;
	float z = this->m_transform.GetPos().z + z1;
	this->SetPos(glm::vec3(x, y, z));
}

void Asset::moverDireita() {
	this->mover(-0.2, 0.0, 0.0);
}

void Asset::moverEsquerda() {
	this->mover(0.2, 0.0, 0.0);
}

void Asset::moverParaFrente() {
	this->mover(0.0, 0.0, -0.2);
}

void Asset::moverParaTras() {
	this->mover(0.0, 0.0, 0.2);
}

void Asset::rotacionar(float a) {
	float x = this->m_transform.GetRot().x;
	float y = this->m_transform.GetRot().y + a;
	float z = this->m_transform.GetRot().z;
	this->SetRot(glm::vec3(x, y, z));
}

void Asset::rotacionarDireita() {
	this->rotacionar(0.2);
}

void Asset::rotacionarEsquerda() {
	this->rotacionar(-0.2);
}

void Asset::SetMaterial(std::string diffPath, std::string specPath)
{
	m_diffuse = new Texture(diffPath);
	m_specular = new Texture(specPath);
}

void Asset::Draw(const Camera& camera)
{
	//this->m_shader->Bind();

	//Bind material
	this->m_diffuse->Bind(0, m_shader);
	this->m_specular->Bind(1, m_shader);

	//glUniform1f(glGetUniformLocation(m_shader->Program(), "material.shininess"), m_material->shininess);

	this->m_shader->Update(m_transform, camera);
	this->m_mesh->Draw();

	//Unbind Material
	this->m_diffuse->Unbind();
	this->m_specular->Unbind();
}
