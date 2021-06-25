<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

/*
 * In Certain QCOM SoCs like apq8096 and msm8996 that have KRYO processors,
 * the CPU frequency subset and voltage value of each OPP varies
 * based on the silicon variant in use. Qualcomm Process Voltage Scaling Tables
 * defines the voltage and frequency value based on the msm-id in SMEM
 * and speedbin blown in the efuse combination.
 * The qcom-cpufreq-nvmem driver पढ़ोs the msm-id and efuse value from the SoC
 * to provide the OPP framework with required inक्रमmation.
 * This is used to determine the voltage and frequency value क्रम each OPP of
 * operating-poपूर्णांकs-v2 table when it is parsed by the OPP framework.
 */

#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/sस्मृति.स>

#घोषणा MSM_ID_SMEM	137

क्रमागत _msm_id अणु
	MSM8996V3 = 0xF6ul,
	APQ8096V3 = 0x123ul,
	MSM8996SG = 0x131ul,
	APQ8096SG = 0x138ul,
पूर्ण;

क्रमागत _msm8996_version अणु
	MSM8996_V3,
	MSM8996_SG,
	NUM_OF_MSM8996_VERSIONS,
पूर्ण;

काष्ठा qcom_cpufreq_drv;

काष्ठा qcom_cpufreq_match_data अणु
	पूर्णांक (*get_version)(काष्ठा device *cpu_dev,
			   काष्ठा nvmem_cell *speedbin_nvmem,
			   अक्षर **pvs_name,
			   काष्ठा qcom_cpufreq_drv *drv);
	स्थिर अक्षर **genpd_names;
पूर्ण;

काष्ठा qcom_cpufreq_drv अणु
	काष्ठा opp_table **names_opp_tables;
	काष्ठा opp_table **hw_opp_tables;
	काष्ठा opp_table **genpd_opp_tables;
	u32 versions;
	स्थिर काष्ठा qcom_cpufreq_match_data *data;
पूर्ण;

अटल काष्ठा platक्रमm_device *cpufreq_dt_pdev, *cpufreq_pdev;

अटल व्योम get_krait_bin_क्रमmat_a(काष्ठा device *cpu_dev,
					  पूर्णांक *speed, पूर्णांक *pvs, पूर्णांक *pvs_ver,
					  काष्ठा nvmem_cell *pvs_nvmem, u8 *buf)
अणु
	u32 pte_efuse;

	pte_efuse = *((u32 *)buf);

	*speed = pte_efuse & 0xf;
	अगर (*speed == 0xf)
		*speed = (pte_efuse >> 4) & 0xf;

	अगर (*speed == 0xf) अणु
		*speed = 0;
		dev_warn(cpu_dev, "Speed bin: Defaulting to %d\n", *speed);
	पूर्ण अन्यथा अणु
		dev_dbg(cpu_dev, "Speed bin: %d\n", *speed);
	पूर्ण

	*pvs = (pte_efuse >> 10) & 0x7;
	अगर (*pvs == 0x7)
		*pvs = (pte_efuse >> 13) & 0x7;

	अगर (*pvs == 0x7) अणु
		*pvs = 0;
		dev_warn(cpu_dev, "PVS bin: Defaulting to %d\n", *pvs);
	पूर्ण अन्यथा अणु
		dev_dbg(cpu_dev, "PVS bin: %d\n", *pvs);
	पूर्ण
पूर्ण

अटल व्योम get_krait_bin_क्रमmat_b(काष्ठा device *cpu_dev,
					  पूर्णांक *speed, पूर्णांक *pvs, पूर्णांक *pvs_ver,
					  काष्ठा nvmem_cell *pvs_nvmem, u8 *buf)
अणु
	u32 pte_efuse, redundant_sel;

	pte_efuse = *((u32 *)buf);
	redundant_sel = (pte_efuse >> 24) & 0x7;

	*pvs_ver = (pte_efuse >> 4) & 0x3;

	चयन (redundant_sel) अणु
	हाल 1:
		*pvs = ((pte_efuse >> 28) & 0x8) | ((pte_efuse >> 6) & 0x7);
		*speed = (pte_efuse >> 27) & 0xf;
		अवरोध;
	हाल 2:
		*pvs = (pte_efuse >> 27) & 0xf;
		*speed = pte_efuse & 0x7;
		अवरोध;
	शेष:
		/* 4 bits of PVS are in efuse रेजिस्टर bits 31, 8-6. */
		*pvs = ((pte_efuse >> 28) & 0x8) | ((pte_efuse >> 6) & 0x7);
		*speed = pte_efuse & 0x7;
	पूर्ण

	/* Check SPEED_BIN_BLOW_STATUS */
	अगर (pte_efuse & BIT(3)) अणु
		dev_dbg(cpu_dev, "Speed bin: %d\n", *speed);
	पूर्ण अन्यथा अणु
		dev_warn(cpu_dev, "Speed bin not set. Defaulting to 0!\n");
		*speed = 0;
	पूर्ण

	/* Check PVS_BLOW_STATUS */
	pte_efuse = *(((u32 *)buf) + 4);
	pte_efuse &= BIT(21);
	अगर (pte_efuse) अणु
		dev_dbg(cpu_dev, "PVS bin: %d\n", *pvs);
	पूर्ण अन्यथा अणु
		dev_warn(cpu_dev, "PVS bin not set. Defaulting to 0!\n");
		*pvs = 0;
	पूर्ण

	dev_dbg(cpu_dev, "PVS version: %d\n", *pvs_ver);
