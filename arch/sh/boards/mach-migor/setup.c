<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas System Solutions Asia Pte. Ltd - Migo-R
 *
 * Copyright (C) 2008 Magnus Damm
 */
#समावेश <linux/clkdev.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sh_keysc.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <video/sh_mobile_lcdc.h>
#समावेश <media/drv-पूर्णांकf/renesas-ceu.h>
#समावेश <media/i2c/ov772x.h>
#समावेश <media/i2c/tw9910.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/suspend.h>
#समावेश <mach/migor.h>
#समावेश <cpu/sh7722.h>

/* Address     IRQ  Size  Bus  Description
 * 0x00000000       64MB  16   NOR Flash (SP29PL256N)
 * 0x0c000000       64MB  64   SDRAM (2xK4M563233G)
 * 0x10000000  IRQ0       16   Ethernet (SMC91C111)
 * 0x14000000  IRQ4       16   USB 2.0 Host Controller (M66596)
 * 0x18000000       8GB    8   न_अंकD Flash (K9K8G08U0A)
 */

#घोषणा CEU_BUFFER_MEMORY_SIZE		(4 << 20)
अटल phys_addr_t ceu_dma_membase;

अटल काष्ठा smc91x_platdata smc91x_info = अणु
	.flags = SMC91X_USE_16BIT | SMC91X_NOWAIT,
पूर्ण;

अटल काष्ठा resource smc91x_eth_resources[] = अणु
	[0] = अणु
		.name   = "SMC91C111" ,
		.start  = 0x10000300,
		.end    = 0x1000030f,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0x600), /* IRQ0 */
		.flags  = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_eth_device = अणु
	.name           = "smc91x",
	.num_resources  = ARRAY_SIZE(smc91x_eth_resources),
	.resource       = smc91x_eth_resources,
	.dev	= अणु
		.platक्रमm_data	= &smc91x_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_keysc_info sh_keysc_info = अणु
	.mode = SH_KEYSC_MODE_2, /* KEYOUT0->4, KEYIN1->5 */
	.scan_timing = 3,
	.delay = 5,
	.keycodes = अणु
		0, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ENTER,
		0, KEY_F, KEY_C, KEY_D,	KEY_H, KEY_1,
		0, KEY_2, KEY_3, KEY_4,	KEY_5, KEY_6,
		0, KEY_7, KEY_8, KEY_9, KEY_S, KEY_0,
		0, KEY_P, KEY_STOP, KEY_REWIND, KEY_PLAY, KEY_FASTFORWARD,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sh_keysc_resources[] = अणु
	[0] = अणु
		.start  = 0x044b0000,
		.end    = 0x044b000f,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0xbe0),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sh_keysc_device = अणु
	.name           = "sh_keysc",
	.id             = 0, /* "keysc0" घड़ी */
	.num_resources  = ARRAY_SIZE(sh_keysc_resources),
	.resource       = sh_keysc_resources,
	.dev	= अणु
		.platक्रमm_data	= &sh_keysc_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition migor_nor_flash_partitions[] =
अणु
	अणु
		.name = "uboot",
		.offset = 0,
		.size = (1 * 1024 * 1024),
		.mask_flags = MTD_WRITEABLE,	/* Read-only */
	पूर्ण,
	अणु
		.name = "rootfs",
		.offset = MTDPART_OFS_APPEND,
		.size = (15 * 1024 * 1024),
	पूर्ण,
	अणु
		.name = "other",
		.offset = MTDPART_OFS_APPEND,
		.size = MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data migor_nor_flash_data = अणु
	.width		= 2,
	.parts		= migor_nor_flash_partitions,
	.nr_parts	= ARRAY_SIZE(migor_nor_flash_partitions),
पूर्ण;

अटल काष्ठा resource migor_nor_flash_resources[] = अणु
	[0] = अणु
		.name		= "NOR Flash",
		.start		= 0x00000000,
		.end		= 0x03ffffff,
		.flags		= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device migor_nor_flash_device = अणु
	.name		= "physmap-flash",
	.resource	= migor_nor_flash_resources,
	.num_resources	= ARRAY_SIZE(migor_nor_flash_resources),
	.dev		= अणु
		.platक्रमm_data = &migor_nor_flash_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition migor_nand_flash_partitions[] = अणु
	अणु
		.name		= "nanddata1",
		.offset		= 0x0,
		.size		= 512 * 1024 * 1024,
	पूर्ण,
	अणु
		.name		= "nanddata2",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 512 * 1024 * 1024,
	पूर्ण,
