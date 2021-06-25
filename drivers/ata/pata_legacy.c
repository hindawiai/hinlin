<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   pata-legacy.c - Legacy port PATA/SATA controller driver.
 *   Copyright 2005/2006 Red Hat, all rights reserved.
 *
 *   An ATA driver क्रम the legacy ATA ports.
 *
 *   Data Sources:
 *	Opti 82C465/82C611 support: Data sheets at opti-inc.com
 *	HT6560 series:
 *	Promise 20230/20620:
 *		http://www.ryston.cz/petr/vlb/pdc20230b.hपंचांगl
 *		http://www.ryston.cz/petr/vlb/pdc20230c.hपंचांगl
 *		http://www.ryston.cz/petr/vlb/pdc20630.hपंचांगl
 *	QDI65x0:
 *		http://www.ryston.cz/petr/vlb/qd6500.hपंचांगl
 *		http://www.ryston.cz/petr/vlb/qd6580.hपंचांगl
 *
 *	QDI65x0 probe code based on drivers/ide/legacy/qd65xx.c
 *	Rewritten from the work of Colten Edwards <pje120@cs.usask.ca> by
 *	Samuel Thibault <samuel.thibault@ens-lyon.org>
 *
 *  Unsupported but करोcs exist:
 *	Appian/Adaptec AIC25VL01/Cirrus Logic PD7220
 *
 *  This driver handles legacy (that is "ISA/VLB side") IDE ports found
 *  on PC class प्रणालीs. There are three hybrid devices that are exceptions
 *  The Cyrix 5510/5520 where a pre SFF ATA device is on the bridge and
 *  the MPIIX where the tuning is PCI side but the IDE is "ISA side".
 *
 *  Specअगरic support is included क्रम the ht6560a/ht6560b/opti82c611a/
 *  opti82c465mv/promise 20230c/20630/qdi65x0/winbond83759A
 *
 *  Support क्रम the Winbond 83759A when operating in advanced mode.
 *  Multichip mode is not currently supported.
 *
 *  Use the स्वतःspeed and pio_mask options with:
 *	Appian ADI/2 aka CLPD7220 or AIC25VL01.
 *  Use the jumpers, स्वतःspeed and set pio_mask to the mode on the jumpers with
 *	Goldstar GM82C711, PIC-1288A-125, UMC 82C871F, Winbond W83759,
 *	Winbond W83759A, Promise PDC20230-B
 *
 *  For now use स्वतःspeed and pio_mask as above with the W83759A. This may
 *  change.
 */

#समावेश <linux/async.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/ata.h>
#समावेश <linux/libata.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRV_NAME "pata_legacy"
#घोषणा DRV_VERSION "0.6.5"

#घोषणा NR_HOST 6

अटल पूर्णांक all;
module_param(all, पूर्णांक, 0444);
MODULE_PARM_DESC(all,
		 "Set to probe unclaimed pri/sec ISA port ranges even if PCI");

अटल पूर्णांक probe_all;
module_param(probe_all, पूर्णांक, 0);
MODULE_PARM_DESC(probe_all,
		 "Set to probe tertiary+ ISA port ranges even if PCI");

अटल पूर्णांक probe_mask = ~0;
module_param(probe_mask, पूर्णांक, 0);
MODULE_PARM_DESC(probe_mask, "Probe mask for legacy ISA PATA ports");

अटल पूर्णांक स्वतःspeed;
module_param(स्वतःspeed, पूर्णांक, 0);
MODULE_PARM_DESC(स्वतःspeed, "Chip present that snoops speed changes");

अटल पूर्णांक pio_mask = ATA_PIO4;
module_param(pio_mask, पूर्णांक, 0);
MODULE_PARM_DESC(pio_mask, "PIO range for autospeed devices");

अटल पूर्णांक iordy_mask = 0xFFFFFFFF;
module_param(iordy_mask, पूर्णांक, 0);
MODULE_PARM_DESC(iordy_mask, "Use IORDY if available");

अटल पूर्णांक ht6560a;
module_param(ht6560a, पूर्णांक, 0);
MODULE_PARM_DESC(ht6560a, "HT 6560A on primary 1, second 2, both 3");

अटल पूर्णांक ht6560b;
module_param(ht6560b, पूर्णांक, 0);
MODULE_PARM_DESC(ht6560b, "HT 6560B on primary 1, secondary 2, both 3");

अटल पूर्णांक opti82c611a;
module_param(opti82c611a, पूर्णांक, 0);
MODULE_PARM_DESC(opti82c611a,
		 "Opti 82c611A on primary 1, secondary 2, both 3");

अटल पूर्णांक opti82c46x;
module_param(opti82c46x, पूर्णांक, 0);
MODULE_PARM_DESC(opti82c46x,
		 "Opti 82c465MV on primary 1, secondary 2, both 3");

#अगर_घोषित CONFIG_PATA_QDI_MODULE
अटल पूर्णांक qdi = 1;
#अन्यथा
अटल पूर्णांक qdi;
#पूर्ण_अगर
module_param(qdi, पूर्णांक, 0);
MODULE_PARM_DESC(qdi, "Set to probe QDI controllers");

#अगर_घोषित CONFIG_PATA_WINBOND_VLB_MODULE
अटल पूर्णांक winbond = 1;
#अन्यथा
अटल पूर्णांक winbond;
#पूर्ण_अगर
module_param(winbond, पूर्णांक, 0);
MODULE_PARM_DESC(winbond,
		 "Set to probe Winbond controllers, "
		 "give I/O port if non standard");


क्रमागत controller अणु
	BIOS = 0,
	SNOOP = 1,
	PDC20230 = 2,
	HT6560A = 3,
	HT6560B = 4,
	OPTI611A = 5,
	OPTI46X = 6,
	QDI6500 = 7,
	QDI6580 = 8,
	QDI6580DP = 9,		/* Dual channel mode is dअगरferent */
	W83759A = 10,

	UNKNOWN = -1
पूर्ण;

काष्ठा legacy_data अणु
	अचिन्हित दीर्घ timing;
	u8 घड़ी[2];
	u8 last;
	पूर्णांक fast;
	क्रमागत controller type;
	काष्ठा platक्रमm_device *platक्रमm_dev;
पूर्ण;

