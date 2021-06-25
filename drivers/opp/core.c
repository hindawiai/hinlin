<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic OPP Interface
 *
 * Copyright (C) 2009-2010 Texas Instruments Incorporated.
 *	Nishanth Menon
 *	Romit Dasgupta
 *	Kevin Hilman
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "opp.h"

/*
 * The root of the list of all opp-tables. All opp_table काष्ठाures branch off
 * from here, with each opp_table containing the list of opps it supports in
 * various states of availability.
 */
LIST_HEAD(opp_tables);

/* OPP tables with uninitialized required OPPs */
LIST_HEAD(lazy_opp_tables);

/* Lock to allow exclusive modअगरication to the device and opp lists */
DEFINE_MUTEX(opp_table_lock);
/* Flag indicating that opp_tables list is being updated at the moment */
अटल bool opp_tables_busy;

अटल bool _find_opp_dev(स्थिर काष्ठा device *dev, काष्ठा opp_table *opp_table)
अणु
	काष्ठा opp_device *opp_dev;
	bool found = false;

	mutex_lock(&opp_table->lock);
	list_क्रम_each_entry(opp_dev, &opp_table->dev_list, node)
		अगर (opp_dev->dev == dev) अणु
			found = true;
			अवरोध;
		पूर्ण

	mutex_unlock(&opp_table->lock);
	वापस found;
पूर्ण

अटल काष्ठा opp_table *_find_opp_table_unlocked(काष्ठा device *dev)
अणु
	काष्ठा opp_table *opp_table;

	list_क्रम_each_entry(opp_table, &opp_tables, node) अणु
		अगर (_find_opp_dev(dev, opp_table)) अणु
			_get_opp_table_kref(opp_table);
			वापस opp_table;
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण

/**
 * _find_opp_table() - find opp_table काष्ठा using device poपूर्णांकer
 * @dev:	device poपूर्णांकer used to lookup OPP table
 *
 * Search OPP table क्रम one containing matching device.
 *
 * Return: poपूर्णांकer to 'struct opp_table' अगर found, otherwise -ENODEV or
 * -EINVAL based on type of error.
 *
 * The callers must call dev_pm_opp_put_opp_table() after the table is used.
 */
काष्ठा opp_table *_find_opp_table(काष्ठा device *dev)
अणु
	काष्ठा opp_table *opp_table;

	अगर (IS_ERR_OR_शून्य(dev)) अणु
		pr_err("%s: Invalid parameters\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mutex_lock(&opp_table_lock);
	opp_table = _find_opp_table_unlocked(dev);
	mutex_unlock(&opp_table_lock);

	वापस opp_table;
पूर्ण

/**
 * dev_pm_opp_get_voltage() - Gets the voltage corresponding to an opp
 * @opp:	opp क्रम which voltage has to be वापसed क्रम
 *
 * Return: voltage in micro volt corresponding to the opp, अन्यथा
 * वापस 0
 *
 * This is useful only क्रम devices with single घातer supply.
 */
अचिन्हित दीर्घ dev_pm_opp_get_voltage(काष्ठा dev_pm_opp *opp)
अणु
	अगर (IS_ERR_OR_शून्य(opp)) अणु
		pr_err("%s: Invalid parameters\n", __func__);
		वापस 0;
	पूर्ण

	वापस opp->supplies[0].u_volt;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_voltage);

/**
 * dev_pm_opp_get_freq() - Gets the frequency corresponding to an available opp
 * @opp:	opp क्रम which frequency has to be वापसed क्रम
 *
 * Return: frequency in hertz corresponding to the opp, अन्यथा
 * वापस 0
 */
अचिन्हित दीर्घ dev_pm_opp_get_freq(काष्ठा dev_pm_opp *opp)
अणु
	अगर (IS_ERR_OR_शून्य(opp)) अणु
		pr_err("%s: Invalid parameters\n", __func__);
		वापस 0;
	पूर्ण

	वापस opp->rate;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_freq);

/**
 * dev_pm_opp_get_level() - Gets the level corresponding to an available opp
 * @opp:	opp क्रम which level value has to be वापसed क्रम
 *
 * Return: level पढ़ो from device tree corresponding to the opp, अन्यथा
 * वापस 0.
 */
अचिन्हित पूर्णांक dev_pm_opp_get_level(काष्ठा dev_pm_opp *opp)
अणु
	अगर (IS_ERR_OR_शून्य(opp) || !opp->available) अणु
		pr_err("%s: Invalid parameters\n", __func__);
		वापस 0;
	पूर्ण

	वापस opp->level;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_level);

/**
 * dev_pm_opp_get_required_pstate() - Gets the required perक्रमmance state
 *                                    corresponding to an available opp
 * @opp:	opp क्रम which perक्रमmance state has to be वापसed क्रम
 * @index:	index of the required opp
 *
 * Return: perक्रमmance state पढ़ो from device tree corresponding to the
 * required opp, अन्यथा वापस 0.
 */
अचिन्हित पूर्णांक dev_pm_opp_get_required_pstate(काष्ठा dev_pm_opp *opp,
					    अचिन्हित पूर्णांक index)
अणु
	अगर (IS_ERR_OR_शून्य(opp) || !opp->available ||
	    index >= opp->opp_table->required_opp_count) अणु
		pr_err("%s: Invalid parameters\n", __func__);
		वापस 0;
	पूर्ण

	/* required-opps not fully initialized yet */
	अगर (lazy_linking_pending(opp->opp_table))
		वापस 0;

	वापस opp->required_opps[index]->pstate;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_required_pstate);

/**
 * dev_pm_opp_is_turbo() - Returns अगर opp is turbo OPP or not
 * @opp: opp क्रम which turbo mode is being verअगरied
 *
 * Turbo OPPs are not क्रम normal use, and can be enabled (under certain
 * conditions) क्रम लघु duration of बार to finish high throughput work
 * quickly. Running on them क्रम दीर्घer बार may overheat the chip.
 *
 * Return: true अगर opp is turbo opp, अन्यथा false.
 */
bool dev_pm_opp_is_turbo(काष्ठा dev_pm_opp *opp)
अणु
	अगर (IS_ERR_OR_शून्य(opp) || !opp->available) अणु
		pr_err("%s: Invalid parameters\n", __func__);
		वापस false;
	पूर्ण

	वापस opp->turbo;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_is_turbo);

/**
 * dev_pm_opp_get_max_घड़ी_latency() - Get max घड़ी latency in nanoseconds
 * @dev:	device क्रम which we करो this operation
 *
 * Return: This function वापसs the max घड़ी latency in nanoseconds.
 */
अचिन्हित दीर्घ dev_pm_opp_get_max_घड़ी_latency(काष्ठा device *dev)
अणु
	काष्ठा opp_table *opp_table;
	अचिन्हित दीर्घ घड़ी_latency_ns;

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table))
		वापस 0;

	घड़ी_latency_ns = opp_table->घड़ी_latency_ns_max;

	dev_pm_opp_put_opp_table(opp_table);

	वापस घड़ी_latency_ns;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_max_घड़ी_latency);

/**
 * dev_pm_opp_get_max_volt_latency() - Get max voltage latency in nanoseconds
 * @dev: device क्रम which we करो this operation
 *
 * Return: This function वापसs the max voltage latency in nanoseconds.
 */
अचिन्हित दीर्घ dev_pm_opp_get_max_volt_latency(काष्ठा device *dev)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा dev_pm_opp *opp;
	काष्ठा regulator *reg;
	अचिन्हित दीर्घ latency_ns = 0;
	पूर्णांक ret, i, count;
	काष्ठा अणु
		अचिन्हित दीर्घ min;
		अचिन्हित दीर्घ max;
	पूर्ण *uV;

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table))
		वापस 0;

	/* Regulator may not be required क्रम the device */
	अगर (!opp_table->regulators)
		जाओ put_opp_table;

	count = opp_table->regulator_count;

	uV = kदो_स्मृति_array(count, माप(*uV), GFP_KERNEL);
	अगर (!uV)
		जाओ put_opp_table;

	mutex_lock(&opp_table->lock);

	क्रम (i = 0; i < count; i++) अणु
		uV[i].min = ~0;
		uV[i].max = 0;

		list_क्रम_each_entry(opp, &opp_table->opp_list, node) अणु
			अगर (!opp->available)
				जारी;

			अगर (opp->supplies[i].u_volt_min < uV[i].min)
				uV[i].min = opp->supplies[i].u_volt_min;
			अगर (opp->supplies[i].u_volt_max > uV[i].max)
				uV[i].max = opp->supplies[i].u_volt_max;
		पूर्ण
	पूर्ण

	mutex_unlock(&opp_table->lock);

	/*
	 * The caller needs to ensure that opp_table (and hence the regulator)
	 * isn't मुक्तd, जबतक we are executing this routine.
	 */
	क्रम (i = 0; i < count; i++) अणु
		reg = opp_table->regulators[i];
		ret = regulator_set_voltage_समय(reg, uV[i].min, uV[i].max);
		अगर (ret > 0)
			latency_ns += ret * 1000;
	पूर्ण

	kमुक्त(uV);
put_opp_table:
	dev_pm_opp_put_opp_table(opp_table);

	वापस latency_ns;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_max_volt_latency);

/**
 * dev_pm_opp_get_max_transition_latency() - Get max transition latency in
 *					     nanoseconds
 * @dev: device क्रम which we करो this operation
 *
 * Return: This function वापसs the max transition latency, in nanoseconds, to
 * चयन from one OPP to other.
 */
अचिन्हित दीर्घ dev_pm_opp_get_max_transition_latency(काष्ठा device *dev)
अणु
	वापस dev_pm_opp_get_max_volt_latency(dev) +
		dev_pm_opp_get_max_घड़ी_latency(dev);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_max_transition_latency);

/**
 * dev_pm_opp_get_suspend_opp_freq() - Get frequency of suspend opp in Hz
 * @dev:	device क्रम which we करो this operation
 *
 * Return: This function वापसs the frequency of the OPP marked as suspend_opp
 * अगर one is available, अन्यथा वापसs 0;
 */
अचिन्हित दीर्घ dev_pm_opp_get_suspend_opp_freq(काष्ठा device *dev)
अणु
	काष्ठा opp_table *opp_table;
	अचिन्हित दीर्घ freq = 0;

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table))
		वापस 0;

	अगर (opp_table->suspend_opp && opp_table->suspend_opp->available)
		freq = dev_pm_opp_get_freq(opp_table->suspend_opp);

	dev_pm_opp_put_opp_table(opp_table);

	वापस freq;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_suspend_opp_freq);

पूर्णांक _get_opp_count(काष्ठा opp_table *opp_table)
अणु
	काष्ठा dev_pm_opp *opp;
	पूर्णांक count = 0;

	mutex_lock(&opp_table->lock);

	list_क्रम_each_entry(opp, &opp_table->opp_list, node) अणु
		अगर (opp->available)
			count++;
	पूर्ण

	mutex_unlock(&opp_table->lock);

	वापस count;
पूर्ण

/**
 * dev_pm_opp_get_opp_count() - Get number of opps available in the opp table
 * @dev:	device क्रम which we करो this operation
 *
 * Return: This function वापसs the number of available opps अगर there are any,
 * अन्यथा वापसs 0 अगर none or the corresponding error value.
 */
पूर्णांक dev_pm_opp_get_opp_count(काष्ठा device *dev)
अणु
	काष्ठा opp_table *opp_table;
	पूर्णांक count;

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table)) अणु
		count = PTR_ERR(opp_table);
		dev_dbg(dev, "%s: OPP table not found (%d)\n",
			__func__, count);
		वापस count;
	पूर्ण

	count = _get_opp_count(opp_table);
	dev_pm_opp_put_opp_table(opp_table);

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_opp_count);

/**
 * dev_pm_opp_find_freq_exact() - search क्रम an exact frequency
 * @dev:		device क्रम which we करो this operation
 * @freq:		frequency to search क्रम
 * @available:		true/false - match क्रम available opp
 *
 * Return: Searches क्रम exact match in the opp table and वापसs poपूर्णांकer to the
 * matching opp अगर found, अन्यथा वापसs ERR_PTR in हाल of error and should
 * be handled using IS_ERR. Error वापस values can be:
 * EINVAL:	क्रम bad poपूर्णांकer
 * दुस्फल:	no match found क्रम search
 * ENODEV:	अगर device not found in list of रेजिस्टरed devices
 *
 * Note: available is a modअगरier क्रम the search. अगर available=true, then the
 * match is क्रम exact matching frequency and is available in the stored OPP
 * table. अगर false, the match is क्रम exact frequency which is not available.
 *
 * This provides a mechanism to enable an opp which is not available currently
 * or the opposite as well.
 *
 * The callers are required to call dev_pm_opp_put() क्रम the वापसed OPP after
 * use.
 */
