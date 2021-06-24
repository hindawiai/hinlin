<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Speyside modules क्रम Cragganmore - board data probing
//
// Copyright 2011 Wolfson Microelectronics plc
//	Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpio/machine.h>

#समावेश <linux/mfd/wm831x/irq.h>
#समावेश <linux/mfd/wm831x/gpपन.स>
#समावेश <linux/mfd/wm8994/pdata.h>
#समावेश <linux/mfd/arizona/pdata.h>

#समावेश <linux/regulator/machine.h>

#समावेश <sound/wm0010.h>
#समावेश <sound/wm2200.h>
#समावेश <sound/wm5100.h>
#समावेश <sound/wm8996.h>
#समावेश <sound/wm8962.h>
#समावेश <sound/wm9081.h>

#समावेश <linux/platक्रमm_data/spi-s3c64xx.h>

#समावेश "cpu.h"
#समावेश <mach/irqs.h>

#समावेश "crag6410.h"

अटल काष्ठा s3c64xx_spi_csinfo wm0010_spi_csinfo = अणु
	.line = S3C64XX_GPC(3),
पूर्ण;

अटल काष्ठा wm0010_pdata wm0010_pdata = अणु
	.gpio_reset = S3C64XX_GPN(6),
	.reset_active_high = 1, /* Active high क्रम Glenfarclas Rev 2 */
पूर्ण;

अटल काष्ठा spi_board_info wm1253_devs[] = अणु
	[0] = अणु
		.modalias	= "wm0010",
		.max_speed_hz	= 26 * 1000 * 1000,
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_0,
		.irq		= S3C_EINT(4),
		.controller_data = &wm0010_spi_csinfo,
		.platक्रमm_data = &wm0010_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा spi_board_info balblair_devs[] = अणु
	[0] = अणु
		.modalias	= "wm0010",
		.max_speed_hz	= 26 * 1000 * 1000,
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_0,
		.irq		= S3C_EINT(4),
		.controller_data = &wm0010_spi_csinfo,
		.platक्रमm_data = &wm0010_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा wm5100_pdata wm5100_pdata = अणु
	.lकरो_ena = S3C64XX_GPN(7),
	.irq_flags = IRQF_TRIGGER_HIGH,
	.gpio_base = CODEC_GPIO_BASE,

	.in_mode = अणु
		WM5100_IN_DIFF,
		WM5100_IN_DIFF,
		WM5100_IN_DIFF,
		WM5100_IN_SE,
	पूर्ण,

	.hp_pol = CODEC_GPIO_BASE + 3,
	.jack_modes = अणु
		अणु WM5100_MICDET_MICBIAS3, 0, 0 पूर्ण,
		अणु WM5100_MICDET_MICBIAS2, 1, 1 पूर्ण,
	पूर्ण,

	.gpio_शेषs = अणु
		0,
		0,
		0,
		0,
		0x2, /* IRQ: CMOS output */
		0x3, /* CLKOUT: CMOS output */
	पूर्ण,
पूर्ण;

