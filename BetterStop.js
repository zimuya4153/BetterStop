// LiteLoader-AIDS automatic generated
/// <reference path="d:\/dts/helperlib/src/index.d.ts"/> 

ll.registerPlugin(
    /* name */ "更好的关服",
    /* introduction */ "关服前踢出所有玩家，并显示原因。",
    /* version */[0, 0, 3],
    /* otherInformation */ {
        '作者': '子沐呀'
    }
);

let CONFIG = new JsonConfigFile('./plugins/BetterStop/Config.json', JSON.stringify({
    'default': '§c服务器已关闭!',// 无原因提示
    'default2': '§c服务器已关闭!\n§a原因§6:§b${Reason}',// 有原因提示
    'time': 0.5,// 多久后关服(不建议太快 单位:秒)
}))

/** 关服状态 */
let Stop = false;
mc.listen('onConsoleCmd', (Cmd) => {
    if (Cmd.split(' ')[0] != 'stop' || Stop) return;
    mc.getOnlinePlayers().forEach(Player => {
        Player.kick(CONFIG.get(Cmd.indexOf(' ') != -1 ? 'default2' : 'default').replace(/\$\{Reason\}/g, Cmd.slice(Cmd.indexOf(' '))));
    });
    setTimeout(() => mc.runcmdEx('stop'), CONFIG.get('time')*1000);
    Stop = true;
    return false;
});

mc.listen('onPlayerCmd', (Player, Cmd) => {
    if (Player.permLevel == 4 && Cmd.split(' ')[0] == 'stop') {
        mc.runcmdEx(Cmd);
        return false;
    }
});