काष्ठा legacy_probe अणु
	अचिन्हित अक्षर *name;
	अचिन्हित दीर्घ port;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक slot;
	क्रमागत controller type;
	अचिन्हित दीर्घ निजी;
पूर्ण;

काष्ठा legacy_controller अणु
	स्थिर अक्षर *name;
	काष्ठा ata_port_operations *ops;
	अचिन्हित पूर्णांक pio_mask;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक pflags;
	पूर्णांक (*setup)(काष्ठा platक्रमm_device *, काष्ठा legacy_probe *probe,
		काष्ठा legacy_data *data);
पूर्ण;

अटल पूर्णांक legacy_port[NR_HOST] = अणु 0x1f0, 0x170, 0x1e8, 0x168, 0x1e0, 0x160 पूर्ण;

अटल काष्ठा legacy_probe probe_list[NR_HOST];
अटल काष्ठा legacy_data legacy_data[NR_HOST];
अटल काष्ठा ata_host *legacy_host[NR_HOST];
अटल पूर्णांक nr_legacy_host;


/**
 *	legacy_probe_add	-	Add पूर्णांकerface to probe list
 *	@port: Controller port
 *	@irq: IRQ number
 *	@type: Controller type
 *	@निजी: Controller specअगरic info
 *
 *	Add an entry पूर्णांकo the probe list क्रम ATA controllers. This is used
 *	to add the शेष ISA slots and then to build up the table
 *	further according to other ISA/VLB/Weird device scans
 *
 *	An I/O port list is used to keep ordering stable and sane, as we
 *	करोn't have any good way to talk about ordering otherwise
 */

अटल पूर्णांक legacy_probe_add(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक irq,
				क्रमागत controller type, अचिन्हित दीर्घ निजी)
अणु
	काष्ठा legacy_probe *lp = &probe_list[0];
	पूर्णांक i;
	काष्ठा legacy_probe *मुक्त = शून्य;

	क्रम (i = 0; i < NR_HOST; i++) अणु
		अगर (lp->port == 0 && मुक्त == शून्य)
			मुक्त = lp;
		/* Matching port, or the correct slot क्रम ordering */
		अगर (lp->port == port || legacy_port[i] == port) अणु
			अगर (!(probe_mask & 1 << i))
				वापस -1;
			मुक्त = lp;
			अवरोध;
		पूर्ण
		lp++;
	पूर्ण
	अगर (मुक्त == शून्य) अणु
		prपूर्णांकk(KERN_ERR "pata_legacy: Too many interfaces.\n");
		वापस -1;
	पूर्ण
	/* Fill in the entry क्रम later probing */
	मुक्त->port = port;
	मुक्त->irq = irq;
	मुक्त->type = type;
	मुक्त->निजी = निजी;
	वापस 0;
पूर्ण


/**
 *	legacy_set_mode		-	mode setting
 *	@link: IDE link
 *	@unused: Device that failed when error is वापसed
 *
 *	Use a non standard set_mode function. We करोn't want to be tuned.
 *
 *	The BIOS configured everything. Our job is not to fiddle. Just use
 *	whatever PIO the hardware is using and leave it at that. When we
 *	get some kind of nice user driven API क्रम control then we can
 *	expand on this as per hdparm in the base kernel.
 */

अटल पूर्णांक legacy_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **unused)
अणु
	काष्ठा ata_device *dev;

	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		ata_dev_info(dev, "configured for PIO\n");
		dev->pio_mode = XFER_PIO_0;
		dev->xfer_mode = XFER_PIO_0;
		dev->xfer_shअगरt = ATA_SHIFT_PIO;
		dev->flags |= ATA_DFLAG_PIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा legacy_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल स्थिर काष्ठा ata_port_operations legacy_base_port_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.cable_detect	= ata_cable_40wire,
पूर्ण;

/*
 *	These ops are used अगर the user indicates the hardware
 *	snoops the commands to decide on the mode and handles the
 *	mode selection "magically" itself. Several legacy controllers
 *	करो this. The mode range can be set अगर it is not 0x1F by setting
 *	pio_mask as well.
 */

अटल काष्ठा ata_port_operations simple_port_ops = अणु
	.inherits	= &legacy_base_port_ops,
	.sff_data_xfer	= ata_sff_data_xfer32,
पूर्ण;

अटल काष्ठा ata_port_operations legacy_port_ops = अणु
	.inherits	= &legacy_base_port_ops,
	.sff_data_xfer	= ata_sff_data_xfer32,
	.set_mode	= legacy_set_mode,
पूर्ण;

/*
 *	Promise 20230C and 20620 support
 *
 *	This controller supports PIO0 to PIO2. We set PIO timings
 *	conservatively to allow क्रम 50MHz Vesa Local Bus. The 20620 DMA
 *	support is weird being DMA to controller and PIO'd to the host
 *	and not supported.
 */

अटल व्योम pdc20230_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	पूर्णांक tries = 5;
	पूर्णांक pio = adev->pio_mode - XFER_PIO_0;
	u8 rt;
	अचिन्हित दीर्घ flags;

	/* Safe as UP only. Force I/Os to occur together */

	local_irq_save(flags);

	/* Unlock the control पूर्णांकerface */
	करो अणु
		inb(0x1F5);
		outb(inb(0x1F2) | 0x80, 0x1F2);
		inb(0x1F2);
		inb(0x3F6);
		inb(0x3F6);
		inb(0x1F2);
		inb(0x1F2);
	पूर्ण
	जबतक ((inb(0x1F2) & 0x80) && --tries);

	local_irq_restore(flags);

	outb(inb(0x1F4) & 0x07, 0x1F4);

	rt = inb(0x1F3);
	rt &= 0x07 << (3 * adev->devno);
	अगर (pio)
		rt |= (1 + 3 * pio) << (3 * adev->devno);

	udelay(100);
	outb(inb(0x1F2) | 0x01, 0x1F2);
	udelay(100);
	inb(0x1F5);

पूर्ण

