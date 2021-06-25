<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * libata-pmp.c - libata port multiplier support
 *
 * Copyright (c) 2007  SUSE Linux Products GmbH
 * Copyright (c) 2007  Tejun Heo <teheo@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/libata.h>
#समावेश <linux/slab.h>
#समावेश "libata.h"
#समावेश "libata-transport.h"

स्थिर काष्ठा ata_port_operations sata_pmp_port_ops = अणु
	.inherits		= &sata_port_ops,
	.pmp_prereset		= ata_std_prereset,
	.pmp_hardreset		= sata_std_hardreset,
	.pmp_postreset		= ata_std_postreset,
	.error_handler		= sata_pmp_error_handler,
पूर्ण;

/**
 *	sata_pmp_पढ़ो - पढ़ो PMP रेजिस्टर
 *	@link: link to पढ़ो PMP रेजिस्टर क्रम
 *	@reg: रेजिस्टर to पढ़ो
 *	@r_val: resulting value
 *
 *	Read PMP रेजिस्टर.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, AC_ERR_* mask on failure.
 */
अटल अचिन्हित पूर्णांक sata_pmp_पढ़ो(काष्ठा ata_link *link, पूर्णांक reg, u32 *r_val)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_device *pmp_dev = ap->link.device;
	काष्ठा ata_taskfile tf;
	अचिन्हित पूर्णांक err_mask;

	ata_tf_init(pmp_dev, &tf);
	tf.command = ATA_CMD_PMP_READ;
	tf.protocol = ATA_PROT_NODATA;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE | ATA_TFLAG_LBA48;
	tf.feature = reg;
	tf.device = link->pmp;

	err_mask = ata_exec_पूर्णांकernal(pmp_dev, &tf, शून्य, DMA_NONE, शून्य, 0,
				     SATA_PMP_RW_TIMEOUT);
	अगर (err_mask)
		वापस err_mask;

	*r_val = tf.nsect | tf.lbal << 8 | tf.lbam << 16 | tf.lbah << 24;
	वापस 0;
पूर्ण

/**
 *	sata_pmp_ग_लिखो - ग_लिखो PMP रेजिस्टर
 *	@link: link to ग_लिखो PMP रेजिस्टर क्रम
 *	@reg: रेजिस्टर to ग_लिखो
 *	@val: value to ग_लिखो
 *
 *	Write PMP रेजिस्टर.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, AC_ERR_* mask on failure.
 */
अटल अचिन्हित पूर्णांक sata_pmp_ग_लिखो(काष्ठा ata_link *link, पूर्णांक reg, u32 val)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_device *pmp_dev = ap->link.device;
	काष्ठा ata_taskfile tf;

	ata_tf_init(pmp_dev, &tf);
	tf.command = ATA_CMD_PMP_WRITE;
	tf.protocol = ATA_PROT_NODATA;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE | ATA_TFLAG_LBA48;
	tf.feature = reg;
	tf.device = link->pmp;
	tf.nsect = val & 0xff;
	tf.lbal = (val >> 8) & 0xff;
	tf.lbam = (val >> 16) & 0xff;
	tf.lbah = (val >> 24) & 0xff;

	वापस ata_exec_पूर्णांकernal(pmp_dev, &tf, शून्य, DMA_NONE, शून्य, 0,
				 SATA_PMP_RW_TIMEOUT);
पूर्ण

/**
 *	sata_pmp_qc_defer_cmd_चयन - qc_defer क्रम command चयनing PMP
 *	@qc: ATA command in question
 *
 *	A host which has command चयनing PMP support cannot issue
 *	commands to multiple links simultaneously.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	ATA_DEFER_* अगर deferring is needed, 0 otherwise.
 */
