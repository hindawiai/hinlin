<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2006 PathScale, Inc.  All Rights Reserved.
 */

#अगर_अघोषित _LINUX_IO_H
#घोषणा _LINUX_IO_H

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>

काष्ठा device;
काष्ठा resource;

__visible व्योम __ioग_लिखो32_copy(व्योम __iomem *to, स्थिर व्योम *from, माप_प्रकार count);
व्योम __ioपढ़ो32_copy(व्योम *to, स्थिर व्योम __iomem *from, माप_प्रकार count);
व्योम __ioग_लिखो64_copy(व्योम __iomem *to, स्थिर व्योम *from, माप_प्रकार count);

#अगर_घोषित CONFIG_MMU
पूर्णांक ioremap_page_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		       phys_addr_t phys_addr, pgprot_t prot);
#अन्यथा
अटल अंतरभूत पूर्णांक ioremap_page_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				     phys_addr_t phys_addr, pgprot_t prot)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Managed iomap पूर्णांकerface
 */
#अगर_घोषित CONFIG_HAS_IOPORT_MAP
व्योम __iomem * devm_ioport_map(काष्ठा device *dev, अचिन्हित दीर्घ port,
			       अचिन्हित पूर्णांक nr);
व्योम devm_ioport_unmap(काष्ठा device *dev, व्योम __iomem *addr);
#अन्यथा
अटल अंतरभूत व्योम __iomem *devm_ioport_map(काष्ठा device *dev,
					     अचिन्हित दीर्घ port,
					     अचिन्हित पूर्णांक nr)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम devm_ioport_unmap(काष्ठा device *dev, व्योम __iomem *addr)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा IOMEM_ERR_PTR(err) (__क्रमce व्योम __iomem *)ERR_PTR(err)

व्योम __iomem *devm_ioremap(काष्ठा device *dev, resource_माप_प्रकार offset,
			   resource_माप_प्रकार size);
व्योम __iomem *devm_ioremap_uc(काष्ठा device *dev, resource_माप_प्रकार offset,
				   resource_माप_प्रकार size);
व्योम __iomem *devm_ioremap_wc(काष्ठा device *dev, resource_माप_प्रकार offset,
				   resource_माप_प्रकार size);
व्योम __iomem *devm_ioremap_np(काष्ठा device *dev, resource_माप_प्रकार offset,
				   resource_माप_प्रकार size);
व्योम devm_iounmap(काष्ठा device *dev, व्योम __iomem *addr);
पूर्णांक check_signature(स्थिर अस्थिर व्योम __iomem *io_addr,
			स्थिर अचिन्हित अक्षर *signature, पूर्णांक length);
व्योम devm_ioremap_release(काष्ठा device *dev, व्योम *res);

व्योम *devm_memremap(काष्ठा device *dev, resource_माप_प्रकार offset,
		माप_प्रकार size, अचिन्हित दीर्घ flags);
व्योम devm_memunmap(काष्ठा device *dev, व्योम *addr);

#अगर_घोषित CONFIG_PCI
/*
 * The PCI specअगरications (Rev 3.0, 3.2.5 "Transaction Ordering and
 * Posting") mandate non-posted configuration transactions. This शेष
 * implementation attempts to use the ioremap_np() API to provide this
 * on arches that support it, and falls back to ioremap() on those that
 * करोn't. Overriding this function is deprecated; arches that properly
 * support non-posted accesses should implement ioremap_np() instead, which
 * this शेष implementation can then use to वापस mappings compliant with
 * the PCI specअगरication.
 */
#अगर_अघोषित pci_remap_cfgspace
#घोषणा pci_remap_cfgspace pci_remap_cfgspace
अटल अंतरभूत व्योम __iomem *pci_remap_cfgspace(phys_addr_t offset,
					       माप_प्रकार size)
अणु
	वापस ioremap_np(offset, size) ?: ioremap(offset, size);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * Some प्रणालीs करो not have legacy ISA devices.
 * /dev/port is not a valid पूर्णांकerface on these प्रणालीs.
 * So क्रम those archs, <यंत्र/पन.स> should define the following symbol.
 */
#अगर_अघोषित arch_has_dev_port
#घोषणा arch_has_dev_port()     (1)
#पूर्ण_अगर

/*
 * Some प्रणालीs (x86 without PAT) have a somewhat reliable way to mark a
 * physical address range such that uncached mappings will actually
 * end up ग_लिखो-combining.  This facility should be used in conjunction
 * with pgprot_ग_लिखोcombine, ioremap-wc, or set_memory_wc, since it has
 * no effect अगर the per-page mechanisms are functional.
 * (On x86 without PAT, these functions manipulate MTRRs.)
 *
 * arch_phys_del_wc(0) or arch_phys_del_wc(any error code) is guaranteed
 * to have no effect.
 */
#अगर_अघोषित arch_phys_wc_add
अटल अंतरभूत पूर्णांक __must_check arch_phys_wc_add(अचिन्हित दीर्घ base,
						अचिन्हित दीर्घ size)
अणु
	वापस 0;  /* It worked (i.e. did nothing). */
पूर्ण

अटल अंतरभूत व्योम arch_phys_wc_del(पूर्णांक handle)
अणु
पूर्ण

#घोषणा arch_phys_wc_add arch_phys_wc_add
#अगर_अघोषित arch_phys_wc_index
अटल अंतरभूत पूर्णांक arch_phys_wc_index(पूर्णांक handle)
अणु
	वापस -1;
पूर्ण
#घोषणा arch_phys_wc_index arch_phys_wc_index
#पूर्ण_अगर
#पूर्ण_अगर

क्रमागत अणु
	/* See memremap() kernel-करोc क्रम usage description... */
	MEMREMAP_WB = 1 << 0,
	MEMREMAP_WT = 1 << 1,
	MEMREMAP_WC = 1 << 2,
	MEMREMAP_ENC = 1 << 3,
	MEMREMAP_DEC = 1 << 4,
पूर्ण;

व्योम *memremap(resource_माप_प्रकार offset, माप_प्रकार size, अचिन्हित दीर्घ flags);
व्योम memunmap(व्योम *addr);

/*
 * On x86 PAT प्रणालीs we have memory tracking that keeps track of
 * the allowed mappings on memory ranges. This tracking works क्रम
 * all the in-kernel mapping APIs (ioremap*), but where the user
 * wishes to map a range from a physical device पूर्णांकo user memory
 * the tracking won't be updated. This API is to be used by
 * drivers which remap physical device pages पूर्णांकo userspace,
 * and wants to make sure they are mapped WC and not UC.
 */
#अगर_अघोषित arch_io_reserve_memtype_wc
अटल अंतरभूत पूर्णांक arch_io_reserve_memtype_wc(resource_माप_प्रकार base,
					     resource_माप_प्रकार size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम arch_io_मुक्त_memtype_wc(resource_माप_प्रकार base,
					   resource_माप_प्रकार size)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_IO_H */
