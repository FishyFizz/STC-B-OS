# STC-B-OS Documentation


- **STC-B-OS** has 8 process slots in total. When ```main()``` calls ```start_scheduler()```, it becomes **Process 0**, used as display and event driver by default.

- Each process has its own 16-bytes stack. starting from ```i:0x80 + pid * 0x10```, so the stack area of 8 process take up all the ```idata``` memory. So any user process variables should be in ```xdata``` memory. Also be careful with nested function calls.

- User process can interact with hardware input by listening and waiting on **events**. Here's a simple example:
```
    wait_on_evts(EVT_BTN1_DN | EVT_BTN2_DN);
    //Process enters sleep state until one of the listened events occurs.
    if(MY_EVENTS & EVT_BTN1_DN)
        //do something.
    else if(MY_EVENTS & EVT_BTN2_DN)
        //do other things.
```

- When any serial port is active, all process are suspended. Which means  calls to ```rs485_write()``` and ```usbcom_write()``` are **blocking**.

- **Always reference examples in ```./test_process``` to learn how to write user process with STC-B-OS**