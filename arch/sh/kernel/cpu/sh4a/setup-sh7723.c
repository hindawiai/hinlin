<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7723 Setup
 *
 *  Copyright (C) 2008  Paul Mundt
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/mm.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/usb/r8a66597.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/platक्रमm_early.h>
#समावेश <cpu/sh7723.h>

/* Serial */
अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type           = PORT_SCIF,
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

अटल काष्ठा plat_sci_port scअगर3_platक्रमm_data = अणु
	.sampling_rate	= 8,
	.type           = PORT_SCIFA,
पूर्ण;

अटल काष्ठा resource scअगर3_resources[] = अणु
	DEFINE_RES_MEM(0xa4e30000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0x900)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर3_device = अणु
	.name		= "sh-sci",
	.id		= 3,
	.resource	= scअगर3_resources,
	.num_resources	= ARRAY_SIZE(scअगर3_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर3_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर4_platक्रमm_data = अणु
	.sampling_rate	= 8,
	.type           = PORT_SCIFA,
पूर्ण;

अटल काष्ठा resource scअगर4_resources[] = अणु
	DEFINE_RES_MEM(0xa4e40000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xd00)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर4_device = अणु
	.name		= "sh-sci",
	.id		= 4,
	.resource	= scअगर4_resources,
	.num_resources	= ARRAY_SIZE(scअगर4_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर4_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_sci_port scअगर5_platक्रमm_data = अणु
	.sampling_rate	= 8,
	.type           = PORT_SCIFA,
पूर्ण;

अटल काष्ठा resource scअगर5_resources[] = अणु
	DEFINE_RES_MEM(0xa4e50000, 0x100),
	DEFINE_RES_IRQ(evt2irq(0xfa0)),
पूर्ण;

अटल काष्ठा platक्रमm_device scअगर5_device = अणु
	.name		= "sh-sci",
	.id		= 5,
	.resource	= scअगर5_resources,
	.num_resources	= ARRAY_SIZE(scअगर5_resources),
	.dev		= अणु
		.platक्रमm_data	= &scअगर5_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा uio_info vpu_platक्रमm_data = अणु
	.name = "VPU5",
	.version = "0",
	.irq = evt2irq(0x980),
पूर्ण;

अटल काष्ठा resource vpu_resources[] = अणु
	[0] = अणु
		.name	= "VPU",
		.start	= 0xfe900000,
		.end	= 0xfe902807,
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

अटल काष्ठा uio_info veu0_platक्रमm_data = अणु
	.name = "VEU2H",
	.version = "0",
	.irq = evt2irq(0x8c0),
पूर्ण;

अटल काष्ठा resource veu0_resources[] = अणु
	[0] = अणु
		.name	= "VEU2H0",
		.start	= 0xfe920000,
		.end	= 0xfe92027b,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* place holder क्रम contiguous memory */
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device veu0_device = अणु
	.name		= "uio_pdrv_genirq",
	.id		= 1,
	.dev = अणु
		.platक्रमm_data	= &veu0_platक्रमm_data,
	पूर्ण,
	.resource	= veu0_resources,
	.num_resources	= ARRAY_SIZE(veu0_resources),
पूर्ण;

अटल काष्ठा uio_info veu1_platक्रमm_data = अणु
	.name = "VEU2H",
	.version = "0",
	.irq = evt2irq(0x560),
पूर्ण;

अटल काष्ठा resource veu1_resources[] = अणु
	[0] = अणु
		.name	= "VEU2H1",
		.start	= 0xfe924000,
		.end	= 0xfe92427b,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* place holder क्रम contiguous memory */
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device veu1_device = अणु
	.name		= "uio_pdrv_genirq",
	.id		= 2,
	.dev = अणु
		.platक्रमm_data	= &veu1_platक्रमm_data,
	पूर्ण,
	.resource	= veu1_resources,
	.num_resources	= ARRAY_SIZE(veu1_resources),
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

अटल काष्ठा sh_समयr_config पंचांगu1_platक्रमm_data = अणु
	.channels_mask = 7,
पूर्ण;

अटल काष्ठा resource पंचांगu1_resources[] = अणु
	DEFINE_RES_MEM(0xffd90000, 0x2c),
	DEFINE_RES_IRQ(evt2irq(0x920)),
	DEFINE_RES_IRQ(evt2irq(0x940)),
	DEFINE_RES_IRQ(evt2irq(0x960)),
पूर्ण;

अटल काष्ठा platक्रमm_device पंचांगu1_device = अणु
	.name		= "sh-tmu",
	.id		= 1,
	.dev = अणु
		.platक्रमm_data	= &पंचांगu1_platक्रमm_data,
	पूर्ण,
	.resource	= पंचांगu1_resources,
	.num_resources	= ARRAY_SIZE(पंचांगu1_resources),
पूर्ण;

अटल काष्ठा resource rtc_resources[] = अणु
	[0] = अणु
		.start	= 0xa465fec0,
		.end	= 0xa465fec0 + 0x58 - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		/* Period IRQ */
		.start	= evt2irq(0xaa0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		/* Carry IRQ */
		.start	= evt2irq(0xac0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[3] = अणु
		/* Alarm IRQ */
		.start	= evt2irq(0xa80),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "sh-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtc_resources),
	.resource	= rtc_resources,
पूर्ण;

अटल काष्ठा r8a66597_platdata r8a66597_data = अणु
	.on_chip = 1,
पूर्ण;

अटल काष्ठा resource sh7723_usb_host_resources[] = अणु
	[0] = अणु
		.start	= 0xa4d80000,
		.end	= 0xa4d800ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xa20),
		.end	= evt2irq(0xa20),
		.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_LOW,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sh7723_usb_host_device = अणु
	.name		= "r8a66597_hcd",
	.id		= 0,
	.dev = अणु
		.dma_mask		= शून्य,         /*  not use dma */
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &r8a66597_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sh7723_usb_host_resources),
	.resource	= sh7723_usb_host_resources,
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

अटल काष्ठा platक्रमm_device *sh7723_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&scअगर5_device,
	&cmt_device,
	&पंचांगu0_device,
	&पंचांगu1_device,
	&rtc_device,
	&iic_device,
	&sh7723_usb_host_device,
	&vpu_device,
	&veu0_device,
	&veu1_device,
पूर्ण;

अटल पूर्णांक __init sh7723_devices_setup(व्योम)
अणु
	platक्रमm_resource_setup_memory(&vpu_device, "vpu", 2 << 20);
	platक्रमm_resource_setup_memory(&veu0_device, "veu0", 2 << 20);
	platक्रमm_resource_setup_memory(&veu1_device, "veu1", 2 << 20);

	वापस platक्रमm_add_devices(sh7723_devices,
				    ARRAY_SIZE(sh7723_devices));
पूर्ण
arch_initcall(sh7723_devices_setup);

अटल काष्ठा platक्रमm_device *sh7723_early_devices[] __initdata = अणु
	&scअगर0_device,
	&scअगर1_device,
	&scअगर2_device,
	&scअगर3_device,
	&scअगर4_device,
	&scअगर5_device,
	&cmt_device,
	&पंचांगu0_device,
	&पंचांगu1_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7723_early_devices,
				   ARRAY_SIZE(sh7723_early_devices));
पूर्ण

#घोषणा RAMCR_CACHE_L2FC	0x0002
#घोषणा RAMCR_CACHE_L2E		0x0001
#घोषणा L2_CACHE_ENABLE		(RAMCR_CACHE_L2E|RAMCR_CACHE_L2FC)

व्योम l2_cache_init(व्योम)
अणु
	/* Enable L2 cache */
	__raw_ग_लिखोl(L2_CACHE_ENABLE, RAMCR);
पूर्ण

क्रमागत अणु
	UNUSED=0,
	ENABLED,
	DISABLED,

	/* पूर्णांकerrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7,
	HUDI,
	DMAC1A_DEI0,DMAC1A_DEI1,DMAC1A_DEI2,DMAC1A_DEI3,
	_2DG_TRI,_2DG_INI,_2DG_CEI,
	DMAC0A_DEI0,DMAC0A_DEI1,DMAC0A_DEI2,DMAC0A_DEI3,
	VIO_CEUI,VIO_BEUI,VIO_VEU2HI,VIO_VOUI,
	SCIFA_SCIFA0,
	VPU_VPUI,
	TPU_TPUI,
	ADC_ADI,
	USB_USI0,
	RTC_ATI,RTC_PRI,RTC_CUI,
	DMAC1B_DEI4,DMAC1B_DEI5,DMAC1B_DADERR,
	DMAC0B_DEI4,DMAC0B_DEI5,DMAC0B_DADERR,
	KEYSC_KEYI,
	SCIF_SCIF0,SCIF_SCIF1,SCIF_SCIF2,
	MSIOF_MSIOFI0,MSIOF_MSIOFI1,
	SCIFA_SCIFA1,
	FLCTL_FLSTEI,FLCTL_FLTENDI,FLCTL_FLTREQ0I,FLCTL_FLTREQ1I,
	I2C_ALI,I2C_TACKI,I2C_WAITI,I2C_DTEI,
	CMT_CMTI,
	TSIF_TSIFI,
	SIU_SIUI,
	SCIFA_SCIFA2,
	TMU0_TUNI0, TMU0_TUNI1, TMU0_TUNI2,
	IRDA_IRDAI,
	ATAPI_ATAPII,
	VEU2H1_VEU2HI,
	LCDC_LCDCI,
	TMU1_TUNI0,TMU1_TUNI1,TMU1_TUNI2,

	/* पूर्णांकerrupt groups */
	DMAC1A, DMAC0A, VIO, DMAC0B, FLCTL, I2C, _2DG,
	SDHI1, RTC, DMAC1B, SDHI0,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(IRQ0, 0x600), INTC_VECT(IRQ1, 0x620),
	INTC_VECT(IRQ2, 0x640), INTC_VECT(IRQ3, 0x660),
	INTC_VECT(IRQ4, 0x680), INTC_VECT(IRQ5, 0x6a0),
	INTC_VECT(IRQ6, 0x6c0), INTC_VECT(IRQ7, 0x6e0),

	INTC_VECT(DMAC1A_DEI0,0x700),
	INTC_VECT(DMAC1A_DEI1,0x720),
	INTC_VECT(DMAC1A_DEI2,0x740),
	INTC_VECT(DMAC1A_DEI3,0x760),

	INTC_VECT(_2DG_TRI, 0x780),
	INTC_VECT(_2DG_INI, 0x7A0),
	INTC_VECT(_2DG_CEI, 0x7C0),

	INTC_VECT(DMAC0A_DEI0,0x800),
	INTC_VECT(DMAC0A_DEI1,0x820),
	INTC_VECT(DMAC0A_DEI2,0x840),
	INTC_VECT(DMAC0A_DEI3,0x860),

	INTC_VECT(VIO_CEUI,0x880),
	INTC_VECT(VIO_BEUI,0x8A0),
	INTC_VECT(VIO_VEU2HI,0x8C0),
	INTC_VECT(VIO_VOUI,0x8E0),

	INTC_VECT(SCIFA_SCIFA0,0x900),
	INTC_VECT(VPU_VPUI,0x980),
	INTC_VECT(TPU_TPUI,0x9A0),
	INTC_VECT(ADC_ADI,0x9E0),
	INTC_VECT(USB_USI0,0xA20),

	INTC_VECT(RTC_ATI,0xA80),
	INTC_VECT(RTC_PRI,0xAA0),
	INTC_VECT(RTC_CUI,0xAC0),

	INTC_VECT(DMAC1B_DEI4,0xB00),
	INTC_VECT(DMAC1B_DEI5,0xB20),
	INTC_VECT(DMAC1B_DADERR,0xB40),

	INTC_VECT(DMAC0B_DEI4,0xB80),
	INTC_VECT(DMAC0B_DEI5,0xBA0),
	INTC_VECT(DMAC0B_DADERR,0xBC0),

	INTC_VECT(KEYSC_KEYI,0xBE0),
	INTC_VECT(SCIF_SCIF0,0xC00),
	INTC_VECT(SCIF_SCIF1,0xC20),
	INTC_VECT(SCIF_SCIF2,0xC40),
	INTC_VECT(MSIOF_MSIOFI0,0xC80),
	INTC_VECT(MSIOF_MSIOFI1,0xCA0),
	INTC_VECT(SCIFA_SCIFA1,0xD00),

	INTC_VECT(FLCTL_FLSTEI,0xD80),
	INTC_VECT(FLCTL_FLTENDI,0xDA0),
	INTC_VECT(FLCTL_FLTREQ0I,0xDC0),
	INTC_VECT(FLCTL_FLTREQ1I,0xDE0),

	INTC_VECT(I2C_ALI,0xE00),
	INTC_VECT(I2C_TACKI,0xE20),
	INTC_VECT(I2C_WAITI,0xE40),
	INTC_VECT(I2C_DTEI,0xE60),

	INTC_VECT(SDHI0, 0xE80),
	INTC_VECT(SDHI0, 0xEA0),
	INTC_VECT(SDHI0, 0xEC0),

	INTC_VECT(CMT_CMTI,0xF00),
	INTC_VECT(TSIF_TSIFI,0xF20),
	INTC_VECT(SIU_SIUI,0xF80),
	INTC_VECT(SCIFA_SCIFA2,0xFA0),

	INTC_VECT(TMU0_TUNI0,0x400),
	INTC_VECT(TMU0_TUNI1,0x420),
	INTC_VECT(TMU0_TUNI2,0x440),

	INTC_VECT(IRDA_IRDAI,0x480),
	INTC_VECT(ATAPI_ATAPII,0x4A0),

	INTC_VECT(SDHI1, 0x4E0),
	INTC_VECT(SDHI1, 0x500),
	INTC_VECT(SDHI1, 0x520),

	INTC_VECT(VEU2H1_VEU2HI,0x560),
	INTC_VECT(LCDC_LCDCI,0x580),

	INTC_VECT(TMU1_TUNI0,0x920),
	INTC_VECT(TMU1_TUNI1,0x940),
	INTC_VECT(TMU1_TUNI2,0x960),

पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(DMAC1A,DMAC1A_DEI0,DMAC1A_DEI1,DMAC1A_DEI2,DMAC1A_DEI3),
	INTC_GROUP(DMAC0A,DMAC0A_DEI0,DMAC0A_DEI1,DMAC0A_DEI2,DMAC0A_DEI3),
	INTC_GROUP(VIO, VIO_CEUI,VIO_BEUI,VIO_VEU2HI,VIO_VOUI),
	INTC_GROUP(DMAC0B, DMAC0B_DEI4,DMAC0B_DEI5,DMAC0B_DADERR),
	INTC_GROUP(FLCTL,FLCTL_FLSTEI,FLCTL_FLTENDI,FLCTL_FLTREQ0I,FLCTL_FLTREQ1I),
	INTC_GROUP(I2C,I2C_ALI,I2C_TACKI,I2C_WAITI,I2C_DTEI),
	INTC_GROUP(_2DG, _2DG_TRI,_2DG_INI,_2DG_CEI),
	INTC_GROUP(RTC, RTC_ATI,RTC_PRI,RTC_CUI),
	INTC_GROUP(DMAC1B, DMAC1B_DEI4,DMAC1B_DEI5,DMAC1B_DADERR),
पूर्ण;

अटल काष्ठा पूर्णांकc_mask_reg mask_रेजिस्टरs[] __initdata = अणु
	अणु 0xa4080080, 0xa40800c0, 8, /* IMR0 / IMCR0 */
	  अणु 0, TMU1_TUNI2, TMU1_TUNI1, TMU1_TUNI0,
	    0, ENABLED, ENABLED, ENABLED पूर्ण पूर्ण,
	अणु 0xa4080084, 0xa40800c4, 8, /* IMR1 / IMCR1 */
	  अणु VIO_VOUI, VIO_VEU2HI,VIO_BEUI,VIO_CEUI,DMAC0A_DEI3,DMAC0A_DEI2,DMAC0A_DEI1,DMAC0A_DEI0 पूर्ण पूर्ण,
	अणु 0xa4080088, 0xa40800c8, 8, /* IMR2 / IMCR2 */
	  अणु 0, 0, 0, VPU_VPUI,0,0,0,SCIFA_SCIFA0 पूर्ण पूर्ण,
	अणु 0xa408008c, 0xa40800cc, 8, /* IMR3 / IMCR3 */
	  अणु DMAC1A_DEI3,DMAC1A_DEI2,DMAC1A_DEI1,DMAC1A_DEI0,0,0,0,IRDA_IRDAI पूर्ण पूर्ण,
	अणु 0xa4080090, 0xa40800d0, 8, /* IMR4 / IMCR4 */
	  अणु 0,TMU0_TUNI2,TMU0_TUNI1,TMU0_TUNI0,VEU2H1_VEU2HI,0,0,LCDC_LCDCI पूर्ण पूर्ण,
	अणु 0xa4080094, 0xa40800d4, 8, /* IMR5 / IMCR5 */
	  अणु KEYSC_KEYI,DMAC0B_DADERR,DMAC0B_DEI5,DMAC0B_DEI4,0,SCIF_SCIF2,SCIF_SCIF1,SCIF_SCIF0 पूर्ण पूर्ण,
	अणु 0xa4080098, 0xa40800d8, 8, /* IMR6 / IMCR6 */
	  अणु 0,0,0,SCIFA_SCIFA1,ADC_ADI,0,MSIOF_MSIOFI1,MSIOF_MSIOFI0 पूर्ण पूर्ण,
	अणु 0xa408009c, 0xa40800dc, 8, /* IMR7 / IMCR7 */
	  अणु I2C_DTEI, I2C_WAITI, I2C_TACKI, I2C_ALI,
	    FLCTL_FLTREQ1I, FLCTL_FLTREQ0I, FLCTL_FLTENDI, FLCTL_FLSTEI पूर्ण पूर्ण,
	अणु 0xa40800a0, 0xa40800e0, 8, /* IMR8 / IMCR8 */
	  अणु 0, ENABLED, ENABLED, ENABLED,
	    0, 0, SCIFA_SCIFA2, SIU_SIUI पूर्ण पूर्ण,
	अणु 0xa40800a4, 0xa40800e4, 8, /* IMR9 / IMCR9 */
	  अणु 0, 0, 0, CMT_CMTI, 0, 0, USB_USI0,0 पूर्ण पूर्ण,
	अणु 0xa40800a8, 0xa40800e8, 8, /* IMR10 / IMCR10 */
	  अणु 0, DMAC1B_DADERR,DMAC1B_DEI5,DMAC1B_DEI4,0,RTC_ATI,RTC_PRI,RTC_CUI पूर्ण पूर्ण,
	अणु 0xa40800ac, 0xa40800ec, 8, /* IMR11 / IMCR11 */
	  अणु 0,_2DG_CEI,_2DG_INI,_2DG_TRI,0,TPU_TPUI,0,TSIF_TSIFI पूर्ण पूर्ण,
	अणु 0xa40800b0, 0xa40800f0, 8, /* IMR12 / IMCR12 */
	  अणु 0,0,0,0,0,0,0,ATAPI_ATAPII पूर्ण पूर्ण,
	अणु 0xa4140044, 0xa4140064, 8, /* INTMSK00 / INTMSKCLR00 */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xa4080000, 0, 16, 4, /* IPRA */ अणु TMU0_TUNI0, TMU0_TUNI1, TMU0_TUNI2, IRDA_IRDAI पूर्ण पूर्ण,
	अणु 0xa4080004, 0, 16, 4, /* IPRB */ अणु VEU2H1_VEU2HI, LCDC_LCDCI, DMAC1A, 0पूर्ण पूर्ण,
	अणु 0xa4080008, 0, 16, 4, /* IPRC */ अणु TMU1_TUNI0, TMU1_TUNI1, TMU1_TUNI2, 0पूर्ण पूर्ण,
	अणु 0xa408000c, 0, 16, 4, /* IPRD */ अणु पूर्ण पूर्ण,
	अणु 0xa4080010, 0, 16, 4, /* IPRE */ अणु DMAC0A, VIO, SCIFA_SCIFA0, VPU_VPUI पूर्ण पूर्ण,
	अणु 0xa4080014, 0, 16, 4, /* IPRF */ अणु KEYSC_KEYI, DMAC0B, USB_USI0, CMT_CMTI पूर्ण पूर्ण,
	अणु 0xa4080018, 0, 16, 4, /* IPRG */ अणु SCIF_SCIF0, SCIF_SCIF1, SCIF_SCIF2,0 पूर्ण पूर्ण,
	अणु 0xa408001c, 0, 16, 4, /* IPRH */ अणु MSIOF_MSIOFI0,MSIOF_MSIOFI1, FLCTL, I2C पूर्ण पूर्ण,
	अणु 0xa4080020, 0, 16, 4, /* IPRI */ अणु SCIFA_SCIFA1,0,TSIF_TSIFI,_2DG पूर्ण पूर्ण,
	अणु 0xa4080024, 0, 16, 4, /* IPRJ */ अणु ADC_ADI,0,SIU_SIUI,SDHI1 पूर्ण पूर्ण,
	अणु 0xa4080028, 0, 16, 4, /* IPRK */ अणु RTC,DMAC1B,0,SDHI0 पूर्ण पूर्ण,
	अणु 0xa408002c, 0, 16, 4, /* IPRL */ अणु SCIFA_SCIFA2,0,TPU_TPUI,ATAPI_ATAPII पूर्ण पूर्ण,
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
	.name = "sh7723",
	.क्रमce_enable = ENABLED,
	.क्रमce_disable = DISABLED,
	.hw = INTC_HW_DESC(vectors, groups, mask_रेजिस्टरs,
			   prio_रेजिस्टरs, sense_रेजिस्टरs, ack_रेजिस्टरs),
पूर्ण;

व्योम __init plat_irq_setup(व्योम)
अणु
	रेजिस्टर_पूर्णांकc_controller(&पूर्णांकc_desc);
पूर्ण
