<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Raspberry Pi cpufreq driver
 *
 * Copyright (C) 2019, Nicolas Saenz Julienne <nsaenzjulienne@suse.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>

#घोषणा RASPBERRYPI_FREQ_INTERVAL	100000000

अटल काष्ठा platक्रमm_device *cpufreq_dt;

अटल पूर्णांक raspberrypi_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *cpu_dev;
	अचिन्हित दीर्घ min, max;
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clk;
	पूर्णांक ret;

	cpu_dev = get_cpu_device(0);
	अगर (!cpu_dev) अणु
		pr_err("Cannot get CPU for cpufreq driver\n");
		वापस -ENODEV;
	पूर्ण

	clk = clk_get(cpu_dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(cpu_dev, "Cannot get clock for CPU0\n");
		वापस PTR_ERR(clk);
	पूर्ण

	/*
	 * The max and min frequencies are configurable in the Raspberry Pi
	 * firmware, so we query them at runसमय.
	 */
	min = roundup(clk_round_rate(clk, 0), RASPBERRYPI_FREQ_INTERVAL);
	max = roundup(clk_round_rate(clk, अच_दीर्घ_उच्च), RASPBERRYPI_FREQ_INTERVAL);
	clk_put(clk);

	क्रम (rate = min; rate <= max; rate += RASPBERRYPI_FREQ_INTERVAL) अणु
		ret = dev_pm_opp_add(cpu_dev, rate, 0);
		अगर (ret)
			जाओ हटाओ_opp;
	पूर्ण

	cpufreq_dt = platक्रमm_device_रेजिस्टर_simple("cpufreq-dt", -1, शून्य, 0);
	ret = PTR_ERR_OR_ZERO(cpufreq_dt);
	अगर (ret) अणु
		dev_err(cpu_dev, "Failed to create platform device, %d\n", ret);
		जाओ हटाओ_opp;
	पूर्ण

	वापस 0;

हटाओ_opp:
	dev_pm_opp_हटाओ_all_dynamic(cpu_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक raspberrypi_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *cpu_dev;

	cpu_dev = get_cpu_device(0);
	अगर (cpu_dev)
		dev_pm_opp_हटाओ_all_dynamic(cpu_dev);

	platक्रमm_device_unरेजिस्टर(cpufreq_dt);

	वापस 0;
पूर्ण

/*
 * Since the driver depends on clk-raspberrypi, which may वापस EPROBE_DEFER,
 * all the activity is perक्रमmed in the probe, which may be defered as well.
 */
अटल काष्ठा platक्रमm_driver raspberrypi_cpufreq_driver = अणु
	.driver = अणु
		.name = "raspberrypi-cpufreq",
	पूर्ण,
	.probe          = raspberrypi_cpufreq_probe,
	.हटाओ		= raspberrypi_cpufreq_हटाओ,
पूर्ण;
module_platक्रमm_driver(raspberrypi_cpufreq_driver);

MODULE_AUTHOR("Nicolas Saenz Julienne <nsaenzjulienne@suse.de");
MODULE_DESCRIPTION("Raspberry Pi cpufreq driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:raspberrypi-cpufreq");
