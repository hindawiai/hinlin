<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Nano River Technologies viperboard GPIO lib driver
 *
 *  (C) 2012 by Lemonage GmbH
 *  Author: Lars Poeschel <poeschel@lemonage.de>
 *  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb.h>
#समावेश <linux/gpio/driver.h>

#समावेश <linux/mfd/viperboard.h>

#घोषणा VPRBRD_GPIOA_CLK_1MHZ		0
#घोषणा VPRBRD_GPIOA_CLK_100KHZ		1
#घोषणा VPRBRD_GPIOA_CLK_10KHZ		2
#घोषणा VPRBRD_GPIOA_CLK_1KHZ		3
#घोषणा VPRBRD_GPIOA_CLK_100HZ		4
#घोषणा VPRBRD_GPIOA_CLK_10HZ		5

#घोषणा VPRBRD_GPIOA_FREQ_DEFAULT	1000

#घोषणा VPRBRD_GPIOA_CMD_CONT		0x00
#घोषणा VPRBRD_GPIOA_CMD_PULSE		0x01
#घोषणा VPRBRD_GPIOA_CMD_PWM		0x02
#घोषणा VPRBRD_GPIOA_CMD_SETOUT		0x03
#घोषणा VPRBRD_GPIOA_CMD_SETIN		0x04
#घोषणा VPRBRD_GPIOA_CMD_SETINT		0x05
#घोषणा VPRBRD_GPIOA_CMD_GETIN		0x06

#घोषणा VPRBRD_GPIOB_CMD_SETसूची		0x00
#घोषणा VPRBRD_GPIOB_CMD_SETVAL		0x01

काष्ठा vprbrd_gpioa_msg अणु
	u8 cmd;
	u8 clk;
	u8 offset;
	u8 t1;
	u8 t2;
	u8 invert;
	u8 pwmlevel;
	u8 outval;
	u8 risefall;
	u8 answer;
	u8 __fill;
पूर्ण __packed;

काष्ठा vprbrd_gpiob_msg अणु
	u8 cmd;
	u16 val;
	u16 mask;
पूर्ण __packed;

काष्ठा vprbrd_gpio अणु
	काष्ठा gpio_chip gpioa; /* gpio a related things */
	u32 gpioa_out;
	u32 gpioa_val;
	काष्ठा gpio_chip gpiob; /* gpio b related things */
	u32 gpiob_out;
	u32 gpiob_val;
	काष्ठा vprbrd *vb;
पूर्ण;

/* gpioa sampling घड़ी module parameter */
अटल अचिन्हित अक्षर gpioa_clk;
अटल अचिन्हित पूर्णांक gpioa_freq = VPRBRD_GPIOA_FREQ_DEFAULT;
module_param(gpioa_freq, uपूर्णांक, 0);
MODULE_PARM_DESC(gpioa_freq,
	"gpio-a sampling freq in Hz (default is 1000Hz) valid values: 10, 100, 1000, 10000, 100000, 1000000");

/* ----- begin of gipo a chip -------------------------------------------- */

