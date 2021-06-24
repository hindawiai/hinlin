<शैली गुरु>
/*
 * TI DaVinci DM644x chip specअगरic setup
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
#समावेश <linux/dmaengine.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/irq-davinci-aपूर्णांकc.h>
#समावेश <linux/platक्रमm_data/edma.h>
#समावेश <linux/platक्रमm_data/gpio-davinci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>

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

/*
 * Device specअगरic घड़ीs
 */
#घोषणा DM644X_REF_FREQ		27000000

#घोषणा DM644X_EMAC_BASE		0x01c80000
#घोषणा DM644X_EMAC_MDIO_BASE		(DM644X_EMAC_BASE + 0x4000)
#घोषणा DM644X_EMAC_CNTRL_OFFSET	0x0000
#घोषणा DM644X_EMAC_CNTRL_MOD_OFFSET	0x1000
#घोषणा DM644X_EMAC_CNTRL_RAM_OFFSET	0x2000
#घोषणा DM644X_EMAC_CNTRL_RAM_SIZE	0x2000

अटल काष्ठा emac_platक्रमm_data dm644x_emac_pdata = अणु
	.ctrl_reg_offset	= DM644X_EMAC_CNTRL_OFFSET,
	.ctrl_mod_reg_offset	= DM644X_EMAC_CNTRL_MOD_OFFSET,
	.ctrl_ram_offset	= DM644X_EMAC_CNTRL_RAM_OFFSET,
	.ctrl_ram_size		= DM644X_EMAC_CNTRL_RAM_SIZE,
	.version		= EMAC_VERSION_1,
पूर्ण;

अटल काष्ठा resource dm644x_emac_resources[] = अणु
	अणु
		.start	= DM644X_EMAC_BASE,
		.end	= DM644X_EMAC_BASE + SZ_16K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start = DAVINCI_INTC_IRQ(IRQ_EMACINT),
		.end   = DAVINCI_INTC_IRQ(IRQ_EMACINT),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm644x_emac_device = अणु
       .name		= "davinci_emac",
       .id		= 1,
       .dev = अणु
	       .platक्रमm_data	= &dm644x_emac_pdata,
       पूर्ण,
       .num_resources	= ARRAY_SIZE(dm644x_emac_resources),
       .resource	= dm644x_emac_resources,
पूर्ण;

अटल काष्ठा resource dm644x_mdio_resources[] = अणु
	अणु
		.start	= DM644X_EMAC_MDIO_BASE,
		.end	= DM644X_EMAC_MDIO_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm644x_mdio_device = अणु
	.name		= "davinci_mdio",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(dm644x_mdio_resources),
	.resource	= dm644x_mdio_resources,
पूर्ण;

/*
 * Device specअगरic mux setup
 *
 *	soc	description	mux  mode   mode  mux	 dbg
 *				reg  offset mask  mode
 */
अटल स्थिर काष्ठा mux_config dm644x_pins[] = अणु
#अगर_घोषित CONFIG_DAVINCI_MUX
MUX_CFG(DM644X, HसूचीEN,		0,   16,    1,	  1,	 true)
MUX_CFG(DM644X, ATAEN,		0,   17,    1,	  1,	 true)
MUX_CFG(DM644X, ATAEN_DISABLE,	0,   17,    1,	  0,	 true)

MUX_CFG(DM644X, HPIEN_DISABLE,	0,   29,    1,	  0,	 true)

MUX_CFG(DM644X, AEAW,		0,   0,     31,	  31,	 true)
MUX_CFG(DM644X, AEAW0,		0,   0,     1,	  0,	 true)
MUX_CFG(DM644X, AEAW1,		0,   1,     1,	  0,	 true)
MUX_CFG(DM644X, AEAW2,		0,   2,     1,	  0,	 true)
MUX_CFG(DM644X, AEAW3,		0,   3,     1,	  0,	 true)
MUX_CFG(DM644X, AEAW4,		0,   4,     1,	  0,	 true)

MUX_CFG(DM644X, MSTK,		1,   9,     1,	  0,	 false)

MUX_CFG(DM644X, I2C,		1,   7,     1,	  1,	 false)

MUX_CFG(DM644X, MCBSP,		1,   10,    1,	  1,	 false)

MUX_CFG(DM644X, UART1,		1,   1,     1,	  1,	 true)
MUX_CFG(DM644X, UART2,		1,   2,     1,	  1,	 true)

MUX_CFG(DM644X, PWM0,		1,   4,     1,	  1,	 false)

