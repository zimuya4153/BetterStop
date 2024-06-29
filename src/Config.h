#include <string>

namespace Better_Stop {
struct Config {
    int         version     = 1;
    std::string default_tip = "§c服务器已关闭。";
    std::string reason_tip  = "§c服务器已关闭!\n§a原因§6:§b${Reason}";
};
} // namespace Better_Stop