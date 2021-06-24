<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009 Renesas Solutions Corp.
 *
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 */
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/heartbeat.h>
#समावेश <यंत्र/suspend.h>
#समावेश <cpu/sh7724.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sh_keysc.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sh_mmcअगर.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/platक्रमm_data/gpio_backlight.h>
#समावेश <linux/platक्रमm_data/tsc2007.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/sh_eth.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/spi/mmc_spi.h>
#समावेश <linux/spi/sh_msiof.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/usb/r8a66597.h>
#समावेश <linux/usb/renesas_usbhs.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/dma-map-ops.h>

#समावेश <media/drv-पूर्णांकf/renesas-ceu.h>
#समावेश <media/i2c/mt9t112.h>
#समावेश <media/i2c/tw9910.h>

#समावेश <sound/sh_fsi.h>
#समावेश <sound/simple_card.h>

#समावेश <video/sh_mobile_lcdc.h>

/*
 *  Address      Interface        BusWidth
 *-----------------------------------------
 *  0x0000_0000  uboot            16bit
 *  0x0004_0000  Linux romImage   16bit
 *  0x0014_0000  MTD क्रम Linux    16bit
 *  0x0400_0000  Internal I/O     16/32bit
 *  0x0800_0000  DRAM             32bit
 *  0x1800_0000  MFI              16bit
 */

/* SWITCH
 *------------------------------
 * DS2[1] = FlashROM ग_लिखो protect  ON     : ग_लिखो protect
 *                                  OFF    : No ग_लिखो protect
 * DS2[2] = RMII / TS, SCIF         ON     : RMII
 *                                  OFF    : TS, SCIF3
 * DS2[3] = Camera / Video          ON     : Camera
 *                                  OFF    : NTSC/PAL (IN)
 * DS2[5] = NTSC_OUT Clock          ON     : On board OSC
 *                                  OFF    : SH7724 DV_CLK
 * DS2[6-7] = MMC / SD              ON-OFF : SD
 *                                  OFF-ON : MMC
 */

/*
 * FSI - DA7210
 *
 * it needs amixer settings क्रम playing
 *
 * amixer set 'HeadPhone' 80
 * amixer set 'Out Mixer Left DAC Left' on
 * amixer set 'Out Mixer Right DAC Right' on
 */

#घोषणा CEU_BUFFER_MEMORY_SIZE		(4 << 20)
अटल phys_addr_t ceu0_dma_membase;
अटल phys_addr_t ceu1_dma_membase;

/* Heartbeat */
अटल अचिन्हित अक्षर led_pos[] = अणु 0, 1, 2, 3 पूर्ण;

अटल काष्ठा heartbeat_data heartbeat_data = अणु
	.nr_bits = 4,
	.bit_pos = led_pos,
पूर्ण;

अटल काष्ठा resource heartbeat_resource = अणु
	.start  = 0xA405012C, /* PTG */
	.end    = 0xA405012E - 1,
	.flags  = IORESOURCE_MEM | IORESOURCE_MEM_8BIT,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name           = "heartbeat",
	.id             = -1,
	.dev = अणु
		.platक्रमm_data = &heartbeat_data,
	पूर्ण,
	.num_resources  = 1,
	.resource       = &heartbeat_resource,
पूर्ण;

/* MTD */
अटल काष्ठा mtd_partition nor_flash_partitions[] = अणु
	अणु
		.name = "boot loader",
		.offset = 0,
		.size = (5 * 1024 * 1024),
		.mask_flags = MTD_WRITEABLE,  /* क्रमce पढ़ो-only */
	पूर्ण, अणु
		.name = "free-area",
		.offset = MTDPART_OFS_APPEND,
		.size = MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data nor_flash_data = अणु
	.width		= 2,
	.parts		= nor_flash_partitions,
	.nr_parts	= ARRAY_SIZE(nor_flash_partitions),
पूर्ण;

अटल काष्ठा resource nor_flash_resources[] = अणु
	[0] = अणु
		.name	= "NOR Flash",
		.start	= 0x00000000,
		.end	= 0x03ffffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device nor_flash_device = अणु
	.name		= "physmap-flash",
	.resource	= nor_flash_resources,
	.num_resources	= ARRAY_SIZE(nor_flash_resources),
	.dev		= अणु
		.platक्रमm_data = &nor_flash_data,
	पूर्ण,
पूर्ण;

/* SH Eth */
#घोषणा SH_ETH_ADDR	(0xA4600000)
अटल काष्ठा resource sh_eth_resources[] = अणु
	[0] = अणु
		.start = SH_ETH_ADDR,
		.end   = SH_ETH_ADDR + 0x1FC,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = evt2irq(0xd60),
		.flags = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_eth_plat_data sh_eth_plat = अणु
	.phy = 0x1f, /* SMSC LAN8700 */
	.phy_पूर्णांकerface = PHY_INTERFACE_MODE_MII,
	.ether_link_active_low = 1
पूर्ण;

अटल काष्ठा platक्रमm_device sh_eth_device = अणु
	.name = "sh7724-ether",
	.id = 0,
	.dev = अणु
		.platक्रमm_data = &sh_eth_plat,
	पूर्ण,
	.num_resources = ARRAY_SIZE(sh_eth_resources),
	.resource = sh_eth_resources,
पूर्ण;

/* USB0 host */
अटल व्योम usb0_port_घातer(पूर्णांक port, पूर्णांक घातer)
अणु
	gpio_set_value(GPIO_PTB4, घातer);
पूर्ण

अटल काष्ठा r8a66597_platdata usb0_host_data = अणु
	.on_chip = 1,
	.port_घातer = usb0_port_घातer,
पूर्ण;

अटल काष्ठा resource usb0_host_resources[] = अणु
	[0] = अणु
		.start	= 0xa4d80000,
		.end	= 0xa4d80124 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xa20),
		.end	= evt2irq(0xa20),
		.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_LOW,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device usb0_host_device = अणु
	.name		= "r8a66597_hcd",
	.id		= 0,
	.dev = अणु
		.dma_mask		= शून्य,         /*  not use dma */
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &usb0_host_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(usb0_host_resources),
	.resource	= usb0_host_resources,
पूर्ण;

/* USB1 host/function */
अटल व्योम usb1_port_घातer(पूर्णांक port, पूर्णांक घातer)
अणु
	gpio_set_value(GPIO_PTB5, घातer);
पूर्ण

अटल काष्ठा r8a66597_platdata usb1_common_data = अणु
	.on_chip = 1,
	.port_घातer = usb1_port_घातer,
पूर्ण;

अटल काष्ठा resource usb1_common_resources[] = अणु
	[0] = अणु
		.start	= 0xa4d90000,
		.end	= 0xa4d90124 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xa40),
		.end	= evt2irq(0xa40),
		.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_LOW,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device usb1_common_device = अणु
	/* .name will be added in arch_setup */
	.id		= 1,
	.dev = अणु
		.dma_mask		= शून्य,         /*  not use dma */
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &usb1_common_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(usb1_common_resources),
	.resource	= usb1_common_resources,
