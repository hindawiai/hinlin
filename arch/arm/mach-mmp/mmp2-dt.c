<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/mmp2-dt.c
 *
 *  Copyright (C) 2012 Marvell Technology Group Ltd.
 *  Author: Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/hardware/cache-tauros2.h>

#समावेश "common.h"

अटल व्योम __init mmp_init_समय(व्योम)
अणु
#अगर_घोषित CONFIG_CACHE_TAUROS2
	tauros2_init(0);
#पूर्ण_अगर
	of_clk_init(शून्य);
	समयr_probe();
पूर्ण

अटल स्थिर अक्षर *स्थिर mmp2_dt_board_compat[] __initस्थिर = अणु
	"mrvl,mmp2",
	शून्य,
पूर्ण;

DT_MACHINE_START(MMP2_DT, "Marvell MMP2 (Device Tree Support)")
	.map_io		= mmp2_map_io,
	.init_समय	= mmp_init_समय,
	.dt_compat	= mmp2_dt_board_compat,
MACHINE_END
