<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * devfreq_cooling: Thermal cooling device implementation क्रम devices using
 *                  devfreq
 *
 * Copyright (C) 2014-2015 ARM Limited
 *
 * TODO:
 *    - If OPPs are added or हटाओd after devfreq cooling has
 *      रेजिस्टरed, the devfreq cooling won't react to it.
 */

#समावेश <linux/devfreq.h>
#समावेश <linux/devfreq_cooling.h>
#समावेश <linux/energy_model.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/thermal.h>

#समावेश <trace/events/thermal.h>

#घोषणा HZ_PER_KHZ		1000
#घोषणा SCALE_ERROR_MITIGATION	100

/**
 * काष्ठा devfreq_cooling_device - Devfreq cooling device
 *		devfreq_cooling_device रेजिस्टरed.
 * @cdev:	Poपूर्णांकer to associated thermal cooling device.
 * @devfreq:	Poपूर्णांकer to associated devfreq device.
 * @cooling_state:	Current cooling state.
 * @freq_table:	Poपूर्णांकer to a table with the frequencies sorted in descending
 *		order.  You can index the table by cooling device state
 * @max_state:	It is the last index, that is, one less than the number of the
 *		OPPs
 * @घातer_ops:	Poपूर्णांकer to devfreq_cooling_घातer, a more precised model.
 * @res_util:	Resource utilization scaling factor क्रम the घातer.
 *		It is multiplied by 100 to minimize the error. It is used
 *		क्रम estimation of the घातer budget instead of using
 *		'utilization' (which is	'busy_time' / 'total_time').
 *		The 'res_util' range is from 100 to घातer * 100	क्रम the
 *		corresponding 'state'.
 * @capped_state:	index to cooling state with in dynamic घातer budget
 * @req_max_freq:	PM QoS request क्रम limiting the maximum frequency
 *			of the devfreq device.
 * @em_pd:		Energy Model क्रम the associated Devfreq device
 */
काष्ठा devfreq_cooling_device अणु
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा devfreq *devfreq;
	अचिन्हित दीर्घ cooling_state;
	u32 *freq_table;
	माप_प्रकार max_state;
	काष्ठा devfreq_cooling_घातer *घातer_ops;
	u32 res_util;
	पूर्णांक capped_state;
	काष्ठा dev_pm_qos_request req_max_freq;
	काष्ठा em_perf_करोमुख्य *em_pd;
पूर्ण;

अटल पूर्णांक devfreq_cooling_get_max_state(काष्ठा thermal_cooling_device *cdev,
					 अचिन्हित दीर्घ *state)
अणु
	काष्ठा devfreq_cooling_device *dfc = cdev->devdata;

	*state = dfc->max_state;

	वापस 0;
पूर्ण

अटल पूर्णांक devfreq_cooling_get_cur_state(काष्ठा thermal_cooling_device *cdev,
					 अचिन्हित दीर्घ *state)
अणु
	काष्ठा devfreq_cooling_device *dfc = cdev->devdata;

	*state = dfc->cooling_state;

	वापस 0;
पूर्ण

अटल पूर्णांक devfreq_cooling_set_cur_state(काष्ठा thermal_cooling_device *cdev,
					 अचिन्हित दीर्घ state)
अणु
	काष्ठा devfreq_cooling_device *dfc = cdev->devdata;
	काष्ठा devfreq *df = dfc->devfreq;
	काष्ठा device *dev = df->dev.parent;
	अचिन्हित दीर्घ freq;
	पूर्णांक perf_idx;

	अगर (state == dfc->cooling_state)
		वापस 0;

	dev_dbg(dev, "Setting cooling state %lu\n", state);

	अगर (state > dfc->max_state)
		वापस -EINVAL;

	अगर (dfc->em_pd) अणु
		perf_idx = dfc->max_state - state;
		freq = dfc->em_pd->table[perf_idx].frequency * 1000;
	पूर्ण अन्यथा अणु
		freq = dfc->freq_table[state];
	पूर्ण

	dev_pm_qos_update_request(&dfc->req_max_freq,
				  DIV_ROUND_UP(freq, HZ_PER_KHZ));

	dfc->cooling_state = state;

	वापस 0;
