<शैली गुरु>
/*
 * TI DaVinci DM365 EVM board support
 *
 * Copyright (C) 2009 Texas Instruments Incorporated
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/property.h>
#समावेश <linux/leds.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/input.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/eeprom.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <linux/platक्रमm_data/ti-aemअगर.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश <mach/mux.h>
#समावेश <mach/common.h>
#समावेश <linux/platक्रमm_data/i2c-davinci.h>
#समावेश <mach/serial.h>
#समावेश <linux/platक्रमm_data/mmc-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci.h>
#समावेश <linux/platक्रमm_data/keyscan-davinci.h>

#समावेश <media/i2c/ths7303.h>
#समावेश <media/i2c/tvp514x.h>

#समावेश "davinci.h"

अटल अंतरभूत पूर्णांक have_imager(व्योम)
अणु
	/* REVISIT when it's supported, trigger via Kconfig */
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक have_tvp7002(व्योम)
अणु
	/* REVISIT when it's supported, trigger via Kconfig */
	वापस 0;
पूर्ण

#घोषणा DM365_EVM_PHY_ID		"davinci_mdio-0:01"
/*
 * A MAX-II CPLD is used क्रम various board control functions.
 */
#घोषणा CPLD_OFFSET(a13a8,a2a1)		(((a13a8) << 10) + ((a2a1) << 3))

#घोषणा CPLD_VERSION	CPLD_OFFSET(0,0)	/* r/o */
#घोषणा CPLD_TEST	CPLD_OFFSET(0,1)
#घोषणा CPLD_LEDS	CPLD_OFFSET(0,2)
#घोषणा CPLD_MUX	CPLD_OFFSET(0,3)
#घोषणा CPLD_SWITCH	CPLD_OFFSET(1,0)	/* r/o */
#घोषणा CPLD_POWER	CPLD_OFFSET(1,1)
#घोषणा CPLD_VIDEO	CPLD_OFFSET(1,2)
#घोषणा CPLD_CARDSTAT	CPLD_OFFSET(1,3)	/* r/o */

#घोषणा CPLD_DILC_OUT	CPLD_OFFSET(2,0)
#घोषणा CPLD_DILC_IN	CPLD_OFFSET(2,1)	/* r/o */

#घोषणा CPLD_IMG_सूची0	CPLD_OFFSET(2,2)
#घोषणा CPLD_IMG_MUX0	CPLD_OFFSET(2,3)
#घोषणा CPLD_IMG_MUX1	CPLD_OFFSET(3,0)
#घोषणा CPLD_IMG_सूची1	CPLD_OFFSET(3,1)
#घोषणा CPLD_IMG_MUX2	CPLD_OFFSET(3,2)
#घोषणा CPLD_IMG_MUX3	CPLD_OFFSET(3,3)
#घोषणा CPLD_IMG_सूची2	CPLD_OFFSET(4,0)
#घोषणा CPLD_IMG_MUX4	CPLD_OFFSET(4,1)
#घोषणा CPLD_IMG_MUX5	CPLD_OFFSET(4,2)

#घोषणा CPLD_RESETS	CPLD_OFFSET(4,3)

#घोषणा CPLD_CCD_सूची1	CPLD_OFFSET(0x3e,0)
#घोषणा CPLD_CCD_IO1	CPLD_OFFSET(0x3e,1)
#घोषणा CPLD_CCD_सूची2	CPLD_OFFSET(0x3e,2)
#घोषणा CPLD_CCD_IO2	CPLD_OFFSET(0x3e,3)
#घोषणा CPLD_CCD_सूची3	CPLD_OFFSET(0x3f,0)
#घोषणा CPLD_CCD_IO3	CPLD_OFFSET(0x3f,1)

अटल व्योम __iomem *cpld;


/* NOTE:  this is geared क्रम the standard config, with a socketed
 * 2 GByte Micron न_अंकD (MT29F16G08FAA) using 128KB sectors.  If you
 * swap chips with a dअगरferent block size, partitioning will
 * need to be changed. This न_अंकD chip MT29F16G08FAA is the शेष
 * न_अंकD shipped with the Spectrum Digital DM365 EVM
 */
