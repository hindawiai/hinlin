<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Sleepable Read-Copy Update mechanism क्रम mutual exclusion,
 *	tree variant.
 *
 * Copyright (C) IBM Corporation, 2017
 *
 * Author: Paul McKenney <paulmck@linux.ibm.com>
 */

#अगर_अघोषित _LINUX_SRCU_TREE_H
#घोषणा _LINUX_SRCU_TREE_H

#समावेश <linux/rcu_node_tree.h>
#समावेश <linux/completion.h>

काष्ठा srcu_node;
काष्ठा srcu_काष्ठा;

/*
 * Per-CPU काष्ठाure feeding पूर्णांकo leaf srcu_node, similar in function
 * to rcu_node.
 */
काष्ठा srcu_data अणु
	/* Read-side state. */
	अचिन्हित दीर्घ srcu_lock_count[2];	/* Locks per CPU. */
	अचिन्हित दीर्घ srcu_unlock_count[2];	/* Unlocks per CPU. */

	/* Update-side state. */
	spinlock_t __निजी lock ____cacheline_पूर्णांकernodealigned_in_smp;
	काष्ठा rcu_segcblist srcu_cblist;	/* List of callbacks.*/
	अचिन्हित दीर्घ srcu_gp_seq_needed;	/* Furthest future GP needed. */
	अचिन्हित दीर्घ srcu_gp_seq_needed_exp;	/* Furthest future exp GP. */
	bool srcu_cblist_invoking;		/* Invoking these CBs? */
	काष्ठा समयr_list delay_work;		/* Delay क्रम CB invoking */
	काष्ठा work_काष्ठा work;		/* Context क्रम CB invoking. */
	काष्ठा rcu_head srcu_barrier_head;	/* For srcu_barrier() use. */
	काष्ठा srcu_node *mynode;		/* Leaf srcu_node. */
	अचिन्हित दीर्घ grpmask;			/* Mask क्रम leaf srcu_node */
						/*  ->srcu_data_have_cbs[]. */
	पूर्णांक cpu;
	काष्ठा srcu_काष्ठा *ssp;
पूर्ण;

/*
 * Node in SRCU combining tree, similar in function to rcu_data.
 */
काष्ठा srcu_node अणु
	spinlock_t __निजी lock;
	अचिन्हित दीर्घ srcu_have_cbs[4];		/* GP seq क्रम children */
						/*  having CBs, but only */
						/*  is > ->srcu_gq_seq. */
	अचिन्हित दीर्घ srcu_data_have_cbs[4];	/* Which srcu_data काष्ठाs */
						/*  have CBs क्रम given GP? */
	अचिन्हित दीर्घ srcu_gp_seq_needed_exp;	/* Furthest future exp GP. */
	काष्ठा srcu_node *srcu_parent;		/* Next up in tree. */
	पूर्णांक grplo;				/* Least CPU क्रम node. */
	पूर्णांक grphi;				/* Biggest CPU क्रम node. */
पूर्ण;

/*
 * Per-SRCU-करोमुख्य काष्ठाure, similar in function to rcu_state.
 */
काष्ठा srcu_काष्ठा अणु
	काष्ठा srcu_node node[NUM_RCU_NODES];	/* Combining tree. */
	काष्ठा srcu_node *level[RCU_NUM_LVLS + 1];
						/* First node at each level. */
	काष्ठा mutex srcu_cb_mutex;		/* Serialize CB preparation. */
	spinlock_t __निजी lock;		/* Protect counters */
	काष्ठा mutex srcu_gp_mutex;		/* Serialize GP work. */
	अचिन्हित पूर्णांक srcu_idx;			/* Current rdr array element. */
	अचिन्हित दीर्घ srcu_gp_seq;		/* Grace-period seq #. */
	अचिन्हित दीर्घ srcu_gp_seq_needed;	/* Latest gp_seq needed. */
	अचिन्हित दीर्घ srcu_gp_seq_needed_exp;	/* Furthest future exp GP. */
	अचिन्हित दीर्घ srcu_last_gp_end;		/* Last GP end बारtamp (ns) */
	काष्ठा srcu_data __percpu *sda;		/* Per-CPU srcu_data array. */
	अचिन्हित दीर्घ srcu_barrier_seq;		/* srcu_barrier seq #. */
	काष्ठा mutex srcu_barrier_mutex;	/* Serialize barrier ops. */
	काष्ठा completion srcu_barrier_completion;
						/* Awaken barrier rq at end. */
	atomic_t srcu_barrier_cpu_cnt;		/* # CPUs not yet posting a */
						/*  callback क्रम the barrier */
						/*  operation. */
	काष्ठा delayed_work work;
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map dep_map;
#पूर्ण_अगर /* #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */
पूर्ण;

/* Values क्रम state variable (bottom bits of ->srcu_gp_seq). */
#घोषणा SRCU_STATE_IDLE		0
#घोषणा SRCU_STATE_SCAN1	1
#घोषणा SRCU_STATE_SCAN2	2

#घोषणा __SRCU_STRUCT_INIT(name, pcpu_name)				\
अणु									\
	.sda = &pcpu_name,						\
	.lock = __SPIN_LOCK_UNLOCKED(name.lock),			\
	.srcu_gp_seq_needed = -1UL,					\
	.work = __DELAYED_WORK_INITIALIZER(name.work, शून्य, 0),		\
	__SRCU_DEP_MAP_INIT(name)					\
पूर्ण

/*
 * Define and initialize a srcu काष्ठा at build समय.
 * Do -not- call init_srcu_काष्ठा() nor cleanup_srcu_काष्ठा() on it.
 *
 * Note that although DEFINE_STATIC_SRCU() hides the name from other
 * files, the per-CPU variable rules nevertheless require that the
 * chosen name be globally unique.  These rules also prohibit use of
 * DEFINE_STATIC_SRCU() within a function.  If these rules are too
 * restrictive, declare the srcu_काष्ठा manually.  For example, in
 * each file:
 *
 *	अटल काष्ठा srcu_काष्ठा my_srcu;
 *
 * Then, beक्रमe the first use of each my_srcu, manually initialize it:
 *
 *	init_srcu_काष्ठा(&my_srcu);
 *
 * See include/linux/percpu-defs.h क्रम the rules on per-CPU variables.
 */
#अगर_घोषित MODULE
# define __DEFINE_SRCU(name, is_अटल)					\
	is_अटल काष्ठा srcu_काष्ठा name;				\
	काष्ठा srcu_काष्ठा * स्थिर __srcu_काष्ठा_##name			\
		__section("___srcu_struct_ptrs") = &name
#अन्यथा
# define __DEFINE_SRCU(name, is_अटल)					\
	अटल DEFINE_PER_CPU(काष्ठा srcu_data, name##_srcu_data);	\
	is_अटल काष्ठा srcu_काष्ठा name =				\
		__SRCU_STRUCT_INIT(name, name##_srcu_data)
#पूर्ण_अगर
#घोषणा DEFINE_SRCU(name)		__DEFINE_SRCU(name, /* not अटल */)
#घोषणा DEFINE_STATIC_SRCU(name)	__DEFINE_SRCU(name, अटल)

व्योम synchronize_srcu_expedited(काष्ठा srcu_काष्ठा *ssp);
व्योम srcu_barrier(काष्ठा srcu_काष्ठा *ssp);
व्योम srcu_torture_stats_prपूर्णांक(काष्ठा srcu_काष्ठा *ssp, अक्षर *tt, अक्षर *tf);

#पूर्ण_अगर
