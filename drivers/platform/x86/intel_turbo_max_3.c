<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Turbo Boost Max Technology 3.0 legacy (non HWP) क्रमागतeration driver
 * Copyright (c) 2017, Intel Corporation.
 * All rights reserved.
 *
 * Author: Srinivas Pandruvada <srinivas.pandruvada@linux.पूर्णांकel.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpufeature.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/topology.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>

#घोषणा MSR_OC_MAILBOX			0x150
#घोषणा MSR_OC_MAILBOX_CMD_OFFSET	32
#घोषणा MSR_OC_MAILBOX_RSP_OFFSET	32
#घोषणा MSR_OC_MAILBOX_BUSY_BIT		63
#घोषणा OC_MAILBOX_FC_CONTROL_CMD	0x1C

/*
 * Typical latency to get mail box response is ~3us, It takes +3 us to
 * process पढ़ोing mailbox after issuing mailbox ग_लिखो on a Broadwell 3.4 GHz
 * प्रणाली. So क्रम most of the समय, the first mailbox पढ़ो should have the
 * response, but to aव्योम some boundary हालs retry twice.
 */
#घोषणा OC_MAILBOX_RETRY_COUNT		2

अटल पूर्णांक get_oc_core_priority(अचिन्हित पूर्णांक cpu)
अणु
	u64 value, cmd = OC_MAILBOX_FC_CONTROL_CMD;
	पूर्णांक ret, i;

	/* Issue favored core पढ़ो command */
	value = cmd << MSR_OC_MAILBOX_CMD_OFFSET;
	/* Set the busy bit to indicate OS is trying to issue command */
	value |=  BIT_ULL(MSR_OC_MAILBOX_BUSY_BIT);
	ret = wrmsrl_safe(MSR_OC_MAILBOX, value);
	अगर (ret) अणु
		pr_debug("cpu %d OC mailbox write failed\n", cpu);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < OC_MAILBOX_RETRY_COUNT; ++i) अणु
		ret = rdmsrl_safe(MSR_OC_MAILBOX, &value);
		अगर (ret) अणु
			pr_debug("cpu %d OC mailbox read failed\n", cpu);
			अवरोध;
		पूर्ण

		अगर (value & BIT_ULL(MSR_OC_MAILBOX_BUSY_BIT)) अणु
			pr_debug("cpu %d OC mailbox still processing\n", cpu);
			ret = -EBUSY;
			जारी;
		पूर्ण

		अगर ((value >> MSR_OC_MAILBOX_RSP_OFFSET) & 0xff) अणु
			pr_debug("cpu %d OC mailbox cmd failed\n", cpu);
			ret = -ENXIO;
			अवरोध;
		पूर्ण

		ret = value & 0xff;
		pr_debug("cpu %d max_ratio %d\n", cpu, ret);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The work item is needed to aव्योम CPU hotplug locking issues. The function
 * iपंचांगt_legacy_set_priority() is called from CPU online callback, so can't
 * call sched_set_iपंचांगt_support() from there as this function will aquire
 * hotplug locks in its path.
 */
अटल व्योम iपंचांगt_legacy_work_fn(काष्ठा work_काष्ठा *work)
अणु
	sched_set_iपंचांगt_support();
पूर्ण

अटल DECLARE_WORK(sched_iपंचांगt_work, iपंचांगt_legacy_work_fn);

अटल पूर्णांक iपंचांगt_legacy_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	अटल u32 max_highest_perf = 0, min_highest_perf = U32_MAX;
	पूर्णांक priority;

	priority = get_oc_core_priority(cpu);
	अगर (priority < 0)
		वापस 0;

	sched_set_iपंचांगt_core_prio(priority, cpu);

	/* Enable ITMT feature when a core with dअगरferent priority is found */
	अगर (max_highest_perf <= min_highest_perf) अणु
		अगर (priority > max_highest_perf)
			max_highest_perf = priority;

		अगर (priority < min_highest_perf)
			min_highest_perf = priority;

		अगर (max_highest_perf > min_highest_perf)
			schedule_work(&sched_iपंचांगt_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id iपंचांगt_legacy_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_X,	शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_X,	शून्य),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init iपंचांगt_legacy_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	पूर्णांक ret;

	id = x86_match_cpu(iपंचांगt_legacy_cpu_ids);
	अगर (!id)
		वापस -ENODEV;

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN,
				"platform/x86/turbo_max_3:online",
				iपंचांगt_legacy_cpu_online,	शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
late_initcall(iपंचांगt_legacy_init)
