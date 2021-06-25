<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2010,2015,2019 The Linux Foundation. All rights reserved.
 * Copyright (C) 2015 Linaro Ltd.
 */

#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/dma-mapping.h>

#समावेश "qcom_scm.h"

अटल DEFINE_MUTEX(qcom_scm_lock);


/**
 * काष्ठा arm_smccc_args
 * @args:	The array of values used in रेजिस्टरs in smc inकाष्ठाion
 */
काष्ठा arm_smccc_args अणु
	अचिन्हित दीर्घ args[8];
पूर्ण;


/**
 * काष्ठा scm_legacy_command - one SCM command buffer
 * @len: total available memory क्रम command and response
 * @buf_offset: start of command buffer
 * @resp_hdr_offset: start of response buffer
 * @id: command to be executed
 * @buf: buffer वापसed from scm_legacy_get_command_buffer()
 *
 * An SCM command is laid out in memory as follows:
 *
 *	------------------- <--- काष्ठा scm_legacy_command
 *	| command header  |
 *	------------------- <--- scm_legacy_get_command_buffer()
 *	| command buffer  |
 *	------------------- <--- काष्ठा scm_legacy_response and
 *	| response header |      scm_legacy_command_to_response()
 *	------------------- <--- scm_legacy_get_response_buffer()
 *	| response buffer |
 *	-------------------
 *
 * There can be arbitrary padding between the headers and buffers so
 * you should always use the appropriate scm_legacy_get_*_buffer() routines
 * to access the buffers in a safe manner.
 */
काष्ठा scm_legacy_command अणु
	__le32 len;
	__le32 buf_offset;
	__le32 resp_hdr_offset;
	__le32 id;
	__le32 buf[];
पूर्ण;

/**
 * काष्ठा scm_legacy_response - one SCM response buffer
 * @len: total available memory क्रम response
 * @buf_offset: start of response data relative to start of scm_legacy_response
 * @is_complete: indicates अगर the command has finished processing
 */
काष्ठा scm_legacy_response अणु
	__le32 len;
	__le32 buf_offset;
	__le32 is_complete;
पूर्ण;

/**
 * scm_legacy_command_to_response() - Get a poपूर्णांकer to a scm_legacy_response
 * @cmd: command
 *
 * Returns a poपूर्णांकer to a response क्रम a command.
 */
अटल अंतरभूत काष्ठा scm_legacy_response *scm_legacy_command_to_response(
		स्थिर काष्ठा scm_legacy_command *cmd)
अणु
	वापस (व्योम *)cmd + le32_to_cpu(cmd->resp_hdr_offset);
पूर्ण

/**
 * scm_legacy_get_command_buffer() - Get a poपूर्णांकer to a command buffer
 * @cmd: command
 *
 * Returns a poपूर्णांकer to the command buffer of a command.
 */
अटल अंतरभूत व्योम *scm_legacy_get_command_buffer(
		स्थिर काष्ठा scm_legacy_command *cmd)
अणु
	वापस (व्योम *)cmd->buf;
पूर्ण

/**
 * scm_legacy_get_response_buffer() - Get a poपूर्णांकer to a response buffer
 * @rsp: response
 *
 * Returns a poपूर्णांकer to a response buffer of a response.
 */
अटल अंतरभूत व्योम *scm_legacy_get_response_buffer(
		स्थिर काष्ठा scm_legacy_response *rsp)
अणु
	वापस (व्योम *)rsp + le32_to_cpu(rsp->buf_offset);
पूर्ण

अटल व्योम __scm_legacy_करो(स्थिर काष्ठा arm_smccc_args *smc,
			    काष्ठा arm_smccc_res *res)
अणु
	करो अणु
		arm_smccc_smc(smc->args[0], smc->args[1], smc->args[2],
			      smc->args[3], smc->args[4], smc->args[5],
			      smc->args[6], smc->args[7], res);
	पूर्ण जबतक (res->a0 == QCOM_SCM_INTERRUPTED);
पूर्ण

/**
 * scm_legacy_call() - Sends a command to the SCM and रुकोs क्रम the command to
 * finish processing.
 *
 * A note on cache मुख्यtenance:
 * Note that any buffers that are expected to be accessed by the secure world
 * must be flushed beक्रमe invoking qcom_scm_call and invalidated in the cache
 * immediately after qcom_scm_call वापसs. Cache मुख्यtenance on the command
 * and response buffers is taken care of by qcom_scm_call; however, callers are
 * responsible क्रम any other cached buffers passed over to the secure world.
 */
पूर्णांक scm_legacy_call(काष्ठा device *dev, स्थिर काष्ठा qcom_scm_desc *desc,
		    काष्ठा qcom_scm_res *res)
