<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom STB AVS TMON thermal sensor driver
 *
 * Copyright (c) 2015-2017 Broadcom
 */

#घोषणा DRV_NAME	"brcmstb_thermal"

#घोषणा pr_fmt(fmt)	DRV_NAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqवापस.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/thermal.h>

#घोषणा AVS_TMON_STATUS			0x00
 #घोषणा AVS_TMON_STATUS_valid_msk	BIT(11)
 #घोषणा AVS_TMON_STATUS_data_msk	GENMASK(10, 1)
 #घोषणा AVS_TMON_STATUS_data_shअगरt	1

#घोषणा AVS_TMON_EN_OVERTEMP_RESET	0x04
 #घोषणा AVS_TMON_EN_OVERTEMP_RESET_msk	BIT(0)

#घोषणा AVS_TMON_RESET_THRESH		0x08
 #घोषणा AVS_TMON_RESET_THRESH_msk	GENMASK(10, 1)
 #घोषणा AVS_TMON_RESET_THRESH_shअगरt	1

#घोषणा AVS_TMON_INT_IDLE_TIME		0x10

#घोषणा AVS_TMON_EN_TEMP_INT_SRCS	0x14
 #घोषणा AVS_TMON_EN_TEMP_INT_SRCS_high	BIT(1)
 #घोषणा AVS_TMON_EN_TEMP_INT_SRCS_low	BIT(0)

#घोषणा AVS_TMON_INT_THRESH		0x18
 #घोषणा AVS_TMON_INT_THRESH_high_msk	GENMASK(26, 17)
 #घोषणा AVS_TMON_INT_THRESH_high_shअगरt	17
 #घोषणा AVS_TMON_INT_THRESH_low_msk	GENMASK(10, 1)
 #घोषणा AVS_TMON_INT_THRESH_low_shअगरt	1

#घोषणा AVS_TMON_TEMP_INT_CODE		0x1c
#घोषणा AVS_TMON_TP_TEST_ENABLE		0x20

/* Default coefficients */
#घोषणा AVS_TMON_TEMP_SLOPE		487
#घोषणा AVS_TMON_TEMP_OFFSET		410040

/* HW related temperature स्थिरants */
#घोषणा AVS_TMON_TEMP_MAX		0x3ff
#घोषणा AVS_TMON_TEMP_MIN		-88161
#घोषणा AVS_TMON_TEMP_MASK		AVS_TMON_TEMP_MAX

क्रमागत avs_पंचांगon_trip_type अणु
	TMON_TRIP_TYPE_LOW = 0,
	TMON_TRIP_TYPE_HIGH,
	TMON_TRIP_TYPE_RESET,
	TMON_TRIP_TYPE_MAX,
पूर्ण;

काष्ठा avs_पंचांगon_trip अणु
	/* HW bit to enable the trip */
	u32 enable_offs;
	u32 enable_mask;

	/* HW field to पढ़ो the trip temperature */
	u32 reg_offs;
	u32 reg_msk;
	पूर्णांक reg_shअगरt;
पूर्ण;

अटल काष्ठा avs_पंचांगon_trip avs_पंचांगon_trips[] = अणु
	/* Trips when temperature is below threshold */
	[TMON_TRIP_TYPE_LOW] = अणु
		.enable_offs	= AVS_TMON_EN_TEMP_INT_SRCS,
		.enable_mask	= AVS_TMON_EN_TEMP_INT_SRCS_low,
		.reg_offs	= AVS_TMON_INT_THRESH,
		.reg_msk	= AVS_TMON_INT_THRESH_low_msk,
		.reg_shअगरt	= AVS_TMON_INT_THRESH_low_shअगरt,
	पूर्ण,
	/* Trips when temperature is above threshold */
	[TMON_TRIP_TYPE_HIGH] = अणु
		.enable_offs	= AVS_TMON_EN_TEMP_INT_SRCS,
		.enable_mask	= AVS_TMON_EN_TEMP_INT_SRCS_high,
		.reg_offs	= AVS_TMON_INT_THRESH,
		.reg_msk	= AVS_TMON_INT_THRESH_high_msk,
		.reg_shअगरt	= AVS_TMON_INT_THRESH_high_shअगरt,
	पूर्ण,
	/* Automatically resets chip when above threshold */
	[TMON_TRIP_TYPE_RESET] = अणु
		.enable_offs	= AVS_TMON_EN_OVERTEMP_RESET,
		.enable_mask	= AVS_TMON_EN_OVERTEMP_RESET_msk,
		.reg_offs	= AVS_TMON_RESET_THRESH,
		.reg_msk	= AVS_TMON_RESET_THRESH_msk,
		.reg_shअगरt	= AVS_TMON_RESET_THRESH_shअगरt,
	पूर्ण,
पूर्ण;

काष्ठा brcmstb_thermal_params अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक mult;
	स्थिर काष्ठा thermal_zone_of_device_ops *of_ops;
पूर्ण;

