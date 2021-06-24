<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_BCMA_DRIVER_PCI_H_
#घोषणा LINUX_BCMA_DRIVER_PCI_H_

#समावेश <linux/types.h>

काष्ठा pci_dev;

/** PCI core रेजिस्टरs. **/
#घोषणा BCMA_CORE_PCI_CTL			0x0000	/* PCI Control */
#घोषणा  BCMA_CORE_PCI_CTL_RST_OE		0x00000001 /* PCI_RESET Output Enable */
#घोषणा  BCMA_CORE_PCI_CTL_RST			0x00000002 /* PCI_RESET driven out to pin */
#घोषणा  BCMA_CORE_PCI_CTL_CLK_OE		0x00000004 /* Clock gate Output Enable */
#घोषणा  BCMA_CORE_PCI_CTL_CLK			0x00000008 /* Gate क्रम घड़ी driven out to pin */
#घोषणा BCMA_CORE_PCI_ARBCTL			0x0010	/* PCI Arbiter Control */
#घोषणा  BCMA_CORE_PCI_ARBCTL_INTERN		0x00000001 /* Use पूर्णांकernal arbiter */
#घोषणा  BCMA_CORE_PCI_ARBCTL_EXTERN		0x00000002 /* Use बाह्यal arbiter */
#घोषणा  BCMA_CORE_PCI_ARBCTL_PARKID		0x00000006 /* Mask, selects which agent is parked on an idle bus */
#घोषणा   BCMA_CORE_PCI_ARBCTL_PARKID_LAST	0x00000000 /* Last requestor */
#घोषणा   BCMA_CORE_PCI_ARBCTL_PARKID_4710	0x00000002 /* 4710 */
#घोषणा   BCMA_CORE_PCI_ARBCTL_PARKID_EXT0	0x00000004 /* External requestor 0 */
#घोषणा   BCMA_CORE_PCI_ARBCTL_PARKID_EXT1	0x00000006 /* External requestor 1 */
#घोषणा BCMA_CORE_PCI_ISTAT			0x0020	/* Interrupt status */
#घोषणा  BCMA_CORE_PCI_ISTAT_INTA		0x00000001 /* PCI INTA# */
#घोषणा  BCMA_CORE_PCI_ISTAT_INTB		0x00000002 /* PCI INTB# */
#घोषणा  BCMA_CORE_PCI_ISTAT_SERR		0x00000004 /* PCI SERR# (ग_लिखो to clear) */
#घोषणा  BCMA_CORE_PCI_ISTAT_PERR		0x00000008 /* PCI PERR# (ग_लिखो to clear) */
#घोषणा  BCMA_CORE_PCI_ISTAT_PME		0x00000010 /* PCI PME# */
#घोषणा BCMA_CORE_PCI_IMASK			0x0024	/* Interrupt mask */
#घोषणा  BCMA_CORE_PCI_IMASK_INTA		0x00000001 /* PCI INTA# */
#घोषणा  BCMA_CORE_PCI_IMASK_INTB		0x00000002 /* PCI INTB# */
#घोषणा  BCMA_CORE_PCI_IMASK_SERR		0x00000004 /* PCI SERR# */
#घोषणा  BCMA_CORE_PCI_IMASK_PERR		0x00000008 /* PCI PERR# */
#घोषणा  BCMA_CORE_PCI_IMASK_PME		0x00000010 /* PCI PME# */
#घोषणा BCMA_CORE_PCI_MBOX			0x0028	/* Backplane to PCI Mailbox */
#घोषणा  BCMA_CORE_PCI_MBOX_F0_0		0x00000100 /* PCI function 0, INT 0 */
#घोषणा  BCMA_CORE_PCI_MBOX_F0_1		0x00000200 /* PCI function 0, INT 1 */
#घोषणा  BCMA_CORE_PCI_MBOX_F1_0		0x00000400 /* PCI function 1, INT 0 */
#घोषणा  BCMA_CORE_PCI_MBOX_F1_1		0x00000800 /* PCI function 1, INT 1 */
#घोषणा  BCMA_CORE_PCI_MBOX_F2_0		0x00001000 /* PCI function 2, INT 0 */
#घोषणा  BCMA_CORE_PCI_MBOX_F2_1		0x00002000 /* PCI function 2, INT 1 */
#घोषणा  BCMA_CORE_PCI_MBOX_F3_0		0x00004000 /* PCI function 3, INT 0 */
#घोषणा  BCMA_CORE_PCI_MBOX_F3_1		0x00008000 /* PCI function 3, INT 1 */
#घोषणा BCMA_CORE_PCI_BCAST_ADDR		0x0050	/* Backplane Broadcast Address */
#घोषणा  BCMA_CORE_PCI_BCAST_ADDR_MASK		0x000000FF
#घोषणा BCMA_CORE_PCI_BCAST_DATA		0x0054	/* Backplane Broadcast Data */
#घोषणा BCMA_CORE_PCI_GPIO_IN			0x0060	/* rev >= 2 only */
#घोषणा BCMA_CORE_PCI_GPIO_OUT			0x0064	/* rev >= 2 only */
#घोषणा BCMA_CORE_PCI_GPIO_ENABLE		0x0068	/* rev >= 2 only */
#घोषणा BCMA_CORE_PCI_GPIO_CTL			0x006C	/* rev >= 2 only */
#घोषणा BCMA_CORE_PCI_SBTOPCI0			0x0100	/* Backplane to PCI translation 0 (sbtopci0) */
#घोषणा  BCMA_CORE_PCI_SBTOPCI0_MASK		0xFC000000
#घोषणा BCMA_CORE_PCI_SBTOPCI1			0x0104	/* Backplane to PCI translation 1 (sbtopci1) */
#घोषणा  BCMA_CORE_PCI_SBTOPCI1_MASK		0xFC000000
#घोषणा BCMA_CORE_PCI_SBTOPCI2			0x0108	/* Backplane to PCI translation 2 (sbtopci2) */
#घोषणा  BCMA_CORE_PCI_SBTOPCI2_MASK		0xC0000000
#घोषणा BCMA_CORE_PCI_CONFIG_ADDR		0x0120	/* pcie config space access */
#घोषणा BCMA_CORE_PCI_CONFIG_DATA		0x0124	/* pcie config space access */
#घोषणा BCMA_CORE_PCI_MDIO_CONTROL		0x0128	/* controls the mdio access */
#घोषणा  BCMA_CORE_PCI_MDIOCTL_DIVISOR_MASK	0x7f	/* घड़ी to be used on MDIO */
#घोषणा  BCMA_CORE_PCI_MDIOCTL_DIVISOR_VAL	0x2
#घोषणा  BCMA_CORE_PCI_MDIOCTL_PREAM_EN		0x80	/* Enable preamble sequnce */
#घोषणा  BCMA_CORE_PCI_MDIOCTL_ACCESS_DONE	0x100	/* Tranaction complete */
#घोषणा BCMA_CORE_PCI_MDIO_DATA			0x012c	/* Data to the mdio access */
#घोषणा  BCMA_CORE_PCI_MDIODATA_MASK		0x0000ffff /* data 2 bytes */
#घोषणा  BCMA_CORE_PCI_MDIODATA_TA		0x00020000 /* Turnaround */
#घोषणा  BCMA_CORE_PCI_MDIODATA_REGADDR_SHF_OLD	18	/* Regaddr shअगरt (rev < 10) */
#घोषणा  BCMA_CORE_PCI_MDIODATA_REGADDR_MASK_OLD	0x003c0000 /* Regaddr Mask (rev < 10) */
#घोषणा  BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF_OLD	22	/* Physmedia devaddr shअगरt (rev < 10) */
#घोषणा  BCMA_CORE_PCI_MDIODATA_DEVADDR_MASK_OLD	0x0fc00000 /* Physmedia devaddr Mask (rev < 10) */
#घोषणा  BCMA_CORE_PCI_MDIODATA_REGADDR_SHF	18	/* Regaddr shअगरt */
#घोषणा  BCMA_CORE_PCI_MDIODATA_REGADDR_MASK	0x007c0000 /* Regaddr Mask */
#घोषणा  BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF	23	/* Physmedia devaddr shअगरt */
#घोषणा  BCMA_CORE_PCI_MDIODATA_DEVADDR_MASK	0x0f800000 /* Physmedia devaddr Mask */
#घोषणा  BCMA_CORE_PCI_MDIODATA_WRITE		0x10000000 /* ग_लिखो Transaction */
#घोषणा  BCMA_CORE_PCI_MDIODATA_READ		0x20000000 /* Read Transaction */
#घोषणा  BCMA_CORE_PCI_MDIODATA_START		0x40000000 /* start of Transaction */
#घोषणा  BCMA_CORE_PCI_MDIODATA_DEV_ADDR	0x0	/* dev address क्रम serdes */
#घोषणा  BCMA_CORE_PCI_MDIODATA_BLK_ADDR	0x1F	/* blk address क्रम serdes */
#घोषणा  BCMA_CORE_PCI_MDIODATA_DEV_PLL		0x1d	/* SERDES PLL Dev */
#घोषणा  BCMA_CORE_PCI_MDIODATA_DEV_TX		0x1e	/* SERDES TX Dev */
#घोषणा  BCMA_CORE_PCI_MDIODATA_DEV_RX		0x1f	/* SERDES RX Dev */
#घोषणा BCMA_CORE_PCI_PCIEIND_ADDR		0x0130	/* indirect access to the पूर्णांकernal रेजिस्टर */
#घोषणा BCMA_CORE_PCI_PCIEIND_DATA		0x0134	/* Data to/from the पूर्णांकernal रेजिस्टर */
#घोषणा BCMA_CORE_PCI_CLKREQENCTRL		0x0138	/*  >= rev 6, Clkreq rdma control */
#घोषणा BCMA_CORE_PCI_PCICFG0			0x0400	/* PCI config space 0 (rev >= 8) */
#घोषणा BCMA_CORE_PCI_PCICFG1			0x0500	/* PCI config space 1 (rev >= 8) */
#घोषणा BCMA_CORE_PCI_PCICFG2			0x0600	/* PCI config space 2 (rev >= 8) */
#घोषणा BCMA_CORE_PCI_PCICFG3			0x0700	/* PCI config space 3 (rev >= 8) */
#घोषणा BCMA_CORE_PCI_SPROM(worकरोffset)		(0x0800 + ((worकरोffset) * 2)) /* SPROM shaकरोw area (72 bytes) */
#घोषणा  BCMA_CORE_PCI_SPROM_PI_OFFSET		0	/* first word */
#घोषणा   BCMA_CORE_PCI_SPROM_PI_MASK		0xf000	/* bit 15:12 */
#घोषणा   BCMA_CORE_PCI_SPROM_PI_SHIFT		12	/* bit 15:12 */
#घोषणा  BCMA_CORE_PCI_SPROM_MISC_CONFIG	5	/* word 5 */
#घोषणा   BCMA_CORE_PCI_SPROM_L23READY_EXIT_NOPERST	0x8000	/* bit 15 */
#घोषणा   BCMA_CORE_PCI_SPROM_CLKREQ_OFFSET_REV5	20	/* word 20 क्रम srom rev <= 5 */
#घोषणा   BCMA_CORE_PCI_SPROM_CLKREQ_ENB	0x0800	/* bit 11 */