पूर्ण;

/*
 * USBHS
 */
अटल पूर्णांक usbhs_get_id(काष्ठा platक्रमm_device *pdev)
अणु
	वापस gpio_get_value(GPIO_PTB3);
पूर्ण

अटल पूर्णांक usbhs_phy_reset(काष्ठा platक्रमm_device *pdev)
अणु
	/* enable vbus अगर HOST */
	अगर (!gpio_get_value(GPIO_PTB3))
		gpio_set_value(GPIO_PTB5, 1);

	वापस 0;
पूर्ण

अटल काष्ठा renesas_usbhs_platक्रमm_info usbhs_info = अणु
	.platक्रमm_callback = अणु
		.get_id		= usbhs_get_id,
		.phy_reset	= usbhs_phy_reset,
	पूर्ण,
	.driver_param = अणु
		.busरुको_bरुको		= 4,
		.detection_delay	= 5,
		.d0_tx_id = SHDMA_SLAVE_USB1D0_TX,
		.d0_rx_id = SHDMA_SLAVE_USB1D0_RX,
		.d1_tx_id = SHDMA_SLAVE_USB1D1_TX,
		.d1_rx_id = SHDMA_SLAVE_USB1D1_RX,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource usbhs_resources[] = अणु
	[0] = अणु
		.start	= 0xa4d90000,
		.end	= 0xa4d90124 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xa40),
		.end	= evt2irq(0xa40),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device usbhs_device = अणु
	.name	= "renesas_usbhs",
	.id	= 1,
	.dev = अणु
		.dma_mask		= शून्य,         /*  not use dma */
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &usbhs_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(usbhs_resources),
	.resource	= usbhs_resources,
पूर्ण;

/* LCDC and backlight */
अटल स्थिर काष्ठा fb_videomode ecovec_lcd_modes[] = अणु
	अणु
		.name		= "Panel",
		.xres		= 800,
		.yres		= 480,
		.left_margin	= 220,
		.right_margin	= 110,
		.hsync_len	= 70,
		.upper_margin	= 20,
		.lower_margin	= 5,
		.vsync_len	= 5,
		.sync		= 0, /* hsync and vsync are active low */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा fb_videomode ecovec_dvi_modes[] = अणु
	अणु
		.name		= "DVI",
		.xres		= 1280,
		.yres		= 720,
		.left_margin	= 220,
		.right_margin	= 110,
		.hsync_len	= 40,
		.upper_margin	= 20,
		.lower_margin	= 5,
		.vsync_len	= 5,
		.sync = 0, /* hsync and vsync are active low */
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_mobile_lcdc_info lcdc_info = अणु
	.ch[0] = अणु
		.पूर्णांकerface_type = RGB18,
		.chan = LCDC_CHAN_MAINLCD,
		.fourcc = V4L2_PIX_FMT_RGB565,
		.panel_cfg = अणु /* 7.0 inch */
			.width = 152,
			.height = 91,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा resource lcdc_resources[] = अणु
	[0] = अणु
		.name	= "LCDC",
		.start	= 0xfe940000,
		.end	= 0xfe942fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xf40),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device lcdc_device = अणु
	.name		= "sh_mobile_lcdc_fb",
	.num_resources	= ARRAY_SIZE(lcdc_resources),
	.resource	= lcdc_resources,
	.dev		= अणु
		.platक्रमm_data	= &lcdc_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table gpio_backlight_lookup = अणु
	.dev_id		= "gpio-backlight.0",
	.table = अणु
		GPIO_LOOKUP("sh7724_pfc", GPIO_PTR1, शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा property_entry gpio_backlight_props[] = अणु
	PROPERTY_ENTRY_BOOL("default-on"),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा gpio_backlight_platक्रमm_data gpio_backlight_data = अणु
	.fbdev = &lcdc_device.dev,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info gpio_backlight_device_info = अणु
	.name = "gpio-backlight",
	.data = &gpio_backlight_data,
	.size_data = माप(gpio_backlight_data),
	.properties = gpio_backlight_props,
पूर्ण;

अटल काष्ठा platक्रमm_device *gpio_backlight_device;

/* CEU0 */
अटल काष्ठा ceu_platक्रमm_data ceu0_pdata = अणु
	.num_subdevs			= 2,
	.subdevs = अणु
		अणु /* [0] = mt9t112  */
			.flags		= 0,
			.bus_width	= 8,
			.bus_shअगरt	= 0,
			.i2c_adapter_id	= 0,
			.i2c_address	= 0x3c,
		पूर्ण,
		अणु /* [1] = tw9910  */
			.flags		= 0,
			.bus_width	= 8,
			.bus_shअगरt	= 0,
			.i2c_adapter_id	= 0,
			.i2c_address	= 0x45,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource ceu0_resources[] = अणु
	[0] = अणु
		.name	= "CEU0",
		.start	= 0xfe910000,
		.end	= 0xfe91009f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0x880),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ceu0_device = अणु
	.name		= "renesas-ceu",
	.id             = 0, /* ceu.0 */
	.num_resources	= ARRAY_SIZE(ceu0_resources),
	.resource	= ceu0_resources,
	.dev	= अणु
		.platक्रमm_data	= &ceu0_pdata,
	पूर्ण,
पूर्ण;

/* CEU1 */
अटल काष्ठा ceu_platक्रमm_data ceu1_pdata = अणु
	.num_subdevs			= 1,
	.subdevs = अणु
		अणु /* [0] = mt9t112  */
			.flags		= 0,
			.bus_width	= 8,
			.bus_shअगरt	= 0,
			.i2c_adapter_id	= 1,
			.i2c_address	= 0x3c,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource ceu1_resources[] = अणु
	[0] = अणु
		.name	= "CEU1",
		.start	= 0xfe914000,
		.end	= 0xfe91409f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0x9e0),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ceu1_device = अणु
	.name		= "renesas-ceu",
	.id             = 1, /* ceu.1 */
	.num_resources	= ARRAY_SIZE(ceu1_resources),
	.resource	= ceu1_resources,
	.dev	= अणु
		.platक्रमm_data	= &ceu1_pdata,
	पूर्ण,
पूर्ण;

/* Power up/करोwn GPIOs क्रम camera devices and video decoder */
अटल काष्ठा gpiod_lookup_table tw9910_gpios = अणु
	.dev_id		= "0-0045",
	.table		= अणु
		GPIO_LOOKUP("sh7724_pfc", GPIO_PTU2, "pdn", GPIO_ACTIVE_HIGH),
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table mt9t112_0_gpios = अणु
	.dev_id		= "0-003c",
	.table		= अणु
		GPIO_LOOKUP("sh7724_pfc", GPIO_PTA3, "standby",
			    GPIO_ACTIVE_HIGH),
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table mt9t112_1_gpios = अणु
	.dev_id		= "1-003c",
	.table		= अणु
		GPIO_LOOKUP("sh7724_pfc", GPIO_PTA4, "standby",
			    GPIO_ACTIVE_HIGH),
	पूर्ण,
