<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Azoteq IQS620A/621/622/624/625 Keys and Switches
 *
 * Copyright (C) 2019 Jeff LaBundy <jeff@labundy.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/iqs62x.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

क्रमागत अणु
	IQS62X_SW_HALL_N,
	IQS62X_SW_HALL_S,
पूर्ण;

अटल स्थिर अक्षर * स्थिर iqs62x_चयन_names[] = अणु
	[IQS62X_SW_HALL_N] = "hall-switch-north",
	[IQS62X_SW_HALL_S] = "hall-switch-south",
पूर्ण;

काष्ठा iqs62x_चयन_desc अणु
	क्रमागत iqs62x_event_flag flag;
	अचिन्हित पूर्णांक code;
	bool enabled;
पूर्ण;

काष्ठा iqs62x_keys_निजी अणु
	काष्ठा iqs62x_core *iqs62x;
	काष्ठा input_dev *input;
	काष्ठा notअगरier_block notअगरier;
	काष्ठा iqs62x_चयन_desc चयनes[ARRAY_SIZE(iqs62x_चयन_names)];
	अचिन्हित पूर्णांक keycode[IQS62X_NUM_KEYS];
	अचिन्हित पूर्णांक keycodemax;
	u8 पूर्णांकerval;
पूर्ण;

अटल पूर्णांक iqs62x_keys_parse_prop(काष्ठा platक्रमm_device *pdev,
				  काष्ठा iqs62x_keys_निजी *iqs62x_keys)
अणु
	काष्ठा fwnode_handle *child;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, i;

	ret = device_property_count_u32(&pdev->dev, "linux,keycodes");
	अगर (ret > IQS62X_NUM_KEYS) अणु
		dev_err(&pdev->dev, "Too many keycodes present\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to count keycodes: %d\n", ret);
		वापस ret;
	पूर्ण
	iqs62x_keys->keycodemax = ret;

	ret = device_property_पढ़ो_u32_array(&pdev->dev, "linux,keycodes",
					     iqs62x_keys->keycode,
					     iqs62x_keys->keycodemax);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to read keycodes: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(iqs62x_keys->चयनes); i++) अणु
		child = device_get_named_child_node(&pdev->dev,
						    iqs62x_चयन_names[i]);
		अगर (!child)
			जारी;

		ret = fwnode_property_पढ़ो_u32(child, "linux,code", &val);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Failed to read switch code: %d\n",
				ret);
			वापस ret;
		पूर्ण
		iqs62x_keys->चयनes[i].code = val;
		iqs62x_keys->चयनes[i].enabled = true;

		अगर (fwnode_property_present(child, "azoteq,use-prox"))
			iqs62x_keys->चयनes[i].flag = (i == IQS62X_SW_HALL_N ?
							 IQS62X_EVENT_HALL_N_P :
							 IQS62X_EVENT_HALL_S_P);
		अन्यथा
			iqs62x_keys->चयनes[i].flag = (i == IQS62X_SW_HALL_N ?
							 IQS62X_EVENT_HALL_N_T :
							 IQS62X_EVENT_HALL_S_T);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iqs62x_keys_init(काष्ठा iqs62x_keys_निजी *iqs62x_keys)