/* SBtoPCIx */
#घोषणा BCMA_CORE_PCI_SBTOPCI_MEM		0x00000000
#घोषणा BCMA_CORE_PCI_SBTOPCI_IO		0x00000001
#घोषणा BCMA_CORE_PCI_SBTOPCI_CFG0		0x00000002
#घोषणा BCMA_CORE_PCI_SBTOPCI_CFG1		0x00000003
#घोषणा BCMA_CORE_PCI_SBTOPCI_PREF		0x00000004 /* Prefetch enable */
#घोषणा BCMA_CORE_PCI_SBTOPCI_BURST		0x00000008 /* Burst enable */
#घोषणा BCMA_CORE_PCI_SBTOPCI_MRM		0x00000020 /* Memory Read Multiple */
#घोषणा BCMA_CORE_PCI_SBTOPCI_RC		0x00000030 /* Read Command mask (rev >= 11) */
#घोषणा  BCMA_CORE_PCI_SBTOPCI_RC_READ		0x00000000 /* Memory पढ़ो */
#घोषणा  BCMA_CORE_PCI_SBTOPCI_RC_READL		0x00000010 /* Memory पढ़ो line */
#घोषणा  BCMA_CORE_PCI_SBTOPCI_RC_READM		0x00000020 /* Memory पढ़ो multiple */

