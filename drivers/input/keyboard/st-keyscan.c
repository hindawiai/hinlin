<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics Key Scanning driver
 *
 * Copyright (c) 2014 STMicroelectonics Ltd.
 * Author: Stuart Menefy <stuart.menefy@st.com>
 *
 * Based on sh_keysc.c, copyright 2008 Magnus Damm
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/input/matrix_keypad.h>

#घोषणा ST_KEYSCAN_MAXKEYS 16

#घोषणा KEYSCAN_CONFIG_OFF		0x0
#घोषणा KEYSCAN_CONFIG_ENABLE		0x1
#घोषणा KEYSCAN_DEBOUNCE_TIME_OFF	0x4
#घोषणा KEYSCAN_MATRIX_STATE_OFF	0x8
#घोषणा KEYSCAN_MATRIX_DIM_OFF		0xc
#घोषणा KEYSCAN_MATRIX_DIM_X_SHIFT	0x0
#घोषणा KEYSCAN_MATRIX_DIM_Y_SHIFT	0x2

काष्ठा st_keyscan अणु
	व्योम __iomem *base;
	पूर्णांक irq;
	काष्ठा clk *clk;
	काष्ठा input_dev *input_dev;
	अचिन्हित दीर्घ last_state;
	अचिन्हित पूर्णांक n_rows;
	अचिन्हित पूर्णांक n_cols;
	अचिन्हित पूर्णांक debounce_us;
पूर्ण;

