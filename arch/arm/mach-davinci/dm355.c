<शैली गुरु>
/*
 * TI DaVinci DM355 chip specअगरic setup
 *
 * Author: Kevin Hilman, Deep Root Systems, LLC
 *
 * 2007 (c) Deep Root Systems, LLC. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/davinci.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/irq-davinci-aपूर्णांकc.h>
#समावेश <linux/platक्रमm_data/edma.h>
#समावेश <linux/platक्रमm_data/gpio-davinci.h>
#समावेश <linux/platक्रमm_data/spi-davinci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/spi/spi.h>

#समावेश <यंत्र/mach/map.h>

#समावेश <mach/common.h>
#समावेश <mach/cputype.h>
#समावेश <mach/mux.h>
#समावेश <mach/serial.h>

#समावेश <घड़ीsource/समयr-davinci.h>

#समावेश "asp.h"
#समावेश "davinci.h"
#समावेश "irqs.h"
#समावेश "mux.h"

#घोषणा DM355_UART2_BASE	(IO_PHYS + 0x206000)
#घोषणा DM355_OSD_BASE		(IO_PHYS + 0x70200)
#घोषणा DM355_VENC_BASE		(IO_PHYS + 0x70400)

/*
 * Device specअगरic घड़ीs
 */
#घोषणा DM355_REF_FREQ		24000000	/* 24 or 36 MHz */

अटल u64 dm355_spi0_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource dm355_spi0_resources[] = अणु
	अणु
		.start = 0x01c66000,
		.end   = 0x01c667ff,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start = DAVINCI_INTC_IRQ(IRQ_DM355_SPINT0_0),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_spi_platक्रमm_data dm355_spi0_pdata = अणु
	.version 	= SPI_VERSION_1,
	.num_chipselect = 2,
	.cshold_bug	= true,
	.dma_event_q	= EVENTQ_1,
	.prescaler_limit = 1,
पूर्ण;
अटल काष्ठा platक्रमm_device dm355_spi0_device = अणु
	.name = "spi_davinci",
	.id = 0,
	.dev = अणु
		.dma_mask = &dm355_spi0_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data = &dm355_spi0_pdata,
	पूर्ण,
	.num_resources = ARRAY_SIZE(dm355_spi0_resources),
	.resource = dm355_spi0_resources,
पूर्ण;

व्योम __init dm355_init_spi0(अचिन्हित chipselect_mask,
		स्थिर काष्ठा spi_board_info *info, अचिन्हित len)
अणु
	/* क्रम now, assume we need MISO */
	davinci_cfg_reg(DM355_SPI0_SDI);

	/* not all slaves will be wired up */
	अगर (chipselect_mask & BIT(0))
		davinci_cfg_reg(DM355_SPI0_SDENA0);
	अगर (chipselect_mask & BIT(1))
		davinci_cfg_reg(DM355_SPI0_SDENA1);

	spi_रेजिस्टर_board_info(info, len);

	platक्रमm_device_रेजिस्टर(&dm355_spi0_device);
पूर्ण

/*----------------------------------------------------------------------*/

#घोषणा INTMUX		0x18
#घोषणा EVTMUX		0x1c

/*
 * Device specअगरic mux setup
 *
 *	soc	description	mux  mode   mode  mux	 dbg
 *				reg  offset mask  mode
 */
अटल स्थिर काष्ठा mux_config dm355_pins[] = अणु
#अगर_घोषित CONFIG_DAVINCI_MUX
MUX_CFG(DM355,	MMCSD0,		4,   2,     1,	  0,	 false)

MUX_CFG(DM355,	SD1_CLK,	3,   6,     1,	  1,	 false)
MUX_CFG(DM355,	SD1_CMD,	3,   7,     1,	  1,	 false)
MUX_CFG(DM355,	SD1_DATA3,	3,   8,     3,	  1,	 false)
MUX_CFG(DM355,	SD1_DATA2,	3,   10,    3,	  1,	 false)
MUX_CFG(DM355,	SD1_DATA1,	3,   12,    3,	  1,	 false)
MUX_CFG(DM355,	SD1_DATA0,	3,   14,    3,	  1,	 false)

