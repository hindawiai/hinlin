<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2003-2009 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/sm501.h>
#समावेश <linux/sm501-regs.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <net/ax88796.h>

#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश <linux/platक्रमm_data/asoc-s3c24xx_simtec.h>

#समावेश "anubis.h"
#समावेश "s3c24xx.h"
#समावेश "simtec.h"

#घोषणा COPYRIGHT ", Copyright 2005-2009 Simtec Electronics"

अटल काष्ठा map_desc anubis_iodesc[] __initdata = अणु
  /* ISA IO areas */

  अणु
	.भव	= (u32)S3C24XX_VA_ISA_BYTE,
	.pfn		= __phys_to_pfn(0x0),
	.length		= SZ_4M,
	.type		= MT_DEVICE,
  पूर्ण, अणु
	.भव	= (u32)S3C24XX_VA_ISA_WORD,
	.pfn		= __phys_to_pfn(0x0),
	.length 	= SZ_4M,
	.type		= MT_DEVICE,
  पूर्ण,

  /* we could possibly compress the next set करोwn पूर्णांकo a set of smaller tables
   * pagetables, but that would mean using an L2 section, and it still means
   * we cannot actually feed the same रेजिस्टर to an LDR due to 16K spacing
   */

  /* CPLD control रेजिस्टरs */

  अणु
	.भव	= (u32)ANUBIS_VA_CTRL1,
	.pfn		= __phys_to_pfn(ANUBIS_PA_CTRL1),
	.length		= SZ_4K,
	.type		= MT_DEVICE,
  पूर्ण, अणु
	.भव	= (u32)ANUBIS_VA_IDREG,
	.pfn		= __phys_to_pfn(ANUBIS_PA_IDREG),
	.length		= SZ_4K,
	.type		= MT_DEVICE,
  पूर्ण,
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg anubis_uartcfgs[] __initdata = अणु
	[0] = अणु
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
		.clk_sel	= S3C2410_UCON_CLKSEL1 | S3C2410_UCON_CLKSEL2,
	पूर्ण,
	[1] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
		.clk_sel	= S3C2410_UCON_CLKSEL1 | S3C2410_UCON_CLKSEL2,
	पूर्ण,
पूर्ण;

/* न_अंकD Flash on Anubis board */

अटल पूर्णांक बाह्यal_map[]   = अणु 2 पूर्ण;
अटल पूर्णांक chip0_map[]      = अणु 0 पूर्ण;
अटल पूर्णांक chip1_map[]      = अणु 1 पूर्ण;

अटल काष्ठा mtd_partition __initdata anubis_शेष_nand_part[] = अणु
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
		.name	= "user1",
		.offset	= SZ_4M,
		.size	= SZ_32M - SZ_4M,
	पूर्ण,
	[3] = अणु
		.name	= "user2",
		.offset	= SZ_32M,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा mtd_partition __initdata anubis_शेष_nand_part_large[] = अणु
	[0] = अणु
		.name	= "Boot Agent",
		.size	= SZ_128K,
		.offset	= 0,
	पूर्ण,
	[1] = अणु
		.name	= "/boot",
		.size	= SZ_4M - SZ_128K,
		.offset	= SZ_128K,
	पूर्ण,
	[2] = अणु
		.name	= "user1",
		.offset	= SZ_4M,
		.size	= SZ_32M - SZ_4M,
	पूर्ण,
	[3] = अणु
		.name	= "user2",
		.offset	= SZ_32M,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

/* the Anubis has 3 selectable slots क्रम nand-flash, the two
 * on-board chip areas, as well as the बाह्यal slot.
 *
 * Note, there is no current hot-plug support क्रम the External
 * socket.
*/

अटल काष्ठा s3c2410_nand_set __initdata anubis_nand_sets[] = अणु
	[1] = अणु
		.name		= "External",
		.nr_chips	= 1,
		.nr_map		= बाह्यal_map,
		.nr_partitions	= ARRAY_SIZE(anubis_शेष_nand_part),
		.partitions	= anubis_शेष_nand_part,
	पूर्ण,
	[0] = अणु
		.name		= "chip0",
		.nr_chips	= 1,
		.nr_map		= chip0_map,
		.nr_partitions	= ARRAY_SIZE(anubis_शेष_nand_part),
		.partitions	= anubis_शेष_nand_part,
	पूर्ण,
	[2] = अणु
		.name		= "chip1",
		.nr_chips	= 1,
		.nr_map		= chip1_map,
		.nr_partitions	= ARRAY_SIZE(anubis_शेष_nand_part),
		.partitions	= anubis_शेष_nand_part,
	पूर्ण,
