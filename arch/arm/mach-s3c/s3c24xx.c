<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2004-2005 Simtec Electronics
//	http://www.simtec.co.uk/products/SWLINUX/
//	Ben Dooks <ben@simtec.co.uk>
//
// Common code क्रम S3C24XX machines

#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <घड़ीsource/samsung_pwm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/clk-s3c2410.h>
#समावेश <linux/platक्रमm_data/dma-s3c24xx.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/clk/samsung.h>

#समावेश "hardware-s3c24xx.h"
#समावेश "map.h"
#समावेश "regs-clock.h"
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "regs-gpio.h"
#समावेश "dma-s3c24xx.h"

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश "pwm-core.h"

#समावेश "s3c24xx.h"

/* table of supported CPUs */

अटल स्थिर अक्षर name_s3c2410[]  = "S3C2410";
अटल स्थिर अक्षर name_s3c2412[]  = "S3C2412";
अटल स्थिर अक्षर name_s3c2416[]  = "S3C2416/S3C2450";
अटल स्थिर अक्षर name_s3c2440[]  = "S3C2440";
अटल स्थिर अक्षर name_s3c2442[]  = "S3C2442";
अटल स्थिर अक्षर name_s3c2442b[]  = "S3C2442B";
अटल स्थिर अक्षर name_s3c2443[]  = "S3C2443";
अटल स्थिर अक्षर name_s3c2410a[] = "S3C2410A";
अटल स्थिर अक्षर name_s3c2440a[] = "S3C2440A";

अटल काष्ठा cpu_table cpu_ids[] __initdata = अणु
	अणु
		.idcode		= 0x32410000,
		.idmask		= 0xffffffff,
		.map_io		= s3c2410_map_io,
		.init_uarts	= s3c2410_init_uarts,
		.init		= s3c2410_init,
		.name		= name_s3c2410
	पूर्ण,
	अणु
		.idcode		= 0x32410002,
		.idmask		= 0xffffffff,
		.map_io		= s3c2410_map_io,
		.init_uarts	= s3c2410_init_uarts,
		.init		= s3c2410a_init,
		.name		= name_s3c2410a
	पूर्ण,
	अणु
		.idcode		= 0x32440000,
		.idmask		= 0xffffffff,
		.map_io		= s3c2440_map_io,
		.init_uarts	= s3c244x_init_uarts,
		.init		= s3c2440_init,
		.name		= name_s3c2440
	पूर्ण,
	अणु
		.idcode		= 0x32440001,
		.idmask		= 0xffffffff,
		.map_io		= s3c2440_map_io,
		.init_uarts	= s3c244x_init_uarts,
		.init		= s3c2440_init,
		.name		= name_s3c2440a
	पूर्ण,
	अणु
		.idcode		= 0x32440aaa,
		.idmask		= 0xffffffff,
		.map_io		= s3c2442_map_io,
		.init_uarts	= s3c244x_init_uarts,
		.init		= s3c2442_init,
		.name		= name_s3c2442
	पूर्ण,
	अणु
		.idcode		= 0x32440aab,
		.idmask		= 0xffffffff,
		.map_io		= s3c2442_map_io,
		.init_uarts	= s3c244x_init_uarts,
		.init		= s3c2442_init,
		.name		= name_s3c2442b
	पूर्ण,
	अणु
		.idcode		= 0x32412001,
		.idmask		= 0xffffffff,
		.map_io		= s3c2412_map_io,
		.init_uarts	= s3c2412_init_uarts,
		.init		= s3c2412_init,
		.name		= name_s3c2412,
	पूर्ण,
	अणु			/* a newer version of the s3c2412 */
		.idcode		= 0x32412003,
		.idmask		= 0xffffffff,
		.map_io		= s3c2412_map_io,
		.init_uarts	= s3c2412_init_uarts,
		.init		= s3c2412_init,
		.name		= name_s3c2412,
	पूर्ण,
	अणु			/* a strange version of the s3c2416 */
		.idcode		= 0x32450003,
		.idmask		= 0xffffffff,
		.map_io		= s3c2416_map_io,
		.init_uarts	= s3c2416_init_uarts,
		.init		= s3c2416_init,
		.name		= name_s3c2416,
	पूर्ण,
	अणु
		.idcode		= 0x32443001,
		.idmask		= 0xffffffff,
		.map_io		= s3c2443_map_io,
		.init_uarts	= s3c2443_init_uarts,
		.init		= s3c2443_init,
		.name		= name_s3c2443,
	पूर्ण,
पूर्ण;

/* minimal IO mapping */

