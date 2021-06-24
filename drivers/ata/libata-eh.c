<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  libata-eh.c - libata error handling
 *
 *  Copyright 2006 Tejun Heo <htejun@gmail.com>
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 *
 *  Hardware करोcumentation available from http://www.t13.org/ and
 *  http://www.sata-io.org/
 */

#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश "../scsi/scsi_transport_api.h"

#समावेश <linux/libata.h>

#समावेश <trace/events/libata.h>
#समावेश "libata.h"

क्रमागत अणु
	/* speed करोwn verdicts */
	ATA_EH_SPDN_NCQ_OFF		= (1 << 0),
	ATA_EH_SPDN_SPEED_DOWN		= (1 << 1),
	ATA_EH_SPDN_FALLBACK_TO_PIO	= (1 << 2),
	ATA_EH_SPDN_KEEP_ERRORS		= (1 << 3),

	/* error flags */
	ATA_EFLAG_IS_IO			= (1 << 0),
	ATA_EFLAG_DUBIOUS_XFER		= (1 << 1),
	ATA_EFLAG_OLD_ER                = (1 << 31),

	/* error categories */
	ATA_ECAT_NONE			= 0,
	ATA_ECAT_ATA_BUS		= 1,
	ATA_ECAT_TOUT_HSM		= 2,
	ATA_ECAT_UNK_DEV		= 3,
	ATA_ECAT_DUBIOUS_NONE		= 4,
	ATA_ECAT_DUBIOUS_ATA_BUS	= 5,
	ATA_ECAT_DUBIOUS_TOUT_HSM	= 6,
	ATA_ECAT_DUBIOUS_UNK_DEV	= 7,
	ATA_ECAT_NR			= 8,

	ATA_EH_CMD_DFL_TIMEOUT		=  5000,

	/* always put at least this amount of समय between resets */
	ATA_EH_RESET_COOL_DOWN		=  5000,

	/* Waiting in ->prereset can never be reliable.  It's
	 * someबार nice to रुको there but it can't be depended upon;
	 * otherwise, we wouldn't be resetting.  Just give it enough
	 * समय क्रम most drives to spin up.
	 */
	ATA_EH_PRERESET_TIMEOUT		= 10000,
	ATA_EH_FASTDRAIN_INTERVAL	=  3000,

	ATA_EH_UA_TRIES			= 5,

	/* probe speed करोwn parameters, see ata_eh_schedule_probe() */
	ATA_EH_PROBE_TRIAL_INTERVAL	= 60000,	/* 1 min */
	ATA_EH_PROBE_TRIALS		= 2,
पूर्ण;

/* The following table determines how we sequence resets.  Each entry
 * represents समयout क्रम that try.  The first try can be soft or
 * hardreset.  All others are hardreset अगर available.  In most हालs
 * the first reset w/ 10sec समयout should succeed.  Following entries
 * are mostly क्रम error handling, hotplug and those outlier devices that
 * take an exceptionally दीर्घ समय to recover from reset.
 */
अटल स्थिर अचिन्हित दीर्घ ata_eh_reset_समयouts[] = अणु
	10000,	/* most drives spin up by 10sec */
	10000,	/* > 99% working drives spin up beक्रमe 20sec */
	35000,	/* give > 30 secs of idleness क्रम outlier devices */
	 5000,	/* and sweet one last chance */
	अच_दीर्घ_उच्च, /* > 1 min has elapsed, give up */
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ ata_eh_identअगरy_समयouts[] = अणु
	 5000,	/* covers > 99% of successes and not too boring on failures */
	10000,  /* combined समय till here is enough even क्रम media access */
	30000,	/* क्रम true idiots */
	अच_दीर्घ_उच्च,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ ata_eh_flush_समयouts[] = अणु
	15000,	/* be generous with flush */
	15000,  /* ditto */
	30000,	/* and even more generous */
	अच_दीर्घ_उच्च,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ ata_eh_other_समयouts[] = अणु
	 5000,	/* same rationale as identअगरy समयout */
	10000,	/* ditto */
	/* but no mercअगरul 30sec क्रम other commands, it just isn't worth it */
	अच_दीर्घ_उच्च,
पूर्ण;

काष्ठा ata_eh_cmd_समयout_ent अणु
	स्थिर u8		*commands;
	स्थिर अचिन्हित दीर्घ	*समयouts;
पूर्ण;

/* The following table determines समयouts to use क्रम EH पूर्णांकernal
 * commands.  Each table entry is a command class and matches the
 * commands the entry applies to and the समयout table to use.
 *
 * On the retry after a command समयd out, the next समयout value from
 * the table is used.  If the table करोesn't contain further entries,
 * the last value is used.
 *
 * ehc->cmd_समयout_idx keeps track of which समयout to use per
 * command class, so अगर SET_FEATURES बार out on the first try, the
 * next try will use the second समयout value only क्रम that class.
 */
#घोषणा CMDS(cmds...)	(स्थिर u8 [])अणु cmds, 0 पूर्ण
अटल स्थिर काष्ठा ata_eh_cmd_समयout_ent
ata_eh_cmd_समयout_table[ATA_EH_CMD_TIMEOUT_TABLE_SIZE] = अणु
	अणु .commands = CMDS(ATA_CMD_ID_ATA, ATA_CMD_ID_ATAPI),
	  .समयouts = ata_eh_identअगरy_समयouts, पूर्ण,
	अणु .commands = CMDS(ATA_CMD_READ_NATIVE_MAX, ATA_CMD_READ_NATIVE_MAX_EXT),
	  .समयouts = ata_eh_other_समयouts, पूर्ण,
	अणु .commands = CMDS(ATA_CMD_SET_MAX, ATA_CMD_SET_MAX_EXT),
	  .समयouts = ata_eh_other_समयouts, पूर्ण,
	अणु .commands = CMDS(ATA_CMD_SET_FEATURES),
	  .समयouts = ata_eh_other_समयouts, पूर्ण,
	अणु .commands = CMDS(ATA_CMD_INIT_DEV_PARAMS),
	  .समयouts = ata_eh_other_समयouts, पूर्ण,
	अणु .commands = CMDS(ATA_CMD_FLUSH, ATA_CMD_FLUSH_EXT),
	  .समयouts = ata_eh_flush_समयouts पूर्ण,
पूर्ण;
#अघोषित CMDS

अटल व्योम __ata_port_मुक्तze(काष्ठा ata_port *ap);
#अगर_घोषित CONFIG_PM
अटल व्योम ata_eh_handle_port_suspend(काष्ठा ata_port *ap);
अटल व्योम ata_eh_handle_port_resume(काष्ठा ata_port *ap);
#अन्यथा /* CONFIG_PM */
अटल व्योम ata_eh_handle_port_suspend(काष्ठा ata_port *ap)
अणु पूर्ण