अटल अचिन्हित पूर्णांक pdc_data_xfer_vlb(काष्ठा ata_queued_cmd *qc,
			अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	काष्ठा ata_device *dev = qc->dev;
	काष्ठा ata_port *ap = dev->link->ap;
	पूर्णांक slop = buflen & 3;

	/* 32bit I/O capable *and* we need to ग_लिखो a whole number of dwords */
	अगर (ata_id_has_dword_io(dev->id) && (slop == 0 || slop == 3)
					&& (ap->pflags & ATA_PFLAG_PIO32)) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);

		/* Perक्रमm the 32bit I/O synchronization sequence */
		ioपढ़ो8(ap->ioaddr.nsect_addr);
		ioपढ़ो8(ap->ioaddr.nsect_addr);
		ioपढ़ो8(ap->ioaddr.nsect_addr);

		/* Now the data */
		अगर (rw == READ)
			ioपढ़ो32_rep(ap->ioaddr.data_addr, buf, buflen >> 2);
		अन्यथा
			ioग_लिखो32_rep(ap->ioaddr.data_addr, buf, buflen >> 2);

		अगर (unlikely(slop)) अणु
			__le32 pad;
			अगर (rw == READ) अणु
				pad = cpu_to_le32(ioपढ़ो32(ap->ioaddr.data_addr));
				स_नकल(buf + buflen - slop, &pad, slop);
			पूर्ण अन्यथा अणु
				स_नकल(&pad, buf + buflen - slop, slop);
				ioग_लिखो32(le32_to_cpu(pad), ap->ioaddr.data_addr);
			पूर्ण
			buflen += 4 - slop;
		पूर्ण
		local_irq_restore(flags);
	पूर्ण अन्यथा
		buflen = ata_sff_data_xfer32(qc, buf, buflen, rw);

	वापस buflen;
पूर्ण

अटल काष्ठा ata_port_operations pdc20230_port_ops = अणु
	.inherits	= &legacy_base_port_ops,
	.set_piomode	= pdc20230_set_piomode,
	.sff_data_xfer	= pdc_data_xfer_vlb,
पूर्ण;

/*
 *	Holtek 6560A support
 *
 *	This controller supports PIO0 to PIO2 (no IORDY even though higher
 *	timings can be loaded).
 */

अटल व्योम ht6560a_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	u8 active, recover;
	काष्ठा ata_timing t;

	/* Get the timing data in cycles. For now play safe at 50Mhz */
	ata_timing_compute(adev, adev->pio_mode, &t, 20000, 1000);

	active = clamp_val(t.active, 2, 15);
	recover = clamp_val(t.recover, 4, 15);

	inb(0x3E6);
	inb(0x3E6);
	inb(0x3E6);
	inb(0x3E6);

	ioग_लिखो8(recover << 4 | active, ap->ioaddr.device_addr);
	ioपढ़ो8(ap->ioaddr.status_addr);
पूर्ण

अटल काष्ठा ata_port_operations ht6560a_port_ops = अणु
	.inherits	= &legacy_base_port_ops,
	.set_piomode	= ht6560a_set_piomode,
पूर्ण;

/*
 *	Holtek 6560B support
 *
 *	This controller supports PIO0 to PIO4. We honour the BIOS/jumper FIFO
 *	setting unless we see an ATAPI device in which हाल we क्रमce it off.
 *
 *	FIXME: need to implement 2nd channel support.
 */

अटल व्योम ht6560b_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	u8 active, recover;
	काष्ठा ata_timing t;

	/* Get the timing data in cycles. For now play safe at 50Mhz */
	ata_timing_compute(adev, adev->pio_mode, &t, 20000, 1000);

	active = clamp_val(t.active, 2, 15);
	recover = clamp_val(t.recover, 2, 16) & 0x0F;

	inb(0x3E6);
	inb(0x3E6);
	inb(0x3E6);
	inb(0x3E6);

	ioग_लिखो8(recover << 4 | active, ap->ioaddr.device_addr);

	अगर (adev->class != ATA_DEV_ATA) अणु
		u8 rconf = inb(0x3E6);
		अगर (rconf & 0x24) अणु
			rconf &= ~0x24;
			outb(rconf, 0x3E6);
		पूर्ण
	पूर्ण
	ioपढ़ो8(ap->ioaddr.status_addr);
पूर्ण

अटल काष्ठा ata_port_operations ht6560b_port_ops = अणु
	.inherits	= &legacy_base_port_ops,
	.set_piomode	= ht6560b_set_piomode,
पूर्ण;

/*
 *	Opti core chipset helpers
 */

/**
 *	opti_syscfg	-	पढ़ो OPTI chipset configuration
 *	@reg: Configuration रेजिस्टर to पढ़ो
 *
 *	Returns the value of an OPTI प्रणाली board configuration रेजिस्टर.
 */

अटल u8 opti_syscfg(u8 reg)
अणु
	अचिन्हित दीर्घ flags;
	u8 r;

	/* Uniprocessor chipset and must क्रमce cycles adjancent */
	local_irq_save(flags);
	outb(reg, 0x22);
	r = inb(0x24);
	local_irq_restore(flags);
	वापस r;
पूर्ण

/*
 *	Opti 82C611A
 *
 *	This controller supports PIO0 to PIO3.
 */

अटल व्योम opti82c611a_set_piomode(काष्ठा ata_port *ap,
						काष्ठा ata_device *adev)
