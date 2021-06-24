<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7757 Setup
 *
 * Copyright (C) 2009, 2011  Renesas Solutions Corp.
 *
 *  based on setup-sh7785.c : Copyright (C) 2007  Paul Mundt
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_dma.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/usb/ohci_pdriver.h>
#समावेश <cpu/dma-रेजिस्टर.h>
#समावेश <cpu/sh7757.h>
#समावेश <यंत्र/platक्रमm_early.h>

अटल काष्ठा plat_sci_port scअगर2_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर2_resources[] = अणु
	DEFINE_RES_MEM(0xfe4b0000, 0x100),		/* SCIF2 */
	DEFINE_RES_IRQ(evt2irq(0x700)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर2_device = अणु
	.name		= "sh-sci",
	.id		= 0,
	.resource	= scअगर2_resources,
	.num_resources	= ARRAY_SIZE(scअगर2_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर2_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर3_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर3_resources[] = अणु
	DEFINE_RES_MEM(0xfe4c0000, 0x100),		/* SCIF3 */
	DEFINE_RES_IRQ(evt2irq(0xb80)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर3_device = अणु
	.name		= "sh-sci",
	.id		= 1,
	.resource	= scअगर3_resources,
	.num_resources	= ARRAY_SIZE(scअगर3_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर3_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर4_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
पूर्ण;

अटल काष्ठा resource scअगर4_resources[] = अणु
	DEFINE_RES_MEM(0xfe4d0000, 0x100),		/* SCIF4 */
	DEFINE_RES_IRQ(evt2irq(0xf00)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर4_device = अणु
	.name		= "sh-sci",
	.id		= 2,
	.resource	= scअगर4_resources,
	.num_resources	= ARRAY_SIZE(scअगर4_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर4_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_समयr_config पंचांगu0_platक्रमm_data = अणु
	.channels_mask = 3,
पूर्ण;

अटल काष्ठा resource पंचांगu0_resources[] = अणु
	DEFINE_RES_MEM(0xfe430000, 0x20),
	DEFINE_RES_IRQ(evt2irq(0x580)),
	DEFINE_RES_IRQ(evt2irq(0x5a0)),
पूर्ण;

अटल काष्ठा platक्रमm_device पंचांगu0_device = अणु
	.name		= "sh-tmu",
	.id		= 0,
	.dev = अणु
		.platक्रमm_data	= &पंचांगu0_platक्रमm_data,
	पूर्ण,
	.resource	= पंचांगu0_resources,
	.num_resources	= ARRAY_SIZE(पंचांगu0_resources),
पूर्ण;

अटल काष्ठा resource spi0_resources[] = अणु
	[0] = अणु
		.start	= 0xfe002000,
		.end	= 0xfe0020ff,
		.flags	= IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xcc0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

/* DMA */
अटल स्थिर काष्ठा sh_dmae_slave_config sh7757_dmae0_slaves[] = अणु
	अणु
		.slave_id	= SHDMA_SLAVE_SDHI_TX,
		.addr		= 0x1fe50030,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_16BIT),
		.mid_rid	= 0xc5,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_SDHI_RX,
		.addr		= 0x1fe50030,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_16BIT),
		.mid_rid	= 0xc6,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_MMCIF_TX,
		.addr		= 0x1fcb0034,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_32BIT),
		.mid_rid	= 0xd3,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_MMCIF_RX,
		.addr		= 0x1fcb0034,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_32BIT),
		.mid_rid	= 0xd7,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sh_dmae_slave_config sh7757_dmae1_slaves[] = अणु
	अणु
		.slave_id	= SHDMA_SLAVE_SCIF2_TX,
		.addr		= 0x1f4b000c,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x21,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_SCIF2_RX,
		.addr		= 0x1f4b0014,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x22,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_SCIF3_TX,
		.addr		= 0x1f4c000c,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x29,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_SCIF3_RX,
		.addr		= 0x1f4c0014,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x2a,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_SCIF4_TX,
		.addr		= 0x1f4d000c,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x41,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_SCIF4_RX,
		.addr		= 0x1f4d0014,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x42,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RSPI_TX,
		.addr		= 0xfe480004,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_16BIT),
		.mid_rid	= 0xc1,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RSPI_RX,
		.addr		= 0xfe480004,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_16BIT),
		.mid_rid	= 0xc2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sh_dmae_slave_config sh7757_dmae2_slaves[] = अणु
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC0_TX,
		.addr		= 0x1e500012,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x21,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC0_RX,
		.addr		= 0x1e500013,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x22,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC1_TX,
		.addr		= 0x1e510012,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x29,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC1_RX,
		.addr		= 0x1e510013,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x2a,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC2_TX,
		.addr		= 0x1e520012,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0xa1,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC2_RX,
		.addr		= 0x1e520013,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0xa2,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC3_TX,
		.addr		= 0x1e530012,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0xa9,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC3_RX,
		.addr		= 0x1e530013,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0xaf,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC4_TX,
		.addr		= 0x1e540012,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0xc5,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC4_RX,
		.addr		= 0x1e540013,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0xc6,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sh_dmae_slave_config sh7757_dmae3_slaves[] = अणु
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC5_TX,
		.addr		= 0x1e550012,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x21,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC5_RX,
		.addr		= 0x1e550013,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x22,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC6_TX,
		.addr		= 0x1e560012,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x29,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC6_RX,
		.addr		= 0x1e560013,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x2a,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC7_TX,
		.addr		= 0x1e570012,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x41,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC7_RX,
		.addr		= 0x1e570013,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x42,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC8_TX,
		.addr		= 0x1e580012,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x45,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC8_RX,
		.addr		= 0x1e580013,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x46,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC9_TX,
		.addr		= 0x1e590012,
		.chcr		= SM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x51,
	पूर्ण,
	अणु
		.slave_id	= SHDMA_SLAVE_RIIC9_RX,
		.addr		= 0x1e590013,
		.chcr		= DM_INC | RS_ERS | 0x40000000 |
				  TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x52,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sh_dmae_channel sh7757_dmae_channels[] = अणु
	अणु
		.offset = 0,
		.dmars = 0,
		.dmars_bit = 0,
	पूर्ण, अणु
		.offset = 0x10,
		.dmars = 0,
		.dmars_bit = 8,
	पूर्ण, अणु
		.offset = 0x20,
		.dmars = 4,
		.dmars_bit = 0,
	पूर्ण, अणु
		.offset = 0x30,
		.dmars = 4,
		.dmars_bit = 8,
	पूर्ण, अणु
		.offset = 0x50,
		.dmars = 8,
		.dmars_bit = 0,
	पूर्ण, अणु
		.offset = 0x60,
		.dmars = 8,
		.dmars_bit = 8,
	पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ts_shअगरt[] = TS_SHIFT;

