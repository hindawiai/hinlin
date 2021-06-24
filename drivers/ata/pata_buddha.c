<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Buddha, Catweasel and X-Surf PATA controller driver
 *
 * Copyright (c) 2018 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Based on buddha.c:
 *
 *	Copyright (C) 1997, 2001 by Geert Uytterhoeven and others
 */

#समावेश <linux/ata.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/libata.h>
#समावेश <linux/mm.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/zorro.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>

#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/ide.h>
#समावेश <यंत्र/setup.h>

#घोषणा DRV_NAME "pata_buddha"
#घोषणा DRV_VERSION "0.1.1"

#घोषणा BUDDHA_BASE1	0x800
#घोषणा BUDDHA_BASE2	0xa00
#घोषणा BUDDHA_BASE3	0xc00
#घोषणा XSURF_BASE1	0xb000 /* 2.5" पूर्णांकerface */
#घोषणा XSURF_BASE2	0xd000 /* 3.5" पूर्णांकerface */
#घोषणा BUDDHA_CONTROL	0x11a
#घोषणा BUDDHA_IRQ	0xf00
#घोषणा XSURF_IRQ	0x7e
#घोषणा BUDDHA_IRQ_MR	0xfc0	/* master पूर्णांकerrupt enable */

क्रमागत अणु
	BOARD_BUDDHA = 0,
	BOARD_CATWEASEL,
	BOARD_XSURF
पूर्ण;

अटल अचिन्हित पूर्णांक buddha_bases[3] = अणु
	BUDDHA_BASE1, BUDDHA_BASE2, BUDDHA_BASE3
पूर्ण;

अटल अचिन्हित पूर्णांक xsurf_bases[2] = अणु
	XSURF_BASE1, XSURF_BASE2
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा pata_buddha_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