#घोषणा न_अंकD_BLOCK_SIZE		SZ_128K

अटल काष्ठा mtd_partition davinci_nand_partitions[] = अणु
	अणु
		/* UBL (a few copies) plus U-Boot */
		.name		= "bootloader",
		.offset		= 0,
		.size		= 30 * न_अंकD_BLOCK_SIZE,
		.mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण, अणु
		/* U-Boot environment */
		.name		= "params",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 2 * न_अंकD_BLOCK_SIZE,
		.mask_flags	= 0,
	पूर्ण, अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_4M,
		.mask_flags	= 0,
	पूर्ण, अणु
		.name		= "filesystem1",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_512M,
		.mask_flags	= 0,
	पूर्ण, अणु
		.name		= "filesystem2",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0,
	पूर्ण
	/* two blocks with bad block table (and mirror) at the end */
पूर्ण;

अटल काष्ठा davinci_nand_pdata davinci_nand_data = अणु
	.core_chipsel		= 0,
	.mask_chipsel		= BIT(14),
	.parts			= davinci_nand_partitions,
	.nr_parts		= ARRAY_SIZE(davinci_nand_partitions),
	.engine_type		= न_अंकD_ECC_ENGINE_TYPE_ON_HOST,
	.bbt_options		= न_अंकD_BBT_USE_FLASH,
	.ecc_bits		= 4,
पूर्ण;

अटल काष्ठा resource davinci_nand_resources[] = अणु
	अणु
		.start		= DM365_ASYNC_EMIF_DATA_CE0_BASE,
		.end		= DM365_ASYNC_EMIF_DATA_CE0_BASE + SZ_32M - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण, अणु
		.start		= DM365_ASYNC_EMIF_CONTROL_BASE,
		.end		= DM365_ASYNC_EMIF_CONTROL_BASE + SZ_4K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_aemअगर_devices[] = अणु
	अणु
		.name		= "davinci_nand",
		.id		= 0,
		.num_resources	= ARRAY_SIZE(davinci_nand_resources),
		.resource	= davinci_nand_resources,
		.dev		= अणु
			.platक्रमm_data	= &davinci_nand_data,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा resource davinci_aemअगर_resources[] = अणु
	अणु
		.start		= DM365_ASYNC_EMIF_CONTROL_BASE,
		.end		= DM365_ASYNC_EMIF_CONTROL_BASE + SZ_4K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा aemअगर_abus_data da850_evm_aemअगर_abus_data[] = अणु
	अणु
		.cs		= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा aemअगर_platक्रमm_data davinci_aemअगर_pdata = अणु
	.abus_data		= da850_evm_aemअगर_abus_data,
	.num_abus_data		= ARRAY_SIZE(da850_evm_aemअगर_abus_data),
	.sub_devices		= davinci_aemअगर_devices,
	.num_sub_devices	= ARRAY_SIZE(davinci_aemअगर_devices),
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_aemअगर_device = अणु
	.name			= "ti-aemif",
	.id			= -1,
	.dev = अणु
		.platक्रमm_data	= &davinci_aemअगर_pdata,
	पूर्ण,
	.resource		= davinci_aemअगर_resources,
	.num_resources		= ARRAY_SIZE(davinci_aemअगर_resources),
पूर्ण;

अटल काष्ठा nvmem_cell_info davinci_nvmem_cells[] = अणु
	अणु
		.name		= "macaddr",
		.offset		= 0x7f00,
		.bytes		= ETH_ALEN,
	पूर्ण
पूर्ण;

अटल काष्ठा nvmem_cell_table davinci_nvmem_cell_table = अणु
	.nvmem_name	= "1-00500",
	.cells		= davinci_nvmem_cells,
	.ncells		= ARRAY_SIZE(davinci_nvmem_cells),
पूर्ण;

अटल काष्ठा nvmem_cell_lookup davinci_nvmem_cell_lookup = अणु
	.nvmem_name	= "1-00500",
	.cell_name	= "macaddr",
	.dev_id		= "davinci_emac.1",
	.con_id		= "mac-address",
पूर्ण;

अटल स्थिर काष्ठा property_entry eeprom_properties[] = अणु
	PROPERTY_ENTRY_U32("pagesize", 64),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node eeprom_node = अणु
	.properties = eeprom_properties,
