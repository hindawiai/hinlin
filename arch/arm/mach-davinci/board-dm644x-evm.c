<शैली गुरु>
/*
 * TI DaVinci EVM board support
 *
 * Author: Kevin Hilman, MontaVista Software, Inc. <source@mvista.com>
 *
 * 2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/pcf857x.h>
#समावेश <linux/platक्रमm_data/gpio-davinci.h>
#समावेश <linux/property.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/phy.h>
#समावेश <linux/clk.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <linux/export.h>
#समावेश <linux/leds.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>

#समावेश <media/i2c/tvp514x.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश <mach/common.h>
#समावेश <mach/mux.h>
#समावेश <mach/serial.h>

#समावेश <linux/platक्रमm_data/i2c-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci.h>
#समावेश <linux/platक्रमm_data/mmc-davinci.h>
#समावेश <linux/platक्रमm_data/usb-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci-aemअगर.h>
#समावेश <linux/platक्रमm_data/ti-aemअगर.h>

#समावेश "davinci.h"
#समावेश "irqs.h"

#घोषणा DM644X_EVM_PHY_ID		"davinci_mdio-0:01"
#घोषणा LXT971_PHY_ID	(0x001378e2)
#घोषणा LXT971_PHY_MASK	(0xfffffff0)

अटल काष्ठा mtd_partition davinci_evm_norflash_partitions[] = अणु
	/* bootloader (UBL, U-Boot, etc) in first 5 sectors */
	अणु
		.name		= "bootloader",
		.offset		= 0,
		.size		= 5 * SZ_64K,
		.mask_flags	= MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	/* bootloader params in the next 1 sectors */
	अणु
		.name		= "params",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_64K,
		.mask_flags	= 0,
	पूर्ण,
	/* kernel */
	अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_2M,
		.mask_flags	= 0
	पूर्ण,
	/* file प्रणाली */
	अणु
		.name		= "filesystem",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data davinci_evm_norflash_data = अणु
	.width		= 2,
	.parts		= davinci_evm_norflash_partitions,
	.nr_parts	= ARRAY_SIZE(davinci_evm_norflash_partitions),
पूर्ण;

/* NOTE: CFI probe will correctly detect flash part as 32M, but EMIF
 * limits addresses to 16M, so using addresses past 16M will wrap */
अटल काष्ठा resource davinci_evm_norflash_resource = अणु
	.start		= DM644X_ASYNC_EMIF_DATA_CE0_BASE,
	.end		= DM644X_ASYNC_EMIF_DATA_CE0_BASE + SZ_16M - 1,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_evm_norflash_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &davinci_evm_norflash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &davinci_evm_norflash_resource,
पूर्ण;

/* DM644x EVM includes a 64 MByte small-page न_अंकD flash (16K blocks).
 * It may used instead of the (शेष) NOR chip to boot, using TI's
 * tools to install the secondary boot loader (UBL) and U-Boot.
 */
अटल काष्ठा mtd_partition davinci_evm_nandflash_partition[] = अणु
	/* Bootloader layout depends on whose u-boot is installed, but we
	 * can hide all the details.
	 *  - block 0 क्रम u-boot environment ... in मुख्यline u-boot
	 *  - block 1 क्रम UBL (plus up to four backup copies in blocks 2..5)
	 *  - blocks 6...? क्रम u-boot
	 *  - blocks 16..23 क्रम u-boot environment ... in TI's u-boot
	 */
	अणु
		.name		= "bootloader",
		.offset		= 0,
		.size		= SZ_256K + SZ_128K,
		.mask_flags	= MTD_WRITEABLE,	/* क्रमce पढ़ो-only */
	पूर्ण,
	/* Kernel */
	अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_4M,
		.mask_flags	= 0,
	पूर्ण,
	/* File प्रणाली (older GIT kernels started this on the 5MB mark) */
	अणु
		.name		= "filesystem",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0,
	पूर्ण
	/* A few blocks at end hold a flash BBT ... created by TI's CCS
	 * using flashग_लिखोr_nand.out, but ignored by TI's versions of
	 * Linux and u-boot.  We boot faster by using them.
	 */
