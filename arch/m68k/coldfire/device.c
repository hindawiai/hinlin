<शैली गुरु>
/*
 * device.c  -- common ColdFire SoC device support
 *
 * (C) Copyright 2011, Greg Ungerer <gerg@uclinux.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/fec.h>
#समावेश <linux/dmaengine.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfuart.h>
#समावेश <यंत्र/mcfqspi.h>
#समावेश <linux/platक्रमm_data/edma.h>
#समावेश <linux/platक्रमm_data/dma-mcf-edma.h>
#समावेश <linux/platक्रमm_data/mmc-esdhc-mcf.h>

/*
 *	All current ColdFire parts contain from 2, 3, 4 or 10 UARTS.
 */
अटल काष्ठा mcf_platक्रमm_uart mcf_uart_platक्रमm_data[] = अणु
	अणु
		.mapbase	= MCFUART_BASE0,
		.irq		= MCF_IRQ_UART0,
	पूर्ण,
	अणु
		.mapbase	= MCFUART_BASE1,
		.irq		= MCF_IRQ_UART1,
	पूर्ण,
#अगर_घोषित MCFUART_BASE2
	अणु
		.mapbase	= MCFUART_BASE2,
		.irq		= MCF_IRQ_UART2,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित MCFUART_BASE3
	अणु
		.mapbase	= MCFUART_BASE3,
		.irq		= MCF_IRQ_UART3,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित MCFUART_BASE4
	अणु
		.mapbase	= MCFUART_BASE4,
		.irq		= MCF_IRQ_UART4,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित MCFUART_BASE5
	अणु
		.mapbase	= MCFUART_BASE5,
		.irq		= MCF_IRQ_UART5,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित MCFUART_BASE6
	अणु
		.mapbase	= MCFUART_BASE6,
		.irq		= MCF_IRQ_UART6,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित MCFUART_BASE7
	अणु
		.mapbase	= MCFUART_BASE7,
		.irq		= MCF_IRQ_UART7,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित MCFUART_BASE8
	अणु
		.mapbase	= MCFUART_BASE8,
		.irq		= MCF_IRQ_UART8,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित MCFUART_BASE9
	अणु
		.mapbase	= MCFUART_BASE9,
		.irq		= MCF_IRQ_UART9,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mcf_uart = अणु
	.name			= "mcfuart",
	.id			= 0,
	.dev.platक्रमm_data	= mcf_uart_platक्रमm_data,
पूर्ण;

#अगर IS_ENABLED(CONFIG_FEC)

#अगर_घोषित CONFIG_M5441x
#घोषणा FEC_NAME	"enet-fec"
अटल काष्ठा fec_platक्रमm_data fec_pdata = अणु
	.phy		= PHY_INTERFACE_MODE_RMII,
पूर्ण;
#घोषणा FEC_PDATA	(&fec_pdata)
#अन्यथा
#घोषणा FEC_NAME	"fec"
#घोषणा FEC_PDATA	शून्य
#पूर्ण_अगर

/*
 *	Some ColdFire cores contain the Fast Ethernet Controller (FEC)
 *	block. It is Freescale's own hardware block. Some ColdFires
 *	have 2 of these.
 */
अटल काष्ठा resource mcf_fec0_resources[] = अणु
	अणु
		.start		= MCFFEC_BASE0,
		.end		= MCFFEC_BASE0 + MCFFEC_SIZE0 - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= MCF_IRQ_FECRX0,
		.end		= MCF_IRQ_FECRX0,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start		= MCF_IRQ_FECTX0,
		.end		= MCF_IRQ_FECTX0,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start		= MCF_IRQ_FECENTC0,
		.end		= MCF_IRQ_FECENTC0,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mcf_fec0 = अणु
	.name			= FEC_NAME,
	.id			= 0,
	.num_resources		= ARRAY_SIZE(mcf_fec0_resources),
	.resource		= mcf_fec0_resources,
	.dev = अणु
		.dma_mask		= &mcf_fec0.dev.coherent_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= FEC_PDATA,
	पूर्ण
पूर्ण;

