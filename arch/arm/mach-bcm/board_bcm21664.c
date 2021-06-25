<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <यंत्र/mach/arch.h>

#समावेश "kona_l2_cache.h"

अटल व्योम __init bcm21664_init(व्योम)
अणु
	kona_l2_cache_init();
पूर्ण

अटल स्थिर अक्षर * स्थिर bcm21664_dt_compat[] = अणु
	"brcm,bcm21664",
	शून्य,
पूर्ण;

DT_MACHINE_START(BCM21664_DT, "BCM21664 Broadcom Application Processor")
	.init_machine = bcm21664_init,
	.dt_compat = bcm21664_dt_compat,
MACHINE_END
