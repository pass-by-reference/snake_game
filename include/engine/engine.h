#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

#include "shader.h"
#include "camera.h"

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Foward declare. Scene depends on engine.h
class SceneInterface;

struct TextureLoadData {
  int width;
  int height;
  int nr_channels;
  unsigned char* data;
};

struct TextureStatus {
  unsigned int texture_id;
  bool success;
};

class Engine {

public:

  class TextureManager {
  public:
    TextureManager() = default;

    TextureStatus get_texture(const std::string& texture_name);
  private:

    TextureStatus import_texture_file(
      const std::string& filename
    );
    TextureStatus load_texture(
      TextureLoadData& texture_data,
      const std::string extension
    );

    std::unordered_map<std::string, unsigned int> m_textures;
  };

  class SceneManager {
  public:
    SceneManager() = default;

    std::shared_ptr<SceneInterface> get_current_scene();
    void set_current_scene(const std::string& scene_name);
    std::string get_current_scene_name();

    bool add_scene(
      std::shared_ptr<SceneInterface> new_scene
    );
    void delete_scene(const std::string& scene_name);

  private:
    std::string m_current_active_scene;
    std::unordered_map<std::string, std::shared_ptr<SceneInterface>>
      m_scenes;
  };

  Engine(
    const std::string window_name,
    const std::string vertex_shader,
    const std::string fragment_shader,
    const float width,
    const float height
  );
  ~Engine();

  Camera& camera();
  Shader& shader();
  GLFWwindow* glfw_window();
  SceneManager& scene_manager();
  TextureManager& texture_manager();

  bool camera_pan();
  void camera_pan(bool);

  bool camera_move();
  void camera_move(bool);

  void reset_camera();

  void add_engine_instance(std::shared_ptr<Engine> engine);

  bool add_event(
    const std::string& scene_name,
    const std::string& event_name,
    const std::function<void(std::shared_ptr<Engine>)>& event_handler
  );

  bool invoke_event(
    const std::string& scene_name,
    const std::string& event_name
  );

  void loop();

  const std::string m_window_name;
private:
  
  // Hold instance to ptr to Engine when created
  // to be passed onto event handlers.
  std::shared_ptr<Engine> m_engine;

  TextureManager m_texture_manager;
  SceneManager m_scene_manager;
  // Double nested map
  // First layer is storing scene_name
  // Second layer is storing event_name
  std::unordered_map<
    std::string,
    std::unordered_map<
      std::string, std::function<void(std::shared_ptr<Engine>)>
    >
  > m_scene_events;

  GLFWwindow* m_window;
  Shader m_shader;
  Camera m_camera;

  float m_window_width;
  float m_window_height;

  unsigned int m_VAO, m_VBO;

  bool m_enable_cam_pan, m_enable_cam_move;

  glm::mat4 m_model;
  glm::mat4 m_view;
  glm::mat4 m_projection;

  unsigned int m_model_id;
  unsigned int m_projection_id;
  unsigned int m_view_id;

  float m_last_frame = 0.0f;
  float m_delta_time = 0.0f;

  void init_window();
  void init_vertex_buffers();
  void init_model_view_projection();
  void init_callbacks();
  void process_exit();
  void calculate_delta_time();

  void process_input_wasd();

  static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
  static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

};

// This is a helper function to
// create an engine instance
std::shared_ptr<Engine> create_engine(
  const std::string& window_name,
  const std::string& vertex_shader,
  const std::string& fragment_shader,
  const float width,
  const float height
);

#endif // ENGINE_ENGINE_H_