/* PCIE protocol PHY diagnostic रेजिस्टरs */
#घोषणा BCMA_CORE_PCI_PLP_MODEREG		0x200	/* Mode */
#घोषणा BCMA_CORE_PCI_PLP_STATUSREG		0x204	/* Status */
#घोषणा  BCMA_CORE_PCI_PLP_POLARITYINV_STAT	0x10	/* Status reg PCIE_PLP_STATUSREG */
#घोषणा BCMA_CORE_PCI_PLP_LTSSMCTRLREG		0x208	/* LTSSM control */
#घोषणा BCMA_CORE_PCI_PLP_LTLINKNUMREG		0x20c	/* Link Training Link number */
#घोषणा BCMA_CORE_PCI_PLP_LTLANENUMREG		0x210	/* Link Training Lane number */
#घोषणा BCMA_CORE_PCI_PLP_LTNFTSREG		0x214	/* Link Training N_FTS */
#घोषणा BCMA_CORE_PCI_PLP_ATTNREG		0x218	/* Attention */
#घोषणा BCMA_CORE_PCI_PLP_ATTNMASKREG		0x21C	/* Attention Mask */
#घोषणा BCMA_CORE_PCI_PLP_RXERRCTR		0x220	/* Rx Error */
#घोषणा BCMA_CORE_PCI_PLP_RXFRMERRCTR		0x224	/* Rx Framing Error */
#घोषणा BCMA_CORE_PCI_PLP_RXERRTHRESHREG	0x228	/* Rx Error threshold */
#घोषणा BCMA_CORE_PCI_PLP_TESTCTRLREG		0x22C	/* Test Control reg */
#घोषणा BCMA_CORE_PCI_PLP_SERDESCTRLOVRDREG	0x230	/* SERDES Control Override */
#घोषणा BCMA_CORE_PCI_PLP_TIMINGOVRDREG		0x234	/* Timing param override */
#घोषणा BCMA_CORE_PCI_PLP_RXTXSMDIAGREG		0x238	/* RXTX State Machine Diag */
#घोषणा BCMA_CORE_PCI_PLP_LTSSMDIAGREG		0x23C	/* LTSSM State Machine Diag */

