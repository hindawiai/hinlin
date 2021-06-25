<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * NUMA memory policies क्रम Linux.
 * Copyright 2003,2004 Andi Kleen SuSE Lअसल
 */
#अगर_अघोषित _UAPI_LINUX_MEMPOLICY_H
#घोषणा _UAPI_LINUX_MEMPOLICY_H

#समावेश <linux/त्रुटिसं.स>


/*
 * Both the MPOL_* mempolicy mode and the MPOL_F_* optional mode flags are
 * passed by the user to either set_mempolicy() or mbind() in an 'int' actual.
 * The MPOL_MODE_FLAGS macro determines the legal set of optional mode flags.
 */

/* Policies */
क्रमागत अणु
	MPOL_DEFAULT,
	MPOL_PREFERRED,
	MPOL_BIND,
	MPOL_INTERLEAVE,
	MPOL_LOCAL,
	MPOL_MAX,	/* always last member of क्रमागत */
पूर्ण;

/* Flags क्रम set_mempolicy */
#घोषणा MPOL_F_STATIC_NODES	(1 << 15)
#घोषणा MPOL_F_RELATIVE_NODES	(1 << 14)
#घोषणा MPOL_F_NUMA_BALANCING	(1 << 13) /* Optimize with NUMA balancing अगर possible */

/*
 * MPOL_MODE_FLAGS is the जोड़ of all possible optional mode flags passed to
 * either set_mempolicy() or mbind().
 */
#घोषणा MPOL_MODE_FLAGS							\
	(MPOL_F_STATIC_NODES | MPOL_F_RELATIVE_NODES | MPOL_F_NUMA_BALANCING)

/* Flags क्रम get_mempolicy */
#घोषणा MPOL_F_NODE	(1<<0)	/* वापस next IL mode instead of node mask */
#घोषणा MPOL_F_ADDR	(1<<1)	/* look up vma using address */
#घोषणा MPOL_F_MEMS_ALLOWED (1<<2) /* वापस allowed memories */

/* Flags क्रम mbind */
#घोषणा MPOL_MF_STRICT	(1<<0)	/* Verअगरy existing pages in the mapping */
#घोषणा MPOL_MF_MOVE	 (1<<1)	/* Move pages owned by this process to conक्रमm
				   to policy */
#घोषणा MPOL_MF_MOVE_ALL (1<<2)	/* Move every page to conक्रमm to policy */
#घोषणा MPOL_MF_LAZY	 (1<<3)	/* Modअगरies '_MOVE:  lazy migrate on fault */
#घोषणा MPOL_MF_INTERNAL (1<<4)	/* Internal flags start here */

#घोषणा MPOL_MF_VALID	(MPOL_MF_STRICT   | 	\
			 MPOL_MF_MOVE     | 	\
			 MPOL_MF_MOVE_ALL)

/*
 * Internal flags that share the काष्ठा mempolicy flags word with
 * "mode flags".  These flags are allocated from bit 0 up, as they
 * are never OR'ed पूर्णांकo the mode in mempolicy API arguments.
 */
#घोषणा MPOL_F_SHARED  (1 << 0)	/* identअगरy shared policies */
#घोषणा MPOL_F_LOCAL   (1 << 1)	/* preferred local allocation */
#घोषणा MPOL_F_MOF	(1 << 3) /* this policy wants migrate on fault */
#घोषणा MPOL_F_MORON	(1 << 4) /* Migrate On protnone Reference On Node */

/*
 * These bit locations are exposed in the vm.zone_reclaim_mode sysctl
 * ABI.  New bits are OK, but existing bits can never change.
 */
#घोषणा RECLAIM_ZONE	(1<<0)	/* Run shrink_inactive_list on the zone */
#घोषणा RECLAIM_WRITE	(1<<1)	/* Writeout pages during reclaim */
#घोषणा RECLAIM_UNMAP	(1<<2)	/* Unmap pages during reclaim */

#पूर्ण_अगर /* _UAPI_LINUX_MEMPOLICY_H */