MUX_CFG(DM355,	I2C_SDA,	3,   19,    1,	  1,	 false)
MUX_CFG(DM355,	I2C_SCL,	3,   20,    1,	  1,	 false)

MUX_CFG(DM355,	MCBSP0_BDX,	3,   0,     1,	  1,	 false)
MUX_CFG(DM355,	MCBSP0_X,	3,   1,     1,	  1,	 false)
MUX_CFG(DM355,	MCBSP0_BFSX,	3,   2,     1,	  1,	 false)
MUX_CFG(DM355,	MCBSP0_BDR,	3,   3,     1,	  1,	 false)
MUX_CFG(DM355,	MCBSP0_R,	3,   4,     1,	  1,	 false)
MUX_CFG(DM355,	MCBSP0_BFSR,	3,   5,     1,	  1,	 false)

MUX_CFG(DM355,	SPI0_SDI,	4,   1,     1,    0,	 false)
MUX_CFG(DM355,	SPI0_SDENA0,	4,   0,     1,    0,	 false)
MUX_CFG(DM355,	SPI0_SDENA1,	3,   28,    1,    1,	 false)

INT_CFG(DM355,  INT_EDMA_CC,	      2,    1,    1,     false)
INT_CFG(DM355,  INT_EDMA_TC0_ERR,     3,    1,    1,     false)
INT_CFG(DM355,  INT_EDMA_TC1_ERR,     4,    1,    1,     false)

EVT_CFG(DM355,  EVT8_ASP1_TX,	      0,    1,    0,     false)
EVT_CFG(DM355,  EVT9_ASP1_RX,	      1,    1,    0,     false)
EVT_CFG(DM355,  EVT26_MMC0_RX,	      2,    1,    0,     false)

MUX_CFG(DM355,	VOUT_FIELD,	1,   18,    3,	  1,	 false)
MUX_CFG(DM355,	VOUT_FIELD_G70,	1,   18,    3,	  0,	 false)
MUX_CFG(DM355,	VOUT_HVSYNC,	1,   16,    1,	  0,	 false)
MUX_CFG(DM355,	VOUT_COUTL_EN,	1,   0,     0xff, 0x55,  false)
MUX_CFG(DM355,	VOUT_COUTH_EN,	1,   8,     0xff, 0x55,  false)

MUX_CFG(DM355,	VIN_PCLK,	0,   14,    1,    1,	 false)
MUX_CFG(DM355,	VIN_CAM_WEN,	0,   13,    1,    1,	 false)
MUX_CFG(DM355,	VIN_CAM_VD,	0,   12,    1,    1,	 false)
MUX_CFG(DM355,	VIN_CAM_HD,	0,   11,    1,    1,	 false)
MUX_CFG(DM355,	VIN_YIN_EN,	0,   10,    1,    1,	 false)
MUX_CFG(DM355,	VIN_CINL_EN,	0,   0,   0xff, 0x55,	 false)
MUX_CFG(DM355,	VIN_CINH_EN,	0,   8,     3,    3,	 false)
#पूर्ण_अगर
पूर्ण;

