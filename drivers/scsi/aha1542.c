<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम Adaptec AHA-1542 SCSI host adapters
 *
 *  Copyright (C) 1992  Tommy Thorn
 *  Copyright (C) 1993, 1994, 1995 Eric Youngdale
 *  Copyright (C) 2015 Ondrej Zary
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/isa.h>
#समावेश <linux/pnp.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश "aha1542.h"

#घोषणा MAXBOARDS 4

अटल bool isapnp = 1;
module_param(isapnp, bool, 0);
MODULE_PARM_DESC(isapnp, "enable PnP support (default=1)");

अटल पूर्णांक io[MAXBOARDS] = अणु 0x330, 0x334, 0, 0 पूर्ण;
module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(io, "base IO address of controller (0x130,0x134,0x230,0x234,0x330,0x334, default=0x330,0x334)");

/* समय AHA spends on the AT-bus during data transfer */
अटल पूर्णांक bus_on[MAXBOARDS] = अणु -1, -1, -1, -1 पूर्ण; /* घातer-on शेष: 11us */
module_param_array(bus_on, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(bus_on, "bus on time [us] (2-15, default=-1 [HW default: 11])");

/* समय AHA spends off the bus (not to monopolize it) during data transfer  */
अटल पूर्णांक bus_off[MAXBOARDS] = अणु -1, -1, -1, -1 पूर्ण; /* घातer-on शेष: 4us */
module_param_array(bus_off, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(bus_off, "bus off time [us] (1-64, default=-1 [HW default: 4])");

/* शेष is jumper selected (J1 on 1542A), factory शेष = 5 MB/s */
अटल पूर्णांक dma_speed[MAXBOARDS] = अणु -1, -1, -1, -1 पूर्ण;
module_param_array(dma_speed, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(dma_speed, "DMA speed [MB/s] (5,6,7,8,10, default=-1 [by jumper])");

#घोषणा BIOS_TRANSLATION_6432 1	/* Default हाल these days */
#घोषणा BIOS_TRANSLATION_25563 2	/* Big disk हाल */

काष्ठा aha1542_hostdata अणु
	/* This will effectively start both of them at the first mailbox */
	पूर्णांक bios_translation;	/* Mapping bios uses - क्रम compatibility */
	पूर्णांक aha1542_last_mbi_used;
	पूर्णांक aha1542_last_mbo_used;
	काष्ठा scsi_cmnd *पूर्णांक_cmds[AHA1542_MAILBOXES];
	काष्ठा mailbox *mb;
	dma_addr_t mb_handle;
	काष्ठा ccb *ccb;
	dma_addr_t ccb_handle;
पूर्ण;

#घोषणा AHA1542_MAX_SECTORS       16

काष्ठा aha1542_cmd अणु
	/* bounce buffer */
	व्योम *data_buffer;
	dma_addr_t data_buffer_handle;
पूर्ण;

अटल अंतरभूत व्योम aha1542_पूर्णांकr_reset(u16 base)
अणु
	outb(IRST, CONTROL(base));
पूर्ण

अटल अंतरभूत bool रुको_mask(u16 port, u8 mask, u8 allof, u8 noneof, पूर्णांक समयout)
अणु
	bool delayed = true;

	अगर (समयout == 0) अणु
		समयout = 3000000;
		delayed = false;
	पूर्ण

	जबतक (1) अणु
		u8 bits = inb(port) & mask;
		अगर ((bits & allof) == allof && ((bits & noneof) == 0))
			अवरोध;
		अगर (delayed)
			mdelay(1);
		अगर (--समयout == 0)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक aha1542_outb(अचिन्हित पूर्णांक base, u8 val)
अणु
	अगर (!रुको_mask(STATUS(base), CDF, 0, CDF, 0))
		वापस 1;
	outb(val, DATA(base));

	वापस 0;
पूर्ण

अटल पूर्णांक aha1542_out(अचिन्हित पूर्णांक base, u8 *buf, पूर्णांक len)
अणु
	जबतक (len--) अणु
		अगर (!रुको_mask(STATUS(base), CDF, 0, CDF, 0))
			वापस 1;
		outb(*buf++, DATA(base));
	पूर्ण
	अगर (!रुको_mask(INTRFLAGS(base), INTRMASK, HACC, 0, 0))
		वापस 1;

	वापस 0;
पूर्ण

/*
 * Only used at boot समय, so we करो not need to worry about latency as much
 * here
 */

अटल पूर्णांक aha1542_in(अचिन्हित पूर्णांक base, u8 *buf, पूर्णांक len, पूर्णांक समयout)
अणु
	जबतक (len--) अणु
		अगर (!रुको_mask(STATUS(base), DF, DF, 0, समयout))
			वापस 1;
		*buf++ = inb(DATA(base));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक makecode(अचिन्हित hosterr, अचिन्हित scsierr)
अणु
	चयन (hosterr) अणु
	हाल 0x0:
	हाल 0xa:		/* Linked command complete without error and linked normally */
	हाल 0xb:		/* Linked command complete without error, पूर्णांकerrupt generated */
		hosterr = 0;
		अवरोध;

	हाल 0x11:		/* Selection समय out-The initiator selection or target
				 * reselection was not complete within the SCSI Time out period
				 */
		hosterr = DID_TIME_OUT;
		अवरोध;

	हाल 0x12:		/* Data overrun/underrun-The target attempted to transfer more data
				 * than was allocated by the Data Length field or the sum of the
				 * Scatter / Gather Data Length fields.
				 */

	हाल 0x13:		/* Unexpected bus मुक्त-The target dropped the SCSI BSY at an unexpected समय. */

	हाल 0x15:		/* MBO command was not 00, 01 or 02-The first byte of the CB was
				 * invalid. This usually indicates a software failure.
				 */

	हाल 0x16:		/* Invalid CCB Operation Code-The first byte of the CCB was invalid.
				 * This usually indicates a software failure.
				 */

	हाल 0x17:		/* Linked CCB करोes not have the same LUN-A subsequent CCB of a set
				 * of linked CCB's करोes not specअगरy the same logical unit number as
				 * the first.
				 */
	हाल 0x18:		/* Invalid Target Direction received from Host-The direction of a
				 * Target Mode CCB was invalid.
				 */

	हाल 0x19:		/* Duplicate CCB Received in Target Mode-More than once CCB was
				 * received to service data transfer between the same target LUN
				 * and initiator SCSI ID in the same direction.
				 */

	हाल 0x1a:		/* Invalid CCB or Segment List Parameter-A segment list with a zero
				 * length segment or invalid segment list boundaries was received.
				 * A CCB parameter was invalid.
				 */
#अगर_घोषित DEBUG
		prपूर्णांकk("Aha1542: %x %x\n", hosterr, scsierr);
#पूर्ण_अगर
		hosterr = DID_ERROR;	/* Couldn't find any better */
		अवरोध;

	हाल 0x14:		/* Target bus phase sequence failure-An invalid bus phase or bus
				 * phase sequence was requested by the target. The host adapter
				 * will generate a SCSI Reset Condition, notअगरying the host with
				 * a SCRD पूर्णांकerrupt
				 */
		hosterr = DID_RESET;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "aha1542: makecode: unknown hoststatus %x\n", hosterr);
		अवरोध;
	पूर्ण
	वापस scsierr | (hosterr << 16);
पूर्ण

अटल पूर्णांक aha1542_test_port(काष्ठा Scsi_Host *sh)
अणु
	u8 inquiry_result[4];
	पूर्णांक i;

	/* Quick and dirty test क्रम presence of the card. */
	अगर (inb(STATUS(sh->io_port)) == 0xff)
		वापस 0;

	/* Reset the adapter. I ought to make a hard reset, but it's not really necessary */

	/* In हाल some other card was probing here, reset पूर्णांकerrupts */
	aha1542_पूर्णांकr_reset(sh->io_port);	/* reset पूर्णांकerrupts, so they करोn't block */

	outb(SRST | IRST /*|SCRST */ , CONTROL(sh->io_port));

	mdelay(20);		/* Wait a little bit क्रम things to settle करोwn. */

	/* Expect INIT and IDLE, any of the others are bad */
	अगर (!रुको_mask(STATUS(sh->io_port), STATMASK, INIT | IDLE, STST | DIAGF | INVDCMD | DF | CDF, 0))
		वापस 0;

	/* Shouldn't have generated any पूर्णांकerrupts during reset */
	अगर (inb(INTRFLAGS(sh->io_port)) & INTRMASK)
		वापस 0;

	/*
	 * Perक्रमm a host adapter inquiry instead so we करो not need to set
	 * up the mailboxes ahead of समय
	 */

	aha1542_outb(sh->io_port, CMD_INQUIRY);

	क्रम (i = 0; i < 4; i++) अणु
		अगर (!रुको_mask(STATUS(sh->io_port), DF, DF, 0, 0))
			वापस 0;
		inquiry_result[i] = inb(DATA(sh->io_port));
	पूर्ण

	/* Reading port should reset DF */
	अगर (inb(STATUS(sh->io_port)) & DF)
		वापस 0;

	/* When HACC, command is completed, and we're though testing */
	अगर (!रुको_mask(INTRFLAGS(sh->io_port), HACC, HACC, 0, 0))
		वापस 0;

	/* Clear पूर्णांकerrupts */
	outb(IRST, CONTROL(sh->io_port));

	वापस 1;
पूर्ण

अटल व्योम aha1542_मुक्त_cmd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा aha1542_cmd *acmd = scsi_cmd_priv(cmd);

	अगर (cmd->sc_data_direction == DMA_FROM_DEVICE) अणु
		व्योम *buf = acmd->data_buffer;
		काष्ठा req_iterator iter;
		काष्ठा bio_vec bv;

		rq_क्रम_each_segment(bv, cmd->request, iter) अणु
			स_नकल_to_page(bv.bv_page, bv.bv_offset, buf,
				       bv.bv_len);
			buf += bv.bv_len;
		पूर्ण
	पूर्ण

	scsi_dma_unmap(cmd);
पूर्ण

अटल irqवापस_t aha1542_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा Scsi_Host *sh = dev_id;
	काष्ठा aha1542_hostdata *aha1542 = shost_priv(sh);
	व्योम (*my_करोne)(काष्ठा scsi_cmnd *) = शून्य;
	पूर्णांक errstatus, mbi, mbo, mbistatus;
	पूर्णांक number_serviced;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_cmnd *पंचांगp_cmd;
	पूर्णांक flag;
	काष्ठा mailbox *mb = aha1542->mb;
	काष्ठा ccb *ccb = aha1542->ccb;

#अगर_घोषित DEBUG
	अणु
		flag = inb(INTRFLAGS(sh->io_port));
		shost_prपूर्णांकk(KERN_DEBUG, sh, "aha1542_intr_handle: ");
		अगर (!(flag & ANYINTR))
			prपूर्णांकk("no interrupt?");
		अगर (flag & MBIF)
			prपूर्णांकk("MBIF ");
		अगर (flag & MBOA)
			prपूर्णांकk("MBOF ");
		अगर (flag & HACC)
			prपूर्णांकk("HACC ");
		अगर (flag & SCRD)
			prपूर्णांकk("SCRD ");
		prपूर्णांकk("status %02x\n", inb(STATUS(sh->io_port)));
	पूर्ण;
#पूर्ण_अगर
	number_serviced = 0;

	spin_lock_irqsave(sh->host_lock, flags);
	जबतक (1) अणु
		flag = inb(INTRFLAGS(sh->io_port));

		/*
		 * Check क्रम unusual पूर्णांकerrupts.  If any of these happen, we should
		 * probably करो something special, but क्रम now just prपूर्णांकing a message
		 * is sufficient.  A SCSI reset detected is something that we really
		 * need to deal with in some way.
		 */
		अगर (flag & ~MBIF) अणु
			अगर (flag & MBOA)
				prपूर्णांकk("MBOF ");
			अगर (flag & HACC)
				prपूर्णांकk("HACC ");
			अगर (flag & SCRD)
				prपूर्णांकk("SCRD ");
		पूर्ण
		aha1542_पूर्णांकr_reset(sh->io_port);

		mbi = aha1542->aha1542_last_mbi_used + 1;
		अगर (mbi >= 2 * AHA1542_MAILBOXES)
			mbi = AHA1542_MAILBOXES;

		करो अणु
			अगर (mb[mbi].status != 0)
				अवरोध;
			mbi++;
			अगर (mbi >= 2 * AHA1542_MAILBOXES)
				mbi = AHA1542_MAILBOXES;
		पूर्ण जबतक (mbi != aha1542->aha1542_last_mbi_used);

		अगर (mb[mbi].status == 0) अणु
			spin_unlock_irqrestore(sh->host_lock, flags);
			/* Hmm, no mail.  Must have पढ़ो it the last समय around */
			अगर (!number_serviced)
				shost_prपूर्णांकk(KERN_WARNING, sh, "interrupt received, but no mail.\n");
			वापस IRQ_HANDLED;
		पूर्ण;

		mbo = (scsi2पूर्णांक(mb[mbi].ccbptr) - (अचिन्हित दीर्घ)aha1542->ccb_handle) / माप(काष्ठा ccb);
		mbistatus = mb[mbi].status;
		mb[mbi].status = 0;
		aha1542->aha1542_last_mbi_used = mbi;

#अगर_घोषित DEBUG
		अगर (ccb[mbo].tarstat | ccb[mbo].hastat)
			shost_prपूर्णांकk(KERN_DEBUG, sh, "aha1542_command: returning %x (status %d)\n",
			       ccb[mbo].tarstat + ((पूर्णांक) ccb[mbo].hastat << 16), mb[mbi].status);
#पूर्ण_अगर

		अगर (mbistatus == 3)
			जारी;	/* Aborted command not found */

#अगर_घोषित DEBUG
		shost_prपूर्णांकk(KERN_DEBUG, sh, "...done %d %d\n", mbo, mbi);
#पूर्ण_अगर

		पंचांगp_cmd = aha1542->पूर्णांक_cmds[mbo];

		अगर (!पंचांगp_cmd || !पंचांगp_cmd->scsi_करोne) अणु
			spin_unlock_irqrestore(sh->host_lock, flags);
			shost_prपूर्णांकk(KERN_WARNING, sh, "Unexpected interrupt\n");
			shost_prपूर्णांकk(KERN_WARNING, sh, "tarstat=%x, hastat=%x idlun=%x ccb#=%d\n", ccb[mbo].tarstat,
			       ccb[mbo].hastat, ccb[mbo].idlun, mbo);
			वापस IRQ_HANDLED;
		पूर्ण
		my_करोne = पंचांगp_cmd->scsi_करोne;
		aha1542_मुक्त_cmd(पंचांगp_cmd);
		/*
		 * Fetch the sense data, and tuck it away, in the required slot.  The
		 * Adaptec स्वतःmatically fetches it, and there is no guarantee that
		 * we will still have it in the cdb when we come back
		 */
		अगर (ccb[mbo].tarstat == 2)
			स_नकल(पंचांगp_cmd->sense_buffer, &ccb[mbo].cdb[ccb[mbo].cdblen],
			       SCSI_SENSE_BUFFERSIZE);


		/* is there mail :-) */

		/* more error checking left out here */
		अगर (mbistatus != 1)
			/* This is surely wrong, but I करोn't know what's right */
			errstatus = makecode(ccb[mbo].hastat, ccb[mbo].tarstat);
		अन्यथा
			errstatus = 0;

#अगर_घोषित DEBUG
		अगर (errstatus)
			shost_prपूर्णांकk(KERN_DEBUG, sh, "(aha1542 error:%x %x %x) ", errstatus,
			       ccb[mbo].hastat, ccb[mbo].tarstat);
		अगर (ccb[mbo].tarstat == 2)
			prपूर्णांक_hex_dump_bytes("sense: ", DUMP_PREFIX_NONE, &ccb[mbo].cdb[ccb[mbo].cdblen], 12);
		अगर (errstatus)
			prपूर्णांकk("aha1542_intr_handle: returning %6x\n", errstatus);
#पूर्ण_अगर
		पंचांगp_cmd->result = errstatus;
		aha1542->पूर्णांक_cmds[mbo] = शून्य;	/* This effectively मुक्तs up the mailbox slot, as
						 * far as queuecommand is concerned
						 */
		my_करोne(पंचांगp_cmd);
		number_serviced++;
	पूर्ण;
पूर्ण

अटल पूर्णांक aha1542_queuecommand(काष्ठा Scsi_Host *sh, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा aha1542_cmd *acmd = scsi_cmd_priv(cmd);
	काष्ठा aha1542_hostdata *aha1542 = shost_priv(sh);
	u8 direction;
	u8 target = cmd->device->id;
	u8 lun = cmd->device->lun;
	अचिन्हित दीर्घ flags;
	पूर्णांक bufflen = scsi_bufflen(cmd);
	पूर्णांक mbo;
	काष्ठा mailbox *mb = aha1542->mb;
	काष्ठा ccb *ccb = aha1542->ccb;

	अगर (*cmd->cmnd == REQUEST_SENSE) अणु
		/* Don't करो the command - we have the sense data alपढ़ोy */
		cmd->result = 0;
		cmd->scsi_करोne(cmd);
		वापस 0;
	पूर्ण
#अगर_घोषित DEBUG
	अणु
		पूर्णांक i = -1;
		अगर (*cmd->cmnd == READ_10 || *cmd->cmnd == WRITE_10)
			i = xscsi2पूर्णांक(cmd->cmnd + 2);
		अन्यथा अगर (*cmd->cmnd == READ_6 || *cmd->cmnd == WRITE_6)
			i = scsi2पूर्णांक(cmd->cmnd + 2);
		shost_prपूर्णांकk(KERN_DEBUG, sh, "aha1542_queuecommand: dev %d cmd %02x pos %d len %d",
						target, *cmd->cmnd, i, bufflen);
		prपूर्णांक_hex_dump_bytes("command: ", DUMP_PREFIX_NONE, cmd->cmnd, cmd->cmd_len);
	पूर्ण
#पूर्ण_अगर

	अगर (cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		व्योम *buf = acmd->data_buffer;
		काष्ठा req_iterator iter;
		काष्ठा bio_vec bv;

		rq_क्रम_each_segment(bv, cmd->request, iter) अणु
			स_नकल_from_page(buf, bv.bv_page, bv.bv_offset,
					 bv.bv_len);
			buf += bv.bv_len;
		पूर्ण
	पूर्ण

	/*
	 * Use the outgoing mailboxes in a round-robin fashion, because this
	 * is how the host adapter will scan क्रम them
	 */

	spin_lock_irqsave(sh->host_lock, flags);
	mbo = aha1542->aha1542_last_mbo_used + 1;
	अगर (mbo >= AHA1542_MAILBOXES)
		mbo = 0;

	करो अणु
		अगर (mb[mbo].status == 0 && aha1542->पूर्णांक_cmds[mbo] == शून्य)
			अवरोध;
		mbo++;
		अगर (mbo >= AHA1542_MAILBOXES)
			mbo = 0;
	पूर्ण जबतक (mbo != aha1542->aha1542_last_mbo_used);

	अगर (mb[mbo].status || aha1542->पूर्णांक_cmds[mbo])
		panic("Unable to find empty mailbox for aha1542.\n");

	aha1542->पूर्णांक_cmds[mbo] = cmd;	/* This will effectively prevent someone अन्यथा from
					 * screwing with this cdb.
					 */

	aha1542->aha1542_last_mbo_used = mbo;

#अगर_घोषित DEBUG
	shost_prपूर्णांकk(KERN_DEBUG, sh, "Sending command (%d %p)...", mbo, cmd->scsi_करोne);
#पूर्ण_अगर

	/* This माला_लो trashed क्रम some reason */
	any2scsi(mb[mbo].ccbptr, aha1542->ccb_handle + mbo * माप(*ccb));

	स_रखो(&ccb[mbo], 0, माप(काष्ठा ccb));

	ccb[mbo].cdblen = cmd->cmd_len;

	direction = 0;
	अगर (*cmd->cmnd == READ_10 || *cmd->cmnd == READ_6)
		direction = 8;
	अन्यथा अगर (*cmd->cmnd == WRITE_10 || *cmd->cmnd == WRITE_6)
		direction = 16;

	स_नकल(ccb[mbo].cdb, cmd->cmnd, ccb[mbo].cdblen);
	ccb[mbo].op = 0;	/* SCSI Initiator Command */
	any2scsi(ccb[mbo].datalen, bufflen);
	अगर (bufflen)
		any2scsi(ccb[mbo].dataptr, acmd->data_buffer_handle);
	अन्यथा
		any2scsi(ccb[mbo].dataptr, 0);
	ccb[mbo].idlun = (target & 7) << 5 | direction | (lun & 7);	/*SCSI Target Id */
	ccb[mbo].rsalen = 16;
	ccb[mbo].linkptr[0] = ccb[mbo].linkptr[1] = ccb[mbo].linkptr[2] = 0;
	ccb[mbo].commlinkid = 0;

#अगर_घोषित DEBUG
	prपूर्णांक_hex_dump_bytes("sending: ", DUMP_PREFIX_NONE, &ccb[mbo], माप(ccb[mbo]) - 10);
	prपूर्णांकk("aha1542_queuecommand: now waiting for interrupt ");
#पूर्ण_अगर
	mb[mbo].status = 1;
	aha1542_outb(cmd->device->host->io_port, CMD_START_SCSI);
	spin_unlock_irqrestore(sh->host_lock, flags);

	वापस 0;
पूर्ण

/* Initialize mailboxes */
अटल व्योम setup_mailboxes(काष्ठा Scsi_Host *sh)
अणु
	काष्ठा aha1542_hostdata *aha1542 = shost_priv(sh);
	u8 mb_cmd[5] = अणु CMD_MBINIT, AHA1542_MAILBOXES, 0, 0, 0पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < AHA1542_MAILBOXES; i++) अणु
		aha1542->mb[i].status = 0;
		any2scsi(aha1542->mb[i].ccbptr,
			 aha1542->ccb_handle + i * माप(काष्ठा ccb));
		aha1542->mb[AHA1542_MAILBOXES + i].status = 0;
	पूर्ण;
	aha1542_पूर्णांकr_reset(sh->io_port);	/* reset पूर्णांकerrupts, so they करोn't block */
	any2scsi(mb_cmd + 2, aha1542->mb_handle);
	अगर (aha1542_out(sh->io_port, mb_cmd, 5))
		shost_prपूर्णांकk(KERN_ERR, sh, "failed setting up mailboxes\n");
	aha1542_पूर्णांकr_reset(sh->io_port);
पूर्ण

अटल पूर्णांक aha1542_अ_लोonfig(काष्ठा Scsi_Host *sh)
अणु
	u8 inquiry_result[3];
	पूर्णांक i;
	i = inb(STATUS(sh->io_port));
	अगर (i & DF) अणु
		i = inb(DATA(sh->io_port));
	पूर्ण;
	aha1542_outb(sh->io_port, CMD_RETCONF);
	aha1542_in(sh->io_port, inquiry_result, 3, 0);
	अगर (!रुको_mask(INTRFLAGS(sh->io_port), INTRMASK, HACC, 0, 0))
		shost_prपूर्णांकk(KERN_ERR, sh, "error querying board settings\n");
	aha1542_पूर्णांकr_reset(sh->io_port);
	चयन (inquiry_result[0]) अणु
	हाल 0x80:
		sh->dma_channel = 7;
		अवरोध;
	हाल 0x40:
		sh->dma_channel = 6;
		अवरोध;
	हाल 0x20:
		sh->dma_channel = 5;
		अवरोध;
	हाल 0x01:
		sh->dma_channel = 0;
		अवरोध;
	हाल 0:
		/*
		 * This means that the adapter, although Adaptec 1542 compatible, करोesn't use a DMA channel.
		 * Currently only aware of the BusLogic BT-445S VL-Bus adapter which needs this.
		 */
		sh->dma_channel = 0xFF;
		अवरोध;
	शेष:
		shost_prपूर्णांकk(KERN_ERR, sh, "Unable to determine DMA channel.\n");
		वापस -1;
	पूर्ण;
	चयन (inquiry_result[1]) अणु
	हाल 0x40:
		sh->irq = 15;
		अवरोध;
	हाल 0x20:
		sh->irq = 14;
		अवरोध;
	हाल 0x8:
		sh->irq = 12;
		अवरोध;
	हाल 0x4:
		sh->irq = 11;
		अवरोध;
	हाल 0x2:
		sh->irq = 10;
		अवरोध;
	हाल 0x1:
		sh->irq = 9;
		अवरोध;
	शेष:
		shost_prपूर्णांकk(KERN_ERR, sh, "Unable to determine IRQ level.\n");
		वापस -1;
	पूर्ण;
	sh->this_id = inquiry_result[2] & 7;
	वापस 0;
पूर्ण

/*
 * This function should only be called क्रम 1542C boards - we can detect
 * the special firmware settings and unlock the board
 */

अटल पूर्णांक aha1542_mbenable(काष्ठा Scsi_Host *sh)
अणु
	अटल u8 mbenable_cmd[3];
	अटल u8 mbenable_result[2];
	पूर्णांक retval;

	retval = BIOS_TRANSLATION_6432;

	aha1542_outb(sh->io_port, CMD_EXTBIOS);
	अगर (aha1542_in(sh->io_port, mbenable_result, 2, 100))
		वापस retval;
	अगर (!रुको_mask(INTRFLAGS(sh->io_port), INTRMASK, HACC, 0, 100))
		जाओ fail;
	aha1542_पूर्णांकr_reset(sh->io_port);

	अगर ((mbenable_result[0] & 0x08) || mbenable_result[1]) अणु
		mbenable_cmd[0] = CMD_MBENABLE;
		mbenable_cmd[1] = 0;
		mbenable_cmd[2] = mbenable_result[1];

		अगर ((mbenable_result[0] & 0x08) && (mbenable_result[1] & 0x03))
			retval = BIOS_TRANSLATION_25563;

		अगर (aha1542_out(sh->io_port, mbenable_cmd, 3))
			जाओ fail;
	पूर्ण;
	जबतक (0) अणु
fail:
		shost_prपूर्णांकk(KERN_ERR, sh, "Mailbox init failed\n");
	पूर्ण
	aha1542_पूर्णांकr_reset(sh->io_port);
	वापस retval;
पूर्ण

/* Query the board to find out अगर it is a 1542 or a 1740, or whatever. */
अटल पूर्णांक aha1542_query(काष्ठा Scsi_Host *sh)
अणु
	काष्ठा aha1542_hostdata *aha1542 = shost_priv(sh);
	u8 inquiry_result[4];
	पूर्णांक i;
	i = inb(STATUS(sh->io_port));
	अगर (i & DF) अणु
		i = inb(DATA(sh->io_port));
	पूर्ण;
	aha1542_outb(sh->io_port, CMD_INQUIRY);
	aha1542_in(sh->io_port, inquiry_result, 4, 0);
	अगर (!रुको_mask(INTRFLAGS(sh->io_port), INTRMASK, HACC, 0, 0))
		shost_prपूर्णांकk(KERN_ERR, sh, "error querying card type\n");
	aha1542_पूर्णांकr_reset(sh->io_port);

	aha1542->bios_translation = BIOS_TRANSLATION_6432;	/* Default हाल */

	/*
	 * For an AHA1740 series board, we ignore the board since there is a
	 * hardware bug which can lead to wrong blocks being वापसed अगर the board
	 * is operating in the 1542 emulation mode.  Since there is an extended mode
	 * driver, we simply ignore the board and let the 1740 driver pick it up.
	 */

	अगर (inquiry_result[0] == 0x43) अणु
		shost_prपूर्णांकk(KERN_INFO, sh, "Emulation mode not supported for AHA-1740 hardware, use aha1740 driver instead.\n");
		वापस 1;
	पूर्ण;

	/*
	 * Always call this - boards that करो not support extended bios translation
	 * will ignore the command, and we will set the proper शेष
	 */

	aha1542->bios_translation = aha1542_mbenable(sh);

	वापस 0;
पूर्ण

अटल u8 dma_speed_hw(पूर्णांक dma_speed)
अणु
	चयन (dma_speed) अणु
	हाल 5:
		वापस 0x00;
	हाल 6:
		वापस 0x04;
	हाल 7:
		वापस 0x01;
	हाल 8:
		वापस 0x02;
	हाल 10:
		वापस 0x03;
	पूर्ण

	वापस 0xff;	/* invalid */
पूर्ण

/* Set the Bus on/off-बार as not to ruin floppy perक्रमmance */
अटल व्योम aha1542_set_bus_बार(काष्ठा Scsi_Host *sh, पूर्णांक bus_on, पूर्णांक bus_off, पूर्णांक dma_speed)
अणु
	अगर (bus_on > 0) अणु
		u8 oncmd[] = अणु CMD_BUSON_TIME, clamp(bus_on, 2, 15) पूर्ण;

		aha1542_पूर्णांकr_reset(sh->io_port);
		अगर (aha1542_out(sh->io_port, oncmd, 2))
			जाओ fail;
	पूर्ण

	अगर (bus_off > 0) अणु
		u8 offcmd[] = अणु CMD_BUSOFF_TIME, clamp(bus_off, 1, 64) पूर्ण;

		aha1542_पूर्णांकr_reset(sh->io_port);
		अगर (aha1542_out(sh->io_port, offcmd, 2))
			जाओ fail;
	पूर्ण

	अगर (dma_speed_hw(dma_speed) != 0xff) अणु
		u8 dmacmd[] = अणु CMD_DMASPEED, dma_speed_hw(dma_speed) पूर्ण;

		aha1542_पूर्णांकr_reset(sh->io_port);
		अगर (aha1542_out(sh->io_port, dmacmd, 2))
			जाओ fail;
	पूर्ण
	aha1542_पूर्णांकr_reset(sh->io_port);
	वापस;
fail:
	shost_prपूर्णांकk(KERN_ERR, sh, "setting bus on/off-time failed\n");
	aha1542_पूर्णांकr_reset(sh->io_port);
पूर्ण

/* वापस non-zero on detection */
अटल काष्ठा Scsi_Host *aha1542_hw_init(काष्ठा scsi_host_ढाँचा *tpnt, काष्ठा device *pdev, पूर्णांक indx)
अणु
	अचिन्हित पूर्णांक base_io = io[indx];
	काष्ठा Scsi_Host *sh;
	काष्ठा aha1542_hostdata *aha1542;
	अक्षर dma_info[] = "no DMA";

	अगर (base_io == 0)
		वापस शून्य;

	अगर (!request_region(base_io, AHA1542_REGION_SIZE, "aha1542"))
		वापस शून्य;

	sh = scsi_host_alloc(tpnt, माप(काष्ठा aha1542_hostdata));
	अगर (!sh)
		जाओ release;
	aha1542 = shost_priv(sh);

	sh->unique_id = base_io;
	sh->io_port = base_io;
	sh->n_io_port = AHA1542_REGION_SIZE;
	aha1542->aha1542_last_mbi_used = 2 * AHA1542_MAILBOXES - 1;
	aha1542->aha1542_last_mbo_used = AHA1542_MAILBOXES - 1;

	अगर (!aha1542_test_port(sh))
		जाओ unरेजिस्टर;

	aha1542_set_bus_बार(sh, bus_on[indx], bus_off[indx], dma_speed[indx]);
	अगर (aha1542_query(sh))
		जाओ unरेजिस्टर;
	अगर (aha1542_अ_लोonfig(sh) == -1)
		जाओ unरेजिस्टर;

	अगर (sh->dma_channel != 0xFF)
		snम_लिखो(dma_info, माप(dma_info), "DMA %d", sh->dma_channel);
	shost_prपूर्णांकk(KERN_INFO, sh, "Adaptec AHA-1542 (SCSI-ID %d) at IO 0x%x, IRQ %d, %s\n",
				sh->this_id, base_io, sh->irq, dma_info);
	अगर (aha1542->bios_translation == BIOS_TRANSLATION_25563)
		shost_prपूर्णांकk(KERN_INFO, sh, "Using extended bios translation\n");

	अगर (dma_set_mask_and_coherent(pdev, DMA_BIT_MASK(24)) < 0)
		जाओ unरेजिस्टर;

	aha1542->mb = dma_alloc_coherent(pdev,
			AHA1542_MAILBOXES * 2 * माप(काष्ठा mailbox),
			&aha1542->mb_handle, GFP_KERNEL);
	अगर (!aha1542->mb)
		जाओ unरेजिस्टर;

	aha1542->ccb = dma_alloc_coherent(pdev,
			AHA1542_MAILBOXES * माप(काष्ठा ccb),
			&aha1542->ccb_handle, GFP_KERNEL);
	अगर (!aha1542->ccb)
		जाओ मुक्त_mb;

	setup_mailboxes(sh);

	अगर (request_irq(sh->irq, aha1542_पूर्णांकerrupt, 0, "aha1542", sh)) अणु
		shost_prपूर्णांकk(KERN_ERR, sh, "Unable to allocate IRQ.\n");
		जाओ मुक्त_ccb;
	पूर्ण
	अगर (sh->dma_channel != 0xFF) अणु
		अगर (request_dma(sh->dma_channel, "aha1542")) अणु
			shost_prपूर्णांकk(KERN_ERR, sh, "Unable to allocate DMA channel.\n");
			जाओ मुक्त_irq;
		पूर्ण
		अगर (sh->dma_channel == 0 || sh->dma_channel >= 5) अणु
			set_dma_mode(sh->dma_channel, DMA_MODE_CASCADE);
			enable_dma(sh->dma_channel);
		पूर्ण
	पूर्ण

	अगर (scsi_add_host(sh, pdev))
		जाओ मुक्त_dma;

	scsi_scan_host(sh);

	वापस sh;

मुक्त_dma:
	अगर (sh->dma_channel != 0xff)
		मुक्त_dma(sh->dma_channel);
मुक्त_irq:
	मुक्त_irq(sh->irq, sh);
मुक्त_ccb:
	dma_मुक्त_coherent(pdev, AHA1542_MAILBOXES * माप(काष्ठा ccb),
			  aha1542->ccb, aha1542->ccb_handle);
मुक्त_mb:
	dma_मुक्त_coherent(pdev, AHA1542_MAILBOXES * 2 * माप(काष्ठा mailbox),
			  aha1542->mb, aha1542->mb_handle);
unरेजिस्टर:
	scsi_host_put(sh);
release:
	release_region(base_io, AHA1542_REGION_SIZE);

	वापस शून्य;
पूर्ण

अटल पूर्णांक aha1542_release(काष्ठा Scsi_Host *sh)
अणु
	काष्ठा aha1542_hostdata *aha1542 = shost_priv(sh);
	काष्ठा device *dev = sh->dma_dev;

	scsi_हटाओ_host(sh);
	अगर (sh->dma_channel != 0xff)
		मुक्त_dma(sh->dma_channel);
	dma_मुक्त_coherent(dev, AHA1542_MAILBOXES * माप(काष्ठा ccb),
			  aha1542->ccb, aha1542->ccb_handle);
	dma_मुक्त_coherent(dev, AHA1542_MAILBOXES * 2 * माप(काष्ठा mailbox),
			  aha1542->mb, aha1542->mb_handle);
	अगर (sh->irq)
		मुक्त_irq(sh->irq, sh);
	अगर (sh->io_port && sh->n_io_port)
		release_region(sh->io_port, sh->n_io_port);
	scsi_host_put(sh);
	वापस 0;
पूर्ण


/*
 * This is a device reset.  This is handled by sending a special command
 * to the device.
 */
अटल पूर्णांक aha1542_dev_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *sh = cmd->device->host;
	काष्ठा aha1542_hostdata *aha1542 = shost_priv(sh);
	अचिन्हित दीर्घ flags;
	काष्ठा mailbox *mb = aha1542->mb;
	u8 target = cmd->device->id;
	u8 lun = cmd->device->lun;
	पूर्णांक mbo;
	काष्ठा ccb *ccb = aha1542->ccb;

	spin_lock_irqsave(sh->host_lock, flags);
	mbo = aha1542->aha1542_last_mbo_used + 1;
	अगर (mbo >= AHA1542_MAILBOXES)
		mbo = 0;

	करो अणु
		अगर (mb[mbo].status == 0 && aha1542->पूर्णांक_cmds[mbo] == शून्य)
			अवरोध;
		mbo++;
		अगर (mbo >= AHA1542_MAILBOXES)
			mbo = 0;
	पूर्ण जबतक (mbo != aha1542->aha1542_last_mbo_used);

	अगर (mb[mbo].status || aha1542->पूर्णांक_cmds[mbo])
		panic("Unable to find empty mailbox for aha1542.\n");

	aha1542->पूर्णांक_cmds[mbo] = cmd;	/* This will effectively
					 * prevent someone अन्यथा from
					 * screwing with this cdb.
					 */

	aha1542->aha1542_last_mbo_used = mbo;

	/* This माला_लो trashed क्रम some reason */
	any2scsi(mb[mbo].ccbptr, aha1542->ccb_handle + mbo * माप(*ccb));

	स_रखो(&ccb[mbo], 0, माप(काष्ठा ccb));

	ccb[mbo].op = 0x81;	/* BUS DEVICE RESET */

	ccb[mbo].idlun = (target & 7) << 5 | (lun & 7);		/*SCSI Target Id */

	ccb[mbo].linkptr[0] = ccb[mbo].linkptr[1] = ccb[mbo].linkptr[2] = 0;
	ccb[mbo].commlinkid = 0;

	/*
	 * Now tell the 1542 to flush all pending commands क्रम this
	 * target
	 */
	aha1542_outb(sh->io_port, CMD_START_SCSI);
	spin_unlock_irqrestore(sh->host_lock, flags);

	scmd_prपूर्णांकk(KERN_WARNING, cmd,
		"Trying device reset for target\n");

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक aha1542_reset(काष्ठा scsi_cmnd *cmd, u8 reset_cmd)
अणु
	काष्ठा Scsi_Host *sh = cmd->device->host;
	काष्ठा aha1542_hostdata *aha1542 = shost_priv(sh);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(sh->host_lock, flags);
	/*
	 * This करोes a scsi reset क्रम all devices on the bus.
	 * In principle, we could also reset the 1542 - should
	 * we करो this?  Try this first, and we can add that later
	 * अगर it turns out to be useful.
	 */
	outb(reset_cmd, CONTROL(cmd->device->host->io_port));

	अगर (!रुको_mask(STATUS(cmd->device->host->io_port),
	     STATMASK, IDLE, STST | DIAGF | INVDCMD | DF | CDF, 0)) अणु
		spin_unlock_irqrestore(sh->host_lock, flags);
		वापस FAILED;
	पूर्ण

	/*
	 * We need to करो this too beक्रमe the 1542 can पूर्णांकeract with
	 * us again after host reset.
	 */
	अगर (reset_cmd & HRST)
		setup_mailboxes(cmd->device->host);

	/*
	 * Now try to pick up the pieces.  For all pending commands,
	 * मुक्त any पूर्णांकernal data काष्ठाures, and basically clear things
	 * out.  We करो not try and restart any commands or anything -
	 * the strategy handler takes care of that crap.
	 */
	shost_prपूर्णांकk(KERN_WARNING, cmd->device->host, "Sent BUS RESET to scsi host %d\n", cmd->device->host->host_no);

	क्रम (i = 0; i < AHA1542_MAILBOXES; i++) अणु
		अगर (aha1542->पूर्णांक_cmds[i] != शून्य) अणु
			काष्ठा scsi_cmnd *पंचांगp_cmd;
			पंचांगp_cmd = aha1542->पूर्णांक_cmds[i];

			अगर (पंचांगp_cmd->device->soft_reset) अणु
				/*
				 * If this device implements the soft reset option,
				 * then it is still holding onto the command, and
				 * may yet complete it.  In this हाल, we करोn't
				 * flush the data.
				 */
				जारी;
			पूर्ण
			aha1542_मुक्त_cmd(पंचांगp_cmd);
			aha1542->पूर्णांक_cmds[i] = शून्य;
			aha1542->mb[i].status = 0;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(sh->host_lock, flags);
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक aha1542_bus_reset(काष्ठा scsi_cmnd *cmd)
अणु
	वापस aha1542_reset(cmd, SCRST);
पूर्ण

अटल पूर्णांक aha1542_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	वापस aha1542_reset(cmd, HRST | SCRST);
पूर्ण

अटल पूर्णांक aha1542_biosparam(काष्ठा scsi_device *sdev,
		काष्ठा block_device *bdev, sector_t capacity, पूर्णांक geom[])
अणु
	काष्ठा aha1542_hostdata *aha1542 = shost_priv(sdev->host);

	अगर (capacity >= 0x200000 &&
			aha1542->bios_translation == BIOS_TRANSLATION_25563) अणु
		/* Please verअगरy that this is the same as what DOS वापसs */
		geom[0] = 255;	/* heads */
		geom[1] = 63;	/* sectors */
	पूर्ण अन्यथा अणु
		geom[0] = 64;	/* heads */
		geom[1] = 32;	/* sectors */
	पूर्ण
	geom[2] = sector_भाग(capacity, geom[0] * geom[1]);	/* cylinders */

	वापस 0;
पूर्ण
MODULE_LICENSE("GPL");

अटल पूर्णांक aha1542_init_cmd_priv(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा aha1542_cmd *acmd = scsi_cmd_priv(cmd);

	acmd->data_buffer = dma_alloc_coherent(shost->dma_dev,
			SECTOR_SIZE * AHA1542_MAX_SECTORS,
			&acmd->data_buffer_handle, GFP_KERNEL);
	अगर (!acmd->data_buffer)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक aha1542_निकास_cmd_priv(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा aha1542_cmd *acmd = scsi_cmd_priv(cmd);

	dma_मुक्त_coherent(shost->dma_dev, SECTOR_SIZE * AHA1542_MAX_SECTORS,
			acmd->data_buffer, acmd->data_buffer_handle);
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.proc_name		= "aha1542",
	.name			= "Adaptec 1542",
	.cmd_size		= माप(काष्ठा aha1542_cmd),
	.queuecommand		= aha1542_queuecommand,
	.eh_device_reset_handler= aha1542_dev_reset,
	.eh_bus_reset_handler	= aha1542_bus_reset,
	.eh_host_reset_handler	= aha1542_host_reset,
	.bios_param		= aha1542_biosparam,
	.init_cmd_priv		= aha1542_init_cmd_priv,
	.निकास_cmd_priv		= aha1542_निकास_cmd_priv,
	.can_queue		= AHA1542_MAILBOXES,
	.this_id		= 7,
	.max_sectors		= AHA1542_MAX_SECTORS,
	.sg_tablesize		= SG_ALL,
पूर्ण;

अटल पूर्णांक aha1542_isa_match(काष्ठा device *pdev, अचिन्हित पूर्णांक ndev)
अणु
	काष्ठा Scsi_Host *sh = aha1542_hw_init(&driver_ढाँचा, pdev, ndev);

	अगर (!sh)
		वापस 0;

	dev_set_drvdata(pdev, sh);
	वापस 1;
पूर्ण

अटल व्योम aha1542_isa_हटाओ(काष्ठा device *pdev,
				    अचिन्हित पूर्णांक ndev)
अणु
	aha1542_release(dev_get_drvdata(pdev));
	dev_set_drvdata(pdev, शून्य);
पूर्ण

अटल काष्ठा isa_driver aha1542_isa_driver = अणु
	.match		= aha1542_isa_match,
	.हटाओ		= aha1542_isa_हटाओ,
	.driver		= अणु
		.name	= "aha1542"
	पूर्ण,
पूर्ण;
अटल पूर्णांक isa_रेजिस्टरed;

#अगर_घोषित CONFIG_PNP
अटल स्थिर काष्ठा pnp_device_id aha1542_pnp_ids[] = अणु
	अणु .id = "ADP1542" पूर्ण,
	अणु .id = "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pnp, aha1542_pnp_ids);

अटल पूर्णांक aha1542_pnp_probe(काष्ठा pnp_dev *pdev, स्थिर काष्ठा pnp_device_id *id)
अणु
	पूर्णांक indx;
	काष्ठा Scsi_Host *sh;

	क्रम (indx = 0; indx < ARRAY_SIZE(io); indx++) अणु
		अगर (io[indx])
			जारी;

		अगर (pnp_activate_dev(pdev) < 0)
			जारी;

		io[indx] = pnp_port_start(pdev, 0);

		/*
		 * The card can be queried क्रम its DMA, we have
		 * the DMA set up that is enough
		 */

		dev_info(&pdev->dev, "ISAPnP found an AHA1535 at I/O 0x%03X", io[indx]);
	पूर्ण

	sh = aha1542_hw_init(&driver_ढाँचा, &pdev->dev, indx);
	अगर (!sh)
		वापस -ENODEV;

	pnp_set_drvdata(pdev, sh);
	वापस 0;
पूर्ण

अटल व्योम aha1542_pnp_हटाओ(काष्ठा pnp_dev *pdev)
अणु
	aha1542_release(pnp_get_drvdata(pdev));
	pnp_set_drvdata(pdev, शून्य);
पूर्ण

अटल काष्ठा pnp_driver aha1542_pnp_driver = अणु
	.name		= "aha1542",
	.id_table	= aha1542_pnp_ids,
	.probe		= aha1542_pnp_probe,
	.हटाओ		= aha1542_pnp_हटाओ,
पूर्ण;
अटल पूर्णांक pnp_रेजिस्टरed;
#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक __init aha1542_init(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर_घोषित CONFIG_PNP
	अगर (isapnp) अणु
		ret = pnp_रेजिस्टर_driver(&aha1542_pnp_driver);
		अगर (!ret)
			pnp_रेजिस्टरed = 1;
	पूर्ण
#पूर्ण_अगर
	ret = isa_रेजिस्टर_driver(&aha1542_isa_driver, MAXBOARDS);
	अगर (!ret)
		isa_रेजिस्टरed = 1;

#अगर_घोषित CONFIG_PNP
	अगर (pnp_रेजिस्टरed)
		ret = 0;
#पूर्ण_अगर
	अगर (isa_रेजिस्टरed)
		ret = 0;

	वापस ret;
पूर्ण

अटल व्योम __निकास aha1542_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_driver(&aha1542_pnp_driver);
#पूर्ण_अगर
	अगर (isa_रेजिस्टरed)
		isa_unरेजिस्टर_driver(&aha1542_isa_driver);
पूर्ण

module_init(aha1542_init);
module_निकास(aha1542_निकास);
