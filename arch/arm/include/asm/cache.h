<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  arch/arm/include/यंत्र/cache.h
 */
#अगर_अघोषित __ASMARM_CACHE_H
#घोषणा __ASMARM_CACHE_H

#घोषणा L1_CACHE_SHIFT		CONFIG_ARM_L1_CACHE_SHIFT
#घोषणा L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)

/*
 * Memory वापसed by kदो_स्मृति() may be used क्रम DMA, so we must make
 * sure that all such allocations are cache aligned. Otherwise,
 * unrelated code may cause parts of the buffer to be पढ़ो पूर्णांकo the
 * cache beक्रमe the transfer is करोne, causing old data to be seen by
 * the CPU.
 */
#घोषणा ARCH_DMA_MINALIGN	L1_CACHE_BYTES

/*
 * With EABI on ARMv5 and above we must have 64-bit aligned slab poपूर्णांकers.
 */
#अगर defined(CONFIG_AEABI) && (__LINUX_ARM_ARCH__ >= 5)
#घोषणा ARCH_SLAB_MINALIGN 8
#पूर्ण_अगर

#घोषणा __पढ़ो_mostly __section(".data..read_mostly")

#पूर्ण_अगर
