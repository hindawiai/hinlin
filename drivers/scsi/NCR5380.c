<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NCR 5380 generic driver routines.  These should make it *trivial*
 * to implement 5380 SCSI drivers under Linux with a non-trantor
 * architecture.
 *
 * Note that these routines also work with NR53c400 family chips.
 *
 * Copyright 1993, Drew Eckhardt
 * Visionary Computing
 * (Unix and Linux consulting and custom programming)
 * drew@coloraकरो.edu
 * +1 (303) 666-5836
 *
 * For more inक्रमmation, please consult
 *
 * NCR 5380 Family
 * SCSI Protocol Controller
 * Databook
 *
 * NCR Microelectronics
 * 1635 Aeroplaza Drive
 * Coloraकरो Springs, CO 80916
 * 1+ (719) 578-3400
 * 1+ (800) 334-5454
 */

/*
 * With contributions from Ray Van Tassle, Ingmar Baumgart,
 * Ronald van Cuijlenborg, Alan Cox and others.
 */

/* Ported to Atari by Roman Hodek and others. */

/* Adapted क्रम the Sun 3 by Sam Creasey. */

/*
 * Design
 *
 * This is a generic 5380 driver.  To use it on a dअगरferent platक्रमm,
 * one simply ग_लिखोs appropriate प्रणाली specअगरic macros (ie, data
 * transfer - some PC's will use the I/O bus, 68K's must use
 * memory mapped) and drops this file in their 'C' wrapper.
 *
 * As far as command queueing, two queues are मुख्यtained क्रम
 * each 5380 in the प्रणाली - commands that haven't been issued yet,
 * and commands that are currently executing.  This means that an
 * unlimited number of commands may be queued, letting
 * more commands propagate from the higher driver levels giving higher
 * throughput.  Note that both I_T_L and I_T_L_Q nexuses are supported,
 * allowing multiple commands to propagate all the way to a SCSI-II device
 * जबतक a command is alपढ़ोy executing.
 *
 *
 * Issues specअगरic to the NCR5380 :
 *
 * When used in a PIO or pseuकरो-dma mode, the NCR5380 is a braindead
 * piece of hardware that requires you to sit in a loop polling क्रम
 * the REQ संकेत as दीर्घ as you are connected.  Some devices are
 * brain dead (ie, many TEXEL CD ROM drives) and won't disconnect
 * जबतक करोing दीर्घ seek operations. [...] These
 * broken devices are the exception rather than the rule and I'd rather
 * spend my समय optimizing क्रम the normal हाल.
 *
 * Architecture :
 *
 * At the heart of the design is a coroutine, NCR5380_मुख्य,
 * which is started from a workqueue क्रम each NCR5380 host in the
 * प्रणाली.  It attempts to establish I_T_L or I_T_L_Q nexuses by
 * removing the commands from the issue queue and calling
 * NCR5380_select() अगर a nexus is not established.
 *
 * Once a nexus is established, the NCR5380_inक्रमmation_transfer()
 * phase goes through the various phases as inकाष्ठाed by the target.
 * अगर the target goes पूर्णांकo MSG IN and sends a DISCONNECT message,
 * the command काष्ठाure is placed पूर्णांकo the per instance disconnected
 * queue, and NCR5380_मुख्य tries to find more work.  If the target is
 * idle क्रम too दीर्घ, the प्रणाली will try to sleep.
 *
 * If a command has disconnected, eventually an पूर्णांकerrupt will trigger,
 * calling NCR5380_पूर्णांकr()  which will in turn call NCR5380_reselect
 * to reestablish a nexus.  This will run मुख्य अगर necessary.
 *
 * On command termination, the करोne function will be called as
 * appropriate.
 *
 * SCSI poपूर्णांकers are मुख्यtained in the SCp field of SCSI command
 * काष्ठाures, being initialized after the command is connected
 * in NCR5380_select, and set as appropriate in NCR5380_inक्रमmation_transfer.
 * Note that in violation of the standard, an implicit SAVE POINTERS operation
 * is करोne, since some BROKEN disks fail to issue an explicit SAVE POINTERS.
 */

/*
 * Using this file :
 * This file a skeleton Linux SCSI driver क्रम the NCR 5380 series
 * of chips.  To use it, you ग_लिखो an architecture specअगरic functions
 * and macros and include this file in your driver.
 *
 * These macros MUST be defined :
 *
 * NCR5380_पढ़ो(रेजिस्टर)  - पढ़ो from the specअगरied रेजिस्टर
 *
 * NCR5380_ग_लिखो(रेजिस्टर, value) - ग_लिखो to the specअगरic रेजिस्टर
 *
 * NCR5380_implementation_fields  - additional fields needed क्रम this
 * specअगरic implementation of the NCR5380
 *
 * Either real DMA *or* pseuकरो DMA may be implemented
 *
 * NCR5380_dma_xfer_len   - determine size of DMA/PDMA transfer
 * NCR5380_dma_send_setup - execute DMA/PDMA from memory to 5380
 * NCR5380_dma_recv_setup - execute DMA/PDMA from 5380 to memory
 * NCR5380_dma_residual   - residual byte count
 *
 * The generic driver is initialized by calling NCR5380_init(instance),
 * after setting the appropriate host specअगरic fields and ID.
 */

#अगर_अघोषित NCR5380_io_delay
#घोषणा NCR5380_io_delay(x)
#पूर्ण_अगर

#अगर_अघोषित NCR5380_acquire_dma_irq
#घोषणा NCR5380_acquire_dma_irq(x)	(1)
#पूर्ण_अगर

#अगर_अघोषित NCR5380_release_dma_irq
#घोषणा NCR5380_release_dma_irq(x)
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक disconnect_mask = ~0;
module_param(disconnect_mask, पूर्णांक, 0444);

अटल पूर्णांक करो_पात(काष्ठा Scsi_Host *, अचिन्हित पूर्णांक);
अटल व्योम करो_reset(काष्ठा Scsi_Host *);
अटल व्योम bus_reset_cleanup(काष्ठा Scsi_Host *);

/**
 * initialize_SCp - init the scsi poपूर्णांकer field
 * @cmd: command block to set up
 *
 * Set up the पूर्णांकernal fields in the SCSI command.
 */

अटल अंतरभूत व्योम initialize_SCp(काष्ठा scsi_cmnd *cmd)
अणु
	/*
	 * Initialize the Scsi Poपूर्णांकer field so that all of the commands in the
	 * various queues are valid.
	 */

	अगर (scsi_bufflen(cmd)) अणु
		cmd->SCp.buffer = scsi_sglist(cmd);
		cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
		cmd->SCp.this_residual = cmd->SCp.buffer->length;
	पूर्ण अन्यथा अणु
		cmd->SCp.buffer = शून्य;
		cmd->SCp.ptr = शून्य;
		cmd->SCp.this_residual = 0;
	पूर्ण

	cmd->SCp.Status = 0;
	cmd->SCp.Message = 0;
पूर्ण