पूर्ण;

अटल व्योम anubis_nand_select(काष्ठा s3c2410_nand_set *set, पूर्णांक slot)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	slot = set->nr_map[slot] & 3;

	pr_debug("anubis_nand: selecting slot %d (set %p,%p)\n",
		 slot, set, set->nr_map);

	पंचांगp = __raw_पढ़ोb(ANUBIS_VA_CTRL1);
	पंचांगp &= ~ANUBIS_CTRL1_न_अंकDSEL;
	पंचांगp |= slot;

	pr_debug("anubis_nand: ctrl1 now %02x\n", पंचांगp);

	__raw_ग_लिखोb(पंचांगp, ANUBIS_VA_CTRL1);
पूर्ण

अटल काष्ठा s3c2410_platक्रमm_nand __initdata anubis_nand_info = अणु
	.tacls		= 25,
	.twrph0		= 55,
	.twrph1		= 40,
	.nr_sets	= ARRAY_SIZE(anubis_nand_sets),
	.sets		= anubis_nand_sets,
	.select_chip	= anubis_nand_select,
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_SOFT,
पूर्ण;

/* IDE channels */

अटल काष्ठा pata_platक्रमm_info anubis_ide_platdata = अणु
	.ioport_shअगरt	= 5,
पूर्ण;

अटल काष्ठा resource anubis_ide0_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS3, 8 * 32),
	[2] = DEFINE_RES_MEM(S3C2410_CS3 + (1 << 26) + (6 * 32), 32),
	[3] = DEFINE_RES_IRQ(ANUBIS_IRQ_IDE0),
पूर्ण;

अटल काष्ठा platक्रमm_device anubis_device_ide0 = अणु
	.name		= "pata_platform",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(anubis_ide0_resource),
	.resource	= anubis_ide0_resource,
	.dev	= अणु
		.platक्रमm_data = &anubis_ide_platdata,
		.coherent_dma_mask = ~0,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource anubis_ide1_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS4, 8 * 32),
	[1] = DEFINE_RES_MEM(S3C2410_CS4 + (1 << 26) + (6 * 32), 32),
	[2] = DEFINE_RES_IRQ(ANUBIS_IRQ_IDE0),
पूर्ण;

अटल काष्ठा platक्रमm_device anubis_device_ide1 = अणु
	.name		= "pata_platform",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(anubis_ide1_resource),
	.resource	= anubis_ide1_resource,
	.dev	= अणु
		.platक्रमm_data = &anubis_ide_platdata,
		.coherent_dma_mask = ~0,
	पूर्ण,
पूर्ण;

/* Asix AX88796 10/100 ethernet controller */

अटल काष्ठा ax_plat_data anubis_asix_platdata = अणु
	.flags		= AXFLG_MAC_FROMDEV,
	.wordlength	= 2,
	.dcr_val	= 0x48,
	.rcr_val	= 0x40,
पूर्ण;

अटल काष्ठा resource anubis_asix_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS5, 0x20 * 0x20),
	[1] = DEFINE_RES_IRQ(ANUBIS_IRQ_ASIX),
पूर्ण;

अटल काष्ठा platक्रमm_device anubis_device_asix = अणु
	.name		= "ax88796",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(anubis_asix_resource),
	.resource	= anubis_asix_resource,
	.dev		= अणु
		.platक्रमm_data = &anubis_asix_platdata,
	पूर्ण
पूर्ण;

/* SM501 */

अटल काष्ठा resource anubis_sm501_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS2, SZ_8M),
	[1] = DEFINE_RES_MEM(S3C2410_CS2 + SZ_64M - SZ_2M, SZ_2M),
	[2] = DEFINE_RES_IRQ(IRQ_EINT0),
पूर्ण;

अटल काष्ठा sm501_initdata anubis_sm501_initdata = अणु
	.gpio_high	= अणु
		.set	= 0x3F000000,		/* 24bit panel */
		.mask	= 0x0,
	पूर्ण,
	.misc_timing	= अणु
		.set	= 0x010100,		/* SDRAM timing */
		.mask	= 0x1F1F00,
	पूर्ण,
	.misc_control	= अणु
		.set	= SM501_MISC_PNL_24BIT,
		.mask	= 0,
	पूर्ण,

	.devices	= SM501_USE_GPIO,

	/* set the SDRAM and bus घड़ीs */
	.mclk		= 72 * MHZ,
	.m1xclk		= 144 * MHZ,
