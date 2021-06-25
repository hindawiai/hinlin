<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R0P7757LC0012RL Support.
 *
 * Copyright (C) 2009 - 2010  Renesas Solutions Corp.
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/irq.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sh_mmcअगर.h>
#समावेश <linux/sh_eth.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/usb/renesas_usbhs.h>
#समावेश <cpu/sh7757.h>
#समावेश <यंत्र/heartbeat.h>

अटल काष्ठा resource heartbeat_resource = अणु
	.start	= 0xffec005c,	/* PUDR */
	.end	= 0xffec005c,
	.flags	= IORESOURCE_MEM | IORESOURCE_MEM_8BIT,
पूर्ण;

अटल अचिन्हित अक्षर heartbeat_bit_pos[] = अणु 0, 1, 2, 3 पूर्ण;

अटल काष्ठा heartbeat_data heartbeat_data = अणु
	.bit_pos	= heartbeat_bit_pos,
	.nr_bits	= ARRAY_SIZE(heartbeat_bit_pos),
	.flags		= HEARTBEAT_INVERTED,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name		= "heartbeat",
	.id		= -1,
	.dev	= अणु
		.platक्रमm_data	= &heartbeat_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &heartbeat_resource,
पूर्ण;

/* Fast Ethernet */
#घोषणा GBECONT		0xffc10100
#घोषणा GBECONT_RMII1	BIT(17)
#घोषणा GBECONT_RMII0	BIT(16)
अटल व्योम sh7757_eth_set_mdio_gate(व्योम *addr)
अणु
	अगर (((अचिन्हित दीर्घ)addr & 0x00000fff) < 0x0800)
		ग_लिखोl(पढ़ोl(GBECONT) | GBECONT_RMII0, GBECONT);
	अन्यथा
		ग_लिखोl(पढ़ोl(GBECONT) | GBECONT_RMII1, GBECONT);
पूर्ण

अटल काष्ठा resource sh_eth0_resources[] = अणु
	अणु
		.start  = 0xfef00000,
		.end    = 0xfef001ff,
		.flags  = IORESOURCE_MEM,
	पूर्ण, अणु
		.start  = evt2irq(0xc80),
		.end    = evt2irq(0xc80),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_eth_plat_data sh7757_eth0_pdata = अणु
	.phy = 1,
	.set_mdio_gate = sh7757_eth_set_mdio_gate,
पूर्ण;

अटल काष्ठा platक्रमm_device sh7757_eth0_device = अणु
	.name		= "sh7757-ether",
	.resource	= sh_eth0_resources,
	.id		= 0,
	.num_resources	= ARRAY_SIZE(sh_eth0_resources),
	.dev		= अणु
		.platक्रमm_data = &sh7757_eth0_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sh_eth1_resources[] = अणु
	अणु
		.start  = 0xfef00800,
		.end    = 0xfef009ff,
		.flags  = IORESOURCE_MEM,
	पूर्ण, अणु
		.start  = evt2irq(0xc80),
		.end    = evt2irq(0xc80),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_eth_plat_data sh7757_eth1_pdata = अणु
	.phy = 1,
	.set_mdio_gate = sh7757_eth_set_mdio_gate,
पूर्ण;

अटल काष्ठा platक्रमm_device sh7757_eth1_device = अणु
	.name		= "sh7757-ether",
	.resource	= sh_eth1_resources,
	.id		= 1,
	.num_resources	= ARRAY_SIZE(sh_eth1_resources),
	.dev		= अणु
		.platक्रमm_data = &sh7757_eth1_pdata,
	पूर्ण,
पूर्ण;

अटल व्योम sh7757_eth_giga_set_mdio_gate(व्योम *addr)
अणु
	अगर (((अचिन्हित दीर्घ)addr & 0x00000fff) < 0x0800) अणु
		gpio_set_value(GPIO_PTT4, 1);
		ग_लिखोl(पढ़ोl(GBECONT) & ~GBECONT_RMII0, GBECONT);
	पूर्ण अन्यथा अणु
		gpio_set_value(GPIO_PTT4, 0);
		ग_लिखोl(पढ़ोl(GBECONT) & ~GBECONT_RMII1, GBECONT);
	पूर्ण
पूर्ण

