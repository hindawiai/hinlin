<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2015 ARM Limited
 */

#घोषणा pr_fmt(fmt) "psci: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/linkage.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/psci.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>

#समावेश <uapi/linux/psci.h>

#समावेश <यंत्र/cpuidle.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/suspend.h>

/*
 * While a 64-bit OS can make calls with SMC32 calling conventions, क्रम some
 * calls it is necessary to use SMC64 to pass or वापस 64-bit values.
 * For such calls PSCI_FN_NATIVE(version, name) will choose the appropriate
 * (native-width) function ID.
 */
#अगर_घोषित CONFIG_64BIT
#घोषणा PSCI_FN_NATIVE(version, name)	PSCI_##version##_FN64_##name
#अन्यथा
#घोषणा PSCI_FN_NATIVE(version, name)	PSCI_##version##_FN_##name
#पूर्ण_अगर

/*
 * The CPU any Trusted OS is resident on. The trusted OS may reject CPU_OFF
 * calls to its resident CPU, so we must aव्योम issuing those. We never migrate
 * a Trusted OS even अगर it claims to be capable of migration -- करोing so will
 * require cooperation with a Trusted OS driver.
 */
अटल पूर्णांक resident_cpu = -1;
काष्ठा psci_operations psci_ops;
अटल क्रमागत arm_smccc_conduit psci_conduit = SMCCC_CONDUIT_NONE;

bool psci_tos_resident_on(पूर्णांक cpu)
अणु
	वापस cpu == resident_cpu;
पूर्ण

प्रकार अचिन्हित दीर्घ (psci_fn)(अचिन्हित दीर्घ, अचिन्हित दीर्घ,
				अचिन्हित दीर्घ, अचिन्हित दीर्घ);
अटल psci_fn *invoke_psci_fn;

अटल काष्ठा psci_0_1_function_ids psci_0_1_function_ids;

काष्ठा psci_0_1_function_ids get_psci_0_1_function_ids(व्योम)
अणु
	वापस psci_0_1_function_ids;
पूर्ण

#घोषणा PSCI_0_2_POWER_STATE_MASK		\
				(PSCI_0_2_POWER_STATE_ID_MASK | \
				PSCI_0_2_POWER_STATE_TYPE_MASK | \
				PSCI_0_2_POWER_STATE_AFFL_MASK)

#घोषणा PSCI_1_0_EXT_POWER_STATE_MASK		\
				(PSCI_1_0_EXT_POWER_STATE_ID_MASK | \
				PSCI_1_0_EXT_POWER_STATE_TYPE_MASK)

अटल u32 psci_cpu_suspend_feature;
अटल bool psci_प्रणाली_reset2_supported;

अटल अंतरभूत bool psci_has_ext_घातer_state(व्योम)
अणु
	वापस psci_cpu_suspend_feature &
				PSCI_1_0_FEATURES_CPU_SUSPEND_PF_MASK;
पूर्ण

bool psci_has_osi_support(व्योम)
अणु
	वापस psci_cpu_suspend_feature & PSCI_1_0_OS_INITIATED;
पूर्ण

अटल अंतरभूत bool psci_घातer_state_loses_context(u32 state)
अणु
	स्थिर u32 mask = psci_has_ext_घातer_state() ?
					PSCI_1_0_EXT_POWER_STATE_TYPE_MASK :
					PSCI_0_2_POWER_STATE_TYPE_MASK;

	वापस state & mask;
पूर्ण

bool psci_घातer_state_is_valid(u32 state)
अणु
	स्थिर u32 valid_mask = psci_has_ext_घातer_state() ?
			       PSCI_1_0_EXT_POWER_STATE_MASK :
			       PSCI_0_2_POWER_STATE_MASK;

	वापस !(state & ~valid_mask);
पूर्ण

अटल अचिन्हित दीर्घ __invoke_psci_fn_hvc(अचिन्हित दीर्घ function_id,
			अचिन्हित दीर्घ arg0, अचिन्हित दीर्घ arg1,
			अचिन्हित दीर्घ arg2)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_hvc(function_id, arg0, arg1, arg2, 0, 0, 0, 0, &res);
	वापस res.a0;
पूर्ण

अटल अचिन्हित दीर्घ __invoke_psci_fn_smc(अचिन्हित दीर्घ function_id,
			अचिन्हित दीर्घ arg0, अचिन्हित दीर्घ arg1,
			अचिन्हित दीर्घ arg2)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(function_id, arg0, arg1, arg2, 0, 0, 0, 0, &res);
	वापस res.a0;
पूर्ण