अटल काष्ठा map_desc s3c_iodesc[] __initdata __maybe_unused = अणु
	IODESC_ENT(GPIO),
	IODESC_ENT(IRQ),
	IODESC_ENT(MEMCTRL),
	IODESC_ENT(UART)
पूर्ण;

/* पढ़ो cpu identअगरicaiton code */

अटल अचिन्हित दीर्घ s3c24xx_पढ़ो_idcode_v5(व्योम)
अणु
#अगर defined(CONFIG_CPU_S3C2416)
	/* s3c2416 is v5, with S3C24XX_GSTATUS1 instead of S3C2412_GSTATUS1 */

	u32 gs = __raw_पढ़ोl(S3C24XX_GSTATUS1);

	/* test क्रम s3c2416 or similar device */
	अगर ((gs >> 16) == 0x3245)
		वापस gs;
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_S3C2412)
	वापस __raw_पढ़ोl(S3C2412_GSTATUS1);
#अन्यथा
	वापस 1UL;	/* करोn't look like an 2400 */
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित दीर्घ s3c24xx_पढ़ो_idcode_v4(व्योम)
अणु
	वापस __raw_पढ़ोl(S3C2410_GSTATUS1);
पूर्ण

अटल व्योम s3c24xx_शेष_idle(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp = 0;
	पूर्णांक i;

	/* idle the प्रणाली by using the idle mode which will रुको क्रम an
	 * पूर्णांकerrupt to happen beक्रमe restarting the प्रणाली.
	 */

	/* Warning: going पूर्णांकo idle state upsets jtag scanning */

	__raw_ग_लिखोl(__raw_पढ़ोl(S3C2410_CLKCON) | S3C2410_CLKCON_IDLE,
		     S3C2410_CLKCON);

	/* the samsung port seems to करो a loop and then unset idle.. */
	क्रम (i = 0; i < 50; i++)
		पंचांगp += __raw_पढ़ोl(S3C2410_CLKCON); /* ensure loop not optimised out */

	/* this bit is not cleared on re-start... */

	__raw_ग_लिखोl(__raw_पढ़ोl(S3C2410_CLKCON) & ~S3C2410_CLKCON_IDLE,
		     S3C2410_CLKCON);
पूर्ण

अटल काष्ठा samsung_pwm_variant s3c24xx_pwm_variant = अणु
	.bits		= 16,
	.भाग_base	= 1,
	.has_tपूर्णांक_cstat	= false,
	.tclk_mask	= (1 << 4),
पूर्ण;

व्योम __init s3c24xx_init_io(काष्ठा map_desc *mach_desc, पूर्णांक size)
अणु
	arm_pm_idle = s3c24xx_शेष_idle;

	/* initialise the io descriptors we need क्रम initialisation */
	iotable_init(mach_desc, size);
	iotable_init(s3c_iodesc, ARRAY_SIZE(s3c_iodesc));

	अगर (cpu_architecture() >= CPU_ARCH_ARMv5) अणु
		samsung_cpu_id = s3c24xx_पढ़ो_idcode_v5();
	पूर्ण अन्यथा अणु
		samsung_cpu_id = s3c24xx_पढ़ो_idcode_v4();
	पूर्ण

	s3c_init_cpu(samsung_cpu_id, cpu_ids, ARRAY_SIZE(cpu_ids));

	samsung_pwm_set_platdata(&s3c24xx_pwm_variant);
पूर्ण

व्योम __init s3c24xx_set_समयr_source(अचिन्हित पूर्णांक event, अचिन्हित पूर्णांक source)
अणु
	s3c24xx_pwm_variant.output_mask = BIT(SAMSUNG_PWM_NUM) - 1;
	s3c24xx_pwm_variant.output_mask &= ~(BIT(event) | BIT(source));
पूर्ण

व्योम __init s3c24xx_समयr_init(व्योम)
अणु
	अचिन्हित पूर्णांक समयr_irqs[SAMSUNG_PWM_NUM] = अणु
		IRQ_TIMER0, IRQ_TIMER1, IRQ_TIMER2, IRQ_TIMER3, IRQ_TIMER4,
	पूर्ण;

	samsung_pwm_घड़ीsource_init(S3C_VA_TIMER,
					समयr_irqs, &s3c24xx_pwm_variant);
पूर्ण

/* Serial port registrations */

#घोषणा S3C2410_PA_UART0      (S3C24XX_PA_UART)
#घोषणा S3C2410_PA_UART1      (S3C24XX_PA_UART + 0x4000 )
#घोषणा S3C2410_PA_UART2      (S3C24XX_PA_UART + 0x8000 )
#घोषणा S3C2443_PA_UART3      (S3C24XX_PA_UART + 0xC000 )

अटल काष्ठा resource s3c2410_uart0_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_PA_UART0, SZ_16K),
	[1] = DEFINE_RES_NAMED(IRQ_S3CUART_RX0, \
			IRQ_S3CUART_ERR0 - IRQ_S3CUART_RX0 + 1, \
			शून्य, IORESOURCE_IRQ)