/* FIXME: is this needed? */
अटल अचिन्हित पूर्णांक pata_buddha_data_xfer(काष्ठा ata_queued_cmd *qc,
					 अचिन्हित अक्षर *buf,
					 अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	काष्ठा ata_device *dev = qc->dev;
	काष्ठा ata_port *ap = dev->link->ap;
	व्योम __iomem *data_addr = ap->ioaddr.data_addr;
	अचिन्हित पूर्णांक words = buflen >> 1;

	/* Transfer multiple of 2 bytes */
	अगर (rw == READ)
		raw_insw((u16 *)data_addr, (u16 *)buf, words);
	अन्यथा
		raw_outsw((u16 *)data_addr, (u16 *)buf, words);

	/* Transfer trailing byte, अगर any. */
	अगर (unlikely(buflen & 0x01)) अणु
		अचिन्हित अक्षर pad[2] = अणु पूर्ण;

		/* Poपूर्णांक buf to the tail of buffer */
		buf += buflen - 1;

		अगर (rw == READ) अणु
			raw_insw((u16 *)data_addr, (u16 *)pad, 1);
			*buf = pad[0];
		पूर्ण अन्यथा अणु
			pad[0] = *buf;
			raw_outsw((u16 *)data_addr, (u16 *)pad, 1);
		पूर्ण
		words++;
	पूर्ण

	वापस words << 1;
पूर्ण

/*
 * Provide our own set_mode() as we करोn't want to change anything that has
 * alपढ़ोy been configured..
 */
अटल पूर्णांक pata_buddha_set_mode(काष्ठा ata_link *link,
				काष्ठा ata_device **unused)
अणु
	काष्ठा ata_device *dev;

	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		/* We करोn't really care */
		dev->pio_mode = dev->xfer_mode = XFER_PIO_0;
		dev->xfer_shअगरt = ATA_SHIFT_PIO;
		dev->flags |= ATA_DFLAG_PIO;
		ata_dev_info(dev, "configured for PIO\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल bool pata_buddha_irq_check(काष्ठा ata_port *ap)
अणु
	u8 ch;

	ch = z_पढ़ोb((अचिन्हित दीर्घ)ap->निजी_data);

	वापस !!(ch & 0x80);
पूर्ण

अटल व्योम pata_xsurf_irq_clear(काष्ठा ata_port *ap)
अणु
	z_ग_लिखोb(0, (अचिन्हित दीर्घ)ap->निजी_data);
पूर्ण

अटल काष्ठा ata_port_operations pata_buddha_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.sff_data_xfer	= pata_buddha_data_xfer,
	.sff_irq_check	= pata_buddha_irq_check,
	.cable_detect	= ata_cable_unknown,
	.set_mode	= pata_buddha_set_mode,
पूर्ण;

अटल काष्ठा ata_port_operations pata_xsurf_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.sff_data_xfer	= pata_buddha_data_xfer,
	.sff_irq_check	= pata_buddha_irq_check,
	.sff_irq_clear	= pata_xsurf_irq_clear,
	.cable_detect	= ata_cable_unknown,
	.set_mode	= pata_buddha_set_mode,
पूर्ण;

अटल पूर्णांक pata_buddha_probe(काष्ठा zorro_dev *z,
			     स्थिर काष्ठा zorro_device_id *ent)
अणु
	अटल स्थिर अक्षर * स्थिर board_name[] = अणु
		"Buddha", "Catweasel", "X-Surf"
	पूर्ण;
	काष्ठा ata_host *host;
	व्योम __iomem *buddha_board;
	अचिन्हित दीर्घ board;
	अचिन्हित पूर्णांक type = ent->driver_data;
	अचिन्हित पूर्णांक nr_ports = (type == BOARD_CATWEASEL) ? 3 : 2;
	व्योम *old_drvdata;
	पूर्णांक i;

	dev_info(&z->dev, "%s IDE controller\n", board_name[type]);

	board = z->resource.start;

	अगर (type != BOARD_XSURF) अणु
		अगर (!devm_request_mem_region(&z->dev,
					     board + BUDDHA_BASE1,
					     0x800, DRV_NAME))
			वापस -ENXIO;
	पूर्ण अन्यथा अणु
		अगर (!devm_request_mem_region(&z->dev,
					     board + XSURF_BASE1,
					     0x1000, DRV_NAME))
			वापस -ENXIO;
		अगर (!devm_request_mem_region(&z->dev,
					     board + XSURF_BASE2,
					     0x1000, DRV_NAME)) अणु
		पूर्ण
	पूर्ण

	/* Workaround क्रम X-Surf: Save drvdata in हाल zorro8390 has set it */
	अगर (type == BOARD_XSURF)
		old_drvdata = dev_get_drvdata(&z->dev);

	/* allocate host */
	host = ata_host_alloc(&z->dev, nr_ports);
	अगर (type == BOARD_XSURF)
		dev_set_drvdata(&z->dev, old_drvdata);
	अगर (!host)
		वापस -ENXIO;

	buddha_board = ZTWO_VADDR(board);

	/* enable the board IRQ on Buddha/Catweasel */
	अगर (type != BOARD_XSURF)
		z_ग_लिखोb(0, buddha_board + BUDDHA_IRQ_MR);

	क्रम (i = 0; i < nr_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		व्योम __iomem *base, *irqport;
		अचिन्हित दीर्घ ctl = 0;

		अगर (type != BOARD_XSURF) अणु
			ap->ops = &pata_buddha_ops;
			base = buddha_board + buddha_bases[i];
			ctl = BUDDHA_CONTROL;
			irqport = buddha_board + BUDDHA_IRQ + i * 0x40;
		पूर्ण अन्यथा अणु
			ap->ops = &pata_xsurf_ops;
			base = buddha_board + xsurf_bases[i];
			/* X-Surf has no CS1* (Control/AltStat) */
			irqport = buddha_board + XSURF_IRQ;
		पूर्ण

		ap->pio_mask = ATA_PIO4;
		ap->flags |= ATA_FLAG_SLAVE_POSS | ATA_FLAG_NO_IORDY;

		ap->ioaddr.data_addr		= base;
		ap->ioaddr.error_addr		= base + 2 + 1 * 4;
		ap->ioaddr.feature_addr		= base + 2 + 1 * 4;
		ap->ioaddr.nsect_addr		= base + 2 + 2 * 4;
		ap->ioaddr.lbal_addr		= base + 2 + 3 * 4;
		ap->ioaddr.lbam_addr		= base + 2 + 4 * 4;
		ap->ioaddr.lbah_addr		= base + 2 + 5 * 4;
		ap->ioaddr.device_addr		= base + 2 + 6 * 4;
		ap->ioaddr.status_addr		= base + 2 + 7 * 4;
		ap->ioaddr.command_addr		= base + 2 + 7 * 4;

		अगर (ctl) अणु
			ap->ioaddr.altstatus_addr = base + ctl;
			ap->ioaddr.ctl_addr	  = base + ctl;
		पूर्ण

		ap->निजी_data = (व्योम *)irqport;

		ata_port_desc(ap, "cmd 0x%lx ctl 0x%lx", board,
			      ctl ? board + buddha_bases[i] + ctl : 0);
	पूर्ण

	ata_host_activate(host, IRQ_AMIGA_PORTS, ata_sff_पूर्णांकerrupt,
			  IRQF_SHARED, &pata_buddha_sht);

	वापस 0;
पूर्ण

अटल व्योम pata_buddha_हटाओ(काष्ठा zorro_dev *z)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(&z->dev);

	ata_host_detach(host);
पूर्ण

अटल स्थिर काष्ठा zorro_device_id pata_buddha_zorro_tbl[] = अणु
	अणु ZORRO_PROD_INDIVIDUAL_COMPUTERS_BUDDHA, BOARD_BUDDHAपूर्ण,
	अणु ZORRO_PROD_INDIVIDUAL_COMPUTERS_CATWEASEL, BOARD_CATWEASELपूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(zorro, pata_buddha_zorro_tbl);

अटल काष्ठा zorro_driver pata_buddha_driver = अणु
	.name           = "pata_buddha",
	.id_table       = pata_buddha_zorro_tbl,
	.probe          = pata_buddha_probe,
	.हटाओ         = pata_buddha_हटाओ,
पूर्ण;

/*
 * We cannot have a modalias क्रम X-Surf boards, as it competes with the
 * zorro8390 network driver. As a stopgap measure until we have proper
 * MFD support क्रम this board, we manually attach to it late after Zorro
 * has क्रमागतerated its boards.
 */
अटल पूर्णांक __init pata_buddha_late_init(व्योम)
अणु
	काष्ठा zorro_dev *z = शून्य;

	/* Auto-bind to regular boards */
	zorro_रेजिस्टर_driver(&pata_buddha_driver);

	/* Manually bind to all X-Surf boards */
	जबतक ((z = zorro_find_device(ZORRO_PROD_INDIVIDUAL_COMPUTERS_X_SURF, z))) अणु
		अटल काष्ठा zorro_device_id xsurf_ent = अणु
			ZORRO_PROD_INDIVIDUAL_COMPUTERS_X_SURF, BOARD_XSURF
		पूर्ण;

		pata_buddha_probe(z, &xsurf_ent);
	पूर्ण

	वापस 0;
पूर्ण
late_initcall(pata_buddha_late_init);

MODULE_AUTHOR("Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("low-level driver for Buddha/Catweasel/X-Surf PATA");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
