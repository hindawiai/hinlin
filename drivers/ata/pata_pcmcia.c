<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   pata_pcmcia.c - PCMCIA PATA controller driver.
 *   Copyright 2005-2006 Red Hat Inc, all rights reserved.
 *   PCMCIA ident update Copyright 2006 Marcin Juszkiewicz
 *						<खोलोembedded@hrw.one.pl>
 *
 *   Heavily based upon ide-cs.c
 *   The initial developer of the original code is David A. Hinds
 *   <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 *   are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/ata.h>
#समावेश <linux/libata.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ciscode.h>


#घोषणा DRV_NAME "pata_pcmcia"
#घोषणा DRV_VERSION "0.3.5"

/**
 *	pcmcia_set_mode	-	PCMCIA specअगरic mode setup
 *	@link: link
 *	@r_failed_dev: Return poपूर्णांकer क्रम failed device
 *
 *	Perक्रमm the tuning and setup of the devices and timings, which
 *	क्रम PCMCIA is the same as any other controller. We wrap it however
 *	as we need to spot hardware with incorrect or missing master/slave
 *	decode, which alas is embarrassingly common in the PC world
 */

अटल पूर्णांक pcmcia_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **r_failed_dev)
अणु
	काष्ठा ata_device *master = &link->device[0];
	काष्ठा ata_device *slave = &link->device[1];

	अगर (!ata_dev_enabled(master) || !ata_dev_enabled(slave))
		वापस ata_करो_set_mode(link, r_failed_dev);

	अगर (स_भेद(master->id + ATA_ID_FW_REV,  slave->id + ATA_ID_FW_REV,
			   ATA_ID_FW_REV_LEN + ATA_ID_PROD_LEN) == 0) अणु
		/* Suspicious match, but could be two cards from
		   the same venकरोr - check serial */
		अगर (स_भेद(master->id + ATA_ID_SERNO, slave->id + ATA_ID_SERNO,
			   ATA_ID_SERNO_LEN) == 0 && master->id[ATA_ID_SERNO] >> 8) अणु
			ata_dev_warn(slave, "is a ghost device, ignoring\n");
			ata_dev_disable(slave);
		पूर्ण
	पूर्ण
	वापस ata_करो_set_mode(link, r_failed_dev);
पूर्ण

/**
 *	pcmcia_set_mode_8bit	-	PCMCIA specअगरic mode setup
 *	@link: link
 *	@r_failed_dev: Return poपूर्णांकer क्रम failed device
 *
 *	For the simple emulated 8bit stuff the less we करो the better.
 */

अटल पूर्णांक pcmcia_set_mode_8bit(काष्ठा ata_link *link,
				काष्ठा ata_device **r_failed_dev)
अणु
	वापस 0;
पूर्ण

/**
 *	ata_data_xfer_8bit	 -	Transfer data by 8bit PIO
 *	@qc: queued command
 *	@buf: data buffer
 *	@buflen: buffer length
 *	@rw: पढ़ो/ग_लिखो
 *
 *	Transfer data from/to the device data रेजिस्टर by 8 bit PIO.
 *
 *	LOCKING:
 *	Inherited from caller.
 */

