<शैली गुरु>
/*
 * HiSilicon thermal sensor driver
 *
 * Copyright (c) 2014-2015 HiSilicon Limited.
 * Copyright (c) 2014-2015 Linaro Limited.
 *
 * Xinwei Kong <kong.kongxinwei@hisilicon.com>
 * Leo Yan <leo.yan@linaro.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>

#समावेश "thermal_core.h"

#घोषणा HI6220_TEMP0_LAG			(0x0)
#घोषणा HI6220_TEMP0_TH				(0x4)
#घोषणा HI6220_TEMP0_RST_TH			(0x8)
#घोषणा HI6220_TEMP0_CFG			(0xC)
#घोषणा HI6220_TEMP0_CFG_SS_MSK			(0xF000)
#घोषणा HI6220_TEMP0_CFG_HDAK_MSK		(0x30)
#घोषणा HI6220_TEMP0_EN				(0x10)
#घोषणा HI6220_TEMP0_INT_EN			(0x14)
#घोषणा HI6220_TEMP0_INT_CLR			(0x18)
#घोषणा HI6220_TEMP0_RST_MSK			(0x1C)
#घोषणा HI6220_TEMP0_VALUE			(0x28)

#घोषणा HI3660_OFFSET(chan)		((chan) * 0x40)
#घोषणा HI3660_TEMP(chan)		(HI3660_OFFSET(chan) + 0x1C)
#घोषणा HI3660_TH(chan)			(HI3660_OFFSET(chan) + 0x20)
#घोषणा HI3660_LAG(chan)		(HI3660_OFFSET(chan) + 0x28)
#घोषणा HI3660_INT_EN(chan)		(HI3660_OFFSET(chan) + 0x2C)
#घोषणा HI3660_INT_CLR(chan)		(HI3660_OFFSET(chan) + 0x30)

#घोषणा HI6220_TEMP_BASE			(-60000)
#घोषणा HI6220_TEMP_RESET			(100000)
#घोषणा HI6220_TEMP_STEP			(785)
#घोषणा HI6220_TEMP_LAG				(3500)

#घोषणा HI3660_TEMP_BASE		(-63780)
#घोषणा HI3660_TEMP_STEP		(205)
#घोषणा HI3660_TEMP_LAG			(4000)

#घोषणा HI6220_CLUSTER0_SENSOR		2
#घोषणा HI6220_CLUSTER1_SENSOR		1

#घोषणा HI3660_LITTLE_SENSOR		0
#घोषणा HI3660_BIG_SENSOR		1
#घोषणा HI3660_G3D_SENSOR		2
#घोषणा HI3660_MODEM_SENSOR		3

काष्ठा hisi_thermal_data;

काष्ठा hisi_thermal_sensor अणु
	काष्ठा hisi_thermal_data *data;
	काष्ठा thermal_zone_device *tzd;
	स्थिर अक्षर *irq_name;
	uपूर्णांक32_t id;
	uपूर्णांक32_t thres_temp;
पूर्ण;

काष्ठा hisi_thermal_ops अणु
	पूर्णांक (*get_temp)(काष्ठा hisi_thermal_sensor *sensor);
	पूर्णांक (*enable_sensor)(काष्ठा hisi_thermal_sensor *sensor);
	पूर्णांक (*disable_sensor)(काष्ठा hisi_thermal_sensor *sensor);
	पूर्णांक (*irq_handler)(काष्ठा hisi_thermal_sensor *sensor);
	पूर्णांक (*probe)(काष्ठा hisi_thermal_data *data);
पूर्ण;

काष्ठा hisi_thermal_data अणु
	स्थिर काष्ठा hisi_thermal_ops *ops;
	काष्ठा hisi_thermal_sensor *sensor;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा clk *clk;
	व्योम __iomem *regs;
	पूर्णांक nr_sensors;
पूर्ण;

/*
 * The temperature computation on the tsensor is as follow:
 *	Unit: millidegree Celsius
 *	Step: 200/255 (0.7843)
 *	Temperature base: -60तओC
 *
 * The रेजिस्टर is programmed in temperature steps, every step is 785
 * millidegree and begins at -60 000 mतओC
 *
 * The temperature from the steps:
 *
 *	Temp = TempBase + (steps x 785)
 *
 * and the steps from the temperature:
 *
 *	steps = (Temp - TempBase) / 785
 *
 */
