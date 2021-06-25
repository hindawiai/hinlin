<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  libata-sff.c - helper library क्रम PCI IDE BMDMA
 *
 *  Copyright 2003-2006 Red Hat, Inc.  All rights reserved.
 *  Copyright 2003-2006 Jeff Garzik
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Hardware करोcumentation available from http://www.t13.org/ and
 *  http://www.sata-io.org/
 */

#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/libata.h>
#समावेश <linux/highस्मृति.स>

#समावेश "libata.h"

अटल काष्ठा workqueue_काष्ठा *ata_sff_wq;

स्थिर काष्ठा ata_port_operations ata_sff_port_ops = अणु
	.inherits		= &ata_base_port_ops,

	.qc_prep		= ata_noop_qc_prep,
	.qc_issue		= ata_sff_qc_issue,
	.qc_fill_rtf		= ata_sff_qc_fill_rtf,

	.मुक्तze			= ata_sff_मुक्तze,
	.thaw			= ata_sff_thaw,
	.prereset		= ata_sff_prereset,
	.softreset		= ata_sff_softreset,
	.hardreset		= sata_sff_hardreset,
	.postreset		= ata_sff_postreset,
	.error_handler		= ata_sff_error_handler,

	.sff_dev_select		= ata_sff_dev_select,
	.sff_check_status	= ata_sff_check_status,
	.sff_tf_load		= ata_sff_tf_load,
	.sff_tf_पढ़ो		= ata_sff_tf_पढ़ो,
	.sff_exec_command	= ata_sff_exec_command,
	.sff_data_xfer		= ata_sff_data_xfer,
	.sff_drain_fअगरo		= ata_sff_drain_fअगरo,

	.lost_पूर्णांकerrupt		= ata_sff_lost_पूर्णांकerrupt,
पूर्ण;
EXPORT_SYMBOL_GPL(ata_sff_port_ops);

/**
 *	ata_sff_check_status - Read device status reg & clear पूर्णांकerrupt
 *	@ap: port where the device is
 *
 *	Reads ATA taskfile status रेजिस्टर क्रम currently-selected device
 *	and वापस its value. This also clears pending पूर्णांकerrupts
 *      from this device
 *
 *	LOCKING:
 *	Inherited from caller.
 */
u8 ata_sff_check_status(काष्ठा ata_port *ap)
अणु
	वापस ioपढ़ो8(ap->ioaddr.status_addr);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_check_status);

/**
 *	ata_sff_altstatus - Read device alternate status reg
 *	@ap: port where the device is
 *
 *	Reads ATA taskfile alternate status रेजिस्टर क्रम
 *	currently-selected device and वापस its value.
 *
 *	Note: may NOT be used as the check_altstatus() entry in
 *	ata_port_operations.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल u8 ata_sff_altstatus(काष्ठा ata_port *ap)
अणु
	अगर (ap->ops->sff_check_altstatus)
		वापस ap->ops->sff_check_altstatus(ap);

	वापस ioपढ़ो8(ap->ioaddr.altstatus_addr);
पूर्ण

/**
 *	ata_sff_irq_status - Check अगर the device is busy
 *	@ap: port where the device is
 *
 *	Determine अगर the port is currently busy. Uses altstatus
 *	अगर available in order to aव्योम clearing shared IRQ status
 *	when finding an IRQ source. Non ctl capable devices करोn't
 *	share पूर्णांकerrupt lines क्रमtunately क्रम us.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल u8 ata_sff_irq_status(काष्ठा ata_port *ap)
अणु
	u8 status;

	अगर (ap->ops->sff_check_altstatus || ap->ioaddr.altstatus_addr) अणु
		status = ata_sff_altstatus(ap);
		/* Not us: We are busy */
		अगर (status & ATA_BUSY)
			वापस status;
	पूर्ण
	/* Clear INTRQ latch */
	status = ap->ops->sff_check_status(ap);
	वापस status;
पूर्ण

/**
 *	ata_sff_sync - Flush ग_लिखोs
 *	@ap: Port to रुको क्रम.
 *
 *	CAUTION:
 *	If we have an mmio device with no ctl and no altstatus
 *	method this will fail. No such devices are known to exist.
 *
 *	LOCKING:
 *	Inherited from caller.
 */

अटल व्योम ata_sff_sync(काष्ठा ata_port *ap)
अणु
	अगर (ap->ops->sff_check_altstatus)
		ap->ops->sff_check_altstatus(ap);
	अन्यथा अगर (ap->ioaddr.altstatus_addr)
		ioपढ़ो8(ap->ioaddr.altstatus_addr);
पूर्ण

/**
 *	ata_sff_छोड़ो		-	Flush ग_लिखोs and रुको 400nS
 *	@ap: Port to छोड़ो क्रम.
 *
 *	CAUTION:
 *	If we have an mmio device with no ctl and no altstatus
 *	method this will fail. No such devices are known to exist.
 *
 *	LOCKING:
 *	Inherited from caller.
 */

व्योम ata_sff_छोड़ो(काष्ठा ata_port *ap)
अणु
	ata_sff_sync(ap);
	ndelay(400);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_छोड़ो);

/**
 *	ata_sff_dma_छोड़ो	-	Pause beक्रमe commencing DMA
 *	@ap: Port to छोड़ो क्रम.
 *
 *	Perक्रमm I/O fencing and ensure sufficient cycle delays occur
 *	क्रम the HDMA1:0 transition
 */

व्योम ata_sff_dma_छोड़ो(काष्ठा ata_port *ap)
अणु
	अगर (ap->ops->sff_check_altstatus || ap->ioaddr.altstatus_addr) अणु
		/* An altstatus पढ़ो will cause the needed delay without
		   messing up the IRQ status */
		ata_sff_altstatus(ap);
		वापस;
	पूर्ण
	/* There are no DMA controllers without ctl. BUG here to ensure
	   we never violate the HDMA1:0 transition timing and risk
	   corruption. */
	BUG();
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_dma_छोड़ो);

/**
 *	ata_sff_busy_sleep - sleep until BSY clears, or समयout
 *	@ap: port containing status रेजिस्टर to be polled
 *	@पंचांगout_pat: impatience समयout in msecs
 *	@पंचांगout: overall समयout in msecs
 *
 *	Sleep until ATA Status रेजिस्टर bit BSY clears,
 *	or a समयout occurs.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_sff_busy_sleep(काष्ठा ata_port *ap,
		       अचिन्हित दीर्घ पंचांगout_pat, अचिन्हित दीर्घ पंचांगout)
अणु
	अचिन्हित दीर्घ समयr_start, समयout;
	u8 status;

	status = ata_sff_busy_रुको(ap, ATA_BUSY, 300);
	समयr_start = jअगरfies;
	समयout = ata_deadline(समयr_start, पंचांगout_pat);
	जबतक (status != 0xff && (status & ATA_BUSY) &&
	       समय_beक्रमe(jअगरfies, समयout)) अणु
		ata_msleep(ap, 50);
		status = ata_sff_busy_रुको(ap, ATA_BUSY, 3);
	पूर्ण

	अगर (status != 0xff && (status & ATA_BUSY))
		ata_port_warn(ap,
			      "port is slow to respond, please be patient (Status 0x%x)\n",
			      status);

	समयout = ata_deadline(समयr_start, पंचांगout);
	जबतक (status != 0xff && (status & ATA_BUSY) &&
	       समय_beक्रमe(jअगरfies, समयout)) अणु
		ata_msleep(ap, 50);
		status = ap->ops->sff_check_status(ap);
	पूर्ण

	अगर (status == 0xff)
		वापस -ENODEV;

	अगर (status & ATA_BUSY) अणु
		ata_port_err(ap,
			     "port failed to respond (%lu secs, Status 0x%x)\n",
			     DIV_ROUND_UP(पंचांगout, 1000), status);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_busy_sleep);

अटल पूर्णांक ata_sff_check_पढ़ोy(काष्ठा ata_link *link)
अणु
	u8 status = link->ap->ops->sff_check_status(link->ap);

	वापस ata_check_पढ़ोy(status);
पूर्ण

/**
 *	ata_sff_रुको_पढ़ोy - sleep until BSY clears, or समयout
 *	@link: SFF link to रुको पढ़ोy status क्रम
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Sleep until ATA Status रेजिस्टर bit BSY clears, or समयout
 *	occurs.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_sff_रुको_पढ़ोy(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	वापस ata_रुको_पढ़ोy(link, deadline, ata_sff_check_पढ़ोy);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_रुको_पढ़ोy);

/**
 *	ata_sff_set_devctl - Write device control reg
 *	@ap: port where the device is
 *	@ctl: value to ग_लिखो
 *
 *	Writes ATA taskfile device control रेजिस्टर.
 *
 *	Note: may NOT be used as the sff_set_devctl() entry in
 *	ata_port_operations.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल व्योम ata_sff_set_devctl(काष्ठा ata_port *ap, u8 ctl)
अणु
	अगर (ap->ops->sff_set_devctl)
		ap->ops->sff_set_devctl(ap, ctl);
	अन्यथा
		ioग_लिखो8(ctl, ap->ioaddr.ctl_addr);
पूर्ण

/**
 *	ata_sff_dev_select - Select device 0/1 on ATA bus
 *	@ap: ATA channel to manipulate
 *	@device: ATA device (numbered from zero) to select
 *
 *	Use the method defined in the ATA specअगरication to
 *	make either device 0, or device 1, active on the
 *	ATA channel.  Works with both PIO and MMIO.
 *
 *	May be used as the dev_select() entry in ata_port_operations.
 *
 *	LOCKING:
 *	caller.
 */
व्योम ata_sff_dev_select(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device)
अणु
	u8 पंचांगp;

	अगर (device == 0)
		पंचांगp = ATA_DEVICE_OBS;
	अन्यथा
		पंचांगp = ATA_DEVICE_OBS | ATA_DEV1;

	ioग_लिखो8(पंचांगp, ap->ioaddr.device_addr);
	ata_sff_छोड़ो(ap);	/* needed; also flushes, क्रम mmio */
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_dev_select);

/**
 *	ata_dev_select - Select device 0/1 on ATA bus
 *	@ap: ATA channel to manipulate
 *	@device: ATA device (numbered from zero) to select
 *	@रुको: non-zero to रुको क्रम Status रेजिस्टर BSY bit to clear
 *	@can_sleep: non-zero अगर context allows sleeping
 *
 *	Use the method defined in the ATA specअगरication to
 *	make either device 0, or device 1, active on the
 *	ATA channel.
 *
 *	This is a high-level version of ata_sff_dev_select(), which
 *	additionally provides the services of inserting the proper
 *	छोड़ोs and status polling, where needed.
 *
 *	LOCKING:
 *	caller.
 */
अटल व्योम ata_dev_select(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device,
			   अचिन्हित पूर्णांक रुको, अचिन्हित पूर्णांक can_sleep)
अणु
	अगर (ata_msg_probe(ap))
		ata_port_info(ap, "ata_dev_select: ENTER, device %u, wait %u\n",
			      device, रुको);

	अगर (रुको)
		ata_रुको_idle(ap);

	ap->ops->sff_dev_select(ap, device);

	अगर (रुको) अणु
		अगर (can_sleep && ap->link.device[device].class == ATA_DEV_ATAPI)
			ata_msleep(ap, 150);
		ata_रुको_idle(ap);
	पूर्ण
पूर्ण

/**
 *	ata_sff_irq_on - Enable पूर्णांकerrupts on a port.
 *	@ap: Port on which पूर्णांकerrupts are enabled.
 *
 *	Enable पूर्णांकerrupts on a legacy IDE device using MMIO or PIO,
 *	रुको क्रम idle, clear any pending पूर्णांकerrupts.
 *
 *	Note: may NOT be used as the sff_irq_on() entry in
 *	ata_port_operations.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
व्योम ata_sff_irq_on(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

	अगर (ap->ops->sff_irq_on) अणु
		ap->ops->sff_irq_on(ap);
		वापस;
	पूर्ण

	ap->ctl &= ~ATA_NIEN;
	ap->last_ctl = ap->ctl;

	अगर (ap->ops->sff_set_devctl || ioaddr->ctl_addr)
		ata_sff_set_devctl(ap, ap->ctl);
	ata_रुको_idle(ap);

	अगर (ap->ops->sff_irq_clear)
		ap->ops->sff_irq_clear(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_irq_on);

/**
 *	ata_sff_tf_load - send taskfile रेजिस्टरs to host controller
 *	@ap: Port to which output is sent
 *	@tf: ATA taskfile रेजिस्टर set
 *
 *	Outमाला_दो ATA taskfile to standard ATA host controller.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
व्योम ata_sff_tf_load(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	अचिन्हित पूर्णांक is_addr = tf->flags & ATA_TFLAG_ISADDR;

	अगर (tf->ctl != ap->last_ctl) अणु
		अगर (ioaddr->ctl_addr)
			ioग_लिखो8(tf->ctl, ioaddr->ctl_addr);
		ap->last_ctl = tf->ctl;
		ata_रुको_idle(ap);
	पूर्ण

	अगर (is_addr && (tf->flags & ATA_TFLAG_LBA48)) अणु
		WARN_ON_ONCE(!ioaddr->ctl_addr);
		ioग_लिखो8(tf->hob_feature, ioaddr->feature_addr);
		ioग_लिखो8(tf->hob_nsect, ioaddr->nsect_addr);
		ioग_लिखो8(tf->hob_lbal, ioaddr->lbal_addr);
		ioग_लिखो8(tf->hob_lbam, ioaddr->lbam_addr);
		ioग_लिखो8(tf->hob_lbah, ioaddr->lbah_addr);
		VPRINTK("hob: feat 0x%X nsect 0x%X, lba 0x%X 0x%X 0x%X\n",
			tf->hob_feature,
			tf->hob_nsect,
			tf->hob_lbal,
			tf->hob_lbam,
			tf->hob_lbah);
	पूर्ण

	अगर (is_addr) अणु
		ioग_लिखो8(tf->feature, ioaddr->feature_addr);
		ioग_लिखो8(tf->nsect, ioaddr->nsect_addr);
		ioग_लिखो8(tf->lbal, ioaddr->lbal_addr);
		ioग_लिखो8(tf->lbam, ioaddr->lbam_addr);
		ioग_लिखो8(tf->lbah, ioaddr->lbah_addr);
		VPRINTK("feat 0x%X nsect 0x%X lba 0x%X 0x%X 0x%X\n",
			tf->feature,
			tf->nsect,
			tf->lbal,
			tf->lbam,
			tf->lbah);
	पूर्ण

	अगर (tf->flags & ATA_TFLAG_DEVICE) अणु
		ioग_लिखो8(tf->device, ioaddr->device_addr);
		VPRINTK("device 0x%X\n", tf->device);
	पूर्ण

	ata_रुको_idle(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_tf_load);

/**
 *	ata_sff_tf_पढ़ो - input device's ATA taskfile shaकरोw रेजिस्टरs
 *	@ap: Port from which input is पढ़ो
 *	@tf: ATA taskfile रेजिस्टर set क्रम storing input
 *
 *	Reads ATA taskfile रेजिस्टरs क्रम currently-selected device
 *	पूर्णांकo @tf. Assumes the device has a fully SFF compliant task file
 *	layout and behaviour. If you device करोes not (eg has a dअगरferent
 *	status method) then you will need to provide a replacement tf_पढ़ो
 *
 *	LOCKING:
 *	Inherited from caller.
 */
