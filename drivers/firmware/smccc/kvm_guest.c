<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा pr_fmt(fmt) "smccc: KVM: " fmt

#समावेश <linux/arm-smccc.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/hypervisor.h>

अटल DECLARE_BITMAP(__kvm_arm_hyp_services, ARM_SMCCC_KVM_NUM_FUNCS) __ro_after_init = अणु पूर्ण;

व्योम __init kvm_init_hyp_services(व्योम)
अणु
	काष्ठा arm_smccc_res res;
	u32 val[4];

	अगर (arm_smccc_1_1_get_conduit() != SMCCC_CONDUIT_HVC)
		वापस;

	arm_smccc_1_1_invoke(ARM_SMCCC_VENDOR_HYP_CALL_UID_FUNC_ID, &res);
	अगर (res.a0 != ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_0 ||
	    res.a1 != ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_1 ||
	    res.a2 != ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_2 ||
	    res.a3 != ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_3)
		वापस;

	स_रखो(&res, 0, माप(res));
	arm_smccc_1_1_invoke(ARM_SMCCC_VENDOR_HYP_KVM_FEATURES_FUNC_ID, &res);

	val[0] = lower_32_bits(res.a0);
	val[1] = lower_32_bits(res.a1);
	val[2] = lower_32_bits(res.a2);
	val[3] = lower_32_bits(res.a3);

	biपंचांगap_from_arr32(__kvm_arm_hyp_services, val, ARM_SMCCC_KVM_NUM_FUNCS);

	pr_info("hypervisor services detected (0x%08lx 0x%08lx 0x%08lx 0x%08lx)\n",
		 res.a3, res.a2, res.a1, res.a0);
पूर्ण

bool kvm_arm_hyp_service_available(u32 func_id)
अणु
	अगर (func_id >= ARM_SMCCC_KVM_NUM_FUNCS)
		वापस false;

	वापस test_bit(func_id, __kvm_arm_hyp_services);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_arm_hyp_service_available);
