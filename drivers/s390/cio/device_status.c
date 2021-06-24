<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2002
 *    Author(s): Cornelia Huck (cornelia.huck@de.ibm.com)
 *		 Martin Schwidefsky (schwidefsky@de.ibm.com)
 *
 * Status accumulation and basic sense functions.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cपन.स>

#समावेश "cio.h"
#समावेश "cio_debug.h"
#समावेश "css.h"
#समावेश "device.h"
#समावेश "ioasm.h"
#समावेश "io_sch.h"

/*
 * Check क्रम any kind of channel or पूर्णांकerface control check but करोn't
 * issue the message क्रम the console device
 */
अटल व्योम
ccw_device_msg_control_check(काष्ठा ccw_device *cdev, काष्ठा irb *irb)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	अक्षर dbf_text[15];

	अगर (!scsw_is_valid_cstat(&irb->scsw) ||
	    !(scsw_cstat(&irb->scsw) & (SCHN_STAT_CHN_DATA_CHK |
	      SCHN_STAT_CHN_CTRL_CHK | SCHN_STAT_INTF_CTRL_CHK)))
		वापस;
	CIO_MSG_EVENT(0, "Channel-Check or Interface-Control-Check "
		      "received"
		      " ... device %04x on subchannel 0.%x.%04x, dev_stat "
		      ": %02X sch_stat : %02X\n",
		      cdev->निजी->dev_id.devno, sch->schid.ssid,
		      sch->schid.sch_no,
		      scsw_dstat(&irb->scsw), scsw_cstat(&irb->scsw));
	प्र_लिखो(dbf_text, "chk%x", sch->schid.sch_no);
	CIO_TRACE_EVENT(0, dbf_text);
	CIO_HEX_EVENT(0, irb, माप(काष्ठा irb));
पूर्ण

/*
 * Some paths became not operational (pno bit in scsw is set).
 */
