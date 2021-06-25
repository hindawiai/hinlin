<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Linux GPIOlib driver क्रम the VIA VX855 पूर्णांकegrated southbridge GPIO
 *
 * Copyright (C) 2009 VIA Technologies, Inc.
 * Copyright (C) 2010 One Laptop per Child
 * Author: Harald Welte <HaraldWelte@viatech.com>
 * All rights reserved.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>

#घोषणा MODULE_NAME "vx855_gpio"

/* The VX855 south bridge has the following GPIO pins:
 *	GPI 0...13	General Purpose Input
 *	GPO 0...12	General Purpose Output
 *	GPIO 0...14	General Purpose I/O (Open-Drain)
 */

#घोषणा NR_VX855_GPI	14
#घोषणा NR_VX855_GPO	13
#घोषणा NR_VX855_GPIO	15

#घोषणा NR_VX855_GPInO	(NR_VX855_GPI + NR_VX855_GPO)
#घोषणा NR_VX855_GP	(NR_VX855_GPI + NR_VX855_GPO + NR_VX855_GPIO)

काष्ठा vx855_gpio अणु
	काष्ठा gpio_chip gpio;
	spinlock_t lock;
	u32 io_gpi;
	u32 io_gpo;
पूर्ण;

/* resolve a GPIx पूर्णांकo the corresponding bit position */
अटल अंतरभूत u_पूर्णांक32_t gpi_i_bit(पूर्णांक i)
अणु
	अगर (i < 10)
		वापस 1 << i;
	अन्यथा
		वापस 1 << (i + 14);
पूर्ण

अटल अंतरभूत u_पूर्णांक32_t gpo_o_bit(पूर्णांक i)
अणु
	अगर (i < 11)
		वापस 1 << i;
	अन्यथा
		वापस 1 << (i + 14);
पूर्ण

अटल अंतरभूत u_पूर्णांक32_t gpio_i_bit(पूर्णांक i)
अणु
	अगर (i < 14)
		वापस 1 << (i + 10);
	अन्यथा
		वापस 1 << (i + 14);
पूर्ण

अटल अंतरभूत u_पूर्णांक32_t gpio_o_bit(पूर्णांक i)
अणु
	अगर (i < 14)
		वापस 1 << (i + 11);
	अन्यथा
		वापस 1 << (i + 13);
पूर्ण

/* Mapping between numeric GPIO ID and the actual GPIO hardware numbering:
 * 0..13	GPI 0..13
 * 14..26	GPO 0..12
 * 27..41	GPIO 0..14
 */

अटल पूर्णांक vx855gpio_direction_input(काष्ठा gpio_chip *gpio,
				     अचिन्हित पूर्णांक nr)