पूर्ण;

/* I2C device */
अटल काष्ठा tw9910_video_info tw9910_info = अणु
	.buswidth	= 8,
	.mpout		= TW9910_MPO_FIELD,
पूर्ण;

अटल काष्ठा mt9t112_platक्रमm_data mt9t112_0_pdata = अणु
	.flags = MT9T112_FLAG_PCLK_RISING_EDGE,
	.भागider = अणु 0x49, 0x6, 0, 6, 0, 9, 9, 6, 0 पूर्ण, /* क्रम 24MHz */
पूर्ण;

अटल काष्ठा mt9t112_platक्रमm_data mt9t112_1_pdata = अणु
	.flags = MT9T112_FLAG_PCLK_RISING_EDGE,
	.भागider = अणु 0x49, 0x6, 0, 6, 0, 9, 9, 6, 0 पूर्ण, /* क्रम 24MHz */
पूर्ण;

अटल काष्ठा i2c_board_info i2c0_devices[] = अणु
	अणु
		I2C_BOARD_INFO("da7210", 0x1a),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("tw9910", 0x45),
		.platक्रमm_data = &tw9910_info,
	पूर्ण,
	अणु
		/* 1st camera */
		I2C_BOARD_INFO("mt9t112", 0x3c),
		.platक्रमm_data = &mt9t112_0_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info i2c1_devices[] = अणु
	अणु
		I2C_BOARD_INFO("r2025sd", 0x32),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("lis3lv02d", 0x1c),
		.irq = evt2irq(0x620),
	पूर्ण,
	अणु
		/* 2nd camera */
		I2C_BOARD_INFO("mt9t112", 0x3c),
		.platक्रमm_data = &mt9t112_1_pdata,
	पूर्ण,
पूर्ण;

/* KEYSC */
अटल काष्ठा sh_keysc_info keysc_info = अणु
	.mode		= SH_KEYSC_MODE_1,
	.scan_timing	= 3,
	.delay		= 50,
	.kycr2_delay	= 100,
	.keycodes	= अणु KEY_1, 0, 0, 0, 0,
			    KEY_2, 0, 0, 0, 0,
			    KEY_3, 0, 0, 0, 0,
			    KEY_4, 0, 0, 0, 0,
			    KEY_5, 0, 0, 0, 0,
			    KEY_6, 0, 0, 0, 0, पूर्ण,
पूर्ण;

अटल काष्ठा resource keysc_resources[] = अणु
	[0] = अणु
		.name	= "KEYSC",
		.start  = 0x044b0000,
		.end    = 0x044b000f,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0xbe0),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device keysc_device = अणु
	.name           = "sh_keysc",
	.id             = 0, /* keysc0 घड़ी */
	.num_resources  = ARRAY_SIZE(keysc_resources),
	.resource       = keysc_resources,
	.dev	= अणु
		.platक्रमm_data	= &keysc_info,
	पूर्ण,
पूर्ण;

/* TouchScreen */
#घोषणा IRQ0 evt2irq(0x600)

अटल पूर्णांक ts_get_penकरोwn_state(काष्ठा device *dev)
अणु
	पूर्णांक val = 0;
	gpio_मुक्त(GPIO_FN_INTC_IRQ0);
	gpio_request(GPIO_PTZ0, शून्य);
	gpio_direction_input(GPIO_PTZ0);

	val = gpio_get_value(GPIO_PTZ0);

	gpio_मुक्त(GPIO_PTZ0);
	gpio_request(GPIO_FN_INTC_IRQ0, शून्य);

	वापस val ? 0 : 1;
पूर्ण

अटल पूर्णांक ts_init(व्योम)
अणु
	gpio_request(GPIO_FN_INTC_IRQ0, शून्य);
	वापस 0;
पूर्ण

अटल काष्ठा tsc2007_platक्रमm_data tsc2007_info = अणु
	.model			= 2007,
	.x_plate_ohms		= 180,
	.get_penकरोwn_state	= ts_get_penकरोwn_state,
	.init_platक्रमm_hw	= ts_init,
पूर्ण;

अटल काष्ठा i2c_board_info ts_i2c_clients = अणु
	I2C_BOARD_INFO("tsc2007", 0x48),
	.type		= "tsc2007",
	.platक्रमm_data	= &tsc2007_info,
	.irq		= IRQ0,
पूर्ण;

अटल काष्ठा regulator_consumer_supply cn12_घातer_consumers[] =
अणु
	REGULATOR_SUPPLY("vmmc", "sh_mmcif.0"),
	REGULATOR_SUPPLY("vqmmc", "sh_mmcif.0"),
	REGULATOR_SUPPLY("vmmc", "sh_mobile_sdhi.1"),
	REGULATOR_SUPPLY("vqmmc", "sh_mobile_sdhi.1"),
पूर्ण;

अटल काष्ठा regulator_init_data cn12_घातer_init_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.num_consumer_supplies  = ARRAY_SIZE(cn12_घातer_consumers),
	.consumer_supplies      = cn12_घातer_consumers,
पूर्ण;

अटल काष्ठा fixed_voltage_config cn12_घातer_info = अणु
	.supply_name = "CN12 SD/MMC Vdd",
	.microvolts = 3300000,
	.init_data = &cn12_घातer_init_data,
पूर्ण;