काष्ठा brcmstb_thermal_priv अणु
	व्योम __iomem *पंचांगon_base;
	काष्ठा device *dev;
	काष्ठा thermal_zone_device *thermal;
	/* Process specअगरic thermal parameters used क्रम calculations */
	स्थिर काष्ठा brcmstb_thermal_params *temp_params;
पूर्ण;

/* Convert a HW code to a temperature पढ़ोing (millidegree celsius) */
अटल अंतरभूत पूर्णांक avs_पंचांगon_code_to_temp(काष्ठा brcmstb_thermal_priv *priv,
					u32 code)
अणु
	पूर्णांक offset = priv->temp_params->offset;
	पूर्णांक mult = priv->temp_params->mult;

	वापस (offset - (पूर्णांक)((code & AVS_TMON_TEMP_MASK) * mult));
पूर्ण

/*
 * Convert a temperature value (millidegree celsius) to a HW code
 *
 * @temp: temperature to convert
 * @low: अगर true, round toward the low side
 */
अटल अंतरभूत u32 avs_पंचांगon_temp_to_code(काष्ठा brcmstb_thermal_priv *priv,
					पूर्णांक temp, bool low)
अणु
	पूर्णांक offset = priv->temp_params->offset;
	पूर्णांक mult = priv->temp_params->mult;

	अगर (temp < AVS_TMON_TEMP_MIN)
		वापस AVS_TMON_TEMP_MAX;	/* Maximum code value */

	अगर (temp >= offset)
		वापस 0;	/* Minimum code value */

	अगर (low)
		वापस (u32)(DIV_ROUND_UP(offset - temp, mult));
	अन्यथा
		वापस (u32)((offset - temp) / mult);
पूर्ण

अटल पूर्णांक brcmstb_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा brcmstb_thermal_priv *priv = data;
	u32 val;
	दीर्घ t;

	val = __raw_पढ़ोl(priv->पंचांगon_base + AVS_TMON_STATUS);

	अगर (!(val & AVS_TMON_STATUS_valid_msk)) अणु
		dev_err(priv->dev, "reading not valid\n");
		वापस -EIO;
	पूर्ण

	val = (val & AVS_TMON_STATUS_data_msk) >> AVS_TMON_STATUS_data_shअगरt;

	t = avs_पंचांगon_code_to_temp(priv, val);
	अगर (t < 0)
		*temp = 0;
	अन्यथा
		*temp = t;

	वापस 0;
पूर्ण

अटल व्योम avs_पंचांगon_trip_enable(काष्ठा brcmstb_thermal_priv *priv,
				 क्रमागत avs_पंचांगon_trip_type type, पूर्णांक en)
अणु
	काष्ठा avs_पंचांगon_trip *trip = &avs_पंचांगon_trips[type];
	u32 val = __raw_पढ़ोl(priv->पंचांगon_base + trip->enable_offs);

	dev_dbg(priv->dev, "%sable trip, type %d\n", en ? "en" : "dis", type);

	अगर (en)
		val |= trip->enable_mask;
	अन्यथा
		val &= ~trip->enable_mask;

	__raw_ग_लिखोl(val, priv->पंचांगon_base + trip->enable_offs);
पूर्ण

अटल पूर्णांक avs_पंचांगon_get_trip_temp(काष्ठा brcmstb_thermal_priv *priv,
				  क्रमागत avs_पंचांगon_trip_type type)
अणु
	काष्ठा avs_पंचांगon_trip *trip = &avs_पंचांगon_trips[type];
	u32 val = __raw_पढ़ोl(priv->पंचांगon_base + trip->reg_offs);

	val &= trip->reg_msk;
	val >>= trip->reg_shअगरt;

	वापस avs_पंचांगon_code_to_temp(priv, val);
पूर्ण

अटल व्योम avs_पंचांगon_set_trip_temp(काष्ठा brcmstb_thermal_priv *priv,
				   क्रमागत avs_पंचांगon_trip_type type,
				   पूर्णांक temp)
अणु
	काष्ठा avs_पंचांगon_trip *trip = &avs_पंचांगon_trips[type];
	u32 val, orig;

	dev_dbg(priv->dev, "set temp %d to %d\n", type, temp);

	/* round toward low temp क्रम the low पूर्णांकerrupt */
	val = avs_पंचांगon_temp_to_code(priv, temp,
				    type == TMON_TRIP_TYPE_LOW);

	val <<= trip->reg_shअगरt;
	val &= trip->reg_msk;

	orig = __raw_पढ़ोl(priv->पंचांगon_base + trip->reg_offs);
	orig &= ~trip->reg_msk;
	orig |= val;
	__raw_ग_लिखोl(orig, priv->पंचांगon_base + trip->reg_offs);
पूर्ण

अटल पूर्णांक avs_पंचांगon_get_पूर्णांकr_temp(काष्ठा brcmstb_thermal_priv *priv)
अणु
	u32 val;

	val = __raw_पढ़ोl(priv->पंचांगon_base + AVS_TMON_TEMP_INT_CODE);
	वापस avs_पंचांगon_code_to_temp(priv, val);
पूर्ण

