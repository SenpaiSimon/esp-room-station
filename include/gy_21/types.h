#pragma once

typedef union gy_user_config {
    struct bits {
        bool test : 1;
    };
    unsigned int data;
} gy_user_config_t;
