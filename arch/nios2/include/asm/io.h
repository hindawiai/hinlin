<शैली गुरु>
/*
 * Copyright (C) 2014 Altera Corporation
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_IO_H
#घोषणा _ASM_NIOS2_IO_H

#समावेश <linux/types.h>
#समावेश <यंत्र/pgtable-bits.h>

/* PCI is not supported in nios2, set this to 0. */
#घोषणा IO_SPACE_LIMIT 0

#घोषणा पढ़ोb_relaxed(addr)	पढ़ोb(addr)
#घोषणा पढ़ोw_relaxed(addr)	पढ़ोw(addr)
#घोषणा पढ़ोl_relaxed(addr)	पढ़ोl(addr)

#घोषणा ग_लिखोb_relaxed(x, addr)	ग_लिखोb(x, addr)
#घोषणा ग_लिखोw_relaxed(x, addr)	ग_लिखोw(x, addr)
#घोषणा ग_लिखोl_relaxed(x, addr)	ग_लिखोl(x, addr)

व्योम __iomem *ioremap(अचिन्हित दीर्घ physaddr, अचिन्हित दीर्घ size);
व्योम iounmap(व्योम __iomem *addr);

/* Pages to physical address... */
#घोषणा page_to_phys(page)	virt_to_phys(page_to_virt(page))

/* Macros used क्रम converting between भव and physical mappings. */
#घोषणा phys_to_virt(vaddr)	\
	((व्योम *)((अचिन्हित दीर्घ)(vaddr) | CONFIG_NIOS2_KERNEL_REGION_BASE))
/* Clear top 3 bits */
#घोषणा virt_to_phys(vaddr)	\
	((अचिन्हित दीर्घ)((अचिन्हित दीर्घ)(vaddr) & ~0xE0000000))

#समावेश <यंत्र-generic/पन.स>

#पूर्ण_अगर /* _ASM_NIOS2_IO_H */
