<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Allwinner sun4i low res adc attached tablet keys driver
 *
 * Copyright (C) 2014 Hans de Goede <hdegoede@redhat.com>
 */

/*
 * Allwinnner sunxi SoCs have a lradc which is specअगरically deचिन्हित to have
 * various (tablet) keys (ie home, back, search, etc). attached to it using
 * a resistor network. This driver is क्रम the keys on such boards.
 *
 * There are 2 channels, currently this driver only supports channel 0 since
 * there are no boards known to use channel 1.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#घोषणा LRADC_CTRL		0x00
#घोषणा LRADC_INTC		0x04
#घोषणा LRADC_INTS		0x08
#घोषणा LRADC_DATA0		0x0c
#घोषणा LRADC_DATA1		0x10

/* LRADC_CTRL bits */
#घोषणा FIRST_CONVERT_DLY(x)	((x) << 24) /* 8 bits */
#घोषणा CHAN_SELECT(x)		((x) << 22) /* 2 bits */
#घोषणा CONTINUE_TIME_SEL(x)	((x) << 16) /* 4 bits */
#घोषणा KEY_MODE_SEL(x)		((x) << 12) /* 2 bits */
#घोषणा LEVELA_B_CNT(x)		((x) << 8)  /* 4 bits */
#घोषणा HOLD_KEY_EN(x)		((x) << 7)
#घोषणा HOLD_EN(x)		((x) << 6)
#घोषणा LEVELB_VOL(x)		((x) << 4)  /* 2 bits */
#घोषणा SAMPLE_RATE(x)		((x) << 2)  /* 2 bits */
#घोषणा ENABLE(x)		((x) << 0)

/* LRADC_INTC and LRADC_INTS bits */
#घोषणा CHAN1_KEYUP_IRQ		BIT(12)
#घोषणा CHAN1_ALRDY_HOLD_IRQ	BIT(11)
#घोषणा CHAN1_HOLD_IRQ		BIT(10)
#घोषणा	CHAN1_KEYDOWN_IRQ	BIT(9)
#घोषणा CHAN1_DATA_IRQ		BIT(8)
#घोषणा CHAN0_KEYUP_IRQ		BIT(4)
#घोषणा CHAN0_ALRDY_HOLD_IRQ	BIT(3)
#घोषणा CHAN0_HOLD_IRQ		BIT(2)
#घोषणा	CHAN0_KEYDOWN_IRQ	BIT(1)
#घोषणा CHAN0_DATA_IRQ		BIT(0)

/* काष्ठा lradc_variant - Describe sun4i-a10-lradc-keys hardware variant
 * @भागisor_numerator:		The numerator of lradc Vref पूर्णांकernally भागisor
 * @भागisor_denominator:	The denominator of lradc Vref पूर्णांकernally भागisor
 */
काष्ठा lradc_variant अणु
	u8 भागisor_numerator;
	u8 भागisor_denominator;
पूर्ण;

अटल स्थिर काष्ठा lradc_variant lradc_variant_a10 = अणु
	.भागisor_numerator = 2,
	.भागisor_denominator = 3
पूर्ण;

अटल स्थिर काष्ठा lradc_variant r_lradc_variant_a83t = अणु
	.भागisor_numerator = 3,
	.भागisor_denominator = 4
पूर्ण;

काष्ठा sun4i_lradc_keymap अणु
	u32 voltage;
	u32 keycode;
पूर्ण;

काष्ठा sun4i_lradc_data अणु
	काष्ठा device *dev;
	काष्ठा input_dev *input;
	व्योम __iomem *base;
	काष्ठा regulator *vref_supply;
	काष्ठा sun4i_lradc_keymap *chan0_map;
	स्थिर काष्ठा lradc_variant *variant;
	u32 chan0_map_count;
	u32 chan0_keycode;
	u32 vref;
पूर्ण;

