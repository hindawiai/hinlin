<शैली गुरु>
/*
 * Xtensa hardware अवरोधpoपूर्णांकs/watchpoपूर्णांकs handling functions
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2016 Cadence Design Systems Inc.
 */

#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/log2.h>
#समावेश <linux/percpu.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/core.h>

/* Breakpoपूर्णांक currently in use क्रम each IBREAKA. */
अटल DEFINE_PER_CPU(काष्ठा perf_event *, bp_on_reg[XCHAL_NUM_IBREAK]);

/* Watchpoपूर्णांक currently in use क्रम each DBREAKA. */
अटल DEFINE_PER_CPU(काष्ठा perf_event *, wp_on_reg[XCHAL_NUM_DBREAK]);

पूर्णांक hw_अवरोधpoपूर्णांक_slots(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल TYPE_INST:
		वापस XCHAL_NUM_IBREAK;
	हाल TYPE_DATA:
		वापस XCHAL_NUM_DBREAK;
	शेष:
		pr_warn("unknown slot type: %d\n", type);
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक arch_check_bp_in_kernelspace(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ va;

	va = hw->address;
	len = hw->len;

	वापस (va >= TASK_SIZE) && ((va + len - 1) >= TASK_SIZE);
पूर्ण

/*
 * Conकाष्ठा an arch_hw_अवरोधpoपूर्णांक from a perf_event.
 */
पूर्णांक hw_अवरोधpoपूर्णांक_arch_parse(काष्ठा perf_event *bp,
			     स्थिर काष्ठा perf_event_attr *attr,
			     काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	/* Type */
	चयन (attr->bp_type) अणु
	हाल HW_BREAKPOINT_X:
		hw->type = XTENSA_BREAKPOINT_EXECUTE;
		अवरोध;
	हाल HW_BREAKPOINT_R:
		hw->type = XTENSA_BREAKPOINT_LOAD;
		अवरोध;
	हाल HW_BREAKPOINT_W:
		hw->type = XTENSA_BREAKPOINT_STORE;
		अवरोध;
	हाल HW_BREAKPOINT_RW:
		hw->type = XTENSA_BREAKPOINT_LOAD | XTENSA_BREAKPOINT_STORE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Len */
	hw->len = attr->bp_len;
	अगर (hw->len < 1 || hw->len > 64 || !is_घातer_of_2(hw->len))
		वापस -EINVAL;

	/* Address */
	hw->address = attr->bp_addr;
	अगर (hw->address & (hw->len - 1))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक hw_अवरोधpoपूर्णांक_exceptions_notअगरy(काष्ठा notअगरier_block *unused,
				    अचिन्हित दीर्घ val, व्योम *data)
अणु
	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम xtensa_wsr(अचिन्हित दीर्घ v, u8 sr)
अणु
	/* We करोn't have indexed wsr and creating inकाष्ठाion dynamically
	 * करोesn't seem worth it given how small XCHAL_NUM_IBREAK and
	 * XCHAL_NUM_DBREAK are. Thus the चयन. In हाल build अवरोधs here
	 * the चयन below needs to be extended.
	 */
	BUILD_BUG_ON(XCHAL_NUM_IBREAK > 2);
	BUILD_BUG_ON(XCHAL_NUM_DBREAK > 2);

	चयन (sr) अणु
#अगर XCHAL_NUM_IBREAK > 0
	हाल SREG_IBREAKA + 0:
		xtensa_set_sr(v, SREG_IBREAKA + 0);
		अवरोध;
#पूर्ण_अगर
#अगर XCHAL_NUM_IBREAK > 1
	हाल SREG_IBREAKA + 1:
		xtensa_set_sr(v, SREG_IBREAKA + 1);
		अवरोध;
#पूर्ण_अगर

#अगर XCHAL_NUM_DBREAK > 0
	हाल SREG_DBREAKA + 0:
		xtensa_set_sr(v, SREG_DBREAKA + 0);
		अवरोध;
	हाल SREG_DBREAKC + 0:
		xtensa_set_sr(v, SREG_DBREAKC + 0);
		अवरोध;
#पूर्ण_अगर
#अगर XCHAL_NUM_DBREAK > 1
	हाल SREG_DBREAKA + 1:
		xtensa_set_sr(v, SREG_DBREAKA + 1);
		अवरोध;

	हाल SREG_DBREAKC + 1:
		xtensa_set_sr(v, SREG_DBREAKC + 1);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_slot(काष्ठा perf_event **slot, माप_प्रकार n,
		      काष्ठा perf_event *bp)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < n; ++i) अणु
		अगर (!slot[i]) अणु
			slot[i] = bp;
			वापस i;
		पूर्ण
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल व्योम set_iअवरोध_regs(पूर्णांक reg, काष्ठा perf_event *bp)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(bp);
	अचिन्हित दीर्घ iअवरोधenable;

	xtensa_wsr(info->address, SREG_IBREAKA + reg);
	iअवरोधenable = xtensa_get_sr(SREG_IBREAKENABLE);
	xtensa_set_sr(iअवरोधenable | (1 << reg), SREG_IBREAKENABLE);
पूर्ण

अटल व्योम set_dअवरोध_regs(पूर्णांक reg, काष्ठा perf_event *bp)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(bp);
	अचिन्हित दीर्घ dअवरोधc = DBREAKC_MASK_MASK & -info->len;

	अगर (info->type & XTENSA_BREAKPOINT_LOAD)
		dअवरोधc |= DBREAKC_LOAD_MASK;
	अगर (info->type & XTENSA_BREAKPOINT_STORE)
		dअवरोधc |= DBREAKC_STOR_MASK;

	xtensa_wsr(info->address, SREG_DBREAKA + reg);
	xtensa_wsr(dअवरोधc, SREG_DBREAKC + reg);
पूर्ण

पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	पूर्णांक i;

	अगर (counter_arch_bp(bp)->type == XTENSA_BREAKPOINT_EXECUTE) अणु
		/* Breakpoपूर्णांक */
		i = alloc_slot(this_cpu_ptr(bp_on_reg), XCHAL_NUM_IBREAK, bp);
		अगर (i < 0)
			वापस i;
		set_iअवरोध_regs(i, bp);

	पूर्ण अन्यथा अणु
		/* Watchpoपूर्णांक */
		i = alloc_slot(this_cpu_ptr(wp_on_reg), XCHAL_NUM_DBREAK, bp);
		अगर (i < 0)
			वापस i;
		set_dअवरोध_regs(i, bp);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक मुक्त_slot(काष्ठा perf_event **slot, माप_प्रकार n,
		     काष्ठा perf_event *bp)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < n; ++i) अणु
		अगर (slot[i] == bp) अणु
			slot[i] = शून्य;
			वापस i;
		पूर्ण
	पूर्ण
	वापस -EBUSY;
पूर्ण

व्योम arch_uninstall_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(bp);
	पूर्णांक i;

	अगर (info->type == XTENSA_BREAKPOINT_EXECUTE) अणु
		अचिन्हित दीर्घ iअवरोधenable;

		/* Breakpoपूर्णांक */
		i = मुक्त_slot(this_cpu_ptr(bp_on_reg), XCHAL_NUM_IBREAK, bp);
		अगर (i >= 0) अणु
			iअवरोधenable = xtensa_get_sr(SREG_IBREAKENABLE);
			xtensa_set_sr(iअवरोधenable & ~(1 << i),
				      SREG_IBREAKENABLE);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Watchpoपूर्णांक */
		i = मुक्त_slot(this_cpu_ptr(wp_on_reg), XCHAL_NUM_DBREAK, bp);
		अगर (i >= 0)
			xtensa_wsr(0, SREG_DBREAKC + i);
	पूर्ण
पूर्ण

व्योम hw_अवरोधpoपूर्णांक_pmu_पढ़ो(काष्ठा perf_event *bp)
अणु
पूर्ण

व्योम flush_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक i;
	काष्ठा thपढ़ो_काष्ठा *t = &tsk->thपढ़ो;

	क्रम (i = 0; i < XCHAL_NUM_IBREAK; ++i) अणु
		अगर (t->ptrace_bp[i]) अणु
			unरेजिस्टर_hw_अवरोधpoपूर्णांक(t->ptrace_bp[i]);
			t->ptrace_bp[i] = शून्य;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < XCHAL_NUM_DBREAK; ++i) अणु
		अगर (t->ptrace_wp[i]) अणु
			unरेजिस्टर_hw_अवरोधpoपूर्णांक(t->ptrace_wp[i]);
			t->ptrace_wp[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Set ptrace अवरोधpoपूर्णांक poपूर्णांकers to zero क्रम this task.
 * This is required in order to prevent child processes from unरेजिस्टरing
 * अवरोधpoपूर्णांकs held by their parent.
 */
व्योम clear_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk)
अणु
	स_रखो(tsk->thपढ़ो.ptrace_bp, 0, माप(tsk->thपढ़ो.ptrace_bp));
	स_रखो(tsk->thपढ़ो.ptrace_wp, 0, माप(tsk->thपढ़ो.ptrace_wp));
