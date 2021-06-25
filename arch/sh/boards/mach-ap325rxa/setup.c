<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas - AP-325RXA
 * (Compatible with Algo System ., LTD. - AP-320A)
 *
 * Copyright (C) 2008 Renesas Solutions Corp.
 * Author : Yusuke Goda <goda.yuske@renesas.com>
 */

#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/suspend.h>

#समावेश <cpu/sh7723.h>

#समावेश <linux/dma-map-ops.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/sh_flctl.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/smsc911x.h>
#समावेश <linux/videodev2.h>

#समावेश <media/drv-पूर्णांकf/renesas-ceu.h>
#समावेश <media/i2c/ov772x.h>

#समावेश <video/sh_mobile_lcdc.h>

#घोषणा CEU_BUFFER_MEMORY_SIZE		(4 << 20)
अटल phys_addr_t ceu_dma_membase;

/* Dummy supplies, where voltage करोesn't matter */
अटल काष्ठा regulator_consumer_supply dummy_supplies[] = अणु
	REGULATOR_SUPPLY("vddvario", "smsc911x"),
	REGULATOR_SUPPLY("vdd33a", "smsc911x"),
पूर्ण;

अटल काष्ठा smsc911x_platक्रमm_config smsc911x_config = अणु
	.phy_पूर्णांकerface	= PHY_INTERFACE_MODE_MII,
	.irq_polarity	= SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type	= SMSC911X_IRQ_TYPE_OPEN_DRAIN,
	.flags		= SMSC911X_USE_32BIT,
पूर्ण;

अटल काष्ठा resource smsc9118_resources[] = अणु
	[0] = अणु
		.start	= 0xb6080000,
		.end	= 0xb60fffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0x660),
		.end	= evt2irq(0x660),
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device smsc9118_device = अणु
	.name		= "smsc911x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smsc9118_resources),
	.resource	= smsc9118_resources,
	.dev		= अणु
		.platक्रमm_data = &smsc911x_config,
	पूर्ण,
पूर्ण;

/*
 * AP320 and AP325RXA has CPLD data in NOR Flash(0xA80000-0xABFFFF).
 * If this area erased, this board can not boot.
 */
अटल काष्ठा mtd_partition ap325rxa_nor_flash_partitions[] = अणु
	अणु
		.name = "uboot",
		.offset = 0,
		.size = (1 * 1024 * 1024),
		.mask_flags = MTD_WRITEABLE,	/* Read-only */
	पूर्ण, अणु
		.name = "kernel",
		.offset = MTDPART_OFS_APPEND,
		.size = (2 * 1024 * 1024),
	पूर्ण, अणु
		.name = "free-area0",
		.offset = MTDPART_OFS_APPEND,
		.size = ((7 * 1024 * 1024) + (512 * 1024)),
	पूर्ण, अणु
		.name = "CPLD-Data",
		.offset = MTDPART_OFS_APPEND,
		.mask_flags = MTD_WRITEABLE,	/* Read-only */
		.size = (1024 * 128 * 2),
	पूर्ण, अणु
		.name = "free-area1",
		.offset = MTDPART_OFS_APPEND,
		.size = MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data ap325rxa_nor_flash_data = अणु
	.width		= 2,
	.parts		= ap325rxa_nor_flash_partitions,
	.nr_parts	= ARRAY_SIZE(ap325rxa_nor_flash_partitions),
पूर्ण;

