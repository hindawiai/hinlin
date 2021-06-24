<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012 Jonas Gorski <jonas.gorski@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_dev_hsspi.h>
#समावेश <bcm63xx_regs.h>

अटल काष्ठा resource spi_resources[] = अणु
	अणु
		.start		= -1, /* filled at runसमय */
		.end		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= -1, /* filled at runसमय */
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device bcm63xx_hsspi_device = अणु
	.name		= "bcm63xx-hsspi",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(spi_resources),
	.resource	= spi_resources,
पूर्ण;

पूर्णांक __init bcm63xx_hsspi_रेजिस्टर(व्योम)
अणु
	अगर (!BCMCPU_IS_6328() && !BCMCPU_IS_6362())
		वापस -ENODEV;

	spi_resources[0].start = bcm63xx_regset_address(RSET_HSSPI);
	spi_resources[0].end = spi_resources[0].start;
	spi_resources[0].end += RSET_HSSPI_SIZE - 1;
	spi_resources[1].start = bcm63xx_get_irq_number(IRQ_HSSPI);

	वापस platक्रमm_device_रेजिस्टर(&bcm63xx_hsspi_device);
पूर्ण