MUX_CFG(DM644X, PWM1,		1,   5,     1,	  1,	 false)

MUX_CFG(DM644X, PWM2,		1,   6,     1,	  1,	 false)

MUX_CFG(DM644X, VLYNQEN,	0,   15,    1,	  1,	 false)
MUX_CFG(DM644X, VLSCREN,	0,   14,    1,	  1,	 false)
MUX_CFG(DM644X, VLYNQWD,	0,   12,    3,	  3,	 false)

MUX_CFG(DM644X, EMACEN,		0,   31,    1,	  1,	 true)

MUX_CFG(DM644X, GPIO3V,		0,   31,    1,	  0,	 true)

MUX_CFG(DM644X, GPIO0,		0,   24,    1,	  0,	 true)
MUX_CFG(DM644X, GPIO3,		0,   25,    1,	  0,	 false)
MUX_CFG(DM644X, GPIO43_44,	1,   7,     1,	  0,	 false)
MUX_CFG(DM644X, GPIO46_47,	0,   22,    1,	  0,	 true)

MUX_CFG(DM644X, RGB666,		0,   22,    1,	  1,	 true)

MUX_CFG(DM644X, LOEEN,		0,   24,    1,	  1,	 true)
MUX_CFG(DM644X, LFLDEN,		0,   25,    1,	  1,	 false)
#पूर्ण_अगर
पूर्ण;

/* FIQ are pri 0-1; otherwise 2-7, with 7 lowest priority */
अटल u8 dm644x_शेष_priorities[DAVINCI_N_AINTC_IRQ] = अणु
	[IRQ_VDINT0]		= 2,
	[IRQ_VDINT1]		= 6,
	[IRQ_VDINT2]		= 6,
	[IRQ_HISTINT]		= 6,
	[IRQ_H3AINT]		= 6,
	[IRQ_PRVUINT]		= 6,
	[IRQ_RSZINT]		= 6,
	[7]			= 7,
	[IRQ_VENCINT]		= 6,
	[IRQ_ASQINT]		= 6,
	[IRQ_IMXINT]		= 6,
	[IRQ_VLCDINT]		= 6,
	[IRQ_USBINT]		= 4,
	[IRQ_EMACINT]		= 4,
	[14]			= 7,
	[15]			= 7,
	[IRQ_CCINT0]		= 5,	/* dma */
	[IRQ_CCERRINT]		= 5,	/* dma */
	[IRQ_TCERRINT0]		= 5,	/* dma */
	[IRQ_TCERRINT]		= 5,	/* dma */
	[IRQ_PSCIN]		= 7,
	[21]			= 7,
	[IRQ_IDE]		= 4,
	[23]			= 7,
	[IRQ_MBXINT]		= 7,
	[IRQ_MBRINT]		= 7,
	[IRQ_MMCINT]		= 7,
	[IRQ_SDIOINT]		= 7,
	[28]			= 7,
	[IRQ_DDRINT]		= 7,
	[IRQ_AEMIFINT]		= 7,
	[IRQ_VLQINT]		= 4,
	[IRQ_TINT0_TINT12]	= 2,	/* घड़ीevent */
	[IRQ_TINT0_TINT34]	= 2,	/* घड़ीsource */
	[IRQ_TINT1_TINT12]	= 7,	/* DSP समयr */
	[IRQ_TINT1_TINT34]	= 7,	/* प्रणाली tick */
	[IRQ_PWMINT0]		= 7,
	[IRQ_PWMINT1]		= 7,
	[IRQ_PWMINT2]		= 7,
	[IRQ_I2C]		= 3,
	[IRQ_UARTINT0]		= 3,
	[IRQ_UARTINT1]		= 3,
	[IRQ_UARTINT2]		= 3,
	[IRQ_SPINT0]		= 3,
	[IRQ_SPINT1]		= 3,
	[45]			= 7,
	[IRQ_DSP2ARM0]		= 4,
	[IRQ_DSP2ARM1]		= 4,
	[IRQ_GPIO0]		= 7,
	[IRQ_GPIO1]		= 7,
	[IRQ_GPIO2]		= 7,
	[IRQ_GPIO3]		= 7,
	[IRQ_GPIO4]		= 7,
	[IRQ_GPIO5]		= 7,
	[IRQ_GPIO6]		= 7,
	[IRQ_GPIO7]		= 7,
	[IRQ_GPIOBNK0]		= 7,
	[IRQ_GPIOBNK1]		= 7,
	[IRQ_GPIOBNK2]		= 7,
	[IRQ_GPIOBNK3]		= 7,
	[IRQ_GPIOBNK4]		= 7,
	[IRQ_COMMTX]		= 7,
	[IRQ_COMMRX]		= 7,
	[IRQ_EMUINT]		= 7,
