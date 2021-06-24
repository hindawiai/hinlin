<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Realtek RTD1195
 *
 * Copyright (c) 2017-2019 Andreas Fथअrber
 */

#समावेश <linux/memblock.h>
#समावेश <यंत्र/mach/arch.h>

अटल व्योम __init rtd1195_memblock_हटाओ(phys_addr_t base, phys_addr_t size)
अणु
	पूर्णांक ret;

	ret = memblock_हटाओ(base, size);
	अगर (ret)
		pr_err("Failed to remove memblock %pa (%d)\n", &base, ret);
पूर्ण

अटल व्योम __init rtd1195_reserve(व्योम)
अणु
	/* Exclude boot ROM from RAM */
	rtd1195_memblock_हटाओ(0x00000000, 0x0000a800);

	/* Exclude peripheral रेजिस्टर spaces from RAM */
	rtd1195_memblock_हटाओ(0x18000000, 0x00070000);
	rtd1195_memblock_हटाओ(0x18100000, 0x01000000);
पूर्ण

अटल स्थिर अक्षर *स्थिर rtd1195_dt_compat[] __initस्थिर = अणु
	"realtek,rtd1195",
	शून्य
पूर्ण;

DT_MACHINE_START(rtd1195, "Realtek RTD1195")
	.dt_compat = rtd1195_dt_compat,
	.reserve = rtd1195_reserve,
	.l2c_aux_val = 0x0,
	.l2c_aux_mask = ~0x0,
MACHINE_END
