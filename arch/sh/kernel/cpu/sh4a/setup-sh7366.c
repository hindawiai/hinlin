<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH7366 Setup
 *
 *  Copyright (C) 2008 Renesas Solutions
 *
 * Based on linux/arch/sh/kernel/cpu/sh4a/setup-sh7722.c
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_sci.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/usb/r8a66597.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/platक्रमm_early.h>

अटल काष्ठा plat_sci_port scअगर0_platक्रमm_data = अणु
	.scscr		= SCSCR_REIE,
	.type		= PORT_SCIF,
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

अटल काष्ठा r8a66597_platdata r8a66597_data = अणु
	.on_chip = 1,
पूर्ण;

अटल काष्ठा resource usb_host_resources[] = अणु
	[0] = अणु
		.start  = 0xa4d80000,
		.end    = 0xa4d800ff,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0xa20),
		.end    = evt2irq(0xa20),
		.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_LOW,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device usb_host_device = अणु
	.name	= "r8a66597_hcd",
	.id	= -1,
	.dev = अणु
		.dma_mask		= शून्य,
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &r8a66597_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(usb_host_resources),
	.resource	= usb_host_resources,
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
	.name = "VEU",
	.version = "0",
	.irq = evt2irq(0x8c0),
पूर्ण;

अटल काष्ठा resource veu0_resources[] = अणु
	[0] = अणु
		.name	= "VEU(1)",
		.start	= 0xfe920000,
		.end	= 0xfe9200b7,
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
	.name = "VEU",
	.version = "0",
	.irq = evt2irq(0x560),
पूर्ण;

अटल काष्ठा resource veu1_resources[] = अणु
	[0] = अणु
		.name	= "VEU(2)",
		.start	= 0xfe924000,
		.end	= 0xfe9240b7,
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

अटल काष्ठा platक्रमm_device *sh7366_devices[] __initdata = अणु
	&scअगर0_device,
	&cmt_device,
	&पंचांगu0_device,
	&iic_device,
	&usb_host_device,
	&vpu_device,
	&veu0_device,
	&veu1_device,
पूर्ण;

अटल पूर्णांक __init sh7366_devices_setup(व्योम)
अणु
	platक्रमm_resource_setup_memory(&vpu_device, "vpu", 2 << 20);
	platक्रमm_resource_setup_memory(&veu0_device, "veu0", 2 << 20);
	platक्रमm_resource_setup_memory(&veu1_device, "veu1", 2 << 20);

	वापस platक्रमm_add_devices(sh7366_devices,
				    ARRAY_SIZE(sh7366_devices));
पूर्ण
arch_initcall(sh7366_devices_setup);

अटल काष्ठा platक्रमm_device *sh7366_early_devices[] __initdata = अणु
	&scअगर0_device,
	&cmt_device,
	&पंचांगu0_device,
पूर्ण;

व्योम __init plat_early_device_setup(व्योम)
अणु
	sh_early_platक्रमm_add_devices(sh7366_early_devices,
				   ARRAY_SIZE(sh7366_early_devices));
पूर्ण

क्रमागत अणु
	UNUSED=0,
	ENABLED,
	DISABLED,

	/* पूर्णांकerrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7,
	ICB,
	DMAC0, DMAC1, DMAC2, DMAC3,
	VIO_CEUI, VIO_BEUI, VIO_VEUI, VOU,
	MFI, VPU, USB,
	MMC_MMC1I, MMC_MMC2I, MMC_MMC3I,
	DMAC4, DMAC5, DMAC_DADERR,
	SCIF, SCIFA1, SCIFA2,
	DENC, MSIOF,
	FLCTL_FLSTEI, FLCTL_FLENDI, FLCTL_FLTREQ0I, FLCTL_FLTREQ1I,
	I2C_ALI, I2C_TACKI, I2C_WAITI, I2C_DTEI,
	SDHI, CMT, TSIF, SIU,
	TMU0, TMU1, TMU2,
	VEU2, LCDC,

	/* पूर्णांकerrupt groups */

	DMAC0123, VIOVOU, MMC, DMAC45, FLCTL, I2C,