अटल व्योम
ccw_device_path_notoper(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch;

	sch = to_subchannel(cdev->dev.parent);
	अगर (cio_update_schib(sch))
		जाओ करोverअगरy;

	CIO_MSG_EVENT(0, "%s(0.%x.%04x) - path(s) %02x are "
		      "not operational \n", __func__,
		      sch->schid.ssid, sch->schid.sch_no,
		      sch->schib.pmcw.pnom);

	sch->lpm &= ~sch->schib.pmcw.pnom;
करोverअगरy:
	cdev->निजी->flags.करोverअगरy = 1;
पूर्ण

/*
 * Copy valid bits from the extended control word to device irb.
 */
अटल व्योम
ccw_device_accumulate_ecw(काष्ठा ccw_device *cdev, काष्ठा irb *irb)
अणु
	/*
	 * Copy extended control bit अगर it is valid... yes there
	 * are condition that have to be met क्रम the extended control
	 * bit to have meaning. Sick.
	 */
	cdev->निजी->dma_area->irb.scsw.cmd.ectl = 0;
	अगर ((irb->scsw.cmd.stctl & SCSW_STCTL_ALERT_STATUS) &&
	    !(irb->scsw.cmd.stctl & SCSW_STCTL_INTER_STATUS))
		cdev->निजी->dma_area->irb.scsw.cmd.ectl = irb->scsw.cmd.ectl;
	/* Check अगर extended control word is valid. */
	अगर (!cdev->निजी->dma_area->irb.scsw.cmd.ectl)
		वापस;
	/* Copy concurrent sense / model dependent inक्रमmation. */
	स_नकल(&cdev->निजी->dma_area->irb.ecw, irb->ecw, माप(irb->ecw));
पूर्ण

/*
 * Check अगर extended status word is valid.
 */
अटल पूर्णांक
ccw_device_accumulate_esw_valid(काष्ठा irb *irb)
अणु
	अगर (!irb->scsw.cmd.eswf &&
	    (irb->scsw.cmd.stctl == SCSW_STCTL_STATUS_PEND))
		वापस 0;
	अगर (irb->scsw.cmd.stctl ==
			(SCSW_STCTL_INTER_STATUS|SCSW_STCTL_STATUS_PEND) &&
	    !(irb->scsw.cmd.actl & SCSW_ACTL_SUSPENDED))
		वापस 0;
	वापस 1;
पूर्ण

/*
 * Copy valid bits from the extended status word to device irb.
 */
अटल व्योम
ccw_device_accumulate_esw(काष्ठा ccw_device *cdev, काष्ठा irb *irb)
अणु
	काष्ठा irb *cdev_irb;
	काष्ठा sublog *cdev_sublog, *sublog;

	अगर (!ccw_device_accumulate_esw_valid(irb))
		वापस;

	cdev_irb = &cdev->निजी->dma_area->irb;

	/* Copy last path used mask. */
	cdev_irb->esw.esw1.lpum = irb->esw.esw1.lpum;

	/* Copy subchannel logout inक्रमmation अगर esw is of क्रमmat 0. */
	अगर (irb->scsw.cmd.eswf) अणु
		cdev_sublog = &cdev_irb->esw.esw0.sublog;
		sublog = &irb->esw.esw0.sublog;
		/* Copy extended status flags. */
		cdev_sublog->esf = sublog->esf;
		/*
		 * Copy fields that have a meaning क्रम channel data check
		 * channel control check and पूर्णांकerface control check.
		 */
		अगर (irb->scsw.cmd.cstat & (SCHN_STAT_CHN_DATA_CHK |
				       SCHN_STAT_CHN_CTRL_CHK |
				       SCHN_STAT_INTF_CTRL_CHK)) अणु
			/* Copy ancillary report bit. */
			cdev_sublog->arep = sublog->arep;
			/* Copy field-validity-flags. */
			cdev_sublog->fvf = sublog->fvf;
			/* Copy storage access code. */
			cdev_sublog->sacc = sublog->sacc;
			/* Copy termination code. */
			cdev_sublog->termc = sublog->termc;
			/* Copy sequence code. */
			cdev_sublog->seqc = sublog->seqc;
		पूर्ण
		/* Copy device status check. */
		cdev_sublog->devsc = sublog->devsc;
		/* Copy secondary error. */
		cdev_sublog->serr = sublog->serr;
		/* Copy i/o-error alert. */
		cdev_sublog->ioerr = sublog->ioerr;
		/* Copy channel path समयout bit. */
		अगर (irb->scsw.cmd.cstat & SCHN_STAT_INTF_CTRL_CHK)
			cdev_irb->esw.esw0.erw.cpt = irb->esw.esw0.erw.cpt;
		/* Copy failing storage address validity flag. */
		cdev_irb->esw.esw0.erw.fsavf = irb->esw.esw0.erw.fsavf;
		अगर (cdev_irb->esw.esw0.erw.fsavf) अणु
			/* ... and copy the failing storage address. */
			स_नकल(cdev_irb->esw.esw0.faddr, irb->esw.esw0.faddr,
			       माप (irb->esw.esw0.faddr));
			/* ... and copy the failing storage address क्रमmat. */
			cdev_irb->esw.esw0.erw.fsaf = irb->esw.esw0.erw.fsaf;
		पूर्ण
		/* Copy secondary ccw address validity bit. */
		cdev_irb->esw.esw0.erw.scavf = irb->esw.esw0.erw.scavf;
		अगर (irb->esw.esw0.erw.scavf)
			/* ... and copy the secondary ccw address. */
			cdev_irb->esw.esw0.saddr = irb->esw.esw0.saddr;
		
	पूर्ण
	/* FIXME: DCTI क्रम क्रमmat 2? */

	/* Copy authorization bit. */
	cdev_irb->esw.esw0.erw.auth = irb->esw.esw0.erw.auth;
	/* Copy path verअगरication required flag. */
	cdev_irb->esw.esw0.erw.pvrf = irb->esw.esw0.erw.pvrf;
	अगर (irb->esw.esw0.erw.pvrf)
		cdev->निजी->flags.करोverअगरy = 1;
	/* Copy concurrent sense bit. */
	cdev_irb->esw.esw0.erw.cons = irb->esw.esw0.erw.cons;
	अगर (irb->esw.esw0.erw.cons)
		cdev_irb->esw.esw0.erw.scnt = irb->esw.esw0.erw.scnt;
पूर्ण

/*
 * Accumulate status from irb to devstat.
 */
व्योम
ccw_device_accumulate_irb(काष्ठा ccw_device *cdev, काष्ठा irb *irb)
अणु
	काष्ठा irb *cdev_irb;

	/*
	 * Check अगर the status pending bit is set in stctl.
	 * If not, the reमुख्यing bit have no meaning and we must ignore them.
	 * The esw is not meaningful as well...
	 */
	अगर (!(scsw_stctl(&irb->scsw) & SCSW_STCTL_STATUS_PEND))
		वापस;

	/* Check क्रम channel checks and पूर्णांकerface control checks. */
	ccw_device_msg_control_check(cdev, irb);

	/* Check क्रम path not operational. */
	अगर (scsw_is_valid_pno(&irb->scsw) && scsw_pno(&irb->scsw))
		ccw_device_path_notoper(cdev);
	/* No irb accumulation क्रम transport mode irbs. */
	अगर (scsw_is_पंचांग(&irb->scsw)) अणु
		स_नकल(&cdev->निजी->dma_area->irb, irb, माप(काष्ठा irb));
		वापस;
	पूर्ण
	/*
	 * Don't accumulate unsolicited पूर्णांकerrupts.
	 */
	अगर (!scsw_is_solicited(&irb->scsw))
		वापस;

	cdev_irb = &cdev->निजी->dma_area->irb;

	/*
	 * If the clear function had been perक्रमmed, all क्रमmerly pending
	 * status at the subchannel has been cleared and we must not pass
	 * पूर्णांकermediate accumulated status to the device driver.
	 */
	अगर (irb->scsw.cmd.fctl & SCSW_FCTL_CLEAR_FUNC)
		स_रखो(&cdev->निजी->dma_area->irb, 0, माप(काष्ठा irb));

	/* Copy bits which are valid only क्रम the start function. */
	अगर (irb->scsw.cmd.fctl & SCSW_FCTL_START_FUNC) अणु
		/* Copy key. */
		cdev_irb->scsw.cmd.key = irb->scsw.cmd.key;
		/* Copy suspend control bit. */
		cdev_irb->scsw.cmd.sctl = irb->scsw.cmd.sctl;
		/* Accumulate deferred condition code. */
		cdev_irb->scsw.cmd.cc |= irb->scsw.cmd.cc;
		/* Copy ccw क्रमmat bit. */
		cdev_irb->scsw.cmd.fmt = irb->scsw.cmd.fmt;
		/* Copy prefetch bit. */
		cdev_irb->scsw.cmd.pfch = irb->scsw.cmd.pfch;
		/* Copy initial-status-पूर्णांकerruption-control. */
		cdev_irb->scsw.cmd.isic = irb->scsw.cmd.isic;
		/* Copy address limit checking control. */
		cdev_irb->scsw.cmd.alcc = irb->scsw.cmd.alcc;
		/* Copy suppress suspend bit. */
		cdev_irb->scsw.cmd.ssi = irb->scsw.cmd.ssi;
	पूर्ण

	/* Take care of the extended control bit and extended control word. */
	ccw_device_accumulate_ecw(cdev, irb);
	    
	/* Accumulate function control. */
	cdev_irb->scsw.cmd.fctl |= irb->scsw.cmd.fctl;
	/* Copy activity control. */
	cdev_irb->scsw.cmd.actl = irb->scsw.cmd.actl;
	/* Accumulate status control. */
	cdev_irb->scsw.cmd.stctl |= irb->scsw.cmd.stctl;
	/*
	 * Copy ccw address अगर it is valid. This is a bit simplअगरied
	 * but should be बंद enough क्रम all practical purposes.
	 */
	अगर ((irb->scsw.cmd.stctl & SCSW_STCTL_PRIM_STATUS) ||
	    ((irb->scsw.cmd.stctl ==
	      (SCSW_STCTL_INTER_STATUS|SCSW_STCTL_STATUS_PEND)) &&
	     (irb->scsw.cmd.actl & SCSW_ACTL_DEVACT) &&
	     (irb->scsw.cmd.actl & SCSW_ACTL_SCHACT)) ||
	    (irb->scsw.cmd.actl & SCSW_ACTL_SUSPENDED))
		cdev_irb->scsw.cmd.cpa = irb->scsw.cmd.cpa;
	/* Accumulate device status, but not the device busy flag. */
	cdev_irb->scsw.cmd.dstat &= ~DEV_STAT_BUSY;
	/* dstat is not always valid. */
	अगर (irb->scsw.cmd.stctl &
	    (SCSW_STCTL_PRIM_STATUS | SCSW_STCTL_SEC_STATUS
	     | SCSW_STCTL_INTER_STATUS | SCSW_STCTL_ALERT_STATUS))
		cdev_irb->scsw.cmd.dstat |= irb->scsw.cmd.dstat;
	/* Accumulate subchannel status. */
	cdev_irb->scsw.cmd.cstat |= irb->scsw.cmd.cstat;
	/* Copy residual count अगर it is valid. */
	अगर ((irb->scsw.cmd.stctl & SCSW_STCTL_PRIM_STATUS) &&
	    (irb->scsw.cmd.cstat & ~(SCHN_STAT_PCI | SCHN_STAT_INCORR_LEN))
	     == 0)
		cdev_irb->scsw.cmd.count = irb->scsw.cmd.count;

	/* Take care of bits in the extended status word. */
	ccw_device_accumulate_esw(cdev, irb);

	/*
	 * Check whether we must issue a SENSE CCW ourselves अगर there is no
	 * concurrent sense facility installed क्रम the subchannel.
	 * No sense is required अगर no delayed sense is pending
	 * and we did not get a unit check without sense inक्रमmation.
	 *
	 * Note: We should check क्रम ioinfo[irq]->flags.consns but VM
	 *	 violates the ESA/390 architecture and करोesn't present an
	 *	 opeअक्रम exception क्रम भव devices without concurrent
	 *	 sense facility available/supported when enabling the
	 *	 concurrent sense facility.
	 */
	अगर ((cdev_irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) &&
	    !(cdev_irb->esw.esw0.erw.cons))
		cdev->निजी->flags.करोsense = 1;
पूर्ण

/*
 * Do a basic sense.
 */
पूर्णांक
ccw_device_करो_sense(काष्ठा ccw_device *cdev, काष्ठा irb *irb)
अणु
	काष्ठा subchannel *sch;
	काष्ठा ccw1 *sense_ccw;
	पूर्णांक rc;

	sch = to_subchannel(cdev->dev.parent);

	/* A sense is required, can we करो it now ? */
	अगर (scsw_actl(&irb->scsw) & (SCSW_ACTL_DEVACT | SCSW_ACTL_SCHACT))
		/*
		 * we received an Unit Check but we have no final
		 *  status yet, thereक्रमe we must delay the SENSE
		 *  processing. We must not report this पूर्णांकermediate
		 *  status to the device पूर्णांकerrupt handler.
		 */
		वापस -EBUSY;

	/*
	 * We have ending status but no sense inक्रमmation. Do a basic sense.
	 */
	sense_ccw = &to_io_निजी(sch)->dma_area->sense_ccw;
	sense_ccw->cmd_code = CCW_CMD_BASIC_SENSE;
	sense_ccw->cda = (__u32) __pa(cdev->निजी->dma_area->irb.ecw);
	sense_ccw->count = SENSE_MAX_COUNT;
	sense_ccw->flags = CCW_FLAG_SLI;

	rc = cio_start(sch, sense_ccw, 0xff);
	अगर (rc == -ENODEV || rc == -EACCES)
		dev_fsm_event(cdev, DEV_EVENT_VERIFY);
	वापस rc;
पूर्ण

/*
 * Add inक्रमmation from basic sense to devstat.
 */
व्योम
ccw_device_accumulate_basic_sense(काष्ठा ccw_device *cdev, काष्ठा irb *irb)
अणु
	/*
	 * Check अगर the status pending bit is set in stctl.
	 * If not, the reमुख्यing bit have no meaning and we must ignore them.
	 * The esw is not meaningful as well...
	 */
	अगर (!(scsw_stctl(&irb->scsw) & SCSW_STCTL_STATUS_PEND))
		वापस;

	/* Check क्रम channel checks and पूर्णांकerface control checks. */
	ccw_device_msg_control_check(cdev, irb);

	/* Check क्रम path not operational. */
	अगर (scsw_is_valid_pno(&irb->scsw) && scsw_pno(&irb->scsw))
		ccw_device_path_notoper(cdev);

	अगर (!(irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) &&
	    (irb->scsw.cmd.dstat & DEV_STAT_CHN_END)) अणु
		cdev->निजी->dma_area->irb.esw.esw0.erw.cons = 1;
		cdev->निजी->flags.करोsense = 0;
	पूर्ण
	/* Check अगर path verअगरication is required. */
	अगर (ccw_device_accumulate_esw_valid(irb) &&
	    irb->esw.esw0.erw.pvrf)
		cdev->निजी->flags.करोverअगरy = 1;
पूर्ण

/*
 * This function accumulates the status पूर्णांकo the निजी devstat and
 * starts a basic sense अगर one is needed.
 */
पूर्णांक
ccw_device_accumulate_and_sense(काष्ठा ccw_device *cdev, काष्ठा irb *irb)
अणु
	ccw_device_accumulate_irb(cdev, irb);
	अगर ((irb->scsw.cmd.actl  & (SCSW_ACTL_DEVACT | SCSW_ACTL_SCHACT)) != 0)
		वापस -EBUSY;
	/* Check क्रम basic sense. */
	अगर (cdev->निजी->flags.करोsense &&
	    !(irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)) अणु
		cdev->निजी->dma_area->irb.esw.esw0.erw.cons = 1;
		cdev->निजी->flags.करोsense = 0;
		वापस 0;
	पूर्ण
	अगर (cdev->निजी->flags.करोsense) अणु
		ccw_device_करो_sense(cdev, irb);
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

