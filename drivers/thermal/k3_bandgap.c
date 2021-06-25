<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TI Bandgap temperature sensor driver क्रम K3 SoC Family
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/thermal.h>
#समावेश <linux/types.h>

#घोषणा K3_VTM_DEVINFO_PWR0_OFFSET		0x4
#घोषणा K3_VTM_DEVINFO_PWR0_TEMPSENS_CT_MASK	0xf0
#घोषणा K3_VTM_TMPSENS0_CTRL_OFFSET	0x80
#घोषणा K3_VTM_REGS_PER_TS			0x10
#घोषणा K3_VTM_TS_STAT_DTEMP_MASK	0x3ff
#घोषणा K3_VTM_TMPSENS_CTRL_CBIASSEL	BIT(0)
#घोषणा K3_VTM_TMPSENS_CTRL_SOC		BIT(5)
#घोषणा K3_VTM_TMPSENS_CTRL_CLRZ		BIT(6)
#घोषणा K3_VTM_TMPSENS_CTRL_CLKON_REQ	BIT(7)

#घोषणा K3_VTM_ADC_BEGIN_VAL		540
#घोषणा K3_VTM_ADC_END_VAL		944

अटल स्थिर पूर्णांक k3_adc_to_temp[] = अणु
	-40000, -40000, -40000, -40000, -39800, -39400, -39000, -38600, -38200,
	-37800, -37400, -37000, -36600, -36200, -35800, -35300, -34700, -34200,
	-33800, -33400, -33000, -32600, -32200, -31800, -31400, -31000, -30600,
	-30200, -29800, -29400, -29000, -28600, -28200, -27700, -27100, -26600,
	-26200, -25800, -25400, -25000, -24600, -24200, -23800, -23400, -23000,
	-22600, -22200, -21800, -21400, -21000, -20500, -19900, -19400, -19000,
	-18600, -18200, -17800, -17400, -17000, -16600, -16200, -15800, -15400,
	-15000, -14600, -14200, -13800, -13400, -13000, -12500, -11900, -11400,
	-11000, -10600, -10200, -9800, -9400, -9000, -8600, -8200, -7800, -7400,
	-7000, -6600, -6200, -5800, -5400, -5000, -4500, -3900, -3400, -3000,
	-2600, -2200, -1800, -1400, -1000, -600, -200, 200, 600, 1000, 1400,
	1800, 2200, 2600, 3000, 3400, 3900, 4500, 5000, 5400, 5800, 6200, 6600,
	7000, 7400, 7800, 8200, 8600, 9000, 9400, 9800, 10200, 10600, 11000,
	11400, 11800, 12200, 12700, 13300, 13800, 14200, 14600, 15000, 15400,
	15800, 16200, 16600, 17000, 17400, 17800, 18200, 18600, 19000, 19400,
	19800, 20200, 20600, 21000, 21400, 21900, 22500, 23000, 23400, 23800,
	24200, 24600, 25000, 25400, 25800, 26200, 26600, 27000, 27400, 27800,
	28200, 28600, 29000, 29400, 29800, 30200, 30600, 31000, 31400, 31900,
	32500, 33000, 33400, 33800, 34200, 34600, 35000, 35400, 35800, 36200,
	36600, 37000, 37400, 37800, 38200, 38600, 39000, 39400, 39800, 40200,
	40600, 41000, 41400, 41800, 42200, 42600, 43100, 43700, 44200, 44600,
	45000, 45400, 45800, 46200, 46600, 47000, 47400, 47800, 48200, 48600,
	49000, 49400, 49800, 50200, 50600, 51000, 51400, 51800, 52200, 52600,
	53000, 53400, 53800, 54200, 54600, 55000, 55400, 55900, 56500, 57000,
	57400, 57800, 58200, 58600, 59000, 59400, 59800, 60200, 60600, 61000,
	61400, 61800, 62200, 62600, 63000, 63400, 63800, 64200, 64600, 65000,
	65400, 65800, 66200, 66600, 67000, 67400, 67800, 68200, 68600, 69000,
	69400, 69800, 70200, 70600, 71000, 71500, 72100, 72600, 73000, 73400,
	73800, 74200, 74600, 75000, 75400, 75800, 76200, 76600, 77000, 77400,
	77800, 78200, 78600, 79000, 79400, 79800, 80200, 80600, 81000, 81400,
	81800, 82200, 82600, 83000, 83400, 83800, 84200, 84600, 85000, 85400,
	85800, 86200, 86600, 87000, 87400, 87800, 88200, 88600, 89000, 89400,
	89800, 90200, 90600, 91000, 91400, 91800, 92200, 92600, 93000, 93400,
	93800, 94200, 94600, 95000, 95400, 95800, 96200, 96600, 97000, 97500,
	98100, 98600, 99000, 99400, 99800, 100200, 100600, 101000, 101400,
	101800, 102200, 102600, 103000, 103400, 103800, 104200, 104600, 105000,
	105400, 105800, 106200, 106600, 107000, 107400, 107800, 108200, 108600,
	109000, 109400, 109800, 110200, 110600, 111000, 111400, 111800, 112200,
	112600, 113000, 113400, 113800, 114200, 114600, 115000, 115400, 115800,
	116200, 116600, 117000, 117400, 117800, 118200, 118600, 119000, 119400,
	119800, 120200, 120600, 121000, 121400, 121800, 122200, 122600, 123000,
	123400, 123800, 124200, 124600, 124900, 125000,
पूर्ण;

काष्ठा k3_bandgap अणु
	व्योम __iomem *base;
	स्थिर काष्ठा k3_bandgap_data *conf;
पूर्ण;

