<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  of-thermal.c - Generic Thermal Management device tree support.
 *
 *  Copyright (C) 2013 Texas Instruments
 *  Copyright (C) 2013 Eduarकरो Valentin <eduarकरो.valentin@ti.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>

#समावेश "thermal_core.h"

/***   Private data काष्ठाures to represent thermal device tree data ***/

/**
 * काष्ठा __thermal_cooling_bind_param - a cooling device क्रम a trip poपूर्णांक
 * @cooling_device: a poपूर्णांकer to identअगरy the referred cooling device
 * @min: minimum cooling state used at this trip poपूर्णांक
 * @max: maximum cooling state used at this trip poपूर्णांक
 */

काष्ठा __thermal_cooling_bind_param अणु
	काष्ठा device_node *cooling_device;
	अचिन्हित दीर्घ min;
	अचिन्हित दीर्घ max;
पूर्ण;

/**
 * काष्ठा __thermal_bind_param - a match between trip and cooling device
 * @tcbp: a poपूर्णांकer to an array of cooling devices
 * @count: number of elements in array
 * @trip_id: the trip poपूर्णांक index
 * @usage: the percentage (from 0 to 100) of cooling contribution
 */

काष्ठा __thermal_bind_params अणु
	काष्ठा __thermal_cooling_bind_param *tcbp;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक trip_id;
	अचिन्हित पूर्णांक usage;
पूर्ण;

/**
 * काष्ठा __thermal_zone - पूर्णांकernal representation of a thermal zone
 * @passive_delay: polling पूर्णांकerval जबतक passive cooling is activated
 * @polling_delay: zone polling पूर्णांकerval
 * @slope: slope of the temperature adjusपंचांगent curve
 * @offset: offset of the temperature adjusपंचांगent curve
 * @ntrips: number of trip poपूर्णांकs
 * @trips: an array of trip poपूर्णांकs (0..ntrips - 1)
 * @num_tbps: number of thermal bind params
 * @tbps: an array of thermal bind params (0..num_tbps - 1)
 * @sensor_data: sensor निजी data used जबतक पढ़ोing temperature and trend
 * @ops: set of callbacks to handle the thermal zone based on DT
 */

काष्ठा __thermal_zone अणु
	पूर्णांक passive_delay;
	पूर्णांक polling_delay;
	पूर्णांक slope;
	पूर्णांक offset;

	/* trip data */
	पूर्णांक ntrips;
	काष्ठा thermal_trip *trips;

	/* cooling binding data */
	पूर्णांक num_tbps;
	काष्ठा __thermal_bind_params *tbps;

	/* sensor पूर्णांकerface */
	व्योम *sensor_data;
	स्थिर काष्ठा thermal_zone_of_device_ops *ops;
पूर्ण;

/***   DT thermal zone device callbacks   ***/

अटल पूर्णांक of_thermal_get_temp(काष्ठा thermal_zone_device *tz,
			       पूर्णांक *temp)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	अगर (!data->ops->get_temp)
		वापस -EINVAL;

	वापस data->ops->get_temp(data->sensor_data, temp);
पूर्ण

अटल पूर्णांक of_thermal_set_trips(काष्ठा thermal_zone_device *tz,
				पूर्णांक low, पूर्णांक high)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	अगर (!data->ops || !data->ops->set_trips)
		वापस -EINVAL;

	वापस data->ops->set_trips(data->sensor_data, low, high);
पूर्ण

/**
 * of_thermal_get_ntrips - function to export number of available trip
 *			   poपूर्णांकs.
 * @tz: poपूर्णांकer to a thermal zone
 *
 * This function is a globally visible wrapper to get number of trip poपूर्णांकs
 * stored in the local काष्ठा __thermal_zone
 *
 * Return: number of available trip poपूर्णांकs, -ENODEV when data not available
 */
पूर्णांक of_thermal_get_ntrips(काष्ठा thermal_zone_device *tz)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	अगर (!data || IS_ERR(data))
		वापस -ENODEV;

	वापस data->ntrips;
पूर्ण
EXPORT_SYMBOL_GPL(of_thermal_get_ntrips);

/**
 * of_thermal_is_trip_valid - function to check अगर trip poपूर्णांक is valid
 *
 * @tz:	poपूर्णांकer to a thermal zone
 * @trip:	trip poपूर्णांक to evaluate
 *
 * This function is responsible क्रम checking अगर passed trip poपूर्णांक is valid
 *
 * Return: true अगर trip poपूर्णांक is valid, false otherwise
 */
bool of_thermal_is_trip_valid(काष्ठा thermal_zone_device *tz, पूर्णांक trip)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	अगर (!data || trip >= data->ntrips || trip < 0)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(of_thermal_is_trip_valid);