अटल u8 dm355_शेष_priorities[DAVINCI_N_AINTC_IRQ] = अणु
	[IRQ_DM355_CCDC_VDINT0]		= 2,
	[IRQ_DM355_CCDC_VDINT1]		= 6,
	[IRQ_DM355_CCDC_VDINT2]		= 6,
	[IRQ_DM355_IPIPE_HST]		= 6,
	[IRQ_DM355_H3AINT]		= 6,
	[IRQ_DM355_IPIPE_SDR]		= 6,
	[IRQ_DM355_IPIPEIFINT]		= 6,
	[IRQ_DM355_OSDINT]		= 7,
	[IRQ_DM355_VENCINT]		= 6,
	[IRQ_ASQINT]			= 6,
	[IRQ_IMXINT]			= 6,
	[IRQ_USBINT]			= 4,
	[IRQ_DM355_RTOINT]		= 4,
	[IRQ_DM355_UARTINT2]		= 7,
	[IRQ_DM355_TINT6]		= 7,
	[IRQ_CCINT0]			= 5,	/* dma */
	[IRQ_CCERRINT]			= 5,	/* dma */
	[IRQ_TCERRINT0]			= 5,	/* dma */
	[IRQ_TCERRINT]			= 5,	/* dma */
	[IRQ_DM355_SPINT2_1]		= 7,
	[IRQ_DM355_TINT7]		= 4,
	[IRQ_DM355_SDIOINT0]		= 7,
	[IRQ_MBXINT]			= 7,
	[IRQ_MBRINT]			= 7,
	[IRQ_MMCINT]			= 7,
	[IRQ_DM355_MMCINT1]		= 7,
	[IRQ_DM355_PWMINT3]		= 7,
	[IRQ_DDRINT]			= 7,
	[IRQ_AEMIFINT]			= 7,
	[IRQ_DM355_SDIOINT1]		= 4,
	[IRQ_TINT0_TINT12]		= 2,	/* घड़ीevent */
	[IRQ_TINT0_TINT34]		= 2,	/* घड़ीsource */
	[IRQ_TINT1_TINT12]		= 7,	/* DSP समयr */
	[IRQ_TINT1_TINT34]		= 7,	/* प्रणाली tick */
	[IRQ_PWMINT0]			= 7,
	[IRQ_PWMINT1]			= 7,
	[IRQ_PWMINT2]			= 7,
	[IRQ_I2C]			= 3,
	[IRQ_UARTINT0]			= 3,
	[IRQ_UARTINT1]			= 3,
	[IRQ_DM355_SPINT0_0]		= 3,
	[IRQ_DM355_SPINT0_1]		= 3,
	[IRQ_DM355_GPIO0]		= 3,
	[IRQ_DM355_GPIO1]		= 7,
	[IRQ_DM355_GPIO2]		= 4,
	[IRQ_DM355_GPIO3]		= 4,
	[IRQ_DM355_GPIO4]		= 7,
	[IRQ_DM355_GPIO5]		= 7,
	[IRQ_DM355_GPIO6]		= 7,
	[IRQ_DM355_GPIO7]		= 7,
	[IRQ_DM355_GPIO8]		= 7,
	[IRQ_DM355_GPIO9]		= 7,
	[IRQ_DM355_GPIOBNK0]		= 7,
	[IRQ_DM355_GPIOBNK1]		= 7,
	[IRQ_DM355_GPIOBNK2]		= 7,
	[IRQ_DM355_GPIOBNK3]		= 7,
	[IRQ_DM355_GPIOBNK4]		= 7,
	[IRQ_DM355_GPIOBNK5]		= 7,
	[IRQ_DM355_GPIOBNK6]		= 7,
	[IRQ_COMMTX]			= 7,
	[IRQ_COMMRX]			= 7,
	[IRQ_EMUINT]			= 7,
पूर्ण;

/*----------------------------------------------------------------------*/

