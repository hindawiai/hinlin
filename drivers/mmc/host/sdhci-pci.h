<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SDHCI_PCI_H
#घोषणा __SDHCI_PCI_H

/*
 * PCI device IDs, sub IDs
 */

#घोषणा PCI_DEVICE_ID_O2_SDS0		0x8420
#घोषणा PCI_DEVICE_ID_O2_SDS1		0x8421
#घोषणा PCI_DEVICE_ID_O2_FUJIN2		0x8520
#घोषणा PCI_DEVICE_ID_O2_SEABIRD0	0x8620
#घोषणा PCI_DEVICE_ID_O2_SEABIRD1	0x8621

#घोषणा PCI_DEVICE_ID_INTEL_PCH_SDIO0	0x8809
#घोषणा PCI_DEVICE_ID_INTEL_PCH_SDIO1	0x880a
#घोषणा PCI_DEVICE_ID_INTEL_BYT_EMMC	0x0f14
#घोषणा PCI_DEVICE_ID_INTEL_BYT_SDIO	0x0f15
#घोषणा PCI_DEVICE_ID_INTEL_BYT_SD	0x0f16
#घोषणा PCI_DEVICE_ID_INTEL_BYT_EMMC2	0x0f50
#घोषणा PCI_DEVICE_ID_INTEL_BSW_EMMC	0x2294
#घोषणा PCI_DEVICE_ID_INTEL_BSW_SDIO	0x2295
#घोषणा PCI_DEVICE_ID_INTEL_BSW_SD	0x2296
#घोषणा PCI_DEVICE_ID_INTEL_MRFLD_MMC	0x1190
#घोषणा PCI_DEVICE_ID_INTEL_CLV_SDIO0	0x08f9
#घोषणा PCI_DEVICE_ID_INTEL_CLV_SDIO1	0x08fa
#घोषणा PCI_DEVICE_ID_INTEL_CLV_SDIO2	0x08fb
#घोषणा PCI_DEVICE_ID_INTEL_CLV_EMMC0	0x08e5
#घोषणा PCI_DEVICE_ID_INTEL_CLV_EMMC1	0x08e6
#घोषणा PCI_DEVICE_ID_INTEL_QRK_SD	0x08A7
#घोषणा PCI_DEVICE_ID_INTEL_SPT_EMMC	0x9d2b
#घोषणा PCI_DEVICE_ID_INTEL_SPT_SDIO	0x9d2c
#घोषणा PCI_DEVICE_ID_INTEL_SPT_SD	0x9d2d
#घोषणा PCI_DEVICE_ID_INTEL_DNV_EMMC	0x19db
#घोषणा PCI_DEVICE_ID_INTEL_CDF_EMMC	0x18db
#घोषणा PCI_DEVICE_ID_INTEL_BXT_SD	0x0aca
#घोषणा PCI_DEVICE_ID_INTEL_BXT_EMMC	0x0acc
#घोषणा PCI_DEVICE_ID_INTEL_BXT_SDIO	0x0ad0
#घोषणा PCI_DEVICE_ID_INTEL_BXTM_SD	0x1aca
#घोषणा PCI_DEVICE_ID_INTEL_BXTM_EMMC	0x1acc
#घोषणा PCI_DEVICE_ID_INTEL_BXTM_SDIO	0x1ad0
#घोषणा PCI_DEVICE_ID_INTEL_APL_SD	0x5aca
#घोषणा PCI_DEVICE_ID_INTEL_APL_EMMC	0x5acc
#घोषणा PCI_DEVICE_ID_INTEL_APL_SDIO	0x5ad0
#घोषणा PCI_DEVICE_ID_INTEL_GLK_SD	0x31ca
#घोषणा PCI_DEVICE_ID_INTEL_GLK_EMMC	0x31cc
#घोषणा PCI_DEVICE_ID_INTEL_GLK_SDIO	0x31d0
#घोषणा PCI_DEVICE_ID_INTEL_CNP_EMMC	0x9dc4
#घोषणा PCI_DEVICE_ID_INTEL_CNP_SD	0x9df5
#घोषणा PCI_DEVICE_ID_INTEL_CNPH_SD	0xa375
#घोषणा PCI_DEVICE_ID_INTEL_ICP_EMMC	0x34c4
#घोषणा PCI_DEVICE_ID_INTEL_ICP_SD	0x34f8
#घोषणा PCI_DEVICE_ID_INTEL_EHL_EMMC	0x4b47
#घोषणा PCI_DEVICE_ID_INTEL_EHL_SD	0x4b48
#घोषणा PCI_DEVICE_ID_INTEL_CML_EMMC	0x02c4
#घोषणा PCI_DEVICE_ID_INTEL_CML_SD	0x02f5
#घोषणा PCI_DEVICE_ID_INTEL_CMLH_SD	0x06f5
#घोषणा PCI_DEVICE_ID_INTEL_JSL_EMMC	0x4dc4
#घोषणा PCI_DEVICE_ID_INTEL_JSL_SD	0x4df8
#घोषणा PCI_DEVICE_ID_INTEL_LKF_EMMC	0x98c4
#घोषणा PCI_DEVICE_ID_INTEL_LKF_SD	0x98f8