#अगर_घोषित MCFFEC_BASE1
अटल काष्ठा resource mcf_fec1_resources[] = अणु
	अणु
		.start		= MCFFEC_BASE1,
		.end		= MCFFEC_BASE1 + MCFFEC_SIZE1 - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= MCF_IRQ_FECRX1,
		.end		= MCF_IRQ_FECRX1,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start		= MCF_IRQ_FECTX1,
		.end		= MCF_IRQ_FECTX1,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start		= MCF_IRQ_FECENTC1,
		.end		= MCF_IRQ_FECENTC1,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mcf_fec1 = अणु
	.name			= FEC_NAME,
	.id			= 1,
	.num_resources		= ARRAY_SIZE(mcf_fec1_resources),
	.resource		= mcf_fec1_resources,
	.dev = अणु
		.dma_mask		= &mcf_fec1.dev.coherent_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= FEC_PDATA,
	पूर्ण
पूर्ण;
#पूर्ण_अगर /* MCFFEC_BASE1 */
#पूर्ण_अगर /* CONFIG_FEC */

#अगर IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI)
/*
 *	The ColdFire QSPI module is an SPI protocol hardware block used
 *	on a number of dअगरferent ColdFire CPUs.
 */
अटल काष्ठा resource mcf_qspi_resources[] = अणु
	अणु
		.start		= MCFQSPI_BASE,
		.end		= MCFQSPI_BASE + MCFQSPI_SIZE - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= MCF_IRQ_QSPI,
		.end		= MCF_IRQ_QSPI,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mcf_cs_setup(काष्ठा mcfqspi_cs_control *cs_control)
अणु
	पूर्णांक status;

	status = gpio_request(MCFQSPI_CS0, "MCFQSPI_CS0");
	अगर (status) अणु
		pr_debug("gpio_request for MCFQSPI_CS0 failed\n");
		जाओ fail0;
	पूर्ण
	status = gpio_direction_output(MCFQSPI_CS0, 1);
	अगर (status) अणु
		pr_debug("gpio_direction_output for MCFQSPI_CS0 failed\n");
		जाओ fail1;
	पूर्ण

	status = gpio_request(MCFQSPI_CS1, "MCFQSPI_CS1");
	अगर (status) अणु
		pr_debug("gpio_request for MCFQSPI_CS1 failed\n");
		जाओ fail1;
	पूर्ण
	status = gpio_direction_output(MCFQSPI_CS1, 1);
	अगर (status) अणु
		pr_debug("gpio_direction_output for MCFQSPI_CS1 failed\n");
		जाओ fail2;
	पूर्ण

	status = gpio_request(MCFQSPI_CS2, "MCFQSPI_CS2");
	अगर (status) अणु
		pr_debug("gpio_request for MCFQSPI_CS2 failed\n");
		जाओ fail2;
	पूर्ण
	status = gpio_direction_output(MCFQSPI_CS2, 1);
	अगर (status) अणु
		pr_debug("gpio_direction_output for MCFQSPI_CS2 failed\n");
		जाओ fail3;
	पूर्ण

#अगर_घोषित MCFQSPI_CS3
	status = gpio_request(MCFQSPI_CS3, "MCFQSPI_CS3");
	अगर (status) अणु
		pr_debug("gpio_request for MCFQSPI_CS3 failed\n");
		जाओ fail3;
	पूर्ण
	status = gpio_direction_output(MCFQSPI_CS3, 1);
	अगर (status) अणु
		pr_debug("gpio_direction_output for MCFQSPI_CS3 failed\n");
		gpio_मुक्त(MCFQSPI_CS3);
		जाओ fail3;
	पूर्ण
#पूर्ण_अगर

	वापस 0;

fail3:
	gpio_मुक्त(MCFQSPI_CS2);
fail2:
	gpio_मुक्त(MCFQSPI_CS1);
fail1:
	gpio_मुक्त(MCFQSPI_CS0);
fail0:
	वापस status;
पूर्ण

अटल व्योम mcf_cs_tearकरोwn(काष्ठा mcfqspi_cs_control *cs_control)
अणु
#अगर_घोषित MCFQSPI_CS3
	gpio_मुक्त(MCFQSPI_CS3);
#पूर्ण_अगर
	gpio_मुक्त(MCFQSPI_CS2);
	gpio_मुक्त(MCFQSPI_CS1);
	gpio_मुक्त(MCFQSPI_CS0);
पूर्ण

अटल व्योम mcf_cs_select(काष्ठा mcfqspi_cs_control *cs_control,
			  u8 chip_select, bool cs_high)
अणु
	चयन (chip_select) अणु
	हाल 0:
		gpio_set_value(MCFQSPI_CS0, cs_high);
		अवरोध;
	हाल 1:
		gpio_set_value(MCFQSPI_CS1, cs_high);
		अवरोध;
	हाल 2:
		gpio_set_value(MCFQSPI_CS2, cs_high);
		अवरोध;
