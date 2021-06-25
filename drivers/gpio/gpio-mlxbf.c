<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/resource.h>
#समावेश <linux/types.h>

/* Number of pins on BlueField */
#घोषणा MLXBF_GPIO_NR 54

/* Pad Electrical Controls. */
#घोषणा MLXBF_GPIO_PAD_CONTROL_FIRST_WORD 0x0700
#घोषणा MLXBF_GPIO_PAD_CONTROL_1_FIRST_WORD 0x0708
#घोषणा MLXBF_GPIO_PAD_CONTROL_2_FIRST_WORD 0x0710
#घोषणा MLXBF_GPIO_PAD_CONTROL_3_FIRST_WORD 0x0718

#घोषणा MLXBF_GPIO_PIN_सूची_I 0x1040
#घोषणा MLXBF_GPIO_PIN_सूची_O 0x1048
#घोषणा MLXBF_GPIO_PIN_STATE 0x1000
#घोषणा MLXBF_GPIO_SCRATCHPAD 0x20

#अगर_घोषित CONFIG_PM
काष्ठा mlxbf_gpio_context_save_regs अणु
	u64 scratchpad;
	u64 pad_control[MLXBF_GPIO_NR];
	u64 pin_dir_i;
	u64 pin_dir_o;
पूर्ण;
#पूर्ण_अगर

/* Device state काष्ठाure. */
काष्ठा mlxbf_gpio_state अणु
	काष्ठा gpio_chip gc;

	/* Memory Address */
	व्योम __iomem *base;

#अगर_घोषित CONFIG_PM
	काष्ठा mlxbf_gpio_context_save_regs csave_regs;
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक mlxbf_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxbf_gpio_state *gs;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_chip *gc;
	पूर्णांक ret;

	gs = devm_kzalloc(&pdev->dev, माप(*gs), GFP_KERNEL);
	अगर (!gs)
		वापस -ENOMEM;

	gs->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gs->base))
		वापस PTR_ERR(gs->base);

	gc = &gs->gc;
	ret = bgpio_init(gc, dev, 8,
			 gs->base + MLXBF_GPIO_PIN_STATE,
			 शून्य,
			 शून्य,
			 gs->base + MLXBF_GPIO_PIN_सूची_O,
			 gs->base + MLXBF_GPIO_PIN_सूची_I,
			 0);
	अगर (ret)
		वापस -ENODEV;

	gc->owner = THIS_MODULE;
	gc->ngpio = MLXBF_GPIO_NR;

	ret = devm_gpiochip_add_data(dev, &gs->gc, gs);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed adding memory mapped gpiochip\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gs);
	dev_info(&pdev->dev, "registered Mellanox BlueField GPIO");
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mlxbf_gpio_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा mlxbf_gpio_state *gs = platक्रमm_get_drvdata(pdev);

	gs->csave_regs.scratchpad = पढ़ोq(gs->base + MLXBF_GPIO_SCRATCHPAD);
	gs->csave_regs.pad_control[0] =
		पढ़ोq(gs->base + MLXBF_GPIO_PAD_CONTROL_FIRST_WORD);
	gs->csave_regs.pad_control[1] =
		पढ़ोq(gs->base + MLXBF_GPIO_PAD_CONTROL_1_FIRST_WORD);
	gs->csave_regs.pad_control[2] =
		पढ़ोq(gs->base + MLXBF_GPIO_PAD_CONTROL_2_FIRST_WORD);
	gs->csave_regs.pad_control[3] =
		पढ़ोq(gs->base + MLXBF_GPIO_PAD_CONTROL_3_FIRST_WORD);
	gs->csave_regs.pin_dir_i = पढ़ोq(gs->base + MLXBF_GPIO_PIN_सूची_I);
	gs->csave_regs.pin_dir_o = पढ़ोq(gs->base + MLXBF_GPIO_PIN_सूची_O);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_gpio_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxbf_gpio_state *gs = platक्रमm_get_drvdata(pdev);

	ग_लिखोq(gs->csave_regs.scratchpad, gs->base + MLXBF_GPIO_SCRATCHPAD);
	ग_लिखोq(gs->csave_regs.pad_control[0],
	       gs->base + MLXBF_GPIO_PAD_CONTROL_FIRST_WORD);
	ग_लिखोq(gs->csave_regs.pad_control[1],
	       gs->base + MLXBF_GPIO_PAD_CONTROL_1_FIRST_WORD);
	ग_लिखोq(gs->csave_regs.pad_control[2],
	       gs->base + MLXBF_GPIO_PAD_CONTROL_2_FIRST_WORD);
	ग_लिखोq(gs->csave_regs.pad_control[3],
	       gs->base + MLXBF_GPIO_PAD_CONTROL_3_FIRST_WORD);
	ग_लिखोq(gs->csave_regs.pin_dir_i, gs->base + MLXBF_GPIO_PIN_सूची_I);
	ग_लिखोq(gs->csave_regs.pin_dir_o, gs->base + MLXBF_GPIO_PIN_सूची_O);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा acpi_device_id __maybe_unused mlxbf_gpio_acpi_match[] = अणु
	अणु "MLNXBF02", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mlxbf_gpio_acpi_match);

अटल काष्ठा platक्रमm_driver mlxbf_gpio_driver = अणु
	.driver = अणु
		.name = "mlxbf_gpio",
		.acpi_match_table = ACPI_PTR(mlxbf_gpio_acpi_match),
	पूर्ण,
	.probe    = mlxbf_gpio_probe,
#अगर_घोषित CONFIG_PM
	.suspend  = mlxbf_gpio_suspend,
	.resume   = mlxbf_gpio_resume,
#पूर्ण_अगर
पूर्ण;

module_platक्रमm_driver(mlxbf_gpio_driver);

MODULE_DESCRIPTION("Mellanox BlueField GPIO Driver");
MODULE_AUTHOR("Mellanox Technologies");
MODULE_LICENSE("GPL");