#घोषणा PCI_DEVICE_ID_SYSKONNECT_8000	0x8000
#घोषणा PCI_DEVICE_ID_VIA_95D0		0x95d0
#घोषणा PCI_DEVICE_ID_REALTEK_5250	0x5250

#घोषणा PCI_SUBDEVICE_ID_NI_7884	0x7884
#घोषणा PCI_SUBDEVICE_ID_NI_78E3	0x78e3

#घोषणा PCI_VENDOR_ID_ARASAN		0x16e6
#घोषणा PCI_DEVICE_ID_ARASAN_PHY_EMMC	0x0670

#घोषणा PCI_DEVICE_ID_SYNOPSYS_DWC_MSHC 0xc202

#घोषणा PCI_DEVICE_ID_GLI_9755		0x9755
#घोषणा PCI_DEVICE_ID_GLI_9750		0x9750
#घोषणा PCI_DEVICE_ID_GLI_9763E		0xe763

/*
 * PCI device class and mask
 */

#घोषणा SYSTEM_SDHCI			(PCI_CLASS_SYSTEM_SDHCI << 8)
#घोषणा PCI_CLASS_MASK			0xFFFF00

/*
 * Macros क्रम PCI device-description
 */

#घोषणा _PCI_VEND(vend) PCI_VENDOR_ID_##vend
#घोषणा _PCI_DEV(vend, dev) PCI_DEVICE_ID_##vend##_##dev
#घोषणा _PCI_SUBDEV(subvend, subdev) PCI_SUBDEVICE_ID_##subvend##_##subdev

