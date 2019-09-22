# Reverse Polish Notation - C Library

**Reverse Polish Notation (RPN)**, also known as **Postfix Notation** splits mathmatical notation into eperands and operators. RPN does not require brackets for order of precedence. More information can be found on this [wiki-page](https://en.wikipedia.org/wiki/Reverse_Polish_notation). This c library provide a simple stack interface for inputing Infix Notation and converting it to Postfix Notation.

# Usage

Create an RPN Handle:
```c
rpnHandle_t handle;
```

Create an RPN Token buffer:
```c
rpnToken_t buffer[BUFFER_SIZE] = {0};
```

Initialize Handle. Provide pointer to handle, buffer, and size of buffer.
```c
rpnInit(&handle, buffer, BUFFER_SIZE);
```

To add a Token to buffer:
```c
rpnStatus_t status;
rpnToken_t token = {.type = rpnTypeOperand, .object.operand = 2};
status = rpnAddToken(&handle, token);
```





