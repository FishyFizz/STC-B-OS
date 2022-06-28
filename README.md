# STC-B-OS
## A minimal OS for HNU STC-B.

To test out the code, clone repository and open directly in Keil.

- Drivers for frequently used board components
- Up to 7 user processes
- Preemptive RR scheduer
- Process start / kill / sleep / yield API support
- Supports concurrent programming. Up to 8 semaphores usable
- Event driven system, user process do not need to poll hardware states



## 适用于湖南大学STC-B开发板的极简操作系统。

使用时直接Clone整个仓库，在Keil中打开工程。

- 包含板上常用硬件驱动
- 支持最多7个用户进程
- 抢占式RR进程调度器
- start / kill / sleep / yield 进程操作支持
- 支持并发编程，至多8个信号量可用
- 基于事件驱动的系统，用户进程无需轮询硬件状态
