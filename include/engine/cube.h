#ifndef ENGINE_CUBE_H_
#define ENGINE_CUBE_H_

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <vector>

#include "shader.h"
#include "image/stb_image.h"
#include "engine/utils.h"
#include "engine/engine.h"

struct Color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

// Intentionally left empty
const std::string DEFAULT_TEXTURE;
const Color DEFAULT_COLOR = {
  .r = 0,
  .g = 0,
  .b = 0
};

namespace cube {
const int g_cube_stride = 5;
const float vertices_cube[] = {
  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // TopBackLeft
  0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
  0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
  0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
  -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
  0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
  0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // BottomFrontRight
  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
  -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
  -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
  -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
  -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
  0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
  0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
  0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
  0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
  0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
  0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
  0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
  0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
  0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
  -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
  0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
  0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
  0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
  -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
  -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};
} // namespace cube

inline bool is_overlapping(
  const glm::vec3& bbl,
  const glm::vec3& tfr,
  const glm::vec3& corner
)
{

  const bool isX = bbl.x <= corner.x && corner.x <= tfr.x;
  const bool isY = bbl.y <= corner.y && corner.y <= tfr.y;
  const bool isZ = bbl.z <= corner.z && corner.z <= tfr.z;

  return isX && isY && isZ;
}

class Cube {

public:

  struct Collision {
    bool collide = false;
    size_t points = 0;
  };

  struct Scale {
    size_t x = 0;
    size_t y = 0;
    size_t z = 0;
  };

  enum class RotateDirection {
    X,
    Y,
    Z
  };

  Cube(const std::shared_ptr<Engine>& engine);
  Cube(
    const std::shared_ptr<Engine>& engine,
    const glm::vec3& position
  );
  Cube(
    const std::shared_ptr<Engine>& engine,
    const glm::vec3& position,
    const std::string& texture_name
  );

  Cube(
    const std::shared_ptr<Engine>& engine,
    const glm::vec3& position,
    const Color& color
  );

  Cube(
    const std::shared_ptr<Engine>& engine,
    const glm::vec3& position,
    const std::string& texture_name,
    const Color& color
  ); 

  Cube(const Cube& other);
  Cube& operator=(const Cube& other);

  const unsigned ShaderId() const;
  const int TextureId() const;
  const glm::mat4 TransformMatrix() const;
  const glm::mat4 ScaleMatrix() const;
  const glm::mat4 RotateMatrix() const;

  void Render();
  void SetPosition(const glm::vec3& position);
  void SetScale(const float scale);

  std::shared_ptr<Engine> Engine_Ptr() const;

  bool UseColor() const;
  void SetTexture(const std::string& texture_name);
  void SetColor(const Color color);
  Color GetColor() const;

  void Transform(const glm::vec3& position);
  void Rotate(float degrees, RotateDirection direction);
  void Scale(const float scale);
  void ScaleX(const float scale);
  void ScaleY(const float scale);
  void ScaleZ(const float scale);

  std::vector<glm::vec3> GetCorners() const;
  glm::vec3 GetPosition() const;
  glm::vec3 BottomBackLeft() const;
  glm::vec3 TopFrontRight() const;

  Collision IsColliding(const Cube& cube) const;

private:

  void FailLoadTexture();

  int m_texture_id;
  Color m_color;
  bool m_use_color;
  glm::mat4 m_transformation;
  glm::mat4 m_rotation;
  glm::mat4 m_scale;
  glm::mat4 m_model;
  const unsigned m_shader_id;

  // For shader ids and texture management
  std::shared_ptr<Engine> m_engine;

};

inline Cube::Cube(const std::shared_ptr<Engine>& engine) 
  : Cube(engine, glm::vec3(0.0f, 0.0f, 0.0f)) {}

inline Cube::Cube(const std::shared_ptr<Engine>& engine, const glm::vec3& position)
  : Cube(engine, position, DEFAULT_TEXTURE, DEFAULT_COLOR)
{}

inline Cube::Cube(
  const std::shared_ptr<Engine>& engine,
  const glm::vec3& position,
  const std::string& texture_name
)
  : Cube(engine, position, texture_name, DEFAULT_COLOR)
{}

inline Cube::Cube(
  const std::shared_ptr<Engine>& engine,
  const glm::vec3& position,
  const Color& color
)
  : Cube(engine, position, DEFAULT_TEXTURE, color)
{}