अटल अंतरभूत व्योम advance_sg_buffer(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scatterlist *s = cmd->SCp.buffer;

	अगर (!cmd->SCp.this_residual && s && !sg_is_last(s)) अणु
		cmd->SCp.buffer = sg_next(s);
		cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
		cmd->SCp.this_residual = cmd->SCp.buffer->length;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम set_resid_from_SCp(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक resid = cmd->SCp.this_residual;
	काष्ठा scatterlist *s = cmd->SCp.buffer;

	अगर (s)
		जबतक (!sg_is_last(s)) अणु
			s = sg_next(s);
			resid += s->length;
		पूर्ण
	scsi_set_resid(cmd, resid);
पूर्ण

/**
 * NCR5380_poll_politely2 - रुको क्रम two chip रेजिस्टर values
 * @hostdata: host निजी data
 * @reg1: 5380 रेजिस्टर to poll
 * @bit1: Biपंचांगask to check
 * @val1: Expected value
 * @reg2: Second 5380 रेजिस्टर to poll
 * @bit2: Second biपंचांगask to check
 * @val2: Second expected value
 * @रुको: Time-out in jअगरfies, 0 अगर sleeping is not allowed
 *
 * Polls the chip in a reasonably efficient manner रुकोing क्रम an
 * event to occur. After a लघु quick poll we begin to yield the CPU
 * (अगर possible). In irq contexts the समय-out is arbitrarily limited.
 * Callers may hold locks as दीर्घ as they are held in irq mode.
 *
 * Returns 0 अगर either or both event(s) occurred otherwise -ETIMEDOUT.
 */

अटल पूर्णांक NCR5380_poll_politely2(काष्ठा NCR5380_hostdata *hostdata,
                                  अचिन्हित पूर्णांक reg1, u8 bit1, u8 val1,
                                  अचिन्हित पूर्णांक reg2, u8 bit2, u8 val2,
                                  अचिन्हित दीर्घ रुको)
अणु
	अचिन्हित दीर्घ n = hostdata->poll_loops;
	अचिन्हित दीर्घ deadline = jअगरfies + रुको;

	करो अणु
		अगर ((NCR5380_पढ़ो(reg1) & bit1) == val1)
			वापस 0;
		अगर ((NCR5380_पढ़ो(reg2) & bit2) == val2)
			वापस 0;
		cpu_relax();
	पूर्ण जबतक (n--);

	अगर (!रुको)
		वापस -ETIMEDOUT;

	/* Repeatedly sleep क्रम 1 ms until deadline */
	जबतक (समय_is_after_jअगरfies(deadline)) अणु
		schedule_समयout_unपूर्णांकerruptible(1);
		अगर ((NCR5380_पढ़ो(reg1) & bit1) == val1)
			वापस 0;
		अगर ((NCR5380_पढ़ो(reg2) & bit2) == val2)
			वापस 0;
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

#अगर न_संशोधन
अटल काष्ठा अणु
	अचिन्हित अक्षर mask;
	स्थिर अक्षर *name;
पूर्ण संकेतs[] = अणु
	अणुSR_DBP, "PARITY"पूर्ण,
	अणुSR_RST, "RST"पूर्ण,
	अणुSR_BSY, "BSY"पूर्ण,
	अणुSR_REQ, "REQ"पूर्ण,
	अणुSR_MSG, "MSG"पूर्ण,
	अणुSR_CD, "CD"पूर्ण,
	अणुSR_IO, "IO"पूर्ण,
	अणुSR_SEL, "SEL"पूर्ण,
	अणु0, शून्यपूर्ण
पूर्ण,
basrs[] = अणु
	अणुBASR_END_DMA_TRANSFER, "END OF DMA"पूर्ण,
	अणुBASR_DRQ, "DRQ"पूर्ण,
	अणुBASR_PARITY_ERROR, "PARITY ERROR"पूर्ण,
	अणुBASR_IRQ, "IRQ"पूर्ण,
	अणुBASR_PHASE_MATCH, "PHASE MATCH"पूर्ण,
	अणुBASR_BUSY_ERROR, "BUSY ERROR"पूर्ण,
	अणुBASR_ATN, "ATN"पूर्ण,
	अणुBASR_ACK, "ACK"पूर्ण,
	अणु0, शून्यपूर्ण
पूर्ण,
icrs[] = अणु
	अणुICR_ASSERT_RST, "ASSERT RST"पूर्ण,
	अणुICR_ARBITRATION_PROGRESS, "ARB. IN PROGRESS"पूर्ण,
	अणुICR_ARBITRATION_LOST, "LOST ARB."पूर्ण,
	अणुICR_ASSERT_ACK, "ASSERT ACK"पूर्ण,
	अणुICR_ASSERT_BSY, "ASSERT BSY"पूर्ण,
	अणुICR_ASSERT_SEL, "ASSERT SEL"पूर्ण,
	अणुICR_ASSERT_ATN, "ASSERT ATN"पूर्ण,
	अणुICR_ASSERT_DATA, "ASSERT DATA"पूर्ण,
	अणु0, शून्यपूर्ण
पूर्ण,
mrs[] = अणु
	अणुMR_BLOCK_DMA_MODE, "BLOCK DMA MODE"पूर्ण,
	अणुMR_TARGET, "TARGET"पूर्ण,
	अणुMR_ENABLE_PAR_CHECK, "PARITY CHECK"पूर्ण,
	अणुMR_ENABLE_PAR_INTR, "PARITY INTR"पूर्ण,
	अणुMR_ENABLE_EOP_INTR, "EOP INTR"पूर्ण,
	अणुMR_MONITOR_BSY, "MONITOR BSY"पूर्ण,
	अणुMR_DMA_MODE, "DMA MODE"पूर्ण,
	अणुMR_ARBITRATE, "ARBITRATE"पूर्ण,
	अणु0, शून्यपूर्ण
पूर्ण;

/**
 * NCR5380_prपूर्णांक - prपूर्णांक scsi bus संकेतs
 * @instance: adapter state to dump
 *
 * Prपूर्णांक the SCSI bus संकेतs क्रम debugging purposes
 */

अटल व्योम NCR5380_prपूर्णांक(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	अचिन्हित अक्षर status, basr, mr, icr, i;

	status = NCR5380_पढ़ो(STATUS_REG);
	mr = NCR5380_पढ़ो(MODE_REG);
	icr = NCR5380_पढ़ो(INITIATOR_COMMAND_REG);
	basr = NCR5380_पढ़ो(BUS_AND_STATUS_REG);

	prपूर्णांकk(KERN_DEBUG "SR =   0x%02x : ", status);
	क्रम (i = 0; संकेतs[i].mask; ++i)
		अगर (status & संकेतs[i].mask)
			prपूर्णांकk(KERN_CONT "%s, ", संकेतs[i].name);
	prपूर्णांकk(KERN_CONT "\nBASR = 0x%02x : ", basr);
	क्रम (i = 0; basrs[i].mask; ++i)
		अगर (basr & basrs[i].mask)
			prपूर्णांकk(KERN_CONT "%s, ", basrs[i].name);
	prपूर्णांकk(KERN_CONT "\nICR =  0x%02x : ", icr);
	क्रम (i = 0; icrs[i].mask; ++i)
		अगर (icr & icrs[i].mask)
			prपूर्णांकk(KERN_CONT "%s, ", icrs[i].name);
	prपूर्णांकk(KERN_CONT "\nMR =   0x%02x : ", mr);
	क्रम (i = 0; mrs[i].mask; ++i)
		अगर (mr & mrs[i].mask)
			prपूर्णांकk(KERN_CONT "%s, ", mrs[i].name);
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

अटल काष्ठा अणु
	अचिन्हित अक्षर value;
	स्थिर अक्षर *name;
पूर्ण phases[] = अणु
	अणुPHASE_DATAOUT, "DATAOUT"पूर्ण,
	अणुPHASE_DATAIN, "DATAIN"पूर्ण,
	अणुPHASE_CMDOUT, "CMDOUT"पूर्ण,
	अणुPHASE_STATIN, "STATIN"पूर्ण,
	अणुPHASE_MSGOUT, "MSGOUT"पूर्ण,
	अणुPHASE_MSGIN, "MSGIN"पूर्ण,
	अणुPHASE_UNKNOWN, "UNKNOWN"पूर्ण
पूर्ण;

/**
 * NCR5380_prपूर्णांक_phase - show SCSI phase
 * @instance: adapter to dump
 *
 * Prपूर्णांक the current SCSI phase क्रम debugging purposes
 */

अटल व्योम NCR5380_prपूर्णांक_phase(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	अचिन्हित अक्षर status;
	पूर्णांक i;

	status = NCR5380_पढ़ो(STATUS_REG);
	अगर (!(status & SR_REQ))
		shost_prपूर्णांकk(KERN_DEBUG, instance, "REQ not asserted, phase unknown.\n");
	अन्यथा अणु
		क्रम (i = 0; (phases[i].value != PHASE_UNKNOWN) &&
		     (phases[i].value != (status & PHASE_MASK)); ++i)
			;
		shost_prपूर्णांकk(KERN_DEBUG, instance, "phase %s\n", phases[i].name);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 * NCR5380_info - report driver and host inक्रमmation
 * @instance: relevant scsi host instance
 *
 * For use as the host ढाँचा info() handler.
 */

अटल स्थिर अक्षर *NCR5380_info(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);

	वापस hostdata->info;
पूर्ण

/**
 * NCR5380_init - initialise an NCR5380
 * @instance: adapter to configure
 * @flags: control flags
 *
 * Initializes *instance and corresponding 5380 chip,
 * with flags OR'd पूर्णांकo the initial flags value.
 *
 * Notes : I assume that the host, hostno, and id bits have been
 * set correctly. I करोn't care about the irq and other fields.
 *
 * Returns 0 क्रम success
 */

अटल पूर्णांक NCR5380_init(काष्ठा Scsi_Host *instance, पूर्णांक flags)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	पूर्णांक i;
	अचिन्हित दीर्घ deadline;
	अचिन्हित दीर्घ accesses_per_ms;

	instance->max_lun = 7;

	hostdata->host = instance;
	hostdata->id_mask = 1 << instance->this_id;
	hostdata->id_higher_mask = 0;
	क्रम (i = hostdata->id_mask; i <= 0x80; i <<= 1)
		अगर (i > hostdata->id_mask)
			hostdata->id_higher_mask |= i;
	क्रम (i = 0; i < 8; ++i)
		hostdata->busy[i] = 0;
	hostdata->dma_len = 0;

	spin_lock_init(&hostdata->lock);
	hostdata->connected = शून्य;
	hostdata->sensing = शून्य;
	INIT_LIST_HEAD(&hostdata->स्वतःsense);
	INIT_LIST_HEAD(&hostdata->unissued);
	INIT_LIST_HEAD(&hostdata->disconnected);

	hostdata->flags = flags;

	INIT_WORK(&hostdata->मुख्य_task, NCR5380_मुख्य);
	hostdata->work_q = alloc_workqueue("ncr5380_%d",
	                        WQ_UNBOUND | WQ_MEM_RECLAIM,
	                        1, instance->host_no);
	अगर (!hostdata->work_q)
		वापस -ENOMEM;

	snम_लिखो(hostdata->info, माप(hostdata->info),
		"%s, irq %d, io_port 0x%lx, base 0x%lx, can_queue %d, cmd_per_lun %d, sg_tablesize %d, this_id %d, flags { %s%s%s}",
		instance->hostt->name, instance->irq, hostdata->io_port,
		hostdata->base, instance->can_queue, instance->cmd_per_lun,
		instance->sg_tablesize, instance->this_id,
		hostdata->flags & FLAG_DMA_FIXUP     ? "DMA_FIXUP "     : "",
		hostdata->flags & FLAG_NO_PSEUDO_DMA ? "NO_PSEUDO_DMA " : "",
		hostdata->flags & FLAG_TOSHIBA_DELAY ? "TOSHIBA_DELAY " : "");

	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
	NCR5380_ग_लिखो(MODE_REG, MR_BASE);
	NCR5380_ग_लिखो(TARGET_COMMAND_REG, 0);
	NCR5380_ग_लिखो(SELECT_ENABLE_REG, 0);

	/* Calibrate रेजिस्टर polling loop */
	i = 0;
	deadline = jअगरfies + 1;
	करो अणु
		cpu_relax();
	पूर्ण जबतक (समय_is_after_jअगरfies(deadline));
	deadline += msecs_to_jअगरfies(256);
	करो अणु
		NCR5380_पढ़ो(STATUS_REG);
		++i;
		cpu_relax();
	पूर्ण जबतक (समय_is_after_jअगरfies(deadline));
	accesses_per_ms = i / 256;
	hostdata->poll_loops = NCR5380_REG_POLL_TIME * accesses_per_ms / 2;

	वापस 0;
पूर्ण

/**
 * NCR5380_maybe_reset_bus - Detect and correct bus wedge problems.
 * @instance: adapter to check
 *
 * If the प्रणाली crashed, it may have crashed with a connected target and
 * the SCSI bus busy. Check क्रम BUS FREE phase. If not, try to पात the
 * currently established nexus, which we know nothing about. Failing that
 * करो a bus reset.
 *
 * Note that a bus reset will cause the chip to निश्चित IRQ.
 *
 * Returns 0 अगर successful, otherwise -ENXIO.
 */

अटल पूर्णांक NCR5380_maybe_reset_bus(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	पूर्णांक pass;

	क्रम (pass = 1; (NCR5380_पढ़ो(STATUS_REG) & SR_BSY) && pass <= 6; ++pass) अणु
		चयन (pass) अणु
		हाल 1:
		हाल 3:
		हाल 5:
			shost_prपूर्णांकk(KERN_ERR, instance, "SCSI bus busy, waiting up to five seconds\n");
			NCR5380_poll_politely(hostdata,
			                      STATUS_REG, SR_BSY, 0, 5 * HZ);
			अवरोध;
		हाल 2:
			shost_prपूर्णांकk(KERN_ERR, instance, "bus busy, attempting abort\n");
			करो_पात(instance, 1);
			अवरोध;
		हाल 4:
			shost_prपूर्णांकk(KERN_ERR, instance, "bus busy, attempting reset\n");
			करो_reset(instance);
			/* Wait after a reset; the SCSI standard calls क्रम
			 * 250ms, we रुको 500ms to be on the safe side.
			 * But some Toshiba CD-ROMs need ten बार that.
			 */
			अगर (hostdata->flags & FLAG_TOSHIBA_DELAY)
				msleep(2500);
			अन्यथा
				msleep(500);
			अवरोध;
		हाल 6:
			shost_prपूर्णांकk(KERN_ERR, instance, "bus locked solid\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * NCR5380_निकास - हटाओ an NCR5380
 * @instance: adapter to हटाओ
 *
 * Assumes that no more work can be queued (e.g. by NCR5380_पूर्णांकr).
 */

अटल व्योम NCR5380_निकास(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);

	cancel_work_sync(&hostdata->मुख्य_task);
	destroy_workqueue(hostdata->work_q);
पूर्ण

/**
 * complete_cmd - finish processing a command and वापस it to the SCSI ML
 * @instance: the host instance
 * @cmd: command to complete
 */

अटल व्योम complete_cmd(काष्ठा Scsi_Host *instance,
                         काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);

	dsprपूर्णांकk(न_संशोधन_QUEUES, instance, "complete_cmd: cmd %p\n", cmd);

	अगर (hostdata->sensing == cmd) अणु
		/* Autosense processing ends here */
		अगर (status_byte(cmd->result) != GOOD) अणु
			scsi_eh_restore_cmnd(cmd, &hostdata->ses);
		पूर्ण अन्यथा अणु
			scsi_eh_restore_cmnd(cmd, &hostdata->ses);
			set_driver_byte(cmd, DRIVER_SENSE);
		पूर्ण
		hostdata->sensing = शून्य;
	पूर्ण

	cmd->scsi_करोne(cmd);
पूर्ण

/**
 * NCR5380_queue_command - queue a command
 * @instance: the relevant SCSI adapter
 * @cmd: SCSI command
 *
 * cmd is added to the per-instance issue queue, with minor
 * twiddling करोne to the host specअगरic fields of cmd.  If the
 * मुख्य coroutine is not running, it is restarted.
 */

अटल पूर्णांक NCR5380_queue_command(काष्ठा Scsi_Host *instance,
                                 काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	काष्ठा NCR5380_cmd *ncmd = scsi_cmd_priv(cmd);
	अचिन्हित दीर्घ flags;

#अगर (न_संशोधन & न_संशोधन_NO_WRITE)
	चयन (cmd->cmnd[0]) अणु
	हाल WRITE_6:
	हाल WRITE_10:
		shost_prपूर्णांकk(KERN_DEBUG, instance, "WRITE attempted with NDEBUG_NO_WRITE set\n");
		cmd->result = (DID_ERROR << 16);
		cmd->scsi_करोne(cmd);
		वापस 0;
	पूर्ण
#पूर्ण_अगर /* (न_संशोधन & न_संशोधन_NO_WRITE) */

	cmd->result = 0;

	spin_lock_irqsave(&hostdata->lock, flags);

	अगर (!NCR5380_acquire_dma_irq(instance)) अणु
		spin_unlock_irqrestore(&hostdata->lock, flags);

		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	/*
	 * Insert the cmd पूर्णांकo the issue queue. Note that REQUEST SENSE
	 * commands are added to the head of the queue since any command will
	 * clear the contingent allegiance condition that exists and the
	 * sense data is only guaranteed to be valid जबतक the condition exists.
	 */

	अगर (cmd->cmnd[0] == REQUEST_SENSE)
		list_add(&ncmd->list, &hostdata->unissued);
	अन्यथा
		list_add_tail(&ncmd->list, &hostdata->unissued);

	spin_unlock_irqrestore(&hostdata->lock, flags);

	dsprपूर्णांकk(न_संशोधन_QUEUES, instance, "command %p added to %s of queue\n",
	         cmd, (cmd->cmnd[0] == REQUEST_SENSE) ? "head" : "tail");

	/* Kick off command processing */
	queue_work(hostdata->work_q, &hostdata->मुख्य_task);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम maybe_release_dma_irq(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);

	/* Caller करोes the locking needed to set & test these data atomically */
	अगर (list_empty(&hostdata->disconnected) &&
	    list_empty(&hostdata->unissued) &&
	    list_empty(&hostdata->स्वतःsense) &&
	    !hostdata->connected &&
	    !hostdata->selecting) अणु
		NCR5380_release_dma_irq(instance);
	पूर्ण
पूर्ण

/**
 * dequeue_next_cmd - dequeue a command क्रम processing
 * @instance: the scsi host instance
 *
 * Priority is given to commands on the स्वतःsense queue. These commands
 * need स्वतःsense because of a CHECK CONDITION result.
 *
 * Returns a command poपूर्णांकer अगर a command is found क्रम a target that is
 * not alपढ़ोy busy. Otherwise वापसs शून्य.
 */

अटल काष्ठा scsi_cmnd *dequeue_next_cmd(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	काष्ठा NCR5380_cmd *ncmd;
	काष्ठा scsi_cmnd *cmd;

	अगर (hostdata->sensing || list_empty(&hostdata->स्वतःsense)) अणु
		list_क्रम_each_entry(ncmd, &hostdata->unissued, list) अणु
			cmd = NCR5380_to_scmd(ncmd);
			dsprपूर्णांकk(न_संशोधन_QUEUES, instance, "dequeue: cmd=%p target=%d busy=0x%02x lun=%llu\n",
			         cmd, scmd_id(cmd), hostdata->busy[scmd_id(cmd)], cmd->device->lun);

			अगर (!(hostdata->busy[scmd_id(cmd)] & (1 << cmd->device->lun))) अणु
				list_del(&ncmd->list);
				dsprपूर्णांकk(न_संशोधन_QUEUES, instance,
				         "dequeue: removed %p from issue queue\n", cmd);
				वापस cmd;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Autosense processing begins here */
		ncmd = list_first_entry(&hostdata->स्वतःsense,
		                        काष्ठा NCR5380_cmd, list);
		list_del(&ncmd->list);
		cmd = NCR5380_to_scmd(ncmd);
		dsprपूर्णांकk(न_संशोधन_QUEUES, instance,
		         "dequeue: removed %p from autosense queue\n", cmd);
		scsi_eh_prep_cmnd(cmd, &hostdata->ses, शून्य, 0, ~0);
		hostdata->sensing = cmd;
		वापस cmd;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम requeue_cmd(काष्ठा Scsi_Host *instance, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	काष्ठा NCR5380_cmd *ncmd = scsi_cmd_priv(cmd);

	अगर (hostdata->sensing == cmd) अणु
		scsi_eh_restore_cmnd(cmd, &hostdata->ses);
		list_add(&ncmd->list, &hostdata->स्वतःsense);
		hostdata->sensing = शून्य;
	पूर्ण अन्यथा
		list_add(&ncmd->list, &hostdata->unissued);
पूर्ण

/**
 * NCR5380_मुख्य - NCR state machines
 *
 * NCR5380_मुख्य is a coroutine that runs as दीर्घ as more work can
 * be करोne on the NCR5380 host adapters in a प्रणाली.  Both
 * NCR5380_queue_command() and NCR5380_पूर्णांकr() will try to start it
 * in हाल it is not running.
 */

अटल व्योम NCR5380_मुख्य(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा NCR5380_hostdata *hostdata =
		container_of(work, काष्ठा NCR5380_hostdata, मुख्य_task);
	काष्ठा Scsi_Host *instance = hostdata->host;
	पूर्णांक करोne;

	करो अणु
		करोne = 1;

		spin_lock_irq(&hostdata->lock);
		जबतक (!hostdata->connected && !hostdata->selecting) अणु
			काष्ठा scsi_cmnd *cmd = dequeue_next_cmd(instance);

			अगर (!cmd)
				अवरोध;

			dsprपूर्णांकk(न_संशोधन_MAIN, instance, "main: dequeued %p\n", cmd);

			/*
			 * Attempt to establish an I_T_L nexus here.
			 * On success, instance->hostdata->connected is set.
			 * On failure, we must add the command back to the
			 * issue queue so we can keep trying.
			 */
			/*
			 * REQUEST SENSE commands are issued without tagged
			 * queueing, even on SCSI-II devices because the
			 * contingent allegiance condition exists क्रम the
			 * entire unit.
			 */

			अगर (!NCR5380_select(instance, cmd)) अणु
				dsprपूर्णांकk(न_संशोधन_MAIN, instance, "main: select complete\n");
			पूर्ण अन्यथा अणु
				dsprपूर्णांकk(न_संशोधन_MAIN | न_संशोधन_QUEUES, instance,
				         "main: select failed, returning %p to queue\n", cmd);
				requeue_cmd(instance, cmd);
			पूर्ण
		पूर्ण
		अगर (hostdata->connected && !hostdata->dma_len) अणु
			dsprपूर्णांकk(न_संशोधन_MAIN, instance, "main: performing information transfer\n");
			NCR5380_inक्रमmation_transfer(instance);
			करोne = 0;
		पूर्ण
		अगर (!hostdata->connected) अणु
			NCR5380_ग_लिखो(SELECT_ENABLE_REG, hostdata->id_mask);
			maybe_release_dma_irq(instance);
		पूर्ण
		spin_unlock_irq(&hostdata->lock);
		अगर (!करोne)
			cond_resched();
	पूर्ण जबतक (!करोne);
पूर्ण

/*
 * NCR5380_dma_complete - finish DMA transfer
 * @instance: the scsi host instance
 *
 * Called by the पूर्णांकerrupt handler when DMA finishes or a phase
 * mismatch occurs (which would end the DMA transfer).
 */

अटल व्योम NCR5380_dma_complete(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	पूर्णांक transferred;
	अचिन्हित अक्षर **data;
	पूर्णांक *count;
	पूर्णांक saved_data = 0, overrun = 0;
	अचिन्हित अक्षर p;

	अगर (hostdata->पढ़ो_overruns) अणु
		p = hostdata->connected->SCp.phase;
		अगर (p & SR_IO) अणु
			udelay(10);
			अगर ((NCR5380_पढ़ो(BUS_AND_STATUS_REG) &
			     (BASR_PHASE_MATCH | BASR_ACK)) ==
			    (BASR_PHASE_MATCH | BASR_ACK)) अणु
				saved_data = NCR5380_पढ़ो(INPUT_DATA_REG);
				overrun = 1;
				dsprपूर्णांकk(न_संशोधन_DMA, instance, "read overrun handled\n");
			पूर्ण
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_SUN3
	अगर ((sun3scsi_dma_finish(rq_data_dir(hostdata->connected->request)))) अणु
		pr_err("scsi%d: overrun in UDC counter -- not prepared to deal with this!\n",
		       instance->host_no);
		BUG();
	पूर्ण

	अगर ((NCR5380_पढ़ो(BUS_AND_STATUS_REG) & (BASR_PHASE_MATCH | BASR_ACK)) ==
	    (BASR_PHASE_MATCH | BASR_ACK)) अणु
		pr_err("scsi%d: BASR %02x\n", instance->host_no,
		       NCR5380_पढ़ो(BUS_AND_STATUS_REG));
		pr_err("scsi%d: bus stuck in data phase -- probably a single byte overrun!\n",
		       instance->host_no);
		BUG();
	पूर्ण
#पूर्ण_अगर

	NCR5380_ग_लिखो(MODE_REG, MR_BASE);
	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
	NCR5380_पढ़ो(RESET_PARITY_INTERRUPT_REG);

	transferred = hostdata->dma_len - NCR5380_dma_residual(hostdata);
	hostdata->dma_len = 0;

	data = (अचिन्हित अक्षर **)&hostdata->connected->SCp.ptr;
	count = &hostdata->connected->SCp.this_residual;
	*data += transferred;
	*count -= transferred;

	अगर (hostdata->पढ़ो_overruns) अणु
		पूर्णांक cnt, toPIO;

		अगर ((NCR5380_पढ़ो(STATUS_REG) & PHASE_MASK) == p && (p & SR_IO)) अणु
			cnt = toPIO = hostdata->पढ़ो_overruns;
			अगर (overrun) अणु
				dsprपूर्णांकk(न_संशोधन_DMA, instance,
				         "Got an input overrun, using saved byte\n");
				*(*data)++ = saved_data;
				(*count)--;
				cnt--;
				toPIO--;
			पूर्ण
			अगर (toPIO > 0) अणु
				dsprपूर्णांकk(न_संशोधन_DMA, instance,
				         "Doing %d byte PIO to 0x%p\n", cnt, *data);
				NCR5380_transfer_pio(instance, &p, &cnt, data, 0);
				*count -= toPIO - cnt;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * NCR5380_पूर्णांकr - generic NCR5380 irq handler
 * @irq: पूर्णांकerrupt number
 * @dev_id: device info
 *
 * Handle पूर्णांकerrupts, reestablishing I_T_L or I_T_L_Q nexuses
 * from the disconnected queue, and restarting NCR5380_मुख्य()
 * as required.
 *
 * The chip can निश्चित IRQ in any of six dअगरferent conditions. The IRQ flag
 * is then cleared by पढ़ोing the Reset Parity/Interrupt Register (RPIR).
 * Three of these six conditions are latched in the Bus and Status Register:
 * - End of DMA (cleared by ending DMA Mode)
 * - Parity error (cleared by पढ़ोing RPIR)
 * - Loss of BSY (cleared by पढ़ोing RPIR)
 * Two conditions have flag bits that are not latched:
 * - Bus phase mismatch (non-maskable in DMA Mode, cleared by ending DMA Mode)
 * - Bus reset (non-maskable)
 * The reमुख्यing condition has no flag bit at all:
 * - Selection/reselection
 *
 * Hence, establishing the cause(s) of any पूर्णांकerrupt is partly guesswork.
 * In "The DP8490 and DP5380 Comparison Guide", National Semiconductor
 * claimed that "the design of the [DP8490] पूर्णांकerrupt logic ensures
 * पूर्णांकerrupts will not be lost (they can be on the DP5380)."
 * The L5380/53C80 datasheet from LOGIC Devices has more details.
 *
 * Checking क्रम bus reset by पढ़ोing RST is futile because of पूर्णांकerrupt
 * latency, but a bus reset will reset chip logic. Checking क्रम parity error
 * is unnecessary because that पूर्णांकerrupt is never enabled. A Loss of BSY
 * condition will clear DMA Mode. We can tell when this occurs because the
 * the Busy Monitor पूर्णांकerrupt is enabled together with DMA Mode.
 */

अटल irqवापस_t __maybe_unused NCR5380_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा Scsi_Host *instance = dev_id;
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	पूर्णांक handled = 0;
	अचिन्हित अक्षर basr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hostdata->lock, flags);

	basr = NCR5380_पढ़ो(BUS_AND_STATUS_REG);
	अगर (basr & BASR_IRQ) अणु
		अचिन्हित अक्षर mr = NCR5380_पढ़ो(MODE_REG);
		अचिन्हित अक्षर sr = NCR5380_पढ़ो(STATUS_REG);

		dsprपूर्णांकk(न_संशोधन_INTR, instance, "IRQ %d, BASR 0x%02x, SR 0x%02x, MR 0x%02x\n",
		         irq, basr, sr, mr);

		अगर ((mr & MR_DMA_MODE) || (mr & MR_MONITOR_BSY)) अणु
			/* Probably End of DMA, Phase Mismatch or Loss of BSY.
			 * We ack IRQ after clearing Mode Register. Workarounds
			 * क्रम End of DMA errata need to happen in DMA Mode.
			 */

			dsprपूर्णांकk(न_संशोधन_INTR, instance, "interrupt in DMA mode\n");

			अगर (hostdata->connected) अणु
				NCR5380_dma_complete(instance);
				queue_work(hostdata->work_q, &hostdata->मुख्य_task);
			पूर्ण अन्यथा अणु
				NCR5380_ग_लिखो(MODE_REG, MR_BASE);
				NCR5380_पढ़ो(RESET_PARITY_INTERRUPT_REG);
			पूर्ण
		पूर्ण अन्यथा अगर ((NCR5380_पढ़ो(CURRENT_SCSI_DATA_REG) & hostdata->id_mask) &&
		    (sr & (SR_SEL | SR_IO | SR_BSY | SR_RST)) == (SR_SEL | SR_IO)) अणु
			/* Probably reselected */
			NCR5380_ग_लिखो(SELECT_ENABLE_REG, 0);
			NCR5380_पढ़ो(RESET_PARITY_INTERRUPT_REG);

			dsprपूर्णांकk(न_संशोधन_INTR, instance, "interrupt with SEL and IO\n");

			अगर (!hostdata->connected) अणु
				NCR5380_reselect(instance);
				queue_work(hostdata->work_q, &hostdata->मुख्य_task);
			पूर्ण
			अगर (!hostdata->connected)
				NCR5380_ग_लिखो(SELECT_ENABLE_REG, hostdata->id_mask);
		पूर्ण अन्यथा अणु
			/* Probably Bus Reset */
			NCR5380_पढ़ो(RESET_PARITY_INTERRUPT_REG);

			अगर (sr & SR_RST) अणु
				/* Certainly Bus Reset */
				shost_prपूर्णांकk(KERN_WARNING, instance,
					     "bus reset interrupt\n");
				bus_reset_cleanup(instance);
			पूर्ण अन्यथा अणु
				dsprपूर्णांकk(न_संशोधन_INTR, instance, "unknown interrupt\n");
			पूर्ण
#अगर_घोषित SUN3_SCSI_VME
			dregs->csr |= CSR_DMA_ENABLE;
#पूर्ण_अगर
		पूर्ण
		handled = 1;
	पूर्ण अन्यथा अणु
		dsprपूर्णांकk(न_संशोधन_INTR, instance, "interrupt without IRQ bit\n");
#अगर_घोषित SUN3_SCSI_VME
		dregs->csr |= CSR_DMA_ENABLE;
#पूर्ण_अगर
	पूर्ण

	spin_unlock_irqrestore(&hostdata->lock, flags);

	वापस IRQ_RETVAL(handled);
पूर्ण

/**
 * NCR5380_select - attempt arbitration and selection क्रम a given command
 * @instance: the Scsi_Host instance
 * @cmd: the scsi_cmnd to execute
 *
 * This routine establishes an I_T_L nexus क्रम a SCSI command. This involves
 * ARBITRATION, SELECTION and MESSAGE OUT phases and an IDENTIFY message.
 *
 * Returns true अगर the operation should be retried.
 * Returns false अगर it should not be retried.
 *
 * Side effects :
 * If bus busy, arbitration failed, etc, NCR5380_select() will निकास
 * with रेजिस्टरs as they should have been on entry - ie
 * SELECT_ENABLE will be set appropriately, the NCR5380
 * will cease to drive any SCSI bus संकेतs.
 *
 * If successful : the I_T_L nexus will be established, and
 * hostdata->connected will be set to cmd.
 * SELECT पूर्णांकerrupt will be disabled.
 *
 * If failed (no target) : cmd->scsi_करोne() will be called, and the
 * cmd->result host byte set to DID_BAD_TARGET.
 */

अटल bool NCR5380_select(काष्ठा Scsi_Host *instance, काष्ठा scsi_cmnd *cmd)
	__releases(&hostdata->lock) __acquires(&hostdata->lock)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	अचिन्हित अक्षर पंचांगp[3], phase;
	अचिन्हित अक्षर *data;
	पूर्णांक len;
	पूर्णांक err;
	bool ret = true;
	bool can_disconnect = instance->irq != NO_IRQ &&
			      cmd->cmnd[0] != REQUEST_SENSE &&
			      (disconnect_mask & BIT(scmd_id(cmd)));

	NCR5380_dprपूर्णांक(न_संशोधन_ARBITRATION, instance);
	dsprपूर्णांकk(न_संशोधन_ARBITRATION, instance, "starting arbitration, id = %d\n",
	         instance->this_id);

	/*
	 * Arbitration and selection phases are slow and involve dropping the
	 * lock, so we have to watch out क्रम EH. An exception handler may
	 * change 'selecting' to शून्य. This function will then वापस false
	 * so that the caller will क्रमget about 'cmd'. (During inक्रमmation
	 * transfer phases, EH may change 'connected' to शून्य.)
	 */
	hostdata->selecting = cmd;

	/*
	 * Set the phase bits to 0, otherwise the NCR5380 won't drive the
	 * data bus during SELECTION.
	 */

	NCR5380_ग_लिखो(TARGET_COMMAND_REG, 0);

	/*
	 * Start arbitration.
	 */

	NCR5380_ग_लिखो(OUTPUT_DATA_REG, hostdata->id_mask);
	NCR5380_ग_लिखो(MODE_REG, MR_ARBITRATE);

	/* The chip now रुकोs क्रम BUS FREE phase. Then after the 800 ns
	 * Bus Free Delay, arbitration will begin.
	 */

	spin_unlock_irq(&hostdata->lock);
	err = NCR5380_poll_politely2(hostdata, MODE_REG, MR_ARBITRATE, 0,
	                INITIATOR_COMMAND_REG, ICR_ARBITRATION_PROGRESS,
	                                       ICR_ARBITRATION_PROGRESS, HZ);
	spin_lock_irq(&hostdata->lock);
	अगर (!(NCR5380_पढ़ो(MODE_REG) & MR_ARBITRATE)) अणु
		/* Reselection पूर्णांकerrupt */
		जाओ out;
	पूर्ण
	अगर (!hostdata->selecting) अणु
		/* Command was पातed */
		NCR5380_ग_लिखो(MODE_REG, MR_BASE);
		वापस false;
	पूर्ण
	अगर (err < 0) अणु
		NCR5380_ग_लिखो(MODE_REG, MR_BASE);
		shost_prपूर्णांकk(KERN_ERR, instance,
		             "select: arbitration timeout\n");
		जाओ out;
	पूर्ण
	spin_unlock_irq(&hostdata->lock);

	/* The SCSI-2 arbitration delay is 2.4 us */
	udelay(3);

	/* Check क्रम lost arbitration */
	अगर ((NCR5380_पढ़ो(INITIATOR_COMMAND_REG) & ICR_ARBITRATION_LOST) ||
	    (NCR5380_पढ़ो(CURRENT_SCSI_DATA_REG) & hostdata->id_higher_mask) ||
	    (NCR5380_पढ़ो(INITIATOR_COMMAND_REG) & ICR_ARBITRATION_LOST)) अणु
		NCR5380_ग_लिखो(MODE_REG, MR_BASE);
		dsprपूर्णांकk(न_संशोधन_ARBITRATION, instance, "lost arbitration, deasserting MR_ARBITRATE\n");
		spin_lock_irq(&hostdata->lock);
		जाओ out;
	पूर्ण

	/* After/during arbitration, BSY should be निश्चितed.
	 * IBM DPES-31080 Version S31Q works now
	 * Tnx to Thomas_Roesch@m2.maus.de क्रम finding this! (Roman)
	 */
	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG,
		      ICR_BASE | ICR_ASSERT_SEL | ICR_ASSERT_BSY);

	/*
	 * Again, bus clear + bus settle समय is 1.2us, however, this is
	 * a minimum so we'll udelay उच्चमान(1.2)
	 */

	अगर (hostdata->flags & FLAG_TOSHIBA_DELAY)
		udelay(15);
	अन्यथा
		udelay(2);

	spin_lock_irq(&hostdata->lock);

	/* NCR5380_reselect() clears MODE_REG after a reselection पूर्णांकerrupt */
	अगर (!(NCR5380_पढ़ो(MODE_REG) & MR_ARBITRATE))
		जाओ out;

	अगर (!hostdata->selecting) अणु
		NCR5380_ग_लिखो(MODE_REG, MR_BASE);
		NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
		वापस false;
	पूर्ण

	dsprपूर्णांकk(न_संशोधन_ARBITRATION, instance, "won arbitration\n");

	/*
	 * Now that we have won arbitration, start Selection process, निश्चितing
	 * the host and target ID's on the SCSI bus.
	 */

	NCR5380_ग_लिखो(OUTPUT_DATA_REG, hostdata->id_mask | (1 << scmd_id(cmd)));

	/*
	 * Raise ATN जबतक SEL is true beक्रमe BSY goes false from arbitration,
	 * since this is the only way to guarantee that we'll get a MESSAGE OUT
	 * phase immediately after selection.
	 */

	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_BSY |
	              ICR_ASSERT_DATA | ICR_ASSERT_ATN | ICR_ASSERT_SEL);
	NCR5380_ग_लिखो(MODE_REG, MR_BASE);

	/*
	 * Reselect पूर्णांकerrupts must be turned off prior to the dropping of BSY,
	 * otherwise we will trigger an पूर्णांकerrupt.
	 */
	NCR5380_ग_लिखो(SELECT_ENABLE_REG, 0);

	spin_unlock_irq(&hostdata->lock);

	/*
	 * The initiator shall then रुको at least two deskew delays and release
	 * the BSY संकेत.
	 */
	udelay(1);        /* wingel -- रुको two bus deskew delay >2*45ns */

	/* Reset BSY */
	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_DATA |
	              ICR_ASSERT_ATN | ICR_ASSERT_SEL);

	/*
	 * Something weird happens when we cease to drive BSY - looks
	 * like the board/chip is letting us करो another पढ़ो beक्रमe the
	 * appropriate propagation delay has expired, and we're confusing
	 * a BSY संकेत from ourselves as the target's response to SELECTION.
	 *
	 * A small delay (the 'C++' frontend अवरोधs the pipeline with an
	 * unnecessary jump, making it work on my 386-33/Trantor T128, the
	 * tighter 'C' code अवरोधs and requires this) solves the problem -
	 * the 1 us delay is arbitrary, and only used because this delay will
	 * be the same on other platक्रमms and since it works here, it should
	 * work there.
	 *
	 * wingel suggests that this could be due to failing to रुको
	 * one deskew delay.
	 */

	udelay(1);

	dsprपूर्णांकk(न_संशोधन_SELECTION, instance, "selecting target %d\n", scmd_id(cmd));

	/*
	 * The SCSI specअगरication calls क्रम a 250 ms समयout क्रम the actual
	 * selection.
	 */

	err = NCR5380_poll_politely(hostdata, STATUS_REG, SR_BSY, SR_BSY,
	                            msecs_to_jअगरfies(250));

	अगर ((NCR5380_पढ़ो(STATUS_REG) & (SR_SEL | SR_IO)) == (SR_SEL | SR_IO)) अणु
		spin_lock_irq(&hostdata->lock);
		NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
		NCR5380_reselect(instance);
		shost_prपूर्णांकk(KERN_ERR, instance, "reselection after won arbitration?\n");
		जाओ out;
	पूर्ण

	अगर (err < 0) अणु
		spin_lock_irq(&hostdata->lock);
		NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);

		/* Can't touch cmd अगर it has been reclaimed by the scsi ML */
		अगर (!hostdata->selecting)
			वापस false;

		cmd->result = DID_BAD_TARGET << 16;
		complete_cmd(instance, cmd);
		dsprपूर्णांकk(न_संशोधन_SELECTION, instance,
			"target did not respond within 250ms\n");
		ret = false;
		जाओ out;
	पूर्ण

	/*
	 * No less than two deskew delays after the initiator detects the
	 * BSY संकेत is true, it shall release the SEL संकेत and may
	 * change the DATA BUS.                                     -wingel
	 */

	udelay(1);

	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ATN);

	/*
	 * Since we followed the SCSI spec, and उठाओd ATN जबतक SEL
	 * was true but beक्रमe BSY was false during selection, the inक्रमmation
	 * transfer phase should be a MESSAGE OUT phase so that we can send the
	 * IDENTIFY message.
	 */

	/* Wait क्रम start of REQ/ACK handshake */

	err = NCR5380_poll_politely(hostdata, STATUS_REG, SR_REQ, SR_REQ, HZ);
	spin_lock_irq(&hostdata->lock);
	अगर (err < 0) अणु
		shost_prपूर्णांकk(KERN_ERR, instance, "select: REQ timeout\n");
		NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
		जाओ out;
	पूर्ण
	अगर (!hostdata->selecting) अणु
		करो_पात(instance, 0);
		वापस false;
	पूर्ण

	dsprपूर्णांकk(न_संशोधन_SELECTION, instance, "target %d selected, going into MESSAGE OUT phase.\n",
	         scmd_id(cmd));
	पंचांगp[0] = IDENTIFY(can_disconnect, cmd->device->lun);

	len = 1;
	data = पंचांगp;
	phase = PHASE_MSGOUT;
	NCR5380_transfer_pio(instance, &phase, &len, &data, 0);
	अगर (len) अणु
		NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
		cmd->result = DID_ERROR << 16;
		complete_cmd(instance, cmd);
		dsprपूर्णांकk(न_संशोधन_SELECTION, instance, "IDENTIFY message transfer failed\n");
		ret = false;
		जाओ out;
	पूर्ण

	dsprपूर्णांकk(न_संशोधन_SELECTION, instance, "nexus established.\n");

	hostdata->connected = cmd;
	hostdata->busy[cmd->device->id] |= 1 << cmd->device->lun;

#अगर_घोषित SUN3_SCSI_VME
	dregs->csr |= CSR_INTR;
#पूर्ण_अगर

	initialize_SCp(cmd);

	ret = false;

out:
	अगर (!hostdata->selecting)
		वापस false;
	hostdata->selecting = शून्य;
	वापस ret;
पूर्ण

/*
 * Function : पूर्णांक NCR5380_transfer_pio (काष्ठा Scsi_Host *instance,
 * अचिन्हित अक्षर *phase, पूर्णांक *count, अचिन्हित अक्षर **data)
 *
 * Purpose : transfers data in given phase using polled I/O
 *
 * Inमाला_दो : instance - instance of driver, *phase - poपूर्णांकer to
 * what phase is expected, *count - poपूर्णांकer to number of
 * bytes to transfer, **data - poपूर्णांकer to data poपूर्णांकer,
 * can_sleep - 1 or 0 when sleeping is permitted or not, respectively.
 *
 * Returns : -1 when dअगरferent phase is entered without transferring
 * maximum number of bytes, 0 अगर all bytes are transferred or निकास
 * is in same phase.
 *
 * Also, *phase, *count, *data are modअगरied in place.
 *
 * XXX Note : handling क्रम bus मुक्त may be useful.
 */

/*
 * Note : this code is not as quick as it could be, however it
 * IS 100% reliable, and क्रम the actual data transfer where speed
 * counts, we will always करो a pseuकरो DMA or DMA transfer.
 */

अटल पूर्णांक NCR5380_transfer_pio(काष्ठा Scsi_Host *instance,
				अचिन्हित अक्षर *phase, पूर्णांक *count,
				अचिन्हित अक्षर **data, अचिन्हित पूर्णांक can_sleep)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	अचिन्हित अक्षर p = *phase, पंचांगp;
	पूर्णांक c = *count;
	अचिन्हित अक्षर *d = *data;

	/*
	 * The NCR5380 chip will only drive the SCSI bus when the
	 * phase specअगरied in the appropriate bits of the TARGET COMMAND
	 * REGISTER match the STATUS REGISTER
	 */

	NCR5380_ग_लिखो(TARGET_COMMAND_REG, PHASE_SR_TO_TCR(p));

	करो अणु
		/*
		 * Wait क्रम निश्चितion of REQ, after which the phase bits will be
		 * valid
		 */

		अगर (NCR5380_poll_politely(hostdata, STATUS_REG, SR_REQ, SR_REQ,
					  HZ * can_sleep) < 0)
			अवरोध;

		dsprपूर्णांकk(न_संशोधन_HANDSHAKE, instance, "REQ asserted\n");

		/* Check क्रम phase mismatch */
		अगर ((NCR5380_पढ़ो(STATUS_REG) & PHASE_MASK) != p) अणु
			dsprपूर्णांकk(न_संशोधन_PIO, instance, "phase mismatch\n");
			NCR5380_dprपूर्णांक_phase(न_संशोधन_PIO, instance);
			अवरोध;
		पूर्ण

		/* Do actual transfer from SCSI bus to / from memory */
		अगर (!(p & SR_IO))
			NCR5380_ग_लिखो(OUTPUT_DATA_REG, *d);
		अन्यथा
			*d = NCR5380_पढ़ो(CURRENT_SCSI_DATA_REG);

		++d;

		/*
		 * The SCSI standard suggests that in MSGOUT phase, the initiator
		 * should drop ATN on the last byte of the message phase
		 * after REQ has been निश्चितed क्रम the handshake but beक्रमe
		 * the initiator उठाओs ACK.
		 */

		अगर (!(p & SR_IO)) अणु
			अगर (!((p & SR_MSG) && c > 1)) अणु
				NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_DATA);
				NCR5380_dprपूर्णांक(न_संशोधन_PIO, instance);
				NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE |
				              ICR_ASSERT_DATA | ICR_ASSERT_ACK);
			पूर्ण अन्यथा अणु
				NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE |
				              ICR_ASSERT_DATA | ICR_ASSERT_ATN);
				NCR5380_dprपूर्णांक(न_संशोधन_PIO, instance);
				NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE |
				              ICR_ASSERT_DATA | ICR_ASSERT_ATN | ICR_ASSERT_ACK);
			पूर्ण
		पूर्ण अन्यथा अणु
			NCR5380_dprपूर्णांक(न_संशोधन_PIO, instance);
			NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ACK);
		पूर्ण

		अगर (NCR5380_poll_politely(hostdata,
		                          STATUS_REG, SR_REQ, 0, 5 * HZ * can_sleep) < 0)
			अवरोध;

		dsprपूर्णांकk(न_संशोधन_HANDSHAKE, instance, "REQ negated, handshake complete\n");

