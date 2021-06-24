<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI AEMIF driver
 *
 * Copyright (C) 2010 - 2013 Texas Instruments Incorporated. http://www.ti.com/
 *
 * Authors:
 * Murali Karicheri <m-karicheri2@ti.com>
 * Ivan Khoronzhuk <ivan.khoronzhuk@ti.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/ti-aemअगर.h>

#घोषणा TA_SHIFT	2
#घोषणा RHOLD_SHIFT	4
#घोषणा RSTROBE_SHIFT	7
#घोषणा RSETUP_SHIFT	13
#घोषणा WHOLD_SHIFT	17
#घोषणा WSTROBE_SHIFT	20
#घोषणा WSETUP_SHIFT	26
#घोषणा EW_SHIFT	30
#घोषणा SSTROBE_SHIFT	31

#घोषणा TA(x)		((x) << TA_SHIFT)
#घोषणा RHOLD(x)	((x) << RHOLD_SHIFT)
#घोषणा RSTROBE(x)	((x) << RSTROBE_SHIFT)
#घोषणा RSETUP(x)	((x) << RSETUP_SHIFT)
#घोषणा WHOLD(x)	((x) << WHOLD_SHIFT)
#घोषणा WSTROBE(x)	((x) << WSTROBE_SHIFT)
#घोषणा WSETUP(x)	((x) << WSETUP_SHIFT)
#घोषणा EW(x)		((x) << EW_SHIFT)
#घोषणा SSTROBE(x)	((x) << SSTROBE_SHIFT)

#घोषणा ASIZE_MAX	0x1
#घोषणा TA_MAX		0x3
#घोषणा RHOLD_MAX	0x7
#घोषणा RSTROBE_MAX	0x3f
#घोषणा RSETUP_MAX	0xf
#घोषणा WHOLD_MAX	0x7
#घोषणा WSTROBE_MAX	0x3f
#घोषणा WSETUP_MAX	0xf
#घोषणा EW_MAX		0x1
#घोषणा SSTROBE_MAX	0x1
#घोषणा NUM_CS		4

#घोषणा TA_VAL(x)	(((x) & TA(TA_MAX)) >> TA_SHIFT)
#घोषणा RHOLD_VAL(x)	(((x) & RHOLD(RHOLD_MAX)) >> RHOLD_SHIFT)
#घोषणा RSTROBE_VAL(x)	(((x) & RSTROBE(RSTROBE_MAX)) >> RSTROBE_SHIFT)
#घोषणा RSETUP_VAL(x)	(((x) & RSETUP(RSETUP_MAX)) >> RSETUP_SHIFT)
#घोषणा WHOLD_VAL(x)	(((x) & WHOLD(WHOLD_MAX)) >> WHOLD_SHIFT)
#घोषणा WSTROBE_VAL(x)	(((x) & WSTROBE(WSTROBE_MAX)) >> WSTROBE_SHIFT)
#घोषणा WSETUP_VAL(x)	(((x) & WSETUP(WSETUP_MAX)) >> WSETUP_SHIFT)
#घोषणा EW_VAL(x)	(((x) & EW(EW_MAX)) >> EW_SHIFT)
#घोषणा SSTROBE_VAL(x)	(((x) & SSTROBE(SSTROBE_MAX)) >> SSTROBE_SHIFT)

#घोषणा NRCSR_OFFSET	0x00
#घोषणा AWCCR_OFFSET	0x04
#घोषणा A1CR_OFFSET	0x10

#घोषणा ACR_ASIZE_MASK	0x3
#घोषणा ACR_EW_MASK	BIT(30)
#घोषणा ACR_SSTROBE_MASK	BIT(31)
#घोषणा ASIZE_16BIT	1

#घोषणा CONFIG_MASK	(TA(TA_MAX) | \
				RHOLD(RHOLD_MAX) | \
				RSTROBE(RSTROBE_MAX) |	\
				RSETUP(RSETUP_MAX) | \
				WHOLD(WHOLD_MAX) | \
				WSTROBE(WSTROBE_MAX) | \
				WSETUP(WSETUP_MAX) | \
				EW(EW_MAX) | SSTROBE(SSTROBE_MAX) | \
				ASIZE_MAX)

/**
 * काष्ठा aemअगर_cs_data: काष्ठाure to hold cs parameters
 * @cs: chip-select number
 * @wstrobe: ग_लिखो strobe width, ns
 * @rstrobe: पढ़ो strobe width, ns
 * @wsetup: ग_लिखो setup width, ns
 * @whold: ग_लिखो hold width, ns
 * @rsetup: पढ़ो setup width, ns
 * @rhold: पढ़ो hold width, ns
 * @ta: minimum turn around समय, ns
 * @enable_ss: enable/disable select strobe mode
 * @enable_ew: enable/disable extended रुको mode
 * @asize: width of the asynchronous device's data bus
 */