/* PCIE protocol DLLP diagnostic रेजिस्टरs */
#घोषणा BCMA_CORE_PCI_DLLP_LCREG		0x100	/* Link Control */
#घोषणा BCMA_CORE_PCI_DLLP_LSREG		0x104	/* Link Status */
#घोषणा BCMA_CORE_PCI_DLLP_LAREG		0x108	/* Link Attention */
#घोषणा  BCMA_CORE_PCI_DLLP_LSREG_LINKUP	(1 << 16)
#घोषणा BCMA_CORE_PCI_DLLP_LAMASKREG		0x10C	/* Link Attention Mask */
#घोषणा BCMA_CORE_PCI_DLLP_NEXTTXSEQNUMREG	0x110	/* Next Tx Seq Num */
#घोषणा BCMA_CORE_PCI_DLLP_ACKEDTXSEQNUMREG	0x114	/* Acked Tx Seq Num */
#घोषणा BCMA_CORE_PCI_DLLP_PURGEDTXSEQNUMREG	0x118	/* Purged Tx Seq Num */
#घोषणा BCMA_CORE_PCI_DLLP_RXSEQNUMREG		0x11C	/* Rx Sequence Number */
#घोषणा BCMA_CORE_PCI_DLLP_LRREG		0x120	/* Link Replay */
#घोषणा BCMA_CORE_PCI_DLLP_LACKTOREG		0x124	/* Link Ack Timeout */
#घोषणा BCMA_CORE_PCI_DLLP_PMTHRESHREG		0x128	/* Power Management Threshold */
#घोषणा  BCMA_CORE_PCI_ASPMTIMER_EXTEND		0x01000000 /* > rev7: enable extend ASPM समयr */
#घोषणा BCMA_CORE_PCI_DLLP_RTRYWPREG		0x12C	/* Retry buffer ग_लिखो ptr */
#घोषणा BCMA_CORE_PCI_DLLP_RTRYRPREG		0x130	/* Retry buffer Read ptr */
#घोषणा BCMA_CORE_PCI_DLLP_RTRYPPREG		0x134	/* Retry buffer Purged ptr */
#घोषणा BCMA_CORE_PCI_DLLP_RTRRWREG		0x138	/* Retry buffer Read/Write */
#घोषणा BCMA_CORE_PCI_DLLP_ECTHRESHREG		0x13C	/* Error Count Threshold */
#घोषणा BCMA_CORE_PCI_DLLP_TLPERRCTRREG		0x140	/* TLP Error Counter */
#घोषणा BCMA_CORE_PCI_DLLP_ERRCTRREG		0x144	/* Error Counter */
#घोषणा BCMA_CORE_PCI_DLLP_NAKRXCTRREG		0x148	/* NAK Received Counter */
#घोषणा BCMA_CORE_PCI_DLLP_TESTREG		0x14C	/* Test */
#घोषणा BCMA_CORE_PCI_DLLP_PKTBIST		0x150	/* Packet BIST */
#घोषणा BCMA_CORE_PCI_DLLP_PCIE11		0x154	/* DLLP PCIE 1.1 reg */