पूर्ण

/**
 * get_perf_idx() - get the perक्रमmance index corresponding to a frequency
 * @em_pd:	Poपूर्णांकer to device's Energy Model
 * @freq:	frequency in kHz
 *
 * Return: the perक्रमmance index associated with the @freq, or
 * -EINVAL अगर it wasn't found.
 */
अटल पूर्णांक get_perf_idx(काष्ठा em_perf_करोमुख्य *em_pd, अचिन्हित दीर्घ freq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < em_pd->nr_perf_states; i++) अणु
		अगर (em_pd->table[i].frequency == freq)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अचिन्हित दीर्घ get_voltage(काष्ठा devfreq *df, अचिन्हित दीर्घ freq)
अणु
	काष्ठा device *dev = df->dev.parent;
	अचिन्हित दीर्घ voltage;
	काष्ठा dev_pm_opp *opp;

	opp = dev_pm_opp_find_freq_exact(dev, freq, true);
	अगर (PTR_ERR(opp) == -दुस्फल)
		opp = dev_pm_opp_find_freq_exact(dev, freq, false);

	अगर (IS_ERR(opp)) अणु
		dev_err_ratelimited(dev, "Failed to find OPP for frequency %lu: %ld\n",
				    freq, PTR_ERR(opp));
		वापस 0;
	पूर्ण

	voltage = dev_pm_opp_get_voltage(opp) / 1000; /* mV */
	dev_pm_opp_put(opp);

	अगर (voltage == 0) अणु
		dev_err_ratelimited(dev,
				    "Failed to get voltage for frequency %lu\n",
				    freq);
	पूर्ण

	वापस voltage;
पूर्ण

अटल व्योम _normalize_load(काष्ठा devfreq_dev_status *status)
अणु
	अगर (status->total_समय > 0xfffff) अणु
		status->total_समय >>= 10;
		status->busy_समय >>= 10;
	पूर्ण

	status->busy_समय <<= 10;
	status->busy_समय /= status->total_समय ? : 1;

	status->busy_समय = status->busy_समय ? : 1;
	status->total_समय = 1024;
पूर्ण

अटल पूर्णांक devfreq_cooling_get_requested_घातer(काष्ठा thermal_cooling_device *cdev,
					       u32 *घातer)
अणु
	काष्ठा devfreq_cooling_device *dfc = cdev->devdata;
	काष्ठा devfreq *df = dfc->devfreq;
	काष्ठा devfreq_dev_status status;
	अचिन्हित दीर्घ state;
	अचिन्हित दीर्घ freq;
	अचिन्हित दीर्घ voltage;
	पूर्णांक res, perf_idx;

	mutex_lock(&df->lock);
	status = df->last_status;
	mutex_unlock(&df->lock);

	freq = status.current_frequency;

	अगर (dfc->घातer_ops && dfc->घातer_ops->get_real_घातer) अणु
		voltage = get_voltage(df, freq);
		अगर (voltage == 0) अणु
			res = -EINVAL;
			जाओ fail;
		पूर्ण

		res = dfc->घातer_ops->get_real_घातer(df, घातer, freq, voltage);
		अगर (!res) अणु
			state = dfc->capped_state;
			dfc->res_util = dfc->em_pd->table[state].घातer;
			dfc->res_util *= SCALE_ERROR_MITIGATION;

			अगर (*घातer > 1)
				dfc->res_util /= *घातer;
		पूर्ण अन्यथा अणु
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Energy Model frequencies are in kHz */
		perf_idx = get_perf_idx(dfc->em_pd, freq / 1000);
		अगर (perf_idx < 0) अणु
			res = -EAGAIN;
			जाओ fail;
		पूर्ण

		_normalize_load(&status);

		/* Scale घातer क्रम utilization */
		*घातer = dfc->em_pd->table[perf_idx].घातer;
		*घातer *= status.busy_समय;
		*घातer >>= 10;
	पूर्ण

	trace_thermal_घातer_devfreq_get_घातer(cdev, &status, freq, *घातer);

	वापस 0;
