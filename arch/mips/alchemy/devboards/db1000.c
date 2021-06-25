<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DBAu1000/1500/1100 PBAu1100/1500 board support
 *
 * Copyright 2000, 2008 MontaVista Software Inc.
 * Author: MontaVista Software, Inc. <source@mvista.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/leds.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_gpपन.स>
#समावेश <linux/spi/ads7846.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/gpio-au1000.h>
#समावेश <यंत्र/mach-au1x00/au1000_dma.h>
#समावेश <यंत्र/mach-au1x00/au1100_mmc.h>
#समावेश <यंत्र/mach-db1x00/bcsr.h>
#समावेश <यंत्र/reboot.h>
#समावेश <prom.h>
#समावेश "platform.h"

#घोषणा F_SWAPPED (bcsr_पढ़ो(BCSR_STATUS) & BCSR_STATUS_DB1000_SWAPBOOT)

स्थिर अक्षर *get_प्रणाली_type(व्योम);

पूर्णांक __init db1000_board_setup(व्योम)
अणु
	/* initialize board रेजिस्टर space */
	bcsr_init(DB1000_BCSR_PHYS_ADDR,
		  DB1000_BCSR_PHYS_ADDR + DB1000_BCSR_HEXLED_OFS);

	चयन (BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI))) अणु
	हाल BCSR_WHOAMI_DB1000:
	हाल BCSR_WHOAMI_DB1500:
	हाल BCSR_WHOAMI_DB1100:
	हाल BCSR_WHOAMI_PB1500:
	हाल BCSR_WHOAMI_PB1500R2:
	हाल BCSR_WHOAMI_PB1100:
		pr_info("AMD Alchemy %s Board\n", get_प्रणाली_type());
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक db1500_map_pci_irq(स्थिर काष्ठा pci_dev *d, u8 slot, u8 pin)
अणु
	अगर ((slot < 12) || (slot > 13) || pin == 0)
		वापस -1;
	अगर (slot == 12)
		वापस (pin == 1) ? AU1500_PCI_INTA : 0xff;
	अगर (slot == 13) अणु
		चयन (pin) अणु
		हाल 1: वापस AU1500_PCI_INTA;
		हाल 2: वापस AU1500_PCI_INTB;
		हाल 3: वापस AU1500_PCI_INTC;
		हाल 4: वापस AU1500_PCI_INTD;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल u64 au1xxx_all_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा resource alchemy_pci_host_res[] = अणु
	[0] = अणु
		.start	= AU1500_PCI_PHYS_ADDR,
		.end	= AU1500_PCI_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा alchemy_pci_platdata db1500_pci_pd = अणु
	.board_map_irq	= db1500_map_pci_irq,
पूर्ण;

अटल काष्ठा platक्रमm_device db1500_pci_host_dev = अणु
	.dev.platक्रमm_data = &db1500_pci_pd,
	.name		= "alchemy-pci",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(alchemy_pci_host_res),
	.resource	= alchemy_pci_host_res,
पूर्ण;

पूर्णांक __init db1500_pci_setup(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&db1500_pci_host_dev);
पूर्ण

अटल काष्ठा resource au1100_lcd_resources[] = अणु
	[0] = अणु
		.start	= AU1100_LCD_PHYS_ADDR,
		.end	= AU1100_LCD_PHYS_ADDR + 0x800 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1100_LCD_INT,
		.end	= AU1100_LCD_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device au1100_lcd_device = अणु
	.name		= "au1100-lcd",
	.id		= 0,
	.dev = अणु
		.dma_mask		= &au1xxx_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
	.num_resources	= ARRAY_SIZE(au1100_lcd_resources),
	.resource	= au1100_lcd_resources,
पूर्ण;

अटल काष्ठा resource alchemy_ac97c_res[] = अणु
	[0] = अणु
		.start	= AU1000_AC97_PHYS_ADDR,
		.end	= AU1000_AC97_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= DMA_ID_AC97C_TX,
		.end	= DMA_ID_AC97C_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[2] = अणु
		.start	= DMA_ID_AC97C_RX,
		.end	= DMA_ID_AC97C_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device alchemy_ac97c_dev = अणु
	.name		= "alchemy-ac97c",
	.id		= -1,
	.resource	= alchemy_ac97c_res,
	.num_resources	= ARRAY_SIZE(alchemy_ac97c_res),
