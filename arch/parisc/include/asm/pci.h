<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_PARISC_PCI_H
#घोषणा __ASM_PARISC_PCI_H

#समावेश <linux/scatterlist.h>



/*
** HP PCI platक्रमms generally support multiple bus adapters.
**    (workstations 1-~4, servers 2-~32)
**
** Newer platक्रमms number the busses across PCI bus adapters *sparsely*.
** E.g. 0, 8, 16, ...
**
** Under a PCI bus, most HP platक्रमms support PPBs up to two or three
** levels deep. See "Bit3" product line. 
*/
#घोषणा PCI_MAX_BUSSES	256


/* To be used as: mdelay(pci_post_reset_delay);
 *
 * post_reset is the समय the kernel should stall to prevent anyone from
 * accessing the PCI bus once #RESET is de-निश्चितed. 
 * PCI spec somewhere says 1 second but with multi-PCI bus प्रणालीs,
 * this makes the boot समय much दीर्घer than necessary.
 * 20ms seems to work क्रम all the HP PCI implementations to date.
 */
#घोषणा pci_post_reset_delay 50


/*
** pci_hba_data (aka H2P_OBJECT in HP/UX)
**
** This is the "common" or "base" data काष्ठाure which HBA drivers
** (eg Dino or LBA) are required to place at the top of their own
** platक्रमm_data काष्ठाure.  I've heard this called "C inheritance" too.
**
** Data needed by pcibios layer beदीर्घs here.
*/
काष्ठा pci_hba_data अणु
	व्योम __iomem   *base_addr;	/* aka Host Physical Address */
	स्थिर काष्ठा parisc_device *dev; /* device from PA bus walk */
	काष्ठा pci_bus *hba_bus;	/* primary PCI bus below HBA */
	पूर्णांक		hba_num;	/* I/O port space access "key" */
	काष्ठा resource bus_num;	/* PCI bus numbers */
	काष्ठा resource io_space;	/* PIOP */
	काष्ठा resource lmmio_space;	/* bus addresses < 4Gb */
	काष्ठा resource elmmio_space;	/* additional bus addresses < 4Gb */
	काष्ठा resource gmmio_space;	/* bus addresses > 4Gb */

	/* NOTE: Dino code assumes it can use *all* of the lmmio_space,
	 * elmmio_space and gmmio_space as a contiguous array of
	 * resources.  This #घोषणा represents the array size */
	#घोषणा DINO_MAX_LMMIO_RESOURCES	3

	अचिन्हित दीर्घ   lmmio_space_offset;  /* CPU view - PCI view */
	काष्ठा ioc	*iommu;		/* IOMMU this device is under */
	/* REVISIT - spinlock to protect resources? */

	#घोषणा HBA_NAME_SIZE 16
	अक्षर io_name[HBA_NAME_SIZE];
	अक्षर lmmio_name[HBA_NAME_SIZE];
	अक्षर elmmio_name[HBA_NAME_SIZE];
	अक्षर gmmio_name[HBA_NAME_SIZE];
पूर्ण;

/* 
** We support 2^16 I/O ports per HBA.  These are set up in the क्रमm
** 0xbbxxxx, where bb is the bus number and xxxx is the I/O port
** space address.
*/
#घोषणा HBA_PORT_SPACE_BITS	16

#घोषणा HBA_PORT_BASE(h)	((h) << HBA_PORT_SPACE_BITS)
#घोषणा HBA_PORT_SPACE_SIZE	(1UL << HBA_PORT_SPACE_BITS)

#घोषणा PCI_PORT_HBA(a)		((a) >> HBA_PORT_SPACE_BITS)
#घोषणा PCI_PORT_ADDR(a)	((a) & (HBA_PORT_SPACE_SIZE - 1))

#अगर_घोषित CONFIG_64BIT
#घोषणा PCI_F_EXTEND		0xffffffff00000000UL
#अन्यथा	/* !CONFIG_64BIT */
#घोषणा PCI_F_EXTEND		0UL
#पूर्ण_अगर /* !CONFIG_64BIT */

/*
** Most PCI devices (eg Tulip, NCR720) also export the same रेजिस्टरs
** to both MMIO and I/O port space.  Due to poor perक्रमmance of I/O Port
** access under HP PCI bus adapters, strongly recommend the use of MMIO
** address space.
**
** While I'm at it more PA programming notes:
**
** 1) MMIO stores (ग_लिखोs) are posted operations. This means the processor
**    माला_लो an "ACK" beक्रमe the ग_लिखो actually माला_लो to the device. A पढ़ो
**    to the same device (or typically the bus adapter above it) will
**    क्रमce in-flight ग_लिखो transaction(s) out to the targeted device
**    beक्रमe the पढ़ो can complete.
**
** 2) The Programmed I/O (PIO) data may not always be strongly ordered with
**    respect to DMA on all platक्रमms. Ie PIO data can reach the processor
**    beक्रमe in-flight DMA reaches memory. Since most SMP PA platक्रमms
**    are I/O coherent, it generally करोesn't matter...but someबार
**    it करोes.
**
** I've helped device driver ग_लिखोrs debug both types of problems.
*/
काष्ठा pci_port_ops अणु
	  u8 (*inb)  (काष्ठा pci_hba_data *hba, u16 port);
	 u16 (*inw)  (काष्ठा pci_hba_data *hba, u16 port);
	 u32 (*inl)  (काष्ठा pci_hba_data *hba, u16 port);
	व्योम (*outb) (काष्ठा pci_hba_data *hba, u16 port,  u8 data);
	व्योम (*outw) (काष्ठा pci_hba_data *hba, u16 port, u16 data);
	व्योम (*outl) (काष्ठा pci_hba_data *hba, u16 port, u32 data);
पूर्ण;


काष्ठा pci_bios_ops अणु
	व्योम (*init)(व्योम);
	व्योम (*fixup_bus)(काष्ठा pci_bus *bus);
पूर्ण;

/*
** Stuff declared in arch/parisc/kernel/pci.c
*/
बाह्य काष्ठा pci_port_ops *pci_port;
बाह्य काष्ठा pci_bios_ops *pci_bios;

#अगर_घोषित CONFIG_PCI
बाह्य व्योम pcibios_रेजिस्टर_hba(काष्ठा pci_hba_data *);
#अन्यथा
अटल अंतरभूत व्योम pcibios_रेजिस्टर_hba(काष्ठा pci_hba_data *x)
अणु
पूर्ण
#पूर्ण_अगर
बाह्य व्योम pcibios_init_bridge(काष्ठा pci_dev *);

/*
 * pcibios_assign_all_busses() is used in drivers/pci/pci.c:pci_करो_scan_bus()
 *   0 == check अगर bridge is numbered beक्रमe re-numbering.
 *   1 == pci_करो_scan_bus() should स्वतःmatically number all PCI-PCI bridges.
 *
 *   We *should* set this to zero क्रम "legacy" platक्रमms and one
 *   क्रम PAT platक्रमms.
 *
 *   But legacy platक्रमms also need to rक्रमागतber the busses below a Host
 *   Bus controller.  Adding a 4-port Tulip card on the first PCI root
 *   bus of a C200 resulted in the secondary bus being numbered as 1.
 *   The second PCI host bus controller's root bus had alपढ़ोy been
 *   asचिन्हित bus number 1 by firmware and sysfs complained.
 *
 *   Firmware isn't करोing anything wrong here since each controller
 *   is its own PCI करोमुख्य.  It's simpler and easier क्रम us to rक्रमागतber
 *   the busses rather than treat each Dino as a separate PCI करोमुख्य.
 *   Eventually, we may want to पूर्णांकroduce PCI करोमुख्यs क्रम Superकरोme or
 *   rp7420/8420 boxes and then revisit this issue.
 */
#घोषणा pcibios_assign_all_busses()     (1)

#घोषणा PCIBIOS_MIN_IO          0x10
#घोषणा PCIBIOS_MIN_MEM         0x1000 /* NBPG - but pci/setup-res.c dies */

अटल अंतरभूत पूर्णांक pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel)
अणु
	वापस channel ? 15 : 14;
पूर्ण

#घोषणा HAVE_PCI_MMAP
#घोषणा ARCH_GENERIC_PCI_MMAP_RESOURCE

#पूर्ण_अगर /* __ASM_PARISC_PCI_H */
