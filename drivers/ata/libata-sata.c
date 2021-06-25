<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  SATA specअगरic part of ATA helper library
 *
 *  Copyright 2003-2004 Red Hat, Inc.  All rights reserved.
 *  Copyright 2003-2004 Jeff Garzik
 *  Copyright 2006 Tejun Heo <htejun@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <linux/libata.h>

#समावेश "libata.h"
#समावेश "libata-transport.h"

/* debounce timing parameters in msecs अणु पूर्णांकerval, duration, समयout पूर्ण */
स्थिर अचिन्हित दीर्घ sata_deb_timing_normal[]		= अणु   5,  100, 2000 पूर्ण;
EXPORT_SYMBOL_GPL(sata_deb_timing_normal);
स्थिर अचिन्हित दीर्घ sata_deb_timing_hotplug[]		= अणु  25,  500, 2000 पूर्ण;
EXPORT_SYMBOL_GPL(sata_deb_timing_hotplug);
स्थिर अचिन्हित दीर्घ sata_deb_timing_दीर्घ[]		= अणु 100, 2000, 5000 पूर्ण;
EXPORT_SYMBOL_GPL(sata_deb_timing_दीर्घ);

/**
 *	sata_scr_valid - test whether SCRs are accessible
 *	@link: ATA link to test SCR accessibility क्रम
 *
 *	Test whether SCRs are accessible क्रम @link.
 *
 *	LOCKING:
 *	None.
 *
 *	RETURNS:
 *	1 अगर SCRs are accessible, 0 otherwise.
 */
पूर्णांक sata_scr_valid(काष्ठा ata_link *link)
अणु
	काष्ठा ata_port *ap = link->ap;

	वापस (ap->flags & ATA_FLAG_SATA) && ap->ops->scr_पढ़ो;
पूर्ण
EXPORT_SYMBOL_GPL(sata_scr_valid);

/**
 *	sata_scr_पढ़ो - पढ़ो SCR रेजिस्टर of the specअगरied port
 *	@link: ATA link to पढ़ो SCR क्रम
 *	@reg: SCR to पढ़ो
 *	@val: Place to store पढ़ो value
 *
 *	Read SCR रेजिस्टर @reg of @link पूर्णांकo *@val.  This function is
 *	guaranteed to succeed अगर @link is ap->link, the cable type of
 *	the port is SATA and the port implements ->scr_पढ़ो.
 *
 *	LOCKING:
 *	None अगर @link is ap->link.  Kernel thपढ़ो context otherwise.
 *
 *	RETURNS:
 *	0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक sata_scr_पढ़ो(काष्ठा ata_link *link, पूर्णांक reg, u32 *val)
अणु
	अगर (ata_is_host_link(link)) अणु
		अगर (sata_scr_valid(link))
			वापस link->ap->ops->scr_पढ़ो(link, reg, val);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस sata_pmp_scr_पढ़ो(link, reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(sata_scr_पढ़ो);

/**
 *	sata_scr_ग_लिखो - ग_लिखो SCR रेजिस्टर of the specअगरied port
 *	@link: ATA link to ग_लिखो SCR क्रम
 *	@reg: SCR to ग_लिखो
 *	@val: value to ग_लिखो
 *
 *	Write @val to SCR रेजिस्टर @reg of @link.  This function is
 *	guaranteed to succeed अगर @link is ap->link, the cable type of
 *	the port is SATA and the port implements ->scr_पढ़ो.
 *
 *	LOCKING:
 *	None अगर @link is ap->link.  Kernel thपढ़ो context otherwise.
 *
 *	RETURNS:
 *	0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक sata_scr_ग_लिखो(काष्ठा ata_link *link, पूर्णांक reg, u32 val)
अणु
	अगर (ata_is_host_link(link)) अणु
		अगर (sata_scr_valid(link))
			वापस link->ap->ops->scr_ग_लिखो(link, reg, val);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस sata_pmp_scr_ग_लिखो(link, reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(sata_scr_ग_लिखो);

/**
 *	sata_scr_ग_लिखो_flush - ग_लिखो SCR रेजिस्टर of the specअगरied port and flush
 *	@link: ATA link to ग_लिखो SCR क्रम
 *	@reg: SCR to ग_लिखो
 *	@val: value to ग_लिखो
 *
 *	This function is identical to sata_scr_ग_लिखो() except that this
 *	function perक्रमms flush after writing to the रेजिस्टर.
 *
 *	LOCKING:
 *	None अगर @link is ap->link.  Kernel thपढ़ो context otherwise.
 *
 *	RETURNS:
 *	0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक sata_scr_ग_लिखो_flush(काष्ठा ata_link *link, पूर्णांक reg, u32 val)
अणु
	अगर (ata_is_host_link(link)) अणु
		पूर्णांक rc;

		अगर (sata_scr_valid(link)) अणु
			rc = link->ap->ops->scr_ग_लिखो(link, reg, val);
			अगर (rc == 0)
				rc = link->ap->ops->scr_पढ़ो(link, reg, &val);
			वापस rc;
		पूर्ण
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस sata_pmp_scr_ग_लिखो(link, reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(sata_scr_ग_लिखो_flush);

/**
 *	ata_tf_to_fis - Convert ATA taskfile to SATA FIS काष्ठाure
 *	@tf: Taskfile to convert
 *	@pmp: Port multiplier port
 *	@is_cmd: This FIS is क्रम command
 *	@fis: Buffer पूर्णांकo which data will output
 *
 *	Converts a standard ATA taskfile to a Serial ATA
 *	FIS काष्ठाure (Register - Host to Device).
 *
 *	LOCKING:
 *	Inherited from caller.
 */
व्योम ata_tf_to_fis(स्थिर काष्ठा ata_taskfile *tf, u8 pmp, पूर्णांक is_cmd, u8 *fis)
अणु
	fis[0] = 0x27;			/* Register - Host to Device FIS */
	fis[1] = pmp & 0xf;		/* Port multiplier number*/
	अगर (is_cmd)
		fis[1] |= (1 << 7);	/* bit 7 indicates Command FIS */

	fis[2] = tf->command;
	fis[3] = tf->feature;

	fis[4] = tf->lbal;
	fis[5] = tf->lbam;
	fis[6] = tf->lbah;
	fis[7] = tf->device;

	fis[8] = tf->hob_lbal;
	fis[9] = tf->hob_lbam;
	fis[10] = tf->hob_lbah;
	fis[11] = tf->hob_feature;

	fis[12] = tf->nsect;
	fis[13] = tf->hob_nsect;
	fis[14] = 0;
	fis[15] = tf->ctl;

	fis[16] = tf->auxiliary & 0xff;
	fis[17] = (tf->auxiliary >> 8) & 0xff;
	fis[18] = (tf->auxiliary >> 16) & 0xff;
	fis[19] = (tf->auxiliary >> 24) & 0xff;