काष्ठा aemअगर_cs_data अणु
	u8	cs;
	u16	wstrobe;
	u16	rstrobe;
	u8	wsetup;
	u8	whold;
	u8	rsetup;
	u8	rhold;
	u8	ta;
	u8	enable_ss;
	u8	enable_ew;
	u8	asize;
पूर्ण;

/**
 * काष्ठा aemअगर_device: काष्ठाure to hold device data
 * @base: base address of AEMIF रेजिस्टरs
 * @clk: source घड़ी
 * @clk_rate: घड़ी's rate in kHz
 * @num_cs: number of asचिन्हित chip-selects
 * @cs_offset: start number of cs nodes
 * @cs_data: array of chip-select settings
 */
काष्ठा aemअगर_device अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ clk_rate;
	u8 num_cs;
	पूर्णांक cs_offset;
	काष्ठा aemअगर_cs_data cs_data[NUM_CS];
पूर्ण;

/**
 * aemअगर_calc_rate - calculate timing data.
 * @pdev: platक्रमm device to calculate क्रम
 * @wanted: The cycle समय needed in nanoseconds.
 * @clk: The input घड़ी rate in kHz.
 * @max: The maximum भागider value that can be programmed.
 *
 * On success, वापसs the calculated timing value minus 1 क्रम easy
 * programming पूर्णांकo AEMIF timing रेजिस्टरs, अन्यथा negative त्रुटि_सं.
 */
अटल पूर्णांक aemअगर_calc_rate(काष्ठा platक्रमm_device *pdev, पूर्णांक wanted,
			   अचिन्हित दीर्घ clk, पूर्णांक max)
अणु
	पूर्णांक result;

	result = DIV_ROUND_UP((wanted * clk), NSEC_PER_MSEC) - 1;

	dev_dbg(&pdev->dev, "%s: result %d from %ld, %d\n", __func__, result,
		clk, wanted);

	/* It is generally OK to have a more relaxed timing than requested... */
	अगर (result < 0)
		result = 0;

	/* ... But configuring tighter timings is not an option. */
	अन्यथा अगर (result > max)
		result = -EINVAL;

	वापस result;
पूर्ण

/**
 * aemअगर_config_abus - configure async bus parameters
 * @pdev: platक्रमm device to configure क्रम
 * @csnum: aemअगर chip select number
 *
 * This function programs the given timing values (in real घड़ी) पूर्णांकo the
 * AEMIF रेजिस्टरs taking the AEMIF घड़ी पूर्णांकo account.
 *
 * This function करोes not use any locking जबतक programming the AEMIF
 * because it is expected that there is only one user of a given
 * chip-select.
 *
 * Returns 0 on success, अन्यथा negative त्रुटि_सं.
 */
