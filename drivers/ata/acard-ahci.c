<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 *  acard-ahci.c - ACard AHCI SATA support
 *
 *  Maपूर्णांकained by:  Tejun Heo <tj@kernel.org>
 *		    Please ALWAYS copy linux-ide@vger.kernel.org
 *		    on emails.
 *
 *  Copyright 2010 Red Hat, Inc.
 *
 * libata करोcumentation is available via 'make {ps|pdf}docs',
 * as Documentation/driver-api/libata.rst
 *
 * AHCI hardware करोcumentation:
 * http://www.पूर्णांकel.com/technology/serialata/pdf/rev1_0.pdf
 * http://www.पूर्णांकel.com/technology/serialata/pdf/rev1_1.pdf
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/gfp.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <linux/libata.h>
#समावेश "ahci.h"

#घोषणा DRV_NAME	"acard-ahci"
#घोषणा DRV_VERSION	"1.0"

/*
  Received FIS काष्ठाure limited to 80h.
*/

#घोषणा ACARD_AHCI_RX_FIS_SZ 128

क्रमागत अणु
	AHCI_PCI_BAR		= 5,
पूर्ण;

क्रमागत board_ids अणु
	board_acard_ahci,
पूर्ण;

काष्ठा acard_sg अणु
	__le32			addr;
	__le32			addr_hi;
	__le32			reserved;
	__le32			size;	 /* bit 31 (EOT) max==0x10000 (64k) */
पूर्ण;

अटल क्रमागत ata_completion_errors acard_ahci_qc_prep(काष्ठा ata_queued_cmd *qc);
अटल bool acard_ahci_qc_fill_rtf(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक acard_ahci_port_start(काष्ठा ata_port *ap);
अटल पूर्णांक acard_ahci_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acard_ahci_pci_device_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg);
अटल पूर्णांक acard_ahci_pci_device_resume(काष्ठा pci_dev *pdev);
#पूर्ण_अगर

अटल काष्ठा scsi_host_ढाँचा acard_ahci_sht = अणु
	AHCI_SHT("acard-ahci"),
पूर्ण;

अटल काष्ठा ata_port_operations acard_ops = अणु
	.inherits		= &ahci_ops,
	.qc_prep		= acard_ahci_qc_prep,
	.qc_fill_rtf		= acard_ahci_qc_fill_rtf,
	.port_start             = acard_ahci_port_start,
पूर्ण;

#घोषणा AHCI_HFLAGS(flags)	.निजी_data	= (व्योम *)(flags)

अटल स्थिर काष्ठा ata_port_info acard_ahci_port_info[] = अणु
	[board_acard_ahci] =
	अणु
		AHCI_HFLAGS	(AHCI_HFLAG_NO_NCQ),
		.flags		= AHCI_FLAG_COMMON,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &acard_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id acard_ahci_pci_tbl[] = अणु
	/* ACard */
	अणु PCI_VDEVICE(ARTOP, 0x000d), board_acard_ahci पूर्ण, /* ATP8620 */

	अणु पूर्ण    /* terminate list */
पूर्ण;

अटल काष्ठा pci_driver acard_ahci_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= acard_ahci_pci_tbl,
	.probe			= acard_ahci_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= acard_ahci_pci_device_suspend,
	.resume			= acard_ahci_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acard_ahci_pci_device_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	u32 ctl;

	अगर (mesg.event & PM_EVENT_SUSPEND &&
	    hpriv->flags & AHCI_HFLAG_NO_SUSPEND) अणु
		dev_err(&pdev->dev,
			"BIOS update required for suspend/resume\n");
		वापस -EIO;
	पूर्ण

	अगर (mesg.event & PM_EVENT_SLEEP) अणु
		/* AHCI spec rev1.1 section 8.3.3:
		 * Software must disable पूर्णांकerrupts prior to requesting a
		 * transition of the HBA to D3 state.
		 */
		ctl = पढ़ोl(mmio + HOST_CTL);
		ctl &= ~HOST_IRQ_EN;
		ग_लिखोl(ctl, mmio + HOST_CTL);
		पढ़ोl(mmio + HOST_CTL); /* flush */
	पूर्ण

	वापस ata_pci_device_suspend(pdev, mesg);
