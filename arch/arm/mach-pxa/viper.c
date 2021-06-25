<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/viper.c
 *
 *  Support क्रम the Arcom VIPER SBC.
 *
 *  Author:	Ian Campbell
 *  Created:    Feb 03, 2003
 *  Copyright:  Arcom Control Systems
 *
 *  Maपूर्णांकained by Marc Zyngier <maz@misterjones.org>
 *                             <marc.zyngier@altran.com>
 *
 * Based on lubbock.c:
 *  Author:	Nicolas Pitre
 *  Created:	Jun 15, 2001
 *  Copyright:	MontaVista Software Inc.
 */

#समावेश <linux/types.h>
#समावेश <linux/memory.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/major.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/sched.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_data/i2c-gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/usb/isp116x.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/syscore_ops.h>

#समावेश "pxa25x.h"
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <mach/regs-uart.h>
#समावेश <linux/platक्रमm_data/pcmcia-pxa2xx_viper.h>
#समावेश "viper.h"

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/प्रणाली_info.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "generic.h"
#समावेश "devices.h"

अटल अचिन्हित पूर्णांक icr;

अटल व्योम viper_icr_set_bit(अचिन्हित पूर्णांक bit)
अणु
	icr |= bit;
	VIPER_ICR = icr;
पूर्ण

अटल व्योम viper_icr_clear_bit(अचिन्हित पूर्णांक bit)
अणु
	icr &= ~bit;
	VIPER_ICR = icr;
पूर्ण

/* This function is used from the pcmcia module to reset the CF */
अटल व्योम viper_cf_reset(पूर्णांक state)
अणु
	अगर (state)
		viper_icr_set_bit(VIPER_ICR_CF_RST);
	अन्यथा
		viper_icr_clear_bit(VIPER_ICR_CF_RST);
पूर्ण

अटल काष्ठा arcom_pcmcia_pdata viper_pcmcia_info = अणु
	.cd_gpio	= VIPER_CF_CD_GPIO,
	.rdy_gpio	= VIPER_CF_RDY_GPIO,
	.pwr_gpio	= VIPER_CF_POWER_GPIO,
	.reset		= viper_cf_reset,
पूर्ण;

अटल काष्ठा platक्रमm_device viper_pcmcia_device = अणु
	.name		= "viper-pcmcia",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &viper_pcmcia_info,
	पूर्ण,
पूर्ण;

/*
 * The CPLD version रेजिस्टर was not present on VIPER boards prior to
 * v2i1. On v1 boards where the version रेजिस्टर is not present we
 * will just पढ़ो back the previous value from the databus.
 *
 * Thereक्रमe we करो two पढ़ोs. The first समय we ग_लिखो 0 to the
 * (पढ़ो-only) रेजिस्टर beक्रमe पढ़ोing and the second समय we ग_लिखो
 * 0xff first. If the two पढ़ोs करो not match or they पढ़ो back as 0xff
 * or 0x00 then we have version 1 hardware.
 */
अटल u8 viper_hw_version(व्योम)
अणु
	u8 v1, v2;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	VIPER_VERSION = 0;
	v1 = VIPER_VERSION;
	VIPER_VERSION = 0xff;
	v2 = VIPER_VERSION;

	v1 = (v1 != v2 || v1 == 0xff) ? 0 : v1;

	local_irq_restore(flags);
	वापस v1;
पूर्ण

/* CPU प्रणाली core operations. */
अटल पूर्णांक viper_cpu_suspend(व्योम)
अणु
	viper_icr_set_bit(VIPER_ICR_R_DIS);
	वापस 0;
पूर्ण

अटल व्योम viper_cpu_resume(व्योम)
अणु
	viper_icr_clear_bit(VIPER_ICR_R_DIS);
पूर्ण

अटल काष्ठा syscore_ops viper_cpu_syscore_ops = अणु
	.suspend	= viper_cpu_suspend,
	.resume		= viper_cpu_resume,
पूर्ण;

अटल अचिन्हित पूर्णांक current_voltage_भागisor;

