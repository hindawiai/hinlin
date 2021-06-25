<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2020 Daniel Palmer<daniel@thingy.jp> */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/gpio/msc313-gpपन.स>
#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>

#घोषणा DRIVER_NAME "gpio-msc313"

#घोषणा MSC313_GPIO_IN  BIT(0)
#घोषणा MSC313_GPIO_OUT BIT(4)
#घोषणा MSC313_GPIO_OEN BIT(5)

/*
 * These bits need to be saved to correctly restore the
 * gpio state when resuming from suspend to memory.
 */
#घोषणा MSC313_GPIO_BITSTOSAVE (MSC313_GPIO_OUT | MSC313_GPIO_OEN)

/* pad names क्रम fuart, same क्रम all SoCs so far */
#घोषणा MSC313_PINNAME_FUART_RX		"fuart_rx"
#घोषणा MSC313_PINNAME_FUART_TX		"fuart_tx"
#घोषणा MSC313_PINNAME_FUART_CTS	"fuart_cts"
#घोषणा MSC313_PINNAME_FUART_RTS	"fuart_rts"

/* pad names क्रम sr, mercury5 is dअगरferent */
#घोषणा MSC313_PINNAME_SR_IO2		"sr_io2"
#घोषणा MSC313_PINNAME_SR_IO3		"sr_io3"
#घोषणा MSC313_PINNAME_SR_IO4		"sr_io4"
#घोषणा MSC313_PINNAME_SR_IO5		"sr_io5"
#घोषणा MSC313_PINNAME_SR_IO6		"sr_io6"
#घोषणा MSC313_PINNAME_SR_IO7		"sr_io7"
#घोषणा MSC313_PINNAME_SR_IO8		"sr_io8"
#घोषणा MSC313_PINNAME_SR_IO9		"sr_io9"
#घोषणा MSC313_PINNAME_SR_IO10		"sr_io10"
#घोषणा MSC313_PINNAME_SR_IO11		"sr_io11"
#घोषणा MSC313_PINNAME_SR_IO12		"sr_io12"
#घोषणा MSC313_PINNAME_SR_IO13		"sr_io13"
#घोषणा MSC313_PINNAME_SR_IO14		"sr_io14"
#घोषणा MSC313_PINNAME_SR_IO15		"sr_io15"
#घोषणा MSC313_PINNAME_SR_IO16		"sr_io16"
#घोषणा MSC313_PINNAME_SR_IO17		"sr_io17"

/* pad names क्रम sd, same क्रम all SoCs so far */
#घोषणा MSC313_PINNAME_SD_CLK		"sd_clk"
#घोषणा MSC313_PINNAME_SD_CMD		"sd_cmd"
#घोषणा MSC313_PINNAME_SD_D0		"sd_d0"
#घोषणा MSC313_PINNAME_SD_D1		"sd_d1"
#घोषणा MSC313_PINNAME_SD_D2		"sd_d2"
#घोषणा MSC313_PINNAME_SD_D3		"sd_d3"

/* pad names क्रम i2c1, same क्रम all SoCs so क्रम */
#घोषणा MSC313_PINNAME_I2C1_SCL		"i2c1_scl"
#घोषणा MSC313_PINNAME_I2C1_SCA		"i2c1_sda"

/* pad names क्रम spi0, same क्रम all SoCs so far */
#घोषणा MSC313_PINNAME_SPI0_CZ		"spi0_cz"
#घोषणा MSC313_PINNAME_SPI0_CK		"spi0_ck"
#घोषणा MSC313_PINNAME_SPI0_DI		"spi0_di"
#घोषणा MSC313_PINNAME_SPI0_DO		"spi0_do"

#घोषणा FUART_NAMES			\
	MSC313_PINNAME_FUART_RX,	\
	MSC313_PINNAME_FUART_TX,	\
	MSC313_PINNAME_FUART_CTS,	\
	MSC313_PINNAME_FUART_RTS

#घोषणा OFF_FUART_RX	0x50
#घोषणा OFF_FUART_TX	0x54
#घोषणा OFF_FUART_CTS	0x58
#घोषणा OFF_FUART_RTS	0x5c

#घोषणा FUART_OFFSETS	\
	OFF_FUART_RX,	\
	OFF_FUART_TX,	\
	OFF_FUART_CTS,	\
	OFF_FUART_RTS