पूर्ण;

अटल व्योम migor_nand_flash_cmd_ctl(काष्ठा nand_chip *chip, पूर्णांक cmd,
				     अचिन्हित पूर्णांक ctrl)
अणु
	अगर (cmd == न_अंकD_CMD_NONE)
		वापस;

	अगर (ctrl & न_अंकD_CLE)
		ग_लिखोb(cmd, chip->legacy.IO_ADDR_W + 0x00400000);
	अन्यथा अगर (ctrl & न_अंकD_ALE)
		ग_लिखोb(cmd, chip->legacy.IO_ADDR_W + 0x00800000);
	अन्यथा
		ग_लिखोb(cmd, chip->legacy.IO_ADDR_W);
पूर्ण

अटल पूर्णांक migor_nand_flash_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	वापस gpio_get_value(GPIO_PTA1); /* न_अंकD_RBn */
पूर्ण

अटल काष्ठा platक्रमm_nand_data migor_nand_flash_data = अणु
	.chip = अणु
		.nr_chips = 1,
		.partitions = migor_nand_flash_partitions,
		.nr_partitions = ARRAY_SIZE(migor_nand_flash_partitions),
		.chip_delay = 20,
	पूर्ण,
	.ctrl = अणु
		.dev_पढ़ोy = migor_nand_flash_पढ़ोy,
		.cmd_ctrl = migor_nand_flash_cmd_ctl,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource migor_nand_flash_resources[] = अणु
	[0] = अणु
		.name		= "NAND Flash",
		.start		= 0x18000000,
		.end		= 0x18ffffff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device migor_nand_flash_device = अणु
	.name		= "gen_nand",
	.resource	= migor_nand_flash_resources,
	.num_resources	= ARRAY_SIZE(migor_nand_flash_resources),
	.dev		= अणु
		.platक्रमm_data = &migor_nand_flash_data,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा fb_videomode migor_lcd_modes[] = अणु
	अणु
#अगर defined(CONFIG_SH_MIGOR_RTA_WVGA)
		.name = "LB070WV1",
		.xres = 800,
		.yres = 480,
		.left_margin = 64,
		.right_margin = 16,
		.hsync_len = 120,
		.sync = 0,
#या_अगर defined(CONFIG_SH_MIGOR_QVGA)
		.name = "PH240320T",
		.xres = 320,
		.yres = 240,
		.left_margin = 0,
		.right_margin = 16,
		.hsync_len = 8,
		.sync = FB_SYNC_HOR_HIGH_ACT,
#पूर्ण_अगर
		.upper_margin = 1,
		.lower_margin = 17,
		.vsync_len = 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_mobile_lcdc_info sh_mobile_lcdc_info = अणु
#अगर defined(CONFIG_SH_MIGOR_RTA_WVGA)
	.घड़ी_source = LCDC_CLK_BUS,
	.ch[0] = अणु
		.chan = LCDC_CHAN_MAINLCD,
		.fourcc = V4L2_PIX_FMT_RGB565,
		.पूर्णांकerface_type = RGB16,
		.घड़ी_भागider = 2,
		.lcd_modes = migor_lcd_modes,
		.num_modes = ARRAY_SIZE(migor_lcd_modes),
		.panel_cfg = अणु /* 7.0 inch */
			.width = 152,
			.height = 91,
		पूर्ण,
	पूर्ण
