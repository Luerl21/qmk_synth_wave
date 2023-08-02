// Copyright 2023 RephlexZero (@RephlexZero)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "quantum.h"

enum via_dynamic_actuation {
    id_animation = 1,
};

//struct to save configs
typedef struct {
    uint8_t animation: 8;
} via_config; // 48 bits
extern via_config g_config;

// function declaration
void via_config_set_value(uint8_t *data);

void via_config_get_value(uint8_t *data);