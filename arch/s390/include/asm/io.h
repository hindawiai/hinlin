<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Derived from "include/asm-i386/io.h"
 */

#अगर_अघोषित _S390_IO_H
#घोषणा _S390_IO_H

#समावेश <linux/kernel.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgtable.h>
#समावेश <यंत्र/pci_पन.स>

#घोषणा xlate_dev_mem_ptr xlate_dev_mem_ptr
व्योम *xlate_dev_mem_ptr(phys_addr_t phys);
#घोषणा unxlate_dev_mem_ptr unxlate_dev_mem_ptr
व्योम unxlate_dev_mem_ptr(phys_addr_t phys, व्योम *addr);

#घोषणा IO_SPACE_LIMIT 0

व्योम __iomem *ioremap_prot(phys_addr_t addr, माप_प्रकार size, अचिन्हित दीर्घ prot);
व्योम __iomem *ioremap(phys_addr_t addr, माप_प्रकार size);
व्योम __iomem *ioremap_wc(phys_addr_t addr, माप_प्रकार size);
व्योम __iomem *ioremap_wt(phys_addr_t addr, माप_प्रकार size);
व्योम iounmap(अस्थिर व्योम __iomem *addr);

अटल अंतरभूत व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम ioport_unmap(व्योम __iomem *p)
अणु
पूर्ण

#अगर_घोषित CONFIG_PCI

/*
 * s390 needs a निजी implementation of pci_iomap since ioremap with its
 * offset parameter isn't sufficient. That's because BAR spaces are not
 * disjunctive on s390 so we need the bar parameter of pci_iomap to find
 * the corresponding device and create the mapping cookie.
 */
#घोषणा pci_iomap pci_iomap
#घोषणा pci_iomap_range pci_iomap_range
#घोषणा pci_iounmap pci_iounmap
#घोषणा pci_iomap_wc pci_iomap_wc
#घोषणा pci_iomap_wc_range pci_iomap_wc_range

#घोषणा ioremap ioremap
#घोषणा ioremap_wt ioremap_wt
#घोषणा ioremap_wc ioremap_wc

#घोषणा स_नकल_fromio(dst, src, count)	zpci_स_नकल_fromio(dst, src, count)
#घोषणा स_नकल_toio(dst, src, count)	zpci_स_नकल_toio(dst, src, count)
#घोषणा स_रखो_io(dst, val, count)	zpci_स_रखो_io(dst, val, count)

#घोषणा mmiowb()	zpci_barrier()

#घोषणा __raw_पढ़ोb	zpci_पढ़ो_u8
#घोषणा __raw_पढ़ोw	zpci_पढ़ो_u16
#घोषणा __raw_पढ़ोl	zpci_पढ़ो_u32
#घोषणा __raw_पढ़ोq	zpci_पढ़ो_u64
#घोषणा __raw_ग_लिखोb	zpci_ग_लिखो_u8
#घोषणा __raw_ग_लिखोw	zpci_ग_लिखो_u16
#घोषणा __raw_ग_लिखोl	zpci_ग_लिखो_u32
#घोषणा __raw_ग_लिखोq	zpci_ग_लिखो_u64

#पूर्ण_अगर /* CONFIG_PCI */

#समावेश <यंत्र-generic/पन.स>

#पूर्ण_अगर
