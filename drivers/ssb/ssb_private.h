<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_SSB_PRIVATE_H_
#घोषणा LINUX_SSB_PRIVATE_H_

#घोषणा PFX		"ssb: "
#घोषणा pr_fmt(fmt)	PFX fmt

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/types.h>
#समावेश <linux/bcm47xx_wdt.h>


/* pci.c */
#अगर_घोषित CONFIG_SSB_PCIHOST
बाह्य पूर्णांक ssb_pci_चयन_core(काष्ठा ssb_bus *bus,
			       काष्ठा ssb_device *dev);
बाह्य पूर्णांक ssb_pci_चयन_coreidx(काष्ठा ssb_bus *bus,
				  u8 coreidx);
बाह्य पूर्णांक ssb_pci_xtal(काष्ठा ssb_bus *bus, u32 what,
			पूर्णांक turn_on);
बाह्य पूर्णांक ssb_pci_get_invariants(काष्ठा ssb_bus *bus,
				  काष्ठा ssb_init_invariants *iv);
बाह्य व्योम ssb_pci_निकास(काष्ठा ssb_bus *bus);
बाह्य पूर्णांक ssb_pci_init(काष्ठा ssb_bus *bus);
बाह्य स्थिर काष्ठा ssb_bus_ops ssb_pci_ops;

#अन्यथा /* CONFIG_SSB_PCIHOST */

