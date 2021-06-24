<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pata_atp867x.c - ARTOP 867X 64bit 4-channel UDMA133 ATA controller driver
 *
 *	(C) 2009 Google Inc. John(Jung-Ik) Lee <jilee@google.com>
 *
 * Per Atp867 data sheet rev 1.2, Acard.
 * Based in part on early ide code from
 *	2003-2004 by Eric Uhrhane, Google, Inc.
 *
 * TODO:
 *   1. RAID features [comparison, XOR, striping, mirroring, etc.]
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा	DRV_NAME	"pata_atp867x"
#घोषणा	DRV_VERSION	"0.7.5"

/*
 * IO Registers
 * Note that all runसमय hot priv ports are cached in ap निजी_data
 */

क्रमागत अणु
	ATP867X_IO_CHANNEL_OFFSET	= 0x10,

	/*
	 * IO Register Bitfields
	 */

	ATP867X_IO_PIOSPD_ACTIVE_SHIFT	= 4,
	ATP867X_IO_PIOSPD_RECOVER_SHIFT	= 0,

	ATP867X_IO_DMAMODE_MSTR_SHIFT	= 0,
	ATP867X_IO_DMAMODE_MSTR_MASK	= 0x07,
	ATP867X_IO_DMAMODE_SLAVE_SHIFT	= 4,
	ATP867X_IO_DMAMODE_SLAVE_MASK	= 0x70,

	ATP867X_IO_DMAMODE_UDMA_6	= 0x07,
	ATP867X_IO_DMAMODE_UDMA_5	= 0x06,
	ATP867X_IO_DMAMODE_UDMA_4	= 0x05,
	ATP867X_IO_DMAMODE_UDMA_3	= 0x04,
	ATP867X_IO_DMAMODE_UDMA_2	= 0x03,
	ATP867X_IO_DMAMODE_UDMA_1	= 0x02,
	ATP867X_IO_DMAMODE_UDMA_0	= 0x01,
	ATP867X_IO_DMAMODE_DISABLE	= 0x00,

	ATP867X_IO_SYS_INFO_66MHZ	= 0x04,
	ATP867X_IO_SYS_INFO_SLOW_UDMA5	= 0x02,
	ATP867X_IO_SYS_MASK_RESERVED	= (~0xf1),

	ATP867X_IO_PORTSPD_VAL		= 0x1143,
	ATP867X_PREREAD_VAL		= 0x0200,

	ATP867X_NUM_PORTS		= 4,
	ATP867X_BAR_IOBASE		= 0,
	ATP867X_BAR_ROMBASE		= 6,
पूर्ण;

#घोषणा ATP867X_IOBASE(ap)		((ap)->host->iomap[0])
#घोषणा ATP867X_SYS_INFO(ap)		(0x3F + ATP867X_IOBASE(ap))

#घोषणा ATP867X_IO_PORTBASE(ap, port)	(0x00 + ATP867X_IOBASE(ap) + \
					(port) * ATP867X_IO_CHANNEL_OFFSET)
#घोषणा ATP867X_IO_DMABASE(ap, port)	(0x40 + \
					ATP867X_IO_PORTBASE((ap), (port)))

#घोषणा ATP867X_IO_STATUS(ap, port)	(0x07 + \
					ATP867X_IO_PORTBASE((ap), (port)))
#घोषणा ATP867X_IO_ALTSTATUS(ap, port)	(0x0E + \
					ATP867X_IO_PORTBASE((ap), (port)))

/*
 * hot priv ports
 */
#घोषणा ATP867X_IO_MSTRPIOSPD(ap, port)	(0x08 + \
					ATP867X_IO_DMABASE((ap), (port)))
#घोषणा ATP867X_IO_SLAVPIOSPD(ap, port)	(0x09 + \
					ATP867X_IO_DMABASE((ap), (port)))
#घोषणा ATP867X_IO_8BPIOSPD(ap, port)	(0x0A + \
					ATP867X_IO_DMABASE((ap), (port)))
#घोषणा ATP867X_IO_DMAMODE(ap, port)	(0x0B + \
					ATP867X_IO_DMABASE((ap), (port)))

#घोषणा ATP867X_IO_PORTSPD(ap, port)	(0x4A + \
					ATP867X_IO_PORTBASE((ap), (port)))
