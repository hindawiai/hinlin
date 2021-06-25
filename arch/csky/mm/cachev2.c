<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/barrier.h>

/* क्रम L1-cache */
#घोषणा INS_CACHE		(1 << 0)
#घोषणा DATA_CACHE		(1 << 1)
#घोषणा CACHE_INV		(1 << 4)
#घोषणा CACHE_CLR		(1 << 5)
#घोषणा CACHE_OMS		(1 << 6)

व्योम local_icache_inv_all(व्योम *priv)
अणु
	mtcr("cr17", INS_CACHE|CACHE_INV);
	sync_is();
पूर्ण

#अगर_घोषित CONFIG_CPU_HAS_ICACHE_INS
व्योम icache_inv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ i = start & ~(L1_CACHE_BYTES - 1);

	क्रम (; i < end; i += L1_CACHE_BYTES)
		यंत्र अस्थिर("icache.iva %0\n"::"r"(i):"memory");
	sync_is();
पूर्ण
#अन्यथा
काष्ठा cache_range अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
पूर्ण;

अटल DEFINE_SPINLOCK(cache_lock);

अटल अंतरभूत व्योम cache_op_line(अचिन्हित दीर्घ i, अचिन्हित पूर्णांक val)
अणु
	mtcr("cr22", i);
	mtcr("cr17", val);
पूर्ण

व्योम local_icache_inv_range(व्योम *priv)
अणु
	काष्ठा cache_range *param = priv;
	अचिन्हित दीर्घ i = param->start & ~(L1_CACHE_BYTES - 1);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cache_lock, flags);

	क्रम (; i < param->end; i += L1_CACHE_BYTES)
		cache_op_line(i, INS_CACHE | CACHE_INV | CACHE_OMS);

	spin_unlock_irqrestore(&cache_lock, flags);

	sync_is();
पूर्ण

व्योम icache_inv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा cache_range param = अणु start, end पूर्ण;

	अगर (irqs_disabled())
		local_icache_inv_range(&param);
	अन्यथा
		on_each_cpu(local_icache_inv_range, &param, 1);
पूर्ण
#पूर्ण_अगर

अंतरभूत व्योम dcache_wb_line(अचिन्हित दीर्घ start)
अणु
	यंत्र अस्थिर("dcache.cval1 %0\n"::"r"(start):"memory");
	sync_is();
पूर्ण

व्योम dcache_wb_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ i = start & ~(L1_CACHE_BYTES - 1);

	क्रम (; i < end; i += L1_CACHE_BYTES)
		यंत्र अस्थिर("dcache.cval1 %0\n"::"r"(i):"memory");
	sync_is();
पूर्ण

व्योम cache_wbinv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	dcache_wb_range(start, end);
	icache_inv_range(start, end);
पूर्ण
EXPORT_SYMBOL(cache_wbinv_range);

व्योम dma_wbinv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ i = start & ~(L1_CACHE_BYTES - 1);

	क्रम (; i < end; i += L1_CACHE_BYTES)
		यंत्र अस्थिर("dcache.civa %0\n"::"r"(i):"memory");
	sync_is();
पूर्ण

व्योम dma_inv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ i = start & ~(L1_CACHE_BYTES - 1);

	क्रम (; i < end; i += L1_CACHE_BYTES)
		यंत्र अस्थिर("dcache.iva %0\n"::"r"(i):"memory");
	sync_is();
पूर्ण

व्योम dma_wb_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ i = start & ~(L1_CACHE_BYTES - 1);

	क्रम (; i < end; i += L1_CACHE_BYTES)
		यंत्र अस्थिर("dcache.cva %0\n"::"r"(i):"memory");
	sync_is();
पूर्ण