/**
 * of_thermal_get_trip_poपूर्णांकs - function to get access to a globally exported
 *				trip poपूर्णांकs
 *
 * @tz:	poपूर्णांकer to a thermal zone
 *
 * This function provides a poपूर्णांकer to trip poपूर्णांकs table
 *
 * Return: poपूर्णांकer to trip poपूर्णांकs table, शून्य otherwise
 */
स्थिर काष्ठा thermal_trip *
of_thermal_get_trip_poपूर्णांकs(काष्ठा thermal_zone_device *tz)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	अगर (!data)
		वापस शून्य;

	वापस data->trips;
पूर्ण
EXPORT_SYMBOL_GPL(of_thermal_get_trip_poपूर्णांकs);

/**
 * of_thermal_set_emul_temp - function to set emulated temperature
 *
 * @tz:	poपूर्णांकer to a thermal zone
 * @temp:	temperature to set
 *
 * This function gives the ability to set emulated value of temperature,
 * which is handy क्रम debugging
 *
 * Return: zero on success, error code otherwise
 */
अटल पूर्णांक of_thermal_set_emul_temp(काष्ठा thermal_zone_device *tz,
				    पूर्णांक temp)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	वापस data->ops->set_emul_temp(data->sensor_data, temp);
पूर्ण

अटल पूर्णांक of_thermal_get_trend(काष्ठा thermal_zone_device *tz, पूर्णांक trip,
				क्रमागत thermal_trend *trend)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	अगर (!data->ops->get_trend)
		वापस -EINVAL;

	वापस data->ops->get_trend(data->sensor_data, trip, trend);
पूर्ण

अटल पूर्णांक of_thermal_bind(काष्ठा thermal_zone_device *thermal,
			   काष्ठा thermal_cooling_device *cdev)
अणु
	काष्ठा __thermal_zone *data = thermal->devdata;
	काष्ठा __thermal_bind_params *tbp;
	काष्ठा __thermal_cooling_bind_param *tcbp;
	पूर्णांक i, j;

	अगर (!data || IS_ERR(data))
		वापस -ENODEV;

	/* find where to bind */
	क्रम (i = 0; i < data->num_tbps; i++) अणु
		tbp = data->tbps + i;

		क्रम (j = 0; j < tbp->count; j++) अणु
			tcbp = tbp->tcbp + j;

			अगर (tcbp->cooling_device == cdev->np) अणु
				पूर्णांक ret;

				ret = thermal_zone_bind_cooling_device(thermal,
						tbp->trip_id, cdev,
						tcbp->max,
						tcbp->min,
						tbp->usage);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक of_thermal_unbind(काष्ठा thermal_zone_device *thermal,
			     काष्ठा thermal_cooling_device *cdev)
अणु
	काष्ठा __thermal_zone *data = thermal->devdata;
	काष्ठा __thermal_bind_params *tbp;
	काष्ठा __thermal_cooling_bind_param *tcbp;
	पूर्णांक i, j;

	अगर (!data || IS_ERR(data))
		वापस -ENODEV;

	/* find where to unbind */
	क्रम (i = 0; i < data->num_tbps; i++) अणु
		tbp = data->tbps + i;

		क्रम (j = 0; j < tbp->count; j++) अणु
			tcbp = tbp->tcbp + j;

			अगर (tcbp->cooling_device == cdev->np) अणु
				पूर्णांक ret;

				ret = thermal_zone_unbind_cooling_device(thermal,
							tbp->trip_id, cdev);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक of_thermal_get_trip_type(काष्ठा thermal_zone_device *tz, पूर्णांक trip,
				    क्रमागत thermal_trip_type *type)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	अगर (trip >= data->ntrips || trip < 0)
		वापस -गलत_तर्क;

	*type = data->trips[trip].type;

	वापस 0;
पूर्ण

अटल पूर्णांक of_thermal_get_trip_temp(काष्ठा thermal_zone_device *tz, पूर्णांक trip,
				    पूर्णांक *temp)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	अगर (trip >= data->ntrips || trip < 0)
		वापस -गलत_तर्क;

	*temp = data->trips[trip].temperature;

	वापस 0;
पूर्ण

अटल पूर्णांक of_thermal_set_trip_temp(काष्ठा thermal_zone_device *tz, पूर्णांक trip,
				    पूर्णांक temp)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	अगर (trip >= data->ntrips || trip < 0)
		वापस -गलत_तर्क;

	अगर (data->ops->set_trip_temp) अणु
		पूर्णांक ret;

		ret = data->ops->set_trip_temp(data->sensor_data, trip, temp);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* thermal framework should take care of data->mask & (1 << trip) */
	data->trips[trip].temperature = temp;

	वापस 0;