#अगर_घोषित MCFQSPI_CS3
	हाल 3:
		gpio_set_value(MCFQSPI_CS3, cs_high);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम mcf_cs_deselect(काष्ठा mcfqspi_cs_control *cs_control,
			    u8 chip_select, bool cs_high)
अणु
	चयन (chip_select) अणु
	हाल 0:
		gpio_set_value(MCFQSPI_CS0, !cs_high);
		अवरोध;
	हाल 1:
		gpio_set_value(MCFQSPI_CS1, !cs_high);
		अवरोध;
	हाल 2:
		gpio_set_value(MCFQSPI_CS2, !cs_high);
		अवरोध;
#अगर_घोषित MCFQSPI_CS3
	हाल 3:
		gpio_set_value(MCFQSPI_CS3, !cs_high);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल काष्ठा mcfqspi_cs_control mcf_cs_control = अणु
	.setup			= mcf_cs_setup,
	.tearकरोwn		= mcf_cs_tearकरोwn,
	.select			= mcf_cs_select,
	.deselect		= mcf_cs_deselect,
पूर्ण;

अटल काष्ठा mcfqspi_platक्रमm_data mcf_qspi_data = अणु
	.bus_num		= 0,
	.num_chipselect		= 4,
	.cs_control		= &mcf_cs_control,
पूर्ण;

अटल काष्ठा platक्रमm_device mcf_qspi = अणु
	.name			= "mcfqspi",
	.id			= 0,
	.num_resources		= ARRAY_SIZE(mcf_qspi_resources),
	.resource		= mcf_qspi_resources,
	.dev.platक्रमm_data	= &mcf_qspi_data,
पूर्ण;
#पूर्ण_अगर /* IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI) */

#अगर IS_ENABLED(CONFIG_I2C_IMX)
अटल काष्ठा resource mcf_i2c0_resources[] = अणु
	अणु
		.start          = MCFI2C_BASE0,
		.end            = MCFI2C_BASE0 + MCFI2C_SIZE0 - 1,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start          = MCF_IRQ_I2C0,
		.end            = MCF_IRQ_I2C0,
		.flags          = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mcf_i2c0 = अणु
	.name                   = "imx1-i2c",
	.id                     = 0,
	.num_resources          = ARRAY_SIZE(mcf_i2c0_resources),
	.resource               = mcf_i2c0_resources,
पूर्ण;
#अगर_घोषित MCFI2C_BASE1

अटल काष्ठा resource mcf_i2c1_resources[] = अणु
	अणु
		.start          = MCFI2C_BASE1,
		.end            = MCFI2C_BASE1 + MCFI2C_SIZE1 - 1,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start          = MCF_IRQ_I2C1,
		.end            = MCF_IRQ_I2C1,
		.flags          = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mcf_i2c1 = अणु
	.name                   = "imx1-i2c",
	.id                     = 1,
	.num_resources          = ARRAY_SIZE(mcf_i2c1_resources),
	.resource               = mcf_i2c1_resources,
पूर्ण;

#पूर्ण_अगर /* MCFI2C_BASE1 */

#अगर_घोषित MCFI2C_BASE2

अटल काष्ठा resource mcf_i2c2_resources[] = अणु
	अणु
		.start          = MCFI2C_BASE2,
		.end            = MCFI2C_BASE2 + MCFI2C_SIZE2 - 1,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start          = MCF_IRQ_I2C2,
		.end            = MCF_IRQ_I2C2,
		.flags          = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mcf_i2c2 = अणु
	.name                   = "imx1-i2c",
	.id                     = 2,
	.num_resources          = ARRAY_SIZE(mcf_i2c2_resources),
	.resource               = mcf_i2c2_resources,
पूर्ण;

#पूर्ण_अगर /* MCFI2C_BASE2 */

#अगर_घोषित MCFI2C_BASE3

अटल काष्ठा resource mcf_i2c3_resources[] = अणु
	अणु
		.start          = MCFI2C_BASE3,
		.end            = MCFI2C_BASE3 + MCFI2C_SIZE3 - 1,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start          = MCF_IRQ_I2C3,
		.end            = MCF_IRQ_I2C3,
		.flags          = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mcf_i2c3 = अणु
	.name                   = "imx1-i2c",
	.id                     = 3,
	.num_resources          = ARRAY_SIZE(mcf_i2c3_resources),
	.resource               = mcf_i2c3_resources,
पूर्ण;

