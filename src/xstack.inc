KERNEL_XSTACKSIZE EQU 32
PROCESS_XSTACKSIZE EQU 64

EXTERN XDATA (KERNEL_XSTACK, PROCESS_XSTACK)
EXTERN DATA (?C_XBP)
EXTERN CODE (GETXBP, SETXBP)