अटल irqवापस_t sun4i_lradc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun4i_lradc_data *lradc = dev_id;
	u32 i, पूर्णांकs, val, voltage, dअगरf, keycode = 0, बंदst = 0xffffffff;

	पूर्णांकs  = पढ़ोl(lradc->base + LRADC_INTS);

	/*
	 * lradc supports only one keypress at a समय, release करोes not give
	 * any info as to which key was released, so we cache the keycode.
	 */

	अगर (पूर्णांकs & CHAN0_KEYUP_IRQ) अणु
		input_report_key(lradc->input, lradc->chan0_keycode, 0);
		lradc->chan0_keycode = 0;
	पूर्ण

	अगर ((पूर्णांकs & CHAN0_KEYDOWN_IRQ) && lradc->chan0_keycode == 0) अणु
		val = पढ़ोl(lradc->base + LRADC_DATA0) & 0x3f;
		voltage = val * lradc->vref / 63;

		क्रम (i = 0; i < lradc->chan0_map_count; i++) अणु
			dअगरf = असल(lradc->chan0_map[i].voltage - voltage);
			अगर (dअगरf < बंदst) अणु
				बंदst = dअगरf;
				keycode = lradc->chan0_map[i].keycode;
			पूर्ण
		पूर्ण

		lradc->chan0_keycode = keycode;
		input_report_key(lradc->input, lradc->chan0_keycode, 1);
	पूर्ण

	input_sync(lradc->input);

	ग_लिखोl(पूर्णांकs, lradc->base + LRADC_INTS);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sun4i_lradc_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा sun4i_lradc_data *lradc = input_get_drvdata(dev);
	पूर्णांक error;

	error = regulator_enable(lradc->vref_supply);
	अगर (error)
		वापस error;

	lradc->vref = regulator_get_voltage(lradc->vref_supply) *
		      lradc->variant->भागisor_numerator /
		      lradc->variant->भागisor_denominator;
	/*
	 * Set sample समय to 4 ms / 250 Hz. Wait 2 * 4 ms क्रम key to
	 * stabilize on press, रुको (1 + 1) * 4 ms क्रम key release
	 */
	ग_लिखोl(FIRST_CONVERT_DLY(2) | LEVELA_B_CNT(1) | HOLD_EN(1) |
		SAMPLE_RATE(0) | ENABLE(1), lradc->base + LRADC_CTRL);

	ग_लिखोl(CHAN0_KEYUP_IRQ | CHAN0_KEYDOWN_IRQ, lradc->base + LRADC_INTC);

	वापस 0;
पूर्ण

अटल व्योम sun4i_lradc_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा sun4i_lradc_data *lradc = input_get_drvdata(dev);

	/* Disable lradc, leave other settings unchanged */
	ग_लिखोl(FIRST_CONVERT_DLY(2) | LEVELA_B_CNT(1) | HOLD_EN(1) |
		SAMPLE_RATE(2), lradc->base + LRADC_CTRL);
	ग_लिखोl(0, lradc->base + LRADC_INTC);

	regulator_disable(lradc->vref_supply);
पूर्ण

अटल पूर्णांक sun4i_lradc_load_dt_keymap(काष्ठा device *dev,
				      काष्ठा sun4i_lradc_data *lradc)
