<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/renesas/sh7763rdp/setup.c
 *
 * Renesas Solutions sh7763rdp board
 *
 * Copyright (C) 2008 Renesas Solutions Corp.
 * Copyright (C) 2008 Nobuhiro Iwamatsu <iwamatsu.nobuhiro@renesas.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/fb.h>
#समावेश <linux/पन.स>
#समावेश <linux/sh_eth.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <mach/sh7763rdp.h>
#समावेश <यंत्र/sh7760fb.h>

/* NOR Flash */
अटल काष्ठा mtd_partition sh7763rdp_nor_flash_partitions[] = अणु
	अणु
		.name = "U-Boot",
		.offset = 0,
		.size = (2 * 128 * 1024),
		.mask_flags = MTD_WRITEABLE,	/* Read-only */
	पूर्ण, अणु
		.name = "Linux-Kernel",
		.offset = MTDPART_OFS_APPEND,
		.size = (20 * 128 * 1024),
	पूर्ण, अणु
		.name = "Root Filesystem",
		.offset = MTDPART_OFS_APPEND,
		.size = MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data sh7763rdp_nor_flash_data = अणु
	.width = 2,
	.parts = sh7763rdp_nor_flash_partitions,
	.nr_parts = ARRAY_SIZE(sh7763rdp_nor_flash_partitions),
पूर्ण;

अटल काष्ठा resource sh7763rdp_nor_flash_resources[] = अणु
	[0] = अणु
		.name = "NOR Flash",
		.start = 0,
		.end = (64 * 1024 * 1024),
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sh7763rdp_nor_flash_device = अणु
	.name = "physmap-flash",
	.resource = sh7763rdp_nor_flash_resources,
	.num_resources = ARRAY_SIZE(sh7763rdp_nor_flash_resources),
	.dev = अणु
		.platक्रमm_data = &sh7763rdp_nor_flash_data,
	पूर्ण,
पूर्ण;

/*
 * SH-Ether
 *
 * SH Ether of SH7763 has multi IRQ handling.
 * (0x920,0x940,0x960 -> 0x920)
 */
अटल काष्ठा resource sh_eth_resources[] = अणु
	अणु
		.start  = 0xFEE00800,   /* use eth1 */
		.end    = 0xFEE00F7C - 1,
		.flags  = IORESOURCE_MEM,
	पूर्ण, अणु
		.start  = 0xFEE01800,   /* TSU */
		.end    = 0xFEE01FFF,
		.flags  = IORESOURCE_MEM,
	पूर्ण, अणु
		.start  = evt2irq(0x920),   /* irq number */
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_eth_plat_data sh7763_eth_pdata = अणु
	.phy = 1,
	.phy_पूर्णांकerface = PHY_INTERFACE_MODE_MII,
पूर्ण;

अटल काष्ठा platक्रमm_device sh7763rdp_eth_device = अणु
	.name       = "sh7763-gether",
	.resource   = sh_eth_resources,
	.num_resources  = ARRAY_SIZE(sh_eth_resources),
	.dev        = अणु
		.platक्रमm_data = &sh7763_eth_pdata,
	पूर्ण,
पूर्ण;

/* SH7763 LCDC */
अटल काष्ठा resource sh7763rdp_fb_resources[] = अणु
	अणु
		.start  = 0xFFE80000,
		.end    = 0xFFE80442 - 1,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा fb_videomode sh7763fb_videomode = अणु
	.refresh = 60,
	.name = "VGA Monitor",
	.xres = 640,
	.yres = 480,
	.pixघड़ी = 10000,
	.left_margin = 80,
	.right_margin = 24,
	.upper_margin = 30,
	.lower_margin = 1,
	.hsync_len = 96,
	.vsync_len = 1,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = FBINFO_FLAG_DEFAULT,
पूर्ण;

अटल काष्ठा sh7760fb_platdata sh7763fb_def_pdata = अणु
	.def_mode = &sh7763fb_videomode,
	.ldmtr = (LDMTR_TFT_COLOR_16|LDMTR_MCNT),
	.lddfr = LDDFR_16BPP_RGB565,
	.ldpmmr = 0x0000,
	.ldpspr = 0xFFFF,
	.ldaclnr = 0x0001,
	.ldickr = 0x1102,
	.rotate = 0,
	.novsync = 0,
	.blank = शून्य,
पूर्ण;

