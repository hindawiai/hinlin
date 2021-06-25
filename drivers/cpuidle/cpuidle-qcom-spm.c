<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011-2014, The Linux Foundation. All rights reserved.
 * Copyright (c) 2014,2015, Linaro Ltd.
 *
 * SAW घातer controller driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/qcom_scm.h>

#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/suspend.h>

#समावेश "dt_idle_states.h"

#घोषणा MAX_PMIC_DATA		2
#घोषणा MAX_SEQ_DATA		64
#घोषणा SPM_CTL_INDEX		0x7f
#घोषणा SPM_CTL_INDEX_SHIFT	4
#घोषणा SPM_CTL_EN		BIT(0)

क्रमागत pm_sleep_mode अणु
	PM_SLEEP_MODE_STBY,
	PM_SLEEP_MODE_RET,
	PM_SLEEP_MODE_SPC,
	PM_SLEEP_MODE_PC,
	PM_SLEEP_MODE_NR,
पूर्ण;

क्रमागत spm_reg अणु
	SPM_REG_CFG,
	SPM_REG_SPM_CTL,
	SPM_REG_DLY,
	SPM_REG_PMIC_DLY,
	SPM_REG_PMIC_DATA_0,
	SPM_REG_PMIC_DATA_1,
	SPM_REG_VCTL,
	SPM_REG_SEQ_ENTRY,
	SPM_REG_SPM_STS,
	SPM_REG_PMIC_STS,
	SPM_REG_NR,
पूर्ण;

काष्ठा spm_reg_data अणु
	स्थिर u8 *reg_offset;
	u32 spm_cfg;
	u32 spm_dly;
	u32 pmic_dly;
	u32 pmic_data[MAX_PMIC_DATA];
	u8 seq[MAX_SEQ_DATA];
	u8 start_index[PM_SLEEP_MODE_NR];
पूर्ण;

काष्ठा spm_driver_data अणु
	काष्ठा cpuidle_driver cpuidle_driver;
	व्योम __iomem *reg_base;
	स्थिर काष्ठा spm_reg_data *reg_data;
पूर्ण;

अटल स्थिर u8 spm_reg_offset_v2_1[SPM_REG_NR] = अणु
	[SPM_REG_CFG]		= 0x08,
	[SPM_REG_SPM_CTL]	= 0x30,
	[SPM_REG_DLY]		= 0x34,
	[SPM_REG_SEQ_ENTRY]	= 0x80,
पूर्ण;

/* SPM रेजिस्टर data क्रम 8974, 8084 */
अटल स्थिर काष्ठा spm_reg_data spm_reg_8974_8084_cpu  = अणु
	.reg_offset = spm_reg_offset_v2_1,
	.spm_cfg = 0x1,
	.spm_dly = 0x3C102800,
	.seq = अणु 0x03, 0x0B, 0x0F, 0x00, 0x20, 0x80, 0x10, 0xE8, 0x5B, 0x03,
		0x3B, 0xE8, 0x5B, 0x82, 0x10, 0x0B, 0x30, 0x06, 0x26, 0x30,
		0x0F पूर्ण,
	.start_index[PM_SLEEP_MODE_STBY] = 0,
	.start_index[PM_SLEEP_MODE_SPC] = 3,
पूर्ण;

अटल स्थिर u8 spm_reg_offset_v1_1[SPM_REG_NR] = अणु
	[SPM_REG_CFG]		= 0x08,
	[SPM_REG_SPM_CTL]	= 0x20,
	[SPM_REG_PMIC_DLY]	= 0x24,
	[SPM_REG_PMIC_DATA_0]	= 0x28,
	[SPM_REG_PMIC_DATA_1]	= 0x2C,
	[SPM_REG_SEQ_ENTRY]	= 0x80,
पूर्ण;

/* SPM रेजिस्टर data क्रम 8064 */
अटल स्थिर काष्ठा spm_reg_data spm_reg_8064_cpu = अणु
	.reg_offset = spm_reg_offset_v1_1,
	.spm_cfg = 0x1F,
	.pmic_dly = 0x02020004,
	.pmic_data[0] = 0x0084009C,
	.pmic_data[1] = 0x00A4001C,
	.seq = अणु 0x03, 0x0F, 0x00, 0x24, 0x54, 0x10, 0x09, 0x03, 0x01,
		0x10, 0x54, 0x30, 0x0C, 0x24, 0x30, 0x0F पूर्ण,
	.start_index[PM_SLEEP_MODE_STBY] = 0,
	.start_index[PM_SLEEP_MODE_SPC] = 2,
पूर्ण;