/*
 * We have several special हालs to consider during REQ/ACK handshaking :
 * 1.  We were in MSGOUT phase, and we are on the last byte of the
 * message.  ATN must be dropped as ACK is dropped.
 *
 * 2.  We are in a MSGIN phase, and we are on the last byte of the
 * message.  We must निकास with ACK निश्चितed, so that the calling
 * code may उठाओ ATN beक्रमe dropping ACK to reject the message.
 *
 * 3.  ACK and ATN are clear and the target may proceed as normal.
 */
		अगर (!(p == PHASE_MSGIN && c == 1)) अणु
			अगर (p == PHASE_MSGOUT && c > 1)
				NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ATN);
			अन्यथा
				NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
		पूर्ण
	पूर्ण जबतक (--c);

	dsprपूर्णांकk(न_संशोधन_PIO, instance, "residual %d\n", c);

	*count = c;
	*data = d;
	पंचांगp = NCR5380_पढ़ो(STATUS_REG);
	/* The phase पढ़ो from the bus is valid अगर either REQ is (alपढ़ोy)
	 * निश्चितed or अगर ACK hasn't been released yet. The latter applies अगर
	 * we're in MSG IN, DATA IN or STATUS and all bytes have been received.
	 */
	अगर ((पंचांगp & SR_REQ) || ((पंचांगp & SR_IO) && c == 0))
		*phase = पंचांगp & PHASE_MASK;
	अन्यथा
		*phase = PHASE_UNKNOWN;

	अगर (!c || (*phase == p))
		वापस 0;
	अन्यथा
		वापस -1;
