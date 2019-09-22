#ifndef _PRN_H_
#define _PRN_H_

#include <stdint.h>

typedef enum {
    rpnStatusOk,
    rpnStatusErrorSize,
    rpnStatusErrorFormat,
    rpnStatusUnknown,
} rpnStatus_t;

typedef enum {
    rpnTypeUnknown,
    rpnTypeOperand,
    rpnTypeOperator,
} rpnType_t;

typedef enum {
    rpnOperatorUnknown,
    rpnOperatorPlus,
    rpnOperatorMinus,
    rpnOperatorMultiply,
    rpnOperatorDivide,
    rpnOperatorModulus,
    rpnOperatorExponent,
    rpnOperatorSqrt,
    rpnOperatorBracketOpen,
    rpnOperatorBracketClose,
    rpnOperatorEqual,
} rpnOperator_t;

typedef struct {
    rpnType_t type;
    union {
        rpnOperator_t operator;
        float operand;
    } object;
} rpnToken_t;

typedef struct {
    uint32_t start;
    uint32_t end;
    uint32_t capacity;
    rpnToken_t* buffer;
} rpnHandle_t;

void rpnInit(rpnHandle_t* handle, rpnToken_t* tokens, uint32_t size);
rpnStatus_t rpnAddToken(rpnHandle_t* handle, rpnToken_t token);

#endif /*_PRN_H_*/