पूर्ण;

अटल काष्ठा platक्रमm_device alchemy_ac97c_dma_dev = अणु
	.name		= "alchemy-pcm-dma",
	.id		= 0,
पूर्ण;

अटल काष्ठा platक्रमm_device db1x00_codec_dev = अणु
	.name		= "ac97-codec",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device db1x00_audio_dev = अणु
	.name		= "db1000-audio",
	.dev = अणु
		.dma_mask		= &au1xxx_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

/******************************************************************************/

अटल irqवापस_t db1100_mmc_cd(पूर्णांक irq, व्योम *ptr)
अणु
	व्योम (*mmc_cd)(काष्ठा mmc_host *, अचिन्हित दीर्घ);
	/* link against CONFIG_MMC=m */
	mmc_cd = symbol_get(mmc_detect_change);
	mmc_cd(ptr, msecs_to_jअगरfies(500));
	symbol_put(mmc_detect_change);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक db1100_mmc_cd_setup(व्योम *mmc_host, पूर्णांक en)
अणु
	पूर्णांक ret = 0, irq;

	अगर (BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI)) == BCSR_WHOAMI_DB1100)
		irq = AU1100_GPIO19_INT;
	अन्यथा
		irq = AU1100_GPIO14_INT;	/* PB1100 SD0 CD# */

	अगर (en) अणु
		irq_set_irq_type(irq, IRQ_TYPE_EDGE_BOTH);
		ret = request_irq(irq, db1100_mmc_cd, 0,
				  "sd0_cd", mmc_host);
	पूर्ण अन्यथा
		मुक्त_irq(irq, mmc_host);
	वापस ret;
पूर्ण

अटल पूर्णांक db1100_mmc1_cd_setup(व्योम *mmc_host, पूर्णांक en)
अणु
	पूर्णांक ret = 0, irq;

	अगर (BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI)) == BCSR_WHOAMI_DB1100)
		irq = AU1100_GPIO20_INT;
	अन्यथा
		irq = AU1100_GPIO15_INT;	/* PB1100 SD1 CD# */

	अगर (en) अणु
		irq_set_irq_type(irq, IRQ_TYPE_EDGE_BOTH);
		ret = request_irq(irq, db1100_mmc_cd, 0,
				  "sd1_cd", mmc_host);
	पूर्ण अन्यथा
		मुक्त_irq(irq, mmc_host);
	वापस ret;
पूर्ण

अटल पूर्णांक db1100_mmc_card_पढ़ोonly(व्योम *mmc_host)
अणु
	/* testing suggests that this bit is inverted */
	वापस (bcsr_पढ़ो(BCSR_STATUS) & BCSR_STATUS_SD0WP) ? 0 : 1;
पूर्ण

अटल पूर्णांक db1100_mmc_card_inserted(व्योम *mmc_host)
अणु
	वापस !alchemy_gpio_get_value(19);
पूर्ण

अटल व्योम db1100_mmc_set_घातer(व्योम *mmc_host, पूर्णांक state)
अणु
	पूर्णांक bit;

	अगर (BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI)) == BCSR_WHOAMI_DB1100)
		bit = BCSR_BOARD_SD0PWR;
	अन्यथा
		bit = BCSR_BOARD_PB1100_SD0PWR;

	अगर (state) अणु
		bcsr_mod(BCSR_BOARD, 0, bit);
		msleep(400);	/* stabilization समय */
	पूर्ण अन्यथा
		bcsr_mod(BCSR_BOARD, bit, 0);
पूर्ण

अटल व्योम db1100_mmcled_set(काष्ठा led_classdev *led, क्रमागत led_brightness b)
अणु
	अगर (b != LED_OFF)
		bcsr_mod(BCSR_LEDS, BCSR_LEDS_LED0, 0);
	अन्यथा
		bcsr_mod(BCSR_LEDS, 0, BCSR_LEDS_LED0);
पूर्ण

अटल काष्ठा led_classdev db1100_mmc_led = अणु
	.brightness_set = db1100_mmcled_set,
पूर्ण;

