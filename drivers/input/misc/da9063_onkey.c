<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OnKey device driver क्रम DA9063, DA9062 and DA9061 PMICs
 * Copyright (C) 2015  Dialog Semiconductor Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/da9063/core.h>
#समावेश <linux/mfd/da9063/रेजिस्टरs.h>
#समावेश <linux/mfd/da9062/core.h>
#समावेश <linux/mfd/da9062/रेजिस्टरs.h>

काष्ठा da906x_chip_config अणु
	/* REGS */
	पूर्णांक onkey_status;
	पूर्णांक onkey_pwr_संकेतling;
	पूर्णांक onkey_fault_log;
	पूर्णांक onkey_shutकरोwn;
	/* MASKS */
	पूर्णांक onkey_nonkey_mask;
	पूर्णांक onkey_nonkey_lock_mask;
	पूर्णांक onkey_key_reset_mask;
	पूर्णांक onkey_shutकरोwn_mask;
	/* NAMES */
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा da9063_onkey अणु
	काष्ठा delayed_work work;
	काष्ठा input_dev *input;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा da906x_chip_config *config;
	अक्षर phys[32];
	bool key_घातer;
पूर्ण;

अटल स्थिर काष्ठा da906x_chip_config da9063_regs = अणु
	/* REGS */
	.onkey_status = DA9063_REG_STATUS_A,
	.onkey_pwr_संकेतling = DA9063_REG_CONTROL_B,
	.onkey_fault_log = DA9063_REG_FAULT_LOG,
	.onkey_shutकरोwn = DA9063_REG_CONTROL_F,
	/* MASKS */
	.onkey_nonkey_mask = DA9063_NONKEY,
	.onkey_nonkey_lock_mask = DA9063_NONKEY_LOCK,
	.onkey_key_reset_mask = DA9063_KEY_RESET,
	.onkey_shutकरोwn_mask = DA9063_SHUTDOWN,
	/* NAMES */
	.name = DA9063_DRVNAME_ONKEY,
पूर्ण;

अटल स्थिर काष्ठा da906x_chip_config da9062_regs = अणु
	/* REGS */
	.onkey_status = DA9062AA_STATUS_A,
	.onkey_pwr_संकेतling = DA9062AA_CONTROL_B,
	.onkey_fault_log = DA9062AA_FAULT_LOG,
	.onkey_shutकरोwn = DA9062AA_CONTROL_F,
	/* MASKS */
	.onkey_nonkey_mask = DA9062AA_NONKEY_MASK,
	.onkey_nonkey_lock_mask = DA9062AA_NONKEY_LOCK_MASK,
	.onkey_key_reset_mask = DA9062AA_KEY_RESET_MASK,
	.onkey_shutकरोwn_mask = DA9062AA_SHUTDOWN_MASK,
	/* NAMES */
	.name = "da9062-onkey",
पूर्ण;

अटल स्थिर काष्ठा of_device_id da9063_compatible_reg_id_table[] = अणु
	अणु .compatible = "dlg,da9063-onkey", .data = &da9063_regs पूर्ण,
	अणु .compatible = "dlg,da9062-onkey", .data = &da9062_regs पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, da9063_compatible_reg_id_table);

