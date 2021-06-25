<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/sh/mm/cache-sh2.c
 *
 * Copyright (C) 2002 Paul Mundt
 * Copyright (C) 2008 Yoshinori Sato
 */

#समावेश <linux/init.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/पन.स>

अटल व्योम sh2__flush_wback_region(व्योम *start, पूर्णांक size)
अणु
	अचिन्हित दीर्घ v;
	अचिन्हित दीर्घ begin, end;

	begin = (अचिन्हित दीर्घ)start & ~(L1_CACHE_BYTES-1);
	end = ((अचिन्हित दीर्घ)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);
	क्रम (v = begin; v < end; v+=L1_CACHE_BYTES) अणु
		अचिन्हित दीर्घ addr = CACHE_OC_ADDRESS_ARRAY | (v & 0x00000ff0);
		पूर्णांक way;
		क्रम (way = 0; way < 4; way++) अणु
			अचिन्हित दीर्घ data =  __raw_पढ़ोl(addr | (way << 12));
			अगर ((data & CACHE_PHYSADDR_MASK) == (v & CACHE_PHYSADDR_MASK)) अणु
				data &= ~SH_CACHE_UPDATED;
				__raw_ग_लिखोl(data, addr | (way << 12));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sh2__flush_purge_region(व्योम *start, पूर्णांक size)
अणु
	अचिन्हित दीर्घ v;
	अचिन्हित दीर्घ begin, end;

	begin = (अचिन्हित दीर्घ)start & ~(L1_CACHE_BYTES-1);
	end = ((अचिन्हित दीर्घ)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);

	क्रम (v = begin; v < end; v+=L1_CACHE_BYTES)
		__raw_ग_लिखोl((v & CACHE_PHYSADDR_MASK),
			  CACHE_OC_ADDRESS_ARRAY | (v & 0x00000ff0) | 0x00000008);
पूर्ण

अटल व्योम sh2__flush_invalidate_region(व्योम *start, पूर्णांक size)
अणु
#अगर_घोषित CONFIG_CACHE_WRITEBACK
	/*
	 * SH-2 करोes not support inभागidual line invalidation, only a
	 * global invalidate.
	 */
	अचिन्हित दीर्घ ccr;
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	jump_to_uncached();

	ccr = __raw_पढ़ोl(SH_CCR);
	ccr |= CCR_CACHE_INVALIDATE;
	__raw_ग_लिखोl(ccr, SH_CCR);

	back_to_cached();
	local_irq_restore(flags);
#अन्यथा
	अचिन्हित दीर्घ v;
	अचिन्हित दीर्घ begin, end;

	begin = (अचिन्हित दीर्घ)start & ~(L1_CACHE_BYTES-1);
	end = ((अचिन्हित दीर्घ)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);

	क्रम (v = begin; v < end; v+=L1_CACHE_BYTES)
		__raw_ग_लिखोl((v & CACHE_PHYSADDR_MASK),
			  CACHE_OC_ADDRESS_ARRAY | (v & 0x00000ff0) | 0x00000008);
#पूर्ण_अगर
पूर्ण

व्योम __init sh2_cache_init(व्योम)
अणु
	__flush_wback_region		= sh2__flush_wback_region;
	__flush_purge_region		= sh2__flush_purge_region;
	__flush_invalidate_region	= sh2__flush_invalidate_region;
पूर्ण