पूर्ण
EXPORT_SYMBOL_GPL(ata_tf_to_fis);

/**
 *	ata_tf_from_fis - Convert SATA FIS to ATA taskfile
 *	@fis: Buffer from which data will be input
 *	@tf: Taskfile to output
 *
 *	Converts a serial ATA FIS काष्ठाure to a standard ATA taskfile.
 *
 *	LOCKING:
 *	Inherited from caller.
 */

व्योम ata_tf_from_fis(स्थिर u8 *fis, काष्ठा ata_taskfile *tf)
अणु
	tf->command	= fis[2];	/* status */
	tf->feature	= fis[3];	/* error */

	tf->lbal	= fis[4];
	tf->lbam	= fis[5];
	tf->lbah	= fis[6];
	tf->device	= fis[7];

	tf->hob_lbal	= fis[8];
	tf->hob_lbam	= fis[9];
	tf->hob_lbah	= fis[10];

	tf->nsect	= fis[12];
	tf->hob_nsect	= fis[13];
पूर्ण
EXPORT_SYMBOL_GPL(ata_tf_from_fis);

/**
 *	sata_link_debounce - debounce SATA phy status
 *	@link: ATA link to debounce SATA phy status क्रम
 *	@params: timing parameters अणु पूर्णांकerval, duration, समयout पूर्ण in msec
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Make sure SStatus of @link reaches stable state, determined by
 *	holding the same value where DET is not 1 क्रम @duration polled
 *	every @पूर्णांकerval, beक्रमe @समयout.  Timeout स्थिरraपूर्णांकs the
 *	beginning of the stable state.  Because DET माला_लो stuck at 1 on
 *	some controllers after hot unplugging, this functions रुकोs
 *	until समयout then वापसs 0 अगर DET is stable at 1.
 *
 *	@समयout is further limited by @deadline.  The sooner of the
 *	two is used.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक sata_link_debounce(काष्ठा ata_link *link, स्थिर अचिन्हित दीर्घ *params,
		       अचिन्हित दीर्घ deadline)
अणु
	अचिन्हित दीर्घ पूर्णांकerval = params[0];
	अचिन्हित दीर्घ duration = params[1];
	अचिन्हित दीर्घ last_jअगरfies, t;
	u32 last, cur;
	पूर्णांक rc;

	t = ata_deadline(jअगरfies, params[2]);
	अगर (समय_beक्रमe(t, deadline))
		deadline = t;

	अगर ((rc = sata_scr_पढ़ो(link, SCR_STATUS, &cur)))
		वापस rc;
	cur &= 0xf;

	last = cur;
	last_jअगरfies = jअगरfies;

	जबतक (1) अणु
		ata_msleep(link->ap, पूर्णांकerval);
		अगर ((rc = sata_scr_पढ़ो(link, SCR_STATUS, &cur)))
			वापस rc;
		cur &= 0xf;

		/* DET stable? */
		अगर (cur == last) अणु
			अगर (cur == 1 && समय_beक्रमe(jअगरfies, deadline))
				जारी;
			अगर (समय_after(jअगरfies,
				       ata_deadline(last_jअगरfies, duration)))
				वापस 0;
			जारी;
		पूर्ण

		/* unstable, start over */
		last = cur;
		last_jअगरfies = jअगरfies;

		/* Check deadline.  If debouncing failed, वापस
		 * -EPIPE to tell upper layer to lower link speed.
		 */
		अगर (समय_after(jअगरfies, deadline))
			वापस -EPIPE;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sata_link_debounce);

/**
 *	sata_link_resume - resume SATA link
 *	@link: ATA link to resume SATA
 *	@params: timing parameters अणु पूर्णांकerval, duration, समयout पूर्ण in msec
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Resume SATA phy @link and debounce it.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक sata_link_resume(काष्ठा ata_link *link, स्थिर अचिन्हित दीर्घ *params,
		     अचिन्हित दीर्घ deadline)
अणु
	पूर्णांक tries = ATA_LINK_RESUME_TRIES;
	u32 scontrol, serror;
	पूर्णांक rc;

	अगर ((rc = sata_scr_पढ़ो(link, SCR_CONTROL, &scontrol)))
		वापस rc;

	/*
	 * Writes to SControl someबार get ignored under certain
	 * controllers (ata_piix SIDPR).  Make sure DET actually is
	 * cleared.
	 */
	करो अणु
		scontrol = (scontrol & 0x0f0) | 0x300;
		अगर ((rc = sata_scr_ग_लिखो(link, SCR_CONTROL, scontrol)))
			वापस rc;
		/*
		 * Some PHYs react badly अगर SStatus is pounded
		 * immediately after resuming.  Delay 200ms beक्रमe
		 * debouncing.
		 */
		अगर (!(link->flags & ATA_LFLAG_NO_DB_DELAY))
			ata_msleep(link->ap, 200);

		/* is SControl restored correctly? */
		अगर ((rc = sata_scr_पढ़ो(link, SCR_CONTROL, &scontrol)))
			वापस rc;
	पूर्ण जबतक ((scontrol & 0xf0f) != 0x300 && --tries);

	अगर ((scontrol & 0xf0f) != 0x300) अणु
		ata_link_warn(link, "failed to resume link (SControl %X)\n",
			     scontrol);
		वापस 0;
	पूर्ण

	अगर (tries < ATA_LINK_RESUME_TRIES)
		ata_link_warn(link, "link resume succeeded after %d retries\n",
			      ATA_LINK_RESUME_TRIES - tries);

	अगर ((rc = sata_link_debounce(link, params, deadline)))
		वापस rc;

	/* clear SError, some PHYs require this even क्रम SRST to work */
	अगर (!(rc = sata_scr_पढ़ो(link, SCR_ERROR, &serror)))
		rc = sata_scr_ग_लिखो(link, SCR_ERROR, serror);

	वापस rc != -EINVAL ? rc : 0;
पूर्ण
EXPORT_SYMBOL_GPL(sata_link_resume);