#घोषणा SDHCI_PCI_DEVICE(vend, dev, cfg) अणु \
	.venकरोr = _PCI_VEND(vend), .device = _PCI_DEV(vend, dev), \
	.subvenकरोr = PCI_ANY_ID, .subdevice = PCI_ANY_ID, \
	.driver_data = (kernel_uदीर्घ_t)&(sdhci_##cfg) \
पूर्ण

#घोषणा SDHCI_PCI_SUBDEVICE(vend, dev, subvend, subdev, cfg) अणु \
	.venकरोr = _PCI_VEND(vend), .device = _PCI_DEV(vend, dev), \
	.subvenकरोr = _PCI_VEND(subvend), \
	.subdevice = _PCI_SUBDEV(subvend, subdev), \
	.driver_data = (kernel_uदीर्घ_t)&(sdhci_##cfg) \
पूर्ण

#घोषणा SDHCI_PCI_DEVICE_CLASS(vend, cl, cl_msk, cfg) अणु \
	.venकरोr = _PCI_VEND(vend), .device = PCI_ANY_ID, \
	.subvenकरोr = PCI_ANY_ID, .subdevice = PCI_ANY_ID, \
	.class = (cl), .class_mask = (cl_msk), \
	.driver_data = (kernel_uदीर्घ_t)&(sdhci_##cfg) \
पूर्ण

/*
 * PCI रेजिस्टरs
 */

#घोषणा PCI_SDHCI_IFPIO			0x00
#घोषणा PCI_SDHCI_IFDMA			0x01
#घोषणा PCI_SDHCI_IFVENDOR		0x02

#घोषणा PCI_SLOT_INFO			0x40	/* 8 bits */
#घोषणा  PCI_SLOT_INFO_SLOTS(x)		((x >> 4) & 7)
#घोषणा  PCI_SLOT_INFO_FIRST_BAR_MASK	0x07

#घोषणा MAX_SLOTS			8

काष्ठा sdhci_pci_chip;
काष्ठा sdhci_pci_slot;

काष्ठा sdhci_pci_fixes अणु
	अचिन्हित पूर्णांक		quirks;
	अचिन्हित पूर्णांक		quirks2;
	bool			allow_runसमय_pm;
	bool			own_cd_क्रम_runसमय_pm;

	पूर्णांक			(*probe) (काष्ठा sdhci_pci_chip *);

	पूर्णांक			(*probe_slot) (काष्ठा sdhci_pci_slot *);
	पूर्णांक			(*add_host) (काष्ठा sdhci_pci_slot *);
	व्योम			(*हटाओ_slot) (काष्ठा sdhci_pci_slot *, पूर्णांक);

#अगर_घोषित CONFIG_PM_SLEEP
	पूर्णांक			(*suspend) (काष्ठा sdhci_pci_chip *);
	पूर्णांक			(*resume) (काष्ठा sdhci_pci_chip *);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM
	पूर्णांक			(*runसमय_suspend) (काष्ठा sdhci_pci_chip *);
	पूर्णांक			(*runसमय_resume) (काष्ठा sdhci_pci_chip *);
#पूर्ण_अगर

	स्थिर काष्ठा sdhci_ops	*ops;
	माप_प्रकार			priv_size;
पूर्ण;

काष्ठा sdhci_pci_slot अणु
	काष्ठा sdhci_pci_chip	*chip;
	काष्ठा sdhci_host	*host;
	काष्ठा sdhci_pci_data	*data;

	पूर्णांक			rst_n_gpio;
	पूर्णांक			cd_gpio;
	पूर्णांक			cd_irq;

	पूर्णांक			cd_idx;
	bool			cd_override_level;

	व्योम (*hw_reset)(काष्ठा sdhci_host *host);
	अचिन्हित दीर्घ		निजी[] ____cacheline_aligned;
पूर्ण;

काष्ठा sdhci_pci_chip अणु
	काष्ठा pci_dev		*pdev;

	अचिन्हित पूर्णांक		quirks;
	अचिन्हित पूर्णांक		quirks2;
	bool			allow_runसमय_pm;
	bool			pm_retune;
	bool			rpm_retune;
	स्थिर काष्ठा sdhci_pci_fixes *fixes;

	पूर्णांक			num_slots;	/* Slots on controller */
	काष्ठा sdhci_pci_slot	*slots[MAX_SLOTS]; /* Poपूर्णांकers to host slots */
पूर्ण;

अटल अंतरभूत व्योम *sdhci_pci_priv(काष्ठा sdhci_pci_slot *slot)
अणु
	वापस (व्योम *)slot->निजी;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक sdhci_pci_resume_host(काष्ठा sdhci_pci_chip *chip);
#पूर्ण_अगर
पूर्णांक sdhci_pci_enable_dma(काष्ठा sdhci_host *host);

बाह्य स्थिर काष्ठा sdhci_pci_fixes sdhci_arasan;
बाह्य स्थिर काष्ठा sdhci_pci_fixes sdhci_snps;
बाह्य स्थिर काष्ठा sdhci_pci_fixes sdhci_o2;
बाह्य स्थिर काष्ठा sdhci_pci_fixes sdhci_gl9750;
बाह्य स्थिर काष्ठा sdhci_pci_fixes sdhci_gl9755;
बाह्य स्थिर काष्ठा sdhci_pci_fixes sdhci_gl9763e;

#पूर्ण_अगर /* __SDHCI_PCI_H */