अणु
	u8 arglen = desc->arginfo & 0xf;
	पूर्णांक ret = 0, context_id;
	अचिन्हित पूर्णांक i;
	काष्ठा scm_legacy_command *cmd;
	काष्ठा scm_legacy_response *rsp;
	काष्ठा arm_smccc_args smc = अणु0पूर्ण;
	काष्ठा arm_smccc_res smc_res;
	स्थिर माप_प्रकार cmd_len = arglen * माप(__le32);
	स्थिर माप_प्रकार resp_len = MAX_QCOM_SCM_RETS * माप(__le32);
	माप_प्रकार alloc_len = माप(*cmd) + cmd_len + माप(*rsp) + resp_len;
	dma_addr_t cmd_phys;
	__le32 *arg_buf;
	स्थिर __le32 *res_buf;

	cmd = kzalloc(PAGE_ALIGN(alloc_len), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->len = cpu_to_le32(alloc_len);
	cmd->buf_offset = cpu_to_le32(माप(*cmd));
	cmd->resp_hdr_offset = cpu_to_le32(माप(*cmd) + cmd_len);
	cmd->id = cpu_to_le32(SCM_LEGACY_FNID(desc->svc, desc->cmd));

	arg_buf = scm_legacy_get_command_buffer(cmd);
	क्रम (i = 0; i < arglen; i++)
		arg_buf[i] = cpu_to_le32(desc->args[i]);

	rsp = scm_legacy_command_to_response(cmd);

	cmd_phys = dma_map_single(dev, cmd, alloc_len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, cmd_phys)) अणु
		kमुक्त(cmd);
		वापस -ENOMEM;
	पूर्ण

	smc.args[0] = 1;
	smc.args[1] = (अचिन्हित दीर्घ)&context_id;
	smc.args[2] = cmd_phys;

	mutex_lock(&qcom_scm_lock);
	__scm_legacy_करो(&smc, &smc_res);
	अगर (smc_res.a0)
		ret = qcom_scm_remap_error(smc_res.a0);
	mutex_unlock(&qcom_scm_lock);
	अगर (ret)
		जाओ out;

	करो अणु
		dma_sync_single_क्रम_cpu(dev, cmd_phys + माप(*cmd) + cmd_len,
					माप(*rsp), DMA_FROM_DEVICE);
	पूर्ण जबतक (!rsp->is_complete);

	dma_sync_single_क्रम_cpu(dev, cmd_phys + माप(*cmd) + cmd_len +
				le32_to_cpu(rsp->buf_offset),
				resp_len, DMA_FROM_DEVICE);

	अगर (res) अणु
		res_buf = scm_legacy_get_response_buffer(rsp);
		क्रम (i = 0; i < MAX_QCOM_SCM_RETS; i++)
			res->result[i] = le32_to_cpu(res_buf[i]);
	पूर्ण
out:
	dma_unmap_single(dev, cmd_phys, alloc_len, DMA_TO_DEVICE);
	kमुक्त(cmd);
	वापस ret;
पूर्ण

#घोषणा SCM_LEGACY_ATOMIC_N_REG_ARGS	5
#घोषणा SCM_LEGACY_ATOMIC_FIRST_REG_IDX	2
#घोषणा SCM_LEGACY_CLASS_REGISTER		(0x2 << 8)
#घोषणा SCM_LEGACY_MASK_IRQS		BIT(5)
#घोषणा SCM_LEGACY_ATOMIC_ID(svc, cmd, n) \
				((SCM_LEGACY_FNID(svc, cmd) << 12) | \
				SCM_LEGACY_CLASS_REGISTER | \
				SCM_LEGACY_MASK_IRQS | \
				(n & 0xf))

/**
 * scm_legacy_call_atomic() - Send an atomic SCM command with up to 5 arguments
 * and 3 वापस values
 * @desc: SCM call descriptor containing arguments
 * @res:  SCM call वापस values
 *
 * This shall only be used with commands that are guaranteed to be
 * unपूर्णांकerruptable, atomic and SMP safe.
 */
पूर्णांक scm_legacy_call_atomic(काष्ठा device *unused,
			   स्थिर काष्ठा qcom_scm_desc *desc,
			   काष्ठा qcom_scm_res *res)
अणु
	पूर्णांक context_id;
	काष्ठा arm_smccc_res smc_res;
	माप_प्रकार arglen = desc->arginfo & 0xf;

	BUG_ON(arglen > SCM_LEGACY_ATOMIC_N_REG_ARGS);

	arm_smccc_smc(SCM_LEGACY_ATOMIC_ID(desc->svc, desc->cmd, arglen),
		      (अचिन्हित दीर्घ)&context_id,
		      desc->args[0], desc->args[1], desc->args[2],
		      desc->args[3], desc->args[4], 0, &smc_res);

	अगर (res) अणु
		res->result[0] = smc_res.a1;
		res->result[1] = smc_res.a2;
		res->result[2] = smc_res.a3;
	पूर्ण

	वापस smc_res.a0;
पूर्ण