पूर्ण;

अटल काष्ठा resource s3c2410_uart1_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_PA_UART1, SZ_16K),
	[1] = DEFINE_RES_NAMED(IRQ_S3CUART_RX1, \
			IRQ_S3CUART_ERR1 - IRQ_S3CUART_RX1 + 1, \
			शून्य, IORESOURCE_IRQ)
पूर्ण;

अटल काष्ठा resource s3c2410_uart2_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_PA_UART2, SZ_16K),
	[1] = DEFINE_RES_NAMED(IRQ_S3CUART_RX2, \
			IRQ_S3CUART_ERR2 - IRQ_S3CUART_RX2 + 1, \
			शून्य, IORESOURCE_IRQ)
पूर्ण;

अटल काष्ठा resource s3c2410_uart3_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2443_PA_UART3, SZ_16K),
	[1] = DEFINE_RES_NAMED(IRQ_S3CUART_RX3, \
			IRQ_S3CUART_ERR3 - IRQ_S3CUART_RX3 + 1, \
			शून्य, IORESOURCE_IRQ)
पूर्ण;

काष्ठा s3c24xx_uart_resources s3c2410_uart_resources[] __initdata = अणु
	[0] = अणु
		.resources	= s3c2410_uart0_resource,
		.nr_resources	= ARRAY_SIZE(s3c2410_uart0_resource),
	पूर्ण,
	[1] = अणु
		.resources	= s3c2410_uart1_resource,
		.nr_resources	= ARRAY_SIZE(s3c2410_uart1_resource),
	पूर्ण,
	[2] = अणु
		.resources	= s3c2410_uart2_resource,
		.nr_resources	= ARRAY_SIZE(s3c2410_uart2_resource),
	पूर्ण,
	[3] = अणु
		.resources	= s3c2410_uart3_resource,
		.nr_resources	= ARRAY_SIZE(s3c2410_uart3_resource),
	पूर्ण,
पूर्ण;

#घोषणा s3c24xx_device_dma_mask (*((u64[]) अणु DMA_BIT_MASK(32) पूर्ण))

#अगर defined(CONFIG_CPU_S3C2410) || defined(CONFIG_CPU_S3C2412) || \
	defined(CONFIG_CPU_S3C2440) || defined(CONFIG_CPU_S3C2442)
