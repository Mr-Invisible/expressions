#include <stdio.h>

#include "rpn.h"

void printOperator(rpnToken_t token) {
    switch (token.object.operator) {
        case rpnOperatorMinus:
            printf("- ");
            break;
        case rpnOperatorPlus:
            printf("+ ");
            break;
        case rpnOperatorMultiply:
            printf("x ");
            break;
        case rpnOperatorDivide:
            printf("/ ");
            break;
        case rpnOperatorExponent:
            printf("^ ");
            break;
        case rpnOperatorSqrt:
            printf("~ ");
            break;
        case rpnOperatorBracketOpen:
            printf("{ ");
            break;
        case rpnOperatorBracketClose:
            printf("} ");
            break;
        case rpnOperatorEqual:
            printf("= ");
            break;
        default:
            break;
    }
}

void printBuffer(rpnHandle_t* handle, rpnToken_t* tokens) {
    for (uint32_t i = 0; i < handle->capacity; i++) {
        if (tokens[i].type == rpnTypeOperator) {
            printOperator(tokens[i]);
        } else {
            if (tokens[i].object.operand == 0) {
                printf("_ ");
            } else {
                printf("%.0f ", tokens[i].object.operand);
            }
        }
    }
}

int main() {
    
    uint8_t* test = "Solving, \" 2x(5+1)= \"";
    
    printf("%s\r\n\r\n", test);
    
    float answer;
    rpnHandle_t handle;
    rpnToken_t buffer[10] = {0};
    rpnStatus_t status;
    
    rpnInit(&handle, buffer, 10);
    printBuffer(&handle, buffer);   printf("   empty\r\n");
    status = rpnAddToken(&handle, (rpnToken_t){.type = rpnTypeOperand, .object.operand = 2});
    printBuffer(&handle, buffer);   printf("   add 2\r\n");
    status = rpnAddToken(&handle, (rpnToken_t){.type = rpnTypeOperator, .object.operator = rpnOperatorMultiply});
    printBuffer(&handle, buffer);   printf("   add x\r\n");
    status = rpnAddToken(&handle, (rpnToken_t){.type = rpnTypeOperator, .object.operator = rpnOperatorBracketOpen});
    printBuffer(&handle, buffer);   printf("   add {\r\n");
    status = rpnAddToken(&handle, (rpnToken_t){.type = rpnTypeOperand, .object.operand = 5});
    printBuffer(&handle, buffer);   printf("   add 5\r\n");
    status = rpnAddToken(&handle, (rpnToken_t){.type = rpnTypeOperator, .object.operator = rpnOperatorPlus});
    printBuffer(&handle, buffer);   printf("   add +\r\n");
    status = rpnAddToken(&handle, (rpnToken_t){.type = rpnTypeOperand, .object.operand = 1});
    printBuffer(&handle, buffer);   printf("   add 1\r\n");
    status = rpnAddToken(&handle, (rpnToken_t){.type = rpnTypeOperator, .object.operator = rpnOperatorBracketClose});
    printBuffer(&handle, buffer);   printf("   add }\r\n");
    status = rpnAddToken(&handle, (rpnToken_t){.type = rpnTypeOperator, .object.operator = rpnOperatorEqual});
    printBuffer(&handle, buffer);   printf("   add =\r\n");
    // status = rpnEvaluate(&rpnHandle, &answer);
    // if (status == rpnStatusOk) {
        printf("\r\n%f\r\n", answer);
    // } else {
        // printf("Error!");
    // }

    return 0;
}