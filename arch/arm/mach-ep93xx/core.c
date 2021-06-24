<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-ep93xx/core.c
 * Core routines क्रम Cirrus EP93xx chips.
 *
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 * Copyright (C) 2007 Herbert Valerio Riedel <hvr@gnu.org>
 *
 * Thanks go to Michael Burian and Ray Lehtiniemi क्रम their key
 * role in the ep93xx linux community.
 */

#घोषणा pr_fmt(fmt) "ep93xx " KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/leds.h>
#समावेश <linux/termios.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/amba/serial.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/export.h>
#समावेश <linux/irqchip/arm-vic.h>
#समावेश <linux/reboot.h>
#समावेश <linux/usb/ohci_pdriver.h>
#समावेश <linux/अक्रमom.h>

#समावेश "hardware.h"
#समावेश <linux/platक्रमm_data/video-ep93xx.h>
#समावेश <linux/platक्रमm_data/keypad-ep93xx.h>
#समावेश <linux/platक्रमm_data/spi-ep93xx.h>
#समावेश <linux/soc/cirrus/ep93xx.h>

#समावेश "gpio-ep93xx.h"

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "soc.h"

/*************************************************************************
 * Static I/O mappings that are needed क्रम all EP93xx platक्रमms
 *************************************************************************/
अटल काष्ठा map_desc ep93xx_io_desc[] __initdata = अणु
	अणु
		.भव	= EP93XX_AHB_VIRT_BASE,
		.pfn		= __phys_to_pfn(EP93XX_AHB_PHYS_BASE),
		.length		= EP93XX_AHB_SIZE,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= EP93XX_APB_VIRT_BASE,
		.pfn		= __phys_to_pfn(EP93XX_APB_PHYS_BASE),
		.length		= EP93XX_APB_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

व्योम __init ep93xx_map_io(व्योम)
अणु
	iotable_init(ep93xx_io_desc, ARRAY_SIZE(ep93xx_io_desc));
पूर्ण

/*************************************************************************
 * EP93xx IRQ handling
 *************************************************************************/
व्योम __init ep93xx_init_irq(व्योम)
अणु
	vic_init(EP93XX_VIC1_BASE, 0, EP93XX_VIC1_VALID_IRQ_MASK, 0);
	vic_init(EP93XX_VIC2_BASE, 32, EP93XX_VIC2_VALID_IRQ_MASK, 0);
पूर्ण


/*************************************************************************
 * EP93xx System Controller Software Locked रेजिस्टर handling
 *************************************************************************/

/*
 * syscon_swlock prevents anything अन्यथा from writing to the syscon
 * block जबतक a software locked रेजिस्टर is being written.
 */
अटल DEFINE_SPINLOCK(syscon_swlock);

व्योम ep93xx_syscon_swlocked_ग_लिखो(अचिन्हित पूर्णांक val, व्योम __iomem *reg)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&syscon_swlock, flags);

	__raw_ग_लिखोl(0xaa, EP93XX_SYSCON_SWLOCK);
	__raw_ग_लिखोl(val, reg);

	spin_unlock_irqrestore(&syscon_swlock, flags);
पूर्ण

व्योम ep93xx_devcfg_set_clear(अचिन्हित पूर्णांक set_bits, अचिन्हित पूर्णांक clear_bits)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&syscon_swlock, flags);

	val = __raw_पढ़ोl(EP93XX_SYSCON_DEVCFG);
	val &= ~clear_bits;
	val |= set_bits;
	__raw_ग_लिखोl(0xaa, EP93XX_SYSCON_SWLOCK);
	__raw_ग_लिखोl(val, EP93XX_SYSCON_DEVCFG);

	spin_unlock_irqrestore(&syscon_swlock, flags);
पूर्ण

/**
 * ep93xx_chip_revision() - वापसs the EP93xx chip revision
 *
 * See "platform.h" क्रम more inक्रमmation.
 */
अचिन्हित पूर्णांक ep93xx_chip_revision(व्योम)
अणु
	अचिन्हित पूर्णांक v;

	v = __raw_पढ़ोl(EP93XX_SYSCON_SYSCFG);
	v &= EP93XX_SYSCON_SYSCFG_REV_MASK;
	v >>= EP93XX_SYSCON_SYSCFG_REV_SHIFT;
	वापस v;
पूर्ण
EXPORT_SYMBOL_GPL(ep93xx_chip_revision);

/*************************************************************************
 * EP93xx GPIO
 *************************************************************************/