पूर्ण

अटल पूर्णांक of_thermal_get_trip_hyst(काष्ठा thermal_zone_device *tz, पूर्णांक trip,
				    पूर्णांक *hyst)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	अगर (trip >= data->ntrips || trip < 0)
		वापस -गलत_तर्क;

	*hyst = data->trips[trip].hysteresis;

	वापस 0;
पूर्ण

अटल पूर्णांक of_thermal_set_trip_hyst(काष्ठा thermal_zone_device *tz, पूर्णांक trip,
				    पूर्णांक hyst)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;

	अगर (trip >= data->ntrips || trip < 0)
		वापस -गलत_तर्क;

	/* thermal framework should take care of data->mask & (1 << trip) */
	data->trips[trip].hysteresis = hyst;

	वापस 0;
पूर्ण

अटल पूर्णांक of_thermal_get_crit_temp(काष्ठा thermal_zone_device *tz,
				    पूर्णांक *temp)
अणु
	काष्ठा __thermal_zone *data = tz->devdata;
	पूर्णांक i;

	क्रम (i = 0; i < data->ntrips; i++)
		अगर (data->trips[i].type == THERMAL_TRIP_CRITICAL) अणु
			*temp = data->trips[i].temperature;
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा thermal_zone_device_ops of_thermal_ops = अणु
	.get_trip_type = of_thermal_get_trip_type,
	.get_trip_temp = of_thermal_get_trip_temp,
	.set_trip_temp = of_thermal_set_trip_temp,
	.get_trip_hyst = of_thermal_get_trip_hyst,
	.set_trip_hyst = of_thermal_set_trip_hyst,
	.get_crit_temp = of_thermal_get_crit_temp,

	.bind = of_thermal_bind,
	.unbind = of_thermal_unbind,
पूर्ण;

/***   sensor API   ***/

अटल काष्ठा thermal_zone_device *
thermal_zone_of_add_sensor(काष्ठा device_node *zone,
			   काष्ठा device_node *sensor, व्योम *data,
			   स्थिर काष्ठा thermal_zone_of_device_ops *ops)
अणु
	काष्ठा thermal_zone_device *tzd;
	काष्ठा __thermal_zone *tz;

	tzd = thermal_zone_get_zone_by_name(zone->name);
	अगर (IS_ERR(tzd))
		वापस ERR_PTR(-EPROBE_DEFER);

	tz = tzd->devdata;

	अगर (!ops)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&tzd->lock);
	tz->ops = ops;
	tz->sensor_data = data;

	tzd->ops->get_temp = of_thermal_get_temp;
	tzd->ops->get_trend = of_thermal_get_trend;

	/*
	 * The thermal zone core will calculate the winकरोw अगर they have set the
	 * optional set_trips poपूर्णांकer.
	 */
	अगर (ops->set_trips)
		tzd->ops->set_trips = of_thermal_set_trips;

	अगर (ops->set_emul_temp)
		tzd->ops->set_emul_temp = of_thermal_set_emul_temp;

	mutex_unlock(&tzd->lock);

	वापस tzd;
पूर्ण

/**
 * thermal_zone_of_get_sensor_id - get sensor ID from a DT thermal zone
 * @tz_np: a valid thermal zone device node.
 * @sensor_np: a sensor node of a valid sensor device.
 * @id: the sensor ID वापसed अगर success.
 *
 * This function will get sensor ID from a given thermal zone node and
 * the sensor node must match the temperature provider @sensor_np.
 *
 * Return: 0 on success, proper error code otherwise.
 */

पूर्णांक thermal_zone_of_get_sensor_id(काष्ठा device_node *tz_np,
				  काष्ठा device_node *sensor_np,
				  u32 *id)
अणु
	काष्ठा of_phandle_args sensor_specs;
	पूर्णांक ret;

	ret = of_parse_phandle_with_args(tz_np,
					 "thermal-sensors",
					 "#thermal-sensor-cells",
					 0,
					 &sensor_specs);
	अगर (ret)
		वापस ret;

	अगर (sensor_specs.np != sensor_np) अणु
		of_node_put(sensor_specs.np);
		वापस -ENODEV;
	पूर्ण

	अगर (sensor_specs.args_count > 1)
		pr_warn("%pOFn: too many cells in sensor specifier %d\n",
		     sensor_specs.np, sensor_specs.args_count);

	*id = sensor_specs.args_count ? sensor_specs.args[0] : 0;

	of_node_put(sensor_specs.np);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_of_get_sensor_id);