अटल काष्ठा sh_dmae_pdata dma0_platक्रमm_data = अणु
	.slave		= sh7757_dmae0_slaves,
	.slave_num	= ARRAY_SIZE(sh7757_dmae0_slaves),
	.channel	= sh7757_dmae_channels,
	.channel_num	= ARRAY_SIZE(sh7757_dmae_channels),
	.ts_low_shअगरt	= CHCR_TS_LOW_SHIFT,
	.ts_low_mask	= CHCR_TS_LOW_MASK,
	.ts_high_shअगरt	= CHCR_TS_HIGH_SHIFT,
	.ts_high_mask	= CHCR_TS_HIGH_MASK,
	.ts_shअगरt	= ts_shअगरt,
	.ts_shअगरt_num	= ARRAY_SIZE(ts_shअगरt),
	.dmaor_init	= DMAOR_INIT,
पूर्ण;

अटल काष्ठा sh_dmae_pdata dma1_platक्रमm_data = अणु
	.slave		= sh7757_dmae1_slaves,
	.slave_num	= ARRAY_SIZE(sh7757_dmae1_slaves),
	.channel	= sh7757_dmae_channels,
	.channel_num	= ARRAY_SIZE(sh7757_dmae_channels),
	.ts_low_shअगरt	= CHCR_TS_LOW_SHIFT,
	.ts_low_mask	= CHCR_TS_LOW_MASK,
	.ts_high_shअगरt	= CHCR_TS_HIGH_SHIFT,
	.ts_high_mask	= CHCR_TS_HIGH_MASK,
	.ts_shअगरt	= ts_shअगरt,
	.ts_shअगरt_num	= ARRAY_SIZE(ts_shअगरt),
	.dmaor_init	= DMAOR_INIT,
पूर्ण;

अटल काष्ठा sh_dmae_pdata dma2_platक्रमm_data = अणु
	.slave		= sh7757_dmae2_slaves,
	.slave_num	= ARRAY_SIZE(sh7757_dmae2_slaves),
	.channel	= sh7757_dmae_channels,
	.channel_num	= ARRAY_SIZE(sh7757_dmae_channels),
	.ts_low_shअगरt	= CHCR_TS_LOW_SHIFT,
	.ts_low_mask	= CHCR_TS_LOW_MASK,
	.ts_high_shअगरt	= CHCR_TS_HIGH_SHIFT,
	.ts_high_mask	= CHCR_TS_HIGH_MASK,
	.ts_shअगरt	= ts_shअगरt,
	.ts_shअगरt_num	= ARRAY_SIZE(ts_shअगरt),
	.dmaor_init	= DMAOR_INIT,
पूर्ण;

अटल काष्ठा sh_dmae_pdata dma3_platक्रमm_data = अणु
	.slave		= sh7757_dmae3_slaves,
	.slave_num	= ARRAY_SIZE(sh7757_dmae3_slaves),
	.channel	= sh7757_dmae_channels,
	.channel_num	= ARRAY_SIZE(sh7757_dmae_channels),
	.ts_low_shअगरt	= CHCR_TS_LOW_SHIFT,
	.ts_low_mask	= CHCR_TS_LOW_MASK,
	.ts_high_shअगरt	= CHCR_TS_HIGH_SHIFT,
	.ts_high_mask	= CHCR_TS_HIGH_MASK,
	.ts_shअगरt	= ts_shअगरt,
	.ts_shअगरt_num	= ARRAY_SIZE(ts_shअगरt),
	.dmaor_init	= DMAOR_INIT,
पूर्ण;

/* channel 0 to 5 */
अटल काष्ठा resource sh7757_dmae0_resources[] = अणु
	[0] = अणु
		/* Channel रेजिस्टरs and DMAOR */
		.start	= 0xff608020,
		.end	= 0xff60808f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* DMARSx */
		.start	= 0xff609000,
		.end	= 0xff60900b,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "error_irq",
		.start	= evt2irq(0x640),
		.end	= evt2irq(0x640),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE,
	पूर्ण,
पूर्ण;

/* channel 6 to 11 */
अटल काष्ठा resource sh7757_dmae1_resources[] = अणु
	[0] = अणु
		/* Channel रेजिस्टरs and DMAOR */
		.start	= 0xff618020,
		.end	= 0xff61808f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* DMARSx */
		.start	= 0xff619000,
		.end	= 0xff61900b,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "error_irq",
		.start	= evt2irq(0x640),
		.end	= evt2irq(0x640),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 4 */
		.start	= evt2irq(0x7c0),
		.end	= evt2irq(0x7c0),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 5 */
		.start	= evt2irq(0x7c0),
		.end	= evt2irq(0x7c0),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 6 */
		.start	= evt2irq(0xd00),
		.end	= evt2irq(0xd00),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 7 */
		.start	= evt2irq(0xd00),
		.end	= evt2irq(0xd00),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 8 */
		.start	= evt2irq(0xd00),
		.end	= evt2irq(0xd00),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 9 */
		.start	= evt2irq(0xd00),
		.end	= evt2irq(0xd00),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 10 */
		.start	= evt2irq(0xd00),
		.end	= evt2irq(0xd00),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 11 */
		.start	= evt2irq(0xd00),
		.end	= evt2irq(0xd00),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE,
	पूर्ण,
पूर्ण;

