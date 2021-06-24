<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2010 Darius Augulis <augulis.darius@gmail.com>
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "map.h"
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश <mach/irqs.h>

#समावेश <linux/soc/samsung/s3c-adc.h>
#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश "fb.h"
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>
#समावेश <linux/platक्रमm_data/touchscreen-s3c2410.h>

#समावेश <video/platक्रमm_lcd.h>
#समावेश <video/samsung_fimd.h>

#समावेश "s3c64xx.h"
#समावेश "regs-modem-s3c64xx.h"
#समावेश "regs-srom-s3c64xx.h"

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON (S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB)
#घोषणा UFCON (S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE)

अटल काष्ठा s3c2410_uartcfg real6410_uartcfgs[] __initdata = अणु
	[0] = अणु
		.hwport	= 0,
		.flags	= 0,
		.ucon	= UCON,
		.ulcon	= ULCON,
		.ufcon	= UFCON,
	पूर्ण,
	[1] = अणु
		.hwport	= 1,
		.flags	= 0,
		.ucon	= UCON,
		.ulcon	= ULCON,
		.ufcon	= UFCON,
	पूर्ण,
	[2] = अणु
		.hwport	= 2,
		.flags	= 0,
		.ucon	= UCON,
		.ulcon	= ULCON,
		.ufcon	= UFCON,
	पूर्ण,
	[3] = अणु
		.hwport	= 3,
		.flags	= 0,
		.ucon	= UCON,
		.ulcon	= ULCON,
		.ufcon	= UFCON,
	पूर्ण,
पूर्ण;

/* DM9000AEP 10/100 ethernet controller */

अटल काष्ठा resource real6410_dm9k_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C64XX_PA_XM0CSN1, 2),
	[1] = DEFINE_RES_MEM(S3C64XX_PA_XM0CSN1 + 4, 2),
	[2] = DEFINE_RES_NAMED(S3C_EINT(7), 1, शून्य, IORESOURCE_IRQ \
					| IORESOURCE_IRQ_HIGHLEVEL),
पूर्ण;

अटल काष्ठा dm9000_plat_data real6410_dm9k_pdata = अणु
	.flags		= (DM9000_PLATF_16BITONLY | DM9000_PLATF_NO_EEPROM),
पूर्ण;

अटल काष्ठा platक्रमm_device real6410_device_eth = अणु
	.name		= "dm9000",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(real6410_dm9k_resource),
	.resource	= real6410_dm9k_resource,
	.dev		= अणु
		.platक्रमm_data	= &real6410_dm9k_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c_fb_pd_win real6410_lcd_type0_fb_win = अणु
	.max_bpp	= 32,
	.शेष_bpp	= 16,
	.xres		= 480,
	.yres		= 272,
पूर्ण;

अटल काष्ठा fb_videomode real6410_lcd_type0_timing = अणु
	/* 4.3" 480x272 */
	.left_margin	= 3,
	.right_margin	= 2,
	.upper_margin	= 1,
	.lower_margin	= 1,
	.hsync_len	= 40,
	.vsync_len	= 1,
पूर्ण;

अटल काष्ठा s3c_fb_pd_win real6410_lcd_type1_fb_win = अणु
	.max_bpp	= 32,
	.शेष_bpp	= 16,
	.xres		= 800,
	.yres		= 480,
पूर्ण;

अटल काष्ठा fb_videomode real6410_lcd_type1_timing = अणु
	/* 7.0" 800x480 */
	.left_margin	= 8,
	.right_margin	= 13,
	.upper_margin	= 7,
	.lower_margin	= 5,
	.hsync_len	= 3,
	.vsync_len	= 1,
	.xres		= 800,
	.yres		= 480,
पूर्ण;

अटल काष्ठा s3c_fb_platdata real6410_lcd_pdata[] __initdata = अणु
	अणु
		.setup_gpio	= s3c64xx_fb_gpio_setup_24bpp,
		.vtiming	= &real6410_lcd_type0_timing,
		.win[0]		= &real6410_lcd_type0_fb_win,
		.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
		.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
	पूर्ण, अणु
		.setup_gpio	= s3c64xx_fb_gpio_setup_24bpp,
		.vtiming	= &real6410_lcd_type1_timing,
		.win[0]		= &real6410_lcd_type1_fb_win,
		.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
		.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition real6410_nand_part[] = अणु
	[0] = अणु
		.name	= "uboot",
		.size	= SZ_1M,
		.offset	= 0,
	पूर्ण,
	[1] = अणु
		.name	= "kernel",
		.size	= SZ_2M,
		.offset	= SZ_1M,
	पूर्ण,
	[2] = अणु
		.name	= "rootfs",
		.size	= MTDPART_SIZ_FULL,
		.offset	= SZ_1M + SZ_2M,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_nand_set real6410_nand_sets[] = अणु
	[0] = अणु
		.name		= "nand",
		.nr_chips	= 1,
		.nr_partitions	= ARRAY_SIZE(real6410_nand_part),
		.partitions	= real6410_nand_part,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_platक्रमm_nand real6410_nand_info = अणु
	.tacls		= 25,
	.twrph0		= 55,
	.twrph1		= 40,
	.nr_sets	= ARRAY_SIZE(real6410_nand_sets),
	.sets		= real6410_nand_sets,
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_SOFT,
पूर्ण;

अटल काष्ठा platक्रमm_device *real6410_devices[] __initdata = अणु
	&real6410_device_eth,
	&s3c_device_hsmmc0,
	&s3c_device_hsmmc1,
	&s3c_device_fb,
	&s3c_device_nand,
	&s3c_device_adc,
	&s3c_device_ohci,
