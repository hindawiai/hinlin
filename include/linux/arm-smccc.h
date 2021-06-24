<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015, Linaro Limited
 */
#अगर_अघोषित __LINUX_ARM_SMCCC_H
#घोषणा __LINUX_ARM_SMCCC_H

#समावेश <linux/init.h>
#समावेश <uapi/linux/स्थिर.h>

/*
 * This file provides common defines क्रम ARM SMC Calling Convention as
 * specअगरied in
 * https://developer.arm.com/करोcs/den0028/latest
 *
 * This code is up-to-date with version DEN 0028 C
 */

#घोषणा ARM_SMCCC_STD_CALL	        _AC(0,U)
#घोषणा ARM_SMCCC_FAST_CALL	        _AC(1,U)
#घोषणा ARM_SMCCC_TYPE_SHIFT		31

#घोषणा ARM_SMCCC_SMC_32		0
#घोषणा ARM_SMCCC_SMC_64		1
#घोषणा ARM_SMCCC_CALL_CONV_SHIFT	30

#घोषणा ARM_SMCCC_OWNER_MASK		0x3F
#घोषणा ARM_SMCCC_OWNER_SHIFT		24

#घोषणा ARM_SMCCC_FUNC_MASK		0xFFFF

#घोषणा ARM_SMCCC_IS_FAST_CALL(smc_val)	\
	((smc_val) & (ARM_SMCCC_FAST_CALL << ARM_SMCCC_TYPE_SHIFT))
#घोषणा ARM_SMCCC_IS_64(smc_val) \
	((smc_val) & (ARM_SMCCC_SMC_64 << ARM_SMCCC_CALL_CONV_SHIFT))
#घोषणा ARM_SMCCC_FUNC_NUM(smc_val)	((smc_val) & ARM_SMCCC_FUNC_MASK)
#घोषणा ARM_SMCCC_OWNER_NUM(smc_val) \
	(((smc_val) >> ARM_SMCCC_OWNER_SHIFT) & ARM_SMCCC_OWNER_MASK)

#घोषणा ARM_SMCCC_CALL_VAL(type, calling_convention, owner, func_num) \
	(((type) << ARM_SMCCC_TYPE_SHIFT) | \
	((calling_convention) << ARM_SMCCC_CALL_CONV_SHIFT) | \
	(((owner) & ARM_SMCCC_OWNER_MASK) << ARM_SMCCC_OWNER_SHIFT) | \
	((func_num) & ARM_SMCCC_FUNC_MASK))

#घोषणा ARM_SMCCC_OWNER_ARCH		0
#घोषणा ARM_SMCCC_OWNER_CPU		1
#घोषणा ARM_SMCCC_OWNER_SIP		2
#घोषणा ARM_SMCCC_OWNER_OEM		3
#घोषणा ARM_SMCCC_OWNER_STANDARD	4
#घोषणा ARM_SMCCC_OWNER_STANDARD_HYP	5
#घोषणा ARM_SMCCC_OWNER_VENDOR_HYP	6
#घोषणा ARM_SMCCC_OWNER_TRUSTED_APP	48
#घोषणा ARM_SMCCC_OWNER_TRUSTED_APP_END	49
#घोषणा ARM_SMCCC_OWNER_TRUSTED_OS	50
#घोषणा ARM_SMCCC_OWNER_TRUSTED_OS_END	63

#घोषणा ARM_SMCCC_FUNC_QUERY_CALL_UID  0xff01

#घोषणा ARM_SMCCC_QUIRK_NONE		0
#घोषणा ARM_SMCCC_QUIRK_QCOM_A6		1 /* Save/restore रेजिस्टर a6 */

#घोषणा ARM_SMCCC_VERSION_1_0		0x10000
#घोषणा ARM_SMCCC_VERSION_1_1		0x10001
#घोषणा ARM_SMCCC_VERSION_1_2		0x10002

#घोषणा ARM_SMCCC_VERSION_FUNC_ID					\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,				\
			   ARM_SMCCC_SMC_32,				\
			   0, 0)

