<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2011 Florian Fainelli <florian@खोलोwrt.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <bcm63xx_cpu.h>

अटल काष्ठा resource rng_resources[] = अणु
	अणु
		.start		= -1, /* filled at runसमय */
		.end		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device bcm63xx_rng_device = अणु
	.name		= "bcm63xx-rng",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rng_resources),
	.resource	= rng_resources,
पूर्ण;

पूर्णांक __init bcm63xx_rng_रेजिस्टर(व्योम)
अणु
	अगर (!BCMCPU_IS_6368())
		वापस -ENODEV;

	rng_resources[0].start = bcm63xx_regset_address(RSET_RNG);
	rng_resources[0].end = rng_resources[0].start;
	rng_resources[0].end += RSET_RNG_SIZE - 1;

	वापस platक्रमm_device_रेजिस्टर(&bcm63xx_rng_device);
पूर्ण
arch_initcall(bcm63xx_rng_रेजिस्टर);