अटल अचिन्हित पूर्णांक ata_data_xfer_8bit(काष्ठा ata_queued_cmd *qc,
				अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	काष्ठा ata_port *ap = qc->dev->link->ap;

	अगर (rw == READ)
		ioपढ़ो8_rep(ap->ioaddr.data_addr, buf, buflen);
	अन्यथा
		ioग_लिखो8_rep(ap->ioaddr.data_addr, buf, buflen);

	वापस buflen;
पूर्ण

/**
 *	pcmcia_8bit_drain_fअगरo - Stock FIFO drain logic क्रम SFF controllers
 *	@qc: command
 *
 *	Drain the FIFO and device of any stuck data following a command
 *	failing to complete. In some हालs this is necessary beक्रमe a
 *	reset will recover the device.
 *
 */

अटल व्योम pcmcia_8bit_drain_fअगरo(काष्ठा ata_queued_cmd *qc)
अणु
	पूर्णांक count;
	काष्ठा ata_port *ap;

	/* We only need to flush incoming data when a command was running */
	अगर (qc == शून्य || qc->dma_dir == DMA_TO_DEVICE)
		वापस;

	ap = qc->ap;

	/* Drain up to 64K of data beक्रमe we give up this recovery method */
	क्रम (count = 0; (ap->ops->sff_check_status(ap) & ATA_DRQ)
							&& count++ < 65536;)
		ioपढ़ो8(ap->ioaddr.data_addr);

	अगर (count)
		ata_port_warn(ap, "drained %d bytes to clear DRQ\n", count);

पूर्ण

अटल काष्ठा scsi_host_ढाँचा pcmcia_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations pcmcia_port_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.sff_data_xfer	= ata_sff_data_xfer32,
	.cable_detect	= ata_cable_40wire,
	.set_mode	= pcmcia_set_mode,
पूर्ण;

अटल काष्ठा ata_port_operations pcmcia_8bit_port_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.sff_data_xfer	= ata_data_xfer_8bit,
	.cable_detect	= ata_cable_40wire,
	.set_mode	= pcmcia_set_mode_8bit,
	.sff_drain_fअगरo	= pcmcia_8bit_drain_fअगरo,
पूर्ण;


अटल पूर्णांक pcmcia_check_one_config(काष्ठा pcmcia_device *pdev, व्योम *priv_data)
अणु
	पूर्णांक *is_kme = priv_data;

	अगर ((pdev->resource[0]->flags & IO_DATA_PATH_WIDTH)
	    != IO_DATA_PATH_WIDTH_8) अणु
		pdev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
		pdev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
	पूर्ण
	pdev->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
	pdev->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;

	अगर (pdev->resource[1]->end) अणु
		pdev->resource[0]->end = 8;
		pdev->resource[1]->end = (*is_kme) ? 2 : 1;
	पूर्ण अन्यथा अणु
		अगर (pdev->resource[0]->end < 16)
			वापस -ENODEV;
	पूर्ण

	वापस pcmcia_request_io(pdev);
पूर्ण

/**
 *	pcmcia_init_one		-	attach a PCMCIA पूर्णांकerface
 *	@pdev: pcmcia device
 *
 *	Register a PCMCIA IDE पूर्णांकerface. Such पूर्णांकerfaces are PIO 0 and
 *	shared IRQ.
 */

अटल पूर्णांक pcmcia_init_one(काष्ठा pcmcia_device *pdev)
अणु
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	पूर्णांक is_kme = 0, ret = -ENOMEM, p;
	अचिन्हित दीर्घ io_base, ctl_base;
	व्योम __iomem *io_addr, *ctl_addr;
	पूर्णांक n_ports = 1;
	काष्ठा ata_port_operations *ops = &pcmcia_port_ops;

	/* Set up attributes in order to probe card and get resources */
	pdev->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO |
		CONF_AUTO_SET_VPP | CONF_AUTO_CHECK_VCC;

	/* See अगर we have a manufacturer identअगरier. Use it to set is_kme क्रम
	   venकरोr quirks */
	is_kme = ((pdev->manf_id == MANFID_KME) &&
		  ((pdev->card_id == PRODID_KME_KXLC005_A) ||
		   (pdev->card_id == PRODID_KME_KXLC005_B)));

	अगर (pcmcia_loop_config(pdev, pcmcia_check_one_config, &is_kme)) अणु
		pdev->config_flags &= ~CONF_AUTO_CHECK_VCC;
		अगर (pcmcia_loop_config(pdev, pcmcia_check_one_config, &is_kme))
			जाओ failed; /* No suitable config found */
	पूर्ण
	io_base = pdev->resource[0]->start;
	अगर (pdev->resource[1]->end)
		ctl_base = pdev->resource[1]->start;
	अन्यथा
		ctl_base = pdev->resource[0]->start + 0x0e;

	अगर (!pdev->irq)
		जाओ failed;

	ret = pcmcia_enable_device(pdev);
	अगर (ret)
		जाओ failed;

	/* iomap */
	ret = -ENOMEM;
	io_addr = devm_ioport_map(&pdev->dev, io_base, 8);
	ctl_addr = devm_ioport_map(&pdev->dev, ctl_base, 1);
	अगर (!io_addr || !ctl_addr)
		जाओ failed;

	/* Success. Disable the IRQ nIEN line, करो quirks */
	ioग_लिखो8(0x02, ctl_addr);
	अगर (is_kme)
		ioग_लिखो8(0x81, ctl_addr + 0x01);

	/* FIXME: Could be more ports at base + 0x10 but we only deal with
	   one right now */
	अगर (resource_size(pdev->resource[0]) >= 0x20)
		n_ports = 2;

	अगर (pdev->manf_id == 0x0097 && pdev->card_id == 0x1620)
		ops = &pcmcia_8bit_port_ops;
	/*
	 *	Having करोne the PCMCIA plumbing the ATA side is relatively
	 *	sane.
	 */
	ret = -ENOMEM;
	host = ata_host_alloc(&pdev->dev, n_ports);
	अगर (!host)
		जाओ failed;

	क्रम (p = 0; p < n_ports; p++) अणु
		ap = host->ports[p];

		ap->ops = ops;
		ap->pio_mask = ATA_PIO0;	/* ISA so PIO 0 cycles */
		ap->flags |= ATA_FLAG_SLAVE_POSS;
		ap->ioaddr.cmd_addr = io_addr + 0x10 * p;
		ap->ioaddr.altstatus_addr = ctl_addr + 0x10 * p;
		ap->ioaddr.ctl_addr = ctl_addr + 0x10 * p;
		ata_sff_std_ports(&ap->ioaddr);

		ata_port_desc(ap, "cmd 0x%lx ctl 0x%lx", io_base, ctl_base);
	पूर्ण

	/* activate */
	ret = ata_host_activate(host, pdev->irq, ata_sff_पूर्णांकerrupt,
				IRQF_SHARED, &pcmcia_sht);
	अगर (ret)
		जाओ failed;

	pdev->priv = host;
	वापस 0;

failed:
	pcmcia_disable_device(pdev);
	वापस ret;
पूर्ण

/**
 *	pcmcia_हटाओ_one	-	unplug an pcmcia पूर्णांकerface
 *	@pdev: pcmcia device
 *
 *	A PCMCIA ATA device has been unplugged. Perक्रमm the needed
 *	cleanup. Also called on module unload क्रम any active devices.
 */

अटल व्योम pcmcia_हटाओ_one(काष्ठा pcmcia_device *pdev)
अणु
	काष्ठा ata_host *host = pdev->priv;

	अगर (host)
		ata_host_detach(host);

	pcmcia_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id pcmcia_devices[] = अणु
	PCMCIA_DEVICE_FUNC_ID(4),
	PCMCIA_DEVICE_MANF_CARD(0x0000, 0x0000),	/* Corsair */
	PCMCIA_DEVICE_MANF_CARD(0x0007, 0x0000),	/* Hitachi */
	PCMCIA_DEVICE_MANF_CARD(0x000a, 0x0000),	/* I-O Data CFA */
	PCMCIA_DEVICE_MANF_CARD(0x001c, 0x0001),	/* Mitsubishi CFA */
	PCMCIA_DEVICE_MANF_CARD(0x0032, 0x0704),
	PCMCIA_DEVICE_MANF_CARD(0x0032, 0x2904),
	PCMCIA_DEVICE_MANF_CARD(0x0045, 0x0401),	/* SanDisk CFA */
	PCMCIA_DEVICE_MANF_CARD(0x004f, 0x0000),	/* Kingston */
	PCMCIA_DEVICE_MANF_CARD(0x0097, 0x1620), 	/* TI emulated */
	PCMCIA_DEVICE_MANF_CARD(0x0098, 0x0000),	/* Toshiba */
	PCMCIA_DEVICE_MANF_CARD(0x00a4, 0x002d),
	PCMCIA_DEVICE_MANF_CARD(0x00ce, 0x0000),	/* Samsung */
	PCMCIA_DEVICE_MANF_CARD(0x00f1, 0x0101),	/* SanDisk High (>8G) CFA */
	PCMCIA_DEVICE_MANF_CARD(0x0319, 0x0000),	/* Hitachi */
	PCMCIA_DEVICE_MANF_CARD(0x2080, 0x0001),
	PCMCIA_DEVICE_MANF_CARD(0x4e01, 0x0100),	/* Viking CFA */
	PCMCIA_DEVICE_MANF_CARD(0x4e01, 0x0200),	/* Lexar, Viking CFA */
	PCMCIA_DEVICE_PROD_ID123("Caravelle", "PSC-IDE ", "PSC000", 0x8c36137c, 0xd0693ab8, 0x2768a9f0),
	PCMCIA_DEVICE_PROD_ID123("CDROM", "IDE", "MCD-601p", 0x1b9179ca, 0xede88951, 0x0d902f74),
	PCMCIA_DEVICE_PROD_ID123("PCMCIA", "IDE CARD", "F1", 0x281f1c5d, 0x1907960c, 0xf7fde8b9),
	PCMCIA_DEVICE_PROD_ID12("ARGOSY", "CD-ROM", 0x78f308dc, 0x66536591),
	PCMCIA_DEVICE_PROD_ID12("ARGOSY", "PnPIDE", 0x78f308dc, 0x0c694728),
	PCMCIA_DEVICE_PROD_ID12("CNF   ", "CD-ROM", 0x46d7db81, 0x66536591),
	PCMCIA_DEVICE_PROD_ID12("CNF CD-M", "CD-ROM", 0x7d93b852, 0x66536591),
	PCMCIA_DEVICE_PROD_ID12("Creative Technology Ltd.", "PCMCIA CD-ROM Interface Card", 0xff8c8a45, 0xfe8020c4),
	PCMCIA_DEVICE_PROD_ID12("Digital Equipment Corporation.", "Digital Mobile Media CD-ROM", 0x17692a66, 0xef1dcbde),
	PCMCIA_DEVICE_PROD_ID12("EXP", "CD+GAME", 0x6f58c983, 0x63c13aaf),
	PCMCIA_DEVICE_PROD_ID12("EXP   ", "CD-ROM", 0x0a5c52fd, 0x66536591),
	PCMCIA_DEVICE_PROD_ID12("EXP   ", "PnPIDE", 0x0a5c52fd, 0x0c694728),
	PCMCIA_DEVICE_PROD_ID12("FREECOM", "PCCARD-IDE", 0x5714cbf7, 0x48e0ab8e),
	PCMCIA_DEVICE_PROD_ID12("HITACHI", "FLASH", 0xf4f43949, 0x9eb86aae),
	PCMCIA_DEVICE_PROD_ID12("HITACHI", "microdrive", 0xf4f43949, 0xa6d76178),
	PCMCIA_DEVICE_PROD_ID12("Hyperstone", "Model1", 0x3d5b9ef5, 0xca6ab420),
	PCMCIA_DEVICE_PROD_ID12("IBM", "microdrive", 0xb569a6e5, 0xa6d76178),
	PCMCIA_DEVICE_PROD_ID12("IBM", "IBM17JSSFP20", 0xb569a6e5, 0xf2508753),
	PCMCIA_DEVICE_PROD_ID12("KINGSTON", "CF CARD 1GB", 0x2e6d1829, 0x55d5bffb),
	PCMCIA_DEVICE_PROD_ID12("KINGSTON", "CF CARD 4GB", 0x2e6d1829, 0x531e7d10),
	PCMCIA_DEVICE_PROD_ID12("KINGSTON", "CF8GB", 0x2e6d1829, 0xacbe682e),
	PCMCIA_DEVICE_PROD_ID12("IO DATA", "CBIDE2      ", 0x547e66dc, 0x8671043b),
	PCMCIA_DEVICE_PROD_ID12("IO DATA", "PCIDE", 0x547e66dc, 0x5c5ab149),
	PCMCIA_DEVICE_PROD_ID12("IO DATA", "PCIDEII", 0x547e66dc, 0xb3662674),
	PCMCIA_DEVICE_PROD_ID12("LOOKMEET", "CBIDE2      ", 0xe37be2b5, 0x8671043b),
	PCMCIA_DEVICE_PROD_ID12("M-Systems", "CF300", 0x7ed2ad87, 0x7e9e78ee),
	PCMCIA_DEVICE_PROD_ID12("M-Systems", "CF500", 0x7ed2ad87, 0x7a13045c),
	PCMCIA_DEVICE_PROD_ID2("NinjaATA-", 0xebe0bd79),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "CD-ROM", 0x281f1c5d, 0x66536591),
	PCMCIA_DEVICE_PROD_ID12("PCMCIA", "PnPIDE", 0x281f1c5d, 0x0c694728),
	PCMCIA_DEVICE_PROD_ID12("SHUTTLE TECHNOLOGY LTD.", "PCCARD-IDE/ATAPI Adapter", 0x4a3f0ba0, 0x322560e1),
	PCMCIA_DEVICE_PROD_ID12("SEAGATE", "ST1", 0x87c1b330, 0xe1f30883),
	PCMCIA_DEVICE_PROD_ID12("SAMSUNG", "04/05/06", 0x43d74cb4, 0x6a22777d),
	PCMCIA_DEVICE_PROD_ID12("SMI VENDOR", "SMI PRODUCT", 0x30896c92, 0x703cc5f6),
	PCMCIA_DEVICE_PROD_ID12("TOSHIBA", "MK2001MPL", 0xb4585a1a, 0x3489e003),
	PCMCIA_DEVICE_PROD_ID1("TRANSCEND    512M   ", 0xd0909443),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS1GCF45", 0x709b1bf1, 0xf68b6f32),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS1GCF80", 0x709b1bf1, 0x2a54d4b1),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS2GCF120", 0x709b1bf1, 0x969aa4f2),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS4GCF120", 0x709b1bf1, 0xf54a91c8),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS4GCF133", 0x709b1bf1, 0x7558f133),
	PCMCIA_DEVICE_PROD_ID12("TRANSCEND", "TS8GCF133", 0x709b1bf1, 0xb2f89b47),
	PCMCIA_DEVICE_PROD_ID12("WIT", "IDE16", 0x244e5994, 0x3e232852),
	PCMCIA_DEVICE_PROD_ID12("WEIDA", "TWTTI", 0xcc7cf69c, 0x212bb918),
	PCMCIA_DEVICE_PROD_ID1("STI Flash", 0xe4a13209),
	PCMCIA_DEVICE_PROD_ID12("STI", "Flash 5.0", 0xbf2df18d, 0x8cb57a0e),
	PCMCIA_MFC_DEVICE_PROD_ID12(1, "SanDisk", "ConnectPlus", 0x7a954bd9, 0x74be00c6),
	PCMCIA_DEVICE_PROD_ID2("Flash Card", 0x5a362506),
	PCMCIA_DEVICE_शून्य,
पूर्ण;

MODULE_DEVICE_TABLE(pcmcia, pcmcia_devices);

अटल काष्ठा pcmcia_driver pcmcia_driver = अणु
	.owner		= THIS_MODULE,
	.name		= DRV_NAME,
	.id_table	= pcmcia_devices,
	.probe		= pcmcia_init_one,
	.हटाओ		= pcmcia_हटाओ_one,
पूर्ण;
module_pcmcia_driver(pcmcia_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for PCMCIA ATA");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