काष्ठा dev_pm_opp *dev_pm_opp_find_freq_exact(काष्ठा device *dev,
					      अचिन्हित दीर्घ freq,
					      bool available)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा dev_pm_opp *temp_opp, *opp = ERR_PTR(-दुस्फल);

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table)) अणु
		पूर्णांक r = PTR_ERR(opp_table);

		dev_err(dev, "%s: OPP table not found (%d)\n", __func__, r);
		वापस ERR_PTR(r);
	पूर्ण

	mutex_lock(&opp_table->lock);

	list_क्रम_each_entry(temp_opp, &opp_table->opp_list, node) अणु
		अगर (temp_opp->available == available &&
				temp_opp->rate == freq) अणु
			opp = temp_opp;

			/* Increment the reference count of OPP */
			dev_pm_opp_get(opp);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&opp_table->lock);
	dev_pm_opp_put_opp_table(opp_table);

	वापस opp;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_find_freq_exact);

/**
 * dev_pm_opp_find_level_exact() - search क्रम an exact level
 * @dev:		device क्रम which we करो this operation
 * @level:		level to search क्रम
 *
 * Return: Searches क्रम exact match in the opp table and वापसs poपूर्णांकer to the
 * matching opp अगर found, अन्यथा वापसs ERR_PTR in हाल of error and should
 * be handled using IS_ERR. Error वापस values can be:
 * EINVAL:	क्रम bad poपूर्णांकer
 * दुस्फल:	no match found क्रम search
 * ENODEV:	अगर device not found in list of रेजिस्टरed devices
 *
 * The callers are required to call dev_pm_opp_put() क्रम the वापसed OPP after
 * use.
 */
काष्ठा dev_pm_opp *dev_pm_opp_find_level_exact(काष्ठा device *dev,
					       अचिन्हित पूर्णांक level)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा dev_pm_opp *temp_opp, *opp = ERR_PTR(-दुस्फल);

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table)) अणु
		पूर्णांक r = PTR_ERR(opp_table);

		dev_err(dev, "%s: OPP table not found (%d)\n", __func__, r);
		वापस ERR_PTR(r);
	पूर्ण

	mutex_lock(&opp_table->lock);

	list_क्रम_each_entry(temp_opp, &opp_table->opp_list, node) अणु
		अगर (temp_opp->level == level) अणु
			opp = temp_opp;

			/* Increment the reference count of OPP */
			dev_pm_opp_get(opp);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&opp_table->lock);
	dev_pm_opp_put_opp_table(opp_table);

	वापस opp;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_find_level_exact);

/**
 * dev_pm_opp_find_level_उच्चमान() - search क्रम an rounded up level
 * @dev:		device क्रम which we करो this operation
 * @level:		level to search क्रम
 *
 * Return: Searches क्रम rounded up match in the opp table and वापसs poपूर्णांकer
 * to the  matching opp अगर found, अन्यथा वापसs ERR_PTR in हाल of error and
 * should be handled using IS_ERR. Error वापस values can be:
 * EINVAL:	क्रम bad poपूर्णांकer
 * दुस्फल:	no match found क्रम search
 * ENODEV:	अगर device not found in list of रेजिस्टरed devices
 *
 * The callers are required to call dev_pm_opp_put() क्रम the वापसed OPP after
 * use.
 */
काष्ठा dev_pm_opp *dev_pm_opp_find_level_उच्चमान(काष्ठा device *dev,
					      अचिन्हित पूर्णांक *level)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा dev_pm_opp *temp_opp, *opp = ERR_PTR(-दुस्फल);

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table)) अणु
		पूर्णांक r = PTR_ERR(opp_table);

		dev_err(dev, "%s: OPP table not found (%d)\n", __func__, r);
		वापस ERR_PTR(r);
	पूर्ण

	mutex_lock(&opp_table->lock);

	list_क्रम_each_entry(temp_opp, &opp_table->opp_list, node) अणु
		अगर (temp_opp->available && temp_opp->level >= *level) अणु
			opp = temp_opp;
			*level = opp->level;

			/* Increment the reference count of OPP */
			dev_pm_opp_get(opp);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&opp_table->lock);
	dev_pm_opp_put_opp_table(opp_table);

	वापस opp;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_find_level_उच्चमान);

अटल noअंतरभूत काष्ठा dev_pm_opp *_find_freq_उच्चमान(काष्ठा opp_table *opp_table,
						   अचिन्हित दीर्घ *freq)
अणु
	काष्ठा dev_pm_opp *temp_opp, *opp = ERR_PTR(-दुस्फल);

	mutex_lock(&opp_table->lock);

	list_क्रम_each_entry(temp_opp, &opp_table->opp_list, node) अणु
		अगर (temp_opp->available && temp_opp->rate >= *freq) अणु
			opp = temp_opp;
			*freq = opp->rate;

			/* Increment the reference count of OPP */
			dev_pm_opp_get(opp);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&opp_table->lock);

	वापस opp;
पूर्ण

/**
 * dev_pm_opp_find_freq_उच्चमान() - Search क्रम an rounded उच्चमान freq
 * @dev:	device क्रम which we करो this operation
 * @freq:	Start frequency
 *
 * Search क्रम the matching उच्चमान *available* OPP from a starting freq
 * क्रम a device.
 *
 * Return: matching *opp and refreshes *freq accordingly, अन्यथा वापसs
 * ERR_PTR in हाल of error and should be handled using IS_ERR. Error वापस
 * values can be:
 * EINVAL:	क्रम bad poपूर्णांकer
 * दुस्फल:	no match found क्रम search
 * ENODEV:	अगर device not found in list of रेजिस्टरed devices
 *
 * The callers are required to call dev_pm_opp_put() क्रम the वापसed OPP after
 * use.
 */
काष्ठा dev_pm_opp *dev_pm_opp_find_freq_उच्चमान(काष्ठा device *dev,
					     अचिन्हित दीर्घ *freq)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा dev_pm_opp *opp;

	अगर (!dev || !freq) अणु
		dev_err(dev, "%s: Invalid argument freq=%p\n", __func__, freq);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table))
		वापस ERR_CAST(opp_table);

	opp = _find_freq_उच्चमान(opp_table, freq);

	dev_pm_opp_put_opp_table(opp_table);

	वापस opp;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_find_freq_उच्चमान);

/**
 * dev_pm_opp_find_freq_न्यूनमान() - Search क्रम a rounded न्यूनमान freq
 * @dev:	device क्रम which we करो this operation
 * @freq:	Start frequency
 *
 * Search क्रम the matching न्यूनमान *available* OPP from a starting freq
 * क्रम a device.
 *
 * Return: matching *opp and refreshes *freq accordingly, अन्यथा वापसs
 * ERR_PTR in हाल of error and should be handled using IS_ERR. Error वापस
 * values can be:
 * EINVAL:	क्रम bad poपूर्णांकer
 * दुस्फल:	no match found क्रम search
 * ENODEV:	अगर device not found in list of रेजिस्टरed devices
 *
 * The callers are required to call dev_pm_opp_put() क्रम the वापसed OPP after
 * use.
 */
काष्ठा dev_pm_opp *dev_pm_opp_find_freq_न्यूनमान(काष्ठा device *dev,
					      अचिन्हित दीर्घ *freq)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा dev_pm_opp *temp_opp, *opp = ERR_PTR(-दुस्फल);

	अगर (!dev || !freq) अणु
		dev_err(dev, "%s: Invalid argument freq=%p\n", __func__, freq);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table))
		वापस ERR_CAST(opp_table);

	mutex_lock(&opp_table->lock);

	list_क्रम_each_entry(temp_opp, &opp_table->opp_list, node) अणु
		अगर (temp_opp->available) अणु
			/* go to the next node, beक्रमe choosing prev */
			अगर (temp_opp->rate > *freq)
				अवरोध;
			अन्यथा
				opp = temp_opp;
		पूर्ण
	पूर्ण

	/* Increment the reference count of OPP */
	अगर (!IS_ERR(opp))
		dev_pm_opp_get(opp);
	mutex_unlock(&opp_table->lock);
	dev_pm_opp_put_opp_table(opp_table);

	अगर (!IS_ERR(opp))
		*freq = opp->rate;

	वापस opp;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_find_freq_न्यूनमान);

/**
 * dev_pm_opp_find_freq_उच्चमान_by_volt() - Find OPP with highest frequency क्रम
 *					 target voltage.
 * @dev:	Device क्रम which we करो this operation.
 * @u_volt:	Target voltage.
 *
 * Search क्रम OPP with highest (उच्चमान) frequency and has voltage <= u_volt.
 *
 * Return: matching *opp, अन्यथा वापसs ERR_PTR in हाल of error which should be
 * handled using IS_ERR.
 *
 * Error वापस values can be:
 * EINVAL:	bad parameters
 *
 * The callers are required to call dev_pm_opp_put() क्रम the वापसed OPP after
 * use.
 */
काष्ठा dev_pm_opp *dev_pm_opp_find_freq_उच्चमान_by_volt(काष्ठा device *dev,
						     अचिन्हित दीर्घ u_volt)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा dev_pm_opp *temp_opp, *opp = ERR_PTR(-दुस्फल);

	अगर (!dev || !u_volt) अणु
		dev_err(dev, "%s: Invalid argument volt=%lu\n", __func__,
			u_volt);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table))
		वापस ERR_CAST(opp_table);

	mutex_lock(&opp_table->lock);

	list_क्रम_each_entry(temp_opp, &opp_table->opp_list, node) अणु
		अगर (temp_opp->available) अणु
			अगर (temp_opp->supplies[0].u_volt > u_volt)
				अवरोध;
			opp = temp_opp;
		पूर्ण
	पूर्ण

	/* Increment the reference count of OPP */
	अगर (!IS_ERR(opp))
		dev_pm_opp_get(opp);

	mutex_unlock(&opp_table->lock);
	dev_pm_opp_put_opp_table(opp_table);

	वापस opp;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_find_freq_उच्चमान_by_volt);

अटल पूर्णांक _set_opp_voltage(काष्ठा device *dev, काष्ठा regulator *reg,
			    काष्ठा dev_pm_opp_supply *supply)
