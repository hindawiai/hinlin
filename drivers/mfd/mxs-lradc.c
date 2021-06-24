<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale MXS Low Resolution Analog-to-Digital Converter driver
 *
 * Copyright (c) 2012 DENX Software Engineering, GmbH.
 * Copyright (c) 2017 Ksenija Stanojevic <ksenija.stanojevic@gmail.com>
 *
 * Authors:
 *  Marek Vasut <marex@denx.de>
 *  Ksenija Stanojevic <ksenija.stanojevic@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/mxs-lradc.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा ADC_CELL		0
#घोषणा TSC_CELL		1
#घोषणा RES_MEM			0

क्रमागत mx23_lradc_irqs अणु
	MX23_LRADC_TS_IRQ = 0,
	MX23_LRADC_CH0_IRQ,
	MX23_LRADC_CH1_IRQ,
	MX23_LRADC_CH2_IRQ,
	MX23_LRADC_CH3_IRQ,
	MX23_LRADC_CH4_IRQ,
	MX23_LRADC_CH5_IRQ,
	MX23_LRADC_CH6_IRQ,
	MX23_LRADC_CH7_IRQ,
पूर्ण;

क्रमागत mx28_lradc_irqs अणु
	MX28_LRADC_TS_IRQ = 0,
	MX28_LRADC_TRESH0_IRQ,
	MX28_LRADC_TRESH1_IRQ,
	MX28_LRADC_CH0_IRQ,
	MX28_LRADC_CH1_IRQ,
	MX28_LRADC_CH2_IRQ,
	MX28_LRADC_CH3_IRQ,
	MX28_LRADC_CH4_IRQ,
	MX28_LRADC_CH5_IRQ,
	MX28_LRADC_CH6_IRQ,
	MX28_LRADC_CH7_IRQ,
	MX28_LRADC_BUTTON0_IRQ,
	MX28_LRADC_BUTTON1_IRQ,
पूर्ण;

अटल काष्ठा resource mx23_adc_resources[] = अणु
	DEFINE_RES_MEM(0x0, 0x0),
	DEFINE_RES_IRQ_NAMED(MX23_LRADC_CH0_IRQ, "mxs-lradc-channel0"),
	DEFINE_RES_IRQ_NAMED(MX23_LRADC_CH1_IRQ, "mxs-lradc-channel1"),
	DEFINE_RES_IRQ_NAMED(MX23_LRADC_CH2_IRQ, "mxs-lradc-channel2"),
	DEFINE_RES_IRQ_NAMED(MX23_LRADC_CH3_IRQ, "mxs-lradc-channel3"),
	DEFINE_RES_IRQ_NAMED(MX23_LRADC_CH4_IRQ, "mxs-lradc-channel4"),
	DEFINE_RES_IRQ_NAMED(MX23_LRADC_CH5_IRQ, "mxs-lradc-channel5"),
पूर्ण;

अटल काष्ठा resource mx23_touchscreen_resources[] = अणु
	DEFINE_RES_MEM(0x0, 0x0),
	DEFINE_RES_IRQ_NAMED(MX23_LRADC_TS_IRQ, "mxs-lradc-touchscreen"),
	DEFINE_RES_IRQ_NAMED(MX23_LRADC_CH6_IRQ, "mxs-lradc-channel6"),
	DEFINE_RES_IRQ_NAMED(MX23_LRADC_CH7_IRQ, "mxs-lradc-channel7"),
पूर्ण;

अटल काष्ठा resource mx28_adc_resources[] = अणु
	DEFINE_RES_MEM(0x0, 0x0),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_TRESH0_IRQ, "mxs-lradc-thresh0"),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_TRESH1_IRQ, "mxs-lradc-thresh1"),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_CH0_IRQ, "mxs-lradc-channel0"),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_CH1_IRQ, "mxs-lradc-channel1"),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_CH2_IRQ, "mxs-lradc-channel2"),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_CH3_IRQ, "mxs-lradc-channel3"),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_CH4_IRQ, "mxs-lradc-channel4"),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_CH5_IRQ, "mxs-lradc-channel5"),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_BUTTON0_IRQ, "mxs-lradc-button0"),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_BUTTON1_IRQ, "mxs-lradc-button1"),
पूर्ण;

अटल काष्ठा resource mx28_touchscreen_resources[] = अणु
	DEFINE_RES_MEM(0x0, 0x0),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_TS_IRQ, "mxs-lradc-touchscreen"),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_CH6_IRQ, "mxs-lradc-channel6"),
	DEFINE_RES_IRQ_NAMED(MX28_LRADC_CH7_IRQ, "mxs-lradc-channel7"),
पूर्ण;

