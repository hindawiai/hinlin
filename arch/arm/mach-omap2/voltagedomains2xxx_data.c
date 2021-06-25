<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP3 voltage करोमुख्य data
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश "voltage.h"

अटल काष्ठा voltageकरोमुख्य omap2_voltdm_core = अणु
	.name = "core",
पूर्ण;

अटल काष्ठा voltageकरोमुख्य omap2_voltdm_wkup = अणु
	.name = "wakeup",
पूर्ण;

अटल काष्ठा voltageकरोमुख्य *voltageकरोमुख्यs_omap2[] __initdata = अणु
	&omap2_voltdm_core,
	&omap2_voltdm_wkup,
	शून्य,
पूर्ण;

व्योम __init omap2xxx_voltageकरोमुख्यs_init(व्योम)
अणु
	voltdm_init(voltageकरोमुख्यs_omap2);
पूर्ण
