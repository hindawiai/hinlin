<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_IO_H
#घोषणा _ASM_MICROBLAZE_IO_H

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>          /* Get काष्ठा page अणु...पूर्ण */

#अगर_अघोषित CONFIG_PCI
#घोषणा _IO_BASE	0
#घोषणा _ISA_MEM_BASE	0
#अन्यथा
#घोषणा _IO_BASE	isa_io_base
#घोषणा _ISA_MEM_BASE	isa_mem_base
काष्ठा pci_dev;
बाह्य व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *);
#घोषणा pci_iounmap pci_iounmap

बाह्य अचिन्हित दीर्घ isa_io_base;
बाह्य resource_माप_प्रकार isa_mem_base;
#पूर्ण_अगर

#घोषणा PCI_IOBASE	((व्योम __iomem *)_IO_BASE)
#घोषणा IO_SPACE_LIMIT (0xFFFFFFFF)

#घोषणा page_to_bus(page)	(page_to_phys(page))

बाह्य व्योम iounmap(अस्थिर व्योम __iomem *addr);

बाह्य व्योम __iomem *ioremap(phys_addr_t address, अचिन्हित दीर्घ size);

/* Big Endian */
#घोषणा out_be32(a, v) __raw_ग_लिखोl((v), (व्योम __iomem __क्रमce *)(a))
#घोषणा out_be16(a, v) __raw_ग_लिखोw((v), (a))

#घोषणा in_be32(a) __raw_पढ़ोl((स्थिर व्योम __iomem __क्रमce *)(a))
#घोषणा in_be16(a) __raw_पढ़ोw(a)

#घोषणा ग_लिखोl_be(v, a)	out_be32((__क्रमce अचिन्हित *)a, v)
#घोषणा पढ़ोl_be(a)	in_be32((__क्रमce अचिन्हित *)a)

/* Little endian */
#घोषणा out_le32(a, v) __raw_ग_लिखोl(__cpu_to_le32(v), (a))
#घोषणा out_le16(a, v) __raw_ग_लिखोw(__cpu_to_le16(v), (a))

#घोषणा in_le32(a) __le32_to_cpu(__raw_पढ़ोl(a))
#घोषणा in_le16(a) __le16_to_cpu(__raw_पढ़ोw(a))

/* Byte ops */
#घोषणा out_8(a, v) __raw_ग_लिखोb((v), (a))
#घोषणा in_8(a) __raw_पढ़ोb(a)

#समावेश <यंत्र-generic/पन.स>

#पूर्ण_अगर /* _ASM_MICROBLAZE_IO_H */
