<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Virtual cpu समयr based समयr functions.
 *
 *    Copyright IBM Corp. 2004, 2012
 *    Author(s): Jan Glauber <jan.glauber@de.ibm.com>
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयx.h>
#समावेश <linux/types.h>
#समावेश <linux/समय.स>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/vसमयr.h>
#समावेश <यंत्र/vसमय.स>
#समावेश <यंत्र/cpu_mf.h>
#समावेश <यंत्र/smp.h>

#समावेश "entry.h"

अटल व्योम virt_समयr_expire(व्योम);

अटल LIST_HEAD(virt_समयr_list);
अटल DEFINE_SPINLOCK(virt_समयr_lock);
अटल atomic64_t virt_समयr_current;
अटल atomic64_t virt_समयr_elapsed;

DEFINE_PER_CPU(u64, mt_cycles[8]);
अटल DEFINE_PER_CPU(u64, mt_scaling_mult) = अणु 1 पूर्ण;
अटल DEFINE_PER_CPU(u64, mt_scaling_भाग) = अणु 1 पूर्ण;
अटल DEFINE_PER_CPU(u64, mt_scaling_jअगरfies);

अटल अंतरभूत u64 get_vसमयr(व्योम)
अणु
	u64 समयr;

	यंत्र अस्थिर("stpt %0" : "=Q" (समयr));
	वापस समयr;
पूर्ण

अटल अंतरभूत व्योम set_vसमयr(u64 expires)
अणु
	u64 समयr;

	यंत्र अस्थिर(
		"	stpt	%0\n"	/* Store current cpu समयr value */
		"	spt	%1"	/* Set new value imm. afterwards */
		: "=Q" (समयr) : "Q" (expires));
	S390_lowcore.प्रणाली_समयr += S390_lowcore.last_update_समयr - समयr;
	S390_lowcore.last_update_समयr = expires;
पूर्ण

अटल अंतरभूत पूर्णांक virt_समयr_क्रमward(u64 elapsed)
अणु
	BUG_ON(!irqs_disabled());

	अगर (list_empty(&virt_समयr_list))
		वापस 0;
	elapsed = atomic64_add_वापस(elapsed, &virt_समयr_elapsed);
	वापस elapsed >= atomic64_पढ़ो(&virt_समयr_current);
पूर्ण

अटल व्योम update_mt_scaling(व्योम)
अणु
	u64 cycles_new[8], *cycles_old;
	u64 delta, fac, mult, भाग;
	पूर्णांक i;

	stccपंचांग(MT_DIAG, smp_cpu_mtid + 1, cycles_new);
	cycles_old = this_cpu_ptr(mt_cycles);
	fac = 1;
	mult = भाग = 0;
	क्रम (i = 0; i <= smp_cpu_mtid; i++) अणु
		delta = cycles_new[i] - cycles_old[i];
		भाग += delta;
		mult *= i + 1;
		mult += delta * fac;
		fac *= i + 1;
	पूर्ण
	भाग *= fac;
	अगर (भाग > 0) अणु
		/* Update scaling factor */
		__this_cpu_ग_लिखो(mt_scaling_mult, mult);
		__this_cpu_ग_लिखो(mt_scaling_भाग, भाग);
		स_नकल(cycles_old, cycles_new,
		       माप(u64) * (smp_cpu_mtid + 1));
	पूर्ण
	__this_cpu_ग_लिखो(mt_scaling_jअगरfies, jअगरfies_64);
पूर्ण

अटल अंतरभूत u64 update_tsk_समयr(अचिन्हित दीर्घ *tsk_vसमय, u64 new)
अणु
	u64 delta;

	delta = new - *tsk_vसमय;
	*tsk_vसमय = new;
	वापस delta;
पूर्ण


अटल अंतरभूत u64 scale_vसमय(u64 vसमय)
अणु
	u64 mult = __this_cpu_पढ़ो(mt_scaling_mult);
	u64 भाग = __this_cpu_पढ़ो(mt_scaling_भाग);

	अगर (smp_cpu_mtid)
		वापस vसमय * mult / भाग;
	वापस vसमय;
पूर्ण

अटल व्योम account_प्रणाली_index_scaled(काष्ठा task_काष्ठा *p, u64 cpuसमय,
					क्रमागत cpu_usage_stat index)
अणु
	p->sबारcaled += cpuसमय_प्रकारo_nsecs(scale_vसमय(cpuसमय));
	account_प्रणाली_index_समय(p, cpuसमय_प्रकारo_nsecs(cpuसमय), index);
पूर्ण

/*
 * Update process बार based on भव cpu बार stored by entry.S
 * to the lowcore fields user_समयr, प्रणाली_समयr & steal_घड़ी.
 */
