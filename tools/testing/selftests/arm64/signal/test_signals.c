<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 ARM Limited
 *
 * Generic test wrapper क्रम arm64 संकेत tests.
 *
 * Each test provides its own tde काष्ठा tdescr descriptor to link with
 * this wrapper. Framework provides common helpers.
 */
#समावेश <kselftest.h>

#समावेश "test_signals.h"
#समावेश "test_signals_utils.h"

काष्ठा tdescr *current;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	current = &tde;

	ksft_prपूर्णांक_msg("%s :: %s\n", current->name, current->descr);
	अगर (test_setup(current) && test_init(current)) अणु
		test_run(current);
		test_cleanup(current);
	पूर्ण
	test_result(current);

	वापस current->result;
पूर्ण