अटल पूर्णांक aemअगर_config_abus(काष्ठा platक्रमm_device *pdev, पूर्णांक csnum)
अणु
	काष्ठा aemअगर_device *aemअगर = platक्रमm_get_drvdata(pdev);
	काष्ठा aemअगर_cs_data *data = &aemअगर->cs_data[csnum];
	पूर्णांक ta, rhold, rstrobe, rsetup, whold, wstrobe, wsetup;
	अचिन्हित दीर्घ clk_rate = aemअगर->clk_rate;
	अचिन्हित offset;
	u32 set, val;

	offset = A1CR_OFFSET + (data->cs - aemअगर->cs_offset) * 4;

	ta	= aemअगर_calc_rate(pdev, data->ta, clk_rate, TA_MAX);
	rhold	= aemअगर_calc_rate(pdev, data->rhold, clk_rate, RHOLD_MAX);
	rstrobe	= aemअगर_calc_rate(pdev, data->rstrobe, clk_rate, RSTROBE_MAX);
	rsetup	= aemअगर_calc_rate(pdev, data->rsetup, clk_rate, RSETUP_MAX);
	whold	= aemअगर_calc_rate(pdev, data->whold, clk_rate, WHOLD_MAX);
	wstrobe	= aemअगर_calc_rate(pdev, data->wstrobe, clk_rate, WSTROBE_MAX);
	wsetup	= aemअगर_calc_rate(pdev, data->wsetup, clk_rate, WSETUP_MAX);

	अगर (ta < 0 || rhold < 0 || rstrobe < 0 || rsetup < 0 ||
	    whold < 0 || wstrobe < 0 || wsetup < 0) अणु
		dev_err(&pdev->dev, "%s: cannot get suitable timings\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	set = TA(ta) | RHOLD(rhold) | RSTROBE(rstrobe) | RSETUP(rsetup) |
		WHOLD(whold) | WSTROBE(wstrobe) | WSETUP(wsetup);

	set |= (data->asize & ACR_ASIZE_MASK);
	अगर (data->enable_ew)
		set |= ACR_EW_MASK;
	अगर (data->enable_ss)
		set |= ACR_SSTROBE_MASK;

	val = पढ़ोl(aemअगर->base + offset);
	val &= ~CONFIG_MASK;
	val |= set;
	ग_लिखोl(val, aemअगर->base + offset);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक aemअगर_cycles_to_nsec(पूर्णांक val, अचिन्हित दीर्घ clk_rate)
अणु
	वापस ((val + 1) * NSEC_PER_MSEC) / clk_rate;
पूर्ण

/**
 * aemअगर_get_hw_params - function to पढ़ो hw रेजिस्टर values
 * @pdev: platक्रमm device to पढ़ो क्रम
 * @csnum: aemअगर chip select number
 *
 * This function पढ़ोs the शेषs from the रेजिस्टरs and update
 * the timing values. Required क्रम get/set commands and also क्रम
 * the हाल when driver needs to use शेषs in hardware.
 */
अटल व्योम aemअगर_get_hw_params(काष्ठा platक्रमm_device *pdev, पूर्णांक csnum)
अणु
	काष्ठा aemअगर_device *aemअगर = platक्रमm_get_drvdata(pdev);
	काष्ठा aemअगर_cs_data *data = &aemअगर->cs_data[csnum];
	अचिन्हित दीर्घ clk_rate = aemअगर->clk_rate;
	u32 val, offset;

	offset = A1CR_OFFSET + (data->cs - aemअगर->cs_offset) * 4;
	val = पढ़ोl(aemअगर->base + offset);

	data->ta = aemअगर_cycles_to_nsec(TA_VAL(val), clk_rate);
	data->rhold = aemअगर_cycles_to_nsec(RHOLD_VAL(val), clk_rate);
	data->rstrobe = aemअगर_cycles_to_nsec(RSTROBE_VAL(val), clk_rate);
	data->rsetup = aemअगर_cycles_to_nsec(RSETUP_VAL(val), clk_rate);
	data->whold = aemअगर_cycles_to_nsec(WHOLD_VAL(val), clk_rate);
	data->wstrobe = aemअगर_cycles_to_nsec(WSTROBE_VAL(val), clk_rate);
	data->wsetup = aemअगर_cycles_to_nsec(WSETUP_VAL(val), clk_rate);
	data->enable_ew = EW_VAL(val);
	data->enable_ss = SSTROBE_VAL(val);
	data->asize = val & ASIZE_MAX;
पूर्ण

/**
 * of_aemअगर_parse_abus_config - parse CS configuration from DT
 * @pdev: platक्रमm device to parse क्रम
 * @np: device node ptr
 *
 * This function update the emअगर async bus configuration based on the values
 * configured in a cs device binding node.
 */
अटल पूर्णांक of_aemअगर_parse_abus_config(काष्ठा platक्रमm_device *pdev,
				      काष्ठा device_node *np)
अणु
	काष्ठा aemअगर_device *aemअगर = platक्रमm_get_drvdata(pdev);
	काष्ठा aemअगर_cs_data *data;
	u32 cs;
	u32 val;

	अगर (of_property_पढ़ो_u32(np, "ti,cs-chipselect", &cs)) अणु
		dev_dbg(&pdev->dev, "cs property is required");
		वापस -EINVAL;
	पूर्ण

	अगर (cs - aemअगर->cs_offset >= NUM_CS || cs < aemअगर->cs_offset) अणु
		dev_dbg(&pdev->dev, "cs number is incorrect %d", cs);
		वापस -EINVAL;
	पूर्ण

	अगर (aemअगर->num_cs >= NUM_CS) अणु
		dev_dbg(&pdev->dev, "cs count is more than %d", NUM_CS);
		वापस -EINVAL;
	पूर्ण

	data = &aemअगर->cs_data[aemअगर->num_cs];
	data->cs = cs;

	/* पढ़ो the current value in the hw रेजिस्टर */
	aemअगर_get_hw_params(pdev, aemअगर->num_cs++);

	/* override the values from device node */
	अगर (!of_property_पढ़ो_u32(np, "ti,cs-min-turnaround-ns", &val))
		data->ta = val;

	अगर (!of_property_पढ़ो_u32(np, "ti,cs-read-hold-ns", &val))
		data->rhold = val;

	अगर (!of_property_पढ़ो_u32(np, "ti,cs-read-strobe-ns", &val))
		data->rstrobe = val;

	अगर (!of_property_पढ़ो_u32(np, "ti,cs-read-setup-ns", &val))
		data->rsetup = val;

	अगर (!of_property_पढ़ो_u32(np, "ti,cs-write-hold-ns", &val))
		data->whold = val;

	अगर (!of_property_पढ़ो_u32(np, "ti,cs-write-strobe-ns", &val))
		data->wstrobe = val;

	अगर (!of_property_पढ़ो_u32(np, "ti,cs-write-setup-ns", &val))
		data->wsetup = val;

	अगर (!of_property_पढ़ो_u32(np, "ti,cs-bus-width", &val))
		अगर (val == 16)
			data->asize = 1;
	data->enable_ew = of_property_पढ़ो_bool(np, "ti,cs-extended-wait-mode");
	data->enable_ss = of_property_पढ़ो_bool(np, "ti,cs-select-strobe-mode");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aemअगर_of_match[] = अणु
	अणु .compatible = "ti,davinci-aemif", पूर्ण,
	अणु .compatible = "ti,da850-aemif", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aemअगर_of_match);

