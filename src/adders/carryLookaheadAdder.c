
#include<stdio.h>


void writeC(FILE *fp, int i)
{
	if(i==0)
	{
		fprintf(fp, "g%d | (p%d & c0)",i, i);
		return;
	}

	fprintf(fp, "g%d | (p%d & (", i, i);	writeC(fp, i-1);	fprintf(fp, "))");
	return;
}


void writeCLA(int n, FILE *fp)
{
	/*
		pi = a ^ b
		gi = a & b
 		si = pi ^ ci
		ci+1 = gi + (pi&ci);
	*/
	
	fprintf(fp, "module CarryLookaheadAdder(A, B, Cin, Cout, Sum);\n");

	fprintf(fp, "\tinput [%d : 0] A, B;\n", n-1);
	fprintf(fp, "\tinput Cin;\n");
	fprintf(fp, "\toutput [%d : 0] Sum;\n", n-1);
	fprintf(fp, "\toutput Cout;\n\n");

	int i;
	for(i=0; i<n; i++)
	{
		fprintf(fp, "\twire p%d = A[%d] ^ B[%d]; \twire g%d = A[%d] & B[%d];\n",i, i, i, i, i, i);
	}

	fprintf(fp, "\n");

	fprintf(fp, "\twire c0 = Cin;\n");

	for(i=1; i<=n; i++)
	{
		fprintf(fp, "\tassign c%d = ",i);
		writeC(fp, i-1); fprintf(fp, ";\n");
	}

	fprintf(fp, "\tassign Cout = c%d;\n\n",n);


	for(i=0; i<n; i++)
	{
		fprintf(fp, "\tassign Sum[%d] = p%d ^ c%d;\n",i, i, i);
	}
	
	fprintf(fp, "endmodule\n\n");
	return;
}


int main()
{
	int n;
	printf("size of adder : ");
	scanf(" %d", &n);

	FILE *fp;
	fp = fopen("CLA.v", "w+");
	writeCLA(n, fp);
	fclose(fp);
}