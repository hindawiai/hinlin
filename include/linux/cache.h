<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_CACHE_H
#घोषणा __LINUX_CACHE_H

#समावेश <uapi/linux/kernel.h>
#समावेश <यंत्र/cache.h>

#अगर_अघोषित L1_CACHE_ALIGN
#घोषणा L1_CACHE_ALIGN(x) __ALIGN_KERNEL(x, L1_CACHE_BYTES)
#पूर्ण_अगर

#अगर_अघोषित SMP_CACHE_BYTES
#घोषणा SMP_CACHE_BYTES L1_CACHE_BYTES
#पूर्ण_अगर

/*
 * __पढ़ो_mostly is used to keep rarely changing variables out of frequently
 * updated cachelines. Its use should be reserved क्रम data that is used
 * frequently in hot paths. Perक्रमmance traces can help decide when to use
 * this. You want __पढ़ो_mostly data to be tightly packed, so that in the
 * best हाल multiple frequently पढ़ो variables क्रम a hot path will be next
 * to each other in order to reduce the number of cachelines needed to
 * execute a critical path. We should be mindful and selective of its use.
 * ie: अगर you're going to use it please supply a *good* justअगरication in your
 * commit log
 */
#अगर_अघोषित __पढ़ो_mostly
#घोषणा __पढ़ो_mostly
#पूर्ण_अगर

/*
 * __ro_after_init is used to mark things that are पढ़ो-only after init (i.e.
 * after mark_rodata_ro() has been called). These are effectively पढ़ो-only,
 * but may get written to during init, so can't live in .rodata (via "const").
 */
#अगर_अघोषित __ro_after_init
#घोषणा __ro_after_init __section(".data..ro_after_init")
#पूर्ण_अगर

#अगर_अघोषित ____cacheline_aligned
#घोषणा ____cacheline_aligned __attribute__((__aligned__(SMP_CACHE_BYTES)))
#पूर्ण_अगर

#अगर_अघोषित ____cacheline_aligned_in_smp
#अगर_घोषित CONFIG_SMP
#घोषणा ____cacheline_aligned_in_smp ____cacheline_aligned
#अन्यथा
#घोषणा ____cacheline_aligned_in_smp
#पूर्ण_अगर /* CONFIG_SMP */
#पूर्ण_अगर

#अगर_अघोषित __cacheline_aligned
#घोषणा __cacheline_aligned					\
  __attribute__((__aligned__(SMP_CACHE_BYTES),			\
		 __section__(".data..cacheline_aligned")))
#पूर्ण_अगर /* __cacheline_aligned */

#अगर_अघोषित __cacheline_aligned_in_smp
#अगर_घोषित CONFIG_SMP
#घोषणा __cacheline_aligned_in_smp __cacheline_aligned
#अन्यथा
#घोषणा __cacheline_aligned_in_smp
#पूर्ण_अगर /* CONFIG_SMP */
#पूर्ण_अगर

/*
 * The maximum alignment needed क्रम some critical काष्ठाures
 * These could be पूर्णांकer-node cacheline sizes/L3 cacheline
 * size etc.  Define this in यंत्र/cache.h क्रम your arch
 */
#अगर_अघोषित INTERNODE_CACHE_SHIFT
#घोषणा INTERNODE_CACHE_SHIFT L1_CACHE_SHIFT
#पूर्ण_अगर

#अगर !defined(____cacheline_पूर्णांकernodealigned_in_smp)
#अगर defined(CONFIG_SMP)
#घोषणा ____cacheline_पूर्णांकernodealigned_in_smp \
	__attribute__((__aligned__(1 << (INTERNODE_CACHE_SHIFT))))
#अन्यथा
#घोषणा ____cacheline_पूर्णांकernodealigned_in_smp
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित CONFIG_ARCH_HAS_CACHE_LINE_SIZE
#घोषणा cache_line_size()	L1_CACHE_BYTES
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_CACHE_H */