/* channel 12 to 17 */
अटल काष्ठा resource sh7757_dmae2_resources[] = अणु
	[0] = अणु
		/* Channel रेजिस्टरs and DMAOR */
		.start	= 0xff708020,
		.end	= 0xff70808f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* DMARSx */
		.start	= 0xff709000,
		.end	= 0xff70900b,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "error_irq",
		.start	= evt2irq(0x2a60),
		.end	= evt2irq(0x2a60),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 12 to 16 */
		.start	= evt2irq(0x2400),
		.end	= evt2irq(0x2480),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		/* IRQ क्रम channel 17 */
		.start	= evt2irq(0x24e0),
		.end	= evt2irq(0x24e0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

/* channel 18 to 23 */
अटल काष्ठा resource sh7757_dmae3_resources[] = अणु
	[0] = अणु
		/* Channel रेजिस्टरs and DMAOR */
		.start	= 0xff718020,
		.end	= 0xff71808f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* DMARSx */
		.start	= 0xff719000,
		.end	= 0xff71900b,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "error_irq",
		.start	= evt2irq(0x2a80),
		.end	= evt2irq(0x2a80),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 18 to 22 */
		.start	= evt2irq(0x2500),
		.end	= evt2irq(0x2580),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		/* IRQ क्रम channel 23 */
		.start	= evt2irq(0x2600),
		.end	= evt2irq(0x2600),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dma0_device = अणु
	.name           = "sh-dma-engine",
	.id             = 0,
	.resource	= sh7757_dmae0_resources,
	.num_resources	= ARRAY_SIZE(sh7757_dmae0_resources),
	.dev            = अणु
		.platक्रमm_data	= &dma0_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dma1_device = अणु
	.name		= "sh-dma-engine",
	.id		= 1,
	.resource	= sh7757_dmae1_resources,
	.num_resources	= ARRAY_SIZE(sh7757_dmae1_resources),
	.dev		= अणु
		.platक्रमm_data	= &dma1_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dma2_device = अणु
	.name		= "sh-dma-engine",
	.id		= 2,
	.resource	= sh7757_dmae2_resources,
	.num_resources	= ARRAY_SIZE(sh7757_dmae2_resources),
	.dev		= अणु
		.platक्रमm_data	= &dma2_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dma3_device = अणु
	.name		= "sh-dma-engine",
	.id		= 3,
	.resource	= sh7757_dmae3_resources,
	.num_resources	= ARRAY_SIZE(sh7757_dmae3_resources),
	.dev		= अणु
		.platक्रमm_data	= &dma3_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device spi0_device = अणु
	.name	= "sh_spi",
	.id	= 0,
	.dev	= अणु
		.dma_mask		= शून्य,
		.coherent_dma_mask	= 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(spi0_resources),
	.resource	= spi0_resources,
पूर्ण;

अटल काष्ठा resource spi1_resources[] = अणु
	अणु
		.start	= 0xffd8ee70,
		.end	= 0xffd8eeff,
		.flags	= IORESOURCE_MEM | IORESOURCE_MEM_8BIT,
	पूर्ण,
	अणु
		.start	= evt2irq(0x8c0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device spi1_device = अणु
	.name	= "sh_spi",
	.id	= 1,
	.num_resources	= ARRAY_SIZE(spi1_resources),
	.resource	= spi1_resources,
पूर्ण;

अटल काष्ठा resource rspi_resources[] = अणु
	अणु
		.start	= 0xfe480000,
		.end	= 0xfe4800ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= evt2irq(0x1d80),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rspi_device = अणु
	.name	= "rspi",
	.id	= 2,
	.num_resources	= ARRAY_SIZE(rspi_resources),
	.resource	= rspi_resources,
पूर्ण;

अटल काष्ठा resource usb_ehci_resources[] = अणु
	[0] = अणु
		.start	= 0xfe4f1000,
		.end	= 0xfe4f10ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0x920),
		.end	= evt2irq(0x920),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device usb_ehci_device = अणु
	.name		= "sh_ehci",
	.id		= -1,
	.dev = अणु
		.dma_mask = &usb_ehci_device.dev.coherent_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
	.num_resources	= ARRAY_SIZE(usb_ehci_resources),
	.resource	= usb_ehci_resources,
पूर्ण;

अटल काष्ठा resource usb_ohci_resources[] = अणु
	[0] = अणु
		.start	= 0xfe4f1800,
		.end	= 0xfe4f18ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0x920),
		.end	= evt2irq(0x920),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा usb_ohci_pdata usb_ohci_pdata;

अटल काष्ठा platक्रमm_device usb_ohci_device = अणु
	.name		= "ohci-platform",
	.id		= -1,
	.dev = अणु
		.dma_mask = &usb_ohci_device.dev.coherent_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data	= &usb_ohci_pdata,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(usb_ohci_resources),
	.resource	= usb_ohci_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7757_devices[] __initdata = अणु
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&पंचांगu0_device,
	&dma0_device,
	&dma1_device,
	&dma2_device,
	&dma3_device,
	&spi0_device,
	&spi1_device,
	&rspi_device,
	&usb_ehci_device,
	&usb_ohci_device,
पूर्ण;

अटल पूर्णांक __init sh7757_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7757_devices,
				    ARRAY_SIZE(sh7757_devices));
पूर्ण
arch_initcall(sh7757_devices_setup);

अटल काष्ठा platक्रमm_device *sh7757_early_devices[] __initdata = अणु
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&पंचांगu0_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7757_early_devices,
				   ARRAY_SIZE(sh7757_early_devices));
पूर्ण

