<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic Exynos Bus frequency driver with DEVFREQ Framework
 *
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
 * Author : Chanwoo Choi <cw00.choi@samsung.com>
 *
 * This driver support Exynos Bus frequency feature by using
 * DEVFREQ framework and is based on drivers/devfreq/exynos/exynos4_bus.c.
 */

#समावेश <linux/clk.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/devfreq-event.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा DEFAULT_SATURATION_RATIO	40

काष्ठा exynos_bus अणु
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *icc_pdev;

	काष्ठा devfreq *devfreq;
	काष्ठा devfreq_event_dev **edev;
	अचिन्हित पूर्णांक edev_count;
	काष्ठा mutex lock;

	अचिन्हित दीर्घ curr_freq;

	काष्ठा opp_table *opp_table;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक ratio;
पूर्ण;

/*
 * Control the devfreq-event device to get the current state of bus
 */
#घोषणा exynos_bus_ops_edev(ops)				\
अटल पूर्णांक exynos_bus_##ops(काष्ठा exynos_bus *bus)		\
अणु								\
	पूर्णांक i, ret;						\
								\
	क्रम (i = 0; i < bus->edev_count; i++) अणु			\
		अगर (!bus->edev[i])				\
			जारी;				\
		ret = devfreq_event_##ops(bus->edev[i]);	\
		अगर (ret < 0)					\
			वापस ret;				\
	पूर्ण							\
								\
	वापस 0;						\
पूर्ण
exynos_bus_ops_edev(enable_edev);
exynos_bus_ops_edev(disable_edev);
exynos_bus_ops_edev(set_event);

अटल पूर्णांक exynos_bus_get_event(काष्ठा exynos_bus *bus,
				काष्ठा devfreq_event_data *edata)
अणु
	काष्ठा devfreq_event_data event_data;
	अचिन्हित दीर्घ load_count = 0, total_count = 0;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < bus->edev_count; i++) अणु
		अगर (!bus->edev[i])
			जारी;

		ret = devfreq_event_get_event(bus->edev[i], &event_data);
		अगर (ret < 0)
			वापस ret;

		अगर (i == 0 || event_data.load_count > load_count) अणु
			load_count = event_data.load_count;
			total_count = event_data.total_count;
		पूर्ण
	पूर्ण

	edata->load_count = load_count;
	edata->total_count = total_count;

	वापस ret;
पूर्ण

/*
 * devfreq function क्रम both simple-ondemand and passive governor
 */