/* common data काष्ठाures */
काष्ठा k3_thermal_data अणु
	काष्ठा thermal_zone_device *tzd;
	काष्ठा k3_bandgap *bgp;
	पूर्णांक sensor_id;
	u32 ctrl_offset;
	u32 stat_offset;
पूर्ण;

अटल अचिन्हित पूर्णांक vपंचांग_get_best_value(अचिन्हित पूर्णांक s0, अचिन्हित पूर्णांक s1,
				       अचिन्हित पूर्णांक s2)
अणु
	पूर्णांक d01 = असल(s0 - s1);
	पूर्णांक d02 = असल(s0 - s2);
	पूर्णांक d12 = असल(s1 - s2);

	अगर (d01 <= d02 && d01 <= d12)
		वापस (s0 + s1) / 2;

	अगर (d02 <= d01 && d02 <= d12)
		वापस (s0 + s2) / 2;

	वापस (s1 + s2) / 2;
पूर्ण

अटल पूर्णांक k3_bgp_पढ़ो_temp(काष्ठा k3_thermal_data *devdata,
			    पूर्णांक *temp)
अणु
	काष्ठा k3_bandgap *bgp;
	अचिन्हित पूर्णांक dtemp, s0, s1, s2;

	bgp = devdata->bgp;

	/*
	 * Errata is applicable क्रम am654 pg 1.0 silicon. There
	 * is a variation of the order क्रम 8-10 degree centigrade.
	 * Work around that by getting the average of two बंदst
	 * पढ़ोings out of three पढ़ोings everyसमय we want to
	 * report temperatures.
	 *
	 * Errata workaround.
	 */
	s0 = पढ़ोl(bgp->base + devdata->stat_offset) &
		K3_VTM_TS_STAT_DTEMP_MASK;
	s1 = पढ़ोl(bgp->base + devdata->stat_offset) &
		K3_VTM_TS_STAT_DTEMP_MASK;
	s2 = पढ़ोl(bgp->base + devdata->stat_offset) &
		K3_VTM_TS_STAT_DTEMP_MASK;
	dtemp = vपंचांग_get_best_value(s0, s1, s2);

	अगर (dtemp < K3_VTM_ADC_BEGIN_VAL || dtemp > K3_VTM_ADC_END_VAL)
		वापस -EINVAL;

	*temp = k3_adc_to_temp[dtemp - K3_VTM_ADC_BEGIN_VAL];

	वापस 0;
पूर्ण

अटल पूर्णांक k3_thermal_get_temp(व्योम *devdata, पूर्णांक *temp)
अणु
	काष्ठा k3_thermal_data *data = devdata;
	पूर्णांक ret = 0;

	ret = k3_bgp_पढ़ो_temp(data, temp);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops k3_of_thermal_ops = अणु
	.get_temp = k3_thermal_get_temp,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_k3_bandgap_match[];

अटल पूर्णांक k3_bandgap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0, cnt, val, id;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा k3_bandgap *bgp;
	काष्ठा k3_thermal_data *data;

	अगर (ARRAY_SIZE(k3_adc_to_temp) != (K3_VTM_ADC_END_VAL + 1 -
						K3_VTM_ADC_BEGIN_VAL))
		वापस -EINVAL;

	bgp = devm_kzalloc(&pdev->dev, माप(*bgp), GFP_KERNEL);
	अगर (!bgp)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	bgp->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(bgp->base))
		वापस PTR_ERR(bgp->base);

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		pm_runसमय_disable(dev);
		वापस ret;
	पूर्ण

	/* Get the sensor count in the VTM */
	val = पढ़ोl(bgp->base + K3_VTM_DEVINFO_PWR0_OFFSET);
	cnt = val & K3_VTM_DEVINFO_PWR0_TEMPSENS_CT_MASK;
	cnt >>= __ffs(K3_VTM_DEVINFO_PWR0_TEMPSENS_CT_MASK);

	data = devm_kसुस्मृति(dev, cnt, माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	/* Register the thermal sensors */
	क्रम (id = 0; id < cnt; id++) अणु
		data[id].sensor_id = id;
		data[id].bgp = bgp;
		data[id].ctrl_offset = K3_VTM_TMPSENS0_CTRL_OFFSET +
					id * K3_VTM_REGS_PER_TS;
		data[id].stat_offset = data[id].ctrl_offset + 0x8;

		val = पढ़ोl(data[id].bgp->base + data[id].ctrl_offset);
		val |= (K3_VTM_TMPSENS_CTRL_SOC |
			K3_VTM_TMPSENS_CTRL_CLRZ |
			K3_VTM_TMPSENS_CTRL_CLKON_REQ);
		val &= ~K3_VTM_TMPSENS_CTRL_CBIASSEL;
		ग_लिखोl(val, data[id].bgp->base + data[id].ctrl_offset);

		data[id].tzd =
		devm_thermal_zone_of_sensor_रेजिस्टर(dev, id,
						     &data[id],
						     &k3_of_thermal_ops);
		अगर (IS_ERR(data[id].tzd)) अणु
			dev_err(dev, "thermal zone device is NULL\n");
			ret = PTR_ERR(data[id].tzd);
			जाओ err_alloc;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, bgp);

	वापस 0;

err_alloc:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक k3_bandgap_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_k3_bandgap_match[] = अणु
	अणु
		.compatible = "ti,am654-vtm",
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_k3_bandgap_match);

अटल काष्ठा platक्रमm_driver k3_bandgap_sensor_driver = अणु
	.probe = k3_bandgap_probe,
	.हटाओ = k3_bandgap_हटाओ,
	.driver = अणु
		.name = "k3-soc-thermal",
		.of_match_table	= of_k3_bandgap_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(k3_bandgap_sensor_driver);

MODULE_DESCRIPTION("K3 bandgap temperature sensor driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("J Keerthy <j-keerthy@ti.com>");
