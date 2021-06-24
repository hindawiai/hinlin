<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sata_sis.c - Silicon Integrated Systems SATA
 *
 *  Maपूर्णांकained by:  Uwe Koziolek
 *  		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *  Copyright 2004 Uwe Koziolek
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Hardware करोcumentation available under NDA.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश "sis.h"

#घोषणा DRV_NAME	"sata_sis"
#घोषणा DRV_VERSION	"1.0"

क्रमागत अणु
	sis_180			= 0,
	SIS_SCR_PCI_BAR		= 5,

	/* PCI configuration रेजिस्टरs */
	SIS_GENCTL		= 0x54, /* IDE General Control रेजिस्टर */
	SIS_SCR_BASE		= 0xc0, /* sata0 phy SCR रेजिस्टरs */
	SIS180_SATA1_OFS	= 0x10, /* offset from sata0->sata1 phy regs */
	SIS182_SATA1_OFS	= 0x20, /* offset from sata0->sata1 phy regs */
	SIS_PMR			= 0x90, /* port mapping रेजिस्टर */
	SIS_PMR_COMBINED	= 0x30,

	/* अक्रमom bits */
	SIS_FLAG_CFGSCR		= (1 << 30), /* host flag: SCRs via PCI cfg */

	GENCTL_IOMAPPED_SCR	= (1 << 26), /* अगर set, SCRs are in IO space */
पूर्ण;

अटल पूर्णांक sis_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल पूर्णांक sis_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val);
अटल पूर्णांक sis_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val);

अटल स्थिर काष्ठा pci_device_id sis_pci_tbl[] = अणु
	अणु PCI_VDEVICE(SI, 0x0180), sis_180 पूर्ण,	/* SiS 964/180 */
	अणु PCI_VDEVICE(SI, 0x0181), sis_180 पूर्ण,	/* SiS 964/180 */
	अणु PCI_VDEVICE(SI, 0x0182), sis_180 पूर्ण,	/* SiS 965/965L */
	अणु PCI_VDEVICE(SI, 0x0183), sis_180 पूर्ण,	/* SiS 965/965L */
	अणु PCI_VDEVICE(SI, 0x1182), sis_180 पूर्ण,	/* SiS 966/680 */
	अणु PCI_VDEVICE(SI, 0x1183), sis_180 पूर्ण,	/* SiS 966/966L/968/680 */

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver sis_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= sis_pci_tbl,
	.probe			= sis_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा sis_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations sis_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.scr_पढ़ो		= sis_scr_पढ़ो,
	.scr_ग_लिखो		= sis_scr_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info sis_port_info = अणु
	.flags		= ATA_FLAG_SATA,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &sis_ops,
पूर्ण;

MODULE_AUTHOR("Uwe Koziolek");
MODULE_DESCRIPTION("low-level driver for Silicon Integrated Systems SATA controller");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, sis_pci_tbl);
MODULE_VERSION(DRV_VERSION);

अटल अचिन्हित पूर्णांक get_scr_cfg_addr(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अचिन्हित पूर्णांक addr = SIS_SCR_BASE + (4 * sc_reg);
	u8 pmr;

	अगर (ap->port_no)  अणु
		चयन (pdev->device) अणु
		हाल 0x0180:
		हाल 0x0181:
			pci_पढ़ो_config_byte(pdev, SIS_PMR, &pmr);
			अगर ((pmr & SIS_PMR_COMBINED) == 0)
				addr += SIS180_SATA1_OFS;
			अवरोध;

		हाल 0x0182:
		हाल 0x0183:
		हाल 0x1182:
			addr += SIS182_SATA1_OFS;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (link->pmp)
		addr += 0x10;

	वापस addr;
पूर्ण

अटल u32 sis_scr_cfg_पढ़ो(काष्ठा ata_link *link,
			    अचिन्हित पूर्णांक sc_reg, u32 *val)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(link->ap->host->dev);
	अचिन्हित पूर्णांक cfg_addr = get_scr_cfg_addr(link, sc_reg);

	अगर (sc_reg == SCR_ERROR) /* करोesn't exist in PCI cfg space */
		वापस -EINVAL;

	pci_पढ़ो_config_dword(pdev, cfg_addr, val);
	वापस 0;
पूर्ण

अटल पूर्णांक sis_scr_cfg_ग_लिखो(काष्ठा ata_link *link,
			     अचिन्हित पूर्णांक sc_reg, u32 val)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(link->ap->host->dev);
	अचिन्हित पूर्णांक cfg_addr = get_scr_cfg_addr(link, sc_reg);

	pci_ग_लिखो_config_dword(pdev, cfg_addr, val);
	वापस 0;
पूर्ण

अटल पूर्णांक sis_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val)
अणु
	काष्ठा ata_port *ap = link->ap;
	व्योम __iomem *base = ap->ioaddr.scr_addr + link->pmp * 0x10;

	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;

	अगर (ap->flags & SIS_FLAG_CFGSCR)
		वापस sis_scr_cfg_पढ़ो(link, sc_reg, val);

	*val = ioपढ़ो32(base + sc_reg * 4);
	वापस 0;
