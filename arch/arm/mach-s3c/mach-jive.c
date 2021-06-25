<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2007 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// http://armlinux.simtec.co.uk/

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>

#समावेश <video/ili9320.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_gpपन.स>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश "hardware-s3c24xx.h"
#समावेश "regs-gpio.h"
#समावेश <linux/platक्रमm_data/fb-s3c2410.h>
#समावेश "gpio-samsung.h"

#समावेश <यंत्र/mach-types.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/partitions.h>

#समावेश "gpio-cfg.h"
#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश "pm.h"
#समावेश <linux/platक्रमm_data/usb-s3c2410_udc.h>

#समावेश "s3c24xx.h"
#समावेश "s3c2412-power.h"

अटल काष्ठा map_desc jive_iodesc[] __initdata = अणु
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg jive_uartcfgs[] = अणु
	[0] = अणु
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण,
	[1] = अणु
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण,
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण
पूर्ण;

/* Jive flash assignment
 *
 * 0x00000000-0x00028000 : uboot
 * 0x00028000-0x0002c000 : uboot env
 * 0x0002c000-0x00030000 : spare
 * 0x00030000-0x00200000 : zimage A
 * 0x00200000-0x01600000 : cramfs A
 * 0x01600000-0x017d0000 : zimage B
 * 0x017d0000-0x02bd0000 : cramfs B
 * 0x02bd0000-0x03fd0000 : yaffs
 */
अटल काष्ठा mtd_partition __initdata jive_imageA_nand_part[] = अणु

#अगर_घोषित CONFIG_MACH_JIVE_SHOW_BOOTLOADER
	/* Don't allow access to the bootloader from linux */
	अणु
		.name           = "uboot",
		.offset         = 0,
		.size           = (160 * SZ_1K),
		.mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,

	/* spare */
        अणु
                .name           = "spare",
                .offset         = (176 * SZ_1K),
                .size           = (16 * SZ_1K),
        पूर्ण,
#पूर्ण_अगर

	/* booted images */
        अणु
		.name		= "kernel (ro)",
		.offset		= (192 * SZ_1K),
		.size		= (SZ_2M) - (192 * SZ_1K),
		.mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
        पूर्ण, अणु
                .name           = "root (ro)",
                .offset         = (SZ_2M),
                .size           = (20 * SZ_1M),
		.mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
        पूर्ण,

	/* yaffs */
	अणु
		.name		= "yaffs",
		.offset		= (44 * SZ_1M),
		.size		= (20 * SZ_1M),
	पूर्ण,

	/* bootloader environment */
	अणु
                .name		= "env",
		.offset		= (160 * SZ_1K),
		.size		= (16 * SZ_1K),
	पूर्ण,

	/* upgrade images */
        अणु
		.name		= "zimage",
		.offset		= (22 * SZ_1M),
		.size		= (2 * SZ_1M) - (192 * SZ_1K),
        पूर्ण, अणु
		.name		= "cramfs",
		.offset		= (24 * SZ_1M) - (192*SZ_1K),
		.size		= (20 * SZ_1M),
        पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition __initdata jive_imageB_nand_part[] = अणु

#अगर_घोषित CONFIG_MACH_JIVE_SHOW_BOOTLOADER
	/* Don't allow access to the bootloader from linux */
	अणु
		.name           = "uboot",
		.offset         = 0,
		.size           = (160 * SZ_1K),
		.mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,

	/* spare */
        अणु
                .name           = "spare",
                .offset         = (176 * SZ_1K),
                .size           = (16 * SZ_1K),
        पूर्ण,