#या_अगर defined(CONFIG_SH_MIGOR_QVGA)
	.घड़ी_source = LCDC_CLK_PERIPHERAL,
	.ch[0] = अणु
		.chan = LCDC_CHAN_MAINLCD,
		.fourcc = V4L2_PIX_FMT_RGB565,
		.पूर्णांकerface_type = SYS16A,
		.घड़ी_भागider = 10,
		.lcd_modes = migor_lcd_modes,
		.num_modes = ARRAY_SIZE(migor_lcd_modes),
		.panel_cfg = अणु
			.width = 49,	/* 2.4 inch */
			.height = 37,
			.setup_sys = migor_lcd_qvga_setup,
		पूर्ण,
		.sys_bus_cfg = अणु
			.ldmt2r = 0x06000a09,
			.ldmt3r = 0x180e3418,
			/* set 1s delay to encourage fsync() */
			.deferred_io_msec = 1000,
		पूर्ण,
	पूर्ण
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा resource migor_lcdc_resources[] = अणु
	[0] = अणु
		.name	= "LCDC",
		.start	= 0xfe940000, /* P4-only space */
		.end	= 0xfe942fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0x580),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device migor_lcdc_device = अणु
	.name		= "sh_mobile_lcdc_fb",
	.num_resources	= ARRAY_SIZE(migor_lcdc_resources),
	.resource	= migor_lcdc_resources,
	.dev	= अणु
		.platक्रमm_data	= &sh_mobile_lcdc_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा ceu_platक्रमm_data ceu_pdata = अणु
	.num_subdevs			= 2,
	.subdevs = अणु
		अणु /* [0] = ov772x */
			.flags		= 0,
			.bus_width	= 8,
			.bus_shअगरt	= 0,
			.i2c_adapter_id	= 0,
			.i2c_address	= 0x21,
		पूर्ण,
		अणु /* [1] = tw9910 */
			.flags		= 0,
			.bus_width	= 8,
			.bus_shअगरt	= 0,
			.i2c_adapter_id	= 0,
			.i2c_address	= 0x45,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource migor_ceu_resources[] = अणु
	[0] = अणु
		.name	= "CEU",
		.start	= 0xfe910000,
		.end	= 0xfe91009f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0x880),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device migor_ceu_device = अणु
	.name		= "renesas-ceu",
	.id             = 0, /* ceu.0 */
	.num_resources	= ARRAY_SIZE(migor_ceu_resources),
	.resource	= migor_ceu_resources,
	.dev	= अणु
		.platक्रमm_data	= &ceu_pdata,
	पूर्ण,
पूर्ण;