/**
 * thermal_zone_of_sensor_रेजिस्टर - रेजिस्टरs a sensor to a DT thermal zone
 * @dev: a valid काष्ठा device poपूर्णांकer of a sensor device. Must contain
 *       a valid .of_node, क्रम the sensor node.
 * @sensor_id: a sensor identअगरier, in हाल the sensor IP has more
 *             than one sensors
 * @data: a निजी poपूर्णांकer (owned by the caller) that will be passed
 *        back, when a temperature पढ़ोing is needed.
 * @ops: काष्ठा thermal_zone_of_device_ops *. Must contain at least .get_temp.
 *
 * This function will search the list of thermal zones described in device
 * tree and look क्रम the zone that refer to the sensor device poपूर्णांकed by
 * @dev->of_node as temperature providers. For the zone poपूर्णांकing to the
 * sensor node, the sensor will be added to the DT thermal zone device.
 *
 * The thermal zone temperature is provided by the @get_temp function
 * poपूर्णांकer. When called, it will have the निजी poपूर्णांकer @data back.
 *
 * The thermal zone temperature trend is provided by the @get_trend function
 * poपूर्णांकer. When called, it will have the निजी poपूर्णांकer @data back.
 *
 * TODO:
 * 01 - This function must enqueue the new sensor instead of using
 * it as the only source of temperature values.
 *
 * 02 - There must be a way to match the sensor with all thermal zones
 * that refer to it.
 *
 * Return: On success वापसs a valid काष्ठा thermal_zone_device,
 * otherwise, it वापसs a corresponding ERR_PTR(). Caller must
 * check the वापस value with help of IS_ERR() helper.
 */
काष्ठा thermal_zone_device *
thermal_zone_of_sensor_रेजिस्टर(काष्ठा device *dev, पूर्णांक sensor_id, व्योम *data,
				स्थिर काष्ठा thermal_zone_of_device_ops *ops)
अणु
	काष्ठा device_node *np, *child, *sensor_np;
	काष्ठा thermal_zone_device *tzd = ERR_PTR(-ENODEV);

	np = of_find_node_by_name(शून्य, "thermal-zones");
	अगर (!np)
		वापस ERR_PTR(-ENODEV);

	अगर (!dev || !dev->of_node) अणु
		of_node_put(np);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	sensor_np = of_node_get(dev->of_node);

	क्रम_each_available_child_of_node(np, child) अणु
		पूर्णांक ret, id;

		/* For now, thermal framework supports only 1 sensor per zone */
		ret = thermal_zone_of_get_sensor_id(child, sensor_np, &id);
		अगर (ret)
			जारी;

		अगर (id == sensor_id) अणु
			tzd = thermal_zone_of_add_sensor(child, sensor_np,
							 data, ops);
			अगर (!IS_ERR(tzd))
				thermal_zone_device_enable(tzd);

			of_node_put(child);
			जाओ निकास;
		पूर्ण
	पूर्ण
निकास:
	of_node_put(sensor_np);
	of_node_put(np);

	वापस tzd;
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_of_sensor_रेजिस्टर);

/**
 * thermal_zone_of_sensor_unरेजिस्टर - unरेजिस्टरs a sensor from a DT thermal zone
 * @dev: a valid काष्ठा device poपूर्णांकer of a sensor device. Must contain
 *       a valid .of_node, क्रम the sensor node.
 * @tzd: a poपूर्णांकer to काष्ठा thermal_zone_device where the sensor is रेजिस्टरed.
 *
 * This function हटाओs the sensor callbacks and निजी data from the
 * thermal zone device रेजिस्टरed with thermal_zone_of_sensor_रेजिस्टर()
 * API. It will also silent the zone by हटाओ the .get_temp() and .get_trend()
 * thermal zone device callbacks.
 *
 * TODO: When the support to several sensors per zone is added, this
 * function must search the sensor list based on @dev parameter.
 *
 */
व्योम thermal_zone_of_sensor_unरेजिस्टर(काष्ठा device *dev,
				       काष्ठा thermal_zone_device *tzd)
अणु
	काष्ठा __thermal_zone *tz;

	अगर (!dev || !tzd || !tzd->devdata)
		वापस;

	tz = tzd->devdata;

	/* no __thermal_zone, nothing to be करोne */
	अगर (!tz)
		वापस;

	mutex_lock(&tzd->lock);
	tzd->ops->get_temp = शून्य;
	tzd->ops->get_trend = शून्य;
	tzd->ops->set_emul_temp = शून्य;

	tz->ops = शून्य;
	tz->sensor_data = शून्य;
	mutex_unlock(&tzd->lock);
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_of_sensor_unरेजिस्टर);

अटल व्योम devm_thermal_zone_of_sensor_release(काष्ठा device *dev, व्योम *res)
अणु
	thermal_zone_of_sensor_unरेजिस्टर(dev,
					  *(काष्ठा thermal_zone_device **)res);
पूर्ण