#पूर्ण_अगर

	/* booted images */
        अणु
		.name           = "kernel (ro)",
		.offset         = (22 * SZ_1M),
		.size           = (2 * SZ_1M) - (192 * SZ_1K),
		.mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
        पूर्ण,
	अणु
		.name		= "root (ro)",
		.offset		= (24 * SZ_1M) - (192 * SZ_1K),
                .size		= (20 * SZ_1M),
		.mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,

	/* yaffs */
	अणु
		.name		= "yaffs",
		.offset		= (44 * SZ_1M),
		.size		= (20 * SZ_1M),
        पूर्ण,

	/* bootloader environment */
	अणु
		.name		= "env",
		.offset		= (160 * SZ_1K),
		.size		= (16 * SZ_1K),
	पूर्ण,

	/* upgrade images */
	अणु
		.name		= "zimage",
		.offset		= (192 * SZ_1K),
		.size		= (2 * SZ_1M) - (192 * SZ_1K),
        पूर्ण, अणु
		.name		= "cramfs",
		.offset		= (2 * SZ_1M),
		.size		= (20 * SZ_1M),
        पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_nand_set __initdata jive_nand_sets[] = अणु
	[0] = अणु
		.name           = "flash",
		.nr_chips       = 1,
		.nr_partitions  = ARRAY_SIZE(jive_imageA_nand_part),
		.partitions     = jive_imageA_nand_part,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_platक्रमm_nand __initdata jive_nand_info = अणु
	/* set taken from osiris nand timings, possibly still conservative */
	.tacls		= 30,
	.twrph0		= 55,
	.twrph1		= 40,
	.sets		= jive_nand_sets,
	.nr_sets	= ARRAY_SIZE(jive_nand_sets),
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_SOFT,
पूर्ण;

अटल पूर्णांक __init jive_mtdset(अक्षर *options)
अणु
	काष्ठा s3c2410_nand_set *nand = &jive_nand_sets[0];
	अचिन्हित दीर्घ set;

	अगर (options == शून्य || options[0] == '\0')
		वापस 0;

	अगर (kम_से_अदीर्घ(options, 10, &set)) अणु
		prपूर्णांकk(KERN_ERR "failed to parse mtdset=%s\n", options);
		वापस 0;
	पूर्ण

	चयन (set) अणु
	हाल 1:
		nand->nr_partitions = ARRAY_SIZE(jive_imageB_nand_part);
		nand->partitions = jive_imageB_nand_part;
	हाल 0:
		/* this is alपढ़ोy setup in the nand info */
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Unknown mtd set %ld specified,"
		       "using default.", set);
	पूर्ण

	वापस 0;
पूर्ण

/* parse the mtdset= option given to the kernel command line */
__setup("mtdset=", jive_mtdset);

/* LCD timing and setup */

#घोषणा LCD_XRES	 (240)
#घोषणा LCD_YRES	 (320)
#घोषणा LCD_LEFT_MARGIN  (12)
#घोषणा LCD_RIGHT_MARGIN (12)
#घोषणा LCD_LOWER_MARGIN (12)
#घोषणा LCD_UPPER_MARGIN (12)
#घोषणा LCD_VSYNC	 (2)
#घोषणा LCD_HSYNC	 (2)

#घोषणा LCD_REFRESH	 (60)

#घोषणा LCD_HTOT (LCD_HSYNC + LCD_LEFT_MARGIN + LCD_XRES + LCD_RIGHT_MARGIN)
#घोषणा LCD_VTOT (LCD_VSYNC + LCD_LOWER_MARGIN + LCD_YRES + LCD_UPPER_MARGIN)

अटल काष्ठा s3c2410fb_display jive_vgg2432a4_display[] = अणु
	[0] = अणु
		.width		= LCD_XRES,
		.height		= LCD_YRES,
		.xres		= LCD_XRES,
		.yres		= LCD_YRES,
		.left_margin	= LCD_LEFT_MARGIN,
		.right_margin	= LCD_RIGHT_MARGIN,
		.upper_margin	= LCD_UPPER_MARGIN,
		.lower_margin	= LCD_LOWER_MARGIN,
		.hsync_len	= LCD_HSYNC,
		.vsync_len	= LCD_VSYNC,

		.pixघड़ी	= (1000000000000LL /
				   (LCD_REFRESH * LCD_HTOT * LCD_VTOT)),

		.bpp		= 16,
		.type		= (S3C2410_LCDCON1_TFT16BPP |
				   S3C2410_LCDCON1_TFT),

		.lcdcon5	= (S3C2410_LCDCON5_FRM565 |
				   S3C2410_LCDCON5_INVVLINE |
				   S3C2410_LCDCON5_INVVFRAME |
				   S3C2410_LCDCON5_INVVDEN |
				   S3C2410_LCDCON5_PWREN),
	पूर्ण,
