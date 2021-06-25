<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implement the sparc iomap पूर्णांकerfaces
 */
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/पन.स>

/* Create a भव mapping cookie क्रम an IO port range */
व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	वापस (व्योम __iomem *) (अचिन्हित दीर्घ) port;
पूर्ण

व्योम ioport_unmap(व्योम __iomem *addr)
अणु
	/* Nothing to करो */
पूर्ण
EXPORT_SYMBOL(ioport_map);
EXPORT_SYMBOL(ioport_unmap);

व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem * addr)
अणु
	/* nothing to करो */
पूर्ण
EXPORT_SYMBOL(pci_iounmap);