/**
 *	sata_link_scr_lpm - manipulate SControl IPM and SPM fields
 *	@link: ATA link to manipulate SControl क्रम
 *	@policy: LPM policy to configure
 *	@spm_wakeup: initiate LPM transition to active state
 *
 *	Manipulate the IPM field of the SControl रेजिस्टर of @link
 *	according to @policy.  If @policy is ATA_LPM_MAX_POWER and
 *	@spm_wakeup is %true, the SPM field is manipulated to wake up
 *	the link.  This function also clears PHYRDY_CHG beक्रमe
 *	वापसing.
 *
 *	LOCKING:
 *	EH context.
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक sata_link_scr_lpm(काष्ठा ata_link *link, क्रमागत ata_lpm_policy policy,
		      bool spm_wakeup)
अणु
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	bool woken_up = false;
	u32 scontrol;
	पूर्णांक rc;

	rc = sata_scr_पढ़ो(link, SCR_CONTROL, &scontrol);
	अगर (rc)
		वापस rc;

	चयन (policy) अणु
	हाल ATA_LPM_MAX_POWER:
		/* disable all LPM transitions */
		scontrol |= (0x7 << 8);
		/* initiate transition to active state */
		अगर (spm_wakeup) अणु
			scontrol |= (0x4 << 12);
			woken_up = true;
		पूर्ण
		अवरोध;
	हाल ATA_LPM_MED_POWER:
		/* allow LPM to PARTIAL */
		scontrol &= ~(0x1 << 8);
		scontrol |= (0x6 << 8);
		अवरोध;
	हाल ATA_LPM_MED_POWER_WITH_DIPM:
	हाल ATA_LPM_MIN_POWER_WITH_PARTIAL:
	हाल ATA_LPM_MIN_POWER:
		अगर (ata_link_nr_enabled(link) > 0)
			/* no restrictions on LPM transitions */
			scontrol &= ~(0x7 << 8);
		अन्यथा अणु
			/* empty port, घातer off */
			scontrol &= ~0xf;
			scontrol |= (0x1 << 2);
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	rc = sata_scr_ग_लिखो(link, SCR_CONTROL, scontrol);
	अगर (rc)
		वापस rc;

	/* give the link समय to transit out of LPM state */
	अगर (woken_up)
		msleep(10);

	/* clear PHYRDY_CHG from SError */
	ehc->i.serror &= ~SERR_PHYRDY_CHG;
	वापस sata_scr_ग_लिखो(link, SCR_ERROR, SERR_PHYRDY_CHG);
पूर्ण
EXPORT_SYMBOL_GPL(sata_link_scr_lpm);

अटल पूर्णांक __sata_set_spd_needed(काष्ठा ata_link *link, u32 *scontrol)
अणु
	काष्ठा ata_link *host_link = &link->ap->link;
	u32 limit, target, spd;

	limit = link->sata_spd_limit;

	/* Don't configure करोwnstream link faster than upstream link.
	 * It करोesn't speed up anything and some PMPs choke on such
	 * configuration.
	 */
	अगर (!ata_is_host_link(link) && host_link->sata_spd)
		limit &= (1 << host_link->sata_spd) - 1;

	अगर (limit == अच_पूर्णांक_उच्च)
		target = 0;
	अन्यथा
		target = fls(limit);

	spd = (*scontrol >> 4) & 0xf;
	*scontrol = (*scontrol & ~0xf0) | ((target & 0xf) << 4);

	वापस spd != target;
पूर्ण

/**
 *	sata_set_spd_needed - is SATA spd configuration needed
 *	@link: Link in question
 *
 *	Test whether the spd limit in SControl matches
 *	@link->sata_spd_limit.  This function is used to determine
 *	whether hardreset is necessary to apply SATA spd
 *	configuration.
 *
 *	LOCKING:
 *	Inherited from caller.
 *
 *	RETURNS:
 *	1 अगर SATA spd configuration is needed, 0 otherwise.
 */
अटल पूर्णांक sata_set_spd_needed(काष्ठा ata_link *link)
अणु
	u32 scontrol;

	अगर (sata_scr_पढ़ो(link, SCR_CONTROL, &scontrol))
		वापस 1;

	वापस __sata_set_spd_needed(link, &scontrol);
पूर्ण

/**
 *	sata_set_spd - set SATA spd according to spd limit
 *	@link: Link to set SATA spd क्रम
 *
 *	Set SATA spd of @link according to sata_spd_limit.
 *
 *	LOCKING:
 *	Inherited from caller.
 *
 *	RETURNS:
 *	0 अगर spd करोesn't need to be changed, 1 अगर spd has been
 *	changed.  Negative त्रुटि_सं अगर SCR रेजिस्टरs are inaccessible.
 */
पूर्णांक sata_set_spd(काष्ठा ata_link *link)
अणु
	u32 scontrol;
	पूर्णांक rc;

	अगर ((rc = sata_scr_पढ़ो(link, SCR_CONTROL, &scontrol)))
		वापस rc;

	अगर (!__sata_set_spd_needed(link, &scontrol))
		वापस 0;

	अगर ((rc = sata_scr_ग_लिखो(link, SCR_CONTROL, scontrol)))
		वापस rc;

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(sata_set_spd);

