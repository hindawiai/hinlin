<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/mmp-dt.c
 *
 *  Copyright (C) 2012 Marvell Technology Group Ltd.
 *  Author: Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/irqchip.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/hardware/cache-tauros2.h>

#समावेश "common.h"

अटल स्थिर अक्षर *स्थिर pxa168_dt_board_compat[] __initस्थिर = अणु
	"mrvl,pxa168-aspenite",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर *स्थिर pxa910_dt_board_compat[] __initस्थिर = अणु
	"mrvl,pxa910-dkb",
	शून्य,
पूर्ण;

अटल व्योम __init mmp_init_समय(व्योम)
अणु
#अगर_घोषित CONFIG_CACHE_TAUROS2
	tauros2_init(0);
#पूर्ण_अगर
	of_clk_init(शून्य);
	समयr_probe();
पूर्ण

DT_MACHINE_START(PXA168_DT, "Marvell PXA168 (Device Tree Support)")
	.map_io		= mmp_map_io,
	.init_समय	= mmp_init_समय,
	.dt_compat	= pxa168_dt_board_compat,
MACHINE_END

DT_MACHINE_START(PXA910_DT, "Marvell PXA910 (Device Tree Support)")
	.map_io		= mmp_map_io,
	.init_समय	= mmp_init_समय,
	.dt_compat	= pxa910_dt_board_compat,
MACHINE_END