अणु
	u8 active, recover, setup;
	काष्ठा ata_timing t;
	काष्ठा ata_device *pair = ata_dev_pair(adev);
	पूर्णांक घड़ी;
	पूर्णांक khz[4] = अणु 50000, 40000, 33000, 25000 पूर्ण;
	u8 rc;

	/* Enter configuration mode */
	ioपढ़ो16(ap->ioaddr.error_addr);
	ioपढ़ो16(ap->ioaddr.error_addr);
	ioग_लिखो8(3, ap->ioaddr.nsect_addr);

	/* Read VLB घड़ी strapping */
	घड़ी = 1000000000 / khz[ioपढ़ो8(ap->ioaddr.lbah_addr) & 0x03];

	/* Get the timing data in cycles */
	ata_timing_compute(adev, adev->pio_mode, &t, घड़ी, 1000);

	/* Setup timing is shared */
	अगर (pair) अणु
		काष्ठा ata_timing tp;
		ata_timing_compute(pair, pair->pio_mode, &tp, घड़ी, 1000);

		ata_timing_merge(&t, &tp, &t, ATA_TIMING_SETUP);
	पूर्ण

	active = clamp_val(t.active, 2, 17) - 2;
	recover = clamp_val(t.recover, 1, 16) - 1;
	setup = clamp_val(t.setup, 1, 4) - 1;

	/* Select the right timing bank क्रम ग_लिखो timing */
	rc = ioपढ़ो8(ap->ioaddr.lbal_addr);
	rc &= 0x7F;
	rc |= (adev->devno << 7);
	ioग_लिखो8(rc, ap->ioaddr.lbal_addr);

	/* Write the timings */
	ioग_लिखो8(active << 4 | recover, ap->ioaddr.error_addr);

	/* Select the right bank क्रम पढ़ो timings, also
	   load the shared timings क्रम address */
	rc = ioपढ़ो8(ap->ioaddr.device_addr);
	rc &= 0xC0;
	rc |= adev->devno;	/* Index select */
	rc |= (setup << 4) | 0x04;
	ioग_लिखो8(rc, ap->ioaddr.device_addr);

	/* Load the पढ़ो timings */
	ioग_लिखो8(active << 4 | recover, ap->ioaddr.data_addr);

	/* Ensure the timing रेजिस्टर mode is right */
	rc = ioपढ़ो8(ap->ioaddr.lbal_addr);
	rc &= 0x73;
	rc |= 0x84;
	ioग_लिखो8(rc, ap->ioaddr.lbal_addr);

	/* Exit command mode */
	ioग_लिखो8(0x83,  ap->ioaddr.nsect_addr);
पूर्ण


अटल काष्ठा ata_port_operations opti82c611a_port_ops = अणु
	.inherits	= &legacy_base_port_ops,
	.set_piomode	= opti82c611a_set_piomode,
पूर्ण;

/*
 *	Opti 82C465MV
 *
 *	This controller supports PIO0 to PIO3. Unlike the 611A the MVB
 *	version is dual channel but करोesn't have a lot of unique रेजिस्टरs.
 */

अटल व्योम opti82c46x_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	u8 active, recover, setup;
	काष्ठा ata_timing t;
	काष्ठा ata_device *pair = ata_dev_pair(adev);
	पूर्णांक घड़ी;
	पूर्णांक khz[4] = अणु 50000, 40000, 33000, 25000 पूर्ण;
	u8 rc;
	u8 sysclk;

	/* Get the घड़ी */
	sysclk = (opti_syscfg(0xAC) & 0xC0) >> 6;	/* BIOS set */

	/* Enter configuration mode */
	ioपढ़ो16(ap->ioaddr.error_addr);
	ioपढ़ो16(ap->ioaddr.error_addr);
	ioग_लिखो8(3, ap->ioaddr.nsect_addr);

	/* Read VLB घड़ी strapping */
	घड़ी = 1000000000 / khz[sysclk];

	/* Get the timing data in cycles */
	ata_timing_compute(adev, adev->pio_mode, &t, घड़ी, 1000);

	/* Setup timing is shared */
	अगर (pair) अणु
		काष्ठा ata_timing tp;
		ata_timing_compute(pair, pair->pio_mode, &tp, घड़ी, 1000);

		ata_timing_merge(&t, &tp, &t, ATA_TIMING_SETUP);
	पूर्ण

	active = clamp_val(t.active, 2, 17) - 2;
	recover = clamp_val(t.recover, 1, 16) - 1;
	setup = clamp_val(t.setup, 1, 4) - 1;

	/* Select the right timing bank क्रम ग_लिखो timing */
	rc = ioपढ़ो8(ap->ioaddr.lbal_addr);
	rc &= 0x7F;
	rc |= (adev->devno << 7);
	ioग_लिखो8(rc, ap->ioaddr.lbal_addr);

	/* Write the timings */
	ioग_लिखो8(active << 4 | recover, ap->ioaddr.error_addr);

	/* Select the right bank क्रम पढ़ो timings, also
	   load the shared timings क्रम address */
	rc = ioपढ़ो8(ap->ioaddr.device_addr);
	rc &= 0xC0;
	rc |= adev->devno;	/* Index select */
	rc |= (setup << 4) | 0x04;
	ioग_लिखो8(rc, ap->ioaddr.device_addr);

	/* Load the पढ़ो timings */
	ioग_लिखो8(active << 4 | recover, ap->ioaddr.data_addr);

	/* Ensure the timing रेजिस्टर mode is right */
	rc = ioपढ़ो8(ap->ioaddr.lbal_addr);
	rc &= 0x73;
	rc |= 0x84;
	ioग_लिखो8(rc, ap->ioaddr.lbal_addr);

	/* Exit command mode */
	ioग_लिखो8(0x83,  ap->ioaddr.nsect_addr);

	/* We need to know this क्रम quad device on the MVB */
	ap->host->निजी_data = ap;
पूर्ण

/**
 *	opti82c46x_qc_issue		-	command issue
 *	@qc: command pending
 *
 *	Called when the libata layer is about to issue a command. We wrap
 *	this पूर्णांकerface so that we can load the correct ATA timings. The
 *	MVB has a single set of timing रेजिस्टरs and these are shared
 *	across channels. As there are two रेजिस्टरs we really ought to
 *	track the last two used values as a sort of रेजिस्टर winकरोw. For
 *	now we just reload on a channel चयन. On the single channel
 *	setup this condition never fires so we करो nothing extra.
 *
 *	FIXME: dual channel needs ->serialize support
 */

अटल अचिन्हित पूर्णांक opti82c46x_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;

	/* If timings are set and क्रम the wrong channel (2nd test is
	   due to a libata लघुcoming and will eventually go I hope) */
	अगर (ap->host->निजी_data != ap->host
	    && ap->host->निजी_data != शून्य)
		opti82c46x_set_piomode(ap, adev);

	वापस ata_sff_qc_issue(qc);
पूर्ण

अटल काष्ठा ata_port_operations opti82c46x_port_ops = अणु
	.inherits	= &legacy_base_port_ops,
	.set_piomode	= opti82c46x_set_piomode,
	.qc_issue	= opti82c46x_qc_issue,
पूर्ण;

/**
 *	qdi65x0_set_piomode		-	PIO setup क्रम QDI65x0
 *	@ap: Port
 *	@adev: Device
 *
 *	In single channel mode the 6580 has one घड़ी per device and we can
 *	aव्योम the requirement to घड़ी चयन. We also have to load the timing
 *	पूर्णांकo the right घड़ी according to whether we are master or slave.
 *
 *	In dual channel mode the 6580 has one घड़ी per channel and we have
 *	to software घड़ीचयन in qc_issue.
 */

