<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/types.h>

#समावेश "../../../util/tsc.h"

u64 rdtsc(व्योम)
अणु
	u64 val;

	/*
	 * According to ARM DDI 0487F.c, from Armv8.0 to Armv8.5 inclusive, the
	 * प्रणाली counter is at least 56 bits wide; from Armv8.6, the counter
	 * must be 64 bits wide.  So the प्रणाली counter could be less than 64
	 * bits wide and it is attributed with the flag 'cap_user_time_short'
	 * is true.
	 */
	यंत्र अस्थिर("mrs %0, cntvct_el0" : "=r" (val));

	वापस val;
पूर्ण