/* SERDES RX रेजिस्टरs */
#घोषणा BCMA_CORE_PCI_SERDES_RX_CTRL		1	/* Rx cntrl */
#घोषणा  BCMA_CORE_PCI_SERDES_RX_CTRL_FORCE	0x80	/* rxpolarity_क्रमce */
#घोषणा  BCMA_CORE_PCI_SERDES_RX_CTRL_POLARITY	0x40	/* rxpolarity_value */
#घोषणा BCMA_CORE_PCI_SERDES_RX_TIMER1		2	/* Rx Timer1 */
#घोषणा BCMA_CORE_PCI_SERDES_RX_CDR		6	/* CDR */
#घोषणा BCMA_CORE_PCI_SERDES_RX_CDRBW		7	/* CDR BW */

/* SERDES PLL रेजिस्टरs */
#घोषणा BCMA_CORE_PCI_SERDES_PLL_CTRL		1	/* PLL control reg */
#घोषणा BCMA_CORE_PCI_PLL_CTRL_FREQDET_EN	0x4000	/* bit 14 is FREQDET on */

/* PCIcore specअगरic boardflags */
#घोषणा BCMA_CORE_PCI_BFL_NOPCI			0x00000400 /* Board leaves PCI भग्नing */

/* PCIE Config space accessing MACROS */
#घोषणा BCMA_CORE_PCI_CFG_BUS_SHIFT		24	/* Bus shअगरt */
#घोषणा BCMA_CORE_PCI_CFG_SLOT_SHIFT		19	/* Slot/Device shअगरt */
#घोषणा BCMA_CORE_PCI_CFG_FUN_SHIFT		16	/* Function shअगरt */
#घोषणा BCMA_CORE_PCI_CFG_OFF_SHIFT		0	/* Register shअगरt */

#घोषणा BCMA_CORE_PCI_CFG_BUS_MASK		0xff	/* Bus mask */
#घोषणा BCMA_CORE_PCI_CFG_SLOT_MASK		0x1f	/* Slot/Device mask */
#घोषणा BCMA_CORE_PCI_CFG_FUN_MASK		7	/* Function mask */
#घोषणा BCMA_CORE_PCI_CFG_OFF_MASK		0xfff	/* Register mask */

#घोषणा BCMA_CORE_PCI_CFG_DEVCTRL		0xd8