#घोषणा SR_NAMES		\
	MSC313_PINNAME_SR_IO2,	\
	MSC313_PINNAME_SR_IO3,	\
	MSC313_PINNAME_SR_IO4,	\
	MSC313_PINNAME_SR_IO5,	\
	MSC313_PINNAME_SR_IO6,	\
	MSC313_PINNAME_SR_IO7,	\
	MSC313_PINNAME_SR_IO8,	\
	MSC313_PINNAME_SR_IO9,	\
	MSC313_PINNAME_SR_IO10,	\
	MSC313_PINNAME_SR_IO11,	\
	MSC313_PINNAME_SR_IO12,	\
	MSC313_PINNAME_SR_IO13,	\
	MSC313_PINNAME_SR_IO14,	\
	MSC313_PINNAME_SR_IO15,	\
	MSC313_PINNAME_SR_IO16,	\
	MSC313_PINNAME_SR_IO17

#घोषणा OFF_SR_IO2	0x88
#घोषणा OFF_SR_IO3	0x8c
#घोषणा OFF_SR_IO4	0x90
#घोषणा OFF_SR_IO5	0x94
#घोषणा OFF_SR_IO6	0x98
#घोषणा OFF_SR_IO7	0x9c
#घोषणा OFF_SR_IO8	0xa0
#घोषणा OFF_SR_IO9	0xa4
#घोषणा OFF_SR_IO10	0xa8
#घोषणा OFF_SR_IO11	0xac
#घोषणा OFF_SR_IO12	0xb0
#घोषणा OFF_SR_IO13	0xb4
#घोषणा OFF_SR_IO14	0xb8
#घोषणा OFF_SR_IO15	0xbc
#घोषणा OFF_SR_IO16	0xc0
#घोषणा OFF_SR_IO17	0xc4

#घोषणा SR_OFFSETS	\
	OFF_SR_IO2,	\
	OFF_SR_IO3,	\
	OFF_SR_IO4,	\
	OFF_SR_IO5,	\
	OFF_SR_IO6,	\
	OFF_SR_IO7,	\
	OFF_SR_IO8,	\
	OFF_SR_IO9,	\
	OFF_SR_IO10,	\
	OFF_SR_IO11,	\
	OFF_SR_IO12,	\
	OFF_SR_IO13,	\
	OFF_SR_IO14,	\
	OFF_SR_IO15,	\
	OFF_SR_IO16,	\
	OFF_SR_IO17

#घोषणा SD_NAMES		\
	MSC313_PINNAME_SD_CLK,	\
	MSC313_PINNAME_SD_CMD,	\
	MSC313_PINNAME_SD_D0,	\
	MSC313_PINNAME_SD_D1,	\
	MSC313_PINNAME_SD_D2,	\
	MSC313_PINNAME_SD_D3

#घोषणा OFF_SD_CLK	0x140
#घोषणा OFF_SD_CMD	0x144
#घोषणा OFF_SD_D0	0x148
#घोषणा OFF_SD_D1	0x14c
#घोषणा OFF_SD_D2	0x150
#घोषणा OFF_SD_D3	0x154

#घोषणा SD_OFFSETS	\
	OFF_SD_CLK,	\
	OFF_SD_CMD,	\
	OFF_SD_D0,	\
	OFF_SD_D1,	\
	OFF_SD_D2,	\
	OFF_SD_D3

#घोषणा I2C1_NAMES			\
	MSC313_PINNAME_I2C1_SCL,	\
	MSC313_PINNAME_I2C1_SCA

#घोषणा OFF_I2C1_SCL	0x188
#घोषणा OFF_I2C1_SCA	0x18c

#घोषणा I2C1_OFFSETS	\
	OFF_I2C1_SCL,	\
	OFF_I2C1_SCA

#घोषणा SPI0_NAMES		\
	MSC313_PINNAME_SPI0_CZ,	\
	MSC313_PINNAME_SPI0_CK,	\
	MSC313_PINNAME_SPI0_DI,	\
	MSC313_PINNAME_SPI0_DO

#घोषणा OFF_SPI0_CZ	0x1c0
#घोषणा OFF_SPI0_CK	0x1c4
#घोषणा OFF_SPI0_DI	0x1c8
#घोषणा OFF_SPI0_DO	0x1cc

#घोषणा SPI0_OFFSETS	\
	OFF_SPI0_CZ,	\
	OFF_SPI0_CK,	\
	OFF_SPI0_DI,	\
	OFF_SPI0_DO

काष्ठा msc313_gpio_data अणु
	स्थिर अक्षर * स्थिर *names;
	स्थिर अचिन्हित पूर्णांक *offsets;
	स्थिर अचिन्हित पूर्णांक num;
पूर्ण;