अटल irqवापस_t brcmstb_पंचांगon_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा brcmstb_thermal_priv *priv = data;
	पूर्णांक low, high, पूर्णांकr;

	low = avs_पंचांगon_get_trip_temp(priv, TMON_TRIP_TYPE_LOW);
	high = avs_पंचांगon_get_trip_temp(priv, TMON_TRIP_TYPE_HIGH);
	पूर्णांकr = avs_पंचांगon_get_पूर्णांकr_temp(priv);

	dev_dbg(priv->dev, "low/intr/high: %d/%d/%d\n",
			low, पूर्णांकr, high);

	/* Disable high-temp until next threshold shअगरt */
	अगर (पूर्णांकr >= high)
		avs_पंचांगon_trip_enable(priv, TMON_TRIP_TYPE_HIGH, 0);
	/* Disable low-temp until next threshold shअगरt */
	अगर (पूर्णांकr <= low)
		avs_पंचांगon_trip_enable(priv, TMON_TRIP_TYPE_LOW, 0);

	/*
	 * Notअगरy using the पूर्णांकerrupt temperature, in हाल the temperature
	 * changes beक्रमe it can next be पढ़ो out
	 */
	thermal_zone_device_update(priv->thermal, पूर्णांकr);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक brcmstb_set_trips(व्योम *data, पूर्णांक low, पूर्णांक high)
अणु
	काष्ठा brcmstb_thermal_priv *priv = data;

	dev_dbg(priv->dev, "set trips %d <--> %d\n", low, high);

	/*
	 * Disable low-temp अगर "low" is too small. As per thermal framework
	 * API, we use -पूर्णांक_उच्च rather than पूर्णांक_न्यून.
	 */
	अगर (low <= -पूर्णांक_उच्च) अणु
		avs_पंचांगon_trip_enable(priv, TMON_TRIP_TYPE_LOW, 0);
	पूर्ण अन्यथा अणु
		avs_पंचांगon_set_trip_temp(priv, TMON_TRIP_TYPE_LOW, low);
		avs_पंचांगon_trip_enable(priv, TMON_TRIP_TYPE_LOW, 1);
	पूर्ण

	/* Disable high-temp अगर "high" is too big. */
	अगर (high == पूर्णांक_उच्च) अणु
		avs_पंचांगon_trip_enable(priv, TMON_TRIP_TYPE_HIGH, 0);
	पूर्ण अन्यथा अणु
		avs_पंचांगon_set_trip_temp(priv, TMON_TRIP_TYPE_HIGH, high);
		avs_पंचांगon_trip_enable(priv, TMON_TRIP_TYPE_HIGH, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops brcmstb_16nm_of_ops = अणु
	.get_temp	= brcmstb_get_temp,
पूर्ण;

अटल स्थिर काष्ठा brcmstb_thermal_params brcmstb_16nm_params = अणु
	.offset	= 457829,
	.mult	= 557,
	.of_ops	= &brcmstb_16nm_of_ops,
पूर्ण;

अटल स्थिर काष्ठा thermal_zone_of_device_ops brcmstb_28nm_of_ops = अणु
	.get_temp	= brcmstb_get_temp,
	.set_trips	= brcmstb_set_trips,
पूर्ण;

अटल स्थिर काष्ठा brcmstb_thermal_params brcmstb_28nm_params = अणु
	.offset	= 410040,
	.mult	= 487,
	.of_ops	= &brcmstb_28nm_of_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id brcmstb_thermal_id_table[] = अणु
	अणु .compatible = "brcm,avs-tmon-bcm7216", .data = &brcmstb_16nm_params पूर्ण,
	अणु .compatible = "brcm,avs-tmon", .data = &brcmstb_28nm_params पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, brcmstb_thermal_id_table);

अटल पूर्णांक brcmstb_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा thermal_zone_of_device_ops *of_ops;
	काष्ठा thermal_zone_device *thermal;
	काष्ठा brcmstb_thermal_priv *priv;
	काष्ठा resource *res;
	पूर्णांक irq, ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->temp_params = of_device_get_match_data(&pdev->dev);
	अगर (!priv->temp_params)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->पंचांगon_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->पंचांगon_base))
		वापस PTR_ERR(priv->पंचांगon_base);

	priv->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, priv);
	of_ops = priv->temp_params->of_ops;

	thermal = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev, 0, priv,
						       of_ops);
	अगर (IS_ERR(thermal)) अणु
		ret = PTR_ERR(thermal);
		dev_err(&pdev->dev, "could not register sensor: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->thermal = thermal;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq >= 0) अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
						brcmstb_पंचांगon_irq_thपढ़ो,
						IRQF_ONESHOT,
						DRV_NAME, priv);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "could not request IRQ: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	dev_info(&pdev->dev, "registered AVS TMON of-sensor driver\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver brcmstb_thermal_driver = अणु
	.probe = brcmstb_thermal_probe,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = brcmstb_thermal_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(brcmstb_thermal_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Brian Norris");
MODULE_DESCRIPTION("Broadcom STB AVS TMON thermal driver");