#घोषणा BCMA_CORE_PCI_

/* MDIO devices (SERDES modules) */
#घोषणा BCMA_CORE_PCI_MDIO_IEEE0		0x000
#घोषणा BCMA_CORE_PCI_MDIO_IEEE1		0x001
#घोषणा BCMA_CORE_PCI_MDIO_BLK0			0x800
#घोषणा BCMA_CORE_PCI_MDIO_BLK1			0x801
#घोषणा  BCMA_CORE_PCI_MDIO_BLK1_MGMT0		0x16
#घोषणा  BCMA_CORE_PCI_MDIO_BLK1_MGMT1		0x17
#घोषणा  BCMA_CORE_PCI_MDIO_BLK1_MGMT2		0x18
#घोषणा  BCMA_CORE_PCI_MDIO_BLK1_MGMT3		0x19
#घोषणा  BCMA_CORE_PCI_MDIO_BLK1_MGMT4		0x1A
#घोषणा BCMA_CORE_PCI_MDIO_BLK2			0x802
#घोषणा BCMA_CORE_PCI_MDIO_BLK3			0x803
#घोषणा BCMA_CORE_PCI_MDIO_BLK4			0x804
#घोषणा BCMA_CORE_PCI_MDIO_TXPLL		0x808	/* TXPLL रेजिस्टर block idx */
#घोषणा BCMA_CORE_PCI_MDIO_TXCTRL0		0x820
#घोषणा BCMA_CORE_PCI_MDIO_SERDESID		0x831
#घोषणा BCMA_CORE_PCI_MDIO_RXCTRL0		0x840

/* PCIE Root Capability Register bits (Host mode only) */
#घोषणा BCMA_CORE_PCI_RC_CRS_VISIBILITY		0x0001

काष्ठा bcma_drv_pci;
काष्ठा bcma_bus;

#अगर_घोषित CONFIG_BCMA_DRIVER_PCI_HOSTMODE
काष्ठा bcma_drv_pci_host अणु
	काष्ठा bcma_drv_pci *pdev;

	u32 host_cfg_addr;
	spinlock_t cfgspace_lock;

	काष्ठा pci_controller pci_controller;
	काष्ठा pci_ops pci_ops;
	काष्ठा resource mem_resource;
	काष्ठा resource io_resource;
पूर्ण;
#पूर्ण_अगर

काष्ठा bcma_drv_pci अणु
	काष्ठा bcma_device *core;
	u8 early_setup_करोne:1;
	u8 setup_करोne:1;
	u8 hosपंचांगode:1;

#अगर_घोषित CONFIG_BCMA_DRIVER_PCI_HOSTMODE
	काष्ठा bcma_drv_pci_host *host_controller;
#पूर्ण_अगर
पूर्ण;

/* Register access */
#घोषणा pcicore_पढ़ो16(pc, offset)		bcma_पढ़ो16((pc)->core, offset)
#घोषणा pcicore_पढ़ो32(pc, offset)		bcma_पढ़ो32((pc)->core, offset)
#घोषणा pcicore_ग_लिखो16(pc, offset, val)	bcma_ग_लिखो16((pc)->core, offset, val)
#घोषणा pcicore_ग_लिखो32(pc, offset, val)	bcma_ग_लिखो32((pc)->core, offset, val)

#अगर_घोषित CONFIG_BCMA_DRIVER_PCI
बाह्य व्योम bcma_core_pci_घातer_save(काष्ठा bcma_bus *bus, bool up);
#अन्यथा
अटल अंतरभूत व्योम bcma_core_pci_घातer_save(काष्ठा bcma_bus *bus, bool up)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BCMA_DRIVER_PCI_HOSTMODE
बाह्य पूर्णांक bcma_core_pci_pcibios_map_irq(स्थिर काष्ठा pci_dev *dev);
बाह्य पूर्णांक bcma_core_pci_plat_dev_init(काष्ठा pci_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक bcma_core_pci_pcibios_map_irq(स्थिर काष्ठा pci_dev *dev)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक bcma_core_pci_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* LINUX_BCMA_DRIVER_PCI_H_ */
