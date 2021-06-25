<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Cache definitions क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011,2014 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __ASM_CACHE_H
#घोषणा __ASM_CACHE_H

/* Bytes per L1 cache line */
#घोषणा L1_CACHE_SHIFT		(5)
#घोषणा L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)

#घोषणा ARCH_DMA_MINALIGN	L1_CACHE_BYTES

#घोषणा __cacheline_aligned	__aligned(L1_CACHE_BYTES)
#घोषणा ____cacheline_aligned	__aligned(L1_CACHE_BYTES)

/* See http://lwn.net/Articles/262554/ */
#घोषणा __पढ़ो_mostly

#पूर्ण_अगर