पूर्ण;

अटल काष्ठा पूर्णांकc_vect vectors[] __initdata = अणु
	INTC_VECT(IRQ0, 0x600), INTC_VECT(IRQ1, 0x620),
	INTC_VECT(IRQ2, 0x640), INTC_VECT(IRQ3, 0x660),
	INTC_VECT(IRQ4, 0x680), INTC_VECT(IRQ5, 0x6a0),
	INTC_VECT(IRQ6, 0x6c0), INTC_VECT(IRQ7, 0x6e0),
	INTC_VECT(ICB, 0x700),
	INTC_VECT(DMAC0, 0x800), INTC_VECT(DMAC1, 0x820),
	INTC_VECT(DMAC2, 0x840), INTC_VECT(DMAC3, 0x860),
	INTC_VECT(VIO_CEUI, 0x880), INTC_VECT(VIO_BEUI, 0x8a0),
	INTC_VECT(VIO_VEUI, 0x8c0), INTC_VECT(VOU, 0x8e0),
	INTC_VECT(MFI, 0x900), INTC_VECT(VPU, 0x980), INTC_VECT(USB, 0xa20),
	INTC_VECT(MMC_MMC1I, 0xb00), INTC_VECT(MMC_MMC2I, 0xb20),
	INTC_VECT(MMC_MMC3I, 0xb40),
	INTC_VECT(DMAC4, 0xb80), INTC_VECT(DMAC5, 0xba0),
	INTC_VECT(DMAC_DADERR, 0xbc0),
	INTC_VECT(SCIF, 0xc00), INTC_VECT(SCIFA1, 0xc20),
	INTC_VECT(SCIFA2, 0xc40),
	INTC_VECT(DENC, 0xc60), INTC_VECT(MSIOF, 0xc80),
	INTC_VECT(FLCTL_FLSTEI, 0xd80), INTC_VECT(FLCTL_FLENDI, 0xda0),
	INTC_VECT(FLCTL_FLTREQ0I, 0xdc0), INTC_VECT(FLCTL_FLTREQ1I, 0xde0),
	INTC_VECT(I2C_ALI, 0xe00), INTC_VECT(I2C_TACKI, 0xe20),
	INTC_VECT(I2C_WAITI, 0xe40), INTC_VECT(I2C_DTEI, 0xe60),
	INTC_VECT(SDHI, 0xe80), INTC_VECT(SDHI, 0xea0),
	INTC_VECT(SDHI, 0xec0), INTC_VECT(SDHI, 0xee0),
	INTC_VECT(CMT, 0xf00), INTC_VECT(TSIF, 0xf20),
	INTC_VECT(SIU, 0xf80),
	INTC_VECT(TMU0, 0x400), INTC_VECT(TMU1, 0x420),
	INTC_VECT(TMU2, 0x440),
	INTC_VECT(VEU2, 0x560), INTC_VECT(LCDC, 0x580),
पूर्ण;