अटल पूर्णांक devm_thermal_zone_of_sensor_match(काष्ठा device *dev, व्योम *res,
					     व्योम *data)
अणु
	काष्ठा thermal_zone_device **r = res;

	अगर (WARN_ON(!r || !*r))
		वापस 0;

	वापस *r == data;
पूर्ण

/**
 * devm_thermal_zone_of_sensor_रेजिस्टर - Resource managed version of
 *				thermal_zone_of_sensor_रेजिस्टर()
 * @dev: a valid काष्ठा device poपूर्णांकer of a sensor device. Must contain
 *       a valid .of_node, क्रम the sensor node.
 * @sensor_id: a sensor identअगरier, in हाल the sensor IP has more
 *	       than one sensors
 * @data: a निजी poपूर्णांकer (owned by the caller) that will be passed
 *	  back, when a temperature पढ़ोing is needed.
 * @ops: काष्ठा thermal_zone_of_device_ops *. Must contain at least .get_temp.
 *
 * Refer thermal_zone_of_sensor_रेजिस्टर() क्रम more details.
 *
 * Return: On success वापसs a valid काष्ठा thermal_zone_device,
 * otherwise, it वापसs a corresponding ERR_PTR(). Caller must
 * check the वापस value with help of IS_ERR() helper.
 * Registered thermal_zone_device device will स्वतःmatically be
 * released when device is unbounded.
 */
काष्ठा thermal_zone_device *devm_thermal_zone_of_sensor_रेजिस्टर(
	काष्ठा device *dev, पूर्णांक sensor_id,
	व्योम *data, स्थिर काष्ठा thermal_zone_of_device_ops *ops)