/*
 * If क्रमce is not true then step from existing to new भागisor. If
 * क्रमce is true then jump straight to the new भागisor. Stepping is
 * used because अगर the jump in voltage is too large, the VCC can dip
 * too low and the regulator cuts out.
 *
 * क्रमce can be used to initialize the भागisor to a know state by
 * setting the value क्रम the current घड़ी speed, since we are alपढ़ोy
 * running at that speed we know the voltage should be pretty बंद so
 * the jump won't be too large
 */
अटल व्योम viper_set_core_cpu_voltage(अचिन्हित दीर्घ khz, पूर्णांक क्रमce)
अणु
	पूर्णांक i = 0;
	अचिन्हित पूर्णांक भागisor = 0;
	स्थिर अक्षर *v;

	अगर (khz < 200000) अणु
		v = "1.0"; भागisor = 0xfff;
	पूर्ण अन्यथा अगर (khz < 300000) अणु
		v = "1.1"; भागisor = 0xde5;
	पूर्ण अन्यथा अणु
		v = "1.3"; भागisor = 0x325;
	पूर्ण

	pr_debug("viper: setting CPU core voltage to %sV at %d.%03dMHz\n",
		 v, (पूर्णांक)khz / 1000, (पूर्णांक)khz % 1000);

#घोषणा STEP 0x100
	करो अणु
		पूर्णांक step;

		अगर (क्रमce)
			step = भागisor;
		अन्यथा अगर (current_voltage_भागisor < भागisor - STEP)
			step = current_voltage_भागisor + STEP;
		अन्यथा अगर (current_voltage_भागisor > भागisor + STEP)
			step = current_voltage_भागisor - STEP;
		अन्यथा
			step = भागisor;
		क्रमce = 0;

		gpio_set_value(VIPER_PSU_CLK_GPIO, 0);
		gpio_set_value(VIPER_PSU_nCS_LD_GPIO, 0);

		क्रम (i = 1 << 11 ; i > 0 ; i >>= 1) अणु
			udelay(1);

			gpio_set_value(VIPER_PSU_DATA_GPIO, step & i);
			udelay(1);

			gpio_set_value(VIPER_PSU_CLK_GPIO, 1);
			udelay(1);

			gpio_set_value(VIPER_PSU_CLK_GPIO, 0);
		पूर्ण
		udelay(1);

		gpio_set_value(VIPER_PSU_nCS_LD_GPIO, 1);
		udelay(1);

		gpio_set_value(VIPER_PSU_nCS_LD_GPIO, 0);

		current_voltage_भागisor = step;
	पूर्ण जबतक (current_voltage_भागisor != भागisor);
पूर्ण

/* Interrupt handling */
अटल अचिन्हित दीर्घ viper_irq_enabled_mask;
अटल स्थिर पूर्णांक viper_isa_irqs[] = अणु 3, 4, 5, 6, 7, 10, 11, 12, 9, 14, 15 पूर्ण;
अटल स्थिर पूर्णांक viper_isa_irq_map[] = अणु
	0,		/* ISA irq #0, invalid */
	0,		/* ISA irq #1, invalid */
	0,		/* ISA irq #2, invalid */
	1 << 0,		/* ISA irq #3 */
	1 << 1,		/* ISA irq #4 */
	1 << 2,		/* ISA irq #5 */
	1 << 3,		/* ISA irq #6 */
	1 << 4,		/* ISA irq #7 */
	0,		/* ISA irq #8, invalid */
	1 << 8,		/* ISA irq #9 */
	1 << 5,		/* ISA irq #10 */
	1 << 6,		/* ISA irq #11 */
	1 << 7,		/* ISA irq #12 */
	0,		/* ISA irq #13, invalid */
	1 << 9,		/* ISA irq #14 */
	1 << 10,	/* ISA irq #15 */
पूर्ण;

अटल अंतरभूत पूर्णांक viper_irq_to_biपंचांगask(अचिन्हित पूर्णांक irq)
अणु
	वापस viper_isa_irq_map[irq - PXA_ISA_IRQ(0)];
पूर्ण

अटल अंतरभूत पूर्णांक viper_bit_to_irq(पूर्णांक bit)
अणु
	वापस viper_isa_irqs[bit] + PXA_ISA_IRQ(0);
पूर्ण