अटल पूर्णांक exynos_bus_target(काष्ठा device *dev, अचिन्हित दीर्घ *freq, u32 flags)
अणु
	काष्ठा exynos_bus *bus = dev_get_drvdata(dev);
	काष्ठा dev_pm_opp *new_opp;
	पूर्णांक ret = 0;

	/* Get correct frequency क्रम bus. */
	new_opp = devfreq_recommended_opp(dev, freq, flags);
	अगर (IS_ERR(new_opp)) अणु
		dev_err(dev, "failed to get recommended opp instance\n");
		वापस PTR_ERR(new_opp);
	पूर्ण

	dev_pm_opp_put(new_opp);

	/* Change voltage and frequency according to new OPP level */
	mutex_lock(&bus->lock);
	ret = dev_pm_opp_set_rate(dev, *freq);
	अगर (!ret)
		bus->curr_freq = *freq;

	mutex_unlock(&bus->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_bus_get_dev_status(काष्ठा device *dev,
				     काष्ठा devfreq_dev_status *stat)
अणु
	काष्ठा exynos_bus *bus = dev_get_drvdata(dev);
	काष्ठा devfreq_event_data edata;
	पूर्णांक ret;

	stat->current_frequency = bus->curr_freq;

	ret = exynos_bus_get_event(bus, &edata);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get event from devfreq-event devices\n");
		stat->total_समय = stat->busy_समय = 0;
		जाओ err;
	पूर्ण

	stat->busy_समय = (edata.load_count * 100) / bus->ratio;
	stat->total_समय = edata.total_count;

	dev_dbg(dev, "Usage of devfreq-event : %lu/%lu\n", stat->busy_समय,
							stat->total_समय);

err:
	ret = exynos_bus_set_event(bus);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set event to devfreq-event devices\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम exynos_bus_निकास(काष्ठा device *dev)
अणु
	काष्ठा exynos_bus *bus = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = exynos_bus_disable_edev(bus);
	अगर (ret < 0)
		dev_warn(dev, "failed to disable the devfreq-event devices\n");

	platक्रमm_device_unरेजिस्टर(bus->icc_pdev);

	dev_pm_opp_of_हटाओ_table(dev);
	clk_disable_unprepare(bus->clk);
	dev_pm_opp_put_regulators(bus->opp_table);
	bus->opp_table = शून्य;
पूर्ण

अटल व्योम exynos_bus_passive_निकास(काष्ठा device *dev)
अणु
	काष्ठा exynos_bus *bus = dev_get_drvdata(dev);

	platक्रमm_device_unरेजिस्टर(bus->icc_pdev);

	dev_pm_opp_of_हटाओ_table(dev);
	clk_disable_unprepare(bus->clk);
पूर्ण

अटल पूर्णांक exynos_bus_parent_parse_of(काष्ठा device_node *np,
					काष्ठा exynos_bus *bus)
अणु
	काष्ठा device *dev = bus->dev;
	काष्ठा opp_table *opp_table;
	स्थिर अक्षर *vdd = "vdd";
	पूर्णांक i, ret, count, size;

	opp_table = dev_pm_opp_set_regulators(dev, &vdd, 1);
	अगर (IS_ERR(opp_table)) अणु
		ret = PTR_ERR(opp_table);
		dev_err(dev, "failed to set regulators %d\n", ret);
		वापस ret;
	पूर्ण

	bus->opp_table = opp_table;

	/*
	 * Get the devfreq-event devices to get the current utilization of
	 * buses. This raw data will be used in devfreq ondemand governor.
	 */
	count = devfreq_event_get_edev_count(dev, "devfreq-events");
	अगर (count < 0) अणु
		dev_err(dev, "failed to get the count of devfreq-event dev\n");
		ret = count;
		जाओ err_regulator;
	पूर्ण
	bus->edev_count = count;

	size = माप(*bus->edev) * count;
	bus->edev = devm_kzalloc(dev, size, GFP_KERNEL);
	अगर (!bus->edev) अणु
		ret = -ENOMEM;
		जाओ err_regulator;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		bus->edev[i] = devfreq_event_get_edev_by_phandle(dev,
							"devfreq-events", i);
		अगर (IS_ERR(bus->edev[i])) अणु
			ret = -EPROBE_DEFER;
			जाओ err_regulator;
		पूर्ण
	पूर्ण

	/*
	 * Optionally, Get the saturation ratio according to Exynos SoC
	 * When measuring the utilization of each AXI bus with devfreq-event
	 * devices, the measured real cycle might be much lower than the
	 * total cycle of bus during sampling rate. In result, the devfreq
	 * simple-ondemand governor might not decide to change the current
	 * frequency due to too utilization (= real cycle/total cycle).
	 * So, this property is used to adjust the utilization when calculating
	 * the busy_समय in exynos_bus_get_dev_status().
	 */
	अगर (of_property_पढ़ो_u32(np, "exynos,saturation-ratio", &bus->ratio))
		bus->ratio = DEFAULT_SATURATION_RATIO;

	वापस 0;

err_regulator:
	dev_pm_opp_put_regulators(bus->opp_table);
	bus->opp_table = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_bus_parse_of(काष्ठा device_node *np,
			      काष्ठा exynos_bus *bus)
अणु
	काष्ठा device *dev = bus->dev;
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	/* Get the घड़ी to provide each bus with source घड़ी */
	bus->clk = devm_clk_get(dev, "bus");
	अगर (IS_ERR(bus->clk)) अणु
		dev_err(dev, "failed to get bus clock\n");
		वापस PTR_ERR(bus->clk);
	पूर्ण

	ret = clk_prepare_enable(bus->clk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get enable clock\n");
		वापस ret;
	पूर्ण

	/* Get the freq and voltage from OPP table to scale the bus freq */
	ret = dev_pm_opp_of_add_table(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get OPP table\n");
		जाओ err_clk;
	पूर्ण

	rate = clk_get_rate(bus->clk);

	opp = devfreq_recommended_opp(dev, &rate, 0);
	अगर (IS_ERR(opp)) अणु
		dev_err(dev, "failed to find dev_pm_opp\n");
		ret = PTR_ERR(opp);
		जाओ err_opp;
	पूर्ण
	bus->curr_freq = dev_pm_opp_get_freq(opp);
	dev_pm_opp_put(opp);

	वापस 0;

err_opp:
	dev_pm_opp_of_हटाओ_table(dev);
err_clk:
	clk_disable_unprepare(bus->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_bus_profile_init(काष्ठा exynos_bus *bus,
				   काष्ठा devfreq_dev_profile *profile)
अणु
	काष्ठा device *dev = bus->dev;
	काष्ठा devfreq_simple_ondemand_data *ondemand_data;
	पूर्णांक ret;

	/* Initialize the काष्ठा profile and governor data क्रम parent device */
	profile->polling_ms = 50;
	profile->target = exynos_bus_target;
	profile->get_dev_status = exynos_bus_get_dev_status;
	profile->निकास = exynos_bus_निकास;

	ondemand_data = devm_kzalloc(dev, माप(*ondemand_data), GFP_KERNEL);
	अगर (!ondemand_data)
		वापस -ENOMEM;

	ondemand_data->upthreshold = 40;
	ondemand_data->करोwndअगरferential = 5;

	/* Add devfreq device to monitor and handle the exynos bus */
	bus->devfreq = devm_devfreq_add_device(dev, profile,
						DEVFREQ_GOV_SIMPLE_ONDEMAND,
						ondemand_data);
	अगर (IS_ERR(bus->devfreq)) अणु
		dev_err(dev, "failed to add devfreq device\n");
		वापस PTR_ERR(bus->devfreq);
	पूर्ण

	/* Register opp_notअगरier to catch the change of OPP  */
	ret = devm_devfreq_रेजिस्टर_opp_notअगरier(dev, bus->devfreq);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register opp notifier\n");
		वापस ret;
	पूर्ण

	/*
	 * Enable devfreq-event to get raw data which is used to determine
	 * current bus load.
	 */
	ret = exynos_bus_enable_edev(bus);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable devfreq-event devices\n");
		वापस ret;
	पूर्ण

	ret = exynos_bus_set_event(bus);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set event to devfreq-event devices\n");
		जाओ err_edev;
	पूर्ण

	वापस 0;

err_edev:
	अगर (exynos_bus_disable_edev(bus))
		dev_warn(dev, "failed to disable the devfreq-event devices\n");

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_bus_profile_init_passive(काष्ठा exynos_bus *bus,
					   काष्ठा devfreq_dev_profile *profile)
अणु
	काष्ठा device *dev = bus->dev;
	काष्ठा devfreq_passive_data *passive_data;
	काष्ठा devfreq *parent_devfreq;

	/* Initialize the काष्ठा profile and governor data क्रम passive device */
	profile->target = exynos_bus_target;
	profile->निकास = exynos_bus_passive_निकास;

	/* Get the instance of parent devfreq device */
	parent_devfreq = devfreq_get_devfreq_by_phandle(dev, "devfreq", 0);
	अगर (IS_ERR(parent_devfreq))
		वापस -EPROBE_DEFER;

	passive_data = devm_kzalloc(dev, माप(*passive_data), GFP_KERNEL);
	अगर (!passive_data)
		वापस -ENOMEM;

	passive_data->parent = parent_devfreq;

	/* Add devfreq device क्रम exynos bus with passive governor */
	bus->devfreq = devm_devfreq_add_device(dev, profile, DEVFREQ_GOV_PASSIVE,
						passive_data);
	अगर (IS_ERR(bus->devfreq)) अणु
		dev_err(dev,
			"failed to add devfreq dev with passive governor\n");
		वापस PTR_ERR(bus->devfreq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_bus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node, *node;
	काष्ठा devfreq_dev_profile *profile;
	काष्ठा exynos_bus *bus;
	पूर्णांक ret, max_state;
	अचिन्हित दीर्घ min_freq, max_freq;
	bool passive = false;

	अगर (!np) अणु
		dev_err(dev, "failed to find devicetree node\n");
		वापस -EINVAL;
	पूर्ण

	bus = devm_kzalloc(&pdev->dev, माप(*bus), GFP_KERNEL);
	अगर (!bus)
		वापस -ENOMEM;
	mutex_init(&bus->lock);
	bus->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, bus);

	profile = devm_kzalloc(dev, माप(*profile), GFP_KERNEL);
	अगर (!profile)
		वापस -ENOMEM;

	node = of_parse_phandle(dev->of_node, "devfreq", 0);
	अगर (node) अणु
		of_node_put(node);
		passive = true;
	पूर्ण अन्यथा अणु
		ret = exynos_bus_parent_parse_of(np, bus);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Parse the device-tree to get the resource inक्रमmation */
	ret = exynos_bus_parse_of(np, bus);
	अगर (ret < 0)
		जाओ err_reg;

	अगर (passive)
		ret = exynos_bus_profile_init_passive(bus, profile);
	अन्यथा
		ret = exynos_bus_profile_init(bus, profile);

	अगर (ret < 0)
		जाओ err;

	/* Create child platक्रमm device क्रम the पूर्णांकerconnect provider */
	अगर (of_get_property(dev->of_node, "#interconnect-cells", शून्य)) अणु
		bus->icc_pdev = platक्रमm_device_रेजिस्टर_data(
						dev, "exynos-generic-icc",
						PLATFORM_DEVID_AUTO, शून्य, 0);

		अगर (IS_ERR(bus->icc_pdev)) अणु
			ret = PTR_ERR(bus->icc_pdev);
			जाओ err;
		पूर्ण
	पूर्ण

	max_state = bus->devfreq->profile->max_state;
	min_freq = (bus->devfreq->profile->freq_table[0] / 1000);
	max_freq = (bus->devfreq->profile->freq_table[max_state - 1] / 1000);
	pr_info("exynos-bus: new bus device registered: %s (%6ld KHz ~ %6ld KHz)\n",
			dev_name(dev), min_freq, max_freq);

	वापस 0;

err:
	dev_pm_opp_of_हटाओ_table(dev);
	clk_disable_unprepare(bus->clk);
err_reg:
	dev_pm_opp_put_regulators(bus->opp_table);
	bus->opp_table = शून्य;

	वापस ret;
पूर्ण

अटल व्योम exynos_bus_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_bus *bus = dev_get_drvdata(&pdev->dev);

	devfreq_suspend_device(bus->devfreq);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक exynos_bus_resume(काष्ठा device *dev)
अणु
	काष्ठा exynos_bus *bus = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = exynos_bus_enable_edev(bus);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable the devfreq-event devices\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_bus_suspend(काष्ठा device *dev)
अणु
	काष्ठा exynos_bus *bus = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = exynos_bus_disable_edev(bus);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to disable the devfreq-event devices\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops exynos_bus_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(exynos_bus_suspend, exynos_bus_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_bus_of_match[] = अणु
	अणु .compatible = "samsung,exynos-bus", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_bus_of_match);

अटल काष्ठा platक्रमm_driver exynos_bus_platdrv = अणु
	.probe		= exynos_bus_probe,
	.shutकरोwn	= exynos_bus_shutकरोwn,
	.driver = अणु
		.name	= "exynos-bus",
		.pm	= &exynos_bus_pm,
		.of_match_table = of_match_ptr(exynos_bus_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(exynos_bus_platdrv);

MODULE_DESCRIPTION("Generic Exynos Bus frequency driver");
MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>");
MODULE_LICENSE("GPL v2");
