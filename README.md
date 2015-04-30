# tower-defender
A tower defender game based on cocos2d-x

游戏视频演示：demo.mov
	
开发环境：
	OS-X Version: 10.10.2
	Xcode Version:6.1.1
   	开发语言： C++

游戏规则：
	1. 游戏预先定义了几波怪物，每波怪物沿着既定的路线循环行走，直到被消灭。
	2. 游戏中由4种炮塔，每种炮塔有不同的射击范围和自己对应的炮弹信息（可以个性化定制更多的炮塔）。
	3. 玩家把炮塔摆放在可以放置的位置，炮塔会自动的射击距离自己最近的怪物。
	4. 当游戏中得所有怪物被消灭时，即可过关。

文件说明:
	Resources--保存了游戏中所有的资源文件（图片，音频等）, 因为资源文件都是网上搜集的，怕版权原因所以为上传。
	Classes
	├── AppDelegate.cpp
	├── AppDelegate.h
	├── DataModel.cpp 该类用来保存游戏中得实时数据
	├── DataModel.h
	├── GameHUD.cpp 该类用来放置用户可操作的接口信息
	├── GameHUD.h
	├── GamePassScene.cpp 游戏“过关” 场景
	├── GamePassScene.h
	├── GameScene.cpp 游戏的主场景类，进入游戏
	├── GameScene.h
	├── LoadScene.cpp 游戏载入主界面，用来把游戏中用到的资源加入载入内存
	├── LoadScene.h
	├── MainMenuScene.cpp 菜单场景
	├── MainMenuScene.h
	├── Monster.cpp  该类定义怪物的超类及不同类型的怪物子类
	├── Monster.h
	├── Projectile.cpp 该类定义个子弹的超类及不同类型的子弹子类
	├── Projectile.h
	├── Tower.cpp 该类定义了塔防的超类及不同类型的子类
	├── Tower.h
	├── Wave.cpp 改了定义每波怪我的数量级产生速率
	├── Wave.h
	├── WayPoint.cpp 该类保存地图的路径信息。
	└── WayPoint.h
