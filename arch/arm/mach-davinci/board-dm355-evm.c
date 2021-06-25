<शैली गुरु>
/*
 * TI DaVinci EVM board support
 *
 * Author: Kevin Hilman, Deep Root Systems, LLC
 *
 * 2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/clk.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/videodev2.h>
#समावेश <media/i2c/tvp514x.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/eeprom.h>
#समावेश <linux/platक्रमm_data/gpio-davinci.h>
#समावेश <linux/platक्रमm_data/i2c-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci.h>
#समावेश <linux/platक्रमm_data/mmc-davinci.h>
#समावेश <linux/platक्रमm_data/usb-davinci.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश <mach/serial.h>
#समावेश <mach/common.h>

#समावेश "davinci.h"

/* NOTE:  this is geared क्रम the standard config, with a socketed
 * 2 GByte Micron न_अंकD (MT29F16G08FAA) using 128KB sectors.  If you
 * swap chips, maybe with a dअगरferent block size, partitioning may
 * need to be changed.
 */
#घोषणा न_अंकD_BLOCK_SIZE		SZ_128K

अटल काष्ठा mtd_partition davinci_nand_partitions[] = अणु
	अणु
		/* UBL (a few copies) plus U-Boot */
		.name		= "bootloader",
		.offset		= 0,
		.size		= 15 * न_अंकD_BLOCK_SIZE,
		.mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण, अणु
		/* U-Boot environment */
		.name		= "params",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 1 * न_अंकD_BLOCK_SIZE,
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
		.start		= DM355_ASYNC_EMIF_DATA_CE0_BASE,
		.end		= DM355_ASYNC_EMIF_DATA_CE0_BASE + SZ_32M - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण, अणु
		.start		= DM355_ASYNC_EMIF_CONTROL_BASE,
		.end		= DM355_ASYNC_EMIF_CONTROL_BASE + SZ_4K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_nand_device = अणु
	.name			= "davinci_nand",
	.id			= 0,

	.num_resources		= ARRAY_SIZE(davinci_nand_resources),
	.resource		= davinci_nand_resources,

	.dev			= अणु
		.platक्रमm_data	= &davinci_nand_data,
	पूर्ण,
पूर्ण;

#घोषणा DM355_I2C_SDA_PIN	GPIO_TO_PIN(0, 15)
#घोषणा DM355_I2C_SCL_PIN	GPIO_TO_PIN(0, 14)

