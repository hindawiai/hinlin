<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * EEPROMs access control driver क्रम display configuration EEPROMs
 * on DigsyMTC board.
 *
 * (C) 2011 DENX Software Engineering, Anम_से_दij Gustschin <agust@denx.de>
 *
 * FIXME: this driver is used on a device-tree probed platक्रमm: it
 * should be defined as a bit-banged SPI device and probed from the device
 * tree and not like this with अटल grabbing of a few numbered GPIO
 * lines at अक्रमom.
 *
 * Add proper SPI and EEPROM in arch/घातerpc/boot/dts/digsy_mtc.dts
 * and delete this driver.
 */

#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_gpपन.स>
#समावेश <linux/eeprom_93xx46.h>

#घोषणा GPIO_EEPROM_CLK		216
#घोषणा GPIO_EEPROM_CS		210
#घोषणा GPIO_EEPROM_DI		217
#घोषणा GPIO_EEPROM_DO		249
#घोषणा GPIO_EEPROM_OE		255
#घोषणा EE_SPI_BUS_NUM	1

अटल व्योम digsy_mtc_op_prepare(व्योम *p)
अणु
	/* enable */
	gpio_set_value(GPIO_EEPROM_OE, 0);
पूर्ण

अटल व्योम digsy_mtc_op_finish(व्योम *p)
अणु
	/* disable */
	gpio_set_value(GPIO_EEPROM_OE, 1);
पूर्ण

काष्ठा eeprom_93xx46_platक्रमm_data digsy_mtc_eeprom_data = अणु
	.flags		= EE_ADDR8,
	.prepare	= digsy_mtc_op_prepare,
	.finish		= digsy_mtc_op_finish,
पूर्ण;

अटल काष्ठा spi_gpio_platक्रमm_data eeprom_spi_gpio_data = अणु
	.num_chipselect	= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device digsy_mtc_eeprom = अणु
	.name	= "spi_gpio",
	.id	= EE_SPI_BUS_NUM,
	.dev	= अणु
		.platक्रमm_data	= &eeprom_spi_gpio_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table eeprom_spi_gpiod_table = अणु
	.dev_id         = "spi_gpio",
	.table          = अणु
		GPIO_LOOKUP("gpio@b00", GPIO_EEPROM_CLK,
			    "sck", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio@b00", GPIO_EEPROM_DI,
			    "mosi", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio@b00", GPIO_EEPROM_DO,
			    "miso", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio@b00", GPIO_EEPROM_CS,
			    "cs", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spi_board_info digsy_mtc_eeprom_info[] __initdata = अणु
	अणु
		.modalias		= "93xx46",
		.max_speed_hz		= 1000000,
		.bus_num		= EE_SPI_BUS_NUM,
		.chip_select		= 0,
		.mode			= SPI_MODE_0,
		.platक्रमm_data		= &digsy_mtc_eeprom_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init digsy_mtc_eeprom_devices_init(व्योम)
अणु
	पूर्णांक ret;

	ret = gpio_request_one(GPIO_EEPROM_OE, GPIOF_OUT_INIT_HIGH,
				"93xx46 EEPROMs OE");
	अगर (ret) अणु
		pr_err("can't request gpio %d\n", GPIO_EEPROM_OE);
		वापस ret;
	पूर्ण
	gpiod_add_lookup_table(&eeprom_spi_gpiod_table);
	spi_रेजिस्टर_board_info(digsy_mtc_eeprom_info,
				ARRAY_SIZE(digsy_mtc_eeprom_info));
	वापस platक्रमm_device_रेजिस्टर(&digsy_mtc_eeprom);
पूर्ण
device_initcall(digsy_mtc_eeprom_devices_init);