अटल काष्ठा resource ep93xx_gpio_resource[] = अणु
	DEFINE_RES_MEM(EP93XX_GPIO_PHYS_BASE, 0xcc),
	DEFINE_RES_IRQ(IRQ_EP93XX_GPIO_AB),
	DEFINE_RES_IRQ(IRQ_EP93XX_GPIO0MUX),
	DEFINE_RES_IRQ(IRQ_EP93XX_GPIO1MUX),
	DEFINE_RES_IRQ(IRQ_EP93XX_GPIO2MUX),
	DEFINE_RES_IRQ(IRQ_EP93XX_GPIO3MUX),
	DEFINE_RES_IRQ(IRQ_EP93XX_GPIO4MUX),
	DEFINE_RES_IRQ(IRQ_EP93XX_GPIO5MUX),
	DEFINE_RES_IRQ(IRQ_EP93XX_GPIO6MUX),
	DEFINE_RES_IRQ(IRQ_EP93XX_GPIO7MUX),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_gpio_device = अणु
	.name		= "gpio-ep93xx",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ep93xx_gpio_resource),
	.resource	= ep93xx_gpio_resource,
पूर्ण;

/*************************************************************************
 * EP93xx peripheral handling
 *************************************************************************/
#घोषणा EP93XX_UART_MCR_OFFSET		(0x0100)

अटल व्योम ep93xx_uart_set_mctrl(काष्ठा amba_device *dev,
				  व्योम __iomem *base, अचिन्हित पूर्णांक mctrl)
अणु
	अचिन्हित पूर्णांक mcr;

	mcr = 0;
	अगर (mctrl & TIOCM_RTS)
		mcr |= 2;
	अगर (mctrl & TIOCM_DTR)
		mcr |= 1;

	__raw_ग_लिखोl(mcr, base + EP93XX_UART_MCR_OFFSET);
पूर्ण

अटल काष्ठा amba_pl010_data ep93xx_uart_data = अणु
	.set_mctrl	= ep93xx_uart_set_mctrl,
पूर्ण;

अटल AMBA_APB_DEVICE(uart1, "apb:uart1", 0x00041010, EP93XX_UART1_PHYS_BASE,
	अणु IRQ_EP93XX_UART1 पूर्ण, &ep93xx_uart_data);

अटल AMBA_APB_DEVICE(uart2, "apb:uart2", 0x00041010, EP93XX_UART2_PHYS_BASE,
	अणु IRQ_EP93XX_UART2 पूर्ण, शून्य);

अटल AMBA_APB_DEVICE(uart3, "apb:uart3", 0x00041010, EP93XX_UART3_PHYS_BASE,
	अणु IRQ_EP93XX_UART3 पूर्ण, &ep93xx_uart_data);

अटल काष्ठा resource ep93xx_rtc_resource[] = अणु
	DEFINE_RES_MEM(EP93XX_RTC_PHYS_BASE, 0x10c),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_rtc_device = अणु
	.name		= "ep93xx-rtc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ep93xx_rtc_resource),
	.resource	= ep93xx_rtc_resource,
पूर्ण;

/*************************************************************************
 * EP93xx OHCI USB Host
 *************************************************************************/

अटल काष्ठा clk *ep93xx_ohci_host_घड़ी;

अटल पूर्णांक ep93xx_ohci_घातer_on(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (!ep93xx_ohci_host_घड़ी) अणु
		ep93xx_ohci_host_घड़ी = devm_clk_get(&pdev->dev, शून्य);
		अगर (IS_ERR(ep93xx_ohci_host_घड़ी))
			वापस PTR_ERR(ep93xx_ohci_host_घड़ी);
	पूर्ण

	वापस clk_enable(ep93xx_ohci_host_घड़ी);
पूर्ण

अटल व्योम ep93xx_ohci_घातer_off(काष्ठा platक्रमm_device *pdev)
अणु
	clk_disable(ep93xx_ohci_host_घड़ी);
पूर्ण

अटल काष्ठा usb_ohci_pdata ep93xx_ohci_pdata = अणु
	.घातer_on	= ep93xx_ohci_घातer_on,
	.घातer_off	= ep93xx_ohci_घातer_off,
	.घातer_suspend	= ep93xx_ohci_घातer_off,
पूर्ण;

अटल काष्ठा resource ep93xx_ohci_resources[] = अणु
	DEFINE_RES_MEM(EP93XX_USB_PHYS_BASE, 0x1000),
	DEFINE_RES_IRQ(IRQ_EP93XX_USB),
पूर्ण;

अटल u64 ep93xx_ohci_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device ep93xx_ohci_device = अणु
	.name		= "ohci-platform",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ep93xx_ohci_resources),
	.resource	= ep93xx_ohci_resources,
	.dev		= अणु
		.dma_mask		= &ep93xx_ohci_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &ep93xx_ohci_pdata,
	पूर्ण,
पूर्ण;

/*************************************************************************
 * EP93xx physmap'ed flash
 *************************************************************************/
अटल काष्ठा physmap_flash_data ep93xx_flash_data;

अटल काष्ठा resource ep93xx_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &ep93xx_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &ep93xx_flash_resource,
पूर्ण;

