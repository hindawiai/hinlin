<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/renesas/r7780rp/setup.c
 *
 * Renesas Solutions Highlander Support.
 *
 * Copyright (C) 2002 Atom Create Engineering Co., Ltd.
 * Copyright (C) 2005 - 2008 Paul Mundt
 *
 * This contains support क्रम the R7780RP-1, R7780MP, and R7785RP
 * Highlander modules.
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/types.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb/r8a66597.h>
#समावेश <linux/usb/m66592.h>
#समावेश <linux/clkdev.h>
#समावेश <net/ax88796.h>
#समावेश <यंत्र/machvec.h>
#समावेश <mach/highlander.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/heartbeat.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/io_trapped.h>

अटल काष्ठा r8a66597_platdata r8a66597_data = अणु
	.xtal = R8A66597_PLATDATA_XTAL_12MHZ,
	.vअगर = 1,
पूर्ण;

अटल काष्ठा resource r8a66597_usb_host_resources[] = अणु
	[0] = अणु
		.start	= 0xA4200000,
		.end	= 0xA42000FF,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_EXT1,		/* irq number */
		.end	= IRQ_EXT1,
		.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_LOW,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device r8a66597_usb_host_device = अणु
	.name		= "r8a66597_hcd",
	.id		= -1,
	.dev = अणु
		.dma_mask		= शून्य,		/* करोn't use dma */
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &r8a66597_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(r8a66597_usb_host_resources),
	.resource	= r8a66597_usb_host_resources,
पूर्ण;

अटल काष्ठा m66592_platdata usbf_platdata = अणु
	.xtal = M66592_PLATDATA_XTAL_24MHZ,
	.vअगर = 1,
पूर्ण;

अटल काष्ठा resource m66592_usb_peripheral_resources[] = अणु
	[0] = अणु
		.name	= "m66592_udc",
		.start	= 0xb0000000,
		.end	= 0xb00000FF,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.name	= "m66592_udc",
		.start	= IRQ_EXT4,		/* irq number */
		.end	= IRQ_EXT4,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device m66592_usb_peripheral_device = अणु
	.name		= "m66592_udc",
	.id		= -1,
	.dev = अणु
		.dma_mask		= शून्य,		/* करोn't use dma */
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &usbf_platdata,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(m66592_usb_peripheral_resources),
	.resource	= m66592_usb_peripheral_resources,
पूर्ण;

अटल काष्ठा resource cf_ide_resources[] = अणु
	[0] = अणु
		.start	= PA_AREA5_IO + 0x1000,
		.end	= PA_AREA5_IO + 0x1000 + 0x08 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PA_AREA5_IO + 0x80c,
		.end	= PA_AREA5_IO + 0x80c + 0x16 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start	= IRQ_CF,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा pata_platक्रमm_info pata_info = अणु
	.ioport_shअगरt	= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device cf_ide_device  = अणु
	.name		= "pata_platform",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(cf_ide_resources),
	.resource	= cf_ide_resources,
	.dev	= अणु
		.platक्रमm_data	= &pata_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource heartbeat_resources[] = अणु
	[0] = अणु
		.start	= PA_OBLED,
		.end	= PA_OBLED,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

#अगर_अघोषित CONFIG_SH_R7785RP
अटल अचिन्हित अक्षर heartbeat_bit_pos[] = अणु 2, 1, 0, 3, 6, 5, 4, 7 पूर्ण;

अटल काष्ठा heartbeat_data heartbeat_data = अणु
	.bit_pos	= heartbeat_bit_pos,
	.nr_bits	= ARRAY_SIZE(heartbeat_bit_pos),
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name		= "heartbeat",
	.id		= -1,

	/* R7785RP has a slightly more sensible FPGA.. */
#अगर_अघोषित CONFIG_SH_R7785RP
	.dev	= अणु
		.platक्रमm_data	= &heartbeat_data,
	पूर्ण,
#पूर्ण_अगर
	.num_resources	= ARRAY_SIZE(heartbeat_resources),
	.resource	= heartbeat_resources,
पूर्ण;