पूर्ण;

/*----------------------------------------------------------------------*/

अटल s8 queue_priority_mapping[][2] = अणु
	/* अणुevent queue no, Priorityपूर्ण */
	अणु0, 3पूर्ण,
	अणु1, 7पूर्ण,
	अणु-1, -1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map dm644x_edma_map[] = अणु
	अणु "davinci-mcbsp", "tx", EDMA_FILTER_PARAM(0, 2) पूर्ण,
	अणु "davinci-mcbsp", "rx", EDMA_FILTER_PARAM(0, 3) पूर्ण,
	अणु "spi_davinci", "tx", EDMA_FILTER_PARAM(0, 16) पूर्ण,
	अणु "spi_davinci", "rx", EDMA_FILTER_PARAM(0, 17) पूर्ण,
	अणु "dm6441-mmc.0", "rx", EDMA_FILTER_PARAM(0, 26) पूर्ण,
	अणु "dm6441-mmc.0", "tx", EDMA_FILTER_PARAM(0, 27) पूर्ण,
पूर्ण;

अटल काष्ठा edma_soc_info dm644x_edma_pdata = अणु
	.queue_priority_mapping	= queue_priority_mapping,
	.शेष_queue		= EVENTQ_1,
	.slave_map		= dm644x_edma_map,
	.slavecnt		= ARRAY_SIZE(dm644x_edma_map),
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
	/* not using TC*_ERR */
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info dm644x_edma_device __initस्थिर = अणु
	.name		= "edma",
	.id		= 0,
	.dma_mask	= DMA_BIT_MASK(32),
	.res		= edma_resources,
	.num_res	= ARRAY_SIZE(edma_resources),
	.data		= &dm644x_edma_pdata,
	.size_data	= माप(dm644x_edma_pdata),
पूर्ण;

/* DM6446 EVM uses ASP0; line-out is a pair of RCA jacks */
अटल काष्ठा resource dm644x_asp_resources[] = अणु
	अणु
		.name	= "mpu",
		.start	= DAVINCI_ASP0_BASE,
		.end	= DAVINCI_ASP0_BASE + SZ_8K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= DAVINCI_DMA_ASP0_TX,
		.end	= DAVINCI_DMA_ASP0_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	अणु
		.start	= DAVINCI_DMA_ASP0_RX,
		.end	= DAVINCI_DMA_ASP0_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm644x_asp_device = अणु
	.name		= "davinci-mcbsp",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(dm644x_asp_resources),
	.resource	= dm644x_asp_resources,
पूर्ण;

#घोषणा DM644X_VPSS_BASE	0x01c73400

अटल काष्ठा resource dm644x_vpss_resources[] = अणु
	अणु
		/* VPSS Base address */
		.name		= "vpss",
		.start		= DM644X_VPSS_BASE,
		.end		= DM644X_VPSS_BASE + 0xff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm644x_vpss_device = अणु
	.name			= "vpss",
	.id			= -1,
	.dev.platक्रमm_data	= "dm644x_vpss",
	.num_resources		= ARRAY_SIZE(dm644x_vpss_resources),
	.resource		= dm644x_vpss_resources,
पूर्ण;

अटल काष्ठा resource dm644x_vpfe_resources[] = अणु
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

अटल u64 dm644x_video_dma_mask = DMA_BIT_MASK(32);
अटल काष्ठा resource dm644x_ccdc_resource[] = अणु
	/* CCDC Base address */
	अणु
		.start          = 0x01c70400,
		.end            = 0x01c70400 + 0xff,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm644x_ccdc_dev = अणु
	.name           = "dm644x_ccdc",
	.id             = -1,
	.num_resources  = ARRAY_SIZE(dm644x_ccdc_resource),
	.resource       = dm644x_ccdc_resource,
	.dev = अणु
		.dma_mask               = &dm644x_video_dma_mask,
		.coherent_dma_mask      = DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm644x_vpfe_dev = अणु
	.name		= CAPTURE_DRV_NAME,
	.id		= -1,
	.num_resources	= ARRAY_SIZE(dm644x_vpfe_resources),
	.resource	= dm644x_vpfe_resources,
	.dev = अणु
		.dma_mask		= &dm644x_video_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