अटल काष्ठा platक्रमm_device cn12_घातer = अणु
	.name = "reg-fixed-voltage",
	.id   = 0,
	.dev  = अणु
		.platक्रमm_data = &cn12_घातer_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table cn12_घातer_gpiod_table = अणु
	.dev_id = "reg-fixed-voltage.0",
	.table = अणु
		/* Offset 7 on port B */
		GPIO_LOOKUP("sh7724_pfc", GPIO_PTB7,
			    शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

#अगर defined(CONFIG_MMC_SDHI) || defined(CONFIG_MMC_SDHI_MODULE)
/* SDHI0 */
अटल काष्ठा regulator_consumer_supply sdhi0_घातer_consumers[] =
अणु
	REGULATOR_SUPPLY("vmmc", "sh_mobile_sdhi.0"),
	REGULATOR_SUPPLY("vqmmc", "sh_mobile_sdhi.0"),
पूर्ण;

अटल काष्ठा regulator_init_data sdhi0_घातer_init_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.num_consumer_supplies  = ARRAY_SIZE(sdhi0_घातer_consumers),
	.consumer_supplies      = sdhi0_घातer_consumers,
पूर्ण;

अटल काष्ठा fixed_voltage_config sdhi0_घातer_info = अणु
	.supply_name = "CN11 SD/MMC Vdd",
	.microvolts = 3300000,
	.init_data = &sdhi0_घातer_init_data,
पूर्ण;

अटल काष्ठा platक्रमm_device sdhi0_घातer = अणु
	.name = "reg-fixed-voltage",
	.id   = 1,
	.dev  = अणु
		.platक्रमm_data = &sdhi0_घातer_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table sdhi0_घातer_gpiod_table = अणु
	.dev_id = "reg-fixed-voltage.1",
	.table = अणु
		/* Offset 6 on port B */
		GPIO_LOOKUP("sh7724_pfc", GPIO_PTB6,
			    शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table sdhi0_gpio_table = अणु
	.dev_id = "sh_mobile_sdhi.0",
	.table = अणु
		/* Card detect */
		GPIO_LOOKUP("sh7724_pfc", GPIO_PTY7, "cd", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा पंचांगio_mmc_data sdhi0_info = अणु
	.chan_priv_tx	= (व्योम *)SHDMA_SLAVE_SDHI0_TX,
	.chan_priv_rx	= (व्योम *)SHDMA_SLAVE_SDHI0_RX,
	.capabilities	= MMC_CAP_SDIO_IRQ | MMC_CAP_POWER_OFF_CARD |
			  MMC_CAP_NEEDS_POLL,
पूर्ण;

अटल काष्ठा resource sdhi0_resources[] = अणु
	[0] = अणु
		.name	= "SDHI0",
		.start  = 0x04ce0000,
		.end    = 0x04ce00ff,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0xe80),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sdhi0_device = अणु
	.name           = "sh_mobile_sdhi",
	.num_resources  = ARRAY_SIZE(sdhi0_resources),
	.resource       = sdhi0_resources,
	.id             = 0,
	.dev	= अणु
		.platक्रमm_data	= &sdhi0_info,
	पूर्ण,
पूर्ण;

#अगर !defined(CONFIG_MMC_SH_MMCIF) && !defined(CONFIG_MMC_SH_MMCIF_MODULE)
/* SDHI1 */
अटल काष्ठा पंचांगio_mmc_data sdhi1_info = अणु
	.chan_priv_tx	= (व्योम *)SHDMA_SLAVE_SDHI1_TX,
	.chan_priv_rx	= (व्योम *)SHDMA_SLAVE_SDHI1_RX,
	.capabilities	= MMC_CAP_SDIO_IRQ | MMC_CAP_POWER_OFF_CARD |
			  MMC_CAP_NEEDS_POLL,
पूर्ण;

अटल काष्ठा gpiod_lookup_table sdhi1_gpio_table = अणु
	.dev_id = "sh_mobile_sdhi.1",
	.table = अणु
		/* Card detect */
		GPIO_LOOKUP("sh7724_pfc", GPIO_PTW7, "cd", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sdhi1_resources[] = अणु
	[0] = अणु
		.name	= "SDHI1",
		.start  = 0x04cf0000,
		.end    = 0x04cf00ff,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0x4e0),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sdhi1_device = अणु
	.name           = "sh_mobile_sdhi",
	.num_resources  = ARRAY_SIZE(sdhi1_resources),
	.resource       = sdhi1_resources,
	.id             = 1,
	.dev	= अणु
		.platक्रमm_data	= &sdhi1_info,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_MMC_SH_MMCIF */

#अन्यथा

/* MMC SPI */
अटल व्योम mmc_spi_setघातer(काष्ठा device *dev, अचिन्हित पूर्णांक maskval)
अणु
	gpio_set_value(GPIO_PTB6, maskval ? 1 : 0);
पूर्ण

अटल काष्ठा mmc_spi_platक्रमm_data mmc_spi_info = अणु
	.caps = MMC_CAP_NEEDS_POLL,
	.caps2 = MMC_CAP2_RO_ACTIVE_HIGH,
	.ocr_mask = MMC_VDD_32_33 | MMC_VDD_33_34, /* 3.3V only */
	.setघातer = mmc_spi_setघातer,
पूर्ण;

अटल काष्ठा gpiod_lookup_table mmc_spi_gpio_table = अणु
	.dev_id = "mmc_spi.0", /* device "mmc_spi" @ CS0 */
	.table = अणु
		/* Card detect */
		GPIO_LOOKUP_IDX("sh7724_pfc", GPIO_PTY7, शून्य, 0,
				GPIO_ACTIVE_LOW),
		/* Write protect */
		GPIO_LOOKUP_IDX("sh7724_pfc", GPIO_PTY6, शून्य, 1,
				GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spi_board_info spi_bus[] = अणु
	अणु
		.modalias	= "mmc_spi",
		.platक्रमm_data	= &mmc_spi_info,
		.max_speed_hz	= 5000000,
		.mode		= SPI_MODE_0,
	पूर्ण,
पूर्ण;

/* MSIOF0 */
अटल काष्ठा sh_msiof_spi_info msiof0_data = अणु
	.num_chipselect = 1,
पूर्ण;

अटल काष्ठा resource msiof0_resources[] = अणु
	[0] = अणु
		.name	= "MSIOF0",
		.start	= 0xa4c40000,
		.end	= 0xa4c40063,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xc80),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device msiof0_device = अणु
	.name		= "spi_sh_msiof",
	.id		= 0, /* MSIOF0 */
	.dev = अणु
		.platक्रमm_data = &msiof0_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(msiof0_resources),
	.resource	= msiof0_resources,
पूर्ण;

अटल काष्ठा gpiod_lookup_table msiof_gpio_table = अणु
	.dev_id = "spi_sh_msiof.0",
	.table = अणु
		GPIO_LOOKUP("sh7724_pfc", GPIO_PTM4, "cs", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

#पूर्ण_अगर

/* FSI */
अटल काष्ठा resource fsi_resources[] = अणु
	[0] = अणु
		.name	= "FSI",
		.start	= 0xFE3C0000,
		.end	= 0xFE3C021d,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0xf80),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device fsi_device = अणु
	.name		= "sh_fsi",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(fsi_resources),
	.resource	= fsi_resources,
पूर्ण;

अटल काष्ठा asoc_simple_card_info fsi_da7210_info = अणु
	.name		= "DA7210",
	.card		= "FSIB-DA7210",
	.codec		= "da7210.0-001a",
	.platक्रमm	= "sh_fsi.0",
	.daअगरmt		= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBM_CFM,
	.cpu_dai = अणु
		.name	= "fsib-dai",
	पूर्ण,
	.codec_dai = अणु
		.name	= "da7210-hifi",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device fsi_da7210_device = अणु
	.name	= "asoc-simple-card",
	.dev	= अणु
		.platक्रमm_data	= &fsi_da7210_info,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.dma_mask = &fsi_da7210_device.dev.coherent_dma_mask,
	पूर्ण,
पूर्ण;


/* IrDA */
अटल काष्ठा resource irda_resources[] = अणु
	[0] = अणु
		.name	= "IrDA",
		.start  = 0xA45D0000,
		.end    = 0xA45D0049,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0x480),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device irda_device = अणु
	.name           = "sh_sir",
	.num_resources  = ARRAY_SIZE(irda_resources),
	.resource       = irda_resources,
पूर्ण;

#समावेश <media/i2c/ak881x.h>
#समावेश <media/drv-पूर्णांकf/sh_vou.h>

अटल काष्ठा ak881x_pdata ak881x_pdata = अणु
	.flags = AK881X_IF_MODE_SLAVE,
पूर्ण;

अटल काष्ठा i2c_board_info ak8813 = अणु
	I2C_BOARD_INFO("ak8813", 0x20),
	.platक्रमm_data = &ak881x_pdata,
पूर्ण;

अटल काष्ठा sh_vou_pdata sh_vou_pdata = अणु
	.bus_fmt	= SH_VOU_BUS_8BIT,
	.flags		= SH_VOU_HSYNC_LOW | SH_VOU_VSYNC_LOW,
	.board_info	= &ak8813,
	.i2c_adap	= 0,
पूर्ण;

अटल काष्ठा resource sh_vou_resources[] = अणु
	[0] = अणु
		.start  = 0xfe960000,
		.end    = 0xfe962043,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0x8e0),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device vou_device = अणु
	.name           = "sh-vou",
	.id		= -1,
	.num_resources  = ARRAY_SIZE(sh_vou_resources),
	.resource       = sh_vou_resources,
	.dev		= अणु
		.platक्रमm_data	= &sh_vou_pdata,
	पूर्ण,