अणु
	काष्ठा thermal_zone_device **ptr, *tzd;

	ptr = devres_alloc(devm_thermal_zone_of_sensor_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	tzd = thermal_zone_of_sensor_रेजिस्टर(dev, sensor_id, data, ops);
	अगर (IS_ERR(tzd)) अणु
		devres_मुक्त(ptr);
		वापस tzd;
	पूर्ण

	*ptr = tzd;
	devres_add(dev, ptr);

	वापस tzd;
पूर्ण
EXPORT_SYMBOL_GPL(devm_thermal_zone_of_sensor_रेजिस्टर);

/**
 * devm_thermal_zone_of_sensor_unरेजिस्टर - Resource managed version of
 *				thermal_zone_of_sensor_unरेजिस्टर().
 * @dev: Device क्रम which which resource was allocated.
 * @tzd: a poपूर्णांकer to काष्ठा thermal_zone_device where the sensor is रेजिस्टरed.
 *
 * This function हटाओs the sensor callbacks and निजी data from the
 * thermal zone device रेजिस्टरed with devm_thermal_zone_of_sensor_रेजिस्टर()
 * API. It will also silent the zone by हटाओ the .get_temp() and .get_trend()
 * thermal zone device callbacks.
 * Normally this function will not need to be called and the resource
 * management code will ensure that the resource is मुक्तd.
 */
व्योम devm_thermal_zone_of_sensor_unरेजिस्टर(काष्ठा device *dev,
					    काष्ठा thermal_zone_device *tzd)
अणु
	WARN_ON(devres_release(dev, devm_thermal_zone_of_sensor_release,
			       devm_thermal_zone_of_sensor_match, tzd));
पूर्ण
EXPORT_SYMBOL_GPL(devm_thermal_zone_of_sensor_unरेजिस्टर);

/***   functions parsing device tree nodes   ***/

/**
 * thermal_of_populate_bind_params - parse and fill cooling map data
 * @np: DT node containing a cooling-map node
 * @__tbp: data काष्ठाure to be filled with cooling map info
 * @trips: array of thermal zone trip poपूर्णांकs
 * @ntrips: number of trip poपूर्णांकs inside trips.
 *
 * This function parses a cooling-map type of node represented by
 * @np parameter and fills the पढ़ो data पूर्णांकo @__tbp data काष्ठाure.
 * It needs the alपढ़ोy parsed array of trip poपूर्णांकs of the thermal zone
 * in consideration.
 *
 * Return: 0 on success, proper error code otherwise
 */
अटल पूर्णांक thermal_of_populate_bind_params(काष्ठा device_node *np,
					   काष्ठा __thermal_bind_params *__tbp,
					   काष्ठा thermal_trip *trips,
					   पूर्णांक ntrips)
अणु
	काष्ठा of_phandle_args cooling_spec;
	काष्ठा __thermal_cooling_bind_param *__tcbp;
	काष्ठा device_node *trip;
	पूर्णांक ret, i, count;
	u32 prop;

	/* Default weight. Usage is optional */
	__tbp->usage = THERMAL_WEIGHT_DEFAULT;
	ret = of_property_पढ़ो_u32(np, "contribution", &prop);
	अगर (ret == 0)
		__tbp->usage = prop;

	trip = of_parse_phandle(np, "trip", 0);
	अगर (!trip) अणु
		pr_err("missing trip property\n");
		वापस -ENODEV;
	पूर्ण

	/* match using device_node */
	क्रम (i = 0; i < ntrips; i++)
		अगर (trip == trips[i].np) अणु
			__tbp->trip_id = i;
			अवरोध;
		पूर्ण

	अगर (i == ntrips) अणु
		ret = -ENODEV;
		जाओ end;
	पूर्ण

	count = of_count_phandle_with_args(np, "cooling-device",
					   "#cooling-cells");
	अगर (count <= 0) अणु
		pr_err("Add a cooling_device property with at least one device\n");
		ret = -ENOENT;
		जाओ end;
	पूर्ण

	__tcbp = kसुस्मृति(count, माप(*__tcbp), GFP_KERNEL);
	अगर (!__tcbp) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		ret = of_parse_phandle_with_args(np, "cooling-device",
				"#cooling-cells", i, &cooling_spec);
		अगर (ret < 0) अणु
			pr_err("Invalid cooling-device entry\n");
			जाओ मुक्त_tcbp;
		पूर्ण

		__tcbp[i].cooling_device = cooling_spec.np;

		अगर (cooling_spec.args_count >= 2) अणु /* at least min and max */
			__tcbp[i].min = cooling_spec.args[0];
			__tcbp[i].max = cooling_spec.args[1];
		पूर्ण अन्यथा अणु
			pr_err("wrong reference to cooling device, missing limits\n");
		पूर्ण
	पूर्ण

	__tbp->tcbp = __tcbp;
	__tbp->count = count;

	जाओ end;

मुक्त_tcbp:
	क्रम (i = i - 1; i >= 0; i--)
		of_node_put(__tcbp[i].cooling_device);
	kमुक्त(__tcbp);
end:
	of_node_put(trip);

	वापस ret;
पूर्ण

/*
 * It maps 'enum thermal_trip_type' found in include/linux/thermal.h
 * पूर्णांकo the device tree binding of 'trip', property type.
 */
अटल स्थिर अक्षर * स्थिर trip_types[] = अणु
	[THERMAL_TRIP_ACTIVE]	= "active",
	[THERMAL_TRIP_PASSIVE]	= "passive",
	[THERMAL_TRIP_HOT]	= "hot",
	[THERMAL_TRIP_CRITICAL]	= "critical",
पूर्ण;

/**
 * thermal_of_get_trip_type - Get phy mode क्रम given device_node
 * @np:	Poपूर्णांकer to the given device_node
 * @type: Poपूर्णांकer to resulting trip type
 *
 * The function माला_लो trip type string from property 'type',
 * and store its index in trip_types table in @type,
 *
 * Return: 0 on success, or त्रुटि_सं in error हाल.
 */
अटल पूर्णांक thermal_of_get_trip_type(काष्ठा device_node *np,
				    क्रमागत thermal_trip_type *type)
अणु
	स्थिर अक्षर *t;
	पूर्णांक err, i;

	err = of_property_पढ़ो_string(np, "type", &t);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < ARRAY_SIZE(trip_types); i++)
		अगर (!strहालcmp(t, trip_types[i])) अणु
			*type = i;
			वापस 0;
		पूर्ण

	वापस -ENODEV;
पूर्ण

/**
 * thermal_of_populate_trip - parse and fill one trip poपूर्णांक data
 * @np: DT node containing a trip poपूर्णांक node
 * @trip: trip poपूर्णांक data काष्ठाure to be filled up
 *
 * This function parses a trip poपूर्णांक type of node represented by
 * @np parameter and fills the पढ़ो data पूर्णांकo @trip data काष्ठाure.
 *
 * Return: 0 on success, proper error code otherwise
 */
अटल पूर्णांक thermal_of_populate_trip(काष्ठा device_node *np,
				    काष्ठा thermal_trip *trip)
अणु
	पूर्णांक prop;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "temperature", &prop);
	अगर (ret < 0) अणु
		pr_err("missing temperature property\n");
		वापस ret;
	पूर्ण
	trip->temperature = prop;

	ret = of_property_पढ़ो_u32(np, "hysteresis", &prop);
	अगर (ret < 0) अणु
		pr_err("missing hysteresis property\n");
		वापस ret;
	पूर्ण
	trip->hysteresis = prop;

	ret = thermal_of_get_trip_type(np, &trip->type);
	अगर (ret < 0) अणु
		pr_err("wrong trip type property\n");
		वापस ret;
	पूर्ण

	/* Required क्रम cooling map matching */
	trip->np = np;
	of_node_get(np);

	वापस 0;