अणु
	पूर्णांक ret;

	/* Regulator not available क्रम device */
	अगर (IS_ERR(reg)) अणु
		dev_dbg(dev, "%s: regulator not available: %ld\n", __func__,
			PTR_ERR(reg));
		वापस 0;
	पूर्ण

	dev_dbg(dev, "%s: voltages (mV): %lu %lu %lu\n", __func__,
		supply->u_volt_min, supply->u_volt, supply->u_volt_max);

	ret = regulator_set_voltage_triplet(reg, supply->u_volt_min,
					    supply->u_volt, supply->u_volt_max);
	अगर (ret)
		dev_err(dev, "%s: failed to set voltage (%lu %lu %lu mV): %d\n",
			__func__, supply->u_volt_min, supply->u_volt,
			supply->u_volt_max, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक _generic_set_opp_clk_only(काष्ठा device *dev, काष्ठा clk *clk,
					    अचिन्हित दीर्घ freq)
अणु
	पूर्णांक ret;

	/* We may reach here क्रम devices which करोn't change frequency */
	अगर (IS_ERR(clk))
		वापस 0;

	ret = clk_set_rate(clk, freq);
	अगर (ret) अणु
		dev_err(dev, "%s: failed to set clock rate: %d\n", __func__,
			ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक _generic_set_opp_regulator(काष्ठा opp_table *opp_table,
				      काष्ठा device *dev,
				      काष्ठा dev_pm_opp *opp,
				      अचिन्हित दीर्घ freq,
				      पूर्णांक scaling_करोwn)
अणु
	काष्ठा regulator *reg = opp_table->regulators[0];
	काष्ठा dev_pm_opp *old_opp = opp_table->current_opp;
	पूर्णांक ret;

	/* This function only supports single regulator per device */
	अगर (WARN_ON(opp_table->regulator_count > 1)) अणु
		dev_err(dev, "multiple regulators are not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Scaling up? Scale voltage beक्रमe frequency */
	अगर (!scaling_करोwn) अणु
		ret = _set_opp_voltage(dev, reg, opp->supplies);
		अगर (ret)
			जाओ restore_voltage;
	पूर्ण

	/* Change frequency */
	ret = _generic_set_opp_clk_only(dev, opp_table->clk, freq);
	अगर (ret)
		जाओ restore_voltage;

	/* Scaling करोwn? Scale voltage after frequency */
	अगर (scaling_करोwn) अणु
		ret = _set_opp_voltage(dev, reg, opp->supplies);
		अगर (ret)
			जाओ restore_freq;
	पूर्ण

	/*
	 * Enable the regulator after setting its voltages, otherwise it अवरोधs
	 * some boot-enabled regulators.
	 */
	अगर (unlikely(!opp_table->enabled)) अणु
		ret = regulator_enable(reg);
		अगर (ret < 0)
			dev_warn(dev, "Failed to enable regulator: %d", ret);
	पूर्ण

	वापस 0;

restore_freq:
	अगर (_generic_set_opp_clk_only(dev, opp_table->clk, old_opp->rate))
		dev_err(dev, "%s: failed to restore old-freq (%lu Hz)\n",
			__func__, old_opp->rate);
restore_voltage:
	/* This shouldn't harm even if the voltages weren't updated earlier */
	_set_opp_voltage(dev, reg, old_opp->supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक _set_opp_bw(स्थिर काष्ठा opp_table *opp_table,
		       काष्ठा dev_pm_opp *opp, काष्ठा device *dev)
अणु
	u32 avg, peak;
	पूर्णांक i, ret;

	अगर (!opp_table->paths)
		वापस 0;

	क्रम (i = 0; i < opp_table->path_count; i++) अणु
		अगर (!opp) अणु
			avg = 0;
			peak = 0;
		पूर्ण अन्यथा अणु
			avg = opp->bandwidth[i].avg;
			peak = opp->bandwidth[i].peak;
		पूर्ण
		ret = icc_set_bw(opp_table->paths[i], avg, peak);
		अगर (ret) अणु
			dev_err(dev, "Failed to %s bandwidth[%d]: %d\n",
				opp ? "set" : "remove", i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _set_opp_custom(स्थिर काष्ठा opp_table *opp_table,
			   काष्ठा device *dev, काष्ठा dev_pm_opp *opp,
			   अचिन्हित दीर्घ freq)
अणु
	काष्ठा dev_pm_set_opp_data *data = opp_table->set_opp_data;
	काष्ठा dev_pm_opp *old_opp = opp_table->current_opp;
	पूर्णांक size;

	/*
	 * We support this only अगर dev_pm_opp_set_regulators() was called
	 * earlier.
	 */
	अगर (opp_table->sod_supplies) अणु
		size = माप(*old_opp->supplies) * opp_table->regulator_count;
		स_नकल(data->old_opp.supplies, old_opp->supplies, size);
		स_नकल(data->new_opp.supplies, opp->supplies, size);
		data->regulator_count = opp_table->regulator_count;
	पूर्ण अन्यथा अणु
		data->regulator_count = 0;
	पूर्ण

	data->regulators = opp_table->regulators;
	data->clk = opp_table->clk;
	data->dev = dev;
	data->old_opp.rate = old_opp->rate;
	data->new_opp.rate = freq;

	वापस opp_table->set_opp(data);
पूर्ण

अटल पूर्णांक _set_required_opp(काष्ठा device *dev, काष्ठा device *pd_dev,
			     काष्ठा dev_pm_opp *opp, पूर्णांक i)
अणु
	अचिन्हित पूर्णांक pstate = likely(opp) ? opp->required_opps[i]->pstate : 0;
	पूर्णांक ret;

	अगर (!pd_dev)
		वापस 0;

	ret = dev_pm_genpd_set_perक्रमmance_state(pd_dev, pstate);
	अगर (ret) अणु
		dev_err(dev, "Failed to set performance rate of %s: %d (%d)\n",
			dev_name(pd_dev), pstate, ret);
	पूर्ण

	वापस ret;
पूर्ण

/* This is only called क्रम PM करोमुख्य क्रम now */
अटल पूर्णांक _set_required_opps(काष्ठा device *dev,
			      काष्ठा opp_table *opp_table,
			      काष्ठा dev_pm_opp *opp, bool up)
अणु
	काष्ठा opp_table **required_opp_tables = opp_table->required_opp_tables;
	काष्ठा device **genpd_virt_devs = opp_table->genpd_virt_devs;
	पूर्णांक i, ret = 0;

	अगर (!required_opp_tables)
		वापस 0;

	/* required-opps not fully initialized yet */
	अगर (lazy_linking_pending(opp_table))
		वापस -EBUSY;

	/* Single genpd हाल */
	अगर (!genpd_virt_devs)
		वापस _set_required_opp(dev, dev, opp, 0);

	/* Multiple genpd हाल */

	/*
	 * Acquire genpd_virt_dev_lock to make sure we करोn't use a genpd_dev
	 * after it is मुक्तd from another thपढ़ो.
	 */
	mutex_lock(&opp_table->genpd_virt_dev_lock);

	/* Scaling up? Set required OPPs in normal order, अन्यथा reverse */
	अगर (up) अणु
		क्रम (i = 0; i < opp_table->required_opp_count; i++) अणु
			ret = _set_required_opp(dev, genpd_virt_devs[i], opp, i);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = opp_table->required_opp_count - 1; i >= 0; i--) अणु
			ret = _set_required_opp(dev, genpd_virt_devs[i], opp, i);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&opp_table->genpd_virt_dev_lock);

	वापस ret;
पूर्ण

अटल व्योम _find_current_opp(काष्ठा device *dev, काष्ठा opp_table *opp_table)
अणु
	काष्ठा dev_pm_opp *opp = ERR_PTR(-ENODEV);
	अचिन्हित दीर्घ freq;

	अगर (!IS_ERR(opp_table->clk)) अणु
		freq = clk_get_rate(opp_table->clk);
		opp = _find_freq_उच्चमान(opp_table, &freq);
	पूर्ण

	/*
	 * Unable to find the current OPP ? Pick the first from the list since
	 * it is in ascending order, otherwise rest of the code will need to
	 * make special checks to validate current_opp.
	 */
	अगर (IS_ERR(opp)) अणु
		mutex_lock(&opp_table->lock);
		opp = list_first_entry(&opp_table->opp_list, काष्ठा dev_pm_opp, node);
		dev_pm_opp_get(opp);
		mutex_unlock(&opp_table->lock);
	पूर्ण

	opp_table->current_opp = opp;
पूर्ण

अटल पूर्णांक _disable_opp_table(काष्ठा device *dev, काष्ठा opp_table *opp_table)
अणु
	पूर्णांक ret;

	अगर (!opp_table->enabled)
		वापस 0;

	/*
	 * Some drivers need to support हालs where some platक्रमms may
	 * have OPP table क्रम the device, जबतक others करोn't and
	 * opp_set_rate() just needs to behave like clk_set_rate().
	 */
	अगर (!_get_opp_count(opp_table))
		वापस 0;

	ret = _set_opp_bw(opp_table, शून्य, dev);
	अगर (ret)
		वापस ret;

	अगर (opp_table->regulators)
		regulator_disable(opp_table->regulators[0]);

	ret = _set_required_opps(dev, opp_table, शून्य, false);

	opp_table->enabled = false;
	वापस ret;
पूर्ण

अटल पूर्णांक _set_opp(काष्ठा device *dev, काष्ठा opp_table *opp_table,
		    काष्ठा dev_pm_opp *opp, अचिन्हित दीर्घ freq)
अणु
	काष्ठा dev_pm_opp *old_opp;
	पूर्णांक scaling_करोwn, ret;

	अगर (unlikely(!opp))
		वापस _disable_opp_table(dev, opp_table);

	/* Find the currently set OPP अगर we करोn't know alपढ़ोy */
	अगर (unlikely(!opp_table->current_opp))
		_find_current_opp(dev, opp_table);

	old_opp = opp_table->current_opp;

	/* Return early अगर nothing to करो */
	अगर (old_opp == opp && opp_table->current_rate == freq &&
	    opp_table->enabled) अणु
		dev_dbg(dev, "%s: OPPs are same, nothing to do\n", __func__);
		वापस 0;
	पूर्ण

	dev_dbg(dev, "%s: switching OPP: Freq %lu -> %lu Hz, Level %u -> %u, Bw %u -> %u\n",
		__func__, opp_table->current_rate, freq, old_opp->level,
		opp->level, old_opp->bandwidth ? old_opp->bandwidth[0].peak : 0,
		opp->bandwidth ? opp->bandwidth[0].peak : 0);

	scaling_करोwn = _opp_compare_key(old_opp, opp);
	अगर (scaling_करोwn == -1)
		scaling_करोwn = 0;

	/* Scaling up? Configure required OPPs beक्रमe frequency */
	अगर (!scaling_करोwn) अणु
		ret = _set_required_opps(dev, opp_table, opp, true);
		अगर (ret) अणु
			dev_err(dev, "Failed to set required opps: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = _set_opp_bw(opp_table, opp, dev);
		अगर (ret) अणु
			dev_err(dev, "Failed to set bw: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (opp_table->set_opp) अणु
		ret = _set_opp_custom(opp_table, dev, opp, freq);
	पूर्ण अन्यथा अगर (opp_table->regulators) अणु
		ret = _generic_set_opp_regulator(opp_table, dev, opp, freq,
						 scaling_करोwn);
	पूर्ण अन्यथा अणु
		/* Only frequency scaling */
		ret = _generic_set_opp_clk_only(dev, opp_table->clk, freq);
	पूर्ण

	अगर (ret)
		वापस ret;

	/* Scaling करोwn? Configure required OPPs after frequency */
	अगर (scaling_करोwn) अणु
		ret = _set_opp_bw(opp_table, opp, dev);
		अगर (ret) अणु
			dev_err(dev, "Failed to set bw: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = _set_required_opps(dev, opp_table, opp, false);
		अगर (ret) अणु
			dev_err(dev, "Failed to set required opps: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	opp_table->enabled = true;
	dev_pm_opp_put(old_opp);

	/* Make sure current_opp करोesn't get मुक्तd */
	dev_pm_opp_get(opp);
	opp_table->current_opp = opp;
	opp_table->current_rate = freq;

	वापस ret;
पूर्ण

/**
 * dev_pm_opp_set_rate() - Configure new OPP based on frequency
 * @dev:	 device क्रम which we करो this operation
 * @target_freq: frequency to achieve
 *
 * This configures the घातer-supplies to the levels specअगरied by the OPP
 * corresponding to the target_freq, and programs the घड़ी to a value <=
 * target_freq, as rounded by clk_round_rate(). Device wanting to run at fmax
 * provided by the opp, should have alपढ़ोy rounded to the target OPP's
 * frequency.
 */
पूर्णांक dev_pm_opp_set_rate(काष्ठा device *dev, अचिन्हित दीर्घ target_freq)
अणु
	काष्ठा opp_table *opp_table;
	अचिन्हित दीर्घ freq = 0, temp_freq;
	काष्ठा dev_pm_opp *opp = शून्य;
	पूर्णांक ret;

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table)) अणु
		dev_err(dev, "%s: device's opp table doesn't exist\n", __func__);
		वापस PTR_ERR(opp_table);
	पूर्ण

	अगर (target_freq) अणु
		/*
		 * For IO devices which require an OPP on some platक्रमms/SoCs
		 * जबतक just needing to scale the घड़ी on some others
		 * we look क्रम empty OPP tables with just a घड़ी handle and
		 * scale only the clk. This makes dev_pm_opp_set_rate()
		 * equivalent to a clk_set_rate()
		 */
		अगर (!_get_opp_count(opp_table)) अणु
			ret = _generic_set_opp_clk_only(dev, opp_table->clk, target_freq);
			जाओ put_opp_table;
		पूर्ण

		freq = clk_round_rate(opp_table->clk, target_freq);
		अगर ((दीर्घ)freq <= 0)
			freq = target_freq;

		/*
		 * The घड़ी driver may support finer resolution of the
		 * frequencies than the OPP table, करोn't update the frequency we
		 * pass to clk_set_rate() here.
		 */
		temp_freq = freq;
		opp = _find_freq_उच्चमान(opp_table, &temp_freq);
		अगर (IS_ERR(opp)) अणु
			ret = PTR_ERR(opp);
			dev_err(dev, "%s: failed to find OPP for freq %lu (%d)\n",
				__func__, freq, ret);
			जाओ put_opp_table;
		पूर्ण
	पूर्ण

	ret = _set_opp(dev, opp_table, opp, freq);

	अगर (target_freq)
		dev_pm_opp_put(opp);
put_opp_table:
	dev_pm_opp_put_opp_table(opp_table);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_set_rate);

/**
 * dev_pm_opp_set_opp() - Configure device क्रम OPP
 * @dev: device क्रम which we करो this operation
 * @opp: OPP to set to
 *
 * This configures the device based on the properties of the OPP passed to this
 * routine.
 *
 * Return: 0 on success, a negative error number otherwise.
 */
पूर्णांक dev_pm_opp_set_opp(काष्ठा device *dev, काष्ठा dev_pm_opp *opp)
अणु
	काष्ठा opp_table *opp_table;
	पूर्णांक ret;

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table)) अणु
		dev_err(dev, "%s: device opp doesn't exist\n", __func__);
		वापस PTR_ERR(opp_table);
	पूर्ण

	ret = _set_opp(dev, opp_table, opp, opp ? opp->rate : 0);
	dev_pm_opp_put_opp_table(opp_table);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_set_opp);

/* OPP-dev Helpers */
अटल व्योम _हटाओ_opp_dev(काष्ठा opp_device *opp_dev,
			    काष्ठा opp_table *opp_table)
अणु
	opp_debug_unरेजिस्टर(opp_dev, opp_table);
	list_del(&opp_dev->node);
	kमुक्त(opp_dev);
पूर्ण

काष्ठा opp_device *_add_opp_dev(स्थिर काष्ठा device *dev,
				काष्ठा opp_table *opp_table)
अणु
	काष्ठा opp_device *opp_dev;

	opp_dev = kzalloc(माप(*opp_dev), GFP_KERNEL);
	अगर (!opp_dev)
		वापस शून्य;

	/* Initialize opp-dev */
	opp_dev->dev = dev;

	mutex_lock(&opp_table->lock);
	list_add(&opp_dev->node, &opp_table->dev_list);
	mutex_unlock(&opp_table->lock);

	/* Create debugfs entries क्रम the opp_table */
	opp_debug_रेजिस्टर(opp_dev, opp_table);

	वापस opp_dev;
पूर्ण

अटल काष्ठा opp_table *_allocate_opp_table(काष्ठा device *dev, पूर्णांक index)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा opp_device *opp_dev;
	पूर्णांक ret;

	/*
	 * Allocate a new OPP table. In the infrequent हाल where a new
	 * device is needed to be added, we pay this penalty.
	 */
	opp_table = kzalloc(माप(*opp_table), GFP_KERNEL);
	अगर (!opp_table)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&opp_table->lock);
	mutex_init(&opp_table->genpd_virt_dev_lock);
	INIT_LIST_HEAD(&opp_table->dev_list);
	INIT_LIST_HEAD(&opp_table->lazy);

	/* Mark regulator count uninitialized */
	opp_table->regulator_count = -1;

	opp_dev = _add_opp_dev(dev, opp_table);
	अगर (!opp_dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	_of_init_opp_table(opp_table, dev, index);

	/* Find पूर्णांकerconnect path(s) क्रम the device */
	ret = dev_pm_opp_of_find_icc_paths(dev, opp_table);
	अगर (ret) अणु
		अगर (ret == -EPROBE_DEFER)
			जाओ हटाओ_opp_dev;

		dev_warn(dev, "%s: Error finding interconnect paths: %d\n",
			 __func__, ret);
	पूर्ण

	BLOCKING_INIT_NOTIFIER_HEAD(&opp_table->head);
	INIT_LIST_HEAD(&opp_table->opp_list);
	kref_init(&opp_table->kref);

	वापस opp_table;

हटाओ_opp_dev:
	_हटाओ_opp_dev(opp_dev, opp_table);
err:
	kमुक्त(opp_table);
	वापस ERR_PTR(ret);
पूर्ण

व्योम _get_opp_table_kref(काष्ठा opp_table *opp_table)
अणु
	kref_get(&opp_table->kref);
पूर्ण

अटल काष्ठा opp_table *_update_opp_table_clk(काष्ठा device *dev,
					       काष्ठा opp_table *opp_table,
					       bool अ_लोlk)
अणु
	पूर्णांक ret;

	/*
	 * Return early अगर we करोn't need to get clk or we have alपढ़ोy tried it
	 * earlier.
	 */
	अगर (!अ_लोlk || IS_ERR(opp_table) || opp_table->clk)
		वापस opp_table;

	/* Find clk क्रम the device */
	opp_table->clk = clk_get(dev, शून्य);

	ret = PTR_ERR_OR_ZERO(opp_table->clk);
	अगर (!ret)
		वापस opp_table;

	अगर (ret == -ENOENT) अणु
		dev_dbg(dev, "%s: Couldn't find clock: %d\n", __func__, ret);
		वापस opp_table;
	पूर्ण

	dev_pm_opp_put_opp_table(opp_table);
	dev_err_probe(dev, ret, "Couldn't find clock\n");

	वापस ERR_PTR(ret);
पूर्ण

/*
 * We need to make sure that the OPP table क्रम a device करोesn't get added twice,
 * अगर this routine माला_लो called in parallel with the same device poपूर्णांकer.
 *
 * The simplest way to enक्रमce that is to perक्रमm everything (find existing
 * table and अगर not found, create a new one) under the opp_table_lock, so only
 * one creator माला_लो access to the same. But that expands the critical section
 * under the lock and may end up causing circular dependencies with frameworks
 * like debugfs, पूर्णांकerconnect or घड़ी framework as they may be direct or
 * indirect users of OPP core.
 *
 * And क्रम that reason we have to go क्रम a bit tricky implementation here, which
 * uses the opp_tables_busy flag to indicate अगर another creator is in the middle
 * of adding an OPP table and others should रुको क्रम it to finish.
 */
काष्ठा opp_table *_add_opp_table_indexed(काष्ठा device *dev, पूर्णांक index,
					 bool अ_लोlk)
अणु
	काष्ठा opp_table *opp_table;

again:
	mutex_lock(&opp_table_lock);

	opp_table = _find_opp_table_unlocked(dev);
	अगर (!IS_ERR(opp_table))
		जाओ unlock;

	/*
	 * The opp_tables list or an OPP table's dev_list is getting updated by
	 * another user, रुको क्रम it to finish.
	 */
	अगर (unlikely(opp_tables_busy)) अणु
		mutex_unlock(&opp_table_lock);
		cpu_relax();
		जाओ again;
	पूर्ण

	opp_tables_busy = true;
	opp_table = _managed_opp(dev, index);

	/* Drop the lock to reduce the size of critical section */
	mutex_unlock(&opp_table_lock);

	अगर (opp_table) अणु
		अगर (!_add_opp_dev(dev, opp_table)) अणु
			dev_pm_opp_put_opp_table(opp_table);
			opp_table = ERR_PTR(-ENOMEM);
		पूर्ण

		mutex_lock(&opp_table_lock);
	पूर्ण अन्यथा अणु
		opp_table = _allocate_opp_table(dev, index);

		mutex_lock(&opp_table_lock);
		अगर (!IS_ERR(opp_table))
			list_add(&opp_table->node, &opp_tables);
	पूर्ण

	opp_tables_busy = false;

unlock:
	mutex_unlock(&opp_table_lock);

	वापस _update_opp_table_clk(dev, opp_table, अ_लोlk);
पूर्ण

अटल काष्ठा opp_table *_add_opp_table(काष्ठा device *dev, bool अ_लोlk)
अणु
	वापस _add_opp_table_indexed(dev, 0, अ_लोlk);
पूर्ण

काष्ठा opp_table *dev_pm_opp_get_opp_table(काष्ठा device *dev)
अणु
	वापस _find_opp_table(dev);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_get_opp_table);

