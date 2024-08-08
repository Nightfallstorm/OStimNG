#pragma once

namespace Threading {
    using ThreadFlags = uint32_t;

    enum ThreadFlag {
        NO_AUTO_MODE =      1 << 0,
        NO_PLAYER_CONTROL = 1 << 1,
        NO_UNDRESSING =     1 << 2,
        UNDRESS =           1 << 3
    };
}