#include "BetterStop.h"
#include "Config.h"

#include <ll/api/Config.h>
#include <ll/api/Logger.h>
#include <ll/api/command/Command.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/data/Version.h>
#include <ll/api/memory/Hook.h>
#include <ll/api/plugin/NativePlugin.h>
#include <ll/api/plugin/RegisterHelper.h>
#include <ll/api/service/Bedrock.h>
#include <ll/api/utils/StringUtils.h>
#include <mc/server/commands/CommandRawText.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandPermissionLevel.h>
#include <mc/server/commands/CommandRegistry.h>
#include <mc/server/common/DedicatedServer.h>
#include <mc/server/common/commands/StopCommand.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/level/Level.h>
#include <memory>

#define VERSION ll::data::Version(3, 0, 0)
ll::Logger          logger(fmt::format(fg(fmt::color::aqua), "BetterStop"));
Better_Stop::Config config;

namespace Better_Stop {

static std::unique_ptr<BetterStop> instance;

BetterStop& BetterStop::getInstance() { return *instance; }

bool BetterStop::load() {
    logger.info("BetterStop-{} Loaded!", VERSION.to_string());
    const auto& configFilePath = getSelf().getConfigDir() / "config.json";
    try {
        if (!ll::config::loadConfig(config, configFilePath))
            logger.warn("读取配置文件 {} 失败，将写入默认配置文件。", configFilePath);
        if (!ll::config::saveConfig(config, configFilePath)) logger.error("无法保存默认配置文件至 {}", configFilePath);
    } catch (...) {
        logger.warn("读取配置文件 {} 失败，将写入默认配置文件。", configFilePath);
        if (!ll::config::saveConfig(config, configFilePath)) logger.error("无法保存默认配置文件至 {}", configFilePath);
    }   
    return true;
}

bool BetterStop::enable() {
    auto& cmd = ll::command::CommandRegistrar::getInstance()
                    .getOrCreateCommand("stop", "commands.stop.description", CommandPermissionLevel::Owner);
    struct cmdParam {
        CommandRawText reason;
    };
    cmd.overload<cmdParam>().execute([](CommandOrigin const& origin, CommandOutput& output) {
        output.success("commands.stop.start");
        ll::service::getLevel()->forEachPlayer([&](Player& player) -> bool {
            player.disconnect(config.default_tip);
            return true;
        });
        StopCommand::mServer->requestServerShutdown("");
    });
    cmd.overload<cmdParam>().required("reason").execute([](CommandOrigin const& origin,
                                                           CommandOutput&       output,
                                                           cmdParam const&      param) {
        output.success("commands.stop.start");
        ll::service::getLevel()->forEachPlayer([&](Player& player) -> bool {
            player.disconnect(ll::string_utils::replaceAll(config.reason_tip, "${Reason}", param.reason.getText()));
            return true;
        });
        StopCommand::mServer->requestServerShutdown("");
    });
    return true;
}

bool BetterStop::disable() { return true; }

} // namespace Better_Stop

LL_REGISTER_PLUGIN(Better_Stop::BetterStop, Better_Stop::instance);