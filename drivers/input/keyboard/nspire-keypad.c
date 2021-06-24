<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2013 Daniel Tang <tangrs@tangrs.id.au>
 */

#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#घोषणा KEYPAD_SCAN_MODE	0x00
#घोषणा KEYPAD_CNTL		0x04
#घोषणा KEYPAD_INT		0x08
#घोषणा KEYPAD_INTMSK		0x0C

#घोषणा KEYPAD_DATA		0x10
#घोषणा KEYPAD_GPIO		0x30

#घोषणा KEYPAD_UNKNOWN_INT	0x40
#घोषणा KEYPAD_UNKNOWN_INT_STS	0x44

#घोषणा KEYPAD_BITMASK_COLS	11
#घोषणा KEYPAD_BITMASK_ROWS	8

काष्ठा nspire_keypad अणु
	व्योम __iomem *reg_base;
	u32 पूर्णांक_mask;

	काष्ठा input_dev *input;
	काष्ठा clk *clk;

	काष्ठा matrix_keymap_data *keymap;
	पूर्णांक row_shअगरt;

	/* Maximum delay estimated assuming 33MHz APB */
	u32 scan_पूर्णांकerval;	/* In microseconds (~2000us max) */
	u32 row_delay;		/* In microseconds (~500us max) */

	u16 state[KEYPAD_BITMASK_ROWS];

	bool active_low;
पूर्ण;

अटल irqवापस_t nspire_keypad_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा nspire_keypad *keypad = dev_id;
	काष्ठा input_dev *input = keypad->input;
	अचिन्हित लघु *keymap = input->keycode;
	अचिन्हित पूर्णांक code;
	पूर्णांक row, col;
	u32 पूर्णांक_sts;
	u16 state[8];
	u16 bits, changed;

	पूर्णांक_sts = पढ़ोl(keypad->reg_base + KEYPAD_INT) & keypad->पूर्णांक_mask;
	अगर (!पूर्णांक_sts)
		वापस IRQ_NONE;

	स_नकल_fromio(state, keypad->reg_base + KEYPAD_DATA, माप(state));

	क्रम (row = 0; row < KEYPAD_BITMASK_ROWS; row++) अणु
		bits = state[row];
		अगर (keypad->active_low)
			bits = ~bits;

		changed = bits ^ keypad->state[row];
		अगर (!changed)
			जारी;

		keypad->state[row] = bits;

		क्रम (col = 0; col < KEYPAD_BITMASK_COLS; col++) अणु
			अगर (!(changed & (1U << col)))
				जारी;

			code = MATRIX_SCAN_CODE(row, col, keypad->row_shअगरt);
			input_event(input, EV_MSC, MSC_SCAN, code);
			input_report_key(input, keymap[code],
					 bits & (1U << col));
		पूर्ण
	पूर्ण

	input_sync(input);

	ग_लिखोl(0x3, keypad->reg_base + KEYPAD_INT);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक nspire_keypad_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा nspire_keypad *keypad = input_get_drvdata(input);
	अचिन्हित दीर्घ val = 0, cycles_per_us, delay_cycles, row_delay_cycles;
	पूर्णांक error;

	error = clk_prepare_enable(keypad->clk);
	अगर (error)
		वापस error;

	cycles_per_us = (clk_get_rate(keypad->clk) / 1000000);
	अगर (cycles_per_us == 0)
		cycles_per_us = 1;

	delay_cycles = cycles_per_us * keypad->scan_पूर्णांकerval;
	WARN_ON(delay_cycles >= (1 << 16)); /* Overflow */
	delay_cycles &= 0xffff;

	row_delay_cycles = cycles_per_us * keypad->row_delay;
	WARN_ON(row_delay_cycles >= (1 << 14)); /* Overflow */
	row_delay_cycles &= 0x3fff;

	val |= 3 << 0; /* Set scan mode to 3 (continuous scan) */
	val |= row_delay_cycles << 2; /* Delay between scanning each row */
	val |= delay_cycles << 16; /* Delay between scans */
	ग_लिखोl(val, keypad->reg_base + KEYPAD_SCAN_MODE);

	val = (KEYPAD_BITMASK_ROWS & 0xff) | (KEYPAD_BITMASK_COLS & 0xff)<<8;
	ग_लिखोl(val, keypad->reg_base + KEYPAD_CNTL);

	/* Enable पूर्णांकerrupts */
	keypad->पूर्णांक_mask = 1 << 1;
	ग_लिखोl(keypad->पूर्णांक_mask, keypad->reg_base + KEYPAD_INTMSK);

	वापस 0;