अटल काष्ठा पूर्णांकc_group groups[] __initdata = अणु
	INTC_GROUP(DMAC0123, DMAC0, DMAC1, DMAC2, DMAC3),
	INTC_GROUP(VIOVOU, VIO_CEUI, VIO_BEUI, VIO_VEUI, VOU),
	INTC_GROUP(MMC, MMC_MMC1I, MMC_MMC2I, MMC_MMC3I),
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
	  अणु 0, 0, 0, VPU, 0, 0, 0, MFI पूर्ण पूर्ण,
	अणु 0xa408008c, 0xa40800cc, 8, /* IMR3 / IMCR3 */
	  अणु 0, 0, 0, ICB पूर्ण पूर्ण,
	अणु 0xa4080090, 0xa40800d0, 8, /* IMR4 / IMCR4 */
	  अणु 0, TMU2, TMU1, TMU0, VEU2, 0, 0, LCDC पूर्ण पूर्ण,
	अणु 0xa4080094, 0xa40800d4, 8, /* IMR5 / IMCR5 */
	  अणु 0, DMAC_DADERR, DMAC5, DMAC4, DENC, SCIFA2, SCIFA1, SCIF पूर्ण पूर्ण,
	अणु 0xa4080098, 0xa40800d8, 8, /* IMR6 / IMCR6 */
	  अणु 0, 0, 0, 0, 0, 0, 0, MSIOF पूर्ण पूर्ण,
	अणु 0xa408009c, 0xa40800dc, 8, /* IMR7 / IMCR7 */
	  अणु I2C_DTEI, I2C_WAITI, I2C_TACKI, I2C_ALI,
	    FLCTL_FLTREQ1I, FLCTL_FLTREQ0I, FLCTL_FLENDI, FLCTL_FLSTEI पूर्ण पूर्ण,
	अणु 0xa40800a0, 0xa40800e0, 8, /* IMR8 / IMCR8 */
	  अणु DISABLED, ENABLED, ENABLED, ENABLED, 0, 0, 0, SIU पूर्ण पूर्ण,
	अणु 0xa40800a4, 0xa40800e4, 8, /* IMR9 / IMCR9 */
	  अणु 0, 0, 0, CMT, 0, USB, पूर्ण पूर्ण,
	अणु 0xa40800a8, 0xa40800e8, 8, /* IMR10 / IMCR10 */
	  अणु 0, MMC_MMC3I, MMC_MMC2I, MMC_MMC1I पूर्ण पूर्ण,
	अणु 0xa40800ac, 0xa40800ec, 8, /* IMR11 / IMCR11 */
	  अणु 0, 0, 0, 0, 0, 0, 0, TSIF पूर्ण पूर्ण,
	अणु 0xa4140044, 0xa4140064, 8, /* INTMSK00 / INTMSKCLR00 */
	  अणु IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7 पूर्ण पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकc_prio_reg prio_रेजिस्टरs[] __initdata = अणु
	अणु 0xa4080000, 0, 16, 4, /* IPRA */ अणु TMU0, TMU1, TMU2 पूर्ण पूर्ण,
	अणु 0xa4080004, 0, 16, 4, /* IPRB */ अणु VEU2, LCDC, ICB पूर्ण पूर्ण,
	अणु 0xa4080008, 0, 16, 4, /* IPRC */ अणु पूर्ण पूर्ण,
	अणु 0xa408000c, 0, 16, 4, /* IPRD */ अणु पूर्ण पूर्ण,
	अणु 0xa4080010, 0, 16, 4, /* IPRE */ अणु DMAC0123, VIOVOU, MFI, VPU पूर्ण पूर्ण,
	अणु 0xa4080014, 0, 16, 4, /* IPRF */ अणु 0, DMAC45, USB, CMT पूर्ण पूर्ण,
	अणु 0xa4080018, 0, 16, 4, /* IPRG */ अणु SCIF, SCIFA1, SCIFA2, DENC पूर्ण पूर्ण,
	अणु 0xa408001c, 0, 16, 4, /* IPRH */ अणु MSIOF, 0, FLCTL, I2C पूर्ण पूर्ण,
	अणु 0xa4080020, 0, 16, 4, /* IPRI */ अणु 0, 0, TSIF, पूर्ण पूर्ण,
	अणु 0xa4080024, 0, 16, 4, /* IPRJ */ अणु 0, 0, SIU पूर्ण पूर्ण,
	अणु 0xa4080028, 0, 16, 4, /* IPRK */ अणु 0, MMC, 0, SDHI पूर्ण पूर्ण,
	अणु 0xa408002c, 0, 16, 4, /* IPRL */ अणु पूर्ण पूर्ण,
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
	.name = "sh7366",
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
	/* TODO: Register Node 1 */
पूर्ण