अटल पूर्णांक psci_to_linux_त्रुटि_सं(पूर्णांक त्रुटि_सं)
अणु
	चयन (त्रुटि_सं) अणु
	हाल PSCI_RET_SUCCESS:
		वापस 0;
	हाल PSCI_RET_NOT_SUPPORTED:
		वापस -EOPNOTSUPP;
	हाल PSCI_RET_INVALID_PARAMS:
	हाल PSCI_RET_INVALID_ADDRESS:
		वापस -EINVAL;
	हाल PSCI_RET_DENIED:
		वापस -EPERM;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल u32 psci_0_1_get_version(व्योम)
अणु
	वापस PSCI_VERSION(0, 1);
पूर्ण

अटल u32 psci_0_2_get_version(व्योम)
अणु
	वापस invoke_psci_fn(PSCI_0_2_FN_PSCI_VERSION, 0, 0, 0);
पूर्ण

पूर्णांक psci_set_osi_mode(bool enable)
अणु
	अचिन्हित दीर्घ suspend_mode;
	पूर्णांक err;

	suspend_mode = enable ? PSCI_1_0_SUSPEND_MODE_OSI :
			PSCI_1_0_SUSPEND_MODE_PC;

	err = invoke_psci_fn(PSCI_1_0_FN_SET_SUSPEND_MODE, suspend_mode, 0, 0);
	वापस psci_to_linux_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक __psci_cpu_suspend(u32 fn, u32 state, अचिन्हित दीर्घ entry_poपूर्णांक)
अणु
	पूर्णांक err;

	err = invoke_psci_fn(fn, state, entry_poपूर्णांक, 0);
	वापस psci_to_linux_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक psci_0_1_cpu_suspend(u32 state, अचिन्हित दीर्घ entry_poपूर्णांक)
अणु
	वापस __psci_cpu_suspend(psci_0_1_function_ids.cpu_suspend,
				  state, entry_poपूर्णांक);
पूर्ण

अटल पूर्णांक psci_0_2_cpu_suspend(u32 state, अचिन्हित दीर्घ entry_poपूर्णांक)
अणु
	वापस __psci_cpu_suspend(PSCI_FN_NATIVE(0_2, CPU_SUSPEND),
				  state, entry_poपूर्णांक);
पूर्ण

अटल पूर्णांक __psci_cpu_off(u32 fn, u32 state)
अणु
	पूर्णांक err;

	err = invoke_psci_fn(fn, state, 0, 0);
	वापस psci_to_linux_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक psci_0_1_cpu_off(u32 state)
अणु
	वापस __psci_cpu_off(psci_0_1_function_ids.cpu_off, state);
पूर्ण

अटल पूर्णांक psci_0_2_cpu_off(u32 state)
अणु
	वापस __psci_cpu_off(PSCI_0_2_FN_CPU_OFF, state);
पूर्ण

अटल पूर्णांक __psci_cpu_on(u32 fn, अचिन्हित दीर्घ cpuid, अचिन्हित दीर्घ entry_poपूर्णांक)
अणु
	पूर्णांक err;

	err = invoke_psci_fn(fn, cpuid, entry_poपूर्णांक, 0);
	वापस psci_to_linux_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक psci_0_1_cpu_on(अचिन्हित दीर्घ cpuid, अचिन्हित दीर्घ entry_poपूर्णांक)
अणु
	वापस __psci_cpu_on(psci_0_1_function_ids.cpu_on, cpuid, entry_poपूर्णांक);
पूर्ण

अटल पूर्णांक psci_0_2_cpu_on(अचिन्हित दीर्घ cpuid, अचिन्हित दीर्घ entry_poपूर्णांक)
अणु
	वापस __psci_cpu_on(PSCI_FN_NATIVE(0_2, CPU_ON), cpuid, entry_poपूर्णांक);
पूर्ण

अटल पूर्णांक __psci_migrate(u32 fn, अचिन्हित दीर्घ cpuid)
अणु
	पूर्णांक err;

	err = invoke_psci_fn(fn, cpuid, 0, 0);
	वापस psci_to_linux_त्रुटि_सं(err);
पूर्ण

अटल पूर्णांक psci_0_1_migrate(अचिन्हित दीर्घ cpuid)
अणु
	वापस __psci_migrate(psci_0_1_function_ids.migrate, cpuid);
पूर्ण

अटल पूर्णांक psci_0_2_migrate(अचिन्हित दीर्घ cpuid)
अणु
	वापस __psci_migrate(PSCI_FN_NATIVE(0_2, MIGRATE), cpuid);
पूर्ण