अटल पूर्णांक db1100_mmc1_card_पढ़ोonly(व्योम *mmc_host)
अणु
	वापस (bcsr_पढ़ो(BCSR_BOARD) & BCSR_BOARD_SD1WP) ? 1 : 0;
पूर्ण

अटल पूर्णांक db1100_mmc1_card_inserted(व्योम *mmc_host)
अणु
	वापस !alchemy_gpio_get_value(20);
पूर्ण

अटल व्योम db1100_mmc1_set_घातer(व्योम *mmc_host, पूर्णांक state)
अणु
	पूर्णांक bit;

	अगर (BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI)) == BCSR_WHOAMI_DB1100)
		bit = BCSR_BOARD_SD1PWR;
	अन्यथा
		bit = BCSR_BOARD_PB1100_SD1PWR;

	अगर (state) अणु
		bcsr_mod(BCSR_BOARD, 0, bit);
		msleep(400);	/* stabilization समय */
	पूर्ण अन्यथा
		bcsr_mod(BCSR_BOARD, bit, 0);
पूर्ण

अटल व्योम db1100_mmc1led_set(काष्ठा led_classdev *led, क्रमागत led_brightness b)
अणु
	अगर (b != LED_OFF)
		bcsr_mod(BCSR_LEDS, BCSR_LEDS_LED1, 0);
	अन्यथा
		bcsr_mod(BCSR_LEDS, 0, BCSR_LEDS_LED1);
पूर्ण

अटल काष्ठा led_classdev db1100_mmc1_led = अणु
	.brightness_set = db1100_mmc1led_set,
पूर्ण;

अटल काष्ठा au1xmmc_platक्रमm_data db1100_mmc_platdata[2] = अणु
	[0] = अणु
		.cd_setup	= db1100_mmc_cd_setup,
		.set_घातer	= db1100_mmc_set_घातer,
		.card_inserted	= db1100_mmc_card_inserted,
		.card_पढ़ोonly	= db1100_mmc_card_पढ़ोonly,
		.led		= &db1100_mmc_led,
	पूर्ण,
	[1] = अणु
		.cd_setup	= db1100_mmc1_cd_setup,
		.set_घातer	= db1100_mmc1_set_घातer,
		.card_inserted	= db1100_mmc1_card_inserted,
		.card_पढ़ोonly	= db1100_mmc1_card_पढ़ोonly,
		.led		= &db1100_mmc1_led,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource au1100_mmc0_resources[] = अणु
	[0] = अणु
		.start	= AU1100_SD0_PHYS_ADDR,
		.end	= AU1100_SD0_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1100_SD_INT,
		.end	= AU1100_SD_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= DMA_ID_SD0_TX,
		.end	= DMA_ID_SD0_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= DMA_ID_SD0_RX,
		.end	= DMA_ID_SD0_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device db1100_mmc0_dev = अणु
	.name		= "au1xxx-mmc",
	.id		= 0,
	.dev = अणु
		.dma_mask		= &au1xxx_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &db1100_mmc_platdata[0],
	पूर्ण,
	.num_resources	= ARRAY_SIZE(au1100_mmc0_resources),
	.resource	= au1100_mmc0_resources,
पूर्ण;

अटल काष्ठा resource au1100_mmc1_res[] = अणु
	[0] = अणु
		.start	= AU1100_SD1_PHYS_ADDR,
		.end	= AU1100_SD1_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= AU1100_SD_INT,
		.end	= AU1100_SD_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= DMA_ID_SD1_TX,
		.end	= DMA_ID_SD1_TX,
		.flags	= IORESOURCE_DMA,
	पूर्ण,
	[3] = अणु
		.start	= DMA_ID_SD1_RX,
		.end	= DMA_ID_SD1_RX,
		.flags	= IORESOURCE_DMA,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device db1100_mmc1_dev = अणु
	.name		= "au1xxx-mmc",
	.id		= 1,
	.dev = अणु
		.dma_mask		= &au1xxx_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &db1100_mmc_platdata[1],
	पूर्ण,
	.num_resources	= ARRAY_SIZE(au1100_mmc1_res),
	.resource	= au1100_mmc1_res,
पूर्ण;

/******************************************************************************/