/**
 * ep93xx_रेजिस्टर_flash() - Register the बाह्यal flash device.
 * @width:	bank width in octets
 * @start:	resource start address
 * @size:	resource size
 */
व्योम __init ep93xx_रेजिस्टर_flash(अचिन्हित पूर्णांक width,
				  resource_माप_प्रकार start, resource_माप_प्रकार size)
अणु
	ep93xx_flash_data.width		= width;

	ep93xx_flash_resource.start	= start;
	ep93xx_flash_resource.end	= start + size - 1;

	platक्रमm_device_रेजिस्टर(&ep93xx_flash);
पूर्ण


/*************************************************************************
 * EP93xx ethernet peripheral handling
 *************************************************************************/
अटल काष्ठा ep93xx_eth_data ep93xx_eth_data;

अटल काष्ठा resource ep93xx_eth_resource[] = अणु
	DEFINE_RES_MEM(EP93XX_ETHERNET_PHYS_BASE, 0x10000),
	DEFINE_RES_IRQ(IRQ_EP93XX_ETHERNET),
पूर्ण;

अटल u64 ep93xx_eth_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device ep93xx_eth_device = अणु
	.name		= "ep93xx-eth",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data		= &ep93xx_eth_data,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.dma_mask		= &ep93xx_eth_dma_mask,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(ep93xx_eth_resource),
	.resource	= ep93xx_eth_resource,
पूर्ण;

/**
 * ep93xx_रेजिस्टर_eth - Register the built-in ethernet platक्रमm device.
 * @data:	platक्रमm specअगरic ethernet configuration (__initdata)
 * @copy_addr:	flag indicating that the MAC address should be copied
 *		from the IndAd रेजिस्टरs (as programmed by the bootloader)
 */
व्योम __init ep93xx_रेजिस्टर_eth(काष्ठा ep93xx_eth_data *data, पूर्णांक copy_addr)
अणु
	अगर (copy_addr)
		स_नकल_fromio(data->dev_addr, EP93XX_ETHERNET_BASE + 0x50, 6);

	ep93xx_eth_data = *data;
	platक्रमm_device_रेजिस्टर(&ep93xx_eth_device);
पूर्ण


/*************************************************************************
 * EP93xx i2c peripheral handling
 *************************************************************************/

