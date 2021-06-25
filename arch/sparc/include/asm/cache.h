<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* cache.h:  Cache specअगरic code क्रम the Sparc.  These include flushing
 *           and direct tag/data line access.
 *
 * Copyright (C) 1995, 2007 David S. Miller (davem@davemloft.net)
 */

#अगर_अघोषित _SPARC_CACHE_H
#घोषणा _SPARC_CACHE_H

#घोषणा ARCH_SLAB_MINALIGN	__alignof__(अचिन्हित दीर्घ दीर्घ)

#घोषणा L1_CACHE_SHIFT 5
#घोषणा L1_CACHE_BYTES 32

#अगर_घोषित CONFIG_SPARC32
#घोषणा SMP_CACHE_BYTES_SHIFT 5
#अन्यथा
#घोषणा SMP_CACHE_BYTES_SHIFT 6
#पूर्ण_अगर

#घोषणा SMP_CACHE_BYTES (1 << SMP_CACHE_BYTES_SHIFT)

#घोषणा __पढ़ो_mostly __section(".data..read_mostly")

#पूर्ण_अगर /* !(_SPARC_CACHE_H) */
