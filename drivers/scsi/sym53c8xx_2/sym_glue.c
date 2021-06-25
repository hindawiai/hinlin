<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device driver क्रम the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family 
 * of PCI-SCSI IO processors.
 *
 * Copyright (C) 1999-2001  Gerard Roudier <groudier@मुक्त.fr>
 * Copyright (c) 2003-2005  Matthew Wilcox <matthew@wil.cx>
 *
 * This driver is derived from the Linux sym53c8xx driver.
 * Copyright (C) 1998-2000  Gerard Roudier
 *
 * The sym53c8xx driver is derived from the ncr53c8xx driver that had been 
 * a port of the FreeBSD ncr driver to Linux-1.2.13.
 *
 * The original ncr driver has been written क्रम 386bsd and FreeBSD by
 *         Wolfgang Stanglmeier        <wolf@cologne.de>
 *         Stefan Esser                <se@mi.Uni-Koeln.de>
 * Copyright (C) 1994  Wolfgang Stanglmeier
 *
 * Other major contributions:
 *
 * NVRAM detection and पढ़ोing.
 * Copyright (C) 1997 Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */
#समावेश <linux/प्रकार.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport.h>

#समावेश "sym_glue.h"
#समावेश "sym_nvram.h"

#घोषणा NAME53C		"sym53c"
#घोषणा NAME53C8XX	"sym53c8xx"

काष्ठा sym_driver_setup sym_driver_setup = SYM_LINUX_DRIVER_SETUP;
अचिन्हित पूर्णांक sym_debug_flags = 0;

अटल अक्षर *excl_string;
अटल अक्षर *safe_string;
module_param_named(cmd_per_lun, sym_driver_setup.max_tag, uलघु, 0);
module_param_named(burst, sym_driver_setup.burst_order, byte, 0);
module_param_named(led, sym_driver_setup.scsi_led, byte, 0);
module_param_named(dअगरf, sym_driver_setup.scsi_dअगरf, byte, 0);
module_param_named(irqm, sym_driver_setup.irq_mode, byte, 0);
module_param_named(buschk, sym_driver_setup.scsi_bus_check, byte, 0);
module_param_named(hostid, sym_driver_setup.host_id, byte, 0);
module_param_named(verb, sym_driver_setup.verbose, byte, 0);
module_param_named(debug, sym_debug_flags, uपूर्णांक, 0);
module_param_named(settle, sym_driver_setup.settle_delay, byte, 0);
module_param_named(nvram, sym_driver_setup.use_nvram, byte, 0);
module_param_named(excl, excl_string, अक्षरp, 0);
module_param_named(safe, safe_string, अक्षरp, 0);

MODULE_PARM_DESC(cmd_per_lun, "The maximum number of tags to use by default");
MODULE_PARM_DESC(burst, "Maximum burst.  0 to disable, 255 to read from registers");
MODULE_PARM_DESC(led, "Set to 1 to enable LED support");
MODULE_PARM_DESC(dअगरf, "0 for no differential mode, 1 for BIOS, 2 for always, 3 for not GPIO3");
MODULE_PARM_DESC(irqm, "0 for open drain, 1 to leave alone, 2 for totem pole");
MODULE_PARM_DESC(buschk, "0 to not check, 1 for detach on error, 2 for warn on error");
MODULE_PARM_DESC(hostid, "The SCSI ID to use for the host adapters");
MODULE_PARM_DESC(verb, "0 for minimal verbosity, 1 for normal, 2 for excessive");
MODULE_PARM_DESC(debug, "Set bits to enable debugging");
MODULE_PARM_DESC(settle, "Settle delay in seconds.  Default 3");
MODULE_PARM_DESC(nvram, "Option currently not used");
MODULE_PARM_DESC(excl, "List ioport addresses here to prevent controllers from being attached");
MODULE_PARM_DESC(safe, "Set other settings to a \"safe mode\"");

MODULE_LICENSE("GPL");
MODULE_VERSION(SYM_VERSION);
MODULE_AUTHOR("Matthew Wilcox <matthew@wil.cx>");
MODULE_DESCRIPTION("NCR, Symbios and LSI 8xx and 1010 PCI SCSI adapters");

अटल व्योम sym2_setup_params(व्योम)
अणु
	अक्षर *p = excl_string;
	पूर्णांक xi = 0;

	जबतक (p && (xi < 8)) अणु
		अक्षर *next_p;
		पूर्णांक val = (पूर्णांक) simple_म_से_अदीर्घ(p, &next_p, 0);
		sym_driver_setup.excludes[xi++] = val;
		p = next_p;
	पूर्ण

	अगर (safe_string) अणु
		अगर (*safe_string == 'y') अणु
			sym_driver_setup.max_tag = 0;
			sym_driver_setup.burst_order = 0;
			sym_driver_setup.scsi_led = 0;
			sym_driver_setup.scsi_dअगरf = 1;
			sym_driver_setup.irq_mode = 0;
			sym_driver_setup.scsi_bus_check = 2;
			sym_driver_setup.host_id = 7;
			sym_driver_setup.verbose = 2;
			sym_driver_setup.settle_delay = 10;
			sym_driver_setup.use_nvram = 1;
		पूर्ण अन्यथा अगर (*safe_string != 'n') अणु
			prपूर्णांकk(KERN_WARNING NAME53C8XX "Ignoring parameter %s"
					" passed to safe option", safe_string);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा scsi_transport_ढाँचा *sym2_transport_ढाँचा = शून्य;

/*
 *  Driver निजी area in the SCSI command काष्ठाure.
 */
काष्ठा sym_ucmd अणु		/* Override the SCSI poपूर्णांकer काष्ठाure */
	काष्ठा completion *eh_करोne;		/* SCSI error handling */
पूर्ण;

#घोषणा SYM_UCMD_PTR(cmd)  ((काष्ठा sym_ucmd *)(&(cmd)->SCp))
#घोषणा SYM_SOFTC_PTR(cmd) sym_get_hcb(cmd->device->host)

/*
 *  Complete a pending CAM CCB.
 */
