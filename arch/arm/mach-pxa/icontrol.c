<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/icontrol.c
 *
 * Support क्रम the iControl and SafeTcam platक्रमms from TMT Services
 * using the Embedian MXM-8x10 Computer on Module
 *
 * Copyright (C) 2009 TMT Services & Supplies (Pty) Ltd.
 *
 * 2010-01-21 Hennie van der Merve <hvdmerwe@पंचांगtservies.co.za>
 */

#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/gpपन.स>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "pxa320.h"
#समावेश "mxm8x10.h"

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/regulator/machine.h>

#समावेश "generic.h"

#घोषणा ICONTROL_MCP251x_nCS1	(15)
#घोषणा ICONTROL_MCP251x_nCS2	(16)
#घोषणा ICONTROL_MCP251x_nCS3	(17)
#घोषणा ICONTROL_MCP251x_nCS4	(24)

#घोषणा ICONTROL_MCP251x_nIRQ1	(74)
#घोषणा ICONTROL_MCP251x_nIRQ2	(75)
#घोषणा ICONTROL_MCP251x_nIRQ3	(76)
#घोषणा ICONTROL_MCP251x_nIRQ4	(77)

अटल काष्ठा pxa2xx_spi_chip mcp251x_chip_info1 = अणु
	.tx_threshold   = 8,
	.rx_threshold   = 128,
	.dma_burst_size = 8,
	.समयout        = 235,
	.gpio_cs        = ICONTROL_MCP251x_nCS1
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip mcp251x_chip_info2 = अणु
	.tx_threshold   = 8,
	.rx_threshold   = 128,
	.dma_burst_size = 8,
	.समयout        = 235,
	.gpio_cs        = ICONTROL_MCP251x_nCS2
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip mcp251x_chip_info3 = अणु
	.tx_threshold   = 8,
	.rx_threshold   = 128,
	.dma_burst_size = 8,
	.समयout        = 235,
	.gpio_cs        = ICONTROL_MCP251x_nCS3
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip mcp251x_chip_info4 = अणु
	.tx_threshold   = 8,
	.rx_threshold   = 128,
	.dma_burst_size = 8,
	.समयout        = 235,
	.gpio_cs        = ICONTROL_MCP251x_nCS4
पूर्ण;

अटल स्थिर काष्ठा property_entry mcp251x_properties[] = अणु
	PROPERTY_ENTRY_U32("clock-frequency", 16000000),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node mcp251x_node = अणु
	.properties = mcp251x_properties,
पूर्ण;

अटल काष्ठा spi_board_info mcp251x_board_info[] = अणु
	अणु
		.modalias        = "mcp2515",
		.max_speed_hz    = 6500000,
		.bus_num         = 3,
		.chip_select     = 0,
		.swnode		 = &mcp251x_node,
		.controller_data = &mcp251x_chip_info1,
		.irq             = PXA_GPIO_TO_IRQ(ICONTROL_MCP251x_nIRQ1)
	पूर्ण,
	अणु
		.modalias        = "mcp2515",
		.max_speed_hz    = 6500000,
		.bus_num         = 3,
		.chip_select     = 1,
		.swnode		 = &mcp251x_node,
		.controller_data = &mcp251x_chip_info2,
		.irq             = PXA_GPIO_TO_IRQ(ICONTROL_MCP251x_nIRQ2)
	पूर्ण,
	अणु
		.modalias        = "mcp2515",
		.max_speed_hz    = 6500000,
		.bus_num         = 4,
		.chip_select     = 0,
		.swnode		 = &mcp251x_node,
		.controller_data = &mcp251x_chip_info3,
		.irq             = PXA_GPIO_TO_IRQ(ICONTROL_MCP251x_nIRQ3)
	पूर्ण,
	अणु
		.modalias        = "mcp2515",
		.max_speed_hz    = 6500000,
		.bus_num         = 4,
		.chip_select     = 1,
		.swnode		 = &mcp251x_node,
		.controller_data = &mcp251x_chip_info4,
		.irq             = PXA_GPIO_TO_IRQ(ICONTROL_MCP251x_nIRQ4)
	पूर्ण
पूर्ण;

अटल काष्ठा pxa2xx_spi_controller pxa_ssp3_spi_master_info = अणु
	.num_chipselect = 2,
	.enable_dma     = 1
पूर्ण;

अटल काष्ठा pxa2xx_spi_controller pxa_ssp4_spi_master_info = अणु
	.num_chipselect = 2,
	.enable_dma     = 1
पूर्ण;

काष्ठा platक्रमm_device pxa_spi_ssp3 = अणु
	.name          = "pxa2xx-spi",
	.id            = 3,
	.dev           = अणु
		.platक्रमm_data = &pxa_ssp3_spi_master_info,
	पूर्ण
पूर्ण;

काष्ठा platक्रमm_device pxa_spi_ssp4 = अणु
	.name          = "pxa2xx-spi",
	.id            = 4,
	.dev           = अणु
		.platक्रमm_data = &pxa_ssp4_spi_master_info,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *icontrol_spi_devices[] __initdata = अणु
	&pxa_spi_ssp3,
	&pxa_spi_ssp4,
पूर्ण;

अटल mfp_cfg_t mfp_can_cfg[] __initdata = अणु
	/* CAN CS lines */
	GPIO15_GPIO,
	GPIO16_GPIO,
	GPIO17_GPIO,
	GPIO24_GPIO,

	/* SPI (SSP3) lines */
	GPIO89_SSP3_SCLK,
	GPIO91_SSP3_TXD,
	GPIO92_SSP3_RXD,

	/* SPI (SSP4) lines */
	GPIO93_SSP4_SCLK,
	GPIO95_SSP4_TXD,
	GPIO96_SSP4_RXD,

	/* CAN nIRQ lines */
	GPIO74_GPIO | MFP_LPM_EDGE_RISE,
	GPIO75_GPIO | MFP_LPM_EDGE_RISE,
	GPIO76_GPIO | MFP_LPM_EDGE_RISE,
	GPIO77_GPIO | MFP_LPM_EDGE_RISE
पूर्ण;

अटल व्योम __init icontrol_can_init(व्योम)
अणु
	pxa3xx_mfp_config(ARRAY_AND_SIZE(mfp_can_cfg));
	platक्रमm_add_devices(ARRAY_AND_SIZE(icontrol_spi_devices));
	spi_रेजिस्टर_board_info(ARRAY_AND_SIZE(mcp251x_board_info));
पूर्ण

अटल व्योम __init icontrol_init(व्योम)
अणु
	mxm_8x10_barebones_init();
	mxm_8x10_usb_host_init();
	mxm_8x10_mmc_init();

	icontrol_can_init();

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

MACHINE_START(ICONTROL, "iControl/SafeTcam boards using Embedian MXM-8x10 CoM")
	.atag_offset	= 0x100,
	.map_io		= pxa3xx_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa3xx_init_irq,
	.handle_irq	= pxa3xx_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= icontrol_init,
	.restart	= pxa_restart,
MACHINE_END
