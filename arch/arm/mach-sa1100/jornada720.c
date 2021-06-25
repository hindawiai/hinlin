<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-sa1100/jornada720.c
 *
 * HP Jornada720 init code
 *
 * Copyright (C) 2007 Kristoffer Ericson <Kristoffer.Ericson@gmail.com>
 * Copyright (C) 2006 Filip Zyzniewski <filip.zyzniewski@tefnet.pl>
 *  Copyright (C) 2005 Michael Gernoth <michael@gernoth.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <video/s1d13xxxfb.h>

#समावेश <यंत्र/hardware/sa1111.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/hardware.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"

/*
 * HP Documentation referred in this file:
 * http://www.jlime.com/करोwnloads/development/करोcs/jornada7xx/jornada720.txt
 */

/* line 110 of HP's करोc */
#घोषणा TUCR_VAL	0x20000400

/* memory space (line 52 of HP's करोc) */
#घोषणा SA1111REGSTART	0x40000000
#घोषणा SA1111REGLEN	0x00002000
#घोषणा EPSONREGSTART	0x48000000
#घोषणा EPSONREGLEN	0x00100000
#घोषणा EPSONFBSTART	0x48200000
/* 512kB framebuffer */
#घोषणा EPSONFBLEN	512*1024

अटल काष्ठा s1d13xxxfb_regval s1d13xxxfb_initregs[] = अणु
	/* line 344 of HP's करोc */
	अणु0x0001,0x00पूर्ण,	// Miscellaneous Register
	अणु0x01FC,0x00पूर्ण,	// Display Mode Register
	अणु0x0004,0x00पूर्ण,	// General IO Pins Configuration Register 0
	अणु0x0005,0x00पूर्ण,	// General IO Pins Configuration Register 1
	अणु0x0008,0x00पूर्ण,	// General IO Pins Control Register 0
	अणु0x0009,0x00पूर्ण,	// General IO Pins Control Register 1
	अणु0x0010,0x01पूर्ण,	// Memory Clock Configuration Register
	अणु0x0014,0x11पूर्ण,	// LCD Pixel Clock Configuration Register
	अणु0x0018,0x01पूर्ण,	// CRT/TV Pixel Clock Configuration Register
	अणु0x001C,0x01पूर्ण,	// MediaPlug Clock Configuration Register
	अणु0x001E,0x01पूर्ण,	// CPU To Memory Wait State Select Register
	अणु0x0020,0x00पूर्ण,	// Memory Configuration Register
	अणु0x0021,0x45पूर्ण,	// DRAM Refresh Rate Register
	अणु0x002A,0x01पूर्ण,	// DRAM Timings Control Register 0
	अणु0x002B,0x03पूर्ण,	// DRAM Timings Control Register 1
	अणु0x0030,0x1cपूर्ण,	// Panel Type Register
	अणु0x0031,0x00पूर्ण,	// MOD Rate Register
	अणु0x0032,0x4Fपूर्ण,	// LCD Horizontal Display Width Register
	अणु0x0034,0x07पूर्ण,	// LCD Horizontal Non-Display Period Register
	अणु0x0035,0x01पूर्ण,	// TFT FPLINE Start Position Register
	अणु0x0036,0x0Bपूर्ण,	// TFT FPLINE Pulse Width Register
	अणु0x0038,0xEFपूर्ण,	// LCD Vertical Display Height Register 0
	अणु0x0039,0x00पूर्ण,	// LCD Vertical Display Height Register 1
	अणु0x003A,0x13पूर्ण,	// LCD Vertical Non-Display Period Register
	अणु0x003B,0x0Bपूर्ण,	// TFT FPFRAME Start Position Register
	अणु0x003C,0x01पूर्ण,	// TFT FPFRAME Pulse Width Register
	अणु0x0040,0x05पूर्ण,	// LCD Display Mode Register (2:4bpp,3:8bpp,5:16bpp)
	अणु0x0041,0x00पूर्ण,	// LCD Miscellaneous Register
	अणु0x0042,0x00पूर्ण,	// LCD Display Start Address Register 0
	अणु0x0043,0x00पूर्ण,	// LCD Display Start Address Register 1
	अणु0x0044,0x00पूर्ण,	// LCD Display Start Address Register 2
	अणु0x0046,0x80पूर्ण,	// LCD Memory Address Offset Register 0
	अणु0x0047,0x02पूर्ण,	// LCD Memory Address Offset Register 1
	अणु0x0048,0x00पूर्ण,	// LCD Pixel Panning Register
	अणु0x004A,0x00पूर्ण,	// LCD Display FIFO High Threshold Control Register
	अणु0x004B,0x00पूर्ण,	// LCD Display FIFO Low Threshold Control Register
	अणु0x0050,0x4Fपूर्ण,	// CRT/TV Horizontal Display Width Register
	अणु0x0052,0x13पूर्ण,	// CRT/TV Horizontal Non-Display Period Register
	अणु0x0053,0x01पूर्ण,	// CRT/TV HRTC Start Position Register
	अणु0x0054,0x0Bपूर्ण,	// CRT/TV HRTC Pulse Width Register
	अणु0x0056,0xDFपूर्ण,	// CRT/TV Vertical Display Height Register 0
	अणु0x0057,0x01पूर्ण,	// CRT/TV Vertical Display Height Register 1
	अणु0x0058,0x2Bपूर्ण,	// CRT/TV Vertical Non-Display Period Register
	अणु0x0059,0x09पूर्ण,	// CRT/TV VRTC Start Position Register
	अणु0x005A,0x01पूर्ण,	// CRT/TV VRTC Pulse Width Register
	अणु0x005B,0x10पूर्ण,	// TV Output Control Register
	अणु0x0060,0x03पूर्ण,	// CRT/TV Display Mode Register (2:4bpp,3:8bpp,5:16bpp)
	अणु0x0062,0x00पूर्ण,	// CRT/TV Display Start Address Register 0
	अणु0x0063,0x00पूर्ण,	// CRT/TV Display Start Address Register 1
	अणु0x0064,0x00पूर्ण,	// CRT/TV Display Start Address Register 2
	अणु0x0066,0x40पूर्ण,	// CRT/TV Memory Address Offset Register 0
	अणु0x0067,0x01पूर्ण,	// CRT/TV Memory Address Offset Register 1
	अणु0x0068,0x00पूर्ण,	// CRT/TV Pixel Panning Register
	अणु0x006A,0x00पूर्ण,	// CRT/TV Display FIFO High Threshold Control Register
	अणु0x006B,0x00पूर्ण,	// CRT/TV Display FIFO Low Threshold Control Register
	अणु0x0070,0x00पूर्ण,	// LCD Ink/Cursor Control Register
	अणु0x0071,0x01पूर्ण,	// LCD Ink/Cursor Start Address Register
	अणु0x0072,0x00पूर्ण,	// LCD Cursor X Position Register 0
	अणु0x0073,0x00पूर्ण,	// LCD Cursor X Position Register 1
	अणु0x0074,0x00पूर्ण,	// LCD Cursor Y Position Register 0
	अणु0x0075,0x00पूर्ण,	// LCD Cursor Y Position Register 1
	अणु0x0076,0x00पूर्ण,	// LCD Ink/Cursor Blue Color 0 Register
	अणु0x0077,0x00पूर्ण,	// LCD Ink/Cursor Green Color 0 Register
	अणु0x0078,0x00पूर्ण,	// LCD Ink/Cursor Red Color 0 Register
	अणु0x007A,0x1Fपूर्ण,	// LCD Ink/Cursor Blue Color 1 Register
	अणु0x007B,0x3Fपूर्ण,	// LCD Ink/Cursor Green Color 1 Register
	अणु0x007C,0x1Fपूर्ण,	// LCD Ink/Cursor Red Color 1 Register
	अणु0x007E,0x00पूर्ण,	// LCD Ink/Cursor FIFO Threshold Register
	अणु0x0080,0x00पूर्ण,	// CRT/TV Ink/Cursor Control Register
	अणु0x0081,0x01पूर्ण,	// CRT/TV Ink/Cursor Start Address Register
	अणु0x0082,0x00पूर्ण,	// CRT/TV Cursor X Position Register 0
	अणु0x0083,0x00पूर्ण,	// CRT/TV Cursor X Position Register 1
	अणु0x0084,0x00पूर्ण,	// CRT/TV Cursor Y Position Register 0
	अणु0x0085,0x00पूर्ण,	// CRT/TV Cursor Y Position Register 1
	अणु0x0086,0x00पूर्ण,	// CRT/TV Ink/Cursor Blue Color 0 Register
	अणु0x0087,0x00पूर्ण,	// CRT/TV Ink/Cursor Green Color 0 Register
	अणु0x0088,0x00पूर्ण,	// CRT/TV Ink/Cursor Red Color 0 Register
	अणु0x008A,0x1Fपूर्ण,	// CRT/TV Ink/Cursor Blue Color 1 Register
	अणु0x008B,0x3Fपूर्ण,	// CRT/TV Ink/Cursor Green Color 1 Register
	अणु0x008C,0x1Fपूर्ण,	// CRT/TV Ink/Cursor Red Color 1 Register
	अणु0x008E,0x00पूर्ण,	// CRT/TV Ink/Cursor FIFO Threshold Register
	अणु0x0100,0x00पूर्ण,	// BitBlt Control Register 0
	अणु0x0101,0x00पूर्ण,	// BitBlt Control Register 1
	अणु0x0102,0x00पूर्ण,	// BitBlt ROP Code/Color Expansion Register
	अणु0x0103,0x00पूर्ण,	// BitBlt Operation Register
	अणु0x0104,0x00पूर्ण,	// BitBlt Source Start Address Register 0
	अणु0x0105,0x00पूर्ण,	// BitBlt Source Start Address Register 1
	अणु0x0106,0x00पूर्ण,	// BitBlt Source Start Address Register 2
	अणु0x0108,0x00पूर्ण,	// BitBlt Destination Start Address Register 0
	अणु0x0109,0x00पूर्ण,	// BitBlt Destination Start Address Register 1
	अणु0x010A,0x00पूर्ण,	// BitBlt Destination Start Address Register 2
	अणु0x010C,0x00पूर्ण,	// BitBlt Memory Address Offset Register 0
	अणु0x010D,0x00पूर्ण,	// BitBlt Memory Address Offset Register 1
	अणु0x0110,0x00पूर्ण,	// BitBlt Width Register 0
	अणु0x0111,0x00पूर्ण,	// BitBlt Width Register 1
	अणु0x0112,0x00पूर्ण,	// BitBlt Height Register 0
	अणु0x0113,0x00पूर्ण,	// BitBlt Height Register 1
	अणु0x0114,0x00पूर्ण,	// BitBlt Background Color Register 0
	अणु0x0115,0x00पूर्ण,	// BitBlt Background Color Register 1
	अणु0x0118,0x00पूर्ण,	// BitBlt Foreground Color Register 0
	अणु0x0119,0x00पूर्ण,	// BitBlt Foreground Color Register 1
	अणु0x01E0,0x00पूर्ण,	// Look-Up Table Mode Register
	अणु0x01E2,0x00पूर्ण,	// Look-Up Table Address Register
	/* not sure, wouldn't like to mess with the driver */
	अणु0x01E4,0x00पूर्ण,	// Look-Up Table Data Register
	/* jornada करोc says 0x00, but I trust the driver */
	अणु0x01F0,0x10पूर्ण,	// Power Save Configuration Register
	अणु0x01F1,0x00पूर्ण,	// Power Save Status Register
	अणु0x01F4,0x00पूर्ण,	// CPU-to-Memory Access Watchकरोg Timer Register
	अणु0x01FC,0x01पूर्ण,	// Display Mode Register(0x01:LCD, 0x02:CRT, 0x03:LCD&CRT)
