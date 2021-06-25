<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Future Doमुख्य TMC-16x0 and TMC-3260 SCSI host adapters
 * Copyright 2019 Ondrej Zary
 *
 * Original driver by
 * Rickard E. Faith, faith@cs.unc.edu
 *
 * Future Doमुख्य BIOS versions supported क्रम स्वतःdetect:
 *    2.0, 3.0, 3.2, 3.4 (1.0), 3.5 (2.0), 3.6, 3.61
 * Chips supported:
 *    TMC-1800, TMC-18C50, TMC-18C30, TMC-36C70
 * Boards supported:
 *    Future Doमुख्य TMC-1650, TMC-1660, TMC-1670, TMC-1680, TMC-1610M/MER/MEX
 *    Future Doमुख्य TMC-3260 (PCI)
 *    Quantum ISA-200S, ISA-250MG
 *    Adaptec AHA-2920A (PCI) [BUT *NOT* AHA-2920C -- use aic7xxx instead]
 *    IBM ?
 *
 * NOTE:
 *
 * The Adaptec AHA-2920C has an Adaptec AIC-7850 chip on it.
 * Use the aic7xxx driver क्रम this board.
 *
 * The Adaptec AHA-2920A has a Future Doमुख्य chip on it, so this is the right
 * driver क्रम that card.  Unक्रमtunately, the boxes will probably just say
 * "2920", so you'll have to look on the card क्रम a Future Doमुख्य logo, or a
 * letter after the 2920.
 *
 * If you have a TMC-8xx or TMC-9xx board, then this is not the driver क्रम
 * your board.
 *
 * DESCRIPTION:
 *
 * This is the Linux low-level SCSI driver क्रम Future Doमुख्य TMC-1660/1680
 * TMC-1650/1670, and TMC-3260 SCSI host adapters.  The 1650 and 1670 have a
 * 25-pin बाह्यal connector, whereas the 1660 and 1680 have a SCSI-2 50-pin
 * high-density बाह्यal connector.  The 1670 and 1680 have floppy disk
 * controllers built in.  The TMC-3260 is a PCI bus card.
 *
 * Future Doमुख्य's older boards are based on the TMC-1800 chip, and this
 * driver was originally written क्रम a TMC-1680 board with the TMC-1800 chip.
 * More recently, boards are being produced with the TMC-18C50 and TMC-18C30
 * chips.
 *
 * Please note that the drive ordering that Future Doमुख्य implemented in BIOS
 * versions 3.4 and 3.5 is the opposite of the order (currently) used by the
 * rest of the SCSI industry.
 *
 *
 * REFERENCES USED:
 *
 * "TMC-1800 SCSI Chip Specification (FDC-1800T)", Future Doमुख्य Corporation,
 * 1990.
 *
 * "Technical Reference Manual: 18C50 SCSI Host Adapter Chip", Future Doमुख्य
 * Corporation, January 1992.
 *
 * "LXT SCSI Products: Specअगरications and OEM Technical Manual (Revision
 * B/September 1991)", Maxtor Corporation, 1991.
 *
 * "7213S product Manual (Revision P3)", Maxtor Corporation, 1992.
 *
 * "Draft Proposed American National Standard: Small Computer System
 * Interface - 2 (SCSI-2)", Global Engineering Documents. (X3T9.2/86-109,
 * revision 10h, October 17, 1991)
 *
 * Private communications, Drew Eckhardt (drew@cs.coloraकरो.edu) and Eric
 * Youngdale (ericy@cais.com), 1992.
 *
 * Private communication, Tuong Le (Future Doमुख्य Engineering deparपंचांगent),
 * 1994. (Disk geometry computations क्रम Future Doमुख्य BIOS version 3.4, and
 * TMC-18C30 detection.)
 *
 * Hogan, Thom. The Programmer's PC Sourcebook. Microsoft Press, 1988. Page
 * 60 (2.39: Disk Partition Table Layout).
 *
 * "18C30 Technical Reference Manual", Future Doमुख्य Corporation, 1993, page
 * 6-1.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/workqueue.h>
#समावेश <scsi/scsicam.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश "fdomain.h"

