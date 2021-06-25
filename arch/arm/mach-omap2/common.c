<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap2/common.c
 *
 * Code common to all OMAP2+ machines.
 *
 * Copyright (C) 2009 Texas Instruments
 * Copyright (C) 2010 Nokia Corporation
 * Tony Lindgren <tony@atomide.com>
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश "common.h"
#समावेश "omap-secure.h"

/*
 * Stub function क्रम OMAP2 so that common files
 * जारी to build when custom builds are used
 */
पूर्णांक __weak omap_secure_ram_reserve_memblock(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम __init omap_reserve(व्योम)
अणु
	omap_secure_ram_reserve_memblock();
	omap_barrier_reserve_memblock();
पूर्ण