अटल काष्ठा resource ap325rxa_nor_flash_resources[] = अणु
	[0] = अणु
		.name	= "NOR Flash",
		.start	= 0x00000000,
		.end	= 0x00ffffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device ap325rxa_nor_flash_device = अणु
	.name		= "physmap-flash",
	.resource	= ap325rxa_nor_flash_resources,
	.num_resources	= ARRAY_SIZE(ap325rxa_nor_flash_resources),
	.dev		= अणु
		.platक्रमm_data = &ap325rxa_nor_flash_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition nand_partition_info[] = अणु
	अणु
		.name	= "nand_data",
		.offset	= 0,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource nand_flash_resources[] = अणु
	[0] = अणु
		.start	= 0xa4530000,
		.end	= 0xa45300ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा sh_flctl_platक्रमm_data nand_flash_data = अणु
	.parts		= nand_partition_info,
	.nr_parts	= ARRAY_SIZE(nand_partition_info),
	.flcmncr_val	= FCKSEL_E | TYPESEL_SET | न_अंकWF_E,
	.has_hwecc	= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device nand_flash_device = अणु
	.name		= "sh_flctl",
	.resource	= nand_flash_resources,
	.num_resources	= ARRAY_SIZE(nand_flash_resources),
	.dev		= अणु
		.platक्रमm_data = &nand_flash_data,
	पूर्ण,
पूर्ण;

#घोषणा FPGA_LCDREG	0xB4100180
#घोषणा FPGA_BKLREG	0xB4100212
#घोषणा FPGA_LCDREG_VAL	0x0018
#घोषणा PORT_MSELCRB	0xA4050182
#घोषणा PORT_HIZCRC	0xA405015C
#घोषणा PORT_DRVCRA	0xA405018A
#घोषणा PORT_DRVCRB	0xA405018C

अटल पूर्णांक ap320_wvga_set_brightness(पूर्णांक brightness)
अणु
	अगर (brightness) अणु
		gpio_set_value(GPIO_PTS3, 0);
		__raw_ग_लिखोw(0x100, FPGA_BKLREG);
	पूर्ण अन्यथा अणु
		__raw_ग_लिखोw(0, FPGA_BKLREG);
		gpio_set_value(GPIO_PTS3, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ap320_wvga_घातer_on(व्योम)
अणु
	msleep(100);

	/* ASD AP-320/325 LCD ON */
	__raw_ग_लिखोw(FPGA_LCDREG_VAL, FPGA_LCDREG);
पूर्ण

अटल व्योम ap320_wvga_घातer_off(व्योम)
अणु
	/* ASD AP-320/325 LCD OFF */
	__raw_ग_लिखोw(0, FPGA_LCDREG);
पूर्ण

अटल स्थिर काष्ठा fb_videomode ap325rxa_lcdc_modes[] = अणु
	अणु
		.name = "LB070WV1",
		.xres = 800,
		.yres = 480,
		.left_margin = 32,
		.right_margin = 160,
		.hsync_len = 8,
		.upper_margin = 63,
		.lower_margin = 80,
		.vsync_len = 1,
		.sync = 0, /* hsync and vsync are active low */
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_mobile_lcdc_info lcdc_info = अणु
	.घड़ी_source = LCDC_CLK_EXTERNAL,
	.ch[0] = अणु
		.chan = LCDC_CHAN_MAINLCD,
		.fourcc = V4L2_PIX_FMT_RGB565,
		.पूर्णांकerface_type = RGB18,
		.घड़ी_भागider = 1,
		.lcd_modes = ap325rxa_lcdc_modes,
		.num_modes = ARRAY_SIZE(ap325rxa_lcdc_modes),
		.panel_cfg = अणु
			.width = 152,	/* 7.0 inch */
			.height = 91,
			.display_on = ap320_wvga_घातer_on,
			.display_off = ap320_wvga_घातer_off,
		पूर्ण,
		.bl_info = अणु
			.name = "sh_mobile_lcdc_bl",
			.max_brightness = 1,
			.set_brightness = ap320_wvga_set_brightness,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा resource lcdc_resources[] = अणु
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

अटल काष्ठा platक्रमm_device lcdc_device = अणु
	.name		= "sh_mobile_lcdc_fb",
	.num_resources	= ARRAY_SIZE(lcdc_resources),
	.resource	= lcdc_resources,
	.dev		= अणु
		.platक्रमm_data	= &lcdc_info,
	पूर्ण,
पूर्ण;

/* Powerकरोwn/reset gpios क्रम CEU image sensors */
अटल काष्ठा gpiod_lookup_table ov7725_gpios = अणु
	.dev_id		= "0-0021",
	.table		= अणु
		GPIO_LOOKUP("sh7723_pfc", GPIO_PTZ5, "reset", GPIO_ACTIVE_LOW),
	पूर्ण,
पूर्ण;

अटल काष्ठा ceu_platक्रमm_data ceu0_pdata = अणु
	.num_subdevs			= 1,
	.subdevs = अणु
		अणु /* [0] = ov7725  */
			.flags		= 0,
			.bus_width	= 8,
			.bus_shअगरt	= 0,
			.i2c_adapter_id	= 0,
			.i2c_address	= 0x21,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource ceu_resources[] = अणु
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

अटल काष्ठा platक्रमm_device ap325rxa_ceu_device = अणु
	.name		= "renesas-ceu",
	.id             = 0, /* "ceu.0" घड़ी */
	.num_resources	= ARRAY_SIZE(ceu_resources),
	.resource	= ceu_resources,
	.dev		= अणु
		.platक्रमm_data	= &ceu0_pdata,
	पूर्ण,
पूर्ण;

/* Fixed 3.3V regulators to be used by SDHI0, SDHI1 */
अटल काष्ठा regulator_consumer_supply fixed3v3_घातer_consumers[] =
अणु
	REGULATOR_SUPPLY("vmmc", "sh_mobile_sdhi.0"),
	REGULATOR_SUPPLY("vqmmc", "sh_mobile_sdhi.0"),
	REGULATOR_SUPPLY("vmmc", "sh_mobile_sdhi.1"),
	REGULATOR_SUPPLY("vqmmc", "sh_mobile_sdhi.1"),
पूर्ण;

अटल काष्ठा resource sdhi0_cn3_resources[] = अणु
	[0] = अणु
		.name	= "SDHI0",
		.start	= 0x04ce0000,
		.end	= 0x04ce00ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xe80),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा पंचांगio_mmc_data sdhi0_cn3_data = अणु
	.capabilities	= MMC_CAP_SDIO_IRQ,