पूर्ण;

अटल काष्ठा i2c_board_info i2c_info[] = अणु
	अणु
		I2C_BOARD_INFO("24c256", 0x50),
		.swnode = &eeprom_node,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("tlv320aic3x", 0x18),
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_i2c_platक्रमm_data i2c_pdata = अणु
	.bus_freq	= 400	/* kHz */,
	.bus_delay	= 0	/* usec */,
पूर्ण;

/* Fixed regulator support */
अटल काष्ठा regulator_consumer_supply fixed_supplies_3_3v[] = अणु
	/* Baseboard 3.3V: 5V -> TPS767D301 -> 3.3V */
	REGULATOR_SUPPLY("AVDD", "1-0018"),
	REGULATOR_SUPPLY("DRVDD", "1-0018"),
	REGULATOR_SUPPLY("IOVDD", "1-0018"),
पूर्ण;

अटल काष्ठा regulator_consumer_supply fixed_supplies_1_8v[] = अणु
	/* Baseboard 1.8V: 5V -> TPS767D301 -> 1.8V */
	REGULATOR_SUPPLY("DVDD", "1-0018"),
पूर्ण;

अटल पूर्णांक dm365evm_keyscan_enable(काष्ठा device *dev)
अणु
	वापस davinci_cfg_reg(DM365_KEYSCAN);
पूर्ण

अटल अचिन्हित लघु dm365evm_keymap[] = अणु
	KEY_KP2,
	KEY_LEFT,
	KEY_EXIT,
	KEY_DOWN,
	KEY_ENTER,
	KEY_UP,
	KEY_KP1,
	KEY_RIGHT,
	KEY_MENU,
	KEY_RECORD,
	KEY_REWIND,
	KEY_KPMINUS,
	KEY_STOP,
	KEY_FASTFORWARD,
	KEY_KPPLUS,
	KEY_PLAYPAUSE,
	0
पूर्ण;

अटल काष्ठा davinci_ks_platक्रमm_data dm365evm_ks_data = अणु
	.device_enable	= dm365evm_keyscan_enable,
	.keymap		= dm365evm_keymap,
	.keymapsize	= ARRAY_SIZE(dm365evm_keymap),
	.rep		= 1,
	/* Scan period = strobe + पूर्णांकerval */
	.strobe		= 0x5,
	.पूर्णांकerval	= 0x2,
	.matrix_type	= DAVINCI_KEYSCAN_MATRIX_4X4,
पूर्ण;

अटल पूर्णांक cpld_mmc_get_cd(पूर्णांक module)
अणु
	अगर (!cpld)
		वापस -ENXIO;

	/* low == card present */
	वापस !(__raw_पढ़ोb(cpld + CPLD_CARDSTAT) & BIT(module ? 4 : 0));
पूर्ण

अटल पूर्णांक cpld_mmc_get_ro(पूर्णांक module)
अणु
	अगर (!cpld)
		वापस -ENXIO;

	/* high == card's ग_लिखो protect चयन active */
	वापस !!(__raw_पढ़ोb(cpld + CPLD_CARDSTAT) & BIT(module ? 5 : 1));
पूर्ण

अटल काष्ठा davinci_mmc_config dm365evm_mmc_config = अणु
	.get_cd		= cpld_mmc_get_cd,
	.get_ro		= cpld_mmc_get_ro,
	.wires		= 4,
	.max_freq	= 50000000,
	.caps		= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED,
पूर्ण;