अटल पूर्णांक psci_affinity_info(अचिन्हित दीर्घ target_affinity,
		अचिन्हित दीर्घ lowest_affinity_level)
अणु
	वापस invoke_psci_fn(PSCI_FN_NATIVE(0_2, AFFINITY_INFO),
			      target_affinity, lowest_affinity_level, 0);
पूर्ण

अटल पूर्णांक psci_migrate_info_type(व्योम)
अणु
	वापस invoke_psci_fn(PSCI_0_2_FN_MIGRATE_INFO_TYPE, 0, 0, 0);
पूर्ण

अटल अचिन्हित दीर्घ psci_migrate_info_up_cpu(व्योम)
अणु
	वापस invoke_psci_fn(PSCI_FN_NATIVE(0_2, MIGRATE_INFO_UP_CPU),
			      0, 0, 0);
पूर्ण

अटल व्योम set_conduit(क्रमागत arm_smccc_conduit conduit)
अणु
	चयन (conduit) अणु
	हाल SMCCC_CONDUIT_HVC:
		invoke_psci_fn = __invoke_psci_fn_hvc;
		अवरोध;
	हाल SMCCC_CONDUIT_SMC:
		invoke_psci_fn = __invoke_psci_fn_smc;
		अवरोध;
	शेष:
		WARN(1, "Unexpected PSCI conduit %d\n", conduit);
	पूर्ण

	psci_conduit = conduit;
पूर्ण

अटल पूर्णांक get_set_conduit_method(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *method;

	pr_info("probing for conduit method from DT.\n");

	अगर (of_property_पढ़ो_string(np, "method", &method)) अणु
		pr_warn("missing \"method\" property\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!म_भेद("hvc", method)) अणु
		set_conduit(SMCCC_CONDUIT_HVC);
	पूर्ण अन्यथा अगर (!म_भेद("smc", method)) अणु
		set_conduit(SMCCC_CONDUIT_SMC);
	पूर्ण अन्यथा अणु
		pr_warn("invalid \"method\" property: %s\n", method);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम psci_sys_reset(क्रमागत reboot_mode reboot_mode, स्थिर अक्षर *cmd)
अणु
	अगर ((reboot_mode == REBOOT_WARM || reboot_mode == REBOOT_SOFT) &&
	    psci_प्रणाली_reset2_supported) अणु
		/*
		 * reset_type[31] = 0 (architectural)
		 * reset_type[30:0] = 0 (SYSTEM_WARM_RESET)
		 * cookie = 0 (ignored by the implementation)
		 */
		invoke_psci_fn(PSCI_FN_NATIVE(1_1, SYSTEM_RESET2), 0, 0, 0);
	पूर्ण अन्यथा अणु
		invoke_psci_fn(PSCI_0_2_FN_SYSTEM_RESET, 0, 0, 0);
	पूर्ण
पूर्ण

अटल व्योम psci_sys_घातeroff(व्योम)
अणु
	invoke_psci_fn(PSCI_0_2_FN_SYSTEM_OFF, 0, 0, 0);
पूर्ण

अटल पूर्णांक __init psci_features(u32 psci_func_id)
अणु
	वापस invoke_psci_fn(PSCI_1_0_FN_PSCI_FEATURES,
			      psci_func_id, 0, 0);
पूर्ण

#अगर_घोषित CONFIG_CPU_IDLE
अटल पूर्णांक psci_suspend_finisher(अचिन्हित दीर्घ state)
अणु
	u32 घातer_state = state;
	phys_addr_t pa_cpu_resume = __pa_symbol(function_nocfi(cpu_resume));

	वापस psci_ops.cpu_suspend(घातer_state, pa_cpu_resume);
पूर्ण

पूर्णांक psci_cpu_suspend_enter(u32 state)
अणु
	पूर्णांक ret;

	अगर (!psci_घातer_state_loses_context(state))
		ret = psci_ops.cpu_suspend(state, 0);
	अन्यथा
		ret = cpu_suspend(state, psci_suspend_finisher);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक psci_प्रणाली_suspend(अचिन्हित दीर्घ unused)
अणु
	phys_addr_t pa_cpu_resume = __pa_symbol(function_nocfi(cpu_resume));

	वापस invoke_psci_fn(PSCI_FN_NATIVE(1_0, SYSTEM_SUSPEND),
			      pa_cpu_resume, 0, 0);
पूर्ण

अटल पूर्णांक psci_प्रणाली_suspend_enter(suspend_state_t state)
अणु
	वापस cpu_suspend(0, psci_प्रणाली_suspend);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops psci_suspend_ops = अणु
	.valid          = suspend_valid_only_mem,
	.enter          = psci_प्रणाली_suspend_enter,
पूर्ण;

अटल व्योम __init psci_init_प्रणाली_reset2(व्योम)
अणु
	पूर्णांक ret;

	ret = psci_features(PSCI_FN_NATIVE(1_1, SYSTEM_RESET2));

	अगर (ret != PSCI_RET_NOT_SUPPORTED)
		psci_प्रणाली_reset2_supported = true;
पूर्ण

अटल व्योम __init psci_init_प्रणाली_suspend(व्योम)
अणु
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_SUSPEND))
		वापस;

	ret = psci_features(PSCI_FN_NATIVE(1_0, SYSTEM_SUSPEND));

	अगर (ret != PSCI_RET_NOT_SUPPORTED)
		suspend_set_ops(&psci_suspend_ops);