अटल irqवापस_t keyscan_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा st_keyscan *keypad = dev_id;
	अचिन्हित लघु *keycode = keypad->input_dev->keycode;
	अचिन्हित दीर्घ state, change;
	पूर्णांक bit_nr;

	state = पढ़ोl(keypad->base + KEYSCAN_MATRIX_STATE_OFF) & 0xffff;
	change = keypad->last_state ^ state;
	keypad->last_state = state;

	क्रम_each_set_bit(bit_nr, &change, BITS_PER_LONG)
		input_report_key(keypad->input_dev,
				 keycode[bit_nr], state & BIT(bit_nr));

	input_sync(keypad->input_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक keyscan_start(काष्ठा st_keyscan *keypad)
अणु
	पूर्णांक error;

	error = clk_enable(keypad->clk);
	अगर (error)
		वापस error;

	ग_लिखोl(keypad->debounce_us * (clk_get_rate(keypad->clk) / 1000000),
	       keypad->base + KEYSCAN_DEBOUNCE_TIME_OFF);

	ग_लिखोl(((keypad->n_cols - 1) << KEYSCAN_MATRIX_DIM_X_SHIFT) |
	       ((keypad->n_rows - 1) << KEYSCAN_MATRIX_DIM_Y_SHIFT),
	       keypad->base + KEYSCAN_MATRIX_DIM_OFF);

	ग_लिखोl(KEYSCAN_CONFIG_ENABLE, keypad->base + KEYSCAN_CONFIG_OFF);

	वापस 0;
पूर्ण

अटल व्योम keyscan_stop(काष्ठा st_keyscan *keypad)
अणु
	ग_लिखोl(0, keypad->base + KEYSCAN_CONFIG_OFF);

	clk_disable(keypad->clk);
पूर्ण

अटल पूर्णांक keyscan_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा st_keyscan *keypad = input_get_drvdata(dev);

	वापस keyscan_start(keypad);
पूर्ण

अटल व्योम keyscan_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा st_keyscan *keypad = input_get_drvdata(dev);

	keyscan_stop(keypad);
पूर्ण

अटल पूर्णांक keypad_matrix_key_parse_dt(काष्ठा st_keyscan *keypad_data)
अणु
	काष्ठा device *dev = keypad_data->input_dev->dev.parent;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक error;

	error = matrix_keypad_parse_properties(dev, &keypad_data->n_rows,
					       &keypad_data->n_cols);
	अगर (error) अणु
		dev_err(dev, "failed to parse keypad params\n");
		वापस error;
	पूर्ण

	of_property_पढ़ो_u32(np, "st,debounce-us", &keypad_data->debounce_us);

	dev_dbg(dev, "n_rows=%d n_col=%d debounce=%d\n",
		keypad_data->n_rows, keypad_data->n_cols,
		keypad_data->debounce_us);

	वापस 0;
पूर्ण

अटल पूर्णांक keyscan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा st_keyscan *keypad_data;
	काष्ठा input_dev *input_dev;
	काष्ठा resource *res;
	पूर्णांक error;

	अगर (!pdev->dev.of_node) अणु
		dev_err(&pdev->dev, "no DT data present\n");
		वापस -EINVAL;
	पूर्ण

	keypad_data = devm_kzalloc(&pdev->dev, माप(*keypad_data),
				   GFP_KERNEL);
	अगर (!keypad_data)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev) अणु
		dev_err(&pdev->dev, "failed to allocate the input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_dev->name = pdev->name;
	input_dev->phys = "keyscan-keys/input0";
	input_dev->dev.parent = &pdev->dev;
	input_dev->खोलो = keyscan_खोलो;
	input_dev->बंद = keyscan_बंद;

	input_dev->id.bustype = BUS_HOST;

	keypad_data->input_dev = input_dev;

	error = keypad_matrix_key_parse_dt(keypad_data);
	अगर (error)
		वापस error;

	error = matrix_keypad_build_keymap(शून्य, शून्य,
					   keypad_data->n_rows,
					   keypad_data->n_cols,
					   शून्य, input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to build keymap\n");
		वापस error;
	पूर्ण

	input_set_drvdata(input_dev, keypad_data);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	keypad_data->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(keypad_data->base))
		वापस PTR_ERR(keypad_data->base);

	keypad_data->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(keypad_data->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(keypad_data->clk);
	पूर्ण

	error = clk_enable(keypad_data->clk);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to enable clock\n");
		वापस error;
	पूर्ण

	keyscan_stop(keypad_data);

	keypad_data->irq = platक्रमm_get_irq(pdev, 0);
	अगर (keypad_data->irq < 0)
		वापस -EINVAL;

	error = devm_request_irq(&pdev->dev, keypad_data->irq, keyscan_isr, 0,
				 pdev->name, keypad_data);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to request IRQ\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, keypad_data);

	device_set_wakeup_capable(&pdev->dev, 1);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक keyscan_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा st_keyscan *keypad = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input = keypad->input_dev;

	mutex_lock(&input->mutex);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(keypad->irq);
	अन्यथा अगर (input_device_enabled(input))
		keyscan_stop(keypad);

	mutex_unlock(&input->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक keyscan_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा st_keyscan *keypad = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input = keypad->input_dev;
	पूर्णांक retval = 0;

	mutex_lock(&input->mutex);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(keypad->irq);
	अन्यथा अगर (input_device_enabled(input))
		retval = keyscan_start(keypad);

	mutex_unlock(&input->mutex);
	वापस retval;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(keyscan_dev_pm_ops, keyscan_suspend, keyscan_resume);

अटल स्थिर काष्ठा of_device_id keyscan_of_match[] = अणु
	अणु .compatible = "st,sti-keyscan" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, keyscan_of_match);

अटल काष्ठा platक्रमm_driver keyscan_device_driver = अणु
	.probe		= keyscan_probe,
	.driver		= अणु
		.name	= "st-keyscan",
		.pm	= &keyscan_dev_pm_ops,
		.of_match_table = of_match_ptr(keyscan_of_match),
	पूर्ण
पूर्ण;

module_platक्रमm_driver(keyscan_device_driver);

MODULE_AUTHOR("Stuart Menefy <stuart.menefy@st.com>");
MODULE_DESCRIPTION("STMicroelectronics keyscan device driver");
MODULE_LICENSE("GPL");