/* All EP93xx devices use the same two GPIO pins क्रम I2C bit-banging */
अटल काष्ठा gpiod_lookup_table ep93xx_i2c_gpiod_table = अणु
	.dev_id		= "i2c-gpio.0",
	.table		= अणु
		/* Use local offsets on gpiochip/port "G" */
		GPIO_LOOKUP_IDX("G", 1, शून्य, 0,
				GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP_IDX("G", 0, शून्य, 1,
				GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_i2c_device = अणु
	.name		= "i2c-gpio",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= शून्य,
	पूर्ण,
पूर्ण;

/**
 * ep93xx_रेजिस्टर_i2c - Register the i2c platक्रमm device.
 * @devices:	platक्रमm specअगरic i2c bus device inक्रमmation (__initdata)
 * @num:	the number of devices on the i2c bus
 */
व्योम __init ep93xx_रेजिस्टर_i2c(काष्ठा i2c_board_info *devices, पूर्णांक num)
अणु
	/*
	 * FIXME: this just sets the two pins as non-खोलोdrain, as no
	 * platक्रमms tries to करो that anyway. Flag the applicable lines
	 * as खोलो drain in the GPIO_LOOKUP above and the driver or
	 * gpiolib will handle खोलो drain/खोलो drain emulation as need
	 * be. Right now i2c-gpio emulates खोलो drain which is not
	 * optimal.
	 */
	__raw_ग_लिखोl((0 << 1) | (0 << 0),
		     EP93XX_GPIO_EEDRIVE);

	i2c_रेजिस्टर_board_info(0, devices, num);
	gpiod_add_lookup_table(&ep93xx_i2c_gpiod_table);
	platक्रमm_device_रेजिस्टर(&ep93xx_i2c_device);
पूर्ण

/*************************************************************************
 * EP93xx SPI peripheral handling
 *************************************************************************/
अटल काष्ठा ep93xx_spi_info ep93xx_spi_master_data;

अटल काष्ठा resource ep93xx_spi_resources[] = अणु
	DEFINE_RES_MEM(EP93XX_SPI_PHYS_BASE, 0x18),
	DEFINE_RES_IRQ(IRQ_EP93XX_SSP),
पूर्ण;

अटल u64 ep93xx_spi_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device ep93xx_spi_device = अणु
	.name		= "ep93xx-spi",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data		= &ep93xx_spi_master_data,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.dma_mask		= &ep93xx_spi_dma_mask,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(ep93xx_spi_resources),
	.resource	= ep93xx_spi_resources,
पूर्ण;

/**
 * ep93xx_रेजिस्टर_spi() - रेजिस्टरs spi platक्रमm device
 * @info: ep93xx board specअगरic spi master info (__initdata)
 * @devices: SPI devices to रेजिस्टर (__initdata)
 * @num: number of SPI devices to रेजिस्टर
 *
 * This function रेजिस्टरs platक्रमm device क्रम the EP93xx SPI controller and
 * also makes sure that SPI pins are muxed so that I2S is not using those pins.
 */
व्योम __init ep93xx_रेजिस्टर_spi(काष्ठा ep93xx_spi_info *info,
				काष्ठा spi_board_info *devices, पूर्णांक num)
अणु
	/*
	 * When SPI is used, we need to make sure that I2S is muxed off from
	 * SPI pins.
	 */
	ep93xx_devcfg_clear_bits(EP93XX_SYSCON_DEVCFG_I2SONSSP);

	ep93xx_spi_master_data = *info;
	spi_रेजिस्टर_board_info(devices, num);
	platक्रमm_device_रेजिस्टर(&ep93xx_spi_device);
पूर्ण

/*************************************************************************
 * EP93xx LEDs
 *************************************************************************/
अटल स्थिर काष्ठा gpio_led ep93xx_led_pins[] __initस्थिर = अणु
	अणु
		.name	= "platform:grled",
		.gpio	= EP93XX_GPIO_LINE_GRLED,
	पूर्ण, अणु
		.name	= "platform:rdled",
		.gpio	= EP93XX_GPIO_LINE_RDLED,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led_platक्रमm_data ep93xx_led_data __initस्थिर = अणु
	.num_leds	= ARRAY_SIZE(ep93xx_led_pins),
	.leds		= ep93xx_led_pins,
पूर्ण;

/*************************************************************************
 * EP93xx pwm peripheral handling
 *************************************************************************/
अटल काष्ठा resource ep93xx_pwm0_resource[] = अणु
	DEFINE_RES_MEM(EP93XX_PWM_PHYS_BASE, 0x10),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_pwm0_device = अणु
	.name		= "ep93xx-pwm",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(ep93xx_pwm0_resource),
	.resource	= ep93xx_pwm0_resource,
पूर्ण;

अटल काष्ठा resource ep93xx_pwm1_resource[] = अणु
	DEFINE_RES_MEM(EP93XX_PWM_PHYS_BASE + 0x20, 0x10),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_pwm1_device = अणु
	.name		= "ep93xx-pwm",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(ep93xx_pwm1_resource),
	.resource	= ep93xx_pwm1_resource,
पूर्ण;

व्योम __init ep93xx_रेजिस्टर_pwm(पूर्णांक pwm0, पूर्णांक pwm1)
अणु
	अगर (pwm0)
		platक्रमm_device_रेजिस्टर(&ep93xx_pwm0_device);

	/* NOTE: EP9307 करोes not have PWMOUT1 (pin EGPIO14) */
	अगर (pwm1)
		platक्रमm_device_रेजिस्टर(&ep93xx_pwm1_device);
पूर्ण

पूर्णांक ep93xx_pwm_acquire_gpio(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;

	अगर (pdev->id == 0) अणु
		err = 0;
	पूर्ण अन्यथा अगर (pdev->id == 1) अणु
		err = gpio_request(EP93XX_GPIO_LINE_EGPIO14,
				   dev_name(&pdev->dev));
		अगर (err)
			वापस err;
		err = gpio_direction_output(EP93XX_GPIO_LINE_EGPIO14, 0);
		अगर (err)
			जाओ fail;

		/* PWM 1 output on EGPIO[14] */
		ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_PONG);
	पूर्ण अन्यथा अणु
		err = -ENODEV;
	पूर्ण

	वापस err;

fail:
	gpio_मुक्त(EP93XX_GPIO_LINE_EGPIO14);
	वापस err;
पूर्ण
EXPORT_SYMBOL(ep93xx_pwm_acquire_gpio);

व्योम ep93xx_pwm_release_gpio(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pdev->id == 1) अणु
		gpio_direction_input(EP93XX_GPIO_LINE_EGPIO14);
		gpio_मुक्त(EP93XX_GPIO_LINE_EGPIO14);

		/* EGPIO[14] used क्रम GPIO */
		ep93xx_devcfg_clear_bits(EP93XX_SYSCON_DEVCFG_PONG);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ep93xx_pwm_release_gpio);


/*************************************************************************
 * EP93xx video peripheral handling
 *************************************************************************/
अटल काष्ठा ep93xxfb_mach_info ep93xxfb_data;

अटल काष्ठा resource ep93xx_fb_resource[] = अणु
	DEFINE_RES_MEM(EP93XX_RASTER_PHYS_BASE, 0x800),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_fb_device = अणु
	.name			= "ep93xx-fb",
	.id			= -1,
	.dev			= अणु
		.platक्रमm_data		= &ep93xxfb_data,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.dma_mask		= &ep93xx_fb_device.dev.coherent_dma_mask,
	पूर्ण,
	.num_resources		= ARRAY_SIZE(ep93xx_fb_resource),
	.resource		= ep93xx_fb_resource,
पूर्ण;

/* The backlight use a single रेजिस्टर in the framebuffer's रेजिस्टर space */
#घोषणा EP93XX_RASTER_REG_BRIGHTNESS 0x20

अटल काष्ठा resource ep93xx_bl_resources[] = अणु
	DEFINE_RES_MEM(EP93XX_RASTER_PHYS_BASE +
		       EP93XX_RASTER_REG_BRIGHTNESS, 0x04),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_bl_device = अणु
	.name		= "ep93xx-bl",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ep93xx_bl_resources),
	.resource	= ep93xx_bl_resources,
