<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020 NXP.
 *
 * Author: Anson Huang <Anson.Huang@nxp.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/thermal.h>

#समावेश "thermal_core.h"

#घोषणा TER			0x0	/* TMU enable */
#घोषणा TPS			0x4
#घोषणा TRITSR			0x20	/* TMU immediate temp */

#घोषणा TER_EN			BIT(31)
#घोषणा TRITSR_TEMP0_VAL_MASK	0xff
#घोषणा TRITSR_TEMP1_VAL_MASK	0xff0000

#घोषणा PROBE_SEL_ALL		GENMASK(31, 30)

#घोषणा probe_status_offset(x)	(30 + x)
#घोषणा SIGN_BIT		BIT(7)
#घोषणा TEMP_VAL_MASK		GENMASK(6, 0)

#घोषणा VER1_TEMP_LOW_LIMIT	10000
#घोषणा VER2_TEMP_LOW_LIMIT	-40000
#घोषणा VER2_TEMP_HIGH_LIMIT	125000

#घोषणा TMU_VER1		0x1
#घोषणा TMU_VER2		0x2

काष्ठा thermal_soc_data अणु
	u32 num_sensors;
	u32 version;
	पूर्णांक (*get_temp)(व्योम *, पूर्णांक *);
पूर्ण;

काष्ठा पंचांगu_sensor अणु
	काष्ठा imx8mm_पंचांगu *priv;
	u32 hw_id;
	काष्ठा thermal_zone_device *tzd;
पूर्ण;

काष्ठा imx8mm_पंचांगu अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	स्थिर काष्ठा thermal_soc_data *socdata;
	काष्ठा पंचांगu_sensor sensors[];
पूर्ण;

अटल पूर्णांक imx8mm_पंचांगu_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा पंचांगu_sensor *sensor = data;
	काष्ठा imx8mm_पंचांगu *पंचांगu = sensor->priv;
	u32 val;

	val = पढ़ोl_relaxed(पंचांगu->base + TRITSR) & TRITSR_TEMP0_VAL_MASK;
	*temp = val * 1000;
	अगर (*temp < VER1_TEMP_LOW_LIMIT)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक imx8mp_पंचांगu_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा पंचांगu_sensor *sensor = data;
	काष्ठा imx8mm_पंचांगu *पंचांगu = sensor->priv;
	अचिन्हित दीर्घ val;
	bool पढ़ोy;

	val = पढ़ोl_relaxed(पंचांगu->base + TRITSR);
	पढ़ोy = test_bit(probe_status_offset(sensor->hw_id), &val);
	अगर (!पढ़ोy)
		वापस -EAGAIN;

	val = sensor->hw_id ? FIELD_GET(TRITSR_TEMP1_VAL_MASK, val) :
	      FIELD_GET(TRITSR_TEMP0_VAL_MASK, val);
	अगर (val & SIGN_BIT) /* negative */
		val = (~(val & TEMP_VAL_MASK) + 1);

	*temp = val * 1000;
	अगर (*temp < VER2_TEMP_LOW_LIMIT || *temp > VER2_TEMP_HIGH_LIMIT)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगu_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा पंचांगu_sensor *sensor = data;
	काष्ठा imx8mm_पंचांगu *पंचांगu = sensor->priv;

	वापस पंचांगu->socdata->get_temp(data, temp);
पूर्ण

अटल काष्ठा thermal_zone_of_device_ops पंचांगu_tz_ops = अणु
	.get_temp = पंचांगu_get_temp,
पूर्ण;

अटल व्योम imx8mm_पंचांगu_enable(काष्ठा imx8mm_पंचांगu *पंचांगu, bool enable)
अणु
	u32 val;

	val = पढ़ोl_relaxed(पंचांगu->base + TER);
	val = enable ? (val | TER_EN) : (val & ~TER_EN);
	ग_लिखोl_relaxed(val, पंचांगu->base + TER);
पूर्ण