पूर्ण;

अटल काष्ठा davinci_aemअगर_timing davinci_evm_nandflash_timing = अणु
	.wsetup		= 20,
	.wstrobe	= 40,
	.whold		= 20,
	.rsetup		= 10,
	.rstrobe	= 40,
	.rhold		= 10,
	.ta		= 40,
पूर्ण;

अटल काष्ठा davinci_nand_pdata davinci_evm_nandflash_data = अणु
	.core_chipsel	= 0,
	.parts		= davinci_evm_nandflash_partition,
	.nr_parts	= ARRAY_SIZE(davinci_evm_nandflash_partition),
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_ON_HOST,
	.ecc_bits	= 1,
	.bbt_options	= न_अंकD_BBT_USE_FLASH,
	.timing		= &davinci_evm_nandflash_timing,
पूर्ण;

अटल काष्ठा resource davinci_evm_nandflash_resource[] = अणु
	अणु
		.start		= DM644X_ASYNC_EMIF_DATA_CE0_BASE,
		.end		= DM644X_ASYNC_EMIF_DATA_CE0_BASE + SZ_16M - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण, अणु
		.start		= DM644X_ASYNC_EMIF_CONTROL_BASE,
		.end		= DM644X_ASYNC_EMIF_CONTROL_BASE + SZ_4K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource davinci_evm_aemअगर_resource[] = अणु
	अणु
		.start		= DM644X_ASYNC_EMIF_CONTROL_BASE,
		.end		= DM644X_ASYNC_EMIF_CONTROL_BASE + SZ_4K - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा aemअगर_abus_data davinci_evm_aemअगर_abus_data[] = अणु
	अणु
		.cs		= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_evm_nandflash_devices[] = अणु
	अणु
		.name		= "davinci_nand",
		.id		= 0,
		.dev		= अणु
			.platक्रमm_data	= &davinci_evm_nandflash_data,
		पूर्ण,
		.num_resources	= ARRAY_SIZE(davinci_evm_nandflash_resource),
		.resource	= davinci_evm_nandflash_resource,
	पूर्ण,
पूर्ण;

अटल काष्ठा aemअगर_platक्रमm_data davinci_evm_aemअगर_pdata = अणु
	.abus_data = davinci_evm_aemअगर_abus_data,
	.num_abus_data = ARRAY_SIZE(davinci_evm_aemअगर_abus_data),
	.sub_devices = davinci_evm_nandflash_devices,
	.num_sub_devices = ARRAY_SIZE(davinci_evm_nandflash_devices),
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_evm_aemअगर_device = अणु
	.name			= "ti-aemif",
	.id			= -1,
	.dev = अणु
		.platक्रमm_data	= &davinci_evm_aemअगर_pdata,
	पूर्ण,
	.resource		= davinci_evm_aemअगर_resource,
	.num_resources		= ARRAY_SIZE(davinci_evm_aemअगर_resource),
पूर्ण;

अटल u64 davinci_fb_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device davinci_fb_device = अणु
	.name		= "davincifb",
	.id		= -1,
	.dev = अणु
		.dma_mask		= &davinci_fb_dma_mask,
		.coherent_dma_mask      = DMA_BIT_MASK(32),
	पूर्ण,
	.num_resources = 0,
पूर्ण;

अटल काष्ठा tvp514x_platक्रमm_data dm644xevm_tvp5146_pdata = अणु
	.clk_polarity = 0,
	.hs_polarity = 1,
	.vs_polarity = 1
पूर्ण;

