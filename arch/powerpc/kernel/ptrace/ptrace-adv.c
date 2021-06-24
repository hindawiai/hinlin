<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/regset.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>

#समावेश "ptrace-decl.h"

व्योम user_enable_single_step(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pt_regs *regs = task->thपढ़ो.regs;

	अगर (regs != शून्य) अणु
		task->thपढ़ो.debug.dbcr0 &= ~DBCR0_BT;
		task->thपढ़ो.debug.dbcr0 |= DBCR0_IDM | DBCR0_IC;
		regs->msr |= MSR_DE;
	पूर्ण
	set_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP);
पूर्ण

व्योम user_enable_block_step(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pt_regs *regs = task->thपढ़ो.regs;

	अगर (regs != शून्य) अणु
		task->thपढ़ो.debug.dbcr0 &= ~DBCR0_IC;
		task->thपढ़ो.debug.dbcr0 = DBCR0_IDM | DBCR0_BT;
		regs->msr |= MSR_DE;
	पूर्ण
	set_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP);
पूर्ण

व्योम user_disable_single_step(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pt_regs *regs = task->thपढ़ो.regs;

	अगर (regs != शून्य) अणु
		/*
		 * The logic to disable single stepping should be as
		 * simple as turning off the Inकाष्ठाion Complete flag.
		 * And, after करोing so, अगर all debug flags are off, turn
		 * off DBCR0(IDM) and MSR(DE) .... Torez
		 */
		task->thपढ़ो.debug.dbcr0 &= ~(DBCR0_IC | DBCR0_BT);
		/*
		 * Test to see अगर any of the DBCR_ACTIVE_EVENTS bits are set.
		 */
		अगर (!DBCR_ACTIVE_EVENTS(task->thपढ़ो.debug.dbcr0,
					task->thपढ़ो.debug.dbcr1)) अणु
			/*
			 * All debug events were off.....
			 */
			task->thपढ़ो.debug.dbcr0 &= ~DBCR0_IDM;
			regs->msr &= ~MSR_DE;
		पूर्ण
	पूर्ण
	clear_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP);
पूर्ण

व्योम ppc_gethwdinfo(काष्ठा ppc_debug_info *dbginfo)
अणु
	dbginfo->version = 1;
	dbginfo->num_inकाष्ठाion_bps = CONFIG_PPC_ADV_DEBUG_IACS;
	dbginfo->num_data_bps = CONFIG_PPC_ADV_DEBUG_DACS;
	dbginfo->num_condition_regs = CONFIG_PPC_ADV_DEBUG_DVCS;
	dbginfo->data_bp_alignment = 4;
	dbginfo->माप_condition = 4;
	dbginfo->features = PPC_DEBUG_FEATURE_INSN_BP_RANGE |
			    PPC_DEBUG_FEATURE_INSN_BP_MASK;
	अगर (IS_ENABLED(CONFIG_PPC_ADV_DEBUG_DAC_RANGE))
		dbginfo->features |= PPC_DEBUG_FEATURE_DATA_BP_RANGE |
				     PPC_DEBUG_FEATURE_DATA_BP_MASK;
पूर्ण

पूर्णांक ptrace_get_debugreg(काष्ठा task_काष्ठा *child, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ __user *datalp)
अणु
	/* We only support one DABR and no IABRS at the moment */
	अगर (addr > 0)
		वापस -EINVAL;
	वापस put_user(child->thपढ़ो.debug.dac1, datalp);
पूर्ण

