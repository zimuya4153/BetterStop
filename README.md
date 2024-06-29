# 更好的关服

## 更好的关服，为你的关服，添加关服信息

### 使用BSD开源协议，允许用户自由使用、修改和分发代码，但要求用户必须标明原作者的协议。

> 此插件并没有采用监听，注册新命令等操作，所以与别的插件适配

### 怎么使用？

两种方法
- /stop —— 不输入原因，会使用配置文件默认的default_tip
- /stop <原因> —— 输入了原因，会使用配置文件的reason_tip，并将${Reason}替换成原因

### 配置文件
```javascript
{
    "version": 1, // 配置文件的版本
    "default_tip": "§c服务器已关闭。", // 默认关服提示
    "reason_tip": "§c服务器已关闭!\n§a原因§6:§b${Reason}", // 有原因关服提示
}
```


### 效果图

![image](https://s21.ax1x.com/2024/06/30/pkcudsK.png)
![image](https://s21.ax1x.com/2024/06/30/pkcurIH.png)
![image](https://s21.ax1x.com/2024/06/30/pkcuDde.png)
