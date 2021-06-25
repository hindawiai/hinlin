<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/pci.h>
#समावेश <linux/cache.h>
#समावेश <linux/init.h>
#समावेश <linux/swiotlb.h>
#समावेश <linux/memblock.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/mem_encrypt.h>

#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/swiotlb.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/xen/swiotlb-xen.h>
#समावेश <यंत्र/iommu_table.h>

पूर्णांक swiotlb __पढ़ो_mostly;

/*
 * pci_swiotlb_detect_override - set swiotlb to 1 अगर necessary
 *
 * This वापसs non-zero अगर we are क्रमced to use swiotlb (by the boot
 * option).
 */
पूर्णांक __init pci_swiotlb_detect_override(व्योम)
अणु
	अगर (swiotlb_क्रमce == SWIOTLB_FORCE)
		swiotlb = 1;

	वापस swiotlb;
पूर्ण
IOMMU_INIT_FINISH(pci_swiotlb_detect_override,
		  pci_xen_swiotlb_detect,
		  pci_swiotlb_init,
		  pci_swiotlb_late_init);

/*
 * If 4GB or more detected (and iommu=off not set) or अगर SME is active
 * then set swiotlb to 1 and वापस 1.
 */
पूर्णांक __init pci_swiotlb_detect_4gb(व्योम)
अणु
	/* करोn't initialize swiotlb अगर iommu=off (no_iommu=1) */
	अगर (!no_iommu && max_possible_pfn > MAX_DMA32_PFN)
		swiotlb = 1;

	/*
	 * If SME is active then swiotlb will be set to 1 so that bounce
	 * buffers are allocated and used क्रम devices that करो not support
	 * the addressing range required क्रम the encryption mask.
	 */
	अगर (sme_active())
		swiotlb = 1;

	वापस swiotlb;
पूर्ण
IOMMU_INIT(pci_swiotlb_detect_4gb,
	   pci_swiotlb_detect_override,
	   pci_swiotlb_init,
	   pci_swiotlb_late_init);

व्योम __init pci_swiotlb_init(व्योम)
अणु
	अगर (swiotlb)
		swiotlb_init(0);
पूर्ण

व्योम __init pci_swiotlb_late_init(व्योम)
अणु
	/* An IOMMU turned us off. */
	अगर (!swiotlb)
		swiotlb_निकास();
	अन्यथा अणु
		prपूर्णांकk(KERN_INFO "PCI-DMA: "
		       "Using software bounce buffering for IO (SWIOTLB)\n");
		swiotlb_prपूर्णांक_info();
	पूर्ण
पूर्ण