अटल व्योम imx8mm_पंचांगu_probe_sel_all(काष्ठा imx8mm_पंचांगu *पंचांगu)
अणु
	u32 val;

	val = पढ़ोl_relaxed(पंचांगu->base + TPS);
	val |= PROBE_SEL_ALL;
	ग_लिखोl_relaxed(val, पंचांगu->base + TPS);
पूर्ण

अटल पूर्णांक imx8mm_पंचांगu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा thermal_soc_data *data;
	काष्ठा imx8mm_पंचांगu *पंचांगu;
	पूर्णांक ret;
	पूर्णांक i;

	data = of_device_get_match_data(&pdev->dev);

	पंचांगu = devm_kzalloc(&pdev->dev, काष्ठा_size(पंचांगu, sensors,
			   data->num_sensors), GFP_KERNEL);
	अगर (!पंचांगu)
		वापस -ENOMEM;

	पंचांगu->socdata = data;

	पंचांगu->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(पंचांगu->base))
		वापस PTR_ERR(पंचांगu->base);

	पंचांगu->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(पंचांगu->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(पंचांगu->clk),
				     "failed to get tmu clock\n");

	ret = clk_prepare_enable(पंचांगu->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable tmu clock: %d\n", ret);
		वापस ret;
	पूर्ण

	/* disable the monitor during initialization */
	imx8mm_पंचांगu_enable(पंचांगu, false);

	क्रम (i = 0; i < data->num_sensors; i++) अणु
		पंचांगu->sensors[i].priv = पंचांगu;
		पंचांगu->sensors[i].tzd =
			devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev, i,
							     &पंचांगu->sensors[i],
							     &पंचांगu_tz_ops);
		अगर (IS_ERR(पंचांगu->sensors[i].tzd)) अणु
			ret = PTR_ERR(पंचांगu->sensors[i].tzd);
			dev_err(&pdev->dev,
				"failed to register thermal zone sensor[%d]: %d\n",
				i, ret);
			जाओ disable_clk;
		पूर्ण
		पंचांगu->sensors[i].hw_id = i;
	पूर्ण

	platक्रमm_set_drvdata(pdev, पंचांगu);

	/* enable all the probes क्रम V2 TMU */
	अगर (पंचांगu->socdata->version == TMU_VER2)
		imx8mm_पंचांगu_probe_sel_all(पंचांगu);

	/* enable the monitor */
	imx8mm_पंचांगu_enable(पंचांगu, true);

	वापस 0;

disable_clk:
	clk_disable_unprepare(पंचांगu->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक imx8mm_पंचांगu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx8mm_पंचांगu *पंचांगu = platक्रमm_get_drvdata(pdev);

	/* disable TMU */
	imx8mm_पंचांगu_enable(पंचांगu, false);

	clk_disable_unprepare(पंचांगu->clk);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा thermal_soc_data imx8mm_पंचांगu_data = अणु
	.num_sensors = 1,
	.version = TMU_VER1,
	.get_temp = imx8mm_पंचांगu_get_temp,
पूर्ण;

अटल काष्ठा thermal_soc_data imx8mp_पंचांगu_data = अणु
	.num_sensors = 2,
	.version = TMU_VER2,
	.get_temp = imx8mp_पंचांगu_get_temp,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx8mm_पंचांगu_table[] = अणु
	अणु .compatible = "fsl,imx8mm-tmu", .data = &imx8mm_पंचांगu_data, पूर्ण,
	अणु .compatible = "fsl,imx8mp-tmu", .data = &imx8mp_पंचांगu_data, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx8mm_पंचांगu_table);

अटल काष्ठा platक्रमm_driver imx8mm_पंचांगu = अणु
	.driver = अणु
		.name	= "i.mx8mm_thermal",
		.of_match_table = imx8mm_पंचांगu_table,
	पूर्ण,
	.probe = imx8mm_पंचांगu_probe,
	.हटाओ = imx8mm_पंचांगu_हटाओ,
पूर्ण;
module_platक्रमm_driver(imx8mm_पंचांगu);

MODULE_AUTHOR("Anson Huang <Anson.Huang@nxp.com>");
MODULE_DESCRIPTION("i.MX8MM Thermal Monitor Unit driver");
MODULE_LICENSE("GPL v2");
