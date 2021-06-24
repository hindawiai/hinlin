<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Sleepable Read-Copy Update mechanism क्रम mutual exclusion,
 *	tiny variant.
 *
 * Copyright (C) IBM Corporation, 2017
 *
 * Author: Paul McKenney <paulmck@linux.ibm.com>
 */

#अगर_अघोषित _LINUX_SRCU_TINY_H
#घोषणा _LINUX_SRCU_TINY_H

#समावेश <linux/sरुको.h>

काष्ठा srcu_काष्ठा अणु
	लघु srcu_lock_nesting[2];	/* srcu_पढ़ो_lock() nesting depth. */
	अचिन्हित लघु srcu_idx;	/* Current पढ़ोer array element in bit 0x2. */
	अचिन्हित लघु srcu_idx_max;	/* Furthest future srcu_idx request. */
	u8 srcu_gp_running;		/* GP workqueue running? */
	u8 srcu_gp_रुकोing;		/* GP रुकोing क्रम पढ़ोers? */
	काष्ठा sरुको_queue_head srcu_wq;
					/* Last srcu_पढ़ो_unlock() wakes GP. */
	काष्ठा rcu_head *srcu_cb_head;	/* Pending callbacks: Head. */
	काष्ठा rcu_head **srcu_cb_tail;	/* Pending callbacks: Tail. */
	काष्ठा work_काष्ठा srcu_work;	/* For driving grace periods. */
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map dep_map;
#पूर्ण_अगर /* #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */
पूर्ण;

व्योम srcu_drive_gp(काष्ठा work_काष्ठा *wp);

#घोषणा __SRCU_STRUCT_INIT(name, __ignored)				\
अणु									\
	.srcu_wq = __SWAIT_QUEUE_HEAD_INITIALIZER(name.srcu_wq),	\
	.srcu_cb_tail = &name.srcu_cb_head,				\
	.srcu_work = __WORK_INITIALIZER(name.srcu_work, srcu_drive_gp),	\
	__SRCU_DEP_MAP_INIT(name)					\
पूर्ण

/*
 * This odd _STATIC_ arrangement is needed क्रम API compatibility with
 * Tree SRCU, which needs some per-CPU data.
 */
#घोषणा DEFINE_SRCU(name) \
	काष्ठा srcu_काष्ठा name = __SRCU_STRUCT_INIT(name, name)
#घोषणा DEFINE_STATIC_SRCU(name) \
	अटल काष्ठा srcu_काष्ठा name = __SRCU_STRUCT_INIT(name, name)

व्योम synchronize_srcu(काष्ठा srcu_काष्ठा *ssp);

/*
 * Counts the new पढ़ोer in the appropriate per-CPU element of the
 * srcu_काष्ठा.  Can be invoked from irq/bh handlers, but the matching
 * __srcu_पढ़ो_unlock() must be in the same handler instance.  Returns an
 * index that must be passed to the matching srcu_पढ़ो_unlock().
 */
अटल अंतरभूत पूर्णांक __srcu_पढ़ो_lock(काष्ठा srcu_काष्ठा *ssp)
अणु
	पूर्णांक idx;

	idx = ((READ_ONCE(ssp->srcu_idx) + 1) & 0x2) >> 1;
	WRITE_ONCE(ssp->srcu_lock_nesting[idx], ssp->srcu_lock_nesting[idx] + 1);
	वापस idx;
पूर्ण

अटल अंतरभूत व्योम synchronize_srcu_expedited(काष्ठा srcu_काष्ठा *ssp)
अणु
	synchronize_srcu(ssp);
पूर्ण

अटल अंतरभूत व्योम srcu_barrier(काष्ठा srcu_काष्ठा *ssp)
अणु
	synchronize_srcu(ssp);
पूर्ण

/* Defined here to aव्योम size increase क्रम non-torture kernels. */
अटल अंतरभूत व्योम srcu_torture_stats_prपूर्णांक(काष्ठा srcu_काष्ठा *ssp,
					    अक्षर *tt, अक्षर *tf)
अणु
	पूर्णांक idx;

	idx = ((READ_ONCE(ssp->srcu_idx) + 1) & 0x2) >> 1;
	pr_alert("%s%s Tiny SRCU per-CPU(idx=%d): (%hd,%hd)\n",
		 tt, tf, idx,
		 READ_ONCE(ssp->srcu_lock_nesting[!idx]),
		 READ_ONCE(ssp->srcu_lock_nesting[idx]));
पूर्ण

#पूर्ण_अगर
