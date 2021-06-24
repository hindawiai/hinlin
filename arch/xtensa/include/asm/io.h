<शैली गुरु>
/*
 * include/यंत्र-xtensa/पन.स
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_IO_H
#घोषणा _XTENSA_IO_H

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/vectors.h>
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>

#समावेश <linux/types.h>

#घोषणा IOADDR(x)		(XCHAL_KIO_BYPASS_VADDR + (x))
#घोषणा IO_SPACE_LIMIT ~0
#घोषणा PCI_IOBASE		((व्योम __iomem *)XCHAL_KIO_BYPASS_VADDR)

#अगर_घोषित CONFIG_MMU

व्योम __iomem *xtensa_ioremap_nocache(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size);
व्योम __iomem *xtensa_ioremap_cache(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size);
व्योम xtensa_iounmap(अस्थिर व्योम __iomem *addr);

/*
 * Return the भव address क्रम the specअगरied bus memory.
 */
अटल अंतरभूत व्योम __iomem *ioremap(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size)
अणु
	अगर (offset >= XCHAL_KIO_PADDR
	    && offset - XCHAL_KIO_PADDR < XCHAL_KIO_SIZE)
		वापस (व्योम*)(offset-XCHAL_KIO_PADDR+XCHAL_KIO_BYPASS_VADDR);
	अन्यथा
		वापस xtensa_ioremap_nocache(offset, size);
पूर्ण

अटल अंतरभूत व्योम __iomem *ioremap_cache(अचिन्हित दीर्घ offset,
		अचिन्हित दीर्घ size)
अणु
	अगर (offset >= XCHAL_KIO_PADDR
	    && offset - XCHAL_KIO_PADDR < XCHAL_KIO_SIZE)
		वापस (व्योम*)(offset-XCHAL_KIO_PADDR+XCHAL_KIO_CACHED_VADDR);
	अन्यथा
		वापस xtensa_ioremap_cache(offset, size);
पूर्ण
#घोषणा ioremap_cache ioremap_cache

अटल अंतरभूत व्योम iounmap(अस्थिर व्योम __iomem *addr)
अणु
	अचिन्हित दीर्घ va = (अचिन्हित दीर्घ) addr;

	अगर (!(va >= XCHAL_KIO_CACHED_VADDR &&
	      va - XCHAL_KIO_CACHED_VADDR < XCHAL_KIO_SIZE) &&
	    !(va >= XCHAL_KIO_BYPASS_VADDR &&
	      va - XCHAL_KIO_BYPASS_VADDR < XCHAL_KIO_SIZE))
		xtensa_iounmap(addr);
पूर्ण

#घोषणा virt_to_bus     virt_to_phys
#घोषणा bus_to_virt     phys_to_virt

#पूर्ण_अगर /* CONFIG_MMU */

#समावेश <यंत्र-generic/पन.स>

#पूर्ण_अगर	/* _XTENSA_IO_H */