अणु
	काष्ठा vx855_gpio *vg = gpiochip_get_data(gpio);
	अचिन्हित दीर्घ flags;
	u_पूर्णांक32_t reg_out;

	/* Real GPI bits are always in input direction */
	अगर (nr < NR_VX855_GPI)
		वापस 0;

	/* Real GPO bits cannot be put in output direction */
	अगर (nr < NR_VX855_GPInO)
		वापस -EINVAL;

	/* Open Drain GPIO have to be set to one */
	spin_lock_irqsave(&vg->lock, flags);
	reg_out = inl(vg->io_gpo);
	reg_out |= gpio_o_bit(nr - NR_VX855_GPInO);
	outl(reg_out, vg->io_gpo);
	spin_unlock_irqrestore(&vg->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक vx855gpio_get(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा vx855_gpio *vg = gpiochip_get_data(gpio);
	u_पूर्णांक32_t reg_in;
	पूर्णांक ret = 0;

	अगर (nr < NR_VX855_GPI) अणु
		reg_in = inl(vg->io_gpi);
		अगर (reg_in & gpi_i_bit(nr))
			ret = 1;
	पूर्ण अन्यथा अगर (nr < NR_VX855_GPInO) अणु
		/* GPO करोn't have an input bit, we need to पढ़ो it
		 * back from the output रेजिस्टर */
		reg_in = inl(vg->io_gpo);
		अगर (reg_in & gpo_o_bit(nr - NR_VX855_GPI))
			ret = 1;
	पूर्ण अन्यथा अणु
		reg_in = inl(vg->io_gpi);
		अगर (reg_in & gpio_i_bit(nr - NR_VX855_GPInO))
			ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vx855gpio_set(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक nr,
			  पूर्णांक val)
अणु
	काष्ठा vx855_gpio *vg = gpiochip_get_data(gpio);
	अचिन्हित दीर्घ flags;
	u_पूर्णांक32_t reg_out;

	/* True GPI cannot be चयनed to output mode */
	अगर (nr < NR_VX855_GPI)
		वापस;

	spin_lock_irqsave(&vg->lock, flags);
	reg_out = inl(vg->io_gpo);
	अगर (nr < NR_VX855_GPInO) अणु
		अगर (val)
			reg_out |= gpo_o_bit(nr - NR_VX855_GPI);
		अन्यथा
			reg_out &= ~gpo_o_bit(nr - NR_VX855_GPI);
	पूर्ण अन्यथा अणु
		अगर (val)
			reg_out |= gpio_o_bit(nr - NR_VX855_GPInO);
		अन्यथा
			reg_out &= ~gpio_o_bit(nr - NR_VX855_GPInO);
	पूर्ण
	outl(reg_out, vg->io_gpo);
	spin_unlock_irqrestore(&vg->lock, flags);
पूर्ण

अटल पूर्णांक vx855gpio_direction_output(काष्ठा gpio_chip *gpio,
				      अचिन्हित पूर्णांक nr, पूर्णांक val)
अणु
	/* True GPI cannot be चयनed to output mode */
	अगर (nr < NR_VX855_GPI)
		वापस -EINVAL;

	/* True GPO करोn't need to be चयनed to output mode,
	 * and GPIO are खोलो-drain, i.e. also need no चयनing,
	 * so all we करो is set the level */
	vx855gpio_set(gpio, nr, val);

	वापस 0;
पूर्ण

अटल पूर्णांक vx855gpio_set_config(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक nr,
				अचिन्हित दीर्घ config)
अणु
	क्रमागत pin_config_param param = pinconf_to_config_param(config);

	/* The GPI cannot be single-ended */
	अगर (nr < NR_VX855_GPI)
		वापस -EINVAL;

	/* The GPO's are push-pull */
	अगर (nr < NR_VX855_GPInO) अणु
		अगर (param != PIN_CONFIG_DRIVE_PUSH_PULL)
			वापस -ENOTSUPP;
		वापस 0;
	पूर्ण

	/* The GPIO's are खोलो drain */
	अगर (param != PIN_CONFIG_DRIVE_OPEN_DRAIN)
		वापस -ENOTSUPP;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *vx855gpio_names[NR_VX855_GP] = अणु
	"VX855_GPI0", "VX855_GPI1", "VX855_GPI2", "VX855_GPI3", "VX855_GPI4",
	"VX855_GPI5", "VX855_GPI6", "VX855_GPI7", "VX855_GPI8", "VX855_GPI9",
	"VX855_GPI10", "VX855_GPI11", "VX855_GPI12", "VX855_GPI13",
	"VX855_GPO0", "VX855_GPO1", "VX855_GPO2", "VX855_GPO3", "VX855_GPO4",
	"VX855_GPO5", "VX855_GPO6", "VX855_GPO7", "VX855_GPO8", "VX855_GPO9",
	"VX855_GPO10", "VX855_GPO11", "VX855_GPO12",
	"VX855_GPIO0", "VX855_GPIO1", "VX855_GPIO2", "VX855_GPIO3",
	"VX855_GPIO4", "VX855_GPIO5", "VX855_GPIO6", "VX855_GPIO7",
	"VX855_GPIO8", "VX855_GPIO9", "VX855_GPIO10", "VX855_GPIO11",
	"VX855_GPIO12", "VX855_GPIO13", "VX855_GPIO14"
पूर्ण;

अटल व्योम vx855gpio_gpio_setup(काष्ठा vx855_gpio *vg)
अणु
	काष्ठा gpio_chip *c = &vg->gpio;

	c->label = "VX855 South Bridge";
	c->owner = THIS_MODULE;
	c->direction_input = vx855gpio_direction_input;
	c->direction_output = vx855gpio_direction_output;
	c->get = vx855gpio_get;
	c->set = vx855gpio_set;
	c->set_config = vx855gpio_set_config;
	c->dbg_show = शून्य;
	c->base = 0;
	c->ngpio = NR_VX855_GP;
	c->can_sleep = false;
	c->names = vx855gpio_names;
पूर्ण

/* This platक्रमm device is ordinarily रेजिस्टरed by the vx855 mfd driver */
अटल पूर्णांक vx855gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res_gpi;
	काष्ठा resource *res_gpo;
	काष्ठा vx855_gpio *vg;

	res_gpi = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	res_gpo = platक्रमm_get_resource(pdev, IORESOURCE_IO, 1);
	अगर (!res_gpi || !res_gpo)
		वापस -EBUSY;

	vg = devm_kzalloc(&pdev->dev, माप(*vg), GFP_KERNEL);
	अगर (!vg)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, vg);

	dev_info(&pdev->dev, "found VX855 GPIO controller\n");
	vg->io_gpi = res_gpi->start;
	vg->io_gpo = res_gpo->start;
	spin_lock_init(&vg->lock);

	/*
	 * A single byte is used to control various GPIO ports on the VX855,
	 * and in the हाल of the OLPC XO-1.5, some of those ports are used
	 * क्रम चयनes that are पूर्णांकerpreted and exposed through ACPI. ACPI
	 * will have reserved the region, so our own reservation will not
	 * succeed. Ignore and जारी.
	 */

	अगर (!devm_request_region(&pdev->dev, res_gpi->start,
				 resource_size(res_gpi), MODULE_NAME "_gpi"))
		dev_warn(&pdev->dev,
			"GPI I/O resource busy, probably claimed by ACPI\n");

	अगर (!devm_request_region(&pdev->dev, res_gpo->start,
				 resource_size(res_gpo), MODULE_NAME "_gpo"))
		dev_warn(&pdev->dev,
			"GPO I/O resource busy, probably claimed by ACPI\n");

	vx855gpio_gpio_setup(vg);

	वापस devm_gpiochip_add_data(&pdev->dev, &vg->gpio, vg);
पूर्ण

अटल काष्ठा platक्रमm_driver vx855gpio_driver = अणु
	.driver = अणु
		.name	= MODULE_NAME,
	पूर्ण,
	.probe		= vx855gpio_probe,
पूर्ण;

module_platक्रमm_driver(vx855gpio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <HaraldWelte@viatech.com>");
MODULE_DESCRIPTION("GPIO driver for the VIA VX855 chipset");
MODULE_ALIAS("platform:vx855_gpio");