#घोषणा ARM_SMCCC_ARCH_FEATURES_FUNC_ID					\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,				\
			   ARM_SMCCC_SMC_32,				\
			   0, 1)

#घोषणा ARM_SMCCC_ARCH_SOC_ID						\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,				\
			   ARM_SMCCC_SMC_32,				\
			   0, 2)

#घोषणा ARM_SMCCC_ARCH_WORKAROUND_1					\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,				\
			   ARM_SMCCC_SMC_32,				\
			   0, 0x8000)

#घोषणा ARM_SMCCC_ARCH_WORKAROUND_2					\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,				\
			   ARM_SMCCC_SMC_32,				\
			   0, 0x7fff)

#घोषणा ARM_SMCCC_VENDOR_HYP_CALL_UID_FUNC_ID				\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,				\
			   ARM_SMCCC_SMC_32,				\
			   ARM_SMCCC_OWNER_VENDOR_HYP,			\
			   ARM_SMCCC_FUNC_QUERY_CALL_UID)

/* KVM UID value: 28b46fb6-2ec5-11e9-a9ca-4b564d003a74 */
#घोषणा ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_0	0xb66fb428U
#घोषणा ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_1	0xe911c52eU
#घोषणा ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_2	0x564bcaa9U
#घोषणा ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_3	0x743a004dU

/* KVM "vendor specific" services */
#घोषणा ARM_SMCCC_KVM_FUNC_FEATURES		0
#घोषणा ARM_SMCCC_KVM_FUNC_PTP			1
#घोषणा ARM_SMCCC_KVM_FUNC_FEATURES_2		127
#घोषणा ARM_SMCCC_KVM_NUM_FUNCS			128

#घोषणा ARM_SMCCC_VENDOR_HYP_KVM_FEATURES_FUNC_ID			\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,				\
			   ARM_SMCCC_SMC_32,				\
			   ARM_SMCCC_OWNER_VENDOR_HYP,			\
			   ARM_SMCCC_KVM_FUNC_FEATURES)

#घोषणा SMCCC_ARCH_WORKAROUND_RET_UNAFFECTED	1

/*
 * ptp_kvm is a feature used क्रम समय sync between vm and host.
 * ptp_kvm module in guest kernel will get service from host using
 * this hypercall ID.
 */
#घोषणा ARM_SMCCC_VENDOR_HYP_KVM_PTP_FUNC_ID				\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,				\
			   ARM_SMCCC_SMC_32,				\
			   ARM_SMCCC_OWNER_VENDOR_HYP,			\
			   ARM_SMCCC_KVM_FUNC_PTP)

/* ptp_kvm counter type ID */
#घोषणा KVM_PTP_VIRT_COUNTER			0
#घोषणा KVM_PTP_PHYS_COUNTER			1

/* Paraभवised समय calls (defined by ARM DEN0057A) */
#घोषणा ARM_SMCCC_HV_PV_TIME_FEATURES				\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,			\
			   ARM_SMCCC_SMC_64,			\
			   ARM_SMCCC_OWNER_STANDARD_HYP,	\
			   0x20)

#घोषणा ARM_SMCCC_HV_PV_TIME_ST					\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,			\
			   ARM_SMCCC_SMC_64,			\
			   ARM_SMCCC_OWNER_STANDARD_HYP,	\
			   0x21)

/* TRNG entropy source calls (defined by ARM DEN0098) */
#घोषणा ARM_SMCCC_TRNG_VERSION					\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,			\
			   ARM_SMCCC_SMC_32,			\
			   ARM_SMCCC_OWNER_STANDARD,		\
			   0x50)

#घोषणा ARM_SMCCC_TRNG_FEATURES					\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,			\
			   ARM_SMCCC_SMC_32,			\
			   ARM_SMCCC_OWNER_STANDARD,		\
			   0x51)

#घोषणा ARM_SMCCC_TRNG_GET_UUID					\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,			\
			   ARM_SMCCC_SMC_32,			\
			   ARM_SMCCC_OWNER_STANDARD,		\
			   0x52)

