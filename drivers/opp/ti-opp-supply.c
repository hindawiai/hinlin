<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016-2017 Texas Instruments Incorporated - https://www.ti.com/
 *	Nishanth Menon <nm@ti.com>
 *	Dave Gerlach <d-gerlach@ti.com>
 *
 * TI OPP supply driver that provides override पूर्णांकo the regulator control
 * क्रम generic opp core to handle devices with ABB regulator and/or
 * SmartReflex Class0.
 */
#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

/**
 * काष्ठा ti_opp_supply_optimum_voltage_table - optimized voltage table
 * @reference_uv:	reference voltage (usually Nominal voltage)
 * @optimized_uv:	Optimized voltage from efuse
 */
काष्ठा ti_opp_supply_optimum_voltage_table अणु
	अचिन्हित पूर्णांक reference_uv;
	अचिन्हित पूर्णांक optimized_uv;
पूर्ण;

/**
 * काष्ठा ti_opp_supply_data - OMAP specअगरic opp supply data
 * @vdd_table:	Optimized voltage mapping table
 * @num_vdd_table: number of entries in vdd_table
 * @vdd_असलolute_max_voltage_uv: असलolute maximum voltage in UV क्रम the supply
 */
काष्ठा ti_opp_supply_data अणु
	काष्ठा ti_opp_supply_optimum_voltage_table *vdd_table;
	u32 num_vdd_table;
	u32 vdd_असलolute_max_voltage_uv;
पूर्ण;

अटल काष्ठा ti_opp_supply_data opp_data;

/**
 * काष्ठा ti_opp_supply_of_data - device tree match data
 * @flags:	specअगरic type of opp supply
 * @efuse_voltage_mask: mask required क्रम efuse रेजिस्टर representing voltage
 * @efuse_voltage_uv: Are the efuse entries in micro-volts? अगर not, assume
 *		milli-volts.
 */
काष्ठा ti_opp_supply_of_data अणु
#घोषणा OPPDM_EFUSE_CLASS0_OPTIMIZED_VOLTAGE	BIT(1)
#घोषणा OPPDM_HAS_NO_ABB			BIT(2)
	स्थिर u8 flags;
	स्थिर u32 efuse_voltage_mask;
	स्थिर bool efuse_voltage_uv;
पूर्ण;

/**
 * _store_optimized_voltages() - store optimized voltages
 * @dev:	ti opp supply device क्रम which we need to store info
 * @data:	data specअगरic to the device
 *
 * Picks up efuse based optimized voltages क्रम VDD unique per device and
 * stores it in पूर्णांकernal data काष्ठाure क्रम use during transition requests.
 *
 * Return: If successful, 0, अन्यथा appropriate error value.
 */
अटल पूर्णांक _store_optimized_voltages(काष्ठा device *dev,
				     काष्ठा ti_opp_supply_data *data)
