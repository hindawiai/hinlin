<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tools/testing/selftests/kvm/include/numaअगर.h
 *
 * Copyright (C) 2020, Google LLC.
 *
 * This work is licensed under the terms of the GNU GPL, version 2.
 *
 * Header file that provides access to NUMA API functions not explicitly
 * exported to user space.
 */

#अगर_अघोषित SELFTEST_KVM_NUMAIF_H
#घोषणा SELFTEST_KVM_NUMAIF_H

#घोषणा __NR_get_mempolicy 239
#घोषणा __NR_migrate_pages 256

/* System calls */
दीर्घ get_mempolicy(पूर्णांक *policy, स्थिर अचिन्हित दीर्घ *nmask,
		   अचिन्हित दीर्घ maxnode, व्योम *addr, पूर्णांक flags)
अणु
	वापस syscall(__NR_get_mempolicy, policy, nmask,
		       maxnode, addr, flags);
पूर्ण

दीर्घ migrate_pages(पूर्णांक pid, अचिन्हित दीर्घ maxnode,
		   स्थिर अचिन्हित दीर्घ *frommask,
		   स्थिर अचिन्हित दीर्घ *tomask)
अणु
	वापस syscall(__NR_migrate_pages, pid, maxnode, frommask, tomask);
पूर्ण

/* Policies */
#घोषणा MPOL_DEFAULT	 0
#घोषणा MPOL_PREFERRED	 1
#घोषणा MPOL_BIND	 2
#घोषणा MPOL_INTERLEAVE	 3

#घोषणा MPOL_MAX MPOL_INTERLEAVE

/* Flags क्रम get_mem_policy */
#घोषणा MPOL_F_NODE	    (1<<0)  /* वापस next il node or node of address */
				    /* Warning: MPOL_F_NODE is unsupported and
				     * subject to change. Don't use.
				     */
#घोषणा MPOL_F_ADDR	    (1<<1)  /* look up vma using address */
#घोषणा MPOL_F_MEMS_ALLOWED (1<<2)  /* query nodes allowed in cpuset */

/* Flags क्रम mbind */
#घोषणा MPOL_MF_STRICT	     (1<<0) /* Verअगरy existing pages in the mapping */
#घोषणा MPOL_MF_MOVE	     (1<<1) /* Move pages owned by this process to conक्रमm to mapping */
#घोषणा MPOL_MF_MOVE_ALL     (1<<2) /* Move every page to conक्रमm to mapping */

#पूर्ण_अगर /* SELFTEST_KVM_NUMAIF_H */
