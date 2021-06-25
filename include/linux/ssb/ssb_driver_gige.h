<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_SSB_DRIVER_GIGE_H_
#घोषणा LINUX_SSB_DRIVER_GIGE_H_

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/bug.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>


#अगर_घोषित CONFIG_SSB_DRIVER_GIGE


#घोषणा SSB_GIGE_PCIIO			0x0000 /* PCI I/O Registers (1024 bytes) */
#घोषणा SSB_GIGE_RESERVED		0x0400 /* Reserved (1024 bytes) */
#घोषणा SSB_GIGE_PCICFG			0x0800 /* PCI config space (256 bytes) */
#घोषणा SSB_GIGE_SHIM_FLUSHSTAT		0x0C00 /* PCI to OCP: Flush status control (32bit) */
#घोषणा SSB_GIGE_SHIM_FLUSHRDA		0x0C04 /* PCI to OCP: Flush पढ़ो address (32bit) */
#घोषणा SSB_GIGE_SHIM_FLUSHTO		0x0C08 /* PCI to OCP: Flush समयout counter (32bit) */
#घोषणा SSB_GIGE_SHIM_BARRIER		0x0C0C /* PCI to OCP: Barrier रेजिस्टर (32bit) */
#घोषणा SSB_GIGE_SHIM_MAOCPSI		0x0C10 /* PCI to OCP: MaocpSI Control (32bit) */
#घोषणा SSB_GIGE_SHIM_SIOCPMA		0x0C14 /* PCI to OCP: SiocpMa Control (32bit) */

/* TM Status High flags */
#घोषणा SSB_GIGE_TMSHIGH_RGMII		0x00010000 /* Have an RGMII PHY-bus */
/* TM Status Low flags */
#घोषणा SSB_GIGE_TMSLOW_TXBYPASS	0x00080000 /* TX bypass (no delay) */
#घोषणा SSB_GIGE_TMSLOW_RXBYPASS	0x00100000 /* RX bypass (no delay) */
#घोषणा SSB_GIGE_TMSLOW_DLLEN		0x01000000 /* Enable DLL controls */

/* Boardflags (low) */
#घोषणा SSB_GIGE_BFL_ROBOSWITCH		0x0010


#घोषणा SSB_GIGE_MEM_RES_NAME		"SSB Broadcom 47xx GigE memory"
#घोषणा SSB_GIGE_IO_RES_NAME		"SSB Broadcom 47xx GigE I/O"

काष्ठा ssb_gige अणु
	काष्ठा ssb_device *dev;

	spinlock_t lock;

	/* True, अगर the device has an RGMII bus.
	 * False, अगर the device has a GMII bus. */
	bool has_rgmii;

	/* The PCI controller device. */
	काष्ठा pci_controller pci_controller;
	काष्ठा pci_ops pci_ops;
	काष्ठा resource mem_resource;
	काष्ठा resource io_resource;
पूर्ण;

/* Check whether a PCI device is a SSB Gigabit Ethernet core. */
बाह्य bool pdev_is_ssb_gige_core(काष्ठा pci_dev *pdev);

/* Convert a pci_dev poपूर्णांकer to a ssb_gige poपूर्णांकer. */
अटल अंतरभूत काष्ठा ssb_gige * pdev_to_ssb_gige(काष्ठा pci_dev *pdev)
अणु
	अगर (!pdev_is_ssb_gige_core(pdev))
		वापस शून्य;
	वापस container_of(pdev->bus->ops, काष्ठा ssb_gige, pci_ops);
पूर्ण