#घोषणा MSC313_GPIO_CHIPDATA(_chip) \
अटल स्थिर काष्ठा msc313_gpio_data _chip##_data = अणु \
	.names = _chip##_names, \
	.offsets = _chip##_offsets, \
	.num = ARRAY_SIZE(_chip##_offsets), \
पूर्ण

#अगर_घोषित CONFIG_MACH_अनन्त
अटल स्थिर अक्षर * स्थिर msc313_names[] = अणु
	FUART_NAMES,
	SR_NAMES,
	SD_NAMES,
	I2C1_NAMES,
	SPI0_NAMES,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक msc313_offsets[] = अणु
	FUART_OFFSETS,
	SR_OFFSETS,
	SD_OFFSETS,
	I2C1_OFFSETS,
	SPI0_OFFSETS,
पूर्ण;

MSC313_GPIO_CHIPDATA(msc313);
#पूर्ण_अगर

काष्ठा msc313_gpio अणु
	व्योम __iomem *base;
	स्थिर काष्ठा msc313_gpio_data *gpio_data;
	u8 *saved;
पूर्ण;

अटल व्योम msc313_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा msc313_gpio *gpio = gpiochip_get_data(chip);
	u8 gpioreg = पढ़ोb_relaxed(gpio->base + gpio->gpio_data->offsets[offset]);

	अगर (value)
		gpioreg |= MSC313_GPIO_OUT;
	अन्यथा
		gpioreg &= ~MSC313_GPIO_OUT;

	ग_लिखोb_relaxed(gpioreg, gpio->base + gpio->gpio_data->offsets[offset]);
पूर्ण

अटल पूर्णांक msc313_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा msc313_gpio *gpio = gpiochip_get_data(chip);

	वापस पढ़ोb_relaxed(gpio->base + gpio->gpio_data->offsets[offset]) & MSC313_GPIO_IN;
पूर्ण

अटल पूर्णांक msc313_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा msc313_gpio *gpio = gpiochip_get_data(chip);
	u8 gpioreg = पढ़ोb_relaxed(gpio->base + gpio->gpio_data->offsets[offset]);

	gpioreg |= MSC313_GPIO_OEN;
	ग_लिखोb_relaxed(gpioreg, gpio->base + gpio->gpio_data->offsets[offset]);

	वापस 0;
पूर्ण

अटल पूर्णांक msc313_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा msc313_gpio *gpio = gpiochip_get_data(chip);
	u8 gpioreg = पढ़ोb_relaxed(gpio->base + gpio->gpio_data->offsets[offset]);

	gpioreg &= ~MSC313_GPIO_OEN;
	अगर (value)
		gpioreg |= MSC313_GPIO_OUT;
	अन्यथा
		gpioreg &= ~MSC313_GPIO_OUT;
	ग_लिखोb_relaxed(gpioreg, gpio->base + gpio->gpio_data->offsets[offset]);

	वापस 0;
पूर्ण

/*
 * The पूर्णांकerrupt handling happens in the parent पूर्णांकerrupt controller,
 * we करोn't करो anything here.
 */
अटल काष्ठा irq_chip msc313_gpio_irqchip = अणु
	.name = "GPIO",
	.irq_eoi = irq_chip_eoi_parent,
	.irq_mask = irq_chip_mask_parent,
	.irq_unmask = irq_chip_unmask_parent,
	.irq_set_type = irq_chip_set_type_parent,
	.irq_set_affinity = irq_chip_set_affinity_parent,
पूर्ण;

/*
 * The parent पूर्णांकerrupt controller needs the GIC पूर्णांकerrupt type set to GIC_SPI
 * so we need to provide the fwspec. Essentially gpiochip_populate_parent_fwspec_twocell
 * that माला_दो GIC_SPI पूर्णांकo the first cell.
 */
अटल व्योम *msc313_gpio_populate_parent_fwspec(काष्ठा gpio_chip *gc,
					     अचिन्हित पूर्णांक parent_hwirq,
					     अचिन्हित पूर्णांक parent_type)
अणु
	काष्ठा irq_fwspec *fwspec;

	fwspec = kदो_स्मृति(माप(*fwspec), GFP_KERNEL);
	अगर (!fwspec)
		वापस शून्य;

	fwspec->fwnode = gc->irq.parent_करोमुख्य->fwnode;
	fwspec->param_count = 3;
	fwspec->param[0] = GIC_SPI;
	fwspec->param[1] = parent_hwirq;
	fwspec->param[2] = parent_type;

	वापस fwspec;
पूर्ण

अटल पूर्णांक msc313e_gpio_child_to_parent_hwirq(काष्ठा gpio_chip *chip,
					     अचिन्हित पूर्णांक child,
					     अचिन्हित पूर्णांक child_type,
					     अचिन्हित पूर्णांक *parent,
					     अचिन्हित पूर्णांक *parent_type)
अणु
	काष्ठा msc313_gpio *priv = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक offset = priv->gpio_data->offsets[child];

	/*
	 * only the spi0 pins have पूर्णांकerrupts on the parent
	 * on all of the known chips and so far they are all
	 * mapped to the same place
	 */
	अगर (offset >= OFF_SPI0_CZ && offset <= OFF_SPI0_DO) अणु
		*parent_type = child_type;
		*parent = ((offset - OFF_SPI0_CZ) >> 2) + 28;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक msc313_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा msc313_gpio_data *match_data;
	काष्ठा msc313_gpio *gpio;
	काष्ठा gpio_chip *gpiochip;
	काष्ठा gpio_irq_chip *gpioirqchip;
	काष्ठा irq_करोमुख्य *parent_करोमुख्य;
	काष्ठा device_node *parent_node;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	match_data = of_device_get_match_data(dev);
	अगर (!match_data)
		वापस -EINVAL;

	parent_node = of_irq_find_parent(dev->of_node);
	अगर (!parent_node)
		वापस -ENODEV;

	parent_करोमुख्य = irq_find_host(parent_node);
	अगर (!parent_करोमुख्य)
		वापस -ENODEV;

	gpio = devm_kzalloc(dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->gpio_data = match_data;

	gpio->saved = devm_kसुस्मृति(dev, gpio->gpio_data->num, माप(*gpio->saved), GFP_KERNEL);
	अगर (!gpio->saved)
		वापस -ENOMEM;

	gpio->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gpio->base))
		वापस PTR_ERR(gpio->base);

	platक्रमm_set_drvdata(pdev, gpio);

	gpiochip = devm_kzalloc(dev, माप(*gpiochip), GFP_KERNEL);
	अगर (!gpiochip)
		वापस -ENOMEM;

	gpiochip->label = DRIVER_NAME;
	gpiochip->parent = dev;
	gpiochip->request = gpiochip_generic_request;
	gpiochip->मुक्त = gpiochip_generic_मुक्त;
	gpiochip->direction_input = msc313_gpio_direction_input;
	gpiochip->direction_output = msc313_gpio_direction_output;
	gpiochip->get = msc313_gpio_get;
	gpiochip->set = msc313_gpio_set;
	gpiochip->base = -1;
	gpiochip->ngpio = gpio->gpio_data->num;
	gpiochip->names = gpio->gpio_data->names;

	gpioirqchip = &gpiochip->irq;
	gpioirqchip->chip = &msc313_gpio_irqchip;
	gpioirqchip->fwnode = of_node_to_fwnode(dev->of_node);
	gpioirqchip->parent_करोमुख्य = parent_करोमुख्य;
	gpioirqchip->child_to_parent_hwirq = msc313e_gpio_child_to_parent_hwirq;
	gpioirqchip->populate_parent_alloc_arg = msc313_gpio_populate_parent_fwspec;
	gpioirqchip->handler = handle_bad_irq;
	gpioirqchip->शेष_type = IRQ_TYPE_NONE;

	ret = devm_gpiochip_add_data(dev, gpiochip, gpio);
	वापस ret;
