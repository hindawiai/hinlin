<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Florian Fainelli <florian@खोलोwrt.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <bcm63xx_cpu.h>

अटल काष्ठा resource wdt_resources[] = अणु
	अणु
		.start		= -1, /* filled at runसमय */
		.end		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device bcm63xx_wdt_device = अणु
	.name		= "bcm63xx-wdt",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(wdt_resources),
	.resource	= wdt_resources,
पूर्ण;

पूर्णांक __init bcm63xx_wdt_रेजिस्टर(व्योम)
अणु
	wdt_resources[0].start = bcm63xx_regset_address(RSET_WDT);
	wdt_resources[0].end = wdt_resources[0].start;
	wdt_resources[0].end += RSET_WDT_SIZE - 1;

	वापस platक्रमm_device_रेजिस्टर(&bcm63xx_wdt_device);
पूर्ण
arch_initcall(bcm63xx_wdt_रेजिस्टर);
