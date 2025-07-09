#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CPF_SIZE 11
#define PARSED_CPF_SIZE 14
#define CPF_VAL 9

char *treat_input(const char *inp) {
    int inpt_s = strlen(inp);

    if (inpt_s != CPF_SIZE && inpt_s != PARSED_CPF_SIZE && inpt_s != CPF_VAL) {
        printf("%s\n", inp);
        perror("Invalid string");
        exit(1);
    }

    char *str = malloc((PARSED_CPF_SIZE) * sizeof(char));
    const char *i = inp;

    int c = 0;
    while (*i != '\0') {
        if (*i != '.' && *i != '-' && isdigit(*i)) {
            str[c] = *i;
            c++;
        }

        i++;
    }

    str[CPF_SIZE] = '\0';

    return str;
}


int calc_digits(const char *input, int lenght) {
    int p = lenght + 1;

    int sum = 0;
    for (int i = 0; i!=lenght; i++) {
        sum += (input[i] - '0') * p--;
    }

    int res = sum % 11;

    return (res < 2) ? 0 : 11 - res;
}


char *validate_digits(const char *input) {
    char *str = malloc(CPF_SIZE + 1);
    if (!str) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    strncpy(str, input, 9);

    str[9] = calc_digits(str, 9) + '0';
    str[10] = calc_digits(str, 10) + '0';
    str[11] = '\0';

    return str;
}


char *parse_cpf_string(const char *input) {
    char *parsed = malloc(PARSED_CPF_SIZE + 1);
    if (!parsed) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    snprintf(parsed, PARSED_CPF_SIZE + 1, "%.3s.%.3s.%.3s-%.2s",
             input, input + 3, input + 6, input + 9);
    return parsed;
}


int main(int argc, char **argv) {
    enum bool { false, true }; // later for validation

    char *input = (argv[1] != NULL) ? argv[1] : "333.444.555-66";
    char *val = treat_input(input);
    char *valid = validate_digits(val);
    char *parsed_val = parse_cpf_string(val);
    char *parsed_valid = parse_cpf_string(valid);

    //printf("%d\n", calc_digits(input, 9));
    printf("Given CPF:\t\t%s\nValidated CPF:\t\t%s\n", parsed_val, parsed_valid);
    
    void *all[] = {
        parsed_valid,
        parsed_val,
        valid,
        val
    };

    for (int i=0; i!= sizeof(all)/sizeof(all[0]); i++) {
        if (all[i] != NULL) {
            //printf("Clearing pointer\t%p\n", &all[i]);
            free(all[i]);
        }
    }

    return EXIT_SUCCESS;
}
