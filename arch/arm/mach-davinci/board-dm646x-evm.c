<शैली गुरु>
/*
 * TI DaVinci DM646X EVM board
 *
 * Derived from: arch/arm/mach-davinci/board-evm.c
 * Copyright (C) 2006 Texas Instruments.
 *
 * (C) 2007-2008, MontaVista Software, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 */

/**************************************************************************
 * Included Files
 **************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/property.h>
#समावेश <linux/platक्रमm_data/pcf857x.h>
#समावेश <linux/platक्रमm_data/ti-aemअगर.h>

#समावेश <media/i2c/tvp514x.h>
#समावेश <media/i2c/adv7343.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_data/gpio-davinci.h>
#समावेश <linux/platक्रमm_data/i2c-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci.h>
#समावेश <linux/platक्रमm_data/mtd-davinci-aemअगर.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश <mach/common.h>
#समावेश <mach/serial.h>

#समावेश "davinci.h"
#समावेश "irqs.h"

#घोषणा न_अंकD_BLOCK_SIZE		SZ_128K

/* Note: We are setting first partition as 'bootloader' स्थिरituting UBL, U-Boot
 * and U-Boot environment this aव्योमs dependency on any particular combination
 * of UBL, U-Boot or flashing tools etc.
 */
अटल काष्ठा mtd_partition davinci_nand_partitions[] = अणु
	अणु
		/* UBL, U-Boot with environment */
		.name		= "bootloader",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 16 * न_अंकD_BLOCK_SIZE,
		.mask_flags	= MTD_WRITEABLE,	/* क्रमce पढ़ो-only */
	पूर्ण, अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_4M,
		.mask_flags	= 0,
	पूर्ण, अणु
		.name		= "filesystem",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
		.mask_flags	= 0,
	पूर्ण
पूर्ण;

अटल काष्ठा davinci_aemअगर_timing dm6467tevm_nandflash_timing = अणु
	.wsetup		= 29,
	.wstrobe	= 24,
	.whold		= 14,
	.rsetup		= 19,
	.rstrobe	= 33,
	.rhold		= 0,
	.ta		= 29,
पूर्ण;

अटल काष्ठा davinci_nand_pdata davinci_nand_data = अणु
	.core_chipsel		= 0,
	.mask_cle 		= 0x80000,
	.mask_ale 		= 0x40000,
	.parts			= davinci_nand_partitions,
	.nr_parts		= ARRAY_SIZE(davinci_nand_partitions),
	.engine_type		= न_अंकD_ECC_ENGINE_TYPE_ON_HOST,
	.ecc_bits		= 1,
	.options		= 0,
पूर्ण;

अटल काष्ठा resource davinci_nand_resources[] = अणु
	अणु
		.start		= DM646X_ASYNC_EMIF_CS2_SPACE_BASE,
		.end		= DM646X_ASYNC_EMIF_CS2_SPACE_BASE + SZ_32M - 1,
		.flags		= IORESOURCE_MEM,
	पूर्ण, अणु
		.start		= DM646X_ASYNC_EMIF_CONTROL_BASE,
		.end		= DM646X_ASYNC_EMIF_CONTROL_BASE + SZ_4K - 1,
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
	पूर्ण,
पूर्ण;

अटल काष्ठा resource davinci_aemअगर_resources[] = अणु
	अणु
		.start	= DM646X_ASYNC_EMIF_CONTROL_BASE,
		.end	= DM646X_ASYNC_EMIF_CONTROL_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा aemअगर_abus_data davinci_aemअगर_abus_data[] = अणु
	अणु
		.cs	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा aemअगर_platक्रमm_data davinci_aemअगर_pdata = अणु
	.abus_data		= davinci_aemअगर_abus_data,
	.num_abus_data		= ARRAY_SIZE(davinci_aemअगर_abus_data),
	.sub_devices		= davinci_aemअगर_devices,
	.num_sub_devices	= ARRAY_SIZE(davinci_aemअगर_devices),
पूर्ण;

अटल काष्ठा platक्रमm_device davinci_aemअगर_device = अणु
	.name		= "ti-aemif",
	.id		= -1,
	.dev = अणु
		.platक्रमm_data	= &davinci_aemअगर_pdata,
	पूर्ण,
	.resource	= davinci_aemअगर_resources,
	.num_resources	= ARRAY_SIZE(davinci_aemअगर_resources),
