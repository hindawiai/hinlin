<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TQ-Systems PLD MFD core driver, based on venकरोr driver by
 * Vadim V.Vlasov <vvlasov@dev.rtsoft.ru>
 *
 * Copyright (c) 2015 TQ-Systems GmbH
 * Copyright (c) 2019 Andrew Lunn <andrew@lunn.ch>
 */

#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/i2c-ocores.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा TQMX86_IOBASE	0x160
#घोषणा TQMX86_IOSIZE	0x3f
#घोषणा TQMX86_IOBASE_I2C	0x1a0
#घोषणा TQMX86_IOSIZE_I2C	0xa
#घोषणा TQMX86_IOBASE_WATCHDOG	0x18b
#घोषणा TQMX86_IOSIZE_WATCHDOG	0x2
#घोषणा TQMX86_IOBASE_GPIO	0x18d
#घोषणा TQMX86_IOSIZE_GPIO	0x4

#घोषणा TQMX86_REG_BOARD_ID	0x20
#घोषणा TQMX86_REG_BOARD_ID_E38M	1
#घोषणा TQMX86_REG_BOARD_ID_50UC	2
#घोषणा TQMX86_REG_BOARD_ID_E38C	3
#घोषणा TQMX86_REG_BOARD_ID_60EB	4
#घोषणा TQMX86_REG_BOARD_ID_E39M	5
#घोषणा TQMX86_REG_BOARD_ID_E39C	6
#घोषणा TQMX86_REG_BOARD_ID_E39x	7
#घोषणा TQMX86_REG_BOARD_ID_70EB	8
#घोषणा TQMX86_REG_BOARD_ID_80UC	9
#घोषणा TQMX86_REG_BOARD_ID_90UC	10
#घोषणा TQMX86_REG_BOARD_REV	0x21
#घोषणा TQMX86_REG_IO_EXT_INT	0x26
#घोषणा TQMX86_REG_IO_EXT_INT_NONE		0
#घोषणा TQMX86_REG_IO_EXT_INT_7			1
#घोषणा TQMX86_REG_IO_EXT_INT_9			2
#घोषणा TQMX86_REG_IO_EXT_INT_12		3
#घोषणा TQMX86_REG_IO_EXT_INT_MASK		0x3
#घोषणा TQMX86_REG_IO_EXT_INT_GPIO_SHIFT	4

#घोषणा TQMX86_REG_I2C_DETECT	0x47
#घोषणा TQMX86_REG_I2C_DETECT_SOFT		0xa5
#घोषणा TQMX86_REG_I2C_INT_EN	0x49

अटल uपूर्णांक gpio_irq;
module_param(gpio_irq, uपूर्णांक, 0);
MODULE_PARM_DESC(gpio_irq, "GPIO IRQ number (7, 9, 12)");

अटल स्थिर काष्ठा resource tqmx_i2c_soft_resources[] = अणु
	DEFINE_RES_IO(TQMX86_IOBASE_I2C, TQMX86_IOSIZE_I2C),
पूर्ण;

अटल स्थिर काष्ठा resource tqmx_watchकरोg_resources[] = अणु
	DEFINE_RES_IO(TQMX86_IOBASE_WATCHDOG, TQMX86_IOSIZE_WATCHDOG),
पूर्ण;

/*
 * The IRQ resource must be first, since it is updated with the
 * configured IRQ in the probe function.
 */
अटल काष्ठा resource tqmx_gpio_resources[] = अणु
	DEFINE_RES_IRQ(0),
	DEFINE_RES_IO(TQMX86_IOBASE_GPIO, TQMX86_IOSIZE_GPIO),
पूर्ण;

अटल काष्ठा i2c_board_info tqmx86_i2c_devices[] = अणु
	अणु
		/* 4K EEPROM at 0x50 */
		I2C_BOARD_INFO("24c32", 0x50),
	पूर्ण,
पूर्ण;

अटल काष्ठा ocores_i2c_platक्रमm_data ocores_platfom_data = अणु
	.num_devices = ARRAY_SIZE(tqmx86_i2c_devices),
	.devices = tqmx86_i2c_devices,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell tqmx86_i2c_soft_dev[] = अणु
	अणु
		.name = "ocores-i2c",
		.platक्रमm_data = &ocores_platfom_data,
		.pdata_size = माप(ocores_platfom_data),
		.resources = tqmx_i2c_soft_resources,
		.num_resources = ARRAY_SIZE(tqmx_i2c_soft_resources),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell tqmx86_devs[] = अणु
	अणु
		.name = "tqmx86-wdt",
		.resources = tqmx_watchकरोg_resources,
		.num_resources = ARRAY_SIZE(tqmx_watchकरोg_resources),
		.ignore_resource_conflicts = true,
	पूर्ण,
	अणु
		.name = "tqmx86-gpio",
		.resources = tqmx_gpio_resources,
		.num_resources = ARRAY_SIZE(tqmx_gpio_resources),
		.ignore_resource_conflicts = true,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *tqmx86_board_id_to_name(u8 board_id)