अटल व्योम dm365evm_emac_configure(व्योम)
अणु
	/*
	 * EMAC pins are multiplexed with GPIO and UART
	 * Further details are available at the DM365 ARM
	 * Subप्रणाली Users Guide(sprufg5.pdf) pages 125 - 127
	 */
	davinci_cfg_reg(DM365_EMAC_TX_EN);
	davinci_cfg_reg(DM365_EMAC_TX_CLK);
	davinci_cfg_reg(DM365_EMAC_COL);
	davinci_cfg_reg(DM365_EMAC_TXD3);
	davinci_cfg_reg(DM365_EMAC_TXD2);
	davinci_cfg_reg(DM365_EMAC_TXD1);
	davinci_cfg_reg(DM365_EMAC_TXD0);
	davinci_cfg_reg(DM365_EMAC_RXD3);
	davinci_cfg_reg(DM365_EMAC_RXD2);
	davinci_cfg_reg(DM365_EMAC_RXD1);
	davinci_cfg_reg(DM365_EMAC_RXD0);
	davinci_cfg_reg(DM365_EMAC_RX_CLK);
	davinci_cfg_reg(DM365_EMAC_RX_DV);
	davinci_cfg_reg(DM365_EMAC_RX_ER);
	davinci_cfg_reg(DM365_EMAC_CRS);
	davinci_cfg_reg(DM365_EMAC_MDIO);
	davinci_cfg_reg(DM365_EMAC_MDCLK);

	/*
	 * EMAC पूर्णांकerrupts are multiplexed with GPIO पूर्णांकerrupts
	 * Details are available at the DM365 ARM
	 * Subप्रणाली Users Guide(sprufg5.pdf) pages 133 - 134
	 */
	davinci_cfg_reg(DM365_INT_EMAC_RXTHRESH);
	davinci_cfg_reg(DM365_INT_EMAC_RXPULSE);
	davinci_cfg_reg(DM365_INT_EMAC_TXPULSE);
	davinci_cfg_reg(DM365_INT_EMAC_MISCPULSE);
पूर्ण

अटल व्योम dm365evm_mmc_configure(व्योम)
अणु
	/*
	 * MMC/SD pins are multiplexed with GPIO and EMIF
	 * Further details are available at the DM365 ARM
	 * Subप्रणाली Users Guide(sprufg5.pdf) pages 118, 128 - 131
	 */
	davinci_cfg_reg(DM365_SD1_CLK);
	davinci_cfg_reg(DM365_SD1_CMD);
	davinci_cfg_reg(DM365_SD1_DATA3);
	davinci_cfg_reg(DM365_SD1_DATA2);
	davinci_cfg_reg(DM365_SD1_DATA1);
	davinci_cfg_reg(DM365_SD1_DATA0);
पूर्ण

अटल काष्ठा tvp514x_platक्रमm_data tvp5146_pdata = अणु
	.clk_polarity = 0,
	.hs_polarity = 1,
	.vs_polarity = 1
पूर्ण;

#घोषणा TVP514X_STD_ALL        (V4L2_STD_NTSC | V4L2_STD_PAL)
/* Inमाला_दो available at the TVP5146 */
अटल काष्ठा v4l2_input tvp5146_inमाला_दो[] = अणु
	अणु
		.index = 0,
		.name = "Composite",
		.type = V4L2_INPUT_TYPE_CAMERA,
		.std = TVP514X_STD_ALL,
	पूर्ण,
	अणु
		.index = 1,
		.name = "S-Video",
		.type = V4L2_INPUT_TYPE_CAMERA,
		.std = TVP514X_STD_ALL,
	पूर्ण,
पूर्ण;

/*
 * this is the route info क्रम connecting each input to decoder
 * ouput that goes to vpfe. There is a one to one correspondence
 * with tvp5146_inमाला_दो
 */
अटल काष्ठा vpfe_route tvp5146_routes[] = अणु
	अणु
		.input = INPUT_CVBS_VI2B,
		.output = OUTPUT_10BIT_422_EMBEDDED_SYNC,
	पूर्ण,
अणु
		.input = INPUT_SVIDEO_VI2C_VI1C,
		.output = OUTPUT_10BIT_422_EMBEDDED_SYNC,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpfe_subdev_info vpfe_sub_devs[] = अणु
	अणु
		.name = "tvp5146",
		.grp_id = 0,
		.num_inमाला_दो = ARRAY_SIZE(tvp5146_inमाला_दो),
		.inमाला_दो = tvp5146_inमाला_दो,
		.routes = tvp5146_routes,
		.can_route = 1,
		.ccdc_अगर_params = अणु
			.अगर_type = VPFE_BT656,
			.hdpol = VPFE_PINPOL_POSITIVE,
			.vdpol = VPFE_PINPOL_POSITIVE,
		पूर्ण,
		.board_info = अणु
			I2C_BOARD_INFO("tvp5146", 0x5d),
			.platक्रमm_data = &tvp5146_pdata,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpfe_config vpfe_cfg = अणु
	.num_subdevs = ARRAY_SIZE(vpfe_sub_devs),
	.sub_devs = vpfe_sub_devs,
	.i2c_adapter_id = 1,
	.card_name = "DM365 EVM",
	.ccdc = "ISIF",
