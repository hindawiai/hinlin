<शैली गुरु>
/*
 * TI DaVinci DM646x chip specअगरic setup
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

#घोषणा DAVINCI_VPIF_BASE       (0x01C12000)

#घोषणा VDD3P3V_VID_MASK	(BIT_MASK(3) | BIT_MASK(2) | BIT_MASK(1) |\
					BIT_MASK(0))
#घोषणा VSCLKDIS_MASK		(BIT_MASK(11) | BIT_MASK(10) | BIT_MASK(9) |\
					BIT_MASK(8))

#घोषणा DM646X_EMAC_BASE		0x01c80000
#घोषणा DM646X_EMAC_MDIO_BASE		(DM646X_EMAC_BASE + 0x4000)
#घोषणा DM646X_EMAC_CNTRL_OFFSET	0x0000
#घोषणा DM646X_EMAC_CNTRL_MOD_OFFSET	0x1000
#घोषणा DM646X_EMAC_CNTRL_RAM_OFFSET	0x2000
#घोषणा DM646X_EMAC_CNTRL_RAM_SIZE	0x2000

अटल काष्ठा emac_platक्रमm_data dm646x_emac_pdata = अणु
	.ctrl_reg_offset	= DM646X_EMAC_CNTRL_OFFSET,
	.ctrl_mod_reg_offset	= DM646X_EMAC_CNTRL_MOD_OFFSET,
	.ctrl_ram_offset	= DM646X_EMAC_CNTRL_RAM_OFFSET,
	.ctrl_ram_size		= DM646X_EMAC_CNTRL_RAM_SIZE,
	.version		= EMAC_VERSION_2,
पूर्ण;

अटल काष्ठा resource dm646x_emac_resources[] = अणु
	अणु
		.start	= DM646X_EMAC_BASE,
		.end	= DM646X_EMAC_BASE + SZ_16K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM646X_EMACRXTHINT),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM646X_EMACRXTHINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM646X_EMACRXINT),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM646X_EMACRXINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM646X_EMACTXINT),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM646X_EMACTXINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM646X_EMACMISCINT),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM646X_EMACMISCINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm646x_emac_device = अणु
	.name		= "davinci_emac",
	.id		= 1,
	.dev = अणु
		.platक्रमm_data	= &dm646x_emac_pdata,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(dm646x_emac_resources),
	.resource	= dm646x_emac_resources,
पूर्ण;

अटल काष्ठा resource dm646x_mdio_resources[] = अणु
	अणु
		.start	= DM646X_EMAC_MDIO_BASE,
		.end	= DM646X_EMAC_MDIO_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm646x_mdio_device = अणु
	.name		= "davinci_mdio",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(dm646x_mdio_resources),
	.resource	= dm646x_mdio_resources,
पूर्ण;

/*
 * Device specअगरic mux setup
 *
 *	soc	description	mux  mode   mode  mux	 dbg
 *				reg  offset mask  mode
 */
अटल स्थिर काष्ठा mux_config dm646x_pins[] = अणु
#अगर_घोषित CONFIG_DAVINCI_MUX
MUX_CFG(DM646X, ATAEN,		0,   0,     5,	  1,	 true)

MUX_CFG(DM646X, AUDCK1,		0,   29,    1,	  0,	 false)

MUX_CFG(DM646X, AUDCK0,		0,   28,    1,	  0,	 false)

MUX_CFG(DM646X, CRGMUX,			0,   24,    7,    5,	 true)

MUX_CFG(DM646X, STSOMUX_DISABLE,	0,   22,    3,    0,	 true)

MUX_CFG(DM646X, STSIMUX_DISABLE,	0,   20,    3,    0,	 true)

MUX_CFG(DM646X, PTSOMUX_DISABLE,	0,   18,    3,    0,	 true)

MUX_CFG(DM646X, PTSIMUX_DISABLE,	0,   16,    3,    0,	 true)

MUX_CFG(DM646X, STSOMUX,		0,   22,    3,    2,	 true)

MUX_CFG(DM646X, STSIMUX,		0,   20,    3,    2,	 true)

MUX_CFG(DM646X, PTSOMUX_PARALLEL,	0,   18,    3,    2,	 true)

MUX_CFG(DM646X, PTSIMUX_PARALLEL,	0,   16,    3,    2,	 true)

MUX_CFG(DM646X, PTSOMUX_SERIAL,		0,   18,    3,    3,	 true)