क्रमागत अणु
	UNUSED = 0,

	/* पूर्णांकerrupt sources */

	IRL0_LLLL, IRL0_LLLH, IRL0_LLHL, IRL0_LLHH,
	IRL0_LHLL, IRL0_LHLH, IRL0_LHHL, IRL0_LHHH,
	IRL0_HLLL, IRL0_HLLH, IRL0_HLHL, IRL0_HLHH,
	IRL0_HHLL, IRL0_HHLH, IRL0_HHHL,

	IRL4_LLLL, IRL4_LLLH, IRL4_LLHL, IRL4_LLHH,
	IRL4_LHLL, IRL4_LHLH, IRL4_LHHL, IRL4_LHHH,
	IRL4_HLLL, IRL4_HLLH, IRL4_HLHL, IRL4_HLHH,
	IRL4_HHLL, IRL4_HHLH, IRL4_HHHL,
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7,

	SDHI, DVC,
	IRQ8, IRQ9, IRQ11, IRQ10, IRQ12, IRQ13, IRQ14, IRQ15,
	TMU0, TMU1, TMU2, TMU2_TICPI, TMU3, TMU4, TMU5,
	HUDI,
	ARC4,
	DMAC0_5, DMAC6_7, DMAC8_11,
	SCIF0, SCIF1, SCIF2, SCIF3, SCIF4,
	USB0, USB1,
	JMC,
	SPI0, SPI1,
	TMR01, TMR23, TMR45,
	FRT,
	LPC, LPC5, LPC6, LPC7, LPC8,
	PECI0, PECI1, PECI2, PECI3, PECI4, PECI5,
	ETHERC,
	ADC0, ADC1,
	SIM,
	IIC0_0, IIC0_1, IIC0_2, IIC0_3,
	IIC1_0, IIC1_1, IIC1_2, IIC1_3,
	IIC2_0, IIC2_1, IIC2_2, IIC2_3,
	IIC3_0, IIC3_1, IIC3_2, IIC3_3,
	IIC4_0, IIC4_1, IIC4_2, IIC4_3,
	IIC5_0, IIC5_1, IIC5_2, IIC5_3,
	IIC6_0, IIC6_1, IIC6_2, IIC6_3,
	IIC7_0, IIC7_1, IIC7_2, IIC7_3,
	IIC8_0, IIC8_1, IIC8_2, IIC8_3,
	IIC9_0, IIC9_1, IIC9_2, IIC9_3,
	ONFICTL,
	MMC1, MMC2,
	ECCU,
	PCIC,
	G200,
	RSPI,
	SGPIO,
	DMINT12, DMINT13, DMINT14, DMINT15, DMINT16, DMINT17, DMINT18, DMINT19,
	DMINT20, DMINT21, DMINT22, DMINT23,
	DDRECC,
	TSIP,
	PCIE_BRIDGE,
	WDT0B, WDT1B, WDT2B, WDT3B, WDT4B, WDT5B, WDT6B, WDT7B, WDT8B,
	GETHER0, GETHER1, GETHER2,
	PBIA, PBIB, PBIC,
	DMAE2, DMAE3,
	SERMUX2, SERMUX3,

	/* पूर्णांकerrupt groups */

	TMU012, TMU345,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(SDHI, 0x480), INTC_VECT(SDHI, 0x04a0),
	INTC_VECT(SDHI, 0x4c0),
	INTC_VECT(DVC, 0x4e0),
	INTC_VECT(IRQ8, 0x500), INTC_VECT(IRQ9, 0x520),
	INTC_VECT(IRQ10, 0x540),
	INTC_VECT(TMU0, 0x580), INTC_VECT(TMU1, 0x5a0),
	INTC_VECT(TMU2, 0x5c0), INTC_VECT(TMU2_TICPI, 0x5e0),
	INTC_VECT(HUDI, 0x600),
	INTC_VECT(ARC4, 0x620),
	INTC_VECT(DMAC0_5, 0x640), INTC_VECT(DMAC0_5, 0x660),
	INTC_VECT(DMAC0_5, 0x680), INTC_VECT(DMAC0_5, 0x6a0),
	INTC_VECT(DMAC0_5, 0x6c0),
	INTC_VECT(IRQ11, 0x6e0),
	INTC_VECT(SCIF2, 0x700), INTC_VECT(SCIF2, 0x720),
	INTC_VECT(SCIF2, 0x740), INTC_VECT(SCIF2, 0x760),
	INTC_VECT(DMAC0_5, 0x780), INTC_VECT(DMAC0_5, 0x7a0),
	INTC_VECT(DMAC6_7, 0x7c0), INTC_VECT(DMAC6_7, 0x7e0),
	INTC_VECT(USB0, 0x840),
	INTC_VECT(IRQ12, 0x880),
	INTC_VECT(JMC, 0x8a0),
	INTC_VECT(SPI1, 0x8c0),
	INTC_VECT(IRQ13, 0x8e0), INTC_VECT(IRQ14, 0x900),
	INTC_VECT(USB1, 0x920),
	INTC_VECT(TMR01, 0xa00), INTC_VECT(TMR23, 0xa20),
	INTC_VECT(TMR45, 0xa40),
	INTC_VECT(FRT, 0xa80),
	INTC_VECT(LPC, 0xaa0), INTC_VECT(LPC, 0xac0),
	INTC_VECT(LPC, 0xae0), INTC_VECT(LPC, 0xb00),
	INTC_VECT(LPC, 0xb20),
	INTC_VECT(SCIF0, 0xb40), INTC_VECT(SCIF1, 0xb60),
	INTC_VECT(SCIF3, 0xb80), INTC_VECT(SCIF3, 0xba0),
	INTC_VECT(SCIF3, 0xbc0), INTC_VECT(SCIF3, 0xbe0),
	INTC_VECT(PECI0, 0xc00), INTC_VECT(PECI1, 0xc20),
	INTC_VECT(PECI2, 0xc40),
	INTC_VECT(IRQ15, 0xc60),
	INTC_VECT(ETHERC, 0xc80), INTC_VECT(ETHERC, 0xca0),
	INTC_VECT(SPI0, 0xcc0),
	INTC_VECT(ADC1, 0xce0),
	INTC_VECT(DMAC8_11, 0xd00), INTC_VECT(DMAC8_11, 0xd20),
	INTC_VECT(DMAC8_11, 0xd40), INTC_VECT(DMAC8_11, 0xd60),
	INTC_VECT(SIM, 0xd80), INTC_VECT(SIM, 0xda0),
	INTC_VECT(SIM, 0xdc0), INTC_VECT(SIM, 0xde0),
	INTC_VECT(TMU3, 0xe00), INTC_VECT(TMU4, 0xe20),
	INTC_VECT(TMU5, 0xe40),
	INTC_VECT(ADC0, 0xe60),
	INTC_VECT(SCIF4, 0xf00), INTC_VECT(SCIF4, 0xf20),
	INTC_VECT(SCIF4, 0xf40), INTC_VECT(SCIF4, 0xf60),
	INTC_VECT(IIC0_0, 0x1400), INTC_VECT(IIC0_1, 0x1420),
	INTC_VECT(IIC0_2, 0x1440), INTC_VECT(IIC0_3, 0x1460),
	INTC_VECT(IIC1_0, 0x1480), INTC_VECT(IIC1_1, 0x14e0),
	INTC_VECT(IIC1_2, 0x1500), INTC_VECT(IIC1_3, 0x1520),
	INTC_VECT(IIC2_0, 0x1540), INTC_VECT(IIC2_1, 0x1560),
	INTC_VECT(IIC2_2, 0x1580), INTC_VECT(IIC2_3, 0x1600),
	INTC_VECT(IIC3_0, 0x1620), INTC_VECT(IIC3_1, 0x1640),
	INTC_VECT(IIC3_2, 0x16e0), INTC_VECT(IIC3_3, 0x1700),
	INTC_VECT(IIC4_0, 0x17c0), INTC_VECT(IIC4_1, 0x1800),
	INTC_VECT(IIC4_2, 0x1820), INTC_VECT(IIC4_3, 0x1840),
	INTC_VECT(IIC5_0, 0x1860), INTC_VECT(IIC5_1, 0x1880),
	INTC_VECT(IIC5_2, 0x18a0), INTC_VECT(IIC5_3, 0x18c0),
	INTC_VECT(IIC6_0, 0x18e0), INTC_VECT(IIC6_1, 0x1900),
	INTC_VECT(IIC6_2, 0x1920),
	INTC_VECT(ONFICTL, 0x1960),
	INTC_VECT(IIC6_3, 0x1980),
	INTC_VECT(IIC7_0, 0x19a0), INTC_VECT(IIC7_1, 0x1a00),
	INTC_VECT(IIC7_2, 0x1a20), INTC_VECT(IIC7_3, 0x1a40),
	INTC_VECT(IIC8_0, 0x1a60), INTC_VECT(IIC8_1, 0x1a80),
	INTC_VECT(IIC8_2, 0x1aa0), INTC_VECT(IIC8_3, 0x1b40),
	INTC_VECT(IIC9_0, 0x1b60), INTC_VECT(IIC9_1, 0x1b80),
	INTC_VECT(IIC9_2, 0x1c00), INTC_VECT(IIC9_3, 0x1c20),
	INTC_VECT(MMC1, 0x1c60), INTC_VECT(MMC2, 0x1c80),
	INTC_VECT(ECCU, 0x1cc0),
	INTC_VECT(PCIC, 0x1ce0),
	INTC_VECT(G200, 0x1d00),
	INTC_VECT(RSPI, 0x1d80), INTC_VECT(RSPI, 0x1da0),
	INTC_VECT(RSPI, 0x1dc0), INTC_VECT(RSPI, 0x1de0),
	INTC_VECT(PECI3, 0x1ec0), INTC_VECT(PECI4, 0x1ee0),
	INTC_VECT(PECI5, 0x1f00),
	INTC_VECT(SGPIO, 0x1f80), INTC_VECT(SGPIO, 0x1fa0),
	INTC_VECT(SGPIO, 0x1fc0),
	INTC_VECT(DMINT12, 0x2400), INTC_VECT(DMINT13, 0x2420),
	INTC_VECT(DMINT14, 0x2440), INTC_VECT(DMINT15, 0x2460),
	INTC_VECT(DMINT16, 0x2480), INTC_VECT(DMINT17, 0x24e0),
	INTC_VECT(DMINT18, 0x2500), INTC_VECT(DMINT19, 0x2520),
	INTC_VECT(DMINT20, 0x2540), INTC_VECT(DMINT21, 0x2560),
	INTC_VECT(DMINT22, 0x2580), INTC_VECT(DMINT23, 0x2600),
	INTC_VECT(DDRECC, 0x2620),
	INTC_VECT(TSIP, 0x2640),
	INTC_VECT(PCIE_BRIDGE, 0x27c0),
	INTC_VECT(WDT0B, 0x2800), INTC_VECT(WDT1B, 0x2820),
	INTC_VECT(WDT2B, 0x2840), INTC_VECT(WDT3B, 0x2860),
	INTC_VECT(WDT4B, 0x2880), INTC_VECT(WDT5B, 0x28a0),
	INTC_VECT(WDT6B, 0x28c0), INTC_VECT(WDT7B, 0x28e0),
	INTC_VECT(WDT8B, 0x2900),
	INTC_VECT(GETHER0, 0x2960), INTC_VECT(GETHER1, 0x2980),
	INTC_VECT(GETHER2, 0x29a0),
	INTC_VECT(PBIA, 0x2a00), INTC_VECT(PBIB, 0x2a20),
	INTC_VECT(PBIC, 0x2a40),
	INTC_VECT(DMAE2, 0x2a60), INTC_VECT(DMAE3, 0x2a80),
	INTC_VECT(SERMUX2, 0x2aa0), INTC_VECT(SERMUX3, 0x2b40),
	INTC_VECT(LPC5, 0x2b60), INTC_VECT(LPC6, 0x2b80),
	INTC_VECT(LPC7, 0x2c00), INTC_VECT(LPC8, 0x2c20),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(TMU012, TMU0, TMU1, TMU2, TMU2_TICPI),
	INTC_GROUP(TMU345, TMU3, TMU4, TMU5),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd00044, 0xffd00064, 32, /* INTMSK0 / INTMSKCLR0 */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,

	अणु 0xffd40080, 0xffd40084, 32, /* INTMSK2 / INTMSKCLR2 */
	  अणु IRL0_LLLL, IRL0_LLLH, IRL0_LLHL, IRL0_LLHH,
	    IRL0_LHLL, IRL0_LHLH, IRL0_LHHL, IRL0_LHHH,
	    IRL0_HLLL, IRL0_HLLH, IRL0_HLHL, IRL0_HLHH,
	    IRL0_HHLL, IRL0_HHLH, IRL0_HHHL, 0,
	    IRL4_LLLL, IRL4_LLLH, IRL4_LLHL, IRL4_LLHH,
	    IRL4_LHLL, IRL4_LHLH, IRL4_LHHL, IRL4_LHHH,
	    IRL4_HLLL, IRL4_HLLH, IRL4_HLHL, IRL4_HLHH,
	    IRL4_HHLL, IRL4_HHLH, IRL4_HHHL, 0, पूर्ण पूर्ण,

	अणु 0xffd40038, 0xffd4003c, 32, /* INT2MSKR / INT2MSKCR */
	  अणु 0, 0, 0, 0, 0, 0, 0, 0,
	    0, DMAC8_11, 0, PECI0, LPC, FRT, 0, TMR45,
	    TMR23, TMR01, 0, 0, 0, 0, 0, DMAC0_5,
	    HUDI, 0, 0, SCIF3, SCIF2, SDHI, TMU345, TMU012
	     पूर्ण पूर्ण,

	अणु 0xffd400d0, 0xffd400d4, 32, /* INT2MSKR1 / INT2MSKCR1 */
	  अणु IRQ15, IRQ14, IRQ13, IRQ12, IRQ11, IRQ10, SCIF4, ETHERC,
	    IRQ9, IRQ8, SCIF1, SCIF0, USB0, 0, 0, USB1,
	    ADC1, 0, DMAC6_7, ADC0, SPI0, SIM, PECI2, PECI1,
	    ARC4, 0, SPI1, JMC, 0, 0, 0, DVC
	     पूर्ण पूर्ण,

	अणु 0xffd10038, 0xffd1003c, 32, /* INT2MSKR2 / INT2MSKCR2 */
	  अणु IIC4_1, IIC4_2, IIC5_0, ONFICTL, 0, 0, SGPIO, 0,
	    0, G200, 0, IIC9_2, IIC8_2, IIC8_1, IIC8_0, IIC7_3,
	    IIC7_2, IIC7_1, IIC6_3, IIC0_0, IIC0_1, IIC0_2, IIC0_3, IIC3_1,
	    IIC2_3, 0, IIC2_1, IIC9_1, IIC3_3, IIC1_0, 0, IIC2_2
	     पूर्ण पूर्ण,

	अणु 0xffd100d0, 0xffd100d4, 32, /* INT2MSKR3 / INT2MSKCR3 */
	  अणु MMC1, IIC6_1, IIC6_0, IIC5_1, IIC3_2, IIC2_0, PECI5, MMC2,
	    IIC1_3, IIC1_2, IIC9_0, IIC8_3, IIC4_3, IIC7_0, 0, IIC6_2,
	    PCIC, 0, IIC4_0, 0, ECCU, RSPI, 0, IIC9_3,
	    IIC3_0, 0, IIC5_3, IIC5_2, 0, 0, 0, IIC1_1
	     पूर्ण पूर्ण,

	अणु 0xffd20038, 0xffd2003c, 32, /* INT2MSKR4 / INT2MSKCR4 */
	  अणु WDT0B, WDT1B, WDT3B, GETHER0, 0, 0, 0, 0,
	    0, 0, 0, LPC7, SERMUX2, DMAE3, DMAE2, PBIC,
	    PBIB, PBIA, GETHER1, DMINT12, DMINT13, DMINT14, DMINT15, TSIP,
	    DMINT23, 0, DMINT21, LPC6, 0, DMINT16, 0, DMINT22
	     पूर्ण पूर्ण,

	अणु 0xffd200d0, 0xffd200d4, 32, /* INT2MSKR5 / INT2MSKCR5 */
	  अणु 0, WDT8B, WDT7B, WDT4B, 0, DMINT20, 0, 0,
	    DMINT19, DMINT18, LPC5, SERMUX3, WDT2B, GETHER2, 0, 0,
	    0, 0, PCIE_BRIDGE, 0, 0, 0, 0, LPC8,
	    DDRECC, 0, WDT6B, WDT5B, 0, 0, 0, DMINT17
	     पूर्ण पूर्ण,
