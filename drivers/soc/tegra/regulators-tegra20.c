<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Voltage regulators coupler क्रम NVIDIA Tegra20
 * Copyright (C) 2019 GRATE-DRIVER project
 *
 * Voltage स्थिरraपूर्णांकs borrowed from करोwnstream kernel sources
 * Copyright (C) 2010-2011 NVIDIA Corporation
 */

#घोषणा pr_fmt(fmt)	"tegra voltage-coupler: " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/coupler.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>

काष्ठा tegra_regulator_coupler अणु
	काष्ठा regulator_coupler coupler;
	काष्ठा regulator_dev *core_rdev;
	काष्ठा regulator_dev *cpu_rdev;
	काष्ठा regulator_dev *rtc_rdev;
	पूर्णांक core_min_uV;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_regulator_coupler *
to_tegra_coupler(काष्ठा regulator_coupler *coupler)
अणु
	वापस container_of(coupler, काष्ठा tegra_regulator_coupler, coupler);
पूर्ण

अटल पूर्णांक tegra20_core_limit(काष्ठा tegra_regulator_coupler *tegra,
			      काष्ठा regulator_dev *core_rdev)
अणु
	पूर्णांक core_min_uV = 0;
	पूर्णांक core_max_uV;
	पूर्णांक core_cur_uV;
	पूर्णांक err;

	अगर (tegra->core_min_uV > 0)
		वापस tegra->core_min_uV;

	core_cur_uV = regulator_get_voltage_rdev(core_rdev);
	अगर (core_cur_uV < 0)
		वापस core_cur_uV;

	core_max_uV = max(core_cur_uV, 1200000);

	err = regulator_check_voltage(core_rdev, &core_min_uV, &core_max_uV);
	अगर (err)
		वापस err;

	/*
	 * Limit minimum CORE voltage to a value left from bootloader or,
	 * अगर it's unreasonably low value, to the most common 1.2v or to
	 * whatever maximum value defined via board's device-tree.
	 */
	tegra->core_min_uV = core_max_uV;

	pr_info("core minimum voltage limited to %duV\n", tegra->core_min_uV);

	वापस tegra->core_min_uV;
पूर्ण

अटल पूर्णांक tegra20_core_rtc_max_spपढ़ो(काष्ठा regulator_dev *core_rdev,
				       काष्ठा regulator_dev *rtc_rdev)
अणु
	काष्ठा coupling_desc *c_desc = &core_rdev->coupling_desc;
	काष्ठा regulator_dev *rdev;
	पूर्णांक max_spपढ़ो;
	अचिन्हित पूर्णांक i;

	क्रम (i = 1; i < c_desc->n_coupled; i++) अणु
		max_spपढ़ो = core_rdev->स्थिरraपूर्णांकs->max_spपढ़ो[i - 1];
		rdev = c_desc->coupled_rdevs[i];

		अगर (rdev == rtc_rdev && max_spपढ़ो)
			वापस max_spपढ़ो;
	पूर्ण

	pr_err_once("rtc-core max-spread is undefined in device-tree\n");

	वापस 150000;
पूर्ण

अटल पूर्णांक tegra20_core_rtc_update(काष्ठा tegra_regulator_coupler *tegra,
				   काष्ठा regulator_dev *core_rdev,
				   काष्ठा regulator_dev *rtc_rdev,
				   पूर्णांक cpu_uV, पूर्णांक cpu_min_uV)
अणु
	पूर्णांक core_min_uV, core_max_uV = पूर्णांक_उच्च;
	पूर्णांक rtc_min_uV, rtc_max_uV = पूर्णांक_उच्च;
	पूर्णांक core_target_uV;
	पूर्णांक rtc_target_uV;
	पूर्णांक max_spपढ़ो;
	पूर्णांक core_uV;
	पूर्णांक rtc_uV;
	पूर्णांक err;

	/*
	 * RTC and CORE voltages should be no more than 170mV from each other,
	 * CPU should be below RTC and CORE by at least 120mV. This applies
	 * to all Tegra20 SoC's.
	 */
	max_spपढ़ो = tegra20_core_rtc_max_spपढ़ो(core_rdev, rtc_rdev);

	/*
	 * The core voltage scaling is currently not hooked up in drivers,
	 * hence we will limit the minimum core voltage to a reasonable value.
	 * This should be good enough क्रम the समय being.
	 */
	core_min_uV = tegra20_core_limit(tegra, core_rdev);
	अगर (core_min_uV < 0)
		वापस core_min_uV;

	err = regulator_check_voltage(core_rdev, &core_min_uV, &core_max_uV);
	अगर (err)
		वापस err;

	err = regulator_check_consumers(core_rdev, &core_min_uV, &core_max_uV,
					PM_SUSPEND_ON);
	अगर (err)
		वापस err;

	core_uV = regulator_get_voltage_rdev(core_rdev);
	अगर (core_uV < 0)
		वापस core_uV;

	core_min_uV = max(cpu_min_uV + 125000, core_min_uV);
	अगर (core_min_uV > core_max_uV)
		वापस -EINVAL;

	अगर (cpu_uV + 120000 > core_uV)
		pr_err("core-cpu voltage constraint violated: %d %d\n",
		       core_uV, cpu_uV + 120000);

	rtc_uV = regulator_get_voltage_rdev(rtc_rdev);
	अगर (rtc_uV < 0)
		वापस rtc_uV;

	अगर (cpu_uV + 120000 > rtc_uV)
		pr_err("rtc-cpu voltage constraint violated: %d %d\n",
		       rtc_uV, cpu_uV + 120000);

	अगर (असल(core_uV - rtc_uV) > 170000)
		pr_err("core-rtc voltage constraint violated: %d %d\n",
		       core_uV, rtc_uV);

	rtc_min_uV = max(cpu_min_uV + 125000, core_min_uV - max_spपढ़ो);

	err = regulator_check_voltage(rtc_rdev, &rtc_min_uV, &rtc_max_uV);
	अगर (err)
		वापस err;

	जबतक (core_uV != core_min_uV || rtc_uV != rtc_min_uV) अणु
		अगर (core_uV < core_min_uV) अणु
			core_target_uV = min(core_uV + max_spपढ़ो, core_min_uV);
			core_target_uV = min(rtc_uV + max_spपढ़ो, core_target_uV);
		पूर्ण अन्यथा अणु
			core_target_uV = max(core_uV - max_spपढ़ो, core_min_uV);
			core_target_uV = max(rtc_uV - max_spपढ़ो, core_target_uV);
		पूर्ण

		अगर (core_uV == core_target_uV)
			जाओ update_rtc;

		err = regulator_set_voltage_rdev(core_rdev,
						 core_target_uV,
						 core_max_uV,
						 PM_SUSPEND_ON);
		अगर (err)
			वापस err;

		core_uV = core_target_uV;
update_rtc:
		अगर (rtc_uV < rtc_min_uV) अणु
			rtc_target_uV = min(rtc_uV + max_spपढ़ो, rtc_min_uV);
			rtc_target_uV = min(core_uV + max_spपढ़ो, rtc_target_uV);
		पूर्ण अन्यथा अणु
			rtc_target_uV = max(rtc_uV - max_spपढ़ो, rtc_min_uV);
			rtc_target_uV = max(core_uV - max_spपढ़ो, rtc_target_uV);
		पूर्ण

		अगर (rtc_uV == rtc_target_uV)
			जारी;

		err = regulator_set_voltage_rdev(rtc_rdev,
						 rtc_target_uV,
						 rtc_max_uV,
						 PM_SUSPEND_ON);
		अगर (err)
			वापस err;

		rtc_uV = rtc_target_uV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra20_core_voltage_update(काष्ठा tegra_regulator_coupler *tegra,
				       काष्ठा regulator_dev *cpu_rdev,
				       काष्ठा regulator_dev *core_rdev,
				       काष्ठा regulator_dev *rtc_rdev)
अणु
	पूर्णांक cpu_uV;

	cpu_uV = regulator_get_voltage_rdev(cpu_rdev);
	अगर (cpu_uV < 0)
		वापस cpu_uV;

	वापस tegra20_core_rtc_update(tegra, core_rdev, rtc_rdev,
				       cpu_uV, cpu_uV);
पूर्ण

अटल पूर्णांक tegra20_cpu_voltage_update(काष्ठा tegra_regulator_coupler *tegra,
				      काष्ठा regulator_dev *cpu_rdev,
				      काष्ठा regulator_dev *core_rdev,
				      काष्ठा regulator_dev *rtc_rdev)