पूर्ण;

#अगर defined(CONFIG_MMC_SH_MMCIF) || defined(CONFIG_MMC_SH_MMCIF_MODULE)
/* SH_MMCIF */
अटल काष्ठा resource sh_mmcअगर_resources[] = अणु
	[0] = अणु
		.name	= "SH_MMCIF",
		.start	= 0xA4CA0000,
		.end	= 0xA4CA00FF,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		/* MMC2I */
		.start	= evt2irq(0x5a0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		/* MMC3I */
		.start	= evt2irq(0x5c0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_mmcअगर_plat_data sh_mmcअगर_plat = अणु
	.sup_pclk	= 0, /* SH7724: Max Pclk/2 */
	.caps		= MMC_CAP_4_BIT_DATA |
			  MMC_CAP_8_BIT_DATA |
			  MMC_CAP_NEEDS_POLL,
	.ocr		= MMC_VDD_32_33 | MMC_VDD_33_34,
पूर्ण;

अटल काष्ठा platक्रमm_device sh_mmcअगर_device = अणु
	.name		= "sh_mmcif",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data		= &sh_mmcअगर_plat,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sh_mmcअगर_resources),
	.resource	= sh_mmcअगर_resources,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_device *ecovec_ceu_devices[] __initdata = अणु
	&ceu0_device,
	&ceu1_device,
पूर्ण;

अटल काष्ठा platक्रमm_device *ecovec_devices[] __initdata = अणु
	&heartbeat_device,
	&nor_flash_device,
	&sh_eth_device,
	&usb0_host_device,
	&usb1_common_device,
	&usbhs_device,
	&lcdc_device,
	&keysc_device,
	&cn12_घातer,
#अगर defined(CONFIG_MMC_SDHI) || defined(CONFIG_MMC_SDHI_MODULE)
	&sdhi0_घातer,
	&sdhi0_device,
#अगर !defined(CONFIG_MMC_SH_MMCIF) && !defined(CONFIG_MMC_SH_MMCIF_MODULE)
	&sdhi1_device,
#पूर्ण_अगर
#अन्यथा
	&msiof0_device,
#पूर्ण_अगर
	&fsi_device,
	&fsi_da7210_device,
	&irda_device,
	&vou_device,
#अगर defined(CONFIG_MMC_SH_MMCIF) || defined(CONFIG_MMC_SH_MMCIF_MODULE)
	&sh_mmcअगर_device,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_I2C
#घोषणा EEPROM_ADDR 0x50
अटल u8 mac_पढ़ो(काष्ठा i2c_adapter *a, u8 command)
अणु
	काष्ठा i2c_msg msg[2];
	u8 buf;
	पूर्णांक ret;

	msg[0].addr  = EEPROM_ADDR;
	msg[0].flags = 0;
	msg[0].len   = 1;
	msg[0].buf   = &command;

	msg[1].addr  = EEPROM_ADDR;
	msg[1].flags = I2C_M_RD;
	msg[1].len   = 1;
	msg[1].buf   = &buf;

	ret = i2c_transfer(a, msg, 2);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "error %d\n", ret);
		buf = 0xff;
	पूर्ण

	वापस buf;
पूर्ण

अटल व्योम __init sh_eth_init(काष्ठा sh_eth_plat_data *pd)
अणु
	काष्ठा i2c_adapter *a = i2c_get_adapter(1);
	पूर्णांक i;

	अगर (!a) अणु
		pr_err("can not get I2C 1\n");
		वापस;
	पूर्ण

	/* पढ़ो MAC address from EEPROM */
	क्रम (i = 0; i < माप(pd->mac_addr); i++) अणु
		pd->mac_addr[i] = mac_पढ़ो(a, 0x10 + i);
		msleep(10);
	पूर्ण

	i2c_put_adapter(a);
पूर्ण
#अन्यथा
अटल व्योम __init sh_eth_init(काष्ठा sh_eth_plat_data *pd)
अणु
	pr_err("unable to read sh_eth MAC address\n");
पूर्ण
#पूर्ण_अगर

#घोषणा PORT_HIZA 0xA4050158
#घोषणा IODRIVEA  0xA405018A

बाह्य अक्षर ecovec24_sdram_enter_start;
बाह्य अक्षर ecovec24_sdram_enter_end;
बाह्य अक्षर ecovec24_sdram_leave_start;
बाह्य अक्षर ecovec24_sdram_leave_end;