पूर्ण;

#घोषणा INTPRI		0xffd00010
#घोषणा INT2PRI0	0xffd40000
#घोषणा INT2PRI1	0xffd40004
#घोषणा INT2PRI2	0xffd40008
#घोषणा INT2PRI3	0xffd4000c
#घोषणा INT2PRI4	0xffd40010
#घोषणा INT2PRI5	0xffd40014
#घोषणा INT2PRI6	0xffd40018
#घोषणा INT2PRI7	0xffd4001c
#घोषणा INT2PRI8	0xffd400a0
#घोषणा INT2PRI9	0xffd400a4
#घोषणा INT2PRI10	0xffd400a8
#घोषणा INT2PRI11	0xffd400ac
#घोषणा INT2PRI12	0xffd400b0
#घोषणा INT2PRI13	0xffd400b4
#घोषणा INT2PRI14	0xffd400b8
#घोषणा INT2PRI15	0xffd400bc
#घोषणा INT2PRI16	0xffd10000
#घोषणा INT2PRI17	0xffd10004
#घोषणा INT2PRI18	0xffd10008
#घोषणा INT2PRI19	0xffd1000c
#घोषणा INT2PRI20	0xffd10010
#घोषणा INT2PRI21	0xffd10014
#घोषणा INT2PRI22	0xffd10018
#घोषणा INT2PRI23	0xffd1001c
#घोषणा INT2PRI24	0xffd100a0
#घोषणा INT2PRI25	0xffd100a4
#घोषणा INT2PRI26	0xffd100a8
#घोषणा INT2PRI27	0xffd100ac
#घोषणा INT2PRI28	0xffd100b0
#घोषणा INT2PRI29	0xffd100b4
#घोषणा INT2PRI30	0xffd100b8
#घोषणा INT2PRI31	0xffd100bc
#घोषणा INT2PRI32	0xffd20000
#घोषणा INT2PRI33	0xffd20004
#घोषणा INT2PRI34	0xffd20008
#घोषणा INT2PRI35	0xffd2000c
#घोषणा INT2PRI36	0xffd20010
#घोषणा INT2PRI37	0xffd20014
#घोषणा INT2PRI38	0xffd20018
#घोषणा INT2PRI39	0xffd2001c
#घोषणा INT2PRI40	0xffd200a0
#घोषणा INT2PRI41	0xffd200a4
#घोषणा INT2PRI42	0xffd200a8
#घोषणा INT2PRI43	0xffd200ac
#घोषणा INT2PRI44	0xffd200b0
#घोषणा INT2PRI45	0xffd200b4
#घोषणा INT2PRI46	0xffd200b8
#घोषणा INT2PRI47	0xffd200bc

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु INTPRI, 0, 32, 4, अणु IRQ0, IRQ1, IRQ2, IRQ3,
			      IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,

	अणु INT2PRI0, 0, 32, 8, अणु TMU0, TMU1, TMU2, TMU2_TICPI पूर्ण पूर्ण,
	अणु INT2PRI1, 0, 32, 8, अणु TMU3, TMU4, TMU5, SDHI पूर्ण पूर्ण,
	अणु INT2PRI2, 0, 32, 8, अणु SCIF2, SCIF3, 0, IRQ8 पूर्ण पूर्ण,
	अणु INT2PRI3, 0, 32, 8, अणु HUDI, DMAC0_5, ADC0, IRQ9 पूर्ण पूर्ण,
	अणु INT2PRI4, 0, 32, 8, अणु IRQ10, 0, TMR01, TMR23 पूर्ण पूर्ण,
	अणु INT2PRI5, 0, 32, 8, अणु TMR45, 0, FRT, LPC पूर्ण पूर्ण,
	अणु INT2PRI6, 0, 32, 8, अणु PECI0, ETHERC, DMAC8_11, 0 पूर्ण पूर्ण,
	अणु INT2PRI7, 0, 32, 8, अणु SCIF4, 0, IRQ11, IRQ12 पूर्ण पूर्ण,
	अणु INT2PRI8, 0, 32, 8, अणु 0, 0, 0, DVC पूर्ण पूर्ण,
	अणु INT2PRI9, 0, 32, 8, अणु ARC4, 0, SPI1, JMC पूर्ण पूर्ण,
	अणु INT2PRI10, 0, 32, 8, अणु SPI0, SIM, PECI2, PECI1 पूर्ण पूर्ण,
	अणु INT2PRI11, 0, 32, 8, अणु ADC1, IRQ13, DMAC6_7, IRQ14 पूर्ण पूर्ण,
	अणु INT2PRI12, 0, 32, 8, अणु USB0, 0, IRQ15, USB1 पूर्ण पूर्ण,
	अणु INT2PRI13, 0, 32, 8, अणु 0, 0, SCIF1, SCIF0 पूर्ण पूर्ण,

	अणु INT2PRI16, 0, 32, 8, अणु IIC2_2, 0, 0, 0 पूर्ण पूर्ण,
	अणु INT2PRI17, 0, 32, 8, अणु 0, 0, 0, IIC1_0 पूर्ण पूर्ण,
	अणु INT2PRI18, 0, 32, 8, अणु IIC3_3, IIC9_1, IIC2_1, IIC1_2 पूर्ण पूर्ण,
	अणु INT2PRI19, 0, 32, 8, अणु IIC2_3, IIC3_1, 0, IIC1_3 पूर्ण पूर्ण,
	अणु INT2PRI20, 0, 32, 8, अणु IIC2_0, IIC6_3, IIC7_1, IIC7_2 पूर्ण पूर्ण,
	अणु INT2PRI21, 0, 32, 8, अणु IIC7_3, IIC8_0, IIC8_1, IIC8_2 पूर्ण पूर्ण,
	अणु INT2PRI22, 0, 32, 8, अणु IIC9_2, MMC2, G200, 0 पूर्ण पूर्ण,
	अणु INT2PRI23, 0, 32, 8, अणु PECI5, SGPIO, IIC3_2, IIC5_1 पूर्ण पूर्ण,
	अणु INT2PRI24, 0, 32, 8, अणु PECI4, PECI3, 0, IIC1_1 पूर्ण पूर्ण,
	अणु INT2PRI25, 0, 32, 8, अणु IIC3_0, 0, IIC5_3, IIC5_2 पूर्ण पूर्ण,
	अणु INT2PRI26, 0, 32, 8, अणु ECCU, RSPI, 0, IIC9_3 पूर्ण पूर्ण,
	अणु INT2PRI27, 0, 32, 8, अणु PCIC, IIC6_0, IIC4_0, IIC6_1 पूर्ण पूर्ण,
	अणु INT2PRI28, 0, 32, 8, अणु IIC4_3, IIC7_0, MMC1, IIC6_2 पूर्ण पूर्ण,
	अणु INT2PRI29, 0, 32, 8, अणु 0, 0, IIC9_0, IIC8_3 पूर्ण पूर्ण,
	अणु INT2PRI30, 0, 32, 8, अणु IIC4_1, IIC4_2, IIC5_0, ONFICTL पूर्ण पूर्ण,
	अणु INT2PRI31, 0, 32, 8, अणु IIC0_0, IIC0_1, IIC0_2, IIC0_3 पूर्ण पूर्ण,
	अणु INT2PRI32, 0, 32, 8, अणु DMINT22, 0, 0, 0 पूर्ण पूर्ण,
	अणु INT2PRI33, 0, 32, 8, अणु 0, 0, 0, DMINT16 पूर्ण पूर्ण,
	अणु INT2PRI34, 0, 32, 8, अणु 0, LPC6, DMINT21, DMINT18 पूर्ण पूर्ण,
	अणु INT2PRI35, 0, 32, 8, अणु DMINT23, TSIP, 0, DMINT19 पूर्ण पूर्ण,
	अणु INT2PRI36, 0, 32, 8, अणु DMINT20, GETHER1, PBIA, PBIB पूर्ण पूर्ण,
	अणु INT2PRI37, 0, 32, 8, अणु PBIC, DMAE2, DMAE3, SERMUX2 पूर्ण पूर्ण,
	अणु INT2PRI38, 0, 32, 8, अणु LPC7, 0, 0, 0 पूर्ण पूर्ण,
	अणु INT2PRI39, 0, 32, 8, अणु 0, 0, 0, WDT4B पूर्ण पूर्ण,
	अणु INT2PRI40, 0, 32, 8, अणु 0, 0, 0, DMINT17 पूर्ण पूर्ण,
	अणु INT2PRI41, 0, 32, 8, अणु DDRECC, 0, WDT6B, WDT5B पूर्ण पूर्ण,
	अणु INT2PRI42, 0, 32, 8, अणु 0, 0, 0, LPC8 पूर्ण पूर्ण,
	अणु INT2PRI43, 0, 32, 8, अणु 0, WDT7B, PCIE_BRIDGE, WDT8B पूर्ण पूर्ण,
	अणु INT2PRI44, 0, 32, 8, अणु WDT2B, GETHER2, 0, 0 पूर्ण पूर्ण,
	अणु INT2PRI45, 0, 32, 8, अणु 0, 0, LPC5, SERMUX3 पूर्ण पूर्ण,
	अणु INT2PRI46, 0, 32, 8, अणु WDT0B, WDT1B, WDT3B, GETHER0 पूर्ण पूर्ण,
	अणु INT2PRI47, 0, 32, 8, अणु DMINT12, DMINT13, DMINT14, DMINT15 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_sense_reg sense_रेजिस्टरs_irq8to15[] __initdata = अणु
	अणु 0xffd100f8, 32, 2, /* ICR2 */   अणु IRQ15, IRQ14, IRQ13, IRQ12,
					    IRQ11, IRQ10, IRQ9, IRQ8 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc, "sh7757", vectors, groups,
			 mask_रेजिस्टरs, prio_रेजिस्टरs,
			 sense_रेजिस्टरs_irq8to15);

