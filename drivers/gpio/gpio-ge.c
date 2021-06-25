<शैली गुरु>
/*
 * Driver क्रम GE FPGA based GPIO
 *
 * Author: Martyn Welch <martyn.welch@ge.com>
 *
 * 2008 (c) GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

/* TODO
 *
 * Configuration of output modes (totem-pole/खोलो-drain)
 * Interrupt configuration - पूर्णांकerrupts are always generated the FPGA relies on
 * the I/O पूर्णांकerrupt controllers mask to stop them propergating
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>

#घोषणा GEF_GPIO_सूचीECT		0x00
#घोषणा GEF_GPIO_IN		0x04
#घोषणा GEF_GPIO_OUT		0x08
#घोषणा GEF_GPIO_TRIG		0x0C
#घोषणा GEF_GPIO_POLAR_A	0x10
#घोषणा GEF_GPIO_POLAR_B	0x14
#घोषणा GEF_GPIO_INT_STAT	0x18
#घोषणा GEF_GPIO_OVERRUN	0x1C
#घोषणा GEF_GPIO_MODE		0x20

अटल स्थिर काष्ठा of_device_id gef_gpio_ids[] = अणु
	अणु
		.compatible	= "gef,sbc610-gpio",
		.data		= (व्योम *)19,
	पूर्ण, अणु
		.compatible	= "gef,sbc310-gpio",
		.data		= (व्योम *)6,
	पूर्ण, अणु
		.compatible	= "ge,imp3a-gpio",
		.data		= (व्योम *)16,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gef_gpio_ids);

अटल पूर्णांक __init gef_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_chip *gc;
	व्योम __iomem *regs;
	पूर्णांक ret;

	gc = devm_kzalloc(&pdev->dev, माप(*gc), GFP_KERNEL);
	अगर (!gc)
		वापस -ENOMEM;

	regs = of_iomap(pdev->dev.of_node, 0);
	अगर (!regs)
		वापस -ENOMEM;

	ret = bgpio_init(gc, &pdev->dev, 4, regs + GEF_GPIO_IN,
			 regs + GEF_GPIO_OUT, शून्य, शून्य,
			 regs + GEF_GPIO_सूचीECT, BGPIOF_BIG_ENDIAN_BYTE_ORDER);
	अगर (ret) अणु
		dev_err(&pdev->dev, "bgpio_init failed\n");
		जाओ err0;
	पूर्ण

	/* Setup poपूर्णांकers to chip functions */
	gc->label = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%pOF", pdev->dev.of_node);
	अगर (!gc->label) अणु
		ret = -ENOMEM;
		जाओ err0;
	पूर्ण

	gc->base = -1;
	gc->ngpio = (u16)(uपूर्णांकptr_t)of_device_get_match_data(&pdev->dev);
	gc->of_gpio_n_cells = 2;
	gc->of_node = pdev->dev.of_node;

	/* This function adds a memory mapped GPIO chip */
	ret = devm_gpiochip_add_data(&pdev->dev, gc, शून्य);
	अगर (ret)
		जाओ err0;

	वापस 0;
err0:
	iounmap(regs);
	pr_err("%pOF: GPIO chip registration failed\n", pdev->dev.of_node);
	वापस ret;
पूर्ण;

अटल काष्ठा platक्रमm_driver gef_gpio_driver = अणु
	.driver = अणु
		.name		= "gef-gpio",
		.of_match_table	= gef_gpio_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver_probe(gef_gpio_driver, gef_gpio_probe);

MODULE_DESCRIPTION("GE I/O FPGA GPIO driver");
MODULE_AUTHOR("Martyn Welch <martyn.welch@ge.com");
MODULE_LICENSE("GPL");
