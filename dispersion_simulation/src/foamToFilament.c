#include "foamToFilament.h"
//#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "fstream"
#include <sys/stat.h>
#include <math.h>

//using namespace std;

/*void setNext(char* str)
{
	int carry= 0;
	//printf("**  %d  ", strlen(str));
	if(strlen(str) > strlen(dT))
		str[strlen(dT)-1] = '\0';
	while(strlen(str) < strlen(dT))
		strcat(str,"0");
	if(strlen(str) == strlen(dT))
	{
		int i;
		for(i = strlen(str)-1; i >= 0; i--)
		{
			if(str[i] == '.')
				continue;
			int j = (int)str[i] - (int)'0' + (int)dT[i] - (int)'0' + carry;
			if(j < 10)
			{
				str[i] = (char)(j+(char)'0');
				carry = 0;
			}
			else
			{
				str[i] = (char)(j%10) + '0';
				carry = j/10;
			}
		}
		if(carry != 0)		str = (char)(carry + (int)'0') + str;
	}
	while(str[strlen(str)-1] == '0')
		str[strlen(str)-1] = '\0';
	if(str[strlen(str)-1] == '.')
		str[strlen(str)-1] = '\0';
	//output is str
}
*/

void setNext1(char* str)
{

	int dotFlagDT = 0;
	int i = 0;
        for(i = 0; i < strlen(dT); i++)
                if(dT[i] == '.')
                {
                        dotFlagDT = i + 1;
                        break;
                }
        


	int dotFlagStr = 0;
	for(i = 0; i < strlen(str); i++)
		if(str[i] == '.')
		{
			dotFlagStr = i + 1;
			break;
		}
	
	//adjusting the dot point
	//char dTTemp [256];
	//strcpy(dTTemp, dT);
	if(dotFlagDT == 0)
	{
		//dotFlagDT = strlen(dTTemp)+1;
		//strcat(dTTemp, ".0");
		printf("Error: The constant dT is set incorrectly.Please add '.0' on the right side of dT\n");
	}
	if(dotFlagStr == 0)
	{
		dotFlagStr = strlen(str) + 1;
		strcat(str, ".0");
	}

	while(dotFlagStr < dotFlagDT)
	{
		for(i = strlen(dT); i >= 0; i--)
			str[i+1] = str[i];
		str[0] = '0';
		//strcat("0", str);
		dotFlagStr ++;
	}
	if(dotFlagStr > dotFlagDT)
		printf("Error: The constant dT is set incorrectly.Please add %d zero on the left side of dT\n", dotFlagStr-dotFlagDT);

	int carry = 0;
        //printf("**  %d  ", strlen(str));
        //if(strlen(str) > strlen(dT))
        //        str[strlen(dT)-1] = '\0';
        while(strlen(str) < strlen(dT))
                strcat(str,"0");
        if(strlen(str) >= strlen(dT))
        {
                int i;
                for(i = strlen(dT)-1; i >= 0; i--)
                {
                        if(str[i] == '.')
                                continue;
                        int j = (int)str[i] - (int)'0' + (int)dT[i] - (int)'0' + carry;
                        if(j < 10)
                        {
                                str[i] = (char)(j+(char)'0');
                                carry = 0;
                        }
                        else
                        {
                                str[i] = (char)(j%10) + '0';
                                carry = j/10;
                        }
                }
                if(carry != 0)
		{
			for(i = strlen(dT); i >= 0; i--)
				str[i+1] = str[i];
			str[0] = '1';
		//	str = strcat("1", str);
                //        str = (char)(carry + (int)'0') + str;
		}
        }
        while(str[strlen(str)-1] == '0')
                str[strlen(str)-1] = '\0';
        if(str[strlen(str)-1] == '.')
                str[strlen(str)-1] = '\0';
	while(str[0] == '0')
	{
		for(i = 0; i < strlen(dT); i++)
			str[i] = str[i+1];
	}
        //output is str
}

void setNext2(char* str)
{
	char dTCSV [10];
	strcpy(dTCSV, "001.0");
	int dotFlagDT = 0;
	int i = 0;
        for(i = 0; i < strlen(dTCSV); i++)
                if(dTCSV[i] == '.')
                {
                        dotFlagDT = i + 1;
                        break;
                }
        


	int dotFlagStr = 0;
	for(i = 0; i < strlen(str); i++)
		if(str[i] == '.')
		{
			dotFlagStr = i + 1;
			break;
		}
	
	//adjusting the dot point
	//char dTTemp [256];
	//strcpy(dTTemp, dT);
	if(dotFlagDT == 0)
	{
		//dotFlagDT = strlen(dTTemp)+1;
		//strcat(dTTemp, ".0");
		printf("Error: The constant dT is set incorrectly.Please add '.0' on the right side of dTcsv");
	}
	if(dotFlagStr == 0)
	{
		dotFlagStr = strlen(str) + 1;
		strcat(str, ".0");
	}

	while(dotFlagStr < dotFlagDT)
	{
		for(i = strlen(dTCSV); i >= 0; i--)
			str[i+1] = str[i];
		str[0] = '0';
		//strcat("0", str);
		dotFlagStr ++;
	}
	if(dotFlagStr > dotFlagDT)
		printf("Error: The constant dT is set incorrectly.Please add %d zero on the left side of dTcsv");

	int carry = 0;
        //printf("**  %d  ", strlen(str));
        //if(strlen(str) > strlen(dT))
        //        str[strlen(dT)-1] = '\0';
        while(strlen(str) < strlen(dTCSV))
                strcat(str,"0");
        if(strlen(str) >= strlen(dTCSV))
        {
                int i;
                for(i = strlen(dTCSV)-1; i >= 0; i--)
                {
                        if(str[i] == '.')
                                continue;
                        int j = (int)str[i] - (int)'0' + (int)dTCSV[i] - (int)'0' + carry;
                        if(j < 10)
                        {
                                str[i] = (char)(j+(char)'0');
                                carry = 0;
                        }
                        else
                        {
                                str[i] = (char)(j%10) + '0';
                                carry = j/10;
                        }
                }
                if(carry != 0)
		{
			for(i = strlen(dTCSV); i >= 0; i--)
				str[i+1] = str[i];
			str[0] = '1';
		//	str = strcat("1", str);
                //        str = (char)(carry + (int)'0') + str;
		}
        }
        while(str[strlen(str)-1] == '0')
                str[strlen(str)-1] = '\0';
        if(str[strlen(str)-1] == '.')
                str[strlen(str)-1] = '\0';
	while(str[0] == '0')
	{
		for(i = 0; i < strlen(dTCSV); i++)
			str[i] = str[i+1];
	}

        //output is str
}

