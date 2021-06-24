<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_COREDUMP_H
#घोषणा _LINUX_SCHED_COREDUMP_H

#समावेश <linux/mm_types.h>

#घोषणा SUID_DUMP_DISABLE	0	/* No setuid dumping */
#घोषणा SUID_DUMP_USER		1	/* Dump as user of process */
#घोषणा SUID_DUMP_ROOT		2	/* Dump as root */

/* mm flags */

/* क्रम SUID_DUMP_* above */
#घोषणा MMF_DUMPABLE_BITS 2
#घोषणा MMF_DUMPABLE_MASK ((1 << MMF_DUMPABLE_BITS) - 1)

बाह्य व्योम set_dumpable(काष्ठा mm_काष्ठा *mm, पूर्णांक value);
/*
 * This वापसs the actual value of the suid_dumpable flag. For things
 * that are using this क्रम checking क्रम privilege transitions, it must
 * test against SUID_DUMP_USER rather than treating it as a boolean
 * value.
 */
अटल अंतरभूत पूर्णांक __get_dumpable(अचिन्हित दीर्घ mm_flags)
अणु
	वापस mm_flags & MMF_DUMPABLE_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक get_dumpable(काष्ठा mm_काष्ठा *mm)
अणु
	वापस __get_dumpable(mm->flags);
पूर्ण

/* coredump filter bits */
#घोषणा MMF_DUMP_ANON_PRIVATE	2
#घोषणा MMF_DUMP_ANON_SHARED	3
#घोषणा MMF_DUMP_MAPPED_PRIVATE	4
#घोषणा MMF_DUMP_MAPPED_SHARED	5
#घोषणा MMF_DUMP_ELF_HEADERS	6
#घोषणा MMF_DUMP_HUGETLB_PRIVATE 7
#घोषणा MMF_DUMP_HUGETLB_SHARED  8
#घोषणा MMF_DUMP_DAX_PRIVATE	9
#घोषणा MMF_DUMP_DAX_SHARED	10

#घोषणा MMF_DUMP_FILTER_SHIFT	MMF_DUMPABLE_BITS
#घोषणा MMF_DUMP_FILTER_BITS	9
#घोषणा MMF_DUMP_FILTER_MASK \
	(((1 << MMF_DUMP_FILTER_BITS) - 1) << MMF_DUMP_FILTER_SHIFT)
#घोषणा MMF_DUMP_FILTER_DEFAULT \
	((1 << MMF_DUMP_ANON_PRIVATE) |	(1 << MMF_DUMP_ANON_SHARED) |\
	 (1 << MMF_DUMP_HUGETLB_PRIVATE) | MMF_DUMP_MASK_DEFAULT_ELF)

#अगर_घोषित CONFIG_CORE_DUMP_DEFAULT_ELF_HEADERS
# define MMF_DUMP_MASK_DEFAULT_ELF	(1 << MMF_DUMP_ELF_HEADERS)
#अन्यथा
# define MMF_DUMP_MASK_DEFAULT_ELF	0
#पूर्ण_अगर
					/* leave room क्रम more dump flags */
#घोषणा MMF_VM_MERGEABLE	16	/* KSM may merge identical pages */
#घोषणा MMF_VM_HUGEPAGE		17	/* set when VM_HUGEPAGE is set on vma */
/*
 * This one-shot flag is dropped due to necessity of changing exe once again
 * on NFS restore
 */
//#घोषणा MMF_EXE_खाता_CHANGED	18	/* see prctl_set_mm_exe_file() */

#घोषणा MMF_HAS_UPROBES		19	/* has uprobes */
#घोषणा MMF_RECALC_UPROBES	20	/* MMF_HAS_UPROBES can be wrong */
#घोषणा MMF_OOM_SKIP		21	/* mm is of no पूर्णांकerest क्रम the OOM समाप्तer */
#घोषणा MMF_UNSTABLE		22	/* mm is unstable क्रम copy_from_user */
#घोषणा MMF_HUGE_ZERO_PAGE	23      /* mm has ever used the global huge zero page */
#घोषणा MMF_DISABLE_THP		24	/* disable THP क्रम all VMAs */
#घोषणा MMF_OOM_VICTIM		25	/* mm is the oom victim */
#घोषणा MMF_OOM_REAP_QUEUED	26	/* mm was queued क्रम oom_reaper */
#घोषणा MMF_MULTIPROCESS	27	/* mm is shared between processes */
#घोषणा MMF_DISABLE_THP_MASK	(1 << MMF_DISABLE_THP)

#घोषणा MMF_INIT_MASK		(MMF_DUMPABLE_MASK | MMF_DUMP_FILTER_MASK |\
				 MMF_DISABLE_THP_MASK)

#पूर्ण_अगर /* _LINUX_SCHED_COREDUMP_H */