पूर्ण;

/* venc standards timings */
अटल काष्ठा vpbe_enc_mode_info dm365evm_enc_std_timing[] = अणु
	अणु
		.name		= "ntsc",
		.timings_type	= VPBE_ENC_STD,
		.std_id		= V4L2_STD_NTSC,
		.पूर्णांकerlaced	= 1,
		.xres		= 720,
		.yres		= 480,
		.aspect		= अणु11, 10पूर्ण,
		.fps		= अणु30000, 1001पूर्ण,
		.left_margin	= 0x79,
		.upper_margin	= 0x10,
	पूर्ण,
	अणु
		.name		= "pal",
		.timings_type	= VPBE_ENC_STD,
		.std_id		= V4L2_STD_PAL,
		.पूर्णांकerlaced	= 1,
		.xres		= 720,
		.yres		= 576,
		.aspect		= अणु54, 59पूर्ण,
		.fps		= अणु25, 1पूर्ण,
		.left_margin	= 0x7E,
		.upper_margin	= 0x16,
	पूर्ण,
पूर्ण;

/* venc dv timings */
अटल काष्ठा vpbe_enc_mode_info dm365evm_enc_preset_timing[] = अणु
	अणु
		.name		= "480p59_94",
		.timings_type	= VPBE_ENC_DV_TIMINGS,
		.dv_timings	= V4L2_DV_BT_CEA_720X480P59_94,
		.पूर्णांकerlaced	= 0,
		.xres		= 720,
		.yres		= 480,
		.aspect		= अणु1, 1पूर्ण,
		.fps		= अणु5994, 100पूर्ण,
		.left_margin	= 0x8F,
		.upper_margin	= 0x2D,
	पूर्ण,
	अणु
		.name		= "576p50",
		.timings_type	= VPBE_ENC_DV_TIMINGS,
		.dv_timings	= V4L2_DV_BT_CEA_720X576P50,
		.पूर्णांकerlaced	= 0,
		.xres		= 720,
		.yres		= 576,
		.aspect		= अणु1, 1पूर्ण,
		.fps		= अणु50, 1पूर्ण,
		.left_margin	= 0x8C,
		.upper_margin   = 0x36,
	पूर्ण,
	अणु
		.name		= "720p60",
		.timings_type	= VPBE_ENC_DV_TIMINGS,
		.dv_timings	= V4L2_DV_BT_CEA_1280X720P60,
		.पूर्णांकerlaced	= 0,
		.xres		= 1280,
		.yres		= 720,
		.aspect		= अणु1, 1पूर्ण,
		.fps		= अणु60, 1पूर्ण,
		.left_margin	= 0x117,
		.right_margin	= 70,
		.upper_margin	= 38,
		.lower_margin	= 3,
		.hsync_len	= 80,
		.vsync_len	= 5,
	पूर्ण,
	अणु
		.name		= "1080i60",
		.timings_type	= VPBE_ENC_DV_TIMINGS,
		.dv_timings	= V4L2_DV_BT_CEA_1920X1080I60,
		.पूर्णांकerlaced	= 1,
		.xres		= 1920,
		.yres		= 1080,
		.aspect		= अणु1, 1पूर्ण,
		.fps		= अणु30, 1पूर्ण,
		.left_margin	= 0xc9,
		.right_margin	= 80,
		.upper_margin	= 30,
		.lower_margin	= 3,
		.hsync_len	= 88,
		.vsync_len	= 5,
	पूर्ण,
पूर्ण;

#घोषणा VENC_STD_ALL	(V4L2_STD_NTSC | V4L2_STD_PAL)

/*
 * The outमाला_दो available from VPBE + ecnoders. Keep the
 * the order same as that of encoders. First those from venc followed by that
 * from encoders. Index in the output refers to index on a particular
 * encoder.Driver uses this index to pass it to encoder when it supports more
 * than one output. Application uses index of the array to set an output.
 */