अटल व्योम _opp_table_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा opp_table *opp_table = container_of(kref, काष्ठा opp_table, kref);
	काष्ठा opp_device *opp_dev, *temp;
	पूर्णांक i;

	/* Drop the lock as soon as we can */
	list_del(&opp_table->node);
	mutex_unlock(&opp_table_lock);

	अगर (opp_table->current_opp)
		dev_pm_opp_put(opp_table->current_opp);

	_of_clear_opp_table(opp_table);

	/* Release clk */
	अगर (!IS_ERR(opp_table->clk))
		clk_put(opp_table->clk);

	अगर (opp_table->paths) अणु
		क्रम (i = 0; i < opp_table->path_count; i++)
			icc_put(opp_table->paths[i]);
		kमुक्त(opp_table->paths);
	पूर्ण

	WARN_ON(!list_empty(&opp_table->opp_list));

	list_क्रम_each_entry_safe(opp_dev, temp, &opp_table->dev_list, node) अणु
		/*
		 * The OPP table is getting हटाओd, drop the perक्रमmance state
		 * स्थिरraपूर्णांकs.
		 */
		अगर (opp_table->genpd_perक्रमmance_state)
			dev_pm_genpd_set_perक्रमmance_state((काष्ठा device *)(opp_dev->dev), 0);

		_हटाओ_opp_dev(opp_dev, opp_table);
	पूर्ण

	mutex_destroy(&opp_table->genpd_virt_dev_lock);
	mutex_destroy(&opp_table->lock);
	kमुक्त(opp_table);
पूर्ण

व्योम dev_pm_opp_put_opp_table(काष्ठा opp_table *opp_table)
अणु
	kref_put_mutex(&opp_table->kref, _opp_table_kref_release,
		       &opp_table_lock);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_put_opp_table);

व्योम _opp_मुक्त(काष्ठा dev_pm_opp *opp)
अणु
	kमुक्त(opp);
पूर्ण

अटल व्योम _opp_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा dev_pm_opp *opp = container_of(kref, काष्ठा dev_pm_opp, kref);
	काष्ठा opp_table *opp_table = opp->opp_table;

	list_del(&opp->node);
	mutex_unlock(&opp_table->lock);

	/*
	 * Notअगरy the changes in the availability of the operable
	 * frequency/voltage list.
	 */
	blocking_notअगरier_call_chain(&opp_table->head, OPP_EVENT_REMOVE, opp);
	_of_opp_मुक्त_required_opps(opp_table, opp);
	opp_debug_हटाओ_one(opp);
	kमुक्त(opp);
पूर्ण

व्योम dev_pm_opp_get(काष्ठा dev_pm_opp *opp)
अणु
	kref_get(&opp->kref);
पूर्ण

व्योम dev_pm_opp_put(काष्ठा dev_pm_opp *opp)
अणु
	kref_put_mutex(&opp->kref, _opp_kref_release, &opp->opp_table->lock);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_put);

/**
 * dev_pm_opp_हटाओ()  - Remove an OPP from OPP table
 * @dev:	device क्रम which we करो this operation
 * @freq:	OPP to हटाओ with matching 'freq'
 *
 * This function हटाओs an opp from the opp table.
 */
व्योम dev_pm_opp_हटाओ(काष्ठा device *dev, अचिन्हित दीर्घ freq)
अणु
	काष्ठा dev_pm_opp *opp;
	काष्ठा opp_table *opp_table;
	bool found = false;

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table))
		वापस;

	mutex_lock(&opp_table->lock);

	list_क्रम_each_entry(opp, &opp_table->opp_list, node) अणु
		अगर (opp->rate == freq) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&opp_table->lock);

	अगर (found) अणु
		dev_pm_opp_put(opp);

		/* Drop the reference taken by dev_pm_opp_add() */
		dev_pm_opp_put_opp_table(opp_table);
	पूर्ण अन्यथा अणु
		dev_warn(dev, "%s: Couldn't find OPP with freq: %lu\n",
			 __func__, freq);
	पूर्ण

	/* Drop the reference taken by _find_opp_table() */
	dev_pm_opp_put_opp_table(opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_हटाओ);

अटल काष्ठा dev_pm_opp *_opp_get_next(काष्ठा opp_table *opp_table,
					bool dynamic)
अणु
	काष्ठा dev_pm_opp *opp = शून्य, *temp;

	mutex_lock(&opp_table->lock);
	list_क्रम_each_entry(temp, &opp_table->opp_list, node) अणु
		/*
		 * Refcount must be dropped only once क्रम each OPP by OPP core,
		 * करो that with help of "removed" flag.
		 */
		अगर (!temp->हटाओd && dynamic == temp->dynamic) अणु
			opp = temp;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&opp_table->lock);
	वापस opp;
