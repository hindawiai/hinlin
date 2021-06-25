<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/se/7724/setup.c
 *
 * Copyright (C) 2009 Renesas Solutions Corp.
 *
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 */
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/heartbeat.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/suspend.h>

#समावेश <cpu/sh7724.h>

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sh_keysc.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/sh_eth.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/usb/r8a66597.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/dma-map-ops.h>

#समावेश <mach-se/mach/se7724.h>
#समावेश <media/drv-पूर्णांकf/renesas-ceu.h>

#समावेश <sound/sh_fsi.h>
#समावेश <sound/simple_card.h>

#समावेश <video/sh_mobile_lcdc.h>

#घोषणा CEU_BUFFER_MEMORY_SIZE		(4 << 20)
अटल phys_addr_t ceu0_dma_membase;
अटल phys_addr_t ceu1_dma_membase;

/*
 * SWx    1234 5678
 * ------------------------------------
 * SW31 : 1001 1100    : शेष
 * SW32 : 0111 1111    : use on board flash
 *
 * SW41 : abxx xxxx  -> a = 0 : Analog  monitor
 *                          1 : Digital monitor
 *                      b = 0 : VGA
 *                          1 : 720p
 */

/*
 * about 720p
 *
 * When you use 1280 x 720 lcdc output,
 * you should change OSC6 lcdc घड़ी from 25.175MHz to 74.25MHz,
 * and change SW41 to use 720p
 */

/*
 * about sound
 *
 * This setup.c supports FSI slave mode.
 * Please change J20, J21, J22 pin to 1-2 connection.
 */

/* Heartbeat */
अटल काष्ठा resource heartbeat_resource = अणु
	.start  = PA_LED,
	.end    = PA_LED,
	.flags  = IORESOURCE_MEM | IORESOURCE_MEM_16BIT,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name           = "heartbeat",
	.id             = -1,
	.num_resources  = 1,
	.resource       = &heartbeat_resource,
पूर्ण;

/* LAN91C111 */
अटल काष्ठा smc91x_platdata smc91x_info = अणु
	.flags = SMC91X_USE_16BIT | SMC91X_NOWAIT,
पूर्ण;

अटल काष्ठा resource smc91x_eth_resources[] = अणु
	[0] = अणु
		.name   = "SMC91C111" ,
		.start  = 0x1a300300,
		.end    = 0x1a30030f,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = IRQ0_SMC,
		.flags  = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_eth_device = अणु
	.name	= "smc91x",
	.num_resources  = ARRAY_SIZE(smc91x_eth_resources),
	.resource       = smc91x_eth_resources,
	.dev	= अणु
		.platक्रमm_data	= &smc91x_info,
	पूर्ण,
पूर्ण;

/* MTD */
अटल काष्ठा mtd_partition nor_flash_partitions[] = अणु
	अणु
		.name = "uboot",
		.offset = 0,
		.size = (1 * 1024 * 1024),
		.mask_flags = MTD_WRITEABLE,	/* Read-only */
	पूर्ण, अणु
		.name = "kernel",
		.offset = MTDPART_OFS_APPEND,
		.size = (2 * 1024 * 1024),
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
		.end	= 0x01ffffff,
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

/* LCDC */
अटल स्थिर काष्ठा fb_videomode lcdc_720p_modes[] = अणु
	अणु
		.name		= "LB070WV1",
		.sync		= 0, /* hsync and vsync are active low */
		.xres		= 1280,
		.yres		= 720,
		.left_margin	= 220,
		.right_margin	= 110,
		.hsync_len	= 40,
		.upper_margin	= 20,
		.lower_margin	= 5,
		.vsync_len	= 5,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा fb_videomode lcdc_vga_modes[] = अणु
	अणु
		.name		= "LB070WV1",
		.sync		= 0, /* hsync and vsync are active low */
		.xres		= 640,
		.yres		= 480,
		.left_margin	= 105,
		.right_margin	= 50,
		.hsync_len	= 96,
		.upper_margin	= 33,
		.lower_margin	= 10,
		.vsync_len	= 2,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_mobile_lcdc_info lcdc_info = अणु
	.घड़ी_source = LCDC_CLK_EXTERNAL,
	.ch[0] = अणु
		.chan = LCDC_CHAN_MAINLCD,
		.fourcc = V4L2_PIX_FMT_RGB565,
		.घड़ी_भागider = 1,
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

