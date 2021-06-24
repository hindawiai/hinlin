<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_BCMA_PRIVATE_H_
#घोषणा LINUX_BCMA_PRIVATE_H_

#अगर_अघोषित pr_fmt
#घोषणा pr_fmt(fmt)		KBUILD_MODNAME ": " fmt
#पूर्ण_अगर

#समावेश <linux/bcma/bcma.h>
#समावेश <linux/delay.h>

#घोषणा bcma_err(bus, fmt, ...) \
	dev_err((bus)->dev, "bus%d: " fmt, (bus)->num, ##__VA_ARGS__)
#घोषणा bcma_warn(bus, fmt, ...) \
	dev_warn((bus)->dev, "bus%d: " fmt, (bus)->num, ##__VA_ARGS__)
#घोषणा bcma_info(bus, fmt, ...) \
	dev_info((bus)->dev, "bus%d: " fmt, (bus)->num, ##__VA_ARGS__)
#घोषणा bcma_debug(bus, fmt, ...) \
	dev_dbg((bus)->dev, "bus%d: " fmt, (bus)->num, ##__VA_ARGS__)

काष्ठा bcma_bus;

/* मुख्य.c */
bool bcma_रुको_value(काष्ठा bcma_device *core, u16 reg, u32 mask, u32 value,
		     पूर्णांक समयout);
व्योम bcma_prepare_core(काष्ठा bcma_bus *bus, काष्ठा bcma_device *core);
व्योम bcma_init_bus(काष्ठा bcma_bus *bus);
व्योम bcma_unरेजिस्टर_cores(काष्ठा bcma_bus *bus);
पूर्णांक bcma_bus_रेजिस्टर(काष्ठा bcma_bus *bus);
व्योम bcma_bus_unरेजिस्टर(काष्ठा bcma_bus *bus);
पूर्णांक __init bcma_bus_early_रेजिस्टर(काष्ठा bcma_bus *bus);
#अगर_घोषित CONFIG_PM
पूर्णांक bcma_bus_suspend(काष्ठा bcma_bus *bus);
पूर्णांक bcma_bus_resume(काष्ठा bcma_bus *bus);
#पूर्ण_अगर

/* scan.c */
व्योम bcma_detect_chip(काष्ठा bcma_bus *bus);
पूर्णांक bcma_bus_scan(काष्ठा bcma_bus *bus);

/* sprom.c */
पूर्णांक bcma_sprom_get(काष्ठा bcma_bus *bus);

/* driver_chipcommon.c */
व्योम bcma_core_chipcommon_early_init(काष्ठा bcma_drv_cc *cc);
व्योम bcma_core_chipcommon_init(काष्ठा bcma_drv_cc *cc);
व्योम bcma_chipco_bcm4331_ext_pa_lines_ctl(काष्ठा bcma_drv_cc *cc, bool enable);
#अगर_घोषित CONFIG_BCMA_DRIVER_MIPS
व्योम bcma_chipco_serial_init(काष्ठा bcma_drv_cc *cc);
#पूर्ण_अगर /* CONFIG_BCMA_DRIVER_MIPS */

/* driver_chipcommon_b.c */
पूर्णांक bcma_core_chipcommon_b_init(काष्ठा bcma_drv_cc_b *ccb);
व्योम bcma_core_chipcommon_b_मुक्त(काष्ठा bcma_drv_cc_b *ccb);

/* driver_chipcommon_pmu.c */
व्योम bcma_pmu_early_init(काष्ठा bcma_drv_cc *cc);
व्योम bcma_pmu_init(काष्ठा bcma_drv_cc *cc);
u32 bcma_pmu_get_alp_घड़ी(काष्ठा bcma_drv_cc *cc);
u32 bcma_pmu_get_cpu_घड़ी(काष्ठा bcma_drv_cc *cc);

/**************************************************
 * driver_chipcommon_sflash.c
 **************************************************/

#अगर_घोषित CONFIG_BCMA_PFLASH
बाह्य काष्ठा platक्रमm_device bcma_pflash_dev;
पूर्णांक bcma_pflash_init(काष्ठा bcma_drv_cc *cc);
#अन्यथा
अटल अंतरभूत पूर्णांक bcma_pflash_init(काष्ठा bcma_drv_cc *cc)
अणु
	bcma_err(cc->core->bus, "Parallel flash not supported\n");
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_BCMA_PFLASH */

#अगर_घोषित CONFIG_BCMA_SFLASH
/* driver_chipcommon_sflash.c */
पूर्णांक bcma_sflash_init(काष्ठा bcma_drv_cc *cc);
बाह्य काष्ठा platक्रमm_device bcma_sflash_dev;
#अन्यथा
अटल अंतरभूत पूर्णांक bcma_sflash_init(काष्ठा bcma_drv_cc *cc)
अणु
	bcma_err(cc->core->bus, "Serial flash not supported\n");
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_BCMA_SFLASH */

#अगर_घोषित CONFIG_BCMA_NFLASH
/* driver_chipcommon_nflash.c */
पूर्णांक bcma_nflash_init(काष्ठा bcma_drv_cc *cc);
बाह्य काष्ठा platक्रमm_device bcma_nflash_dev;
#अन्यथा
अटल अंतरभूत पूर्णांक bcma_nflash_init(काष्ठा bcma_drv_cc *cc)
अणु
	bcma_err(cc->core->bus, "NAND flash not supported\n");
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_BCMA_NFLASH */

#अगर_घोषित CONFIG_BCMA_HOST_PCI
/* host_pci.c */
बाह्य पूर्णांक __init bcma_host_pci_init(व्योम);
बाह्य व्योम __निकास bcma_host_pci_निकास(व्योम);
#पूर्ण_अगर /* CONFIG_BCMA_HOST_PCI */

/* host_soc.c */
#अगर defined(CONFIG_BCMA_HOST_SOC) && defined(CONFIG_OF)
बाह्य पूर्णांक __init bcma_host_soc_रेजिस्टर_driver(व्योम);
बाह्य व्योम __निकास bcma_host_soc_unरेजिस्टर_driver(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक __init bcma_host_soc_रेजिस्टर_driver(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम __निकास bcma_host_soc_unरेजिस्टर_driver(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BCMA_HOST_SOC && CONFIG_OF */

/* driver_pci.c */
#अगर_घोषित CONFIG_BCMA_DRIVER_PCI
u32 bcma_pcie_पढ़ो(काष्ठा bcma_drv_pci *pc, u32 address);
व्योम bcma_core_pci_early_init(काष्ठा bcma_drv_pci *pc);
व्योम bcma_core_pci_init(काष्ठा bcma_drv_pci *pc);
व्योम bcma_core_pci_up(काष्ठा bcma_drv_pci *pc);
व्योम bcma_core_pci_करोwn(काष्ठा bcma_drv_pci *pc);
#अन्यथा
अटल अंतरभूत व्योम bcma_core_pci_early_init(काष्ठा bcma_drv_pci *pc)
अणु
	WARN_ON(pc->core->bus->hosttype == BCMA_HOSTTYPE_PCI);
पूर्ण
अटल अंतरभूत व्योम bcma_core_pci_init(काष्ठा bcma_drv_pci *pc)
अणु
	/* Initialization is required क्रम PCI hosted bus */
	WARN_ON(pc->core->bus->hosttype == BCMA_HOSTTYPE_PCI);
पूर्ण
#पूर्ण_अगर

/* driver_pcie2.c */
#अगर_घोषित CONFIG_BCMA_DRIVER_PCI
व्योम bcma_core_pcie2_init(काष्ठा bcma_drv_pcie2 *pcie2);
व्योम bcma_core_pcie2_up(काष्ठा bcma_drv_pcie2 *pcie2);
#अन्यथा
अटल अंतरभूत व्योम bcma_core_pcie2_init(काष्ठा bcma_drv_pcie2 *pcie2)
अणु
	/* Initialization is required क्रम PCI hosted bus */
	WARN_ON(pcie2->core->bus->hosttype == BCMA_HOSTTYPE_PCI);
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक bcma_chipco_watchकरोg_रेजिस्टर(काष्ठा bcma_drv_cc *cc);

#अगर_घोषित CONFIG_BCMA_DRIVER_PCI_HOSTMODE
bool bcma_core_pci_is_in_hosपंचांगode(काष्ठा bcma_drv_pci *pc);
व्योम bcma_core_pci_hosपंचांगode_init(काष्ठा bcma_drv_pci *pc);
#अन्यथा
अटल अंतरभूत bool bcma_core_pci_is_in_hosपंचांगode(काष्ठा bcma_drv_pci *pc)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम bcma_core_pci_hosपंचांगode_init(काष्ठा bcma_drv_pci *pc)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BCMA_DRIVER_PCI_HOSTMODE */

/**************************************************
 * driver_mips.c
 **************************************************/

#अगर_घोषित CONFIG_BCMA_DRIVER_MIPS
अचिन्हित पूर्णांक bcma_core_mips_irq(काष्ठा bcma_device *dev);
व्योम bcma_core_mips_early_init(काष्ठा bcma_drv_mips *mcore);
व्योम bcma_core_mips_init(काष्ठा bcma_drv_mips *mcore);
#अन्यथा
अटल अंतरभूत अचिन्हित पूर्णांक bcma_core_mips_irq(काष्ठा bcma_device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम bcma_core_mips_early_init(काष्ठा bcma_drv_mips *mcore)
अणु
पूर्ण
अटल अंतरभूत व्योम bcma_core_mips_init(काष्ठा bcma_drv_mips *mcore)
अणु
पूर्ण
#पूर्ण_अगर

/**************************************************
 * driver_gmac_cmn.c
 **************************************************/

#अगर_घोषित CONFIG_BCMA_DRIVER_GMAC_CMN
व्योम bcma_core_gmac_cmn_init(काष्ठा bcma_drv_gmac_cmn *gc);
#अन्यथा
अटल अंतरभूत व्योम bcma_core_gmac_cmn_init(काष्ठा bcma_drv_gmac_cmn *gc)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BCMA_DRIVER_GPIO
/* driver_gpio.c */
पूर्णांक bcma_gpio_init(काष्ठा bcma_drv_cc *cc);
पूर्णांक bcma_gpio_unरेजिस्टर(काष्ठा bcma_drv_cc *cc);
#अन्यथा
अटल अंतरभूत पूर्णांक bcma_gpio_init(काष्ठा bcma_drv_cc *cc)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक bcma_gpio_unरेजिस्टर(काष्ठा bcma_drv_cc *cc)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_BCMA_DRIVER_GPIO */

#पूर्ण_अगर
