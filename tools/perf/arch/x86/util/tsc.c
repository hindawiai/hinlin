<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>

#समावेश "../../../util/tsc.h"

u64 rdtsc(व्योम)
अणु
	अचिन्हित पूर्णांक low, high;

	यंत्र अस्थिर("rdtsc" : "=a" (low), "=d" (high));

	वापस low | ((u64)high) << 32;
पूर्ण