अटल व्योम qdi65x0_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा ata_timing t;
	काष्ठा legacy_data *ld_qdi = ap->host->निजी_data;
	पूर्णांक active, recovery;
	u8 timing;

	/* Get the timing data in cycles */
	ata_timing_compute(adev, adev->pio_mode, &t, 30303, 1000);

	अगर (ld_qdi->fast) अणु
		active = 8 - clamp_val(t.active, 1, 8);
		recovery = 18 - clamp_val(t.recover, 3, 18);
	पूर्ण अन्यथा अणु
		active = 9 - clamp_val(t.active, 2, 9);
		recovery = 15 - clamp_val(t.recover, 0, 15);
	पूर्ण
	timing = (recovery << 4) | active | 0x08;
	ld_qdi->घड़ी[adev->devno] = timing;

	अगर (ld_qdi->type == QDI6580)
		outb(timing, ld_qdi->timing + 2 * adev->devno);
	अन्यथा
		outb(timing, ld_qdi->timing + 2 * ap->port_no);

	/* Clear the FIFO */
	अगर (ld_qdi->type != QDI6500 && adev->class != ATA_DEV_ATA)
		outb(0x5F, (ld_qdi->timing & 0xFFF0) + 3);
पूर्ण

/**
 *	qdi_qc_issue		-	command issue
 *	@qc: command pending
 *
 *	Called when the libata layer is about to issue a command. We wrap
 *	this पूर्णांकerface so that we can load the correct ATA timings.
 */

अटल अचिन्हित पूर्णांक qdi_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;
	काष्ठा legacy_data *ld_qdi = ap->host->निजी_data;

	अगर (ld_qdi->घड़ी[adev->devno] != ld_qdi->last) अणु
		अगर (adev->pio_mode) अणु
			ld_qdi->last = ld_qdi->घड़ी[adev->devno];
			outb(ld_qdi->घड़ी[adev->devno], ld_qdi->timing +
							2 * ap->port_no);
		पूर्ण
	पूर्ण
	वापस ata_sff_qc_issue(qc);
पूर्ण

अटल अचिन्हित पूर्णांक vlb32_data_xfer(काष्ठा ata_queued_cmd *qc,
				    अचिन्हित अक्षर *buf,
				    अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	काष्ठा ata_device *adev = qc->dev;
	काष्ठा ata_port *ap = adev->link->ap;
	पूर्णांक slop = buflen & 3;

	अगर (ata_id_has_dword_io(adev->id) && (slop == 0 || slop == 3)
					&& (ap->pflags & ATA_PFLAG_PIO32)) अणु
		अगर (rw == WRITE)
			ioग_लिखो32_rep(ap->ioaddr.data_addr, buf, buflen >> 2);
		अन्यथा
			ioपढ़ो32_rep(ap->ioaddr.data_addr, buf, buflen >> 2);

		अगर (unlikely(slop)) अणु
			__le32 pad;
			अगर (rw == WRITE) अणु
				स_नकल(&pad, buf + buflen - slop, slop);
				ioग_लिखो32(le32_to_cpu(pad), ap->ioaddr.data_addr);
			पूर्ण अन्यथा अणु
				pad = cpu_to_le32(ioपढ़ो32(ap->ioaddr.data_addr));
				स_नकल(buf + buflen - slop, &pad, slop);
			पूर्ण
		पूर्ण
		वापस (buflen + 3) & ~3;
	पूर्ण अन्यथा
		वापस ata_sff_data_xfer(qc, buf, buflen, rw);
पूर्ण

अटल पूर्णांक qdi_port(काष्ठा platक्रमm_device *dev,
			काष्ठा legacy_probe *lp, काष्ठा legacy_data *ld)
अणु
	अगर (devm_request_region(&dev->dev, lp->निजी, 4, "qdi") == शून्य)
		वापस -EBUSY;
	ld->timing = lp->निजी;
	वापस 0;
पूर्ण

अटल काष्ठा ata_port_operations qdi6500_port_ops = अणु
	.inherits	= &legacy_base_port_ops,
	.set_piomode	= qdi65x0_set_piomode,
	.qc_issue	= qdi_qc_issue,
	.sff_data_xfer	= vlb32_data_xfer,
पूर्ण;

अटल काष्ठा ata_port_operations qdi6580_port_ops = अणु
	.inherits	= &legacy_base_port_ops,
	.set_piomode	= qdi65x0_set_piomode,
	.sff_data_xfer	= vlb32_data_xfer,
पूर्ण;

अटल काष्ठा ata_port_operations qdi6580dp_port_ops = अणु
	.inherits	= &legacy_base_port_ops,
	.set_piomode	= qdi65x0_set_piomode,
	.qc_issue	= qdi_qc_issue,
	.sff_data_xfer	= vlb32_data_xfer,
पूर्ण;

अटल DEFINE_SPINLOCK(winbond_lock);

अटल व्योम winbond_ग_लिखोcfg(अचिन्हित दीर्घ port, u8 reg, u8 val)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&winbond_lock, flags);
	outb(reg, port + 0x01);
	outb(val, port + 0x02);
	spin_unlock_irqrestore(&winbond_lock, flags);
पूर्ण

अटल u8 winbond_पढ़ोcfg(अचिन्हित दीर्घ port, u8 reg)
अणु
	u8 val;

	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&winbond_lock, flags);
	outb(reg, port + 0x01);
	val = inb(port + 0x02);
	spin_unlock_irqrestore(&winbond_lock, flags);

	वापस val;
पूर्ण