अटल अंतरभूत व्योम spm_रेजिस्टर_ग_लिखो(काष्ठा spm_driver_data *drv,
					क्रमागत spm_reg reg, u32 val)
अणु
	अगर (drv->reg_data->reg_offset[reg])
		ग_लिखोl_relaxed(val, drv->reg_base +
				drv->reg_data->reg_offset[reg]);
पूर्ण

/* Ensure a guaranteed ग_लिखो, beक्रमe वापस */
अटल अंतरभूत व्योम spm_रेजिस्टर_ग_लिखो_sync(काष्ठा spm_driver_data *drv,
					क्रमागत spm_reg reg, u32 val)
अणु
	u32 ret;

	अगर (!drv->reg_data->reg_offset[reg])
		वापस;

	करो अणु
		ग_लिखोl_relaxed(val, drv->reg_base +
				drv->reg_data->reg_offset[reg]);
		ret = पढ़ोl_relaxed(drv->reg_base +
				drv->reg_data->reg_offset[reg]);
		अगर (ret == val)
			अवरोध;
		cpu_relax();
	पूर्ण जबतक (1);
पूर्ण

अटल अंतरभूत u32 spm_रेजिस्टर_पढ़ो(काष्ठा spm_driver_data *drv,
					क्रमागत spm_reg reg)
अणु
	वापस पढ़ोl_relaxed(drv->reg_base + drv->reg_data->reg_offset[reg]);
पूर्ण

अटल व्योम spm_set_low_घातer_mode(काष्ठा spm_driver_data *drv,
					क्रमागत pm_sleep_mode mode)
अणु
	u32 start_index;
	u32 ctl_val;

	start_index = drv->reg_data->start_index[mode];

	ctl_val = spm_रेजिस्टर_पढ़ो(drv, SPM_REG_SPM_CTL);
	ctl_val &= ~(SPM_CTL_INDEX << SPM_CTL_INDEX_SHIFT);
	ctl_val |= start_index << SPM_CTL_INDEX_SHIFT;
	ctl_val |= SPM_CTL_EN;
	spm_रेजिस्टर_ग_लिखो_sync(drv, SPM_REG_SPM_CTL, ctl_val);
पूर्ण

अटल पूर्णांक qcom_pm_collapse(अचिन्हित दीर्घ पूर्णांक unused)
अणु
	qcom_scm_cpu_घातer_करोwn(QCOM_SCM_CPU_PWR_DOWN_L2_ON);

	/*
	 * Returns here only अगर there was a pending पूर्णांकerrupt and we did not
	 * घातer करोwn as a result.
	 */
	वापस -1;
पूर्ण

अटल पूर्णांक qcom_cpu_spc(काष्ठा spm_driver_data *drv)
अणु
	पूर्णांक ret;

	spm_set_low_घातer_mode(drv, PM_SLEEP_MODE_SPC);
	ret = cpu_suspend(0, qcom_pm_collapse);
	/*
	 * ARM common code executes WFI without calling पूर्णांकo our driver and
	 * अगर the SPM mode is not reset, then we may accidently घातer करोwn the
	 * cpu when we पूर्णांकended only to gate the cpu घड़ी.
	 * Ensure the state is set to standby beक्रमe वापसing.
	 */
	spm_set_low_घातer_mode(drv, PM_SLEEP_MODE_STBY);

	वापस ret;
पूर्ण

अटल पूर्णांक spm_enter_idle_state(काष्ठा cpuidle_device *dev,
				काष्ठा cpuidle_driver *drv, पूर्णांक idx)
अणु
	काष्ठा spm_driver_data *data = container_of(drv, काष्ठा spm_driver_data,
						    cpuidle_driver);

	वापस CPU_PM_CPU_IDLE_ENTER_PARAM(qcom_cpu_spc, idx, data);
पूर्ण

अटल काष्ठा cpuidle_driver qcom_spm_idle_driver = अणु
	.name = "qcom_spm",
	.owner = THIS_MODULE,
	.states[0] = अणु
		.enter			= spm_enter_idle_state,
		.निकास_latency		= 1,
		.target_residency	= 1,
		.घातer_usage		= अच_पूर्णांक_उच्च,
		.name			= "WFI",
		.desc			= "ARM WFI",
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_idle_state_match[] = अणु
	अणु .compatible = "qcom,idle-state-spc", .data = spm_enter_idle_state पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक spm_cpuidle_init(काष्ठा cpuidle_driver *drv, पूर्णांक cpu)