अटल काष्ठा resource s3c2410_dma_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C24XX_PA_DMA, S3C24XX_SZ_DMA),
	[1] = DEFINE_RES_IRQ(IRQ_DMA0),
	[2] = DEFINE_RES_IRQ(IRQ_DMA1),
	[3] = DEFINE_RES_IRQ(IRQ_DMA2),
	[4] = DEFINE_RES_IRQ(IRQ_DMA3),
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_S3C2410) || defined(CONFIG_CPU_S3C2442)
अटल काष्ठा s3c24xx_dma_channel s3c2410_dma_channels[DMACH_MAX] = अणु
	[DMACH_XD0] = अणु S3C24XX_DMA_AHB, true, S3C24XX_DMA_CHANREQ(0, 0), पूर्ण,
	[DMACH_XD1] = अणु S3C24XX_DMA_AHB, true, S3C24XX_DMA_CHANREQ(0, 1), पूर्ण,
	[DMACH_SDI] = अणु S3C24XX_DMA_APB, false, S3C24XX_DMA_CHANREQ(2, 0) |
						S3C24XX_DMA_CHANREQ(2, 2) |
						S3C24XX_DMA_CHANREQ(1, 3),
	पूर्ण,
	[DMACH_SPI0] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(3, 1), पूर्ण,
	[DMACH_SPI1] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(2, 3), पूर्ण,
	[DMACH_UART0] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(1, 0), पूर्ण,
	[DMACH_UART1] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(1, 1), पूर्ण,
	[DMACH_UART2] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(0, 3), पूर्ण,
	[DMACH_TIMER] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(3, 0) |
						 S3C24XX_DMA_CHANREQ(3, 2) |
						 S3C24XX_DMA_CHANREQ(3, 3),
	पूर्ण,
	[DMACH_I2S_IN] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(2, 1) |
						  S3C24XX_DMA_CHANREQ(1, 2),
	पूर्ण,
	[DMACH_I2S_OUT] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(0, 2), पूर्ण,
	[DMACH_USB_EP1] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(4, 0), पूर्ण,
	[DMACH_USB_EP2] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(4, 1), पूर्ण,
	[DMACH_USB_EP3] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(4, 2), पूर्ण,
	[DMACH_USB_EP4] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(4, 3), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map s3c2410_dma_slave_map[] = अणु
	अणु "s3c2410-sdi", "rx-tx", (व्योम *)DMACH_SDI पूर्ण,
	अणु "s3c2410-spi.0", "rx", (व्योम *)DMACH_SPI0_RX पूर्ण,
	अणु "s3c2410-spi.0", "tx", (व्योम *)DMACH_SPI0_TX पूर्ण,
	अणु "s3c2410-spi.1", "rx", (व्योम *)DMACH_SPI1_RX पूर्ण,
	अणु "s3c2410-spi.1", "tx", (व्योम *)DMACH_SPI1_TX पूर्ण,
	/*
	 * The DMA request source[1] (DMACH_UARTx_SRC2) are
	 * not used in the UART driver.
	 */
	अणु "s3c2410-uart.0", "rx", (व्योम *)DMACH_UART0 पूर्ण,
	अणु "s3c2410-uart.0", "tx", (व्योम *)DMACH_UART0 पूर्ण,
	अणु "s3c2410-uart.1", "rx", (व्योम *)DMACH_UART1 पूर्ण,
	अणु "s3c2410-uart.1", "tx", (व्योम *)DMACH_UART1 पूर्ण,
	अणु "s3c2410-uart.2", "rx", (व्योम *)DMACH_UART2 पूर्ण,
	अणु "s3c2410-uart.2", "tx", (व्योम *)DMACH_UART2 पूर्ण,
	अणु "s3c24xx-iis", "rx", (व्योम *)DMACH_I2S_IN पूर्ण,
	अणु "s3c24xx-iis", "tx", (व्योम *)DMACH_I2S_OUT पूर्ण,
	अणु "s3c-hsudc", "rx0", (व्योम *)DMACH_USB_EP1 पूर्ण,
	अणु "s3c-hsudc", "tx0", (व्योम *)DMACH_USB_EP1 पूर्ण,
	अणु "s3c-hsudc", "rx1", (व्योम *)DMACH_USB_EP2 पूर्ण,
	अणु "s3c-hsudc", "tx1", (व्योम *)DMACH_USB_EP2 पूर्ण,
	अणु "s3c-hsudc", "rx2", (व्योम *)DMACH_USB_EP3 पूर्ण,
	अणु "s3c-hsudc", "tx2", (व्योम *)DMACH_USB_EP3 पूर्ण,
	अणु "s3c-hsudc", "rx3", (व्योम *)DMACH_USB_EP4 पूर्ण,
	अणु "s3c-hsudc", "tx3", (व्योम *)DMACH_USB_EP4 पूर्ण
पूर्ण;

अटल काष्ठा s3c24xx_dma_platdata s3c2410_dma_platdata = अणु
	.num_phy_channels = 4,
	.channels = s3c2410_dma_channels,
	.num_channels = DMACH_MAX,
	.slave_map = s3c2410_dma_slave_map,
	.slavecnt = ARRAY_SIZE(s3c2410_dma_slave_map),
पूर्ण;

काष्ठा platक्रमm_device s3c2410_device_dma = अणु
	.name		= "s3c2410-dma",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s3c2410_dma_resource),
	.resource	= s3c2410_dma_resource,
	.dev	= अणु
		.dma_mask = &s3c24xx_device_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data = &s3c2410_dma_platdata,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2412
