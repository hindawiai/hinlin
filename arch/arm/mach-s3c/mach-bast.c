<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2003-2008 Simtec Electronics
//   Ben Dooks <ben@simtec.co.uk>
//
// http://www.simtec.co.uk/products/EB2410ITX/

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/serial_8250.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <linux/platक्रमm_data/asoc-s3c24xx_simtec.h>
#समावेश <linux/platक्रमm_data/hwmon-s3c.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>

#समावेश <net/ax88796.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <linux/platक्रमm_data/fb-s3c2410.h>
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

#समावेश "cpu.h"
#समावेश <linux/soc/samsung/s3c-cpu-freq.h>
#समावेश "devs.h"
#समावेश "gpio-cfg.h"

#समावेश "bast.h"
#समावेश "s3c24xx.h"
#समावेश "simtec.h"

#घोषणा COPYRIGHT ", Copyright 2004-2008 Simtec Electronics"

/* macros क्रम भव address mods क्रम the io space entries */
#घोषणा VA_C5(item) ((अचिन्हित दीर्घ)(item) + BAST_VAM_CS5)
#घोषणा VA_C4(item) ((अचिन्हित दीर्घ)(item) + BAST_VAM_CS4)
#घोषणा VA_C3(item) ((अचिन्हित दीर्घ)(item) + BAST_VAM_CS3)
#घोषणा VA_C2(item) ((अचिन्हित दीर्घ)(item) + BAST_VAM_CS2)

/* macros to modअगरy the physical addresses क्रम io space */

#घोषणा PA_CS2(item) (__phys_to_pfn((item) + S3C2410_CS2))
#घोषणा PA_CS3(item) (__phys_to_pfn((item) + S3C2410_CS3))
#घोषणा PA_CS4(item) (__phys_to_pfn((item) + S3C2410_CS4))
#घोषणा PA_CS5(item) (__phys_to_pfn((item) + S3C2410_CS5))

