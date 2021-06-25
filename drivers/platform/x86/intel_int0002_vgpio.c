<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel INT0002 "Virtual GPIO" driver
 *
 * Copyright (C) 2017 Hans de Goede <hdegoede@redhat.com>
 *
 * Loosely based on android x86 kernel code which is:
 *
 * Copyright (c) 2014, Intel Corporation.
 *
 * Author: Dyut Kumar Sil <dyut.k.sil@पूर्णांकel.com>
 *
 * Some peripherals on Bay Trail and Cherry Trail platक्रमms संकेत a Power
 * Management Event (PME) to the Power Management Controller (PMC) to wakeup
 * the प्रणाली. When this happens software needs to clear the PME bus 0 status
 * bit in the GPE0a_STS रेजिस्टर to aव्योम an IRQ storm on IRQ 9.
 *
 * This is modelled in ACPI through the INT0002 ACPI device, which is
 * called a "Virtual GPIO controller" in ACPI because it defines the event
 * handler to call when the PME triggers through _AEI and _L02 / _E02
 * methods as would be करोne क्रम a real GPIO पूर्णांकerrupt in ACPI. Note this
 * is a hack to define an AML event handler क्रम the PME जबतक using existing
 * ACPI mechanisms, this is not a real GPIO at all.
 *
 * This driver will bind to the INT0002 device, and रेजिस्टर as a GPIO
 * controller, letting gpiolib-acpi.c call the _L02 handler as it would
 * क्रम a real GPIO controller.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>

#घोषणा DRV_NAME			"INT0002 Virtual GPIO"

/* For some reason the भव GPIO pin tied to the GPE is numbered pin 2 */
#घोषणा GPE0A_PME_B0_VIRT_GPIO_PIN	2

#घोषणा GPE0A_PME_B0_STS_BIT		BIT(13)
#घोषणा GPE0A_PME_B0_EN_BIT		BIT(13)
#घोषणा GPE0A_STS_PORT			0x420
#घोषणा GPE0A_EN_PORT			0x428

काष्ठा पूर्णांक0002_data अणु
	काष्ठा gpio_chip chip;
	पूर्णांक parent_irq;
	पूर्णांक wake_enable_count;
पूर्ण;

/*
 * As this is not a real GPIO at all, but just a hack to model an event in
 * ACPI the get / set functions are dummy functions.
 */

अटल पूर्णांक पूर्णांक0002_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस 0;
पूर्ण

अटल व्योम पूर्णांक0002_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			     पूर्णांक value)
अणु
पूर्ण

अटल पूर्णांक पूर्णांक0002_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	वापस 0;
पूर्ण

अटल व्योम पूर्णांक0002_irq_ack(काष्ठा irq_data *data)
अणु
	outl(GPE0A_PME_B0_STS_BIT, GPE0A_STS_PORT);
पूर्ण

अटल व्योम पूर्णांक0002_irq_unmask(काष्ठा irq_data *data)
अणु
	u32 gpe_en_reg;

	gpe_en_reg = inl(GPE0A_EN_PORT);
	gpe_en_reg |= GPE0A_PME_B0_EN_BIT;
	outl(gpe_en_reg, GPE0A_EN_PORT);
पूर्ण

अटल व्योम पूर्णांक0002_irq_mask(काष्ठा irq_data *data)
अणु
	u32 gpe_en_reg;

	gpe_en_reg = inl(GPE0A_EN_PORT);
	gpe_en_reg &= ~GPE0A_PME_B0_EN_BIT;
	outl(gpe_en_reg, GPE0A_EN_PORT);
पूर्ण

अटल पूर्णांक पूर्णांक0002_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा पूर्णांक0002_data *पूर्णांक0002 = container_of(chip, काष्ठा पूर्णांक0002_data, chip);

	/*
	 * Applying of the wakeup flag to our parent IRQ is delayed till प्रणाली
	 * suspend, because we only want to करो this when using s2idle.
	 */
	अगर (on)
		पूर्णांक0002->wake_enable_count++;
	अन्यथा
		पूर्णांक0002->wake_enable_count--;

	वापस 0;
पूर्ण

अटल irqवापस_t पूर्णांक0002_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा gpio_chip *chip = data;
	u32 gpe_sts_reg;

	gpe_sts_reg = inl(GPE0A_STS_PORT);
	अगर (!(gpe_sts_reg & GPE0A_PME_B0_STS_BIT))
		वापस IRQ_NONE;

	generic_handle_irq(irq_find_mapping(chip->irq.करोमुख्य,
					    GPE0A_PME_B0_VIRT_GPIO_PIN));

	pm_wakeup_hard_event(chip->parent);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool पूर्णांक0002_check_wake(व्योम *data)
अणु
	u32 gpe_sts_reg;

	gpe_sts_reg = inl(GPE0A_STS_PORT);
	वापस (gpe_sts_reg & GPE0A_PME_B0_STS_BIT);
पूर्ण

