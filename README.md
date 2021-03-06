# Linux_DeviceDriver

原博主帖子: [linux设备驱动归纳总结](http://blog.chinaunix.net/uid-25014876-id-59420.html)

```js
该博主总结的相对基础和完整, 比较好入门Linux设备驱动, 但由于时间久远(已过去12年),
我计划是在原博主帖子基础之上, 把原博主的总结用实验Demo去验证的形式重新梳理纳入自己
的知识体系当中。

其实2016年就学习部分内容,但没记笔记,目前我总结到语雀,总结完成后分享出来。

重构理由:
1.原博客的排版相对难已阅读。
2.测试环境内核版本差异。
3.部分内容存在错误。

实验机器:
  Linux ubuntu 5.13.0-44-generic #49~20.04.1-Ubuntu
```
# 以下的文章若有侵权，请马上与我联系

* linux设备驱动归纳总结（一）：内核的相关基础概念
* linux设备驱动归纳总结（二）：模块的相关基础概念
* linux设备驱动归纳总结（三）：1.字符型设备之设备申请
* linux设备驱动归纳总结（三）:2.open.close.read.write
* linux设备驱动归纳总结（三）：3面向对象思想和lseek
* linux设备驱动归纳总结（三）：4.ioctl的实现
* linux设备驱动归纳总结（三）：5.阻塞型IO实现
* linux设备驱动归纳总结（三）：6.poll和sellct
* linux设备驱动归纳总结（三）：7.异步通知fasync
* linux设备驱动归纳总结（四）：1.进程管理的相关概念
* linux设备驱动归纳总结（四）：2.进程调度的相关概念
* linux设备驱动归纳总结（四）：3.抢占和上下文切换
* linux设备驱动归纳总结（四）：4.单CPU下竞态和并发
* linux设备驱动归纳总结（四）：5.SMP下的竞态和并发
* linux设备驱动归纳总结（五）：1.在内核空间分配内存
* linux设备驱动归纳总结（五）：2.操作硬件——IO内存
* linux设备驱动归纳总结（五）：3.IO静态映射
* linux设备驱动归纳总结（五）：4.写个简单的LED驱动
* linux设备驱动归纳总结（六）：1.中断的实现
* linux设备驱动归纳总结（六）：2.分享中断号
* linux设备驱动归纳总结（六）：3.中断下半部之tasklet
* linux设备驱动归纳总结（六）:3.中断下半部之工作队列
* linux设备驱动归纳总结（七）：1.时间管理与内核延时
* linux设备驱动归纳总结（七）：2.内核定时器
* linux设备驱动归纳总结（八）：1.总线、设备和驱动
* linux设备驱动归纳总结（八）：2.match.probe.remove
* linux设备驱动归纳总结 (八) ：3.设备模型的分层与面向对象
* linux设备驱动归纳总结（八）：4.总线热插拔
* linux设备驱动归纳总结（九）：1.platform设备驱动
* linux设备驱动归纳总结（十）：1.udev&misc
* linux设备驱动归纳总结（十一）：简单的看门狗驱动
* linux设备驱动归纳总结（十二）：简单的数码相框          
* linux设备驱动归纳总结（十三）：1.触摸屏与ADC时钟         