अणु
	काष्ठा iqs62x_core *iqs62x = iqs62x_keys->iqs62x;
	क्रमागत iqs62x_event_flag flag;
	अचिन्हित पूर्णांक event_reg, val;
	अचिन्हित पूर्णांक event_mask = 0;
	पूर्णांक ret, i;

	चयन (iqs62x->dev_desc->prod_num) अणु
	हाल IQS620_PROD_NUM:
	हाल IQS621_PROD_NUM:
	हाल IQS622_PROD_NUM:
		event_reg = IQS620_GLBL_EVENT_MASK;

		/*
		 * Discreet button, hysteresis and SAR UI flags represent keys
		 * and are unmasked अगर mapped to a valid keycode.
		 */
		क्रम (i = 0; i < iqs62x_keys->keycodemax; i++) अणु
			अगर (iqs62x_keys->keycode[i] == KEY_RESERVED)
				जारी;

			अगर (iqs62x_events[i].reg == IQS62X_EVENT_PROX)
				event_mask |= iqs62x->dev_desc->prox_mask;
			अन्यथा अगर (iqs62x_events[i].reg == IQS62X_EVENT_HYST)
				event_mask |= (iqs62x->dev_desc->hyst_mask |
					       iqs62x->dev_desc->sar_mask);
		पूर्ण

		ret = regmap_पढ़ो(iqs62x->regmap, iqs62x->dev_desc->hall_flags,
				  &val);
		अगर (ret)
			वापस ret;

		/*
		 * Hall UI flags represent चयनes and are unmasked अगर their
		 * corresponding child nodes are present.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(iqs62x_keys->चयनes); i++) अणु
			अगर (!(iqs62x_keys->चयनes[i].enabled))
				जारी;

			flag = iqs62x_keys->चयनes[i].flag;

			अगर (iqs62x_events[flag].reg != IQS62X_EVENT_HALL)
				जारी;

			event_mask |= iqs62x->dev_desc->hall_mask;

			input_report_चयन(iqs62x_keys->input,
					    iqs62x_keys->चयनes[i].code,
					    (val & iqs62x_events[flag].mask) ==
					    iqs62x_events[flag].val);
		पूर्ण

		input_sync(iqs62x_keys->input);
		अवरोध;

	हाल IQS624_PROD_NUM:
		event_reg = IQS624_HALL_UI;

		/*
		 * Interval change events represent keys and are unmasked अगर
		 * either wheel movement flag is mapped to a valid keycode.
		 */
		अगर (iqs62x_keys->keycode[IQS62X_EVENT_WHEEL_UP] != KEY_RESERVED)
			event_mask |= IQS624_HALL_UI_INT_EVENT;

		अगर (iqs62x_keys->keycode[IQS62X_EVENT_WHEEL_DN] != KEY_RESERVED)
			event_mask |= IQS624_HALL_UI_INT_EVENT;

		ret = regmap_पढ़ो(iqs62x->regmap, iqs62x->dev_desc->पूर्णांकerval,
				  &val);
		अगर (ret)
			वापस ret;

		iqs62x_keys->पूर्णांकerval = val;
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस regmap_update_bits(iqs62x->regmap, event_reg, event_mask, 0);
पूर्ण

अटल पूर्णांक iqs62x_keys_notअगरier(काष्ठा notअगरier_block *notअगरier,
				अचिन्हित दीर्घ event_flags, व्योम *context)