अटल काष्ठा vpbe_output dm365evm_vpbe_outमाला_दो[] = अणु
	अणु
		.output		= अणु
			.index		= 0,
			.name		= "Composite",
			.type		= V4L2_OUTPUT_TYPE_ANALOG,
			.std		= VENC_STD_ALL,
			.capabilities	= V4L2_OUT_CAP_STD,
		पूर्ण,
		.subdev_name	= DM365_VPBE_VENC_SUBDEV_NAME,
		.शेष_mode	= "ntsc",
		.num_modes	= ARRAY_SIZE(dm365evm_enc_std_timing),
		.modes		= dm365evm_enc_std_timing,
		.अगर_params	= MEDIA_BUS_FMT_FIXED,
	पूर्ण,
	अणु
		.output		= अणु
			.index		= 1,
			.name		= "Component",
			.type		= V4L2_OUTPUT_TYPE_ANALOG,
			.capabilities	= V4L2_OUT_CAP_DV_TIMINGS,
		पूर्ण,
		.subdev_name	= DM365_VPBE_VENC_SUBDEV_NAME,
		.शेष_mode	= "480p59_94",
		.num_modes	= ARRAY_SIZE(dm365evm_enc_preset_timing),
		.modes		= dm365evm_enc_preset_timing,
		.अगर_params	= MEDIA_BUS_FMT_FIXED,
	पूर्ण,
पूर्ण;

/*
 * Amplअगरiers on the board
 */
अटल काष्ठा ths7303_platक्रमm_data ths7303_pdata = अणु
	.ch_1 = 3,
	.ch_2 = 3,
	.ch_3 = 3,
पूर्ण;

अटल काष्ठा amp_config_info vpbe_amp = अणु
	.module_name	= "ths7303",
	.is_i2c		= 1,
	.board_info	= अणु
		I2C_BOARD_INFO("ths7303", 0x2c),
		.platक्रमm_data = &ths7303_pdata,
	पूर्ण
पूर्ण;

अटल काष्ठा vpbe_config dm365evm_display_cfg = अणु
	.module_name	= "dm365-vpbe-display",
	.i2c_adapter_id	= 1,
	.amp		= &vpbe_amp,
	.osd		= अणु
		.module_name	= DM365_VPBE_OSD_SUBDEV_NAME,
	पूर्ण,
	.venc		= अणु
		.module_name	= DM365_VPBE_VENC_SUBDEV_NAME,
	पूर्ण,
	.num_outमाला_दो	= ARRAY_SIZE(dm365evm_vpbe_outमाला_दो),
	.outमाला_दो	= dm365evm_vpbe_outमाला_दो,
पूर्ण;

अटल व्योम __init evm_init_i2c(व्योम)
अणु
	davinci_init_i2c(&i2c_pdata);
	i2c_रेजिस्टर_board_info(1, i2c_info, ARRAY_SIZE(i2c_info));
पूर्ण

अटल अंतरभूत पूर्णांक have_leds(व्योम)
अणु
#अगर_घोषित CONFIG_LEDS_CLASS
	वापस 1;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

काष्ठा cpld_led अणु
	काष्ठा led_classdev	cdev;
	u8			mask;
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *trigger;
पूर्ण cpld_leds[] = अणु
	अणु "dm365evm::ds2", पूर्ण,
	अणु "dm365evm::ds3", पूर्ण,
	अणु "dm365evm::ds4", पूर्ण,
	अणु "dm365evm::ds5", पूर्ण,
	अणु "dm365evm::ds6", "nand-disk", पूर्ण,
	अणु "dm365evm::ds7", "mmc1", पूर्ण,
	अणु "dm365evm::ds8", "mmc0", पूर्ण,
	अणु "dm365evm::ds9", "heartbeat", पूर्ण,
पूर्ण;

अटल व्योम cpld_led_set(काष्ठा led_classdev *cdev, क्रमागत led_brightness b)
अणु
	काष्ठा cpld_led *led = container_of(cdev, काष्ठा cpld_led, cdev);
	u8 reg = __raw_पढ़ोb(cpld + CPLD_LEDS);

	अगर (b != LED_OFF)
		reg &= ~led->mask;
	अन्यथा
		reg |= led->mask;
	__raw_ग_लिखोb(reg, cpld + CPLD_LEDS);
