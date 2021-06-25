<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा PU_SOC_VOLTAGE_NORMAL	1250000
#घोषणा PU_SOC_VOLTAGE_HIGH	1275000
#घोषणा FREQ_1P2_GHZ		1200000000

अटल काष्ठा regulator *arm_reg;
अटल काष्ठा regulator *pu_reg;
अटल काष्ठा regulator *soc_reg;

क्रमागत IMX6_CPUFREQ_CLKS अणु
	ARM,
	PLL1_SYS,
	STEP,
	PLL1_SW,
	PLL2_PFD2_396M,
	/* MX6UL requires two more clks */
	PLL2_BUS,
	SECONDARY_SEL,
पूर्ण;
#घोषणा IMX6Q_CPUFREQ_CLK_NUM		5
#घोषणा IMX6UL_CPUFREQ_CLK_NUM		7

अटल पूर्णांक num_clks;
अटल काष्ठा clk_bulk_data clks[] = अणु
	अणु .id = "arm" पूर्ण,
	अणु .id = "pll1_sys" पूर्ण,
	अणु .id = "step" पूर्ण,
	अणु .id = "pll1_sw" पूर्ण,
	अणु .id = "pll2_pfd2_396m" पूर्ण,
	अणु .id = "pll2_bus" पूर्ण,
	अणु .id = "secondary_sel" पूर्ण,
पूर्ण;

अटल काष्ठा device *cpu_dev;
अटल काष्ठा cpufreq_frequency_table *freq_table;
अटल अचिन्हित पूर्णांक max_freq;
अटल अचिन्हित पूर्णांक transition_latency;

अटल u32 *imx6_soc_volt;
अटल u32 soc_opp_count;