/*
 * FIFO_COUNT: The host adapter has an 8K cache (host adapters based on the
 * 18C30 chip have a 2k cache).  When this many 512 byte blocks are filled by
 * the SCSI device, an पूर्णांकerrupt will be उठाओd.  Thereक्रमe, this could be as
 * low as 0, or as high as 16.  Note, however, that values which are too high
 * or too low seem to prevent any पूर्णांकerrupts from occurring, and thereby lock
 * up the machine.
 */
#घोषणा FIFO_COUNT	2	/* Number of 512 byte blocks beक्रमe INTR */
#घोषणा PARITY_MASK	ACTL_PAREN	/* Parity enabled, 0 = disabled */

क्रमागत chip_type अणु
	unknown		= 0x00,
	पंचांगc1800		= 0x01,
	पंचांगc18c50	= 0x02,
	पंचांगc18c30	= 0x03,
पूर्ण;

काष्ठा fकरोमुख्य अणु
	पूर्णांक base;
	काष्ठा scsi_cmnd *cur_cmd;
	क्रमागत chip_type chip;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल अंतरभूत व्योम fकरोमुख्य_make_bus_idle(काष्ठा fकरोमुख्य *fd)
अणु
	outb(0, fd->base + REG_BCTL);
	outb(0, fd->base + REG_MCTL);
	अगर (fd->chip == पंचांगc18c50 || fd->chip == पंचांगc18c30)
		/* Clear क्रमced पूर्णांकr. */
		outb(ACTL_RESET | ACTL_CLRFIRQ | PARITY_MASK,
		     fd->base + REG_ACTL);
	अन्यथा
		outb(ACTL_RESET | PARITY_MASK, fd->base + REG_ACTL);
पूर्ण

अटल क्रमागत chip_type fकरोमुख्य_identअगरy(पूर्णांक port)
अणु
	u16 id = inb(port + REG_ID_LSB) | inb(port + REG_ID_MSB) << 8;

	चयन (id) अणु
	हाल 0x6127:
		वापस पंचांगc1800;
	हाल 0x60e9: /* 18c50 or 18c30 */
		अवरोध;
	शेष:
		वापस unknown;
	पूर्ण

	/* Try to toggle 32-bit mode. This only works on an 18c30 chip. */
	outb(CFG2_32BIT, port + REG_CFG2);
	अगर ((inb(port + REG_CFG2) & CFG2_32BIT)) अणु
		outb(0, port + REG_CFG2);
		अगर ((inb(port + REG_CFG2) & CFG2_32BIT) == 0)
			वापस पंचांगc18c30;
	पूर्ण
	/* If that failed, we are an 18c50. */
	वापस पंचांगc18c50;
पूर्ण

अटल पूर्णांक fकरोमुख्य_test_loopback(पूर्णांक base)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 255; i++) अणु
		outb(i, base + REG_LOOPBACK);
		अगर (inb(base + REG_LOOPBACK) != i)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fकरोमुख्य_reset(पूर्णांक base)
अणु
	outb(BCTL_RST, base + REG_BCTL);
	mdelay(20);
	outb(0, base + REG_BCTL);
	mdelay(1150);
	outb(0, base + REG_MCTL);
	outb(PARITY_MASK, base + REG_ACTL);
पूर्ण

अटल पूर्णांक fकरोमुख्य_select(काष्ठा Scsi_Host *sh, पूर्णांक target)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ समयout;
	काष्ठा fकरोमुख्य *fd = shost_priv(sh);

	outb(BCTL_BUSEN | BCTL_SEL, fd->base + REG_BCTL);
	outb(BIT(sh->this_id) | BIT(target), fd->base + REG_SCSI_DATA_NOACK);

	/* Stop arbitration and enable parity */
	outb(PARITY_MASK, fd->base + REG_ACTL);

	समयout = 350;	/* 350 msec */

	करो अणु
		status = inb(fd->base + REG_BSTAT);
		अगर (status & BSTAT_BSY) अणु
			/* Enable SCSI Bus */
			/* (on error, should make bus idle with 0) */
			outb(BCTL_BUSEN, fd->base + REG_BCTL);
			वापस 0;
		पूर्ण
		mdelay(1);
	पूर्ण जबतक (--समयout);
	fकरोमुख्य_make_bus_idle(fd);
	वापस 1;
