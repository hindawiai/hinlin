<शैली गुरु>
/*
 * Copyright (c) 2000-2001 Adaptec Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * String handling code courtesy of Gerard Roudier's <groudier@club-पूर्णांकernet.fr>
 * sym driver.
 *
 * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/aic79xx_proc.c#19 $
 */
#समावेश "aic79xx_osm.h"
#समावेश "aic79xx_inline.h"

अटल व्योम	ahd_dump_target_state(काष्ठा ahd_softc *ahd,
				      काष्ठा seq_file *m,
				      u_पूर्णांक our_id, अक्षर channel,
				      u_पूर्णांक target_id);
अटल व्योम	ahd_dump_device_state(काष्ठा seq_file *m,
				      काष्ठा scsi_device *sdev);

/*
 * Table of syncrates that करोn't follow the "divisible by 4"
 * rule. This table will be expanded in future SCSI specs.
 */
अटल स्थिर काष्ठा अणु
	u_पूर्णांक period_factor;
	u_पूर्णांक period;	/* in 100ths of ns */
पूर्ण scsi_syncrates[] = अणु
	अणु 0x08, 625 पूर्ण,	/* FAST-160 */
	अणु 0x09, 1250 पूर्ण,	/* FAST-80 */
	अणु 0x0a, 2500 पूर्ण,	/* FAST-40 40MHz */
	अणु 0x0b, 3030 पूर्ण,	/* FAST-40 33MHz */
	अणु 0x0c, 5000 पूर्ण	/* FAST-20 */
पूर्ण;

/*
 * Return the frequency in kHz corresponding to the given
 * sync period factor.
 */
अटल u_पूर्णांक
ahd_calc_syncsrate(u_पूर्णांक period_factor)
अणु
	पूर्णांक i;

	/* See अगर the period is in the "exception" table */
	क्रम (i = 0; i < ARRAY_SIZE(scsi_syncrates); i++) अणु

		अगर (period_factor == scsi_syncrates[i].period_factor) अणु
			/* Period in kHz */
			वापस (100000000 / scsi_syncrates[i].period);
		पूर्ण
	पूर्ण

	/*
	 * Wasn't in the table, so use the standard
	 * 4 बार conversion.
	 */
	वापस (10000000 / (period_factor * 4 * 10));
पूर्ण

अटल व्योम
ahd_क्रमmat_transinfo(काष्ठा seq_file *m, काष्ठा ahd_transinfo *tinfo)
अणु
	u_पूर्णांक speed;
	u_पूर्णांक freq;
	u_पूर्णांक mb;

	अगर (tinfo->period == AHD_PERIOD_UNKNOWN) अणु
		seq_माला_दो(m, "Renegotiation Pending\n");
		वापस;
	पूर्ण
	speed = 3300;
	freq = 0;
	अगर (tinfo->offset != 0) अणु
		freq = ahd_calc_syncsrate(tinfo->period);
		speed = freq;
	पूर्ण
	speed *= (0x01 << tinfo->width);
	mb = speed / 1000;
	अगर (mb > 0)
		seq_म_लिखो(m, "%d.%03dMB/s transfers", mb, speed % 1000);
	अन्यथा
		seq_म_लिखो(m, "%dKB/s transfers", speed);

	अगर (freq != 0) अणु
		पूर्णांक	prपूर्णांकed_options;

		prपूर्णांकed_options = 0;
		seq_म_लिखो(m, " (%d.%03dMHz", freq / 1000, freq % 1000);
		अगर ((tinfo->ppr_options & MSG_EXT_PPR_RD_STRM) != 0) अणु
			seq_माला_दो(m, " RDSTRM");
			prपूर्णांकed_options++;
		पूर्ण
		अगर ((tinfo->ppr_options & MSG_EXT_PPR_DT_REQ) != 0) अणु
			seq_माला_दो(m, prपूर्णांकed_options ? "|DT" : " DT");
			prपूर्णांकed_options++;
		पूर्ण
		अगर ((tinfo->ppr_options & MSG_EXT_PPR_IU_REQ) != 0) अणु
			seq_माला_दो(m, prपूर्णांकed_options ? "|IU" : " IU");
			prपूर्णांकed_options++;
		पूर्ण
		अगर ((tinfo->ppr_options & MSG_EXT_PPR_RTI) != 0) अणु
			seq_माला_दो(m, prपूर्णांकed_options ? "|RTI" : " RTI");
			prपूर्णांकed_options++;
		पूर्ण
		अगर ((tinfo->ppr_options & MSG_EXT_PPR_QAS_REQ) != 0) अणु
			seq_माला_दो(m, prपूर्णांकed_options ? "|QAS" : " QAS");
			prपूर्णांकed_options++;
		पूर्ण
	पूर्ण

	अगर (tinfo->width > 0) अणु
		अगर (freq != 0) अणु
			seq_माला_दो(m, ", ");
		पूर्ण अन्यथा अणु
			seq_माला_दो(m, " (");
		पूर्ण
		seq_म_लिखो(m, "%dbit)", 8 * (0x01 << tinfo->width));
	पूर्ण अन्यथा अगर (freq != 0) अणु
		seq_अ_दो(m, ')');
	पूर्ण
	seq_अ_दो(m, '\n');
