<शैली गुरु>
/*
 * Critical Link MityOMAP-L138 SoM
 *
 * Copyright (C) 2010 Critical Link LLC - https://www.criticallink.com
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of
 * any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) "MityOMAPL138: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/i2c.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <mach/common.h>
#समावेश <mach/da8xx.h>
#समावेश <linux/platक्रमm_data/mtd-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci-aemअगर.h>
#समावेश <linux/platक्रमm_data/ti-aemअगर.h>
#समावेश <mach/mux.h>
#समावेश <linux/platक्रमm_data/spi-davinci.h>

#घोषणा MITYOMAPL138_PHY_ID		""

#घोषणा FACTORY_CONFIG_MAGIC	0x012C0138
#घोषणा FACTORY_CONFIG_VERSION	0x00010001

/* Data Held in On-Board I2C device */
काष्ठा factory_config अणु
	u32	magic;
	u32	version;
	u8	mac[6];
	u32	fpga_type;
	u32	spare;
	u32	serialnumber;
	अक्षर	partnum[32];
पूर्ण;

अटल काष्ठा factory_config factory_config;

#अगर_घोषित CONFIG_CPU_FREQ
काष्ठा part_no_info अणु
	स्थिर अक्षर	*part_no;	/* part number string of पूर्णांकerest */
	पूर्णांक		max_freq;	/* khz */
पूर्ण;

अटल काष्ठा part_no_info mityomapl138_pn_info[] = अणु
	अणु
		.part_no	= "L138-C",
		.max_freq	= 300000,
	पूर्ण,
	अणु
		.part_no	= "L138-D",
		.max_freq	= 375000,
	पूर्ण,
	अणु
		.part_no	= "L138-F",
		.max_freq	= 456000,
	पूर्ण,
	अणु
		.part_no	= "1808-C",
		.max_freq	= 300000,
	पूर्ण,
	अणु
		.part_no	= "1808-D",
		.max_freq	= 375000,
	पूर्ण,
	अणु
		.part_no	= "1808-F",
		.max_freq	= 456000,
	पूर्ण,
	अणु
		.part_no	= "1810-D",
		.max_freq	= 375000,
	पूर्ण,
पूर्ण;

अटल व्योम mityomapl138_cpufreq_init(स्थिर अक्षर *partnum)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; partnum && i < ARRAY_SIZE(mityomapl138_pn_info); i++) अणु
		/*
		 * the part number has additional अक्षरacters beyond what is
		 * stored in the table.  This inक्रमmation is not needed क्रम
		 * determining the speed grade, and would require several
		 * more table entries.  Only check the first N अक्षरacters
		 * क्रम a match.
		 */
		अगर (!म_भेदन(partnum, mityomapl138_pn_info[i].part_no,
			     म_माप(mityomapl138_pn_info[i].part_no))) अणु
			da850_max_speed = mityomapl138_pn_info[i].max_freq;
			अवरोध;
		पूर्ण
	पूर्ण

	ret = da850_रेजिस्टर_cpufreq("pll0_sysclk3");
	अगर (ret)
		pr_warn("cpufreq registration failed: %d\n", ret);
पूर्ण
#अन्यथा
अटल व्योम mityomapl138_cpufreq_init(स्थिर अक्षर *partnum) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक पढ़ो_factory_config(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ event, व्योम *data)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *partnum = शून्य;
	काष्ठा nvmem_device *nvmem = data;

	अगर (म_भेद(nvmem_dev_name(nvmem), "1-00500") != 0)
		वापस NOTIFY_DONE;

	अगर (!IS_BUILTIN(CONFIG_NVMEM)) अणु
		pr_warn("Factory Config not available without CONFIG_NVMEM\n");
		जाओ bad_config;
	पूर्ण

	ret = nvmem_device_पढ़ो(nvmem, 0, माप(factory_config),
				&factory_config);
	अगर (ret != माप(काष्ठा factory_config)) अणु
		pr_warn("Read Factory Config Failed: %d\n", ret);
		जाओ bad_config;
	पूर्ण

	अगर (factory_config.magic != FACTORY_CONFIG_MAGIC) अणु
		pr_warn("Factory Config Magic Wrong (%X)\n",
			factory_config.magic);
		जाओ bad_config;
	पूर्ण

	अगर (factory_config.version != FACTORY_CONFIG_VERSION) अणु
		pr_warn("Factory Config Version Wrong (%X)\n",
			factory_config.version);
		जाओ bad_config;
	पूर्ण

	partnum = factory_config.partnum;
	pr_info("Part Number = %s\n", partnum);