अटल व्योम viper_ack_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक viper_irq = viper_irq_to_biपंचांगask(d->irq);

	अगर (viper_irq & 0xff)
		VIPER_LO_IRQ_STATUS = viper_irq;
	अन्यथा
		VIPER_HI_IRQ_STATUS = (viper_irq >> 8);
पूर्ण

अटल व्योम viper_mask_irq(काष्ठा irq_data *d)
अणु
	viper_irq_enabled_mask &= ~(viper_irq_to_biपंचांगask(d->irq));
पूर्ण

अटल व्योम viper_unmask_irq(काष्ठा irq_data *d)
अणु
	viper_irq_enabled_mask |= viper_irq_to_biपंचांगask(d->irq);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ viper_irq_pending(व्योम)
अणु
	वापस (VIPER_HI_IRQ_STATUS << 8 | VIPER_LO_IRQ_STATUS) &
			viper_irq_enabled_mask;
पूर्ण

अटल व्योम viper_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ pending;

	pending = viper_irq_pending();
	करो अणु
		/* we're in a chained irq handler,
		 * so ack the पूर्णांकerrupt by hand */
		desc->irq_data.chip->irq_ack(&desc->irq_data);

		अगर (likely(pending)) अणु
			irq = viper_bit_to_irq(__ffs(pending));
			generic_handle_irq(irq);
		पूर्ण
		pending = viper_irq_pending();
	पूर्ण जबतक (pending);
पूर्ण

अटल काष्ठा irq_chip viper_irq_chip = अणु
	.name		= "ISA",
	.irq_ack	= viper_ack_irq,
	.irq_mask	= viper_mask_irq,
	.irq_unmask	= viper_unmask_irq
पूर्ण;

