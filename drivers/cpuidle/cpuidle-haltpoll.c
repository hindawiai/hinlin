<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cpuidle driver क्रम haltpoll governor.
 *
 * Copyright 2019 Red Hat, Inc. and/or its affiliates.
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * Authors: Marcelo Tosatti <mtosatti@redhat.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/idle.h>
#समावेश <linux/kvm_para.h>
#समावेश <linux/cpuidle_haltpoll.h>

अटल bool क्रमce __पढ़ो_mostly;
module_param(क्रमce, bool, 0444);
MODULE_PARM_DESC(क्रमce, "Load unconditionally");

अटल काष्ठा cpuidle_device __percpu *haltpoll_cpuidle_devices;
अटल क्रमागत cpuhp_state haltpoll_hp_state;

अटल पूर्णांक शेष_enter_idle(काष्ठा cpuidle_device *dev,
			      काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	अगर (current_clr_polling_and_test()) अणु
		local_irq_enable();
		वापस index;
	पूर्ण
	शेष_idle();
	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver haltpoll_driver = अणु
	.name = "haltpoll",
	.governor = "haltpoll",
	.states = अणु
		अणु /* entry 0 is क्रम polling */ पूर्ण,
		अणु
			.enter			= शेष_enter_idle,
			.निकास_latency		= 1,
			.target_residency	= 1,
			.घातer_usage		= -1,
			.name			= "haltpoll idle",
			.desc			= "default architecture idle",
		पूर्ण,
	पूर्ण,
	.safe_state_index = 0,
	.state_count = 2,
पूर्ण;

अटल पूर्णांक haltpoll_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuidle_device *dev;

	dev = per_cpu_ptr(haltpoll_cpuidle_devices, cpu);
	अगर (!dev->रेजिस्टरed) अणु
		dev->cpu = cpu;
		अगर (cpuidle_रेजिस्टर_device(dev)) अणु
			pr_notice("cpuidle_register_device %d failed!\n", cpu);
			वापस -EIO;
		पूर्ण
		arch_haltpoll_enable(cpu);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक haltpoll_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuidle_device *dev;

	dev = per_cpu_ptr(haltpoll_cpuidle_devices, cpu);
	अगर (dev->रेजिस्टरed) अणु
		arch_haltpoll_disable(cpu);
		cpuidle_unरेजिस्टर_device(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम haltpoll_uninit(व्योम)
अणु
	अगर (haltpoll_hp_state)
		cpuhp_हटाओ_state(haltpoll_hp_state);
	cpuidle_unरेजिस्टर_driver(&haltpoll_driver);

	मुक्त_percpu(haltpoll_cpuidle_devices);
	haltpoll_cpuidle_devices = शून्य;
पूर्ण

अटल bool haltpoll_want(व्योम)
अणु
	वापस kvm_para_has_hपूर्णांक(KVM_HINTS_REALTIME) || क्रमce;
पूर्ण

अटल पूर्णांक __init haltpoll_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा cpuidle_driver *drv = &haltpoll_driver;

	/* Do not load haltpoll अगर idle= is passed */
	अगर (boot_option_idle_override != IDLE_NO_OVERRIDE)
		वापस -ENODEV;

	cpuidle_poll_state_init(drv);

	अगर (!kvm_para_available() || !haltpoll_want())
		वापस -ENODEV;

	ret = cpuidle_रेजिस्टर_driver(drv);
	अगर (ret < 0)
		वापस ret;

	haltpoll_cpuidle_devices = alloc_percpu(काष्ठा cpuidle_device);
	अगर (haltpoll_cpuidle_devices == शून्य) अणु
		cpuidle_unरेजिस्टर_driver(drv);
		वापस -ENOMEM;
	पूर्ण

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "cpuidle/haltpoll:online",
				haltpoll_cpu_online, haltpoll_cpu_offline);
	अगर (ret < 0) अणु
		haltpoll_uninit();
	पूर्ण अन्यथा अणु
		haltpoll_hp_state = ret;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास haltpoll_निकास(व्योम)
अणु
	haltpoll_uninit();
पूर्ण

module_init(haltpoll_init);
module_निकास(haltpoll_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marcelo Tosatti <mtosatti@redhat.com>");