inline Cube::Cube(
  const std::shared_ptr<Engine>& engine,
  const glm::vec3& position,
  const std::string& texture_name,
  const Color& color
) : m_engine{engine},
    m_shader_id{engine->shader().m_ID},
    m_model{glm::mat4(1.0f)},
    m_transformation{glm::mat4(1.0f)},
    m_rotation{glm::mat4(1.0f)},
    m_scale{glm::mat4(1.0f)},
    m_texture_id{-1}
{

  Transform(position);

  SetColor(color);
  SetTexture(texture_name);
}

inline Cube::Cube(const Cube& other)
 : m_shader_id{other.ShaderId()},
   m_engine{other.Engine_Ptr()},
   m_texture_id{other.TextureId()},
   m_transformation{other.TransformMatrix()},
   m_scale{other.ScaleMatrix()},
   m_rotation{other.RotateMatrix()}
{
  // Figure out for texture
  if(other.UseColor()) {
    SetColor(other.GetColor()); 
  }
}

inline Cube& Cube::operator=(const Cube& other) {
  if(this == &other) {
    return *this;
  }

  m_engine = other.Engine_Ptr();
  m_texture_id = other.TextureId();
  m_transformation = other.TransformMatrix();
  m_scale = other.ScaleMatrix();
  m_rotation = other.RotateMatrix();

  if(other.UseColor()) {
    SetColor(other.GetColor());
  }

  return *this;
}

inline const unsigned Cube::ShaderId() const {
  return m_shader_id;
}

inline const int Cube::TextureId() const {
  return m_texture_id;
}

inline const glm::mat4 Cube::TransformMatrix() const {
  return m_transformation;
}

inline const glm::mat4 Cube::RotateMatrix() const {
  return m_rotation;
}

inline const glm::mat4 Cube::ScaleMatrix() const {
  return m_scale;
}

inline void Cube::Render() {

  // Handle textures
  if(!m_use_color) {
    unsigned int use_texture_id = glGetUniformLocation(m_shader_id, "use_texture");
    if(m_texture_id == -1) {
      glUniform1i(use_texture_id, (int)false);
    } else {
      glUniform1i(use_texture_id, (int)true);

      // Probably not a good idea to bind every render call
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, m_texture_id);    
    }
  }

  // Handle color
  if(m_use_color) {
    unsigned int use_texture_id = glGetUniformLocation(m_shader_id, "use_texture");
    glUniform1i(use_texture_id, (int)false);

    unsigned int color_id = glGetUniformLocation(m_shader_id, "color");

    float r = ((float)m_color.r) / 255;
    float g = ((float)m_color.g) / 255;
    float b = ((float)m_color.b) / 255;
    glUniform4f(color_id, r, g, b, 1.0);
  }

  unsigned int model_id_trans = glGetUniformLocation(m_shader_id, "transform");
  unsigned int model_id_rotate = glGetUniformLocation(m_shader_id, "rotate");
  unsigned int model_id_scale = glGetUniformLocation(m_shader_id, "scale");

  glUniformMatrix4fv(model_id_trans, 1, GL_FALSE, glm::value_ptr(m_transformation));
  glUniformMatrix4fv(model_id_rotate, 1, GL_FALSE, glm::value_ptr(m_rotation));
  glUniformMatrix4fv(model_id_scale, 1, GL_FALSE, glm::value_ptr(m_scale));

  glDrawArrays(GL_TRIANGLES, 0, 36);
}

inline void Cube::SetPosition(const glm::vec3& position) {
  m_transformation = glm::mat4(1);
  m_transformation = glm::translate(m_transformation, position);
}

inline void Cube::Transform(const glm::vec3& position) {
  m_transformation = glm::translate(m_transformation, position);
}

inline void Cube::Rotate(float degrees, RotateDirection direction) {
  switch(direction) {
    case RotateDirection::X:
      m_rotation = glm::rotate(m_rotation, glm::radians(degrees), glm::vec3(1.0, 0.0, 0.0));
      break;
    case RotateDirection::Y:
      m_rotation = glm::rotate(m_rotation, glm::radians(degrees), glm::vec3(0.0, 1.0, 0.0));
      break;
    case RotateDirection::Z:
      m_rotation = glm::rotate(m_rotation, glm::radians(degrees), glm::vec3(0.0, 0.0, 1.0));
      break;
  }
}