#पूर्ण_अगर /* MCFI2C_BASE3 */

#अगर_घोषित MCFI2C_BASE4

अटल काष्ठा resource mcf_i2c4_resources[] = अणु
	अणु
		.start          = MCFI2C_BASE4,
		.end            = MCFI2C_BASE4 + MCFI2C_SIZE4 - 1,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start          = MCF_IRQ_I2C4,
		.end            = MCF_IRQ_I2C4,
		.flags          = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mcf_i2c4 = अणु
	.name                   = "imx1-i2c",
	.id                     = 4,
	.num_resources          = ARRAY_SIZE(mcf_i2c4_resources),
	.resource               = mcf_i2c4_resources,
पूर्ण;

#पूर्ण_अगर /* MCFI2C_BASE4 */

#अगर_घोषित MCFI2C_BASE5

अटल काष्ठा resource mcf_i2c5_resources[] = अणु
	अणु
		.start          = MCFI2C_BASE5,
		.end            = MCFI2C_BASE5 + MCFI2C_SIZE5 - 1,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start          = MCF_IRQ_I2C5,
		.end            = MCF_IRQ_I2C5,
		.flags          = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mcf_i2c5 = अणु
	.name                   = "imx1-i2c",
	.id                     = 5,
	.num_resources          = ARRAY_SIZE(mcf_i2c5_resources),
	.resource               = mcf_i2c5_resources,
पूर्ण;

#पूर्ण_अगर /* MCFI2C_BASE5 */
#पूर्ण_अगर /* IS_ENABLED(CONFIG_I2C_IMX) */

#अगर IS_ENABLED(CONFIG_MCF_EDMA)

अटल स्थिर काष्ठा dma_slave_map mcf_edma_map[] = अणु
	अणु "dreq0", "rx-tx", MCF_EDMA_FILTER_PARAM(0) पूर्ण,
	अणु "dreq1", "rx-tx", MCF_EDMA_FILTER_PARAM(1) पूर्ण,
	अणु "uart.0", "rx", MCF_EDMA_FILTER_PARAM(2) पूर्ण,
	अणु "uart.0", "tx", MCF_EDMA_FILTER_PARAM(3) पूर्ण,
	अणु "uart.1", "rx", MCF_EDMA_FILTER_PARAM(4) पूर्ण,
	अणु "uart.1", "tx", MCF_EDMA_FILTER_PARAM(5) पूर्ण,
	अणु "uart.2", "rx", MCF_EDMA_FILTER_PARAM(6) पूर्ण,
	अणु "uart.2", "tx", MCF_EDMA_FILTER_PARAM(7) पूर्ण,
	अणु "timer0", "rx-tx", MCF_EDMA_FILTER_PARAM(8) पूर्ण,
	अणु "timer1", "rx-tx", MCF_EDMA_FILTER_PARAM(9) पूर्ण,
	अणु "timer2", "rx-tx", MCF_EDMA_FILTER_PARAM(10) पूर्ण,
	अणु "timer3", "rx-tx", MCF_EDMA_FILTER_PARAM(11) पूर्ण,
	अणु "fsl-dspi.0", "rx", MCF_EDMA_FILTER_PARAM(12) पूर्ण,
	अणु "fsl-dspi.0", "tx", MCF_EDMA_FILTER_PARAM(13) पूर्ण,
	अणु "fsl-dspi.1", "rx", MCF_EDMA_FILTER_PARAM(14) पूर्ण,
	अणु "fsl-dspi.1", "tx", MCF_EDMA_FILTER_PARAM(15) पूर्ण,
पूर्ण;

अटल काष्ठा mcf_edma_platक्रमm_data mcf_edma_data = अणु
	.dma_channels		= 64,
	.slave_map		= mcf_edma_map,
	.slavecnt		= ARRAY_SIZE(mcf_edma_map),
पूर्ण;

अटल काष्ठा resource mcf_edma_resources[] = अणु
	अणु
		.start		= MCFEDMA_BASE,
		.end		= MCFEDMA_BASE + MCFEDMA_SIZE - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= MCFEDMA_IRQ_INTR0,
		.end		= MCFEDMA_IRQ_INTR0 + 15,
		.flags		= IORESOURCE_IRQ,
		.name		= "edma-tx-00-15",
	पूर्ण,
	अणु
		.start		= MCFEDMA_IRQ_INTR16,
		.end		= MCFEDMA_IRQ_INTR16 + 39,
		.flags		= IORESOURCE_IRQ,
		.name		= "edma-tx-16-55",
	पूर्ण,
	अणु
		.start		= MCFEDMA_IRQ_INTR56,
		.end		= MCFEDMA_IRQ_INTR56,
		.flags		= IORESOURCE_IRQ,
		.name		= "edma-tx-56-63",
	पूर्ण,
	अणु
		.start		= MCFEDMA_IRQ_ERR,
		.end		= MCFEDMA_IRQ_ERR,
		.flags		= IORESOURCE_IRQ,
		.name		= "edma-err",
	पूर्ण,