#घोषणा TVP514X_STD_ALL	(V4L2_STD_NTSC | V4L2_STD_PAL)
/* Inमाला_दो available at the TVP5146 */
अटल काष्ठा v4l2_input dm644xevm_tvp5146_inमाला_दो[] = अणु
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
अटल काष्ठा vpfe_route dm644xevm_tvp5146_routes[] = अणु
	अणु
		.input = INPUT_CVBS_VI2B,
		.output = OUTPUT_10BIT_422_EMBEDDED_SYNC,
	पूर्ण,
	अणु
		.input = INPUT_SVIDEO_VI2C_VI1C,
		.output = OUTPUT_10BIT_422_EMBEDDED_SYNC,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpfe_subdev_info dm644xevm_vpfe_sub_devs[] = अणु
	अणु
		.name = "tvp5146",
		.grp_id = 0,
		.num_inमाला_दो = ARRAY_SIZE(dm644xevm_tvp5146_inमाला_दो),
		.inमाला_दो = dm644xevm_tvp5146_inमाला_दो,
		.routes = dm644xevm_tvp5146_routes,
		.can_route = 1,
		.ccdc_अगर_params = अणु
			.अगर_type = VPFE_BT656,
			.hdpol = VPFE_PINPOL_POSITIVE,
			.vdpol = VPFE_PINPOL_POSITIVE,
		पूर्ण,
		.board_info = अणु
			I2C_BOARD_INFO("tvp5146", 0x5d),
			.platक्रमm_data = &dm644xevm_tvp5146_pdata,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpfe_config dm644xevm_capture_cfg = अणु
	.num_subdevs = ARRAY_SIZE(dm644xevm_vpfe_sub_devs),
	.i2c_adapter_id = 1,
	.sub_devs = dm644xevm_vpfe_sub_devs,
	.card_name = "DM6446 EVM",
	.ccdc = "DM6446 CCDC",
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_dev = अणु
	.name           = "rtc_davinci_evm",
	.id             = -1,
पूर्ण;

/*----------------------------------------------------------------------*/
#अगर_घोषित CONFIG_I2C
/*
 * I2C GPIO expanders
 */

#घोषणा PCF_Uxx_BASE(x)	(DAVINCI_N_GPIO + ((x) * 8))


/* U2 -- LEDs */

अटल काष्ठा gpio_led evm_leds[] = अणु
	अणु .name = "DS8", .active_low = 1,
		.शेष_trigger = "heartbeat", पूर्ण,
	अणु .name = "DS7", .active_low = 1, पूर्ण,
	अणु .name = "DS6", .active_low = 1, पूर्ण,
	अणु .name = "DS5", .active_low = 1, पूर्ण,
	अणु .name = "DS4", .active_low = 1, पूर्ण,
	अणु .name = "DS3", .active_low = 1, पूर्ण,
	अणु .name = "DS2", .active_low = 1,
		.शेष_trigger = "mmc0", पूर्ण,
	अणु .name = "DS1", .active_low = 1,
		.शेष_trigger = "disk-activity", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led_platक्रमm_data evm_led_data = अणु
	.num_leds	= ARRAY_SIZE(evm_leds),
	.leds		= evm_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device *evm_led_dev;

अटल पूर्णांक
evm_led_setup(काष्ठा i2c_client *client, पूर्णांक gpio, अचिन्हित ngpio, व्योम *c)
अणु
	काष्ठा gpio_led *leds = evm_leds;
	पूर्णांक status;

	जबतक (ngpio--) अणु
		leds->gpio = gpio++;
		leds++;
	पूर्ण

	/* what an extremely annoying way to be क्रमced to handle
	 * device unregistration ...
	 */
	evm_led_dev = platक्रमm_device_alloc("leds-gpio", 0);
	platक्रमm_device_add_data(evm_led_dev,
			&evm_led_data, माप evm_led_data);

	evm_led_dev->dev.parent = &client->dev;
	status = platक्रमm_device_add(evm_led_dev);
	अगर (status < 0) अणु
		platक्रमm_device_put(evm_led_dev);
		evm_led_dev = शून्य;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक
evm_led_tearकरोwn(काष्ठा i2c_client *client, पूर्णांक gpio, अचिन्हित ngpio, व्योम *c)
अणु
	अगर (evm_led_dev) अणु
		platक्रमm_device_unरेजिस्टर(evm_led_dev);
		evm_led_dev = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा pcf857x_platक्रमm_data pcf_data_u2 = अणु
	.gpio_base	= PCF_Uxx_BASE(0),
	.setup		= evm_led_setup,
	.tearकरोwn	= evm_led_tearकरोwn,
पूर्ण;


