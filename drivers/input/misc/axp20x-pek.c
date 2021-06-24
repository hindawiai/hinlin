<शैली गुरु>
/*
 * axp20x घातer button driver.
 *
 * Copyright (C) 2013 Carlo Caione <carlo@caione.org>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/irq.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/axp20x.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा AXP20X_PEK_STARTUP_MASK		(0xc0)
#घोषणा AXP20X_PEK_SHUTDOWN_MASK	(0x03)

काष्ठा axp20x_info अणु
	स्थिर काष्ठा axp20x_समय *startup_समय;
	अचिन्हित पूर्णांक startup_mask;
	स्थिर काष्ठा axp20x_समय *shutकरोwn_समय;
	अचिन्हित पूर्णांक shutकरोwn_mask;
पूर्ण;

काष्ठा axp20x_pek अणु
	काष्ठा axp20x_dev *axp20x;
	काष्ठा input_dev *input;
	काष्ठा axp20x_info *info;
	पूर्णांक irq_dbr;
	पूर्णांक irq_dbf;
पूर्ण;

काष्ठा axp20x_समय अणु
	अचिन्हित पूर्णांक समय;
	अचिन्हित पूर्णांक idx;
पूर्ण;

अटल स्थिर काष्ठा axp20x_समय startup_समय[] = अणु
	अणु .समय = 128,  .idx = 0 पूर्ण,
	अणु .समय = 1000, .idx = 2 पूर्ण,
	अणु .समय = 3000, .idx = 1 पूर्ण,
	अणु .समय = 2000, .idx = 3 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा axp20x_समय axp221_startup_समय[] = अणु
	अणु .समय = 128,  .idx = 0 पूर्ण,
	अणु .समय = 1000, .idx = 1 पूर्ण,
	अणु .समय = 2000, .idx = 2 पूर्ण,
	अणु .समय = 3000, .idx = 3 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा axp20x_समय shutकरोwn_समय[] = अणु
	अणु .समय = 4000,  .idx = 0 पूर्ण,
	अणु .समय = 6000,  .idx = 1 पूर्ण,
	अणु .समय = 8000,  .idx = 2 पूर्ण,
	अणु .समय = 10000, .idx = 3 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा axp20x_info axp20x_info = अणु
	.startup_समय = startup_समय,
	.startup_mask = AXP20X_PEK_STARTUP_MASK,
	.shutकरोwn_समय = shutकरोwn_समय,
	.shutकरोwn_mask = AXP20X_PEK_SHUTDOWN_MASK,
पूर्ण;

अटल स्थिर काष्ठा axp20x_info axp221_info = अणु
	.startup_समय = axp221_startup_समय,
	.startup_mask = AXP20X_PEK_STARTUP_MASK,
	.shutकरोwn_समय = shutकरोwn_समय,
	.shutकरोwn_mask = AXP20X_PEK_SHUTDOWN_MASK,
पूर्ण;

अटल sमाप_प्रकार axp20x_show_attr(काष्ठा device *dev,
				स्थिर काष्ठा axp20x_समय *समय,
				अचिन्हित पूर्णांक mask, अक्षर *buf)
अणु
	काष्ठा axp20x_pek *axp20x_pek = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, i;

	ret = regmap_पढ़ो(axp20x_pek->axp20x->regmap, AXP20X_PEK_KEY, &val);
	अगर (ret != 0)
		वापस ret;

	val &= mask;
	val >>= ffs(mask) - 1;

	क्रम (i = 0; i < 4; i++)
		अगर (val == समय[i].idx)
			val = समय[i].समय;

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार axp20x_show_attr_startup(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा axp20x_pek *axp20x_pek = dev_get_drvdata(dev);

	वापस axp20x_show_attr(dev, axp20x_pek->info->startup_समय,
				axp20x_pek->info->startup_mask, buf);
पूर्ण

अटल sमाप_प्रकार axp20x_show_attr_shutकरोwn(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा axp20x_pek *axp20x_pek = dev_get_drvdata(dev);

	वापस axp20x_show_attr(dev, axp20x_pek->info->shutकरोwn_समय,
				axp20x_pek->info->shutकरोwn_mask, buf);
पूर्ण

अटल sमाप_प्रकार axp20x_store_attr(काष्ठा device *dev,
				 स्थिर काष्ठा axp20x_समय *समय,
				 अचिन्हित पूर्णांक mask, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	काष्ठा axp20x_pek *axp20x_pek = dev_get_drvdata(dev);
	अक्षर val_str[20];
	माप_प्रकार len;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक val, idx = 0;
	अचिन्हित पूर्णांक best_err = अच_पूर्णांक_उच्च;

	val_str[माप(val_str) - 1] = '\0';
	म_नकलन(val_str, buf, माप(val_str) - 1);
	len = म_माप(val_str);

	अगर (len && val_str[len - 1] == '\n')
		val_str[len - 1] = '\0';

	ret = kstrtouपूर्णांक(val_str, 10, &val);
	अगर (ret)
		वापस ret;

	क्रम (i = 3; i >= 0; i--) अणु
		अचिन्हित पूर्णांक err;

		err = असल(समय[i].समय - val);
		अगर (err < best_err) अणु
			best_err = err;
			idx = समय[i].idx;
		पूर्ण

		अगर (!err)
			अवरोध;
	पूर्ण

	idx <<= ffs(mask) - 1;
	ret = regmap_update_bits(axp20x_pek->axp20x->regmap, AXP20X_PEK_KEY,
				 mask, idx);
	अगर (ret != 0)
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल sमाप_प्रकार axp20x_store_attr_startup(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा axp20x_pek *axp20x_pek = dev_get_drvdata(dev);

	वापस axp20x_store_attr(dev, axp20x_pek->info->startup_समय,
				 axp20x_pek->info->startup_mask, buf, count);
पूर्ण

अटल sमाप_प्रकार axp20x_store_attr_shutकरोwn(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा axp20x_pek *axp20x_pek = dev_get_drvdata(dev);

	वापस axp20x_store_attr(dev, axp20x_pek->info->shutकरोwn_समय,
				 axp20x_pek->info->shutकरोwn_mask, buf, count);
पूर्ण

अटल DEVICE_ATTR(startup, 0644, axp20x_show_attr_startup,
		   axp20x_store_attr_startup);
अटल DEVICE_ATTR(shutकरोwn, 0644, axp20x_show_attr_shutकरोwn,
		   axp20x_store_attr_shutकरोwn);

अटल काष्ठा attribute *axp20x_attrs[] = अणु
	&dev_attr_startup.attr,
	&dev_attr_shutकरोwn.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(axp20x);

अटल irqवापस_t axp20x_pek_irq(पूर्णांक irq, व्योम *pwr)
अणु
	काष्ठा axp20x_pek *axp20x_pek = pwr;
	काष्ठा input_dev *idev = axp20x_pek->input;

	अगर (!idev)
		वापस IRQ_HANDLED;

	/*
	 * The घातer-button is connected to ground so a falling edge (dbf)
	 * means it is pressed.
	 */
	अगर (irq == axp20x_pek->irq_dbf)
		input_report_key(idev, KEY_POWER, true);
	अन्यथा अगर (irq == axp20x_pek->irq_dbr)
		input_report_key(idev, KEY_POWER, false);

	input_sync(idev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक axp20x_pek_probe_input_device(काष्ठा axp20x_pek *axp20x_pek,
					 काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *idev;
	पूर्णांक error;

	axp20x_pek->input = devm_input_allocate_device(&pdev->dev);
	अगर (!axp20x_pek->input)
		वापस -ENOMEM;

	idev = axp20x_pek->input;

	idev->name = "axp20x-pek";
	idev->phys = "m1kbd/input2";
	idev->dev.parent = &pdev->dev;

	input_set_capability(idev, EV_KEY, KEY_POWER);

	input_set_drvdata(idev, axp20x_pek);

	error = input_रेजिस्टर_device(idev);
	अगर (error) अणु
		dev_err(&pdev->dev, "Can't register input device: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल bool axp20x_pek_should_रेजिस्टर_input(काष्ठा axp20x_pek *axp20x_pek,
					     काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित दीर्घ दीर्घ hrv = 0;
	acpi_status status;

	अगर (IS_ENABLED(CONFIG_INPUT_SOC_BUTTON_ARRAY) &&
	    axp20x_pek->axp20x->variant == AXP288_ID) अणु
		status = acpi_evaluate_पूर्णांकeger(ACPI_HANDLE(pdev->dev.parent),
					       "_HRV", शून्य, &hrv);
		अगर (ACPI_FAILURE(status))
			dev_err(&pdev->dev, "Failed to get PMIC hardware revision\n");

		/*
		 * On Cherry Trail platक्रमms (hrv == 3), करो not रेजिस्टर the
		 * input device अगर there is an "INTCFD9" or "ACPI0011" gpio
		 * button ACPI device, as that handles the घातer button too,
		 * and otherwise we end up reporting all presses twice.
		 */
		अगर (hrv == 3 && (acpi_dev_present("INTCFD9", शून्य, -1) ||
				 acpi_dev_present("ACPI0011", शून्य, -1)))
			वापस false;

	पूर्ण

	वापस true;
पूर्ण
#अन्यथा
अटल bool axp20x_pek_should_रेजिस्टर_input(काष्ठा axp20x_pek *axp20x_pek,
					     काष्ठा platक्रमm_device *pdev)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक axp20x_pek_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axp20x_pek *axp20x_pek;
	स्थिर काष्ठा platक्रमm_device_id *match = platक्रमm_get_device_id(pdev);
	पूर्णांक error;

	अगर (!match) अणु
		dev_err(&pdev->dev, "Failed to get platform_device_id\n");
		वापस -EINVAL;
	पूर्ण

	axp20x_pek = devm_kzalloc(&pdev->dev, माप(काष्ठा axp20x_pek),
				  GFP_KERNEL);
	अगर (!axp20x_pek)
		वापस -ENOMEM;

	axp20x_pek->axp20x = dev_get_drvdata(pdev->dev.parent);

	axp20x_pek->irq_dbr = platक्रमm_get_irq_byname(pdev, "PEK_DBR");
	अगर (axp20x_pek->irq_dbr < 0)
		वापस axp20x_pek->irq_dbr;
	axp20x_pek->irq_dbr = regmap_irq_get_virq(
			axp20x_pek->axp20x->regmap_irqc, axp20x_pek->irq_dbr);

	axp20x_pek->irq_dbf = platक्रमm_get_irq_byname(pdev, "PEK_DBF");
	अगर (axp20x_pek->irq_dbf < 0)
		वापस axp20x_pek->irq_dbf;
	axp20x_pek->irq_dbf = regmap_irq_get_virq(
			axp20x_pek->axp20x->regmap_irqc, axp20x_pek->irq_dbf);

	अगर (axp20x_pek_should_रेजिस्टर_input(axp20x_pek, pdev)) अणु
		error = axp20x_pek_probe_input_device(axp20x_pek, pdev);
		अगर (error)
			वापस error;
	पूर्ण

	axp20x_pek->info = (काष्ठा axp20x_info *)match->driver_data;

	error = devm_request_any_context_irq(&pdev->dev, axp20x_pek->irq_dbr,
					     axp20x_pek_irq, 0,
					     "axp20x-pek-dbr", axp20x_pek);
	अगर (error < 0) अणु
		dev_err(&pdev->dev, "Failed to request dbr IRQ#%d: %d\n",
			axp20x_pek->irq_dbr, error);
		वापस error;
	पूर्ण

	error = devm_request_any_context_irq(&pdev->dev, axp20x_pek->irq_dbf,
					  axp20x_pek_irq, 0,
					  "axp20x-pek-dbf", axp20x_pek);
	अगर (error < 0) अणु
		dev_err(&pdev->dev, "Failed to request dbf IRQ#%d: %d\n",
			axp20x_pek->irq_dbf, error);
		वापस error;
	पूर्ण

	device_init_wakeup(&pdev->dev, true);

	platक्रमm_set_drvdata(pdev, axp20x_pek);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused axp20x_pek_suspend(काष्ठा device *dev)
अणु
	काष्ठा axp20x_pek *axp20x_pek = dev_get_drvdata(dev);

	/*
	 * As nested thपढ़ोed IRQs are not स्वतःmatically disabled during
	 * suspend, we must explicitly disable non-wakeup IRQs.
	 */
	अगर (device_may_wakeup(dev)) अणु
		enable_irq_wake(axp20x_pek->irq_dbf);
		enable_irq_wake(axp20x_pek->irq_dbr);
	पूर्ण अन्यथा अणु
		disable_irq(axp20x_pek->irq_dbf);
		disable_irq(axp20x_pek->irq_dbr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused axp20x_pek_resume(काष्ठा device *dev)
अणु
	काष्ठा axp20x_pek *axp20x_pek = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev)) अणु
		disable_irq_wake(axp20x_pek->irq_dbf);
		disable_irq_wake(axp20x_pek->irq_dbr);
	पूर्ण अन्यथा अणु
		enable_irq(axp20x_pek->irq_dbf);
		enable_irq(axp20x_pek->irq_dbr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused axp20x_pek_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा axp20x_pek *axp20x_pek = dev_get_drvdata(dev);

	अगर (axp20x_pek->axp20x->variant != AXP288_ID)
		वापस 0;

	/*
	 * Clear पूर्णांकerrupts from button presses during suspend, to aव्योम
	 * a wakeup घातer-button press getting reported to userspace.
	 */
	regmap_ग_लिखो(axp20x_pek->axp20x->regmap,
		     AXP20X_IRQ1_STATE + AXP288_IRQ_POKN / 8,
		     BIT(AXP288_IRQ_POKN % 8));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops axp20x_pek_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(axp20x_pek_suspend, axp20x_pek_resume)
#अगर_घोषित CONFIG_PM_SLEEP
	.resume_noirq = axp20x_pek_resume_noirq,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id axp_pek_id_match[] = अणु
	अणु
		.name = "axp20x-pek",
		.driver_data = (kernel_uदीर्घ_t)&axp20x_info,
	पूर्ण,
	अणु
		.name = "axp221-pek",
		.driver_data = (kernel_uदीर्घ_t)&axp221_info,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, axp_pek_id_match);

अटल काष्ठा platक्रमm_driver axp20x_pek_driver = अणु
	.probe		= axp20x_pek_probe,
	.id_table	= axp_pek_id_match,
	.driver		= अणु
		.name		= "axp20x-pek",
		.pm		= &axp20x_pek_pm_ops,
		.dev_groups	= axp20x_groups,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axp20x_pek_driver);

MODULE_DESCRIPTION("axp20x Power Button");
MODULE_AUTHOR("Carlo Caione <carlo@caione.org>");
MODULE_LICENSE("GPL");