अणु
	चयन (board_id) अणु
	हाल TQMX86_REG_BOARD_ID_E38M:
		वापस "TQMxE38M";
	हाल TQMX86_REG_BOARD_ID_50UC:
		वापस "TQMx50UC";
	हाल TQMX86_REG_BOARD_ID_E38C:
		वापस "TQMxE38C";
	हाल TQMX86_REG_BOARD_ID_60EB:
		वापस "TQMx60EB";
	हाल TQMX86_REG_BOARD_ID_E39M:
		वापस "TQMxE39M";
	हाल TQMX86_REG_BOARD_ID_E39C:
		वापस "TQMxE39C";
	हाल TQMX86_REG_BOARD_ID_E39x:
		वापस "TQMxE39x";
	हाल TQMX86_REG_BOARD_ID_70EB:
		वापस "TQMx70EB";
	हाल TQMX86_REG_BOARD_ID_80UC:
		वापस "TQMx80UC";
	हाल TQMX86_REG_BOARD_ID_90UC:
		वापस "TQMx90UC";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक tqmx86_board_id_to_clk_rate(u8 board_id)
अणु
	चयन (board_id) अणु
	हाल TQMX86_REG_BOARD_ID_50UC:
	हाल TQMX86_REG_BOARD_ID_60EB:
	हाल TQMX86_REG_BOARD_ID_70EB:
	हाल TQMX86_REG_BOARD_ID_80UC:
	हाल TQMX86_REG_BOARD_ID_90UC:
		वापस 24000;
	हाल TQMX86_REG_BOARD_ID_E39M:
	हाल TQMX86_REG_BOARD_ID_E39C:
	हाल TQMX86_REG_BOARD_ID_E39x:
		वापस 25000;
	हाल TQMX86_REG_BOARD_ID_E38M:
	हाल TQMX86_REG_BOARD_ID_E38C:
		वापस 33000;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक tqmx86_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u8 board_id, rev, i2c_det, io_ext_पूर्णांक_val;
	काष्ठा device *dev = &pdev->dev;
	u8 gpio_irq_cfg, पढ़ोback;
	स्थिर अक्षर *board_name;
	व्योम __iomem *io_base;
	पूर्णांक err;

	चयन (gpio_irq) अणु
	हाल 0:
		gpio_irq_cfg = TQMX86_REG_IO_EXT_INT_NONE;
		अवरोध;
	हाल 7:
		gpio_irq_cfg = TQMX86_REG_IO_EXT_INT_7;
		अवरोध;
	हाल 9:
		gpio_irq_cfg = TQMX86_REG_IO_EXT_INT_9;
		अवरोध;
	हाल 12:
		gpio_irq_cfg = TQMX86_REG_IO_EXT_INT_12;
		अवरोध;
	शेष:
		pr_err("tqmx86: Invalid GPIO IRQ (%d)\n", gpio_irq);
		वापस -EINVAL;
	पूर्ण

	io_base = devm_ioport_map(dev, TQMX86_IOBASE, TQMX86_IOSIZE);
	अगर (!io_base)
		वापस -ENOMEM;

	board_id = ioपढ़ो8(io_base + TQMX86_REG_BOARD_ID);
	board_name = tqmx86_board_id_to_name(board_id);
	rev = ioपढ़ो8(io_base + TQMX86_REG_BOARD_REV);

	dev_info(dev,
		 "Found %s - Board ID %d, PCB Revision %d, PLD Revision %d\n",
		 board_name, board_id, rev >> 4, rev & 0xf);

	i2c_det = ioपढ़ो8(io_base + TQMX86_REG_I2C_DETECT);

	अगर (gpio_irq_cfg) अणु
		io_ext_पूर्णांक_val =
			gpio_irq_cfg << TQMX86_REG_IO_EXT_INT_GPIO_SHIFT;
		ioग_लिखो8(io_ext_पूर्णांक_val, io_base + TQMX86_REG_IO_EXT_INT);
		पढ़ोback = ioपढ़ो8(io_base + TQMX86_REG_IO_EXT_INT);
		अगर (पढ़ोback != io_ext_पूर्णांक_val) अणु
			dev_warn(dev, "GPIO interrupts not supported.\n");
			वापस -EINVAL;
		पूर्ण

		/* Assumes the IRQ resource is first. */
		tqmx_gpio_resources[0].start = gpio_irq;
	पूर्ण

	ocores_platfom_data.घड़ी_khz = tqmx86_board_id_to_clk_rate(board_id);

	अगर (i2c_det == TQMX86_REG_I2C_DETECT_SOFT) अणु
		err = devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
					   tqmx86_i2c_soft_dev,
					   ARRAY_SIZE(tqmx86_i2c_soft_dev),
					   शून्य, 0, शून्य);
		अगर (err)
			वापस err;
	पूर्ण

	वापस devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
				    tqmx86_devs,
				    ARRAY_SIZE(tqmx86_devs),
				    शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक tqmx86_create_platक्रमm_device(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक err;

	pdev = platक्रमm_device_alloc("tqmx86", -1);
	अगर (!pdev)
		वापस -ENOMEM;

	err = platक्रमm_device_add(pdev);
	अगर (err)
		platक्रमm_device_put(pdev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id tqmx86_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "TQMX86",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TQ-Group"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TQMx"),
		पूर्ण,
		.callback = tqmx86_create_platक्रमm_device,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, tqmx86_dmi_table);

अटल काष्ठा platक्रमm_driver tqmx86_driver = अणु
	.driver		= अणु
		.name	= "tqmx86",
	पूर्ण,
	.probe		= tqmx86_probe,
पूर्ण;

अटल पूर्णांक __init tqmx86_init(व्योम)
अणु
	अगर (!dmi_check_प्रणाली(tqmx86_dmi_table))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&tqmx86_driver);
पूर्ण

module_init(tqmx86_init);

MODULE_DESCRIPTION("TQMx86 PLD Core Driver");
MODULE_AUTHOR("Andrew Lunn <andrew@lunn.ch>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:tqmx86");
