<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_CACHE_H
#घोषणा __ASM_CSKY_CACHE_H

/* bytes per L1 cache line */
#घोषणा L1_CACHE_SHIFT	CONFIG_L1_CACHE_SHIFT

#घोषणा L1_CACHE_BYTES	(1 << L1_CACHE_SHIFT)

#घोषणा ARCH_DMA_MINALIGN	L1_CACHE_BYTES

#अगर_अघोषित __ASSEMBLY__

व्योम dcache_wb_line(अचिन्हित दीर्घ start);

व्योम icache_inv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम icache_inv_all(व्योम);
व्योम local_icache_inv_all(व्योम *priv);

व्योम dcache_wb_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम dcache_wbinv_all(व्योम);

व्योम cache_wbinv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम cache_wbinv_all(व्योम);

व्योम dma_wbinv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम dma_inv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम dma_wb_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#पूर्ण_अगर
#पूर्ण_अगर  /* __ASM_CSKY_CACHE_H */