अटल व्योम da9063_poll_on(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da9063_onkey *onkey = container_of(work,
						काष्ठा da9063_onkey,
						work.work);
	स्थिर काष्ठा da906x_chip_config *config = onkey->config;
	अचिन्हित पूर्णांक val;
	पूर्णांक fault_log = 0;
	bool poll = true;
	पूर्णांक error;

	/* Poll to see when the pin is released */
	error = regmap_पढ़ो(onkey->regmap,
			    config->onkey_status,
			    &val);
	अगर (error) अणु
		dev_err(onkey->dev,
			"Failed to read ON status: %d\n", error);
		जाओ err_poll;
	पूर्ण

	अगर (!(val & config->onkey_nonkey_mask)) अणु
		error = regmap_update_bits(onkey->regmap,
					   config->onkey_pwr_संकेतling,
					   config->onkey_nonkey_lock_mask,
					   0);
		अगर (error) अणु
			dev_err(onkey->dev,
				"Failed to reset the Key Delay %d\n", error);
			जाओ err_poll;
		पूर्ण

		input_report_key(onkey->input, KEY_POWER, 0);
		input_sync(onkey->input);

		poll = false;
	पूर्ण

	/*
	 * If the fault log KEY_RESET is detected, then clear it
	 * and shut करोwn the प्रणाली.
	 */
	error = regmap_पढ़ो(onkey->regmap,
			    config->onkey_fault_log,
			    &fault_log);
	अगर (error) अणु
		dev_warn(&onkey->input->dev,
			 "Cannot read FAULT_LOG: %d\n", error);
	पूर्ण अन्यथा अगर (fault_log & config->onkey_key_reset_mask) अणु
		error = regmap_ग_लिखो(onkey->regmap,
				     config->onkey_fault_log,
				     config->onkey_key_reset_mask);
		अगर (error) अणु
			dev_warn(&onkey->input->dev,
				 "Cannot reset KEY_RESET fault log: %d\n",
				 error);
		पूर्ण अन्यथा अणु
			/* at this poपूर्णांक we करो any S/W housekeeping
			 * and then send shutकरोwn command
			 */
			dev_dbg(&onkey->input->dev,
				"Sending SHUTDOWN to PMIC ...\n");
			error = regmap_ग_लिखो(onkey->regmap,
					     config->onkey_shutकरोwn,
					     config->onkey_shutकरोwn_mask);
			अगर (error)
				dev_err(&onkey->input->dev,
					"Cannot SHUTDOWN PMIC: %d\n",
					error);
		पूर्ण
	पूर्ण

err_poll:
	अगर (poll)
		schedule_delayed_work(&onkey->work, msecs_to_jअगरfies(50));
पूर्ण

अटल irqवापस_t da9063_onkey_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9063_onkey *onkey = data;
	स्थिर काष्ठा da906x_chip_config *config = onkey->config;
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	error = regmap_पढ़ो(onkey->regmap,
			    config->onkey_status,
			    &val);
	अगर (onkey->key_घातer && !error && (val & config->onkey_nonkey_mask)) अणु
		input_report_key(onkey->input, KEY_POWER, 1);
		input_sync(onkey->input);
		schedule_delayed_work(&onkey->work, 0);
		dev_dbg(onkey->dev, "KEY_POWER long press.\n");
	पूर्ण अन्यथा अणु
		input_report_key(onkey->input, KEY_POWER, 1);
		input_sync(onkey->input);
		input_report_key(onkey->input, KEY_POWER, 0);
		input_sync(onkey->input);
		dev_dbg(onkey->dev, "KEY_POWER short press.\n");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम da9063_cancel_poll(व्योम *data)
अणु
	काष्ठा da9063_onkey *onkey = data;

	cancel_delayed_work_sync(&onkey->work);
पूर्ण

अटल पूर्णांक da9063_onkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9063_onkey *onkey;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक irq;
	पूर्णांक error;

	match = of_match_node(da9063_compatible_reg_id_table,
			      pdev->dev.of_node);
	अगर (!match)
		वापस -ENXIO;

	onkey = devm_kzalloc(&pdev->dev, माप(काष्ठा da9063_onkey),
			     GFP_KERNEL);
	अगर (!onkey) अणु
		dev_err(&pdev->dev, "Failed to allocate memory.\n");
		वापस -ENOMEM;
	पूर्ण

	onkey->config = match->data;
	onkey->dev = &pdev->dev;

	onkey->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!onkey->regmap) अणु
		dev_err(&pdev->dev, "Parent regmap unavailable.\n");
		वापस -ENXIO;
	पूर्ण

	onkey->key_घातer = !of_property_पढ़ो_bool(pdev->dev.of_node,
						  "dlg,disable-key-power");

	onkey->input = devm_input_allocate_device(&pdev->dev);
	अगर (!onkey->input) अणु
		dev_err(&pdev->dev, "Failed to allocated input device.\n");
		वापस -ENOMEM;
	पूर्ण

	onkey->input->name = onkey->config->name;
	snम_लिखो(onkey->phys, माप(onkey->phys), "%s/input0",
		 onkey->config->name);
	onkey->input->phys = onkey->phys;
	onkey->input->dev.parent = &pdev->dev;

	input_set_capability(onkey->input, EV_KEY, KEY_POWER);

	INIT_DELAYED_WORK(&onkey->work, da9063_poll_on);

	error = devm_add_action(&pdev->dev, da9063_cancel_poll, onkey);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"Failed to add cancel poll action: %d\n",
			error);
		वापस error;
	पूर्ण

	irq = platक्रमm_get_irq_byname(pdev, "ONKEY");
	अगर (irq < 0)
		वापस irq;

	error = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
					  शून्य, da9063_onkey_irq_handler,
					  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					  "ONKEY", onkey);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"Failed to request IRQ %d: %d\n", irq, error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(onkey->input);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"Failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9063_onkey_driver = अणु
	.probe	= da9063_onkey_probe,
	.driver	= अणु
		.name	= DA9063_DRVNAME_ONKEY,
		.of_match_table = da9063_compatible_reg_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(da9063_onkey_driver);

MODULE_AUTHOR("S Twiss <stwiss.opensource@diasemi.com>");
MODULE_DESCRIPTION("Onkey device driver for Dialog DA9063, DA9062 and DA9061");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DA9063_DRVNAME_ONKEY);
