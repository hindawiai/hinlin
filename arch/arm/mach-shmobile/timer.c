<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH-Mobile Timer
 *
 * Copyright (C) 2010  Magnus Damm
 * Copyright (C) 2002 - 2009  Paul Mundt
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_address.h>

#समावेश "common.h"

व्योम __init shmobile_init_delay(व्योम)
अणु
	काष्ठा device_node *np;
	u32 max_freq = 0;

	क्रम_each_of_cpu_node(np) अणु
		u32 freq;

		अगर (!of_property_पढ़ो_u32(np, "clock-frequency", &freq))
			max_freq = max(max_freq, freq);
	पूर्ण

	अगर (!max_freq)
		वापस;

	/*
	 * Calculate a worst-हाल loops-per-jअगरfy value
	 * based on maximum cpu core hz setting and the
	 * __delay() implementation in arch/arm/lib/delay.S.
	 *
	 * This will result in a दीर्घer delay than expected
	 * when the cpu core runs on lower frequencies.
	 */

	अगर (!preset_lpj)
		preset_lpj = max_freq / HZ;
पूर्ण