/* Support क्रम बाह्यal पूर्णांकerrupt pins in IRQ mode */
अटल काष्ठा पूर्णांकc_vect vectors_irq0123[] __initdata = अणु
	INTC_VECT(IRQ0, 0x200), INTC_VECT(IRQ1, 0x240),
	INTC_VECT(IRQ2, 0x280), INTC_VECT(IRQ3, 0x2c0),
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors_irq4567[] __initdata = अणु
	INTC_VECT(IRQ4, 0x300), INTC_VECT(IRQ5, 0x340),
	INTC_VECT(IRQ6, 0x380), INTC_VECT(IRQ7, 0x3c0),
पूर्ण;

अटल काष्ठा पूर्णांकc_sense_reg sense_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd0001c, 32, 2, /* ICR1 */   अणु IRQ0, IRQ1, IRQ2, IRQ3,
					    IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg ack_रेजिस्टरs[] __initdata = अणु
	अणु 0xffd00024, 0, 32, /* INTREQ */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल DECLARE_INTC_DESC_ACK(पूर्णांकc_desc_irq0123, "sh7757-irq0123",
			     vectors_irq0123, शून्य, mask_रेजिस्टरs,
			     prio_रेजिस्टरs, sense_रेजिस्टरs, ack_रेजिस्टरs);

