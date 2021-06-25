<शैली गुरु>
/*
 * Hawkboard.org based on TI's OMAP-L138 Platक्रमm
 *
 * Initial code: Syed Mohammed Khasim
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - https://www.ti.com
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of
 * any kind, whether express or implied.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/platक्रमm_data/gpio-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci-aemअगर.h>
#समावेश <linux/platक्रमm_data/ti-aemअगर.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश <mach/common.h>
#समावेश <mach/da8xx.h>
#समावेश <mach/mux.h>

#घोषणा HAWKBOARD_PHY_ID		"davinci_mdio-0:07"

#घोषणा DA850_USB1_VBUS_PIN		GPIO_TO_PIN(2, 4)
#घोषणा DA850_USB1_OC_PIN		GPIO_TO_PIN(6, 13)

अटल लघु omapl138_hawk_mii_pins[] __initdata = अणु
	DA850_MII_TXEN, DA850_MII_TXCLK, DA850_MII_COL, DA850_MII_TXD_3,
	DA850_MII_TXD_2, DA850_MII_TXD_1, DA850_MII_TXD_0, DA850_MII_RXER,
	DA850_MII_CRS, DA850_MII_RXCLK, DA850_MII_RXDV, DA850_MII_RXD_3,
	DA850_MII_RXD_2, DA850_MII_RXD_1, DA850_MII_RXD_0, DA850_MDIO_CLK,
	DA850_MDIO_D,
	-1
पूर्ण;

अटल __init व्योम omapl138_hawk_config_emac(व्योम)
अणु
	व्योम __iomem *cfgchip3 = DA8XX_SYSCFG0_VIRT(DA8XX_CFGCHIP3_REG);
	पूर्णांक ret;
	u32 val;
	काष्ठा davinci_soc_info *soc_info = &davinci_soc_info;

	val = __raw_पढ़ोl(cfgchip3);
	val &= ~BIT(8);
	ret = davinci_cfg_reg_list(omapl138_hawk_mii_pins);
	अगर (ret) अणु
		pr_warn("%s: CPGMAC/MII mux setup failed: %d\n", __func__, ret);
		वापस;
	पूर्ण

	/* configure the CFGCHIP3 रेजिस्टर क्रम MII */
	__raw_ग_लिखोl(val, cfgchip3);
	pr_info("EMAC: MII PHY configured\n");

	soc_info->emac_pdata->phy_id = HAWKBOARD_PHY_ID;

	ret = da8xx_रेजिस्टर_emac();
	अगर (ret)
		pr_warn("%s: EMAC registration failed: %d\n", __func__, ret);
पूर्ण

/*
 * The following EDMA channels/slots are not being used by drivers (क्रम
 * example: Timer, GPIO, UART events etc) on da850/omap-l138 EVM/Hawkboard,
 * hence they are being reserved क्रम codecs on the DSP side.
 */
अटल स्थिर s16 da850_dma0_rsv_chans[][2] = अणु
	/* (offset, number) */
	अणु 8,  6पूर्ण,
	अणु24,  4पूर्ण,
	अणु30,  2पूर्ण,
	अणु-1, -1पूर्ण
पूर्ण;

अटल स्थिर s16 da850_dma0_rsv_slots[][2] = अणु
	/* (offset, number) */
	अणु 8,  6पूर्ण,
	अणु24,  4पूर्ण,
	अणु30, 50पूर्ण,
	अणु-1, -1पूर्ण
पूर्ण;

अटल स्थिर s16 da850_dma1_rsv_chans[][2] = अणु
	/* (offset, number) */
	अणु 0, 28पूर्ण,
	अणु30,  2पूर्ण,
	अणु-1, -1पूर्ण
पूर्ण;

अटल स्थिर s16 da850_dma1_rsv_slots[][2] = अणु
	/* (offset, number) */
	अणु 0, 28पूर्ण,
	अणु30, 90पूर्ण,
	अणु-1, -1पूर्ण
पूर्ण;

अटल काष्ठा edma_rsv_info da850_edma_cc0_rsv = अणु
	.rsv_chans	= da850_dma0_rsv_chans,
	.rsv_slots	= da850_dma0_rsv_slots,
पूर्ण;