MUX_CFG(DM646X, PTSIMUX_SERIAL,		0,   16,    3,    3,	 true)
#पूर्ण_अगर
पूर्ण;

अटल u8 dm646x_शेष_priorities[DAVINCI_N_AINTC_IRQ] = अणु
	[IRQ_DM646X_VP_VERTINT0]        = 7,
	[IRQ_DM646X_VP_VERTINT1]        = 7,
	[IRQ_DM646X_VP_VERTINT2]        = 7,
	[IRQ_DM646X_VP_VERTINT3]        = 7,
	[IRQ_DM646X_VP_ERRINT]          = 7,
	[IRQ_DM646X_RESERVED_1]         = 7,
	[IRQ_DM646X_RESERVED_2]         = 7,
	[IRQ_DM646X_WDINT]              = 7,
	[IRQ_DM646X_CRGENINT0]          = 7,
	[IRQ_DM646X_CRGENINT1]          = 7,
	[IRQ_DM646X_TSIFINT0]           = 7,
	[IRQ_DM646X_TSIFINT1]           = 7,
	[IRQ_DM646X_VDCEINT]            = 7,
	[IRQ_DM646X_USBINT]             = 7,
	[IRQ_DM646X_USBDMAINT]          = 7,
	[IRQ_DM646X_PCIINT]             = 7,
	[IRQ_CCINT0]                    = 7,    /* dma */
	[IRQ_CCERRINT]                  = 7,    /* dma */
	[IRQ_TCERRINT0]                 = 7,    /* dma */
	[IRQ_TCERRINT]                  = 7,    /* dma */
	[IRQ_DM646X_TCERRINT2]          = 7,
	[IRQ_DM646X_TCERRINT3]          = 7,
	[IRQ_DM646X_IDE]                = 7,
	[IRQ_DM646X_HPIINT]             = 7,
	[IRQ_DM646X_EMACRXTHINT]        = 7,
	[IRQ_DM646X_EMACRXINT]          = 7,
	[IRQ_DM646X_EMACTXINT]          = 7,
	[IRQ_DM646X_EMACMISCINT]        = 7,
	[IRQ_DM646X_MCASP0TXINT]        = 7,
	[IRQ_DM646X_MCASP0RXINT]        = 7,
	[IRQ_DM646X_RESERVED_3]         = 7,
	[IRQ_DM646X_MCASP1TXINT]        = 7,
	[IRQ_TINT0_TINT12]              = 7,    /* घड़ीevent */
	[IRQ_TINT0_TINT34]              = 7,    /* घड़ीsource */
	[IRQ_TINT1_TINT12]              = 7,    /* DSP समयr */
	[IRQ_TINT1_TINT34]              = 7,    /* प्रणाली tick */
	[IRQ_PWMINT0]                   = 7,
	[IRQ_PWMINT1]                   = 7,
	[IRQ_DM646X_VLQINT]             = 7,
	[IRQ_I2C]                       = 7,
	[IRQ_UARTINT0]                  = 7,
	[IRQ_UARTINT1]                  = 7,
	[IRQ_DM646X_UARTINT2]           = 7,
	[IRQ_DM646X_SPINT0]             = 7,
	[IRQ_DM646X_SPINT1]             = 7,
	[IRQ_DM646X_DSP2ARMINT]         = 7,
	[IRQ_DM646X_RESERVED_4]         = 7,
	[IRQ_DM646X_PSCINT]             = 7,
	[IRQ_DM646X_GPIO0]              = 7,
	[IRQ_DM646X_GPIO1]              = 7,
	[IRQ_DM646X_GPIO2]              = 7,
	[IRQ_DM646X_GPIO3]              = 7,
	[IRQ_DM646X_GPIO4]              = 7,
	[IRQ_DM646X_GPIO5]              = 7,
	[IRQ_DM646X_GPIO6]              = 7,
	[IRQ_DM646X_GPIO7]              = 7,
	[IRQ_DM646X_GPIOBNK0]           = 7,
	[IRQ_DM646X_GPIOBNK1]           = 7,
	[IRQ_DM646X_GPIOBNK2]           = 7,
	[IRQ_DM646X_DDRINT]             = 7,
	[IRQ_DM646X_AEMIFINT]           = 7,
	[IRQ_COMMTX]                    = 7,
	[IRQ_COMMRX]                    = 7,
	[IRQ_EMUINT]                    = 7,
पूर्ण;

/*----------------------------------------------------------------------*/