अटल काष्ठा irq_chip पूर्णांक0002_irqchip = अणु
	.name			= DRV_NAME,
	.irq_ack		= पूर्णांक0002_irq_ack,
	.irq_mask		= पूर्णांक0002_irq_mask,
	.irq_unmask		= पूर्णांक0002_irq_unmask,
	.irq_set_wake		= पूर्णांक0002_irq_set_wake,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id पूर्णांक0002_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT, शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_AIRMONT, शून्य),
	अणुपूर्ण
पूर्ण;

अटल व्योम पूर्णांक0002_init_irq_valid_mask(काष्ठा gpio_chip *chip,
					अचिन्हित दीर्घ *valid_mask,
					अचिन्हित पूर्णांक ngpios)
अणु
	biपंचांगap_clear(valid_mask, 0, GPE0A_PME_B0_VIRT_GPIO_PIN);
पूर्ण

अटल पूर्णांक पूर्णांक0002_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा x86_cpu_id *cpu_id;
	काष्ठा पूर्णांक0002_data *पूर्णांक0002;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा gpio_chip *chip;
	पूर्णांक irq, ret;

	/* Menlow has a dअगरferent INT0002 device? <sigh> */
	cpu_id = x86_match_cpu(पूर्णांक0002_cpu_ids);
	अगर (!cpu_id)
		वापस -ENODEV;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	पूर्णांक0002 = devm_kzalloc(dev, माप(*पूर्णांक0002), GFP_KERNEL);
	अगर (!पूर्णांक0002)
		वापस -ENOMEM;

	पूर्णांक0002->parent_irq = irq;

	chip = &पूर्णांक0002->chip;
	chip->label = DRV_NAME;
	chip->parent = dev;
	chip->owner = THIS_MODULE;
	chip->get = पूर्णांक0002_gpio_get;
	chip->set = पूर्णांक0002_gpio_set;
	chip->direction_input = पूर्णांक0002_gpio_get;
	chip->direction_output = पूर्णांक0002_gpio_direction_output;
	chip->base = -1;
	chip->ngpio = GPE0A_PME_B0_VIRT_GPIO_PIN + 1;
	chip->irq.init_valid_mask = पूर्णांक0002_init_irq_valid_mask;

	/*
	 * We directly request the irq here instead of passing a flow-handler
	 * to gpiochip_set_chained_irqchip, because the irq is shared.
	 * FIXME: augment this अगर we managed to pull handling of shared
	 * IRQs पूर्णांकo gpiolib.
	 */
	ret = devm_request_irq(dev, irq, पूर्णांक0002_irq,
			       IRQF_SHARED, "INT0002", chip);
	अगर (ret) अणु
		dev_err(dev, "Error requesting IRQ %d: %d\n", irq, ret);
		वापस ret;
	पूर्ण

	girq = &chip->irq;
	girq->chip = &पूर्णांक0002_irqchip;
	/* This let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_edge_irq;

	ret = devm_gpiochip_add_data(dev, chip, शून्य);
	अगर (ret) अणु
		dev_err(dev, "Error adding gpio chip: %d\n", ret);
		वापस ret;
	पूर्ण

	acpi_रेजिस्टर_wakeup_handler(irq, पूर्णांक0002_check_wake, शून्य);
	device_init_wakeup(dev, true);
	dev_set_drvdata(dev, पूर्णांक0002);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांक0002_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	device_init_wakeup(&pdev->dev, false);
	acpi_unरेजिस्टर_wakeup_handler(पूर्णांक0002_check_wake, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांक0002_suspend(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांक0002_data *पूर्णांक0002 = dev_get_drvdata(dev);

	/*
	 * The INT0002 parent IRQ is often shared with the ACPI GPE IRQ, करोn't
	 * muck with it when firmware based suspend is used, otherwise we may
	 * cause spurious wakeups from firmware managed suspend.
	 */
	अगर (!pm_suspend_via_firmware() && पूर्णांक0002->wake_enable_count)
		enable_irq_wake(पूर्णांक0002->parent_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांक0002_resume(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांक0002_data *पूर्णांक0002 = dev_get_drvdata(dev);

	अगर (!pm_suspend_via_firmware() && पूर्णांक0002->wake_enable_count)
		disable_irq_wake(पूर्णांक0002->parent_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops पूर्णांक0002_pm_ops = अणु
	.suspend = पूर्णांक0002_suspend,
	.resume = पूर्णांक0002_resume,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id पूर्णांक0002_acpi_ids[] = अणु
	अणु "INT0002", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांक0002_acpi_ids);

अटल काष्ठा platक्रमm_driver पूर्णांक0002_driver = अणु
	.driver = अणु
		.name			= DRV_NAME,
		.acpi_match_table	= पूर्णांक0002_acpi_ids,
		.pm			= &पूर्णांक0002_pm_ops,
	पूर्ण,
	.probe	= पूर्णांक0002_probe,
	.हटाओ	= पूर्णांक0002_हटाओ,
पूर्ण;

module_platक्रमm_driver(पूर्णांक0002_driver);

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Intel INT0002 Virtual GPIO driver");
MODULE_LICENSE("GPL v2");