अणु
	व्योम __iomem *base;
	काष्ठा property *prop;
	काष्ठा resource *res;
	स्थिर __be32 *val;
	पूर्णांक proplen, i;
	पूर्णांक ret = 0;
	काष्ठा ti_opp_supply_optimum_voltage_table *table;
	स्थिर काष्ठा ti_opp_supply_of_data *of_data = dev_get_drvdata(dev);

	/* pick up Efuse based voltages */
	res = platक्रमm_get_resource(to_platक्रमm_device(dev), IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "Unable to get IO resource\n");
		ret = -ENODEV;
		जाओ out_map;
	पूर्ण

	base = ioremap(res->start, resource_size(res));
	अगर (!base) अणु
		dev_err(dev, "Unable to map Efuse registers\n");
		ret = -ENOMEM;
		जाओ out_map;
	पूर्ण

	/* Fetch efuse-settings. */
	prop = of_find_property(dev->of_node, "ti,efuse-settings", शून्य);
	अगर (!prop) अणु
		dev_err(dev, "No 'ti,efuse-settings' property found\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	proplen = prop->length / माप(पूर्णांक);
	data->num_vdd_table = proplen / 2;
	/* Verअगरy क्रम corrupted OPP entries in dt */
	अगर (data->num_vdd_table * 2 * माप(पूर्णांक) != prop->length) अणु
		dev_err(dev, "Invalid 'ti,efuse-settings'\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "ti,absolute-max-voltage-uv",
				   &data->vdd_असलolute_max_voltage_uv);
	अगर (ret) अणु
		dev_err(dev, "ti,absolute-max-voltage-uv is missing\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	table = kसुस्मृति(data->num_vdd_table, माप(*data->vdd_table),
			GFP_KERNEL);
	अगर (!table) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	data->vdd_table = table;

	val = prop->value;
	क्रम (i = 0; i < data->num_vdd_table; i++, table++) अणु
		u32 efuse_offset;
		u32 पंचांगp;

		table->reference_uv = be32_to_cpup(val++);
		efuse_offset = be32_to_cpup(val++);

		पंचांगp = पढ़ोl(base + efuse_offset);
		पंचांगp &= of_data->efuse_voltage_mask;
		पंचांगp >>= __ffs(of_data->efuse_voltage_mask);

		table->optimized_uv = of_data->efuse_voltage_uv ? पंचांगp :
					पंचांगp * 1000;

		dev_dbg(dev, "[%d] efuse=0x%08x volt_table=%d vset=%d\n",
			i, efuse_offset, table->reference_uv,
			table->optimized_uv);

		/*
		 * Some older samples might not have optimized efuse
		 * Use reference voltage क्रम those - just add debug message
		 * क्रम them.
		 */
		अगर (!table->optimized_uv) अणु
			dev_dbg(dev, "[%d] efuse=0x%08x volt_table=%d:vset0\n",
				i, efuse_offset, table->reference_uv);
			table->optimized_uv = table->reference_uv;
		पूर्ण
	पूर्ण
out:
	iounmap(base);
out_map:
	वापस ret;
पूर्ण

/**
 * _मुक्त_optimized_voltages() - मुक्त resources क्रम optvoltages
 * @dev:	device क्रम which we need to मुक्त info
 * @data:	data specअगरic to the device
 */
अटल व्योम _मुक्त_optimized_voltages(काष्ठा device *dev,
				     काष्ठा ti_opp_supply_data *data)
अणु
	kमुक्त(data->vdd_table);
	data->vdd_table = शून्य;
	data->num_vdd_table = 0;
पूर्ण

/**
 * _get_optimal_vdd_voltage() - Finds optimal voltage क्रम the supply
 * @dev:	device क्रम which we need to find info
 * @data:	data specअगरic to the device
 * @reference_uv:	reference voltage (OPP voltage) क्रम which we need value
 *
 * Return: अगर a match is found, वापस optimized voltage, अन्यथा वापस
 * reference_uv, also वापस reference_uv अगर no optimization is needed.
 */
अटल पूर्णांक _get_optimal_vdd_voltage(काष्ठा device *dev,
				    काष्ठा ti_opp_supply_data *data,
				    पूर्णांक reference_uv)
अणु
	पूर्णांक i;
	काष्ठा ti_opp_supply_optimum_voltage_table *table;

	अगर (!data->num_vdd_table)
		वापस reference_uv;

	table = data->vdd_table;
	अगर (!table)
		वापस -EINVAL;

	/* Find a exact match - this list is usually very small */
	क्रम (i = 0; i < data->num_vdd_table; i++, table++)
		अगर (table->reference_uv == reference_uv)
			वापस table->optimized_uv;

	/* IF things are screwed up, we'd make a mess on console.. ratelimit */
	dev_err_ratelimited(dev, "%s: Failed optimized voltage match for %d\n",
			    __func__, reference_uv);
	वापस reference_uv;
पूर्ण

अटल पूर्णांक _opp_set_voltage(काष्ठा device *dev,
			    काष्ठा dev_pm_opp_supply *supply,
			    पूर्णांक new_target_uv, काष्ठा regulator *reg,
			    अक्षर *reg_name)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ vdd_uv, uv_max;

	अगर (new_target_uv)
		vdd_uv = new_target_uv;
	अन्यथा
		vdd_uv = supply->u_volt;

	/*
	 * If we करो have an असलolute max voltage specअगरied, then we should
	 * use that voltage instead to allow क्रम हालs where the voltage rails
	 * are ganged (example अगर we set the max क्रम an opp as 1.12v, and
	 * the असलolute max is 1.5v, क्रम another rail to get 1.25v, it cannot
	 * be achieved अगर the regulator is स्थिरraपूर्णांकed to max of 1.12v, even
	 * अगर it can function at 1.25v
	 */
	अगर (opp_data.vdd_असलolute_max_voltage_uv)
		uv_max = opp_data.vdd_असलolute_max_voltage_uv;
	अन्यथा
		uv_max = supply->u_volt_max;

	अगर (vdd_uv > uv_max ||
	    vdd_uv < supply->u_volt_min ||
	    supply->u_volt_min > uv_max) अणु
		dev_warn(dev,
			 "Invalid range voltages [Min:%lu target:%lu Max:%lu]\n",
			 supply->u_volt_min, vdd_uv, uv_max);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "%s scaling to %luuV[min %luuV max %luuV]\n", reg_name,
		vdd_uv, supply->u_volt_min,
		uv_max);

	ret = regulator_set_voltage_triplet(reg,
					    supply->u_volt_min,
					    vdd_uv,
					    uv_max);
	अगर (ret) अणु
		dev_err(dev, "%s failed for %luuV[min %luuV max %luuV]\n",
			reg_name, vdd_uv, supply->u_volt_min,
			uv_max);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ti_opp_supply_set_opp() - करो the opp supply transition
 * @data:	inक्रमmation on regulators and new and old opps provided by
 *		opp core to use in transition
 *
 * Return: If successful, 0, अन्यथा appropriate error value.
 */