अटल पूर्णांक __init arch_setup(व्योम)
अणु
	काष्ठा clk *clk;
	bool cn12_enabled = false;

	/* रेजिस्टर board specअगरic self-refresh code */
	sh_mobile_रेजिस्टर_self_refresh(SUSP_SH_STANDBY | SUSP_SH_SF |
					SUSP_SH_RSTANDBY,
					&ecovec24_sdram_enter_start,
					&ecovec24_sdram_enter_end,
					&ecovec24_sdram_leave_start,
					&ecovec24_sdram_leave_end);

	/* enable STATUS0, STATUS2 and PDSTATUS */
	gpio_request(GPIO_FN_STATUS0, शून्य);
	gpio_request(GPIO_FN_STATUS2, शून्य);
	gpio_request(GPIO_FN_PDSTATUS, शून्य);

	/* enable SCIFA0 */
	gpio_request(GPIO_FN_SCIF0_TXD, शून्य);
	gpio_request(GPIO_FN_SCIF0_RXD, शून्य);

	/* enable debug LED */
	gpio_request(GPIO_PTG0, शून्य);
	gpio_request(GPIO_PTG1, शून्य);
	gpio_request(GPIO_PTG2, शून्य);
	gpio_request(GPIO_PTG3, शून्य);
	gpio_direction_output(GPIO_PTG0, 0);
	gpio_direction_output(GPIO_PTG1, 0);
	gpio_direction_output(GPIO_PTG2, 0);
	gpio_direction_output(GPIO_PTG3, 0);
	__raw_ग_लिखोw((__raw_पढ़ोw(PORT_HIZA) & ~(0x1 << 1)) , PORT_HIZA);

	/* enable SH-Eth */
	gpio_request(GPIO_PTA1, शून्य);
	gpio_direction_output(GPIO_PTA1, 1);
	mdelay(20);

	gpio_request(GPIO_FN_RMII_RXD0,    शून्य);
	gpio_request(GPIO_FN_RMII_RXD1,    शून्य);
	gpio_request(GPIO_FN_RMII_TXD0,    शून्य);
	gpio_request(GPIO_FN_RMII_TXD1,    शून्य);
	gpio_request(GPIO_FN_RMII_REF_CLK, शून्य);
	gpio_request(GPIO_FN_RMII_TX_EN,   शून्य);
	gpio_request(GPIO_FN_RMII_RX_ER,   शून्य);
	gpio_request(GPIO_FN_RMII_CRS_DV,  शून्य);
	gpio_request(GPIO_FN_MDIO,         शून्य);
	gpio_request(GPIO_FN_MDC,          शून्य);
	gpio_request(GPIO_FN_LNKSTA,       शून्य);

	/* enable USB */
	__raw_ग_लिखोw(0x0000, 0xA4D80000);
	__raw_ग_लिखोw(0x0000, 0xA4D90000);
	gpio_request(GPIO_PTB3,  शून्य);
	gpio_request(GPIO_PTB4,  शून्य);
	gpio_request(GPIO_PTB5,  शून्य);
	gpio_direction_input(GPIO_PTB3);
	gpio_direction_output(GPIO_PTB4, 0);
	gpio_direction_output(GPIO_PTB5, 0);
	__raw_ग_लिखोw(0x0600, 0xa40501d4);
	__raw_ग_लिखोw(0x0600, 0xa4050192);

	अगर (gpio_get_value(GPIO_PTB3)) अणु
		prपूर्णांकk(KERN_INFO "USB1 function is selected\n");
		usb1_common_device.name = "r8a66597_udc";
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "USB1 host is selected\n");
		usb1_common_device.name = "r8a66597_hcd";
	पूर्ण

	/* enable LCDC */
	gpio_request(GPIO_FN_LCDD23,   शून्य);
	gpio_request(GPIO_FN_LCDD22,   शून्य);
	gpio_request(GPIO_FN_LCDD21,   शून्य);
	gpio_request(GPIO_FN_LCDD20,   शून्य);
	gpio_request(GPIO_FN_LCDD19,   शून्य);
	gpio_request(GPIO_FN_LCDD18,   शून्य);
	gpio_request(GPIO_FN_LCDD17,   शून्य);
	gpio_request(GPIO_FN_LCDD16,   शून्य);
	gpio_request(GPIO_FN_LCDD15,   शून्य);
	gpio_request(GPIO_FN_LCDD14,   शून्य);
	gpio_request(GPIO_FN_LCDD13,   शून्य);
	gpio_request(GPIO_FN_LCDD12,   शून्य);
	gpio_request(GPIO_FN_LCDD11,   शून्य);
	gpio_request(GPIO_FN_LCDD10,   शून्य);
	gpio_request(GPIO_FN_LCDD9,    शून्य);
	gpio_request(GPIO_FN_LCDD8,    शून्य);
	gpio_request(GPIO_FN_LCDD7,    शून्य);
	gpio_request(GPIO_FN_LCDD6,    शून्य);
	gpio_request(GPIO_FN_LCDD5,    शून्य);
	gpio_request(GPIO_FN_LCDD4,    शून्य);
	gpio_request(GPIO_FN_LCDD3,    शून्य);
	gpio_request(GPIO_FN_LCDD2,    शून्य);
	gpio_request(GPIO_FN_LCDD1,    शून्य);
	gpio_request(GPIO_FN_LCDD0,    शून्य);
	gpio_request(GPIO_FN_LCDDISP,  शून्य);
	gpio_request(GPIO_FN_LCDHSYN,  शून्य);
	gpio_request(GPIO_FN_LCDDCK,   शून्य);
	gpio_request(GPIO_FN_LCDVSYN,  शून्य);
	gpio_request(GPIO_FN_LCDDON,   शून्य);
	gpio_request(GPIO_FN_LCDLCLK,  शून्य);
	__raw_ग_लिखोw((__raw_पढ़ोw(PORT_HIZA) & ~0x0001), PORT_HIZA);

	gpio_request(GPIO_PTE6, शून्य);
	gpio_request(GPIO_PTU1, शून्य);
	gpio_request(GPIO_PTA2, शून्य);
	gpio_direction_input(GPIO_PTE6);
	gpio_direction_output(GPIO_PTU1, 0);
	gpio_direction_output(GPIO_PTA2, 0);

	/* I/O buffer drive ability is high */
	__raw_ग_लिखोw((__raw_पढ़ोw(IODRIVEA) & ~0x00c0) | 0x0080 , IODRIVEA);

	अगर (gpio_get_value(GPIO_PTE6)) अणु
		/* DVI */
		lcdc_info.घड़ी_source			= LCDC_CLK_EXTERNAL;
		lcdc_info.ch[0].घड़ी_भागider		= 1;
		lcdc_info.ch[0].lcd_modes		= ecovec_dvi_modes;
		lcdc_info.ch[0].num_modes		= ARRAY_SIZE(ecovec_dvi_modes);

		/* No backlight */
		gpio_backlight_data.fbdev = शून्य;

		gpio_set_value(GPIO_PTA2, 1);
		gpio_set_value(GPIO_PTU1, 1);
	पूर्ण अन्यथा अणु
		/* Panel */
		lcdc_info.घड़ी_source			= LCDC_CLK_PERIPHERAL;
		lcdc_info.ch[0].घड़ी_भागider		= 2;
		lcdc_info.ch[0].lcd_modes		= ecovec_lcd_modes;
		lcdc_info.ch[0].num_modes		= ARRAY_SIZE(ecovec_lcd_modes);

		/* FIXME
		 *
		 * LCDDON control is needed क्रम Panel,
		 * but current sh_mobile_lcdc driver करोesn't control it.
		 * It is temporary correspondence
		 */
		gpio_request(GPIO_PTF4, शून्य);
		gpio_direction_output(GPIO_PTF4, 1);

		/* enable TouchScreen */
		i2c_रेजिस्टर_board_info(0, &ts_i2c_clients, 1);
		irq_set_irq_type(IRQ0, IRQ_TYPE_LEVEL_LOW);
	पूर्ण

	/* enable CEU0 */
	gpio_request(GPIO_FN_VIO0_D15, शून्य);
	gpio_request(GPIO_FN_VIO0_D14, शून्य);
	gpio_request(GPIO_FN_VIO0_D13, शून्य);
	gpio_request(GPIO_FN_VIO0_D12, शून्य);
	gpio_request(GPIO_FN_VIO0_D11, शून्य);
	gpio_request(GPIO_FN_VIO0_D10, शून्य);
	gpio_request(GPIO_FN_VIO0_D9,  शून्य);
	gpio_request(GPIO_FN_VIO0_D8,  शून्य);
	gpio_request(GPIO_FN_VIO0_D7,  शून्य);
	gpio_request(GPIO_FN_VIO0_D6,  शून्य);
	gpio_request(GPIO_FN_VIO0_D5,  शून्य);
	gpio_request(GPIO_FN_VIO0_D4,  शून्य);
	gpio_request(GPIO_FN_VIO0_D3,  शून्य);
	gpio_request(GPIO_FN_VIO0_D2,  शून्य);
	gpio_request(GPIO_FN_VIO0_D1,  शून्य);
	gpio_request(GPIO_FN_VIO0_D0,  शून्य);
	gpio_request(GPIO_FN_VIO0_VD,  शून्य);
	gpio_request(GPIO_FN_VIO0_CLK, शून्य);
	gpio_request(GPIO_FN_VIO0_FLD, शून्य);
	gpio_request(GPIO_FN_VIO0_HD,  शून्य);

	/* enable CEU1 */
	gpio_request(GPIO_FN_VIO1_D7,  शून्य);
	gpio_request(GPIO_FN_VIO1_D6,  शून्य);
	gpio_request(GPIO_FN_VIO1_D5,  शून्य);
	gpio_request(GPIO_FN_VIO1_D4,  शून्य);
	gpio_request(GPIO_FN_VIO1_D3,  शून्य);
	gpio_request(GPIO_FN_VIO1_D2,  शून्य);
	gpio_request(GPIO_FN_VIO1_D1,  शून्य);
	gpio_request(GPIO_FN_VIO1_D0,  शून्य);
	gpio_request(GPIO_FN_VIO1_FLD, शून्य);
	gpio_request(GPIO_FN_VIO1_HD,  शून्य);
	gpio_request(GPIO_FN_VIO1_VD,  शून्य);
	gpio_request(GPIO_FN_VIO1_CLK, शून्य);

	/* enable KEYSC */
	gpio_request(GPIO_FN_KEYOUT5_IN5, शून्य);
	gpio_request(GPIO_FN_KEYOUT4_IN6, शून्य);
	gpio_request(GPIO_FN_KEYOUT3,     शून्य);
	gpio_request(GPIO_FN_KEYOUT2,     शून्य);
	gpio_request(GPIO_FN_KEYOUT1,     शून्य);
	gpio_request(GPIO_FN_KEYOUT0,     शून्य);
	gpio_request(GPIO_FN_KEYIN0,      शून्य);

	/* enable user debug चयन */
	gpio_request(GPIO_PTR0, शून्य);
	gpio_request(GPIO_PTR4, शून्य);
	gpio_request(GPIO_PTR5, शून्य);
	gpio_request(GPIO_PTR6, शून्य);
	gpio_direction_input(GPIO_PTR0);
	gpio_direction_input(GPIO_PTR4);
	gpio_direction_input(GPIO_PTR5);
	gpio_direction_input(GPIO_PTR6);

	/* SD-card slot CN11 */