पूर्ण;

/* toकरो - put पूर्णांकo gpio header */

#घोषणा S3C2410_GPCCON_MASK(x)	(3 << ((x) * 2))
#घोषणा S3C2410_GPDCON_MASK(x)	(3 << ((x) * 2))

अटल काष्ठा s3c2410fb_mach_info jive_lcd_config = अणु
	.displays	 = jive_vgg2432a4_display,
	.num_displays	 = ARRAY_SIZE(jive_vgg2432a4_display),
	.शेष_display = 0,

	/* Enable VD[2..7], VD[10..15], VD[18..23] and VCLK, syncs, VDEN
	 * and disable the pull करोwn resistors on pins we are using क्रम LCD
	 * data. */

	.gpcup		= (0xf << 1) | (0x3f << 10),
	.gpcup_reg	= S3C2410_GPCUP,

	.gpccon		= (S3C2410_GPC1_VCLK   | S3C2410_GPC2_VLINE |
			   S3C2410_GPC3_VFRAME | S3C2410_GPC4_VM |
			   S3C2410_GPC10_VD2   | S3C2410_GPC11_VD3 |
			   S3C2410_GPC12_VD4   | S3C2410_GPC13_VD5 |
			   S3C2410_GPC14_VD6   | S3C2410_GPC15_VD7),

	.gpccon_mask	= (S3C2410_GPCCON_MASK(1)  | S3C2410_GPCCON_MASK(2)  |
			   S3C2410_GPCCON_MASK(3)  | S3C2410_GPCCON_MASK(4)  |
			   S3C2410_GPCCON_MASK(10) | S3C2410_GPCCON_MASK(11) |
			   S3C2410_GPCCON_MASK(12) | S3C2410_GPCCON_MASK(13) |
			   S3C2410_GPCCON_MASK(14) | S3C2410_GPCCON_MASK(15)),

	.gpccon_reg	= S3C2410_GPCCON,

	.gpdup		= (0x3f << 2) | (0x3f << 10),

	.gpdup_reg	= S3C2410_GPDUP,

	.gpdcon		= (S3C2410_GPD2_VD10  | S3C2410_GPD3_VD11 |
			   S3C2410_GPD4_VD12  | S3C2410_GPD5_VD13 |
			   S3C2410_GPD6_VD14  | S3C2410_GPD7_VD15 |
			   S3C2410_GPD10_VD18 | S3C2410_GPD11_VD19 |
			   S3C2410_GPD12_VD20 | S3C2410_GPD13_VD21 |
			   S3C2410_GPD14_VD22 | S3C2410_GPD15_VD23),

	.gpdcon_mask	= (S3C2410_GPDCON_MASK(2)  | S3C2410_GPDCON_MASK(3) |
			   S3C2410_GPDCON_MASK(4)  | S3C2410_GPDCON_MASK(5) |
			   S3C2410_GPDCON_MASK(6)  | S3C2410_GPDCON_MASK(7) |
			   S3C2410_GPDCON_MASK(10) | S3C2410_GPDCON_MASK(11)|
			   S3C2410_GPDCON_MASK(12) | S3C2410_GPDCON_MASK(13)|
			   S3C2410_GPDCON_MASK(14) | S3C2410_GPDCON_MASK(15)),

	.gpdcon_reg	= S3C2410_GPDCON,
पूर्ण;

/* ILI9320 support. */

अटल व्योम jive_lcm_reset(अचिन्हित पूर्णांक set)
अणु
	prपूर्णांकk(KERN_DEBUG "%s(%d)\n", __func__, set);

	gpio_set_value(S3C2410_GPG(13), set);
पूर्ण

#अघोषित LCD_UPPER_MARGIN
#घोषणा LCD_UPPER_MARGIN 2

