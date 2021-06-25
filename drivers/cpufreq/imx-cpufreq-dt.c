<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP
 */

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश "cpufreq-dt.h"

#घोषणा OCOTP_CFG3_SPEED_GRADE_SHIFT	8
#घोषणा OCOTP_CFG3_SPEED_GRADE_MASK	(0x3 << 8)
#घोषणा IMX8MN_OCOTP_CFG3_SPEED_GRADE_MASK	(0xf << 8)
#घोषणा OCOTP_CFG3_MKT_SEGMENT_SHIFT    6
#घोषणा OCOTP_CFG3_MKT_SEGMENT_MASK     (0x3 << 6)
#घोषणा IMX8MP_OCOTP_CFG3_MKT_SEGMENT_SHIFT    5
#घोषणा IMX8MP_OCOTP_CFG3_MKT_SEGMENT_MASK     (0x3 << 5)

#घोषणा IMX7ULP_MAX_RUN_FREQ	528000

/* cpufreq-dt device रेजिस्टरed by imx-cpufreq-dt */
अटल काष्ठा platक्रमm_device *cpufreq_dt_pdev;
अटल काष्ठा opp_table *cpufreq_opp_table;
अटल काष्ठा device *cpu_dev;

क्रमागत IMX7ULP_CPUFREQ_CLKS अणु
	ARM,
	CORE,
	SCS_SEL,
	HSRUN_CORE,
	HSRUN_SCS_SEL,
	FIRC,
पूर्ण;

अटल काष्ठा clk_bulk_data imx7ulp_clks[] = अणु
	अणु .id = "arm" पूर्ण,
	अणु .id = "core" पूर्ण,
	अणु .id = "scs_sel" पूर्ण,
	अणु .id = "hsrun_core" पूर्ण,
	अणु .id = "hsrun_scs_sel" पूर्ण,
	अणु .id = "firc" पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक imx7ulp_get_पूर्णांकermediate(काष्ठा cpufreq_policy *policy,
					     अचिन्हित पूर्णांक index)
अणु
	वापस clk_get_rate(imx7ulp_clks[FIRC].clk);
पूर्ण

अटल पूर्णांक imx7ulp_target_पूर्णांकermediate(काष्ठा cpufreq_policy *policy,
					अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक newfreq = policy->freq_table[index].frequency;

	clk_set_parent(imx7ulp_clks[SCS_SEL].clk, imx7ulp_clks[FIRC].clk);
	clk_set_parent(imx7ulp_clks[HSRUN_SCS_SEL].clk, imx7ulp_clks[FIRC].clk);

	अगर (newfreq > IMX7ULP_MAX_RUN_FREQ)
		clk_set_parent(imx7ulp_clks[ARM].clk,
			       imx7ulp_clks[HSRUN_CORE].clk);
	अन्यथा
		clk_set_parent(imx7ulp_clks[ARM].clk, imx7ulp_clks[CORE].clk);

	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_dt_platक्रमm_data imx7ulp_data = अणु
	.target_पूर्णांकermediate = imx7ulp_target_पूर्णांकermediate,
	.get_पूर्णांकermediate = imx7ulp_get_पूर्णांकermediate,
पूर्ण;

अटल पूर्णांक imx_cpufreq_dt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_device *dt_pdev;
	u32 cell_value, supported_hw[2];
	पूर्णांक speed_grade, mkt_segment;
	पूर्णांक ret;

	cpu_dev = get_cpu_device(0);

	अगर (!of_find_property(cpu_dev->of_node, "cpu-supply", शून्य))
		वापस -ENODEV;

	अगर (of_machine_is_compatible("fsl,imx7ulp")) अणु
		ret = clk_bulk_get(cpu_dev, ARRAY_SIZE(imx7ulp_clks),
				   imx7ulp_clks);
		अगर (ret)
			वापस ret;

		dt_pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "cpufreq-dt",
							-1, &imx7ulp_data,
							माप(imx7ulp_data));
		अगर (IS_ERR(dt_pdev)) अणु
			clk_bulk_put(ARRAY_SIZE(imx7ulp_clks), imx7ulp_clks);
			ret = PTR_ERR(dt_pdev);
			dev_err(&pdev->dev, "Failed to register cpufreq-dt: %d\n", ret);
			वापस ret;
		पूर्ण

		cpufreq_dt_pdev = dt_pdev;

		वापस 0;
	पूर्ण

	ret = nvmem_cell_पढ़ो_u32(cpu_dev, "speed_grade", &cell_value);
	अगर (ret)
		वापस ret;

	अगर (of_machine_is_compatible("fsl,imx8mn") ||
	    of_machine_is_compatible("fsl,imx8mp"))
		speed_grade = (cell_value & IMX8MN_OCOTP_CFG3_SPEED_GRADE_MASK)
			      >> OCOTP_CFG3_SPEED_GRADE_SHIFT;
	अन्यथा
		speed_grade = (cell_value & OCOTP_CFG3_SPEED_GRADE_MASK)
			      >> OCOTP_CFG3_SPEED_GRADE_SHIFT;

	अगर (of_machine_is_compatible("fsl,imx8mp"))
		mkt_segment = (cell_value & IMX8MP_OCOTP_CFG3_MKT_SEGMENT_MASK)
			       >> IMX8MP_OCOTP_CFG3_MKT_SEGMENT_SHIFT;
	अन्यथा
		mkt_segment = (cell_value & OCOTP_CFG3_MKT_SEGMENT_MASK)
			       >> OCOTP_CFG3_MKT_SEGMENT_SHIFT;

	/*
	 * Early samples without fuses written report "0 0" which may NOT
	 * match any OPP defined in DT. So clamp to minimum OPP defined in
	 * DT to aव्योम warning क्रम "no OPPs".
	 *
	 * Applies to i.MX8M series SoCs.
	 */
	अगर (mkt_segment == 0 && speed_grade == 0) अणु
		अगर (of_machine_is_compatible("fsl,imx8mm") ||
		    of_machine_is_compatible("fsl,imx8mq"))
			speed_grade = 1;
		अगर (of_machine_is_compatible("fsl,imx8mn") ||
		    of_machine_is_compatible("fsl,imx8mp"))
			speed_grade = 0xb;
	पूर्ण

	supported_hw[0] = BIT(speed_grade);
	supported_hw[1] = BIT(mkt_segment);
	dev_info(&pdev->dev, "cpu speed grade %d mkt segment %d supported-hw %#x %#x\n",
			speed_grade, mkt_segment, supported_hw[0], supported_hw[1]);

	cpufreq_opp_table = dev_pm_opp_set_supported_hw(cpu_dev, supported_hw, 2);
	अगर (IS_ERR(cpufreq_opp_table)) अणु
		ret = PTR_ERR(cpufreq_opp_table);
		dev_err(&pdev->dev, "Failed to set supported opp: %d\n", ret);
		वापस ret;
	पूर्ण

	cpufreq_dt_pdev = platक्रमm_device_रेजिस्टर_data(
			&pdev->dev, "cpufreq-dt", -1, शून्य, 0);
	अगर (IS_ERR(cpufreq_dt_pdev)) अणु
		dev_pm_opp_put_supported_hw(cpufreq_opp_table);
		ret = PTR_ERR(cpufreq_dt_pdev);
		dev_err(&pdev->dev, "Failed to register cpufreq-dt: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_cpufreq_dt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	platक्रमm_device_unरेजिस्टर(cpufreq_dt_pdev);
	अगर (!of_machine_is_compatible("fsl,imx7ulp"))
		dev_pm_opp_put_supported_hw(cpufreq_opp_table);
	अन्यथा
		clk_bulk_put(ARRAY_SIZE(imx7ulp_clks), imx7ulp_clks);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver imx_cpufreq_dt_driver = अणु
	.probe = imx_cpufreq_dt_probe,
	.हटाओ = imx_cpufreq_dt_हटाओ,
	.driver = अणु
		.name = "imx-cpufreq-dt",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_cpufreq_dt_driver);

MODULE_ALIAS("platform:imx-cpufreq-dt");
MODULE_DESCRIPTION("Freescale i.MX cpufreq speed grading driver");
MODULE_LICENSE("GPL v2");