पूर्ण;

अटल काष्ठा sm501_platdata_gpio_i2c anubis_sm501_gpio_i2c[] = अणु
	[0] = अणु
		.bus_num	= 1,
		.pin_scl	= 44,
		.pin_sda	= 45,
	पूर्ण,
	[1] = अणु
		.bus_num	= 2,
		.pin_scl	= 40,
		.pin_sda	= 41,
	पूर्ण,
पूर्ण;

अटल काष्ठा sm501_platdata anubis_sm501_platdata = अणु
	.init		= &anubis_sm501_initdata,
	.gpio_base	= -1,
	.gpio_i2c	= anubis_sm501_gpio_i2c,
	.gpio_i2c_nr	= ARRAY_SIZE(anubis_sm501_gpio_i2c),
पूर्ण;

अटल काष्ठा platक्रमm_device anubis_device_sm501 = अणु
	.name		= "sm501",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(anubis_sm501_resource),
	.resource	= anubis_sm501_resource,
	.dev		= अणु
		.platक्रमm_data = &anubis_sm501_platdata,
	पूर्ण,
पूर्ण;

/* Standard Anubis devices */

अटल काष्ठा platक्रमm_device *anubis_devices[] __initdata = अणु
	&s3c2410_device_dclk,
	&s3c_device_ohci,
	&s3c_device_wdt,
	&s3c_device_adc,
	&s3c_device_i2c0,
 	&s3c_device_rtc,
	&s3c_device_nand,
	&anubis_device_ide0,
	&anubis_device_ide1,
	&anubis_device_asix,
	&anubis_device_sm501,
पूर्ण;

/* I2C devices. */

अटल काष्ठा i2c_board_info anubis_i2c_devs[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("tps65011", 0x48),
		.irq	= IRQ_EINT20,
	पूर्ण
पूर्ण;

/* Audio setup */
अटल काष्ठा s3c24xx_audio_simtec_pdata __initdata anubis_audio = अणु
	.have_mic	= 1,
	.have_lout	= 1,
	.output_cdclk	= 1,
	.use_mpllin	= 1,
	.amp_gpio	= S3C2410_GPB(2),
	.amp_gain[0]	= S3C2410_GPD(10),
	.amp_gain[1]	= S3C2410_GPD(11),
पूर्ण;

अटल व्योम __init anubis_map_io(व्योम)
अणु
	s3c24xx_init_io(anubis_iodesc, ARRAY_SIZE(anubis_iodesc));
	s3c24xx_init_uarts(anubis_uartcfgs, ARRAY_SIZE(anubis_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);

	/* check क्रम the newer revision boards with large page nand */

	अगर ((__raw_पढ़ोb(ANUBIS_VA_IDREG) & ANUBIS_IDREG_REVMASK) >= 4) अणु
		prपूर्णांकk(KERN_INFO "ANUBIS-B detected (revision %d)\n",
		       __raw_पढ़ोb(ANUBIS_VA_IDREG) & ANUBIS_IDREG_REVMASK);
		anubis_nand_sets[0].partitions = anubis_शेष_nand_part_large;
		anubis_nand_sets[0].nr_partitions = ARRAY_SIZE(anubis_शेष_nand_part_large);
	पूर्ण अन्यथा अणु
		/* ensure that the GPIO is setup */
		gpio_request_one(S3C2410_GPA(0), GPIOF_OUT_INIT_HIGH, शून्य);
		gpio_मुक्त(S3C2410_GPA(0));
	पूर्ण
पूर्ण

अटल व्योम __init anubis_init_समय(व्योम)
अणु
	s3c2440_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init anubis_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);
	s3c_nand_set_platdata(&anubis_nand_info);
	simtec_audio_add(शून्य, false, &anubis_audio);

	platक्रमm_add_devices(anubis_devices, ARRAY_SIZE(anubis_devices));

	i2c_रेजिस्टर_board_info(0, anubis_i2c_devs,
				ARRAY_SIZE(anubis_i2c_devs));
पूर्ण


MACHINE_START(ANUBIS, "Simtec-Anubis")
	/* Maपूर्णांकainer: Ben Dooks <ben@simtec.co.uk> */
	.atag_offset	= 0x100,
	.map_io		= anubis_map_io,
	.init_machine	= anubis_init,
	.init_irq	= s3c2440_init_irq,
	.init_समय	= anubis_init_समय,
MACHINE_END