पूर्ण

अटल क्रमागत _msm8996_version qcom_cpufreq_get_msm_id(व्योम)
अणु
	माप_प्रकार len;
	u32 *msm_id;
	क्रमागत _msm8996_version version;

	msm_id = qcom_smem_get(QCOM_SMEM_HOST_ANY, MSM_ID_SMEM, &len);
	अगर (IS_ERR(msm_id))
		वापस NUM_OF_MSM8996_VERSIONS;

	/* The first 4 bytes are क्रमmat, next to them is the actual msm-id */
	msm_id++;

	चयन ((क्रमागत _msm_id)*msm_id) अणु
	हाल MSM8996V3:
	हाल APQ8096V3:
		version = MSM8996_V3;
		अवरोध;
	हाल MSM8996SG:
	हाल APQ8096SG:
		version = MSM8996_SG;
		अवरोध;
	शेष:
		version = NUM_OF_MSM8996_VERSIONS;
	पूर्ण

	वापस version;
पूर्ण

अटल पूर्णांक qcom_cpufreq_kryo_name_version(काष्ठा device *cpu_dev,
					  काष्ठा nvmem_cell *speedbin_nvmem,
					  अक्षर **pvs_name,
					  काष्ठा qcom_cpufreq_drv *drv)
अणु
	माप_प्रकार len;
	u8 *speedbin;
	क्रमागत _msm8996_version msm8996_version;
	*pvs_name = शून्य;

	msm8996_version = qcom_cpufreq_get_msm_id();
	अगर (NUM_OF_MSM8996_VERSIONS == msm8996_version) अणु
		dev_err(cpu_dev, "Not Snapdragon 820/821!");
		वापस -ENODEV;
	पूर्ण

	speedbin = nvmem_cell_पढ़ो(speedbin_nvmem, &len);
	अगर (IS_ERR(speedbin))
		वापस PTR_ERR(speedbin);

	चयन (msm8996_version) अणु
	हाल MSM8996_V3:
		drv->versions = 1 << (अचिन्हित पूर्णांक)(*speedbin);
		अवरोध;
	हाल MSM8996_SG:
		drv->versions = 1 << ((अचिन्हित पूर्णांक)(*speedbin) + 4);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	kमुक्त(speedbin);
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_cpufreq_krait_name_version(काष्ठा device *cpu_dev,
					   काष्ठा nvmem_cell *speedbin_nvmem,
					   अक्षर **pvs_name,
					   काष्ठा qcom_cpufreq_drv *drv)
अणु
	पूर्णांक speed = 0, pvs = 0, pvs_ver = 0;
	u8 *speedbin;
	माप_प्रकार len;

	speedbin = nvmem_cell_पढ़ो(speedbin_nvmem, &len);

	अगर (IS_ERR(speedbin))
		वापस PTR_ERR(speedbin);

	चयन (len) अणु
	हाल 4:
		get_krait_bin_क्रमmat_a(cpu_dev, &speed, &pvs, &pvs_ver,
				       speedbin_nvmem, speedbin);
		अवरोध;
	हाल 8:
		get_krait_bin_क्रमmat_b(cpu_dev, &speed, &pvs, &pvs_ver,
				       speedbin_nvmem, speedbin);
		अवरोध;
	शेष:
		dev_err(cpu_dev, "Unable to read nvmem data. Defaulting to 0!\n");
		वापस -ENODEV;
	पूर्ण

	snम_लिखो(*pvs_name, माप("speedXX-pvsXX-vXX"), "speed%d-pvs%d-v%d",
		 speed, pvs, pvs_ver);

	drv->versions = (1 << speed);

	kमुक्त(speedbin);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा qcom_cpufreq_match_data match_data_kryo = अणु
	.get_version = qcom_cpufreq_kryo_name_version,
पूर्ण;

अटल स्थिर काष्ठा qcom_cpufreq_match_data match_data_krait = अणु
	.get_version = qcom_cpufreq_krait_name_version,
पूर्ण;

अटल स्थिर अक्षर *qcs404_genpd_names[] = अणु "cpr", शून्य पूर्ण;

