#pragma

#include <SDL.h>

#include <Eigen/Dense>
#include <string>

namespace grp {

using Eigen::Vector2i;

class Window {
public:
    class InitializationError : public std::runtime_error {
    public:
        explicit InitializationError(const std::string &what_arg);
    };

    struct Dimensions {
        Vector2i position {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
        Vector2i size;
    };

    enum class Mode : uint32_t {
        Windowed   = 0,
        Fullscreen = SDL_WINDOW_FULLSCREEN
    };

    struct Settings {
        Dimensions dimensions;
        Mode mode {Mode::Windowed};
        std::string title;
    };

    explicit Window(Settings settings);
    ~Window();

    Window(const Window &)            = delete;
    Window(Window &&)                 = delete;
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&)      = delete;

    void clear() const;

    void update() const;

private:
    SDL_Window *window_;
    SDL_Surface *screen_surface_;
};
}  // namespace grp