पूर्ण

/*
 * Can't call dev_pm_opp_put() from under the lock as debugfs removal needs to
 * happen lock less to aव्योम circular dependency issues. This routine must be
 * called without the opp_table->lock held.
 */
अटल व्योम _opp_हटाओ_all(काष्ठा opp_table *opp_table, bool dynamic)
अणु
	काष्ठा dev_pm_opp *opp;

	जबतक ((opp = _opp_get_next(opp_table, dynamic))) अणु
		opp->हटाओd = true;
		dev_pm_opp_put(opp);

		/* Drop the references taken by dev_pm_opp_add() */
		अगर (dynamic)
			dev_pm_opp_put_opp_table(opp_table);
	पूर्ण
पूर्ण

bool _opp_हटाओ_all_अटल(काष्ठा opp_table *opp_table)
अणु
	mutex_lock(&opp_table->lock);

	अगर (!opp_table->parsed_अटल_opps) अणु
		mutex_unlock(&opp_table->lock);
		वापस false;
	पूर्ण

	अगर (--opp_table->parsed_अटल_opps) अणु
		mutex_unlock(&opp_table->lock);
		वापस true;
	पूर्ण

	mutex_unlock(&opp_table->lock);

	_opp_हटाओ_all(opp_table, false);
	वापस true;
पूर्ण

/**
 * dev_pm_opp_हटाओ_all_dynamic() - Remove all dynamically created OPPs
 * @dev:	device क्रम which we करो this operation
 *
 * This function हटाओs all dynamically created OPPs from the opp table.
 */
व्योम dev_pm_opp_हटाओ_all_dynamic(काष्ठा device *dev)
अणु
	काष्ठा opp_table *opp_table;

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table))
		वापस;

	_opp_हटाओ_all(opp_table, true);

	/* Drop the reference taken by _find_opp_table() */
	dev_pm_opp_put_opp_table(opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_हटाओ_all_dynamic);

काष्ठा dev_pm_opp *_opp_allocate(काष्ठा opp_table *table)
अणु
	काष्ठा dev_pm_opp *opp;
	पूर्णांक supply_count, supply_size, icc_size;

	/* Allocate space क्रम at least one supply */
	supply_count = table->regulator_count > 0 ? table->regulator_count : 1;
	supply_size = माप(*opp->supplies) * supply_count;
	icc_size = माप(*opp->bandwidth) * table->path_count;

	/* allocate new OPP node and supplies काष्ठाures */
	opp = kzalloc(माप(*opp) + supply_size + icc_size, GFP_KERNEL);

	अगर (!opp)
		वापस शून्य;

	/* Put the supplies at the end of the OPP काष्ठाure as an empty array */
	opp->supplies = (काष्ठा dev_pm_opp_supply *)(opp + 1);
	अगर (icc_size)
		opp->bandwidth = (काष्ठा dev_pm_opp_icc_bw *)(opp->supplies + supply_count);
	INIT_LIST_HEAD(&opp->node);

	वापस opp;
पूर्ण

अटल bool _opp_supported_by_regulators(काष्ठा dev_pm_opp *opp,
					 काष्ठा opp_table *opp_table)
अणु
	काष्ठा regulator *reg;
	पूर्णांक i;

	अगर (!opp_table->regulators)
		वापस true;

	क्रम (i = 0; i < opp_table->regulator_count; i++) अणु
		reg = opp_table->regulators[i];

		अगर (!regulator_is_supported_voltage(reg,
					opp->supplies[i].u_volt_min,
					opp->supplies[i].u_volt_max)) अणु
			pr_warn("%s: OPP minuV: %lu maxuV: %lu, not supported by regulator\n",
				__func__, opp->supplies[i].u_volt_min,
				opp->supplies[i].u_volt_max);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक _opp_compare_key(काष्ठा dev_pm_opp *opp1, काष्ठा dev_pm_opp *opp2)
अणु
	अगर (opp1->rate != opp2->rate)
		वापस opp1->rate < opp2->rate ? -1 : 1;
	अगर (opp1->bandwidth && opp2->bandwidth &&
	    opp1->bandwidth[0].peak != opp2->bandwidth[0].peak)
		वापस opp1->bandwidth[0].peak < opp2->bandwidth[0].peak ? -1 : 1;
	अगर (opp1->level != opp2->level)
		वापस opp1->level < opp2->level ? -1 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक _opp_is_duplicate(काष्ठा device *dev, काष्ठा dev_pm_opp *new_opp,
			     काष्ठा opp_table *opp_table,
			     काष्ठा list_head **head)
अणु
	काष्ठा dev_pm_opp *opp;
	पूर्णांक opp_cmp;

	/*
	 * Insert new OPP in order of increasing frequency and discard अगर
	 * alपढ़ोy present.
	 *
	 * Need to use &opp_table->opp_list in the condition part of the 'for'
	 * loop, करोn't replace it with head otherwise it will become an infinite
	 * loop.
	 */
	list_क्रम_each_entry(opp, &opp_table->opp_list, node) अणु
		opp_cmp = _opp_compare_key(new_opp, opp);
		अगर (opp_cmp > 0) अणु
			*head = &opp->node;
			जारी;
		पूर्ण

		अगर (opp_cmp < 0)
			वापस 0;

		/* Duplicate OPPs */
		dev_warn(dev, "%s: duplicate OPPs detected. Existing: freq: %lu, volt: %lu, enabled: %d. New: freq: %lu, volt: %lu, enabled: %d\n",
			 __func__, opp->rate, opp->supplies[0].u_volt,
			 opp->available, new_opp->rate,
			 new_opp->supplies[0].u_volt, new_opp->available);

		/* Should we compare voltages क्रम all regulators here ? */
		वापस opp->available &&
		       new_opp->supplies[0].u_volt == opp->supplies[0].u_volt ? -EBUSY : -EEXIST;
	पूर्ण

	वापस 0;
पूर्ण

व्योम _required_opps_available(काष्ठा dev_pm_opp *opp, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		अगर (opp->required_opps[i]->available)
			जारी;

		opp->available = false;
		pr_warn("%s: OPP not supported by required OPP %pOF (%lu)\n",
			 __func__, opp->required_opps[i]->np, opp->rate);
		वापस;
	पूर्ण
पूर्ण

/*
 * Returns:
 * 0: On success. And appropriate error message क्रम duplicate OPPs.
 * -EBUSY: For OPP with same freq/volt and is available. The callers of
 *  _opp_add() must वापस 0 अगर they receive -EBUSY from it. This is to make
 *  sure we करोn't prपूर्णांक error messages unnecessarily अगर dअगरferent parts of
 *  kernel try to initialize the OPP table.
 * -EEXIST: For OPP with same freq but dअगरferent volt or is unavailable. This
 *  should be considered an error by the callers of _opp_add().
 */
पूर्णांक _opp_add(काष्ठा device *dev, काष्ठा dev_pm_opp *new_opp,
	     काष्ठा opp_table *opp_table, bool rate_not_available)
अणु
	काष्ठा list_head *head;
	पूर्णांक ret;

	mutex_lock(&opp_table->lock);
	head = &opp_table->opp_list;

	ret = _opp_is_duplicate(dev, new_opp, opp_table, &head);
	अगर (ret) अणु
		mutex_unlock(&opp_table->lock);
		वापस ret;
	पूर्ण

	list_add(&new_opp->node, head);
	mutex_unlock(&opp_table->lock);

	new_opp->opp_table = opp_table;
	kref_init(&new_opp->kref);

	opp_debug_create_one(new_opp, opp_table);

	अगर (!_opp_supported_by_regulators(new_opp, opp_table)) अणु
		new_opp->available = false;
		dev_warn(dev, "%s: OPP not supported by regulators (%lu)\n",
			 __func__, new_opp->rate);
	पूर्ण

	/* required-opps not fully initialized yet */
	अगर (lazy_linking_pending(opp_table))
		वापस 0;

	_required_opps_available(new_opp, opp_table->required_opp_count);

	वापस 0;
पूर्ण

/**
 * _opp_add_v1() - Allocate a OPP based on v1 bindings.
 * @opp_table:	OPP table
 * @dev:	device क्रम which we करो this operation
 * @freq:	Frequency in Hz क्रम this OPP
 * @u_volt:	Voltage in uVolts क्रम this OPP
 * @dynamic:	Dynamically added OPPs.
 *
 * This function adds an opp definition to the opp table and वापसs status.
 * The opp is made available by शेष and it can be controlled using
 * dev_pm_opp_enable/disable functions and may be हटाओd by dev_pm_opp_हटाओ.
 *
 * NOTE: "dynamic" parameter impacts OPPs added by the dev_pm_opp_of_add_table
 * and मुक्तd by dev_pm_opp_of_हटाओ_table.
 *
 * Return:
 * 0		On success OR
 *		Duplicate OPPs (both freq and volt are same) and opp->available
 * -EEXIST	Freq are same and volt are dअगरferent OR
 *		Duplicate OPPs (both freq and volt are same) and !opp->available
 * -ENOMEM	Memory allocation failure
 */
पूर्णांक _opp_add_v1(काष्ठा opp_table *opp_table, काष्ठा device *dev,
		अचिन्हित दीर्घ freq, दीर्घ u_volt, bool dynamic)
अणु
	काष्ठा dev_pm_opp *new_opp;
	अचिन्हित दीर्घ tol;
	पूर्णांक ret;

	new_opp = _opp_allocate(opp_table);
	अगर (!new_opp)
		वापस -ENOMEM;

	/* populate the opp table */
	new_opp->rate = freq;
	tol = u_volt * opp_table->voltage_tolerance_v1 / 100;
	new_opp->supplies[0].u_volt = u_volt;
	new_opp->supplies[0].u_volt_min = u_volt - tol;
	new_opp->supplies[0].u_volt_max = u_volt + tol;
	new_opp->available = true;
	new_opp->dynamic = dynamic;

	ret = _opp_add(dev, new_opp, opp_table, false);
	अगर (ret) अणु
		/* Don't वापस error क्रम duplicate OPPs */
		अगर (ret == -EBUSY)
			ret = 0;
		जाओ मुक्त_opp;
	पूर्ण

	/*
	 * Notअगरy the changes in the availability of the operable
	 * frequency/voltage list.
	 */
	blocking_notअगरier_call_chain(&opp_table->head, OPP_EVENT_ADD, new_opp);
	वापस 0;

मुक्त_opp:
	_opp_मुक्त(new_opp);

	वापस ret;
पूर्ण

/**
 * dev_pm_opp_set_supported_hw() - Set supported platक्रमms
 * @dev: Device क्रम which supported-hw has to be set.
 * @versions: Array of hierarchy of versions to match.
 * @count: Number of elements in the array.
 *
 * This is required only क्रम the V2 bindings, and it enables a platक्रमm to
 * specअगरy the hierarchy of versions it supports. OPP layer will then enable
 * OPPs, which are available क्रम those versions, based on its 'opp-supported-hw'
 * property.
 */
काष्ठा opp_table *dev_pm_opp_set_supported_hw(काष्ठा device *dev,
			स्थिर u32 *versions, अचिन्हित पूर्णांक count)
अणु
	काष्ठा opp_table *opp_table;

	opp_table = _add_opp_table(dev, false);
	अगर (IS_ERR(opp_table))
		वापस opp_table;

	/* Make sure there are no concurrent पढ़ोers जबतक updating opp_table */
	WARN_ON(!list_empty(&opp_table->opp_list));

	/* Another CPU that shares the OPP table has set the property ? */
	अगर (opp_table->supported_hw)
		वापस opp_table;

	opp_table->supported_hw = kmemdup(versions, count * माप(*versions),
					GFP_KERNEL);
	अगर (!opp_table->supported_hw) अणु
		dev_pm_opp_put_opp_table(opp_table);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	opp_table->supported_hw_count = count;

	वापस opp_table;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_set_supported_hw);

/**
 * dev_pm_opp_put_supported_hw() - Releases resources blocked क्रम supported hw
 * @opp_table: OPP table वापसed by dev_pm_opp_set_supported_hw().
 *
 * This is required only क्रम the V2 bindings, and is called क्रम a matching
 * dev_pm_opp_set_supported_hw(). Until this is called, the opp_table काष्ठाure
 * will not be मुक्तd.
 */