पूर्ण

/**
 * करो_reset - issue a reset command
 * @instance: adapter to reset
 *
 * Issue a reset sequence to the NCR5380 and try and get the bus
 * back पूर्णांकo sane shape.
 *
 * This clears the reset पूर्णांकerrupt flag because there may be no handler क्रम
 * it. When the driver is initialized, the NCR5380_पूर्णांकr() handler has not yet
 * been installed. And when in EH we may have released the ST DMA पूर्णांकerrupt.
 */

अटल व्योम करो_reset(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata __maybe_unused *hostdata = shost_priv(instance);
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	NCR5380_ग_लिखो(TARGET_COMMAND_REG,
	              PHASE_SR_TO_TCR(NCR5380_पढ़ो(STATUS_REG) & PHASE_MASK));
	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_RST);
	udelay(50);
	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
	(व्योम)NCR5380_पढ़ो(RESET_PARITY_INTERRUPT_REG);
	local_irq_restore(flags);
पूर्ण

/**
 * करो_पात - पात the currently established nexus by going to
 * MESSAGE OUT phase and sending an ABORT message.
 * @instance: relevant scsi host instance
 * @can_sleep: 1 or 0 when sleeping is permitted or not, respectively
 *
 * Returns 0 on success, negative error code on failure.
 */