अटल काष्ठा resource sh_eth_giga0_resources[] = अणु
	अणु
		.start  = 0xfee00000,
		.end    = 0xfee007ff,
		.flags  = IORESOURCE_MEM,
	पूर्ण, अणु
		/* TSU */
		.start  = 0xfee01800,
		.end    = 0xfee01fff,
		.flags  = IORESOURCE_MEM,
	पूर्ण, अणु
		.start  = evt2irq(0x2960),
		.end    = evt2irq(0x2960),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_eth_plat_data sh7757_eth_giga0_pdata = अणु
	.phy = 18,
	.set_mdio_gate = sh7757_eth_giga_set_mdio_gate,
	.phy_पूर्णांकerface = PHY_INTERFACE_MODE_RGMII_ID,
पूर्ण;

अटल काष्ठा platक्रमm_device sh7757_eth_giga0_device = अणु
	.name		= "sh7757-gether",
	.resource	= sh_eth_giga0_resources,
	.id		= 2,
	.num_resources	= ARRAY_SIZE(sh_eth_giga0_resources),
	.dev		= अणु
		.platक्रमm_data = &sh7757_eth_giga0_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sh_eth_giga1_resources[] = अणु
	अणु
		.start  = 0xfee00800,
		.end    = 0xfee00fff,
		.flags  = IORESOURCE_MEM,
	पूर्ण, अणु
		/* TSU */
		.start  = 0xfee01800,
		.end    = 0xfee01fff,
		.flags  = IORESOURCE_MEM,
	पूर्ण, अणु
		.start  = evt2irq(0x2980),
		.end    = evt2irq(0x2980),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_eth_plat_data sh7757_eth_giga1_pdata = अणु
	.phy = 19,
	.set_mdio_gate = sh7757_eth_giga_set_mdio_gate,
	.phy_पूर्णांकerface = PHY_INTERFACE_MODE_RGMII_ID,
पूर्ण;

अटल काष्ठा platक्रमm_device sh7757_eth_giga1_device = अणु
	.name		= "sh7757-gether",
	.resource	= sh_eth_giga1_resources,
	.id		= 3,
	.num_resources	= ARRAY_SIZE(sh_eth_giga1_resources),
	.dev		= अणु
		.platक्रमm_data = &sh7757_eth_giga1_pdata,
	पूर्ण,
पूर्ण;

/* Fixed 3.3V regulator to be used by SDHI0, MMCIF */
अटल काष्ठा regulator_consumer_supply fixed3v3_घातer_consumers[] =
अणु
	REGULATOR_SUPPLY("vmmc", "sh_mobile_sdhi.0"),
	REGULATOR_SUPPLY("vqmmc", "sh_mobile_sdhi.0"),
	REGULATOR_SUPPLY("vmmc", "sh_mmcif.0"),
	REGULATOR_SUPPLY("vqmmc", "sh_mmcif.0"),
पूर्ण;

/* SH_MMCIF */
अटल काष्ठा resource sh_mmcअगर_resources[] = अणु
	[0] = अणु
		.start	= 0xffcb0000,
		.end	= 0xffcb00ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0x1c60),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	[2] = अणु
		.start	= evt2irq(0x1c80),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा sh_mmcअगर_plat_data sh_mmcअगर_plat = अणु
	.sup_pclk	= 0x0f,
	.caps		= MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA |
			  MMC_CAP_NONREMOVABLE,
	.ocr		= MMC_VDD_32_33 | MMC_VDD_33_34,
	.slave_id_tx	= SHDMA_SLAVE_MMCIF_TX,
	.slave_id_rx	= SHDMA_SLAVE_MMCIF_RX,
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

/* SDHI0 */
अटल काष्ठा पंचांगio_mmc_data sdhi_info = अणु
	.chan_priv_tx	= (व्योम *)SHDMA_SLAVE_SDHI_TX,
	.chan_priv_rx	= (व्योम *)SHDMA_SLAVE_SDHI_RX,
	.capabilities	= MMC_CAP_SD_HIGHSPEED,
पूर्ण;

अटल काष्ठा resource sdhi_resources[] = अणु
	[0] = अणु
		.start  = 0xffe50000,
		.end    = 0xffe500ff,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = evt2irq(0x480),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sdhi_device = अणु
	.name           = "sh_mobile_sdhi",
	.num_resources  = ARRAY_SIZE(sdhi_resources),
	.resource       = sdhi_resources,
	.id             = 0,
	.dev	= अणु
		.platक्रमm_data	= &sdhi_info,
	पूर्ण,