अटल s8 queue_priority_mapping[][2] = अणु
	/* अणुevent queue no, Priorityपूर्ण */
	अणु0, 3पूर्ण,
	अणु1, 7पूर्ण,
	अणु-1, -1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map dm355_edma_map[] = अणु
	अणु "davinci-mcbsp.0", "tx", EDMA_FILTER_PARAM(0, 2) पूर्ण,
	अणु "davinci-mcbsp.0", "rx", EDMA_FILTER_PARAM(0, 3) पूर्ण,
	अणु "davinci-mcbsp.1", "tx", EDMA_FILTER_PARAM(0, 8) पूर्ण,
	अणु "davinci-mcbsp.1", "rx", EDMA_FILTER_PARAM(0, 9) पूर्ण,
	अणु "spi_davinci.2", "tx", EDMA_FILTER_PARAM(0, 10) पूर्ण,
	अणु "spi_davinci.2", "rx", EDMA_FILTER_PARAM(0, 11) पूर्ण,
	अणु "spi_davinci.1", "tx", EDMA_FILTER_PARAM(0, 14) पूर्ण,
	अणु "spi_davinci.1", "rx", EDMA_FILTER_PARAM(0, 15) पूर्ण,
	अणु "spi_davinci.0", "tx", EDMA_FILTER_PARAM(0, 16) पूर्ण,
	अणु "spi_davinci.0", "rx", EDMA_FILTER_PARAM(0, 17) पूर्ण,
	अणु "dm6441-mmc.0", "rx", EDMA_FILTER_PARAM(0, 26) पूर्ण,
	अणु "dm6441-mmc.0", "tx", EDMA_FILTER_PARAM(0, 27) पूर्ण,
	अणु "dm6441-mmc.1", "rx", EDMA_FILTER_PARAM(0, 30) पूर्ण,
	अणु "dm6441-mmc.1", "tx", EDMA_FILTER_PARAM(0, 31) पूर्ण,
पूर्ण;

अटल काष्ठा edma_soc_info dm355_edma_pdata = अणु
	.queue_priority_mapping	= queue_priority_mapping,
	.शेष_queue		= EVENTQ_1,
	.slave_map		= dm355_edma_map,
	.slavecnt		= ARRAY_SIZE(dm355_edma_map),
पूर्ण;