/* CEU0 */
अटल काष्ठा ceu_platक्रमm_data ceu0_pdata = अणु
	.num_subdevs = 0,
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
	.id             = 0, /* "ceu.0" घड़ी */
	.num_resources	= ARRAY_SIZE(ceu0_resources),
	.resource	= ceu0_resources,
	.dev	= अणु
		.platक्रमm_data	= &ceu0_pdata,
	पूर्ण,
पूर्ण;

/* CEU1 */
अटल काष्ठा ceu_platक्रमm_data ceu1_pdata = अणु
	.num_subdevs = 0,
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
	.id             = 1, /* "ceu.1" घड़ी */
	.num_resources	= ARRAY_SIZE(ceu1_resources),
	.resource	= ceu1_resources,
	.dev	= अणु
		.platक्रमm_data	= &ceu1_pdata,
	पूर्ण,
पूर्ण;

/* FSI */
/* change J20, J21, J22 pin to 1-2 connection to use slave mode */
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

अटल काष्ठा asoc_simple_card_info fsi_ak4642_info = अणु
	.name		= "AK4642",
	.card		= "FSIA-AK4642",
	.codec		= "ak4642-codec.0-0012",
	.platक्रमm	= "sh_fsi.0",
	.daअगरmt		= SND_SOC_DAIFMT_LEFT_J | SND_SOC_DAIFMT_CBM_CFM,
	.cpu_dai = अणु
		.name	= "fsia-dai",
	पूर्ण,
	.codec_dai = अणु
		.name	= "ak4642-hifi",
		.sysclk	= 11289600,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device fsi_ak4642_device = अणु
	.name	= "asoc-simple-card",
	.dev	= अणु
		.platक्रमm_data	= &fsi_ak4642_info,
	पूर्ण,
पूर्ण;

/* KEYSC in SoC (Needs SW33-2 set to ON) */
अटल काष्ठा sh_keysc_info keysc_info = अणु
	.mode = SH_KEYSC_MODE_1,
	.scan_timing = 3,
	.delay = 50,
	.keycodes = अणु
		KEY_1, KEY_2, KEY_3, KEY_4, KEY_5,
		KEY_6, KEY_7, KEY_8, KEY_9, KEY_A,
		KEY_B, KEY_C, KEY_D, KEY_E, KEY_F,
		KEY_G, KEY_H, KEY_I, KEY_K, KEY_L,
		KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q,
		KEY_R, KEY_S, KEY_T, KEY_U, KEY_V,
	पूर्ण,
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
	.id             = 0, /* "keysc0" घड़ी */
	.num_resources  = ARRAY_SIZE(keysc_resources),
	.resource       = keysc_resources,
	.dev	= अणु
		.platक्रमm_data	= &keysc_info,
	पूर्ण,
पूर्ण;

/* SH Eth */
अटल काष्ठा resource sh_eth_resources[] = अणु
	[0] = अणु
		.start = SH_ETH_ADDR,
		.end   = SH_ETH_ADDR + 0x1FC - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = evt2irq(0xd60),
		.flags = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_eth_plat_data sh_eth_plat = अणु
	.phy = 0x1f, /* SMSC LAN8187 */
	.phy_पूर्णांकerface = PHY_INTERFACE_MODE_MII,
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

अटल काष्ठा r8a66597_platdata sh7724_usb0_host_data = अणु
	.on_chip = 1,
पूर्ण;

अटल काष्ठा resource sh7724_usb0_host_resources[] = अणु
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

अटल काष्ठा platक्रमm_device sh7724_usb0_host_device = अणु
	.name		= "r8a66597_hcd",
	.id		= 0,
	.dev = अणु
		.dma_mask		= शून्य,         /*  not use dma */
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &sh7724_usb0_host_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sh7724_usb0_host_resources),
	.resource	= sh7724_usb0_host_resources,
पूर्ण;

अटल काष्ठा r8a66597_platdata sh7724_usb1_gadget_data = अणु
	.on_chip = 1,
पूर्ण;