पूर्ण;

अटल पूर्णांक usbhs0_get_id(काष्ठा platक्रमm_device *pdev)
अणु
	वापस USBHS_GADGET;
पूर्ण

अटल काष्ठा renesas_usbhs_platक्रमm_info usb0_data = अणु
	.platक्रमm_callback = अणु
		.get_id = usbhs0_get_id,
	पूर्ण,
	.driver_param = अणु
		.busरुको_bरुको = 5,
	पूर्ण
पूर्ण;

अटल काष्ठा resource usb0_resources[] = अणु
	[0] = अणु
		.start	= 0xfe450000,
		.end	= 0xfe4501ff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0x840),
		.end	= evt2irq(0x840),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device usb0_device = अणु
	.name		= "renesas_usbhs",
	.id		= 0,
	.dev = अणु
		.platक्रमm_data		= &usb0_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(usb0_resources),
	.resource	= usb0_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7757lcr_devices[] __initdata = अणु
	&heartbeat_device,
	&sh7757_eth0_device,
	&sh7757_eth1_device,
	&sh7757_eth_giga0_device,
	&sh7757_eth_giga1_device,
	&sh_mmcअगर_device,
	&sdhi_device,
	&usb0_device,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data spi_flash_data = अणु
	.name = "m25p80",
	.type = "m25px64",
पूर्ण;

अटल काष्ठा spi_board_info spi_board_info[] = अणु
	अणु
		.modalias = "m25p80",
		.max_speed_hz = 25000000,
		.bus_num = 0,
		.chip_select = 1,
		.platक्रमm_data = &spi_flash_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sh7757lcr_devices_setup(व्योम)
