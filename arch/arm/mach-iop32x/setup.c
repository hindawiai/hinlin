<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/plat-iop/setup.c
 *
 * Author: Nicolas Pitre <nico@fluxnic.net>
 * Copyright (C) 2001 MontaVista Software, Inc.
 * Copyright (C) 2004 Intel Corporation.
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/mach/map.h>
#समावेश "iop3xx.h"

/*
 * Standard IO mapping क्रम all IOP3xx based प्रणालीs.  Note that
 * the IOP3xx OCCDR must be mapped uncached and unbuffered.
 */
अटल काष्ठा map_desc iop3xx_std_desc[] __initdata = अणु
	अणु	/* mem mapped रेजिस्टरs */
		.भव	= IOP3XX_PERIPHERAL_VIRT_BASE,
		.pfn		= __phys_to_pfn(IOP3XX_PERIPHERAL_PHYS_BASE),
		.length		= IOP3XX_PERIPHERAL_SIZE,
		.type		= MT_UNCACHED,
	पूर्ण,
पूर्ण;

व्योम __init iop3xx_map_io(व्योम)
अणु
	iotable_init(iop3xx_std_desc, ARRAY_SIZE(iop3xx_std_desc));
पूर्ण
