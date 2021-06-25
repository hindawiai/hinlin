<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/iommu.h>
#समावेश <linux/dmar.h>
#समावेश <linux/export.h>
#समावेश <linux/memblock.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/gart.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/iommu_table.h>

अटल bool disable_dac_quirk __पढ़ो_mostly;

स्थिर काष्ठा dma_map_ops *dma_ops;
EXPORT_SYMBOL(dma_ops);

#अगर_घोषित CONFIG_IOMMU_DEBUG
पूर्णांक panic_on_overflow __पढ़ो_mostly = 1;
पूर्णांक क्रमce_iommu __पढ़ो_mostly = 1;
#अन्यथा
पूर्णांक panic_on_overflow __पढ़ो_mostly = 0;
पूर्णांक क्रमce_iommu __पढ़ो_mostly = 0;
#पूर्ण_अगर

पूर्णांक iommu_merge __पढ़ो_mostly = 0;

पूर्णांक no_iommu __पढ़ो_mostly;
/* Set this to 1 अगर there is a HW IOMMU in the प्रणाली */
पूर्णांक iommu_detected __पढ़ो_mostly = 0;

बाह्य काष्ठा iommu_table_entry __iommu_table[], __iommu_table_end[];

व्योम __init pci_iommu_alloc(व्योम)
अणु
	काष्ठा iommu_table_entry *p;

	sort_iommu_table(__iommu_table, __iommu_table_end);
	check_iommu_entries(__iommu_table, __iommu_table_end);

	क्रम (p = __iommu_table; p < __iommu_table_end; p++) अणु
		अगर (p && p->detect && p->detect() > 0) अणु
			p->flags |= IOMMU_DETECTED;
			अगर (p->early_init)
				p->early_init();
			अगर (p->flags & IOMMU_FINISH_IF_DETECTED)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * See <Documentation/x86/x86_64/boot-options.rst> क्रम the iommu kernel
 * parameter करोcumentation.
 */
अटल __init पूर्णांक iommu_setup(अक्षर *p)
अणु
	iommu_merge = 1;

	अगर (!p)
		वापस -EINVAL;

	जबतक (*p) अणु
		अगर (!म_भेदन(p, "off", 3))
			no_iommu = 1;
		/* gart_parse_options has more क्रमce support */
		अगर (!म_भेदन(p, "force", 5))
			क्रमce_iommu = 1;
		अगर (!म_भेदन(p, "noforce", 7)) अणु
			iommu_merge = 0;
			क्रमce_iommu = 0;
		पूर्ण

		अगर (!म_भेदन(p, "biomerge", 8)) अणु
			iommu_merge = 1;
			क्रमce_iommu = 1;
		पूर्ण
		अगर (!म_भेदन(p, "panic", 5))
			panic_on_overflow = 1;
		अगर (!म_भेदन(p, "nopanic", 7))
			panic_on_overflow = 0;
		अगर (!म_भेदन(p, "merge", 5)) अणु
			iommu_merge = 1;
			क्रमce_iommu = 1;
		पूर्ण
		अगर (!म_भेदन(p, "nomerge", 7))
			iommu_merge = 0;
		अगर (!म_भेदन(p, "forcesac", 8))
			pr_warn("forcesac option ignored.\n");
		अगर (!म_भेदन(p, "allowdac", 8))
			pr_warn("allowdac option ignored.\n");
		अगर (!म_भेदन(p, "nodac", 5))
			pr_warn("nodac option ignored.\n");
		अगर (!म_भेदन(p, "usedac", 6)) अणु
			disable_dac_quirk = true;
			वापस 1;
		पूर्ण
#अगर_घोषित CONFIG_SWIOTLB
		अगर (!म_भेदन(p, "soft", 4))
			swiotlb = 1;
#पूर्ण_अगर
		अगर (!म_भेदन(p, "pt", 2))
			iommu_set_शेष_passthrough(true);
		अगर (!म_भेदन(p, "nopt", 4))
			iommu_set_शेष_translated(true);

		gart_parse_options(p);

		p += म_खोज(p, ",");
		अगर (*p == ',')
			++p;
	पूर्ण
	वापस 0;
पूर्ण
early_param("iommu", iommu_setup);

अटल पूर्णांक __init pci_iommu_init(व्योम)
अणु
	काष्ठा iommu_table_entry *p;

	x86_init.iommu.iommu_init();

	क्रम (p = __iommu_table; p < __iommu_table_end; p++) अणु
		अगर (p && (p->flags & IOMMU_DETECTED) && p->late_init)
			p->late_init();
	पूर्ण

	वापस 0;
पूर्ण
/* Must execute after PCI subप्रणाली */
rootfs_initcall(pci_iommu_init);

#अगर_घोषित CONFIG_PCI
/* Many VIA bridges seem to corrupt data क्रम DAC. Disable it here */

अटल पूर्णांक via_no_dac_cb(काष्ठा pci_dev *pdev, व्योम *data)
अणु
	pdev->dev.bus_dma_limit = DMA_BIT_MASK(32);
	वापस 0;
पूर्ण

अटल व्योम via_no_dac(काष्ठा pci_dev *dev)
अणु
	अगर (!disable_dac_quirk) अणु
		dev_info(&dev->dev, "disabling DAC on VIA PCI bridge\n");
		pci_walk_bus(dev->subordinate, via_no_dac_cb, शून्य);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_VENDOR_ID_VIA, PCI_ANY_ID,
				PCI_CLASS_BRIDGE_PCI, 8, via_no_dac);
#पूर्ण_अगर
