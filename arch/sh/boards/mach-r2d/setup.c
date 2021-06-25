<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas Technology Sales RTS7751R2D Support.
 *
 * Copyright (C) 2002 - 2006 Atom Create Engineering Co., Ltd.
 * Copyright (C) 2004 - 2007 Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/sm501.h>
#समावेश <linux/sm501-regs.h>
#समावेश <linux/pm.h>
#समावेश <linux/fb.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <यंत्र/machvec.h>
#समावेश <mach/r2d.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/io_trapped.h>
#समावेश <यंत्र/spi.h>

अटल काष्ठा resource cf_ide_resources[] = अणु
	[0] = अणु
		.start	= PA_AREA5_IO + 0x1000,
		.end	= PA_AREA5_IO + 0x1000 + 0x10 - 0x2,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PA_AREA5_IO + 0x80c,
		.end	= PA_AREA5_IO + 0x80c,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
#अगर_अघोषित CONFIG_RTS7751R2D_1 /* For R2D-1 polling is preferred */
	[2] = अणु
		.start	= IRQ_CF_IDE,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
#पूर्ण_अगर
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

अटल काष्ठा spi_board_info spi_bus[] = अणु
	अणु
		.modalias	= "rtc-r9701",
		.max_speed_hz	= 1000000,
		.mode		= SPI_MODE_3,
	पूर्ण,
पूर्ण;

अटल व्योम r2d_chip_select(काष्ठा sh_spi_info *spi, पूर्णांक cs, पूर्णांक state)
अणु
	BUG_ON(cs != 0);  /* Single Epson RTC-9701JE attached on CS0 */
	__raw_ग_लिखोw(state == BITBANG_CS_ACTIVE, PA_RTCCE);
पूर्ण

अटल काष्ठा sh_spi_info spi_info = अणु
	.num_chipselect = 1,
	.chip_select = r2d_chip_select,
पूर्ण;

अटल काष्ठा resource spi_sh_sci_resources[] = अणु
	अणु
		.start	= 0xffe00000,
		.end	= 0xffe0001f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device spi_sh_sci_device  = अणु
	.name		= "spi_sh_sci",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(spi_sh_sci_resources),
	.resource	= spi_sh_sci_resources,
	.dev	= अणु
		.platक्रमm_data	= &spi_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource heartbeat_resources[] = अणु
	[0] = अणु
		.start	= PA_OUTPORT,
		.end	= PA_OUTPORT,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name		= "heartbeat",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(heartbeat_resources),
	.resource	= heartbeat_resources,
पूर्ण;

अटल काष्ठा resource sm501_resources[] = अणु
	[0]	= अणु
		.start	= 0x10000000,
		.end	= 0x13e00000 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1]	= अणु
		.start	= 0x13e00000,
		.end	= 0x13ffffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[2]	= अणु
		.start	= IRQ_VOYAGER,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा fb_videomode sm501_शेष_mode = अणु
	.pixघड़ी	= 35714,
	.xres		= 640,
	.yres		= 480,
	.left_margin	= 105,
	.right_margin	= 50,
	.upper_margin	= 35,
	.lower_margin	= 0,
	.hsync_len	= 96,
	.vsync_len	= 2,
	.sync = FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा sm501_platdata_fbsub sm501_pdata_fbsub_pnl = अणु
	.def_bpp	= 16,
	.def_mode	= &sm501_शेष_mode,
	.flags		= SM501FB_FLAG_USE_INIT_MODE |
			  SM501FB_FLAG_USE_HWCURSOR |
			  SM501FB_FLAG_USE_HWACCEL |
			  SM501FB_FLAG_DISABLE_AT_EXIT,
पूर्ण;

अटल काष्ठा sm501_platdata_fbsub sm501_pdata_fbsub_crt = अणु
	.flags		= (SM501FB_FLAG_USE_INIT_MODE |
			   SM501FB_FLAG_USE_HWCURSOR |
			   SM501FB_FLAG_USE_HWACCEL |
			   SM501FB_FLAG_DISABLE_AT_EXIT),

पूर्ण;

अटल काष्ठा sm501_platdata_fb sm501_fb_pdata = अणु
	.fb_route	= SM501_FB_OWN,
	.fb_crt		= &sm501_pdata_fbsub_crt,
	.fb_pnl		= &sm501_pdata_fbsub_pnl,
	.flags		= SM501_FBPD_SWAP_FB_ENDIAN,
पूर्ण;

अटल काष्ठा sm501_initdata sm501_initdata = अणु
	.devices	= SM501_USE_USB_HOST | SM501_USE_UART0,
पूर्ण;

अटल काष्ठा sm501_platdata sm501_platक्रमm_data = अणु
	.init		= &sm501_initdata,
	.fb		= &sm501_fb_pdata,