पूर्ण;

अटल व्योम __init real6410_map_io(व्योम)
अणु
	u32 पंचांगp;

	s3c64xx_init_io(शून्य, 0);
	s3c24xx_init_घड़ीs(12000000);
	s3c24xx_init_uarts(real6410_uartcfgs, ARRAY_SIZE(real6410_uartcfgs));
	s3c64xx_set_समयr_source(S3C64XX_PWM3, S3C64XX_PWM4);

	/* set the LCD type */
	पंचांगp = __raw_पढ़ोl(S3C64XX_SPCON);
	पंचांगp &= ~S3C64XX_SPCON_LCD_SEL_MASK;
	पंचांगp |= S3C64XX_SPCON_LCD_SEL_RGB;
	__raw_ग_लिखोl(पंचांगp, S3C64XX_SPCON);

	/* हटाओ the LCD bypass */
	पंचांगp = __raw_पढ़ोl(S3C64XX_MODEM_MIFPCON);
	पंचांगp &= ~MIFPCON_LCD_BYPASS;
	__raw_ग_लिखोl(पंचांगp, S3C64XX_MODEM_MIFPCON);
पूर्ण

/*
 * real6410_features string
 *
 * 0-9 LCD configuration
 *
 */
अटल अक्षर real6410_features_str[12] __initdata = "0";

अटल पूर्णांक __init real6410_features_setup(अक्षर *str)
अणु
	अगर (str)
		strlcpy(real6410_features_str, str,
			माप(real6410_features_str));
	वापस 1;
पूर्ण

__setup("real6410=", real6410_features_setup);

#घोषणा FEATURE_SCREEN (1 << 0)

काष्ठा real6410_features_t अणु
	पूर्णांक करोne;
	पूर्णांक lcd_index;
पूर्ण;

अटल व्योम real6410_parse_features(
		काष्ठा real6410_features_t *features,
		स्थिर अक्षर *features_str)
अणु
	स्थिर अक्षर *fp = features_str;

	features->करोne = 0;
	features->lcd_index = 0;

	जबतक (*fp) अणु
		अक्षर f = *fp++;

		चयन (f) अणु
		हाल '0'...'9':	/* tft screen */
			अगर (features->करोne & FEATURE_SCREEN) अणु
				prपूर्णांकk(KERN_INFO "REAL6410: '%c' ignored, "
					"screen type already set\n", f);
			पूर्ण अन्यथा अणु
				पूर्णांक li = f - '0';
				अगर (li >= ARRAY_SIZE(real6410_lcd_pdata))
					prपूर्णांकk(KERN_INFO "REAL6410: '%c' out "
						"of range LCD mode\n", f);
				अन्यथा अणु
					features->lcd_index = li;
				पूर्ण
			पूर्ण
			features->करोne |= FEATURE_SCREEN;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init real6410_machine_init(व्योम)
अणु
	u32 cs1;
	काष्ठा real6410_features_t features = अणु 0 पूर्ण;

	prपूर्णांकk(KERN_INFO "REAL6410: Option string real6410=%s\n",
			real6410_features_str);

	/* Parse the feature string */
	real6410_parse_features(&features, real6410_features_str);

	prपूर्णांकk(KERN_INFO "REAL6410: selected LCD display is %dx%d\n",
		real6410_lcd_pdata[features.lcd_index].win[0]->xres,
		real6410_lcd_pdata[features.lcd_index].win[0]->yres);

	s3c_fb_set_platdata(&real6410_lcd_pdata[features.lcd_index]);
	s3c_nand_set_platdata(&real6410_nand_info);
	s3c64xx_ts_set_platdata(शून्य);

	/* configure nCS1 width to 16 bits */

	cs1 = __raw_पढ़ोl(S3C64XX_SROM_BW) &
		~(S3C64XX_SROM_BW__CS_MASK << S3C64XX_SROM_BW__NCS1__SHIFT);
	cs1 |= ((1 << S3C64XX_SROM_BW__DATAWIDTH__SHIFT) |
		(1 << S3C64XX_SROM_BW__WAITENABLE__SHIFT) |
		(1 << S3C64XX_SROM_BW__BYTEENABLE__SHIFT)) <<
			S3C64XX_SROM_BW__NCS1__SHIFT;
	__raw_ग_लिखोl(cs1, S3C64XX_SROM_BW);

	/* set timing क्रम nCS1 suitable क्रम ethernet chip */

	__raw_ग_लिखोl((0 << S3C64XX_SROM_BCX__PMC__SHIFT) |
		(6 << S3C64XX_SROM_BCX__TACP__SHIFT) |
		(4 << S3C64XX_SROM_BCX__TCAH__SHIFT) |
		(1 << S3C64XX_SROM_BCX__TCOH__SHIFT) |
		(13 << S3C64XX_SROM_BCX__TACC__SHIFT) |
		(4 << S3C64XX_SROM_BCX__TCOS__SHIFT) |
		(0 << S3C64XX_SROM_BCX__TACS__SHIFT), S3C64XX_SROM_BC1);

	gpio_request(S3C64XX_GPF(15), "LCD power");

	platक्रमm_add_devices(real6410_devices, ARRAY_SIZE(real6410_devices));
पूर्ण

MACHINE_START(REAL6410, "REAL6410")
	/* Maपूर्णांकainer: Darius Augulis <augulis.darius@gmail.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= S3C64XX_NR_IRQS,
	.init_irq	= s3c6410_init_irq,
	.map_io		= real6410_map_io,
	.init_machine	= real6410_machine_init,
	.init_समय	= s3c64xx_समयr_init,
MACHINE_END