पूर्ण;

#घोषणा HAS_ATA		(IS_ENABLED(CONFIG_BLK_DEV_PALMCHIP_BK3710) || \
			 IS_ENABLED(CONFIG_PATA_BK3710))

#अगर_घोषित CONFIG_I2C
/* CPLD Register 0 bits to control ATA */
#घोषणा DM646X_EVM_ATA_RST		BIT(0)
#घोषणा DM646X_EVM_ATA_PWD		BIT(1)

/* CPLD Register 0 Client: used क्रम I/O Control */
अटल पूर्णांक cpld_reg0_probe(काष्ठा i2c_client *client)
अणु
	अगर (HAS_ATA) अणु
		u8 data;
		काष्ठा i2c_msg msg[2] = अणु
			अणु
				.addr = client->addr,
				.flags = I2C_M_RD,
				.len = 1,
				.buf = &data,
			पूर्ण,
			अणु
				.addr = client->addr,
				.flags = 0,
				.len = 1,
				.buf = &data,
			पूर्ण,
		पूर्ण;

		/* Clear ATA_RSTn and ATA_PWD bits to enable ATA operation. */
		i2c_transfer(client->adapter, msg, 1);
		data &= ~(DM646X_EVM_ATA_RST | DM646X_EVM_ATA_PWD);
		i2c_transfer(client->adapter, msg + 1, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cpld_reg_ids[] = अणु
	अणु "cpld_reg0", 0, पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा i2c_driver dm6467evm_cpld_driver = अणु
	.driver.name	= "cpld_reg0",
	.id_table	= cpld_reg_ids,
	.probe_new	= cpld_reg0_probe,
पूर्ण;

/* LEDS */

अटल काष्ठा gpio_led evm_leds[] = अणु
	अणु .name = "DS1", .active_low = 1, पूर्ण,
	अणु .name = "DS2", .active_low = 1, पूर्ण,
	अणु .name = "DS3", .active_low = 1, पूर्ण,
	अणु .name = "DS4", .active_low = 1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led_platक्रमm_data evm_led_data = अणु
	.num_leds = ARRAY_SIZE(evm_leds),
	.leds     = evm_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device *evm_led_dev;

अटल पूर्णांक evm_led_setup(काष्ठा i2c_client *client, पूर्णांक gpio,
			अचिन्हित पूर्णांक ngpio, व्योम *c)
अणु
	काष्ठा gpio_led *leds = evm_leds;
	पूर्णांक status;

	जबतक (ngpio--) अणु
		leds->gpio = gpio++;
		leds++;
	पूर्ण

	evm_led_dev = platक्रमm_device_alloc("leds-gpio", 0);
	platक्रमm_device_add_data(evm_led_dev, &evm_led_data,
				माप(evm_led_data));

	evm_led_dev->dev.parent = &client->dev;
	status = platक्रमm_device_add(evm_led_dev);
	अगर (status < 0) अणु
		platक्रमm_device_put(evm_led_dev);
		evm_led_dev = शून्य;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक evm_led_tearकरोwn(काष्ठा i2c_client *client, पूर्णांक gpio,
				अचिन्हित ngpio, व्योम *c)
अणु
	अगर (evm_led_dev) अणु
		platक्रमm_device_unरेजिस्टर(evm_led_dev);
		evm_led_dev = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक evm_sw_gpio[4] = अणु -EINVAL, -EINVAL, -EINVAL, -EINVAL पूर्ण;

अटल पूर्णांक evm_sw_setup(काष्ठा i2c_client *client, पूर्णांक gpio,
			अचिन्हित ngpio, व्योम *c)
अणु
	पूर्णांक status;
	पूर्णांक i;
	अक्षर label[10];

	क्रम (i = 0; i < 4; ++i) अणु
		snम_लिखो(label, 10, "user_sw%d", i);
		status = gpio_request(gpio, label);
		अगर (status)
			जाओ out_मुक्त;
		evm_sw_gpio[i] = gpio++;

		status = gpio_direction_input(evm_sw_gpio[i]);
		अगर (status)
			जाओ out_मुक्त;

		status = gpio_export(evm_sw_gpio[i], 0);
		अगर (status)
			जाओ out_मुक्त;
	पूर्ण
	वापस 0;

out_मुक्त:
	क्रम (i = 0; i < 4; ++i) अणु
		अगर (evm_sw_gpio[i] != -EINVAL) अणु
			gpio_मुक्त(evm_sw_gpio[i]);
			evm_sw_gpio[i] = -EINVAL;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक evm_sw_tearकरोwn(काष्ठा i2c_client *client, पूर्णांक gpio,
			अचिन्हित ngpio, व्योम *c)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; ++i) अणु
		अगर (evm_sw_gpio[i] != -EINVAL) अणु
			gpio_unexport(evm_sw_gpio[i]);
			gpio_मुक्त(evm_sw_gpio[i]);
			evm_sw_gpio[i] = -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक evm_pcf_setup(काष्ठा i2c_client *client, पूर्णांक gpio,
			अचिन्हित पूर्णांक ngpio, व्योम *c)