अटल काष्ठा mfd_cell mx23_cells[] = अणु
	अणु
		.name = "mxs-lradc-adc",
		.resources = mx23_adc_resources,
		.num_resources = ARRAY_SIZE(mx23_adc_resources),
	पूर्ण,
	अणु
		.name = "mxs-lradc-ts",
		.resources = mx23_touchscreen_resources,
		.num_resources = ARRAY_SIZE(mx23_touchscreen_resources),
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell mx28_cells[] = अणु
	अणु
		.name = "mxs-lradc-adc",
		.resources = mx28_adc_resources,
		.num_resources = ARRAY_SIZE(mx28_adc_resources),
	पूर्ण,
	अणु
		.name = "mxs-lradc-ts",
		.resources = mx28_touchscreen_resources,
		.num_resources = ARRAY_SIZE(mx28_touchscreen_resources),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id mxs_lradc_dt_ids[] = अणु
	अणु .compatible = "fsl,imx23-lradc", .data = (व्योम *)IMX23_LRADC, पूर्ण,
	अणु .compatible = "fsl,imx28-lradc", .data = (व्योम *)IMX28_LRADC, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_lradc_dt_ids);

अटल पूर्णांक mxs_lradc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा mxs_lradc *lradc;
	काष्ठा mfd_cell *cells = शून्य;
	काष्ठा resource *res;
	पूर्णांक ret = 0;
	u32 ts_wires = 0;

	lradc = devm_kzalloc(&pdev->dev, माप(*lradc), GFP_KERNEL);
	अगर (!lradc)
		वापस -ENOMEM;

	of_id = of_match_device(mxs_lradc_dt_ids, &pdev->dev);
	अगर (!of_id)
		वापस -EINVAL;

	lradc->soc = (क्रमागत mxs_lradc_id)of_id->data;

	lradc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(lradc->clk)) अणु
		dev_err(dev, "Failed to get the delay unit clock\n");
		वापस PTR_ERR(lradc->clk);
	पूर्ण

	ret = clk_prepare_enable(lradc->clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable the delay unit clock\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "fsl,lradc-touchscreen-wires",
					 &ts_wires);

	अगर (!ret) अणु
		lradc->buffer_vchans = BUFFER_VCHANS_LIMITED;

		चयन (ts_wires) अणु
		हाल 4:
			lradc->touchscreen_wire = MXS_LRADC_TOUCHSCREEN_4WIRE;
			अवरोध;
		हाल 5:
			अगर (lradc->soc == IMX28_LRADC) अणु
				lradc->touchscreen_wire =
					MXS_LRADC_TOUCHSCREEN_5WIRE;
				अवरोध;
			पूर्ण
			fallthrough;	/* to an error message क्रम i.MX23 */
		शेष:
			dev_err(&pdev->dev,
				"Unsupported number of touchscreen wires (%d)\n"
				, ts_wires);
			ret = -EINVAL;
			जाओ err_clk;
		पूर्ण
	पूर्ण अन्यथा अणु
		lradc->buffer_vchans = BUFFER_VCHANS_ALL;
	पूर्ण

	platक्रमm_set_drvdata(pdev, lradc);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -ENOMEM;
		जाओ err_clk;
	पूर्ण

	चयन (lradc->soc) अणु
	हाल IMX23_LRADC:
		mx23_adc_resources[RES_MEM] = *res;
		mx23_touchscreen_resources[RES_MEM] = *res;
		cells = mx23_cells;
		अवरोध;
	हाल IMX28_LRADC:
		mx28_adc_resources[RES_MEM] = *res;
		mx28_touchscreen_resources[RES_MEM] = *res;
		cells = mx28_cells;
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported SoC\n");
		ret = -ENODEV;
		जाओ err_clk;
	पूर्ण

	ret = devm_mfd_add_devices(&pdev->dev, PLATFORM_DEVID_NONE,
				   &cells[ADC_CELL], 1, शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add the ADC subdevice\n");
		जाओ err_clk;
	पूर्ण

	अगर (!lradc->touchscreen_wire)
		वापस 0;

	ret = devm_mfd_add_devices(&pdev->dev, PLATFORM_DEVID_NONE,
				   &cells[TSC_CELL], 1, शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to add the touchscreen subdevice\n");
		जाओ err_clk;
	पूर्ण

	वापस 0;

err_clk:
	clk_disable_unprepare(lradc->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक mxs_lradc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxs_lradc *lradc = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(lradc->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mxs_lradc_driver = अणु
	.driver = अणु
		.name = "mxs-lradc",
		.of_match_table = mxs_lradc_dt_ids,
	पूर्ण,
	.probe = mxs_lradc_probe,
	.हटाओ = mxs_lradc_हटाओ,
पूर्ण;
module_platक्रमm_driver(mxs_lradc_driver);

MODULE_AUTHOR("Ksenija Stanojevic <ksenija.stanojevic@gmail.com>");
MODULE_DESCRIPTION("Freescale i.MX23/i.MX28 LRADC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mxs-lradc");