अटल काष्ठा map_desc bast_iodesc[] __initdata = अणु
  /* ISA IO areas */
  अणु
	  .भव	= (u32)S3C24XX_VA_ISA_BYTE,
	  .pfn		= PA_CS2(BAST_PA_ISAIO),
	  .length	= SZ_16M,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)S3C24XX_VA_ISA_WORD,
	  .pfn		= PA_CS3(BAST_PA_ISAIO),
	  .length	= SZ_16M,
	  .type		= MT_DEVICE,
  पूर्ण,
  /* bast CPLD control रेजिस्टरs, and बाह्यal पूर्णांकerrupt controls */
  अणु
	  .भव	= (u32)BAST_VA_CTRL1,
	  .pfn		= __phys_to_pfn(BAST_PA_CTRL1),
	  .length	= SZ_1M,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)BAST_VA_CTRL2,
	  .pfn		= __phys_to_pfn(BAST_PA_CTRL2),
	  .length	= SZ_1M,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)BAST_VA_CTRL3,
	  .pfn		= __phys_to_pfn(BAST_PA_CTRL3),
	  .length	= SZ_1M,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)BAST_VA_CTRL4,
	  .pfn		= __phys_to_pfn(BAST_PA_CTRL4),
	  .length	= SZ_1M,
	  .type		= MT_DEVICE,
  पूर्ण,
  /* PC104 IRQ mux */
  अणु
	  .भव	= (u32)BAST_VA_PC104_IRQREQ,
	  .pfn		= __phys_to_pfn(BAST_PA_PC104_IRQREQ),
	  .length	= SZ_1M,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)BAST_VA_PC104_IRQRAW,
	  .pfn		= __phys_to_pfn(BAST_PA_PC104_IRQRAW),
	  .length	= SZ_1M,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)BAST_VA_PC104_IRQMASK,
	  .pfn		= __phys_to_pfn(BAST_PA_PC104_IRQMASK),
	  .length	= SZ_1M,
	  .type		= MT_DEVICE,
  पूर्ण,

  /* peripheral space... one क्रम each of fast/slow/byte/16bit */
  /* note, ide is only decoded in word space, even though some रेजिस्टरs
   * are only 8bit */

  /* slow, byte */
  अणु VA_C2(BAST_VA_ISAIO),   PA_CS2(BAST_PA_ISAIO),    SZ_16M, MT_DEVICE पूर्ण,
  अणु VA_C2(BAST_VA_ISAMEM),  PA_CS2(BAST_PA_ISAMEM),   SZ_16M, MT_DEVICE पूर्ण,
  अणु VA_C2(BAST_VA_SUPERIO), PA_CS2(BAST_PA_SUPERIO),  SZ_1M,  MT_DEVICE पूर्ण,

  /* slow, word */
  अणु VA_C3(BAST_VA_ISAIO),   PA_CS3(BAST_PA_ISAIO),    SZ_16M, MT_DEVICE पूर्ण,
  अणु VA_C3(BAST_VA_ISAMEM),  PA_CS3(BAST_PA_ISAMEM),   SZ_16M, MT_DEVICE पूर्ण,
  अणु VA_C3(BAST_VA_SUPERIO), PA_CS3(BAST_PA_SUPERIO),  SZ_1M,  MT_DEVICE पूर्ण,

  /* fast, byte */
  अणु VA_C4(BAST_VA_ISAIO),   PA_CS4(BAST_PA_ISAIO),    SZ_16M, MT_DEVICE पूर्ण,
  अणु VA_C4(BAST_VA_ISAMEM),  PA_CS4(BAST_PA_ISAMEM),   SZ_16M, MT_DEVICE पूर्ण,
  अणु VA_C4(BAST_VA_SUPERIO), PA_CS4(BAST_PA_SUPERIO),  SZ_1M,  MT_DEVICE पूर्ण,

  /* fast, word */
  अणु VA_C5(BAST_VA_ISAIO),   PA_CS5(BAST_PA_ISAIO),    SZ_16M, MT_DEVICE पूर्ण,
  अणु VA_C5(BAST_VA_ISAMEM),  PA_CS5(BAST_PA_ISAMEM),   SZ_16M, MT_DEVICE पूर्ण,
  अणु VA_C5(BAST_VA_SUPERIO), PA_CS5(BAST_PA_SUPERIO),  SZ_1M,  MT_DEVICE पूर्ण,
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg bast_uartcfgs[] __initdata = अणु
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
	/* port 2 is not actually used */
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण
पूर्ण;

/* न_अंकD Flash on BAST board */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bast_pm_suspend(व्योम)
अणु
	/* ensure that an nRESET is not generated on resume. */
	gpio_direction_output(S3C2410_GPA(21), 1);
	वापस 0;
पूर्ण

अटल व्योम bast_pm_resume(व्योम)
अणु
	s3c_gpio_cfgpin(S3C2410_GPA(21), S3C2410_GPA21_nRSTOUT);
पूर्ण

#अन्यथा
#घोषणा bast_pm_suspend शून्य
#घोषणा bast_pm_resume शून्य
#पूर्ण_अगर

अटल काष्ठा syscore_ops bast_pm_syscore_ops = अणु
	.suspend	= bast_pm_suspend,
	.resume		= bast_pm_resume,
पूर्ण;

अटल पूर्णांक smarपंचांगedia_map[] = अणु 0 पूर्ण;
अटल पूर्णांक chip0_map[] = अणु 1 पूर्ण;
अटल पूर्णांक chip1_map[] = अणु 2 पूर्ण;
अटल पूर्णांक chip2_map[] = अणु 3 पूर्ण;

अटल काष्ठा mtd_partition __initdata bast_शेष_nand_part[] = अणु
	[0] = अणु
		.name	= "Boot Agent",
		.size	= SZ_16K,
		.offset	= 0,
	पूर्ण,
	[1] = अणु
		.name	= "/boot",
		.size	= SZ_4M - SZ_16K,
		.offset	= SZ_16K,
	पूर्ण,
	[2] = अणु
		.name	= "user",
		.offset	= SZ_4M,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

/* the bast has 4 selectable slots क्रम nand-flash, the three
 * on-board chip areas, as well as the बाह्यal SmartMedia
 * slot.
 *
 * Note, there is no current hot-plug support क्रम the SmartMedia
 * socket.
*/

