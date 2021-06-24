<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7722 Setup
 *
 *  Copyright (C) 2006 - 2008  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/sh_dma.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/usb/m66592.h>

#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/siu.h>
#समावेश <यंत्र/platक्रमm_early.h>

#समावेश <cpu/dma-रेजिस्टर.h>
#समावेश <cpu/sh7722.h>
#समावेश <cpu/serial.h>

अटल स्थिर काष्ठा sh_dmae_slave_config sh7722_dmae_slaves[] = अणु
	अणु
		.slave_id	= SHDMA_SLAVE_SCIF0_TX,
		.addr		= 0xffe0000c,
		.chcr		= DM_FIX | SM_INC | RS_ERS | TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x21,
	पूर्ण, अणु
		.slave_id	= SHDMA_SLAVE_SCIF0_RX,
		.addr		= 0xffe00014,
		.chcr		= DM_INC | SM_FIX | RS_ERS | TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x22,
	पूर्ण, अणु
		.slave_id	= SHDMA_SLAVE_SCIF1_TX,
		.addr		= 0xffe1000c,
		.chcr		= DM_FIX | SM_INC | RS_ERS | TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x25,
	पूर्ण, अणु
		.slave_id	= SHDMA_SLAVE_SCIF1_RX,
		.addr		= 0xffe10014,
		.chcr		= DM_INC | SM_FIX | RS_ERS | TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x26,
	पूर्ण, अणु
		.slave_id	= SHDMA_SLAVE_SCIF2_TX,
		.addr		= 0xffe2000c,
		.chcr		= DM_FIX | SM_INC | RS_ERS | TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x29,
	पूर्ण, अणु
		.slave_id	= SHDMA_SLAVE_SCIF2_RX,
		.addr		= 0xffe20014,
		.chcr		= DM_INC | SM_FIX | RS_ERS | TS_INDEX2VAL(XMIT_SZ_8BIT),
		.mid_rid	= 0x2a,
	पूर्ण, अणु
		.slave_id	= SHDMA_SLAVE_SIUA_TX,
		.addr		= 0xa454c098,
		.chcr		= DM_FIX | SM_INC | RS_ERS | TS_INDEX2VAL(XMIT_SZ_32BIT),
		.mid_rid	= 0xb1,
	पूर्ण, अणु
		.slave_id	= SHDMA_SLAVE_SIUA_RX,
		.addr		= 0xa454c090,
		.chcr		= DM_INC | SM_FIX | RS_ERS | TS_INDEX2VAL(XMIT_SZ_32BIT),
		.mid_rid	= 0xb2,
	पूर्ण, अणु
		.slave_id	= SHDMA_SLAVE_SIUB_TX,
		.addr		= 0xa454c09c,
		.chcr		= DM_FIX | SM_INC | RS_ERS | TS_INDEX2VAL(XMIT_SZ_32BIT),
		.mid_rid	= 0xb5,
	पूर्ण, अणु
		.slave_id	= SHDMA_SLAVE_SIUB_RX,
		.addr		= 0xa454c094,
		.chcr		= DM_INC | SM_FIX | RS_ERS | TS_INDEX2VAL(XMIT_SZ_32BIT),
		.mid_rid	= 0xb6,
	पूर्ण, अणु
		.slave_id	= SHDMA_SLAVE_SDHI0_TX,
		.addr		= 0x04ce0030,
		.chcr		= DM_FIX | SM_INC | RS_ERS | TS_INDEX2VAL(XMIT_SZ_16BIT),
		.mid_rid	= 0xc1,
	पूर्ण, अणु
		.slave_id	= SHDMA_SLAVE_SDHI0_RX,
		.addr		= 0x04ce0030,
		.chcr		= DM_INC | SM_FIX | RS_ERS | TS_INDEX2VAL(XMIT_SZ_16BIT),
		.mid_rid	= 0xc2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sh_dmae_channel sh7722_dmae_channels[] = अणु
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