/* Four Transfer Controllers on DM646x */
अटल s8 dm646x_queue_priority_mapping[][2] = अणु
	/* अणुevent queue no, Priorityपूर्ण */
	अणु0, 4पूर्ण,
	अणु1, 0पूर्ण,
	अणु2, 5पूर्ण,
	अणु3, 1पूर्ण,
	अणु-1, -1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map dm646x_edma_map[] = अणु
	अणु "davinci-mcasp.0", "tx", EDMA_FILTER_PARAM(0, 6) पूर्ण,
	अणु "davinci-mcasp.0", "rx", EDMA_FILTER_PARAM(0, 9) पूर्ण,
	अणु "davinci-mcasp.1", "tx", EDMA_FILTER_PARAM(0, 12) पूर्ण,
	अणु "spi_davinci", "tx", EDMA_FILTER_PARAM(0, 16) पूर्ण,
	अणु "spi_davinci", "rx", EDMA_FILTER_PARAM(0, 17) पूर्ण,
पूर्ण;

अटल काष्ठा edma_soc_info dm646x_edma_pdata = अणु
	.queue_priority_mapping	= dm646x_queue_priority_mapping,
	.शेष_queue		= EVENTQ_1,
	.slave_map		= dm646x_edma_map,
	.slavecnt		= ARRAY_SIZE(dm646x_edma_map),
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
		.name	= "edma3_tc2",
		.start	= 0x01c10800,
		.end	= 0x01c10800 + SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "edma3_tc3",
		.start	= 0x01c10c00,
		.end	= 0x01c10c00 + SZ_1K - 1,
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

अटल स्थिर काष्ठा platक्रमm_device_info dm646x_edma_device __initस्थिर = अणु
	.name		= "edma",
	.id		= 0,
	.dma_mask	= DMA_BIT_MASK(32),
	.res		= edma_resources,
	.num_res	= ARRAY_SIZE(edma_resources),
	.data		= &dm646x_edma_pdata,
	.size_data	= माप(dm646x_edma_pdata),
पूर्ण;