अटल पूर्णांक aemअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	पूर्णांक ret = -ENODEV;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child_np;
	काष्ठा aemअगर_device *aemअगर;
	काष्ठा aemअगर_platक्रमm_data *pdata;
	काष्ठा of_dev_auxdata *dev_lookup;

	aemअगर = devm_kzalloc(dev, माप(*aemअगर), GFP_KERNEL);
	अगर (!aemअगर)
		वापस -ENOMEM;

	pdata = dev_get_platdata(&pdev->dev);
	dev_lookup = pdata ? pdata->dev_lookup : शून्य;

	platक्रमm_set_drvdata(pdev, aemअगर);

	aemअगर->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(aemअगर->clk)) अणु
		dev_err(dev, "cannot get clock 'aemif'\n");
		वापस PTR_ERR(aemअगर->clk);
	पूर्ण

	ret = clk_prepare_enable(aemअगर->clk);
	अगर (ret)
		वापस ret;

	aemअगर->clk_rate = clk_get_rate(aemअगर->clk) / MSEC_PER_SEC;

	अगर (np && of_device_is_compatible(np, "ti,da850-aemif"))
		aemअगर->cs_offset = 2;
	अन्यथा अगर (pdata)
		aemअगर->cs_offset = pdata->cs_offset;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	aemअगर->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(aemअगर->base)) अणु
		ret = PTR_ERR(aemअगर->base);
		जाओ error;
	पूर्ण

	अगर (np) अणु
		/*
		 * For every controller device node, there is a cs device node
		 * that describe the bus configuration parameters. This
		 * functions iterate over these nodes and update the cs data
		 * array.
		 */
		क्रम_each_available_child_of_node(np, child_np) अणु
			ret = of_aemअगर_parse_abus_config(pdev, child_np);
			अगर (ret < 0) अणु
				of_node_put(child_np);
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (pdata && pdata->num_abus_data > 0) अणु
		क्रम (i = 0; i < pdata->num_abus_data; i++, aemअगर->num_cs++) अणु
			aemअगर->cs_data[i].cs = pdata->abus_data[i].cs;
			aemअगर_get_hw_params(pdev, i);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < aemअगर->num_cs; i++) अणु
		ret = aemअगर_config_abus(pdev, i);
		अगर (ret < 0) अणु
			dev_err(dev, "Error configuring chip select %d\n",
				aemअगर->cs_data[i].cs);
			जाओ error;
		पूर्ण
	पूर्ण

	/*
	 * Create a child devices explicitly from here to guarantee that the
	 * child will be probed after the AEMIF timing parameters are set.
	 */
	अगर (np) अणु
		क्रम_each_available_child_of_node(np, child_np) अणु
			ret = of_platक्रमm_populate(child_np, शून्य,
						   dev_lookup, dev);
			अगर (ret < 0) अणु
				of_node_put(child_np);
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (pdata) अणु
		क्रम (i = 0; i < pdata->num_sub_devices; i++) अणु
			pdata->sub_devices[i].dev.parent = dev;
			ret = platक्रमm_device_रेजिस्टर(&pdata->sub_devices[i]);
			अगर (ret) अणु
				dev_warn(dev, "Error register sub device %s\n",
					 pdata->sub_devices[i].name);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
error:
	clk_disable_unprepare(aemअगर->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक aemअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aemअगर_device *aemअगर = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(aemअगर->clk);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aemअगर_driver = अणु
	.probe = aemअगर_probe,
	.हटाओ = aemअगर_हटाओ,
	.driver = अणु
		.name = "ti-aemif",
		.of_match_table = of_match_ptr(aemअगर_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(aemअगर_driver);

MODULE_AUTHOR("Murali Karicheri <m-karicheri2@ti.com>");
MODULE_AUTHOR("Ivan Khoronzhuk <ivan.khoronzhuk@ti.com>");
MODULE_DESCRIPTION("Texas Instruments AEMIF driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" KBUILD_MODNAME);
