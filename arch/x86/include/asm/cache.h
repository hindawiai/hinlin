<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_CACHE_H
#घोषणा _ASM_X86_CACHE_H

#समावेश <linux/linkage.h>

/* L1 cache line size */
#घोषणा L1_CACHE_SHIFT	(CONFIG_X86_L1_CACHE_SHIFT)
#घोषणा L1_CACHE_BYTES	(1 << L1_CACHE_SHIFT)

#घोषणा __पढ़ो_mostly __section(".data..read_mostly")

#घोषणा INTERNODE_CACHE_SHIFT CONFIG_X86_INTERNODE_CACHE_SHIFT
#घोषणा INTERNODE_CACHE_BYTES (1 << INTERNODE_CACHE_SHIFT)

#अगर_घोषित CONFIG_X86_VSMP
#अगर_घोषित CONFIG_SMP
#घोषणा __cacheline_aligned_in_smp					\
	__attribute__((__aligned__(INTERNODE_CACHE_BYTES)))		\
	__page_aligned_data
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_CACHE_H */
