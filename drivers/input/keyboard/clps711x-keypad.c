<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cirrus Logic CLPS711X Keypad driver
 *
 * Copyright (C) 2014 Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/clps711x.h>

#घोषणा CLPS711X_KEYPAD_COL_COUNT	8

काष्ठा clps711x_gpio_data अणु
	काष्ठा gpio_desc *desc;
	DECLARE_BITMAP(last_state, CLPS711X_KEYPAD_COL_COUNT);
पूर्ण;

काष्ठा clps711x_keypad_data अणु
	काष्ठा regmap			*syscon;
	पूर्णांक				row_count;
	अचिन्हित पूर्णांक			row_shअगरt;
	काष्ठा clps711x_gpio_data	*gpio_data;
पूर्ण;

अटल व्योम clps711x_keypad_poll(काष्ठा input_dev *input)
अणु
	स्थिर अचिन्हित लघु *keycodes = input->keycode;
	काष्ठा clps711x_keypad_data *priv = input_get_drvdata(input);
	bool sync = false;
	पूर्णांक col, row;

	क्रम (col = 0; col < CLPS711X_KEYPAD_COL_COUNT; col++) अणु
		/* Assert column */
		regmap_update_bits(priv->syscon, SYSCON_OFFSET,
				   SYSCON1_KBDSCAN_MASK,
				   SYSCON1_KBDSCAN(8 + col));

		/* Scan rows */
		क्रम (row = 0; row < priv->row_count; row++) अणु
			काष्ठा clps711x_gpio_data *data = &priv->gpio_data[row];
			bool state, state1;

			/* Read twice क्रम protection against fluctuations */
			करो अणु
				state = gpiod_get_value_cansleep(data->desc);
				cond_resched();
				state1 = gpiod_get_value_cansleep(data->desc);
			पूर्ण जबतक (state != state1);

			अगर (test_bit(col, data->last_state) != state) अणु
				पूर्णांक code = MATRIX_SCAN_CODE(row, col,
							    priv->row_shअगरt);

				अगर (state) अणु
					set_bit(col, data->last_state);
					input_event(input,
						    EV_MSC, MSC_SCAN, code);
				पूर्ण अन्यथा अणु
					clear_bit(col, data->last_state);
				पूर्ण

				अगर (keycodes[code])
					input_report_key(input,
							 keycodes[code], state);
				sync = true;
			पूर्ण
		पूर्ण

		/* Set all columns to low */
		regmap_update_bits(priv->syscon, SYSCON_OFFSET,
				   SYSCON1_KBDSCAN_MASK, SYSCON1_KBDSCAN(1));
	पूर्ण

	अगर (sync)
		input_sync(input);
पूर्ण

अटल पूर्णांक clps711x_keypad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clps711x_keypad_data *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा input_dev *input;
	u32 poll_पूर्णांकerval;
	पूर्णांक i, err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->syscon =
		syscon_regmap_lookup_by_compatible("cirrus,ep7209-syscon1");
	अगर (IS_ERR(priv->syscon))
		वापस PTR_ERR(priv->syscon);

	priv->row_count = of_gpio_named_count(np, "row-gpios");
	अगर (priv->row_count < 1)
		वापस -EINVAL;

	priv->gpio_data = devm_kसुस्मृति(dev,
				priv->row_count, माप(*priv->gpio_data),
				GFP_KERNEL);
	अगर (!priv->gpio_data)
		वापस -ENOMEM;

	priv->row_shअगरt = get_count_order(CLPS711X_KEYPAD_COL_COUNT);

	क्रम (i = 0; i < priv->row_count; i++) अणु
		काष्ठा clps711x_gpio_data *data = &priv->gpio_data[i];

		data->desc = devm_gpiod_get_index(dev, "row", i, GPIOD_IN);
		अगर (IS_ERR(data->desc))
			वापस PTR_ERR(data->desc);
	पूर्ण

	err = of_property_पढ़ो_u32(np, "poll-interval", &poll_पूर्णांकerval);
	अगर (err)
		वापस err;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	input_set_drvdata(input, priv);

	input->name		= pdev->name;
	input->dev.parent	= dev;
	input->id.bustype	= BUS_HOST;
	input->id.venकरोr	= 0x0001;
	input->id.product	= 0x0001;
	input->id.version	= 0x0100;

	err = matrix_keypad_build_keymap(शून्य, शून्य, priv->row_count,
					 CLPS711X_KEYPAD_COL_COUNT,
					 शून्य, input);
	अगर (err)
		वापस err;

	input_set_capability(input, EV_MSC, MSC_SCAN);
	अगर (of_property_पढ़ो_bool(np, "autorepeat"))
		__set_bit(EV_REP, input->evbit);

	/* Set all columns to low */
	regmap_update_bits(priv->syscon, SYSCON_OFFSET, SYSCON1_KBDSCAN_MASK,
			   SYSCON1_KBDSCAN(1));


	err = input_setup_polling(input, clps711x_keypad_poll);
	अगर (err)
		वापस err;

	input_set_poll_पूर्णांकerval(input, poll_पूर्णांकerval);

	err = input_रेजिस्टर_device(input);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id clps711x_keypad_of_match[] = अणु
	अणु .compatible = "cirrus,ep7209-keypad", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clps711x_keypad_of_match);

अटल काष्ठा platक्रमm_driver clps711x_keypad_driver = अणु
	.driver	= अणु
		.name		= "clps711x-keypad",
		.of_match_table	= clps711x_keypad_of_match,
	पूर्ण,
	.probe	= clps711x_keypad_probe,
पूर्ण;
module_platक्रमm_driver(clps711x_keypad_driver);

MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("Cirrus Logic CLPS711X Keypad driver");
MODULE_LICENSE("GPL");
