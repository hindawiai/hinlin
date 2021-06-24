<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 ARM Limited
 *
 * Try to mangle the ucontext from inside a संकेत handler, toggling
 * the mode bit to escalate exception level: this attempt must be spotted
 * by Kernel and the test हाल is expected to be termninated via SEGV.
 */

#समावेश "test_signals_utils.h"
#समावेश "testcases.h"

#समावेश "mangle_pstate_invalid_mode_template.h"

DEFINE_TESTCASE_MANGLE_PSTATE_INVALID_MODE(3h);
