<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020 Arm Limited
 */

#घोषणा pr_fmt(fmt) "SMCCC: SOC_ID: " fmt

#समावेश <linux/arm-smccc.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#घोषणा SMCCC_SOC_ID_JEP106_BANK_IDX_MASK	GENMASK(30, 24)
/*
 * As per the SMC Calling Convention specअगरication v1.2 (ARM DEN 0028C)
 * Section 7.4 SMCCC_ARCH_SOC_ID bits[23:16] are JEP-106 identअगरication
 * code with parity bit क्रम the SiP. We can drop the parity bit.
 */
#घोषणा SMCCC_SOC_ID_JEP106_ID_CODE_MASK	GENMASK(22, 16)
#घोषणा SMCCC_SOC_ID_IMP_DEF_SOC_ID_MASK	GENMASK(15, 0)

#घोषणा JEP106_BANK_CONT_CODE(x)	\
	(u8)(FIELD_GET(SMCCC_SOC_ID_JEP106_BANK_IDX_MASK, (x)))
#घोषणा JEP106_ID_CODE(x)	\
	(u8)(FIELD_GET(SMCCC_SOC_ID_JEP106_ID_CODE_MASK, (x)))
#घोषणा IMP_DEF_SOC_ID(x)	\
	(u16)(FIELD_GET(SMCCC_SOC_ID_IMP_DEF_SOC_ID_MASK, (x)))

अटल काष्ठा soc_device *soc_dev;
अटल काष्ठा soc_device_attribute *soc_dev_attr;

अटल पूर्णांक __init smccc_soc_init(व्योम)
अणु
	काष्ठा arm_smccc_res res;
	पूर्णांक soc_id_rev, soc_id_version;
	अटल अक्षर soc_id_str[20], soc_id_rev_str[12];
	अटल अक्षर soc_id_jep106_id_str[12];

	अगर (arm_smccc_get_version() < ARM_SMCCC_VERSION_1_2)
		वापस 0;

	अगर (arm_smccc_1_1_get_conduit() == SMCCC_CONDUIT_NONE) अणु
		pr_err("%s: invalid SMCCC conduit\n", __func__);
		वापस -EOPNOTSUPP;
	पूर्ण

	arm_smccc_1_1_invoke(ARM_SMCCC_ARCH_FEATURES_FUNC_ID,
			     ARM_SMCCC_ARCH_SOC_ID, &res);

	अगर (res.a0 == SMCCC_RET_NOT_SUPPORTED) अणु
		pr_info("ARCH_SOC_ID not implemented, skipping ....\n");
		वापस 0;
	पूर्ण

	अगर ((पूर्णांक)res.a0 < 0) अणु
		pr_info("ARCH_FEATURES(ARCH_SOC_ID) returned error: %lx\n",
			res.a0);
		वापस -EINVAL;
	पूर्ण

	arm_smccc_1_1_invoke(ARM_SMCCC_ARCH_SOC_ID, 0, &res);
	अगर ((पूर्णांक)res.a0 < 0) अणु
		pr_err("ARCH_SOC_ID(0) returned error: %lx\n", res.a0);
		वापस -EINVAL;
	पूर्ण

	soc_id_version = res.a0;

	arm_smccc_1_1_invoke(ARM_SMCCC_ARCH_SOC_ID, 1, &res);
	अगर ((पूर्णांक)res.a0 < 0) अणु
		pr_err("ARCH_SOC_ID(1) returned error: %lx\n", res.a0);
		वापस -EINVAL;
	पूर्ण

	soc_id_rev = res.a0;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENOMEM;

	प्र_लिखो(soc_id_rev_str, "0x%08x", soc_id_rev);
	प्र_लिखो(soc_id_jep106_id_str, "jep106:%02x%02x",
		JEP106_BANK_CONT_CODE(soc_id_version),
		JEP106_ID_CODE(soc_id_version));
	प्र_लिखो(soc_id_str, "%s:%04x", soc_id_jep106_id_str,
		IMP_DEF_SOC_ID(soc_id_version));

	soc_dev_attr->soc_id = soc_id_str;
	soc_dev_attr->revision = soc_id_rev_str;
	soc_dev_attr->family = soc_id_jep106_id_str;

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr);
		वापस PTR_ERR(soc_dev);
	पूर्ण

	pr_info("ID = %s Revision = %s\n", soc_dev_attr->soc_id,
		soc_dev_attr->revision);

	वापस 0;
पूर्ण
module_init(smccc_soc_init);

अटल व्योम __निकास smccc_soc_निकास(व्योम)
अणु
	अगर (soc_dev)
		soc_device_unरेजिस्टर(soc_dev);
	kमुक्त(soc_dev_attr);
पूर्ण
module_निकास(smccc_soc_निकास);
