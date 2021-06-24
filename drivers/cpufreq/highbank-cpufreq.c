<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Calxeda, Inc.
 *
 * This driver provides the clk notअगरier callbacks that are used when
 * the cpufreq-dt driver changes to frequency to alert the highbank
 * EnergyCore Management Engine (ECME) about the need to change
 * voltage. The ECME पूर्णांकerfaces with the actual voltage regulators.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/pl320-ipc.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा HB_CPUFREQ_CHANGE_NOTE	0x80000001
#घोषणा HB_CPUFREQ_IPC_LEN	7
#घोषणा HB_CPUFREQ_VOLT_RETRIES	15

अटल पूर्णांक hb_voltage_change(अचिन्हित पूर्णांक freq)
अणु
	u32 msg[HB_CPUFREQ_IPC_LEN] = अणुHB_CPUFREQ_CHANGE_NOTE, freq / 1000000पूर्ण;

	वापस pl320_ipc_transmit(msg);
पूर्ण

अटल पूर्णांक hb_cpufreq_clk_notअगरy(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ action, व्योम *hclk)
अणु
	काष्ठा clk_notअगरier_data *clk_data = hclk;
	पूर्णांक i = 0;

	अगर (action == PRE_RATE_CHANGE) अणु
		अगर (clk_data->new_rate > clk_data->old_rate)
			जबतक (hb_voltage_change(clk_data->new_rate))
				अगर (i++ > HB_CPUFREQ_VOLT_RETRIES)
					वापस NOTIFY_BAD;
	पूर्ण अन्यथा अगर (action == POST_RATE_CHANGE) अणु
		अगर (clk_data->new_rate < clk_data->old_rate)
			जबतक (hb_voltage_change(clk_data->new_rate))
				अगर (i++ > HB_CPUFREQ_VOLT_RETRIES)
					वापस NOTIFY_BAD;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block hb_cpufreq_clk_nb = अणु
	.notअगरier_call = hb_cpufreq_clk_notअगरy,
पूर्ण;

अटल पूर्णांक hb_cpufreq_driver_init(व्योम)
अणु
	काष्ठा platक्रमm_device_info devinfo = अणु .name = "cpufreq-dt", पूर्ण;
	काष्ठा device *cpu_dev;
	काष्ठा clk *cpu_clk;
	काष्ठा device_node *np;
	पूर्णांक ret;

	अगर ((!of_machine_is_compatible("calxeda,highbank")) &&
		(!of_machine_is_compatible("calxeda,ecx-2000")))
		वापस -ENODEV;

	cpu_dev = get_cpu_device(0);
	अगर (!cpu_dev) अणु
		pr_err("failed to get highbank cpufreq device\n");
		वापस -ENODEV;
	पूर्ण

	np = of_node_get(cpu_dev->of_node);
	अगर (!np) अणु
		pr_err("failed to find highbank cpufreq node\n");
		वापस -ENOENT;
	पूर्ण

	cpu_clk = clk_get(cpu_dev, शून्य);
	अगर (IS_ERR(cpu_clk)) अणु
		ret = PTR_ERR(cpu_clk);
		pr_err("failed to get cpu0 clock: %d\n", ret);
		जाओ out_put_node;
	पूर्ण

	ret = clk_notअगरier_रेजिस्टर(cpu_clk, &hb_cpufreq_clk_nb);
	अगर (ret) अणु
		pr_err("failed to register clk notifier: %d\n", ret);
		जाओ out_put_node;
	पूर्ण

	/* Instantiate cpufreq-dt */
	platक्रमm_device_रेजिस्टर_full(&devinfo);

out_put_node:
	of_node_put(np);
	वापस ret;
पूर्ण
module_init(hb_cpufreq_driver_init);

अटल स्थिर काष्ठा of_device_id __maybe_unused hb_cpufreq_of_match[] = अणु
	अणु .compatible = "calxeda,highbank" पूर्ण,
	अणु .compatible = "calxeda,ecx-2000" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hb_cpufreq_of_match);

MODULE_AUTHOR("Mark Langsdorf <mark.langsdorf@calxeda.com>");
MODULE_DESCRIPTION("Calxeda Highbank cpufreq driver");
MODULE_LICENSE("GPL");
