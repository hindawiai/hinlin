<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* delayacct.h - per-task delay accounting
 *
 * Copyright (C) Shailabh Nagar, IBM Corp. 2006
 */

#अगर_अघोषित _LINUX_DELAYACCT_H
#घोषणा _LINUX_DELAYACCT_H

#समावेश <uapi/linux/taskstats.h>

/*
 * Per-task flags relevant to delay accounting
 * मुख्यtained निजीly to aव्योम exhausting similar flags in sched.h:PF_*
 * Used to set current->delays->flags
 */
#घोषणा DELAYACCT_PF_SWAPIN	0x00000001	/* I am करोing a swapin */
#घोषणा DELAYACCT_PF_BLKIO	0x00000002	/* I am रुकोing on IO */

#अगर_घोषित CONFIG_TASK_DELAY_ACCT
काष्ठा task_delay_info अणु
	raw_spinlock_t	lock;
	अचिन्हित पूर्णांक	flags;	/* Private per-task flags */

	/* For each stat XXX, add following, aligned appropriately
	 *
	 * काष्ठा बारpec XXX_start, XXX_end;
	 * u64 XXX_delay;
	 * u32 XXX_count;
	 *
	 * Atomicity of updates to XXX_delay, XXX_count रक्षित by
	 * single lock above (split पूर्णांकo XXX_lock अगर contention is an issue).
	 */

	/*
	 * XXX_count is incremented on every XXX operation, the delay
	 * associated with the operation is added to XXX_delay.
	 * XXX_delay contains the accumulated delay समय in nanoseconds.
	 */
	u64 blkio_start;	/* Shared by blkio, swapin */
	u64 blkio_delay;	/* रुको क्रम sync block io completion */
	u64 swapin_delay;	/* रुको क्रम swapin block io completion */
	u32 blkio_count;	/* total count of the number of sync block */
				/* io operations perक्रमmed */
	u32 swapin_count;	/* total count of the number of swapin block */
				/* io operations perक्रमmed */

	u64 मुक्तpages_start;
	u64 मुक्तpages_delay;	/* रुको क्रम memory reclaim */

	u64 thrashing_start;
	u64 thrashing_delay;	/* रुको क्रम thrashing page */

	u32 मुक्तpages_count;	/* total count of memory reclaim */
	u32 thrashing_count;	/* total count of thrash रुकोs */
पूर्ण;
#पूर्ण_अगर

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#अगर_घोषित CONFIG_TASK_DELAY_ACCT
बाह्य पूर्णांक delayacct_on;	/* Delay accounting turned on/off */
बाह्य काष्ठा kmem_cache *delayacct_cache;
बाह्य व्योम delayacct_init(व्योम);
बाह्य व्योम __delayacct_tsk_init(काष्ठा task_काष्ठा *);
बाह्य व्योम __delayacct_tsk_निकास(काष्ठा task_काष्ठा *);
बाह्य व्योम __delayacct_blkio_start(व्योम);
बाह्य व्योम __delayacct_blkio_end(काष्ठा task_काष्ठा *);
बाह्य पूर्णांक __delayacct_add_tsk(काष्ठा taskstats *, काष्ठा task_काष्ठा *);
बाह्य __u64 __delayacct_blkio_ticks(काष्ठा task_काष्ठा *);
बाह्य व्योम __delayacct_मुक्तpages_start(व्योम);
बाह्य व्योम __delayacct_मुक्तpages_end(व्योम);
बाह्य व्योम __delayacct_thrashing_start(व्योम);
बाह्य व्योम __delayacct_thrashing_end(व्योम);

अटल अंतरभूत पूर्णांक delayacct_is_task_रुकोing_on_io(काष्ठा task_काष्ठा *p)
अणु
	अगर (p->delays)
		वापस (p->delays->flags & DELAYACCT_PF_BLKIO);
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत व्योम delayacct_set_flag(काष्ठा task_काष्ठा *p, पूर्णांक flag)
अणु
	अगर (p->delays)
		p->delays->flags |= flag;
पूर्ण

अटल अंतरभूत व्योम delayacct_clear_flag(काष्ठा task_काष्ठा *p, पूर्णांक flag)
अणु
	अगर (p->delays)
		p->delays->flags &= ~flag;