अटल DECLARE_INTC_DESC_ACK(पूर्णांकc_desc_irq4567, "sh7757-irq4567",
			     vectors_irq4567, शून्य, mask_रेजिस्टरs,
			     prio_रेजिस्टरs, sense_रेजिस्टरs, ack_रेजिस्टरs);

/* External पूर्णांकerrupt pins in IRL mode */
अटल काष्ठा पूर्णांकc_vect vectors_irl0123[] __initdata = अणु
	INTC_VECT(IRL0_LLLL, 0x200), INTC_VECT(IRL0_LLLH, 0x220),
	INTC_VECT(IRL0_LLHL, 0x240), INTC_VECT(IRL0_LLHH, 0x260),
	INTC_VECT(IRL0_LHLL, 0x280), INTC_VECT(IRL0_LHLH, 0x2a0),
	INTC_VECT(IRL0_LHHL, 0x2c0), INTC_VECT(IRL0_LHHH, 0x2e0),
	INTC_VECT(IRL0_HLLL, 0x300), INTC_VECT(IRL0_HLLH, 0x320),
	INTC_VECT(IRL0_HLHL, 0x340), INTC_VECT(IRL0_HLHH, 0x360),
	INTC_VECT(IRL0_HHLL, 0x380), INTC_VECT(IRL0_HHLH, 0x3a0),
	INTC_VECT(IRL0_HHHL, 0x3c0),
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors_irl4567[] __initdata = अणु
	INTC_VECT(IRL4_LLLL, 0x200), INTC_VECT(IRL4_LLLH, 0x220),
	INTC_VECT(IRL4_LLHL, 0x240), INTC_VECT(IRL4_LLHH, 0x260),
	INTC_VECT(IRL4_LHLL, 0x280), INTC_VECT(IRL4_LHLH, 0x2a0),
	INTC_VECT(IRL4_LHHL, 0x2c0), INTC_VECT(IRL4_LHHH, 0x2e0),
	INTC_VECT(IRL4_HLLL, 0x300), INTC_VECT(IRL4_HLLH, 0x320),
	INTC_VECT(IRL4_HLHL, 0x340), INTC_VECT(IRL4_HLHH, 0x360),
	INTC_VECT(IRL4_HHLL, 0x380), INTC_VECT(IRL4_HHLH, 0x3a0),
	INTC_VECT(IRL4_HHHL, 0x3c0),