अटल काष्ठा wm8996_retune_mobile_config wm8996_retune[] = अणु
	अणु
		.name = "Sub LPF",
		.rate = 48000,
		.regs = अणु
			0x6318, 0x6300, 0x1000, 0x0000, 0x0004, 0x2000, 0xF000,
			0x0000, 0x0004, 0x2000, 0xF000, 0x0000, 0x0004, 0x2000,
			0xF000, 0x0000, 0x0004, 0x1000, 0x0800, 0x4000
		पूर्ण,
	पूर्ण,
	अणु
		.name = "Sub HPF",
		.rate = 48000,
		.regs = अणु
			0x000A, 0x6300, 0x1000, 0x0000, 0x0004, 0x2000, 0xF000,
			0x0000, 0x0004, 0x2000, 0xF000, 0x0000, 0x0004, 0x2000,
			0xF000, 0x0000, 0x0004, 0x1000, 0x0800, 0x4000
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा wm8996_pdata wm8996_pdata __initdata = अणु
	.lकरो_ena = S3C64XX_GPN(7),
	.gpio_base = CODEC_GPIO_BASE,
	.micdet_def = 1,
	.inl_mode = WM8996_DIFFERRENTIAL_1,
	.inr_mode = WM8996_DIFFERRENTIAL_1,

	.irq_flags = IRQF_TRIGGER_RISING,

	.gpio_शेष = अणु
		0x8001, /* GPIO1 == ADCLRCLK1 */
		0x8001, /* GPIO2 == ADCLRCLK2, input due to CPU */
		0x0141, /* GPIO3 == HP_SEL */
		0x0002, /* GPIO4 == IRQ */
		0x020e, /* GPIO5 == CLKOUT */
	पूर्ण,

	.retune_mobile_cfgs = wm8996_retune,
	.num_retune_mobile_cfgs = ARRAY_SIZE(wm8996_retune),
पूर्ण;

अटल काष्ठा wm8962_pdata wm8962_pdata __initdata = अणु
	.gpio_init = अणु
		0,
		WM8962_GPIO_FN_OPCLK,
		WM8962_GPIO_FN_DMICCLK,
		0,
		0x8000 | WM8962_GPIO_FN_DMICDAT,
		WM8962_GPIO_FN_IRQ,    /* Open drain mode */
	पूर्ण,
	.in4_dc_measure = true,
पूर्ण;

अटल काष्ठा wm9081_pdata wm9081_pdata __initdata = अणु
	.irq_high = false,
	.irq_cmos = false,
पूर्ण;

अटल स्थिर काष्ठा i2c_board_info wm1254_devs[] = अणु
	अणु I2C_BOARD_INFO("wm8996", 0x1a),
	  .platक्रमm_data = &wm8996_pdata,
	  .irq = GLENFARCLAS_PMIC_IRQ_BASE + WM831X_IRQ_GPIO_2,
	पूर्ण,
	अणु I2C_BOARD_INFO("wm9081", 0x6c),
	  .platक्रमm_data = &wm9081_pdata, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_board_info wm1255_devs[] = अणु
	अणु I2C_BOARD_INFO("wm5100", 0x1a),
	  .platक्रमm_data = &wm5100_pdata,
	  .irq = GLENFARCLAS_PMIC_IRQ_BASE + WM831X_IRQ_GPIO_2,
	पूर्ण,
	अणु I2C_BOARD_INFO("wm9081", 0x6c),
	  .platक्रमm_data = &wm9081_pdata, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_board_info wm1259_devs[] = अणु
	अणु I2C_BOARD_INFO("wm8962", 0x1a),
	  .platक्रमm_data = &wm8962_pdata,
	  .irq = GLENFARCLAS_PMIC_IRQ_BASE + WM831X_IRQ_GPIO_2,
	पूर्ण,
पूर्ण;

अटल काष्ठा regulator_init_data wm8994_lकरो1 = अणु
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा regulator_init_data wm8994_lकरो2 = अणु
	.supply_regulator = "WALLVDD",
पूर्ण;