पूर्ण

अटल व्योम fकरोमुख्य_finish_cmd(काष्ठा fकरोमुख्य *fd, पूर्णांक result)
अणु
	outb(0, fd->base + REG_ICTL);
	fकरोमुख्य_make_bus_idle(fd);
	fd->cur_cmd->result = result;
	fd->cur_cmd->scsi_करोne(fd->cur_cmd);
	fd->cur_cmd = शून्य;
पूर्ण

अटल व्योम fकरोमुख्य_पढ़ो_data(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा fकरोमुख्य *fd = shost_priv(cmd->device->host);
	अचिन्हित अक्षर *virt, *ptr;
	माप_प्रकार offset, len;

	जबतक ((len = inw(fd->base + REG_FIFO_COUNT)) > 0) अणु
		offset = scsi_bufflen(cmd) - scsi_get_resid(cmd);
		virt = scsi_kmap_atomic_sg(scsi_sglist(cmd), scsi_sg_count(cmd),
					   &offset, &len);
		ptr = virt + offset;
		अगर (len & 1)
			*ptr++ = inb(fd->base + REG_FIFO);
		अगर (len > 1)
			insw(fd->base + REG_FIFO, ptr, len >> 1);
		scsi_set_resid(cmd, scsi_get_resid(cmd) - len);
		scsi_kunmap_atomic_sg(virt);
	पूर्ण
पूर्ण

अटल व्योम fकरोमुख्य_ग_लिखो_data(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा fकरोमुख्य *fd = shost_priv(cmd->device->host);
	/* 8k FIFO क्रम pre-पंचांगc18c30 chips, 2k FIFO क्रम पंचांगc18c30 */
	पूर्णांक FIFO_Size = fd->chip == पंचांगc18c30 ? 0x800 : 0x2000;
	अचिन्हित अक्षर *virt, *ptr;
	माप_प्रकार offset, len;

	जबतक ((len = FIFO_Size - inw(fd->base + REG_FIFO_COUNT)) > 512) अणु
		offset = scsi_bufflen(cmd) - scsi_get_resid(cmd);
		अगर (len + offset > scsi_bufflen(cmd)) अणु
			len = scsi_bufflen(cmd) - offset;
			अगर (len == 0)
				अवरोध;
		पूर्ण
		virt = scsi_kmap_atomic_sg(scsi_sglist(cmd), scsi_sg_count(cmd),
					   &offset, &len);
		ptr = virt + offset;
		अगर (len & 1)
			outb(*ptr++, fd->base + REG_FIFO);
		अगर (len > 1)
			outsw(fd->base + REG_FIFO, ptr, len >> 1);
		scsi_set_resid(cmd, scsi_get_resid(cmd) - len);
		scsi_kunmap_atomic_sg(virt);
	पूर्ण
पूर्ण

अटल व्योम fकरोमुख्य_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fकरोमुख्य *fd = container_of(work, काष्ठा fकरोमुख्य, work);
	काष्ठा Scsi_Host *sh = container_of((व्योम *)fd, काष्ठा Scsi_Host,
					    hostdata);
	काष्ठा scsi_cmnd *cmd = fd->cur_cmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक status;
	पूर्णांक करोne = 0;

	spin_lock_irqsave(sh->host_lock, flags);

	अगर (cmd->SCp.phase & in_arbitration) अणु
		status = inb(fd->base + REG_ASTAT);
		अगर (!(status & ASTAT_ARB)) अणु
			fकरोमुख्य_finish_cmd(fd, DID_BUS_BUSY << 16);
			जाओ out;
		पूर्ण
		cmd->SCp.phase = in_selection;

		outb(ICTL_SEL | FIFO_COUNT, fd->base + REG_ICTL);
		outb(BCTL_BUSEN | BCTL_SEL, fd->base + REG_BCTL);
		outb(BIT(cmd->device->host->this_id) | BIT(scmd_id(cmd)),
		     fd->base + REG_SCSI_DATA_NOACK);
		/* Stop arbitration and enable parity */
		outb(ACTL_IRQEN | PARITY_MASK, fd->base + REG_ACTL);
		जाओ out;
	पूर्ण अन्यथा अगर (cmd->SCp.phase & in_selection) अणु
		status = inb(fd->base + REG_BSTAT);
		अगर (!(status & BSTAT_BSY)) अणु
			/* Try again, क्रम slow devices */
			अगर (fकरोमुख्य_select(cmd->device->host, scmd_id(cmd))) अणु
				fकरोमुख्य_finish_cmd(fd, DID_NO_CONNECT << 16);
				जाओ out;
			पूर्ण
			/* Stop arbitration and enable parity */
			outb(ACTL_IRQEN | PARITY_MASK, fd->base + REG_ACTL);
		पूर्ण
		cmd->SCp.phase = in_other;
		outb(ICTL_FIFO | ICTL_REQ | FIFO_COUNT, fd->base + REG_ICTL);
		outb(BCTL_BUSEN, fd->base + REG_BCTL);
		जाओ out;
	पूर्ण

	/* cur_cmd->SCp.phase == in_other: this is the body of the routine */
	status = inb(fd->base + REG_BSTAT);

	अगर (status & BSTAT_REQ) अणु
		चयन (status & (BSTAT_MSG | BSTAT_CMD | BSTAT_IO)) अणु
		हाल BSTAT_CMD:	/* COMMAND OUT */
			outb(cmd->cmnd[cmd->SCp.sent_command++],
			     fd->base + REG_SCSI_DATA);
			अवरोध;
		हाल 0:	/* DATA OUT -- पंचांगc18c50/पंचांगc18c30 only */
			अगर (fd->chip != पंचांगc1800 && !cmd->SCp.have_data_in) अणु
				cmd->SCp.have_data_in = -1;
				outb(ACTL_IRQEN | ACTL_FIFOWR | ACTL_FIFOEN |
				     PARITY_MASK, fd->base + REG_ACTL);
			पूर्ण
			अवरोध;
		हाल BSTAT_IO:	/* DATA IN -- पंचांगc18c50/पंचांगc18c30 only */
			अगर (fd->chip != पंचांगc1800 && !cmd->SCp.have_data_in) अणु
				cmd->SCp.have_data_in = 1;
				outb(ACTL_IRQEN | ACTL_FIFOEN | PARITY_MASK,
				     fd->base + REG_ACTL);
			पूर्ण
			अवरोध;
		हाल BSTAT_CMD | BSTAT_IO:	/* STATUS IN */
			cmd->SCp.Status = inb(fd->base + REG_SCSI_DATA);
			अवरोध;
		हाल BSTAT_MSG | BSTAT_CMD:	/* MESSAGE OUT */
			outb(MESSAGE_REJECT, fd->base + REG_SCSI_DATA);
			अवरोध;
		हाल BSTAT_MSG | BSTAT_CMD | BSTAT_IO:	/* MESSAGE IN */
			cmd->SCp.Message = inb(fd->base + REG_SCSI_DATA);
			अगर (!cmd->SCp.Message)
				++करोne;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fd->chip == पंचांगc1800 && !cmd->SCp.have_data_in &&
	    cmd->SCp.sent_command >= cmd->cmd_len) अणु
		अगर (cmd->sc_data_direction == DMA_TO_DEVICE) अणु
			cmd->SCp.have_data_in = -1;
			outb(ACTL_IRQEN | ACTL_FIFOWR | ACTL_FIFOEN |
			     PARITY_MASK, fd->base + REG_ACTL);
		पूर्ण अन्यथा अणु
			cmd->SCp.have_data_in = 1;
			outb(ACTL_IRQEN | ACTL_FIFOEN | PARITY_MASK,
			     fd->base + REG_ACTL);
		पूर्ण
	पूर्ण

	अगर (cmd->SCp.have_data_in == -1) /* DATA OUT */
		fकरोमुख्य_ग_लिखो_data(cmd);

	अगर (cmd->SCp.have_data_in == 1) /* DATA IN */
		fकरोमुख्य_पढ़ो_data(cmd);

	अगर (करोne) अणु
		fकरोमुख्य_finish_cmd(fd, (cmd->SCp.Status & 0xff) |
				   ((cmd->SCp.Message & 0xff) << 8) |
				   (DID_OK << 16));
	पूर्ण अन्यथा अणु
		अगर (cmd->SCp.phase & disconnect) अणु
			outb(ICTL_FIFO | ICTL_SEL | ICTL_REQ | FIFO_COUNT,
			     fd->base + REG_ICTL);
			outb(0, fd->base + REG_BCTL);
		पूर्ण अन्यथा
			outb(ICTL_FIFO | ICTL_REQ | FIFO_COUNT,
			     fd->base + REG_ICTL);
	पूर्ण
out:
	spin_unlock_irqrestore(sh->host_lock, flags);
पूर्ण

अटल irqवापस_t fकरोमुख्य_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fकरोमुख्य *fd = dev_id;

	/* Is it our IRQ? */
	अगर ((inb(fd->base + REG_ASTAT) & ASTAT_IRQ) == 0)
		वापस IRQ_NONE;

	outb(0, fd->base + REG_ICTL);

	/* We usually have one spurious पूर्णांकerrupt after each command. */
	अगर (!fd->cur_cmd)	/* Spurious पूर्णांकerrupt */
		वापस IRQ_NONE;

	schedule_work(&fd->work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fकरोमुख्य_queue(काष्ठा Scsi_Host *sh, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा fकरोमुख्य *fd = shost_priv(cmd->device->host);
	अचिन्हित दीर्घ flags;

	cmd->SCp.Status		= 0;
	cmd->SCp.Message	= 0;
	cmd->SCp.have_data_in	= 0;
	cmd->SCp.sent_command	= 0;
	cmd->SCp.phase		= in_arbitration;
	scsi_set_resid(cmd, scsi_bufflen(cmd));

	spin_lock_irqsave(sh->host_lock, flags);

	fd->cur_cmd = cmd;

	fकरोमुख्य_make_bus_idle(fd);

	/* Start arbitration */
	outb(0, fd->base + REG_ICTL);
	outb(0, fd->base + REG_BCTL);	/* Disable data drivers */
	/* Set our id bit */
	outb(BIT(cmd->device->host->this_id), fd->base + REG_SCSI_DATA_NOACK);
	outb(ICTL_ARB, fd->base + REG_ICTL);
	/* Start arbitration */
	outb(ACTL_ARB | ACTL_IRQEN | PARITY_MASK, fd->base + REG_ACTL);

	spin_unlock_irqrestore(sh->host_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक fकरोमुख्य_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *sh = cmd->device->host;
	काष्ठा fकरोमुख्य *fd = shost_priv(sh);
	अचिन्हित दीर्घ flags;

	अगर (!fd->cur_cmd)
		वापस FAILED;

	spin_lock_irqsave(sh->host_lock, flags);

	fकरोमुख्य_make_bus_idle(fd);
	fd->cur_cmd->SCp.phase |= पातed;
	fd->cur_cmd->result = DID_ABORT << 16;

	/* Aborts are not करोne well. . . */
	fकरोमुख्य_finish_cmd(fd, DID_ABORT << 16);
	spin_unlock_irqrestore(sh->host_lock, flags);
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक fकरोमुख्य_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *sh = cmd->device->host;
	काष्ठा fकरोमुख्य *fd = shost_priv(sh);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(sh->host_lock, flags);
	fकरोमुख्य_reset(fd->base);
	spin_unlock_irqrestore(sh->host_lock, flags);
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक fकरोमुख्य_biosparam(काष्ठा scsi_device *sdev,
			     काष्ठा block_device *bdev,	sector_t capacity,
			     पूर्णांक geom[])
अणु
	अचिन्हित अक्षर *p = scsi_bios_ptable(bdev);

	अगर (p && p[65] == 0xaa && p[64] == 0x55 /* Partition table valid */
	    && p[4]) अणु	 /* Partition type */
		geom[0] = p[5] + 1;	/* heads */
		geom[1] = p[6] & 0x3f;	/* sectors */
	पूर्ण अन्यथा अणु
		अगर (capacity >= 0x7e0000) अणु
			geom[0] = 255;	/* heads */
			geom[1] = 63;	/* sectors */
		पूर्ण अन्यथा अगर (capacity >= 0x200000) अणु
			geom[0] = 128;	/* heads */
			geom[1] = 63;	/* sectors */
		पूर्ण अन्यथा अणु
			geom[0] = 64;	/* heads */
			geom[1] = 32;	/* sectors */
		पूर्ण
	पूर्ण
	geom[2] = sector_भाग(capacity, geom[0] * geom[1]);
	kमुक्त(p);

	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा fकरोमुख्य_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "Future Domain TMC-16x0",
	.proc_name		= "fdomain",
	.queuecommand		= fकरोमुख्य_queue,
	.eh_पात_handler	= fकरोमुख्य_पात,
	.eh_host_reset_handler	= fकरोमुख्य_host_reset,
	.bios_param		= fकरोमुख्य_biosparam,
	.can_queue		= 1,
	.this_id		= 7,
	.sg_tablesize		= 64,
	.dma_boundary		= PAGE_SIZE - 1,
पूर्ण;

काष्ठा Scsi_Host *fकरोमुख्य_create(पूर्णांक base, पूर्णांक irq, पूर्णांक this_id,
				 काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *sh;
	काष्ठा fकरोमुख्य *fd;
	क्रमागत chip_type chip;
	अटल स्थिर अक्षर * स्थिर chip_names[] = अणु
		"Unknown", "TMC-1800", "TMC-18C50", "TMC-18C30"
	पूर्ण;
	अचिन्हित दीर्घ irq_flags = 0;

	chip = fकरोमुख्य_identअगरy(base);
	अगर (!chip)
		वापस शून्य;

	fकरोमुख्य_reset(base);

	अगर (fकरोमुख्य_test_loopback(base))
		वापस शून्य;

	अगर (!irq) अणु
		dev_err(dev, "card has no IRQ assigned");
		वापस शून्य;
	पूर्ण

	sh = scsi_host_alloc(&fकरोमुख्य_ढाँचा, माप(काष्ठा fकरोमुख्य));
	अगर (!sh)
		वापस शून्य;

	अगर (this_id)
		sh->this_id = this_id & 0x07;

	sh->irq = irq;
	sh->io_port = base;
	sh->n_io_port = FDOMAIN_REGION_SIZE;

	fd = shost_priv(sh);
	fd->base = base;
	fd->chip = chip;
	INIT_WORK(&fd->work, fकरोमुख्य_work);

	अगर (dev_is_pci(dev) || !म_भेद(dev->bus->name, "pcmcia"))
		irq_flags = IRQF_SHARED;

	अगर (request_irq(irq, fकरोमुख्य_irq, irq_flags, "fdomain", fd))
		जाओ fail_put;

	shost_prपूर्णांकk(KERN_INFO, sh, "%s chip at 0x%x irq %d SCSI ID %d\n",
		     dev_is_pci(dev) ? "TMC-36C70 (PCI bus)" : chip_names[chip],
		     base, irq, sh->this_id);

	अगर (scsi_add_host(sh, dev))
		जाओ fail_मुक्त_irq;

	scsi_scan_host(sh);

	वापस sh;

fail_मुक्त_irq:
	मुक्त_irq(irq, fd);
fail_put:
	scsi_host_put(sh);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fकरोमुख्य_create);

पूर्णांक fकरोमुख्य_destroy(काष्ठा Scsi_Host *sh)
अणु
	काष्ठा fकरोमुख्य *fd = shost_priv(sh);

	cancel_work_sync(&fd->work);
	scsi_हटाओ_host(sh);
	अगर (sh->irq)
		मुक्त_irq(sh->irq, fd);
	scsi_host_put(sh);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fकरोमुख्य_destroy);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक fकरोमुख्य_resume(काष्ठा device *dev)
अणु
	काष्ठा fकरोमुख्य *fd = shost_priv(dev_get_drvdata(dev));

	fकरोमुख्य_reset(fd->base);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(fकरोमुख्य_pm_ops, शून्य, fकरोमुख्य_resume);
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

MODULE_AUTHOR("Ondrej Zary, Rickard E. Faith");
MODULE_DESCRIPTION("Future Domain TMC-16x0/TMC-3260 SCSI driver");
MODULE_LICENSE("GPL");
