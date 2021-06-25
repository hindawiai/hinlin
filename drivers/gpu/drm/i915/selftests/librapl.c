<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <यंत्र/msr.h>

#समावेश "librapl.h"

u64 librapl_energy_uJ(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ घातer;
	u32 units;

	अगर (rdmsrl_safe(MSR_RAPL_POWER_UNIT, &घातer))
		वापस 0;

	units = (घातer & 0x1f00) >> 8;

	अगर (rdmsrl_safe(MSR_PP1_ENERGY_STATUS, &घातer))
		वापस 0;

	वापस (1000000 * घातer) >> units; /* convert to uJ */
पूर्ण