/* U18 - A/V घड़ी generator and user चयन */

अटल पूर्णांक sw_gpio;

अटल sमाप_प्रकार
sw_show(काष्ठा device *d, काष्ठा device_attribute *a, अक्षर *buf)
अणु
	अक्षर *s = gpio_get_value_cansleep(sw_gpio) ? "on\n" : "off\n";

	म_नकल(buf, s);
	वापस म_माप(s);
पूर्ण

अटल DEVICE_ATTR(user_sw, S_IRUGO, sw_show, शून्य);

अटल पूर्णांक
evm_u18_setup(काष्ठा i2c_client *client, पूर्णांक gpio, अचिन्हित ngpio, व्योम *c)
अणु
	पूर्णांक	status;

	/* export dip चयन option */
	sw_gpio = gpio + 7;
	status = gpio_request(sw_gpio, "user_sw");
	अगर (status == 0)
		status = gpio_direction_input(sw_gpio);
	अगर (status == 0)
		status = device_create_file(&client->dev, &dev_attr_user_sw);
	अन्यथा
		gpio_मुक्त(sw_gpio);
	अगर (status != 0)
		sw_gpio = -EINVAL;

	/* audio PLL:  48 kHz (vs 44.1 or 32), single rate (vs द्विगुन) */
	gpio_request(gpio + 3, "pll_fs2");
	gpio_direction_output(gpio + 3, 0);

	gpio_request(gpio + 2, "pll_fs1");
	gpio_direction_output(gpio + 2, 0);

	gpio_request(gpio + 1, "pll_sr");
	gpio_direction_output(gpio + 1, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
evm_u18_tearकरोwn(काष्ठा i2c_client *client, पूर्णांक gpio, अचिन्हित ngpio, व्योम *c)
अणु
	gpio_मुक्त(gpio + 1);
	gpio_मुक्त(gpio + 2);
	gpio_मुक्त(gpio + 3);

	अगर (sw_gpio > 0) अणु
		device_हटाओ_file(&client->dev, &dev_attr_user_sw);
		gpio_मुक्त(sw_gpio);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा pcf857x_platक्रमm_data pcf_data_u18 = अणु
	.gpio_base	= PCF_Uxx_BASE(1),
	.n_latch	= (1 << 3) | (1 << 2) | (1 << 1),
	.setup		= evm_u18_setup,
	.tearकरोwn	= evm_u18_tearकरोwn,
पूर्ण;


/* U35 - various I/O संकेतs used to manage USB, CF, ATA, etc */

अटल पूर्णांक
evm_u35_setup(काष्ठा i2c_client *client, पूर्णांक gpio, अचिन्हित ngpio, व्योम *c)
अणु
	/* p0 = nDRV_VBUS (initial:  करोn't supply it) */
	gpio_request(gpio + 0, "nDRV_VBUS");
	gpio_direction_output(gpio + 0, 1);

	/* p1 = VDDIMX_EN */
	gpio_request(gpio + 1, "VDDIMX_EN");
	gpio_direction_output(gpio + 1, 1);

	/* p2 = VLYNQ_EN */
	gpio_request(gpio + 2, "VLYNQ_EN");
	gpio_direction_output(gpio + 2, 1);

	/* p3 = n3V3_CF_RESET (initial: stay in reset) */
	gpio_request(gpio + 3, "nCF_RESET");
	gpio_direction_output(gpio + 3, 0);

	/* (p4 unused) */

	/* p5 = 1V8_WLAN_RESET (initial: stay in reset) */
	gpio_request(gpio + 5, "WLAN_RESET");
	gpio_direction_output(gpio + 5, 1);

	/* p6 = nATA_SEL (initial: select) */
	gpio_request(gpio + 6, "nATA_SEL");
	gpio_direction_output(gpio + 6, 0);

	/* p7 = nCF_SEL (initial: deselect) */
	gpio_request(gpio + 7, "nCF_SEL");
	gpio_direction_output(gpio + 7, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक
evm_u35_tearकरोwn(काष्ठा i2c_client *client, पूर्णांक gpio, अचिन्हित ngpio, व्योम *c)
अणु
	gpio_मुक्त(gpio + 7);
	gpio_मुक्त(gpio + 6);
	gpio_मुक्त(gpio + 5);
	gpio_मुक्त(gpio + 3);
	gpio_मुक्त(gpio + 2);
	gpio_मुक्त(gpio + 1);
	gpio_मुक्त(gpio + 0);
	वापस 0;
पूर्ण

अटल काष्ठा pcf857x_platक्रमm_data pcf_data_u35 = अणु
	.gpio_base	= PCF_Uxx_BASE(2),
	.setup		= evm_u35_setup,
	.tearकरोwn	= evm_u35_tearकरोwn,
पूर्ण;

/*----------------------------------------------------------------------*/

/* Most of this EEPROM is unused, but U-Boot uses some data:
 *  - 0x7f00, 6 bytes Ethernet Address
 *  - 0x0039, 1 byte NTSC vs PAL (bit 0x80 == PAL)
 *  - ... newer boards may have more
 */

अटल काष्ठा nvmem_cell_info dm644evm_nvmem_cells[] = अणु
	अणु
		.name		= "macaddr",
		.offset		= 0x7f00,
		.bytes		= ETH_ALEN,
	पूर्ण
पूर्ण;

अटल काष्ठा nvmem_cell_table dm644evm_nvmem_cell_table = अणु
	.nvmem_name	= "1-00500",
	.cells		= dm644evm_nvmem_cells,
	.ncells		= ARRAY_SIZE(dm644evm_nvmem_cells),
पूर्ण;

अटल काष्ठा nvmem_cell_lookup dm644evm_nvmem_cell_lookup = अणु
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

/*
 * MSP430 supports RTC, card detection, input from IR remote, and
 * a bit more.  It triggers पूर्णांकerrupts on GPIO(7) from pressing
 * buttons on the IR remote, and क्रम card detect चयनes.
 */
अटल काष्ठा i2c_client *dm6446evm_msp;

अटल पूर्णांक dm6446evm_msp_probe(काष्ठा i2c_client *client)
अणु
	dm6446evm_msp = client;
	वापस 0;
पूर्ण

अटल पूर्णांक dm6446evm_msp_हटाओ(काष्ठा i2c_client *client)
अणु
	dm6446evm_msp = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id dm6446evm_msp_ids[] = अणु
	अणु "dm6446evm_msp", 0, पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

अटल काष्ठा i2c_driver dm6446evm_msp_driver = अणु
	.driver.name	= "dm6446evm_msp",
	.id_table	= dm6446evm_msp_ids,
	.probe_new	= dm6446evm_msp_probe,
	.हटाओ		= dm6446evm_msp_हटाओ,
पूर्ण;

अटल पूर्णांक dm6444evm_msp430_get_pins(व्योम)
अणु
	अटल स्थिर अक्षर txbuf[2] = अणु 2, 4, पूर्ण;
	अक्षर buf[4];
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.flags = 0,
			.len = 2,
			.buf = (व्योम __क्रमce *)txbuf,
		पूर्ण,
		अणु
			.flags = I2C_M_RD,
			.len = 4,
			.buf = buf,
		पूर्ण,
	पूर्ण;
	पूर्णांक status;

	अगर (!dm6446evm_msp)
		वापस -ENXIO;

	msg[0].addr = dm6446evm_msp->addr;
	msg[1].addr = dm6446evm_msp->addr;

	/* Command 4 == get input state, वापसs port 2 and port3 data
	 *   S Addr W [A] len=2 [A] cmd=4 [A]
	 *   RS Addr R [A] [len=4] A [cmd=4] A [port2] A [port3] N P
	 */
	status = i2c_transfer(dm6446evm_msp->adapter, msg, 2);
	अगर (status < 0)
		वापस status;

	dev_dbg(&dm6446evm_msp->dev, "PINS: %4ph\n", buf);

	वापस (buf[3] << 8) | buf[2];
पूर्ण

अटल पूर्णांक dm6444evm_mmc_get_cd(पूर्णांक module)
अणु
	पूर्णांक status = dm6444evm_msp430_get_pins();

	वापस (status < 0) ? status : !(status & BIT(1));
पूर्ण

अटल पूर्णांक dm6444evm_mmc_get_ro(पूर्णांक module)
अणु
	पूर्णांक status = dm6444evm_msp430_get_pins();

	वापस (status < 0) ? status : status & BIT(6 + 8);
पूर्ण

अटल काष्ठा davinci_mmc_config dm6446evm_mmc_config = अणु
	.get_cd		= dm6444evm_mmc_get_cd,
	.get_ro		= dm6444evm_mmc_get_ro,
	.wires		= 4,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata i2c_info[] =  अणु
	अणु
		I2C_BOARD_INFO("dm6446evm_msp", 0x23),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("pcf8574", 0x38),
		.platक्रमm_data	= &pcf_data_u2,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("pcf8574", 0x39),
		.platक्रमm_data	= &pcf_data_u18,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("pcf8574", 0x3a),
		.platक्रमm_data	= &pcf_data_u35,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("24c256", 0x50),
		.swnode = &eeprom_node,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("tlv320aic33", 0x1b),
	पूर्ण,
पूर्ण;

#घोषणा DM644X_I2C_SDA_PIN	GPIO_TO_PIN(2, 12)
#घोषणा DM644X_I2C_SCL_PIN	GPIO_TO_PIN(2, 11)

अटल काष्ठा gpiod_lookup_table i2c_recovery_gpiod_table = अणु
	.dev_id = "i2c_davinci.1",
	.table = अणु
		GPIO_LOOKUP("davinci_gpio", DM644X_I2C_SDA_PIN, "sda",
			    GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP("davinci_gpio", DM644X_I2C_SCL_PIN, "scl",
			    GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

/* The msp430 uses a slow bitbanged I2C implementation (ergo 20 KHz),
 * which requires 100 usec of idle bus after i2c ग_लिखोs sent to it.
 */
अटल काष्ठा davinci_i2c_platक्रमm_data i2c_pdata = अणु
	.bus_freq	= 20 /* kHz */,
	.bus_delay	= 100 /* usec */,
	.gpio_recovery	= true,
पूर्ण;

अटल व्योम __init evm_init_i2c(व्योम)
अणु
	gpiod_add_lookup_table(&i2c_recovery_gpiod_table);
	davinci_init_i2c(&i2c_pdata);
	i2c_add_driver(&dm6446evm_msp_driver);
	i2c_रेजिस्टर_board_info(1, i2c_info, ARRAY_SIZE(i2c_info));
पूर्ण
#पूर्ण_अगर

/* Fixed regulator support */
अटल काष्ठा regulator_consumer_supply fixed_supplies_3_3v[] = अणु
	/* Baseboard 3.3V: 5V -> TPS54310PWP -> 3.3V */
	REGULATOR_SUPPLY("AVDD", "1-001b"),
	REGULATOR_SUPPLY("DRVDD", "1-001b"),
पूर्ण;

अटल काष्ठा regulator_consumer_supply fixed_supplies_1_8v[] = अणु
	/* Baseboard 1.8V: 5V -> TPS54310PWP -> 1.8V */
	REGULATOR_SUPPLY("IOVDD", "1-001b"),
	REGULATOR_SUPPLY("DVDD", "1-001b"),
पूर्ण;

#घोषणा VENC_STD_ALL	(V4L2_STD_NTSC | V4L2_STD_PAL)

/* venc standard timings */
अटल काष्ठा vpbe_enc_mode_info dm644xevm_enc_std_timing[] = अणु
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
		.left_margin	= 0x7e,
		.upper_margin	= 0x16,
	पूर्ण,
पूर्ण;

/* venc dv preset timings */
अटल काष्ठा vpbe_enc_mode_info dm644xevm_enc_preset_timing[] = अणु
	अणु
		.name		= "480p59_94",
		.timings_type	= VPBE_ENC_DV_TIMINGS,
		.dv_timings	= V4L2_DV_BT_CEA_720X480P59_94,
		.पूर्णांकerlaced	= 0,
		.xres		= 720,
		.yres		= 480,
		.aspect		= अणु1, 1पूर्ण,
		.fps		= अणु5994, 100पूर्ण,
		.left_margin	= 0x80,
		.upper_margin	= 0x20,
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
		.left_margin	= 0x7e,
		.upper_margin	= 0x30,
	पूर्ण,
पूर्ण;

/*
 * The outमाला_दो available from VPBE + encoders. Keep the order same
 * as that of encoders. First those from venc followed by that from
 * encoders. Index in the output refers to index on a particular encoder.
 * Driver uses this index to pass it to encoder when it supports more
 * than one output. Userspace applications use index of the array to
 * set an output.
 */
अटल काष्ठा vpbe_output dm644xevm_vpbe_outमाला_दो[] = अणु
	अणु
		.output		= अणु
			.index		= 0,
			.name		= "Composite",
			.type		= V4L2_OUTPUT_TYPE_ANALOG,
			.std		= VENC_STD_ALL,
			.capabilities	= V4L2_OUT_CAP_STD,
		पूर्ण,
		.subdev_name	= DM644X_VPBE_VENC_SUBDEV_NAME,
		.शेष_mode	= "ntsc",
		.num_modes	= ARRAY_SIZE(dm644xevm_enc_std_timing),
		.modes		= dm644xevm_enc_std_timing,
	पूर्ण,
	अणु
		.output		= अणु
			.index		= 1,
			.name		= "Component",
			.type		= V4L2_OUTPUT_TYPE_ANALOG,
			.capabilities	= V4L2_OUT_CAP_DV_TIMINGS,
		पूर्ण,
		.subdev_name	= DM644X_VPBE_VENC_SUBDEV_NAME,
		.शेष_mode	= "480p59_94",
		.num_modes	= ARRAY_SIZE(dm644xevm_enc_preset_timing),
		.modes		= dm644xevm_enc_preset_timing,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpbe_config dm644xevm_display_cfg = अणु
	.module_name	= "dm644x-vpbe-display",
	.i2c_adapter_id	= 1,
	.osd		= अणु
		.module_name	= DM644X_VPBE_OSD_SUBDEV_NAME,
	पूर्ण,
	.venc		= अणु
		.module_name	= DM644X_VPBE_VENC_SUBDEV_NAME,
	पूर्ण,
	.num_outमाला_दो	= ARRAY_SIZE(dm644xevm_vpbe_outमाला_दो),
	.outमाला_दो	= dm644xevm_vpbe_outमाला_दो,
पूर्ण;

अटल काष्ठा platक्रमm_device *davinci_evm_devices[] __initdata = अणु
	&davinci_fb_device,
	&rtc_dev,
पूर्ण;

अटल व्योम __init
davinci_evm_map_io(व्योम)
अणु
	dm644x_init();
पूर्ण

अटल पूर्णांक davinci_phy_fixup(काष्ठा phy_device *phydev)
अणु
	अचिन्हित पूर्णांक control;
	/* CRITICAL: Fix क्रम increasing PHY संकेत drive strength क्रम
	 * TX lockup issue. On DaVinci EVM, the Intel LXT971 PHY
	 * संकेत strength was low causing  TX to fail अक्रमomly. The
	 * fix is to Set bit 11 (Increased MII drive strength) of PHY
	 * रेजिस्टर 26 (Digital Config रेजिस्टर) on this phy. */
	control = phy_पढ़ो(phydev, 26);
	phy_ग_लिखो(phydev, 26, (control | 0x800));
	वापस 0;
पूर्ण

#घोषणा HAS_ATA		(IS_ENABLED(CONFIG_BLK_DEV_PALMCHIP_BK3710) || \
			 IS_ENABLED(CONFIG_PATA_BK3710))

#घोषणा HAS_NOR		IS_ENABLED(CONFIG_MTD_PHYSMAP)

#घोषणा HAS_न_अंकD	IS_ENABLED(CONFIG_MTD_न_अंकD_DAVINCI)

#घोषणा GPIO_nVBUS_DRV		160

अटल काष्ठा gpiod_lookup_table dm644evm_usb_gpio_table = अणु
	.dev_id = "musb-davinci",
	.table = अणु
		GPIO_LOOKUP("davinci_gpio", GPIO_nVBUS_DRV, शून्य,
			    GPIO_ACTIVE_HIGH),
		अणु पूर्ण
	पूर्ण,
पूर्ण;

अटल __init व्योम davinci_evm_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा clk *aemअगर_clk;
	काष्ठा davinci_soc_info *soc_info = &davinci_soc_info;

	dm644x_रेजिस्टर_घड़ीs();

	regulator_रेजिस्टर_always_on(0, "fixed-dummy", fixed_supplies_1_8v,
				     ARRAY_SIZE(fixed_supplies_1_8v), 1800000);
	regulator_रेजिस्टर_always_on(1, "fixed-dummy", fixed_supplies_3_3v,
				     ARRAY_SIZE(fixed_supplies_3_3v), 3300000);

	dm644x_init_devices();

	ret = dm644x_gpio_रेजिस्टर();
	अगर (ret)
		pr_warn("%s: GPIO init failed: %d\n", __func__, ret);

	aemअगर_clk = clk_get(शून्य, "aemif");
	clk_prepare_enable(aemअगर_clk);

	अगर (HAS_ATA) अणु
		अगर (HAS_न_अंकD || HAS_NOR)
			pr_warn("WARNING: both IDE and Flash are enabled, but they share AEMIF pins\n"
				"\tDisable IDE for NAND/NOR support\n");
		davinci_init_ide();
	पूर्ण अन्यथा अगर (HAS_न_अंकD || HAS_NOR) अणु
		davinci_cfg_reg(DM644X_HPIEN_DISABLE);
		davinci_cfg_reg(DM644X_ATAEN_DISABLE);

		/* only one device will be jumpered and detected */
		अगर (HAS_न_अंकD) अणु
			platक्रमm_device_रेजिस्टर(&davinci_evm_aemअगर_device);
#अगर_घोषित CONFIG_I2C
			evm_leds[7].शेष_trigger = "nand-disk";
#पूर्ण_अगर
			अगर (HAS_NOR)
				pr_warn("WARNING: both NAND and NOR flash are enabled; disable one of them.\n");
		पूर्ण अन्यथा अगर (HAS_NOR)
			platक्रमm_device_रेजिस्टर(&davinci_evm_norflash_device);
	पूर्ण

	platक्रमm_add_devices(davinci_evm_devices,
			     ARRAY_SIZE(davinci_evm_devices));
#अगर_घोषित CONFIG_I2C
	nvmem_add_cell_table(&dm644evm_nvmem_cell_table);
	nvmem_add_cell_lookups(&dm644evm_nvmem_cell_lookup, 1);
	evm_init_i2c();
	davinci_setup_mmc(0, &dm6446evm_mmc_config);
#पूर्ण_अगर
	dm644x_init_video(&dm644xevm_capture_cfg, &dm644xevm_display_cfg);

	davinci_serial_init(dm644x_serial_device);
	dm644x_init_asp();

	/* irlml6401 चयनes over 1A, in under 8 msec */
	gpiod_add_lookup_table(&dm644evm_usb_gpio_table);
	davinci_setup_usb(1000, 8);

	अगर (IS_BUILTIN(CONFIG_PHYLIB)) अणु
		soc_info->emac_pdata->phy_id = DM644X_EVM_PHY_ID;
		/* Register the fixup क्रम PHY on DaVinci */
		phy_रेजिस्टर_fixup_क्रम_uid(LXT971_PHY_ID, LXT971_PHY_MASK,
						davinci_phy_fixup);
	पूर्ण
पूर्ण

MACHINE_START(DAVINCI_EVM, "DaVinci DM644x EVM")
	/* Maपूर्णांकainer: MontaVista Software <source@mvista.com> */
	.atag_offset  = 0x100,
	.map_io	      = davinci_evm_map_io,
	.init_irq     = dm644x_init_irq,
	.init_समय	= dm644x_init_समय,
	.init_machine = davinci_evm_init,
	.init_late	= davinci_init_late,
	.dma_zone_size	= SZ_128M,
MACHINE_END
