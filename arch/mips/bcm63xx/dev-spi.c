<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2009-2011 Florian Fainelli <florian@खोलोwrt.org>
 * Copyright (C) 2010 Tanguy Bouzeloc <tanguy.bouzeloc@efixo.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>

#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_dev_spi.h>
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

अटल काष्ठा platक्रमm_device bcm63xx_spi_device = अणु
	.id		= -1,
	.num_resources	= ARRAY_SIZE(spi_resources),
	.resource	= spi_resources,
पूर्ण;

पूर्णांक __init bcm63xx_spi_रेजिस्टर(व्योम)
अणु
	अगर (BCMCPU_IS_6328() || BCMCPU_IS_6345())
		वापस -ENODEV;

	spi_resources[0].start = bcm63xx_regset_address(RSET_SPI);
	spi_resources[0].end = spi_resources[0].start;
	spi_resources[1].start = bcm63xx_get_irq_number(IRQ_SPI);

	अगर (BCMCPU_IS_6338() || BCMCPU_IS_6348()) अणु
		bcm63xx_spi_device.name = "bcm6348-spi",
		spi_resources[0].end += BCM_6348_RSET_SPI_SIZE - 1;
	पूर्ण

	अगर (BCMCPU_IS_3368() || BCMCPU_IS_6358() || BCMCPU_IS_6362() ||
		BCMCPU_IS_6368()) अणु
		bcm63xx_spi_device.name = "bcm6358-spi",
		spi_resources[0].end += BCM_6358_RSET_SPI_SIZE - 1;
	पूर्ण

	वापस platक्रमm_device_रेजिस्टर(&bcm63xx_spi_device);
पूर्ण