/**
 *	sata_link_hardreset - reset link via SATA phy reset
 *	@link: link to reset
 *	@timing: timing parameters अणु पूर्णांकerval, duration, समयout पूर्ण in msec
 *	@deadline: deadline jअगरfies क्रम the operation
 *	@online: optional out parameter indicating link onlineness
 *	@check_पढ़ोy: optional callback to check link पढ़ोiness
 *
 *	SATA phy-reset @link using DET bits of SControl रेजिस्टर.
 *	After hardreset, link पढ़ोiness is रुकोed upon using
 *	ata_रुको_पढ़ोy() अगर @check_पढ़ोy is specअगरied.  LLDs are
 *	allowed to not specअगरy @check_पढ़ोy and रुको itself after this
 *	function वापसs.  Device classअगरication is LLD's
 *	responsibility.
 *
 *	*@online is set to one अगरf reset succeeded and @link is online
 *	after reset.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep)
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
पूर्णांक sata_link_hardreset(काष्ठा ata_link *link, स्थिर अचिन्हित दीर्घ *timing,
			अचिन्हित दीर्घ deadline,
			bool *online, पूर्णांक (*check_पढ़ोy)(काष्ठा ata_link *))
अणु
	u32 scontrol;
	पूर्णांक rc;

	DPRINTK("ENTER\n");

	अगर (online)
		*online = false;

	अगर (sata_set_spd_needed(link)) अणु
		/* SATA spec says nothing about how to reconfigure
		 * spd.  To be on the safe side, turn off phy during
		 * reconfiguration.  This works क्रम at least ICH7 AHCI
		 * and Sil3124.
		 */
		अगर ((rc = sata_scr_पढ़ो(link, SCR_CONTROL, &scontrol)))
			जाओ out;

		scontrol = (scontrol & 0x0f0) | 0x304;

		अगर ((rc = sata_scr_ग_लिखो(link, SCR_CONTROL, scontrol)))
			जाओ out;

		sata_set_spd(link);
	पूर्ण

	/* issue phy wake/reset */
	अगर ((rc = sata_scr_पढ़ो(link, SCR_CONTROL, &scontrol)))
		जाओ out;

	scontrol = (scontrol & 0x0f0) | 0x301;

	अगर ((rc = sata_scr_ग_लिखो_flush(link, SCR_CONTROL, scontrol)))
		जाओ out;

	/* Couldn't find anything in SATA I/II specs, but AHCI-1.1
	 * 10.4.2 says at least 1 ms.
	 */
	ata_msleep(link->ap, 1);

	/* bring link back */
	rc = sata_link_resume(link, timing, deadline);
	अगर (rc)
		जाओ out;
	/* अगर link is offline nothing more to करो */
	अगर (ata_phys_link_offline(link))
		जाओ out;

	/* Link is online.  From this poपूर्णांक, -ENODEV too is an error. */
	अगर (online)
		*online = true;

	अगर (sata_pmp_supported(link->ap) && ata_is_host_link(link)) अणु
		/* If PMP is supported, we have to करो follow-up SRST.
		 * Some PMPs करोn't send D2H Reg FIS after hardreset अगर
		 * the first port is empty.  Wait only क्रम
		 * ATA_TMOUT_PMP_SRST_WAIT.
		 */
		अगर (check_पढ़ोy) अणु
			अचिन्हित दीर्घ pmp_deadline;

			pmp_deadline = ata_deadline(jअगरfies,
						    ATA_TMOUT_PMP_SRST_WAIT);
			अगर (समय_after(pmp_deadline, deadline))
				pmp_deadline = deadline;
			ata_रुको_पढ़ोy(link, pmp_deadline, check_पढ़ोy);
		पूर्ण
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	rc = 0;
	अगर (check_पढ़ोy)
		rc = ata_रुको_पढ़ोy(link, deadline, check_पढ़ोy);
 out:
	अगर (rc && rc != -EAGAIN) अणु
		/* online is set अगरf link is online && reset succeeded */
		अगर (online)
			*online = false;
		ata_link_err(link, "COMRESET failed (errno=%d)\n", rc);
	पूर्ण
	DPRINTK("EXIT, rc=%d\n", rc);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(sata_link_hardreset);

/**
 *	ata_qc_complete_multiple - Complete multiple qcs successfully
 *	@ap: port in question
 *	@qc_active: new qc_active mask
 *
 *	Complete in-flight commands.  This functions is meant to be
 *	called from low-level driver's पूर्णांकerrupt routine to complete
 *	requests normally.  ap->qc_active and @qc_active is compared
 *	and commands are completed accordingly.
 *
 *	Always use this function when completing multiple NCQ commands
 *	from IRQ handlers instead of calling ata_qc_complete()
 *	multiple बार to keep IRQ expect status properly in sync.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	Number of completed commands on success, -त्रुटि_सं otherwise.
 */
पूर्णांक ata_qc_complete_multiple(काष्ठा ata_port *ap, u64 qc_active)
अणु
	u64 करोne_mask, ap_qc_active = ap->qc_active;
	पूर्णांक nr_करोne = 0;

	/*
	 * If the पूर्णांकernal tag is set on ap->qc_active, then we care about
	 * bit0 on the passed in qc_active mask. Move that bit up to match
	 * the पूर्णांकernal tag.
	 */
	अगर (ap_qc_active & (1ULL << ATA_TAG_INTERNAL)) अणु
		qc_active |= (qc_active & 0x01) << ATA_TAG_INTERNAL;
		qc_active ^= qc_active & 0x01;
	पूर्ण

	करोne_mask = ap_qc_active ^ qc_active;

	अगर (unlikely(करोne_mask & qc_active)) अणु
		ata_port_err(ap, "illegal qc_active transition (%08llx->%08llx)\n",
			     ap->qc_active, qc_active);
		वापस -EINVAL;
	पूर्ण

	जबतक (करोne_mask) अणु
		काष्ठा ata_queued_cmd *qc;
		अचिन्हित पूर्णांक tag = __ffs64(करोne_mask);

		qc = ata_qc_from_tag(ap, tag);
		अगर (qc) अणु
			ata_qc_complete(qc);
			nr_करोne++;
		पूर्ण
		करोne_mask &= ~(1ULL << tag);
	पूर्ण

	वापस nr_करोne;
पूर्ण
EXPORT_SYMBOL_GPL(ata_qc_complete_multiple);

/**
 *	ata_slave_link_init - initialize slave link
 *	@ap: port to initialize slave link क्रम
 *
 *	Create and initialize slave link क्रम @ap.  This enables slave
 *	link handling on the port.
 *
 *	In libata, a port contains links and a link contains devices.
 *	There is single host link but अगर a PMP is attached to it,
 *	there can be multiple fan-out links.  On SATA, there's usually
 *	a single device connected to a link but PATA and SATA
 *	controllers emulating TF based पूर्णांकerface can have two - master
 *	and slave.
 *
 *	However, there are a few controllers which करोn't fit पूर्णांकo this
 *	असलtraction too well - SATA controllers which emulate TF
 *	पूर्णांकerface with both master and slave devices but also have
 *	separate SCR रेजिस्टर sets क्रम each device.  These controllers
 *	need separate links क्रम physical link handling
 *	(e.g. onlineness, link speed) but should be treated like a
 *	traditional M/S controller क्रम everything अन्यथा (e.g. command
 *	issue, softreset).
 *
 *	slave_link is libata's way of handling this class of
 *	controllers without impacting core layer too much.  For
 *	anything other than physical link handling, the शेष host
 *	link is used क्रम both master and slave.  For physical link
 *	handling, separate @ap->slave_link is used.  All dirty details
 *	are implemented inside libata core layer.  From LLD's POV, the
 *	only dअगरference is that prereset, hardreset and postreset are
 *	called once more क्रम the slave link, so the reset sequence
 *	looks like the following.
 *
 *	prereset(M) -> prereset(S) -> hardreset(M) -> hardreset(S) ->
 *	softreset(M) -> postreset(M) -> postreset(S)
 *
 *	Note that softreset is called only क्रम the master.  Softreset
 *	resets both M/S by definition, so SRST on master should handle
 *	both (the standard method will work just fine).
 *
 *	LOCKING:
 *	Should be called beक्रमe host is रेजिस्टरed.
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक ata_slave_link_init(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_link *link;

	WARN_ON(ap->slave_link);
	WARN_ON(ap->flags & ATA_FLAG_PMP);

	link = kzalloc(माप(*link), GFP_KERNEL);
	अगर (!link)
		वापस -ENOMEM;

	ata_link_init(ap, link, 1);
	ap->slave_link = link;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_slave_link_init);

/**
 *	sata_lpm_ignore_phy_events - test अगर PHY event should be ignored
 *	@link: Link receiving the event
 *
 *	Test whether the received PHY event has to be ignored or not.
 *
 *	LOCKING:
 *	None:
 *
 *	RETURNS:
 *	True अगर the event has to be ignored.
 */