व्योम ata_sff_tf_पढ़ो(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

	tf->command = ata_sff_check_status(ap);
	tf->feature = ioपढ़ो8(ioaddr->error_addr);
	tf->nsect = ioपढ़ो8(ioaddr->nsect_addr);
	tf->lbal = ioपढ़ो8(ioaddr->lbal_addr);
	tf->lbam = ioपढ़ो8(ioaddr->lbam_addr);
	tf->lbah = ioपढ़ो8(ioaddr->lbah_addr);
	tf->device = ioपढ़ो8(ioaddr->device_addr);

	अगर (tf->flags & ATA_TFLAG_LBA48) अणु
		अगर (likely(ioaddr->ctl_addr)) अणु
			ioग_लिखो8(tf->ctl | ATA_HOB, ioaddr->ctl_addr);
			tf->hob_feature = ioपढ़ो8(ioaddr->error_addr);
			tf->hob_nsect = ioपढ़ो8(ioaddr->nsect_addr);
			tf->hob_lbal = ioपढ़ो8(ioaddr->lbal_addr);
			tf->hob_lbam = ioपढ़ो8(ioaddr->lbam_addr);
			tf->hob_lbah = ioपढ़ो8(ioaddr->lbah_addr);
			ioग_लिखो8(tf->ctl, ioaddr->ctl_addr);
			ap->last_ctl = tf->ctl;
		पूर्ण अन्यथा
			WARN_ON_ONCE(1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_tf_पढ़ो);

/**
 *	ata_sff_exec_command - issue ATA command to host controller
 *	@ap: port to which command is being issued
 *	@tf: ATA taskfile रेजिस्टर set
 *
 *	Issues ATA command, with proper synchronization with पूर्णांकerrupt
 *	handler / other thपढ़ोs.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_sff_exec_command(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf)
अणु
	DPRINTK("ata%u: cmd 0x%X\n", ap->prपूर्णांक_id, tf->command);

	ioग_लिखो8(tf->command, ap->ioaddr.command_addr);
	ata_sff_छोड़ो(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_exec_command);

/**
 *	ata_tf_to_host - issue ATA taskfile to host controller
 *	@ap: port to which command is being issued
 *	@tf: ATA taskfile रेजिस्टर set
 *
 *	Issues ATA taskfile रेजिस्टर set to ATA host controller,
 *	with proper synchronization with पूर्णांकerrupt handler and
 *	other thपढ़ोs.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल अंतरभूत व्योम ata_tf_to_host(काष्ठा ata_port *ap,
				  स्थिर काष्ठा ata_taskfile *tf)
अणु
	ap->ops->sff_tf_load(ap, tf);
	ap->ops->sff_exec_command(ap, tf);
पूर्ण

/**
 *	ata_sff_data_xfer - Transfer data by PIO
 *	@qc: queued command
 *	@buf: data buffer
 *	@buflen: buffer length
 *	@rw: पढ़ो/ग_लिखो
 *
 *	Transfer data from/to the device data रेजिस्टर by PIO.
 *
 *	LOCKING:
 *	Inherited from caller.
 *
 *	RETURNS:
 *	Bytes consumed.
 */
अचिन्हित पूर्णांक ata_sff_data_xfer(काष्ठा ata_queued_cmd *qc, अचिन्हित अक्षर *buf,
			       अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	काष्ठा ata_port *ap = qc->dev->link->ap;
	व्योम __iomem *data_addr = ap->ioaddr.data_addr;
	अचिन्हित पूर्णांक words = buflen >> 1;

	/* Transfer multiple of 2 bytes */
	अगर (rw == READ)
		ioपढ़ो16_rep(data_addr, buf, words);
	अन्यथा
		ioग_लिखो16_rep(data_addr, buf, words);

	/* Transfer trailing byte, अगर any. */
	अगर (unlikely(buflen & 0x01)) अणु
		अचिन्हित अक्षर pad[2] = अणु पूर्ण;

		/* Poपूर्णांक buf to the tail of buffer */
		buf += buflen - 1;

		/*
		 * Use io*16_rep() accessors here as well to aव्योम poपूर्णांकlessly
		 * swapping bytes to and from on the big endian machines...
		 */
		अगर (rw == READ) अणु
			ioपढ़ो16_rep(data_addr, pad, 1);
			*buf = pad[0];
		पूर्ण अन्यथा अणु
			pad[0] = *buf;
			ioग_लिखो16_rep(data_addr, pad, 1);
		पूर्ण
		words++;
	पूर्ण

	वापस words << 1;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_data_xfer);

/**
 *	ata_sff_data_xfer32 - Transfer data by PIO
 *	@qc: queued command
 *	@buf: data buffer
 *	@buflen: buffer length
 *	@rw: पढ़ो/ग_लिखो
 *
 *	Transfer data from/to the device data रेजिस्टर by PIO using 32bit
 *	I/O operations.
 *
 *	LOCKING:
 *	Inherited from caller.
 *
 *	RETURNS:
 *	Bytes consumed.
 */

अचिन्हित पूर्णांक ata_sff_data_xfer32(काष्ठा ata_queued_cmd *qc, अचिन्हित अक्षर *buf,
			       अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	काष्ठा ata_device *dev = qc->dev;
	काष्ठा ata_port *ap = dev->link->ap;
	व्योम __iomem *data_addr = ap->ioaddr.data_addr;
	अचिन्हित पूर्णांक words = buflen >> 2;
	पूर्णांक slop = buflen & 3;

	अगर (!(ap->pflags & ATA_PFLAG_PIO32))
		वापस ata_sff_data_xfer(qc, buf, buflen, rw);

	/* Transfer multiple of 4 bytes */
	अगर (rw == READ)
		ioपढ़ो32_rep(data_addr, buf, words);
	अन्यथा
		ioग_लिखो32_rep(data_addr, buf, words);

	/* Transfer trailing bytes, अगर any */
	अगर (unlikely(slop)) अणु
		अचिन्हित अक्षर pad[4] = अणु पूर्ण;

		/* Poपूर्णांक buf to the tail of buffer */
		buf += buflen - slop;

		/*
		 * Use io*_rep() accessors here as well to aव्योम poपूर्णांकlessly
		 * swapping bytes to and from on the big endian machines...
		 */
		अगर (rw == READ) अणु
			अगर (slop < 3)
				ioपढ़ो16_rep(data_addr, pad, 1);
			अन्यथा
				ioपढ़ो32_rep(data_addr, pad, 1);
			स_नकल(buf, pad, slop);
		पूर्ण अन्यथा अणु
			स_नकल(pad, buf, slop);
			अगर (slop < 3)
				ioग_लिखो16_rep(data_addr, pad, 1);
			अन्यथा
				ioग_लिखो32_rep(data_addr, pad, 1);
		पूर्ण
	पूर्ण
	वापस (buflen + 1) & ~1;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_data_xfer32);

/**
 *	ata_pio_sector - Transfer a sector of data.
 *	@qc: Command on going
 *
 *	Transfer qc->sect_size bytes of data from/to the ATA device.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल व्योम ata_pio_sector(काष्ठा ata_queued_cmd *qc)
अणु
	पूर्णांक करो_ग_लिखो = (qc->tf.flags & ATA_TFLAG_WRITE);
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा page *page;
	अचिन्हित पूर्णांक offset;
	अचिन्हित अक्षर *buf;

	अगर (!qc->cursg) अणु
		qc->curbytes = qc->nbytes;
		वापस;
	पूर्ण
	अगर (qc->curbytes == qc->nbytes - qc->sect_size)
		ap->hsm_task_state = HSM_ST_LAST;

	page = sg_page(qc->cursg);
	offset = qc->cursg->offset + qc->cursg_ofs;

	/* get the current page and offset */
	page = nth_page(page, (offset >> PAGE_SHIFT));
	offset %= PAGE_SIZE;

	DPRINTK("data %s\n", qc->tf.flags & ATA_TFLAG_WRITE ? "write" : "read");

	/* करो the actual data transfer */
	buf = kmap_atomic(page);
	ap->ops->sff_data_xfer(qc, buf + offset, qc->sect_size, करो_ग_लिखो);
	kunmap_atomic(buf);

	अगर (!करो_ग_लिखो && !PageSlab(page))
		flush_dcache_page(page);

	qc->curbytes += qc->sect_size;
	qc->cursg_ofs += qc->sect_size;

	अगर (qc->cursg_ofs == qc->cursg->length) अणु
		qc->cursg = sg_next(qc->cursg);
		अगर (!qc->cursg)
			ap->hsm_task_state = HSM_ST_LAST;
		qc->cursg_ofs = 0;
	पूर्ण
पूर्ण

/**
 *	ata_pio_sectors - Transfer one or many sectors.
 *	@qc: Command on going
 *
 *	Transfer one or many sectors of data from/to the
 *	ATA device क्रम the DRQ request.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल व्योम ata_pio_sectors(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (is_multi_taskfile(&qc->tf)) अणु
		/* READ/WRITE MULTIPLE */
		अचिन्हित पूर्णांक nsect;

		WARN_ON_ONCE(qc->dev->multi_count == 0);

		nsect = min((qc->nbytes - qc->curbytes) / qc->sect_size,
			    qc->dev->multi_count);
		जबतक (nsect--)
			ata_pio_sector(qc);
	पूर्ण अन्यथा
		ata_pio_sector(qc);

	ata_sff_sync(qc->ap); /* flush */
पूर्ण

/**
 *	atapi_send_cdb - Write CDB bytes to hardware
 *	@ap: Port to which ATAPI device is attached.
 *	@qc: Taskfile currently active
 *
 *	When device has indicated its पढ़ोiness to accept
 *	a CDB, this function is called.  Send the CDB.
 *
 *	LOCKING:
 *	caller.
 */
अटल व्योम atapi_send_cdb(काष्ठा ata_port *ap, काष्ठा ata_queued_cmd *qc)
अणु
	/* send SCSI cdb */
	DPRINTK("send cdb\n");
	WARN_ON_ONCE(qc->dev->cdb_len < 12);

	ap->ops->sff_data_xfer(qc, qc->cdb, qc->dev->cdb_len, 1);
	ata_sff_sync(ap);
	/* FIXME: If the CDB is क्रम DMA करो we need to करो the transition delay
	   or is bmdma_start guaranteed to करो it ? */
	चयन (qc->tf.protocol) अणु
	हाल ATAPI_PROT_PIO:
		ap->hsm_task_state = HSM_ST;
		अवरोध;
	हाल ATAPI_PROT_NODATA:
		ap->hsm_task_state = HSM_ST_LAST;
		अवरोध;
#अगर_घोषित CONFIG_ATA_BMDMA
	हाल ATAPI_PROT_DMA:
		ap->hsm_task_state = HSM_ST_LAST;
		/* initiate bmdma */
		ap->ops->bmdma_start(qc);
		अवरोध;
#पूर्ण_अगर /* CONFIG_ATA_BMDMA */
	शेष:
		BUG();
	पूर्ण
पूर्ण

/**
 *	__atapi_pio_bytes - Transfer data from/to the ATAPI device.
 *	@qc: Command on going
 *	@bytes: number of bytes
 *
 *	Transfer Transfer data from/to the ATAPI device.
 *
 *	LOCKING:
 *	Inherited from caller.
 *
 */
अटल पूर्णांक __atapi_pio_bytes(काष्ठा ata_queued_cmd *qc, अचिन्हित पूर्णांक bytes)
अणु
	पूर्णांक rw = (qc->tf.flags & ATA_TFLAG_WRITE) ? WRITE : READ;
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *dev = qc->dev;
	काष्ठा ata_eh_info *ehi = &dev->link->eh_info;
	काष्ठा scatterlist *sg;
	काष्ठा page *page;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक offset, count, consumed;

next_sg:
	sg = qc->cursg;
	अगर (unlikely(!sg)) अणु
		ata_ehi_push_desc(ehi, "unexpected or too much trailing data "
				  "buf=%u cur=%u bytes=%u",
				  qc->nbytes, qc->curbytes, bytes);
		वापस -1;
	पूर्ण

	page = sg_page(sg);
	offset = sg->offset + qc->cursg_ofs;

	/* get the current page and offset */
	page = nth_page(page, (offset >> PAGE_SHIFT));
	offset %= PAGE_SIZE;

	/* करोn't overrun current sg */
	count = min(sg->length - qc->cursg_ofs, bytes);

	/* करोn't cross page boundaries */
	count = min(count, (अचिन्हित पूर्णांक)PAGE_SIZE - offset);

	DPRINTK("data %s\n", qc->tf.flags & ATA_TFLAG_WRITE ? "write" : "read");

	/* करो the actual data transfer */
	buf = kmap_atomic(page);
	consumed = ap->ops->sff_data_xfer(qc, buf + offset, count, rw);
	kunmap_atomic(buf);

	bytes -= min(bytes, consumed);
	qc->curbytes += count;
	qc->cursg_ofs += count;

	अगर (qc->cursg_ofs == sg->length) अणु
		qc->cursg = sg_next(qc->cursg);
		qc->cursg_ofs = 0;
	पूर्ण

	/*
	 * There used to be a  WARN_ON_ONCE(qc->cursg && count != consumed);
	 * Unक्रमtunately __atapi_pio_bytes करोesn't know enough to करो the WARN
	 * check correctly as it करोesn't know अगर it is the last request being
	 * made. Somebody should implement a proper sanity check.
	 */
	अगर (bytes)
		जाओ next_sg;
	वापस 0;
पूर्ण

/**
 *	atapi_pio_bytes - Transfer data from/to the ATAPI device.
 *	@qc: Command on going
 *
 *	Transfer Transfer data from/to the ATAPI device.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल व्योम atapi_pio_bytes(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *dev = qc->dev;
	काष्ठा ata_eh_info *ehi = &dev->link->eh_info;
	अचिन्हित पूर्णांक ireason, bc_lo, bc_hi, bytes;
	पूर्णांक i_ग_लिखो, करो_ग_लिखो = (qc->tf.flags & ATA_TFLAG_WRITE) ? 1 : 0;

	/* Abuse qc->result_tf क्रम temp storage of पूर्णांकermediate TF
	 * here to save some kernel stack usage.
	 * For normal completion, qc->result_tf is not relevant. For
	 * error, qc->result_tf is later overwritten by ata_qc_complete().
	 * So, the correctness of qc->result_tf is not affected.
	 */
	ap->ops->sff_tf_पढ़ो(ap, &qc->result_tf);
	ireason = qc->result_tf.nsect;
	bc_lo = qc->result_tf.lbam;
	bc_hi = qc->result_tf.lbah;
	bytes = (bc_hi << 8) | bc_lo;

	/* shall be cleared to zero, indicating xfer of data */
	अगर (unlikely(ireason & ATAPI_COD))
		जाओ atapi_check;

	/* make sure transfer direction matches expected */
	i_ग_लिखो = ((ireason & ATAPI_IO) == 0) ? 1 : 0;
	अगर (unlikely(करो_ग_लिखो != i_ग_लिखो))
		जाओ atapi_check;

	अगर (unlikely(!bytes))
		जाओ atapi_check;

	VPRINTK("ata%u: xfering %d bytes\n", ap->prपूर्णांक_id, bytes);

	अगर (unlikely(__atapi_pio_bytes(qc, bytes)))
		जाओ err_out;
	ata_sff_sync(ap); /* flush */

	वापस;

 atapi_check:
	ata_ehi_push_desc(ehi, "ATAPI check failed (ireason=0x%x bytes=%u)",
			  ireason, bytes);
 err_out:
	qc->err_mask |= AC_ERR_HSM;
	ap->hsm_task_state = HSM_ST_ERR;
पूर्ण

/**
 *	ata_hsm_ok_in_wq - Check अगर the qc can be handled in the workqueue.
 *	@ap: the target ata_port
 *	@qc: qc on going
 *
 *	RETURNS:
 *	1 अगर ok in workqueue, 0 otherwise.
 */
अटल अंतरभूत पूर्णांक ata_hsm_ok_in_wq(काष्ठा ata_port *ap,
						काष्ठा ata_queued_cmd *qc)
अणु
	अगर (qc->tf.flags & ATA_TFLAG_POLLING)
		वापस 1;

	अगर (ap->hsm_task_state == HSM_ST_FIRST) अणु
		अगर (qc->tf.protocol == ATA_PROT_PIO &&
		   (qc->tf.flags & ATA_TFLAG_WRITE))
		    वापस 1;

		अगर (ata_is_atapi(qc->tf.protocol) &&
		   !(qc->dev->flags & ATA_DFLAG_CDB_INTR))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	ata_hsm_qc_complete - finish a qc running on standard HSM
 *	@qc: Command to complete
 *	@in_wq: 1 अगर called from workqueue, 0 otherwise
 *
 *	Finish @qc which is running on standard HSM.
 *
 *	LOCKING:
 *	If @in_wq is zero, spin_lock_irqsave(host lock).
 *	Otherwise, none on entry and grअसल host lock.
 */
अटल व्योम ata_hsm_qc_complete(काष्ठा ata_queued_cmd *qc, पूर्णांक in_wq)
अणु
	काष्ठा ata_port *ap = qc->ap;

	अगर (ap->ops->error_handler) अणु
		अगर (in_wq) अणु
			/* EH might have kicked in जबतक host lock is
			 * released.
			 */
			qc = ata_qc_from_tag(ap, qc->tag);
			अगर (qc) अणु
				अगर (likely(!(qc->err_mask & AC_ERR_HSM))) अणु
					ata_sff_irq_on(ap);
					ata_qc_complete(qc);
				पूर्ण अन्यथा
					ata_port_मुक्तze(ap);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (likely(!(qc->err_mask & AC_ERR_HSM)))
				ata_qc_complete(qc);
			अन्यथा
				ata_port_मुक्तze(ap);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (in_wq) अणु
			ata_sff_irq_on(ap);
			ata_qc_complete(qc);
		पूर्ण अन्यथा
			ata_qc_complete(qc);
	पूर्ण
पूर्ण

/**
 *	ata_sff_hsm_move - move the HSM to the next state.
 *	@ap: the target ata_port
 *	@qc: qc on going
 *	@status: current device status
 *	@in_wq: 1 अगर called from workqueue, 0 otherwise
 *
 *	RETURNS:
 *	1 when poll next status needed, 0 otherwise.
 */
पूर्णांक ata_sff_hsm_move(काष्ठा ata_port *ap, काष्ठा ata_queued_cmd *qc,
		     u8 status, पूर्णांक in_wq)
अणु
	काष्ठा ata_link *link = qc->dev->link;
	काष्ठा ata_eh_info *ehi = &link->eh_info;
	पूर्णांक poll_next;

	lockdep_निश्चित_held(ap->lock);

	WARN_ON_ONCE((qc->flags & ATA_QCFLAG_ACTIVE) == 0);

	/* Make sure ata_sff_qc_issue() करोes not throw things
	 * like DMA polling पूर्णांकo the workqueue. Notice that
	 * in_wq is not equivalent to (qc->tf.flags & ATA_TFLAG_POLLING).
	 */
	WARN_ON_ONCE(in_wq != ata_hsm_ok_in_wq(ap, qc));

fsm_start:
	DPRINTK("ata%u: protocol %d task_state %d (dev_stat 0x%X)\n",
		ap->prपूर्णांक_id, qc->tf.protocol, ap->hsm_task_state, status);

	चयन (ap->hsm_task_state) अणु
	हाल HSM_ST_FIRST:
		/* Send first data block or PACKET CDB */

		/* If polling, we will stay in the work queue after
		 * sending the data. Otherwise, पूर्णांकerrupt handler
		 * takes over after sending the data.
		 */
		poll_next = (qc->tf.flags & ATA_TFLAG_POLLING);

		/* check device status */
		अगर (unlikely((status & ATA_DRQ) == 0)) अणु
			/* handle BSY=0, DRQ=0 as error */
			अगर (likely(status & (ATA_ERR | ATA_DF)))
				/* device stops HSM क्रम पात/error */
				qc->err_mask |= AC_ERR_DEV;
			अन्यथा अणु
				/* HSM violation. Let EH handle this */
				ata_ehi_push_desc(ehi,
					"ST_FIRST: !(DRQ|ERR|DF)");
				qc->err_mask |= AC_ERR_HSM;
			पूर्ण

			ap->hsm_task_state = HSM_ST_ERR;
			जाओ fsm_start;
		पूर्ण

		/* Device should not ask क्रम data transfer (DRQ=1)
		 * when it finds something wrong.
		 * We ignore DRQ here and stop the HSM by
		 * changing hsm_task_state to HSM_ST_ERR and
		 * let the EH पात the command or reset the device.
		 */
		अगर (unlikely(status & (ATA_ERR | ATA_DF))) अणु
			/* Some ATAPI tape drives क्रमget to clear the ERR bit
			 * when करोing the next command (mostly request sense).
			 * We ignore ERR here to workaround and proceed sending
			 * the CDB.
			 */
			अगर (!(qc->dev->horkage & ATA_HORKAGE_STUCK_ERR)) अणु
				ata_ehi_push_desc(ehi, "ST_FIRST: "
					"DRQ=1 with device error, "
					"dev_stat 0x%X", status);
				qc->err_mask |= AC_ERR_HSM;
				ap->hsm_task_state = HSM_ST_ERR;
				जाओ fsm_start;
			पूर्ण
		पूर्ण

		अगर (qc->tf.protocol == ATA_PROT_PIO) अणु
			/* PIO data out protocol.
			 * send first data block.
			 */

			/* ata_pio_sectors() might change the state
			 * to HSM_ST_LAST. so, the state is changed here
			 * beक्रमe ata_pio_sectors().
			 */
			ap->hsm_task_state = HSM_ST;
			ata_pio_sectors(qc);
		पूर्ण अन्यथा
			/* send CDB */
			atapi_send_cdb(ap, qc);

		/* अगर polling, ata_sff_pio_task() handles the rest.
		 * otherwise, पूर्णांकerrupt handler takes over from here.
		 */
		अवरोध;

	हाल HSM_ST:
		/* complete command or पढ़ो/ग_लिखो the data रेजिस्टर */
		अगर (qc->tf.protocol == ATAPI_PROT_PIO) अणु
			/* ATAPI PIO protocol */
			अगर ((status & ATA_DRQ) == 0) अणु
				/* No more data to transfer or device error.
				 * Device error will be tagged in HSM_ST_LAST.
				 */
				ap->hsm_task_state = HSM_ST_LAST;
				जाओ fsm_start;
			पूर्ण

			/* Device should not ask क्रम data transfer (DRQ=1)
			 * when it finds something wrong.
			 * We ignore DRQ here and stop the HSM by
			 * changing hsm_task_state to HSM_ST_ERR and
			 * let the EH पात the command or reset the device.
			 */
			अगर (unlikely(status & (ATA_ERR | ATA_DF))) अणु
				ata_ehi_push_desc(ehi, "ST-ATAPI: "
					"DRQ=1 with device error, "
					"dev_stat 0x%X", status);
				qc->err_mask |= AC_ERR_HSM;
				ap->hsm_task_state = HSM_ST_ERR;
				जाओ fsm_start;
			पूर्ण

			atapi_pio_bytes(qc);

			अगर (unlikely(ap->hsm_task_state == HSM_ST_ERR))
				/* bad ireason reported by device */
				जाओ fsm_start;

		पूर्ण अन्यथा अणु
			/* ATA PIO protocol */
			अगर (unlikely((status & ATA_DRQ) == 0)) अणु
				/* handle BSY=0, DRQ=0 as error */
				अगर (likely(status & (ATA_ERR | ATA_DF))) अणु
					/* device stops HSM क्रम पात/error */
					qc->err_mask |= AC_ERR_DEV;

					/* If diagnostic failed and this is
					 * IDENTIFY, it's likely a phantom
					 * device.  Mark hपूर्णांक.
					 */
					अगर (qc->dev->horkage &
					    ATA_HORKAGE_DIAGNOSTIC)
						qc->err_mask |=
							AC_ERR_NODEV_HINT;
				पूर्ण अन्यथा अणु
					/* HSM violation. Let EH handle this.
					 * Phantom devices also trigger this
					 * condition.  Mark hपूर्णांक.
					 */
					ata_ehi_push_desc(ehi, "ST-ATA: "
						"DRQ=0 without device error, "
						"dev_stat 0x%X", status);
					qc->err_mask |= AC_ERR_HSM |
							AC_ERR_NODEV_HINT;
				पूर्ण

				ap->hsm_task_state = HSM_ST_ERR;
				जाओ fsm_start;
			पूर्ण

			/* For PIO पढ़ोs, some devices may ask क्रम
			 * data transfer (DRQ=1) alone with ERR=1.
			 * We respect DRQ here and transfer one
			 * block of junk data beक्रमe changing the
			 * hsm_task_state to HSM_ST_ERR.
			 *
			 * For PIO ग_लिखोs, ERR=1 DRQ=1 करोesn't make
			 * sense since the data block has been
			 * transferred to the device.
			 */
			अगर (unlikely(status & (ATA_ERR | ATA_DF))) अणु
				/* data might be corrputed */
				qc->err_mask |= AC_ERR_DEV;

				अगर (!(qc->tf.flags & ATA_TFLAG_WRITE)) अणु
					ata_pio_sectors(qc);
					status = ata_रुको_idle(ap);
				पूर्ण

				अगर (status & (ATA_BUSY | ATA_DRQ)) अणु
					ata_ehi_push_desc(ehi, "ST-ATA: "
						"BUSY|DRQ persists on ERR|DF, "
						"dev_stat 0x%X", status);
					qc->err_mask |= AC_ERR_HSM;
				पूर्ण

				/* There are oddball controllers with
				 * status रेजिस्टर stuck at 0x7f and
				 * lbal/m/h at zero which makes it
				 * pass all other presence detection
				 * mechanisms we have.  Set NODEV_HINT
				 * क्रम it.  Kernel bz#7241.
				 */
				अगर (status == 0x7f)
					qc->err_mask |= AC_ERR_NODEV_HINT;

				/* ata_pio_sectors() might change the
				 * state to HSM_ST_LAST. so, the state
				 * is changed after ata_pio_sectors().
				 */
				ap->hsm_task_state = HSM_ST_ERR;
				जाओ fsm_start;
			पूर्ण

			ata_pio_sectors(qc);

			अगर (ap->hsm_task_state == HSM_ST_LAST &&
			    (!(qc->tf.flags & ATA_TFLAG_WRITE))) अणु
				/* all data पढ़ो */
				status = ata_रुको_idle(ap);
				जाओ fsm_start;
			पूर्ण
		पूर्ण

		poll_next = 1;
		अवरोध;

	हाल HSM_ST_LAST:
		अगर (unlikely(!ata_ok(status))) अणु
			qc->err_mask |= __ac_err_mask(status);
			ap->hsm_task_state = HSM_ST_ERR;
			जाओ fsm_start;
		पूर्ण

		/* no more data to transfer */
		DPRINTK("ata%u: dev %u command complete, drv_stat 0x%x\n",
			ap->prपूर्णांक_id, qc->dev->devno, status);

		WARN_ON_ONCE(qc->err_mask & (AC_ERR_DEV | AC_ERR_HSM));

		ap->hsm_task_state = HSM_ST_IDLE;

		/* complete taskfile transaction */
		ata_hsm_qc_complete(qc, in_wq);

		poll_next = 0;
		अवरोध;

	हाल HSM_ST_ERR:
		ap->hsm_task_state = HSM_ST_IDLE;

		/* complete taskfile transaction */
		ata_hsm_qc_complete(qc, in_wq);

		poll_next = 0;
		अवरोध;
	शेष:
		poll_next = 0;
		WARN(true, "ata%d: SFF host state machine in invalid state %d",
		     ap->prपूर्णांक_id, ap->hsm_task_state);
	पूर्ण

	वापस poll_next;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_hsm_move);