#घोषणा ATP867X_IO_PREREAD(ap, port)	(0x4C + \
					ATP867X_IO_PORTBASE((ap), (port)))

काष्ठा atp867x_priv अणु
	व्योम __iomem *dma_mode;
	व्योम __iomem *mstr_piospd;
	व्योम __iomem *slave_piospd;
	व्योम __iomem *eightb_piospd;
	पूर्णांक		pci66mhz;
पूर्ण;

अटल व्योम atp867x_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev	= to_pci_dev(ap->host->dev);
	काष्ठा atp867x_priv *dp = ap->निजी_data;
	u8 speed = adev->dma_mode;
	u8 b;
	u8 mode = speed - XFER_UDMA_0 + 1;

	/*
	 * Doc 6.6.9: decrease the udma mode value by 1 क्रम safer UDMA speed
	 * on 66MHz bus
	 *   rev-A: UDMA_1~4 (5, 6 no change)
	 *   rev-B: all UDMA modes
	 *   UDMA_0 stays not to disable UDMA
	 */
	अगर (dp->pci66mhz && mode > ATP867X_IO_DMAMODE_UDMA_0  &&
	   (pdev->device == PCI_DEVICE_ID_ARTOP_ATP867B ||
	    mode < ATP867X_IO_DMAMODE_UDMA_5))
		mode--;

	b = ioपढ़ो8(dp->dma_mode);
	अगर (adev->devno & 1) अणु
		b = (b & ~ATP867X_IO_DMAMODE_SLAVE_MASK) |
			(mode << ATP867X_IO_DMAMODE_SLAVE_SHIFT);
	पूर्ण अन्यथा अणु
		b = (b & ~ATP867X_IO_DMAMODE_MSTR_MASK) |
			(mode << ATP867X_IO_DMAMODE_MSTR_SHIFT);
	पूर्ण
	ioग_लिखो8(b, dp->dma_mode);
पूर्ण

अटल पूर्णांक atp867x_get_active_घड़ीs_shअगरted(काष्ठा ata_port *ap,
	अचिन्हित पूर्णांक clk)
अणु
	काष्ठा atp867x_priv *dp = ap->निजी_data;
	अचिन्हित अक्षर घड़ीs = clk;

	/*
	 * Doc 6.6.9: increase the घड़ी value by 1 क्रम safer PIO speed
	 * on 66MHz bus
	 */
	अगर (dp->pci66mhz)
		घड़ीs++;

	चयन (घड़ीs) अणु
	हाल 0:
		घड़ीs = 1;
		अवरोध;
	हाल 1 ... 6:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "ATP867X: active %dclk is invalid. "
			"Using 12clk.\n", clk);
		fallthrough;
	हाल 9 ... 12:
		घड़ीs = 7;	/* 12 clk */
		अवरोध;
	हाल 7:
	हाल 8:	/* शेष 8 clk */
		घड़ीs = 0;
		जाओ active_घड़ी_shअगरt_करोne;
	पूर्ण

active_घड़ी_shअगरt_करोne:
	वापस घड़ीs << ATP867X_IO_PIOSPD_ACTIVE_SHIFT;
पूर्ण

अटल पूर्णांक atp867x_get_recover_घड़ीs_shअगरted(अचिन्हित पूर्णांक clk)
अणु
	अचिन्हित अक्षर घड़ीs = clk;

	चयन (घड़ीs) अणु
	हाल 0:
		घड़ीs = 1;
		अवरोध;
	हाल 1 ... 11:
		अवरोध;
	हाल 13:
	हाल 14:
		--घड़ीs;	/* by the spec */
		अवरोध;
	हाल 15:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "ATP867X: recover %dclk is invalid. "
			"Using default 12clk.\n", clk);
		fallthrough;
	हाल 12:	/* शेष 12 clk */
		घड़ीs = 0;
		अवरोध;
	पूर्ण

	वापस घड़ीs << ATP867X_IO_PIOSPD_RECOVER_SHIFT;
पूर्ण