/* Powerकरोwn/reset gpios क्रम CEU image sensors */
अटल काष्ठा gpiod_lookup_table ov7725_gpios = अणु
	.dev_id		= "0-0021",
	.table		= अणु
		GPIO_LOOKUP("sh7722_pfc", GPIO_PTT0, "powerdown",
			    GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("sh7722_pfc", GPIO_PTT3, "reset", GPIO_ACTIVE_LOW),
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table tw9910_gpios = अणु
	.dev_id		= "0-0045",
	.table		= अणु
		GPIO_LOOKUP("sh7722_pfc", GPIO_PTT2, "pdn", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("sh7722_pfc", GPIO_PTT3, "rstb", GPIO_ACTIVE_LOW),
	पूर्ण,
पूर्ण;

/* Fixed 3.3V regulator to be used by SDHI0 */
अटल काष्ठा regulator_consumer_supply fixed3v3_घातer_consumers[] =
अणु
	REGULATOR_SUPPLY("vmmc", "sh_mobile_sdhi.0"),
	REGULATOR_SUPPLY("vqmmc", "sh_mobile_sdhi.0"),
पूर्ण;

अटल काष्ठा resource sdhi_cn9_resources[] = अणु
	[0] = अणु
		.name	= "SDHI",
		.start	= 0x04ce0000,
		.end	= 0x04ce00ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xe80),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा पंचांगio_mmc_data sh7724_sdhi_data = अणु
	.chan_priv_tx	= (व्योम *)SHDMA_SLAVE_SDHI0_TX,
	.chan_priv_rx	= (व्योम *)SHDMA_SLAVE_SDHI0_RX,
	.capabilities	= MMC_CAP_SDIO_IRQ,
पूर्ण;

अटल काष्ठा platक्रमm_device sdhi_cn9_device = अणु
	.name		= "sh_mobile_sdhi",
	.num_resources	= ARRAY_SIZE(sdhi_cn9_resources),
	.resource	= sdhi_cn9_resources,
	.dev = अणु
		.platक्रमm_data	= &sh7724_sdhi_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा ov772x_camera_info ov7725_info = अणु
	.flags		= 0,
पूर्ण;

अटल काष्ठा tw9910_video_info tw9910_info = अणु
	.buswidth       = 8,
	.mpout          = TW9910_MPO_FIELD,
पूर्ण;

अटल काष्ठा i2c_board_info migor_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("rs5c372b", 0x32),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("migor_ts", 0x51),
		.irq = evt2irq(0x6c0), /* IRQ6 */
	पूर्ण,
	अणु
		I2C_BOARD_INFO("wm8978", 0x1a),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("ov772x", 0x21),
		.platक्रमm_data = &ov7725_info,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("tw9910", 0x45),
		.platक्रमm_data = &tw9910_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *migor_devices[] __initdata = अणु
	&smc91x_eth_device,
	&sh_keysc_device,
	&migor_lcdc_device,
	&migor_nor_flash_device,
	&migor_nand_flash_device,
	&sdhi_cn9_device,
पूर्ण;

बाह्य अक्षर migor_sdram_enter_start;
बाह्य अक्षर migor_sdram_enter_end;
बाह्य अक्षर migor_sdram_leave_start;
बाह्य अक्षर migor_sdram_leave_end;

अटल पूर्णांक __init migor_devices_setup(व्योम)
अणु
	काष्ठा clk *video_clk;

	/* रेजिस्टर board specअगरic self-refresh code */
	sh_mobile_रेजिस्टर_self_refresh(SUSP_SH_STANDBY | SUSP_SH_SF,
					&migor_sdram_enter_start,
					&migor_sdram_enter_end,
					&migor_sdram_leave_start,
					&migor_sdram_leave_end);

	regulator_रेजिस्टर_always_on(0, "fixed-3.3V", fixed3v3_घातer_consumers,
				     ARRAY_SIZE(fixed3v3_घातer_consumers), 3300000);

	/* Let D11 LED show STATUS0 */
	gpio_request(GPIO_FN_STATUS0, शून्य);

	/* Lit D12 LED show PDSTATUS */
	gpio_request(GPIO_FN_PDSTATUS, शून्य);

	/* SMC91C111 - Enable IRQ0, Setup CS4 क्रम 16-bit fast access */
	gpio_request(GPIO_FN_IRQ0, शून्य);
	__raw_ग_लिखोl(0x00003400, BSC_CS4BCR);
	__raw_ग_लिखोl(0x00110080, BSC_CS4WCR);

	/* KEYSC */
	gpio_request(GPIO_FN_KEYOUT0, शून्य);
	gpio_request(GPIO_FN_KEYOUT1, शून्य);
	gpio_request(GPIO_FN_KEYOUT2, शून्य);
	gpio_request(GPIO_FN_KEYOUT3, शून्य);
	gpio_request(GPIO_FN_KEYOUT4_IN6, शून्य);
	gpio_request(GPIO_FN_KEYIN1, शून्य);
	gpio_request(GPIO_FN_KEYIN2, शून्य);
	gpio_request(GPIO_FN_KEYIN3, शून्य);
	gpio_request(GPIO_FN_KEYIN4, शून्य);
	gpio_request(GPIO_FN_KEYOUT5_IN5, शून्य);

	/* न_अंकD Flash */
	gpio_request(GPIO_FN_CS6A_CE2B, शून्य);
	__raw_ग_लिखोl((__raw_पढ़ोl(BSC_CS6ABCR) & ~0x0600) | 0x0200, BSC_CS6ABCR);
	gpio_request(GPIO_PTA1, शून्य);
	gpio_direction_input(GPIO_PTA1);

	/* SDHI */
	gpio_request(GPIO_FN_SDHICD, शून्य);
	gpio_request(GPIO_FN_SDHIWP, शून्य);
	gpio_request(GPIO_FN_SDHID3, शून्य);
	gpio_request(GPIO_FN_SDHID2, शून्य);
	gpio_request(GPIO_FN_SDHID1, शून्य);
	gpio_request(GPIO_FN_SDHID0, शून्य);
	gpio_request(GPIO_FN_SDHICMD, शून्य);
	gpio_request(GPIO_FN_SDHICLK, शून्य);

	/* Touch Panel */
	gpio_request(GPIO_FN_IRQ6, शून्य);

	/* LCD Panel */
#अगर_घोषित CONFIG_SH_MIGOR_QVGA /* LCDC - QVGA - Enable SYS Interface संकेतs */
	gpio_request(GPIO_FN_LCDD17, शून्य);
	gpio_request(GPIO_FN_LCDD16, शून्य);
	gpio_request(GPIO_FN_LCDD15, शून्य);
	gpio_request(GPIO_FN_LCDD14, शून्य);
	gpio_request(GPIO_FN_LCDD13, शून्य);
	gpio_request(GPIO_FN_LCDD12, शून्य);
	gpio_request(GPIO_FN_LCDD11, शून्य);
	gpio_request(GPIO_FN_LCDD10, शून्य);
	gpio_request(GPIO_FN_LCDD8, शून्य);
	gpio_request(GPIO_FN_LCDD7, शून्य);
	gpio_request(GPIO_FN_LCDD6, शून्य);
	gpio_request(GPIO_FN_LCDD5, शून्य);
	gpio_request(GPIO_FN_LCDD4, शून्य);
	gpio_request(GPIO_FN_LCDD3, शून्य);
	gpio_request(GPIO_FN_LCDD2, शून्य);
	gpio_request(GPIO_FN_LCDD1, शून्य);
	gpio_request(GPIO_FN_LCDRS, शून्य);
	gpio_request(GPIO_FN_LCDCS, शून्य);
	gpio_request(GPIO_FN_LCDRD, शून्य);
	gpio_request(GPIO_FN_LCDWR, शून्य);
	gpio_request(GPIO_PTH2, शून्य); /* LCD_DON */
	gpio_direction_output(GPIO_PTH2, 1);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SH_MIGOR_RTA_WVGA /* LCDC - WVGA - Enable RGB Interface संकेतs */
	gpio_request(GPIO_FN_LCDD15, शून्य);
	gpio_request(GPIO_FN_LCDD14, शून्य);
	gpio_request(GPIO_FN_LCDD13, शून्य);
	gpio_request(GPIO_FN_LCDD12, शून्य);
	gpio_request(GPIO_FN_LCDD11, शून्य);
	gpio_request(GPIO_FN_LCDD10, शून्य);
	gpio_request(GPIO_FN_LCDD9, शून्य);
	gpio_request(GPIO_FN_LCDD8, शून्य);
	gpio_request(GPIO_FN_LCDD7, शून्य);
	gpio_request(GPIO_FN_LCDD6, शून्य);
	gpio_request(GPIO_FN_LCDD5, शून्य);
	gpio_request(GPIO_FN_LCDD4, शून्य);
	gpio_request(GPIO_FN_LCDD3, शून्य);
	gpio_request(GPIO_FN_LCDD2, शून्य);
	gpio_request(GPIO_FN_LCDD1, शून्य);
	gpio_request(GPIO_FN_LCDD0, शून्य);
	gpio_request(GPIO_FN_LCDLCLK, शून्य);
	gpio_request(GPIO_FN_LCDDCK, शून्य);
	gpio_request(GPIO_FN_LCDVEPWC, शून्य);
	gpio_request(GPIO_FN_LCDVCPWC, शून्य);
	gpio_request(GPIO_FN_LCDVSYN, शून्य);
	gpio_request(GPIO_FN_LCDHSYN, शून्य);
	gpio_request(GPIO_FN_LCDDISP, शून्य);
	gpio_request(GPIO_FN_LCDDON, शून्य);
#पूर्ण_अगर

	/* CEU */
	gpio_request(GPIO_FN_VIO_CLK2, शून्य);
	gpio_request(GPIO_FN_VIO_VD2, शून्य);
	gpio_request(GPIO_FN_VIO_HD2, शून्य);
	gpio_request(GPIO_FN_VIO_FLD, शून्य);
	gpio_request(GPIO_FN_VIO_CKO, शून्य);
	gpio_request(GPIO_FN_VIO_D15, शून्य);
	gpio_request(GPIO_FN_VIO_D14, शून्य);
	gpio_request(GPIO_FN_VIO_D13, शून्य);
	gpio_request(GPIO_FN_VIO_D12, शून्य);
	gpio_request(GPIO_FN_VIO_D11, शून्य);
	gpio_request(GPIO_FN_VIO_D10, शून्य);
	gpio_request(GPIO_FN_VIO_D9, शून्य);
	gpio_request(GPIO_FN_VIO_D8, शून्य);

	__raw_ग_लिखोw(__raw_पढ़ोw(PORT_MSELCRB) | 0x2000, PORT_MSELCRB); /* D15->D8 */

	/* SIU: Port B */
	gpio_request(GPIO_FN_SIUBOLR, शून्य);
	gpio_request(GPIO_FN_SIUBOBT, शून्य);
	gpio_request(GPIO_FN_SIUBISLD, शून्य);
	gpio_request(GPIO_FN_SIUBOSLD, शून्य);
	gpio_request(GPIO_FN_SIUMCKB, शून्य);

	/*
	 * The original driver sets SIUB OLR/OBT, ILR/IBT, and SIUA OLR/OBT to
	 * output. Need only SIUB, set to output क्रम master mode (table 34.2)
	 */
	__raw_ग_लिखोw(__raw_पढ़ोw(PORT_MSELCRA) | 1, PORT_MSELCRA);

	 /*
	  * Use 10 MHz VIO_CKO instead of 24 MHz to work around संकेत quality
	  * issues on Panel Board V2.1.
	  */
	video_clk = clk_get(शून्य, "video_clk");
	अगर (!IS_ERR(video_clk)) अणु
		clk_set_rate(video_clk, clk_round_rate(video_clk, 10000000));
		clk_put(video_clk);
	पूर्ण

	/* Add a घड़ी alias क्रम ov7725 xclk source. */
	clk_add_alias(शून्य, "0-0021", "video_clk", शून्य);

	/* Register GPIOs क्रम video sources. */
	gpiod_add_lookup_table(&ov7725_gpios);
	gpiod_add_lookup_table(&tw9910_gpios);

	i2c_रेजिस्टर_board_info(0, migor_i2c_devices,
				ARRAY_SIZE(migor_i2c_devices));

	/* Initialize CEU platक्रमm device separately to map memory first */
	device_initialize(&migor_ceu_device.dev);
	dma_declare_coherent_memory(&migor_ceu_device.dev,
			ceu_dma_membase, ceu_dma_membase,
			ceu_dma_membase + CEU_BUFFER_MEMORY_SIZE - 1);

	platक्रमm_device_add(&migor_ceu_device);

	वापस platक्रमm_add_devices(migor_devices, ARRAY_SIZE(migor_devices));
पूर्ण
arch_initcall(migor_devices_setup);

/* Return the board specअगरic boot mode pin configuration */
अटल पूर्णांक migor_mode_pins(व्योम)
अणु
	/* MD0=1, MD1=1, MD2=0: Clock Mode 3
	 * MD3=0: 16-bit Area0 Bus Width
	 * MD5=1: Little Endian
	 * TSTMD=1, MD8=0: Test Mode Disabled
	 */
	वापस MODE_PIN0 | MODE_PIN1 | MODE_PIN5;
पूर्ण

/* Reserve a portion of memory क्रम CEU buffers */
अटल व्योम __init migor_mv_mem_reserve(व्योम)
अणु
	phys_addr_t phys;
	phys_addr_t size = CEU_BUFFER_MEMORY_SIZE;

	phys = memblock_phys_alloc(size, PAGE_SIZE);
	अगर (!phys)
		panic("Failed to allocate CEU memory\n");

	memblock_मुक्त(phys, size);
	memblock_हटाओ(phys, size);

	ceu_dma_membase = phys;
पूर्ण

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_migor __iniपंचांगv = अणु
	.mv_name		= "Migo-R",
	.mv_mode_pins		= migor_mode_pins,
	.mv_mem_reserve		= migor_mv_mem_reserve,
पूर्ण;