अटल पूर्णांक करो_पात(काष्ठा Scsi_Host *instance, अचिन्हित पूर्णांक can_sleep)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	अचिन्हित अक्षर *msgptr, phase, पंचांगp;
	पूर्णांक len;
	पूर्णांक rc;

	/* Request message out phase */
	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ATN);

	/*
	 * Wait क्रम the target to indicate a valid phase by निश्चितing
	 * REQ.  Once this happens, we'll have either a MSGOUT phase
	 * and can immediately send the ABORT message, or we'll have some
	 * other phase and will have to source/sink data.
	 *
	 * We really करोn't care what value was on the bus or what value
	 * the target sees, so we just handshake.
	 */

	rc = NCR5380_poll_politely(hostdata, STATUS_REG, SR_REQ, SR_REQ,
				   10 * HZ * can_sleep);
	अगर (rc < 0)
		जाओ out;

	पंचांगp = NCR5380_पढ़ो(STATUS_REG) & PHASE_MASK;

	NCR5380_ग_लिखो(TARGET_COMMAND_REG, PHASE_SR_TO_TCR(पंचांगp));

	अगर (पंचांगp != PHASE_MSGOUT) अणु
		NCR5380_ग_लिखो(INITIATOR_COMMAND_REG,
		              ICR_BASE | ICR_ASSERT_ATN | ICR_ASSERT_ACK);
		rc = NCR5380_poll_politely(hostdata, STATUS_REG, SR_REQ, 0,
					   3 * HZ * can_sleep);
		अगर (rc < 0)
			जाओ out;
		NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ATN);
	पूर्ण

	पंचांगp = ABORT;
	msgptr = &पंचांगp;
	len = 1;
	phase = PHASE_MSGOUT;
	NCR5380_transfer_pio(instance, &phase, &len, &msgptr, can_sleep);
	अगर (len)
		rc = -ENXIO;

	/*
	 * If we got here, and the command completed successfully,
	 * we're about to go पूर्णांकo bus मुक्त state.
	 */

out:
	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
	वापस rc;
पूर्ण

/*
 * Function : पूर्णांक NCR5380_transfer_dma (काष्ठा Scsi_Host *instance,
 * अचिन्हित अक्षर *phase, पूर्णांक *count, अचिन्हित अक्षर **data)
 *
 * Purpose : transfers data in given phase using either real
 * or pseuकरो DMA.
 *
 * Inमाला_दो : instance - instance of driver, *phase - poपूर्णांकer to
 * what phase is expected, *count - poपूर्णांकer to number of
 * bytes to transfer, **data - poपूर्णांकer to data poपूर्णांकer.
 *
 * Returns : -1 when dअगरferent phase is entered without transferring
 * maximum number of bytes, 0 अगर all bytes or transferred or निकास
 * is in same phase.
 *
 * Also, *phase, *count, *data are modअगरied in place.
 */


