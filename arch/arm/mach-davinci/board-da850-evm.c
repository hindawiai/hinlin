<शैली गुरु>
/*
 * TI DA850/OMAP-L138 EVM board
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Derived from: arch/arm/mach-davinci/board-da830-evm.c
 * Original Copyrights follow:
 *
 * 2007, 2009 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/pca953x.h>
#समावेश <linux/input.h>
#समावेश <linux/input/tps6507x-ts.h>
#समावेश <linux/mfd/tps6507x.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/gpio-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci-aemअगर.h>
#समावेश <linux/platक्रमm_data/ti-aemअगर.h>
#समावेश <linux/platक्रमm_data/spi-davinci.h>
#समावेश <linux/platक्रमm_data/uio_pruss.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/tps6507x.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>

#समावेश <mach/common.h>
#समावेश <mach/da8xx.h>
#समावेश <mach/mux.h>

#समावेश "irqs.h"
#समावेश "sram.h"

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/प्रणाली_info.h>

#समावेश <media/i2c/tvp514x.h>
#समावेश <media/i2c/adv7343.h>

#घोषणा DA850_EVM_PHY_ID		"davinci_mdio-0:00"
#घोषणा DA850_LCD_PWR_PIN		GPIO_TO_PIN(2, 8)
#घोषणा DA850_LCD_BL_PIN		GPIO_TO_PIN(2, 15)

#घोषणा DA850_MII_MDIO_CLKEN_PIN	GPIO_TO_PIN(2, 6)

अटल काष्ठा mtd_partition da850evm_spअगरlash_part[] = अणु
	[0] = अणु
		.name = "UBL",
		.offset = 0,
		.size = SZ_64K,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	[1] = अणु
		.name = "U-Boot",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_512K,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	[2] = अणु
		.name = "U-Boot-Env",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_64K,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	[3] = अणु
		.name = "Kernel",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_2M + SZ_512K,
		.mask_flags = 0,
	पूर्ण,
	[4] = अणु
		.name = "Filesystem",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_4M,
		.mask_flags = 0,
	पूर्ण,
	[5] = अणु
		.name = "MAC-Address",
		.offset = SZ_8M - SZ_64K,
		.size = SZ_64K,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
पूर्ण;

अटल काष्ठा nvmem_cell_info da850evm_nvmem_cells[] = अणु
	अणु
		.name		= "macaddr",
		.offset		= 0x0,
		.bytes		= ETH_ALEN,
	पूर्ण
पूर्ण;

अटल काष्ठा nvmem_cell_table da850evm_nvmem_cell_table = अणु
	/*
	 * The nvmem name dअगरfers from the partition name because of the
	 * पूर्णांकernal works of the nvmem framework.
	 */
	.nvmem_name	= "MAC-Address0",
	.cells		= da850evm_nvmem_cells,
	.ncells		= ARRAY_SIZE(da850evm_nvmem_cells),
पूर्ण;

अटल काष्ठा nvmem_cell_lookup da850evm_nvmem_cell_lookup = अणु
	.nvmem_name	= "MAC-Address0",
	.cell_name	= "macaddr",
	.dev_id		= "davinci_emac.1",
	.con_id		= "mac-address",
पूर्ण;

अटल काष्ठा flash_platक्रमm_data da850evm_spअगरlash_data = अणु
	.name		= "m25p80",
	.parts		= da850evm_spअगरlash_part,
	.nr_parts	= ARRAY_SIZE(da850evm_spअगरlash_part),
	.type		= "m25p64",
पूर्ण;

अटल काष्ठा davinci_spi_config da850evm_spअगरlash_cfg = अणु
	.io_type	= SPI_IO_TYPE_DMA,
	.c2tdelay	= 8,
	.t2cdelay	= 8,
पूर्ण;

अटल काष्ठा spi_board_info da850evm_spi_info[] = अणु
	अणु
		.modalias		= "m25p80",
		.platक्रमm_data		= &da850evm_spअगरlash_data,
		.controller_data	= &da850evm_spअगरlash_cfg,
		.mode			= SPI_MODE_0,
		.max_speed_hz		= 30000000,
		.bus_num		= 1,
		.chip_select		= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition da850_evm_norflash_partition[] = अणु
	अणु
		.name           = "bootloaders + env",
		.offset         = 0,
		.size           = SZ_512K,
		.mask_flags     = MTD_WRITEABLE,
	पूर्ण,
	अणु
		.name           = "kernel",
		.offset         = MTDPART_OFS_APPEND,
		.size           = SZ_2M,
		.mask_flags     = 0,
	पूर्ण,
	अणु
		.name           = "filesystem",
		.offset         = MTDPART_OFS_APPEND,
		.size           = MTDPART_SIZ_FULL,
		.mask_flags     = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data da850_evm_norflash_data = अणु
	.width		= 2,
	.parts		= da850_evm_norflash_partition,
	.nr_parts	= ARRAY_SIZE(da850_evm_norflash_partition),
पूर्ण;

अटल काष्ठा resource da850_evm_norflash_resource[] = अणु
	अणु
		.start	= DA8XX_AEMIF_CS2_BASE,
		.end	= DA8XX_AEMIF_CS2_BASE + SZ_32M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

/* DA850/OMAP-L138 EVM includes a 512 MByte large-page न_अंकD flash
 * (128K blocks). It may be used instead of the (शेष) SPI flash
 * to boot, using TI's tools to install the secondary boot loader
 * (UBL) and U-Boot.
 */
अटल काष्ठा mtd_partition da850_evm_nandflash_partition[] = अणु
	अणु
		.name		= "u-boot env",
		.offset		= 0,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	 पूर्ण,
	अणु
		.name		= "UBL",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
	अणु
		.name		= "u-boot",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 4 * SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण,
	अणु
		.name		= "kernel",
		.offset		= 0x200000,
		.size		= SZ_2M,
		.mask_flags	= 0,
	पूर्ण,
	अणु
		.name		= "filesystem",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_aemअगर_timing da850_evm_nandflash_timing = अणु
	.wsetup		= 24,
	.wstrobe	= 21,
	.whold		= 14,
	.rsetup		= 19,
	.rstrobe	= 50,
	.rhold		= 0,
	.ta		= 20,
पूर्ण;

अटल काष्ठा davinci_nand_pdata da850_evm_nandflash_data = अणु
	.core_chipsel	= 1,
	.parts		= da850_evm_nandflash_partition,
	.nr_parts	= ARRAY_SIZE(da850_evm_nandflash_partition),
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST,
	.ecc_bits	= 4,
	.bbt_options	= न_अंकD_BBT_USE_FLASH,
	.timing		= &da850_evm_nandflash_timing,
पूर्ण;

अटल काष्ठा resource da850_evm_nandflash_resource[] = अणु
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