पूर्ण

अटल क्रमागत led_brightness cpld_led_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा cpld_led *led = container_of(cdev, काष्ठा cpld_led, cdev);
	u8 reg = __raw_पढ़ोb(cpld + CPLD_LEDS);

	वापस (reg & led->mask) ? LED_OFF : LED_FULL;
पूर्ण

अटल पूर्णांक __init cpld_leds_init(व्योम)
अणु
	पूर्णांक	i;

	अगर (!have_leds() ||  !cpld)
		वापस 0;

	/* setup LEDs */
	__raw_ग_लिखोb(0xff, cpld + CPLD_LEDS);
	क्रम (i = 0; i < ARRAY_SIZE(cpld_leds); i++) अणु
		काष्ठा cpld_led *led;

		led = kzalloc(माप(*led), GFP_KERNEL);
		अगर (!led)
			अवरोध;

		led->cdev.name = cpld_leds[i].name;
		led->cdev.brightness_set = cpld_led_set;
		led->cdev.brightness_get = cpld_led_get;
		led->cdev.शेष_trigger = cpld_leds[i].trigger;
		led->mask = BIT(i);

		अगर (led_classdev_रेजिस्टर(शून्य, &led->cdev) < 0) अणु
			kमुक्त(led);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
/* run after subsys_initcall() क्रम LEDs */
fs_initcall(cpld_leds_init);


अटल व्योम __init evm_init_cpld(व्योम)
अणु
	u8 mux, resets;
	स्थिर अक्षर *label;
	काष्ठा clk *aemअगर_clk;
	पूर्णांक rc;

	/* Make sure we can configure the CPLD through CS1.  Then
	 * leave it on क्रम later access to MMC and LED रेजिस्टरs.
	 */
	aemअगर_clk = clk_get(शून्य, "aemif");
	अगर (IS_ERR(aemअगर_clk))
		वापस;
	clk_prepare_enable(aemअगर_clk);

	अगर (request_mem_region(DM365_ASYNC_EMIF_DATA_CE1_BASE, SECTION_SIZE,
			"cpld") == शून्य)
		जाओ fail;
	cpld = ioremap(DM365_ASYNC_EMIF_DATA_CE1_BASE, SECTION_SIZE);
	अगर (!cpld) अणु
		release_mem_region(DM365_ASYNC_EMIF_DATA_CE1_BASE,
				SECTION_SIZE);
fail:
		pr_err("ERROR: can't map CPLD\n");
		clk_disable_unprepare(aemअगर_clk);
		वापस;
	पूर्ण

	/* External muxing क्रम some संकेतs */
	mux = 0;

	/* Read SW5 to set up न_अंकD + keypad _or_ Oneन_अंकD (sync पढ़ो).
	 * NOTE:  SW4 bus width setting must match!
	 */
	अगर ((__raw_पढ़ोb(cpld + CPLD_SWITCH) & BIT(5)) == 0) अणु
		/* बाह्यal keypad mux */
		mux |= BIT(7);

		rc = platक्रमm_device_रेजिस्टर(&davinci_aemअगर_device);
		अगर (rc)
			pr_warn("%s(): error registering the aemif device: %d\n",
				__func__, rc);
	पूर्ण अन्यथा अणु
		/* no Oneन_अंकD support yet */
	पूर्ण

	/* Leave बाह्यal chips in reset when unused. */
	resets = BIT(3) | BIT(2) | BIT(1) | BIT(0);

	/* Static video input config with SN74CBT16214 1-of-3 mux:
	 *  - port b1 == tvp7002 (mux lowbits == 1 or 6)
	 *  - port b2 == imager (mux lowbits == 2 or 7)
	 *  - port b3 == tvp5146 (mux lowbits == 5)
	 *
	 * Runसमय चयनing could work too, with limitations.
	 */
	अगर (have_imager()) अणु
		label = "HD imager";
		mux |= 2;

		/* बाह्यally mux MMC1/ENET/AIC33 to imager */
		mux |= BIT(6) | BIT(5) | BIT(3);
	पूर्ण अन्यथा अणु
		काष्ठा davinci_soc_info *soc_info = &davinci_soc_info;

		/* we can use MMC1 ... */
		dm365evm_mmc_configure();
		davinci_setup_mmc(1, &dm365evm_mmc_config);

		/* ... and ENET ... */
		dm365evm_emac_configure();
		soc_info->emac_pdata->phy_id = DM365_EVM_PHY_ID;
		resets &= ~BIT(3);

		/* ... and AIC33 */
		resets &= ~BIT(1);

		अगर (have_tvp7002()) अणु
			mux |= 1;
			resets &= ~BIT(2);
			label = "tvp7002 HD";
		पूर्ण अन्यथा अणु
			/* शेष to tvp5146 */
			mux |= 5;
			resets &= ~BIT(0);
			label = "tvp5146 SD";
		पूर्ण
	पूर्ण
	__raw_ग_लिखोb(mux, cpld + CPLD_MUX);
	__raw_ग_लिखोb(resets, cpld + CPLD_RESETS);
	pr_info("EVM: %s video input\n", label);

	/* REVISIT export चयनes: NTSC/PAL (SW5.6), EXTRA1 (SW5.2), etc */