अणु
	पूर्णांक status;

	अगर (ngpio < 8)
		वापस -EINVAL;

	status = evm_sw_setup(client, gpio, 4, c);
	अगर (status)
		वापस status;

	वापस evm_led_setup(client, gpio+4, 4, c);
पूर्ण

अटल पूर्णांक evm_pcf_tearकरोwn(काष्ठा i2c_client *client, पूर्णांक gpio,
			अचिन्हित पूर्णांक ngpio, व्योम *c)
अणु
	BUG_ON(ngpio < 8);

	evm_sw_tearकरोwn(client, gpio, 4, c);
	evm_led_tearकरोwn(client, gpio+4, 4, c);

	वापस 0;
पूर्ण

अटल काष्ठा pcf857x_platक्रमm_data pcf_data = अणु
	.gpio_base	= DAVINCI_N_GPIO+1,
	.setup		= evm_pcf_setup,
	.tearकरोwn	= evm_pcf_tearकरोwn,
पूर्ण;

/* Most of this EEPROM is unused, but U-Boot uses some data:
 *  - 0x7f00, 6 bytes Ethernet Address
 *  - ... newer boards may have more
 */

अटल काष्ठा nvmem_cell_info dm646x_evm_nvmem_cells[] = अणु
	अणु
		.name		= "macaddr",
		.offset		= 0x7f00,
		.bytes		= ETH_ALEN,
	पूर्ण
पूर्ण;

अटल काष्ठा nvmem_cell_table dm646x_evm_nvmem_cell_table = अणु
	.nvmem_name	= "1-00500",
	.cells		= dm646x_evm_nvmem_cells,
	.ncells		= ARRAY_SIZE(dm646x_evm_nvmem_cells),
पूर्ण;

अटल काष्ठा nvmem_cell_lookup dm646x_evm_nvmem_cell_lookup = अणु
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
#पूर्ण_अगर

अटल u8 dm646x_iis_serializer_direction[] = अणु
       TX_MODE, RX_MODE, INACTIVE_MODE, INACTIVE_MODE,
पूर्ण;

अटल u8 dm646x_dit_serializer_direction[] = अणु
       TX_MODE,
पूर्ण;

अटल काष्ठा snd_platक्रमm_data dm646x_evm_snd_data[] = अणु
	अणु
		.tx_dma_offset  = 0x400,
		.rx_dma_offset  = 0x400,
		.op_mode        = DAVINCI_MCASP_IIS_MODE,
		.num_serializer = ARRAY_SIZE(dm646x_iis_serializer_direction),
		.tdm_slots      = 2,
		.serial_dir     = dm646x_iis_serializer_direction,
		.asp_chan_q     = EVENTQ_0,
	पूर्ण,
	अणु
		.tx_dma_offset  = 0x400,
		.rx_dma_offset  = 0,
		.op_mode        = DAVINCI_MCASP_DIT_MODE,
		.num_serializer = ARRAY_SIZE(dm646x_dit_serializer_direction),
		.tdm_slots      = 32,
		.serial_dir     = dm646x_dit_serializer_direction,
		.asp_chan_q     = EVENTQ_0,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_I2C
अटल काष्ठा i2c_client *cpld_client;

अटल पूर्णांक cpld_video_probe(काष्ठा i2c_client *client)
अणु
	cpld_client = client;
	वापस 0;
पूर्ण

