<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2005-2008 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/tps65010.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/irq.h>

#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/partitions.h>

#समावेश "cpu.h"
#समावेश <linux/soc/samsung/s3c-cpu-freq.h>
#समावेश "devs.h"
#समावेश "gpio-cfg.h"

#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

#समावेश "s3c24xx.h"
#समावेश "osiris.h"
#समावेश "regs-mem-s3c24xx.h"

/* onboard perihperal map */

अटल काष्ठा map_desc osiris_iodesc[] __initdata = अणु
  /* ISA IO areas (may be over-written later) */

  अणु
	  .भव	= (u32)S3C24XX_VA_ISA_BYTE,
	  .pfn		= __phys_to_pfn(S3C2410_CS5),
	  .length	= SZ_16M,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)S3C24XX_VA_ISA_WORD,
	  .pfn		= __phys_to_pfn(S3C2410_CS5),
	  .length	= SZ_16M,
	  .type		= MT_DEVICE,
  पूर्ण,

  /* CPLD control रेजिस्टरs */

  अणु
	  .भव	= (u32)OSIRIS_VA_CTRL0,
	  .pfn		= __phys_to_pfn(OSIRIS_PA_CTRL0),
	  .length	= SZ_16K,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)OSIRIS_VA_CTRL1,
	  .pfn		= __phys_to_pfn(OSIRIS_PA_CTRL1),
	  .length	= SZ_16K,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)OSIRIS_VA_CTRL2,
	  .pfn		= __phys_to_pfn(OSIRIS_PA_CTRL2),
	  .length	= SZ_16K,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)OSIRIS_VA_IDREG,
	  .pfn		= __phys_to_pfn(OSIRIS_PA_IDREG),
	  .length	= SZ_16K,
	  .type		= MT_DEVICE,
  पूर्ण,
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg osiris_uartcfgs[] __initdata = अणु
	[0] = अणु
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
		.clk_sel	= S3C2410_UCON_CLKSEL1 | S3C2410_UCON_CLKSEL2,
	पूर्ण,
	[1] = अणु
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
		.clk_sel	= S3C2410_UCON_CLKSEL1 | S3C2410_UCON_CLKSEL2,
	पूर्ण,
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
		.clk_sel	= S3C2410_UCON_CLKSEL1 | S3C2410_UCON_CLKSEL2,
	पूर्ण
पूर्ण;

/* न_अंकD Flash on Osiris board */

अटल पूर्णांक बाह्यal_map[]   = अणु 2 पूर्ण;
अटल पूर्णांक chip0_map[]      = अणु 0 पूर्ण;
अटल पूर्णांक chip1_map[]      = अणु 1 पूर्ण;

अटल काष्ठा mtd_partition __initdata osiris_शेष_nand_part[] = अणु
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

अटल काष्ठा mtd_partition __initdata osiris_शेष_nand_part_large[] = अणु
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

/* the Osiris has 3 selectable slots क्रम nand-flash, the two
 * on-board chip areas, as well as the बाह्यal slot.
 *
 * Note, there is no current hot-plug support क्रम the External
 * socket.
*/

अटल काष्ठा s3c2410_nand_set __initdata osiris_nand_sets[] = अणु
	[1] = अणु
		.name		= "External",
		.nr_chips	= 1,
		.nr_map		= बाह्यal_map,
		.options	= न_अंकD_SCAN_SILENT_NODEV,
		.nr_partitions	= ARRAY_SIZE(osiris_शेष_nand_part),
		.partitions	= osiris_शेष_nand_part,
	पूर्ण,
	[0] = अणु
		.name		= "chip0",
		.nr_chips	= 1,
		.nr_map		= chip0_map,
		.nr_partitions	= ARRAY_SIZE(osiris_शेष_nand_part),
		.partitions	= osiris_शेष_nand_part,
	पूर्ण,
	[2] = अणु
		.name		= "chip1",
		.nr_chips	= 1,
		.nr_map		= chip1_map,
		.options	= न_अंकD_SCAN_SILENT_NODEV,
		.nr_partitions	= ARRAY_SIZE(osiris_शेष_nand_part),
		.partitions	= osiris_शेष_nand_part,
	पूर्ण,
