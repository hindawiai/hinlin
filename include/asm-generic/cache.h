<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_CACHE_H
#घोषणा __ASM_GENERIC_CACHE_H
/*
 * 32 bytes appears to be the most common cache line size,
 * so make that the शेष here. Architectures with larger
 * cache lines need to provide their own cache.h.
 */

#घोषणा L1_CACHE_SHIFT		5
#घोषणा L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)

#पूर्ण_अगर /* __ASM_GENERIC_CACHE_H */