अटल पूर्णांक cpld_video_हटाओ(काष्ठा i2c_client *client)
अणु
	cpld_client = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cpld_video_id[] = अणु
	अणु "cpld_video", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver cpld_video_driver = अणु
	.driver = अणु
		.name	= "cpld_video",
	पूर्ण,
	.probe_new	= cpld_video_probe,
	.हटाओ		= cpld_video_हटाओ,
	.id_table	= cpld_video_id,
पूर्ण;

अटल व्योम evm_init_cpld(व्योम)
अणु
	i2c_add_driver(&cpld_video_driver);
पूर्ण

अटल काष्ठा i2c_board_info __initdata i2c_info[] =  अणु
	अणु
		I2C_BOARD_INFO("24c256", 0x50),
		.swnode = &eeprom_node,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("pcf8574a", 0x38),
		.platक्रमm_data	= &pcf_data,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("cpld_reg0", 0x3a),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("tlv320aic33", 0x18),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("cpld_video", 0x3b),
	पूर्ण,
पूर्ण;

अटल काष्ठा davinci_i2c_platक्रमm_data i2c_pdata = अणु
	.bus_freq       = 100 /* kHz */,
	.bus_delay      = 0 /* usec */,
पूर्ण;

#घोषणा VCH2CLK_MASK		(BIT_MASK(10) | BIT_MASK(9) | BIT_MASK(8))
#घोषणा VCH2CLK_SYSCLK8		(BIT(9))
#घोषणा VCH2CLK_AUXCLK		(BIT(9) | BIT(8))
#घोषणा VCH3CLK_MASK		(BIT_MASK(14) | BIT_MASK(13) | BIT_MASK(12))
#घोषणा VCH3CLK_SYSCLK8		(BIT(13))
#घोषणा VCH3CLK_AUXCLK		(BIT(14) | BIT(13))

#घोषणा VIDCH2CLK		(BIT(10))
#घोषणा VIDCH3CLK		(BIT(11))
#घोषणा VIDCH1CLK		(BIT(4))
#घोषणा TVP7002_INPUT		(BIT(4))
#घोषणा TVP5147_INPUT		(~BIT(4))
#घोषणा VPIF_INPUT_ONE_CHANNEL	(BIT(5))
#घोषणा VPIF_INPUT_TWO_CHANNEL	(~BIT(5))
#घोषणा TVP5147_CH0		"tvp514x-0"
#घोषणा TVP5147_CH1		"tvp514x-1"

/* spin lock क्रम updating above रेजिस्टरs */
अटल spinlock_t vpअगर_reg_lock;