अणु
	काष्ठा iqs62x_event_data *event_data = context;
	काष्ठा iqs62x_keys_निजी *iqs62x_keys;
	पूर्णांक ret, i;

	iqs62x_keys = container_of(notअगरier, काष्ठा iqs62x_keys_निजी,
				   notअगरier);

	अगर (event_flags & BIT(IQS62X_EVENT_SYS_RESET)) अणु
		ret = iqs62x_keys_init(iqs62x_keys);
		अगर (ret) अणु
			dev_err(iqs62x_keys->input->dev.parent,
				"Failed to re-initialize device: %d\n", ret);
			वापस NOTIFY_BAD;
		पूर्ण

		वापस NOTIFY_OK;
	पूर्ण

	क्रम (i = 0; i < iqs62x_keys->keycodemax; i++) अणु
		अगर (iqs62x_events[i].reg == IQS62X_EVENT_WHEEL &&
		    event_data->पूर्णांकerval == iqs62x_keys->पूर्णांकerval)
			जारी;

		input_report_key(iqs62x_keys->input, iqs62x_keys->keycode[i],
				 event_flags & BIT(i));
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(iqs62x_keys->चयनes); i++)
		अगर (iqs62x_keys->चयनes[i].enabled)
			input_report_चयन(iqs62x_keys->input,
					    iqs62x_keys->चयनes[i].code,
					    event_flags &
					    BIT(iqs62x_keys->चयनes[i].flag));

	input_sync(iqs62x_keys->input);

	अगर (event_data->पूर्णांकerval == iqs62x_keys->पूर्णांकerval)
		वापस NOTIFY_OK;

	/*
	 * Each frame contains at most one wheel event (up or करोwn), in which
	 * हाल a complementary release cycle is emulated.
	 */
	अगर (event_flags & BIT(IQS62X_EVENT_WHEEL_UP)) अणु
		input_report_key(iqs62x_keys->input,
				 iqs62x_keys->keycode[IQS62X_EVENT_WHEEL_UP],
				 0);
		input_sync(iqs62x_keys->input);
	पूर्ण अन्यथा अगर (event_flags & BIT(IQS62X_EVENT_WHEEL_DN)) अणु
		input_report_key(iqs62x_keys->input,
				 iqs62x_keys->keycode[IQS62X_EVENT_WHEEL_DN],
				 0);
		input_sync(iqs62x_keys->input);
	पूर्ण

	iqs62x_keys->पूर्णांकerval = event_data->पूर्णांकerval;

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक iqs62x_keys_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iqs62x_core *iqs62x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा iqs62x_keys_निजी *iqs62x_keys;
	काष्ठा input_dev *input;
	पूर्णांक ret, i;

	iqs62x_keys = devm_kzalloc(&pdev->dev, माप(*iqs62x_keys),
				   GFP_KERNEL);
	अगर (!iqs62x_keys)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, iqs62x_keys);

	ret = iqs62x_keys_parse_prop(pdev, iqs62x_keys);
	अगर (ret)
		वापस ret;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	input->keycodemax = iqs62x_keys->keycodemax;
	input->keycode = iqs62x_keys->keycode;
	input->keycodesize = माप(*iqs62x_keys->keycode);

	input->name = iqs62x->dev_desc->dev_name;
	input->id.bustype = BUS_I2C;

	क्रम (i = 0; i < iqs62x_keys->keycodemax; i++)
		अगर (iqs62x_keys->keycode[i] != KEY_RESERVED)
			input_set_capability(input, EV_KEY,
					     iqs62x_keys->keycode[i]);

	क्रम (i = 0; i < ARRAY_SIZE(iqs62x_keys->चयनes); i++)
		अगर (iqs62x_keys->चयनes[i].enabled)
			input_set_capability(input, EV_SW,
					     iqs62x_keys->चयनes[i].code);

	iqs62x_keys->iqs62x = iqs62x;
	iqs62x_keys->input = input;

	ret = iqs62x_keys_init(iqs62x_keys);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to initialize device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = input_रेजिस्टर_device(iqs62x_keys->input);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register device: %d\n", ret);
		वापस ret;
	पूर्ण

	iqs62x_keys->notअगरier.notअगरier_call = iqs62x_keys_notअगरier;
	ret = blocking_notअगरier_chain_रेजिस्टर(&iqs62x_keys->iqs62x->nh,
					       &iqs62x_keys->notअगरier);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to register notifier: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक iqs62x_keys_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iqs62x_keys_निजी *iqs62x_keys = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = blocking_notअगरier_chain_unरेजिस्टर(&iqs62x_keys->iqs62x->nh,
						 &iqs62x_keys->notअगरier);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to unregister notifier: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver iqs62x_keys_platक्रमm_driver = अणु
	.driver = अणु
		.name = "iqs62x-keys",
	पूर्ण,
	.probe = iqs62x_keys_probe,
	.हटाओ = iqs62x_keys_हटाओ,
पूर्ण;
module_platक्रमm_driver(iqs62x_keys_platक्रमm_driver);

MODULE_AUTHOR("Jeff LaBundy <jeff@labundy.com>");
MODULE_DESCRIPTION("Azoteq IQS620A/621/622/624/625 Keys and Switches");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:iqs62x-keys");