अटल व्योम winbond_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा ata_timing t;
	काष्ठा legacy_data *ld_winbond = ap->host->निजी_data;
	पूर्णांक active, recovery;
	u8 reg;
	पूर्णांक timing = 0x88 + (ap->port_no * 4) + (adev->devno * 2);

	reg = winbond_पढ़ोcfg(ld_winbond->timing, 0x81);

	/* Get the timing data in cycles */
	अगर (reg & 0x40)		/* Fast VLB bus, assume 50MHz */
		ata_timing_compute(adev, adev->pio_mode, &t, 20000, 1000);
	अन्यथा
		ata_timing_compute(adev, adev->pio_mode, &t, 30303, 1000);

	active = (clamp_val(t.active, 3, 17) - 1) & 0x0F;
	recovery = (clamp_val(t.recover, 1, 15) + 1) & 0x0F;
	timing = (active << 4) | recovery;
	winbond_ग_लिखोcfg(ld_winbond->timing, timing, reg);

	/* Load the setup timing */

	reg = 0x35;
	अगर (adev->class != ATA_DEV_ATA)
		reg |= 0x08;	/* FIFO off */
	अगर (!ata_pio_need_iordy(adev))
		reg |= 0x02;	/* IORDY off */
	reg |= (clamp_val(t.setup, 0, 3) << 6);
	winbond_ग_लिखोcfg(ld_winbond->timing, timing + 1, reg);
पूर्ण

अटल पूर्णांक winbond_port(काष्ठा platक्रमm_device *dev,
			काष्ठा legacy_probe *lp, काष्ठा legacy_data *ld)
अणु
	अगर (devm_request_region(&dev->dev, lp->निजी, 4, "winbond") == शून्य)
		वापस -EBUSY;
	ld->timing = lp->निजी;
	वापस 0;
पूर्ण

अटल काष्ठा ata_port_operations winbond_port_ops = अणु
	.inherits	= &legacy_base_port_ops,
	.set_piomode	= winbond_set_piomode,
	.sff_data_xfer	= vlb32_data_xfer,
पूर्ण;

अटल काष्ठा legacy_controller controllers[] = अणु
	अणु"BIOS",	&legacy_port_ops, 	ATA_PIO4,
			ATA_FLAG_NO_IORDY,	0,			शून्य पूर्ण,
	अणु"Snooping", 	&simple_port_ops, 	ATA_PIO4,
			0,			0,			शून्य पूर्ण,
	अणु"PDC20230",	&pdc20230_port_ops,	ATA_PIO2,
			ATA_FLAG_NO_IORDY,
			ATA_PFLAG_PIO32 | ATA_PFLAG_PIO32CHANGE,	शून्य पूर्ण,
	अणु"HT6560A",	&ht6560a_port_ops,	ATA_PIO2,
			ATA_FLAG_NO_IORDY,	0,			शून्य पूर्ण,
	अणु"HT6560B",	&ht6560b_port_ops,	ATA_PIO4,
			ATA_FLAG_NO_IORDY,	0,			शून्य पूर्ण,
	अणु"OPTI82C611A",	&opti82c611a_port_ops,	ATA_PIO3,
			0,			0,			शून्य पूर्ण,
	अणु"OPTI82C46X",	&opti82c46x_port_ops,	ATA_PIO3,
			0,			0,			शून्य पूर्ण,
	अणु"QDI6500",	&qdi6500_port_ops,	ATA_PIO2,
			ATA_FLAG_NO_IORDY,
			ATA_PFLAG_PIO32 | ATA_PFLAG_PIO32CHANGE,    qdi_port पूर्ण,
	अणु"QDI6580",	&qdi6580_port_ops,	ATA_PIO4,
			0, ATA_PFLAG_PIO32 | ATA_PFLAG_PIO32CHANGE, qdi_port पूर्ण,
	अणु"QDI6580DP",	&qdi6580dp_port_ops,	ATA_PIO4,
			0, ATA_PFLAG_PIO32 | ATA_PFLAG_PIO32CHANGE, qdi_port पूर्ण,
	अणु"W83759A",	&winbond_port_ops,	ATA_PIO4,
			0, ATA_PFLAG_PIO32 | ATA_PFLAG_PIO32CHANGE,
								winbond_port पूर्ण
पूर्ण;

/**
 *	probe_chip_type		-	Discover controller
 *	@probe: Probe entry to check
 *
 *	Probe an ATA port and identअगरy the type of controller. We करोn't
 *	check अगर the controller appears to be driveless at this poपूर्णांक.
 */

अटल __init पूर्णांक probe_chip_type(काष्ठा legacy_probe *probe)
अणु
	पूर्णांक mask = 1 << probe->slot;

	अगर (winbond && (probe->port == 0x1F0 || probe->port == 0x170)) अणु
		u8 reg = winbond_पढ़ोcfg(winbond, 0x81);
		reg |= 0x80;	/* jumpered mode off */
		winbond_ग_लिखोcfg(winbond, 0x81, reg);
		reg = winbond_पढ़ोcfg(winbond, 0x83);
		reg |= 0xF0;	/* local control */
		winbond_ग_लिखोcfg(winbond, 0x83, reg);
		reg = winbond_पढ़ोcfg(winbond, 0x85);
		reg |= 0xF0;	/* programmable timing */
		winbond_ग_लिखोcfg(winbond, 0x85, reg);

		reg = winbond_पढ़ोcfg(winbond, 0x81);

		अगर (reg & mask)
			वापस W83759A;
	पूर्ण
	अगर (probe->port == 0x1F0) अणु
		अचिन्हित दीर्घ flags;
		local_irq_save(flags);
		/* Probes */
		outb(inb(0x1F2) | 0x80, 0x1F2);
		inb(0x1F5);
		inb(0x1F2);
		inb(0x3F6);
		inb(0x3F6);
		inb(0x1F2);
		inb(0x1F2);

		अगर ((inb(0x1F2) & 0x80) == 0) अणु
			/* PDC20230c or 20630 ? */
			prपूर्णांकk(KERN_INFO  "PDC20230-C/20630 VLB ATA controller"
							" detected.\n");
			udelay(100);
			inb(0x1F5);
			local_irq_restore(flags);
			वापस PDC20230;
		पूर्ण अन्यथा अणु
			outb(0x55, 0x1F2);
			inb(0x1F2);
			inb(0x1F2);
			अगर (inb(0x1F2) == 0x00)
				prपूर्णांकk(KERN_INFO "PDC20230-B VLB ATA "
						     "controller detected.\n");
			local_irq_restore(flags);
			वापस BIOS;
		पूर्ण
	पूर्ण

	अगर (ht6560a & mask)
		वापस HT6560A;
	अगर (ht6560b & mask)
		वापस HT6560B;
	अगर (opti82c611a & mask)
		वापस OPTI611A;
	अगर (opti82c46x & mask)
		वापस OPTI46X;
	अगर (स्वतःspeed & mask)
		वापस SNOOP;
	वापस BIOS;