अटल काष्ठा s3c2410_nand_set __initdata bast_nand_sets[] = अणु
	[0] = अणु
		.name		= "SmartMedia",
		.nr_chips	= 1,
		.nr_map		= smarपंचांगedia_map,
		.options        = न_अंकD_SCAN_SILENT_NODEV,
		.nr_partitions	= ARRAY_SIZE(bast_शेष_nand_part),
		.partitions	= bast_शेष_nand_part,
	पूर्ण,
	[1] = अणु
		.name		= "chip0",
		.nr_chips	= 1,
		.nr_map		= chip0_map,
		.nr_partitions	= ARRAY_SIZE(bast_शेष_nand_part),
		.partitions	= bast_शेष_nand_part,
	पूर्ण,
	[2] = अणु
		.name		= "chip1",
		.nr_chips	= 1,
		.nr_map		= chip1_map,
		.options        = न_अंकD_SCAN_SILENT_NODEV,
		.nr_partitions	= ARRAY_SIZE(bast_शेष_nand_part),
		.partitions	= bast_शेष_nand_part,
	पूर्ण,
	[3] = अणु
		.name		= "chip2",
		.nr_chips	= 1,
		.nr_map		= chip2_map,
		.options        = न_अंकD_SCAN_SILENT_NODEV,
		.nr_partitions	= ARRAY_SIZE(bast_शेष_nand_part),
		.partitions	= bast_शेष_nand_part,
	पूर्ण
पूर्ण;

अटल व्योम bast_nand_select(काष्ठा s3c2410_nand_set *set, पूर्णांक slot)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	slot = set->nr_map[slot] & 3;

	pr_debug("bast_nand: selecting slot %d (set %p,%p)\n",
		 slot, set, set->nr_map);

	पंचांगp = __raw_पढ़ोb(BAST_VA_CTRL2);
	पंचांगp &= BAST_CPLD_CTLR2_IDERST;
	पंचांगp |= slot;
	पंचांगp |= BAST_CPLD_CTRL2_Wन_अंकD;

	pr_debug("bast_nand: ctrl2 now %02x\n", पंचांगp);

	__raw_ग_लिखोb(पंचांगp, BAST_VA_CTRL2);
पूर्ण

अटल काष्ठा s3c2410_platक्रमm_nand __initdata bast_nand_info = अणु
	.tacls		= 30,
	.twrph0		= 60,
	.twrph1		= 60,
	.nr_sets	= ARRAY_SIZE(bast_nand_sets),
	.sets		= bast_nand_sets,
	.select_chip	= bast_nand_select,
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_SOFT,
पूर्ण;

/* DM9000 */

अटल काष्ठा resource bast_dm9k_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS5 + BAST_PA_DM9000, 4),
	[1] = DEFINE_RES_MEM(S3C2410_CS5 + BAST_PA_DM9000 + 0x40, 0x40),
	[2] = DEFINE_RES_NAMED(BAST_IRQ_DM9000 , 1, शून्य, IORESOURCE_IRQ \
					| IORESOURCE_IRQ_HIGHLEVEL),
पूर्ण;

/* क्रम the moment we limit ourselves to 16bit IO until some
 * better IO routines can be written and tested
*/

अटल काष्ठा dm9000_plat_data bast_dm9k_platdata = अणु
	.flags		= DM9000_PLATF_16BITONLY,
पूर्ण;

अटल काष्ठा platक्रमm_device bast_device_dm9k = अणु
	.name		= "dm9000",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(bast_dm9k_resource),
	.resource	= bast_dm9k_resource,
	.dev		= अणु
		.platक्रमm_data = &bast_dm9k_platdata,
	पूर्ण
पूर्ण;

/* serial devices */

#घोषणा SERIAL_BASE  (S3C2410_CS2 + BAST_PA_SUPERIO)
#घोषणा SERIAL_FLAGS (UPF_BOOT_AUTOCONF | UPF_IOREMAP | UPF_SHARE_IRQ)
#घोषणा SERIAL_CLK   (1843200)

