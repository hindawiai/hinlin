<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __GENERIC_IO_H
#घोषणा __GENERIC_IO_H

#समावेश <linux/linkage.h>
#समावेश <यंत्र/byteorder.h>

/*
 * These are the "generic" पूर्णांकerfaces क्रम करोing new-style
 * memory-mapped or PIO accesses. Architectures may करो
 * their own arch-optimized versions, these just act as
 * wrappers around the old-style IO रेजिस्टर access functions:
 * पढ़ो[bwl]/ग_लिखो[bwl]/in[bwl]/out[bwl]
 *
 * Don't include this directly, include it from <यंत्र/पन.स>.
 */

/*
 * Read/ग_लिखो from/to an (offsettable) iomem cookie. It might be a PIO
 * access or a MMIO access, these functions करोn't care. The info is
 * encoded in the hardware mapping set up by the mapping functions
 * (or the cookie itself, depending on implementation and hw).
 *
 * The generic routines just encode the PIO/MMIO as part of the
 * cookie, and coldly assume that the MMIO IO mappings are not
 * in the low address range. Architectures क्रम which this is not
 * true can't use this generic implementation.
 */
बाह्य अचिन्हित पूर्णांक ioपढ़ो8(स्थिर व्योम __iomem *);
बाह्य अचिन्हित पूर्णांक ioपढ़ो16(स्थिर व्योम __iomem *);
बाह्य अचिन्हित पूर्णांक ioपढ़ो16be(स्थिर व्योम __iomem *);
बाह्य अचिन्हित पूर्णांक ioपढ़ो32(स्थिर व्योम __iomem *);
बाह्य अचिन्हित पूर्णांक ioपढ़ो32be(स्थिर व्योम __iomem *);
#अगर_घोषित CONFIG_64BIT
बाह्य u64 ioपढ़ो64(स्थिर व्योम __iomem *);
बाह्य u64 ioपढ़ो64be(स्थिर व्योम __iomem *);
#पूर्ण_अगर

#अगर_घोषित पढ़ोq
#घोषणा ioपढ़ो64_lo_hi ioपढ़ो64_lo_hi
#घोषणा ioपढ़ो64_hi_lo ioपढ़ो64_hi_lo
#घोषणा ioपढ़ो64be_lo_hi ioपढ़ो64be_lo_hi
#घोषणा ioपढ़ो64be_hi_lo ioपढ़ो64be_hi_lo
बाह्य u64 ioपढ़ो64_lo_hi(स्थिर व्योम __iomem *addr);
बाह्य u64 ioपढ़ो64_hi_lo(स्थिर व्योम __iomem *addr);
बाह्य u64 ioपढ़ो64be_lo_hi(स्थिर व्योम __iomem *addr);
बाह्य u64 ioपढ़ो64be_hi_lo(स्थिर व्योम __iomem *addr);
#पूर्ण_अगर

बाह्य व्योम ioग_लिखो8(u8, व्योम __iomem *);
बाह्य व्योम ioग_लिखो16(u16, व्योम __iomem *);
बाह्य व्योम ioग_लिखो16be(u16, व्योम __iomem *);
बाह्य व्योम ioग_लिखो32(u32, व्योम __iomem *);
बाह्य व्योम ioग_लिखो32be(u32, व्योम __iomem *);
#अगर_घोषित CONFIG_64BIT
बाह्य व्योम ioग_लिखो64(u64, व्योम __iomem *);
बाह्य व्योम ioग_लिखो64be(u64, व्योम __iomem *);
#पूर्ण_अगर

#अगर_घोषित ग_लिखोq
#घोषणा ioग_लिखो64_lo_hi ioग_लिखो64_lo_hi
#घोषणा ioग_लिखो64_hi_lo ioग_लिखो64_hi_lo
#घोषणा ioग_लिखो64be_lo_hi ioग_लिखो64be_lo_hi
#घोषणा ioग_लिखो64be_hi_lo ioग_लिखो64be_hi_lo
बाह्य व्योम ioग_लिखो64_lo_hi(u64 val, व्योम __iomem *addr);
बाह्य व्योम ioग_लिखो64_hi_lo(u64 val, व्योम __iomem *addr);
बाह्य व्योम ioग_लिखो64be_lo_hi(u64 val, व्योम __iomem *addr);
बाह्य व्योम ioग_लिखो64be_hi_lo(u64 val, व्योम __iomem *addr);
#पूर्ण_अगर

/*
 * "string" versions of the above. Note that they
 * use native byte ordering क्रम the accesses (on
 * the assumption that IO and memory agree on a
 * byte order, and CPU byteorder is irrelevant).
 *
 * They करो _not_ update the port address. If you
 * want MMIO that copies stuff laid out in MMIO
 * memory across multiple ports, use "memcpy_toio()"
 * and मित्रs.
 */
बाह्य व्योम ioपढ़ो8_rep(स्थिर व्योम __iomem *port, व्योम *buf, अचिन्हित दीर्घ count);
बाह्य व्योम ioपढ़ो16_rep(स्थिर व्योम __iomem *port, व्योम *buf, अचिन्हित दीर्घ count);
बाह्य व्योम ioपढ़ो32_rep(स्थिर व्योम __iomem *port, व्योम *buf, अचिन्हित दीर्घ count);

बाह्य व्योम ioग_लिखो8_rep(व्योम __iomem *port, स्थिर व्योम *buf, अचिन्हित दीर्घ count);
बाह्य व्योम ioग_लिखो16_rep(व्योम __iomem *port, स्थिर व्योम *buf, अचिन्हित दीर्घ count);
बाह्य व्योम ioग_लिखो32_rep(व्योम __iomem *port, स्थिर व्योम *buf, अचिन्हित दीर्घ count);

#अगर_घोषित CONFIG_HAS_IOPORT_MAP
/* Create a भव mapping cookie क्रम an IO port range */
बाह्य व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr);
बाह्य व्योम ioport_unmap(व्योम __iomem *);
#पूर्ण_अगर

#अगर_अघोषित ARCH_HAS_IOREMAP_WC
#घोषणा ioremap_wc ioremap
#पूर्ण_अगर

#अगर_अघोषित ARCH_HAS_IOREMAP_WT
#घोषणा ioremap_wt ioremap
#पूर्ण_अगर

#अगर_अघोषित ARCH_HAS_IOREMAP_NP
/* See the comment in यंत्र-generic/पन.स about ioremap_np(). */
#घोषणा ioremap_np ioremap_np
अटल अंतरभूत व्योम __iomem *ioremap_np(phys_addr_t offset, माप_प्रकार size)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
/* Destroy a भव mapping cookie क्रम a PCI BAR (memory or IO) */
काष्ठा pci_dev;
बाह्य व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *);
#या_अगर defined(CONFIG_GENERIC_IOMAP)
काष्ठा pci_dev;
अटल अंतरभूत व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *addr)
अणु पूर्ण
#पूर्ण_अगर

#समावेश <यंत्र-generic/pci_iomap.h>

#पूर्ण_अगर
