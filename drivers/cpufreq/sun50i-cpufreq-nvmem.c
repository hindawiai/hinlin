<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Allwinner CPUFreq nvmem based driver
 *
 * The sun50i-cpufreq-nvmem driver पढ़ोs the efuse value from the SoC to
 * provide the OPP framework with required inक्रमmation.
 *
 * Copyright (C) 2019 Yangtao Li <tiny.windzz@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/slab.h>

#घोषणा MAX_NAME_LEN	7

#घोषणा NVMEM_MASK	0x7
#घोषणा NVMEM_SHIFT	5

अटल काष्ठा platक्रमm_device *cpufreq_dt_pdev, *sun50i_cpufreq_pdev;

/**
 * sun50i_cpufreq_get_efuse() - Determine speed grade from efuse value
 * @versions: Set to the value parsed from efuse
 *
 * Returns 0 अगर success.
 */
अटल पूर्णांक sun50i_cpufreq_get_efuse(u32 *versions)
अणु
	काष्ठा nvmem_cell *speedbin_nvmem;
	काष्ठा device_node *np;
	काष्ठा device *cpu_dev;
	u32 *speedbin, efuse_value;
	माप_प्रकार len;
	पूर्णांक ret;

	cpu_dev = get_cpu_device(0);
	अगर (!cpu_dev)
		वापस -ENODEV;

	np = dev_pm_opp_of_get_opp_desc_node(cpu_dev);
	अगर (!np)
		वापस -ENOENT;

	ret = of_device_is_compatible(np,
				      "allwinner,sun50i-h6-operating-points");
	अगर (!ret) अणु
		of_node_put(np);
		वापस -ENOENT;
	पूर्ण

	speedbin_nvmem = of_nvmem_cell_get(np, शून्य);
	of_node_put(np);
	अगर (IS_ERR(speedbin_nvmem)) अणु
		अगर (PTR_ERR(speedbin_nvmem) != -EPROBE_DEFER)
			pr_err("Could not get nvmem cell: %ld\n",
			       PTR_ERR(speedbin_nvmem));
		वापस PTR_ERR(speedbin_nvmem);
	पूर्ण

	speedbin = nvmem_cell_पढ़ो(speedbin_nvmem, &len);
	nvmem_cell_put(speedbin_nvmem);
	अगर (IS_ERR(speedbin))
		वापस PTR_ERR(speedbin);

	efuse_value = (*speedbin >> NVMEM_SHIFT) & NVMEM_MASK;

	/*
	 * We treat unexpected efuse values as अगर the SoC was from
	 * the slowest bin. Expected efuse values are 1-3, slowest
	 * to fastest.
	 */
	अगर (efuse_value >= 1 && efuse_value <= 3)
		*versions = efuse_value - 1;
	अन्यथा
		*versions = 0;

	kमुक्त(speedbin);
	वापस 0;
पूर्ण;

अटल पूर्णांक sun50i_cpufreq_nvmem_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा opp_table **opp_tables;
	अक्षर name[MAX_NAME_LEN];
	अचिन्हित पूर्णांक cpu;
	u32 speed = 0;
	पूर्णांक ret;

	opp_tables = kसुस्मृति(num_possible_cpus(), माप(*opp_tables),
			     GFP_KERNEL);
	अगर (!opp_tables)
		वापस -ENOMEM;

	ret = sun50i_cpufreq_get_efuse(&speed);
	अगर (ret)
		वापस ret;

	snम_लिखो(name, MAX_NAME_LEN, "speed%d", speed);

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा device *cpu_dev = get_cpu_device(cpu);

		अगर (!cpu_dev) अणु
			ret = -ENODEV;
			जाओ मुक्त_opp;
		पूर्ण

		opp_tables[cpu] = dev_pm_opp_set_prop_name(cpu_dev, name);
		अगर (IS_ERR(opp_tables[cpu])) अणु
			ret = PTR_ERR(opp_tables[cpu]);
			pr_err("Failed to set prop name\n");
			जाओ मुक्त_opp;
		पूर्ण
	पूर्ण

	cpufreq_dt_pdev = platक्रमm_device_रेजिस्टर_simple("cpufreq-dt", -1,
							  शून्य, 0);
	अगर (!IS_ERR(cpufreq_dt_pdev)) अणु
		platक्रमm_set_drvdata(pdev, opp_tables);
		वापस 0;
	पूर्ण

	ret = PTR_ERR(cpufreq_dt_pdev);
	pr_err("Failed to register platform device\n");

मुक्त_opp:
	क्रम_each_possible_cpu(cpu) अणु
		अगर (IS_ERR_OR_शून्य(opp_tables[cpu]))
			अवरोध;
		dev_pm_opp_put_prop_name(opp_tables[cpu]);
	पूर्ण
	kमुक्त(opp_tables);

	वापस ret;
पूर्ण

अटल पूर्णांक sun50i_cpufreq_nvmem_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा opp_table **opp_tables = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक cpu;

	platक्रमm_device_unरेजिस्टर(cpufreq_dt_pdev);

	क्रम_each_possible_cpu(cpu)
		dev_pm_opp_put_prop_name(opp_tables[cpu]);

	kमुक्त(opp_tables);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sun50i_cpufreq_driver = अणु
	.probe = sun50i_cpufreq_nvmem_probe,
	.हटाओ = sun50i_cpufreq_nvmem_हटाओ,
	.driver = अणु
		.name = "sun50i-cpufreq-nvmem",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun50i_cpufreq_match_list[] = अणु
	अणु .compatible = "allwinner,sun50i-h6" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun50i_cpufreq_match_list);

अटल स्थिर काष्ठा of_device_id *sun50i_cpufreq_match_node(व्योम)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np;

	np = of_find_node_by_path("/");
	match = of_match_node(sun50i_cpufreq_match_list, np);
	of_node_put(np);

	वापस match;
पूर्ण

/*
 * Since the driver depends on nvmem drivers, which may वापस EPROBE_DEFER,
 * all the real activity is करोne in the probe, which may be defered as well.
 * The init here is only रेजिस्टरing the driver and the platक्रमm device.
 */
अटल पूर्णांक __init sun50i_cpufreq_init(व्योम)
अणु
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	match = sun50i_cpufreq_match_node();
	अगर (!match)
		वापस -ENODEV;

	ret = platक्रमm_driver_रेजिस्टर(&sun50i_cpufreq_driver);
	अगर (unlikely(ret < 0))
		वापस ret;

	sun50i_cpufreq_pdev =
		platक्रमm_device_रेजिस्टर_simple("sun50i-cpufreq-nvmem",
						-1, शून्य, 0);
	ret = PTR_ERR_OR_ZERO(sun50i_cpufreq_pdev);
	अगर (ret == 0)
		वापस 0;

	platक्रमm_driver_unरेजिस्टर(&sun50i_cpufreq_driver);
	वापस ret;
पूर्ण
module_init(sun50i_cpufreq_init);

अटल व्योम __निकास sun50i_cpufreq_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(sun50i_cpufreq_pdev);
	platक्रमm_driver_unरेजिस्टर(&sun50i_cpufreq_driver);
पूर्ण
module_निकास(sun50i_cpufreq_निकास);

MODULE_DESCRIPTION("Sun50i-h6 cpufreq driver");
MODULE_LICENSE("GPL v2");
