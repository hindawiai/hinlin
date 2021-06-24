<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Voltage regulators coupler क्रम NVIDIA Tegra30
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

#समावेश <soc/tegra/fuse.h>

काष्ठा tegra_regulator_coupler अणु
	काष्ठा regulator_coupler coupler;
	काष्ठा regulator_dev *core_rdev;
	काष्ठा regulator_dev *cpu_rdev;
	पूर्णांक core_min_uV;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_regulator_coupler *
to_tegra_coupler(काष्ठा regulator_coupler *coupler)
अणु
	वापस container_of(coupler, काष्ठा tegra_regulator_coupler, coupler);
पूर्ण

अटल पूर्णांक tegra30_core_limit(काष्ठा tegra_regulator_coupler *tegra,
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

अटल पूर्णांक tegra30_core_cpu_limit(पूर्णांक cpu_uV)
अणु
	अगर (cpu_uV < 800000)
		वापस 950000;

	अगर (cpu_uV < 900000)
		वापस 1000000;

	अगर (cpu_uV < 1000000)
		वापस 1100000;

	अगर (cpu_uV < 1100000)
		वापस 1200000;

	अगर (cpu_uV < 1250000) अणु
		चयन (tegra_sku_info.cpu_speeकरो_id) अणु
		हाल 0 ... 1:
		हाल 4:
		हाल 7 ... 8:
			वापस 1200000;

		शेष:
			वापस 1300000;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tegra30_voltage_update(काष्ठा tegra_regulator_coupler *tegra,
				  काष्ठा regulator_dev *cpu_rdev,
				  काष्ठा regulator_dev *core_rdev)
अणु
	पूर्णांक core_min_uV, core_max_uV = पूर्णांक_उच्च;
	पूर्णांक cpu_min_uV, cpu_max_uV = पूर्णांक_उच्च;
	पूर्णांक cpu_min_uV_consumers = 0;
	पूर्णांक core_min_limited_uV;
	पूर्णांक core_target_uV;
	पूर्णांक cpu_target_uV;
	पूर्णांक core_max_step;
	पूर्णांक cpu_max_step;
	पूर्णांक max_spपढ़ो;
	पूर्णांक core_uV;
	पूर्णांक cpu_uV;
	पूर्णांक err;

	/*
	 * CPU voltage should not got lower than 300mV from the CORE.
	 * CPU voltage should stay below the CORE by 100mV+, depending
	 * by the CORE voltage. This applies to all Tegra30 SoC's.
	 */
	max_spपढ़ो = cpu_rdev->स्थिरraपूर्णांकs->max_spपढ़ो[0];
	cpu_max_step = cpu_rdev->स्थिरraपूर्णांकs->max_uV_step;
	core_max_step = core_rdev->स्थिरraपूर्णांकs->max_uV_step;

	अगर (!max_spपढ़ो) अणु
		pr_err_once("cpu-core max-spread is undefined in device-tree\n");
		max_spपढ़ो = 300000;
	पूर्ण

	अगर (!cpu_max_step) अणु
		pr_err_once("cpu max-step is undefined in device-tree\n");
		cpu_max_step = 150000;
	पूर्ण

	अगर (!core_max_step) अणु
		pr_err_once("core max-step is undefined in device-tree\n");
		core_max_step = 150000;
	पूर्ण

	/*
	 * The CORE voltage scaling is currently not hooked up in drivers,
	 * hence we will limit the minimum CORE voltage to a reasonable value.
	 * This should be good enough क्रम the समय being.
	 */
	core_min_uV = tegra30_core_limit(tegra, core_rdev);
	अगर (core_min_uV < 0)
		वापस core_min_uV;

	err = regulator_check_consumers(core_rdev, &core_min_uV, &core_max_uV,
					PM_SUSPEND_ON);
	अगर (err)
		वापस err;

	core_uV = regulator_get_voltage_rdev(core_rdev);
	अगर (core_uV < 0)
		वापस core_uV;

	cpu_min_uV = core_min_uV - max_spपढ़ो;

	err = regulator_check_consumers(cpu_rdev, &cpu_min_uV, &cpu_max_uV,
					PM_SUSPEND_ON);
	अगर (err)
		वापस err;

	err = regulator_check_consumers(cpu_rdev, &cpu_min_uV_consumers,
					&cpu_max_uV, PM_SUSPEND_ON);
	अगर (err)
		वापस err;

	err = regulator_check_voltage(cpu_rdev, &cpu_min_uV, &cpu_max_uV);
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
		cpu_min_uV = max(cpu_uV, cpu_min_uV);

	/*
	 * Bootloader shall set up voltages correctly, but अगर it
	 * happens that there is a violation, then try to fix it
	 * at first.
	 */
	core_min_limited_uV = tegra30_core_cpu_limit(cpu_uV);
	अगर (core_min_limited_uV < 0)
		वापस core_min_limited_uV;

	core_min_uV = max(core_min_uV, tegra30_core_cpu_limit(cpu_min_uV));

	err = regulator_check_voltage(core_rdev, &core_min_uV, &core_max_uV);
	अगर (err)
		वापस err;

	अगर (core_min_limited_uV > core_uV) अणु
		pr_err("core voltage constraint violated: %d %d %d\n",
		       core_uV, core_min_limited_uV, cpu_uV);
		जाओ update_core;
	पूर्ण

	जबतक (cpu_uV != cpu_min_uV || core_uV != core_min_uV) अणु
		अगर (cpu_uV < cpu_min_uV) अणु
			cpu_target_uV = min(cpu_uV + cpu_max_step, cpu_min_uV);
		पूर्ण अन्यथा अणु
			cpu_target_uV = max(cpu_uV - cpu_max_step, cpu_min_uV);
			cpu_target_uV = max(core_uV - max_spपढ़ो, cpu_target_uV);
		पूर्ण

		अगर (cpu_uV == cpu_target_uV)
			जाओ update_core;

		err = regulator_set_voltage_rdev(cpu_rdev,
						 cpu_target_uV,
						 cpu_max_uV,
						 PM_SUSPEND_ON);
		अगर (err)
			वापस err;

		cpu_uV = cpu_target_uV;
update_core:
		core_min_limited_uV = tegra30_core_cpu_limit(cpu_uV);
		अगर (core_min_limited_uV < 0)
			वापस core_min_limited_uV;

		core_target_uV = max(core_min_limited_uV, core_min_uV);

		अगर (core_uV < core_target_uV) अणु
			core_target_uV = min(core_target_uV, core_uV + core_max_step);
			core_target_uV = min(core_target_uV, cpu_uV + max_spपढ़ो);
		पूर्ण अन्यथा अणु
			core_target_uV = max(core_target_uV, core_uV - core_max_step);
		पूर्ण

		अगर (core_uV == core_target_uV)
			जारी;

		err = regulator_set_voltage_rdev(core_rdev,
						 core_target_uV,
						 core_max_uV,
						 PM_SUSPEND_ON);
		अगर (err)
			वापस err;

		core_uV = core_target_uV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra30_regulator_balance_voltage(काष्ठा regulator_coupler *coupler,
					     काष्ठा regulator_dev *rdev,
					     suspend_state_t state)
अणु
	काष्ठा tegra_regulator_coupler *tegra = to_tegra_coupler(coupler);
	काष्ठा regulator_dev *core_rdev = tegra->core_rdev;
	काष्ठा regulator_dev *cpu_rdev = tegra->cpu_rdev;

	अगर ((core_rdev != rdev && cpu_rdev != rdev) || state != PM_SUSPEND_ON) अणु
		pr_err("regulators are not coupled properly\n");
		वापस -EINVAL;
	पूर्ण

	वापस tegra30_voltage_update(tegra, cpu_rdev, core_rdev);
पूर्ण

अटल पूर्णांक tegra30_regulator_attach(काष्ठा regulator_coupler *coupler,
				    काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tegra_regulator_coupler *tegra = to_tegra_coupler(coupler);
	काष्ठा device_node *np = rdev->dev.of_node;

	अगर (of_property_पढ़ो_bool(np, "nvidia,tegra-core-regulator") &&
	    !tegra->core_rdev) अणु
		tegra->core_rdev = rdev;
		वापस 0;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "nvidia,tegra-cpu-regulator") &&
	    !tegra->cpu_rdev) अणु
		tegra->cpu_rdev = rdev;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tegra30_regulator_detach(काष्ठा regulator_coupler *coupler,
				    काष्ठा regulator_dev *rdev)
अणु
	काष्ठा tegra_regulator_coupler *tegra = to_tegra_coupler(coupler);

	अगर (tegra->core_rdev == rdev) अणु
		tegra->core_rdev = शून्य;
		वापस 0;
	पूर्ण

	अगर (tegra->cpu_rdev == rdev) अणु
		tegra->cpu_rdev = शून्य;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा tegra_regulator_coupler tegra30_coupler = अणु
	.coupler = अणु
		.attach_regulator = tegra30_regulator_attach,
		.detach_regulator = tegra30_regulator_detach,
		.balance_voltage = tegra30_regulator_balance_voltage,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tegra_regulator_coupler_init(व्योम)
अणु
	अगर (!of_machine_is_compatible("nvidia,tegra30"))
		वापस 0;

	वापस regulator_coupler_रेजिस्टर(&tegra30_coupler.coupler);
पूर्ण
arch_initcall(tegra_regulator_coupler_init);