पूर्ण;

/**
 * ep93xx_रेजिस्टर_fb - Register the framebuffer platक्रमm device.
 * @data:	platक्रमm specअगरic framebuffer configuration (__initdata)
 */
व्योम __init ep93xx_रेजिस्टर_fb(काष्ठा ep93xxfb_mach_info *data)
अणु
	ep93xxfb_data = *data;
	platक्रमm_device_रेजिस्टर(&ep93xx_fb_device);
	platक्रमm_device_रेजिस्टर(&ep93xx_bl_device);
पूर्ण


/*************************************************************************
 * EP93xx matrix keypad peripheral handling
 *************************************************************************/
अटल काष्ठा ep93xx_keypad_platक्रमm_data ep93xx_keypad_data;

अटल काष्ठा resource ep93xx_keypad_resource[] = अणु
	DEFINE_RES_MEM(EP93XX_KEY_MATRIX_PHYS_BASE, 0x0c),
	DEFINE_RES_IRQ(IRQ_EP93XX_KEY),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_keypad_device = अणु
	.name		= "ep93xx-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &ep93xx_keypad_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(ep93xx_keypad_resource),
	.resource	= ep93xx_keypad_resource,
पूर्ण;

/**
 * ep93xx_रेजिस्टर_keypad - Register the keypad platक्रमm device.
 * @data:	platक्रमm specअगरic keypad configuration (__initdata)
 */
व्योम __init ep93xx_रेजिस्टर_keypad(काष्ठा ep93xx_keypad_platक्रमm_data *data)
अणु
	ep93xx_keypad_data = *data;
	platक्रमm_device_रेजिस्टर(&ep93xx_keypad_device);
पूर्ण

पूर्णांक ep93xx_keypad_acquire_gpio(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		err = gpio_request(EP93XX_GPIO_LINE_C(i), dev_name(&pdev->dev));
		अगर (err)
			जाओ fail_gpio_c;
		err = gpio_request(EP93XX_GPIO_LINE_D(i), dev_name(&pdev->dev));
		अगर (err)
			जाओ fail_gpio_d;
	पूर्ण

	/* Enable the keypad controller; GPIO ports C and D used क्रम keypad */
	ep93xx_devcfg_clear_bits(EP93XX_SYSCON_DEVCFG_KEYS |
				 EP93XX_SYSCON_DEVCFG_GONK);

	वापस 0;

fail_gpio_d:
	gpio_मुक्त(EP93XX_GPIO_LINE_C(i));
fail_gpio_c:
	क्रम (--i; i >= 0; --i) अणु
		gpio_मुक्त(EP93XX_GPIO_LINE_C(i));
		gpio_मुक्त(EP93XX_GPIO_LINE_D(i));
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(ep93xx_keypad_acquire_gpio);

व्योम ep93xx_keypad_release_gpio(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		gpio_मुक्त(EP93XX_GPIO_LINE_C(i));
		gpio_मुक्त(EP93XX_GPIO_LINE_D(i));
	पूर्ण

	/* Disable the keypad controller; GPIO ports C and D used क्रम GPIO */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_KEYS |
			       EP93XX_SYSCON_DEVCFG_GONK);
पूर्ण
EXPORT_SYMBOL(ep93xx_keypad_release_gpio);

/*************************************************************************
 * EP93xx I2S audio peripheral handling
 *************************************************************************/
अटल काष्ठा resource ep93xx_i2s_resource[] = अणु
	DEFINE_RES_MEM(EP93XX_I2S_PHYS_BASE, 0x100),
	DEFINE_RES_IRQ(IRQ_EP93XX_SAI),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_i2s_device = अणु
	.name		= "ep93xx-i2s",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ep93xx_i2s_resource),
	.resource	= ep93xx_i2s_resource,
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_pcm_device = अणु
	.name		= "ep93xx-pcm-audio",
	.id		= -1,
पूर्ण;

व्योम __init ep93xx_रेजिस्टर_i2s(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&ep93xx_i2s_device);
	platक्रमm_device_रेजिस्टर(&ep93xx_pcm_device);
पूर्ण