अणु
	regulator_रेजिस्टर_always_on(0, "fixed-3.3V", fixed3v3_घातer_consumers,
				     ARRAY_SIZE(fixed3v3_घातer_consumers), 3300000);

	/* RGMII (PTA) */
	gpio_request(GPIO_FN_ET0_MDC, शून्य);
	gpio_request(GPIO_FN_ET0_MDIO, शून्य);
	gpio_request(GPIO_FN_ET1_MDC, शून्य);
	gpio_request(GPIO_FN_ET1_MDIO, शून्य);

	/* ONFI (PTB, PTZ) */
	gpio_request(GPIO_FN_ON_NRE, शून्य);
	gpio_request(GPIO_FN_ON_NWE, शून्य);
	gpio_request(GPIO_FN_ON_NWP, शून्य);
	gpio_request(GPIO_FN_ON_NCE0, शून्य);
	gpio_request(GPIO_FN_ON_R_B0, शून्य);
	gpio_request(GPIO_FN_ON_ALE, शून्य);
	gpio_request(GPIO_FN_ON_CLE, शून्य);

	gpio_request(GPIO_FN_ON_DQ7, शून्य);
	gpio_request(GPIO_FN_ON_DQ6, शून्य);
	gpio_request(GPIO_FN_ON_DQ5, शून्य);
	gpio_request(GPIO_FN_ON_DQ4, शून्य);
	gpio_request(GPIO_FN_ON_DQ3, शून्य);
	gpio_request(GPIO_FN_ON_DQ2, शून्य);
	gpio_request(GPIO_FN_ON_DQ1, शून्य);
	gpio_request(GPIO_FN_ON_DQ0, शून्य);

	/* IRQ8 to 0 (PTB, PTC) */
	gpio_request(GPIO_FN_IRQ8, शून्य);
	gpio_request(GPIO_FN_IRQ7, शून्य);
	gpio_request(GPIO_FN_IRQ6, शून्य);
	gpio_request(GPIO_FN_IRQ5, शून्य);
	gpio_request(GPIO_FN_IRQ4, शून्य);
	gpio_request(GPIO_FN_IRQ3, शून्य);
	gpio_request(GPIO_FN_IRQ2, शून्य);
	gpio_request(GPIO_FN_IRQ1, शून्य);
	gpio_request(GPIO_FN_IRQ0, शून्य);

	/* SPI0 (PTD) */
	gpio_request(GPIO_FN_SP0_MOSI, शून्य);
	gpio_request(GPIO_FN_SP0_MISO, शून्य);
	gpio_request(GPIO_FN_SP0_SCK, शून्य);
	gpio_request(GPIO_FN_SP0_SCK_FB, शून्य);
	gpio_request(GPIO_FN_SP0_SS0, शून्य);
	gpio_request(GPIO_FN_SP0_SS1, शून्य);
	gpio_request(GPIO_FN_SP0_SS2, शून्य);
	gpio_request(GPIO_FN_SP0_SS3, शून्य);

	/* RMII 0/1 (PTE, PTF) */
	gpio_request(GPIO_FN_RMII0_CRS_DV, शून्य);
	gpio_request(GPIO_FN_RMII0_TXD1, शून्य);
	gpio_request(GPIO_FN_RMII0_TXD0, शून्य);
	gpio_request(GPIO_FN_RMII0_TXEN, शून्य);
	gpio_request(GPIO_FN_RMII0_REFCLK, शून्य);
	gpio_request(GPIO_FN_RMII0_RXD1, शून्य);
	gpio_request(GPIO_FN_RMII0_RXD0, शून्य);
	gpio_request(GPIO_FN_RMII0_RX_ER, शून्य);
	gpio_request(GPIO_FN_RMII1_CRS_DV, शून्य);
	gpio_request(GPIO_FN_RMII1_TXD1, शून्य);
	gpio_request(GPIO_FN_RMII1_TXD0, शून्य);
	gpio_request(GPIO_FN_RMII1_TXEN, शून्य);
	gpio_request(GPIO_FN_RMII1_REFCLK, शून्य);
	gpio_request(GPIO_FN_RMII1_RXD1, शून्य);
	gpio_request(GPIO_FN_RMII1_RXD0, शून्य);
	gpio_request(GPIO_FN_RMII1_RX_ER, शून्य);

	/* eMMC (PTG) */
	gpio_request(GPIO_FN_MMCCLK, शून्य);
	gpio_request(GPIO_FN_MMCCMD, शून्य);
	gpio_request(GPIO_FN_MMCDAT7, शून्य);
	gpio_request(GPIO_FN_MMCDAT6, शून्य);
	gpio_request(GPIO_FN_MMCDAT5, शून्य);
	gpio_request(GPIO_FN_MMCDAT4, शून्य);
	gpio_request(GPIO_FN_MMCDAT3, शून्य);
	gpio_request(GPIO_FN_MMCDAT2, शून्य);
	gpio_request(GPIO_FN_MMCDAT1, शून्य);
	gpio_request(GPIO_FN_MMCDAT0, शून्य);

	/* LPC (PTG, PTH, PTQ, PTU) */
	gpio_request(GPIO_FN_SERIRQ, शून्य);
	gpio_request(GPIO_FN_LPCPD, शून्य);
	gpio_request(GPIO_FN_LDRQ, शून्य);
	gpio_request(GPIO_FN_WP, शून्य);
	gpio_request(GPIO_FN_FMS0, शून्य);
	gpio_request(GPIO_FN_LAD3, शून्य);
	gpio_request(GPIO_FN_LAD2, शून्य);
	gpio_request(GPIO_FN_LAD1, शून्य);
	gpio_request(GPIO_FN_LAD0, शून्य);
	gpio_request(GPIO_FN_LFRAME, शून्य);
	gpio_request(GPIO_FN_LRESET, शून्य);
	gpio_request(GPIO_FN_LCLK, शून्य);
	gpio_request(GPIO_FN_LGPIO7, शून्य);
	gpio_request(GPIO_FN_LGPIO6, शून्य);
	gpio_request(GPIO_FN_LGPIO5, शून्य);
	gpio_request(GPIO_FN_LGPIO4, शून्य);

	/* SPI1 (PTH) */
	gpio_request(GPIO_FN_SP1_MOSI, शून्य);
	gpio_request(GPIO_FN_SP1_MISO, शून्य);
	gpio_request(GPIO_FN_SP1_SCK, शून्य);
	gpio_request(GPIO_FN_SP1_SCK_FB, शून्य);
	gpio_request(GPIO_FN_SP1_SS0, शून्य);
	gpio_request(GPIO_FN_SP1_SS1, शून्य);

	/* SDHI (PTI) */
	gpio_request(GPIO_FN_SD_WP, शून्य);
	gpio_request(GPIO_FN_SD_CD, शून्य);
	gpio_request(GPIO_FN_SD_CLK, शून्य);
	gpio_request(GPIO_FN_SD_CMD, शून्य);
	gpio_request(GPIO_FN_SD_D3, शून्य);
	gpio_request(GPIO_FN_SD_D2, शून्य);
	gpio_request(GPIO_FN_SD_D1, शून्य);
	gpio_request(GPIO_FN_SD_D0, शून्य);

	/* SCIF3/4 (PTJ, PTW) */
	gpio_request(GPIO_FN_RTS3, शून्य);
	gpio_request(GPIO_FN_CTS3, शून्य);
	gpio_request(GPIO_FN_TXD3, शून्य);
	gpio_request(GPIO_FN_RXD3, शून्य);
	gpio_request(GPIO_FN_RTS4, शून्य);
	gpio_request(GPIO_FN_RXD4, शून्य);
	gpio_request(GPIO_FN_TXD4, शून्य);
	gpio_request(GPIO_FN_CTS4, शून्य);

	/* SERMUX (PTK, PTL, PTO, PTV) */
	gpio_request(GPIO_FN_COM2_TXD, शून्य);
	gpio_request(GPIO_FN_COM2_RXD, शून्य);
	gpio_request(GPIO_FN_COM2_RTS, शून्य);
	gpio_request(GPIO_FN_COM2_CTS, शून्य);
	gpio_request(GPIO_FN_COM2_DTR, शून्य);
	gpio_request(GPIO_FN_COM2_DSR, शून्य);
	gpio_request(GPIO_FN_COM2_DCD, शून्य);
	gpio_request(GPIO_FN_COM2_RI, शून्य);
	gpio_request(GPIO_FN_RAC_RXD, शून्य);
	gpio_request(GPIO_FN_RAC_RTS, शून्य);
	gpio_request(GPIO_FN_RAC_CTS, शून्य);
	gpio_request(GPIO_FN_RAC_DTR, शून्य);
	gpio_request(GPIO_FN_RAC_DSR, शून्य);
	gpio_request(GPIO_FN_RAC_DCD, शून्य);
	gpio_request(GPIO_FN_RAC_TXD, शून्य);
	gpio_request(GPIO_FN_COM1_TXD, शून्य);
	gpio_request(GPIO_FN_COM1_RXD, शून्य);
	gpio_request(GPIO_FN_COM1_RTS, शून्य);
	gpio_request(GPIO_FN_COM1_CTS, शून्य);

	ग_लिखोb(0x10, 0xfe470000);	/* SMR0: SerMux mode 0 */

	/* IIC (PTM, PTR, PTS) */
	gpio_request(GPIO_FN_SDA7, शून्य);
	gpio_request(GPIO_FN_SCL7, शून्य);
	gpio_request(GPIO_FN_SDA6, शून्य);
	gpio_request(GPIO_FN_SCL6, शून्य);
	gpio_request(GPIO_FN_SDA5, शून्य);
	gpio_request(GPIO_FN_SCL5, शून्य);
	gpio_request(GPIO_FN_SDA4, शून्य);
	gpio_request(GPIO_FN_SCL4, शून्य);
	gpio_request(GPIO_FN_SDA3, शून्य);
	gpio_request(GPIO_FN_SCL3, शून्य);
	gpio_request(GPIO_FN_SDA2, शून्य);
	gpio_request(GPIO_FN_SCL2, शून्य);
	gpio_request(GPIO_FN_SDA1, शून्य);
	gpio_request(GPIO_FN_SCL1, शून्य);
	gpio_request(GPIO_FN_SDA0, शून्य);
	gpio_request(GPIO_FN_SCL0, शून्य);

	/* USB (PTN) */
	gpio_request(GPIO_FN_VBUS_EN, शून्य);
	gpio_request(GPIO_FN_VBUS_OC, शून्य);

	/* SGPIO1/0 (PTN, PTO) */
	gpio_request(GPIO_FN_SGPIO1_CLK, शून्य);
	gpio_request(GPIO_FN_SGPIO1_LOAD, शून्य);
	gpio_request(GPIO_FN_SGPIO1_DI, शून्य);
	gpio_request(GPIO_FN_SGPIO1_DO, शून्य);
	gpio_request(GPIO_FN_SGPIO0_CLK, शून्य);
	gpio_request(GPIO_FN_SGPIO0_LOAD, शून्य);
	gpio_request(GPIO_FN_SGPIO0_DI, शून्य);
	gpio_request(GPIO_FN_SGPIO0_DO, शून्य);

	/* WDT (PTN) */
	gpio_request(GPIO_FN_SUB_CLKIN, शून्य);

	/* System (PTT) */
	gpio_request(GPIO_FN_STATUS1, शून्य);
	gpio_request(GPIO_FN_STATUS0, शून्य);

	/* PWMX (PTT) */
	gpio_request(GPIO_FN_PWMX1, शून्य);
	gpio_request(GPIO_FN_PWMX0, शून्य);

	/* R-SPI (PTV) */
	gpio_request(GPIO_FN_R_SPI_MOSI, शून्य);
	gpio_request(GPIO_FN_R_SPI_MISO, शून्य);
	gpio_request(GPIO_FN_R_SPI_RSPCK, शून्य);
	gpio_request(GPIO_FN_R_SPI_SSL0, शून्य);
	gpio_request(GPIO_FN_R_SPI_SSL1, शून्य);

	/* EVC (PTV, PTW) */
	gpio_request(GPIO_FN_EVENT7, शून्य);
	gpio_request(GPIO_FN_EVENT6, शून्य);
	gpio_request(GPIO_FN_EVENT5, शून्य);
	gpio_request(GPIO_FN_EVENT4, शून्य);
	gpio_request(GPIO_FN_EVENT3, शून्य);
	gpio_request(GPIO_FN_EVENT2, शून्य);
	gpio_request(GPIO_FN_EVENT1, शून्य);
	gpio_request(GPIO_FN_EVENT0, शून्य);

	/* LED क्रम heartbeat */
	gpio_request(GPIO_PTU3, शून्य);
	gpio_direction_output(GPIO_PTU3, 1);
	gpio_request(GPIO_PTU2, शून्य);
	gpio_direction_output(GPIO_PTU2, 1);
	gpio_request(GPIO_PTU1, शून्य);
	gpio_direction_output(GPIO_PTU1, 1);
	gpio_request(GPIO_PTU0, शून्य);
	gpio_direction_output(GPIO_PTU0, 1);

	/* control क्रम MDIO of Gigabit Ethernet */
	gpio_request(GPIO_PTT4, शून्य);
	gpio_direction_output(GPIO_PTT4, 1);

	/* control क्रम eMMC */
	gpio_request(GPIO_PTT7, शून्य);		/* eMMC_RST# */
	gpio_direction_output(GPIO_PTT7, 0);
	gpio_request(GPIO_PTT6, शून्य);		/* eMMC_INDEX# */
	gpio_direction_output(GPIO_PTT6, 0);
	gpio_request(GPIO_PTT5, शून्य);		/* eMMC_PRST# */
	gpio_direction_output(GPIO_PTT5, 1);

	/* रेजिस्टर SPI device inक्रमmation */
	spi_रेजिस्टर_board_info(spi_board_info,
				ARRAY_SIZE(spi_board_info));

	/* General platक्रमm */
	वापस platक्रमm_add_devices(sh7757lcr_devices,
				    ARRAY_SIZE(sh7757lcr_devices));
