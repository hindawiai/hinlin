<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/regset.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>

#समावेश <यंत्र/debug.h>

#समावेश "ptrace-decl.h"

व्योम user_enable_single_step(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pt_regs *regs = task->thपढ़ो.regs;

	अगर (regs != शून्य) अणु
		regs->msr &= ~MSR_BE;
		regs->msr |= MSR_SE;
	पूर्ण
	set_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP);
पूर्ण

व्योम user_enable_block_step(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pt_regs *regs = task->thपढ़ो.regs;

	अगर (regs != शून्य) अणु
		regs->msr &= ~MSR_SE;
		regs->msr |= MSR_BE;
	पूर्ण
	set_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP);
पूर्ण

व्योम user_disable_single_step(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pt_regs *regs = task->thपढ़ो.regs;

	अगर (regs != शून्य)
		regs->msr &= ~(MSR_SE | MSR_BE);

	clear_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP);
पूर्ण

व्योम ppc_gethwdinfo(काष्ठा ppc_debug_info *dbginfo)
अणु
	dbginfo->version = 1;
	dbginfo->num_inकाष्ठाion_bps = 0;
	अगर (ppc_अवरोधpoपूर्णांक_available())
		dbginfo->num_data_bps = nr_wp_slots();
	अन्यथा
		dbginfo->num_data_bps = 0;
	dbginfo->num_condition_regs = 0;
	dbginfo->data_bp_alignment = माप(दीर्घ);
	dbginfo->माप_condition = 0;
	अगर (IS_ENABLED(CONFIG_HAVE_HW_BREAKPOINT)) अणु
		dbginfo->features = PPC_DEBUG_FEATURE_DATA_BP_RANGE;
		अगर (dawr_enabled())
			dbginfo->features |= PPC_DEBUG_FEATURE_DATA_BP_DAWR;
	पूर्ण अन्यथा अणु
		dbginfo->features = 0;
	पूर्ण
	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		dbginfo->features |= PPC_DEBUG_FEATURE_DATA_BP_ARCH_31;
पूर्ण

पूर्णांक ptrace_get_debugreg(काष्ठा task_काष्ठा *child, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ __user *datalp)
अणु
	अचिन्हित दीर्घ dabr_fake;

	/* We only support one DABR and no IABRS at the moment */
	अगर (addr > 0)
		वापस -EINVAL;
	dabr_fake = ((child->thपढ़ो.hw_brk[0].address & (~HW_BRK_TYPE_DABR)) |
		     (child->thपढ़ो.hw_brk[0].type & HW_BRK_TYPE_DABR));
	वापस put_user(dabr_fake, datalp);
पूर्ण

/*
 * ptrace_set_debugreg() fakes DABR and DABR is only one. So even अगर
 * पूर्णांकernal hw supports more than one watchpoपूर्णांक, we support only one
 * watchpoपूर्णांक with this पूर्णांकerface.
 */
