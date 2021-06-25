<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2003-2008 Simtec Electronics
//   Ben Dooks <ben@simtec.co.uk>
//
// Machine support क्रम Thorcom VR1000 board. Deचिन्हित क्रम Thorcom by
// Simtec Electronics, http://www.simtec.co.uk/

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/i2c.h>

#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <linux/platक्रमm_data/leds-s3c24xx.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश <linux/platक्रमm_data/asoc-s3c24xx_simtec.h>

#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश "gpio-cfg.h"

#समावेश "cpu.h"
#समावेश "devs.h"

#समावेश "bast.h"
#समावेश "s3c24xx.h"
#समावेश "simtec.h"
#समावेश "vr1000.h"

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

अटल काष्ठा map_desc vr1000_iodesc[] __initdata = अणु
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

  /*  CPLD control रेजिस्टरs, and बाह्यal पूर्णांकerrupt controls */
  अणु
	  .भव	= (u32)VR1000_VA_CTRL1,
	  .pfn		= __phys_to_pfn(VR1000_PA_CTRL1),
	  .length	= SZ_1M,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)VR1000_VA_CTRL2,
	  .pfn		= __phys_to_pfn(VR1000_PA_CTRL2),
	  .length	= SZ_1M,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)VR1000_VA_CTRL3,
	  .pfn		= __phys_to_pfn(VR1000_PA_CTRL3),
	  .length	= SZ_1M,
	  .type		= MT_DEVICE,
  पूर्ण, अणु
	  .भव	= (u32)VR1000_VA_CTRL4,
	  .pfn		= __phys_to_pfn(VR1000_PA_CTRL4),
	  .length	= SZ_1M,
	  .type		= MT_DEVICE,
  पूर्ण,
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg vr1000_uartcfgs[] __initdata = अणु
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

/* definitions क्रम the vr1000 extra 16550 serial ports */

#घोषणा VR1000_BAUDBASE (3692307)

#घोषणा VR1000_SERIAL_MAPBASE(x) (VR1000_PA_SERIAL + 0x80 + ((x) << 5))

अटल काष्ठा plat_serial8250_port serial_platक्रमm_data[] = अणु
	[0] = अणु
		.mapbase	= VR1000_SERIAL_MAPBASE(0),
		.irq		= VR1000_IRQ_SERIAL + 0,
		.flags		= UPF_BOOT_AUTOCONF | UPF_IOREMAP,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 0,
		.uartclk	= VR1000_BAUDBASE,
	पूर्ण,
	[1] = अणु
		.mapbase	= VR1000_SERIAL_MAPBASE(1),
		.irq		= VR1000_IRQ_SERIAL + 1,
		.flags		= UPF_BOOT_AUTOCONF | UPF_IOREMAP,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 0,
		.uartclk	= VR1000_BAUDBASE,
	पूर्ण,
	[2] = अणु
		.mapbase	= VR1000_SERIAL_MAPBASE(2),
		.irq		= VR1000_IRQ_SERIAL + 2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_IOREMAP,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 0,
		.uartclk	= VR1000_BAUDBASE,
	पूर्ण,
	[3] = अणु
		.mapbase	= VR1000_SERIAL_MAPBASE(3),
		.irq		= VR1000_IRQ_SERIAL + 3,
		.flags		= UPF_BOOT_AUTOCONF | UPF_IOREMAP,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 0,
		.uartclk	= VR1000_BAUDBASE,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device serial_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= serial_platक्रमm_data,
	पूर्ण,
पूर्ण;

/* DM9000 ethernet devices */

अटल काष्ठा resource vr1000_dm9k0_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS5 + VR1000_PA_DM9000, 4),
	[1] = DEFINE_RES_MEM(S3C2410_CS5 + VR1000_PA_DM9000 + 0x40, 0x40),
	[2] = DEFINE_RES_NAMED(VR1000_IRQ_DM9000A, 1, शून्य, IORESOURCE_IRQ \
						| IORESOURCE_IRQ_HIGHLEVEL),
पूर्ण;

अटल काष्ठा resource vr1000_dm9k1_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS5 + VR1000_PA_DM9000 + 0x80, 4),
	[1] = DEFINE_RES_MEM(S3C2410_CS5 + VR1000_PA_DM9000 + 0xC0, 0x40),
	[2] = DEFINE_RES_NAMED(VR1000_IRQ_DM9000N, 1, शून्य, IORESOURCE_IRQ \
						| IORESOURCE_IRQ_HIGHLEVEL),
पूर्ण;

/* क्रम the moment we limit ourselves to 16bit IO until some
 * better IO routines can be written and tested
*/

अटल काष्ठा dm9000_plat_data vr1000_dm9k_platdata = अणु
	.flags		= DM9000_PLATF_16BITONLY,
पूर्ण;