अटल पूर्णांक vprbrd_gpioa_get(काष्ठा gpio_chip *chip,
		अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret, answer, error = 0;
	काष्ठा vprbrd_gpio *gpio = gpiochip_get_data(chip);
	काष्ठा vprbrd *vb = gpio->vb;
	काष्ठा vprbrd_gpioa_msg *gamsg = (काष्ठा vprbrd_gpioa_msg *)vb->buf;

	/* अगर io is set to output, just वापस the saved value */
	अगर (gpio->gpioa_out & (1 << offset))
		वापस !!(gpio->gpioa_val & (1 << offset));

	mutex_lock(&vb->lock);

	gamsg->cmd = VPRBRD_GPIOA_CMD_GETIN;
	gamsg->clk = 0x00;
	gamsg->offset = offset;
	gamsg->t1 = 0x00;
	gamsg->t2 = 0x00;
	gamsg->invert = 0x00;
	gamsg->pwmlevel = 0x00;
	gamsg->outval = 0x00;
	gamsg->risefall = 0x00;
	gamsg->answer = 0x00;
	gamsg->__fill = 0x00;

	ret = usb_control_msg(vb->usb_dev, usb_sndctrlpipe(vb->usb_dev, 0),
		VPRBRD_USB_REQUEST_GPIOA, VPRBRD_USB_TYPE_OUT, 0x0000,
		0x0000, gamsg, माप(काष्ठा vprbrd_gpioa_msg),
		VPRBRD_USB_TIMEOUT_MS);
	अगर (ret != माप(काष्ठा vprbrd_gpioa_msg))
		error = -EREMOTEIO;

	ret = usb_control_msg(vb->usb_dev, usb_rcvctrlpipe(vb->usb_dev, 0),
		VPRBRD_USB_REQUEST_GPIOA, VPRBRD_USB_TYPE_IN, 0x0000,
		0x0000, gamsg, माप(काष्ठा vprbrd_gpioa_msg),
		VPRBRD_USB_TIMEOUT_MS);
	answer = gamsg->answer & 0x01;

	mutex_unlock(&vb->lock);

	अगर (ret != माप(काष्ठा vprbrd_gpioa_msg))
		error = -EREMOTEIO;

	अगर (error)
		वापस error;

	वापस answer;
पूर्ण

अटल व्योम vprbrd_gpioa_set(काष्ठा gpio_chip *chip,
		अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	पूर्णांक ret;
	काष्ठा vprbrd_gpio *gpio = gpiochip_get_data(chip);
	काष्ठा vprbrd *vb = gpio->vb;
	काष्ठा vprbrd_gpioa_msg *gamsg = (काष्ठा vprbrd_gpioa_msg *)vb->buf;

	अगर (gpio->gpioa_out & (1 << offset)) अणु
		अगर (value)
			gpio->gpioa_val |= (1 << offset);
		अन्यथा
			gpio->gpioa_val &= ~(1 << offset);

		mutex_lock(&vb->lock);

		gamsg->cmd = VPRBRD_GPIOA_CMD_SETOUT;
		gamsg->clk = 0x00;
		gamsg->offset = offset;
		gamsg->t1 = 0x00;
		gamsg->t2 = 0x00;
		gamsg->invert = 0x00;
		gamsg->pwmlevel = 0x00;
		gamsg->outval = value;
		gamsg->risefall = 0x00;
		gamsg->answer = 0x00;
		gamsg->__fill = 0x00;

		ret = usb_control_msg(vb->usb_dev,
			usb_sndctrlpipe(vb->usb_dev, 0),
			VPRBRD_USB_REQUEST_GPIOA, VPRBRD_USB_TYPE_OUT,
			0x0000,	0x0000, gamsg,
			माप(काष्ठा vprbrd_gpioa_msg), VPRBRD_USB_TIMEOUT_MS);

		mutex_unlock(&vb->lock);

		अगर (ret != माप(काष्ठा vprbrd_gpioa_msg))
			dev_err(chip->parent, "usb error setting pin value\n");
	पूर्ण
पूर्ण

अटल पूर्णांक vprbrd_gpioa_direction_input(काष्ठा gpio_chip *chip,
			अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	काष्ठा vprbrd_gpio *gpio = gpiochip_get_data(chip);
	काष्ठा vprbrd *vb = gpio->vb;
	काष्ठा vprbrd_gpioa_msg *gamsg = (काष्ठा vprbrd_gpioa_msg *)vb->buf;

	gpio->gpioa_out &= ~(1 << offset);

	mutex_lock(&vb->lock);

	gamsg->cmd = VPRBRD_GPIOA_CMD_SETIN;
	gamsg->clk = gpioa_clk;
	gamsg->offset = offset;
	gamsg->t1 = 0x00;
	gamsg->t2 = 0x00;
	gamsg->invert = 0x00;
	gamsg->pwmlevel = 0x00;
	gamsg->outval = 0x00;
	gamsg->risefall = 0x00;
	gamsg->answer = 0x00;
	gamsg->__fill = 0x00;

	ret = usb_control_msg(vb->usb_dev, usb_sndctrlpipe(vb->usb_dev, 0),
		VPRBRD_USB_REQUEST_GPIOA, VPRBRD_USB_TYPE_OUT, 0x0000,
		0x0000, gamsg, माप(काष्ठा vprbrd_gpioa_msg),
		VPRBRD_USB_TIMEOUT_MS);

	mutex_unlock(&vb->lock);

	अगर (ret != माप(काष्ठा vprbrd_gpioa_msg))
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण

अटल पूर्णांक vprbrd_gpioa_direction_output(काष्ठा gpio_chip *chip,
			अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	पूर्णांक ret;
	काष्ठा vprbrd_gpio *gpio = gpiochip_get_data(chip);
	काष्ठा vprbrd *vb = gpio->vb;
	काष्ठा vprbrd_gpioa_msg *gamsg = (काष्ठा vprbrd_gpioa_msg *)vb->buf;

	gpio->gpioa_out |= (1 << offset);
	अगर (value)
		gpio->gpioa_val |= (1 << offset);
	अन्यथा
		gpio->gpioa_val &= ~(1 << offset);

	mutex_lock(&vb->lock);

	gamsg->cmd = VPRBRD_GPIOA_CMD_SETOUT;
	gamsg->clk = 0x00;
	gamsg->offset = offset;
	gamsg->t1 = 0x00;
	gamsg->t2 = 0x00;
	gamsg->invert = 0x00;
	gamsg->pwmlevel = 0x00;
	gamsg->outval = value;
	gamsg->risefall = 0x00;
	gamsg->answer = 0x00;
	gamsg->__fill = 0x00;

	ret = usb_control_msg(vb->usb_dev, usb_sndctrlpipe(vb->usb_dev, 0),
		VPRBRD_USB_REQUEST_GPIOA, VPRBRD_USB_TYPE_OUT, 0x0000,
		0x0000, gamsg, माप(काष्ठा vprbrd_gpioa_msg),
		VPRBRD_USB_TIMEOUT_MS);

	mutex_unlock(&vb->lock);

	अगर (ret != माप(काष्ठा vprbrd_gpioa_msg))
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण

/* ----- end of gpio a chip ---------------------------------------------- */

/* ----- begin of gipo b chip -------------------------------------------- */

अटल पूर्णांक vprbrd_gpiob_setdir(काष्ठा vprbrd *vb, अचिन्हित पूर्णांक offset,
	अचिन्हित पूर्णांक dir)
अणु
	काष्ठा vprbrd_gpiob_msg *gbmsg = (काष्ठा vprbrd_gpiob_msg *)vb->buf;
	पूर्णांक ret;

	gbmsg->cmd = VPRBRD_GPIOB_CMD_SETसूची;
	gbmsg->val = cpu_to_be16(dir << offset);
	gbmsg->mask = cpu_to_be16(0x0001 << offset);

	ret = usb_control_msg(vb->usb_dev, usb_sndctrlpipe(vb->usb_dev, 0),
		VPRBRD_USB_REQUEST_GPIOB, VPRBRD_USB_TYPE_OUT, 0x0000,
		0x0000, gbmsg, माप(काष्ठा vprbrd_gpiob_msg),
		VPRBRD_USB_TIMEOUT_MS);

	अगर (ret != माप(काष्ठा vprbrd_gpiob_msg))
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण

अटल पूर्णांक vprbrd_gpiob_get(काष्ठा gpio_chip *chip,
		अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	u16 val;
	काष्ठा vprbrd_gpio *gpio = gpiochip_get_data(chip);
	काष्ठा vprbrd *vb = gpio->vb;
	काष्ठा vprbrd_gpiob_msg *gbmsg = (काष्ठा vprbrd_gpiob_msg *)vb->buf;

	/* अगर io is set to output, just वापस the saved value */
	अगर (gpio->gpiob_out & (1 << offset))
		वापस gpio->gpiob_val & (1 << offset);

	mutex_lock(&vb->lock);

	ret = usb_control_msg(vb->usb_dev, usb_rcvctrlpipe(vb->usb_dev, 0),
		VPRBRD_USB_REQUEST_GPIOB, VPRBRD_USB_TYPE_IN, 0x0000,
		0x0000, gbmsg,	माप(काष्ठा vprbrd_gpiob_msg),
		VPRBRD_USB_TIMEOUT_MS);
	val = gbmsg->val;

	mutex_unlock(&vb->lock);

	अगर (ret != माप(काष्ठा vprbrd_gpiob_msg))
		वापस ret;

	/* cache the पढ़ो values */
	gpio->gpiob_val = be16_to_cpu(val);

	वापस (gpio->gpiob_val >> offset) & 0x1;
पूर्ण

अटल व्योम vprbrd_gpiob_set(काष्ठा gpio_chip *chip,
		अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	पूर्णांक ret;
	काष्ठा vprbrd_gpio *gpio = gpiochip_get_data(chip);
	काष्ठा vprbrd *vb = gpio->vb;
	काष्ठा vprbrd_gpiob_msg *gbmsg = (काष्ठा vprbrd_gpiob_msg *)vb->buf;

	अगर (gpio->gpiob_out & (1 << offset)) अणु
		अगर (value)
			gpio->gpiob_val |= (1 << offset);
		अन्यथा
			gpio->gpiob_val &= ~(1 << offset);

		mutex_lock(&vb->lock);

		gbmsg->cmd = VPRBRD_GPIOB_CMD_SETVAL;
		gbmsg->val = cpu_to_be16(value << offset);
		gbmsg->mask = cpu_to_be16(0x0001 << offset);

		ret = usb_control_msg(vb->usb_dev,
			usb_sndctrlpipe(vb->usb_dev, 0),
			VPRBRD_USB_REQUEST_GPIOB, VPRBRD_USB_TYPE_OUT,
			0x0000,	0x0000, gbmsg,
			माप(काष्ठा vprbrd_gpiob_msg), VPRBRD_USB_TIMEOUT_MS);

		mutex_unlock(&vb->lock);

		अगर (ret != माप(काष्ठा vprbrd_gpiob_msg))
			dev_err(chip->parent, "usb error setting pin value\n");
	पूर्ण
पूर्ण

अटल पूर्णांक vprbrd_gpiob_direction_input(काष्ठा gpio_chip *chip,
			अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	काष्ठा vprbrd_gpio *gpio = gpiochip_get_data(chip);
	काष्ठा vprbrd *vb = gpio->vb;

	gpio->gpiob_out &= ~(1 << offset);

	mutex_lock(&vb->lock);

	ret = vprbrd_gpiob_setdir(vb, offset, 0);

	mutex_unlock(&vb->lock);

	अगर (ret)
		dev_err(chip->parent, "usb error setting pin to input\n");

	वापस ret;
पूर्ण

अटल पूर्णांक vprbrd_gpiob_direction_output(काष्ठा gpio_chip *chip,
			अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	पूर्णांक ret;
	काष्ठा vprbrd_gpio *gpio = gpiochip_get_data(chip);
	काष्ठा vprbrd *vb = gpio->vb;

	gpio->gpiob_out |= (1 << offset);

	mutex_lock(&vb->lock);

	ret = vprbrd_gpiob_setdir(vb, offset, 1);
	अगर (ret)
		dev_err(chip->parent, "usb error setting pin to output\n");

	mutex_unlock(&vb->lock);

	vprbrd_gpiob_set(chip, offset, value);

	वापस ret;
पूर्ण

/* ----- end of gpio b chip ---------------------------------------------- */

अटल पूर्णांक vprbrd_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vprbrd *vb = dev_get_drvdata(pdev->dev.parent);
	काष्ठा vprbrd_gpio *vb_gpio;
	पूर्णांक ret;

	vb_gpio = devm_kzalloc(&pdev->dev, माप(*vb_gpio), GFP_KERNEL);
	अगर (vb_gpio == शून्य)
		वापस -ENOMEM;

	vb_gpio->vb = vb;
	/* रेजिस्टरing gpio a */
	vb_gpio->gpioa.label = "viperboard gpio a";
	vb_gpio->gpioa.parent = &pdev->dev;
	vb_gpio->gpioa.owner = THIS_MODULE;
	vb_gpio->gpioa.base = -1;
	vb_gpio->gpioa.ngpio = 16;
	vb_gpio->gpioa.can_sleep = true;
	vb_gpio->gpioa.set = vprbrd_gpioa_set;
	vb_gpio->gpioa.get = vprbrd_gpioa_get;
	vb_gpio->gpioa.direction_input = vprbrd_gpioa_direction_input;
	vb_gpio->gpioa.direction_output = vprbrd_gpioa_direction_output;
	ret = devm_gpiochip_add_data(&pdev->dev, &vb_gpio->gpioa, vb_gpio);
	अगर (ret < 0) अणु
		dev_err(vb_gpio->gpioa.parent, "could not add gpio a");
		वापस ret;
	पूर्ण

	/* रेजिस्टरing gpio b */
	vb_gpio->gpiob.label = "viperboard gpio b";
	vb_gpio->gpiob.parent = &pdev->dev;
	vb_gpio->gpiob.owner = THIS_MODULE;
	vb_gpio->gpiob.base = -1;
	vb_gpio->gpiob.ngpio = 16;
	vb_gpio->gpiob.can_sleep = true;
	vb_gpio->gpiob.set = vprbrd_gpiob_set;
	vb_gpio->gpiob.get = vprbrd_gpiob_get;
	vb_gpio->gpiob.direction_input = vprbrd_gpiob_direction_input;
	vb_gpio->gpiob.direction_output = vprbrd_gpiob_direction_output;
	ret = devm_gpiochip_add_data(&pdev->dev, &vb_gpio->gpiob, vb_gpio);
	अगर (ret < 0) अणु
		dev_err(vb_gpio->gpiob.parent, "could not add gpio b");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, vb_gpio);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver vprbrd_gpio_driver = अणु
	.driver.name	= "viperboard-gpio",
	.probe		= vprbrd_gpio_probe,
पूर्ण;

अटल पूर्णांक __init vprbrd_gpio_init(व्योम)
अणु
	चयन (gpioa_freq) अणु
	हाल 1000000:
		gpioa_clk = VPRBRD_GPIOA_CLK_1MHZ;
		अवरोध;
	हाल 100000:
		gpioa_clk = VPRBRD_GPIOA_CLK_100KHZ;
		अवरोध;
	हाल 10000:
		gpioa_clk = VPRBRD_GPIOA_CLK_10KHZ;
		अवरोध;
	हाल 1000:
		gpioa_clk = VPRBRD_GPIOA_CLK_1KHZ;
		अवरोध;
	हाल 100:
		gpioa_clk = VPRBRD_GPIOA_CLK_100HZ;
		अवरोध;
	हाल 10:
		gpioa_clk = VPRBRD_GPIOA_CLK_10HZ;
		अवरोध;
	शेष:
		pr_warn("invalid gpioa_freq (%d)\n", gpioa_freq);
		gpioa_clk = VPRBRD_GPIOA_CLK_1KHZ;
	पूर्ण

	वापस platक्रमm_driver_रेजिस्टर(&vprbrd_gpio_driver);
पूर्ण
subsys_initcall(vprbrd_gpio_init);

अटल व्योम __निकास vprbrd_gpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&vprbrd_gpio_driver);
पूर्ण
module_निकास(vprbrd_gpio_निकास);

MODULE_AUTHOR("Lars Poeschel <poeschel@lemonage.de>");
MODULE_DESCRIPTION("GPIO driver for Nano River Techs Viperboard");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:viperboard-gpio");