व्योम sym_xpt_करोne(काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा sym_ucmd *ucmd = SYM_UCMD_PTR(cmd);
	BUILD_BUG_ON(माप(काष्ठा scsi_poपूर्णांकer) < माप(काष्ठा sym_ucmd));

	अगर (ucmd->eh_करोne)
		complete(ucmd->eh_करोne);

	scsi_dma_unmap(cmd);
	cmd->scsi_करोne(cmd);
पूर्ण

/*
 *  Tell the SCSI layer about a BUS RESET.
 */
व्योम sym_xpt_async_bus_reset(काष्ठा sym_hcb *np)
अणु
	म_लिखो_notice("%s: SCSI BUS has been reset.\n", sym_name(np));
	np->s.settle_समय = jअगरfies + sym_driver_setup.settle_delay * HZ;
	np->s.settle_समय_valid = 1;
	अगर (sym_verbose >= 2)
		म_लिखो_info("%s: command processing suspended for %d seconds\n",
			    sym_name(np), sym_driver_setup.settle_delay);
पूर्ण

/*
 *  Choose the more appropriate CAM status अगर 
 *  the IO encountered an extended error.
 */
अटल पूर्णांक sym_xerr_cam_status(पूर्णांक cam_status, पूर्णांक x_status)
अणु
	अगर (x_status) अणु
		अगर (x_status & XE_PARITY_ERR)
			cam_status = DID_PARITY;
		अन्यथा
			cam_status = DID_ERROR;
	पूर्ण
	वापस cam_status;
पूर्ण

/*
 *  Build CAM result क्रम a failed or स्वतः-sensed IO.
 */
व्योम sym_set_cam_result_error(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp, पूर्णांक resid)
अणु
	काष्ठा scsi_cmnd *cmd = cp->cmd;
	u_पूर्णांक cam_status, scsi_status, drv_status;

	drv_status  = 0;
	cam_status  = DID_OK;
	scsi_status = cp->ssss_status;

	अगर (cp->host_flags & HF_SENSE) अणु
		scsi_status = cp->sv_scsi_status;
		resid = cp->sv_resid;
		अगर (sym_verbose && cp->sv_xerr_status)
			sym_prपूर्णांक_xerr(cmd, cp->sv_xerr_status);
		अगर (cp->host_status == HS_COMPLETE &&
		    cp->ssss_status == S_GOOD &&
		    cp->xerr_status == 0) अणु
			cam_status = sym_xerr_cam_status(DID_OK,
							 cp->sv_xerr_status);
			drv_status = DRIVER_SENSE;
			/*
			 *  Bounce back the sense data to user.
			 */
			स_रखो(cmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
			स_नकल(cmd->sense_buffer, cp->sns_bbuf,
			       min(SCSI_SENSE_BUFFERSIZE, SYM_SNS_BBUF_LEN));
#अगर 0
			/*
			 *  If the device reports a UNIT ATTENTION condition 
			 *  due to a RESET condition, we should consider all 
			 *  disconnect CCBs क्रम this unit as पातed.
			 */
			अगर (1) अणु
				u_अक्षर *p;
				p  = (u_अक्षर *) cmd->sense_data;
				अगर (p[0]==0x70 && p[2]==0x6 && p[12]==0x29)
					sym_clear_tasks(np, DID_ABORT,
							cp->target,cp->lun, -1);
			पूर्ण
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			/*
			 * Error वापस from our पूर्णांकernal request sense.  This
			 * is bad: we must clear the contingent allegiance
			 * condition otherwise the device will always वापस
			 * BUSY.  Use a big stick.
			 */
			sym_reset_scsi_target(np, cmd->device->id);
			cam_status = DID_ERROR;
		पूर्ण
	पूर्ण अन्यथा अगर (cp->host_status == HS_COMPLETE) 	/* Bad SCSI status */
		cam_status = DID_OK;
	अन्यथा अगर (cp->host_status == HS_SEL_TIMEOUT)	/* Selection समयout */
		cam_status = DID_NO_CONNECT;
	अन्यथा अगर (cp->host_status == HS_UNEXPECTED)	/* Unexpected BUS FREE*/
		cam_status = DID_ERROR;
	अन्यथा अणु						/* Extended error */
		अगर (sym_verbose) अणु
			sym_prपूर्णांक_addr(cmd, "COMMAND FAILED (%x %x %x).\n",
				cp->host_status, cp->ssss_status,
				cp->xerr_status);
		पूर्ण
		/*
		 *  Set the most appropriate value क्रम CAM status.
		 */
		cam_status = sym_xerr_cam_status(DID_ERROR, cp->xerr_status);
	पूर्ण
	scsi_set_resid(cmd, resid);
	cmd->result = (drv_status << 24) | (cam_status << 16) | scsi_status;
पूर्ण

अटल पूर्णांक sym_scatter(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp, काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक segment;
	पूर्णांक use_sg;

	cp->data_len = 0;

	use_sg = scsi_dma_map(cmd);
	अगर (use_sg > 0) अणु
		काष्ठा scatterlist *sg;
		काष्ठा sym_tcb *tp = &np->target[cp->target];
		काष्ठा sym_tblmove *data;

		अगर (use_sg > SYM_CONF_MAX_SG) अणु
			scsi_dma_unmap(cmd);
			वापस -1;
		पूर्ण

		data = &cp->phys.data[SYM_CONF_MAX_SG - use_sg];

		scsi_क्रम_each_sg(cmd, sg, use_sg, segment) अणु
			dma_addr_t baddr = sg_dma_address(sg);
			अचिन्हित पूर्णांक len = sg_dma_len(sg);

			अगर ((len & 1) && (tp->head.wval & EWS)) अणु
				len++;
				cp->odd_byte_adjusपंचांगent++;
			पूर्ण

			sym_build_sge(np, &data[segment], baddr, len);
			cp->data_len += len;
		पूर्ण
	पूर्ण अन्यथा अणु
		segment = -2;
	पूर्ण

	वापस segment;
पूर्ण

/*
 *  Queue a SCSI command.
 */
अटल पूर्णांक sym_queue_command(काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device *sdev = cmd->device;
	काष्ठा sym_tcb *tp;
	काष्ठा sym_lcb *lp;
	काष्ठा sym_ccb *cp;
	पूर्णांक	order;

	/*
	 *  Retrieve the target descriptor.
	 */
	tp = &np->target[sdev->id];

	/*
	 *  Select tagged/untagged.
	 */
	lp = sym_lp(tp, sdev->lun);
	order = (lp && lp->s.reqtags) ? M_SIMPLE_TAG : 0;

	/*
	 *  Queue the SCSI IO.
	 */
	cp = sym_get_ccb(np, cmd, order);
	अगर (!cp)
		वापस 1;	/* Means resource लघुage */
	sym_queue_scsiio(np, cmd, cp);
	वापस 0;
पूर्ण

/*
 *  Setup buffers and poपूर्णांकers that address the CDB.
 */
अटल अंतरभूत पूर्णांक sym_setup_cdb(काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *cmd, काष्ठा sym_ccb *cp)
अणु
	स_नकल(cp->cdb_buf, cmd->cmnd, cmd->cmd_len);

	cp->phys.cmd.addr = CCB_BA(cp, cdb_buf[0]);
	cp->phys.cmd.size = cpu_to_scr(cmd->cmd_len);

	वापस 0;
पूर्ण

/*
 *  Setup poपूर्णांकers that address the data and start the I/O.
 */
पूर्णांक sym_setup_data_and_start(काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *cmd, काष्ठा sym_ccb *cp)
अणु
	u32 lastp, goalp;
	पूर्णांक dir;

	/*
	 *  Build the CDB.
	 */
	अगर (sym_setup_cdb(np, cmd, cp))
		जाओ out_पात;

	/*
	 *  No direction means no data.
	 */
	dir = cmd->sc_data_direction;
	अगर (dir != DMA_NONE) अणु
		cp->segments = sym_scatter(np, cp, cmd);
		अगर (cp->segments < 0) अणु
			sym_set_cam_status(cmd, DID_ERROR);
			जाओ out_पात;
		पूर्ण

		/*
		 *  No segments means no data.
		 */
		अगर (!cp->segments)
			dir = DMA_NONE;
	पूर्ण अन्यथा अणु
		cp->data_len = 0;
		cp->segments = 0;
	पूर्ण

	/*
	 *  Set the data poपूर्णांकer.
	 */
	चयन (dir) अणु
	हाल DMA_BIसूचीECTIONAL:
		scmd_prपूर्णांकk(KERN_INFO, cmd, "got DMA_BIDIRECTIONAL command");
		sym_set_cam_status(cmd, DID_ERROR);
		जाओ out_पात;
	हाल DMA_TO_DEVICE:
		goalp = SCRIPTA_BA(np, data_out2) + 8;
		lastp = goalp - 8 - (cp->segments * (2*4));
		अवरोध;
	हाल DMA_FROM_DEVICE:
		cp->host_flags |= HF_DATA_IN;
		goalp = SCRIPTA_BA(np, data_in2) + 8;
		lastp = goalp - 8 - (cp->segments * (2*4));
		अवरोध;
	हाल DMA_NONE:
	शेष:
		lastp = goalp = SCRIPTB_BA(np, no_data);
		अवरोध;
	पूर्ण

	/*
	 *  Set all poपूर्णांकers values needed by SCRIPTS.
	 */
	cp->phys.head.lastp = cpu_to_scr(lastp);
	cp->phys.head.savep = cpu_to_scr(lastp);
	cp->startp	    = cp->phys.head.savep;
	cp->goalp	    = cpu_to_scr(goalp);

	/*
	 *  When `#अगरed 1', the code below makes the driver 
	 *  panic on the first attempt to ग_लिखो to a SCSI device.
	 *  It is the first test we want to करो after a driver 
	 *  change that करोes not seem obviously safe. :)
	 */
#अगर 0
	चयन (cp->cdb_buf[0]) अणु
	हाल 0x0A: हाल 0x2A: हाल 0xAA:
		panic("XXXXXXXXXXXXX WRITE NOT YET ALLOWED XXXXXXXXXXXXXX\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	/*
	 *	activate this job.
	 */
	sym_put_start_queue(np, cp);
	वापस 0;

out_पात:
	sym_मुक्त_ccb(np, cp);
	sym_xpt_करोne(np, cmd);
	वापस 0;
पूर्ण


/*
 *  समयr daemon.
 *
 *  Misused to keep the driver running when
 *  पूर्णांकerrupts are not configured correctly.
 */
अटल व्योम sym_समयr(काष्ठा sym_hcb *np)
अणु
	अचिन्हित दीर्घ thisसमय = jअगरfies;

	/*
	 *  Restart the समयr.
	 */
	np->s.समयr.expires = thisसमय + SYM_CONF_TIMER_INTERVAL;
	add_समयr(&np->s.समयr);

	/*
	 *  If we are resetting the ncr, रुको क्रम settle_समय beक्रमe 
	 *  clearing it. Then command processing will be resumed.
	 */
	अगर (np->s.settle_समय_valid) अणु
		अगर (समय_beक्रमe_eq(np->s.settle_समय, thisसमय)) अणु
			अगर (sym_verbose >= 2 )
				prपूर्णांकk("%s: command processing resumed\n",
				       sym_name(np));
			np->s.settle_समय_valid = 0;
		पूर्ण
		वापस;
	पूर्ण

	/*
	 *	Nothing to करो क्रम now, but that may come.
	 */
	अगर (np->s.lastसमय + 4*HZ < thisसमय) अणु
		np->s.lastसमय = thisसमय;
	पूर्ण

#अगर_घोषित SYM_CONF_PCIQ_MAY_MISS_COMPLETIONS
	/*
	 *  Some way-broken PCI bridges may lead to 
	 *  completions being lost when the clearing 
	 *  of the INTFLY flag by the CPU occurs 
	 *  concurrently with the chip raising this flag.
	 *  If this ever happen, lost completions will 
	 * be reaped here.
	 */
	sym_wakeup_करोne(np);
#पूर्ण_अगर
पूर्ण


/*
 *  PCI BUS error handler.
 */
व्योम sym_log_bus_error(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा sym_data *sym_data = shost_priv(shost);
	काष्ठा pci_dev *pdev = sym_data->pdev;
	अचिन्हित लघु pci_sts;
	pci_पढ़ो_config_word(pdev, PCI_STATUS, &pci_sts);
	अगर (pci_sts & 0xf900) अणु
		pci_ग_लिखो_config_word(pdev, PCI_STATUS, pci_sts);
		shost_prपूर्णांकk(KERN_WARNING, shost,
			"PCI bus error: status = 0x%04x\n", pci_sts & 0xf900);
	पूर्ण
पूर्ण

/*
 * queuecommand method.  Entered with the host adapter lock held and
 * पूर्णांकerrupts disabled.
 */
अटल पूर्णांक sym53c8xx_queue_command_lck(काष्ठा scsi_cmnd *cmd,
					व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा sym_hcb *np = SYM_SOFTC_PTR(cmd);
	काष्ठा sym_ucmd *ucp = SYM_UCMD_PTR(cmd);
	पूर्णांक sts = 0;

	cmd->scsi_करोne = करोne;
	स_रखो(ucp, 0, माप(*ucp));

	/*
	 *  Shorten our settle_समय अगर needed क्रम 
	 *  this command not to समय out.
	 */
	अगर (np->s.settle_समय_valid && cmd->request->समयout) अणु
		अचिन्हित दीर्घ tlimit = jअगरfies + cmd->request->समयout;
		tlimit -= SYM_CONF_TIMER_INTERVAL*2;
		अगर (समय_after(np->s.settle_समय, tlimit)) अणु
			np->s.settle_समय = tlimit;
		पूर्ण
	पूर्ण

	अगर (np->s.settle_समय_valid)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	sts = sym_queue_command(np, cmd);
	अगर (sts)
		वापस SCSI_MLQUEUE_HOST_BUSY;
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(sym53c8xx_queue_command)

/*
 *  Linux entry poपूर्णांक of the पूर्णांकerrupt handler.
 */
अटल irqवापस_t sym53c8xx_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा Scsi_Host *shost = dev_id;
	काष्ठा sym_data *sym_data = shost_priv(shost);
	irqवापस_t result;

	/* Aव्योम spinloop trying to handle पूर्णांकerrupts on frozen device */
	अगर (pci_channel_offline(sym_data->pdev))
		वापस IRQ_NONE;

	अगर (DEBUG_FLAGS & DEBUG_TINY) म_लिखो_debug ("[");

	spin_lock(shost->host_lock);
	result = sym_पूर्णांकerrupt(shost);
	spin_unlock(shost->host_lock);

	अगर (DEBUG_FLAGS & DEBUG_TINY) म_लिखो_debug ("]\n");

	वापस result;
पूर्ण

/*
 *  Linux entry poपूर्णांक of the समयr handler
 */
अटल व्योम sym53c8xx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sym_hcb *np = from_समयr(np, t, s.समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(np->s.host->host_lock, flags);
	sym_समयr(np);
	spin_unlock_irqrestore(np->s.host->host_lock, flags);
पूर्ण


/*
 *  What the eh thपढ़ो wants us to perक्रमm.
 */
#घोषणा SYM_EH_ABORT		0
#घोषणा SYM_EH_DEVICE_RESET	1
#घोषणा SYM_EH_BUS_RESET	2
#घोषणा SYM_EH_HOST_RESET	3

/*
 *  Generic method क्रम our eh processing.
 *  The 'op' argument tells what we have to करो.
 */
अटल पूर्णांक sym_eh_handler(पूर्णांक op, अक्षर *opname, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा sym_ucmd *ucmd = SYM_UCMD_PTR(cmd);
	काष्ठा Scsi_Host *shost = cmd->device->host;
	काष्ठा sym_data *sym_data = shost_priv(shost);
	काष्ठा pci_dev *pdev = sym_data->pdev;
	काष्ठा sym_hcb *np = sym_data->ncb;
	SYM_QUEHEAD *qp;
	पूर्णांक cmd_queued = 0;
	पूर्णांक sts = -1;
	काष्ठा completion eh_करोne;

	scmd_prपूर्णांकk(KERN_WARNING, cmd, "%s operation started\n", opname);

	/* We may be in an error condition because the PCI bus
	 * went करोwn. In this हाल, we need to रुको until the
	 * PCI bus is reset, the card is reset, and only then
	 * proceed with the scsi error recovery.  There's no
	 * poपूर्णांक in hurrying; take a leisurely रुको.
	 */
#घोषणा WAIT_FOR_PCI_RECOVERY	35
	अगर (pci_channel_offline(pdev)) अणु
		पूर्णांक finished_reset = 0;
		init_completion(&eh_करोne);
		spin_lock_irq(shost->host_lock);
		/* Make sure we didn't race */
		अगर (pci_channel_offline(pdev)) अणु
			BUG_ON(sym_data->io_reset);
			sym_data->io_reset = &eh_करोne;
		पूर्ण अन्यथा अणु
			finished_reset = 1;
		पूर्ण
		spin_unlock_irq(shost->host_lock);
		अगर (!finished_reset)
			finished_reset = रुको_क्रम_completion_समयout
						(sym_data->io_reset,
						WAIT_FOR_PCI_RECOVERY*HZ);
		spin_lock_irq(shost->host_lock);
		sym_data->io_reset = शून्य;
		spin_unlock_irq(shost->host_lock);
		अगर (!finished_reset)
			वापस SCSI_FAILED;
	पूर्ण

	spin_lock_irq(shost->host_lock);
	/* This one is queued in some place -> to रुको क्रम completion */
	FOR_EACH_QUEUED_ELEMENT(&np->busy_ccbq, qp) अणु
		काष्ठा sym_ccb *cp = sym_que_entry(qp, काष्ठा sym_ccb, link_ccbq);
		अगर (cp->cmd == cmd) अणु
			cmd_queued = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Try to proceed the operation we have been asked क्रम */
	sts = -1;
	चयन(op) अणु
	हाल SYM_EH_ABORT:
		sts = sym_पात_scsiio(np, cmd, 1);
		अवरोध;
	हाल SYM_EH_DEVICE_RESET:
		sts = sym_reset_scsi_target(np, cmd->device->id);
		अवरोध;
	हाल SYM_EH_BUS_RESET:
		sym_reset_scsi_bus(np, 1);
		sts = 0;
		अवरोध;
	हाल SYM_EH_HOST_RESET:
		sym_reset_scsi_bus(np, 0);
		sym_start_up(shost, 1);
		sts = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* On error, restore everything and cross fingers :) */
	अगर (sts)
		cmd_queued = 0;

	अगर (cmd_queued) अणु
		init_completion(&eh_करोne);
		ucmd->eh_करोne = &eh_करोne;
		spin_unlock_irq(shost->host_lock);
		अगर (!रुको_क्रम_completion_समयout(&eh_करोne, 5*HZ)) अणु
			ucmd->eh_करोne = शून्य;
			sts = -2;
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock_irq(shost->host_lock);
	पूर्ण

	dev_warn(&cmd->device->sdev_gendev, "%s operation %s.\n", opname,
			sts==0 ? "complete" :sts==-2 ? "timed-out" : "failed");
	वापस sts ? SCSI_FAILED : SCSI_SUCCESS;
पूर्ण


/*
 * Error handlers called from the eh thपढ़ो (one thपढ़ो per HBA).
 */
अटल पूर्णांक sym53c8xx_eh_पात_handler(काष्ठा scsi_cmnd *cmd)
अणु
	वापस sym_eh_handler(SYM_EH_ABORT, "ABORT", cmd);
पूर्ण

अटल पूर्णांक sym53c8xx_eh_device_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	वापस sym_eh_handler(SYM_EH_DEVICE_RESET, "DEVICE RESET", cmd);
पूर्ण

अटल पूर्णांक sym53c8xx_eh_bus_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	वापस sym_eh_handler(SYM_EH_BUS_RESET, "BUS RESET", cmd);
पूर्ण

अटल पूर्णांक sym53c8xx_eh_host_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	वापस sym_eh_handler(SYM_EH_HOST_RESET, "HOST RESET", cmd);
पूर्ण

/*
 *  Tune device queuing depth, according to various limits.
 */
अटल व्योम sym_tune_dev_queuing(काष्ठा sym_tcb *tp, पूर्णांक lun, u_लघु reqtags)
अणु
	काष्ठा sym_lcb *lp = sym_lp(tp, lun);
	u_लघु	oldtags;

	अगर (!lp)
		वापस;

	oldtags = lp->s.reqtags;

	अगर (reqtags > lp->s.scdev_depth)
		reqtags = lp->s.scdev_depth;

	lp->s.reqtags     = reqtags;

	अगर (reqtags != oldtags) अणु
		dev_info(&tp->starget->dev,
		         "tagged command queuing %s, command queue depth %d.\n",
		          lp->s.reqtags ? "enabled" : "disabled", reqtags);
	पूर्ण
पूर्ण

अटल पूर्णांक sym53c8xx_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा sym_hcb *np = sym_get_hcb(sdev->host);
	काष्ठा sym_tcb *tp = &np->target[sdev->id];
	काष्ठा sym_lcb *lp;
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	अगर (sdev->id >= SYM_CONF_MAX_TARGET || sdev->lun >= SYM_CONF_MAX_LUN)
		वापस -ENXIO;

	spin_lock_irqsave(np->s.host->host_lock, flags);

	/*
	 * Fail the device init अगर the device is flagged NOSCAN at BOOT in
	 * the NVRAM.  This may speed up boot and मुख्यtain coherency with
	 * BIOS device numbering.  Clearing the flag allows the user to
	 * rescan skipped devices later.  We also वापस an error क्रम
	 * devices not flagged क्रम SCAN LUNS in the NVRAM since some single
	 * lun devices behave badly when asked क्रम a non zero LUN.
	 */

	अगर (tp->usrflags & SYM_SCAN_BOOT_DISABLED) अणु
		tp->usrflags &= ~SYM_SCAN_BOOT_DISABLED;
		starget_prपूर्णांकk(KERN_INFO, sdev->sdev_target,
				"Scan at boot disabled in NVRAM\n");
		error = -ENXIO;
		जाओ out;
	पूर्ण

	अगर (tp->usrflags & SYM_SCAN_LUNS_DISABLED) अणु
		अगर (sdev->lun != 0) अणु
			error = -ENXIO;
			जाओ out;
		पूर्ण
		starget_prपूर्णांकk(KERN_INFO, sdev->sdev_target,
				"Multiple LUNs disabled in NVRAM\n");
	पूर्ण

	lp = sym_alloc_lcb(np, sdev->id, sdev->lun);
	अगर (!lp) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर (tp->nlcb == 1)
		tp->starget = sdev->sdev_target;

	spi_min_period(tp->starget) = tp->usr_period;
	spi_max_width(tp->starget) = tp->usr_width;

	error = 0;
out:
	spin_unlock_irqrestore(np->s.host->host_lock, flags);

	वापस error;
पूर्ण

/*
 * Linux entry poपूर्णांक क्रम device queue sizing.
 */
अटल पूर्णांक sym53c8xx_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा sym_hcb *np = sym_get_hcb(sdev->host);
	काष्ठा sym_tcb *tp = &np->target[sdev->id];
	काष्ठा sym_lcb *lp = sym_lp(tp, sdev->lun);
	पूर्णांक reqtags, depth_to_use;

	/*
	 *  Get user flags.
	 */
	lp->curr_flags = lp->user_flags;

	/*
	 *  Select queue depth from driver setup.
	 *  Do not use more than configured by user.
	 *  Use at least 1.
	 *  Do not use more than our maximum.
	 */
	reqtags = sym_driver_setup.max_tag;
	अगर (reqtags > tp->usrtags)
		reqtags = tp->usrtags;
	अगर (!sdev->tagged_supported)
		reqtags = 0;
	अगर (reqtags > SYM_CONF_MAX_TAG)
		reqtags = SYM_CONF_MAX_TAG;
	depth_to_use = reqtags ? reqtags : 1;
	scsi_change_queue_depth(sdev, depth_to_use);
	lp->s.scdev_depth = depth_to_use;
	sym_tune_dev_queuing(tp, sdev->lun, reqtags);

	अगर (!spi_initial_dv(sdev->sdev_target))
		spi_dv_device(sdev);

	वापस 0;
पूर्ण

अटल व्योम sym53c8xx_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	काष्ठा sym_hcb *np = sym_get_hcb(sdev->host);
	काष्ठा sym_tcb *tp = &np->target[sdev->id];
	काष्ठा sym_lcb *lp = sym_lp(tp, sdev->lun);
	अचिन्हित दीर्घ flags;

	/* अगर slave_alloc वापसed beक्रमe allocating a sym_lcb, वापस */
	अगर (!lp)
		वापस;

	spin_lock_irqsave(np->s.host->host_lock, flags);

	अगर (lp->busy_itlq || lp->busy_itl) अणु
		/*
		 * This really shouldn't happen, but we can't वापस an error
		 * so let's try to stop all on-going I/O.
		 */
		starget_prपूर्णांकk(KERN_WARNING, tp->starget,
			       "Removing busy LCB (%d)\n", (u8)sdev->lun);
		sym_reset_scsi_bus(np, 1);
	पूर्ण

	अगर (sym_मुक्त_lcb(np, sdev->id, sdev->lun) == 0) अणु
		/*
		 * It was the last unit क्रम this target.
		 */
		tp->head.sval        = 0;
		tp->head.wval        = np->rv_scntl3;
		tp->head.uval        = 0;
		tp->tgoal.check_nego = 1;
		tp->starget	     = शून्य;
	पूर्ण

	spin_unlock_irqrestore(np->s.host->host_lock, flags);
पूर्ण

/*
 *  Linux entry poपूर्णांक क्रम info() function
 */
अटल स्थिर अक्षर *sym53c8xx_info (काष्ठा Scsi_Host *host)
अणु
	वापस SYM_DRIVER_NAME;
पूर्ण


#अगर_घोषित SYM_LINUX_PROC_INFO_SUPPORT
/*
 *  Proc file प्रणाली stuff
 *
 *  A पढ़ो operation वापसs adapter inक्रमmation.
 *  A ग_लिखो operation is a control command.
 *  The string is parsed in the driver code and the command is passed 
 *  to the sym_usercmd() function.
 */

#अगर_घोषित SYM_LINUX_USER_COMMAND_SUPPORT

काष्ठा	sym_usrcmd अणु
	u_दीर्घ	target;
	u_दीर्घ	lun;
	u_दीर्घ	data;
	u_दीर्घ	cmd;
पूर्ण;

#घोषणा UC_SETSYNC      10
#घोषणा UC_SETTAGS	11
#घोषणा UC_SETDEBUG	12
#घोषणा UC_SETWIDE	14
#घोषणा UC_SETFLAG	15
#घोषणा UC_SETVERBOSE	17
#घोषणा UC_RESETDEV	18
#घोषणा UC_CLEARDEV	19

अटल व्योम sym_exec_user_command (काष्ठा sym_hcb *np, काष्ठा sym_usrcmd *uc)
अणु
	काष्ठा sym_tcb *tp;
	पूर्णांक t, l;

	चयन (uc->cmd) अणु
	हाल 0: वापस;

#अगर_घोषित SYM_LINUX_DEBUG_CONTROL_SUPPORT
	हाल UC_SETDEBUG:
		sym_debug_flags = uc->data;
		अवरोध;
#पूर्ण_अगर
	हाल UC_SETVERBOSE:
		np->verbose = uc->data;
		अवरोध;
	शेष:
		/*
		 * We assume that other commands apply to tarमाला_लो.
		 * This should always be the हाल and aव्योम the below 
		 * 4 lines to be repeated 6 बार.
		 */
		क्रम (t = 0; t < SYM_CONF_MAX_TARGET; t++) अणु
			अगर (!((uc->target >> t) & 1))
				जारी;
			tp = &np->target[t];
			अगर (!tp->nlcb)
				जारी;

			चयन (uc->cmd) अणु

			हाल UC_SETSYNC:
				अगर (!uc->data || uc->data >= 255) अणु
					tp->tgoal.iu = tp->tgoal.dt =
						tp->tgoal.qas = 0;
					tp->tgoal.offset = 0;
				पूर्ण अन्यथा अगर (uc->data <= 9 && np->minsync_dt) अणु
					अगर (uc->data < np->minsync_dt)
						uc->data = np->minsync_dt;
					tp->tgoal.iu = tp->tgoal.dt =
						tp->tgoal.qas = 1;
					tp->tgoal.width = 1;
					tp->tgoal.period = uc->data;
					tp->tgoal.offset = np->maxoffs_dt;
				पूर्ण अन्यथा अणु
					अगर (uc->data < np->minsync)
						uc->data = np->minsync;
					tp->tgoal.iu = tp->tgoal.dt =
						tp->tgoal.qas = 0;
					tp->tgoal.period = uc->data;
					tp->tgoal.offset = np->maxoffs;
				पूर्ण
				tp->tgoal.check_nego = 1;
				अवरोध;
			हाल UC_SETWIDE:
				tp->tgoal.width = uc->data ? 1 : 0;
				tp->tgoal.check_nego = 1;
				अवरोध;
			हाल UC_SETTAGS:
				क्रम (l = 0; l < SYM_CONF_MAX_LUN; l++)
					sym_tune_dev_queuing(tp, l, uc->data);
				अवरोध;
			हाल UC_RESETDEV:
				tp->to_reset = 1;
				np->istat_sem = SEM;
				OUTB(np, nc_istat, SIGP|SEM);
				अवरोध;
			हाल UC_CLEARDEV:
				क्रम (l = 0; l < SYM_CONF_MAX_LUN; l++) अणु
					काष्ठा sym_lcb *lp = sym_lp(tp, l);
					अगर (lp) lp->to_clear = 1;
				पूर्ण
				np->istat_sem = SEM;
				OUTB(np, nc_istat, SIGP|SEM);
				अवरोध;
			हाल UC_SETFLAG:
				tp->usrflags = uc->data;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sym_skip_spaces(अक्षर *ptr, पूर्णांक len)
अणु
	पूर्णांक cnt, c;

	क्रम (cnt = len; cnt > 0 && (c = *ptr++) && है_खाली(c); cnt--);

	वापस (len - cnt);
पूर्ण

अटल पूर्णांक get_पूर्णांक_arg(अक्षर *ptr, पूर्णांक len, u_दीर्घ *pv)
अणु
	अक्षर *end;

	*pv = simple_म_से_अदीर्घ(ptr, &end, 10);
	वापस (end - ptr);
पूर्ण

अटल पूर्णांक is_keyword(अक्षर *ptr, पूर्णांक len, अक्षर *verb)
अणु
	पूर्णांक verb_len = म_माप(verb);

	अगर (len >= verb_len && !स_भेद(verb, ptr, verb_len))
		वापस verb_len;
	अन्यथा
		वापस 0;
पूर्ण

#घोषणा SKIP_SPACES(ptr, len)						\
	अगर ((arg_len = sym_skip_spaces(ptr, len)) < 1)			\
		वापस -EINVAL;						\
	ptr += arg_len; len -= arg_len;

#घोषणा GET_INT_ARG(ptr, len, v)					\
	अगर (!(arg_len = get_पूर्णांक_arg(ptr, len, &(v))))			\
		वापस -EINVAL;						\
	ptr += arg_len; len -= arg_len;


/*
 * Parse a control command
 */

अटल पूर्णांक sym_user_command(काष्ठा Scsi_Host *shost, अक्षर *buffer, पूर्णांक length)
अणु
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	अक्षर *ptr	= buffer;
	पूर्णांक len		= length;
	काष्ठा sym_usrcmd cmd, *uc = &cmd;
	पूर्णांक		arg_len;
	u_दीर्घ 		target;

	स_रखो(uc, 0, माप(*uc));

	अगर (len > 0 && ptr[len-1] == '\n')
		--len;

	अगर	((arg_len = is_keyword(ptr, len, "setsync")) != 0)
		uc->cmd = UC_SETSYNC;
	अन्यथा अगर	((arg_len = is_keyword(ptr, len, "settags")) != 0)
		uc->cmd = UC_SETTAGS;
	अन्यथा अगर	((arg_len = is_keyword(ptr, len, "setverbose")) != 0)
		uc->cmd = UC_SETVERBOSE;
	अन्यथा अगर	((arg_len = is_keyword(ptr, len, "setwide")) != 0)
		uc->cmd = UC_SETWIDE;
#अगर_घोषित SYM_LINUX_DEBUG_CONTROL_SUPPORT
	अन्यथा अगर	((arg_len = is_keyword(ptr, len, "setdebug")) != 0)
		uc->cmd = UC_SETDEBUG;
#पूर्ण_अगर
	अन्यथा अगर	((arg_len = is_keyword(ptr, len, "setflag")) != 0)
		uc->cmd = UC_SETFLAG;
	अन्यथा अगर	((arg_len = is_keyword(ptr, len, "resetdev")) != 0)
		uc->cmd = UC_RESETDEV;
	अन्यथा अगर	((arg_len = is_keyword(ptr, len, "cleardev")) != 0)
		uc->cmd = UC_CLEARDEV;
	अन्यथा
		arg_len = 0;

#अगर_घोषित DEBUG_PROC_INFO
prपूर्णांकk("sym_user_command: arg_len=%d, cmd=%ld\n", arg_len, uc->cmd);
#पूर्ण_अगर

	अगर (!arg_len)
		वापस -EINVAL;
	ptr += arg_len; len -= arg_len;

	चयन(uc->cmd) अणु
	हाल UC_SETSYNC:
	हाल UC_SETTAGS:
	हाल UC_SETWIDE:
	हाल UC_SETFLAG:
	हाल UC_RESETDEV:
	हाल UC_CLEARDEV:
		SKIP_SPACES(ptr, len);
		अगर ((arg_len = is_keyword(ptr, len, "all")) != 0) अणु
			ptr += arg_len; len -= arg_len;
			uc->target = ~0;
		पूर्ण अन्यथा अणु
			GET_INT_ARG(ptr, len, target);
			uc->target = (1<<target);
#अगर_घोषित DEBUG_PROC_INFO
prपूर्णांकk("sym_user_command: target=%ld\n", target);
#पूर्ण_अगर
		पूर्ण
		अवरोध;
	पूर्ण

	चयन(uc->cmd) अणु
	हाल UC_SETVERBOSE:
	हाल UC_SETSYNC:
	हाल UC_SETTAGS:
	हाल UC_SETWIDE:
		SKIP_SPACES(ptr, len);
		GET_INT_ARG(ptr, len, uc->data);
#अगर_घोषित DEBUG_PROC_INFO
prपूर्णांकk("sym_user_command: data=%ld\n", uc->data);
#पूर्ण_अगर
		अवरोध;
#अगर_घोषित SYM_LINUX_DEBUG_CONTROL_SUPPORT
	हाल UC_SETDEBUG:
		जबतक (len > 0) अणु
			SKIP_SPACES(ptr, len);
			अगर	((arg_len = is_keyword(ptr, len, "alloc")))
				uc->data |= DEBUG_ALLOC;
			अन्यथा अगर	((arg_len = is_keyword(ptr, len, "phase")))
				uc->data |= DEBUG_PHASE;
			अन्यथा अगर	((arg_len = is_keyword(ptr, len, "queue")))
				uc->data |= DEBUG_QUEUE;
			अन्यथा अगर	((arg_len = is_keyword(ptr, len, "result")))
				uc->data |= DEBUG_RESULT;
			अन्यथा अगर	((arg_len = is_keyword(ptr, len, "scatter")))
				uc->data |= DEBUG_SCATTER;
			अन्यथा अगर	((arg_len = is_keyword(ptr, len, "script")))
				uc->data |= DEBUG_SCRIPT;
			अन्यथा अगर	((arg_len = is_keyword(ptr, len, "tiny")))
				uc->data |= DEBUG_TINY;
			अन्यथा अगर	((arg_len = is_keyword(ptr, len, "timing")))
				uc->data |= DEBUG_TIMING;
			अन्यथा अगर	((arg_len = is_keyword(ptr, len, "nego")))
				uc->data |= DEBUG_NEGO;
			अन्यथा अगर	((arg_len = is_keyword(ptr, len, "tags")))
				uc->data |= DEBUG_TAGS;
			अन्यथा अगर	((arg_len = is_keyword(ptr, len, "pointer")))
				uc->data |= DEBUG_POINTER;
			अन्यथा
				वापस -EINVAL;
			ptr += arg_len; len -= arg_len;
		पूर्ण
#अगर_घोषित DEBUG_PROC_INFO
prपूर्णांकk("sym_user_command: data=%ld\n", uc->data);
#पूर्ण_अगर
		अवरोध;
#पूर्ण_अगर /* SYM_LINUX_DEBUG_CONTROL_SUPPORT */
	हाल UC_SETFLAG:
		जबतक (len > 0) अणु
			SKIP_SPACES(ptr, len);
			अगर	((arg_len = is_keyword(ptr, len, "no_disc")))
				uc->data &= ~SYM_DISC_ENABLED;
			अन्यथा
				वापस -EINVAL;
			ptr += arg_len; len -= arg_len;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (len)
		वापस -EINVAL;
	अन्यथा अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(shost->host_lock, flags);
		sym_exec_user_command(np, uc);
		spin_unlock_irqrestore(shost->host_lock, flags);
	पूर्ण
	वापस length;
पूर्ण

#पूर्ण_अगर	/* SYM_LINUX_USER_COMMAND_SUPPORT */


/*
 *  Copy क्रमmatted inक्रमmation पूर्णांकo the input buffer.
 */
अटल पूर्णांक sym_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
#अगर_घोषित SYM_LINUX_USER_INFO_SUPPORT
	काष्ठा sym_data *sym_data = shost_priv(shost);
	काष्ठा pci_dev *pdev = sym_data->pdev;
	काष्ठा sym_hcb *np = sym_data->ncb;

	seq_म_लिखो(m, "Chip " NAME53C "%s, device id 0x%x, "
		 "revision id 0x%x\n", np->s.chip_name,
		 pdev->device, pdev->revision);
	seq_म_लिखो(m, "At PCI address %s, IRQ %u\n",
			 pci_name(pdev), pdev->irq);
	seq_म_लिखो(m, "Min. period factor %d, %s SCSI BUS%s\n",
		 (पूर्णांक) (np->minsync_dt ? np->minsync_dt : np->minsync),
		 np->maxwide ? "Wide" : "Narrow",
		 np->minsync_dt ? ", DT capable" : "");

	seq_म_लिखो(m, "Max. started commands %d, "
		 "max. commands per LUN %d\n",
		 SYM_CONF_MAX_START, SYM_CONF_MAX_TAG);

	वापस 0;
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर /* SYM_LINUX_USER_INFO_SUPPORT */
पूर्ण

#पूर्ण_अगर /* SYM_LINUX_PROC_INFO_SUPPORT */

/*
 * Free resources claimed by sym_iomap_device().  Note that
 * sym_मुक्त_resources() should be used instead of this function after calling
 * sym_attach().
 */
अटल व्योम sym_iounmap_device(काष्ठा sym_device *device)
अणु
	अगर (device->s.ioaddr)
		pci_iounmap(device->pdev, device->s.ioaddr);
	अगर (device->s.ramaddr)
		pci_iounmap(device->pdev, device->s.ramaddr);
पूर्ण

/*
 *	Free controller resources.
 */
अटल व्योम sym_मुक्त_resources(काष्ठा sym_hcb *np, काष्ठा pci_dev *pdev,
		पूर्णांक करो_मुक्त_irq)
अणु
	/*
	 *  Free O/S specअगरic resources.
	 */
	अगर (करो_मुक्त_irq)
		मुक्त_irq(pdev->irq, np->s.host);
	अगर (np->s.ioaddr)
		pci_iounmap(pdev, np->s.ioaddr);
	अगर (np->s.ramaddr)
		pci_iounmap(pdev, np->s.ramaddr);
	/*
	 *  Free O/S independent resources.
	 */
	sym_hcb_मुक्त(np);

	sym_mमुक्त_dma(np, माप(*np), "HCB");
पूर्ण

/*
 *  Host attach and initialisations.
 *
 *  Allocate host data and ncb काष्ठाure.
 *  Remap MMIO region.
 *  Do chip initialization.
 *  If all is OK, install पूर्णांकerrupt handling and
 *  start the समयr daemon.
 */
अटल काष्ठा Scsi_Host *sym_attach(काष्ठा scsi_host_ढाँचा *tpnt, पूर्णांक unit,
				    काष्ठा sym_device *dev)
अणु
	काष्ठा sym_data *sym_data;
	काष्ठा sym_hcb *np = शून्य;
	काष्ठा Scsi_Host *shost = शून्य;
	काष्ठा pci_dev *pdev = dev->pdev;
	अचिन्हित दीर्घ flags;
	काष्ठा sym_fw *fw;
	पूर्णांक करो_मुक्त_irq = 0;

	prपूर्णांकk(KERN_INFO "sym%d: <%s> rev 0x%x at pci %s irq %u\n",
		unit, dev->chip.name, pdev->revision, pci_name(pdev),
		pdev->irq);

	/*
	 *  Get the firmware क्रम this chip.
	 */
	fw = sym_find_firmware(&dev->chip);
	अगर (!fw)
		जाओ attach_failed;

	shost = scsi_host_alloc(tpnt, माप(*sym_data));
	अगर (!shost)
		जाओ attach_failed;
	sym_data = shost_priv(shost);

	/*
	 *  Allocate immediately the host control block, 
	 *  since we are only expecting to succeed. :)
	 *  We keep track in the HCB of all the resources that 
	 *  are to be released on error.
	 */
	np = __sym_सुस्मृति_dma(&pdev->dev, माप(*np), "HCB");
	अगर (!np)
		जाओ attach_failed;
	np->bus_dmat = &pdev->dev; /* Result in 1 DMA pool per HBA */
	sym_data->ncb = np;
	sym_data->pdev = pdev;
	np->s.host = shost;

	pci_set_drvdata(pdev, shost);

	/*
	 *  Copy some useful infos to the HCB.
	 */
	np->hcb_ba	= vtobus(np);
	np->verbose	= sym_driver_setup.verbose;
	np->s.unit	= unit;
	np->features	= dev->chip.features;
	np->घड़ी_भागn	= dev->chip.nr_भागisor;
	np->maxoffs	= dev->chip.offset_max;
	np->maxburst	= dev->chip.burst_max;
	np->myaddr	= dev->host_id;
	np->mmio_ba	= (u32)dev->mmio_base;
	np->ram_ba	= (u32)dev->ram_base;
	np->s.ioaddr	= dev->s.ioaddr;
	np->s.ramaddr	= dev->s.ramaddr;

	/*
	 *  Edit its name.
	 */
	strlcpy(np->s.chip_name, dev->chip.name, माप(np->s.chip_name));
	प्र_लिखो(np->s.inst_name, "sym%d", np->s.unit);

	अगर ((SYM_CONF_DMA_ADDRESSING_MODE > 0) && (np->features & FE_DAC) &&
			!dma_set_mask(&pdev->dev, DMA_DAC_MASK)) अणु
		set_dac(np);
	पूर्ण अन्यथा अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		म_लिखो_warning("%s: No suitable DMA available\n", sym_name(np));
		जाओ attach_failed;
	पूर्ण

	अगर (sym_hcb_attach(shost, fw, dev->nvram))
		जाओ attach_failed;

	/*
	 *  Install the पूर्णांकerrupt handler.
	 *  If we synchonize the C code with SCRIPTS on पूर्णांकerrupt, 
	 *  we करो not want to share the INTR line at all.
	 */
	अगर (request_irq(pdev->irq, sym53c8xx_पूर्णांकr, IRQF_SHARED, NAME53C8XX,
			shost)) अणु
		म_लिखो_err("%s: request irq %u failure\n",
			sym_name(np), pdev->irq);
		जाओ attach_failed;
	पूर्ण
	करो_मुक्त_irq = 1;

	/*
	 *  After SCSI devices have been खोलोed, we cannot
	 *  reset the bus safely, so we करो it here.
	 */
	spin_lock_irqsave(shost->host_lock, flags);
	अगर (sym_reset_scsi_bus(np, 0))
		जाओ reset_failed;

	/*
	 *  Start the SCRIPTS.
	 */
	sym_start_up(shost, 1);

	/*
	 *  Start the समयr daemon
	 */
	समयr_setup(&np->s.समयr, sym53c8xx_समयr, 0);
	np->s.lastसमय=0;
	sym_समयr (np);

	/*
	 *  Fill Linux host instance काष्ठाure
	 *  and वापस success.
	 */
	shost->max_channel	= 0;
	shost->this_id		= np->myaddr;
	shost->max_id		= np->maxwide ? 16 : 8;
	shost->max_lun		= SYM_CONF_MAX_LUN;
	shost->unique_id	= pci_resource_start(pdev, 0);
	shost->cmd_per_lun	= SYM_CONF_MAX_TAG;
	shost->can_queue	= (SYM_CONF_MAX_START-2);
	shost->sg_tablesize	= SYM_CONF_MAX_SG;
	shost->max_cmd_len	= 16;
	BUG_ON(sym2_transport_ढाँचा == शून्य);
	shost->transportt	= sym2_transport_ढाँचा;

	/* 53c896 rev 1 errata: DMA may not cross 16MB boundary */
	अगर (pdev->device == PCI_DEVICE_ID_NCR_53C896 && pdev->revision < 2)
		shost->dma_boundary = 0xFFFFFF;

	spin_unlock_irqrestore(shost->host_lock, flags);

	वापस shost;

 reset_failed:
	म_लिखो_err("%s: FATAL ERROR: CHECK SCSI BUS - CABLES, "
		   "TERMINATION, DEVICE POWER etc.!\n", sym_name(np));
	spin_unlock_irqrestore(shost->host_lock, flags);
 attach_failed:
	म_लिखो_info("sym%d: giving up ...\n", unit);
	अगर (np)
		sym_मुक्त_resources(np, pdev, करो_मुक्त_irq);
	अन्यथा
		sym_iounmap_device(dev);
	अगर (shost)
		scsi_host_put(shost);

	वापस शून्य;
पूर्ण


/*
 *    Detect and try to पढ़ो SYMBIOS and TEKRAM NVRAM.
 */
#अगर SYM_CONF_NVRAM_SUPPORT
अटल व्योम sym_get_nvram(काष्ठा sym_device *devp, काष्ठा sym_nvram *nvp)
अणु
	devp->nvram = nvp;
	nvp->type = 0;

	sym_पढ़ो_nvram(devp, nvp);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम sym_get_nvram(काष्ठा sym_device *devp, काष्ठा sym_nvram *nvp)
अणु
पूर्ण
#पूर्ण_अगर	/* SYM_CONF_NVRAM_SUPPORT */

अटल पूर्णांक sym_check_supported(काष्ठा sym_device *device)
अणु
	काष्ठा sym_chip *chip;
	काष्ठा pci_dev *pdev = device->pdev;
	अचिन्हित दीर्घ io_port = pci_resource_start(pdev, 0);
	पूर्णांक i;

	/*
	 *  If user excluded this chip, करो not initialize it.
	 *  I hate this code so much.  Must समाप्त it.
	 */
	अगर (io_port) अणु
		क्रम (i = 0 ; i < 8 ; i++) अणु
			अगर (sym_driver_setup.excludes[i] == io_port)
				वापस -ENODEV;
		पूर्ण
	पूर्ण

	/*
	 * Check अगर the chip is supported.  Then copy the chip description
	 * to our device काष्ठाure so we can make it match the actual device
	 * and options.
	 */
	chip = sym_lookup_chip_table(pdev->device, pdev->revision);
	अगर (!chip) अणु
		dev_info(&pdev->dev, "device not supported\n");
		वापस -ENODEV;
	पूर्ण
	स_नकल(&device->chip, chip, माप(device->chip));

	वापस 0;
पूर्ण

/*
 * Ignore Symbios chips controlled by various RAID controllers.
 * These controllers set value 0x52414944 at RAM end - 16.
 */
अटल पूर्णांक sym_check_raid(काष्ठा sym_device *device)
अणु
	अचिन्हित पूर्णांक ram_size, ram_val;

	अगर (!device->s.ramaddr)
		वापस 0;

	अगर (device->chip.features & FE_RAM8K)
		ram_size = 8192;
	अन्यथा
		ram_size = 4096;

	ram_val = पढ़ोl(device->s.ramaddr + ram_size - 16);
	अगर (ram_val != 0x52414944)
		वापस 0;

	dev_info(&device->pdev->dev,
			"not initializing, driven by RAID controller.\n");
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक sym_set_workarounds(काष्ठा sym_device *device)
अणु
	काष्ठा sym_chip *chip = &device->chip;
	काष्ठा pci_dev *pdev = device->pdev;
	u_लघु status_reg;

	/*
	 *  (ITEM 12 of a DEL about the 896 I haven't yet).
	 *  We must ensure the chip will use WRITE AND INVALIDATE.
	 *  The revision number limit is क्रम now arbitrary.
	 */
	अगर (pdev->device == PCI_DEVICE_ID_NCR_53C896 && pdev->revision < 0x4) अणु
		chip->features	|= (FE_WRIE | FE_CLSE);
	पूर्ण

	/* If the chip can करो Memory Write Invalidate, enable it */
	अगर (chip->features & FE_WRIE) अणु
		अगर (pci_set_mwi(pdev))
			वापस -ENODEV;
	पूर्ण

	/*
	 *  Work around क्रम errant bit in 895A. The 66Mhz
	 *  capable bit is set erroneously. Clear this bit.
	 *  (Item 1 DEL 533)
	 *
	 *  Make sure Config space and Features agree.
	 *
	 *  Recall: ग_लिखोs are not normal to status रेजिस्टर -
	 *  ग_लिखो a 1 to clear and a 0 to leave unchanged.
	 *  Can only reset bits.
	 */
	pci_पढ़ो_config_word(pdev, PCI_STATUS, &status_reg);
	अगर (chip->features & FE_66MHZ) अणु
		अगर (!(status_reg & PCI_STATUS_66MHZ))
			chip->features &= ~FE_66MHZ;
	पूर्ण अन्यथा अणु
		अगर (status_reg & PCI_STATUS_66MHZ) अणु
			status_reg = PCI_STATUS_66MHZ;
			pci_ग_लिखो_config_word(pdev, PCI_STATUS, status_reg);
			pci_पढ़ो_config_word(pdev, PCI_STATUS, &status_reg);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Map HBA रेजिस्टरs and on-chip SRAM (अगर present).
 */
अटल पूर्णांक sym_iomap_device(काष्ठा sym_device *device)
अणु
	काष्ठा pci_dev *pdev = device->pdev;
	काष्ठा pci_bus_region bus_addr;
	पूर्णांक i = 2;

	pcibios_resource_to_bus(pdev->bus, &bus_addr, &pdev->resource[1]);
	device->mmio_base = bus_addr.start;

	अगर (device->chip.features & FE_RAM) अणु
		/*
		 * If the BAR is 64-bit, resource 2 will be occupied by the
		 * upper 32 bits
		 */
		अगर (!pdev->resource[i].flags)
			i++;
		pcibios_resource_to_bus(pdev->bus, &bus_addr,
					&pdev->resource[i]);
		device->ram_base = bus_addr.start;
	पूर्ण

#अगर_घोषित CONFIG_SCSI_SYM53C8XX_MMIO
	अगर (device->mmio_base)
		device->s.ioaddr = pci_iomap(pdev, 1,
						pci_resource_len(pdev, 1));
#पूर्ण_अगर
	अगर (!device->s.ioaddr)
		device->s.ioaddr = pci_iomap(pdev, 0,
						pci_resource_len(pdev, 0));
	अगर (!device->s.ioaddr) अणु
		dev_err(&pdev->dev, "could not map registers; giving up.\n");
		वापस -EIO;
	पूर्ण
	अगर (device->ram_base) अणु
		device->s.ramaddr = pci_iomap(pdev, i,
						pci_resource_len(pdev, i));
		अगर (!device->s.ramaddr) अणु
			dev_warn(&pdev->dev,
				"could not map SRAM; continuing anyway.\n");
			device->ram_base = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The NCR PQS and PDS cards are स्थिरructed as a DEC bridge
 * behind which sits a proprietary NCR memory controller and
 * either four or two 53c875s as separate devices.  We can tell
 * अगर an 875 is part of a PQS/PDS or not since अगर it is, it will
 * be on the same bus as the memory controller.  In its usual
 * mode of operation, the 875s are slaved to the memory
 * controller क्रम all transfers.  To operate with the Linux
 * driver, the memory controller is disabled and the 875s
 * मुक्तd to function independently.  The only wrinkle is that
 * the preset SCSI ID (which may be zero) must be पढ़ो in from
 * a special configuration space रेजिस्टर of the 875.
 */
अटल व्योम sym_config_pqs(काष्ठा pci_dev *pdev, काष्ठा sym_device *sym_dev)
अणु
	पूर्णांक slot;
	u8 पंचांगp;

	क्रम (slot = 0; slot < 256; slot++) अणु
		काष्ठा pci_dev *memc = pci_get_slot(pdev->bus, slot);

		अगर (!memc || memc->venकरोr != 0x101a || memc->device == 0x0009) अणु
			pci_dev_put(memc);
			जारी;
		पूर्ण

		/* bit 1: allow inभागidual 875 configuration */
		pci_पढ़ो_config_byte(memc, 0x44, &पंचांगp);
		अगर ((पंचांगp & 0x2) == 0) अणु
			पंचांगp |= 0x2;
			pci_ग_लिखो_config_byte(memc, 0x44, पंचांगp);
		पूर्ण

		/* bit 2: drive inभागidual 875 पूर्णांकerrupts to the bus */
		pci_पढ़ो_config_byte(memc, 0x45, &पंचांगp);
		अगर ((पंचांगp & 0x4) == 0) अणु
			पंचांगp |= 0x4;
			pci_ग_लिखो_config_byte(memc, 0x45, पंचांगp);
		पूर्ण

		pci_dev_put(memc);
		अवरोध;
	पूर्ण

	pci_पढ़ो_config_byte(pdev, 0x84, &पंचांगp);
	sym_dev->host_id = पंचांगp;
पूर्ण

/*
 *  Called beक्रमe unloading the module.
 *  Detach the host.
 *  We have to मुक्त resources and halt the NCR chip.
 */
अटल पूर्णांक sym_detach(काष्ठा Scsi_Host *shost, काष्ठा pci_dev *pdev)
अणु
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	prपूर्णांकk("%s: detaching ...\n", sym_name(np));

	del_समयr_sync(&np->s.समयr);

	/*
	 * Reset NCR chip.
	 * We should use sym_soft_reset(), but we करोn't want to करो 
	 * so, since we may not be safe अगर पूर्णांकerrupts occur.
	 */
	prपूर्णांकk("%s: resetting chip\n", sym_name(np));
	OUTB(np, nc_istat, SRST);
	INB(np, nc_mbox1);
	udelay(10);
	OUTB(np, nc_istat, 0);

	sym_मुक्त_resources(np, pdev, 1);
	scsi_host_put(shost);

	वापस 1;
पूर्ण

/*
 * Driver host ढाँचा.
 */
अटल काष्ठा scsi_host_ढाँचा sym2_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "sym53c8xx",
	.info			= sym53c8xx_info, 
	.queuecommand		= sym53c8xx_queue_command,
	.slave_alloc		= sym53c8xx_slave_alloc,
	.slave_configure	= sym53c8xx_slave_configure,
	.slave_destroy		= sym53c8xx_slave_destroy,
	.eh_पात_handler	= sym53c8xx_eh_पात_handler,
	.eh_device_reset_handler = sym53c8xx_eh_device_reset_handler,
	.eh_bus_reset_handler	= sym53c8xx_eh_bus_reset_handler,
	.eh_host_reset_handler	= sym53c8xx_eh_host_reset_handler,
	.this_id		= 7,
	.max_sectors		= 0xFFFF,
#अगर_घोषित SYM_LINUX_PROC_INFO_SUPPORT
	.show_info		= sym_show_info,
#अगर_घोषित	SYM_LINUX_USER_COMMAND_SUPPORT
	.ग_लिखो_info		= sym_user_command,
#पूर्ण_अगर
	.proc_name		= NAME53C8XX,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक attach_count;

अटल पूर्णांक sym2_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा sym_device sym_dev;
	काष्ठा sym_nvram nvram;
	काष्ठा Scsi_Host *shost;
	पूर्णांक करो_iounmap = 0;
	पूर्णांक करो_disable_device = 1;

	स_रखो(&sym_dev, 0, माप(sym_dev));
	स_रखो(&nvram, 0, माप(nvram));
	sym_dev.pdev = pdev;
	sym_dev.host_id = SYM_SETUP_HOST_ID;

	अगर (pci_enable_device(pdev))
		जाओ leave;

	pci_set_master(pdev);

	अगर (pci_request_regions(pdev, NAME53C8XX))
		जाओ disable;

	अगर (sym_check_supported(&sym_dev))
		जाओ मुक्त;

	अगर (sym_iomap_device(&sym_dev))
		जाओ मुक्त;
	करो_iounmap = 1;

	अगर (sym_check_raid(&sym_dev)) अणु
		करो_disable_device = 0;	/* Don't disable the device */
		जाओ मुक्त;
	पूर्ण

	अगर (sym_set_workarounds(&sym_dev))
		जाओ मुक्त;

	sym_config_pqs(pdev, &sym_dev);

	sym_get_nvram(&sym_dev, &nvram);

	करो_iounmap = 0; /* Don't sym_iounmap_device() after sym_attach(). */
	shost = sym_attach(&sym2_ढाँचा, attach_count, &sym_dev);
	अगर (!shost)
		जाओ मुक्त;

	अगर (scsi_add_host(shost, &pdev->dev))
		जाओ detach;
	scsi_scan_host(shost);

	attach_count++;

	वापस 0;

 detach:
	sym_detach(pci_get_drvdata(pdev), pdev);
 मुक्त:
	अगर (करो_iounmap)
		sym_iounmap_device(&sym_dev);
	pci_release_regions(pdev);
 disable:
	अगर (करो_disable_device)
		pci_disable_device(pdev);
 leave:
	वापस -ENODEV;
पूर्ण

अटल व्योम sym2_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost = pci_get_drvdata(pdev);

	scsi_हटाओ_host(shost);
	sym_detach(shost, pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

	attach_count--;
पूर्ण

/**
 * sym2_io_error_detected() - called when PCI error is detected
 * @pdev: poपूर्णांकer to PCI device
 * @state: current state of the PCI slot
 */
अटल pci_ers_result_t sym2_io_error_detected(काष्ठा pci_dev *pdev,
                                         pci_channel_state_t state)
अणु
	/* If slot is permanently frozen, turn everything off */
	अगर (state == pci_channel_io_perm_failure) अणु
		sym2_हटाओ(pdev);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	disable_irq(pdev->irq);
	pci_disable_device(pdev);

	/* Request that MMIO be enabled, so रेजिस्टर dump can be taken. */
	वापस PCI_ERS_RESULT_CAN_RECOVER;
पूर्ण

/**
 * sym2_io_slot_dump - Enable MMIO and dump debug रेजिस्टरs
 * @pdev: poपूर्णांकer to PCI device
 */
अटल pci_ers_result_t sym2_io_slot_dump(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost = pci_get_drvdata(pdev);

	sym_dump_रेजिस्टरs(shost);

	/* Request a slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * sym2_reset_workarounds - hardware-specअगरic work-arounds
 * @pdev: poपूर्णांकer to PCI device
 *
 * This routine is similar to sym_set_workarounds(), except
 * that, at this poपूर्णांक, we alपढ़ोy know that the device was
 * successfully initialized at least once beक्रमe, and so most
 * of the steps taken there are un-needed here.
 */
अटल व्योम sym2_reset_workarounds(काष्ठा pci_dev *pdev)
अणु
	u_लघु status_reg;
	काष्ठा sym_chip *chip;

	chip = sym_lookup_chip_table(pdev->device, pdev->revision);

	/* Work around क्रम errant bit in 895A, in a fashion
	 * similar to what is करोne in sym_set_workarounds().
	 */
	pci_पढ़ो_config_word(pdev, PCI_STATUS, &status_reg);
	अगर (!(chip->features & FE_66MHZ) && (status_reg & PCI_STATUS_66MHZ)) अणु
		status_reg = PCI_STATUS_66MHZ;
		pci_ग_लिखो_config_word(pdev, PCI_STATUS, status_reg);
		pci_पढ़ो_config_word(pdev, PCI_STATUS, &status_reg);
	पूर्ण
पूर्ण

/**
 * sym2_io_slot_reset() - called when the pci bus has been reset.
 * @pdev: poपूर्णांकer to PCI device
 *
 * Restart the card from scratch.
 */
अटल pci_ers_result_t sym2_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost = pci_get_drvdata(pdev);
	काष्ठा sym_hcb *np = sym_get_hcb(shost);

	prपूर्णांकk(KERN_INFO "%s: recovering from a PCI slot reset\n",
	          sym_name(np));

	अगर (pci_enable_device(pdev)) अणु
		prपूर्णांकk(KERN_ERR "%s: Unable to enable after PCI reset\n",
		        sym_name(np));
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	pci_set_master(pdev);
	enable_irq(pdev->irq);

	/* If the chip can करो Memory Write Invalidate, enable it */
	अगर (np->features & FE_WRIE) अणु
		अगर (pci_set_mwi(pdev))
			वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	/* Perक्रमm work-arounds, analogous to sym_set_workarounds() */
	sym2_reset_workarounds(pdev);

	/* Perक्रमm host reset only on one instance of the card */
	अगर (PCI_FUNC(pdev->devfn) == 0) अणु
		अगर (sym_reset_scsi_bus(np, 0)) अणु
			prपूर्णांकk(KERN_ERR "%s: Unable to reset scsi host\n",
			        sym_name(np));
			वापस PCI_ERS_RESULT_DISCONNECT;
		पूर्ण
		sym_start_up(shost, 1);
	पूर्ण

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * sym2_io_resume() - resume normal ops after PCI reset
 * @pdev: poपूर्णांकer to PCI device
 *
 * Called when the error recovery driver tells us that its
 * OK to resume normal operation. Use completion to allow
 * halted scsi ops to resume.
 */
अटल व्योम sym2_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost = pci_get_drvdata(pdev);
	काष्ठा sym_data *sym_data = shost_priv(shost);

	spin_lock_irq(shost->host_lock);
	अगर (sym_data->io_reset)
		complete(sym_data->io_reset);
	spin_unlock_irq(shost->host_lock);
पूर्ण

अटल व्योम sym2_get_संकेतling(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	क्रमागत spi_संकेत_type type;

	चयन (np->scsi_mode) अणु
	हाल SMODE_SE:
		type = SPI_SIGNAL_SE;
		अवरोध;
	हाल SMODE_LVD:
		type = SPI_SIGNAL_LVD;
		अवरोध;
	हाल SMODE_HVD:
		type = SPI_SIGNAL_HVD;
		अवरोध;
	शेष:
		type = SPI_SIGNAL_UNKNOWN;
		अवरोध;
	पूर्ण
	spi_संकेतling(shost) = type;
पूर्ण

अटल व्योम sym2_set_offset(काष्ठा scsi_target *starget, पूर्णांक offset)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	काष्ठा sym_tcb *tp = &np->target[starget->id];

	tp->tgoal.offset = offset;
	tp->tgoal.check_nego = 1;
पूर्ण

अटल व्योम sym2_set_period(काष्ठा scsi_target *starget, पूर्णांक period)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	काष्ठा sym_tcb *tp = &np->target[starget->id];

	/* have to have DT क्रम these transfers, but DT will also
	 * set width, so check that this is allowed */
	अगर (period <= np->minsync && spi_width(starget))
		tp->tgoal.dt = 1;

	tp->tgoal.period = period;
	tp->tgoal.check_nego = 1;
पूर्ण

अटल व्योम sym2_set_width(काष्ठा scsi_target *starget, पूर्णांक width)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	काष्ठा sym_tcb *tp = &np->target[starget->id];

	/* It is illegal to have DT set on narrow transfers.  If DT is
	 * clear, we must also clear IU and QAS.  */
	अगर (width == 0)
		tp->tgoal.iu = tp->tgoal.dt = tp->tgoal.qas = 0;

	tp->tgoal.width = width;
	tp->tgoal.check_nego = 1;
पूर्ण

अटल व्योम sym2_set_dt(काष्ठा scsi_target *starget, पूर्णांक dt)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	काष्ठा sym_tcb *tp = &np->target[starget->id];

	/* We must clear QAS and IU अगर DT is clear */
	अगर (dt)
		tp->tgoal.dt = 1;
	अन्यथा
		tp->tgoal.iu = tp->tgoal.dt = tp->tgoal.qas = 0;
	tp->tgoal.check_nego = 1;
पूर्ण

#अगर 0
अटल व्योम sym2_set_iu(काष्ठा scsi_target *starget, पूर्णांक iu)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	काष्ठा sym_tcb *tp = &np->target[starget->id];

	अगर (iu)
		tp->tgoal.iu = tp->tgoal.dt = 1;
	अन्यथा
		tp->tgoal.iu = 0;
	tp->tgoal.check_nego = 1;
पूर्ण

अटल व्योम sym2_set_qas(काष्ठा scsi_target *starget, पूर्णांक qas)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	काष्ठा sym_tcb *tp = &np->target[starget->id];

	अगर (qas)
		tp->tgoal.dt = tp->tgoal.qas = 1;
	अन्यथा
		tp->tgoal.qas = 0;
	tp->tgoal.check_nego = 1;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा spi_function_ढाँचा sym2_transport_functions = अणु
	.set_offset	= sym2_set_offset,
	.show_offset	= 1,
	.set_period	= sym2_set_period,
	.show_period	= 1,
	.set_width	= sym2_set_width,
	.show_width	= 1,
	.set_dt		= sym2_set_dt,
	.show_dt	= 1,
#अगर 0
	.set_iu		= sym2_set_iu,
	.show_iu	= 1,
	.set_qas	= sym2_set_qas,
	.show_qas	= 1,
#पूर्ण_अगर
	.get_संकेतling	= sym2_get_संकेतling,
पूर्ण;

अटल काष्ठा pci_device_id sym2_id_table[] = अणु
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_NCR_53C810,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_NCR_53C820,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण, /* new */
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_NCR_53C825,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_NCR_53C815,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_53C810AP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण, /* new */
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_NCR_53C860,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_53C1510,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_STORAGE_SCSI<<8,  0xffff00, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_NCR_53C896,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_NCR_53C895,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_NCR_53C885,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_NCR_53C875,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_NCR_53C1510,
	  PCI_ANY_ID, PCI_ANY_ID,  PCI_CLASS_STORAGE_SCSI<<8,  0xffff00, 0UL पूर्ण, /* new */
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_53C895A,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_53C875A,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_53C1010_33,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_LSI_53C1010_66,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, PCI_DEVICE_ID_NCR_53C875J,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, sym2_id_table);

अटल स्थिर काष्ठा pci_error_handlers sym2_err_handler = अणु
	.error_detected	= sym2_io_error_detected,
	.mmio_enabled	= sym2_io_slot_dump,
	.slot_reset	= sym2_io_slot_reset,
	.resume		= sym2_io_resume,
पूर्ण;

अटल काष्ठा pci_driver sym2_driver = अणु
	.name		= NAME53C8XX,
	.id_table	= sym2_id_table,
	.probe		= sym2_probe,
	.हटाओ		= sym2_हटाओ,
	.err_handler 	= &sym2_err_handler,
पूर्ण;

अटल पूर्णांक __init sym2_init(व्योम)
अणु
	पूर्णांक error;

	sym2_setup_params();
	sym2_transport_ढाँचा = spi_attach_transport(&sym2_transport_functions);
	अगर (!sym2_transport_ढाँचा)
		वापस -ENODEV;

	error = pci_रेजिस्टर_driver(&sym2_driver);
	अगर (error)
		spi_release_transport(sym2_transport_ढाँचा);
	वापस error;
पूर्ण

अटल व्योम __निकास sym2_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sym2_driver);
	spi_release_transport(sym2_transport_ढाँचा);
पूर्ण

module_init(sym2_init);
module_निकास(sym2_निकास);