पूर्ण

व्योम restore_dअवरोध(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < XCHAL_NUM_DBREAK; ++i) अणु
		काष्ठा perf_event *bp = this_cpu_ptr(wp_on_reg)[i];

		अगर (bp)
			set_dअवरोध_regs(i, bp);
	पूर्ण
	clear_thपढ़ो_flag(TIF_DB_DISABLED);
पूर्ण

पूर्णांक check_hw_अवरोधpoपूर्णांक(काष्ठा pt_regs *regs)
अणु
	अगर (regs->debugcause & BIT(DEBUGCAUSE_IBREAK_BIT)) अणु
		पूर्णांक i;
		काष्ठा perf_event **bp = this_cpu_ptr(bp_on_reg);

		क्रम (i = 0; i < XCHAL_NUM_IBREAK; ++i) अणु
			अगर (bp[i] && !bp[i]->attr.disabled &&
			    regs->pc == bp[i]->attr.bp_addr)
				perf_bp_event(bp[i], regs);
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अगर (regs->debugcause & BIT(DEBUGCAUSE_DBREAK_BIT)) अणु
		काष्ठा perf_event **bp = this_cpu_ptr(wp_on_reg);
		पूर्णांक dbnum = (regs->debugcause & DEBUGCAUSE_DBNUM_MASK) >>
			DEBUGCAUSE_DBNUM_SHIFT;

		अगर (dbnum < XCHAL_NUM_DBREAK && bp[dbnum]) अणु
			अगर (user_mode(regs)) अणु
				perf_bp_event(bp[dbnum], regs);
			पूर्ण अन्यथा अणु
				set_thपढ़ो_flag(TIF_DB_DISABLED);
				xtensa_wsr(0, SREG_DBREAKC + dbnum);
			पूर्ण
		पूर्ण अन्यथा अणु
			WARN_ONCE(1,
				  "Wrong/unconfigured DBNUM reported in DEBUGCAUSE: %d\n",
				  dbnum);
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण
