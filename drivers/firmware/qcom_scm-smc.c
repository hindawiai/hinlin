<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015,2019 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/dma-mapping.h>

#समावेश "qcom_scm.h"

/**
 * काष्ठा arm_smccc_args
 * @args:	The array of values used in रेजिस्टरs in smc inकाष्ठाion
 */
काष्ठा arm_smccc_args अणु
	अचिन्हित दीर्घ args[8];
पूर्ण;

अटल DEFINE_MUTEX(qcom_scm_lock);

#घोषणा QCOM_SCM_EBUSY_WAIT_MS 30
#घोषणा QCOM_SCM_EBUSY_MAX_RETRY 20

#घोषणा SCM_SMC_N_REG_ARGS	4
#घोषणा SCM_SMC_FIRST_EXT_IDX	(SCM_SMC_N_REG_ARGS - 1)
#घोषणा SCM_SMC_N_EXT_ARGS	(MAX_QCOM_SCM_ARGS - SCM_SMC_N_REG_ARGS + 1)
#घोषणा SCM_SMC_FIRST_REG_IDX	2
#घोषणा SCM_SMC_LAST_REG_IDX	(SCM_SMC_FIRST_REG_IDX + SCM_SMC_N_REG_ARGS - 1)

अटल व्योम __scm_smc_करो_quirk(स्थिर काष्ठा arm_smccc_args *smc,
			       काष्ठा arm_smccc_res *res)
अणु
	अचिन्हित दीर्घ a0 = smc->args[0];
	काष्ठा arm_smccc_quirk quirk = अणु .id = ARM_SMCCC_QUIRK_QCOM_A6 पूर्ण;

	quirk.state.a6 = 0;

	करो अणु
		arm_smccc_smc_quirk(a0, smc->args[1], smc->args[2],
				    smc->args[3], smc->args[4], smc->args[5],
				    quirk.state.a6, smc->args[7], res, &quirk);

		अगर (res->a0 == QCOM_SCM_INTERRUPTED)
			a0 = res->a0;

	पूर्ण जबतक (res->a0 == QCOM_SCM_INTERRUPTED);
पूर्ण

अटल व्योम __scm_smc_करो(स्थिर काष्ठा arm_smccc_args *smc,
			 काष्ठा arm_smccc_res *res, bool atomic)
अणु
	पूर्णांक retry_count = 0;

	अगर (atomic) अणु
		__scm_smc_करो_quirk(smc, res);
		वापस;
	पूर्ण

	करो अणु
		mutex_lock(&qcom_scm_lock);

		__scm_smc_करो_quirk(smc, res);

		mutex_unlock(&qcom_scm_lock);

		अगर (res->a0 == QCOM_SCM_V2_EBUSY) अणु
			अगर (retry_count++ > QCOM_SCM_EBUSY_MAX_RETRY)
				अवरोध;
			msleep(QCOM_SCM_EBUSY_WAIT_MS);
		पूर्ण
	पूर्ण  जबतक (res->a0 == QCOM_SCM_V2_EBUSY);
पूर्ण


पूर्णांक __scm_smc_call(काष्ठा device *dev, स्थिर काष्ठा qcom_scm_desc *desc,
		   क्रमागत qcom_scm_convention qcom_convention,
		   काष्ठा qcom_scm_res *res, bool atomic)
अणु
	पूर्णांक arglen = desc->arginfo & 0xf;
	पूर्णांक i;
	dma_addr_t args_phys = 0;
	व्योम *args_virt = शून्य;
	माप_प्रकार alloc_len;
	gfp_t flag = atomic ? GFP_ATOMIC : GFP_KERNEL;
	u32 smccc_call_type = atomic ? ARM_SMCCC_FAST_CALL : ARM_SMCCC_STD_CALL;
	u32 qcom_smccc_convention = (qcom_convention == SMC_CONVENTION_ARM_32) ?
				    ARM_SMCCC_SMC_32 : ARM_SMCCC_SMC_64;
	काष्ठा arm_smccc_res smc_res;
	काष्ठा arm_smccc_args smc = अणु0पूर्ण;

	smc.args[0] = ARM_SMCCC_CALL_VAL(
		smccc_call_type,
		qcom_smccc_convention,
		desc->owner,
		SCM_SMC_FNID(desc->svc, desc->cmd));
	smc.args[1] = desc->arginfo;
	क्रम (i = 0; i < SCM_SMC_N_REG_ARGS; i++)
		smc.args[i + SCM_SMC_FIRST_REG_IDX] = desc->args[i];

	अगर (unlikely(arglen > SCM_SMC_N_REG_ARGS)) अणु
		alloc_len = SCM_SMC_N_EXT_ARGS * माप(u64);
		args_virt = kzalloc(PAGE_ALIGN(alloc_len), flag);

		अगर (!args_virt)
			वापस -ENOMEM;

		अगर (qcom_smccc_convention == ARM_SMCCC_SMC_32) अणु
			__le32 *args = args_virt;

			क्रम (i = 0; i < SCM_SMC_N_EXT_ARGS; i++)
				args[i] = cpu_to_le32(desc->args[i +
						      SCM_SMC_FIRST_EXT_IDX]);
		पूर्ण अन्यथा अणु
			__le64 *args = args_virt;

			क्रम (i = 0; i < SCM_SMC_N_EXT_ARGS; i++)
				args[i] = cpu_to_le64(desc->args[i +
						      SCM_SMC_FIRST_EXT_IDX]);
		पूर्ण

		args_phys = dma_map_single(dev, args_virt, alloc_len,
					   DMA_TO_DEVICE);

		अगर (dma_mapping_error(dev, args_phys)) अणु
			kमुक्त(args_virt);
			वापस -ENOMEM;
		पूर्ण

		smc.args[SCM_SMC_LAST_REG_IDX] = args_phys;
	पूर्ण

	__scm_smc_करो(&smc, &smc_res, atomic);

	अगर (args_virt) अणु
		dma_unmap_single(dev, args_phys, alloc_len, DMA_TO_DEVICE);
		kमुक्त(args_virt);
	पूर्ण

	अगर (res) अणु
		res->result[0] = smc_res.a1;
		res->result[1] = smc_res.a2;
		res->result[2] = smc_res.a3;
	पूर्ण

	वापस (दीर्घ)smc_res.a0 ? qcom_scm_remap_error(smc_res.a0) : 0;

पूर्ण