व्योम ata_sff_queue_work(काष्ठा work_काष्ठा *work)
अणु
	queue_work(ata_sff_wq, work);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_queue_work);

व्योम ata_sff_queue_delayed_work(काष्ठा delayed_work *dwork, अचिन्हित दीर्घ delay)
अणु
	queue_delayed_work(ata_sff_wq, dwork, delay);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_queue_delayed_work);

व्योम ata_sff_queue_pio_task(काष्ठा ata_link *link, अचिन्हित दीर्घ delay)
अणु
	काष्ठा ata_port *ap = link->ap;

	WARN_ON((ap->sff_pio_task_link != शून्य) &&
		(ap->sff_pio_task_link != link));
	ap->sff_pio_task_link = link;

	/* may fail अगर ata_sff_flush_pio_task() in progress */
	ata_sff_queue_delayed_work(&ap->sff_pio_task, msecs_to_jअगरfies(delay));
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_queue_pio_task);

व्योम ata_sff_flush_pio_task(काष्ठा ata_port *ap)
अणु
	DPRINTK("ENTER\n");

	cancel_delayed_work_sync(&ap->sff_pio_task);

	/*
	 * We wanna reset the HSM state to IDLE.  If we करो so without
	 * grabbing the port lock, critical sections रक्षित by it which
	 * expect the HSM state to stay stable may get surprised.  For
	 * example, we may set IDLE in between the समय
	 * __ata_sff_port_पूर्णांकr() checks क्रम HSM_ST_IDLE and beक्रमe it calls
	 * ata_sff_hsm_move() causing ata_sff_hsm_move() to BUG().
	 */
	spin_lock_irq(ap->lock);
	ap->hsm_task_state = HSM_ST_IDLE;
	spin_unlock_irq(ap->lock);

	ap->sff_pio_task_link = शून्य;

	अगर (ata_msg_ctl(ap))
		ata_port_dbg(ap, "%s: EXIT\n", __func__);