पूर्ण;

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_irl0123, "sh7757-irl0123", vectors_irl0123,
			 शून्य, mask_रेजिस्टरs, शून्य, शून्य);

अटल DECLARE_INTC_DESC(पूर्णांकc_desc_irl4567, "sh7757-irl4567", vectors_irl4567,
			 शून्य, mask_रेजिस्टरs, शून्य, शून्य);

#घोषणा INTC_ICR0	0xffd00000
#घोषणा INTC_INTMSK0	0xffd00044
#घोषणा INTC_INTMSK1	0xffd00048
#घोषणा INTC_INTMSK2	0xffd40080
#घोषणा INTC_INTMSKCLR1	0xffd00068
#घोषणा INTC_INTMSKCLR2	0xffd40084

व्योम __init plat_irq_setup(व्योम)
अणु
	/* disable IRQ3-0 + IRQ7-4 */
	__raw_ग_लिखोl(0xff000000, INTC_INTMSK0);

	/* disable IRL3-0 + IRL7-4 */
	__raw_ग_लिखोl(0xc0000000, INTC_INTMSK1);
	__raw_ग_लिखोl(0xfffefffe, INTC_INTMSK2);

	/* select IRL mode क्रम IRL3-0 + IRL7-4 */
	__raw_ग_लिखोl(__raw_पढ़ोl(INTC_ICR0) & ~0x00c00000, INTC_ICR0);

	/* disable holding function, ie enable "SH-4 Mode" */
	__raw_ग_लिखोl(__raw_पढ़ोl(INTC_ICR0) | 0x00200000, INTC_ICR0);

	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण

व्योम __init plat_irq_setup_pins(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल IRQ_MODE_IRQ7654:
		/* select IRQ mode क्रम IRL7-4 */
		__raw_ग_लिखोl(__raw_पढ़ोl(INTC_ICR0) | 0x00400000, INTC_ICR0);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irq4567);
		अवरोध;
	हाल IRQ_MODE_IRQ3210:
		/* select IRQ mode क्रम IRL3-0 */
		__raw_ग_लिखोl(__raw_पढ़ोl(INTC_ICR0) | 0x00800000, INTC_ICR0);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irq0123);
		अवरोध;
	हाल IRQ_MODE_IRL7654:
		/* enable IRL7-4 but करोn't provide any masking */
		__raw_ग_लिखोl(0x40000000, INTC_INTMSKCLR1);
		__raw_ग_लिखोl(0x0000fffe, INTC_INTMSKCLR2);
		अवरोध;
	हाल IRQ_MODE_IRL3210:
		/* enable IRL0-3 but करोn't provide any masking */
		__raw_ग_लिखोl(0x80000000, INTC_INTMSKCLR1);
		__raw_ग_लिखोl(0xfffe0000, INTC_INTMSKCLR2);
		अवरोध;
	हाल IRQ_MODE_IRL7654_MASK:
		/* enable IRL7-4 and mask using cpu पूर्णांकc controller */
		__raw_ग_लिखोl(0x40000000, INTC_INTMSKCLR1);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irl4567);
		अवरोध;
	हाल IRQ_MODE_IRL3210_MASK:
		/* enable IRL0-3 and mask using cpu पूर्णांकc controller */
		__raw_ग_लिखोl(0x80000000, INTC_INTMSKCLR1);
		रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc_irl0123);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
पूर्ण