पूर्णांक sata_pmp_qc_defer_cmd_चयन(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_link *link = qc->dev->link;
	काष्ठा ata_port *ap = link->ap;

	अगर (ap->excl_link == शून्य || ap->excl_link == link) अणु
		अगर (ap->nr_active_links == 0 || ata_link_active(link)) अणु
			qc->flags |= ATA_QCFLAG_CLEAR_EXCL;
			वापस ata_std_qc_defer(qc);
		पूर्ण

		ap->excl_link = link;
	पूर्ण

	वापस ATA_DEFER_PORT;
पूर्ण

/**
 *	sata_pmp_scr_पढ़ो - पढ़ो PSCR
 *	@link: ATA link to पढ़ो PSCR क्रम
 *	@reg: PSCR to पढ़ो
 *	@r_val: resulting value
 *
 *	Read PSCR @reg पूर्णांकo @r_val क्रम @link, to be called from
 *	ata_scr_पढ़ो().
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक sata_pmp_scr_पढ़ो(काष्ठा ata_link *link, पूर्णांक reg, u32 *r_val)
अणु
	अचिन्हित पूर्णांक err_mask;

	अगर (reg > SATA_PMP_PSCR_CONTROL)
		वापस -EINVAL;

	err_mask = sata_pmp_पढ़ो(link, reg, r_val);
	अगर (err_mask) अणु
		ata_link_warn(link, "failed to read SCR %d (Emask=0x%x)\n",
			      reg, err_mask);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	sata_pmp_scr_ग_लिखो - ग_लिखो PSCR
 *	@link: ATA link to ग_लिखो PSCR क्रम
 *	@reg: PSCR to ग_लिखो
 *	@val: value to be written
 *
 *	Write @val to PSCR @reg क्रम @link, to be called from
 *	ata_scr_ग_लिखो() and ata_scr_ग_लिखो_flush().
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक sata_pmp_scr_ग_लिखो(काष्ठा ata_link *link, पूर्णांक reg, u32 val)
अणु
	अचिन्हित पूर्णांक err_mask;

	अगर (reg > SATA_PMP_PSCR_CONTROL)
		वापस -EINVAL;

	err_mask = sata_pmp_ग_लिखो(link, reg, val);
	अगर (err_mask) अणु
		ata_link_warn(link, "failed to write SCR %d (Emask=0x%x)\n",
			      reg, err_mask);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	sata_pmp_set_lpm - configure LPM क्रम a PMP link
 *	@link: PMP link to configure LPM क्रम
 *	@policy: target LPM policy
 *	@hपूर्णांकs: LPM hपूर्णांकs
 *
 *	Configure LPM क्रम @link.  This function will contain any PMP
 *	specअगरic workarounds अगर necessary.
 *
 *	LOCKING:
 *	EH context.
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक sata_pmp_set_lpm(काष्ठा ata_link *link, क्रमागत ata_lpm_policy policy,
		     अचिन्हित hपूर्णांकs)
अणु
	वापस sata_link_scr_lpm(link, policy, true);
पूर्ण

/**
 *	sata_pmp_पढ़ो_gscr - पढ़ो GSCR block of SATA PMP
 *	@dev: PMP device
 *	@gscr: buffer to पढ़ो GSCR block पूर्णांकo
 *
 *	Read selected PMP GSCRs from the PMP at @dev.  This will serve
 *	as configuration and identअगरication info क्रम the PMP.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक sata_pmp_पढ़ो_gscr(काष्ठा ata_device *dev, u32 *gscr)
अणु
	अटल स्थिर पूर्णांक gscr_to_पढ़ो[] = अणु 0, 1, 2, 32, 33, 64, 96 पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(gscr_to_पढ़ो); i++) अणु
		पूर्णांक reg = gscr_to_पढ़ो[i];
		अचिन्हित पूर्णांक err_mask;

		err_mask = sata_pmp_पढ़ो(dev->link, reg, &gscr[reg]);
		अगर (err_mask) अणु
			ata_dev_err(dev, "failed to read PMP GSCR[%d] (Emask=0x%x)\n",
				    reg, err_mask);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *sata_pmp_spec_rev_str(स्थिर u32 *gscr)
अणु
	u32 rev = gscr[SATA_PMP_GSCR_REV];

	अगर (rev & (1 << 3))
		वापस "1.2";
	अगर (rev & (1 << 2))
		वापस "1.1";
	अगर (rev & (1 << 1))
		वापस "1.0";
	वापस "<unknown>";
पूर्ण

#घोषणा PMP_GSCR_SII_POL 129

अटल पूर्णांक sata_pmp_configure(काष्ठा ata_device *dev, पूर्णांक prपूर्णांक_info)
अणु
	काष्ठा ata_port *ap = dev->link->ap;
	u32 *gscr = dev->gscr;
	u16 venकरोr = sata_pmp_gscr_venकरोr(gscr);
	u16 devid = sata_pmp_gscr_devid(gscr);
	अचिन्हित पूर्णांक err_mask = 0;
	स्थिर अक्षर *reason;
	पूर्णांक nr_ports, rc;

	nr_ports = sata_pmp_gscr_ports(gscr);

	अगर (nr_ports <= 0 || nr_ports > SATA_PMP_MAX_PORTS) अणु
		rc = -EINVAL;
		reason = "invalid nr_ports";
		जाओ fail;
	पूर्ण

	अगर ((ap->flags & ATA_FLAG_AN) &&
	    (gscr[SATA_PMP_GSCR_FEAT] & SATA_PMP_FEAT_NOTIFY))
		dev->flags |= ATA_DFLAG_AN;

	/* monitor SERR_PHYRDY_CHG on fan-out ports */
	err_mask = sata_pmp_ग_लिखो(dev->link, SATA_PMP_GSCR_ERROR_EN,
				  SERR_PHYRDY_CHG);
	अगर (err_mask) अणु
		rc = -EIO;
		reason = "failed to write GSCR_ERROR_EN";
		जाओ fail;
	पूर्ण

	/* Disable sending Early R_OK.
	 * With "cached read" HDD testing and multiple ports busy on a SATA
	 * host controller, 3x26 PMP will very rarely drop a deferred
	 * R_OK that was पूर्णांकended क्रम the host. Symptom will be all
	 * 5 drives under test will समयout, get reset, and recover.
	 */
	अगर (venकरोr == 0x1095 && (devid == 0x3726 || devid == 0x3826)) अणु
		u32 reg;

		err_mask = sata_pmp_पढ़ो(&ap->link, PMP_GSCR_SII_POL, &reg);
		अगर (err_mask) अणु
			rc = -EIO;
			reason = "failed to read Sil3x26 Private Register";
			जाओ fail;
		पूर्ण
		reg &= ~0x1;
		err_mask = sata_pmp_ग_लिखो(&ap->link, PMP_GSCR_SII_POL, reg);
		अगर (err_mask) अणु
			rc = -EIO;
			reason = "failed to write Sil3x26 Private Register";
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (prपूर्णांक_info) अणु
		ata_dev_info(dev, "Port Multiplier %s, "
			     "0x%04x:0x%04x r%d, %d ports, feat 0x%x/0x%x\n",
			     sata_pmp_spec_rev_str(gscr), venकरोr, devid,
			     sata_pmp_gscr_rev(gscr),
			     nr_ports, gscr[SATA_PMP_GSCR_FEAT_EN],
			     gscr[SATA_PMP_GSCR_FEAT]);

		अगर (!(dev->flags & ATA_DFLAG_AN))
			ata_dev_info(dev,
				"Asynchronous notification not supported, "
				"hotplug won't work on fan-out ports. Use warm-plug instead.\n");
	पूर्ण

	वापस 0;

 fail:
	ata_dev_err(dev,
		    "failed to configure Port Multiplier (%s, Emask=0x%x)\n",
		    reason, err_mask);
	वापस rc;
पूर्ण

अटल पूर्णांक sata_pmp_init_links (काष्ठा ata_port *ap, पूर्णांक nr_ports)
अणु
	काष्ठा ata_link *pmp_link = ap->pmp_link;
	पूर्णांक i, err;

	अगर (!pmp_link) अणु
		pmp_link = kसुस्मृति(SATA_PMP_MAX_PORTS, माप(pmp_link[0]),
				   GFP_NOIO);
		अगर (!pmp_link)
			वापस -ENOMEM;

		क्रम (i = 0; i < SATA_PMP_MAX_PORTS; i++)
			ata_link_init(ap, &pmp_link[i], i);

		ap->pmp_link = pmp_link;

		क्रम (i = 0; i < SATA_PMP_MAX_PORTS; i++) अणु
			err = ata_tlink_add(&pmp_link[i]);
			अगर (err) अणु
				जाओ err_tlink;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nr_ports; i++) अणु
		काष्ठा ata_link *link = &pmp_link[i];
		काष्ठा ata_eh_context *ehc = &link->eh_context;

		link->flags = 0;
		ehc->i.probe_mask |= ATA_ALL_DEVICES;
		ehc->i.action |= ATA_EH_RESET;
	पूर्ण

	वापस 0;
  err_tlink:
	जबतक (--i >= 0)
		ata_tlink_delete(&pmp_link[i]);
	kमुक्त(pmp_link);
	ap->pmp_link = शून्य;
	वापस err;
