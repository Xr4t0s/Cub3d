#include "cube3d.h"

unsigned int rgb24(int fc[3])
{
	return ((fc[0] & 0xFF) << 16 | ((fc[1] & 0xFF) << 8) | (fc[2] & 0xFF));
}