अटल काष्ठा resource edma_resources[] = अणु
	अणु
		.name	= "edma3_cc",
		.start	= 0x01c00000,
		.end	= 0x01c00000 + SZ_64K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "edma3_tc0",
		.start	= 0x01c10000,
		.end	= 0x01c10000 + SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "edma3_tc1",
		.start	= 0x01c10400,
		.end	= 0x01c10400 + SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "edma3_ccint",
		.start	= DAVINCI_INTC_IRQ(IRQ_CCINT0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name	= "edma3_ccerrint",
		.start	= DAVINCI_INTC_IRQ(IRQ_CCERRINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	/* not using (or muxing) TC*_ERR */
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info dm355_edma_device __initस्थिर = अणु
	.name		= "edma",
	.id		= 0,
	.dma_mask	= DMA_BIT_MASK(32),
	.res		= edma_resources,
	.num_res	= ARRAY_SIZE(edma_resources),
	.data		= &dm355_edma_pdata,
	.size_data	= माप(dm355_edma_pdata),
पूर्ण;

अटल काष्ठा resource dm355_asp1_resources[] = अणु
	अणु
		.name	= "mpu",
		.start	= DAVINCI_ASP1_BASE,
		.end	= DAVINCI_ASP1_BASE + SZ_8K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= DAVINCI_DMA_ASP1_TX,
		.end	= DAVINCI_DMA_ASP1_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	अणु
		.start	= DAVINCI_DMA_ASP1_RX,
		.end	= DAVINCI_DMA_ASP1_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm355_asp1_device = अणु
	.name		= "davinci-mcbsp",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(dm355_asp1_resources),
	.resource	= dm355_asp1_resources,
पूर्ण;

अटल व्योम dm355_ccdc_setup_pinmux(व्योम)
अणु
	davinci_cfg_reg(DM355_VIN_PCLK);
	davinci_cfg_reg(DM355_VIN_CAM_WEN);
	davinci_cfg_reg(DM355_VIN_CAM_VD);
	davinci_cfg_reg(DM355_VIN_CAM_HD);
	davinci_cfg_reg(DM355_VIN_YIN_EN);
	davinci_cfg_reg(DM355_VIN_CINL_EN);
	davinci_cfg_reg(DM355_VIN_CINH_EN);
पूर्ण

अटल काष्ठा resource dm355_vpss_resources[] = अणु
	अणु
		/* VPSS BL Base address */
		.name		= "vpss",
		.start          = 0x01c70800,
		.end            = 0x01c70800 + 0xff,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
	अणु
		/* VPSS CLK Base address */
		.name		= "vpss",
		.start          = 0x01c70000,
		.end            = 0x01c70000 + 0xf,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm355_vpss_device = अणु
	.name			= "vpss",
	.id			= -1,
	.dev.platक्रमm_data	= "dm355_vpss",
	.num_resources		= ARRAY_SIZE(dm355_vpss_resources),
	.resource		= dm355_vpss_resources,
पूर्ण;

अटल काष्ठा resource vpfe_resources[] = अणु
	अणु
		.start          = DAVINCI_INTC_IRQ(IRQ_VDINT0),
		.end            = DAVINCI_INTC_IRQ(IRQ_VDINT0),
		.flags          = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start          = DAVINCI_INTC_IRQ(IRQ_VDINT1),
		.end            = DAVINCI_INTC_IRQ(IRQ_VDINT1),
		.flags          = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 vpfe_capture_dma_mask = DMA_BIT_MASK(32);
अटल काष्ठा resource dm355_ccdc_resource[] = अणु
	/* CCDC Base address */
	अणु
		.flags          = IORESOURCE_MEM,
		.start          = 0x01c70600,
		.end            = 0x01c70600 + 0x1ff,
	पूर्ण,
पूर्ण;
अटल काष्ठा platक्रमm_device dm355_ccdc_dev = अणु
	.name           = "dm355_ccdc",
	.id             = -1,
	.num_resources  = ARRAY_SIZE(dm355_ccdc_resource),
	.resource       = dm355_ccdc_resource,
	.dev = अणु
		.dma_mask               = &vpfe_capture_dma_mask,
		.coherent_dma_mask      = DMA_BIT_MASK(32),
		.platक्रमm_data		= dm355_ccdc_setup_pinmux,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device vpfe_capture_dev = अणु
	.name		= CAPTURE_DRV_NAME,
	.id		= -1,
	.num_resources	= ARRAY_SIZE(vpfe_resources),
	.resource	= vpfe_resources,
	.dev = अणु
		.dma_mask		= &vpfe_capture_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा resource dm355_osd_resources[] = अणु
	अणु
		.start	= DM355_OSD_BASE,
		.end	= DM355_OSD_BASE + 0x17f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm355_osd_dev = अणु
	.name		= DM355_VPBE_OSD_SUBDEV_NAME,
	.id		= -1,
	.num_resources	= ARRAY_SIZE(dm355_osd_resources),
	.resource	= dm355_osd_resources,
	.dev		= अणु
		.dma_mask		= &vpfe_capture_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा resource dm355_venc_resources[] = अणु
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_VENCINT),
		.end	= DAVINCI_INTC_IRQ(IRQ_VENCINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	/* venc रेजिस्टरs io space */
	अणु
		.start	= DM355_VENC_BASE,
		.end	= DM355_VENC_BASE + 0x17f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	/* VDAC config रेजिस्टर io space */
	अणु
		.start	= DAVINCI_SYSTEM_MODULE_BASE + SYSMOD_VDAC_CONFIG,
		.end	= DAVINCI_SYSTEM_MODULE_BASE + SYSMOD_VDAC_CONFIG + 3,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource dm355_v4l2_disp_resources[] = अणु
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_VENCINT),
		.end	= DAVINCI_INTC_IRQ(IRQ_VENCINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	/* venc रेजिस्टरs io space */
	अणु
		.start	= DM355_VENC_BASE,
		.end	= DM355_VENC_BASE + 0x17f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल पूर्णांक dm355_vpbe_setup_pinmux(u32 अगर_type, पूर्णांक field)
अणु
	चयन (अगर_type) अणु
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
		davinci_cfg_reg(DM355_VOUT_FIELD_G70);
		अवरोध;
	हाल MEDIA_BUS_FMT_YUYV10_1X20:
		अगर (field)
			davinci_cfg_reg(DM355_VOUT_FIELD);
		अन्यथा
			davinci_cfg_reg(DM355_VOUT_FIELD_G70);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	davinci_cfg_reg(DM355_VOUT_COUTL_EN);
	davinci_cfg_reg(DM355_VOUT_COUTH_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक dm355_venc_setup_घड़ी(क्रमागत vpbe_enc_timings_type type,
				   अचिन्हित पूर्णांक pघड़ी)
अणु
	व्योम __iomem *vpss_clk_ctrl_reg;

	vpss_clk_ctrl_reg = DAVINCI_SYSMOD_VIRT(SYSMOD_VPSS_CLKCTL);

	चयन (type) अणु
	हाल VPBE_ENC_STD:
		ग_लिखोl(VPSS_DACCLKEN_ENABLE | VPSS_VENCCLKEN_ENABLE,
		       vpss_clk_ctrl_reg);
		अवरोध;
	हाल VPBE_ENC_DV_TIMINGS:
		अगर (pघड़ी > 27000000)
			/*
			 * For HD, use बाह्यal घड़ी source since we cannot
			 * support HD mode with पूर्णांकernal घड़ीs.
			 */
			ग_लिखोl(VPSS_MUXSEL_EXTCLK_ENABLE, vpss_clk_ctrl_reg);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device dm355_vpbe_display = अणु
	.name		= "vpbe-v4l2",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(dm355_v4l2_disp_resources),
	.resource	= dm355_v4l2_disp_resources,
	.dev		= अणु
		.dma_mask		= &vpfe_capture_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा venc_platक्रमm_data dm355_venc_pdata = अणु
	.setup_pinmux	= dm355_vpbe_setup_pinmux,
	.setup_घड़ी	= dm355_venc_setup_घड़ी,
पूर्ण;

अटल काष्ठा platक्रमm_device dm355_venc_dev = अणु
	.name		= DM355_VPBE_VENC_SUBDEV_NAME,
	.id		= -1,
	.num_resources	= ARRAY_SIZE(dm355_venc_resources),
	.resource	= dm355_venc_resources,
	.dev		= अणु
		.dma_mask		= &vpfe_capture_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= (व्योम *)&dm355_venc_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm355_vpbe_dev = अणु
	.name		= "vpbe_controller",
	.id		= -1,
	.dev		= अणु
		.dma_mask		= &vpfe_capture_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा resource dm355_gpio_resources[] = अणु
	अणु	/* रेजिस्टरs */
		.start	= DAVINCI_GPIO_BASE,
		.end	= DAVINCI_GPIO_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु	/* पूर्णांकerrupt */
		.start	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK0),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK1),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK1),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK2),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK2),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK3),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK3),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK4),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK4),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK5),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK5),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK6),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM355_GPIOBNK6),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_gpio_platक्रमm_data dm355_gpio_platक्रमm_data = अणु
	.no_स्वतः_base	= true,
	.base		= 0,
	.ngpio		= 104,
