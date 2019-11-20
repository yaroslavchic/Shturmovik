#include <string>

using namespace std;

int get_height  (string adress)
{
	unsigned char info[54];
	FILE*f = fopen (adress.c_str() , "r");
	fread (info, sizeof (unsigned char), 54, f);
	int height =* (int*) &info[22];

	return height;
}