अटल काष्ठा edma_rsv_info da850_edma_cc1_rsv = अणु
	.rsv_chans	= da850_dma1_rsv_chans,
	.rsv_slots	= da850_dma1_rsv_slots,
पूर्ण;

अटल काष्ठा edma_rsv_info *da850_edma_rsv[2] = अणु
	&da850_edma_cc0_rsv,
	&da850_edma_cc1_rsv,
पूर्ण;

अटल स्थिर लघु hawk_mmcsd0_pins[] = अणु
	DA850_MMCSD0_DAT_0, DA850_MMCSD0_DAT_1, DA850_MMCSD0_DAT_2,
	DA850_MMCSD0_DAT_3, DA850_MMCSD0_CLK, DA850_MMCSD0_CMD,
	DA850_GPIO3_12, DA850_GPIO3_13,
	-1
पूर्ण;

#घोषणा DA850_HAWK_MMCSD_CD_PIN		GPIO_TO_PIN(3, 12)
#घोषणा DA850_HAWK_MMCSD_WP_PIN		GPIO_TO_PIN(3, 13)

अटल काष्ठा gpiod_lookup_table mmc_gpios_table = अणु
	.dev_id = "da830-mmc.0",
	.table = अणु
		GPIO_LOOKUP("davinci_gpio", DA850_HAWK_MMCSD_CD_PIN, "cd",
			    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("davinci_gpio", DA850_HAWK_MMCSD_WP_PIN, "wp",
			    GPIO_ACTIVE_LOW),
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_mmc_config da850_mmc_config = अणु
	.wires		= 4,
	.max_freq	= 50000000,
	.caps		= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED,
पूर्ण;

अटल __init व्योम omapl138_hawk_mmc_init(व्योम)
अणु
	पूर्णांक ret;

	ret = davinci_cfg_reg_list(hawk_mmcsd0_pins);
	अगर (ret) अणु
		pr_warn("%s: MMC/SD0 mux setup failed: %d\n", __func__, ret);
		वापस;
	पूर्ण

	gpiod_add_lookup_table(&mmc_gpios_table);

	ret = da8xx_रेजिस्टर_mmcsd0(&da850_mmc_config);
	अगर (ret) अणु
		pr_warn("%s: MMC/SD0 registration failed: %d\n", __func__, ret);
		जाओ mmc_setup_mmcsd_fail;
	पूर्ण

	वापस;

mmc_setup_mmcsd_fail:
	gpiod_हटाओ_lookup_table(&mmc_gpios_table);
पूर्ण

अटल काष्ठा mtd_partition omapl138_hawk_nandflash_partition[] = अणु
	अणु
		.name		= "u-boot env",
		.offset		= 0,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	 पूर्ण,
	अणु
		.name		= "u-boot",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_512K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
	अणु
		.name		= "free space",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_aemअगर_timing omapl138_hawk_nandflash_timing = अणु
	.wsetup		= 24,
	.wstrobe	= 21,
	.whold		= 14,
	.rsetup		= 19,
	.rstrobe	= 50,
	.rhold		= 0,
	.ta		= 20,
पूर्ण;

अटल काष्ठा davinci_nand_pdata omapl138_hawk_nandflash_data = अणु
	.core_chipsel	= 1,
	.parts		= omapl138_hawk_nandflash_partition,
	.nr_parts	= ARRAY_SIZE(omapl138_hawk_nandflash_partition),
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST,
	.ecc_bits	= 4,
	.bbt_options	= न_अंकD_BBT_USE_FLASH,
	.options	= न_अंकD_BUSWIDTH_16,
	.timing		= &omapl138_hawk_nandflash_timing,
	.mask_chipsel	= 0,
	.mask_ale	= 0,
	.mask_cle	= 0,
पूर्ण;

अटल काष्ठा resource omapl138_hawk_nandflash_resource[] = अणु
	अणु
		.start	= DA8XX_AEMIF_CS3_BASE,
		.end	= DA8XX_AEMIF_CS3_BASE + SZ_32M,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= DA8XX_AEMIF_CTL_BASE,
		.end	= DA8XX_AEMIF_CTL_BASE + SZ_32K,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource omapl138_hawk_aemअगर_resource[] = अणु
	अणु
		.start	= DA8XX_AEMIF_CTL_BASE,
		.end	= DA8XX_AEMIF_CTL_BASE + SZ_32K,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा aemअगर_abus_data omapl138_hawk_aemअगर_abus_data[] = अणु
	अणु
		.cs	= 3,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device omapl138_hawk_aemअगर_devices[] = अणु
	अणु
		.name		= "davinci_nand",
		.id		= -1,
		.dev		= अणु
			.platक्रमm_data	= &omapl138_hawk_nandflash_data,
		पूर्ण,
		.resource	= omapl138_hawk_nandflash_resource,
		.num_resources	= ARRAY_SIZE(omapl138_hawk_nandflash_resource),
	पूर्ण
पूर्ण;

अटल काष्ठा aemअगर_platक्रमm_data omapl138_hawk_aemअगर_pdata = अणु
	.cs_offset = 2,
	.abus_data = omapl138_hawk_aemअगर_abus_data,
	.num_abus_data = ARRAY_SIZE(omapl138_hawk_aemअगर_abus_data),
	.sub_devices = omapl138_hawk_aemअगर_devices,
	.num_sub_devices = ARRAY_SIZE(omapl138_hawk_aemअगर_devices),
पूर्ण;

अटल काष्ठा platक्रमm_device omapl138_hawk_aemअगर_device = अणु
	.name		= "ti-aemif",
	.id		= -1,
	.dev = अणु
		.platक्रमm_data	= &omapl138_hawk_aemअगर_pdata,
	पूर्ण,
	.resource	= omapl138_hawk_aemअगर_resource,
	.num_resources	= ARRAY_SIZE(omapl138_hawk_aemअगर_resource),
पूर्ण;

अटल स्थिर लघु omapl138_hawk_nand_pins[] = अणु
	DA850_EMA_WAIT_1, DA850_NEMA_OE, DA850_NEMA_WE, DA850_NEMA_CS_3,
	DA850_EMA_D_0, DA850_EMA_D_1, DA850_EMA_D_2, DA850_EMA_D_3,
	DA850_EMA_D_4, DA850_EMA_D_5, DA850_EMA_D_6, DA850_EMA_D_7,
	DA850_EMA_D_8, DA850_EMA_D_9, DA850_EMA_D_10, DA850_EMA_D_11,
	DA850_EMA_D_12, DA850_EMA_D_13, DA850_EMA_D_14, DA850_EMA_D_15,
	DA850_EMA_A_1, DA850_EMA_A_2,
	-1
पूर्ण;

अटल पूर्णांक omapl138_hawk_रेजिस्टर_aemअगर(व्योम)
अणु
	पूर्णांक ret;

	ret = davinci_cfg_reg_list(omapl138_hawk_nand_pins);
	अगर (ret)
		pr_warn("%s: NAND mux setup failed: %d\n", __func__, ret);

	वापस platक्रमm_device_रेजिस्टर(&omapl138_hawk_aemअगर_device);
पूर्ण

अटल स्थिर लघु da850_hawk_usb11_pins[] = अणु
	DA850_GPIO2_4, DA850_GPIO6_13,
	-1
पूर्ण;

अटल काष्ठा regulator_consumer_supply hawk_usb_supplies[] = अणु
	REGULATOR_SUPPLY("vbus", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data hawk_usb_vbus_data = अणु
	.consumer_supplies	= hawk_usb_supplies,
	.num_consumer_supplies	= ARRAY_SIZE(hawk_usb_supplies),
	.स्थिरraपूर्णांकs    = अणु
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	पूर्ण,
पूर्ण;

अटल काष्ठा fixed_voltage_config hawk_usb_vbus = अणु
	.supply_name		= "vbus",
	.microvolts		= 3300000,
	.init_data		= &hawk_usb_vbus_data,
पूर्ण;

अटल काष्ठा platक्रमm_device hawk_usb_vbus_device = अणु
	.name		= "reg-fixed-voltage",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data = &hawk_usb_vbus,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table hawk_usb_oc_gpio_lookup = अणु
	.dev_id		= "ohci-da8xx",
	.table = अणु
		GPIO_LOOKUP("davinci_gpio", DA850_USB1_OC_PIN, "oc", 0),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table hawk_usb_vbus_gpio_lookup = अणु
	.dev_id		= "reg-fixed-voltage.0",
	.table = अणु
		GPIO_LOOKUP("davinci_gpio", DA850_USB1_VBUS_PIN, शून्य, 0),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table *hawk_usb_gpio_lookups[] = अणु
	&hawk_usb_oc_gpio_lookup,
	&hawk_usb_vbus_gpio_lookup,
पूर्ण;

अटल काष्ठा da8xx_ohci_root_hub omapl138_hawk_usb11_pdata = अणु
	/* TPS2087 चयन @ 5V */
	.potpgt         = (3 + 1) / 2,  /* 3 ms max */
पूर्ण;

अटल __init व्योम omapl138_hawk_usb_init(व्योम)
अणु
	पूर्णांक ret;

	ret = davinci_cfg_reg_list(da850_hawk_usb11_pins);
	अगर (ret) अणु
		pr_warn("%s: USB 1.1 PinMux setup failed: %d\n", __func__, ret);
		वापस;
	पूर्ण

	ret = da8xx_रेजिस्टर_usb_phy_घड़ीs();
	अगर (ret)
		pr_warn("%s: USB PHY CLK registration failed: %d\n",
			__func__, ret);

	gpiod_add_lookup_tables(hawk_usb_gpio_lookups,
				ARRAY_SIZE(hawk_usb_gpio_lookups));

	ret = da8xx_रेजिस्टर_usb_phy();
	अगर (ret)
		pr_warn("%s: USB PHY registration failed: %d\n",
			__func__, ret);

	ret = platक्रमm_device_रेजिस्टर(&hawk_usb_vbus_device);
	अगर (ret) अणु
		pr_warn("%s: Unable to register the vbus supply\n", __func__);
		वापस;
	पूर्ण

	ret = da8xx_रेजिस्टर_usb11(&omapl138_hawk_usb11_pdata);
	अगर (ret)
		pr_warn("%s: USB 1.1 registration failed: %d\n", __func__, ret);

	वापस;
पूर्ण

अटल __init व्योम omapl138_hawk_init(व्योम)
अणु
	पूर्णांक ret;

	da850_रेजिस्टर_घड़ीs();

	ret = da850_रेजिस्टर_gpio();
	अगर (ret)
		pr_warn("%s: GPIO init failed: %d\n", __func__, ret);

	davinci_serial_init(da8xx_serial_device);

	omapl138_hawk_config_emac();

	ret = da850_रेजिस्टर_edma(da850_edma_rsv);
	अगर (ret)
		pr_warn("%s: EDMA registration failed: %d\n", __func__, ret);

	omapl138_hawk_mmc_init();

	omapl138_hawk_usb_init();

	ret = omapl138_hawk_रेजिस्टर_aemअगर();
	अगर (ret)
		pr_warn("%s: aemif registration failed: %d\n", __func__, ret);

	ret = da8xx_रेजिस्टर_watchकरोg();
	अगर (ret)
		pr_warn("%s: watchdog registration failed: %d\n",
			__func__, ret);

	ret = da8xx_रेजिस्टर_rproc();
	अगर (ret)
		pr_warn("%s: dsp/rproc registration failed: %d\n",
			__func__, ret);

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
अटल पूर्णांक __init omapl138_hawk_console_init(व्योम)
अणु
	अगर (!machine_is_omapl138_hawkboard())
		वापस 0;

	वापस add_preferred_console("ttyS", 2, "115200");
पूर्ण
console_initcall(omapl138_hawk_console_init);
#पूर्ण_अगर

अटल व्योम __init omapl138_hawk_map_io(व्योम)
अणु
	da850_init();
पूर्ण

MACHINE_START(OMAPL138_HAWKBOARD, "AM18x/OMAP-L138 Hawkboard")
	.atag_offset	= 0x100,
	.map_io		= omapl138_hawk_map_io,
	.init_irq	= da850_init_irq,
	.init_समय	= da850_init_समय,
	.init_machine	= omapl138_hawk_init,
	.init_late	= davinci_init_late,
	.dma_zone_size	= SZ_128M,
	.reserve	= da8xx_rproc_reserve_cma,
MACHINE_END