पूर्णांक ptrace_set_debugreg(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	पूर्णांक ret;
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो = &task->thपढ़ो;
	काष्ठा perf_event *bp;
	काष्ठा perf_event_attr attr;
#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */

	/* For ppc64 we support one DABR and no IABR's at the moment (ppc64).
	 *  For embedded processors we support one DAC and no IAC's at the
	 *  moment.
	 */
	अगर (addr > 0)
		वापस -EINVAL;

	/* The bottom 3 bits in dabr are flags */
	अगर ((data & ~0x7UL) >= TASK_SIZE)
		वापस -EIO;

	/* As described above, it was assumed 3 bits were passed with the data
	 *  address, but we will assume only the mode bits will be passed
	 *  as to not cause alignment restrictions क्रम DAC-based processors.
	 */

	/* DAC's hold the whole address without any mode flags */
	task->thपढ़ो.debug.dac1 = data & ~0x3UL;

	अगर (task->thपढ़ो.debug.dac1 == 0) अणु
		dbcr_dac(task) &= ~(DBCR_DAC1R | DBCR_DAC1W);
		अगर (!DBCR_ACTIVE_EVENTS(task->thपढ़ो.debug.dbcr0,
					task->thपढ़ो.debug.dbcr1)) अणु
			task->thपढ़ो.regs->msr &= ~MSR_DE;
			task->thपढ़ो.debug.dbcr0 &= ~DBCR0_IDM;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Read or Write bits must be set */

	अगर (!(data & 0x3UL))
		वापस -EINVAL;

	/* Set the Internal Debugging flag (IDM bit 1) क्रम the DBCR0 रेजिस्टर */
	task->thपढ़ो.debug.dbcr0 |= DBCR0_IDM;

	/* Check क्रम ग_लिखो and पढ़ो flags and set DBCR0 accordingly */
	dbcr_dac(task) &= ~(DBCR_DAC1R | DBCR_DAC1W);
	अगर (data & 0x1UL)
		dbcr_dac(task) |= DBCR_DAC1R;
	अगर (data & 0x2UL)
		dbcr_dac(task) |= DBCR_DAC1W;
	task->thपढ़ो.regs->msr |= MSR_DE;
	वापस 0;
पूर्ण

अटल दीर्घ set_inकाष्ठाion_bp(काष्ठा task_काष्ठा *child,
			       काष्ठा ppc_hw_अवरोधpoपूर्णांक *bp_info)
अणु
	पूर्णांक slot;
	पूर्णांक slot1_in_use = ((child->thपढ़ो.debug.dbcr0 & DBCR0_IAC1) != 0);
	पूर्णांक slot2_in_use = ((child->thपढ़ो.debug.dbcr0 & DBCR0_IAC2) != 0);
	पूर्णांक slot3_in_use = ((child->thपढ़ो.debug.dbcr0 & DBCR0_IAC3) != 0);
	पूर्णांक slot4_in_use = ((child->thपढ़ो.debug.dbcr0 & DBCR0_IAC4) != 0);

	अगर (dbcr_iac_range(child) & DBCR_IAC12MODE)
		slot2_in_use = 1;
	अगर (dbcr_iac_range(child) & DBCR_IAC34MODE)
		slot4_in_use = 1;

	अगर (bp_info->addr >= TASK_SIZE)
		वापस -EIO;

	अगर (bp_info->addr_mode != PPC_BREAKPOINT_MODE_EXACT) अणु
		/* Make sure range is valid. */
		अगर (bp_info->addr2 >= TASK_SIZE)
			वापस -EIO;

		/* We need a pair of IAC regsisters */
		अगर (!slot1_in_use && !slot2_in_use) अणु
			slot = 1;
			child->thपढ़ो.debug.iac1 = bp_info->addr;
			child->thपढ़ो.debug.iac2 = bp_info->addr2;
			child->thपढ़ो.debug.dbcr0 |= DBCR0_IAC1;
			अगर (bp_info->addr_mode ==
					PPC_BREAKPOINT_MODE_RANGE_EXCLUSIVE)
				dbcr_iac_range(child) |= DBCR_IAC12X;
			अन्यथा
				dbcr_iac_range(child) |= DBCR_IAC12I;
#अगर CONFIG_PPC_ADV_DEBUG_IACS > 2
		पूर्ण अन्यथा अगर ((!slot3_in_use) && (!slot4_in_use)) अणु
			slot = 3;
			child->thपढ़ो.debug.iac3 = bp_info->addr;
			child->thपढ़ो.debug.iac4 = bp_info->addr2;
			child->thपढ़ो.debug.dbcr0 |= DBCR0_IAC3;
			अगर (bp_info->addr_mode ==
					PPC_BREAKPOINT_MODE_RANGE_EXCLUSIVE)
				dbcr_iac_range(child) |= DBCR_IAC34X;
			अन्यथा
				dbcr_iac_range(child) |= DBCR_IAC34I;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			वापस -ENOSPC;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We only need one.  If possible leave a pair मुक्त in
		 * हाल a range is needed later
		 */
		अगर (!slot1_in_use) अणु
			/*
			 * Don't use iac1 अगर iac1-iac2 are मुक्त and either
			 * iac3 or iac4 (but not both) are मुक्त
			 */
			अगर (slot2_in_use || slot3_in_use == slot4_in_use) अणु
				slot = 1;
				child->thपढ़ो.debug.iac1 = bp_info->addr;
				child->thपढ़ो.debug.dbcr0 |= DBCR0_IAC1;
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (!slot2_in_use) अणु
			slot = 2;
			child->thपढ़ो.debug.iac2 = bp_info->addr;
			child->thपढ़ो.debug.dbcr0 |= DBCR0_IAC2;
#अगर CONFIG_PPC_ADV_DEBUG_IACS > 2
		पूर्ण अन्यथा अगर (!slot3_in_use) अणु
			slot = 3;
			child->thपढ़ो.debug.iac3 = bp_info->addr;
			child->thपढ़ो.debug.dbcr0 |= DBCR0_IAC3;
		पूर्ण अन्यथा अगर (!slot4_in_use) अणु
			slot = 4;
			child->thपढ़ो.debug.iac4 = bp_info->addr;
			child->thपढ़ो.debug.dbcr0 |= DBCR0_IAC4;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			वापस -ENOSPC;
		पूर्ण
	पूर्ण
out:
	child->thपढ़ो.debug.dbcr0 |= DBCR0_IDM;
	child->thपढ़ो.regs->msr |= MSR_DE;

	वापस slot;
पूर्ण

अटल पूर्णांक del_inकाष्ठाion_bp(काष्ठा task_काष्ठा *child, पूर्णांक slot)
अणु
	चयन (slot) अणु
	हाल 1:
		अगर ((child->thपढ़ो.debug.dbcr0 & DBCR0_IAC1) == 0)
			वापस -ENOENT;

		अगर (dbcr_iac_range(child) & DBCR_IAC12MODE) अणु
			/* address range - clear slots 1 & 2 */
			child->thपढ़ो.debug.iac2 = 0;
			dbcr_iac_range(child) &= ~DBCR_IAC12MODE;
		पूर्ण
		child->thपढ़ो.debug.iac1 = 0;
		child->thपढ़ो.debug.dbcr0 &= ~DBCR0_IAC1;
		अवरोध;
	हाल 2:
		अगर ((child->thपढ़ो.debug.dbcr0 & DBCR0_IAC2) == 0)
			वापस -ENOENT;

		अगर (dbcr_iac_range(child) & DBCR_IAC12MODE)
			/* used in a range */
			वापस -EINVAL;
		child->thपढ़ो.debug.iac2 = 0;
		child->thपढ़ो.debug.dbcr0 &= ~DBCR0_IAC2;
		अवरोध;
#अगर CONFIG_PPC_ADV_DEBUG_IACS > 2
	हाल 3:
		अगर ((child->thपढ़ो.debug.dbcr0 & DBCR0_IAC3) == 0)
			वापस -ENOENT;

		अगर (dbcr_iac_range(child) & DBCR_IAC34MODE) अणु
			/* address range - clear slots 3 & 4 */
			child->thपढ़ो.debug.iac4 = 0;
			dbcr_iac_range(child) &= ~DBCR_IAC34MODE;
		पूर्ण
		child->thपढ़ो.debug.iac3 = 0;
		child->thपढ़ो.debug.dbcr0 &= ~DBCR0_IAC3;
		अवरोध;
	हाल 4:
		अगर ((child->thपढ़ो.debug.dbcr0 & DBCR0_IAC4) == 0)
			वापस -ENOENT;

		अगर (dbcr_iac_range(child) & DBCR_IAC34MODE)
			/* Used in a range */
			वापस -EINVAL;
		child->thपढ़ो.debug.iac4 = 0;
		child->thपढ़ो.debug.dbcr0 &= ~DBCR0_IAC4;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक set_dac(काष्ठा task_काष्ठा *child, काष्ठा ppc_hw_अवरोधpoपूर्णांक *bp_info)
अणु
	पूर्णांक byte_enable =
		(bp_info->condition_mode >> PPC_BREAKPOINT_CONDITION_BE_SHIFT)
		& 0xf;
	पूर्णांक condition_mode =
		bp_info->condition_mode & PPC_BREAKPOINT_CONDITION_MODE;
	पूर्णांक slot;

	अगर (byte_enable && condition_mode == 0)
		वापस -EINVAL;

	अगर (bp_info->addr >= TASK_SIZE)
		वापस -EIO;

	अगर ((dbcr_dac(child) & (DBCR_DAC1R | DBCR_DAC1W)) == 0) अणु
		slot = 1;
		अगर (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_READ)
			dbcr_dac(child) |= DBCR_DAC1R;
		अगर (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_WRITE)
			dbcr_dac(child) |= DBCR_DAC1W;
		child->thपढ़ो.debug.dac1 = (अचिन्हित दीर्घ)bp_info->addr;
#अगर CONFIG_PPC_ADV_DEBUG_DVCS > 0
		अगर (byte_enable) अणु
			child->thपढ़ो.debug.dvc1 =
				(अचिन्हित दीर्घ)bp_info->condition_value;
			child->thपढ़ो.debug.dbcr2 |=
				((byte_enable << DBCR2_DVC1BE_SHIFT) |
				 (condition_mode << DBCR2_DVC1M_SHIFT));
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_DAC_RANGE
	पूर्ण अन्यथा अगर (child->thपढ़ो.debug.dbcr2 & DBCR2_DAC12MODE) अणु
		/* Both dac1 and dac2 are part of a range */
		वापस -ENOSPC;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर ((dbcr_dac(child) & (DBCR_DAC2R | DBCR_DAC2W)) == 0) अणु
		slot = 2;
		अगर (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_READ)
			dbcr_dac(child) |= DBCR_DAC2R;
		अगर (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_WRITE)
			dbcr_dac(child) |= DBCR_DAC2W;
		child->thपढ़ो.debug.dac2 = (अचिन्हित दीर्घ)bp_info->addr;
#अगर CONFIG_PPC_ADV_DEBUG_DVCS > 0
		अगर (byte_enable) अणु
			child->thपढ़ो.debug.dvc2 =
				(अचिन्हित दीर्घ)bp_info->condition_value;
			child->thपढ़ो.debug.dbcr2 |=
				((byte_enable << DBCR2_DVC2BE_SHIFT) |
				 (condition_mode << DBCR2_DVC2M_SHIFT));
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		वापस -ENOSPC;
	पूर्ण
	child->thपढ़ो.debug.dbcr0 |= DBCR0_IDM;
	child->thपढ़ो.regs->msr |= MSR_DE;

	वापस slot + 4;
पूर्ण

अटल पूर्णांक del_dac(काष्ठा task_काष्ठा *child, पूर्णांक slot)
अणु
	अगर (slot == 1) अणु
		अगर ((dbcr_dac(child) & (DBCR_DAC1R | DBCR_DAC1W)) == 0)
			वापस -ENOENT;

		child->thपढ़ो.debug.dac1 = 0;
		dbcr_dac(child) &= ~(DBCR_DAC1R | DBCR_DAC1W);
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_DAC_RANGE
		अगर (child->thपढ़ो.debug.dbcr2 & DBCR2_DAC12MODE) अणु
			child->thपढ़ो.debug.dac2 = 0;
			child->thपढ़ो.debug.dbcr2 &= ~DBCR2_DAC12MODE;
		पूर्ण
		child->thपढ़ो.debug.dbcr2 &= ~(DBCR2_DVC1M | DBCR2_DVC1BE);
#पूर्ण_अगर
#अगर CONFIG_PPC_ADV_DEBUG_DVCS > 0
		child->thपढ़ो.debug.dvc1 = 0;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (slot == 2) अणु
		अगर ((dbcr_dac(child) & (DBCR_DAC2R | DBCR_DAC2W)) == 0)
			वापस -ENOENT;

#अगर_घोषित CONFIG_PPC_ADV_DEBUG_DAC_RANGE
		अगर (child->thपढ़ो.debug.dbcr2 & DBCR2_DAC12MODE)
			/* Part of a range */
			वापस -EINVAL;
		child->thपढ़ो.debug.dbcr2 &= ~(DBCR2_DVC2M | DBCR2_DVC2BE);
#पूर्ण_अगर
#अगर CONFIG_PPC_ADV_DEBUG_DVCS > 0
		child->thपढ़ो.debug.dvc2 = 0;
#पूर्ण_अगर
		child->thपढ़ो.debug.dac2 = 0;
		dbcr_dac(child) &= ~(DBCR_DAC2R | DBCR_DAC2W);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC_ADV_DEBUG_DAC_RANGE
अटल पूर्णांक set_dac_range(काष्ठा task_काष्ठा *child,
			 काष्ठा ppc_hw_अवरोधpoपूर्णांक *bp_info)
अणु
	पूर्णांक mode = bp_info->addr_mode & PPC_BREAKPOINT_MODE_MASK;

	/* We करोn't allow range watchpoपूर्णांकs to be used with DVC */
	अगर (bp_info->condition_mode)
		वापस -EINVAL;

	/*
	 * Best efक्रमt to verअगरy the address range.  The user/supervisor bits
	 * prevent trapping in kernel space, but let's fail on an obvious bad
	 * range.  The simple test on the mask is not fool-proof, and any
	 * exclusive range will spill over पूर्णांकo kernel space.
	 */
	अगर (bp_info->addr >= TASK_SIZE)
		वापस -EIO;
	अगर (mode == PPC_BREAKPOINT_MODE_MASK) अणु
		/*
		 * dac2 is a biपंचांगask.  Don't allow a mask that makes a
		 * kernel space address from a valid dac1 value
		 */
		अगर (~((अचिन्हित दीर्घ)bp_info->addr2) >= TASK_SIZE)
			वापस -EIO;
	पूर्ण अन्यथा अणु
		/*
		 * For range अवरोधpoपूर्णांकs, addr2 must also be a valid address
		 */
		अगर (bp_info->addr2 >= TASK_SIZE)
			वापस -EIO;
	पूर्ण

	अगर (child->thपढ़ो.debug.dbcr0 &
	    (DBCR0_DAC1R | DBCR0_DAC1W | DBCR0_DAC2R | DBCR0_DAC2W))
		वापस -ENOSPC;

	अगर (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_READ)
		child->thपढ़ो.debug.dbcr0 |= (DBCR0_DAC1R | DBCR0_IDM);
	अगर (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_WRITE)
		child->thपढ़ो.debug.dbcr0 |= (DBCR0_DAC1W | DBCR0_IDM);
	child->thपढ़ो.debug.dac1 = bp_info->addr;
	child->thपढ़ो.debug.dac2 = bp_info->addr2;
	अगर (mode == PPC_BREAKPOINT_MODE_RANGE_INCLUSIVE)
		child->thपढ़ो.debug.dbcr2  |= DBCR2_DAC12M;
	अन्यथा अगर (mode == PPC_BREAKPOINT_MODE_RANGE_EXCLUSIVE)
		child->thपढ़ो.debug.dbcr2  |= DBCR2_DAC12MX;
	अन्यथा	/* PPC_BREAKPOINT_MODE_MASK */
		child->thपढ़ो.debug.dbcr2  |= DBCR2_DAC12MM;
	child->thपढ़ो.regs->msr |= MSR_DE;

	वापस 5;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_ADV_DEBUG_DAC_RANGE */

दीर्घ ppc_set_hwdebug(काष्ठा task_काष्ठा *child, काष्ठा ppc_hw_अवरोधpoपूर्णांक *bp_info)
अणु
	अगर (bp_info->version != 1)
		वापस -ENOTSUPP;
	/*
	 * Check क्रम invalid flags and combinations
	 */
	अगर (bp_info->trigger_type == 0 ||
	    (bp_info->trigger_type & ~(PPC_BREAKPOINT_TRIGGER_EXECUTE |
				       PPC_BREAKPOINT_TRIGGER_RW)) ||
	    (bp_info->addr_mode & ~PPC_BREAKPOINT_MODE_MASK) ||
	    (bp_info->condition_mode &
	     ~(PPC_BREAKPOINT_CONDITION_MODE |
	       PPC_BREAKPOINT_CONDITION_BE_ALL)))
		वापस -EINVAL;
#अगर CONFIG_PPC_ADV_DEBUG_DVCS == 0
	अगर (bp_info->condition_mode != PPC_BREAKPOINT_CONDITION_NONE)
		वापस -EINVAL;
#पूर्ण_अगर

	अगर (bp_info->trigger_type & PPC_BREAKPOINT_TRIGGER_EXECUTE) अणु
		अगर (bp_info->trigger_type != PPC_BREAKPOINT_TRIGGER_EXECUTE ||
		    bp_info->condition_mode != PPC_BREAKPOINT_CONDITION_NONE)
			वापस -EINVAL;
		वापस set_inकाष्ठाion_bp(child, bp_info);
	पूर्ण
	अगर (bp_info->addr_mode == PPC_BREAKPOINT_MODE_EXACT)
		वापस set_dac(child, bp_info);

#अगर_घोषित CONFIG_PPC_ADV_DEBUG_DAC_RANGE
	वापस set_dac_range(child, bp_info);
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

दीर्घ ppc_del_hwdebug(काष्ठा task_काष्ठा *child, दीर्घ data)
अणु
	पूर्णांक rc;

	अगर (data <= 4)
		rc = del_inकाष्ठाion_bp(child, (पूर्णांक)data);
	अन्यथा
		rc = del_dac(child, (पूर्णांक)data - 4);

	अगर (!rc) अणु
		अगर (!DBCR_ACTIVE_EVENTS(child->thपढ़ो.debug.dbcr0,
					child->thपढ़ो.debug.dbcr1)) अणु
			child->thपढ़ो.debug.dbcr0 &= ~DBCR0_IDM;
			child->thपढ़ो.regs->msr &= ~MSR_DE;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण
