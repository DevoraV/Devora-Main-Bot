#include <iostream>
#include "bot.h"
#include "config.h"

int main() {
    Bot->run(Config->token(), Config->prefix());
    return 0;
}
