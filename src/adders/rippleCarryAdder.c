#include<stdio.h>

void writeFA(FILE * fp)
{
	fprintf(fp, "module FullAdder(A, B, Cin, Cout, Sum);\n");
	fprintf(fp, "\tinput A, B, Cin;\n");
	fprintf(fp, "\toutput Cout, Sum;\n\n");
	fprintf(fp, "\tassign Sum = A^B^Cin;\n");
	fprintf(fp, "\tassign Cout = (A^B)&Cin | (A&B);\n");
	fprintf(fp, "endmodule\n");
	return;
}


void writeRCA(int n, FILE *fp)
{
	
	fprintf(fp, "module RippleCarryAdder(A, B, Cin, Cout, Sum);\n");

	fprintf(fp, "\tinput [%d : 0] A, B;\n", n-1);
	fprintf(fp, "\tinput Cin;\n");
	fprintf(fp, "\toutput [%d : 0] Sum;\n", n-1);
	fprintf(fp, "\toutput Cout;\n\n");

	fprintf(fp, "\twire c0 = Cin;\n");

	int i;
	for(i=0; i<n; i++)	
		fprintf(fp, "\tFullAdder fa%d(A[%d], B[%d], c%d, c%d, Sum[%d]);\n", i, i, i, i, i+1, i);		

	fprintf(fp, "\tassign Cout = c%d;\n", n);


	fprintf(fp, "endmodule\n\n");
	
	writeFA(fp);

	return;
}


int main()
{
	int n;
	printf("size of adder : ");
	scanf(" %d", &n);

	FILE *fp;
	fp = fopen("RCA.v", "w+");
	writeRCA(n, fp);
	fclose(fp);
}