fail:
	/* It is safe to set max in this हाल */
	dfc->res_util = SCALE_ERROR_MITIGATION;
	वापस res;
पूर्ण

अटल पूर्णांक devfreq_cooling_state2घातer(काष्ठा thermal_cooling_device *cdev,
				       अचिन्हित दीर्घ state, u32 *घातer)
अणु
	काष्ठा devfreq_cooling_device *dfc = cdev->devdata;
	पूर्णांक perf_idx;

	अगर (state > dfc->max_state)
		वापस -EINVAL;

	perf_idx = dfc->max_state - state;
	*घातer = dfc->em_pd->table[perf_idx].घातer;

	वापस 0;
पूर्ण

अटल पूर्णांक devfreq_cooling_घातer2state(काष्ठा thermal_cooling_device *cdev,
				       u32 घातer, अचिन्हित दीर्घ *state)
अणु
	काष्ठा devfreq_cooling_device *dfc = cdev->devdata;
	काष्ठा devfreq *df = dfc->devfreq;
	काष्ठा devfreq_dev_status status;
	अचिन्हित दीर्घ freq;
	s32 est_घातer;
	पूर्णांक i;

	mutex_lock(&df->lock);
	status = df->last_status;
	mutex_unlock(&df->lock);

	freq = status.current_frequency;

	अगर (dfc->घातer_ops && dfc->घातer_ops->get_real_घातer) अणु
		/* Scale क्रम resource utilization */
		est_घातer = घातer * dfc->res_util;
		est_घातer /= SCALE_ERROR_MITIGATION;
	पूर्ण अन्यथा अणु
		/* Scale dynamic घातer क्रम utilization */
		_normalize_load(&status);
		est_घातer = घातer << 10;
		est_घातer /= status.busy_समय;
	पूर्ण

	/*
	 * Find the first cooling state that is within the घातer
	 * budget. The EM घातer table is sorted ascending.
	 */
	क्रम (i = dfc->max_state; i > 0; i--)
		अगर (est_घातer >= dfc->em_pd->table[i].घातer)
			अवरोध;

	*state = dfc->max_state - i;
	dfc->capped_state = *state;

	trace_thermal_घातer_devfreq_limit(cdev, freq, *state, घातer);
	वापस 0;
पूर्ण

अटल काष्ठा thermal_cooling_device_ops devfreq_cooling_ops = अणु
	.get_max_state = devfreq_cooling_get_max_state,
	.get_cur_state = devfreq_cooling_get_cur_state,
	.set_cur_state = devfreq_cooling_set_cur_state,
पूर्ण;

/**
 * devfreq_cooling_gen_tables() - Generate frequency table.
 * @dfc:	Poपूर्णांकer to devfreq cooling device.
 * @num_opps:	Number of OPPs
 *
 * Generate frequency table which holds the frequencies in descending
 * order. That way its indexed by cooling device state. This is क्रम
 * compatibility with drivers which करो not रेजिस्टर Energy Model.
 *
 * Return: 0 on success, negative error code on failure.
 */
अटल पूर्णांक devfreq_cooling_gen_tables(काष्ठा devfreq_cooling_device *dfc,
				      पूर्णांक num_opps)
