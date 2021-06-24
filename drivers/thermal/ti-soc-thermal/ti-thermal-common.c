<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP thermal driver पूर्णांकerface
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
 * Contact:
 *   Eduarकरो Valentin <eduarकरो.valentin@ti.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/thermal.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpu_cooling.h>
#समावेश <linux/of.h>

#समावेश "ti-thermal.h"
#समावेश "ti-bandgap.h"

/* common data काष्ठाures */
काष्ठा ti_thermal_data अणु
	काष्ठा cpufreq_policy *policy;
	काष्ठा thermal_zone_device *ti_thermal;
	काष्ठा thermal_zone_device *pcb_tz;
	काष्ठा thermal_cooling_device *cool_dev;
	काष्ठा ti_bandgap *bgp;
	क्रमागत thermal_device_mode mode;
	काष्ठा work_काष्ठा thermal_wq;
	पूर्णांक sensor_id;
	bool our_zone;
पूर्ण;

अटल व्योम ti_thermal_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ti_thermal_data *data = container_of(work,
					काष्ठा ti_thermal_data, thermal_wq);

	thermal_zone_device_update(data->ti_thermal, THERMAL_EVENT_UNSPECIFIED);

	dev_dbg(&data->ti_thermal->device, "updated thermal zone %s\n",
		data->ti_thermal->type);
पूर्ण

/**
 * ti_thermal_hotspot_temperature - वापसs sensor extrapolated temperature
 * @t:	omap sensor temperature
 * @s:	omap sensor slope value
 * @c:	omap sensor स्थिर value
 */
अटल अंतरभूत पूर्णांक ti_thermal_hotspot_temperature(पूर्णांक t, पूर्णांक s, पूर्णांक c)
अणु
	पूर्णांक delta = t * s / 1000 + c;

	अगर (delta < 0)
		delta = 0;

	वापस t + delta;
पूर्ण

/* thermal zone ops */
/* Get temperature callback function क्रम thermal zone */
अटल अंतरभूत पूर्णांक __ti_thermal_get_temp(व्योम *devdata, पूर्णांक *temp)
अणु
	काष्ठा thermal_zone_device *pcb_tz = शून्य;
	काष्ठा ti_thermal_data *data = devdata;
	काष्ठा ti_bandgap *bgp;
	स्थिर काष्ठा ti_temp_sensor *s;
	पूर्णांक ret, पंचांगp, slope, स्थिरant;
	पूर्णांक pcb_temp;

	अगर (!data)
		वापस 0;

	bgp = data->bgp;
	s = &bgp->conf->sensors[data->sensor_id];

	ret = ti_bandgap_पढ़ो_temperature(bgp, data->sensor_id, &पंचांगp);
	अगर (ret)
		वापस ret;

	/* Default स्थिरants */
	slope = thermal_zone_get_slope(data->ti_thermal);
	स्थिरant = thermal_zone_get_offset(data->ti_thermal);

	pcb_tz = data->pcb_tz;
	/* In हाल pcb zone is available, use the extrapolation rule with it */
	अगर (!IS_ERR(pcb_tz)) अणु
		ret = thermal_zone_get_temp(pcb_tz, &pcb_temp);
		अगर (!ret) अणु
			पंचांगp -= pcb_temp; /* got a valid PCB temp */
			slope = s->slope_pcb;
			स्थिरant = s->स्थिरant_pcb;
		पूर्ण अन्यथा अणु
			dev_err(bgp->dev,
				"Failed to read PCB state. Using defaults\n");
			ret = 0;
		पूर्ण
	पूर्ण
	*temp = ti_thermal_hotspot_temperature(पंचांगp, slope, स्थिरant);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ti_thermal_get_temp(काष्ठा thermal_zone_device *thermal,
				      पूर्णांक *temp)
अणु
	काष्ठा ti_thermal_data *data = thermal->devdata;

	वापस __ti_thermal_get_temp(data, temp);
पूर्ण

अटल पूर्णांक __ti_thermal_get_trend(व्योम *p, पूर्णांक trip, क्रमागत thermal_trend *trend)
अणु
	काष्ठा ti_thermal_data *data = p;
	काष्ठा ti_bandgap *bgp;
	पूर्णांक id, tr, ret = 0;

	bgp = data->bgp;
	id = data->sensor_id;

	ret = ti_bandgap_get_trend(bgp, id, &tr);
	अगर (ret)
		वापस ret;

	अगर (tr > 0)
		*trend = THERMAL_TREND_RAISING;
	अन्यथा अगर (tr < 0)
		*trend = THERMAL_TREND_DROPPING;
	अन्यथा
		*trend = THERMAL_TREND_STABLE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops ti_of_thermal_ops = अणु
	.get_temp = __ti_thermal_get_temp,
	.get_trend = __ti_thermal_get_trend,