अणु
	काष्ठा device_node *np, *pp;
	पूर्णांक i;
	पूर्णांक error;

	np = dev->of_node;
	अगर (!np)
		वापस -EINVAL;

	lradc->chan0_map_count = of_get_child_count(np);
	अगर (lradc->chan0_map_count == 0) अणु
		dev_err(dev, "keymap is missing in device tree\n");
		वापस -EINVAL;
	पूर्ण

	lradc->chan0_map = devm_kदो_स्मृति_array(dev, lradc->chan0_map_count,
					      माप(काष्ठा sun4i_lradc_keymap),
					      GFP_KERNEL);
	अगर (!lradc->chan0_map)
		वापस -ENOMEM;

	i = 0;
	क्रम_each_child_of_node(np, pp) अणु
		काष्ठा sun4i_lradc_keymap *map = &lradc->chan0_map[i];
		u32 channel;

		error = of_property_पढ़ो_u32(pp, "channel", &channel);
		अगर (error || channel != 0) अणु
			dev_err(dev, "%pOFn: Inval channel prop\n", pp);
			of_node_put(pp);
			वापस -EINVAL;
		पूर्ण

		error = of_property_पढ़ो_u32(pp, "voltage", &map->voltage);
		अगर (error) अणु
			dev_err(dev, "%pOFn: Inval voltage prop\n", pp);
			of_node_put(pp);
			वापस -EINVAL;
		पूर्ण

		error = of_property_पढ़ो_u32(pp, "linux,code", &map->keycode);
		अगर (error) अणु
			dev_err(dev, "%pOFn: Inval linux,code prop\n", pp);
			of_node_put(pp);
			वापस -EINVAL;
		पूर्ण

		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_lradc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_lradc_data *lradc;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i;
	पूर्णांक error;

	lradc = devm_kzalloc(dev, माप(काष्ठा sun4i_lradc_data), GFP_KERNEL);
	अगर (!lradc)
		वापस -ENOMEM;

	error = sun4i_lradc_load_dt_keymap(dev, lradc);
	अगर (error)
		वापस error;

	lradc->variant = of_device_get_match_data(&pdev->dev);
	अगर (!lradc->variant) अणु
		dev_err(&pdev->dev, "Missing sun4i-a10-lradc-keys variant\n");
		वापस -EINVAL;
	पूर्ण

	lradc->vref_supply = devm_regulator_get(dev, "vref");
	अगर (IS_ERR(lradc->vref_supply))
		वापस PTR_ERR(lradc->vref_supply);

	lradc->dev = dev;
	lradc->input = devm_input_allocate_device(dev);
	अगर (!lradc->input)
		वापस -ENOMEM;

	lradc->input->name = pdev->name;
	lradc->input->phys = "sun4i_lradc/input0";
	lradc->input->खोलो = sun4i_lradc_खोलो;
	lradc->input->बंद = sun4i_lradc_बंद;
	lradc->input->id.bustype = BUS_HOST;
	lradc->input->id.venकरोr = 0x0001;
	lradc->input->id.product = 0x0001;
	lradc->input->id.version = 0x0100;

	__set_bit(EV_KEY, lradc->input->evbit);
	क्रम (i = 0; i < lradc->chan0_map_count; i++)
		__set_bit(lradc->chan0_map[i].keycode, lradc->input->keybit);

	input_set_drvdata(lradc->input, lradc);

	lradc->base = devm_ioremap_resource(dev,
			      platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0));
	अगर (IS_ERR(lradc->base))
		वापस PTR_ERR(lradc->base);

	error = devm_request_irq(dev, platक्रमm_get_irq(pdev, 0),
				 sun4i_lradc_irq, 0,
				 "sun4i-a10-lradc-keys", lradc);
	अगर (error)
		वापस error;

	error = input_रेजिस्टर_device(lradc->input);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_lradc_of_match[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-lradc-keys",
		.data = &lradc_variant_a10 पूर्ण,
	अणु .compatible = "allwinner,sun8i-a83t-r-lradc",
		.data = &r_lradc_variant_a83t पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_lradc_of_match);

अटल काष्ठा platक्रमm_driver sun4i_lradc_driver = अणु
	.driver = अणु
		.name	= "sun4i-a10-lradc-keys",
		.of_match_table = of_match_ptr(sun4i_lradc_of_match),
	पूर्ण,
	.probe	= sun4i_lradc_probe,
पूर्ण;

module_platक्रमm_driver(sun4i_lradc_driver);

MODULE_DESCRIPTION("Allwinner sun4i low res adc attached tablet keys driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");