पूर्ण
arch_initcall(sh7757lcr_devices_setup);

/* Initialize IRQ setting */
व्योम __init init_sh7757lcr_IRQ(व्योम)
अणु
	plat_irq_setup_pins(IRQ_MODE_IRQ7654);
	plat_irq_setup_pins(IRQ_MODE_IRQ3210);
पूर्ण

/* Initialize the board */
अटल व्योम __init sh7757lcr_setup(अक्षर **cmdline_p)
अणु
	prपूर्णांकk(KERN_INFO "Renesas R0P7757LC0012RL support.\n");
पूर्ण

अटल पूर्णांक sh7757lcr_mode_pins(व्योम)
अणु
	पूर्णांक value = 0;

	/* These are the factory शेष settings of S3 (Low active).
	 * If you change these dip चयनes then you will need to
	 * adjust the values below as well.
	 */
	value |= MODE_PIN0;	/* Clock Mode: 1 */

	वापस value;
पूर्ण

/* The Machine Vector */
अटल काष्ठा sh_machine_vector mv_sh7757lcr __iniपंचांगv = अणु
	.mv_name		= "SH7757LCR",
	.mv_setup		= sh7757lcr_setup,
	.mv_init_irq		= init_sh7757lcr_IRQ,
	.mv_mode_pins		= sh7757lcr_mode_pins,
पूर्ण;

