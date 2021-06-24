<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device Tree support क्रम Marvell Berlin SoCs.
 *
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 *
 * based on GPL'ed 2.6 kernel sources
 *  (c) Marvell International Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/mach/arch.h>

अटल स्थिर अक्षर * स्थिर berlin_dt_compat[] = अणु
	"marvell,berlin",
	शून्य,
पूर्ण;

DT_MACHINE_START(BERLIN_DT, "Marvell Berlin")
	.dt_compat	= berlin_dt_compat,
	/*
	 * with DT probing क्रम L2CCs, berlin_init_machine can be हटाओd.
	 * Note: 88DE3005 (Armada 1500-mini) uses pl310 l2cc
	 */
	.l2c_aux_val	= 0x30c00000,
	.l2c_aux_mask	= 0xfeffffff,
MACHINE_END