अटल काष्ठा ax_plat_data ax88796_platdata = अणु
	.flags          = AXFLG_HAS_93CX6,
	.wordlength     = 2,
	.dcr_val        = 0x1,
	.rcr_val        = 0x40,
पूर्ण;

अटल काष्ठा resource ax88796_resources[] = अणु
	अणु
#अगर_घोषित CONFIG_SH_R7780RP
		.start  = 0xa5800400,
		.end    = 0xa5800400 + (0x20 * 0x2) - 1,
#अन्यथा
		.start  = 0xa4100400,
		.end    = 0xa4100400 + (0x20 * 0x2) - 1,
#पूर्ण_अगर
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start  = IRQ_AX88796,
		.end    = IRQ_AX88796,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ax88796_device = अणु
	.name           = "ax88796",
	.id             = 0,

	.dev    = अणु
		.platक्रमm_data = &ax88796_platdata,
	पूर्ण,

	.num_resources  = ARRAY_SIZE(ax88796_resources),
	.resource       = ax88796_resources,
पूर्ण;

अटल काष्ठा mtd_partition nor_flash_partitions[] = अणु
	अणु
		.name		= "loader",
		.offset		= 0x00000000,
		.size		= 512 * 1024,
	पूर्ण,
	अणु
		.name		= "bootenv",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 512 * 1024,
	पूर्ण,
	अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 4 * 1024 * 1024,
	पूर्ण,
	अणु
		.name		= "data",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data nor_flash_data = अणु
	.width		= 4,
	.parts		= nor_flash_partitions,
	.nr_parts	= ARRAY_SIZE(nor_flash_partitions),
पूर्ण;

/* This config is flash board क्रम mass production. */
अटल काष्ठा resource nor_flash_resources[] = अणु
	[0]	= अणु
		.start	= PA_NORFLASH_ADDR,
		.end	= PA_NORFLASH_ADDR + PA_NORFLASH_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device nor_flash_device = अणु
	.name		= "physmap-flash",
	.dev		= अणु
		.platक्रमm_data	= &nor_flash_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(nor_flash_resources),
	.resource	= nor_flash_resources,
पूर्ण;

अटल काष्ठा resource smbus_resources[] = अणु
	[0] = अणु
		.start	= PA_SMCR,
		.end	= PA_SMCR + 0x100 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= IRQ_SMBUS,
		.end	= IRQ_SMBUS,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smbus_device = अणु
	.name		= "i2c-highlander",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smbus_resources),
	.resource	= smbus_resources,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata highlander_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("r2025sd", 0x32),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *r7780rp_devices[] __initdata = अणु
	&r8a66597_usb_host_device,
	&m66592_usb_peripheral_device,
	&heartbeat_device,
	&smbus_device,
	&nor_flash_device,
#अगर_अघोषित CONFIG_SH_R7780RP
	&ax88796_device,
#पूर्ण_अगर
पूर्ण;

/*
 * The CF is connected using a 16-bit bus where 8-bit operations are
 * unsupported. The linux ata driver is however using 8-bit operations, so
 * insert a trapped io filter to convert 8-bit operations पूर्णांकo 16-bit.
 */
अटल काष्ठा trapped_io cf_trapped_io = अणु
	.resource		= cf_ide_resources,
	.num_resources		= 2,
	.minimum_bus_width	= 16,
पूर्ण;