पूर्ण

/**
 * thermal_of_build_thermal_zone - parse and fill one thermal zone data
 * @np: DT node containing a thermal zone node
 *
 * This function parses a thermal zone type of node represented by
 * @np parameter and fills the पढ़ो data पूर्णांकo a __thermal_zone data काष्ठाure
 * and वापस this poपूर्णांकer.
 *
 * TODO: Missing properties to parse: thermal-sensor-names
 *
 * Return: On success वापसs a valid काष्ठा __thermal_zone,
 * otherwise, it वापसs a corresponding ERR_PTR(). Caller must
 * check the वापस value with help of IS_ERR() helper.
 */
अटल काष्ठा __thermal_zone
__init *thermal_of_build_thermal_zone(काष्ठा device_node *np)
अणु
	काष्ठा device_node *child = शून्य, *gchild;
	काष्ठा __thermal_zone *tz;
	पूर्णांक ret, i;
	u32 prop, coef[2];

	अगर (!np) अणु
		pr_err("no thermal zone np\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	tz = kzalloc(माप(*tz), GFP_KERNEL);
	अगर (!tz)
		वापस ERR_PTR(-ENOMEM);

	ret = of_property_पढ़ो_u32(np, "polling-delay-passive", &prop);
	अगर (ret < 0) अणु
		pr_err("%pOFn: missing polling-delay-passive property\n", np);
		जाओ मुक्त_tz;
	पूर्ण
	tz->passive_delay = prop;

	ret = of_property_पढ़ो_u32(np, "polling-delay", &prop);
	अगर (ret < 0) अणु
		pr_err("%pOFn: missing polling-delay property\n", np);
		जाओ मुक्त_tz;
	पूर्ण
	tz->polling_delay = prop;

	/*
	 * REVIST: क्रम now, the thermal framework supports only
	 * one sensor per thermal zone. Thus, we are considering
	 * only the first two values as slope and offset.
	 */
	ret = of_property_पढ़ो_u32_array(np, "coefficients", coef, 2);
	अगर (ret == 0) अणु
		tz->slope = coef[0];
		tz->offset = coef[1];
	पूर्ण अन्यथा अणु
		tz->slope = 1;
		tz->offset = 0;
	पूर्ण

	/* trips */
	child = of_get_child_by_name(np, "trips");

	/* No trips provided */
	अगर (!child)
		जाओ finish;

	tz->ntrips = of_get_child_count(child);
	अगर (tz->ntrips == 0) /* must have at least one child */
		जाओ finish;

	tz->trips = kसुस्मृति(tz->ntrips, माप(*tz->trips), GFP_KERNEL);
	अगर (!tz->trips) अणु
		ret = -ENOMEM;
		जाओ मुक्त_tz;
	पूर्ण

	i = 0;
	क्रम_each_child_of_node(child, gchild) अणु
		ret = thermal_of_populate_trip(gchild, &tz->trips[i++]);
		अगर (ret)
			जाओ मुक्त_trips;
	पूर्ण

	of_node_put(child);

	/* cooling-maps */
	child = of_get_child_by_name(np, "cooling-maps");

	/* cooling-maps not provided */
	अगर (!child)
		जाओ finish;

	tz->num_tbps = of_get_child_count(child);
	अगर (tz->num_tbps == 0)
		जाओ finish;

	tz->tbps = kसुस्मृति(tz->num_tbps, माप(*tz->tbps), GFP_KERNEL);
	अगर (!tz->tbps) अणु
		ret = -ENOMEM;
		जाओ मुक्त_trips;
	पूर्ण

	i = 0;
	क्रम_each_child_of_node(child, gchild) अणु
		ret = thermal_of_populate_bind_params(gchild, &tz->tbps[i++],
						      tz->trips, tz->ntrips);
		अगर (ret)
			जाओ मुक्त_tbps;
	पूर्ण

finish:
	of_node_put(child);

	वापस tz;

मुक्त_tbps:
	क्रम (i = i - 1; i >= 0; i--) अणु
		काष्ठा __thermal_bind_params *tbp = tz->tbps + i;
		पूर्णांक j;

		क्रम (j = 0; j < tbp->count; j++)
			of_node_put(tbp->tcbp[j].cooling_device);

		kमुक्त(tbp->tcbp);
	पूर्ण

	kमुक्त(tz->tbps);
मुक्त_trips:
	क्रम (i = 0; i < tz->ntrips; i++)
		of_node_put(tz->trips[i].np);
	kमुक्त(tz->trips);
	of_node_put(gchild);
मुक्त_tz:
	kमुक्त(tz);
	of_node_put(child);

	वापस ERR_PTR(ret);
पूर्ण

अटल __init व्योम of_thermal_मुक्त_zone(काष्ठा __thermal_zone *tz)
अणु
	काष्ठा __thermal_bind_params *tbp;
	पूर्णांक i, j;

	क्रम (i = 0; i < tz->num_tbps; i++) अणु
		tbp = tz->tbps + i;

		क्रम (j = 0; j < tbp->count; j++)
			of_node_put(tbp->tcbp[j].cooling_device);

		kमुक्त(tbp->tcbp);
	पूर्ण

	kमुक्त(tz->tbps);
	क्रम (i = 0; i < tz->ntrips; i++)
		of_node_put(tz->trips[i].np);
	kमुक्त(tz->trips);
	kमुक्त(tz);
पूर्ण

/**
 * of_thermal_destroy_zones - हटाओ all zones parsed and allocated resources
 *
 * Finds all zones parsed and added to the thermal framework and हटाओ them
 * from the प्रणाली, together with their resources.
 *
 */
अटल __init व्योम of_thermal_destroy_zones(व्योम)
अणु
	काष्ठा device_node *np, *child;

	np = of_find_node_by_name(शून्य, "thermal-zones");
	अगर (!np) अणु
		pr_debug("unable to find thermal zones\n");
		वापस;
	पूर्ण

	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा thermal_zone_device *zone;

		zone = thermal_zone_get_zone_by_name(child->name);
		अगर (IS_ERR(zone))
			जारी;

		thermal_zone_device_unरेजिस्टर(zone);
		kमुक्त(zone->tzp);
		kमुक्त(zone->ops);
		of_thermal_मुक्त_zone(zone->devdata);
	पूर्ण
	of_node_put(np);
पूर्ण

/**
 * of_parse_thermal_zones - parse device tree thermal data
 *
 * Initialization function that can be called by machine initialization
 * code to parse thermal data and populate the thermal framework
 * with hardware thermal zones info. This function only parses thermal zones.
 * Cooling devices and sensor devices nodes are supposed to be parsed
 * by their respective drivers.
 *
 * Return: 0 on success, proper error code otherwise
 *
 */
पूर्णांक __init of_parse_thermal_zones(व्योम)
अणु
	काष्ठा device_node *np, *child;
	काष्ठा __thermal_zone *tz;
	काष्ठा thermal_zone_device_ops *ops;

	np = of_find_node_by_name(शून्य, "thermal-zones");
	अगर (!np) अणु
		pr_debug("unable to find thermal zones\n");
		वापस 0; /* Run successfully on प्रणालीs without thermal DT */
	पूर्ण

	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा thermal_zone_device *zone;
		काष्ठा thermal_zone_params *tzp;
		पूर्णांक i, mask = 0;
		u32 prop;

		tz = thermal_of_build_thermal_zone(child);
		अगर (IS_ERR(tz)) अणु
			pr_err("failed to build thermal zone %pOFn: %ld\n",
			       child,
			       PTR_ERR(tz));
			जारी;
		पूर्ण

		ops = kmemdup(&of_thermal_ops, माप(*ops), GFP_KERNEL);
		अगर (!ops)
			जाओ निकास_मुक्त;

		tzp = kzalloc(माप(*tzp), GFP_KERNEL);
		अगर (!tzp) अणु
			kमुक्त(ops);
			जाओ निकास_मुक्त;
		पूर्ण

		/* No hwmon because there might be hwmon drivers रेजिस्टरing */
		tzp->no_hwmon = true;

		अगर (!of_property_पढ़ो_u32(child, "sustainable-power", &prop))
			tzp->sustainable_घातer = prop;

		क्रम (i = 0; i < tz->ntrips; i++)
			mask |= 1 << i;

		/* these two are left क्रम temperature drivers to use */
		tzp->slope = tz->slope;
		tzp->offset = tz->offset;

		zone = thermal_zone_device_रेजिस्टर(child->name, tz->ntrips,
						    mask, tz,
						    ops, tzp,
						    tz->passive_delay,
						    tz->polling_delay);
		अगर (IS_ERR(zone)) अणु
			pr_err("Failed to build %pOFn zone %ld\n", child,
			       PTR_ERR(zone));
			kमुक्त(tzp);
			kमुक्त(ops);
			of_thermal_मुक्त_zone(tz);
			/* attempting to build reमुख्यing zones still */
		पूर्ण
	पूर्ण
	of_node_put(np);

	वापस 0;

निकास_मुक्त:
	of_node_put(child);
	of_node_put(np);
	of_thermal_मुक्त_zone(tz);

	/* no memory available, so मुक्त what we have built */
	of_thermal_destroy_zones();

	वापस -ENOMEM;
पूर्ण