पूर्ण;

अटल काष्ठा s1d13xxxfb_pdata s1d13xxxfb_data = अणु
	.initregs		= s1d13xxxfb_initregs,
	.initregssize		= ARRAY_SIZE(s1d13xxxfb_initregs),
	.platक्रमm_init_video	= शून्य
पूर्ण;

अटल काष्ठा resource s1d13xxxfb_resources[] = अणु
	[0] = DEFINE_RES_MEM(EPSONFBSTART, EPSONFBLEN),
	[1] = DEFINE_RES_MEM(EPSONREGSTART, EPSONREGLEN),
पूर्ण;

अटल काष्ठा platक्रमm_device s1d13xxxfb_device = अणु
	.name		= S1D_DEVICENAME,
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &s1d13xxxfb_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(s1d13xxxfb_resources),
	.resource	= s1d13xxxfb_resources,
पूर्ण;

अटल काष्ठा gpiod_lookup_table jornada_pcmcia_gpiod_table = अणु
	.dev_id = "1800",
	.table = अणु
		GPIO_LOOKUP("sa1111", 0, "s0-power", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("sa1111", 1, "s1-power", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("sa1111", 2, "s0-3v", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("sa1111", 3, "s1-3v", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sa1111_resources[] = अणु
	[0] = DEFINE_RES_MEM(SA1111REGSTART, SA1111REGLEN),
	[1] = DEFINE_RES_IRQ(IRQ_GPIO1),
पूर्ण;

अटल काष्ठा sa1111_platक्रमm_data sa1111_info = अणु
	.disable_devs	= SA1111_DEVID_PS2_MSE,
पूर्ण;

अटल u64 sa1111_dmamask = 0xffffffffUL;

अटल काष्ठा platक्रमm_device sa1111_device = अणु
	.name		= "sa1111",
	.id		= 0,
	.dev		= अणु
		.dma_mask = &sa1111_dmamask,
		.coherent_dma_mask = 0xffffffff,
		.platक्रमm_data = &sa1111_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sa1111_resources),
	.resource	= sa1111_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device jornada_ssp_device = अणु
	.name           = "jornada_ssp",
	.id             = -1,
पूर्ण;

अटल काष्ठा resource jornada_kbd_resources[] = अणु
	DEFINE_RES_IRQ(IRQ_GPIO0),
पूर्ण;

अटल काष्ठा platक्रमm_device jornada_kbd_device = अणु
	.name		= "jornada720_kbd",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(jornada_kbd_resources),
	.resource	= jornada_kbd_resources,
पूर्ण;

अटल काष्ठा gpiod_lookup_table jornada_ts_gpiod_table = अणु
	.dev_id		= "jornada_ts",
	.table		= अणु
		GPIO_LOOKUP("gpio", 9, "penup", GPIO_ACTIVE_HIGH),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device jornada_ts_device = अणु
	.name		= "jornada_ts",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&sa1111_device,
	&jornada_ssp_device,
	&s1d13xxxfb_device,
	&jornada_kbd_device,
	&jornada_ts_device,
पूर्ण;

अटल पूर्णांक __init jornada720_init(व्योम)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (machine_is_jornada720()) अणु
		/* we want to use gpio20 as input to drive the घड़ी of our uart 3 */
		GPDR |= GPIO_GPIO20;	/* Clear gpio20 pin as input */
		TUCR = TUCR_VAL;
		GPSR = GPIO_GPIO20;	/* start gpio20 pin */
		udelay(1);
		GPCR = GPIO_GPIO20;	/* stop gpio20 */
		udelay(1);
		GPSR = GPIO_GPIO20;	/* restart gpio20 */
		udelay(20);		/* give it some समय to restart */

		gpiod_add_lookup_table(&jornada_ts_gpiod_table);
		gpiod_add_lookup_table(&jornada_pcmcia_gpiod_table);

		ret = platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
	पूर्ण

	वापस ret;
पूर्ण

arch_initcall(jornada720_init);

अटल काष्ठा map_desc jornada720_io_desc[] __initdata = अणु
	अणु	/* Epson रेजिस्टरs */
		.भव	= 0xf0000000,
		.pfn		= __phys_to_pfn(EPSONREGSTART),
		.length		= EPSONREGLEN,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* Epson frame buffer */
		.भव	= 0xf1000000,
		.pfn		= __phys_to_pfn(EPSONFBSTART),
		.length		= EPSONFBLEN,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init jornada720_map_io(व्योम)
अणु
	sa1100_map_io();
	iotable_init(jornada720_io_desc, ARRAY_SIZE(jornada720_io_desc));

	sa1100_रेजिस्टर_uart(0, 3);
	sa1100_रेजिस्टर_uart(1, 1);
पूर्ण

अटल काष्ठा mtd_partition jornada720_partitions[] = अणु
	अणु
		.name		= "JORNADA720 boot firmware",
		.size		= 0x00040000,
		.offset		= 0,
		.mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण, अणु
		.name		= "JORNADA720 kernel",
		.size		= 0x000c0000,
		.offset		= 0x00040000,
	पूर्ण, अणु
		.name		= "JORNADA720 params",
		.size		= 0x00040000,
		.offset		= 0x00100000,
	पूर्ण, अणु
		.name		= "JORNADA720 initrd",
		.size		= 0x00100000,
		.offset		= 0x00140000,
	पूर्ण, अणु
		.name		= "JORNADA720 root cramfs",
		.size		= 0x00300000,
		.offset		= 0x00240000,
	पूर्ण, अणु
		.name		= "JORNADA720 usr cramfs",
		.size		= 0x00800000,
		.offset		= 0x00540000,
	पूर्ण, अणु
		.name		= "JORNADA720 usr local",
		.size		= 0, /* will expand to the end of the flash */
		.offset		= 0x00d00000,
	पूर्ण
पूर्ण;

अटल व्योम jornada720_set_vpp(पूर्णांक vpp)
अणु
	अगर (vpp)
		/* enabling flash ग_लिखो (line 470 of HP's करोc) */
		PPSR |= PPC_LDD7;
	अन्यथा
		/* disabling flash ग_लिखो (line 470 of HP's करोc) */
		PPSR &= ~PPC_LDD7;
	PPDR |= PPC_LDD7;
पूर्ण

अटल काष्ठा flash_platक्रमm_data jornada720_flash_data = अणु
	.map_name	= "cfi_probe",
	.set_vpp	= jornada720_set_vpp,
	.parts		= jornada720_partitions,
	.nr_parts	= ARRAY_SIZE(jornada720_partitions),
पूर्ण;

अटल काष्ठा resource jornada720_flash_resource =
	DEFINE_RES_MEM(SA1100_CS0_PHYS, SZ_32M);

अटल व्योम __init jornada720_mach_init(व्योम)
अणु
	sa11x0_रेजिस्टर_mtd(&jornada720_flash_data, &jornada720_flash_resource, 1);
पूर्ण

MACHINE_START(JORNADA720, "HP Jornada 720")
	/* Maपूर्णांकainer: Kristoffer Ericson <Kristoffer.Ericson@gmail.com> */
	.atag_offset	= 0x100,
	.map_io		= jornada720_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= sa1100_init_irq,
	.init_समय	= sa1100_समयr_init,
	.init_machine	= jornada720_mach_init,
	.init_late	= sa11x0_init_late,
#अगर_घोषित CONFIG_SA1111
	.dma_zone_size	= SZ_1M,
#पूर्ण_अगर
	.restart	= sa11x0_restart,
MACHINE_END
