<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Speed Select Interface: Mbox via MSR Interface
 * Copyright (c) 2019, Intel Corporation.
 * All rights reserved.
 *
 * Author: Srinivas Pandruvada <srinivas.pandruvada@linux.पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <linux/topology.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/isst_अगर.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>

#समावेश "isst_if_common.h"

#घोषणा MSR_OS_MAILBOX_INTERFACE	0xB0
#घोषणा MSR_OS_MAILBOX_DATA		0xB1
#घोषणा MSR_OS_MAILBOX_BUSY_BIT		31

/*
 * Based on experiments count is never more than 1, as the MSR overhead
 * is enough to finish the command. So here this is the worst हाल number.
 */
#घोषणा OS_MAILBOX_RETRY_COUNT		3

अटल पूर्णांक isst_अगर_send_mbox_cmd(u8 command, u8 sub_command, u32 parameter,
				 u32 command_data, u32 *response_data)
अणु
	u32 retries;
	u64 data;
	पूर्णांक ret;

	/* Poll क्रम rb bit == 0 */
	retries = OS_MAILBOX_RETRY_COUNT;
	करो अणु
		rdmsrl(MSR_OS_MAILBOX_INTERFACE, data);
		अगर (data & BIT_ULL(MSR_OS_MAILBOX_BUSY_BIT)) अणु
			ret = -EBUSY;
			जारी;
		पूर्ण
		ret = 0;
		अवरोध;
	पूर्ण जबतक (--retries);

	अगर (ret)
		वापस ret;

	/* Write DATA रेजिस्टर */
	wrmsrl(MSR_OS_MAILBOX_DATA, command_data);

	/* Write command रेजिस्टर */
	data = BIT_ULL(MSR_OS_MAILBOX_BUSY_BIT) |
		      (parameter & GENMASK_ULL(13, 0)) << 16 |
		      (sub_command << 8) |
		      command;
	wrmsrl(MSR_OS_MAILBOX_INTERFACE, data);

	/* Poll क्रम rb bit == 0 */
	retries = OS_MAILBOX_RETRY_COUNT;
	करो अणु
		rdmsrl(MSR_OS_MAILBOX_INTERFACE, data);
		अगर (data & BIT_ULL(MSR_OS_MAILBOX_BUSY_BIT)) अणु
			ret = -EBUSY;
			जारी;
		पूर्ण

		अगर (data & 0xff)
			वापस -ENXIO;

		अगर (response_data) अणु
			rdmsrl(MSR_OS_MAILBOX_DATA, data);
			*response_data = data;
		पूर्ण
		ret = 0;
		अवरोध;
	पूर्ण जबतक (--retries);

	वापस ret;
पूर्ण

काष्ठा msrl_action अणु
	पूर्णांक err;
	काष्ठा isst_अगर_mbox_cmd *mbox_cmd;
पूर्ण;

/* revisit, smp_call_function_single should be enough क्रम atomic mailbox! */
अटल व्योम msrl_update_func(व्योम *info)
अणु
	काष्ठा msrl_action *act = info;

	act->err = isst_अगर_send_mbox_cmd(act->mbox_cmd->command,
					 act->mbox_cmd->sub_command,
					 act->mbox_cmd->parameter,
					 act->mbox_cmd->req_data,
					 &act->mbox_cmd->resp_data);
पूर्ण

अटल दीर्घ isst_अगर_mbox_proc_cmd(u8 *cmd_ptr, पूर्णांक *ग_लिखो_only, पूर्णांक resume)
अणु
	काष्ठा msrl_action action;
	पूर्णांक ret;

	action.mbox_cmd = (काष्ठा isst_अगर_mbox_cmd *)cmd_ptr;

	अगर (isst_अगर_mbox_cmd_invalid(action.mbox_cmd))
		वापस -EINVAL;

	अगर (isst_अगर_mbox_cmd_set_req(action.mbox_cmd) &&
	    !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	/*
	 * To complete mailbox command, we need to access two MSRs.
	 * So we करोn't want race to complete a mailbox transcation.
	 * Here smp_call ensures that msrl_update_func() has no race
	 * and also with रुको flag, रुको क्रम completion.
	 * smp_call_function_single is using get_cpu() and put_cpu().
	 */
	ret = smp_call_function_single(action.mbox_cmd->logical_cpu,
				       msrl_update_func, &action, 1);
	अगर (ret)
		वापस ret;

	अगर (!action.err && !resume && isst_अगर_mbox_cmd_set_req(action.mbox_cmd))
		action.err = isst_store_cmd(action.mbox_cmd->command,
					    action.mbox_cmd->sub_command,
					    action.mbox_cmd->logical_cpu, 1,
					    action.mbox_cmd->parameter,
					    action.mbox_cmd->req_data);
	*ग_लिखो_only = 0;

	वापस action.err;
पूर्ण


अटल पूर्णांक isst_pm_notअगरy(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ mode, व्योम *_unused)
अणु
	चयन (mode) अणु
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_RESTORE:
	हाल PM_POST_SUSPEND:
		isst_resume_common();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block isst_pm_nb = अणु
	.notअगरier_call = isst_pm_notअगरy,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id isst_अगर_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_X, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, isst_अगर_cpu_ids);

अटल पूर्णांक __init isst_अगर_mbox_init(व्योम)
अणु
	काष्ठा isst_अगर_cmd_cb cb;
	स्थिर काष्ठा x86_cpu_id *id;
	u64 data;
	पूर्णांक ret;

	id = x86_match_cpu(isst_अगर_cpu_ids);
	अगर (!id)
		वापस -ENODEV;

	/* Check presence of mailbox MSRs */
	ret = rdmsrl_safe(MSR_OS_MAILBOX_INTERFACE, &data);
	अगर (ret)
		वापस ret;

	ret = rdmsrl_safe(MSR_OS_MAILBOX_DATA, &data);
	अगर (ret)
		वापस ret;

	स_रखो(&cb, 0, माप(cb));
	cb.cmd_size = माप(काष्ठा isst_अगर_mbox_cmd);
	cb.offset = दुरत्व(काष्ठा isst_अगर_mbox_cmds, mbox_cmd);
	cb.cmd_callback = isst_अगर_mbox_proc_cmd;
	cb.owner = THIS_MODULE;
	ret = isst_अगर_cdev_रेजिस्टर(ISST_IF_DEV_MBOX, &cb);
	अगर (ret)
		वापस ret;

	ret = रेजिस्टर_pm_notअगरier(&isst_pm_nb);
	अगर (ret)
		isst_अगर_cdev_unरेजिस्टर(ISST_IF_DEV_MBOX);

	वापस ret;
पूर्ण
module_init(isst_अगर_mbox_init)

अटल व्योम __निकास isst_अगर_mbox_निकास(व्योम)
अणु
	unरेजिस्टर_pm_notअगरier(&isst_pm_nb);
	isst_अगर_cdev_unरेजिस्टर(ISST_IF_DEV_MBOX);
पूर्ण
module_निकास(isst_अगर_mbox_निकास)

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel speed select interface mailbox driver");