#अगर defined(CONFIG_MMC_SDHI) || defined(CONFIG_MMC_SDHI_MODULE)
	/* enable SDHI0 on CN11 (needs DS2.4 set to ON) */
	gpio_request(GPIO_FN_SDHI0WP,  शून्य);
	gpio_request(GPIO_FN_SDHI0CMD, शून्य);
	gpio_request(GPIO_FN_SDHI0CLK, शून्य);
	gpio_request(GPIO_FN_SDHI0D3,  शून्य);
	gpio_request(GPIO_FN_SDHI0D2,  शून्य);
	gpio_request(GPIO_FN_SDHI0D1,  शून्य);
	gpio_request(GPIO_FN_SDHI0D0,  शून्य);
#अन्यथा
	/* enable MSIOF0 on CN11 (needs DS2.4 set to OFF) */
	gpio_request(GPIO_FN_MSIOF0_TXD, शून्य);
	gpio_request(GPIO_FN_MSIOF0_RXD, शून्य);
	gpio_request(GPIO_FN_MSIOF0_TSCK, शून्य);
	gpio_request(GPIO_PTB6, शून्य); /* 3.3V घातer control */
	gpio_direction_output(GPIO_PTB6, 0); /* disable घातer by शेष */

	gpiod_add_lookup_table(&mmc_spi_gpio_table);
	gpiod_add_lookup_table(&msiof_gpio_table);
	spi_रेजिस्टर_board_info(spi_bus, ARRAY_SIZE(spi_bus));
#पूर्ण_अगर

	/* MMC/SD-card slot CN12 */
#अगर defined(CONFIG_MMC_SH_MMCIF) || defined(CONFIG_MMC_SH_MMCIF_MODULE)
	/* enable MMCIF (needs DS2.6,7 set to OFF,ON) */
	gpio_request(GPIO_FN_MMC_D7, शून्य);
	gpio_request(GPIO_FN_MMC_D6, शून्य);
	gpio_request(GPIO_FN_MMC_D5, शून्य);
	gpio_request(GPIO_FN_MMC_D4, शून्य);
	gpio_request(GPIO_FN_MMC_D3, शून्य);
	gpio_request(GPIO_FN_MMC_D2, शून्य);
	gpio_request(GPIO_FN_MMC_D1, शून्य);
	gpio_request(GPIO_FN_MMC_D0, शून्य);
	gpio_request(GPIO_FN_MMC_CLK, शून्य);
	gpio_request(GPIO_FN_MMC_CMD, शून्य);

	cn12_enabled = true;
#या_अगर defined(CONFIG_MMC_SDHI) || defined(CONFIG_MMC_SDHI_MODULE)
	/* enable SDHI1 on CN12 (needs DS2.6,7 set to ON,OFF) */
	gpio_request(GPIO_FN_SDHI1WP,  शून्य);
	gpio_request(GPIO_FN_SDHI1CMD, शून्य);
	gpio_request(GPIO_FN_SDHI1CLK, शून्य);
	gpio_request(GPIO_FN_SDHI1D3,  शून्य);
	gpio_request(GPIO_FN_SDHI1D2,  शून्य);
	gpio_request(GPIO_FN_SDHI1D1,  शून्य);
	gpio_request(GPIO_FN_SDHI1D0,  शून्य);

	cn12_enabled = true;