पूर्ण


/**
 *	legacy_init_one		-	attach a legacy पूर्णांकerface
 *	@probe: probe record
 *
 *	Register an ISA bus IDE पूर्णांकerface. Such पूर्णांकerfaces are PIO and we
 *	assume करो not support IRQ sharing.
 */

अटल __init पूर्णांक legacy_init_one(काष्ठा legacy_probe *probe)
अणु
	काष्ठा legacy_controller *controller = &controllers[probe->type];
	पूर्णांक pio_modes = controller->pio_mask;
	अचिन्हित दीर्घ io = probe->port;
	u32 mask = (1 << probe->slot);
	काष्ठा ata_port_operations *ops = controller->ops;
	काष्ठा legacy_data *ld = &legacy_data[probe->slot];
	काष्ठा ata_host *host = शून्य;
	काष्ठा ata_port *ap;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा ata_device *dev;
	व्योम __iomem *io_addr, *ctrl_addr;
	u32 iordy = (iordy_mask & mask) ? 0: ATA_FLAG_NO_IORDY;
	पूर्णांक ret;

	iordy |= controller->flags;

	pdev = platक्रमm_device_रेजिस्टर_simple(DRV_NAME, probe->slot, शून्य, 0);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	ret = -EBUSY;
	अगर (devm_request_region(&pdev->dev, io, 8, "pata_legacy") == शून्य ||
	    devm_request_region(&pdev->dev, io + 0x0206, 1,
							"pata_legacy") == शून्य)
		जाओ fail;

	ret = -ENOMEM;
	io_addr = devm_ioport_map(&pdev->dev, io, 8);
	ctrl_addr = devm_ioport_map(&pdev->dev, io + 0x0206, 1);
	अगर (!io_addr || !ctrl_addr)
		जाओ fail;
	ld->type = probe->type;
	अगर (controller->setup)
		अगर (controller->setup(pdev, probe, ld) < 0)
			जाओ fail;
	host = ata_host_alloc(&pdev->dev, 1);
	अगर (!host)
		जाओ fail;
	ap = host->ports[0];

	ap->ops = ops;
	ap->pio_mask = pio_modes;
	ap->flags |= ATA_FLAG_SLAVE_POSS | iordy;
	ap->pflags |= controller->pflags;
	ap->ioaddr.cmd_addr = io_addr;
	ap->ioaddr.altstatus_addr = ctrl_addr;
	ap->ioaddr.ctl_addr = ctrl_addr;
	ata_sff_std_ports(&ap->ioaddr);
	ap->host->निजी_data = ld;

	ata_port_desc(ap, "cmd 0x%lx ctl 0x%lx", io, io + 0x0206);

	ret = ata_host_activate(host, probe->irq, ata_sff_पूर्णांकerrupt, 0,
				&legacy_sht);
	अगर (ret)
		जाओ fail;
	async_synchronize_full();
	ld->platक्रमm_dev = pdev;

	/* Nothing found means we drop the port as its probably not there */

	ret = -ENODEV;
	ata_क्रम_each_dev(dev, &ap->link, ALL) अणु
		अगर (!ata_dev_असलent(dev)) अणु
			legacy_host[probe->slot] = host;
			ld->platक्रमm_dev = pdev;
			वापस 0;
		पूर्ण
	पूर्ण
	ata_host_detach(host);
fail:
	platक्रमm_device_unरेजिस्टर(pdev);
	वापस ret;
पूर्ण

/**
 *	legacy_check_special_हालs	-	ATA special हालs
 *	@p: PCI device to check
 *	@primary: set this अगर we find an ATA master
 *	@secondary: set this अगर we find an ATA secondary
 *
 *	A small number of venकरोrs implemented early PCI ATA पूर्णांकerfaces
 *	on bridge logic without the ATA पूर्णांकerface being PCI visible.
 *	Where we have a matching PCI driver we must skip the relevant
 *	device here. If we करोn't know about it then the legacy driver
 *	is the right driver anyway.
 */

अटल व्योम __init legacy_check_special_हालs(काष्ठा pci_dev *p, पूर्णांक *primary,
								पूर्णांक *secondary)
अणु
	/* Cyrix CS5510 pre SFF MWDMA ATA on the bridge */
	अगर (p->venकरोr == 0x1078 && p->device == 0x0000) अणु
		*primary = *secondary = 1;
		वापस;
	पूर्ण
	/* Cyrix CS5520 pre SFF MWDMA ATA on the bridge */
	अगर (p->venकरोr == 0x1078 && p->device == 0x0002) अणु
		*primary = *secondary = 1;
		वापस;
	पूर्ण
	/* Intel MPIIX - PIO ATA on non PCI side of bridge */
	अगर (p->venकरोr == 0x8086 && p->device == 0x1234) अणु
		u16 r;
		pci_पढ़ो_config_word(p, 0x6C, &r);
		अगर (r & 0x8000) अणु
			/* ATA port enabled */
			अगर (r & 0x4000)
				*secondary = 1;
			अन्यथा
				*primary = 1;
		पूर्ण
		वापस;
	पूर्ण
पूर्ण

अटल __init व्योम probe_opti_vlb(व्योम)
अणु
	/* If an OPTI 82C46X is present find out where the channels are */
	अटल स्थिर अक्षर *optis[4] = अणु
		"3/463MV", "5MV",
		"5MVA", "5MVB"
	पूर्ण;
	u8 chans = 1;
	u8 ctrl = (opti_syscfg(0x30) & 0xC0) >> 6;

	opti82c46x = 3;	/* Assume master and slave first */
	prपूर्णांकk(KERN_INFO DRV_NAME ": Opti 82C46%s chipset support.\n",
								optis[ctrl]);
	अगर (ctrl == 3)
		chans = (opti_syscfg(0x3F) & 0x20) ? 2 : 1;
	ctrl = opti_syscfg(0xAC);
	/* Check enabled and this port is the 465MV port. On the
	   MVB we may have two channels */
	अगर (ctrl & 8) अणु
		अगर (chans == 2) अणु
			legacy_probe_add(0x1F0, 14, OPTI46X, 0);
			legacy_probe_add(0x170, 15, OPTI46X, 0);
		पूर्ण
		अगर (ctrl & 4)
			legacy_probe_add(0x170, 15, OPTI46X, 0);
		अन्यथा
			legacy_probe_add(0x1F0, 14, OPTI46X, 0);
	पूर्ण अन्यथा
		legacy_probe_add(0x1F0, 14, OPTI46X, 0);