पूर्ण

अटल व्योम nspire_keypad_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा nspire_keypad *keypad = input_get_drvdata(input);

	/* Disable पूर्णांकerrupts */
	ग_लिखोl(0, keypad->reg_base + KEYPAD_INTMSK);
	/* Acknowledge existing पूर्णांकerrupts */
	ग_लिखोl(~0, keypad->reg_base + KEYPAD_INT);

	clk_disable_unprepare(keypad->clk);
पूर्ण

अटल पूर्णांक nspire_keypad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा device_node *of_node = pdev->dev.of_node;
	काष्ठा nspire_keypad *keypad;
	काष्ठा input_dev *input;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक error;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	keypad = devm_kzalloc(&pdev->dev, माप(काष्ठा nspire_keypad),
			      GFP_KERNEL);
	अगर (!keypad) अणु
		dev_err(&pdev->dev, "failed to allocate keypad memory\n");
		वापस -ENOMEM;
	पूर्ण

	keypad->row_shअगरt = get_count_order(KEYPAD_BITMASK_COLS);

	error = of_property_पढ़ो_u32(of_node, "scan-interval",
				     &keypad->scan_पूर्णांकerval);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to get scan-interval\n");
		वापस error;
	पूर्ण

	error = of_property_पढ़ो_u32(of_node, "row-delay",
				     &keypad->row_delay);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to get row-delay\n");
		वापस error;
	पूर्ण

	keypad->active_low = of_property_पढ़ो_bool(of_node, "active-low");

	keypad->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(keypad->clk)) अणु
		dev_err(&pdev->dev, "unable to get clock\n");
		वापस PTR_ERR(keypad->clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	keypad->reg_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(keypad->reg_base))
		वापस PTR_ERR(keypad->reg_base);

	keypad->input = input = devm_input_allocate_device(&pdev->dev);
	अगर (!input) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	error = clk_prepare_enable(keypad->clk);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to enable clock\n");
		वापस error;
	पूर्ण

	/* Disable पूर्णांकerrupts */
	ग_लिखोl(0, keypad->reg_base + KEYPAD_INTMSK);
	/* Acknowledge existing पूर्णांकerrupts */
	ग_लिखोl(~0, keypad->reg_base + KEYPAD_INT);

	/* Disable GPIO पूर्णांकerrupts to prevent hanging on touchpad */
	/* Possibly used to detect touchpad events */
	ग_लिखोl(0, keypad->reg_base + KEYPAD_UNKNOWN_INT);
	/* Acknowledge existing GPIO पूर्णांकerrupts */
	ग_लिखोl(~0, keypad->reg_base + KEYPAD_UNKNOWN_INT_STS);

	clk_disable_unprepare(keypad->clk);

	input_set_drvdata(input, keypad);

	input->id.bustype = BUS_HOST;
	input->name = "nspire-keypad";
	input->खोलो = nspire_keypad_खोलो;
	input->बंद = nspire_keypad_बंद;

	__set_bit(EV_KEY, input->evbit);
	__set_bit(EV_REP, input->evbit);
	input_set_capability(input, EV_MSC, MSC_SCAN);

	error = matrix_keypad_build_keymap(शून्य, शून्य,
					   KEYPAD_BITMASK_ROWS,
					   KEYPAD_BITMASK_COLS,
					   शून्य, input);
	अगर (error) अणु
		dev_err(&pdev->dev, "building keymap failed\n");
		वापस error;
	पूर्ण

	error = devm_request_irq(&pdev->dev, irq, nspire_keypad_irq, 0,
				 "nspire_keypad", keypad);
	अगर (error) अणु
		dev_err(&pdev->dev, "allocate irq %d failed\n", irq);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"unable to register input device: %d\n", error);
		वापस error;
	पूर्ण

	dev_dbg(&pdev->dev,
		"TI-NSPIRE keypad at %pR (scan_interval=%uus, row_delay=%uus%s)\n",
		res, keypad->row_delay, keypad->scan_पूर्णांकerval,
		keypad->active_low ? ", active_low" : "");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id nspire_keypad_dt_match[] = अणु
	अणु .compatible = "ti,nspire-keypad" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, nspire_keypad_dt_match);

अटल काष्ठा platक्रमm_driver nspire_keypad_driver = अणु
	.driver = अणु
		.name = "nspire-keypad",
		.of_match_table = nspire_keypad_dt_match,
	पूर्ण,
	.probe = nspire_keypad_probe,
पूर्ण;

module_platक्रमm_driver(nspire_keypad_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TI-NSPIRE Keypad Driver");