अटल व्योम atp867x_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा ata_device *peer = ata_dev_pair(adev);
	काष्ठा atp867x_priv *dp = ap->निजी_data;
	u8 speed = adev->pio_mode;
	काष्ठा ata_timing t, p;
	पूर्णांक T, UT;
	u8 b;

	T = 1000000000 / 33333;
	UT = T / 4;

	ata_timing_compute(adev, speed, &t, T, UT);
	अगर (peer && peer->pio_mode) अणु
		ata_timing_compute(peer, peer->pio_mode, &p, T, UT);
		ata_timing_merge(&p, &t, &t, ATA_TIMING_8BIT);
	पूर्ण

	b = ioपढ़ो8(dp->dma_mode);
	अगर (adev->devno & 1)
		b = (b & ~ATP867X_IO_DMAMODE_SLAVE_MASK);
	अन्यथा
		b = (b & ~ATP867X_IO_DMAMODE_MSTR_MASK);
	ioग_लिखो8(b, dp->dma_mode);

	b = atp867x_get_active_घड़ीs_shअगरted(ap, t.active) |
	    atp867x_get_recover_घड़ीs_shअगरted(t.recover);

	अगर (adev->devno & 1)
		ioग_लिखो8(b, dp->slave_piospd);
	अन्यथा
		ioग_लिखो8(b, dp->mstr_piospd);

	b = atp867x_get_active_घड़ीs_shअगरted(ap, t.act8b) |
	    atp867x_get_recover_घड़ीs_shअगरted(t.rec8b);

	ioग_लिखो8(b, dp->eightb_piospd);
पूर्ण

अटल पूर्णांक atp867x_cable_override(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_ARTOP &&
		(pdev->subप्रणाली_device == PCI_DEVICE_ID_ARTOP_ATP867A ||
		 pdev->subप्रणाली_device == PCI_DEVICE_ID_ARTOP_ATP867B)) अणु
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक atp867x_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अगर (atp867x_cable_override(pdev))
		वापस ATA_CBL_PATA40_SHORT;

	वापस ATA_CBL_PATA_UNK;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा atp867x_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations atp867x_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.cable_detect		= atp867x_cable_detect,
	.set_piomode		= atp867x_set_piomode,
	.set_dmamode		= atp867x_set_dmamode,
पूर्ण;