पूर्ण;

अटल u64 mcf_edma_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device mcf_edma = अणु
	.name			= "mcf-edma",
	.id			= 0,
	.num_resources		= ARRAY_SIZE(mcf_edma_resources),
	.resource		= mcf_edma_resources,
	.dev = अणु
		.dma_mask = &mcf_edma_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data = &mcf_edma_data,
	पूर्ण
पूर्ण;
#पूर्ण_अगर /* IS_ENABLED(CONFIG_MCF_EDMA) */

#अगर_घोषित MCFSDHC_BASE
अटल काष्ठा mcf_esdhc_platक्रमm_data mcf_esdhc_data = अणु
	.max_bus_width = 4,
	.cd_type = ESDHC_CD_NONE,
पूर्ण;

अटल काष्ठा resource mcf_esdhc_resources[] = अणु
	अणु
		.start = MCFSDHC_BASE,
		.end = MCFSDHC_BASE + MCFSDHC_SIZE - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण, अणु
		.start = MCF_IRQ_SDHC,
		.end = MCF_IRQ_SDHC,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mcf_esdhc = अणु
	.name			= "sdhci-esdhc-mcf",
	.id			= 0,
	.num_resources		= ARRAY_SIZE(mcf_esdhc_resources),
	.resource		= mcf_esdhc_resources,
	.dev.platक्रमm_data	= &mcf_esdhc_data,
पूर्ण;
#पूर्ण_अगर /* MCFSDHC_BASE */

अटल काष्ठा platक्रमm_device *mcf_devices[] __initdata = अणु
	&mcf_uart,
#अगर IS_ENABLED(CONFIG_FEC)
	&mcf_fec0,
#अगर_घोषित MCFFEC_BASE1
	&mcf_fec1,
#पूर्ण_अगर
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI)
	&mcf_qspi,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_I2C_IMX)
	&mcf_i2c0,
#अगर_घोषित MCFI2C_BASE1
	&mcf_i2c1,
#पूर्ण_अगर
#अगर_घोषित MCFI2C_BASE2
	&mcf_i2c2,
#पूर्ण_अगर
#अगर_घोषित MCFI2C_BASE3
	&mcf_i2c3,
#पूर्ण_अगर
#अगर_घोषित MCFI2C_BASE4
	&mcf_i2c4,
#पूर्ण_अगर
#अगर_घोषित MCFI2C_BASE5
	&mcf_i2c5,
#पूर्ण_अगर
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_MCF_EDMA)
	&mcf_edma,
#पूर्ण_अगर
#अगर_घोषित MCFSDHC_BASE
	&mcf_esdhc,
#पूर्ण_अगर
पूर्ण;

/*
 *	Some ColdFire UARTs let you set the IRQ line to use.
 */
अटल व्योम __init mcf_uart_set_irq(व्योम)
अणु
#अगर_घोषित MCFUART_UIVR
	/* UART0 पूर्णांकerrupt setup */
	ग_लिखोb(MCFSIM_ICR_LEVEL6 | MCFSIM_ICR_PRI1, MCFSIM_UART1ICR);
	ग_लिखोb(MCF_IRQ_UART0, MCFUART_BASE0 + MCFUART_UIVR);
	mcf_mapirq2imr(MCF_IRQ_UART0, MCFINTC_UART0);

	/* UART1 पूर्णांकerrupt setup */
	ग_लिखोb(MCFSIM_ICR_LEVEL6 | MCFSIM_ICR_PRI2, MCFSIM_UART2ICR);
	ग_लिखोb(MCF_IRQ_UART1, MCFUART_BASE1 + MCFUART_UIVR);
	mcf_mapirq2imr(MCF_IRQ_UART1, MCFINTC_UART1);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init mcf_init_devices(व्योम)
अणु
	mcf_uart_set_irq();
	platक्रमm_add_devices(mcf_devices, ARRAY_SIZE(mcf_devices));
	वापस 0;
पूर्ण

arch_initcall(mcf_init_devices);
