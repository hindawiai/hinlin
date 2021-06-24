<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68KNOMMU_IO_H
#घोषणा _M68KNOMMU_IO_H

/*
 * Convert a physical memory address पूर्णांकo a IO memory address.
 * For us this is trivially a type cast.
 */
#घोषणा iomem(a)	((व्योम __iomem *) (a))

/*
 * The non-MMU m68k and ColdFire IO and memory mapped hardware access
 * functions have always worked in CPU native endian. We need to define
 * that behavior here first beक्रमe we include यंत्र-generic/पन.स.
 */
#घोषणा __raw_पढ़ोb(addr) \
    (अणु u8 __v = (*(__क्रमce अस्थिर u8 *) (addr)); __v; पूर्ण)
#घोषणा __raw_पढ़ोw(addr) \
    (अणु u16 __v = (*(__क्रमce अस्थिर u16 *) (addr)); __v; पूर्ण)
#घोषणा __raw_पढ़ोl(addr) \
    (अणु u32 __v = (*(__क्रमce अस्थिर u32 *) (addr)); __v; पूर्ण)

#घोषणा __raw_ग_लिखोb(b, addr) (व्योम)((*(__क्रमce अस्थिर u8 *) (addr)) = (b))
#घोषणा __raw_ग_लिखोw(b, addr) (व्योम)((*(__क्रमce अस्थिर u16 *) (addr)) = (b))
#घोषणा __raw_ग_लिखोl(b, addr) (व्योम)((*(__क्रमce अस्थिर u32 *) (addr)) = (b))

#अगर defined(CONFIG_COLDFIRE)
/*
 * For ColdFire platक्रमms we may need to करो some extra checks क्रम what
 * type of address range we are accessing. Include the ColdFire platक्रमm
 * definitions so we can figure out अगर need to करो something special.
 */
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#पूर्ण_अगर /* CONFIG_COLDFIRE */

#अगर defined(IOMEMBASE)
/*
 * The ColdFire SoC पूर्णांकernal peripherals are mapped पूर्णांकo भव address
 * space using the ACR रेजिस्टरs of the cache control unit. This means we
 * are using a 1:1 physical:भव mapping क्रम them. We can quickly
 * determine अगर we are accessing an पूर्णांकernal peripheral device given the
 * physical or vitrual address using the same range check. This check logic
 * applies just the same of there is no MMU but something like a PCI bus
 * is present.
 */
अटल पूर्णांक __cf_पूर्णांकernalio(अचिन्हित दीर्घ addr)
अणु
	वापस (addr >= IOMEMBASE) && (addr <= IOMEMBASE + IOMEMSIZE - 1);
पूर्ण

अटल पूर्णांक cf_पूर्णांकernalio(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस __cf_पूर्णांकernalio((अचिन्हित दीर्घ) addr);
पूर्ण

/*
 * We need to treat built-in peripherals and bus based address ranges
 * dअगरferently. Local built-in peripherals (and the ColdFire SoC parts
 * have quite a lot of them) are always native endian - which is big
 * endian on m68k/ColdFire. Bus based address ranges, like the PCI bus,
 * are accessed little endian - so we need to byte swap those.
 */
#घोषणा पढ़ोw पढ़ोw
अटल अंतरभूत u16 पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	अगर (cf_पूर्णांकernalio(addr))
		वापस __raw_पढ़ोw(addr);
	वापस swab16(__raw_पढ़ोw(addr));
पूर्ण

#घोषणा पढ़ोl पढ़ोl
अटल अंतरभूत u32 पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	अगर (cf_पूर्णांकernalio(addr))
		वापस __raw_पढ़ोl(addr);
	वापस swab32(__raw_पढ़ोl(addr));
पूर्ण

#घोषणा ग_लिखोw ग_लिखोw
अटल अंतरभूत व्योम ग_लिखोw(u16 value, अस्थिर व्योम __iomem *addr)
अणु
	अगर (cf_पूर्णांकernalio(addr))
		__raw_ग_लिखोw(value, addr);
	अन्यथा
		__raw_ग_लिखोw(swab16(value), addr);
पूर्ण

#घोषणा ग_लिखोl ग_लिखोl
अटल अंतरभूत व्योम ग_लिखोl(u32 value, अस्थिर व्योम __iomem *addr)
अणु
	अगर (cf_पूर्णांकernalio(addr))
		__raw_ग_लिखोl(value, addr);
	अन्यथा
		__raw_ग_लिखोl(swab32(value), addr);
पूर्ण

#अन्यथा

#घोषणा पढ़ोb __raw_पढ़ोb
#घोषणा पढ़ोw __raw_पढ़ोw
#घोषणा पढ़ोl __raw_पढ़ोl
#घोषणा ग_लिखोb __raw_ग_लिखोb
#घोषणा ग_लिखोw __raw_ग_लिखोw
#घोषणा ग_लिखोl __raw_ग_लिखोl

#पूर्ण_अगर /* IOMEMBASE */

#अगर defined(CONFIG_PCI)
/*
 * Support क्रम PCI bus access uses the यंत्र-generic access functions.
 * We need to supply the base address and masks क्रम the normal memory
 * and IO address space mappings.
 */
#घोषणा PCI_MEM_PA	0xf0000000		/* Host physical address */
#घोषणा PCI_MEM_BA	0xf0000000		/* Bus physical address */
#घोषणा PCI_MEM_SIZE	0x08000000		/* 128 MB */
#घोषणा PCI_MEM_MASK	(PCI_MEM_SIZE - 1)

#घोषणा PCI_IO_PA	0xf8000000		/* Host physical address */
#घोषणा PCI_IO_BA	0x00000000		/* Bus physical address */
#घोषणा PCI_IO_SIZE	0x00010000		/* 64k */
#घोषणा PCI_IO_MASK	(PCI_IO_SIZE - 1)

#घोषणा HAVE_ARCH_PIO_SIZE
#घोषणा PIO_OFFSET	0
#घोषणा PIO_MASK	0xffff
#घोषणा PIO_RESERVED	0x10000
#घोषणा PCI_IOBASE	((व्योम __iomem *) PCI_IO_PA)
#घोषणा PCI_SPACE_LIMIT	PCI_IO_MASK
#पूर्ण_अगर /* CONFIG_PCI */

#समावेश <यंत्र/kmap.h>
#समावेश <यंत्र/virtconvert.h>

#पूर्ण_अगर /* _M68KNOMMU_IO_H */