#घोषणा DM644X_OSD_BASE		0x01c72600

अटल काष्ठा resource dm644x_osd_resources[] = अणु
	अणु
		.start	= DM644X_OSD_BASE,
		.end	= DM644X_OSD_BASE + 0x1ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm644x_osd_dev = अणु
	.name		= DM644X_VPBE_OSD_SUBDEV_NAME,
	.id		= -1,
	.num_resources	= ARRAY_SIZE(dm644x_osd_resources),
	.resource	= dm644x_osd_resources,
	.dev		= अणु
		.dma_mask		= &dm644x_video_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

#घोषणा DM644X_VENC_BASE		0x01c72400

अटल काष्ठा resource dm644x_venc_resources[] = अणु
	अणु
		.start	= DM644X_VENC_BASE,
		.end	= DM644X_VENC_BASE + 0x17f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

#घोषणा DM644X_VPSS_MUXSEL_PLL2_MODE          BIT(0)
#घोषणा DM644X_VPSS_MUXSEL_VPBECLK_MODE       BIT(1)
#घोषणा DM644X_VPSS_VENCLKEN                  BIT(3)
#घोषणा DM644X_VPSS_DACCLKEN                  BIT(4)

अटल पूर्णांक dm644x_venc_setup_घड़ी(क्रमागत vpbe_enc_timings_type type,
				   अचिन्हित पूर्णांक pघड़ी)
अणु
	पूर्णांक ret = 0;
	u32 v = DM644X_VPSS_VENCLKEN;

	चयन (type) अणु
	हाल VPBE_ENC_STD:
		v |= DM644X_VPSS_DACCLKEN;
		ग_लिखोl(v, DAVINCI_SYSMOD_VIRT(SYSMOD_VPSS_CLKCTL));
		अवरोध;
	हाल VPBE_ENC_DV_TIMINGS:
		अगर (pघड़ी <= 27000000) अणु
			v |= DM644X_VPSS_DACCLKEN;
			ग_लिखोl(v, DAVINCI_SYSMOD_VIRT(SYSMOD_VPSS_CLKCTL));
		पूर्ण अन्यथा अणु
			/*
			 * For HD, use बाह्यal घड़ी source since
			 * HD requires higher घड़ी rate
			 */
			v |= DM644X_VPSS_MUXSEL_VPBECLK_MODE;
			ग_लिखोl(v, DAVINCI_SYSMOD_VIRT(SYSMOD_VPSS_CLKCTL));
		पूर्ण
		अवरोध;
	शेष:
		ret  = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा resource dm644x_v4l2_disp_resources[] = अणु
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_VENCINT),
		.end	= DAVINCI_INTC_IRQ(IRQ_VENCINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm644x_vpbe_display = अणु
	.name		= "vpbe-v4l2",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(dm644x_v4l2_disp_resources),
	.resource	= dm644x_v4l2_disp_resources,
	.dev		= अणु
		.dma_mask		= &dm644x_video_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा venc_platक्रमm_data dm644x_venc_pdata = अणु
	.setup_घड़ी	= dm644x_venc_setup_घड़ी,
पूर्ण;

अटल काष्ठा platक्रमm_device dm644x_venc_dev = अणु
	.name		= DM644X_VPBE_VENC_SUBDEV_NAME,
	.id		= -1,
	.num_resources	= ARRAY_SIZE(dm644x_venc_resources),
	.resource	= dm644x_venc_resources,
	.dev		= अणु
		.dma_mask		= &dm644x_video_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &dm644x_venc_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm644x_vpbe_dev = अणु
	.name		= "vpbe_controller",
	.id		= -1,
	.dev		= अणु
		.dma_mask		= &dm644x_video_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल काष्ठा resource dm644_gpio_resources[] = अणु
	अणु	/* रेजिस्टरs */
		.start	= DAVINCI_GPIO_BASE,
		.end	= DAVINCI_GPIO_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु	/* पूर्णांकerrupt */
		.start	= DAVINCI_INTC_IRQ(IRQ_GPIOBNK0),
		.end	= DAVINCI_INTC_IRQ(IRQ_GPIOBNK0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_GPIOBNK1),
		.end	= DAVINCI_INTC_IRQ(IRQ_GPIOBNK1),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_GPIOBNK2),
		.end	= DAVINCI_INTC_IRQ(IRQ_GPIOBNK2),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_GPIOBNK3),
		.end	= DAVINCI_INTC_IRQ(IRQ_GPIOBNK3),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_GPIOBNK4),
		.end	= DAVINCI_INTC_IRQ(IRQ_GPIOBNK4),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_gpio_platक्रमm_data dm644_gpio_platक्रमm_data = अणु
	.no_स्वतः_base	= true,
	.base		= 0,
	.ngpio		= 71,
