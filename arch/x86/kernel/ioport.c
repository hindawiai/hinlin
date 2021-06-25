<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This contains the io-permission biपंचांगap code - written by obz, with changes
 * by Linus. 32/64 bits code unअगरication by Miguel Botथकn.
 */
#समावेश <linux/capability.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/io_biपंचांगap.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/syscalls.h>

#अगर_घोषित CONFIG_X86_IOPL_IOPERM

अटल atomic64_t io_biपंचांगap_sequence;

व्योम io_biपंचांगap_share(काष्ठा task_काष्ठा *tsk)
अणु
	/* Can be शून्य when current->thपढ़ो.iopl_emul == 3 */
	अगर (current->thपढ़ो.io_biपंचांगap) अणु
		/*
		 * Take a refcount on current's biपंचांगap. It can be used by
		 * both tasks as दीर्घ as none of them changes the biपंचांगap.
		 */
		refcount_inc(&current->thपढ़ो.io_biपंचांगap->refcnt);
		tsk->thपढ़ो.io_biपंचांगap = current->thपढ़ो.io_biपंचांगap;
	पूर्ण
	set_tsk_thपढ़ो_flag(tsk, TIF_IO_BITMAP);
पूर्ण

अटल व्योम task_update_io_biपंचांगap(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &tsk->thपढ़ो;

	अगर (t->iopl_emul == 3 || t->io_biपंचांगap) अणु
		/* TSS update is handled on निकास to user space */
		set_tsk_thपढ़ो_flag(tsk, TIF_IO_BITMAP);
	पूर्ण अन्यथा अणु
		clear_tsk_thपढ़ो_flag(tsk, TIF_IO_BITMAP);
		/* Invalidate TSS */
		preempt_disable();
		tss_update_io_biपंचांगap();
		preempt_enable();
	पूर्ण
पूर्ण

व्योम io_biपंचांगap_निकास(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा io_biपंचांगap *iobm = tsk->thपढ़ो.io_biपंचांगap;

	tsk->thपढ़ो.io_biपंचांगap = शून्य;
	task_update_io_biपंचांगap(tsk);
	अगर (iobm && refcount_dec_and_test(&iobm->refcnt))
		kमुक्त(iobm);
पूर्ण

/*
 * This changes the io permissions biपंचांगap in the current task.
 */
दीर्घ ksys_ioperm(अचिन्हित दीर्घ from, अचिन्हित दीर्घ num, पूर्णांक turn_on)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &current->thपढ़ो;
	अचिन्हित पूर्णांक i, max_दीर्घ;
	काष्ठा io_biपंचांगap *iobm;

	अगर ((from + num <= from) || (from + num > IO_BITMAP_BITS))
		वापस -EINVAL;
	अगर (turn_on && (!capable(CAP_SYS_RAWIO) ||
			security_locked_करोwn(LOCKDOWN_IOPORT)))
		वापस -EPERM;

	/*
	 * If it's the first ioperm() call in this thread's lअगरeसमय, set the
	 * IO biपंचांगap up. ioperm() is much less timing critical than clone(),
	 * this is why we delay this operation until now:
	 */
	iobm = t->io_biपंचांगap;
	अगर (!iobm) अणु
		/* No poपूर्णांक to allocate a biपंचांगap just to clear permissions */
		अगर (!turn_on)
			वापस 0;
		iobm = kदो_स्मृति(माप(*iobm), GFP_KERNEL);
		अगर (!iobm)
			वापस -ENOMEM;

		स_रखो(iobm->biपंचांगap, 0xff, माप(iobm->biपंचांगap));
		refcount_set(&iobm->refcnt, 1);
	पूर्ण

	/*
	 * If the biपंचांगap is not shared, then nothing can take a refcount as
	 * current can obviously not विभाजन at the same समय. If it's shared
	 * duplicate it and drop the refcount on the original one.
	 */
	अगर (refcount_पढ़ो(&iobm->refcnt) > 1) अणु
		iobm = kmemdup(iobm, माप(*iobm), GFP_KERNEL);
		अगर (!iobm)
			वापस -ENOMEM;
		refcount_set(&iobm->refcnt, 1);
		io_biपंचांगap_निकास(current);
	पूर्ण

	/*
	 * Store the biपंचांगap poपूर्णांकer (might be the same अगर the task alपढ़ोy
	 * head one). Must be करोne here so मुक्तing the biपंचांगap when all
	 * permissions are dropped has the poपूर्णांकer set up.
	 */
	t->io_biपंचांगap = iobm;
	/* Mark it active क्रम context चयनing and निकास to user mode */
	set_thपढ़ो_flag(TIF_IO_BITMAP);

	/*
	 * Update the tasks biपंचांगap. The update of the TSS biपंचांगap happens on
	 * निकास to user mode. So this needs no protection.
	 */
	अगर (turn_on)
		biपंचांगap_clear(iobm->biपंचांगap, from, num);
	अन्यथा
		biपंचांगap_set(iobm->biपंचांगap, from, num);

	/*
	 * Search क्रम a (possibly new) maximum. This is simple and stupid,
	 * to keep it obviously correct:
	 */
	max_दीर्घ = अच_पूर्णांक_उच्च;
	क्रम (i = 0; i < IO_BITMAP_LONGS; i++) अणु
		अगर (iobm->biपंचांगap[i] != ~0UL)
			max_दीर्घ = i;
	पूर्ण
	/* All permissions dropped? */
	अगर (max_दीर्घ == अच_पूर्णांक_उच्च) अणु
		io_biपंचांगap_निकास(current);
		वापस 0;
	पूर्ण

	iobm->max = (max_दीर्घ + 1) * माप(अचिन्हित दीर्घ);

	/*
	 * Update the sequence number to क्रमce a TSS update on वापस to
	 * user mode.
	 */
	iobm->sequence = atomic64_add_वापस(1, &io_biपंचांगap_sequence);

	वापस 0;
पूर्ण

SYSCALL_DEFINE3(ioperm, अचिन्हित दीर्घ, from, अचिन्हित दीर्घ, num, पूर्णांक, turn_on)
अणु
	वापस ksys_ioperm(from, num, turn_on);
पूर्ण

/*
 * The sys_iopl functionality depends on the level argument, which अगर
 * granted क्रम the task is used to enable access to all 65536 I/O ports.
 *
 * This करोes not use the IOPL mechanism provided by the CPU as that would
 * also allow the user space task to use the CLI/STI inकाष्ठाions.
 *
 * Disabling पूर्णांकerrupts in a user space task is dangerous as it might lock
 * up the machine and the semantics vs. syscalls and exceptions is
 * undefined.
 *
 * Setting IOPL to level 0-2 is disabling I/O permissions. Level 3
 * 3 enables them.
 *
 * IOPL is strictly per thपढ़ो and inherited on विभाजन.
 */
SYSCALL_DEFINE1(iopl, अचिन्हित पूर्णांक, level)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &current->thपढ़ो;
	अचिन्हित पूर्णांक old;

	अगर (level > 3)
		वापस -EINVAL;

	old = t->iopl_emul;

	/* No poपूर्णांक in going further अगर nothing changes */
	अगर (level == old)
		वापस 0;

	/* Trying to gain more privileges? */
	अगर (level > old) अणु
		अगर (!capable(CAP_SYS_RAWIO) ||
		    security_locked_करोwn(LOCKDOWN_IOPORT))
			वापस -EPERM;
	पूर्ण

	t->iopl_emul = level;
	task_update_io_biपंचांगap(current);

	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_X86_IOPL_IOPERM */

दीर्घ ksys_ioperm(अचिन्हित दीर्घ from, अचिन्हित दीर्घ num, पूर्णांक turn_on)
अणु
	वापस -ENOSYS;
पूर्ण
SYSCALL_DEFINE3(ioperm, अचिन्हित दीर्घ, from, अचिन्हित दीर्घ, num, पूर्णांक, turn_on)
अणु
	वापस -ENOSYS;
पूर्ण

SYSCALL_DEFINE1(iopl, अचिन्हित पूर्णांक, level)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर
