#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm.hpp>
#include <string>
#include <cstdint>
#include <GLES3/gl32.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>

namespace ludo
{
    class sprite
    {
    private:
        int32_t m_width = 0;
        int32_t m_height = 0;
        uint8_t *m_data = nullptr;
        GLuint m_texture = 0;
        static android_app *s_app;
        static std::string vertshader_source_str;
        static std::string fragshader_source_str;
        static GLuint s_vertex_buffer_object;
        static GLuint s_vertex_array_object;
        static GLuint s_element_buffer_object;
        static GLuint s_shader_program;
        static GLint s_transform_uniform_location;
        static GLint s_transparency_uniform_location;

    public:
        float transparency;

        sprite();
        explicit sprite(const std::string &_filepath);
        void setup_sprite(const std::string &_filepath);
        void draw(const glm::mat4x4 &_global_transform) const;
        ~sprite();
        static void initialise(android_app *const _app);
    };
}

#endif