पूर्ण;

अटल काष्ठा platक्रमm_device sdhi0_cn3_device = अणु
	.name		= "sh_mobile_sdhi",
	.id             = 0, /* "sdhi0" घड़ी */
	.num_resources	= ARRAY_SIZE(sdhi0_cn3_resources),
	.resource	= sdhi0_cn3_resources,
	.dev = अणु
		.platक्रमm_data = &sdhi0_cn3_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sdhi1_cn7_resources[] = अणु
	[0] = अणु
		.name	= "SDHI1",
		.start	= 0x04cf0000,
		.end	= 0x04cf00ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0x4e0),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा पंचांगio_mmc_data sdhi1_cn7_data = अणु
	.capabilities	= MMC_CAP_SDIO_IRQ,
पूर्ण;

अटल काष्ठा platक्रमm_device sdhi1_cn7_device = अणु
	.name		= "sh_mobile_sdhi",
	.id             = 1, /* "sdhi1" घड़ी */
	.num_resources	= ARRAY_SIZE(sdhi1_cn7_resources),
	.resource	= sdhi1_cn7_resources,
	.dev = अणु
		.platक्रमm_data = &sdhi1_cn7_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा ov772x_camera_info ov7725_info = अणु
	.flags		= OV772X_FLAG_VFLIP | OV772X_FLAG_HFLIP,
	.edgectrl	= OV772X_AUTO_EDGECTRL(0xf, 0),
पूर्ण;