अटल पूर्णांक NCR5380_transfer_dma(काष्ठा Scsi_Host *instance,
				अचिन्हित अक्षर *phase, पूर्णांक *count,
				अचिन्हित अक्षर **data)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	पूर्णांक c = *count;
	अचिन्हित अक्षर p = *phase;
	अचिन्हित अक्षर *d = *data;
	अचिन्हित अक्षर पंचांगp;
	पूर्णांक result = 0;

	अगर ((पंचांगp = (NCR5380_पढ़ो(STATUS_REG) & PHASE_MASK)) != p) अणु
		*phase = पंचांगp;
		वापस -1;
	पूर्ण

	hostdata->connected->SCp.phase = p;

	अगर (p & SR_IO) अणु
		अगर (hostdata->पढ़ो_overruns)
			c -= hostdata->पढ़ो_overruns;
		अन्यथा अगर (hostdata->flags & FLAG_DMA_FIXUP)
			--c;
	पूर्ण

	dsprपूर्णांकk(न_संशोधन_DMA, instance, "initializing DMA %s: length %d, address %p\n",
	         (p & SR_IO) ? "receive" : "send", c, d);

#अगर_घोषित CONFIG_SUN3
	/* send start chain */
	sun3scsi_dma_start(c, *data);
#पूर्ण_अगर

	NCR5380_ग_लिखो(TARGET_COMMAND_REG, PHASE_SR_TO_TCR(p));
	NCR5380_ग_लिखो(MODE_REG, MR_BASE | MR_DMA_MODE | MR_MONITOR_BSY |
	                        MR_ENABLE_EOP_INTR);

	अगर (!(hostdata->flags & FLAG_LATE_DMA_SETUP)) अणु
		/* On the Medusa, it is a must to initialize the DMA beक्रमe
		 * starting the NCR. This is also the cleaner way क्रम the TT.
		 */
		अगर (p & SR_IO)
			result = NCR5380_dma_recv_setup(hostdata, d, c);
		अन्यथा
			result = NCR5380_dma_send_setup(hostdata, d, c);
	पूर्ण

	/*
	 * On the PAS16 at least I/O recovery delays are not needed here.
	 * Everyone अन्यथा seems to want them.
	 */

	अगर (p & SR_IO) अणु
		NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
		NCR5380_io_delay(1);
		NCR5380_ग_लिखो(START_DMA_INITIATOR_RECEIVE_REG, 0);
	पूर्ण अन्यथा अणु
		NCR5380_io_delay(1);
		NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_DATA);
		NCR5380_io_delay(1);
		NCR5380_ग_लिखो(START_DMA_SEND_REG, 0);
		NCR5380_io_delay(1);
	पूर्ण

#अगर_घोषित CONFIG_SUN3
#अगर_घोषित SUN3_SCSI_VME
	dregs->csr |= CSR_DMA_ENABLE;
#पूर्ण_अगर
	sun3_dma_active = 1;
#पूर्ण_अगर

	अगर (hostdata->flags & FLAG_LATE_DMA_SETUP) अणु
		/* On the Falcon, the DMA setup must be करोne after the last
		 * NCR access, अन्यथा the DMA setup माला_लो trashed!
		 */
		अगर (p & SR_IO)
			result = NCR5380_dma_recv_setup(hostdata, d, c);
		अन्यथा
			result = NCR5380_dma_send_setup(hostdata, d, c);
	पूर्ण

	/* On failure, NCR5380_dma_xxxx_setup() वापसs a negative पूर्णांक. */
	अगर (result < 0)
		वापस result;

	/* For real DMA, result is the byte count. DMA पूर्णांकerrupt is expected. */
	अगर (result > 0) अणु
		hostdata->dma_len = result;
		वापस 0;
	पूर्ण

	/* The result is zero अगरf pseuकरो DMA send/receive was completed. */
	hostdata->dma_len = c;

/*
 * A note regarding the DMA errata workarounds क्रम early NMOS silicon.
 *
 * For DMA sends, we want to रुको until the last byte has been
 * transferred out over the bus beक्रमe we turn off DMA mode.  Alas, there
 * seems to be no terribly good way of करोing this on a 5380 under all
 * conditions.  For non-scatter-gather operations, we can रुको until REQ
 * and ACK both go false, or until a phase mismatch occurs.  Gather-sends
 * are nastier, since the device will be expecting more data than we
 * are prepared to send it, and REQ will reमुख्य निश्चितed.  On a 53C8[01] we
 * could test Last Byte Sent to assure transfer (I imagine this is precisely
 * why this संकेत was added to the newer chips) but on the older 538[01]
 * this संकेत करोes not exist.  The workaround क्रम this lack is a watchकरोg;
 * we bail out of the रुको-loop after a modest amount of रुको-समय अगर
 * the usual निकास conditions are not met.  Not a terribly clean or
 * correct solution :-%
 *
 * DMA receive is equally tricky due to a nasty अक्षरacteristic of the NCR5380.
 * If the chip is in DMA receive mode, it will respond to a target's
 * REQ by latching the SCSI data पूर्णांकo the INPUT DATA रेजिस्टर and निश्चितing
 * ACK, even अगर it has _alपढ़ोy_ been notअगरied by the DMA controller that
 * the current DMA transfer has completed!  If the NCR5380 is then taken
 * out of DMA mode, this alपढ़ोy-acknowledged byte is lost. This is
 * not a problem क्रम "one DMA transfer per READ command", because
 * the situation will never arise... either all of the data is DMA'ed
 * properly, or the target चयनes to MESSAGE IN phase to संकेत a
 * disconnection (either operation bringing the DMA to a clean halt).
 * However, in order to handle scatter-receive, we must work around the
 * problem.  The chosen fix is to DMA fewer bytes, then check क्रम the
 * condition beक्रमe taking the NCR5380 out of DMA mode.  One or two extra
 * bytes are transferred via PIO as necessary to fill out the original
 * request.
 */

	अगर (hostdata->flags & FLAG_DMA_FIXUP) अणु
		अगर (p & SR_IO) अणु
			/*
			 * The workaround was to transfer fewer bytes than we
			 * पूर्णांकended to with the pseuकरो-DMA पढ़ो function, रुको क्रम
			 * the chip to latch the last byte, पढ़ो it, and then disable
			 * pseuकरो-DMA mode.
			 *
			 * After REQ is निश्चितed, the NCR5380 निश्चितs DRQ and ACK.
			 * REQ is deनिश्चितed when ACK is निश्चितed, and not reनिश्चितed
			 * until ACK goes false.  Since the NCR5380 won't lower ACK
			 * until DACK is निश्चितed, which won't happen unless we twiddle
			 * the DMA port or we take the NCR5380 out of DMA mode, we
			 * can guarantee that we won't handshake another extra
			 * byte.
			 */

			अगर (NCR5380_poll_politely(hostdata, BUS_AND_STATUS_REG,
			                          BASR_DRQ, BASR_DRQ, 0) < 0) अणु
				result = -1;
				shost_prपूर्णांकk(KERN_ERR, instance, "PDMA read: DRQ timeout\n");
			पूर्ण
			अगर (NCR5380_poll_politely(hostdata, STATUS_REG,
			                          SR_REQ, 0, 0) < 0) अणु
				result = -1;
				shost_prपूर्णांकk(KERN_ERR, instance, "PDMA read: !REQ timeout\n");
			पूर्ण
			d[*count - 1] = NCR5380_पढ़ो(INPUT_DATA_REG);
		पूर्ण अन्यथा अणु
			/*
			 * Wait क्रम the last byte to be sent.  If REQ is being निश्चितed क्रम
			 * the byte we're interested, we'll ACK it and it will go false.
			 */
			अगर (NCR5380_poll_politely2(hostdata,
			     BUS_AND_STATUS_REG, BASR_DRQ, BASR_DRQ,
			     BUS_AND_STATUS_REG, BASR_PHASE_MATCH, 0, 0) < 0) अणु
				result = -1;
				shost_prपूर्णांकk(KERN_ERR, instance, "PDMA write: DRQ and phase timeout\n");
			पूर्ण
		पूर्ण
	पूर्ण

	NCR5380_dma_complete(instance);
	वापस result;
पूर्ण

/*
 * Function : NCR5380_inक्रमmation_transfer (काष्ठा Scsi_Host *instance)
 *
 * Purpose : run through the various SCSI phases and करो as the target
 * directs us to.  Operates on the currently connected command,
 * instance->connected.
 *
 * Inमाला_दो : instance, instance क्रम which we are करोing commands
 *
 * Side effects : SCSI things happen, the disconnected queue will be
 * modअगरied अगर a command disconnects, *instance->connected will
 * change.
 *
 * XXX Note : we need to watch क्रम bus मुक्त or a reset condition here
 * to recover from an unexpected bus मुक्त condition.
 */

अटल व्योम NCR5380_inक्रमmation_transfer(काष्ठा Scsi_Host *instance)
	__releases(&hostdata->lock) __acquires(&hostdata->lock)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	अचिन्हित अक्षर msgout = NOP;
	पूर्णांक sink = 0;
	पूर्णांक len;
	पूर्णांक transfersize;
	अचिन्हित अक्षर *data;
	अचिन्हित अक्षर phase, पंचांगp, extended_msg[10], old_phase = 0xff;
	काष्ठा scsi_cmnd *cmd;

#अगर_घोषित SUN3_SCSI_VME
	dregs->csr |= CSR_INTR;
#पूर्ण_अगर

	जबतक ((cmd = hostdata->connected)) अणु
		काष्ठा NCR5380_cmd *ncmd = scsi_cmd_priv(cmd);

		पंचांगp = NCR5380_पढ़ो(STATUS_REG);
		/* We only have a valid SCSI phase when REQ is निश्चितed */
		अगर (पंचांगp & SR_REQ) अणु
			phase = (पंचांगp & PHASE_MASK);
			अगर (phase != old_phase) अणु
				old_phase = phase;
				NCR5380_dprपूर्णांक_phase(न_संशोधन_INFORMATION, instance);
			पूर्ण
#अगर_घोषित CONFIG_SUN3
			अगर (phase == PHASE_CMDOUT &&
			    sun3_dma_setup_करोne != cmd) अणु
				पूर्णांक count;

				advance_sg_buffer(cmd);

				count = sun3scsi_dma_xfer_len(hostdata, cmd);

				अगर (count > 0) अणु
					अगर (rq_data_dir(cmd->request))
						sun3scsi_dma_send_setup(hostdata,
						                        cmd->SCp.ptr, count);
					अन्यथा
						sun3scsi_dma_recv_setup(hostdata,
						                        cmd->SCp.ptr, count);
					sun3_dma_setup_करोne = cmd;
				पूर्ण
#अगर_घोषित SUN3_SCSI_VME
				dregs->csr |= CSR_INTR;
#पूर्ण_अगर
			पूर्ण
#पूर्ण_अगर /* CONFIG_SUN3 */

			अगर (sink && (phase != PHASE_MSGOUT)) अणु
				NCR5380_ग_लिखो(TARGET_COMMAND_REG, PHASE_SR_TO_TCR(पंचांगp));

				NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ATN |
				              ICR_ASSERT_ACK);
				जबतक (NCR5380_पढ़ो(STATUS_REG) & SR_REQ)
					;
				NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE |
				              ICR_ASSERT_ATN);
				sink = 0;
				जारी;
			पूर्ण

			चयन (phase) अणु
			हाल PHASE_DATAOUT:
#अगर (न_संशोधन & न_संशोधन_NO_DATAOUT)
				shost_prपूर्णांकk(KERN_DEBUG, instance, "NDEBUG_NO_DATAOUT set, attempted DATAOUT aborted\n");
				sink = 1;
				करो_पात(instance, 0);
				cmd->result = DID_ERROR << 16;
				complete_cmd(instance, cmd);
				hostdata->connected = शून्य;
				hostdata->busy[scmd_id(cmd)] &= ~(1 << cmd->device->lun);
				वापस;