अटल काष्ठा resource sh7724_usb1_gadget_resources[] = अणु
	[0] = अणु
		.start	= 0xa4d90000,
		.end	= 0xa4d90123,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0xa40),
		.end	= evt2irq(0xa40),
		.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_LOW,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sh7724_usb1_gadget_device = अणु
	.name		= "r8a66597_udc",
	.id		= 1, /* USB1 */
	.dev = अणु
		.dma_mask		= शून्य,         /*  not use dma */
		.coherent_dma_mask	= 0xffffffff,
		.platक्रमm_data		= &sh7724_usb1_gadget_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(sh7724_usb1_gadget_resources),
	.resource	= sh7724_usb1_gadget_resources,
पूर्ण;

/* Fixed 3.3V regulator to be used by SDHI0, SDHI1 */
अटल काष्ठा regulator_consumer_supply fixed3v3_घातer_consumers[] =
अणु
	REGULATOR_SUPPLY("vmmc", "sh_mobile_sdhi.0"),
	REGULATOR_SUPPLY("vqmmc", "sh_mobile_sdhi.0"),
	REGULATOR_SUPPLY("vmmc", "sh_mobile_sdhi.1"),
	REGULATOR_SUPPLY("vqmmc", "sh_mobile_sdhi.1"),
पूर्ण;

अटल काष्ठा resource sdhi0_cn7_resources[] = अणु
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

अटल काष्ठा पंचांगio_mmc_data sh7724_sdhi0_data = अणु
	.chan_priv_tx	= (व्योम *)SHDMA_SLAVE_SDHI0_TX,
	.chan_priv_rx	= (व्योम *)SHDMA_SLAVE_SDHI0_RX,
	.capabilities	= MMC_CAP_SDIO_IRQ,
पूर्ण;

अटल काष्ठा platक्रमm_device sdhi0_cn7_device = अणु
	.name           = "sh_mobile_sdhi",
	.id		= 0,
	.num_resources  = ARRAY_SIZE(sdhi0_cn7_resources),
	.resource       = sdhi0_cn7_resources,
	.dev = अणु
		.platक्रमm_data	= &sh7724_sdhi0_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sdhi1_cn8_resources[] = अणु
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

अटल काष्ठा पंचांगio_mmc_data sh7724_sdhi1_data = अणु
	.chan_priv_tx	= (व्योम *)SHDMA_SLAVE_SDHI1_TX,
	.chan_priv_rx	= (व्योम *)SHDMA_SLAVE_SDHI1_RX,
	.capabilities	= MMC_CAP_SDIO_IRQ,
पूर्ण;

अटल काष्ठा platक्रमm_device sdhi1_cn8_device = अणु
	.name           = "sh_mobile_sdhi",
	.id		= 1,
	.num_resources  = ARRAY_SIZE(sdhi1_cn8_resources),
	.resource       = sdhi1_cn8_resources,
	.dev = अणु
		.platक्रमm_data	= &sh7724_sdhi1_data,
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
	/* With खोलो J18 jumper address is 0x21 */
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

अटल काष्ठा platक्रमm_device *ms7724se_ceu_devices[] __initdata = अणु
	&ceu0_device,
	&ceu1_device,
पूर्ण;

अटल काष्ठा platक्रमm_device *ms7724se_devices[] __initdata = अणु
	&heartbeat_device,
	&smc91x_eth_device,
	&lcdc_device,
	&nor_flash_device,
	&keysc_device,
	&sh_eth_device,
	&sh7724_usb0_host_device,
	&sh7724_usb1_gadget_device,
	&fsi_device,
	&fsi_ak4642_device,
	&sdhi0_cn7_device,
	&sdhi1_cn8_device,
	&irda_device,
	&vou_device,
पूर्ण;

/* I2C device */
अटल काष्ठा i2c_board_info i2c0_devices[] = अणु
	अणु
		I2C_BOARD_INFO("ak4642", 0x12),
	पूर्ण,
पूर्ण;

#घोषणा EEPROM_OP   0xBA206000
#घोषणा EEPROM_ADR  0xBA206004
#घोषणा EEPROM_DATA 0xBA20600C
#घोषणा EEPROM_STAT 0xBA206010
#घोषणा EEPROM_STRT 0xBA206014