पूर्ण

अटल __init व्योम qdi65_identअगरy_port(u8 r, u8 res, अचिन्हित दीर्घ port)
अणु
	अटल स्थिर अचिन्हित दीर्घ ide_port[2] = अणु 0x170, 0x1F0 पूर्ण;
	/* Check card type */
	अगर ((r & 0xF0) == 0xC0) अणु
		/* QD6500: single channel */
		अगर (r & 8)
			/* Disabled ? */
			वापस;
		legacy_probe_add(ide_port[r & 0x01], 14 + (r & 0x01),
								QDI6500, port);
	पूर्ण
	अगर (((r & 0xF0) == 0xA0) || (r & 0xF0) == 0x50) अणु
		/* QD6580: dual channel */
		अगर (!request_region(port + 2 , 2, "pata_qdi")) अणु
			release_region(port, 2);
			वापस;
		पूर्ण
		res = inb(port + 3);
		/* Single channel mode ? */
		अगर (res & 1)
			legacy_probe_add(ide_port[r & 0x01], 14 + (r & 0x01),
								QDI6580, port);
		अन्यथा अणु /* Dual channel mode */
			legacy_probe_add(0x1F0, 14, QDI6580DP, port);
			/* port + 0x02, r & 0x04 */
			legacy_probe_add(0x170, 15, QDI6580DP, port + 2);
		पूर्ण
		release_region(port + 2, 2);
	पूर्ण
पूर्ण

अटल __init व्योम probe_qdi_vlb(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अटल स्थिर अचिन्हित दीर्घ qd_port[2] = अणु 0x30, 0xB0 पूर्ण;
	पूर्णांक i;

	/*
	 *	Check each possible QD65xx base address
	 */

	क्रम (i = 0; i < 2; i++) अणु
		अचिन्हित दीर्घ port = qd_port[i];
		u8 r, res;


		अगर (request_region(port, 2, "pata_qdi")) अणु
			/* Check क्रम a card */
			local_irq_save(flags);
			/* I have no h/w that needs this delay but it
			   is present in the historic code */
			r = inb(port);
			udelay(1);
			outb(0x19, port);
			udelay(1);
			res = inb(port);
			udelay(1);
			outb(r, port);
			udelay(1);
			local_irq_restore(flags);

			/* Fail */
			अगर (res == 0x19) अणु
				release_region(port, 2);
				जारी;
			पूर्ण
			/* Passes the presence test */
			r = inb(port + 1);
			udelay(1);
			/* Check port agrees with port set */
			अगर ((r & 2) >> 1 == i)
				qdi65_identअगरy_port(r, res, port);
			release_region(port, 2);
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	legacy_init		-	attach legacy पूर्णांकerfaces
 *
 *	Attach legacy IDE पूर्णांकerfaces by scanning the usual IRQ/port suspects.
 *	Right now we करो not scan the ide0 and ide1 address but should करो so
 *	क्रम non PCI प्रणालीs or प्रणालीs with no PCI IDE legacy mode devices.
 *	If you fix that note there are special हालs to consider like VLB
 *	drivers and CS5510/20.
 */

अटल __init पूर्णांक legacy_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक ct = 0;
	पूर्णांक primary = 0;
	पूर्णांक secondary = 0;
	पूर्णांक pci_present = 0;
	काष्ठा legacy_probe *pl = &probe_list[0];
	पूर्णांक slot = 0;

	काष्ठा pci_dev *p = शून्य;

	क्रम_each_pci_dev(p) अणु
		पूर्णांक r;
		/* Check क्रम any overlap of the प्रणाली ATA mappings. Native
		   mode controllers stuck on these addresses or some devices
		   in 'raid' mode won't be found by the storage class test */
		क्रम (r = 0; r < 6; r++) अणु
			अगर (pci_resource_start(p, r) == 0x1f0)
				primary = 1;
			अगर (pci_resource_start(p, r) == 0x170)
				secondary = 1;
		पूर्ण
		/* Check क्रम special हालs */
		legacy_check_special_हालs(p, &primary, &secondary);

		/* If PCI bus is present then करोn't probe क्रम tertiary
		   legacy ports */
		pci_present = 1;
	पूर्ण

	अगर (winbond == 1)
		winbond = 0x130;	/* Default port, alt is 1B0 */

	अगर (primary == 0 || all)
		legacy_probe_add(0x1F0, 14, UNKNOWN, 0);
	अगर (secondary == 0 || all)
		legacy_probe_add(0x170, 15, UNKNOWN, 0);

	अगर (probe_all || !pci_present) अणु
		/* ISA/VLB extra ports */
		legacy_probe_add(0x1E8, 11, UNKNOWN, 0);
		legacy_probe_add(0x168, 10, UNKNOWN, 0);
		legacy_probe_add(0x1E0, 8, UNKNOWN, 0);
		legacy_probe_add(0x160, 12, UNKNOWN, 0);
	पूर्ण

	अगर (opti82c46x)
		probe_opti_vlb();
	अगर (qdi)
		probe_qdi_vlb();

	क्रम (i = 0; i < NR_HOST; i++, pl++) अणु
		अगर (pl->port == 0)
			जारी;
		अगर (pl->type == UNKNOWN)
			pl->type = probe_chip_type(pl);
		pl->slot = slot++;
		अगर (legacy_init_one(pl) == 0)
			ct++;
	पूर्ण
	अगर (ct != 0)
		वापस 0;
	वापस -ENODEV;
पूर्ण

अटल __निकास व्योम legacy_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_legacy_host; i++) अणु
		काष्ठा legacy_data *ld = &legacy_data[i];
		ata_host_detach(legacy_host[i]);
		platक्रमm_device_unरेजिस्टर(ld->platक्रमm_dev);
	पूर्ण
पूर्ण

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for legacy ATA");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
MODULE_ALIAS("pata_qdi");
MODULE_ALIAS("pata_winbond");

module_init(legacy_init);
module_निकास(legacy_निकास);