#पूर्ण_अगर
			हाल PHASE_DATAIN:
				/*
				 * If there is no room left in the current buffer in the
				 * scatter-gather list, move onto the next one.
				 */

				advance_sg_buffer(cmd);
				dsprपूर्णांकk(न_संशोधन_INFORMATION, instance,
					"this residual %d, sg ents %d\n",
					cmd->SCp.this_residual,
					sg_nents(cmd->SCp.buffer));

				/*
				 * The preferred transfer method is going to be
				 * PSEUDO-DMA क्रम प्रणालीs that are strictly PIO,
				 * since we can let the hardware करो the handshaking.
				 *
				 * For this to work, we need to know the transfersize
				 * ahead of समय, since the pseuकरो-DMA code will sit
				 * in an unconditional loop.
				 */

				transfersize = 0;
				अगर (!cmd->device->borken)
					transfersize = NCR5380_dma_xfer_len(hostdata, cmd);

				अगर (transfersize > 0) अणु
					len = transfersize;
					अगर (NCR5380_transfer_dma(instance, &phase,
					    &len, (अचिन्हित अक्षर **)&cmd->SCp.ptr)) अणु
						/*
						 * If the watchकरोg समयr fires, all future
						 * accesses to this device will use the
						 * polled-IO.
						 */
						scmd_prपूर्णांकk(KERN_INFO, cmd,
							"switching to slow handshake\n");
						cmd->device->borken = 1;
						करो_reset(instance);
						bus_reset_cleanup(instance);
					पूर्ण
				पूर्ण अन्यथा अणु
					/* Transfer a small chunk so that the
					 * irq mode lock is not held too दीर्घ.
					 */
					transfersize = min(cmd->SCp.this_residual,
							   NCR5380_PIO_CHUNK_SIZE);
					len = transfersize;
					NCR5380_transfer_pio(instance, &phase, &len,
					                     (अचिन्हित अक्षर **)&cmd->SCp.ptr,
							     0);
					cmd->SCp.this_residual -= transfersize - len;
				पूर्ण
#अगर_घोषित CONFIG_SUN3
				अगर (sun3_dma_setup_करोne == cmd)
					sun3_dma_setup_करोne = शून्य;
#पूर्ण_अगर
				वापस;
			हाल PHASE_MSGIN:
				len = 1;
				data = &पंचांगp;
				NCR5380_transfer_pio(instance, &phase, &len, &data, 0);
				cmd->SCp.Message = पंचांगp;

				चयन (पंचांगp) अणु
				हाल ABORT:
				हाल COMMAND_COMPLETE:
					/* Accept message by clearing ACK */
					sink = 1;
					NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
					dsprपूर्णांकk(न_संशोधन_QUEUES, instance,
					         "COMMAND COMPLETE %p target %d lun %llu\n",
					         cmd, scmd_id(cmd), cmd->device->lun);

					hostdata->connected = शून्य;
					hostdata->busy[scmd_id(cmd)] &= ~(1 << cmd->device->lun);

					cmd->result &= ~0xffff;
					cmd->result |= cmd->SCp.Status;
					cmd->result |= cmd->SCp.Message << 8;

					set_resid_from_SCp(cmd);

					अगर (cmd->cmnd[0] == REQUEST_SENSE)
						complete_cmd(instance, cmd);
					अन्यथा अणु
						अगर (cmd->SCp.Status == SAM_STAT_CHECK_CONDITION ||
						    cmd->SCp.Status == SAM_STAT_COMMAND_TERMINATED) अणु
							dsprपूर्णांकk(न_संशोधन_QUEUES, instance, "autosense: adding cmd %p to tail of autosense queue\n",
							         cmd);
							list_add_tail(&ncmd->list,
							              &hostdata->स्वतःsense);
						पूर्ण अन्यथा
							complete_cmd(instance, cmd);
					पूर्ण

					/*
					 * Restore phase bits to 0 so an पूर्णांकerrupted selection,
					 * arbitration can resume.
					 */
					NCR5380_ग_लिखो(TARGET_COMMAND_REG, 0);

					वापस;
				हाल MESSAGE_REJECT:
					/* Accept message by clearing ACK */
					NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
					चयन (hostdata->last_message) अणु
					हाल HEAD_OF_QUEUE_TAG:
					हाल ORDERED_QUEUE_TAG:
					हाल SIMPLE_QUEUE_TAG:
						cmd->device->simple_tags = 0;
						hostdata->busy[cmd->device->id] |= (1 << (cmd->device->lun & 0xFF));
						अवरोध;
					शेष:
						अवरोध;
					पूर्ण
					अवरोध;
				हाल DISCONNECT:
					/* Accept message by clearing ACK */
					NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
					hostdata->connected = शून्य;
					list_add(&ncmd->list, &hostdata->disconnected);
					dsprपूर्णांकk(न_संशोधन_INFORMATION | न_संशोधन_QUEUES,
					         instance, "connected command %p for target %d lun %llu moved to disconnected queue\n",
					         cmd, scmd_id(cmd), cmd->device->lun);

					/*
					 * Restore phase bits to 0 so an पूर्णांकerrupted selection,
					 * arbitration can resume.
					 */
					NCR5380_ग_लिखो(TARGET_COMMAND_REG, 0);

#अगर_घोषित SUN3_SCSI_VME
					dregs->csr |= CSR_DMA_ENABLE;
#पूर्ण_अगर
					वापस;
					/*
					 * The SCSI data poपूर्णांकer is *IMPLICITLY* saved on a disconnect
					 * operation, in violation of the SCSI spec so we can safely
					 * ignore SAVE/RESTORE poपूर्णांकers calls.
					 *
					 * Unक्रमtunately, some disks violate the SCSI spec and
					 * करोn't issue the required SAVE_POINTERS message beक्रमe
					 * disconnecting, and we have to अवरोध spec to reमुख्य
					 * compatible.
					 */
				हाल SAVE_POINTERS:
				हाल RESTORE_POINTERS:
					/* Accept message by clearing ACK */
					NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
					अवरोध;
				हाल EXTENDED_MESSAGE:
					/*
					 * Start the message buffer with the EXTENDED_MESSAGE
					 * byte, since spi_prपूर्णांक_msg() wants the whole thing.
					 */
					extended_msg[0] = EXTENDED_MESSAGE;
					/* Accept first byte by clearing ACK */
					NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);

					spin_unlock_irq(&hostdata->lock);

					dsprपूर्णांकk(न_संशोधन_EXTENDED, instance, "receiving extended message\n");

					len = 2;
					data = extended_msg + 1;
					phase = PHASE_MSGIN;
					NCR5380_transfer_pio(instance, &phase, &len, &data, 1);
					dsprपूर्णांकk(न_संशोधन_EXTENDED, instance, "length %d, code 0x%02x\n",
					         (पूर्णांक)extended_msg[1],
					         (पूर्णांक)extended_msg[2]);

					अगर (!len && extended_msg[1] > 0 &&
					    extended_msg[1] <= माप(extended_msg) - 2) अणु
						/* Accept third byte by clearing ACK */
						NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
						len = extended_msg[1] - 1;
						data = extended_msg + 3;
						phase = PHASE_MSGIN;

						NCR5380_transfer_pio(instance, &phase, &len, &data, 1);
						dsprपूर्णांकk(न_संशोधन_EXTENDED, instance, "message received, residual %d\n",
						         len);

						चयन (extended_msg[2]) अणु
						हाल EXTENDED_SDTR:
						हाल EXTENDED_WDTR:
							पंचांगp = 0;
						पूर्ण
					पूर्ण अन्यथा अगर (len) अणु
						shost_prपूर्णांकk(KERN_ERR, instance, "error receiving extended message\n");
						पंचांगp = 0;
					पूर्ण अन्यथा अणु
						shost_prपूर्णांकk(KERN_NOTICE, instance, "extended message code %02x length %d is too long\n",
						             extended_msg[2], extended_msg[1]);
						पंचांगp = 0;
					पूर्ण

					spin_lock_irq(&hostdata->lock);
					अगर (!hostdata->connected)
						वापस;

					/* Reject message */
					fallthrough;
				शेष:
					/*
					 * If we get something weird that we aren't expecting,
					 * log it.
					 */
					अगर (पंचांगp == EXTENDED_MESSAGE)
						scmd_prपूर्णांकk(KERN_INFO, cmd,
						            "rejecting unknown extended message code %02x, length %d\n",
						            extended_msg[2], extended_msg[1]);
					अन्यथा अगर (पंचांगp)
						scmd_prपूर्णांकk(KERN_INFO, cmd,
						            "rejecting unknown message code %02x\n",
						            पंचांगp);

					msgout = MESSAGE_REJECT;
					NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ATN);
					अवरोध;
				पूर्ण /* चयन (पंचांगp) */
				अवरोध;
			हाल PHASE_MSGOUT:
				len = 1;
				data = &msgout;
				hostdata->last_message = msgout;
				NCR5380_transfer_pio(instance, &phase, &len, &data, 0);
				अगर (msgout == ABORT) अणु
					hostdata->connected = शून्य;
					hostdata->busy[scmd_id(cmd)] &= ~(1 << cmd->device->lun);
					cmd->result = DID_ERROR << 16;
					complete_cmd(instance, cmd);
					वापस;
				पूर्ण
				msgout = NOP;
				अवरोध;
			हाल PHASE_CMDOUT:
				len = cmd->cmd_len;
				data = cmd->cmnd;
				/*
				 * XXX क्रम perक्रमmance reasons, on machines with a
				 * PSEUDO-DMA architecture we should probably
				 * use the dma transfer function.
				 */
				NCR5380_transfer_pio(instance, &phase, &len, &data, 0);
				अवरोध;
			हाल PHASE_STATIN:
				len = 1;
				data = &पंचांगp;
				NCR5380_transfer_pio(instance, &phase, &len, &data, 0);
				cmd->SCp.Status = पंचांगp;
				अवरोध;
			शेष:
				shost_prपूर्णांकk(KERN_ERR, instance, "unknown phase\n");
				NCR5380_dprपूर्णांक(न_संशोधन_ANY, instance);
			पूर्ण /* चयन(phase) */
		पूर्ण अन्यथा अणु
			spin_unlock_irq(&hostdata->lock);
			NCR5380_poll_politely(hostdata, STATUS_REG, SR_REQ, SR_REQ, HZ);
			spin_lock_irq(&hostdata->lock);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Function : व्योम NCR5380_reselect (काष्ठा Scsi_Host *instance)
 *
 * Purpose : करोes reselection, initializing the instance->connected
 * field to poपूर्णांक to the scsi_cmnd क्रम which the I_T_L or I_T_L_Q
 * nexus has been reestablished,
 *
 * Inमाला_दो : instance - this instance of the NCR5380.
 */

अटल व्योम NCR5380_reselect(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	अचिन्हित अक्षर target_mask;
	अचिन्हित अक्षर lun;
	अचिन्हित अक्षर msg[3];
	काष्ठा NCR5380_cmd *ncmd;
	काष्ठा scsi_cmnd *पंचांगp;

	/*
	 * Disable arbitration, etc. since the host adapter obviously
	 * lost, and tell an पूर्णांकerrupted NCR5380_select() to restart.
	 */

	NCR5380_ग_लिखो(MODE_REG, MR_BASE);

	target_mask = NCR5380_पढ़ो(CURRENT_SCSI_DATA_REG) & ~(hostdata->id_mask);
	अगर (!target_mask || target_mask & (target_mask - 1)) अणु
		shost_prपूर्णांकk(KERN_WARNING, instance,
			     "reselect: bad target_mask 0x%02x\n", target_mask);
		वापस;
	पूर्ण

	/*
	 * At this poपूर्णांक, we have detected that our SCSI ID is on the bus,
	 * SEL is true and BSY was false क्रम at least one bus settle delay
	 * (400 ns).
	 *
	 * We must निश्चित BSY ourselves, until the target drops the SEL
	 * संकेत.
	 */

	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_BSY);
	अगर (NCR5380_poll_politely(hostdata,
	                          STATUS_REG, SR_SEL, 0, 0) < 0) अणु
		shost_prपूर्णांकk(KERN_ERR, instance, "reselect: !SEL timeout\n");
		NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
		वापस;
	पूर्ण
	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);

	/*
	 * Wait क्रम target to go पूर्णांकo MSGIN.
	 */

	अगर (NCR5380_poll_politely(hostdata,
	                          STATUS_REG, SR_REQ, SR_REQ, 0) < 0) अणु
		अगर ((NCR5380_पढ़ो(STATUS_REG) & (SR_BSY | SR_SEL)) == 0)
			/* BUS FREE phase */
			वापस;
		shost_prपूर्णांकk(KERN_ERR, instance, "reselect: REQ timeout\n");
		करो_पात(instance, 0);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_SUN3
	/* acknowledge toggle to MSGIN */
	NCR5380_ग_लिखो(TARGET_COMMAND_REG, PHASE_SR_TO_TCR(PHASE_MSGIN));

	/* peek at the byte without really hitting the bus */
	msg[0] = NCR5380_पढ़ो(CURRENT_SCSI_DATA_REG);
