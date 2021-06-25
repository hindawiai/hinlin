<शैली गुरु>
/*
 * Created by: Jason Wessel <jason.wessel@windriver.com>
 *
 * Copyright (c) 2009 Wind River Systems, Inc.  All Rights Reserved.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kgdb.h>
#समावेश <linux/kdb.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/export.h>
#समावेश <linux/hardirq.h>
#समावेश "kdb_private.h"
#समावेश "../debug_core.h"

/*
 * KDB पूर्णांकerface to KGDB पूर्णांकernals
 */
get_अक्षर_func kdb_poll_funcs[] = अणु
	dbg_io_get_अक्षर,
	शून्य,
	शून्य,
	शून्य,
	शून्य,
	शून्य,
पूर्ण;
EXPORT_SYMBOL_GPL(kdb_poll_funcs);

पूर्णांक kdb_poll_idx = 1;
EXPORT_SYMBOL_GPL(kdb_poll_idx);

अटल काष्ठा kgdb_state *kdb_ks;

पूर्णांक kdb_common_init_state(काष्ठा kgdb_state *ks)
अणु
	kdb_initial_cpu = atomic_पढ़ो(&kgdb_active);
	kdb_current_task = kgdb_info[ks->cpu].task;
	kdb_current_regs = kgdb_info[ks->cpu].debuggerinfo;
	वापस 0;
पूर्ण

पूर्णांक kdb_common_deinit_state(व्योम)
अणु
	kdb_initial_cpu = -1;
	kdb_current_task = शून्य;
	kdb_current_regs = शून्य;
	वापस 0;
पूर्ण

पूर्णांक kdb_stub(काष्ठा kgdb_state *ks)
अणु
	पूर्णांक error = 0;
	kdb_bp_t *bp;
	अचिन्हित दीर्घ addr = kgdb_arch_pc(ks->ex_vector, ks->linux_regs);
	kdb_reason_t reason = KDB_REASON_OOPS;
	kdb_dbtrap_t db_result = KDB_DB_NOBPT;
	पूर्णांक i;

	kdb_ks = ks;
	अगर (KDB_STATE(REENTRY)) अणु
		reason = KDB_REASON_SWITCH;
		KDB_STATE_CLEAR(REENTRY);
		addr = inकाष्ठाion_poपूर्णांकer(ks->linux_regs);
	पूर्ण
	ks->pass_exception = 0;
	अगर (atomic_पढ़ो(&kgdb_setting_अवरोधpoपूर्णांक))
		reason = KDB_REASON_KEYBOARD;

	अगर (ks->err_code == KDB_REASON_SYSTEM_NMI && ks->signo == SIGTRAP)
		reason = KDB_REASON_SYSTEM_NMI;

	अन्यथा अगर (in_nmi())
		reason = KDB_REASON_NMI;

	क्रम (i = 0, bp = kdb_अवरोधpoपूर्णांकs; i < KDB_MAXBPT; i++, bp++) अणु
		अगर ((bp->bp_enabled) && (bp->bp_addr == addr)) अणु
			reason = KDB_REASON_BREAK;
			db_result = KDB_DB_BPT;
			अगर (addr != inकाष्ठाion_poपूर्णांकer(ks->linux_regs))
				kgdb_arch_set_pc(ks->linux_regs, addr);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (reason == KDB_REASON_BREAK || reason == KDB_REASON_SWITCH) अणु
		क्रम (i = 0, bp = kdb_अवरोधpoपूर्णांकs; i < KDB_MAXBPT; i++, bp++) अणु
			अगर (bp->bp_मुक्त)
				जारी;
			अगर (bp->bp_addr == addr) अणु
				bp->bp_delay = 1;
				bp->bp_delayed = 1;
	/*
	 * SSBPT is set when the kernel debugger must single step a
	 * task in order to re-establish an inकाष्ठाion अवरोधpoपूर्णांक
	 * which uses the inकाष्ठाion replacement mechanism.  It is
	 * cleared by any action that हटाओs the need to single-step
	 * the अवरोधpoपूर्णांक.
	 */
				reason = KDB_REASON_BREAK;
				db_result = KDB_DB_BPT;
				KDB_STATE_SET(SSBPT);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (reason != KDB_REASON_BREAK && ks->ex_vector == 0 &&
		ks->signo == SIGTRAP) अणु
		reason = KDB_REASON_SSTEP;
		db_result = KDB_DB_BPT;
	पूर्ण
	/* Set initial kdb state variables */
	KDB_STATE_CLEAR(KGDB_TRANS);
	kdb_common_init_state(ks);
	/* Remove any अवरोधpoपूर्णांकs as needed by kdb and clear single step */
	kdb_bp_हटाओ();
	KDB_STATE_CLEAR(DOING_SS);
	KDB_STATE_SET(PAGER);
	अगर (ks->err_code == DIE_OOPS || reason == KDB_REASON_OOPS) अणु
		ks->pass_exception = 1;
		KDB_FLAG_SET(CATASTROPHIC);
	पूर्ण
	/* set CATASTROPHIC अगर the प्रणाली contains unresponsive processors */
	क्रम_each_online_cpu(i)
		अगर (!kgdb_info[i].enter_kgdb)
			KDB_FLAG_SET(CATASTROPHIC);
	अगर (KDB_STATE(SSBPT) && reason == KDB_REASON_SSTEP) अणु
		KDB_STATE_CLEAR(SSBPT);
		KDB_STATE_CLEAR(DOING_SS);
	पूर्ण अन्यथा अणु
		/* Start kdb मुख्य loop */
		error = kdb_मुख्य_loop(KDB_REASON_ENTER, reason,
				      ks->err_code, db_result, ks->linux_regs);
	पूर्ण
	/*
	 * Upon निकास from the kdb मुख्य loop setup अवरोध poपूर्णांकs and restart
	 * the प्रणाली based on the requested जारी state
	 */
	kdb_common_deinit_state();
	KDB_STATE_CLEAR(PAGER);
	kdbnearsym_cleanup();
	अगर (error == KDB_CMD_KGDB) अणु
		अगर (KDB_STATE(DOING_KGDB))
			KDB_STATE_CLEAR(DOING_KGDB);
		वापस DBG_PASS_EVENT;
	पूर्ण
	kdb_bp_install(ks->linux_regs);
	/* Set the निकास state to a single step or a जारी */
	अगर (KDB_STATE(DOING_SS))
		gdbstub_state(ks, "s");
	अन्यथा
		gdbstub_state(ks, "c");

	KDB_FLAG_CLEAR(CATASTROPHIC);

	/* Invoke arch specअगरic exception handling prior to प्रणाली resume */
	kgdb_info[ks->cpu].ret_state = gdbstub_state(ks, "e");
	अगर (ks->pass_exception)
		kgdb_info[ks->cpu].ret_state = 1;
	अगर (error == KDB_CMD_CPU) अणु
		KDB_STATE_SET(REENTRY);
		/*
		 * Force clear the single step bit because kdb emulates this
		 * dअगरferently vs the gdbstub
		 */
		kgdb_single_step = 0;
		वापस DBG_SWITCH_CPU_EVENT;
	पूर्ण
	वापस kgdb_info[ks->cpu].ret_state;
पूर्ण

व्योम kdb_gdb_state_pass(अक्षर *buf)
अणु
	gdbstub_state(kdb_ks, buf);
पूर्ण