अटल पूर्णांक __init sh_eth_is_eeprom_पढ़ोy(व्योम)
अणु
	पूर्णांक t = 10000;

	जबतक (t--) अणु
		अगर (!__raw_पढ़ोw(EEPROM_STAT))
			वापस 1;
		udelay(1);
	पूर्ण

	prपूर्णांकk(KERN_ERR "ms7724se can not access to eeprom\n");
	वापस 0;
पूर्ण

अटल व्योम __init sh_eth_init(व्योम)
अणु
	पूर्णांक i;
	u16 mac;

	/* check EEPROM status */
	अगर (!sh_eth_is_eeprom_पढ़ोy())
		वापस;

	/* पढ़ो MAC addr from EEPROM */
	क्रम (i = 0 ; i < 3 ; i++) अणु
		__raw_ग_लिखोw(0x0, EEPROM_OP); /* पढ़ो */
		__raw_ग_लिखोw(i*2, EEPROM_ADR);
		__raw_ग_लिखोw(0x1, EEPROM_STRT);
		अगर (!sh_eth_is_eeprom_पढ़ोy())
			वापस;

		mac = __raw_पढ़ोw(EEPROM_DATA);
		sh_eth_plat.mac_addr[i << 1] = mac & 0xff;
		sh_eth_plat.mac_addr[(i << 1) + 1] = mac >> 8;
	पूर्ण
पूर्ण

#घोषणा SW4140    0xBA201000
#घोषणा FPGA_OUT  0xBA200400
#घोषणा PORT_HIZA 0xA4050158
#घोषणा PORT_MSELCRB 0xA4050182

#घोषणा SW41_A    0x0100
#घोषणा SW41_B    0x0200
#घोषणा SW41_C    0x0400
#घोषणा SW41_D    0x0800
#घोषणा SW41_E    0x1000
#घोषणा SW41_F    0x2000
#घोषणा SW41_G    0x4000
#घोषणा SW41_H    0x8000

बाह्य अक्षर ms7724se_sdram_enter_start;
बाह्य अक्षर ms7724se_sdram_enter_end;
बाह्य अक्षर ms7724se_sdram_leave_start;
बाह्य अक्षर ms7724se_sdram_leave_end;

अटल पूर्णांक __init arch_setup(व्योम)
अणु
	/* enable I2C device */
	i2c_रेजिस्टर_board_info(0, i2c0_devices,
				ARRAY_SIZE(i2c0_devices));
	वापस 0;
पूर्ण
arch_initcall(arch_setup);

