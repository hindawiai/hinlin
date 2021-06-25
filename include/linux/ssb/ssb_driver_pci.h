<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_SSB_PCICORE_H_
#घोषणा LINUX_SSB_PCICORE_H_

#समावेश <linux/types.h>

काष्ठा pci_dev;


#अगर_घोषित CONFIG_SSB_DRIVER_PCICORE

/* PCI core रेजिस्टरs. */
#घोषणा SSB_PCICORE_CTL			0x0000	/* PCI Control */
#घोषणा  SSB_PCICORE_CTL_RST_OE		0x00000001 /* PCI_RESET Output Enable */
#घोषणा  SSB_PCICORE_CTL_RST		0x00000002 /* PCI_RESET driven out to pin */
#घोषणा  SSB_PCICORE_CTL_CLK_OE		0x00000004 /* Clock gate Output Enable */
#घोषणा  SSB_PCICORE_CTL_CLK		0x00000008 /* Gate क्रम घड़ी driven out to pin */
#घोषणा SSB_PCICORE_ARBCTL		0x0010	/* PCI Arbiter Control */
#घोषणा  SSB_PCICORE_ARBCTL_INTERN	0x00000001 /* Use पूर्णांकernal arbiter */
#घोषणा  SSB_PCICORE_ARBCTL_EXTERN	0x00000002 /* Use बाह्यal arbiter */
#घोषणा  SSB_PCICORE_ARBCTL_PARKID	0x00000006 /* Mask, selects which agent is parked on an idle bus */
#घोषणा   SSB_PCICORE_ARBCTL_PARKID_LAST	0x00000000 /* Last requestor */
#घोषणा   SSB_PCICORE_ARBCTL_PARKID_4710	0x00000002 /* 4710 */
#घोषणा   SSB_PCICORE_ARBCTL_PARKID_EXT0	0x00000004 /* External requestor 0 */
#घोषणा   SSB_PCICORE_ARBCTL_PARKID_EXT1	0x00000006 /* External requestor 1 */
#घोषणा SSB_PCICORE_ISTAT		0x0020	/* Interrupt status */
#घोषणा  SSB_PCICORE_ISTAT_INTA		0x00000001 /* PCI INTA# */
#घोषणा  SSB_PCICORE_ISTAT_INTB		0x00000002 /* PCI INTB# */
#घोषणा  SSB_PCICORE_ISTAT_SERR		0x00000004 /* PCI SERR# (ग_लिखो to clear) */
#घोषणा  SSB_PCICORE_ISTAT_PERR		0x00000008 /* PCI PERR# (ग_लिखो to clear) */
#घोषणा  SSB_PCICORE_ISTAT_PME		0x00000010 /* PCI PME# */
#घोषणा SSB_PCICORE_IMASK		0x0024	/* Interrupt mask */
#घोषणा  SSB_PCICORE_IMASK_INTA		0x00000001 /* PCI INTA# */
#घोषणा  SSB_PCICORE_IMASK_INTB		0x00000002 /* PCI INTB# */
#घोषणा  SSB_PCICORE_IMASK_SERR		0x00000004 /* PCI SERR# */
#घोषणा  SSB_PCICORE_IMASK_PERR		0x00000008 /* PCI PERR# */
#घोषणा  SSB_PCICORE_IMASK_PME		0x00000010 /* PCI PME# */
#घोषणा SSB_PCICORE_MBOX		0x0028	/* Backplane to PCI Mailbox */
#घोषणा  SSB_PCICORE_MBOX_F0_0		0x00000100 /* PCI function 0, INT 0 */
#घोषणा  SSB_PCICORE_MBOX_F0_1		0x00000200 /* PCI function 0, INT 1 */
#घोषणा  SSB_PCICORE_MBOX_F1_0		0x00000400 /* PCI function 1, INT 0 */
#घोषणा  SSB_PCICORE_MBOX_F1_1		0x00000800 /* PCI function 1, INT 1 */
#घोषणा  SSB_PCICORE_MBOX_F2_0		0x00001000 /* PCI function 2, INT 0 */
#घोषणा  SSB_PCICORE_MBOX_F2_1		0x00002000 /* PCI function 2, INT 1 */
#घोषणा  SSB_PCICORE_MBOX_F3_0		0x00004000 /* PCI function 3, INT 0 */
#घोषणा  SSB_PCICORE_MBOX_F3_1		0x00008000 /* PCI function 3, INT 1 */
#घोषणा SSB_PCICORE_BCAST_ADDR		0x0050	/* Backplane Broadcast Address */
#घोषणा  SSB_PCICORE_BCAST_ADDR_MASK	0x000000FF
#घोषणा SSB_PCICORE_BCAST_DATA		0x0054	/* Backplane Broadcast Data */
#घोषणा SSB_PCICORE_GPIO_IN		0x0060	/* rev >= 2 only */
#घोषणा SSB_PCICORE_GPIO_OUT		0x0064	/* rev >= 2 only */
#घोषणा SSB_PCICORE_GPIO_ENABLE		0x0068	/* rev >= 2 only */
#घोषणा SSB_PCICORE_GPIO_CTL		0x006C	/* rev >= 2 only */
#घोषणा SSB_PCICORE_SBTOPCI0		0x0100	/* Backplane to PCI translation 0 (sbtopci0) */
#घोषणा  SSB_PCICORE_SBTOPCI0_MASK	0xFC000000
#घोषणा SSB_PCICORE_SBTOPCI1		0x0104	/* Backplane to PCI translation 1 (sbtopci1) */
#घोषणा  SSB_PCICORE_SBTOPCI1_MASK	0xFC000000
#घोषणा SSB_PCICORE_SBTOPCI2		0x0108	/* Backplane to PCI translation 2 (sbtopci2) */
#घोषणा  SSB_PCICORE_SBTOPCI2_MASK	0xC0000000
#घोषणा SSB_PCICORE_PCICFG0		0x0400	/* PCI config space 0 (rev >= 8) */
#घोषणा SSB_PCICORE_PCICFG1		0x0500	/* PCI config space 1 (rev >= 8) */
#घोषणा SSB_PCICORE_PCICFG2		0x0600	/* PCI config space 2 (rev >= 8) */
#घोषणा SSB_PCICORE_PCICFG3		0x0700	/* PCI config space 3 (rev >= 8) */
#घोषणा SSB_PCICORE_SPROM(worकरोffset)	(0x0800 + ((worकरोffset) * 2)) /* SPROM shaकरोw area (72 bytes) */