पूर्ण;

अटल काष्ठा ti_thermal_data
*ti_thermal_build_data(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	काष्ठा ti_thermal_data *data;

	data = devm_kzalloc(bgp->dev, माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		dev_err(bgp->dev, "kzalloc fail\n");
		वापस शून्य;
	पूर्ण
	data->sensor_id = id;
	data->bgp = bgp;
	data->mode = THERMAL_DEVICE_ENABLED;
	/* pcb_tz will be either valid or PTR_ERR() */
	data->pcb_tz = thermal_zone_get_zone_by_name("pcb");
	INIT_WORK(&data->thermal_wq, ti_thermal_work);

	वापस data;
पूर्ण

पूर्णांक ti_thermal_expose_sensor(काष्ठा ti_bandgap *bgp, पूर्णांक id,
			     अक्षर *करोमुख्य)
अणु
	काष्ठा ti_thermal_data *data;
	पूर्णांक पूर्णांकerval;

	data = ti_bandgap_get_sensor_data(bgp, id);

	अगर (IS_ERR_OR_शून्य(data))
		data = ti_thermal_build_data(bgp, id);

	अगर (!data)
		वापस -EINVAL;

	/* in हाल this is specअगरied by DT */
	data->ti_thermal = devm_thermal_zone_of_sensor_रेजिस्टर(bgp->dev, id,
					data, &ti_of_thermal_ops);
	अगर (IS_ERR(data->ti_thermal)) अणु
		dev_err(bgp->dev, "thermal zone device is NULL\n");
		वापस PTR_ERR(data->ti_thermal);
	पूर्ण

	पूर्णांकerval = jअगरfies_to_msecs(data->ti_thermal->polling_delay_jअगरfies);

	ti_bandgap_set_sensor_data(bgp, id, data);
	ti_bandgap_ग_लिखो_update_पूर्णांकerval(bgp, data->sensor_id, पूर्णांकerval);

	वापस 0;
पूर्ण

पूर्णांक ti_thermal_हटाओ_sensor(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	काष्ठा ti_thermal_data *data;

	data = ti_bandgap_get_sensor_data(bgp, id);

	अगर (!IS_ERR_OR_शून्य(data) && data->ti_thermal) अणु
		अगर (data->our_zone)
			thermal_zone_device_unरेजिस्टर(data->ti_thermal);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ti_thermal_report_sensor_temperature(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	काष्ठा ti_thermal_data *data;

	data = ti_bandgap_get_sensor_data(bgp, id);

	schedule_work(&data->thermal_wq);

	वापस 0;
पूर्ण

पूर्णांक ti_thermal_रेजिस्टर_cpu_cooling(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	काष्ठा ti_thermal_data *data;
	काष्ठा device_node *np = bgp->dev->of_node;

	/*
	 * We are assuming here that अगर one deploys the zone
	 * using DT, then it must be aware that the cooling device
	 * loading has to happen via cpufreq driver.
	 */
	अगर (of_find_property(np, "#thermal-sensor-cells", शून्य))
		वापस 0;

	data = ti_bandgap_get_sensor_data(bgp, id);
	अगर (!data || IS_ERR(data))
		data = ti_thermal_build_data(bgp, id);

	अगर (!data)
		वापस -EINVAL;

	data->policy = cpufreq_cpu_get(0);
	अगर (!data->policy) अणु
		pr_debug("%s: CPUFreq policy not found\n", __func__);
		वापस -EPROBE_DEFER;
	पूर्ण

	/* Register cooling device */
	data->cool_dev = cpufreq_cooling_रेजिस्टर(data->policy);
	अगर (IS_ERR(data->cool_dev)) अणु
		पूर्णांक ret = PTR_ERR(data->cool_dev);
		dev_err(bgp->dev, "Failed to register cpu cooling device %d\n",
			ret);
		cpufreq_cpu_put(data->policy);

		वापस ret;
	पूर्ण
	ti_bandgap_set_sensor_data(bgp, id, data);

	वापस 0;
पूर्ण

पूर्णांक ti_thermal_unरेजिस्टर_cpu_cooling(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	काष्ठा ti_thermal_data *data;

	data = ti_bandgap_get_sensor_data(bgp, id);

	अगर (!IS_ERR_OR_शून्य(data)) अणु
		cpufreq_cooling_unरेजिस्टर(data->cool_dev);
		अगर (data->policy)
			cpufreq_cpu_put(data->policy);
	पूर्ण

	वापस 0;
पूर्ण