अटल काष्ठा resource dm646x_mcasp0_resources[] = अणु
	अणु
		.name	= "mpu",
		.start 	= DAVINCI_DM646X_MCASP0_REG_BASE,
		.end 	= DAVINCI_DM646X_MCASP0_REG_BASE + (SZ_1K << 1) - 1,
		.flags 	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "tx",
		.start	= DAVINCI_DM646X_DMA_MCASP0_AXEVT0,
		.end	= DAVINCI_DM646X_DMA_MCASP0_AXEVT0,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	अणु
		.name	= "rx",
		.start	= DAVINCI_DM646X_DMA_MCASP0_AREVT0,
		.end	= DAVINCI_DM646X_DMA_MCASP0_AREVT0,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	अणु
		.name	= "tx",
		.start	= DAVINCI_INTC_IRQ(IRQ_DM646X_MCASP0TXINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name	= "rx",
		.start	= DAVINCI_INTC_IRQ(IRQ_DM646X_MCASP0RXINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

/* DIT mode only, rx is not supported */
अटल काष्ठा resource dm646x_mcasp1_resources[] = अणु
	अणु
		.name	= "mpu",
		.start	= DAVINCI_DM646X_MCASP1_REG_BASE,
		.end	= DAVINCI_DM646X_MCASP1_REG_BASE + (SZ_1K << 1) - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "tx",
		.start	= DAVINCI_DM646X_DMA_MCASP1_AXEVT1,
		.end	= DAVINCI_DM646X_DMA_MCASP1_AXEVT1,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	अणु
		.name	= "tx",
		.start	= DAVINCI_INTC_IRQ(IRQ_DM646X_MCASP1TXINT),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm646x_mcasp0_device = अणु
	.name		= "davinci-mcasp",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(dm646x_mcasp0_resources),
	.resource	= dm646x_mcasp0_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device dm646x_mcasp1_device = अणु
	.name		= "davinci-mcasp",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(dm646x_mcasp1_resources),
	.resource	= dm646x_mcasp1_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device dm646x_dit_device = अणु
	.name	= "spdif-dit",
	.id	= -1,
पूर्ण;

अटल u64 vpअगर_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा resource vpअगर_resource[] = अणु
	अणु
		.start	= DAVINCI_VPIF_BASE,
		.end	= DAVINCI_VPIF_BASE + 0x03ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device vpअगर_dev = अणु
	.name		= "vpif",
	.id		= -1,
	.dev		= अणु
			.dma_mask 		= &vpअगर_dma_mask,
			.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= vpअगर_resource,
	.num_resources	= ARRAY_SIZE(vpअगर_resource),
पूर्ण;

अटल काष्ठा resource vpअगर_display_resource[] = अणु
	अणु
		.start = DAVINCI_INTC_IRQ(IRQ_DM646X_VP_VERTINT2),
		.end   = DAVINCI_INTC_IRQ(IRQ_DM646X_VP_VERTINT2),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start = DAVINCI_INTC_IRQ(IRQ_DM646X_VP_VERTINT3),
		.end   = DAVINCI_INTC_IRQ(IRQ_DM646X_VP_VERTINT3),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device vpअगर_display_dev = अणु
	.name		= "vpif_display",
	.id		= -1,
	.dev		= अणु
			.dma_mask 		= &vpअगर_dma_mask,
			.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= vpअगर_display_resource,
	.num_resources	= ARRAY_SIZE(vpअगर_display_resource),
पूर्ण;

अटल काष्ठा resource vpअगर_capture_resource[] = अणु
	अणु
		.start = DAVINCI_INTC_IRQ(IRQ_DM646X_VP_VERTINT0),
		.end   = DAVINCI_INTC_IRQ(IRQ_DM646X_VP_VERTINT0),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start = DAVINCI_INTC_IRQ(IRQ_DM646X_VP_VERTINT1),
		.end   = DAVINCI_INTC_IRQ(IRQ_DM646X_VP_VERTINT1),
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device vpअगर_capture_dev = अणु
	.name		= "vpif_capture",
	.id		= -1,
	.dev		= अणु
			.dma_mask 		= &vpअगर_dma_mask,
			.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.resource	= vpअगर_capture_resource,
	.num_resources	= ARRAY_SIZE(vpअगर_capture_resource),
पूर्ण;

अटल काष्ठा resource dm646x_gpio_resources[] = अणु
	अणु	/* रेजिस्टरs */
		.start	= DAVINCI_GPIO_BASE,
		.end	= DAVINCI_GPIO_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु	/* पूर्णांकerrupt */
		.start	= DAVINCI_INTC_IRQ(IRQ_DM646X_GPIOBNK0),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM646X_GPIOBNK0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM646X_GPIOBNK1),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM646X_GPIOBNK1),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DAVINCI_INTC_IRQ(IRQ_DM646X_GPIOBNK2),
		.end	= DAVINCI_INTC_IRQ(IRQ_DM646X_GPIOBNK2),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_gpio_platक्रमm_data dm646x_gpio_platक्रमm_data = अणु
	.no_स्वतः_base	= true,
	.base		= 0,
	.ngpio		= 43,
पूर्ण;

पूर्णांक __init dm646x_gpio_रेजिस्टर(व्योम)
अणु
	वापस davinci_gpio_रेजिस्टर(dm646x_gpio_resources,
				     ARRAY_SIZE(dm646x_gpio_resources),
				     &dm646x_gpio_platक्रमm_data);
पूर्ण
/*----------------------------------------------------------------------*/

अटल काष्ठा map_desc dm646x_io_desc[] = अणु
	अणु
		.भव	= IO_VIRT,
		.pfn		= __phys_to_pfn(IO_PHYS),
		.length		= IO_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

/* Contents of JTAG ID रेजिस्टर used to identअगरy exact cpu type */
अटल काष्ठा davinci_id dm646x_ids[] = अणु
	अणु
		.variant	= 0x0,
		.part_no	= 0xb770,
		.manufacturer	= 0x017,
		.cpu_id		= DAVINCI_CPU_ID_DM6467,
		.name		= "dm6467_rev1.x",
	पूर्ण,
	अणु
		.variant	= 0x1,
		.part_no	= 0xb770,
		.manufacturer	= 0x017,
		.cpu_id		= DAVINCI_CPU_ID_DM6467,
		.name		= "dm6467_rev3.x",
	पूर्ण,
पूर्ण;

/*
 * Bottom half of समयr0 is used क्रम घड़ीevent, top half is used क्रम
 * घड़ीsource.
 */