अटल काष्ठा platक्रमm_device vr1000_dm9k0 = अणु
	.name		= "dm9000",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(vr1000_dm9k0_resource),
	.resource	= vr1000_dm9k0_resource,
	.dev		= अणु
		.platक्रमm_data = &vr1000_dm9k_platdata,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device vr1000_dm9k1 = अणु
	.name		= "dm9000",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(vr1000_dm9k1_resource),
	.resource	= vr1000_dm9k1_resource,
	.dev		= अणु
		.platक्रमm_data = &vr1000_dm9k_platdata,
	पूर्ण
पूर्ण;

/* LEDS */

अटल काष्ठा gpiod_lookup_table vr1000_led1_gpio_table = अणु
	.dev_id = "s3c24xx_led.1",
	.table = अणु
		GPIO_LOOKUP("GPB", 0, शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table vr1000_led2_gpio_table = अणु
	.dev_id = "s3c24xx_led.2",
	.table = अणु
		GPIO_LOOKUP("GPB", 1, शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table vr1000_led3_gpio_table = अणु
	.dev_id = "s3c24xx_led.3",
	.table = अणु
		GPIO_LOOKUP("GPB", 2, शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata vr1000_led1_pdata = अणु
	.name		= "led1",
	.def_trigger	= "",
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata vr1000_led2_pdata = अणु
	.name		= "led2",
	.def_trigger	= "",
पूर्ण;

अटल काष्ठा s3c24xx_led_platdata vr1000_led3_pdata = अणु
	.name		= "led3",
	.def_trigger	= "",
पूर्ण;

अटल काष्ठा platक्रमm_device vr1000_led1 = अणु
	.name		= "s3c24xx_led",
	.id		= 1,
	.dev		= अणु
		.platक्रमm_data	= &vr1000_led1_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device vr1000_led2 = अणु
	.name		= "s3c24xx_led",
	.id		= 2,
	.dev		= अणु
		.platक्रमm_data	= &vr1000_led2_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device vr1000_led3 = अणु
	.name		= "s3c24xx_led",
	.id		= 3,
	.dev		= अणु
		.platक्रमm_data	= &vr1000_led3_pdata,
	पूर्ण,
पूर्ण;

/* I2C devices. */

अटल काष्ठा i2c_board_info vr1000_i2c_devs[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("tlv320aic23", 0x1a),
	पूर्ण, अणु
		I2C_BOARD_INFO("tmp101", 0x48),
	पूर्ण, अणु
		I2C_BOARD_INFO("m41st87", 0x68),
	पूर्ण,
पूर्ण;

/* devices क्रम this board */

अटल काष्ठा platक्रमm_device *vr1000_devices[] __initdata = अणु
	&s3c2410_device_dclk,
	&s3c_device_ohci,
	&s3c_device_lcd,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_adc,
	&serial_device,
	&vr1000_dm9k0,
	&vr1000_dm9k1,
	&vr1000_led1,
	&vr1000_led2,
	&vr1000_led3,
पूर्ण;

अटल व्योम vr1000_घातer_off(व्योम)
अणु
	gpio_direction_output(S3C2410_GPB(9), 1);
पूर्ण

अटल व्योम __init vr1000_map_io(व्योम)
अणु
	pm_घातer_off = vr1000_घातer_off;

	s3c24xx_init_io(vr1000_iodesc, ARRAY_SIZE(vr1000_iodesc));
	s3c24xx_init_uarts(vr1000_uartcfgs, ARRAY_SIZE(vr1000_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init vr1000_init_समय(व्योम)
अणु
	s3c2410_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init vr1000_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);

	/* Disable pull-up on LED lines and रेजिस्टर GPIO lookups */
	s3c_gpio_setpull(S3C2410_GPB(0), S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(S3C2410_GPB(1), S3C_GPIO_PULL_NONE);
	s3c_gpio_setpull(S3C2410_GPB(2), S3C_GPIO_PULL_NONE);
	gpiod_add_lookup_table(&vr1000_led1_gpio_table);
	gpiod_add_lookup_table(&vr1000_led2_gpio_table);
	gpiod_add_lookup_table(&vr1000_led3_gpio_table);

	platक्रमm_add_devices(vr1000_devices, ARRAY_SIZE(vr1000_devices));

	i2c_रेजिस्टर_board_info(0, vr1000_i2c_devs,
				ARRAY_SIZE(vr1000_i2c_devs));

	nor_simtec_init();
	simtec_audio_add(शून्य, true, शून्य);

	WARN_ON(gpio_request(S3C2410_GPB(9), "power off"));
पूर्ण

MACHINE_START(VR1000, "Thorcom-VR1000")
	/* Maपूर्णांकainer: Ben Dooks <ben@simtec.co.uk> */
	.atag_offset	= 0x100,
	.map_io		= vr1000_map_io,
	.init_machine	= vr1000_init,
	.init_irq	= s3c2410_init_irq,
	.init_समय	= vr1000_init_समय,
MACHINE_END