#अन्यथा
	अणु
		पूर्णांक len = 1;
		अचिन्हित अक्षर *data = msg;
		अचिन्हित अक्षर phase = PHASE_MSGIN;

		NCR5380_transfer_pio(instance, &phase, &len, &data, 0);

		अगर (len) अणु
			करो_पात(instance, 0);
			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_SUN3 */

	अगर (!(msg[0] & 0x80)) अणु
		shost_prपूर्णांकk(KERN_ERR, instance, "expecting IDENTIFY message, got ");
		spi_prपूर्णांक_msg(msg);
		prपूर्णांकk("\n");
		करो_पात(instance, 0);
		वापस;
	पूर्ण
	lun = msg[0] & 0x07;

	/*
	 * We need to add code क्रम SCSI-II to track which devices have
	 * I_T_L_Q nexuses established, and which have simple I_T_L
	 * nexuses so we can chose to करो additional data transfer.
	 */

	/*
	 * Find the command corresponding to the I_T_L or I_T_L_Q  nexus we
	 * just reestablished, and हटाओ it from the disconnected queue.
	 */

	पंचांगp = शून्य;
	list_क्रम_each_entry(ncmd, &hostdata->disconnected, list) अणु
		काष्ठा scsi_cmnd *cmd = NCR5380_to_scmd(ncmd);

		अगर (target_mask == (1 << scmd_id(cmd)) &&
		    lun == (u8)cmd->device->lun) अणु
			list_del(&ncmd->list);
			पंचांगp = cmd;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (पंचांगp) अणु
		dsprपूर्णांकk(न_संशोधन_RESELECTION | न_संशोधन_QUEUES, instance,
		         "reselect: removed %p from disconnected queue\n", पंचांगp);
	पूर्ण अन्यथा अणु
		पूर्णांक target = ffs(target_mask) - 1;

		shost_prपूर्णांकk(KERN_ERR, instance, "target bitmask 0x%02x lun %d not in disconnected queue.\n",
		             target_mask, lun);
		/*
		 * Since we have an established nexus that we can't करो anything
		 * with, we must पात it.
		 */
		अगर (करो_पात(instance, 0) == 0)
			hostdata->busy[target] &= ~(1 << lun);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_SUN3
	अगर (sun3_dma_setup_करोne != पंचांगp) अणु
		पूर्णांक count;

		advance_sg_buffer(पंचांगp);

		count = sun3scsi_dma_xfer_len(hostdata, पंचांगp);

		अगर (count > 0) अणु
			अगर (rq_data_dir(पंचांगp->request))
				sun3scsi_dma_send_setup(hostdata,
				                        पंचांगp->SCp.ptr, count);
			अन्यथा
				sun3scsi_dma_recv_setup(hostdata,
				                        पंचांगp->SCp.ptr, count);
			sun3_dma_setup_करोne = पंचांगp;
		पूर्ण
	पूर्ण

	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ACK);
#पूर्ण_अगर /* CONFIG_SUN3 */

	/* Accept message by clearing ACK */
	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);

	hostdata->connected = पंचांगp;
	dsprपूर्णांकk(न_संशोधन_RESELECTION, instance, "nexus established, target %d, lun %llu\n",
	         scmd_id(पंचांगp), पंचांगp->device->lun);
पूर्ण

/**
 * list_find_cmd - test क्रम presence of a command in a linked list
 * @haystack: list of commands
 * @needle: command to search क्रम
 */

अटल bool list_find_cmd(काष्ठा list_head *haystack,
                          काष्ठा scsi_cmnd *needle)
अणु
	काष्ठा NCR5380_cmd *ncmd;

	list_क्रम_each_entry(ncmd, haystack, list)
		अगर (NCR5380_to_scmd(ncmd) == needle)
			वापस true;
	वापस false;
पूर्ण

/**
 * list_हटाओ_cmd - हटाओ a command from linked list
 * @haystack: list of commands
 * @needle: command to हटाओ
 */

अटल bool list_del_cmd(काष्ठा list_head *haystack,
                         काष्ठा scsi_cmnd *needle)
अणु
	अगर (list_find_cmd(haystack, needle)) अणु
		काष्ठा NCR5380_cmd *ncmd = scsi_cmd_priv(needle);

		list_del(&ncmd->list);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * NCR5380_पात - scsi host eh_पात_handler() method
 * @cmd: the command to be पातed
 *
 * Try to पात a given command by removing it from queues and/or sending
 * the target an पात message. This may not succeed in causing a target
 * to पात the command. Nonetheless, the low-level driver must क्रमget about
 * the command because the mid-layer reclaims it and it may be re-issued.
 *
 * The normal path taken by a command is as follows. For EH we trace this
 * same path to locate and पात the command.
 *
 * unissued -> selecting -> [unissued -> selecting ->]... connected ->
 * [disconnected -> connected ->]...
 * [स्वतःsense -> connected ->] करोne
 *
 * If cmd was not found at all then presumably it has alपढ़ोy been completed,
 * in which हाल वापस SUCCESS to try to aव्योम further EH measures.
 *
 * If the command has not completed yet, we must not fail to find it.
 * We have no option but to क्रमget the पातed command (even अगर it still
 * lacks sense data). The mid-layer may re-issue a command that is in error
 * recovery (see scsi_send_eh_cmnd), but the logic and data काष्ठाures in
 * this driver are such that a command can appear on one queue only.
 *
 * The lock protects driver data काष्ठाures, but EH handlers also use it
 * to serialize their own execution and prevent their own re-entry.
 */

अटल पूर्णांक NCR5380_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *instance = cmd->device->host;
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	अचिन्हित दीर्घ flags;
	पूर्णांक result = SUCCESS;

	spin_lock_irqsave(&hostdata->lock, flags);

#अगर (न_संशोधन & न_संशोधन_ANY)
	scmd_prपूर्णांकk(KERN_INFO, cmd, __func__);
#पूर्ण_अगर
	NCR5380_dprपूर्णांक(न_संशोधन_ANY, instance);
	NCR5380_dprपूर्णांक_phase(न_संशोधन_ANY, instance);

	अगर (list_del_cmd(&hostdata->unissued, cmd)) अणु
		dsprपूर्णांकk(न_संशोधन_ABORT, instance,
		         "abort: removed %p from issue queue\n", cmd);
		cmd->result = DID_ABORT << 16;
		cmd->scsi_करोne(cmd); /* No tag or busy flag to worry about */
		जाओ out;
	पूर्ण

	अगर (hostdata->selecting == cmd) अणु
		dsprपूर्णांकk(न_संशोधन_ABORT, instance,
		         "abort: cmd %p == selecting\n", cmd);
		hostdata->selecting = शून्य;
		cmd->result = DID_ABORT << 16;
		complete_cmd(instance, cmd);
		जाओ out;
	पूर्ण

	अगर (list_del_cmd(&hostdata->disconnected, cmd)) अणु
		dsprपूर्णांकk(न_संशोधन_ABORT, instance,
		         "abort: removed %p from disconnected list\n", cmd);
		/* Can't call NCR5380_select() and send ABORT because that
		 * means releasing the lock. Need a bus reset.
		 */
		set_host_byte(cmd, DID_ERROR);
		complete_cmd(instance, cmd);
		result = FAILED;
		जाओ out;
	पूर्ण

	अगर (hostdata->connected == cmd) अणु
		dsprपूर्णांकk(न_संशोधन_ABORT, instance, "abort: cmd %p is connected\n", cmd);
		hostdata->connected = शून्य;
		hostdata->dma_len = 0;
		अगर (करो_पात(instance, 0) < 0) अणु
			set_host_byte(cmd, DID_ERROR);
			complete_cmd(instance, cmd);
			result = FAILED;
			जाओ out;
		पूर्ण
		set_host_byte(cmd, DID_ABORT);
		complete_cmd(instance, cmd);
		जाओ out;
	पूर्ण

	अगर (list_del_cmd(&hostdata->स्वतःsense, cmd)) अणु
		dsprपूर्णांकk(न_संशोधन_ABORT, instance,
		         "abort: removed %p from sense queue\n", cmd);
		complete_cmd(instance, cmd);
	पूर्ण

out:
	अगर (result == FAILED)
		dsprपूर्णांकk(न_संशोधन_ABORT, instance, "abort: failed to abort %p\n", cmd);
	अन्यथा अणु
		hostdata->busy[scmd_id(cmd)] &= ~(1 << cmd->device->lun);
		dsprपूर्णांकk(न_संशोधन_ABORT, instance, "abort: successfully aborted %p\n", cmd);
	पूर्ण

	queue_work(hostdata->work_q, &hostdata->मुख्य_task);
	spin_unlock_irqrestore(&hostdata->lock, flags);

	वापस result;
पूर्ण


अटल व्योम bus_reset_cleanup(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	पूर्णांक i;
	काष्ठा NCR5380_cmd *ncmd;

	/* reset NCR रेजिस्टरs */
	NCR5380_ग_लिखो(MODE_REG, MR_BASE);
	NCR5380_ग_लिखो(TARGET_COMMAND_REG, 0);
	NCR5380_ग_लिखो(SELECT_ENABLE_REG, 0);

	/* After the reset, there are no more connected or disconnected commands
	 * and no busy units; so clear the low-level status here to aव्योम
	 * conflicts when the mid-level code tries to wake up the affected
	 * commands!
	 */

	अगर (hostdata->selecting) अणु
		hostdata->selecting->result = DID_RESET << 16;
		complete_cmd(instance, hostdata->selecting);
		hostdata->selecting = शून्य;
	पूर्ण

	list_क्रम_each_entry(ncmd, &hostdata->disconnected, list) अणु
		काष्ठा scsi_cmnd *cmd = NCR5380_to_scmd(ncmd);

		set_host_byte(cmd, DID_RESET);
		complete_cmd(instance, cmd);
	पूर्ण
	INIT_LIST_HEAD(&hostdata->disconnected);

	list_क्रम_each_entry(ncmd, &hostdata->स्वतःsense, list) अणु
		काष्ठा scsi_cmnd *cmd = NCR5380_to_scmd(ncmd);

		cmd->scsi_करोne(cmd);
	पूर्ण
	INIT_LIST_HEAD(&hostdata->स्वतःsense);

	अगर (hostdata->connected) अणु
		set_host_byte(hostdata->connected, DID_RESET);
		complete_cmd(instance, hostdata->connected);
		hostdata->connected = शून्य;
	पूर्ण

	क्रम (i = 0; i < 8; ++i)
		hostdata->busy[i] = 0;
	hostdata->dma_len = 0;

	queue_work(hostdata->work_q, &hostdata->मुख्य_task);
पूर्ण

/**
 * NCR5380_host_reset - reset the SCSI host
 * @cmd: SCSI command undergoing EH
 *
 * Returns SUCCESS
 */

अटल पूर्णांक NCR5380_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *instance = cmd->device->host;
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	अचिन्हित दीर्घ flags;
	काष्ठा NCR5380_cmd *ncmd;

	spin_lock_irqsave(&hostdata->lock, flags);

#अगर (न_संशोधन & न_संशोधन_ANY)
	shost_prपूर्णांकk(KERN_INFO, instance, __func__);
#पूर्ण_अगर
	NCR5380_dprपूर्णांक(न_संशोधन_ANY, instance);
	NCR5380_dprपूर्णांक_phase(न_संशोधन_ANY, instance);

	list_क्रम_each_entry(ncmd, &hostdata->unissued, list) अणु
		काष्ठा scsi_cmnd *scmd = NCR5380_to_scmd(ncmd);

		scmd->result = DID_RESET << 16;
		scmd->scsi_करोne(scmd);
	पूर्ण
	INIT_LIST_HEAD(&hostdata->unissued);

	करो_reset(instance);
	bus_reset_cleanup(instance);

	spin_unlock_irqrestore(&hostdata->lock, flags);

	वापस SUCCESS;
पूर्ण
