#include <stdlib.h>

#include "loggerutils.h"

int main(int argc, char ** argv)
{
    log_debug(__FILE__, __LINE__, "THIS IS A DEBUG");
    log_warning(__FILE__, __LINE__, "THIS IS A WARNING");
    log_error(__FILE__, __LINE__, "THIS IS AN ERROR");
    exit(0);
}