अटल काष्ठा platक्रमm_device sh7763rdp_fb_device = अणु
	.name		= "sh7760-lcdc",
	.resource	= sh7763rdp_fb_resources,
	.num_resources = ARRAY_SIZE(sh7763rdp_fb_resources),
	.dev = अणु
		.platक्रमm_data = &sh7763fb_def_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7763rdp_devices[] __initdata = अणु
	&sh7763rdp_nor_flash_device,
	&sh7763rdp_eth_device,
	&sh7763rdp_fb_device,
पूर्ण;

अटल पूर्णांक __init sh7763rdp_devices_setup(व्योम)
अणु
	वापस platक्रमm_add_devices(sh7763rdp_devices,
				    ARRAY_SIZE(sh7763rdp_devices));
पूर्ण
device_initcall(sh7763rdp_devices_setup);

अटल व्योम __init sh7763rdp_setup(अक्षर **cmdline_p)
अणु
	/* Board version check */
	अगर (__raw_पढ़ोw(CPLD_BOARD_ID_ERV_REG) == 0xECB1)
		prपूर्णांकk(KERN_INFO "RTE Standard Configuration\n");
	अन्यथा
		prपूर्णांकk(KERN_INFO "RTA Standard Configuration\n");

	/* USB pin select bits (clear bit 5-2 to 0) */
	__raw_ग_लिखोw((__raw_पढ़ोw(PORT_PSEL2) & 0xFFC3), PORT_PSEL2);
	/* USBH setup port I controls to other (clear bits 4-9 to 0) */
	__raw_ग_लिखोw(__raw_पढ़ोw(PORT_PICR) & 0xFC0F, PORT_PICR);

	/* Select USB Host controller */
	__raw_ग_लिखोw(0x00, USB_USBHSC);

	/* For LCD */
	/* set PTJ7-1, bits 15-2 of PJCR to 0 */
	__raw_ग_लिखोw(__raw_पढ़ोw(PORT_PJCR) & 0x0003, PORT_PJCR);
	/* set PTI5, bits 11-10 of PICR to 0 */
	__raw_ग_लिखोw(__raw_पढ़ोw(PORT_PICR) & 0xF3FF, PORT_PICR);
	__raw_ग_लिखोw(0, PORT_PKCR);
	__raw_ग_लिखोw(0, PORT_PLCR);
	/* set PSEL2 bits 14-8, 5-4, of PSEL2 to 0 */
	__raw_ग_लिखोw((__raw_पढ़ोw(PORT_PSEL2) & 0x00C0), PORT_PSEL2);
	/* set PSEL3 bits 14-12, 6-4, 2-0 of PSEL3 to 0 */
	__raw_ग_लिखोw((__raw_पढ़ोw(PORT_PSEL3) & 0x0700), PORT_PSEL3);

	/* For HAC */
	/* bit3-0  0100:HAC & SSI1 enable */
	__raw_ग_लिखोw((__raw_पढ़ोw(PORT_PSEL1) & 0xFFF0) | 0x0004, PORT_PSEL1);
	/* bit14      1:SSI_HAC_CLK enable */
	__raw_ग_लिखोw(__raw_पढ़ोw(PORT_PSEL4) | 0x4000, PORT_PSEL4);

	/* SH-Ether */
	__raw_ग_लिखोw((__raw_पढ़ोw(PORT_PSEL1) & ~0xff00) | 0x2400, PORT_PSEL1);
	__raw_ग_लिखोw(0x0, PORT_PFCR);
	__raw_ग_लिखोw(0x0, PORT_PFCR);
	__raw_ग_लिखोw(0x0, PORT_PFCR);

	/* MMC */
	/*selects SCIF and MMC other functions */
	__raw_ग_लिखोw(0x0001, PORT_PSEL0);
	/* MMC घड़ी operates */
	__raw_ग_लिखोl(__raw_पढ़ोl(MSTPCR1) & ~0x8, MSTPCR1);
	__raw_ग_लिखोw(__raw_पढ़ोw(PORT_PACR) & ~0x3000, PORT_PACR);
	__raw_ग_लिखोw(__raw_पढ़ोw(PORT_PCCR) & ~0xCFC3, PORT_PCCR);
पूर्ण

अटल काष्ठा sh_machine_vector mv_sh7763rdp __iniपंचांगv = अणु
	.mv_name = "sh7763drp",
	.mv_setup = sh7763rdp_setup,
	.mv_init_irq = init_sh7763rdp_IRQ,
पूर्ण;