अटल पूर्णांक करो_account_vसमय(काष्ठा task_काष्ठा *tsk)
अणु
	u64 समयr, घड़ी, user, guest, प्रणाली, hardirq, softirq;

	समयr = S390_lowcore.last_update_समयr;
	घड़ी = S390_lowcore.last_update_घड़ी;
	/* Use STORE CLOCK by शेष, STORE CLOCK FAST अगर available. */
	alternative_io("stpt %0\n .insn s,0xb2050000,%1\n",
		       "stpt %0\n .insn s,0xb27c0000,%1\n",
		       25,
		       ASM_OUTPUT2("=Q" (S390_lowcore.last_update_समयr),
				   "=Q" (S390_lowcore.last_update_घड़ी)),
		       ASM_NO_INPUT_CLOBBER("cc"));
	घड़ी = S390_lowcore.last_update_घड़ी - घड़ी;
	समयr -= S390_lowcore.last_update_समयr;

	अगर (hardirq_count())
		S390_lowcore.hardirq_समयr += समयr;
	अन्यथा
		S390_lowcore.प्रणाली_समयr += समयr;

	/* Update MT utilization calculation */
	अगर (smp_cpu_mtid &&
	    समय_after64(jअगरfies_64, this_cpu_पढ़ो(mt_scaling_jअगरfies)))
		update_mt_scaling();

	/* Calculate cpuसमय delta */
	user = update_tsk_समयr(&tsk->thपढ़ो.user_समयr,
				READ_ONCE(S390_lowcore.user_समयr));
	guest = update_tsk_समयr(&tsk->thपढ़ो.guest_समयr,
				 READ_ONCE(S390_lowcore.guest_समयr));
	प्रणाली = update_tsk_समयr(&tsk->thपढ़ो.प्रणाली_समयr,
				  READ_ONCE(S390_lowcore.प्रणाली_समयr));
	hardirq = update_tsk_समयr(&tsk->thपढ़ो.hardirq_समयr,
				   READ_ONCE(S390_lowcore.hardirq_समयr));
	softirq = update_tsk_समयr(&tsk->thपढ़ो.softirq_समयr,
				   READ_ONCE(S390_lowcore.softirq_समयr));
	S390_lowcore.steal_समयr +=
		घड़ी - user - guest - प्रणाली - hardirq - softirq;

	/* Push account value */
	अगर (user) अणु
		account_user_समय(tsk, cpuसमय_प्रकारo_nsecs(user));
		tsk->uबारcaled += cpuसमय_प्रकारo_nsecs(scale_vसमय(user));
	पूर्ण

	अगर (guest) अणु
		account_guest_समय(tsk, cpuसमय_प्रकारo_nsecs(guest));
		tsk->uबारcaled += cpuसमय_प्रकारo_nsecs(scale_vसमय(guest));
	पूर्ण

	अगर (प्रणाली)
		account_प्रणाली_index_scaled(tsk, प्रणाली, CPUTIME_SYSTEM);
	अगर (hardirq)
		account_प्रणाली_index_scaled(tsk, hardirq, CPUTIME_IRQ);
	अगर (softirq)
		account_प्रणाली_index_scaled(tsk, softirq, CPUTIME_SOFTIRQ);

	वापस virt_समयr_क्रमward(user + guest + प्रणाली + hardirq + softirq);
पूर्ण

व्योम vसमय_प्रकारask_चयन(काष्ठा task_काष्ठा *prev)
अणु
	करो_account_vसमय(prev);
	prev->thपढ़ो.user_समयr = S390_lowcore.user_समयr;
	prev->thपढ़ो.guest_समयr = S390_lowcore.guest_समयr;
	prev->thपढ़ो.प्रणाली_समयr = S390_lowcore.प्रणाली_समयr;
	prev->thपढ़ो.hardirq_समयr = S390_lowcore.hardirq_समयr;
	prev->thपढ़ो.softirq_समयr = S390_lowcore.softirq_समयr;
	S390_lowcore.user_समयr = current->thपढ़ो.user_समयr;
	S390_lowcore.guest_समयr = current->thपढ़ो.guest_समयr;
	S390_lowcore.प्रणाली_समयr = current->thपढ़ो.प्रणाली_समयr;
	S390_lowcore.hardirq_समयr = current->thपढ़ो.hardirq_समयr;
	S390_lowcore.softirq_समयr = current->thपढ़ो.softirq_समयr;
पूर्ण

/*
 * In s390, accounting pending user समय also implies
 * accounting प्रणाली समय in order to correctly compute
 * the stolen समय accounting.
 */