पूर्ण

अटल व्योम ata_sff_pio_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ata_port *ap =
		container_of(work, काष्ठा ata_port, sff_pio_task.work);
	काष्ठा ata_link *link = ap->sff_pio_task_link;
	काष्ठा ata_queued_cmd *qc;
	u8 status;
	पूर्णांक poll_next;

	spin_lock_irq(ap->lock);

	BUG_ON(ap->sff_pio_task_link == शून्य);
	/* qc can be शून्य अगर समयout occurred */
	qc = ata_qc_from_tag(ap, link->active_tag);
	अगर (!qc) अणु
		ap->sff_pio_task_link = शून्य;
		जाओ out_unlock;
	पूर्ण

fsm_start:
	WARN_ON_ONCE(ap->hsm_task_state == HSM_ST_IDLE);

	/*
	 * This is purely heuristic.  This is a fast path.
	 * Someबार when we enter, BSY will be cleared in
	 * a chk-status or two.  If not, the drive is probably seeking
	 * or something.  Snooze क्रम a couple msecs, then
	 * chk-status again.  If still busy, queue delayed work.
	 */
	status = ata_sff_busy_रुको(ap, ATA_BUSY, 5);
	अगर (status & ATA_BUSY) अणु
		spin_unlock_irq(ap->lock);
		ata_msleep(ap, 2);
		spin_lock_irq(ap->lock);

		status = ata_sff_busy_रुको(ap, ATA_BUSY, 10);
		अगर (status & ATA_BUSY) अणु
			ata_sff_queue_pio_task(link, ATA_SHORT_PAUSE);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/*
	 * hsm_move() may trigger another command to be processed.
	 * clean the link beक्रमehand.
	 */
	ap->sff_pio_task_link = शून्य;
	/* move the HSM */
	poll_next = ata_sff_hsm_move(ap, qc, status, 1);

	/* another command or पूर्णांकerrupt handler
	 * may be running at this poपूर्णांक.
	 */
	अगर (poll_next)
		जाओ fsm_start;
out_unlock:
	spin_unlock_irq(ap->lock);
पूर्ण

/**
 *	ata_sff_qc_issue - issue taskfile to a SFF controller
 *	@qc: command to issue to device
 *
 *	This function issues a PIO or NODATA command to a SFF
 *	controller.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Zero on success, AC_ERR_* mask on failure
 */
अचिन्हित पूर्णांक ata_sff_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_link *link = qc->dev->link;

	/* Use polling pio अगर the LLD करोesn't handle
	 * पूर्णांकerrupt driven pio and atapi CDB पूर्णांकerrupt.
	 */
	अगर (ap->flags & ATA_FLAG_PIO_POLLING)
		qc->tf.flags |= ATA_TFLAG_POLLING;

	/* select the device */
	ata_dev_select(ap, qc->dev->devno, 1, 0);

	/* start the command */
	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_NODATA:
		अगर (qc->tf.flags & ATA_TFLAG_POLLING)
			ata_qc_set_polling(qc);

		ata_tf_to_host(ap, &qc->tf);
		ap->hsm_task_state = HSM_ST_LAST;

		अगर (qc->tf.flags & ATA_TFLAG_POLLING)
			ata_sff_queue_pio_task(link, 0);

		अवरोध;

	हाल ATA_PROT_PIO:
		अगर (qc->tf.flags & ATA_TFLAG_POLLING)
			ata_qc_set_polling(qc);

		ata_tf_to_host(ap, &qc->tf);

		अगर (qc->tf.flags & ATA_TFLAG_WRITE) अणु
			/* PIO data out protocol */
			ap->hsm_task_state = HSM_ST_FIRST;
			ata_sff_queue_pio_task(link, 0);

			/* always send first data block using the
			 * ata_sff_pio_task() codepath.
			 */
		पूर्ण अन्यथा अणु
			/* PIO data in protocol */
			ap->hsm_task_state = HSM_ST;

			अगर (qc->tf.flags & ATA_TFLAG_POLLING)
				ata_sff_queue_pio_task(link, 0);

			/* अगर polling, ata_sff_pio_task() handles the
			 * rest.  otherwise, पूर्णांकerrupt handler takes
			 * over from here.
			 */
		पूर्ण

		अवरोध;

	हाल ATAPI_PROT_PIO:
	हाल ATAPI_PROT_NODATA:
		अगर (qc->tf.flags & ATA_TFLAG_POLLING)
			ata_qc_set_polling(qc);

		ata_tf_to_host(ap, &qc->tf);

		ap->hsm_task_state = HSM_ST_FIRST;

		/* send cdb by polling अगर no cdb पूर्णांकerrupt */
		अगर ((!(qc->dev->flags & ATA_DFLAG_CDB_INTR)) ||
		    (qc->tf.flags & ATA_TFLAG_POLLING))
			ata_sff_queue_pio_task(link, 0);
		अवरोध;

	शेष:
		वापस AC_ERR_SYSTEM;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_qc_issue);

/**
 *	ata_sff_qc_fill_rtf - fill result TF using ->sff_tf_पढ़ो
 *	@qc: qc to fill result TF क्रम
 *
 *	@qc is finished and result TF needs to be filled.  Fill it
 *	using ->sff_tf_पढ़ो.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	true indicating that result TF is successfully filled.
 */
bool ata_sff_qc_fill_rtf(काष्ठा ata_queued_cmd *qc)
अणु
	qc->ap->ops->sff_tf_पढ़ो(qc->ap, &qc->result_tf);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_qc_fill_rtf);

अटल अचिन्हित पूर्णांक ata_sff_idle_irq(काष्ठा ata_port *ap)
अणु
	ap->stats.idle_irq++;

#अगर_घोषित ATA_IRQ_TRAP
	अगर ((ap->stats.idle_irq % 1000) == 0) अणु
		ap->ops->sff_check_status(ap);
		अगर (ap->ops->sff_irq_clear)
			ap->ops->sff_irq_clear(ap);
		ata_port_warn(ap, "irq trap\n");
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;	/* irq not handled */
पूर्ण

अटल अचिन्हित पूर्णांक __ata_sff_port_पूर्णांकr(काष्ठा ata_port *ap,
					काष्ठा ata_queued_cmd *qc,
					bool hsmv_on_idle)
अणु
	u8 status;

	VPRINTK("ata%u: protocol %d task_state %d\n",
		ap->prपूर्णांक_id, qc->tf.protocol, ap->hsm_task_state);

	/* Check whether we are expecting पूर्णांकerrupt in this state */
	चयन (ap->hsm_task_state) अणु
	हाल HSM_ST_FIRST:
		/* Some pre-ATAPI-4 devices निश्चित INTRQ
		 * at this state when पढ़ोy to receive CDB.
		 */

		/* Check the ATA_DFLAG_CDB_INTR flag is enough here.
		 * The flag was turned on only क्रम atapi devices.  No
		 * need to check ata_is_atapi(qc->tf.protocol) again.
		 */
		अगर (!(qc->dev->flags & ATA_DFLAG_CDB_INTR))
			वापस ata_sff_idle_irq(ap);
		अवरोध;
	हाल HSM_ST_IDLE:
		वापस ata_sff_idle_irq(ap);
	शेष:
		अवरोध;
	पूर्ण

	/* check मुख्य status, clearing INTRQ अगर needed */
	status = ata_sff_irq_status(ap);
	अगर (status & ATA_BUSY) अणु
		अगर (hsmv_on_idle) अणु
			/* BMDMA engine is alपढ़ोy stopped, we're screwed */
			qc->err_mask |= AC_ERR_HSM;
			ap->hsm_task_state = HSM_ST_ERR;
		पूर्ण अन्यथा
			वापस ata_sff_idle_irq(ap);
	पूर्ण

	/* clear irq events */
	अगर (ap->ops->sff_irq_clear)
		ap->ops->sff_irq_clear(ap);

	ata_sff_hsm_move(ap, qc, status, 0);

	वापस 1;	/* irq handled */
पूर्ण

/**
 *	ata_sff_port_पूर्णांकr - Handle SFF port पूर्णांकerrupt
 *	@ap: Port on which पूर्णांकerrupt arrived (possibly...)
 *	@qc: Taskfile currently active in engine
 *
 *	Handle port पूर्णांकerrupt क्रम given queued command.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	One अगर पूर्णांकerrupt was handled, zero अगर not (shared irq).
 */
अचिन्हित पूर्णांक ata_sff_port_पूर्णांकr(काष्ठा ata_port *ap, काष्ठा ata_queued_cmd *qc)
अणु
	वापस __ata_sff_port_पूर्णांकr(ap, qc, false);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_port_पूर्णांकr);

अटल अंतरभूत irqवापस_t __ata_sff_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance,
	अचिन्हित पूर्णांक (*port_पूर्णांकr)(काष्ठा ata_port *, काष्ठा ata_queued_cmd *))
अणु
	काष्ठा ata_host *host = dev_instance;
	bool retried = false;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक handled, idle, polling;
	अचिन्हित दीर्घ flags;

	/* TODO: make _irqsave conditional on x86 PCI IDE legacy mode */
	spin_lock_irqsave(&host->lock, flags);

retry:
	handled = idle = polling = 0;
	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		काष्ठा ata_queued_cmd *qc;

		qc = ata_qc_from_tag(ap, ap->link.active_tag);
		अगर (qc) अणु
			अगर (!(qc->tf.flags & ATA_TFLAG_POLLING))
				handled |= port_पूर्णांकr(ap, qc);
			अन्यथा
				polling |= 1 << i;
		पूर्ण अन्यथा
			idle |= 1 << i;
	पूर्ण

	/*
	 * If no port was expecting IRQ but the controller is actually
	 * निश्चितing IRQ line, nobody cared will ensue.  Check IRQ
	 * pending status अगर available and clear spurious IRQ.
	 */
	अगर (!handled && !retried) अणु
		bool retry = false;

		क्रम (i = 0; i < host->n_ports; i++) अणु
			काष्ठा ata_port *ap = host->ports[i];

			अगर (polling & (1 << i))
				जारी;

			अगर (!ap->ops->sff_irq_check ||
			    !ap->ops->sff_irq_check(ap))
				जारी;

			अगर (idle & (1 << i)) अणु
				ap->ops->sff_check_status(ap);
				अगर (ap->ops->sff_irq_clear)
					ap->ops->sff_irq_clear(ap);
			पूर्ण अन्यथा अणु
				/* clear INTRQ and check अगर BUSY cleared */
				अगर (!(ap->ops->sff_check_status(ap) & ATA_BUSY))
					retry |= true;
				/*
				 * With command in flight, we can't करो
				 * sff_irq_clear() w/o racing with completion.
				 */
			पूर्ण
		पूर्ण

		अगर (retry) अणु
			retried = true;
			जाओ retry;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);

	वापस IRQ_RETVAL(handled);