पूर्ण

अटल व्योम
ahd_dump_target_state(काष्ठा ahd_softc *ahd, काष्ठा seq_file *m,
		      u_पूर्णांक our_id, अक्षर channel, u_पूर्णांक target_id)
अणु
	काष्ठा  scsi_target *starget;
	काष्ठा	ahd_initiator_tinfo *tinfo;
	काष्ठा	ahd_पंचांगode_tstate *tstate;
	पूर्णांक	lun;

	tinfo = ahd_fetch_transinfo(ahd, channel, our_id,
				    target_id, &tstate);
	seq_म_लिखो(m, "Target %d Negotiation Settings\n", target_id);
	seq_माला_दो(m, "\tUser: ");
	ahd_क्रमmat_transinfo(m, &tinfo->user);
	starget = ahd->platक्रमm_data->starget[target_id];
	अगर (starget == शून्य)
		वापस;

	seq_माला_दो(m, "\tGoal: ");
	ahd_क्रमmat_transinfo(m, &tinfo->goal);
	seq_माला_दो(m, "\tCurr: ");
	ahd_क्रमmat_transinfo(m, &tinfo->curr);

	क्रम (lun = 0; lun < AHD_NUM_LUNS; lun++) अणु
		काष्ठा scsi_device *dev;

		dev = scsi_device_lookup_by_target(starget, lun);

		अगर (dev == शून्य)
			जारी;

		ahd_dump_device_state(m, dev);
	पूर्ण
पूर्ण

अटल व्योम
ahd_dump_device_state(काष्ठा seq_file *m, काष्ठा scsi_device *sdev)
अणु
	काष्ठा ahd_linux_device *dev = scsi_transport_device_data(sdev);

	seq_म_लिखो(m, "\tChannel %c Target %d Lun %d Settings\n",
		  sdev->sdev_target->channel + 'A',
		   sdev->sdev_target->id, (u8)sdev->lun);

	seq_म_लिखो(m, "\t\tCommands Queued %ld\n", dev->commands_issued);
	seq_म_लिखो(m, "\t\tCommands Active %d\n", dev->active);
	seq_म_लिखो(m, "\t\tCommand Openings %d\n", dev->खोलोings);
	seq_म_लिखो(m, "\t\tMax Tagged Openings %d\n", dev->maxtags);
	seq_म_लिखो(m, "\t\tDevice Queue Frozen Count %d\n", dev->qfrozen);
पूर्ण