अणु
	पूर्णांक cpu_min_uV_consumers = 0;
	पूर्णांक cpu_max_uV = पूर्णांक_उच्च;
	पूर्णांक cpu_min_uV = 0;
	पूर्णांक cpu_uV;
	पूर्णांक err;

	err = regulator_check_voltage(cpu_rdev, &cpu_min_uV, &cpu_max_uV);
	अगर (err)
		वापस err;

	err = regulator_check_consumers(cpu_rdev, &cpu_min_uV, &cpu_max_uV,
					PM_SUSPEND_ON);
	अगर (err)
		वापस err;

	err = regulator_check_consumers(cpu_rdev, &cpu_min_uV_consumers,
					&cpu_max_uV, PM_SUSPEND_ON);
	अगर (err)
		वापस err;

	cpu_uV = regulator_get_voltage_rdev(cpu_rdev);
	अगर (cpu_uV < 0)
		वापस cpu_uV;

	/*
	 * CPU's regulator may not have any consumers, hence the voltage
	 * must not be changed in that हाल because CPU simply won't
	 * survive the voltage drop अगर it's running on a higher frequency.
	 */
	अगर (!cpu_min_uV_consumers)
		cpu_min_uV = cpu_uV;

	अगर (cpu_min_uV > cpu_uV) अणु
		err = tegra20_core_rtc_update(tegra, core_rdev, rtc_rdev,
					      cpu_uV, cpu_min_uV);
		अगर (err)
			वापस err;

		err = regulator_set_voltage_rdev(cpu_rdev, cpu_min_uV,
						 cpu_max_uV, PM_SUSPEND_ON);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (cpu_min_uV < cpu_uV)  अणु
		err = regulator_set_voltage_rdev(cpu_rdev, cpu_min_uV,
						 cpu_max_uV, PM_SUSPEND_ON);
		अगर (err)
			वापस err;

		err = tegra20_core_rtc_update(tegra, core_rdev, rtc_rdev,
					      cpu_uV, cpu_min_uV);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra20_regulator_balance_voltage(काष्ठा regulator_coupler *coupler,
					     काष्ठा regulator_dev *rdev,
					     suspend_state_t state)
अणु
	काष्ठा tegra_regulator_coupler *tegra = to_tegra_coupler(coupler);
	काष्ठा regulator_dev *core_rdev = tegra->core_rdev;
	काष्ठा regulator_dev *cpu_rdev = tegra->cpu_rdev;
	काष्ठा regulator_dev *rtc_rdev = tegra->rtc_rdev;

	अगर ((core_rdev != rdev && cpu_rdev != rdev && rtc_rdev != rdev) ||
	    state != PM_SUSPEND_ON) अणु
		pr_err("regulators are not coupled properly\n");
		वापस -EINVAL;
	पूर्ण

	अगर (rdev == cpu_rdev)
		वापस tegra20_cpu_voltage_update(tegra, cpu_rdev,
						  core_rdev, rtc_rdev);

	अगर (rdev == core_rdev)
		वापस tegra20_core_voltage_update(tegra, cpu_rdev,
						   core_rdev, rtc_rdev);

	pr_err("changing %s voltage not permitted\n", rdev_get_name(rtc_rdev));

	वापस -EPERM;
पूर्ण

अटल पूर्णांक tegra20_regulator_attach(काष्ठा regulator_coupler *coupler,
				    काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tegra_regulator_coupler *tegra = to_tegra_coupler(coupler);
	काष्ठा device_node *np = rdev->dev.of_node;

	अगर (of_property_पढ़ो_bool(np, "nvidia,tegra-core-regulator") &&
	    !tegra->core_rdev) अणु
		tegra->core_rdev = rdev;
		वापस 0;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "nvidia,tegra-rtc-regulator") &&
	    !tegra->rtc_rdev) अणु
		tegra->rtc_rdev = rdev;
		वापस 0;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "nvidia,tegra-cpu-regulator") &&
	    !tegra->cpu_rdev) अणु
		tegra->cpu_rdev = rdev;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tegra20_regulator_detach(काष्ठा regulator_coupler *coupler,
				    काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tegra_regulator_coupler *tegra = to_tegra_coupler(coupler);

	अगर (tegra->core_rdev == rdev) अणु
		tegra->core_rdev = शून्य;
		वापस 0;
	पूर्ण

	अगर (tegra->rtc_rdev == rdev) अणु
		tegra->rtc_rdev = शून्य;
		वापस 0;
	पूर्ण

	अगर (tegra->cpu_rdev == rdev) अणु
		tegra->cpu_rdev = शून्य;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा tegra_regulator_coupler tegra20_coupler = अणु
	.coupler = अणु
		.attach_regulator = tegra20_regulator_attach,
		.detach_regulator = tegra20_regulator_detach,
		.balance_voltage = tegra20_regulator_balance_voltage,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tegra_regulator_coupler_init(व्योम)
अणु
	अगर (!of_machine_is_compatible("nvidia,tegra20"))
		वापस 0;

	वापस regulator_coupler_रेजिस्टर(&tegra20_coupler.coupler);
पूर्ण
arch_initcall(tegra_regulator_coupler_init);