पूर्ण;

पूर्णांक __init dm355_gpio_रेजिस्टर(व्योम)
अणु
	वापस davinci_gpio_रेजिस्टर(dm355_gpio_resources,
				     ARRAY_SIZE(dm355_gpio_resources),
				     &dm355_gpio_platक्रमm_data);
पूर्ण
/*----------------------------------------------------------------------*/

अटल काष्ठा map_desc dm355_io_desc[] = अणु
	अणु
		.भव	= IO_VIRT,
		.pfn		= __phys_to_pfn(IO_PHYS),
		.length		= IO_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

/* Contents of JTAG ID रेजिस्टर used to identअगरy exact cpu type */
अटल काष्ठा davinci_id dm355_ids[] = अणु
	अणु
		.variant	= 0x0,
		.part_no	= 0xb73b,
		.manufacturer	= 0x00f,
		.cpu_id		= DAVINCI_CPU_ID_DM355,
		.name		= "dm355",
	पूर्ण,
पूर्ण;

/*
 * Bottom half of समयr0 is used क्रम घड़ीevent, top half is used क्रम
 * घड़ीsource.
 */
अटल स्थिर काष्ठा davinci_समयr_cfg dm355_समयr_cfg = अणु
	.reg = DEFINE_RES_IO(DAVINCI_TIMER0_BASE, SZ_4K),
	.irq = अणु
		DEFINE_RES_IRQ(DAVINCI_INTC_IRQ(IRQ_TINT0_TINT12)),
		DEFINE_RES_IRQ(DAVINCI_INTC_IRQ(IRQ_TINT0_TINT34)),
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_serial8250_port dm355_serial0_platक्रमm_data[] = अणु
	अणु
		.mapbase	= DAVINCI_UART0_BASE,
		.irq		= DAVINCI_INTC_IRQ(IRQ_UARTINT0),
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
				  UPF_IOREMAP,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
	पूर्ण,
	अणु
		.flags	= 0,
	पूर्ण
