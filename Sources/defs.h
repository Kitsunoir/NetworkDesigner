//----------------------------------- defs.h -----------------------------------

#ifndef DEFS_H
#define DEFS_H

//     Matching network ID codes

#define NET_NONE    0
#define TWOCAP_L_I  1
#define TWOCAP_L_II 2
#define T_NET       3
#define CAPDIV      4
#define PI_NET      5
#define L_LOZ_I     6
#define L_LOZ_II    7
#define L_HIZ_I     8
#define L_HIZ_II    9

//     Constants

#ifndef PI
#define PI 3.141592653589793116
#endif

#define NETFIELDS  4

//                               Macro Functions

/*
        Name: ANGULAR

	Type: Real Macro function

	Parameters: Cyclic frequency (Hz)

	Returns: Angular frequency (rads/sec)
*/

#define ANGULAR(f) (6.283185307179586232*(f))

/*
        Name: CYCLIC

	Type: Real Macro Function

	Parameters: Angular frequency (rad/sec)

	Returns: Cyclic frequency (Hz)
*/

#define CYCLIC(w) ((w)/6.283185307179586232)

/*
        Name: POW2

	Type: Macro function

	Parameters: Real or Integer

	Returns: Square of arguement
*/

#define POW2(x) ((x)*(x))

/*
       Name: CEIL

       Type: Integer Macro Function

       Parameters: x (int) -- Length of string for which dynamic memory is
                   allocated.

       Returns: The next closest value that'll accomodate this string length.

       Note: Force carry by adding 15 to x. Next, bitwise AND with -16 to determine
             where the carry bit was set. Allocate sufficient memory for a string
	     that insures against malloc arena corruption.
*/

#define CEIL(x) (((x)+15) & -16)

#endif

//----------------------------------- defs.h -----------------------------------