bool sata_lpm_ignore_phy_events(काष्ठा ata_link *link)
अणु
	अचिन्हित दीर्घ lpm_समयout = link->last_lpm_change +
				    msecs_to_jअगरfies(ATA_TMOUT_SPURIOUS_PHY);

	/* अगर LPM is enabled, PHYRDY करोesn't mean anything */
	अगर (link->lpm_policy > ATA_LPM_MAX_POWER)
		वापस true;

	/* ignore the first PHY event after the LPM policy changed
	 * as it is might be spurious
	 */
	अगर ((link->flags & ATA_LFLAG_CHANGED) &&
	    समय_beक्रमe(jअगरfies, lpm_समयout))
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(sata_lpm_ignore_phy_events);

अटल स्थिर अक्षर *ata_lpm_policy_names[] = अणु
	[ATA_LPM_UNKNOWN]		= "max_performance",
	[ATA_LPM_MAX_POWER]		= "max_performance",
	[ATA_LPM_MED_POWER]		= "medium_power",
	[ATA_LPM_MED_POWER_WITH_DIPM]	= "med_power_with_dipm",
	[ATA_LPM_MIN_POWER_WITH_PARTIAL] = "min_power_with_partial",
	[ATA_LPM_MIN_POWER]		= "min_power",
पूर्ण;

अटल sमाप_प्रकार ata_scsi_lpm_store(काष्ठा device *device,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(device);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);
	काष्ठा ata_link *link;
	काष्ठा ata_device *dev;
	क्रमागत ata_lpm_policy policy;
	अचिन्हित दीर्घ flags;

	/* UNKNOWN is पूर्णांकernal state, iterate from MAX_POWER */
	क्रम (policy = ATA_LPM_MAX_POWER;
	     policy < ARRAY_SIZE(ata_lpm_policy_names); policy++) अणु
		स्थिर अक्षर *name = ata_lpm_policy_names[policy];

		अगर (म_भेदन(name, buf, म_माप(name)) == 0)
			अवरोध;
	पूर्ण
	अगर (policy == ARRAY_SIZE(ata_lpm_policy_names))
		वापस -EINVAL;

	spin_lock_irqsave(ap->lock, flags);

	ata_क्रम_each_link(link, ap, EDGE) अणु
		ata_क्रम_each_dev(dev, &ap->link, ENABLED) अणु
			अगर (dev->horkage & ATA_HORKAGE_NOLPM) अणु
				count = -EOPNOTSUPP;
				जाओ out_unlock;
			पूर्ण
		पूर्ण
	पूर्ण

	ap->target_lpm_policy = policy;
	ata_port_schedule_eh(ap);
out_unlock:
	spin_unlock_irqrestore(ap->lock, flags);
	वापस count;
पूर्ण

अटल sमाप_प्रकार ata_scsi_lpm_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);

	अगर (ap->target_lpm_policy >= ARRAY_SIZE(ata_lpm_policy_names))
		वापस -EINVAL;

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n",
			ata_lpm_policy_names[ap->target_lpm_policy]);
पूर्ण
DEVICE_ATTR(link_घातer_management_policy, S_IRUGO | S_IWUSR,
	    ata_scsi_lpm_show, ata_scsi_lpm_store);
EXPORT_SYMBOL_GPL(dev_attr_link_घातer_management_policy);

अटल sमाप_प्रकार ata_ncq_prio_enable_show(काष्ठा device *device,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(device);
	काष्ठा ata_port *ap;
	काष्ठा ata_device *dev;
	bool ncq_prio_enable;
	पूर्णांक rc = 0;

	ap = ata_shost_to_port(sdev->host);

	spin_lock_irq(ap->lock);
	dev = ata_scsi_find_dev(ap, sdev);
	अगर (!dev) अणु
		rc = -ENODEV;
		जाओ unlock;
	पूर्ण

	ncq_prio_enable = dev->flags & ATA_DFLAG_NCQ_PRIO_ENABLE;

unlock:
	spin_unlock_irq(ap->lock);

	वापस rc ? rc : snम_लिखो(buf, 20, "%u\n", ncq_prio_enable);
पूर्ण

अटल sमाप_प्रकार ata_ncq_prio_enable_store(काष्ठा device *device,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(device);
	काष्ठा ata_port *ap;
	काष्ठा ata_device *dev;
	दीर्घ पूर्णांक input;
	पूर्णांक rc;

	rc = kम_से_दीर्घ(buf, 10, &input);
	अगर (rc)
		वापस rc;
	अगर ((input < 0) || (input > 1))
		वापस -EINVAL;

	ap = ata_shost_to_port(sdev->host);
	dev = ata_scsi_find_dev(ap, sdev);
	अगर (unlikely(!dev))
		वापस  -ENODEV;

	spin_lock_irq(ap->lock);
	अगर (input)
		dev->flags |= ATA_DFLAG_NCQ_PRIO_ENABLE;
	अन्यथा
		dev->flags &= ~ATA_DFLAG_NCQ_PRIO_ENABLE;

	dev->link->eh_info.action |= ATA_EH_REVALIDATE;
	dev->link->eh_info.flags |= ATA_EHI_QUIET;
	ata_port_schedule_eh(ap);
	spin_unlock_irq(ap->lock);

	ata_port_रुको_eh(ap);

	अगर (input) अणु
		spin_lock_irq(ap->lock);
		अगर (!(dev->flags & ATA_DFLAG_NCQ_PRIO)) अणु
			dev->flags &= ~ATA_DFLAG_NCQ_PRIO_ENABLE;
			rc = -EIO;
		पूर्ण
		spin_unlock_irq(ap->lock);
	पूर्ण

	वापस rc ? rc : len;
पूर्ण

DEVICE_ATTR(ncq_prio_enable, S_IRUGO | S_IWUSR,
	    ata_ncq_prio_enable_show, ata_ncq_prio_enable_store);
EXPORT_SYMBOL_GPL(dev_attr_ncq_prio_enable);

काष्ठा device_attribute *ata_ncq_sdev_attrs[] = अणु
	&dev_attr_unload_heads,
	&dev_attr_ncq_prio_enable,
	शून्य
पूर्ण;
EXPORT_SYMBOL_GPL(ata_ncq_sdev_attrs);

अटल sमाप_प्रकार
ata_scsi_em_message_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);
	अगर (ap->ops->em_store && (ap->flags & ATA_FLAG_EM))
		वापस ap->ops->em_store(ap, buf, count);
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार
ata_scsi_em_message_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);

	अगर (ap->ops->em_show && (ap->flags & ATA_FLAG_EM))
		वापस ap->ops->em_show(ap, buf);
	वापस -EINVAL;