अणु
	पूर्णांक ret;

	स_नकल(drv, &qcom_spm_idle_driver, माप(*drv));
	drv->cpumask = (काष्ठा cpumask *)cpumask_of(cpu);

	/* Parse idle states from device tree */
	ret = dt_init_idle_driver(drv, qcom_idle_state_match, 1);
	अगर (ret <= 0)
		वापस ret ? : -ENODEV;

	/* We have atleast one घातer करोwn mode */
	वापस qcom_scm_set_warm_boot_addr(cpu_resume_arm, drv->cpumask);
पूर्ण

अटल काष्ठा spm_driver_data *spm_get_drv(काष्ठा platक्रमm_device *pdev,
		पूर्णांक *spm_cpu)
अणु
	काष्ठा spm_driver_data *drv = शून्य;
	काष्ठा device_node *cpu_node, *saw_node;
	पूर्णांक cpu;
	bool found = 0;

	क्रम_each_possible_cpu(cpu) अणु
		cpu_node = of_cpu_device_node_get(cpu);
		अगर (!cpu_node)
			जारी;
		saw_node = of_parse_phandle(cpu_node, "qcom,saw", 0);
		found = (saw_node == pdev->dev.of_node);
		of_node_put(saw_node);
		of_node_put(cpu_node);
		अगर (found)
			अवरोध;
	पूर्ण

	अगर (found) अणु
		drv = devm_kzalloc(&pdev->dev, माप(*drv), GFP_KERNEL);
		अगर (drv)
			*spm_cpu = cpu;
	पूर्ण

	वापस drv;
पूर्ण

अटल स्थिर काष्ठा of_device_id spm_match_table[] = अणु
	अणु .compatible = "qcom,msm8974-saw2-v2.1-cpu",
	  .data = &spm_reg_8974_8084_cpu पूर्ण,
	अणु .compatible = "qcom,apq8084-saw2-v2.1-cpu",
	  .data = &spm_reg_8974_8084_cpu पूर्ण,
	अणु .compatible = "qcom,apq8064-saw2-v1.1-cpu",
	  .data = &spm_reg_8064_cpu पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक spm_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spm_driver_data *drv;
	काष्ठा resource *res;
	स्थिर काष्ठा of_device_id *match_id;
	व्योम __iomem *addr;
	पूर्णांक cpu, ret;

	अगर (!qcom_scm_is_available())
		वापस -EPROBE_DEFER;

	drv = spm_get_drv(pdev, &cpu);
	अगर (!drv)
		वापस -EINVAL;
	platक्रमm_set_drvdata(pdev, drv);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	drv->reg_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(drv->reg_base))
		वापस PTR_ERR(drv->reg_base);

	match_id = of_match_node(spm_match_table, pdev->dev.of_node);
	अगर (!match_id)
		वापस -ENODEV;

	drv->reg_data = match_id->data;

	ret = spm_cpuidle_init(&drv->cpuidle_driver, cpu);
	अगर (ret)
		वापस ret;

	/* Write the SPM sequences first.. */
	addr = drv->reg_base + drv->reg_data->reg_offset[SPM_REG_SEQ_ENTRY];
	__ioग_लिखो32_copy(addr, drv->reg_data->seq,
			ARRAY_SIZE(drv->reg_data->seq) / 4);

	/*
	 * ..and then the control रेजिस्टरs.
	 * On some SoC अगर the control रेजिस्टरs are written first and अगर the
	 * CPU was held in reset, the reset संकेत could trigger the SPM state
	 * machine, beक्रमe the sequences are completely written.
	 */
	spm_रेजिस्टर_ग_लिखो(drv, SPM_REG_CFG, drv->reg_data->spm_cfg);
	spm_रेजिस्टर_ग_लिखो(drv, SPM_REG_DLY, drv->reg_data->spm_dly);
	spm_रेजिस्टर_ग_लिखो(drv, SPM_REG_PMIC_DLY, drv->reg_data->pmic_dly);
	spm_रेजिस्टर_ग_लिखो(drv, SPM_REG_PMIC_DATA_0,
				drv->reg_data->pmic_data[0]);
	spm_रेजिस्टर_ग_लिखो(drv, SPM_REG_PMIC_DATA_1,
				drv->reg_data->pmic_data[1]);

	/* Set up Standby as the शेष low घातer mode */
	spm_set_low_घातer_mode(drv, PM_SLEEP_MODE_STBY);

	वापस cpuidle_रेजिस्टर(&drv->cpuidle_driver, शून्य);
पूर्ण

अटल पूर्णांक spm_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spm_driver_data *drv = platक्रमm_get_drvdata(pdev);

	cpuidle_unरेजिस्टर(&drv->cpuidle_driver);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver spm_driver = अणु
	.probe = spm_dev_probe,
	.हटाओ = spm_dev_हटाओ,
	.driver = अणु
		.name = "saw",
		.of_match_table = spm_match_table,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(spm_driver);