पूर्ण

/**
 *	ata_sff_पूर्णांकerrupt - Default SFF ATA host पूर्णांकerrupt handler
 *	@irq: irq line (unused)
 *	@dev_instance: poपूर्णांकer to our ata_host inक्रमmation काष्ठाure
 *
 *	Default पूर्णांकerrupt handler क्रम PCI IDE devices.  Calls
 *	ata_sff_port_पूर्णांकr() क्रम each port that is not disabled.
 *
 *	LOCKING:
 *	Obtains host lock during operation.
 *
 *	RETURNS:
 *	IRQ_NONE or IRQ_HANDLED.
 */
irqवापस_t ata_sff_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	वापस __ata_sff_पूर्णांकerrupt(irq, dev_instance, ata_sff_port_पूर्णांकr);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_पूर्णांकerrupt);

/**
 *	ata_sff_lost_पूर्णांकerrupt	-	Check क्रम an apparent lost पूर्णांकerrupt
 *	@ap: port that appears to have समयd out
 *
 *	Called from the libata error handlers when the core code suspects
 *	an पूर्णांकerrupt has been lost. If it has complete anything we can and
 *	then वापस. Interface must support altstatus क्रम this faster
 *	recovery to occur.
 *
 *	Locking:
 *	Caller holds host lock
 */

व्योम ata_sff_lost_पूर्णांकerrupt(काष्ठा ata_port *ap)
अणु
	u8 status;
	काष्ठा ata_queued_cmd *qc;

	/* Only one outstanding command per SFF channel */
	qc = ata_qc_from_tag(ap, ap->link.active_tag);
	/* We cannot lose an पूर्णांकerrupt on a non-existent or polled command */
	अगर (!qc || qc->tf.flags & ATA_TFLAG_POLLING)
		वापस;
	/* See अगर the controller thinks it is still busy - अगर so the command
	   isn't a lost IRQ but is still in progress */
	status = ata_sff_altstatus(ap);
	अगर (status & ATA_BUSY)
		वापस;

	/* There was a command running, we are no दीर्घer busy and we have
	   no पूर्णांकerrupt. */
	ata_port_warn(ap, "lost interrupt (Status 0x%x)\n",
								status);
	/* Run the host पूर्णांकerrupt logic as अगर the पूर्णांकerrupt had not been
	   lost */
	ata_sff_port_पूर्णांकr(ap, qc);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_lost_पूर्णांकerrupt);

/**
 *	ata_sff_मुक्तze - Freeze SFF controller port
 *	@ap: port to मुक्तze
 *
 *	Freeze SFF controller port.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
व्योम ata_sff_मुक्तze(काष्ठा ata_port *ap)
अणु
	ap->ctl |= ATA_NIEN;
	ap->last_ctl = ap->ctl;

	अगर (ap->ops->sff_set_devctl || ap->ioaddr.ctl_addr)
		ata_sff_set_devctl(ap, ap->ctl);

	/* Under certain circumstances, some controllers उठाओ IRQ on
	 * ATA_NIEN manipulation.  Also, many controllers fail to mask
	 * previously pending IRQ on ATA_NIEN निश्चितion.  Clear it.
	 */
	ap->ops->sff_check_status(ap);

	अगर (ap->ops->sff_irq_clear)
		ap->ops->sff_irq_clear(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_मुक्तze);

/**
 *	ata_sff_thaw - Thaw SFF controller port
 *	@ap: port to thaw
 *
 *	Thaw SFF controller port.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
व्योम ata_sff_thaw(काष्ठा ata_port *ap)
अणु
	/* clear & re-enable पूर्णांकerrupts */
	ap->ops->sff_check_status(ap);
	अगर (ap->ops->sff_irq_clear)
		ap->ops->sff_irq_clear(ap);
	ata_sff_irq_on(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_thaw);

/**
 *	ata_sff_prereset - prepare SFF link क्रम reset
 *	@link: SFF link to be reset
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	SFF link @link is about to be reset.  Initialize it.  It first
 *	calls ata_std_prereset() and रुको क्रम !BSY अगर the port is
 *	being softreset.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_sff_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	पूर्णांक rc;

	rc = ata_std_prereset(link, deadline);
	अगर (rc)
		वापस rc;

	/* अगर we're about to करो hardreset, nothing more to करो */
	अगर (ehc->i.action & ATA_EH_HARDRESET)
		वापस 0;

	/* रुको क्रम !BSY अगर we करोn't know that no device is attached */
	अगर (!ata_link_offline(link)) अणु
		rc = ata_sff_रुको_पढ़ोy(link, deadline);
		अगर (rc && rc != -ENODEV) अणु
			ata_link_warn(link,
				      "device not ready (errno=%d), forcing hardreset\n",
				      rc);
			ehc->i.action |= ATA_EH_HARDRESET;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_prereset);

/**
 *	ata_devchk - PATA device presence detection
 *	@ap: ATA channel to examine
 *	@device: Device to examine (starting at zero)
 *
 *	This technique was originally described in
 *	Hale Landis's ATADRVR (www.ata-atapi.com), and
 *	later found its way पूर्णांकo the ATA/ATAPI spec.
 *
 *	Write a pattern to the ATA shaकरोw रेजिस्टरs,
 *	and अगर a device is present, it will respond by
 *	correctly storing and echoing back the
 *	ATA shaकरोw रेजिस्टर contents.
 *
 *	LOCKING:
 *	caller.
 */
अटल अचिन्हित पूर्णांक ata_devchk(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	u8 nsect, lbal;

	ap->ops->sff_dev_select(ap, device);

	ioग_लिखो8(0x55, ioaddr->nsect_addr);
	ioग_लिखो8(0xaa, ioaddr->lbal_addr);

	ioग_लिखो8(0xaa, ioaddr->nsect_addr);
	ioग_लिखो8(0x55, ioaddr->lbal_addr);

	ioग_लिखो8(0x55, ioaddr->nsect_addr);
	ioग_लिखो8(0xaa, ioaddr->lbal_addr);

	nsect = ioपढ़ो8(ioaddr->nsect_addr);
	lbal = ioपढ़ो8(ioaddr->lbal_addr);

	अगर ((nsect == 0x55) && (lbal == 0xaa))
		वापस 1;	/* we found a device */

	वापस 0;		/* nothing found */
पूर्ण

/**
 *	ata_sff_dev_classअगरy - Parse वापसed ATA device signature
 *	@dev: ATA device to classअगरy (starting at zero)
 *	@present: device seems present
 *	@r_err: Value of error रेजिस्टर on completion
 *
 *	After an event -- SRST, E.D.D., or SATA COMRESET -- occurs,
 *	an ATA/ATAPI-defined set of values is placed in the ATA
 *	shaकरोw रेजिस्टरs, indicating the results of device detection
 *	and diagnostics.
 *
 *	Select the ATA device, and पढ़ो the values from the ATA shaकरोw
 *	रेजिस्टरs.  Then parse according to the Error रेजिस्टर value,
 *	and the spec-defined values examined by ata_dev_classअगरy().
 *
 *	LOCKING:
 *	caller.
 *
 *	RETURNS:
 *	Device type - %ATA_DEV_ATA, %ATA_DEV_ATAPI or %ATA_DEV_NONE.
 */
अचिन्हित पूर्णांक ata_sff_dev_classअगरy(काष्ठा ata_device *dev, पूर्णांक present,
				  u8 *r_err)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	काष्ठा ata_taskfile tf;
	अचिन्हित पूर्णांक class;
	u8 err;

	ap->ops->sff_dev_select(ap, dev->devno);

	स_रखो(&tf, 0, माप(tf));

	ap->ops->sff_tf_पढ़ो(ap, &tf);
	err = tf.feature;
	अगर (r_err)
		*r_err = err;

	/* see अगर device passed diags: जारी and warn later */
	अगर (err == 0)
		/* diagnostic fail : करो nothing _YET_ */
		dev->horkage |= ATA_HORKAGE_DIAGNOSTIC;
	अन्यथा अगर (err == 1)
		/* करो nothing */ ;
	अन्यथा अगर ((dev->devno == 0) && (err == 0x81))
		/* करो nothing */ ;
	अन्यथा
		वापस ATA_DEV_NONE;

	/* determine अगर device is ATA or ATAPI */
	class = ata_dev_classअगरy(&tf);

	अगर (class == ATA_DEV_UNKNOWN) अणु
		/* If the device failed diagnostic, it's likely to
		 * have reported incorrect device signature too.
		 * Assume ATA device अगर the device seems present but
		 * device signature is invalid with diagnostic
		 * failure.
		 */
		अगर (present && (dev->horkage & ATA_HORKAGE_DIAGNOSTIC))
			class = ATA_DEV_ATA;
		अन्यथा
			class = ATA_DEV_NONE;
	पूर्ण अन्यथा अगर ((class == ATA_DEV_ATA) &&
		   (ap->ops->sff_check_status(ap) == 0))
		class = ATA_DEV_NONE;

	वापस class;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_dev_classअगरy);

/**
 *	ata_sff_रुको_after_reset - रुको क्रम devices to become पढ़ोy after reset
 *	@link: SFF link which is just reset
 *	@devmask: mask of present devices
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Wait devices attached to SFF @link to become पढ़ोy after
 *	reset.  It contains preceding 150ms रुको to aव्योम accessing TF
 *	status रेजिस्टर too early.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -ENODEV अगर some or all of devices in @devmask
 *	करोn't seem to exist.  -त्रुटि_सं on other errors.
 */
पूर्णांक ata_sff_रुको_after_reset(काष्ठा ata_link *link, अचिन्हित पूर्णांक devmask,
			     अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	अचिन्हित पूर्णांक dev0 = devmask & (1 << 0);
	अचिन्हित पूर्णांक dev1 = devmask & (1 << 1);
	पूर्णांक rc, ret = 0;

	ata_msleep(ap, ATA_WAIT_AFTER_RESET);

	/* always check पढ़ोiness of the master device */
	rc = ata_sff_रुको_पढ़ोy(link, deadline);
	/* -ENODEV means the odd clown क्रमgot the D7 pullकरोwn resistor
	 * and TF status is 0xff, bail out on it too.
	 */
	अगर (rc)
		वापस rc;

	/* अगर device 1 was found in ata_devchk, रुको क्रम रेजिस्टर
	 * access briefly, then रुको क्रम BSY to clear.
	 */
	अगर (dev1) अणु
		पूर्णांक i;

		ap->ops->sff_dev_select(ap, 1);

		/* Wait क्रम रेजिस्टर access.  Some ATAPI devices fail
		 * to set nsect/lbal after reset, so करोn't waste too
		 * much समय on it.  We're gonna रुको क्रम !BSY anyway.
		 */
		क्रम (i = 0; i < 2; i++) अणु
			u8 nsect, lbal;

			nsect = ioपढ़ो8(ioaddr->nsect_addr);
			lbal = ioपढ़ो8(ioaddr->lbal_addr);
			अगर ((nsect == 1) && (lbal == 1))
				अवरोध;
			ata_msleep(ap, 50);	/* give drive a breather */
		पूर्ण

		rc = ata_sff_रुको_पढ़ोy(link, deadline);
		अगर (rc) अणु
			अगर (rc != -ENODEV)
				वापस rc;
			ret = rc;
		पूर्ण
	पूर्ण

	/* is all this really necessary? */
	ap->ops->sff_dev_select(ap, 0);
	अगर (dev1)
		ap->ops->sff_dev_select(ap, 1);
	अगर (dev0)
		ap->ops->sff_dev_select(ap, 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_रुको_after_reset);

अटल पूर्णांक ata_bus_softreset(काष्ठा ata_port *ap, अचिन्हित पूर्णांक devmask,
			     अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

	DPRINTK("ata%u: bus reset via SRST\n", ap->prपूर्णांक_id);

	अगर (ap->ioaddr.ctl_addr) अणु
		/* software reset.  causes dev0 to be selected */
		ioग_लिखो8(ap->ctl, ioaddr->ctl_addr);
		udelay(20);	/* FIXME: flush */
		ioग_लिखो8(ap->ctl | ATA_SRST, ioaddr->ctl_addr);
		udelay(20);	/* FIXME: flush */
		ioग_लिखो8(ap->ctl, ioaddr->ctl_addr);
		ap->last_ctl = ap->ctl;
	पूर्ण

	/* रुको the port to become पढ़ोy */
	वापस ata_sff_रुको_after_reset(&ap->link, devmask, deadline);
पूर्ण

/**
 *	ata_sff_softreset - reset host port via ATA SRST
 *	@link: ATA link to reset
 *	@classes: resulting classes of attached devices
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Reset host port using ATA SRST.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_sff_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes,
		      अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	अचिन्हित पूर्णांक slave_possible = ap->flags & ATA_FLAG_SLAVE_POSS;
	अचिन्हित पूर्णांक devmask = 0;
	पूर्णांक rc;
	u8 err;

	DPRINTK("ENTER\n");

	/* determine अगर device 0/1 are present */
	अगर (ata_devchk(ap, 0))
		devmask |= (1 << 0);
	अगर (slave_possible && ata_devchk(ap, 1))
		devmask |= (1 << 1);

	/* select device 0 again */
	ap->ops->sff_dev_select(ap, 0);

	/* issue bus reset */
	DPRINTK("about to softreset, devmask=%x\n", devmask);
	rc = ata_bus_softreset(ap, devmask, deadline);
	/* अगर link is occupied, -ENODEV too is an error */
	अगर (rc && (rc != -ENODEV || sata_scr_valid(link))) अणु
		ata_link_err(link, "SRST failed (errno=%d)\n", rc);
		वापस rc;
	पूर्ण

	/* determine by signature whether we have ATA or ATAPI devices */
	classes[0] = ata_sff_dev_classअगरy(&link->device[0],
					  devmask & (1 << 0), &err);
	अगर (slave_possible && err != 0x81)
		classes[1] = ata_sff_dev_classअगरy(&link->device[1],
						  devmask & (1 << 1), &err);

	DPRINTK("EXIT, classes[0]=%u [1]=%u\n", classes[0], classes[1]);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_softreset);

/**
 *	sata_sff_hardreset - reset host port via SATA phy reset
 *	@link: link to reset
 *	@class: resulting class of attached device
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	SATA phy-reset host port using DET bits of SControl रेजिस्टर,
 *	रुको क्रम !BSY and classअगरy the attached device.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक sata_sff_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
		       अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	स्थिर अचिन्हित दीर्घ *timing = sata_ehc_deb_timing(ehc);
	bool online;
	पूर्णांक rc;

	rc = sata_link_hardreset(link, timing, deadline, &online,
				 ata_sff_check_पढ़ोy);
	अगर (online)
		*class = ata_sff_dev_classअगरy(link->device, 1, शून्य);

	DPRINTK("EXIT, class=%u\n", *class);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(sata_sff_hardreset);

/**
 *	ata_sff_postreset - SFF postreset callback
 *	@link: the target SFF ata_link
 *	@classes: classes of attached devices
 *
 *	This function is invoked after a successful reset.  It first
 *	calls ata_std_postreset() and perक्रमms SFF specअगरic postreset
 *	processing.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 */
व्योम ata_sff_postreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes)
अणु
	काष्ठा ata_port *ap = link->ap;

	ata_std_postreset(link, classes);

	/* is द्विगुन-select really necessary? */
	अगर (classes[0] != ATA_DEV_NONE)
		ap->ops->sff_dev_select(ap, 1);
	अगर (classes[1] != ATA_DEV_NONE)
		ap->ops->sff_dev_select(ap, 0);

	/* bail out अगर no device is present */
	अगर (classes[0] == ATA_DEV_NONE && classes[1] == ATA_DEV_NONE) अणु
		DPRINTK("EXIT, no device\n");
		वापस;
	पूर्ण

	/* set up device control */
	अगर (ap->ops->sff_set_devctl || ap->ioaddr.ctl_addr) अणु
		ata_sff_set_devctl(ap, ap->ctl);
		ap->last_ctl = ap->ctl;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_postreset);