व्योम dev_pm_opp_put_supported_hw(काष्ठा opp_table *opp_table)
अणु
	अगर (unlikely(!opp_table))
		वापस;

	/* Make sure there are no concurrent पढ़ोers जबतक updating opp_table */
	WARN_ON(!list_empty(&opp_table->opp_list));

	kमुक्त(opp_table->supported_hw);
	opp_table->supported_hw = शून्य;
	opp_table->supported_hw_count = 0;

	dev_pm_opp_put_opp_table(opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_put_supported_hw);

अटल व्योम devm_pm_opp_supported_hw_release(व्योम *data)
अणु
	dev_pm_opp_put_supported_hw(data);
पूर्ण

/**
 * devm_pm_opp_set_supported_hw() - Set supported platक्रमms
 * @dev: Device क्रम which supported-hw has to be set.
 * @versions: Array of hierarchy of versions to match.
 * @count: Number of elements in the array.
 *
 * This is a resource-managed variant of dev_pm_opp_set_supported_hw().
 *
 * Return: 0 on success and errorno otherwise.
 */
पूर्णांक devm_pm_opp_set_supported_hw(काष्ठा device *dev, स्थिर u32 *versions,
				 अचिन्हित पूर्णांक count)
अणु
	काष्ठा opp_table *opp_table;

	opp_table = dev_pm_opp_set_supported_hw(dev, versions, count);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	वापस devm_add_action_or_reset(dev, devm_pm_opp_supported_hw_release,
					opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(devm_pm_opp_set_supported_hw);

/**
 * dev_pm_opp_set_prop_name() - Set prop-extn name
 * @dev: Device क्रम which the prop-name has to be set.
 * @name: name to postfix to properties.
 *
 * This is required only क्रम the V2 bindings, and it enables a platक्रमm to
 * specअगरy the extn to be used क्रम certain property names. The properties to
 * which the extension will apply are opp-microvolt and opp-microamp. OPP core
 * should postfix the property name with -<name> जबतक looking क्रम them.
 */
काष्ठा opp_table *dev_pm_opp_set_prop_name(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा opp_table *opp_table;

	opp_table = _add_opp_table(dev, false);
	अगर (IS_ERR(opp_table))
		वापस opp_table;

	/* Make sure there are no concurrent पढ़ोers जबतक updating opp_table */
	WARN_ON(!list_empty(&opp_table->opp_list));

	/* Another CPU that shares the OPP table has set the property ? */
	अगर (opp_table->prop_name)
		वापस opp_table;

	opp_table->prop_name = kstrdup(name, GFP_KERNEL);
	अगर (!opp_table->prop_name) अणु
		dev_pm_opp_put_opp_table(opp_table);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस opp_table;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_set_prop_name);

/**
 * dev_pm_opp_put_prop_name() - Releases resources blocked क्रम prop-name
 * @opp_table: OPP table वापसed by dev_pm_opp_set_prop_name().
 *
 * This is required only क्रम the V2 bindings, and is called क्रम a matching
 * dev_pm_opp_set_prop_name(). Until this is called, the opp_table काष्ठाure
 * will not be मुक्तd.
 */
व्योम dev_pm_opp_put_prop_name(काष्ठा opp_table *opp_table)
अणु
	अगर (unlikely(!opp_table))
		वापस;

	/* Make sure there are no concurrent पढ़ोers जबतक updating opp_table */
	WARN_ON(!list_empty(&opp_table->opp_list));

	kमुक्त(opp_table->prop_name);
	opp_table->prop_name = शून्य;

	dev_pm_opp_put_opp_table(opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_put_prop_name);

/**
 * dev_pm_opp_set_regulators() - Set regulator names क्रम the device
 * @dev: Device क्रम which regulator name is being set.
 * @names: Array of poपूर्णांकers to the names of the regulator.
 * @count: Number of regulators.
 *
 * In order to support OPP चयनing, OPP layer needs to know the name of the
 * device's regulators, as the core would be required to चयन voltages as
 * well.
 *
 * This must be called beक्रमe any OPPs are initialized क्रम the device.
 */
काष्ठा opp_table *dev_pm_opp_set_regulators(काष्ठा device *dev,
					    स्थिर अक्षर * स्थिर names[],
					    अचिन्हित पूर्णांक count)
अणु
	काष्ठा dev_pm_opp_supply *supplies;
	काष्ठा opp_table *opp_table;
	काष्ठा regulator *reg;
	पूर्णांक ret, i;

	opp_table = _add_opp_table(dev, false);
	अगर (IS_ERR(opp_table))
		वापस opp_table;

	/* This should be called beक्रमe OPPs are initialized */
	अगर (WARN_ON(!list_empty(&opp_table->opp_list))) अणु
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	/* Another CPU that shares the OPP table has set the regulators ? */
	अगर (opp_table->regulators)
		वापस opp_table;

	opp_table->regulators = kदो_स्मृति_array(count,
					      माप(*opp_table->regulators),
					      GFP_KERNEL);
	अगर (!opp_table->regulators) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		reg = regulator_get_optional(dev, names[i]);
		अगर (IS_ERR(reg)) अणु
			ret = PTR_ERR(reg);
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "%s: no regulator (%s) found: %d\n",
					__func__, names[i], ret);
			जाओ मुक्त_regulators;
		पूर्ण

		opp_table->regulators[i] = reg;
	पूर्ण

	opp_table->regulator_count = count;

	supplies = kदो_स्मृति_array(count * 2, माप(*supplies), GFP_KERNEL);
	अगर (!supplies) अणु
		ret = -ENOMEM;
		जाओ मुक्त_regulators;
	पूर्ण

	mutex_lock(&opp_table->lock);
	opp_table->sod_supplies = supplies;
	अगर (opp_table->set_opp_data) अणु
		opp_table->set_opp_data->old_opp.supplies = supplies;
		opp_table->set_opp_data->new_opp.supplies = supplies + count;
	पूर्ण
	mutex_unlock(&opp_table->lock);

	वापस opp_table;

मुक्त_regulators:
	जबतक (i != 0)
		regulator_put(opp_table->regulators[--i]);

	kमुक्त(opp_table->regulators);
	opp_table->regulators = शून्य;
	opp_table->regulator_count = -1;
err:
	dev_pm_opp_put_opp_table(opp_table);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_set_regulators);

/**
 * dev_pm_opp_put_regulators() - Releases resources blocked क्रम regulator
 * @opp_table: OPP table वापसed from dev_pm_opp_set_regulators().
 */
व्योम dev_pm_opp_put_regulators(काष्ठा opp_table *opp_table)
अणु
	पूर्णांक i;

	अगर (unlikely(!opp_table))
		वापस;

	अगर (!opp_table->regulators)
		जाओ put_opp_table;

	/* Make sure there are no concurrent पढ़ोers जबतक updating opp_table */
	WARN_ON(!list_empty(&opp_table->opp_list));

	अगर (opp_table->enabled) अणु
		क्रम (i = opp_table->regulator_count - 1; i >= 0; i--)
			regulator_disable(opp_table->regulators[i]);
	पूर्ण

	क्रम (i = opp_table->regulator_count - 1; i >= 0; i--)
		regulator_put(opp_table->regulators[i]);

	mutex_lock(&opp_table->lock);
	अगर (opp_table->set_opp_data) अणु
		opp_table->set_opp_data->old_opp.supplies = शून्य;
		opp_table->set_opp_data->new_opp.supplies = शून्य;
	पूर्ण

	kमुक्त(opp_table->sod_supplies);
	opp_table->sod_supplies = शून्य;
	mutex_unlock(&opp_table->lock);

	kमुक्त(opp_table->regulators);
	opp_table->regulators = शून्य;
	opp_table->regulator_count = -1;

put_opp_table:
	dev_pm_opp_put_opp_table(opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_put_regulators);

अटल व्योम devm_pm_opp_regulators_release(व्योम *data)
अणु
	dev_pm_opp_put_regulators(data);
पूर्ण

/**
 * devm_pm_opp_set_regulators() - Set regulator names क्रम the device
 * @dev: Device क्रम which regulator name is being set.
 * @names: Array of poपूर्णांकers to the names of the regulator.
 * @count: Number of regulators.
 *
 * This is a resource-managed variant of dev_pm_opp_set_regulators().
 *
 * Return: 0 on success and errorno otherwise.
 */
पूर्णांक devm_pm_opp_set_regulators(काष्ठा device *dev,
			       स्थिर अक्षर * स्थिर names[],
			       अचिन्हित पूर्णांक count)