अटल पूर्णांक imx6q_set_target(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक index)
अणु
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ freq_hz, volt, volt_old;
	अचिन्हित पूर्णांक old_freq, new_freq;
	bool pll1_sys_temp_enabled = false;
	पूर्णांक ret;

	new_freq = freq_table[index].frequency;
	freq_hz = new_freq * 1000;
	old_freq = clk_get_rate(clks[ARM].clk) / 1000;

	opp = dev_pm_opp_find_freq_उच्चमान(cpu_dev, &freq_hz);
	अगर (IS_ERR(opp)) अणु
		dev_err(cpu_dev, "failed to find OPP for %ld\n", freq_hz);
		वापस PTR_ERR(opp);
	पूर्ण

	volt = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	volt_old = regulator_get_voltage(arm_reg);

	dev_dbg(cpu_dev, "%u MHz, %ld mV --> %u MHz, %ld mV\n",
		old_freq / 1000, volt_old / 1000,
		new_freq / 1000, volt / 1000);

	/* scaling up?  scale voltage beक्रमe frequency */
	अगर (new_freq > old_freq) अणु
		अगर (!IS_ERR(pu_reg)) अणु
			ret = regulator_set_voltage_tol(pu_reg, imx6_soc_volt[index], 0);
			अगर (ret) अणु
				dev_err(cpu_dev, "failed to scale vddpu up: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		ret = regulator_set_voltage_tol(soc_reg, imx6_soc_volt[index], 0);
		अगर (ret) अणु
			dev_err(cpu_dev, "failed to scale vddsoc up: %d\n", ret);
			वापस ret;
		पूर्ण
		ret = regulator_set_voltage_tol(arm_reg, volt, 0);
		अगर (ret) अणु
			dev_err(cpu_dev,
				"failed to scale vddarm up: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * The setpoपूर्णांकs are selected per PLL/PDF frequencies, so we need to
	 * reprogram PLL क्रम frequency scaling.  The procedure of reprogramming
	 * PLL1 is as below.
	 * For i.MX6UL, it has a secondary clk mux, the cpu frequency change
	 * flow is slightly dअगरferent from other i.MX6 OSC.
	 * The cpu frequeny change flow क्रम i.MX6(except i.MX6UL) is as below:
	 *  - Enable pll2_pfd2_396m_clk and reparent pll1_sw_clk to it
	 *  - Reprogram pll1_sys_clk and reparent pll1_sw_clk back to it
	 *  - Disable pll2_pfd2_396m_clk
	 */
	अगर (of_machine_is_compatible("fsl,imx6ul") ||
	    of_machine_is_compatible("fsl,imx6ull")) अणु
		/*
		 * When changing pll1_sw_clk's parent to pll1_sys_clk,
		 * CPU may run at higher than 528MHz, this will lead to
		 * the प्रणाली unstable अगर the voltage is lower than the
		 * voltage of 528MHz, so lower the CPU frequency to one
		 * half beक्रमe changing CPU frequency.
		 */
		clk_set_rate(clks[ARM].clk, (old_freq >> 1) * 1000);
		clk_set_parent(clks[PLL1_SW].clk, clks[PLL1_SYS].clk);
		अगर (freq_hz > clk_get_rate(clks[PLL2_PFD2_396M].clk))
			clk_set_parent(clks[SECONDARY_SEL].clk,
				       clks[PLL2_BUS].clk);
		अन्यथा
			clk_set_parent(clks[SECONDARY_SEL].clk,
				       clks[PLL2_PFD2_396M].clk);
		clk_set_parent(clks[STEP].clk, clks[SECONDARY_SEL].clk);
		clk_set_parent(clks[PLL1_SW].clk, clks[STEP].clk);
		अगर (freq_hz > clk_get_rate(clks[PLL2_BUS].clk)) अणु
			clk_set_rate(clks[PLL1_SYS].clk, new_freq * 1000);
			clk_set_parent(clks[PLL1_SW].clk, clks[PLL1_SYS].clk);
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_set_parent(clks[STEP].clk, clks[PLL2_PFD2_396M].clk);
		clk_set_parent(clks[PLL1_SW].clk, clks[STEP].clk);
		अगर (freq_hz > clk_get_rate(clks[PLL2_PFD2_396M].clk)) अणु
			clk_set_rate(clks[PLL1_SYS].clk, new_freq * 1000);
			clk_set_parent(clks[PLL1_SW].clk, clks[PLL1_SYS].clk);
		पूर्ण अन्यथा अणु
			/* pll1_sys needs to be enabled क्रम भागider rate change to work. */
			pll1_sys_temp_enabled = true;
			clk_prepare_enable(clks[PLL1_SYS].clk);
		पूर्ण
	पूर्ण

	/* Ensure the arm घड़ी भागider is what we expect */
	ret = clk_set_rate(clks[ARM].clk, new_freq * 1000);
	अगर (ret) अणु
		पूर्णांक ret1;

		dev_err(cpu_dev, "failed to set clock rate: %d\n", ret);
		ret1 = regulator_set_voltage_tol(arm_reg, volt_old, 0);
		अगर (ret1)
			dev_warn(cpu_dev,
				 "failed to restore vddarm voltage: %d\n", ret1);
		वापस ret;
	पूर्ण

	/* PLL1 is only needed until after ARM-PODF is set. */
	अगर (pll1_sys_temp_enabled)
		clk_disable_unprepare(clks[PLL1_SYS].clk);

	/* scaling करोwn?  scale voltage after frequency */
	अगर (new_freq < old_freq) अणु
		ret = regulator_set_voltage_tol(arm_reg, volt, 0);
		अगर (ret)
			dev_warn(cpu_dev,
				 "failed to scale vddarm down: %d\n", ret);
		ret = regulator_set_voltage_tol(soc_reg, imx6_soc_volt[index], 0);
		अगर (ret)
			dev_warn(cpu_dev, "failed to scale vddsoc down: %d\n", ret);
		अगर (!IS_ERR(pu_reg)) अणु
			ret = regulator_set_voltage_tol(pu_reg, imx6_soc_volt[index], 0);
			अगर (ret)
				dev_warn(cpu_dev, "failed to scale vddpu down: %d\n", ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx6q_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	policy->clk = clks[ARM].clk;
	cpufreq_generic_init(policy, freq_table, transition_latency);
	policy->suspend_freq = max_freq;
	dev_pm_opp_of_रेजिस्टर_em(cpu_dev, policy->cpus);

	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver imx6q_cpufreq_driver = अणु
	.flags = CPUFREQ_NEED_INITIAL_FREQ_CHECK |
		 CPUFREQ_IS_COOLING_DEV,
	.verअगरy = cpufreq_generic_frequency_table_verअगरy,
	.target_index = imx6q_set_target,
	.get = cpufreq_generic_get,
	.init = imx6q_cpufreq_init,
	.name = "imx6q-cpufreq",
	.attr = cpufreq_generic_attr,
	.suspend = cpufreq_generic_suspend,
पूर्ण;

#घोषणा OCOTP_CFG3			0x440
#घोषणा OCOTP_CFG3_SPEED_SHIFT		16
#घोषणा OCOTP_CFG3_SPEED_1P2GHZ		0x3
#घोषणा OCOTP_CFG3_SPEED_996MHZ		0x2
#घोषणा OCOTP_CFG3_SPEED_852MHZ		0x1

अटल पूर्णांक imx6q_opp_check_speed_grading(काष्ठा device *dev)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *base;
	u32 val;
	पूर्णांक ret;

	अगर (of_find_property(dev->of_node, "nvmem-cells", शून्य)) अणु
		ret = nvmem_cell_पढ़ो_u32(dev, "speed_grade", &val);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		np = of_find_compatible_node(शून्य, शून्य, "fsl,imx6q-ocotp");
		अगर (!np)
			वापस -ENOENT;

		base = of_iomap(np, 0);
		of_node_put(np);
		अगर (!base) अणु
			dev_err(dev, "failed to map ocotp\n");
			वापस -EFAULT;
		पूर्ण

		/*
		 * SPEED_GRADING[1:0] defines the max speed of ARM:
		 * 2b'11: 1200000000Hz;
		 * 2b'10: 996000000Hz;
		 * 2b'01: 852000000Hz; -- i.MX6Q Only, exclusive with 996MHz.
		 * 2b'00: 792000000Hz;
		 * We need to set the max speed of ARM according to fuse map.
		 */
		val = पढ़ोl_relaxed(base + OCOTP_CFG3);
		iounmap(base);
	पूर्ण

	val >>= OCOTP_CFG3_SPEED_SHIFT;
	val &= 0x3;

	अगर (val < OCOTP_CFG3_SPEED_996MHZ)
		अगर (dev_pm_opp_disable(dev, 996000000))
			dev_warn(dev, "failed to disable 996MHz OPP\n");

	अगर (of_machine_is_compatible("fsl,imx6q") ||
	    of_machine_is_compatible("fsl,imx6qp")) अणु
		अगर (val != OCOTP_CFG3_SPEED_852MHZ)
			अगर (dev_pm_opp_disable(dev, 852000000))
				dev_warn(dev, "failed to disable 852MHz OPP\n");
		अगर (val != OCOTP_CFG3_SPEED_1P2GHZ)
			अगर (dev_pm_opp_disable(dev, 1200000000))
				dev_warn(dev, "failed to disable 1.2GHz OPP\n");
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा OCOTP_CFG3_6UL_SPEED_696MHZ	0x2
#घोषणा OCOTP_CFG3_6ULL_SPEED_792MHZ	0x2
#घोषणा OCOTP_CFG3_6ULL_SPEED_900MHZ	0x3

अटल पूर्णांक imx6ul_opp_check_speed_grading(काष्ठा device *dev)
अणु
	u32 val;
	पूर्णांक ret = 0;

	अगर (of_find_property(dev->of_node, "nvmem-cells", शून्य)) अणु
		ret = nvmem_cell_पढ़ो_u32(dev, "speed_grade", &val);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		काष्ठा device_node *np;
		व्योम __iomem *base;

		np = of_find_compatible_node(शून्य, शून्य, "fsl,imx6ul-ocotp");
		अगर (!np)
			np = of_find_compatible_node(शून्य, शून्य,
						     "fsl,imx6ull-ocotp");
		अगर (!np)
			वापस -ENOENT;

		base = of_iomap(np, 0);
		of_node_put(np);
		अगर (!base) अणु
			dev_err(dev, "failed to map ocotp\n");
			वापस -EFAULT;
		पूर्ण

		val = पढ़ोl_relaxed(base + OCOTP_CFG3);
		iounmap(base);
	पूर्ण

	/*
	 * Speed GRADING[1:0] defines the max speed of ARM:
	 * 2b'00: Reserved;
	 * 2b'01: 528000000Hz;
	 * 2b'10: 696000000Hz on i.MX6UL, 792000000Hz on i.MX6ULL;
	 * 2b'11: 900000000Hz on i.MX6ULL only;
	 * We need to set the max speed of ARM according to fuse map.
	 */
	val >>= OCOTP_CFG3_SPEED_SHIFT;
	val &= 0x3;

	अगर (of_machine_is_compatible("fsl,imx6ul")) अणु
		अगर (val != OCOTP_CFG3_6UL_SPEED_696MHZ)
			अगर (dev_pm_opp_disable(dev, 696000000))
				dev_warn(dev, "failed to disable 696MHz OPP\n");
	पूर्ण

	अगर (of_machine_is_compatible("fsl,imx6ull")) अणु
		अगर (val != OCOTP_CFG3_6ULL_SPEED_792MHZ)
			अगर (dev_pm_opp_disable(dev, 792000000))
				dev_warn(dev, "failed to disable 792MHz OPP\n");

		अगर (val != OCOTP_CFG3_6ULL_SPEED_900MHZ)
			अगर (dev_pm_opp_disable(dev, 900000000))
				dev_warn(dev, "failed to disable 900MHz OPP\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक imx6q_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np;
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ min_volt, max_volt;
	पूर्णांक num, ret;
	स्थिर काष्ठा property *prop;
	स्थिर __be32 *val;
	u32 nr, i, j;

	cpu_dev = get_cpu_device(0);
	अगर (!cpu_dev) अणु
		pr_err("failed to get cpu0 device\n");
		वापस -ENODEV;
	पूर्ण

	np = of_node_get(cpu_dev->of_node);
	अगर (!np) अणु
		dev_err(cpu_dev, "failed to find cpu0 node\n");
		वापस -ENOENT;
	पूर्ण

	अगर (of_machine_is_compatible("fsl,imx6ul") ||
	    of_machine_is_compatible("fsl,imx6ull"))
		num_clks = IMX6UL_CPUFREQ_CLK_NUM;
	अन्यथा
		num_clks = IMX6Q_CPUFREQ_CLK_NUM;

	ret = clk_bulk_get(cpu_dev, num_clks, clks);
	अगर (ret)
		जाओ put_node;

	arm_reg = regulator_get(cpu_dev, "arm");
	pu_reg = regulator_get_optional(cpu_dev, "pu");
	soc_reg = regulator_get(cpu_dev, "soc");
	अगर (PTR_ERR(arm_reg) == -EPROBE_DEFER ||
			PTR_ERR(soc_reg) == -EPROBE_DEFER ||
			PTR_ERR(pu_reg) == -EPROBE_DEFER) अणु
		ret = -EPROBE_DEFER;
		dev_dbg(cpu_dev, "regulators not ready, defer\n");
		जाओ put_reg;
	पूर्ण
	अगर (IS_ERR(arm_reg) || IS_ERR(soc_reg)) अणु
		dev_err(cpu_dev, "failed to get regulators\n");
		ret = -ENOENT;
		जाओ put_reg;
	पूर्ण

	ret = dev_pm_opp_of_add_table(cpu_dev);
	अगर (ret < 0) अणु
		dev_err(cpu_dev, "failed to init OPP table: %d\n", ret);
		जाओ put_reg;
	पूर्ण

	अगर (of_machine_is_compatible("fsl,imx6ul") ||
	    of_machine_is_compatible("fsl,imx6ull")) अणु
		ret = imx6ul_opp_check_speed_grading(cpu_dev);
	पूर्ण अन्यथा अणु
		ret = imx6q_opp_check_speed_grading(cpu_dev);
	पूर्ण
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(cpu_dev, "failed to read ocotp: %d\n",
				ret);
		जाओ out_मुक्त_opp;
	पूर्ण

	num = dev_pm_opp_get_opp_count(cpu_dev);
	अगर (num < 0) अणु
		ret = num;
		dev_err(cpu_dev, "no OPP table is found: %d\n", ret);
		जाओ out_मुक्त_opp;
	पूर्ण

	ret = dev_pm_opp_init_cpufreq_table(cpu_dev, &freq_table);
	अगर (ret) अणु
		dev_err(cpu_dev, "failed to init cpufreq table: %d\n", ret);
		जाओ out_मुक्त_opp;
	पूर्ण

	/* Make imx6_soc_volt array's size same as arm opp number */
	imx6_soc_volt = devm_kसुस्मृति(cpu_dev, num, माप(*imx6_soc_volt),
				     GFP_KERNEL);
	अगर (imx6_soc_volt == शून्य) अणु
		ret = -ENOMEM;
		जाओ मुक्त_freq_table;
	पूर्ण

	prop = of_find_property(np, "fsl,soc-operating-points", शून्य);
	अगर (!prop || !prop->value)
		जाओ soc_opp_out;

	/*
	 * Each OPP is a set of tuples consisting of frequency and
	 * voltage like <freq-kHz vol-uV>.
	 */
	nr = prop->length / माप(u32);
	अगर (nr % 2 || (nr / 2) < num)
		जाओ soc_opp_out;

	क्रम (j = 0; j < num; j++) अणु
		val = prop->value;
		क्रम (i = 0; i < nr / 2; i++) अणु
			अचिन्हित दीर्घ freq = be32_to_cpup(val++);
			अचिन्हित दीर्घ volt = be32_to_cpup(val++);
			अगर (freq_table[j].frequency == freq) अणु
				imx6_soc_volt[soc_opp_count++] = volt;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

soc_opp_out:
	/* use fixed soc opp volt अगर no valid soc opp info found in dtb */
	अगर (soc_opp_count != num) अणु
		dev_warn(cpu_dev, "can NOT find valid fsl,soc-operating-points property in dtb, use default value!\n");
		क्रम (j = 0; j < num; j++)
			imx6_soc_volt[j] = PU_SOC_VOLTAGE_NORMAL;
		अगर (freq_table[num - 1].frequency * 1000 == FREQ_1P2_GHZ)
			imx6_soc_volt[num - 1] = PU_SOC_VOLTAGE_HIGH;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "clock-latency", &transition_latency))
		transition_latency = CPUFREQ_ETERNAL;

	/*
	 * Calculate the ramp समय क्रम max voltage change in the
	 * VDDSOC and VDDPU regulators.
	 */
	ret = regulator_set_voltage_समय(soc_reg, imx6_soc_volt[0], imx6_soc_volt[num - 1]);
	अगर (ret > 0)
		transition_latency += ret * 1000;
	अगर (!IS_ERR(pu_reg)) अणु
		ret = regulator_set_voltage_समय(pu_reg, imx6_soc_volt[0], imx6_soc_volt[num - 1]);
		अगर (ret > 0)
			transition_latency += ret * 1000;
	पूर्ण

	/*
	 * OPP is मुख्यtained in order of increasing frequency, and
	 * freq_table initialised from OPP is thereक्रमe sorted in the
	 * same order.
	 */
	max_freq = freq_table[--num].frequency;
	opp = dev_pm_opp_find_freq_exact(cpu_dev,
				  freq_table[0].frequency * 1000, true);
	min_volt = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);
	opp = dev_pm_opp_find_freq_exact(cpu_dev, max_freq * 1000, true);
	max_volt = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	ret = regulator_set_voltage_समय(arm_reg, min_volt, max_volt);
	अगर (ret > 0)
		transition_latency += ret * 1000;

	ret = cpufreq_रेजिस्टर_driver(&imx6q_cpufreq_driver);
	अगर (ret) अणु
		dev_err(cpu_dev, "failed register driver: %d\n", ret);
		जाओ मुक्त_freq_table;
	पूर्ण

	of_node_put(np);
	वापस 0;

मुक्त_freq_table:
	dev_pm_opp_मुक्त_cpufreq_table(cpu_dev, &freq_table);
out_मुक्त_opp:
	dev_pm_opp_of_हटाओ_table(cpu_dev);
put_reg:
	अगर (!IS_ERR(arm_reg))
		regulator_put(arm_reg);
	अगर (!IS_ERR(pu_reg))
		regulator_put(pu_reg);
	अगर (!IS_ERR(soc_reg))
		regulator_put(soc_reg);

	clk_bulk_put(num_clks, clks);
put_node:
	of_node_put(np);

	वापस ret;
पूर्ण

अटल पूर्णांक imx6q_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cpufreq_unरेजिस्टर_driver(&imx6q_cpufreq_driver);
	dev_pm_opp_मुक्त_cpufreq_table(cpu_dev, &freq_table);
	dev_pm_opp_of_हटाओ_table(cpu_dev);
	regulator_put(arm_reg);
	अगर (!IS_ERR(pu_reg))
		regulator_put(pu_reg);
	regulator_put(soc_reg);

	clk_bulk_put(num_clks, clks);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver imx6q_cpufreq_platdrv = अणु
	.driver = अणु
		.name	= "imx6q-cpufreq",
	पूर्ण,
	.probe		= imx6q_cpufreq_probe,
	.हटाओ		= imx6q_cpufreq_हटाओ,
पूर्ण;
module_platक्रमm_driver(imx6q_cpufreq_platdrv);

MODULE_ALIAS("platform:imx6q-cpufreq");
MODULE_AUTHOR("Shawn Guo <shawn.guo@linaro.org>");
MODULE_DESCRIPTION("Freescale i.MX6Q cpufreq driver");
MODULE_LICENSE("GPL");