पूर्ण;

पूर्णांक __init dm644x_gpio_रेजिस्टर(व्योम)
अणु
	वापस davinci_gpio_रेजिस्टर(dm644_gpio_resources,
				     ARRAY_SIZE(dm644_gpio_resources),
				     &dm644_gpio_platक्रमm_data);
पूर्ण
/*----------------------------------------------------------------------*/

अटल काष्ठा map_desc dm644x_io_desc[] = अणु
	अणु
		.भव	= IO_VIRT,
		.pfn		= __phys_to_pfn(IO_PHYS),
		.length		= IO_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

/* Contents of JTAG ID रेजिस्टर used to identअगरy exact cpu type */
अटल काष्ठा davinci_id dm644x_ids[] = अणु
	अणु
		.variant	= 0x0,
		.part_no	= 0xb700,
		.manufacturer	= 0x017,
		.cpu_id		= DAVINCI_CPU_ID_DM6446,
		.name		= "dm6446",
	पूर्ण,
	अणु
		.variant	= 0x1,
		.part_no	= 0xb700,
		.manufacturer	= 0x017,
		.cpu_id		= DAVINCI_CPU_ID_DM6446,
		.name		= "dm6446a",
	पूर्ण,
पूर्ण;

/*
 * Bottom half of समयr0 is used क्रम घड़ीevent, top half is used क्रम
 * घड़ीsource.
 */
अटल स्थिर काष्ठा davinci_समयr_cfg dm644x_समयr_cfg = अणु
	.reg = DEFINE_RES_IO(DAVINCI_TIMER0_BASE, SZ_4K),
	.irq = अणु
		DEFINE_RES_IRQ(DAVINCI_INTC_IRQ(IRQ_TINT0_TINT12)),
		DEFINE_RES_IRQ(DAVINCI_INTC_IRQ(IRQ_TINT0_TINT34)),
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_serial8250_port dm644x_serial0_platक्रमm_data[] = अणु
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
अटल काष्ठा plat_serial8250_port dm644x_serial1_platक्रमm_data[] = अणु
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
अटल काष्ठा plat_serial8250_port dm644x_serial2_platक्रमm_data[] = अणु
	अणु
		.mapbase	= DAVINCI_UART2_BASE,
		.irq		= DAVINCI_INTC_IRQ(IRQ_UARTINT2),
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
				  UPF_IOREMAP,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
	पूर्ण,
	अणु
		.flags	= 0,
	पूर्ण
पूर्ण;

काष्ठा platक्रमm_device dm644x_serial_device[] = अणु
	अणु
		.name			= "serial8250",
		.id			= PLAT8250_DEV_PLATFORM,
		.dev			= अणु
			.platक्रमm_data	= dm644x_serial0_platक्रमm_data,
		पूर्ण
	पूर्ण,
	अणु
		.name			= "serial8250",
		.id			= PLAT8250_DEV_PLATFORM1,
		.dev			= अणु
			.platक्रमm_data	= dm644x_serial1_platक्रमm_data,
		पूर्ण
	पूर्ण,
	अणु
		.name			= "serial8250",
		.id			= PLAT8250_DEV_PLATFORM2,
		.dev			= अणु
			.platक्रमm_data	= dm644x_serial2_platक्रमm_data,
		पूर्ण
	पूर्ण,
	अणु
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा davinci_soc_info davinci_soc_info_dm644x = अणु
	.io_desc		= dm644x_io_desc,
	.io_desc_num		= ARRAY_SIZE(dm644x_io_desc),
	.jtag_id_reg		= 0x01c40028,
	.ids			= dm644x_ids,
	.ids_num		= ARRAY_SIZE(dm644x_ids),
	.pinmux_base		= DAVINCI_SYSTEM_MODULE_BASE,
	.pinmux_pins		= dm644x_pins,
	.pinmux_pins_num	= ARRAY_SIZE(dm644x_pins),
	.emac_pdata		= &dm644x_emac_pdata,
	.sram_dma		= 0x00008000,
	.sram_len		= SZ_16K,
पूर्ण;