अटल व्योम ata_eh_handle_port_resume(काष्ठा ata_port *ap)
अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल __म_लिखो(2, 0) व्योम __ata_ehi_pushv_desc(काष्ठा ata_eh_info *ehi,
				 स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	ehi->desc_len += vscnम_लिखो(ehi->desc + ehi->desc_len,
				     ATA_EH_DESC_LEN - ehi->desc_len,
				     fmt, args);
पूर्ण

/**
 *	__ata_ehi_push_desc - push error description without adding separator
 *	@ehi: target EHI
 *	@fmt: म_लिखो क्रमmat string
 *
 *	Format string according to @fmt and append it to @ehi->desc.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम __ata_ehi_push_desc(काष्ठा ata_eh_info *ehi, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	__ata_ehi_pushv_desc(ehi, fmt, args);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(__ata_ehi_push_desc);

/**
 *	ata_ehi_push_desc - push error description with separator
 *	@ehi: target EHI
 *	@fmt: म_लिखो क्रमmat string
 *
 *	Format string according to @fmt and append it to @ehi->desc.
 *	If @ehi->desc is not empty, ", " is added in-between.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_ehi_push_desc(काष्ठा ata_eh_info *ehi, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	अगर (ehi->desc_len)
		__ata_ehi_push_desc(ehi, ", ");

	बहु_शुरू(args, fmt);
	__ata_ehi_pushv_desc(ehi, fmt, args);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(ata_ehi_push_desc);

/**
 *	ata_ehi_clear_desc - clean error description
 *	@ehi: target EHI
 *
 *	Clear @ehi->desc.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_ehi_clear_desc(काष्ठा ata_eh_info *ehi)
अणु
	ehi->desc[0] = '\0';
	ehi->desc_len = 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_ehi_clear_desc);

/**
 *	ata_port_desc - append port description
 *	@ap: target ATA port
 *	@fmt: म_लिखो क्रमmat string
 *
 *	Format string according to @fmt and append it to port
 *	description.  If port description is not empty, " " is added
 *	in-between.  This function is to be used जबतक initializing
 *	ata_host.  The description is prपूर्णांकed on host registration.
 *
 *	LOCKING:
 *	None.
 */
व्योम ata_port_desc(काष्ठा ata_port *ap, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	WARN_ON(!(ap->pflags & ATA_PFLAG_INITIALIZING));

	अगर (ap->link.eh_info.desc_len)
		__ata_ehi_push_desc(&ap->link.eh_info, " ");

	बहु_शुरू(args, fmt);
	__ata_ehi_pushv_desc(&ap->link.eh_info, fmt, args);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(ata_port_desc);

#अगर_घोषित CONFIG_PCI
/**
 *	ata_port_pbar_desc - append PCI BAR description
 *	@ap: target ATA port
 *	@bar: target PCI BAR
 *	@offset: offset पूर्णांकo PCI BAR
 *	@name: name of the area
 *
 *	If @offset is negative, this function क्रमmats a string which
 *	contains the name, address, size and type of the BAR and
 *	appends it to the port description.  If @offset is zero or
 *	positive, only name and offsetted address is appended.
 *
 *	LOCKING:
 *	None.
 */
व्योम ata_port_pbar_desc(काष्ठा ata_port *ap, पूर्णांक bar, sमाप_प्रकार offset,
			स्थिर अक्षर *name)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अक्षर *type = "";
	अचिन्हित दीर्घ दीर्घ start, len;

	अगर (pci_resource_flags(pdev, bar) & IORESOURCE_MEM)
		type = "m";
	अन्यथा अगर (pci_resource_flags(pdev, bar) & IORESOURCE_IO)
		type = "i";

	start = (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, bar);
	len = (अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, bar);

	अगर (offset < 0)
		ata_port_desc(ap, "%s %s%llu@0x%llx", name, type, len, start);
	अन्यथा
		ata_port_desc(ap, "%s 0x%llx", name,
				start + (अचिन्हित दीर्घ दीर्घ)offset);
पूर्ण
EXPORT_SYMBOL_GPL(ata_port_pbar_desc);
#पूर्ण_अगर /* CONFIG_PCI */

अटल पूर्णांक ata_lookup_समयout_table(u8 cmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ATA_EH_CMD_TIMEOUT_TABLE_SIZE; i++) अणु
		स्थिर u8 *cur;

		क्रम (cur = ata_eh_cmd_समयout_table[i].commands; *cur; cur++)
			अगर (*cur == cmd)
				वापस i;
	पूर्ण

	वापस -1;
पूर्ण

/**
 *	ata_पूर्णांकernal_cmd_समयout - determine समयout क्रम an पूर्णांकernal command
 *	@dev: target device
 *	@cmd: पूर्णांकernal command to be issued
 *
 *	Determine समयout क्रम पूर्णांकernal command @cmd क्रम @dev.
 *
 *	LOCKING:
 *	EH context.
 *
 *	RETURNS:
 *	Determined समयout.
 */
अचिन्हित दीर्घ ata_पूर्णांकernal_cmd_समयout(काष्ठा ata_device *dev, u8 cmd)
अणु
	काष्ठा ata_eh_context *ehc = &dev->link->eh_context;
	पूर्णांक ent = ata_lookup_समयout_table(cmd);
	पूर्णांक idx;

	अगर (ent < 0)
		वापस ATA_EH_CMD_DFL_TIMEOUT;

	idx = ehc->cmd_समयout_idx[dev->devno][ent];
	वापस ata_eh_cmd_समयout_table[ent].समयouts[idx];
पूर्ण

/**
 *	ata_पूर्णांकernal_cmd_समयd_out - notअगरication क्रम पूर्णांकernal command समयout
 *	@dev: target device
 *	@cmd: पूर्णांकernal command which समयd out
 *
 *	Notअगरy EH that पूर्णांकernal command @cmd क्रम @dev समयd out.  This
 *	function should be called only क्रम commands whose समयouts are
 *	determined using ata_पूर्णांकernal_cmd_समयout().
 *
 *	LOCKING:
 *	EH context.
 */
व्योम ata_पूर्णांकernal_cmd_समयd_out(काष्ठा ata_device *dev, u8 cmd)
अणु
	काष्ठा ata_eh_context *ehc = &dev->link->eh_context;
	पूर्णांक ent = ata_lookup_समयout_table(cmd);
	पूर्णांक idx;

	अगर (ent < 0)
		वापस;

	idx = ehc->cmd_समयout_idx[dev->devno][ent];
	अगर (ata_eh_cmd_समयout_table[ent].समयouts[idx + 1] != अच_दीर्घ_उच्च)
		ehc->cmd_समयout_idx[dev->devno][ent]++;
पूर्ण

अटल व्योम ata_ering_record(काष्ठा ata_ering *ering, अचिन्हित पूर्णांक eflags,
			     अचिन्हित पूर्णांक err_mask)
अणु
	काष्ठा ata_ering_entry *ent;

	WARN_ON(!err_mask);

	ering->cursor++;
	ering->cursor %= ATA_ERING_SIZE;

	ent = &ering->ring[ering->cursor];
	ent->eflags = eflags;
	ent->err_mask = err_mask;
	ent->बारtamp = get_jअगरfies_64();
पूर्ण

अटल काष्ठा ata_ering_entry *ata_ering_top(काष्ठा ata_ering *ering)
अणु
	काष्ठा ata_ering_entry *ent = &ering->ring[ering->cursor];

	अगर (ent->err_mask)
		वापस ent;
	वापस शून्य;
पूर्ण

पूर्णांक ata_ering_map(काष्ठा ata_ering *ering,
		  पूर्णांक (*map_fn)(काष्ठा ata_ering_entry *, व्योम *),
		  व्योम *arg)
अणु
	पूर्णांक idx, rc = 0;
	काष्ठा ata_ering_entry *ent;

	idx = ering->cursor;
	करो अणु
		ent = &ering->ring[idx];
		अगर (!ent->err_mask)
			अवरोध;
		rc = map_fn(ent, arg);
		अगर (rc)
			अवरोध;
		idx = (idx - 1 + ATA_ERING_SIZE) % ATA_ERING_SIZE;
	पूर्ण जबतक (idx != ering->cursor);

	वापस rc;
पूर्ण

अटल पूर्णांक ata_ering_clear_cb(काष्ठा ata_ering_entry *ent, व्योम *व्योम_arg)
अणु
	ent->eflags |= ATA_EFLAG_OLD_ER;
	वापस 0;
पूर्ण

अटल व्योम ata_ering_clear(काष्ठा ata_ering *ering)
अणु
	ata_ering_map(ering, ata_ering_clear_cb, शून्य);
पूर्ण

अटल अचिन्हित पूर्णांक ata_eh_dev_action(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_eh_context *ehc = &dev->link->eh_context;

	वापस ehc->i.action | ehc->i.dev_action[dev->devno];
पूर्ण

अटल व्योम ata_eh_clear_action(काष्ठा ata_link *link, काष्ठा ata_device *dev,
				काष्ठा ata_eh_info *ehi, अचिन्हित पूर्णांक action)
अणु
	काष्ठा ata_device *tdev;

	अगर (!dev) अणु
		ehi->action &= ~action;
		ata_क्रम_each_dev(tdev, link, ALL)
			ehi->dev_action[tdev->devno] &= ~action;
	पूर्ण अन्यथा अणु
		/* करोesn't make sense क्रम port-wide EH actions */
		WARN_ON(!(action & ATA_EH_PERDEV_MASK));

		/* अवरोध ehi->action पूर्णांकo ehi->dev_action */
		अगर (ehi->action & action) अणु
			ata_क्रम_each_dev(tdev, link, ALL)
				ehi->dev_action[tdev->devno] |=
					ehi->action & action;
			ehi->action &= ~action;
		पूर्ण

		/* turn off the specअगरied per-dev action */
		ehi->dev_action[dev->devno] &= ~action;
	पूर्ण
पूर्ण

/**
 *	ata_eh_acquire - acquire EH ownership
 *	@ap: ATA port to acquire EH ownership क्रम
 *
 *	Acquire EH ownership क्रम @ap.  This is the basic exclusion
 *	mechanism क्रम ports sharing a host.  Only one port hanging off
 *	the same host can claim the ownership of EH.
 *
 *	LOCKING:
 *	EH context.
 */
व्योम ata_eh_acquire(काष्ठा ata_port *ap)
अणु
	mutex_lock(&ap->host->eh_mutex);
	WARN_ON_ONCE(ap->host->eh_owner);
	ap->host->eh_owner = current;
पूर्ण

/**
 *	ata_eh_release - release EH ownership
 *	@ap: ATA port to release EH ownership क्रम
 *
 *	Release EH ownership क्रम @ap अगर the caller.  The caller must
 *	have acquired EH ownership using ata_eh_acquire() previously.
 *
 *	LOCKING:
 *	EH context.
 */
व्योम ata_eh_release(काष्ठा ata_port *ap)
अणु
	WARN_ON_ONCE(ap->host->eh_owner != current);
	ap->host->eh_owner = शून्य;
	mutex_unlock(&ap->host->eh_mutex);
पूर्ण

अटल व्योम ata_eh_unload(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_link *link;
	काष्ठा ata_device *dev;
	अचिन्हित दीर्घ flags;

	/* Restore SControl IPM and SPD क्रम the next driver and
	 * disable attached devices.
	 */
	ata_क्रम_each_link(link, ap, PMP_FIRST) अणु
		sata_scr_ग_लिखो(link, SCR_CONTROL, link->saved_scontrol & 0xff0);
		ata_क्रम_each_dev(dev, link, ALL)
			ata_dev_disable(dev);
	पूर्ण

	/* मुक्तze and set UNLOADED */
	spin_lock_irqsave(ap->lock, flags);

	ata_port_मुक्तze(ap);			/* won't be thawed */
	ap->pflags &= ~ATA_PFLAG_EH_PENDING;	/* clear pending from मुक्तze */
	ap->pflags |= ATA_PFLAG_UNLOADED;

	spin_unlock_irqrestore(ap->lock, flags);
पूर्ण

/**
 *	ata_scsi_error - SCSI layer error handler callback
 *	@host: SCSI host on which error occurred
 *
 *	Handles SCSI-layer-thrown error events.
 *
 *	LOCKING:
 *	Inherited from SCSI layer (none, can sleep)
 *
 *	RETURNS:
 *	Zero.
 */
व्योम ata_scsi_error(काष्ठा Scsi_Host *host)
अणु
	काष्ठा ata_port *ap = ata_shost_to_port(host);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(eh_work_q);

	DPRINTK("ENTER\n");

	spin_lock_irqsave(host->host_lock, flags);
	list_splice_init(&host->eh_cmd_q, &eh_work_q);
	spin_unlock_irqrestore(host->host_lock, flags);

	ata_scsi_cmd_error_handler(host, ap, &eh_work_q);

	/* If we समयd raced normal completion and there is nothing to
	   recover nr_समयकरोut == 0 why exactly are we करोing error recovery ? */
	ata_scsi_port_error_handler(host, ap);

	/* finish or retry handled scmd's and clean up */
	WARN_ON(!list_empty(&eh_work_q));

	DPRINTK("EXIT\n");
पूर्ण

/**
 * ata_scsi_cmd_error_handler - error callback क्रम a list of commands
 * @host:	scsi host containing the port
 * @ap:		ATA port within the host
 * @eh_work_q:	list of commands to process
 *
 * process the given list of commands and वापस those finished to the
 * ap->eh_करोne_q.  This function is the first part of the libata error
 * handler which processes a given list of failed commands.
 */
व्योम ata_scsi_cmd_error_handler(काष्ठा Scsi_Host *host, काष्ठा ata_port *ap,
				काष्ठा list_head *eh_work_q)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	/* make sure sff pio task is not running */
	ata_sff_flush_pio_task(ap);

	/* synchronize with host lock and sort out समयouts */

	/* For new EH, all qcs are finished in one of three ways -
	 * normal completion, error completion, and SCSI समयout.
	 * Both completions can race against SCSI समयout.  When normal
	 * completion wins, the qc never reaches EH.  When error
	 * completion wins, the qc has ATA_QCFLAG_FAILED set.
	 *
	 * When SCSI समयout wins, things are a bit more complex.
	 * Normal or error completion can occur after the समयout but
	 * beक्रमe this poपूर्णांक.  In such हालs, both types of
	 * completions are honored.  A scmd is determined to have
	 * समयd out अगरf its associated qc is active and not failed.
	 */
	spin_lock_irqsave(ap->lock, flags);
	अगर (ap->ops->error_handler) अणु
		काष्ठा scsi_cmnd *scmd, *पंचांगp;
		पूर्णांक nr_समयकरोut = 0;

		/* This must occur under the ap->lock as we करोn't want
		   a polled recovery to race the real पूर्णांकerrupt handler

		   The lost_पूर्णांकerrupt handler checks क्रम any completed but
		   non-notअगरied command and completes much like an IRQ handler.

		   We then fall पूर्णांकo the error recovery code which will treat
		   this as अगर normal completion won the race */

		अगर (ap->ops->lost_पूर्णांकerrupt)
			ap->ops->lost_पूर्णांकerrupt(ap);

		list_क्रम_each_entry_safe(scmd, पंचांगp, eh_work_q, eh_entry) अणु
			काष्ठा ata_queued_cmd *qc;

			ata_qc_क्रम_each_raw(ap, qc, i) अणु
				अगर (qc->flags & ATA_QCFLAG_ACTIVE &&
				    qc->scsicmd == scmd)
					अवरोध;
			पूर्ण

			अगर (i < ATA_MAX_QUEUE) अणु
				/* the scmd has an associated qc */
				अगर (!(qc->flags & ATA_QCFLAG_FAILED)) अणु
					/* which hasn't failed yet, समयout */
					qc->err_mask |= AC_ERR_TIMEOUT;
					qc->flags |= ATA_QCFLAG_FAILED;
					nr_समयकरोut++;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Normal completion occurred after
				 * SCSI समयout but beक्रमe this poपूर्णांक.
				 * Successfully complete it.
				 */
				scmd->retries = scmd->allowed;
				scsi_eh_finish_cmd(scmd, &ap->eh_करोne_q);
			पूर्ण
		पूर्ण

		/* If we have समयd out qcs.  They beदीर्घ to EH from
		 * this poपूर्णांक but the state of the controller is
		 * unknown.  Freeze the port to make sure the IRQ
		 * handler करोesn't diddle with those qcs.  This must
		 * be करोne atomically w.r.t. setting QCFLAG_FAILED.
		 */
		अगर (nr_समयकरोut)
			__ata_port_मुक्तze(ap);


		/* initialize eh_tries */
		ap->eh_tries = ATA_EH_MAX_TRIES;
	पूर्ण
	spin_unlock_irqrestore(ap->lock, flags);

पूर्ण
EXPORT_SYMBOL(ata_scsi_cmd_error_handler);

/**
 * ata_scsi_port_error_handler - recover the port after the commands
 * @host:	SCSI host containing the port
 * @ap:		the ATA port
 *
 * Handle the recovery of the port @ap after all the commands
 * have been recovered.
 */
व्योम ata_scsi_port_error_handler(काष्ठा Scsi_Host *host, काष्ठा ata_port *ap)
अणु
	अचिन्हित दीर्घ flags;

	/* invoke error handler */
	अगर (ap->ops->error_handler) अणु
		काष्ठा ata_link *link;

		/* acquire EH ownership */
		ata_eh_acquire(ap);
 repeat:
		/* समाप्त fast drain समयr */
		del_समयr_sync(&ap->fastdrain_समयr);

		/* process port resume request */
		ata_eh_handle_port_resume(ap);

		/* fetch & clear EH info */
		spin_lock_irqsave(ap->lock, flags);

		ata_क्रम_each_link(link, ap, HOST_FIRST) अणु
			काष्ठा ata_eh_context *ehc = &link->eh_context;
			काष्ठा ata_device *dev;

			स_रखो(&link->eh_context, 0, माप(link->eh_context));
			link->eh_context.i = link->eh_info;
			स_रखो(&link->eh_info, 0, माप(link->eh_info));

			ata_क्रम_each_dev(dev, link, ENABLED) अणु
				पूर्णांक devno = dev->devno;

				ehc->saved_xfer_mode[devno] = dev->xfer_mode;
				अगर (ata_ncq_enabled(dev))
					ehc->saved_ncq_enabled |= 1 << devno;
			पूर्ण
		पूर्ण

		ap->pflags |= ATA_PFLAG_EH_IN_PROGRESS;
		ap->pflags &= ~ATA_PFLAG_EH_PENDING;
		ap->excl_link = शून्य;	/* करोn't मुख्यtain exclusion over EH */

		spin_unlock_irqrestore(ap->lock, flags);

		/* invoke EH, skip अगर unloading or suspended */
		अगर (!(ap->pflags & (ATA_PFLAG_UNLOADING | ATA_PFLAG_SUSPENDED)))
			ap->ops->error_handler(ap);
		अन्यथा अणु
			/* अगर unloading, commence suicide */
			अगर ((ap->pflags & ATA_PFLAG_UNLOADING) &&
			    !(ap->pflags & ATA_PFLAG_UNLOADED))
				ata_eh_unload(ap);
			ata_eh_finish(ap);
		पूर्ण

		/* process port suspend request */
		ata_eh_handle_port_suspend(ap);

		/* Exception might have happened after ->error_handler
		 * recovered the port but beक्रमe this poपूर्णांक.  Repeat
		 * EH in such हाल.
		 */
		spin_lock_irqsave(ap->lock, flags);

		अगर (ap->pflags & ATA_PFLAG_EH_PENDING) अणु
			अगर (--ap->eh_tries) अणु
				spin_unlock_irqrestore(ap->lock, flags);
				जाओ repeat;
			पूर्ण
			ata_port_err(ap,
				     "EH pending after %d tries, giving up\n",
				     ATA_EH_MAX_TRIES);
			ap->pflags &= ~ATA_PFLAG_EH_PENDING;
		पूर्ण

		/* this run is complete, make sure EH info is clear */
		ata_क्रम_each_link(link, ap, HOST_FIRST)
			स_रखो(&link->eh_info, 0, माप(link->eh_info));

		/* end eh (clear host_eh_scheduled) जबतक holding
		 * ap->lock such that अगर exception occurs after this
		 * poपूर्णांक but beक्रमe EH completion, SCSI midlayer will
		 * re-initiate EH.
		 */
		ap->ops->end_eh(ap);

		spin_unlock_irqrestore(ap->lock, flags);
		ata_eh_release(ap);
	पूर्ण अन्यथा अणु
		WARN_ON(ata_qc_from_tag(ap, ap->link.active_tag) == शून्य);
		ap->ops->eng_समयout(ap);
	पूर्ण

	scsi_eh_flush_करोne_q(&ap->eh_करोne_q);

	/* clean up */
	spin_lock_irqsave(ap->lock, flags);

	अगर (ap->pflags & ATA_PFLAG_LOADING)
		ap->pflags &= ~ATA_PFLAG_LOADING;
	अन्यथा अगर ((ap->pflags & ATA_PFLAG_SCSI_HOTPLUG) &&
		!(ap->flags & ATA_FLAG_SAS_HOST))
		schedule_delayed_work(&ap->hotplug_task, 0);

	अगर (ap->pflags & ATA_PFLAG_RECOVERED)
		ata_port_info(ap, "EH complete\n");

	ap->pflags &= ~(ATA_PFLAG_SCSI_HOTPLUG | ATA_PFLAG_RECOVERED);

	/* tell रुको_eh that we're करोne */
	ap->pflags &= ~ATA_PFLAG_EH_IN_PROGRESS;
	wake_up_all(&ap->eh_रुको_q);

	spin_unlock_irqrestore(ap->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ata_scsi_port_error_handler);

/**
 *	ata_port_रुको_eh - Wait क्रम the currently pending EH to complete
 *	@ap: Port to रुको EH क्रम
 *
 *	Wait until the currently pending EH is complete.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
व्योम ata_port_रुको_eh(काष्ठा ata_port *ap)
अणु
	अचिन्हित दीर्घ flags;
	DEFINE_WAIT(रुको);

 retry:
	spin_lock_irqsave(ap->lock, flags);

	जबतक (ap->pflags & (ATA_PFLAG_EH_PENDING | ATA_PFLAG_EH_IN_PROGRESS)) अणु
		prepare_to_रुको(&ap->eh_रुको_q, &रुको, TASK_UNINTERRUPTIBLE);
		spin_unlock_irqrestore(ap->lock, flags);
		schedule();
		spin_lock_irqsave(ap->lock, flags);
	पूर्ण
	finish_रुको(&ap->eh_रुको_q, &रुको);

	spin_unlock_irqrestore(ap->lock, flags);

	/* make sure SCSI EH is complete */
	अगर (scsi_host_in_recovery(ap->scsi_host)) अणु
		ata_msleep(ap, 10);
		जाओ retry;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ata_port_रुको_eh);

अटल पूर्णांक ata_eh_nr_in_flight(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_queued_cmd *qc;
	अचिन्हित पूर्णांक tag;
	पूर्णांक nr = 0;

	/* count only non-पूर्णांकernal commands */
	ata_qc_क्रम_each(ap, qc, tag) अणु
		अगर (qc)
			nr++;
	पूर्ण

	वापस nr;
पूर्ण

व्योम ata_eh_fastdrain_समयrfn(काष्ठा समयr_list *t)
अणु
	काष्ठा ata_port *ap = from_समयr(ap, t, fastdrain_समयr);
	अचिन्हित दीर्घ flags;
	पूर्णांक cnt;

	spin_lock_irqsave(ap->lock, flags);

	cnt = ata_eh_nr_in_flight(ap);

	/* are we करोne? */
	अगर (!cnt)
		जाओ out_unlock;

	अगर (cnt == ap->fastdrain_cnt) अणु
		काष्ठा ata_queued_cmd *qc;
		अचिन्हित पूर्णांक tag;

		/* No progress during the last पूर्णांकerval, tag all
		 * in-flight qcs as समयd out and मुक्तze the port.
		 */
		ata_qc_क्रम_each(ap, qc, tag) अणु
			अगर (qc)
				qc->err_mask |= AC_ERR_TIMEOUT;
		पूर्ण

		ata_port_मुक्तze(ap);
	पूर्ण अन्यथा अणु
		/* some qcs have finished, give it another chance */
		ap->fastdrain_cnt = cnt;
		ap->fastdrain_समयr.expires =
			ata_deadline(jअगरfies, ATA_EH_FASTDRAIN_INTERVAL);
		add_समयr(&ap->fastdrain_समयr);
	पूर्ण

 out_unlock:
	spin_unlock_irqrestore(ap->lock, flags);
पूर्ण

/**
 *	ata_eh_set_pending - set ATA_PFLAG_EH_PENDING and activate fast drain
 *	@ap: target ATA port
 *	@fastdrain: activate fast drain
 *
 *	Set ATA_PFLAG_EH_PENDING and activate fast drain अगर @fastdrain
 *	is non-zero and EH wasn't pending beक्रमe.  Fast drain ensures
 *	that EH kicks in in समयly manner.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल व्योम ata_eh_set_pending(काष्ठा ata_port *ap, पूर्णांक fastdrain)
अणु
	पूर्णांक cnt;

	/* alपढ़ोy scheduled? */
	अगर (ap->pflags & ATA_PFLAG_EH_PENDING)
		वापस;

	ap->pflags |= ATA_PFLAG_EH_PENDING;

	अगर (!fastdrain)
		वापस;

	/* करो we have in-flight qcs? */
	cnt = ata_eh_nr_in_flight(ap);
	अगर (!cnt)
		वापस;

	/* activate fast drain */
	ap->fastdrain_cnt = cnt;
	ap->fastdrain_समयr.expires =
		ata_deadline(jअगरfies, ATA_EH_FASTDRAIN_INTERVAL);
	add_समयr(&ap->fastdrain_समयr);
पूर्ण

/**
 *	ata_qc_schedule_eh - schedule qc क्रम error handling
 *	@qc: command to schedule error handling क्रम
 *
 *	Schedule error handling क्रम @qc.  EH will kick in as soon as
 *	other commands are drained.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_qc_schedule_eh(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;

	WARN_ON(!ap->ops->error_handler);

	qc->flags |= ATA_QCFLAG_FAILED;
	ata_eh_set_pending(ap, 1);

	/* The following will fail अगर समयout has alपढ़ोy expired.
	 * ata_scsi_error() takes care of such scmds on EH entry.
	 * Note that ATA_QCFLAG_FAILED is unconditionally set after
	 * this function completes.
	 */
	blk_पात_request(qc->scsicmd->request);
पूर्ण

/**
 * ata_std_sched_eh - non-libsas ata_ports issue eh with this common routine
 * @ap: ATA port to schedule EH क्रम
 *
 *	LOCKING: inherited from ata_port_schedule_eh
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_std_sched_eh(काष्ठा ata_port *ap)
अणु
	WARN_ON(!ap->ops->error_handler);

	अगर (ap->pflags & ATA_PFLAG_INITIALIZING)
		वापस;

	ata_eh_set_pending(ap, 1);
	scsi_schedule_eh(ap->scsi_host);

	DPRINTK("port EH scheduled\n");
पूर्ण
EXPORT_SYMBOL_GPL(ata_std_sched_eh);

/**
 * ata_std_end_eh - non-libsas ata_ports complete eh with this common routine
 * @ap: ATA port to end EH क्रम
 *
 * In the libata object model there is a 1:1 mapping of ata_port to
 * shost, so host fields can be directly manipulated under ap->lock, in
 * the libsas हाल we need to hold a lock at the ha->level to coordinate
 * these events.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_std_end_eh(काष्ठा ata_port *ap)
अणु
	काष्ठा Scsi_Host *host = ap->scsi_host;

	host->host_eh_scheduled = 0;
पूर्ण
EXPORT_SYMBOL(ata_std_end_eh);


/**
 *	ata_port_schedule_eh - schedule error handling without a qc
 *	@ap: ATA port to schedule EH क्रम
 *
 *	Schedule error handling क्रम @ap.  EH will kick in as soon as
 *	all commands are drained.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
व्योम ata_port_schedule_eh(काष्ठा ata_port *ap)
अणु
	/* see: ata_std_sched_eh, unless you know better */
	ap->ops->sched_eh(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_port_schedule_eh);

अटल पूर्णांक ata_करो_link_पात(काष्ठा ata_port *ap, काष्ठा ata_link *link)
अणु
	काष्ठा ata_queued_cmd *qc;
	पूर्णांक tag, nr_पातed = 0;

	WARN_ON(!ap->ops->error_handler);

	/* we're gonna पात all commands, no need क्रम fast drain */
	ata_eh_set_pending(ap, 0);

	/* include पूर्णांकernal tag in iteration */
	ata_qc_क्रम_each_with_पूर्णांकernal(ap, qc, tag) अणु
		अगर (qc && (!link || qc->dev->link == link)) अणु
			qc->flags |= ATA_QCFLAG_FAILED;
			ata_qc_complete(qc);
			nr_पातed++;
		पूर्ण
	पूर्ण

	अगर (!nr_पातed)
		ata_port_schedule_eh(ap);

	वापस nr_पातed;
पूर्ण

/**
 *	ata_link_पात - पात all qc's on the link
 *	@link: ATA link to पात qc's क्रम
 *
 *	Abort all active qc's active on @link and schedule EH.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Number of पातed qc's.
 */
पूर्णांक ata_link_पात(काष्ठा ata_link *link)
अणु
	वापस ata_करो_link_पात(link->ap, link);
पूर्ण
EXPORT_SYMBOL_GPL(ata_link_पात);

/**
 *	ata_port_पात - पात all qc's on the port
 *	@ap: ATA port to पात qc's क्रम
 *
 *	Abort all active qc's of @ap and schedule EH.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host_set lock)
 *
 *	RETURNS:
 *	Number of पातed qc's.
 */
पूर्णांक ata_port_पात(काष्ठा ata_port *ap)
अणु
	वापस ata_करो_link_पात(ap, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(ata_port_पात);

/**
 *	__ata_port_मुक्तze - मुक्तze port
 *	@ap: ATA port to मुक्तze
 *
 *	This function is called when HSM violation or some other
 *	condition disrupts normal operation of the port.  Frozen port
 *	is not allowed to perक्रमm any operation until the port is
 *	thawed, which usually follows a successful reset.
 *
 *	ap->ops->मुक्तze() callback can be used क्रम मुक्तzing the port
 *	hardware-wise (e.g. mask पूर्णांकerrupt and stop DMA engine).  If a
 *	port cannot be frozen hardware-wise, the पूर्णांकerrupt handler
 *	must ack and clear पूर्णांकerrupts unconditionally जबतक the port
 *	is frozen.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल व्योम __ata_port_मुक्तze(काष्ठा ata_port *ap)
अणु
	WARN_ON(!ap->ops->error_handler);

	अगर (ap->ops->मुक्तze)
		ap->ops->मुक्तze(ap);

	ap->pflags |= ATA_PFLAG_FROZEN;

	DPRINTK("ata%u port frozen\n", ap->prपूर्णांक_id);
पूर्ण

/**
 *	ata_port_मुक्तze - पात & मुक्तze port
 *	@ap: ATA port to मुक्तze
 *
 *	Abort and मुक्तze @ap.  The मुक्तze operation must be called
 *	first, because some hardware requires special operations
 *	beक्रमe the taskfile रेजिस्टरs are accessible.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Number of पातed commands.
 */
पूर्णांक ata_port_मुक्तze(काष्ठा ata_port *ap)
अणु
	पूर्णांक nr_पातed;

	WARN_ON(!ap->ops->error_handler);

	__ata_port_मुक्तze(ap);
	nr_पातed = ata_port_पात(ap);

	वापस nr_पातed;
पूर्ण
EXPORT_SYMBOL_GPL(ata_port_मुक्तze);

/**
 *	ata_eh_मुक्तze_port - EH helper to मुक्तze port
 *	@ap: ATA port to मुक्तze
 *
 *	Freeze @ap.
 *
 *	LOCKING:
 *	None.
 */
व्योम ata_eh_मुक्तze_port(काष्ठा ata_port *ap)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!ap->ops->error_handler)
		वापस;

	spin_lock_irqsave(ap->lock, flags);
	__ata_port_मुक्तze(ap);
	spin_unlock_irqrestore(ap->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ata_eh_मुक्तze_port);

/**
 *	ata_eh_thaw_port - EH helper to thaw port
 *	@ap: ATA port to thaw
 *
 *	Thaw frozen port @ap.
 *
 *	LOCKING:
 *	None.
 */
व्योम ata_eh_thaw_port(काष्ठा ata_port *ap)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!ap->ops->error_handler)
		वापस;

	spin_lock_irqsave(ap->lock, flags);

	ap->pflags &= ~ATA_PFLAG_FROZEN;

	अगर (ap->ops->thaw)
		ap->ops->thaw(ap);

	spin_unlock_irqrestore(ap->lock, flags);

	DPRINTK("ata%u port thawed\n", ap->prपूर्णांक_id);
पूर्ण

अटल व्योम ata_eh_scsiकरोne(काष्ठा scsi_cmnd *scmd)
अणु
	/* nada */
पूर्ण

अटल व्योम __ata_eh_qc_complete(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(ap->lock, flags);
	qc->scsiकरोne = ata_eh_scsiकरोne;
	__ata_qc_complete(qc);
	WARN_ON(ata_tag_valid(qc->tag));
	spin_unlock_irqrestore(ap->lock, flags);

	scsi_eh_finish_cmd(scmd, &ap->eh_करोne_q);
पूर्ण

/**
 *	ata_eh_qc_complete - Complete an active ATA command from EH
 *	@qc: Command to complete
 *
 *	Indicate to the mid and upper layers that an ATA command has
 *	completed.  To be used from EH.
 */
व्योम ata_eh_qc_complete(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	scmd->retries = scmd->allowed;
	__ata_eh_qc_complete(qc);
पूर्ण

/**
 *	ata_eh_qc_retry - Tell midlayer to retry an ATA command after EH
 *	@qc: Command to retry
 *
 *	Indicate to the mid and upper layers that an ATA command
 *	should be retried.  To be used from EH.
 *
 *	SCSI midlayer limits the number of retries to scmd->allowed.
 *	scmd->allowed is incremented क्रम commands which get retried
 *	due to unrelated failures (qc->err_mask is zero).
 */
व्योम ata_eh_qc_retry(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;
	अगर (!qc->err_mask)
		scmd->allowed++;
	__ata_eh_qc_complete(qc);
पूर्ण

/**
 *	ata_dev_disable - disable ATA device
 *	@dev: ATA device to disable
 *
 *	Disable @dev.
 *
 *	Locking:
 *	EH context.
 */
व्योम ata_dev_disable(काष्ठा ata_device *dev)
अणु
	अगर (!ata_dev_enabled(dev))
		वापस;

	अगर (ata_msg_drv(dev->link->ap))
		ata_dev_warn(dev, "disabled\n");
	ata_acpi_on_disable(dev);
	ata_करोwn_xfermask_limit(dev, ATA_DNXFER_FORCE_PIO0 | ATA_DNXFER_QUIET);
	dev->class++;

	/* From now till the next successful probe, ering is used to
	 * track probe failures.  Clear accumulated device error info.
	 */
	ata_ering_clear(&dev->ering);
पूर्ण
EXPORT_SYMBOL_GPL(ata_dev_disable);

/**
 *	ata_eh_detach_dev - detach ATA device
 *	@dev: ATA device to detach
 *
 *	Detach @dev.
 *
 *	LOCKING:
 *	None.
 */
व्योम ata_eh_detach_dev(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_link *link = dev->link;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	अचिन्हित दीर्घ flags;

	ata_dev_disable(dev);

	spin_lock_irqsave(ap->lock, flags);

	dev->flags &= ~ATA_DFLAG_DETACH;

	अगर (ata_scsi_offline_dev(dev)) अणु
		dev->flags |= ATA_DFLAG_DETACHED;
		ap->pflags |= ATA_PFLAG_SCSI_HOTPLUG;
	पूर्ण

	/* clear per-dev EH info */
	ata_eh_clear_action(link, dev, &link->eh_info, ATA_EH_PERDEV_MASK);
	ata_eh_clear_action(link, dev, &link->eh_context.i, ATA_EH_PERDEV_MASK);
	ehc->saved_xfer_mode[dev->devno] = 0;
	ehc->saved_ncq_enabled &= ~(1 << dev->devno);

	spin_unlock_irqrestore(ap->lock, flags);
पूर्ण

/**
 *	ata_eh_about_to_करो - about to perक्रमm eh_action
 *	@link: target ATA link
 *	@dev: target ATA dev क्रम per-dev action (can be शून्य)
 *	@action: action about to be perक्रमmed
 *
 *	Called just beक्रमe perक्रमming EH actions to clear related bits
 *	in @link->eh_info such that eh actions are not unnecessarily
 *	repeated.
 *
 *	LOCKING:
 *	None.
 */
व्योम ata_eh_about_to_करो(काष्ठा ata_link *link, काष्ठा ata_device *dev,
			अचिन्हित पूर्णांक action)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_eh_info *ehi = &link->eh_info;
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(ap->lock, flags);

	ata_eh_clear_action(link, dev, ehi, action);

	/* About to take EH action, set RECOVERED.  Ignore actions on
	 * slave links as master will करो them again.
	 */
	अगर (!(ehc->i.flags & ATA_EHI_QUIET) && link != ap->slave_link)
		ap->pflags |= ATA_PFLAG_RECOVERED;

	spin_unlock_irqrestore(ap->lock, flags);
पूर्ण

/**
 *	ata_eh_करोne - EH action complete
 *	@link: ATA link क्रम which EH actions are complete
 *	@dev: target ATA dev क्रम per-dev action (can be शून्य)
 *	@action: action just completed
 *
 *	Called right after perक्रमming EH actions to clear related bits
 *	in @link->eh_context.
 *
 *	LOCKING:
 *	None.
 */
व्योम ata_eh_करोne(काष्ठा ata_link *link, काष्ठा ata_device *dev,
		 अचिन्हित पूर्णांक action)
अणु
	काष्ठा ata_eh_context *ehc = &link->eh_context;

	ata_eh_clear_action(link, dev, &ehc->i, action);
पूर्ण

/**
 *	ata_err_string - convert err_mask to descriptive string
 *	@err_mask: error mask to convert to string
 *
 *	Convert @err_mask to descriptive string.  Errors are
 *	prioritized according to severity and only the most severe
 *	error is reported.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	Descriptive string क्रम @err_mask
 */
अटल स्थिर अक्षर *ata_err_string(अचिन्हित पूर्णांक err_mask)
अणु
	अगर (err_mask & AC_ERR_HOST_BUS)
		वापस "host bus error";
	अगर (err_mask & AC_ERR_ATA_BUS)
		वापस "ATA bus error";
	अगर (err_mask & AC_ERR_TIMEOUT)
		वापस "timeout";
	अगर (err_mask & AC_ERR_HSM)
		वापस "HSM violation";
	अगर (err_mask & AC_ERR_SYSTEM)
		वापस "internal error";
	अगर (err_mask & AC_ERR_MEDIA)
		वापस "media error";
	अगर (err_mask & AC_ERR_INVALID)
		वापस "invalid argument";
	अगर (err_mask & AC_ERR_DEV)
		वापस "device error";
	अगर (err_mask & AC_ERR_NCQ)
		वापस "NCQ error";
	अगर (err_mask & AC_ERR_NODEV_HINT)
		वापस "Polling detection error";
	वापस "unknown error";
पूर्ण

/**
 *	atapi_eh_tur - perक्रमm ATAPI TEST_UNIT_READY
 *	@dev: target ATAPI device
 *	@r_sense_key: out parameter क्रम sense_key
 *
 *	Perक्रमm ATAPI TEST_UNIT_READY.
 *
 *	LOCKING:
 *	EH context (may sleep).
 *
 *	RETURNS:
 *	0 on success, AC_ERR_* mask on failure.
 */
अचिन्हित पूर्णांक atapi_eh_tur(काष्ठा ata_device *dev, u8 *r_sense_key)
अणु
	u8 cdb[ATAPI_CDB_LEN] = अणु TEST_UNIT_READY, 0, 0, 0, 0, 0 पूर्ण;
	काष्ठा ata_taskfile tf;
	अचिन्हित पूर्णांक err_mask;

	ata_tf_init(dev, &tf);

	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf.command = ATA_CMD_PACKET;
	tf.protocol = ATAPI_PROT_NODATA;

	err_mask = ata_exec_पूर्णांकernal(dev, &tf, cdb, DMA_NONE, शून्य, 0, 0);
	अगर (err_mask == AC_ERR_DEV)
		*r_sense_key = tf.feature >> 4;
	वापस err_mask;
पूर्ण

/**
 *	ata_eh_request_sense - perक्रमm REQUEST_SENSE_DATA_EXT
 *	@qc: qc to perक्रमm REQUEST_SENSE_SENSE_DATA_EXT to
 *	@cmd: scsi command क्रम which the sense code should be set
 *
 *	Perक्रमm REQUEST_SENSE_DATA_EXT after the device reported CHECK
 *	SENSE.  This function is an EH helper.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
अटल व्योम ata_eh_request_sense(काष्ठा ata_queued_cmd *qc,
				 काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा ata_device *dev = qc->dev;
	काष्ठा ata_taskfile tf;
	अचिन्हित पूर्णांक err_mask;

	अगर (qc->ap->pflags & ATA_PFLAG_FROZEN) अणु
		ata_dev_warn(dev, "sense data available but port frozen\n");
		वापस;
	पूर्ण

	अगर (!cmd || qc->flags & ATA_QCFLAG_SENSE_VALID)
		वापस;

	अगर (!ata_id_sense_reporting_enabled(dev->id)) अणु
		ata_dev_warn(qc->dev, "sense data reporting disabled\n");
		वापस;
	पूर्ण

	DPRINTK("ATA request sense\n");

	ata_tf_init(dev, &tf);
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf.flags |= ATA_TFLAG_LBA | ATA_TFLAG_LBA48;
	tf.command = ATA_CMD_REQ_SENSE_DATA;
	tf.protocol = ATA_PROT_NODATA;

	err_mask = ata_exec_पूर्णांकernal(dev, &tf, शून्य, DMA_NONE, शून्य, 0, 0);
	/* Ignore err_mask; ATA_ERR might be set */
	अगर (tf.command & ATA_SENSE) अणु
		ata_scsi_set_sense(dev, cmd, tf.lbah, tf.lbam, tf.lbal);
		qc->flags |= ATA_QCFLAG_SENSE_VALID;
	पूर्ण अन्यथा अणु
		ata_dev_warn(dev, "request sense failed stat %02x emask %x\n",
			     tf.command, err_mask);
	पूर्ण
पूर्ण

/**
 *	atapi_eh_request_sense - perक्रमm ATAPI REQUEST_SENSE
 *	@dev: device to perक्रमm REQUEST_SENSE to
 *	@sense_buf: result sense data buffer (SCSI_SENSE_BUFFERSIZE bytes दीर्घ)
 *	@dfl_sense_key: शेष sense key to use
 *
 *	Perक्रमm ATAPI REQUEST_SENSE after the device reported CHECK
 *	SENSE.  This function is EH helper.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, AC_ERR_* mask on failure
 */
अचिन्हित पूर्णांक atapi_eh_request_sense(काष्ठा ata_device *dev,
					   u8 *sense_buf, u8 dfl_sense_key)
अणु
	u8 cdb[ATAPI_CDB_LEN] =
		अणु REQUEST_SENSE, 0, 0, 0, SCSI_SENSE_BUFFERSIZE, 0 पूर्ण;
	काष्ठा ata_port *ap = dev->link->ap;
	काष्ठा ata_taskfile tf;

	DPRINTK("ATAPI request sense\n");

	स_रखो(sense_buf, 0, SCSI_SENSE_BUFFERSIZE);

	/* initialize sense_buf with the error रेजिस्टर,
	 * क्रम the हाल where they are -not- overwritten
	 */
	sense_buf[0] = 0x70;
	sense_buf[2] = dfl_sense_key;

	/* some devices समय out अगर garbage left in tf */
	ata_tf_init(dev, &tf);

	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf.command = ATA_CMD_PACKET;

	/* is it poपूर्णांकless to prefer PIO क्रम "safety reasons"? */
	अगर (ap->flags & ATA_FLAG_PIO_DMA) अणु
		tf.protocol = ATAPI_PROT_DMA;
		tf.feature |= ATAPI_PKT_DMA;
	पूर्ण अन्यथा अणु
		tf.protocol = ATAPI_PROT_PIO;
		tf.lbam = SCSI_SENSE_BUFFERSIZE;
		tf.lbah = 0;
	पूर्ण

	वापस ata_exec_पूर्णांकernal(dev, &tf, cdb, DMA_FROM_DEVICE,
				 sense_buf, SCSI_SENSE_BUFFERSIZE, 0);
पूर्ण

/**
 *	ata_eh_analyze_serror - analyze SError क्रम a failed port
 *	@link: ATA link to analyze SError क्रम
 *
 *	Analyze SError अगर available and further determine cause of
 *	failure.
 *
 *	LOCKING:
 *	None.
 */
अटल व्योम ata_eh_analyze_serror(काष्ठा ata_link *link)
अणु
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	u32 serror = ehc->i.serror;
	अचिन्हित पूर्णांक err_mask = 0, action = 0;
	u32 hotplug_mask;

	अगर (serror & (SERR_PERSISTENT | SERR_DATA)) अणु
		err_mask |= AC_ERR_ATA_BUS;
		action |= ATA_EH_RESET;
	पूर्ण
	अगर (serror & SERR_PROTOCOL) अणु
		err_mask |= AC_ERR_HSM;
		action |= ATA_EH_RESET;
	पूर्ण
	अगर (serror & SERR_INTERNAL) अणु
		err_mask |= AC_ERR_SYSTEM;
		action |= ATA_EH_RESET;
	पूर्ण

	/* Determine whether a hotplug event has occurred.  Both
	 * SError.N/X are considered hotplug events क्रम enabled or
	 * host links.  For disabled PMP links, only N bit is
	 * considered as X bit is left at 1 क्रम link plugging.
	 */
	अगर (link->lpm_policy > ATA_LPM_MAX_POWER)
		hotplug_mask = 0;	/* hotplug करोesn't work w/ LPM */
	अन्यथा अगर (!(link->flags & ATA_LFLAG_DISABLED) || ata_is_host_link(link))
		hotplug_mask = SERR_PHYRDY_CHG | SERR_DEV_XCHG;
	अन्यथा
		hotplug_mask = SERR_PHYRDY_CHG;

	अगर (serror & hotplug_mask)
		ata_ehi_hotplugged(&ehc->i);

	ehc->i.err_mask |= err_mask;
	ehc->i.action |= action;
पूर्ण

/**
 *	ata_eh_analyze_tf - analyze taskfile of a failed qc
 *	@qc: qc to analyze
 *	@tf: Taskfile रेजिस्टरs to analyze
 *
 *	Analyze taskfile of @qc and further determine cause of
 *	failure.  This function also requests ATAPI sense data अगर
 *	available.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	Determined recovery action
 */
अटल अचिन्हित पूर्णांक ata_eh_analyze_tf(काष्ठा ata_queued_cmd *qc,
				      स्थिर काष्ठा ata_taskfile *tf)
अणु
	अचिन्हित पूर्णांक पंचांगp, action = 0;
	u8 stat = tf->command, err = tf->feature;

	अगर ((stat & (ATA_BUSY | ATA_DRQ | ATA_DRDY)) != ATA_DRDY) अणु
		qc->err_mask |= AC_ERR_HSM;
		वापस ATA_EH_RESET;
	पूर्ण

	अगर (stat & (ATA_ERR | ATA_DF)) अणु
		qc->err_mask |= AC_ERR_DEV;
		/*
		 * Sense data reporting करोes not work अगर the
		 * device fault bit is set.
		 */
		अगर (stat & ATA_DF)
			stat &= ~ATA_SENSE;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	चयन (qc->dev->class) अणु
	हाल ATA_DEV_ZAC:
		अगर (stat & ATA_SENSE)
			ata_eh_request_sense(qc, qc->scsicmd);
		fallthrough;
	हाल ATA_DEV_ATA:
		अगर (err & ATA_ICRC)
			qc->err_mask |= AC_ERR_ATA_BUS;
		अगर (err & (ATA_UNC | ATA_AMNF))
			qc->err_mask |= AC_ERR_MEDIA;
		अगर (err & ATA_IDNF)
			qc->err_mask |= AC_ERR_INVALID;
		अवरोध;

	हाल ATA_DEV_ATAPI:
		अगर (!(qc->ap->pflags & ATA_PFLAG_FROZEN)) अणु
			पंचांगp = atapi_eh_request_sense(qc->dev,
						qc->scsicmd->sense_buffer,
						qc->result_tf.feature >> 4);
			अगर (!पंचांगp)
				qc->flags |= ATA_QCFLAG_SENSE_VALID;
			अन्यथा
				qc->err_mask |= पंचांगp;
		पूर्ण
	पूर्ण

	अगर (qc->flags & ATA_QCFLAG_SENSE_VALID) अणु
		क्रमागत scsi_disposition ret = scsi_check_sense(qc->scsicmd);
		/*
		 * SUCCESS here means that the sense code could be
		 * evaluated and should be passed to the upper layers
		 * क्रम correct evaluation.
		 * FAILED means the sense code could not be पूर्णांकerpreted
		 * and the device would need to be reset.
		 * NEEDS_RETRY and ADD_TO_MLQUEUE means that the
		 * command would need to be retried.
		 */
		अगर (ret == NEEDS_RETRY || ret == ADD_TO_MLQUEUE) अणु
			qc->flags |= ATA_QCFLAG_RETRY;
			qc->err_mask |= AC_ERR_OTHER;
		पूर्ण अन्यथा अगर (ret != SUCCESS) अणु
			qc->err_mask |= AC_ERR_HSM;
		पूर्ण
	पूर्ण
	अगर (qc->err_mask & (AC_ERR_HSM | AC_ERR_TIMEOUT | AC_ERR_ATA_BUS))
		action |= ATA_EH_RESET;

	वापस action;
पूर्ण

अटल पूर्णांक ata_eh_categorize_error(अचिन्हित पूर्णांक eflags, अचिन्हित पूर्णांक err_mask,
				   पूर्णांक *xfer_ok)
अणु
	पूर्णांक base = 0;

	अगर (!(eflags & ATA_EFLAG_DUBIOUS_XFER))
		*xfer_ok = 1;

	अगर (!*xfer_ok)
		base = ATA_ECAT_DUBIOUS_NONE;

	अगर (err_mask & AC_ERR_ATA_BUS)
		वापस base + ATA_ECAT_ATA_BUS;

	अगर (err_mask & AC_ERR_TIMEOUT)
		वापस base + ATA_ECAT_TOUT_HSM;

	अगर (eflags & ATA_EFLAG_IS_IO) अणु
		अगर (err_mask & AC_ERR_HSM)
			वापस base + ATA_ECAT_TOUT_HSM;
		अगर ((err_mask &
		     (AC_ERR_DEV|AC_ERR_MEDIA|AC_ERR_INVALID)) == AC_ERR_DEV)
			वापस base + ATA_ECAT_UNK_DEV;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा speed_करोwn_verdict_arg अणु
	u64 since;
	पूर्णांक xfer_ok;
	पूर्णांक nr_errors[ATA_ECAT_NR];
पूर्ण;

अटल पूर्णांक speed_करोwn_verdict_cb(काष्ठा ata_ering_entry *ent, व्योम *व्योम_arg)
अणु
	काष्ठा speed_करोwn_verdict_arg *arg = व्योम_arg;
	पूर्णांक cat;

	अगर ((ent->eflags & ATA_EFLAG_OLD_ER) || (ent->बारtamp < arg->since))
		वापस -1;

	cat = ata_eh_categorize_error(ent->eflags, ent->err_mask,
				      &arg->xfer_ok);
	arg->nr_errors[cat]++;

	वापस 0;
पूर्ण

/**
 *	ata_eh_speed_करोwn_verdict - Determine speed करोwn verdict
 *	@dev: Device of पूर्णांकerest
 *
 *	This function examines error ring of @dev and determines
 *	whether NCQ needs to be turned off, transfer speed should be
 *	stepped करोwn, or falling back to PIO is necessary.
 *
 *	ECAT_ATA_BUS	: ATA_BUS error क्रम any command
 *
 *	ECAT_TOUT_HSM	: TIMEOUT क्रम any command or HSM violation क्रम
 *			  IO commands
 *
 *	ECAT_UNK_DEV	: Unknown DEV error क्रम IO commands
 *
 *	ECAT_DUBIOUS_*	: Identical to above three but occurred जबतक
 *			  data transfer hasn't been verअगरied.
 *
 *	Verdicts are
 *
 *	NCQ_OFF		: Turn off NCQ.
 *
 *	SPEED_DOWN	: Speed करोwn transfer speed but करोn't fall back
 *			  to PIO.
 *
 *	FALLBACK_TO_PIO	: Fall back to PIO.
 *
 *	Even अगर multiple verdicts are वापसed, only one action is
 *	taken per error.  An action triggered by non-DUBIOUS errors
 *	clears ering, जबतक one triggered by DUBIOUS_* errors करोesn't.
 *	This is to expedite speed करोwn decisions right after device is
 *	initially configured.
 *
 *	The following are speed करोwn rules.  #1 and #2 deal with
 *	DUBIOUS errors.
 *
 *	1. If more than one DUBIOUS_ATA_BUS or DUBIOUS_TOUT_HSM errors
 *	   occurred during last 5 mins, SPEED_DOWN and FALLBACK_TO_PIO.
 *
 *	2. If more than one DUBIOUS_TOUT_HSM or DUBIOUS_UNK_DEV errors
 *	   occurred during last 5 mins, NCQ_OFF.
 *
 *	3. If more than 8 ATA_BUS, TOUT_HSM or UNK_DEV errors
 *	   occurred during last 5 mins, FALLBACK_TO_PIO
 *
 *	4. If more than 3 TOUT_HSM or UNK_DEV errors occurred
 *	   during last 10 mins, NCQ_OFF.
 *
 *	5. If more than 3 ATA_BUS or TOUT_HSM errors, or more than 6
 *	   UNK_DEV errors occurred during last 10 mins, SPEED_DOWN.
 *
 *	LOCKING:
 *	Inherited from caller.
 *
 *	RETURNS:
 *	OR of ATA_EH_SPDN_* flags.
 */
अटल अचिन्हित पूर्णांक ata_eh_speed_करोwn_verdict(काष्ठा ata_device *dev)
अणु
	स्थिर u64 j5mins = 5LLU * 60 * HZ, j10mins = 10LLU * 60 * HZ;
	u64 j64 = get_jअगरfies_64();
	काष्ठा speed_करोwn_verdict_arg arg;
	अचिन्हित पूर्णांक verdict = 0;

	/* scan past 5 mins of error history */
	स_रखो(&arg, 0, माप(arg));
	arg.since = j64 - min(j64, j5mins);
	ata_ering_map(&dev->ering, speed_करोwn_verdict_cb, &arg);

	अगर (arg.nr_errors[ATA_ECAT_DUBIOUS_ATA_BUS] +
	    arg.nr_errors[ATA_ECAT_DUBIOUS_TOUT_HSM] > 1)
		verdict |= ATA_EH_SPDN_SPEED_DOWN |
			ATA_EH_SPDN_FALLBACK_TO_PIO | ATA_EH_SPDN_KEEP_ERRORS;

	अगर (arg.nr_errors[ATA_ECAT_DUBIOUS_TOUT_HSM] +
	    arg.nr_errors[ATA_ECAT_DUBIOUS_UNK_DEV] > 1)
		verdict |= ATA_EH_SPDN_NCQ_OFF | ATA_EH_SPDN_KEEP_ERRORS;

	अगर (arg.nr_errors[ATA_ECAT_ATA_BUS] +
	    arg.nr_errors[ATA_ECAT_TOUT_HSM] +
	    arg.nr_errors[ATA_ECAT_UNK_DEV] > 6)
		verdict |= ATA_EH_SPDN_FALLBACK_TO_PIO;

	/* scan past 10 mins of error history */
	स_रखो(&arg, 0, माप(arg));
	arg.since = j64 - min(j64, j10mins);
	ata_ering_map(&dev->ering, speed_करोwn_verdict_cb, &arg);

	अगर (arg.nr_errors[ATA_ECAT_TOUT_HSM] +
	    arg.nr_errors[ATA_ECAT_UNK_DEV] > 3)
		verdict |= ATA_EH_SPDN_NCQ_OFF;

	अगर (arg.nr_errors[ATA_ECAT_ATA_BUS] +
	    arg.nr_errors[ATA_ECAT_TOUT_HSM] > 3 ||
	    arg.nr_errors[ATA_ECAT_UNK_DEV] > 6)
		verdict |= ATA_EH_SPDN_SPEED_DOWN;

	वापस verdict;
पूर्ण

/**
 *	ata_eh_speed_करोwn - record error and speed करोwn अगर necessary
 *	@dev: Failed device
 *	@eflags: mask of ATA_EFLAG_* flags
 *	@err_mask: err_mask of the error
 *
 *	Record error and examine error history to determine whether
 *	adjusting transmission speed is necessary.  It also sets
 *	transmission limits appropriately अगर such adjusपंचांगent is
 *	necessary.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	Determined recovery action.
 */
अटल अचिन्हित पूर्णांक ata_eh_speed_करोwn(काष्ठा ata_device *dev,
				अचिन्हित पूर्णांक eflags, अचिन्हित पूर्णांक err_mask)
अणु
	काष्ठा ata_link *link = ata_dev_phys_link(dev);
	पूर्णांक xfer_ok = 0;
	अचिन्हित पूर्णांक verdict;
	अचिन्हित पूर्णांक action = 0;

	/* करोn't bother अगर Cat-0 error */
	अगर (ata_eh_categorize_error(eflags, err_mask, &xfer_ok) == 0)
		वापस 0;

	/* record error and determine whether speed करोwn is necessary */
	ata_ering_record(&dev->ering, eflags, err_mask);
	verdict = ata_eh_speed_करोwn_verdict(dev);

	/* turn off NCQ? */
	अगर ((verdict & ATA_EH_SPDN_NCQ_OFF) &&
	    (dev->flags & (ATA_DFLAG_PIO | ATA_DFLAG_NCQ |
			   ATA_DFLAG_NCQ_OFF)) == ATA_DFLAG_NCQ) अणु
		dev->flags |= ATA_DFLAG_NCQ_OFF;
		ata_dev_warn(dev, "NCQ disabled due to excessive errors\n");
		जाओ करोne;
	पूर्ण

	/* speed करोwn? */
	अगर (verdict & ATA_EH_SPDN_SPEED_DOWN) अणु
		/* speed करोwn SATA link speed अगर possible */
		अगर (sata_करोwn_spd_limit(link, 0) == 0) अणु
			action |= ATA_EH_RESET;
			जाओ करोne;
		पूर्ण

		/* lower transfer mode */
		अगर (dev->spdn_cnt < 2) अणु
			अटल स्थिर पूर्णांक dma_dnxfer_sel[] =
				अणु ATA_DNXFER_DMA, ATA_DNXFER_40C पूर्ण;
			अटल स्थिर पूर्णांक pio_dnxfer_sel[] =
				अणु ATA_DNXFER_PIO, ATA_DNXFER_FORCE_PIO0 पूर्ण;
			पूर्णांक sel;

			अगर (dev->xfer_shअगरt != ATA_SHIFT_PIO)
				sel = dma_dnxfer_sel[dev->spdn_cnt];
			अन्यथा
				sel = pio_dnxfer_sel[dev->spdn_cnt];

			dev->spdn_cnt++;

			अगर (ata_करोwn_xfermask_limit(dev, sel) == 0) अणु
				action |= ATA_EH_RESET;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Fall back to PIO?  Slowing करोwn to PIO is meaningless क्रम
	 * SATA ATA devices.  Consider it only क्रम PATA and SATAPI.
	 */
	अगर ((verdict & ATA_EH_SPDN_FALLBACK_TO_PIO) && (dev->spdn_cnt >= 2) &&
	    (link->ap->cbl != ATA_CBL_SATA || dev->class == ATA_DEV_ATAPI) &&
	    (dev->xfer_shअगरt != ATA_SHIFT_PIO)) अणु
		अगर (ata_करोwn_xfermask_limit(dev, ATA_DNXFER_FORCE_PIO) == 0) अणु
			dev->spdn_cnt = 0;
			action |= ATA_EH_RESET;
			जाओ करोne;
		पूर्ण
	पूर्ण

	वापस 0;
 करोne:
	/* device has been slowed करोwn, blow error history */
	अगर (!(verdict & ATA_EH_SPDN_KEEP_ERRORS))
		ata_ering_clear(&dev->ering);
	वापस action;
पूर्ण

/**
 *	ata_eh_worth_retry - analyze error and decide whether to retry
 *	@qc: qc to possibly retry
 *
 *	Look at the cause of the error and decide अगर a retry
 * 	might be useful or not.  We करोn't want to retry media errors
 *	because the drive itself has probably alपढ़ोy taken 10-30 seconds
 *	करोing its own पूर्णांकernal retries beक्रमe reporting the failure.
 */
अटल अंतरभूत पूर्णांक ata_eh_worth_retry(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (qc->err_mask & AC_ERR_MEDIA)
		वापस 0;	/* करोn't retry media errors */
	अगर (qc->flags & ATA_QCFLAG_IO)
		वापस 1;	/* otherwise retry anything from fs stack */
	अगर (qc->err_mask & AC_ERR_INVALID)
		वापस 0;	/* करोn't retry these */
	वापस qc->err_mask != AC_ERR_DEV;  /* retry अगर not dev error */
पूर्ण

/**
 *      ata_eh_quiet - check अगर we need to be quiet about a command error
 *      @qc: qc to check
 *
 *      Look at the qc flags anbd its scsi command request flags to determine
 *      अगर we need to be quiet about the command failure.
 */
अटल अंतरभूत bool ata_eh_quiet(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (qc->scsicmd &&
	    qc->scsicmd->request->rq_flags & RQF_QUIET)
		qc->flags |= ATA_QCFLAG_QUIET;
	वापस qc->flags & ATA_QCFLAG_QUIET;
पूर्ण

/**
 *	ata_eh_link_स्वतःpsy - analyze error and determine recovery action
 *	@link: host link to perक्रमm स्वतःpsy on
 *
 *	Analyze why @link failed and determine which recovery actions
 *	are needed.  This function also sets more detailed AC_ERR_*
 *	values and fills sense data क्रम ATAPI CHECK SENSE.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
अटल व्योम ata_eh_link_स्वतःpsy(काष्ठा ata_link *link)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	काष्ठा ata_queued_cmd *qc;
	काष्ठा ata_device *dev;
	अचिन्हित पूर्णांक all_err_mask = 0, eflags = 0;
	पूर्णांक tag, nr_failed = 0, nr_quiet = 0;
	u32 serror;
	पूर्णांक rc;

	DPRINTK("ENTER\n");

	अगर (ehc->i.flags & ATA_EHI_NO_AUTOPSY)
		वापस;

	/* obtain and analyze SError */
	rc = sata_scr_पढ़ो(link, SCR_ERROR, &serror);
	अगर (rc == 0) अणु
		ehc->i.serror |= serror;
		ata_eh_analyze_serror(link);
	पूर्ण अन्यथा अगर (rc != -EOPNOTSUPP) अणु
		/* SError पढ़ो failed, क्रमce reset and probing */
		ehc->i.probe_mask |= ATA_ALL_DEVICES;
		ehc->i.action |= ATA_EH_RESET;
		ehc->i.err_mask |= AC_ERR_OTHER;
	पूर्ण

	/* analyze NCQ failure */
	ata_eh_analyze_ncq_error(link);

	/* any real error trumps AC_ERR_OTHER */
	अगर (ehc->i.err_mask & ~AC_ERR_OTHER)
		ehc->i.err_mask &= ~AC_ERR_OTHER;

	all_err_mask |= ehc->i.err_mask;

	ata_qc_क्रम_each_raw(ap, qc, tag) अणु
		अगर (!(qc->flags & ATA_QCFLAG_FAILED) ||
		    ata_dev_phys_link(qc->dev) != link)
			जारी;

		/* inherit upper level err_mask */
		qc->err_mask |= ehc->i.err_mask;

		/* analyze TF */
		ehc->i.action |= ata_eh_analyze_tf(qc, &qc->result_tf);

		/* DEV errors are probably spurious in हाल of ATA_BUS error */
		अगर (qc->err_mask & AC_ERR_ATA_BUS)
			qc->err_mask &= ~(AC_ERR_DEV | AC_ERR_MEDIA |
					  AC_ERR_INVALID);

		/* any real error trumps unknown error */
		अगर (qc->err_mask & ~AC_ERR_OTHER)
			qc->err_mask &= ~AC_ERR_OTHER;

		/*
		 * SENSE_VALID trumps dev/unknown error and revalidation. Upper
		 * layers will determine whether the command is worth retrying
		 * based on the sense data and device class/type. Otherwise,
		 * determine directly अगर the command is worth retrying using its
		 * error mask and flags.
		 */
		अगर (qc->flags & ATA_QCFLAG_SENSE_VALID)
			qc->err_mask &= ~(AC_ERR_DEV | AC_ERR_OTHER);
		अन्यथा अगर (ata_eh_worth_retry(qc))
			qc->flags |= ATA_QCFLAG_RETRY;

		/* accumulate error info */
		ehc->i.dev = qc->dev;
		all_err_mask |= qc->err_mask;
		अगर (qc->flags & ATA_QCFLAG_IO)
			eflags |= ATA_EFLAG_IS_IO;
		trace_ata_eh_link_स्वतःpsy_qc(qc);

		/* Count quiet errors */
		अगर (ata_eh_quiet(qc))
			nr_quiet++;
		nr_failed++;
	पूर्ण

	/* If all failed commands requested silence, then be quiet */
	अगर (nr_quiet == nr_failed)
		ehc->i.flags |= ATA_EHI_QUIET;

	/* enक्रमce शेष EH actions */
	अगर (ap->pflags & ATA_PFLAG_FROZEN ||
	    all_err_mask & (AC_ERR_HSM | AC_ERR_TIMEOUT))
		ehc->i.action |= ATA_EH_RESET;
	अन्यथा अगर (((eflags & ATA_EFLAG_IS_IO) && all_err_mask) ||
		 (!(eflags & ATA_EFLAG_IS_IO) && (all_err_mask & ~AC_ERR_DEV)))
		ehc->i.action |= ATA_EH_REVALIDATE;

	/* If we have offending qcs and the associated failed device,
	 * perक्रमm per-dev EH action only on the offending device.
	 */
	अगर (ehc->i.dev) अणु
		ehc->i.dev_action[ehc->i.dev->devno] |=
			ehc->i.action & ATA_EH_PERDEV_MASK;
		ehc->i.action &= ~ATA_EH_PERDEV_MASK;
	पूर्ण

	/* propagate समयout to host link */
	अगर ((all_err_mask & AC_ERR_TIMEOUT) && !ata_is_host_link(link))
		ap->link.eh_context.i.err_mask |= AC_ERR_TIMEOUT;

	/* record error and consider speeding करोwn */
	dev = ehc->i.dev;
	अगर (!dev && ((ata_link_max_devices(link) == 1 &&
		      ata_dev_enabled(link->device))))
	    dev = link->device;

	अगर (dev) अणु
		अगर (dev->flags & ATA_DFLAG_DUBIOUS_XFER)
			eflags |= ATA_EFLAG_DUBIOUS_XFER;
		ehc->i.action |= ata_eh_speed_करोwn(dev, eflags, all_err_mask);
		trace_ata_eh_link_स्वतःpsy(dev, ehc->i.action, all_err_mask);
	पूर्ण
	DPRINTK("EXIT\n");
पूर्ण

/**
 *	ata_eh_स्वतःpsy - analyze error and determine recovery action
 *	@ap: host port to perक्रमm स्वतःpsy on
 *
 *	Analyze all links of @ap and determine why they failed and
 *	which recovery actions are needed.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
व्योम ata_eh_स्वतःpsy(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_link *link;

	ata_क्रम_each_link(link, ap, EDGE)
		ata_eh_link_स्वतःpsy(link);

	/* Handle the frigging slave link.  Autopsy is करोne similarly
	 * but actions and flags are transferred over to the master
	 * link and handled from there.
	 */
	अगर (ap->slave_link) अणु
		काष्ठा ata_eh_context *mehc = &ap->link.eh_context;
		काष्ठा ata_eh_context *sehc = &ap->slave_link->eh_context;

		/* transfer control flags from master to slave */
		sehc->i.flags |= mehc->i.flags & ATA_EHI_TO_SLAVE_MASK;

		/* perक्रमm स्वतःpsy on the slave link */
		ata_eh_link_स्वतःpsy(ap->slave_link);

		/* transfer actions from slave to master and clear slave */
		ata_eh_about_to_करो(ap->slave_link, शून्य, ATA_EH_ALL_ACTIONS);
		mehc->i.action		|= sehc->i.action;
		mehc->i.dev_action[1]	|= sehc->i.dev_action[1];
		mehc->i.flags		|= sehc->i.flags;
		ata_eh_करोne(ap->slave_link, शून्य, ATA_EH_ALL_ACTIONS);
	पूर्ण

	/* Autopsy of fanout ports can affect host link स्वतःpsy.
	 * Perक्रमm host link स्वतःpsy last.
	 */
	अगर (sata_pmp_attached(ap))
		ata_eh_link_स्वतःpsy(&ap->link);
पूर्ण

/**
 *	ata_get_cmd_descript - get description क्रम ATA command
 *	@command: ATA command code to get description क्रम
 *
 *	Return a textual description of the given command, or शून्य अगर the
 *	command is not known.
 *
 *	LOCKING:
 *	None
 */
स्थिर अक्षर *ata_get_cmd_descript(u8 command)
अणु
#अगर_घोषित CONFIG_ATA_VERBOSE_ERROR
	अटल स्थिर काष्ठा
	अणु
		u8 command;
		स्थिर अक्षर *text;
	पूर्ण cmd_descr[] = अणु
		अणु ATA_CMD_DEV_RESET,		"DEVICE RESET" पूर्ण,
		अणु ATA_CMD_CHK_POWER,		"CHECK POWER MODE" पूर्ण,
		अणु ATA_CMD_STANDBY,		"STANDBY" पूर्ण,
		अणु ATA_CMD_IDLE,			"IDLE" पूर्ण,
		अणु ATA_CMD_EDD,			"EXECUTE DEVICE DIAGNOSTIC" पूर्ण,
		अणु ATA_CMD_DOWNLOAD_MICRO,	"DOWNLOAD MICROCODE" पूर्ण,
		अणु ATA_CMD_DOWNLOAD_MICRO_DMA,	"DOWNLOAD MICROCODE DMA" पूर्ण,
		अणु ATA_CMD_NOP,			"NOP" पूर्ण,
		अणु ATA_CMD_FLUSH,		"FLUSH CACHE" पूर्ण,
		अणु ATA_CMD_FLUSH_EXT,		"FLUSH CACHE EXT" पूर्ण,
		अणु ATA_CMD_ID_ATA,		"IDENTIFY DEVICE" पूर्ण,
		अणु ATA_CMD_ID_ATAPI,		"IDENTIFY PACKET DEVICE" पूर्ण,
		अणु ATA_CMD_SERVICE,		"SERVICE" पूर्ण,
		अणु ATA_CMD_READ,			"READ DMA" पूर्ण,
		अणु ATA_CMD_READ_EXT,		"READ DMA EXT" पूर्ण,
		अणु ATA_CMD_READ_QUEUED,		"READ DMA QUEUED" पूर्ण,
		अणु ATA_CMD_READ_STREAM_EXT,	"READ STREAM EXT" पूर्ण,
		अणु ATA_CMD_READ_STREAM_DMA_EXT,  "READ STREAM DMA EXT" पूर्ण,
		अणु ATA_CMD_WRITE,		"WRITE DMA" पूर्ण,
		अणु ATA_CMD_WRITE_EXT,		"WRITE DMA EXT" पूर्ण,
		अणु ATA_CMD_WRITE_QUEUED,		"WRITE DMA QUEUED EXT" पूर्ण,
		अणु ATA_CMD_WRITE_STREAM_EXT,	"WRITE STREAM EXT" पूर्ण,
		अणु ATA_CMD_WRITE_STREAM_DMA_EXT, "WRITE STREAM DMA EXT" पूर्ण,
		अणु ATA_CMD_WRITE_FUA_EXT,	"WRITE DMA FUA EXT" पूर्ण,
		अणु ATA_CMD_WRITE_QUEUED_FUA_EXT, "WRITE DMA QUEUED FUA EXT" पूर्ण,
		अणु ATA_CMD_FPDMA_READ,		"READ FPDMA QUEUED" पूर्ण,
		अणु ATA_CMD_FPDMA_WRITE,		"WRITE FPDMA QUEUED" पूर्ण,
		अणु ATA_CMD_FPDMA_SEND,		"SEND FPDMA QUEUED" पूर्ण,
		अणु ATA_CMD_FPDMA_RECV,		"RECEIVE FPDMA QUEUED" पूर्ण,
		अणु ATA_CMD_PIO_READ,		"READ SECTOR(S)" पूर्ण,
		अणु ATA_CMD_PIO_READ_EXT,		"READ SECTOR(S) EXT" पूर्ण,
		अणु ATA_CMD_PIO_WRITE,		"WRITE SECTOR(S)" पूर्ण,
		अणु ATA_CMD_PIO_WRITE_EXT,	"WRITE SECTOR(S) EXT" पूर्ण,
		अणु ATA_CMD_READ_MULTI,		"READ MULTIPLE" पूर्ण,
		अणु ATA_CMD_READ_MULTI_EXT,	"READ MULTIPLE EXT" पूर्ण,
		अणु ATA_CMD_WRITE_MULTI,		"WRITE MULTIPLE" पूर्ण,
		अणु ATA_CMD_WRITE_MULTI_EXT,	"WRITE MULTIPLE EXT" पूर्ण,
		अणु ATA_CMD_WRITE_MULTI_FUA_EXT,	"WRITE MULTIPLE FUA EXT" पूर्ण,
		अणु ATA_CMD_SET_FEATURES,		"SET FEATURES" पूर्ण,
		अणु ATA_CMD_SET_MULTI,		"SET MULTIPLE MODE" पूर्ण,
		अणु ATA_CMD_VERIFY,		"READ VERIFY SECTOR(S)" पूर्ण,
		अणु ATA_CMD_VERIFY_EXT,		"READ VERIFY SECTOR(S) EXT" पूर्ण,
		अणु ATA_CMD_WRITE_UNCORR_EXT,	"WRITE UNCORRECTABLE EXT" पूर्ण,
		अणु ATA_CMD_STANDBYNOW1,		"STANDBY IMMEDIATE" पूर्ण,
		अणु ATA_CMD_IDLEIMMEDIATE,	"IDLE IMMEDIATE" पूर्ण,
		अणु ATA_CMD_SLEEP,		"SLEEP" पूर्ण,
		अणु ATA_CMD_INIT_DEV_PARAMS,	"INITIALIZE DEVICE PARAMETERS" पूर्ण,
		अणु ATA_CMD_READ_NATIVE_MAX,	"READ NATIVE MAX ADDRESS" पूर्ण,
		अणु ATA_CMD_READ_NATIVE_MAX_EXT,	"READ NATIVE MAX ADDRESS EXT" पूर्ण,
		अणु ATA_CMD_SET_MAX,		"SET MAX ADDRESS" पूर्ण,
		अणु ATA_CMD_SET_MAX_EXT,		"SET MAX ADDRESS EXT" पूर्ण,
		अणु ATA_CMD_READ_LOG_EXT,		"READ LOG EXT" पूर्ण,
		अणु ATA_CMD_WRITE_LOG_EXT,	"WRITE LOG EXT" पूर्ण,
		अणु ATA_CMD_READ_LOG_DMA_EXT,	"READ LOG DMA EXT" पूर्ण,
		अणु ATA_CMD_WRITE_LOG_DMA_EXT,	"WRITE LOG DMA EXT" पूर्ण,
		अणु ATA_CMD_TRUSTED_NONDATA,	"TRUSTED NON-DATA" पूर्ण,
		अणु ATA_CMD_TRUSTED_RCV,		"TRUSTED RECEIVE" पूर्ण,
		अणु ATA_CMD_TRUSTED_RCV_DMA,	"TRUSTED RECEIVE DMA" पूर्ण,
		अणु ATA_CMD_TRUSTED_SND,		"TRUSTED SEND" पूर्ण,
		अणु ATA_CMD_TRUSTED_SND_DMA,	"TRUSTED SEND DMA" पूर्ण,
		अणु ATA_CMD_PMP_READ,		"READ BUFFER" पूर्ण,
		अणु ATA_CMD_PMP_READ_DMA,		"READ BUFFER DMA" पूर्ण,
		अणु ATA_CMD_PMP_WRITE,		"WRITE BUFFER" पूर्ण,
		अणु ATA_CMD_PMP_WRITE_DMA,	"WRITE BUFFER DMA" पूर्ण,
		अणु ATA_CMD_CONF_OVERLAY,		"DEVICE CONFIGURATION OVERLAY" पूर्ण,
		अणु ATA_CMD_SEC_SET_PASS,		"SECURITY SET PASSWORD" पूर्ण,
		अणु ATA_CMD_SEC_UNLOCK,		"SECURITY UNLOCK" पूर्ण,
		अणु ATA_CMD_SEC_ERASE_PREP,	"SECURITY ERASE PREPARE" पूर्ण,
		अणु ATA_CMD_SEC_ERASE_UNIT,	"SECURITY ERASE UNIT" पूर्ण,
		अणु ATA_CMD_SEC_FREEZE_LOCK,	"SECURITY FREEZE LOCK" पूर्ण,
		अणु ATA_CMD_SEC_DISABLE_PASS,	"SECURITY DISABLE PASSWORD" पूर्ण,
		अणु ATA_CMD_CONFIG_STREAM,	"CONFIGURE STREAM" पूर्ण,
		अणु ATA_CMD_SMART,		"SMART" पूर्ण,
		अणु ATA_CMD_MEDIA_LOCK,		"DOOR LOCK" पूर्ण,
		अणु ATA_CMD_MEDIA_UNLOCK,		"DOOR UNLOCK" पूर्ण,
		अणु ATA_CMD_DSM,			"DATA SET MANAGEMENT" पूर्ण,
		अणु ATA_CMD_CHK_MED_CRD_TYP,	"CHECK MEDIA CARD TYPE" पूर्ण,
		अणु ATA_CMD_CFA_REQ_EXT_ERR,	"CFA REQUEST EXTENDED ERROR" पूर्ण,
		अणु ATA_CMD_CFA_WRITE_NE,		"CFA WRITE SECTORS WITHOUT ERASE" पूर्ण,
		अणु ATA_CMD_CFA_TRANS_SECT,	"CFA TRANSLATE SECTOR" पूर्ण,
		अणु ATA_CMD_CFA_ERASE,		"CFA ERASE SECTORS" पूर्ण,
		अणु ATA_CMD_CFA_WRITE_MULT_NE,	"CFA WRITE MULTIPLE WITHOUT ERASE" पूर्ण,
		अणु ATA_CMD_REQ_SENSE_DATA,	"REQUEST SENSE DATA EXT" पूर्ण,
		अणु ATA_CMD_SANITIZE_DEVICE,	"SANITIZE DEVICE" पूर्ण,
		अणु ATA_CMD_ZAC_MGMT_IN,		"ZAC MANAGEMENT IN" पूर्ण,
		अणु ATA_CMD_ZAC_MGMT_OUT,		"ZAC MANAGEMENT OUT" पूर्ण,
		अणु ATA_CMD_READ_LONG,		"READ LONG (with retries)" पूर्ण,
		अणु ATA_CMD_READ_LONG_ONCE,	"READ LONG (without retries)" पूर्ण,
		अणु ATA_CMD_WRITE_LONG,		"WRITE LONG (with retries)" पूर्ण,
		अणु ATA_CMD_WRITE_LONG_ONCE,	"WRITE LONG (without retries)" पूर्ण,
		अणु ATA_CMD_RESTORE,		"RECALIBRATE" पूर्ण,
		अणु 0,				शून्य पूर्ण /* terminate list */
	पूर्ण;

	अचिन्हित पूर्णांक i;
	क्रम (i = 0; cmd_descr[i].text; i++)
		अगर (cmd_descr[i].command == command)
			वापस cmd_descr[i].text;
#पूर्ण_अगर

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ata_get_cmd_descript);

/**
 *	ata_eh_link_report - report error handling to user
 *	@link: ATA link EH is going on
 *
 *	Report EH to user.
 *
 *	LOCKING:
 *	None.
 */
अटल व्योम ata_eh_link_report(काष्ठा ata_link *link)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	काष्ठा ata_queued_cmd *qc;
	स्थिर अक्षर *frozen, *desc;
	अक्षर tries_buf[6] = "";
	पूर्णांक tag, nr_failed = 0;

	अगर (ehc->i.flags & ATA_EHI_QUIET)
		वापस;

	desc = शून्य;
	अगर (ehc->i.desc[0] != '\0')
		desc = ehc->i.desc;

	ata_qc_क्रम_each_raw(ap, qc, tag) अणु
		अगर (!(qc->flags & ATA_QCFLAG_FAILED) ||
		    ata_dev_phys_link(qc->dev) != link ||
		    ((qc->flags & ATA_QCFLAG_QUIET) &&
		     qc->err_mask == AC_ERR_DEV))
			जारी;
		अगर (qc->flags & ATA_QCFLAG_SENSE_VALID && !qc->err_mask)
			जारी;

		nr_failed++;
	पूर्ण

	अगर (!nr_failed && !ehc->i.err_mask)
		वापस;

	frozen = "";
	अगर (ap->pflags & ATA_PFLAG_FROZEN)
		frozen = " frozen";

	अगर (ap->eh_tries < ATA_EH_MAX_TRIES)
		snम_लिखो(tries_buf, माप(tries_buf), " t%d",
			 ap->eh_tries);

	अगर (ehc->i.dev) अणु
		ata_dev_err(ehc->i.dev, "exception Emask 0x%x "
			    "SAct 0x%x SErr 0x%x action 0x%x%s%s\n",
			    ehc->i.err_mask, link->sactive, ehc->i.serror,
			    ehc->i.action, frozen, tries_buf);
		अगर (desc)
			ata_dev_err(ehc->i.dev, "%s\n", desc);
	पूर्ण अन्यथा अणु
		ata_link_err(link, "exception Emask 0x%x "
			     "SAct 0x%x SErr 0x%x action 0x%x%s%s\n",
			     ehc->i.err_mask, link->sactive, ehc->i.serror,
			     ehc->i.action, frozen, tries_buf);
		अगर (desc)
			ata_link_err(link, "%s\n", desc);
	पूर्ण

#अगर_घोषित CONFIG_ATA_VERBOSE_ERROR
	अगर (ehc->i.serror)
		ata_link_err(link,
		  "SError: { %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s}\n",
		  ehc->i.serror & SERR_DATA_RECOVERED ? "RecovData " : "",
		  ehc->i.serror & SERR_COMM_RECOVERED ? "RecovComm " : "",
		  ehc->i.serror & SERR_DATA ? "UnrecovData " : "",
		  ehc->i.serror & SERR_PERSISTENT ? "Persist " : "",
		  ehc->i.serror & SERR_PROTOCOL ? "Proto " : "",
		  ehc->i.serror & SERR_INTERNAL ? "HostInt " : "",
		  ehc->i.serror & SERR_PHYRDY_CHG ? "PHYRdyChg " : "",
		  ehc->i.serror & SERR_PHY_INT_ERR ? "PHYInt " : "",
		  ehc->i.serror & SERR_COMM_WAKE ? "CommWake " : "",
		  ehc->i.serror & SERR_10B_8B_ERR ? "10B8B " : "",
		  ehc->i.serror & SERR_DISPARITY ? "Dispar " : "",
		  ehc->i.serror & SERR_CRC ? "BadCRC " : "",
		  ehc->i.serror & SERR_HANDSHAKE ? "Handshk " : "",
		  ehc->i.serror & SERR_LINK_SEQ_ERR ? "LinkSeq " : "",
		  ehc->i.serror & SERR_TRANS_ST_ERROR ? "TrStaTrns " : "",
		  ehc->i.serror & SERR_UNRECOG_FIS ? "UnrecFIS " : "",
		  ehc->i.serror & SERR_DEV_XCHG ? "DevExch " : "");
#पूर्ण_अगर

	ata_qc_क्रम_each_raw(ap, qc, tag) अणु
		काष्ठा ata_taskfile *cmd = &qc->tf, *res = &qc->result_tf;
		अक्षर data_buf[20] = "";
		अक्षर cdb_buf[70] = "";

		अगर (!(qc->flags & ATA_QCFLAG_FAILED) ||
		    ata_dev_phys_link(qc->dev) != link || !qc->err_mask)
			जारी;

		अगर (qc->dma_dir != DMA_NONE) अणु
			अटल स्थिर अक्षर *dma_str[] = अणु
				[DMA_BIसूचीECTIONAL]	= "bidi",
				[DMA_TO_DEVICE]		= "out",
				[DMA_FROM_DEVICE]	= "in",
			पूर्ण;
			स्थिर अक्षर *prot_str = शून्य;

			चयन (qc->tf.protocol) अणु
			हाल ATA_PROT_UNKNOWN:
				prot_str = "unknown";
				अवरोध;
			हाल ATA_PROT_NODATA:
				prot_str = "nodata";
				अवरोध;
			हाल ATA_PROT_PIO:
				prot_str = "pio";
				अवरोध;
			हाल ATA_PROT_DMA:
				prot_str = "dma";
				अवरोध;
			हाल ATA_PROT_NCQ:
				prot_str = "ncq dma";
				अवरोध;
			हाल ATA_PROT_NCQ_NODATA:
				prot_str = "ncq nodata";
				अवरोध;
			हाल ATAPI_PROT_NODATA:
				prot_str = "nodata";
				अवरोध;
			हाल ATAPI_PROT_PIO:
				prot_str = "pio";
				अवरोध;
			हाल ATAPI_PROT_DMA:
				prot_str = "dma";
				अवरोध;
			पूर्ण
			snम_लिखो(data_buf, माप(data_buf), " %s %u %s",
				 prot_str, qc->nbytes, dma_str[qc->dma_dir]);
		पूर्ण

		अगर (ata_is_atapi(qc->tf.protocol)) अणु
			स्थिर u8 *cdb = qc->cdb;
			माप_प्रकार cdb_len = qc->dev->cdb_len;

			अगर (qc->scsicmd) अणु
				cdb = qc->scsicmd->cmnd;
				cdb_len = qc->scsicmd->cmd_len;
			पूर्ण
			__scsi_क्रमmat_command(cdb_buf, माप(cdb_buf),
					      cdb, cdb_len);
		पूर्ण अन्यथा अणु
			स्थिर अक्षर *descr = ata_get_cmd_descript(cmd->command);
			अगर (descr)
				ata_dev_err(qc->dev, "failed command: %s\n",
					    descr);
		पूर्ण

		ata_dev_err(qc->dev,
			"cmd %02x/%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x/%02x "
			"tag %d%s\n         %s"
			"res %02x/%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x/%02x "
			"Emask 0x%x (%s)%s\n",
			cmd->command, cmd->feature, cmd->nsect,
			cmd->lbal, cmd->lbam, cmd->lbah,
			cmd->hob_feature, cmd->hob_nsect,
			cmd->hob_lbal, cmd->hob_lbam, cmd->hob_lbah,
			cmd->device, qc->tag, data_buf, cdb_buf,
			res->command, res->feature, res->nsect,
			res->lbal, res->lbam, res->lbah,
			res->hob_feature, res->hob_nsect,
			res->hob_lbal, res->hob_lbam, res->hob_lbah,
			res->device, qc->err_mask, ata_err_string(qc->err_mask),
			qc->err_mask & AC_ERR_NCQ ? " <F>" : "");

#अगर_घोषित CONFIG_ATA_VERBOSE_ERROR
		अगर (res->command & (ATA_BUSY | ATA_DRDY | ATA_DF | ATA_DRQ |
				    ATA_SENSE | ATA_ERR)) अणु
			अगर (res->command & ATA_BUSY)
				ata_dev_err(qc->dev, "status: { Busy }\n");
			अन्यथा
				ata_dev_err(qc->dev, "status: { %s%s%s%s%s}\n",
				  res->command & ATA_DRDY ? "DRDY " : "",
				  res->command & ATA_DF ? "DF " : "",
				  res->command & ATA_DRQ ? "DRQ " : "",
				  res->command & ATA_SENSE ? "SENSE " : "",
				  res->command & ATA_ERR ? "ERR " : "");
		पूर्ण

		अगर (cmd->command != ATA_CMD_PACKET &&
		    (res->feature & (ATA_ICRC | ATA_UNC | ATA_AMNF |
				     ATA_IDNF | ATA_ABORTED)))
			ata_dev_err(qc->dev, "error: { %s%s%s%s%s}\n",
			  res->feature & ATA_ICRC ? "ICRC " : "",
			  res->feature & ATA_UNC ? "UNC " : "",
			  res->feature & ATA_AMNF ? "AMNF " : "",
			  res->feature & ATA_IDNF ? "IDNF " : "",
			  res->feature & ATA_ABORTED ? "ABRT " : "");
#पूर्ण_अगर
	पूर्ण
पूर्ण

/**
 *	ata_eh_report - report error handling to user
 *	@ap: ATA port to report EH about
 *
 *	Report EH to user.
 *
 *	LOCKING:
 *	None.
 */
व्योम ata_eh_report(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_link *link;

	ata_क्रम_each_link(link, ap, HOST_FIRST)
		ata_eh_link_report(link);
पूर्ण

अटल पूर्णांक ata_करो_reset(काष्ठा ata_link *link, ata_reset_fn_t reset,
			अचिन्हित पूर्णांक *classes, अचिन्हित दीर्घ deadline,
			bool clear_classes)
अणु
	काष्ठा ata_device *dev;

	अगर (clear_classes)
		ata_क्रम_each_dev(dev, link, ALL)
			classes[dev->devno] = ATA_DEV_UNKNOWN;

	वापस reset(link, classes, deadline);
पूर्ण

अटल पूर्णांक ata_eh_followup_srst_needed(काष्ठा ata_link *link, पूर्णांक rc)
अणु
	अगर ((link->flags & ATA_LFLAG_NO_SRST) || ata_link_offline(link))
		वापस 0;
	अगर (rc == -EAGAIN)
		वापस 1;
	अगर (sata_pmp_supported(link->ap) && ata_is_host_link(link))
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक ata_eh_reset(काष्ठा ata_link *link, पूर्णांक classअगरy,
		 ata_prereset_fn_t prereset, ata_reset_fn_t softreset,
		 ata_reset_fn_t hardreset, ata_postreset_fn_t postreset)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_link *slave = ap->slave_link;
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	काष्ठा ata_eh_context *sehc = slave ? &slave->eh_context : शून्य;
	अचिन्हित पूर्णांक *classes = ehc->classes;
	अचिन्हित पूर्णांक lflags = link->flags;
	पूर्णांक verbose = !(ehc->i.flags & ATA_EHI_QUIET);
	पूर्णांक max_tries = 0, try = 0;
	काष्ठा ata_link *failed_link;
	काष्ठा ata_device *dev;
	अचिन्हित दीर्घ deadline, now;
	ata_reset_fn_t reset;
	अचिन्हित दीर्घ flags;
	u32 sstatus;
	पूर्णांक nr_unknown, rc;

	/*
	 * Prepare to reset
	 */
	जबतक (ata_eh_reset_समयouts[max_tries] != अच_दीर्घ_उच्च)
		max_tries++;
	अगर (link->flags & ATA_LFLAG_RST_ONCE)
		max_tries = 1;
	अगर (link->flags & ATA_LFLAG_NO_HRST)
		hardreset = शून्य;
	अगर (link->flags & ATA_LFLAG_NO_SRST)
		softreset = शून्य;

	/* make sure each reset attempt is at least COOL_DOWN apart */
	अगर (ehc->i.flags & ATA_EHI_DID_RESET) अणु
		now = jअगरfies;
		WARN_ON(समय_after(ehc->last_reset, now));
		deadline = ata_deadline(ehc->last_reset,
					ATA_EH_RESET_COOL_DOWN);
		अगर (समय_beक्रमe(now, deadline))
			schedule_समयout_unपूर्णांकerruptible(deadline - now);
	पूर्ण

	spin_lock_irqsave(ap->lock, flags);
	ap->pflags |= ATA_PFLAG_RESETTING;
	spin_unlock_irqrestore(ap->lock, flags);

	ata_eh_about_to_करो(link, शून्य, ATA_EH_RESET);

	ata_क्रम_each_dev(dev, link, ALL) अणु
		/* If we issue an SRST then an ATA drive (not ATAPI)
		 * may change configuration and be in PIO0 timing. If
		 * we करो a hard reset (or are coming from घातer on)
		 * this is true क्रम ATA or ATAPI. Until we've set a
		 * suitable controller mode we should not touch the
		 * bus as we may be talking too fast.
		 */
		dev->pio_mode = XFER_PIO_0;
		dev->dma_mode = 0xff;

		/* If the controller has a pio mode setup function
		 * then use it to set the chipset to rights. Don't
		 * touch the DMA setup as that will be dealt with when
		 * configuring devices.
		 */
		अगर (ap->ops->set_piomode)
			ap->ops->set_piomode(ap, dev);
	पूर्ण

	/* prefer hardreset */
	reset = शून्य;
	ehc->i.action &= ~ATA_EH_RESET;
	अगर (hardreset) अणु
		reset = hardreset;
		ehc->i.action |= ATA_EH_HARDRESET;
	पूर्ण अन्यथा अगर (softreset) अणु
		reset = softreset;
		ehc->i.action |= ATA_EH_SOFTRESET;
	पूर्ण

	अगर (prereset) अणु
		अचिन्हित दीर्घ deadline = ata_deadline(jअगरfies,
						      ATA_EH_PRERESET_TIMEOUT);

		अगर (slave) अणु
			sehc->i.action &= ~ATA_EH_RESET;
			sehc->i.action |= ehc->i.action;
		पूर्ण

		rc = prereset(link, deadline);

		/* If present, करो prereset on slave link too.  Reset
		 * is skipped अगरf both master and slave links report
		 * -ENOENT or clear ATA_EH_RESET.
		 */
		अगर (slave && (rc == 0 || rc == -ENOENT)) अणु
			पूर्णांक पंचांगp;

			पंचांगp = prereset(slave, deadline);
			अगर (पंचांगp != -ENOENT)
				rc = पंचांगp;

			ehc->i.action |= sehc->i.action;
		पूर्ण

		अगर (rc) अणु
			अगर (rc == -ENOENT) अणु
				ata_link_dbg(link, "port disabled--ignoring\n");
				ehc->i.action &= ~ATA_EH_RESET;

				ata_क्रम_each_dev(dev, link, ALL)
					classes[dev->devno] = ATA_DEV_NONE;

				rc = 0;
			पूर्ण अन्यथा
				ata_link_err(link,
					     "prereset failed (errno=%d)\n",
					     rc);
			जाओ out;
		पूर्ण

		/* prereset() might have cleared ATA_EH_RESET.  If so,
		 * bang classes, thaw and वापस.
		 */
		अगर (reset && !(ehc->i.action & ATA_EH_RESET)) अणु
			ata_क्रम_each_dev(dev, link, ALL)
				classes[dev->devno] = ATA_DEV_NONE;
			अगर ((ap->pflags & ATA_PFLAG_FROZEN) &&
			    ata_is_host_link(link))
				ata_eh_thaw_port(ap);
			rc = 0;
			जाओ out;
		पूर्ण
	पूर्ण

 retry:
	/*
	 * Perक्रमm reset
	 */
	अगर (ata_is_host_link(link))
		ata_eh_मुक्तze_port(ap);

	deadline = ata_deadline(jअगरfies, ata_eh_reset_समयouts[try++]);

	अगर (reset) अणु
		अगर (verbose)
			ata_link_info(link, "%s resetting link\n",
				      reset == softreset ? "soft" : "hard");

		/* mark that this EH session started with reset */
		ehc->last_reset = jअगरfies;
		अगर (reset == hardreset)
			ehc->i.flags |= ATA_EHI_DID_HARDRESET;
		अन्यथा
			ehc->i.flags |= ATA_EHI_DID_SOFTRESET;

		rc = ata_करो_reset(link, reset, classes, deadline, true);
		अगर (rc && rc != -EAGAIN) अणु
			failed_link = link;
			जाओ fail;
		पूर्ण

		/* hardreset slave link अगर existent */
		अगर (slave && reset == hardreset) अणु
			पूर्णांक पंचांगp;

			अगर (verbose)
				ata_link_info(slave, "hard resetting link\n");

			ata_eh_about_to_करो(slave, शून्य, ATA_EH_RESET);
			पंचांगp = ata_करो_reset(slave, reset, classes, deadline,
					   false);
			चयन (पंचांगp) अणु
			हाल -EAGAIN:
				rc = -EAGAIN;
				अवरोध;
			हाल 0:
				अवरोध;
			शेष:
				failed_link = slave;
				rc = पंचांगp;
				जाओ fail;
			पूर्ण
		पूर्ण

		/* perक्रमm follow-up SRST अगर necessary */
		अगर (reset == hardreset &&
		    ata_eh_followup_srst_needed(link, rc)) अणु
			reset = softreset;

			अगर (!reset) अणु
				ata_link_err(link,
	     "follow-up softreset required but no softreset available\n");
				failed_link = link;
				rc = -EINVAL;
				जाओ fail;
			पूर्ण

			ata_eh_about_to_करो(link, शून्य, ATA_EH_RESET);
			rc = ata_करो_reset(link, reset, classes, deadline, true);
			अगर (rc) अणु
				failed_link = link;
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (verbose)
			ata_link_info(link,
	"no reset method available, skipping reset\n");
		अगर (!(lflags & ATA_LFLAG_ASSUME_CLASS))
			lflags |= ATA_LFLAG_ASSUME_ATA;
	पूर्ण

	/*
	 * Post-reset processing
	 */
	ata_क्रम_each_dev(dev, link, ALL) अणु
		/* After the reset, the device state is PIO 0 and the
		 * controller state is undefined.  Reset also wakes up
		 * drives from sleeping mode.
		 */
		dev->pio_mode = XFER_PIO_0;
		dev->flags &= ~ATA_DFLAG_SLEEPING;

		अगर (ata_phys_link_offline(ata_dev_phys_link(dev)))
			जारी;

		/* apply class override */
		अगर (lflags & ATA_LFLAG_ASSUME_ATA)
			classes[dev->devno] = ATA_DEV_ATA;
		अन्यथा अगर (lflags & ATA_LFLAG_ASSUME_SEMB)
			classes[dev->devno] = ATA_DEV_SEMB_UNSUP;
	पूर्ण

	/* record current link speed */
	अगर (sata_scr_पढ़ो(link, SCR_STATUS, &sstatus) == 0)
		link->sata_spd = (sstatus >> 4) & 0xf;
	अगर (slave && sata_scr_पढ़ो(slave, SCR_STATUS, &sstatus) == 0)
		slave->sata_spd = (sstatus >> 4) & 0xf;

	/* thaw the port */
	अगर (ata_is_host_link(link))
		ata_eh_thaw_port(ap);

	/* postreset() should clear hardware SError.  Although SError
	 * is cleared during link resume, clearing SError here is
	 * necessary as some PHYs उठाओ hotplug events after SRST.
	 * This पूर्णांकroduces race condition where hotplug occurs between
	 * reset and here.  This race is mediated by cross checking
	 * link onlineness and classअगरication result later.
	 */
	अगर (postreset) अणु
		postreset(link, classes);
		अगर (slave)
			postreset(slave, classes);
	पूर्ण

	/*
	 * Some controllers can't be frozen very well and may set spurious
	 * error conditions during reset.  Clear accumulated error
	 * inक्रमmation and re-thaw the port अगर frozen.  As reset is the
	 * final recovery action and we cross check link onlineness against
	 * device classअगरication later, no hotplug event is lost by this.
	 */
	spin_lock_irqsave(link->ap->lock, flags);
	स_रखो(&link->eh_info, 0, माप(link->eh_info));
	अगर (slave)
		स_रखो(&slave->eh_info, 0, माप(link->eh_info));
	ap->pflags &= ~ATA_PFLAG_EH_PENDING;
	spin_unlock_irqrestore(link->ap->lock, flags);

	अगर (ap->pflags & ATA_PFLAG_FROZEN)
		ata_eh_thaw_port(ap);

	/*
	 * Make sure onlineness and classअगरication result correspond.
	 * Hotplug could have happened during reset and some
	 * controllers fail to रुको जबतक a drive is spinning up after
	 * being hotplugged causing misdetection.  By cross checking
	 * link on/offlineness and classअगरication result, those
	 * conditions can be reliably detected and retried.
	 */
	nr_unknown = 0;
	ata_क्रम_each_dev(dev, link, ALL) अणु
		अगर (ata_phys_link_online(ata_dev_phys_link(dev))) अणु
			अगर (classes[dev->devno] == ATA_DEV_UNKNOWN) अणु
				ata_dev_dbg(dev, "link online but device misclassified\n");
				classes[dev->devno] = ATA_DEV_NONE;
				nr_unknown++;
			पूर्ण
		पूर्ण अन्यथा अगर (ata_phys_link_offline(ata_dev_phys_link(dev))) अणु
			अगर (ata_class_enabled(classes[dev->devno]))
				ata_dev_dbg(dev,
					    "link offline, clearing class %d to NONE\n",
					    classes[dev->devno]);
			classes[dev->devno] = ATA_DEV_NONE;
		पूर्ण अन्यथा अगर (classes[dev->devno] == ATA_DEV_UNKNOWN) अणु
			ata_dev_dbg(dev,
				    "link status unknown, clearing UNKNOWN to NONE\n");
			classes[dev->devno] = ATA_DEV_NONE;
		पूर्ण
	पूर्ण

	अगर (classअगरy && nr_unknown) अणु
		अगर (try < max_tries) अणु
			ata_link_warn(link,
				      "link online but %d devices misclassified, retrying\n",
				      nr_unknown);
			failed_link = link;
			rc = -EAGAIN;
			जाओ fail;
		पूर्ण
		ata_link_warn(link,
			      "link online but %d devices misclassified, "
			      "device detection might fail\n", nr_unknown);
	पूर्ण

	/* reset successful, schedule revalidation */
	ata_eh_करोne(link, शून्य, ATA_EH_RESET);
	अगर (slave)
		ata_eh_करोne(slave, शून्य, ATA_EH_RESET);
	ehc->last_reset = jअगरfies;		/* update to completion समय */
	ehc->i.action |= ATA_EH_REVALIDATE;
	link->lpm_policy = ATA_LPM_UNKNOWN;	/* reset LPM state */

	rc = 0;
 out:
	/* clear hotplug flag */
	ehc->i.flags &= ~ATA_EHI_HOTPLUGGED;
	अगर (slave)
		sehc->i.flags &= ~ATA_EHI_HOTPLUGGED;

	spin_lock_irqsave(ap->lock, flags);
	ap->pflags &= ~ATA_PFLAG_RESETTING;
	spin_unlock_irqrestore(ap->lock, flags);

	वापस rc;

 fail:
	/* अगर SCR isn't accessible on a fan-out port, PMP needs to be reset */
	अगर (!ata_is_host_link(link) &&
	    sata_scr_पढ़ो(link, SCR_STATUS, &sstatus))
		rc = -ERESTART;

	अगर (try >= max_tries) अणु
		/*
		 * Thaw host port even अगर reset failed, so that the port
		 * can be retried on the next phy event.  This risks
		 * repeated EH runs but seems to be a better tradeoff than
		 * shutting करोwn a port after a botched hotplug attempt.
		 */
		अगर (ata_is_host_link(link))
			ata_eh_thaw_port(ap);
		जाओ out;
	पूर्ण

	now = jअगरfies;
	अगर (समय_beक्रमe(now, deadline)) अणु
		अचिन्हित दीर्घ delta = deadline - now;

		ata_link_warn(failed_link,
			"reset failed (errno=%d), retrying in %u secs\n",
			rc, DIV_ROUND_UP(jअगरfies_to_msecs(delta), 1000));

		ata_eh_release(ap);
		जबतक (delta)
			delta = schedule_समयout_unपूर्णांकerruptible(delta);
		ata_eh_acquire(ap);
	पूर्ण

	/*
	 * While disks spinup behind PMP, some controllers fail sending SRST.
	 * They need to be reset - as well as the PMP - beक्रमe retrying.
	 */
	अगर (rc == -ERESTART) अणु
		अगर (ata_is_host_link(link))
			ata_eh_thaw_port(ap);
		जाओ out;
	पूर्ण

	अगर (try == max_tries - 1) अणु
		sata_करोwn_spd_limit(link, 0);
		अगर (slave)
			sata_करोwn_spd_limit(slave, 0);
	पूर्ण अन्यथा अगर (rc == -EPIPE)
		sata_करोwn_spd_limit(failed_link, 0);

	अगर (hardreset)
		reset = hardreset;
	जाओ retry;
पूर्ण

अटल अंतरभूत व्योम ata_eh_pull_park_action(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_link *link;
	काष्ठा ata_device *dev;
	अचिन्हित दीर्घ flags;

	/*
	 * This function can be thought of as an extended version of
	 * ata_eh_about_to_करो() specially crafted to accommodate the
	 * requirements of ATA_EH_PARK handling. Since the EH thपढ़ो
	 * करोes not leave the करो अणुपूर्ण जबतक () loop in ata_eh_recover as
	 * दीर्घ as the समयout क्रम a park request to *one* device on
	 * the port has not expired, and since we still want to pick
	 * up park requests to other devices on the same port or
	 * समयout updates क्रम the same device, we have to pull
	 * ATA_EH_PARK actions from eh_info पूर्णांकo eh_context.i
	 * ourselves at the beginning of each pass over the loop.
	 *
	 * Additionally, all ग_लिखो accesses to &ap->park_req_pending
	 * through reinit_completion() (see below) or complete_all()
	 * (see ata_scsi_park_store()) are रक्षित by the host lock.
	 * As a result we have that park_req_pending.करोne is zero on
	 * निकास from this function, i.e. when ATA_EH_PARK actions क्रम
	 * *all* devices on port ap have been pulled पूर्णांकo the
	 * respective eh_context काष्ठाs. If, and only अगर,
	 * park_req_pending.करोne is non-zero by the समय we reach
	 * रुको_क्रम_completion_समयout(), another ATA_EH_PARK action
	 * has been scheduled क्रम at least one of the devices on port
	 * ap and we have to cycle over the करो अणुपूर्ण जबतक () loop in
	 * ata_eh_recover() again.
	 */

	spin_lock_irqsave(ap->lock, flags);
	reinit_completion(&ap->park_req_pending);
	ata_क्रम_each_link(link, ap, EDGE) अणु
		ata_क्रम_each_dev(dev, link, ALL) अणु
			काष्ठा ata_eh_info *ehi = &link->eh_info;

			link->eh_context.i.dev_action[dev->devno] |=
				ehi->dev_action[dev->devno] & ATA_EH_PARK;
			ata_eh_clear_action(link, dev, ehi, ATA_EH_PARK);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(ap->lock, flags);
पूर्ण

अटल व्योम ata_eh_park_issue_cmd(काष्ठा ata_device *dev, पूर्णांक park)
अणु
	काष्ठा ata_eh_context *ehc = &dev->link->eh_context;
	काष्ठा ata_taskfile tf;
	अचिन्हित पूर्णांक err_mask;

	ata_tf_init(dev, &tf);
	अगर (park) अणु
		ehc->unloaded_mask |= 1 << dev->devno;
		tf.command = ATA_CMD_IDLEIMMEDIATE;
		tf.feature = 0x44;
		tf.lbal = 0x4c;
		tf.lbam = 0x4e;
		tf.lbah = 0x55;
	पूर्ण अन्यथा अणु
		ehc->unloaded_mask &= ~(1 << dev->devno);
		tf.command = ATA_CMD_CHK_POWER;
	पूर्ण

	tf.flags |= ATA_TFLAG_DEVICE | ATA_TFLAG_ISADDR;
	tf.protocol = ATA_PROT_NODATA;
	err_mask = ata_exec_पूर्णांकernal(dev, &tf, शून्य, DMA_NONE, शून्य, 0, 0);
	अगर (park && (err_mask || tf.lbal != 0xc4)) अणु
		ata_dev_err(dev, "head unload failed!\n");
		ehc->unloaded_mask &= ~(1 << dev->devno);
	पूर्ण
पूर्ण

अटल पूर्णांक ata_eh_revalidate_and_attach(काष्ठा ata_link *link,
					काष्ठा ata_device **r_failed_dev)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	काष्ठा ata_device *dev;
	अचिन्हित पूर्णांक new_mask = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	DPRINTK("ENTER\n");

	/* For PATA drive side cable detection to work, IDENTIFY must
	 * be करोne backwards such that PDIAG- is released by the slave
	 * device beक्रमe the master device is identअगरied.
	 */
	ata_क्रम_each_dev(dev, link, ALL_REVERSE) अणु
		अचिन्हित पूर्णांक action = ata_eh_dev_action(dev);
		अचिन्हित पूर्णांक पढ़ोid_flags = 0;

		अगर (ehc->i.flags & ATA_EHI_DID_RESET)
			पढ़ोid_flags |= ATA_READID_POSTRESET;

		अगर ((action & ATA_EH_REVALIDATE) && ata_dev_enabled(dev)) अणु
			WARN_ON(dev->class == ATA_DEV_PMP);

			अगर (ata_phys_link_offline(ata_dev_phys_link(dev))) अणु
				rc = -EIO;
				जाओ err;
			पूर्ण

			ata_eh_about_to_करो(link, dev, ATA_EH_REVALIDATE);
			rc = ata_dev_revalidate(dev, ehc->classes[dev->devno],
						पढ़ोid_flags);
			अगर (rc)
				जाओ err;

			ata_eh_करोne(link, dev, ATA_EH_REVALIDATE);

			/* Configuration may have changed, reconfigure
			 * transfer mode.
			 */
			ehc->i.flags |= ATA_EHI_SETMODE;

			/* schedule the scsi_rescan_device() here */
			schedule_work(&(ap->scsi_rescan_task));
		पूर्ण अन्यथा अगर (dev->class == ATA_DEV_UNKNOWN &&
			   ehc->tries[dev->devno] &&
			   ata_class_enabled(ehc->classes[dev->devno])) अणु
			/* Temporarily set dev->class, it will be
			 * permanently set once all configurations are
			 * complete.  This is necessary because new
			 * device configuration is करोne in two
			 * separate loops.
			 */
			dev->class = ehc->classes[dev->devno];

			अगर (dev->class == ATA_DEV_PMP)
				rc = sata_pmp_attach(dev);
			अन्यथा
				rc = ata_dev_पढ़ो_id(dev, &dev->class,
						     पढ़ोid_flags, dev->id);

			/* पढ़ो_id might have changed class, store and reset */
			ehc->classes[dev->devno] = dev->class;
			dev->class = ATA_DEV_UNKNOWN;

			चयन (rc) अणु
			हाल 0:
				/* clear error info accumulated during probe */
				ata_ering_clear(&dev->ering);
				new_mask |= 1 << dev->devno;
				अवरोध;
			हाल -ENOENT:
				/* IDENTIFY was issued to non-existent
				 * device.  No need to reset.  Just
				 * thaw and ignore the device.
				 */
				ata_eh_thaw_port(ap);
				अवरोध;
			शेष:
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	/* PDIAG- should have been released, ask cable type अगर post-reset */
	अगर ((ehc->i.flags & ATA_EHI_DID_RESET) && ata_is_host_link(link)) अणु
		अगर (ap->ops->cable_detect)
			ap->cbl = ap->ops->cable_detect(ap);
		ata_क्रमce_cbl(ap);
	पूर्ण

	/* Configure new devices क्रमward such that user करोesn't see
	 * device detection messages backwards.
	 */
	ata_क्रम_each_dev(dev, link, ALL) अणु
		अगर (!(new_mask & (1 << dev->devno)))
			जारी;

		dev->class = ehc->classes[dev->devno];

		अगर (dev->class == ATA_DEV_PMP)
			जारी;

		ehc->i.flags |= ATA_EHI_PRINTINFO;
		rc = ata_dev_configure(dev);
		ehc->i.flags &= ~ATA_EHI_PRINTINFO;
		अगर (rc) अणु
			dev->class = ATA_DEV_UNKNOWN;
			जाओ err;
		पूर्ण

		spin_lock_irqsave(ap->lock, flags);
		ap->pflags |= ATA_PFLAG_SCSI_HOTPLUG;
		spin_unlock_irqrestore(ap->lock, flags);

		/* new device discovered, configure xfermode */
		ehc->i.flags |= ATA_EHI_SETMODE;
	पूर्ण

	वापस 0;

 err:
	*r_failed_dev = dev;
	DPRINTK("EXIT rc=%d\n", rc);
	वापस rc;
पूर्ण

/**
 *	ata_set_mode - Program timings and issue SET FEATURES - XFER
 *	@link: link on which timings will be programmed
 *	@r_failed_dev: out parameter क्रम failed device
 *
 *	Set ATA device disk transfer mode (PIO3, UDMA6, etc.).  If
 *	ata_set_mode() fails, poपूर्णांकer to the failing device is
 *	वापसed in @r_failed_dev.
 *
 *	LOCKING:
 *	PCI/etc. bus probe sem.
 *
 *	RETURNS:
 *	0 on success, negative त्रुटि_सं otherwise
 */
पूर्णांक ata_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **r_failed_dev)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_device *dev;
	पूर्णांक rc;

	/* अगर data transfer is verअगरied, clear DUBIOUS_XFER on ering top */
	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		अगर (!(dev->flags & ATA_DFLAG_DUBIOUS_XFER)) अणु
			काष्ठा ata_ering_entry *ent;

			ent = ata_ering_top(&dev->ering);
			अगर (ent)
				ent->eflags &= ~ATA_EFLAG_DUBIOUS_XFER;
		पूर्ण
	पूर्ण

	/* has निजी set_mode? */
	अगर (ap->ops->set_mode)
		rc = ap->ops->set_mode(link, r_failed_dev);
	अन्यथा
		rc = ata_करो_set_mode(link, r_failed_dev);

	/* अगर transfer mode has changed, set DUBIOUS_XFER on device */
	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		काष्ठा ata_eh_context *ehc = &link->eh_context;
		u8 saved_xfer_mode = ehc->saved_xfer_mode[dev->devno];
		u8 saved_ncq = !!(ehc->saved_ncq_enabled & (1 << dev->devno));

		अगर (dev->xfer_mode != saved_xfer_mode ||
		    ata_ncq_enabled(dev) != saved_ncq)
			dev->flags |= ATA_DFLAG_DUBIOUS_XFER;
	पूर्ण

	वापस rc;
पूर्ण

/**
 *	atapi_eh_clear_ua - Clear ATAPI UNIT ATTENTION after reset
 *	@dev: ATAPI device to clear UA क्रम
 *
 *	Resets and other operations can make an ATAPI device उठाओ
 *	UNIT ATTENTION which causes the next operation to fail.  This
 *	function clears UA.
 *
 *	LOCKING:
 *	EH context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक atapi_eh_clear_ua(काष्ठा ata_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ATA_EH_UA_TRIES; i++) अणु
		u8 *sense_buffer = dev->link->ap->sector_buf;
		u8 sense_key = 0;
		अचिन्हित पूर्णांक err_mask;

		err_mask = atapi_eh_tur(dev, &sense_key);
		अगर (err_mask != 0 && err_mask != AC_ERR_DEV) अणु
			ata_dev_warn(dev,
				     "TEST_UNIT_READY failed (err_mask=0x%x)\n",
				     err_mask);
			वापस -EIO;
		पूर्ण

		अगर (!err_mask || sense_key != UNIT_ATTENTION)
			वापस 0;

		err_mask = atapi_eh_request_sense(dev, sense_buffer, sense_key);
		अगर (err_mask) अणु
			ata_dev_warn(dev, "failed to clear "
				"UNIT ATTENTION (err_mask=0x%x)\n", err_mask);
			वापस -EIO;
		पूर्ण
	पूर्ण

	ata_dev_warn(dev, "UNIT ATTENTION persists after %d tries\n",
		     ATA_EH_UA_TRIES);

	वापस 0;
पूर्ण

/**
 *	ata_eh_maybe_retry_flush - Retry FLUSH अगर necessary
 *	@dev: ATA device which may need FLUSH retry
 *
 *	If @dev failed FLUSH, it needs to be reported upper layer
 *	immediately as it means that @dev failed to remap and alपढ़ोy
 *	lost at least a sector and further FLUSH retrials won't make
 *	any dअगरference to the lost sector.  However, अगर FLUSH failed
 *	क्रम other reasons, क्रम example transmission error, FLUSH needs
 *	to be retried.
 *
 *	This function determines whether FLUSH failure retry is
 *	necessary and perक्रमms it अगर so.
 *
 *	RETURNS:
 *	0 अगर EH can जारी, -त्रुटि_सं अगर EH needs to be repeated.
 */
अटल पूर्णांक ata_eh_maybe_retry_flush(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_link *link = dev->link;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_queued_cmd *qc;
	काष्ठा ata_taskfile tf;
	अचिन्हित पूर्णांक err_mask;
	पूर्णांक rc = 0;

	/* did flush fail क्रम this device? */
	अगर (!ata_tag_valid(link->active_tag))
		वापस 0;

	qc = __ata_qc_from_tag(ap, link->active_tag);
	अगर (qc->dev != dev || (qc->tf.command != ATA_CMD_FLUSH_EXT &&
			       qc->tf.command != ATA_CMD_FLUSH))
		वापस 0;

	/* अगर the device failed it, it should be reported to upper layers */
	अगर (qc->err_mask & AC_ERR_DEV)
		वापस 0;

	/* flush failed क्रम some other reason, give it another shot */
	ata_tf_init(dev, &tf);

	tf.command = qc->tf.command;
	tf.flags |= ATA_TFLAG_DEVICE;
	tf.protocol = ATA_PROT_NODATA;

	ata_dev_warn(dev, "retrying FLUSH 0x%x Emask 0x%x\n",
		       tf.command, qc->err_mask);

	err_mask = ata_exec_पूर्णांकernal(dev, &tf, शून्य, DMA_NONE, शून्य, 0, 0);
	अगर (!err_mask) अणु
		/*
		 * FLUSH is complete but there's no way to
		 * successfully complete a failed command from EH.
		 * Making sure retry is allowed at least once and
		 * retrying it should करो the trick - whatever was in
		 * the cache is alपढ़ोy on the platter and this won't
		 * cause infinite loop.
		 */
		qc->scsicmd->allowed = max(qc->scsicmd->allowed, 1);
	पूर्ण अन्यथा अणु
		ata_dev_warn(dev, "FLUSH failed Emask 0x%x\n",
			       err_mask);
		rc = -EIO;

		/* अगर device failed it, report it to upper layers */
		अगर (err_mask & AC_ERR_DEV) अणु
			qc->err_mask |= AC_ERR_DEV;
			qc->result_tf = tf;
			अगर (!(ap->pflags & ATA_PFLAG_FROZEN))
				rc = 0;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

/**
 *	ata_eh_set_lpm - configure SATA पूर्णांकerface घातer management
 *	@link: link to configure घातer management
 *	@policy: the link घातer management policy
 *	@r_failed_dev: out parameter क्रम failed device
 *
 *	Enable SATA Interface घातer management.  This will enable
 *	Device Interface Power Management (DIPM) क्रम min_घातer and
 *	medium_घातer_with_dipm policies, and then call driver specअगरic
 *	callbacks क्रम enabling Host Initiated Power management.
 *
 *	LOCKING:
 *	EH context.
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक ata_eh_set_lpm(काष्ठा ata_link *link, क्रमागत ata_lpm_policy policy,
			  काष्ठा ata_device **r_failed_dev)
अणु
	काष्ठा ata_port *ap = ata_is_host_link(link) ? link->ap : शून्य;
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	काष्ठा ata_device *dev, *link_dev = शून्य, *lpm_dev = शून्य;
	क्रमागत ata_lpm_policy old_policy = link->lpm_policy;
	bool no_dipm = link->ap->flags & ATA_FLAG_NO_DIPM;
	अचिन्हित पूर्णांक hपूर्णांकs = ATA_LPM_EMPTY | ATA_LPM_HIPM;
	अचिन्हित पूर्णांक err_mask;
	पूर्णांक rc;

	/* अगर the link or host करोesn't करो LPM, noop */
	अगर (!IS_ENABLED(CONFIG_SATA_HOST) ||
	    (link->flags & ATA_LFLAG_NO_LPM) || (ap && !ap->ops->set_lpm))
		वापस 0;

	/*
	 * DIPM is enabled only क्रम MIN_POWER as some devices
	 * misbehave when the host NACKs transition to SLUMBER.  Order
	 * device and link configurations such that the host always
	 * allows DIPM requests.
	 */
	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		bool hipm = ata_id_has_hipm(dev->id);
		bool dipm = ata_id_has_dipm(dev->id) && !no_dipm;

		/* find the first enabled and LPM enabled devices */
		अगर (!link_dev)
			link_dev = dev;

		अगर (!lpm_dev && (hipm || dipm))
			lpm_dev = dev;

		hपूर्णांकs &= ~ATA_LPM_EMPTY;
		अगर (!hipm)
			hपूर्णांकs &= ~ATA_LPM_HIPM;

		/* disable DIPM beक्रमe changing link config */
		अगर (policy < ATA_LPM_MED_POWER_WITH_DIPM && dipm) अणु
			err_mask = ata_dev_set_feature(dev,
					SETFEATURES_SATA_DISABLE, SATA_DIPM);
			अगर (err_mask && err_mask != AC_ERR_DEV) अणु
				ata_dev_warn(dev,
					     "failed to disable DIPM, Emask 0x%x\n",
					     err_mask);
				rc = -EIO;
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ap) अणु
		rc = ap->ops->set_lpm(link, policy, hपूर्णांकs);
		अगर (!rc && ap->slave_link)
			rc = ap->ops->set_lpm(ap->slave_link, policy, hपूर्णांकs);
	पूर्ण अन्यथा
		rc = sata_pmp_set_lpm(link, policy, hपूर्णांकs);

	/*
	 * Attribute link config failure to the first (LPM) enabled
	 * device on the link.
	 */
	अगर (rc) अणु
		अगर (rc == -EOPNOTSUPP) अणु
			link->flags |= ATA_LFLAG_NO_LPM;
			वापस 0;
		पूर्ण
		dev = lpm_dev ? lpm_dev : link_dev;
		जाओ fail;
	पूर्ण

	/*
	 * Low level driver acked the transition.  Issue DIPM command
	 * with the new policy set.
	 */
	link->lpm_policy = policy;
	अगर (ap && ap->slave_link)
		ap->slave_link->lpm_policy = policy;

	/* host config updated, enable DIPM अगर transitioning to MIN_POWER */
	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		अगर (policy >= ATA_LPM_MED_POWER_WITH_DIPM && !no_dipm &&
		    ata_id_has_dipm(dev->id)) अणु
			err_mask = ata_dev_set_feature(dev,
					SETFEATURES_SATA_ENABLE, SATA_DIPM);
			अगर (err_mask && err_mask != AC_ERR_DEV) अणु
				ata_dev_warn(dev,
					"failed to enable DIPM, Emask 0x%x\n",
					err_mask);
				rc = -EIO;
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

	link->last_lpm_change = jअगरfies;
	link->flags |= ATA_LFLAG_CHANGED;

	वापस 0;

fail:
	/* restore the old policy */
	link->lpm_policy = old_policy;
	अगर (ap && ap->slave_link)
		ap->slave_link->lpm_policy = old_policy;

	/* अगर no device or only one more chance is left, disable LPM */
	अगर (!dev || ehc->tries[dev->devno] <= 2) अणु
		ata_link_warn(link, "disabling LPM on the link\n");
		link->flags |= ATA_LFLAG_NO_LPM;
	पूर्ण
	अगर (r_failed_dev)
		*r_failed_dev = dev;
	वापस rc;
पूर्ण

पूर्णांक ata_link_nr_enabled(काष्ठा ata_link *link)
अणु
	काष्ठा ata_device *dev;
	पूर्णांक cnt = 0;

	ata_क्रम_each_dev(dev, link, ENABLED)
		cnt++;
	वापस cnt;
पूर्ण

अटल पूर्णांक ata_link_nr_vacant(काष्ठा ata_link *link)
अणु
	काष्ठा ata_device *dev;
	पूर्णांक cnt = 0;

	ata_क्रम_each_dev(dev, link, ALL)
		अगर (dev->class == ATA_DEV_UNKNOWN)
			cnt++;
	वापस cnt;
पूर्ण

अटल पूर्णांक ata_eh_skip_recovery(काष्ठा ata_link *link)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	काष्ठा ata_device *dev;

	/* skip disabled links */
	अगर (link->flags & ATA_LFLAG_DISABLED)
		वापस 1;

	/* skip अगर explicitly requested */
	अगर (ehc->i.flags & ATA_EHI_NO_RECOVERY)
		वापस 1;

	/* thaw frozen port and recover failed devices */
	अगर ((ap->pflags & ATA_PFLAG_FROZEN) || ata_link_nr_enabled(link))
		वापस 0;

	/* reset at least once अगर reset is requested */
	अगर ((ehc->i.action & ATA_EH_RESET) &&
	    !(ehc->i.flags & ATA_EHI_DID_RESET))
		वापस 0;

	/* skip अगर class codes क्रम all vacant slots are ATA_DEV_NONE */
	ata_क्रम_each_dev(dev, link, ALL) अणु
		अगर (dev->class == ATA_DEV_UNKNOWN &&
		    ehc->classes[dev->devno] != ATA_DEV_NONE)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक ata_count_probe_trials_cb(काष्ठा ata_ering_entry *ent, व्योम *व्योम_arg)
अणु
	u64 पूर्णांकerval = msecs_to_jअगरfies(ATA_EH_PROBE_TRIAL_INTERVAL);
	u64 now = get_jअगरfies_64();
	पूर्णांक *trials = व्योम_arg;

	अगर ((ent->eflags & ATA_EFLAG_OLD_ER) ||
	    (ent->बारtamp < now - min(now, पूर्णांकerval)))
		वापस -1;

	(*trials)++;
	वापस 0;
पूर्ण

अटल पूर्णांक ata_eh_schedule_probe(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_eh_context *ehc = &dev->link->eh_context;
	काष्ठा ata_link *link = ata_dev_phys_link(dev);
	पूर्णांक trials = 0;

	अगर (!(ehc->i.probe_mask & (1 << dev->devno)) ||
	    (ehc->did_probe_mask & (1 << dev->devno)))
		वापस 0;

	ata_eh_detach_dev(dev);
	ata_dev_init(dev);
	ehc->did_probe_mask |= (1 << dev->devno);
	ehc->i.action |= ATA_EH_RESET;
	ehc->saved_xfer_mode[dev->devno] = 0;
	ehc->saved_ncq_enabled &= ~(1 << dev->devno);

	/* the link maybe in a deep sleep, wake it up */
	अगर (link->lpm_policy > ATA_LPM_MAX_POWER) अणु
		अगर (ata_is_host_link(link))
			link->ap->ops->set_lpm(link, ATA_LPM_MAX_POWER,
					       ATA_LPM_EMPTY);
		अन्यथा
			sata_pmp_set_lpm(link, ATA_LPM_MAX_POWER,
					 ATA_LPM_EMPTY);
	पूर्ण

	/* Record and count probe trials on the ering.  The specअगरic
	 * error mask used is irrelevant.  Because a successful device
	 * detection clears the ering, this count accumulates only अगर
	 * there are consecutive failed probes.
	 *
	 * If the count is equal to or higher than ATA_EH_PROBE_TRIALS
	 * in the last ATA_EH_PROBE_TRIAL_INTERVAL, link speed is
	 * क्रमced to 1.5Gbps.
	 *
	 * This is to work around हालs where failed link speed
	 * negotiation results in device misdetection leading to
	 * infinite DEVXCHG or PHRDY CHG events.
	 */
	ata_ering_record(&dev->ering, 0, AC_ERR_OTHER);
	ata_ering_map(&dev->ering, ata_count_probe_trials_cb, &trials);

	अगर (trials > ATA_EH_PROBE_TRIALS)
		sata_करोwn_spd_limit(link, 1);

	वापस 1;
पूर्ण

अटल पूर्णांक ata_eh_handle_dev_fail(काष्ठा ata_device *dev, पूर्णांक err)
अणु
	काष्ठा ata_eh_context *ehc = &dev->link->eh_context;

	/* -EAGAIN from EH routine indicates retry without prejudice.
	 * The requester is responsible क्रम ensuring क्रमward progress.
	 */
	अगर (err != -EAGAIN)
		ehc->tries[dev->devno]--;

	चयन (err) अणु
	हाल -ENODEV:
		/* device missing or wrong IDENTIFY data, schedule probing */
		ehc->i.probe_mask |= (1 << dev->devno);
		fallthrough;
	हाल -EINVAL:
		/* give it just one more chance */
		ehc->tries[dev->devno] = min(ehc->tries[dev->devno], 1);
		fallthrough;
	हाल -EIO:
		अगर (ehc->tries[dev->devno] == 1) अणु
			/* This is the last chance, better to slow
			 * करोwn than lose it.
			 */
			sata_करोwn_spd_limit(ata_dev_phys_link(dev), 0);
			अगर (dev->pio_mode > XFER_PIO_0)
				ata_करोwn_xfermask_limit(dev, ATA_DNXFER_PIO);
		पूर्ण
	पूर्ण

	अगर (ata_dev_enabled(dev) && !ehc->tries[dev->devno]) अणु
		/* disable device अगर it has used up all its chances */
		ata_dev_disable(dev);

		/* detach अगर offline */
		अगर (ata_phys_link_offline(ata_dev_phys_link(dev)))
			ata_eh_detach_dev(dev);

		/* schedule probe अगर necessary */
		अगर (ata_eh_schedule_probe(dev)) अणु
			ehc->tries[dev->devno] = ATA_EH_DEV_TRIES;
			स_रखो(ehc->cmd_समयout_idx[dev->devno], 0,
			       माप(ehc->cmd_समयout_idx[dev->devno]));
		पूर्ण

		वापस 1;
	पूर्ण अन्यथा अणु
		ehc->i.action |= ATA_EH_RESET;
		वापस 0;
	पूर्ण
पूर्ण

/**
 *	ata_eh_recover - recover host port after error
 *	@ap: host port to recover
 *	@prereset: prereset method (can be शून्य)
 *	@softreset: softreset method (can be शून्य)
 *	@hardreset: hardreset method (can be शून्य)
 *	@postreset: postreset method (can be शून्य)
 *	@r_failed_link: out parameter क्रम failed link
 *
 *	This is the alpha and omega, eum and yang, heart and soul of
 *	libata exception handling.  On entry, actions required to
 *	recover each link and hotplug requests are recorded in the
 *	link's eh_context.  This function executes all the operations
 *	with appropriate retrials and fallbacks to resurrect failed
 *	devices, detach goners and greet newcomers.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक ata_eh_recover(काष्ठा ata_port *ap, ata_prereset_fn_t prereset,
		   ata_reset_fn_t softreset, ata_reset_fn_t hardreset,
		   ata_postreset_fn_t postreset,
		   काष्ठा ata_link **r_failed_link)
अणु
	काष्ठा ata_link *link;
	काष्ठा ata_device *dev;
	पूर्णांक rc, nr_fails;
	अचिन्हित दीर्घ flags, deadline;

	DPRINTK("ENTER\n");

	/* prep क्रम recovery */
	ata_क्रम_each_link(link, ap, EDGE) अणु
		काष्ठा ata_eh_context *ehc = &link->eh_context;

		/* re-enable link? */
		अगर (ehc->i.action & ATA_EH_ENABLE_LINK) अणु
			ata_eh_about_to_करो(link, शून्य, ATA_EH_ENABLE_LINK);
			spin_lock_irqsave(ap->lock, flags);
			link->flags &= ~ATA_LFLAG_DISABLED;
			spin_unlock_irqrestore(ap->lock, flags);
			ata_eh_करोne(link, शून्य, ATA_EH_ENABLE_LINK);
		पूर्ण

		ata_क्रम_each_dev(dev, link, ALL) अणु
			अगर (link->flags & ATA_LFLAG_NO_RETRY)
				ehc->tries[dev->devno] = 1;
			अन्यथा
				ehc->tries[dev->devno] = ATA_EH_DEV_TRIES;

			/* collect port action mask recorded in dev actions */
			ehc->i.action |= ehc->i.dev_action[dev->devno] &
					 ~ATA_EH_PERDEV_MASK;
			ehc->i.dev_action[dev->devno] &= ATA_EH_PERDEV_MASK;

			/* process hotplug request */
			अगर (dev->flags & ATA_DFLAG_DETACH)
				ata_eh_detach_dev(dev);

			/* schedule probe अगर necessary */
			अगर (!ata_dev_enabled(dev))
				ata_eh_schedule_probe(dev);
		पूर्ण
	पूर्ण

 retry:
	rc = 0;

	/* अगर UNLOADING, finish immediately */
	अगर (ap->pflags & ATA_PFLAG_UNLOADING)
		जाओ out;

	/* prep क्रम EH */
	ata_क्रम_each_link(link, ap, EDGE) अणु
		काष्ठा ata_eh_context *ehc = &link->eh_context;

		/* skip EH अगर possible. */
		अगर (ata_eh_skip_recovery(link))
			ehc->i.action = 0;

		ata_क्रम_each_dev(dev, link, ALL)
			ehc->classes[dev->devno] = ATA_DEV_UNKNOWN;
	पूर्ण

	/* reset */
	ata_क्रम_each_link(link, ap, EDGE) अणु
		काष्ठा ata_eh_context *ehc = &link->eh_context;

		अगर (!(ehc->i.action & ATA_EH_RESET))
			जारी;

		rc = ata_eh_reset(link, ata_link_nr_vacant(link),
				  prereset, softreset, hardreset, postreset);
		अगर (rc) अणु
			ata_link_err(link, "reset failed, giving up\n");
			जाओ out;
		पूर्ण
	पूर्ण

	करो अणु
		अचिन्हित दीर्घ now;

		/*
		 * clears ATA_EH_PARK in eh_info and resets
		 * ap->park_req_pending
		 */
		ata_eh_pull_park_action(ap);

		deadline = jअगरfies;
		ata_क्रम_each_link(link, ap, EDGE) अणु
			ata_क्रम_each_dev(dev, link, ALL) अणु
				काष्ठा ata_eh_context *ehc = &link->eh_context;
				अचिन्हित दीर्घ पंचांगp;

				अगर (dev->class != ATA_DEV_ATA &&
				    dev->class != ATA_DEV_ZAC)
					जारी;
				अगर (!(ehc->i.dev_action[dev->devno] &
				      ATA_EH_PARK))
					जारी;
				पंचांगp = dev->unpark_deadline;
				अगर (समय_beक्रमe(deadline, पंचांगp))
					deadline = पंचांगp;
				अन्यथा अगर (समय_beक्रमe_eq(पंचांगp, jअगरfies))
					जारी;
				अगर (ehc->unloaded_mask & (1 << dev->devno))
					जारी;

				ata_eh_park_issue_cmd(dev, 1);
			पूर्ण
		पूर्ण

		now = jअगरfies;
		अगर (समय_beक्रमe_eq(deadline, now))
			अवरोध;

		ata_eh_release(ap);
		deadline = रुको_क्रम_completion_समयout(&ap->park_req_pending,
						       deadline - now);
		ata_eh_acquire(ap);
	पूर्ण जबतक (deadline);
	ata_क्रम_each_link(link, ap, EDGE) अणु
		ata_क्रम_each_dev(dev, link, ALL) अणु
			अगर (!(link->eh_context.unloaded_mask &
			      (1 << dev->devno)))
				जारी;

			ata_eh_park_issue_cmd(dev, 0);
			ata_eh_करोne(link, dev, ATA_EH_PARK);
		पूर्ण
	पूर्ण

	/* the rest */
	nr_fails = 0;
	ata_क्रम_each_link(link, ap, PMP_FIRST) अणु
		काष्ठा ata_eh_context *ehc = &link->eh_context;

		अगर (sata_pmp_attached(ap) && ata_is_host_link(link))
			जाओ config_lpm;

		/* revalidate existing devices and attach new ones */
		rc = ata_eh_revalidate_and_attach(link, &dev);
		अगर (rc)
			जाओ rest_fail;

		/* अगर PMP got attached, वापस, pmp EH will take care of it */
		अगर (link->device->class == ATA_DEV_PMP) अणु
			ehc->i.action = 0;
			वापस 0;
		पूर्ण

		/* configure transfer mode अगर necessary */
		अगर (ehc->i.flags & ATA_EHI_SETMODE) अणु
			rc = ata_set_mode(link, &dev);
			अगर (rc)
				जाओ rest_fail;
			ehc->i.flags &= ~ATA_EHI_SETMODE;
		पूर्ण

		/* If reset has been issued, clear UA to aव्योम
		 * disrupting the current users of the device.
		 */
		अगर (ehc->i.flags & ATA_EHI_DID_RESET) अणु
			ata_क्रम_each_dev(dev, link, ALL) अणु
				अगर (dev->class != ATA_DEV_ATAPI)
					जारी;
				rc = atapi_eh_clear_ua(dev);
				अगर (rc)
					जाओ rest_fail;
				अगर (zpodd_dev_enabled(dev))
					zpodd_post_घातeron(dev);
			पूर्ण
		पूर्ण

		/* retry flush अगर necessary */
		ata_क्रम_each_dev(dev, link, ALL) अणु
			अगर (dev->class != ATA_DEV_ATA &&
			    dev->class != ATA_DEV_ZAC)
				जारी;
			rc = ata_eh_maybe_retry_flush(dev);
			अगर (rc)
				जाओ rest_fail;
		पूर्ण

	config_lpm:
		/* configure link घातer saving */
		अगर (link->lpm_policy != ap->target_lpm_policy) अणु
			rc = ata_eh_set_lpm(link, ap->target_lpm_policy, &dev);
			अगर (rc)
				जाओ rest_fail;
		पूर्ण

		/* this link is okay now */
		ehc->i.flags = 0;
		जारी;

	rest_fail:
		nr_fails++;
		अगर (dev)
			ata_eh_handle_dev_fail(dev, rc);

		अगर (ap->pflags & ATA_PFLAG_FROZEN) अणु
			/* PMP reset requires working host port.
			 * Can't retry if it's frozen.
			 */
			अगर (sata_pmp_attached(ap))
				जाओ out;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nr_fails)
		जाओ retry;

 out:
	अगर (rc && r_failed_link)
		*r_failed_link = link;

	DPRINTK("EXIT, rc=%d\n", rc);
	वापस rc;
पूर्ण

/**
 *	ata_eh_finish - finish up EH
 *	@ap: host port to finish EH क्रम
 *
 *	Recovery is complete.  Clean up EH states and retry or finish
 *	failed qcs.
 *
 *	LOCKING:
 *	None.
 */
व्योम ata_eh_finish(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_queued_cmd *qc;
	पूर्णांक tag;

	/* retry or finish qcs */
	ata_qc_क्रम_each_raw(ap, qc, tag) अणु
		अगर (!(qc->flags & ATA_QCFLAG_FAILED))
			जारी;

		अगर (qc->err_mask) अणु
			/* FIXME: Once EH migration is complete,
			 * generate sense data in this function,
			 * considering both err_mask and tf.
			 */
			अगर (qc->flags & ATA_QCFLAG_RETRY)
				ata_eh_qc_retry(qc);
			अन्यथा
				ata_eh_qc_complete(qc);
		पूर्ण अन्यथा अणु
			अगर (qc->flags & ATA_QCFLAG_SENSE_VALID) अणु
				ata_eh_qc_complete(qc);
			पूर्ण अन्यथा अणु
				/* feed zero TF to sense generation */
				स_रखो(&qc->result_tf, 0, माप(qc->result_tf));
				ata_eh_qc_retry(qc);
			पूर्ण
		पूर्ण
	पूर्ण

	/* make sure nr_active_links is zero after EH */
	WARN_ON(ap->nr_active_links);
	ap->nr_active_links = 0;
पूर्ण

/**
 *	ata_करो_eh - करो standard error handling
 *	@ap: host port to handle error क्रम
 *
 *	@prereset: prereset method (can be शून्य)
 *	@softreset: softreset method (can be शून्य)
 *	@hardreset: hardreset method (can be शून्य)
 *	@postreset: postreset method (can be शून्य)
 *
 *	Perक्रमm standard error handling sequence.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
व्योम ata_करो_eh(काष्ठा ata_port *ap, ata_prereset_fn_t prereset,
	       ata_reset_fn_t softreset, ata_reset_fn_t hardreset,
	       ata_postreset_fn_t postreset)
अणु
	काष्ठा ata_device *dev;
	पूर्णांक rc;

	ata_eh_स्वतःpsy(ap);
	ata_eh_report(ap);

	rc = ata_eh_recover(ap, prereset, softreset, hardreset, postreset,
			    शून्य);
	अगर (rc) अणु
		ata_क्रम_each_dev(dev, &ap->link, ALL)
			ata_dev_disable(dev);
	पूर्ण

	ata_eh_finish(ap);
पूर्ण

/**
 *	ata_std_error_handler - standard error handler
 *	@ap: host port to handle error क्रम
 *
 *	Standard error handler
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
व्योम ata_std_error_handler(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_port_operations *ops = ap->ops;
	ata_reset_fn_t hardreset = ops->hardreset;

	/* ignore built-in hardreset अगर SCR access is not available */
	अगर (hardreset == sata_std_hardreset && !sata_scr_valid(&ap->link))
		hardreset = शून्य;

	ata_करो_eh(ap, ops->prereset, ops->softreset, hardreset, ops->postreset);
पूर्ण
EXPORT_SYMBOL_GPL(ata_std_error_handler);

#अगर_घोषित CONFIG_PM
/**
 *	ata_eh_handle_port_suspend - perक्रमm port suspend operation
 *	@ap: port to suspend
 *
 *	Suspend @ap.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
अटल व्योम ata_eh_handle_port_suspend(काष्ठा ata_port *ap)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;
	काष्ठा ata_device *dev;

	/* are we suspending? */
	spin_lock_irqsave(ap->lock, flags);
	अगर (!(ap->pflags & ATA_PFLAG_PM_PENDING) ||
	    ap->pm_mesg.event & PM_EVENT_RESUME) अणु
		spin_unlock_irqrestore(ap->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(ap->lock, flags);

	WARN_ON(ap->pflags & ATA_PFLAG_SUSPENDED);

	/*
	 * If we have a ZPODD attached, check its zero
	 * घातer पढ़ोy status beक्रमe the port is frozen.
	 * Only needed क्रम runसमय suspend.
	 */
	अगर (PMSG_IS_AUTO(ap->pm_mesg)) अणु
		ata_क्रम_each_dev(dev, &ap->link, ENABLED) अणु
			अगर (zpodd_dev_enabled(dev))
				zpodd_on_suspend(dev);
		पूर्ण
	पूर्ण

	/* tell ACPI we're suspending */
	rc = ata_acpi_on_suspend(ap);
	अगर (rc)
		जाओ out;

	/* suspend */
	ata_eh_मुक्तze_port(ap);

	अगर (ap->ops->port_suspend)
		rc = ap->ops->port_suspend(ap, ap->pm_mesg);

	ata_acpi_set_state(ap, ap->pm_mesg);
 out:
	/* update the flags */
	spin_lock_irqsave(ap->lock, flags);

	ap->pflags &= ~ATA_PFLAG_PM_PENDING;
	अगर (rc == 0)
		ap->pflags |= ATA_PFLAG_SUSPENDED;
	अन्यथा अगर (ap->pflags & ATA_PFLAG_FROZEN)
		ata_port_schedule_eh(ap);

	spin_unlock_irqrestore(ap->lock, flags);

	वापस;
पूर्ण

/**
 *	ata_eh_handle_port_resume - perक्रमm port resume operation
 *	@ap: port to resume
 *
 *	Resume @ap.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
अटल व्योम ata_eh_handle_port_resume(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_link *link;
	काष्ठा ata_device *dev;
	अचिन्हित दीर्घ flags;

	/* are we resuming? */
	spin_lock_irqsave(ap->lock, flags);
	अगर (!(ap->pflags & ATA_PFLAG_PM_PENDING) ||
	    !(ap->pm_mesg.event & PM_EVENT_RESUME)) अणु
		spin_unlock_irqrestore(ap->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(ap->lock, flags);

	WARN_ON(!(ap->pflags & ATA_PFLAG_SUSPENDED));

	/*
	 * Error बारtamps are in jअगरfies which करोesn't run जबतक
	 * suspended and PHY events during resume isn't too uncommon.
	 * When the two are combined, it can lead to unnecessary speed
	 * करोwns अगर the machine is suspended and resumed repeatedly.
	 * Clear error history.
	 */
	ata_क्रम_each_link(link, ap, HOST_FIRST)
		ata_क्रम_each_dev(dev, link, ALL)
			ata_ering_clear(&dev->ering);

	ata_acpi_set_state(ap, ap->pm_mesg);

	अगर (ap->ops->port_resume)
		ap->ops->port_resume(ap);

	/* tell ACPI that we're resuming */
	ata_acpi_on_resume(ap);

	/* update the flags */
	spin_lock_irqsave(ap->lock, flags);
	ap->pflags &= ~(ATA_PFLAG_PM_PENDING | ATA_PFLAG_SUSPENDED);
	spin_unlock_irqrestore(ap->lock, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */
