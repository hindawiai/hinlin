<शैली गुरु>
/*
 * TI DA830/OMAP L137 EVM board
 *
 * Author: Mark A. Greer <mgreer@mvista.com>
 * Derived from: arch/arm/mach-davinci/board-dm644x-evm.c
 *
 * 2007, 2009 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/pcf857x.h>
#समावेश <linux/property.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/platक्रमm_data/gpio-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci-aemअगर.h>
#समावेश <linux/platक्रमm_data/spi-davinci.h>
#समावेश <linux/platक्रमm_data/usb-davinci.h>
#समावेश <linux/platक्रमm_data/ti-aemअगर.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/nvmem-provider.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश <mach/common.h>
#समावेश <mach/mux.h>
#समावेश <mach/da8xx.h>

#समावेश "irqs.h"

#घोषणा DA830_EVM_PHY_ID		""
/*
 * USB1 VBUS is controlled by GPIO1[15], over-current is reported on GPIO2[4].
 */
#घोषणा ON_BD_USB_DRV	GPIO_TO_PIN(1, 15)
#घोषणा ON_BD_USB_OVC	GPIO_TO_PIN(2, 4)

अटल स्थिर लघु da830_evm_usb11_pins[] = अणु
	DA830_GPIO1_15, DA830_GPIO2_4,
	-1
पूर्ण;