पूर्ण

अटल अंतरभूत व्योम delayacct_tsk_init(काष्ठा task_काष्ठा *tsk)
अणु
	/* reinitialize in हाल parent's non-null pointer was dup'ed*/
	tsk->delays = शून्य;
	अगर (delayacct_on)
		__delayacct_tsk_init(tsk);
पूर्ण

/* Free tsk->delays. Called from bad विभाजन and __put_task_काष्ठा
 * where there's no risk of tsk->delays being accessed अन्यथाwhere
 */
अटल अंतरभूत व्योम delayacct_tsk_मुक्त(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->delays)
		kmem_cache_मुक्त(delayacct_cache, tsk->delays);
	tsk->delays = शून्य;
पूर्ण

अटल अंतरभूत व्योम delayacct_blkio_start(व्योम)
अणु
	delayacct_set_flag(current, DELAYACCT_PF_BLKIO);
	अगर (current->delays)
		__delayacct_blkio_start();
पूर्ण

अटल अंतरभूत व्योम delayacct_blkio_end(काष्ठा task_काष्ठा *p)
अणु
	अगर (p->delays)
		__delayacct_blkio_end(p);
	delayacct_clear_flag(p, DELAYACCT_PF_BLKIO);
पूर्ण

अटल अंतरभूत पूर्णांक delayacct_add_tsk(काष्ठा taskstats *d,
					काष्ठा task_काष्ठा *tsk)
अणु
	अगर (!delayacct_on || !tsk->delays)
		वापस 0;
	वापस __delayacct_add_tsk(d, tsk);
पूर्ण

अटल अंतरभूत __u64 delayacct_blkio_ticks(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->delays)
		वापस __delayacct_blkio_ticks(tsk);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम delayacct_मुक्तpages_start(व्योम)
अणु
	अगर (current->delays)
		__delayacct_मुक्तpages_start();
पूर्ण

अटल अंतरभूत व्योम delayacct_मुक्तpages_end(व्योम)
अणु
	अगर (current->delays)
		__delayacct_मुक्तpages_end();
पूर्ण

अटल अंतरभूत व्योम delayacct_thrashing_start(व्योम)
अणु
	अगर (current->delays)
		__delayacct_thrashing_start();
पूर्ण

अटल अंतरभूत व्योम delayacct_thrashing_end(व्योम)
अणु
	अगर (current->delays)
		__delayacct_thrashing_end();
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम delayacct_set_flag(काष्ठा task_काष्ठा *p, पूर्णांक flag)
अणुपूर्ण
अटल अंतरभूत व्योम delayacct_clear_flag(काष्ठा task_काष्ठा *p, पूर्णांक flag)
अणुपूर्ण
अटल अंतरभूत व्योम delayacct_init(व्योम)
अणुपूर्ण
अटल अंतरभूत व्योम delayacct_tsk_init(काष्ठा task_काष्ठा *tsk)
अणुपूर्ण
अटल अंतरभूत व्योम delayacct_tsk_मुक्त(काष्ठा task_काष्ठा *tsk)
अणुपूर्ण
अटल अंतरभूत व्योम delayacct_blkio_start(व्योम)
अणुपूर्ण
अटल अंतरभूत व्योम delayacct_blkio_end(काष्ठा task_काष्ठा *p)
अणुपूर्ण
अटल अंतरभूत पूर्णांक delayacct_add_tsk(काष्ठा taskstats *d,
					काष्ठा task_काष्ठा *tsk)
अणु वापस 0; पूर्ण
अटल अंतरभूत __u64 delayacct_blkio_ticks(काष्ठा task_काष्ठा *tsk)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक delayacct_is_task_रुकोing_on_io(काष्ठा task_काष्ठा *p)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम delayacct_मुक्तpages_start(व्योम)
अणुपूर्ण
अटल अंतरभूत व्योम delayacct_मुक्तpages_end(व्योम)
अणुपूर्ण
अटल अंतरभूत व्योम delayacct_thrashing_start(व्योम)
अणुपूर्ण
अटल अंतरभूत व्योम delayacct_thrashing_end(व्योम)
अणुपूर्ण

#पूर्ण_अगर /* CONFIG_TASK_DELAY_ACCT */

#पूर्ण_अगर