#घोषणा EP93XX_SYSCON_DEVCFG_I2S_MASK	(EP93XX_SYSCON_DEVCFG_I2SONSSP | \
					 EP93XX_SYSCON_DEVCFG_I2SONAC97)

#घोषणा EP93XX_I2SCLKDIV_MASK		(EP93XX_SYSCON_I2SCLKDIV_ORIDE | \
					 EP93XX_SYSCON_I2SCLKDIV_SPOL)

पूर्णांक ep93xx_i2s_acquire(व्योम)
अणु
	अचिन्हित val;

	ep93xx_devcfg_set_clear(EP93XX_SYSCON_DEVCFG_I2SONAC97,
			EP93XX_SYSCON_DEVCFG_I2S_MASK);

	/*
	 * This is potentially racy with the घड़ी api क्रम i2s_mclk, sclk and 
	 * lrclk. Since the i2s driver is the only user of those घड़ीs we
	 * rely on it to prevent parallel use of this function and the 
	 * घड़ी api क्रम the i2s घड़ीs.
	 */
	val = __raw_पढ़ोl(EP93XX_SYSCON_I2SCLKDIV);
	val &= ~EP93XX_I2SCLKDIV_MASK;
	val |= EP93XX_SYSCON_I2SCLKDIV_ORIDE | EP93XX_SYSCON_I2SCLKDIV_SPOL;
	ep93xx_syscon_swlocked_ग_लिखो(val, EP93XX_SYSCON_I2SCLKDIV);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ep93xx_i2s_acquire);

व्योम ep93xx_i2s_release(व्योम)
अणु
	ep93xx_devcfg_clear_bits(EP93XX_SYSCON_DEVCFG_I2S_MASK);
पूर्ण
EXPORT_SYMBOL(ep93xx_i2s_release);

/*************************************************************************
 * EP93xx AC97 audio peripheral handling
 *************************************************************************/
अटल काष्ठा resource ep93xx_ac97_resources[] = अणु
	DEFINE_RES_MEM(EP93XX_AAC_PHYS_BASE, 0xac),
	DEFINE_RES_IRQ(IRQ_EP93XX_AACINTR),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_ac97_device = अणु
	.name		= "ep93xx-ac97",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ep93xx_ac97_resources),
	.resource	= ep93xx_ac97_resources,
पूर्ण;

व्योम __init ep93xx_रेजिस्टर_ac97(व्योम)
अणु
	/*
	 * Make sure that the AC97 pins are not used by I2S.
	 */
	ep93xx_devcfg_clear_bits(EP93XX_SYSCON_DEVCFG_I2SONAC97);

	platक्रमm_device_रेजिस्टर(&ep93xx_ac97_device);
	platक्रमm_device_रेजिस्टर(&ep93xx_pcm_device);
पूर्ण

/*************************************************************************
 * EP93xx Watchकरोg
 *************************************************************************/
अटल काष्ठा resource ep93xx_wdt_resources[] = अणु
	DEFINE_RES_MEM(EP93XX_WATCHDOG_PHYS_BASE, 0x08),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_wdt_device = अणु
	.name		= "ep93xx-wdt",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ep93xx_wdt_resources),
	.resource	= ep93xx_wdt_resources,
पूर्ण;

/*************************************************************************
 * EP93xx IDE
 *************************************************************************/
अटल काष्ठा resource ep93xx_ide_resources[] = अणु
	DEFINE_RES_MEM(EP93XX_IDE_PHYS_BASE, 0x38),
	DEFINE_RES_IRQ(IRQ_EP93XX_EXT3),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_ide_device = अणु
	.name		= "ep93xx-ide",
	.id		= -1,
	.dev		= अणु
		.dma_mask		= &ep93xx_ide_device.dev.coherent_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.num_resources	= ARRAY_SIZE(ep93xx_ide_resources),
	.resource	= ep93xx_ide_resources,
पूर्ण;

व्योम __init ep93xx_रेजिस्टर_ide(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&ep93xx_ide_device);
पूर्ण