अटल अंतरभूत पूर्णांक hi6220_thermal_step_to_temp(पूर्णांक step)
अणु
	वापस HI6220_TEMP_BASE + (step * HI6220_TEMP_STEP);
पूर्ण

अटल अंतरभूत पूर्णांक hi6220_thermal_temp_to_step(पूर्णांक temp)
अणु
	वापस DIV_ROUND_UP(temp - HI6220_TEMP_BASE, HI6220_TEMP_STEP);
पूर्ण

/*
 * क्रम Hi3660,
 *	Step: 189/922 (0.205)
 *	Temperature base: -63.780तओC
 *
 * The रेजिस्टर is programmed in temperature steps, every step is 205
 * millidegree and begins at -63 780 mतओC
 */
अटल अंतरभूत पूर्णांक hi3660_thermal_step_to_temp(पूर्णांक step)
अणु
	वापस HI3660_TEMP_BASE + step * HI3660_TEMP_STEP;
पूर्ण

अटल अंतरभूत पूर्णांक hi3660_thermal_temp_to_step(पूर्णांक temp)
अणु
	वापस DIV_ROUND_UP(temp - HI3660_TEMP_BASE, HI3660_TEMP_STEP);
पूर्ण

/*
 * The lag रेजिस्टर contains 5 bits encoding the temperature in steps.
 *
 * Each समय the temperature crosses the threshold boundary, an
 * पूर्णांकerrupt is उठाओd. It could be when the temperature is going
 * above the threshold or below. However, अगर the temperature is
 * fluctuating around this value due to the load, we can receive
 * several पूर्णांकerrupts which may not desired.
 *
 * We can setup a temperature representing the delta between the
 * threshold and the current temperature when the temperature is
 * decreasing.
 *
 * For instance: the lag रेजिस्टर is 5तओC, the threshold is 65तओC, when
 * the temperature reaches 65तओC an पूर्णांकerrupt is उठाओd and when the
 * temperature decrease to 65तओC - 5तओC another पूर्णांकerrupt is उठाओd.
 *
 * A very लघु lag can lead to an पूर्णांकerrupt storm, a दीर्घ lag
 * increase the latency to react to the temperature changes.  In our
 * हाल, that is not really a problem as we are polling the
 * temperature.
 *
 * [0:4] : lag रेजिस्टर
 *
 * The temperature is coded in steps, cf. HI6220_TEMP_STEP.
 *
 * Min : 0x00 :  0.0 तओC
 * Max : 0x1F : 24.3 तओC
 *
 * The 'value' parameter is in milliCelsius.
 */
अटल अंतरभूत व्योम hi6220_thermal_set_lag(व्योम __iomem *addr, पूर्णांक value)
अणु
	ग_लिखोl(DIV_ROUND_UP(value, HI6220_TEMP_STEP) & 0x1F,
			addr + HI6220_TEMP0_LAG);
पूर्ण

अटल अंतरभूत व्योम hi6220_thermal_alarm_clear(व्योम __iomem *addr, पूर्णांक value)
अणु
	ग_लिखोl(value, addr + HI6220_TEMP0_INT_CLR);
पूर्ण

अटल अंतरभूत व्योम hi6220_thermal_alarm_enable(व्योम __iomem *addr, पूर्णांक value)
अणु
	ग_लिखोl(value, addr + HI6220_TEMP0_INT_EN);
पूर्ण

अटल अंतरभूत व्योम hi6220_thermal_alarm_set(व्योम __iomem *addr, पूर्णांक temp)
अणु
	ग_लिखोl(hi6220_thermal_temp_to_step(temp) | 0x0FFFFFF00,
	       addr + HI6220_TEMP0_TH);
पूर्ण