अटल पूर्णांक __init r7780rp_devices_setup(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर_अघोषित CONFIG_SH_R7780RP
	अगर (रेजिस्टर_trapped_io(&cf_trapped_io) == 0)
		ret |= platक्रमm_device_रेजिस्टर(&cf_ide_device);
#पूर्ण_अगर

	ret |= platक्रमm_add_devices(r7780rp_devices,
				    ARRAY_SIZE(r7780rp_devices));

	ret |= i2c_रेजिस्टर_board_info(0, highlander_i2c_devices,
				       ARRAY_SIZE(highlander_i2c_devices));

	वापस ret;
पूर्ण
device_initcall(r7780rp_devices_setup);

/*
 * Platक्रमm specअगरic घड़ीs
 */
अटल पूर्णांक ivdr_clk_enable(काष्ठा clk *clk)
अणु
	__raw_ग_लिखोw(__raw_पढ़ोw(PA_IVDRCTL) | (1 << IVDR_CK_ON), PA_IVDRCTL);
	वापस 0;
पूर्ण

अटल व्योम ivdr_clk_disable(काष्ठा clk *clk)
अणु
	__raw_ग_लिखोw(__raw_पढ़ोw(PA_IVDRCTL) & ~(1 << IVDR_CK_ON), PA_IVDRCTL);
पूर्ण

अटल काष्ठा sh_clk_ops ivdr_clk_ops = अणु
	.enable		= ivdr_clk_enable,
	.disable	= ivdr_clk_disable,
पूर्ण;

अटल काष्ठा clk ivdr_clk = अणु
	.ops		= &ivdr_clk_ops,
पूर्ण;

अटल काष्ठा clk *r7780rp_घड़ीs[] = अणु
	&ivdr_clk,
पूर्ण;

अटल काष्ठा clk_lookup lookups[] = अणु
	/* मुख्य घड़ीs */
	CLKDEV_CON_ID("ivdr_clk", &ivdr_clk),
पूर्ण;

अटल व्योम r7780rp_घातer_off(व्योम)
अणु
	अगर (mach_is_r7780mp() || mach_is_r7785rp())
		__raw_ग_लिखोw(0x0001, PA_POFF);
पूर्ण

/*
 * Initialize the board
 */
अटल व्योम __init highlander_setup(अक्षर **cmdline_p)
अणु
	u16 ver = __raw_पढ़ोw(PA_VERREG);
	पूर्णांक i;

	prपूर्णांकk(KERN_INFO "Renesas Solutions Highlander %s support.\n",
			 mach_is_r7780rp() ? "R7780RP-1" :
			 mach_is_r7780mp() ? "R7780MP"	 :
					     "R7785RP");

	prपूर्णांकk(KERN_INFO "Board version: %d (revision %d), "
			 "FPGA version: %d (revision %d)\n",
			 (ver >> 12) & 0xf, (ver >> 8) & 0xf,
			 (ver >>  4) & 0xf, ver & 0xf);

	highlander_plat_pinmux_setup();

	/*
	 * Enable the important घड़ीs right away..
	 */
	क्रम (i = 0; i < ARRAY_SIZE(r7780rp_घड़ीs); i++) अणु
		काष्ठा clk *clk = r7780rp_घड़ीs[i];

		clk_रेजिस्टर(clk);
		clk_enable(clk);
	पूर्ण

	clkdev_add_table(lookups, ARRAY_SIZE(lookups));

	__raw_ग_लिखोw(0x0000, PA_OBLED);	/* Clear LED. */

	अगर (mach_is_r7780rp())
		__raw_ग_लिखोw(0x0001, PA_SDPOW);	/* SD Power ON */

	__raw_ग_लिखोw(__raw_पढ़ोw(PA_IVDRCTL) | 0x01, PA_IVDRCTL);	/* Si13112 */

	pm_घातer_off = r7780rp_घातer_off;
पूर्ण

अटल अचिन्हित अक्षर irl2irq[HL_NR_IRL];

अटल पूर्णांक highlander_irq_demux(पूर्णांक irq)
अणु
	अगर (irq >= HL_NR_IRL || irq < 0 || !irl2irq[irq])
		वापस irq;

	वापस irl2irq[irq];
पूर्ण

अटल व्योम __init highlander_init_irq(व्योम)
अणु
	अचिन्हित अक्षर *ucp = highlander_plat_irq_setup();

	अगर (ucp) अणु
		plat_irq_setup_pins(IRQ_MODE_IRL3210);
		स_नकल(irl2irq, ucp, HL_NR_IRL);
	पूर्ण
पूर्ण

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_highlander __iniपंचांगv = अणु
	.mv_name		= "Highlander",
	.mv_setup		= highlander_setup,
	.mv_init_irq		= highlander_init_irq,
	.mv_irq_demux		= highlander_irq_demux,
पूर्ण;