अटल काष्ठा ili9320_platdata jive_lcm_config = अणु
	.hsize		= LCD_XRES,
	.vsize		= LCD_YRES,

	.reset		= jive_lcm_reset,
	.suspend	= ILI9320_SUSPEND_DEEP,

	.entry_mode	= ILI9320_ENTRYMODE_ID(3) | ILI9320_ENTRYMODE_BGR,
	.display2	= (ILI9320_DISPLAY2_FP(LCD_UPPER_MARGIN) |
			   ILI9320_DISPLAY2_BP(LCD_LOWER_MARGIN)),
	.display3	= 0x0,
	.display4	= 0x0,
	.rgb_अगर1	= (ILI9320_RGBIF1_RIM_RGB18 |
			   ILI9320_RGBIF1_RM | ILI9320_RGBIF1_CLK_RGBIF),
	.rgb_अगर2	= ILI9320_RGBIF2_DPL,
	.पूर्णांकerface2	= 0x0,
	.पूर्णांकerface3	= 0x3,
	.पूर्णांकerface4	= (ILI9320_INTERFACE4_RTNE(16) |
			   ILI9320_INTERFACE4_DIVE(1)),
	.पूर्णांकerface5	= 0x0,
	.पूर्णांकerface6	= 0x0,
पूर्ण;

/* LCD SPI support */

अटल काष्ठा spi_gpio_platक्रमm_data jive_lcd_spi = अणु
	.num_chipselect	= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device jive_device_lcdspi = अणु
	.name		= "spi_gpio",
	.id		= 1,
	.dev.platक्रमm_data = &jive_lcd_spi,
पूर्ण;