अटल काष्ठा s3c24xx_dma_channel s3c2412_dma_channels[DMACH_MAX] = अणु
	[DMACH_XD0] = अणु S3C24XX_DMA_AHB, true, 17 पूर्ण,
	[DMACH_XD1] = अणु S3C24XX_DMA_AHB, true, 18 पूर्ण,
	[DMACH_SDI] = अणु S3C24XX_DMA_APB, false, 10 पूर्ण,
	[DMACH_SPI0_RX] = अणु S3C24XX_DMA_APB, true, 1 पूर्ण,
	[DMACH_SPI0_TX] = अणु S3C24XX_DMA_APB, true, 0 पूर्ण,
	[DMACH_SPI1_RX] = अणु S3C24XX_DMA_APB, true, 3 पूर्ण,
	[DMACH_SPI1_TX] = अणु S3C24XX_DMA_APB, true, 2 पूर्ण,
	[DMACH_UART0] = अणु S3C24XX_DMA_APB, true, 19 पूर्ण,
	[DMACH_UART1] = अणु S3C24XX_DMA_APB, true, 21 पूर्ण,
	[DMACH_UART2] = अणु S3C24XX_DMA_APB, true, 23 पूर्ण,
	[DMACH_UART0_SRC2] = अणु S3C24XX_DMA_APB, true, 20 पूर्ण,
	[DMACH_UART1_SRC2] = अणु S3C24XX_DMA_APB, true, 22 पूर्ण,
	[DMACH_UART2_SRC2] = अणु S3C24XX_DMA_APB, true, 24 पूर्ण,
	[DMACH_TIMER] = अणु S3C24XX_DMA_APB, true, 9 पूर्ण,
	[DMACH_I2S_IN] = अणु S3C24XX_DMA_APB, true, 5 पूर्ण,
	[DMACH_I2S_OUT] = अणु S3C24XX_DMA_APB, true, 4 पूर्ण,
	[DMACH_USB_EP1] = अणु S3C24XX_DMA_APB, true, 13 पूर्ण,
	[DMACH_USB_EP2] = अणु S3C24XX_DMA_APB, true, 14 पूर्ण,
	[DMACH_USB_EP3] = अणु S3C24XX_DMA_APB, true, 15 पूर्ण,
	[DMACH_USB_EP4] = अणु S3C24XX_DMA_APB, true, 16 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map s3c2412_dma_slave_map[] = अणु
	अणु "s3c2412-sdi", "rx-tx", (व्योम *)DMACH_SDI पूर्ण,
	अणु "s3c2412-spi.0", "rx", (व्योम *)DMACH_SPI0_RX पूर्ण,
	अणु "s3c2412-spi.0", "tx", (व्योम *)DMACH_SPI0_TX पूर्ण,
	अणु "s3c2412-spi.1", "rx", (व्योम *)DMACH_SPI1_RX पूर्ण,
	अणु "s3c2412-spi.1", "tx", (व्योम *)DMACH_SPI1_TX पूर्ण,
	अणु "s3c2440-uart.0", "rx", (व्योम *)DMACH_UART0 पूर्ण,
	अणु "s3c2440-uart.0", "tx", (व्योम *)DMACH_UART0 पूर्ण,
	अणु "s3c2440-uart.1", "rx", (व्योम *)DMACH_UART1 पूर्ण,
	अणु "s3c2440-uart.1", "tx", (व्योम *)DMACH_UART1 पूर्ण,
	अणु "s3c2440-uart.2", "rx", (व्योम *)DMACH_UART2 पूर्ण,
	अणु "s3c2440-uart.2", "tx", (व्योम *)DMACH_UART2 पूर्ण,
	अणु "s3c2412-iis", "rx", (व्योम *)DMACH_I2S_IN पूर्ण,
	अणु "s3c2412-iis", "tx", (व्योम *)DMACH_I2S_OUT पूर्ण,
	अणु "s3c-hsudc", "rx0", (व्योम *)DMACH_USB_EP1 पूर्ण,
	अणु "s3c-hsudc", "tx0", (व्योम *)DMACH_USB_EP1 पूर्ण,
	अणु "s3c-hsudc", "rx1", (व्योम *)DMACH_USB_EP2 पूर्ण,
	अणु "s3c-hsudc", "tx1", (व्योम *)DMACH_USB_EP2 पूर्ण,
	अणु "s3c-hsudc", "rx2", (व्योम *)DMACH_USB_EP3 पूर्ण,
	अणु "s3c-hsudc", "tx2", (व्योम *)DMACH_USB_EP3 पूर्ण,
	अणु "s3c-hsudc", "rx3", (व्योम *)DMACH_USB_EP4 पूर्ण,
	अणु "s3c-hsudc", "tx3", (व्योम *)DMACH_USB_EP4 पूर्ण
पूर्ण;

अटल काष्ठा s3c24xx_dma_platdata s3c2412_dma_platdata = अणु
	.num_phy_channels = 4,
	.channels = s3c2412_dma_channels,
	.num_channels = DMACH_MAX,
	.slave_map = s3c2412_dma_slave_map,
	.slavecnt = ARRAY_SIZE(s3c2412_dma_slave_map),
पूर्ण;

काष्ठा platक्रमm_device s3c2412_device_dma = अणु
	.name		= "s3c2412-dma",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s3c2410_dma_resource),
	.resource	= s3c2410_dma_resource,
	.dev	= अणु
		.dma_mask = &s3c24xx_device_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data = &s3c2412_dma_platdata,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_S3C2440)