अटल काष्ठा regulator_consumer_supply da830_evm_usb_supplies[] = अणु
	REGULATOR_SUPPLY("vbus", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data da830_evm_usb_vbus_data = अणु
	.consumer_supplies	= da830_evm_usb_supplies,
	.num_consumer_supplies	= ARRAY_SIZE(da830_evm_usb_supplies),
	.स्थिरraपूर्णांकs    = अणु
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	पूर्ण,
पूर्ण;

अटल काष्ठा fixed_voltage_config da830_evm_usb_vbus = अणु
	.supply_name		= "vbus",
	.microvolts		= 33000000,
	.init_data		= &da830_evm_usb_vbus_data,
पूर्ण;

अटल काष्ठा platक्रमm_device da830_evm_usb_vbus_device = अणु
	.name		= "reg-fixed-voltage",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data = &da830_evm_usb_vbus,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table da830_evm_usb_oc_gpio_lookup = अणु
	.dev_id		= "ohci-da8xx",
	.table = अणु
		GPIO_LOOKUP("davinci_gpio", ON_BD_USB_OVC, "oc", 0),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table da830_evm_usb_vbus_gpio_lookup = अणु
	.dev_id		= "reg-fixed-voltage.0",
	.table = अणु
		GPIO_LOOKUP("davinci_gpio", ON_BD_USB_DRV, शून्य, 0),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table *da830_evm_usb_gpio_lookups[] = अणु
	&da830_evm_usb_oc_gpio_lookup,
	&da830_evm_usb_vbus_gpio_lookup,
पूर्ण;

अटल काष्ठा da8xx_ohci_root_hub da830_evm_usb11_pdata = अणु
	/* TPS2065 चयन @ 5V */
	.potpgt		= (3 + 1) / 2,	/* 3 ms max */
पूर्ण;

अटल __init व्योम da830_evm_usb_init(व्योम)
अणु
	पूर्णांक ret;

	ret = da8xx_रेजिस्टर_usb_phy_घड़ीs();
	अगर (ret)
		pr_warn("%s: USB PHY CLK registration failed: %d\n",
			__func__, ret);

	gpiod_add_lookup_tables(da830_evm_usb_gpio_lookups,
				ARRAY_SIZE(da830_evm_usb_gpio_lookups));

	ret = da8xx_रेजिस्टर_usb_phy();
	अगर (ret)
		pr_warn("%s: USB PHY registration failed: %d\n",
			__func__, ret);

	ret = davinci_cfg_reg(DA830_USB0_DRVVBUS);
	अगर (ret)
		pr_warn("%s: USB 2.0 PinMux setup failed: %d\n", __func__, ret);
	अन्यथा अणु
		/*
		 * TPS2065 चयन @ 5V supplies 1 A (sustains 1.5 A),
		 * with the घातer on to घातer good समय of 3 ms.
		 */
		ret = da8xx_रेजिस्टर_usb20(1000, 3);
		अगर (ret)
			pr_warn("%s: USB 2.0 registration failed: %d\n",
				__func__, ret);
	पूर्ण

	ret = davinci_cfg_reg_list(da830_evm_usb11_pins);
	अगर (ret) अणु
		pr_warn("%s: USB 1.1 PinMux setup failed: %d\n", __func__, ret);
		वापस;
	पूर्ण

	ret = platक्रमm_device_रेजिस्टर(&da830_evm_usb_vbus_device);
	अगर (ret) अणु
		pr_warn("%s: Unable to register the vbus supply\n", __func__);
		वापस;
	पूर्ण

	ret = da8xx_रेजिस्टर_usb11(&da830_evm_usb11_pdata);
	अगर (ret)
		pr_warn("%s: USB 1.1 registration failed: %d\n", __func__, ret);
पूर्ण

अटल स्थिर लघु da830_evm_mcasp1_pins[] = अणु
	DA830_AHCLKX1, DA830_ACLKX1, DA830_AFSX1, DA830_AHCLKR1, DA830_AFSR1,
	DA830_AMUTE1, DA830_AXR1_0, DA830_AXR1_1, DA830_AXR1_2, DA830_AXR1_5,
	DA830_ACLKR1, DA830_AXR1_6, DA830_AXR1_7, DA830_AXR1_8, DA830_AXR1_10,
	DA830_AXR1_11,
	-1
पूर्ण;

अटल u8 da830_iis_serializer_direction[] = अणु
	RX_MODE,	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,
	INACTIVE_MODE,	TX_MODE,	INACTIVE_MODE,	INACTIVE_MODE,
	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,
पूर्ण;

अटल काष्ठा snd_platक्रमm_data da830_evm_snd_data = अणु
	.tx_dma_offset  = 0x2000,
	.rx_dma_offset  = 0x2000,
	.op_mode        = DAVINCI_MCASP_IIS_MODE,
	.num_serializer = ARRAY_SIZE(da830_iis_serializer_direction),
	.tdm_slots      = 2,
	.serial_dir     = da830_iis_serializer_direction,
	.asp_chan_q     = EVENTQ_0,
	.version	= MCASP_VERSION_2,
	.txnumevt	= 1,
	.rxnumevt	= 1,
पूर्ण;

/*
 * GPIO2[1] is used as MMC_SD_WP and GPIO2[2] as MMC_SD_INS.
 */
अटल स्थिर लघु da830_evm_mmc_sd_pins[] = अणु
	DA830_MMCSD_DAT_0, DA830_MMCSD_DAT_1, DA830_MMCSD_DAT_2,
	DA830_MMCSD_DAT_3, DA830_MMCSD_DAT_4, DA830_MMCSD_DAT_5,
	DA830_MMCSD_DAT_6, DA830_MMCSD_DAT_7, DA830_MMCSD_CLK,
	DA830_MMCSD_CMD,   DA830_GPIO2_1,     DA830_GPIO2_2,
	-1
पूर्ण;

#घोषणा DA830_MMCSD_WP_PIN		GPIO_TO_PIN(2, 1)
#घोषणा DA830_MMCSD_CD_PIN		GPIO_TO_PIN(2, 2)

अटल काष्ठा gpiod_lookup_table mmc_gpios_table = अणु
	.dev_id = "da830-mmc.0",
	.table = अणु
		/* gpio chip 1 contains gpio range 32-63 */
		GPIO_LOOKUP("davinci_gpio", DA830_MMCSD_CD_PIN, "cd",
			    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("davinci_gpio", DA830_MMCSD_WP_PIN, "wp",
			    GPIO_ACTIVE_LOW),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_mmc_config da830_evm_mmc_config = अणु
	.wires			= 8,
	.max_freq		= 50000000,
	.caps			= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED,
पूर्ण;

अटल अंतरभूत व्योम da830_evm_init_mmc(व्योम)
अणु
	पूर्णांक ret;

	ret = davinci_cfg_reg_list(da830_evm_mmc_sd_pins);
	अगर (ret) अणु
		pr_warn("%s: mmc/sd mux setup failed: %d\n", __func__, ret);
		वापस;
	पूर्ण

	gpiod_add_lookup_table(&mmc_gpios_table);

	ret = da8xx_रेजिस्टर_mmcsd0(&da830_evm_mmc_config);
	अगर (ret) अणु
		pr_warn("%s: mmc/sd registration failed: %d\n", __func__, ret);
		gpiod_हटाओ_lookup_table(&mmc_gpios_table);
	पूर्ण
पूर्ण

#घोषणा HAS_MMC		IS_ENABLED(CONFIG_MMC_DAVINCI)

#अगर_घोषित CONFIG_DA830_UI_न_अंकD
अटल काष्ठा mtd_partition da830_evm_nand_partitions[] = अणु
	/* bootloader (U-Boot, etc) in first sector */
	[0] = अणु
		.name		= "bootloader",
		.offset		= 0,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,	/* क्रमce पढ़ो-only */
	पूर्ण,
	/* bootloader params in the next sector */
	[1] = अणु
		.name		= "params",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,	/* क्रमce पढ़ो-only */
	पूर्ण,
	/* kernel */
	[2] = अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_2M,
		.mask_flags	= 0,
	पूर्ण,
	/* file प्रणाली */
	[3] = अणु
		.name		= "filesystem",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0,
	पूर्ण
पूर्ण;

/* flash bbt descriptors */
अटल uपूर्णांक8_t da830_evm_nand_bbt_pattern[] = अणु 'B', 'b', 't', '0' पूर्ण;
अटल uपूर्णांक8_t da830_evm_nand_mirror_pattern[] = अणु '1', 't', 'b', 'B' पूर्ण;

अटल काष्ठा nand_bbt_descr da830_evm_nand_bbt_मुख्य_descr = अणु
	.options	= न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE |
			  न_अंकD_BBT_WRITE | न_अंकD_BBT_2BIT |
			  न_अंकD_BBT_VERSION | न_अंकD_BBT_PERCHIP,
	.offs		= 2,
	.len		= 4,
	.veroffs	= 16,
	.maxblocks	= 4,
	.pattern	= da830_evm_nand_bbt_pattern
पूर्ण;

अटल काष्ठा nand_bbt_descr da830_evm_nand_bbt_mirror_descr = अणु
	.options	= न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE |
			  न_अंकD_BBT_WRITE | न_अंकD_BBT_2BIT |
			  न_अंकD_BBT_VERSION | न_अंकD_BBT_PERCHIP,
	.offs		= 2,
	.len		= 4,
	.veroffs	= 16,
	.maxblocks	= 4,
	.pattern	= da830_evm_nand_mirror_pattern
पूर्ण;

अटल काष्ठा davinci_aemअगर_timing da830_evm_nandflash_timing = अणु
	.wsetup         = 24,
	.wstrobe        = 21,
	.whold          = 14,
	.rsetup         = 19,
	.rstrobe        = 50,
	.rhold          = 0,
	.ta             = 20,
पूर्ण;

अटल काष्ठा davinci_nand_pdata da830_evm_nand_pdata = अणु
	.core_chipsel	= 1,
	.parts		= da830_evm_nand_partitions,
	.nr_parts	= ARRAY_SIZE(da830_evm_nand_partitions),
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST,
	.ecc_bits	= 4,
	.bbt_options	= न_अंकD_BBT_USE_FLASH,
	.bbt_td		= &da830_evm_nand_bbt_मुख्य_descr,
	.bbt_md		= &da830_evm_nand_bbt_mirror_descr,
	.timing         = &da830_evm_nandflash_timing,
पूर्ण;

अटल काष्ठा resource da830_evm_nand_resources[] = अणु
	[0] = अणु		/* First memory resource is न_अंकD I/O winकरोw */
		.start	= DA8XX_AEMIF_CS3_BASE,
		.end	= DA8XX_AEMIF_CS3_BASE + PAGE_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु		/* Second memory resource is AEMIF control रेजिस्टरs */
		.start	= DA8XX_AEMIF_CTL_BASE,
		.end	= DA8XX_AEMIF_CTL_BASE + SZ_32K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da830_evm_aemअगर_devices[] = अणु
	अणु
		.name		= "davinci_nand",
		.id		= 1,
		.dev		= अणु
			.platक्रमm_data	= &da830_evm_nand_pdata,
		पूर्ण,
		.num_resources	= ARRAY_SIZE(da830_evm_nand_resources),
		.resource	= da830_evm_nand_resources,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource da830_evm_aemअगर_resource[] = अणु
	अणु
		.start	= DA8XX_AEMIF_CTL_BASE,
		.end	= DA8XX_AEMIF_CTL_BASE + SZ_32K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा aemअगर_abus_data da830_evm_aemअगर_abus_data[] = अणु
	अणु
		.cs	= 3,
	पूर्ण,
पूर्ण;

अटल काष्ठा aemअगर_platक्रमm_data da830_evm_aemअगर_pdata = अणु
	.abus_data		= da830_evm_aemअगर_abus_data,
	.num_abus_data		= ARRAY_SIZE(da830_evm_aemअगर_abus_data),
	.sub_devices		= da830_evm_aemअगर_devices,
	.num_sub_devices	= ARRAY_SIZE(da830_evm_aemअगर_devices),
	.cs_offset		= 2,
पूर्ण;

अटल काष्ठा platक्रमm_device da830_evm_aemअगर_device = अणु
	.name		= "ti-aemif",
	.id		= -1,
	.dev = अणु
		.platक्रमm_data = &da830_evm_aemअगर_pdata,
	पूर्ण,
	.resource	= da830_evm_aemअगर_resource,
	.num_resources	= ARRAY_SIZE(da830_evm_aemअगर_resource),
पूर्ण;

/*
 * UI board न_अंकD/NOR flashes only use 8-bit data bus.
 */
अटल स्थिर लघु da830_evm_emअगर25_pins[] = अणु
	DA830_EMA_D_0, DA830_EMA_D_1, DA830_EMA_D_2, DA830_EMA_D_3,
	DA830_EMA_D_4, DA830_EMA_D_5, DA830_EMA_D_6, DA830_EMA_D_7,
	DA830_EMA_A_0, DA830_EMA_A_1, DA830_EMA_A_2, DA830_EMA_A_3,
	DA830_EMA_A_4, DA830_EMA_A_5, DA830_EMA_A_6, DA830_EMA_A_7,
	DA830_EMA_A_8, DA830_EMA_A_9, DA830_EMA_A_10, DA830_EMA_A_11,
	DA830_EMA_A_12, DA830_EMA_BA_0, DA830_EMA_BA_1, DA830_NEMA_WE,
	DA830_NEMA_CS_2, DA830_NEMA_CS_3, DA830_NEMA_OE, DA830_EMA_WAIT_0,
	-1
पूर्ण;

अटल अंतरभूत व्योम da830_evm_init_nand(पूर्णांक mux_mode)
अणु
	पूर्णांक ret;

	अगर (HAS_MMC) अणु
		pr_warn("WARNING: both MMC/SD and NAND are enabled, but they share AEMIF pins\n"
			"\tDisable MMC/SD for NAND support\n");
		वापस;
	पूर्ण

	ret = davinci_cfg_reg_list(da830_evm_emअगर25_pins);
	अगर (ret)
		pr_warn("%s: emif25 mux setup failed: %d\n", __func__, ret);

	ret = platक्रमm_device_रेजिस्टर(&da830_evm_aemअगर_device);
	अगर (ret)
		pr_warn("%s: AEMIF device not registered\n", __func__);

	gpio_direction_output(mux_mode, 1);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम da830_evm_init_nand(पूर्णांक mux_mode) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DA830_UI_LCD
अटल अंतरभूत व्योम da830_evm_init_lcdc(पूर्णांक mux_mode)
अणु
	पूर्णांक ret;

	ret = davinci_cfg_reg_list(da830_lcdcntl_pins);
	अगर (ret)
		pr_warn("%s: lcdcntl mux setup failed: %d\n", __func__, ret);

	ret = da8xx_रेजिस्टर_lcdc(&sharp_lcd035q3dg01_pdata);
	अगर (ret)
		pr_warn("%s: lcd setup failed: %d\n", __func__, ret);

	gpio_direction_output(mux_mode, 0);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम da830_evm_init_lcdc(पूर्णांक mux_mode) अणु पूर्ण
#पूर्ण_अगर

अटल काष्ठा nvmem_cell_info da830_evm_nvmem_cells[] = अणु
	अणु
		.name		= "macaddr",
		.offset		= 0x7f00,
		.bytes		= ETH_ALEN,
	पूर्ण
पूर्ण;

अटल काष्ठा nvmem_cell_table da830_evm_nvmem_cell_table = अणु
	.nvmem_name	= "1-00500",
	.cells		= da830_evm_nvmem_cells,
	.ncells		= ARRAY_SIZE(da830_evm_nvmem_cells),
पूर्ण;

अटल काष्ठा nvmem_cell_lookup da830_evm_nvmem_cell_lookup = अणु
	.nvmem_name	= "1-00500",
	.cell_name	= "macaddr",
	.dev_id		= "davinci_emac.1",
	.con_id		= "mac-address",
पूर्ण;

अटल स्थिर काष्ठा property_entry da830_evm_i2c_eeprom_properties[] = अणु
	PROPERTY_ENTRY_U32("pagesize", 64),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node da830_evm_i2c_eeprom_node = अणु
	.properties = da830_evm_i2c_eeprom_properties,
पूर्ण;

अटल पूर्णांक __init da830_evm_ui_expander_setup(काष्ठा i2c_client *client,
		पूर्णांक gpio, अचिन्हित ngpio, व्योम *context)
अणु
	gpio_request(gpio + 6, "UI MUX_MODE");

	/* Drive mux mode low to match the शेष without UI card */
	gpio_direction_output(gpio + 6, 0);

	da830_evm_init_lcdc(gpio + 6);

	da830_evm_init_nand(gpio + 6);

	वापस 0;
पूर्ण

अटल पूर्णांक da830_evm_ui_expander_tearकरोwn(काष्ठा i2c_client *client, पूर्णांक gpio,
		अचिन्हित ngpio, व्योम *context)
अणु
	gpio_मुक्त(gpio + 6);
	वापस 0;
पूर्ण

अटल काष्ठा pcf857x_platक्रमm_data __initdata da830_evm_ui_expander_info = अणु
	.gpio_base	= DAVINCI_N_GPIO,
	.setup		= da830_evm_ui_expander_setup,
	.tearकरोwn	= da830_evm_ui_expander_tearकरोwn,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata da830_evm_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("24c256", 0x50),
		.swnode = &da830_evm_i2c_eeprom_node,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("tlv320aic3x", 0x18),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("pcf8574", 0x3f),
		.platक्रमm_data	= &da830_evm_ui_expander_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_i2c_platक्रमm_data da830_evm_i2c_0_pdata = अणु
	.bus_freq	= 100,	/* kHz */
	.bus_delay	= 0,	/* usec */
पूर्ण;

/*
 * The following EDMA channels/slots are not being used by drivers (क्रम
 * example: Timer, GPIO, UART events etc) on da830/omap-l137 EVM, hence
 * they are being reserved क्रम codecs on the DSP side.
 */
अटल स्थिर s16 da830_dma_rsv_chans[][2] = अणु
	/* (offset, number) */
	अणु 8,  2पूर्ण,
	अणु12,  2पूर्ण,
	अणु24,  4पूर्ण,
	अणु30,  2पूर्ण,
	अणु-1, -1पूर्ण
पूर्ण;

अटल स्थिर s16 da830_dma_rsv_slots[][2] = अणु
	/* (offset, number) */
	अणु 8,  2पूर्ण,
	अणु12,  2पूर्ण,
	अणु24,  4पूर्ण,
	अणु30, 26पूर्ण,
	अणु-1, -1पूर्ण
पूर्ण;

अटल काष्ठा edma_rsv_info da830_edma_rsv[] = अणु
	अणु
		.rsv_chans	= da830_dma_rsv_chans,
		.rsv_slots	= da830_dma_rsv_slots,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition da830evm_spअगरlash_part[] = अणु
	[0] = अणु
		.name = "DSP-UBL",
		.offset = 0,
		.size = SZ_8K,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	[1] = अणु
		.name = "ARM-UBL",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_16K + SZ_8K,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	[2] = अणु
		.name = "U-Boot",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_256K - SZ_32K,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	[3] = अणु
		.name = "U-Boot-Environment",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_16K,
		.mask_flags = 0,
	पूर्ण,
	[4] = अणु
		.name = "Kernel",
		.offset = MTDPART_OFS_APPEND,
		.size = MTDPART_SIZ_FULL,
		.mask_flags = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data da830evm_spअगरlash_data = अणु
	.name		= "m25p80",
	.parts		= da830evm_spअगरlash_part,
	.nr_parts	= ARRAY_SIZE(da830evm_spअगरlash_part),
	.type		= "w25x32",
पूर्ण;

अटल काष्ठा davinci_spi_config da830evm_spअगरlash_cfg = अणु
	.io_type	= SPI_IO_TYPE_DMA,
	.c2tdelay	= 8,
	.t2cdelay	= 8,
पूर्ण;

अटल काष्ठा spi_board_info da830evm_spi_info[] = अणु
	अणु
		.modalias		= "m25p80",
		.platक्रमm_data		= &da830evm_spअगरlash_data,
		.controller_data	= &da830evm_spअगरlash_cfg,
		.mode			= SPI_MODE_0,
		.max_speed_hz		= 30000000,
		.bus_num		= 0,
		.chip_select		= 0,
	पूर्ण,
पूर्ण;

अटल __init व्योम da830_evm_init(व्योम)
अणु
	काष्ठा davinci_soc_info *soc_info = &davinci_soc_info;
	पूर्णांक ret;

	da830_रेजिस्टर_घड़ीs();

	ret = da830_रेजिस्टर_gpio();
	अगर (ret)
		pr_warn("%s: GPIO init failed: %d\n", __func__, ret);

	ret = da830_रेजिस्टर_edma(da830_edma_rsv);
	अगर (ret)
		pr_warn("%s: edma registration failed: %d\n", __func__, ret);

	ret = davinci_cfg_reg_list(da830_i2c0_pins);
	अगर (ret)
		pr_warn("%s: i2c0 mux setup failed: %d\n", __func__, ret);

	ret = da8xx_रेजिस्टर_i2c(0, &da830_evm_i2c_0_pdata);
	अगर (ret)
		pr_warn("%s: i2c0 registration failed: %d\n", __func__, ret);

	da830_evm_usb_init();

	soc_info->emac_pdata->rmii_en = 1;
	soc_info->emac_pdata->phy_id = DA830_EVM_PHY_ID;

	ret = davinci_cfg_reg_list(da830_cpgmac_pins);
	अगर (ret)
		pr_warn("%s: cpgmac mux setup failed: %d\n", __func__, ret);

	ret = da8xx_रेजिस्टर_emac();
	अगर (ret)
		pr_warn("%s: emac registration failed: %d\n", __func__, ret);

	ret = da8xx_रेजिस्टर_watchकरोg();
	अगर (ret)
		pr_warn("%s: watchdog registration failed: %d\n",
			__func__, ret);

	davinci_serial_init(da8xx_serial_device);

	nvmem_add_cell_table(&da830_evm_nvmem_cell_table);
	nvmem_add_cell_lookups(&da830_evm_nvmem_cell_lookup, 1);

	i2c_रेजिस्टर_board_info(1, da830_evm_i2c_devices,
			ARRAY_SIZE(da830_evm_i2c_devices));

	ret = davinci_cfg_reg_list(da830_evm_mcasp1_pins);
	अगर (ret)
		pr_warn("%s: mcasp1 mux setup failed: %d\n", __func__, ret);

	da8xx_रेजिस्टर_mcasp(1, &da830_evm_snd_data);

	da830_evm_init_mmc();

	ret = da8xx_रेजिस्टर_rtc();
	अगर (ret)
		pr_warn("%s: rtc setup failed: %d\n", __func__, ret);

	ret = spi_रेजिस्टर_board_info(da830evm_spi_info,
				      ARRAY_SIZE(da830evm_spi_info));
	अगर (ret)
		pr_warn("%s: spi info registration failed: %d\n",
			__func__, ret);

	ret = da8xx_रेजिस्टर_spi_bus(0, ARRAY_SIZE(da830evm_spi_info));
	अगर (ret)
		pr_warn("%s: spi 0 registration failed: %d\n", __func__, ret);

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
अटल पूर्णांक __init da830_evm_console_init(व्योम)
अणु
	अगर (!machine_is_davinci_da830_evm())
		वापस 0;

	वापस add_preferred_console("ttyS", 2, "115200");
पूर्ण
console_initcall(da830_evm_console_init);
#पूर्ण_अगर

अटल व्योम __init da830_evm_map_io(व्योम)
अणु
	da830_init();
पूर्ण

MACHINE_START(DAVINCI_DA830_EVM, "DaVinci DA830/OMAP-L137/AM17x EVM")
	.atag_offset	= 0x100,
	.map_io		= da830_evm_map_io,
	.init_irq	= da830_init_irq,
	.init_समय	= da830_init_समय,
	.init_machine	= da830_evm_init,
	.init_late	= davinci_init_late,
	.dma_zone_size	= SZ_128M,
MACHINE_END