अटल काष्ठा gpiod_lookup_table jive_lcdspi_gpiod_table = अणु
	.dev_id         = "spi_gpio",
	.table          = अणु
		GPIO_LOOKUP("GPIOG", 8,
			    "sck", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("GPIOB", 8,
			    "mosi", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("GPIOB", 7,
			    "cs", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/* WM8750 audio code SPI definition */

अटल काष्ठा spi_gpio_platक्रमm_data jive_wm8750_spi = अणु
	.num_chipselect	= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device jive_device_wm8750 = अणु
	.name		= "spi_gpio",
	.id		= 2,
	.dev.platक्रमm_data = &jive_wm8750_spi,
पूर्ण;

अटल काष्ठा gpiod_lookup_table jive_wm8750_gpiod_table = अणु
	.dev_id         = "spi_gpio",
	.table          = अणु
		GPIO_LOOKUP("GPIOB", 4,
			    "sck", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("GPIOB", 9,
			    "mosi", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("GPIOH", 10,
			    "cs", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/* JIVE SPI devices. */

अटल काष्ठा spi_board_info __initdata jive_spi_devs[] = अणु
	[0] = अणु
		.modalias	= "VGG2432A4",
		.bus_num	= 1,
		.chip_select	= 0,
		.mode		= SPI_MODE_3,	/* CPOL=1, CPHA=1 */
		.max_speed_hz	= 100000,
		.platक्रमm_data	= &jive_lcm_config,
	पूर्ण, अणु
		.modalias	= "WM8750",
		.bus_num	= 2,
		.chip_select	= 0,
		.mode		= SPI_MODE_0,	/* CPOL=0, CPHA=0 */
		.max_speed_hz	= 100000,
	पूर्ण,
पूर्ण;

/* I2C bus and device configuration. */

अटल काष्ठा s3c2410_platक्रमm_i2c jive_i2c_cfg __initdata = अणु
	.frequency	= 80 * 1000,
	.flags		= S3C_IICFLG_FILTER,
	.sda_delay	= 2,
पूर्ण;

अटल काष्ठा i2c_board_info jive_i2c_devs[] __initdata = अणु
	[0] = अणु
		I2C_BOARD_INFO("lis302dl", 0x1c),
		.irq	= IRQ_EINT14,
	पूर्ण,
पूर्ण;

/* The platक्रमm devices being used. */

अटल काष्ठा platक्रमm_device *jive_devices[] __initdata = अणु
	&s3c_device_ohci,
	&s3c_device_rtc,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_lcd,
	&jive_device_lcdspi,
	&jive_device_wm8750,
	&s3c_device_nand,
	&s3c_device_usbgadget,
	&s3c2412_device_dma,
पूर्ण;

अटल काष्ठा s3c2410_udc_mach_info jive_udc_cfg __initdata = अणु
	.vbus_pin	= S3C2410_GPG(1),		/* detect is on GPG1 */
पूर्ण;

/* Jive घातer management device */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक jive_pm_suspend(व्योम)
अणु
	/* Write the magic value u-boot uses to check क्रम resume पूर्णांकo
	 * the INFORM0 रेजिस्टर, and ensure INFORM1 is set to the
	 * correct address to resume from. */

	__raw_ग_लिखोl(0x2BED, S3C2412_INFORM0);
	__raw_ग_लिखोl(__pa_symbol(s3c_cpu_resume), S3C2412_INFORM1);

	वापस 0;
पूर्ण

अटल व्योम jive_pm_resume(व्योम)
अणु
	__raw_ग_लिखोl(0x0, S3C2412_INFORM0);
पूर्ण

#अन्यथा
#घोषणा jive_pm_suspend शून्य
#घोषणा jive_pm_resume शून्य
#पूर्ण_अगर

अटल काष्ठा syscore_ops jive_pm_syscore_ops = अणु
	.suspend	= jive_pm_suspend,
	.resume		= jive_pm_resume,
पूर्ण;

अटल व्योम __init jive_map_io(व्योम)
अणु
	s3c24xx_init_io(jive_iodesc, ARRAY_SIZE(jive_iodesc));
	s3c24xx_init_uarts(jive_uartcfgs, ARRAY_SIZE(jive_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init jive_init_समय(व्योम)
अणु
	s3c2412_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम jive_घातer_off(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "powering system down...\n");

	gpio_request_one(S3C2410_GPC(5), GPIOF_OUT_INIT_HIGH, शून्य);
	gpio_मुक्त(S3C2410_GPC(5));
पूर्ण

अटल व्योम __init jive_machine_init(व्योम)
अणु
	/* रेजिस्टर प्रणाली core operations क्रम managing low level suspend */

	रेजिस्टर_syscore_ops(&jive_pm_syscore_ops);

	/* ग_लिखो our sleep configurations क्रम the IO. Pull करोwn all unused
	 * IO, ensure that we have turned off all peripherals we करो not
	 * need, and configure the ones we करो need. */

	/* Port B sleep */

	__raw_ग_लिखोl(S3C2412_SLPCON_IN(0)   |
		     S3C2412_SLPCON_PULL(1) |
		     S3C2412_SLPCON_HIGH(2) |
		     S3C2412_SLPCON_PULL(3) |
		     S3C2412_SLPCON_PULL(4) |
		     S3C2412_SLPCON_PULL(5) |
		     S3C2412_SLPCON_PULL(6) |
		     S3C2412_SLPCON_HIGH(7) |
		     S3C2412_SLPCON_PULL(8) |
		     S3C2412_SLPCON_PULL(9) |
		     S3C2412_SLPCON_PULL(10), S3C2412_GPBSLPCON);

	/* Port C sleep */

	__raw_ग_लिखोl(S3C2412_SLPCON_PULL(0) |
		     S3C2412_SLPCON_PULL(1) |
		     S3C2412_SLPCON_PULL(2) |
		     S3C2412_SLPCON_PULL(3) |
		     S3C2412_SLPCON_PULL(4) |
		     S3C2412_SLPCON_PULL(5) |
		     S3C2412_SLPCON_LOW(6)  |
		     S3C2412_SLPCON_PULL(6) |
		     S3C2412_SLPCON_PULL(7) |
		     S3C2412_SLPCON_PULL(8) |
		     S3C2412_SLPCON_PULL(9) |
		     S3C2412_SLPCON_PULL(10) |
		     S3C2412_SLPCON_PULL(11) |
		     S3C2412_SLPCON_PULL(12) |
		     S3C2412_SLPCON_PULL(13) |
		     S3C2412_SLPCON_PULL(14) |
		     S3C2412_SLPCON_PULL(15), S3C2412_GPCSLPCON);

	/* Port D sleep */

	__raw_ग_लिखोl(S3C2412_SLPCON_ALL_PULL, S3C2412_GPDSLPCON);

	/* Port F sleep */

	__raw_ग_लिखोl(S3C2412_SLPCON_LOW(0)  |
		     S3C2412_SLPCON_LOW(1)  |
		     S3C2412_SLPCON_LOW(2)  |
		     S3C2412_SLPCON_EINT(3) |
		     S3C2412_SLPCON_EINT(4) |
		     S3C2412_SLPCON_EINT(5) |
		     S3C2412_SLPCON_EINT(6) |
		     S3C2412_SLPCON_EINT(7), S3C2412_GPFSLPCON);

	/* Port G sleep */

	__raw_ग_लिखोl(S3C2412_SLPCON_IN(0)    |
		     S3C2412_SLPCON_IN(1)    |
		     S3C2412_SLPCON_IN(2)    |
		     S3C2412_SLPCON_IN(3)    |
		     S3C2412_SLPCON_IN(4)    |
		     S3C2412_SLPCON_IN(5)    |
		     S3C2412_SLPCON_IN(6)    |
		     S3C2412_SLPCON_IN(7)    |
		     S3C2412_SLPCON_PULL(8)  |
		     S3C2412_SLPCON_PULL(9)  |
		     S3C2412_SLPCON_IN(10)   |
		     S3C2412_SLPCON_PULL(11) |
		     S3C2412_SLPCON_PULL(12) |
		     S3C2412_SLPCON_PULL(13) |
		     S3C2412_SLPCON_IN(14)   |
		     S3C2412_SLPCON_PULL(15), S3C2412_GPGSLPCON);

	/* Port H sleep */

	__raw_ग_लिखोl(S3C2412_SLPCON_PULL(0) |
		     S3C2412_SLPCON_PULL(1) |
		     S3C2412_SLPCON_PULL(2) |
		     S3C2412_SLPCON_PULL(3) |
		     S3C2412_SLPCON_PULL(4) |
		     S3C2412_SLPCON_PULL(5) |
		     S3C2412_SLPCON_PULL(6) |
		     S3C2412_SLPCON_IN(7)   |
		     S3C2412_SLPCON_IN(8)   |
		     S3C2412_SLPCON_PULL(9) |
		     S3C2412_SLPCON_IN(10), S3C2412_GPHSLPCON);

	/* initialise the घातer management now we've setup everything. */

	s3c_pm_init();

	/** TODO - check that this is after the cmdline option! */
	s3c_nand_set_platdata(&jive_nand_info);

	gpio_request(S3C2410_GPG(13), "lcm reset");
	gpio_direction_output(S3C2410_GPG(13), 0);

	gpio_request_one(S3C2410_GPB(6), GPIOF_OUT_INIT_LOW, शून्य);
	gpio_मुक्त(S3C2410_GPB(6));

	/* Turn off suspend on both USB ports, and चयन the
	 * selectable USB port to USB device mode. */

	s3c2410_modअगरy_misccr(S3C2410_MISCCR_USBHOST |
			      S3C2410_MISCCR_USBSUSPND0 |
			      S3C2410_MISCCR_USBSUSPND1, 0x0);

	s3c24xx_udc_set_platdata(&jive_udc_cfg);
	s3c24xx_fb_set_platdata(&jive_lcd_config);

	spi_रेजिस्टर_board_info(jive_spi_devs, ARRAY_SIZE(jive_spi_devs));

	s3c_i2c0_set_platdata(&jive_i2c_cfg);
	i2c_रेजिस्टर_board_info(0, jive_i2c_devs, ARRAY_SIZE(jive_i2c_devs));

	pm_घातer_off = jive_घातer_off;

	gpiod_add_lookup_table(&jive_lcdspi_gpiod_table);
	gpiod_add_lookup_table(&jive_wm8750_gpiod_table);
	platक्रमm_add_devices(jive_devices, ARRAY_SIZE(jive_devices));
पूर्ण

MACHINE_START(JIVE, "JIVE")
	/* Maपूर्णांकainer: Ben Dooks <ben-linux@fluff.org> */
	.atag_offset	= 0x100,

	.init_irq	= s3c2412_init_irq,
	.map_io		= jive_map_io,
	.init_machine	= jive_machine_init,
	.init_समय	= jive_init_समय,
MACHINE_END
