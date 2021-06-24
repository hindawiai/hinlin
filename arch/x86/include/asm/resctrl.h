<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_RESCTRL_H
#घोषणा _ASM_X86_RESCTRL_H

#अगर_घोषित CONFIG_X86_CPU_RESCTRL

#समावेश <linux/sched.h>
#समावेश <linux/jump_label.h>

#घोषणा IA32_PQR_ASSOC	0x0c8f

/**
 * काष्ठा resctrl_pqr_state - State cache क्रम the PQR MSR
 * @cur_rmid:		The cached Resource Monitoring ID
 * @cur_closid:	The cached Class Of Service ID
 * @शेष_rmid:	The user asचिन्हित Resource Monitoring ID
 * @शेष_closid:	The user asचिन्हित cached Class Of Service ID
 *
 * The upper 32 bits of IA32_PQR_ASSOC contain closid and the
 * lower 10 bits rmid. The update to IA32_PQR_ASSOC always
 * contains both parts, so we need to cache them. This also
 * stores the user configured per cpu CLOSID and RMID.
 *
 * The cache also helps to aव्योम poपूर्णांकless updates अगर the value करोes
 * not change.
 */
काष्ठा resctrl_pqr_state अणु
	u32			cur_rmid;
	u32			cur_closid;
	u32			शेष_rmid;
	u32			शेष_closid;
पूर्ण;

DECLARE_PER_CPU(काष्ठा resctrl_pqr_state, pqr_state);

DECLARE_STATIC_KEY_FALSE(rdt_enable_key);
DECLARE_STATIC_KEY_FALSE(rdt_alloc_enable_key);
DECLARE_STATIC_KEY_FALSE(rdt_mon_enable_key);

/*
 * __resctrl_sched_in() - Writes the task's CLOSid/RMID to IA32_PQR_MSR
 *
 * Following considerations are made so that this has minimal impact
 * on scheduler hot path:
 * - This will stay as no-op unless we are running on an Intel SKU
 *   which supports resource control or monitoring and we enable by
 *   mounting the resctrl file प्रणाली.
 * - Caches the per cpu CLOSid/RMID values and करोes the MSR ग_लिखो only
 *   when a task with a dअगरferent CLOSid/RMID is scheduled in.
 * - We allocate RMIDs/CLOSids globally in order to keep this as
 *   simple as possible.
 * Must be called with preemption disabled.
 */
अटल व्योम __resctrl_sched_in(व्योम)
अणु
	काष्ठा resctrl_pqr_state *state = this_cpu_ptr(&pqr_state);
	u32 closid = state->शेष_closid;
	u32 rmid = state->शेष_rmid;
	u32 पंचांगp;

	/*
	 * If this task has a closid/rmid asचिन्हित, use it.
	 * Else use the closid/rmid asचिन्हित to this cpu.
	 */
	अगर (अटल_branch_likely(&rdt_alloc_enable_key)) अणु
		पंचांगp = READ_ONCE(current->closid);
		अगर (पंचांगp)
			closid = पंचांगp;
	पूर्ण

	अगर (अटल_branch_likely(&rdt_mon_enable_key)) अणु
		पंचांगp = READ_ONCE(current->rmid);
		अगर (पंचांगp)
			rmid = पंचांगp;
	पूर्ण

	अगर (closid != state->cur_closid || rmid != state->cur_rmid) अणु
		state->cur_closid = closid;
		state->cur_rmid = rmid;
		wrmsr(IA32_PQR_ASSOC, rmid, closid);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम resctrl_sched_in(व्योम)
अणु
	अगर (अटल_branch_likely(&rdt_enable_key))
		__resctrl_sched_in();
पूर्ण

व्योम resctrl_cpu_detect(काष्ठा cpuinfo_x86 *c);

#अन्यथा

अटल अंतरभूत व्योम resctrl_sched_in(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम resctrl_cpu_detect(काष्ठा cpuinfo_x86 *c) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_X86_CPU_RESCTRL */

#पूर्ण_अगर /* _ASM_X86_RESCTRL_H */
