<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_PERCPU_H
#घोषणा _ASM_IA64_PERCPU_H

/*
 * Copyright (C) 2002-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

#अगर_घोषित __ASSEMBLY__
# define THIS_CPU(var)	(var)  /* use this to mark accesses to per-CPU variables... */
#अन्यथा /* !__ASSEMBLY__ */


#समावेश <linux/thपढ़ोs.h>

#अगर_घोषित CONFIG_SMP

#अगर_घोषित HAVE_MODEL_SMALL_ATTRIBUTE
# define PER_CPU_ATTRIBUTES	__attribute__((__model__ (__small__)))
#पूर्ण_अगर

#घोषणा __my_cpu_offset	__ia64_per_cpu_var(local_per_cpu_offset)

बाह्य व्योम *per_cpu_init(व्योम);

#अन्यथा /* ! SMP */

#घोषणा per_cpu_init()				(__phys_per_cpu_start)

#पूर्ण_अगर	/* SMP */

#घोषणा PER_CPU_BASE_SECTION ".data..percpu"

/*
 * Be extremely careful when taking the address of this variable!  Due to भव
 * remapping, it is dअगरferent from the canonical address वापसed by this_cpu_ptr(&var)!
 * On the positive side, using __ia64_per_cpu_var() instead of this_cpu_ptr() is slightly
 * more efficient.
 */
#घोषणा __ia64_per_cpu_var(var) (*(अणु					\
	__verअगरy_pcpu_ptr(&(var));					\
	((typeof(var) __kernel __क्रमce *)&(var));			\
पूर्ण))

#समावेश <यंत्र-generic/percpu.h>

/* Equal to __per_cpu_offset[smp_processor_id()], but faster to access: */
DECLARE_PER_CPU(अचिन्हित दीर्घ, local_per_cpu_offset);

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_IA64_PERCPU_H */