अटल अंतरभूत व्योम hi6220_thermal_reset_set(व्योम __iomem *addr, पूर्णांक temp)
अणु
	ग_लिखोl(hi6220_thermal_temp_to_step(temp), addr + HI6220_TEMP0_RST_TH);
पूर्ण

अटल अंतरभूत व्योम hi6220_thermal_reset_enable(व्योम __iomem *addr, पूर्णांक value)
अणु
	ग_लिखोl(value, addr + HI6220_TEMP0_RST_MSK);
पूर्ण

अटल अंतरभूत व्योम hi6220_thermal_enable(व्योम __iomem *addr, पूर्णांक value)
अणु
	ग_लिखोl(value, addr + HI6220_TEMP0_EN);
पूर्ण

अटल अंतरभूत पूर्णांक hi6220_thermal_get_temperature(व्योम __iomem *addr)
अणु
	वापस hi6220_thermal_step_to_temp(पढ़ोl(addr + HI6220_TEMP0_VALUE));
पूर्ण

/*
 * [0:6] lag रेजिस्टर
 *
 * The temperature is coded in steps, cf. HI3660_TEMP_STEP.
 *
 * Min : 0x00 :  0.0 तओC
 * Max : 0x7F : 26.0 तओC
 *
 */
अटल अंतरभूत व्योम hi3660_thermal_set_lag(व्योम __iomem *addr,
					  पूर्णांक id, पूर्णांक value)
अणु
	ग_लिखोl(DIV_ROUND_UP(value, HI3660_TEMP_STEP) & 0x7F,
			addr + HI3660_LAG(id));
पूर्ण

अटल अंतरभूत व्योम hi3660_thermal_alarm_clear(व्योम __iomem *addr,
					      पूर्णांक id, पूर्णांक value)
अणु
	ग_लिखोl(value, addr + HI3660_INT_CLR(id));
पूर्ण

अटल अंतरभूत व्योम hi3660_thermal_alarm_enable(व्योम __iomem *addr,
					       पूर्णांक id, पूर्णांक value)
अणु
	ग_लिखोl(value, addr + HI3660_INT_EN(id));
पूर्ण

अटल अंतरभूत व्योम hi3660_thermal_alarm_set(व्योम __iomem *addr,
					    पूर्णांक id, पूर्णांक value)
अणु
	ग_लिखोl(value, addr + HI3660_TH(id));
पूर्ण

अटल अंतरभूत पूर्णांक hi3660_thermal_get_temperature(व्योम __iomem *addr, पूर्णांक id)
अणु
	वापस hi3660_thermal_step_to_temp(पढ़ोl(addr + HI3660_TEMP(id)));
पूर्ण

/*
 * Temperature configuration रेजिस्टर - Sensor selection
 *
 * Bits [19:12]
 *
 * 0x0: local sensor (शेष)
 * 0x1: remote sensor 1 (ACPU cluster 1)
 * 0x2: remote sensor 2 (ACPU cluster 0)
 * 0x3: remote sensor 3 (G3D)
 */
अटल अंतरभूत व्योम hi6220_thermal_sensor_select(व्योम __iomem *addr, पूर्णांक sensor)
अणु
	ग_लिखोl((पढ़ोl(addr + HI6220_TEMP0_CFG) & ~HI6220_TEMP0_CFG_SS_MSK) |
	       (sensor << 12), addr + HI6220_TEMP0_CFG);
पूर्ण

/*
 * Temperature configuration रेजिस्टर - Hdak conversion polling पूर्णांकerval
 *
 * Bits [5:4]
 *
 * 0x0 :   0.768 ms
 * 0x1 :   6.144 ms
 * 0x2 :  49.152 ms
 * 0x3 : 393.216 ms
 */
अटल अंतरभूत व्योम hi6220_thermal_hdak_set(व्योम __iomem *addr, पूर्णांक value)
अणु
	ग_लिखोl((पढ़ोl(addr + HI6220_TEMP0_CFG) & ~HI6220_TEMP0_CFG_HDAK_MSK) |
	       (value << 4), addr + HI6220_TEMP0_CFG);
पूर्ण