#घोषणा ARM_SMCCC_TRNG_RND32					\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,			\
			   ARM_SMCCC_SMC_32,			\
			   ARM_SMCCC_OWNER_STANDARD,		\
			   0x53)

#घोषणा ARM_SMCCC_TRNG_RND64					\
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL,			\
			   ARM_SMCCC_SMC_64,			\
			   ARM_SMCCC_OWNER_STANDARD,		\
			   0x53)

/*
 * Return codes defined in ARM DEN 0070A
 * ARM DEN 0070A is now merged/consolidated पूर्णांकo ARM DEN 0028 C
 */
#घोषणा SMCCC_RET_SUCCESS			0
#घोषणा SMCCC_RET_NOT_SUPPORTED			-1
#घोषणा SMCCC_RET_NOT_REQUIRED			-2
#घोषणा SMCCC_RET_INVALID_PARAMETER		-3

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/linkage.h>
#समावेश <linux/types.h>

क्रमागत arm_smccc_conduit अणु
	SMCCC_CONDUIT_NONE,
	SMCCC_CONDUIT_SMC,
	SMCCC_CONDUIT_HVC,
पूर्ण;

/**
 * arm_smccc_1_1_get_conduit()
 *
 * Returns the conduit to be used क्रम SMCCCv1.1 or later.
 *
 * When SMCCCv1.1 is not present, वापसs SMCCC_CONDUIT_NONE.
 */
क्रमागत arm_smccc_conduit arm_smccc_1_1_get_conduit(व्योम);

/**
 * arm_smccc_get_version()
 *
 * Returns the version to be used क्रम SMCCCv1.1 or later.
 *
 * When SMCCCv1.1 or above is not present, वापसs SMCCCv1.0, but this
 * करोes not imply the presence of firmware or a valid conduit. Caller
 * handling SMCCCv1.0 must determine the conduit by other means.
 */
u32 arm_smccc_get_version(व्योम);

व्योम __init arm_smccc_version_init(u32 version, क्रमागत arm_smccc_conduit conduit);

/**
 * काष्ठा arm_smccc_res - Result from SMC/HVC call
 * @a0-a3 result values from रेजिस्टरs 0 to 3
 */
काष्ठा arm_smccc_res अणु
	अचिन्हित दीर्घ a0;
	अचिन्हित दीर्घ a1;
	अचिन्हित दीर्घ a2;
	अचिन्हित दीर्घ a3;
पूर्ण;

/**
 * काष्ठा arm_smccc_quirk - Contains quirk inक्रमmation
 * @id: quirk identअगरication
 * @state: quirk specअगरic inक्रमmation
 * @a6: Qualcomm quirk entry क्रम वापसing post-smc call contents of a6
 */
काष्ठा arm_smccc_quirk अणु
	पूर्णांक	id;
	जोड़ अणु
		अचिन्हित दीर्घ a6;
	पूर्ण state;
पूर्ण;

/**
 * __arm_smccc_smc() - make SMC calls
 * @a0-a7: arguments passed in रेजिस्टरs 0 to 7
 * @res: result values from रेजिस्टरs 0 to 3
 * @quirk: poपूर्णांकs to an arm_smccc_quirk, or शून्य when no quirks are required.
 *
 * This function is used to make SMC calls following SMC Calling Convention.
 * The content of the supplied param are copied to रेजिस्टरs 0 to 7 prior
 * to the SMC inकाष्ठाion. The वापस values are updated with the content
 * from रेजिस्टर 0 to 3 on वापस from the SMC inकाष्ठाion.  An optional
 * quirk काष्ठाure provides venकरोr specअगरic behavior.
 */
यंत्रlinkage व्योम __arm_smccc_smc(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1,
			अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3, अचिन्हित दीर्घ a4,
			अचिन्हित दीर्घ a5, अचिन्हित दीर्घ a6, अचिन्हित दीर्घ a7,
			काष्ठा arm_smccc_res *res, काष्ठा arm_smccc_quirk *quirk);

