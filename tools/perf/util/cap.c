<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Capability utilities
 */

#अगर_घोषित HAVE_LIBCAP_SUPPORT

#समावेश "cap.h"
#समावेश <stdbool.h>
#समावेश <sys/capability.h>

bool perf_cap__capable(cap_value_t cap)
अणु
	cap_flag_value_t val;
	cap_t caps = cap_get_proc();

	अगर (!caps)
		वापस false;

	अगर (cap_get_flag(caps, cap, CAP_EFFECTIVE, &val) != 0)
		val = CAP_CLEAR;

	अगर (cap_मुक्त(caps) != 0)
		वापस false;

	वापस val == CAP_SET;
पूर्ण

#पूर्ण_अगर  /* HAVE_LIBCAP_SUPPORT */
