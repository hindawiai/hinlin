<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_GART_H
#घोषणा _ASM_X86_GART_H

#समावेश <यंत्र/e820/api.h>

बाह्य व्योम set_up_gart_resume(u32, u32);

बाह्य पूर्णांक fallback_aper_order;
बाह्य पूर्णांक fallback_aper_क्रमce;
बाह्य पूर्णांक fix_aperture;

/* PTE bits. */
#घोषणा GPTE_VALID	1
#घोषणा GPTE_COHERENT	2

/* Aperture control रेजिस्टर bits. */
#घोषणा GARTEN		(1<<0)
#घोषणा DISGARTCPU	(1<<4)
#घोषणा DISGARTIO	(1<<5)
#घोषणा DISTLBWALKPRB	(1<<6)

/* GART cache control रेजिस्टर bits. */
#घोषणा INVGART		(1<<0)
#घोषणा GARTPTEERR	(1<<1)

/* K8 On-cpu GART रेजिस्टरs */
#घोषणा AMD64_GARTAPERTURECTL	0x90
#घोषणा AMD64_GARTAPERTUREBASE	0x94
#घोषणा AMD64_GARTTABLEBASE	0x98
#घोषणा AMD64_GARTCACHECTL	0x9c

#अगर_घोषित CONFIG_GART_IOMMU
बाह्य पूर्णांक gart_iommu_aperture;
बाह्य पूर्णांक gart_iommu_aperture_allowed;
बाह्य पूर्णांक gart_iommu_aperture_disabled;

बाह्य व्योम early_gart_iommu_check(व्योम);
बाह्य पूर्णांक gart_iommu_init(व्योम);
बाह्य व्योम __init gart_parse_options(अक्षर *);
बाह्य पूर्णांक gart_iommu_hole_init(व्योम);

#अन्यथा
#घोषणा gart_iommu_aperture            0
#घोषणा gart_iommu_aperture_allowed    0
#घोषणा gart_iommu_aperture_disabled   1

अटल अंतरभूत व्योम early_gart_iommu_check(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम gart_parse_options(अक्षर *options)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक gart_iommu_hole_init(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक agp_amd64_init(व्योम);

अटल अंतरभूत व्योम gart_set_size_and_enable(काष्ठा pci_dev *dev, u32 order)
अणु
	u32 ctl;

	/*
	 * Don't enable translation but enable GART IO and CPU accesses.
	 * Also, set DISTLBWALKPRB since GART tables memory is UC.
	 */
	ctl = order << 1;

	pci_ग_लिखो_config_dword(dev, AMD64_GARTAPERTURECTL, ctl);
पूर्ण

अटल अंतरभूत व्योम enable_gart_translation(काष्ठा pci_dev *dev, u64 addr)
अणु
	u32 पंचांगp, ctl;

	/* address of the mappings table */
	addr >>= 12;
	पंचांगp = (u32) addr<<4;
	पंचांगp &= ~0xf;
	pci_ग_लिखो_config_dword(dev, AMD64_GARTTABLEBASE, पंचांगp);

	/* Enable GART translation क्रम this hammer. */
	pci_पढ़ो_config_dword(dev, AMD64_GARTAPERTURECTL, &ctl);
	ctl |= GARTEN | DISTLBWALKPRB;
	ctl &= ~(DISGARTCPU | DISGARTIO);
	pci_ग_लिखो_config_dword(dev, AMD64_GARTAPERTURECTL, ctl);
पूर्ण

अटल अंतरभूत पूर्णांक aperture_valid(u64 aper_base, u32 aper_size, u32 min_size)
अणु
	अगर (!aper_base)
		वापस 0;

	अगर (aper_base + aper_size > 0x100000000ULL) अणु
		prपूर्णांकk(KERN_INFO "Aperture beyond 4GB. Ignoring.\n");
		वापस 0;
	पूर्ण
	अगर (e820__mapped_any(aper_base, aper_base + aper_size, E820_TYPE_RAM)) अणु
		prपूर्णांकk(KERN_INFO "Aperture pointing to e820 RAM. Ignoring.\n");
		वापस 0;
	पूर्ण
	अगर (aper_size < min_size) अणु
		prपूर्णांकk(KERN_INFO "Aperture too small (%d MB) than (%d MB)\n",
				 aper_size>>20, min_size>>20);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

#पूर्ण_अगर /* _ASM_X86_GART_H */