#अगर_घोषित	ATP867X_DEBUG
अटल व्योम atp867x_check_res(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ start, len;

	/* Check the PCI resources क्रम this channel are enabled */
	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		start = pci_resource_start(pdev, i);
		len   = pci_resource_len(pdev, i);
		prपूर्णांकk(KERN_DEBUG "ATP867X: resource start:len=%lx:%lx\n",
			start, len);
	पूर्ण
पूर्ण

अटल व्योम atp867x_check_ports(काष्ठा ata_port *ap, पूर्णांक port)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	काष्ठा atp867x_priv *dp = ap->निजी_data;

	prपूर्णांकk(KERN_DEBUG "ATP867X: port[%d] addresses\n"
		"  cmd_addr	=0x%llx, 0x%llx\n"
		"  ctl_addr	=0x%llx, 0x%llx\n"
		"  bmdma_addr	=0x%llx, 0x%llx\n"
		"  data_addr	=0x%llx\n"
		"  error_addr	=0x%llx\n"
		"  feature_addr	=0x%llx\n"
		"  nsect_addr	=0x%llx\n"
		"  lbal_addr	=0x%llx\n"
		"  lbam_addr	=0x%llx\n"
		"  lbah_addr	=0x%llx\n"
		"  device_addr	=0x%llx\n"
		"  status_addr	=0x%llx\n"
		"  command_addr	=0x%llx\n"
		"  dp->dma_mode	=0x%llx\n"
		"  dp->mstr_piospd	=0x%llx\n"
		"  dp->slave_piospd	=0x%llx\n"
		"  dp->eightb_piospd	=0x%llx\n"
		"  dp->pci66mhz		=0x%lx\n",
		port,
		(अचिन्हित दीर्घ दीर्घ)ioaddr->cmd_addr,
		(अचिन्हित दीर्घ दीर्घ)ATP867X_IO_PORTBASE(ap, port),
		(अचिन्हित दीर्घ दीर्घ)ioaddr->ctl_addr,
		(अचिन्हित दीर्घ दीर्घ)ATP867X_IO_ALTSTATUS(ap, port),
		(अचिन्हित दीर्घ दीर्घ)ioaddr->bmdma_addr,
		(अचिन्हित दीर्घ दीर्घ)ATP867X_IO_DMABASE(ap, port),
		(अचिन्हित दीर्घ दीर्घ)ioaddr->data_addr,
		(अचिन्हित दीर्घ दीर्घ)ioaddr->error_addr,
		(अचिन्हित दीर्घ दीर्घ)ioaddr->feature_addr,
		(अचिन्हित दीर्घ दीर्घ)ioaddr->nsect_addr,
		(अचिन्हित दीर्घ दीर्घ)ioaddr->lbal_addr,
		(अचिन्हित दीर्घ दीर्घ)ioaddr->lbam_addr,
		(अचिन्हित दीर्घ दीर्घ)ioaddr->lbah_addr,
		(अचिन्हित दीर्घ दीर्घ)ioaddr->device_addr,
		(अचिन्हित दीर्घ दीर्घ)ioaddr->status_addr,
		(अचिन्हित दीर्घ दीर्घ)ioaddr->command_addr,
		(अचिन्हित दीर्घ दीर्घ)dp->dma_mode,
		(अचिन्हित दीर्घ दीर्घ)dp->mstr_piospd,
		(अचिन्हित दीर्घ दीर्घ)dp->slave_piospd,
		(अचिन्हित दीर्घ दीर्घ)dp->eightb_piospd,
		(अचिन्हित दीर्घ)dp->pci66mhz);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक atp867x_set_priv(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा atp867x_priv *dp;
	पूर्णांक port = ap->port_no;

	dp = ap->निजी_data =
		devm_kzalloc(&pdev->dev, माप(*dp), GFP_KERNEL);
	अगर (dp == शून्य)
		वापस -ENOMEM;

	dp->dma_mode	 = ATP867X_IO_DMAMODE(ap, port);
	dp->mstr_piospd	 = ATP867X_IO_MSTRPIOSPD(ap, port);
	dp->slave_piospd = ATP867X_IO_SLAVPIOSPD(ap, port);
	dp->eightb_piospd = ATP867X_IO_8BPIOSPD(ap, port);

	dp->pci66mhz =
		ioपढ़ो8(ATP867X_SYS_INFO(ap)) & ATP867X_IO_SYS_INFO_66MHZ;

	वापस 0;
पूर्ण

अटल व्योम atp867x_fixup(काष्ठा ata_host *host)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	काष्ठा ata_port *ap = host->ports[0];
	पूर्णांक i;
	u8 v;

	/*
	 * Broken BIOS might not set latency high enough
	 */
	pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &v);
	अगर (v < 0x80) अणु
		v = 0x80;
		pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, v);
		prपूर्णांकk(KERN_DEBUG "ATP867X: set latency timer of device %s"
			" to %d\n", pci_name(pdev), v);
	पूर्ण

	/*
	 * init 8bit io ports speed(0aaarrrr) to 43h and
	 * init udma modes of master/slave to 0/0(11h)
	 */
	क्रम (i = 0; i < ATP867X_NUM_PORTS; i++)
		ioग_लिखो16(ATP867X_IO_PORTSPD_VAL, ATP867X_IO_PORTSPD(ap, i));

	/*
	 * init PreREAD counts
	 */
	क्रम (i = 0; i < ATP867X_NUM_PORTS; i++)
		ioग_लिखो16(ATP867X_PREREAD_VAL, ATP867X_IO_PREREAD(ap, i));

	v = ioपढ़ो8(ATP867X_IOBASE(ap) + 0x28);
	v &= 0xcf;	/* Enable INTA#: bit4=0 means enable */
	v |= 0xc0;	/* Enable PCI burst, MRM & not immediate पूर्णांकerrupts */
	ioग_लिखो8(v, ATP867X_IOBASE(ap) + 0x28);

	/*
	 * Turn off the over घड़ीed udma5 mode, only क्रम Rev-B
	 */
	v = ioपढ़ो8(ATP867X_SYS_INFO(ap));
	v &= ATP867X_IO_SYS_MASK_RESERVED;
	अगर (pdev->device == PCI_DEVICE_ID_ARTOP_ATP867B)
		v |= ATP867X_IO_SYS_INFO_SLOW_UDMA5;
	ioग_लिखो8(v, ATP867X_SYS_INFO(ap));
