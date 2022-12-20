#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ll long long int

typedef struct SYMTAB
{
    char label[30];
} symtab;

long long int hex_to_int(char hstr[])
{
    // converts hexadecimal to decimal integer
    ll ans = 0;
    // there is a catch in this oftern the hstr has endline i.e '\n' at end so check that as well
    for (int i = 0; hstr[i] != '\0' && hstr[i] != '\n'; i++)
    {
        ans = (ans * 16) + (hstr[i] - '0');
    }
    return ans;
}

void main() {
    char opcode[10], operand[10], label[10], code[10], mnemonic[10];
    int locctr, start, length;
    symtab smtb[100];
    int smtb_len = 0;

    FILE *fp1, *fp2, *fp3, *fp4, *fp5;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("out.txt", "w");
    fp5 = fopen("length.txt", "w");

    fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);

    if(strcmp(opcode, "START")==0) {
        start = hex_to_int(operand);
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }
    else {
        locctr = 0;
    }
    int flag = 0;
    while(strcmp(opcode, "END")!=0) {
        fprintf(fp4, "%X\t", locctr);

        if(strcmp(label, "**")!=0) 
        {
            for (int i = 0; i < smtb_len; i++)
            {
                if (strcmp(smtb[i].label, label) == 0)
                {
                    printf("DUPLICACY Error\n");
                    flag = 1;
                    exit(0);
                }
            }
            if(!flag)
            {
                fprintf(fp3, "%s\t%X\n", label, locctr);
                strcpy(smtb[smtb_len].label, label);
                smtb_len++;
            }
        }

        fscanf(fp2, "%s\t%s", code, mnemonic);

        while(strcmp(code, "END")!=0) {
            if(strcmp(opcode, code)==0) {
                locctr+=3;
                break;
            }
            fscanf(fp2, "%s\t%s", code, mnemonic);
        }

        if(strcmp(opcode, "WORD")==0) {
            locctr+=3;
        }
        else if(strcmp(opcode, "RESW")==0) {
            locctr+=(3*(atoi(operand)));
        }
        else if(strcmp(opcode, "RESB")==0) {
            locctr+=(atoi(operand));
        }
        else if(strcmp(opcode, "BYTE")==0) {
            ++locctr;
        }

        fprintf(fp4, "%s\t%s\t%s\t\n", label, opcode, operand);
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }

    fprintf(fp4, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    length = locctr-start;

    fprintf(fp5, "%d", length);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
}