अटल काष्ठा wm8994_pdata wm8994_pdata = अणु
	.gpio_base = CODEC_GPIO_BASE,
	.micb2_delay = 150,
	.gpio_शेषs = अणु
		0x3,          /* IRQ out, active high, CMOS */
	पूर्ण,
	.lकरो = अणु
		 अणु .init_data = &wm8994_lकरो1, पूर्ण,
		 अणु .init_data = &wm8994_lकरो2, पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_board_info wm1277_devs[] = अणु
	अणु I2C_BOARD_INFO("wm8958", 0x1a),  /* WM8958 is the superset */
	  .platक्रमm_data = &wm8994_pdata,
	  .irq = GLENFARCLAS_PMIC_IRQ_BASE + WM831X_IRQ_GPIO_2,
	  .dev_name = "wm8958",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table wm8994_gpiod_table = अणु
	.dev_id = "i2c-wm8958", /* I2C device name */
	.table = अणु
		GPIO_LOOKUP("GPION", 6,
			    "wlf,ldo1ena", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("GPION", 4,
			    "wlf,ldo2ena", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा arizona_pdata wm5102_reva_pdata = अणु
	.gpio_base = CODEC_GPIO_BASE,
	.irq_flags = IRQF_TRIGGER_HIGH,
	.micd_pol_gpio = CODEC_GPIO_BASE + 4,
	.micd_rate = 6,
	.gpio_शेषs = अणु
		[2] = 0x10000, /* AIF3TXLRCLK */
		[3] = 0x4,     /* OPCLK */
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c64xx_spi_csinfo codec_spi_csinfo = अणु
	.line = S3C64XX_GPN(5),
पूर्ण;

अटल काष्ठा spi_board_info wm5102_reva_spi_devs[] = अणु
	[0] = अणु
		.modalias	= "wm5102",
		.max_speed_hz	= 10 * 1000 * 1000,
		.bus_num	= 0,
		.chip_select	= 1,
		.mode		= SPI_MODE_0,
		.irq		= GLENFARCLAS_PMIC_IRQ_BASE +
				  WM831X_IRQ_GPIO_2,
		.controller_data = &codec_spi_csinfo,
		.platक्रमm_data = &wm5102_reva_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table wm5102_reva_gpiod_table = अणु
	.dev_id = "spi0.1", /* SPI device name */
	.table = अणु
		GPIO_LOOKUP("GPION", 7,
			    "wlf,ldoena", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा arizona_pdata wm5102_pdata = अणु
	.gpio_base = CODEC_GPIO_BASE,
	.irq_flags = IRQF_TRIGGER_HIGH,
	.micd_pol_gpio = CODEC_GPIO_BASE + 2,
	.gpio_शेषs = अणु
		[2] = 0x10000, /* AIF3TXLRCLK */
		[3] = 0x4,     /* OPCLK */
	पूर्ण,
पूर्ण;

अटल काष्ठा spi_board_info wm5102_spi_devs[] = अणु
	[0] = अणु
		.modalias	= "wm5102",
		.max_speed_hz	= 10 * 1000 * 1000,
		.bus_num	= 0,
		.chip_select	= 1,
		.mode		= SPI_MODE_0,
		.irq		= GLENFARCLAS_PMIC_IRQ_BASE +
				  WM831X_IRQ_GPIO_2,
		.controller_data = &codec_spi_csinfo,
		.platक्रमm_data = &wm5102_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table wm5102_gpiod_table = अणु
	.dev_id = "spi0.1", /* SPI device name */
	.table = अणु
		GPIO_LOOKUP("GPION", 7,
			    "wlf,ldo1ena", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spi_board_info wm5110_spi_devs[] = अणु
	[0] = अणु
		.modalias	= "wm5110",
		.max_speed_hz	= 10 * 1000 * 1000,
		.bus_num	= 0,
		.chip_select	= 1,
		.mode		= SPI_MODE_0,
		.irq		= GLENFARCLAS_PMIC_IRQ_BASE +
				  WM831X_IRQ_GPIO_2,
		.controller_data = &codec_spi_csinfo,
		.platक्रमm_data = &wm5102_reva_pdata,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_board_info wm6230_i2c_devs[] = अणु
	अणु I2C_BOARD_INFO("wm9081", 0x6c),
	  .platक्रमm_data = &wm9081_pdata, पूर्ण,
पूर्ण;

अटल काष्ठा wm2200_pdata wm2200_pdata = अणु
	.lकरो_ena = S3C64XX_GPN(7),
	.gpio_शेषs = अणु
		[2] = 0x0005,  /* GPIO3 24.576MHz output घड़ी */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_board_info wm2200_i2c[] = अणु
	अणु I2C_BOARD_INFO("wm2200", 0x3a),
	  .platक्रमm_data = &wm2200_pdata, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	u8 id;
	u8 rev;
	स्थिर अक्षर *name;
	स्थिर काष्ठा i2c_board_info *i2c_devs;
	पूर्णांक num_i2c_devs;
	स्थिर काष्ठा spi_board_info *spi_devs;
	पूर्णांक num_spi_devs;

	काष्ठा gpiod_lookup_table *gpiod_table;
पूर्ण gf_mods[] = अणु
	अणु .id = 0x01, .rev = 0xff, .name = "1250-EV1 Springbank" पूर्ण,
	अणु .id = 0x02, .rev = 0xff, .name = "1251-EV1 Jura" पूर्ण,
	अणु .id = 0x03, .rev = 0xff, .name = "1252-EV1 Glenlivet" पूर्ण,
	अणु .id = 0x06, .rev = 0xff, .name = "WM8997-6721-CS96-EV1 Lapraoig" पूर्ण,
	अणु .id = 0x07, .rev = 0xff, .name = "WM5110-6271 Deanston",
	  .spi_devs = wm5110_spi_devs,
	  .num_spi_devs = ARRAY_SIZE(wm5110_spi_devs) पूर्ण,
	अणु .id = 0x08, .rev = 0xff, .name = "WM8903-6102 Tamdhu" पूर्ण,
	अणु .id = 0x09, .rev = 0xff, .name = "WM1811A-6305 Adelphi" पूर्ण,
	अणु .id = 0x0a, .rev = 0xff, .name = "WM8996-6272 Blackadder" पूर्ण,
	अणु .id = 0x0b, .rev = 0xff, .name = "WM8994-6235 Benromach" पूर्ण,
	अणु .id = 0x11, .rev = 0xff, .name = "6249-EV2 Glenfarclas", पूर्ण,
	अणु .id = 0x14, .rev = 0xff, .name = "6271-EV1 Lochnagar" पूर्ण,
	अणु .id = 0x15, .rev = 0xff, .name = "6320-EV1 Bells",
	  .i2c_devs = wm6230_i2c_devs,
	  .num_i2c_devs = ARRAY_SIZE(wm6230_i2c_devs) पूर्ण,
	अणु .id = 0x21, .rev = 0xff, .name = "1275-EV1 Mortlach" पूर्ण,
	अणु .id = 0x25, .rev = 0xff, .name = "1274-EV1 Glencadam" पूर्ण,
	अणु .id = 0x31, .rev = 0xff, .name = "1253-EV1 Tomatin",
	  .spi_devs = wm1253_devs, .num_spi_devs = ARRAY_SIZE(wm1253_devs) पूर्ण,
	अणु .id = 0x32, .rev = 0xff, .name = "XXXX-EV1 Caol Illa" पूर्ण,
	अणु .id = 0x33, .rev = 0xff, .name = "XXXX-EV1 Oban" पूर्ण,
	अणु .id = 0x34, .rev = 0xff, .name = "WM0010-6320-CS42 Balblair",
	  .spi_devs = balblair_devs,
	  .num_spi_devs = ARRAY_SIZE(balblair_devs) पूर्ण,
	अणु .id = 0x39, .rev = 0xff, .name = "1254-EV1 Dallas Dhu",
	  .i2c_devs = wm1254_devs, .num_i2c_devs = ARRAY_SIZE(wm1254_devs) पूर्ण,
	अणु .id = 0x3a, .rev = 0xff, .name = "1259-EV1 Tobermory",
	  .i2c_devs = wm1259_devs, .num_i2c_devs = ARRAY_SIZE(wm1259_devs) पूर्ण,
	अणु .id = 0x3b, .rev = 0xff, .name = "1255-EV1 Kilchoman",
	  .i2c_devs = wm1255_devs, .num_i2c_devs = ARRAY_SIZE(wm1255_devs) पूर्ण,
	अणु .id = 0x3c, .rev = 0xff, .name = "1273-EV1 Longmorn" पूर्ण,
	अणु .id = 0x3d, .rev = 0xff, .name = "1277-EV1 Littlemill",
	  .i2c_devs = wm1277_devs, .num_i2c_devs = ARRAY_SIZE(wm1277_devs),
	  .gpiod_table = &wm8994_gpiod_table पूर्ण,
	अणु .id = 0x3e, .rev = 0, .name = "WM5102-6271-EV1-CS127 Amrut",
	  .spi_devs = wm5102_reva_spi_devs,
	  .num_spi_devs = ARRAY_SIZE(wm5102_reva_spi_devs),
	  .gpiod_table = &wm5102_reva_gpiod_table पूर्ण,
	अणु .id = 0x3e, .rev = -1, .name = "WM5102-6271-EV1-CS127 Amrut",
	  .spi_devs = wm5102_spi_devs,
	  .num_spi_devs = ARRAY_SIZE(wm5102_spi_devs),
	  .gpiod_table = &wm5102_gpiod_table पूर्ण,
	अणु .id = 0x3f, .rev = -1, .name = "WM2200-6271-CS90-M-REV1",
	  .i2c_devs = wm2200_i2c, .num_i2c_devs = ARRAY_SIZE(wm2200_i2c) पूर्ण,
पूर्ण;

अटल पूर्णांक wlf_gf_module_probe(काष्ठा i2c_client *i2c)
अणु
	पूर्णांक ret, i, j, id, rev;

	ret = i2c_smbus_पढ़ो_byte_data(i2c, 0);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read ID: %d\n", ret);
		वापस ret;
	पूर्ण

	id = (ret & 0xfe) >> 2;
	rev = ret & 0x3;
	क्रम (i = 0; i < ARRAY_SIZE(gf_mods); i++)
		अगर (id == gf_mods[i].id && (gf_mods[i].rev == 0xff ||
					    rev == gf_mods[i].rev))
			अवरोध;

	gpiod_add_lookup_table(&wm5102_reva_gpiod_table);
	gpiod_add_lookup_table(&wm5102_gpiod_table);
	gpiod_add_lookup_table(&wm8994_gpiod_table);

	अगर (i < ARRAY_SIZE(gf_mods)) अणु
		dev_info(&i2c->dev, "%s revision %d\n",
			 gf_mods[i].name, rev + 1);

		क्रम (j = 0; j < gf_mods[i].num_i2c_devs; j++) अणु
			अगर (IS_ERR(i2c_new_client_device(i2c->adapter,
							 &(gf_mods[i].i2c_devs[j]))))
				dev_err(&i2c->dev, "Failed to register\n");
		पूर्ण

		spi_रेजिस्टर_board_info(gf_mods[i].spi_devs,
					gf_mods[i].num_spi_devs);

		अगर (gf_mods[i].gpiod_table)
			gpiod_add_lookup_table(gf_mods[i].gpiod_table);
	पूर्ण अन्यथा अणु
		dev_warn(&i2c->dev, "Unknown module ID 0x%x revision %d\n",
			 id, rev + 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wlf_gf_module_id[] = अणु
	अणु "wlf-gf-module", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver wlf_gf_module_driver = अणु
	.driver = अणु
		.name = "wlf-gf-module"
	पूर्ण,
	.probe_new = wlf_gf_module_probe,
	.id_table = wlf_gf_module_id,
पूर्ण;

अटल पूर्णांक __init wlf_gf_module_रेजिस्टर(व्योम)
अणु
	अगर (!soc_is_s3c64xx())
		वापस 0;

	वापस i2c_add_driver(&wlf_gf_module_driver);
पूर्ण
device_initcall(wlf_gf_module_रेजिस्टर);