पूर्ण

अटल पूर्णांक acard_ahci_pci_device_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	अगर (pdev->dev.घातer.घातer_state.event == PM_EVENT_SUSPEND) अणु
		rc = ahci_reset_controller(host);
		अगर (rc)
			वापस rc;

		ahci_init_controller(host);
	पूर्ण

	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम acard_ahci_pci_prपूर्णांक_info(काष्ठा ata_host *host)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	u16 cc;
	स्थिर अक्षर *scc_s;

	pci_पढ़ो_config_word(pdev, 0x0a, &cc);
	अगर (cc == PCI_CLASS_STORAGE_IDE)
		scc_s = "IDE";
	अन्यथा अगर (cc == PCI_CLASS_STORAGE_SATA)
		scc_s = "SATA";
	अन्यथा अगर (cc == PCI_CLASS_STORAGE_RAID)
		scc_s = "RAID";
	अन्यथा
		scc_s = "unknown";

	ahci_prपूर्णांक_info(host, scc_s);
पूर्ण

अटल अचिन्हित पूर्णांक acard_ahci_fill_sg(काष्ठा ata_queued_cmd *qc, व्योम *cmd_tbl)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा acard_sg *acard_sg = cmd_tbl + AHCI_CMD_TBL_HDR_SZ;
	अचिन्हित पूर्णांक si, last_si = 0;

	VPRINTK("ENTER\n");

	/*
	 * Next, the S/G list.
	 */
	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		dma_addr_t addr = sg_dma_address(sg);
		u32 sg_len = sg_dma_len(sg);

		/*
		 * ACard note:
		 * We must set an end-of-table (EOT) bit,
		 * and the segment cannot exceed 64k (0x10000)
		 */
		acard_sg[si].addr = cpu_to_le32(addr & 0xffffffff);
		acard_sg[si].addr_hi = cpu_to_le32((addr >> 16) >> 16);
		acard_sg[si].size = cpu_to_le32(sg_len);
		last_si = si;
	पूर्ण

	acard_sg[last_si].size |= cpu_to_le32(1 << 31);	/* set EOT */

	वापस si;
पूर्ण

अटल क्रमागत ata_completion_errors acard_ahci_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	पूर्णांक is_atapi = ata_is_atapi(qc->tf.protocol);
	व्योम *cmd_tbl;
	u32 opts;
	स्थिर u32 cmd_fis_len = 5; /* five dwords */

	/*
	 * Fill in command table inक्रमmation.  First, the header,
	 * a SATA Register - Host to Device command FIS.
	 */
	cmd_tbl = pp->cmd_tbl + qc->hw_tag * AHCI_CMD_TBL_SZ;

	ata_tf_to_fis(&qc->tf, qc->dev->link->pmp, 1, cmd_tbl);
	अगर (is_atapi) अणु
		स_रखो(cmd_tbl + AHCI_CMD_TBL_CDB, 0, 32);
		स_नकल(cmd_tbl + AHCI_CMD_TBL_CDB, qc->cdb, qc->dev->cdb_len);
	पूर्ण

	अगर (qc->flags & ATA_QCFLAG_DMAMAP)
		acard_ahci_fill_sg(qc, cmd_tbl);

	/*
	 * Fill in command slot inक्रमmation.
	 *
	 * ACard note: prd table length not filled in
	 */
	opts = cmd_fis_len | (qc->dev->link->pmp << 12);
	अगर (qc->tf.flags & ATA_TFLAG_WRITE)
		opts |= AHCI_CMD_WRITE;
	अगर (is_atapi)
		opts |= AHCI_CMD_ATAPI | AHCI_CMD_PREFETCH;

	ahci_fill_cmd_slot(pp, qc->hw_tag, opts);

	वापस AC_ERR_OK;