पूर्ण

अटल व्योम __init dm365_evm_map_io(व्योम)
अणु
	dm365_init();
पूर्ण

अटल काष्ठा spi_eeprom at25640 = अणु
	.byte_len	= SZ_64K / 8,
	.name		= "at25640",
	.page_size	= 32,
	.flags		= EE_ADDR2,
पूर्ण;

अटल स्थिर काष्ठा spi_board_info dm365_evm_spi_info[] __initस्थिर = अणु
	अणु
		.modalias	= "at25",
		.platक्रमm_data	= &at25640,
		.max_speed_hz	= 10 * 1000 * 1000,
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_0,
	पूर्ण,
पूर्ण;

अटल __init व्योम dm365_evm_init(व्योम)
अणु
	पूर्णांक ret;

	dm365_रेजिस्टर_घड़ीs();

	ret = dm365_gpio_रेजिस्टर();
	अगर (ret)
		pr_warn("%s: GPIO init failed: %d\n", __func__, ret);

	regulator_रेजिस्टर_always_on(0, "fixed-dummy", fixed_supplies_1_8v,
				     ARRAY_SIZE(fixed_supplies_1_8v), 1800000);
	regulator_रेजिस्टर_always_on(1, "fixed-dummy", fixed_supplies_3_3v,
				     ARRAY_SIZE(fixed_supplies_3_3v), 3300000);

	nvmem_add_cell_table(&davinci_nvmem_cell_table);
	nvmem_add_cell_lookups(&davinci_nvmem_cell_lookup, 1);

	evm_init_i2c();
	davinci_serial_init(dm365_serial_device);

	dm365evm_emac_configure();
	dm365evm_mmc_configure();

	davinci_setup_mmc(0, &dm365evm_mmc_config);

	dm365_init_video(&vpfe_cfg, &dm365evm_display_cfg);

	/* maybe setup mmc1/etc ... _after_ mmc0 */
	evm_init_cpld();

#अगर_घोषित CONFIG_SND_SOC_DM365_AIC3X_CODEC
	dm365_init_asp();
#या_अगर defined(CONFIG_SND_SOC_DM365_VOICE_CODEC)
	dm365_init_vc();
#पूर्ण_अगर
	dm365_init_rtc();
	dm365_init_ks(&dm365evm_ks_data);

	dm365_init_spi0(BIT(0), dm365_evm_spi_info,
			ARRAY_SIZE(dm365_evm_spi_info));
पूर्ण

MACHINE_START(DAVINCI_DM365_EVM, "DaVinci DM365 EVM")
	.atag_offset	= 0x100,
	.map_io		= dm365_evm_map_io,
	.init_irq	= dm365_init_irq,
	.init_समय	= dm365_init_समय,
	.init_machine	= dm365_evm_init,
	.init_late	= davinci_init_late,
	.dma_zone_size	= SZ_128M,
MACHINE_END

