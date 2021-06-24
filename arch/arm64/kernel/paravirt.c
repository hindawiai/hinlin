<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2013 Citrix Systems
 *
 * Author: Stefano Stabellini <stefano.stabellini@eu.citrix.com>
 */

#घोषणा pr_fmt(fmt) "arm-pv: " fmt

#समावेश <linux/arm-smccc.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/jump_label.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/psci.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/अटल_call.h>

#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/pvघड़ी-abi.h>
#समावेश <यंत्र/smp_plat.h>

काष्ठा अटल_key paravirt_steal_enabled;
काष्ठा अटल_key paravirt_steal_rq_enabled;

अटल u64 native_steal_घड़ी(पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

DEFINE_STATIC_CALL(pv_steal_घड़ी, native_steal_घड़ी);

काष्ठा pv_समय_stolen_समय_region अणु
	काष्ठा pvघड़ी_vcpu_stolen_समय *kaddr;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा pv_समय_stolen_समय_region, stolen_समय_region);

अटल bool steal_acc = true;
अटल पूर्णांक __init parse_no_stealacc(अक्षर *arg)
अणु
	steal_acc = false;
	वापस 0;
पूर्ण

early_param("no-steal-acc", parse_no_stealacc);

/* वापस stolen समय in ns by asking the hypervisor */
अटल u64 para_steal_घड़ी(पूर्णांक cpu)
अणु
	काष्ठा pv_समय_stolen_समय_region *reg;

	reg = per_cpu_ptr(&stolen_समय_region, cpu);

	/*
	 * paravirt_steal_घड़ी() may be called beक्रमe the CPU
	 * online notअगरication callback runs. Until the callback
	 * has run we just वापस zero.
	 */
	अगर (!reg->kaddr)
		वापस 0;

	वापस le64_to_cpu(READ_ONCE(reg->kaddr->stolen_समय));
पूर्ण

अटल पूर्णांक stolen_समय_cpu_करोwn_prepare(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा pv_समय_stolen_समय_region *reg;

	reg = this_cpu_ptr(&stolen_समय_region);
	अगर (!reg->kaddr)
		वापस 0;

	memunmap(reg->kaddr);
	स_रखो(reg, 0, माप(*reg));

	वापस 0;
पूर्ण

अटल पूर्णांक stolen_समय_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा pv_समय_stolen_समय_region *reg;
	काष्ठा arm_smccc_res res;

	reg = this_cpu_ptr(&stolen_समय_region);

	arm_smccc_1_1_invoke(ARM_SMCCC_HV_PV_TIME_ST, &res);

	अगर (res.a0 == SMCCC_RET_NOT_SUPPORTED)
		वापस -EINVAL;

	reg->kaddr = memremap(res.a0,
			      माप(काष्ठा pvघड़ी_vcpu_stolen_समय),
			      MEMREMAP_WB);

	अगर (!reg->kaddr) अणु
		pr_warn("Failed to map stolen time data structure\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (le32_to_cpu(reg->kaddr->revision) != 0 ||
	    le32_to_cpu(reg->kaddr->attributes) != 0) अणु
		pr_warn_once("Unexpected revision or attributes in stolen time data\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init pv_समय_init_stolen_समय(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN,
				"hypervisor/arm/pvtime:online",
				stolen_समय_cpu_online,
				stolen_समय_cpu_करोwn_prepare);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल bool __init has_pv_steal_घड़ी(व्योम)
अणु
	काष्ठा arm_smccc_res res;

	/* To detect the presence of PV समय support we require SMCCC 1.1+ */
	अगर (arm_smccc_1_1_get_conduit() == SMCCC_CONDUIT_NONE)
		वापस false;

	arm_smccc_1_1_invoke(ARM_SMCCC_ARCH_FEATURES_FUNC_ID,
			     ARM_SMCCC_HV_PV_TIME_FEATURES, &res);

	अगर (res.a0 != SMCCC_RET_SUCCESS)
		वापस false;

	arm_smccc_1_1_invoke(ARM_SMCCC_HV_PV_TIME_FEATURES,
			     ARM_SMCCC_HV_PV_TIME_ST, &res);

	वापस (res.a0 == SMCCC_RET_SUCCESS);
पूर्ण

पूर्णांक __init pv_समय_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!has_pv_steal_घड़ी())
		वापस 0;

	ret = pv_समय_init_stolen_समय();
	अगर (ret)
		वापस ret;

	अटल_call_update(pv_steal_घड़ी, para_steal_घड़ी);

	अटल_key_slow_inc(&paravirt_steal_enabled);
	अगर (steal_acc)
		अटल_key_slow_inc(&paravirt_steal_rq_enabled);

	pr_info("using stolen time PV\n");

	वापस 0;
पूर्ण