अटल काष्ठा s3c24xx_dma_channel s3c2440_dma_channels[DMACH_MAX] = अणु
	[DMACH_XD0] = अणु S3C24XX_DMA_AHB, true, S3C24XX_DMA_CHANREQ(0, 0), पूर्ण,
	[DMACH_XD1] = अणु S3C24XX_DMA_AHB, true, S3C24XX_DMA_CHANREQ(0, 1), पूर्ण,
	[DMACH_SDI] = अणु S3C24XX_DMA_APB, false, S3C24XX_DMA_CHANREQ(2, 0) |
						S3C24XX_DMA_CHANREQ(6, 1) |
						S3C24XX_DMA_CHANREQ(2, 2) |
						S3C24XX_DMA_CHANREQ(1, 3),
	पूर्ण,
	[DMACH_SPI0] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(3, 1), पूर्ण,
	[DMACH_SPI1] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(2, 3), पूर्ण,
	[DMACH_UART0] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(1, 0), पूर्ण,
	[DMACH_UART1] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(1, 1), पूर्ण,
	[DMACH_UART2] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(0, 3), पूर्ण,
	[DMACH_TIMER] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(3, 0) |
						 S3C24XX_DMA_CHANREQ(3, 2) |
						 S3C24XX_DMA_CHANREQ(3, 3),
	पूर्ण,
	[DMACH_I2S_IN] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(2, 1) |
						  S3C24XX_DMA_CHANREQ(1, 2),
	पूर्ण,
	[DMACH_I2S_OUT] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(5, 0) |
						   S3C24XX_DMA_CHANREQ(0, 2),
	पूर्ण,
	[DMACH_PCM_IN] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(6, 0) |
						  S3C24XX_DMA_CHANREQ(5, 2),
	पूर्ण,
	[DMACH_PCM_OUT] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(5, 1) |
						  S3C24XX_DMA_CHANREQ(6, 3),
	पूर्ण,
	[DMACH_MIC_IN] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(6, 2) |
						  S3C24XX_DMA_CHANREQ(5, 3),
	पूर्ण,
	[DMACH_USB_EP1] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(4, 0), पूर्ण,
	[DMACH_USB_EP2] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(4, 1), पूर्ण,
	[DMACH_USB_EP3] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(4, 2), पूर्ण,
	[DMACH_USB_EP4] = अणु S3C24XX_DMA_APB, true, S3C24XX_DMA_CHANREQ(4, 3), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map s3c2440_dma_slave_map[] = अणु
	/* TODO: DMACH_XD0 */
	/* TODO: DMACH_XD1 */
	अणु "s3c2440-sdi", "rx-tx", (व्योम *)DMACH_SDI पूर्ण,
	अणु "s3c2410-spi.0", "rx", (व्योम *)DMACH_SPI0 पूर्ण,
	अणु "s3c2410-spi.0", "tx", (व्योम *)DMACH_SPI0 पूर्ण,
	अणु "s3c2410-spi.1", "rx", (व्योम *)DMACH_SPI1 पूर्ण,
	अणु "s3c2410-spi.1", "tx", (व्योम *)DMACH_SPI1 पूर्ण,
	अणु "s3c2440-uart.0", "rx", (व्योम *)DMACH_UART0 पूर्ण,
	अणु "s3c2440-uart.0", "tx", (व्योम *)DMACH_UART0 पूर्ण,
	अणु "s3c2440-uart.1", "rx", (व्योम *)DMACH_UART1 पूर्ण,
	अणु "s3c2440-uart.1", "tx", (व्योम *)DMACH_UART1 पूर्ण,
	अणु "s3c2440-uart.2", "rx", (व्योम *)DMACH_UART2 पूर्ण,
	अणु "s3c2440-uart.2", "tx", (व्योम *)DMACH_UART2 पूर्ण,
	अणु "s3c2440-uart.3", "rx", (व्योम *)DMACH_UART3 पूर्ण,
	अणु "s3c2440-uart.3", "tx", (व्योम *)DMACH_UART3 पूर्ण,
	/* TODO: DMACH_TIMER */
	अणु "s3c24xx-iis", "rx", (व्योम *)DMACH_I2S_IN पूर्ण,
	अणु "s3c24xx-iis", "tx", (व्योम *)DMACH_I2S_OUT पूर्ण,
	अणु "samsung-ac97", "rx", (व्योम *)DMACH_PCM_IN पूर्ण,
	अणु "samsung-ac97", "tx", (व्योम *)DMACH_PCM_OUT पूर्ण,
	अणु "samsung-ac97", "rx", (व्योम *)DMACH_MIC_IN पूर्ण,
	अणु "s3c-hsudc", "rx0", (व्योम *)DMACH_USB_EP1 पूर्ण,
	अणु "s3c-hsudc", "rx1", (व्योम *)DMACH_USB_EP2 पूर्ण,
	अणु "s3c-hsudc", "rx2", (व्योम *)DMACH_USB_EP3 पूर्ण,
	अणु "s3c-hsudc", "rx3", (व्योम *)DMACH_USB_EP4 पूर्ण,
	अणु "s3c-hsudc", "tx0", (व्योम *)DMACH_USB_EP1 पूर्ण,
	अणु "s3c-hsudc", "tx1", (व्योम *)DMACH_USB_EP2 पूर्ण,
	अणु "s3c-hsudc", "tx2", (व्योम *)DMACH_USB_EP3 पूर्ण,
	अणु "s3c-hsudc", "tx3", (व्योम *)DMACH_USB_EP4 पूर्ण