अटल काष्ठा plat_serial8250_port bast_sio_data[] = अणु
	[0] = अणु
		.mapbase	= SERIAL_BASE + 0x2f8,
		.irq		= BAST_IRQ_PCSERIAL1,
		.flags		= SERIAL_FLAGS,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 0,
		.uartclk	= SERIAL_CLK,
	पूर्ण,
	[1] = अणु
		.mapbase	= SERIAL_BASE + 0x3f8,
		.irq		= BAST_IRQ_PCSERIAL2,
		.flags		= SERIAL_FLAGS,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 0,
		.uartclk	= SERIAL_CLK,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device bast_sio = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= &bast_sio_data,
	पूर्ण,
पूर्ण;

/* we have devices on the bus which cannot work much over the
 * standard 100KHz i2c bus frequency
*/

अटल काष्ठा s3c2410_platक्रमm_i2c __initdata bast_i2c_info = अणु
	.flags		= 0,
	.slave_addr	= 0x10,
	.frequency	= 100*1000,
पूर्ण;

/* Asix AX88796 10/100 ethernet controller */

अटल काष्ठा ax_plat_data bast_asix_platdata = अणु
	.flags		= AXFLG_MAC_FROMDEV,
	.wordlength	= 2,
	.dcr_val	= 0x48,
	.rcr_val	= 0x40,
पूर्ण;

अटल काष्ठा resource bast_asix_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS5 + BAST_PA_ASIXNET, 0x18 * 0x20),
	[1] = DEFINE_RES_MEM(S3C2410_CS5 + BAST_PA_ASIXNET + (0x1f * 0x20), 1),
	[2] = DEFINE_RES_IRQ(BAST_IRQ_ASIX),
पूर्ण;

अटल काष्ठा platक्रमm_device bast_device_asix = अणु
	.name		= "ax88796",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(bast_asix_resource),
	.resource	= bast_asix_resource,
	.dev		= अणु
		.platक्रमm_data = &bast_asix_platdata
	पूर्ण
पूर्ण;

/* Asix AX88796 10/100 ethernet controller parallel port */

अटल काष्ठा resource bast_asixpp_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS5 + BAST_PA_ASIXNET + (0x18 * 0x20), \
					0x30 * 0x20),
पूर्ण;

अटल काष्ठा platक्रमm_device bast_device_axpp = अणु
	.name		= "ax88796-pp",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(bast_asixpp_resource),
	.resource	= bast_asixpp_resource,
पूर्ण;

/* LCD/VGA controller */

अटल काष्ठा s3c2410fb_display __initdata bast_lcd_info[] = अणु
	अणु
		.type		= S3C2410_LCDCON1_TFT,
		.width		= 640,
		.height		= 480,

		.pixघड़ी	= 33333,
		.xres		= 640,
		.yres		= 480,
		.bpp		= 4,
		.left_margin	= 40,
		.right_margin	= 20,
		.hsync_len	= 88,
		.upper_margin	= 30,
		.lower_margin	= 32,
		.vsync_len	= 3,

		.lcdcon5	= 0x00014b02,
	पूर्ण,
	अणु
		.type		= S3C2410_LCDCON1_TFT,
		.width		= 640,
		.height		= 480,

		.pixघड़ी	= 33333,
		.xres		= 640,
		.yres		= 480,
		.bpp		= 8,
		.left_margin	= 40,
		.right_margin	= 20,
		.hsync_len	= 88,
		.upper_margin	= 30,
		.lower_margin	= 32,
		.vsync_len	= 3,

		.lcdcon5	= 0x00014b02,
	पूर्ण,
	अणु
		.type		= S3C2410_LCDCON1_TFT,
		.width		= 640,
		.height		= 480,

		.pixघड़ी	= 33333,
		.xres		= 640,
		.yres		= 480,
		.bpp		= 16,
		.left_margin	= 40,
		.right_margin	= 20,
		.hsync_len	= 88,
		.upper_margin	= 30,
		.lower_margin	= 32,
		.vsync_len	= 3,

		.lcdcon5	= 0x00014b02,
	पूर्ण,
पूर्ण;

/* LCD/VGA controller */

अटल काष्ठा s3c2410fb_mach_info __initdata bast_fb_info = अणु

	.displays = bast_lcd_info,
	.num_displays = ARRAY_SIZE(bast_lcd_info),
	.शेष_display = 1,