अटल पूर्णांक ti_opp_supply_set_opp(काष्ठा dev_pm_set_opp_data *data)
अणु
	काष्ठा dev_pm_opp_supply *old_supply_vdd = &data->old_opp.supplies[0];
	काष्ठा dev_pm_opp_supply *old_supply_vbb = &data->old_opp.supplies[1];
	काष्ठा dev_pm_opp_supply *new_supply_vdd = &data->new_opp.supplies[0];
	काष्ठा dev_pm_opp_supply *new_supply_vbb = &data->new_opp.supplies[1];
	काष्ठा device *dev = data->dev;
	अचिन्हित दीर्घ old_freq = data->old_opp.rate, freq = data->new_opp.rate;
	काष्ठा clk *clk = data->clk;
	काष्ठा regulator *vdd_reg = data->regulators[0];
	काष्ठा regulator *vbb_reg = data->regulators[1];
	पूर्णांक vdd_uv;
	पूर्णांक ret;

	vdd_uv = _get_optimal_vdd_voltage(dev, &opp_data,
					  new_supply_vdd->u_volt);

	अगर (new_supply_vdd->u_volt_min < vdd_uv)
		new_supply_vdd->u_volt_min = vdd_uv;

	/* Scaling up? Scale voltage beक्रमe frequency */
	अगर (freq > old_freq) अणु
		ret = _opp_set_voltage(dev, new_supply_vdd, vdd_uv, vdd_reg,
				       "vdd");
		अगर (ret)
			जाओ restore_voltage;

		ret = _opp_set_voltage(dev, new_supply_vbb, 0, vbb_reg, "vbb");
		अगर (ret)
			जाओ restore_voltage;
	पूर्ण

	/* Change frequency */
	dev_dbg(dev, "%s: switching OPP: %lu Hz --> %lu Hz\n",
		__func__, old_freq, freq);

	ret = clk_set_rate(clk, freq);
	अगर (ret) अणु
		dev_err(dev, "%s: failed to set clock rate: %d\n", __func__,
			ret);
		जाओ restore_voltage;
	पूर्ण

	/* Scaling करोwn? Scale voltage after frequency */
	अगर (freq < old_freq) अणु
		ret = _opp_set_voltage(dev, new_supply_vbb, 0, vbb_reg, "vbb");
		अगर (ret)
			जाओ restore_freq;

		ret = _opp_set_voltage(dev, new_supply_vdd, vdd_uv, vdd_reg,
				       "vdd");
		अगर (ret)
			जाओ restore_freq;
	पूर्ण

	वापस 0;