पूर्ण;

अटल काष्ठा s3c24xx_dma_platdata s3c2440_dma_platdata = अणु
	.num_phy_channels = 4,
	.channels = s3c2440_dma_channels,
	.num_channels = DMACH_MAX,
	.slave_map = s3c2440_dma_slave_map,
	.slavecnt = ARRAY_SIZE(s3c2440_dma_slave_map),
पूर्ण;

काष्ठा platक्रमm_device s3c2440_device_dma = अणु
	.name		= "s3c2410-dma",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s3c2410_dma_resource),
	.resource	= s3c2410_dma_resource,
	.dev	= अणु
		.dma_mask = &s3c24xx_device_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data = &s3c2440_dma_platdata,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_S3C2443) || defined(CONFIG_CPU_S3C2416)
अटल काष्ठा resource s3c2443_dma_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C24XX_PA_DMA, S3C24XX_SZ_DMA),
	[1] = DEFINE_RES_IRQ(IRQ_S3C2443_DMA0),
	[2] = DEFINE_RES_IRQ(IRQ_S3C2443_DMA1),
	[3] = DEFINE_RES_IRQ(IRQ_S3C2443_DMA2),
	[4] = DEFINE_RES_IRQ(IRQ_S3C2443_DMA3),
	[5] = DEFINE_RES_IRQ(IRQ_S3C2443_DMA4),
	[6] = DEFINE_RES_IRQ(IRQ_S3C2443_DMA5),
पूर्ण;

अटल काष्ठा s3c24xx_dma_channel s3c2443_dma_channels[DMACH_MAX] = अणु
	[DMACH_XD0] = अणु S3C24XX_DMA_AHB, true, 17 पूर्ण,
	[DMACH_XD1] = अणु S3C24XX_DMA_AHB, true, 18 पूर्ण,
	[DMACH_SDI] = अणु S3C24XX_DMA_APB, false, 10 पूर्ण,
	[DMACH_SPI0_RX] = अणु S3C24XX_DMA_APB, true, 1 पूर्ण,
	[DMACH_SPI0_TX] = अणु S3C24XX_DMA_APB, true, 0 पूर्ण,
	[DMACH_SPI1_RX] = अणु S3C24XX_DMA_APB, true, 3 पूर्ण,
	[DMACH_SPI1_TX] = अणु S3C24XX_DMA_APB, true, 2 पूर्ण,
	[DMACH_UART0] = अणु S3C24XX_DMA_APB, true, 19 पूर्ण,
	[DMACH_UART1] = अणु S3C24XX_DMA_APB, true, 21 पूर्ण,
	[DMACH_UART2] = अणु S3C24XX_DMA_APB, true, 23 पूर्ण,
	[DMACH_UART3] = अणु S3C24XX_DMA_APB, true, 25 पूर्ण,
	[DMACH_UART0_SRC2] = अणु S3C24XX_DMA_APB, true, 20 पूर्ण,
	[DMACH_UART1_SRC2] = अणु S3C24XX_DMA_APB, true, 22 पूर्ण,
	[DMACH_UART2_SRC2] = अणु S3C24XX_DMA_APB, true, 24 पूर्ण,
	[DMACH_UART3_SRC2] = अणु S3C24XX_DMA_APB, true, 26 पूर्ण,
	[DMACH_TIMER] = अणु S3C24XX_DMA_APB, true, 9 पूर्ण,
	[DMACH_I2S_IN] = अणु S3C24XX_DMA_APB, true, 5 पूर्ण,
	[DMACH_I2S_OUT] = अणु S3C24XX_DMA_APB, true, 4 पूर्ण,
	[DMACH_PCM_IN] = अणु S3C24XX_DMA_APB, true, 28 पूर्ण,
	[DMACH_PCM_OUT] = अणु S3C24XX_DMA_APB, true, 27 पूर्ण,
	[DMACH_MIC_IN] = अणु S3C24XX_DMA_APB, true, 29 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map s3c2443_dma_slave_map[] = अणु
	अणु "s3c2440-sdi", "rx-tx", (व्योम *)DMACH_SDI पूर्ण,
	अणु "s3c2443-spi.0", "rx", (व्योम *)DMACH_SPI0_RX पूर्ण,
	अणु "s3c2443-spi.0", "tx", (व्योम *)DMACH_SPI0_TX पूर्ण,
	अणु "s3c2443-spi.1", "rx", (व्योम *)DMACH_SPI1_RX पूर्ण,
	अणु "s3c2443-spi.1", "tx", (व्योम *)DMACH_SPI1_TX पूर्ण,
	अणु "s3c2440-uart.0", "rx", (व्योम *)DMACH_UART0 पूर्ण,
	अणु "s3c2440-uart.0", "tx", (व्योम *)DMACH_UART0 पूर्ण,
	अणु "s3c2440-uart.1", "rx", (व्योम *)DMACH_UART1 पूर्ण,
	अणु "s3c2440-uart.1", "tx", (व्योम *)DMACH_UART1 पूर्ण,
	अणु "s3c2440-uart.2", "rx", (व्योम *)DMACH_UART2 पूर्ण,
	अणु "s3c2440-uart.2", "tx", (व्योम *)DMACH_UART2 पूर्ण,
	अणु "s3c2440-uart.3", "rx", (व्योम *)DMACH_UART3 पूर्ण,
	अणु "s3c2440-uart.3", "tx", (व्योम *)DMACH_UART3 पूर्ण,
	अणु "s3c24xx-iis", "rx", (व्योम *)DMACH_I2S_IN पूर्ण,
	अणु "s3c24xx-iis", "tx", (व्योम *)DMACH_I2S_OUT पूर्ण,