व्योम vसमय_flush(काष्ठा task_काष्ठा *tsk)
अणु
	u64 steal, avg_steal;

	अगर (करो_account_vसमय(tsk))
		virt_समयr_expire();

	steal = S390_lowcore.steal_समयr;
	avg_steal = S390_lowcore.avg_steal_समयr / 2;
	अगर ((s64) steal > 0) अणु
		S390_lowcore.steal_समयr = 0;
		account_steal_समय(cpuसमय_प्रकारo_nsecs(steal));
		avg_steal += steal;
	पूर्ण
	S390_lowcore.avg_steal_समयr = avg_steal;
पूर्ण

अटल u64 vसमय_delta(व्योम)
अणु
	u64 समयr = S390_lowcore.last_update_समयr;

	S390_lowcore.last_update_समयr = get_vसमयr();

	वापस समयr - S390_lowcore.last_update_समयr;
पूर्ण

/*
 * Update process बार based on भव cpu बार stored by entry.S
 * to the lowcore fields user_समयr, प्रणाली_समयr & steal_घड़ी.
 */
व्योम vसमय_account_kernel(काष्ठा task_काष्ठा *tsk)
अणु
	u64 delta = vसमय_delta();

	अगर (tsk->flags & PF_VCPU)
		S390_lowcore.guest_समयr += delta;
	अन्यथा
		S390_lowcore.प्रणाली_समयr += delta;

	virt_समयr_क्रमward(delta);
पूर्ण
EXPORT_SYMBOL_GPL(vसमय_account_kernel);

व्योम vसमय_account_softirq(काष्ठा task_काष्ठा *tsk)
अणु
	u64 delta = vसमय_delta();

	S390_lowcore.softirq_समयr += delta;

	virt_समयr_क्रमward(delta);
पूर्ण

व्योम vसमय_account_hardirq(काष्ठा task_काष्ठा *tsk)
अणु
	u64 delta = vसमय_delta();

	S390_lowcore.hardirq_समयr += delta;

	virt_समयr_क्रमward(delta);
पूर्ण

/*
 * Sorted add to a list. List is linear searched until first bigger
 * element is found.
 */
अटल व्योम list_add_sorted(काष्ठा vसमयr_list *समयr, काष्ठा list_head *head)
अणु
	काष्ठा vसमयr_list *पंचांगp;

	list_क्रम_each_entry(पंचांगp, head, entry) अणु
		अगर (पंचांगp->expires > समयr->expires) अणु
			list_add_tail(&समयr->entry, &पंचांगp->entry);
			वापस;
		पूर्ण
	पूर्ण
	list_add_tail(&समयr->entry, head);
पूर्ण

/*
 * Handler क्रम expired भव CPU समयr.
 */
अटल व्योम virt_समयr_expire(व्योम)
अणु
	काष्ठा vसमयr_list *समयr, *पंचांगp;
	अचिन्हित दीर्घ elapsed;
	LIST_HEAD(cb_list);

	/* walk समयr list, fire all expired समयrs */
	spin_lock(&virt_समयr_lock);
	elapsed = atomic64_पढ़ो(&virt_समयr_elapsed);
	list_क्रम_each_entry_safe(समयr, पंचांगp, &virt_समयr_list, entry) अणु
		अगर (समयr->expires < elapsed)
			/* move expired समयr to the callback queue */
			list_move_tail(&समयr->entry, &cb_list);
		अन्यथा
			समयr->expires -= elapsed;
	पूर्ण
	अगर (!list_empty(&virt_समयr_list)) अणु
		समयr = list_first_entry(&virt_समयr_list,
					 काष्ठा vसमयr_list, entry);
		atomic64_set(&virt_समयr_current, समयr->expires);
	पूर्ण
	atomic64_sub(elapsed, &virt_समयr_elapsed);
	spin_unlock(&virt_समयr_lock);

	/* Do callbacks and reअक्षरge periodic समयrs */
	list_क्रम_each_entry_safe(समयr, पंचांगp, &cb_list, entry) अणु
		list_del_init(&समयr->entry);
		समयr->function(समयr->data);
		अगर (समयr->पूर्णांकerval) अणु
			/* Reअक्षरge पूर्णांकerval समयr */
			समयr->expires = समयr->पूर्णांकerval +
				atomic64_पढ़ो(&virt_समयr_elapsed);
			spin_lock(&virt_समयr_lock);
			list_add_sorted(समयr, &virt_समयr_list);
			spin_unlock(&virt_समयr_lock);
		पूर्ण
	पूर्ण
पूर्ण

व्योम init_virt_समयr(काष्ठा vसमयr_list *समयr)
अणु
	समयr->function = शून्य;
	INIT_LIST_HEAD(&समयr->entry);
पूर्ण
EXPORT_SYMBOL(init_virt_समयr);

अटल अंतरभूत पूर्णांक vसमयr_pending(काष्ठा vसमयr_list *समयr)
अणु
	वापस !list_empty(&समयr->entry);
पूर्ण

