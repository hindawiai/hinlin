<शैली गुरु>
/*
 * DM355 leopard board support
 *
 * Based on board-dm355-evm.c
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
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
#समावेश <linux/clk.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/eeprom.h>
#समावेश <linux/platक्रमm_data/i2c-davinci.h>
#समावेश <linux/platक्रमm_data/mmc-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci.h>
#समावेश <linux/platक्रमm_data/usb-davinci.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश <mach/common.h>
#समावेश <mach/serial.h>

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
	.ecc_placement		= न_अंकD_ECC_PLACEMENT_INTERLEAVED,
	.ecc_bits		= 4,
	.bbt_options		= न_अंकD_BBT_USE_FLASH,
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

अटल काष्ठा davinci_i2c_platक्रमm_data i2c_pdata = अणु
	.bus_freq	= 400	/* kHz */,
	.bus_delay	= 0	/* usec */,
पूर्ण;

अटल पूर्णांक leopard_mmc_gpio = -EINVAL;

अटल व्योम dm355leopard_mmcsd_gpios(अचिन्हित gpio)
अणु
	gpio_request(gpio + 0, "mmc0_ro");
	gpio_request(gpio + 1, "mmc0_cd");
	gpio_request(gpio + 2, "mmc1_ro");
	gpio_request(gpio + 3, "mmc1_cd");

	/* we "know" these are input-only so we करोn't
	 * need to call gpio_direction_input()
	 */

	leopard_mmc_gpio = gpio;
पूर्ण

अटल काष्ठा i2c_board_info dm355leopard_i2c_info[] = अणु
	अणु I2C_BOARD_INFO("dm355leopard_msp", 0x25),
		.platक्रमm_data = dm355leopard_mmcsd_gpios,
		/* plus irq */ पूर्ण,
	/* अणु I2C_BOARD_INFO("tlv320aic3x", 0x1b), पूर्ण, */
	/* अणु I2C_BOARD_INFO("tvp5146", 0x5d), पूर्ण, */
पूर्ण;

अटल व्योम __init leopard_init_i2c(व्योम)
अणु
	davinci_init_i2c(&i2c_pdata);

	gpio_request(5, "dm355leopard_msp");
	gpio_direction_input(5);
	dm355leopard_i2c_info[0].irq = gpio_to_irq(5);

	i2c_रेजिस्टर_board_info(1, dm355leopard_i2c_info,
			ARRAY_SIZE(dm355leopard_i2c_info));
पूर्ण

अटल काष्ठा resource dm355leopard_dm9000_rsrc[] = अणु
	अणु
		/* addr */
		.start	= 0x04000000,
		.end	= 0x04000001,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		/* data */
		.start	= 0x04000016,
		.end	= 0x04000017,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.flags	= IORESOURCE_IRQ
			| IORESOURCE_IRQ_HIGHEDGE /* rising (active high) */,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dm355leopard_dm9000 = अणु
	.name		= "dm9000",
	.id		= -1,
	.resource	= dm355leopard_dm9000_rsrc,
	.num_resources	= ARRAY_SIZE(dm355leopard_dm9000_rsrc),
पूर्ण;

अटल काष्ठा platक्रमm_device *davinci_leopard_devices[] __initdata = अणु
	&dm355leopard_dm9000,
	&davinci_nand_device,
पूर्ण;

अटल व्योम __init dm355_leopard_map_io(व्योम)
अणु
	dm355_init();
पूर्ण

अटल पूर्णांक dm355leopard_mmc_get_cd(पूर्णांक module)
अणु
	अगर (!gpio_is_valid(leopard_mmc_gpio))
		वापस -ENXIO;
	/* low == card present */
	वापस !gpio_get_value_cansleep(leopard_mmc_gpio + 2 * module + 1);
पूर्ण

अटल पूर्णांक dm355leopard_mmc_get_ro(पूर्णांक module)
अणु
	अगर (!gpio_is_valid(leopard_mmc_gpio))
		वापस -ENXIO;
	/* high == card's ग_लिखो protect चयन active */
	वापस gpio_get_value_cansleep(leopard_mmc_gpio + 2 * module + 0);
पूर्ण

अटल काष्ठा davinci_mmc_config dm355leopard_mmc_config = अणु
	.get_cd		= dm355leopard_mmc_get_cd,
	.get_ro		= dm355leopard_mmc_get_ro,
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

अटल स्थिर काष्ठा spi_board_info dm355_leopard_spi_info[] __initस्थिर = अणु
	अणु
		.modalias	= "at25",
		.platक्रमm_data	= &at25640a,
		.max_speed_hz	= 10 * 1000 * 1000,	/* at 3v3 */
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_0,
	पूर्ण,
पूर्ण;

अटल __init व्योम dm355_leopard_init(व्योम)
अणु
	काष्ठा clk *aemअगर;
	पूर्णांक ret;

	dm355_रेजिस्टर_घड़ीs();

	ret = dm355_gpio_रेजिस्टर();
	अगर (ret)
		pr_warn("%s: GPIO init failed: %d\n", __func__, ret);

	gpio_request(9, "dm9000");
	gpio_direction_input(9);
	dm355leopard_dm9000_rsrc[2].start = gpio_to_irq(9);

	aemअगर = clk_get(&dm355leopard_dm9000.dev, "aemif");
	अगर (!WARN(IS_ERR(aemअगर), "unable to get AEMIF clock\n"))
		clk_prepare_enable(aemअगर);

	platक्रमm_add_devices(davinci_leopard_devices,
			     ARRAY_SIZE(davinci_leopard_devices));
	leopard_init_i2c();
	davinci_serial_init(dm355_serial_device);

	/* NOTE:  न_अंकD flash timings set by the UBL are slower than
	 * needed by MT29F16G08FAA chips ... EMIF.A1CR is 0x40400204
	 * but could be 0x0400008c क्रम about 25% faster page पढ़ोs.
	 */

	gpio_request(2, "usb_id_toggle");
	gpio_direction_output(2, USB_ID_VALUE);
	/* irlml6401 चयनes over 1A in under 8 msec */
	davinci_setup_usb(1000, 8);

	davinci_setup_mmc(0, &dm355leopard_mmc_config);
	davinci_setup_mmc(1, &dm355leopard_mmc_config);

	dm355_init_spi0(BIT(0), dm355_leopard_spi_info,
			ARRAY_SIZE(dm355_leopard_spi_info));
पूर्ण

MACHINE_START(DM355_LEOPARD, "DaVinci DM355 leopard")
	.atag_offset  = 0x100,
	.map_io	      = dm355_leopard_map_io,
	.init_irq     = dm355_init_irq,
	.init_समय	= dm355_init_समय,
	.init_machine = dm355_leopard_init,
	.init_late	= davinci_init_late,
	.dma_zone_size	= SZ_128M,
MACHINE_END
