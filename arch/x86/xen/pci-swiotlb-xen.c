<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Glue code to lib/swiotlb-xen.c */

#समावेश <linux/dma-map-ops.h>
#समावेश <linux/pci.h>
#समावेश <xen/swiotlb-xen.h>

#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <xen/xen.h>
#समावेश <यंत्र/iommu_table.h>


#समावेश <यंत्र/xen/swiotlb-xen.h>
#अगर_घोषित CONFIG_X86_64
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/dma.h>
#पूर्ण_अगर
#समावेश <linux/export.h>

पूर्णांक xen_swiotlb __पढ़ो_mostly;

/*
 * pci_xen_swiotlb_detect - set xen_swiotlb to 1 अगर necessary
 *
 * This वापसs non-zero अगर we are क्रमced to use xen_swiotlb (by the boot
 * option).
 */
पूर्णांक __init pci_xen_swiotlb_detect(व्योम)
अणु

	अगर (!xen_pv_करोमुख्य())
		वापस 0;

	/* If running as PV guest, either iommu=soft, or swiotlb=क्रमce will
	 * activate this IOMMU. If running as PV privileged, activate it
	 * irregardless.
	 */
	अगर (xen_initial_करोमुख्य() || swiotlb || swiotlb_क्रमce == SWIOTLB_FORCE)
		xen_swiotlb = 1;

	/* If we are running under Xen, we MUST disable the native SWIOTLB.
	 * Don't worry about swiotlb_क्रमce flag activating the native, as
	 * the 'swiotlb' flag is the only one turning it on. */
	swiotlb = 0;

#अगर_घोषित CONFIG_X86_64
	/* pci_swiotlb_detect_4gb turns on native SWIOTLB अगर no_iommu == 0
	 * (so no iommu=X command line over-ग_लिखोs).
	 * Considering that PV guests करो not want the *native SWIOTLB* but
	 * only Xen SWIOTLB it is not useful to us so set no_iommu=1 here.
	 */
	अगर (max_pfn > MAX_DMA32_PFN)
		no_iommu = 1;
#पूर्ण_अगर
	वापस xen_swiotlb;
पूर्ण

व्योम __init pci_xen_swiotlb_init(व्योम)
अणु
	अगर (xen_swiotlb) अणु
		xen_swiotlb_init_early();
		dma_ops = &xen_swiotlb_dma_ops;

#अगर_घोषित CONFIG_PCI
		/* Make sure ACS will be enabled */
		pci_request_acs();
#पूर्ण_अगर
	पूर्ण
पूर्ण

पूर्णांक pci_xen_swiotlb_init_late(व्योम)
अणु
	पूर्णांक rc;

	अगर (xen_swiotlb)
		वापस 0;

	rc = xen_swiotlb_init();
	अगर (rc)
		वापस rc;

	dma_ops = &xen_swiotlb_dma_ops;
#अगर_घोषित CONFIG_PCI
	/* Make sure ACS will be enabled */
	pci_request_acs();
#पूर्ण_अगर

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_xen_swiotlb_init_late);

IOMMU_INIT_FINISH(pci_xen_swiotlb_detect,
		  शून्य,
		  pci_xen_swiotlb_init,
		  शून्य);
