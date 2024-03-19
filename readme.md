<!-- markdownlint-disable MD033 -->

# BetterStop

给关服加上原因。
![Alt text](https://raw.github.com/zimuya4153/BetterStop/main/src/img/1.png)
![Alt text](https://raw.github.com/zimuya4153/BetterStop/main/src/img/2.png)

```jsonc
{
    "default": "§c服务器已关闭!",// 无原因提示
    "default2": "§c服务器已关闭!\n§a原因§6:§b${Reason}",// 有原因提示
    "time": 0.5,// 多久后关服(不建议太快 单位:秒)
}
```

## 更新日志

### 0.0.2
  - 添加玩家执行命令监听，支持控制台权限的玩家执行stop时加上原因
### 1.0.0
  - 添加配置文件，支持自定义