अटल पूर्णांक hi6220_thermal_irq_handler(काष्ठा hisi_thermal_sensor *sensor)
अणु
	काष्ठा hisi_thermal_data *data = sensor->data;

	hi6220_thermal_alarm_clear(data->regs, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक hi3660_thermal_irq_handler(काष्ठा hisi_thermal_sensor *sensor)
अणु
	काष्ठा hisi_thermal_data *data = sensor->data;

	hi3660_thermal_alarm_clear(data->regs, sensor->id, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक hi6220_thermal_get_temp(काष्ठा hisi_thermal_sensor *sensor)
अणु
	काष्ठा hisi_thermal_data *data = sensor->data;

	वापस hi6220_thermal_get_temperature(data->regs);
पूर्ण

अटल पूर्णांक hi3660_thermal_get_temp(काष्ठा hisi_thermal_sensor *sensor)
अणु
	काष्ठा hisi_thermal_data *data = sensor->data;

	वापस hi3660_thermal_get_temperature(data->regs, sensor->id);
पूर्ण

अटल पूर्णांक hi6220_thermal_disable_sensor(काष्ठा hisi_thermal_sensor *sensor)
अणु
	काष्ठा hisi_thermal_data *data = sensor->data;

	/* disable sensor module */
	hi6220_thermal_enable(data->regs, 0);
	hi6220_thermal_alarm_enable(data->regs, 0);
	hi6220_thermal_reset_enable(data->regs, 0);

	clk_disable_unprepare(data->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक hi3660_thermal_disable_sensor(काष्ठा hisi_thermal_sensor *sensor)
अणु
	काष्ठा hisi_thermal_data *data = sensor->data;

	/* disable sensor module */
	hi3660_thermal_alarm_enable(data->regs, sensor->id, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक hi6220_thermal_enable_sensor(काष्ठा hisi_thermal_sensor *sensor)
अणु
	काष्ठा hisi_thermal_data *data = sensor->data;
	पूर्णांक ret;

	/* enable घड़ी क्रम tsensor */
	ret = clk_prepare_enable(data->clk);
	अगर (ret)
		वापस ret;

	/* disable module firstly */
	hi6220_thermal_reset_enable(data->regs, 0);
	hi6220_thermal_enable(data->regs, 0);

	/* select sensor id */
	hi6220_thermal_sensor_select(data->regs, sensor->id);

	/* setting the hdak समय */
	hi6220_thermal_hdak_set(data->regs, 0);

	/* setting lag value between current temp and the threshold */
	hi6220_thermal_set_lag(data->regs, HI6220_TEMP_LAG);

	/* enable क्रम पूर्णांकerrupt */
	hi6220_thermal_alarm_set(data->regs, sensor->thres_temp);

	hi6220_thermal_reset_set(data->regs, HI6220_TEMP_RESET);

	/* enable module */
	hi6220_thermal_reset_enable(data->regs, 1);
	hi6220_thermal_enable(data->regs, 1);

	hi6220_thermal_alarm_clear(data->regs, 0);
	hi6220_thermal_alarm_enable(data->regs, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक hi3660_thermal_enable_sensor(काष्ठा hisi_thermal_sensor *sensor)
अणु
	अचिन्हित पूर्णांक value;
	काष्ठा hisi_thermal_data *data = sensor->data;

	/* disable पूर्णांकerrupt */
	hi3660_thermal_alarm_enable(data->regs, sensor->id, 0);

	/* setting lag value between current temp and the threshold */
	hi3660_thermal_set_lag(data->regs, sensor->id, HI3660_TEMP_LAG);

	/* set पूर्णांकerrupt threshold */
	value = hi3660_thermal_temp_to_step(sensor->thres_temp);
	hi3660_thermal_alarm_set(data->regs, sensor->id, value);

	/* enable पूर्णांकerrupt */
	hi3660_thermal_alarm_clear(data->regs, sensor->id, 1);
	hi3660_thermal_alarm_enable(data->regs, sensor->id, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक hi6220_thermal_probe(काष्ठा hisi_thermal_data *data)
अणु
	काष्ठा platक्रमm_device *pdev = data->pdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	data->clk = devm_clk_get(dev, "thermal_clk");
	अगर (IS_ERR(data->clk)) अणु
		ret = PTR_ERR(data->clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get thermal clk: %d\n", ret);
		वापस ret;
	पूर्ण

	data->sensor = devm_kzalloc(dev, माप(*data->sensor), GFP_KERNEL);
	अगर (!data->sensor)
		वापस -ENOMEM;

	data->sensor[0].id = HI6220_CLUSTER0_SENSOR;
	data->sensor[0].irq_name = "tsensor_intr";
	data->sensor[0].data = data;
	data->nr_sensors = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक hi3660_thermal_probe(काष्ठा hisi_thermal_data *data)
अणु
	काष्ठा platक्रमm_device *pdev = data->pdev;
	काष्ठा device *dev = &pdev->dev;

	data->nr_sensors = 1;

	data->sensor = devm_kzalloc(dev, माप(*data->sensor) *
				    data->nr_sensors, GFP_KERNEL);
	अगर (!data->sensor)
		वापस -ENOMEM;

	data->sensor[0].id = HI3660_BIG_SENSOR;
	data->sensor[0].irq_name = "tsensor_a73";
	data->sensor[0].data = data;

	data->sensor[1].id = HI3660_LITTLE_SENSOR;
	data->sensor[1].irq_name = "tsensor_a53";
	data->sensor[1].data = data;

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_thermal_get_temp(व्योम *__data, पूर्णांक *temp)
अणु
	काष्ठा hisi_thermal_sensor *sensor = __data;
	काष्ठा hisi_thermal_data *data = sensor->data;

	*temp = data->ops->get_temp(sensor);

	dev_dbg(&data->pdev->dev, "tzd=%p, id=%d, temp=%d, thres=%d\n",
		sensor->tzd, sensor->id, *temp, sensor->thres_temp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops hisi_of_thermal_ops = अणु
	.get_temp = hisi_thermal_get_temp,
पूर्ण;

अटल irqवापस_t hisi_thermal_alarm_irq_thपढ़ो(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा hisi_thermal_sensor *sensor = dev;
	काष्ठा hisi_thermal_data *data = sensor->data;
	पूर्णांक temp = 0;

	data->ops->irq_handler(sensor);

	hisi_thermal_get_temp(sensor, &temp);

	अगर (temp >= sensor->thres_temp) अणु
		dev_crit(&data->pdev->dev,
			 "sensor <%d> THERMAL ALARM: %d > %d\n",
			 sensor->id, temp, sensor->thres_temp);

		thermal_zone_device_update(sensor->tzd,
					   THERMAL_EVENT_UNSPECIFIED);

	पूर्ण अन्यथा अणु
		dev_crit(&data->pdev->dev,
			 "sensor <%d> THERMAL ALARM stopped: %d < %d\n",
			 sensor->id, temp, sensor->thres_temp);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hisi_thermal_रेजिस्टर_sensor(काष्ठा platक्रमm_device *pdev,
					काष्ठा hisi_thermal_sensor *sensor)
अणु
	पूर्णांक ret, i;
	स्थिर काष्ठा thermal_trip *trip;

	sensor->tzd = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev,
							   sensor->id, sensor,
							   &hisi_of_thermal_ops);
	अगर (IS_ERR(sensor->tzd)) अणु
		ret = PTR_ERR(sensor->tzd);
		sensor->tzd = शून्य;
		dev_err(&pdev->dev, "failed to register sensor id %d: %d\n",
			sensor->id, ret);
		वापस ret;
	पूर्ण

	trip = of_thermal_get_trip_poपूर्णांकs(sensor->tzd);

	क्रम (i = 0; i < of_thermal_get_ntrips(sensor->tzd); i++) अणु
		अगर (trip[i].type == THERMAL_TRIP_PASSIVE) अणु
			sensor->thres_temp = trip[i].temperature;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hisi_thermal_ops hi6220_ops = अणु
	.get_temp	= hi6220_thermal_get_temp,
	.enable_sensor	= hi6220_thermal_enable_sensor,
	.disable_sensor	= hi6220_thermal_disable_sensor,
	.irq_handler	= hi6220_thermal_irq_handler,
	.probe		= hi6220_thermal_probe,
पूर्ण;

अटल स्थिर काष्ठा hisi_thermal_ops hi3660_ops = अणु
	.get_temp	= hi3660_thermal_get_temp,
	.enable_sensor	= hi3660_thermal_enable_sensor,
	.disable_sensor	= hi3660_thermal_disable_sensor,
	.irq_handler	= hi3660_thermal_irq_handler,
	.probe		= hi3660_thermal_probe,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_hisi_thermal_match[] = अणु
	अणु
		.compatible = "hisilicon,tsensor",
		.data = &hi6220_ops,
	पूर्ण,
	अणु
		.compatible = "hisilicon,hi3660-tsensor",
		.data = &hi3660_ops,
	पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_hisi_thermal_match);

अटल व्योम hisi_thermal_toggle_sensor(काष्ठा hisi_thermal_sensor *sensor,
				       bool on)
अणु
	काष्ठा thermal_zone_device *tzd = sensor->tzd;

	अगर (on)
		thermal_zone_device_enable(tzd);
	अन्यथा
		thermal_zone_device_disable(tzd);
पूर्ण

अटल पूर्णांक hisi_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_thermal_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक i, ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->pdev = pdev;
	platक्रमm_set_drvdata(pdev, data);
	data->ops = of_device_get_match_data(dev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(data->regs))
		वापस PTR_ERR(data->regs);

	ret = data->ops->probe(data);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < data->nr_sensors; i++) अणु
		काष्ठा hisi_thermal_sensor *sensor = &data->sensor[i];

		ret = hisi_thermal_रेजिस्टर_sensor(pdev, sensor);
		अगर (ret) अणु
			dev_err(dev, "failed to register thermal sensor: %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = platक्रमm_get_irq(pdev, 0);
		अगर (ret < 0)
			वापस ret;

		ret = devm_request_thपढ़ोed_irq(dev, ret, शून्य,
						hisi_thermal_alarm_irq_thपढ़ो,
						IRQF_ONESHOT, sensor->irq_name,
						sensor);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to request alarm irq: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = data->ops->enable_sensor(sensor);
		अगर (ret) अणु
			dev_err(dev, "Failed to setup the sensor: %d\n", ret);
			वापस ret;
		पूर्ण

		hisi_thermal_toggle_sensor(sensor, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_thermal_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < data->nr_sensors; i++) अणु
		काष्ठा hisi_thermal_sensor *sensor = &data->sensor[i];

		hisi_thermal_toggle_sensor(sensor, false);
		data->ops->disable_sensor(sensor);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hisi_thermal_suspend(काष्ठा device *dev)
अणु
	काष्ठा hisi_thermal_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < data->nr_sensors; i++)
		data->ops->disable_sensor(&data->sensor[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_thermal_resume(काष्ठा device *dev)
अणु
	काष्ठा hisi_thermal_data *data = dev_get_drvdata(dev);
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < data->nr_sensors; i++)
		ret |= data->ops->enable_sensor(&data->sensor[i]);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(hisi_thermal_pm_ops,
			 hisi_thermal_suspend, hisi_thermal_resume);

अटल काष्ठा platक्रमm_driver hisi_thermal_driver = अणु
	.driver = अणु
		.name		= "hisi_thermal",
		.pm		= &hisi_thermal_pm_ops,
		.of_match_table = of_hisi_thermal_match,
	पूर्ण,
	.probe	= hisi_thermal_probe,
	.हटाओ	= hisi_thermal_हटाओ,
पूर्ण;

module_platक्रमm_driver(hisi_thermal_driver);

MODULE_AUTHOR("Xinwei Kong <kong.kongxinwei@hisilicon.com>");
MODULE_AUTHOR("Leo Yan <leo.yan@linaro.org>");
MODULE_DESCRIPTION("HiSilicon thermal driver");
MODULE_LICENSE("GPL v2");