अटल स्थिर काष्ठा davinci_समयr_cfg dm646x_समयr_cfg = अणु
	.reg = DEFINE_RES_IO(DAVINCI_TIMER0_BASE, SZ_4K),
	.irq = अणु
		DEFINE_RES_IRQ(DAVINCI_INTC_IRQ(IRQ_TINT0_TINT12)),
		DEFINE_RES_IRQ(DAVINCI_INTC_IRQ(IRQ_TINT0_TINT34)),
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_serial8250_port dm646x_serial0_platक्रमm_data[] = अणु
	अणु
		.mapbase	= DAVINCI_UART0_BASE,
		.irq		= DAVINCI_INTC_IRQ(IRQ_UARTINT0),
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
				  UPF_IOREMAP,
		.iotype		= UPIO_MEM32,
		.regshअगरt	= 2,
	पूर्ण,
	अणु
		.flags	= 0,
	पूर्ण
पूर्ण;
अटल काष्ठा plat_serial8250_port dm646x_serial1_platक्रमm_data[] = अणु
	अणु
		.mapbase	= DAVINCI_UART1_BASE,
		.irq		= DAVINCI_INTC_IRQ(IRQ_UARTINT1),
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
				  UPF_IOREMAP,
		.iotype		= UPIO_MEM32,
		.regshअगरt	= 2,
	पूर्ण,
	अणु
		.flags	= 0,
	पूर्ण
पूर्ण;
अटल काष्ठा plat_serial8250_port dm646x_serial2_platक्रमm_data[] = अणु
	अणु
		.mapbase	= DAVINCI_UART2_BASE,
		.irq		= DAVINCI_INTC_IRQ(IRQ_DM646X_UARTINT2),
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
				  UPF_IOREMAP,
		.iotype		= UPIO_MEM32,
		.regshअगरt	= 2,
	पूर्ण,
	अणु
		.flags	= 0,
	पूर्ण
पूर्ण;

काष्ठा platक्रमm_device dm646x_serial_device[] = अणु
	अणु
		.name			= "serial8250",
		.id			= PLAT8250_DEV_PLATFORM,
		.dev			= अणु
			.platक्रमm_data	= dm646x_serial0_platक्रमm_data,
		पूर्ण
	पूर्ण,
	अणु
		.name			= "serial8250",
		.id			= PLAT8250_DEV_PLATFORM1,
		.dev			= अणु
			.platक्रमm_data	= dm646x_serial1_platक्रमm_data,
		पूर्ण
	पूर्ण,
	अणु
		.name			= "serial8250",
		.id			= PLAT8250_DEV_PLATFORM2,
		.dev			= अणु
			.platक्रमm_data	= dm646x_serial2_platक्रमm_data,
		पूर्ण
	पूर्ण,
	अणु
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा davinci_soc_info davinci_soc_info_dm646x = अणु
	.io_desc		= dm646x_io_desc,
	.io_desc_num		= ARRAY_SIZE(dm646x_io_desc),
	.jtag_id_reg		= 0x01c40028,
	.ids			= dm646x_ids,
	.ids_num		= ARRAY_SIZE(dm646x_ids),
	.pinmux_base		= DAVINCI_SYSTEM_MODULE_BASE,
	.pinmux_pins		= dm646x_pins,
	.pinmux_pins_num	= ARRAY_SIZE(dm646x_pins),
	.emac_pdata		= &dm646x_emac_pdata,
	.sram_dma		= 0x10010000,
	.sram_len		= SZ_32K,
पूर्ण;

व्योम __init dm646x_init_mcasp0(काष्ठा snd_platक्रमm_data *pdata)
अणु
	dm646x_mcasp0_device.dev.platक्रमm_data = pdata;
	platक्रमm_device_रेजिस्टर(&dm646x_mcasp0_device);
पूर्ण

व्योम __init dm646x_init_mcasp1(काष्ठा snd_platक्रमm_data *pdata)
अणु
	dm646x_mcasp1_device.dev.platक्रमm_data = pdata;
	platक्रमm_device_रेजिस्टर(&dm646x_mcasp1_device);
	platक्रमm_device_रेजिस्टर(&dm646x_dit_device);
पूर्ण

व्योम dm646x_setup_vpअगर(काष्ठा vpअगर_display_config *display_config,
		       काष्ठा vpअगर_capture_config *capture_config)