#पूर्ण_अगर

	अगर (cn12_enabled)
		/* I/O buffer drive ability is high क्रम CN12 */
		__raw_ग_लिखोw((__raw_पढ़ोw(IODRIVEA) & ~0x3000) | 0x2000,
			     IODRIVEA);

	/* enable FSI */
	gpio_request(GPIO_FN_FSIMCKB,    शून्य);
	gpio_request(GPIO_FN_FSIIBSD,    शून्य);
	gpio_request(GPIO_FN_FSIOBSD,    शून्य);
	gpio_request(GPIO_FN_FSIIBBCK,   शून्य);
	gpio_request(GPIO_FN_FSIIBLRCK,  शून्य);
	gpio_request(GPIO_FN_FSIOBBCK,   शून्य);
	gpio_request(GPIO_FN_FSIOBLRCK,  शून्य);
	gpio_request(GPIO_FN_CLKAUDIOBO, शून्य);

	/* set SPU2 घड़ी to 83.4 MHz */
	clk = clk_get(शून्य, "spu_clk");
	अगर (!IS_ERR(clk)) अणु
		clk_set_rate(clk, clk_round_rate(clk, 83333333));
		clk_put(clk);
	पूर्ण

	/* change parent of FSI B */
	clk = clk_get(शून्य, "fsib_clk");
	अगर (!IS_ERR(clk)) अणु
		/* 48kHz dummy घड़ी was used to make sure 1/1 भागide */
		clk_set_rate(&sh7724_fsimckb_clk, 48000);
		clk_set_parent(clk, &sh7724_fsimckb_clk);
		clk_set_rate(clk, 48000);
		clk_put(clk);
	पूर्ण

	gpio_request(GPIO_PTU0, शून्य);
	gpio_direction_output(GPIO_PTU0, 0);
	mdelay(20);

	/* enable motion sensor */
	gpio_request(GPIO_FN_INTC_IRQ1, शून्य);
	gpio_direction_input(GPIO_FN_INTC_IRQ1);

	/* set VPU घड़ी to 166 MHz */
	clk = clk_get(शून्य, "vpu_clk");
	अगर (!IS_ERR(clk)) अणु
		clk_set_rate(clk, clk_round_rate(clk, 166000000));
		clk_put(clk);
	पूर्ण

	/* enable IrDA */
	gpio_request(GPIO_FN_IRDA_OUT, शून्य);
	gpio_request(GPIO_FN_IRDA_IN,  शून्य);
	gpio_request(GPIO_PTU5, शून्य);
	gpio_direction_output(GPIO_PTU5, 0);

	/* Register gpio lookup tables क्रम cameras and video decoder */
	gpiod_add_lookup_table(&tw9910_gpios);
	gpiod_add_lookup_table(&mt9t112_0_gpios);
	gpiod_add_lookup_table(&mt9t112_1_gpios);

	/* enable I2C device */
	i2c_रेजिस्टर_board_info(0, i2c0_devices,
				ARRAY_SIZE(i2c0_devices));

	i2c_रेजिस्टर_board_info(1, i2c1_devices,
				ARRAY_SIZE(i2c1_devices));

#अगर defined(CONFIG_VIDEO_SH_VOU) || defined(CONFIG_VIDEO_SH_VOU_MODULE)
	/* VOU */
	gpio_request(GPIO_FN_DV_D15, शून्य);
	gpio_request(GPIO_FN_DV_D14, शून्य);
	gpio_request(GPIO_FN_DV_D13, शून्य);
	gpio_request(GPIO_FN_DV_D12, शून्य);
	gpio_request(GPIO_FN_DV_D11, शून्य);
	gpio_request(GPIO_FN_DV_D10, शून्य);
	gpio_request(GPIO_FN_DV_D9, शून्य);
	gpio_request(GPIO_FN_DV_D8, शून्य);
	gpio_request(GPIO_FN_DV_CLKI, शून्य);
	gpio_request(GPIO_FN_DV_CLK, शून्य);
	gpio_request(GPIO_FN_DV_VSYNC, शून्य);
	gpio_request(GPIO_FN_DV_HSYNC, शून्य);

	/* AK8813 घातer / reset sequence */
	gpio_request(GPIO_PTG4, शून्य);
	gpio_request(GPIO_PTU3, शून्य);
	/* Reset */
	gpio_direction_output(GPIO_PTG4, 0);
	/* Power करोwn */
	gpio_direction_output(GPIO_PTU3, 1);

	udelay(10);

	/* Power up, reset */
	gpio_set_value(GPIO_PTU3, 0);

	udelay(10);

	/* Remove reset */
	gpio_set_value(GPIO_PTG4, 1);
#पूर्ण_अगर

	/* Initialize CEU platक्रमm devices separately to map memory first */
	device_initialize(&ecovec_ceu_devices[0]->dev);
	dma_declare_coherent_memory(&ecovec_ceu_devices[0]->dev,
				    ceu0_dma_membase, ceu0_dma_membase,
				    ceu0_dma_membase +
				    CEU_BUFFER_MEMORY_SIZE - 1);
	platक्रमm_device_add(ecovec_ceu_devices[0]);

	device_initialize(&ecovec_ceu_devices[1]->dev);
	dma_declare_coherent_memory(&ecovec_ceu_devices[1]->dev,
				    ceu1_dma_membase, ceu1_dma_membase,
				    ceu1_dma_membase +
				    CEU_BUFFER_MEMORY_SIZE - 1);
	platक्रमm_device_add(ecovec_ceu_devices[1]);

	gpiod_add_lookup_table(&cn12_घातer_gpiod_table);
#अगर defined(CONFIG_MMC_SDHI) || defined(CONFIG_MMC_SDHI_MODULE)
	gpiod_add_lookup_table(&sdhi0_घातer_gpiod_table);
	gpiod_add_lookup_table(&sdhi0_gpio_table);
#अगर !defined(CONFIG_MMC_SH_MMCIF) && !defined(CONFIG_MMC_SH_MMCIF_MODULE)
	gpiod_add_lookup_table(&sdhi1_gpio_table);
#पूर्ण_अगर
#पूर्ण_अगर

	gpiod_add_lookup_table(&gpio_backlight_lookup);
	gpio_backlight_device = platक्रमm_device_रेजिस्टर_full(
					&gpio_backlight_device_info);
	अगर (IS_ERR(gpio_backlight_device))
		वापस PTR_ERR(gpio_backlight_device);

	वापस platक्रमm_add_devices(ecovec_devices,
				    ARRAY_SIZE(ecovec_devices));
पूर्ण
arch_initcall(arch_setup);

अटल पूर्णांक __init devices_setup(व्योम)
अणु
	sh_eth_init(&sh_eth_plat);
	वापस 0;
पूर्ण
device_initcall(devices_setup);

/* Reserve a portion of memory क्रम CEU 0 and CEU 1 buffers */
अटल व्योम __init ecovec_mv_mem_reserve(व्योम)
अणु
	phys_addr_t phys;
	phys_addr_t size = CEU_BUFFER_MEMORY_SIZE;

	phys = memblock_phys_alloc(size, PAGE_SIZE);
	अगर (!phys)
		panic("Failed to allocate CEU0 memory\n");

	memblock_मुक्त(phys, size);
	memblock_हटाओ(phys, size);
	ceu0_dma_membase = phys;

	phys = memblock_phys_alloc(size, PAGE_SIZE);
	अगर (!phys)
		panic("Failed to allocate CEU1 memory\n");

	memblock_मुक्त(phys, size);
	memblock_हटाओ(phys, size);
	ceu1_dma_membase = phys;
पूर्ण

अटल काष्ठा sh_machine_vector mv_ecovec __iniपंचांगv = अणु
	.mv_name	= "R0P7724 (EcoVec)",
	.mv_mem_reserve	= ecovec_mv_mem_reserve,
पूर्ण;