पूर्ण

अटल पूर्णांक msc313_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id msc313_gpio_of_match[] = अणु
#अगर_घोषित CONFIG_MACH_अनन्त
	अणु
		.compatible = "mstar,msc313-gpio",
		.data = &msc313_data,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

/*
 * The GPIO controller loses the state of the रेजिस्टरs when the
 * SoC goes पूर्णांकo suspend to memory mode so we need to save some
 * of the रेजिस्टर bits beक्रमe suspending and put it back when resuming
 */
अटल पूर्णांक __maybe_unused msc313_gpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा msc313_gpio *gpio = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < gpio->gpio_data->num; i++)
		gpio->saved[i] = पढ़ोb_relaxed(gpio->base + gpio->gpio_data->offsets[i]) & MSC313_GPIO_BITSTOSAVE;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused msc313_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा msc313_gpio *gpio = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < gpio->gpio_data->num; i++)
		ग_लिखोb_relaxed(gpio->saved[i], gpio->base + gpio->gpio_data->offsets[i]);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(msc313_gpio_ops, msc313_gpio_suspend, msc313_gpio_resume);

अटल काष्ठा platक्रमm_driver msc313_gpio_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = msc313_gpio_of_match,
		.pm = &msc313_gpio_ops,
	पूर्ण,
	.probe = msc313_gpio_probe,
	.हटाओ = msc313_gpio_हटाओ,
पूर्ण;

builtin_platक्रमm_driver(msc313_gpio_driver);