अणु
	काष्ठा devfreq *df = dfc->devfreq;
	काष्ठा device *dev = df->dev.parent;
	अचिन्हित दीर्घ freq;
	पूर्णांक i;

	dfc->freq_table = kसुस्मृति(num_opps, माप(*dfc->freq_table),
			     GFP_KERNEL);
	अगर (!dfc->freq_table)
		वापस -ENOMEM;

	क्रम (i = 0, freq = अच_दीर्घ_उच्च; i < num_opps; i++, freq--) अणु
		काष्ठा dev_pm_opp *opp;

		opp = dev_pm_opp_find_freq_न्यूनमान(dev, &freq);
		अगर (IS_ERR(opp)) अणु
			kमुक्त(dfc->freq_table);
			वापस PTR_ERR(opp);
		पूर्ण

		dev_pm_opp_put(opp);
		dfc->freq_table[i] = freq;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * of_devfreq_cooling_रेजिस्टर_घातer() - Register devfreq cooling device,
 *                                      with OF and घातer inक्रमmation.
 * @np:	Poपूर्णांकer to OF device_node.
 * @df:	Poपूर्णांकer to devfreq device.
 * @dfc_घातer:	Poपूर्णांकer to devfreq_cooling_घातer.
 *
 * Register a devfreq cooling device.  The available OPPs must be
 * रेजिस्टरed on the device.
 *
 * If @dfc_घातer is provided, the cooling device is रेजिस्टरed with the
 * घातer extensions.  For the घातer extensions to work correctly,
 * devfreq should use the simple_ondemand governor, other governors
 * are not currently supported.
 */
काष्ठा thermal_cooling_device *
of_devfreq_cooling_रेजिस्टर_घातer(काष्ठा device_node *np, काष्ठा devfreq *df,
				  काष्ठा devfreq_cooling_घातer *dfc_घातer)
अणु
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा device *dev = df->dev.parent;
	काष्ठा devfreq_cooling_device *dfc;
	अक्षर *name;
	पूर्णांक err, num_opps;

	dfc = kzalloc(माप(*dfc), GFP_KERNEL);
	अगर (!dfc)
		वापस ERR_PTR(-ENOMEM);

	dfc->devfreq = df;

	dfc->em_pd = em_pd_get(dev);
	अगर (dfc->em_pd) अणु
		devfreq_cooling_ops.get_requested_घातer =
			devfreq_cooling_get_requested_घातer;
		devfreq_cooling_ops.state2घातer = devfreq_cooling_state2घातer;
		devfreq_cooling_ops.घातer2state = devfreq_cooling_घातer2state;

		dfc->घातer_ops = dfc_घातer;

		num_opps = em_pd_nr_perf_states(dfc->em_pd);
	पूर्ण अन्यथा अणु
		/* Backward compatibility क्रम drivers which करो not use IPA */
		dev_dbg(dev, "missing EM for cooling device\n");

		num_opps = dev_pm_opp_get_opp_count(dev);

		err = devfreq_cooling_gen_tables(dfc, num_opps);
		अगर (err)
			जाओ मुक्त_dfc;
	पूर्ण

	अगर (num_opps <= 0) अणु
		err = -EINVAL;
		जाओ मुक्त_dfc;
	पूर्ण

	/* max_state is an index, not a counter */
	dfc->max_state = num_opps - 1;

	err = dev_pm_qos_add_request(dev, &dfc->req_max_freq,
				     DEV_PM_QOS_MAX_FREQUENCY,
				     PM_QOS_MAX_FREQUENCY_DEFAULT_VALUE);
	अगर (err < 0)
		जाओ मुक्त_table;

	err = -ENOMEM;
	name = kaप्र_लिखो(GFP_KERNEL, "devfreq-%s", dev_name(dev));
	अगर (!name)
		जाओ हटाओ_qos_req;

	cdev = thermal_of_cooling_device_रेजिस्टर(np, name, dfc,
						  &devfreq_cooling_ops);
	kमुक्त(name);

	अगर (IS_ERR(cdev)) अणु
		err = PTR_ERR(cdev);
		dev_err(dev,
			"Failed to register devfreq cooling device (%d)\n",
			err);
		जाओ हटाओ_qos_req;
	पूर्ण

	dfc->cdev = cdev;

	वापस cdev;

हटाओ_qos_req:
	dev_pm_qos_हटाओ_request(&dfc->req_max_freq);
मुक्त_table:
	kमुक्त(dfc->freq_table);