अटल स्थिर काष्ठा qcom_cpufreq_match_data match_data_qcs404 = अणु
	.genpd_names = qcs404_genpd_names,
पूर्ण;

अटल पूर्णांक qcom_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_cpufreq_drv *drv;
	काष्ठा nvmem_cell *speedbin_nvmem;
	काष्ठा device_node *np;
	काष्ठा device *cpu_dev;
	अक्षर *pvs_name = "speedXX-pvsXX-vXX";
	अचिन्हित cpu;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	cpu_dev = get_cpu_device(0);
	अगर (!cpu_dev)
		वापस -ENODEV;

	np = dev_pm_opp_of_get_opp_desc_node(cpu_dev);
	अगर (!np)
		वापस -ENOENT;

	ret = of_device_is_compatible(np, "operating-points-v2-kryo-cpu");
	अगर (!ret) अणु
		of_node_put(np);
		वापस -ENOENT;
	पूर्ण

	drv = kzalloc(माप(*drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;

	match = pdev->dev.platक्रमm_data;
	drv->data = match->data;
	अगर (!drv->data) अणु
		ret = -ENODEV;
		जाओ मुक्त_drv;
	पूर्ण

	अगर (drv->data->get_version) अणु
		speedbin_nvmem = of_nvmem_cell_get(np, शून्य);
		अगर (IS_ERR(speedbin_nvmem)) अणु
			अगर (PTR_ERR(speedbin_nvmem) != -EPROBE_DEFER)
				dev_err(cpu_dev,
					"Could not get nvmem cell: %ld\n",
					PTR_ERR(speedbin_nvmem));
			ret = PTR_ERR(speedbin_nvmem);
			जाओ मुक्त_drv;
		पूर्ण

		ret = drv->data->get_version(cpu_dev,
							speedbin_nvmem, &pvs_name, drv);
		अगर (ret) अणु
			nvmem_cell_put(speedbin_nvmem);
			जाओ मुक्त_drv;
		पूर्ण
		nvmem_cell_put(speedbin_nvmem);
	पूर्ण
	of_node_put(np);

	drv->names_opp_tables = kसुस्मृति(num_possible_cpus(),
				  माप(*drv->names_opp_tables),
				  GFP_KERNEL);
	अगर (!drv->names_opp_tables) अणु
		ret = -ENOMEM;
		जाओ मुक्त_drv;
	पूर्ण
	drv->hw_opp_tables = kसुस्मृति(num_possible_cpus(),
				  माप(*drv->hw_opp_tables),
				  GFP_KERNEL);
	अगर (!drv->hw_opp_tables) अणु
		ret = -ENOMEM;
		जाओ मुक्त_opp_names;
	पूर्ण

	drv->genpd_opp_tables = kसुस्मृति(num_possible_cpus(),
					माप(*drv->genpd_opp_tables),
					GFP_KERNEL);
	अगर (!drv->genpd_opp_tables) अणु
		ret = -ENOMEM;
		जाओ मुक्त_opp;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		cpu_dev = get_cpu_device(cpu);
		अगर (शून्य == cpu_dev) अणु
			ret = -ENODEV;
			जाओ मुक्त_genpd_opp;
		पूर्ण

		अगर (drv->data->get_version) अणु

			अगर (pvs_name) अणु
				drv->names_opp_tables[cpu] = dev_pm_opp_set_prop_name(
								     cpu_dev,
								     pvs_name);
				अगर (IS_ERR(drv->names_opp_tables[cpu])) अणु
					ret = PTR_ERR(drv->names_opp_tables[cpu]);
					dev_err(cpu_dev, "Failed to add OPP name %s\n",
						pvs_name);
					जाओ मुक्त_opp;
				पूर्ण
			पूर्ण

			drv->hw_opp_tables[cpu] = dev_pm_opp_set_supported_hw(
									 cpu_dev, &drv->versions, 1);
			अगर (IS_ERR(drv->hw_opp_tables[cpu])) अणु
				ret = PTR_ERR(drv->hw_opp_tables[cpu]);
				dev_err(cpu_dev,
					"Failed to set supported hardware\n");
				जाओ मुक्त_genpd_opp;
			पूर्ण
		पूर्ण

		अगर (drv->data->genpd_names) अणु
			drv->genpd_opp_tables[cpu] =
				dev_pm_opp_attach_genpd(cpu_dev,
							drv->data->genpd_names,
							शून्य);
			अगर (IS_ERR(drv->genpd_opp_tables[cpu])) अणु
				ret = PTR_ERR(drv->genpd_opp_tables[cpu]);
				अगर (ret != -EPROBE_DEFER)
					dev_err(cpu_dev,
						"Could not attach to pm_domain: %d\n",
						ret);
				जाओ मुक्त_genpd_opp;
			पूर्ण
		पूर्ण
	पूर्ण

	cpufreq_dt_pdev = platक्रमm_device_रेजिस्टर_simple("cpufreq-dt", -1,
							  शून्य, 0);
	अगर (!IS_ERR(cpufreq_dt_pdev)) अणु
		platक्रमm_set_drvdata(pdev, drv);
		वापस 0;
	पूर्ण

	ret = PTR_ERR(cpufreq_dt_pdev);
	dev_err(cpu_dev, "Failed to register platform device\n");

मुक्त_genpd_opp:
	क्रम_each_possible_cpu(cpu) अणु
		अगर (IS_ERR(drv->genpd_opp_tables[cpu]))
			अवरोध;
		dev_pm_opp_detach_genpd(drv->genpd_opp_tables[cpu]);
	पूर्ण
	kमुक्त(drv->genpd_opp_tables);
मुक्त_opp:
	क्रम_each_possible_cpu(cpu) अणु
		अगर (IS_ERR(drv->names_opp_tables[cpu]))
			अवरोध;
		dev_pm_opp_put_prop_name(drv->names_opp_tables[cpu]);
	पूर्ण
	क्रम_each_possible_cpu(cpu) अणु
		अगर (IS_ERR(drv->hw_opp_tables[cpu]))
			अवरोध;
		dev_pm_opp_put_supported_hw(drv->hw_opp_tables[cpu]);
	पूर्ण
	kमुक्त(drv->hw_opp_tables);
मुक्त_opp_names:
	kमुक्त(drv->names_opp_tables);
मुक्त_drv:
	kमुक्त(drv);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_cpufreq_drv *drv = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक cpu;

	platक्रमm_device_unरेजिस्टर(cpufreq_dt_pdev);

	क्रम_each_possible_cpu(cpu) अणु
		dev_pm_opp_put_supported_hw(drv->names_opp_tables[cpu]);
		dev_pm_opp_put_supported_hw(drv->hw_opp_tables[cpu]);
		dev_pm_opp_detach_genpd(drv->genpd_opp_tables[cpu]);
	पूर्ण

	kमुक्त(drv->names_opp_tables);
	kमुक्त(drv->hw_opp_tables);
	kमुक्त(drv->genpd_opp_tables);
	kमुक्त(drv);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_cpufreq_driver = अणु
	.probe = qcom_cpufreq_probe,
	.हटाओ = qcom_cpufreq_हटाओ,
	.driver = अणु
		.name = "qcom-cpufreq-nvmem",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_cpufreq_match_list[] __initस्थिर = अणु
	अणु .compatible = "qcom,apq8096", .data = &match_data_kryo पूर्ण,
	अणु .compatible = "qcom,msm8996", .data = &match_data_kryo पूर्ण,
	अणु .compatible = "qcom,qcs404", .data = &match_data_qcs404 पूर्ण,
	अणु .compatible = "qcom,ipq8064", .data = &match_data_krait पूर्ण,
	अणु .compatible = "qcom,apq8064", .data = &match_data_krait पूर्ण,
	अणु .compatible = "qcom,msm8974", .data = &match_data_krait पूर्ण,
	अणु .compatible = "qcom,msm8960", .data = &match_data_krait पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_cpufreq_match_list);

/*
 * Since the driver depends on smem and nvmem drivers, which may
 * वापस EPROBE_DEFER, all the real activity is करोne in the probe,
 * which may be defered as well. The init here is only रेजिस्टरing
 * the driver and the platक्रमm device.
 */
अटल पूर्णांक __init qcom_cpufreq_init(व्योम)
अणु
	काष्ठा device_node *np = of_find_node_by_path("/");
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	अगर (!np)
		वापस -ENODEV;

	match = of_match_node(qcom_cpufreq_match_list, np);
	of_node_put(np);
	अगर (!match)
		वापस -ENODEV;

	ret = platक्रमm_driver_रेजिस्टर(&qcom_cpufreq_driver);
	अगर (unlikely(ret < 0))
		वापस ret;

	cpufreq_pdev = platक्रमm_device_रेजिस्टर_data(शून्य, "qcom-cpufreq-nvmem",
						     -1, match, माप(*match));
	ret = PTR_ERR_OR_ZERO(cpufreq_pdev);
	अगर (0 == ret)
		वापस 0;

	platक्रमm_driver_unरेजिस्टर(&qcom_cpufreq_driver);
	वापस ret;
पूर्ण
module_init(qcom_cpufreq_init);

अटल व्योम __निकास qcom_cpufreq_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(cpufreq_pdev);
	platक्रमm_driver_unरेजिस्टर(&qcom_cpufreq_driver);
पूर्ण
module_निकास(qcom_cpufreq_निकास);

MODULE_DESCRIPTION("Qualcomm Technologies, Inc. CPUfreq driver");
MODULE_LICENSE("GPL v2");
