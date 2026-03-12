// binary codes for seven segment display
//   
// A  __
// F |  | B
//  G __
// E |  | C
// D  __   . DP
//
//
//  0bABCDEFG{DP}
#define DP 0b10000000
#define A  0b01000000
#define B  0b00100000
#define C  0b00010000
#define D  0b00001000
#define E  0b00000100
#define F  0b00000010
#define G  0b00000001

#define ZERO_7SD  (A|B|C|D|E|F)
#define ONE_7SD   (B|C)
#define TWO_7SD   (A|B|G|E|D)
#define THREE_7SD (A|B|G|C|D)
#define FOUR_7SD  (F|G|B|C)
#define FIVE_7SD  (A|F|G|C|D)
#define SIX_7SD   (A|F|G|C|D|E)
#define SEVEN_7SD (A|B|C)
#define EIGHT_7SD (A|B|C|D|E|F|G)
#define NINE_7SD  (A|F|G|B|C)
#define ERROR_7SD G