पूर्ण;
अटल काष्ठा plat_serial8250_port dm355_serial1_platक्रमm_data[] = अणु
	अणु
		.mapbase	= DAVINCI_UART1_BASE,
		.irq		= DAVINCI_INTC_IRQ(IRQ_UARTINT1),
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
				  UPF_IOREMAP,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
	पूर्ण,
	अणु
		.flags	= 0,
	पूर्ण
पूर्ण;
अटल काष्ठा plat_serial8250_port dm355_serial2_platक्रमm_data[] = अणु
	अणु
		.mapbase	= DM355_UART2_BASE,
		.irq		= DAVINCI_INTC_IRQ(IRQ_DM355_UARTINT2),
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
				  UPF_IOREMAP,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
	पूर्ण,
	अणु
		.flags	= 0,
	पूर्ण
पूर्ण;

काष्ठा platक्रमm_device dm355_serial_device[] = अणु
	अणु
		.name			= "serial8250",
		.id			= PLAT8250_DEV_PLATFORM,
		.dev			= अणु
			.platक्रमm_data	= dm355_serial0_platक्रमm_data,
		पूर्ण
	पूर्ण,
	अणु
		.name			= "serial8250",
		.id			= PLAT8250_DEV_PLATFORM1,
		.dev			= अणु
			.platक्रमm_data	= dm355_serial1_platक्रमm_data,
		पूर्ण
	पूर्ण,
	अणु
		.name			= "serial8250",
		.id			= PLAT8250_DEV_PLATFORM2,
		.dev			= अणु
			.platक्रमm_data	= dm355_serial2_platक्रमm_data,
		पूर्ण
	पूर्ण,
	अणु
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा davinci_soc_info davinci_soc_info_dm355 = अणु
	.io_desc		= dm355_io_desc,
	.io_desc_num		= ARRAY_SIZE(dm355_io_desc),
	.jtag_id_reg		= 0x01c40028,
	.ids			= dm355_ids,
	.ids_num		= ARRAY_SIZE(dm355_ids),
	.pinmux_base		= DAVINCI_SYSTEM_MODULE_BASE,
	.pinmux_pins		= dm355_pins,
	.pinmux_pins_num	= ARRAY_SIZE(dm355_pins),
	.sram_dma		= 0x00010000,
	.sram_len		= SZ_32K,
पूर्ण;

व्योम __init dm355_init_asp1(u32 evt_enable)
अणु
	/* we करोn't use ASP1 IRQs, or we'd need to mux them ... */
	अगर (evt_enable & ASP1_TX_EVT_EN)
		davinci_cfg_reg(DM355_EVT8_ASP1_TX);

	अगर (evt_enable & ASP1_RX_EVT_EN)
		davinci_cfg_reg(DM355_EVT9_ASP1_RX);

	platक्रमm_device_रेजिस्टर(&dm355_asp1_device);
पूर्ण

व्योम __init dm355_init(व्योम)
अणु
	davinci_common_init(&davinci_soc_info_dm355);
	davinci_map_sysmod();
पूर्ण

