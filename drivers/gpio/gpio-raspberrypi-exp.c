<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Raspberry Pi 3 expander GPIO driver
 *
 *  Uses the firmware mailbox service to communicate with the
 *  GPIO expander on the VPU.
 *
 *  Copyright (C) 2017 Raspberry Pi Trading Ltd.
 */

#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <soc/bcm2835/raspberrypi-firmware.h>

#घोषणा MODULE_NAME "raspberrypi-exp-gpio"
#घोषणा NUM_GPIO 8

#घोषणा RPI_EXP_GPIO_BASE	128

#घोषणा RPI_EXP_GPIO_सूची_IN	0
#घोषणा RPI_EXP_GPIO_सूची_OUT	1

काष्ठा rpi_exp_gpio अणु
	काष्ठा gpio_chip gc;
	काष्ठा rpi_firmware *fw;
पूर्ण;

/* VC4 firmware mailbox पूर्णांकerface data काष्ठाures */

काष्ठा gpio_set_config अणु
	u32 gpio;
	u32 direction;
	u32 polarity;
	u32 term_en;
	u32 term_pull_up;
	u32 state;
पूर्ण;

काष्ठा gpio_get_config अणु
	u32 gpio;
	u32 direction;
	u32 polarity;
	u32 term_en;
	u32 term_pull_up;
पूर्ण;

काष्ठा gpio_get_set_state अणु
	u32 gpio;
	u32 state;
पूर्ण;

अटल पूर्णांक rpi_exp_gpio_get_polarity(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक off)
अणु
	काष्ठा rpi_exp_gpio *gpio;
	काष्ठा gpio_get_config get;
	पूर्णांक ret;

	gpio = gpiochip_get_data(gc);

	get.gpio = off + RPI_EXP_GPIO_BASE;	/* GPIO to update */

	ret = rpi_firmware_property(gpio->fw, RPI_FIRMWARE_GET_GPIO_CONFIG,
				    &get, माप(get));
	अगर (ret || get.gpio != 0) अणु
		dev_err(gc->parent, "Failed to get GPIO %u config (%d %x)\n",
			off, ret, get.gpio);
		वापस ret ? ret : -EIO;
	पूर्ण
	वापस get.polarity;
पूर्ण

अटल पूर्णांक rpi_exp_gpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक off)
अणु
	काष्ठा rpi_exp_gpio *gpio;
	काष्ठा gpio_set_config set_in;
	पूर्णांक ret;

	gpio = gpiochip_get_data(gc);

	set_in.gpio = off + RPI_EXP_GPIO_BASE;	/* GPIO to update */
	set_in.direction = RPI_EXP_GPIO_सूची_IN;
	set_in.term_en = 0;		/* termination disabled */
	set_in.term_pull_up = 0;	/* n/a as termination disabled */
	set_in.state = 0;		/* n/a as configured as an input */

	ret = rpi_exp_gpio_get_polarity(gc, off);
	अगर (ret < 0)
		वापस ret;
	set_in.polarity = ret;		/* Retain existing setting */

	ret = rpi_firmware_property(gpio->fw, RPI_FIRMWARE_SET_GPIO_CONFIG,
				    &set_in, माप(set_in));
	अगर (ret || set_in.gpio != 0) अणु
		dev_err(gc->parent, "Failed to set GPIO %u to input (%d %x)\n",
			off, ret, set_in.gpio);
		वापस ret ? ret : -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rpi_exp_gpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक off, पूर्णांक val)
अणु
	काष्ठा rpi_exp_gpio *gpio;
	काष्ठा gpio_set_config set_out;
	पूर्णांक ret;

	gpio = gpiochip_get_data(gc);

	set_out.gpio = off + RPI_EXP_GPIO_BASE;	/* GPIO to update */
	set_out.direction = RPI_EXP_GPIO_सूची_OUT;
	set_out.term_en = 0;		/* n/a as an output */
	set_out.term_pull_up = 0;	/* n/a as termination disabled */
	set_out.state = val;		/* Output state */

	ret = rpi_exp_gpio_get_polarity(gc, off);
	अगर (ret < 0)
		वापस ret;
	set_out.polarity = ret;		/* Retain existing setting */

	ret = rpi_firmware_property(gpio->fw, RPI_FIRMWARE_SET_GPIO_CONFIG,
				    &set_out, माप(set_out));
	अगर (ret || set_out.gpio != 0) अणु
		dev_err(gc->parent, "Failed to set GPIO %u to output (%d %x)\n",
			off, ret, set_out.gpio);
		वापस ret ? ret : -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rpi_exp_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक off)