पूर्ण;

अटल व्योम osiris_nand_select(काष्ठा s3c2410_nand_set *set, पूर्णांक slot)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	slot = set->nr_map[slot] & 3;

	pr_debug("osiris_nand: selecting slot %d (set %p,%p)\n",
		 slot, set, set->nr_map);

	पंचांगp = __raw_पढ़ोb(OSIRIS_VA_CTRL0);
	पंचांगp &= ~OSIRIS_CTRL0_न_अंकDSEL;
	पंचांगp |= slot;

	pr_debug("osiris_nand: ctrl0 now %02x\n", पंचांगp);

	__raw_ग_लिखोb(पंचांगp, OSIRIS_VA_CTRL0);
पूर्ण

अटल काष्ठा s3c2410_platक्रमm_nand __initdata osiris_nand_info = अणु
	.tacls		= 25,
	.twrph0		= 60,
	.twrph1		= 60,
	.nr_sets	= ARRAY_SIZE(osiris_nand_sets),
	.sets		= osiris_nand_sets,
	.select_chip	= osiris_nand_select,
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_SOFT,
पूर्ण;

/* PCMCIA control and configuration */

अटल काष्ठा resource osiris_pcmcia_resource[] = अणु
	[0] = DEFINE_RES_MEM(0x0f000000, SZ_1M),
	[1] = DEFINE_RES_MEM(0x0c000000, SZ_1M),
पूर्ण;

अटल काष्ठा platक्रमm_device osiris_pcmcia = अणु
	.name		= "osiris-pcmcia",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(osiris_pcmcia_resource),
	.resource	= osiris_pcmcia_resource,
पूर्ण;

/* Osiris घातer management device */

#अगर_घोषित CONFIG_PM
अटल अचिन्हित अक्षर pm_osiris_ctrl0;