व्योम __init dm355_init_समय(व्योम)
अणु
	व्योम __iomem *pll1, *psc;
	काष्ठा clk *clk;
	पूर्णांक rv;

	clk_रेजिस्टर_fixed_rate(शून्य, "ref_clk", शून्य, 0, DM355_REF_FREQ);

	pll1 = ioremap(DAVINCI_PLL1_BASE, SZ_1K);
	dm355_pll1_init(शून्य, pll1, शून्य);

	psc = ioremap(DAVINCI_PWR_SLEEP_CNTRL_BASE, SZ_4K);
	dm355_psc_init(शून्य, psc);

	clk = clk_get(शून्य, "timer0");
	अगर (WARN_ON(IS_ERR(clk))) अणु
		pr_err("Unable to get the timer clock\n");
		वापस;
	पूर्ण

	rv = davinci_समयr_रेजिस्टर(clk, &dm355_समयr_cfg);
	WARN(rv, "Unable to register the timer: %d\n", rv);
पूर्ण

अटल काष्ठा resource dm355_pll2_resources[] = अणु
	अणु
		.start	= DAVINCI_PLL2_BASE,
		.end	= DAVINCI_PLL2_BASE + SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm355_pll2_device = अणु
	.name		= "dm355-pll2",
	.id		= -1,
	.resource	= dm355_pll2_resources,
	.num_resources	= ARRAY_SIZE(dm355_pll2_resources),
पूर्ण;

व्योम __init dm355_रेजिस्टर_घड़ीs(व्योम)
अणु
	/* PLL1 and PSC are रेजिस्टरed in dm355_init_समय() */
	platक्रमm_device_रेजिस्टर(&dm355_pll2_device);
पूर्ण

पूर्णांक __init dm355_init_video(काष्ठा vpfe_config *vpfe_cfg,
				काष्ठा vpbe_config *vpbe_cfg)
अणु
	अगर (vpfe_cfg || vpbe_cfg)
		platक्रमm_device_रेजिस्टर(&dm355_vpss_device);

	अगर (vpfe_cfg) अणु
		vpfe_capture_dev.dev.platक्रमm_data = vpfe_cfg;
		platक्रमm_device_रेजिस्टर(&dm355_ccdc_dev);
		platक्रमm_device_रेजिस्टर(&vpfe_capture_dev);
	पूर्ण

	अगर (vpbe_cfg) अणु
		dm355_vpbe_dev.dev.platक्रमm_data = vpbe_cfg;
		platक्रमm_device_रेजिस्टर(&dm355_osd_dev);
		platक्रमm_device_रेजिस्टर(&dm355_venc_dev);
		platक्रमm_device_रेजिस्टर(&dm355_vpbe_dev);
		platक्रमm_device_रेजिस्टर(&dm355_vpbe_display);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा davinci_aपूर्णांकc_config dm355_aपूर्णांकc_config = अणु
	.reg = अणु
		.start		= DAVINCI_ARM_INTC_BASE,
		.end		= DAVINCI_ARM_INTC_BASE + SZ_4K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	.num_irqs		= 64,
	.prios			= dm355_शेष_priorities,
पूर्ण;

व्योम __init dm355_init_irq(व्योम)
अणु
	davinci_aपूर्णांकc_init(&dm355_aपूर्णांकc_config);
पूर्ण

अटल पूर्णांक __init dm355_init_devices(व्योम)
अणु
	काष्ठा platक्रमm_device *edma_pdev;
	पूर्णांक ret = 0;

	अगर (!cpu_is_davinci_dm355())
		वापस 0;

	davinci_cfg_reg(DM355_INT_EDMA_CC);
	edma_pdev = platक्रमm_device_रेजिस्टर_full(&dm355_edma_device);
	अगर (IS_ERR(edma_pdev)) अणु
		pr_warn("%s: Failed to register eDMA\n", __func__);
		वापस PTR_ERR(edma_pdev);
	पूर्ण

	ret = davinci_init_wdt();
	अगर (ret)
		pr_warn("%s: watchdog init failed: %d\n", __func__, ret);

	वापस ret;
पूर्ण
postcore_initcall(dm355_init_devices);