अटल अंतरभूत पूर्णांक ssb_pci_चयन_core(काष्ठा ssb_bus *bus,
				      काष्ठा ssb_device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ssb_pci_चयन_coreidx(काष्ठा ssb_bus *bus,
					 u8 coreidx)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ssb_pci_xtal(काष्ठा ssb_bus *bus, u32 what,
			       पूर्णांक turn_on)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ssb_pci_निकास(काष्ठा ssb_bus *bus)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक ssb_pci_init(काष्ठा ssb_bus *bus)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_PCIHOST */


/* pcmcia.c */
#अगर_घोषित CONFIG_SSB_PCMCIAHOST
बाह्य पूर्णांक ssb_pcmcia_चयन_coreidx(काष्ठा ssb_bus *bus,
				     u8 coreidx);
बाह्य पूर्णांक ssb_pcmcia_चयन_segment(काष्ठा ssb_bus *bus,
				     u8 seg);
बाह्य पूर्णांक ssb_pcmcia_get_invariants(काष्ठा ssb_bus *bus,
				     काष्ठा ssb_init_invariants *iv);
बाह्य पूर्णांक ssb_pcmcia_hardware_setup(काष्ठा ssb_bus *bus);
बाह्य व्योम ssb_pcmcia_निकास(काष्ठा ssb_bus *bus);
बाह्य पूर्णांक ssb_pcmcia_init(काष्ठा ssb_bus *bus);
बाह्य पूर्णांक ssb_host_pcmcia_init(व्योम);
बाह्य व्योम ssb_host_pcmcia_निकास(व्योम);
बाह्य स्थिर काष्ठा ssb_bus_ops ssb_pcmcia_ops;
#अन्यथा /* CONFIG_SSB_PCMCIAHOST */
अटल अंतरभूत पूर्णांक ssb_pcmcia_चयन_coreidx(काष्ठा ssb_bus *bus,
					    u8 coreidx)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ssb_pcmcia_चयन_segment(काष्ठा ssb_bus *bus,
					    u8 seg)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ssb_pcmcia_hardware_setup(काष्ठा ssb_bus *bus)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ssb_pcmcia_निकास(काष्ठा ssb_bus *bus)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक ssb_pcmcia_init(काष्ठा ssb_bus *bus)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ssb_host_pcmcia_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ssb_host_pcmcia_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_PCMCIAHOST */

/* sdio.c */
#अगर_घोषित CONFIG_SSB_SDIOHOST
बाह्य पूर्णांक ssb_sdio_get_invariants(काष्ठा ssb_bus *bus,
				     काष्ठा ssb_init_invariants *iv);

बाह्य u32 ssb_sdio_scan_पढ़ो32(काष्ठा ssb_bus *bus, u16 offset);
बाह्य पूर्णांक ssb_sdio_scan_चयन_coreidx(काष्ठा ssb_bus *bus, u8 coreidx);
बाह्य व्योम ssb_sdio_निकास(काष्ठा ssb_bus *bus);
बाह्य पूर्णांक ssb_sdio_init(काष्ठा ssb_bus *bus);

बाह्य स्थिर काष्ठा ssb_bus_ops ssb_sdio_ops;
#अन्यथा /* CONFIG_SSB_SDIOHOST */
अटल अंतरभूत u32 ssb_sdio_scan_पढ़ो32(काष्ठा ssb_bus *bus, u16 offset)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक ssb_sdio_scan_चयन_coreidx(काष्ठा ssb_bus *bus, u8 coreidx)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ssb_sdio_निकास(काष्ठा ssb_bus *bus)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक ssb_sdio_init(काष्ठा ssb_bus *bus)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_SDIOHOST */

/**************************************************
 * host_soc.c
 **************************************************/

#अगर_घोषित CONFIG_SSB_HOST_SOC
बाह्य स्थिर काष्ठा ssb_bus_ops ssb_host_soc_ops;

बाह्य पूर्णांक ssb_host_soc_get_invariants(काष्ठा ssb_bus *bus,
				       काष्ठा ssb_init_invariants *iv);
#पूर्ण_अगर

/* scan.c */
बाह्य स्थिर अक्षर *ssb_core_name(u16 coreid);
बाह्य पूर्णांक ssb_bus_scan(काष्ठा ssb_bus *bus,
			अचिन्हित दीर्घ baseaddr);
बाह्य व्योम ssb_iounmap(काष्ठा ssb_bus *ssb);


/* sprom.c */
बाह्य
sमाप_प्रकार ssb_attr_sprom_show(काष्ठा ssb_bus *bus, अक्षर *buf,
			    पूर्णांक (*sprom_पढ़ो)(काष्ठा ssb_bus *bus, u16 *sprom));
बाह्य
sमाप_प्रकार ssb_attr_sprom_store(काष्ठा ssb_bus *bus,
			     स्थिर अक्षर *buf, माप_प्रकार count,
			     पूर्णांक (*sprom_check_crc)(स्थिर u16 *sprom, माप_प्रकार size),
			     पूर्णांक (*sprom_ग_लिखो)(काष्ठा ssb_bus *bus, स्थिर u16 *sprom));
बाह्य पूर्णांक ssb_fill_sprom_with_fallback(काष्ठा ssb_bus *bus,
					काष्ठा ssb_sprom *out);


/* core.c */
बाह्य u32 ssb_calc_घड़ी_rate(u32 plltype, u32 n, u32 m);
बाह्य काष्ठा ssb_bus *ssb_pci_dev_to_bus(काष्ठा pci_dev *pdev);
पूर्णांक ssb_क्रम_each_bus_call(अचिन्हित दीर्घ data,
			  पूर्णांक (*func)(काष्ठा ssb_bus *bus, अचिन्हित दीर्घ data));
बाह्य काष्ठा ssb_bus *ssb_pcmcia_dev_to_bus(काष्ठा pcmcia_device *pdev);

काष्ठा ssb_मुक्तze_context अणु
	/* Poपूर्णांकer to the bus */
	काष्ठा ssb_bus *bus;
	/* Boolean list to indicate whether a device is frozen on this bus. */
	bool device_frozen[SSB_MAX_NR_CORES];
पूर्ण;
बाह्य पूर्णांक ssb_devices_मुक्तze(काष्ठा ssb_bus *bus, काष्ठा ssb_मुक्तze_context *ctx);
बाह्य पूर्णांक ssb_devices_thaw(काष्ठा ssb_मुक्तze_context *ctx);



/* b43_pci_bridge.c */
#अगर_घोषित CONFIG_SSB_B43_PCI_BRIDGE
बाह्य पूर्णांक __init b43_pci_ssb_bridge_init(व्योम);
बाह्य व्योम __निकास b43_pci_ssb_bridge_निकास(व्योम);
#अन्यथा /* CONFIG_SSB_B43_PCI_BRIDGE */
अटल अंतरभूत पूर्णांक b43_pci_ssb_bridge_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम b43_pci_ssb_bridge_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_B43_PCI_BRIDGE */

/* driver_chipcommon_pmu.c */
बाह्य u32 ssb_pmu_get_cpu_घड़ी(काष्ठा ssb_chipcommon *cc);
बाह्य u32 ssb_pmu_get_controlघड़ी(काष्ठा ssb_chipcommon *cc);
बाह्य u32 ssb_pmu_get_alp_घड़ी(काष्ठा ssb_chipcommon *cc);

बाह्य u32 ssb_chipco_watchकरोg_समयr_set_wdt(काष्ठा bcm47xx_wdt *wdt,
					     u32 ticks);
बाह्य u32 ssb_chipco_watchकरोg_समयr_set_ms(काष्ठा bcm47xx_wdt *wdt, u32 ms);

/* driver_chipcommon_sflash.c */
#अगर_घोषित CONFIG_SSB_SFLASH
पूर्णांक ssb_sflash_init(काष्ठा ssb_chipcommon *cc);
#अन्यथा
अटल अंतरभूत पूर्णांक ssb_sflash_init(काष्ठा ssb_chipcommon *cc)
अणु
	pr_err("Serial flash not supported\n");
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_SFLASH */

#अगर_घोषित CONFIG_SSB_DRIVER_MIPS
बाह्य काष्ठा platक्रमm_device ssb_pflash_dev;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SSB_SFLASH
बाह्य काष्ठा platक्रमm_device ssb_sflash_dev;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SSB_DRIVER_EXTIF
बाह्य u32 ssb_extअगर_watchकरोg_समयr_set_wdt(काष्ठा bcm47xx_wdt *wdt, u32 ticks);
बाह्य u32 ssb_extअगर_watchकरोg_समयr_set_ms(काष्ठा bcm47xx_wdt *wdt, u32 ms);
#अन्यथा
अटल अंतरभूत u32 ssb_extअगर_watchकरोg_समयr_set_wdt(काष्ठा bcm47xx_wdt *wdt,
						   u32 ticks)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत u32 ssb_extअगर_watchकरोg_समयr_set_ms(काष्ठा bcm47xx_wdt *wdt,
						  u32 ms)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SSB_EMBEDDED
बाह्य पूर्णांक ssb_watchकरोg_रेजिस्टर(काष्ठा ssb_bus *bus);
#अन्यथा /* CONFIG_SSB_EMBEDDED */
अटल अंतरभूत पूर्णांक ssb_watchकरोg_रेजिस्टर(काष्ठा ssb_bus *bus)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_EMBEDDED */

#अगर_घोषित CONFIG_SSB_DRIVER_EXTIF
बाह्य व्योम ssb_extअगर_init(काष्ठा ssb_extअगर *extअगर);
#अन्यथा
अटल अंतरभूत व्योम ssb_extअगर_init(काष्ठा ssb_extअगर *extअगर)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SSB_DRIVER_GPIO
बाह्य पूर्णांक ssb_gpio_init(काष्ठा ssb_bus *bus);
बाह्य पूर्णांक ssb_gpio_unरेजिस्टर(काष्ठा ssb_bus *bus);
#अन्यथा /* CONFIG_SSB_DRIVER_GPIO */
अटल अंतरभूत पूर्णांक ssb_gpio_init(काष्ठा ssb_bus *bus)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक ssb_gpio_unरेजिस्टर(काष्ठा ssb_bus *bus)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_DRIVER_GPIO */

#पूर्ण_अगर /* LINUX_SSB_PRIVATE_H_ */
