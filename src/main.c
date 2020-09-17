#include "spi1.h"

int main()
{
	int command;
	while(1)
	{
		printf("\nMENU\n"
			   "1 - Decode\n"
			   "2 - Encode\n"
			   "3 - Exit\n\n");
		if (!scanf("%d", &command))
			return -1;
		if (command == 3)
			break;
			
		printf("\nMENU\n"
			   "1 - First code\n"
			   "2 - Second code\n"
			   "3 - Third code\n"
			   "4 - Return\n\n");
		if (!scanf("%d", &code_type))
			return -1;
			
		if (code_type == 4)
			continue;
		printf("\nMENU\n"
		   "Enter the file name to input\n\n");
		if (!scanf("%s", fin_name))
			return -1;
		if (command == 2)
		{
			printf("\nMENU\n"
			   "Enter the file name to output\n\n");
			if (!scanf("%s", fout_name))
				return -1;
		}
		
		if (command == 2)
		{
			coder();
		}
		else
		{
			decoder();
		}
	}
    return 1;
}