अणु
	काष्ठा opp_table *opp_table;

	opp_table = dev_pm_opp_set_regulators(dev, names, count);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	वापस devm_add_action_or_reset(dev, devm_pm_opp_regulators_release,
					opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(devm_pm_opp_set_regulators);

/**
 * dev_pm_opp_set_clkname() - Set clk name क्रम the device
 * @dev: Device क्रम which clk name is being set.
 * @name: Clk name.
 *
 * In order to support OPP चयनing, OPP layer needs to get poपूर्णांकer to the
 * घड़ी क्रम the device. Simple हालs work fine without using this routine (i.e.
 * by passing connection-id as शून्य), but क्रम a device with multiple घड़ीs
 * available, the OPP core needs to know the exact name of the clk to use.
 *
 * This must be called beक्रमe any OPPs are initialized क्रम the device.
 */
काष्ठा opp_table *dev_pm_opp_set_clkname(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा opp_table *opp_table;
	पूर्णांक ret;

	opp_table = _add_opp_table(dev, false);
	अगर (IS_ERR(opp_table))
		वापस opp_table;

	/* This should be called beक्रमe OPPs are initialized */
	अगर (WARN_ON(!list_empty(&opp_table->opp_list))) अणु
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	/* clk shouldn't be initialized at this poपूर्णांक */
	अगर (WARN_ON(opp_table->clk)) अणु
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	/* Find clk क्रम the device */
	opp_table->clk = clk_get(dev, name);
	अगर (IS_ERR(opp_table->clk)) अणु
		ret = PTR_ERR(opp_table->clk);
		अगर (ret != -EPROBE_DEFER) अणु
			dev_err(dev, "%s: Couldn't find clock: %d\n", __func__,
				ret);
		पूर्ण
		जाओ err;
	पूर्ण

	वापस opp_table;

err:
	dev_pm_opp_put_opp_table(opp_table);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_set_clkname);

/**
 * dev_pm_opp_put_clkname() - Releases resources blocked क्रम clk.
 * @opp_table: OPP table वापसed from dev_pm_opp_set_clkname().
 */
व्योम dev_pm_opp_put_clkname(काष्ठा opp_table *opp_table)
अणु
	अगर (unlikely(!opp_table))
		वापस;

	/* Make sure there are no concurrent पढ़ोers जबतक updating opp_table */
	WARN_ON(!list_empty(&opp_table->opp_list));

	clk_put(opp_table->clk);
	opp_table->clk = ERR_PTR(-EINVAL);

	dev_pm_opp_put_opp_table(opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_put_clkname);

अटल व्योम devm_pm_opp_clkname_release(व्योम *data)
अणु
	dev_pm_opp_put_clkname(data);
पूर्ण

/**
 * devm_pm_opp_set_clkname() - Set clk name क्रम the device
 * @dev: Device क्रम which clk name is being set.
 * @name: Clk name.
 *
 * This is a resource-managed variant of dev_pm_opp_set_clkname().
 *
 * Return: 0 on success and errorno otherwise.
 */
पूर्णांक devm_pm_opp_set_clkname(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा opp_table *opp_table;

	opp_table = dev_pm_opp_set_clkname(dev, name);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	वापस devm_add_action_or_reset(dev, devm_pm_opp_clkname_release,
					opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(devm_pm_opp_set_clkname);

/**
 * dev_pm_opp_रेजिस्टर_set_opp_helper() - Register custom set OPP helper
 * @dev: Device क्रम which the helper is getting रेजिस्टरed.
 * @set_opp: Custom set OPP helper.
 *
 * This is useful to support complex platक्रमms (like platक्रमms with multiple
 * regulators per device), instead of the generic OPP set rate helper.
 *
 * This must be called beक्रमe any OPPs are initialized क्रम the device.
 */
काष्ठा opp_table *dev_pm_opp_रेजिस्टर_set_opp_helper(काष्ठा device *dev,
			पूर्णांक (*set_opp)(काष्ठा dev_pm_set_opp_data *data))
अणु
	काष्ठा dev_pm_set_opp_data *data;
	काष्ठा opp_table *opp_table;

	अगर (!set_opp)
		वापस ERR_PTR(-EINVAL);

	opp_table = _add_opp_table(dev, false);
	अगर (IS_ERR(opp_table))
		वापस opp_table;

	/* This should be called beक्रमe OPPs are initialized */
	अगर (WARN_ON(!list_empty(&opp_table->opp_list))) अणु
		dev_pm_opp_put_opp_table(opp_table);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	/* Another CPU that shares the OPP table has set the helper ? */
	अगर (opp_table->set_opp)
		वापस opp_table;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	mutex_lock(&opp_table->lock);
	opp_table->set_opp_data = data;
	अगर (opp_table->sod_supplies) अणु
		data->old_opp.supplies = opp_table->sod_supplies;
		data->new_opp.supplies = opp_table->sod_supplies +
					 opp_table->regulator_count;
	पूर्ण
	mutex_unlock(&opp_table->lock);

	opp_table->set_opp = set_opp;

	वापस opp_table;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_रेजिस्टर_set_opp_helper);

/**
 * dev_pm_opp_unरेजिस्टर_set_opp_helper() - Releases resources blocked क्रम
 *					   set_opp helper
 * @opp_table: OPP table वापसed from dev_pm_opp_रेजिस्टर_set_opp_helper().
 *
 * Release resources blocked क्रम platक्रमm specअगरic set_opp helper.
 */
व्योम dev_pm_opp_unरेजिस्टर_set_opp_helper(काष्ठा opp_table *opp_table)
अणु
	अगर (unlikely(!opp_table))
		वापस;

	/* Make sure there are no concurrent पढ़ोers जबतक updating opp_table */
	WARN_ON(!list_empty(&opp_table->opp_list));

	opp_table->set_opp = शून्य;

	mutex_lock(&opp_table->lock);
	kमुक्त(opp_table->set_opp_data);
	opp_table->set_opp_data = शून्य;
	mutex_unlock(&opp_table->lock);

	dev_pm_opp_put_opp_table(opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_unरेजिस्टर_set_opp_helper);

अटल व्योम devm_pm_opp_unरेजिस्टर_set_opp_helper(व्योम *data)
अणु
	dev_pm_opp_unरेजिस्टर_set_opp_helper(data);
पूर्ण

/**
 * devm_pm_opp_रेजिस्टर_set_opp_helper() - Register custom set OPP helper
 * @dev: Device क्रम which the helper is getting रेजिस्टरed.
 * @set_opp: Custom set OPP helper.
 *
 * This is a resource-managed version of dev_pm_opp_रेजिस्टर_set_opp_helper().
 *
 * Return: 0 on success and errorno otherwise.
 */
पूर्णांक devm_pm_opp_रेजिस्टर_set_opp_helper(काष्ठा device *dev,
					पूर्णांक (*set_opp)(काष्ठा dev_pm_set_opp_data *data))
अणु
	काष्ठा opp_table *opp_table;

	opp_table = dev_pm_opp_रेजिस्टर_set_opp_helper(dev, set_opp);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	वापस devm_add_action_or_reset(dev, devm_pm_opp_unरेजिस्टर_set_opp_helper,
					opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(devm_pm_opp_रेजिस्टर_set_opp_helper);

अटल व्योम _opp_detach_genpd(काष्ठा opp_table *opp_table)
अणु
	पूर्णांक index;

	अगर (!opp_table->genpd_virt_devs)
		वापस;

	क्रम (index = 0; index < opp_table->required_opp_count; index++) अणु
		अगर (!opp_table->genpd_virt_devs[index])
			जारी;

		dev_pm_करोमुख्य_detach(opp_table->genpd_virt_devs[index], false);
		opp_table->genpd_virt_devs[index] = शून्य;
	पूर्ण

	kमुक्त(opp_table->genpd_virt_devs);
	opp_table->genpd_virt_devs = शून्य;
पूर्ण

/**
 * dev_pm_opp_attach_genpd - Attach genpd(s) क्रम the device and save भव device poपूर्णांकer
 * @dev: Consumer device क्रम which the genpd is getting attached.
 * @names: Null terminated array of poपूर्णांकers containing names of genpd to attach.
 * @virt_devs: Poपूर्णांकer to वापस the array of भव devices.
 *
 * Multiple generic घातer करोमुख्यs क्रम a device are supported with the help of
 * भव genpd devices, which are created क्रम each consumer device - genpd
 * pair. These are the device काष्ठाures which are attached to the घातer करोमुख्य
 * and are required by the OPP core to set the perक्रमmance state of the genpd.
 * The same API also works क्रम the हाल where single genpd is available and so
 * we करोn't need to support that separately.
 *
 * This helper will normally be called by the consumer driver of the device
 * "dev", as only that has details of the genpd names.
 *
 * This helper needs to be called once with a list of all genpd to attach.
 * Otherwise the original device काष्ठाure will be used instead by the OPP core.
 *
 * The order of entries in the names array must match the order in which
 * "required-opps" are added in DT.
 */
काष्ठा opp_table *dev_pm_opp_attach_genpd(काष्ठा device *dev,
		स्थिर अक्षर **names, काष्ठा device ***virt_devs)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा device *virt_dev;
	पूर्णांक index = 0, ret = -EINVAL;
	स्थिर अक्षर **name = names;

	opp_table = _add_opp_table(dev, false);
	अगर (IS_ERR(opp_table))
		वापस opp_table;

	अगर (opp_table->genpd_virt_devs)
		वापस opp_table;

	/*
	 * If the genpd's OPP table isn't alपढ़ोy initialized, parsing of the
	 * required-opps fail क्रम dev. We should retry this after genpd's OPP
	 * table is added.
	 */
	अगर (!opp_table->required_opp_count) अणु
		ret = -EPROBE_DEFER;
		जाओ put_table;
	पूर्ण

	mutex_lock(&opp_table->genpd_virt_dev_lock);

	opp_table->genpd_virt_devs = kसुस्मृति(opp_table->required_opp_count,
					     माप(*opp_table->genpd_virt_devs),
					     GFP_KERNEL);
	अगर (!opp_table->genpd_virt_devs)
		जाओ unlock;

	जबतक (*name) अणु
		अगर (index >= opp_table->required_opp_count) अणु
			dev_err(dev, "Index can't be greater than required-opp-count - 1, %s (%d : %d)\n",
				*name, opp_table->required_opp_count, index);
			जाओ err;
		पूर्ण

		virt_dev = dev_pm_करोमुख्य_attach_by_name(dev, *name);
		अगर (IS_ERR(virt_dev)) अणु
			ret = PTR_ERR(virt_dev);
			dev_err(dev, "Couldn't attach to pm_domain: %d\n", ret);
			जाओ err;
		पूर्ण

		opp_table->genpd_virt_devs[index] = virt_dev;
		index++;
		name++;
	पूर्ण

	अगर (virt_devs)
		*virt_devs = opp_table->genpd_virt_devs;
	mutex_unlock(&opp_table->genpd_virt_dev_lock);

	वापस opp_table;

err:
	_opp_detach_genpd(opp_table);
unlock:
	mutex_unlock(&opp_table->genpd_virt_dev_lock);

put_table:
	dev_pm_opp_put_opp_table(opp_table);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_attach_genpd);

/**
 * dev_pm_opp_detach_genpd() - Detach genpd(s) from the device.
 * @opp_table: OPP table वापसed by dev_pm_opp_attach_genpd().
 *
 * This detaches the genpd(s), resets the भव device poपूर्णांकers, and माला_दो the
 * OPP table.
 */
व्योम dev_pm_opp_detach_genpd(काष्ठा opp_table *opp_table)
अणु
	अगर (unlikely(!opp_table))
		वापस;

	/*
	 * Acquire genpd_virt_dev_lock to make sure virt_dev isn't getting
	 * used in parallel.
	 */
	mutex_lock(&opp_table->genpd_virt_dev_lock);
	_opp_detach_genpd(opp_table);
	mutex_unlock(&opp_table->genpd_virt_dev_lock);

	dev_pm_opp_put_opp_table(opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_detach_genpd);

अटल व्योम devm_pm_opp_detach_genpd(व्योम *data)
अणु
	dev_pm_opp_detach_genpd(data);
पूर्ण

/**
 * devm_pm_opp_attach_genpd - Attach genpd(s) क्रम the device and save भव
 *			      device poपूर्णांकer
 * @dev: Consumer device क्रम which the genpd is getting attached.
 * @names: Null terminated array of poपूर्णांकers containing names of genpd to attach.
 * @virt_devs: Poपूर्णांकer to वापस the array of भव devices.
 *
 * This is a resource-managed version of dev_pm_opp_attach_genpd().
 *
 * Return: 0 on success and errorno otherwise.
 */
पूर्णांक devm_pm_opp_attach_genpd(काष्ठा device *dev, स्थिर अक्षर **names,
			     काष्ठा device ***virt_devs)
अणु
	काष्ठा opp_table *opp_table;

	opp_table = dev_pm_opp_attach_genpd(dev, names, virt_devs);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	वापस devm_add_action_or_reset(dev, devm_pm_opp_detach_genpd,
					opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(devm_pm_opp_attach_genpd);

/**
 * dev_pm_opp_xlate_required_opp() - Find required OPP क्रम @src_table OPP.
 * @src_table: OPP table which has @dst_table as one of its required OPP table.
 * @dst_table: Required OPP table of the @src_table.
 * @src_opp: OPP from the @src_table.
 *
 * This function वापसs the OPP (present in @dst_table) poपूर्णांकed out by the
 * "required-opps" property of the @src_opp (present in @src_table).
 *
 * The callers are required to call dev_pm_opp_put() क्रम the वापसed OPP after
 * use.
 *
 * Return: poपूर्णांकer to 'struct dev_pm_opp' on success and errorno otherwise.
 */
काष्ठा dev_pm_opp *dev_pm_opp_xlate_required_opp(काष्ठा opp_table *src_table,
						 काष्ठा opp_table *dst_table,
						 काष्ठा dev_pm_opp *src_opp)
अणु
	काष्ठा dev_pm_opp *opp, *dest_opp = ERR_PTR(-ENODEV);
	पूर्णांक i;

	अगर (!src_table || !dst_table || !src_opp ||
	    !src_table->required_opp_tables)
		वापस ERR_PTR(-EINVAL);

	/* required-opps not fully initialized yet */
	अगर (lazy_linking_pending(src_table))
		वापस ERR_PTR(-EBUSY);

	क्रम (i = 0; i < src_table->required_opp_count; i++) अणु
		अगर (src_table->required_opp_tables[i] == dst_table) अणु
			mutex_lock(&src_table->lock);

			list_क्रम_each_entry(opp, &src_table->opp_list, node) अणु
				अगर (opp == src_opp) अणु
					dest_opp = opp->required_opps[i];
					dev_pm_opp_get(dest_opp);
					अवरोध;
				पूर्ण
			पूर्ण

			mutex_unlock(&src_table->lock);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (IS_ERR(dest_opp)) अणु
		pr_err("%s: Couldn't find matching OPP (%p: %p)\n", __func__,
		       src_table, dst_table);
	पूर्ण

	वापस dest_opp;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_xlate_required_opp);

/**
 * dev_pm_opp_xlate_perक्रमmance_state() - Find required OPP's pstate क्रम src_table.
 * @src_table: OPP table which has dst_table as one of its required OPP table.
 * @dst_table: Required OPP table of the src_table.
 * @pstate: Current perक्रमmance state of the src_table.
 *
 * This Returns pstate of the OPP (present in @dst_table) poपूर्णांकed out by the
 * "required-opps" property of the OPP (present in @src_table) which has
 * perक्रमmance state set to @pstate.
 *
 * Return: Zero or positive perक्रमmance state on success, otherwise negative
 * value on errors.
 */
पूर्णांक dev_pm_opp_xlate_perक्रमmance_state(काष्ठा opp_table *src_table,
				       काष्ठा opp_table *dst_table,
				       अचिन्हित पूर्णांक pstate)
अणु
	काष्ठा dev_pm_opp *opp;
	पूर्णांक dest_pstate = -EINVAL;
	पूर्णांक i;

	/*
	 * Normally the src_table will have the "required_opps" property set to
	 * poपूर्णांक to one of the OPPs in the dst_table, but in some हालs the
	 * genpd and its master have one to one mapping of perक्रमmance states
	 * and so none of them have the "required-opps" property set. Return the
	 * pstate of the src_table as it is in such हालs.
	 */
	अगर (!src_table || !src_table->required_opp_count)
		वापस pstate;

	/* required-opps not fully initialized yet */
	अगर (lazy_linking_pending(src_table))
		वापस -EBUSY;

	क्रम (i = 0; i < src_table->required_opp_count; i++) अणु
		अगर (src_table->required_opp_tables[i]->np == dst_table->np)
			अवरोध;
	पूर्ण

	अगर (unlikely(i == src_table->required_opp_count)) अणु
		pr_err("%s: Couldn't find matching OPP table (%p: %p)\n",
		       __func__, src_table, dst_table);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&src_table->lock);

	list_क्रम_each_entry(opp, &src_table->opp_list, node) अणु
		अगर (opp->pstate == pstate) अणु
			dest_pstate = opp->required_opps[i]->pstate;
			जाओ unlock;
		पूर्ण
	पूर्ण

	pr_err("%s: Couldn't find matching OPP (%p: %p)\n", __func__, src_table,
	       dst_table);

unlock:
	mutex_unlock(&src_table->lock);

	वापस dest_pstate;
पूर्ण

/**
 * dev_pm_opp_add()  - Add an OPP table from a table definitions
 * @dev:	device क्रम which we करो this operation
 * @freq:	Frequency in Hz क्रम this OPP
 * @u_volt:	Voltage in uVolts क्रम this OPP
 *
 * This function adds an opp definition to the opp table and वापसs status.
 * The opp is made available by शेष and it can be controlled using
 * dev_pm_opp_enable/disable functions.
 *
 * Return:
 * 0		On success OR
 *		Duplicate OPPs (both freq and volt are same) and opp->available
 * -EEXIST	Freq are same and volt are dअगरferent OR
 *		Duplicate OPPs (both freq and volt are same) and !opp->available
 * -ENOMEM	Memory allocation failure
 */
पूर्णांक dev_pm_opp_add(काष्ठा device *dev, अचिन्हित दीर्घ freq, अचिन्हित दीर्घ u_volt)
अणु
	काष्ठा opp_table *opp_table;
	पूर्णांक ret;

	opp_table = _add_opp_table(dev, true);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	/* Fix regulator count क्रम dynamic OPPs */
	opp_table->regulator_count = 1;

	ret = _opp_add_v1(opp_table, dev, freq, u_volt, true);
	अगर (ret)
		dev_pm_opp_put_opp_table(opp_table);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_add);

