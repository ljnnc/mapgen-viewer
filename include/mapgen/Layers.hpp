#ifndef LAYERS_H_
#define LAYERS_H_

#include <memory>
#include <SFML/Graphics.hpp>

class Layer : public sf::Drawable {
public:
  Layer(std::string name);
  bool needUpdate = true;
  bool enabled = true;
  bool damaged = true;
  std::string name = "";
  std::vector<sf::Drawable*> shapes;
  sf::Shader* shader = nullptr;
  void clear();
  void add(sf::Drawable* shape);
  void update(std::shared_ptr<sf::RenderWindow> w);
  Layer* mask = nullptr;
  sf::Shader* shader_mask;
  sf::RenderTexture* cache = nullptr;
  bool direct = false;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class LayersManager : public sf::Drawable {
private:
  std::shared_ptr<sf::RenderWindow> window;
  Layer* addLayer(std::string name);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  sf::Shader* shader_mask;

public:
  LayersManager(std::shared_ptr<sf::RenderWindow> w, sf::Shader* shader_mask);
  std::vector<Layer*> layers;

  Layer* getLayer(std::string name);
  void setLayerEnabled(std::string name, bool enabled);
  void setShader(std::string name, sf::Shader* shader);
  void setMask(std::string name, Layer* mask);

  void invalidateLayer(std::string name);
};

#endif