अटल काष्ठा i2c_board_info ap325rxa_i2c_devices[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("pcf8563", 0x51),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("ov772x", 0x21),
		.platक्रमm_data = &ov7725_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *ap325rxa_devices[] __initdata = अणु
	&smsc9118_device,
	&ap325rxa_nor_flash_device,
	&lcdc_device,
	&nand_flash_device,
	&sdhi0_cn3_device,
	&sdhi1_cn7_device,
पूर्ण;

बाह्य अक्षर ap325rxa_sdram_enter_start;
बाह्य अक्षर ap325rxa_sdram_enter_end;
बाह्य अक्षर ap325rxa_sdram_leave_start;
बाह्य अक्षर ap325rxa_sdram_leave_end;

अटल पूर्णांक __init ap325rxa_devices_setup(व्योम)
अणु
	/* रेजिस्टर board specअगरic self-refresh code */
	sh_mobile_रेजिस्टर_self_refresh(SUSP_SH_STANDBY | SUSP_SH_SF,
					&ap325rxa_sdram_enter_start,
					&ap325rxa_sdram_enter_end,
					&ap325rxa_sdram_leave_start,
					&ap325rxa_sdram_leave_end);

	regulator_रेजिस्टर_always_on(0, "fixed-3.3V", fixed3v3_घातer_consumers,
				     ARRAY_SIZE(fixed3v3_घातer_consumers), 3300000);
	regulator_रेजिस्टर_fixed(1, dummy_supplies, ARRAY_SIZE(dummy_supplies));

	/* LD3 and LD4 LEDs */
	gpio_request(GPIO_PTX5, शून्य); /* RUN */
	gpio_direction_output(GPIO_PTX5, 1);
	gpio_export(GPIO_PTX5, 0);

	gpio_request(GPIO_PTX4, शून्य); /* INDICATOR */
	gpio_direction_output(GPIO_PTX4, 0);
	gpio_export(GPIO_PTX4, 0);

	/* SW1 input */
	gpio_request(GPIO_PTF7, शून्य); /* MODE */
	gpio_direction_input(GPIO_PTF7);
	gpio_export(GPIO_PTF7, 0);

	/* LCDC */
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
	gpio_request(GPIO_FN_LCDLCLK_PTR, शून्य);
	gpio_request(GPIO_FN_LCDDCK, शून्य);
	gpio_request(GPIO_FN_LCDVEPWC, शून्य);
	gpio_request(GPIO_FN_LCDVCPWC, शून्य);
	gpio_request(GPIO_FN_LCDVSYN, शून्य);
	gpio_request(GPIO_FN_LCDHSYN, शून्य);
	gpio_request(GPIO_FN_LCDDISP, शून्य);
	gpio_request(GPIO_FN_LCDDON, शून्य);

	/* LCD backlight */
	gpio_request(GPIO_PTS3, शून्य);
	gpio_direction_output(GPIO_PTS3, 1);

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

	gpio_request(GPIO_PTZ7, शून्य);
	gpio_direction_output(GPIO_PTZ7, 0); /* OE_CAM */
	gpio_request(GPIO_PTZ6, शून्य);
	gpio_direction_output(GPIO_PTZ6, 0); /* STBY_CAM */
	gpio_request(GPIO_PTZ5, शून्य);
	gpio_direction_output(GPIO_PTZ5, 0); /* RST_CAM */
	gpio_request(GPIO_PTZ4, शून्य);
	gpio_direction_output(GPIO_PTZ4, 0); /* SADDR */

	__raw_ग_लिखोw(__raw_पढ़ोw(PORT_MSELCRB) & ~0x0001, PORT_MSELCRB);

	/* FLCTL */
	gpio_request(GPIO_FN_FCE, शून्य);
	gpio_request(GPIO_FN_NAF7, शून्य);
	gpio_request(GPIO_FN_NAF6, शून्य);
	gpio_request(GPIO_FN_NAF5, शून्य);
	gpio_request(GPIO_FN_NAF4, शून्य);
	gpio_request(GPIO_FN_NAF3, शून्य);
	gpio_request(GPIO_FN_NAF2, शून्य);
	gpio_request(GPIO_FN_NAF1, शून्य);
	gpio_request(GPIO_FN_NAF0, शून्य);
	gpio_request(GPIO_FN_FCDE, शून्य);
	gpio_request(GPIO_FN_FOE, शून्य);
	gpio_request(GPIO_FN_FSC, शून्य);
	gpio_request(GPIO_FN_FWE, शून्य);
	gpio_request(GPIO_FN_FRB, शून्य);

	__raw_ग_लिखोw(0, PORT_HIZCRC);
	__raw_ग_लिखोw(0xFFFF, PORT_DRVCRA);
	__raw_ग_लिखोw(0xFFFF, PORT_DRVCRB);

	/* SDHI0 - CN3 - SD CARD */
	gpio_request(GPIO_FN_SDHI0CD_PTD, शून्य);
	gpio_request(GPIO_FN_SDHI0WP_PTD, शून्य);
	gpio_request(GPIO_FN_SDHI0D3_PTD, शून्य);
	gpio_request(GPIO_FN_SDHI0D2_PTD, शून्य);
	gpio_request(GPIO_FN_SDHI0D1_PTD, शून्य);
	gpio_request(GPIO_FN_SDHI0D0_PTD, शून्य);
	gpio_request(GPIO_FN_SDHI0CMD_PTD, शून्य);
	gpio_request(GPIO_FN_SDHI0CLK_PTD, शून्य);

	/* SDHI1 - CN7 - MICRO SD CARD */
	gpio_request(GPIO_FN_SDHI1CD, शून्य);
	gpio_request(GPIO_FN_SDHI1D3, शून्य);
	gpio_request(GPIO_FN_SDHI1D2, शून्य);
	gpio_request(GPIO_FN_SDHI1D1, शून्य);
	gpio_request(GPIO_FN_SDHI1D0, शून्य);
	gpio_request(GPIO_FN_SDHI1CMD, शून्य);
	gpio_request(GPIO_FN_SDHI1CLK, शून्य);

	/* Add a घड़ी alias क्रम ov7725 xclk source. */
	clk_add_alias(शून्य, "0-0021", "video_clk", शून्य);

	/* Register RSTB gpio क्रम ov7725 camera sensor. */
	gpiod_add_lookup_table(&ov7725_gpios);

	i2c_रेजिस्टर_board_info(0, ap325rxa_i2c_devices,
				ARRAY_SIZE(ap325rxa_i2c_devices));

	/* Initialize CEU platक्रमm device separately to map memory first */
	device_initialize(&ap325rxa_ceu_device.dev);
	dma_declare_coherent_memory(&ap325rxa_ceu_device.dev,
			ceu_dma_membase, ceu_dma_membase,
			ceu_dma_membase + CEU_BUFFER_MEMORY_SIZE - 1);

	platक्रमm_device_add(&ap325rxa_ceu_device);

	वापस platक्रमm_add_devices(ap325rxa_devices,
				ARRAY_SIZE(ap325rxa_devices));
पूर्ण
arch_initcall(ap325rxa_devices_setup);

/* Return the board specअगरic boot mode pin configuration */
अटल पूर्णांक ap325rxa_mode_pins(व्योम)
अणु
	/* MD0=0, MD1=0, MD2=0: Clock Mode 0
	 * MD3=0: 16-bit Area0 Bus Width
	 * MD5=1: Little Endian
	 * TSTMD=1, MD8=1: Test Mode Disabled
	 */
	वापस MODE_PIN5 | MODE_PIN8;
पूर्ण

/* Reserve a portion of memory क्रम CEU buffers */
अटल व्योम __init ap325rxa_mv_mem_reserve(व्योम)
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

अटल काष्ठा sh_machine_vector mv_ap325rxa __iniपंचांगv = अणु
	.mv_name = "AP-325RXA",
	.mv_mode_pins = ap325rxa_mode_pins,
	.mv_mem_reserve	= ap325rxa_mv_mem_reserve,
पूर्ण;
