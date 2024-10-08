#ifndef SCENE_H
#define SCENE_H

#include <ludo/sprite.hpp>
#include <ludo/input.hpp>
#include <vector>
#include <set>
#include <functional>
#include <glm/ext.hpp>

namespace ludo
{
    class transform
    {
    public:
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;

        transform();
        transform(const glm::vec3 &_position, const glm::quat &_rotation, const glm::vec3 &_scale);
    };

    class camera
    {
    public:
        ludo::transform transform;
        glm::mat4 projection;

        camera();
        camera(const ludo::transform &_transform);
    };

    class scene;

    class gameobject
    {
    private:
        ludo::scene *m_scene_ptr;

    public:
        bool active;
        ludo::gameobject *parent;
        std::set<ludo::gameobject *> children_ptrs;
        ludo::transform local_transform;
        ludo::sprite *sprite_ptr;

        gameobject(ludo::scene *_scene);
        ludo::scene *get_scene() const;
        void attach_child_ptr(ludo::gameobject *_child_ptr);    // recommended way to attach children instead of std::set::insert()
        void draw(const glm::mat4 &_global_transform) const;
        virtual ~gameobject();
    };

    class event_listener : public gameobject
    {
    public:
        std::vector<std::function<void()>> callbacks;

        event_listener(ludo::scene *_scene);
        void listen(const glm::vec4 &_mouse_pos);
        void execute_callbacks();
    };

    class button : public event_listener
    {
    public:
        button(ludo::scene *_scene);
    };

    class scene
    {
    private:
        glm::mat4 m_ui_projection;
        static ludo::input::status s_left_mouse_previous_status;

    protected:
        std::vector<ludo::gameobject *> m_world_element_ptrs;
        std::vector<ludo::gameobject *> m_canvas_element_ptrs;

    public:
        ludo::camera main_camera;
        std::set<ludo::event_listener *> event_listener_ptrs;

        scene();
        void draw() const;
        virtual void on_update() = 0;
        virtual void on_late_update() = 0;
        void listen_events();
        void simulate_physics() const;
        virtual ~scene();
    };

    class scene_manager
    {
    private:
        static ludo::scene *s_previous_scene;
        static ludo::scene *s_current_scene;

    public:
        static void cleanup_previous_scene();
        static void set_current_scene(ludo::scene *_scene);
        static ludo::scene *get_current_scene();
    };
}

#endif