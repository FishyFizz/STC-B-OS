
#define BIT(x) ((u8)(1<<(x)))
#define CLEARBIT(var, bit) {(var) &= ~(1<<(bit));}
#define SETBIT(var, bit) {(var) |= (1<<(bit));}
#define INVOF(bit) ((bit==0)?1:0)
#define WRITEBIT(var, bit, wrt) {CLEARBIT(var,bit); var|=(((u8)(wrt))<<(bit));}
#define GETBIT(var,bit) (((var)&BIT(bit))?1:0)

#define RSL(var) (((var)<<1) + ((var)>>7))