/**
 * __arm_smccc_hvc() - make HVC calls
 * @a0-a7: arguments passed in रेजिस्टरs 0 to 7
 * @res: result values from रेजिस्टरs 0 to 3
 * @quirk: poपूर्णांकs to an arm_smccc_quirk, or शून्य when no quirks are required.
 *
 * This function is used to make HVC calls following SMC Calling
 * Convention.  The content of the supplied param are copied to रेजिस्टरs 0
 * to 7 prior to the HVC inकाष्ठाion. The वापस values are updated with
 * the content from रेजिस्टर 0 to 3 on वापस from the HVC inकाष्ठाion.  An
 * optional quirk काष्ठाure provides venकरोr specअगरic behavior.
 */
यंत्रlinkage व्योम __arm_smccc_hvc(अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1,
			अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3, अचिन्हित दीर्घ a4,
			अचिन्हित दीर्घ a5, अचिन्हित दीर्घ a6, अचिन्हित दीर्घ a7,
			काष्ठा arm_smccc_res *res, काष्ठा arm_smccc_quirk *quirk);

#घोषणा arm_smccc_smc(...) __arm_smccc_smc(__VA_ARGS__, शून्य)

#घोषणा arm_smccc_smc_quirk(...) __arm_smccc_smc(__VA_ARGS__)

#घोषणा arm_smccc_hvc(...) __arm_smccc_hvc(__VA_ARGS__, शून्य)

#घोषणा arm_smccc_hvc_quirk(...) __arm_smccc_hvc(__VA_ARGS__)

/* SMCCC v1.1 implementation madness follows */
#अगर_घोषित CONFIG_ARM64

#घोषणा SMCCC_SMC_INST	"smc	#0"
#घोषणा SMCCC_HVC_INST	"hvc	#0"

#या_अगर defined(CONFIG_ARM)
#समावेश <यंत्र/opcodes-sec.h>
#समावेश <यंत्र/opcodes-virt.h>

#घोषणा SMCCC_SMC_INST	__SMC(0)
#घोषणा SMCCC_HVC_INST	__HVC(0)

#पूर्ण_अगर

#घोषणा ___count_args(_0, _1, _2, _3, _4, _5, _6, _7, _8, x, ...) x

#घोषणा __count_args(...)						\
	___count_args(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1, 0)

#घोषणा __स्थिरraपूर्णांक_पढ़ो_0	"r" (arg0)
#घोषणा __स्थिरraपूर्णांक_पढ़ो_1	__स्थिरraपूर्णांक_पढ़ो_0, "r" (arg1)
#घोषणा __स्थिरraपूर्णांक_पढ़ो_2	__स्थिरraपूर्णांक_पढ़ो_1, "r" (arg2)
#घोषणा __स्थिरraपूर्णांक_पढ़ो_3	__स्थिरraपूर्णांक_पढ़ो_2, "r" (arg3)
#घोषणा __स्थिरraपूर्णांक_पढ़ो_4	__स्थिरraपूर्णांक_पढ़ो_3, "r" (arg4)
#घोषणा __स्थिरraपूर्णांक_पढ़ो_5	__स्थिरraपूर्णांक_पढ़ो_4, "r" (arg5)
#घोषणा __स्थिरraपूर्णांक_पढ़ो_6	__स्थिरraपूर्णांक_पढ़ो_5, "r" (arg6)
#घोषणा __स्थिरraपूर्णांक_पढ़ो_7	__स्थिरraपूर्णांक_पढ़ो_6, "r" (arg7)

#घोषणा __declare_arg_0(a0, res)					\
	काष्ठा arm_smccc_res   *___res = res;				\
	रेजिस्टर अचिन्हित दीर्घ arg0 यंत्र("r0") = (u32)a0

