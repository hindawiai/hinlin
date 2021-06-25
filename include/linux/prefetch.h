<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Generic cache management functions. Everything is arch-specअगरic,  
 *  but this header exists to make sure the defines/functions can be
 *  used in a generic way.
 *
 *  2000-11-13  Arjan van de Ven   <arjan@fenrus.demon.nl>
 *
 */

#अगर_अघोषित _LINUX_PREFETCH_H
#घोषणा _LINUX_PREFETCH_H

#समावेश <linux/types.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cache.h>

काष्ठा page;
/*
	prefetch(x) attempts to pre-emptively get the memory poपूर्णांकed to
	by address "x" पूर्णांकo the CPU L1 cache. 
	prefetch(x) should not cause any kind of exception, prefetch(0) is
	specअगरically ok.

	prefetch() should be defined by the architecture, अगर not, the 
	#घोषणा below provides a no-op define.	
	
	There are 3 prefetch() macros:
	
	prefetch(x)  	- prefetches the cacheline at "x" क्रम पढ़ो
	prefetchw(x)	- prefetches the cacheline at "x" क्रम ग_लिखो
	spin_lock_prefetch(x) - prefetches the spinlock *x क्रम taking
	
	there is also PREFETCH_STRIDE which is the architecure-preferred 
	"lookahead" size क्रम prefetching streamed operations.
	
*/

#अगर_अघोषित ARCH_HAS_PREFETCH
#घोषणा prefetch(x) __builtin_prefetch(x)
#पूर्ण_अगर

#अगर_अघोषित ARCH_HAS_PREFETCHW
#घोषणा prefetchw(x) __builtin_prefetch(x,1)
#पूर्ण_अगर

#अगर_अघोषित ARCH_HAS_SPINLOCK_PREFETCH
#घोषणा spin_lock_prefetch(x) prefetchw(x)
#पूर्ण_अगर

#अगर_अघोषित PREFETCH_STRIDE
#घोषणा PREFETCH_STRIDE (4*L1_CACHE_BYTES)
#पूर्ण_अगर

अटल अंतरभूत व्योम prefetch_range(व्योम *addr, माप_प्रकार len)
अणु
#अगर_घोषित ARCH_HAS_PREFETCH
	अक्षर *cp;
	अक्षर *end = addr + len;

	क्रम (cp = addr; cp < end; cp += PREFETCH_STRIDE)
		prefetch(cp);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम prefetch_page_address(काष्ठा page *page)
अणु
#अगर defined(WANT_PAGE_VIRTUAL) || defined(HASHED_PAGE_VIRTUAL)
	prefetch(page);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर
