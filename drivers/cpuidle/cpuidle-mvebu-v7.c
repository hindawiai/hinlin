<शैली गुरु>
/*
 * Marvell Armada 370, 38x and XP SoC cpuidle driver
 *
 * Copyright (C) 2014 Marvell
 *
 * Nadav Haklai <nadavh@marvell.com>
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * Maपूर्णांकainer: Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 */

#समावेश <linux/cpu_pm.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/suspend.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/cpuidle.h>

#घोषणा MVEBU_V7_FLAG_DEEP_IDLE	0x10000

अटल पूर्णांक (*mvebu_v7_cpu_suspend)(पूर्णांक);

अटल पूर्णांक mvebu_v7_enter_idle(काष्ठा cpuidle_device *dev,
				काष्ठा cpuidle_driver *drv,
				पूर्णांक index)
अणु
	पूर्णांक ret;
	bool deepidle = false;
	cpu_pm_enter();

	अगर (drv->states[index].flags & MVEBU_V7_FLAG_DEEP_IDLE)
		deepidle = true;

	ret = mvebu_v7_cpu_suspend(deepidle);
	cpu_pm_निकास();

	अगर (ret)
		वापस ret;

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver armadaxp_idle_driver = अणु
	.name			= "armada_xp_idle",
	.states[0]		= ARM_CPUIDLE_WFI_STATE,
	.states[1]		= अणु
		.enter			= mvebu_v7_enter_idle,
		.निकास_latency		= 100,
		.घातer_usage		= 50,
		.target_residency	= 1000,
		.name			= "MV CPU IDLE",
		.desc			= "CPU power down",
	पूर्ण,
	.states[2]		= अणु
		.enter			= mvebu_v7_enter_idle,
		.निकास_latency		= 1000,
		.घातer_usage		= 5,
		.target_residency	= 10000,
		.flags			= MVEBU_V7_FLAG_DEEP_IDLE,
		.name			= "MV CPU DEEP IDLE",
		.desc			= "CPU and L2 Fabric power down",
	पूर्ण,
	.state_count = 3,
पूर्ण;

अटल काष्ठा cpuidle_driver armada370_idle_driver = अणु
	.name			= "armada_370_idle",
	.states[0]		= ARM_CPUIDLE_WFI_STATE,
	.states[1]		= अणु
		.enter			= mvebu_v7_enter_idle,
		.निकास_latency		= 100,
		.घातer_usage		= 5,
		.target_residency	= 1000,
		.flags			= MVEBU_V7_FLAG_DEEP_IDLE,
		.name			= "Deep Idle",
		.desc			= "CPU and L2 Fabric power down",
	पूर्ण,
	.state_count = 2,
पूर्ण;

अटल काष्ठा cpuidle_driver armada38x_idle_driver = अणु
	.name			= "armada_38x_idle",
	.states[0]		= ARM_CPUIDLE_WFI_STATE,
	.states[1]		= अणु
		.enter			= mvebu_v7_enter_idle,
		.निकास_latency		= 10,
		.घातer_usage		= 5,
		.target_residency	= 100,
		.name			= "Idle",
		.desc			= "CPU and SCU power down",
	पूर्ण,
	.state_count = 2,
पूर्ण;

अटल पूर्णांक mvebu_v7_cpuidle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा platक्रमm_device_id *id = pdev->id_entry;

	अगर (!id)
		वापस -EINVAL;

	mvebu_v7_cpu_suspend = pdev->dev.platक्रमm_data;

	वापस cpuidle_रेजिस्टर((काष्ठा cpuidle_driver *)id->driver_data, शून्य);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mvebu_cpuidle_ids[] = अणु
	अणु
		.name = "cpuidle-armada-xp",
		.driver_data = (अचिन्हित दीर्घ)&armadaxp_idle_driver,
	पूर्ण, अणु
		.name = "cpuidle-armada-370",
		.driver_data = (अचिन्हित दीर्घ)&armada370_idle_driver,
	पूर्ण, अणु
		.name = "cpuidle-armada-38x",
		.driver_data = (अचिन्हित दीर्घ)&armada38x_idle_driver,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mvebu_cpuidle_driver = अणु
	.probe = mvebu_v7_cpuidle_probe,
	.driver = अणु
		.name = "cpuidle-mbevu",
		.suppress_bind_attrs = true,
	पूर्ण,
	.id_table = mvebu_cpuidle_ids,
पूर्ण;

builtin_platक्रमm_driver(mvebu_cpuidle_driver);

MODULE_AUTHOR("Gregory CLEMENT <gregory.clement@free-electrons.com>");
MODULE_DESCRIPTION("Marvell EBU v7 cpuidle driver");
MODULE_LICENSE("GPL");