अटल पूर्णांक osiris_pm_suspend(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	pm_osiris_ctrl0 = __raw_पढ़ोb(OSIRIS_VA_CTRL0);
	पंचांगp = pm_osiris_ctrl0 & ~OSIRIS_CTRL0_न_अंकDSEL;

	/* ensure correct न_अंकD slot is selected on resume */
	अगर ((pm_osiris_ctrl0 & OSIRIS_CTRL0_BOOT_INT) == 0)
	        पंचांगp |= 2;

	__raw_ग_लिखोb(पंचांगp, OSIRIS_VA_CTRL0);

	/* ensure that an nRESET is not generated on resume. */
	gpio_request_one(S3C2410_GPA(21), GPIOF_OUT_INIT_HIGH, शून्य);
	gpio_मुक्त(S3C2410_GPA(21));

	वापस 0;
पूर्ण

अटल व्योम osiris_pm_resume(व्योम)
अणु
	अगर (pm_osiris_ctrl0 & OSIRIS_CTRL0_FIX8)
		__raw_ग_लिखोb(OSIRIS_CTRL1_FIX8, OSIRIS_VA_CTRL1);

	__raw_ग_लिखोb(pm_osiris_ctrl0, OSIRIS_VA_CTRL0);

	s3c_gpio_cfgpin(S3C2410_GPA(21), S3C2410_GPA21_nRSTOUT);
पूर्ण

#अन्यथा
#घोषणा osiris_pm_suspend शून्य
#घोषणा osiris_pm_resume शून्य
#पूर्ण_अगर

अटल काष्ठा syscore_ops osiris_pm_syscore_ops = अणु
	.suspend	= osiris_pm_suspend,
	.resume		= osiris_pm_resume,
पूर्ण;

/* Link क्रम DVS driver to TPS65011 */

अटल व्योम osiris_tps_release(काष्ठा device *dev)
अणु
	/* अटल device, करो not need to release anything */
पूर्ण

अटल काष्ठा platक्रमm_device osiris_tps_device = अणु
	.name	= "osiris-dvs",
	.id	= -1,
	.dev.release = osiris_tps_release,
पूर्ण;

अटल पूर्णांक osiris_tps_setup(काष्ठा i2c_client *client, व्योम *context)
अणु
	osiris_tps_device.dev.parent = &client->dev;
	वापस platक्रमm_device_रेजिस्टर(&osiris_tps_device);
पूर्ण

अटल पूर्णांक osiris_tps_हटाओ(काष्ठा i2c_client *client, व्योम *context)
अणु
	platक्रमm_device_unरेजिस्टर(&osiris_tps_device);
	वापस 0;
पूर्ण

अटल काष्ठा tps65010_board osiris_tps_board = अणु
	.base		= -1,	/* GPIO can go anywhere at the moment */
	.setup		= osiris_tps_setup,
	.tearकरोwn	= osiris_tps_हटाओ,
पूर्ण;

/* I2C devices fitted. */

अटल काष्ठा i2c_board_info osiris_i2c_devs[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("tps65011", 0x48),
		.irq	= IRQ_EINT20,
		.platक्रमm_data = &osiris_tps_board,
	पूर्ण,
पूर्ण;

/* Standard Osiris devices */

अटल काष्ठा platक्रमm_device *osiris_devices[] __initdata = अणु
	&s3c2410_device_dclk,
	&s3c_device_i2c0,
	&s3c_device_wdt,
	&s3c_device_nand,
	&osiris_pcmcia,
पूर्ण;

अटल काष्ठा s3c_cpufreq_board __initdata osiris_cpufreq = अणु
	.refresh	= 7800, /* refresh period is 7.8usec */
	.स्वतः_io	= 1,
	.need_io	= 1,
पूर्ण;

अटल व्योम __init osiris_map_io(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	s3c24xx_init_io(osiris_iodesc, ARRAY_SIZE(osiris_iodesc));
	s3c24xx_init_uarts(osiris_uartcfgs, ARRAY_SIZE(osiris_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);

	/* check क्रम the newer revision boards with large page nand */

	अगर ((__raw_पढ़ोb(OSIRIS_VA_IDREG) & OSIRIS_ID_REVMASK) >= 4) अणु
		prपूर्णांकk(KERN_INFO "OSIRIS-B detected (revision %d)\n",
		       __raw_पढ़ोb(OSIRIS_VA_IDREG) & OSIRIS_ID_REVMASK);
		osiris_nand_sets[0].partitions = osiris_शेष_nand_part_large;
		osiris_nand_sets[0].nr_partitions = ARRAY_SIZE(osiris_शेष_nand_part_large);
	पूर्ण अन्यथा अणु
		/* ग_लिखो-protect line to the न_अंकD */
		gpio_request_one(S3C2410_GPA(0), GPIOF_OUT_INIT_HIGH, शून्य);
		gpio_मुक्त(S3C2410_GPA(0));
	पूर्ण

	/* fix bus configuration (nBE settings wrong on ABLE pre v2.20) */

	local_irq_save(flags);
	__raw_ग_लिखोl(__raw_पढ़ोl(S3C2410_BWSCON) | S3C2410_BWSCON_ST1 | S3C2410_BWSCON_ST2 | S3C2410_BWSCON_ST3 | S3C2410_BWSCON_ST4 | S3C2410_BWSCON_ST5, S3C2410_BWSCON);
	local_irq_restore(flags);
पूर्ण

अटल व्योम __init osiris_init_समय(व्योम)
अणु
	s3c2440_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init osiris_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&osiris_pm_syscore_ops);

	s3c_i2c0_set_platdata(शून्य);
	s3c_nand_set_platdata(&osiris_nand_info);

	s3c_cpufreq_setboard(&osiris_cpufreq);

	i2c_रेजिस्टर_board_info(0, osiris_i2c_devs,
				ARRAY_SIZE(osiris_i2c_devs));

	platक्रमm_add_devices(osiris_devices, ARRAY_SIZE(osiris_devices));
पूर्ण;

MACHINE_START(OSIRIS, "Simtec-OSIRIS")
	/* Maपूर्णांकainer: Ben Dooks <ben@simtec.co.uk> */
	.atag_offset	= 0x100,
	.map_io		= osiris_map_io,
	.init_irq	= s3c2440_init_irq,
	.init_machine	= osiris_init,
	.init_समय	= osiris_init_समय,
MACHINE_END
