<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Marvell MMP3 aka PXA2128 aka 88AP2128 support
 *
 *  Copyright (C) 2019 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 */

#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk-provider.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

#समावेश "common.h"

अटल स्थिर अक्षर *स्थिर mmp3_dt_board_compat[] __initस्थिर = अणु
	"marvell,mmp3",
	शून्य,
पूर्ण;

DT_MACHINE_START(MMP2_DT, "Marvell MMP3")
	.map_io		= mmp2_map_io,
	.dt_compat	= mmp3_dt_board_compat,
	.l2c_aux_val	= 1 << L310_AUX_CTRL_FWA_SHIFT |
			  L310_AUX_CTRL_DATA_PREFETCH |
			  L310_AUX_CTRL_INSTR_PREFETCH,
	.l2c_aux_mask	= 0xc20fffff,
MACHINE_END