अटल काष्ठा resource da850_evm_aemअगर_resource[] = अणु
	अणु
		.start	= DA8XX_AEMIF_CTL_BASE,
		.end	= DA8XX_AEMIF_CTL_BASE + SZ_32K,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा aemअगर_abus_data da850_evm_aemअगर_abus_data[] = अणु
	अणु
		.cs	= 3,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device da850_evm_aemअगर_devices[] = अणु
	अणु
		.name		= "davinci_nand",
		.id		= 1,
		.dev		= अणु
			.platक्रमm_data	= &da850_evm_nandflash_data,
		पूर्ण,
		.num_resources	= ARRAY_SIZE(da850_evm_nandflash_resource),
		.resource	= da850_evm_nandflash_resource,
	पूर्ण,
	अणु
		.name		= "physmap-flash",
		.id		= 0,
		.dev		= अणु
			.platक्रमm_data  = &da850_evm_norflash_data,
		पूर्ण,
		.num_resources	= 1,
		.resource	= da850_evm_norflash_resource,
	पूर्ण
पूर्ण;

अटल काष्ठा aemअगर_platक्रमm_data da850_evm_aemअगर_pdata = अणु
	.cs_offset = 2,
	.abus_data = da850_evm_aemअगर_abus_data,
	.num_abus_data = ARRAY_SIZE(da850_evm_aemअगर_abus_data),
	.sub_devices = da850_evm_aemअगर_devices,
	.num_sub_devices = ARRAY_SIZE(da850_evm_aemअगर_devices),
पूर्ण;

अटल काष्ठा platक्रमm_device da850_evm_aemअगर_device = अणु
	.name		= "ti-aemif",
	.id		= -1,
	.dev = अणु
		.platक्रमm_data	= &da850_evm_aemअगर_pdata,
	पूर्ण,
	.resource	= da850_evm_aemअगर_resource,
	.num_resources	= ARRAY_SIZE(da850_evm_aemअगर_resource),
पूर्ण;

अटल स्थिर लघु da850_evm_nand_pins[] = अणु
	DA850_EMA_D_0, DA850_EMA_D_1, DA850_EMA_D_2, DA850_EMA_D_3,
	DA850_EMA_D_4, DA850_EMA_D_5, DA850_EMA_D_6, DA850_EMA_D_7,
	DA850_EMA_A_1, DA850_EMA_A_2, DA850_NEMA_CS_3, DA850_NEMA_CS_4,
	DA850_NEMA_WE, DA850_NEMA_OE,
	-1
पूर्ण;

अटल स्थिर लघु da850_evm_nor_pins[] = अणु
	DA850_EMA_BA_1, DA850_EMA_CLK, DA850_EMA_WAIT_1, DA850_NEMA_CS_2,
	DA850_NEMA_WE, DA850_NEMA_OE, DA850_EMA_D_0, DA850_EMA_D_1,
	DA850_EMA_D_2, DA850_EMA_D_3, DA850_EMA_D_4, DA850_EMA_D_5,
	DA850_EMA_D_6, DA850_EMA_D_7, DA850_EMA_D_8, DA850_EMA_D_9,
	DA850_EMA_D_10, DA850_EMA_D_11, DA850_EMA_D_12, DA850_EMA_D_13,
	DA850_EMA_D_14, DA850_EMA_D_15, DA850_EMA_A_0, DA850_EMA_A_1,
	DA850_EMA_A_2, DA850_EMA_A_3, DA850_EMA_A_4, DA850_EMA_A_5,
	DA850_EMA_A_6, DA850_EMA_A_7, DA850_EMA_A_8, DA850_EMA_A_9,
	DA850_EMA_A_10, DA850_EMA_A_11, DA850_EMA_A_12, DA850_EMA_A_13,
	DA850_EMA_A_14, DA850_EMA_A_15, DA850_EMA_A_16, DA850_EMA_A_17,
	DA850_EMA_A_18, DA850_EMA_A_19, DA850_EMA_A_20, DA850_EMA_A_21,
	DA850_EMA_A_22, DA850_EMA_A_23,
	-1
पूर्ण;

#घोषणा HAS_MMC		IS_ENABLED(CONFIG_MMC_DAVINCI)

