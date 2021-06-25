<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * mach/sram.h - DaVinci simple SRAM allocator
 *
 * Copyright (C) 2009 David Brownell
 */
#अगर_अघोषित __MACH_SRAM_H
#घोषणा __MACH_SRAM_H

/* ARBITRARY:  SRAM allocations are multiples of this 2^N size */
#घोषणा SRAM_GRANULARITY	512

/*
 * SRAM allocations वापस a CPU भव address, or शून्य on error.
 * If a DMA address is requested and the SRAM supports DMA, its
 * mapped address is also वापसed.
 *
 * Errors include SRAM memory not being available, and requesting
 * DMA mapped SRAM on प्रणालीs which करोn't allow that.
 */
बाह्य व्योम *sram_alloc(माप_प्रकार len, dma_addr_t *dma);
बाह्य व्योम sram_मुक्त(व्योम *addr, माप_प्रकार len);

/* Get the काष्ठा gen_pool * क्रम use in platक्रमm data */
बाह्य काष्ठा gen_pool *sram_get_gen_pool(व्योम);

#पूर्ण_अगर /* __MACH_SRAM_H */