अटल पूर्णांक __init devices_setup(व्योम)
अणु
	u16 sw = __raw_पढ़ोw(SW4140); /* select camera, monitor */
	काष्ठा clk *clk;
	u16 fpga_out;

	/* रेजिस्टर board specअगरic self-refresh code */
	sh_mobile_रेजिस्टर_self_refresh(SUSP_SH_STANDBY | SUSP_SH_SF |
					SUSP_SH_RSTANDBY,
					&ms7724se_sdram_enter_start,
					&ms7724se_sdram_enter_end,
					&ms7724se_sdram_leave_start,
					&ms7724se_sdram_leave_end);

	regulator_रेजिस्टर_always_on(0, "fixed-3.3V", fixed3v3_घातer_consumers,
				     ARRAY_SIZE(fixed3v3_घातer_consumers), 3300000);

	/* Reset Release */
	fpga_out = __raw_पढ़ोw(FPGA_OUT);
	/* bit4: NTSC_PDN, bit5: NTSC_RESET */
	fpga_out &= ~((1 << 1)  | /* LAN */
		      (1 << 4)  | /* AK8813 PDN */
		      (1 << 5)  | /* AK8813 RESET */
		      (1 << 6)  | /* VIDEO DAC */
		      (1 << 7)  | /* AK4643 */
		      (1 << 8)  | /* IrDA */
		      (1 << 12) | /* USB0 */
		      (1 << 14)); /* RMII */
	__raw_ग_लिखोw(fpga_out | (1 << 4), FPGA_OUT);

	udelay(10);

	/* AK8813 RESET */
	__raw_ग_लिखोw(fpga_out | (1 << 5), FPGA_OUT);

	udelay(10);

	__raw_ग_लिखोw(fpga_out, FPGA_OUT);

	/* turn on USB घड़ीs, use बाह्यal घड़ी */
	__raw_ग_लिखोw((__raw_पढ़ोw(PORT_MSELCRB) & ~0xc000) | 0x8000, PORT_MSELCRB);

	/* Let LED9 show STATUS2 */
	gpio_request(GPIO_FN_STATUS2, शून्य);

	/* Lit LED10 show STATUS0 */
	gpio_request(GPIO_FN_STATUS0, शून्य);

	/* Lit LED11 show PDSTATUS */
	gpio_request(GPIO_FN_PDSTATUS, शून्य);

	/* enable USB0 port */
	__raw_ग_लिखोw(0x0600, 0xa40501d4);

	/* enable USB1 port */
	__raw_ग_लिखोw(0x0600, 0xa4050192);

	/* enable IRQ 0,1,2 */
	gpio_request(GPIO_FN_INTC_IRQ0, शून्य);
	gpio_request(GPIO_FN_INTC_IRQ1, शून्य);
	gpio_request(GPIO_FN_INTC_IRQ2, शून्य);

	/* enable SCIFA3 */
	gpio_request(GPIO_FN_SCIF3_I_SCK, शून्य);
	gpio_request(GPIO_FN_SCIF3_I_RXD, शून्य);
	gpio_request(GPIO_FN_SCIF3_I_TXD, शून्य);
	gpio_request(GPIO_FN_SCIF3_I_CTS, शून्य);
	gpio_request(GPIO_FN_SCIF3_I_RTS, शून्य);

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
	gpio_request(GPIO_FN_LCDVEPWC, शून्य);
	gpio_request(GPIO_FN_LCDVCPWC, शून्य);
	gpio_request(GPIO_FN_LCDRD,    शून्य);
	gpio_request(GPIO_FN_LCDLCLK,  शून्य);
	__raw_ग_लिखोw((__raw_पढ़ोw(PORT_HIZA) & ~0x0001), PORT_HIZA);

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

	/* KEYSC */
	gpio_request(GPIO_FN_KEYOUT5_IN5, शून्य);
	gpio_request(GPIO_FN_KEYOUT4_IN6, शून्य);
	gpio_request(GPIO_FN_KEYIN4,      शून्य);
	gpio_request(GPIO_FN_KEYIN3,      शून्य);
	gpio_request(GPIO_FN_KEYIN2,      शून्य);
	gpio_request(GPIO_FN_KEYIN1,      शून्य);
	gpio_request(GPIO_FN_KEYIN0,      शून्य);
	gpio_request(GPIO_FN_KEYOUT3,     शून्य);
	gpio_request(GPIO_FN_KEYOUT2,     शून्य);
	gpio_request(GPIO_FN_KEYOUT1,     शून्य);
	gpio_request(GPIO_FN_KEYOUT0,     शून्य);

	/* enable FSI */
	gpio_request(GPIO_FN_FSIMCKA,    शून्य);
	gpio_request(GPIO_FN_FSIIASD,    शून्य);
	gpio_request(GPIO_FN_FSIOASD,    शून्य);
	gpio_request(GPIO_FN_FSIIABCK,   शून्य);
	gpio_request(GPIO_FN_FSIIALRCK,  शून्य);
	gpio_request(GPIO_FN_FSIOABCK,   शून्य);
	gpio_request(GPIO_FN_FSIOALRCK,  शून्य);
	gpio_request(GPIO_FN_CLKAUDIOAO, शून्य);

	/* set SPU2 घड़ी to 83.4 MHz */
	clk = clk_get(शून्य, "spu_clk");
	अगर (!IS_ERR(clk)) अणु
		clk_set_rate(clk, clk_round_rate(clk, 83333333));
		clk_put(clk);
	पूर्ण

	/* change parent of FSI A */
	clk = clk_get(शून्य, "fsia_clk");
	अगर (!IS_ERR(clk)) अणु
		/* 48kHz dummy घड़ी was used to make sure 1/1 भागide */
		clk_set_rate(&sh7724_fsimcka_clk, 48000);
		clk_set_parent(clk, &sh7724_fsimcka_clk);
		clk_set_rate(clk, 48000);
		clk_put(clk);
	पूर्ण

	/* SDHI0 connected to cn7 */
	gpio_request(GPIO_FN_SDHI0CD, शून्य);
	gpio_request(GPIO_FN_SDHI0WP, शून्य);
	gpio_request(GPIO_FN_SDHI0D3, शून्य);
	gpio_request(GPIO_FN_SDHI0D2, शून्य);
	gpio_request(GPIO_FN_SDHI0D1, शून्य);
	gpio_request(GPIO_FN_SDHI0D0, शून्य);
	gpio_request(GPIO_FN_SDHI0CMD, शून्य);
	gpio_request(GPIO_FN_SDHI0CLK, शून्य);

	/* SDHI1 connected to cn8 */
	gpio_request(GPIO_FN_SDHI1CD, शून्य);
	gpio_request(GPIO_FN_SDHI1WP, शून्य);
	gpio_request(GPIO_FN_SDHI1D3, शून्य);
	gpio_request(GPIO_FN_SDHI1D2, शून्य);
	gpio_request(GPIO_FN_SDHI1D1, शून्य);
	gpio_request(GPIO_FN_SDHI1D0, शून्य);
	gpio_request(GPIO_FN_SDHI1CMD, शून्य);
	gpio_request(GPIO_FN_SDHI1CLK, शून्य);

	/* enable IrDA */
	gpio_request(GPIO_FN_IRDA_OUT, शून्य);
	gpio_request(GPIO_FN_IRDA_IN,  शून्य);

	/*
	 * enable SH-Eth
	 *
	 * please हटाओ J33 pin from your board !!
	 *
	 * ms7724 board should not use GPIO_FN_LNKSTA pin
	 * So, This समय PTX5 is set to input pin
	 */
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
	gpio_request(GPIO_PTX5, शून्य);
	gpio_direction_input(GPIO_PTX5);
	sh_eth_init();

	अगर (sw & SW41_B) अणु
		/* 720p */
		lcdc_info.ch[0].lcd_modes = lcdc_720p_modes;
		lcdc_info.ch[0].num_modes = ARRAY_SIZE(lcdc_720p_modes);
	पूर्ण अन्यथा अणु
		/* VGA */
		lcdc_info.ch[0].lcd_modes = lcdc_vga_modes;
		lcdc_info.ch[0].num_modes = ARRAY_SIZE(lcdc_vga_modes);
	पूर्ण

	अगर (sw & SW41_A) अणु
		/* Digital monitor */
		lcdc_info.ch[0].पूर्णांकerface_type = RGB18;
		lcdc_info.ch[0].flags          = 0;
	पूर्ण अन्यथा अणु
		/* Analog monitor */
		lcdc_info.ch[0].पूर्णांकerface_type = RGB24;
		lcdc_info.ch[0].flags          = LCDC_FLAGS_DWPOL;
	पूर्ण

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

	/* Initialize CEU platक्रमm devices separately to map memory first */
	device_initialize(&ms7724se_ceu_devices[0]->dev);
	dma_declare_coherent_memory(&ms7724se_ceu_devices[0]->dev,
				    ceu0_dma_membase, ceu0_dma_membase,
				    ceu0_dma_membase +
				    CEU_BUFFER_MEMORY_SIZE - 1);
	platक्रमm_device_add(ms7724se_ceu_devices[0]);

	device_initialize(&ms7724se_ceu_devices[1]->dev);
	dma_declare_coherent_memory(&ms7724se_ceu_devices[1]->dev,
				    ceu1_dma_membase, ceu1_dma_membase,
				    ceu1_dma_membase +
				    CEU_BUFFER_MEMORY_SIZE - 1);
	platक्रमm_device_add(ms7724se_ceu_devices[1]);

	वापस platक्रमm_add_devices(ms7724se_devices,
				    ARRAY_SIZE(ms7724se_devices));
पूर्ण
device_initcall(devices_setup);

/* Reserve a portion of memory क्रम CEU 0 and CEU 1 buffers */
अटल व्योम __init ms7724se_mv_mem_reserve(व्योम)
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

अटल काष्ठा sh_machine_vector mv_ms7724se __iniपंचांगv = अणु
	.mv_name	= "ms7724se",
	.mv_init_irq	= init_se7724_IRQ,
	.mv_mem_reserve	= ms7724se_mv_mem_reserve,
पूर्ण;