पूर्ण

अटल bool acard_ahci_qc_fill_rtf(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ahci_port_priv *pp = qc->ap->निजी_data;
	u8 *rx_fis = pp->rx_fis;

	अगर (pp->fbs_enabled)
		rx_fis += qc->dev->link->pmp * ACARD_AHCI_RX_FIS_SZ;

	/*
	 * After a successful execution of an ATA PIO data-in command,
	 * the device करोesn't send D2H Reg FIS to update the TF and
	 * the host should take TF and E_Status from the preceding PIO
	 * Setup FIS.
	 */
	अगर (qc->tf.protocol == ATA_PROT_PIO && qc->dma_dir == DMA_FROM_DEVICE &&
	    !(qc->flags & ATA_QCFLAG_FAILED)) अणु
		ata_tf_from_fis(rx_fis + RX_FIS_PIO_SETUP, &qc->result_tf);
		qc->result_tf.command = (rx_fis + RX_FIS_PIO_SETUP)[15];
	पूर्ण अन्यथा
		ata_tf_from_fis(rx_fis + RX_FIS_D2H_REG, &qc->result_tf);

	वापस true;
पूर्ण

अटल पूर्णांक acard_ahci_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा device *dev = ap->host->dev;
	काष्ठा ahci_port_priv *pp;
	व्योम *mem;
	dma_addr_t mem_dma;
	माप_प्रकार dma_sz, rx_fis_sz;

	pp = devm_kzalloc(dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;

	/* check FBS capability */
	अगर ((hpriv->cap & HOST_CAP_FBS) && sata_pmp_supported(ap)) अणु
		व्योम __iomem *port_mmio = ahci_port_base(ap);
		u32 cmd = पढ़ोl(port_mmio + PORT_CMD);
		अगर (cmd & PORT_CMD_FBSCP)
			pp->fbs_supported = true;
		अन्यथा अगर (hpriv->flags & AHCI_HFLAG_YES_FBS) अणु
			dev_info(dev, "port %d can do FBS, forcing FBSCP\n",
				 ap->port_no);
			pp->fbs_supported = true;
		पूर्ण अन्यथा
			dev_warn(dev, "port %d is not capable of FBS\n",
				 ap->port_no);
	पूर्ण

	अगर (pp->fbs_supported) अणु
		dma_sz = AHCI_PORT_PRIV_FBS_DMA_SZ;
		rx_fis_sz = ACARD_AHCI_RX_FIS_SZ * 16;
	पूर्ण अन्यथा अणु
		dma_sz = AHCI_PORT_PRIV_DMA_SZ;
		rx_fis_sz = ACARD_AHCI_RX_FIS_SZ;
	पूर्ण

	mem = dmam_alloc_coherent(dev, dma_sz, &mem_dma, GFP_KERNEL);
	अगर (!mem)
		वापस -ENOMEM;

	/*
	 * First item in chunk of DMA memory: 32-slot command table,
	 * 32 bytes each in size
	 */
	pp->cmd_slot = mem;
	pp->cmd_slot_dma = mem_dma;

	mem += AHCI_CMD_SLOT_SZ;
	mem_dma += AHCI_CMD_SLOT_SZ;

	/*
	 * Second item: Received-FIS area
	 */
	pp->rx_fis = mem;
	pp->rx_fis_dma = mem_dma;

	mem += rx_fis_sz;
	mem_dma += rx_fis_sz;

	/*
	 * Third item: data area क्रम storing a single command
	 * and its scatter-gather table
	 */
	pp->cmd_tbl = mem;
	pp->cmd_tbl_dma = mem_dma;

	/*
	 * Save off initial list of पूर्णांकerrupts to be enabled.
	 * This could be changed later
	 */
	pp->पूर्णांकr_mask = DEF_PORT_IRQ;

	ap->निजी_data = pp;

	/* engage engines, captain */
	वापस ahci_port_resume(ap);
पूर्ण

अटल पूर्णांक acard_ahci_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित पूर्णांक board_id = ent->driver_data;
	काष्ठा ata_port_info pi = acard_ahci_port_info[board_id];
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &pi, शून्य पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ahci_host_priv *hpriv;
	काष्ठा ata_host *host;
	पूर्णांक n_ports, i, rc;

	VPRINTK("ENTER\n");

	WARN_ON((पूर्णांक)ATA_MAX_QUEUE > AHCI_MAX_CMDS);

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* acquire resources */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/* AHCI controllers often implement SFF compatible पूर्णांकerface.
	 * Grab all PCI BARs just in हाल.
	 */
	rc = pcim_iomap_regions_request_all(pdev, 1 << AHCI_PCI_BAR, DRV_NAME);
	अगर (rc == -EBUSY)
		pcim_pin_device(pdev);
	अगर (rc)
		वापस rc;

	hpriv = devm_kzalloc(dev, माप(*hpriv), GFP_KERNEL);
	अगर (!hpriv)
		वापस -ENOMEM;

	hpriv->irq = pdev->irq;
	hpriv->flags |= (अचिन्हित दीर्घ)pi.निजी_data;

	अगर (!(hpriv->flags & AHCI_HFLAG_NO_MSI))
		pci_enable_msi(pdev);

	hpriv->mmio = pcim_iomap_table(pdev)[AHCI_PCI_BAR];

	/* save initial config */
	ahci_save_initial_config(&pdev->dev, hpriv);

	/* prepare host */
	अगर (hpriv->cap & HOST_CAP_NCQ)
		pi.flags |= ATA_FLAG_NCQ;

	अगर (hpriv->cap & HOST_CAP_PMP)
		pi.flags |= ATA_FLAG_PMP;

	ahci_set_em_messages(hpriv, &pi);

	/* CAP.NP someबार indicate the index of the last enabled
	 * port, at other बार, that of the last possible port, so
	 * determining the maximum port number requires looking at
	 * both CAP.NP and port_map.
	 */
	n_ports = max(ahci_nr_ports(hpriv->cap), fls(hpriv->port_map));

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, n_ports);
	अगर (!host)
		वापस -ENOMEM;
	host->निजी_data = hpriv;

	अगर (!(hpriv->cap & HOST_CAP_SSS) || ahci_ignore_sss)
		host->flags |= ATA_HOST_PARALLEL_SCAN;
	अन्यथा
		prपूर्णांकk(KERN_INFO "ahci: SSS flag set, parallel bus scan disabled\n");

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		ata_port_pbar_desc(ap, AHCI_PCI_BAR, -1, "abar");
		ata_port_pbar_desc(ap, AHCI_PCI_BAR,
				   0x100 + ap->port_no * 0x80, "port");

		/* set initial link pm policy */
		/*
		ap->pm_policy = NOT_AVAILABLE;
		*/
		/* disabled/not-implemented port */
		अगर (!(hpriv->port_map & (1 << i)))
			ap->ops = &ata_dummy_port_ops;
	पूर्ण

	/* initialize adapter */
	rc = dma_set_mask_and_coherent(&pdev->dev,
			DMA_BIT_MASK((hpriv->cap & HOST_CAP_64) ? 64 : 32));
	अगर (rc) अणु
		dev_err(&pdev->dev, "DMA enable failed\n");
		वापस rc;
	पूर्ण

	rc = ahci_reset_controller(host);
	अगर (rc)
		वापस rc;

	ahci_init_controller(host);
	acard_ahci_pci_prपूर्णांक_info(host);

	pci_set_master(pdev);
	वापस ahci_host_activate(host, &acard_ahci_sht);
पूर्ण

module_pci_driver(acard_ahci_pci_driver);

MODULE_AUTHOR("Jeff Garzik");
MODULE_DESCRIPTION("ACard AHCI SATA low-level driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, acard_ahci_pci_tbl);
MODULE_VERSION(DRV_VERSION);
