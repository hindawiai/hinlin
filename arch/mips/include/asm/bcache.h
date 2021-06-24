<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 1997, 1999 by Ralf Baechle
 * Copyright (c) 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_BCACHE_H
#घोषणा _ASM_BCACHE_H

#समावेश <linux/types.h>

/* Some R4000 / R4400 / R4600 / R5000 machines may have a non-dma-coherent,
   chipset implemented caches.	On machines with other CPUs the CPU करोes the
   cache thing itself. */
काष्ठा bcache_ops अणु
	व्योम (*bc_enable)(व्योम);
	व्योम (*bc_disable)(व्योम);
	व्योम (*bc_wback_inv)(अचिन्हित दीर्घ page, अचिन्हित दीर्घ size);
	व्योम (*bc_inv)(अचिन्हित दीर्घ page, अचिन्हित दीर्घ size);
	व्योम (*bc_prefetch_enable)(व्योम);
	व्योम (*bc_prefetch_disable)(व्योम);
	bool (*bc_prefetch_is_enabled)(व्योम);
पूर्ण;

बाह्य व्योम indy_sc_init(व्योम);

#अगर_घोषित CONFIG_BOARD_SCACHE

बाह्य काष्ठा bcache_ops *bcops;

अटल अंतरभूत व्योम bc_enable(व्योम)
अणु
	bcops->bc_enable();
पूर्ण

अटल अंतरभूत व्योम bc_disable(व्योम)
अणु
	bcops->bc_disable();
पूर्ण

अटल अंतरभूत व्योम bc_wback_inv(अचिन्हित दीर्घ page, अचिन्हित दीर्घ size)
अणु
	bcops->bc_wback_inv(page, size);
पूर्ण

अटल अंतरभूत व्योम bc_inv(अचिन्हित दीर्घ page, अचिन्हित दीर्घ size)
अणु
	bcops->bc_inv(page, size);
पूर्ण

अटल अंतरभूत व्योम bc_prefetch_enable(व्योम)
अणु
	अगर (bcops->bc_prefetch_enable)
		bcops->bc_prefetch_enable();
पूर्ण

अटल अंतरभूत व्योम bc_prefetch_disable(व्योम)
अणु
	अगर (bcops->bc_prefetch_disable)
		bcops->bc_prefetch_disable();
पूर्ण

अटल अंतरभूत bool bc_prefetch_is_enabled(व्योम)
अणु
	अगर (bcops->bc_prefetch_is_enabled)
		वापस bcops->bc_prefetch_is_enabled();

	वापस false;
पूर्ण

#अन्यथा /* !defined(CONFIG_BOARD_SCACHE) */

/* Not R4000 / R4400 / R4600 / R5000.  */

#घोषणा bc_enable() करो अणु पूर्ण जबतक (0)
#घोषणा bc_disable() करो अणु पूर्ण जबतक (0)
#घोषणा bc_wback_inv(page, size) करो अणु पूर्ण जबतक (0)
#घोषणा bc_inv(page, size) करो अणु पूर्ण जबतक (0)
#घोषणा bc_prefetch_enable() करो अणु पूर्ण जबतक (0)
#घोषणा bc_prefetch_disable() करो अणु पूर्ण जबतक (0)
#घोषणा bc_prefetch_is_enabled() 0

#पूर्ण_अगर /* !defined(CONFIG_BOARD_SCACHE) */

#पूर्ण_अगर /* _ASM_BCACHE_H */
