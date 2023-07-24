// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef AVR_PWM_USE_PWM0
#define AVR_PWM_USE_PWM0 TRUE

#undef AVR_PWM_USE_PWM4
#define AVR_PWM_USE_PWM4 TRUE

#undef AVR_SERIAL_USE_USART0
#define AVR_SERIAL_USE_USART0 TRUE