पूर्ण

अटल व्योम __init psci_init_cpu_suspend(व्योम)
अणु
	पूर्णांक feature = psci_features(PSCI_FN_NATIVE(0_2, CPU_SUSPEND));

	अगर (feature != PSCI_RET_NOT_SUPPORTED)
		psci_cpu_suspend_feature = feature;
पूर्ण

/*
 * Detect the presence of a resident Trusted OS which may cause CPU_OFF to
 * वापस DENIED (which would be fatal).
 */
अटल व्योम __init psci_init_migrate(व्योम)
अणु
	अचिन्हित दीर्घ cpuid;
	पूर्णांक type, cpu = -1;

	type = psci_ops.migrate_info_type();

	अगर (type == PSCI_0_2_TOS_MP) अणु
		pr_info("Trusted OS migration not required\n");
		वापस;
	पूर्ण

	अगर (type == PSCI_RET_NOT_SUPPORTED) अणु
		pr_info("MIGRATE_INFO_TYPE not supported.\n");
		वापस;
	पूर्ण

	अगर (type != PSCI_0_2_TOS_UP_MIGRATE &&
	    type != PSCI_0_2_TOS_UP_NO_MIGRATE) अणु
		pr_err("MIGRATE_INFO_TYPE returned unknown type (%d)\n", type);
		वापस;
	पूर्ण

	cpuid = psci_migrate_info_up_cpu();
	अगर (cpuid & ~MPIDR_HWID_BITMASK) अणु
		pr_warn("MIGRATE_INFO_UP_CPU reported invalid physical ID (0x%lx)\n",
			cpuid);
		वापस;
	पूर्ण

	cpu = get_logical_index(cpuid);
	resident_cpu = cpu >= 0 ? cpu : -1;

	pr_info("Trusted OS resident on physical CPU 0x%lx\n", cpuid);
पूर्ण

अटल व्योम __init psci_init_smccc(व्योम)
अणु
	u32 ver = ARM_SMCCC_VERSION_1_0;
	पूर्णांक feature;

	feature = psci_features(ARM_SMCCC_VERSION_FUNC_ID);

	अगर (feature != PSCI_RET_NOT_SUPPORTED) अणु
		u32 ret;
		ret = invoke_psci_fn(ARM_SMCCC_VERSION_FUNC_ID, 0, 0, 0);
		अगर (ret >= ARM_SMCCC_VERSION_1_1) अणु
			arm_smccc_version_init(ret, psci_conduit);
			ver = ret;
		पूर्ण
	पूर्ण

	/*
	 * Conveniently, the SMCCC and PSCI versions are encoded the
	 * same way. No, this isn't accidental.
	 */
	pr_info("SMC Calling Convention v%d.%d\n",
		PSCI_VERSION_MAJOR(ver), PSCI_VERSION_MINOR(ver));

पूर्ण

अटल व्योम __init psci_0_2_set_functions(व्योम)
अणु
	pr_info("Using standard PSCI v0.2 function IDs\n");

	psci_ops = (काष्ठा psci_operations)अणु
		.get_version = psci_0_2_get_version,
		.cpu_suspend = psci_0_2_cpu_suspend,
		.cpu_off = psci_0_2_cpu_off,
		.cpu_on = psci_0_2_cpu_on,
		.migrate = psci_0_2_migrate,
		.affinity_info = psci_affinity_info,
		.migrate_info_type = psci_migrate_info_type,
	पूर्ण;

	arm_pm_restart = psci_sys_reset;

	pm_घातer_off = psci_sys_घातeroff;
पूर्ण

/*
 * Probe function क्रम PSCI firmware versions >= 0.2
 */