अटल अंतरभूत व्योम da850_evm_setup_nor_nand(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (!HAS_MMC) अणु
		ret = davinci_cfg_reg_list(da850_evm_nand_pins);
		अगर (ret)
			pr_warn("%s: NAND mux setup failed: %d\n",
				__func__, ret);

		ret = davinci_cfg_reg_list(da850_evm_nor_pins);
		अगर (ret)
			pr_warn("%s: NOR mux setup failed: %d\n",
				__func__, ret);

		ret = platक्रमm_device_रेजिस्टर(&da850_evm_aemअगर_device);
		अगर (ret)
			pr_warn("%s: registering aemif failed: %d\n",
				__func__, ret);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DA850_UI_RMII
अटल अंतरभूत व्योम da850_evm_setup_emac_rmii(पूर्णांक rmii_sel)
अणु
	काष्ठा davinci_soc_info *soc_info = &davinci_soc_info;

	soc_info->emac_pdata->rmii_en = 1;
	gpio_set_value_cansleep(rmii_sel, 0);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम da850_evm_setup_emac_rmii(पूर्णांक rmii_sel) अणु पूर्ण
#पूर्ण_अगर


#घोषणा DA850_KEYS_DEBOUNCE_MS	10
/*
 * At 200ms polling पूर्णांकerval it is possible to miss an
 * event by tapping very lightly on the push button but most
 * pushes करो result in an event; दीर्घer पूर्णांकervals require the
 * user to hold the button whereas लघुer पूर्णांकervals require
 * more CPU समय क्रम polling.
 */
#घोषणा DA850_GPIO_KEYS_POLL_MS	200

क्रमागत da850_evm_ui_exp_pins अणु
	DA850_EVM_UI_EXP_SEL_C = 5,
	DA850_EVM_UI_EXP_SEL_B,
	DA850_EVM_UI_EXP_SEL_A,
	DA850_EVM_UI_EXP_PB8,
	DA850_EVM_UI_EXP_PB7,
	DA850_EVM_UI_EXP_PB6,
	DA850_EVM_UI_EXP_PB5,
	DA850_EVM_UI_EXP_PB4,
	DA850_EVM_UI_EXP_PB3,
	DA850_EVM_UI_EXP_PB2,
	DA850_EVM_UI_EXP_PB1,
पूर्ण;

अटल स्थिर अक्षर * स्थिर da850_evm_ui_exp[] = अणु
	[DA850_EVM_UI_EXP_SEL_C]        = "sel_c",
	[DA850_EVM_UI_EXP_SEL_B]        = "sel_b",
	[DA850_EVM_UI_EXP_SEL_A]        = "sel_a",
	[DA850_EVM_UI_EXP_PB8]          = "pb8",
	[DA850_EVM_UI_EXP_PB7]          = "pb7",
	[DA850_EVM_UI_EXP_PB6]          = "pb6",
	[DA850_EVM_UI_EXP_PB5]          = "pb5",
	[DA850_EVM_UI_EXP_PB4]          = "pb4",
	[DA850_EVM_UI_EXP_PB3]          = "pb3",
	[DA850_EVM_UI_EXP_PB2]          = "pb2",
	[DA850_EVM_UI_EXP_PB1]          = "pb1",
पूर्ण;

#घोषणा DA850_N_UI_PB		8

अटल काष्ठा gpio_keys_button da850_evm_ui_keys[] = अणु
	[0 ... DA850_N_UI_PB - 1] = अणु
		.type			= EV_KEY,
		.active_low		= 1,
		.wakeup			= 0,
		.debounce_पूर्णांकerval	= DA850_KEYS_DEBOUNCE_MS,
		.code			= -1, /* asचिन्हित at runसमय */
		.gpio			= -1, /* asचिन्हित at runसमय */
		.desc			= शून्य, /* asचिन्हित at runसमय */
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data da850_evm_ui_keys_pdata = अणु
	.buttons = da850_evm_ui_keys,
	.nbuttons = ARRAY_SIZE(da850_evm_ui_keys),
	.poll_पूर्णांकerval = DA850_GPIO_KEYS_POLL_MS,
पूर्ण;

अटल काष्ठा platक्रमm_device da850_evm_ui_keys_device = अणु
	.name = "gpio-keys-polled",
	.id = 0,
	.dev = अणु
		.platक्रमm_data = &da850_evm_ui_keys_pdata
	पूर्ण,
पूर्ण;

अटल व्योम da850_evm_ui_keys_init(अचिन्हित gpio)
अणु
	पूर्णांक i;
	काष्ठा gpio_keys_button *button;

	क्रम (i = 0; i < DA850_N_UI_PB; i++) अणु
		button = &da850_evm_ui_keys[i];
		button->code = KEY_F8 - i;
		button->desc = da850_evm_ui_exp[DA850_EVM_UI_EXP_PB8 + i];
		button->gpio = gpio + DA850_EVM_UI_EXP_PB8 + i;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DA850_UI_SD_VIDEO_PORT
अटल अंतरभूत व्योम da850_evm_setup_video_port(पूर्णांक video_sel)
अणु
	gpio_set_value_cansleep(video_sel, 0);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम da850_evm_setup_video_port(पूर्णांक video_sel) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक da850_evm_ui_expander_setup(काष्ठा i2c_client *client, अचिन्हित gpio,
						अचिन्हित ngpio, व्योम *c)
अणु
	पूर्णांक sel_a, sel_b, sel_c, ret;

	sel_a = gpio + DA850_EVM_UI_EXP_SEL_A;
	sel_b = gpio + DA850_EVM_UI_EXP_SEL_B;
	sel_c = gpio + DA850_EVM_UI_EXP_SEL_C;

	ret = gpio_request(sel_a, da850_evm_ui_exp[DA850_EVM_UI_EXP_SEL_A]);
	अगर (ret) अणु
		pr_warn("Cannot open UI expander pin %d\n", sel_a);
		जाओ exp_setup_sela_fail;
	पूर्ण

	ret = gpio_request(sel_b, da850_evm_ui_exp[DA850_EVM_UI_EXP_SEL_B]);
	अगर (ret) अणु
		pr_warn("Cannot open UI expander pin %d\n", sel_b);
		जाओ exp_setup_selb_fail;
	पूर्ण

	ret = gpio_request(sel_c, da850_evm_ui_exp[DA850_EVM_UI_EXP_SEL_C]);
	अगर (ret) अणु
		pr_warn("Cannot open UI expander pin %d\n", sel_c);
		जाओ exp_setup_selc_fail;
	पूर्ण

	/* deselect all functionalities */
	gpio_direction_output(sel_a, 1);
	gpio_direction_output(sel_b, 1);
	gpio_direction_output(sel_c, 1);

	da850_evm_ui_keys_init(gpio);
	ret = platक्रमm_device_रेजिस्टर(&da850_evm_ui_keys_device);
	अगर (ret) अणु
		pr_warn("Could not register UI GPIO expander push-buttons");
		जाओ exp_setup_keys_fail;
	पूर्ण

	pr_info("DA850/OMAP-L138 EVM UI card detected\n");

	da850_evm_setup_nor_nand();

	da850_evm_setup_emac_rmii(sel_a);

	da850_evm_setup_video_port(sel_c);

	वापस 0;

exp_setup_keys_fail:
	gpio_मुक्त(sel_c);
exp_setup_selc_fail:
	gpio_मुक्त(sel_b);
exp_setup_selb_fail:
	gpio_मुक्त(sel_a);
exp_setup_sela_fail:
	वापस ret;
पूर्ण

अटल पूर्णांक da850_evm_ui_expander_tearकरोwn(काष्ठा i2c_client *client,
					अचिन्हित gpio, अचिन्हित ngpio, व्योम *c)
अणु
	platक्रमm_device_unरेजिस्टर(&da850_evm_ui_keys_device);

	/* deselect all functionalities */
	gpio_set_value_cansleep(gpio + DA850_EVM_UI_EXP_SEL_C, 1);
	gpio_set_value_cansleep(gpio + DA850_EVM_UI_EXP_SEL_B, 1);
	gpio_set_value_cansleep(gpio + DA850_EVM_UI_EXP_SEL_A, 1);

	gpio_मुक्त(gpio + DA850_EVM_UI_EXP_SEL_C);
	gpio_मुक्त(gpio + DA850_EVM_UI_EXP_SEL_B);
	gpio_मुक्त(gpio + DA850_EVM_UI_EXP_SEL_A);

	वापस 0;
पूर्ण

/* assign the baseboard expander's GPIOs after the UI board's */
#घोषणा DA850_UI_EXPANDER_N_GPIOS ARRAY_SIZE(da850_evm_ui_exp)
#घोषणा DA850_BB_EXPANDER_GPIO_BASE (DAVINCI_N_GPIO + DA850_UI_EXPANDER_N_GPIOS)

क्रमागत da850_evm_bb_exp_pins अणु
	DA850_EVM_BB_EXP_DEEP_SLEEP_EN = 0,
	DA850_EVM_BB_EXP_SW_RST,
	DA850_EVM_BB_EXP_TP_23,
	DA850_EVM_BB_EXP_TP_22,
	DA850_EVM_BB_EXP_TP_21,
	DA850_EVM_BB_EXP_USER_PB1,
	DA850_EVM_BB_EXP_USER_LED2,
	DA850_EVM_BB_EXP_USER_LED1,
	DA850_EVM_BB_EXP_USER_SW1,
	DA850_EVM_BB_EXP_USER_SW2,
	DA850_EVM_BB_EXP_USER_SW3,
	DA850_EVM_BB_EXP_USER_SW4,
	DA850_EVM_BB_EXP_USER_SW5,
	DA850_EVM_BB_EXP_USER_SW6,
	DA850_EVM_BB_EXP_USER_SW7,
	DA850_EVM_BB_EXP_USER_SW8
पूर्ण;

अटल स्थिर अक्षर * स्थिर da850_evm_bb_exp[] = अणु
	[DA850_EVM_BB_EXP_DEEP_SLEEP_EN]	= "deep_sleep_en",
	[DA850_EVM_BB_EXP_SW_RST]		= "sw_rst",
	[DA850_EVM_BB_EXP_TP_23]		= "tp_23",
	[DA850_EVM_BB_EXP_TP_22]		= "tp_22",
	[DA850_EVM_BB_EXP_TP_21]		= "tp_21",
	[DA850_EVM_BB_EXP_USER_PB1]		= "user_pb1",
	[DA850_EVM_BB_EXP_USER_LED2]		= "user_led2",
	[DA850_EVM_BB_EXP_USER_LED1]		= "user_led1",
	[DA850_EVM_BB_EXP_USER_SW1]		= "user_sw1",
	[DA850_EVM_BB_EXP_USER_SW2]		= "user_sw2",
	[DA850_EVM_BB_EXP_USER_SW3]		= "user_sw3",
	[DA850_EVM_BB_EXP_USER_SW4]		= "user_sw4",
	[DA850_EVM_BB_EXP_USER_SW5]		= "user_sw5",
	[DA850_EVM_BB_EXP_USER_SW6]		= "user_sw6",
	[DA850_EVM_BB_EXP_USER_SW7]		= "user_sw7",
	[DA850_EVM_BB_EXP_USER_SW8]		= "user_sw8",
पूर्ण;

#घोषणा DA850_N_BB_USER_SW	8

अटल काष्ठा gpio_keys_button da850_evm_bb_keys[] = अणु
	[0] = अणु
		.type			= EV_KEY,
		.active_low		= 1,
		.wakeup			= 0,
		.debounce_पूर्णांकerval	= DA850_KEYS_DEBOUNCE_MS,
		.code			= KEY_PROG1,
		.desc			= शून्य, /* asचिन्हित at runसमय */
		.gpio			= -1, /* asचिन्हित at runसमय */
	पूर्ण,
	[1 ... DA850_N_BB_USER_SW] = अणु
		.type			= EV_SW,
		.active_low		= 1,
		.wakeup			= 0,
		.debounce_पूर्णांकerval	= DA850_KEYS_DEBOUNCE_MS,
		.code			= -1, /* asचिन्हित at runसमय */
		.desc			= शून्य, /* asचिन्हित at runसमय */
		.gpio			= -1, /* asचिन्हित at runसमय */
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data da850_evm_bb_keys_pdata = अणु
	.buttons = da850_evm_bb_keys,
	.nbuttons = ARRAY_SIZE(da850_evm_bb_keys),
	.poll_पूर्णांकerval = DA850_GPIO_KEYS_POLL_MS,
पूर्ण;

अटल काष्ठा platक्रमm_device da850_evm_bb_keys_device = अणु
	.name = "gpio-keys-polled",
	.id = 1,
	.dev = अणु
		.platक्रमm_data = &da850_evm_bb_keys_pdata
	पूर्ण,
पूर्ण;

अटल व्योम da850_evm_bb_keys_init(अचिन्हित gpio)
अणु
	पूर्णांक i;
	काष्ठा gpio_keys_button *button;

	button = &da850_evm_bb_keys[0];
	button->desc = da850_evm_bb_exp[DA850_EVM_BB_EXP_USER_PB1];
	button->gpio = gpio + DA850_EVM_BB_EXP_USER_PB1;

	क्रम (i = 0; i < DA850_N_BB_USER_SW; i++) अणु
		button = &da850_evm_bb_keys[i + 1];
		button->code = SW_LID + i;
		button->desc = da850_evm_bb_exp[DA850_EVM_BB_EXP_USER_SW1 + i];
		button->gpio = gpio + DA850_EVM_BB_EXP_USER_SW1 + i;
	पूर्ण
पूर्ण

अटल काष्ठा gpio_led da850_evm_bb_leds[] = अणु
	अणु
		.name = "user_led2",
	पूर्ण,
	अणु
		.name = "user_led1",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data da850_evm_bb_leds_pdata = अणु
	.leds = da850_evm_bb_leds,
	.num_leds = ARRAY_SIZE(da850_evm_bb_leds),
पूर्ण;

अटल काष्ठा gpiod_lookup_table da850_evm_bb_leds_gpio_table = अणु
	.dev_id = "leds-gpio",
	.table = अणु
		GPIO_LOOKUP_IDX("i2c-bb-expander",
				DA850_EVM_BB_EXP_USER_LED2, शून्य,
				0, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("i2c-bb-expander",
				DA850_EVM_BB_EXP_USER_LED2 + 1, शून्य,
				1, GPIO_ACTIVE_LOW),

		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device da850_evm_bb_leds_device = अणु
	.name		= "leds-gpio",
	.id		= -1,
	.dev = अणु
		.platक्रमm_data = &da850_evm_bb_leds_pdata
	पूर्ण
पूर्ण;

अटल पूर्णांक da850_evm_bb_expander_setup(काष्ठा i2c_client *client,
						अचिन्हित gpio, अचिन्हित ngpio,
						व्योम *c)
अणु
	पूर्णांक ret;

	/*
	 * Register the चयनes and pushbutton on the baseboard as a gpio-keys
	 * device.
	 */
	da850_evm_bb_keys_init(gpio);
	ret = platक्रमm_device_रेजिस्टर(&da850_evm_bb_keys_device);
	अगर (ret) अणु
		pr_warn("Could not register baseboard GPIO expander keys");
		जाओ io_exp_setup_sw_fail;
	पूर्ण

	gpiod_add_lookup_table(&da850_evm_bb_leds_gpio_table);
	ret = platक्रमm_device_रेजिस्टर(&da850_evm_bb_leds_device);
	अगर (ret) अणु
		pr_warn("Could not register baseboard GPIO expander LEDs");
		जाओ io_exp_setup_leds_fail;
	पूर्ण

	वापस 0;

io_exp_setup_leds_fail:
	platक्रमm_device_unरेजिस्टर(&da850_evm_bb_keys_device);
io_exp_setup_sw_fail:
	वापस ret;
पूर्ण

अटल पूर्णांक da850_evm_bb_expander_tearकरोwn(काष्ठा i2c_client *client,
					अचिन्हित gpio, अचिन्हित ngpio, व्योम *c)
अणु
	platक्रमm_device_unरेजिस्टर(&da850_evm_bb_leds_device);
	platक्रमm_device_unरेजिस्टर(&da850_evm_bb_keys_device);

	वापस 0;
पूर्ण

अटल काष्ठा pca953x_platक्रमm_data da850_evm_ui_expander_info = अणु
	.gpio_base	= DAVINCI_N_GPIO,
	.setup		= da850_evm_ui_expander_setup,
	.tearकरोwn	= da850_evm_ui_expander_tearकरोwn,
	.names		= da850_evm_ui_exp,
पूर्ण;

अटल काष्ठा pca953x_platक्रमm_data da850_evm_bb_expander_info = अणु
	.gpio_base	= DA850_BB_EXPANDER_GPIO_BASE,
	.setup		= da850_evm_bb_expander_setup,
	.tearकरोwn	= da850_evm_bb_expander_tearकरोwn,
	.names		= da850_evm_bb_exp,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata da850_evm_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("tlv320aic3x", 0x18),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("tca6416", 0x20),
		.dev_name = "ui-expander",
		.platक्रमm_data = &da850_evm_ui_expander_info,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("tca6416", 0x21),
		.dev_name = "bb-expander",
		.platक्रमm_data = &da850_evm_bb_expander_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_i2c_platक्रमm_data da850_evm_i2c_0_pdata = अणु
	.bus_freq	= 100,	/* kHz */
	.bus_delay	= 0,	/* usec */
पूर्ण;

/* davinci da850 evm audio machine driver */
अटल u8 da850_iis_serializer_direction[] = अणु
	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,
	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,
	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,	TX_MODE,
	RX_MODE,	INACTIVE_MODE,	INACTIVE_MODE,	INACTIVE_MODE,
पूर्ण;

अटल काष्ठा snd_platक्रमm_data da850_evm_snd_data = अणु
	.tx_dma_offset		= 0x2000,
	.rx_dma_offset		= 0x2000,
	.op_mode		= DAVINCI_MCASP_IIS_MODE,
	.num_serializer		= ARRAY_SIZE(da850_iis_serializer_direction),
	.tdm_slots		= 2,
	.serial_dir		= da850_iis_serializer_direction,
	.asp_chan_q		= EVENTQ_0,
	.ram_chan_q		= EVENTQ_1,
	.version		= MCASP_VERSION_2,
	.txnumevt		= 1,
	.rxnumevt		= 1,
	.sram_size_playback	= SZ_8K,
	.sram_size_capture	= SZ_8K,
पूर्ण;

अटल स्थिर लघु da850_evm_mcasp_pins[] __initस्थिर = अणु
	DA850_AHCLKX, DA850_ACLKX, DA850_AFSX,
	DA850_AHCLKR, DA850_ACLKR, DA850_AFSR, DA850_AMUTE,
	DA850_AXR_11, DA850_AXR_12,
	-1
पूर्ण;

#घोषणा DA850_MMCSD_CD_PIN		GPIO_TO_PIN(4, 0)
#घोषणा DA850_MMCSD_WP_PIN		GPIO_TO_PIN(4, 1)

अटल काष्ठा gpiod_lookup_table mmc_gpios_table = अणु
	.dev_id = "da830-mmc.0",
	.table = अणु
		/* gpio chip 2 contains gpio range 64-95 */
		GPIO_LOOKUP("davinci_gpio", DA850_MMCSD_CD_PIN, "cd",
			    GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("davinci_gpio", DA850_MMCSD_WP_PIN, "wp",
			    GPIO_ACTIVE_HIGH),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_mmc_config da850_mmc_config = अणु
	.wires		= 4,
	.max_freq	= 50000000,
	.caps		= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED,
पूर्ण;

अटल स्थिर लघु da850_evm_mmcsd0_pins[] __initस्थिर = अणु
	DA850_MMCSD0_DAT_0, DA850_MMCSD0_DAT_1, DA850_MMCSD0_DAT_2,
	DA850_MMCSD0_DAT_3, DA850_MMCSD0_CLK, DA850_MMCSD0_CMD,
	DA850_GPIO4_0, DA850_GPIO4_1,
	-1
पूर्ण;

अटल काष्ठा property_entry da850_lcd_backlight_props[] = अणु
	PROPERTY_ENTRY_BOOL("default-on"),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा gpiod_lookup_table da850_lcd_backlight_gpio_table = अणु
	.dev_id		= "gpio-backlight",
	.table = अणु
		GPIO_LOOKUP("davinci_gpio", DA850_LCD_BL_PIN, शून्य, 0),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info da850_lcd_backlight_info = अणु
	.name		= "gpio-backlight",
	.id		= PLATFORM_DEVID_NONE,
	.properties	= da850_lcd_backlight_props,
पूर्ण;

अटल काष्ठा regulator_consumer_supply da850_lcd_supplies[] = अणु
	REGULATOR_SUPPLY("lcd", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data da850_lcd_supply_data = अणु
	.consumer_supplies	= da850_lcd_supplies,
	.num_consumer_supplies	= ARRAY_SIZE(da850_lcd_supplies),
	.स्थिरraपूर्णांकs    = अणु
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	पूर्ण,
पूर्ण;

अटल काष्ठा fixed_voltage_config da850_lcd_supply = अणु
	.supply_name		= "lcd",
	.microvolts		= 33000000,
	.init_data		= &da850_lcd_supply_data,
पूर्ण;

अटल काष्ठा platक्रमm_device da850_lcd_supply_device = अणु
	.name			= "reg-fixed-voltage",
	.id			= 1, /* Dummy fixed regulator is 0 */
	.dev			= अणु
		.platक्रमm_data = &da850_lcd_supply,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table da850_lcd_supply_gpio_table = अणु
	.dev_id			= "reg-fixed-voltage.1",
	.table = अणु
		GPIO_LOOKUP("davinci_gpio", DA850_LCD_PWR_PIN, शून्य, 0),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table *da850_lcd_gpio_lookups[] = अणु
	&da850_lcd_backlight_gpio_table,
	&da850_lcd_supply_gpio_table,
पूर्ण;

अटल पूर्णांक da850_lcd_hw_init(व्योम)
अणु
	काष्ठा platक्रमm_device *backlight;
	पूर्णांक status;

	gpiod_add_lookup_tables(da850_lcd_gpio_lookups,
				ARRAY_SIZE(da850_lcd_gpio_lookups));

	backlight = platक्रमm_device_रेजिस्टर_full(&da850_lcd_backlight_info);
	अगर (IS_ERR(backlight))
		वापस PTR_ERR(backlight);

	status = platक्रमm_device_रेजिस्टर(&da850_lcd_supply_device);
	अगर (status)
		वापस status;

	वापस 0;
पूर्ण

/* Fixed regulator support */
अटल काष्ठा regulator_consumer_supply fixed_supplies[] = अणु
	/* Baseboard 3.3V: 5V -> TPS73701DCQ -> 3.3V */
	REGULATOR_SUPPLY("AVDD", "1-0018"),
	REGULATOR_SUPPLY("DRVDD", "1-0018"),

	/* Baseboard 1.8V: 5V -> TPS73701DCQ -> 1.8V */
	REGULATOR_SUPPLY("DVDD", "1-0018"),

	/* UI card 3.3V: 5V -> TPS73701DCQ -> 3.3V */
	REGULATOR_SUPPLY("vcc", "1-0020"),
पूर्ण;

/* TPS65070 voltage regulator support */

/* 3.3V */
अटल काष्ठा regulator_consumer_supply tps65070_dcdc1_consumers[] = अणु
	अणु
		.supply = "usb0_vdda33",
	पूर्ण,
	अणु
		.supply = "usb1_vdda33",
	पूर्ण,
पूर्ण;

/* 3.3V or 1.8V */
अटल काष्ठा regulator_consumer_supply tps65070_dcdc2_consumers[] = अणु
	अणु
		.supply = "dvdd3318_a",
	पूर्ण,
	अणु
		.supply = "dvdd3318_b",
	पूर्ण,
	अणु
		.supply = "dvdd3318_c",
	पूर्ण,
	REGULATOR_SUPPLY("IOVDD", "1-0018"),
पूर्ण;

/* 1.2V */
अटल काष्ठा regulator_consumer_supply tps65070_dcdc3_consumers[] = अणु
	अणु
		.supply = "cvdd",
	पूर्ण,
पूर्ण;

/* 1.8V LDO */
अटल काष्ठा regulator_consumer_supply tps65070_lकरो1_consumers[] = अणु
	अणु
		.supply = "sata_vddr",
	पूर्ण,
	अणु
		.supply = "usb0_vdda18",
	पूर्ण,
	अणु
		.supply = "usb1_vdda18",
	पूर्ण,
	अणु
		.supply = "ddr_dvdd18",
	पूर्ण,
पूर्ण;

/* 1.2V LDO */
अटल काष्ठा regulator_consumer_supply tps65070_lकरो2_consumers[] = अणु
	अणु
		.supply = "sata_vdd",
	पूर्ण,
	अणु
		.supply = "pll0_vdda",
	पूर्ण,
	अणु
		.supply = "pll1_vdda",
	पूर्ण,
	अणु
		.supply = "usbs_cvdd",
	पूर्ण,
	अणु
		.supply = "vddarnwa1",
	पूर्ण,
पूर्ण;

/* We take advantage of the fact that both defdcdcअणु2,3पूर्ण are tied high */
अटल काष्ठा tps6507x_reg_platक्रमm_data tps6507x_platक्रमm_data = अणु
	.defdcdc_शेष = true,
पूर्ण;

अटल काष्ठा regulator_init_data tps65070_regulator_data[] = अणु
	/* dcdc1 */
	अणु
		.स्थिरraपूर्णांकs = अणु
			.min_uV = 3150000,
			.max_uV = 3450000,
			.valid_ops_mask = (REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_STATUS),
			.boot_on = 1,
		पूर्ण,
		.num_consumer_supplies = ARRAY_SIZE(tps65070_dcdc1_consumers),
		.consumer_supplies = tps65070_dcdc1_consumers,
	पूर्ण,

	/* dcdc2 */
	अणु
		.स्थिरraपूर्णांकs = अणु
			.min_uV = 1710000,
			.max_uV = 3450000,
			.valid_ops_mask = (REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_STATUS),
			.boot_on = 1,
			.always_on = 1,
		पूर्ण,
		.num_consumer_supplies = ARRAY_SIZE(tps65070_dcdc2_consumers),
		.consumer_supplies = tps65070_dcdc2_consumers,
		.driver_data = &tps6507x_platक्रमm_data,
	पूर्ण,

	/* dcdc3 */
	अणु
		.स्थिरraपूर्णांकs = अणु
			.min_uV = 950000,
			.max_uV = 1350000,
			.valid_ops_mask = (REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_STATUS),
			.boot_on = 1,
		पूर्ण,
		.num_consumer_supplies = ARRAY_SIZE(tps65070_dcdc3_consumers),
		.consumer_supplies = tps65070_dcdc3_consumers,
		.driver_data = &tps6507x_platक्रमm_data,
	पूर्ण,

	/* lकरो1 */
	अणु
		.स्थिरraपूर्णांकs = अणु
			.min_uV = 1710000,
			.max_uV = 1890000,
			.valid_ops_mask = (REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_STATUS),
			.boot_on = 1,
		पूर्ण,
		.num_consumer_supplies = ARRAY_SIZE(tps65070_lकरो1_consumers),
		.consumer_supplies = tps65070_lकरो1_consumers,
	पूर्ण,

	/* lकरो2 */
	अणु
		.स्थिरraपूर्णांकs = अणु
			.min_uV = 1140000,
			.max_uV = 1320000,
			.valid_ops_mask = (REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_STATUS),
			.boot_on = 1,
		पूर्ण,
		.num_consumer_supplies = ARRAY_SIZE(tps65070_lकरो2_consumers),
		.consumer_supplies = tps65070_lकरो2_consumers,
	पूर्ण,
पूर्ण;

अटल काष्ठा touchscreen_init_data tps6507x_touchscreen_data = अणु
	.poll_period =  30,	/* ms between touch samples */
	.min_pressure = 0x30,	/* minimum pressure to trigger touch */
	.venकरोr = 0,		/* /sys/class/input/input?/id/venकरोr */
	.product = 65070,	/* /sys/class/input/input?/id/product */
	.version = 0x100,	/* /sys/class/input/input?/id/version */
पूर्ण;

अटल काष्ठा tps6507x_board tps_board = अणु
	.tps6507x_pmic_init_data = &tps65070_regulator_data[0],
	.tps6507x_ts_init_data = &tps6507x_touchscreen_data,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata da850_evm_tps65070_info[] = अणु
	अणु
		I2C_BOARD_INFO("tps6507x", 0x48),
		.platक्रमm_data = &tps_board,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pmic_tps65070_init(व्योम)
अणु
	वापस i2c_रेजिस्टर_board_info(1, da850_evm_tps65070_info,
					ARRAY_SIZE(da850_evm_tps65070_info));
पूर्ण

अटल स्थिर लघु da850_evm_lcdc_pins[] = अणु
	DA850_GPIO2_8, DA850_GPIO2_15,
	-1
पूर्ण;

अटल स्थिर लघु da850_evm_mii_pins[] = अणु
	DA850_MII_TXEN, DA850_MII_TXCLK, DA850_MII_COL, DA850_MII_TXD_3,
	DA850_MII_TXD_2, DA850_MII_TXD_1, DA850_MII_TXD_0, DA850_MII_RXER,
	DA850_MII_CRS, DA850_MII_RXCLK, DA850_MII_RXDV, DA850_MII_RXD_3,
	DA850_MII_RXD_2, DA850_MII_RXD_1, DA850_MII_RXD_0, DA850_MDIO_CLK,
	DA850_MDIO_D,
	-1
पूर्ण;

अटल स्थिर लघु da850_evm_rmii_pins[] = अणु
	DA850_RMII_TXD_0, DA850_RMII_TXD_1, DA850_RMII_TXEN,
	DA850_RMII_CRS_DV, DA850_RMII_RXD_0, DA850_RMII_RXD_1,
	DA850_RMII_RXER, DA850_RMII_MHZ_50_CLK, DA850_MDIO_CLK,
	DA850_MDIO_D,
	-1
पूर्ण;

अटल काष्ठा gpiod_hog da850_evm_emac_gpio_hogs[] = अणु
	अणु
		.chip_label	= "davinci_gpio",
		.chip_hwnum	= DA850_MII_MDIO_CLKEN_PIN,
		.line_name	= "mdio_clk_en",
		.lflags		= 0,
		/* dflags set in da850_evm_config_emac() */
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init da850_evm_config_emac(व्योम)
अणु
	व्योम __iomem *cfg_chip3_base;
	पूर्णांक ret;
	u32 val;
	काष्ठा davinci_soc_info *soc_info = &davinci_soc_info;
	u8 rmii_en = soc_info->emac_pdata->rmii_en;

	अगर (!machine_is_davinci_da850_evm())
		वापस 0;

	cfg_chip3_base = DA8XX_SYSCFG0_VIRT(DA8XX_CFGCHIP3_REG);

	val = __raw_पढ़ोl(cfg_chip3_base);

	अगर (rmii_en) अणु
		val |= BIT(8);
		ret = davinci_cfg_reg_list(da850_evm_rmii_pins);
		pr_info("EMAC: RMII PHY configured, MII PHY will not be"
							" functional\n");
	पूर्ण अन्यथा अणु
		val &= ~BIT(8);
		ret = davinci_cfg_reg_list(da850_evm_mii_pins);
		pr_info("EMAC: MII PHY configured, RMII PHY will not be"
							" functional\n");
	पूर्ण

	अगर (ret)
		pr_warn("%s: CPGMAC/RMII mux setup failed: %d\n",
			__func__, ret);

	/* configure the CFGCHIP3 रेजिस्टर क्रम RMII or MII */
	__raw_ग_लिखोl(val, cfg_chip3_base);

	ret = davinci_cfg_reg(DA850_GPIO2_6);
	अगर (ret)
		pr_warn("%s:GPIO(2,6) mux setup failed\n", __func__);

	da850_evm_emac_gpio_hogs[0].dflags = rmii_en ? GPIOD_OUT_HIGH
						     : GPIOD_OUT_LOW;
	gpiod_add_hogs(da850_evm_emac_gpio_hogs);

	soc_info->emac_pdata->phy_id = DA850_EVM_PHY_ID;

	ret = da8xx_रेजिस्टर_emac();
	अगर (ret)
		pr_warn("%s: EMAC registration failed: %d\n", __func__, ret);

	वापस 0;
पूर्ण
device_initcall(da850_evm_config_emac);

/*
 * The following EDMA channels/slots are not being used by drivers (क्रम
 * example: Timer, GPIO, UART events etc) on da850/omap-l138 EVM, hence
 * they are being reserved क्रम codecs on the DSP side.
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

#अगर_घोषित CONFIG_CPU_FREQ
अटल __init पूर्णांक da850_evm_init_cpufreq(व्योम)
अणु
	चयन (प्रणाली_rev & 0xF) अणु
	हाल 3:
		da850_max_speed = 456000;
		अवरोध;
	हाल 2:
		da850_max_speed = 408000;
		अवरोध;
	हाल 1:
		da850_max_speed = 372000;
		अवरोध;
	पूर्ण

	वापस da850_रेजिस्टर_cpufreq("pll0_sysclk3");
पूर्ण
#अन्यथा
अटल __init पूर्णांक da850_evm_init_cpufreq(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_DA850_UI_SD_VIDEO_PORT)

#घोषणा TVP5147_CH0		"tvp514x-0"
#घोषणा TVP5147_CH1		"tvp514x-1"

/* VPIF capture configuration */
अटल काष्ठा tvp514x_platक्रमm_data tvp5146_pdata = अणु
		.clk_polarity = 0,
		.hs_polarity  = 1,
		.vs_polarity  = 1,
पूर्ण;

#घोषणा TVP514X_STD_ALL (V4L2_STD_NTSC | V4L2_STD_PAL)

अटल काष्ठा vpअगर_input da850_ch0_inमाला_दो[] = अणु
	अणु
		.input = अणु
			.index = 0,
			.name  = "Composite",
			.type  = V4L2_INPUT_TYPE_CAMERA,
			.capabilities = V4L2_IN_CAP_STD,
			.std   = TVP514X_STD_ALL,
		पूर्ण,
		.input_route = INPUT_CVBS_VI2B,
		.output_route = OUTPUT_10BIT_422_EMBEDDED_SYNC,
		.subdev_name = TVP5147_CH0,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_input da850_ch1_inमाला_दो[] = अणु
	अणु
		.input = अणु
			.index = 0,
			.name  = "S-Video",
			.type  = V4L2_INPUT_TYPE_CAMERA,
			.capabilities = V4L2_IN_CAP_STD,
			.std   = TVP514X_STD_ALL,
		पूर्ण,
		.input_route = INPUT_SVIDEO_VI2C_VI1C,
		.output_route = OUTPUT_10BIT_422_EMBEDDED_SYNC,
		.subdev_name = TVP5147_CH1,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_subdev_info da850_vpअगर_capture_sdev_info[] = अणु
	अणु
		.name = TVP5147_CH0,
		.board_info = अणु
			I2C_BOARD_INFO("tvp5146", 0x5d),
			.platक्रमm_data = &tvp5146_pdata,
		पूर्ण,
	पूर्ण,
	अणु
		.name = TVP5147_CH1,
		.board_info = अणु
			I2C_BOARD_INFO("tvp5146", 0x5c),
			.platक्रमm_data = &tvp5146_pdata,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_capture_config da850_vpअगर_capture_config = अणु
	.subdev_info = da850_vpअगर_capture_sdev_info,
	.subdev_count = ARRAY_SIZE(da850_vpअगर_capture_sdev_info),
	.i2c_adapter_id = 1,
	.chan_config[0] = अणु
		.inमाला_दो = da850_ch0_inमाला_दो,
		.input_count = ARRAY_SIZE(da850_ch0_inमाला_दो),
		.vpअगर_अगर = अणु
			.अगर_type = VPIF_IF_BT656,
			.hd_pol  = 1,
			.vd_pol  = 1,
			.fid_pol = 0,
		पूर्ण,
	पूर्ण,
	.chan_config[1] = अणु
		.inमाला_दो = da850_ch1_inमाला_दो,
		.input_count = ARRAY_SIZE(da850_ch1_inमाला_दो),
		.vpअगर_अगर = अणु
			.अगर_type = VPIF_IF_BT656,
			.hd_pol  = 1,
			.vd_pol  = 1,
			.fid_pol = 0,
		पूर्ण,
	पूर्ण,
	.card_name = "DA850/OMAP-L138 Video Capture",
पूर्ण;

/* VPIF display configuration */

अटल काष्ठा adv7343_platक्रमm_data adv7343_pdata = अणु
	.mode_config = अणु
		.dac = अणु 1, 1, 1 पूर्ण,
	पूर्ण,
	.sd_config = अणु
		.sd_dac_out = अणु 1 पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_subdev_info da850_vpअगर_subdev[] = अणु
	अणु
		.name = "adv7343",
		.board_info = अणु
			I2C_BOARD_INFO("adv7343", 0x2a),
			.platक्रमm_data = &adv7343_pdata,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vpअगर_output da850_ch0_outमाला_दो[] = अणु
	अणु
		.output = अणु
			.index = 0,
			.name = "Composite",
			.type = V4L2_OUTPUT_TYPE_ANALOG,
			.capabilities = V4L2_OUT_CAP_STD,
			.std = V4L2_STD_ALL,
		पूर्ण,
		.subdev_name = "adv7343",
		.output_route = ADV7343_COMPOSITE_ID,
	पूर्ण,
	अणु
		.output = अणु
			.index = 1,
			.name = "S-Video",
			.type = V4L2_OUTPUT_TYPE_ANALOG,
			.capabilities = V4L2_OUT_CAP_STD,
			.std = V4L2_STD_ALL,
		पूर्ण,
		.subdev_name = "adv7343",
		.output_route = ADV7343_SVIDEO_ID,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_display_config da850_vpअगर_display_config = अणु
	.subdevinfo   = da850_vpअगर_subdev,
	.subdev_count = ARRAY_SIZE(da850_vpअगर_subdev),
	.chan_config[0] = अणु
		.outमाला_दो = da850_ch0_outमाला_दो,
		.output_count = ARRAY_SIZE(da850_ch0_outमाला_दो),
	पूर्ण,
	.card_name    = "DA850/OMAP-L138 Video Display",
	.i2c_adapter_id = 1,
पूर्ण;

अटल __init व्योम da850_vpअगर_init(व्योम)
अणु
	पूर्णांक ret;

	ret = da850_रेजिस्टर_vpअगर();
	अगर (ret)
		pr_warn("da850_evm_init: VPIF setup failed: %d\n", ret);

	ret = davinci_cfg_reg_list(da850_vpअगर_capture_pins);
	अगर (ret)
		pr_warn("da850_evm_init: VPIF capture mux setup failed: %d\n",
			ret);

	ret = da850_रेजिस्टर_vpअगर_capture(&da850_vpअगर_capture_config);
	अगर (ret)
		pr_warn("da850_evm_init: VPIF capture setup failed: %d\n", ret);

	ret = davinci_cfg_reg_list(da850_vpअगर_display_pins);
	अगर (ret)
		pr_warn("da850_evm_init: VPIF display mux setup failed: %d\n",
			ret);

	ret = da850_रेजिस्टर_vpअगर_display(&da850_vpअगर_display_config);
	अगर (ret)
		pr_warn("da850_evm_init: VPIF display setup failed: %d\n", ret);
पूर्ण

#अन्यथा
अटल __init व्योम da850_vpअगर_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#घोषणा DA850EVM_SATA_REFCLKPN_RATE	(100 * 1000 * 1000)

अटल __init व्योम da850_evm_init(व्योम)
अणु
	पूर्णांक ret;

	da850_रेजिस्टर_घड़ीs();

	ret = da850_रेजिस्टर_gpio();
	अगर (ret)
		pr_warn("%s: GPIO init failed: %d\n", __func__, ret);

	regulator_रेजिस्टर_fixed(0, fixed_supplies, ARRAY_SIZE(fixed_supplies));

	ret = pmic_tps65070_init();
	अगर (ret)
		pr_warn("%s: TPS65070 PMIC init failed: %d\n", __func__, ret);

	ret = da850_रेजिस्टर_edma(da850_edma_rsv);
	अगर (ret)
		pr_warn("%s: EDMA registration failed: %d\n", __func__, ret);

	ret = davinci_cfg_reg_list(da850_i2c0_pins);
	अगर (ret)
		pr_warn("%s: I2C0 mux setup failed: %d\n", __func__, ret);

	ret = da8xx_रेजिस्टर_i2c(0, &da850_evm_i2c_0_pdata);
	अगर (ret)
		pr_warn("%s: I2C0 registration failed: %d\n", __func__, ret);


	ret = da8xx_रेजिस्टर_watchकरोg();
	अगर (ret)
		pr_warn("%s: watchdog registration failed: %d\n",
			__func__, ret);

	अगर (HAS_MMC) अणु
		ret = davinci_cfg_reg_list(da850_evm_mmcsd0_pins);
		अगर (ret)
			pr_warn("%s: MMCSD0 mux setup failed: %d\n",
				__func__, ret);

		gpiod_add_lookup_table(&mmc_gpios_table);

		ret = da8xx_रेजिस्टर_mmcsd0(&da850_mmc_config);
		अगर (ret)
			pr_warn("%s: MMCSD0 registration failed: %d\n",
				__func__, ret);
	पूर्ण

	davinci_serial_init(da8xx_serial_device);

	nvmem_add_cell_table(&da850evm_nvmem_cell_table);
	nvmem_add_cell_lookups(&da850evm_nvmem_cell_lookup, 1);

	i2c_रेजिस्टर_board_info(1, da850_evm_i2c_devices,
			ARRAY_SIZE(da850_evm_i2c_devices));

	/*
	 * shut करोwn uart 0 and 1; they are not used on the board and
	 * accessing them causes endless "too much work in irq53" messages
	 * with arago fs
	 */
	__raw_ग_लिखोl(0, IO_ADDRESS(DA8XX_UART1_BASE) + 0x30);
	__raw_ग_लिखोl(0, IO_ADDRESS(DA8XX_UART0_BASE) + 0x30);

	ret = davinci_cfg_reg_list(da850_evm_mcasp_pins);
	अगर (ret)
		pr_warn("%s: McASP mux setup failed: %d\n", __func__, ret);

	da850_evm_snd_data.sram_pool = sram_get_gen_pool();
	da8xx_रेजिस्टर_mcasp(0, &da850_evm_snd_data);

	ret = davinci_cfg_reg_list(da850_lcdcntl_pins);
	अगर (ret)
		pr_warn("%s: LCDC mux setup failed: %d\n", __func__, ret);

	ret = da8xx_रेजिस्टर_uio_pruss();
	अगर (ret)
		pr_warn("da850_evm_init: pruss initialization failed: %d\n",
				ret);

	/* Handle board specअगरic muxing क्रम LCD here */
	ret = davinci_cfg_reg_list(da850_evm_lcdc_pins);
	अगर (ret)
		pr_warn("%s: EVM specific LCD mux setup failed: %d\n",
			__func__, ret);

	ret = da850_lcd_hw_init();
	अगर (ret)
		pr_warn("%s: LCD initialization failed: %d\n", __func__, ret);

	ret = da8xx_रेजिस्टर_lcdc(&sharp_lk043t1dg01_pdata);
	अगर (ret)
		pr_warn("%s: LCDC registration failed: %d\n", __func__, ret);

	ret = da8xx_रेजिस्टर_rtc();
	अगर (ret)
		pr_warn("%s: RTC setup failed: %d\n", __func__, ret);

	ret = da850_evm_init_cpufreq();
	अगर (ret)
		pr_warn("%s: cpufreq registration failed: %d\n", __func__, ret);

	ret = da8xx_रेजिस्टर_cpuidle();
	अगर (ret)
		pr_warn("%s: cpuidle registration failed: %d\n", __func__, ret);

	davinci_pm_init();
	da850_vpअगर_init();

	ret = spi_रेजिस्टर_board_info(da850evm_spi_info,
				      ARRAY_SIZE(da850evm_spi_info));
	अगर (ret)
		pr_warn("%s: spi info registration failed: %d\n", __func__,
			ret);

	ret = da8xx_रेजिस्टर_spi_bus(1, ARRAY_SIZE(da850evm_spi_info));
	अगर (ret)
		pr_warn("%s: SPI 1 registration failed: %d\n", __func__, ret);

	ret = da850_रेजिस्टर_sata(DA850EVM_SATA_REFCLKPN_RATE);
	अगर (ret)
		pr_warn("%s: SATA registration failed: %d\n", __func__, ret);

	ret = da8xx_रेजिस्टर_rproc();
	अगर (ret)
		pr_warn("%s: dsp/rproc registration failed: %d\n",
			__func__, ret);

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
अटल पूर्णांक __init da850_evm_console_init(व्योम)
अणु
	अगर (!machine_is_davinci_da850_evm())
		वापस 0;

	वापस add_preferred_console("ttyS", 2, "115200");
पूर्ण
console_initcall(da850_evm_console_init);
#पूर्ण_अगर

अटल व्योम __init da850_evm_map_io(व्योम)
अणु
	da850_init();
पूर्ण

MACHINE_START(DAVINCI_DA850_EVM, "DaVinci DA850/OMAP-L138/AM18x EVM")
	.atag_offset	= 0x100,
	.map_io		= da850_evm_map_io,
	.init_irq	= da850_init_irq,
	.init_समय	= da850_init_समय,
	.init_machine	= da850_evm_init,
	.init_late	= davinci_init_late,
	.dma_zone_size	= SZ_128M,
	.reserve	= da8xx_rproc_reserve_cma,
MACHINE_END