पूर्ण

अटल पूर्णांक atp867x_ata_pci_sff_init_host(काष्ठा ata_host *host)
अणु
	काष्ठा device *gdev = host->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(gdev);
	अचिन्हित पूर्णांक mask = 0;
	पूर्णांक i, rc;

	/*
	 * करो not map rombase
	 */
	rc = pcim_iomap_regions(pdev, 1 << ATP867X_BAR_IOBASE, DRV_NAME);
	अगर (rc == -EBUSY)
		pcim_pin_device(pdev);
	अगर (rc)
		वापस rc;
	host->iomap = pcim_iomap_table(pdev);

#अगर_घोषित	ATP867X_DEBUG
	atp867x_check_res(pdev);

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++)
		prपूर्णांकk(KERN_DEBUG "ATP867X: iomap[%d]=0x%llx\n", i,
			(अचिन्हित दीर्घ दीर्घ)(host->iomap[i]));
#पूर्ण_अगर

	/*
	 * request, iomap BARs and init port addresses accordingly
	 */
	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

		ioaddr->cmd_addr = ATP867X_IO_PORTBASE(ap, i);
		ioaddr->ctl_addr = ioaddr->altstatus_addr
				 = ATP867X_IO_ALTSTATUS(ap, i);
		ioaddr->bmdma_addr = ATP867X_IO_DMABASE(ap, i);

		ata_sff_std_ports(ioaddr);
		rc = atp867x_set_priv(ap);
		अगर (rc)
			वापस rc;

#अगर_घोषित	ATP867X_DEBUG
		atp867x_check_ports(ap, i);
#पूर्ण_अगर
		ata_port_desc(ap, "cmd 0x%lx ctl 0x%lx",
			(अचिन्हित दीर्घ)ioaddr->cmd_addr,
			(अचिन्हित दीर्घ)ioaddr->ctl_addr);
		ata_port_desc(ap, "bmdma 0x%lx",
			(अचिन्हित दीर्घ)ioaddr->bmdma_addr);

		mask |= 1 << i;
	पूर्ण

	अगर (!mask) अणु
		dev_err(gdev, "no available native port\n");
		वापस -ENODEV;
	पूर्ण

	atp867x_fixup(host);

	वापस dma_set_mask_and_coherent(&pdev->dev, ATA_DMA_MASK);
पूर्ण

अटल पूर्णांक atp867x_init_one(काष्ठा pci_dev *pdev,
	स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info_867x = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.udma_mask 	= ATA_UDMA6,
		.port_ops	= &atp867x_ops,
	पूर्ण;

	काष्ठा ata_host *host;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info_867x, शून्य पूर्ण;
	पूर्णांक rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	prपूर्णांकk(KERN_INFO "ATP867X: ATP867 ATA UDMA133 controller (rev %02X)",
		pdev->device);

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, ATP867X_NUM_PORTS);
	अगर (!host) अणु
		dev_err(&pdev->dev, "failed to allocate ATA host\n");
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण

	rc = atp867x_ata_pci_sff_init_host(host);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed to init host\n");
		जाओ err_out;
	पूर्ण

	pci_set_master(pdev);

	rc = ata_host_activate(host, pdev->irq, ata_bmdma_पूर्णांकerrupt,
				IRQF_SHARED, &atp867x_sht);
	अगर (rc)
		dev_err(&pdev->dev, "failed to activate host\n");

err_out:
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक atp867x_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	atp867x_fixup(host);

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pci_device_id atp867x_pci_tbl[] = अणु
	अणु PCI_VDEVICE(ARTOP, PCI_DEVICE_ID_ARTOP_ATP867A),	0 पूर्ण,
	अणु PCI_VDEVICE(ARTOP, PCI_DEVICE_ID_ARTOP_ATP867B),	0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver atp867x_driver = अणु
	.name 		= DRV_NAME,
	.id_table 	= atp867x_pci_tbl,
	.probe 		= atp867x_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= atp867x_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(atp867x_driver);

MODULE_AUTHOR("John(Jung-Ik) Lee, Google Inc.");
MODULE_DESCRIPTION("low level driver for Artop/Acard 867x ATA controller");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, atp867x_pci_tbl);
MODULE_VERSION(DRV_VERSION);