पूर्णांक ptrace_set_debugreg(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	पूर्णांक ret;
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो = &task->thपढ़ो;
	काष्ठा perf_event *bp;
	काष्ठा perf_event_attr attr;
#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */
	bool set_bp = true;
	काष्ठा arch_hw_अवरोधpoपूर्णांक hw_brk;

	/* For ppc64 we support one DABR and no IABR's at the moment (ppc64).
	 *  For embedded processors we support one DAC and no IAC's at the
	 *  moment.
	 */
	अगर (addr > 0)
		वापस -EINVAL;

	/* The bottom 3 bits in dabr are flags */
	अगर ((data & ~0x7UL) >= TASK_SIZE)
		वापस -EIO;

	/* For processors using DABR (i.e. 970), the bottom 3 bits are flags.
	 *  It was assumed, on previous implementations, that 3 bits were
	 *  passed together with the data address, fitting the design of the
	 *  DABR रेजिस्टर, as follows:
	 *
	 *  bit 0: Read flag
	 *  bit 1: Write flag
	 *  bit 2: Breakpoपूर्णांक translation
	 *
	 *  Thus, we use them here as so.
	 */

	/* Ensure अवरोधpoपूर्णांक translation bit is set */
	अगर (data && !(data & HW_BRK_TYPE_TRANSLATE))
		वापस -EIO;
	hw_brk.address = data & (~HW_BRK_TYPE_DABR);
	hw_brk.type = (data & HW_BRK_TYPE_DABR) | HW_BRK_TYPE_PRIV_ALL;
	hw_brk.len = DABR_MAX_LEN;
	hw_brk.hw_len = DABR_MAX_LEN;
	set_bp = (data) && (hw_brk.type & HW_BRK_TYPE_RDWR);
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	bp = thपढ़ो->ptrace_bps[0];
	अगर (!set_bp) अणु
		अगर (bp) अणु
			unरेजिस्टर_hw_अवरोधpoपूर्णांक(bp);
			thपढ़ो->ptrace_bps[0] = शून्य;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (bp) अणु
		attr = bp->attr;
		attr.bp_addr = hw_brk.address;
		attr.bp_len = DABR_MAX_LEN;
		arch_bp_generic_fields(hw_brk.type, &attr.bp_type);

		/* Enable अवरोधpoपूर्णांक */
		attr.disabled = false;

		ret =  modअगरy_user_hw_अवरोधpoपूर्णांक(bp, &attr);
		अगर (ret)
			वापस ret;

		thपढ़ो->ptrace_bps[0] = bp;
		thपढ़ो->hw_brk[0] = hw_brk;
		वापस 0;
	पूर्ण

	/* Create a new अवरोधpoपूर्णांक request अगर one करोesn't exist alपढ़ोy */
	hw_अवरोधpoपूर्णांक_init(&attr);
	attr.bp_addr = hw_brk.address;
	attr.bp_len = DABR_MAX_LEN;
	arch_bp_generic_fields(hw_brk.type,
			       &attr.bp_type);

	thपढ़ो->ptrace_bps[0] = bp = रेजिस्टर_user_hw_अवरोधpoपूर्णांक(&attr,
					       ptrace_triggered, शून्य, task);
	अगर (IS_ERR(bp)) अणु
		thपढ़ो->ptrace_bps[0] = शून्य;
		वापस PTR_ERR(bp);
	पूर्ण

#अन्यथा /* !CONFIG_HAVE_HW_BREAKPOINT */
	अगर (set_bp && (!ppc_अवरोधpoपूर्णांक_available()))
		वापस -ENODEV;
#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */
	task->thपढ़ो.hw_brk[0] = hw_brk;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
अटल पूर्णांक find_empty_ptrace_bp(काष्ठा thपढ़ो_काष्ठा *thपढ़ो)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (!thपढ़ो->ptrace_bps[i])
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक find_empty_hw_brk(काष्ठा thपढ़ो_काष्ठा *thपढ़ो)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (!thपढ़ो->hw_brk[i].address)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

दीर्घ ppc_set_hwdebug(काष्ठा task_काष्ठा *child, काष्ठा ppc_hw_अवरोधpoपूर्णांक *bp_info)
अणु
	पूर्णांक i;
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	पूर्णांक len = 0;
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो = &child->thपढ़ो;
	काष्ठा perf_event *bp;
	काष्ठा perf_event_attr attr;
#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */
	काष्ठा arch_hw_अवरोधpoपूर्णांक brk;

	अगर (bp_info->version != 1)
		वापस -ENOTSUPP;
	/*
	 * We only support one data अवरोधpoपूर्णांक
	 */
	अगर ((bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_RW) == 0 ||
	    (bp_info->trigger_type & ~PPC_BREAKPOINT_TRIGGER_RW) != 0 ||
	    bp_info->condition_mode != PPC_BREAKPOINT_CONDITION_NONE)
		वापस -EINVAL;

	अगर ((अचिन्हित दीर्घ)bp_info->addr >= TASK_SIZE)
		वापस -EIO;

	brk.address = ALIGN_DOWN(bp_info->addr, HW_BREAKPOINT_SIZE);
	brk.type = HW_BRK_TYPE_TRANSLATE | HW_BRK_TYPE_PRIV_ALL;
	brk.len = DABR_MAX_LEN;
	brk.hw_len = DABR_MAX_LEN;
	अगर (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_READ)
		brk.type |= HW_BRK_TYPE_READ;
	अगर (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_WRITE)
		brk.type |= HW_BRK_TYPE_WRITE;
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	अगर (bp_info->addr_mode == PPC_BREAKPOINT_MODE_RANGE_INCLUSIVE)
		len = bp_info->addr2 - bp_info->addr;
	अन्यथा अगर (bp_info->addr_mode == PPC_BREAKPOINT_MODE_EXACT)
		len = 1;
	अन्यथा
		वापस -EINVAL;

	i = find_empty_ptrace_bp(thपढ़ो);
	अगर (i < 0)
		वापस -ENOSPC;

	/* Create a new अवरोधpoपूर्णांक request अगर one करोesn't exist alपढ़ोy */
	hw_अवरोधpoपूर्णांक_init(&attr);
	attr.bp_addr = (अचिन्हित दीर्घ)bp_info->addr;
	attr.bp_len = len;
	arch_bp_generic_fields(brk.type, &attr.bp_type);

	bp = रेजिस्टर_user_hw_अवरोधpoपूर्णांक(&attr, ptrace_triggered, शून्य, child);
	thपढ़ो->ptrace_bps[i] = bp;
	अगर (IS_ERR(bp)) अणु
		thपढ़ो->ptrace_bps[i] = शून्य;
		वापस PTR_ERR(bp);
	पूर्ण

	वापस i + 1;
#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */

	अगर (bp_info->addr_mode != PPC_BREAKPOINT_MODE_EXACT)
		वापस -EINVAL;

	i = find_empty_hw_brk(&child->thपढ़ो);
	अगर (i < 0)
		वापस -ENOSPC;

	अगर (!ppc_अवरोधpoपूर्णांक_available())
		वापस -ENODEV;

	child->thपढ़ो.hw_brk[i] = brk;

	वापस i + 1;
पूर्ण

दीर्घ ppc_del_hwdebug(काष्ठा task_काष्ठा *child, दीर्घ data)
अणु
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	पूर्णांक ret = 0;
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो = &child->thपढ़ो;
	काष्ठा perf_event *bp;
#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */
	अगर (data < 1 || data > nr_wp_slots())
		वापस -EINVAL;

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	bp = thपढ़ो->ptrace_bps[data - 1];
	अगर (bp) अणु
		unरेजिस्टर_hw_अवरोधpoपूर्णांक(bp);
		thपढ़ो->ptrace_bps[data - 1] = शून्य;
	पूर्ण अन्यथा अणु
		ret = -ENOENT;
	पूर्ण
	वापस ret;
#अन्यथा /* CONFIG_HAVE_HW_BREAKPOINT */
	अगर (!(child->thपढ़ो.hw_brk[data - 1].flags & HW_BRK_FLAG_DISABLED) &&
	    child->thपढ़ो.hw_brk[data - 1].address == 0)
		वापस -ENOENT;

	child->thपढ़ो.hw_brk[data - 1].address = 0;
	child->thपढ़ो.hw_brk[data - 1].type = 0;
	child->thपढ़ो.hw_brk[data - 1].flags = 0;
#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */

	वापस 0;
पूर्ण