पूर्ण

अटल व्योम sata_pmp_quirks(काष्ठा ata_port *ap)
अणु
	u32 *gscr = ap->link.device->gscr;
	u16 venकरोr = sata_pmp_gscr_venकरोr(gscr);
	u16 devid = sata_pmp_gscr_devid(gscr);
	काष्ठा ata_link *link;

	अगर (venकरोr == 0x1095 && (devid == 0x3726 || devid == 0x3826)) अणु
		/* sil3x26 quirks */
		ata_क्रम_each_link(link, ap, EDGE) अणु
			/* link reports offline after LPM */
			link->flags |= ATA_LFLAG_NO_LPM;

			/*
			 * Class code report is unreliable and SRST बार
			 * out under certain configurations.
			 */
			अगर (link->pmp < 5)
				link->flags |= ATA_LFLAG_NO_SRST |
					       ATA_LFLAG_ASSUME_ATA;

			/* port 5 is क्रम SEMB device and it करोesn't like SRST */
			अगर (link->pmp == 5)
				link->flags |= ATA_LFLAG_NO_SRST |
					       ATA_LFLAG_ASSUME_SEMB;
		पूर्ण
	पूर्ण अन्यथा अगर (venकरोr == 0x1095 && devid == 0x4723) अणु
		/*
		 * sil4723 quirks
		 *
		 * Link reports offline after LPM.  Class code report is
		 * unreliable.  SIMG PMPs never got SRST reliable and the
		 * config device at port 2 locks up on SRST.
		 */
		ata_क्रम_each_link(link, ap, EDGE)
			link->flags |= ATA_LFLAG_NO_LPM |
				       ATA_LFLAG_NO_SRST |
				       ATA_LFLAG_ASSUME_ATA;
	पूर्ण अन्यथा अगर (venकरोr == 0x1095 && devid == 0x4726) अणु
		/* sil4726 quirks */
		ata_क्रम_each_link(link, ap, EDGE) अणु
			/* link reports offline after LPM */
			link->flags |= ATA_LFLAG_NO_LPM;

			/* Class code report is unreliable and SRST
			 * बार out under certain configurations.
			 * Config device can be at port 0 or 5 and
			 * locks up on SRST.
			 */
			अगर (link->pmp <= 5)
				link->flags |= ATA_LFLAG_NO_SRST |
					       ATA_LFLAG_ASSUME_ATA;

			/* Port 6 is क्रम SEMB device which करोesn't
			 * like SRST either.
			 */
			अगर (link->pmp == 6)
				link->flags |= ATA_LFLAG_NO_SRST |
					       ATA_LFLAG_ASSUME_SEMB;
		पूर्ण
	पूर्ण अन्यथा अगर (venकरोr == 0x1095 && (devid == 0x5723 || devid == 0x5733 ||
					devid == 0x5734 || devid == 0x5744)) अणु
		/* sil5723/5744 quirks */

		/* sil5723/5744 has either two or three करोwnstream
		 * ports depending on operation mode.  The last port
		 * is empty अगर any actual IO device is available or
		 * occupied by a pseuकरो configuration device
		 * otherwise.  Don't try hard to recover it.
		 */
		ap->pmp_link[ap->nr_pmp_links - 1].flags |= ATA_LFLAG_NO_RETRY;
	पूर्ण अन्यथा अगर (venकरोr == 0x197b && (devid == 0x2352 || devid == 0x0325)) अणु
		/*
		 * 0x2352: found in Thermaltake BlackX Duet, jmicron JMB350?
		 * 0x0325: jmicron JMB394.
		 */
		ata_क्रम_each_link(link, ap, EDGE) अणु
			/* SRST अवरोधs detection and disks get misclassअगरied
			 * LPM disabled to aव्योम potential problems
			 */
			link->flags |= ATA_LFLAG_NO_LPM |
				       ATA_LFLAG_NO_SRST |
				       ATA_LFLAG_ASSUME_ATA;
		पूर्ण
	पूर्ण अन्यथा अगर (venकरोr == 0x11ab && devid == 0x4140) अणु
		/* Marvell 4140 quirks */
		ata_क्रम_each_link(link, ap, EDGE) अणु
			/* port 4 is क्रम SEMB device and it करोesn't like SRST */
			अगर (link->pmp == 4)
				link->flags |= ATA_LFLAG_DISABLED;
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	sata_pmp_attach - attach a SATA PMP device
 *	@dev: SATA PMP device to attach
 *
 *	Configure and attach SATA PMP device @dev.  This function is
 *	also responsible क्रम allocating and initializing PMP links.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक sata_pmp_attach(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_link *link = dev->link;
	काष्ठा ata_port *ap = link->ap;
	अचिन्हित दीर्घ flags;
	काष्ठा ata_link *tlink;
	पूर्णांक rc;

	/* is it hanging off the right place? */
	अगर (!sata_pmp_supported(ap)) अणु
		ata_dev_err(dev, "host does not support Port Multiplier\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!ata_is_host_link(link)) अणु
		ata_dev_err(dev, "Port Multipliers cannot be nested\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->devno) अणु
		ata_dev_err(dev, "Port Multiplier must be the first device\n");
		वापस -EINVAL;
	पूर्ण

	WARN_ON(link->pmp != 0);
	link->pmp = SATA_PMP_CTRL_PORT;

	/* पढ़ो GSCR block */
	rc = sata_pmp_पढ़ो_gscr(dev, dev->gscr);
	अगर (rc)
		जाओ fail;

	/* config PMP */
	rc = sata_pmp_configure(dev, 1);
	अगर (rc)
		जाओ fail;

	rc = sata_pmp_init_links(ap, sata_pmp_gscr_ports(dev->gscr));
	अगर (rc) अणु
		ata_dev_info(dev, "failed to initialize PMP links\n");
		जाओ fail;
	पूर्ण

	/* attach it */
	spin_lock_irqsave(ap->lock, flags);
	WARN_ON(ap->nr_pmp_links);
	ap->nr_pmp_links = sata_pmp_gscr_ports(dev->gscr);
	spin_unlock_irqrestore(ap->lock, flags);

	sata_pmp_quirks(ap);

	अगर (ap->ops->pmp_attach)
		ap->ops->pmp_attach(ap);

	ata_क्रम_each_link(tlink, ap, EDGE)
		sata_link_init_spd(tlink);

	वापस 0;

 fail:
	link->pmp = 0;
	वापस rc;
पूर्ण

/**
 *	sata_pmp_detach - detach a SATA PMP device
 *	@dev: SATA PMP device to detach
 *
 *	Detach SATA PMP device @dev.  This function is also
 *	responsible क्रम deconfiguring PMP links.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
अटल व्योम sata_pmp_detach(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_link *link = dev->link;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_link *tlink;
	अचिन्हित दीर्घ flags;

	ata_dev_info(dev, "Port Multiplier detaching\n");

	WARN_ON(!ata_is_host_link(link) || dev->devno ||
		link->pmp != SATA_PMP_CTRL_PORT);

	अगर (ap->ops->pmp_detach)
		ap->ops->pmp_detach(ap);

	ata_क्रम_each_link(tlink, ap, EDGE)
		ata_eh_detach_dev(tlink->device);

	spin_lock_irqsave(ap->lock, flags);
	ap->nr_pmp_links = 0;
	link->pmp = 0;
	spin_unlock_irqrestore(ap->lock, flags);
पूर्ण

/**
 *	sata_pmp_same_pmp - करोes new GSCR matches the configured PMP?
 *	@dev: PMP device to compare against
 *	@new_gscr: GSCR block of the new device
 *
 *	Compare @new_gscr against @dev and determine whether @dev is
 *	the PMP described by @new_gscr.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	1 अगर @dev matches @new_gscr, 0 otherwise.
 */
अटल पूर्णांक sata_pmp_same_pmp(काष्ठा ata_device *dev, स्थिर u32 *new_gscr)
अणु
	स्थिर u32 *old_gscr = dev->gscr;
	u16 old_venकरोr, new_venकरोr, old_devid, new_devid;
	पूर्णांक old_nr_ports, new_nr_ports;

	old_venकरोr = sata_pmp_gscr_venकरोr(old_gscr);
	new_venकरोr = sata_pmp_gscr_venकरोr(new_gscr);
	old_devid = sata_pmp_gscr_devid(old_gscr);
	new_devid = sata_pmp_gscr_devid(new_gscr);
	old_nr_ports = sata_pmp_gscr_ports(old_gscr);
	new_nr_ports = sata_pmp_gscr_ports(new_gscr);

	अगर (old_venकरोr != new_venकरोr) अणु
		ata_dev_info(dev,
			     "Port Multiplier vendor mismatch '0x%x' != '0x%x'\n",
			     old_venकरोr, new_venकरोr);
		वापस 0;
	पूर्ण

	अगर (old_devid != new_devid) अणु
		ata_dev_info(dev,
			     "Port Multiplier device ID mismatch '0x%x' != '0x%x'\n",
			     old_devid, new_devid);
		वापस 0;
	पूर्ण

	अगर (old_nr_ports != new_nr_ports) अणु
		ata_dev_info(dev,
			     "Port Multiplier nr_ports mismatch '0x%x' != '0x%x'\n",
			     old_nr_ports, new_nr_ports);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/**
 *	sata_pmp_revalidate - revalidate SATA PMP
 *	@dev: PMP device to revalidate
 *	@new_class: new class code
 *
 *	Re-पढ़ो GSCR block and make sure @dev is still attached to the
 *	port and properly configured.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक sata_pmp_revalidate(काष्ठा ata_device *dev, अचिन्हित पूर्णांक new_class)
अणु
	काष्ठा ata_link *link = dev->link;
	काष्ठा ata_port *ap = link->ap;
	u32 *gscr = (व्योम *)ap->sector_buf;
	पूर्णांक rc;

	DPRINTK("ENTER\n");

	ata_eh_about_to_करो(link, शून्य, ATA_EH_REVALIDATE);

	अगर (!ata_dev_enabled(dev)) अणु
		rc = -ENODEV;
		जाओ fail;
	पूर्ण

	/* wrong class? */
	अगर (ata_class_enabled(new_class) && new_class != ATA_DEV_PMP) अणु
		rc = -ENODEV;
		जाओ fail;
	पूर्ण

	/* पढ़ो GSCR */
	rc = sata_pmp_पढ़ो_gscr(dev, gscr);
	अगर (rc)
		जाओ fail;

	/* is the pmp still there? */
	अगर (!sata_pmp_same_pmp(dev, gscr)) अणु
		rc = -ENODEV;
		जाओ fail;
	पूर्ण

	स_नकल(dev->gscr, gscr, माप(gscr[0]) * SATA_PMP_GSCR_DWORDS);

	rc = sata_pmp_configure(dev, 0);
	अगर (rc)
		जाओ fail;

	ata_eh_करोne(link, शून्य, ATA_EH_REVALIDATE);

	DPRINTK("EXIT, rc=0\n");
	वापस 0;

 fail:
	ata_dev_err(dev, "PMP revalidation failed (errno=%d)\n", rc);
	DPRINTK("EXIT, rc=%d\n", rc);
	वापस rc;
पूर्ण

/**
 *	sata_pmp_revalidate_quick - revalidate SATA PMP quickly
 *	@dev: PMP device to revalidate
 *
 *	Make sure the attached PMP is accessible.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक sata_pmp_revalidate_quick(काष्ठा ata_device *dev)
अणु
	अचिन्हित पूर्णांक err_mask;
	u32 prod_id;

	err_mask = sata_pmp_पढ़ो(dev->link, SATA_PMP_GSCR_PROD_ID, &prod_id);
	अगर (err_mask) अणु
		ata_dev_err(dev,
			    "failed to read PMP product ID (Emask=0x%x)\n",
			    err_mask);
		वापस -EIO;
	पूर्ण

	अगर (prod_id != dev->gscr[SATA_PMP_GSCR_PROD_ID]) अणु
		ata_dev_err(dev, "PMP product ID mismatch\n");
		/* something weird is going on, request full PMP recovery */
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	sata_pmp_eh_recover_pmp - recover PMP
 *	@ap: ATA port PMP is attached to
 *	@prereset: prereset method (can be शून्य)
 *	@softreset: softreset method
 *	@hardreset: hardreset method
 *	@postreset: postreset method (can be शून्य)
 *
 *	Recover PMP attached to @ap.  Recovery procedure is somewhat
 *	similar to that of ata_eh_recover() except that reset should
 *	always be perक्रमmed in hard->soft sequence and recovery
 *	failure results in PMP detachment.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक sata_pmp_eh_recover_pmp(काष्ठा ata_port *ap,
		ata_prereset_fn_t prereset, ata_reset_fn_t softreset,
		ata_reset_fn_t hardreset, ata_postreset_fn_t postreset)
अणु
	काष्ठा ata_link *link = &ap->link;
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	काष्ठा ata_device *dev = link->device;
	पूर्णांक tries = ATA_EH_PMP_TRIES;
	पूर्णांक detach = 0, rc = 0;
	पूर्णांक reval_failed = 0;

	DPRINTK("ENTER\n");

	अगर (dev->flags & ATA_DFLAG_DETACH) अणु
		detach = 1;
		rc = -ENODEV;
		जाओ fail;
	पूर्ण

 retry:
	ehc->classes[0] = ATA_DEV_UNKNOWN;

	अगर (ehc->i.action & ATA_EH_RESET) अणु
		काष्ठा ata_link *tlink;

		/* reset */
		rc = ata_eh_reset(link, 0, prereset, softreset, hardreset,
				  postreset);
		अगर (rc) अणु
			ata_link_err(link, "failed to reset PMP, giving up\n");
			जाओ fail;
		पूर्ण

		/* PMP is reset, SErrors cannot be trusted, scan all */
		ata_क्रम_each_link(tlink, ap, EDGE) अणु
			काष्ठा ata_eh_context *ehc = &tlink->eh_context;

			ehc->i.probe_mask |= ATA_ALL_DEVICES;
			ehc->i.action |= ATA_EH_RESET;
		पूर्ण
	पूर्ण

	/* If revalidation is requested, revalidate and reconfigure;
	 * otherwise, करो quick revalidation.
	 */
	अगर (ehc->i.action & ATA_EH_REVALIDATE)
		rc = sata_pmp_revalidate(dev, ehc->classes[0]);
	अन्यथा
		rc = sata_pmp_revalidate_quick(dev);

	अगर (rc) अणु
		tries--;

		अगर (rc == -ENODEV) अणु
			ehc->i.probe_mask |= ATA_ALL_DEVICES;
			detach = 1;
			/* give it just two more chances */
			tries = min(tries, 2);
		पूर्ण

		अगर (tries) अणु
			/* consecutive revalidation failures? speed करोwn */
			अगर (reval_failed)
				sata_करोwn_spd_limit(link, 0);
			अन्यथा
				reval_failed = 1;

			ehc->i.action |= ATA_EH_RESET;
			जाओ retry;
		पूर्ण अन्यथा अणु
			ata_dev_err(dev,
				    "failed to recover PMP after %d tries, giving up\n",
				    ATA_EH_PMP_TRIES);
			जाओ fail;
		पूर्ण
	पूर्ण

	/* okay, PMP resurrected */
	ehc->i.flags = 0;

	DPRINTK("EXIT, rc=0\n");
	वापस 0;

 fail:
	sata_pmp_detach(dev);
	अगर (detach)
		ata_eh_detach_dev(dev);
	अन्यथा
		ata_dev_disable(dev);

	DPRINTK("EXIT, rc=%d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक sata_pmp_eh_handle_disabled_links(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_link *link;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(ap->lock, flags);

	ata_क्रम_each_link(link, ap, EDGE) अणु
		अगर (!(link->flags & ATA_LFLAG_DISABLED))
			जारी;

		spin_unlock_irqrestore(ap->lock, flags);

		/* Some PMPs require hardreset sequence to get
		 * SError.N working.
		 */
		sata_link_hardreset(link, sata_deb_timing_normal,
				ata_deadline(jअगरfies, ATA_TMOUT_INTERNAL_QUICK),
				शून्य, शून्य);

		/* unconditionally clear SError.N */
		rc = sata_scr_ग_लिखो(link, SCR_ERROR, SERR_PHYRDY_CHG);
		अगर (rc) अणु
			ata_link_err(link,
				     "failed to clear SError.N (errno=%d)\n",
				     rc);
			वापस rc;
		पूर्ण

		spin_lock_irqsave(ap->lock, flags);
	पूर्ण

	spin_unlock_irqrestore(ap->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sata_pmp_handle_link_fail(काष्ठा ata_link *link, पूर्णांक *link_tries)
अणु
	काष्ठा ata_port *ap = link->ap;
	अचिन्हित दीर्घ flags;

	अगर (link_tries[link->pmp] && --link_tries[link->pmp])
		वापस 1;

	/* disable this link */
	अगर (!(link->flags & ATA_LFLAG_DISABLED)) अणु
		ata_link_warn(link,
			"failed to recover link after %d tries, disabling\n",
			ATA_EH_PMP_LINK_TRIES);

		spin_lock_irqsave(ap->lock, flags);
		link->flags |= ATA_LFLAG_DISABLED;
		spin_unlock_irqrestore(ap->lock, flags);
	पूर्ण

	ata_dev_disable(link->device);
	link->eh_context.i.action = 0;

	वापस 0;
पूर्ण

/**
 *	sata_pmp_eh_recover - recover PMP-enabled port
 *	@ap: ATA port to recover
 *
 *	Drive EH recovery operation क्रम PMP enabled port @ap.  This
 *	function recovers host and PMP ports with proper retrials and
 *	fallbacks.  Actual recovery operations are perक्रमmed using
 *	ata_eh_recover() and sata_pmp_eh_recover_pmp().
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक sata_pmp_eh_recover(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_port_operations *ops = ap->ops;
	पूर्णांक pmp_tries, link_tries[SATA_PMP_MAX_PORTS];
	काष्ठा ata_link *pmp_link = &ap->link;
	काष्ठा ata_device *pmp_dev = pmp_link->device;
	काष्ठा ata_eh_context *pmp_ehc = &pmp_link->eh_context;
	u32 *gscr = pmp_dev->gscr;
	काष्ठा ata_link *link;
	काष्ठा ata_device *dev;
	अचिन्हित पूर्णांक err_mask;
	u32 gscr_error, sntf;
	पूर्णांक cnt, rc;

	pmp_tries = ATA_EH_PMP_TRIES;
	ata_क्रम_each_link(link, ap, EDGE)
		link_tries[link->pmp] = ATA_EH_PMP_LINK_TRIES;

 retry:
	/* PMP attached? */
	अगर (!sata_pmp_attached(ap)) अणु
		rc = ata_eh_recover(ap, ops->prereset, ops->softreset,
				    ops->hardreset, ops->postreset, शून्य);
		अगर (rc) अणु
			ata_क्रम_each_dev(dev, &ap->link, ALL)
				ata_dev_disable(dev);
			वापस rc;
		पूर्ण

		अगर (pmp_dev->class != ATA_DEV_PMP)
			वापस 0;

		/* new PMP online */
		ata_क्रम_each_link(link, ap, EDGE)
			link_tries[link->pmp] = ATA_EH_PMP_LINK_TRIES;

		/* fall through */
	पूर्ण

	/* recover pmp */
	rc = sata_pmp_eh_recover_pmp(ap, ops->prereset, ops->softreset,
				     ops->hardreset, ops->postreset);
	अगर (rc)
		जाओ pmp_fail;

	/* PHY event notअगरication can disturb reset and other recovery
	 * operations.  Turn it off.
	 */
	अगर (gscr[SATA_PMP_GSCR_FEAT_EN] & SATA_PMP_FEAT_NOTIFY) अणु
		gscr[SATA_PMP_GSCR_FEAT_EN] &= ~SATA_PMP_FEAT_NOTIFY;

		err_mask = sata_pmp_ग_लिखो(pmp_link, SATA_PMP_GSCR_FEAT_EN,
					  gscr[SATA_PMP_GSCR_FEAT_EN]);
		अगर (err_mask) अणु
			ata_link_warn(pmp_link,
				"failed to disable NOTIFY (err_mask=0x%x)\n",
				err_mask);
			जाओ pmp_fail;
		पूर्ण
	पूर्ण

	/* handle disabled links */
	rc = sata_pmp_eh_handle_disabled_links(ap);
	अगर (rc)
		जाओ pmp_fail;

	/* recover links */
	rc = ata_eh_recover(ap, ops->pmp_prereset, ops->pmp_softreset,
			    ops->pmp_hardreset, ops->pmp_postreset, &link);
	अगर (rc)
		जाओ link_fail;

	/* clear SNotअगरication */
	rc = sata_scr_पढ़ो(&ap->link, SCR_NOTIFICATION, &sntf);
	अगर (rc == 0)
		sata_scr_ग_लिखो(&ap->link, SCR_NOTIFICATION, sntf);

	/*
	 * If LPM is active on any fan-out port, hotplug wouldn't
	 * work.  Return w/ PHY event notअगरication disabled.
	 */
	ata_क्रम_each_link(link, ap, EDGE)
		अगर (link->lpm_policy > ATA_LPM_MAX_POWER)
			वापस 0;

	/*
	 * Connection status might have changed जबतक resetting other
	 * links, enable notअगरication and check SATA_PMP_GSCR_ERROR
	 * beक्रमe वापसing.
	 */

	/* enable notअगरication */
	अगर (pmp_dev->flags & ATA_DFLAG_AN) अणु
		gscr[SATA_PMP_GSCR_FEAT_EN] |= SATA_PMP_FEAT_NOTIFY;

		err_mask = sata_pmp_ग_लिखो(pmp_link, SATA_PMP_GSCR_FEAT_EN,
					  gscr[SATA_PMP_GSCR_FEAT_EN]);
		अगर (err_mask) अणु
			ata_dev_err(pmp_dev,
				    "failed to write PMP_FEAT_EN (Emask=0x%x)\n",
				    err_mask);
			rc = -EIO;
			जाओ pmp_fail;
		पूर्ण
	पूर्ण

	/* check GSCR_ERROR */
	err_mask = sata_pmp_पढ़ो(pmp_link, SATA_PMP_GSCR_ERROR, &gscr_error);
	अगर (err_mask) अणु
		ata_dev_err(pmp_dev,
			    "failed to read PMP_GSCR_ERROR (Emask=0x%x)\n",
			    err_mask);
		rc = -EIO;
		जाओ pmp_fail;
	पूर्ण

	cnt = 0;
	ata_क्रम_each_link(link, ap, EDGE) अणु
		अगर (!(gscr_error & (1 << link->pmp)))
			जारी;

		अगर (sata_pmp_handle_link_fail(link, link_tries)) अणु
			ata_ehi_hotplugged(&link->eh_context.i);
			cnt++;
		पूर्ण अन्यथा अणु
			ata_link_warn(link,
				"PHY status changed but maxed out on retries, giving up\n");
			ata_link_warn(link,
				"Manually issue scan to resume this link\n");
		पूर्ण
	पूर्ण

	अगर (cnt) अणु
		ata_port_info(ap,
			"PMP SError.N set for some ports, repeating recovery\n");
		जाओ retry;
	पूर्ण

	वापस 0;

 link_fail:
	अगर (sata_pmp_handle_link_fail(link, link_tries)) अणु
		pmp_ehc->i.action |= ATA_EH_RESET;
		जाओ retry;
	पूर्ण

	/* fall through */
 pmp_fail:
	/* Control always ends up here after detaching PMP.  Shut up
	 * and वापस अगर we're unloading.
	 */
	अगर (ap->pflags & ATA_PFLAG_UNLOADING)
		वापस rc;

	अगर (!sata_pmp_attached(ap))
		जाओ retry;

	अगर (--pmp_tries) अणु
		pmp_ehc->i.action |= ATA_EH_RESET;
		जाओ retry;
	पूर्ण

	ata_port_err(ap, "failed to recover PMP after %d tries, giving up\n",
		     ATA_EH_PMP_TRIES);
	sata_pmp_detach(pmp_dev);
	ata_dev_disable(pmp_dev);

	वापस rc;
पूर्ण

/**
 *	sata_pmp_error_handler - करो standard error handling क्रम PMP-enabled host
 *	@ap: host port to handle error क्रम
 *
 *	Perक्रमm standard error handling sequence क्रम PMP-enabled host
 *	@ap.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
व्योम sata_pmp_error_handler(काष्ठा ata_port *ap)
अणु
	ata_eh_स्वतःpsy(ap);
	ata_eh_report(ap);
	sata_pmp_eh_recover(ap);
	ata_eh_finish(ap);
पूर्ण

EXPORT_SYMBOL_GPL(sata_pmp_port_ops);
EXPORT_SYMBOL_GPL(sata_pmp_qc_defer_cmd_चयन);
EXPORT_SYMBOL_GPL(sata_pmp_error_handler);