पूर्ण

अटल पूर्णांक sis_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val)
अणु
	काष्ठा ata_port *ap = link->ap;
	व्योम __iomem *base = ap->ioaddr.scr_addr + link->pmp * 0x10;

	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;

	अगर (ap->flags & SIS_FLAG_CFGSCR)
		वापस sis_scr_cfg_ग_लिखो(link, sc_reg, val);

	ioग_लिखो32(val, base + (sc_reg * 4));
	वापस 0;
पूर्ण

अटल पूर्णांक sis_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा ata_port_info pi = sis_port_info;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &pi, &pi पूर्ण;
	काष्ठा ata_host *host;
	u32 genctl, val;
	u8 pmr;
	u8 port2_start = 0x20;
	पूर्णांक i, rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/* check and see अगर the SCRs are in IO space or PCI cfg space */
	pci_पढ़ो_config_dword(pdev, SIS_GENCTL, &genctl);
	अगर ((genctl & GENCTL_IOMAPPED_SCR) == 0)
		pi.flags |= SIS_FLAG_CFGSCR;

	/* अगर hardware thinks SCRs are in IO space, but there are
	 * no IO resources asचिन्हित, change to PCI cfg space.
	 */
	अगर ((!(pi.flags & SIS_FLAG_CFGSCR)) &&
	    ((pci_resource_start(pdev, SIS_SCR_PCI_BAR) == 0) ||
	     (pci_resource_len(pdev, SIS_SCR_PCI_BAR) < 128))) अणु
		genctl &= ~GENCTL_IOMAPPED_SCR;
		pci_ग_लिखो_config_dword(pdev, SIS_GENCTL, genctl);
		pi.flags |= SIS_FLAG_CFGSCR;
	पूर्ण

	pci_पढ़ो_config_byte(pdev, SIS_PMR, &pmr);
	चयन (ent->device) अणु
	हाल 0x0180:
	हाल 0x0181:

		/* The PATA-handling is provided by pata_sis */
		चयन (pmr & 0x30) अणु
		हाल 0x10:
			ppi[1] = &sis_info133_क्रम_sata;
			अवरोध;

		हाल 0x30:
			ppi[0] = &sis_info133_क्रम_sata;
			अवरोध;
		पूर्ण
		अगर ((pmr & SIS_PMR_COMBINED) == 0) अणु
			dev_info(&pdev->dev,
				 "Detected SiS 180/181/964 chipset in SATA mode\n");
			port2_start = 64;
		पूर्ण अन्यथा अणु
			dev_info(&pdev->dev,
				 "Detected SiS 180/181 chipset in combined mode\n");
			port2_start = 0;
			pi.flags |= ATA_FLAG_SLAVE_POSS;
		पूर्ण
		अवरोध;

	हाल 0x0182:
	हाल 0x0183:
		pci_पढ़ो_config_dword(pdev, 0x6C, &val);
		अगर (val & (1L << 31)) अणु
			dev_info(&pdev->dev, "Detected SiS 182/965 chipset\n");
			pi.flags |= ATA_FLAG_SLAVE_POSS;
		पूर्ण अन्यथा अणु
			dev_info(&pdev->dev, "Detected SiS 182/965L chipset\n");
		पूर्ण
		अवरोध;

	हाल 0x1182:
		dev_info(&pdev->dev,
			 "Detected SiS 1182/966/680 SATA controller\n");
		pi.flags |= ATA_FLAG_SLAVE_POSS;
		अवरोध;

	हाल 0x1183:
		dev_info(&pdev->dev,
			 "Detected SiS 1183/966/966L/968/680 controller in PATA mode\n");
		ppi[0] = &sis_info133_क्रम_sata;
		ppi[1] = &sis_info133_क्रम_sata;
		अवरोध;
	पूर्ण

	rc = ata_pci_bmdma_prepare_host(pdev, ppi, &host);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		अगर (ap->flags & ATA_FLAG_SATA &&
		    ap->flags & ATA_FLAG_SLAVE_POSS) अणु
			rc = ata_slave_link_init(ap);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	अगर (!(pi.flags & SIS_FLAG_CFGSCR)) अणु
		व्योम __iomem *mmio;

		rc = pcim_iomap_regions(pdev, 1 << SIS_SCR_PCI_BAR, DRV_NAME);
		अगर (rc)
			वापस rc;
		mmio = host->iomap[SIS_SCR_PCI_BAR];

		host->ports[0]->ioaddr.scr_addr = mmio;
		host->ports[1]->ioaddr.scr_addr = mmio + port2_start;
	पूर्ण

	pci_set_master(pdev);
	pci_पूर्णांकx(pdev, 1);
	वापस ata_host_activate(host, pdev->irq, ata_bmdma_पूर्णांकerrupt,
				 IRQF_SHARED, &sis_sht);
पूर्ण

module_pci_driver(sis_pci_driver);
