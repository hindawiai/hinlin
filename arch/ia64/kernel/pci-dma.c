<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dynamic DMA mapping support.
 */

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/dmar.h>
#समावेश <यंत्र/iommu.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/page.h>

पूर्णांक no_iommu __पढ़ो_mostly;
#अगर_घोषित CONFIG_IOMMU_DEBUG
पूर्णांक क्रमce_iommu __पढ़ो_mostly = 1;
#अन्यथा
पूर्णांक क्रमce_iommu __पढ़ो_mostly;
#पूर्ण_अगर

अटल पूर्णांक __init pci_iommu_init(व्योम)
अणु
	अगर (iommu_detected)
		पूर्णांकel_iommu_init();

	वापस 0;
पूर्ण

/* Must execute after PCI subप्रणाली */
fs_initcall(pci_iommu_init);
