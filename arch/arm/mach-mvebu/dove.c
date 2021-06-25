<शैली गुरु>
/*
 * arch/arm/mach-mvebu/करोve.c
 *
 * Marvell Dove 88AP510 System On Chip FDT Board
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/init.h>
#समावेश <linux/mbus.h>
#समावेश <linux/of.h>
#समावेश <linux/soc/करोve/pmu.h>
#समावेश <यंत्र/hardware/cache-tauros2.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "common.h"

अटल व्योम __init करोve_init(व्योम)
अणु
	pr_info("Dove 88AP510 SoC\n");

#अगर_घोषित CONFIG_CACHE_TAUROS2
	tauros2_init(0);
#पूर्ण_अगर
	BUG_ON(mvebu_mbus_dt_init(false));
	करोve_init_pmu();
पूर्ण

अटल स्थिर अक्षर * स्थिर करोve_dt_compat[] __initस्थिर = अणु
	"marvell,dove",
	शून्य
पूर्ण;

DT_MACHINE_START(DOVE_DT, "Marvell Dove")
	.init_machine	= करोve_init,
	.restart	= mvebu_restart,
	.dt_compat	= करोve_dt_compat,
MACHINE_END
