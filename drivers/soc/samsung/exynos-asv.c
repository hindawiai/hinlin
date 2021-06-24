<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *	      http://www.samsung.com/
 * Copyright (c) 2020 Krzysztof Kozlowski <krzk@kernel.org>
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 * Author: Krzysztof Kozlowski <krzk@kernel.org>
 *
 * Samsung Exynos SoC Adaptive Supply Voltage support
 */

#समावेश <linux/cpu.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/regmap.h>
#समावेश <linux/soc/samsung/exynos-chipid.h>

#समावेश "exynos-asv.h"
#समावेश "exynos5422-asv.h"

#घोषणा MHZ 1000000U

अटल पूर्णांक exynos_asv_update_cpu_opps(काष्ठा exynos_asv *asv,
				      काष्ठा device *cpu)
अणु
	काष्ठा exynos_asv_subsys *subsys = शून्य;
	काष्ठा dev_pm_opp *opp;
	अचिन्हित पूर्णांक opp_freq;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(asv->subsys); i++) अणु
		अगर (of_device_is_compatible(cpu->of_node,
					    asv->subsys[i].cpu_dt_compat)) अणु
			subsys = &asv->subsys[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!subsys)
		वापस -EINVAL;

	क्रम (i = 0; i < subsys->table.num_rows; i++) अणु
		अचिन्हित पूर्णांक new_volt, volt;
		पूर्णांक ret;

		opp_freq = exynos_asv_opp_get_frequency(subsys, i);

		opp = dev_pm_opp_find_freq_exact(cpu, opp_freq * MHZ, true);
		अगर (IS_ERR(opp)) अणु
			dev_info(asv->dev, "cpu%d opp%d, freq: %u missing\n",
				 cpu->id, i, opp_freq);

			जारी;
		पूर्ण

		volt = dev_pm_opp_get_voltage(opp);
		new_volt = asv->opp_get_voltage(subsys, i, volt);
		dev_pm_opp_put(opp);

		अगर (new_volt == volt)
			जारी;

		ret = dev_pm_opp_adjust_voltage(cpu, opp_freq * MHZ,
						new_volt, new_volt, new_volt);
		अगर (ret < 0)
			dev_err(asv->dev,
				"Failed to adjust OPP %u Hz/%u uV for cpu%d\n",
				opp_freq, new_volt, cpu->id);
		अन्यथा
			dev_dbg(asv->dev,
				"Adjusted OPP %u Hz/%u -> %u uV, cpu%d\n",
				opp_freq, volt, new_volt, cpu->id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_asv_update_opps(काष्ठा exynos_asv *asv)
अणु
	काष्ठा opp_table *last_opp_table = शून्य;
	काष्ठा device *cpu;
	पूर्णांक ret, cpuid;

	क्रम_each_possible_cpu(cpuid) अणु
		काष्ठा opp_table *opp_table;

		cpu = get_cpu_device(cpuid);
		अगर (!cpu)
			जारी;

		opp_table = dev_pm_opp_get_opp_table(cpu);
		अगर (IS_ERR(opp_table))
			जारी;

		अगर (!last_opp_table || opp_table != last_opp_table) अणु
			last_opp_table = opp_table;

			ret = exynos_asv_update_cpu_opps(asv, cpu);
			अगर (ret < 0)
				dev_err(asv->dev, "Couldn't udate OPPs for cpu%d\n",
					cpuid);
		पूर्ण

		dev_pm_opp_put_opp_table(opp_table);
	पूर्ण

	वापस	0;
पूर्ण

पूर्णांक exynos_asv_init(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	पूर्णांक (*probe_func)(काष्ठा exynos_asv *asv);
	काष्ठा exynos_asv *asv;
	काष्ठा device *cpu_dev;
	u32 product_id = 0;
	पूर्णांक ret, i;

	asv = devm_kzalloc(dev, माप(*asv), GFP_KERNEL);
	अगर (!asv)
		वापस -ENOMEM;

	asv->chipid_regmap = regmap;
	asv->dev = dev;
	ret = regmap_पढ़ो(asv->chipid_regmap, EXYNOS_CHIPID_REG_PRO_ID,
			  &product_id);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot read revision from ChipID: %d\n", ret);
		वापस -ENODEV;
	पूर्ण

	चयन (product_id & EXYNOS_MASK) अणु
	हाल 0xE5422000:
		probe_func = exynos5422_asv_init;
		अवरोध;
	शेष:
		dev_dbg(dev, "No ASV support for this SoC\n");
		devm_kमुक्त(dev, asv);
		वापस 0;
	पूर्ण

	cpu_dev = get_cpu_device(0);
	ret = dev_pm_opp_get_opp_count(cpu_dev);
	अगर (ret < 0)
		वापस -EPROBE_DEFER;

	ret = of_property_पढ़ो_u32(dev->of_node, "samsung,asv-bin",
				   &asv->of_bin);
	अगर (ret < 0)
		asv->of_bin = -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(asv->subsys); i++)
		asv->subsys[i].asv = asv;

	ret = probe_func(asv);
	अगर (ret < 0)
		वापस ret;

	वापस exynos_asv_update_opps(asv);
पूर्ण