अटल पूर्णांक set_vpअगर_घड़ी(पूर्णांक mux_mode, पूर्णांक hd)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक value;
	पूर्णांक val = 0;
	पूर्णांक err = 0;

	अगर (!cpld_client)
		वापस -ENXIO;

	/* disable the घड़ी */
	spin_lock_irqsave(&vpअगर_reg_lock, flags);
	value = __raw_पढ़ोl(DAVINCI_SYSMOD_VIRT(SYSMOD_VSCLKDIS));
	value |= (VIDCH3CLK | VIDCH2CLK);
	__raw_ग_लिखोl(value, DAVINCI_SYSMOD_VIRT(SYSMOD_VSCLKDIS));
	spin_unlock_irqrestore(&vpअगर_reg_lock, flags);

	val = i2c_smbus_पढ़ो_byte(cpld_client);
	अगर (val < 0)
		वापस val;

	अगर (mux_mode == 1)
		val &= ~0x40;
	अन्यथा
		val |= 0x40;

	err = i2c_smbus_ग_लिखो_byte(cpld_client, val);
	अगर (err)
		वापस err;

	value = __raw_पढ़ोl(DAVINCI_SYSMOD_VIRT(SYSMOD_VIDCLKCTL));
	value &= ~(VCH2CLK_MASK);
	value &= ~(VCH3CLK_MASK);

	अगर (hd >= 1)
		value |= (VCH2CLK_SYSCLK8 | VCH3CLK_SYSCLK8);
	अन्यथा
		value |= (VCH2CLK_AUXCLK | VCH3CLK_AUXCLK);

	__raw_ग_लिखोl(value, DAVINCI_SYSMOD_VIRT(SYSMOD_VIDCLKCTL));

	spin_lock_irqsave(&vpअगर_reg_lock, flags);
	value = __raw_पढ़ोl(DAVINCI_SYSMOD_VIRT(SYSMOD_VSCLKDIS));
	/* enable the घड़ी */
	value &= ~(VIDCH3CLK | VIDCH2CLK);
	__raw_ग_लिखोl(value, DAVINCI_SYSMOD_VIRT(SYSMOD_VSCLKDIS));
	spin_unlock_irqrestore(&vpअगर_reg_lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा vpअगर_subdev_info dm646x_vpअगर_subdev[] = अणु
	अणु
		.name	= "adv7343",
		.board_info = अणु
			I2C_BOARD_INFO("adv7343", 0x2a),
		पूर्ण,
	पूर्ण,
	अणु
		.name	= "ths7303",
		.board_info = अणु
			I2C_BOARD_INFO("ths7303", 0x2c),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vpअगर_output dm6467_ch0_outमाला_दो[] = अणु
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
			.name = "Component",
			.type = V4L2_OUTPUT_TYPE_ANALOG,
			.capabilities = V4L2_OUT_CAP_DV_TIMINGS,
		पूर्ण,
		.subdev_name = "adv7343",
		.output_route = ADV7343_COMPONENT_ID,
	पूर्ण,
	अणु
		.output = अणु
			.index = 2,
			.name = "S-Video",
			.type = V4L2_OUTPUT_TYPE_ANALOG,
			.capabilities = V4L2_OUT_CAP_STD,
			.std = V4L2_STD_ALL,
		पूर्ण,
		.subdev_name = "adv7343",
		.output_route = ADV7343_SVIDEO_ID,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_display_config dm646x_vpअगर_display_config = अणु
	.set_घड़ी	= set_vpअगर_घड़ी,
	.subdevinfo	= dm646x_vpअगर_subdev,
	.subdev_count	= ARRAY_SIZE(dm646x_vpअगर_subdev),
	.i2c_adapter_id = 1,
	.chan_config[0] = अणु
		.outमाला_दो = dm6467_ch0_outमाला_दो,
		.output_count = ARRAY_SIZE(dm6467_ch0_outमाला_दो),
	पूर्ण,
	.card_name	= "DM646x EVM Video Display",
पूर्ण;

/**
 * setup_vpअगर_input_path()
 * @channel: channel id (0 - CH0, 1 - CH1)
 * @sub_dev_name: ptr sub device name
 *
 * This will set vpअगर input to capture data from tvp514x or
 * tvp7002.
 */
अटल पूर्णांक setup_vpअगर_input_path(पूर्णांक channel, स्थिर अक्षर *sub_dev_name)
अणु
	पूर्णांक err = 0;
	पूर्णांक val;

	/* क्रम channel 1, we करोn't करो anything */
	अगर (channel != 0)
		वापस 0;

	अगर (!cpld_client)
		वापस -ENXIO;

	val = i2c_smbus_पढ़ो_byte(cpld_client);
	अगर (val < 0)
		वापस val;

	अगर (!म_भेद(sub_dev_name, TVP5147_CH0) ||
	    !म_भेद(sub_dev_name, TVP5147_CH1))
		val &= TVP5147_INPUT;
	अन्यथा
		val |= TVP7002_INPUT;

	err = i2c_smbus_ग_लिखो_byte(cpld_client, val);
	अगर (err)
		वापस err;
	वापस 0;
पूर्ण

/**
 * setup_vpअगर_input_channel_mode()
 * @mux_mode:  mux mode. 0 - 1 channel or (1) - 2 channel
 *
 * This will setup input mode to one channel (TVP7002) or 2 channel (TVP5147)
 */
अटल पूर्णांक setup_vpअगर_input_channel_mode(पूर्णांक mux_mode)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक val;
	u32 value;

	अगर (!cpld_client)
		वापस -ENXIO;

	val = i2c_smbus_पढ़ो_byte(cpld_client);
	अगर (val < 0)
		वापस val;

	spin_lock_irqsave(&vpअगर_reg_lock, flags);
	value = __raw_पढ़ोl(DAVINCI_SYSMOD_VIRT(SYSMOD_VIDCLKCTL));
	अगर (mux_mode) अणु
		val &= VPIF_INPUT_TWO_CHANNEL;
		value |= VIDCH1CLK;
	पूर्ण अन्यथा अणु
		val |= VPIF_INPUT_ONE_CHANNEL;
		value &= ~VIDCH1CLK;
	पूर्ण
	__raw_ग_लिखोl(value, DAVINCI_SYSMOD_VIRT(SYSMOD_VIDCLKCTL));
	spin_unlock_irqrestore(&vpअगर_reg_lock, flags);

	err = i2c_smbus_ग_लिखो_byte(cpld_client, val);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल काष्ठा tvp514x_platक्रमm_data tvp5146_pdata = अणु
	.clk_polarity = 0,
	.hs_polarity = 1,
	.vs_polarity = 1
पूर्ण;

#घोषणा TVP514X_STD_ALL (V4L2_STD_NTSC | V4L2_STD_PAL)

अटल काष्ठा vpअगर_subdev_info vpअगर_capture_sdev_info[] = अणु
	अणु
		.name	= TVP5147_CH0,
		.board_info = अणु
			I2C_BOARD_INFO("tvp5146", 0x5d),
			.platक्रमm_data = &tvp5146_pdata,
		पूर्ण,
	पूर्ण,
	अणु
		.name	= TVP5147_CH1,
		.board_info = अणु
			I2C_BOARD_INFO("tvp5146", 0x5c),
			.platक्रमm_data = &tvp5146_pdata,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_input dm6467_ch0_inमाला_दो[] = अणु
	अणु
		.input = अणु
			.index = 0,
			.name = "Composite",
			.type = V4L2_INPUT_TYPE_CAMERA,
			.capabilities = V4L2_IN_CAP_STD,
			.std = TVP514X_STD_ALL,
		पूर्ण,
		.subdev_name = TVP5147_CH0,
		.input_route = INPUT_CVBS_VI2B,
		.output_route = OUTPUT_10BIT_422_EMBEDDED_SYNC,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_input dm6467_ch1_inमाला_दो[] = अणु
       अणु
		.input = अणु
			.index = 0,
			.name = "S-Video",
			.type = V4L2_INPUT_TYPE_CAMERA,
			.capabilities = V4L2_IN_CAP_STD,
			.std = TVP514X_STD_ALL,
		पूर्ण,
		.subdev_name = TVP5147_CH1,
		.input_route = INPUT_SVIDEO_VI2C_VI1C,
		.output_route = OUTPUT_10BIT_422_EMBEDDED_SYNC,
	पूर्ण,
पूर्ण;

अटल काष्ठा vpअगर_capture_config dm646x_vpअगर_capture_cfg = अणु
	.setup_input_path = setup_vpअगर_input_path,
	.setup_input_channel_mode = setup_vpअगर_input_channel_mode,
	.subdev_info = vpअगर_capture_sdev_info,
	.subdev_count = ARRAY_SIZE(vpअगर_capture_sdev_info),
	.i2c_adapter_id = 1,
	.chan_config[0] = अणु
		.inमाला_दो = dm6467_ch0_inमाला_दो,
		.input_count = ARRAY_SIZE(dm6467_ch0_inमाला_दो),
		.vpअगर_अगर = अणु
			.अगर_type = VPIF_IF_BT656,
			.hd_pol = 1,
			.vd_pol = 1,
			.fid_pol = 0,
		पूर्ण,
	पूर्ण,
	.chan_config[1] = अणु
		.inमाला_दो = dm6467_ch1_inमाला_दो,
		.input_count = ARRAY_SIZE(dm6467_ch1_inमाला_दो),
		.vpअगर_अगर = अणु
			.अगर_type = VPIF_IF_BT656,
			.hd_pol = 1,
			.vd_pol = 1,
			.fid_pol = 0,
		पूर्ण,
	पूर्ण,
	.card_name = "DM646x EVM Video Capture",
पूर्ण;

अटल व्योम __init evm_init_video(व्योम)
अणु
	spin_lock_init(&vpअगर_reg_lock);

	dm646x_setup_vpअगर(&dm646x_vpअगर_display_config,
			  &dm646x_vpअगर_capture_cfg);
पूर्ण

अटल व्योम __init evm_init_i2c(व्योम)
अणु
	davinci_init_i2c(&i2c_pdata);
	i2c_add_driver(&dm6467evm_cpld_driver);
	i2c_रेजिस्टर_board_info(1, i2c_info, ARRAY_SIZE(i2c_info));
	evm_init_cpld();
	evm_init_video();
पूर्ण
#पूर्ण_अगर

#घोषणा DM646X_REF_FREQ			27000000
#घोषणा DM646X_AUX_FREQ			24000000
#घोषणा DM6467T_EVM_REF_FREQ		33000000

अटल व्योम __init davinci_map_io(व्योम)
अणु
	dm646x_init();
पूर्ण

अटल व्योम __init dm646x_evm_init_समय(व्योम)
अणु
	dm646x_init_समय(DM646X_REF_FREQ, DM646X_AUX_FREQ);
पूर्ण

अटल व्योम __init dm6467t_evm_init_समय(व्योम)
अणु
	dm646x_init_समय(DM6467T_EVM_REF_FREQ, DM646X_AUX_FREQ);
पूर्ण

#घोषणा DM646X_EVM_PHY_ID		"davinci_mdio-0:01"
/*
 * The following EDMA channels/slots are not being used by drivers (क्रम
 * example: Timer, GPIO, UART events etc) on dm646x, hence they are being
 * reserved क्रम codecs on the DSP side.
 */
अटल स्थिर s16 dm646x_dma_rsv_chans[][2] = अणु
	/* (offset, number) */
	अणु 0,  4पूर्ण,
	अणु13,  3पूर्ण,
	अणु24,  4पूर्ण,
	अणु30,  2पूर्ण,
	अणु54,  3पूर्ण,
	अणु-1, -1पूर्ण
पूर्ण;

अटल स्थिर s16 dm646x_dma_rsv_slots[][2] = अणु
	/* (offset, number) */
	अणु 0,  4पूर्ण,
	अणु13,  3पूर्ण,
	अणु24,  4पूर्ण,
	अणु30,  2पूर्ण,
	अणु54,  3पूर्ण,
	अणु128, 384पूर्ण,
	अणु-1, -1पूर्ण
पूर्ण;

अटल काष्ठा edma_rsv_info dm646x_edma_rsv[] = अणु
	अणु
		.rsv_chans	= dm646x_dma_rsv_chans,
		.rsv_slots	= dm646x_dma_rsv_slots,
	पूर्ण,
पूर्ण;

अटल __init व्योम evm_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा davinci_soc_info *soc_info = &davinci_soc_info;

	dm646x_रेजिस्टर_घड़ीs();

	ret = dm646x_gpio_रेजिस्टर();
	अगर (ret)
		pr_warn("%s: GPIO init failed: %d\n", __func__, ret);

#अगर_घोषित CONFIG_I2C
	nvmem_add_cell_table(&dm646x_evm_nvmem_cell_table);
	nvmem_add_cell_lookups(&dm646x_evm_nvmem_cell_lookup, 1);
	evm_init_i2c();
#पूर्ण_अगर

	davinci_serial_init(dm646x_serial_device);
	dm646x_init_mcasp0(&dm646x_evm_snd_data[0]);
	dm646x_init_mcasp1(&dm646x_evm_snd_data[1]);

	अगर (machine_is_davinci_dm6467tevm())
		davinci_nand_data.timing = &dm6467tevm_nandflash_timing;

	अगर (platक्रमm_device_रेजिस्टर(&davinci_aemअगर_device))
		pr_warn("%s: Cannot register AEMIF device.\n", __func__);

	dm646x_init_edma(dm646x_edma_rsv);

	अगर (HAS_ATA)
		davinci_init_ide();

	soc_info->emac_pdata->phy_id = DM646X_EVM_PHY_ID;
पूर्ण

MACHINE_START(DAVINCI_DM6467_EVM, "DaVinci DM646x EVM")
	.atag_offset  = 0x100,
	.map_io       = davinci_map_io,
	.init_irq     = dm646x_init_irq,
	.init_समय	= dm646x_evm_init_समय,
	.init_machine = evm_init,
	.init_late	= davinci_init_late,
	.dma_zone_size	= SZ_128M,
MACHINE_END

MACHINE_START(DAVINCI_DM6467TEVM, "DaVinci DM6467T EVM")
	.atag_offset  = 0x100,
	.map_io       = davinci_map_io,
	.init_irq     = dm646x_init_irq,
	.init_समय	= dm6467t_evm_init_समय,
	.init_machine = evm_init,
	.init_late	= davinci_init_late,
	.dma_zone_size	= SZ_128M,
MACHINE_END