पूर्ण;

अटल काष्ठा platक्रमm_device sm501_device = अणु
	.name		= "sm501",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &sm501_platक्रमm_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sm501_resources),
	.resource	= sm501_resources,
पूर्ण;

अटल काष्ठा mtd_partition r2d_partitions[] = अणु
	अणु
		.name		= "U-Boot",
		.offset		= 0x00000000,
		.size		= 0x00040000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "Environment",
		.offset		= MTDPART_OFS_NXTBLK,
		.size		= 0x00040000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "Kernel",
		.offset		= MTDPART_OFS_NXTBLK,
		.size		= 0x001c0000,
	पूर्ण, अणु
		.name		= "Flash_FS",
		.offset		= MTDPART_OFS_NXTBLK,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data flash_data = अणु
	.width		= 2,
	.nr_parts	= ARRAY_SIZE(r2d_partitions),
	.parts		= r2d_partitions,
पूर्ण;

अटल काष्ठा resource flash_resource = अणु
	.start		= 0x00000000,
	.end		= 0x02000000,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device flash_device = अणु
	.name		= "physmap-flash",
	.id		= -1,
	.resource	= &flash_resource,
	.num_resources	= 1,
	.dev		= अणु
		.platक्रमm_data = &flash_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *rts7751r2d_devices[] __initdata = अणु
	&sm501_device,
	&heartbeat_device,
	&spi_sh_sci_device,
पूर्ण;

/*
 * The CF is connected with a 16-bit bus where 8-bit operations are
 * unsupported. The linux ata driver is however using 8-bit operations, so
 * insert a trapped io filter to convert 8-bit operations पूर्णांकo 16-bit.
 */
अटल काष्ठा trapped_io cf_trapped_io = अणु
	.resource		= cf_ide_resources,
	.num_resources		= 2,
	.minimum_bus_width	= 16,
पूर्ण;

अटल पूर्णांक __init rts7751r2d_devices_setup(व्योम)
अणु
	अगर (रेजिस्टर_trapped_io(&cf_trapped_io) == 0)
		platक्रमm_device_रेजिस्टर(&cf_ide_device);

	अगर (mach_is_r2d_plus())
		platक्रमm_device_रेजिस्टर(&flash_device);

	spi_रेजिस्टर_board_info(spi_bus, ARRAY_SIZE(spi_bus));

	वापस platक्रमm_add_devices(rts7751r2d_devices,
				    ARRAY_SIZE(rts7751r2d_devices));
पूर्ण
device_initcall(rts7751r2d_devices_setup);

अटल व्योम rts7751r2d_घातer_off(व्योम)
अणु
	__raw_ग_लिखोw(0x0001, PA_POWOFF);
पूर्ण

/*
 * Initialize the board
 */
अटल व्योम __init rts7751r2d_setup(अक्षर **cmdline_p)
अणु
	व्योम __iomem *sm501_reg;
	u16 ver = __raw_पढ़ोw(PA_VERREG);

	prपूर्णांकk(KERN_INFO "Renesas Technology Sales RTS7751R2D support.\n");

	prपूर्णांकk(KERN_INFO "FPGA version:%d (revision:%d)\n",
					(ver >> 4) & 0xf, ver & 0xf);

	__raw_ग_लिखोw(0x0000, PA_OUTPORT);
	pm_घातer_off = rts7751r2d_घातer_off;

	/* sm501 dram configuration:
	 * ColSizeX = 11 - External Memory Column Size: 256 words.
	 * APX = 1 - External Memory Active to Pre-Charge Delay: 7 घड़ीs.
	 * RstX = 1 - External Memory Reset: Normal.
	 * Rfsh = 1 - Local Memory Refresh to Command Delay: 12 घड़ीs.
	 * BwC =  1 - Local Memory Block Write Cycle Time: 2 घड़ीs.
	 * BwP =  1 - Local Memory Block Write to Pre-Charge Delay: 1 घड़ी.
	 * AP = 1 - Internal Memory Active to Pre-Charge Delay: 7 घड़ीs.
	 * Rst = 1 - Internal Memory Reset: Normal.
	 * RA = 1 - Internal Memory Reमुख्य in Active State: Do not reमुख्य.
	 */

	sm501_reg = (व्योम __iomem *)0xb3e00000 + SM501_DRAM_CONTROL;
	ग_लिखोl(पढ़ोl(sm501_reg) | 0x00f107c0, sm501_reg);
पूर्ण

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_rts7751r2d __iniपंचांगv = अणु
	.mv_name		= "RTS7751R2D",
	.mv_setup		= rts7751r2d_setup,
	.mv_init_irq		= init_rts7751r2d_IRQ,
	.mv_irq_demux		= rts7751r2d_irq_demux,
पूर्ण;