#घोषणा __declare_arg_1(a0, a1, res)					\
	typeof(a1) __a1 = a1;						\
	काष्ठा arm_smccc_res   *___res = res;				\
	रेजिस्टर अचिन्हित दीर्घ arg0 यंत्र("r0") = (u32)a0;			\
	रेजिस्टर typeof(a1) arg1 यंत्र("r1") = __a1

#घोषणा __declare_arg_2(a0, a1, a2, res)				\
	typeof(a1) __a1 = a1;						\
	typeof(a2) __a2 = a2;						\
	काष्ठा arm_smccc_res   *___res = res;				\
	रेजिस्टर अचिन्हित दीर्घ arg0 यंत्र("r0") = (u32)a0;			\
	रेजिस्टर typeof(a1) arg1 यंत्र("r1") = __a1;			\
	रेजिस्टर typeof(a2) arg2 यंत्र("r2") = __a2

#घोषणा __declare_arg_3(a0, a1, a2, a3, res)				\
	typeof(a1) __a1 = a1;						\
	typeof(a2) __a2 = a2;						\
	typeof(a3) __a3 = a3;						\
	काष्ठा arm_smccc_res   *___res = res;				\
	रेजिस्टर अचिन्हित दीर्घ arg0 यंत्र("r0") = (u32)a0;			\
	रेजिस्टर typeof(a1) arg1 यंत्र("r1") = __a1;			\
	रेजिस्टर typeof(a2) arg2 यंत्र("r2") = __a2;			\
	रेजिस्टर typeof(a3) arg3 यंत्र("r3") = __a3

#घोषणा __declare_arg_4(a0, a1, a2, a3, a4, res)			\
	typeof(a4) __a4 = a4;						\
	__declare_arg_3(a0, a1, a2, a3, res);				\
	रेजिस्टर typeof(a4) arg4 यंत्र("r4") = __a4

#घोषणा __declare_arg_5(a0, a1, a2, a3, a4, a5, res)			\
	typeof(a5) __a5 = a5;						\
	__declare_arg_4(a0, a1, a2, a3, a4, res);			\
	रेजिस्टर typeof(a5) arg5 यंत्र("r5") = __a5

#घोषणा __declare_arg_6(a0, a1, a2, a3, a4, a5, a6, res)		\
	typeof(a6) __a6 = a6;						\
	__declare_arg_5(a0, a1, a2, a3, a4, a5, res);			\
	रेजिस्टर typeof(a6) arg6 यंत्र("r6") = __a6

#घोषणा __declare_arg_7(a0, a1, a2, a3, a4, a5, a6, a7, res)		\
	typeof(a7) __a7 = a7;						\
	__declare_arg_6(a0, a1, a2, a3, a4, a5, a6, res);		\
	रेजिस्टर typeof(a7) arg7 यंत्र("r7") = __a7

#घोषणा ___declare_args(count, ...) __declare_arg_ ## count(__VA_ARGS__)
#घोषणा __declare_args(count, ...)  ___declare_args(count, __VA_ARGS__)

#घोषणा ___स्थिरraपूर्णांकs(count)						\
	: __स्थिरraपूर्णांक_पढ़ो_ ## count					\
	: "memory"
#घोषणा __स्थिरraपूर्णांकs(count)	___स्थिरraपूर्णांकs(count)

/*
 * We have an output list that is not necessarily used, and GCC feels
 * entitled to optimise the whole sequence away. "volatile" is what
 * makes it stick.
 */
#घोषणा __arm_smccc_1_1(inst, ...)					\
	करो अणु								\
		रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("r0");			\
		रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("r1");			\
		रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("r2");			\
		रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("r3"); 			\
		__declare_args(__count_args(__VA_ARGS__), __VA_ARGS__);	\
		यंत्र अस्थिर(inst "\n" :				\
			     "=r" (r0), "=r" (r1), "=r" (r2), "=r" (r3)	\
			     __स्थिरraपूर्णांकs(__count_args(__VA_ARGS__)));	\
		अगर (___res)						\
			*___res = (typeof(*___res))अणुr0, r1, r2, r3पूर्ण;	\
	पूर्ण जबतक (0)

