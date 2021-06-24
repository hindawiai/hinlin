<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/capability.h>
#समावेश <linux/capability.h>

पूर्णांक मुख्य(व्योम)
अणु
	cap_flag_value_t val;
	cap_t caps = cap_get_proc();

	अगर (!caps)
		वापस 1;

	अगर (cap_get_flag(caps, CAP_SYS_ADMIN, CAP_EFFECTIVE, &val) != 0)
		वापस 1;

	अगर (cap_मुक्त(caps) != 0)
		वापस 1;

	वापस 0;
पूर्ण