पूर्ण;

अटल काष्ठा s3c24xx_dma_platdata s3c2443_dma_platdata = अणु
	.num_phy_channels = 6,
	.channels = s3c2443_dma_channels,
	.num_channels = DMACH_MAX,
	.slave_map = s3c2443_dma_slave_map,
	.slavecnt = ARRAY_SIZE(s3c2443_dma_slave_map),
पूर्ण;

काष्ठा platक्रमm_device s3c2443_device_dma = अणु
	.name		= "s3c2443-dma",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s3c2443_dma_resource),
	.resource	= s3c2443_dma_resource,
	.dev	= अणु
		.dma_mask = &s3c24xx_device_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data = &s3c2443_dma_platdata,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_COMMON_CLK) && defined(CONFIG_CPU_S3C2410)
व्योम __init s3c2410_init_घड़ीs(पूर्णांक xtal)
अणु
	s3c2410_common_clk_init(शून्य, xtal, 0, S3C24XX_VA_CLKPWR);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2412
व्योम __init s3c2412_init_घड़ीs(पूर्णांक xtal)
अणु
	s3c2412_common_clk_init(शून्य, xtal, 0, S3C24XX_VA_CLKPWR);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2416
व्योम __init s3c2416_init_घड़ीs(पूर्णांक xtal)
अणु
	s3c2443_common_clk_init(शून्य, xtal, 0, S3C24XX_VA_CLKPWR);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_COMMON_CLK) && defined(CONFIG_CPU_S3C2440)
व्योम __init s3c2440_init_घड़ीs(पूर्णांक xtal)
अणु
	s3c2410_common_clk_init(शून्य, xtal, 1, S3C24XX_VA_CLKPWR);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_COMMON_CLK) && defined(CONFIG_CPU_S3C2442)
व्योम __init s3c2442_init_घड़ीs(पूर्णांक xtal)
अणु
	s3c2410_common_clk_init(शून्य, xtal, 2, S3C24XX_VA_CLKPWR);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2443
व्योम __init s3c2443_init_घड़ीs(पूर्णांक xtal)
अणु
	s3c2443_common_clk_init(शून्य, xtal, 1, S3C24XX_VA_CLKPWR);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_S3C2410) || defined(CONFIG_CPU_S3C2440) || \
	defined(CONFIG_CPU_S3C2442)
अटल काष्ठा resource s3c2410_dclk_resource[] = अणु
	[0] = DEFINE_RES_MEM(0x56000084, 0x4),
पूर्ण;

अटल काष्ठा s3c2410_clk_platक्रमm_data s3c_clk_platक्रमm_data = अणु
	.modअगरy_misccr = s3c2410_modअगरy_misccr,
पूर्ण;

काष्ठा platक्रमm_device s3c2410_device_dclk = अणु
	.name		= "s3c2410-dclk",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s3c2410_dclk_resource),
	.resource	= s3c2410_dclk_resource,
	.dev		= अणु
		.platक्रमm_data = &s3c_clk_platक्रमm_data,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर
