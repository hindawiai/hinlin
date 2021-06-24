<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sata_uli.c - ULi Electronics SATA
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Hardware करोcumentation available under NDA.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"sata_uli"
#घोषणा DRV_VERSION	"1.3"

क्रमागत अणु
	uli_5289		= 0,
	uli_5287		= 1,
	uli_5281		= 2,

	uli_max_ports		= 4,

	/* PCI configuration रेजिस्टरs */
	ULI5287_BASE		= 0x90, /* sata0 phy SCR रेजिस्टरs */
	ULI5287_OFFS		= 0x10, /* offset from sata0->sata1 phy regs */
	ULI5281_BASE		= 0x60, /* sata0 phy SCR  रेजिस्टरs */
	ULI5281_OFFS		= 0x60, /* offset from sata0->sata1 phy regs */
पूर्ण;

काष्ठा uli_priv अणु
	अचिन्हित पूर्णांक		scr_cfg_addr[uli_max_ports];
पूर्ण;

अटल पूर्णांक uli_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल पूर्णांक uli_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val);
अटल पूर्णांक uli_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val);

अटल स्थिर काष्ठा pci_device_id uli_pci_tbl[] = अणु
	अणु PCI_VDEVICE(AL, 0x5289), uli_5289 पूर्ण,
	अणु PCI_VDEVICE(AL, 0x5287), uli_5287 पूर्ण,
	अणु PCI_VDEVICE(AL, 0x5281), uli_5281 पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver uli_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= uli_pci_tbl,
	.probe			= uli_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा uli_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations uli_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.scr_पढ़ो		= uli_scr_पढ़ो,
	.scr_ग_लिखो		= uli_scr_ग_लिखो,
	.hardreset		= ATA_OP_शून्य,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info uli_port_info = अणु
	.flags		= ATA_FLAG_SATA | ATA_FLAG_IGN_SIMPLEX,
	.pio_mask       = ATA_PIO4,
	.udma_mask      = ATA_UDMA6,
	.port_ops       = &uli_ops,
पूर्ण;


MODULE_AUTHOR("Peer Chen");
MODULE_DESCRIPTION("low-level driver for ULi Electronics SATA controller");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, uli_pci_tbl);
MODULE_VERSION(DRV_VERSION);

अटल अचिन्हित पूर्णांक get_scr_cfg_addr(काष्ठा ata_port *ap, अचिन्हित पूर्णांक sc_reg)
अणु
	काष्ठा uli_priv *hpriv = ap->host->निजी_data;
	वापस hpriv->scr_cfg_addr[ap->port_no] + (4 * sc_reg);
पूर्ण

अटल u32 uli_scr_cfg_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(link->ap->host->dev);
	अचिन्हित पूर्णांक cfg_addr = get_scr_cfg_addr(link->ap, sc_reg);
	u32 val;

	pci_पढ़ो_config_dword(pdev, cfg_addr, &val);
	वापस val;
पूर्ण

अटल व्योम uli_scr_cfg_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक scr, u32 val)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(link->ap->host->dev);
	अचिन्हित पूर्णांक cfg_addr = get_scr_cfg_addr(link->ap, scr);

	pci_ग_लिखो_config_dword(pdev, cfg_addr, val);
पूर्ण

अटल पूर्णांक uli_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 *val)
अणु
	अगर (sc_reg > SCR_CONTROL)
		वापस -EINVAL;

	*val = uli_scr_cfg_पढ़ो(link, sc_reg);
	वापस 0;
पूर्ण

अटल पूर्णांक uli_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg, u32 val)
अणु
	अगर (sc_reg > SCR_CONTROL) //SCR_CONTROL=2, SCR_ERROR=1, SCR_STATUS=0
		वापस -EINVAL;

	uli_scr_cfg_ग_लिखो(link, sc_reg, val);
	वापस 0;
पूर्ण

अटल पूर्णांक uli_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &uli_port_info, शून्य पूर्ण;
	अचिन्हित पूर्णांक board_idx = (अचिन्हित पूर्णांक) ent->driver_data;
	काष्ठा ata_host *host;
	काष्ठा uli_priv *hpriv;
	व्योम __iomem * स्थिर *iomap;
	काष्ठा ata_ioports *ioaddr;
	पूर्णांक n_ports, rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	n_ports = 2;
	अगर (board_idx == uli_5287)
		n_ports = 4;

	/* allocate the host */
	host = ata_host_alloc_pinfo(&pdev->dev, ppi, n_ports);
	अगर (!host)
		वापस -ENOMEM;

	hpriv = devm_kzalloc(&pdev->dev, माप(*hpriv), GFP_KERNEL);
	अगर (!hpriv)
		वापस -ENOMEM;
	host->निजी_data = hpriv;

	/* the first two ports are standard SFF */
	rc = ata_pci_sff_init_host(host);
	अगर (rc)
		वापस rc;

	ata_pci_bmdma_init(host);

	iomap = host->iomap;

	चयन (board_idx) अणु
	हाल uli_5287:
		/* If there are four, the last two live right after
		 * the standard SFF ports.
		 */
		hpriv->scr_cfg_addr[0] = ULI5287_BASE;
		hpriv->scr_cfg_addr[1] = ULI5287_BASE + ULI5287_OFFS;

		ioaddr = &host->ports[2]->ioaddr;
		ioaddr->cmd_addr = iomap[0] + 8;
		ioaddr->altstatus_addr =
		ioaddr->ctl_addr = (व्योम __iomem *)
			((अचिन्हित दीर्घ)iomap[1] | ATA_PCI_CTL_OFS) + 4;
		ioaddr->bmdma_addr = iomap[4] + 16;
		hpriv->scr_cfg_addr[2] = ULI5287_BASE + ULI5287_OFFS*4;
		ata_sff_std_ports(ioaddr);

		ata_port_desc(host->ports[2],
			"cmd 0x%llx ctl 0x%llx bmdma 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 0) + 8,
			((अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 1) | ATA_PCI_CTL_OFS) + 4,
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 4) + 16);

		ioaddr = &host->ports[3]->ioaddr;
		ioaddr->cmd_addr = iomap[2] + 8;
		ioaddr->altstatus_addr =
		ioaddr->ctl_addr = (व्योम __iomem *)
			((अचिन्हित दीर्घ)iomap[3] | ATA_PCI_CTL_OFS) + 4;
		ioaddr->bmdma_addr = iomap[4] + 24;
		hpriv->scr_cfg_addr[3] = ULI5287_BASE + ULI5287_OFFS*5;
		ata_sff_std_ports(ioaddr);

		ata_port_desc(host->ports[2],
			"cmd 0x%llx ctl 0x%llx bmdma 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 2) + 9,
			((अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 3) | ATA_PCI_CTL_OFS) + 4,
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 4) + 24);

		अवरोध;

	हाल uli_5289:
		hpriv->scr_cfg_addr[0] = ULI5287_BASE;
		hpriv->scr_cfg_addr[1] = ULI5287_BASE + ULI5287_OFFS;
		अवरोध;

	हाल uli_5281:
		hpriv->scr_cfg_addr[0] = ULI5281_BASE;
		hpriv->scr_cfg_addr[1] = ULI5281_BASE + ULI5281_OFFS;
		अवरोध;

	शेष:
		BUG();
		अवरोध;
	पूर्ण

	pci_set_master(pdev);
	pci_पूर्णांकx(pdev, 1);
	वापस ata_host_activate(host, pdev->irq, ata_bmdma_पूर्णांकerrupt,
				 IRQF_SHARED, &uli_sht);
पूर्ण

module_pci_driver(uli_pci_driver);