पूर्ण
DEVICE_ATTR(em_message, S_IRUGO | S_IWUSR,
		ata_scsi_em_message_show, ata_scsi_em_message_store);
EXPORT_SYMBOL_GPL(dev_attr_em_message);

अटल sमाप_प्रकार
ata_scsi_em_message_type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(shost);

	वापस snम_लिखो(buf, 23, "%d\n", ap->em_message_type);
पूर्ण
DEVICE_ATTR(em_message_type, S_IRUGO,
		  ata_scsi_em_message_type_show, शून्य);
EXPORT_SYMBOL_GPL(dev_attr_em_message_type);

अटल sमाप_प्रकार
ata_scsi_activity_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(sdev->host);
	काष्ठा ata_device *atadev = ata_scsi_find_dev(ap, sdev);

	अगर (atadev && ap->ops->sw_activity_show &&
	    (ap->flags & ATA_FLAG_SW_ACTIVITY))
		वापस ap->ops->sw_activity_show(atadev, buf);
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार
ata_scsi_activity_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा ata_port *ap = ata_shost_to_port(sdev->host);
	काष्ठा ata_device *atadev = ata_scsi_find_dev(ap, sdev);
	क्रमागत sw_activity val;
	पूर्णांक rc;

	अगर (atadev && ap->ops->sw_activity_store &&
	    (ap->flags & ATA_FLAG_SW_ACTIVITY)) अणु
		val = simple_म_से_अदीर्घ(buf, शून्य, 0);
		चयन (val) अणु
		हाल OFF: हाल BLINK_ON: हाल BLINK_OFF:
			rc = ap->ops->sw_activity_store(atadev, val);
			अगर (!rc)
				वापस count;
			अन्यथा
				वापस rc;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण
DEVICE_ATTR(sw_activity, S_IWUSR | S_IRUGO, ata_scsi_activity_show,
			ata_scsi_activity_store);
EXPORT_SYMBOL_GPL(dev_attr_sw_activity);

/**
 *	__ata_change_queue_depth - helper क्रम ata_scsi_change_queue_depth
 *	@ap: ATA port to which the device change the queue depth
 *	@sdev: SCSI device to configure queue depth क्रम
 *	@queue_depth: new queue depth
 *
 *	libsas and libata have dअगरferent approaches क्रम associating a sdev to
 *	its ata_port.
 *
 */
पूर्णांक __ata_change_queue_depth(काष्ठा ata_port *ap, काष्ठा scsi_device *sdev,
			     पूर्णांक queue_depth)
अणु
	काष्ठा ata_device *dev;
	अचिन्हित दीर्घ flags;

	अगर (queue_depth < 1 || queue_depth == sdev->queue_depth)
		वापस sdev->queue_depth;

	dev = ata_scsi_find_dev(ap, sdev);
	अगर (!dev || !ata_dev_enabled(dev))
		वापस sdev->queue_depth;

	/* NCQ enabled? */
	spin_lock_irqsave(ap->lock, flags);
	dev->flags &= ~ATA_DFLAG_NCQ_OFF;
	अगर (queue_depth == 1 || !ata_ncq_enabled(dev)) अणु
		dev->flags |= ATA_DFLAG_NCQ_OFF;
		queue_depth = 1;
	पूर्ण
	spin_unlock_irqrestore(ap->lock, flags);

	/* limit and apply queue depth */
	queue_depth = min(queue_depth, sdev->host->can_queue);
	queue_depth = min(queue_depth, ata_id_queue_depth(dev->id));
	queue_depth = min(queue_depth, ATA_MAX_QUEUE);

	अगर (sdev->queue_depth == queue_depth)
		वापस -EINVAL;

	वापस scsi_change_queue_depth(sdev, queue_depth);
पूर्ण
EXPORT_SYMBOL_GPL(__ata_change_queue_depth);

/**
 *	ata_scsi_change_queue_depth - SCSI callback क्रम queue depth config
 *	@sdev: SCSI device to configure queue depth क्रम
 *	@queue_depth: new queue depth
 *
 *	This is libata standard hostt->change_queue_depth callback.
 *	SCSI will call पूर्णांकo this callback when user tries to set queue
 *	depth via sysfs.
 *
 *	LOCKING:
 *	SCSI layer (we करोn't care)
 *
 *	RETURNS:
 *	Newly configured queue depth.
 */
पूर्णांक ata_scsi_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक queue_depth)
अणु
	काष्ठा ata_port *ap = ata_shost_to_port(sdev->host);

	वापस __ata_change_queue_depth(ap, sdev, queue_depth);
पूर्ण
EXPORT_SYMBOL_GPL(ata_scsi_change_queue_depth);

/**
 *	ata_sas_port_alloc - Allocate port क्रम a SAS attached SATA device
 *	@host: ATA host container क्रम all SAS ports
 *	@port_info: Inक्रमmation from low-level host driver
 *	@shost: SCSI host that the scsi device is attached to
 *
 *	LOCKING:
 *	PCI/etc. bus probe sem.
 *
 *	RETURNS:
 *	ata_port poपूर्णांकer on success / शून्य on failure.
 */

काष्ठा ata_port *ata_sas_port_alloc(काष्ठा ata_host *host,
				    काष्ठा ata_port_info *port_info,
				    काष्ठा Scsi_Host *shost)