पूर्णांक ep93xx_ide_acquire_gpio(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	पूर्णांक i;

	err = gpio_request(EP93XX_GPIO_LINE_EGPIO2, dev_name(&pdev->dev));
	अगर (err)
		वापस err;
	err = gpio_request(EP93XX_GPIO_LINE_EGPIO15, dev_name(&pdev->dev));
	अगर (err)
		जाओ fail_egpio15;
	क्रम (i = 2; i < 8; i++) अणु
		err = gpio_request(EP93XX_GPIO_LINE_E(i), dev_name(&pdev->dev));
		अगर (err)
			जाओ fail_gpio_e;
	पूर्ण
	क्रम (i = 4; i < 8; i++) अणु
		err = gpio_request(EP93XX_GPIO_LINE_G(i), dev_name(&pdev->dev));
		अगर (err)
			जाओ fail_gpio_g;
	पूर्ण
	क्रम (i = 0; i < 8; i++) अणु
		err = gpio_request(EP93XX_GPIO_LINE_H(i), dev_name(&pdev->dev));
		अगर (err)
			जाओ fail_gpio_h;
	पूर्ण

	/* GPIO ports E[7:2], G[7:4] and H used by IDE */
	ep93xx_devcfg_clear_bits(EP93XX_SYSCON_DEVCFG_EONIDE |
				 EP93XX_SYSCON_DEVCFG_GONIDE |
				 EP93XX_SYSCON_DEVCFG_HONIDE);
	वापस 0;

fail_gpio_h:
	क्रम (--i; i >= 0; --i)
		gpio_मुक्त(EP93XX_GPIO_LINE_H(i));
	i = 8;
fail_gpio_g:
	क्रम (--i; i >= 4; --i)
		gpio_मुक्त(EP93XX_GPIO_LINE_G(i));
	i = 8;
fail_gpio_e:
	क्रम (--i; i >= 2; --i)
		gpio_मुक्त(EP93XX_GPIO_LINE_E(i));
	gpio_मुक्त(EP93XX_GPIO_LINE_EGPIO15);
fail_egpio15:
	gpio_मुक्त(EP93XX_GPIO_LINE_EGPIO2);
	वापस err;
पूर्ण
EXPORT_SYMBOL(ep93xx_ide_acquire_gpio);

व्योम ep93xx_ide_release_gpio(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;

	क्रम (i = 2; i < 8; i++)
		gpio_मुक्त(EP93XX_GPIO_LINE_E(i));
	क्रम (i = 4; i < 8; i++)
		gpio_मुक्त(EP93XX_GPIO_LINE_G(i));
	क्रम (i = 0; i < 8; i++)
		gpio_मुक्त(EP93XX_GPIO_LINE_H(i));
	gpio_मुक्त(EP93XX_GPIO_LINE_EGPIO15);
	gpio_मुक्त(EP93XX_GPIO_LINE_EGPIO2);


	/* GPIO ports E[7:2], G[7:4] and H used by GPIO */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_EONIDE |
			       EP93XX_SYSCON_DEVCFG_GONIDE |
			       EP93XX_SYSCON_DEVCFG_HONIDE);
पूर्ण
EXPORT_SYMBOL(ep93xx_ide_release_gpio);

/*************************************************************************
 * EP93xx ADC
 *************************************************************************/
अटल काष्ठा resource ep93xx_adc_resources[] = अणु
	DEFINE_RES_MEM(EP93XX_ADC_PHYS_BASE, 0x28),
	DEFINE_RES_IRQ(IRQ_EP93XX_TOUCH),
पूर्ण;

अटल काष्ठा platक्रमm_device ep93xx_adc_device = अणु
	.name		= "ep93xx-adc",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ep93xx_adc_resources),
	.resource	= ep93xx_adc_resources,
पूर्ण;

व्योम __init ep93xx_रेजिस्टर_adc(व्योम)
अणु
	/* Power up ADC, deactivate Touch Screen Controller */
	ep93xx_devcfg_set_clear(EP93XX_SYSCON_DEVCFG_TIN,
				EP93XX_SYSCON_DEVCFG_ADCPD);

	platक्रमm_device_रेजिस्टर(&ep93xx_adc_device);
पूर्ण

/*************************************************************************
 * EP93xx Security peripheral
 *************************************************************************/

/*
 * The Maverick Key is 256 bits of micro fuses blown at the factory during
 * manufacturing to uniquely identअगरy a part.
 *
 * See: http://arm.cirrus.com/क्रमum/viewtopic.php?t=486&highlight=maverick+key
 */
#घोषणा EP93XX_SECURITY_REG(x)		(EP93XX_SECURITY_BASE + (x))
#घोषणा EP93XX_SECURITY_SECFLG		EP93XX_SECURITY_REG(0x2400)
#घोषणा EP93XX_SECURITY_FUSEFLG		EP93XX_SECURITY_REG(0x2410)
#घोषणा EP93XX_SECURITY_UNIQID		EP93XX_SECURITY_REG(0x2440)
#घोषणा EP93XX_SECURITY_UNIQCHK		EP93XX_SECURITY_REG(0x2450)
#घोषणा EP93XX_SECURITY_UNIQVAL		EP93XX_SECURITY_REG(0x2460)
#घोषणा EP93XX_SECURITY_SECID1		EP93XX_SECURITY_REG(0x2500)
#घोषणा EP93XX_SECURITY_SECID2		EP93XX_SECURITY_REG(0x2504)
#घोषणा EP93XX_SECURITY_SECCHK1		EP93XX_SECURITY_REG(0x2520)
#घोषणा EP93XX_SECURITY_SECCHK2		EP93XX_SECURITY_REG(0x2524)
#घोषणा EP93XX_SECURITY_UNIQID2		EP93XX_SECURITY_REG(0x2700)
#घोषणा EP93XX_SECURITY_UNIQID3		EP93XX_SECURITY_REG(0x2704)
#घोषणा EP93XX_SECURITY_UNIQID4		EP93XX_SECURITY_REG(0x2708)
#घोषणा EP93XX_SECURITY_UNIQID5		EP93XX_SECURITY_REG(0x270c)