bad_config:
	/* शेष maximum speed is valid क्रम all platक्रमms */
	mityomapl138_cpufreq_init(partnum);

	वापस NOTIFY_STOP;
पूर्ण

अटल काष्ठा notअगरier_block mityomapl138_nvmem_notअगरier = अणु
	.notअगरier_call = पढ़ो_factory_config,
पूर्ण;

/*
 * We करोn't define a cell क्रम factory config as it will be accessed from the
 * board file using the nvmem notअगरier chain.
 */
अटल काष्ठा nvmem_cell_info mityomapl138_nvmem_cells[] = अणु
	अणु
		.name		= "macaddr",
		.offset		= 0x64,
		.bytes		= ETH_ALEN,
	पूर्ण
पूर्ण;

अटल काष्ठा nvmem_cell_table mityomapl138_nvmem_cell_table = अणु
	.nvmem_name	= "1-00500",
	.cells		= mityomapl138_nvmem_cells,
	.ncells		= ARRAY_SIZE(mityomapl138_nvmem_cells),
पूर्ण;

अटल काष्ठा nvmem_cell_lookup mityomapl138_nvmem_cell_lookup = अणु
	.nvmem_name	= "1-00500",
	.cell_name	= "macaddr",
	.dev_id		= "davinci_emac.1",
	.con_id		= "mac-address",
पूर्ण;