अटल काष्ठा ads7846_platक्रमm_data db1100_touch_pd = अणु
	.model		= 7846,
	.vref_mv	= 3300,
	.gpio_penकरोwn	= 21,
पूर्ण;

अटल काष्ठा spi_gpio_platक्रमm_data db1100_spictl_pd = अणु
	.num_chipselect = 1,
पूर्ण;

अटल काष्ठा spi_board_info db1100_spi_info[] __initdata = अणु
	[0] = अणु
		.modalias	 = "ads7846",
		.max_speed_hz	 = 3250000,
		.bus_num	 = 0,
		.chip_select	 = 0,
		.mode		 = 0,
		.irq		 = AU1100_GPIO21_INT,
		.platक्रमm_data	 = &db1100_touch_pd,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device db1100_spi_dev = अणु
	.name		= "spi_gpio",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &db1100_spictl_pd,
		.dma_mask		= &au1xxx_all_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

/*
 * Alchemy GPIO 2 has its base at 200 so the GPIO lines
 * 207 thru 210 are GPIOs at offset 7 thru 10 at this chip.
 */
अटल काष्ठा gpiod_lookup_table db1100_spi_gpiod_table = अणु
	.dev_id         = "spi_gpio",
	.table          = अणु
		GPIO_LOOKUP("alchemy-gpio2", 9,
			    "sck", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("alchemy-gpio2", 8,
			    "mosi", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("alchemy-gpio2", 7,
			    "miso", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("alchemy-gpio2", 10,
			    "cs", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *db1x00_devs[] = अणु
	&db1x00_codec_dev,
	&alchemy_ac97c_dma_dev,
	&alchemy_ac97c_dev,
	&db1x00_audio_dev,
पूर्ण;

अटल काष्ठा platक्रमm_device *db1100_devs[] = अणु
	&au1100_lcd_device,
	&db1100_mmc0_dev,
	&db1100_mmc1_dev,
पूर्ण;

पूर्णांक __init db1000_dev_setup(व्योम)
अणु
	पूर्णांक board = BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI));
	पूर्णांक c0, c1, d0, d1, s0, s1, flashsize = 32,  twosocks = 1;
	अचिन्हित दीर्घ pfc;
	काष्ठा clk *c, *p;

	अगर (board == BCSR_WHOAMI_DB1500) अणु
		c0 = AU1500_GPIO2_INT;
		c1 = AU1500_GPIO5_INT;
		d0 = 0;	/* GPIO number, NOT irq! */
		d1 = 3; /* GPIO number, NOT irq! */
		s0 = AU1500_GPIO1_INT;
		s1 = AU1500_GPIO4_INT;
	पूर्ण अन्यथा अगर (board == BCSR_WHOAMI_DB1100) अणु
		c0 = AU1100_GPIO2_INT;
		c1 = AU1100_GPIO5_INT;
		d0 = 0; /* GPIO number, NOT irq! */
		d1 = 3; /* GPIO number, NOT irq! */
		s0 = AU1100_GPIO1_INT;
		s1 = AU1100_GPIO4_INT;

		gpio_request(19, "sd0_cd");
		gpio_request(20, "sd1_cd");
		gpio_direction_input(19);	/* sd0 cd# */
		gpio_direction_input(20);	/* sd1 cd# */

		/* spi_gpio on SSI0 pins */
		pfc = alchemy_rdsys(AU1000_SYS_PINFUNC);
		pfc |= (1 << 0);	/* SSI0 pins as GPIOs */
		alchemy_wrsys(pfc, AU1000_SYS_PINFUNC);

		spi_रेजिस्टर_board_info(db1100_spi_info,
					ARRAY_SIZE(db1100_spi_info));

		/* link LCD घड़ी to AUXPLL */
		p = clk_get(शून्य, "auxpll_clk");
		c = clk_get(शून्य, "lcd_intclk");
		अगर (!IS_ERR(c) && !IS_ERR(p)) अणु
			clk_set_parent(c, p);
			clk_set_rate(c, clk_get_rate(p));
		पूर्ण
		अगर (!IS_ERR(c))
			clk_put(c);
		अगर (!IS_ERR(p))
			clk_put(p);

		platक्रमm_add_devices(db1100_devs, ARRAY_SIZE(db1100_devs));
		gpiod_add_lookup_table(&db1100_spi_gpiod_table);
		platक्रमm_device_रेजिस्टर(&db1100_spi_dev);
	पूर्ण अन्यथा अगर (board == BCSR_WHOAMI_DB1000) अणु
		c0 = AU1000_GPIO2_INT;
		c1 = AU1000_GPIO5_INT;
		d0 = 0; /* GPIO number, NOT irq! */
		d1 = 3; /* GPIO number, NOT irq! */
		s0 = AU1000_GPIO1_INT;
		s1 = AU1000_GPIO4_INT;
	पूर्ण अन्यथा अगर ((board == BCSR_WHOAMI_PB1500) ||
		   (board == BCSR_WHOAMI_PB1500R2)) अणु
		c0 = AU1500_GPIO203_INT;
		d0 = 1; /* GPIO number, NOT irq! */
		s0 = AU1500_GPIO202_INT;
		twosocks = 0;
		flashsize = 64;
		/* RTC and daughtercard irqs */
		irq_set_irq_type(AU1500_GPIO204_INT, IRQ_TYPE_LEVEL_LOW);
		irq_set_irq_type(AU1500_GPIO205_INT, IRQ_TYPE_LEVEL_LOW);
		/* EPSON S1D13806 0x1b000000
		 * SRAM 1MB/2MB	  0x1a000000
		 * DS1693 RTC	  0x0c000000
		 */
	पूर्ण अन्यथा अगर (board == BCSR_WHOAMI_PB1100) अणु
		c0 = AU1100_GPIO11_INT;
		d0 = 9; /* GPIO number, NOT irq! */
		s0 = AU1100_GPIO10_INT;
		twosocks = 0;
		flashsize = 64;
		/* penकरोwn, rtc, daughtercard irqs */
		irq_set_irq_type(AU1100_GPIO8_INT, IRQ_TYPE_LEVEL_LOW);
		irq_set_irq_type(AU1100_GPIO12_INT, IRQ_TYPE_LEVEL_LOW);
		irq_set_irq_type(AU1100_GPIO13_INT, IRQ_TYPE_LEVEL_LOW);
		/* EPSON S1D13806 0x1b000000
		 * SRAM 1MB/2MB	  0x1a000000
		 * DiskOnChip	  0x0d000000
		 * DS1693 RTC	  0x0c000000
		 */
		platक्रमm_add_devices(db1100_devs, ARRAY_SIZE(db1100_devs));
	पूर्ण अन्यथा
		वापस 0; /* unknown board, no further dev setup to करो */

	irq_set_irq_type(c0, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(s0, IRQ_TYPE_LEVEL_LOW);

	db1x_रेजिस्टर_pcmcia_socket(
		AU1000_PCMCIA_ATTR_PHYS_ADDR,
		AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x000400000 - 1,
		AU1000_PCMCIA_MEM_PHYS_ADDR,
		AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x000400000 - 1,
		AU1000_PCMCIA_IO_PHYS_ADDR,
		AU1000_PCMCIA_IO_PHYS_ADDR   + 0x000010000 - 1,
		c0, d0, /*s0*/0, 0, 0);

	अगर (twosocks) अणु
		irq_set_irq_type(c1, IRQ_TYPE_LEVEL_LOW);
		irq_set_irq_type(s1, IRQ_TYPE_LEVEL_LOW);

		db1x_रेजिस्टर_pcmcia_socket(
			AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x004000000,
			AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x004400000 - 1,
			AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x004000000,
			AU1000_PCMCIA_MEM_PHYS_ADDR  + 0x004400000 - 1,
			AU1000_PCMCIA_IO_PHYS_ADDR   + 0x004000000,
			AU1000_PCMCIA_IO_PHYS_ADDR   + 0x004010000 - 1,
			c1, d1, /*s1*/0, 0, 1);
	पूर्ण

	platक्रमm_add_devices(db1x00_devs, ARRAY_SIZE(db1x00_devs));
	db1x_रेजिस्टर_norflash(flashsize << 20, 4 /* 32bit */, F_SWAPPED);
	वापस 0;
पूर्ण