अटल व्योम __init viper_init_irq(व्योम)
अणु
	पूर्णांक level;
	पूर्णांक isa_irq;

	pxa25x_init_irq();

	/* setup ISA IRQs */
	क्रम (level = 0; level < ARRAY_SIZE(viper_isa_irqs); level++) अणु
		isa_irq = viper_bit_to_irq(level);
		irq_set_chip_and_handler(isa_irq, &viper_irq_chip,
					 handle_edge_irq);
		irq_clear_status_flags(isa_irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण

	irq_set_chained_handler(gpio_to_irq(VIPER_CPLD_GPIO),
				viper_irq_handler);
	irq_set_irq_type(gpio_to_irq(VIPER_CPLD_GPIO), IRQ_TYPE_EDGE_BOTH);
पूर्ण

/* Flat Panel */
अटल काष्ठा pxafb_mode_info fb_mode_info[] = अणु
	अणु
		.pixघड़ी	= 157500,

		.xres		= 320,
		.yres		= 240,

		.bpp		= 16,

		.hsync_len	= 63,
		.left_margin	= 7,
		.right_margin	= 13,

		.vsync_len	= 20,
		.upper_margin	= 0,
		.lower_margin	= 0,

		.sync		= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info fb_info = अणु
	.modes			= fb_mode_info,
	.num_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
पूर्ण;

अटल काष्ठा pwm_lookup viper_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa25x-pwm.0", 0, "pwm-backlight.0", शून्य, 1000000,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल पूर्णांक viper_backlight_init(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	/* GPIO9 and 10 control FB backlight. Initialise to off */
	ret = gpio_request(VIPER_BCKLIGHT_EN_GPIO, "Backlight");
	अगर (ret)
		जाओ err_request_bckl;

	ret = gpio_request(VIPER_LCD_EN_GPIO, "LCD");
	अगर (ret)
		जाओ err_request_lcd;

	ret = gpio_direction_output(VIPER_BCKLIGHT_EN_GPIO, 0);
	अगर (ret)
		जाओ err_dir;

	ret = gpio_direction_output(VIPER_LCD_EN_GPIO, 0);
	अगर (ret)
		जाओ err_dir;

	वापस 0;

err_dir:
	gpio_मुक्त(VIPER_LCD_EN_GPIO);
err_request_lcd:
	gpio_मुक्त(VIPER_BCKLIGHT_EN_GPIO);
err_request_bckl:
	dev_err(dev, "Failed to setup LCD GPIOs\n");

	वापस ret;
पूर्ण

अटल पूर्णांक viper_backlight_notअगरy(काष्ठा device *dev, पूर्णांक brightness)
अणु
	gpio_set_value(VIPER_LCD_EN_GPIO, !!brightness);
	gpio_set_value(VIPER_BCKLIGHT_EN_GPIO, !!brightness);

	वापस brightness;
पूर्ण

अटल व्योम viper_backlight_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त(VIPER_LCD_EN_GPIO);
	gpio_मुक्त(VIPER_BCKLIGHT_EN_GPIO);
पूर्ण

अटल काष्ठा platक्रमm_pwm_backlight_data viper_backlight_data = अणु
	.max_brightness	= 100,
	.dft_brightness	= 100,
	.init		= viper_backlight_init,
	.notअगरy		= viper_backlight_notअगरy,
	.निकास		= viper_backlight_निकास,
पूर्ण;

अटल काष्ठा platक्रमm_device viper_backlight_device = अणु
	.name		= "pwm-backlight",
	.dev		= अणु
		.parent		= &pxa25x_device_pwm0.dev,
		.platक्रमm_data	= &viper_backlight_data,
	पूर्ण,
पूर्ण;

/* Ethernet */
अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.name	= "smc91x-regs",
		.start  = VIPER_ETH_PHYS + 0x300,
		.end    = VIPER_ETH_PHYS + 0x30f,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = PXA_GPIO_TO_IRQ(VIPER_ETH_GPIO),
		.end    = PXA_GPIO_TO_IRQ(VIPER_ETH_GPIO),
		.flags  = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण,
	[2] = अणु
		.name	= "smc91x-data32",
		.start  = VIPER_ETH_DATA_PHYS,
		.end    = VIPER_ETH_DATA_PHYS + 3,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा smc91x_platdata viper_smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT,
	.leda	= RPC_LED_100_10,
	.ledb	= RPC_LED_TX_RX,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= -1,
	.num_resources  = ARRAY_SIZE(smc91x_resources),
	.resource       = smc91x_resources,
	.dev		= अणु
		.platक्रमm_data	= &viper_smc91x_info,
	पूर्ण,
पूर्ण;

/* i2c */
अटल काष्ठा gpiod_lookup_table viper_i2c_gpiod_table = अणु
	.dev_id		= "i2c-gpio.1",
	.table		= अणु
		GPIO_LOOKUP_IDX("gpio-pxa", VIPER_RTC_I2C_SDA_GPIO,
				शून्य, 0, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP_IDX("gpio-pxa", VIPER_RTC_I2C_SCL_GPIO,
				शून्य, 1, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_gpio_platक्रमm_data i2c_bus_data = अणु
	.udelay  = 10,
	.समयout = HZ,
पूर्ण;

अटल काष्ठा platक्रमm_device i2c_bus_device = अणु
	.name		= "i2c-gpio",
	.id		= 1, /* pxa2xx-i2c is bus 0, so start at 1 */
	.dev = अणु
		.platक्रमm_data = &i2c_bus_data,
	पूर्ण
पूर्ण;

अटल काष्ठा i2c_board_info __initdata viper_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("ds1338", 0x68),
	पूर्ण,
पूर्ण;

/*
 * Serial configuration:
 * You can either have the standard PXA ports driven by the PXA driver,
 * or all the ports (PXA + 16850) driven by the 8250 driver.
 * Choose your poison.
 */

अटल काष्ठा resource viper_serial_resources[] = अणु
#अगर_अघोषित CONFIG_SERIAL_PXA
	अणु
		.start	= 0x40100000,
		.end	= 0x4010001f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x40200000,
		.end	= 0x4020001f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x40700000,
		.end	= 0x4070001f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= VIPER_UARTA_PHYS,
		.end	= VIPER_UARTA_PHYS + 0xf,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= VIPER_UARTB_PHYS,
		.end	= VIPER_UARTB_PHYS + 0xf,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
#अन्यथा
	अणु
		0,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा plat_serial8250_port serial_platक्रमm_data[] = अणु
#अगर_अघोषित CONFIG_SERIAL_PXA
	/* Internal UARTs */
	अणु
		.membase	= (व्योम *)&FFUART,
		.mapbase	= __PREG(FFUART),
		.irq		= IRQ_FFUART,
		.uartclk	= 921600 * 16,
		.regshअगरt	= 2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	पूर्ण,
	अणु
		.membase	= (व्योम *)&BTUART,
		.mapbase	= __PREG(BTUART),
		.irq		= IRQ_BTUART,
		.uartclk	= 921600 * 16,
		.regshअगरt	= 2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	पूर्ण,
	अणु
		.membase	= (व्योम *)&STUART,
		.mapbase	= __PREG(STUART),
		.irq		= IRQ_STUART,
		.uartclk	= 921600 * 16,
		.regshअगरt	= 2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	पूर्ण,
	/* External UARTs */
	अणु
		.mapbase	= VIPER_UARTA_PHYS,
		.irq		= PXA_GPIO_TO_IRQ(VIPER_UARTA_GPIO),
		.irqflags	= IRQF_TRIGGER_RISING,
		.uartclk	= 1843200,
		.regshअगरt	= 1,
		.iotype		= UPIO_MEM,
		.flags		= UPF_BOOT_AUTOCONF | UPF_IOREMAP |
				  UPF_SKIP_TEST,
	पूर्ण,
	अणु
		.mapbase	= VIPER_UARTB_PHYS,
		.irq		= PXA_GPIO_TO_IRQ(VIPER_UARTB_GPIO),
		.irqflags	= IRQF_TRIGGER_RISING,
		.uartclk	= 1843200,
		.regshअगरt	= 1,
		.iotype		= UPIO_MEM,
		.flags		= UPF_BOOT_AUTOCONF | UPF_IOREMAP |
				  UPF_SKIP_TEST,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device serial_device = अणु
	.name			= "serial8250",
	.id			= 0,
	.dev			= अणु
		.platक्रमm_data	= serial_platक्रमm_data,
	पूर्ण,
	.num_resources		= ARRAY_SIZE(viper_serial_resources),
	.resource		= viper_serial_resources,
पूर्ण;

/* USB */
अटल व्योम isp116x_delay(काष्ठा device *dev, पूर्णांक delay)
अणु
	ndelay(delay);
पूर्ण

अटल काष्ठा resource isp116x_resources[] = अणु
	[0] = अणु /* DATA */
		.start  = VIPER_USB_PHYS + 0,
		.end    = VIPER_USB_PHYS + 1,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु /* ADDR */
		.start  = VIPER_USB_PHYS + 2,
		.end    = VIPER_USB_PHYS + 3,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start  = PXA_GPIO_TO_IRQ(VIPER_USB_GPIO),
		.end    = PXA_GPIO_TO_IRQ(VIPER_USB_GPIO),
		.flags  = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण,
पूर्ण;

/* (DataBusWidth16|AnalogOCEnable|DREQOutputPolarity|DownstreamPort15KRSel ) */
अटल काष्ठा isp116x_platक्रमm_data isp116x_platक्रमm_data = अणु
	/* Enable पूर्णांकernal resistors on करोwnstream ports */
	.sel15Kres		= 1,
	/* On-chip overcurrent protection */
	.oc_enable		= 1,
	/* INT output polarity */
	.पूर्णांक_act_high		= 1,
	/* INT edge or level triggered */
	.पूर्णांक_edge_triggered	= 0,

	/* WAKEUP pin connected - NOT SUPPORTED  */
	/* .remote_wakeup_connected = 0, */
	/* Wakeup by devices on usb bus enabled */
	.remote_wakeup_enable	= 0,
	.delay			= isp116x_delay,
पूर्ण;

अटल काष्ठा platक्रमm_device isp116x_device = अणु
	.name			= "isp116x-hcd",
	.id			= -1,
	.num_resources  	= ARRAY_SIZE(isp116x_resources),
	.resource       	= isp116x_resources,
	.dev			= अणु
		.platक्रमm_data	= &isp116x_platक्रमm_data,
	पूर्ण,

पूर्ण;

/* MTD */
अटल काष्ठा resource mtd_resources[] = अणु
	[0] = अणु	/* RedBoot config + fileप्रणाली flash */
		.start	= VIPER_FLASH_PHYS,
		.end	= VIPER_FLASH_PHYS + SZ_32M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु	/* Boot flash */
		.start	= VIPER_BOOT_PHYS,
		.end	= VIPER_BOOT_PHYS + SZ_1M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु /*
		 * SRAM size is actually 256KB, 8bits, with a sparse mapping
		 * (each byte is on a 16bit boundary).
		 */
		.start	= _VIPER_SRAM_BASE,
		.end	= _VIPER_SRAM_BASE + SZ_512K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition viper_boot_flash_partition = अणु
	.name		= "RedBoot",
	.size		= SZ_1M,
	.offset		= 0,
	.mask_flags	= MTD_WRITEABLE,	/* क्रमce R/O */
पूर्ण;

अटल काष्ठा physmap_flash_data viper_flash_data[] = अणु
	[0] = अणु
		.width		= 2,
		.parts		= शून्य,
		.nr_parts	= 0,
	पूर्ण,
	[1] = अणु
		.width		= 2,
		.parts		= &viper_boot_flash_partition,
		.nr_parts	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device viper_mtd_devices[] = अणु
	[0] = अणु
		.name		= "physmap-flash",
		.id		= 0,
		.dev		= अणु
			.platक्रमm_data	= &viper_flash_data[0],
		पूर्ण,
		.resource	= &mtd_resources[0],
		.num_resources	= 1,
	पूर्ण,
	[1] = अणु
		.name		= "physmap-flash",
		.id		= 1,
		.dev		= अणु
			.platक्रमm_data	= &viper_flash_data[1],
		पूर्ण,
		.resource	= &mtd_resources[1],
		.num_resources	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *viper_devs[] __initdata = अणु
	&smc91x_device,
	&i2c_bus_device,
	&serial_device,
	&isp116x_device,
	&viper_mtd_devices[0],
	&viper_mtd_devices[1],
	&viper_backlight_device,
	&viper_pcmcia_device,
पूर्ण;

अटल mfp_cfg_t viper_pin_config[] __initdata = अणु
	/* Chip selects */
	GPIO15_nCS_1,
	GPIO78_nCS_2,
	GPIO79_nCS_3,
	GPIO80_nCS_4,
	GPIO33_nCS_5,

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,

	/* FP Backlight */
	GPIO9_GPIO, 				/* VIPER_BCKLIGHT_EN_GPIO */
	GPIO10_GPIO,				/* VIPER_LCD_EN_GPIO */
	GPIO16_PWM0_OUT,

	/* Ethernet PHY Ready */
	GPIO18_RDY,

	/* Serial shutकरोwn */
	GPIO12_GPIO | MFP_LPM_DRIVE_HIGH,	/* VIPER_UART_SHDN_GPIO */

	/* Compact-Flash / PC104 */
	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO52_nPCE_1,
	GPIO53_nPCE_2,
	GPIO54_nPSKTSEL,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16,
	GPIO8_GPIO,				/* VIPER_CF_RDY_GPIO */
	GPIO32_GPIO,				/* VIPER_CF_CD_GPIO */
	GPIO82_GPIO,				/* VIPER_CF_POWER_GPIO */

	/* Integrated UPS control */
	GPIO20_GPIO,				/* VIPER_UPS_GPIO */

	/* Vcc regulator control */
	GPIO6_GPIO,				/* VIPER_PSU_DATA_GPIO */
	GPIO11_GPIO,				/* VIPER_PSU_CLK_GPIO */
	GPIO19_GPIO,				/* VIPER_PSU_nCS_LD_GPIO */

	/* i2c busses */
	GPIO26_GPIO,				/* VIPER_TPM_I2C_SDA_GPIO */
	GPIO27_GPIO,				/* VIPER_TPM_I2C_SCL_GPIO */
	GPIO83_GPIO,				/* VIPER_RTC_I2C_SDA_GPIO */
	GPIO84_GPIO,				/* VIPER_RTC_I2C_SCL_GPIO */

	/* PC/104 Interrupt */
	GPIO1_GPIO | WAKEUP_ON_EDGE_RISE,	/* VIPER_CPLD_GPIO */
पूर्ण;

अटल अचिन्हित दीर्घ viper_tpm;

अटल पूर्णांक __init viper_tpm_setup(अक्षर *str)
अणु
	वापस kम_से_अदीर्घ(str, 10, &viper_tpm) >= 0;
पूर्ण

__setup("tpm=", viper_tpm_setup);

काष्ठा gpiod_lookup_table viper_tpm_i2c_gpiod_table = अणु
	.dev_id = "i2c-gpio.2",
	.table = अणु
		GPIO_LOOKUP_IDX("gpio-pxa", VIPER_TPM_I2C_SDA_GPIO,
				शून्य, 0, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP_IDX("gpio-pxa", VIPER_TPM_I2C_SCL_GPIO,
				शून्य, 1, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
	पूर्ण,
पूर्ण;

अटल व्योम __init viper_tpm_init(व्योम)
अणु
	काष्ठा platक्रमm_device *tpm_device;
	काष्ठा i2c_gpio_platक्रमm_data i2c_tpm_data = अणु
		.udelay  = 10,
		.समयout = HZ,
	पूर्ण;
	अक्षर *errstr;

	/* Allocate TPM i2c bus अगर requested */
	अगर (!viper_tpm)
		वापस;

	gpiod_add_lookup_table(&viper_tpm_i2c_gpiod_table);
	tpm_device = platक्रमm_device_alloc("i2c-gpio", 2);
	अगर (tpm_device) अणु
		अगर (!platक्रमm_device_add_data(tpm_device,
					      &i2c_tpm_data,
					      माप(i2c_tpm_data))) अणु
			अगर (platक्रमm_device_add(tpm_device)) अणु
				errstr = "register TPM i2c bus";
				जाओ error_मुक्त_tpm;
			पूर्ण
		पूर्ण अन्यथा अणु
			errstr = "allocate TPM i2c bus data";
			जाओ error_मुक्त_tpm;
		पूर्ण
	पूर्ण अन्यथा अणु
		errstr = "allocate TPM i2c device";
		जाओ error_tpm;
	पूर्ण

	वापस;

error_मुक्त_tpm:
	kमुक्त(tpm_device);
error_tpm:
	pr_err("viper: Couldn't %s, giving up\n", errstr);
पूर्ण

अटल व्योम __init viper_init_vcore_gpios(व्योम)
अणु
	अगर (gpio_request(VIPER_PSU_DATA_GPIO, "PSU data"))
		जाओ err_request_data;

	अगर (gpio_request(VIPER_PSU_CLK_GPIO, "PSU clock"))
		जाओ err_request_clk;

	अगर (gpio_request(VIPER_PSU_nCS_LD_GPIO, "PSU cs"))
		जाओ err_request_cs;

	अगर (gpio_direction_output(VIPER_PSU_DATA_GPIO, 0) ||
	    gpio_direction_output(VIPER_PSU_CLK_GPIO, 0) ||
	    gpio_direction_output(VIPER_PSU_nCS_LD_GPIO, 0))
		जाओ err_dir;

	/* c/should assume redboot set the correct level ??? */
	viper_set_core_cpu_voltage(get_clk_frequency_khz(0), 1);

	वापस;

err_dir:
	gpio_मुक्त(VIPER_PSU_nCS_LD_GPIO);
err_request_cs:
	gpio_मुक्त(VIPER_PSU_CLK_GPIO);
err_request_clk:
	gpio_मुक्त(VIPER_PSU_DATA_GPIO);
err_request_data:
	pr_err("viper: Failed to setup vcore control GPIOs\n");
पूर्ण

अटल व्योम __init viper_init_serial_gpio(व्योम)
अणु
	अगर (gpio_request(VIPER_UART_SHDN_GPIO, "UARTs shutdown"))
		जाओ err_request;

	अगर (gpio_direction_output(VIPER_UART_SHDN_GPIO, 0))
		जाओ err_dir;

	वापस;

err_dir:
	gpio_मुक्त(VIPER_UART_SHDN_GPIO);
err_request:
	pr_err("viper: Failed to setup UART shutdown GPIO\n");
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
अटल पूर्णांक viper_cpufreq_notअगरier(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा cpufreq_freqs *freq = data;

	/* TODO: Adjust timings??? */

	चयन (val) अणु
	हाल CPUFREQ_PRECHANGE:
		अगर (freq->old < freq->new) अणु
			/* we are getting faster so उठाओ the voltage
			 * beक्रमe we change freq */
			viper_set_core_cpu_voltage(freq->new, 0);
		पूर्ण
		अवरोध;
	हाल CPUFREQ_POSTCHANGE:
		अगर (freq->old > freq->new) अणु
			/* we are slowing करोwn so drop the घातer
			 * after we change freq */
			viper_set_core_cpu_voltage(freq->new, 0);
		पूर्ण
		अवरोध;
	शेष:
		/* ignore */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block viper_cpufreq_notअगरier_block = अणु
	.notअगरier_call  = viper_cpufreq_notअगरier
पूर्ण;

अटल व्योम __init viper_init_cpufreq(व्योम)
अणु
	अगर (cpufreq_रेजिस्टर_notअगरier(&viper_cpufreq_notअगरier_block,
				      CPUFREQ_TRANSITION_NOTIFIER))
		pr_err("viper: Failed to setup cpufreq notifier\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम viper_init_cpufreq(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम viper_घातer_off(व्योम)
अणु
	pr_notice("Shutting off UPS\n");
	gpio_set_value(VIPER_UPS_GPIO, 1);
	/* Spin to death... */
	जबतक (1);
पूर्ण

अटल व्योम __init viper_init(व्योम)
अणु
	u8 version;

	pm_घातer_off = viper_घातer_off;

	pxa2xx_mfp_config(ARRAY_AND_SIZE(viper_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	/* Wake-up serial console */
	viper_init_serial_gpio();

	pxa_set_fb_info(शून्य, &fb_info);

	/* v1 hardware cannot use the datacs line */
	version = viper_hw_version();
	अगर (version == 0)
		smc91x_device.num_resources--;

	pxa_set_i2c_info(शून्य);
	gpiod_add_lookup_table(&viper_i2c_gpiod_table);
	pwm_add_table(viper_pwm_lookup, ARRAY_SIZE(viper_pwm_lookup));
	platक्रमm_add_devices(viper_devs, ARRAY_SIZE(viper_devs));

	viper_init_vcore_gpios();
	viper_init_cpufreq();

	रेजिस्टर_syscore_ops(&viper_cpu_syscore_ops);

	अगर (version) अणु
		pr_info("viper: hardware v%di%d detected. "
			"CPLD revision %d.\n",
			VIPER_BOARD_VERSION(version),
			VIPER_BOARD_ISSUE(version),
			VIPER_CPLD_REVISION(version));
		प्रणाली_rev = (VIPER_BOARD_VERSION(version) << 8) |
			     (VIPER_BOARD_ISSUE(version) << 4) |
			     VIPER_CPLD_REVISION(version);
	पूर्ण अन्यथा अणु
		pr_info("viper: No version register.\n");
	पूर्ण

	i2c_रेजिस्टर_board_info(1, ARRAY_AND_SIZE(viper_i2c_devices));

	viper_tpm_init();
	pxa_set_ac97_info(शून्य);
पूर्ण

अटल काष्ठा map_desc viper_io_desc[] __initdata = अणु
	अणु
		.भव = VIPER_CPLD_BASE,
		.pfn     = __phys_to_pfn(VIPER_CPLD_PHYS),
		.length  = 0x00300000,
		.type    = MT_DEVICE,
	पूर्ण,
	अणु
		.भव = VIPER_PC104IO_BASE,
		.pfn     = __phys_to_pfn(0x30000000),
		.length  = 0x00800000,
		.type    = MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल व्योम __init viper_map_io(व्योम)
अणु
	pxa25x_map_io();

	iotable_init(viper_io_desc, ARRAY_SIZE(viper_io_desc));

	PCFR |= PCFR_OPDE;
पूर्ण

MACHINE_START(VIPER, "Arcom/Eurotech VIPER SBC")
	/* Maपूर्णांकainer: Marc Zyngier <maz@misterjones.org> */
	.atag_offset	= 0x100,
	.map_io		= viper_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= viper_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= viper_init,
	.restart	= pxa_restart,
MACHINE_END
