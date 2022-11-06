# tf小作业——SunEarthMoon



#### 题目要求

1. rviz中显示三个坐标系，分别为太阳、地球和月球。前一个坐标系是后一个坐标系的父坐标系。

2. 地球围绕太阳公转；地球自转且自转轴斜着；月球围绕地球公转。

3. 使用marker，绘制太阳地球月球三个球体以及地球和月球的轨迹。

4. 深刻理解ros中时间戳的概念，tf坐标系必须在marker球体的中心。

5. 尝试不发布月球的tf坐标系就用marker绘出月球球体。



#### 提交方式

clone当前仓库到本地，创建自己的分支后push。并将结果展示给师兄看。分支用自己名字的拼音全拼。比如小明 xiaoming。



master分支只有题目，不要向master分支上推送。



#### 作业2：tf监听（写代码实现前先思考输出是什么）

- 实现两个节点，一个是tf的发布者，一个是tf的监听者。tf为baselink到map。

- 发布者从0开始每隔0.1秒发布一个baselink到map的位移，分别是0 0.1 0.2 0.3...

- 监听者监听并打印0.55秒 baselink到map的位移是多少。



#### 作业3：订阅者发布者缓冲机制（写代码实现前先思考输出是什么）

- 实现两个节点，一个发布者一个接受者。

- 发布者每0.5秒发布一个消息，0 0.5 1.0 1.5 ...  接受者在回调函数中打印消息。

- 接受者通过spinOnce+sleep的方式实现回调函数，接受者设置回调函数的长度为5。

- 尝试sleep为0.2 0.5 1 2 4 8 秒，查看输出结果。并思考为什么。