पूर्ण;

/* I2C devices fitted. */

अटल काष्ठा i2c_board_info bast_i2c_devs[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("tlv320aic23", 0x1a),
	पूर्ण, अणु
		I2C_BOARD_INFO("simtec-pmu", 0x6b),
	पूर्ण, अणु
		I2C_BOARD_INFO("ch7013", 0x75),
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c_hwmon_pdata bast_hwmon_info = अणु
	/* LCD contrast (0-6.6V) */
	.in[0] = &(काष्ठा s3c_hwmon_chcfg) अणु
		.name		= "lcd-contrast",
		.mult		= 3300,
		.भाग		= 512,
	पूर्ण,
	/* LED current feedback */
	.in[1] = &(काष्ठा s3c_hwmon_chcfg) अणु
		.name		= "led-feedback",
		.mult		= 3300,
		.भाग		= 1024,
	पूर्ण,
	/* LCD feedback (0-6.6V) */
	.in[2] = &(काष्ठा s3c_hwmon_chcfg) अणु
		.name		= "lcd-feedback",
		.mult		= 3300,
		.भाग		= 512,
	पूर्ण,
	/* Vcore (1.8-2.0V), Vref 3.3V  */
	.in[3] = &(काष्ठा s3c_hwmon_chcfg) अणु
		.name		= "vcore",
		.mult		= 3300,
		.भाग		= 1024,
	पूर्ण,
पूर्ण;

/* Standard BAST devices */
// cat /sys/devices/platक्रमm/s3c24xx-adc/s3c-hwmon/in_0

अटल काष्ठा platक्रमm_device *bast_devices[] __initdata = अणु
	&s3c2410_device_dclk,
	&s3c_device_ohci,
	&s3c_device_lcd,
	&s3c_device_wdt,
	&s3c_device_i2c0,
 	&s3c_device_rtc,
	&s3c_device_nand,
	&s3c_device_adc,
	&s3c_device_hwmon,
	&bast_device_dm9k,
	&bast_device_asix,
	&bast_device_axpp,
	&bast_sio,
पूर्ण;

अटल काष्ठा s3c_cpufreq_board __initdata bast_cpufreq = अणु
	.refresh	= 7800, /* 7.8usec */
	.स्वतः_io	= 1,
	.need_io	= 1,
पूर्ण;

अटल काष्ठा s3c24xx_audio_simtec_pdata __initdata bast_audio = अणु
	.have_mic	= 1,
	.have_lout	= 1,
पूर्ण;

अटल व्योम __init bast_map_io(व्योम)
अणु
	s3c_hwmon_set_platdata(&bast_hwmon_info);

	s3c24xx_init_io(bast_iodesc, ARRAY_SIZE(bast_iodesc));
	s3c24xx_init_uarts(bast_uartcfgs, ARRAY_SIZE(bast_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init bast_init_समय(व्योम)
अणु
	s3c2410_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init bast_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&bast_pm_syscore_ops);

	s3c_i2c0_set_platdata(&bast_i2c_info);
	s3c_nand_set_platdata(&bast_nand_info);
	s3c24xx_fb_set_platdata(&bast_fb_info);
	platक्रमm_add_devices(bast_devices, ARRAY_SIZE(bast_devices));

	i2c_रेजिस्टर_board_info(0, bast_i2c_devs,
				ARRAY_SIZE(bast_i2c_devs));

	usb_simtec_init();
	nor_simtec_init();
	simtec_audio_add(शून्य, true, &bast_audio);

	WARN_ON(gpio_request(S3C2410_GPA(21), "bast nreset"));
	
	s3c_cpufreq_setboard(&bast_cpufreq);
पूर्ण

MACHINE_START(BAST, "Simtec-BAST")
	/* Maपूर्णांकainer: Ben Dooks <ben@simtec.co.uk> */
	.atag_offset	= 0x100,
	.map_io		= bast_map_io,
	.init_irq	= s3c2410_init_irq,
	.init_machine	= bast_init,
	.init_समय	= bast_init_समय,
MACHINE_END
