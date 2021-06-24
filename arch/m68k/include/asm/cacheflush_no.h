<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68KNOMMU_CACHEFLUSH_H
#घोषणा _M68KNOMMU_CACHEFLUSH_H

/*
 * (C) Copyright 2000-2010, Greg Ungerer <gerg@snapgear.com>
 */
#समावेश <linux/mm.h>
#समावेश <यंत्र/mcfsim.h>

#घोषणा flush_cache_all()			__flush_cache_all()
#घोषणा flush_dcache_range(start, len)		__flush_dcache_all()
#घोषणा flush_icache_range(start, len)		__flush_icache_all()

व्योम mcf_cache_push(व्योम);

अटल अंतरभूत व्योम __clear_cache_all(व्योम)
अणु
#अगर_घोषित CACHE_INVALIDATE
	__यंत्र__ __अस्थिर__ (
		"movec	%0, %%CACR\n\t"
		"nop\n\t"
		: : "r" (CACHE_INVALIDATE) );
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम __flush_cache_all(व्योम)
अणु
#अगर_घोषित CACHE_PUSH
	mcf_cache_push();
#पूर्ण_अगर
	__clear_cache_all();
पूर्ण

/*
 * Some ColdFire parts implement separate inकाष्ठाion and data caches,
 * on those we should just flush the appropriate cache. If we करोn't need
 * to करो any specअगरic flushing then this will be optimized away.
 */
अटल अंतरभूत व्योम __flush_icache_all(व्योम)
अणु
#अगर_घोषित CACHE_INVALIDATEI
	__यंत्र__ __अस्थिर__ (
		"movec	%0, %%CACR\n\t"
		"nop\n\t"
		: : "r" (CACHE_INVALIDATEI) );
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम __flush_dcache_all(व्योम)
अणु
#अगर_घोषित CACHE_PUSH
	mcf_cache_push();
#पूर्ण_अगर
#अगर_घोषित CACHE_INVALIDATED
	__यंत्र__ __अस्थिर__ (
		"movec	%0, %%CACR\n\t"
		"nop\n\t"
		: : "r" (CACHE_INVALIDATED) );
#अन्यथा
	/* Flush the ग_लिखो buffer */
	__यंत्र__ __अस्थिर__ ( "nop" );
#पूर्ण_अगर
पूर्ण

/*
 * Push cache entries at supplied address. We want to ग_लिखो back any dirty
 * data and then invalidate the cache lines associated with this address.
 */
अटल अंतरभूत व्योम cache_push(अचिन्हित दीर्घ paddr, पूर्णांक len)
अणु
	__flush_cache_all();
पूर्ण

/*
 * Clear cache entries at supplied address (that is करोn't ग_लिखो back any
 * dirty data).
 */
अटल अंतरभूत व्योम cache_clear(अचिन्हित दीर्घ paddr, पूर्णांक len)
अणु
	__clear_cache_all();
पूर्ण

#समावेश <यंत्र-generic/cacheflush.h>

#पूर्ण_अगर /* _M68KNOMMU_CACHEFLUSH_H */