अटल अक्षर ep93xx_soc_id[33];

अटल स्थिर अक्षर __init *ep93xx_get_soc_id(व्योम)
अणु
	अचिन्हित पूर्णांक id, id2, id3, id4, id5;

	अगर (__raw_पढ़ोl(EP93XX_SECURITY_UNIQVAL) != 1)
		वापस "bad Hamming code";

	id = __raw_पढ़ोl(EP93XX_SECURITY_UNIQID);
	id2 = __raw_पढ़ोl(EP93XX_SECURITY_UNIQID2);
	id3 = __raw_पढ़ोl(EP93XX_SECURITY_UNIQID3);
	id4 = __raw_पढ़ोl(EP93XX_SECURITY_UNIQID4);
	id5 = __raw_पढ़ोl(EP93XX_SECURITY_UNIQID5);

	अगर (id != id2)
		वापस "invalid";

	/* Toss the unique ID पूर्णांकo the entropy pool */
	add_device_अक्रमomness(&id2, 4);
	add_device_अक्रमomness(&id3, 4);
	add_device_अक्रमomness(&id4, 4);
	add_device_अक्रमomness(&id5, 4);

	snम_लिखो(ep93xx_soc_id, माप(ep93xx_soc_id),
		 "%08x%08x%08x%08x", id2, id3, id4, id5);

	वापस ep93xx_soc_id;
पूर्ण

अटल स्थिर अक्षर __init *ep93xx_get_soc_rev(व्योम)
अणु
	पूर्णांक rev = ep93xx_chip_revision();

	चयन (rev) अणु
	हाल EP93XX_CHIP_REV_D0:
		वापस "D0";
	हाल EP93XX_CHIP_REV_D1:
		वापस "D1";
	हाल EP93XX_CHIP_REV_E0:
		वापस "E0";
	हाल EP93XX_CHIP_REV_E1:
		वापस "E1";
	हाल EP93XX_CHIP_REV_E2:
		वापस "E2";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर __init *ep93xx_get_machine_name(व्योम)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL,"%s", machine_desc->name);
पूर्ण

अटल काष्ठा device __init *ep93xx_init_soc(व्योम)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा soc_device *soc_dev;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस शून्य;

	soc_dev_attr->machine = ep93xx_get_machine_name();
	soc_dev_attr->family = "Cirrus Logic EP93xx";
	soc_dev_attr->revision = ep93xx_get_soc_rev();
	soc_dev_attr->soc_id = ep93xx_get_soc_id();

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr->machine);
		kमुक्त(soc_dev_attr);
		वापस शून्य;
	पूर्ण

	वापस soc_device_to_device(soc_dev);
पूर्ण

काष्ठा device __init *ep93xx_init_devices(व्योम)
अणु
	काष्ठा device *parent;

	/* Disallow access to MaverickCrunch initially */
	ep93xx_devcfg_clear_bits(EP93XX_SYSCON_DEVCFG_CPENA);

	/* Default all ports to GPIO */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_KEYS |
			       EP93XX_SYSCON_DEVCFG_GONK |
			       EP93XX_SYSCON_DEVCFG_EONIDE |
			       EP93XX_SYSCON_DEVCFG_GONIDE |
			       EP93XX_SYSCON_DEVCFG_HONIDE);

	parent = ep93xx_init_soc();

	/* Get the GPIO working early, other devices need it */
	platक्रमm_device_रेजिस्टर(&ep93xx_gpio_device);

	amba_device_रेजिस्टर(&uart1_device, &iomem_resource);
	amba_device_रेजिस्टर(&uart2_device, &iomem_resource);
	amba_device_रेजिस्टर(&uart3_device, &iomem_resource);

	platक्रमm_device_रेजिस्टर(&ep93xx_rtc_device);
	platक्रमm_device_रेजिस्टर(&ep93xx_ohci_device);
	platक्रमm_device_रेजिस्टर(&ep93xx_wdt_device);

	gpio_led_रेजिस्टर_device(-1, &ep93xx_led_data);

	वापस parent;
पूर्ण

व्योम ep93xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	/*
	 * Set then clear the SWRST bit to initiate a software reset
	 */
	ep93xx_devcfg_set_bits(EP93XX_SYSCON_DEVCFG_SWRST);
	ep93xx_devcfg_clear_bits(EP93XX_SYSCON_DEVCFG_SWRST);

	जबतक (1)
		;
पूर्ण

व्योम __init ep93xx_init_late(व्योम)
अणु
	crunch_init();
पूर्ण
