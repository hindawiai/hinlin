<शैली गुरु>
/*
 * Touchscreen driver क्रम the TS-4800 board
 *
 * Copyright (c) 2015 - Savoir-faire Linux
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* polling पूर्णांकerval in ms */
#घोषणा POLL_INTERVAL		3

#घोषणा DEBOUNCE_COUNT		1

/* sensor values are 12-bit wide */
#घोषणा MAX_12BIT		((1 << 12) - 1)

#घोषणा PENDOWN_MASK		0x1

#घोषणा X_OFFSET		0x0
#घोषणा Y_OFFSET		0x2

काष्ठा ts4800_ts अणु
	काष्ठा input_dev        *input;
	काष्ठा device           *dev;
	अक्षर                    phys[32];

	व्योम __iomem            *base;
	काष्ठा regmap           *regmap;
	अचिन्हित पूर्णांक            reg;
	अचिन्हित पूर्णांक            bit;

	bool                    penकरोwn;
	पूर्णांक                     debounce;
पूर्ण;

अटल पूर्णांक ts4800_ts_खोलो(काष्ठा input_dev *input_dev)
अणु
	काष्ठा ts4800_ts *ts = input_get_drvdata(input_dev);
	पूर्णांक error;

	ts->penकरोwn = false;
	ts->debounce = DEBOUNCE_COUNT;

	error = regmap_update_bits(ts->regmap, ts->reg, ts->bit, ts->bit);
	अगर (error) अणु
		dev_warn(ts->dev, "Failed to enable touchscreen: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ts4800_ts_बंद(काष्ठा input_dev *input_dev)
अणु
	काष्ठा ts4800_ts *ts = input_get_drvdata(input_dev);
	पूर्णांक ret;

	ret = regmap_update_bits(ts->regmap, ts->reg, ts->bit, 0);
	अगर (ret)
		dev_warn(ts->dev, "Failed to disable touchscreen\n");

पूर्ण

अटल व्योम ts4800_ts_poll(काष्ठा input_dev *input_dev)
अणु
	काष्ठा ts4800_ts *ts = input_get_drvdata(input_dev);
	u16 last_x = पढ़ोw(ts->base + X_OFFSET);
	u16 last_y = पढ़ोw(ts->base + Y_OFFSET);
	bool penकरोwn = last_x & PENDOWN_MASK;

	अगर (penकरोwn) अणु
		अगर (ts->debounce) अणु
			ts->debounce--;
			वापस;
		पूर्ण

		अगर (!ts->penकरोwn) अणु
			input_report_key(input_dev, BTN_TOUCH, 1);
			ts->penकरोwn = true;
		पूर्ण

		last_x = ((~last_x) >> 4) & MAX_12BIT;
		last_y = ((~last_y) >> 4) & MAX_12BIT;

		input_report_असल(input_dev, ABS_X, last_x);
		input_report_असल(input_dev, ABS_Y, last_y);
		input_sync(input_dev);
	पूर्ण अन्यथा अगर (ts->penकरोwn) अणु
		ts->penकरोwn = false;
		ts->debounce = DEBOUNCE_COUNT;
		input_report_key(input_dev, BTN_TOUCH, 0);
		input_sync(input_dev);
	पूर्ण
पूर्ण

अटल पूर्णांक ts4800_parse_dt(काष्ठा platक्रमm_device *pdev,
			   काष्ठा ts4800_ts *ts)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *syscon_np;
	u32 reg, bit;
	पूर्णांक error;

	syscon_np = of_parse_phandle(np, "syscon", 0);
	अगर (!syscon_np) अणु
		dev_err(dev, "no syscon property\n");
		वापस -ENODEV;
	पूर्ण

	ts->regmap = syscon_node_to_regmap(syscon_np);
	of_node_put(syscon_np);
	अगर (IS_ERR(ts->regmap)) अणु
		dev_err(dev, "cannot get parent's regmap\n");
		वापस PTR_ERR(ts->regmap);
	पूर्ण

	error = of_property_पढ़ो_u32_index(np, "syscon", 1, &reg);
	अगर (error < 0) अणु
		dev_err(dev, "no offset in syscon\n");
		वापस error;
	पूर्ण

	ts->reg = reg;

	error = of_property_पढ़ो_u32_index(np, "syscon", 2, &bit);
	अगर (error < 0) अणु
		dev_err(dev, "no bit in syscon\n");
		वापस error;
	पूर्ण

	ts->bit = BIT(bit);

	वापस 0;
पूर्ण

अटल पूर्णांक ts4800_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *input_dev;
	काष्ठा ts4800_ts *ts;
	पूर्णांक error;

	ts = devm_kzalloc(&pdev->dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	error = ts4800_parse_dt(pdev, ts);
	अगर (error)
		वापस error;

	ts->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ts->base))
		वापस PTR_ERR(ts->base);

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	snम_लिखो(ts->phys, माप(ts->phys), "%s/input0", dev_name(&pdev->dev));
	ts->input = input_dev;
	ts->dev = &pdev->dev;

	input_set_drvdata(input_dev, ts);

	input_dev->name = "TS-4800 Touchscreen";
	input_dev->phys = ts->phys;

	input_dev->खोलो = ts4800_ts_खोलो;
	input_dev->बंद = ts4800_ts_बंद;

	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);
	input_set_असल_params(input_dev, ABS_X, 0, MAX_12BIT, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, MAX_12BIT, 0, 0);

	error = input_setup_polling(input_dev, ts4800_ts_poll);
	अगर (error) अणु
		dev_err(&pdev->dev, "Unable to set up polling: %d\n", error);
		वापस error;
	पूर्ण

	input_set_poll_पूर्णांकerval(input_dev, POLL_INTERVAL);

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"Unable to register input device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ts4800_ts_of_match[] = अणु
	अणु .compatible = "technologic,ts4800-ts", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ts4800_ts_of_match);

अटल काष्ठा platक्रमm_driver ts4800_ts_driver = अणु
	.driver = अणु
		.name = "ts4800-ts",
		.of_match_table = ts4800_ts_of_match,
	पूर्ण,
	.probe = ts4800_ts_probe,
पूर्ण;
module_platक्रमm_driver(ts4800_ts_driver);

MODULE_AUTHOR("Damien Riegel <damien.riegel@savoirfairelinux.com>");
MODULE_DESCRIPTION("TS-4800 Touchscreen Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:ts4800_ts");
