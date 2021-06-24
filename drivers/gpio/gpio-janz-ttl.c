<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Janz MODULbus VMOD-TTL GPIO Driver
 *
 * Copyright (c) 2010 Ira W. Snyder <iws@ovro.caltech.edu>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>

#समावेश <linux/mfd/janz.h>

#घोषणा DRV_NAME "janz-ttl"

#घोषणा PORTA_सूचीECTION		0x23
#घोषणा PORTB_सूचीECTION		0x2B
#घोषणा PORTC_सूचीECTION		0x06
#घोषणा PORTA_IOCTL		0x24
#घोषणा PORTB_IOCTL		0x2C
#घोषणा PORTC_IOCTL		0x07

#घोषणा MASTER_INT_CTL		0x00
#घोषणा MASTER_CONF_CTL		0x01

#घोषणा CONF_PAE		BIT(2)
#घोषणा CONF_PBE		BIT(7)
#घोषणा CONF_PCE		BIT(4)

काष्ठा ttl_control_regs अणु
	__be16 portc;
	__be16 portb;
	__be16 porta;
	__be16 control;
पूर्ण;

काष्ठा ttl_module अणु
	काष्ठा gpio_chip gpio;

	/* base address of रेजिस्टरs */
	काष्ठा ttl_control_regs __iomem *regs;

	u8 portc_shaकरोw;
	u8 portb_shaकरोw;
	u8 porta_shaकरोw;

	spinlock_t lock;
पूर्ण;

अटल पूर्णांक ttl_get_value(काष्ठा gpio_chip *gpio, अचिन्हित offset)
अणु
	काष्ठा ttl_module *mod = dev_get_drvdata(gpio->parent);
	u8 *shaकरोw;
	पूर्णांक ret;

	अगर (offset < 8) अणु
		shaकरोw = &mod->porta_shaकरोw;
	पूर्ण अन्यथा अगर (offset < 16) अणु
		shaकरोw = &mod->portb_shaकरोw;
		offset -= 8;
	पूर्ण अन्यथा अणु
		shaकरोw = &mod->portc_shaकरोw;
		offset -= 16;
	पूर्ण

	spin_lock(&mod->lock);
	ret = *shaकरोw & BIT(offset);
	spin_unlock(&mod->lock);
	वापस !!ret;
पूर्ण

अटल व्योम ttl_set_value(काष्ठा gpio_chip *gpio, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा ttl_module *mod = dev_get_drvdata(gpio->parent);
	व्योम __iomem *port;
	u8 *shaकरोw;

	अगर (offset < 8) अणु
		port = &mod->regs->porta;
		shaकरोw = &mod->porta_shaकरोw;
	पूर्ण अन्यथा अगर (offset < 16) अणु
		port = &mod->regs->portb;
		shaकरोw = &mod->portb_shaकरोw;
		offset -= 8;
	पूर्ण अन्यथा अणु
		port = &mod->regs->portc;
		shaकरोw = &mod->portc_shaकरोw;
		offset -= 16;
	पूर्ण

	spin_lock(&mod->lock);
	अगर (value)
		*shaकरोw |= BIT(offset);
	अन्यथा
		*shaकरोw &= ~BIT(offset);

	ioग_लिखो16be(*shaकरोw, port);
	spin_unlock(&mod->lock);
पूर्ण

अटल व्योम ttl_ग_लिखो_reg(काष्ठा ttl_module *mod, u8 reg, u16 val)
अणु
	ioग_लिखो16be(reg, &mod->regs->control);
	ioग_लिखो16be(val, &mod->regs->control);
पूर्ण

अटल व्योम ttl_setup_device(काष्ठा ttl_module *mod)
अणु
	/* reset the device to a known state */
	ioग_लिखो16be(0x0000, &mod->regs->control);
	ioग_लिखो16be(0x0001, &mod->regs->control);
	ioग_लिखो16be(0x0000, &mod->regs->control);

	/* put all ports in खोलो-drain mode */
	ttl_ग_लिखो_reg(mod, PORTA_IOCTL, 0x00ff);
	ttl_ग_लिखो_reg(mod, PORTB_IOCTL, 0x00ff);
	ttl_ग_लिखो_reg(mod, PORTC_IOCTL, 0x000f);

	/* set all ports as outमाला_दो */
	ttl_ग_लिखो_reg(mod, PORTA_सूचीECTION, 0x0000);
	ttl_ग_लिखो_reg(mod, PORTB_सूचीECTION, 0x0000);
	ttl_ग_लिखो_reg(mod, PORTC_सूचीECTION, 0x0000);

	/* set all ports to drive zeroes */
	ioग_लिखो16be(0x0000, &mod->regs->porta);
	ioग_लिखो16be(0x0000, &mod->regs->portb);
	ioग_लिखो16be(0x0000, &mod->regs->portc);

	/* enable all ports */
	ttl_ग_लिखो_reg(mod, MASTER_CONF_CTL, CONF_PAE | CONF_PBE | CONF_PCE);
पूर्ण

अटल पूर्णांक ttl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा janz_platक्रमm_data *pdata;
	काष्ठा ttl_module *mod;
	काष्ठा gpio_chip *gpio;
	पूर्णांक ret;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data\n");
		वापस -ENXIO;
	पूर्ण

	mod = devm_kzalloc(&pdev->dev, माप(*mod), GFP_KERNEL);
	अगर (!mod)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mod);
	spin_lock_init(&mod->lock);

	/* get access to the MODULbus रेजिस्टरs क्रम this module */
	mod->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mod->regs))
		वापस PTR_ERR(mod->regs);

	ttl_setup_device(mod);

	/* Initialize the GPIO data काष्ठाures */
	gpio = &mod->gpio;
	gpio->parent = &pdev->dev;
	gpio->label = pdev->name;
	gpio->get = ttl_get_value;
	gpio->set = ttl_set_value;
	gpio->owner = THIS_MODULE;

	/* request dynamic allocation */
	gpio->base = -1;
	gpio->ngpio = 20;

	ret = devm_gpiochip_add_data(&pdev->dev, gpio, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to add GPIO chip\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ttl_driver = अणु
	.driver		= अणु
		.name	= DRV_NAME,
	पूर्ण,
	.probe		= ttl_probe,
पूर्ण;

module_platक्रमm_driver(ttl_driver);

MODULE_AUTHOR("Ira W. Snyder <iws@ovro.caltech.edu>");
MODULE_DESCRIPTION("Janz MODULbus VMOD-TTL Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:janz-ttl");