मुक्त_dfc:
	kमुक्त(dfc);

	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(of_devfreq_cooling_रेजिस्टर_घातer);

/**
 * of_devfreq_cooling_रेजिस्टर() - Register devfreq cooling device,
 *                                with OF inक्रमmation.
 * @np: Poपूर्णांकer to OF device_node.
 * @df: Poपूर्णांकer to devfreq device.
 */
काष्ठा thermal_cooling_device *
of_devfreq_cooling_रेजिस्टर(काष्ठा device_node *np, काष्ठा devfreq *df)
अणु
	वापस of_devfreq_cooling_रेजिस्टर_घातer(np, df, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(of_devfreq_cooling_रेजिस्टर);

/**
 * devfreq_cooling_रेजिस्टर() - Register devfreq cooling device.
 * @df: Poपूर्णांकer to devfreq device.
 */
काष्ठा thermal_cooling_device *devfreq_cooling_रेजिस्टर(काष्ठा devfreq *df)
अणु
	वापस of_devfreq_cooling_रेजिस्टर(शून्य, df);
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_cooling_रेजिस्टर);

/**
 * devfreq_cooling_em_रेजिस्टर_घातer() - Register devfreq cooling device with
 *		घातer inक्रमmation and स्वतःmatically रेजिस्टर Energy Model (EM)
 * @df:		Poपूर्णांकer to devfreq device.
 * @dfc_घातer:	Poपूर्णांकer to devfreq_cooling_घातer.
 *
 * Register a devfreq cooling device and स्वतःmatically रेजिस्टर EM. The
 * available OPPs must be रेजिस्टरed क्रम the device.
 *
 * If @dfc_घातer is provided, the cooling device is रेजिस्टरed with the
 * घातer extensions. It is using the simple Energy Model which requires
 * "dynamic-power-coefficient" a devicetree property. To not अवरोध drivers
 * which miss that DT property, the function won't bail out when the EM
 * registration failed. The cooling device will be रेजिस्टरed अगर everything
 * अन्यथा is OK.
 */
काष्ठा thermal_cooling_device *
devfreq_cooling_em_रेजिस्टर(काष्ठा devfreq *df,
			    काष्ठा devfreq_cooling_घातer *dfc_घातer)
अणु
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा device *dev;
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(df))
		वापस ERR_PTR(-EINVAL);

	dev = df->dev.parent;

	ret = dev_pm_opp_of_रेजिस्टर_em(dev, शून्य);
	अगर (ret)
		dev_dbg(dev, "Unable to register EM for devfreq cooling device (%d)\n",
			ret);

	cdev = of_devfreq_cooling_रेजिस्टर_घातer(dev->of_node, df, dfc_घातer);

	अगर (IS_ERR_OR_शून्य(cdev))
		em_dev_unरेजिस्टर_perf_करोमुख्य(dev);

	वापस cdev;
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_cooling_em_रेजिस्टर);

/**
 * devfreq_cooling_unरेजिस्टर() - Unरेजिस्टर devfreq cooling device.
 * @cdev: Poपूर्णांकer to devfreq cooling device to unरेजिस्टर.
 *
 * Unरेजिस्टरs devfreq cooling device and related Energy Model अगर it was
 * present.
 */
व्योम devfreq_cooling_unरेजिस्टर(काष्ठा thermal_cooling_device *cdev)
अणु
	काष्ठा devfreq_cooling_device *dfc;
	काष्ठा device *dev;

	अगर (IS_ERR_OR_शून्य(cdev))
		वापस;

	dfc = cdev->devdata;
	dev = dfc->devfreq->dev.parent;

	thermal_cooling_device_unरेजिस्टर(dfc->cdev);
	dev_pm_qos_हटाओ_request(&dfc->req_max_freq);

	em_dev_unरेजिस्टर_perf_करोमुख्य(dev);

	kमुक्त(dfc->freq_table);
	kमुक्त(dfc);
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_cooling_unरेजिस्टर);