/**
 *	ata_sff_drain_fअगरo - Stock FIFO drain logic क्रम SFF controllers
 *	@qc: command
 *
 *	Drain the FIFO and device of any stuck data following a command
 *	failing to complete. In some हालs this is necessary beक्रमe a
 *	reset will recover the device.
 *
 */

व्योम ata_sff_drain_fअगरo(काष्ठा ata_queued_cmd *qc)
अणु
	पूर्णांक count;
	काष्ठा ata_port *ap;

	/* We only need to flush incoming data when a command was running */
	अगर (qc == शून्य || qc->dma_dir == DMA_TO_DEVICE)
		वापस;

	ap = qc->ap;
	/* Drain up to 64K of data beक्रमe we give up this recovery method */
	क्रम (count = 0; (ap->ops->sff_check_status(ap) & ATA_DRQ)
						&& count < 65536; count += 2)
		ioपढ़ो16(ap->ioaddr.data_addr);

	/* Can become DEBUG later */
	अगर (count)
		ata_port_dbg(ap, "drained %d bytes to clear DRQ\n", count);

पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_drain_fअगरo);

/**
 *	ata_sff_error_handler - Stock error handler क्रम SFF controller
 *	@ap: port to handle error क्रम
 *
 *	Stock error handler क्रम SFF controller.  It can handle both
 *	PATA and SATA controllers.  Many controllers should be able to
 *	use this EH as-is or with some added handling beक्रमe and
 *	after.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 */
व्योम ata_sff_error_handler(काष्ठा ata_port *ap)
अणु
	ata_reset_fn_t softreset = ap->ops->softreset;
	ata_reset_fn_t hardreset = ap->ops->hardreset;
	काष्ठा ata_queued_cmd *qc;
	अचिन्हित दीर्घ flags;

	qc = __ata_qc_from_tag(ap, ap->link.active_tag);
	अगर (qc && !(qc->flags & ATA_QCFLAG_FAILED))
		qc = शून्य;

	spin_lock_irqsave(ap->lock, flags);

	/*
	 * We *MUST* करो FIFO draining beक्रमe we issue a reset as
	 * several devices helpfully clear their पूर्णांकernal state and
	 * will lock solid अगर we touch the data port post reset. Pass
	 * qc in हाल anyone wants to करो dअगरferent PIO/DMA recovery or
	 * has per command fixups
	 */
	अगर (ap->ops->sff_drain_fअगरo)
		ap->ops->sff_drain_fअगरo(qc);

	spin_unlock_irqrestore(ap->lock, flags);

	/* ignore built-in hardresets अगर SCR access is not available */
	अगर ((hardreset == sata_std_hardreset ||
	     hardreset == sata_sff_hardreset) && !sata_scr_valid(&ap->link))
		hardreset = शून्य;

	ata_करो_eh(ap, ap->ops->prereset, softreset, hardreset,
		  ap->ops->postreset);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_error_handler);

/**
 *	ata_sff_std_ports - initialize ioaddr with standard port offsets.
 *	@ioaddr: IO address काष्ठाure to be initialized
 *
 *	Utility function which initializes data_addr, error_addr,
 *	feature_addr, nsect_addr, lbal_addr, lbam_addr, lbah_addr,
 *	device_addr, status_addr, and command_addr to standard offsets
 *	relative to cmd_addr.
 *
 *	Does not set ctl_addr, altstatus_addr, bmdma_addr, or scr_addr.
 */
व्योम ata_sff_std_ports(काष्ठा ata_ioports *ioaddr)
अणु
	ioaddr->data_addr = ioaddr->cmd_addr + ATA_REG_DATA;
	ioaddr->error_addr = ioaddr->cmd_addr + ATA_REG_ERR;
	ioaddr->feature_addr = ioaddr->cmd_addr + ATA_REG_FEATURE;
	ioaddr->nsect_addr = ioaddr->cmd_addr + ATA_REG_NSECT;
	ioaddr->lbal_addr = ioaddr->cmd_addr + ATA_REG_LBAL;
	ioaddr->lbam_addr = ioaddr->cmd_addr + ATA_REG_LBAM;
	ioaddr->lbah_addr = ioaddr->cmd_addr + ATA_REG_LBAH;
	ioaddr->device_addr = ioaddr->cmd_addr + ATA_REG_DEVICE;
	ioaddr->status_addr = ioaddr->cmd_addr + ATA_REG_STATUS;
	ioaddr->command_addr = ioaddr->cmd_addr + ATA_REG_CMD;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sff_std_ports);

#अगर_घोषित CONFIG_PCI

अटल पूर्णांक ata_resources_present(काष्ठा pci_dev *pdev, पूर्णांक port)
अणु
	पूर्णांक i;

	/* Check the PCI resources क्रम this channel are enabled */
	port = port * 2;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (pci_resource_start(pdev, port + i) == 0 ||
		    pci_resource_len(pdev, port + i) == 0)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 *	ata_pci_sff_init_host - acquire native PCI ATA resources and init host
 *	@host: target ATA host
 *
 *	Acquire native PCI ATA resources क्रम @host and initialize the
 *	first two ports of @host accordingly.  Ports marked dummy are
 *	skipped and allocation failure makes the port dummy.
 *
 *	Note that native PCI resources are valid even क्रम legacy hosts
 *	as we fix up pdev resources array early in boot, so this
 *	function can be used क्रम both native and legacy SFF hosts.
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 *
 *	RETURNS:
 *	0 अगर at least one port is initialized, -ENODEV अगर no port is
 *	available.
 */
पूर्णांक ata_pci_sff_init_host(काष्ठा ata_host *host)
अणु
	काष्ठा device *gdev = host->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(gdev);
	अचिन्हित पूर्णांक mask = 0;
	पूर्णांक i, rc;

	/* request, iomap BARs and init port addresses accordingly */
	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		पूर्णांक base = i * 2;
		व्योम __iomem * स्थिर *iomap;

		अगर (ata_port_is_dummy(ap))
			जारी;

		/* Discard disabled ports.  Some controllers show
		 * their unused channels this way.  Disabled ports are
		 * made dummy.
		 */
		अगर (!ata_resources_present(pdev, i)) अणु
			ap->ops = &ata_dummy_port_ops;
			जारी;
		पूर्ण

		rc = pcim_iomap_regions(pdev, 0x3 << base,
					dev_driver_string(gdev));
		अगर (rc) अणु
			dev_warn(gdev,
				 "failed to request/iomap BARs for port %d (errno=%d)\n",
				 i, rc);
			अगर (rc == -EBUSY)
				pcim_pin_device(pdev);
			ap->ops = &ata_dummy_port_ops;
			जारी;
		पूर्ण
		host->iomap = iomap = pcim_iomap_table(pdev);

		ap->ioaddr.cmd_addr = iomap[base];
		ap->ioaddr.altstatus_addr =
		ap->ioaddr.ctl_addr = (व्योम __iomem *)
			((अचिन्हित दीर्घ)iomap[base + 1] | ATA_PCI_CTL_OFS);
		ata_sff_std_ports(&ap->ioaddr);

		ata_port_desc(ap, "cmd 0x%llx ctl 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, base),
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, base + 1));

		mask |= 1 << i;
	पूर्ण

	अगर (!mask) अणु
		dev_err(gdev, "no available native port\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_sff_init_host);

/**
 *	ata_pci_sff_prepare_host - helper to prepare PCI PIO-only SFF ATA host
 *	@pdev: target PCI device
 *	@ppi: array of port_info, must be enough क्रम two ports
 *	@r_host: out argument क्रम the initialized ATA host
 *
 *	Helper to allocate PIO-only SFF ATA host क्रम @pdev, acquire
 *	all PCI resources and initialize it accordingly in one go.
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_pci_sff_prepare_host(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा ata_port_info * स्थिर *ppi,
			     काष्ठा ata_host **r_host)
अणु
	काष्ठा ata_host *host;
	पूर्णांक rc;

	अगर (!devres_खोलो_group(&pdev->dev, शून्य, GFP_KERNEL))
		वापस -ENOMEM;

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, 2);
	अगर (!host) अणु
		dev_err(&pdev->dev, "failed to allocate ATA host\n");
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण

	rc = ata_pci_sff_init_host(host);
	अगर (rc)
		जाओ err_out;

	devres_हटाओ_group(&pdev->dev, शून्य);
	*r_host = host;
	वापस 0;

err_out:
	devres_release_group(&pdev->dev, शून्य);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_sff_prepare_host);

/**
 *	ata_pci_sff_activate_host - start SFF host, request IRQ and रेजिस्टर it
 *	@host: target SFF ATA host
 *	@irq_handler: irq_handler used when requesting IRQ(s)
 *	@sht: scsi_host_ढाँचा to use when रेजिस्टरing the host
 *
 *	This is the counterpart of ata_host_activate() क्रम SFF ATA
 *	hosts.  This separate helper is necessary because SFF hosts
 *	use two separate पूर्णांकerrupts in legacy mode.
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_pci_sff_activate_host(काष्ठा ata_host *host,
			      irq_handler_t irq_handler,
			      काष्ठा scsi_host_ढाँचा *sht)
अणु
	काष्ठा device *dev = host->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	स्थिर अक्षर *drv_name = dev_driver_string(host->dev);
	पूर्णांक legacy_mode = 0, rc;

	rc = ata_host_start(host);
	अगर (rc)
		वापस rc;

	अगर ((pdev->class >> 8) == PCI_CLASS_STORAGE_IDE) अणु
		u8 पंचांगp8, mask = 0;

		/*
		 * ATA spec says we should use legacy mode when one
		 * port is in legacy mode, but disabled ports on some
		 * PCI hosts appear as fixed legacy ports, e.g SB600/700
		 * on which the secondary port is not wired, so
		 * ignore ports that are marked as 'dummy' during
		 * this check
		 */
		pci_पढ़ो_config_byte(pdev, PCI_CLASS_PROG, &पंचांगp8);
		अगर (!ata_port_is_dummy(host->ports[0]))
			mask |= (1 << 0);
		अगर (!ata_port_is_dummy(host->ports[1]))
			mask |= (1 << 2);
		अगर ((पंचांगp8 & mask) != mask)
			legacy_mode = 1;
	पूर्ण

	अगर (!devres_खोलो_group(dev, शून्य, GFP_KERNEL))
		वापस -ENOMEM;

	अगर (!legacy_mode && pdev->irq) अणु
		पूर्णांक i;

		rc = devm_request_irq(dev, pdev->irq, irq_handler,
				      IRQF_SHARED, drv_name, host);
		अगर (rc)
			जाओ out;

		क्रम (i = 0; i < 2; i++) अणु
			अगर (ata_port_is_dummy(host->ports[i]))
				जारी;
			ata_port_desc(host->ports[i], "irq %d", pdev->irq);
		पूर्ण
	पूर्ण अन्यथा अगर (legacy_mode) अणु
		अगर (!ata_port_is_dummy(host->ports[0])) अणु
			rc = devm_request_irq(dev, ATA_PRIMARY_IRQ(pdev),
					      irq_handler, IRQF_SHARED,
					      drv_name, host);
			अगर (rc)
				जाओ out;

			ata_port_desc(host->ports[0], "irq %d",
				      ATA_PRIMARY_IRQ(pdev));
		पूर्ण

		अगर (!ata_port_is_dummy(host->ports[1])) अणु
			rc = devm_request_irq(dev, ATA_SECONDARY_IRQ(pdev),
					      irq_handler, IRQF_SHARED,
					      drv_name, host);
			अगर (rc)
				जाओ out;

			ata_port_desc(host->ports[1], "irq %d",
				      ATA_SECONDARY_IRQ(pdev));
		पूर्ण
	पूर्ण

	rc = ata_host_रेजिस्टर(host, sht);
out:
	अगर (rc == 0)
		devres_हटाओ_group(dev, शून्य);
	अन्यथा
		devres_release_group(dev, शून्य);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_sff_activate_host);