अटल व्योम पूर्णांकernal_add_vसमयr(काष्ठा vसमयr_list *समयr)
अणु
	अगर (list_empty(&virt_समयr_list)) अणु
		/* First समयr, just program it. */
		atomic64_set(&virt_समयr_current, समयr->expires);
		atomic64_set(&virt_समयr_elapsed, 0);
		list_add(&समयr->entry, &virt_समयr_list);
	पूर्ण अन्यथा अणु
		/* Update समयr against current base. */
		समयr->expires += atomic64_पढ़ो(&virt_समयr_elapsed);
		अगर (likely((s64) समयr->expires <
			   (s64) atomic64_पढ़ो(&virt_समयr_current)))
			/* The new समयr expires beक्रमe the current समयr. */
			atomic64_set(&virt_समयr_current, समयr->expires);
		/* Insert new समयr पूर्णांकo the list. */
		list_add_sorted(समयr, &virt_समयr_list);
	पूर्ण
पूर्ण

अटल व्योम __add_vसमयr(काष्ठा vसमयr_list *समयr, पूर्णांक periodic)
अणु
	अचिन्हित दीर्घ flags;

	समयr->पूर्णांकerval = periodic ? समयr->expires : 0;
	spin_lock_irqsave(&virt_समयr_lock, flags);
	पूर्णांकernal_add_vसमयr(समयr);
	spin_unlock_irqrestore(&virt_समयr_lock, flags);
पूर्ण

/*
 * add_virt_समयr - add a oneshot भव CPU समयr
 */
व्योम add_virt_समयr(काष्ठा vसमयr_list *समयr)
अणु
	__add_vसमयr(समयr, 0);
पूर्ण
EXPORT_SYMBOL(add_virt_समयr);

/*
 * add_virt_समयr_पूर्णांक - add an पूर्णांकerval भव CPU समयr
 */
व्योम add_virt_समयr_periodic(काष्ठा vसमयr_list *समयr)
अणु
	__add_vसमयr(समयr, 1);
पूर्ण
EXPORT_SYMBOL(add_virt_समयr_periodic);

अटल पूर्णांक __mod_vसमयr(काष्ठा vसमयr_list *समयr, u64 expires, पूर्णांक periodic)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	BUG_ON(!समयr->function);

	अगर (समयr->expires == expires && vसमयr_pending(समयr))
		वापस 1;
	spin_lock_irqsave(&virt_समयr_lock, flags);
	rc = vसमयr_pending(समयr);
	अगर (rc)
		list_del_init(&समयr->entry);
	समयr->पूर्णांकerval = periodic ? expires : 0;
	समयr->expires = expires;
	पूर्णांकernal_add_vसमयr(समयr);
	spin_unlock_irqrestore(&virt_समयr_lock, flags);
	वापस rc;
पूर्ण

/*
 * वापसs whether it has modअगरied a pending समयr (1) or not (0)
 */
पूर्णांक mod_virt_समयr(काष्ठा vसमयr_list *समयr, u64 expires)
अणु
	वापस __mod_vसमयr(समयr, expires, 0);
पूर्ण
EXPORT_SYMBOL(mod_virt_समयr);

/*
 * वापसs whether it has modअगरied a pending समयr (1) or not (0)
 */
पूर्णांक mod_virt_समयr_periodic(काष्ठा vसमयr_list *समयr, u64 expires)
अणु
	वापस __mod_vसमयr(समयr, expires, 1);
पूर्ण
EXPORT_SYMBOL(mod_virt_समयr_periodic);

/*
 * Delete a भव समयr.
 *
 * वापसs whether the deleted समयr was pending (1) or not (0)
 */
पूर्णांक del_virt_समयr(काष्ठा vसमयr_list *समयr)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!vसमयr_pending(समयr))
		वापस 0;
	spin_lock_irqsave(&virt_समयr_lock, flags);
	list_del_init(&समयr->entry);
	spin_unlock_irqrestore(&virt_समयr_lock, flags);
	वापस 1;
पूर्ण
EXPORT_SYMBOL(del_virt_समयr);

/*
 * Start the भव CPU समयr on the current CPU.
 */
व्योम vसमय_init(व्योम)
अणु
	/* set initial cpu समयr */
	set_vसमयr(VTIMER_MAX_SLICE);
	/* Setup initial MT scaling values */
	अगर (smp_cpu_mtid) अणु
		__this_cpu_ग_लिखो(mt_scaling_jअगरfies, jअगरfies);
		__this_cpu_ग_लिखो(mt_scaling_mult, 1);
		__this_cpu_ग_लिखो(mt_scaling_भाग, 1);
		stccपंचांग(MT_DIAG, smp_cpu_mtid + 1, this_cpu_ptr(mt_cycles));
	पूर्ण
पूर्ण