अटल काष्ठा sh_dmae_pdata dma_platक्रमm_data = अणु
	.slave		= sh7722_dmae_slaves,
	.slave_num	= ARRAY_SIZE(sh7722_dmae_slaves),
	.channel	= sh7722_dmae_channels,
	.channel_num	= ARRAY_SIZE(sh7722_dmae_channels),
	.ts_low_shअगरt	= CHCR_TS_LOW_SHIFT,
	.ts_low_mask	= CHCR_TS_LOW_MASK,
	.ts_high_shअगरt	= CHCR_TS_HIGH_SHIFT,
	.ts_high_mask	= CHCR_TS_HIGH_MASK,
	.ts_shअगरt	= ts_shअगरt,
	.ts_shअगरt_num	= ARRAY_SIZE(ts_shअगरt),
	.dmaor_init	= DMAOR_INIT,
पूर्ण;

अटल काष्ठा resource sh7722_dmae_resources[] = अणु
	[0] = अणु
		/* Channel रेजिस्टरs and DMAOR */
		.start	= 0xfe008020,
		.end	= 0xfe00808f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* DMARSx */
		.start	= 0xfe009000,
		.end	= 0xfe00900b,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "error_irq",
		.start	= evt2irq(0xbc0),
		.end	= evt2irq(0xbc0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 0-3 */
		.start	= evt2irq(0x800),
		.end	= evt2irq(0x860),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		/* IRQ क्रम channels 4-5 */
		.start	= evt2irq(0xb80),
		.end	= evt2irq(0xba0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device dma_device = अणु
	.name		= "sh-dma-engine",
	.id		= -1,
	.resource	= sh7722_dmae_resources,
	.num_resources	= ARRAY_SIZE(sh7722_dmae_resources),
	.dev		= अणु
		.platक्रमm_data	= &dma_platक्रमm_data,
	पूर्ण,
पूर्ण;

/* Serial */
अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type           = PORT_SCIF,
	.ops		= &sh7722_sci_port_ops,
	.regtype	= SCIx_SH4_SCIF_NO_SCSPTR_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर0_resources[] = अणु
	DEFINE_RES_MEM(0xffe00000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xc00)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर0_device = अणु
	.name		= "sh-sci",
	.id		= 0,
	.resource	= scअगर0_resources,
	.num_resources	= ARRAY_SIZE(scअगर0_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर0_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर1_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type           = PORT_SCIF,
	.ops		= &sh7722_sci_port_ops,
	.regtype	= SCIx_SH4_SCIF_NO_SCSPTR_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर1_resources[] = अणु
	DEFINE_RES_MEM(0xffe10000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xc20)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर1_device = अणु
	.name		= "sh-sci",
	.id		= 1,
	.resource	= scअगर1_resources,
	.num_resources	= ARRAY_SIZE(scअगर1_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर1_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर2_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type           = PORT_SCIF,
	.ops		= &sh7722_sci_port_ops,
	.regtype	= SCIx_SH4_SCIF_NO_SCSPTR_REGTYPE,
पूर्ण;

अटल काष्ठा resource scअगर2_resources[] = अणु
	DEFINE_RES_MEM(0xffe20000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xc40)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर2_device = अणु
	.name		= "sh-sci",
	.id		= 2,
	.resource	= scअगर2_resources,
	.num_resources	= ARRAY_SIZE(scअगर2_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर2_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource rtc_resources[] = अणु
	[0] = अणु
		.start	= 0xa465fec0,
		.end	= 0xa465fec0 + 0x58 - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		/* Period IRQ */
		.start	= evt2irq(0x7a0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		/* Carry IRQ */
		.start	= evt2irq(0x7c0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[3] = अणु
		/* Alarm IRQ */
		.start	= evt2irq(0x780),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "sh-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtc_resources),
	.resource	= rtc_resources,
पूर्ण;

अटल काष्ठा m66592_platdata usbf_platdata = अणु
	.on_chip = 1,
पूर्ण;

अटल काष्ठा resource usbf_resources[] = अणु
	[0] = अणु
		.name	= "USBF",
		.start	= 0x04480000,
		.end	= 0x044800FF,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xa20),
		.end	= evt2irq(0xa20),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device usbf_device = अणु
	.name		= "m66592_udc",
	.id             = 0, /* "usbf0" घड़ी */
	.dev = अणु
		.dma_mask		= शून्य,
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &usbf_platdata,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(usbf_resources),
	.resource	= usbf_resources,
पूर्ण;

अटल काष्ठा resource iic_resources[] = अणु
	[0] = अणु
		.name	= "IIC",
		.start  = 0x04470000,
		.end    = 0x04470017,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0xe00),
		.end    = evt2irq(0xe60),
		.flags  = IORESOURCE_IRQ,
       पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device iic_device = अणु
	.name           = "i2c-sh_mobile",
	.id             = 0, /* "i2c0" घड़ी */
	.num_resources  = ARRAY_SIZE(iic_resources),
	.resource       = iic_resources,
पूर्ण;

अटल काष्ठा uio_info vpu_platक्रमm_data = अणु
	.name = "VPU4",
	.version = "0",
	.irq = evt2irq(0x980),
पूर्ण;

अटल काष्ठा resource vpu_resources[] = अणु
	[0] = अणु
		.name	= "VPU",
		.start	= 0xfe900000,
		.end	= 0xfe9022eb,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* place holder क्रम contiguous memory */
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device vpu_device = अणु
	.name		= "uio_pdrv_genirq",
	.id		= 0,
	.dev = अणु
		.platक्रमm_data	= &vpu_platक्रमm_data,
	पूर्ण,
	.resource	= vpu_resources,
	.num_resources	= ARRAY_SIZE(vpu_resources),
पूर्ण;

अटल काष्ठा uio_info veu_platक्रमm_data = अणु
	.name = "VEU",
	.version = "0",
	.irq = evt2irq(0x8c0),
पूर्ण;

अटल काष्ठा resource veu_resources[] = अणु
	[0] = अणु
		.name	= "VEU",
		.start	= 0xfe920000,
		.end	= 0xfe9200b7,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* place holder क्रम contiguous memory */
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device veu_device = अणु
	.name		= "uio_pdrv_genirq",
	.id		= 1,
	.dev = अणु
		.platक्रमm_data	= &veu_platक्रमm_data,
	पूर्ण,
	.resource	= veu_resources,
	.num_resources	= ARRAY_SIZE(veu_resources),
पूर्ण;

अटल काष्ठा uio_info jpu_platक्रमm_data = अणु
	.name = "JPU",
	.version = "0",
	.irq = evt2irq(0x560),
पूर्ण;

अटल काष्ठा resource jpu_resources[] = अणु
	[0] = अणु
		.name	= "JPU",
		.start	= 0xfea00000,
		.end	= 0xfea102d3,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* place holder क्रम contiguous memory */
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device jpu_device = अणु
	.name		= "uio_pdrv_genirq",
	.id		= 2,
	.dev = अणु
		.platक्रमm_data	= &jpu_platक्रमm_data,
	पूर्ण,
	.resource	= jpu_resources,
	.num_resources	= ARRAY_SIZE(jpu_resources),
पूर्ण;

अटल काष्ठा sh_समयr_config cmt_platक्रमm_data = अणु
	.channels_mask = 0x20,
पूर्ण;

अटल काष्ठा resource cmt_resources[] = अणु
	DEFINE_RES_MEM(0x044a0000, 0x70),
	DEFINE_RES_IRQ(evt2irq(0xf00)),
पूर्ण;

अटल काष्ठा platक्रमm_device cmt_device = अणु
	.name		= "sh-cmt-32",
	.id		= 0,
	.dev = अणु
		.platक्रमm_data	= &cmt_platक्रमm_data,
	पूर्ण,
	.resource	= cmt_resources,
	.num_resources	= ARRAY_SIZE(cmt_resources),
पूर्ण;

अटल काष्ठा sh_समयr_config पंचांगu0_platक्रमm_data = अणु
	.channels_mask = 7,
पूर्ण;

अटल काष्ठा resource पंचांगu0_resources[] = अणु
	DEFINE_RES_MEM(0xffd80000, 0x2c),
	DEFINE_RES_IRQ(evt2irq(0x400)),
	DEFINE_RES_IRQ(evt2irq(0x420)),
	DEFINE_RES_IRQ(evt2irq(0x440)),
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

अटल काष्ठा siu_platक्रमm siu_platक्रमm_data = अणु
	.dma_slave_tx_a	= SHDMA_SLAVE_SIUA_TX,
	.dma_slave_rx_a	= SHDMA_SLAVE_SIUA_RX,
	.dma_slave_tx_b	= SHDMA_SLAVE_SIUB_TX,
	.dma_slave_rx_b	= SHDMA_SLAVE_SIUB_RX,
पूर्ण;

अटल काष्ठा resource siu_resources[] = अणु
	[0] = अणु
		.start	= 0xa4540000,
		.end	= 0xa454c10f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xf80),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device siu_device = अणु
	.name		= "siu-pcm-audio",
	.id		= -1,
	.dev = अणु
		.platक्रमm_data	= &siu_platक्रमm_data,
	पूर्ण,
	.resource	= siu_resources,
	.num_resources	= ARRAY_SIZE(siu_resources),
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7722_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&cmt_device,
	&पंचांगu0_device,
	&rtc_device,
	&usbf_device,
	&iic_device,
	&vpu_device,
	&veu_device,
	&jpu_device,
	&siu_device,
	&dma_device,
पूर्ण;

अटल पूर्णांक __init sh7722_devices_setup(व्योम)
अणु
	platक्रमm_resource_setup_memory(&vpu_device, "vpu", 1 << 20);
	platक्रमm_resource_setup_memory(&veu_device, "veu", 2 << 20);
	platक्रमm_resource_setup_memory(&jpu_device, "jpu", 2 << 20);

	वापस platक्रमm_add_devices(sh7722_devices,
				    ARRAY_SIZE(sh7722_devices));
पूर्ण
arch_initcall(sh7722_devices_setup);

अटल काष्ठा platक्रमm_device *sh7722_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&cmt_device,
	&पंचांगu0_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7722_early_devices,
				   ARRAY_SIZE(sh7722_early_devices));
पूर्ण

क्रमागत अणु
	UNUSED=0,
	ENABLED,
	DISABLED,

	/* पूर्णांकerrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7,
	HUDI,
	SIM_ERI, SIM_RXI, SIM_TXI, SIM_TEI,
	RTC_ATI, RTC_PRI, RTC_CUI,
	DMAC0, DMAC1, DMAC2, DMAC3,
	VIO_CEUI, VIO_BEUI, VIO_VEUI, VOU,
	VPU, TPU,
	USB_USBI0, USB_USBI1,
	DMAC4, DMAC5, DMAC_DADERR,
	KEYSC,
	SCIF0, SCIF1, SCIF2, SIOF0, SIOF1, SIO,
	FLCTL_FLSTEI, FLCTL_FLENDI, FLCTL_FLTREQ0I, FLCTL_FLTREQ1I,
	I2C_ALI, I2C_TACKI, I2C_WAITI, I2C_DTEI,
	CMT, TSIF, SIU, TWODG,
	TMU0, TMU1, TMU2,
	IRDA, JPU, LCDC,

	/* पूर्णांकerrupt groups */
	SIM, RTC, DMAC0123, VIOVOU, USB, DMAC45, FLCTL, I2C, SDHI,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(IRQ0, 0x600), INTC_VECT(IRQ1, 0x620),
	INTC_VECT(IRQ2, 0x640), INTC_VECT(IRQ3, 0x660),
	INTC_VECT(IRQ4, 0x680), INTC_VECT(IRQ5, 0x6a0),
	INTC_VECT(IRQ6, 0x6c0), INTC_VECT(IRQ7, 0x6e0),
	INTC_VECT(SIM_ERI, 0x700), INTC_VECT(SIM_RXI, 0x720),
	INTC_VECT(SIM_TXI, 0x740), INTC_VECT(SIM_TEI, 0x760),
	INTC_VECT(RTC_ATI, 0x780), INTC_VECT(RTC_PRI, 0x7a0),
	INTC_VECT(RTC_CUI, 0x7c0),
	INTC_VECT(DMAC0, 0x800), INTC_VECT(DMAC1, 0x820),
	INTC_VECT(DMAC2, 0x840), INTC_VECT(DMAC3, 0x860),
	INTC_VECT(VIO_CEUI, 0x880), INTC_VECT(VIO_BEUI, 0x8a0),
	INTC_VECT(VIO_VEUI, 0x8c0), INTC_VECT(VOU, 0x8e0),
	INTC_VECT(VPU, 0x980), INTC_VECT(TPU, 0x9a0),
	INTC_VECT(USB_USBI0, 0xa20), INTC_VECT(USB_USBI1, 0xa40),
	INTC_VECT(DMAC4, 0xb80), INTC_VECT(DMAC5, 0xba0),
	INTC_VECT(DMAC_DADERR, 0xbc0), INTC_VECT(KEYSC, 0xbe0),
	INTC_VECT(SCIF0, 0xc00), INTC_VECT(SCIF1, 0xc20),
	INTC_VECT(SCIF2, 0xc40), INTC_VECT(SIOF0, 0xc80),
	INTC_VECT(SIOF1, 0xca0), INTC_VECT(SIO, 0xd00),
	INTC_VECT(FLCTL_FLSTEI, 0xd80), INTC_VECT(FLCTL_FLENDI, 0xda0),
	INTC_VECT(FLCTL_FLTREQ0I, 0xdc0), INTC_VECT(FLCTL_FLTREQ1I, 0xde0),
	INTC_VECT(I2C_ALI, 0xe00), INTC_VECT(I2C_TACKI, 0xe20),
	INTC_VECT(I2C_WAITI, 0xe40), INTC_VECT(I2C_DTEI, 0xe60),
	INTC_VECT(SDHI, 0xe80), INTC_VECT(SDHI, 0xea0),
	INTC_VECT(SDHI, 0xec0), INTC_VECT(SDHI, 0xee0),
	INTC_VECT(CMT, 0xf00), INTC_VECT(TSIF, 0xf20),
	INTC_VECT(SIU, 0xf80), INTC_VECT(TWODG, 0xfa0),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440), INTC_VECT(IRDA, 0x480),
	INTC_VECT(JPU, 0x560), INTC_VECT(LCDC, 0x580),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(SIM, SIM_ERI, SIM_RXI, SIM_TXI, SIM_TEI),
	INTC_GROUP(RTC, RTC_ATI, RTC_PRI, RTC_CUI),
	INTC_GROUP(DMAC0123, DMAC0, DMAC1, DMAC2, DMAC3),
	INTC_GROUP(VIOVOU, VIO_CEUI, VIO_BEUI, VIO_VEUI, VOU),
	INTC_GROUP(USB, USB_USBI0, USB_USBI1),
	INTC_GROUP(DMAC45, DMAC4, DMAC5, DMAC_DADERR),
	INTC_GROUP(FLCTL, FLCTL_FLSTEI, FLCTL_FLENDI,
		   FLCTL_FLTREQ0I, FLCTL_FLTREQ1I),
	INTC_GROUP(I2C, I2C_ALI, I2C_TACKI, I2C_WAITI, I2C_DTEI),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xa4080080, 0xa40800c0, 8, /* IMR0 / IMCR0 */
	  अणु पूर्ण पूर्ण,
	अणु 0xa4080084, 0xa40800c4, 8, /* IMR1 / IMCR1 */
	  अणु VOU, VIO_VEUI, VIO_BEUI, VIO_CEUI, DMAC3, DMAC2, DMAC1, DMAC0 पूर्ण पूर्ण,
	अणु 0xa4080088, 0xa40800c8, 8, /* IMR2 / IMCR2 */
	  अणु 0, 0, 0, VPU, पूर्ण पूर्ण,
	अणु 0xa408008c, 0xa40800cc, 8, /* IMR3 / IMCR3 */
	  अणु SIM_TEI, SIM_TXI, SIM_RXI, SIM_ERI, 0, 0, 0, IRDA पूर्ण पूर्ण,
	अणु 0xa4080090, 0xa40800d0, 8, /* IMR4 / IMCR4 */
	  अणु 0, TMU2, TMU1, TMU0, JPU, 0, 0, LCDC पूर्ण पूर्ण,
	अणु 0xa4080094, 0xa40800d4, 8, /* IMR5 / IMCR5 */
	  अणु KEYSC, DMAC_DADERR, DMAC5, DMAC4, 0, SCIF2, SCIF1, SCIF0 पूर्ण पूर्ण,
	अणु 0xa4080098, 0xa40800d8, 8, /* IMR6 / IMCR6 */
	  अणु 0, 0, 0, SIO, 0, 0, SIOF1, SIOF0 पूर्ण पूर्ण,
	अणु 0xa408009c, 0xa40800dc, 8, /* IMR7 / IMCR7 */
	  अणु I2C_DTEI, I2C_WAITI, I2C_TACKI, I2C_ALI,
	    FLCTL_FLTREQ1I, FLCTL_FLTREQ0I, FLCTL_FLENDI, FLCTL_FLSTEI पूर्ण पूर्ण,
	अणु 0xa40800a0, 0xa40800e0, 8, /* IMR8 / IMCR8 */
	  अणु DISABLED, ENABLED, ENABLED, ENABLED, 0, 0, TWODG, SIU पूर्ण पूर्ण,
	अणु 0xa40800a4, 0xa40800e4, 8, /* IMR9 / IMCR9 */
	  अणु 0, 0, 0, CMT, 0, USB_USBI1, USB_USBI0, पूर्ण पूर्ण,
	अणु 0xa40800a8, 0xa40800e8, 8, /* IMR10 / IMCR10 */
	  अणु पूर्ण पूर्ण,
	अणु 0xa40800ac, 0xa40800ec, 8, /* IMR11 / IMCR11 */
	  अणु 0, RTC_CUI, RTC_PRI, RTC_ATI, 0, TPU, 0, TSIF पूर्ण पूर्ण,
	अणु 0xa4140044, 0xa4140064, 8, /* INTMSK00 / INTMSKCLR00 */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xa4080000, 0, 16, 4, /* IPRA */ अणु TMU0, TMU1, TMU2, IRDA पूर्ण पूर्ण,
	अणु 0xa4080004, 0, 16, 4, /* IPRB */ अणु JPU, LCDC, SIM पूर्ण पूर्ण,
	अणु 0xa4080008, 0, 16, 4, /* IPRC */ अणु पूर्ण पूर्ण,
	अणु 0xa408000c, 0, 16, 4, /* IPRD */ अणु पूर्ण पूर्ण,
	अणु 0xa4080010, 0, 16, 4, /* IPRE */ अणु DMAC0123, VIOVOU, 0, VPU पूर्ण पूर्ण,
	अणु 0xa4080014, 0, 16, 4, /* IPRF */ अणु KEYSC, DMAC45, USB, CMT पूर्ण पूर्ण,
	अणु 0xa4080018, 0, 16, 4, /* IPRG */ अणु SCIF0, SCIF1, SCIF2 पूर्ण पूर्ण,
	अणु 0xa408001c, 0, 16, 4, /* IPRH */ अणु SIOF0, SIOF1, FLCTL, I2C पूर्ण पूर्ण,
	अणु 0xa4080020, 0, 16, 4, /* IPRI */ अणु SIO, 0, TSIF, RTC पूर्ण पूर्ण,
	अणु 0xa4080024, 0, 16, 4, /* IPRJ */ अणु 0, 0, SIU पूर्ण पूर्ण,
	अणु 0xa4080028, 0, 16, 4, /* IPRK */ अणु 0, 0, 0, SDHI पूर्ण पूर्ण,
	अणु 0xa408002c, 0, 16, 4, /* IPRL */ अणु TWODG, 0, TPU पूर्ण पूर्ण,
	अणु 0xa4140010, 0, 32, 4, /* INTPRI00 */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_sense_reg sense_रेजिस्टरs[] __initdata = अणु
	अणु 0xa414001c, 16, 2, /* ICR1 */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg ack_रेजिस्टरs[] __initdata = अणु
	अणु 0xa4140024, 0, 8, /* INTREQ00 */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_desc पूर्णांकc_desc __initdata = अणु
	.name = "sh7722",
	.क्रमce_enable = ENABLED,
	.क्रमce_disable = DISABLED,
	.hw = INTC_HW_DESC(vectors, groups, mask_रेजिस्टरs,
			   prio_रेजिस्टरs, sense_रेजिस्टरs, ack_रेजिस्टरs),
पूर्ण;

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	/* Register the URAM space as Node 1 */
	setup_booपंचांगem_node(1, 0x055f0000, 0x05610000);
पूर्ण