/*
 * arm_smccc_1_1_smc() - make an SMCCC v1.1 compliant SMC call
 *
 * This is a variadic macro taking one to eight source arguments, and
 * an optional वापस काष्ठाure.
 *
 * @a0-a7: arguments passed in रेजिस्टरs 0 to 7
 * @res: result values from रेजिस्टरs 0 to 3
 *
 * This macro is used to make SMC calls following SMC Calling Convention v1.1.
 * The content of the supplied param are copied to रेजिस्टरs 0 to 7 prior
 * to the SMC inकाष्ठाion. The वापस values are updated with the content
 * from रेजिस्टर 0 to 3 on वापस from the SMC inकाष्ठाion अगर not शून्य.
 */
#घोषणा arm_smccc_1_1_smc(...)	__arm_smccc_1_1(SMCCC_SMC_INST, __VA_ARGS__)

/*
 * arm_smccc_1_1_hvc() - make an SMCCC v1.1 compliant HVC call
 *
 * This is a variadic macro taking one to eight source arguments, and
 * an optional वापस काष्ठाure.
 *
 * @a0-a7: arguments passed in रेजिस्टरs 0 to 7
 * @res: result values from रेजिस्टरs 0 to 3
 *
 * This macro is used to make HVC calls following SMC Calling Convention v1.1.
 * The content of the supplied param are copied to रेजिस्टरs 0 to 7 prior
 * to the HVC inकाष्ठाion. The वापस values are updated with the content
 * from रेजिस्टर 0 to 3 on वापस from the HVC inकाष्ठाion अगर not शून्य.
 */
#घोषणा arm_smccc_1_1_hvc(...)	__arm_smccc_1_1(SMCCC_HVC_INST, __VA_ARGS__)

/*
 * Like arm_smccc_1_1* but always वापसs SMCCC_RET_NOT_SUPPORTED.
 * Used when the SMCCC conduit is not defined. The empty यंत्र statement
 * aव्योमs compiler warnings about unused variables.
 */
#घोषणा __fail_smccc_1_1(...)						\
	करो अणु								\
		__declare_args(__count_args(__VA_ARGS__), __VA_ARGS__);	\
		यंत्र ("" : __स्थिरraपूर्णांकs(__count_args(__VA_ARGS__)));	\
		अगर (___res)						\
			___res->a0 = SMCCC_RET_NOT_SUPPORTED;		\
	पूर्ण जबतक (0)

/*
 * arm_smccc_1_1_invoke() - make an SMCCC v1.1 compliant call
 *
 * This is a variadic macro taking one to eight source arguments, and
 * an optional वापस काष्ठाure.
 *
 * @a0-a7: arguments passed in रेजिस्टरs 0 to 7
 * @res: result values from रेजिस्टरs 0 to 3
 *
 * This macro will make either an HVC call or an SMC call depending on the
 * current SMCCC conduit. If no valid conduit is available then -1
 * (SMCCC_RET_NOT_SUPPORTED) is वापसed in @res.a0 (अगर supplied).
 *
 * The वापस value also provides the conduit that was used.
 */
#घोषणा arm_smccc_1_1_invoke(...) (अणु					\
		पूर्णांक method = arm_smccc_1_1_get_conduit();		\
		चयन (method) अणु					\
		हाल SMCCC_CONDUIT_HVC:					\
			arm_smccc_1_1_hvc(__VA_ARGS__);			\
			अवरोध;						\
		हाल SMCCC_CONDUIT_SMC:					\
			arm_smccc_1_1_smc(__VA_ARGS__);			\
			अवरोध;						\
		शेष:						\
			__fail_smccc_1_1(__VA_ARGS__);			\
			method = SMCCC_CONDUIT_NONE;			\
			अवरोध;						\
		पूर्ण							\
		method;							\
	पूर्ण)

#पूर्ण_अगर /*__ASSEMBLY__*/
#पूर्ण_अगर /*__LINUX_ARM_SMCCC_H*/