अटल स्थिर काष्ठा property_entry mityomapl138_fd_chip_properties[] = अणु
	PROPERTY_ENTRY_U32("pagesize", 8),
	PROPERTY_ENTRY_BOOL("read-only"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node mityomapl138_fd_chip_node = अणु
	.properties = mityomapl138_fd_chip_properties,
पूर्ण;

अटल काष्ठा davinci_i2c_platक्रमm_data mityomap_i2c_0_pdata = अणु
	.bus_freq	= 100,	/* kHz */
	.bus_delay	= 0,	/* usec */
पूर्ण;

/* TPS65023 voltage regulator support */
/* 1.2V Core */
अटल काष्ठा regulator_consumer_supply tps65023_dcdc1_consumers[] = अणु
	अणु
		.supply = "cvdd",
	पूर्ण,
पूर्ण;

/* 1.8V */
अटल काष्ठा regulator_consumer_supply tps65023_dcdc2_consumers[] = अणु
	अणु
		.supply = "usb0_vdda18",
	पूर्ण,
	अणु
		.supply = "usb1_vdda18",
	पूर्ण,
	अणु
		.supply = "ddr_dvdd18",
	पूर्ण,
	अणु
		.supply = "sata_vddr",
	पूर्ण,
पूर्ण;

/* 1.2V */
अटल काष्ठा regulator_consumer_supply tps65023_dcdc3_consumers[] = अणु
	अणु
		.supply = "sata_vdd",
	पूर्ण,
	अणु
		.supply = "usb_cvdd",
	पूर्ण,
	अणु
		.supply = "pll0_vdda",
	पूर्ण,
	अणु
		.supply = "pll1_vdda",
	पूर्ण,
पूर्ण;

/* 1.8V Aux LDO, not used */
अटल काष्ठा regulator_consumer_supply tps65023_lकरो1_consumers[] = अणु
	अणु
		.supply = "1.8v_aux",
	पूर्ण,
पूर्ण;

/* FPGA VCC Aux (2.5 or 3.3) LDO */
अटल काष्ठा regulator_consumer_supply tps65023_lकरो2_consumers[] = अणु
	अणु
		.supply = "vccaux",
	पूर्ण,
पूर्ण;

अटल काष्ठा regulator_init_data tps65023_regulator_data[] = अणु
	/* dcdc1 */
	अणु
		.स्थिरraपूर्णांकs = अणु
			.min_uV = 1150000,
			.max_uV = 1350000,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE |
					  REGULATOR_CHANGE_STATUS,
			.boot_on = 1,
		पूर्ण,
		.num_consumer_supplies = ARRAY_SIZE(tps65023_dcdc1_consumers),
		.consumer_supplies = tps65023_dcdc1_consumers,
	पूर्ण,
	/* dcdc2 */
	अणु
		.स्थिरraपूर्णांकs = अणु
			.min_uV = 1800000,
			.max_uV = 1800000,
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
			.boot_on = 1,
		पूर्ण,
		.num_consumer_supplies = ARRAY_SIZE(tps65023_dcdc2_consumers),
		.consumer_supplies = tps65023_dcdc2_consumers,
	पूर्ण,
	/* dcdc3 */
	अणु
		.स्थिरraपूर्णांकs = अणु
			.min_uV = 1200000,
			.max_uV = 1200000,
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
			.boot_on = 1,
		पूर्ण,
		.num_consumer_supplies = ARRAY_SIZE(tps65023_dcdc3_consumers),
		.consumer_supplies = tps65023_dcdc3_consumers,
	पूर्ण,
	/* lकरो1 */
	अणु
		.स्थिरraपूर्णांकs = अणु
			.min_uV = 1800000,
			.max_uV = 1800000,
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
			.boot_on = 1,
		पूर्ण,
		.num_consumer_supplies = ARRAY_SIZE(tps65023_lकरो1_consumers),
		.consumer_supplies = tps65023_lकरो1_consumers,
	पूर्ण,
	/* lकरो2 */
	अणु
		.स्थिरraपूर्णांकs = अणु
			.min_uV = 2500000,
			.max_uV = 3300000,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE |
					  REGULATOR_CHANGE_STATUS,
			.boot_on = 1,
		पूर्ण,
		.num_consumer_supplies = ARRAY_SIZE(tps65023_lकरो2_consumers),
		.consumer_supplies = tps65023_lकरो2_consumers,
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata mityomap_tps65023_info[] = अणु
	अणु
		I2C_BOARD_INFO("tps65023", 0x48),
		.platक्रमm_data = &tps65023_regulator_data[0],
	पूर्ण,
	अणु
		I2C_BOARD_INFO("24c02", 0x50),
		.swnode = &mityomapl138_fd_chip_node,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pmic_tps65023_init(व्योम)
अणु
	वापस i2c_रेजिस्टर_board_info(1, mityomap_tps65023_info,
					ARRAY_SIZE(mityomap_tps65023_info));
पूर्ण

/*
 * SPI Devices:
 *	SPI1_CS0: 8M Flash ST-M25P64-VME6G
 */
अटल काष्ठा mtd_partition spi_flash_partitions[] = अणु
	[0] = अणु
		.name		= "ubl",
		.offset		= 0,
		.size		= SZ_64K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
	[1] = अणु
		.name		= "u-boot",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_512K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
	[2] = अणु
		.name		= "u-boot-env",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_64K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
	[3] = अणु
		.name		= "periph-config",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_64K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
	[4] = अणु
		.name		= "reserved",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_256K + SZ_64K,
	पूर्ण,
	[5] = अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_2M + SZ_1M,
	पूर्ण,
	[6] = अणु
		.name		= "fpga",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_2M,
	पूर्ण,
	[7] = अणु
		.name		= "spare",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data mityomapl138_spi_flash_data = अणु
	.name		= "m25p80",
	.parts		= spi_flash_partitions,
	.nr_parts	= ARRAY_SIZE(spi_flash_partitions),
	.type		= "m24p64",
पूर्ण;

अटल काष्ठा davinci_spi_config spi_eprom_config = अणु
	.io_type	= SPI_IO_TYPE_DMA,
	.c2tdelay	= 8,
	.t2cdelay	= 8,
पूर्ण;

अटल काष्ठा spi_board_info mityomapl138_spi_flash_info[] = अणु
	अणु
		.modalias		= "m25p80",
		.platक्रमm_data		= &mityomapl138_spi_flash_data,
		.controller_data	= &spi_eprom_config,
		.mode			= SPI_MODE_0,
		.max_speed_hz		= 30000000,
		.bus_num		= 1,
		.chip_select		= 0,
	पूर्ण,
पूर्ण;

/*
 * MityDSP-L138 includes a 256 MByte large-page न_अंकD flash
 * (128K blocks).
 */
अटल काष्ठा mtd_partition mityomapl138_nandflash_partition[] = अणु
	अणु
		.name		= "rootfs",
		.offset		= 0,
		.size		= SZ_128M,
		.mask_flags	= 0, /* MTD_WRITEABLE, */
	पूर्ण,
	अणु
		.name		= "homefs",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_nand_pdata mityomapl138_nandflash_data = अणु
	.core_chipsel	= 1,
	.parts		= mityomapl138_nandflash_partition,
	.nr_parts	= ARRAY_SIZE(mityomapl138_nandflash_partition),
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST,
	.bbt_options	= न_अंकD_BBT_USE_FLASH,
	.options	= न_अंकD_BUSWIDTH_16,
	.ecc_bits	= 1, /* 4 bit mode is not supported with 16 bit न_अंकD */
पूर्ण;

अटल काष्ठा resource mityomapl138_nandflash_resource[] = अणु
	अणु
		.start	= DA8XX_AEMIF_CS3_BASE,
		.end	= DA8XX_AEMIF_CS3_BASE + SZ_512K + 2 * SZ_1K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= DA8XX_AEMIF_CTL_BASE,
		.end	= DA8XX_AEMIF_CTL_BASE + SZ_32K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mityomapl138_aemअगर_devices[] = अणु
	अणु
		.name		= "davinci_nand",
		.id		= 1,
		.dev		= अणु
			.platक्रमm_data	= &mityomapl138_nandflash_data,
		पूर्ण,
		.num_resources	= ARRAY_SIZE(mityomapl138_nandflash_resource),
		.resource	= mityomapl138_nandflash_resource,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource mityomapl138_aemअगर_resources[] = अणु
	अणु
		.start	= DA8XX_AEMIF_CTL_BASE,
		.end	= DA8XX_AEMIF_CTL_BASE + SZ_32K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा aemअगर_abus_data mityomapl138_aemअगर_abus_data[] = अणु
	अणु
		.cs	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा aemअगर_platक्रमm_data mityomapl138_aemअगर_pdata = अणु
	.abus_data		= mityomapl138_aemअगर_abus_data,
	.num_abus_data		= ARRAY_SIZE(mityomapl138_aemअगर_abus_data),
	.sub_devices		= mityomapl138_aemअगर_devices,
	.num_sub_devices	= ARRAY_SIZE(mityomapl138_aemअगर_devices),
पूर्ण;

अटल काष्ठा platक्रमm_device mityomapl138_aemअगर_device = अणु
	.name		= "ti-aemif",
	.id		= -1,
	.dev = अणु
		.platक्रमm_data	= &mityomapl138_aemअगर_pdata,
	पूर्ण,
	.resource	= mityomapl138_aemअगर_resources,
	.num_resources	= ARRAY_SIZE(mityomapl138_aemअगर_resources),
पूर्ण;

अटल व्योम __init mityomapl138_setup_nand(व्योम)
अणु
	अगर (platक्रमm_device_रेजिस्टर(&mityomapl138_aemअगर_device))
		pr_warn("%s: Cannot register AEMIF device\n", __func__);
पूर्ण

अटल स्थिर लघु mityomap_mii_pins[] = अणु
	DA850_MII_TXEN, DA850_MII_TXCLK, DA850_MII_COL, DA850_MII_TXD_3,
	DA850_MII_TXD_2, DA850_MII_TXD_1, DA850_MII_TXD_0, DA850_MII_RXER,
	DA850_MII_CRS, DA850_MII_RXCLK, DA850_MII_RXDV, DA850_MII_RXD_3,
	DA850_MII_RXD_2, DA850_MII_RXD_1, DA850_MII_RXD_0, DA850_MDIO_CLK,
	DA850_MDIO_D,
	-1
पूर्ण;

अटल स्थिर लघु mityomap_rmii_pins[] = अणु
	DA850_RMII_TXD_0, DA850_RMII_TXD_1, DA850_RMII_TXEN,
	DA850_RMII_CRS_DV, DA850_RMII_RXD_0, DA850_RMII_RXD_1,
	DA850_RMII_RXER, DA850_RMII_MHZ_50_CLK, DA850_MDIO_CLK,
	DA850_MDIO_D,
	-1
पूर्ण;

अटल व्योम __init mityomapl138_config_emac(व्योम)
अणु
	व्योम __iomem *cfg_chip3_base;
	पूर्णांक ret;
	u32 val;
	काष्ठा davinci_soc_info *soc_info = &davinci_soc_info;

	soc_info->emac_pdata->rmii_en = 0; /* hardcoded क्रम now */

	cfg_chip3_base = DA8XX_SYSCFG0_VIRT(DA8XX_CFGCHIP3_REG);
	val = __raw_पढ़ोl(cfg_chip3_base);

	अगर (soc_info->emac_pdata->rmii_en) अणु
		val |= BIT(8);
		ret = davinci_cfg_reg_list(mityomap_rmii_pins);
		pr_info("RMII PHY configured\n");
	पूर्ण अन्यथा अणु
		val &= ~BIT(8);
		ret = davinci_cfg_reg_list(mityomap_mii_pins);
		pr_info("MII PHY configured\n");
	पूर्ण

	अगर (ret) अणु
		pr_warn("mii/rmii mux setup failed: %d\n", ret);
		वापस;
	पूर्ण

	/* configure the CFGCHIP3 रेजिस्टर क्रम RMII or MII */
	__raw_ग_लिखोl(val, cfg_chip3_base);

	soc_info->emac_pdata->phy_id = MITYOMAPL138_PHY_ID;

	ret = da8xx_रेजिस्टर_emac();
	अगर (ret)
		pr_warn("emac registration failed: %d\n", ret);
पूर्ण

अटल व्योम __init mityomapl138_init(व्योम)
अणु
	पूर्णांक ret;

	da850_रेजिस्टर_घड़ीs();

	/* क्रम now, no special EDMA channels are reserved */
	ret = da850_रेजिस्टर_edma(शून्य);
	अगर (ret)
		pr_warn("edma registration failed: %d\n", ret);

	ret = da8xx_रेजिस्टर_watchकरोg();
	अगर (ret)
		pr_warn("watchdog registration failed: %d\n", ret);

	davinci_serial_init(da8xx_serial_device);

	nvmem_रेजिस्टर_notअगरier(&mityomapl138_nvmem_notअगरier);
	nvmem_add_cell_table(&mityomapl138_nvmem_cell_table);
	nvmem_add_cell_lookups(&mityomapl138_nvmem_cell_lookup, 1);

	ret = da8xx_रेजिस्टर_i2c(0, &mityomap_i2c_0_pdata);
	अगर (ret)
		pr_warn("i2c0 registration failed: %d\n", ret);

	ret = pmic_tps65023_init();
	अगर (ret)
		pr_warn("TPS65023 PMIC init failed: %d\n", ret);

	mityomapl138_setup_nand();

	ret = spi_रेजिस्टर_board_info(mityomapl138_spi_flash_info,
				      ARRAY_SIZE(mityomapl138_spi_flash_info));
	अगर (ret)
		pr_warn("spi info registration failed: %d\n", ret);

	ret = da8xx_रेजिस्टर_spi_bus(1,
				     ARRAY_SIZE(mityomapl138_spi_flash_info));
	अगर (ret)
		pr_warn("spi 1 registration failed: %d\n", ret);

	mityomapl138_config_emac();

	ret = da8xx_रेजिस्टर_rtc();
	अगर (ret)
		pr_warn("rtc setup failed: %d\n", ret);

	ret = da8xx_रेजिस्टर_cpuidle();
	अगर (ret)
		pr_warn("cpuidle registration failed: %d\n", ret);

	davinci_pm_init();
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
अटल पूर्णांक __init mityomapl138_console_init(व्योम)
अणु
	अगर (!machine_is_mityomapl138())
		वापस 0;

	वापस add_preferred_console("ttyS", 1, "115200");
पूर्ण
console_initcall(mityomapl138_console_init);
#पूर्ण_अगर

अटल व्योम __init mityomapl138_map_io(व्योम)
अणु
	da850_init();
पूर्ण

MACHINE_START(MITYOMAPL138, "MityDSP-L138/MityARM-1808")
	.atag_offset	= 0x100,
	.map_io		= mityomapl138_map_io,
	.init_irq	= da850_init_irq,
	.init_समय	= da850_init_समय,
	.init_machine	= mityomapl138_init,
	.init_late	= davinci_init_late,
	.dma_zone_size	= SZ_128M,
MACHINE_END