अटल काष्ठा gpiod_lookup_table i2c_recovery_gpiod_table = अणु
	.dev_id = "i2c_davinci.1",
	.table = अणु
		GPIO_LOOKUP("davinci_gpio", DM355_I2C_SDA_PIN, "sda",
			    GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP("davinci_gpio", DM355_I2C_SCL_PIN, "scl",
			    GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_i2c_platक्रमm_data i2c_pdata = अणु
	.bus_freq	= 400	/* kHz */,
	.bus_delay	= 0	/* usec */,
	.gpio_recovery	= true,
पूर्ण;

अटल पूर्णांक dm355evm_mmc_gpios = -EINVAL;

अटल व्योम dm355evm_mmcsd_gpios(अचिन्हित gpio)
अणु
	gpio_request(gpio + 0, "mmc0_ro");
	gpio_request(gpio + 1, "mmc0_cd");
	gpio_request(gpio + 2, "mmc1_ro");
	gpio_request(gpio + 3, "mmc1_cd");

	/* we "know" these are input-only so we करोn't
	 * need to call gpio_direction_input()
	 */

	dm355evm_mmc_gpios = gpio;
पूर्ण

अटल काष्ठा i2c_board_info dm355evm_i2c_info[] = अणु
	अणु	I2C_BOARD_INFO("dm355evm_msp", 0x25),
		.platक्रमm_data = dm355evm_mmcsd_gpios,
	पूर्ण,
	/* अणु plus irq  पूर्ण, */
	अणु I2C_BOARD_INFO("tlv320aic33", 0x1b), पूर्ण,
पूर्ण;

अटल व्योम __init evm_init_i2c(व्योम)
अणु
	gpiod_add_lookup_table(&i2c_recovery_gpiod_table);
	davinci_init_i2c(&i2c_pdata);

	gpio_request(5, "dm355evm_msp");
	gpio_direction_input(5);
	dm355evm_i2c_info[0].irq = gpio_to_irq(5);

	i2c_रेजिस्टर_board_info(1, dm355evm_i2c_info,
			ARRAY_SIZE(dm355evm_i2c_info));
पूर्ण

अटल काष्ठा resource dm355evm_dm9000_rsrc[] = अणु
	अणु
		/* addr */
		.start	= 0x04014000,
		.end	= 0x04014001,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		/* data */
		.start	= 0x04014002,
		.end	= 0x04014003,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.flags	= IORESOURCE_IRQ
			| IORESOURCE_IRQ_HIGHEDGE /* rising (active high) */,
	पूर्ण,
पूर्ण;

अटल काष्ठा dm9000_plat_data dm335evm_dm9000_platdata;

अटल काष्ठा platक्रमm_device dm355evm_dm9000 = अणु
	.name		= "dm9000",
	.id		= -1,
	.resource	= dm355evm_dm9000_rsrc,
	.num_resources	= ARRAY_SIZE(dm355evm_dm9000_rsrc),
	.dev		= अणु
		.platक्रमm_data = &dm335evm_dm9000_platdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा tvp514x_platक्रमm_data tvp5146_pdata = अणु
	.clk_polarity = 0,
	.hs_polarity = 1,
	.vs_polarity = 1
पूर्ण;

#घोषणा TVP514X_STD_ALL	(V4L2_STD_NTSC | V4L2_STD_PAL)
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
	पूर्ण
पूर्ण;

अटल काष्ठा vpfe_config vpfe_cfg = अणु
	.num_subdevs = ARRAY_SIZE(vpfe_sub_devs),
	.i2c_adapter_id = 1,
	.sub_devs = vpfe_sub_devs,
	.card_name = "DM355 EVM",
	.ccdc = "DM355 CCDC",
पूर्ण;

/* venc standards timings */
अटल काष्ठा vpbe_enc_mode_info dm355evm_enc_preset_timing[] = अणु
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
		.upper_margin	= 0x16
	पूर्ण,
पूर्ण;

#घोषणा VENC_STD_ALL	(V4L2_STD_NTSC | V4L2_STD_PAL)

/*
 * The outमाला_दो available from VPBE + ecnoders. Keep the
 * the order same as that of encoders. First those from venc followed by that
 * from encoders. Index in the output refers to index on a particular encoder.
 * Driver uses this index to pass it to encoder when it supports more than
 * one output. Application uses index of the array to set an output.
 */
अटल काष्ठा vpbe_output dm355evm_vpbe_outमाला_दो[] = अणु
	अणु
		.output		= अणु
			.index		= 0,
			.name		= "Composite",
			.type		= V4L2_OUTPUT_TYPE_ANALOG,
			.std		= VENC_STD_ALL,
			.capabilities	= V4L2_OUT_CAP_STD,
		पूर्ण,
		.subdev_name	= DM355_VPBE_VENC_SUBDEV_NAME,
		.शेष_mode	= "ntsc",
		.num_modes	= ARRAY_SIZE(dm355evm_enc_preset_timing),
		.modes		= dm355evm_enc_preset_timing,
		.अगर_params	= MEDIA_BUS_FMT_FIXED,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpbe_config dm355evm_display_cfg = अणु
	.module_name	= "dm355-vpbe-display",
	.i2c_adapter_id	= 1,
	.osd		= अणु
		.module_name	= DM355_VPBE_OSD_SUBDEV_NAME,
	पूर्ण,
	.venc		= अणु
		.module_name	= DM355_VPBE_VENC_SUBDEV_NAME,
	पूर्ण,
	.num_outमाला_दो	= ARRAY_SIZE(dm355evm_vpbe_outमाला_दो),
	.outमाला_दो	= dm355evm_vpbe_outमाला_दो,
पूर्ण;

अटल काष्ठा platक्रमm_device *davinci_evm_devices[] __initdata = अणु
	&dm355evm_dm9000,
	&davinci_nand_device,
पूर्ण;

अटल व्योम __init dm355_evm_map_io(व्योम)
अणु
	dm355_init();
पूर्ण

अटल पूर्णांक dm355evm_mmc_get_cd(पूर्णांक module)
अणु
	अगर (!gpio_is_valid(dm355evm_mmc_gpios))
		वापस -ENXIO;
	/* low == card present */
	वापस !gpio_get_value_cansleep(dm355evm_mmc_gpios + 2 * module + 1);
पूर्ण

अटल पूर्णांक dm355evm_mmc_get_ro(पूर्णांक module)
अणु
	अगर (!gpio_is_valid(dm355evm_mmc_gpios))
		वापस -ENXIO;
	/* high == card's ग_लिखो protect चयन active */
	वापस gpio_get_value_cansleep(dm355evm_mmc_gpios + 2 * module + 0);
पूर्ण

अटल काष्ठा davinci_mmc_config dm355evm_mmc_config = अणु
	.get_cd		= dm355evm_mmc_get_cd,
	.get_ro		= dm355evm_mmc_get_ro,
	.wires		= 4,
	.max_freq       = 50000000,
	.caps           = MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED,
पूर्ण;

/* Don't connect anything to J10 unless you're only using USB host
 * mode *and* have to करो so with some kind of gender-bender.  If
 * you have proper Mini-B or Mini-A cables (or Mini-A adapters)
 * the ID pin won't need any help.
 */
#घोषणा USB_ID_VALUE	1	/* ID pulled low */

अटल काष्ठा spi_eeprom at25640a = अणु
	.byte_len	= SZ_64K / 8,
	.name		= "at25640a",
	.page_size	= 32,
	.flags		= EE_ADDR2,
पूर्ण;

अटल स्थिर काष्ठा spi_board_info dm355_evm_spi_info[] __initस्थिर = अणु
	अणु
		.modalias	= "at25",
		.platक्रमm_data	= &at25640a,
		.max_speed_hz	= 10 * 1000 * 1000,	/* at 3v3 */
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_0,
	पूर्ण,
पूर्ण;

अटल __init व्योम dm355_evm_init(व्योम)
अणु
	काष्ठा clk *aemअगर;
	पूर्णांक ret;

	dm355_रेजिस्टर_घड़ीs();

	ret = dm355_gpio_रेजिस्टर();
	अगर (ret)
		pr_warn("%s: GPIO init failed: %d\n", __func__, ret);

	gpio_request(1, "dm9000");
	gpio_direction_input(1);
	dm355evm_dm9000_rsrc[2].start = gpio_to_irq(1);

	aemअगर = clk_get(&dm355evm_dm9000.dev, "aemif");
	अगर (!WARN(IS_ERR(aemअगर), "unable to get AEMIF clock\n"))
		clk_prepare_enable(aemअगर);

	platक्रमm_add_devices(davinci_evm_devices,
			     ARRAY_SIZE(davinci_evm_devices));
	evm_init_i2c();
	davinci_serial_init(dm355_serial_device);

	/* NOTE:  न_अंकD flash timings set by the UBL are slower than
	 * needed by MT29F16G08FAA chips ... EMIF.A1CR is 0x40400204
	 * but could be 0x0400008c क्रम about 25% faster page पढ़ोs.
	 */

	gpio_request(2, "usb_id_toggle");
	gpio_direction_output(2, USB_ID_VALUE);
	/* irlml6401 चयनes over 1A in under 8 msec */
	davinci_setup_usb(1000, 8);

	davinci_setup_mmc(0, &dm355evm_mmc_config);
	davinci_setup_mmc(1, &dm355evm_mmc_config);

	dm355_init_video(&vpfe_cfg, &dm355evm_display_cfg);

	dm355_init_spi0(BIT(0), dm355_evm_spi_info,
			ARRAY_SIZE(dm355_evm_spi_info));

	/* DM335 EVM uses ASP1; line-out is a stereo mini-jack */
	dm355_init_asp1(ASP1_TX_EVT_EN | ASP1_RX_EVT_EN);
पूर्ण

MACHINE_START(DAVINCI_DM355_EVM, "DaVinci DM355 EVM")
	.atag_offset  = 0x100,
	.map_io	      = dm355_evm_map_io,
	.init_irq     = dm355_init_irq,
	.init_समय	= dm355_init_समय,
	.init_machine = dm355_evm_init,
	.init_late	= davinci_init_late,
	.dma_zone_size	= SZ_128M,
MACHINE_END
