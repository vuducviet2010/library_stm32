



																												// Boundary address of Reset and clock control ( RCC )
#define RCC_APB2ENR       (*((volatile unsigned long *) 0x40021018))
																																//0x18 ( address )
																									// Boundary address of GPIO Port A
#define GPIO_A       		 (*((volatile unsigned long *) 0x40010800))
	
																									// Boundary address of GPIO Port B
#define GPIO_B       		 (*((volatile unsigned long *) 0x40010C00))
	
																									// Boundary address of GPIO Port C
#define GPIO_C       		 (*((volatile unsigned long *) 0x40011000))

// list of Ports
#define PortA          1           
#define PortB          2           
#define PortC          3          

// Status definition
#define HIGH       1
#define LOW        0

// Directions						
#define  INPUT     0		// Input mode (reset state)
#define  OUT10     1    // Output mode, max speed 10 MHz
#define  OUT2      2    // Output mode, max speed 2  MHz
#define  OUT50     3    // Output mode, max speed 50 MHz

// Direction options for input
#define IN_AN 0					// Analog mode
#define IN_F  1         // Floating input (reset state)
#define IN_PP 2         // Input with pull-up / pull-down


// Direction options for output
#define OUT_GP_PP 0			// General purpose output push-pull
#define OUT_GP_OD 1     // General purpose output Open-drain
#define OUT_AF_PP 2     // Alternate function output Push-pull
#define OUT_AF_OD 3     // Alternate function output Open-drain





void PINc(unsigned short pin, unsigned short STATUS);


void init_GP(unsigned short PORT,unsigned short PIN,unsigned short DIR,unsigned short OPT);

int Read_GP(unsigned short PORT,unsigned short pin);
void Write_GP(unsigned short PORT,unsigned short pin, unsigned short STATUS);
void toggle_GP(unsigned short Port,unsigned short pin);

void BLED(unsigned short state);


void B_init(void);