/* SBtoPCIx */
#घोषणा SSB_PCICORE_SBTOPCI_MEM		0x00000000
#घोषणा SSB_PCICORE_SBTOPCI_IO		0x00000001
#घोषणा SSB_PCICORE_SBTOPCI_CFG0	0x00000002
#घोषणा SSB_PCICORE_SBTOPCI_CFG1	0x00000003
#घोषणा SSB_PCICORE_SBTOPCI_PREF	0x00000004 /* Prefetch enable */
#घोषणा SSB_PCICORE_SBTOPCI_BURST	0x00000008 /* Burst enable */
#घोषणा SSB_PCICORE_SBTOPCI_MRM		0x00000020 /* Memory Read Multiple */
#घोषणा SSB_PCICORE_SBTOPCI_RC		0x00000030 /* Read Command mask (rev >= 11) */
#घोषणा  SSB_PCICORE_SBTOPCI_RC_READ	0x00000000 /* Memory पढ़ो */
#घोषणा  SSB_PCICORE_SBTOPCI_RC_READL	0x00000010 /* Memory पढ़ो line */
#घोषणा  SSB_PCICORE_SBTOPCI_RC_READM	0x00000020 /* Memory पढ़ो multiple */


/* PCIcore specअगरic boardflags */
#घोषणा SSB_PCICORE_BFL_NOPCI		0x00000400 /* Board leaves PCI भग्नing */


काष्ठा ssb_pcicore अणु
	काष्ठा ssb_device *dev;
	u8 setup_करोne:1;
	u8 hosपंचांगode:1;
	u8 cardbusmode:1;
पूर्ण;

बाह्य व्योम ssb_pcicore_init(काष्ठा ssb_pcicore *pc);

/* Enable IRQ routing क्रम a specअगरic device */
बाह्य पूर्णांक ssb_pcicore_dev_irqvecs_enable(काष्ठा ssb_pcicore *pc,
					  काष्ठा ssb_device *dev);

पूर्णांक ssb_pcicore_plat_dev_init(काष्ठा pci_dev *d);
पूर्णांक ssb_pcicore_pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);


#अन्यथा /* CONFIG_SSB_DRIVER_PCICORE */


काष्ठा ssb_pcicore अणु
पूर्ण;

अटल अंतरभूत
व्योम ssb_pcicore_init(काष्ठा ssb_pcicore *pc)
अणु
पूर्ण

अटल अंतरभूत
पूर्णांक ssb_pcicore_dev_irqvecs_enable(काष्ठा ssb_pcicore *pc,
				   काष्ठा ssb_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक ssb_pcicore_plat_dev_init(काष्ठा pci_dev *d)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत
पूर्णांक ssb_pcicore_pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर /* CONFIG_SSB_DRIVER_PCICORE */
#पूर्ण_अगर /* LINUX_SSB_PCICORE_H_ */