पूर्णांक
ahd_proc_ग_लिखो_seeprom(काष्ठा Scsi_Host *shost, अक्षर *buffer, पूर्णांक length)
अणु
	काष्ठा	ahd_softc *ahd = *(काष्ठा ahd_softc **)shost->hostdata;
	ahd_mode_state saved_modes;
	पूर्णांक have_seeprom;
	u_दीर्घ s;
	पूर्णांक छोड़ोd;
	पूर्णांक written;

	/* Default to failure. */
	written = -EINVAL;
	ahd_lock(ahd, &s);
	छोड़ोd = ahd_is_छोड़ोd(ahd);
	अगर (!छोड़ोd)
		ahd_छोड़ो(ahd);

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	अगर (length != माप(काष्ठा seeprom_config)) अणु
		prपूर्णांकk("ahd_proc_write_seeprom: incorrect buffer size\n");
		जाओ करोne;
	पूर्ण

	have_seeprom = ahd_verअगरy_cksum((काष्ठा seeprom_config*)buffer);
	अगर (have_seeprom == 0) अणु
		prपूर्णांकk("ahd_proc_write_seeprom: cksum verification failed\n");
		जाओ करोne;
	पूर्ण

	have_seeprom = ahd_acquire_seeprom(ahd);
	अगर (!have_seeprom) अणु
		prपूर्णांकk("ahd_proc_write_seeprom: No Serial EEPROM\n");
		जाओ करोne;
	पूर्ण अन्यथा अणु
		u_पूर्णांक start_addr;

		अगर (ahd->seep_config == शून्य) अणु
			ahd->seep_config = kदो_स्मृति(माप(*ahd->seep_config),
						   GFP_ATOMIC);
			अगर (ahd->seep_config == शून्य) अणु
				prपूर्णांकk("aic79xx: Unable to allocate serial "
				       "eeprom buffer.  Write failing\n");
				जाओ करोne;
			पूर्ण
		पूर्ण
		prपूर्णांकk("aic79xx: Writing Serial EEPROM\n");
		start_addr = 32 * (ahd->channel - 'A');
		ahd_ग_लिखो_seeprom(ahd, (u_पूर्णांक16_t *)buffer, start_addr,
				  माप(काष्ठा seeprom_config)/2);
		ahd_पढ़ो_seeprom(ahd, (uपूर्णांक16_t *)ahd->seep_config,
				 start_addr, माप(काष्ठा seeprom_config)/2,
				 /*ByteStream*/FALSE);
		ahd_release_seeprom(ahd);
		written = length;
	पूर्ण

करोne:
	ahd_restore_modes(ahd, saved_modes);
	अगर (!छोड़ोd)
		ahd_unछोड़ो(ahd);
	ahd_unlock(ahd, &s);
	वापस (written);
पूर्ण
/*
 * Return inक्रमmation to handle /proc support क्रम the driver.
 */
पूर्णांक
ahd_linux_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा	ahd_softc *ahd = *(काष्ठा ahd_softc **)shost->hostdata;
	अक्षर	ahd_info[256];
	u_पूर्णांक	max_targ;
	u_पूर्णांक	i;

	seq_म_लिखो(m, "Adaptec AIC79xx driver version: %s\n",
		  AIC79XX_DRIVER_VERSION);
	seq_म_लिखो(m, "%s\n", ahd->description);
	ahd_controller_info(ahd, ahd_info);
	seq_म_लिखो(m, "%s\n", ahd_info);
	seq_म_लिखो(m, "Allocated SCBs: %d, SG List Length: %d\n\n",
		  ahd->scb_data.numscbs, AHD_NSEG);

	max_targ = 16;

	अगर (ahd->seep_config == शून्य)
		seq_माला_दो(m, "No Serial EEPROM\n");
	अन्यथा अणु
		seq_माला_दो(m, "Serial EEPROM:\n");
		क्रम (i = 0; i < माप(*ahd->seep_config)/2; i++) अणु
			अगर (((i % 8) == 0) && (i != 0)) अणु
				seq_अ_दो(m, '\n');
			पूर्ण
			seq_म_लिखो(m, "0x%.4x ",
				  ((uपूर्णांक16_t*)ahd->seep_config)[i]);
		पूर्ण
		seq_अ_दो(m, '\n');
	पूर्ण
	seq_अ_दो(m, '\n');

	अगर ((ahd->features & AHD_WIDE) == 0)
		max_targ = 8;

	क्रम (i = 0; i < max_targ; i++) अणु

		ahd_dump_target_state(ahd, m, ahd->our_id, 'A',
				      /*target_id*/i);
	पूर्ण
	वापस 0;
पूर्ण