inline void Cube::Scale(const float scale) {
  m_scale = glm::scale(m_scale, glm::vec3(scale));
}

inline void Cube::ScaleX(const float scale) {
  m_scale = glm::scale(m_scale, glm::vec3(scale, 1.0f, 1.0f));
}

inline void Cube::ScaleY(const float scale) {
  m_scale = glm::scale(m_scale, glm::vec3(1.0f, scale, 1.0f));
}

inline void Cube::ScaleZ(const float scale) {
  m_scale = glm::scale(m_scale, glm::vec3(1.0f, 1.0f, scale));
}

inline std::shared_ptr<Engine> Cube::Engine_Ptr() const {
  return m_engine;
}

inline bool Cube::UseColor() const {
  return m_use_color;
}

inline void Cube::SetTexture(const std::string& texture_name) {
  TextureStatus status = m_engine->texture_manager().get_texture(texture_name);

  if(!status.success) {
    m_texture_id = -1;
    m_use_color = true;
    return;
  }

  m_texture_id = status.texture_id;
  m_use_color = false;
}

inline void Cube::SetColor(const Color color) {

  m_use_color = true;
  m_color = color;

}

inline Color Cube::GetColor() const {
  return m_color;
}

inline std::vector<glm::vec3> Cube::GetCorners() const {
  std::vector<glm::vec4> corners = {
    {-0.5f, -0.5f, -0.5f, 1.0f}, // bottom_back_left
    {0.5, -0.5, -0.5, 1.0f},
    {-0.5, 0.5, -0.5, 1.0f},
    {0.5, 0.5, -0.5f, 1.0f},

    {-0.5f, -0.5f, -0.5f, 1.0f},
    {0.5, -0.5, 0.5, 1.0f},
    {-0.5f, 0.5f, 0.5f, 1.0f},
    {0.5f, 0.5f, 0.5f, 1.0f} // top_front_right
  };

  std::vector<glm::vec3> ret_corners;
  for(auto& corner : corners) {
    glm::vec3 ret_corner =
      m_transformation * m_rotation * m_scale * corner;

    ret_corners.push_back(ret_corner);
  }

  return ret_corners;
}

inline glm::vec3 Cube::GetPosition() const {
  return glm::vec3(
    m_transformation[3][0],
    m_transformation[3][1],
    m_transformation[3][2]
  );
}

inline glm::vec3 Cube::BottomBackLeft() const {
  const glm::vec4 vertex = {-0.5f, -0.5f, -0.5f, 1.0f};

  return m_transformation * m_rotation * m_scale * vertex;
}

inline glm::vec3 Cube::TopFrontRight() const {
  const glm::vec4 vertex = {0.5f, 0.5f, 0.5f, 1.0f};

  return m_transformation * m_rotation * m_scale * vertex;
}

inline Cube::Collision Cube::IsColliding(const Cube& cube) const {

  size_t points = 0;
  bool found_collision = false;

  glm::vec3 bbl = BottomBackLeft();
  glm::vec3 tfr = TopFrontRight();

  const auto corners_other = cube.GetCorners();
  for(const glm::vec3& corner : corners_other) {
    // utils::print_glm_vec(corner);
    if(is_overlapping(bbl, tfr, corner)) {
      found_collision = true;
      ++points;
    }
  }

  if(found_collision) {
    return {
      .collide = found_collision,
      .points = points
    };
  }

  // Check other cube
  glm::vec3 bbl_other = cube.BottomBackLeft();
  glm::vec3 tfr_other = cube.TopFrontRight();

  const std::vector<glm::vec3> corners_curr = GetCorners();
  for(const glm::vec3& corner : corners_curr) {
    if(is_overlapping(bbl_other, tfr_other, corner)) {
      found_collision = true;
      ++points;
    }
  }

  return {
    .collide = found_collision,
    .points = points
  };

}

inline void Cube::FailLoadTexture() {
  unsigned int use_texture_id = glGetUniformLocation(m_shader_id, "use_texture");
  glUniform1i(use_texture_id, (int)false);
  m_texture_id = -1;
}

#endif // ENGINE_CUBE_H_