अणु
	काष्ठा rpi_exp_gpio *gpio;
	काष्ठा gpio_get_config get;
	पूर्णांक ret;

	gpio = gpiochip_get_data(gc);

	get.gpio = off + RPI_EXP_GPIO_BASE;	/* GPIO to update */

	ret = rpi_firmware_property(gpio->fw, RPI_FIRMWARE_GET_GPIO_CONFIG,
				    &get, माप(get));
	अगर (ret || get.gpio != 0) अणु
		dev_err(gc->parent,
			"Failed to get GPIO %u config (%d %x)\n", off, ret,
			get.gpio);
		वापस ret ? ret : -EIO;
	पूर्ण
	अगर (get.direction)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक rpi_exp_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक off)
अणु
	काष्ठा rpi_exp_gpio *gpio;
	काष्ठा gpio_get_set_state get;
	पूर्णांक ret;

	gpio = gpiochip_get_data(gc);

	get.gpio = off + RPI_EXP_GPIO_BASE;	/* GPIO to update */
	get.state = 0;		/* storage क्रम वापसed value */

	ret = rpi_firmware_property(gpio->fw, RPI_FIRMWARE_GET_GPIO_STATE,
					 &get, माप(get));
	अगर (ret || get.gpio != 0) अणु
		dev_err(gc->parent,
			"Failed to get GPIO %u state (%d %x)\n", off, ret,
			get.gpio);
		वापस ret ? ret : -EIO;
	पूर्ण
	वापस !!get.state;
पूर्ण

अटल व्योम rpi_exp_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक off, पूर्णांक val)
अणु
	काष्ठा rpi_exp_gpio *gpio;
	काष्ठा gpio_get_set_state set;
	पूर्णांक ret;

	gpio = gpiochip_get_data(gc);

	set.gpio = off + RPI_EXP_GPIO_BASE;	/* GPIO to update */
	set.state = val;	/* Output state */

	ret = rpi_firmware_property(gpio->fw, RPI_FIRMWARE_SET_GPIO_STATE,
					 &set, माप(set));
	अगर (ret || set.gpio != 0)
		dev_err(gc->parent,
			"Failed to set GPIO %u state (%d %x)\n", off, ret,
			set.gpio);
पूर्ण

अटल पूर्णांक rpi_exp_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *fw_node;
	काष्ठा rpi_firmware *fw;
	काष्ठा rpi_exp_gpio *rpi_gpio;

	fw_node = of_get_parent(np);
	अगर (!fw_node) अणु
		dev_err(dev, "Missing firmware node\n");
		वापस -ENOENT;
	पूर्ण

	fw = devm_rpi_firmware_get(&pdev->dev, fw_node);
	of_node_put(fw_node);
	अगर (!fw)
		वापस -EPROBE_DEFER;

	rpi_gpio = devm_kzalloc(dev, माप(*rpi_gpio), GFP_KERNEL);
	अगर (!rpi_gpio)
		वापस -ENOMEM;

	rpi_gpio->fw = fw;
	rpi_gpio->gc.parent = dev;
	rpi_gpio->gc.label = MODULE_NAME;
	rpi_gpio->gc.owner = THIS_MODULE;
	rpi_gpio->gc.of_node = np;
	rpi_gpio->gc.base = -1;
	rpi_gpio->gc.ngpio = NUM_GPIO;

	rpi_gpio->gc.direction_input = rpi_exp_gpio_dir_in;
	rpi_gpio->gc.direction_output = rpi_exp_gpio_dir_out;
	rpi_gpio->gc.get_direction = rpi_exp_gpio_get_direction;
	rpi_gpio->gc.get = rpi_exp_gpio_get;
	rpi_gpio->gc.set = rpi_exp_gpio_set;
	rpi_gpio->gc.can_sleep = true;

	वापस devm_gpiochip_add_data(dev, &rpi_gpio->gc, rpi_gpio);
पूर्ण

अटल स्थिर काष्ठा of_device_id rpi_exp_gpio_ids[] = अणु
	अणु .compatible = "raspberrypi,firmware-gpio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rpi_exp_gpio_ids);

अटल काष्ठा platक्रमm_driver rpi_exp_gpio_driver = अणु
	.driver	= अणु
		.name		= MODULE_NAME,
		.of_match_table	= of_match_ptr(rpi_exp_gpio_ids),
	पूर्ण,
	.probe	= rpi_exp_gpio_probe,
पूर्ण;
module_platक्रमm_driver(rpi_exp_gpio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dave Stevenson <dave.stevenson@raspberrypi.org>");
MODULE_DESCRIPTION("Raspberry Pi 3 expander GPIO driver");
MODULE_ALIAS("platform:rpi-exp-gpio");