अणु
	अचिन्हित पूर्णांक value;

	value = __raw_पढ़ोl(DAVINCI_SYSMOD_VIRT(SYSMOD_VSCLKDIS));
	value &= ~VSCLKDIS_MASK;
	__raw_ग_लिखोl(value, DAVINCI_SYSMOD_VIRT(SYSMOD_VSCLKDIS));

	value = __raw_पढ़ोl(DAVINCI_SYSMOD_VIRT(SYSMOD_VDD3P3VPWDN));
	value &= ~VDD3P3V_VID_MASK;
	__raw_ग_लिखोl(value, DAVINCI_SYSMOD_VIRT(SYSMOD_VDD3P3VPWDN));

	davinci_cfg_reg(DM646X_STSOMUX_DISABLE);
	davinci_cfg_reg(DM646X_STSIMUX_DISABLE);
	davinci_cfg_reg(DM646X_PTSOMUX_DISABLE);
	davinci_cfg_reg(DM646X_PTSIMUX_DISABLE);

	vpअगर_display_dev.dev.platक्रमm_data = display_config;
	vpअगर_capture_dev.dev.platक्रमm_data = capture_config;
	platक्रमm_device_रेजिस्टर(&vpअगर_dev);
	platक्रमm_device_रेजिस्टर(&vpअगर_display_dev);
	platक्रमm_device_रेजिस्टर(&vpअगर_capture_dev);
पूर्ण

पूर्णांक __init dm646x_init_edma(काष्ठा edma_rsv_info *rsv)
अणु
	काष्ठा platक्रमm_device *edma_pdev;

	dm646x_edma_pdata.rsv = rsv;

	edma_pdev = platक्रमm_device_रेजिस्टर_full(&dm646x_edma_device);
	वापस PTR_ERR_OR_ZERO(edma_pdev);
पूर्ण

व्योम __init dm646x_init(व्योम)
अणु
	davinci_common_init(&davinci_soc_info_dm646x);
	davinci_map_sysmod();
पूर्ण

व्योम __init dm646x_init_समय(अचिन्हित दीर्घ ref_clk_rate,
			     अचिन्हित दीर्घ aux_clkin_rate)
अणु
	व्योम __iomem *pll1, *psc;
	काष्ठा clk *clk;
	पूर्णांक rv;

	clk_रेजिस्टर_fixed_rate(शून्य, "ref_clk", शून्य, 0, ref_clk_rate);
	clk_रेजिस्टर_fixed_rate(शून्य, "aux_clkin", शून्य, 0, aux_clkin_rate);

	pll1 = ioremap(DAVINCI_PLL1_BASE, SZ_1K);
	dm646x_pll1_init(शून्य, pll1, शून्य);

	psc = ioremap(DAVINCI_PWR_SLEEP_CNTRL_BASE, SZ_4K);
	dm646x_psc_init(शून्य, psc);

	clk = clk_get(शून्य, "timer0");
	अगर (WARN_ON(IS_ERR(clk))) अणु
		pr_err("Unable to get the timer clock\n");
		वापस;
	पूर्ण

	rv = davinci_समयr_रेजिस्टर(clk, &dm646x_समयr_cfg);
	WARN(rv, "Unable to register the timer: %d\n", rv);
पूर्ण

अटल काष्ठा resource dm646x_pll2_resources[] = अणु
	अणु
		.start	= DAVINCI_PLL2_BASE,
		.end	= DAVINCI_PLL2_BASE + SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm646x_pll2_device = अणु
	.name		= "dm646x-pll2",
	.id		= -1,
	.resource	= dm646x_pll2_resources,
	.num_resources	= ARRAY_SIZE(dm646x_pll2_resources),
पूर्ण;

व्योम __init dm646x_रेजिस्टर_घड़ीs(व्योम)
अणु
	/* PLL1 and PSC are रेजिस्टरed in dm646x_init_समय() */
	platक्रमm_device_रेजिस्टर(&dm646x_pll2_device);
पूर्ण

अटल स्थिर काष्ठा davinci_aपूर्णांकc_config dm646x_aपूर्णांकc_config = अणु
	.reg = अणु
		.start		= DAVINCI_ARM_INTC_BASE,
		.end		= DAVINCI_ARM_INTC_BASE + SZ_4K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	.num_irqs		= 64,
	.prios			= dm646x_शेष_priorities,
पूर्ण;

व्योम __init dm646x_init_irq(व्योम)
अणु
	davinci_aपूर्णांकc_init(&dm646x_aपूर्णांकc_config);
पूर्ण

अटल पूर्णांक __init dm646x_init_devices(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (!cpu_is_davinci_dm646x())
		वापस 0;

	platक्रमm_device_रेजिस्टर(&dm646x_mdio_device);
	platक्रमm_device_रेजिस्टर(&dm646x_emac_device);

	ret = davinci_init_wdt();
	अगर (ret)
		pr_warn("%s: watchdog init failed: %d\n", __func__, ret);

	वापस ret;
पूर्ण
postcore_initcall(dm646x_init_devices);