अटल स्थिर काष्ठा ata_port_info *ata_sff_find_valid_pi(
					स्थिर काष्ठा ata_port_info * स्थिर *ppi)
अणु
	पूर्णांक i;

	/* look up the first valid port_info */
	क्रम (i = 0; i < 2 && ppi[i]; i++)
		अगर (ppi[i]->port_ops != &ata_dummy_port_ops)
			वापस ppi[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक ata_pci_init_one(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा ata_port_info * स्थिर *ppi,
		काष्ठा scsi_host_ढाँचा *sht, व्योम *host_priv,
		पूर्णांक hflags, bool bmdma)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा ata_port_info *pi;
	काष्ठा ata_host *host = शून्य;
	पूर्णांक rc;

	DPRINTK("ENTER\n");

	pi = ata_sff_find_valid_pi(ppi);
	अगर (!pi) अणु
		dev_err(&pdev->dev, "no valid port_info specified\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!devres_खोलो_group(dev, शून्य, GFP_KERNEL))
		वापस -ENOMEM;

	rc = pcim_enable_device(pdev);
	अगर (rc)
		जाओ out;

#अगर_घोषित CONFIG_ATA_BMDMA
	अगर (bmdma)
		/* prepare and activate BMDMA host */
		rc = ata_pci_bmdma_prepare_host(pdev, ppi, &host);
	अन्यथा
#पूर्ण_अगर
		/* prepare and activate SFF host */
		rc = ata_pci_sff_prepare_host(pdev, ppi, &host);
	अगर (rc)
		जाओ out;
	host->निजी_data = host_priv;
	host->flags |= hflags;

#अगर_घोषित CONFIG_ATA_BMDMA
	अगर (bmdma) अणु
		pci_set_master(pdev);
		rc = ata_pci_sff_activate_host(host, ata_bmdma_पूर्णांकerrupt, sht);
	पूर्ण अन्यथा
#पूर्ण_अगर
		rc = ata_pci_sff_activate_host(host, ata_sff_पूर्णांकerrupt, sht);
out:
	अगर (rc == 0)
		devres_हटाओ_group(&pdev->dev, शून्य);
	अन्यथा
		devres_release_group(&pdev->dev, शून्य);

	वापस rc;
पूर्ण

/**
 *	ata_pci_sff_init_one - Initialize/रेजिस्टर PIO-only PCI IDE controller
 *	@pdev: Controller to be initialized
 *	@ppi: array of port_info, must be enough क्रम two ports
 *	@sht: scsi_host_ढाँचा to use when रेजिस्टरing the host
 *	@host_priv: host निजी_data
 *	@hflag: host flags
 *
 *	This is a helper function which can be called from a driver's
 *	xxx_init_one() probe function अगर the hardware uses traditional
 *	IDE taskfile रेजिस्टरs and is PIO only.
 *
 *	ASSUMPTION:
 *	Nobody makes a single channel controller that appears solely as
 *	the secondary legacy port on PCI.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, negative on त्रुटि_सं-based value on error.
 */
पूर्णांक ata_pci_sff_init_one(काष्ठा pci_dev *pdev,
		 स्थिर काष्ठा ata_port_info * स्थिर *ppi,
		 काष्ठा scsi_host_ढाँचा *sht, व्योम *host_priv, पूर्णांक hflag)
अणु
	वापस ata_pci_init_one(pdev, ppi, sht, host_priv, hflag, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_sff_init_one);

#पूर्ण_अगर /* CONFIG_PCI */

/*
 *	BMDMA support
 */

#अगर_घोषित CONFIG_ATA_BMDMA

स्थिर काष्ठा ata_port_operations ata_bmdma_port_ops = अणु
	.inherits		= &ata_sff_port_ops,

	.error_handler		= ata_bmdma_error_handler,
	.post_पूर्णांकernal_cmd	= ata_bmdma_post_पूर्णांकernal_cmd,

	.qc_prep		= ata_bmdma_qc_prep,
	.qc_issue		= ata_bmdma_qc_issue,

	.sff_irq_clear		= ata_bmdma_irq_clear,
	.bmdma_setup		= ata_bmdma_setup,
	.bmdma_start		= ata_bmdma_start,
	.bmdma_stop		= ata_bmdma_stop,
	.bmdma_status		= ata_bmdma_status,

	.port_start		= ata_bmdma_port_start,
पूर्ण;
EXPORT_SYMBOL_GPL(ata_bmdma_port_ops);

स्थिर काष्ठा ata_port_operations ata_bmdma32_port_ops = अणु
	.inherits		= &ata_bmdma_port_ops,

	.sff_data_xfer		= ata_sff_data_xfer32,
	.port_start		= ata_bmdma_port_start32,
पूर्ण;
EXPORT_SYMBOL_GPL(ata_bmdma32_port_ops);

/**
 *	ata_bmdma_fill_sg - Fill PCI IDE PRD table
 *	@qc: Metadata associated with taskfile to be transferred
 *
 *	Fill PCI IDE PRD (scatter-gather) table with segments
 *	associated with the current disk command.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 */
अटल व्योम ata_bmdma_fill_sg(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_bmdma_prd *prd = ap->bmdma_prd;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक si, pi;

	pi = 0;
	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		u32 addr, offset;
		u32 sg_len, len;

		/* determine अगर physical DMA addr spans 64K boundary.
		 * Note h/w करोesn't support 64-bit, so we unconditionally
		 * truncate dma_addr_t to u32.
		 */
		addr = (u32) sg_dma_address(sg);
		sg_len = sg_dma_len(sg);

		जबतक (sg_len) अणु
			offset = addr & 0xffff;
			len = sg_len;
			अगर ((offset + sg_len) > 0x10000)
				len = 0x10000 - offset;

			prd[pi].addr = cpu_to_le32(addr);
			prd[pi].flags_len = cpu_to_le32(len & 0xffff);
			VPRINTK("PRD[%u] = (0x%X, 0x%X)\n", pi, addr, len);

			pi++;
			sg_len -= len;
			addr += len;
		पूर्ण
	पूर्ण

	prd[pi - 1].flags_len |= cpu_to_le32(ATA_PRD_EOT);
पूर्ण

/**
 *	ata_bmdma_fill_sg_dumb - Fill PCI IDE PRD table
 *	@qc: Metadata associated with taskfile to be transferred
 *
 *	Fill PCI IDE PRD (scatter-gather) table with segments
 *	associated with the current disk command. Perक्रमm the fill
 *	so that we aव्योम writing any length 64K records क्रम
 *	controllers that करोn't follow the spec.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 */
अटल व्योम ata_bmdma_fill_sg_dumb(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_bmdma_prd *prd = ap->bmdma_prd;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक si, pi;

	pi = 0;
	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		u32 addr, offset;
		u32 sg_len, len, blen;

		/* determine अगर physical DMA addr spans 64K boundary.
		 * Note h/w करोesn't support 64-bit, so we unconditionally
		 * truncate dma_addr_t to u32.
		 */
		addr = (u32) sg_dma_address(sg);
		sg_len = sg_dma_len(sg);

		जबतक (sg_len) अणु
			offset = addr & 0xffff;
			len = sg_len;
			अगर ((offset + sg_len) > 0x10000)
				len = 0x10000 - offset;

			blen = len & 0xffff;
			prd[pi].addr = cpu_to_le32(addr);
			अगर (blen == 0) अणु
				/* Some PATA chipsets like the CS5530 can't
				   cope with 0x0000 meaning 64K as the spec
				   says */
				prd[pi].flags_len = cpu_to_le32(0x8000);
				blen = 0x8000;
				prd[++pi].addr = cpu_to_le32(addr + 0x8000);
			पूर्ण
			prd[pi].flags_len = cpu_to_le32(blen);
			VPRINTK("PRD[%u] = (0x%X, 0x%X)\n", pi, addr, len);

			pi++;
			sg_len -= len;
			addr += len;
		पूर्ण
	पूर्ण

	prd[pi - 1].flags_len |= cpu_to_le32(ATA_PRD_EOT);
पूर्ण

/**
 *	ata_bmdma_qc_prep - Prepare taskfile क्रम submission
 *	@qc: Metadata associated with taskfile to be prepared
 *
 *	Prepare ATA taskfile क्रम submission.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
क्रमागत ata_completion_errors ata_bmdma_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (!(qc->flags & ATA_QCFLAG_DMAMAP))
		वापस AC_ERR_OK;

	ata_bmdma_fill_sg(qc);

	वापस AC_ERR_OK;
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_qc_prep);

/**
 *	ata_bmdma_dumb_qc_prep - Prepare taskfile क्रम submission
 *	@qc: Metadata associated with taskfile to be prepared
 *
 *	Prepare ATA taskfile क्रम submission.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
क्रमागत ata_completion_errors ata_bmdma_dumb_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (!(qc->flags & ATA_QCFLAG_DMAMAP))
		वापस AC_ERR_OK;

	ata_bmdma_fill_sg_dumb(qc);

	वापस AC_ERR_OK;
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_dumb_qc_prep);

/**
 *	ata_bmdma_qc_issue - issue taskfile to a BMDMA controller
 *	@qc: command to issue to device
 *
 *	This function issues a PIO, NODATA or DMA command to a
 *	SFF/BMDMA controller.  PIO and NODATA are handled by
 *	ata_sff_qc_issue().
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Zero on success, AC_ERR_* mask on failure
 */
अचिन्हित पूर्णांक ata_bmdma_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_link *link = qc->dev->link;

	/* defer PIO handling to sff_qc_issue */
	अगर (!ata_is_dma(qc->tf.protocol))
		वापस ata_sff_qc_issue(qc);

	/* select the device */
	ata_dev_select(ap, qc->dev->devno, 1, 0);

	/* start the command */
	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_DMA:
		WARN_ON_ONCE(qc->tf.flags & ATA_TFLAG_POLLING);

		ap->ops->sff_tf_load(ap, &qc->tf);  /* load tf रेजिस्टरs */
		ap->ops->bmdma_setup(qc);	    /* set up bmdma */
		ap->ops->bmdma_start(qc);	    /* initiate bmdma */
		ap->hsm_task_state = HSM_ST_LAST;
		अवरोध;

	हाल ATAPI_PROT_DMA:
		WARN_ON_ONCE(qc->tf.flags & ATA_TFLAG_POLLING);

		ap->ops->sff_tf_load(ap, &qc->tf);  /* load tf रेजिस्टरs */
		ap->ops->bmdma_setup(qc);	    /* set up bmdma */
		ap->hsm_task_state = HSM_ST_FIRST;

		/* send cdb by polling अगर no cdb पूर्णांकerrupt */
		अगर (!(qc->dev->flags & ATA_DFLAG_CDB_INTR))
			ata_sff_queue_pio_task(link, 0);
		अवरोध;

	शेष:
		WARN_ON(1);
		वापस AC_ERR_SYSTEM;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_qc_issue);

/**
 *	ata_bmdma_port_पूर्णांकr - Handle BMDMA port पूर्णांकerrupt
 *	@ap: Port on which पूर्णांकerrupt arrived (possibly...)
 *	@qc: Taskfile currently active in engine
 *
 *	Handle port पूर्णांकerrupt क्रम given queued command.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	One अगर पूर्णांकerrupt was handled, zero अगर not (shared irq).
 */
अचिन्हित पूर्णांक ata_bmdma_port_पूर्णांकr(काष्ठा ata_port *ap, काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	u8 host_stat = 0;
	bool bmdma_stopped = false;
	अचिन्हित पूर्णांक handled;

	अगर (ap->hsm_task_state == HSM_ST_LAST && ata_is_dma(qc->tf.protocol)) अणु
		/* check status of DMA engine */
		host_stat = ap->ops->bmdma_status(ap);
		VPRINTK("ata%u: host_stat 0x%X\n", ap->prपूर्णांक_id, host_stat);

		/* अगर it's not our irq... */
		अगर (!(host_stat & ATA_DMA_INTR))
			वापस ata_sff_idle_irq(ap);

		/* beक्रमe we करो anything अन्यथा, clear DMA-Start bit */
		ap->ops->bmdma_stop(qc);
		bmdma_stopped = true;

		अगर (unlikely(host_stat & ATA_DMA_ERR)) अणु
			/* error when transferring data to/from memory */
			qc->err_mask |= AC_ERR_HOST_BUS;
			ap->hsm_task_state = HSM_ST_ERR;
		पूर्ण
	पूर्ण

	handled = __ata_sff_port_पूर्णांकr(ap, qc, bmdma_stopped);

	अगर (unlikely(qc->err_mask) && ata_is_dma(qc->tf.protocol))
		ata_ehi_push_desc(ehi, "BMDMA stat 0x%x", host_stat);

	वापस handled;
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_port_पूर्णांकr);

/**
 *	ata_bmdma_पूर्णांकerrupt - Default BMDMA ATA host पूर्णांकerrupt handler
 *	@irq: irq line (unused)
 *	@dev_instance: poपूर्णांकer to our ata_host inक्रमmation काष्ठाure
 *
 *	Default पूर्णांकerrupt handler क्रम PCI IDE devices.  Calls
 *	ata_bmdma_port_पूर्णांकr() क्रम each port that is not disabled.
 *
 *	LOCKING:
 *	Obtains host lock during operation.
 *
 *	RETURNS:
 *	IRQ_NONE or IRQ_HANDLED.
 */
irqवापस_t ata_bmdma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	वापस __ata_sff_पूर्णांकerrupt(irq, dev_instance, ata_bmdma_port_पूर्णांकr);
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_पूर्णांकerrupt);

/**
 *	ata_bmdma_error_handler - Stock error handler क्रम BMDMA controller
 *	@ap: port to handle error क्रम
 *
 *	Stock error handler क्रम BMDMA controller.  It can handle both
 *	PATA and SATA controllers.  Most BMDMA controllers should be
 *	able to use this EH as-is or with some added handling beक्रमe
 *	and after.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 */
व्योम ata_bmdma_error_handler(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_queued_cmd *qc;
	अचिन्हित दीर्घ flags;
	bool thaw = false;

	qc = __ata_qc_from_tag(ap, ap->link.active_tag);
	अगर (qc && !(qc->flags & ATA_QCFLAG_FAILED))
		qc = शून्य;

	/* reset PIO HSM and stop DMA engine */
	spin_lock_irqsave(ap->lock, flags);

	अगर (qc && ata_is_dma(qc->tf.protocol)) अणु
		u8 host_stat;

		host_stat = ap->ops->bmdma_status(ap);

		/* BMDMA controllers indicate host bus error by
		 * setting DMA_ERR bit and timing out.  As it wasn't
		 * really a समयout event, adjust error mask and
		 * cancel frozen state.
		 */
		अगर (qc->err_mask == AC_ERR_TIMEOUT && (host_stat & ATA_DMA_ERR)) अणु
			qc->err_mask = AC_ERR_HOST_BUS;
			thaw = true;
		पूर्ण

		ap->ops->bmdma_stop(qc);

		/* अगर we're gonna thaw, make sure IRQ is clear */
		अगर (thaw) अणु
			ap->ops->sff_check_status(ap);
			अगर (ap->ops->sff_irq_clear)
				ap->ops->sff_irq_clear(ap);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(ap->lock, flags);

	अगर (thaw)
		ata_eh_thaw_port(ap);

	ata_sff_error_handler(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_error_handler);

/**
 *	ata_bmdma_post_पूर्णांकernal_cmd - Stock post_पूर्णांकernal_cmd क्रम BMDMA
 *	@qc: पूर्णांकernal command to clean up
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 */
व्योम ata_bmdma_post_पूर्णांकernal_cmd(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	अचिन्हित दीर्घ flags;

	अगर (ata_is_dma(qc->tf.protocol)) अणु
		spin_lock_irqsave(ap->lock, flags);
		ap->ops->bmdma_stop(qc);
		spin_unlock_irqrestore(ap->lock, flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_post_पूर्णांकernal_cmd);

/**
 *	ata_bmdma_irq_clear - Clear PCI IDE BMDMA पूर्णांकerrupt.
 *	@ap: Port associated with this ATA transaction.
 *
 *	Clear पूर्णांकerrupt and error flags in DMA status रेजिस्टर.
 *
 *	May be used as the irq_clear() entry in ata_port_operations.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_bmdma_irq_clear(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio = ap->ioaddr.bmdma_addr;

	अगर (!mmio)
		वापस;

	ioग_लिखो8(ioपढ़ो8(mmio + ATA_DMA_STATUS), mmio + ATA_DMA_STATUS);
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_irq_clear);

/**
 *	ata_bmdma_setup - Set up PCI IDE BMDMA transaction
 *	@qc: Info associated with this ATA transaction.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_bmdma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	अचिन्हित पूर्णांक rw = (qc->tf.flags & ATA_TFLAG_WRITE);
	u8 dmactl;

	/* load PRD table addr. */
	mb();	/* make sure PRD table ग_लिखोs are visible to controller */
	ioग_लिखो32(ap->bmdma_prd_dma, ap->ioaddr.bmdma_addr + ATA_DMA_TABLE_OFS);

	/* specअगरy data direction, triple-check start bit is clear */
	dmactl = ioपढ़ो8(ap->ioaddr.bmdma_addr + ATA_DMA_CMD);
	dmactl &= ~(ATA_DMA_WR | ATA_DMA_START);
	अगर (!rw)
		dmactl |= ATA_DMA_WR;
	ioग_लिखो8(dmactl, ap->ioaddr.bmdma_addr + ATA_DMA_CMD);

	/* issue r/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_setup);

/**
 *	ata_bmdma_start - Start a PCI IDE BMDMA transaction
 *	@qc: Info associated with this ATA transaction.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	u8 dmactl;

	/* start host DMA transaction */
	dmactl = ioपढ़ो8(ap->ioaddr.bmdma_addr + ATA_DMA_CMD);
	ioग_लिखो8(dmactl | ATA_DMA_START, ap->ioaddr.bmdma_addr + ATA_DMA_CMD);

	/* Strictly, one may wish to issue an ioपढ़ो8() here, to
	 * flush the mmio ग_लिखो.  However, control also passes
	 * to the hardware at this poपूर्णांक, and it will पूर्णांकerrupt
	 * us when we are to resume control.  So, in effect,
	 * we करोn't care when the mmio ग_लिखो flushes.
	 * Further, a पढ़ो of the DMA status रेजिस्टर _immediately_
	 * following the ग_लिखो may not be what certain flaky hardware
	 * is expected, so I think it is best to not add a पढ़ोb()
	 * without first all the MMIO ATA cards/mobos.
	 * Or maybe I'm just being paranoid.
	 *
	 * FIXME: The posting of this ग_लिखो means I/O starts are
	 * unnecessarily delayed क्रम MMIO
	 */
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_start);

/**
 *	ata_bmdma_stop - Stop PCI IDE BMDMA transfer
 *	@qc: Command we are ending DMA क्रम
 *
 *	Clears the ATA_DMA_START flag in the dma control रेजिस्टर
 *
 *	May be used as the bmdma_stop() entry in ata_port_operations.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	व्योम __iomem *mmio = ap->ioaddr.bmdma_addr;

	/* clear start/stop bit */
	ioग_लिखो8(ioपढ़ो8(mmio + ATA_DMA_CMD) & ~ATA_DMA_START,
		 mmio + ATA_DMA_CMD);

	/* one-PIO-cycle guaranteed रुको, per spec, क्रम HDMA1:0 transition */
	ata_sff_dma_छोड़ो(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_stop);

/**
 *	ata_bmdma_status - Read PCI IDE BMDMA status
 *	@ap: Port associated with this ATA transaction.
 *
 *	Read and वापस BMDMA status रेजिस्टर.
 *
 *	May be used as the bmdma_status() entry in ata_port_operations.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
u8 ata_bmdma_status(काष्ठा ata_port *ap)
अणु
	वापस ioपढ़ो8(ap->ioaddr.bmdma_addr + ATA_DMA_STATUS);
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_status);


/**
 *	ata_bmdma_port_start - Set port up क्रम bmdma.
 *	@ap: Port to initialize
 *
 *	Called just after data काष्ठाures क्रम each port are
 *	initialized.  Allocates space क्रम PRD table.
 *
 *	May be used as the port_start() entry in ata_port_operations.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
पूर्णांक ata_bmdma_port_start(काष्ठा ata_port *ap)
अणु
	अगर (ap->mwdma_mask || ap->udma_mask) अणु
		ap->bmdma_prd =
			dmam_alloc_coherent(ap->host->dev, ATA_PRD_TBL_SZ,
					    &ap->bmdma_prd_dma, GFP_KERNEL);
		अगर (!ap->bmdma_prd)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_port_start);

/**
 *	ata_bmdma_port_start32 - Set port up क्रम dma.
 *	@ap: Port to initialize
 *
 *	Called just after data काष्ठाures क्रम each port are
 *	initialized.  Enables 32bit PIO and allocates space क्रम PRD
 *	table.
 *
 *	May be used as the port_start() entry in ata_port_operations क्रम
 *	devices that are capable of 32bit PIO.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
पूर्णांक ata_bmdma_port_start32(काष्ठा ata_port *ap)
अणु
	ap->pflags |= ATA_PFLAG_PIO32 | ATA_PFLAG_PIO32CHANGE;
	वापस ata_bmdma_port_start(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_bmdma_port_start32);

#अगर_घोषित CONFIG_PCI

/**
 *	ata_pci_bmdma_clear_simplex -	attempt to kick device out of simplex
 *	@pdev: PCI device
 *
 *	Some PCI ATA devices report simplex mode but in fact can be told to
 *	enter non simplex mode. This implements the necessary logic to
 *	perक्रमm the task on such devices. Calling it on other devices will
 *	have -undefined- behaviour.
 */
पूर्णांक ata_pci_bmdma_clear_simplex(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ bmdma = pci_resource_start(pdev, 4);
	u8 simplex;

	अगर (bmdma == 0)
		वापस -ENOENT;

	simplex = inb(bmdma + 0x02);
	outb(simplex & 0x60, bmdma + 0x02);
	simplex = inb(bmdma + 0x02);
	अगर (simplex & 0x80)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_bmdma_clear_simplex);

अटल व्योम ata_bmdma_nodma(काष्ठा ata_host *host, स्थिर अक्षर *reason)
अणु
	पूर्णांक i;

	dev_err(host->dev, "BMDMA: %s, falling back to PIO\n", reason);

	क्रम (i = 0; i < 2; i++) अणु
		host->ports[i]->mwdma_mask = 0;
		host->ports[i]->udma_mask = 0;
	पूर्ण
पूर्ण

/**
 *	ata_pci_bmdma_init - acquire PCI BMDMA resources and init ATA host
 *	@host: target ATA host
 *
 *	Acquire PCI BMDMA resources and initialize @host accordingly.
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 */
व्योम ata_pci_bmdma_init(काष्ठा ata_host *host)
अणु
	काष्ठा device *gdev = host->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(gdev);
	पूर्णांक i, rc;

	/* No BAR4 allocation: No DMA */
	अगर (pci_resource_start(pdev, 4) == 0) अणु
		ata_bmdma_nodma(host, "BAR4 is zero");
		वापस;
	पूर्ण

	/*
	 * Some controllers require BMDMA region to be initialized
	 * even अगर DMA is not in use to clear IRQ status via
	 * ->sff_irq_clear method.  Try to initialize bmdma_addr
	 * regardless of dma masks.
	 */
	rc = dma_set_mask_and_coherent(&pdev->dev, ATA_DMA_MASK);
	अगर (rc)
		ata_bmdma_nodma(host, "failed to set dma mask");

	/* request and iomap DMA region */
	rc = pcim_iomap_regions(pdev, 1 << 4, dev_driver_string(gdev));
	अगर (rc) अणु
		ata_bmdma_nodma(host, "failed to request/iomap BAR4");
		वापस;
	पूर्ण
	host->iomap = pcim_iomap_table(pdev);

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		व्योम __iomem *bmdma = host->iomap[4] + 8 * i;

		अगर (ata_port_is_dummy(ap))
			जारी;

		ap->ioaddr.bmdma_addr = bmdma;
		अगर ((!(ap->flags & ATA_FLAG_IGN_SIMPLEX)) &&
		    (ioपढ़ो8(bmdma + 2) & 0x80))
			host->flags |= ATA_HOST_SIMPLEX;

		ata_port_desc(ap, "bmdma 0x%llx",
		    (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 4) + 8 * i);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_bmdma_init);

/**
 *	ata_pci_bmdma_prepare_host - helper to prepare PCI BMDMA ATA host
 *	@pdev: target PCI device
 *	@ppi: array of port_info, must be enough क्रम two ports
 *	@r_host: out argument क्रम the initialized ATA host
 *
 *	Helper to allocate BMDMA ATA host क्रम @pdev, acquire all PCI
 *	resources and initialize it accordingly in one go.
 *
 *	LOCKING:
 *	Inherited from calling layer (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_pci_bmdma_prepare_host(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा ata_port_info * स्थिर * ppi,
			       काष्ठा ata_host **r_host)
अणु
	पूर्णांक rc;

	rc = ata_pci_sff_prepare_host(pdev, ppi, r_host);
	अगर (rc)
		वापस rc;

	ata_pci_bmdma_init(*r_host);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_bmdma_prepare_host);

/**
 *	ata_pci_bmdma_init_one - Initialize/रेजिस्टर BMDMA PCI IDE controller
 *	@pdev: Controller to be initialized
 *	@ppi: array of port_info, must be enough क्रम two ports
 *	@sht: scsi_host_ढाँचा to use when रेजिस्टरing the host
 *	@host_priv: host निजी_data
 *	@hflags: host flags
 *
 *	This function is similar to ata_pci_sff_init_one() but also
 *	takes care of BMDMA initialization.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, negative on त्रुटि_सं-based value on error.
 */
पूर्णांक ata_pci_bmdma_init_one(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा ata_port_info * स्थिर * ppi,
			   काष्ठा scsi_host_ढाँचा *sht, व्योम *host_priv,
			   पूर्णांक hflags)
अणु
	वापस ata_pci_init_one(pdev, ppi, sht, host_priv, hflags, 1);
पूर्ण
EXPORT_SYMBOL_GPL(ata_pci_bmdma_init_one);

#पूर्ण_अगर /* CONFIG_PCI */
#पूर्ण_अगर /* CONFIG_ATA_BMDMA */

/**
 *	ata_sff_port_init - Initialize SFF/BMDMA ATA port
 *	@ap: Port to initialize
 *
 *	Called on port allocation to initialize SFF/BMDMA specअगरic
 *	fields.
 *
 *	LOCKING:
 *	None.
 */
व्योम ata_sff_port_init(काष्ठा ata_port *ap)
अणु
	INIT_DELAYED_WORK(&ap->sff_pio_task, ata_sff_pio_task);
	ap->ctl = ATA_DEVCTL_OBS;
	ap->last_ctl = 0xFF;
पूर्ण

पूर्णांक __init ata_sff_init(व्योम)
अणु
	ata_sff_wq = alloc_workqueue("ata_sff", WQ_MEM_RECLAIM, WQ_MAX_ACTIVE);
	अगर (!ata_sff_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम ata_sff_निकास(व्योम)
अणु
	destroy_workqueue(ata_sff_wq);
पूर्ण
