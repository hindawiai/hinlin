<शैली गुरु>
/*
 * Core routines and tables shareable across OS platक्रमms.
 *
 * Copyright (c) 1994-2002 Justin T. Gibbs.
 * Copyright (c) 2000-2002 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/aic7xxx/aic7xxx.c#155 $
 */

#समावेश "aic7xxx_osm.h"
#समावेश "aic7xxx_inline.h"
#समावेश "aicasm/aicasm_insformat.h"

/***************************** Lookup Tables **********************************/
अटल स्थिर अक्षर *स्थिर ahc_chip_names[] = अणु
	"NONE",
	"aic7770",
	"aic7850",
	"aic7855",
	"aic7859",
	"aic7860",
	"aic7870",
	"aic7880",
	"aic7895",
	"aic7895C",
	"aic7890/91",
	"aic7896/97",
	"aic7892",
	"aic7899"
पूर्ण;

/*
 * Hardware error codes.
 */
काष्ठा ahc_hard_error_entry अणु
	uपूर्णांक8_t त्रुटि_सं;
	स्थिर अक्षर *errmesg;
पूर्ण;

अटल स्थिर काष्ठा ahc_hard_error_entry ahc_hard_errors[] = अणु
	अणु ILLHADDR,	"Illegal Host Access" पूर्ण,
	अणु ILLSADDR,	"Illegal Sequencer Address referenced" पूर्ण,
	अणु ILLOPCODE,	"Illegal Opcode in sequencer program" पूर्ण,
	अणु SQPARERR,	"Sequencer Parity Error" पूर्ण,
	अणु DPARERR,	"Data-path Parity Error" पूर्ण,
	अणु MPARERR,	"Scratch or SCB Memory Parity Error" पूर्ण,
	अणु PCIERRSTAT,	"PCI Error detected" पूर्ण,
	अणु CIOPARERR,	"CIOBUS Parity Error" पूर्ण,
पूर्ण;
अटल स्थिर u_पूर्णांक num_errors = ARRAY_SIZE(ahc_hard_errors);

अटल स्थिर काष्ठा ahc_phase_table_entry ahc_phase_table[] =
अणु
	अणु P_DATAOUT,	NOP,			"in Data-out phase"	पूर्ण,
	अणु P_DATAIN,	INITIATOR_ERROR,	"in Data-in phase"	पूर्ण,
	अणु P_DATAOUT_DT,	NOP,			"in DT Data-out phase"	पूर्ण,
	अणु P_DATAIN_DT,	INITIATOR_ERROR,	"in DT Data-in phase"	पूर्ण,
	अणु P_COMMAND,	NOP,			"in Command phase"	पूर्ण,
	अणु P_MESGOUT,	NOP,			"in Message-out phase"	पूर्ण,
	अणु P_STATUS,	INITIATOR_ERROR,	"in Status phase"	पूर्ण,
	अणु P_MESGIN,	MSG_PARITY_ERROR,	"in Message-in phase"	पूर्ण,
	अणु P_BUSFREE,	NOP,			"while idle"		पूर्ण,
	अणु 0,		NOP,			"in unknown phase"	पूर्ण
पूर्ण;

/*
 * In most हालs we only wish to itterate over real phases, so
 * exclude the last element from the count.
 */
अटल स्थिर u_पूर्णांक num_phases = ARRAY_SIZE(ahc_phase_table) - 1;

/*
 * Valid SCSIRATE values.  (p. 3-17)
 * Provides a mapping of tranfer periods in ns to the proper value to
 * stick in the scsixfer reg.
 */
अटल स्थिर काष्ठा ahc_syncrate ahc_syncrates[] =
अणु
      /* ultra2    fast/ultra  period     rate */
	अणु 0x42,      0x000,      9,      "80.0" पूर्ण,
	अणु 0x03,      0x000,     10,      "40.0" पूर्ण,
	अणु 0x04,      0x000,     11,      "33.0" पूर्ण,
	अणु 0x05,      0x100,     12,      "20.0" पूर्ण,
	अणु 0x06,      0x110,     15,      "16.0" पूर्ण,
	अणु 0x07,      0x120,     18,      "13.4" पूर्ण,
	अणु 0x08,      0x000,     25,      "10.0" पूर्ण,
	अणु 0x19,      0x010,     31,      "8.0"  पूर्ण,
	अणु 0x1a,      0x020,     37,      "6.67" पूर्ण,
	अणु 0x1b,      0x030,     43,      "5.7"  पूर्ण,
	अणु 0x1c,      0x040,     50,      "5.0"  पूर्ण,
	अणु 0x00,      0x050,     56,      "4.4"  पूर्ण,
	अणु 0x00,      0x060,     62,      "4.0"  पूर्ण,
	अणु 0x00,      0x070,     68,      "3.6"  पूर्ण,
	अणु 0x00,      0x000,      0,      शून्य   पूर्ण
पूर्ण;

/* Our Sequencer Program */
#समावेश "aic7xxx_seq.h"

/**************************** Function Declarations ***************************/
अटल व्योम		ahc_क्रमce_renegotiation(काष्ठा ahc_softc *ahc,
						काष्ठा ahc_devinfo *devinfo);
अटल काष्ठा ahc_पंचांगode_tstate*
			ahc_alloc_tstate(काष्ठा ahc_softc *ahc,
					 u_पूर्णांक scsi_id, अक्षर channel);
#अगर_घोषित AHC_TARGET_MODE
अटल व्योम		ahc_मुक्त_tstate(काष्ठा ahc_softc *ahc,
					u_पूर्णांक scsi_id, अक्षर channel, पूर्णांक क्रमce);
#पूर्ण_अगर
अटल स्थिर काष्ठा ahc_syncrate*
			ahc_devlimited_syncrate(काष्ठा ahc_softc *ahc,
						काष्ठा ahc_initiator_tinfo *,
						u_पूर्णांक *period,
						u_पूर्णांक *ppr_options,
						role_t role);
अटल व्योम		ahc_update_pending_scbs(काष्ठा ahc_softc *ahc);
अटल व्योम		ahc_fetch_devinfo(काष्ठा ahc_softc *ahc,
					  काष्ठा ahc_devinfo *devinfo);
अटल व्योम		ahc_scb_devinfo(काष्ठा ahc_softc *ahc,
					काष्ठा ahc_devinfo *devinfo,
					काष्ठा scb *scb);
अटल व्योम		ahc_निश्चित_atn(काष्ठा ahc_softc *ahc);
अटल व्योम		ahc_setup_initiator_msgout(काष्ठा ahc_softc *ahc,
						   काष्ठा ahc_devinfo *devinfo,
						   काष्ठा scb *scb);
अटल व्योम		ahc_build_transfer_msg(काष्ठा ahc_softc *ahc,
					       काष्ठा ahc_devinfo *devinfo);
अटल व्योम		ahc_स्थिरruct_sdtr(काष्ठा ahc_softc *ahc,
					   काष्ठा ahc_devinfo *devinfo,
					   u_पूर्णांक period, u_पूर्णांक offset);
अटल व्योम		ahc_स्थिरruct_wdtr(काष्ठा ahc_softc *ahc,
					   काष्ठा ahc_devinfo *devinfo,
					   u_पूर्णांक bus_width);
अटल व्योम		ahc_स्थिरruct_ppr(काष्ठा ahc_softc *ahc,
					  काष्ठा ahc_devinfo *devinfo,
					  u_पूर्णांक period, u_पूर्णांक offset,
					  u_पूर्णांक bus_width, u_पूर्णांक ppr_options);
अटल व्योम		ahc_clear_msg_state(काष्ठा ahc_softc *ahc);
अटल व्योम		ahc_handle_proto_violation(काष्ठा ahc_softc *ahc);
अटल व्योम		ahc_handle_message_phase(काष्ठा ahc_softc *ahc);
प्रकार क्रमागत अणु
	AHCMSG_1B,
	AHCMSG_2B,
	AHCMSG_EXT
पूर्ण ahc_msgtype;
अटल पूर्णांक		ahc_sent_msg(काष्ठा ahc_softc *ahc, ahc_msgtype type,
				     u_पूर्णांक msgval, पूर्णांक full);
अटल पूर्णांक		ahc_parse_msg(काष्ठा ahc_softc *ahc,
				      काष्ठा ahc_devinfo *devinfo);
अटल पूर्णांक		ahc_handle_msg_reject(काष्ठा ahc_softc *ahc,
					      काष्ठा ahc_devinfo *devinfo);
अटल व्योम		ahc_handle_ign_wide_residue(काष्ठा ahc_softc *ahc,
						काष्ठा ahc_devinfo *devinfo);
अटल व्योम		ahc_reinitialize_dataptrs(काष्ठा ahc_softc *ahc);
अटल व्योम		ahc_handle_devreset(काष्ठा ahc_softc *ahc,
					    काष्ठा ahc_devinfo *devinfo,
					    cam_status status, अक्षर *message,
					    पूर्णांक verbose_level);
#अगर_घोषित AHC_TARGET_MODE
अटल व्योम		ahc_setup_target_msgin(काष्ठा ahc_softc *ahc,
					       काष्ठा ahc_devinfo *devinfo,
					       काष्ठा scb *scb);
#पूर्ण_अगर

अटल bus_dmamap_callback_t	ahc_dmamap_cb;
अटल व्योम		ahc_build_मुक्त_scb_list(काष्ठा ahc_softc *ahc);
अटल पूर्णांक		ahc_init_scbdata(काष्ठा ahc_softc *ahc);
अटल व्योम		ahc_fini_scbdata(काष्ठा ahc_softc *ahc);
अटल व्योम		ahc_qinfअगरo_requeue(काष्ठा ahc_softc *ahc,
					    काष्ठा scb *prev_scb,
					    काष्ठा scb *scb);
अटल पूर्णांक		ahc_qinfअगरo_count(काष्ठा ahc_softc *ahc);
अटल u_पूर्णांक		ahc_rem_scb_from_disc_list(काष्ठा ahc_softc *ahc,
						   u_पूर्णांक prev, u_पूर्णांक scbptr);
अटल व्योम		ahc_add_curscb_to_मुक्त_list(काष्ठा ahc_softc *ahc);
अटल u_पूर्णांक		ahc_rem_wscb(काष्ठा ahc_softc *ahc,
				     u_पूर्णांक scbpos, u_पूर्णांक prev);
अटल व्योम		ahc_reset_current_bus(काष्ठा ahc_softc *ahc);
#अगर_घोषित AHC_DUMP_SEQ
अटल व्योम		ahc_dumpseq(काष्ठा ahc_softc *ahc);
#पूर्ण_अगर
अटल पूर्णांक		ahc_loadseq(काष्ठा ahc_softc *ahc);
अटल पूर्णांक		ahc_check_patch(काष्ठा ahc_softc *ahc,
					स्थिर काष्ठा patch **start_patch,
					u_पूर्णांक start_instr, u_पूर्णांक *skip_addr);
अटल व्योम		ahc_करोwnload_instr(काष्ठा ahc_softc *ahc,
					   u_पूर्णांक instrptr, uपूर्णांक8_t *dस्थिरs);
#अगर_घोषित AHC_TARGET_MODE
अटल व्योम		ahc_queue_lstate_event(काष्ठा ahc_softc *ahc,
					       काष्ठा ahc_पंचांगode_lstate *lstate,
					       u_पूर्णांक initiator_id,
					       u_पूर्णांक event_type,
					       u_पूर्णांक event_arg);
अटल व्योम		ahc_update_scsiid(काष्ठा ahc_softc *ahc,
					  u_पूर्णांक targid_mask);
अटल पूर्णांक		ahc_handle_target_cmd(काष्ठा ahc_softc *ahc,
					      काष्ठा target_cmd *cmd);
#पूर्ण_अगर

अटल u_पूर्णांक		ahc_index_busy_tcl(काष्ठा ahc_softc *ahc, u_पूर्णांक tcl);
अटल व्योम		ahc_unbusy_tcl(काष्ठा ahc_softc *ahc, u_पूर्णांक tcl);
अटल व्योम		ahc_busy_tcl(काष्ठा ahc_softc *ahc,
				     u_पूर्णांक tcl, u_पूर्णांक busyid);

/************************** SCB and SCB queue management **********************/
अटल व्योम		ahc_run_untagged_queues(काष्ठा ahc_softc *ahc);
अटल व्योम		ahc_run_untagged_queue(काष्ठा ahc_softc *ahc,
					       काष्ठा scb_tailq *queue);

/****************************** Initialization ********************************/
अटल व्योम		 ahc_alloc_scbs(काष्ठा ahc_softc *ahc);
अटल व्योम		 ahc_shutकरोwn(व्योम *arg);

/*************************** Interrupt Services *******************************/
अटल व्योम		ahc_clear_पूर्णांकstat(काष्ठा ahc_softc *ahc);
अटल व्योम		ahc_run_qoutfअगरo(काष्ठा ahc_softc *ahc);
#अगर_घोषित AHC_TARGET_MODE
अटल व्योम		ahc_run_tqinfअगरo(काष्ठा ahc_softc *ahc, पूर्णांक छोड़ोd);
#पूर्ण_अगर
अटल व्योम		ahc_handle_brkadrपूर्णांक(काष्ठा ahc_softc *ahc);
अटल व्योम		ahc_handle_seqपूर्णांक(काष्ठा ahc_softc *ahc, u_पूर्णांक पूर्णांकstat);
अटल व्योम		ahc_handle_scsiपूर्णांक(काष्ठा ahc_softc *ahc,
					   u_पूर्णांक पूर्णांकstat);
अटल व्योम		ahc_clear_critical_section(काष्ठा ahc_softc *ahc);

/***************************** Error Recovery *********************************/
अटल व्योम		ahc_मुक्तze_devq(काष्ठा ahc_softc *ahc, काष्ठा scb *scb);
अटल पूर्णांक		ahc_पात_scbs(काष्ठा ahc_softc *ahc, पूर्णांक target,
				       अक्षर channel, पूर्णांक lun, u_पूर्णांक tag,
				       role_t role, uपूर्णांक32_t status);
अटल व्योम		ahc_calc_residual(काष्ठा ahc_softc *ahc,
					  काष्ठा scb *scb);

/*********************** Untagged Transaction Routines ************************/
अटल अंतरभूत व्योम	ahc_मुक्तze_untagged_queues(काष्ठा ahc_softc *ahc);
अटल अंतरभूत व्योम	ahc_release_untagged_queues(काष्ठा ahc_softc *ahc);

/*
 * Block our completion routine from starting the next untagged
 * transaction क्रम this target or target lun.
 */
अटल अंतरभूत व्योम
ahc_मुक्तze_untagged_queues(काष्ठा ahc_softc *ahc)
अणु
	अगर ((ahc->flags & AHC_SCB_BTT) == 0)
		ahc->untagged_queue_lock++;
पूर्ण

/*
 * Allow the next untagged transaction क्रम this target or target lun
 * to be executed.  We use a counting semaphore to allow the lock
 * to be acquired recursively.  Once the count drops to zero, the
 * transaction queues will be run.
 */
अटल अंतरभूत व्योम
ahc_release_untagged_queues(काष्ठा ahc_softc *ahc)
अणु
	अगर ((ahc->flags & AHC_SCB_BTT) == 0) अणु
		ahc->untagged_queue_lock--;
		अगर (ahc->untagged_queue_lock == 0)
			ahc_run_untagged_queues(ahc);
	पूर्ण
पूर्ण

/************************* Sequencer Execution Control ************************/
/*
 * Work around any chip bugs related to halting sequencer execution.
 * On Ultra2 controllers, we must clear the CIOBUS stretch संकेत by
 * पढ़ोing a रेजिस्टर that will set this संकेत and deनिश्चित it.
 * Without this workaround, अगर the chip is छोड़ोd, by an पूर्णांकerrupt or
 * manual छोड़ो जबतक accessing scb ram, accesses to certain रेजिस्टरs
 * will hang the प्रणाली (infinite pci retries).
 */
अटल व्योम
ahc_छोड़ो_bug_fix(काष्ठा ahc_softc *ahc)
अणु
	अगर ((ahc->features & AHC_ULTRA2) != 0)
		(व्योम)ahc_inb(ahc, CCSCBCTL);
पूर्ण

/*
 * Determine whether the sequencer has halted code execution.
 * Returns non-zero status अगर the sequencer is stopped.
 */
पूर्णांक
ahc_is_छोड़ोd(काष्ठा ahc_softc *ahc)
अणु
	वापस ((ahc_inb(ahc, HCNTRL) & PAUSE) != 0);
पूर्ण

/*
 * Request that the sequencer stop and रुको, indefinitely, क्रम it
 * to stop.  The sequencer will only acknowledge that it is छोड़ोd
 * once it has reached an inकाष्ठाion boundary and PAUSEDIS is
 * cleared in the SEQCTL रेजिस्टर.  The sequencer may use PAUSEDIS
 * क्रम critical sections.
 */
व्योम
ahc_छोड़ो(काष्ठा ahc_softc *ahc)
अणु
	ahc_outb(ahc, HCNTRL, ahc->छोड़ो);

	/*
	 * Since the sequencer can disable pausing in a critical section, we
	 * must loop until it actually stops.
	 */
	जबतक (ahc_is_छोड़ोd(ahc) == 0)
		;

	ahc_छोड़ो_bug_fix(ahc);
पूर्ण

/*
 * Allow the sequencer to जारी program execution.
 * We check here to ensure that no additional पूर्णांकerrupt
 * sources that would cause the sequencer to halt have been
 * निश्चितed.  If, क्रम example, a SCSI bus reset is detected
 * जबतक we are fielding a dअगरferent, pausing, पूर्णांकerrupt type,
 * we करोn't want to release the sequencer beक्रमe going back
 * पूर्णांकo our पूर्णांकerrupt handler and dealing with this new
 * condition.
 */
व्योम
ahc_unछोड़ो(काष्ठा ahc_softc *ahc)
अणु
	अगर ((ahc_inb(ahc, INTSTAT) & (SCSIINT | SEQINT | BRKADRINT)) == 0)
		ahc_outb(ahc, HCNTRL, ahc->unछोड़ो);
पूर्ण

/************************** Memory mapping routines ***************************/
अटल काष्ठा ahc_dma_seg *
ahc_sg_bus_to_virt(काष्ठा scb *scb, uपूर्णांक32_t sg_busaddr)
अणु
	पूर्णांक sg_index;

	sg_index = (sg_busaddr - scb->sg_list_phys)/माप(काष्ठा ahc_dma_seg);
	/* sg_list_phys poपूर्णांकs to entry 1, not 0 */
	sg_index++;

	वापस (&scb->sg_list[sg_index]);
पूर्ण

अटल uपूर्णांक32_t
ahc_sg_virt_to_bus(काष्ठा scb *scb, काष्ठा ahc_dma_seg *sg)
अणु
	पूर्णांक sg_index;

	/* sg_list_phys poपूर्णांकs to entry 1, not 0 */
	sg_index = sg - &scb->sg_list[1];

	वापस (scb->sg_list_phys + (sg_index * माप(*scb->sg_list)));
पूर्ण

अटल uपूर्णांक32_t
ahc_hscb_busaddr(काष्ठा ahc_softc *ahc, u_पूर्णांक index)
अणु
	वापस (ahc->scb_data->hscb_busaddr
		+ (माप(काष्ठा hardware_scb) * index));
पूर्ण

अटल व्योम
ahc_sync_scb(काष्ठा ahc_softc *ahc, काष्ठा scb *scb, पूर्णांक op)
अणु
	ahc_dmamap_sync(ahc, ahc->scb_data->hscb_dmat,
			ahc->scb_data->hscb_dmamap,
			/*offset*/(scb->hscb - ahc->hscbs) * माप(*scb->hscb),
			/*len*/माप(*scb->hscb), op);
पूर्ण

व्योम
ahc_sync_sglist(काष्ठा ahc_softc *ahc, काष्ठा scb *scb, पूर्णांक op)
अणु
	अगर (scb->sg_count == 0)
		वापस;

	ahc_dmamap_sync(ahc, ahc->scb_data->sg_dmat, scb->sg_map->sg_dmamap,
			/*offset*/(scb->sg_list - scb->sg_map->sg_vaddr)
				* माप(काष्ठा ahc_dma_seg),
			/*len*/माप(काष्ठा ahc_dma_seg) * scb->sg_count, op);
पूर्ण

#अगर_घोषित AHC_TARGET_MODE
अटल uपूर्णांक32_t
ahc_tarअ_लोmd_offset(काष्ठा ahc_softc *ahc, u_पूर्णांक index)
अणु
	वापस (((uपूर्णांक8_t *)&ahc->tarअ_लोmds[index]) - ahc->qoutfअगरo);
पूर्ण
#पूर्ण_अगर

/*********************** Miscellaneous Support Functions ***********************/
/*
 * Determine whether the sequencer reported a residual
 * क्रम this SCB/transaction.
 */
अटल व्योम
ahc_update_residual(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	uपूर्णांक32_t sgptr;

	sgptr = ahc_le32toh(scb->hscb->sgptr);
	अगर ((sgptr & SG_RESID_VALID) != 0)
		ahc_calc_residual(ahc, scb);
पूर्ण

/*
 * Return poपूर्णांकers to the transfer negotiation inक्रमmation
 * क्रम the specअगरied our_id/remote_id pair.
 */
काष्ठा ahc_initiator_tinfo *
ahc_fetch_transinfo(काष्ठा ahc_softc *ahc, अक्षर channel, u_पूर्णांक our_id,
		    u_पूर्णांक remote_id, काष्ठा ahc_पंचांगode_tstate **tstate)
अणु
	/*
	 * Transfer data काष्ठाures are stored from the perspective
	 * of the target role.  Since the parameters क्रम a connection
	 * in the initiator role to a given target are the same as
	 * when the roles are reversed, we pretend we are the target.
	 */
	अगर (channel == 'B')
		our_id += 8;
	*tstate = ahc->enabled_tarमाला_लो[our_id];
	वापस (&(*tstate)->transinfo[remote_id]);
पूर्ण

uपूर्णांक16_t
ahc_inw(काष्ठा ahc_softc *ahc, u_पूर्णांक port)
अणु
	uपूर्णांक16_t r = ahc_inb(ahc, port+1) << 8;
	वापस r | ahc_inb(ahc, port);
पूर्ण

व्योम
ahc_outw(काष्ठा ahc_softc *ahc, u_पूर्णांक port, u_पूर्णांक value)
अणु
	ahc_outb(ahc, port, value & 0xFF);
	ahc_outb(ahc, port+1, (value >> 8) & 0xFF);
पूर्ण

uपूर्णांक32_t
ahc_inl(काष्ठा ahc_softc *ahc, u_पूर्णांक port)
अणु
	वापस ((ahc_inb(ahc, port))
	      | (ahc_inb(ahc, port+1) << 8)
	      | (ahc_inb(ahc, port+2) << 16)
	      | (ahc_inb(ahc, port+3) << 24));
पूर्ण

व्योम
ahc_outl(काष्ठा ahc_softc *ahc, u_पूर्णांक port, uपूर्णांक32_t value)
अणु
	ahc_outb(ahc, port, (value) & 0xFF);
	ahc_outb(ahc, port+1, ((value) >> 8) & 0xFF);
	ahc_outb(ahc, port+2, ((value) >> 16) & 0xFF);
	ahc_outb(ahc, port+3, ((value) >> 24) & 0xFF);
पूर्ण

uपूर्णांक64_t
ahc_inq(काष्ठा ahc_softc *ahc, u_पूर्णांक port)
अणु
	वापस ((ahc_inb(ahc, port))
	      | (ahc_inb(ahc, port+1) << 8)
	      | (ahc_inb(ahc, port+2) << 16)
	      | (ahc_inb(ahc, port+3) << 24)
	      | (((uपूर्णांक64_t)ahc_inb(ahc, port+4)) << 32)
	      | (((uपूर्णांक64_t)ahc_inb(ahc, port+5)) << 40)
	      | (((uपूर्णांक64_t)ahc_inb(ahc, port+6)) << 48)
	      | (((uपूर्णांक64_t)ahc_inb(ahc, port+7)) << 56));
पूर्ण

व्योम
ahc_outq(काष्ठा ahc_softc *ahc, u_पूर्णांक port, uपूर्णांक64_t value)
अणु
	ahc_outb(ahc, port, value & 0xFF);
	ahc_outb(ahc, port+1, (value >> 8) & 0xFF);
	ahc_outb(ahc, port+2, (value >> 16) & 0xFF);
	ahc_outb(ahc, port+3, (value >> 24) & 0xFF);
	ahc_outb(ahc, port+4, (value >> 32) & 0xFF);
	ahc_outb(ahc, port+5, (value >> 40) & 0xFF);
	ahc_outb(ahc, port+6, (value >> 48) & 0xFF);
	ahc_outb(ahc, port+7, (value >> 56) & 0xFF);
पूर्ण

/*
 * Get a मुक्त scb. If there are none, see अगर we can allocate a new SCB.
 */
काष्ठा scb *
ahc_get_scb(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा scb *scb;

	अगर ((scb = SLIST_FIRST(&ahc->scb_data->मुक्त_scbs)) == शून्य) अणु
		ahc_alloc_scbs(ahc);
		scb = SLIST_FIRST(&ahc->scb_data->मुक्त_scbs);
		अगर (scb == शून्य)
			वापस (शून्य);
	पूर्ण
	SLIST_REMOVE_HEAD(&ahc->scb_data->मुक्त_scbs, links.sle);
	वापस (scb);
पूर्ण

/*
 * Return an SCB resource to the मुक्त list.
 */
व्योम
ahc_मुक्त_scb(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	काष्ठा hardware_scb *hscb;

	hscb = scb->hscb;
	/* Clean up क्रम the next user */
	ahc->scb_data->scbindex[hscb->tag] = शून्य;
	scb->flags = SCB_FREE;
	hscb->control = 0;

	SLIST_INSERT_HEAD(&ahc->scb_data->मुक्त_scbs, scb, links.sle);

	/* Notअगरy the OSM that a resource is now available. */
	ahc_platक्रमm_scb_मुक्त(ahc, scb);
पूर्ण

काष्ठा scb *
ahc_lookup_scb(काष्ठा ahc_softc *ahc, u_पूर्णांक tag)
अणु
	काष्ठा scb* scb;

	scb = ahc->scb_data->scbindex[tag];
	अगर (scb != शून्य)
		ahc_sync_scb(ahc, scb,
			     BUS_DMASYNC_POSTREAD|BUS_DMASYNC_POSTWRITE);
	वापस (scb);
पूर्ण

अटल व्योम
ahc_swap_with_next_hscb(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	काष्ठा hardware_scb *q_hscb;
	u_पूर्णांक  saved_tag;

	/*
	 * Our queuing method is a bit tricky.  The card
	 * knows in advance which HSCB to करोwnload, and we
	 * can't disappoपूर्णांक it.  To achieve this, the next
	 * SCB to करोwnload is saved off in ahc->next_queued_scb.
	 * When we are called to queue "an arbitrary scb",
	 * we copy the contents of the incoming HSCB to the one
	 * the sequencer knows about, swap HSCB poपूर्णांकers and
	 * finally assign the SCB to the tag indexed location
	 * in the scb_array.  This makes sure that we can still
	 * locate the correct SCB by SCB_TAG.
	 */
	q_hscb = ahc->next_queued_scb->hscb;
	saved_tag = q_hscb->tag;
	स_नकल(q_hscb, scb->hscb, माप(*scb->hscb));
	अगर ((scb->flags & SCB_CDB32_PTR) != 0) अणु
		q_hscb->shared_data.cdb_ptr =
		    ahc_htole32(ahc_hscb_busaddr(ahc, q_hscb->tag)
			      + दुरत्व(काष्ठा hardware_scb, cdb32));
	पूर्ण
	q_hscb->tag = saved_tag;
	q_hscb->next = scb->hscb->tag;

	/* Now swap HSCB poपूर्णांकers. */
	ahc->next_queued_scb->hscb = scb->hscb;
	scb->hscb = q_hscb;

	/* Now define the mapping from tag to SCB in the scbindex */
	ahc->scb_data->scbindex[scb->hscb->tag] = scb;
पूर्ण

/*
 * Tell the sequencer about a new transaction to execute.
 */
व्योम
ahc_queue_scb(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	ahc_swap_with_next_hscb(ahc, scb);

	अगर (scb->hscb->tag == SCB_LIST_शून्य
	 || scb->hscb->next == SCB_LIST_शून्य)
		panic("Attempt to queue invalid SCB tag %x:%x\n",
		      scb->hscb->tag, scb->hscb->next);

	/*
	 * Setup data "oddness".
	 */
	scb->hscb->lun &= LID;
	अगर (ahc_get_transfer_length(scb) & 0x1)
		scb->hscb->lun |= SCB_XFERLEN_ODD;

	/*
	 * Keep a history of SCBs we've करोwnloaded in the qinfअगरo.
	 */
	ahc->qinfअगरo[ahc->qinfअगरonext++] = scb->hscb->tag;

	/*
	 * Make sure our data is consistent from the
	 * perspective of the adapter.
	 */
	ahc_sync_scb(ahc, scb, BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);

	/* Tell the adapter about the newly queued SCB */
	अगर ((ahc->features & AHC_QUEUE_REGS) != 0) अणु
		ahc_outb(ahc, HNSCB_QOFF, ahc->qinfअगरonext);
	पूर्ण अन्यथा अणु
		अगर ((ahc->features & AHC_AUTOPAUSE) == 0)
			ahc_छोड़ो(ahc);
		ahc_outb(ahc, KERNEL_QINPOS, ahc->qinfअगरonext);
		अगर ((ahc->features & AHC_AUTOPAUSE) == 0)
			ahc_unछोड़ो(ahc);
	पूर्ण
पूर्ण

काष्ठा scsi_sense_data *
ahc_get_sense_buf(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	पूर्णांक offset;

	offset = scb - ahc->scb_data->scbarray;
	वापस (&ahc->scb_data->sense[offset]);
पूर्ण

अटल uपूर्णांक32_t
ahc_get_sense_bufaddr(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	पूर्णांक offset;

	offset = scb - ahc->scb_data->scbarray;
	वापस (ahc->scb_data->sense_busaddr
	      + (offset * माप(काष्ठा scsi_sense_data)));
पूर्ण

/************************** Interrupt Processing ******************************/
अटल व्योम
ahc_sync_qoutfअगरo(काष्ठा ahc_softc *ahc, पूर्णांक op)
अणु
	ahc_dmamap_sync(ahc, ahc->shared_data_dmat, ahc->shared_data_dmamap,
			/*offset*/0, /*len*/256, op);
पूर्ण

अटल व्योम
ahc_sync_tqinfअगरo(काष्ठा ahc_softc *ahc, पूर्णांक op)
अणु
#अगर_घोषित AHC_TARGET_MODE
	अगर ((ahc->flags & AHC_TARGETROLE) != 0) अणु
		ahc_dmamap_sync(ahc, ahc->shared_data_dmat,
				ahc->shared_data_dmamap,
				ahc_tarअ_लोmd_offset(ahc, 0),
				माप(काष्ठा target_cmd) * AHC_TMODE_CMDS,
				op);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * See अगर the firmware has posted any completed commands
 * पूर्णांकo our in-core command complete fअगरos.
 */
#घोषणा AHC_RUN_QOUTFIFO 0x1
#घोषणा AHC_RUN_TQINFIFO 0x2
अटल u_पूर्णांक
ahc_check_cmdcmpltqueues(काष्ठा ahc_softc *ahc)
अणु
	u_पूर्णांक retval;

	retval = 0;
	ahc_dmamap_sync(ahc, ahc->shared_data_dmat, ahc->shared_data_dmamap,
			/*offset*/ahc->qoutfअगरonext, /*len*/1,
			BUS_DMASYNC_POSTREAD);
	अगर (ahc->qoutfअगरo[ahc->qoutfअगरonext] != SCB_LIST_शून्य)
		retval |= AHC_RUN_QOUTFIFO;
#अगर_घोषित AHC_TARGET_MODE
	अगर ((ahc->flags & AHC_TARGETROLE) != 0
	 && (ahc->flags & AHC_TQINFIFO_BLOCKED) == 0) अणु
		ahc_dmamap_sync(ahc, ahc->shared_data_dmat,
				ahc->shared_data_dmamap,
				ahc_tarअ_लोmd_offset(ahc, ahc->tqinfअगरofnext),
				/*len*/माप(काष्ठा target_cmd),
				BUS_DMASYNC_POSTREAD);
		अगर (ahc->tarअ_लोmds[ahc->tqinfअगरonext].cmd_valid != 0)
			retval |= AHC_RUN_TQINFIFO;
	पूर्ण
#पूर्ण_अगर
	वापस (retval);
पूर्ण

/*
 * Catch an पूर्णांकerrupt from the adapter
 */
पूर्णांक
ahc_पूर्णांकr(काष्ठा ahc_softc *ahc)
अणु
	u_पूर्णांक	पूर्णांकstat;

	अगर ((ahc->छोड़ो & INTEN) == 0) अणु
		/*
		 * Our पूर्णांकerrupt is not enabled on the chip
		 * and may be disabled क्रम re-entrancy reasons,
		 * so just वापस.  This is likely just a shared
		 * पूर्णांकerrupt.
		 */
		वापस (0);
	पूर्ण
	/*
	 * Instead of directly पढ़ोing the पूर्णांकerrupt status रेजिस्टर,
	 * infer the cause of the पूर्णांकerrupt by checking our in-core
	 * completion queues.  This aव्योमs a costly PCI bus पढ़ो in
	 * most हालs.
	 */
	अगर ((ahc->flags & (AHC_ALL_INTERRUPTS|AHC_EDGE_INTERRUPT)) == 0
	 && (ahc_check_cmdcmpltqueues(ahc) != 0))
		पूर्णांकstat = CMDCMPLT;
	अन्यथा अणु
		पूर्णांकstat = ahc_inb(ahc, INTSTAT);
	पूर्ण

	अगर ((पूर्णांकstat & INT_PEND) == 0) अणु
#अगर AHC_PCI_CONFIG > 0
		अगर (ahc->unsolicited_पूर्णांकs > 500) अणु
			ahc->unsolicited_पूर्णांकs = 0;
			अगर ((ahc->chip & AHC_PCI) != 0
			 && (ahc_inb(ahc, ERROR) & PCIERRSTAT) != 0)
				ahc->bus_पूर्णांकr(ahc);
		पूर्ण
#पूर्ण_अगर
		ahc->unsolicited_पूर्णांकs++;
		वापस (0);
	पूर्ण
	ahc->unsolicited_पूर्णांकs = 0;

	अगर (पूर्णांकstat & CMDCMPLT) अणु
		ahc_outb(ahc, CLRINT, CLRCMDINT);

		/*
		 * Ensure that the chip sees that we've cleared
		 * this पूर्णांकerrupt beक्रमe we walk the output fअगरo.
		 * Otherwise, we may, due to posted bus ग_लिखोs,
		 * clear the पूर्णांकerrupt after we finish the scan,
		 * and after the sequencer has added new entries
		 * and निश्चितed the पूर्णांकerrupt again.
		 */
		ahc_flush_device_ग_लिखोs(ahc);
		ahc_run_qoutfअगरo(ahc);
#अगर_घोषित AHC_TARGET_MODE
		अगर ((ahc->flags & AHC_TARGETROLE) != 0)
			ahc_run_tqinfअगरo(ahc, /*छोड़ोd*/FALSE);
#पूर्ण_अगर
	पूर्ण

	/*
	 * Handle statuses that may invalidate our cached
	 * copy of INTSTAT separately.
	 */
	अगर (पूर्णांकstat == 0xFF && (ahc->features & AHC_REMOVABLE) != 0) अणु
		/* Hot eject.  Do nothing */
	पूर्ण अन्यथा अगर (पूर्णांकstat & BRKADRINT) अणु
		ahc_handle_brkadrपूर्णांक(ahc);
	पूर्ण अन्यथा अगर ((पूर्णांकstat & (SEQINT|SCSIINT)) != 0) अणु

		ahc_छोड़ो_bug_fix(ahc);

		अगर ((पूर्णांकstat & SEQINT) != 0)
			ahc_handle_seqपूर्णांक(ahc, पूर्णांकstat);

		अगर ((पूर्णांकstat & SCSIINT) != 0)
			ahc_handle_scsiपूर्णांक(ahc, पूर्णांकstat);
	पूर्ण
	वापस (1);
पूर्ण

/************************* Sequencer Execution Control ************************/
/*
 * Restart the sequencer program from address zero
 */
अटल व्योम
ahc_restart(काष्ठा ahc_softc *ahc)
अणु
	uपूर्णांक8_t	sblkctl;

	ahc_छोड़ो(ahc);

	/* No more pending messages. */
	ahc_clear_msg_state(ahc);

	ahc_outb(ahc, SCSISIGO, 0);		/* De-निश्चित BSY */
	ahc_outb(ahc, MSG_OUT, NOP);	/* No message to send */
	ahc_outb(ahc, SXFRCTL1, ahc_inb(ahc, SXFRCTL1) & ~BITBUCKET);
	ahc_outb(ahc, LASTPHASE, P_BUSFREE);
	ahc_outb(ahc, SAVED_SCSIID, 0xFF);
	ahc_outb(ahc, SAVED_LUN, 0xFF);

	/*
	 * Ensure that the sequencer's idea of TQINPOS
	 * matches our own.  The sequencer increments TQINPOS
	 * only after it sees a DMA complete and a reset could
	 * occur beक्रमe the increment leaving the kernel to believe
	 * the command arrived but the sequencer to not.
	 */
	ahc_outb(ahc, TQINPOS, ahc->tqinfअगरonext);

	/* Always allow reselection */
	ahc_outb(ahc, SCSISEQ,
		 ahc_inb(ahc, SCSISEQ_TEMPLATE) & (ENSELI|ENRSELI|ENAUTOATNP));
	अगर ((ahc->features & AHC_CMD_CHAN) != 0) अणु
		/* Ensure that no DMA operations are in progress */
		ahc_outb(ahc, CCSCBCNT, 0);
		ahc_outb(ahc, CCSGCTL, 0);
		ahc_outb(ahc, CCSCBCTL, 0);
	पूर्ण
	/*
	 * If we were in the process of DMA'ing SCB data पूर्णांकo
	 * an SCB, replace that SCB on the मुक्त list.  This prevents
	 * an SCB leak.
	 */
	अगर ((ahc_inb(ahc, SEQ_FLAGS2) & SCB_DMA) != 0) अणु
		ahc_add_curscb_to_मुक्त_list(ahc);
		ahc_outb(ahc, SEQ_FLAGS2,
			 ahc_inb(ahc, SEQ_FLAGS2) & ~SCB_DMA);
	पूर्ण

	/*
	 * Clear any pending sequencer पूर्णांकerrupt.  It is no
	 * दीर्घer relevant since we're resetting the Program
	 * Counter.
	 */
	ahc_outb(ahc, CLRINT, CLRSEQINT);

	ahc_outb(ahc, MWI_RESIDUAL, 0);
	ahc_outb(ahc, SEQCTL, ahc->seqctl);
	ahc_outb(ahc, SEQADDR0, 0);
	ahc_outb(ahc, SEQADDR1, 0);

	/*
	 * Take the LED out of diagnostic mode on PM resume, too
	 */
	sblkctl = ahc_inb(ahc, SBLKCTL);
	ahc_outb(ahc, SBLKCTL, (sblkctl & ~(DIAGLEDEN|DIAGLEDON)));

	ahc_unछोड़ो(ahc);
पूर्ण

/************************* Input/Output Queues ********************************/
अटल व्योम
ahc_run_qoutfअगरo(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा scb *scb;
	u_पूर्णांक  scb_index;

	ahc_sync_qoutfअगरo(ahc, BUS_DMASYNC_POSTREAD);
	जबतक (ahc->qoutfअगरo[ahc->qoutfअगरonext] != SCB_LIST_शून्य) अणु

		scb_index = ahc->qoutfअगरo[ahc->qoutfअगरonext];
		अगर ((ahc->qoutfअगरonext & 0x03) == 0x03) अणु
			u_पूर्णांक modnext;

			/*
			 * Clear 32bits of QOUTFIFO at a समय
			 * so that we करोn't clobber an incoming
			 * byte DMA to the array on architectures
			 * that only support 32bit load and store
			 * operations.
			 */
			modnext = ahc->qoutfअगरonext & ~0x3;
			*((uपूर्णांक32_t *)(&ahc->qoutfअगरo[modnext])) = 0xFFFFFFFFUL;
			ahc_dmamap_sync(ahc, ahc->shared_data_dmat,
					ahc->shared_data_dmamap,
					/*offset*/modnext, /*len*/4,
					BUS_DMASYNC_PREREAD);
		पूर्ण
		ahc->qoutfअगरonext++;

		scb = ahc_lookup_scb(ahc, scb_index);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("%s: WARNING no command for scb %d "
			       "(cmdcmplt)\nQOUTPOS = %d\n",
			       ahc_name(ahc), scb_index,
			       (ahc->qoutfअगरonext - 1) & 0xFF);
			जारी;
		पूर्ण

		/*
		 * Save off the residual
		 * अगर there is one.
		 */
		ahc_update_residual(ahc, scb);
		ahc_करोne(ahc, scb);
	पूर्ण
पूर्ण

अटल व्योम
ahc_run_untagged_queues(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		ahc_run_untagged_queue(ahc, &ahc->untagged_queues[i]);
पूर्ण

अटल व्योम
ahc_run_untagged_queue(काष्ठा ahc_softc *ahc, काष्ठा scb_tailq *queue)
अणु
	काष्ठा scb *scb;

	अगर (ahc->untagged_queue_lock != 0)
		वापस;

	अगर ((scb = TAILQ_FIRST(queue)) != शून्य
	 && (scb->flags & SCB_ACTIVE) == 0) अणु
		scb->flags |= SCB_ACTIVE;
		ahc_queue_scb(ahc, scb);
	पूर्ण
पूर्ण

/************************* Interrupt Handling *********************************/
अटल व्योम
ahc_handle_brkadrपूर्णांक(काष्ठा ahc_softc *ahc)
अणु
	/*
	 * We upset the sequencer :-(
	 * Lookup the error message
	 */
	पूर्णांक i;
	पूर्णांक error;

	error = ahc_inb(ahc, ERROR);
	क्रम (i = 0; error != 1 && i < num_errors; i++)
		error >>= 1;
	prपूर्णांकk("%s: brkadrint, %s at seqaddr = 0x%x\n",
	       ahc_name(ahc), ahc_hard_errors[i].errmesg,
	       ahc_inb(ahc, SEQADDR0) |
	       (ahc_inb(ahc, SEQADDR1) << 8));

	ahc_dump_card_state(ahc);

	/* Tell everyone that this HBA is no दीर्घer available */
	ahc_पात_scbs(ahc, CAM_TARGET_WILDCARD, ALL_CHANNELS,
		       CAM_LUN_WILDCARD, SCB_LIST_शून्य, ROLE_UNKNOWN,
		       CAM_NO_HBA);

	/* Disable all पूर्णांकerrupt sources by resetting the controller */
	ahc_shutकरोwn(ahc);
पूर्ण

अटल व्योम
ahc_handle_seqपूर्णांक(काष्ठा ahc_softc *ahc, u_पूर्णांक पूर्णांकstat)
अणु
	काष्ठा scb *scb;
	काष्ठा ahc_devinfo devinfo;

	ahc_fetch_devinfo(ahc, &devinfo);

	/*
	 * Clear the upper byte that holds SEQINT status
	 * codes and clear the SEQINT bit. We will unछोड़ो
	 * the sequencer, अगर appropriate, after servicing
	 * the request.
	 */
	ahc_outb(ahc, CLRINT, CLRSEQINT);
	चयन (पूर्णांकstat & SEQINT_MASK) अणु
	हाल BAD_STATUS:
	अणु
		u_पूर्णांक  scb_index;
		काष्ठा hardware_scb *hscb;

		/*
		 * Set the शेष वापस value to 0 (करोn't
		 * send sense).  The sense code will change
		 * this अगर needed.
		 */
		ahc_outb(ahc, RETURN_1, 0);

		/*
		 * The sequencer will notअगरy us when a command
		 * has an error that would be of पूर्णांकerest to
		 * the kernel.  This allows us to leave the sequencer
		 * running in the common हाल of command completes
		 * without error.  The sequencer will alपढ़ोy have
		 * dma'd the SCB back up to us, so we can reference
		 * the in kernel copy directly.
		 */
		scb_index = ahc_inb(ahc, SCB_TAG);
		scb = ahc_lookup_scb(ahc, scb_index);
		अगर (scb == शून्य) अणु
			ahc_prपूर्णांक_devinfo(ahc, &devinfo);
			prपूर्णांकk("ahc_intr - referenced scb "
			       "not valid during seqint 0x%x scb(%d)\n",
			       पूर्णांकstat, scb_index);
			ahc_dump_card_state(ahc);
			panic("for safety");
			जाओ unछोड़ो;
		पूर्ण

		hscb = scb->hscb;

		/* Don't want to clobber the original sense code */
		अगर ((scb->flags & SCB_SENSE) != 0) अणु
			/*
			 * Clear the SCB_SENSE Flag and have
			 * the sequencer करो a normal command
			 * complete.
			 */
			scb->flags &= ~SCB_SENSE;
			ahc_set_transaction_status(scb, CAM_AUTOSENSE_FAIL);
			अवरोध;
		पूर्ण
		ahc_set_transaction_status(scb, CAM_SCSI_STATUS_ERROR);
		/* Freeze the queue until the client sees the error. */
		ahc_मुक्तze_devq(ahc, scb);
		ahc_मुक्तze_scb(scb);
		ahc_set_scsi_status(scb, hscb->shared_data.status.scsi_status);
		चयन (hscb->shared_data.status.scsi_status) अणु
		हाल SAM_STAT_GOOD:
			prपूर्णांकk("%s: Interrupted for status of 0???\n",
			       ahc_name(ahc));
			अवरोध;
		हाल SAM_STAT_COMMAND_TERMINATED:
		हाल SAM_STAT_CHECK_CONDITION:
		अणु
			काष्ठा ahc_dma_seg *sg;
			काष्ठा scsi_sense *sc;
			काष्ठा ahc_initiator_tinfo *targ_info;
			काष्ठा ahc_पंचांगode_tstate *tstate;
			काष्ठा ahc_transinfo *tinfo;
#अगर_घोषित AHC_DEBUG
			अगर (ahc_debug & AHC_SHOW_SENSE) अणु
				ahc_prपूर्णांक_path(ahc, scb);
				prपूर्णांकk("SCB %d: requests Check Status\n",
				       scb->hscb->tag);
			पूर्ण
#पूर्ण_अगर

			अगर (ahc_perक्रमm_स्वतःsense(scb) == 0)
				अवरोध;

			targ_info = ahc_fetch_transinfo(ahc,
							devinfo.channel,
							devinfo.our_scsiid,
							devinfo.target,
							&tstate);
			tinfo = &targ_info->curr;
			sg = scb->sg_list;
			sc = (काष्ठा scsi_sense *)(&hscb->shared_data.cdb);
			/*
			 * Save off the residual अगर there is one.
			 */
			ahc_update_residual(ahc, scb);
#अगर_घोषित AHC_DEBUG
			अगर (ahc_debug & AHC_SHOW_SENSE) अणु
				ahc_prपूर्णांक_path(ahc, scb);
				prपूर्णांकk("Sending Sense\n");
			पूर्ण
#पूर्ण_अगर
			sg->addr = ahc_get_sense_bufaddr(ahc, scb);
			sg->len = ahc_get_sense_bufsize(ahc, scb);
			sg->len |= AHC_DMA_LAST_SEG;

			/* Fixup byte order */
			sg->addr = ahc_htole32(sg->addr);
			sg->len = ahc_htole32(sg->len);

			sc->opcode = REQUEST_SENSE;
			sc->byte2 = 0;
			अगर (tinfo->protocol_version <= SCSI_REV_2
			 && SCB_GET_LUN(scb) < 8)
				sc->byte2 = SCB_GET_LUN(scb) << 5;
			sc->unused[0] = 0;
			sc->unused[1] = 0;
			sc->length = sg->len;
			sc->control = 0;

			/*
			 * We can't allow the target to disconnect.
			 * This will be an untagged transaction and
			 * having the target disconnect will make this
			 * transaction indestinguishable from outstanding
			 * tagged transactions.
			 */
			hscb->control = 0;

			/*
			 * This request sense could be because the
			 * the device lost घातer or in some other
			 * way has lost our transfer negotiations.
			 * Renegotiate अगर appropriate.  Unit attention
			 * errors will be reported beक्रमe any data
			 * phases occur.
			 */
			अगर (ahc_get_residual(scb)
			    == ahc_get_transfer_length(scb)) अणु
				ahc_update_neg_request(ahc, &devinfo,
						       tstate, targ_info,
						       AHC_NEG_IF_NON_ASYNC);
			पूर्ण
			अगर (tstate->स्वतः_negotiate & devinfo.target_mask) अणु
				hscb->control |= MK_MESSAGE;
				scb->flags &= ~SCB_NEGOTIATE;
				scb->flags |= SCB_AUTO_NEGOTIATE;
			पूर्ण
			hscb->cdb_len = माप(*sc);
			hscb->dataptr = sg->addr;
			hscb->datacnt = sg->len;
			hscb->sgptr = scb->sg_list_phys | SG_FULL_RESID;
			hscb->sgptr = ahc_htole32(hscb->sgptr);
			scb->sg_count = 1;
			scb->flags |= SCB_SENSE;
			ahc_qinfअगरo_requeue_tail(ahc, scb);
			ahc_outb(ahc, RETURN_1, SEND_SENSE);
			/*
			 * Ensure we have enough समय to actually
			 * retrieve the sense.
			 */
			ahc_scb_समयr_reset(scb, 5 * 1000000);
			अवरोध;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल NO_MATCH:
	अणु
		/* Ensure we करोn't leave the selection hardware on */
		ahc_outb(ahc, SCSISEQ,
			 ahc_inb(ahc, SCSISEQ) & (ENSELI|ENRSELI|ENAUTOATNP));

		prपूर्णांकk("%s:%c:%d: no active SCB for reconnecting "
		       "target - issuing BUS DEVICE RESET\n",
		       ahc_name(ahc), devinfo.channel, devinfo.target);
		prपूर्णांकk("SAVED_SCSIID == 0x%x, SAVED_LUN == 0x%x, "
		       "ARG_1 == 0x%x ACCUM = 0x%x\n",
		       ahc_inb(ahc, SAVED_SCSIID), ahc_inb(ahc, SAVED_LUN),
		       ahc_inb(ahc, ARG_1), ahc_inb(ahc, ACCUM));
		prपूर्णांकk("SEQ_FLAGS == 0x%x, SCBPTR == 0x%x, BTT == 0x%x, "
		       "SINDEX == 0x%x\n",
		       ahc_inb(ahc, SEQ_FLAGS), ahc_inb(ahc, SCBPTR),
		       ahc_index_busy_tcl(ahc,
			    BUILD_TCL(ahc_inb(ahc, SAVED_SCSIID),
				      ahc_inb(ahc, SAVED_LUN))),
		       ahc_inb(ahc, SINDEX));
		prपूर्णांकk("SCSIID == 0x%x, SCB_SCSIID == 0x%x, SCB_LUN == 0x%x, "
		       "SCB_TAG == 0x%x, SCB_CONTROL == 0x%x\n",
		       ahc_inb(ahc, SCSIID), ahc_inb(ahc, SCB_SCSIID),
		       ahc_inb(ahc, SCB_LUN), ahc_inb(ahc, SCB_TAG),
		       ahc_inb(ahc, SCB_CONTROL));
		prपूर्णांकk("SCSIBUSL == 0x%x, SCSISIGI == 0x%x\n",
		       ahc_inb(ahc, SCSIBUSL), ahc_inb(ahc, SCSISIGI));
		prपूर्णांकk("SXFRCTL0 == 0x%x\n", ahc_inb(ahc, SXFRCTL0));
		prपूर्णांकk("SEQCTL == 0x%x\n", ahc_inb(ahc, SEQCTL));
		ahc_dump_card_state(ahc);
		ahc->msgout_buf[0] = TARGET_RESET;
		ahc->msgout_len = 1;
		ahc->msgout_index = 0;
		ahc->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
		ahc_outb(ahc, MSG_OUT, HOST_MSG);
		ahc_निश्चित_atn(ahc);
		अवरोध;
	पूर्ण
	हाल SEND_REJECT:
	अणु
		u_पूर्णांक rejbyte = ahc_inb(ahc, ACCUM);
		prपूर्णांकk("%s:%c:%d: Warning - unknown message received from "
		       "target (0x%x).  Rejecting\n",
		       ahc_name(ahc), devinfo.channel, devinfo.target, rejbyte);
		अवरोध;
	पूर्ण
	हाल PROTO_VIOLATION:
	अणु
		ahc_handle_proto_violation(ahc);
		अवरोध;
	पूर्ण
	हाल IGN_WIDE_RES:
		ahc_handle_ign_wide_residue(ahc, &devinfo);
		अवरोध;
	हाल PDATA_REINIT:
		ahc_reinitialize_dataptrs(ahc);
		अवरोध;
	हाल BAD_PHASE:
	अणु
		u_पूर्णांक lastphase;

		lastphase = ahc_inb(ahc, LASTPHASE);
		prपूर्णांकk("%s:%c:%d: unknown scsi bus phase %x, "
		       "lastphase = 0x%x.  Attempting to continue\n",
		       ahc_name(ahc), devinfo.channel, devinfo.target,
		       lastphase, ahc_inb(ahc, SCSISIGI));
		अवरोध;
	पूर्ण
	हाल MISSED_BUSFREE:
	अणु
		u_पूर्णांक lastphase;

		lastphase = ahc_inb(ahc, LASTPHASE);
		prपूर्णांकk("%s:%c:%d: Missed busfree. "
		       "Lastphase = 0x%x, Curphase = 0x%x\n",
		       ahc_name(ahc), devinfo.channel, devinfo.target,
		       lastphase, ahc_inb(ahc, SCSISIGI));
		ahc_restart(ahc);
		वापस;
	पूर्ण
	हाल HOST_MSG_LOOP:
	अणु
		/*
		 * The sequencer has encountered a message phase
		 * that requires host assistance क्रम completion.
		 * While handling the message phase(s), we will be
		 * notअगरied by the sequencer after each byte is
		 * transferred so we can track bus phase changes.
		 *
		 * If this is the first समय we've seen a HOST_MSG_LOOP
		 * पूर्णांकerrupt, initialize the state of the host message
		 * loop.
		 */
		अगर (ahc->msg_type == MSG_TYPE_NONE) अणु
			काष्ठा scb *scb;
			u_पूर्णांक scb_index;
			u_पूर्णांक bus_phase;

			bus_phase = ahc_inb(ahc, SCSISIGI) & PHASE_MASK;
			अगर (bus_phase != P_MESGIN
			 && bus_phase != P_MESGOUT) अणु
				prपूर्णांकk("ahc_intr: HOST_MSG_LOOP bad "
				       "phase 0x%x\n",
				      bus_phase);
				/*
				 * Probably transitioned to bus मुक्त beक्रमe
				 * we got here.  Just punt the message.
				 */
				ahc_clear_पूर्णांकstat(ahc);
				ahc_restart(ahc);
				वापस;
			पूर्ण

			scb_index = ahc_inb(ahc, SCB_TAG);
			scb = ahc_lookup_scb(ahc, scb_index);
			अगर (devinfo.role == ROLE_INITIATOR) अणु
				अगर (bus_phase == P_MESGOUT) अणु
					अगर (scb == शून्य)
						panic("HOST_MSG_LOOP with "
						      "invalid SCB %x\n",
						      scb_index);

					ahc_setup_initiator_msgout(ahc,
								   &devinfo,
								   scb);
				पूर्ण अन्यथा अणु
					ahc->msg_type =
					    MSG_TYPE_INITIATOR_MSGIN;
					ahc->msgin_index = 0;
				पूर्ण
			पूर्ण
#अगर_घोषित AHC_TARGET_MODE
			अन्यथा अणु
				अगर (bus_phase == P_MESGOUT) अणु
					ahc->msg_type =
					    MSG_TYPE_TARGET_MSGOUT;
					ahc->msgin_index = 0;
				पूर्ण अन्यथा
					ahc_setup_target_msgin(ahc,
							       &devinfo,
							       scb);
			पूर्ण
#पूर्ण_अगर
		पूर्ण

		ahc_handle_message_phase(ahc);
		अवरोध;
	पूर्ण
	हाल PERR_DETECTED:
	अणु
		/*
		 * If we've cleared the parity error पूर्णांकerrupt
		 * but the sequencer still believes that SCSIPERR
		 * is true, it must be that the parity error is
		 * क्रम the currently presented byte on the bus,
		 * and we are not in a phase (data-in) where we will
		 * eventually ack this byte.  Ack the byte and
		 * throw it away in the hope that the target will
		 * take us to message out to deliver the appropriate
		 * error message.
		 */
		अगर ((पूर्णांकstat & SCSIINT) == 0
		 && (ahc_inb(ahc, SSTAT1) & SCSIPERR) != 0) अणु

			अगर ((ahc->features & AHC_DT) == 0) अणु
				u_पूर्णांक curphase;

				/*
				 * The hardware will only let you ack bytes
				 * अगर the expected phase in SCSISIGO matches
				 * the current phase.  Make sure this is
				 * currently the हाल.
				 */
				curphase = ahc_inb(ahc, SCSISIGI) & PHASE_MASK;
				ahc_outb(ahc, LASTPHASE, curphase);
				ahc_outb(ahc, SCSISIGO, curphase);
			पूर्ण
			अगर ((ahc_inb(ahc, SCSISIGI) & (CDI|MSGI)) == 0) अणु
				पूर्णांक रुको;

				/*
				 * In a data phase.  Faster to bitbucket
				 * the data than to inभागidually ack each
				 * byte.  This is also the only strategy
				 * that will work with AUTOACK enabled.
				 */
				ahc_outb(ahc, SXFRCTL1,
					 ahc_inb(ahc, SXFRCTL1) | BITBUCKET);
				रुको = 5000;
				जबतक (--रुको != 0) अणु
					अगर ((ahc_inb(ahc, SCSISIGI)
					  & (CDI|MSGI)) != 0)
						अवरोध;
					ahc_delay(100);
				पूर्ण
				ahc_outb(ahc, SXFRCTL1,
					 ahc_inb(ahc, SXFRCTL1) & ~BITBUCKET);
				अगर (रुको == 0) अणु
					काष्ठा	scb *scb;
					u_पूर्णांक	scb_index;

					ahc_prपूर्णांक_devinfo(ahc, &devinfo);
					prपूर्णांकk("Unable to clear parity error.  "
					       "Resetting bus.\n");
					scb_index = ahc_inb(ahc, SCB_TAG);
					scb = ahc_lookup_scb(ahc, scb_index);
					अगर (scb != शून्य)
						ahc_set_transaction_status(scb,
						    CAM_UNCOR_PARITY);
					ahc_reset_channel(ahc, devinfo.channel,
							  /*init reset*/TRUE);
				पूर्ण
			पूर्ण अन्यथा अणु
				ahc_inb(ahc, SCSIDATL);
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	हाल DATA_OVERRUN:
	अणु
		/*
		 * When the sequencer detects an overrun, it
		 * places the controller in "BITBUCKET" mode
		 * and allows the target to complete its transfer.
		 * Unक्रमtunately, none of the counters get updated
		 * when the controller is in this mode, so we have
		 * no way of knowing how large the overrun was.
		 */
		u_पूर्णांक scbindex = ahc_inb(ahc, SCB_TAG);
		u_पूर्णांक lastphase = ahc_inb(ahc, LASTPHASE);
		u_पूर्णांक i;

		scb = ahc_lookup_scb(ahc, scbindex);
		क्रम (i = 0; i < num_phases; i++) अणु
			अगर (lastphase == ahc_phase_table[i].phase)
				अवरोध;
		पूर्ण
		ahc_prपूर्णांक_path(ahc, scb);
		prपूर्णांकk("data overrun detected %s."
		       "  Tag == 0x%x.\n",
		       ahc_phase_table[i].phasemsg,
		       scb->hscb->tag);
		ahc_prपूर्णांक_path(ahc, scb);
		prपूर्णांकk("%s seen Data Phase.  Length = %ld.  NumSGs = %d.\n",
		       ahc_inb(ahc, SEQ_FLAGS) & DPHASE ? "Have" : "Haven't",
		       ahc_get_transfer_length(scb), scb->sg_count);
		अगर (scb->sg_count > 0) अणु
			क्रम (i = 0; i < scb->sg_count; i++) अणु

				prपूर्णांकk("sg[%d] - Addr 0x%x%x : Length %d\n",
				       i,
				       (ahc_le32toh(scb->sg_list[i].len) >> 24
					& SG_HIGH_ADDR_BITS),
				       ahc_le32toh(scb->sg_list[i].addr),
				       ahc_le32toh(scb->sg_list[i].len)
				       & AHC_SG_LEN_MASK);
			पूर्ण
		पूर्ण
		/*
		 * Set this and it will take effect when the
		 * target करोes a command complete.
		 */
		ahc_मुक्तze_devq(ahc, scb);
		अगर ((scb->flags & SCB_SENSE) == 0) अणु
			ahc_set_transaction_status(scb, CAM_DATA_RUN_ERR);
		पूर्ण अन्यथा अणु
			scb->flags &= ~SCB_SENSE;
			ahc_set_transaction_status(scb, CAM_AUTOSENSE_FAIL);
		पूर्ण
		ahc_मुक्तze_scb(scb);

		अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
			/*
			 * Clear the channel in हाल we वापस
			 * to data phase later.
			 */
			ahc_outb(ahc, SXFRCTL0,
				 ahc_inb(ahc, SXFRCTL0) | CLRSTCNT|CLRCHN);
			ahc_outb(ahc, SXFRCTL0,
				 ahc_inb(ahc, SXFRCTL0) | CLRSTCNT|CLRCHN);
		पूर्ण
		अगर ((ahc->flags & AHC_39BIT_ADDRESSING) != 0) अणु
			u_पूर्णांक dscommand1;

			/* Ensure HHADDR is 0 क्रम future DMA operations. */
			dscommand1 = ahc_inb(ahc, DSCOMMAND1);
			ahc_outb(ahc, DSCOMMAND1, dscommand1 | HADDLDSEL0);
			ahc_outb(ahc, HADDR, 0);
			ahc_outb(ahc, DSCOMMAND1, dscommand1);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल MKMSG_FAILED:
	अणु
		u_पूर्णांक scbindex;

		prपूर्णांकk("%s:%c:%d:%d: Attempt to issue message failed\n",
		       ahc_name(ahc), devinfo.channel, devinfo.target,
		       devinfo.lun);
		scbindex = ahc_inb(ahc, SCB_TAG);
		scb = ahc_lookup_scb(ahc, scbindex);
		अगर (scb != शून्य
		 && (scb->flags & SCB_RECOVERY_SCB) != 0)
			/*
			 * Ensure that we didn't put a second instance of this
			 * SCB पूर्णांकo the QINFIFO.
			 */
			ahc_search_qinfअगरo(ahc, SCB_GET_TARGET(ahc, scb),
					   SCB_GET_CHANNEL(ahc, scb),
					   SCB_GET_LUN(scb), scb->hscb->tag,
					   ROLE_INITIATOR, /*status*/0,
					   SEARCH_REMOVE);
		अवरोध;
	पूर्ण
	हाल NO_FREE_SCB:
	अणु
		prपूर्णांकk("%s: No free or disconnected SCBs\n", ahc_name(ahc));
		ahc_dump_card_state(ahc);
		panic("for safety");
		अवरोध;
	पूर्ण
	हाल SCB_MISMATCH:
	अणु
		u_पूर्णांक scbptr;

		scbptr = ahc_inb(ahc, SCBPTR);
		prपूर्णांकk("Bogus TAG after DMA.  SCBPTR %d, tag %d, our tag %d\n",
		       scbptr, ahc_inb(ahc, ARG_1),
		       ahc->scb_data->hscbs[scbptr].tag);
		ahc_dump_card_state(ahc);
		panic("for safety");
		अवरोध;
	पूर्ण
	हाल OUT_OF_RANGE:
	अणु
		prपूर्णांकk("%s: BTT calculation out of range\n", ahc_name(ahc));
		prपूर्णांकk("SAVED_SCSIID == 0x%x, SAVED_LUN == 0x%x, "
		       "ARG_1 == 0x%x ACCUM = 0x%x\n",
		       ahc_inb(ahc, SAVED_SCSIID), ahc_inb(ahc, SAVED_LUN),
		       ahc_inb(ahc, ARG_1), ahc_inb(ahc, ACCUM));
		prपूर्णांकk("SEQ_FLAGS == 0x%x, SCBPTR == 0x%x, BTT == 0x%x, "
		       "SINDEX == 0x%x\n, A == 0x%x\n",
		       ahc_inb(ahc, SEQ_FLAGS), ahc_inb(ahc, SCBPTR),
		       ahc_index_busy_tcl(ahc,
			    BUILD_TCL(ahc_inb(ahc, SAVED_SCSIID),
				      ahc_inb(ahc, SAVED_LUN))),
		       ahc_inb(ahc, SINDEX),
		       ahc_inb(ahc, ACCUM));
		prपूर्णांकk("SCSIID == 0x%x, SCB_SCSIID == 0x%x, SCB_LUN == 0x%x, "
		       "SCB_TAG == 0x%x, SCB_CONTROL == 0x%x\n",
		       ahc_inb(ahc, SCSIID), ahc_inb(ahc, SCB_SCSIID),
		       ahc_inb(ahc, SCB_LUN), ahc_inb(ahc, SCB_TAG),
		       ahc_inb(ahc, SCB_CONTROL));
		prपूर्णांकk("SCSIBUSL == 0x%x, SCSISIGI == 0x%x\n",
		       ahc_inb(ahc, SCSIBUSL), ahc_inb(ahc, SCSISIGI));
		ahc_dump_card_state(ahc);
		panic("for safety");
		अवरोध;
	पूर्ण
	शेष:
		prपूर्णांकk("ahc_intr: seqint, "
		       "intstat == 0x%x, scsisigi = 0x%x\n",
		       पूर्णांकstat, ahc_inb(ahc, SCSISIGI));
		अवरोध;
	पूर्ण
unछोड़ो:
	/*
	 *  The sequencer is छोड़ोd immediately on
	 *  a SEQINT, so we should restart it when
	 *  we're करोne.
	 */
	ahc_unछोड़ो(ahc);
पूर्ण

अटल व्योम
ahc_handle_scsiपूर्णांक(काष्ठा ahc_softc *ahc, u_पूर्णांक पूर्णांकstat)
अणु
	u_पूर्णांक	scb_index;
	u_पूर्णांक	status0;
	u_पूर्णांक	status;
	काष्ठा	scb *scb;
	अक्षर	cur_channel;
	अक्षर	पूर्णांकr_channel;

	अगर ((ahc->features & AHC_TWIN) != 0
	 && ((ahc_inb(ahc, SBLKCTL) & SELBUSB) != 0))
		cur_channel = 'B';
	अन्यथा
		cur_channel = 'A';
	पूर्णांकr_channel = cur_channel;

	अगर ((ahc->features & AHC_ULTRA2) != 0)
		status0 = ahc_inb(ahc, SSTAT0) & IOERR;
	अन्यथा
		status0 = 0;
	status = ahc_inb(ahc, SSTAT1) & (SELTO|SCSIRSTI|BUSFREE|SCSIPERR);
	अगर (status == 0 && status0 == 0) अणु
		अगर ((ahc->features & AHC_TWIN) != 0) अणु
			/* Try the other channel */
			ahc_outb(ahc, SBLKCTL, ahc_inb(ahc, SBLKCTL) ^ SELBUSB);
			status = ahc_inb(ahc, SSTAT1)
			       & (SELTO|SCSIRSTI|BUSFREE|SCSIPERR);
			पूर्णांकr_channel = (cur_channel == 'A') ? 'B' : 'A';
		पूर्ण
		अगर (status == 0) अणु
			prपूर्णांकk("%s: Spurious SCSI interrupt\n", ahc_name(ahc));
			ahc_outb(ahc, CLRINT, CLRSCSIINT);
			ahc_unछोड़ो(ahc);
			वापस;
		पूर्ण
	पूर्ण

	/* Make sure the sequencer is in a safe location. */
	ahc_clear_critical_section(ahc);

	scb_index = ahc_inb(ahc, SCB_TAG);
	scb = ahc_lookup_scb(ahc, scb_index);
	अगर (scb != शून्य
	 && (ahc_inb(ahc, SEQ_FLAGS) & NOT_IDENTIFIED) != 0)
		scb = शून्य;

	अगर ((ahc->features & AHC_ULTRA2) != 0
	 && (status0 & IOERR) != 0) अणु
		पूर्णांक now_lvd;

		now_lvd = ahc_inb(ahc, SBLKCTL) & ENAB40;
		prपूर्णांकk("%s: Transceiver State Has Changed to %s mode\n",
		       ahc_name(ahc), now_lvd ? "LVD" : "SE");
		ahc_outb(ahc, CLRSINT0, CLRIOERR);
		/*
		 * When transitioning to SE mode, the reset line
		 * glitches, triggering an arbitration bug in some
		 * Ultra2 controllers.  This bug is cleared when we
		 * निश्चित the reset line.  Since a reset glitch has
		 * alपढ़ोy occurred with this transition and a
		 * transceiver state change is handled just like
		 * a bus reset anyway, निश्चितing the reset line
		 * ourselves is safe.
		 */
		ahc_reset_channel(ahc, पूर्णांकr_channel,
				 /*Initiate Reset*/now_lvd == 0);
	पूर्ण अन्यथा अगर ((status & SCSIRSTI) != 0) अणु
		prपूर्णांकk("%s: Someone reset channel %c\n",
			ahc_name(ahc), पूर्णांकr_channel);
		अगर (पूर्णांकr_channel != cur_channel)
			ahc_outb(ahc, SBLKCTL, ahc_inb(ahc, SBLKCTL) ^ SELBUSB);
		ahc_reset_channel(ahc, पूर्णांकr_channel, /*Initiate Reset*/FALSE);
	पूर्ण अन्यथा अगर ((status & SCSIPERR) != 0) अणु
		/*
		 * Determine the bus phase and queue an appropriate message.
		 * SCSIPERR is latched true as soon as a parity error
		 * occurs.  If the sequencer acked the transfer that
		 * caused the parity error and the currently presented
		 * transfer on the bus has correct parity, SCSIPERR will
		 * be cleared by CLRSCSIPERR.  Use this to determine अगर
		 * we should look at the last phase the sequencer recorded,
		 * or the current phase presented on the bus.
		 */
		काष्ठा	ahc_devinfo devinfo;
		u_पूर्णांक	mesg_out;
		u_पूर्णांक	curphase;
		u_पूर्णांक	errorphase;
		u_पूर्णांक	lastphase;
		u_पूर्णांक	scsirate;
		u_पूर्णांक	i;
		u_पूर्णांक	sstat2;
		पूर्णांक	silent;

		lastphase = ahc_inb(ahc, LASTPHASE);
		curphase = ahc_inb(ahc, SCSISIGI) & PHASE_MASK;
		sstat2 = ahc_inb(ahc, SSTAT2);
		ahc_outb(ahc, CLRSINT1, CLRSCSIPERR);
		/*
		 * For all phases save DATA, the sequencer won't
		 * स्वतःmatically ack a byte that has a parity error
		 * in it.  So the only way that the current phase
		 * could be 'data-in' is अगर the parity error is क्रम
		 * an alपढ़ोy acked byte in the data phase.  During
		 * synchronous data-in transfers, we may actually
		 * ack bytes beक्रमe latching the current phase in
		 * LASTPHASE, leading to the discrepancy between
		 * curphase and lastphase.
		 */
		अगर ((ahc_inb(ahc, SSTAT1) & SCSIPERR) != 0
		 || curphase == P_DATAIN || curphase == P_DATAIN_DT)
			errorphase = curphase;
		अन्यथा
			errorphase = lastphase;

		क्रम (i = 0; i < num_phases; i++) अणु
			अगर (errorphase == ahc_phase_table[i].phase)
				अवरोध;
		पूर्ण
		mesg_out = ahc_phase_table[i].mesg_out;
		silent = FALSE;
		अगर (scb != शून्य) अणु
			अगर (SCB_IS_SILENT(scb))
				silent = TRUE;
			अन्यथा
				ahc_prपूर्णांक_path(ahc, scb);
			scb->flags |= SCB_TRANSMISSION_ERROR;
		पूर्ण अन्यथा
			prपूर्णांकk("%s:%c:%d: ", ahc_name(ahc), पूर्णांकr_channel,
			       SCSIID_TARGET(ahc, ahc_inb(ahc, SAVED_SCSIID)));
		scsirate = ahc_inb(ahc, SCSIRATE);
		अगर (silent == FALSE) अणु
			prपूर्णांकk("parity error detected %s. "
			       "SEQADDR(0x%x) SCSIRATE(0x%x)\n",
			       ahc_phase_table[i].phasemsg,
			       ahc_inw(ahc, SEQADDR0),
			       scsirate);
			अगर ((ahc->features & AHC_DT) != 0) अणु
				अगर ((sstat2 & CRCVALERR) != 0)
					prपूर्णांकk("\tCRC Value Mismatch\n");
				अगर ((sstat2 & CRCENDERR) != 0)
					prपूर्णांकk("\tNo terminal CRC packet "
					       "received\n");
				अगर ((sstat2 & CRCREQERR) != 0)
					prपूर्णांकk("\tIllegal CRC packet "
					       "request\n");
				अगर ((sstat2 & DUAL_EDGE_ERR) != 0)
					prपूर्णांकk("\tUnexpected %sDT Data Phase\n",
					       (scsirate & SINGLE_EDGE)
					     ? "" : "non-");
			पूर्ण
		पूर्ण

		अगर ((ahc->features & AHC_DT) != 0
		 && (sstat2 & DUAL_EDGE_ERR) != 0) अणु
			/*
			 * This error applies regardless of
			 * data direction, so ignore the value
			 * in the phase table.
			 */
			mesg_out = INITIATOR_ERROR;
		पूर्ण

		/*
		 * We've set the hardware to निश्चित ATN अगर we
		 * get a parity error on "in" phases, so all we
		 * need to करो is stuff the message buffer with
		 * the appropriate message.  "In" phases have set
		 * mesg_out to something other than MSG_NOP.
		 */
		अगर (mesg_out != NOP) अणु
			अगर (ahc->msg_type != MSG_TYPE_NONE)
				ahc->send_msg_लिखो_त्रुटि = TRUE;
			अन्यथा
				ahc_outb(ahc, MSG_OUT, mesg_out);
		पूर्ण
		/*
		 * Force a renegotiation with this target just in
		 * हाल we are out of sync क्रम some बाह्यal reason
		 * unknown (or unreported) by the target.
		 */
		ahc_fetch_devinfo(ahc, &devinfo);
		ahc_क्रमce_renegotiation(ahc, &devinfo);

		ahc_outb(ahc, CLRINT, CLRSCSIINT);
		ahc_unछोड़ो(ahc);
	पूर्ण अन्यथा अगर ((status & SELTO) != 0) अणु
		u_पूर्णांक	scbptr;

		/* Stop the selection */
		ahc_outb(ahc, SCSISEQ, 0);

		/* No more pending messages */
		ahc_clear_msg_state(ahc);

		/* Clear पूर्णांकerrupt state */
		ahc_outb(ahc, SIMODE1, ahc_inb(ahc, SIMODE1) & ~ENBUSFREE);
		ahc_outb(ahc, CLRSINT1, CLRSELTIMEO|CLRBUSFREE|CLRSCSIPERR);

		/*
		 * Although the driver करोes not care about the
		 * 'Selection in Progress' status bit, the busy
		 * LED करोes.  SELINGO is only cleared by a successful
		 * selection, so we must manually clear it to insure
		 * the LED turns off just inहाल no future successful
		 * selections occur (e.g. no devices on the bus).
		 */
		ahc_outb(ahc, CLRSINT0, CLRSELINGO);

		scbptr = ahc_inb(ahc, WAITING_SCBH);
		ahc_outb(ahc, SCBPTR, scbptr);
		scb_index = ahc_inb(ahc, SCB_TAG);

		scb = ahc_lookup_scb(ahc, scb_index);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("%s: ahc_intr - referenced scb not "
			       "valid during SELTO scb(%d, %d)\n",
			       ahc_name(ahc), scbptr, scb_index);
			ahc_dump_card_state(ahc);
		पूर्ण अन्यथा अणु
			काष्ठा ahc_devinfo devinfo;
#अगर_घोषित AHC_DEBUG
			अगर ((ahc_debug & AHC_SHOW_SELTO) != 0) अणु
				ahc_prपूर्णांक_path(ahc, scb);
				prपूर्णांकk("Saw Selection Timeout for SCB 0x%x\n",
				       scb_index);
			पूर्ण
#पूर्ण_अगर
			ahc_scb_devinfo(ahc, &devinfo, scb);
			ahc_set_transaction_status(scb, CAM_SEL_TIMEOUT);
			ahc_मुक्तze_devq(ahc, scb);

			/*
			 * Cancel any pending transactions on the device
			 * now that it seems to be missing.  This will
			 * also revert us to async/narrow transfers until
			 * we can renegotiate with the device.
			 */
			ahc_handle_devreset(ahc, &devinfo,
					    CAM_SEL_TIMEOUT,
					    "Selection Timeout",
					    /*verbose_level*/1);
		पूर्ण
		ahc_outb(ahc, CLRINT, CLRSCSIINT);
		ahc_restart(ahc);
	पूर्ण अन्यथा अगर ((status & BUSFREE) != 0
		&& (ahc_inb(ahc, SIMODE1) & ENBUSFREE) != 0) अणु
		काष्ठा	ahc_devinfo devinfo;
		u_पूर्णांक	lastphase;
		u_पूर्णांक	saved_scsiid;
		u_पूर्णांक	saved_lun;
		u_पूर्णांक	target;
		u_पूर्णांक	initiator_role_id;
		अक्षर	channel;
		पूर्णांक	prपूर्णांकerror;

		/*
		 * Clear our selection hardware as soon as possible.
		 * We may have an entry in the रुकोing Q क्रम this target,
		 * that is affected by this busमुक्त and we करोn't want to
		 * go about selecting the target जबतक we handle the event.
		 */
		ahc_outb(ahc, SCSISEQ,
			 ahc_inb(ahc, SCSISEQ) & (ENSELI|ENRSELI|ENAUTOATNP));

		/*
		 * Disable busमुक्त पूर्णांकerrupts and clear the busमुक्त
		 * पूर्णांकerrupt status.  We करो this here so that several
		 * bus transactions occur prior to clearing the SCSIINT
		 * latch.  It can take a bit क्रम the clearing to take effect.
		 */
		ahc_outb(ahc, SIMODE1, ahc_inb(ahc, SIMODE1) & ~ENBUSFREE);
		ahc_outb(ahc, CLRSINT1, CLRBUSFREE|CLRSCSIPERR);

		/*
		 * Look at what phase we were last in.
		 * If its message out, chances are pretty good
		 * that the busमुक्त was in response to one of
		 * our पात requests.
		 */
		lastphase = ahc_inb(ahc, LASTPHASE);
		saved_scsiid = ahc_inb(ahc, SAVED_SCSIID);
		saved_lun = ahc_inb(ahc, SAVED_LUN);
		target = SCSIID_TARGET(ahc, saved_scsiid);
		initiator_role_id = SCSIID_OUR_ID(saved_scsiid);
		channel = SCSIID_CHANNEL(ahc, saved_scsiid);
		ahc_compile_devinfo(&devinfo, initiator_role_id,
				    target, saved_lun, channel, ROLE_INITIATOR);
		prपूर्णांकerror = 1;

		अगर (lastphase == P_MESGOUT) अणु
			u_पूर्णांक tag;

			tag = SCB_LIST_शून्य;
			अगर (ahc_sent_msg(ahc, AHCMSG_1B, ABORT_TASK, TRUE)
			 || ahc_sent_msg(ahc, AHCMSG_1B, ABORT_TASK_SET, TRUE)) अणु
				अगर (ahc->msgout_buf[ahc->msgout_index - 1]
				 == ABORT_TASK)
					tag = scb->hscb->tag;
				ahc_prपूर्णांक_path(ahc, scb);
				prपूर्णांकk("SCB %d - Abort%s Completed.\n",
				       scb->hscb->tag, tag == SCB_LIST_शून्य ?
				       "" : " Tag");
				ahc_पात_scbs(ahc, target, channel,
					       saved_lun, tag,
					       ROLE_INITIATOR,
					       CAM_REQ_ABORTED);
				prपूर्णांकerror = 0;
			पूर्ण अन्यथा अगर (ahc_sent_msg(ahc, AHCMSG_1B,
						TARGET_RESET, TRUE)) अणु
				ahc_compile_devinfo(&devinfo,
						    initiator_role_id,
						    target,
						    CAM_LUN_WILDCARD,
						    channel,
						    ROLE_INITIATOR);
				ahc_handle_devreset(ahc, &devinfo,
						    CAM_BDR_SENT,
						    "Bus Device Reset",
						    /*verbose_level*/0);
				prपूर्णांकerror = 0;
			पूर्ण अन्यथा अगर (ahc_sent_msg(ahc, AHCMSG_EXT,
						EXTENDED_PPR, FALSE)) अणु
				काष्ठा ahc_initiator_tinfo *tinfo;
				काष्ठा ahc_पंचांगode_tstate *tstate;

				/*
				 * PPR Rejected.  Try non-ppr negotiation
				 * and retry command.
				 */
				tinfo = ahc_fetch_transinfo(ahc,
							    devinfo.channel,
							    devinfo.our_scsiid,
							    devinfo.target,
							    &tstate);
				tinfo->curr.transport_version = 2;
				tinfo->goal.transport_version = 2;
				tinfo->goal.ppr_options = 0;
				ahc_qinfअगरo_requeue_tail(ahc, scb);
				prपूर्णांकerror = 0;
			पूर्ण अन्यथा अगर (ahc_sent_msg(ahc, AHCMSG_EXT,
						EXTENDED_WDTR, FALSE)) अणु
				/*
				 * Negotiation Rejected.  Go-narrow and
				 * retry command.
				 */
				ahc_set_width(ahc, &devinfo,
					      MSG_EXT_WDTR_BUS_8_BIT,
					      AHC_TRANS_CUR|AHC_TRANS_GOAL,
					      /*छोड़ोd*/TRUE);
				ahc_qinfअगरo_requeue_tail(ahc, scb);
				prपूर्णांकerror = 0;
			पूर्ण अन्यथा अगर (ahc_sent_msg(ahc, AHCMSG_EXT,
						EXTENDED_SDTR, FALSE)) अणु
				/*
				 * Negotiation Rejected.  Go-async and
				 * retry command.
				 */
				ahc_set_syncrate(ahc, &devinfo,
						/*syncrate*/शून्य,
						/*period*/0, /*offset*/0,
						/*ppr_options*/0,
						AHC_TRANS_CUR|AHC_TRANS_GOAL,
						/*छोड़ोd*/TRUE);
				ahc_qinfअगरo_requeue_tail(ahc, scb);
				prपूर्णांकerror = 0;
			पूर्ण
		पूर्ण
		अगर (prपूर्णांकerror != 0) अणु
			u_पूर्णांक i;

			अगर (scb != शून्य) अणु
				u_पूर्णांक tag;

				अगर ((scb->hscb->control & TAG_ENB) != 0)
					tag = scb->hscb->tag;
				अन्यथा
					tag = SCB_LIST_शून्य;
				ahc_prपूर्णांक_path(ahc, scb);
				ahc_पात_scbs(ahc, target, channel,
					       SCB_GET_LUN(scb), tag,
					       ROLE_INITIATOR,
					       CAM_UNEXP_BUSFREE);
			पूर्ण अन्यथा अणु
				/*
				 * We had not fully identअगरied this connection,
				 * so we cannot पात anything.
				 */
				prपूर्णांकk("%s: ", ahc_name(ahc));
			पूर्ण
			क्रम (i = 0; i < num_phases; i++) अणु
				अगर (lastphase == ahc_phase_table[i].phase)
					अवरोध;
			पूर्ण
			अगर (lastphase != P_BUSFREE) अणु
				/*
				 * Renegotiate with this device at the
				 * next opportunity just in हाल this busमुक्त
				 * is due to a negotiation mismatch with the
				 * device.
				 */
				ahc_क्रमce_renegotiation(ahc, &devinfo);
			पूर्ण
			prपूर्णांकk("Unexpected busfree %s\n"
			       "SEQADDR == 0x%x\n",
			       ahc_phase_table[i].phasemsg,
			       ahc_inb(ahc, SEQADDR0)
				| (ahc_inb(ahc, SEQADDR1) << 8));
		पूर्ण
		ahc_outb(ahc, CLRINT, CLRSCSIINT);
		ahc_restart(ahc);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("%s: Missing case in ahc_handle_scsiint. status = %x\n",
		       ahc_name(ahc), status);
		ahc_outb(ahc, CLRINT, CLRSCSIINT);
	पूर्ण
पूर्ण

/*
 * Force renegotiation to occur the next समय we initiate
 * a command to the current device.
 */
अटल व्योम
ahc_क्रमce_renegotiation(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo)
अणु
	काष्ठा	ahc_initiator_tinfo *targ_info;
	काष्ठा	ahc_पंचांगode_tstate *tstate;

	targ_info = ahc_fetch_transinfo(ahc,
					devinfo->channel,
					devinfo->our_scsiid,
					devinfo->target,
					&tstate);
	ahc_update_neg_request(ahc, devinfo, tstate,
			       targ_info, AHC_NEG_IF_NON_ASYNC);
पूर्ण

#घोषणा AHC_MAX_STEPS 2000
अटल व्योम
ahc_clear_critical_section(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक	stepping;
	पूर्णांक	steps;
	u_पूर्णांक	simode0;
	u_पूर्णांक	simode1;

	अगर (ahc->num_critical_sections == 0)
		वापस;

	stepping = FALSE;
	steps = 0;
	simode0 = 0;
	simode1 = 0;
	क्रम (;;) अणु
		काष्ठा	cs *cs;
		u_पूर्णांक	seqaddr;
		u_पूर्णांक	i;

		seqaddr = ahc_inb(ahc, SEQADDR0)
			| (ahc_inb(ahc, SEQADDR1) << 8);

		/*
		 * Seqaddr represents the next inकाष्ठाion to execute,
		 * so we are really executing the inकाष्ठाion just
		 * beक्रमe it.
		 */
		अगर (seqaddr != 0)
			seqaddr -= 1;
		cs = ahc->critical_sections;
		क्रम (i = 0; i < ahc->num_critical_sections; i++, cs++) अणु
			अगर (cs->begin < seqaddr && cs->end >= seqaddr)
				अवरोध;
		पूर्ण

		अगर (i == ahc->num_critical_sections)
			अवरोध;

		अगर (steps > AHC_MAX_STEPS) अणु
			prपूर्णांकk("%s: Infinite loop in critical section\n",
			       ahc_name(ahc));
			ahc_dump_card_state(ahc);
			panic("critical section loop");
		पूर्ण

		steps++;
		अगर (stepping == FALSE) अणु

			/*
			 * Disable all पूर्णांकerrupt sources so that the
			 * sequencer will not be stuck by a pausing
			 * पूर्णांकerrupt condition जबतक we attempt to
			 * leave a critical section.
			 */
			simode0 = ahc_inb(ahc, SIMODE0);
			ahc_outb(ahc, SIMODE0, 0);
			simode1 = ahc_inb(ahc, SIMODE1);
			अगर ((ahc->features & AHC_DT) != 0)
				/*
				 * On DT class controllers, we
				 * use the enhanced busमुक्त logic.
				 * Unक्रमtunately we cannot re-enable
				 * busमुक्त detection within the
				 * current connection, so we must
				 * leave it on जबतक single stepping.
				 */
				ahc_outb(ahc, SIMODE1, simode1 & ENBUSFREE);
			अन्यथा
				ahc_outb(ahc, SIMODE1, 0);
			ahc_outb(ahc, CLRINT, CLRSCSIINT);
			ahc_outb(ahc, SEQCTL, ahc->seqctl | STEP);
			stepping = TRUE;
		पूर्ण
		अगर ((ahc->features & AHC_DT) != 0) अणु
			ahc_outb(ahc, CLRSINT1, CLRBUSFREE);
			ahc_outb(ahc, CLRINT, CLRSCSIINT);
		पूर्ण
		ahc_outb(ahc, HCNTRL, ahc->unछोड़ो);
		जबतक (!ahc_is_छोड़ोd(ahc))
			ahc_delay(200);
	पूर्ण
	अगर (stepping) अणु
		ahc_outb(ahc, SIMODE0, simode0);
		ahc_outb(ahc, SIMODE1, simode1);
		ahc_outb(ahc, SEQCTL, ahc->seqctl);
	पूर्ण
पूर्ण

/*
 * Clear any pending पूर्णांकerrupt status.
 */
अटल व्योम
ahc_clear_पूर्णांकstat(काष्ठा ahc_softc *ahc)
अणु
	/* Clear any पूर्णांकerrupt conditions this may have caused */
	ahc_outb(ahc, CLRSINT1, CLRSELTIMEO|CLRATNO|CLRSCSIRSTI
				|CLRBUSFREE|CLRSCSIPERR|CLRPHASECHG|
				CLRREQINIT);
	ahc_flush_device_ग_लिखोs(ahc);
	ahc_outb(ahc, CLRSINT0, CLRSELDO|CLRSELDI|CLRSELINGO);
	ahc_flush_device_ग_लिखोs(ahc);
	ahc_outb(ahc, CLRINT, CLRSCSIINT);
	ahc_flush_device_ग_लिखोs(ahc);
पूर्ण

/**************************** Debugging Routines ******************************/
#अगर_घोषित AHC_DEBUG
uपूर्णांक32_t ahc_debug = AHC_DEBUG_OPTS;
#पूर्ण_अगर

#अगर 0 /* unused */
अटल व्योम
ahc_prपूर्णांक_scb(काष्ठा scb *scb)
अणु
	पूर्णांक i;

	काष्ठा hardware_scb *hscb = scb->hscb;

	prपूर्णांकk("scb:%p control:0x%x scsiid:0x%x lun:%d cdb_len:%d\n",
	       (व्योम *)scb,
	       hscb->control,
	       hscb->scsiid,
	       hscb->lun,
	       hscb->cdb_len);
	prपूर्णांकk("Shared Data: ");
	क्रम (i = 0; i < माप(hscb->shared_data.cdb); i++)
		prपूर्णांकk("%#02x", hscb->shared_data.cdb[i]);
	prपूर्णांकk("        dataptr:%#x datacnt:%#x sgptr:%#x tag:%#x\n",
		ahc_le32toh(hscb->dataptr),
		ahc_le32toh(hscb->datacnt),
		ahc_le32toh(hscb->sgptr),
		hscb->tag);
	अगर (scb->sg_count > 0) अणु
		क्रम (i = 0; i < scb->sg_count; i++) अणु
			prपूर्णांकk("sg[%d] - Addr 0x%x%x : Length %d\n",
			       i,
			       (ahc_le32toh(scb->sg_list[i].len) >> 24
				& SG_HIGH_ADDR_BITS),
			       ahc_le32toh(scb->sg_list[i].addr),
			       ahc_le32toh(scb->sg_list[i].len));
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

/************************* Transfer Negotiation *******************************/
/*
 * Allocate per target mode instance (ID we respond to as a target)
 * transfer negotiation data काष्ठाures.
 */
अटल काष्ठा ahc_पंचांगode_tstate *
ahc_alloc_tstate(काष्ठा ahc_softc *ahc, u_पूर्णांक scsi_id, अक्षर channel)
अणु
	काष्ठा ahc_पंचांगode_tstate *master_tstate;
	काष्ठा ahc_पंचांगode_tstate *tstate;
	पूर्णांक i;

	master_tstate = ahc->enabled_tarमाला_लो[ahc->our_id];
	अगर (channel == 'B') अणु
		scsi_id += 8;
		master_tstate = ahc->enabled_tarमाला_लो[ahc->our_id_b + 8];
	पूर्ण
	अगर (ahc->enabled_tarमाला_लो[scsi_id] != शून्य
	 && ahc->enabled_tarमाला_लो[scsi_id] != master_tstate)
		panic("%s: ahc_alloc_tstate - Target already allocated",
		      ahc_name(ahc));
	tstate = kदो_स्मृति(माप(*tstate), GFP_ATOMIC);
	अगर (tstate == शून्य)
		वापस (शून्य);

	/*
	 * If we have allocated a master tstate, copy user settings from
	 * the master tstate (taken from SRAM or the EEPROM) क्रम this
	 * channel, but reset our current and goal settings to async/narrow
	 * until an initiator talks to us.
	 */
	अगर (master_tstate != शून्य) अणु
		स_नकल(tstate, master_tstate, माप(*tstate));
		स_रखो(tstate->enabled_luns, 0, माप(tstate->enabled_luns));
		tstate->ultraenb = 0;
		क्रम (i = 0; i < AHC_NUM_TARGETS; i++) अणु
			स_रखो(&tstate->transinfo[i].curr, 0,
			      माप(tstate->transinfo[i].curr));
			स_रखो(&tstate->transinfo[i].goal, 0,
			      माप(tstate->transinfo[i].goal));
		पूर्ण
	पूर्ण अन्यथा
		स_रखो(tstate, 0, माप(*tstate));
	ahc->enabled_tarमाला_लो[scsi_id] = tstate;
	वापस (tstate);
पूर्ण

#अगर_घोषित AHC_TARGET_MODE
/*
 * Free per target mode instance (ID we respond to as a target)
 * transfer negotiation data काष्ठाures.
 */
अटल व्योम
ahc_मुक्त_tstate(काष्ठा ahc_softc *ahc, u_पूर्णांक scsi_id, अक्षर channel, पूर्णांक क्रमce)
अणु
	काष्ठा ahc_पंचांगode_tstate *tstate;

	/*
	 * Don't clean up our "master" tstate.
	 * It has our शेष user settings.
	 */
	अगर (((channel == 'B' && scsi_id == ahc->our_id_b)
	  || (channel == 'A' && scsi_id == ahc->our_id))
	 && क्रमce == FALSE)
		वापस;

	अगर (channel == 'B')
		scsi_id += 8;
	tstate = ahc->enabled_tarमाला_लो[scsi_id];
	kमुक्त(tstate);
	ahc->enabled_tarमाला_लो[scsi_id] = शून्य;
पूर्ण
#पूर्ण_अगर

/*
 * Called when we have an active connection to a target on the bus,
 * this function finds the nearest syncrate to the input period limited
 * by the capabilities of the bus connectivity of and sync settings क्रम
 * the target.
 */
अटल स्थिर काष्ठा ahc_syncrate *
ahc_devlimited_syncrate(काष्ठा ahc_softc *ahc,
			काष्ठा ahc_initiator_tinfo *tinfo,
			u_पूर्णांक *period, u_पूर्णांक *ppr_options, role_t role)
अणु
	काष्ठा	ahc_transinfo *transinfo;
	u_पूर्णांक	maxsync;

	अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
		अगर ((ahc_inb(ahc, SBLKCTL) & ENAB40) != 0
		 && (ahc_inb(ahc, SSTAT2) & EXP_ACTIVE) == 0) अणु
			maxsync = AHC_SYNCRATE_DT;
		पूर्ण अन्यथा अणु
			maxsync = AHC_SYNCRATE_ULTRA;
			/* Can't करो DT on an SE bus */
			*ppr_options &= ~MSG_EXT_PPR_DT_REQ;
		पूर्ण
	पूर्ण अन्यथा अगर ((ahc->features & AHC_ULTRA) != 0) अणु
		maxsync = AHC_SYNCRATE_ULTRA;
	पूर्ण अन्यथा अणु
		maxsync = AHC_SYNCRATE_FAST;
	पूर्ण
	/*
	 * Never allow a value higher than our current goal
	 * period otherwise we may allow a target initiated
	 * negotiation to go above the limit as set by the
	 * user.  In the हाल of an initiator initiated
	 * sync negotiation, we limit based on the user
	 * setting.  This allows the प्रणाली to still accept
	 * incoming negotiations even अगर target initiated
	 * negotiation is not perक्रमmed.
	 */
	अगर (role == ROLE_TARGET)
		transinfo = &tinfo->user;
	अन्यथा
		transinfo = &tinfo->goal;
	*ppr_options &= transinfo->ppr_options;
	अगर (transinfo->width == MSG_EXT_WDTR_BUS_8_BIT) अणु
		maxsync = max(maxsync, (u_पूर्णांक)AHC_SYNCRATE_ULTRA2);
		*ppr_options &= ~MSG_EXT_PPR_DT_REQ;
	पूर्ण
	अगर (transinfo->period == 0) अणु
		*period = 0;
		*ppr_options = 0;
		वापस (शून्य);
	पूर्ण
	*period = max(*period, (u_पूर्णांक)transinfo->period);
	वापस (ahc_find_syncrate(ahc, period, ppr_options, maxsync));
पूर्ण

/*
 * Look up the valid period to SCSIRATE conversion in our table.
 * Return the period and offset that should be sent to the target
 * अगर this was the beginning of an SDTR.
 */
स्थिर काष्ठा ahc_syncrate *
ahc_find_syncrate(काष्ठा ahc_softc *ahc, u_पूर्णांक *period,
		  u_पूर्णांक *ppr_options, u_पूर्णांक maxsync)
अणु
	स्थिर काष्ठा ahc_syncrate *syncrate;

	अगर ((ahc->features & AHC_DT) == 0)
		*ppr_options &= ~MSG_EXT_PPR_DT_REQ;

	/* Skip all DT only entries अगर DT is not available */
	अगर ((*ppr_options & MSG_EXT_PPR_DT_REQ) == 0
	 && maxsync < AHC_SYNCRATE_ULTRA2)
		maxsync = AHC_SYNCRATE_ULTRA2;

	/* Now set the maxsync based on the card capabilities
	 * DT is alपढ़ोy करोne above */
	अगर ((ahc->features & (AHC_DT | AHC_ULTRA2)) == 0
	    && maxsync < AHC_SYNCRATE_ULTRA)
		maxsync = AHC_SYNCRATE_ULTRA;
	अगर ((ahc->features & (AHC_DT | AHC_ULTRA2 | AHC_ULTRA)) == 0
	    && maxsync < AHC_SYNCRATE_FAST)
		maxsync = AHC_SYNCRATE_FAST;

	क्रम (syncrate = &ahc_syncrates[maxsync];
	     syncrate->rate != शून्य;
	     syncrate++) अणु

		/*
		 * The Ultra2 table करोesn't go as low
		 * as क्रम the Fast/Ultra cards.
		 */
		अगर ((ahc->features & AHC_ULTRA2) != 0
		 && (syncrate->sxfr_u2 == 0))
			अवरोध;

		अगर (*period <= syncrate->period) अणु
			/*
			 * When responding to a target that requests
			 * sync, the requested rate may fall between
			 * two rates that we can output, but still be
			 * a rate that we can receive.  Because of this,
			 * we want to respond to the target with
			 * the same rate that it sent to us even
			 * अगर the period we use to send data to it
			 * is lower.  Only lower the response period
			 * अगर we must.
			 */
			अगर (syncrate == &ahc_syncrates[maxsync])
				*period = syncrate->period;

			/*
			 * At some speeds, we only support
			 * ST transfers.
			 */
			अगर ((syncrate->sxfr_u2 & ST_SXFR) != 0)
				*ppr_options &= ~MSG_EXT_PPR_DT_REQ;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((*period == 0)
	 || (syncrate->rate == शून्य)
	 || ((ahc->features & AHC_ULTRA2) != 0
	  && (syncrate->sxfr_u2 == 0))) अणु
		/* Use asynchronous transfers. */
		*period = 0;
		syncrate = शून्य;
		*ppr_options &= ~MSG_EXT_PPR_DT_REQ;
	पूर्ण
	वापस (syncrate);
पूर्ण

/*
 * Convert from an entry in our syncrate table to the SCSI equivalent
 * sync "period" factor.
 */
u_पूर्णांक
ahc_find_period(काष्ठा ahc_softc *ahc, u_पूर्णांक scsirate, u_पूर्णांक maxsync)
अणु
	स्थिर काष्ठा ahc_syncrate *syncrate;

	अगर ((ahc->features & AHC_ULTRA2) != 0)
		scsirate &= SXFR_ULTRA2;
	अन्यथा
		scsirate &= SXFR;

	/* now set maxsync based on card capabilities */
	अगर ((ahc->features & AHC_DT) == 0 && maxsync < AHC_SYNCRATE_ULTRA2)
		maxsync = AHC_SYNCRATE_ULTRA2;
	अगर ((ahc->features & (AHC_DT | AHC_ULTRA2)) == 0
	    && maxsync < AHC_SYNCRATE_ULTRA)
		maxsync = AHC_SYNCRATE_ULTRA;
	अगर ((ahc->features & (AHC_DT | AHC_ULTRA2 | AHC_ULTRA)) == 0
	    && maxsync < AHC_SYNCRATE_FAST)
		maxsync = AHC_SYNCRATE_FAST;


	syncrate = &ahc_syncrates[maxsync];
	जबतक (syncrate->rate != शून्य) अणु

		अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
			अगर (syncrate->sxfr_u2 == 0)
				अवरोध;
			अन्यथा अगर (scsirate == (syncrate->sxfr_u2 & SXFR_ULTRA2))
				वापस (syncrate->period);
		पूर्ण अन्यथा अगर (scsirate == (syncrate->sxfr & SXFR)) अणु
				वापस (syncrate->period);
		पूर्ण
		syncrate++;
	पूर्ण
	वापस (0); /* async */
पूर्ण

/*
 * Truncate the given synchronous offset to a value the
 * current adapter type and syncrate are capable of.
 */
अटल व्योम
ahc_validate_offset(काष्ठा ahc_softc *ahc,
		    काष्ठा ahc_initiator_tinfo *tinfo,
		    स्थिर काष्ठा ahc_syncrate *syncrate,
		    u_पूर्णांक *offset, पूर्णांक wide, role_t role)
अणु
	u_पूर्णांक maxoffset;

	/* Limit offset to what we can करो */
	अगर (syncrate == शून्य) अणु
		maxoffset = 0;
	पूर्ण अन्यथा अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
		maxoffset = MAX_OFFSET_ULTRA2;
	पूर्ण अन्यथा अणु
		अगर (wide)
			maxoffset = MAX_OFFSET_16BIT;
		अन्यथा
			maxoffset = MAX_OFFSET_8BIT;
	पूर्ण
	*offset = min(*offset, maxoffset);
	अगर (tinfo != शून्य) अणु
		अगर (role == ROLE_TARGET)
			*offset = min(*offset, (u_पूर्णांक)tinfo->user.offset);
		अन्यथा
			*offset = min(*offset, (u_पूर्णांक)tinfo->goal.offset);
	पूर्ण
पूर्ण

/*
 * Truncate the given transfer width parameter to a value the
 * current adapter type is capable of.
 */
अटल व्योम
ahc_validate_width(काष्ठा ahc_softc *ahc, काष्ठा ahc_initiator_tinfo *tinfo,
		   u_पूर्णांक *bus_width, role_t role)
अणु
	चयन (*bus_width) अणु
	शेष:
		अगर (ahc->features & AHC_WIDE) अणु
			/* Respond Wide */
			*bus_width = MSG_EXT_WDTR_BUS_16_BIT;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल MSG_EXT_WDTR_BUS_8_BIT:
		*bus_width = MSG_EXT_WDTR_BUS_8_BIT;
		अवरोध;
	पूर्ण
	अगर (tinfo != शून्य) अणु
		अगर (role == ROLE_TARGET)
			*bus_width = min((u_पूर्णांक)tinfo->user.width, *bus_width);
		अन्यथा
			*bus_width = min((u_पूर्णांक)tinfo->goal.width, *bus_width);
	पूर्ण
पूर्ण

/*
 * Update the biपंचांगask of tarमाला_लो क्रम which the controller should
 * negotiate with at the next convenient opportunity.  This currently
 * means the next समय we send the initial identअगरy messages क्रम
 * a new transaction.
 */
पूर्णांक
ahc_update_neg_request(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo,
		       काष्ठा ahc_पंचांगode_tstate *tstate,
		       काष्ठा ahc_initiator_tinfo *tinfo, ahc_neg_type neg_type)
अणु
	u_पूर्णांक स्वतः_negotiate_orig;

	स्वतः_negotiate_orig = tstate->स्वतः_negotiate;
	अगर (neg_type == AHC_NEG_ALWAYS) अणु
		/*
		 * Force our "current" settings to be
		 * unknown so that unless a bus reset
		 * occurs the need to renegotiate is
		 * recorded persistently.
		 */
		अगर ((ahc->features & AHC_WIDE) != 0)
			tinfo->curr.width = AHC_WIDTH_UNKNOWN;
		tinfo->curr.period = AHC_PERIOD_UNKNOWN;
		tinfo->curr.offset = AHC_OFFSET_UNKNOWN;
	पूर्ण
	अगर (tinfo->curr.period != tinfo->goal.period
	 || tinfo->curr.width != tinfo->goal.width
	 || tinfo->curr.offset != tinfo->goal.offset
	 || tinfo->curr.ppr_options != tinfo->goal.ppr_options
	 || (neg_type == AHC_NEG_IF_NON_ASYNC
	  && (tinfo->goal.offset != 0
	   || tinfo->goal.width != MSG_EXT_WDTR_BUS_8_BIT
	   || tinfo->goal.ppr_options != 0)))
		tstate->स्वतः_negotiate |= devinfo->target_mask;
	अन्यथा
		tstate->स्वतः_negotiate &= ~devinfo->target_mask;

	वापस (स्वतः_negotiate_orig != tstate->स्वतः_negotiate);
पूर्ण

/*
 * Update the user/goal/curr tables of synchronous negotiation
 * parameters as well as, in the हाल of a current or active update,
 * any data काष्ठाures on the host controller.  In the हाल of an
 * active update, the specअगरied target is currently talking to us on
 * the bus, so the transfer parameter update must take effect
 * immediately.
 */
व्योम
ahc_set_syncrate(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo,
		 स्थिर काष्ठा ahc_syncrate *syncrate, u_पूर्णांक period,
		 u_पूर्णांक offset, u_पूर्णांक ppr_options, u_पूर्णांक type, पूर्णांक छोड़ोd)
अणु
	काष्ठा	ahc_initiator_tinfo *tinfo;
	काष्ठा	ahc_पंचांगode_tstate *tstate;
	u_पूर्णांक	old_period;
	u_पूर्णांक	old_offset;
	u_पूर्णांक	old_ppr;
	पूर्णांक	active;
	पूर्णांक	update_needed;

	active = (type & AHC_TRANS_ACTIVE) == AHC_TRANS_ACTIVE;
	update_needed = 0;

	अगर (syncrate == शून्य) अणु
		period = 0;
		offset = 0;
	पूर्ण

	tinfo = ahc_fetch_transinfo(ahc, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);

	अगर ((type & AHC_TRANS_USER) != 0) अणु
		tinfo->user.period = period;
		tinfo->user.offset = offset;
		tinfo->user.ppr_options = ppr_options;
	पूर्ण

	अगर ((type & AHC_TRANS_GOAL) != 0) अणु
		tinfo->goal.period = period;
		tinfo->goal.offset = offset;
		tinfo->goal.ppr_options = ppr_options;
	पूर्ण

	old_period = tinfo->curr.period;
	old_offset = tinfo->curr.offset;
	old_ppr	   = tinfo->curr.ppr_options;

	अगर ((type & AHC_TRANS_CUR) != 0
	 && (old_period != period
	  || old_offset != offset
	  || old_ppr != ppr_options)) अणु
		u_पूर्णांक	scsirate;

		update_needed++;
		scsirate = tinfo->scsirate;
		अगर ((ahc->features & AHC_ULTRA2) != 0) अणु

			scsirate &= ~(SXFR_ULTRA2|SINGLE_EDGE|ENABLE_CRC);
			अगर (syncrate != शून्य) अणु
				scsirate |= syncrate->sxfr_u2;
				अगर ((ppr_options & MSG_EXT_PPR_DT_REQ) != 0)
					scsirate |= ENABLE_CRC;
				अन्यथा
					scsirate |= SINGLE_EDGE;
			पूर्ण
		पूर्ण अन्यथा अणु

			scsirate &= ~(SXFR|SOFS);
			/*
			 * Ensure Ultra mode is set properly क्रम
			 * this target.
			 */
			tstate->ultraenb &= ~devinfo->target_mask;
			अगर (syncrate != शून्य) अणु
				अगर (syncrate->sxfr & ULTRA_SXFR) अणु
					tstate->ultraenb |=
						devinfo->target_mask;
				पूर्ण
				scsirate |= syncrate->sxfr & SXFR;
				scsirate |= offset & SOFS;
			पूर्ण
			अगर (active) अणु
				u_पूर्णांक sxfrctl0;

				sxfrctl0 = ahc_inb(ahc, SXFRCTL0);
				sxfrctl0 &= ~FAST20;
				अगर (tstate->ultraenb & devinfo->target_mask)
					sxfrctl0 |= FAST20;
				ahc_outb(ahc, SXFRCTL0, sxfrctl0);
			पूर्ण
		पूर्ण
		अगर (active) अणु
			ahc_outb(ahc, SCSIRATE, scsirate);
			अगर ((ahc->features & AHC_ULTRA2) != 0)
				ahc_outb(ahc, SCSIOFFSET, offset);
		पूर्ण

		tinfo->scsirate = scsirate;
		tinfo->curr.period = period;
		tinfo->curr.offset = offset;
		tinfo->curr.ppr_options = ppr_options;

		ahc_send_async(ahc, devinfo->channel, devinfo->target,
			       CAM_LUN_WILDCARD, AC_TRANSFER_NEG);
		अगर (bootverbose) अणु
			अगर (offset != 0) अणु
				prपूर्णांकk("%s: target %d synchronous at %sMHz%s, "
				       "offset = 0x%x\n", ahc_name(ahc),
				       devinfo->target, syncrate->rate,
				       (ppr_options & MSG_EXT_PPR_DT_REQ)
				       ? " DT" : "", offset);
			पूर्ण अन्यथा अणु
				prपूर्णांकk("%s: target %d using "
				       "asynchronous transfers\n",
				       ahc_name(ahc), devinfo->target);
			पूर्ण
		पूर्ण
	पूर्ण

	update_needed += ahc_update_neg_request(ahc, devinfo, tstate,
						tinfo, AHC_NEG_TO_GOAL);

	अगर (update_needed)
		ahc_update_pending_scbs(ahc);
पूर्ण

/*
 * Update the user/goal/curr tables of wide negotiation
 * parameters as well as, in the हाल of a current or active update,
 * any data काष्ठाures on the host controller.  In the हाल of an
 * active update, the specअगरied target is currently talking to us on
 * the bus, so the transfer parameter update must take effect
 * immediately.
 */
व्योम
ahc_set_width(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo,
	      u_पूर्णांक width, u_पूर्णांक type, पूर्णांक छोड़ोd)
अणु
	काष्ठा	ahc_initiator_tinfo *tinfo;
	काष्ठा	ahc_पंचांगode_tstate *tstate;
	u_पूर्णांक	oldwidth;
	पूर्णांक	active;
	पूर्णांक	update_needed;

	active = (type & AHC_TRANS_ACTIVE) == AHC_TRANS_ACTIVE;
	update_needed = 0;
	tinfo = ahc_fetch_transinfo(ahc, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);

	अगर ((type & AHC_TRANS_USER) != 0)
		tinfo->user.width = width;

	अगर ((type & AHC_TRANS_GOAL) != 0)
		tinfo->goal.width = width;

	oldwidth = tinfo->curr.width;
	अगर ((type & AHC_TRANS_CUR) != 0 && oldwidth != width) अणु
		u_पूर्णांक	scsirate;

		update_needed++;
		scsirate =  tinfo->scsirate;
		scsirate &= ~WIDEXFER;
		अगर (width == MSG_EXT_WDTR_BUS_16_BIT)
			scsirate |= WIDEXFER;

		tinfo->scsirate = scsirate;

		अगर (active)
			ahc_outb(ahc, SCSIRATE, scsirate);

		tinfo->curr.width = width;

		ahc_send_async(ahc, devinfo->channel, devinfo->target,
			       CAM_LUN_WILDCARD, AC_TRANSFER_NEG);
		अगर (bootverbose) अणु
			prपूर्णांकk("%s: target %d using %dbit transfers\n",
			       ahc_name(ahc), devinfo->target,
			       8 * (0x01 << width));
		पूर्ण
	पूर्ण

	update_needed += ahc_update_neg_request(ahc, devinfo, tstate,
						tinfo, AHC_NEG_TO_GOAL);
	अगर (update_needed)
		ahc_update_pending_scbs(ahc);
पूर्ण

/*
 * Update the current state of tagged queuing क्रम a given target.
 */
अटल व्योम
ahc_set_tags(काष्ठा ahc_softc *ahc, काष्ठा scsi_cmnd *cmd,
	     काष्ठा ahc_devinfo *devinfo, ahc_queue_alg alg)
अणु
	काष्ठा scsi_device *sdev = cmd->device;

	ahc_platक्रमm_set_tags(ahc, sdev, devinfo, alg);
	ahc_send_async(ahc, devinfo->channel, devinfo->target,
		       devinfo->lun, AC_TRANSFER_NEG);
पूर्ण

/*
 * When the transfer settings क्रम a connection change, update any
 * in-transit SCBs to contain the new data so the hardware will
 * be set correctly during future (re)selections.
 */
अटल व्योम
ahc_update_pending_scbs(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा	scb *pending_scb;
	पूर्णांक	pending_scb_count;
	पूर्णांक	i;
	पूर्णांक	छोड़ोd;
	u_पूर्णांक	saved_scbptr;

	/*
	 * Traverse the pending SCB list and ensure that all of the
	 * SCBs there have the proper settings.
	 */
	pending_scb_count = 0;
	LIST_FOREACH(pending_scb, &ahc->pending_scbs, pending_links) अणु
		काष्ठा ahc_devinfo devinfo;
		काष्ठा hardware_scb *pending_hscb;
		काष्ठा ahc_initiator_tinfo *tinfo;
		काष्ठा ahc_पंचांगode_tstate *tstate;

		ahc_scb_devinfo(ahc, &devinfo, pending_scb);
		tinfo = ahc_fetch_transinfo(ahc, devinfo.channel,
					    devinfo.our_scsiid,
					    devinfo.target, &tstate);
		pending_hscb = pending_scb->hscb;
		pending_hscb->control &= ~ULTRAENB;
		अगर ((tstate->ultraenb & devinfo.target_mask) != 0)
			pending_hscb->control |= ULTRAENB;
		pending_hscb->scsirate = tinfo->scsirate;
		pending_hscb->scsioffset = tinfo->curr.offset;
		अगर ((tstate->स्वतः_negotiate & devinfo.target_mask) == 0
		 && (pending_scb->flags & SCB_AUTO_NEGOTIATE) != 0) अणु
			pending_scb->flags &= ~SCB_AUTO_NEGOTIATE;
			pending_hscb->control &= ~MK_MESSAGE;
		पूर्ण
		ahc_sync_scb(ahc, pending_scb,
			     BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);
		pending_scb_count++;
	पूर्ण

	अगर (pending_scb_count == 0)
		वापस;

	अगर (ahc_is_छोड़ोd(ahc)) अणु
		छोड़ोd = 1;
	पूर्ण अन्यथा अणु
		छोड़ोd = 0;
		ahc_छोड़ो(ahc);
	पूर्ण

	saved_scbptr = ahc_inb(ahc, SCBPTR);
	/* Ensure that the hscbs करोwn on the card match the new inक्रमmation */
	क्रम (i = 0; i < ahc->scb_data->maxhscbs; i++) अणु
		काष्ठा	hardware_scb *pending_hscb;
		u_पूर्णांक	control;
		u_पूर्णांक	scb_tag;

		ahc_outb(ahc, SCBPTR, i);
		scb_tag = ahc_inb(ahc, SCB_TAG);
		pending_scb = ahc_lookup_scb(ahc, scb_tag);
		अगर (pending_scb == शून्य)
			जारी;

		pending_hscb = pending_scb->hscb;
		control = ahc_inb(ahc, SCB_CONTROL);
		control &= ~(ULTRAENB|MK_MESSAGE);
		control |= pending_hscb->control & (ULTRAENB|MK_MESSAGE);
		ahc_outb(ahc, SCB_CONTROL, control);
		ahc_outb(ahc, SCB_SCSIRATE, pending_hscb->scsirate);
		ahc_outb(ahc, SCB_SCSIOFFSET, pending_hscb->scsioffset);
	पूर्ण
	ahc_outb(ahc, SCBPTR, saved_scbptr);

	अगर (छोड़ोd == 0)
		ahc_unछोड़ो(ahc);
पूर्ण

/**************************** Pathing Inक्रमmation *****************************/
अटल व्योम
ahc_fetch_devinfo(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo)
अणु
	u_पूर्णांक	saved_scsiid;
	role_t	role;
	पूर्णांक	our_id;

	अगर (ahc_inb(ahc, SSTAT0) & TARGET)
		role = ROLE_TARGET;
	अन्यथा
		role = ROLE_INITIATOR;

	अगर (role == ROLE_TARGET
	    && (ahc->features & AHC_MULTI_TID) != 0
	    && (ahc_inb(ahc, SEQ_FLAGS)
	     & (CMDPHASE_PENDING|TARG_CMD_PENDING|NO_DISCONNECT)) != 0) अणु
		/* We were selected, so pull our id from TARGIDIN */
		our_id = ahc_inb(ahc, TARGIDIN) & OID;
	पूर्ण अन्यथा अगर ((ahc->features & AHC_ULTRA2) != 0)
		our_id = ahc_inb(ahc, SCSIID_ULTRA2) & OID;
	अन्यथा
		our_id = ahc_inb(ahc, SCSIID) & OID;

	saved_scsiid = ahc_inb(ahc, SAVED_SCSIID);
	ahc_compile_devinfo(devinfo,
			    our_id,
			    SCSIID_TARGET(ahc, saved_scsiid),
			    ahc_inb(ahc, SAVED_LUN),
			    SCSIID_CHANNEL(ahc, saved_scsiid),
			    role);
पूर्ण

अटल स्थिर काष्ठा ahc_phase_table_entry*
ahc_lookup_phase_entry(पूर्णांक phase)
अणु
	स्थिर काष्ठा ahc_phase_table_entry *entry;
	स्थिर काष्ठा ahc_phase_table_entry *last_entry;

	/*
	 * num_phases करोesn't include the शेष entry which
	 * will be वापसed अगर the phase करोesn't match.
	 */
	last_entry = &ahc_phase_table[num_phases];
	क्रम (entry = ahc_phase_table; entry < last_entry; entry++) अणु
		अगर (phase == entry->phase)
			अवरोध;
	पूर्ण
	वापस (entry);
पूर्ण

व्योम
ahc_compile_devinfo(काष्ठा ahc_devinfo *devinfo, u_पूर्णांक our_id, u_पूर्णांक target,
		    u_पूर्णांक lun, अक्षर channel, role_t role)
अणु
	devinfo->our_scsiid = our_id;
	devinfo->target = target;
	devinfo->lun = lun;
	devinfo->target_offset = target;
	devinfo->channel = channel;
	devinfo->role = role;
	अगर (channel == 'B')
		devinfo->target_offset += 8;
	devinfo->target_mask = (0x01 << devinfo->target_offset);
पूर्ण

व्योम
ahc_prपूर्णांक_devinfo(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo)
अणु
	prपूर्णांकk("%s:%c:%d:%d: ", ahc_name(ahc), devinfo->channel,
	       devinfo->target, devinfo->lun);
पूर्ण

अटल व्योम
ahc_scb_devinfo(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo,
		काष्ठा scb *scb)
अणु
	role_t	role;
	पूर्णांक	our_id;

	our_id = SCSIID_OUR_ID(scb->hscb->scsiid);
	role = ROLE_INITIATOR;
	अगर ((scb->flags & SCB_TARGET_SCB) != 0)
		role = ROLE_TARGET;
	ahc_compile_devinfo(devinfo, our_id, SCB_GET_TARGET(ahc, scb),
			    SCB_GET_LUN(scb), SCB_GET_CHANNEL(ahc, scb), role);
पूर्ण


/************************ Message Phase Processing ****************************/
अटल व्योम
ahc_निश्चित_atn(काष्ठा ahc_softc *ahc)
अणु
	u_पूर्णांक scsisigo;

	scsisigo = ATNO;
	अगर ((ahc->features & AHC_DT) == 0)
		scsisigo |= ahc_inb(ahc, SCSISIGI);
	ahc_outb(ahc, SCSISIGO, scsisigo);
पूर्ण

/*
 * When an initiator transaction with the MK_MESSAGE flag either reconnects
 * or enters the initial message out phase, we are पूर्णांकerrupted.  Fill our
 * outgoing message buffer with the appropriate message and beging handing
 * the message phase(s) manually.
 */
अटल व्योम
ahc_setup_initiator_msgout(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo,
			   काष्ठा scb *scb)
अणु
	/*
	 * To facilitate adding multiple messages together,
	 * each routine should increment the index and len
	 * variables instead of setting them explicitly.
	 */
	ahc->msgout_index = 0;
	ahc->msgout_len = 0;

	अगर ((scb->flags & SCB_DEVICE_RESET) == 0
	 && ahc_inb(ahc, MSG_OUT) == MSG_IDENTIFYFLAG) अणु
		u_पूर्णांक identअगरy_msg;

		identअगरy_msg = MSG_IDENTIFYFLAG | SCB_GET_LUN(scb);
		अगर ((scb->hscb->control & DISCENB) != 0)
			identअगरy_msg |= MSG_IDENTIFY_DISCFLAG;
		ahc->msgout_buf[ahc->msgout_index++] = identअगरy_msg;
		ahc->msgout_len++;

		अगर ((scb->hscb->control & TAG_ENB) != 0) अणु
			ahc->msgout_buf[ahc->msgout_index++] =
			    scb->hscb->control & (TAG_ENB|SCB_TAG_TYPE);
			ahc->msgout_buf[ahc->msgout_index++] = scb->hscb->tag;
			ahc->msgout_len += 2;
		पूर्ण
	पूर्ण

	अगर (scb->flags & SCB_DEVICE_RESET) अणु
		ahc->msgout_buf[ahc->msgout_index++] = TARGET_RESET;
		ahc->msgout_len++;
		ahc_prपूर्णांक_path(ahc, scb);
		prपूर्णांकk("Bus Device Reset Message Sent\n");
		/*
		 * Clear our selection hardware in advance of
		 * the busमुक्त.  We may have an entry in the रुकोing
		 * Q क्रम this target, and we करोn't want to go about
		 * selecting जबतक we handle the busमुक्त and blow it
		 * away.
		 */
		ahc_outb(ahc, SCSISEQ, (ahc_inb(ahc, SCSISEQ) & ~ENSELO));
	पूर्ण अन्यथा अगर ((scb->flags & SCB_ABORT) != 0) अणु
		अगर ((scb->hscb->control & TAG_ENB) != 0)
			ahc->msgout_buf[ahc->msgout_index++] = ABORT_TASK;
		अन्यथा
			ahc->msgout_buf[ahc->msgout_index++] = ABORT_TASK_SET;
		ahc->msgout_len++;
		ahc_prपूर्णांक_path(ahc, scb);
		prपूर्णांकk("Abort%s Message Sent\n",
		       (scb->hscb->control & TAG_ENB) != 0 ? " Tag" : "");
		/*
		 * Clear our selection hardware in advance of
		 * the busमुक्त.  We may have an entry in the रुकोing
		 * Q क्रम this target, and we करोn't want to go about
		 * selecting जबतक we handle the busमुक्त and blow it
		 * away.
		 */
		ahc_outb(ahc, SCSISEQ, (ahc_inb(ahc, SCSISEQ) & ~ENSELO));
	पूर्ण अन्यथा अगर ((scb->flags & (SCB_AUTO_NEGOTIATE|SCB_NEGOTIATE)) != 0) अणु
		ahc_build_transfer_msg(ahc, devinfo);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("ahc_intr: AWAITING_MSG for an SCB that "
		       "does not have a waiting message\n");
		prपूर्णांकk("SCSIID = %x, target_mask = %x\n", scb->hscb->scsiid,
		       devinfo->target_mask);
		panic("SCB = %d, SCB Control = %x, MSG_OUT = %x "
		      "SCB flags = %x", scb->hscb->tag, scb->hscb->control,
		      ahc_inb(ahc, MSG_OUT), scb->flags);
	पूर्ण

	/*
	 * Clear the MK_MESSAGE flag from the SCB so we aren't
	 * asked to send this message again.
	 */
	ahc_outb(ahc, SCB_CONTROL, ahc_inb(ahc, SCB_CONTROL) & ~MK_MESSAGE);
	scb->hscb->control &= ~MK_MESSAGE;
	ahc->msgout_index = 0;
	ahc->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
पूर्ण

/*
 * Build an appropriate transfer negotiation message क्रम the
 * currently active target.
 */
अटल व्योम
ahc_build_transfer_msg(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo)
अणु
	/*
	 * We need to initiate transfer negotiations.
	 * If our current and goal settings are identical,
	 * we want to renegotiate due to a check condition.
	 */
	काष्ठा	ahc_initiator_tinfo *tinfo;
	काष्ठा	ahc_पंचांगode_tstate *tstate;
	स्थिर काष्ठा ahc_syncrate *rate;
	पूर्णांक	करोwide;
	पूर्णांक	करोsync;
	पूर्णांक	करोppr;
	u_पूर्णांक	period;
	u_पूर्णांक	ppr_options;
	u_पूर्णांक	offset;

	tinfo = ahc_fetch_transinfo(ahc, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);
	/*
	 * Filter our period based on the current connection.
	 * If we can't perक्रमm DT transfers on this segment (not in LVD
	 * mode क्रम instance), then our decision to issue a PPR message
	 * may change.
	 */
	period = tinfo->goal.period;
	offset = tinfo->goal.offset;
	ppr_options = tinfo->goal.ppr_options;
	/* Target initiated PPR is not allowed in the SCSI spec */
	अगर (devinfo->role == ROLE_TARGET)
		ppr_options = 0;
	rate = ahc_devlimited_syncrate(ahc, tinfo, &period,
				       &ppr_options, devinfo->role);
	करोwide = tinfo->curr.width != tinfo->goal.width;
	करोsync = tinfo->curr.offset != offset || tinfo->curr.period != period;
	/*
	 * Only use PPR अगर we have options that need it, even अगर the device
	 * claims to support it.  There might be an expander in the way
	 * that करोesn't.
	 */
	करोppr = ppr_options != 0;

	अगर (!करोwide && !करोsync && !करोppr) अणु
		करोwide = tinfo->goal.width != MSG_EXT_WDTR_BUS_8_BIT;
		करोsync = tinfo->goal.offset != 0;
	पूर्ण

	अगर (!करोwide && !करोsync && !करोppr) अणु
		/*
		 * Force async with a WDTR message अगर we have a wide bus,
		 * or just issue an SDTR with a 0 offset.
		 */
		अगर ((ahc->features & AHC_WIDE) != 0)
			करोwide = 1;
		अन्यथा
			करोsync = 1;

		अगर (bootverbose) अणु
			ahc_prपूर्णांक_devinfo(ahc, devinfo);
			prपूर्णांकk("Ensuring async\n");
		पूर्ण
	पूर्ण

	/* Target initiated PPR is not allowed in the SCSI spec */
	अगर (devinfo->role == ROLE_TARGET)
		करोppr = 0;

	/*
	 * Both the PPR message and SDTR message require the
	 * goal syncrate to be limited to what the target device
	 * is capable of handling (based on whether an LVD->SE
	 * expander is on the bus), so combine these two हालs.
	 * Regardless, guarantee that अगर we are using WDTR and SDTR
	 * messages that WDTR comes first.
	 */
	अगर (करोppr || (करोsync && !करोwide)) अणु

		offset = tinfo->goal.offset;
		ahc_validate_offset(ahc, tinfo, rate, &offset,
				    करोppr ? tinfo->goal.width
					  : tinfo->curr.width,
				    devinfo->role);
		अगर (करोppr) अणु
			ahc_स्थिरruct_ppr(ahc, devinfo, period, offset,
					  tinfo->goal.width, ppr_options);
		पूर्ण अन्यथा अणु
			ahc_स्थिरruct_sdtr(ahc, devinfo, period, offset);
		पूर्ण
	पूर्ण अन्यथा अणु
		ahc_स्थिरruct_wdtr(ahc, devinfo, tinfo->goal.width);
	पूर्ण
पूर्ण

/*
 * Build a synchronous negotiation message in our message
 * buffer based on the input parameters.
 */
अटल व्योम
ahc_स्थिरruct_sdtr(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo,
		   u_पूर्णांक period, u_पूर्णांक offset)
अणु
	अगर (offset == 0)
		period = AHC_ASYNC_XFER_PERIOD;
	ahc->msgout_index += spi_populate_sync_msg(
			ahc->msgout_buf + ahc->msgout_index, period, offset);
	ahc->msgout_len += 5;
	अगर (bootverbose) अणु
		prपूर्णांकk("(%s:%c:%d:%d): Sending SDTR period %x, offset %x\n",
		       ahc_name(ahc), devinfo->channel, devinfo->target,
		       devinfo->lun, period, offset);
	पूर्ण
पूर्ण

/*
 * Build a wide negotiation message in our message
 * buffer based on the input parameters.
 */
अटल व्योम
ahc_स्थिरruct_wdtr(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo,
		   u_पूर्णांक bus_width)
अणु
	ahc->msgout_index += spi_populate_width_msg(
			ahc->msgout_buf + ahc->msgout_index, bus_width);
	ahc->msgout_len += 4;
	अगर (bootverbose) अणु
		prपूर्णांकk("(%s:%c:%d:%d): Sending WDTR %x\n",
		       ahc_name(ahc), devinfo->channel, devinfo->target,
		       devinfo->lun, bus_width);
	पूर्ण
पूर्ण

/*
 * Build a parallel protocol request message in our message
 * buffer based on the input parameters.
 */
अटल व्योम
ahc_स्थिरruct_ppr(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo,
		  u_पूर्णांक period, u_पूर्णांक offset, u_पूर्णांक bus_width,
		  u_पूर्णांक ppr_options)
अणु
	अगर (offset == 0)
		period = AHC_ASYNC_XFER_PERIOD;
	ahc->msgout_index += spi_populate_ppr_msg(
			ahc->msgout_buf + ahc->msgout_index, period, offset,
			bus_width, ppr_options);
	ahc->msgout_len += 8;
	अगर (bootverbose) अणु
		prपूर्णांकk("(%s:%c:%d:%d): Sending PPR bus_width %x, period %x, "
		       "offset %x, ppr_options %x\n", ahc_name(ahc),
		       devinfo->channel, devinfo->target, devinfo->lun,
		       bus_width, period, offset, ppr_options);
	पूर्ण
पूर्ण

/*
 * Clear any active message state.
 */
अटल व्योम
ahc_clear_msg_state(काष्ठा ahc_softc *ahc)
अणु
	ahc->msgout_len = 0;
	ahc->msgin_index = 0;
	ahc->msg_type = MSG_TYPE_NONE;
	अगर ((ahc_inb(ahc, SCSISIGI) & ATNI) != 0) अणु
		/*
		 * The target didn't care to respond to our
		 * message request, so clear ATN.
		 */
		ahc_outb(ahc, CLRSINT1, CLRATNO);
	पूर्ण
	ahc_outb(ahc, MSG_OUT, NOP);
	ahc_outb(ahc, SEQ_FLAGS2,
		 ahc_inb(ahc, SEQ_FLAGS2) & ~TARGET_MSG_PENDING);
पूर्ण

अटल व्योम
ahc_handle_proto_violation(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा	ahc_devinfo devinfo;
	काष्ठा	scb *scb;
	u_पूर्णांक	scbid;
	u_पूर्णांक	seq_flags;
	u_पूर्णांक	curphase;
	u_पूर्णांक	lastphase;
	पूर्णांक	found;

	ahc_fetch_devinfo(ahc, &devinfo);
	scbid = ahc_inb(ahc, SCB_TAG);
	scb = ahc_lookup_scb(ahc, scbid);
	seq_flags = ahc_inb(ahc, SEQ_FLAGS);
	curphase = ahc_inb(ahc, SCSISIGI) & PHASE_MASK;
	lastphase = ahc_inb(ahc, LASTPHASE);
	अगर ((seq_flags & NOT_IDENTIFIED) != 0) अणु

		/*
		 * The reconnecting target either did not send an
		 * identअगरy message, or did, but we didn't find an SCB
		 * to match.
		 */
		ahc_prपूर्णांक_devinfo(ahc, &devinfo);
		prपूर्णांकk("Target did not send an IDENTIFY message. "
		       "LASTPHASE = 0x%x.\n", lastphase);
		scb = शून्य;
	पूर्ण अन्यथा अगर (scb == शून्य) अणु
		/*
		 * We करोn't seem to have an SCB active क्रम this
		 * transaction.  Prपूर्णांक an error and reset the bus.
		 */
		ahc_prपूर्णांक_devinfo(ahc, &devinfo);
		prपूर्णांकk("No SCB found during protocol violation\n");
		जाओ proto_violation_reset;
	पूर्ण अन्यथा अणु
		ahc_set_transaction_status(scb, CAM_SEQUENCE_FAIL);
		अगर ((seq_flags & NO_CDB_SENT) != 0) अणु
			ahc_prपूर्णांक_path(ahc, scb);
			prपूर्णांकk("No or incomplete CDB sent to device.\n");
		पूर्ण अन्यथा अगर ((ahc_inb(ahc, SCB_CONTROL) & STATUS_RCVD) == 0) अणु
			/*
			 * The target never bothered to provide status to
			 * us prior to completing the command.  Since we करोn't
			 * know the disposition of this command, we must attempt
			 * to पात it.  Assert ATN and prepare to send an पात
			 * message.
			 */
			ahc_prपूर्णांक_path(ahc, scb);
			prपूर्णांकk("Completed command without status.\n");
		पूर्ण अन्यथा अणु
			ahc_prपूर्णांक_path(ahc, scb);
			prपूर्णांकk("Unknown protocol violation.\n");
			ahc_dump_card_state(ahc);
		पूर्ण
	पूर्ण
	अगर ((lastphase & ~P_DATAIN_DT) == 0
	 || lastphase == P_COMMAND) अणु
proto_violation_reset:
		/*
		 * Target either went directly to data/command
		 * phase or didn't respond to our ATN.
		 * The only safe thing to करो is to blow
		 * it away with a bus reset.
		 */
		found = ahc_reset_channel(ahc, 'A', TRUE);
		prपूर्णांकk("%s: Issued Channel %c Bus Reset. "
		       "%d SCBs aborted\n", ahc_name(ahc), 'A', found);
	पूर्ण अन्यथा अणु
		/*
		 * Leave the selection hardware off in हाल
		 * this पात attempt will affect yet to
		 * be sent commands.
		 */
		ahc_outb(ahc, SCSISEQ,
			 ahc_inb(ahc, SCSISEQ) & ~ENSELO);
		ahc_निश्चित_atn(ahc);
		ahc_outb(ahc, MSG_OUT, HOST_MSG);
		अगर (scb == शून्य) अणु
			ahc_prपूर्णांक_devinfo(ahc, &devinfo);
			ahc->msgout_buf[0] = ABORT_TASK;
			ahc->msgout_len = 1;
			ahc->msgout_index = 0;
			ahc->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
		पूर्ण अन्यथा अणु
			ahc_prपूर्णांक_path(ahc, scb);
			scb->flags |= SCB_ABORT;
		पूर्ण
		prपूर्णांकk("Protocol violation %s.  Attempting to abort.\n",
		       ahc_lookup_phase_entry(curphase)->phasemsg);
	पूर्ण
पूर्ण

/*
 * Manual message loop handler.
 */
अटल व्योम
ahc_handle_message_phase(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा	ahc_devinfo devinfo;
	u_पूर्णांक	bus_phase;
	पूर्णांक	end_session;

	ahc_fetch_devinfo(ahc, &devinfo);
	end_session = FALSE;
	bus_phase = ahc_inb(ahc, SCSISIGI) & PHASE_MASK;

reचयन:
	चयन (ahc->msg_type) अणु
	हाल MSG_TYPE_INITIATOR_MSGOUT:
	अणु
		पूर्णांक lastbyte;
		पूर्णांक phasemis;
		पूर्णांक msgकरोne;

		अगर (ahc->msgout_len == 0)
			panic("HOST_MSG_LOOP interrupt with no active message");

#अगर_घोषित AHC_DEBUG
		अगर ((ahc_debug & AHC_SHOW_MESSAGES) != 0) अणु
			ahc_prपूर्णांक_devinfo(ahc, &devinfo);
			prपूर्णांकk("INITIATOR_MSG_OUT");
		पूर्ण
#पूर्ण_अगर
		phasemis = bus_phase != P_MESGOUT;
		अगर (phasemis) अणु
#अगर_घोषित AHC_DEBUG
			अगर ((ahc_debug & AHC_SHOW_MESSAGES) != 0) अणु
				prपूर्णांकk(" PHASEMIS %s\n",
				       ahc_lookup_phase_entry(bus_phase)
							     ->phasemsg);
			पूर्ण
#पूर्ण_अगर
			अगर (bus_phase == P_MESGIN) अणु
				/*
				 * Change gears and see अगर
				 * this messages is of पूर्णांकerest to
				 * us or should be passed back to
				 * the sequencer.
				 */
				ahc_outb(ahc, CLRSINT1, CLRATNO);
				ahc->send_msg_लिखो_त्रुटि = FALSE;
				ahc->msg_type = MSG_TYPE_INITIATOR_MSGIN;
				ahc->msgin_index = 0;
				जाओ reचयन;
			पूर्ण
			end_session = TRUE;
			अवरोध;
		पूर्ण

		अगर (ahc->send_msg_लिखो_त्रुटि) अणु
			ahc_outb(ahc, CLRSINT1, CLRATNO);
			ahc_outb(ahc, CLRSINT1, CLRREQINIT);
#अगर_घोषित AHC_DEBUG
			अगर ((ahc_debug & AHC_SHOW_MESSAGES) != 0)
				prपूर्णांकk(" byte 0x%x\n", ahc->send_msg_लिखो_त्रुटि);
#पूर्ण_अगर
			ahc_outb(ahc, SCSIDATL, MSG_PARITY_ERROR);
			अवरोध;
		पूर्ण

		msgकरोne	= ahc->msgout_index == ahc->msgout_len;
		अगर (msgकरोne) अणु
			/*
			 * The target has requested a retry.
			 * Re-निश्चित ATN, reset our message index to
			 * 0, and try again.
			 */
			ahc->msgout_index = 0;
			ahc_निश्चित_atn(ahc);
		पूर्ण

		lastbyte = ahc->msgout_index == (ahc->msgout_len - 1);
		अगर (lastbyte) अणु
			/* Last byte is signअगरied by dropping ATN */
			ahc_outb(ahc, CLRSINT1, CLRATNO);
		पूर्ण

		/*
		 * Clear our पूर्णांकerrupt status and present
		 * the next byte on the bus.
		 */
		ahc_outb(ahc, CLRSINT1, CLRREQINIT);
#अगर_घोषित AHC_DEBUG
		अगर ((ahc_debug & AHC_SHOW_MESSAGES) != 0)
			prपूर्णांकk(" byte 0x%x\n",
			       ahc->msgout_buf[ahc->msgout_index]);
#पूर्ण_अगर
		ahc_outb(ahc, SCSIDATL, ahc->msgout_buf[ahc->msgout_index++]);
		अवरोध;
	पूर्ण
	हाल MSG_TYPE_INITIATOR_MSGIN:
	अणु
		पूर्णांक phasemis;
		पूर्णांक message_करोne;

#अगर_घोषित AHC_DEBUG
		अगर ((ahc_debug & AHC_SHOW_MESSAGES) != 0) अणु
			ahc_prपूर्णांक_devinfo(ahc, &devinfo);
			prपूर्णांकk("INITIATOR_MSG_IN");
		पूर्ण
#पूर्ण_अगर
		phasemis = bus_phase != P_MESGIN;
		अगर (phasemis) अणु
#अगर_घोषित AHC_DEBUG
			अगर ((ahc_debug & AHC_SHOW_MESSAGES) != 0) अणु
				prपूर्णांकk(" PHASEMIS %s\n",
				       ahc_lookup_phase_entry(bus_phase)
							     ->phasemsg);
			पूर्ण
#पूर्ण_अगर
			ahc->msgin_index = 0;
			अगर (bus_phase == P_MESGOUT
			 && (ahc->send_msg_लिखो_त्रुटि == TRUE
			  || (ahc->msgout_len != 0
			   && ahc->msgout_index == 0))) अणु
				ahc->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
				जाओ reचयन;
			पूर्ण
			end_session = TRUE;
			अवरोध;
		पूर्ण

		/* Pull the byte in without acking it */
		ahc->msgin_buf[ahc->msgin_index] = ahc_inb(ahc, SCSIBUSL);
#अगर_घोषित AHC_DEBUG
		अगर ((ahc_debug & AHC_SHOW_MESSAGES) != 0)
			prपूर्णांकk(" byte 0x%x\n",
			       ahc->msgin_buf[ahc->msgin_index]);
#पूर्ण_अगर

		message_करोne = ahc_parse_msg(ahc, &devinfo);

		अगर (message_करोne) अणु
			/*
			 * Clear our incoming message buffer in हाल there
			 * is another message following this one.
			 */
			ahc->msgin_index = 0;

			/*
			 * If this message illicited a response,
			 * निश्चित ATN so the target takes us to the
			 * message out phase.
			 */
			अगर (ahc->msgout_len != 0) अणु
#अगर_घोषित AHC_DEBUG
				अगर ((ahc_debug & AHC_SHOW_MESSAGES) != 0) अणु
					ahc_prपूर्णांक_devinfo(ahc, &devinfo);
					prपूर्णांकk("Asserting ATN for response\n");
				पूर्ण
#पूर्ण_अगर
				ahc_निश्चित_atn(ahc);
			पूर्ण
		पूर्ण अन्यथा
			ahc->msgin_index++;

		अगर (message_करोne == MSGLOOP_TERMINATED) अणु
			end_session = TRUE;
		पूर्ण अन्यथा अणु
			/* Ack the byte */
			ahc_outb(ahc, CLRSINT1, CLRREQINIT);
			ahc_inb(ahc, SCSIDATL);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल MSG_TYPE_TARGET_MSGIN:
	अणु
		पूर्णांक msgकरोne;
		पूर्णांक msgout_request;

		अगर (ahc->msgout_len == 0)
			panic("Target MSGIN with no active message");

		/*
		 * If we पूर्णांकerrupted a mesgout session, the initiator
		 * will not know this until our first REQ.  So, we
		 * only honor mesgout requests after we've sent our
		 * first byte.
		 */
		अगर ((ahc_inb(ahc, SCSISIGI) & ATNI) != 0
		 && ahc->msgout_index > 0)
			msgout_request = TRUE;
		अन्यथा
			msgout_request = FALSE;

		अगर (msgout_request) अणु

			/*
			 * Change gears and see अगर
			 * this messages is of पूर्णांकerest to
			 * us or should be passed back to
			 * the sequencer.
			 */
			ahc->msg_type = MSG_TYPE_TARGET_MSGOUT;
			ahc_outb(ahc, SCSISIGO, P_MESGOUT | BSYO);
			ahc->msgin_index = 0;
			/* Dummy पढ़ो to REQ क्रम first byte */
			ahc_inb(ahc, SCSIDATL);
			ahc_outb(ahc, SXFRCTL0,
				 ahc_inb(ahc, SXFRCTL0) | SPIOEN);
			अवरोध;
		पूर्ण

		msgकरोne = ahc->msgout_index == ahc->msgout_len;
		अगर (msgकरोne) अणु
			ahc_outb(ahc, SXFRCTL0,
				 ahc_inb(ahc, SXFRCTL0) & ~SPIOEN);
			end_session = TRUE;
			अवरोध;
		पूर्ण

		/*
		 * Present the next byte on the bus.
		 */
		ahc_outb(ahc, SXFRCTL0, ahc_inb(ahc, SXFRCTL0) | SPIOEN);
		ahc_outb(ahc, SCSIDATL, ahc->msgout_buf[ahc->msgout_index++]);
		अवरोध;
	पूर्ण
	हाल MSG_TYPE_TARGET_MSGOUT:
	अणु
		पूर्णांक lastbyte;
		पूर्णांक msgकरोne;

		/*
		 * The initiator संकेतs that this is
		 * the last byte by dropping ATN.
		 */
		lastbyte = (ahc_inb(ahc, SCSISIGI) & ATNI) == 0;

		/*
		 * Read the latched byte, but turn off SPIOEN first
		 * so that we करोn't inadvertently cause a REQ क्रम the
		 * next byte.
		 */
		ahc_outb(ahc, SXFRCTL0, ahc_inb(ahc, SXFRCTL0) & ~SPIOEN);
		ahc->msgin_buf[ahc->msgin_index] = ahc_inb(ahc, SCSIDATL);
		msgकरोne = ahc_parse_msg(ahc, &devinfo);
		अगर (msgकरोne == MSGLOOP_TERMINATED) अणु
			/*
			 * The message is *really* करोne in that it caused
			 * us to go to bus मुक्त.  The sequencer has alपढ़ोy
			 * been reset at this poपूर्णांक, so pull the ejection
			 * handle.
			 */
			वापस;
		पूर्ण

		ahc->msgin_index++;

		/*
		 * XXX Read spec about initiator dropping ATN too soon
		 *     and use msgकरोne to detect it.
		 */
		अगर (msgकरोne == MSGLOOP_MSGCOMPLETE) अणु
			ahc->msgin_index = 0;

			/*
			 * If this message illicited a response, transition
			 * to the Message in phase and send it.
			 */
			अगर (ahc->msgout_len != 0) अणु
				ahc_outb(ahc, SCSISIGO, P_MESGIN | BSYO);
				ahc_outb(ahc, SXFRCTL0,
					 ahc_inb(ahc, SXFRCTL0) | SPIOEN);
				ahc->msg_type = MSG_TYPE_TARGET_MSGIN;
				ahc->msgin_index = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (lastbyte)
			end_session = TRUE;
		अन्यथा अणु
			/* Ask क्रम the next byte. */
			ahc_outb(ahc, SXFRCTL0,
				 ahc_inb(ahc, SXFRCTL0) | SPIOEN);
		पूर्ण

		अवरोध;
	पूर्ण
	शेष:
		panic("Unknown REQINIT message type");
	पूर्ण

	अगर (end_session) अणु
		ahc_clear_msg_state(ahc);
		ahc_outb(ahc, RETURN_1, EXIT_MSG_LOOP);
	पूर्ण अन्यथा
		ahc_outb(ahc, RETURN_1, CONT_MSG_LOOP);
पूर्ण

/*
 * See अगर we sent a particular extended message to the target.
 * If "full" is true, वापस true only अगर the target saw the full
 * message.  If "full" is false, वापस true अगर the target saw at
 * least the first byte of the message.
 */
अटल पूर्णांक
ahc_sent_msg(काष्ठा ahc_softc *ahc, ahc_msgtype type, u_पूर्णांक msgval, पूर्णांक full)
अणु
	पूर्णांक found;
	u_पूर्णांक index;

	found = FALSE;
	index = 0;

	जबतक (index < ahc->msgout_len) अणु
		अगर (ahc->msgout_buf[index] == EXTENDED_MESSAGE) अणु
			u_पूर्णांक end_index;

			end_index = index + 1 + ahc->msgout_buf[index + 1];
			अगर (ahc->msgout_buf[index+2] == msgval
			 && type == AHCMSG_EXT) अणु

				अगर (full) अणु
					अगर (ahc->msgout_index > end_index)
						found = TRUE;
				पूर्ण अन्यथा अगर (ahc->msgout_index > index)
					found = TRUE;
			पूर्ण
			index = end_index;
		पूर्ण अन्यथा अगर (ahc->msgout_buf[index] >= SIMPLE_QUEUE_TAG
			&& ahc->msgout_buf[index] <= IGNORE_WIDE_RESIDUE) अणु

			/* Skip tag type and tag id or residue param*/
			index += 2;
		पूर्ण अन्यथा अणु
			/* Single byte message */
			अगर (type == AHCMSG_1B
			 && ahc->msgout_buf[index] == msgval
			 && ahc->msgout_index > index)
				found = TRUE;
			index++;
		पूर्ण

		अगर (found)
			अवरोध;
	पूर्ण
	वापस (found);
पूर्ण

/*
 * Wait क्रम a complete incoming message, parse it, and respond accordingly.
 */
अटल पूर्णांक
ahc_parse_msg(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo)
अणु
	काष्ठा	ahc_initiator_tinfo *tinfo;
	काष्ठा	ahc_पंचांगode_tstate *tstate;
	पूर्णांक	reject;
	पूर्णांक	करोne;
	पूर्णांक	response;
	u_पूर्णांक	targ_scsirate;

	करोne = MSGLOOP_IN_PROG;
	response = FALSE;
	reject = FALSE;
	tinfo = ahc_fetch_transinfo(ahc, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);
	targ_scsirate = tinfo->scsirate;

	/*
	 * Parse as much of the message as is available,
	 * rejecting it अगर we करोn't support it.  When
	 * the entire message is available and has been
	 * handled, वापस MSGLOOP_MSGCOMPLETE, indicating
	 * that we have parsed an entire message.
	 *
	 * In the हाल of extended messages, we accept the length
	 * byte outright and perक्रमm more checking once we know the
	 * extended message type.
	 */
	चयन (ahc->msgin_buf[0]) अणु
	हाल DISCONNECT:
	हाल SAVE_POINTERS:
	हाल COMMAND_COMPLETE:
	हाल RESTORE_POINTERS:
	हाल IGNORE_WIDE_RESIDUE:
		/*
		 * End our message loop as these are messages
		 * the sequencer handles on its own.
		 */
		करोne = MSGLOOP_TERMINATED;
		अवरोध;
	हाल MESSAGE_REJECT:
		response = ahc_handle_msg_reject(ahc, devinfo);
		fallthrough;
	हाल NOP:
		करोne = MSGLOOP_MSGCOMPLETE;
		अवरोध;
	हाल EXTENDED_MESSAGE:
	अणु
		/* Wait क्रम enough of the message to begin validation */
		अगर (ahc->msgin_index < 2)
			अवरोध;
		चयन (ahc->msgin_buf[2]) अणु
		हाल EXTENDED_SDTR:
		अणु
			स्थिर काष्ठा ahc_syncrate *syncrate;
			u_पूर्णांक	 period;
			u_पूर्णांक	 ppr_options;
			u_पूर्णांक	 offset;
			u_पूर्णांक	 saved_offset;

			अगर (ahc->msgin_buf[1] != MSG_EXT_SDTR_LEN) अणु
				reject = TRUE;
				अवरोध;
			पूर्ण

			/*
			 * Wait until we have both args beक्रमe validating
			 * and acting on this message.
			 *
			 * Add one to MSG_EXT_SDTR_LEN to account क्रम
			 * the extended message preamble.
			 */
			अगर (ahc->msgin_index < (MSG_EXT_SDTR_LEN + 1))
				अवरोध;

			period = ahc->msgin_buf[3];
			ppr_options = 0;
			saved_offset = offset = ahc->msgin_buf[4];
			syncrate = ahc_devlimited_syncrate(ahc, tinfo, &period,
							   &ppr_options,
							   devinfo->role);
			ahc_validate_offset(ahc, tinfo, syncrate, &offset,
					    targ_scsirate & WIDEXFER,
					    devinfo->role);
			अगर (bootverbose) अणु
				prपूर्णांकk("(%s:%c:%d:%d): Received "
				       "SDTR period %x, offset %x\n\t"
				       "Filtered to period %x, offset %x\n",
				       ahc_name(ahc), devinfo->channel,
				       devinfo->target, devinfo->lun,
				       ahc->msgin_buf[3], saved_offset,
				       period, offset);
			पूर्ण
			ahc_set_syncrate(ahc, devinfo,
					 syncrate, period,
					 offset, ppr_options,
					 AHC_TRANS_ACTIVE|AHC_TRANS_GOAL,
					 /*छोड़ोd*/TRUE);

			/*
			 * See अगर we initiated Sync Negotiation
			 * and didn't have to fall करोwn to async
			 * transfers.
			 */
			अगर (ahc_sent_msg(ahc, AHCMSG_EXT, EXTENDED_SDTR, TRUE)) अणु
				/* We started it */
				अगर (saved_offset != offset) अणु
					/* Went too low - क्रमce async */
					reject = TRUE;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * Send our own SDTR in reply
				 */
				अगर (bootverbose
				 && devinfo->role == ROLE_INITIATOR) अणु
					prपूर्णांकk("(%s:%c:%d:%d): Target "
					       "Initiated SDTR\n",
					       ahc_name(ahc), devinfo->channel,
					       devinfo->target, devinfo->lun);
				पूर्ण
				ahc->msgout_index = 0;
				ahc->msgout_len = 0;
				ahc_स्थिरruct_sdtr(ahc, devinfo,
						   period, offset);
				ahc->msgout_index = 0;
				response = TRUE;
			पूर्ण
			करोne = MSGLOOP_MSGCOMPLETE;
			अवरोध;
		पूर्ण
		हाल EXTENDED_WDTR:
		अणु
			u_पूर्णांक bus_width;
			u_पूर्णांक saved_width;
			u_पूर्णांक sending_reply;

			sending_reply = FALSE;
			अगर (ahc->msgin_buf[1] != MSG_EXT_WDTR_LEN) अणु
				reject = TRUE;
				अवरोध;
			पूर्ण

			/*
			 * Wait until we have our arg beक्रमe validating
			 * and acting on this message.
			 *
			 * Add one to MSG_EXT_WDTR_LEN to account क्रम
			 * the extended message preamble.
			 */
			अगर (ahc->msgin_index < (MSG_EXT_WDTR_LEN + 1))
				अवरोध;

			bus_width = ahc->msgin_buf[3];
			saved_width = bus_width;
			ahc_validate_width(ahc, tinfo, &bus_width,
					   devinfo->role);
			अगर (bootverbose) अणु
				prपूर्णांकk("(%s:%c:%d:%d): Received WDTR "
				       "%x filtered to %x\n",
				       ahc_name(ahc), devinfo->channel,
				       devinfo->target, devinfo->lun,
				       saved_width, bus_width);
			पूर्ण

			अगर (ahc_sent_msg(ahc, AHCMSG_EXT, EXTENDED_WDTR, TRUE)) अणु
				/*
				 * Don't send a WDTR back to the
				 * target, since we asked first.
				 * If the width went higher than our
				 * request, reject it.
				 */
				अगर (saved_width > bus_width) अणु
					reject = TRUE;
					prपूर्णांकk("(%s:%c:%d:%d): requested %dBit "
					       "transfers.  Rejecting...\n",
					       ahc_name(ahc), devinfo->channel,
					       devinfo->target, devinfo->lun,
					       8 * (0x01 << bus_width));
					bus_width = 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * Send our own WDTR in reply
				 */
				अगर (bootverbose
				 && devinfo->role == ROLE_INITIATOR) अणु
					prपूर्णांकk("(%s:%c:%d:%d): Target "
					       "Initiated WDTR\n",
					       ahc_name(ahc), devinfo->channel,
					       devinfo->target, devinfo->lun);
				पूर्ण
				ahc->msgout_index = 0;
				ahc->msgout_len = 0;
				ahc_स्थिरruct_wdtr(ahc, devinfo, bus_width);
				ahc->msgout_index = 0;
				response = TRUE;
				sending_reply = TRUE;
			पूर्ण
			/*
			 * After a wide message, we are async, but
			 * some devices करोn't seem to honor this portion
			 * of the spec.  Force a renegotiation of the
			 * sync component of our transfer agreement even
			 * अगर our goal is async.  By updating our width
			 * after क्रमcing the negotiation, we aव्योम
			 * renegotiating क्रम width.
			 */
			ahc_update_neg_request(ahc, devinfo, tstate,
					       tinfo, AHC_NEG_ALWAYS);
			ahc_set_width(ahc, devinfo, bus_width,
				      AHC_TRANS_ACTIVE|AHC_TRANS_GOAL,
				      /*छोड़ोd*/TRUE);
			अगर (sending_reply == FALSE && reject == FALSE) अणु

				/*
				 * We will always have an SDTR to send.
				 */
				ahc->msgout_index = 0;
				ahc->msgout_len = 0;
				ahc_build_transfer_msg(ahc, devinfo);
				ahc->msgout_index = 0;
				response = TRUE;
			पूर्ण
			करोne = MSGLOOP_MSGCOMPLETE;
			अवरोध;
		पूर्ण
		हाल EXTENDED_PPR:
		अणु
			स्थिर काष्ठा ahc_syncrate *syncrate;
			u_पूर्णांक	period;
			u_पूर्णांक	offset;
			u_पूर्णांक	bus_width;
			u_पूर्णांक	ppr_options;
			u_पूर्णांक	saved_width;
			u_पूर्णांक	saved_offset;
			u_पूर्णांक	saved_ppr_options;

			अगर (ahc->msgin_buf[1] != MSG_EXT_PPR_LEN) अणु
				reject = TRUE;
				अवरोध;
			पूर्ण

			/*
			 * Wait until we have all args beक्रमe validating
			 * and acting on this message.
			 *
			 * Add one to MSG_EXT_PPR_LEN to account क्रम
			 * the extended message preamble.
			 */
			अगर (ahc->msgin_index < (MSG_EXT_PPR_LEN + 1))
				अवरोध;

			period = ahc->msgin_buf[3];
			offset = ahc->msgin_buf[5];
			bus_width = ahc->msgin_buf[6];
			saved_width = bus_width;
			ppr_options = ahc->msgin_buf[7];
			/*
			 * According to the spec, a DT only
			 * period factor with no DT option
			 * set implies async.
			 */
			अगर ((ppr_options & MSG_EXT_PPR_DT_REQ) == 0
			 && period == 9)
				offset = 0;
			saved_ppr_options = ppr_options;
			saved_offset = offset;

			/*
			 * Mask out any options we करोn't support
			 * on any controller.  Transfer options are
			 * only available अगर we are negotiating wide.
			 */
			ppr_options &= MSG_EXT_PPR_DT_REQ;
			अगर (bus_width == 0)
				ppr_options = 0;

			ahc_validate_width(ahc, tinfo, &bus_width,
					   devinfo->role);
			syncrate = ahc_devlimited_syncrate(ahc, tinfo, &period,
							   &ppr_options,
							   devinfo->role);
			ahc_validate_offset(ahc, tinfo, syncrate,
					    &offset, bus_width,
					    devinfo->role);

			अगर (ahc_sent_msg(ahc, AHCMSG_EXT, EXTENDED_PPR, TRUE)) अणु
				/*
				 * If we are unable to करो any of the
				 * requested options (we went too low),
				 * then we'll have to reject the message.
				 */
				अगर (saved_width > bus_width
				 || saved_offset != offset
				 || saved_ppr_options != ppr_options) अणु
					reject = TRUE;
					period = 0;
					offset = 0;
					bus_width = 0;
					ppr_options = 0;
					syncrate = शून्य;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (devinfo->role != ROLE_TARGET)
					prपूर्णांकk("(%s:%c:%d:%d): Target "
					       "Initiated PPR\n",
					       ahc_name(ahc), devinfo->channel,
					       devinfo->target, devinfo->lun);
				अन्यथा
					prपूर्णांकk("(%s:%c:%d:%d): Initiator "
					       "Initiated PPR\n",
					       ahc_name(ahc), devinfo->channel,
					       devinfo->target, devinfo->lun);
				ahc->msgout_index = 0;
				ahc->msgout_len = 0;
				ahc_स्थिरruct_ppr(ahc, devinfo, period, offset,
						  bus_width, ppr_options);
				ahc->msgout_index = 0;
				response = TRUE;
			पूर्ण
			अगर (bootverbose) अणु
				prपूर्णांकk("(%s:%c:%d:%d): Received PPR width %x, "
				       "period %x, offset %x,options %x\n"
				       "\tFiltered to width %x, period %x, "
				       "offset %x, options %x\n",
				       ahc_name(ahc), devinfo->channel,
				       devinfo->target, devinfo->lun,
				       saved_width, ahc->msgin_buf[3],
				       saved_offset, saved_ppr_options,
				       bus_width, period, offset, ppr_options);
			पूर्ण
			ahc_set_width(ahc, devinfo, bus_width,
				      AHC_TRANS_ACTIVE|AHC_TRANS_GOAL,
				      /*छोड़ोd*/TRUE);
			ahc_set_syncrate(ahc, devinfo,
					 syncrate, period,
					 offset, ppr_options,
					 AHC_TRANS_ACTIVE|AHC_TRANS_GOAL,
					 /*छोड़ोd*/TRUE);
			करोne = MSGLOOP_MSGCOMPLETE;
			अवरोध;
		पूर्ण
		शेष:
			/* Unknown extended message.  Reject it. */
			reject = TRUE;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
#अगर_घोषित AHC_TARGET_MODE
	हाल TARGET_RESET:
		ahc_handle_devreset(ahc, devinfo,
				    CAM_BDR_SENT,
				    "Bus Device Reset Received",
				    /*verbose_level*/0);
		ahc_restart(ahc);
		करोne = MSGLOOP_TERMINATED;
		अवरोध;
	हाल ABORT_TASK:
	हाल ABORT_TASK_SET:
	हाल CLEAR_QUEUE_TASK_SET:
	अणु
		पूर्णांक tag;

		/* Target mode messages */
		अगर (devinfo->role != ROLE_TARGET) अणु
			reject = TRUE;
			अवरोध;
		पूर्ण
		tag = SCB_LIST_शून्य;
		अगर (ahc->msgin_buf[0] == ABORT_TASK)
			tag = ahc_inb(ahc, INITIATOR_TAG);
		ahc_पात_scbs(ahc, devinfo->target, devinfo->channel,
			       devinfo->lun, tag, ROLE_TARGET,
			       CAM_REQ_ABORTED);

		tstate = ahc->enabled_tarमाला_लो[devinfo->our_scsiid];
		अगर (tstate != शून्य) अणु
			काष्ठा ahc_पंचांगode_lstate* lstate;

			lstate = tstate->enabled_luns[devinfo->lun];
			अगर (lstate != शून्य) अणु
				ahc_queue_lstate_event(ahc, lstate,
						       devinfo->our_scsiid,
						       ahc->msgin_buf[0],
						       /*arg*/tag);
				ahc_send_lstate_events(ahc, lstate);
			पूर्ण
		पूर्ण
		ahc_restart(ahc);
		करोne = MSGLOOP_TERMINATED;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल TERMINATE_IO_PROC:
	शेष:
		reject = TRUE;
		अवरोध;
	पूर्ण

	अगर (reject) अणु
		/*
		 * Setup to reject the message.
		 */
		ahc->msgout_index = 0;
		ahc->msgout_len = 1;
		ahc->msgout_buf[0] = MESSAGE_REJECT;
		करोne = MSGLOOP_MSGCOMPLETE;
		response = TRUE;
	पूर्ण

	अगर (करोne != MSGLOOP_IN_PROG && !response)
		/* Clear the outgoing message buffer */
		ahc->msgout_len = 0;

	वापस (करोne);
पूर्ण

/*
 * Process a message reject message.
 */
अटल पूर्णांक
ahc_handle_msg_reject(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo)
अणु
	/*
	 * What we care about here is अगर we had an
	 * outstanding SDTR or WDTR message क्रम this
	 * target.  If we did, this is a संकेत that
	 * the target is refusing negotiation.
	 */
	काष्ठा scb *scb;
	काष्ठा ahc_initiator_tinfo *tinfo;
	काष्ठा ahc_पंचांगode_tstate *tstate;
	u_पूर्णांक scb_index;
	u_पूर्णांक last_msg;
	पूर्णांक   response = 0;

	scb_index = ahc_inb(ahc, SCB_TAG);
	scb = ahc_lookup_scb(ahc, scb_index);
	tinfo = ahc_fetch_transinfo(ahc, devinfo->channel,
				    devinfo->our_scsiid,
				    devinfo->target, &tstate);
	/* Might be necessary */
	last_msg = ahc_inb(ahc, LAST_MSG);

	अगर (ahc_sent_msg(ahc, AHCMSG_EXT, EXTENDED_PPR, /*full*/FALSE)) अणु
		/*
		 * Target करोes not support the PPR message.
		 * Attempt to negotiate SPI-2 style.
		 */
		अगर (bootverbose) अणु
			prपूर्णांकk("(%s:%c:%d:%d): PPR Rejected. "
			       "Trying WDTR/SDTR\n",
			       ahc_name(ahc), devinfo->channel,
			       devinfo->target, devinfo->lun);
		पूर्ण
		tinfo->goal.ppr_options = 0;
		tinfo->curr.transport_version = 2;
		tinfo->goal.transport_version = 2;
		ahc->msgout_index = 0;
		ahc->msgout_len = 0;
		ahc_build_transfer_msg(ahc, devinfo);
		ahc->msgout_index = 0;
		response = 1;
	पूर्ण अन्यथा अगर (ahc_sent_msg(ahc, AHCMSG_EXT, EXTENDED_WDTR, /*full*/FALSE)) अणु

		/* note 8bit xfers */
		prपूर्णांकk("(%s:%c:%d:%d): refuses WIDE negotiation.  Using "
		       "8bit transfers\n", ahc_name(ahc),
		       devinfo->channel, devinfo->target, devinfo->lun);
		ahc_set_width(ahc, devinfo, MSG_EXT_WDTR_BUS_8_BIT,
			      AHC_TRANS_ACTIVE|AHC_TRANS_GOAL,
			      /*छोड़ोd*/TRUE);
		/*
		 * No need to clear the sync rate.  If the target
		 * did not accept the command, our syncrate is
		 * unaffected.  If the target started the negotiation,
		 * but rejected our response, we alपढ़ोy cleared the
		 * sync rate beक्रमe sending our WDTR.
		 */
		अगर (tinfo->goal.offset != tinfo->curr.offset) अणु

			/* Start the sync negotiation */
			ahc->msgout_index = 0;
			ahc->msgout_len = 0;
			ahc_build_transfer_msg(ahc, devinfo);
			ahc->msgout_index = 0;
			response = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (ahc_sent_msg(ahc, AHCMSG_EXT, EXTENDED_SDTR, /*full*/FALSE)) अणु
		/* note asynch xfers and clear flag */
		ahc_set_syncrate(ahc, devinfo, /*syncrate*/शून्य, /*period*/0,
				 /*offset*/0, /*ppr_options*/0,
				 AHC_TRANS_ACTIVE|AHC_TRANS_GOAL,
				 /*छोड़ोd*/TRUE);
		prपूर्णांकk("(%s:%c:%d:%d): refuses synchronous negotiation. "
		       "Using asynchronous transfers\n",
		       ahc_name(ahc), devinfo->channel,
		       devinfo->target, devinfo->lun);
	पूर्ण अन्यथा अगर ((scb->hscb->control & SIMPLE_QUEUE_TAG) != 0) अणु
		पूर्णांक tag_type;
		पूर्णांक mask;

		tag_type = (scb->hscb->control & SIMPLE_QUEUE_TAG);

		अगर (tag_type == SIMPLE_QUEUE_TAG) अणु
			prपूर्णांकk("(%s:%c:%d:%d): refuses tagged commands.  "
			       "Performing non-tagged I/O\n", ahc_name(ahc),
			       devinfo->channel, devinfo->target, devinfo->lun);
			ahc_set_tags(ahc, scb->io_ctx, devinfo, AHC_QUEUE_NONE);
			mask = ~0x23;
		पूर्ण अन्यथा अणु
			prपूर्णांकk("(%s:%c:%d:%d): refuses %s tagged commands.  "
			       "Performing simple queue tagged I/O only\n",
			       ahc_name(ahc), devinfo->channel, devinfo->target,
			       devinfo->lun, tag_type == ORDERED_QUEUE_TAG
			       ? "ordered" : "head of queue");
			ahc_set_tags(ahc, scb->io_ctx, devinfo, AHC_QUEUE_BASIC);
			mask = ~0x03;
		पूर्ण

		/*
		 * Resend the identअगरy क्रम this CCB as the target
		 * may believe that the selection is invalid otherwise.
		 */
		ahc_outb(ahc, SCB_CONTROL,
			 ahc_inb(ahc, SCB_CONTROL) & mask);
		scb->hscb->control &= mask;
		ahc_set_transaction_tag(scb, /*enabled*/FALSE,
					/*type*/SIMPLE_QUEUE_TAG);
		ahc_outb(ahc, MSG_OUT, MSG_IDENTIFYFLAG);
		ahc_निश्चित_atn(ahc);

		/*
		 * This transaction is now at the head of
		 * the untagged queue क्रम this target.
		 */
		अगर ((ahc->flags & AHC_SCB_BTT) == 0) अणु
			काष्ठा scb_tailq *untagged_q;

			untagged_q =
			    &(ahc->untagged_queues[devinfo->target_offset]);
			TAILQ_INSERT_HEAD(untagged_q, scb, links.tqe);
			scb->flags |= SCB_UNTAGGEDQ;
		पूर्ण
		ahc_busy_tcl(ahc, BUILD_TCL(scb->hscb->scsiid, devinfo->lun),
			     scb->hscb->tag);

		/*
		 * Requeue all tagged commands क्रम this target
		 * currently in our possession so they can be
		 * converted to untagged commands.
		 */
		ahc_search_qinfअगरo(ahc, SCB_GET_TARGET(ahc, scb),
				   SCB_GET_CHANNEL(ahc, scb),
				   SCB_GET_LUN(scb), /*tag*/SCB_LIST_शून्य,
				   ROLE_INITIATOR, CAM_REQUEUE_REQ,
				   SEARCH_COMPLETE);
	पूर्ण अन्यथा अणु
		/*
		 * Otherwise, we ignore it.
		 */
		prपूर्णांकk("%s:%c:%d: Message reject for %x -- ignored\n",
		       ahc_name(ahc), devinfo->channel, devinfo->target,
		       last_msg);
	पूर्ण
	वापस (response);
पूर्ण

/*
 * Process an ingnore wide residue message.
 */
अटल व्योम
ahc_handle_ign_wide_residue(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo)
अणु
	u_पूर्णांक scb_index;
	काष्ठा scb *scb;

	scb_index = ahc_inb(ahc, SCB_TAG);
	scb = ahc_lookup_scb(ahc, scb_index);
	/*
	 * XXX Actually check data direction in the sequencer?
	 * Perhaps add datadir to some spare bits in the hscb?
	 */
	अगर ((ahc_inb(ahc, SEQ_FLAGS) & DPHASE) == 0
	 || ahc_get_transfer_dir(scb) != CAM_सूची_IN) अणु
		/*
		 * Ignore the message अगर we haven't
		 * seen an appropriate data phase yet.
		 */
	पूर्ण अन्यथा अणु
		/*
		 * If the residual occurred on the last
		 * transfer and the transfer request was
		 * expected to end on an odd count, करो
		 * nothing.  Otherwise, subtract a byte
		 * and update the residual count accordingly.
		 */
		uपूर्णांक32_t sgptr;

		sgptr = ahc_inb(ahc, SCB_RESIDUAL_SGPTR);
		अगर ((sgptr & SG_LIST_शून्य) != 0
		 && (ahc_inb(ahc, SCB_LUN) & SCB_XFERLEN_ODD) != 0) अणु
			/*
			 * If the residual occurred on the last
			 * transfer and the transfer request was
			 * expected to end on an odd count, करो
			 * nothing.
			 */
		पूर्ण अन्यथा अणु
			काष्ठा ahc_dma_seg *sg;
			uपूर्णांक32_t data_cnt;
			uपूर्णांक32_t data_addr;
			uपूर्णांक32_t sglen;

			/* Pull in all of the sgptr */
			sgptr = ahc_inl(ahc, SCB_RESIDUAL_SGPTR);
			data_cnt = ahc_inl(ahc, SCB_RESIDUAL_DATACNT);

			अगर ((sgptr & SG_LIST_शून्य) != 0) अणु
				/*
				 * The residual data count is not updated
				 * क्रम the command run to completion हाल.
				 * Explicitly zero the count.
				 */
				data_cnt &= ~AHC_SG_LEN_MASK;
			पूर्ण

			data_addr = ahc_inl(ahc, SHADDR);

			data_cnt += 1;
			data_addr -= 1;
			sgptr &= SG_PTR_MASK;

			sg = ahc_sg_bus_to_virt(scb, sgptr);

			/*
			 * The residual sg ptr poपूर्णांकs to the next S/G
			 * to load so we must go back one.
			 */
			sg--;
			sglen = ahc_le32toh(sg->len) & AHC_SG_LEN_MASK;
			अगर (sg != scb->sg_list
			 && sglen < (data_cnt & AHC_SG_LEN_MASK)) अणु

				sg--;
				sglen = ahc_le32toh(sg->len);
				/*
				 * Preserve High Address and SG_LIST bits
				 * जबतक setting the count to 1.
				 */
				data_cnt = 1 | (sglen & (~AHC_SG_LEN_MASK));
				data_addr = ahc_le32toh(sg->addr)
					  + (sglen & AHC_SG_LEN_MASK) - 1;

				/*
				 * Increment sg so it poपूर्णांकs to the
				 * "next" sg.
				 */
				sg++;
				sgptr = ahc_sg_virt_to_bus(scb, sg);
			पूर्ण
			ahc_outl(ahc, SCB_RESIDUAL_SGPTR, sgptr);
			ahc_outl(ahc, SCB_RESIDUAL_DATACNT, data_cnt);
			/*
			 * Toggle the "oddness" of the transfer length
			 * to handle this mid-transfer ignore wide
			 * residue.  This ensures that the oddness is
			 * correct क्रम subsequent data transfers.
			 */
			ahc_outb(ahc, SCB_LUN,
				 ahc_inb(ahc, SCB_LUN) ^ SCB_XFERLEN_ODD);
		पूर्ण
	पूर्ण
पूर्ण


/*
 * Reinitialize the data poपूर्णांकers क्रम the active transfer
 * based on its current residual.
 */
अटल व्योम
ahc_reinitialize_dataptrs(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा	 scb *scb;
	काष्ठा	 ahc_dma_seg *sg;
	u_पूर्णांक	 scb_index;
	uपूर्णांक32_t sgptr;
	uपूर्णांक32_t resid;
	uपूर्णांक32_t dataptr;

	scb_index = ahc_inb(ahc, SCB_TAG);
	scb = ahc_lookup_scb(ahc, scb_index);
	sgptr = (ahc_inb(ahc, SCB_RESIDUAL_SGPTR + 3) << 24)
	      | (ahc_inb(ahc, SCB_RESIDUAL_SGPTR + 2) << 16)
	      | (ahc_inb(ahc, SCB_RESIDUAL_SGPTR + 1) << 8)
	      |	ahc_inb(ahc, SCB_RESIDUAL_SGPTR);

	sgptr &= SG_PTR_MASK;
	sg = ahc_sg_bus_to_virt(scb, sgptr);

	/* The residual sg_ptr always poपूर्णांकs to the next sg */
	sg--;

	resid = (ahc_inb(ahc, SCB_RESIDUAL_DATACNT + 2) << 16)
	      | (ahc_inb(ahc, SCB_RESIDUAL_DATACNT + 1) << 8)
	      | ahc_inb(ahc, SCB_RESIDUAL_DATACNT);

	dataptr = ahc_le32toh(sg->addr)
		+ (ahc_le32toh(sg->len) & AHC_SG_LEN_MASK)
		- resid;
	अगर ((ahc->flags & AHC_39BIT_ADDRESSING) != 0) अणु
		u_पूर्णांक dscommand1;

		dscommand1 = ahc_inb(ahc, DSCOMMAND1);
		ahc_outb(ahc, DSCOMMAND1, dscommand1 | HADDLDSEL0);
		ahc_outb(ahc, HADDR,
			 (ahc_le32toh(sg->len) >> 24) & SG_HIGH_ADDR_BITS);
		ahc_outb(ahc, DSCOMMAND1, dscommand1);
	पूर्ण
	ahc_outb(ahc, HADDR + 3, dataptr >> 24);
	ahc_outb(ahc, HADDR + 2, dataptr >> 16);
	ahc_outb(ahc, HADDR + 1, dataptr >> 8);
	ahc_outb(ahc, HADDR, dataptr);
	ahc_outb(ahc, HCNT + 2, resid >> 16);
	ahc_outb(ahc, HCNT + 1, resid >> 8);
	ahc_outb(ahc, HCNT, resid);
	अगर ((ahc->features & AHC_ULTRA2) == 0) अणु
		ahc_outb(ahc, STCNT + 2, resid >> 16);
		ahc_outb(ahc, STCNT + 1, resid >> 8);
		ahc_outb(ahc, STCNT, resid);
	पूर्ण
पूर्ण

/*
 * Handle the effects of issuing a bus device reset message.
 */
अटल व्योम
ahc_handle_devreset(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo,
		    cam_status status, अक्षर *message, पूर्णांक verbose_level)
अणु
#अगर_घोषित AHC_TARGET_MODE
	काष्ठा ahc_पंचांगode_tstate* tstate;
	u_पूर्णांक lun;
#पूर्ण_अगर
	पूर्णांक found;

	found = ahc_पात_scbs(ahc, devinfo->target, devinfo->channel,
			       CAM_LUN_WILDCARD, SCB_LIST_शून्य, devinfo->role,
			       status);

#अगर_घोषित AHC_TARGET_MODE
	/*
	 * Send an immediate notअगरy ccb to all target mord peripheral
	 * drivers affected by this action.
	 */
	tstate = ahc->enabled_tarमाला_लो[devinfo->our_scsiid];
	अगर (tstate != शून्य) अणु
		क्रम (lun = 0; lun < AHC_NUM_LUNS; lun++) अणु
			काष्ठा ahc_पंचांगode_lstate* lstate;

			lstate = tstate->enabled_luns[lun];
			अगर (lstate == शून्य)
				जारी;

			ahc_queue_lstate_event(ahc, lstate, devinfo->our_scsiid,
					       TARGET_RESET, /*arg*/0);
			ahc_send_lstate_events(ahc, lstate);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * Go back to async/narrow transfers and renegotiate.
	 */
	ahc_set_width(ahc, devinfo, MSG_EXT_WDTR_BUS_8_BIT,
		      AHC_TRANS_CUR, /*छोड़ोd*/TRUE);
	ahc_set_syncrate(ahc, devinfo, /*syncrate*/शून्य,
			 /*period*/0, /*offset*/0, /*ppr_options*/0,
			 AHC_TRANS_CUR, /*छोड़ोd*/TRUE);

	अगर (status != CAM_SEL_TIMEOUT)
		ahc_send_async(ahc, devinfo->channel, devinfo->target,
			       CAM_LUN_WILDCARD, AC_SENT_BDR);

	अगर (message != शून्य
	 && (verbose_level <= bootverbose))
		prपूर्णांकk("%s: %s on %c:%d. %d SCBs aborted\n", ahc_name(ahc),
		       message, devinfo->channel, devinfo->target, found);
पूर्ण

#अगर_घोषित AHC_TARGET_MODE
अटल व्योम
ahc_setup_target_msgin(काष्ठा ahc_softc *ahc, काष्ठा ahc_devinfo *devinfo,
		       काष्ठा scb *scb)
अणु

	/*
	 * To facilitate adding multiple messages together,
	 * each routine should increment the index and len
	 * variables instead of setting them explicitly.
	 */
	ahc->msgout_index = 0;
	ahc->msgout_len = 0;

	अगर (scb != शून्य && (scb->flags & SCB_AUTO_NEGOTIATE) != 0)
		ahc_build_transfer_msg(ahc, devinfo);
	अन्यथा
		panic("ahc_intr: AWAITING target message with no message");

	ahc->msgout_index = 0;
	ahc->msg_type = MSG_TYPE_TARGET_MSGIN;
पूर्ण
#पूर्ण_अगर
/**************************** Initialization **********************************/
/*
 * Allocate a controller काष्ठाure क्रम a new device
 * and perक्रमm initial initializion.
 */
काष्ठा ahc_softc *
ahc_alloc(व्योम *platक्रमm_arg, अक्षर *name)
अणु
	काष्ठा  ahc_softc *ahc;
	पूर्णांक	i;

	ahc = kzalloc(माप(*ahc), GFP_ATOMIC);
	अगर (!ahc) अणु
		prपूर्णांकk("aic7xxx: cannot malloc softc!\n");
		kमुक्त(name);
		वापस शून्य;
	पूर्ण

	ahc->seep_config = kदो_स्मृति(माप(*ahc->seep_config), GFP_ATOMIC);
	अगर (ahc->seep_config == शून्य) अणु
		kमुक्त(ahc);
		kमुक्त(name);
		वापस (शून्य);
	पूर्ण
	LIST_INIT(&ahc->pending_scbs);
	/* We करोn't know our unit number until the OSM sets it */
	ahc->name = name;
	ahc->unit = -1;
	ahc->description = शून्य;
	ahc->channel = 'A';
	ahc->channel_b = 'B';
	ahc->chip = AHC_NONE;
	ahc->features = AHC_FENONE;
	ahc->bugs = AHC_BUGNONE;
	ahc->flags = AHC_FNONE;
	/*
	 * Default to all error reporting enabled with the
	 * sequencer operating at its fastest speed.
	 * The bus attach code may modअगरy this.
	 */
	ahc->seqctl = FASTMODE;

	क्रम (i = 0; i < AHC_NUM_TARGETS; i++)
		TAILQ_INIT(&ahc->untagged_queues[i]);
	अगर (ahc_platक्रमm_alloc(ahc, platक्रमm_arg) != 0) अणु
		ahc_मुक्त(ahc);
		ahc = शून्य;
	पूर्ण
	वापस (ahc);
पूर्ण

पूर्णांक
ahc_softc_init(काष्ठा ahc_softc *ahc)
अणु

	/* The IRQMS bit is only valid on VL and EISA chips */
	अगर ((ahc->chip & AHC_PCI) == 0)
		ahc->unछोड़ो = ahc_inb(ahc, HCNTRL) & IRQMS;
	अन्यथा
		ahc->unछोड़ो = 0;
	ahc->छोड़ो = ahc->unछोड़ो | PAUSE;
	/* XXX The shared scb data stuff should be deprecated */
	अगर (ahc->scb_data == शून्य) अणु
		ahc->scb_data = kzalloc(माप(*ahc->scb_data), GFP_ATOMIC);
		अगर (ahc->scb_data == शून्य)
			वापस (ENOMEM);
	पूर्ण

	वापस (0);
पूर्ण

व्योम
ahc_set_unit(काष्ठा ahc_softc *ahc, पूर्णांक unit)
अणु
	ahc->unit = unit;
पूर्ण

व्योम
ahc_set_name(काष्ठा ahc_softc *ahc, अक्षर *name)
अणु
	kमुक्त(ahc->name);
	ahc->name = name;
पूर्ण

व्योम
ahc_मुक्त(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक i;

	चयन (ahc->init_level) अणु
	शेष:
	हाल 5:
		ahc_shutकरोwn(ahc);
		fallthrough;
	हाल 4:
		ahc_dmamap_unload(ahc, ahc->shared_data_dmat,
				  ahc->shared_data_dmamap);
		fallthrough;
	हाल 3:
		ahc_dmamem_मुक्त(ahc, ahc->shared_data_dmat, ahc->qoutfअगरo,
				ahc->shared_data_dmamap);
		ahc_dmamap_destroy(ahc, ahc->shared_data_dmat,
				   ahc->shared_data_dmamap);
		fallthrough;
	हाल 2:
		ahc_dma_tag_destroy(ahc, ahc->shared_data_dmat);
		fallthrough;
	हाल 1:
		अवरोध;
	हाल 0:
		अवरोध;
	पूर्ण

	ahc_platक्रमm_मुक्त(ahc);
	ahc_fini_scbdata(ahc);
	क्रम (i = 0; i < AHC_NUM_TARGETS; i++) अणु
		काष्ठा ahc_पंचांगode_tstate *tstate;

		tstate = ahc->enabled_tarमाला_लो[i];
		अगर (tstate != शून्य) अणु
#अगर_घोषित AHC_TARGET_MODE
			पूर्णांक j;

			क्रम (j = 0; j < AHC_NUM_LUNS; j++) अणु
				काष्ठा ahc_पंचांगode_lstate *lstate;

				lstate = tstate->enabled_luns[j];
				अगर (lstate != शून्य) अणु
					xpt_मुक्त_path(lstate->path);
					kमुक्त(lstate);
				पूर्ण
			पूर्ण
#पूर्ण_अगर
			kमुक्त(tstate);
		पूर्ण
	पूर्ण
#अगर_घोषित AHC_TARGET_MODE
	अगर (ahc->black_hole != शून्य) अणु
		xpt_मुक्त_path(ahc->black_hole->path);
		kमुक्त(ahc->black_hole);
	पूर्ण
#पूर्ण_अगर
	kमुक्त(ahc->name);
	kमुक्त(ahc->seep_config);
	kमुक्त(ahc);
	वापस;
पूर्ण

अटल व्योम
ahc_shutकरोwn(व्योम *arg)
अणु
	काष्ठा	ahc_softc *ahc;
	पूर्णांक	i;

	ahc = (काष्ठा ahc_softc *)arg;

	/* This will reset most रेजिस्टरs to 0, but not all */
	ahc_reset(ahc, /*reinit*/FALSE);
	ahc_outb(ahc, SCSISEQ, 0);
	ahc_outb(ahc, SXFRCTL0, 0);
	ahc_outb(ahc, DSPCISTATUS, 0);

	क्रम (i = TARG_SCSIRATE; i < SCSICONF; i++)
		ahc_outb(ahc, i, 0);
पूर्ण

/*
 * Reset the controller and record some inक्रमmation about it
 * that is only available just after a reset.  If "reinit" is
 * non-zero, this reset occurred after initial configuration
 * and the caller requests that the chip be fully reinitialized
 * to a runable state.  Chip पूर्णांकerrupts are *not* enabled after
 * a reinitialization.  The caller must enable पूर्णांकerrupts via
 * ahc_पूर्णांकr_enable().
 */
पूर्णांक
ahc_reset(काष्ठा ahc_softc *ahc, पूर्णांक reinit)
अणु
	u_पूर्णांक	sblkctl;
	u_पूर्णांक	sxfrctl1_a, sxfrctl1_b;
	पूर्णांक	error;
	पूर्णांक	रुको;

	/*
	 * Preserve the value of the SXFRCTL1 रेजिस्टर क्रम all channels.
	 * It contains settings that affect termination and we करोn't want
	 * to disturb the पूर्णांकegrity of the bus.
	 */
	ahc_छोड़ो(ahc);
	sxfrctl1_b = 0;
	अगर ((ahc->chip & AHC_CHIPID_MASK) == AHC_AIC7770) अणु
		u_पूर्णांक sblkctl;

		/*
		 * Save channel B's settings in हाल this chip
		 * is setup क्रम TWIN channel operation.
		 */
		sblkctl = ahc_inb(ahc, SBLKCTL);
		ahc_outb(ahc, SBLKCTL, sblkctl | SELBUSB);
		sxfrctl1_b = ahc_inb(ahc, SXFRCTL1);
		ahc_outb(ahc, SBLKCTL, sblkctl & ~SELBUSB);
	पूर्ण
	sxfrctl1_a = ahc_inb(ahc, SXFRCTL1);

	ahc_outb(ahc, HCNTRL, CHIPRST | ahc->छोड़ो);

	/*
	 * Ensure that the reset has finished.  We delay 1000us
	 * prior to पढ़ोing the रेजिस्टर to make sure the chip
	 * has sufficiently completed its reset to handle रेजिस्टर
	 * accesses.
	 */
	रुको = 1000;
	करो अणु
		ahc_delay(1000);
	पूर्ण जबतक (--रुको && !(ahc_inb(ahc, HCNTRL) & CHIPRSTACK));

	अगर (रुको == 0) अणु
		prपूर्णांकk("%s: WARNING - Failed chip reset!  "
		       "Trying to initialize anyway.\n", ahc_name(ahc));
	पूर्ण
	ahc_outb(ahc, HCNTRL, ahc->छोड़ो);

	/* Determine channel configuration */
	sblkctl = ahc_inb(ahc, SBLKCTL) & (SELBUSB|SELWIDE);
	/* No Twin Channel PCI cards */
	अगर ((ahc->chip & AHC_PCI) != 0)
		sblkctl &= ~SELBUSB;
	चयन (sblkctl) अणु
	हाल 0:
		/* Single Narrow Channel */
		अवरोध;
	हाल 2:
		/* Wide Channel */
		ahc->features |= AHC_WIDE;
		अवरोध;
	हाल 8:
		/* Twin Channel */
		ahc->features |= AHC_TWIN;
		अवरोध;
	शेष:
		prपूर्णांकk(" Unsupported adapter type.  Ignoring\n");
		वापस(-1);
	पूर्ण

	/*
	 * Reload sxfrctl1.
	 *
	 * We must always initialize STPWEN to 1 beक्रमe we
	 * restore the saved values.  STPWEN is initialized
	 * to a tri-state condition which can only be cleared
	 * by turning it on.
	 */
	अगर ((ahc->features & AHC_TWIN) != 0) अणु
		u_पूर्णांक sblkctl;

		sblkctl = ahc_inb(ahc, SBLKCTL);
		ahc_outb(ahc, SBLKCTL, sblkctl | SELBUSB);
		ahc_outb(ahc, SXFRCTL1, sxfrctl1_b);
		ahc_outb(ahc, SBLKCTL, sblkctl & ~SELBUSB);
	पूर्ण
	ahc_outb(ahc, SXFRCTL1, sxfrctl1_a);

	error = 0;
	अगर (reinit != 0)
		/*
		 * If a recovery action has क्रमced a chip reset,
		 * re-initialize the chip to our liking.
		 */
		error = ahc->bus_chip_init(ahc);
#अगर_घोषित AHC_DUMP_SEQ
	अन्यथा
		ahc_dumpseq(ahc);
#पूर्ण_अगर

	वापस (error);
पूर्ण

/*
 * Determine the number of SCBs available on the controller
 */
पूर्णांक
ahc_probe_scbs(काष्ठा ahc_softc *ahc) अणु
	पूर्णांक i;

	क्रम (i = 0; i < AHC_SCB_MAX; i++) अणु

		ahc_outb(ahc, SCBPTR, i);
		ahc_outb(ahc, SCB_BASE, i);
		अगर (ahc_inb(ahc, SCB_BASE) != i)
			अवरोध;
		ahc_outb(ahc, SCBPTR, 0);
		अगर (ahc_inb(ahc, SCB_BASE) != 0)
			अवरोध;
	पूर्ण
	वापस (i);
पूर्ण

अटल व्योम
ahc_dmamap_cb(व्योम *arg, bus_dma_segment_t *segs, पूर्णांक nseg, पूर्णांक error) 
अणु
	dma_addr_t *baddr;

	baddr = (dma_addr_t *)arg;
	*baddr = segs->ds_addr;
पूर्ण

अटल व्योम
ahc_build_मुक्त_scb_list(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक scbsize;
	पूर्णांक i;

	scbsize = 32;
	अगर ((ahc->flags & AHC_LSCBS_ENABLED) != 0)
		scbsize = 64;

	क्रम (i = 0; i < ahc->scb_data->maxhscbs; i++) अणु
		पूर्णांक j;

		ahc_outb(ahc, SCBPTR, i);

		/*
		 * Touch all SCB bytes to aव्योम parity errors
		 * should one of our debugging routines पढ़ो
		 * an otherwise uninitiatlized byte.
		 */
		क्रम (j = 0; j < scbsize; j++)
			ahc_outb(ahc, SCB_BASE+j, 0xFF);

		/* Clear the control byte. */
		ahc_outb(ahc, SCB_CONTROL, 0);

		/* Set the next poपूर्णांकer */
		अगर ((ahc->flags & AHC_PAGESCBS) != 0)
			ahc_outb(ahc, SCB_NEXT, i+1);
		अन्यथा
			ahc_outb(ahc, SCB_NEXT, SCB_LIST_शून्य);

		/* Make the tag number, SCSIID, and lun invalid */
		ahc_outb(ahc, SCB_TAG, SCB_LIST_शून्य);
		ahc_outb(ahc, SCB_SCSIID, 0xFF);
		ahc_outb(ahc, SCB_LUN, 0xFF);
	पूर्ण

	अगर ((ahc->flags & AHC_PAGESCBS) != 0) अणु
		/* SCB 0 heads the मुक्त list. */
		ahc_outb(ahc, FREE_SCBH, 0);
	पूर्ण अन्यथा अणु
		/* No मुक्त list. */
		ahc_outb(ahc, FREE_SCBH, SCB_LIST_शून्य);
	पूर्ण

	/* Make sure that the last SCB terminates the मुक्त list */
	ahc_outb(ahc, SCBPTR, i-1);
	ahc_outb(ahc, SCB_NEXT, SCB_LIST_शून्य);
पूर्ण

अटल पूर्णांक
ahc_init_scbdata(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा scb_data *scb_data;

	scb_data = ahc->scb_data;
	SLIST_INIT(&scb_data->मुक्त_scbs);
	SLIST_INIT(&scb_data->sg_maps);

	/* Allocate SCB resources */
	scb_data->scbarray = kसुस्मृति(AHC_SCB_MAX_ALLOC, माप(काष्ठा scb),
				     GFP_ATOMIC);
	अगर (scb_data->scbarray == शून्य)
		वापस (ENOMEM);

	/* Determine the number of hardware SCBs and initialize them */

	scb_data->maxhscbs = ahc_probe_scbs(ahc);
	अगर (ahc->scb_data->maxhscbs == 0) अणु
		prपूर्णांकk("%s: No SCB space found\n", ahc_name(ahc));
		वापस (ENXIO);
	पूर्ण

	/*
	 * Create our DMA tags.  These tags define the kinds of device
	 * accessible memory allocations and memory mappings we will
	 * need to perक्रमm during normal operation.
	 *
	 * Unless we need to further restrict the allocation, we rely
	 * on the restrictions of the parent dmat, hence the common
	 * use of MAXADDR and MAXSIZE.
	 */

	/* DMA tag क्रम our hardware scb काष्ठाures */
	अगर (ahc_dma_tag_create(ahc, ahc->parent_dmat, /*alignment*/1,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/शून्य, /*filterarg*/शून्य,
			       AHC_SCB_MAX_ALLOC * माप(काष्ठा hardware_scb),
			       /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &scb_data->hscb_dmat) != 0) अणु
		जाओ error_निकास;
	पूर्ण

	scb_data->init_level++;

	/* Allocation क्रम our hscbs */
	अगर (ahc_dmamem_alloc(ahc, scb_data->hscb_dmat,
			     (व्योम **)&scb_data->hscbs,
			     BUS_DMA_NOWAIT, &scb_data->hscb_dmamap) != 0) अणु
		जाओ error_निकास;
	पूर्ण

	scb_data->init_level++;

	/* And permanently map them */
	ahc_dmamap_load(ahc, scb_data->hscb_dmat, scb_data->hscb_dmamap,
			scb_data->hscbs,
			AHC_SCB_MAX_ALLOC * माप(काष्ठा hardware_scb),
			ahc_dmamap_cb, &scb_data->hscb_busaddr, /*flags*/0);

	scb_data->init_level++;

	/* DMA tag क्रम our sense buffers */
	अगर (ahc_dma_tag_create(ahc, ahc->parent_dmat, /*alignment*/1,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/शून्य, /*filterarg*/शून्य,
			       AHC_SCB_MAX_ALLOC * माप(काष्ठा scsi_sense_data),
			       /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &scb_data->sense_dmat) != 0) अणु
		जाओ error_निकास;
	पूर्ण

	scb_data->init_level++;

	/* Allocate them */
	अगर (ahc_dmamem_alloc(ahc, scb_data->sense_dmat,
			     (व्योम **)&scb_data->sense,
			     BUS_DMA_NOWAIT, &scb_data->sense_dmamap) != 0) अणु
		जाओ error_निकास;
	पूर्ण

	scb_data->init_level++;

	/* And permanently map them */
	ahc_dmamap_load(ahc, scb_data->sense_dmat, scb_data->sense_dmamap,
			scb_data->sense,
			AHC_SCB_MAX_ALLOC * माप(काष्ठा scsi_sense_data),
			ahc_dmamap_cb, &scb_data->sense_busaddr, /*flags*/0);

	scb_data->init_level++;

	/* DMA tag क्रम our S/G काष्ठाures.  We allocate in page sized chunks */
	अगर (ahc_dma_tag_create(ahc, ahc->parent_dmat, /*alignment*/8,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/शून्य, /*filterarg*/शून्य,
			       PAGE_SIZE, /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &scb_data->sg_dmat) != 0) अणु
		जाओ error_निकास;
	पूर्ण

	scb_data->init_level++;

	/* Perक्रमm initial CCB allocation */
	स_रखो(scb_data->hscbs, 0,
	       AHC_SCB_MAX_ALLOC * माप(काष्ठा hardware_scb));
	ahc_alloc_scbs(ahc);

	अगर (scb_data->numscbs == 0) अणु
		prपूर्णांकk("%s: ahc_init_scbdata - "
		       "Unable to allocate initial scbs\n",
		       ahc_name(ahc));
		जाओ error_निकास;
	पूर्ण

	/*
	 * Reserve the next queued SCB.
	 */
	ahc->next_queued_scb = ahc_get_scb(ahc);

	/*
	 * Note that we were successful
	 */
	वापस (0);

error_निकास:

	वापस (ENOMEM);
पूर्ण

अटल व्योम
ahc_fini_scbdata(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा scb_data *scb_data;

	scb_data = ahc->scb_data;
	अगर (scb_data == शून्य)
		वापस;

	चयन (scb_data->init_level) अणु
	शेष:
	हाल 7:
	अणु
		काष्ठा sg_map_node *sg_map;

		जबतक ((sg_map = SLIST_FIRST(&scb_data->sg_maps))!= शून्य) अणु
			SLIST_REMOVE_HEAD(&scb_data->sg_maps, links);
			ahc_dmamap_unload(ahc, scb_data->sg_dmat,
					  sg_map->sg_dmamap);
			ahc_dmamem_मुक्त(ahc, scb_data->sg_dmat,
					sg_map->sg_vaddr,
					sg_map->sg_dmamap);
			kमुक्त(sg_map);
		पूर्ण
		ahc_dma_tag_destroy(ahc, scb_data->sg_dmat);
	पूर्ण
		fallthrough;
	हाल 6:
		ahc_dmamap_unload(ahc, scb_data->sense_dmat,
				  scb_data->sense_dmamap);
		fallthrough;
	हाल 5:
		ahc_dmamem_मुक्त(ahc, scb_data->sense_dmat, scb_data->sense,
				scb_data->sense_dmamap);
		ahc_dmamap_destroy(ahc, scb_data->sense_dmat,
				   scb_data->sense_dmamap);
		fallthrough;
	हाल 4:
		ahc_dma_tag_destroy(ahc, scb_data->sense_dmat);
		fallthrough;
	हाल 3:
		ahc_dmamap_unload(ahc, scb_data->hscb_dmat,
				  scb_data->hscb_dmamap);
		fallthrough;
	हाल 2:
		ahc_dmamem_मुक्त(ahc, scb_data->hscb_dmat, scb_data->hscbs,
				scb_data->hscb_dmamap);
		ahc_dmamap_destroy(ahc, scb_data->hscb_dmat,
				   scb_data->hscb_dmamap);
		fallthrough;
	हाल 1:
		ahc_dma_tag_destroy(ahc, scb_data->hscb_dmat);
		अवरोध;
	हाल 0:
		अवरोध;
	पूर्ण
	kमुक्त(scb_data->scbarray);
पूर्ण

अटल व्योम
ahc_alloc_scbs(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा scb_data *scb_data;
	काष्ठा scb *next_scb;
	काष्ठा sg_map_node *sg_map;
	dma_addr_t physaddr;
	काष्ठा ahc_dma_seg *segs;
	पूर्णांक newcount;
	पूर्णांक i;

	scb_data = ahc->scb_data;
	अगर (scb_data->numscbs >= AHC_SCB_MAX_ALLOC)
		/* Can't allocate any more */
		वापस;

	next_scb = &scb_data->scbarray[scb_data->numscbs];

	sg_map = kदो_स्मृति(माप(*sg_map), GFP_ATOMIC);

	अगर (sg_map == शून्य)
		वापस;

	/* Allocate S/G space क्रम the next batch of SCBS */
	अगर (ahc_dmamem_alloc(ahc, scb_data->sg_dmat,
			     (व्योम **)&sg_map->sg_vaddr,
			     BUS_DMA_NOWAIT, &sg_map->sg_dmamap) != 0) अणु
		kमुक्त(sg_map);
		वापस;
	पूर्ण

	SLIST_INSERT_HEAD(&scb_data->sg_maps, sg_map, links);

	ahc_dmamap_load(ahc, scb_data->sg_dmat, sg_map->sg_dmamap,
			sg_map->sg_vaddr, PAGE_SIZE, ahc_dmamap_cb,
			&sg_map->sg_physaddr, /*flags*/0);

	segs = sg_map->sg_vaddr;
	physaddr = sg_map->sg_physaddr;

	newcount = (PAGE_SIZE / (AHC_NSEG * माप(काष्ठा ahc_dma_seg)));
	newcount = min(newcount, (AHC_SCB_MAX_ALLOC - scb_data->numscbs));
	क्रम (i = 0; i < newcount; i++) अणु
		काष्ठा scb_platक्रमm_data *pdata;

		pdata = kदो_स्मृति(माप(*pdata), GFP_ATOMIC);
		अगर (pdata == शून्य)
			अवरोध;
		next_scb->platक्रमm_data = pdata;
		next_scb->sg_map = sg_map;
		next_scb->sg_list = segs;
		/*
		 * The sequencer always starts with the second entry.
		 * The first entry is embedded in the scb.
		 */
		next_scb->sg_list_phys = physaddr + माप(काष्ठा ahc_dma_seg);
		next_scb->ahc_softc = ahc;
		next_scb->flags = SCB_FREE;
		next_scb->hscb = &scb_data->hscbs[scb_data->numscbs];
		next_scb->hscb->tag = ahc->scb_data->numscbs;
		SLIST_INSERT_HEAD(&ahc->scb_data->मुक्त_scbs,
				  next_scb, links.sle);
		segs += AHC_NSEG;
		physaddr += (AHC_NSEG * माप(काष्ठा ahc_dma_seg));
		next_scb++;
		ahc->scb_data->numscbs++;
	पूर्ण
पूर्ण

व्योम
ahc_controller_info(काष्ठा ahc_softc *ahc, अक्षर *buf)
अणु
	पूर्णांक len;

	len = प्र_लिखो(buf, "%s: ", ahc_chip_names[ahc->chip & AHC_CHIPID_MASK]);
	buf += len;
	अगर ((ahc->features & AHC_TWIN) != 0)
		len = प्र_लिखो(buf, "Twin Channel, A SCSI Id=%d, "
			      "B SCSI Id=%d, primary %c, ",
			      ahc->our_id, ahc->our_id_b,
			      (ahc->flags & AHC_PRIMARY_CHANNEL) + 'A');
	अन्यथा अणु
		स्थिर अक्षर *speed;
		स्थिर अक्षर *type;

		speed = "";
		अगर ((ahc->features & AHC_ULTRA) != 0) अणु
			speed = "Ultra ";
		पूर्ण अन्यथा अगर ((ahc->features & AHC_DT) != 0) अणु
			speed = "Ultra160 ";
		पूर्ण अन्यथा अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
			speed = "Ultra2 ";
		पूर्ण
		अगर ((ahc->features & AHC_WIDE) != 0) अणु
			type = "Wide";
		पूर्ण अन्यथा अणु
			type = "Single";
		पूर्ण
		len = प्र_लिखो(buf, "%s%s Channel %c, SCSI Id=%d, ",
			      speed, type, ahc->channel, ahc->our_id);
	पूर्ण
	buf += len;

	अगर ((ahc->flags & AHC_PAGESCBS) != 0)
		प्र_लिखो(buf, "%d/%d SCBs",
			ahc->scb_data->maxhscbs, AHC_MAX_QUEUE);
	अन्यथा
		प्र_लिखो(buf, "%d SCBs", ahc->scb_data->maxhscbs);
पूर्ण

पूर्णांक
ahc_chip_init(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक	 term;
	पूर्णांक	 error;
	u_पूर्णांक	 i;
	u_पूर्णांक	 scsi_conf;
	u_पूर्णांक	 scsiseq_ढाँचा;
	uपूर्णांक32_t physaddr;

	ahc_outb(ahc, SEQ_FLAGS, 0);
	ahc_outb(ahc, SEQ_FLAGS2, 0);

	/* Set the SCSI Id, SXFRCTL0, SXFRCTL1, and SIMODE1, क्रम both channels*/
	अगर (ahc->features & AHC_TWIN) अणु

		/*
		 * Setup Channel B first.
		 */
		ahc_outb(ahc, SBLKCTL, ahc_inb(ahc, SBLKCTL) | SELBUSB);
		term = (ahc->flags & AHC_TERM_ENB_B) != 0 ? STPWEN : 0;
		ahc_outb(ahc, SCSIID, ahc->our_id_b);
		scsi_conf = ahc_inb(ahc, SCSICONF + 1);
		ahc_outb(ahc, SXFRCTL1, (scsi_conf & (ENSPCHK|STIMESEL))
					|term|ahc->selसमय_b|ENSTIMER|ACTNEGEN);
		अगर ((ahc->features & AHC_ULTRA2) != 0)
			ahc_outb(ahc, SIMODE0, ahc_inb(ahc, SIMODE0)|ENIOERR);
		ahc_outb(ahc, SIMODE1, ENSELTIMO|ENSCSIRST|ENSCSIPERR);
		ahc_outb(ahc, SXFRCTL0, DFON|SPIOEN);

		/* Select Channel A */
		ahc_outb(ahc, SBLKCTL, ahc_inb(ahc, SBLKCTL) & ~SELBUSB);
	पूर्ण
	term = (ahc->flags & AHC_TERM_ENB_A) != 0 ? STPWEN : 0;
	अगर ((ahc->features & AHC_ULTRA2) != 0)
		ahc_outb(ahc, SCSIID_ULTRA2, ahc->our_id);
	अन्यथा
		ahc_outb(ahc, SCSIID, ahc->our_id);
	scsi_conf = ahc_inb(ahc, SCSICONF);
	ahc_outb(ahc, SXFRCTL1, (scsi_conf & (ENSPCHK|STIMESEL))
				|term|ahc->selसमय
				|ENSTIMER|ACTNEGEN);
	अगर ((ahc->features & AHC_ULTRA2) != 0)
		ahc_outb(ahc, SIMODE0, ahc_inb(ahc, SIMODE0)|ENIOERR);
	ahc_outb(ahc, SIMODE1, ENSELTIMO|ENSCSIRST|ENSCSIPERR);
	ahc_outb(ahc, SXFRCTL0, DFON|SPIOEN);

	/* There are no untagged SCBs active yet. */
	क्रम (i = 0; i < 16; i++) अणु
		ahc_unbusy_tcl(ahc, BUILD_TCL(i << 4, 0));
		अगर ((ahc->flags & AHC_SCB_BTT) != 0) अणु
			पूर्णांक lun;

			/*
			 * The SCB based BTT allows an entry per
			 * target and lun pair.
			 */
			क्रम (lun = 1; lun < AHC_NUM_LUNS; lun++)
				ahc_unbusy_tcl(ahc, BUILD_TCL(i << 4, lun));
		पूर्ण
	पूर्ण

	/* All of our queues are empty */
	क्रम (i = 0; i < 256; i++)
		ahc->qoutfअगरo[i] = SCB_LIST_शून्य;
	ahc_sync_qoutfअगरo(ahc, BUS_DMASYNC_PREREAD);

	क्रम (i = 0; i < 256; i++)
		ahc->qinfअगरo[i] = SCB_LIST_शून्य;

	अगर ((ahc->features & AHC_MULTI_TID) != 0) अणु
		ahc_outb(ahc, TARGID, 0);
		ahc_outb(ahc, TARGID + 1, 0);
	पूर्ण

	/*
	 * Tell the sequencer where it can find our arrays in memory.
	 */
	physaddr = ahc->scb_data->hscb_busaddr;
	ahc_outb(ahc, HSCB_ADDR, physaddr & 0xFF);
	ahc_outb(ahc, HSCB_ADDR + 1, (physaddr >> 8) & 0xFF);
	ahc_outb(ahc, HSCB_ADDR + 2, (physaddr >> 16) & 0xFF);
	ahc_outb(ahc, HSCB_ADDR + 3, (physaddr >> 24) & 0xFF);

	physaddr = ahc->shared_data_busaddr;
	ahc_outb(ahc, SHARED_DATA_ADDR, physaddr & 0xFF);
	ahc_outb(ahc, SHARED_DATA_ADDR + 1, (physaddr >> 8) & 0xFF);
	ahc_outb(ahc, SHARED_DATA_ADDR + 2, (physaddr >> 16) & 0xFF);
	ahc_outb(ahc, SHARED_DATA_ADDR + 3, (physaddr >> 24) & 0xFF);

	/*
	 * Initialize the group code to command length table.
	 * This overrides the values in TARG_SCSIRATE, so only
	 * setup the table after we have processed that inक्रमmation.
	 */
	ahc_outb(ahc, CMDSIZE_TABLE, 5);
	ahc_outb(ahc, CMDSIZE_TABLE + 1, 9);
	ahc_outb(ahc, CMDSIZE_TABLE + 2, 9);
	ahc_outb(ahc, CMDSIZE_TABLE + 3, 0);
	ahc_outb(ahc, CMDSIZE_TABLE + 4, 15);
	ahc_outb(ahc, CMDSIZE_TABLE + 5, 11);
	ahc_outb(ahc, CMDSIZE_TABLE + 6, 0);
	ahc_outb(ahc, CMDSIZE_TABLE + 7, 0);

	अगर ((ahc->features & AHC_HS_MAILBOX) != 0)
		ahc_outb(ahc, HS_MAILBOX, 0);

	/* Tell the sequencer of our initial queue positions */
	अगर ((ahc->features & AHC_TARGETMODE) != 0) अणु
		ahc->tqinfअगरonext = 1;
		ahc_outb(ahc, KERNEL_TQINPOS, ahc->tqinfअगरonext - 1);
		ahc_outb(ahc, TQINPOS, ahc->tqinfअगरonext);
	पूर्ण
	ahc->qinfअगरonext = 0;
	ahc->qoutfअगरonext = 0;
	अगर ((ahc->features & AHC_QUEUE_REGS) != 0) अणु
		ahc_outb(ahc, QOFF_CTLSTA, SCB_QSIZE_256);
		ahc_outb(ahc, HNSCB_QOFF, ahc->qinfअगरonext);
		ahc_outb(ahc, SNSCB_QOFF, ahc->qinfअगरonext);
		ahc_outb(ahc, SDSCB_QOFF, 0);
	पूर्ण अन्यथा अणु
		ahc_outb(ahc, KERNEL_QINPOS, ahc->qinfअगरonext);
		ahc_outb(ahc, QINPOS, ahc->qinfअगरonext);
		ahc_outb(ahc, QOUTPOS, ahc->qoutfअगरonext);
	पूर्ण

	/* We करोn't have any रुकोing selections */
	ahc_outb(ahc, WAITING_SCBH, SCB_LIST_शून्य);

	/* Our disconnection list is empty too */
	ahc_outb(ahc, DISCONNECTED_SCBH, SCB_LIST_शून्य);

	/* Message out buffer starts empty */
	ahc_outb(ahc, MSG_OUT, NOP);

	/*
	 * Setup the allowed SCSI Sequences based on operational mode.
	 * If we are a target, we'll enable select in operations once
	 * we've had a lun enabled.
	 */
	scsiseq_ढाँचा = ENSELO|ENAUTOATNO|ENAUTOATNP;
	अगर ((ahc->flags & AHC_INITIATORROLE) != 0)
		scsiseq_ढाँचा |= ENRSELI;
	ahc_outb(ahc, SCSISEQ_TEMPLATE, scsiseq_ढाँचा);

	/* Initialize our list of मुक्त SCBs. */
	ahc_build_मुक्त_scb_list(ahc);

	/*
	 * Tell the sequencer which SCB will be the next one it receives.
	 */
	ahc_outb(ahc, NEXT_QUEUED_SCB, ahc->next_queued_scb->hscb->tag);

	/*
	 * Load the Sequencer program and Enable the adapter
	 * in "fast" mode.
	 */
	अगर (bootverbose)
		prपूर्णांकk("%s: Downloading Sequencer Program...",
		       ahc_name(ahc));

	error = ahc_loadseq(ahc);
	अगर (error != 0)
		वापस (error);

	अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
		पूर्णांक रुको;

		/*
		 * Wait क्रम up to 500ms क्रम our transceivers
		 * to settle.  If the adapter करोes not have
		 * a cable attached, the transceivers may
		 * never settle, so करोn't complain अगर we
		 * fail here.
		 */
		क्रम (रुको = 5000;
		     (ahc_inb(ahc, SBLKCTL) & (ENAB40|ENAB20)) == 0 && रुको;
		     रुको--)
			ahc_delay(100);
	पूर्ण
	ahc_restart(ahc);
	वापस (0);
पूर्ण

/*
 * Start the board, पढ़ोy क्रम normal operation
 */
पूर्णांक
ahc_init(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक	 max_targ;
	u_पूर्णांक	 i;
	u_पूर्णांक	 scsi_conf;
	u_पूर्णांक	 ultraenb;
	u_पूर्णांक	 discenable;
	u_पूर्णांक	 tagenable;
	माप_प्रकार	 driver_data_size;

#अगर_घोषित AHC_DEBUG
	अगर ((ahc_debug & AHC_DEBUG_SEQUENCER) != 0)
		ahc->flags |= AHC_SEQUENCER_DEBUG;
#पूर्ण_अगर

#अगर_घोषित AHC_PRINT_SRAM
	prपूर्णांकk("Scratch Ram:");
	क्रम (i = 0x20; i < 0x5f; i++) अणु
		अगर (((i % 8) == 0) && (i != 0)) अणु
			prपूर्णांकk ("\n              ");
		पूर्ण
		prपूर्णांकk (" 0x%x", ahc_inb(ahc, i));
	पूर्ण
	अगर ((ahc->features & AHC_MORE_SRAM) != 0) अणु
		क्रम (i = 0x70; i < 0x7f; i++) अणु
			अगर (((i % 8) == 0) && (i != 0)) अणु
				prपूर्णांकk ("\n              ");
			पूर्ण
			prपूर्णांकk (" 0x%x", ahc_inb(ahc, i));
		पूर्ण
	पूर्ण
	prपूर्णांकk ("\n");
	/*
	 * Reading uninitialized scratch ram may
	 * generate parity errors.
	 */
	ahc_outb(ahc, CLRINT, CLRPARERR);
	ahc_outb(ahc, CLRINT, CLRBRKADRINT);
#पूर्ण_अगर
	max_targ = 15;

	/*
	 * Assume we have a board at this stage and it has been reset.
	 */
	अगर ((ahc->flags & AHC_USEDEFAULTS) != 0)
		ahc->our_id = ahc->our_id_b = 7;

	/*
	 * Default to allowing initiator operations.
	 */
	ahc->flags |= AHC_INITIATORROLE;

	/*
	 * Only allow target mode features अगर this unit has them enabled.
	 */
	अगर ((AHC_TMODE_ENABLE & (0x1 << ahc->unit)) == 0)
		ahc->features &= ~AHC_TARGETMODE;

	ahc->init_level++;

	/*
	 * DMA tag क्रम our command fअगरos and other data in प्रणाली memory
	 * the card's sequencer must be able to access.  For initiator
	 * roles, we need to allocate space क्रम the qinfअगरo and qoutfअगरo.
	 * The qinfअगरo and qoutfअगरo are composed of 256 1 byte elements.
	 * When providing क्रम the target mode role, we must additionally
	 * provide space क्रम the incoming target command fअगरo and an extra
	 * byte to deal with a dma bug in some chip versions.
	 */
	driver_data_size = 2 * 256 * माप(uपूर्णांक8_t);
	अगर ((ahc->features & AHC_TARGETMODE) != 0)
		driver_data_size += AHC_TMODE_CMDS * माप(काष्ठा target_cmd)
				 + /*DMA WideOdd Bug Buffer*/1;
	अगर (ahc_dma_tag_create(ahc, ahc->parent_dmat, /*alignment*/1,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/शून्य, /*filterarg*/शून्य,
			       driver_data_size,
			       /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &ahc->shared_data_dmat) != 0) अणु
		वापस (ENOMEM);
	पूर्ण

	ahc->init_level++;

	/* Allocation of driver data */
	अगर (ahc_dmamem_alloc(ahc, ahc->shared_data_dmat,
			     (व्योम **)&ahc->qoutfअगरo,
			     BUS_DMA_NOWAIT, &ahc->shared_data_dmamap) != 0) अणु
		वापस (ENOMEM);
	पूर्ण

	ahc->init_level++;

	/* And permanently map it in */
	ahc_dmamap_load(ahc, ahc->shared_data_dmat, ahc->shared_data_dmamap,
			ahc->qoutfअगरo, driver_data_size, ahc_dmamap_cb,
			&ahc->shared_data_busaddr, /*flags*/0);

	अगर ((ahc->features & AHC_TARGETMODE) != 0) अणु
		ahc->tarअ_लोmds = (काष्ठा target_cmd *)ahc->qoutfअगरo;
		ahc->qoutfअगरo = (uपूर्णांक8_t *)&ahc->tarअ_लोmds[AHC_TMODE_CMDS];
		ahc->dma_bug_buf = ahc->shared_data_busaddr
				 + driver_data_size - 1;
		/* All target command blocks start out invalid. */
		क्रम (i = 0; i < AHC_TMODE_CMDS; i++)
			ahc->tarअ_लोmds[i].cmd_valid = 0;
		ahc_sync_tqinfअगरo(ahc, BUS_DMASYNC_PREREAD);
		ahc->qoutfअगरo = (uपूर्णांक8_t *)&ahc->tarअ_लोmds[256];
	पूर्ण
	ahc->qinfअगरo = &ahc->qoutfअगरo[256];

	ahc->init_level++;

	/* Allocate SCB data now that buffer_dmat is initialized */
	अगर (ahc->scb_data->maxhscbs == 0)
		अगर (ahc_init_scbdata(ahc) != 0)
			वापस (ENOMEM);

	/*
	 * Allocate a tstate to house inक्रमmation क्रम our
	 * initiator presence on the bus as well as the user
	 * data क्रम any target mode initiator.
	 */
	अगर (ahc_alloc_tstate(ahc, ahc->our_id, 'A') == शून्य) अणु
		prपूर्णांकk("%s: unable to allocate ahc_tmode_tstate.  "
		       "Failing attach\n", ahc_name(ahc));
		वापस (ENOMEM);
	पूर्ण

	अगर ((ahc->features & AHC_TWIN) != 0) अणु
		अगर (ahc_alloc_tstate(ahc, ahc->our_id_b, 'B') == शून्य) अणु
			prपूर्णांकk("%s: unable to allocate ahc_tmode_tstate.  "
			       "Failing attach\n", ahc_name(ahc));
			वापस (ENOMEM);
		पूर्ण
	पूर्ण

	अगर (ahc->scb_data->maxhscbs < AHC_SCB_MAX_ALLOC) अणु
		ahc->flags |= AHC_PAGESCBS;
	पूर्ण अन्यथा अणु
		ahc->flags &= ~AHC_PAGESCBS;
	पूर्ण

#अगर_घोषित AHC_DEBUG
	अगर (ahc_debug & AHC_SHOW_MISC) अणु
		prपूर्णांकk("%s: hardware scb %u bytes; kernel scb %u bytes; "
		       "ahc_dma %u bytes\n",
			ahc_name(ahc),
			(u_पूर्णांक)माप(काष्ठा hardware_scb),
			(u_पूर्णांक)माप(काष्ठा scb),
			(u_पूर्णांक)माप(काष्ठा ahc_dma_seg));
	पूर्ण
#पूर्ण_अगर /* AHC_DEBUG */

	/*
	 * Look at the inक्रमmation that board initialization or
	 * the board bios has left us.
	 */
	अगर (ahc->features & AHC_TWIN) अणु
		scsi_conf = ahc_inb(ahc, SCSICONF + 1);
		अगर ((scsi_conf & RESET_SCSI) != 0
		 && (ahc->flags & AHC_INITIATORROLE) != 0)
			ahc->flags |= AHC_RESET_BUS_B;
	पूर्ण

	scsi_conf = ahc_inb(ahc, SCSICONF);
	अगर ((scsi_conf & RESET_SCSI) != 0
	 && (ahc->flags & AHC_INITIATORROLE) != 0)
		ahc->flags |= AHC_RESET_BUS_A;

	ultraenb = 0;
	tagenable = ALL_TARGETS_MASK;

	/* Grab the disconnection disable table and invert it क्रम our needs */
	अगर ((ahc->flags & AHC_USEDEFAULTS) != 0) अणु
		prपूर्णांकk("%s: Host Adapter Bios disabled.  Using default SCSI "
			"device parameters\n", ahc_name(ahc));
		ahc->flags |= AHC_EXTENDED_TRANS_A|AHC_EXTENDED_TRANS_B|
			      AHC_TERM_ENB_A|AHC_TERM_ENB_B;
		discenable = ALL_TARGETS_MASK;
		अगर ((ahc->features & AHC_ULTRA) != 0)
			ultraenb = ALL_TARGETS_MASK;
	पूर्ण अन्यथा अणु
		discenable = ~((ahc_inb(ahc, DISC_DSB + 1) << 8)
			   | ahc_inb(ahc, DISC_DSB));
		अगर ((ahc->features & (AHC_ULTRA|AHC_ULTRA2)) != 0)
			ultraenb = (ahc_inb(ahc, ULTRA_ENB + 1) << 8)
				      | ahc_inb(ahc, ULTRA_ENB);
	पूर्ण

	अगर ((ahc->features & (AHC_WIDE|AHC_TWIN)) == 0)
		max_targ = 7;

	क्रम (i = 0; i <= max_targ; i++) अणु
		काष्ठा ahc_initiator_tinfo *tinfo;
		काष्ठा ahc_पंचांगode_tstate *tstate;
		u_पूर्णांक our_id;
		u_पूर्णांक target_id;
		अक्षर channel;

		channel = 'A';
		our_id = ahc->our_id;
		target_id = i;
		अगर (i > 7 && (ahc->features & AHC_TWIN) != 0) अणु
			channel = 'B';
			our_id = ahc->our_id_b;
			target_id = i % 8;
		पूर्ण
		tinfo = ahc_fetch_transinfo(ahc, channel, our_id,
					    target_id, &tstate);
		/* Default to async narrow across the board */
		स_रखो(tinfo, 0, माप(*tinfo));
		अगर (ahc->flags & AHC_USEDEFAULTS) अणु
			अगर ((ahc->features & AHC_WIDE) != 0)
				tinfo->user.width = MSG_EXT_WDTR_BUS_16_BIT;

			/*
			 * These will be truncated when we determine the
			 * connection type we have with the target.
			 */
			tinfo->user.period = ahc_syncrates->period;
			tinfo->user.offset = MAX_OFFSET;
		पूर्ण अन्यथा अणु
			u_पूर्णांक scsirate;
			uपूर्णांक16_t mask;

			/* Take the settings leftover in scratch RAM. */
			scsirate = ahc_inb(ahc, TARG_SCSIRATE + i);
			mask = (0x01 << i);
			अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
				u_पूर्णांक offset;
				u_पूर्णांक maxsync;

				अगर ((scsirate & SOFS) == 0x0F) अणु
					/*
					 * Haven't negotiated yet,
					 * so the क्रमmat is dअगरferent.
					 */
					scsirate = (scsirate & SXFR) >> 4
						 | (ultraenb & mask)
						  ? 0x08 : 0x0
						 | (scsirate & WIDEXFER);
					offset = MAX_OFFSET_ULTRA2;
				पूर्ण अन्यथा
					offset = ahc_inb(ahc, TARG_OFFSET + i);
				अगर ((scsirate & ~WIDEXFER) == 0 && offset != 0)
					/* Set to the lowest sync rate, 5MHz */
					scsirate |= 0x1c;
				maxsync = AHC_SYNCRATE_ULTRA2;
				अगर ((ahc->features & AHC_DT) != 0)
					maxsync = AHC_SYNCRATE_DT;
				tinfo->user.period =
				    ahc_find_period(ahc, scsirate, maxsync);
				अगर (offset == 0)
					tinfo->user.period = 0;
				अन्यथा
					tinfo->user.offset = MAX_OFFSET;
				अगर ((scsirate & SXFR_ULTRA2) <= 8/*10MHz*/
				 && (ahc->features & AHC_DT) != 0)
					tinfo->user.ppr_options =
					    MSG_EXT_PPR_DT_REQ;
			पूर्ण अन्यथा अगर ((scsirate & SOFS) != 0) अणु
				अगर ((scsirate & SXFR) == 0x40
				 && (ultraenb & mask) != 0) अणु
					/* Treat 10MHz as a non-ultra speed */
					scsirate &= ~SXFR;
					ultraenb &= ~mask;
				पूर्ण
				tinfo->user.period =
				    ahc_find_period(ahc, scsirate,
						    (ultraenb & mask)
						   ? AHC_SYNCRATE_ULTRA
						   : AHC_SYNCRATE_FAST);
				अगर (tinfo->user.period != 0)
					tinfo->user.offset = MAX_OFFSET;
			पूर्ण
			अगर (tinfo->user.period == 0)
				tinfo->user.offset = 0;
			अगर ((scsirate & WIDEXFER) != 0
			 && (ahc->features & AHC_WIDE) != 0)
				tinfo->user.width = MSG_EXT_WDTR_BUS_16_BIT;
			tinfo->user.protocol_version = 4;
			अगर ((ahc->features & AHC_DT) != 0)
				tinfo->user.transport_version = 3;
			अन्यथा
				tinfo->user.transport_version = 2;
			tinfo->goal.protocol_version = 2;
			tinfo->goal.transport_version = 2;
			tinfo->curr.protocol_version = 2;
			tinfo->curr.transport_version = 2;
		पूर्ण
		tstate->ultraenb = 0;
	पूर्ण
	ahc->user_discenable = discenable;
	ahc->user_tagenable = tagenable;

	वापस (ahc->bus_chip_init(ahc));
पूर्ण

व्योम
ahc_पूर्णांकr_enable(काष्ठा ahc_softc *ahc, पूर्णांक enable)
अणु
	u_पूर्णांक hcntrl;

	hcntrl = ahc_inb(ahc, HCNTRL);
	hcntrl &= ~INTEN;
	ahc->छोड़ो &= ~INTEN;
	ahc->unछोड़ो &= ~INTEN;
	अगर (enable) अणु
		hcntrl |= INTEN;
		ahc->छोड़ो |= INTEN;
		ahc->unछोड़ो |= INTEN;
	पूर्ण
	ahc_outb(ahc, HCNTRL, hcntrl);
पूर्ण

/*
 * Ensure that the card is छोड़ोd in a location
 * outside of all critical sections and that all
 * pending work is completed prior to वापसing.
 * This routine should only be called from outside
 * an पूर्णांकerrupt context.
 */
व्योम
ahc_छोड़ो_and_flushwork(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक पूर्णांकstat;
	पूर्णांक maxloops;
	पूर्णांक छोड़ोd;

	maxloops = 1000;
	ahc->flags |= AHC_ALL_INTERRUPTS;
	छोड़ोd = FALSE;
	करो अणु
		अगर (छोड़ोd) अणु
			ahc_unछोड़ो(ahc);
			/*
			 * Give the sequencer some समय to service
			 * any active selections.
			 */
			ahc_delay(500);
		पूर्ण
		ahc_पूर्णांकr(ahc);
		ahc_छोड़ो(ahc);
		छोड़ोd = TRUE;
		ahc_outb(ahc, SCSISEQ, ahc_inb(ahc, SCSISEQ) & ~ENSELO);
		पूर्णांकstat = ahc_inb(ahc, INTSTAT);
		अगर ((पूर्णांकstat & INT_PEND) == 0) अणु
			ahc_clear_critical_section(ahc);
			पूर्णांकstat = ahc_inb(ahc, INTSTAT);
		पूर्ण
	पूर्ण जबतक (--maxloops
	      && (पूर्णांकstat != 0xFF || (ahc->features & AHC_REMOVABLE) == 0)
	      && ((पूर्णांकstat & INT_PEND) != 0
	       || (ahc_inb(ahc, SSTAT0) & (SELDO|SELINGO)) != 0));
	अगर (maxloops == 0) अणु
		prपूर्णांकk("Infinite interrupt loop, INTSTAT = %x",
		       ahc_inb(ahc, INTSTAT));
	पूर्ण
	ahc_platक्रमm_flushwork(ahc);
	ahc->flags &= ~AHC_ALL_INTERRUPTS;
पूर्ण

पूर्णांक __maybe_unused
ahc_suspend(काष्ठा ahc_softc *ahc)
अणु

	ahc_छोड़ो_and_flushwork(ahc);

	अगर (LIST_FIRST(&ahc->pending_scbs) != शून्य) अणु
		ahc_unछोड़ो(ahc);
		वापस (EBUSY);
	पूर्ण

#अगर_घोषित AHC_TARGET_MODE
	/*
	 * XXX What about ATIOs that have not yet been serviced?
	 * Perhaps we should just refuse to be suspended अगर we
	 * are acting in a target role.
	 */
	अगर (ahc->pending_device != शून्य) अणु
		ahc_unछोड़ो(ahc);
		वापस (EBUSY);
	पूर्ण
#पूर्ण_अगर
	ahc_shutकरोwn(ahc);
	वापस (0);
पूर्ण

पूर्णांक __maybe_unused
ahc_resume(काष्ठा ahc_softc *ahc)
अणु

	ahc_reset(ahc, /*reinit*/TRUE);
	ahc_पूर्णांकr_enable(ahc, TRUE);
	ahc_restart(ahc);
	वापस (0);
पूर्ण
/************************** Busy Target Table *********************************/
/*
 * Return the untagged transaction id क्रम a given target/channel lun.
 * Optionally, clear the entry.
 */
अटल u_पूर्णांक
ahc_index_busy_tcl(काष्ठा ahc_softc *ahc, u_पूर्णांक tcl)
अणु
	u_पूर्णांक scbid;
	u_पूर्णांक target_offset;

	अगर ((ahc->flags & AHC_SCB_BTT) != 0) अणु
		u_पूर्णांक saved_scbptr;

		saved_scbptr = ahc_inb(ahc, SCBPTR);
		ahc_outb(ahc, SCBPTR, TCL_LUN(tcl));
		scbid = ahc_inb(ahc, SCB_64_BTT + TCL_TARGET_OFFSET(tcl));
		ahc_outb(ahc, SCBPTR, saved_scbptr);
	पूर्ण अन्यथा अणु
		target_offset = TCL_TARGET_OFFSET(tcl);
		scbid = ahc_inb(ahc, BUSY_TARGETS + target_offset);
	पूर्ण

	वापस (scbid);
पूर्ण

अटल व्योम
ahc_unbusy_tcl(काष्ठा ahc_softc *ahc, u_पूर्णांक tcl)
अणु
	u_पूर्णांक target_offset;

	अगर ((ahc->flags & AHC_SCB_BTT) != 0) अणु
		u_पूर्णांक saved_scbptr;

		saved_scbptr = ahc_inb(ahc, SCBPTR);
		ahc_outb(ahc, SCBPTR, TCL_LUN(tcl));
		ahc_outb(ahc, SCB_64_BTT+TCL_TARGET_OFFSET(tcl), SCB_LIST_शून्य);
		ahc_outb(ahc, SCBPTR, saved_scbptr);
	पूर्ण अन्यथा अणु
		target_offset = TCL_TARGET_OFFSET(tcl);
		ahc_outb(ahc, BUSY_TARGETS + target_offset, SCB_LIST_शून्य);
	पूर्ण
पूर्ण

अटल व्योम
ahc_busy_tcl(काष्ठा ahc_softc *ahc, u_पूर्णांक tcl, u_पूर्णांक scbid)
अणु
	u_पूर्णांक target_offset;

	अगर ((ahc->flags & AHC_SCB_BTT) != 0) अणु
		u_पूर्णांक saved_scbptr;

		saved_scbptr = ahc_inb(ahc, SCBPTR);
		ahc_outb(ahc, SCBPTR, TCL_LUN(tcl));
		ahc_outb(ahc, SCB_64_BTT + TCL_TARGET_OFFSET(tcl), scbid);
		ahc_outb(ahc, SCBPTR, saved_scbptr);
	पूर्ण अन्यथा अणु
		target_offset = TCL_TARGET_OFFSET(tcl);
		ahc_outb(ahc, BUSY_TARGETS + target_offset, scbid);
	पूर्ण
पूर्ण

/************************** SCB and SCB queue management **********************/
पूर्णांक
ahc_match_scb(काष्ठा ahc_softc *ahc, काष्ठा scb *scb, पूर्णांक target,
	      अक्षर channel, पूर्णांक lun, u_पूर्णांक tag, role_t role)
अणु
	पूर्णांक targ = SCB_GET_TARGET(ahc, scb);
	अक्षर chan = SCB_GET_CHANNEL(ahc, scb);
	पूर्णांक slun = SCB_GET_LUN(scb);
	पूर्णांक match;

	match = ((chan == channel) || (channel == ALL_CHANNELS));
	अगर (match != 0)
		match = ((targ == target) || (target == CAM_TARGET_WILDCARD));
	अगर (match != 0)
		match = ((lun == slun) || (lun == CAM_LUN_WILDCARD));
	अगर (match != 0) अणु
#अगर_घोषित AHC_TARGET_MODE
		पूर्णांक group;

		group = XPT_FC_GROUP(scb->io_ctx->ccb_h.func_code);
		अगर (role == ROLE_INITIATOR) अणु
			match = (group != XPT_FC_GROUP_TMODE)
			      && ((tag == scb->hscb->tag)
			       || (tag == SCB_LIST_शून्य));
		पूर्ण अन्यथा अगर (role == ROLE_TARGET) अणु
			match = (group == XPT_FC_GROUP_TMODE)
			      && ((tag == scb->io_ctx->csio.tag_id)
			       || (tag == SCB_LIST_शून्य));
		पूर्ण
#अन्यथा /* !AHC_TARGET_MODE */
		match = ((tag == scb->hscb->tag) || (tag == SCB_LIST_शून्य));
#पूर्ण_अगर /* AHC_TARGET_MODE */
	पूर्ण

	वापस match;
पूर्ण

अटल व्योम
ahc_मुक्तze_devq(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	पूर्णांक	target;
	अक्षर	channel;
	पूर्णांक	lun;

	target = SCB_GET_TARGET(ahc, scb);
	lun = SCB_GET_LUN(scb);
	channel = SCB_GET_CHANNEL(ahc, scb);

	ahc_search_qinfअगरo(ahc, target, channel, lun,
			   /*tag*/SCB_LIST_शून्य, ROLE_UNKNOWN,
			   CAM_REQUEUE_REQ, SEARCH_COMPLETE);

	ahc_platक्रमm_मुक्तze_devq(ahc, scb);
पूर्ण

व्योम
ahc_qinfअगरo_requeue_tail(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	काष्ठा scb *prev_scb;

	prev_scb = शून्य;
	अगर (ahc_qinfअगरo_count(ahc) != 0) अणु
		u_पूर्णांक prev_tag;
		uपूर्णांक8_t prev_pos;

		prev_pos = ahc->qinfअगरonext - 1;
		prev_tag = ahc->qinfअगरo[prev_pos];
		prev_scb = ahc_lookup_scb(ahc, prev_tag);
	पूर्ण
	ahc_qinfअगरo_requeue(ahc, prev_scb, scb);
	अगर ((ahc->features & AHC_QUEUE_REGS) != 0) अणु
		ahc_outb(ahc, HNSCB_QOFF, ahc->qinfअगरonext);
	पूर्ण अन्यथा अणु
		ahc_outb(ahc, KERNEL_QINPOS, ahc->qinfअगरonext);
	पूर्ण
पूर्ण

अटल व्योम
ahc_qinfअगरo_requeue(काष्ठा ahc_softc *ahc, काष्ठा scb *prev_scb,
		    काष्ठा scb *scb)
अणु
	अगर (prev_scb == शून्य) अणु
		ahc_outb(ahc, NEXT_QUEUED_SCB, scb->hscb->tag);
	पूर्ण अन्यथा अणु
		prev_scb->hscb->next = scb->hscb->tag;
		ahc_sync_scb(ahc, prev_scb,
			     BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);
	पूर्ण
	ahc->qinfअगरo[ahc->qinfअगरonext++] = scb->hscb->tag;
	scb->hscb->next = ahc->next_queued_scb->hscb->tag;
	ahc_sync_scb(ahc, scb, BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);
पूर्ण

अटल पूर्णांक
ahc_qinfअगरo_count(काष्ठा ahc_softc *ahc)
अणु
	uपूर्णांक8_t qinpos;
	uपूर्णांक8_t dअगरf;

	अगर ((ahc->features & AHC_QUEUE_REGS) != 0) अणु
		qinpos = ahc_inb(ahc, SNSCB_QOFF);
		ahc_outb(ahc, SNSCB_QOFF, qinpos);
	पूर्ण अन्यथा
		qinpos = ahc_inb(ahc, QINPOS);
	dअगरf = ahc->qinfअगरonext - qinpos;
	वापस (dअगरf);
पूर्ण

पूर्णांक
ahc_search_qinfअगरo(काष्ठा ahc_softc *ahc, पूर्णांक target, अक्षर channel,
		   पूर्णांक lun, u_पूर्णांक tag, role_t role, uपूर्णांक32_t status,
		   ahc_search_action action)
अणु
	काष्ठा	scb *scb;
	काष्ठा	scb *prev_scb;
	uपूर्णांक8_t qinstart;
	uपूर्णांक8_t qinpos;
	uपूर्णांक8_t qपूर्णांकail;
	uपूर्णांक8_t next;
	uपूर्णांक8_t prev;
	uपूर्णांक8_t curscbptr;
	पूर्णांक	found;
	पूर्णांक	have_qregs;

	qपूर्णांकail = ahc->qinfअगरonext;
	have_qregs = (ahc->features & AHC_QUEUE_REGS) != 0;
	अगर (have_qregs) अणु
		qinstart = ahc_inb(ahc, SNSCB_QOFF);
		ahc_outb(ahc, SNSCB_QOFF, qinstart);
	पूर्ण अन्यथा
		qinstart = ahc_inb(ahc, QINPOS);
	qinpos = qinstart;
	found = 0;
	prev_scb = शून्य;

	अगर (action == SEARCH_COMPLETE) अणु
		/*
		 * Don't attempt to run any queued untagged transactions
		 * until we are करोne with the पात process.
		 */
		ahc_मुक्तze_untagged_queues(ahc);
	पूर्ण

	/*
	 * Start with an empty queue.  Entries that are not chosen
	 * क्रम removal will be re-added to the queue as we go.
	 */
	ahc->qinfअगरonext = qinpos;
	ahc_outb(ahc, NEXT_QUEUED_SCB, ahc->next_queued_scb->hscb->tag);

	जबतक (qinpos != qपूर्णांकail) अणु
		scb = ahc_lookup_scb(ahc, ahc->qinfअगरo[qinpos]);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("qinpos = %d, SCB index = %d\n",
				qinpos, ahc->qinfअगरo[qinpos]);
			panic("Loop 1\n");
		पूर्ण

		अगर (ahc_match_scb(ahc, scb, target, channel, lun, tag, role)) अणु
			/*
			 * We found an scb that needs to be acted on.
			 */
			found++;
			चयन (action) अणु
			हाल SEARCH_COMPLETE:
			अणु
				cam_status ostat;
				cam_status cstat;

				ostat = ahc_get_transaction_status(scb);
				अगर (ostat == CAM_REQ_INPROG)
					ahc_set_transaction_status(scb, status);
				cstat = ahc_get_transaction_status(scb);
				अगर (cstat != CAM_REQ_CMP)
					ahc_मुक्तze_scb(scb);
				अगर ((scb->flags & SCB_ACTIVE) == 0)
					prपूर्णांकk("Inactive SCB in qinfifo\n");
				ahc_करोne(ahc, scb);
			पूर्ण
				fallthrough;
			हाल SEARCH_REMOVE:
				अवरोध;
			हाल SEARCH_COUNT:
				ahc_qinfअगरo_requeue(ahc, prev_scb, scb);
				prev_scb = scb;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			ahc_qinfअगरo_requeue(ahc, prev_scb, scb);
			prev_scb = scb;
		पूर्ण
		qinpos++;
	पूर्ण

	अगर ((ahc->features & AHC_QUEUE_REGS) != 0) अणु
		ahc_outb(ahc, HNSCB_QOFF, ahc->qinfअगरonext);
	पूर्ण अन्यथा अणु
		ahc_outb(ahc, KERNEL_QINPOS, ahc->qinfअगरonext);
	पूर्ण

	अगर (action != SEARCH_COUNT
	 && (found != 0)
	 && (qinstart != ahc->qinfअगरonext)) अणु
		/*
		 * The sequencer may be in the process of dमुख्यg
		 * करोwn the SCB at the beginning of the queue.
		 * This could be problematic अगर either the first,
		 * or the second SCB is हटाओd from the queue
		 * (the first SCB includes a poपूर्णांकer to the "next"
		 * SCB to dma). If we have हटाओd any entries, swap
		 * the first element in the queue with the next HSCB
		 * so the sequencer will notice that NEXT_QUEUED_SCB
		 * has changed during its dma attempt and will retry
		 * the DMA.
		 */
		scb = ahc_lookup_scb(ahc, ahc->qinfअगरo[qinstart]);

		अगर (scb == शून्य) अणु
			prपूर्णांकk("found = %d, qinstart = %d, qinfifionext = %d\n",
				found, qinstart, ahc->qinfअगरonext);
			panic("First/Second Qinfifo fixup\n");
		पूर्ण
		/*
		 * ahc_swap_with_next_hscb क्रमces our next poपूर्णांकer to
		 * poपूर्णांक to the reserved SCB क्रम future commands.  Save
		 * and restore our original next poपूर्णांकer to मुख्यtain
		 * queue पूर्णांकegrity.
		 */
		next = scb->hscb->next;
		ahc->scb_data->scbindex[scb->hscb->tag] = शून्य;
		ahc_swap_with_next_hscb(ahc, scb);
		scb->hscb->next = next;
		ahc->qinfअगरo[qinstart] = scb->hscb->tag;

		/* Tell the card about the new head of the qinfअगरo. */
		ahc_outb(ahc, NEXT_QUEUED_SCB, scb->hscb->tag);

		/* Fixup the tail "next" poपूर्णांकer. */
		qपूर्णांकail = ahc->qinfअगरonext - 1;
		scb = ahc_lookup_scb(ahc, ahc->qinfअगरo[qपूर्णांकail]);
		scb->hscb->next = ahc->next_queued_scb->hscb->tag;
	पूर्ण

	/*
	 * Search रुकोing क्रम selection list.
	 */
	curscbptr = ahc_inb(ahc, SCBPTR);
	next = ahc_inb(ahc, WAITING_SCBH);  /* Start at head of list. */
	prev = SCB_LIST_शून्य;

	जबतक (next != SCB_LIST_शून्य) अणु
		uपूर्णांक8_t scb_index;

		ahc_outb(ahc, SCBPTR, next);
		scb_index = ahc_inb(ahc, SCB_TAG);
		अगर (scb_index >= ahc->scb_data->numscbs) अणु
			prपूर्णांकk("Waiting List inconsistency. "
			       "SCB index == %d, yet numscbs == %d.",
			       scb_index, ahc->scb_data->numscbs);
			ahc_dump_card_state(ahc);
			panic("for safety");
		पूर्ण
		scb = ahc_lookup_scb(ahc, scb_index);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("scb_index = %d, next = %d\n",
				scb_index, next);
			panic("Waiting List traversal\n");
		पूर्ण
		अगर (ahc_match_scb(ahc, scb, target, channel,
				  lun, SCB_LIST_शून्य, role)) अणु
			/*
			 * We found an scb that needs to be acted on.
			 */
			found++;
			चयन (action) अणु
			हाल SEARCH_COMPLETE:
			अणु
				cam_status ostat;
				cam_status cstat;

				ostat = ahc_get_transaction_status(scb);
				अगर (ostat == CAM_REQ_INPROG)
					ahc_set_transaction_status(scb,
								   status);
				cstat = ahc_get_transaction_status(scb);
				अगर (cstat != CAM_REQ_CMP)
					ahc_मुक्तze_scb(scb);
				अगर ((scb->flags & SCB_ACTIVE) == 0)
					prपूर्णांकk("Inactive SCB in Waiting List\n");
				ahc_करोne(ahc, scb);
			पूर्ण
				fallthrough;
			हाल SEARCH_REMOVE:
				next = ahc_rem_wscb(ahc, next, prev);
				अवरोध;
			हाल SEARCH_COUNT:
				prev = next;
				next = ahc_inb(ahc, SCB_NEXT);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			prev = next;
			next = ahc_inb(ahc, SCB_NEXT);
		पूर्ण
	पूर्ण
	ahc_outb(ahc, SCBPTR, curscbptr);

	found += ahc_search_untagged_queues(ahc, /*ahc_io_ctx_t*/शून्य, target,
					    channel, lun, status, action);

	अगर (action == SEARCH_COMPLETE)
		ahc_release_untagged_queues(ahc);
	वापस (found);
पूर्ण

पूर्णांक
ahc_search_untagged_queues(काष्ठा ahc_softc *ahc, ahc_io_ctx_t ctx,
			   पूर्णांक target, अक्षर channel, पूर्णांक lun, uपूर्णांक32_t status,
			   ahc_search_action action)
अणु
	काष्ठा	scb *scb;
	पूर्णांक	maxtarget;
	पूर्णांक	found;
	पूर्णांक	i;

	अगर (action == SEARCH_COMPLETE) अणु
		/*
		 * Don't attempt to run any queued untagged transactions
		 * until we are करोne with the पात process.
		 */
		ahc_मुक्तze_untagged_queues(ahc);
	पूर्ण

	found = 0;
	i = 0;
	अगर ((ahc->flags & AHC_SCB_BTT) == 0) अणु

		maxtarget = 16;
		अगर (target != CAM_TARGET_WILDCARD) अणु

			i = target;
			अगर (channel == 'B')
				i += 8;
			maxtarget = i + 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		maxtarget = 0;
	पूर्ण

	क्रम (; i < maxtarget; i++) अणु
		काष्ठा scb_tailq *untagged_q;
		काष्ठा scb *next_scb;

		untagged_q = &(ahc->untagged_queues[i]);
		next_scb = TAILQ_FIRST(untagged_q);
		जबतक (next_scb != शून्य) अणु

			scb = next_scb;
			next_scb = TAILQ_NEXT(scb, links.tqe);

			/*
			 * The head of the list may be the currently
			 * active untagged command क्रम a device.
			 * We're only searching क्रम commands that
			 * have not been started.  A transaction
			 * marked active but still in the qinfअगरo
			 * is हटाओd by the qinfअगरo scanning code
			 * above.
			 */
			अगर ((scb->flags & SCB_ACTIVE) != 0)
				जारी;

			अगर (ahc_match_scb(ahc, scb, target, channel, lun,
					  SCB_LIST_शून्य, ROLE_INITIATOR) == 0
			 || (ctx != शून्य && ctx != scb->io_ctx))
				जारी;

			/*
			 * We found an scb that needs to be acted on.
			 */
			found++;
			चयन (action) अणु
			हाल SEARCH_COMPLETE:
			अणु
				cam_status ostat;
				cam_status cstat;

				ostat = ahc_get_transaction_status(scb);
				अगर (ostat == CAM_REQ_INPROG)
					ahc_set_transaction_status(scb, status);
				cstat = ahc_get_transaction_status(scb);
				अगर (cstat != CAM_REQ_CMP)
					ahc_मुक्तze_scb(scb);
				अगर ((scb->flags & SCB_ACTIVE) == 0)
					prपूर्णांकk("Inactive SCB in untaggedQ\n");
				ahc_करोne(ahc, scb);
				अवरोध;
			पूर्ण
			हाल SEARCH_REMOVE:
				scb->flags &= ~SCB_UNTAGGEDQ;
				TAILQ_REMOVE(untagged_q, scb, links.tqe);
				अवरोध;
			हाल SEARCH_COUNT:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (action == SEARCH_COMPLETE)
		ahc_release_untagged_queues(ahc);
	वापस (found);
पूर्ण

पूर्णांक
ahc_search_disc_list(काष्ठा ahc_softc *ahc, पूर्णांक target, अक्षर channel,
		     पूर्णांक lun, u_पूर्णांक tag, पूर्णांक stop_on_first, पूर्णांक हटाओ,
		     पूर्णांक save_state)
अणु
	काष्ठा	scb *scbp;
	u_पूर्णांक	next;
	u_पूर्णांक	prev;
	u_पूर्णांक	count;
	u_पूर्णांक	active_scb;

	count = 0;
	next = ahc_inb(ahc, DISCONNECTED_SCBH);
	prev = SCB_LIST_शून्य;

	अगर (save_state) अणु
		/* restore this when we're करोne */
		active_scb = ahc_inb(ahc, SCBPTR);
	पूर्ण अन्यथा
		/* Silence compiler */
		active_scb = SCB_LIST_शून्य;

	जबतक (next != SCB_LIST_शून्य) अणु
		u_पूर्णांक scb_index;

		ahc_outb(ahc, SCBPTR, next);
		scb_index = ahc_inb(ahc, SCB_TAG);
		अगर (scb_index >= ahc->scb_data->numscbs) अणु
			prपूर्णांकk("Disconnected List inconsistency. "
			       "SCB index == %d, yet numscbs == %d.",
			       scb_index, ahc->scb_data->numscbs);
			ahc_dump_card_state(ahc);
			panic("for safety");
		पूर्ण

		अगर (next == prev) अणु
			panic("Disconnected List Loop. "
			      "cur SCBPTR == %x, prev SCBPTR == %x.",
			      next, prev);
		पूर्ण
		scbp = ahc_lookup_scb(ahc, scb_index);
		अगर (ahc_match_scb(ahc, scbp, target, channel, lun,
				  tag, ROLE_INITIATOR)) अणु
			count++;
			अगर (हटाओ) अणु
				next =
				    ahc_rem_scb_from_disc_list(ahc, prev, next);
			पूर्ण अन्यथा अणु
				prev = next;
				next = ahc_inb(ahc, SCB_NEXT);
			पूर्ण
			अगर (stop_on_first)
				अवरोध;
		पूर्ण अन्यथा अणु
			prev = next;
			next = ahc_inb(ahc, SCB_NEXT);
		पूर्ण
	पूर्ण
	अगर (save_state)
		ahc_outb(ahc, SCBPTR, active_scb);
	वापस (count);
पूर्ण

/*
 * Remove an SCB from the on chip list of disconnected transactions.
 * This is empty/unused अगर we are not perक्रमming SCB paging.
 */
अटल u_पूर्णांक
ahc_rem_scb_from_disc_list(काष्ठा ahc_softc *ahc, u_पूर्णांक prev, u_पूर्णांक scbptr)
अणु
	u_पूर्णांक next;

	ahc_outb(ahc, SCBPTR, scbptr);
	next = ahc_inb(ahc, SCB_NEXT);

	ahc_outb(ahc, SCB_CONTROL, 0);

	ahc_add_curscb_to_मुक्त_list(ahc);

	अगर (prev != SCB_LIST_शून्य) अणु
		ahc_outb(ahc, SCBPTR, prev);
		ahc_outb(ahc, SCB_NEXT, next);
	पूर्ण अन्यथा
		ahc_outb(ahc, DISCONNECTED_SCBH, next);

	वापस (next);
पूर्ण

/*
 * Add the SCB as selected by SCBPTR onto the on chip list of
 * मुक्त hardware SCBs.  This list is empty/unused अगर we are not
 * perक्रमming SCB paging.
 */
अटल व्योम
ahc_add_curscb_to_मुक्त_list(काष्ठा ahc_softc *ahc)
अणु
	/*
	 * Invalidate the tag so that our पात
	 * routines करोn't think it's active.
	 */
	ahc_outb(ahc, SCB_TAG, SCB_LIST_शून्य);

	अगर ((ahc->flags & AHC_PAGESCBS) != 0) अणु
		ahc_outb(ahc, SCB_NEXT, ahc_inb(ahc, FREE_SCBH));
		ahc_outb(ahc, FREE_SCBH, ahc_inb(ahc, SCBPTR));
	पूर्ण
पूर्ण

/*
 * Manipulate the रुकोing क्रम selection list and वापस the
 * scb that follows the one that we हटाओ.
 */
अटल u_पूर्णांक
ahc_rem_wscb(काष्ठा ahc_softc *ahc, u_पूर्णांक scbpos, u_पूर्णांक prev)
अणु
	u_पूर्णांक curscb, next;

	/*
	 * Select the SCB we want to पात and
	 * pull the next poपूर्णांकer out of it.
	 */
	curscb = ahc_inb(ahc, SCBPTR);
	ahc_outb(ahc, SCBPTR, scbpos);
	next = ahc_inb(ahc, SCB_NEXT);

	/* Clear the necessary fields */
	ahc_outb(ahc, SCB_CONTROL, 0);

	ahc_add_curscb_to_मुक्त_list(ahc);

	/* update the रुकोing list */
	अगर (prev == SCB_LIST_शून्य) अणु
		/* First in the list */
		ahc_outb(ahc, WAITING_SCBH, next);

		/*
		 * Ensure we aren't attempting to perक्रमm
		 * selection क्रम this entry.
		 */
		ahc_outb(ahc, SCSISEQ, (ahc_inb(ahc, SCSISEQ) & ~ENSELO));
	पूर्ण अन्यथा अणु
		/*
		 * Select the scb that poपूर्णांकed to us
		 * and update its next poपूर्णांकer.
		 */
		ahc_outb(ahc, SCBPTR, prev);
		ahc_outb(ahc, SCB_NEXT, next);
	पूर्ण

	/*
	 * Poपूर्णांक us back at the original scb position.
	 */
	ahc_outb(ahc, SCBPTR, curscb);
	वापस next;
पूर्ण

/******************************** Error Handling ******************************/
/*
 * Abort all SCBs that match the given description (target/channel/lun/tag),
 * setting their status to the passed in status अगर the status has not alपढ़ोy
 * been modअगरied from CAM_REQ_INPROG.  This routine assumes that the sequencer
 * is छोड़ोd beक्रमe it is called.
 */
अटल पूर्णांक
ahc_पात_scbs(काष्ठा ahc_softc *ahc, पूर्णांक target, अक्षर channel,
	       पूर्णांक lun, u_पूर्णांक tag, role_t role, uपूर्णांक32_t status)
अणु
	काष्ठा	scb *scbp;
	काष्ठा	scb *scbp_next;
	u_पूर्णांक	active_scb;
	पूर्णांक	i, j;
	पूर्णांक	maxtarget;
	पूर्णांक	minlun;
	पूर्णांक	maxlun;

	पूर्णांक	found;

	/*
	 * Don't attempt to run any queued untagged transactions
	 * until we are करोne with the पात process.
	 */
	ahc_मुक्तze_untagged_queues(ahc);

	/* restore this when we're करोne */
	active_scb = ahc_inb(ahc, SCBPTR);

	found = ahc_search_qinfअगरo(ahc, target, channel, lun, SCB_LIST_शून्य,
				   role, CAM_REQUEUE_REQ, SEARCH_COMPLETE);

	/*
	 * Clean out the busy target table क्रम any untagged commands.
	 */
	i = 0;
	maxtarget = 16;
	अगर (target != CAM_TARGET_WILDCARD) अणु
		i = target;
		अगर (channel == 'B')
			i += 8;
		maxtarget = i + 1;
	पूर्ण

	अगर (lun == CAM_LUN_WILDCARD) अणु

		/*
		 * Unless we are using an SCB based
		 * busy tarमाला_लो table, there is only
		 * one table entry क्रम all luns of
		 * a target.
		 */
		minlun = 0;
		maxlun = 1;
		अगर ((ahc->flags & AHC_SCB_BTT) != 0)
			maxlun = AHC_NUM_LUNS;
	पूर्ण अन्यथा अणु
		minlun = lun;
		maxlun = lun + 1;
	पूर्ण

	अगर (role != ROLE_TARGET) अणु
		क्रम (;i < maxtarget; i++) अणु
			क्रम (j = minlun;j < maxlun; j++) अणु
				u_पूर्णांक scbid;
				u_पूर्णांक tcl;

				tcl = BUILD_TCL(i << 4, j);
				scbid = ahc_index_busy_tcl(ahc, tcl);
				scbp = ahc_lookup_scb(ahc, scbid);
				अगर (scbp == शून्य
				 || ahc_match_scb(ahc, scbp, target, channel,
						  lun, tag, role) == 0)
					जारी;
				ahc_unbusy_tcl(ahc, BUILD_TCL(i << 4, j));
			पूर्ण
		पूर्ण

		/*
		 * Go through the disconnected list and हटाओ any entries we
		 * have queued क्रम completion, 0'ing their control byte too.
		 * We save the active SCB and restore it ourselves, so there
		 * is no reason क्रम this search to restore it too.
		 */
		ahc_search_disc_list(ahc, target, channel, lun, tag,
				     /*stop_on_first*/FALSE, /*हटाओ*/TRUE,
				     /*save_state*/FALSE);
	पूर्ण

	/*
	 * Go through the hardware SCB array looking क्रम commands that
	 * were active but not on any list.  In some हालs, these remnants
	 * might not still have mappings in the scbindex array (e.g. unexpected
	 * bus मुक्त with the same scb queued क्रम an पात).  Don't hold this
	 * against them.
	 */
	क्रम (i = 0; i < ahc->scb_data->maxhscbs; i++) अणु
		u_पूर्णांक scbid;

		ahc_outb(ahc, SCBPTR, i);
		scbid = ahc_inb(ahc, SCB_TAG);
		scbp = ahc_lookup_scb(ahc, scbid);
		अगर ((scbp == शून्य && scbid != SCB_LIST_शून्य)
		 || (scbp != शून्य
		  && ahc_match_scb(ahc, scbp, target, channel, lun, tag, role)))
			ahc_add_curscb_to_मुक्त_list(ahc);
	पूर्ण

	/*
	 * Go through the pending CCB list and look क्रम
	 * commands क्रम this target that are still active.
	 * These are other tagged commands that were
	 * disconnected when the reset occurred.
	 */
	scbp_next = LIST_FIRST(&ahc->pending_scbs);
	जबतक (scbp_next != शून्य) अणु
		scbp = scbp_next;
		scbp_next = LIST_NEXT(scbp, pending_links);
		अगर (ahc_match_scb(ahc, scbp, target, channel, lun, tag, role)) अणु
			cam_status ostat;

			ostat = ahc_get_transaction_status(scbp);
			अगर (ostat == CAM_REQ_INPROG)
				ahc_set_transaction_status(scbp, status);
			अगर (ahc_get_transaction_status(scbp) != CAM_REQ_CMP)
				ahc_मुक्तze_scb(scbp);
			अगर ((scbp->flags & SCB_ACTIVE) == 0)
				prपूर्णांकk("Inactive SCB on pending list\n");
			ahc_करोne(ahc, scbp);
			found++;
		पूर्ण
	पूर्ण
	ahc_outb(ahc, SCBPTR, active_scb);
	ahc_platक्रमm_पात_scbs(ahc, target, channel, lun, tag, role, status);
	ahc_release_untagged_queues(ahc);
	वापस found;
पूर्ण

अटल व्योम
ahc_reset_current_bus(काष्ठा ahc_softc *ahc)
अणु
	uपूर्णांक8_t scsiseq;

	ahc_outb(ahc, SIMODE1, ahc_inb(ahc, SIMODE1) & ~ENSCSIRST);
	scsiseq = ahc_inb(ahc, SCSISEQ);
	ahc_outb(ahc, SCSISEQ, scsiseq | SCSIRSTO);
	ahc_flush_device_ग_लिखोs(ahc);
	ahc_delay(AHC_BUSRESET_DELAY);
	/* Turn off the bus reset */
	ahc_outb(ahc, SCSISEQ, scsiseq & ~SCSIRSTO);

	ahc_clear_पूर्णांकstat(ahc);

	/* Re-enable reset पूर्णांकerrupts */
	ahc_outb(ahc, SIMODE1, ahc_inb(ahc, SIMODE1) | ENSCSIRST);
पूर्ण

पूर्णांक
ahc_reset_channel(काष्ठा ahc_softc *ahc, अक्षर channel, पूर्णांक initiate_reset)
अणु
	काष्ठा	ahc_devinfo devinfo;
	u_पूर्णांक	initiator, target, max_scsiid;
	u_पूर्णांक	sblkctl;
	u_पूर्णांक	scsiseq;
	u_पूर्णांक	simode1;
	पूर्णांक	found;
	पूर्णांक	restart_needed;
	अक्षर	cur_channel;

	ahc->pending_device = शून्य;

	ahc_compile_devinfo(&devinfo,
			    CAM_TARGET_WILDCARD,
			    CAM_TARGET_WILDCARD,
			    CAM_LUN_WILDCARD,
			    channel, ROLE_UNKNOWN);
	ahc_छोड़ो(ahc);

	/* Make sure the sequencer is in a safe location. */
	ahc_clear_critical_section(ahc);

	/*
	 * Run our command complete fअगरos to ensure that we perक्रमm
	 * completion processing on any commands that 'completed'
	 * beक्रमe the reset occurred.
	 */
	ahc_run_qoutfअगरo(ahc);
#अगर_घोषित AHC_TARGET_MODE
	/*
	 * XXX - In Twin mode, the tqinfअगरo may have commands
	 *	 क्रम an unaffected channel in it.  However, अगर
	 *	 we have run out of ATIO resources to drain that
	 *	 queue, we may not get them all out here.  Further,
	 *	 the blocked transactions क्रम the reset channel
	 *	 should just be समाप्तed off, irrespecitve of whether
	 *	 we are blocked on ATIO resources.  Write a routine
	 *	 to compact the tqinfअगरo appropriately.
	 */
	अगर ((ahc->flags & AHC_TARGETROLE) != 0) अणु
		ahc_run_tqinfअगरo(ahc, /*छोड़ोd*/TRUE);
	पूर्ण
#पूर्ण_अगर

	/*
	 * Reset the bus अगर we are initiating this reset
	 */
	sblkctl = ahc_inb(ahc, SBLKCTL);
	cur_channel = 'A';
	अगर ((ahc->features & AHC_TWIN) != 0
	 && ((sblkctl & SELBUSB) != 0))
	    cur_channel = 'B';
	scsiseq = ahc_inb(ahc, SCSISEQ_TEMPLATE);
	अगर (cur_channel != channel) अणु
		/* Case 1: Command क्रम another bus is active
		 * Stealthily reset the other bus without
		 * upsetting the current bus.
		 */
		ahc_outb(ahc, SBLKCTL, sblkctl ^ SELBUSB);
		simode1 = ahc_inb(ahc, SIMODE1) & ~(ENBUSFREE|ENSCSIRST);
#अगर_घोषित AHC_TARGET_MODE
		/*
		 * Bus resets clear ENSELI, so we cannot
		 * defer re-enabling bus reset पूर्णांकerrupts
		 * अगर we are in target mode.
		 */
		अगर ((ahc->flags & AHC_TARGETROLE) != 0)
			simode1 |= ENSCSIRST;
#पूर्ण_अगर
		ahc_outb(ahc, SIMODE1, simode1);
		अगर (initiate_reset)
			ahc_reset_current_bus(ahc);
		ahc_clear_पूर्णांकstat(ahc);
		ahc_outb(ahc, SCSISEQ, scsiseq & (ENSELI|ENRSELI|ENAUTOATNP));
		ahc_outb(ahc, SBLKCTL, sblkctl);
		restart_needed = FALSE;
	पूर्ण अन्यथा अणु
		/* Case 2: A command from this bus is active or we're idle */
		simode1 = ahc_inb(ahc, SIMODE1) & ~(ENBUSFREE|ENSCSIRST);
#अगर_घोषित AHC_TARGET_MODE
		/*
		 * Bus resets clear ENSELI, so we cannot
		 * defer re-enabling bus reset पूर्णांकerrupts
		 * अगर we are in target mode.
		 */
		अगर ((ahc->flags & AHC_TARGETROLE) != 0)
			simode1 |= ENSCSIRST;
#पूर्ण_अगर
		ahc_outb(ahc, SIMODE1, simode1);
		अगर (initiate_reset)
			ahc_reset_current_bus(ahc);
		ahc_clear_पूर्णांकstat(ahc);
		ahc_outb(ahc, SCSISEQ, scsiseq & (ENSELI|ENRSELI|ENAUTOATNP));
		restart_needed = TRUE;
	पूर्ण

	/*
	 * Clean up all the state inक्रमmation क्रम the
	 * pending transactions on this bus.
	 */
	found = ahc_पात_scbs(ahc, CAM_TARGET_WILDCARD, channel,
			       CAM_LUN_WILDCARD, SCB_LIST_शून्य,
			       ROLE_UNKNOWN, CAM_SCSI_BUS_RESET);

	max_scsiid = (ahc->features & AHC_WIDE) ? 15 : 7;

#अगर_घोषित AHC_TARGET_MODE
	/*
	 * Send an immediate notअगरy ccb to all target more peripheral
	 * drivers affected by this action.
	 */
	क्रम (target = 0; target <= max_scsiid; target++) अणु
		काष्ठा ahc_पंचांगode_tstate* tstate;
		u_पूर्णांक lun;

		tstate = ahc->enabled_tarमाला_लो[target];
		अगर (tstate == शून्य)
			जारी;
		क्रम (lun = 0; lun < AHC_NUM_LUNS; lun++) अणु
			काष्ठा ahc_पंचांगode_lstate* lstate;

			lstate = tstate->enabled_luns[lun];
			अगर (lstate == शून्य)
				जारी;

			ahc_queue_lstate_event(ahc, lstate, CAM_TARGET_WILDCARD,
					       EVENT_TYPE_BUS_RESET, /*arg*/0);
			ahc_send_lstate_events(ahc, lstate);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/* Notअगरy the XPT that a bus reset occurred */
	ahc_send_async(ahc, devinfo.channel, CAM_TARGET_WILDCARD,
		       CAM_LUN_WILDCARD, AC_BUS_RESET);

	/*
	 * Revert to async/narrow transfers until we renegotiate.
	 */
	क्रम (target = 0; target <= max_scsiid; target++) अणु

		अगर (ahc->enabled_tarमाला_लो[target] == शून्य)
			जारी;
		क्रम (initiator = 0; initiator <= max_scsiid; initiator++) अणु
			काष्ठा ahc_devinfo devinfo;

			ahc_compile_devinfo(&devinfo, target, initiator,
					    CAM_LUN_WILDCARD,
					    channel, ROLE_UNKNOWN);
			ahc_set_width(ahc, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
				      AHC_TRANS_CUR, /*छोड़ोd*/TRUE);
			ahc_set_syncrate(ahc, &devinfo, /*syncrate*/शून्य,
					 /*period*/0, /*offset*/0,
					 /*ppr_options*/0, AHC_TRANS_CUR,
					 /*छोड़ोd*/TRUE);
		पूर्ण
	पूर्ण

	अगर (restart_needed)
		ahc_restart(ahc);
	अन्यथा
		ahc_unछोड़ो(ahc);
	वापस found;
पूर्ण


/***************************** Residual Processing ****************************/
/*
 * Calculate the residual क्रम a just completed SCB.
 */
अटल व्योम
ahc_calc_residual(काष्ठा ahc_softc *ahc, काष्ठा scb *scb)
अणु
	काष्ठा hardware_scb *hscb;
	काष्ठा status_pkt *spkt;
	uपूर्णांक32_t sgptr;
	uपूर्णांक32_t resid_sgptr;
	uपूर्णांक32_t resid;

	/*
	 * 5 हालs.
	 * 1) No residual.
	 *    SG_RESID_VALID clear in sgptr.
	 * 2) Transferless command
	 * 3) Never perक्रमmed any transfers.
	 *    sgptr has SG_FULL_RESID set.
	 * 4) No residual but target did not
	 *    save data poपूर्णांकers after the
	 *    last transfer, so sgptr was
	 *    never updated.
	 * 5) We have a partial residual.
	 *    Use residual_sgptr to determine
	 *    where we are.
	 */

	hscb = scb->hscb;
	sgptr = ahc_le32toh(hscb->sgptr);
	अगर ((sgptr & SG_RESID_VALID) == 0)
		/* Case 1 */
		वापस;
	sgptr &= ~SG_RESID_VALID;

	अगर ((sgptr & SG_LIST_शून्य) != 0)
		/* Case 2 */
		वापस;

	spkt = &hscb->shared_data.status;
	resid_sgptr = ahc_le32toh(spkt->residual_sg_ptr);
	अगर ((sgptr & SG_FULL_RESID) != 0) अणु
		/* Case 3 */
		resid = ahc_get_transfer_length(scb);
	पूर्ण अन्यथा अगर ((resid_sgptr & SG_LIST_शून्य) != 0) अणु
		/* Case 4 */
		वापस;
	पूर्ण अन्यथा अगर ((resid_sgptr & ~SG_PTR_MASK) != 0) अणु
		panic("Bogus resid sgptr value 0x%x\n", resid_sgptr);
	पूर्ण अन्यथा अणु
		काष्ठा ahc_dma_seg *sg;

		/*
		 * Reमुख्यder of the SG where the transfer
		 * stopped.
		 */
		resid = ahc_le32toh(spkt->residual_datacnt) & AHC_SG_LEN_MASK;
		sg = ahc_sg_bus_to_virt(scb, resid_sgptr & SG_PTR_MASK);

		/* The residual sg_ptr always poपूर्णांकs to the next sg */
		sg--;

		/*
		 * Add up the contents of all residual
		 * SG segments that are after the SG where
		 * the transfer stopped.
		 */
		जबतक ((ahc_le32toh(sg->len) & AHC_DMA_LAST_SEG) == 0) अणु
			sg++;
			resid += ahc_le32toh(sg->len) & AHC_SG_LEN_MASK;
		पूर्ण
	पूर्ण
	अगर ((scb->flags & SCB_SENSE) == 0)
		ahc_set_residual(scb, resid);
	अन्यथा
		ahc_set_sense_residual(scb, resid);

#अगर_घोषित AHC_DEBUG
	अगर ((ahc_debug & AHC_SHOW_MISC) != 0) अणु
		ahc_prपूर्णांक_path(ahc, scb);
		prपूर्णांकk("Handled %sResidual of %d bytes\n",
		       (scb->flags & SCB_SENSE) ? "Sense " : "", resid);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/******************************* Target Mode **********************************/
#अगर_घोषित AHC_TARGET_MODE
/*
 * Add a target mode event to this lun's queue
 */
अटल व्योम
ahc_queue_lstate_event(काष्ठा ahc_softc *ahc, काष्ठा ahc_पंचांगode_lstate *lstate,
		       u_पूर्णांक initiator_id, u_पूर्णांक event_type, u_पूर्णांक event_arg)
अणु
	काष्ठा ahc_पंचांगode_event *event;
	पूर्णांक pending;

	xpt_मुक्तze_devq(lstate->path, /*count*/1);
	अगर (lstate->event_w_idx >= lstate->event_r_idx)
		pending = lstate->event_w_idx - lstate->event_r_idx;
	अन्यथा
		pending = AHC_TMODE_EVENT_BUFFER_SIZE + 1
			- (lstate->event_r_idx - lstate->event_w_idx);

	अगर (event_type == EVENT_TYPE_BUS_RESET
	 || event_type == TARGET_RESET) अणु
		/*
		 * Any earlier events are irrelevant, so reset our buffer.
		 * This has the effect of allowing us to deal with reset
		 * floods (an बाह्यal device holding करोwn the reset line)
		 * without losing the event that is really पूर्णांकeresting.
		 */
		lstate->event_r_idx = 0;
		lstate->event_w_idx = 0;
		xpt_release_devq(lstate->path, pending, /*runqueue*/FALSE);
	पूर्ण

	अगर (pending == AHC_TMODE_EVENT_BUFFER_SIZE) अणु
		xpt_prपूर्णांक_path(lstate->path);
		prपूर्णांकk("immediate event %x:%x lost\n",
		       lstate->event_buffer[lstate->event_r_idx].event_type,
		       lstate->event_buffer[lstate->event_r_idx].event_arg);
		lstate->event_r_idx++;
		अगर (lstate->event_r_idx == AHC_TMODE_EVENT_BUFFER_SIZE)
			lstate->event_r_idx = 0;
		xpt_release_devq(lstate->path, /*count*/1, /*runqueue*/FALSE);
	पूर्ण

	event = &lstate->event_buffer[lstate->event_w_idx];
	event->initiator_id = initiator_id;
	event->event_type = event_type;
	event->event_arg = event_arg;
	lstate->event_w_idx++;
	अगर (lstate->event_w_idx == AHC_TMODE_EVENT_BUFFER_SIZE)
		lstate->event_w_idx = 0;
पूर्ण

/*
 * Send any target mode events queued up रुकोing
 * क्रम immediate notअगरy resources.
 */
व्योम
ahc_send_lstate_events(काष्ठा ahc_softc *ahc, काष्ठा ahc_पंचांगode_lstate *lstate)
अणु
	काष्ठा ccb_hdr *ccbh;
	काष्ठा ccb_immed_notअगरy *inot;

	जबतक (lstate->event_r_idx != lstate->event_w_idx
	    && (ccbh = SLIST_FIRST(&lstate->immed_notअगरies)) != शून्य) अणु
		काष्ठा ahc_पंचांगode_event *event;

		event = &lstate->event_buffer[lstate->event_r_idx];
		SLIST_REMOVE_HEAD(&lstate->immed_notअगरies, sim_links.sle);
		inot = (काष्ठा ccb_immed_notअगरy *)ccbh;
		चयन (event->event_type) अणु
		हाल EVENT_TYPE_BUS_RESET:
			ccbh->status = CAM_SCSI_BUS_RESET|CAM_DEV_QFRZN;
			अवरोध;
		शेष:
			ccbh->status = CAM_MESSAGE_RECV|CAM_DEV_QFRZN;
			inot->message_args[0] = event->event_type;
			inot->message_args[1] = event->event_arg;
			अवरोध;
		पूर्ण
		inot->initiator_id = event->initiator_id;
		inot->sense_len = 0;
		xpt_करोne((जोड़ ccb *)inot);
		lstate->event_r_idx++;
		अगर (lstate->event_r_idx == AHC_TMODE_EVENT_BUFFER_SIZE)
			lstate->event_r_idx = 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/******************** Sequencer Program Patching/Download *********************/

#अगर_घोषित AHC_DUMP_SEQ
व्योम
ahc_dumpseq(काष्ठा ahc_softc* ahc)
अणु
	पूर्णांक i;

	ahc_outb(ahc, SEQCTL, PERRORDIS|FAILDIS|FASTMODE|LOADRAM);
	ahc_outb(ahc, SEQADDR0, 0);
	ahc_outb(ahc, SEQADDR1, 0);
	क्रम (i = 0; i < ahc->inकाष्ठाion_ram_size; i++) अणु
		uपूर्णांक8_t ins_bytes[4];

		ahc_insb(ahc, SEQRAM, ins_bytes, 4);
		prपूर्णांकk("0x%08x\n", ins_bytes[0] << 24
				 | ins_bytes[1] << 16
				 | ins_bytes[2] << 8
				 | ins_bytes[3]);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
ahc_loadseq(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा	cs cs_table[NUM_CRITICAL_SECTIONS];
	u_पूर्णांक	begin_set[NUM_CRITICAL_SECTIONS];
	u_पूर्णांक	end_set[NUM_CRITICAL_SECTIONS];
	स्थिर काष्ठा patch *cur_patch;
	u_पूर्णांक	cs_count;
	u_पूर्णांक	cur_cs;
	u_पूर्णांक	i;
	u_पूर्णांक	skip_addr;
	u_पूर्णांक	sg_prefetch_cnt;
	पूर्णांक	करोwnloaded;
	uपूर्णांक8_t	करोwnload_स्थिरs[7];

	/*
	 * Start out with 0 critical sections
	 * that apply to this firmware load.
	 */
	cs_count = 0;
	cur_cs = 0;
	स_रखो(begin_set, 0, माप(begin_set));
	स_रखो(end_set, 0, माप(end_set));

	/* Setup करोwnloadable स्थिरant table */
	करोwnload_स्थिरs[QOUTFIFO_OFFSET] = 0;
	अगर (ahc->tarअ_लोmds != शून्य)
		करोwnload_स्थिरs[QOUTFIFO_OFFSET] += 32;
	करोwnload_स्थिरs[QINFIFO_OFFSET] = करोwnload_स्थिरs[QOUTFIFO_OFFSET] + 1;
	करोwnload_स्थिरs[CACHESIZE_MASK] = ahc->pci_cachesize - 1;
	करोwnload_स्थिरs[INVERTED_CACHESIZE_MASK] = ~(ahc->pci_cachesize - 1);
	sg_prefetch_cnt = ahc->pci_cachesize;
	अगर (sg_prefetch_cnt < (2 * माप(काष्ठा ahc_dma_seg)))
		sg_prefetch_cnt = 2 * माप(काष्ठा ahc_dma_seg);
	करोwnload_स्थिरs[SG_PREFETCH_CNT] = sg_prefetch_cnt;
	करोwnload_स्थिरs[SG_PREFETCH_ALIGN_MASK] = ~(sg_prefetch_cnt - 1);
	करोwnload_स्थिरs[SG_PREFETCH_ADDR_MASK] = (sg_prefetch_cnt - 1);

	cur_patch = patches;
	करोwnloaded = 0;
	skip_addr = 0;
	ahc_outb(ahc, SEQCTL, PERRORDIS|FAILDIS|FASTMODE|LOADRAM);
	ahc_outb(ahc, SEQADDR0, 0);
	ahc_outb(ahc, SEQADDR1, 0);

	क्रम (i = 0; i < माप(seqprog)/4; i++) अणु
		अगर (ahc_check_patch(ahc, &cur_patch, i, &skip_addr) == 0) अणु
			/*
			 * Don't करोwnload this inकाष्ठाion as it
			 * is in a patch that was हटाओd.
			 */
			जारी;
		पूर्ण

		अगर (करोwnloaded == ahc->inकाष्ठाion_ram_size) अणु
			/*
			 * We're about to exceed the inकाष्ठाion
			 * storage capacity क्रम this chip.  Fail
			 * the load.
			 */
			prपूर्णांकk("\n%s: Program too large for instruction memory "
			       "size of %d!\n", ahc_name(ahc),
			       ahc->inकाष्ठाion_ram_size);
			वापस (ENOMEM);
		पूर्ण

		/*
		 * Move through the CS table until we find a CS
		 * that might apply to this inकाष्ठाion.
		 */
		क्रम (; cur_cs < NUM_CRITICAL_SECTIONS; cur_cs++) अणु
			अगर (critical_sections[cur_cs].end <= i) अणु
				अगर (begin_set[cs_count] == TRUE
				 && end_set[cs_count] == FALSE) अणु
					cs_table[cs_count].end = करोwnloaded;
					end_set[cs_count] = TRUE;
					cs_count++;
				पूर्ण
				जारी;
			पूर्ण
			अगर (critical_sections[cur_cs].begin <= i
			 && begin_set[cs_count] == FALSE) अणु
				cs_table[cs_count].begin = करोwnloaded;
				begin_set[cs_count] = TRUE;
			पूर्ण
			अवरोध;
		पूर्ण
		ahc_करोwnload_instr(ahc, i, करोwnload_स्थिरs);
		करोwnloaded++;
	पूर्ण

	ahc->num_critical_sections = cs_count;
	अगर (cs_count != 0) अणु

		cs_count *= माप(काष्ठा cs);
		ahc->critical_sections = kmemdup(cs_table, cs_count, GFP_ATOMIC);
		अगर (ahc->critical_sections == शून्य)
			panic("ahc_loadseq: Could not malloc");
	पूर्ण
	ahc_outb(ahc, SEQCTL, PERRORDIS|FAILDIS|FASTMODE);

	अगर (bootverbose) अणु
		prपूर्णांकk(" %d instructions downloaded\n", करोwnloaded);
		prपूर्णांकk("%s: Features 0x%x, Bugs 0x%x, Flags 0x%x\n",
		       ahc_name(ahc), ahc->features, ahc->bugs, ahc->flags);
	पूर्ण
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_check_patch(काष्ठा ahc_softc *ahc, स्थिर काष्ठा patch **start_patch,
		u_पूर्णांक start_instr, u_पूर्णांक *skip_addr)
अणु
	स्थिर काष्ठा patch *cur_patch;
	स्थिर काष्ठा patch *last_patch;
	u_पूर्णांक	num_patches;

	num_patches = ARRAY_SIZE(patches);
	last_patch = &patches[num_patches];
	cur_patch = *start_patch;

	जबतक (cur_patch < last_patch && start_instr == cur_patch->begin) अणु

		अगर (cur_patch->patch_func(ahc) == 0) अणु

			/* Start rejecting code */
			*skip_addr = start_instr + cur_patch->skip_instr;
			cur_patch += cur_patch->skip_patch;
		पूर्ण अन्यथा अणु
			/* Accepted this patch.  Advance to the next
			 * one and रुको क्रम our पूर्णांकruction poपूर्णांकer to
			 * hit this poपूर्णांक.
			 */
			cur_patch++;
		पूर्ण
	पूर्ण

	*start_patch = cur_patch;
	अगर (start_instr < *skip_addr)
		/* Still skipping */
		वापस (0);

	वापस (1);
पूर्ण

अटल व्योम
ahc_करोwnload_instr(काष्ठा ahc_softc *ahc, u_पूर्णांक instrptr, uपूर्णांक8_t *dस्थिरs)
अणु
	जोड़	ins_क्रमmats instr;
	काष्ठा	ins_क्रमmat1 *fmt1_ins;
	काष्ठा	ins_क्रमmat3 *fmt3_ins;
	u_पूर्णांक	opcode;

	/*
	 * The firmware is always compiled पूर्णांकo a little endian क्रमmat.
	 */
	instr.पूर्णांकeger = ahc_le32toh(*(uपूर्णांक32_t*)&seqprog[instrptr * 4]);

	fmt1_ins = &instr.क्रमmat1;
	fmt3_ins = शून्य;

	/* Pull the opcode */
	opcode = instr.क्रमmat1.opcode;
	चयन (opcode) अणु
	हाल AIC_OP_JMP:
	हाल AIC_OP_JC:
	हाल AIC_OP_JNC:
	हाल AIC_OP_CALL:
	हाल AIC_OP_JNE:
	हाल AIC_OP_JNZ:
	हाल AIC_OP_JE:
	हाल AIC_OP_JZ:
	अणु
		स्थिर काष्ठा patch *cur_patch;
		पूर्णांक address_offset;
		u_पूर्णांक address;
		u_पूर्णांक skip_addr;
		u_पूर्णांक i;

		fmt3_ins = &instr.क्रमmat3;
		address_offset = 0;
		address = fmt3_ins->address;
		cur_patch = patches;
		skip_addr = 0;

		क्रम (i = 0; i < address;) अणु

			ahc_check_patch(ahc, &cur_patch, i, &skip_addr);

			अगर (skip_addr > i) अणु
				पूर्णांक end_addr;

				end_addr = min(address, skip_addr);
				address_offset += end_addr - i;
				i = skip_addr;
			पूर्ण अन्यथा अणु
				i++;
			पूर्ण
		पूर्ण
		address -= address_offset;
		fmt3_ins->address = address;
	पूर्ण
		fallthrough;
	हाल AIC_OP_OR:
	हाल AIC_OP_AND:
	हाल AIC_OP_XOR:
	हाल AIC_OP_ADD:
	हाल AIC_OP_ADC:
	हाल AIC_OP_BMOV:
		अगर (fmt1_ins->parity != 0) अणु
			fmt1_ins->immediate = dस्थिरs[fmt1_ins->immediate];
		पूर्ण
		fmt1_ins->parity = 0;
		अगर ((ahc->features & AHC_CMD_CHAN) == 0
		 && opcode == AIC_OP_BMOV) अणु
			/*
			 * Block move was added at the same समय
			 * as the command channel.  Verअगरy that
			 * this is only a move of a single element
			 * and convert the BMOV to a MOV
			 * (AND with an immediate of FF).
			 */
			अगर (fmt1_ins->immediate != 1)
				panic("%s: BMOV not supported\n",
				      ahc_name(ahc));
			fmt1_ins->opcode = AIC_OP_AND;
			fmt1_ins->immediate = 0xff;
		पूर्ण
		fallthrough;
	हाल AIC_OP_ROL:
		अगर ((ahc->features & AHC_ULTRA2) != 0) अणु
			पूर्णांक i, count;

			/* Calculate odd parity क्रम the inकाष्ठाion */
			क्रम (i = 0, count = 0; i < 31; i++) अणु
				uपूर्णांक32_t mask;

				mask = 0x01 << i;
				अगर ((instr.पूर्णांकeger & mask) != 0)
					count++;
			पूर्ण
			अगर ((count & 0x01) == 0)
				instr.क्रमmat1.parity = 1;
		पूर्ण अन्यथा अणु
			/* Compress the inकाष्ठाion क्रम older sequencers */
			अगर (fmt3_ins != शून्य) अणु
				instr.पूर्णांकeger =
					fmt3_ins->immediate
				      | (fmt3_ins->source << 8)
				      | (fmt3_ins->address << 16)
				      |	(fmt3_ins->opcode << 25);
			पूर्ण अन्यथा अणु
				instr.पूर्णांकeger =
					fmt1_ins->immediate
				      | (fmt1_ins->source << 8)
				      | (fmt1_ins->destination << 16)
				      |	(fmt1_ins->ret << 24)
				      |	(fmt1_ins->opcode << 25);
			पूर्ण
		पूर्ण
		/* The sequencer is a little endian cpu */
		instr.पूर्णांकeger = ahc_htole32(instr.पूर्णांकeger);
		ahc_outsb(ahc, SEQRAM, instr.bytes, 4);
		अवरोध;
	शेष:
		panic("Unknown opcode encountered in seq program");
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक
ahc_prपूर्णांक_रेजिस्टर(स्थिर ahc_reg_parse_entry_t *table, u_पूर्णांक num_entries,
		   स्थिर अक्षर *name, u_पूर्णांक address, u_पूर्णांक value,
		   u_पूर्णांक *cur_column, u_पूर्णांक wrap_poपूर्णांक)
अणु
	पूर्णांक	prपूर्णांकed;
	u_पूर्णांक	prपूर्णांकed_mask;

	अगर (cur_column != शून्य && *cur_column >= wrap_poपूर्णांक) अणु
		prपूर्णांकk("\n");
		*cur_column = 0;
	पूर्ण
	prपूर्णांकed  = prपूर्णांकk("%s[0x%x]", name, value);
	अगर (table == शून्य) अणु
		prपूर्णांकed += prपूर्णांकk(" ");
		*cur_column += prपूर्णांकed;
		वापस (prपूर्णांकed);
	पूर्ण
	prपूर्णांकed_mask = 0;
	जबतक (prपूर्णांकed_mask != 0xFF) अणु
		पूर्णांक entry;

		क्रम (entry = 0; entry < num_entries; entry++) अणु
			अगर (((value & table[entry].mask)
			  != table[entry].value)
			 || ((prपूर्णांकed_mask & table[entry].mask)
			  == table[entry].mask))
				जारी;

			prपूर्णांकed += prपूर्णांकk("%s%s",
					  prपूर्णांकed_mask == 0 ? ":(" : "|",
					  table[entry].name);
			prपूर्णांकed_mask |= table[entry].mask;
			अवरोध;
		पूर्ण
		अगर (entry >= num_entries)
			अवरोध;
	पूर्ण
	अगर (prपूर्णांकed_mask != 0)
		prपूर्णांकed += prपूर्णांकk(") ");
	अन्यथा
		prपूर्णांकed += prपूर्णांकk(" ");
	अगर (cur_column != शून्य)
		*cur_column += prपूर्णांकed;
	वापस (prपूर्णांकed);
पूर्ण

व्योम
ahc_dump_card_state(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा	scb *scb;
	काष्ठा	scb_tailq *untagged_q;
	u_पूर्णांक	cur_col;
	पूर्णांक	छोड़ोd;
	पूर्णांक	target;
	पूर्णांक	maxtarget;
	पूर्णांक	i;
	uपूर्णांक8_t last_phase;
	uपूर्णांक8_t qinpos;
	uपूर्णांक8_t qपूर्णांकail;
	uपूर्णांक8_t qoutpos;
	uपूर्णांक8_t scb_index;
	uपूर्णांक8_t saved_scbptr;

	अगर (ahc_is_छोड़ोd(ahc)) अणु
		छोड़ोd = 1;
	पूर्ण अन्यथा अणु
		छोड़ोd = 0;
		ahc_छोड़ो(ahc);
	पूर्ण

	saved_scbptr = ahc_inb(ahc, SCBPTR);
	last_phase = ahc_inb(ahc, LASTPHASE);
	prपूर्णांकk(">>>>>>>>>>>>>>>>>> Dump Card State Begins <<<<<<<<<<<<<<<<<\n"
	       "%s: Dumping Card State %s, at SEQADDR 0x%x\n",
	       ahc_name(ahc), ahc_lookup_phase_entry(last_phase)->phasemsg,
	       ahc_inb(ahc, SEQADDR0) | (ahc_inb(ahc, SEQADDR1) << 8));
	अगर (छोड़ोd)
		prपूर्णांकk("Card was paused\n");
	prपूर्णांकk("ACCUM = 0x%x, SINDEX = 0x%x, DINDEX = 0x%x, ARG_2 = 0x%x\n",
	       ahc_inb(ahc, ACCUM), ahc_inb(ahc, SINDEX), ahc_inb(ahc, DINDEX),
	       ahc_inb(ahc, ARG_2));
	prपूर्णांकk("HCNT = 0x%x SCBPTR = 0x%x\n", ahc_inb(ahc, HCNT),
	       ahc_inb(ahc, SCBPTR));
	cur_col = 0;
	अगर ((ahc->features & AHC_DT) != 0)
		ahc_scsiphase_prपूर्णांक(ahc_inb(ahc, SCSIPHASE), &cur_col, 50);
	ahc_scsisigi_prपूर्णांक(ahc_inb(ahc, SCSISIGI), &cur_col, 50);
	ahc_error_prपूर्णांक(ahc_inb(ahc, ERROR), &cur_col, 50);
	ahc_scsibusl_prपूर्णांक(ahc_inb(ahc, SCSIBUSL), &cur_col, 50);
	ahc_lastphase_prपूर्णांक(ahc_inb(ahc, LASTPHASE), &cur_col, 50);
	ahc_scsiseq_prपूर्णांक(ahc_inb(ahc, SCSISEQ), &cur_col, 50);
	ahc_sblkctl_prपूर्णांक(ahc_inb(ahc, SBLKCTL), &cur_col, 50);
	ahc_scsirate_prपूर्णांक(ahc_inb(ahc, SCSIRATE), &cur_col, 50);
	ahc_seqctl_prपूर्णांक(ahc_inb(ahc, SEQCTL), &cur_col, 50);
	ahc_seq_flags_prपूर्णांक(ahc_inb(ahc, SEQ_FLAGS), &cur_col, 50);
	ahc_sstat0_prपूर्णांक(ahc_inb(ahc, SSTAT0), &cur_col, 50);
	ahc_sstat1_prपूर्णांक(ahc_inb(ahc, SSTAT1), &cur_col, 50);
	ahc_sstat2_prपूर्णांक(ahc_inb(ahc, SSTAT2), &cur_col, 50);
	ahc_sstat3_prपूर्णांक(ahc_inb(ahc, SSTAT3), &cur_col, 50);
	ahc_simode0_prपूर्णांक(ahc_inb(ahc, SIMODE0), &cur_col, 50);
	ahc_simode1_prपूर्णांक(ahc_inb(ahc, SIMODE1), &cur_col, 50);
	ahc_sxfrctl0_prपूर्णांक(ahc_inb(ahc, SXFRCTL0), &cur_col, 50);
	ahc_dfcntrl_prपूर्णांक(ahc_inb(ahc, DFCNTRL), &cur_col, 50);
	ahc_dख_स्थितिus_prपूर्णांक(ahc_inb(ahc, DFSTATUS), &cur_col, 50);
	अगर (cur_col != 0)
		prपूर्णांकk("\n");
	prपूर्णांकk("STACK:");
	क्रम (i = 0; i < STACK_SIZE; i++)
		prपूर्णांकk(" 0x%x", ahc_inb(ahc, STACK)|(ahc_inb(ahc, STACK) << 8));
	prपूर्णांकk("\nSCB count = %d\n", ahc->scb_data->numscbs);
	prपूर्णांकk("Kernel NEXTQSCB = %d\n", ahc->next_queued_scb->hscb->tag);
	prपूर्णांकk("Card NEXTQSCB = %d\n", ahc_inb(ahc, NEXT_QUEUED_SCB));
	/* QINFIFO */
	prपूर्णांकk("QINFIFO entries: ");
	अगर ((ahc->features & AHC_QUEUE_REGS) != 0) अणु
		qinpos = ahc_inb(ahc, SNSCB_QOFF);
		ahc_outb(ahc, SNSCB_QOFF, qinpos);
	पूर्ण अन्यथा
		qinpos = ahc_inb(ahc, QINPOS);
	qपूर्णांकail = ahc->qinfअगरonext;
	जबतक (qinpos != qपूर्णांकail) अणु
		prपूर्णांकk("%d ", ahc->qinfअगरo[qinpos]);
		qinpos++;
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("Waiting Queue entries: ");
	scb_index = ahc_inb(ahc, WAITING_SCBH);
	i = 0;
	जबतक (scb_index != SCB_LIST_शून्य && i++ < 256) अणु
		ahc_outb(ahc, SCBPTR, scb_index);
		prपूर्णांकk("%d:%d ", scb_index, ahc_inb(ahc, SCB_TAG));
		scb_index = ahc_inb(ahc, SCB_NEXT);
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("Disconnected Queue entries: ");
	scb_index = ahc_inb(ahc, DISCONNECTED_SCBH);
	i = 0;
	जबतक (scb_index != SCB_LIST_शून्य && i++ < 256) अणु
		ahc_outb(ahc, SCBPTR, scb_index);
		prपूर्णांकk("%d:%d ", scb_index, ahc_inb(ahc, SCB_TAG));
		scb_index = ahc_inb(ahc, SCB_NEXT);
	पूर्ण
	prपूर्णांकk("\n");

	ahc_sync_qoutfअगरo(ahc, BUS_DMASYNC_POSTREAD);
	prपूर्णांकk("QOUTFIFO entries: ");
	qoutpos = ahc->qoutfअगरonext;
	i = 0;
	जबतक (ahc->qoutfअगरo[qoutpos] != SCB_LIST_शून्य && i++ < 256) अणु
		prपूर्णांकk("%d ", ahc->qoutfअगरo[qoutpos]);
		qoutpos++;
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("Sequencer Free SCB List: ");
	scb_index = ahc_inb(ahc, FREE_SCBH);
	i = 0;
	जबतक (scb_index != SCB_LIST_शून्य && i++ < 256) अणु
		ahc_outb(ahc, SCBPTR, scb_index);
		prपूर्णांकk("%d ", scb_index);
		scb_index = ahc_inb(ahc, SCB_NEXT);
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("Sequencer SCB Info: ");
	क्रम (i = 0; i < ahc->scb_data->maxhscbs; i++) अणु
		ahc_outb(ahc, SCBPTR, i);
		cur_col  = prपूर्णांकk("\n%3d ", i);

		ahc_scb_control_prपूर्णांक(ahc_inb(ahc, SCB_CONTROL), &cur_col, 60);
		ahc_scb_scsiid_prपूर्णांक(ahc_inb(ahc, SCB_SCSIID), &cur_col, 60);
		ahc_scb_lun_prपूर्णांक(ahc_inb(ahc, SCB_LUN), &cur_col, 60);
		ahc_scb_tag_prपूर्णांक(ahc_inb(ahc, SCB_TAG), &cur_col, 60);
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("Pending list: ");
	i = 0;
	LIST_FOREACH(scb, &ahc->pending_scbs, pending_links) अणु
		अगर (i++ > 256)
			अवरोध;
		cur_col  = prपूर्णांकk("\n%3d ", scb->hscb->tag);
		ahc_scb_control_prपूर्णांक(scb->hscb->control, &cur_col, 60);
		ahc_scb_scsiid_prपूर्णांक(scb->hscb->scsiid, &cur_col, 60);
		ahc_scb_lun_prपूर्णांक(scb->hscb->lun, &cur_col, 60);
		अगर ((ahc->flags & AHC_PAGESCBS) == 0) अणु
			ahc_outb(ahc, SCBPTR, scb->hscb->tag);
			prपूर्णांकk("(");
			ahc_scb_control_prपूर्णांक(ahc_inb(ahc, SCB_CONTROL),
					      &cur_col, 60);
			ahc_scb_tag_prपूर्णांक(ahc_inb(ahc, SCB_TAG), &cur_col, 60);
			prपूर्णांकk(")");
		पूर्ण
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("Kernel Free SCB list: ");
	i = 0;
	SLIST_FOREACH(scb, &ahc->scb_data->मुक्त_scbs, links.sle) अणु
		अगर (i++ > 256)
			अवरोध;
		prपूर्णांकk("%d ", scb->hscb->tag);
	पूर्ण
	prपूर्णांकk("\n");

	maxtarget = (ahc->features & (AHC_WIDE|AHC_TWIN)) ? 15 : 7;
	क्रम (target = 0; target <= maxtarget; target++) अणु
		untagged_q = &ahc->untagged_queues[target];
		अगर (TAILQ_FIRST(untagged_q) == शून्य)
			जारी;
		prपूर्णांकk("Untagged Q(%d): ", target);
		i = 0;
		TAILQ_FOREACH(scb, untagged_q, links.tqe) अणु
			अगर (i++ > 256)
				अवरोध;
			prपूर्णांकk("%d ", scb->hscb->tag);
		पूर्ण
		prपूर्णांकk("\n");
	पूर्ण

	prपूर्णांकk("\n<<<<<<<<<<<<<<<<< Dump Card State Ends >>>>>>>>>>>>>>>>>>\n");
	ahc_outb(ahc, SCBPTR, saved_scbptr);
	अगर (छोड़ोd == 0)
		ahc_unछोड़ो(ahc);
पूर्ण

/************************* Target Mode ****************************************/
#अगर_घोषित AHC_TARGET_MODE
cam_status
ahc_find_पंचांगode_devs(काष्ठा ahc_softc *ahc, काष्ठा cam_sim *sim, जोड़ ccb *ccb,
		    काष्ठा ahc_पंचांगode_tstate **tstate,
		    काष्ठा ahc_पंचांगode_lstate **lstate,
		    पूर्णांक notfound_failure)
अणु

	अगर ((ahc->features & AHC_TARGETMODE) == 0)
		वापस (CAM_REQ_INVALID);

	/*
	 * Handle the 'black hole' device that sucks up
	 * requests to unattached luns on enabled tarमाला_लो.
	 */
	अगर (ccb->ccb_h.target_id == CAM_TARGET_WILDCARD
	 && ccb->ccb_h.target_lun == CAM_LUN_WILDCARD) अणु
		*tstate = शून्य;
		*lstate = ahc->black_hole;
	पूर्ण अन्यथा अणु
		u_पूर्णांक max_id;

		max_id = (ahc->features & AHC_WIDE) ? 16 : 8;
		अगर (ccb->ccb_h.target_id >= max_id)
			वापस (CAM_TID_INVALID);

		अगर (ccb->ccb_h.target_lun >= AHC_NUM_LUNS)
			वापस (CAM_LUN_INVALID);

		*tstate = ahc->enabled_tarमाला_लो[ccb->ccb_h.target_id];
		*lstate = शून्य;
		अगर (*tstate != शून्य)
			*lstate =
			    (*tstate)->enabled_luns[ccb->ccb_h.target_lun];
	पूर्ण

	अगर (notfound_failure != 0 && *lstate == शून्य)
		वापस (CAM_PATH_INVALID);

	वापस (CAM_REQ_CMP);
पूर्ण

व्योम
ahc_handle_en_lun(काष्ठा ahc_softc *ahc, काष्ठा cam_sim *sim, जोड़ ccb *ccb)
अणु
	काष्ठा	   ahc_पंचांगode_tstate *tstate;
	काष्ठा	   ahc_पंचांगode_lstate *lstate;
	काष्ठा	   ccb_en_lun *cel;
	cam_status status;
	u_दीर्घ	   s;
	u_पूर्णांक	   target;
	u_पूर्णांक	   lun;
	u_पूर्णांक	   target_mask;
	u_पूर्णांक	   our_id;
	पूर्णांक	   error;
	अक्षर	   channel;

	status = ahc_find_पंचांगode_devs(ahc, sim, ccb, &tstate, &lstate,
				     /*notfound_failure*/FALSE);

	अगर (status != CAM_REQ_CMP) अणु
		ccb->ccb_h.status = status;
		वापस;
	पूर्ण

	अगर (cam_sim_bus(sim) == 0)
		our_id = ahc->our_id;
	अन्यथा
		our_id = ahc->our_id_b;

	अगर (ccb->ccb_h.target_id != our_id) अणु
		/*
		 * our_id represents our initiator ID, or
		 * the ID of the first target to have an
		 * enabled lun in target mode.  There are
		 * two हालs that may preclude enabling a
		 * target id other than our_id.
		 *
		 *   o our_id is क्रम an active initiator role.
		 *     Since the hardware करोes not support
		 *     reselections to the initiator role at
		 *     anything other than our_id, and our_id
		 *     is used by the hardware to indicate the
		 *     ID to use क्रम both select-out and
		 *     reselect-out operations, the only target
		 *     ID we can support in this mode is our_id.
		 *
		 *   o The MULTARGID feature is not available and
		 *     a previous target mode ID has been enabled.
		 */
		अगर ((ahc->features & AHC_MULTIROLE) != 0) अणु

			अगर ((ahc->features & AHC_MULTI_TID) != 0
			 && (ahc->flags & AHC_INITIATORROLE) != 0) अणु
				/*
				 * Only allow additional tarमाला_लो अगर
				 * the initiator role is disabled.
				 * The hardware cannot handle a re-select-in
				 * on the initiator id during a re-select-out
				 * on a dअगरferent target id.
				 */
				status = CAM_TID_INVALID;
			पूर्ण अन्यथा अगर ((ahc->flags & AHC_INITIATORROLE) != 0
				|| ahc->enabled_luns > 0) अणु
				/*
				 * Only allow our target id to change
				 * अगर the initiator role is not configured
				 * and there are no enabled luns which
				 * are attached to the currently रेजिस्टरed
				 * scsi id.
				 */
				status = CAM_TID_INVALID;
			पूर्ण
		पूर्ण अन्यथा अगर ((ahc->features & AHC_MULTI_TID) == 0
			&& ahc->enabled_luns > 0) अणु

			status = CAM_TID_INVALID;
		पूर्ण
	पूर्ण

	अगर (status != CAM_REQ_CMP) अणु
		ccb->ccb_h.status = status;
		वापस;
	पूर्ण

	/*
	 * We now have an id that is valid.
	 * If we aren't in target mode, चयन modes.
	 */
	अगर ((ahc->flags & AHC_TARGETROLE) == 0
	 && ccb->ccb_h.target_id != CAM_TARGET_WILDCARD) अणु
		u_दीर्घ	 s;
		ahc_flag saved_flags;

		prपूर्णांकk("Configuring Target Mode\n");
		ahc_lock(ahc, &s);
		अगर (LIST_FIRST(&ahc->pending_scbs) != शून्य) अणु
			ccb->ccb_h.status = CAM_BUSY;
			ahc_unlock(ahc, &s);
			वापस;
		पूर्ण
		saved_flags = ahc->flags;
		ahc->flags |= AHC_TARGETROLE;
		अगर ((ahc->features & AHC_MULTIROLE) == 0)
			ahc->flags &= ~AHC_INITIATORROLE;
		ahc_छोड़ो(ahc);
		error = ahc_loadseq(ahc);
		अगर (error != 0) अणु
			/*
			 * Restore original configuration and notअगरy
			 * the caller that we cannot support target mode.
			 * Since the adapter started out in this
			 * configuration, the firmware load will succeed,
			 * so there is no poपूर्णांक in checking ahc_loadseq's
			 * वापस value.
			 */
			ahc->flags = saved_flags;
			(व्योम)ahc_loadseq(ahc);
			ahc_restart(ahc);
			ahc_unlock(ahc, &s);
			ccb->ccb_h.status = CAM_FUNC_NOTAVAIL;
			वापस;
		पूर्ण
		ahc_restart(ahc);
		ahc_unlock(ahc, &s);
	पूर्ण
	cel = &ccb->cel;
	target = ccb->ccb_h.target_id;
	lun = ccb->ccb_h.target_lun;
	channel = SIM_CHANNEL(ahc, sim);
	target_mask = 0x01 << target;
	अगर (channel == 'B')
		target_mask <<= 8;

	अगर (cel->enable != 0) अणु
		u_पूर्णांक scsiseq;

		/* Are we alपढ़ोy enabled?? */
		अगर (lstate != शून्य) अणु
			xpt_prपूर्णांक_path(ccb->ccb_h.path);
			prपूर्णांकk("Lun already enabled\n");
			ccb->ccb_h.status = CAM_LUN_ALRDY_ENA;
			वापस;
		पूर्ण

		अगर (cel->grp6_len != 0
		 || cel->grp7_len != 0) अणु
			/*
			 * Don't (yet?) support venकरोr
			 * specअगरic commands.
			 */
			ccb->ccb_h.status = CAM_REQ_INVALID;
			prपूर्णांकk("Non-zero Group Codes\n");
			वापस;
		पूर्ण

		/*
		 * Seems to be okay.
		 * Setup our data काष्ठाures.
		 */
		अगर (target != CAM_TARGET_WILDCARD && tstate == शून्य) अणु
			tstate = ahc_alloc_tstate(ahc, target, channel);
			अगर (tstate == शून्य) अणु
				xpt_prपूर्णांक_path(ccb->ccb_h.path);
				prपूर्णांकk("Couldn't allocate tstate\n");
				ccb->ccb_h.status = CAM_RESRC_UNAVAIL;
				वापस;
			पूर्ण
		पूर्ण
		lstate = kzalloc(माप(*lstate), GFP_ATOMIC);
		अगर (lstate == शून्य) अणु
			xpt_prपूर्णांक_path(ccb->ccb_h.path);
			prपूर्णांकk("Couldn't allocate lstate\n");
			ccb->ccb_h.status = CAM_RESRC_UNAVAIL;
			वापस;
		पूर्ण
		status = xpt_create_path(&lstate->path, /*periph*/शून्य,
					 xpt_path_path_id(ccb->ccb_h.path),
					 xpt_path_target_id(ccb->ccb_h.path),
					 xpt_path_lun_id(ccb->ccb_h.path));
		अगर (status != CAM_REQ_CMP) अणु
			kमुक्त(lstate);
			xpt_prपूर्णांक_path(ccb->ccb_h.path);
			prपूर्णांकk("Couldn't allocate path\n");
			ccb->ccb_h.status = CAM_RESRC_UNAVAIL;
			वापस;
		पूर्ण
		SLIST_INIT(&lstate->accept_tios);
		SLIST_INIT(&lstate->immed_notअगरies);
		ahc_lock(ahc, &s);
		ahc_छोड़ो(ahc);
		अगर (target != CAM_TARGET_WILDCARD) अणु
			tstate->enabled_luns[lun] = lstate;
			ahc->enabled_luns++;

			अगर ((ahc->features & AHC_MULTI_TID) != 0) अणु
				u_पूर्णांक targid_mask;

				targid_mask = ahc_inb(ahc, TARGID)
					    | (ahc_inb(ahc, TARGID + 1) << 8);

				targid_mask |= target_mask;
				ahc_outb(ahc, TARGID, targid_mask);
				ahc_outb(ahc, TARGID+1, (targid_mask >> 8));
				ahc_update_scsiid(ahc, targid_mask);
			पूर्ण अन्यथा अणु
				u_पूर्णांक our_id;
				अक्षर  channel;

				channel = SIM_CHANNEL(ahc, sim);
				our_id = SIM_SCSI_ID(ahc, sim);

				/*
				 * This can only happen अगर selections
				 * are not enabled
				 */
				अगर (target != our_id) अणु
					u_पूर्णांक sblkctl;
					अक्षर  cur_channel;
					पूर्णांक   swap;

					sblkctl = ahc_inb(ahc, SBLKCTL);
					cur_channel = (sblkctl & SELBUSB)
						    ? 'B' : 'A';
					अगर ((ahc->features & AHC_TWIN) == 0)
						cur_channel = 'A';
					swap = cur_channel != channel;
					अगर (channel == 'A')
						ahc->our_id = target;
					अन्यथा
						ahc->our_id_b = target;

					अगर (swap)
						ahc_outb(ahc, SBLKCTL,
							 sblkctl ^ SELBUSB);

					ahc_outb(ahc, SCSIID, target);

					अगर (swap)
						ahc_outb(ahc, SBLKCTL, sblkctl);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			ahc->black_hole = lstate;
		/* Allow select-in operations */
		अगर (ahc->black_hole != शून्य && ahc->enabled_luns > 0) अणु
			scsiseq = ahc_inb(ahc, SCSISEQ_TEMPLATE);
			scsiseq |= ENSELI;
			ahc_outb(ahc, SCSISEQ_TEMPLATE, scsiseq);
			scsiseq = ahc_inb(ahc, SCSISEQ);
			scsiseq |= ENSELI;
			ahc_outb(ahc, SCSISEQ, scsiseq);
		पूर्ण
		ahc_unछोड़ो(ahc);
		ahc_unlock(ahc, &s);
		ccb->ccb_h.status = CAM_REQ_CMP;
		xpt_prपूर्णांक_path(ccb->ccb_h.path);
		prपूर्णांकk("Lun now enabled for target mode\n");
	पूर्ण अन्यथा अणु
		काष्ठा scb *scb;
		पूर्णांक i, empty;

		अगर (lstate == शून्य) अणु
			ccb->ccb_h.status = CAM_LUN_INVALID;
			वापस;
		पूर्ण

		ahc_lock(ahc, &s);

		ccb->ccb_h.status = CAM_REQ_CMP;
		LIST_FOREACH(scb, &ahc->pending_scbs, pending_links) अणु
			काष्ठा ccb_hdr *ccbh;

			ccbh = &scb->io_ctx->ccb_h;
			अगर (ccbh->func_code == XPT_CONT_TARGET_IO
			 && !xpt_path_comp(ccbh->path, ccb->ccb_h.path))अणु
				prपूर्णांकk("CTIO pending\n");
				ccb->ccb_h.status = CAM_REQ_INVALID;
				ahc_unlock(ahc, &s);
				वापस;
			पूर्ण
		पूर्ण

		अगर (SLIST_FIRST(&lstate->accept_tios) != शून्य) अणु
			prपूर्णांकk("ATIOs pending\n");
			ccb->ccb_h.status = CAM_REQ_INVALID;
		पूर्ण

		अगर (SLIST_FIRST(&lstate->immed_notअगरies) != शून्य) अणु
			prपूर्णांकk("INOTs pending\n");
			ccb->ccb_h.status = CAM_REQ_INVALID;
		पूर्ण

		अगर (ccb->ccb_h.status != CAM_REQ_CMP) अणु
			ahc_unlock(ahc, &s);
			वापस;
		पूर्ण

		xpt_prपूर्णांक_path(ccb->ccb_h.path);
		prपूर्णांकk("Target mode disabled\n");
		xpt_मुक्त_path(lstate->path);
		kमुक्त(lstate);

		ahc_छोड़ो(ahc);
		/* Can we clean up the target too? */
		अगर (target != CAM_TARGET_WILDCARD) अणु
			tstate->enabled_luns[lun] = शून्य;
			ahc->enabled_luns--;
			क्रम (empty = 1, i = 0; i < 8; i++)
				अगर (tstate->enabled_luns[i] != शून्य) अणु
					empty = 0;
					अवरोध;
				पूर्ण

			अगर (empty) अणु
				ahc_मुक्त_tstate(ahc, target, channel,
						/*क्रमce*/FALSE);
				अगर (ahc->features & AHC_MULTI_TID) अणु
					u_पूर्णांक targid_mask;

					targid_mask = ahc_inb(ahc, TARGID)
						    | (ahc_inb(ahc, TARGID + 1)
						       << 8);

					targid_mask &= ~target_mask;
					ahc_outb(ahc, TARGID, targid_mask);
					ahc_outb(ahc, TARGID+1,
						 (targid_mask >> 8));
					ahc_update_scsiid(ahc, targid_mask);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु

			ahc->black_hole = शून्य;

			/*
			 * We can't allow selections without
			 * our black hole device.
			 */
			empty = TRUE;
		पूर्ण
		अगर (ahc->enabled_luns == 0) अणु
			/* Disallow select-in */
			u_पूर्णांक scsiseq;

			scsiseq = ahc_inb(ahc, SCSISEQ_TEMPLATE);
			scsiseq &= ~ENSELI;
			ahc_outb(ahc, SCSISEQ_TEMPLATE, scsiseq);
			scsiseq = ahc_inb(ahc, SCSISEQ);
			scsiseq &= ~ENSELI;
			ahc_outb(ahc, SCSISEQ, scsiseq);

			अगर ((ahc->features & AHC_MULTIROLE) == 0) अणु
				prपूर्णांकk("Configuring Initiator Mode\n");
				ahc->flags &= ~AHC_TARGETROLE;
				ahc->flags |= AHC_INITIATORROLE;
				/*
				 * Returning to a configuration that
				 * fit previously will always succeed.
				 */
				(व्योम)ahc_loadseq(ahc);
				ahc_restart(ahc);
				/*
				 * Unछोड़ोd.  The extra unछोड़ो
				 * that follows is harmless.
				 */
			पूर्ण
		पूर्ण
		ahc_unछोड़ो(ahc);
		ahc_unlock(ahc, &s);
	पूर्ण
पूर्ण

अटल व्योम
ahc_update_scsiid(काष्ठा ahc_softc *ahc, u_पूर्णांक targid_mask)
अणु
	u_पूर्णांक scsiid_mask;
	u_पूर्णांक scsiid;

	अगर ((ahc->features & AHC_MULTI_TID) == 0)
		panic("ahc_update_scsiid called on non-multitid unit\n");

	/*
	 * Since we will rely on the TARGID mask
	 * क्रम selection enables, ensure that OID
	 * in SCSIID is not set to some other ID
	 * that we करोn't want to allow selections on.
	 */
	अगर ((ahc->features & AHC_ULTRA2) != 0)
		scsiid = ahc_inb(ahc, SCSIID_ULTRA2);
	अन्यथा
		scsiid = ahc_inb(ahc, SCSIID);
	scsiid_mask = 0x1 << (scsiid & OID);
	अगर ((targid_mask & scsiid_mask) == 0) अणु
		u_पूर्णांक our_id;

		/* ffs counts from 1 */
		our_id = ffs(targid_mask);
		अगर (our_id == 0)
			our_id = ahc->our_id;
		अन्यथा
			our_id--;
		scsiid &= TID;
		scsiid |= our_id;
	पूर्ण
	अगर ((ahc->features & AHC_ULTRA2) != 0)
		ahc_outb(ahc, SCSIID_ULTRA2, scsiid);
	अन्यथा
		ahc_outb(ahc, SCSIID, scsiid);
पूर्ण

अटल व्योम
ahc_run_tqinfअगरo(काष्ठा ahc_softc *ahc, पूर्णांक छोड़ोd)
अणु
	काष्ठा target_cmd *cmd;

	/*
	 * If the card supports स्वतः-access छोड़ो,
	 * we can access the card directly regardless
	 * of whether it is छोड़ोd or not.
	 */
	अगर ((ahc->features & AHC_AUTOPAUSE) != 0)
		छोड़ोd = TRUE;

	ahc_sync_tqinfअगरo(ahc, BUS_DMASYNC_POSTREAD);
	जबतक ((cmd = &ahc->tarअ_लोmds[ahc->tqinfअगरonext])->cmd_valid != 0) अणु

		/*
		 * Only advance through the queue अगर we
		 * have the resources to process the command.
		 */
		अगर (ahc_handle_target_cmd(ahc, cmd) != 0)
			अवरोध;

		cmd->cmd_valid = 0;
		ahc_dmamap_sync(ahc, ahc->shared_data_dmat,
				ahc->shared_data_dmamap,
				ahc_tarअ_लोmd_offset(ahc, ahc->tqinfअगरonext),
				माप(काष्ठा target_cmd),
				BUS_DMASYNC_PREREAD);
		ahc->tqinfअगरonext++;

		/*
		 * Lazily update our position in the target mode incoming
		 * command queue as seen by the sequencer.
		 */
		अगर ((ahc->tqinfअगरonext & (HOST_TQINPOS - 1)) == 1) अणु
			अगर ((ahc->features & AHC_HS_MAILBOX) != 0) अणु
				u_पूर्णांक hs_mailbox;

				hs_mailbox = ahc_inb(ahc, HS_MAILBOX);
				hs_mailbox &= ~HOST_TQINPOS;
				hs_mailbox |= ahc->tqinfअगरonext & HOST_TQINPOS;
				ahc_outb(ahc, HS_MAILBOX, hs_mailbox);
			पूर्ण अन्यथा अणु
				अगर (!छोड़ोd)
					ahc_छोड़ो(ahc);
				ahc_outb(ahc, KERNEL_TQINPOS,
					 ahc->tqinfअगरonext & HOST_TQINPOS);
				अगर (!छोड़ोd)
					ahc_unछोड़ो(ahc);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
ahc_handle_target_cmd(काष्ठा ahc_softc *ahc, काष्ठा target_cmd *cmd)
अणु
	काष्ठा	  ahc_पंचांगode_tstate *tstate;
	काष्ठा	  ahc_पंचांगode_lstate *lstate;
	काष्ठा	  ccb_accept_tio *atio;
	uपूर्णांक8_t *byte;
	पूर्णांक	  initiator;
	पूर्णांक	  target;
	पूर्णांक	  lun;

	initiator = SCSIID_TARGET(ahc, cmd->scsiid);
	target = SCSIID_OUR_ID(cmd->scsiid);
	lun    = (cmd->identअगरy & MSG_IDENTIFY_LUNMASK);

	byte = cmd->bytes;
	tstate = ahc->enabled_tarमाला_लो[target];
	lstate = शून्य;
	अगर (tstate != शून्य)
		lstate = tstate->enabled_luns[lun];

	/*
	 * Commands क्रम disabled luns go to the black hole driver.
	 */
	अगर (lstate == शून्य)
		lstate = ahc->black_hole;

	atio = (काष्ठा ccb_accept_tio*)SLIST_FIRST(&lstate->accept_tios);
	अगर (atio == शून्य) अणु
		ahc->flags |= AHC_TQINFIFO_BLOCKED;
		/*
		 * Wait क्रम more ATIOs from the peripheral driver क्रम this lun.
		 */
		अगर (bootverbose)
			prपूर्णांकk("%s: ATIOs exhausted\n", ahc_name(ahc));
		वापस (1);
	पूर्ण अन्यथा
		ahc->flags &= ~AHC_TQINFIFO_BLOCKED;
#अगर 0
	prपूर्णांकk("Incoming command from %d for %d:%d%s\n",
	       initiator, target, lun,
	       lstate == ahc->black_hole ? "(Black Holed)" : "");
#पूर्ण_अगर
	SLIST_REMOVE_HEAD(&lstate->accept_tios, sim_links.sle);

	अगर (lstate == ahc->black_hole) अणु
		/* Fill in the wildcards */
		atio->ccb_h.target_id = target;
		atio->ccb_h.target_lun = lun;
	पूर्ण

	/*
	 * Package it up and send it off to
	 * whomever has this lun enabled.
	 */
	atio->sense_len = 0;
	atio->init_id = initiator;
	अगर (byte[0] != 0xFF) अणु
		/* Tag was included */
		atio->tag_action = *byte++;
		atio->tag_id = *byte++;
		atio->ccb_h.flags = CAM_TAG_ACTION_VALID;
	पूर्ण अन्यथा अणु
		atio->ccb_h.flags = 0;
	पूर्ण
	byte++;

	/* Okay.  Now determine the cdb size based on the command code */
	चयन (*byte >> CMD_GROUP_CODE_SHIFT) अणु
	हाल 0:
		atio->cdb_len = 6;
		अवरोध;
	हाल 1:
	हाल 2:
		atio->cdb_len = 10;
		अवरोध;
	हाल 4:
		atio->cdb_len = 16;
		अवरोध;
	हाल 5:
		atio->cdb_len = 12;
		अवरोध;
	हाल 3:
	शेष:
		/* Only copy the opcode. */
		atio->cdb_len = 1;
		prपूर्णांकk("Reserved or VU command code type encountered\n");
		अवरोध;
	पूर्ण

	स_नकल(atio->cdb_io.cdb_bytes, byte, atio->cdb_len);

	atio->ccb_h.status |= CAM_CDB_RECVD;

	अगर ((cmd->identअगरy & MSG_IDENTIFY_DISCFLAG) == 0) अणु
		/*
		 * We weren't allowed to disconnect.
		 * We're hanging on the bus until a
		 * जारी target I/O comes in response
		 * to this accept tio.
		 */
#अगर 0
		prपूर्णांकk("Received Immediate Command %d:%d:%d - %p\n",
		       initiator, target, lun, ahc->pending_device);
#पूर्ण_अगर
		ahc->pending_device = lstate;
		ahc_मुक्तze_ccb((जोड़ ccb *)atio);
		atio->ccb_h.flags |= CAM_DIS_DISCONNECT;
	पूर्ण
	xpt_करोne((जोड़ ccb*)atio);
	वापस (0);
पूर्ण

#पूर्ण_अगर