int convert()
{
	//initialization
	FILE * infile;
	FILE * outfile1;
	FILE * outfile2;
	FILE * outfile3;
	mkdir("inputs", 0777);

	char name[256];
	char temp [256];
	temp[0] = '\0';

	double i;
	char output [256];
	output[0] = '0';
	output[1] = '.';
	output[2] = '\0'; //simulation will start at time 0 as defualt
	//printf("%s  ", output);

	for (i=startTime; i<(endTime-(deltaT/10)); i+=deltaT)
	{
		// read
		strcpy(temp, "");
		setNext1(output);
		strcat(temp, sT);
		strncat(temp, output, strlen(output));
		strcat(temp, st2);
		infile = fopen(temp, "r");
		printf("%s \n", temp);
		if (infile == NULL)
		{
			printf("* Error opening file \n");
			return 0;
		}
		int j;
		for(j = 0; j < 20 && !feof(infile); j++)
			fgets(name, 256, infile);
		int n = 0;
		
		fscanf(infile, "%d", &n);
		fgets(name, 256, infile);
		
		j = 0;
		char tmpStr1[30];
		char tmpStr2[30];
		char tmpStr3[30];
		char c = ' ';
		fscanf(infile, "%c", &c);
		// write X, Y, Z, Velocity.dat_U, Velocity.dat_W, Velocity.dat_V
		strcpy(temp, "inputs/Velocity");
		strcat(strncat(temp, output, strlen(output)), ".dat_U");
		outfile1 = fopen(temp, "w");
		strcpy(temp, "inputs/Velocity");
		strcat(strncat(temp, output, strlen(output)), ".dat_W");
		outfile2 = fopen(temp, "w");
		strcpy(temp, "inputs/Velocity");
		strcat(strncat(temp, output, strlen(output)),".dat_V");
		outfile3 = fopen(temp, "w");
		if (outfile1 == NULL || outfile2 == NULL || outfile3 == NULL)
		{
			printf("** Error opening file \n");
			return 0;
		}

		while (!feof(infile) && j < n)
		{
			fscanf(infile, "%c%c%s %s %s)\n", &c, &c, tmpStr1, tmpStr2, tmpStr3);
			tmpStr3[strlen(tmpStr3)-1] = '\0';
			j++;
			if(j % nY == 0)
			{
				fprintf(outfile1, "%s\n", tmpStr1);
				fprintf(outfile2, "%s\n", tmpStr2);
				fprintf(outfile3, "%s\n", tmpStr3);
			}
			else
			{
				fprintf(outfile1, "%s\t", tmpStr1);
				fprintf(outfile2, "%s\t", tmpStr2);
				fprintf(outfile3, "%s\t", tmpStr3);
			}
		}
		fclose(infile);
		fclose(outfile1);
		fclose(outfile2);
		fclose(outfile3);
	}

	// X Y Z
	outfile1 = fopen("inputs/Velocity.dat_X", "w");
	outfile2 = fopen("inputs/Velocity.dat_Y", "w");
	outfile3 = fopen("inputs/Velocity.dat_Z", "w");
	double cell_size_x, cell_size_y, cell_size_z;
	cell_size_x = cell_size_y = cell_size_z = 1;
	int k, ii;
	for(ii = 0; ii < nX; ii++)
	{
		int j;
		for(j = 0; j < nY; j++)
		{
			for(k = 0; k < nZ-1; k++)
			{
				fprintf(outfile1, "%f ", ii*cell_size_x + cell_size_x/2);
				fprintf(outfile2, "%f ", j*cell_size_y + cell_size_y/2);
				fprintf(outfile3, "%f ", k*cell_size_z + cell_size_z/2);
			}
			fprintf(outfile1, "%f\n", ii*cell_size_x + cell_size_x/2);
			fprintf(outfile2, "%f\n", j*cell_size_y + cell_size_y/2);
			fprintf(outfile3, "%f\n", k*cell_size_z + cell_size_z/2);
		}
	}
	fclose(outfile1);
	fclose(outfile2);
	fclose(outfile3);

	return 1;
}
