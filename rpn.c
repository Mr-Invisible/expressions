#include "rpn.h"


uint8_t isBufferEmpty(rpnHandle_t* handle) {
    uint8_t status = 0;
    if (handle->start == -1) {
        status = 1;
    }
    return status;
}

uint8_t isStackEmpty(rpnHandle_t* handle) {
    uint8_t status = 0;
    if (handle->end == handle->capacity) {
        status = 1;
    }
    return status;
}

rpnToken_t bufferPeak(rpnHandle_t* handle) {
    return handle->buffer[handle->start];
}

rpnToken_t stackPeak(rpnHandle_t* handle) {
    return handle->buffer[handle->end];
}

rpnToken_t bufferPop(rpnHandle_t* handle) {
    rpnToken_t token = {.type = rpnTypeUnknown, .object.operator = rpnOperatorUnknown};
    if (!isBufferEmpty(handle)) {
        token = handle->buffer[handle->start--];
    }
    return token;
}

rpnToken_t stackPop(rpnHandle_t* handle) {
    rpnToken_t token = {.type = rpnTypeUnknown, .object.operator = rpnOperatorUnknown};
    if (!isStackEmpty(handle)) {
        token = handle->buffer[handle->end++];
    }
    return token;
}

rpnStatus_t bufferPush(rpnHandle_t* handle, rpnToken_t token) {
    rpnStatus_t status = rpnStatusOk;
    if ((handle->start + 1) != handle->end) {
        handle->buffer[++handle->start] = token;
    } else {
        status = rpnStatusErrorSize;
    }
    return status;
}

rpnStatus_t stackPush(rpnHandle_t* handle, rpnToken_t token) {
    rpnStatus_t status = rpnStatusOk;
    if ((handle->end - 1) != handle->start) {
        handle->buffer[--handle->end] = token;
    } else {
        status = rpnStatusErrorSize;
    }
    return status;
}

uint8_t getPrecedence(rpnToken_t token) {
    uint8_t precedence = 0;
    if (token.type == rpnTypeOperator) {
        switch (token.object.operator) {
            case rpnOperatorMinus:
            case rpnOperatorPlus:
                precedence = 1;
                break;
            case rpnOperatorMultiply:
            case rpnOperatorDivide:
            case rpnOperatorModulus:
                precedence = 2;
                break;
            case rpnOperatorExponent:
            case rpnOperatorSqrt:
                precedence = 3;
                break;
        }
    }
    return precedence;
}

uint8_t isOperator(rpnToken_t token) {
    uint8_t status = 0;
    if (token.type == rpnTypeOperator) {
        status = 1;
    }
    return status;
}

uint8_t isOperand(rpnToken_t token) {
    uint8_t status = 0;
    if (token.type == rpnTypeOperand) {
        status = 1;
    }
    return status;
}

void rpnInit(rpnHandle_t* handle, rpnToken_t* tokens, uint32_t size) {
    handle->start = -1;
    handle->end = size;
    handle->capacity = size;
    handle->buffer = tokens;
}

rpnStatus_t rpnAddToken(rpnHandle_t* handle, rpnToken_t token) {
    rpnStatus_t status = rpnStatusOk;
    if (isOperand(token)) {
        status = bufferPush(handle, token);
    } else if (token.object.operator == rpnOperatorBracketOpen) {
        status = stackPush(handle, token);
    } else if (token.object.operator == rpnOperatorBracketClose) {
        while (!isStackEmpty(handle) && stackPeak(handle).object.operator != rpnOperatorBracketOpen) {
            status = bufferPush(handle, stackPop(handle));
        }
        if (!isStackEmpty(handle) && stackPeak(handle).object.operator == rpnOperatorBracketOpen) {
            stackPop(handle);
        }
    } else {
        while (!isStackEmpty(handle) && getPrecedence(token) < getPrecedence(stackPeak(handle))) {
            status = bufferPush(handle, stackPop(handle));
        }
        if (status == rpnStatusOk) {
            status = stackPush(handle, token);
        }
    }
    return status;
}