restore_freq:
	ret = clk_set_rate(clk, old_freq);
	अगर (ret)
		dev_err(dev, "%s: failed to restore old-freq (%lu Hz)\n",
			__func__, old_freq);
restore_voltage:
	/* This shouldn't harm even if the voltages weren't updated earlier */
	अगर (old_supply_vdd->u_volt) अणु
		ret = _opp_set_voltage(dev, old_supply_vbb, 0, vbb_reg, "vbb");
		अगर (ret)
			वापस ret;

		ret = _opp_set_voltage(dev, old_supply_vdd, 0, vdd_reg,
				       "vdd");
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ti_opp_supply_of_data omap_generic_of_data = अणु
पूर्ण;

अटल स्थिर काष्ठा ti_opp_supply_of_data omap_omap5_of_data = अणु
	.flags = OPPDM_EFUSE_CLASS0_OPTIMIZED_VOLTAGE,
	.efuse_voltage_mask = 0xFFF,
	.efuse_voltage_uv = false,
पूर्ण;

अटल स्थिर काष्ठा ti_opp_supply_of_data omap_omap5core_of_data = अणु
	.flags = OPPDM_EFUSE_CLASS0_OPTIMIZED_VOLTAGE | OPPDM_HAS_NO_ABB,
	.efuse_voltage_mask = 0xFFF,
	.efuse_voltage_uv = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ti_opp_supply_of_match[] = अणु
	अणु.compatible = "ti,omap-opp-supply", .data = &omap_generic_of_dataपूर्ण,
	अणु.compatible = "ti,omap5-opp-supply", .data = &omap_omap5_of_dataपूर्ण,
	अणु.compatible = "ti,omap5-core-opp-supply",
	 .data = &omap_omap5core_of_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_opp_supply_of_match);

अटल पूर्णांक ti_opp_supply_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *cpu_dev = get_cpu_device(0);
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा ti_opp_supply_of_data *of_data;
	पूर्णांक ret = 0;

	match = of_match_device(ti_opp_supply_of_match, dev);
	अगर (!match) अणु
		/* We करो not expect this to happen */
		dev_err(dev, "%s: Unable to match device\n", __func__);
		वापस -ENODEV;
	पूर्ण
	अगर (!match->data) अणु
		/* Again, unlikely.. but mistakes करो happen */
		dev_err(dev, "%s: Bad data in match\n", __func__);
		वापस -EINVAL;
	पूर्ण
	of_data = match->data;

	dev_set_drvdata(dev, (व्योम *)of_data);

	/* If we need optimized voltage */
	अगर (of_data->flags & OPPDM_EFUSE_CLASS0_OPTIMIZED_VOLTAGE) अणु
		ret = _store_optimized_voltages(dev, &opp_data);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = PTR_ERR_OR_ZERO(dev_pm_opp_रेजिस्टर_set_opp_helper(cpu_dev,
								 ti_opp_supply_set_opp));
	अगर (ret)
		_मुक्त_optimized_voltages(dev, &opp_data);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver ti_opp_supply_driver = अणु
	.probe = ti_opp_supply_probe,
	.driver = अणु
		   .name = "ti_opp_supply",
		   .of_match_table = of_match_ptr(ti_opp_supply_of_match),
		   पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_opp_supply_driver);

MODULE_DESCRIPTION("Texas Instruments OMAP OPP Supply driver");
MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_LICENSE("GPL v2");