/* Returns whether the PHY is connected by an RGMII bus. */
अटल अंतरभूत bool ssb_gige_is_rgmii(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ssb_gige *dev = pdev_to_ssb_gige(pdev);
	वापस (dev ? dev->has_rgmii : 0);
पूर्ण

/* Returns whether we have a Roboचयन. */
अटल अंतरभूत bool ssb_gige_have_roboचयन(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ssb_gige *dev = pdev_to_ssb_gige(pdev);
	अगर (dev)
		वापस !!(dev->dev->bus->sprom.boardflags_lo &
			  SSB_GIGE_BFL_ROBOSWITCH);
	वापस false;
पूर्ण

/* Returns whether we can only करो one DMA at once. */
अटल अंतरभूत bool ssb_gige_one_dma_at_once(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ssb_gige *dev = pdev_to_ssb_gige(pdev);
	अगर (dev)
		वापस ((dev->dev->bus->chip_id == 0x4785) &&
			(dev->dev->bus->chip_rev < 2));
	वापस false;
पूर्ण

/* Returns whether we must flush posted ग_लिखोs. */
अटल अंतरभूत bool ssb_gige_must_flush_posted_ग_लिखोs(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ssb_gige *dev = pdev_to_ssb_gige(pdev);
	अगर (dev)
		वापस (dev->dev->bus->chip_id == 0x4785);
	वापस 0;
पूर्ण

/* Get the device MAC address */
अटल अंतरभूत पूर्णांक ssb_gige_get_macaddr(काष्ठा pci_dev *pdev, u8 *macaddr)
अणु
	काष्ठा ssb_gige *dev = pdev_to_ssb_gige(pdev);
	अगर (!dev)
		वापस -ENODEV;

	स_नकल(macaddr, dev->dev->bus->sprom.et0mac, 6);
	वापस 0;
पूर्ण

/* Get the device phy address */
अटल अंतरभूत पूर्णांक ssb_gige_get_phyaddr(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ssb_gige *dev = pdev_to_ssb_gige(pdev);
	अगर (!dev)
		वापस -ENODEV;

	वापस dev->dev->bus->sprom.et0phyaddr;
पूर्ण

बाह्य पूर्णांक ssb_gige_pcibios_plat_dev_init(काष्ठा ssb_device *sdev,
					  काष्ठा pci_dev *pdev);
बाह्य पूर्णांक ssb_gige_map_irq(काष्ठा ssb_device *sdev,
			    स्थिर काष्ठा pci_dev *pdev);

/* The GigE driver is not a standalone module, because we करोn't have support
 * क्रम unरेजिस्टरing the driver. So we could not unload the module anyway. */
बाह्य पूर्णांक ssb_gige_init(व्योम);
अटल अंतरभूत व्योम ssb_gige_निकास(व्योम)
अणु
	/* Currently we can not unरेजिस्टर the GigE driver,
	 * because we can not unरेजिस्टर the PCI bridge. */
	BUG();
पूर्ण


#अन्यथा /* CONFIG_SSB_DRIVER_GIGE */
/* Gigabit Ethernet driver disabled */


अटल अंतरभूत पूर्णांक ssb_gige_pcibios_plat_dev_init(काष्ठा ssb_device *sdev,
						 काष्ठा pci_dev *pdev)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक ssb_gige_map_irq(काष्ठा ssb_device *sdev,
				   स्थिर काष्ठा pci_dev *pdev)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक ssb_gige_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ssb_gige_निकास(व्योम)
अणु
पूर्ण

अटल अंतरभूत bool pdev_is_ssb_gige_core(काष्ठा pci_dev *pdev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत काष्ठा ssb_gige * pdev_to_ssb_gige(काष्ठा pci_dev *pdev)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत bool ssb_gige_is_rgmii(काष्ठा pci_dev *pdev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool ssb_gige_have_roboचयन(काष्ठा pci_dev *pdev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool ssb_gige_one_dma_at_once(काष्ठा pci_dev *pdev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool ssb_gige_must_flush_posted_ग_लिखोs(काष्ठा pci_dev *pdev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक ssb_gige_get_macaddr(काष्ठा pci_dev *pdev, u8 *macaddr)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक ssb_gige_get_phyaddr(काष्ठा pci_dev *pdev)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर /* CONFIG_SSB_DRIVER_GIGE */
#पूर्ण_अगर /* LINUX_SSB_DRIVER_GIGE_H_ */