/**
 * _opp_set_availability() - helper to set the availability of an opp
 * @dev:		device क्रम which we करो this operation
 * @freq:		OPP frequency to modअगरy availability
 * @availability_req:	availability status requested क्रम this opp
 *
 * Set the availability of an OPP, opp_अणुenable,disableपूर्ण share a common logic
 * which is isolated here.
 *
 * Return: -EINVAL क्रम bad poपूर्णांकers, -ENOMEM अगर no memory available क्रम the
 * copy operation, वापसs 0 अगर no modअगरication was करोne OR modअगरication was
 * successful.
 */
अटल पूर्णांक _opp_set_availability(काष्ठा device *dev, अचिन्हित दीर्घ freq,
				 bool availability_req)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा dev_pm_opp *पंचांगp_opp, *opp = ERR_PTR(-ENODEV);
	पूर्णांक r = 0;

	/* Find the opp_table */
	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table)) अणु
		r = PTR_ERR(opp_table);
		dev_warn(dev, "%s: Device OPP not found (%d)\n", __func__, r);
		वापस r;
	पूर्ण

	mutex_lock(&opp_table->lock);

	/* Do we have the frequency? */
	list_क्रम_each_entry(पंचांगp_opp, &opp_table->opp_list, node) अणु
		अगर (पंचांगp_opp->rate == freq) अणु
			opp = पंचांगp_opp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (IS_ERR(opp)) अणु
		r = PTR_ERR(opp);
		जाओ unlock;
	पूर्ण

	/* Is update really needed? */
	अगर (opp->available == availability_req)
		जाओ unlock;

	opp->available = availability_req;

	dev_pm_opp_get(opp);
	mutex_unlock(&opp_table->lock);

	/* Notअगरy the change of the OPP availability */
	अगर (availability_req)
		blocking_notअगरier_call_chain(&opp_table->head, OPP_EVENT_ENABLE,
					     opp);
	अन्यथा
		blocking_notअगरier_call_chain(&opp_table->head,
					     OPP_EVENT_DISABLE, opp);

	dev_pm_opp_put(opp);
	जाओ put_table;

unlock:
	mutex_unlock(&opp_table->lock);
put_table:
	dev_pm_opp_put_opp_table(opp_table);
	वापस r;
पूर्ण

/**
 * dev_pm_opp_adjust_voltage() - helper to change the voltage of an OPP
 * @dev:		device क्रम which we करो this operation
 * @freq:		OPP frequency to adjust voltage of
 * @u_volt:		new OPP target voltage
 * @u_volt_min:		new OPP min voltage
 * @u_volt_max:		new OPP max voltage
 *
 * Return: -EINVAL क्रम bad poपूर्णांकers, -ENOMEM अगर no memory available क्रम the
 * copy operation, वापसs 0 अगर no modअगरcation was करोne OR modअगरication was
 * successful.
 */
पूर्णांक dev_pm_opp_adjust_voltage(काष्ठा device *dev, अचिन्हित दीर्घ freq,
			      अचिन्हित दीर्घ u_volt, अचिन्हित दीर्घ u_volt_min,
			      अचिन्हित दीर्घ u_volt_max)

अणु
	काष्ठा opp_table *opp_table;
	काष्ठा dev_pm_opp *पंचांगp_opp, *opp = ERR_PTR(-ENODEV);
	पूर्णांक r = 0;

	/* Find the opp_table */
	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table)) अणु
		r = PTR_ERR(opp_table);
		dev_warn(dev, "%s: Device OPP not found (%d)\n", __func__, r);
		वापस r;
	पूर्ण

	mutex_lock(&opp_table->lock);

	/* Do we have the frequency? */
	list_क्रम_each_entry(पंचांगp_opp, &opp_table->opp_list, node) अणु
		अगर (पंचांगp_opp->rate == freq) अणु
			opp = पंचांगp_opp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (IS_ERR(opp)) अणु
		r = PTR_ERR(opp);
		जाओ adjust_unlock;
	पूर्ण

	/* Is update really needed? */
	अगर (opp->supplies->u_volt == u_volt)
		जाओ adjust_unlock;

	opp->supplies->u_volt = u_volt;
	opp->supplies->u_volt_min = u_volt_min;
	opp->supplies->u_volt_max = u_volt_max;

	dev_pm_opp_get(opp);
	mutex_unlock(&opp_table->lock);

	/* Notअगरy the voltage change of the OPP */
	blocking_notअगरier_call_chain(&opp_table->head, OPP_EVENT_ADJUST_VOLTAGE,
				     opp);

	dev_pm_opp_put(opp);
	जाओ adjust_put_table;

adjust_unlock:
	mutex_unlock(&opp_table->lock);
adjust_put_table:
	dev_pm_opp_put_opp_table(opp_table);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_adjust_voltage);

/**
 * dev_pm_opp_enable() - Enable a specअगरic OPP
 * @dev:	device क्रम which we करो this operation
 * @freq:	OPP frequency to enable
 *
 * Enables a provided opp. If the operation is valid, this वापसs 0, अन्यथा the
 * corresponding error value. It is meant to be used क्रम users an OPP available
 * after being temporarily made unavailable with dev_pm_opp_disable.
 *
 * Return: -EINVAL क्रम bad poपूर्णांकers, -ENOMEM अगर no memory available क्रम the
 * copy operation, वापसs 0 अगर no modअगरication was करोne OR modअगरication was
 * successful.
 */
पूर्णांक dev_pm_opp_enable(काष्ठा device *dev, अचिन्हित दीर्घ freq)
अणु
	वापस _opp_set_availability(dev, freq, true);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_enable);

/**
 * dev_pm_opp_disable() - Disable a specअगरic OPP
 * @dev:	device क्रम which we करो this operation
 * @freq:	OPP frequency to disable
 *
 * Disables a provided opp. If the operation is valid, this वापसs
 * 0, अन्यथा the corresponding error value. It is meant to be a temporary
 * control by users to make this OPP not available until the circumstances are
 * right to make it available again (with a call to dev_pm_opp_enable).
 *
 * Return: -EINVAL क्रम bad poपूर्णांकers, -ENOMEM अगर no memory available क्रम the
 * copy operation, वापसs 0 अगर no modअगरication was करोne OR modअगरication was
 * successful.
 */
पूर्णांक dev_pm_opp_disable(काष्ठा device *dev, अचिन्हित दीर्घ freq)
अणु
	वापस _opp_set_availability(dev, freq, false);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_disable);

/**
 * dev_pm_opp_रेजिस्टर_notअगरier() - Register OPP notअगरier क्रम the device
 * @dev:	Device क्रम which notअगरier needs to be रेजिस्टरed
 * @nb:		Notअगरier block to be रेजिस्टरed
 *
 * Return: 0 on success or a negative error value.
 */
पूर्णांक dev_pm_opp_रेजिस्टर_notअगरier(काष्ठा device *dev, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा opp_table *opp_table;
	पूर्णांक ret;

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	ret = blocking_notअगरier_chain_रेजिस्टर(&opp_table->head, nb);

	dev_pm_opp_put_opp_table(opp_table);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dev_pm_opp_रेजिस्टर_notअगरier);

/**
 * dev_pm_opp_unरेजिस्टर_notअगरier() - Unरेजिस्टर OPP notअगरier क्रम the device
 * @dev:	Device क्रम which notअगरier needs to be unरेजिस्टरed
 * @nb:		Notअगरier block to be unरेजिस्टरed
 *
 * Return: 0 on success or a negative error value.
 */
पूर्णांक dev_pm_opp_unरेजिस्टर_notअगरier(काष्ठा device *dev,
				   काष्ठा notअगरier_block *nb)
अणु
	काष्ठा opp_table *opp_table;
	पूर्णांक ret;

	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	ret = blocking_notअगरier_chain_unरेजिस्टर(&opp_table->head, nb);

	dev_pm_opp_put_opp_table(opp_table);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dev_pm_opp_unरेजिस्टर_notअगरier);

/**
 * dev_pm_opp_हटाओ_table() - Free all OPPs associated with the device
 * @dev:	device poपूर्णांकer used to lookup OPP table.
 *
 * Free both OPPs created using अटल entries present in DT and the
 * dynamically added entries.
 */
व्योम dev_pm_opp_हटाओ_table(काष्ठा device *dev)
अणु
	काष्ठा opp_table *opp_table;

	/* Check क्रम existing table क्रम 'dev' */
	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table)) अणु
		पूर्णांक error = PTR_ERR(opp_table);

		अगर (error != -ENODEV)
			WARN(1, "%s: opp_table: %d\n",
			     IS_ERR_OR_शून्य(dev) ?
					"Invalid device" : dev_name(dev),
			     error);
		वापस;
	पूर्ण

	/*
	 * Drop the extra reference only अगर the OPP table was successfully added
	 * with dev_pm_opp_of_add_table() earlier.
	 **/
	अगर (_opp_हटाओ_all_अटल(opp_table))
		dev_pm_opp_put_opp_table(opp_table);

	/* Drop reference taken by _find_opp_table() */
	dev_pm_opp_put_opp_table(opp_table);
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_हटाओ_table);

/**
 * dev_pm_opp_sync_regulators() - Sync state of voltage regulators
 * @dev:	device क्रम which we करो this operation
 *
 * Sync voltage state of the OPP table regulators.
 *
 * Return: 0 on success or a negative error value.
 */
पूर्णांक dev_pm_opp_sync_regulators(काष्ठा device *dev)
अणु
	काष्ठा opp_table *opp_table;
	काष्ठा regulator *reg;
	पूर्णांक i, ret = 0;

	/* Device may not have OPP table */
	opp_table = _find_opp_table(dev);
	अगर (IS_ERR(opp_table))
		वापस 0;

	/* Regulator may not be required क्रम the device */
	अगर (unlikely(!opp_table->regulators))
		जाओ put_table;

	/* Nothing to sync अगर voltage wasn't changed */
	अगर (!opp_table->enabled)
		जाओ put_table;

	क्रम (i = 0; i < opp_table->regulator_count; i++) अणु
		reg = opp_table->regulators[i];
		ret = regulator_sync_voltage(reg);
		अगर (ret)
			अवरोध;
	पूर्ण
put_table:
	/* Drop reference taken by _find_opp_table() */
	dev_pm_opp_put_opp_table(opp_table);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dev_pm_opp_sync_regulators);