अणु
	काष्ठा ata_port *ap;

	ap = ata_port_alloc(host);
	अगर (!ap)
		वापस शून्य;

	ap->port_no = 0;
	ap->lock = &host->lock;
	ap->pio_mask = port_info->pio_mask;
	ap->mwdma_mask = port_info->mwdma_mask;
	ap->udma_mask = port_info->udma_mask;
	ap->flags |= port_info->flags;
	ap->ops = port_info->port_ops;
	ap->cbl = ATA_CBL_SATA;

	वापस ap;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_port_alloc);

/**
 *	ata_sas_port_start - Set port up क्रम dma.
 *	@ap: Port to initialize
 *
 *	Called just after data काष्ठाures क्रम each port are
 *	initialized.
 *
 *	May be used as the port_start() entry in ata_port_operations.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
पूर्णांक ata_sas_port_start(काष्ठा ata_port *ap)
अणु
	/*
	 * the port is marked as frozen at allocation समय, but अगर we करोn't
	 * have new eh, we won't thaw it
	 */
	अगर (!ap->ops->error_handler)
		ap->pflags &= ~ATA_PFLAG_FROZEN;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_port_start);

/**
 *	ata_sas_port_stop - Unकरो ata_sas_port_start()
 *	@ap: Port to shut करोwn
 *
 *	May be used as the port_stop() entry in ata_port_operations.
 *
 *	LOCKING:
 *	Inherited from caller.
 */

व्योम ata_sas_port_stop(काष्ठा ata_port *ap)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_port_stop);

/**
 * ata_sas_async_probe - simply schedule probing and वापस
 * @ap: Port to probe
 *
 * For batch scheduling of probe क्रम sas attached ata devices, assumes
 * the port has alपढ़ोy been through ata_sas_port_init()
 */
व्योम ata_sas_async_probe(काष्ठा ata_port *ap)
अणु
	__ata_port_probe(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_async_probe);

पूर्णांक ata_sas_sync_probe(काष्ठा ata_port *ap)
अणु
	वापस ata_port_probe(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_sync_probe);


/**
 *	ata_sas_port_init - Initialize a SATA device
 *	@ap: SATA port to initialize
 *
 *	LOCKING:
 *	PCI/etc. bus probe sem.
 *
 *	RETURNS:
 *	Zero on success, non-zero on error.
 */

पूर्णांक ata_sas_port_init(काष्ठा ata_port *ap)
अणु
	पूर्णांक rc = ap->ops->port_start(ap);

	अगर (rc)
		वापस rc;
	ap->prपूर्णांक_id = atomic_inc_वापस(&ata_prपूर्णांक_id);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_port_init);

पूर्णांक ata_sas_tport_add(काष्ठा device *parent, काष्ठा ata_port *ap)
अणु
	वापस ata_tport_add(parent, ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_tport_add);

व्योम ata_sas_tport_delete(काष्ठा ata_port *ap)
अणु
	ata_tport_delete(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_tport_delete);

/**
 *	ata_sas_port_destroy - Destroy a SATA port allocated by ata_sas_port_alloc
 *	@ap: SATA port to destroy
 *
 */

व्योम ata_sas_port_destroy(काष्ठा ata_port *ap)
अणु
	अगर (ap->ops->port_stop)
		ap->ops->port_stop(ap);
	kमुक्त(ap);
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_port_destroy);

/**
 *	ata_sas_slave_configure - Default slave_config routine क्रम libata devices
 *	@sdev: SCSI device to configure
 *	@ap: ATA port to which SCSI device is attached
 *
 *	RETURNS:
 *	Zero.
 */

पूर्णांक ata_sas_slave_configure(काष्ठा scsi_device *sdev, काष्ठा ata_port *ap)
अणु
	ata_scsi_sdev_config(sdev);
	ata_scsi_dev_config(sdev, ap->link.device);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_slave_configure);

/**
 *	ata_sas_queuecmd - Issue SCSI cdb to libata-managed device
 *	@cmd: SCSI command to be sent
 *	@ap:	ATA port to which the command is being sent
 *
 *	RETURNS:
 *	Return value from __ata_scsi_queuecmd() अगर @cmd can be queued,
 *	0 otherwise.
 */

पूर्णांक ata_sas_queuecmd(काष्ठा scsi_cmnd *cmd, काष्ठा ata_port *ap)
अणु
	पूर्णांक rc = 0;

	ata_scsi_dump_cdb(ap, cmd);

	अगर (likely(ata_dev_enabled(ap->link.device)))
		rc = __ata_scsi_queuecmd(cmd, ap->link.device);
	अन्यथा अणु
		cmd->result = (DID_BAD_TARGET << 16);
		cmd->scsi_करोne(cmd);
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ata_sas_queuecmd);

पूर्णांक ata_sas_allocate_tag(काष्ठा ata_port *ap)
अणु
	अचिन्हित पूर्णांक max_queue = ap->host->n_tags;
	अचिन्हित पूर्णांक i, tag;

	क्रम (i = 0, tag = ap->sas_last_tag + 1; i < max_queue; i++, tag++) अणु
		tag = tag < max_queue ? tag : 0;

		/* the last tag is reserved क्रम पूर्णांकernal command. */
		अगर (ata_tag_पूर्णांकernal(tag))
			जारी;

		अगर (!test_and_set_bit(tag, &ap->sas_tag_allocated)) अणु
			ap->sas_last_tag = tag;
			वापस tag;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

व्योम ata_sas_मुक्त_tag(अचिन्हित पूर्णांक tag, काष्ठा ata_port *ap)
अणु
	clear_bit(tag, &ap->sas_tag_allocated);
पूर्ण

/**
 *	sata_async_notअगरication - SATA async notअगरication handler
 *	@ap: ATA port where async notअगरication is received
 *
 *	Handler to be called when async notअगरication via SDB FIS is
 *	received.  This function schedules EH अगर necessary.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 *
 *	RETURNS:
 *	1 अगर EH is scheduled, 0 otherwise.
 */
