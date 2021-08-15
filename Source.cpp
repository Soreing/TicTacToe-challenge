#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>

long long var = 0;
// .---------------.---------------------.---------.--------.---------.---------.--------.---------.
// |     byte-8    |        byte-7       |  byte-6 | byte-5 | byte-4  |  byte-3 | byte-2 | byte-1  |
// |-----.---------|-----.-----.---------|---------|--------|---------|---------|--------|---------|
// |  0  | 0000000 | 000 |  0  | 00 | 00 | 00000000 00000000 00000000 | 00000000 00000000 00000000 |
// | end | input/i | res | err |  r |  c |  Player2's win conditions  |  Player1's win conditions  |
// '-----'---------'-----'-----'----'----'----------------------------'----------------------------'

int main()
{
	for (; var>=0 ; var ^=0x10000000000000, *((char*)&var + 6) &= 0xF0)
	{	
		printf("Player %d's turn! [r c]: ", (var & 0x10000000000000 ? 2 : 1));
		scanf(" %c", ((char*)&var) + 7);
		*((char*)&var + 6) |= ((*(((char*)&var) + 7) < '0' || *(((char*)&var) + 7) > '2') ? 3  : ((*((char*)&var + 7) - '0') & 7));
		scanf(" %c", ((char*)&var) + 7);
		*((char*)&var + 6) |= ((*(((char*)&var) + 7) < '0' || *(((char*)&var) + 7) > '2') ? 12 : ((((*((char*)&var + 7) - '0') & 7)<<2)));

		if ((*((char*)&var + 6) & 3) == 3 || ((*((char*)&var + 6) & 12) >> 2) == 3 ||
			((var & (1LL << ((*((char*)&var + 6) & 3) * 3 + ((*((char*)&var + 6) & 12) >> 2)))) ||
			(var & (1LL << ((*((char*)&var + 6) & 3) * 3 + ((*((char*)&var + 6) & 12) >> 2) + 24)))))
			printf("Wrong Input! Try again..\n\n", var ^= 0x10000000000000);

		else
		{
			*(int*)((char*)&var + (var & 0x10000000000000 ? 3 : 0)) |=
				(long long)((1 << ((*((char*)&var + 6) & 3) * 3 + ((*((char*)&var + 6) & 12) >> 2))) |
				(1 << (((*((char*)&var + 6) & 12) >> 2) * 3 + (*((char*)&var + 6) & 3) + 9))) |
				(((1 << ((*((char*)&var + 6) & 3) + ((*((char*)&var + 6) & 3) - ((*((char*)&var + 6) & 12) + 2)>>2) * 3)) & 448) << 12) |
				(((1 << ((*((char*)&var + 6) & 3) + ((*((char*)&var + 6) & 3) + ((*((char*)&var + 6) & 12) + 2) >>2) * 3)) & 448) << 15);

			std::cout << (var&0x0000FFFFFFFFFFFF)<<"\n";

			printf("\n%c %c %c\n%c %c %c\n%c %c %c\n\n",
				var & 0x001 ? 'x' : var & 0x001000000 ? 'o' : '-', var & 0x002 ? 'x' : var & 0x002000000 ? 'o' : '-', var & 0x004 ? 'x' : var & 0x004000000 ? 'o' : '-',
				var & 0x008 ? 'x' : var & 0x008000000 ? 'o' : '-', var & 0x010 ? 'x' : var & 0x010000000 ? 'o' : '-', var & 0x020 ? 'x' : var & 0x020000000 ? 'o' : '-',
				var & 0x040 ? 'x' : var & 0x040000000 ? 'o' : '-', var & 0x080 ? 'x' : var & 0x080000000 ? 'o' : '-', var & 0x100 ? 'x' : var & 0x100000000 ? 'o' : '-');

			for (*(((char*)&var) + 7) = 0; (*(((unsigned char*)&var) + 7) & 0x1F) < 16; (*(((char*)&var) + 7))++)
				*((char*)&var + 7) ^= (((var & (7 << (*(((char*)&var) + 7) * 3))) == (7 << (*(((char*)&var) + 7) * 3))) << 7);

			if (*((char*)&var + 7) & 0x80)
				printf("Player %d Won!\n", (var & 0x10000000000000 ? 2 : 1));

			if(  ((*(int*)&var | *(int*)((char*)&var+3)) & 0x1FF) == 0x1FF)
				printf("It's a Draw!\n");
		}
	}

	scanf(" %c", ((char*)&var) + 7);
}
