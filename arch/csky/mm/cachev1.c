<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/spinlock.h>
#समावेश <यंत्र/cache.h>
#समावेश <abi/reg_ops.h>

/* क्रम L1-cache */
#घोषणा INS_CACHE		(1 << 0)
#घोषणा DATA_CACHE		(1 << 1)
#घोषणा CACHE_INV		(1 << 4)
#घोषणा CACHE_CLR		(1 << 5)
#घोषणा CACHE_OMS		(1 << 6)
#घोषणा CACHE_ITS		(1 << 7)
#घोषणा CACHE_LICF		(1 << 31)

/* क्रम L2-cache */
#घोषणा CR22_LEVEL_SHIFT	(1)
#घोषणा CR22_SET_SHIFT		(7)
#घोषणा CR22_WAY_SHIFT		(30)
#घोषणा CR22_WAY_SHIFT_L2	(29)

अटल DEFINE_SPINLOCK(cache_lock);

अटल अंतरभूत व्योम cache_op_line(अचिन्हित दीर्घ i, अचिन्हित पूर्णांक val)
अणु
	mtcr("cr22", i);
	mtcr("cr17", val);
पूर्ण

#घोषणा CCR2_L2E (1 << 3)
अटल व्योम cache_op_all(अचिन्हित पूर्णांक value, अचिन्हित पूर्णांक l2)
अणु
	mtcr("cr17", value | CACHE_CLR);
	mb();

	अगर (l2 && (mfcr_ccr2() & CCR2_L2E)) अणु
		mtcr("cr24", value | CACHE_CLR);
		mb();
	पूर्ण
पूर्ण

अटल व्योम cache_op_range(
	अचिन्हित पूर्णांक start,
	अचिन्हित पूर्णांक end,
	अचिन्हित पूर्णांक value,
	अचिन्हित पूर्णांक l2)
अणु
	अचिन्हित दीर्घ i, flags;
	अचिन्हित पूर्णांक val = value | CACHE_CLR | CACHE_OMS;
	bool l2_sync;

	अगर (unlikely((end - start) >= PAGE_SIZE) ||
	    unlikely(start < PAGE_OFFSET) ||
	    unlikely(start >= PAGE_OFFSET + LOWMEM_LIMIT)) अणु
		cache_op_all(value, l2);
		वापस;
	पूर्ण

	अगर ((mfcr_ccr2() & CCR2_L2E) && l2)
		l2_sync = 1;
	अन्यथा
		l2_sync = 0;

	spin_lock_irqsave(&cache_lock, flags);

	i = start & ~(L1_CACHE_BYTES - 1);
	क्रम (; i < end; i += L1_CACHE_BYTES) अणु
		cache_op_line(i, val);
		अगर (l2_sync) अणु
			mb();
			mtcr("cr24", val);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cache_lock, flags);

	mb();
पूर्ण

व्योम dcache_wb_line(अचिन्हित दीर्घ start)
अणु
	यंत्र अस्थिर("idly4\n":::"memory");
	cache_op_line(start, DATA_CACHE|CACHE_CLR);
	mb();
पूर्ण

व्योम icache_inv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	cache_op_range(start, end, INS_CACHE|CACHE_INV, 0);
पूर्ण

व्योम icache_inv_all(व्योम)
अणु
	cache_op_all(INS_CACHE|CACHE_INV, 0);
पूर्ण

व्योम local_icache_inv_all(व्योम *priv)
अणु
	cache_op_all(INS_CACHE|CACHE_INV, 0);
पूर्ण

व्योम dcache_wb_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	cache_op_range(start, end, DATA_CACHE|CACHE_CLR, 0);
पूर्ण

व्योम dcache_wbinv_all(व्योम)
अणु
	cache_op_all(DATA_CACHE|CACHE_CLR|CACHE_INV, 0);
पूर्ण

व्योम cache_wbinv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	cache_op_range(start, end, INS_CACHE|DATA_CACHE|CACHE_CLR|CACHE_INV, 0);
पूर्ण
EXPORT_SYMBOL(cache_wbinv_range);

व्योम cache_wbinv_all(व्योम)
अणु
	cache_op_all(INS_CACHE|DATA_CACHE|CACHE_CLR|CACHE_INV, 0);
पूर्ण

व्योम dma_wbinv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	cache_op_range(start, end, DATA_CACHE|CACHE_CLR|CACHE_INV, 1);
पूर्ण

व्योम dma_inv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	cache_op_range(start, end, DATA_CACHE|CACHE_CLR|CACHE_INV, 1);
पूर्ण

व्योम dma_wb_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	cache_op_range(start, end, DATA_CACHE|CACHE_CLR|CACHE_INV, 1);
पूर्ण