व्योम __init dm644x_init_asp(व्योम)
अणु
	davinci_cfg_reg(DM644X_MCBSP);
	platक्रमm_device_रेजिस्टर(&dm644x_asp_device);
पूर्ण

व्योम __init dm644x_init(व्योम)
अणु
	davinci_common_init(&davinci_soc_info_dm644x);
	davinci_map_sysmod();
पूर्ण

व्योम __init dm644x_init_समय(व्योम)
अणु
	व्योम __iomem *pll1, *psc;
	काष्ठा clk *clk;
	पूर्णांक rv;

	clk_रेजिस्टर_fixed_rate(शून्य, "ref_clk", शून्य, 0, DM644X_REF_FREQ);

	pll1 = ioremap(DAVINCI_PLL1_BASE, SZ_1K);
	dm644x_pll1_init(शून्य, pll1, शून्य);

	psc = ioremap(DAVINCI_PWR_SLEEP_CNTRL_BASE, SZ_4K);
	dm644x_psc_init(शून्य, psc);

	clk = clk_get(शून्य, "timer0");
	अगर (WARN_ON(IS_ERR(clk))) अणु
		pr_err("Unable to get the timer clock\n");
		वापस;
	पूर्ण

	rv = davinci_समयr_रेजिस्टर(clk, &dm644x_समयr_cfg);
	WARN(rv, "Unable to register the timer: %d\n", rv);
पूर्ण

अटल काष्ठा resource dm644x_pll2_resources[] = अणु
	अणु
		.start	= DAVINCI_PLL2_BASE,
		.end	= DAVINCI_PLL2_BASE + SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm644x_pll2_device = अणु
	.name		= "dm644x-pll2",
	.id		= -1,
	.resource	= dm644x_pll2_resources,
	.num_resources	= ARRAY_SIZE(dm644x_pll2_resources),
पूर्ण;

व्योम __init dm644x_रेजिस्टर_घड़ीs(व्योम)
अणु
	/* PLL1 and PSC are रेजिस्टरed in dm644x_init_समय() */
	platक्रमm_device_रेजिस्टर(&dm644x_pll2_device);
पूर्ण

पूर्णांक __init dm644x_init_video(काष्ठा vpfe_config *vpfe_cfg,
				काष्ठा vpbe_config *vpbe_cfg)
अणु
	अगर (vpfe_cfg || vpbe_cfg)
		platक्रमm_device_रेजिस्टर(&dm644x_vpss_device);

	अगर (vpfe_cfg) अणु
		dm644x_vpfe_dev.dev.platक्रमm_data = vpfe_cfg;
		platक्रमm_device_रेजिस्टर(&dm644x_ccdc_dev);
		platक्रमm_device_रेजिस्टर(&dm644x_vpfe_dev);
	पूर्ण

	अगर (vpbe_cfg) अणु
		dm644x_vpbe_dev.dev.platक्रमm_data = vpbe_cfg;
		platक्रमm_device_रेजिस्टर(&dm644x_osd_dev);
		platक्रमm_device_रेजिस्टर(&dm644x_venc_dev);
		platक्रमm_device_रेजिस्टर(&dm644x_vpbe_dev);
		platक्रमm_device_रेजिस्टर(&dm644x_vpbe_display);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा davinci_aपूर्णांकc_config dm644x_aपूर्णांकc_config = अणु
	.reg = अणु
		.start		= DAVINCI_ARM_INTC_BASE,
		.end		= DAVINCI_ARM_INTC_BASE + SZ_4K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	.num_irqs		= 64,
	.prios			= dm644x_शेष_priorities,
पूर्ण;

व्योम __init dm644x_init_irq(व्योम)
अणु
	davinci_aपूर्णांकc_init(&dm644x_aपूर्णांकc_config);
पूर्ण

व्योम __init dm644x_init_devices(व्योम)
अणु
	काष्ठा platक्रमm_device *edma_pdev;
	पूर्णांक ret;

	edma_pdev = platक्रमm_device_रेजिस्टर_full(&dm644x_edma_device);
	अगर (IS_ERR(edma_pdev))
		pr_warn("%s: Failed to register eDMA\n", __func__);

	platक्रमm_device_रेजिस्टर(&dm644x_mdio_device);
	platक्रमm_device_रेजिस्टर(&dm644x_emac_device);

	ret = davinci_init_wdt();
	अगर (ret)
		pr_warn("%s: watchdog init failed: %d\n", __func__, ret);

पूर्ण
