<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * All rights reserved.
 */

#अगर_अघोषित _ASM_NIOS2_CACHE_H
#घोषणा _ASM_NIOS2_CACHE_H

#घोषणा NIOS2_DCACHE_SIZE	CONFIG_NIOS2_DCACHE_SIZE
#घोषणा NIOS2_ICACHE_SIZE	CONFIG_NIOS2_ICACHE_SIZE
#घोषणा NIOS2_DCACHE_LINE_SIZE	CONFIG_NIOS2_DCACHE_LINE_SIZE
#घोषणा NIOS2_ICACHE_LINE_SHIFT	5
#घोषणा NIOS2_ICACHE_LINE_SIZE	(1 << NIOS2_ICACHE_LINE_SHIFT)

/* bytes per L1 cache line */
#घोषणा L1_CACHE_SHIFT		NIOS2_ICACHE_LINE_SHIFT
#घोषणा L1_CACHE_BYTES		NIOS2_ICACHE_LINE_SIZE

#घोषणा ARCH_DMA_MINALIGN	L1_CACHE_BYTES

#घोषणा __cacheline_aligned
#घोषणा ____cacheline_aligned

#पूर्ण_अगर