अटल पूर्णांक __init psci_probe(व्योम)
अणु
	u32 ver = psci_0_2_get_version();

	pr_info("PSCIv%d.%d detected in firmware.\n",
			PSCI_VERSION_MAJOR(ver),
			PSCI_VERSION_MINOR(ver));

	अगर (PSCI_VERSION_MAJOR(ver) == 0 && PSCI_VERSION_MINOR(ver) < 2) अणु
		pr_err("Conflicting PSCI version detected.\n");
		वापस -EINVAL;
	पूर्ण

	psci_0_2_set_functions();

	psci_init_migrate();

	अगर (PSCI_VERSION_MAJOR(ver) >= 1) अणु
		psci_init_smccc();
		psci_init_cpu_suspend();
		psci_init_प्रणाली_suspend();
		psci_init_प्रणाली_reset2();
		kvm_init_hyp_services();
	पूर्ण

	वापस 0;
पूर्ण

प्रकार पूर्णांक (*psci_initcall_t)(स्थिर काष्ठा device_node *);

/*
 * PSCI init function क्रम PSCI versions >=0.2
 *
 * Probe based on PSCI PSCI_VERSION function
 */
अटल पूर्णांक __init psci_0_2_init(काष्ठा device_node *np)
अणु
	पूर्णांक err;

	err = get_set_conduit_method(np);
	अगर (err)
		वापस err;

	/*
	 * Starting with v0.2, the PSCI specअगरication पूर्णांकroduced a call
	 * (PSCI_VERSION) that allows probing the firmware version, so
	 * that PSCI function IDs and version specअगरic initialization
	 * can be carried out according to the specअगरic version reported
	 * by firmware
	 */
	वापस psci_probe();
पूर्ण

/*
 * PSCI < v0.2 get PSCI Function IDs via DT.
 */
अटल पूर्णांक __init psci_0_1_init(काष्ठा device_node *np)
अणु
	u32 id;
	पूर्णांक err;

	err = get_set_conduit_method(np);
	अगर (err)
		वापस err;

	pr_info("Using PSCI v0.1 Function IDs from DT\n");

	psci_ops.get_version = psci_0_1_get_version;

	अगर (!of_property_पढ़ो_u32(np, "cpu_suspend", &id)) अणु
		psci_0_1_function_ids.cpu_suspend = id;
		psci_ops.cpu_suspend = psci_0_1_cpu_suspend;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "cpu_off", &id)) अणु
		psci_0_1_function_ids.cpu_off = id;
		psci_ops.cpu_off = psci_0_1_cpu_off;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "cpu_on", &id)) अणु
		psci_0_1_function_ids.cpu_on = id;
		psci_ops.cpu_on = psci_0_1_cpu_on;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(np, "migrate", &id)) अणु
		psci_0_1_function_ids.migrate = id;
		psci_ops.migrate = psci_0_1_migrate;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init psci_1_0_init(काष्ठा device_node *np)
अणु
	पूर्णांक err;

	err = psci_0_2_init(np);
	अगर (err)
		वापस err;

	अगर (psci_has_osi_support()) अणु
		pr_info("OSI mode supported.\n");

		/* Default to PC mode. */
		psci_set_osi_mode(false);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id psci_of_match[] __initस्थिर = अणु
	अणु .compatible = "arm,psci",	.data = psci_0_1_initपूर्ण,
	अणु .compatible = "arm,psci-0.2",	.data = psci_0_2_initपूर्ण,
	अणु .compatible = "arm,psci-1.0",	.data = psci_1_0_initपूर्ण,
	अणुपूर्ण,
पूर्ण;

पूर्णांक __init psci_dt_init(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *matched_np;
	psci_initcall_t init_fn;
	पूर्णांक ret;

	np = of_find_matching_node_and_match(शून्य, psci_of_match, &matched_np);

	अगर (!np || !of_device_is_available(np))
		वापस -ENODEV;

	init_fn = (psci_initcall_t)matched_np->data;
	ret = init_fn(np);

	of_node_put(np);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ACPI
/*
 * We use PSCI 0.2+ when ACPI is deployed on ARM64 and it's
 * explicitly clarअगरied in SBBR
 */
पूर्णांक __init psci_acpi_init(व्योम)
अणु
	अगर (!acpi_psci_present()) अणु
		pr_info("is not implemented in ACPI.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	pr_info("probing for conduit method from ACPI.\n");

	अगर (acpi_psci_use_hvc())
		set_conduit(SMCCC_CONDUIT_HVC);
	अन्यथा
		set_conduit(SMCCC_CONDUIT_SMC);

	वापस psci_probe();
पूर्ण
#पूर्ण_अगर
