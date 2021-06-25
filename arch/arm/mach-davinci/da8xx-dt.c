<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Modअगरied from mach-omap/omap2/board-generic.c
 */

#समावेश <यंत्र/mach/arch.h>

#समावेश <mach/common.h>
#समावेश <mach/da8xx.h>

#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850

अटल व्योम __init da850_init_machine(व्योम)
अणु
	davinci_pm_init();
	pdata_quirks_init();
पूर्ण

अटल स्थिर अक्षर *स्थिर da850_boards_compat[] __initस्थिर = अणु
	"enbw,cmc",
	"ti,da850-lcdk",
	"ti,da850-evm",
	"ti,da850",
	शून्य,
पूर्ण;

DT_MACHINE_START(DA850_DT, "Generic DA850/OMAP-L138/AM18x")
	.map_io		= da850_init,
	.init_machine	= da850_init_machine,
	.dt_compat	= da850_boards_compat,
	.init_late	= davinci_init_late,
MACHINE_END

#पूर्ण_अगर