पूर्णांक sata_async_notअगरication(काष्ठा ata_port *ap)
अणु
	u32 sntf;
	पूर्णांक rc;

	अगर (!(ap->flags & ATA_FLAG_AN))
		वापस 0;

	rc = sata_scr_पढ़ो(&ap->link, SCR_NOTIFICATION, &sntf);
	अगर (rc == 0)
		sata_scr_ग_लिखो(&ap->link, SCR_NOTIFICATION, sntf);

	अगर (!sata_pmp_attached(ap) || rc) अणु
		/* PMP is not attached or SNTF is not available */
		अगर (!sata_pmp_attached(ap)) अणु
			/* PMP is not attached.  Check whether ATAPI
			 * AN is configured.  If so, notअगरy media
			 * change.
			 */
			काष्ठा ata_device *dev = ap->link.device;

			अगर ((dev->class == ATA_DEV_ATAPI) &&
			    (dev->flags & ATA_DFLAG_AN))
				ata_scsi_media_change_notअगरy(dev);
			वापस 0;
		पूर्ण अन्यथा अणु
			/* PMP is attached but SNTF is not available.
			 * ATAPI async media change notअगरication is
			 * not used.  The PMP must be reporting PHY
			 * status change, schedule EH.
			 */
			ata_port_schedule_eh(ap);
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* PMP is attached and SNTF is available */
		काष्ठा ata_link *link;

		/* check and notअगरy ATAPI AN */
		ata_क्रम_each_link(link, ap, EDGE) अणु
			अगर (!(sntf & (1 << link->pmp)))
				जारी;

			अगर ((link->device->class == ATA_DEV_ATAPI) &&
			    (link->device->flags & ATA_DFLAG_AN))
				ata_scsi_media_change_notअगरy(link->device);
		पूर्ण

		/* If PMP is reporting that PHY status of some
		 * करोwnstream ports has changed, schedule EH.
		 */
		अगर (sntf & (1 << SATA_PMP_CTRL_PORT)) अणु
			ata_port_schedule_eh(ap);
			वापस 1;
		पूर्ण

		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sata_async_notअगरication);

/**
 *	ata_eh_पढ़ो_log_10h - Read log page 10h क्रम NCQ error details
 *	@dev: Device to पढ़ो log page 10h from
 *	@tag: Resulting tag of the failed command
 *	@tf: Resulting taskfile रेजिस्टरs of the failed command
 *
 *	Read log page 10h to obtain NCQ error details and clear error
 *	condition.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक ata_eh_पढ़ो_log_10h(काष्ठा ata_device *dev,
			       पूर्णांक *tag, काष्ठा ata_taskfile *tf)
अणु
	u8 *buf = dev->link->ap->sector_buf;
	अचिन्हित पूर्णांक err_mask;
	u8 csum;
	पूर्णांक i;

	err_mask = ata_पढ़ो_log_page(dev, ATA_LOG_SATA_NCQ, 0, buf, 1);
	अगर (err_mask)
		वापस -EIO;

	csum = 0;
	क्रम (i = 0; i < ATA_SECT_SIZE; i++)
		csum += buf[i];
	अगर (csum)
		ata_dev_warn(dev, "invalid checksum 0x%x on log page 10h\n",
			     csum);

	अगर (buf[0] & 0x80)
		वापस -ENOENT;

	*tag = buf[0] & 0x1f;

	tf->command = buf[2];
	tf->feature = buf[3];
	tf->lbal = buf[4];
	tf->lbam = buf[5];
	tf->lbah = buf[6];
	tf->device = buf[7];
	tf->hob_lbal = buf[8];
	tf->hob_lbam = buf[9];
	tf->hob_lbah = buf[10];
	tf->nsect = buf[12];
	tf->hob_nsect = buf[13];
	अगर (dev->class == ATA_DEV_ZAC && ata_id_has_ncq_स्वतःsense(dev->id))
		tf->auxiliary = buf[14] << 16 | buf[15] << 8 | buf[16];

	वापस 0;
पूर्ण

/**
 *	ata_eh_analyze_ncq_error - analyze NCQ error
 *	@link: ATA link to analyze NCQ error क्रम
 *
 *	Read log page 10h, determine the offending qc and acquire
 *	error status TF.  For NCQ device errors, all LLDDs have to करो
 *	is setting AC_ERR_DEV in ehi->err_mask.  This function takes
 *	care of the rest.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 */
व्योम ata_eh_analyze_ncq_error(काष्ठा ata_link *link)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_eh_context *ehc = &link->eh_context;
	काष्ठा ata_device *dev = link->device;
	काष्ठा ata_queued_cmd *qc;
	काष्ठा ata_taskfile tf;
	पूर्णांक tag, rc;

	/* अगर frozen, we can't करो much */
	अगर (ap->pflags & ATA_PFLAG_FROZEN)
		वापस;

	/* is it NCQ device error? */
	अगर (!link->sactive || !(ehc->i.err_mask & AC_ERR_DEV))
		वापस;

	/* has LLDD analyzed alपढ़ोy? */
	ata_qc_क्रम_each_raw(ap, qc, tag) अणु
		अगर (!(qc->flags & ATA_QCFLAG_FAILED))
			जारी;

		अगर (qc->err_mask)
			वापस;
	पूर्ण

	/* okay, this error is ours */
	स_रखो(&tf, 0, माप(tf));
	rc = ata_eh_पढ़ो_log_10h(dev, &tag, &tf);
	अगर (rc) अणु
		ata_link_err(link, "failed to read log page 10h (errno=%d)\n",
			     rc);
		वापस;
	पूर्ण

	अगर (!(link->sactive & (1 << tag))) अणु
		ata_link_err(link, "log page 10h reported inactive tag %d\n",
			     tag);
		वापस;
	पूर्ण

	/* we've got the perpetrator, condemn it */
	qc = __ata_qc_from_tag(ap, tag);
	स_नकल(&qc->result_tf, &tf, माप(tf));
	qc->result_tf.flags = ATA_TFLAG_ISADDR | ATA_TFLAG_LBA | ATA_TFLAG_LBA48;
	qc->err_mask |= AC_ERR_DEV | AC_ERR_NCQ;
	अगर (dev->class == ATA_DEV_ZAC &&
	    ((qc->result_tf.command & ATA_SENSE) || qc->result_tf.auxiliary)) अणु
		अक्षर sense_key, asc, ascq;

		sense_key = (qc->result_tf.auxiliary >> 16) & 0xff;
		asc = (qc->result_tf.auxiliary >> 8) & 0xff;
		ascq = qc->result_tf.auxiliary & 0xff;
		ata_scsi_set_sense(dev, qc->scsicmd, sense_key, asc, ascq);
		ata_scsi_set_sense_inक्रमmation(dev, qc->scsicmd,
					       &qc->result_tf);
		qc->flags |= ATA_QCFLAG_SENSE_VALID;
	पूर्ण

	ehc->i.err_mask &= ~AC_ERR_DEV;
पूर्ण
EXPORT_SYMBOL_GPL(ata_eh_analyze_ncq_error);
