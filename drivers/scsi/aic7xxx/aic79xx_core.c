<शैली गुरु>
/*
 * Core routines and tables shareable across OS platक्रमms.
 *
 * Copyright (c) 1994-2002 Justin T. Gibbs.
 * Copyright (c) 2000-2003 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/aic7xxx/aic79xx.c#250 $
 */

#समावेश "aic79xx_osm.h"
#समावेश "aic79xx_inline.h"
#समावेश "aicasm/aicasm_insformat.h"

/***************************** Lookup Tables **********************************/
अटल स्थिर अक्षर *स्थिर ahd_chip_names[] =
अणु
	"NONE",
	"aic7901",
	"aic7902",
	"aic7901A"
पूर्ण;

/*
 * Hardware error codes.
 */
काष्ठा ahd_hard_error_entry अणु
	uपूर्णांक8_t त्रुटि_सं;
	स्थिर अक्षर *errmesg;
पूर्ण;

अटल स्थिर काष्ठा ahd_hard_error_entry ahd_hard_errors[] = अणु
	अणु DSCTMOUT,	"Discard Timer has timed out" पूर्ण,
	अणु ILLOPCODE,	"Illegal Opcode in sequencer program" पूर्ण,
	अणु SQPARERR,	"Sequencer Parity Error" पूर्ण,
	अणु DPARERR,	"Data-path Parity Error" पूर्ण,
	अणु MPARERR,	"Scratch or SCB Memory Parity Error" पूर्ण,
	अणु CIOPARERR,	"CIOBUS Parity Error" पूर्ण,
पूर्ण;
अटल स्थिर u_पूर्णांक num_errors = ARRAY_SIZE(ahd_hard_errors);

अटल स्थिर काष्ठा ahd_phase_table_entry ahd_phase_table[] =
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
अटल स्थिर u_पूर्णांक num_phases = ARRAY_SIZE(ahd_phase_table) - 1;

/* Our Sequencer Program */
#समावेश "aic79xx_seq.h"

/**************************** Function Declarations ***************************/
अटल व्योम		ahd_handle_transmission_error(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_handle_lqiphase_error(काष्ठा ahd_softc *ahd,
						  u_पूर्णांक lqistat1);
अटल पूर्णांक		ahd_handle_pkt_busमुक्त(काष्ठा ahd_softc *ahd,
					       u_पूर्णांक busमुक्तसमय);
अटल पूर्णांक		ahd_handle_nonpkt_busमुक्त(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_handle_proto_violation(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_क्रमce_renegotiation(काष्ठा ahd_softc *ahd,
						काष्ठा ahd_devinfo *devinfo);

अटल काष्ठा ahd_पंचांगode_tstate*
			ahd_alloc_tstate(काष्ठा ahd_softc *ahd,
					 u_पूर्णांक scsi_id, अक्षर channel);
#अगर_घोषित AHD_TARGET_MODE
अटल व्योम		ahd_मुक्त_tstate(काष्ठा ahd_softc *ahd,
					u_पूर्णांक scsi_id, अक्षर channel, पूर्णांक क्रमce);
#पूर्ण_अगर
अटल व्योम		ahd_devlimited_syncrate(काष्ठा ahd_softc *ahd,
						काष्ठा ahd_initiator_tinfo *,
						u_पूर्णांक *period,
						u_पूर्णांक *ppr_options,
						role_t role);
अटल व्योम		ahd_update_neg_table(काष्ठा ahd_softc *ahd,
					     काष्ठा ahd_devinfo *devinfo,
					     काष्ठा ahd_transinfo *tinfo);
अटल व्योम		ahd_update_pending_scbs(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_fetch_devinfo(काष्ठा ahd_softc *ahd,
					  काष्ठा ahd_devinfo *devinfo);
अटल व्योम		ahd_scb_devinfo(काष्ठा ahd_softc *ahd,
					काष्ठा ahd_devinfo *devinfo,
					काष्ठा scb *scb);
अटल व्योम		ahd_setup_initiator_msgout(काष्ठा ahd_softc *ahd,
						   काष्ठा ahd_devinfo *devinfo,
						   काष्ठा scb *scb);
अटल व्योम		ahd_build_transfer_msg(काष्ठा ahd_softc *ahd,
					       काष्ठा ahd_devinfo *devinfo);
अटल व्योम		ahd_स्थिरruct_sdtr(काष्ठा ahd_softc *ahd,
					   काष्ठा ahd_devinfo *devinfo,
					   u_पूर्णांक period, u_पूर्णांक offset);
अटल व्योम		ahd_स्थिरruct_wdtr(काष्ठा ahd_softc *ahd,
					   काष्ठा ahd_devinfo *devinfo,
					   u_पूर्णांक bus_width);
अटल व्योम		ahd_स्थिरruct_ppr(काष्ठा ahd_softc *ahd,
					  काष्ठा ahd_devinfo *devinfo,
					  u_पूर्णांक period, u_पूर्णांक offset,
					  u_पूर्णांक bus_width, u_पूर्णांक ppr_options);
अटल व्योम		ahd_clear_msg_state(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_handle_message_phase(काष्ठा ahd_softc *ahd);
प्रकार क्रमागत अणु
	AHDMSG_1B,
	AHDMSG_2B,
	AHDMSG_EXT
पूर्ण ahd_msgtype;
अटल पूर्णांक		ahd_sent_msg(काष्ठा ahd_softc *ahd, ahd_msgtype type,
				     u_पूर्णांक msgval, पूर्णांक full);
अटल पूर्णांक		ahd_parse_msg(काष्ठा ahd_softc *ahd,
				      काष्ठा ahd_devinfo *devinfo);
अटल पूर्णांक		ahd_handle_msg_reject(काष्ठा ahd_softc *ahd,
					      काष्ठा ahd_devinfo *devinfo);
अटल व्योम		ahd_handle_ign_wide_residue(काष्ठा ahd_softc *ahd,
						काष्ठा ahd_devinfo *devinfo);
अटल व्योम		ahd_reinitialize_dataptrs(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_handle_devreset(काष्ठा ahd_softc *ahd,
					    काष्ठा ahd_devinfo *devinfo,
					    u_पूर्णांक lun, cam_status status,
					    अक्षर *message, पूर्णांक verbose_level);
#अगर_घोषित AHD_TARGET_MODE
अटल व्योम		ahd_setup_target_msgin(काष्ठा ahd_softc *ahd,
					       काष्ठा ahd_devinfo *devinfo,
					       काष्ठा scb *scb);
#पूर्ण_अगर

अटल u_पूर्णांक		ahd_sglist_size(काष्ठा ahd_softc *ahd);
अटल u_पूर्णांक		ahd_sglist_allocsize(काष्ठा ahd_softc *ahd);
अटल bus_dmamap_callback_t
			ahd_dmamap_cb;
अटल व्योम		ahd_initialize_hscbs(काष्ठा ahd_softc *ahd);
अटल पूर्णांक		ahd_init_scbdata(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_fini_scbdata(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_setup_iocell_workaround(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_iocell_first_selection(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_add_col_list(काष्ठा ahd_softc *ahd,
					 काष्ठा scb *scb, u_पूर्णांक col_idx);
अटल व्योम		ahd_rem_col_list(काष्ठा ahd_softc *ahd,
					 काष्ठा scb *scb);
अटल व्योम		ahd_chip_init(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_qinfअगरo_requeue(काष्ठा ahd_softc *ahd,
					    काष्ठा scb *prev_scb,
					    काष्ठा scb *scb);
अटल पूर्णांक		ahd_qinfअगरo_count(काष्ठा ahd_softc *ahd);
अटल पूर्णांक		ahd_search_scb_list(काष्ठा ahd_softc *ahd, पूर्णांक target,
					    अक्षर channel, पूर्णांक lun, u_पूर्णांक tag,
					    role_t role, uपूर्णांक32_t status,
					    ahd_search_action action,
					    u_पूर्णांक *list_head, u_पूर्णांक *list_tail,
					    u_पूर्णांक tid);
अटल व्योम		ahd_stitch_tid_list(काष्ठा ahd_softc *ahd,
					    u_पूर्णांक tid_prev, u_पूर्णांक tid_cur,
					    u_पूर्णांक tid_next);
अटल व्योम		ahd_add_scb_to_मुक्त_list(काष्ठा ahd_softc *ahd,
						 u_पूर्णांक scbid);
अटल u_पूर्णांक		ahd_rem_wscb(काष्ठा ahd_softc *ahd, u_पूर्णांक scbid,
				     u_पूर्णांक prev, u_पूर्णांक next, u_पूर्णांक tid);
अटल व्योम		ahd_reset_current_bus(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_stat_समयr(काष्ठा समयr_list *t);
#अगर_घोषित AHD_DUMP_SEQ
अटल व्योम		ahd_dumpseq(काष्ठा ahd_softc *ahd);
#पूर्ण_अगर
अटल व्योम		ahd_loadseq(काष्ठा ahd_softc *ahd);
अटल पूर्णांक		ahd_check_patch(काष्ठा ahd_softc *ahd,
					स्थिर काष्ठा patch **start_patch,
					u_पूर्णांक start_instr, u_पूर्णांक *skip_addr);
अटल u_पूर्णांक		ahd_resolve_seqaddr(काष्ठा ahd_softc *ahd,
					    u_पूर्णांक address);
अटल व्योम		ahd_करोwnload_instr(काष्ठा ahd_softc *ahd,
					   u_पूर्णांक instrptr, uपूर्णांक8_t *dस्थिरs);
अटल पूर्णांक		ahd_probe_stack_size(काष्ठा ahd_softc *ahd);
अटल पूर्णांक		ahd_scb_active_in_fअगरo(काष्ठा ahd_softc *ahd,
					       काष्ठा scb *scb);
अटल व्योम		ahd_run_data_fअगरo(काष्ठा ahd_softc *ahd,
					  काष्ठा scb *scb);

#अगर_घोषित AHD_TARGET_MODE
अटल व्योम		ahd_queue_lstate_event(काष्ठा ahd_softc *ahd,
					       काष्ठा ahd_पंचांगode_lstate *lstate,
					       u_पूर्णांक initiator_id,
					       u_पूर्णांक event_type,
					       u_पूर्णांक event_arg);
अटल व्योम		ahd_update_scsiid(काष्ठा ahd_softc *ahd,
					  u_पूर्णांक targid_mask);
अटल पूर्णांक		ahd_handle_target_cmd(काष्ठा ahd_softc *ahd,
					      काष्ठा target_cmd *cmd);
#पूर्ण_अगर

अटल पूर्णांक		ahd_पात_scbs(काष्ठा ahd_softc *ahd, पूर्णांक target,
				       अक्षर channel, पूर्णांक lun, u_पूर्णांक tag,
				       role_t role, uपूर्णांक32_t status);
अटल व्योम		ahd_alloc_scbs(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_busy_tcl(काष्ठा ahd_softc *ahd, u_पूर्णांक tcl,
				     u_पूर्णांक scbid);
अटल व्योम		ahd_calc_residual(काष्ठा ahd_softc *ahd,
					  काष्ठा scb *scb);
अटल व्योम		ahd_clear_critical_section(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_clear_पूर्णांकstat(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_enable_coalescing(काष्ठा ahd_softc *ahd,
					      पूर्णांक enable);
अटल u_पूर्णांक		ahd_find_busy_tcl(काष्ठा ahd_softc *ahd, u_पूर्णांक tcl);
अटल व्योम		ahd_मुक्तze_devq(काष्ठा ahd_softc *ahd,
					काष्ठा scb *scb);
अटल व्योम		ahd_handle_scb_status(काष्ठा ahd_softc *ahd,
					      काष्ठा scb *scb);
अटल स्थिर काष्ठा ahd_phase_table_entry* ahd_lookup_phase_entry(पूर्णांक phase);
अटल व्योम		ahd_shutकरोwn(व्योम *arg);
अटल व्योम		ahd_update_coalescing_values(काष्ठा ahd_softc *ahd,
						     u_पूर्णांक समयr,
						     u_पूर्णांक maxcmds,
						     u_पूर्णांक mincmds);
अटल पूर्णांक		ahd_verअगरy_vpd_cksum(काष्ठा vpd_config *vpd);
अटल पूर्णांक		ahd_रुको_seeprom(काष्ठा ahd_softc *ahd);
अटल पूर्णांक		ahd_match_scb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb,
				      पूर्णांक target, अक्षर channel, पूर्णांक lun,
				      u_पूर्णांक tag, role_t role);

अटल व्योम		ahd_reset_cmds_pending(काष्ठा ahd_softc *ahd);

/*************************** Interrupt Services *******************************/
अटल व्योम		ahd_run_qoutfअगरo(काष्ठा ahd_softc *ahd);
#अगर_घोषित AHD_TARGET_MODE
अटल व्योम		ahd_run_tqinfअगरo(काष्ठा ahd_softc *ahd, पूर्णांक छोड़ोd);
#पूर्ण_अगर
अटल व्योम		ahd_handle_hwerrपूर्णांक(काष्ठा ahd_softc *ahd);
अटल व्योम		ahd_handle_seqपूर्णांक(काष्ठा ahd_softc *ahd, u_पूर्णांक पूर्णांकstat);
अटल व्योम		ahd_handle_scsiपूर्णांक(काष्ठा ahd_softc *ahd,
					   u_पूर्णांक पूर्णांकstat);

/************************ Sequencer Execution Control *************************/
व्योम
ahd_set_modes(काष्ठा ahd_softc *ahd, ahd_mode src, ahd_mode dst)
अणु
	अगर (ahd->src_mode == src && ahd->dst_mode == dst)
		वापस;
#अगर_घोषित AHD_DEBUG
	अगर (ahd->src_mode == AHD_MODE_UNKNOWN
	 || ahd->dst_mode == AHD_MODE_UNKNOWN)
		panic("Setting mode prior to saving it.\n");
	अगर ((ahd_debug & AHD_SHOW_MODEPTR) != 0)
		prपूर्णांकk("%s: Setting mode 0x%x\n", ahd_name(ahd),
		       ahd_build_mode_state(ahd, src, dst));
#पूर्ण_अगर
	ahd_outb(ahd, MODE_PTR, ahd_build_mode_state(ahd, src, dst));
	ahd->src_mode = src;
	ahd->dst_mode = dst;
पूर्ण

अटल व्योम
ahd_update_modes(काष्ठा ahd_softc *ahd)
अणु
	ahd_mode_state mode_ptr;
	ahd_mode src;
	ahd_mode dst;

	mode_ptr = ahd_inb(ahd, MODE_PTR);
#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_MODEPTR) != 0)
		prपूर्णांकk("Reading mode 0x%x\n", mode_ptr);
#पूर्ण_अगर
	ahd_extract_mode_state(ahd, mode_ptr, &src, &dst);
	ahd_known_modes(ahd, src, dst);
पूर्ण

अटल व्योम
ahd_निश्चित_modes(काष्ठा ahd_softc *ahd, ahd_mode srcmode,
		 ahd_mode dsपंचांगode, स्थिर अक्षर *file, पूर्णांक line)
अणु
#अगर_घोषित AHD_DEBUG
	अगर ((srcmode & AHD_MK_MSK(ahd->src_mode)) == 0
	 || (dsपंचांगode & AHD_MK_MSK(ahd->dst_mode)) == 0) अणु
		panic("%s:%s:%d: Mode assertion failed.\n",
		       ahd_name(ahd), file, line);
	पूर्ण
#पूर्ण_अगर
पूर्ण

#घोषणा AHD_ASSERT_MODES(ahd, source, dest) \
	ahd_निश्चित_modes(ahd, source, dest, __खाता__, __LINE__);

ahd_mode_state
ahd_save_modes(काष्ठा ahd_softc *ahd)
अणु
	अगर (ahd->src_mode == AHD_MODE_UNKNOWN
	 || ahd->dst_mode == AHD_MODE_UNKNOWN)
		ahd_update_modes(ahd);

	वापस (ahd_build_mode_state(ahd, ahd->src_mode, ahd->dst_mode));
पूर्ण

व्योम
ahd_restore_modes(काष्ठा ahd_softc *ahd, ahd_mode_state state)
अणु
	ahd_mode src;
	ahd_mode dst;

	ahd_extract_mode_state(ahd, state, &src, &dst);
	ahd_set_modes(ahd, src, dst);
पूर्ण

/*
 * Determine whether the sequencer has halted code execution.
 * Returns non-zero status अगर the sequencer is stopped.
 */
पूर्णांक
ahd_is_छोड़ोd(काष्ठा ahd_softc *ahd)
अणु
	वापस ((ahd_inb(ahd, HCNTRL) & PAUSE) != 0);
पूर्ण

/*
 * Request that the sequencer stop and रुको, indefinitely, क्रम it
 * to stop.  The sequencer will only acknowledge that it is छोड़ोd
 * once it has reached an inकाष्ठाion boundary and PAUSEDIS is
 * cleared in the SEQCTL रेजिस्टर.  The sequencer may use PAUSEDIS
 * क्रम critical sections.
 */
व्योम
ahd_छोड़ो(काष्ठा ahd_softc *ahd)
अणु
	ahd_outb(ahd, HCNTRL, ahd->छोड़ो);

	/*
	 * Since the sequencer can disable pausing in a critical section, we
	 * must loop until it actually stops.
	 */
	जबतक (ahd_is_छोड़ोd(ahd) == 0)
		;
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
ahd_unछोड़ो(काष्ठा ahd_softc *ahd)
अणु
	/*
	 * Automatically restore our modes to those saved
	 * prior to the first change of the mode.
	 */
	अगर (ahd->saved_src_mode != AHD_MODE_UNKNOWN
	 && ahd->saved_dst_mode != AHD_MODE_UNKNOWN) अणु
		अगर ((ahd->flags & AHD_UPDATE_PEND_CMDS) != 0)
			ahd_reset_cmds_pending(ahd);
		ahd_set_modes(ahd, ahd->saved_src_mode, ahd->saved_dst_mode);
	पूर्ण

	अगर ((ahd_inb(ahd, INTSTAT) & ~CMDCMPLT) == 0)
		ahd_outb(ahd, HCNTRL, ahd->unछोड़ो);

	ahd_known_modes(ahd, AHD_MODE_UNKNOWN, AHD_MODE_UNKNOWN);
पूर्ण

/*********************** Scatter Gather List Handling *************************/
व्योम *
ahd_sg_setup(काष्ठा ahd_softc *ahd, काष्ठा scb *scb,
	     व्योम *sgptr, dma_addr_t addr, bus_माप_प्रकार len, पूर्णांक last)
अणु
	scb->sg_count++;
	अगर (माप(dma_addr_t) > 4
	 && (ahd->flags & AHD_64BIT_ADDRESSING) != 0) अणु
		काष्ठा ahd_dma64_seg *sg;

		sg = (काष्ठा ahd_dma64_seg *)sgptr;
		sg->addr = ahd_htole64(addr);
		sg->len = ahd_htole32(len | (last ? AHD_DMA_LAST_SEG : 0));
		वापस (sg + 1);
	पूर्ण अन्यथा अणु
		काष्ठा ahd_dma_seg *sg;

		sg = (काष्ठा ahd_dma_seg *)sgptr;
		sg->addr = ahd_htole32(addr & 0xFFFFFFFF);
		sg->len = ahd_htole32(len | ((addr >> 8) & 0x7F000000)
				    | (last ? AHD_DMA_LAST_SEG : 0));
		वापस (sg + 1);
	पूर्ण
पूर्ण

अटल व्योम
ahd_setup_scb_common(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	/* XXX Handle target mode SCBs. */
	scb->crc_retry_count = 0;
	अगर ((scb->flags & SCB_PACKETIZED) != 0) अणु
		/* XXX what about ACA??  It is type 4, but TAG_TYPE == 0x3. */
		scb->hscb->task_attribute = scb->hscb->control & SCB_TAG_TYPE;
	पूर्ण अन्यथा अणु
		अगर (ahd_get_transfer_length(scb) & 0x01)
			scb->hscb->task_attribute = SCB_XFERLEN_ODD;
		अन्यथा
			scb->hscb->task_attribute = 0;
	पूर्ण

	अगर (scb->hscb->cdb_len <= MAX_CDB_LEN_WITH_SENSE_ADDR
	 || (scb->hscb->cdb_len & SCB_CDB_LEN_PTR) != 0)
		scb->hscb->shared_data.idata.cdb_plus_saddr.sense_addr =
		    ahd_htole32(scb->sense_busaddr);
पूर्ण

अटल व्योम
ahd_setup_data_scb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	/*
	 * Copy the first SG पूर्णांकo the "current" data ponter area.
	 */
	अगर ((ahd->flags & AHD_64BIT_ADDRESSING) != 0) अणु
		काष्ठा ahd_dma64_seg *sg;

		sg = (काष्ठा ahd_dma64_seg *)scb->sg_list;
		scb->hscb->dataptr = sg->addr;
		scb->hscb->datacnt = sg->len;
	पूर्ण अन्यथा अणु
		काष्ठा ahd_dma_seg *sg;
		uपूर्णांक32_t *dataptr_words;

		sg = (काष्ठा ahd_dma_seg *)scb->sg_list;
		dataptr_words = (uपूर्णांक32_t*)&scb->hscb->dataptr;
		dataptr_words[0] = sg->addr;
		dataptr_words[1] = 0;
		अगर ((ahd->flags & AHD_39BIT_ADDRESSING) != 0) अणु
			uपूर्णांक64_t high_addr;

			high_addr = ahd_le32toh(sg->len) & 0x7F000000;
			scb->hscb->dataptr |= ahd_htole64(high_addr << 8);
		पूर्ण
		scb->hscb->datacnt = sg->len;
	पूर्ण
	/*
	 * Note where to find the SG entries in bus space.
	 * We also set the full residual flag which the
	 * sequencer will clear as soon as a data transfer
	 * occurs.
	 */
	scb->hscb->sgptr = ahd_htole32(scb->sg_list_busaddr|SG_FULL_RESID);
पूर्ण

अटल व्योम
ahd_setup_noxfer_scb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	scb->hscb->sgptr = ahd_htole32(SG_LIST_शून्य);
	scb->hscb->dataptr = 0;
	scb->hscb->datacnt = 0;
पूर्ण

/************************** Memory mapping routines ***************************/
अटल व्योम *
ahd_sg_bus_to_virt(काष्ठा ahd_softc *ahd, काष्ठा scb *scb, uपूर्णांक32_t sg_busaddr)
अणु
	dma_addr_t sg_offset;

	/* sg_list_phys poपूर्णांकs to entry 1, not 0 */
	sg_offset = sg_busaddr - (scb->sg_list_busaddr - ahd_sg_size(ahd));
	वापस ((uपूर्णांक8_t *)scb->sg_list + sg_offset);
पूर्ण

अटल uपूर्णांक32_t
ahd_sg_virt_to_bus(काष्ठा ahd_softc *ahd, काष्ठा scb *scb, व्योम *sg)
अणु
	dma_addr_t sg_offset;

	/* sg_list_phys poपूर्णांकs to entry 1, not 0 */
	sg_offset = ((uपूर्णांक8_t *)sg - (uपूर्णांक8_t *)scb->sg_list)
		  - ahd_sg_size(ahd);

	वापस (scb->sg_list_busaddr + sg_offset);
पूर्ण

अटल व्योम
ahd_sync_scb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb, पूर्णांक op)
अणु
	ahd_dmamap_sync(ahd, ahd->scb_data.hscb_dmat,
			scb->hscb_map->dmamap,
			/*offset*/(uपूर्णांक8_t*)scb->hscb - scb->hscb_map->vaddr,
			/*len*/माप(*scb->hscb), op);
पूर्ण

व्योम
ahd_sync_sglist(काष्ठा ahd_softc *ahd, काष्ठा scb *scb, पूर्णांक op)
अणु
	अगर (scb->sg_count == 0)
		वापस;

	ahd_dmamap_sync(ahd, ahd->scb_data.sg_dmat,
			scb->sg_map->dmamap,
			/*offset*/scb->sg_list_busaddr - ahd_sg_size(ahd),
			/*len*/ahd_sg_size(ahd) * scb->sg_count, op);
पूर्ण

अटल व्योम
ahd_sync_sense(काष्ठा ahd_softc *ahd, काष्ठा scb *scb, पूर्णांक op)
अणु
	ahd_dmamap_sync(ahd, ahd->scb_data.sense_dmat,
			scb->sense_map->dmamap,
			/*offset*/scb->sense_busaddr,
			/*len*/AHD_SENSE_बफ_मानE, op);
पूर्ण

#अगर_घोषित AHD_TARGET_MODE
अटल uपूर्णांक32_t
ahd_tarअ_लोmd_offset(काष्ठा ahd_softc *ahd, u_पूर्णांक index)
अणु
	वापस (((uपूर्णांक8_t *)&ahd->tarअ_लोmds[index])
	       - (uपूर्णांक8_t *)ahd->qoutfअगरo);
पूर्ण
#पूर्ण_अगर

/*********************** Miscellaneous Support Functions ***********************/
/*
 * Return poपूर्णांकers to the transfer negotiation inक्रमmation
 * क्रम the specअगरied our_id/remote_id pair.
 */
काष्ठा ahd_initiator_tinfo *
ahd_fetch_transinfo(काष्ठा ahd_softc *ahd, अक्षर channel, u_पूर्णांक our_id,
		    u_पूर्णांक remote_id, काष्ठा ahd_पंचांगode_tstate **tstate)
अणु
	/*
	 * Transfer data काष्ठाures are stored from the perspective
	 * of the target role.  Since the parameters क्रम a connection
	 * in the initiator role to a given target are the same as
	 * when the roles are reversed, we pretend we are the target.
	 */
	अगर (channel == 'B')
		our_id += 8;
	*tstate = ahd->enabled_tarमाला_लो[our_id];
	वापस (&(*tstate)->transinfo[remote_id]);
पूर्ण

uपूर्णांक16_t
ahd_inw(काष्ठा ahd_softc *ahd, u_पूर्णांक port)
अणु
	/*
	 * Read high byte first as some रेजिस्टरs increment
	 * or have other side effects when the low byte is
	 * पढ़ो.
	 */
	uपूर्णांक16_t r = ahd_inb(ahd, port+1) << 8;
	वापस r | ahd_inb(ahd, port);
पूर्ण

व्योम
ahd_outw(काष्ठा ahd_softc *ahd, u_पूर्णांक port, u_पूर्णांक value)
अणु
	/*
	 * Write low byte first to accommodate रेजिस्टरs
	 * such as PRGMCNT where the order maters.
	 */
	ahd_outb(ahd, port, value & 0xFF);
	ahd_outb(ahd, port+1, (value >> 8) & 0xFF);
पूर्ण

uपूर्णांक32_t
ahd_inl(काष्ठा ahd_softc *ahd, u_पूर्णांक port)
अणु
	वापस ((ahd_inb(ahd, port))
	      | (ahd_inb(ahd, port+1) << 8)
	      | (ahd_inb(ahd, port+2) << 16)
	      | (ahd_inb(ahd, port+3) << 24));
पूर्ण

व्योम
ahd_outl(काष्ठा ahd_softc *ahd, u_पूर्णांक port, uपूर्णांक32_t value)
अणु
	ahd_outb(ahd, port, (value) & 0xFF);
	ahd_outb(ahd, port+1, ((value) >> 8) & 0xFF);
	ahd_outb(ahd, port+2, ((value) >> 16) & 0xFF);
	ahd_outb(ahd, port+3, ((value) >> 24) & 0xFF);
पूर्ण

uपूर्णांक64_t
ahd_inq(काष्ठा ahd_softc *ahd, u_पूर्णांक port)
अणु
	वापस ((ahd_inb(ahd, port))
	      | (ahd_inb(ahd, port+1) << 8)
	      | (ahd_inb(ahd, port+2) << 16)
	      | (ahd_inb(ahd, port+3) << 24)
	      | (((uपूर्णांक64_t)ahd_inb(ahd, port+4)) << 32)
	      | (((uपूर्णांक64_t)ahd_inb(ahd, port+5)) << 40)
	      | (((uपूर्णांक64_t)ahd_inb(ahd, port+6)) << 48)
	      | (((uपूर्णांक64_t)ahd_inb(ahd, port+7)) << 56));
पूर्ण

व्योम
ahd_outq(काष्ठा ahd_softc *ahd, u_पूर्णांक port, uपूर्णांक64_t value)
अणु
	ahd_outb(ahd, port, value & 0xFF);
	ahd_outb(ahd, port+1, (value >> 8) & 0xFF);
	ahd_outb(ahd, port+2, (value >> 16) & 0xFF);
	ahd_outb(ahd, port+3, (value >> 24) & 0xFF);
	ahd_outb(ahd, port+4, (value >> 32) & 0xFF);
	ahd_outb(ahd, port+5, (value >> 40) & 0xFF);
	ahd_outb(ahd, port+6, (value >> 48) & 0xFF);
	ahd_outb(ahd, port+7, (value >> 56) & 0xFF);
पूर्ण

u_पूर्णांक
ahd_get_scbptr(काष्ठा ahd_softc *ahd)
अणु
	AHD_ASSERT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	वापस (ahd_inb(ahd, SCBPTR) | (ahd_inb(ahd, SCBPTR + 1) << 8));
पूर्ण

व्योम
ahd_set_scbptr(काष्ठा ahd_softc *ahd, u_पूर्णांक scbptr)
अणु
	AHD_ASSERT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	ahd_outb(ahd, SCBPTR, scbptr & 0xFF);
	ahd_outb(ahd, SCBPTR+1, (scbptr >> 8) & 0xFF);
पूर्ण

#अगर 0 /* unused */
अटल u_पूर्णांक
ahd_get_hnscb_qoff(काष्ठा ahd_softc *ahd)
अणु
	वापस (ahd_inw_atomic(ahd, HNSCB_QOFF));
पूर्ण
#पूर्ण_अगर

अटल व्योम
ahd_set_hnscb_qoff(काष्ठा ahd_softc *ahd, u_पूर्णांक value)
अणु
	ahd_outw_atomic(ahd, HNSCB_QOFF, value);
पूर्ण

#अगर 0 /* unused */
अटल u_पूर्णांक
ahd_get_hescb_qoff(काष्ठा ahd_softc *ahd)
अणु
	वापस (ahd_inb(ahd, HESCB_QOFF));
पूर्ण
#पूर्ण_अगर

अटल व्योम
ahd_set_hescb_qoff(काष्ठा ahd_softc *ahd, u_पूर्णांक value)
अणु
	ahd_outb(ahd, HESCB_QOFF, value);
पूर्ण

अटल u_पूर्णांक
ahd_get_snscb_qoff(काष्ठा ahd_softc *ahd)
अणु
	u_पूर्णांक oldvalue;

	AHD_ASSERT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	oldvalue = ahd_inw(ahd, SNSCB_QOFF);
	ahd_outw(ahd, SNSCB_QOFF, oldvalue);
	वापस (oldvalue);
पूर्ण

अटल व्योम
ahd_set_snscb_qoff(काष्ठा ahd_softc *ahd, u_पूर्णांक value)
अणु
	AHD_ASSERT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	ahd_outw(ahd, SNSCB_QOFF, value);
पूर्ण

#अगर 0 /* unused */
अटल u_पूर्णांक
ahd_get_sescb_qoff(काष्ठा ahd_softc *ahd)
अणु
	AHD_ASSERT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	वापस (ahd_inb(ahd, SESCB_QOFF));
पूर्ण
#पूर्ण_अगर

अटल व्योम
ahd_set_sescb_qoff(काष्ठा ahd_softc *ahd, u_पूर्णांक value)
अणु
	AHD_ASSERT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	ahd_outb(ahd, SESCB_QOFF, value);
पूर्ण

#अगर 0 /* unused */
अटल u_पूर्णांक
ahd_get_sdscb_qoff(काष्ठा ahd_softc *ahd)
अणु
	AHD_ASSERT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	वापस (ahd_inb(ahd, SDSCB_QOFF) | (ahd_inb(ahd, SDSCB_QOFF + 1) << 8));
पूर्ण
#पूर्ण_अगर

अटल व्योम
ahd_set_sdscb_qoff(काष्ठा ahd_softc *ahd, u_पूर्णांक value)
अणु
	AHD_ASSERT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	ahd_outb(ahd, SDSCB_QOFF, value & 0xFF);
	ahd_outb(ahd, SDSCB_QOFF+1, (value >> 8) & 0xFF);
पूर्ण

u_पूर्णांक
ahd_inb_scbram(काष्ठा ahd_softc *ahd, u_पूर्णांक offset)
अणु
	u_पूर्णांक value;

	/*
	 * Workaround PCI-X Rev A. hardware bug.
	 * After a host पढ़ो of SCB memory, the chip
	 * may become confused पूर्णांकo thinking prefetch
	 * was required.  This starts the discard समयr
	 * running and can cause an unexpected discard
	 * समयr पूर्णांकerrupt.  The work around is to पढ़ो
	 * a normal रेजिस्टर prior to the exhaustion of
	 * the discard समयr.  The mode poपूर्णांकer रेजिस्टर
	 * has no side effects and so serves well क्रम
	 * this purpose.
	 *
	 * Razor #528
	 */
	value = ahd_inb(ahd, offset);
	अगर ((ahd->bugs & AHD_PCIX_SCBRAM_RD_BUG) != 0)
		ahd_inb(ahd, MODE_PTR);
	वापस (value);
पूर्ण

u_पूर्णांक
ahd_inw_scbram(काष्ठा ahd_softc *ahd, u_पूर्णांक offset)
अणु
	वापस (ahd_inb_scbram(ahd, offset)
	      | (ahd_inb_scbram(ahd, offset+1) << 8));
पूर्ण

अटल uपूर्णांक32_t
ahd_inl_scbram(काष्ठा ahd_softc *ahd, u_पूर्णांक offset)
अणु
	वापस (ahd_inw_scbram(ahd, offset)
	      | (ahd_inw_scbram(ahd, offset+2) << 16));
पूर्ण

अटल uपूर्णांक64_t
ahd_inq_scbram(काष्ठा ahd_softc *ahd, u_पूर्णांक offset)
अणु
	वापस (ahd_inl_scbram(ahd, offset)
	      | ((uपूर्णांक64_t)ahd_inl_scbram(ahd, offset+4)) << 32);
पूर्ण

काष्ठा scb *
ahd_lookup_scb(काष्ठा ahd_softc *ahd, u_पूर्णांक tag)
अणु
	काष्ठा scb* scb;

	अगर (tag >= AHD_SCB_MAX)
		वापस (शून्य);
	scb = ahd->scb_data.scbindex[tag];
	अगर (scb != शून्य)
		ahd_sync_scb(ahd, scb,
			     BUS_DMASYNC_POSTREAD|BUS_DMASYNC_POSTWRITE);
	वापस (scb);
पूर्ण

अटल व्योम
ahd_swap_with_next_hscb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	काष्ठा	 hardware_scb *q_hscb;
	काष्ठा	 map_node *q_hscb_map;
	uपूर्णांक32_t saved_hscb_busaddr;

	/*
	 * Our queuing method is a bit tricky.  The card
	 * knows in advance which HSCB (by address) to करोwnload,
	 * and we can't disappoपूर्णांक it.  To achieve this, the next
	 * HSCB to करोwnload is saved off in ahd->next_queued_hscb.
	 * When we are called to queue "an arbitrary scb",
	 * we copy the contents of the incoming HSCB to the one
	 * the sequencer knows about, swap HSCB poपूर्णांकers and
	 * finally assign the SCB to the tag indexed location
	 * in the scb_array.  This makes sure that we can still
	 * locate the correct SCB by SCB_TAG.
	 */
	q_hscb = ahd->next_queued_hscb;
	q_hscb_map = ahd->next_queued_hscb_map;
	saved_hscb_busaddr = q_hscb->hscb_busaddr;
	स_नकल(q_hscb, scb->hscb, माप(*scb->hscb));
	q_hscb->hscb_busaddr = saved_hscb_busaddr;
	q_hscb->next_hscb_busaddr = scb->hscb->hscb_busaddr;

	/* Now swap HSCB poपूर्णांकers. */
	ahd->next_queued_hscb = scb->hscb;
	ahd->next_queued_hscb_map = scb->hscb_map;
	scb->hscb = q_hscb;
	scb->hscb_map = q_hscb_map;

	/* Now define the mapping from tag to SCB in the scbindex */
	ahd->scb_data.scbindex[SCB_GET_TAG(scb)] = scb;
पूर्ण

/*
 * Tell the sequencer about a new transaction to execute.
 */
व्योम
ahd_queue_scb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	ahd_swap_with_next_hscb(ahd, scb);

	अगर (SCBID_IS_शून्य(SCB_GET_TAG(scb)))
		panic("Attempt to queue invalid SCB tag %x\n",
		      SCB_GET_TAG(scb));

	/*
	 * Keep a history of SCBs we've करोwnloaded in the qinfअगरo.
	 */
	ahd->qinfअगरo[AHD_QIN_WRAP(ahd->qinfअगरonext)] = SCB_GET_TAG(scb);
	ahd->qinfअगरonext++;

	अगर (scb->sg_count != 0)
		ahd_setup_data_scb(ahd, scb);
	अन्यथा
		ahd_setup_noxfer_scb(ahd, scb);
	ahd_setup_scb_common(ahd, scb);

	/*
	 * Make sure our data is consistent from the
	 * perspective of the adapter.
	 */
	ahd_sync_scb(ahd, scb, BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_QUEUE) != 0) अणु
		uपूर्णांक64_t host_dataptr;

		host_dataptr = ahd_le64toh(scb->hscb->dataptr);
		prपूर्णांकk("%s: Queueing SCB %d:0x%x bus addr 0x%x - 0x%x%x/0x%x\n",
		       ahd_name(ahd),
		       SCB_GET_TAG(scb), scb->hscb->scsiid,
		       ahd_le32toh(scb->hscb->hscb_busaddr),
		       (u_पूर्णांक)((host_dataptr >> 32) & 0xFFFFFFFF),
		       (u_पूर्णांक)(host_dataptr & 0xFFFFFFFF),
		       ahd_le32toh(scb->hscb->datacnt));
	पूर्ण
#पूर्ण_अगर
	/* Tell the adapter about the newly queued SCB */
	ahd_set_hnscb_qoff(ahd, ahd->qinfअगरonext);
पूर्ण

/************************** Interrupt Processing ******************************/
अटल व्योम
ahd_sync_qoutfअगरo(काष्ठा ahd_softc *ahd, पूर्णांक op)
अणु
	ahd_dmamap_sync(ahd, ahd->shared_data_dmat, ahd->shared_data_map.dmamap,
			/*offset*/0,
			/*len*/AHD_SCB_MAX * माप(काष्ठा ahd_completion), op);
पूर्ण

अटल व्योम
ahd_sync_tqinfअगरo(काष्ठा ahd_softc *ahd, पूर्णांक op)
अणु
#अगर_घोषित AHD_TARGET_MODE
	अगर ((ahd->flags & AHD_TARGETROLE) != 0) अणु
		ahd_dmamap_sync(ahd, ahd->shared_data_dmat,
				ahd->shared_data_map.dmamap,
				ahd_tarअ_लोmd_offset(ahd, 0),
				माप(काष्ठा target_cmd) * AHD_TMODE_CMDS,
				op);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * See अगर the firmware has posted any completed commands
 * पूर्णांकo our in-core command complete fअगरos.
 */
#घोषणा AHD_RUN_QOUTFIFO 0x1
#घोषणा AHD_RUN_TQINFIFO 0x2
अटल u_पूर्णांक
ahd_check_cmdcmpltqueues(काष्ठा ahd_softc *ahd)
अणु
	u_पूर्णांक retval;

	retval = 0;
	ahd_dmamap_sync(ahd, ahd->shared_data_dmat, ahd->shared_data_map.dmamap,
			/*offset*/ahd->qoutfअगरonext * माप(*ahd->qoutfअगरo),
			/*len*/माप(*ahd->qoutfअगरo), BUS_DMASYNC_POSTREAD);
	अगर (ahd->qoutfअगरo[ahd->qoutfअगरonext].valid_tag
	  == ahd->qoutfअगरonext_valid_tag)
		retval |= AHD_RUN_QOUTFIFO;
#अगर_घोषित AHD_TARGET_MODE
	अगर ((ahd->flags & AHD_TARGETROLE) != 0
	 && (ahd->flags & AHD_TQINFIFO_BLOCKED) == 0) अणु
		ahd_dmamap_sync(ahd, ahd->shared_data_dmat,
				ahd->shared_data_map.dmamap,
				ahd_tarअ_लोmd_offset(ahd, ahd->tqinfअगरofnext),
				/*len*/माप(काष्ठा target_cmd),
				BUS_DMASYNC_POSTREAD);
		अगर (ahd->tarअ_लोmds[ahd->tqinfअगरonext].cmd_valid != 0)
			retval |= AHD_RUN_TQINFIFO;
	पूर्ण
#पूर्ण_अगर
	वापस (retval);
पूर्ण

/*
 * Catch an पूर्णांकerrupt from the adapter
 */
पूर्णांक
ahd_पूर्णांकr(काष्ठा ahd_softc *ahd)
अणु
	u_पूर्णांक	पूर्णांकstat;

	अगर ((ahd->छोड़ो & INTEN) == 0) अणु
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
	अगर ((ahd->flags & AHD_ALL_INTERRUPTS) == 0
	 && (ahd_check_cmdcmpltqueues(ahd) != 0))
		पूर्णांकstat = CMDCMPLT;
	अन्यथा
		पूर्णांकstat = ahd_inb(ahd, INTSTAT);

	अगर ((पूर्णांकstat & INT_PEND) == 0)
		वापस (0);

	अगर (पूर्णांकstat & CMDCMPLT) अणु
		ahd_outb(ahd, CLRINT, CLRCMDINT);

		/*
		 * Ensure that the chip sees that we've cleared
		 * this पूर्णांकerrupt beक्रमe we walk the output fअगरo.
		 * Otherwise, we may, due to posted bus ग_लिखोs,
		 * clear the पूर्णांकerrupt after we finish the scan,
		 * and after the sequencer has added new entries
		 * and निश्चितed the पूर्णांकerrupt again.
		 */
		अगर ((ahd->bugs & AHD_INTCOLLISION_BUG) != 0) अणु
			अगर (ahd_is_छोड़ोd(ahd)) अणु
				/*
				 * Potentially lost SEQINT.
				 * If SEQINTCODE is non-zero,
				 * simulate the SEQINT.
				 */
				अगर (ahd_inb(ahd, SEQINTCODE) != NO_SEQINT)
					पूर्णांकstat |= SEQINT;
			पूर्ण
		पूर्ण अन्यथा अणु
			ahd_flush_device_ग_लिखोs(ahd);
		पूर्ण
		ahd_run_qoutfअगरo(ahd);
		ahd->cmdcmplt_counts[ahd->cmdcmplt_bucket]++;
		ahd->cmdcmplt_total++;
#अगर_घोषित AHD_TARGET_MODE
		अगर ((ahd->flags & AHD_TARGETROLE) != 0)
			ahd_run_tqinfअगरo(ahd, /*छोड़ोd*/FALSE);
#पूर्ण_अगर
	पूर्ण

	/*
	 * Handle statuses that may invalidate our cached
	 * copy of INTSTAT separately.
	 */
	अगर (पूर्णांकstat == 0xFF && (ahd->features & AHD_REMOVABLE) != 0) अणु
		/* Hot eject.  Do nothing */
	पूर्ण अन्यथा अगर (पूर्णांकstat & HWERRINT) अणु
		ahd_handle_hwerrपूर्णांक(ahd);
	पूर्ण अन्यथा अगर ((पूर्णांकstat & (PCIINT|SPLTINT)) != 0) अणु
		ahd->bus_पूर्णांकr(ahd);
	पूर्ण अन्यथा अणु

		अगर ((पूर्णांकstat & SEQINT) != 0)
			ahd_handle_seqपूर्णांक(ahd, पूर्णांकstat);

		अगर ((पूर्णांकstat & SCSIINT) != 0)
			ahd_handle_scsiपूर्णांक(ahd, पूर्णांकstat);
	पूर्ण
	वापस (1);
पूर्ण

/******************************** Private Inlines *****************************/
अटल अंतरभूत व्योम
ahd_निश्चित_atn(काष्ठा ahd_softc *ahd)
अणु
	ahd_outb(ahd, SCSISIGO, ATNO);
पूर्ण

/*
 * Determine अगर the current connection has a packetized
 * agreement.  This करोes not necessarily mean that we
 * are currently in a packetized transfer.  We could
 * just as easily be sending or receiving a message.
 */
अटल पूर्णांक
ahd_currently_packetized(काष्ठा ahd_softc *ahd)
अणु
	ahd_mode_state	 saved_modes;
	पूर्णांक		 packetized;

	saved_modes = ahd_save_modes(ahd);
	अगर ((ahd->bugs & AHD_PKTIZED_STATUS_BUG) != 0) अणु
		/*
		 * The packetized bit refers to the last
		 * connection, not the current one.  Check
		 * क्रम non-zero LQISTATE instead.
		 */
		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		packetized = ahd_inb(ahd, LQISTATE) != 0;
	पूर्ण अन्यथा अणु
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		packetized = ahd_inb(ahd, LQISTAT2) & PACKETIZED;
	पूर्ण
	ahd_restore_modes(ahd, saved_modes);
	वापस (packetized);
पूर्ण

अटल अंतरभूत पूर्णांक
ahd_set_active_fअगरo(काष्ठा ahd_softc *ahd)
अणु
	u_पूर्णांक active_fअगरo;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	active_fअगरo = ahd_inb(ahd, DFFSTAT) & CURRFIFO;
	चयन (active_fअगरo) अणु
	हाल 0:
	हाल 1:
		ahd_set_modes(ahd, active_fअगरo, active_fअगरo);
		वापस (1);
	शेष:
		वापस (0);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
ahd_unbusy_tcl(काष्ठा ahd_softc *ahd, u_पूर्णांक tcl)
अणु
	ahd_busy_tcl(ahd, tcl, SCB_LIST_शून्य);
पूर्ण

/*
 * Determine whether the sequencer reported a residual
 * क्रम this SCB/transaction.
 */
अटल अंतरभूत व्योम
ahd_update_residual(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	uपूर्णांक32_t sgptr;

	sgptr = ahd_le32toh(scb->hscb->sgptr);
	अगर ((sgptr & SG_STATUS_VALID) != 0)
		ahd_calc_residual(ahd, scb);
पूर्ण

अटल अंतरभूत व्योम
ahd_complete_scb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	uपूर्णांक32_t sgptr;

	sgptr = ahd_le32toh(scb->hscb->sgptr);
	अगर ((sgptr & SG_STATUS_VALID) != 0)
		ahd_handle_scb_status(ahd, scb);
	अन्यथा
		ahd_करोne(ahd, scb);
पूर्ण


/************************* Sequencer Execution Control ************************/
/*
 * Restart the sequencer program from address zero
 */
अटल व्योम
ahd_restart(काष्ठा ahd_softc *ahd)
अणु

	ahd_छोड़ो(ahd);

	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	/* No more pending messages */
	ahd_clear_msg_state(ahd);
	ahd_outb(ahd, SCSISIGO, 0);		/* De-निश्चित BSY */
	ahd_outb(ahd, MSG_OUT, NOP);	/* No message to send */
	ahd_outb(ahd, SXFRCTL1, ahd_inb(ahd, SXFRCTL1) & ~BITBUCKET);
	ahd_outb(ahd, SEQINTCTL, 0);
	ahd_outb(ahd, LASTPHASE, P_BUSFREE);
	ahd_outb(ahd, SEQ_FLAGS, 0);
	ahd_outb(ahd, SAVED_SCSIID, 0xFF);
	ahd_outb(ahd, SAVED_LUN, 0xFF);

	/*
	 * Ensure that the sequencer's idea of TQINPOS
	 * matches our own.  The sequencer increments TQINPOS
	 * only after it sees a DMA complete and a reset could
	 * occur beक्रमe the increment leaving the kernel to believe
	 * the command arrived but the sequencer to not.
	 */
	ahd_outb(ahd, TQINPOS, ahd->tqinfअगरonext);

	/* Always allow reselection */
	ahd_outb(ahd, SCSISEQ1,
		 ahd_inb(ahd, SCSISEQ_TEMPLATE) & (ENSELI|ENRSELI|ENAUTOATNP));
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);

	/*
	 * Clear any pending sequencer पूर्णांकerrupt.  It is no
	 * दीर्घer relevant since we're resetting the Program
	 * Counter.
	 */
	ahd_outb(ahd, CLRINT, CLRSEQINT);

	ahd_outb(ahd, SEQCTL0, FASTMODE|SEQRESET);
	ahd_unछोड़ो(ahd);
पूर्ण

अटल व्योम
ahd_clear_fअगरo(काष्ठा ahd_softc *ahd, u_पूर्णांक fअगरo)
अणु
	ahd_mode_state	 saved_modes;

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_FIFOS) != 0)
		prपूर्णांकk("%s: Clearing FIFO %d\n", ahd_name(ahd), fअगरo);
#पूर्ण_अगर
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, fअगरo, fअगरo);
	ahd_outb(ahd, DFFSXFRCTL, RSTCHN|CLRSHCNT);
	अगर ((ahd_inb(ahd, SG_STATE) & FETCH_INPROG) != 0)
		ahd_outb(ahd, CCSGCTL, CCSGRESET);
	ahd_outb(ahd, LONGJMP_ADDR + 1, INVALID_ADDR);
	ahd_outb(ahd, SG_STATE, 0);
	ahd_restore_modes(ahd, saved_modes);
पूर्ण

/************************* Input/Output Queues ********************************/
/*
 * Flush and completed commands that are sitting in the command
 * complete queues करोwn on the chip but have yet to be dma'ed back up.
 */
अटल व्योम
ahd_flush_qoutfअगरo(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा		scb *scb;
	ahd_mode_state	saved_modes;
	u_पूर्णांक		saved_scbptr;
	u_पूर्णांक		ccscbctl;
	u_पूर्णांक		scbid;
	u_पूर्णांक		next_scbid;

	saved_modes = ahd_save_modes(ahd);

	/*
	 * Flush the good status FIFO क्रम completed packetized commands.
	 */
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	saved_scbptr = ahd_get_scbptr(ahd);
	जबतक ((ahd_inb(ahd, LQISTAT2) & LQIGSAVAIL) != 0) अणु
		u_पूर्णांक fअगरo_mode;
		u_पूर्णांक i;

		scbid = ahd_inw(ahd, GSFIFO);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("%s: Warning - GSFIFO SCB %d invalid\n",
			       ahd_name(ahd), scbid);
			जारी;
		पूर्ण
		/*
		 * Determine अगर this transaction is still active in
		 * any FIFO.  If it is, we must flush that FIFO to
		 * the host beक्रमe completing the  command.
		 */
		fअगरo_mode = 0;
rescan_fअगरos:
		क्रम (i = 0; i < 2; i++) अणु
			/* Toggle to the other mode. */
			fअगरo_mode ^= 1;
			ahd_set_modes(ahd, fअगरo_mode, fअगरo_mode);

			अगर (ahd_scb_active_in_fअगरo(ahd, scb) == 0)
				जारी;

			ahd_run_data_fअगरo(ahd, scb);

			/*
			 * Running this FIFO may cause a CFG4DATA क्रम
			 * this same transaction to निश्चित in the other
			 * FIFO or a new snapshot SAVEPTRS पूर्णांकerrupt
			 * in this FIFO.  Even running a FIFO may not
			 * clear the transaction अगर we are still रुकोing
			 * क्रम data to drain to the host. We must loop
			 * until the transaction is not active in either
			 * FIFO just to be sure.  Reset our loop counter
			 * so we will visit both FIFOs again beक्रमe
			 * declaring this transaction finished.  We
			 * also delay a bit so that status has a chance
			 * to change beक्रमe we look at this FIFO again.
			 */
			ahd_delay(200);
			जाओ rescan_fअगरos;
		पूर्ण
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		ahd_set_scbptr(ahd, scbid);
		अगर ((ahd_inb_scbram(ahd, SCB_SGPTR) & SG_LIST_शून्य) == 0
		 && ((ahd_inb_scbram(ahd, SCB_SGPTR) & SG_FULL_RESID) != 0
		  || (ahd_inb_scbram(ahd, SCB_RESIDUAL_SGPTR)
		      & SG_LIST_शून्य) != 0)) अणु
			u_पूर्णांक comp_head;

			/*
			 * The transfer completed with a residual.
			 * Place this SCB on the complete DMA list
			 * so that we update our in-core copy of the
			 * SCB beक्रमe completing the command.
			 */
			ahd_outb(ahd, SCB_SCSI_STATUS, 0);
			ahd_outb(ahd, SCB_SGPTR,
				 ahd_inb_scbram(ahd, SCB_SGPTR)
				 | SG_STATUS_VALID);
			ahd_outw(ahd, SCB_TAG, scbid);
			ahd_outw(ahd, SCB_NEXT_COMPLETE, SCB_LIST_शून्य);
			comp_head = ahd_inw(ahd, COMPLETE_DMA_SCB_HEAD);
			अगर (SCBID_IS_शून्य(comp_head)) अणु
				ahd_outw(ahd, COMPLETE_DMA_SCB_HEAD, scbid);
				ahd_outw(ahd, COMPLETE_DMA_SCB_TAIL, scbid);
			पूर्ण अन्यथा अणु
				u_पूर्णांक tail;

				tail = ahd_inw(ahd, COMPLETE_DMA_SCB_TAIL);
				ahd_set_scbptr(ahd, tail);
				ahd_outw(ahd, SCB_NEXT_COMPLETE, scbid);
				ahd_outw(ahd, COMPLETE_DMA_SCB_TAIL, scbid);
				ahd_set_scbptr(ahd, scbid);
			पूर्ण
		पूर्ण अन्यथा
			ahd_complete_scb(ahd, scb);
	पूर्ण
	ahd_set_scbptr(ahd, saved_scbptr);

	/*
	 * Setup क्रम command channel portion of flush.
	 */
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);

	/*
	 * Wait क्रम any inprogress DMA to complete and clear DMA state
	 * अगर this is क्रम an SCB in the qinfअगरo.
	 */
	जबतक (((ccscbctl = ahd_inb(ahd, CCSCBCTL)) & (CCARREN|CCSCBEN)) != 0) अणु

		अगर ((ccscbctl & (CCSCBसूची|CCARREN)) == (CCSCBसूची|CCARREN)) अणु
			अगर ((ccscbctl & ARRDONE) != 0)
				अवरोध;
		पूर्ण अन्यथा अगर ((ccscbctl & CCSCBDONE) != 0)
			अवरोध;
		ahd_delay(200);
	पूर्ण
	/*
	 * We leave the sequencer to cleanup in the हाल of DMA's to
	 * update the qoutfअगरo.  In all other हालs (DMA's to the
	 * chip or a push of an SCB from the COMPLETE_DMA_SCB list),
	 * we disable the DMA engine so that the sequencer will not
	 * attempt to handle the DMA completion.
	 */
	अगर ((ccscbctl & CCSCBसूची) != 0 || (ccscbctl & ARRDONE) != 0)
		ahd_outb(ahd, CCSCBCTL, ccscbctl & ~(CCARREN|CCSCBEN));

	/*
	 * Complete any SCBs that just finished
	 * being DMA'ed पूर्णांकo the qoutfअगरo.
	 */
	ahd_run_qoutfअगरo(ahd);

	saved_scbptr = ahd_get_scbptr(ahd);
	/*
	 * Manually update/complete any completed SCBs that are रुकोing to be
	 * DMA'ed back up to the host.
	 */
	scbid = ahd_inw(ahd, COMPLETE_DMA_SCB_HEAD);
	जबतक (!SCBID_IS_शून्य(scbid)) अणु
		uपूर्णांक8_t *hscb_ptr;
		u_पूर्णांक	 i;

		ahd_set_scbptr(ahd, scbid);
		next_scbid = ahd_inw_scbram(ahd, SCB_NEXT_COMPLETE);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("%s: Warning - DMA-up and complete "
			       "SCB %d invalid\n", ahd_name(ahd), scbid);
			जारी;
		पूर्ण
		hscb_ptr = (uपूर्णांक8_t *)scb->hscb;
		क्रम (i = 0; i < माप(काष्ठा hardware_scb); i++)
			*hscb_ptr++ = ahd_inb_scbram(ahd, SCB_BASE + i);

		ahd_complete_scb(ahd, scb);
		scbid = next_scbid;
	पूर्ण
	ahd_outw(ahd, COMPLETE_DMA_SCB_HEAD, SCB_LIST_शून्य);
	ahd_outw(ahd, COMPLETE_DMA_SCB_TAIL, SCB_LIST_शून्य);

	scbid = ahd_inw(ahd, COMPLETE_ON_QFREEZE_HEAD);
	जबतक (!SCBID_IS_शून्य(scbid)) अणु

		ahd_set_scbptr(ahd, scbid);
		next_scbid = ahd_inw_scbram(ahd, SCB_NEXT_COMPLETE);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("%s: Warning - Complete Qfrz SCB %d invalid\n",
			       ahd_name(ahd), scbid);
			जारी;
		पूर्ण

		ahd_complete_scb(ahd, scb);
		scbid = next_scbid;
	पूर्ण
	ahd_outw(ahd, COMPLETE_ON_QFREEZE_HEAD, SCB_LIST_शून्य);

	scbid = ahd_inw(ahd, COMPLETE_SCB_HEAD);
	जबतक (!SCBID_IS_शून्य(scbid)) अणु

		ahd_set_scbptr(ahd, scbid);
		next_scbid = ahd_inw_scbram(ahd, SCB_NEXT_COMPLETE);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("%s: Warning - Complete SCB %d invalid\n",
			       ahd_name(ahd), scbid);
			जारी;
		पूर्ण

		ahd_complete_scb(ahd, scb);
		scbid = next_scbid;
	पूर्ण
	ahd_outw(ahd, COMPLETE_SCB_HEAD, SCB_LIST_शून्य);

	/*
	 * Restore state.
	 */
	ahd_set_scbptr(ahd, saved_scbptr);
	ahd_restore_modes(ahd, saved_modes);
	ahd->flags |= AHD_UPDATE_PEND_CMDS;
पूर्ण

/*
 * Determine अगर an SCB क्रम a packetized transaction
 * is active in a FIFO.
 */
अटल पूर्णांक
ahd_scb_active_in_fअगरo(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु

	/*
	 * The FIFO is only active क्रम our transaction अगर
	 * the SCBPTR matches the SCB's ID and the firmware
	 * has installed a handler क्रम the FIFO or we have
	 * a pending SAVEPTRS or CFG4DATA पूर्णांकerrupt.
	 */
	अगर (ahd_get_scbptr(ahd) != SCB_GET_TAG(scb)
	 || ((ahd_inb(ahd, LONGJMP_ADDR+1) & INVALID_ADDR) != 0
	  && (ahd_inb(ahd, SEQINTSRC) & (CFG4DATA|SAVEPTRS)) == 0))
		वापस (0);

	वापस (1);
पूर्ण

/*
 * Run a data fअगरo to completion क्रम a transaction we know
 * has completed across the SCSI bus (good status has been
 * received).  We are alपढ़ोy set to the correct FIFO mode
 * on entry to this routine.
 *
 * This function attempts to operate exactly as the firmware
 * would when running this FIFO.  Care must be taken to update
 * this routine any समय the firmware's FIFO algorithm is
 * changed.
 */
अटल व्योम
ahd_run_data_fअगरo(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	u_पूर्णांक seqपूर्णांकsrc;

	seqपूर्णांकsrc = ahd_inb(ahd, SEQINTSRC);
	अगर ((seqपूर्णांकsrc & CFG4DATA) != 0) अणु
		uपूर्णांक32_t datacnt;
		uपूर्णांक32_t sgptr;

		/*
		 * Clear full residual flag.
		 */
		sgptr = ahd_inl_scbram(ahd, SCB_SGPTR) & ~SG_FULL_RESID;
		ahd_outb(ahd, SCB_SGPTR, sgptr);

		/*
		 * Load datacnt and address.
		 */
		datacnt = ahd_inl_scbram(ahd, SCB_DATACNT);
		अगर ((datacnt & AHD_DMA_LAST_SEG) != 0) अणु
			sgptr |= LAST_SEG;
			ahd_outb(ahd, SG_STATE, 0);
		पूर्ण अन्यथा
			ahd_outb(ahd, SG_STATE, LOADING_NEEDED);
		ahd_outq(ahd, HADDR, ahd_inq_scbram(ahd, SCB_DATAPTR));
		ahd_outl(ahd, HCNT, datacnt & AHD_SG_LEN_MASK);
		ahd_outb(ahd, SG_CACHE_PRE, sgptr);
		ahd_outb(ahd, DFCNTRL, PRELOADEN|SCSIEN|HDMAEN);

		/*
		 * Initialize Residual Fields.
		 */
		ahd_outb(ahd, SCB_RESIDUAL_DATACNT+3, datacnt >> 24);
		ahd_outl(ahd, SCB_RESIDUAL_SGPTR, sgptr & SG_PTR_MASK);

		/*
		 * Mark the SCB as having a FIFO in use.
		 */
		ahd_outb(ahd, SCB_FIFO_USE_COUNT,
			 ahd_inb_scbram(ahd, SCB_FIFO_USE_COUNT) + 1);

		/*
		 * Install a "fake" handler क्रम this FIFO.
		 */
		ahd_outw(ahd, LONGJMP_ADDR, 0);

		/*
		 * Notअगरy the hardware that we have satisfied
		 * this sequencer पूर्णांकerrupt.
		 */
		ahd_outb(ahd, CLRSEQINTSRC, CLRCFG4DATA);
	पूर्ण अन्यथा अगर ((seqपूर्णांकsrc & SAVEPTRS) != 0) अणु
		uपूर्णांक32_t sgptr;
		uपूर्णांक32_t resid;

		अगर ((ahd_inb(ahd, LONGJMP_ADDR+1)&INVALID_ADDR) != 0) अणु
			/*
			 * Snapshot Save Poपूर्णांकers.  All that
			 * is necessary to clear the snapshot
			 * is a CLRCHN.
			 */
			जाओ clrchn;
		पूर्ण

		/*
		 * Disable S/G fetch so the DMA engine
		 * is available to future users.
		 */
		अगर ((ahd_inb(ahd, SG_STATE) & FETCH_INPROG) != 0)
			ahd_outb(ahd, CCSGCTL, 0);
		ahd_outb(ahd, SG_STATE, 0);

		/*
		 * Flush the data FIFO.  Strickly only
		 * necessary क्रम Rev A parts.
		 */
		ahd_outb(ahd, DFCNTRL, ahd_inb(ahd, DFCNTRL) | FIFOFLUSH);

		/*
		 * Calculate residual.
		 */
		sgptr = ahd_inl_scbram(ahd, SCB_RESIDUAL_SGPTR);
		resid = ahd_inl(ahd, SHCNT);
		resid |= ahd_inb_scbram(ahd, SCB_RESIDUAL_DATACNT+3) << 24;
		ahd_outl(ahd, SCB_RESIDUAL_DATACNT, resid);
		अगर ((ahd_inb(ahd, SG_CACHE_SHADOW) & LAST_SEG) == 0) अणु
			/*
			 * Must back up to the correct S/G element.
			 * Typically this just means resetting our
			 * low byte to the offset in the SG_CACHE,
			 * but अगर we wrapped, we have to correct
			 * the other bytes of the sgptr too.
			 */
			अगर ((ahd_inb(ahd, SG_CACHE_SHADOW) & 0x80) != 0
			 && (sgptr & 0x80) == 0)
				sgptr -= 0x100;
			sgptr &= ~0xFF;
			sgptr |= ahd_inb(ahd, SG_CACHE_SHADOW)
			       & SG_ADDR_MASK;
			ahd_outl(ahd, SCB_RESIDUAL_SGPTR, sgptr);
			ahd_outb(ahd, SCB_RESIDUAL_DATACNT + 3, 0);
		पूर्ण अन्यथा अगर ((resid & AHD_SG_LEN_MASK) == 0) अणु
			ahd_outb(ahd, SCB_RESIDUAL_SGPTR,
				 sgptr | SG_LIST_शून्य);
		पूर्ण
		/*
		 * Save Poपूर्णांकers.
		 */
		ahd_outq(ahd, SCB_DATAPTR, ahd_inq(ahd, SHADDR));
		ahd_outl(ahd, SCB_DATACNT, resid);
		ahd_outl(ahd, SCB_SGPTR, sgptr);
		ahd_outb(ahd, CLRSEQINTSRC, CLRSAVEPTRS);
		ahd_outb(ahd, SEQIMODE,
			 ahd_inb(ahd, SEQIMODE) | ENSAVEPTRS);
		/*
		 * If the data is to the SCSI bus, we are
		 * करोne, otherwise रुको क्रम FIFOEMP.
		 */
		अगर ((ahd_inb(ahd, DFCNTRL) & सूचीECTION) != 0)
			जाओ clrchn;
	पूर्ण अन्यथा अगर ((ahd_inb(ahd, SG_STATE) & LOADING_NEEDED) != 0) अणु
		uपूर्णांक32_t sgptr;
		uपूर्णांक64_t data_addr;
		uपूर्णांक32_t data_len;
		u_पूर्णांक	 dfcntrl;

		/*
		 * Disable S/G fetch so the DMA engine
		 * is available to future users.  We won't
		 * be using the DMA engine to load segments.
		 */
		अगर ((ahd_inb(ahd, SG_STATE) & FETCH_INPROG) != 0) अणु
			ahd_outb(ahd, CCSGCTL, 0);
			ahd_outb(ahd, SG_STATE, LOADING_NEEDED);
		पूर्ण

		/*
		 * Wait क्रम the DMA engine to notice that the
		 * host transfer is enabled and that there is
		 * space in the S/G FIFO क्रम new segments beक्रमe
		 * loading more segments.
		 */
		अगर ((ahd_inb(ahd, DFSTATUS) & PRELOAD_AVAIL) != 0
		 && (ahd_inb(ahd, DFCNTRL) & HDMAENACK) != 0) अणु

			/*
			 * Determine the offset of the next S/G
			 * element to load.
			 */
			sgptr = ahd_inl_scbram(ahd, SCB_RESIDUAL_SGPTR);
			sgptr &= SG_PTR_MASK;
			अगर ((ahd->flags & AHD_64BIT_ADDRESSING) != 0) अणु
				काष्ठा ahd_dma64_seg *sg;

				sg = ahd_sg_bus_to_virt(ahd, scb, sgptr);
				data_addr = sg->addr;
				data_len = sg->len;
				sgptr += माप(*sg);
			पूर्ण अन्यथा अणु
				काष्ठा	ahd_dma_seg *sg;

				sg = ahd_sg_bus_to_virt(ahd, scb, sgptr);
				data_addr = sg->len & AHD_SG_HIGH_ADDR_MASK;
				data_addr <<= 8;
				data_addr |= sg->addr;
				data_len = sg->len;
				sgptr += माप(*sg);
			पूर्ण

			/*
			 * Update residual inक्रमmation.
			 */
			ahd_outb(ahd, SCB_RESIDUAL_DATACNT+3, data_len >> 24);
			ahd_outl(ahd, SCB_RESIDUAL_SGPTR, sgptr);

			/*
			 * Load the S/G.
			 */
			अगर (data_len & AHD_DMA_LAST_SEG) अणु
				sgptr |= LAST_SEG;
				ahd_outb(ahd, SG_STATE, 0);
			पूर्ण
			ahd_outq(ahd, HADDR, data_addr);
			ahd_outl(ahd, HCNT, data_len & AHD_SG_LEN_MASK);
			ahd_outb(ahd, SG_CACHE_PRE, sgptr & 0xFF);

			/*
			 * Advertise the segment to the hardware.
			 */
			dfcntrl = ahd_inb(ahd, DFCNTRL)|PRELOADEN|HDMAEN;
			अगर ((ahd->features & AHD_NEW_DFCNTRL_OPTS) != 0) अणु
				/*
				 * Use SCSIENWRDIS so that SCSIEN
				 * is never modअगरied by this
				 * operation.
				 */
				dfcntrl |= SCSIENWRDIS;
			पूर्ण
			ahd_outb(ahd, DFCNTRL, dfcntrl);
		पूर्ण
	पूर्ण अन्यथा अगर ((ahd_inb(ahd, SG_CACHE_SHADOW) & LAST_SEG_DONE) != 0) अणु

		/*
		 * Transfer completed to the end of SG list
		 * and has flushed to the host.
		 */
		ahd_outb(ahd, SCB_SGPTR,
			 ahd_inb_scbram(ahd, SCB_SGPTR) | SG_LIST_शून्य);
		जाओ clrchn;
	पूर्ण अन्यथा अगर ((ahd_inb(ahd, DFSTATUS) & FIFOEMP) != 0) अणु
clrchn:
		/*
		 * Clear any handler क्रम this FIFO, decrement
		 * the FIFO use count क्रम the SCB, and release
		 * the FIFO.
		 */
		ahd_outb(ahd, LONGJMP_ADDR + 1, INVALID_ADDR);
		ahd_outb(ahd, SCB_FIFO_USE_COUNT,
			 ahd_inb_scbram(ahd, SCB_FIFO_USE_COUNT) - 1);
		ahd_outb(ahd, DFFSXFRCTL, CLRCHN);
	पूर्ण
पूर्ण

/*
 * Look क्रम entries in the QoutFIFO that have completed.
 * The valid_tag completion field indicates the validity
 * of the entry - the valid value toggles each समय through
 * the queue. We use the sg_status field in the completion
 * entry to aव्योम referencing the hscb अगर the completion
 * occurred with no errors and no residual.  sg_status is
 * a copy of the first byte (little endian) of the sgptr
 * hscb field.
 */
अटल व्योम
ahd_run_qoutfअगरo(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा ahd_completion *completion;
	काष्ठा scb *scb;
	u_पूर्णांक  scb_index;

	अगर ((ahd->flags & AHD_RUNNING_QOUTFIFO) != 0)
		panic("ahd_run_qoutfifo recursion");
	ahd->flags |= AHD_RUNNING_QOUTFIFO;
	ahd_sync_qoutfअगरo(ahd, BUS_DMASYNC_POSTREAD);
	क्रम (;;) अणु
		completion = &ahd->qoutfअगरo[ahd->qoutfअगरonext];

		अगर (completion->valid_tag != ahd->qoutfअगरonext_valid_tag)
			अवरोध;

		scb_index = ahd_le16toh(completion->tag);
		scb = ahd_lookup_scb(ahd, scb_index);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("%s: WARNING no command for scb %d "
			       "(cmdcmplt)\nQOUTPOS = %d\n",
			       ahd_name(ahd), scb_index,
			       ahd->qoutfअगरonext);
			ahd_dump_card_state(ahd);
		पूर्ण अन्यथा अगर ((completion->sg_status & SG_STATUS_VALID) != 0) अणु
			ahd_handle_scb_status(ahd, scb);
		पूर्ण अन्यथा अणु
			ahd_करोne(ahd, scb);
		पूर्ण

		ahd->qoutfअगरonext = (ahd->qoutfअगरonext+1) & (AHD_QOUT_SIZE-1);
		अगर (ahd->qoutfअगरonext == 0)
			ahd->qoutfअगरonext_valid_tag ^= QOUTFIFO_ENTRY_VALID;
	पूर्ण
	ahd->flags &= ~AHD_RUNNING_QOUTFIFO;
पूर्ण

/************************* Interrupt Handling *********************************/
अटल व्योम
ahd_handle_hwerrपूर्णांक(काष्ठा ahd_softc *ahd)
अणु
	/*
	 * Some catastrophic hardware error has occurred.
	 * Prपूर्णांक it क्रम the user and disable the controller.
	 */
	पूर्णांक i;
	पूर्णांक error;

	error = ahd_inb(ahd, ERROR);
	क्रम (i = 0; i < num_errors; i++) अणु
		अगर ((error & ahd_hard_errors[i].त्रुटि_सं) != 0)
			prपूर्णांकk("%s: hwerrint, %s\n",
			       ahd_name(ahd), ahd_hard_errors[i].errmesg);
	पूर्ण

	ahd_dump_card_state(ahd);
	panic("BRKADRINT");

	/* Tell everyone that this HBA is no दीर्घer available */
	ahd_पात_scbs(ahd, CAM_TARGET_WILDCARD, ALL_CHANNELS,
		       CAM_LUN_WILDCARD, SCB_LIST_शून्य, ROLE_UNKNOWN,
		       CAM_NO_HBA);

	/* Tell the प्रणाली that this controller has gone away. */
	ahd_मुक्त(ahd);
पूर्ण

#अगर_घोषित AHD_DEBUG
अटल व्योम
ahd_dump_sglist(काष्ठा scb *scb)
अणु
	पूर्णांक i;

	अगर (scb->sg_count > 0) अणु
		अगर ((scb->ahd_softc->flags & AHD_64BIT_ADDRESSING) != 0) अणु
			काष्ठा ahd_dma64_seg *sg_list;

			sg_list = (काष्ठा ahd_dma64_seg*)scb->sg_list;
			क्रम (i = 0; i < scb->sg_count; i++) अणु
				uपूर्णांक64_t addr;

				addr = ahd_le64toh(sg_list[i].addr);
				prपूर्णांकk("sg[%d] - Addr 0x%x%x : Length %d%s\n",
				       i,
				       (uपूर्णांक32_t)((addr >> 32) & 0xFFFFFFFF),
				       (uपूर्णांक32_t)(addr & 0xFFFFFFFF),
				       sg_list[i].len & AHD_SG_LEN_MASK,
				       (sg_list[i].len & AHD_DMA_LAST_SEG)
				     ? " Last" : "");
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा ahd_dma_seg *sg_list;

			sg_list = (काष्ठा ahd_dma_seg*)scb->sg_list;
			क्रम (i = 0; i < scb->sg_count; i++) अणु
				uपूर्णांक32_t len;

				len = ahd_le32toh(sg_list[i].len);
				prपूर्णांकk("sg[%d] - Addr 0x%x%x : Length %d%s\n",
				       i,
				       (len & AHD_SG_HIGH_ADDR_MASK) >> 24,
				       ahd_le32toh(sg_list[i].addr),
				       len & AHD_SG_LEN_MASK,
				       len & AHD_DMA_LAST_SEG ? " Last" : "");
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर  /*  AHD_DEBUG  */

अटल व्योम
ahd_handle_seqपूर्णांक(काष्ठा ahd_softc *ahd, u_पूर्णांक पूर्णांकstat)
अणु
	u_पूर्णांक seqपूर्णांकcode;

	/*
	 * Save the sequencer पूर्णांकerrupt code and clear the SEQINT
	 * bit. We will unछोड़ो the sequencer, अगर appropriate,
	 * after servicing the request.
	 */
	seqपूर्णांकcode = ahd_inb(ahd, SEQINTCODE);
	ahd_outb(ahd, CLRINT, CLRSEQINT);
	अगर ((ahd->bugs & AHD_INTCOLLISION_BUG) != 0) अणु
		/*
		 * Unछोड़ो the sequencer and let it clear
		 * SEQINT by writing NO_SEQINT to it.  This
		 * will cause the sequencer to be छोड़ोd again,
		 * which is the expected state of this routine.
		 */
		ahd_unछोड़ो(ahd);
		जबतक (!ahd_is_छोड़ोd(ahd))
			;
		ahd_outb(ahd, CLRINT, CLRSEQINT);
	पूर्ण
	ahd_update_modes(ahd);
#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_MISC) != 0)
		prपूर्णांकk("%s: Handle Seqint Called for code %d\n",
		       ahd_name(ahd), seqपूर्णांकcode);
#पूर्ण_अगर
	चयन (seqपूर्णांकcode) अणु
	हाल ENTERING_NONPACK:
	अणु
		काष्ठा	scb *scb;
		u_पूर्णांक	scbid;

		AHD_ASSERT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
				 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb == शून्य) अणु
			/*
			 * Somehow need to know अगर this
			 * is from a selection or reselection.
			 * From that, we can determine target
			 * ID so we at least have an I_T nexus.
			 */
		पूर्ण अन्यथा अणु
			ahd_outb(ahd, SAVED_SCSIID, scb->hscb->scsiid);
			ahd_outb(ahd, SAVED_LUN, scb->hscb->lun);
			ahd_outb(ahd, SEQ_FLAGS, 0x0);
		पूर्ण
		अगर ((ahd_inb(ahd, LQISTAT2) & LQIPHASE_OUTPKT) != 0
		 && (ahd_inb(ahd, SCSISIGO) & ATNO) != 0) अणु
			/*
			 * Phase change after पढ़ो stream with
			 * CRC error with P0 निश्चितed on last
			 * packet.
			 */
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_RECOVERY) != 0)
				prपूर्णांकk("%s: Assuming LQIPHASE_NLQ with "
				       "P0 assertion\n", ahd_name(ahd));
#पूर्ण_अगर
		पूर्ण
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_RECOVERY) != 0)
			prपूर्णांकk("%s: Entering NONPACK\n", ahd_name(ahd));
#पूर्ण_अगर
		अवरोध;
	पूर्ण
	हाल INVALID_SEQINT:
		prपूर्णांकk("%s: Invalid Sequencer interrupt occurred, "
		       "resetting channel.\n",
		       ahd_name(ahd));
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_RECOVERY) != 0)
			ahd_dump_card_state(ahd);
#पूर्ण_अगर
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
		अवरोध;
	हाल STATUS_OVERRUN:
	अणु
		काष्ठा	scb *scb;
		u_पूर्णांक	scbid;

		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb != शून्य)
			ahd_prपूर्णांक_path(ahd, scb);
		अन्यथा
			prपूर्णांकk("%s: ", ahd_name(ahd));
		prपूर्णांकk("SCB %d Packetized Status Overrun", scbid);
		ahd_dump_card_state(ahd);
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
		अवरोध;
	पूर्ण
	हाल CFG4ISTAT_INTR:
	अणु
		काष्ठा	scb *scb;
		u_पूर्णांक	scbid;

		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb == शून्य) अणु
			ahd_dump_card_state(ahd);
			prपूर्णांकk("CFG4ISTAT: Free SCB %d referenced", scbid);
			panic("For safety");
		पूर्ण
		ahd_outq(ahd, HADDR, scb->sense_busaddr);
		ahd_outw(ahd, HCNT, AHD_SENSE_बफ_मानE);
		ahd_outb(ahd, HCNT + 2, 0);
		ahd_outb(ahd, SG_CACHE_PRE, SG_LAST_SEG);
		ahd_outb(ahd, DFCNTRL, PRELOADEN|SCSIEN|HDMAEN);
		अवरोध;
	पूर्ण
	हाल ILLEGAL_PHASE:
	अणु
		u_पूर्णांक bus_phase;

		bus_phase = ahd_inb(ahd, SCSISIGI) & PHASE_MASK;
		prपूर्णांकk("%s: ILLEGAL_PHASE 0x%x\n",
		       ahd_name(ahd), bus_phase);

		चयन (bus_phase) अणु
		हाल P_DATAOUT:
		हाल P_DATAIN:
		हाल P_DATAOUT_DT:
		हाल P_DATAIN_DT:
		हाल P_MESGOUT:
		हाल P_STATUS:
		हाल P_MESGIN:
			ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
			prपूर्णांकk("%s: Issued Bus Reset.\n", ahd_name(ahd));
			अवरोध;
		हाल P_COMMAND:
		अणु
			काष्ठा	ahd_devinfo devinfo;
			काष्ठा	scb *scb;
			u_पूर्णांक	scbid;

			/*
			 * If a target takes us पूर्णांकo the command phase
			 * assume that it has been बाह्यally reset and
			 * has thus lost our previous packetized negotiation
			 * agreement.  Since we have not sent an identअगरy
			 * message and may not have fully qualअगरied the
			 * connection, we change our command to TUR, निश्चित
			 * ATN and ABORT the task when we go to message in
			 * phase.  The OSM will see the REQUEUE_REQUEST
			 * status and retry the command.
			 */
			scbid = ahd_get_scbptr(ahd);
			scb = ahd_lookup_scb(ahd, scbid);
			अगर (scb == शून्य) अणु
				prपूर्णांकk("Invalid phase with no valid SCB.  "
				       "Resetting bus.\n");
				ahd_reset_channel(ahd, 'A',
						  /*Initiate Reset*/TRUE);
				अवरोध;
			पूर्ण
			ahd_compile_devinfo(&devinfo, SCB_GET_OUR_ID(scb),
					    SCB_GET_TARGET(ahd, scb),
					    SCB_GET_LUN(scb),
					    SCB_GET_CHANNEL(ahd, scb),
					    ROLE_INITIATOR);
			ahd_set_width(ahd, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
				      AHD_TRANS_ACTIVE, /*छोड़ोd*/TRUE);
			ahd_set_syncrate(ahd, &devinfo, /*period*/0,
					 /*offset*/0, /*ppr_options*/0,
					 AHD_TRANS_ACTIVE, /*छोड़ोd*/TRUE);
			/* Hand-craft TUR command */
			ahd_outb(ahd, SCB_CDB_STORE, 0);
			ahd_outb(ahd, SCB_CDB_STORE+1, 0);
			ahd_outb(ahd, SCB_CDB_STORE+2, 0);
			ahd_outb(ahd, SCB_CDB_STORE+3, 0);
			ahd_outb(ahd, SCB_CDB_STORE+4, 0);
			ahd_outb(ahd, SCB_CDB_STORE+5, 0);
			ahd_outb(ahd, SCB_CDB_LEN, 6);
			scb->hscb->control &= ~(TAG_ENB|SCB_TAG_TYPE);
			scb->hscb->control |= MK_MESSAGE;
			ahd_outb(ahd, SCB_CONTROL, scb->hscb->control);
			ahd_outb(ahd, MSG_OUT, HOST_MSG);
			ahd_outb(ahd, SAVED_SCSIID, scb->hscb->scsiid);
			/*
			 * The lun is 0, regardless of the SCB's lun
			 * as we have not sent an identअगरy message.
			 */
			ahd_outb(ahd, SAVED_LUN, 0);
			ahd_outb(ahd, SEQ_FLAGS, 0);
			ahd_निश्चित_atn(ahd);
			scb->flags &= ~SCB_PACKETIZED;
			scb->flags |= SCB_ABORT|SCB_EXTERNAL_RESET;
			ahd_मुक्तze_devq(ahd, scb);
			ahd_set_transaction_status(scb, CAM_REQUEUE_REQ);
			ahd_मुक्तze_scb(scb);

			/* Notअगरy XPT */
			ahd_send_async(ahd, devinfo.channel, devinfo.target,
				       CAM_LUN_WILDCARD, AC_SENT_BDR);

			/*
			 * Allow the sequencer to जारी with
			 * non-pack processing.
			 */
			ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
			ahd_outb(ahd, CLRLQOINT1, CLRLQOPHACHGINPKT);
			अगर ((ahd->bugs & AHD_CLRLQO_AUTOCLR_BUG) != 0) अणु
				ahd_outb(ahd, CLRLQOINT1, 0);
			पूर्ण
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_RECOVERY) != 0) अणु
				ahd_prपूर्णांक_path(ahd, scb);
				prपूर्णांकk("Unexpected command phase from "
				       "packetized target\n");
			पूर्ण
#पूर्ण_अगर
			अवरोध;
		पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	हाल CFG4OVERRUN:
	अणु
		काष्ठा	scb *scb;
		u_पूर्णांक	scb_index;

#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_RECOVERY) != 0) अणु
			prपूर्णांकk("%s: CFG4OVERRUN mode = %x\n", ahd_name(ahd),
			       ahd_inb(ahd, MODE_PTR));
		पूर्ण
#पूर्ण_अगर
		scb_index = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scb_index);
		अगर (scb == शून्य) अणु
			/*
			 * Attempt to transfer to an SCB that is
			 * not outstanding.
			 */
			ahd_निश्चित_atn(ahd);
			ahd_outb(ahd, MSG_OUT, HOST_MSG);
			ahd->msgout_buf[0] = ABORT_TASK;
			ahd->msgout_len = 1;
			ahd->msgout_index = 0;
			ahd->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
			/*
			 * Clear status received flag to prevent any
			 * attempt to complete this bogus SCB.
			 */
			ahd_outb(ahd, SCB_CONTROL,
				 ahd_inb_scbram(ahd, SCB_CONTROL)
				 & ~STATUS_RCVD);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल DUMP_CARD_STATE:
	अणु
		ahd_dump_card_state(ahd);
		अवरोध;
	पूर्ण
	हाल PDATA_REINIT:
	अणु
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_RECOVERY) != 0) अणु
			prपूर्णांकk("%s: PDATA_REINIT - DFCNTRL = 0x%x "
			       "SG_CACHE_SHADOW = 0x%x\n",
			       ahd_name(ahd), ahd_inb(ahd, DFCNTRL),
			       ahd_inb(ahd, SG_CACHE_SHADOW));
		पूर्ण
#पूर्ण_अगर
		ahd_reinitialize_dataptrs(ahd);
		अवरोध;
	पूर्ण
	हाल HOST_MSG_LOOP:
	अणु
		काष्ठा ahd_devinfo devinfo;

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
		ahd_fetch_devinfo(ahd, &devinfo);
		अगर (ahd->msg_type == MSG_TYPE_NONE) अणु
			काष्ठा scb *scb;
			u_पूर्णांक scb_index;
			u_पूर्णांक bus_phase;

			bus_phase = ahd_inb(ahd, SCSISIGI) & PHASE_MASK;
			अगर (bus_phase != P_MESGIN
			 && bus_phase != P_MESGOUT) अणु
				prपूर्णांकk("ahd_intr: HOST_MSG_LOOP bad "
				       "phase 0x%x\n", bus_phase);
				/*
				 * Probably transitioned to bus मुक्त beक्रमe
				 * we got here.  Just punt the message.
				 */
				ahd_dump_card_state(ahd);
				ahd_clear_पूर्णांकstat(ahd);
				ahd_restart(ahd);
				वापस;
			पूर्ण

			scb_index = ahd_get_scbptr(ahd);
			scb = ahd_lookup_scb(ahd, scb_index);
			अगर (devinfo.role == ROLE_INITIATOR) अणु
				अगर (bus_phase == P_MESGOUT)
					ahd_setup_initiator_msgout(ahd,
								   &devinfo,
								   scb);
				अन्यथा अणु
					ahd->msg_type =
					    MSG_TYPE_INITIATOR_MSGIN;
					ahd->msgin_index = 0;
				पूर्ण
			पूर्ण
#अगर_घोषित AHD_TARGET_MODE
			अन्यथा अणु
				अगर (bus_phase == P_MESGOUT) अणु
					ahd->msg_type =
					    MSG_TYPE_TARGET_MSGOUT;
					ahd->msgin_index = 0;
				पूर्ण अन्यथा
					ahd_setup_target_msgin(ahd,
							       &devinfo,
							       scb);
			पूर्ण
#पूर्ण_अगर
		पूर्ण

		ahd_handle_message_phase(ahd);
		अवरोध;
	पूर्ण
	हाल NO_MATCH:
	अणु
		/* Ensure we करोn't leave the selection hardware on */
		AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
		ahd_outb(ahd, SCSISEQ0, ahd_inb(ahd, SCSISEQ0) & ~ENSELO);

		prपूर्णांकk("%s:%c:%d: no active SCB for reconnecting "
		       "target - issuing BUS DEVICE RESET\n",
		       ahd_name(ahd), 'A', ahd_inb(ahd, SELID) >> 4);
		prपूर्णांकk("SAVED_SCSIID == 0x%x, SAVED_LUN == 0x%x, "
		       "REG0 == 0x%x ACCUM = 0x%x\n",
		       ahd_inb(ahd, SAVED_SCSIID), ahd_inb(ahd, SAVED_LUN),
		       ahd_inw(ahd, REG0), ahd_inb(ahd, ACCUM));
		prपूर्णांकk("SEQ_FLAGS == 0x%x, SCBPTR == 0x%x, BTT == 0x%x, "
		       "SINDEX == 0x%x\n",
		       ahd_inb(ahd, SEQ_FLAGS), ahd_get_scbptr(ahd),
		       ahd_find_busy_tcl(ahd,
					 BUILD_TCL(ahd_inb(ahd, SAVED_SCSIID),
						   ahd_inb(ahd, SAVED_LUN))),
		       ahd_inw(ahd, SINDEX));
		prपूर्णांकk("SELID == 0x%x, SCB_SCSIID == 0x%x, SCB_LUN == 0x%x, "
		       "SCB_CONTROL == 0x%x\n",
		       ahd_inb(ahd, SELID), ahd_inb_scbram(ahd, SCB_SCSIID),
		       ahd_inb_scbram(ahd, SCB_LUN),
		       ahd_inb_scbram(ahd, SCB_CONTROL));
		prपूर्णांकk("SCSIBUS[0] == 0x%x, SCSISIGI == 0x%x\n",
		       ahd_inb(ahd, SCSIBUS), ahd_inb(ahd, SCSISIGI));
		prपूर्णांकk("SXFRCTL0 == 0x%x\n", ahd_inb(ahd, SXFRCTL0));
		prपूर्णांकk("SEQCTL0 == 0x%x\n", ahd_inb(ahd, SEQCTL0));
		ahd_dump_card_state(ahd);
		ahd->msgout_buf[0] = TARGET_RESET;
		ahd->msgout_len = 1;
		ahd->msgout_index = 0;
		ahd->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
		ahd_outb(ahd, MSG_OUT, HOST_MSG);
		ahd_निश्चित_atn(ahd);
		अवरोध;
	पूर्ण
	हाल PROTO_VIOLATION:
	अणु
		ahd_handle_proto_violation(ahd);
		अवरोध;
	पूर्ण
	हाल IGN_WIDE_RES:
	अणु
		काष्ठा ahd_devinfo devinfo;

		ahd_fetch_devinfo(ahd, &devinfo);
		ahd_handle_ign_wide_residue(ahd, &devinfo);
		अवरोध;
	पूर्ण
	हाल BAD_PHASE:
	अणु
		u_पूर्णांक lastphase;

		lastphase = ahd_inb(ahd, LASTPHASE);
		prपूर्णांकk("%s:%c:%d: unknown scsi bus phase %x, "
		       "lastphase = 0x%x.  Attempting to continue\n",
		       ahd_name(ahd), 'A',
		       SCSIID_TARGET(ahd, ahd_inb(ahd, SAVED_SCSIID)),
		       lastphase, ahd_inb(ahd, SCSISIGI));
		अवरोध;
	पूर्ण
	हाल MISSED_BUSFREE:
	अणु
		u_पूर्णांक lastphase;

		lastphase = ahd_inb(ahd, LASTPHASE);
		prपूर्णांकk("%s:%c:%d: Missed busfree. "
		       "Lastphase = 0x%x, Curphase = 0x%x\n",
		       ahd_name(ahd), 'A',
		       SCSIID_TARGET(ahd, ahd_inb(ahd, SAVED_SCSIID)),
		       lastphase, ahd_inb(ahd, SCSISIGI));
		ahd_restart(ahd);
		वापस;
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
		काष्ठा	scb *scb;
		u_पूर्णांक	scbindex;
#अगर_घोषित AHD_DEBUG
		u_पूर्णांक	lastphase;
#पूर्ण_अगर

		scbindex = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbindex);
#अगर_घोषित AHD_DEBUG
		lastphase = ahd_inb(ahd, LASTPHASE);
		अगर ((ahd_debug & AHD_SHOW_RECOVERY) != 0) अणु
			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("data overrun detected %s.  Tag == 0x%x.\n",
			       ahd_lookup_phase_entry(lastphase)->phasemsg,
			       SCB_GET_TAG(scb));
			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("%s seen Data Phase.  Length = %ld.  "
			       "NumSGs = %d.\n",
			       ahd_inb(ahd, SEQ_FLAGS) & DPHASE
			       ? "Have" : "Haven't",
			       ahd_get_transfer_length(scb), scb->sg_count);
			ahd_dump_sglist(scb);
		पूर्ण
#पूर्ण_अगर

		/*
		 * Set this and it will take effect when the
		 * target करोes a command complete.
		 */
		ahd_मुक्तze_devq(ahd, scb);
		ahd_set_transaction_status(scb, CAM_DATA_RUN_ERR);
		ahd_मुक्तze_scb(scb);
		अवरोध;
	पूर्ण
	हाल MKMSG_FAILED:
	अणु
		काष्ठा ahd_devinfo devinfo;
		काष्ठा scb *scb;
		u_पूर्णांक scbid;

		ahd_fetch_devinfo(ahd, &devinfo);
		prपूर्णांकk("%s:%c:%d:%d: Attempt to issue message failed\n",
		       ahd_name(ahd), devinfo.channel, devinfo.target,
		       devinfo.lun);
		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb != शून्य
		 && (scb->flags & SCB_RECOVERY_SCB) != 0)
			/*
			 * Ensure that we didn't put a second instance of this
			 * SCB पूर्णांकo the QINFIFO.
			 */
			ahd_search_qinfअगरo(ahd, SCB_GET_TARGET(ahd, scb),
					   SCB_GET_CHANNEL(ahd, scb),
					   SCB_GET_LUN(scb), SCB_GET_TAG(scb),
					   ROLE_INITIATOR, /*status*/0,
					   SEARCH_REMOVE);
		ahd_outb(ahd, SCB_CONTROL,
			 ahd_inb_scbram(ahd, SCB_CONTROL) & ~MK_MESSAGE);
		अवरोध;
	पूर्ण
	हाल TASKMGMT_FUNC_COMPLETE:
	अणु
		u_पूर्णांक	scbid;
		काष्ठा	scb *scb;

		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb != शून्य) अणु
			u_पूर्णांक	   lun;
			u_पूर्णांक	   tag;
			cam_status error;

			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("Task Management Func 0x%x Complete\n",
			       scb->hscb->task_management);
			lun = CAM_LUN_WILDCARD;
			tag = SCB_LIST_शून्य;

			चयन (scb->hscb->task_management) अणु
			हाल SIU_TASKMGMT_ABORT_TASK:
				tag = SCB_GET_TAG(scb);
				fallthrough;
			हाल SIU_TASKMGMT_ABORT_TASK_SET:
			हाल SIU_TASKMGMT_CLEAR_TASK_SET:
				lun = scb->hscb->lun;
				error = CAM_REQ_ABORTED;
				ahd_पात_scbs(ahd, SCB_GET_TARGET(ahd, scb),
					       'A', lun, tag, ROLE_INITIATOR,
					       error);
				अवरोध;
			हाल SIU_TASKMGMT_LUN_RESET:
				lun = scb->hscb->lun;
				fallthrough;
			हाल SIU_TASKMGMT_TARGET_RESET:
			अणु
				काष्ठा ahd_devinfo devinfo;

				ahd_scb_devinfo(ahd, &devinfo, scb);
				error = CAM_BDR_SENT;
				ahd_handle_devreset(ahd, &devinfo, lun,
						    CAM_BDR_SENT,
						    lun != CAM_LUN_WILDCARD
						    ? "Lun Reset"
						    : "Target Reset",
						    /*verbose_level*/0);
				अवरोध;
			पूर्ण
			शेष:
				panic("Unexpected TaskMgmt Func\n");
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	हाल TASKMGMT_CMD_CMPLT_OKAY:
	अणु
		u_पूर्णांक	scbid;
		काष्ठा	scb *scb;

		/*
		 * An ABORT TASK TMF failed to be delivered beक्रमe
		 * the targeted command completed normally.
		 */
		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb != शून्य) अणु
			/*
			 * Remove the second instance of this SCB from
			 * the QINFIFO अगर it is still there.
                         */
			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("SCB completes before TMF\n");
			/*
			 * Handle losing the race.  Wait until any
			 * current selection completes.  We will then
			 * set the TMF back to zero in this SCB so that
			 * the sequencer करोesn't bother to issue another
			 * sequencer पूर्णांकerrupt क्रम its completion.
			 */
			जबतक ((ahd_inb(ahd, SCSISEQ0) & ENSELO) != 0
			    && (ahd_inb(ahd, SSTAT0) & SELDO) == 0
			    && (ahd_inb(ahd, SSTAT1) & SELTO) == 0)
				;
			ahd_outb(ahd, SCB_TASK_MANAGEMENT, 0);
			ahd_search_qinfअगरo(ahd, SCB_GET_TARGET(ahd, scb),
					   SCB_GET_CHANNEL(ahd, scb),
					   SCB_GET_LUN(scb), SCB_GET_TAG(scb),
					   ROLE_INITIATOR, /*status*/0,
					   SEARCH_REMOVE);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल TRACEPOINT0:
	हाल TRACEPOINT1:
	हाल TRACEPOINT2:
	हाल TRACEPOINT3:
		prपूर्णांकk("%s: Tracepoint %d\n", ahd_name(ahd),
		       seqपूर्णांकcode - TRACEPOINT0);
		अवरोध;
	हाल NO_SEQINT:
		अवरोध;
	हाल SAW_HWERR:
		ahd_handle_hwerrपूर्णांक(ahd);
		अवरोध;
	शेष:
		prपूर्णांकk("%s: Unexpected SEQINTCODE %d\n", ahd_name(ahd),
		       seqपूर्णांकcode);
		अवरोध;
	पूर्ण
	/*
	 *  The sequencer is छोड़ोd immediately on
	 *  a SEQINT, so we should restart it when
	 *  we're करोne.
	 */
	ahd_unछोड़ो(ahd);
पूर्ण

अटल व्योम
ahd_handle_scsiपूर्णांक(काष्ठा ahd_softc *ahd, u_पूर्णांक पूर्णांकstat)
अणु
	काष्ठा scb	*scb;
	u_पूर्णांक		 status0;
	u_पूर्णांक		 status3;
	u_पूर्णांक		 status;
	u_पूर्णांक		 lqistat1;
	u_पूर्णांक		 lqostat0;
	u_पूर्णांक		 scbid;
	u_पूर्णांक		 busमुक्तसमय;

	ahd_update_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	status3 = ahd_inb(ahd, SSTAT3) & (NTRAMPERR|OSRAMPERR);
	status0 = ahd_inb(ahd, SSTAT0) & (IOERR|OVERRUN|SELDI|SELDO);
	status = ahd_inb(ahd, SSTAT1) & (SELTO|SCSIRSTI|BUSFREE|SCSIPERR);
	lqistat1 = ahd_inb(ahd, LQISTAT1);
	lqostat0 = ahd_inb(ahd, LQOSTAT0);
	busमुक्तसमय = ahd_inb(ahd, SSTAT2) & BUSFREETIME;

	/*
	 * Ignore बाह्यal resets after a bus reset.
	 */
	अगर (((status & SCSIRSTI) != 0) && (ahd->flags & AHD_BUS_RESET_ACTIVE)) अणु
		ahd_outb(ahd, CLRSINT1, CLRSCSIRSTI);
		वापस;
	पूर्ण

	/*
	 * Clear bus reset flag
	 */
	ahd->flags &= ~AHD_BUS_RESET_ACTIVE;

	अगर ((status0 & (SELDI|SELDO)) != 0) अणु
		u_पूर्णांक simode0;

		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		simode0 = ahd_inb(ahd, SIMODE0);
		status0 &= simode0 & (IOERR|OVERRUN|SELDI|SELDO);
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	पूर्ण
	scbid = ahd_get_scbptr(ahd);
	scb = ahd_lookup_scb(ahd, scbid);
	अगर (scb != शून्य
	 && (ahd_inb(ahd, SEQ_FLAGS) & NOT_IDENTIFIED) != 0)
		scb = शून्य;

	अगर ((status0 & IOERR) != 0) अणु
		u_पूर्णांक now_lvd;

		now_lvd = ahd_inb(ahd, SBLKCTL) & ENAB40;
		prपूर्णांकk("%s: Transceiver State Has Changed to %s mode\n",
		       ahd_name(ahd), now_lvd ? "LVD" : "SE");
		ahd_outb(ahd, CLRSINT0, CLRIOERR);
		/*
		 * A change in I/O mode is equivalent to a bus reset.
		 */
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
		ahd_छोड़ो(ahd);
		ahd_setup_iocell_workaround(ahd);
		ahd_unछोड़ो(ahd);
	पूर्ण अन्यथा अगर ((status0 & OVERRUN) != 0) अणु

		prपूर्णांकk("%s: SCSI offset overrun detected.  Resetting bus.\n",
		       ahd_name(ahd));
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
	पूर्ण अन्यथा अगर ((status & SCSIRSTI) != 0) अणु

		prपूर्णांकk("%s: Someone reset channel A\n", ahd_name(ahd));
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/FALSE);
	पूर्ण अन्यथा अगर ((status & SCSIPERR) != 0) अणु

		/* Make sure the sequencer is in a safe location. */
		ahd_clear_critical_section(ahd);

		ahd_handle_transmission_error(ahd);
	पूर्ण अन्यथा अगर (lqostat0 != 0) अणु

		prपूर्णांकk("%s: lqostat0 == 0x%x!\n", ahd_name(ahd), lqostat0);
		ahd_outb(ahd, CLRLQOINT0, lqostat0);
		अगर ((ahd->bugs & AHD_CLRLQO_AUTOCLR_BUG) != 0)
			ahd_outb(ahd, CLRLQOINT1, 0);
	पूर्ण अन्यथा अगर ((status & SELTO) != 0) अणु
		/* Stop the selection */
		ahd_outb(ahd, SCSISEQ0, 0);

		/* Make sure the sequencer is in a safe location. */
		ahd_clear_critical_section(ahd);

		/* No more pending messages */
		ahd_clear_msg_state(ahd);

		/* Clear पूर्णांकerrupt state */
		ahd_outb(ahd, CLRSINT1, CLRSELTIMEO|CLRBUSFREE|CLRSCSIPERR);

		/*
		 * Although the driver करोes not care about the
		 * 'Selection in Progress' status bit, the busy
		 * LED करोes.  SELINGO is only cleared by a successful
		 * selection, so we must manually clear it to insure
		 * the LED turns off just inहाल no future successful
		 * selections occur (e.g. no devices on the bus).
		 */
		ahd_outb(ahd, CLRSINT0, CLRSELINGO);

		scbid = ahd_inw(ahd, WAITING_TID_HEAD);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("%s: ahd_intr - referenced scb not "
			       "valid during SELTO scb(0x%x)\n",
			       ahd_name(ahd), scbid);
			ahd_dump_card_state(ahd);
		पूर्ण अन्यथा अणु
			काष्ठा ahd_devinfo devinfo;
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_SELTO) != 0) अणु
				ahd_prपूर्णांक_path(ahd, scb);
				prपूर्णांकk("Saw Selection Timeout for SCB 0x%x\n",
				       scbid);
			पूर्ण
#पूर्ण_अगर
			ahd_scb_devinfo(ahd, &devinfo, scb);
			ahd_set_transaction_status(scb, CAM_SEL_TIMEOUT);
			ahd_मुक्तze_devq(ahd, scb);

			/*
			 * Cancel any pending transactions on the device
			 * now that it seems to be missing.  This will
			 * also revert us to async/narrow transfers until
			 * we can renegotiate with the device.
			 */
			ahd_handle_devreset(ahd, &devinfo,
					    CAM_LUN_WILDCARD,
					    CAM_SEL_TIMEOUT,
					    "Selection Timeout",
					    /*verbose_level*/1);
		पूर्ण
		ahd_outb(ahd, CLRINT, CLRSCSIINT);
		ahd_iocell_first_selection(ahd);
		ahd_unछोड़ो(ahd);
	पूर्ण अन्यथा अगर ((status0 & (SELDI|SELDO)) != 0) अणु

		ahd_iocell_first_selection(ahd);
		ahd_unछोड़ो(ahd);
	पूर्ण अन्यथा अगर (status3 != 0) अणु
		prपूर्णांकk("%s: SCSI Cell parity error SSTAT3 == 0x%x\n",
		       ahd_name(ahd), status3);
		ahd_outb(ahd, CLRSINT3, status3);
	पूर्ण अन्यथा अगर ((lqistat1 & (LQIPHASE_LQ|LQIPHASE_NLQ)) != 0) अणु

		/* Make sure the sequencer is in a safe location. */
		ahd_clear_critical_section(ahd);

		ahd_handle_lqiphase_error(ahd, lqistat1);
	पूर्ण अन्यथा अगर ((lqistat1 & LQICRCI_NLQ) != 0) अणु
		/*
		 * This status can be delayed during some
		 * streaming operations.  The SCSIPHASE
		 * handler has alपढ़ोy dealt with this हाल
		 * so just clear the error.
		 */
		ahd_outb(ahd, CLRLQIINT1, CLRLQICRCI_NLQ);
	पूर्ण अन्यथा अगर ((status & BUSFREE) != 0
		|| (lqistat1 & LQOBUSFREE) != 0) अणु
		u_पूर्णांक lqostat1;
		पूर्णांक   restart;
		पूर्णांक   clear_fअगरo;
		पूर्णांक   packetized;
		u_पूर्णांक mode;

		/*
		 * Clear our selection hardware as soon as possible.
		 * We may have an entry in the रुकोing Q क्रम this target,
		 * that is affected by this busमुक्त and we करोn't want to
		 * go about selecting the target जबतक we handle the event.
		 */
		ahd_outb(ahd, SCSISEQ0, 0);

		/* Make sure the sequencer is in a safe location. */
		ahd_clear_critical_section(ahd);

		/*
		 * Determine what we were up to at the समय of
		 * the busमुक्त.
		 */
		mode = AHD_MODE_SCSI;
		busमुक्तसमय = ahd_inb(ahd, SSTAT2) & BUSFREETIME;
		lqostat1 = ahd_inb(ahd, LQOSTAT1);
		चयन (busमुक्तसमय) अणु
		हाल BUSFREE_DFF0:
		हाल BUSFREE_DFF1:
		अणु
			mode = busमुक्तसमय == BUSFREE_DFF0
			     ? AHD_MODE_DFF0 : AHD_MODE_DFF1;
			ahd_set_modes(ahd, mode, mode);
			scbid = ahd_get_scbptr(ahd);
			scb = ahd_lookup_scb(ahd, scbid);
			अगर (scb == शून्य) अणु
				prपूर्णांकk("%s: Invalid SCB %d in DFF%d "
				       "during unexpected busfree\n",
				       ahd_name(ahd), scbid, mode);
				packetized = 0;
			पूर्ण अन्यथा
				packetized = (scb->flags & SCB_PACKETIZED) != 0;
			clear_fअगरo = 1;
			अवरोध;
		पूर्ण
		हाल BUSFREE_LQO:
			clear_fअगरo = 0;
			packetized = 1;
			अवरोध;
		शेष:
			clear_fअगरo = 0;
			packetized =  (lqostat1 & LQOBUSFREE) != 0;
			अगर (!packetized
			 && ahd_inb(ahd, LASTPHASE) == P_BUSFREE
			 && (ahd_inb(ahd, SSTAT0) & SELDI) == 0
			 && ((ahd_inb(ahd, SSTAT0) & SELDO) == 0
			  || (ahd_inb(ahd, SCSISEQ0) & ENSELO) == 0))
				/*
				 * Assume packetized अगर we are not
				 * on the bus in a non-packetized
				 * capacity and any pending selection
				 * was a packetized selection.
				 */
				packetized = 1;
			अवरोध;
		पूर्ण

#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MISC) != 0)
			prपूर्णांकk("Saw Busfree.  Busfreetime = 0x%x.\n",
			       busमुक्तसमय);
#पूर्ण_अगर
		/*
		 * Busमुक्तs that occur in non-packetized phases are
		 * handled by the nonpkt_busमुक्त handler.
		 */
		अगर (packetized && ahd_inb(ahd, LASTPHASE) == P_BUSFREE) अणु
			restart = ahd_handle_pkt_busमुक्त(ahd, busमुक्तसमय);
		पूर्ण अन्यथा अणु
			packetized = 0;
			restart = ahd_handle_nonpkt_busमुक्त(ahd);
		पूर्ण
		/*
		 * Clear the busमुक्त पूर्णांकerrupt status.  The setting of
		 * the पूर्णांकerrupt is a pulse, so in a perfect world, we
		 * would not need to muck with the ENBUSFREE logic.  This
		 * would ensure that अगर the bus moves on to another
		 * connection, busमुक्त protection is still in क्रमce.  If
		 * BUSFREEREV is broken, however, we must manually clear
		 * the ENBUSFREE अगर the busमुक्त occurred during a non-pack
		 * connection so that we करोn't get false positives during
		 * future, packetized, connections.
		 */
		ahd_outb(ahd, CLRSINT1, CLRBUSFREE);
		अगर (packetized == 0
		 && (ahd->bugs & AHD_BUSFREEREV_BUG) != 0)
			ahd_outb(ahd, SIMODE1,
				 ahd_inb(ahd, SIMODE1) & ~ENBUSFREE);

		अगर (clear_fअगरo)
			ahd_clear_fअगरo(ahd, mode);

		ahd_clear_msg_state(ahd);
		ahd_outb(ahd, CLRINT, CLRSCSIINT);
		अगर (restart) अणु
			ahd_restart(ahd);
		पूर्ण अन्यथा अणु
			ahd_unछोड़ो(ahd);
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk("%s: Missing case in ahd_handle_scsiint. status = %x\n",
		       ahd_name(ahd), status);
		ahd_dump_card_state(ahd);
		ahd_clear_पूर्णांकstat(ahd);
		ahd_unछोड़ो(ahd);
	पूर्ण
पूर्ण

अटल व्योम
ahd_handle_transmission_error(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा	scb *scb;
	u_पूर्णांक	scbid;
	u_पूर्णांक	lqistat1;
	u_पूर्णांक	msg_out;
	u_पूर्णांक	curphase;
	u_पूर्णांक	lastphase;
	u_पूर्णांक	perrdiag;
	u_पूर्णांक	cur_col;
	पूर्णांक	silent;

	scb = शून्य;
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	lqistat1 = ahd_inb(ahd, LQISTAT1) & ~(LQIPHASE_LQ|LQIPHASE_NLQ);
	ahd_inb(ahd, LQISTAT2);
	अगर ((lqistat1 & (LQICRCI_NLQ|LQICRCI_LQ)) == 0
	 && (ahd->bugs & AHD_NLQICRC_DELAYED_BUG) != 0) अणु
		u_पूर्णांक lqistate;

		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		lqistate = ahd_inb(ahd, LQISTATE);
		अगर ((lqistate >= 0x1E && lqistate <= 0x24)
		 || (lqistate == 0x29)) अणु
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_RECOVERY) != 0) अणु
				prपूर्णांकk("%s: NLQCRC found via LQISTATE\n",
				       ahd_name(ahd));
			पूर्ण
#पूर्ण_अगर
			lqistat1 |= LQICRCI_NLQ;
		पूर्ण
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	पूर्ण

	ahd_outb(ahd, CLRLQIINT1, lqistat1);
	lastphase = ahd_inb(ahd, LASTPHASE);
	curphase = ahd_inb(ahd, SCSISIGI) & PHASE_MASK;
	perrdiag = ahd_inb(ahd, PERRDIAG);
	msg_out = INITIATOR_ERROR;
	ahd_outb(ahd, CLRSINT1, CLRSCSIPERR);

	/*
	 * Try to find the SCB associated with this error.
	 */
	silent = FALSE;
	अगर (lqistat1 == 0
	 || (lqistat1 & LQICRCI_NLQ) != 0) अणु
		अगर ((lqistat1 & (LQICRCI_NLQ|LQIOVERI_NLQ)) != 0)
			ahd_set_active_fअगरo(ahd);
		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb != शून्य && SCB_IS_SILENT(scb))
			silent = TRUE;
	पूर्ण

	cur_col = 0;
	अगर (silent == FALSE) अणु
		prपूर्णांकk("%s: Transmission error detected\n", ahd_name(ahd));
		ahd_lqistat1_prपूर्णांक(lqistat1, &cur_col, 50);
		ahd_lastphase_prपूर्णांक(lastphase, &cur_col, 50);
		ahd_scsisigi_prपूर्णांक(curphase, &cur_col, 50);
		ahd_perrdiag_prपूर्णांक(perrdiag, &cur_col, 50);
		prपूर्णांकk("\n");
		ahd_dump_card_state(ahd);
	पूर्ण

	अगर ((lqistat1 & (LQIOVERI_LQ|LQIOVERI_NLQ)) != 0) अणु
		अगर (silent == FALSE) अणु
			prपूर्णांकk("%s: Gross protocol error during incoming "
			       "packet.  lqistat1 == 0x%x.  Resetting bus.\n",
			       ahd_name(ahd), lqistat1);
		पूर्ण
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
		वापस;
	पूर्ण अन्यथा अगर ((lqistat1 & LQICRCI_LQ) != 0) अणु
		/*
		 * A CRC error has been detected on an incoming LQ.
		 * The bus is currently hung on the last ACK.
		 * Hit LQIRETRY to release the last ack, and
		 * रुको क्रम the sequencer to determine that ATNO
		 * is निश्चितed जबतक in message out to take us
		 * to our host message loop.  No NONPACKREQ or
		 * LQIPHASE type errors will occur in this
		 * scenario.  After this first LQIRETRY, the LQI
		 * manager will be in ISELO where it will
		 * happily sit until another packet phase begins.
		 * Unexpected bus मुक्त detection is enabled
		 * through any phases that occur after we release
		 * this last ack until the LQI manager sees a
		 * packet phase.  This implies we may have to
		 * ignore a perfectly valid "unexected busfree"
		 * after our "initiator detected error" message is
		 * sent.  A busमुक्त is the expected response after
		 * we tell the target that it's L_Q was corrupted.
		 * (SPI4R09 10.7.3.3.3)
		 */
		ahd_outb(ahd, LQCTL2, LQIRETRY);
		prपूर्णांकk("LQIRetry for LQICRCI_LQ to release ACK\n");
	पूर्ण अन्यथा अगर ((lqistat1 & LQICRCI_NLQ) != 0) अणु
		/*
		 * We detected a CRC error in a NON-LQ packet.
		 * The hardware has varying behavior in this situation
		 * depending on whether this packet was part of a
		 * stream or not.
		 *
		 * PKT by PKT mode:
		 * The hardware has alपढ़ोy acked the complete packet.
		 * If the target honors our outstanding ATN condition,
		 * we should be (or soon will be) in MSGOUT phase.
		 * This will trigger the LQIPHASE_LQ status bit as the
		 * hardware was expecting another LQ.  Unexpected
		 * busमुक्त detection is enabled.  Once LQIPHASE_LQ is
		 * true (first entry पूर्णांकo host message loop is much
		 * the same), we must clear LQIPHASE_LQ and hit
		 * LQIRETRY so the hardware is पढ़ोy to handle
		 * a future LQ.  NONPACKREQ will not be निश्चितed again
		 * once we hit LQIRETRY until another packet is
		 * processed.  The target may either go busमुक्त
		 * or start another packet in response to our message.
		 *
		 * Read Streaming P0 निश्चितed:
		 * If we उठाओ ATN and the target completes the entire
		 * stream (P0 निश्चितed during the last packet), the
		 * hardware will ack all data and वापस to the ISTART
		 * state.  When the target reponds to our ATN condition,
		 * LQIPHASE_LQ will be निश्चितed.  We should respond to
		 * this with an LQIRETRY to prepare क्रम any future
		 * packets.  NONPACKREQ will not be निश्चितed again
		 * once we hit LQIRETRY until another packet is
		 * processed.  The target may either go busमुक्त or
		 * start another packet in response to our message.
		 * Busमुक्त detection is enabled.
		 *
		 * Read Streaming P0 not निश्चितed:
		 * If we उठाओ ATN and the target transitions to
		 * MSGOUT in or after a packet where P0 is not
		 * निश्चितed, the hardware will निश्चित LQIPHASE_NLQ.
		 * We should respond to the LQIPHASE_NLQ with an
		 * LQIRETRY.  Should the target stay in a non-pkt
		 * phase after we send our message, the hardware
		 * will निश्चित LQIPHASE_LQ.  Recovery is then just as
		 * listed above क्रम the पढ़ो streaming with P0 निश्चितed.
		 * Busमुक्त detection is enabled.
		 */
		अगर (silent == FALSE)
			prपूर्णांकk("LQICRC_NLQ\n");
		अगर (scb == शून्य) अणु
			prपूर्णांकk("%s: No SCB valid for LQICRC_NLQ.  "
			       "Resetting bus\n", ahd_name(ahd));
			ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर ((lqistat1 & LQIBADLQI) != 0) अणु
		prपूर्णांकk("Need to handle BADLQI!\n");
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
		वापस;
	पूर्ण अन्यथा अगर ((perrdiag & (PARITYERR|PREVPHASE)) == PARITYERR) अणु
		अगर ((curphase & ~P_DATAIN_DT) != 0) अणु
			/* Ack the byte.  So we can जारी. */
			अगर (silent == FALSE)
				prपूर्णांकk("Acking %s to clear perror\n",
				    ahd_lookup_phase_entry(curphase)->phasemsg);
			ahd_inb(ahd, SCSIDAT);
		पूर्ण

		अगर (curphase == P_MESGIN)
			msg_out = MSG_PARITY_ERROR;
	पूर्ण

	/*
	 * We've set the hardware to निश्चित ATN अगर we
	 * get a parity error on "in" phases, so all we
	 * need to करो is stuff the message buffer with
	 * the appropriate message.  "In" phases have set
	 * mesg_out to something other than NOP.
	 */
	ahd->send_msg_लिखो_त्रुटि = msg_out;
	अगर (scb != शून्य && msg_out == INITIATOR_ERROR)
		scb->flags |= SCB_TRANSMISSION_ERROR;
	ahd_outb(ahd, MSG_OUT, HOST_MSG);
	ahd_outb(ahd, CLRINT, CLRSCSIINT);
	ahd_unछोड़ो(ahd);
पूर्ण

अटल व्योम
ahd_handle_lqiphase_error(काष्ठा ahd_softc *ahd, u_पूर्णांक lqistat1)
अणु
	/*
	 * Clear the sources of the पूर्णांकerrupts.
	 */
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, CLRLQIINT1, lqistat1);

	/*
	 * If the "illegal" phase changes were in response
	 * to our ATN to flag a CRC error, AND we ended up
	 * on packet boundaries, clear the error, restart the
	 * LQI manager as appropriate, and go on our merry
	 * way toward sending the message.  Otherwise, reset
	 * the bus to clear the error.
	 */
	ahd_set_active_fअगरo(ahd);
	अगर ((ahd_inb(ahd, SCSISIGO) & ATNO) != 0
	 && (ahd_inb(ahd, MDFFSTAT) & DLZERO) != 0) अणु
		अगर ((lqistat1 & LQIPHASE_LQ) != 0) अणु
			prपूर्णांकk("LQIRETRY for LQIPHASE_LQ\n");
			ahd_outb(ahd, LQCTL2, LQIRETRY);
		पूर्ण अन्यथा अगर ((lqistat1 & LQIPHASE_NLQ) != 0) अणु
			prपूर्णांकk("LQIRETRY for LQIPHASE_NLQ\n");
			ahd_outb(ahd, LQCTL2, LQIRETRY);
		पूर्ण अन्यथा
			panic("ahd_handle_lqiphase_error: No phase errors\n");
		ahd_dump_card_state(ahd);
		ahd_outb(ahd, CLRINT, CLRSCSIINT);
		ahd_unछोड़ो(ahd);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("Resetting Channel for LQI Phase error\n");
		ahd_dump_card_state(ahd);
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
	पूर्ण
पूर्ण

/*
 * Packetized unexpected or expected busमुक्त.
 * Entered in mode based on busमुक्तसमय.
 */
अटल पूर्णांक
ahd_handle_pkt_busमुक्त(काष्ठा ahd_softc *ahd, u_पूर्णांक busमुक्तसमय)
अणु
	u_पूर्णांक lqostat1;

	AHD_ASSERT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	lqostat1 = ahd_inb(ahd, LQOSTAT1);
	अगर ((lqostat1 & LQOBUSFREE) != 0) अणु
		काष्ठा scb *scb;
		u_पूर्णांक scbid;
		u_पूर्णांक saved_scbptr;
		u_पूर्णांक रुकोing_h;
		u_पूर्णांक रुकोing_t;
		u_पूर्णांक next;

		/*
		 * The LQO manager detected an unexpected busमुक्त
		 * either:
		 *
		 * 1) During an outgoing LQ.
		 * 2) After an outgoing LQ but beक्रमe the first
		 *    REQ of the command packet.
		 * 3) During an outgoing command packet.
		 *
		 * In all हालs, CURRSCB is poपूर्णांकing to the
		 * SCB that encountered the failure.  Clean
		 * up the queue, clear SELDO and LQOBUSFREE,
		 * and allow the sequencer to restart the select
		 * out at its lesure.
		 */
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		scbid = ahd_inw(ahd, CURRSCB);
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb == शून्य)
		       panic("SCB not valid during LQOBUSFREE");
		/*
		 * Clear the status.
		 */
		ahd_outb(ahd, CLRLQOINT1, CLRLQOBUSFREE);
		अगर ((ahd->bugs & AHD_CLRLQO_AUTOCLR_BUG) != 0)
			ahd_outb(ahd, CLRLQOINT1, 0);
		ahd_outb(ahd, SCSISEQ0, ahd_inb(ahd, SCSISEQ0) & ~ENSELO);
		ahd_flush_device_ग_लिखोs(ahd);
		ahd_outb(ahd, CLRSINT0, CLRSELDO);

		/*
		 * Return the LQO manager to its idle loop.  It will
		 * not करो this स्वतःmatically अगर the busमुक्त occurs
		 * after the first REQ of either the LQ or command
		 * packet or between the LQ and command packet.
		 */
		ahd_outb(ahd, LQCTL2, ahd_inb(ahd, LQCTL2) | LQOTOIDLE);

		/*
		 * Update the रुकोing क्रम selection queue so
		 * we restart on the correct SCB.
		 */
		रुकोing_h = ahd_inw(ahd, WAITING_TID_HEAD);
		saved_scbptr = ahd_get_scbptr(ahd);
		अगर (रुकोing_h != scbid) अणु

			ahd_outw(ahd, WAITING_TID_HEAD, scbid);
			रुकोing_t = ahd_inw(ahd, WAITING_TID_TAIL);
			अगर (रुकोing_t == रुकोing_h) अणु
				ahd_outw(ahd, WAITING_TID_TAIL, scbid);
				next = SCB_LIST_शून्य;
			पूर्ण अन्यथा अणु
				ahd_set_scbptr(ahd, रुकोing_h);
				next = ahd_inw_scbram(ahd, SCB_NEXT2);
			पूर्ण
			ahd_set_scbptr(ahd, scbid);
			ahd_outw(ahd, SCB_NEXT2, next);
		पूर्ण
		ahd_set_scbptr(ahd, saved_scbptr);
		अगर (scb->crc_retry_count < AHD_MAX_LQ_CRC_ERRORS) अणु
			अगर (SCB_IS_SILENT(scb) == FALSE) अणु
				ahd_prपूर्णांक_path(ahd, scb);
				prपूर्णांकk("Probable outgoing LQ CRC error.  "
				       "Retrying command\n");
			पूर्ण
			scb->crc_retry_count++;
		पूर्ण अन्यथा अणु
			ahd_set_transaction_status(scb, CAM_UNCOR_PARITY);
			ahd_मुक्तze_scb(scb);
			ahd_मुक्तze_devq(ahd, scb);
		पूर्ण
		/* Return unpausing the sequencer. */
		वापस (0);
	पूर्ण अन्यथा अगर ((ahd_inb(ahd, PERRDIAG) & PARITYERR) != 0) अणु
		/*
		 * Ignore what are really parity errors that
		 * occur on the last REQ of a मुक्त running
		 * घड़ी prior to going busमुक्त.  Some drives
		 * करो not properly active negate just beक्रमe
		 * going busमुक्त resulting in a parity glitch.
		 */
		ahd_outb(ahd, CLRSINT1, CLRSCSIPERR|CLRBUSFREE);
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MASKED_ERRORS) != 0)
			prपूर्णांकk("%s: Parity on last REQ detected "
			       "during busfree phase.\n",
			       ahd_name(ahd));
#पूर्ण_अगर
		/* Return unpausing the sequencer. */
		वापस (0);
	पूर्ण
	अगर (ahd->src_mode != AHD_MODE_SCSI) अणु
		u_पूर्णांक	scbid;
		काष्ठा	scb *scb;

		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		ahd_prपूर्णांक_path(ahd, scb);
		prपूर्णांकk("Unexpected PKT busfree condition\n");
		ahd_dump_card_state(ahd);
		ahd_पात_scbs(ahd, SCB_GET_TARGET(ahd, scb), 'A',
			       SCB_GET_LUN(scb), SCB_GET_TAG(scb),
			       ROLE_INITIATOR, CAM_UNEXP_BUSFREE);

		/* Return restarting the sequencer. */
		वापस (1);
	पूर्ण
	prपूर्णांकk("%s: Unexpected PKT busfree condition\n", ahd_name(ahd));
	ahd_dump_card_state(ahd);
	/* Restart the sequencer. */
	वापस (1);
पूर्ण

/*
 * Non-packetized unexpected or expected busमुक्त.
 */
अटल पूर्णांक
ahd_handle_nonpkt_busमुक्त(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा	ahd_devinfo devinfo;
	काष्ठा	scb *scb;
	u_पूर्णांक	lastphase;
	u_पूर्णांक	saved_scsiid;
	u_पूर्णांक	saved_lun;
	u_पूर्णांक	target;
	u_पूर्णांक	initiator_role_id;
	u_पूर्णांक	scbid;
	u_पूर्णांक	ppr_busमुक्त;
	पूर्णांक	prपूर्णांकerror;

	/*
	 * Look at what phase we were last in.  If its message out,
	 * chances are pretty good that the busमुक्त was in response
	 * to one of our पात requests.
	 */
	lastphase = ahd_inb(ahd, LASTPHASE);
	saved_scsiid = ahd_inb(ahd, SAVED_SCSIID);
	saved_lun = ahd_inb(ahd, SAVED_LUN);
	target = SCSIID_TARGET(ahd, saved_scsiid);
	initiator_role_id = SCSIID_OUR_ID(saved_scsiid);
	ahd_compile_devinfo(&devinfo, initiator_role_id,
			    target, saved_lun, 'A', ROLE_INITIATOR);
	prपूर्णांकerror = 1;

	scbid = ahd_get_scbptr(ahd);
	scb = ahd_lookup_scb(ahd, scbid);
	अगर (scb != शून्य
	 && (ahd_inb(ahd, SEQ_FLAGS) & NOT_IDENTIFIED) != 0)
		scb = शून्य;

	ppr_busमुक्त = (ahd->msg_flags & MSG_FLAG_EXPECT_PPR_BUSFREE) != 0;
	अगर (lastphase == P_MESGOUT) अणु
		u_पूर्णांक tag;

		tag = SCB_LIST_शून्य;
		अगर (ahd_sent_msg(ahd, AHDMSG_1B, ABORT_TASK, TRUE)
		 || ahd_sent_msg(ahd, AHDMSG_1B, ABORT_TASK_SET, TRUE)) अणु
			पूर्णांक found;
			पूर्णांक sent_msg;

			अगर (scb == शून्य) अणु
				ahd_prपूर्णांक_devinfo(ahd, &devinfo);
				prपूर्णांकk("Abort for unidentified "
				       "connection completed.\n");
				/* restart the sequencer. */
				वापस (1);
			पूर्ण
			sent_msg = ahd->msgout_buf[ahd->msgout_index - 1];
			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("SCB %d - Abort%s Completed.\n",
			       SCB_GET_TAG(scb),
			       sent_msg == ABORT_TASK ? "" : " Tag");

			अगर (sent_msg == ABORT_TASK)
				tag = SCB_GET_TAG(scb);

			अगर ((scb->flags & SCB_EXTERNAL_RESET) != 0) अणु
				/*
				 * This पात is in response to an
				 * unexpected चयन to command phase
				 * क्रम a packetized connection.  Since
				 * the identअगरy message was never sent,
				 * "saved lun" is 0.  We really want to
				 * पात only the SCB that encountered
				 * this error, which could have a dअगरferent
				 * lun.  The SCB will be retried so the OS
				 * will see the UA after renegotiating to
				 * packetized.
				 */
				tag = SCB_GET_TAG(scb);
				saved_lun = scb->hscb->lun;
			पूर्ण
			found = ahd_पात_scbs(ahd, target, 'A', saved_lun,
					       tag, ROLE_INITIATOR,
					       CAM_REQ_ABORTED);
			prपूर्णांकk("found == 0x%x\n", found);
			prपूर्णांकerror = 0;
		पूर्ण अन्यथा अगर (ahd_sent_msg(ahd, AHDMSG_1B,
					TARGET_RESET, TRUE)) अणु
			ahd_handle_devreset(ahd, &devinfo, CAM_LUN_WILDCARD,
					    CAM_BDR_SENT, "Bus Device Reset",
					    /*verbose_level*/0);
			prपूर्णांकerror = 0;
		पूर्ण अन्यथा अगर (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_PPR, FALSE)
			&& ppr_busमुक्त == 0) अणु
			काष्ठा ahd_initiator_tinfo *tinfo;
			काष्ठा ahd_पंचांगode_tstate *tstate;

			/*
			 * PPR Rejected.
			 *
			 * If the previous negotiation was packetized,
			 * this could be because the device has been
			 * reset without our knowledge.  Force our
			 * current negotiation to async and retry the
			 * negotiation.  Otherwise retry the command
			 * with non-ppr negotiation.
			 */
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				prपूर्णांकk("PPR negotiation rejected busfree.\n");
#पूर्ण_अगर
			tinfo = ahd_fetch_transinfo(ahd, devinfo.channel,
						    devinfo.our_scsiid,
						    devinfo.target, &tstate);
			अगर ((tinfo->curr.ppr_options & MSG_EXT_PPR_IU_REQ)!=0) अणु
				ahd_set_width(ahd, &devinfo,
					      MSG_EXT_WDTR_BUS_8_BIT,
					      AHD_TRANS_CUR,
					      /*छोड़ोd*/TRUE);
				ahd_set_syncrate(ahd, &devinfo,
						/*period*/0, /*offset*/0,
						/*ppr_options*/0,
						AHD_TRANS_CUR,
						/*छोड़ोd*/TRUE);
				/*
				 * The expect PPR busमुक्त handler below
				 * will effect the retry and necessary
				 * पात.
				 */
			पूर्ण अन्यथा अणु
				tinfo->curr.transport_version = 2;
				tinfo->goal.transport_version = 2;
				tinfo->goal.ppr_options = 0;
				अगर (scb != शून्य) अणु
					/*
					 * Remove any SCBs in the रुकोing
					 * क्रम selection queue that may
					 * also be क्रम this target so that
					 * command ordering is preserved.
					 */
					ahd_मुक्तze_devq(ahd, scb);
					ahd_qinfअगरo_requeue_tail(ahd, scb);
				पूर्ण
				prपूर्णांकerror = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_WDTR, FALSE)
			&& ppr_busमुक्त == 0) अणु
			/*
			 * Negotiation Rejected.  Go-narrow and
			 * retry command.
			 */
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				prपूर्णांकk("WDTR negotiation rejected busfree.\n");
#पूर्ण_अगर
			ahd_set_width(ahd, &devinfo,
				      MSG_EXT_WDTR_BUS_8_BIT,
				      AHD_TRANS_CUR|AHD_TRANS_GOAL,
				      /*छोड़ोd*/TRUE);
			अगर (scb != शून्य) अणु
				/*
				 * Remove any SCBs in the रुकोing क्रम
				 * selection queue that may also be क्रम
				 * this target so that command ordering
				 * is preserved.
				 */
				ahd_मुक्तze_devq(ahd, scb);
				ahd_qinfअगरo_requeue_tail(ahd, scb);
			पूर्ण
			prपूर्णांकerror = 0;
		पूर्ण अन्यथा अगर (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_SDTR, FALSE)
			&& ppr_busमुक्त == 0) अणु
			/*
			 * Negotiation Rejected.  Go-async and
			 * retry command.
			 */
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				prपूर्णांकk("SDTR negotiation rejected busfree.\n");
#पूर्ण_अगर
			ahd_set_syncrate(ahd, &devinfo,
					/*period*/0, /*offset*/0,
					/*ppr_options*/0,
					AHD_TRANS_CUR|AHD_TRANS_GOAL,
					/*छोड़ोd*/TRUE);
			अगर (scb != शून्य) अणु
				/*
				 * Remove any SCBs in the रुकोing क्रम
				 * selection queue that may also be क्रम
				 * this target so that command ordering
				 * is preserved.
				 */
				ahd_मुक्तze_devq(ahd, scb);
				ahd_qinfअगरo_requeue_tail(ahd, scb);
			पूर्ण
			prपूर्णांकerror = 0;
		पूर्ण अन्यथा अगर ((ahd->msg_flags & MSG_FLAG_EXPECT_IDE_BUSFREE) != 0
			&& ahd_sent_msg(ahd, AHDMSG_1B,
					 INITIATOR_ERROR, TRUE)) अणु

#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				prपूर्णांकk("Expected IDE Busfree\n");
#पूर्ण_अगर
			prपूर्णांकerror = 0;
		पूर्ण अन्यथा अगर ((ahd->msg_flags & MSG_FLAG_EXPECT_QASREJ_BUSFREE)
			&& ahd_sent_msg(ahd, AHDMSG_1B,
					MESSAGE_REJECT, TRUE)) अणु

#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				prपूर्णांकk("Expected QAS Reject Busfree\n");
#पूर्ण_अगर
			prपूर्णांकerror = 0;
		पूर्ण
	पूर्ण

	/*
	 * The busमुक्त required flag is honored at the end of
	 * the message phases.  We check it last in हाल we
	 * had to send some other message that caused a busमुक्त.
	 */
	अगर (scb != शून्य && prपूर्णांकerror != 0
	 && (lastphase == P_MESGIN || lastphase == P_MESGOUT)
	 && ((ahd->msg_flags & MSG_FLAG_EXPECT_PPR_BUSFREE) != 0)) अणु

		ahd_मुक्तze_devq(ahd, scb);
		ahd_set_transaction_status(scb, CAM_REQUEUE_REQ);
		ahd_मुक्तze_scb(scb);
		अगर ((ahd->msg_flags & MSG_FLAG_IU_REQ_CHANGED) != 0) अणु
			ahd_पात_scbs(ahd, SCB_GET_TARGET(ahd, scb),
				       SCB_GET_CHANNEL(ahd, scb),
				       SCB_GET_LUN(scb), SCB_LIST_शून्य,
				       ROLE_INITIATOR, CAM_REQ_ABORTED);
		पूर्ण अन्यथा अणु
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				prपूर्णांकk("PPR Negotiation Busfree.\n");
#पूर्ण_अगर
			ahd_करोne(ahd, scb);
		पूर्ण
		prपूर्णांकerror = 0;
	पूर्ण
	अगर (prपूर्णांकerror != 0) अणु
		पूर्णांक पातed;

		पातed = 0;
		अगर (scb != शून्य) अणु
			u_पूर्णांक tag;

			अगर ((scb->hscb->control & TAG_ENB) != 0)
				tag = SCB_GET_TAG(scb);
			अन्यथा
				tag = SCB_LIST_शून्य;
			ahd_prपूर्णांक_path(ahd, scb);
			पातed = ahd_पात_scbs(ahd, target, 'A',
				       SCB_GET_LUN(scb), tag,
				       ROLE_INITIATOR,
				       CAM_UNEXP_BUSFREE);
		पूर्ण अन्यथा अणु
			/*
			 * We had not fully identअगरied this connection,
			 * so we cannot पात anything.
			 */
			prपूर्णांकk("%s: ", ahd_name(ahd));
		पूर्ण
		prपूर्णांकk("Unexpected busfree %s, %d SCBs aborted, "
		       "PRGMCNT == 0x%x\n",
		       ahd_lookup_phase_entry(lastphase)->phasemsg,
		       पातed,
		       ahd_inw(ahd, PRGMCNT));
		ahd_dump_card_state(ahd);
		अगर (lastphase != P_BUSFREE)
			ahd_क्रमce_renegotiation(ahd, &devinfo);
	पूर्ण
	/* Always restart the sequencer. */
	वापस (1);
पूर्ण

अटल व्योम
ahd_handle_proto_violation(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा	ahd_devinfo devinfo;
	काष्ठा	scb *scb;
	u_पूर्णांक	scbid;
	u_पूर्णांक	seq_flags;
	u_पूर्णांक	curphase;
	u_पूर्णांक	lastphase;
	पूर्णांक	found;

	ahd_fetch_devinfo(ahd, &devinfo);
	scbid = ahd_get_scbptr(ahd);
	scb = ahd_lookup_scb(ahd, scbid);
	seq_flags = ahd_inb(ahd, SEQ_FLAGS);
	curphase = ahd_inb(ahd, SCSISIGI) & PHASE_MASK;
	lastphase = ahd_inb(ahd, LASTPHASE);
	अगर ((seq_flags & NOT_IDENTIFIED) != 0) अणु

		/*
		 * The reconnecting target either did not send an
		 * identअगरy message, or did, but we didn't find an SCB
		 * to match.
		 */
		ahd_prपूर्णांक_devinfo(ahd, &devinfo);
		prपूर्णांकk("Target did not send an IDENTIFY message. "
		       "LASTPHASE = 0x%x.\n", lastphase);
		scb = शून्य;
	पूर्ण अन्यथा अगर (scb == शून्य) अणु
		/*
		 * We करोn't seem to have an SCB active क्रम this
		 * transaction.  Prपूर्णांक an error and reset the bus.
		 */
		ahd_prपूर्णांक_devinfo(ahd, &devinfo);
		prपूर्णांकk("No SCB found during protocol violation\n");
		जाओ proto_violation_reset;
	पूर्ण अन्यथा अणु
		ahd_set_transaction_status(scb, CAM_SEQUENCE_FAIL);
		अगर ((seq_flags & NO_CDB_SENT) != 0) अणु
			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("No or incomplete CDB sent to device.\n");
		पूर्ण अन्यथा अगर ((ahd_inb_scbram(ahd, SCB_CONTROL)
			  & STATUS_RCVD) == 0) अणु
			/*
			 * The target never bothered to provide status to
			 * us prior to completing the command.  Since we करोn't
			 * know the disposition of this command, we must attempt
			 * to पात it.  Assert ATN and prepare to send an पात
			 * message.
			 */
			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("Completed command without status.\n");
		पूर्ण अन्यथा अणु
			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("Unknown protocol violation.\n");
			ahd_dump_card_state(ahd);
		पूर्ण
	पूर्ण
	अगर ((lastphase & ~P_DATAIN_DT) == 0
	 || lastphase == P_COMMAND) अणु
proto_violation_reset:
		/*
		 * Target either went directly to data
		 * phase or didn't respond to our ATN.
		 * The only safe thing to करो is to blow
		 * it away with a bus reset.
		 */
		found = ahd_reset_channel(ahd, 'A', TRUE);
		prपूर्णांकk("%s: Issued Channel %c Bus Reset. "
		       "%d SCBs aborted\n", ahd_name(ahd), 'A', found);
	पूर्ण अन्यथा अणु
		/*
		 * Leave the selection hardware off in हाल
		 * this पात attempt will affect yet to
		 * be sent commands.
		 */
		ahd_outb(ahd, SCSISEQ0,
			 ahd_inb(ahd, SCSISEQ0) & ~ENSELO);
		ahd_निश्चित_atn(ahd);
		ahd_outb(ahd, MSG_OUT, HOST_MSG);
		अगर (scb == शून्य) अणु
			ahd_prपूर्णांक_devinfo(ahd, &devinfo);
			ahd->msgout_buf[0] = ABORT_TASK;
			ahd->msgout_len = 1;
			ahd->msgout_index = 0;
			ahd->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
		पूर्ण अन्यथा अणु
			ahd_prपूर्णांक_path(ahd, scb);
			scb->flags |= SCB_ABORT;
		पूर्ण
		prपूर्णांकk("Protocol violation %s.  Attempting to abort.\n",
		       ahd_lookup_phase_entry(curphase)->phasemsg);
	पूर्ण
पूर्ण

/*
 * Force renegotiation to occur the next समय we initiate
 * a command to the current device.
 */
अटल व्योम
ahd_क्रमce_renegotiation(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo)
अणु
	काष्ठा	ahd_initiator_tinfo *targ_info;
	काष्ठा	ahd_पंचांगode_tstate *tstate;

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0) अणु
		ahd_prपूर्णांक_devinfo(ahd, devinfo);
		prपूर्णांकk("Forcing renegotiation\n");
	पूर्ण
#पूर्ण_अगर
	targ_info = ahd_fetch_transinfo(ahd,
					devinfo->channel,
					devinfo->our_scsiid,
					devinfo->target,
					&tstate);
	ahd_update_neg_request(ahd, devinfo, tstate,
			       targ_info, AHD_NEG_IF_NON_ASYNC);
पूर्ण

#घोषणा AHD_MAX_STEPS 2000
अटल व्योम
ahd_clear_critical_section(काष्ठा ahd_softc *ahd)
अणु
	ahd_mode_state	saved_modes;
	पूर्णांक		stepping;
	पूर्णांक		steps;
	पूर्णांक		first_instr;
	u_पूर्णांक		simode0;
	u_पूर्णांक		simode1;
	u_पूर्णांक		simode3;
	u_पूर्णांक		lqimode0;
	u_पूर्णांक		lqimode1;
	u_पूर्णांक		lqomode0;
	u_पूर्णांक		lqomode1;

	अगर (ahd->num_critical_sections == 0)
		वापस;

	stepping = FALSE;
	steps = 0;
	first_instr = 0;
	simode0 = 0;
	simode1 = 0;
	simode3 = 0;
	lqimode0 = 0;
	lqimode1 = 0;
	lqomode0 = 0;
	lqomode1 = 0;
	saved_modes = ahd_save_modes(ahd);
	क्रम (;;) अणु
		काष्ठा	cs *cs;
		u_पूर्णांक	seqaddr;
		u_पूर्णांक	i;

		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		seqaddr = ahd_inw(ahd, CURADDR);

		cs = ahd->critical_sections;
		क्रम (i = 0; i < ahd->num_critical_sections; i++, cs++) अणु
			अगर (cs->begin < seqaddr && cs->end >= seqaddr)
				अवरोध;
		पूर्ण

		अगर (i == ahd->num_critical_sections)
			अवरोध;

		अगर (steps > AHD_MAX_STEPS) अणु
			prपूर्णांकk("%s: Infinite loop in critical section\n"
			       "%s: First Instruction 0x%x now 0x%x\n",
			       ahd_name(ahd), ahd_name(ahd), first_instr,
			       seqaddr);
			ahd_dump_card_state(ahd);
			panic("critical section loop");
		पूर्ण

		steps++;
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MISC) != 0)
			prपूर्णांकk("%s: Single stepping at 0x%x\n", ahd_name(ahd),
			       seqaddr);
#पूर्ण_अगर
		अगर (stepping == FALSE) अणु

			first_instr = seqaddr;
			ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
			simode0 = ahd_inb(ahd, SIMODE0);
			simode3 = ahd_inb(ahd, SIMODE3);
			lqimode0 = ahd_inb(ahd, LQIMODE0);
			lqimode1 = ahd_inb(ahd, LQIMODE1);
			lqomode0 = ahd_inb(ahd, LQOMODE0);
			lqomode1 = ahd_inb(ahd, LQOMODE1);
			ahd_outb(ahd, SIMODE0, 0);
			ahd_outb(ahd, SIMODE3, 0);
			ahd_outb(ahd, LQIMODE0, 0);
			ahd_outb(ahd, LQIMODE1, 0);
			ahd_outb(ahd, LQOMODE0, 0);
			ahd_outb(ahd, LQOMODE1, 0);
			ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
			simode1 = ahd_inb(ahd, SIMODE1);
			/*
			 * We करोn't clear ENBUSFREE.  Unक्रमtunately
			 * we cannot re-enable busमुक्त detection within
			 * the current connection, so we must leave it
			 * on जबतक single stepping.
			 */
			ahd_outb(ahd, SIMODE1, simode1 & ENBUSFREE);
			ahd_outb(ahd, SEQCTL0, ahd_inb(ahd, SEQCTL0) | STEP);
			stepping = TRUE;
		पूर्ण
		ahd_outb(ahd, CLRSINT1, CLRBUSFREE);
		ahd_outb(ahd, CLRINT, CLRSCSIINT);
		ahd_set_modes(ahd, ahd->saved_src_mode, ahd->saved_dst_mode);
		ahd_outb(ahd, HCNTRL, ahd->unछोड़ो);
		जबतक (!ahd_is_छोड़ोd(ahd))
			ahd_delay(200);
		ahd_update_modes(ahd);
	पूर्ण
	अगर (stepping) अणु
		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		ahd_outb(ahd, SIMODE0, simode0);
		ahd_outb(ahd, SIMODE3, simode3);
		ahd_outb(ahd, LQIMODE0, lqimode0);
		ahd_outb(ahd, LQIMODE1, lqimode1);
		ahd_outb(ahd, LQOMODE0, lqomode0);
		ahd_outb(ahd, LQOMODE1, lqomode1);
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		ahd_outb(ahd, SEQCTL0, ahd_inb(ahd, SEQCTL0) & ~STEP);
		ahd_outb(ahd, SIMODE1, simode1);
		/*
		 * SCSIINT seems to glitch occasionally when
		 * the पूर्णांकerrupt masks are restored.  Clear SCSIINT
		 * one more समय so that only persistent errors
		 * are seen as a real पूर्णांकerrupt.
		 */
		ahd_outb(ahd, CLRINT, CLRSCSIINT);
	पूर्ण
	ahd_restore_modes(ahd, saved_modes);
पूर्ण

/*
 * Clear any pending पूर्णांकerrupt status.
 */
अटल व्योम
ahd_clear_पूर्णांकstat(काष्ठा ahd_softc *ahd)
अणु
	AHD_ASSERT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	/* Clear any पूर्णांकerrupt conditions this may have caused */
	ahd_outb(ahd, CLRLQIINT0, CLRLQIATNQAS|CLRLQICRCT1|CLRLQICRCT2
				 |CLRLQIBADLQT|CLRLQIATNLQ|CLRLQIATNCMD);
	ahd_outb(ahd, CLRLQIINT1, CLRLQIPHASE_LQ|CLRLQIPHASE_NLQ|CLRLIQABORT
				 |CLRLQICRCI_LQ|CLRLQICRCI_NLQ|CLRLQIBADLQI
				 |CLRLQIOVERI_LQ|CLRLQIOVERI_NLQ|CLRNONPACKREQ);
	ahd_outb(ahd, CLRLQOINT0, CLRLQOTARGSCBPERR|CLRLQOSTOPT2|CLRLQOATNLQ
				 |CLRLQOATNPKT|CLRLQOTCRC);
	ahd_outb(ahd, CLRLQOINT1, CLRLQOINITSCBPERR|CLRLQOSTOPI2|CLRLQOBADQAS
				 |CLRLQOBUSFREE|CLRLQOPHACHGINPKT);
	अगर ((ahd->bugs & AHD_CLRLQO_AUTOCLR_BUG) != 0) अणु
		ahd_outb(ahd, CLRLQOINT0, 0);
		ahd_outb(ahd, CLRLQOINT1, 0);
	पूर्ण
	ahd_outb(ahd, CLRSINT3, CLRNTRAMPERR|CLROSRAMPERR);
	ahd_outb(ahd, CLRSINT1, CLRSELTIMEO|CLRATNO|CLRSCSIRSTI
				|CLRBUSFREE|CLRSCSIPERR|CLRREQINIT);
	ahd_outb(ahd, CLRSINT0, CLRSELDO|CLRSELDI|CLRSELINGO
				|CLRIOERR|CLROVERRUN);
	ahd_outb(ahd, CLRINT, CLRSCSIINT);
पूर्ण

/**************************** Debugging Routines ******************************/
#अगर_घोषित AHD_DEBUG
uपूर्णांक32_t ahd_debug = AHD_DEBUG_OPTS;
#पूर्ण_अगर

#अगर 0
व्योम
ahd_prपूर्णांक_scb(काष्ठा scb *scb)
अणु
	काष्ठा hardware_scb *hscb;
	पूर्णांक i;

	hscb = scb->hscb;
	prपूर्णांकk("scb:%p control:0x%x scsiid:0x%x lun:%d cdb_len:%d\n",
	       (व्योम *)scb,
	       hscb->control,
	       hscb->scsiid,
	       hscb->lun,
	       hscb->cdb_len);
	prपूर्णांकk("Shared Data: ");
	क्रम (i = 0; i < माप(hscb->shared_data.idata.cdb); i++)
		prपूर्णांकk("%#02x", hscb->shared_data.idata.cdb[i]);
	prपूर्णांकk("        dataptr:%#x%x datacnt:%#x sgptr:%#x tag:%#x\n",
	       (uपूर्णांक32_t)((ahd_le64toh(hscb->dataptr) >> 32) & 0xFFFFFFFF),
	       (uपूर्णांक32_t)(ahd_le64toh(hscb->dataptr) & 0xFFFFFFFF),
	       ahd_le32toh(hscb->datacnt),
	       ahd_le32toh(hscb->sgptr),
	       SCB_GET_TAG(scb));
	ahd_dump_sglist(scb);
पूर्ण
#पूर्ण_अगर  /*  0  */

/************************* Transfer Negotiation *******************************/
/*
 * Allocate per target mode instance (ID we respond to as a target)
 * transfer negotiation data काष्ठाures.
 */
अटल काष्ठा ahd_पंचांगode_tstate *
ahd_alloc_tstate(काष्ठा ahd_softc *ahd, u_पूर्णांक scsi_id, अक्षर channel)
अणु
	काष्ठा ahd_पंचांगode_tstate *master_tstate;
	काष्ठा ahd_पंचांगode_tstate *tstate;
	पूर्णांक i;

	master_tstate = ahd->enabled_tarमाला_लो[ahd->our_id];
	अगर (ahd->enabled_tarमाला_लो[scsi_id] != शून्य
	 && ahd->enabled_tarमाला_लो[scsi_id] != master_tstate)
		panic("%s: ahd_alloc_tstate - Target already allocated",
		      ahd_name(ahd));
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
		क्रम (i = 0; i < 16; i++) अणु
			स_रखो(&tstate->transinfo[i].curr, 0,
			      माप(tstate->transinfo[i].curr));
			स_रखो(&tstate->transinfo[i].goal, 0,
			      माप(tstate->transinfo[i].goal));
		पूर्ण
	पूर्ण अन्यथा
		स_रखो(tstate, 0, माप(*tstate));
	ahd->enabled_tarमाला_लो[scsi_id] = tstate;
	वापस (tstate);
पूर्ण

#अगर_घोषित AHD_TARGET_MODE
/*
 * Free per target mode instance (ID we respond to as a target)
 * transfer negotiation data काष्ठाures.
 */
अटल व्योम
ahd_मुक्त_tstate(काष्ठा ahd_softc *ahd, u_पूर्णांक scsi_id, अक्षर channel, पूर्णांक क्रमce)
अणु
	काष्ठा ahd_पंचांगode_tstate *tstate;

	/*
	 * Don't clean up our "master" tstate.
	 * It has our शेष user settings.
	 */
	अगर (scsi_id == ahd->our_id
	 && क्रमce == FALSE)
		वापस;

	tstate = ahd->enabled_tarमाला_लो[scsi_id];
	kमुक्त(tstate);
	ahd->enabled_tarमाला_लो[scsi_id] = शून्य;
पूर्ण
#पूर्ण_अगर

/*
 * Called when we have an active connection to a target on the bus,
 * this function finds the nearest period to the input period limited
 * by the capabilities of the bus connectivity of and sync settings क्रम
 * the target.
 */
अटल व्योम
ahd_devlimited_syncrate(काष्ठा ahd_softc *ahd,
			काष्ठा ahd_initiator_tinfo *tinfo,
			u_पूर्णांक *period, u_पूर्णांक *ppr_options, role_t role)
अणु
	काष्ठा	ahd_transinfo *transinfo;
	u_पूर्णांक	maxsync;

	अगर ((ahd_inb(ahd, SBLKCTL) & ENAB40) != 0
	 && (ahd_inb(ahd, SSTAT2) & EXP_ACTIVE) == 0) अणु
		maxsync = AHD_SYNCRATE_PACED;
	पूर्ण अन्यथा अणु
		maxsync = AHD_SYNCRATE_ULTRA;
		/* Can't करो DT related options on an SE bus */
		*ppr_options &= MSG_EXT_PPR_QAS_REQ;
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
	*ppr_options &= (transinfo->ppr_options|MSG_EXT_PPR_PCOMP_EN);
	अगर (transinfo->width == MSG_EXT_WDTR_BUS_8_BIT) अणु
		maxsync = max(maxsync, (u_पूर्णांक)AHD_SYNCRATE_ULTRA2);
		*ppr_options &= ~MSG_EXT_PPR_DT_REQ;
	पूर्ण
	अगर (transinfo->period == 0) अणु
		*period = 0;
		*ppr_options = 0;
	पूर्ण अन्यथा अणु
		*period = max(*period, (u_पूर्णांक)transinfo->period);
		ahd_find_syncrate(ahd, period, ppr_options, maxsync);
	पूर्ण
पूर्ण

/*
 * Look up the valid period to SCSIRATE conversion in our table.
 * Return the period and offset that should be sent to the target
 * अगर this was the beginning of an SDTR.
 */
व्योम
ahd_find_syncrate(काष्ठा ahd_softc *ahd, u_पूर्णांक *period,
		  u_पूर्णांक *ppr_options, u_पूर्णांक maxsync)
अणु
	अगर (*period < maxsync)
		*period = maxsync;

	अगर ((*ppr_options & MSG_EXT_PPR_DT_REQ) != 0
	 && *period > AHD_SYNCRATE_MIN_DT)
		*ppr_options &= ~MSG_EXT_PPR_DT_REQ;

	अगर (*period > AHD_SYNCRATE_MIN)
		*period = 0;

	/* Honor PPR option conक्रमmance rules. */
	अगर (*period > AHD_SYNCRATE_PACED)
		*ppr_options &= ~MSG_EXT_PPR_RTI;

	अगर ((*ppr_options & MSG_EXT_PPR_IU_REQ) == 0)
		*ppr_options &= (MSG_EXT_PPR_DT_REQ|MSG_EXT_PPR_QAS_REQ);

	अगर ((*ppr_options & MSG_EXT_PPR_DT_REQ) == 0)
		*ppr_options &= MSG_EXT_PPR_QAS_REQ;

	/* Skip all PACED only entries अगर IU is not available */
	अगर ((*ppr_options & MSG_EXT_PPR_IU_REQ) == 0
	 && *period < AHD_SYNCRATE_DT)
		*period = AHD_SYNCRATE_DT;

	/* Skip all DT only entries अगर DT is not available */
	अगर ((*ppr_options & MSG_EXT_PPR_DT_REQ) == 0
	 && *period < AHD_SYNCRATE_ULTRA2)
		*period = AHD_SYNCRATE_ULTRA2;
पूर्ण

/*
 * Truncate the given synchronous offset to a value the
 * current adapter type and syncrate are capable of.
 */
अटल व्योम
ahd_validate_offset(काष्ठा ahd_softc *ahd,
		    काष्ठा ahd_initiator_tinfo *tinfo,
		    u_पूर्णांक period, u_पूर्णांक *offset, पूर्णांक wide,
		    role_t role)
अणु
	u_पूर्णांक maxoffset;

	/* Limit offset to what we can करो */
	अगर (period == 0)
		maxoffset = 0;
	अन्यथा अगर (period <= AHD_SYNCRATE_PACED) अणु
		अगर ((ahd->bugs & AHD_PACED_NEGTABLE_BUG) != 0)
			maxoffset = MAX_OFFSET_PACED_BUG;
		अन्यथा
			maxoffset = MAX_OFFSET_PACED;
	पूर्ण अन्यथा
		maxoffset = MAX_OFFSET_NON_PACED;
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
ahd_validate_width(काष्ठा ahd_softc *ahd, काष्ठा ahd_initiator_tinfo *tinfo,
		   u_पूर्णांक *bus_width, role_t role)
अणु
	चयन (*bus_width) अणु
	शेष:
		अगर (ahd->features & AHD_WIDE) अणु
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
ahd_update_neg_request(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo,
		       काष्ठा ahd_पंचांगode_tstate *tstate,
		       काष्ठा ahd_initiator_tinfo *tinfo, ahd_neg_type neg_type)
अणु
	u_पूर्णांक स्वतः_negotiate_orig;

	स्वतः_negotiate_orig = tstate->स्वतः_negotiate;
	अगर (neg_type == AHD_NEG_ALWAYS) अणु
		/*
		 * Force our "current" settings to be
		 * unknown so that unless a bus reset
		 * occurs the need to renegotiate is
		 * recorded persistently.
		 */
		अगर ((ahd->features & AHD_WIDE) != 0)
			tinfo->curr.width = AHD_WIDTH_UNKNOWN;
		tinfo->curr.period = AHD_PERIOD_UNKNOWN;
		tinfo->curr.offset = AHD_OFFSET_UNKNOWN;
	पूर्ण
	अगर (tinfo->curr.period != tinfo->goal.period
	 || tinfo->curr.width != tinfo->goal.width
	 || tinfo->curr.offset != tinfo->goal.offset
	 || tinfo->curr.ppr_options != tinfo->goal.ppr_options
	 || (neg_type == AHD_NEG_IF_NON_ASYNC
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
ahd_set_syncrate(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo,
		 u_पूर्णांक period, u_पूर्णांक offset, u_पूर्णांक ppr_options,
		 u_पूर्णांक type, पूर्णांक छोड़ोd)
अणु
	काष्ठा	ahd_initiator_tinfo *tinfo;
	काष्ठा	ahd_पंचांगode_tstate *tstate;
	u_पूर्णांक	old_period;
	u_पूर्णांक	old_offset;
	u_पूर्णांक	old_ppr;
	पूर्णांक	active;
	पूर्णांक	update_needed;

	active = (type & AHD_TRANS_ACTIVE) == AHD_TRANS_ACTIVE;
	update_needed = 0;

	अगर (period == 0 || offset == 0) अणु
		period = 0;
		offset = 0;
	पूर्ण

	tinfo = ahd_fetch_transinfo(ahd, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);

	अगर ((type & AHD_TRANS_USER) != 0) अणु
		tinfo->user.period = period;
		tinfo->user.offset = offset;
		tinfo->user.ppr_options = ppr_options;
	पूर्ण

	अगर ((type & AHD_TRANS_GOAL) != 0) अणु
		tinfo->goal.period = period;
		tinfo->goal.offset = offset;
		tinfo->goal.ppr_options = ppr_options;
	पूर्ण

	old_period = tinfo->curr.period;
	old_offset = tinfo->curr.offset;
	old_ppr	   = tinfo->curr.ppr_options;

	अगर ((type & AHD_TRANS_CUR) != 0
	 && (old_period != period
	  || old_offset != offset
	  || old_ppr != ppr_options)) अणु

		update_needed++;

		tinfo->curr.period = period;
		tinfo->curr.offset = offset;
		tinfo->curr.ppr_options = ppr_options;

		ahd_send_async(ahd, devinfo->channel, devinfo->target,
			       CAM_LUN_WILDCARD, AC_TRANSFER_NEG);
		अगर (bootverbose) अणु
			अगर (offset != 0) अणु
				पूर्णांक options;

				prपूर्णांकk("%s: target %d synchronous with "
				       "period = 0x%x, offset = 0x%x",
				       ahd_name(ahd), devinfo->target,
				       period, offset);
				options = 0;
				अगर ((ppr_options & MSG_EXT_PPR_RD_STRM) != 0) अणु
					prपूर्णांकk("(RDSTRM");
					options++;
				पूर्ण
				अगर ((ppr_options & MSG_EXT_PPR_DT_REQ) != 0) अणु
					prपूर्णांकk("%s", options ? "|DT" : "(DT");
					options++;
				पूर्ण
				अगर ((ppr_options & MSG_EXT_PPR_IU_REQ) != 0) अणु
					prपूर्णांकk("%s", options ? "|IU" : "(IU");
					options++;
				पूर्ण
				अगर ((ppr_options & MSG_EXT_PPR_RTI) != 0) अणु
					prपूर्णांकk("%s", options ? "|RTI" : "(RTI");
					options++;
				पूर्ण
				अगर ((ppr_options & MSG_EXT_PPR_QAS_REQ) != 0) अणु
					prपूर्णांकk("%s", options ? "|QAS" : "(QAS");
					options++;
				पूर्ण
				अगर (options != 0)
					prपूर्णांकk(")\n");
				अन्यथा
					prपूर्णांकk("\n");
			पूर्ण अन्यथा अणु
				prपूर्णांकk("%s: target %d using "
				       "asynchronous transfers%s\n",
				       ahd_name(ahd), devinfo->target,
				       (ppr_options & MSG_EXT_PPR_QAS_REQ) != 0
				     ?  "(QAS)" : "");
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * Always refresh the neg-table to handle the हाल of the
	 * sequencer setting the ENATNO bit क्रम a MK_MESSAGE request.
	 * We will always renegotiate in that हाल अगर this is a
	 * packetized request.  Also manage the busमुक्त expected flag
	 * from this common routine so that we catch changes due to
	 * WDTR or SDTR messages.
	 */
	अगर ((type & AHD_TRANS_CUR) != 0) अणु
		अगर (!छोड़ोd)
			ahd_छोड़ो(ahd);
		ahd_update_neg_table(ahd, devinfo, &tinfo->curr);
		अगर (!छोड़ोd)
			ahd_unछोड़ो(ahd);
		अगर (ahd->msg_type != MSG_TYPE_NONE) अणु
			अगर ((old_ppr & MSG_EXT_PPR_IU_REQ)
			 != (ppr_options & MSG_EXT_PPR_IU_REQ)) अणु
#अगर_घोषित AHD_DEBUG
				अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0) अणु
					ahd_prपूर्णांक_devinfo(ahd, devinfo);
					prपूर्णांकk("Expecting IU Change busfree\n");
				पूर्ण
#पूर्ण_अगर
				ahd->msg_flags |= MSG_FLAG_EXPECT_PPR_BUSFREE
					       |  MSG_FLAG_IU_REQ_CHANGED;
			पूर्ण
			अगर ((old_ppr & MSG_EXT_PPR_IU_REQ) != 0) अणु
#अगर_घोषित AHD_DEBUG
				अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
					prपूर्णांकk("PPR with IU_REQ outstanding\n");
#पूर्ण_अगर
				ahd->msg_flags |= MSG_FLAG_EXPECT_PPR_BUSFREE;
			पूर्ण
		पूर्ण
	पूर्ण

	update_needed += ahd_update_neg_request(ahd, devinfo, tstate,
						tinfo, AHD_NEG_TO_GOAL);

	अगर (update_needed && active)
		ahd_update_pending_scbs(ahd);
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
ahd_set_width(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo,
	      u_पूर्णांक width, u_पूर्णांक type, पूर्णांक छोड़ोd)
अणु
	काष्ठा	ahd_initiator_tinfo *tinfo;
	काष्ठा	ahd_पंचांगode_tstate *tstate;
	u_पूर्णांक	oldwidth;
	पूर्णांक	active;
	पूर्णांक	update_needed;

	active = (type & AHD_TRANS_ACTIVE) == AHD_TRANS_ACTIVE;
	update_needed = 0;
	tinfo = ahd_fetch_transinfo(ahd, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);

	अगर ((type & AHD_TRANS_USER) != 0)
		tinfo->user.width = width;

	अगर ((type & AHD_TRANS_GOAL) != 0)
		tinfo->goal.width = width;

	oldwidth = tinfo->curr.width;
	अगर ((type & AHD_TRANS_CUR) != 0 && oldwidth != width) अणु

		update_needed++;

		tinfo->curr.width = width;
		ahd_send_async(ahd, devinfo->channel, devinfo->target,
			       CAM_LUN_WILDCARD, AC_TRANSFER_NEG);
		अगर (bootverbose) अणु
			prपूर्णांकk("%s: target %d using %dbit transfers\n",
			       ahd_name(ahd), devinfo->target,
			       8 * (0x01 << width));
		पूर्ण
	पूर्ण

	अगर ((type & AHD_TRANS_CUR) != 0) अणु
		अगर (!छोड़ोd)
			ahd_छोड़ो(ahd);
		ahd_update_neg_table(ahd, devinfo, &tinfo->curr);
		अगर (!छोड़ोd)
			ahd_unछोड़ो(ahd);
	पूर्ण

	update_needed += ahd_update_neg_request(ahd, devinfo, tstate,
						tinfo, AHD_NEG_TO_GOAL);
	अगर (update_needed && active)
		ahd_update_pending_scbs(ahd);

पूर्ण

/*
 * Update the current state of tagged queuing क्रम a given target.
 */
अटल व्योम
ahd_set_tags(काष्ठा ahd_softc *ahd, काष्ठा scsi_cmnd *cmd,
	     काष्ठा ahd_devinfo *devinfo, ahd_queue_alg alg)
अणु
	काष्ठा scsi_device *sdev = cmd->device;

	ahd_platक्रमm_set_tags(ahd, sdev, devinfo, alg);
	ahd_send_async(ahd, devinfo->channel, devinfo->target,
		       devinfo->lun, AC_TRANSFER_NEG);
पूर्ण

अटल व्योम
ahd_update_neg_table(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo,
		     काष्ठा ahd_transinfo *tinfo)
अणु
	ahd_mode_state	saved_modes;
	u_पूर्णांक		period;
	u_पूर्णांक		ppr_opts;
	u_पूर्णांक		con_opts;
	u_पूर्णांक		offset;
	u_पूर्णांक		saved_negoaddr;
	uपूर्णांक8_t		iocell_opts[माप(ahd->iocell_opts)];

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	saved_negoaddr = ahd_inb(ahd, NEGOADDR);
	ahd_outb(ahd, NEGOADDR, devinfo->target);
	period = tinfo->period;
	offset = tinfo->offset;
	स_नकल(iocell_opts, ahd->iocell_opts, माप(ahd->iocell_opts));
	ppr_opts = tinfo->ppr_options & (MSG_EXT_PPR_QAS_REQ|MSG_EXT_PPR_DT_REQ
					|MSG_EXT_PPR_IU_REQ|MSG_EXT_PPR_RTI);
	con_opts = 0;
	अगर (period == 0)
		period = AHD_SYNCRATE_ASYNC;
	अगर (period == AHD_SYNCRATE_160) अणु

		अगर ((ahd->bugs & AHD_PACED_NEGTABLE_BUG) != 0) अणु
			/*
			 * When the SPI4 spec was finalized, PACE transfers
			 * was not made a configurable option in the PPR
			 * message.  Instead it is assumed to be enabled क्रम
			 * any syncrate faster than 80MHz.  Nevertheless,
			 * Harpoon2A4 allows this to be configurable.
			 *
			 * Harpoon2A4 also assumes at most 2 data bytes per
			 * negotiated REQ/ACK offset.  Paced transfers take
			 * 4, so we must adjust our offset.
			 */
			ppr_opts |= PPROPT_PACE;
			offset *= 2;

			/*
			 * Harpoon2A assumed that there would be a
			 * fallback rate between 160MHz and 80MHz,
			 * so 7 is used as the period factor rather
			 * than 8 क्रम 160MHz.
			 */
			period = AHD_SYNCRATE_REVA_160;
		पूर्ण
		अगर ((tinfo->ppr_options & MSG_EXT_PPR_PCOMP_EN) == 0)
			iocell_opts[AHD_PRECOMP_SLEW_INDEX] &=
			    ~AHD_PRECOMP_MASK;
	पूर्ण अन्यथा अणु
		/*
		 * Precomp should be disabled क्रम non-paced transfers.
		 */
		iocell_opts[AHD_PRECOMP_SLEW_INDEX] &= ~AHD_PRECOMP_MASK;

		अगर ((ahd->features & AHD_NEW_IOCELL_OPTS) != 0
		 && (ppr_opts & MSG_EXT_PPR_DT_REQ) != 0
		 && (ppr_opts & MSG_EXT_PPR_IU_REQ) == 0) अणु
			/*
			 * Slow करोwn our CRC पूर्णांकerval to be
			 * compatible with non-packetized
			 * U160 devices that can't handle a
			 * CRC at full speed.
			 */
			con_opts |= ENSLOWCRC;
		पूर्ण

		अगर ((ahd->bugs & AHD_PACED_NEGTABLE_BUG) != 0) अणु
			/*
			 * On H2A4, revert to a slower slewrate
			 * on non-paced transfers.
			 */
			iocell_opts[AHD_PRECOMP_SLEW_INDEX] &=
			    ~AHD_SLEWRATE_MASK;
		पूर्ण
	पूर्ण

	ahd_outb(ahd, ANNEXCOL, AHD_ANNEXCOL_PRECOMP_SLEW);
	ahd_outb(ahd, ANNEXDAT, iocell_opts[AHD_PRECOMP_SLEW_INDEX]);
	ahd_outb(ahd, ANNEXCOL, AHD_ANNEXCOL_AMPLITUDE);
	ahd_outb(ahd, ANNEXDAT, iocell_opts[AHD_AMPLITUDE_INDEX]);

	ahd_outb(ahd, NEGPERIOD, period);
	ahd_outb(ahd, NEGPPROPTS, ppr_opts);
	ahd_outb(ahd, NEGOFFSET, offset);

	अगर (tinfo->width == MSG_EXT_WDTR_BUS_16_BIT)
		con_opts |= WIDEXFER;

	/*
	 * Slow करोwn our CRC पूर्णांकerval to be
	 * compatible with packetized U320 devices
	 * that can't handle a CRC at full speed
	 */
	अगर (ahd->features & AHD_AIC79XXB_SLOWCRC) अणु
		con_opts |= ENSLOWCRC;
	पूर्ण

	/*
	 * During packetized transfers, the target will
	 * give us the opportunity to send command packets
	 * without us निश्चितing attention.
	 */
	अगर ((tinfo->ppr_options & MSG_EXT_PPR_IU_REQ) == 0)
		con_opts |= ENAUTOATNO;
	ahd_outb(ahd, NEGCONOPTS, con_opts);
	ahd_outb(ahd, NEGOADDR, saved_negoaddr);
	ahd_restore_modes(ahd, saved_modes);
पूर्ण

/*
 * When the transfer settings क्रम a connection change, setup क्रम
 * negotiation in pending SCBs to effect the change as quickly as
 * possible.  We also cancel any negotiations that are scheduled
 * क्रम inflight SCBs that have not been started yet.
 */
अटल व्योम
ahd_update_pending_scbs(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा		scb *pending_scb;
	पूर्णांक		pending_scb_count;
	पूर्णांक		छोड़ोd;
	u_पूर्णांक		saved_scbptr;
	ahd_mode_state	saved_modes;

	/*
	 * Traverse the pending SCB list and ensure that all of the
	 * SCBs there have the proper settings.  We can only safely
	 * clear the negotiation required flag (setting requires the
	 * execution queue to be modअगरied) and this is only possible
	 * अगर we are not alपढ़ोy attempting to select out क्रम this
	 * SCB.  For this reason, all callers only call this routine
	 * अगर we are changing the negotiation settings क्रम the currently
	 * active transaction on the bus.
	 */
	pending_scb_count = 0;
	LIST_FOREACH(pending_scb, &ahd->pending_scbs, pending_links) अणु
		काष्ठा ahd_devinfo devinfo;
		काष्ठा ahd_पंचांगode_tstate *tstate;

		ahd_scb_devinfo(ahd, &devinfo, pending_scb);
		ahd_fetch_transinfo(ahd, devinfo.channel, devinfo.our_scsiid,
				    devinfo.target, &tstate);
		अगर ((tstate->स्वतः_negotiate & devinfo.target_mask) == 0
		 && (pending_scb->flags & SCB_AUTO_NEGOTIATE) != 0) अणु
			pending_scb->flags &= ~SCB_AUTO_NEGOTIATE;
			pending_scb->hscb->control &= ~MK_MESSAGE;
		पूर्ण
		ahd_sync_scb(ahd, pending_scb,
			     BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);
		pending_scb_count++;
	पूर्ण

	अगर (pending_scb_count == 0)
		वापस;

	अगर (ahd_is_छोड़ोd(ahd)) अणु
		छोड़ोd = 1;
	पूर्ण अन्यथा अणु
		छोड़ोd = 0;
		ahd_छोड़ो(ahd);
	पूर्ण

	/*
	 * Force the sequencer to reinitialize the selection क्रम
	 * the command at the head of the execution queue अगर it
	 * has alपढ़ोy been setup.  The negotiation changes may
	 * effect whether we select-out with ATN.  It is only
	 * safe to clear ENSELO when the bus is not मुक्त and no
	 * selection is in progres or completed.
	 */
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	अगर ((ahd_inb(ahd, SCSISIGI) & BSYI) != 0
	 && (ahd_inb(ahd, SSTAT0) & (SELDO|SELINGO)) == 0)
		ahd_outb(ahd, SCSISEQ0, ahd_inb(ahd, SCSISEQ0) & ~ENSELO);
	saved_scbptr = ahd_get_scbptr(ahd);
	/* Ensure that the hscbs करोwn on the card match the new inक्रमmation */
	LIST_FOREACH(pending_scb, &ahd->pending_scbs, pending_links) अणु
		u_पूर्णांक	scb_tag;
		u_पूर्णांक	control;

		scb_tag = SCB_GET_TAG(pending_scb);
		ahd_set_scbptr(ahd, scb_tag);
		control = ahd_inb_scbram(ahd, SCB_CONTROL);
		control &= ~MK_MESSAGE;
		control |= pending_scb->hscb->control & MK_MESSAGE;
		ahd_outb(ahd, SCB_CONTROL, control);
	पूर्ण
	ahd_set_scbptr(ahd, saved_scbptr);
	ahd_restore_modes(ahd, saved_modes);

	अगर (छोड़ोd == 0)
		ahd_unछोड़ो(ahd);
पूर्ण

/**************************** Pathing Inक्रमmation *****************************/
अटल व्योम
ahd_fetch_devinfo(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo)
अणु
	ahd_mode_state	saved_modes;
	u_पूर्णांक		saved_scsiid;
	role_t		role;
	पूर्णांक		our_id;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	अगर (ahd_inb(ahd, SSTAT0) & TARGET)
		role = ROLE_TARGET;
	अन्यथा
		role = ROLE_INITIATOR;

	अगर (role == ROLE_TARGET
	 && (ahd_inb(ahd, SEQ_FLAGS) & CMDPHASE_PENDING) != 0) अणु
		/* We were selected, so pull our id from TARGIDIN */
		our_id = ahd_inb(ahd, TARGIDIN) & OID;
	पूर्ण अन्यथा अगर (role == ROLE_TARGET)
		our_id = ahd_inb(ahd, TOWNID);
	अन्यथा
		our_id = ahd_inb(ahd, IOWNID);

	saved_scsiid = ahd_inb(ahd, SAVED_SCSIID);
	ahd_compile_devinfo(devinfo,
			    our_id,
			    SCSIID_TARGET(ahd, saved_scsiid),
			    ahd_inb(ahd, SAVED_LUN),
			    SCSIID_CHANNEL(ahd, saved_scsiid),
			    role);
	ahd_restore_modes(ahd, saved_modes);
पूर्ण

व्योम
ahd_prपूर्णांक_devinfo(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo)
अणु
	prपूर्णांकk("%s:%c:%d:%d: ", ahd_name(ahd), 'A',
	       devinfo->target, devinfo->lun);
पूर्ण

अटल स्थिर काष्ठा ahd_phase_table_entry*
ahd_lookup_phase_entry(पूर्णांक phase)
अणु
	स्थिर काष्ठा ahd_phase_table_entry *entry;
	स्थिर काष्ठा ahd_phase_table_entry *last_entry;

	/*
	 * num_phases करोesn't include the शेष entry which
	 * will be वापसed अगर the phase करोesn't match.
	 */
	last_entry = &ahd_phase_table[num_phases];
	क्रम (entry = ahd_phase_table; entry < last_entry; entry++) अणु
		अगर (phase == entry->phase)
			अवरोध;
	पूर्ण
	वापस (entry);
पूर्ण

व्योम
ahd_compile_devinfo(काष्ठा ahd_devinfo *devinfo, u_पूर्णांक our_id, u_पूर्णांक target,
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

अटल व्योम
ahd_scb_devinfo(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo,
		काष्ठा scb *scb)
अणु
	role_t	role;
	पूर्णांक	our_id;

	our_id = SCSIID_OUR_ID(scb->hscb->scsiid);
	role = ROLE_INITIATOR;
	अगर ((scb->hscb->control & TARGET_SCB) != 0)
		role = ROLE_TARGET;
	ahd_compile_devinfo(devinfo, our_id, SCB_GET_TARGET(ahd, scb),
			    SCB_GET_LUN(scb), SCB_GET_CHANNEL(ahd, scb), role);
पूर्ण


/************************ Message Phase Processing ****************************/
/*
 * When an initiator transaction with the MK_MESSAGE flag either reconnects
 * or enters the initial message out phase, we are पूर्णांकerrupted.  Fill our
 * outgoing message buffer with the appropriate message and beging handing
 * the message phase(s) manually.
 */
अटल व्योम
ahd_setup_initiator_msgout(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo,
			   काष्ठा scb *scb)
अणु
	/*
	 * To facilitate adding multiple messages together,
	 * each routine should increment the index and len
	 * variables instead of setting them explicitly.
	 */
	ahd->msgout_index = 0;
	ahd->msgout_len = 0;

	अगर (ahd_currently_packetized(ahd))
		ahd->msg_flags |= MSG_FLAG_PACKETIZED;

	अगर (ahd->send_msg_लिखो_त्रुटि
	 && ahd_inb(ahd, MSG_OUT) == HOST_MSG) अणु
		ahd->msgout_buf[ahd->msgout_index++] = ahd->send_msg_लिखो_त्रुटि;
		ahd->msgout_len++;
		ahd->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
			prपूर्णांकk("Setting up for Parity Error delivery\n");
#पूर्ण_अगर
		वापस;
	पूर्ण अन्यथा अगर (scb == शून्य) अणु
		prपूर्णांकk("%s: WARNING. No pending message for "
		       "I_T msgin.  Issuing NO-OP\n", ahd_name(ahd));
		ahd->msgout_buf[ahd->msgout_index++] = NOP;
		ahd->msgout_len++;
		ahd->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
		वापस;
	पूर्ण

	अगर ((scb->flags & SCB_DEVICE_RESET) == 0
	 && (scb->flags & SCB_PACKETIZED) == 0
	 && ahd_inb(ahd, MSG_OUT) == MSG_IDENTIFYFLAG) अणु
		u_पूर्णांक identअगरy_msg;

		identअगरy_msg = MSG_IDENTIFYFLAG | SCB_GET_LUN(scb);
		अगर ((scb->hscb->control & DISCENB) != 0)
			identअगरy_msg |= MSG_IDENTIFY_DISCFLAG;
		ahd->msgout_buf[ahd->msgout_index++] = identअगरy_msg;
		ahd->msgout_len++;

		अगर ((scb->hscb->control & TAG_ENB) != 0) अणु
			ahd->msgout_buf[ahd->msgout_index++] =
			    scb->hscb->control & (TAG_ENB|SCB_TAG_TYPE);
			ahd->msgout_buf[ahd->msgout_index++] = SCB_GET_TAG(scb);
			ahd->msgout_len += 2;
		पूर्ण
	पूर्ण

	अगर (scb->flags & SCB_DEVICE_RESET) अणु
		ahd->msgout_buf[ahd->msgout_index++] = TARGET_RESET;
		ahd->msgout_len++;
		ahd_prपूर्णांक_path(ahd, scb);
		prपूर्णांकk("Bus Device Reset Message Sent\n");
		/*
		 * Clear our selection hardware in advance of
		 * the busमुक्त.  We may have an entry in the रुकोing
		 * Q क्रम this target, and we करोn't want to go about
		 * selecting जबतक we handle the busमुक्त and blow it
		 * away.
		 */
		ahd_outb(ahd, SCSISEQ0, 0);
	पूर्ण अन्यथा अगर ((scb->flags & SCB_ABORT) != 0) अणु

		अगर ((scb->hscb->control & TAG_ENB) != 0) अणु
			ahd->msgout_buf[ahd->msgout_index++] = ABORT_TASK;
		पूर्ण अन्यथा अणु
			ahd->msgout_buf[ahd->msgout_index++] = ABORT_TASK_SET;
		पूर्ण
		ahd->msgout_len++;
		ahd_prपूर्णांक_path(ahd, scb);
		prपूर्णांकk("Abort%s Message Sent\n",
		       (scb->hscb->control & TAG_ENB) != 0 ? " Tag" : "");
		/*
		 * Clear our selection hardware in advance of
		 * the busमुक्त.  We may have an entry in the रुकोing
		 * Q क्रम this target, and we करोn't want to go about
		 * selecting जबतक we handle the busमुक्त and blow it
		 * away.
		 */
		ahd_outb(ahd, SCSISEQ0, 0);
	पूर्ण अन्यथा अगर ((scb->flags & (SCB_AUTO_NEGOTIATE|SCB_NEGOTIATE)) != 0) अणु
		ahd_build_transfer_msg(ahd, devinfo);
		/*
		 * Clear our selection hardware in advance of potential
		 * PPR IU status change busमुक्त.  We may have an entry in
		 * the रुकोing Q क्रम this target, and we करोn't want to go
		 * about selecting जबतक we handle the busमुक्त and blow
		 * it away.
		 */
		ahd_outb(ahd, SCSISEQ0, 0);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("ahd_intr: AWAITING_MSG for an SCB that "
		       "does not have a waiting message\n");
		prपूर्णांकk("SCSIID = %x, target_mask = %x\n", scb->hscb->scsiid,
		       devinfo->target_mask);
		panic("SCB = %d, SCB Control = %x:%x, MSG_OUT = %x "
		      "SCB flags = %x", SCB_GET_TAG(scb), scb->hscb->control,
		      ahd_inb_scbram(ahd, SCB_CONTROL), ahd_inb(ahd, MSG_OUT),
		      scb->flags);
	पूर्ण

	/*
	 * Clear the MK_MESSAGE flag from the SCB so we aren't
	 * asked to send this message again.
	 */
	ahd_outb(ahd, SCB_CONTROL,
		 ahd_inb_scbram(ahd, SCB_CONTROL) & ~MK_MESSAGE);
	scb->hscb->control &= ~MK_MESSAGE;
	ahd->msgout_index = 0;
	ahd->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
पूर्ण

/*
 * Build an appropriate transfer negotiation message क्रम the
 * currently active target.
 */
अटल व्योम
ahd_build_transfer_msg(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo)
अणु
	/*
	 * We need to initiate transfer negotiations.
	 * If our current and goal settings are identical,
	 * we want to renegotiate due to a check condition.
	 */
	काष्ठा	ahd_initiator_tinfo *tinfo;
	काष्ठा	ahd_पंचांगode_tstate *tstate;
	पूर्णांक	करोwide;
	पूर्णांक	करोsync;
	पूर्णांक	करोppr;
	u_पूर्णांक	period;
	u_पूर्णांक	ppr_options;
	u_पूर्णांक	offset;

	tinfo = ahd_fetch_transinfo(ahd, devinfo->channel, devinfo->our_scsiid,
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
	ahd_devlimited_syncrate(ahd, tinfo, &period,
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
		अगर ((ahd->features & AHD_WIDE) != 0)
			करोwide = 1;
		अन्यथा
			करोsync = 1;

		अगर (bootverbose) अणु
			ahd_prपूर्णांक_devinfo(ahd, devinfo);
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
		ahd_validate_offset(ahd, tinfo, period, &offset,
				    करोppr ? tinfo->goal.width
					  : tinfo->curr.width,
				    devinfo->role);
		अगर (करोppr) अणु
			ahd_स्थिरruct_ppr(ahd, devinfo, period, offset,
					  tinfo->goal.width, ppr_options);
		पूर्ण अन्यथा अणु
			ahd_स्थिरruct_sdtr(ahd, devinfo, period, offset);
		पूर्ण
	पूर्ण अन्यथा अणु
		ahd_स्थिरruct_wdtr(ahd, devinfo, tinfo->goal.width);
	पूर्ण
पूर्ण

/*
 * Build a synchronous negotiation message in our message
 * buffer based on the input parameters.
 */
अटल व्योम
ahd_स्थिरruct_sdtr(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo,
		   u_पूर्णांक period, u_पूर्णांक offset)
अणु
	अगर (offset == 0)
		period = AHD_ASYNC_XFER_PERIOD;
	ahd->msgout_index += spi_populate_sync_msg(
			ahd->msgout_buf + ahd->msgout_index, period, offset);
	ahd->msgout_len += 5;
	अगर (bootverbose) अणु
		prपूर्णांकk("(%s:%c:%d:%d): Sending SDTR period %x, offset %x\n",
		       ahd_name(ahd), devinfo->channel, devinfo->target,
		       devinfo->lun, period, offset);
	पूर्ण
पूर्ण

/*
 * Build a wide negotiateion message in our message
 * buffer based on the input parameters.
 */
अटल व्योम
ahd_स्थिरruct_wdtr(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo,
		   u_पूर्णांक bus_width)
अणु
	ahd->msgout_index += spi_populate_width_msg(
			ahd->msgout_buf + ahd->msgout_index, bus_width);
	ahd->msgout_len += 4;
	अगर (bootverbose) अणु
		prपूर्णांकk("(%s:%c:%d:%d): Sending WDTR %x\n",
		       ahd_name(ahd), devinfo->channel, devinfo->target,
		       devinfo->lun, bus_width);
	पूर्ण
पूर्ण

/*
 * Build a parallel protocol request message in our message
 * buffer based on the input parameters.
 */
अटल व्योम
ahd_स्थिरruct_ppr(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo,
		  u_पूर्णांक period, u_पूर्णांक offset, u_पूर्णांक bus_width,
		  u_पूर्णांक ppr_options)
अणु
	/*
	 * Always request precompensation from
	 * the other target अगर we are running
	 * at paced syncrates.
	 */
	अगर (period <= AHD_SYNCRATE_PACED)
		ppr_options |= MSG_EXT_PPR_PCOMP_EN;
	अगर (offset == 0)
		period = AHD_ASYNC_XFER_PERIOD;
	ahd->msgout_index += spi_populate_ppr_msg(
			ahd->msgout_buf + ahd->msgout_index, period, offset,
			bus_width, ppr_options);
	ahd->msgout_len += 8;
	अगर (bootverbose) अणु
		prपूर्णांकk("(%s:%c:%d:%d): Sending PPR bus_width %x, period %x, "
		       "offset %x, ppr_options %x\n", ahd_name(ahd),
		       devinfo->channel, devinfo->target, devinfo->lun,
		       bus_width, period, offset, ppr_options);
	पूर्ण
पूर्ण

/*
 * Clear any active message state.
 */
अटल व्योम
ahd_clear_msg_state(काष्ठा ahd_softc *ahd)
अणु
	ahd_mode_state saved_modes;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd->send_msg_लिखो_त्रुटि = 0;
	ahd->msg_flags = MSG_FLAG_NONE;
	ahd->msgout_len = 0;
	ahd->msgin_index = 0;
	ahd->msg_type = MSG_TYPE_NONE;
	अगर ((ahd_inb(ahd, SCSISIGO) & ATNO) != 0) अणु
		/*
		 * The target didn't care to respond to our
		 * message request, so clear ATN.
		 */
		ahd_outb(ahd, CLRSINT1, CLRATNO);
	पूर्ण
	ahd_outb(ahd, MSG_OUT, NOP);
	ahd_outb(ahd, SEQ_FLAGS2,
		 ahd_inb(ahd, SEQ_FLAGS2) & ~TARGET_MSG_PENDING);
	ahd_restore_modes(ahd, saved_modes);
पूर्ण

/*
 * Manual message loop handler.
 */
अटल व्योम
ahd_handle_message_phase(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा	ahd_devinfo devinfo;
	u_पूर्णांक	bus_phase;
	पूर्णांक	end_session;

	ahd_fetch_devinfo(ahd, &devinfo);
	end_session = FALSE;
	bus_phase = ahd_inb(ahd, LASTPHASE);

	अगर ((ahd_inb(ahd, LQISTAT2) & LQIPHASE_OUTPKT) != 0) अणु
		prपूर्णांकk("LQIRETRY for LQIPHASE_OUTPKT\n");
		ahd_outb(ahd, LQCTL2, LQIRETRY);
	पूर्ण
reचयन:
	चयन (ahd->msg_type) अणु
	हाल MSG_TYPE_INITIATOR_MSGOUT:
	अणु
		पूर्णांक lastbyte;
		पूर्णांक phasemis;
		पूर्णांक msgकरोne;

		अगर (ahd->msgout_len == 0 && ahd->send_msg_लिखो_त्रुटि == 0)
			panic("HOST_MSG_LOOP interrupt with no active message");

#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0) अणु
			ahd_prपूर्णांक_devinfo(ahd, &devinfo);
			prपूर्णांकk("INITIATOR_MSG_OUT");
		पूर्ण
#पूर्ण_अगर
		phasemis = bus_phase != P_MESGOUT;
		अगर (phasemis) अणु
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0) अणु
				prपूर्णांकk(" PHASEMIS %s\n",
				       ahd_lookup_phase_entry(bus_phase)
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
				ahd_outb(ahd, CLRSINT1, CLRATNO);
				ahd->send_msg_लिखो_त्रुटि = 0;
				ahd->msg_type = MSG_TYPE_INITIATOR_MSGIN;
				ahd->msgin_index = 0;
				जाओ reचयन;
			पूर्ण
			end_session = TRUE;
			अवरोध;
		पूर्ण

		अगर (ahd->send_msg_लिखो_त्रुटि) अणु
			ahd_outb(ahd, CLRSINT1, CLRATNO);
			ahd_outb(ahd, CLRSINT1, CLRREQINIT);
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
				prपूर्णांकk(" byte 0x%x\n", ahd->send_msg_लिखो_त्रुटि);
#पूर्ण_अगर
			/*
			 * If we are notअगरying the target of a CRC error
			 * during packetized operations, the target is
			 * within its rights to acknowledge our message
			 * with a busमुक्त.
			 */
			अगर ((ahd->msg_flags & MSG_FLAG_PACKETIZED) != 0
			 && ahd->send_msg_लिखो_त्रुटि == INITIATOR_ERROR)
				ahd->msg_flags |= MSG_FLAG_EXPECT_IDE_BUSFREE;

			ahd_outb(ahd, RETURN_2, ahd->send_msg_लिखो_त्रुटि);
			ahd_outb(ahd, RETURN_1, CONT_MSG_LOOP_WRITE);
			अवरोध;
		पूर्ण

		msgकरोne	= ahd->msgout_index == ahd->msgout_len;
		अगर (msgकरोne) अणु
			/*
			 * The target has requested a retry.
			 * Re-निश्चित ATN, reset our message index to
			 * 0, and try again.
			 */
			ahd->msgout_index = 0;
			ahd_निश्चित_atn(ahd);
		पूर्ण

		lastbyte = ahd->msgout_index == (ahd->msgout_len - 1);
		अगर (lastbyte) अणु
			/* Last byte is signअगरied by dropping ATN */
			ahd_outb(ahd, CLRSINT1, CLRATNO);
		पूर्ण

		/*
		 * Clear our पूर्णांकerrupt status and present
		 * the next byte on the bus.
		 */
		ahd_outb(ahd, CLRSINT1, CLRREQINIT);
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
			prपूर्णांकk(" byte 0x%x\n",
			       ahd->msgout_buf[ahd->msgout_index]);
#पूर्ण_अगर
		ahd_outb(ahd, RETURN_2, ahd->msgout_buf[ahd->msgout_index++]);
		ahd_outb(ahd, RETURN_1, CONT_MSG_LOOP_WRITE);
		अवरोध;
	पूर्ण
	हाल MSG_TYPE_INITIATOR_MSGIN:
	अणु
		पूर्णांक phasemis;
		पूर्णांक message_करोne;

#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0) अणु
			ahd_prपूर्णांक_devinfo(ahd, &devinfo);
			prपूर्णांकk("INITIATOR_MSG_IN");
		पूर्ण
#पूर्ण_अगर
		phasemis = bus_phase != P_MESGIN;
		अगर (phasemis) अणु
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0) अणु
				prपूर्णांकk(" PHASEMIS %s\n",
				       ahd_lookup_phase_entry(bus_phase)
							     ->phasemsg);
			पूर्ण
#पूर्ण_अगर
			ahd->msgin_index = 0;
			अगर (bus_phase == P_MESGOUT
			 && (ahd->send_msg_लिखो_त्रुटि != 0
			  || (ahd->msgout_len != 0
			   && ahd->msgout_index == 0))) अणु
				ahd->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
				जाओ reचयन;
			पूर्ण
			end_session = TRUE;
			अवरोध;
		पूर्ण

		/* Pull the byte in without acking it */
		ahd->msgin_buf[ahd->msgin_index] = ahd_inb(ahd, SCSIBUS);
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
			prपूर्णांकk(" byte 0x%x\n",
			       ahd->msgin_buf[ahd->msgin_index]);
#पूर्ण_अगर

		message_करोne = ahd_parse_msg(ahd, &devinfo);

		अगर (message_करोne) अणु
			/*
			 * Clear our incoming message buffer in हाल there
			 * is another message following this one.
			 */
			ahd->msgin_index = 0;

			/*
			 * If this message illicited a response,
			 * निश्चित ATN so the target takes us to the
			 * message out phase.
			 */
			अगर (ahd->msgout_len != 0) अणु
#अगर_घोषित AHD_DEBUG
				अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0) अणु
					ahd_prपूर्णांक_devinfo(ahd, &devinfo);
					prपूर्णांकk("Asserting ATN for response\n");
				पूर्ण
#पूर्ण_अगर
				ahd_निश्चित_atn(ahd);
			पूर्ण
		पूर्ण अन्यथा
			ahd->msgin_index++;

		अगर (message_करोne == MSGLOOP_TERMINATED) अणु
			end_session = TRUE;
		पूर्ण अन्यथा अणु
			/* Ack the byte */
			ahd_outb(ahd, CLRSINT1, CLRREQINIT);
			ahd_outb(ahd, RETURN_1, CONT_MSG_LOOP_READ);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल MSG_TYPE_TARGET_MSGIN:
	अणु
		पूर्णांक msgकरोne;
		पूर्णांक msgout_request;

		/*
		 * By शेष, the message loop will जारी.
		 */
		ahd_outb(ahd, RETURN_1, CONT_MSG_LOOP_TARG);

		अगर (ahd->msgout_len == 0)
			panic("Target MSGIN with no active message");

		/*
		 * If we पूर्णांकerrupted a mesgout session, the initiator
		 * will not know this until our first REQ.  So, we
		 * only honor mesgout requests after we've sent our
		 * first byte.
		 */
		अगर ((ahd_inb(ahd, SCSISIGI) & ATNI) != 0
		 && ahd->msgout_index > 0)
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
			ahd->msg_type = MSG_TYPE_TARGET_MSGOUT;
			ahd_outb(ahd, SCSISIGO, P_MESGOUT | BSYO);
			ahd->msgin_index = 0;
			/* Dummy पढ़ो to REQ क्रम first byte */
			ahd_inb(ahd, SCSIDAT);
			ahd_outb(ahd, SXFRCTL0,
				 ahd_inb(ahd, SXFRCTL0) | SPIOEN);
			अवरोध;
		पूर्ण

		msgकरोne = ahd->msgout_index == ahd->msgout_len;
		अगर (msgकरोne) अणु
			ahd_outb(ahd, SXFRCTL0,
				 ahd_inb(ahd, SXFRCTL0) & ~SPIOEN);
			end_session = TRUE;
			अवरोध;
		पूर्ण

		/*
		 * Present the next byte on the bus.
		 */
		ahd_outb(ahd, SXFRCTL0, ahd_inb(ahd, SXFRCTL0) | SPIOEN);
		ahd_outb(ahd, SCSIDAT, ahd->msgout_buf[ahd->msgout_index++]);
		अवरोध;
	पूर्ण
	हाल MSG_TYPE_TARGET_MSGOUT:
	अणु
		पूर्णांक lastbyte;
		पूर्णांक msgकरोne;

		/*
		 * By शेष, the message loop will जारी.
		 */
		ahd_outb(ahd, RETURN_1, CONT_MSG_LOOP_TARG);

		/*
		 * The initiator संकेतs that this is
		 * the last byte by dropping ATN.
		 */
		lastbyte = (ahd_inb(ahd, SCSISIGI) & ATNI) == 0;

		/*
		 * Read the latched byte, but turn off SPIOEN first
		 * so that we करोn't inadvertently cause a REQ क्रम the
		 * next byte.
		 */
		ahd_outb(ahd, SXFRCTL0, ahd_inb(ahd, SXFRCTL0) & ~SPIOEN);
		ahd->msgin_buf[ahd->msgin_index] = ahd_inb(ahd, SCSIDAT);
		msgकरोne = ahd_parse_msg(ahd, &devinfo);
		अगर (msgकरोne == MSGLOOP_TERMINATED) अणु
			/*
			 * The message is *really* करोne in that it caused
			 * us to go to bus मुक्त.  The sequencer has alपढ़ोy
			 * been reset at this poपूर्णांक, so pull the ejection
			 * handle.
			 */
			वापस;
		पूर्ण

		ahd->msgin_index++;

		/*
		 * XXX Read spec about initiator dropping ATN too soon
		 *     and use msgकरोne to detect it.
		 */
		अगर (msgकरोne == MSGLOOP_MSGCOMPLETE) अणु
			ahd->msgin_index = 0;

			/*
			 * If this message illicited a response, transition
			 * to the Message in phase and send it.
			 */
			अगर (ahd->msgout_len != 0) अणु
				ahd_outb(ahd, SCSISIGO, P_MESGIN | BSYO);
				ahd_outb(ahd, SXFRCTL0,
					 ahd_inb(ahd, SXFRCTL0) | SPIOEN);
				ahd->msg_type = MSG_TYPE_TARGET_MSGIN;
				ahd->msgin_index = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (lastbyte)
			end_session = TRUE;
		अन्यथा अणु
			/* Ask क्रम the next byte. */
			ahd_outb(ahd, SXFRCTL0,
				 ahd_inb(ahd, SXFRCTL0) | SPIOEN);
		पूर्ण

		अवरोध;
	पूर्ण
	शेष:
		panic("Unknown REQINIT message type");
	पूर्ण

	अगर (end_session) अणु
		अगर ((ahd->msg_flags & MSG_FLAG_PACKETIZED) != 0) अणु
			prपूर्णांकk("%s: Returning to Idle Loop\n",
			       ahd_name(ahd));
			ahd_clear_msg_state(ahd);

			/*
			 * Perक्रमm the equivalent of a clear_target_state.
			 */
			ahd_outb(ahd, LASTPHASE, P_BUSFREE);
			ahd_outb(ahd, SEQ_FLAGS, NOT_IDENTIFIED|NO_CDB_SENT);
			ahd_outb(ahd, SEQCTL0, FASTMODE|SEQRESET);
		पूर्ण अन्यथा अणु
			ahd_clear_msg_state(ahd);
			ahd_outb(ahd, RETURN_1, EXIT_MSG_LOOP);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * See अगर we sent a particular extended message to the target.
 * If "full" is true, वापस true only अगर the target saw the full
 * message.  If "full" is false, वापस true अगर the target saw at
 * least the first byte of the message.
 */
अटल पूर्णांक
ahd_sent_msg(काष्ठा ahd_softc *ahd, ahd_msgtype type, u_पूर्णांक msgval, पूर्णांक full)
अणु
	पूर्णांक found;
	u_पूर्णांक index;

	found = FALSE;
	index = 0;

	जबतक (index < ahd->msgout_len) अणु
		अगर (ahd->msgout_buf[index] == EXTENDED_MESSAGE) अणु
			u_पूर्णांक end_index;

			end_index = index + 1 + ahd->msgout_buf[index + 1];
			अगर (ahd->msgout_buf[index+2] == msgval
			 && type == AHDMSG_EXT) अणु

				अगर (full) अणु
					अगर (ahd->msgout_index > end_index)
						found = TRUE;
				पूर्ण अन्यथा अगर (ahd->msgout_index > index)
					found = TRUE;
			पूर्ण
			index = end_index;
		पूर्ण अन्यथा अगर (ahd->msgout_buf[index] >= SIMPLE_QUEUE_TAG
			&& ahd->msgout_buf[index] <= IGNORE_WIDE_RESIDUE) अणु

			/* Skip tag type and tag id or residue param*/
			index += 2;
		पूर्ण अन्यथा अणु
			/* Single byte message */
			अगर (type == AHDMSG_1B
			 && ahd->msgout_index > index
			 && (ahd->msgout_buf[index] == msgval
			  || ((ahd->msgout_buf[index] & MSG_IDENTIFYFLAG) != 0
			   && msgval == MSG_IDENTIFYFLAG)))
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
ahd_parse_msg(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo)
अणु
	काष्ठा	ahd_initiator_tinfo *tinfo;
	काष्ठा	ahd_पंचांगode_tstate *tstate;
	पूर्णांक	reject;
	पूर्णांक	करोne;
	पूर्णांक	response;

	करोne = MSGLOOP_IN_PROG;
	response = FALSE;
	reject = FALSE;
	tinfo = ahd_fetch_transinfo(ahd, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);

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
	चयन (ahd->msgin_buf[0]) अणु
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
		response = ahd_handle_msg_reject(ahd, devinfo);
		fallthrough;
	हाल NOP:
		करोne = MSGLOOP_MSGCOMPLETE;
		अवरोध;
	हाल EXTENDED_MESSAGE:
	अणु
		/* Wait क्रम enough of the message to begin validation */
		अगर (ahd->msgin_index < 2)
			अवरोध;
		चयन (ahd->msgin_buf[2]) अणु
		हाल EXTENDED_SDTR:
		अणु
			u_पूर्णांक	 period;
			u_पूर्णांक	 ppr_options;
			u_पूर्णांक	 offset;
			u_पूर्णांक	 saved_offset;

			अगर (ahd->msgin_buf[1] != MSG_EXT_SDTR_LEN) अणु
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
			अगर (ahd->msgin_index < (MSG_EXT_SDTR_LEN + 1))
				अवरोध;

			period = ahd->msgin_buf[3];
			ppr_options = 0;
			saved_offset = offset = ahd->msgin_buf[4];
			ahd_devlimited_syncrate(ahd, tinfo, &period,
						&ppr_options, devinfo->role);
			ahd_validate_offset(ahd, tinfo, period, &offset,
					    tinfo->curr.width, devinfo->role);
			अगर (bootverbose) अणु
				prपूर्णांकk("(%s:%c:%d:%d): Received "
				       "SDTR period %x, offset %x\n\t"
				       "Filtered to period %x, offset %x\n",
				       ahd_name(ahd), devinfo->channel,
				       devinfo->target, devinfo->lun,
				       ahd->msgin_buf[3], saved_offset,
				       period, offset);
			पूर्ण
			ahd_set_syncrate(ahd, devinfo, period,
					 offset, ppr_options,
					 AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
					 /*छोड़ोd*/TRUE);

			/*
			 * See अगर we initiated Sync Negotiation
			 * and didn't have to fall करोwn to async
			 * transfers.
			 */
			अगर (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_SDTR, TRUE)) अणु
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
					       ahd_name(ahd), devinfo->channel,
					       devinfo->target, devinfo->lun);
				पूर्ण
				ahd->msgout_index = 0;
				ahd->msgout_len = 0;
				ahd_स्थिरruct_sdtr(ahd, devinfo,
						   period, offset);
				ahd->msgout_index = 0;
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
			अगर (ahd->msgin_buf[1] != MSG_EXT_WDTR_LEN) अणु
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
			अगर (ahd->msgin_index < (MSG_EXT_WDTR_LEN + 1))
				अवरोध;

			bus_width = ahd->msgin_buf[3];
			saved_width = bus_width;
			ahd_validate_width(ahd, tinfo, &bus_width,
					   devinfo->role);
			अगर (bootverbose) अणु
				prपूर्णांकk("(%s:%c:%d:%d): Received WDTR "
				       "%x filtered to %x\n",
				       ahd_name(ahd), devinfo->channel,
				       devinfo->target, devinfo->lun,
				       saved_width, bus_width);
			पूर्ण

			अगर (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_WDTR, TRUE)) अणु
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
					       ahd_name(ahd), devinfo->channel,
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
					       ahd_name(ahd), devinfo->channel,
					       devinfo->target, devinfo->lun);
				पूर्ण
				ahd->msgout_index = 0;
				ahd->msgout_len = 0;
				ahd_स्थिरruct_wdtr(ahd, devinfo, bus_width);
				ahd->msgout_index = 0;
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
			ahd_update_neg_request(ahd, devinfo, tstate,
					       tinfo, AHD_NEG_ALWAYS);
			ahd_set_width(ahd, devinfo, bus_width,
				      AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
				      /*छोड़ोd*/TRUE);
			अगर (sending_reply == FALSE && reject == FALSE) अणु

				/*
				 * We will always have an SDTR to send.
				 */
				ahd->msgout_index = 0;
				ahd->msgout_len = 0;
				ahd_build_transfer_msg(ahd, devinfo);
				ahd->msgout_index = 0;
				response = TRUE;
			पूर्ण
			करोne = MSGLOOP_MSGCOMPLETE;
			अवरोध;
		पूर्ण
		हाल EXTENDED_PPR:
		अणु
			u_पूर्णांक	period;
			u_पूर्णांक	offset;
			u_पूर्णांक	bus_width;
			u_पूर्णांक	ppr_options;
			u_पूर्णांक	saved_width;
			u_पूर्णांक	saved_offset;
			u_पूर्णांक	saved_ppr_options;

			अगर (ahd->msgin_buf[1] != MSG_EXT_PPR_LEN) अणु
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
			अगर (ahd->msgin_index < (MSG_EXT_PPR_LEN + 1))
				अवरोध;

			period = ahd->msgin_buf[3];
			offset = ahd->msgin_buf[5];
			bus_width = ahd->msgin_buf[6];
			saved_width = bus_width;
			ppr_options = ahd->msgin_buf[7];
			/*
			 * According to the spec, a DT only
			 * period factor with no DT option
			 * set implies async.
			 */
			अगर ((ppr_options & MSG_EXT_PPR_DT_REQ) == 0
			 && period <= 9)
				offset = 0;
			saved_ppr_options = ppr_options;
			saved_offset = offset;

			/*
			 * Transfer options are only available अगर we
			 * are negotiating wide.
			 */
			अगर (bus_width == 0)
				ppr_options &= MSG_EXT_PPR_QAS_REQ;

			ahd_validate_width(ahd, tinfo, &bus_width,
					   devinfo->role);
			ahd_devlimited_syncrate(ahd, tinfo, &period,
						&ppr_options, devinfo->role);
			ahd_validate_offset(ahd, tinfo, period, &offset,
					    bus_width, devinfo->role);

			अगर (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_PPR, TRUE)) अणु
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
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (devinfo->role != ROLE_TARGET)
					prपूर्णांकk("(%s:%c:%d:%d): Target "
					       "Initiated PPR\n",
					       ahd_name(ahd), devinfo->channel,
					       devinfo->target, devinfo->lun);
				अन्यथा
					prपूर्णांकk("(%s:%c:%d:%d): Initiator "
					       "Initiated PPR\n",
					       ahd_name(ahd), devinfo->channel,
					       devinfo->target, devinfo->lun);
				ahd->msgout_index = 0;
				ahd->msgout_len = 0;
				ahd_स्थिरruct_ppr(ahd, devinfo, period, offset,
						  bus_width, ppr_options);
				ahd->msgout_index = 0;
				response = TRUE;
			पूर्ण
			अगर (bootverbose) अणु
				prपूर्णांकk("(%s:%c:%d:%d): Received PPR width %x, "
				       "period %x, offset %x,options %x\n"
				       "\tFiltered to width %x, period %x, "
				       "offset %x, options %x\n",
				       ahd_name(ahd), devinfo->channel,
				       devinfo->target, devinfo->lun,
				       saved_width, ahd->msgin_buf[3],
				       saved_offset, saved_ppr_options,
				       bus_width, period, offset, ppr_options);
			पूर्ण
			ahd_set_width(ahd, devinfo, bus_width,
				      AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
				      /*छोड़ोd*/TRUE);
			ahd_set_syncrate(ahd, devinfo, period,
					 offset, ppr_options,
					 AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
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
#अगर_घोषित AHD_TARGET_MODE
	हाल TARGET_RESET:
		ahd_handle_devreset(ahd, devinfo, CAM_LUN_WILDCARD,
				    CAM_BDR_SENT,
				    "Bus Device Reset Received",
				    /*verbose_level*/0);
		ahd_restart(ahd);
		करोne = MSGLOOP_TERMINATED;
		अवरोध;
	हाल ABORT_TASK:
	हाल ABORT_TASK_SET:
	हाल CLEAR_TASK_SET:
	अणु
		पूर्णांक tag;

		/* Target mode messages */
		अगर (devinfo->role != ROLE_TARGET) अणु
			reject = TRUE;
			अवरोध;
		पूर्ण
		tag = SCB_LIST_शून्य;
		अगर (ahd->msgin_buf[0] == ABORT_TASK)
			tag = ahd_inb(ahd, INITIATOR_TAG);
		ahd_पात_scbs(ahd, devinfo->target, devinfo->channel,
			       devinfo->lun, tag, ROLE_TARGET,
			       CAM_REQ_ABORTED);

		tstate = ahd->enabled_tarमाला_लो[devinfo->our_scsiid];
		अगर (tstate != शून्य) अणु
			काष्ठा ahd_पंचांगode_lstate* lstate;

			lstate = tstate->enabled_luns[devinfo->lun];
			अगर (lstate != शून्य) अणु
				ahd_queue_lstate_event(ahd, lstate,
						       devinfo->our_scsiid,
						       ahd->msgin_buf[0],
						       /*arg*/tag);
				ahd_send_lstate_events(ahd, lstate);
			पूर्ण
		पूर्ण
		ahd_restart(ahd);
		करोne = MSGLOOP_TERMINATED;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल QAS_REQUEST:
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
			prपूर्णांकk("%s: QAS request.  SCSISIGI == 0x%x\n",
			       ahd_name(ahd), ahd_inb(ahd, SCSISIGI));
#पूर्ण_अगर
		ahd->msg_flags |= MSG_FLAG_EXPECT_QASREJ_BUSFREE;
		fallthrough;
	हाल TERMINATE_IO_PROC:
	शेष:
		reject = TRUE;
		अवरोध;
	पूर्ण

	अगर (reject) अणु
		/*
		 * Setup to reject the message.
		 */
		ahd->msgout_index = 0;
		ahd->msgout_len = 1;
		ahd->msgout_buf[0] = MESSAGE_REJECT;
		करोne = MSGLOOP_MSGCOMPLETE;
		response = TRUE;
	पूर्ण

	अगर (करोne != MSGLOOP_IN_PROG && !response)
		/* Clear the outgoing message buffer */
		ahd->msgout_len = 0;

	वापस (करोne);
पूर्ण

/*
 * Process a message reject message.
 */
अटल पूर्णांक
ahd_handle_msg_reject(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo)
अणु
	/*
	 * What we care about here is अगर we had an
	 * outstanding SDTR or WDTR message क्रम this
	 * target.  If we did, this is a संकेत that
	 * the target is refusing negotiation.
	 */
	काष्ठा scb *scb;
	काष्ठा ahd_initiator_tinfo *tinfo;
	काष्ठा ahd_पंचांगode_tstate *tstate;
	u_पूर्णांक scb_index;
	u_पूर्णांक last_msg;
	पूर्णांक   response = 0;

	scb_index = ahd_get_scbptr(ahd);
	scb = ahd_lookup_scb(ahd, scb_index);
	tinfo = ahd_fetch_transinfo(ahd, devinfo->channel,
				    devinfo->our_scsiid,
				    devinfo->target, &tstate);
	/* Might be necessary */
	last_msg = ahd_inb(ahd, LAST_MSG);

	अगर (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_PPR, /*full*/FALSE)) अणु
		अगर (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_PPR, /*full*/TRUE)
		 && tinfo->goal.period <= AHD_SYNCRATE_PACED) अणु
			/*
			 * Target may not like our SPI-4 PPR Options.
			 * Attempt to negotiate 80MHz which will turn
			 * off these options.
			 */
			अगर (bootverbose) अणु
				prपूर्णांकk("(%s:%c:%d:%d): PPR Rejected. "
				       "Trying simple U160 PPR\n",
				       ahd_name(ahd), devinfo->channel,
				       devinfo->target, devinfo->lun);
			पूर्ण
			tinfo->goal.period = AHD_SYNCRATE_DT;
			tinfo->goal.ppr_options &= MSG_EXT_PPR_IU_REQ
						|  MSG_EXT_PPR_QAS_REQ
						|  MSG_EXT_PPR_DT_REQ;
		पूर्ण अन्यथा अणु
			/*
			 * Target करोes not support the PPR message.
			 * Attempt to negotiate SPI-2 style.
			 */
			अगर (bootverbose) अणु
				prपूर्णांकk("(%s:%c:%d:%d): PPR Rejected. "
				       "Trying WDTR/SDTR\n",
				       ahd_name(ahd), devinfo->channel,
				       devinfo->target, devinfo->lun);
			पूर्ण
			tinfo->goal.ppr_options = 0;
			tinfo->curr.transport_version = 2;
			tinfo->goal.transport_version = 2;
		पूर्ण
		ahd->msgout_index = 0;
		ahd->msgout_len = 0;
		ahd_build_transfer_msg(ahd, devinfo);
		ahd->msgout_index = 0;
		response = 1;
	पूर्ण अन्यथा अगर (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_WDTR, /*full*/FALSE)) अणु

		/* note 8bit xfers */
		prपूर्णांकk("(%s:%c:%d:%d): refuses WIDE negotiation.  Using "
		       "8bit transfers\n", ahd_name(ahd),
		       devinfo->channel, devinfo->target, devinfo->lun);
		ahd_set_width(ahd, devinfo, MSG_EXT_WDTR_BUS_8_BIT,
			      AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
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
			ahd->msgout_index = 0;
			ahd->msgout_len = 0;
			ahd_build_transfer_msg(ahd, devinfo);
			ahd->msgout_index = 0;
			response = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (ahd_sent_msg(ahd, AHDMSG_EXT, EXTENDED_SDTR, /*full*/FALSE)) अणु
		/* note asynch xfers and clear flag */
		ahd_set_syncrate(ahd, devinfo, /*period*/0,
				 /*offset*/0, /*ppr_options*/0,
				 AHD_TRANS_ACTIVE|AHD_TRANS_GOAL,
				 /*छोड़ोd*/TRUE);
		prपूर्णांकk("(%s:%c:%d:%d): refuses synchronous negotiation. "
		       "Using asynchronous transfers\n",
		       ahd_name(ahd), devinfo->channel,
		       devinfo->target, devinfo->lun);
	पूर्ण अन्यथा अगर ((scb->hscb->control & SIMPLE_QUEUE_TAG) != 0) अणु
		पूर्णांक tag_type;
		पूर्णांक mask;

		tag_type = (scb->hscb->control & SIMPLE_QUEUE_TAG);

		अगर (tag_type == SIMPLE_QUEUE_TAG) अणु
			prपूर्णांकk("(%s:%c:%d:%d): refuses tagged commands.  "
			       "Performing non-tagged I/O\n", ahd_name(ahd),
			       devinfo->channel, devinfo->target, devinfo->lun);
			ahd_set_tags(ahd, scb->io_ctx, devinfo, AHD_QUEUE_NONE);
			mask = ~0x23;
		पूर्ण अन्यथा अणु
			prपूर्णांकk("(%s:%c:%d:%d): refuses %s tagged commands.  "
			       "Performing simple queue tagged I/O only\n",
			       ahd_name(ahd), devinfo->channel, devinfo->target,
			       devinfo->lun, tag_type == ORDERED_QUEUE_TAG
			       ? "ordered" : "head of queue");
			ahd_set_tags(ahd, scb->io_ctx, devinfo, AHD_QUEUE_BASIC);
			mask = ~0x03;
		पूर्ण

		/*
		 * Resend the identअगरy क्रम this CCB as the target
		 * may believe that the selection is invalid otherwise.
		 */
		ahd_outb(ahd, SCB_CONTROL,
			 ahd_inb_scbram(ahd, SCB_CONTROL) & mask);
		scb->hscb->control &= mask;
		ahd_set_transaction_tag(scb, /*enabled*/FALSE,
					/*type*/SIMPLE_QUEUE_TAG);
		ahd_outb(ahd, MSG_OUT, MSG_IDENTIFYFLAG);
		ahd_निश्चित_atn(ahd);
		ahd_busy_tcl(ahd, BUILD_TCL(scb->hscb->scsiid, devinfo->lun),
			     SCB_GET_TAG(scb));

		/*
		 * Requeue all tagged commands क्रम this target
		 * currently in our possession so they can be
		 * converted to untagged commands.
		 */
		ahd_search_qinfअगरo(ahd, SCB_GET_TARGET(ahd, scb),
				   SCB_GET_CHANNEL(ahd, scb),
				   SCB_GET_LUN(scb), /*tag*/SCB_LIST_शून्य,
				   ROLE_INITIATOR, CAM_REQUEUE_REQ,
				   SEARCH_COMPLETE);
	पूर्ण अन्यथा अगर (ahd_sent_msg(ahd, AHDMSG_1B, MSG_IDENTIFYFLAG, TRUE)) अणु
		/*
		 * Most likely the device believes that we had
		 * previously negotiated packetized.
		 */
		ahd->msg_flags |= MSG_FLAG_EXPECT_PPR_BUSFREE
			       |  MSG_FLAG_IU_REQ_CHANGED;

		ahd_क्रमce_renegotiation(ahd, devinfo);
		ahd->msgout_index = 0;
		ahd->msgout_len = 0;
		ahd_build_transfer_msg(ahd, devinfo);
		ahd->msgout_index = 0;
		response = 1;
	पूर्ण अन्यथा अणु
		/*
		 * Otherwise, we ignore it.
		 */
		prपूर्णांकk("%s:%c:%d: Message reject for %x -- ignored\n",
		       ahd_name(ahd), devinfo->channel, devinfo->target,
		       last_msg);
	पूर्ण
	वापस (response);
पूर्ण

/*
 * Process an ingnore wide residue message.
 */
अटल व्योम
ahd_handle_ign_wide_residue(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo)
अणु
	u_पूर्णांक scb_index;
	काष्ठा scb *scb;

	scb_index = ahd_get_scbptr(ahd);
	scb = ahd_lookup_scb(ahd, scb_index);
	/*
	 * XXX Actually check data direction in the sequencer?
	 * Perhaps add datadir to some spare bits in the hscb?
	 */
	अगर ((ahd_inb(ahd, SEQ_FLAGS) & DPHASE) == 0
	 || ahd_get_transfer_dir(scb) != CAM_सूची_IN) अणु
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

		sgptr = ahd_inb_scbram(ahd, SCB_RESIDUAL_SGPTR);
		अगर ((sgptr & SG_LIST_शून्य) != 0
		 && (ahd_inb_scbram(ahd, SCB_TASK_ATTRIBUTE)
		     & SCB_XFERLEN_ODD) != 0) अणु
			/*
			 * If the residual occurred on the last
			 * transfer and the transfer request was
			 * expected to end on an odd count, करो
			 * nothing.
			 */
		पूर्ण अन्यथा अणु
			uपूर्णांक32_t data_cnt;
			uपूर्णांक64_t data_addr;
			uपूर्णांक32_t sglen;

			/* Pull in the rest of the sgptr */
			sgptr = ahd_inl_scbram(ahd, SCB_RESIDUAL_SGPTR);
			data_cnt = ahd_inl_scbram(ahd, SCB_RESIDUAL_DATACNT);
			अगर ((sgptr & SG_LIST_शून्य) != 0) अणु
				/*
				 * The residual data count is not updated
				 * क्रम the command run to completion हाल.
				 * Explicitly zero the count.
				 */
				data_cnt &= ~AHD_SG_LEN_MASK;
			पूर्ण
			data_addr = ahd_inq(ahd, SHADDR);
			data_cnt += 1;
			data_addr -= 1;
			sgptr &= SG_PTR_MASK;
			अगर ((ahd->flags & AHD_64BIT_ADDRESSING) != 0) अणु
				काष्ठा ahd_dma64_seg *sg;

				sg = ahd_sg_bus_to_virt(ahd, scb, sgptr);

				/*
				 * The residual sg ptr poपूर्णांकs to the next S/G
				 * to load so we must go back one.
				 */
				sg--;
				sglen = ahd_le32toh(sg->len) & AHD_SG_LEN_MASK;
				अगर (sg != scb->sg_list
				 && sglen < (data_cnt & AHD_SG_LEN_MASK)) अणु

					sg--;
					sglen = ahd_le32toh(sg->len);
					/*
					 * Preserve High Address and SG_LIST
					 * bits जबतक setting the count to 1.
					 */
					data_cnt = 1|(sglen&(~AHD_SG_LEN_MASK));
					data_addr = ahd_le64toh(sg->addr)
						  + (sglen & AHD_SG_LEN_MASK)
						  - 1;

					/*
					 * Increment sg so it poपूर्णांकs to the
					 * "next" sg.
					 */
					sg++;
					sgptr = ahd_sg_virt_to_bus(ahd, scb,
								   sg);
				पूर्ण
			पूर्ण अन्यथा अणु
				काष्ठा ahd_dma_seg *sg;

				sg = ahd_sg_bus_to_virt(ahd, scb, sgptr);

				/*
				 * The residual sg ptr poपूर्णांकs to the next S/G
				 * to load so we must go back one.
				 */
				sg--;
				sglen = ahd_le32toh(sg->len) & AHD_SG_LEN_MASK;
				अगर (sg != scb->sg_list
				 && sglen < (data_cnt & AHD_SG_LEN_MASK)) अणु

					sg--;
					sglen = ahd_le32toh(sg->len);
					/*
					 * Preserve High Address and SG_LIST
					 * bits जबतक setting the count to 1.
					 */
					data_cnt = 1|(sglen&(~AHD_SG_LEN_MASK));
					data_addr = ahd_le32toh(sg->addr)
						  + (sglen & AHD_SG_LEN_MASK)
						  - 1;

					/*
					 * Increment sg so it poपूर्णांकs to the
					 * "next" sg.
					 */
					sg++;
					sgptr = ahd_sg_virt_to_bus(ahd, scb,
								  sg);
				पूर्ण
			पूर्ण
			/*
			 * Toggle the "oddness" of the transfer length
			 * to handle this mid-transfer ignore wide
			 * residue.  This ensures that the oddness is
			 * correct क्रम subsequent data transfers.
			 */
			ahd_outb(ahd, SCB_TASK_ATTRIBUTE,
			    ahd_inb_scbram(ahd, SCB_TASK_ATTRIBUTE)
			    ^ SCB_XFERLEN_ODD);

			ahd_outl(ahd, SCB_RESIDUAL_SGPTR, sgptr);
			ahd_outl(ahd, SCB_RESIDUAL_DATACNT, data_cnt);
			/*
			 * The FIFO's poपूर्णांकers will be updated अगर/when the
			 * sequencer re-enters a data phase.
			 */
		पूर्ण
	पूर्ण
पूर्ण


/*
 * Reinitialize the data poपूर्णांकers क्रम the active transfer
 * based on its current residual.
 */
अटल व्योम
ahd_reinitialize_dataptrs(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा		 scb *scb;
	ahd_mode_state	 saved_modes;
	u_पूर्णांक		 scb_index;
	u_पूर्णांक		 रुको;
	uपूर्णांक32_t	 sgptr;
	uपूर्णांक32_t	 resid;
	uपूर्णांक64_t	 dataptr;

	AHD_ASSERT_MODES(ahd, AHD_MODE_DFF0_MSK|AHD_MODE_DFF1_MSK,
			 AHD_MODE_DFF0_MSK|AHD_MODE_DFF1_MSK);

	scb_index = ahd_get_scbptr(ahd);
	scb = ahd_lookup_scb(ahd, scb_index);

	/*
	 * Release and reacquire the FIFO so we
	 * have a clean slate.
	 */
	ahd_outb(ahd, DFFSXFRCTL, CLRCHN);
	रुको = 1000;
	जबतक (--रुको && !(ahd_inb(ahd, MDFFSTAT) & FIFOFREE))
		ahd_delay(100);
	अगर (रुको == 0) अणु
		ahd_prपूर्णांक_path(ahd, scb);
		prपूर्णांकk("ahd_reinitialize_dataptrs: Forcing FIFO free.\n");
		ahd_outb(ahd, DFFSXFRCTL, RSTCHN|CLRSHCNT);
	पूर्ण
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, DFFSTAT,
		 ahd_inb(ahd, DFFSTAT)
		| (saved_modes == 0x11 ? CURRFIFO_1 : CURRFIFO_0));

	/*
	 * Determine initial values क्रम data_addr and data_cnt
	 * क्रम resuming the data phase.
	 */
	sgptr = ahd_inl_scbram(ahd, SCB_RESIDUAL_SGPTR);
	sgptr &= SG_PTR_MASK;

	resid = (ahd_inb_scbram(ahd, SCB_RESIDUAL_DATACNT + 2) << 16)
	      | (ahd_inb_scbram(ahd, SCB_RESIDUAL_DATACNT + 1) << 8)
	      | ahd_inb_scbram(ahd, SCB_RESIDUAL_DATACNT);

	अगर ((ahd->flags & AHD_64BIT_ADDRESSING) != 0) अणु
		काष्ठा ahd_dma64_seg *sg;

		sg = ahd_sg_bus_to_virt(ahd, scb, sgptr);

		/* The residual sg_ptr always poपूर्णांकs to the next sg */
		sg--;

		dataptr = ahd_le64toh(sg->addr)
			+ (ahd_le32toh(sg->len) & AHD_SG_LEN_MASK)
			- resid;
		ahd_outl(ahd, HADDR + 4, dataptr >> 32);
	पूर्ण अन्यथा अणु
		काष्ठा	 ahd_dma_seg *sg;

		sg = ahd_sg_bus_to_virt(ahd, scb, sgptr);

		/* The residual sg_ptr always poपूर्णांकs to the next sg */
		sg--;

		dataptr = ahd_le32toh(sg->addr)
			+ (ahd_le32toh(sg->len) & AHD_SG_LEN_MASK)
			- resid;
		ahd_outb(ahd, HADDR + 4,
			 (ahd_le32toh(sg->len) & ~AHD_SG_LEN_MASK) >> 24);
	पूर्ण
	ahd_outl(ahd, HADDR, dataptr);
	ahd_outb(ahd, HCNT + 2, resid >> 16);
	ahd_outb(ahd, HCNT + 1, resid >> 8);
	ahd_outb(ahd, HCNT, resid);
पूर्ण

/*
 * Handle the effects of issuing a bus device reset message.
 */
अटल व्योम
ahd_handle_devreset(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo,
		    u_पूर्णांक lun, cam_status status, अक्षर *message,
		    पूर्णांक verbose_level)
अणु
#अगर_घोषित AHD_TARGET_MODE
	काष्ठा ahd_पंचांगode_tstate* tstate;
#पूर्ण_अगर
	पूर्णांक found;

	found = ahd_पात_scbs(ahd, devinfo->target, devinfo->channel,
			       lun, SCB_LIST_शून्य, devinfo->role,
			       status);

#अगर_घोषित AHD_TARGET_MODE
	/*
	 * Send an immediate notअगरy ccb to all target mord peripheral
	 * drivers affected by this action.
	 */
	tstate = ahd->enabled_tarमाला_लो[devinfo->our_scsiid];
	अगर (tstate != शून्य) अणु
		u_पूर्णांक cur_lun;
		u_पूर्णांक max_lun;

		अगर (lun != CAM_LUN_WILDCARD) अणु
			cur_lun = 0;
			max_lun = AHD_NUM_LUNS - 1;
		पूर्ण अन्यथा अणु
			cur_lun = lun;
			max_lun = lun;
		पूर्ण
		क्रम (;cur_lun <= max_lun; cur_lun++) अणु
			काष्ठा ahd_पंचांगode_lstate* lstate;

			lstate = tstate->enabled_luns[cur_lun];
			अगर (lstate == शून्य)
				जारी;

			ahd_queue_lstate_event(ahd, lstate, devinfo->our_scsiid,
					       TARGET_RESET, /*arg*/0);
			ahd_send_lstate_events(ahd, lstate);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * Go back to async/narrow transfers and renegotiate.
	 */
	ahd_set_width(ahd, devinfo, MSG_EXT_WDTR_BUS_8_BIT,
		      AHD_TRANS_CUR, /*छोड़ोd*/TRUE);
	ahd_set_syncrate(ahd, devinfo, /*period*/0, /*offset*/0,
			 /*ppr_options*/0, AHD_TRANS_CUR,
			 /*छोड़ोd*/TRUE);

	अगर (status != CAM_SEL_TIMEOUT)
		ahd_send_async(ahd, devinfo->channel, devinfo->target,
			       CAM_LUN_WILDCARD, AC_SENT_BDR);

	अगर (message != शून्य && bootverbose)
		prपूर्णांकk("%s: %s on %c:%d. %d SCBs aborted\n", ahd_name(ahd),
		       message, devinfo->channel, devinfo->target, found);
पूर्ण

#अगर_घोषित AHD_TARGET_MODE
अटल व्योम
ahd_setup_target_msgin(काष्ठा ahd_softc *ahd, काष्ठा ahd_devinfo *devinfo,
		       काष्ठा scb *scb)
अणु

	/*
	 * To facilitate adding multiple messages together,
	 * each routine should increment the index and len
	 * variables instead of setting them explicitly.
	 */
	ahd->msgout_index = 0;
	ahd->msgout_len = 0;

	अगर (scb != शून्य && (scb->flags & SCB_AUTO_NEGOTIATE) != 0)
		ahd_build_transfer_msg(ahd, devinfo);
	अन्यथा
		panic("ahd_intr: AWAITING target message with no message");

	ahd->msgout_index = 0;
	ahd->msg_type = MSG_TYPE_TARGET_MSGIN;
पूर्ण
#पूर्ण_अगर
/**************************** Initialization **********************************/
अटल u_पूर्णांक
ahd_sglist_size(काष्ठा ahd_softc *ahd)
अणु
	bus_माप_प्रकार list_size;

	list_size = माप(काष्ठा ahd_dma_seg) * AHD_NSEG;
	अगर ((ahd->flags & AHD_64BIT_ADDRESSING) != 0)
		list_size = माप(काष्ठा ahd_dma64_seg) * AHD_NSEG;
	वापस (list_size);
पूर्ण

/*
 * Calculate the optimum S/G List allocation size.  S/G elements used
 * क्रम a given transaction must be physically contiguous.  Assume the
 * OS will allocate full pages to us, so it करोesn't make sense to request
 * less than a page.
 */
अटल u_पूर्णांक
ahd_sglist_allocsize(काष्ठा ahd_softc *ahd)
अणु
	bus_माप_प्रकार sg_list_increment;
	bus_माप_प्रकार sg_list_size;
	bus_माप_प्रकार max_list_size;
	bus_माप_प्रकार best_list_size;

	/* Start out with the minimum required क्रम AHD_NSEG. */
	sg_list_increment = ahd_sglist_size(ahd);
	sg_list_size = sg_list_increment;

	/* Get us as बंद as possible to a page in size. */
	जबतक ((sg_list_size + sg_list_increment) <= PAGE_SIZE)
		sg_list_size += sg_list_increment;

	/*
	 * Try to reduce the amount of wastage by allocating
	 * multiple pages.
	 */
	best_list_size = sg_list_size;
	max_list_size = roundup(sg_list_increment, PAGE_SIZE);
	अगर (max_list_size < 4 * PAGE_SIZE)
		max_list_size = 4 * PAGE_SIZE;
	अगर (max_list_size > (AHD_SCB_MAX_ALLOC * sg_list_increment))
		max_list_size = (AHD_SCB_MAX_ALLOC * sg_list_increment);
	जबतक ((sg_list_size + sg_list_increment) <= max_list_size
	   &&  (sg_list_size % PAGE_SIZE) != 0) अणु
		bus_माप_प्रकार new_mod;
		bus_माप_प्रकार best_mod;

		sg_list_size += sg_list_increment;
		new_mod = sg_list_size % PAGE_SIZE;
		best_mod = best_list_size % PAGE_SIZE;
		अगर (new_mod > best_mod || new_mod == 0) अणु
			best_list_size = sg_list_size;
		पूर्ण
	पूर्ण
	वापस (best_list_size);
पूर्ण

/*
 * Allocate a controller काष्ठाure क्रम a new device
 * and perक्रमm initial initializion.
 */
काष्ठा ahd_softc *
ahd_alloc(व्योम *platक्रमm_arg, अक्षर *name)
अणु
	काष्ठा  ahd_softc *ahd;

	ahd = kzalloc(माप(*ahd), GFP_ATOMIC);
	अगर (!ahd) अणु
		prपूर्णांकk("aic7xxx: cannot malloc softc!\n");
		kमुक्त(name);
		वापस शून्य;
	पूर्ण

	ahd->seep_config = kदो_स्मृति(माप(*ahd->seep_config), GFP_ATOMIC);
	अगर (ahd->seep_config == शून्य) अणु
		kमुक्त(ahd);
		kमुक्त(name);
		वापस (शून्य);
	पूर्ण
	LIST_INIT(&ahd->pending_scbs);
	/* We करोn't know our unit number until the OSM sets it */
	ahd->name = name;
	ahd->unit = -1;
	ahd->description = शून्य;
	ahd->bus_description = शून्य;
	ahd->channel = 'A';
	ahd->chip = AHD_NONE;
	ahd->features = AHD_FENONE;
	ahd->bugs = AHD_BUGNONE;
	ahd->flags = AHD_SPCHK_ENB_A|AHD_RESET_BUS_A|AHD_TERM_ENB_A
		   | AHD_EXTENDED_TRANS_A|AHD_STPWLEVEL_A;
	समयr_setup(&ahd->stat_समयr, ahd_stat_समयr, 0);
	ahd->पूर्णांक_coalescing_समयr = AHD_INT_COALESCING_TIMER_DEFAULT;
	ahd->पूर्णांक_coalescing_maxcmds = AHD_INT_COALESCING_MAXCMDS_DEFAULT;
	ahd->पूर्णांक_coalescing_mincmds = AHD_INT_COALESCING_MINCMDS_DEFAULT;
	ahd->पूर्णांक_coalescing_threshold = AHD_INT_COALESCING_THRESHOLD_DEFAULT;
	ahd->पूर्णांक_coalescing_stop_threshold =
	    AHD_INT_COALESCING_STOP_THRESHOLD_DEFAULT;

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_MEMORY) != 0) अणु
		prपूर्णांकk("%s: scb size = 0x%x, hscb size = 0x%x\n",
		       ahd_name(ahd), (u_पूर्णांक)माप(काष्ठा scb),
		       (u_पूर्णांक)माप(काष्ठा hardware_scb));
	पूर्ण
#पूर्ण_अगर
	अगर (ahd_platक्रमm_alloc(ahd, platक्रमm_arg) != 0) अणु
		ahd_मुक्त(ahd);
		ahd = शून्य;
	पूर्ण
	वापस (ahd);
पूर्ण

पूर्णांक
ahd_softc_init(काष्ठा ahd_softc *ahd)
अणु

	ahd->unछोड़ो = 0;
	ahd->छोड़ो = PAUSE;
	वापस (0);
पूर्ण

व्योम
ahd_set_unit(काष्ठा ahd_softc *ahd, पूर्णांक unit)
अणु
	ahd->unit = unit;
पूर्ण

व्योम
ahd_set_name(काष्ठा ahd_softc *ahd, अक्षर *name)
अणु
	kमुक्त(ahd->name);
	ahd->name = name;
पूर्ण

व्योम
ahd_मुक्त(काष्ठा ahd_softc *ahd)
अणु
	पूर्णांक i;

	चयन (ahd->init_level) अणु
	शेष:
	हाल 5:
		ahd_shutकरोwn(ahd);
		fallthrough;
	हाल 4:
		ahd_dmamap_unload(ahd, ahd->shared_data_dmat,
				  ahd->shared_data_map.dmamap);
		fallthrough;
	हाल 3:
		ahd_dmamem_मुक्त(ahd, ahd->shared_data_dmat, ahd->qoutfअगरo,
				ahd->shared_data_map.dmamap);
		ahd_dmamap_destroy(ahd, ahd->shared_data_dmat,
				   ahd->shared_data_map.dmamap);
		fallthrough;
	हाल 2:
		ahd_dma_tag_destroy(ahd, ahd->shared_data_dmat);
		अवरोध;
	हाल 1:
		अवरोध;
	हाल 0:
		अवरोध;
	पूर्ण

	ahd_platक्रमm_मुक्त(ahd);
	ahd_fini_scbdata(ahd);
	क्रम (i = 0; i < AHD_NUM_TARGETS; i++) अणु
		काष्ठा ahd_पंचांगode_tstate *tstate;

		tstate = ahd->enabled_tarमाला_लो[i];
		अगर (tstate != शून्य) अणु
#अगर_घोषित AHD_TARGET_MODE
			पूर्णांक j;

			क्रम (j = 0; j < AHD_NUM_LUNS; j++) अणु
				काष्ठा ahd_पंचांगode_lstate *lstate;

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
#अगर_घोषित AHD_TARGET_MODE
	अगर (ahd->black_hole != शून्य) अणु
		xpt_मुक्त_path(ahd->black_hole->path);
		kमुक्त(ahd->black_hole);
	पूर्ण
#पूर्ण_अगर
	kमुक्त(ahd->name);
	kमुक्त(ahd->seep_config);
	kमुक्त(ahd->saved_stack);
	kमुक्त(ahd);
	वापस;
पूर्ण

अटल व्योम
ahd_shutकरोwn(व्योम *arg)
अणु
	काष्ठा	ahd_softc *ahd;

	ahd = (काष्ठा ahd_softc *)arg;

	/*
	 * Stop periodic समयr callbacks.
	 */
	del_समयr_sync(&ahd->stat_समयr);

	/* This will reset most रेजिस्टरs to 0, but not all */
	ahd_reset(ahd, /*reinit*/FALSE);
पूर्ण

/*
 * Reset the controller and record some inक्रमmation about it
 * that is only available just after a reset.  If "reinit" is
 * non-zero, this reset occurred after initial configuration
 * and the caller requests that the chip be fully reinitialized
 * to a runable state.  Chip पूर्णांकerrupts are *not* enabled after
 * a reinitialization.  The caller must enable पूर्णांकerrupts via
 * ahd_पूर्णांकr_enable().
 */
पूर्णांक
ahd_reset(काष्ठा ahd_softc *ahd, पूर्णांक reinit)
अणु
	u_पूर्णांक	 sxfrctl1;
	पूर्णांक	 रुको;
	uपूर्णांक32_t cmd;

	/*
	 * Preserve the value of the SXFRCTL1 रेजिस्टर क्रम all channels.
	 * It contains settings that affect termination and we करोn't want
	 * to disturb the पूर्णांकegrity of the bus.
	 */
	ahd_छोड़ो(ahd);
	ahd_update_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	sxfrctl1 = ahd_inb(ahd, SXFRCTL1);

	cmd = ahd_pci_पढ़ो_config(ahd->dev_softc, PCIR_COMMAND, /*bytes*/2);
	अगर ((ahd->bugs & AHD_PCIX_CHIPRST_BUG) != 0) अणु
		uपूर्णांक32_t mod_cmd;

		/*
		 * A4 Razor #632
		 * During the निश्चितion of CHIPRST, the chip
		 * करोes not disable its parity logic prior to
		 * the start of the reset.  This may cause a
		 * parity error to be detected and thus a
		 * spurious SERR or PERR निश्चितion.  Disable
		 * PERR and SERR responses during the CHIPRST.
		 */
		mod_cmd = cmd & ~(PCIM_CMD_PERRESPEN|PCIM_CMD_SERRESPEN);
		ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_COMMAND,
				     mod_cmd, /*bytes*/2);
	पूर्ण
	ahd_outb(ahd, HCNTRL, CHIPRST | ahd->छोड़ो);

	/*
	 * Ensure that the reset has finished.  We delay 1000us
	 * prior to पढ़ोing the रेजिस्टर to make sure the chip
	 * has sufficiently completed its reset to handle रेजिस्टर
	 * accesses.
	 */
	रुको = 1000;
	करो अणु
		ahd_delay(1000);
	पूर्ण जबतक (--रुको && !(ahd_inb(ahd, HCNTRL) & CHIPRSTACK));

	अगर (रुको == 0) अणु
		prपूर्णांकk("%s: WARNING - Failed chip reset!  "
		       "Trying to initialize anyway.\n", ahd_name(ahd));
	पूर्ण
	ahd_outb(ahd, HCNTRL, ahd->छोड़ो);

	अगर ((ahd->bugs & AHD_PCIX_CHIPRST_BUG) != 0) अणु
		/*
		 * Clear any latched PCI error status and restore
		 * previous SERR and PERR response enables.
		 */
		ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_STATUS + 1,
				     0xFF, /*bytes*/1);
		ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_COMMAND,
				     cmd, /*bytes*/2);
	पूर्ण

	/*
	 * Mode should be SCSI after a chip reset, but lets
	 * set it just to be safe.  We touch the MODE_PTR
	 * रेजिस्टर directly so as to bypass the lazy update
	 * code in ahd_set_modes().
	 */
	ahd_known_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, MODE_PTR,
		 ahd_build_mode_state(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI));

	/*
	 * Restore SXFRCTL1.
	 *
	 * We must always initialize STPWEN to 1 beक्रमe we
	 * restore the saved values.  STPWEN is initialized
	 * to a tri-state condition which can only be cleared
	 * by turning it on.
	 */
	ahd_outb(ahd, SXFRCTL1, sxfrctl1|STPWEN);
	ahd_outb(ahd, SXFRCTL1, sxfrctl1);

	/* Determine chip configuration */
	ahd->features &= ~AHD_WIDE;
	अगर ((ahd_inb(ahd, SBLKCTL) & SELWIDE) != 0)
		ahd->features |= AHD_WIDE;

	/*
	 * If a recovery action has क्रमced a chip reset,
	 * re-initialize the chip to our liking.
	 */
	अगर (reinit != 0)
		ahd_chip_init(ahd);

	वापस (0);
पूर्ण

/*
 * Determine the number of SCBs available on the controller
 */
अटल पूर्णांक
ahd_probe_scbs(काष्ठा ahd_softc *ahd) अणु
	पूर्णांक i;

	AHD_ASSERT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
			 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
	क्रम (i = 0; i < AHD_SCB_MAX; i++) अणु
		पूर्णांक j;

		ahd_set_scbptr(ahd, i);
		ahd_outw(ahd, SCB_BASE, i);
		क्रम (j = 2; j < 64; j++)
			ahd_outb(ahd, SCB_BASE+j, 0);
		/* Start out lअगरe as unallocated (needing an पात) */
		ahd_outb(ahd, SCB_CONTROL, MK_MESSAGE);
		अगर (ahd_inw_scbram(ahd, SCB_BASE) != i)
			अवरोध;
		ahd_set_scbptr(ahd, 0);
		अगर (ahd_inw_scbram(ahd, SCB_BASE) != 0)
			अवरोध;
	पूर्ण
	वापस (i);
पूर्ण

अटल व्योम
ahd_dmamap_cb(व्योम *arg, bus_dma_segment_t *segs, पूर्णांक nseg, पूर्णांक error) 
अणु
	dma_addr_t *baddr;

	baddr = (dma_addr_t *)arg;
	*baddr = segs->ds_addr;
पूर्ण

अटल व्योम
ahd_initialize_hscbs(काष्ठा ahd_softc *ahd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ahd->scb_data.maxhscbs; i++) अणु
		ahd_set_scbptr(ahd, i);

		/* Clear the control byte. */
		ahd_outb(ahd, SCB_CONTROL, 0);

		/* Set the next poपूर्णांकer */
		ahd_outw(ahd, SCB_NEXT, SCB_LIST_शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक
ahd_init_scbdata(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा	scb_data *scb_data;
	पूर्णांक	i;

	scb_data = &ahd->scb_data;
	TAILQ_INIT(&scb_data->मुक्त_scbs);
	क्रम (i = 0; i < AHD_NUM_TARGETS * AHD_NUM_LUNS_NONPKT; i++)
		LIST_INIT(&scb_data->मुक्त_scb_lists[i]);
	LIST_INIT(&scb_data->any_dev_मुक्त_scb_list);
	SLIST_INIT(&scb_data->hscb_maps);
	SLIST_INIT(&scb_data->sg_maps);
	SLIST_INIT(&scb_data->sense_maps);

	/* Determine the number of hardware SCBs and initialize them */
	scb_data->maxhscbs = ahd_probe_scbs(ahd);
	अगर (scb_data->maxhscbs == 0) अणु
		prपूर्णांकk("%s: No SCB space found\n", ahd_name(ahd));
		वापस (ENXIO);
	पूर्ण

	ahd_initialize_hscbs(ahd);

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
	अगर (ahd_dma_tag_create(ahd, ahd->parent_dmat, /*alignment*/1,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/शून्य, /*filterarg*/शून्य,
			       PAGE_SIZE, /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &scb_data->hscb_dmat) != 0) अणु
		जाओ error_निकास;
	पूर्ण

	scb_data->init_level++;

	/* DMA tag क्रम our S/G काष्ठाures. */
	अगर (ahd_dma_tag_create(ahd, ahd->parent_dmat, /*alignment*/8,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/शून्य, /*filterarg*/शून्य,
			       ahd_sglist_allocsize(ahd), /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &scb_data->sg_dmat) != 0) अणु
		जाओ error_निकास;
	पूर्ण
#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_MEMORY) != 0)
		prपूर्णांकk("%s: ahd_sglist_allocsize = 0x%x\n", ahd_name(ahd),
		       ahd_sglist_allocsize(ahd));
#पूर्ण_अगर

	scb_data->init_level++;

	/* DMA tag क्रम our sense buffers.  We allocate in page sized chunks */
	अगर (ahd_dma_tag_create(ahd, ahd->parent_dmat, /*alignment*/1,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/शून्य, /*filterarg*/शून्य,
			       PAGE_SIZE, /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &scb_data->sense_dmat) != 0) अणु
		जाओ error_निकास;
	पूर्ण

	scb_data->init_level++;

	/* Perक्रमm initial CCB allocation */
	ahd_alloc_scbs(ahd);

	अगर (scb_data->numscbs == 0) अणु
		prपूर्णांकk("%s: ahd_init_scbdata - "
		       "Unable to allocate initial scbs\n",
		       ahd_name(ahd));
		जाओ error_निकास;
	पूर्ण

	/*
	 * Note that we were successful
	 */
	वापस (0);

error_निकास:

	वापस (ENOMEM);
पूर्ण

अटल काष्ठा scb *
ahd_find_scb_by_tag(काष्ठा ahd_softc *ahd, u_पूर्णांक tag)
अणु
	काष्ठा scb *scb;

	/*
	 * Look on the pending list.
	 */
	LIST_FOREACH(scb, &ahd->pending_scbs, pending_links) अणु
		अगर (SCB_GET_TAG(scb) == tag)
			वापस (scb);
	पूर्ण

	/*
	 * Then on all of the collision मुक्त lists.
	 */
	TAILQ_FOREACH(scb, &ahd->scb_data.मुक्त_scbs, links.tqe) अणु
		काष्ठा scb *list_scb;

		list_scb = scb;
		करो अणु
			अगर (SCB_GET_TAG(list_scb) == tag)
				वापस (list_scb);
			list_scb = LIST_NEXT(list_scb, collision_links);
		पूर्ण जबतक (list_scb);
	पूर्ण

	/*
	 * And finally on the generic मुक्त list.
	 */
	LIST_FOREACH(scb, &ahd->scb_data.any_dev_मुक्त_scb_list, links.le) अणु
		अगर (SCB_GET_TAG(scb) == tag)
			वापस (scb);
	पूर्ण

	वापस (शून्य);
पूर्ण

अटल व्योम
ahd_fini_scbdata(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा scb_data *scb_data;

	scb_data = &ahd->scb_data;
	अगर (scb_data == शून्य)
		वापस;

	चयन (scb_data->init_level) अणु
	शेष:
	हाल 7:
	अणु
		काष्ठा map_node *sns_map;

		जबतक ((sns_map = SLIST_FIRST(&scb_data->sense_maps)) != शून्य) अणु
			SLIST_REMOVE_HEAD(&scb_data->sense_maps, links);
			ahd_dmamap_unload(ahd, scb_data->sense_dmat,
					  sns_map->dmamap);
			ahd_dmamem_मुक्त(ahd, scb_data->sense_dmat,
					sns_map->vaddr, sns_map->dmamap);
			kमुक्त(sns_map);
		पूर्ण
		ahd_dma_tag_destroy(ahd, scb_data->sense_dmat);
	पूर्ण
		fallthrough;
	हाल 6:
	अणु
		काष्ठा map_node *sg_map;

		जबतक ((sg_map = SLIST_FIRST(&scb_data->sg_maps)) != शून्य) अणु
			SLIST_REMOVE_HEAD(&scb_data->sg_maps, links);
			ahd_dmamap_unload(ahd, scb_data->sg_dmat,
					  sg_map->dmamap);
			ahd_dmamem_मुक्त(ahd, scb_data->sg_dmat,
					sg_map->vaddr, sg_map->dmamap);
			kमुक्त(sg_map);
		पूर्ण
		ahd_dma_tag_destroy(ahd, scb_data->sg_dmat);
	पूर्ण
		fallthrough;
	हाल 5:
	अणु
		काष्ठा map_node *hscb_map;

		जबतक ((hscb_map = SLIST_FIRST(&scb_data->hscb_maps)) != शून्य) अणु
			SLIST_REMOVE_HEAD(&scb_data->hscb_maps, links);
			ahd_dmamap_unload(ahd, scb_data->hscb_dmat,
					  hscb_map->dmamap);
			ahd_dmamem_मुक्त(ahd, scb_data->hscb_dmat,
					hscb_map->vaddr, hscb_map->dmamap);
			kमुक्त(hscb_map);
		पूर्ण
		ahd_dma_tag_destroy(ahd, scb_data->hscb_dmat);
	पूर्ण
		fallthrough;
	हाल 4:
	हाल 3:
	हाल 2:
	हाल 1:
	हाल 0:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * DSP filter Bypass must be enabled until the first selection
 * after a change in bus mode (Razor #491 and #493).
 */
अटल व्योम
ahd_setup_iocell_workaround(काष्ठा ahd_softc *ahd)
अणु
	ahd_mode_state saved_modes;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	ahd_outb(ahd, DSPDATACTL, ahd_inb(ahd, DSPDATACTL)
	       | BYPASSENAB | RCVROFFSTDIS | XMITOFFSTDIS);
	ahd_outb(ahd, SIMODE0, ahd_inb(ahd, SIMODE0) | (ENSELDO|ENSELDI));
#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_MISC) != 0)
		prपूर्णांकk("%s: Setting up iocell workaround\n", ahd_name(ahd));
#पूर्ण_अगर
	ahd_restore_modes(ahd, saved_modes);
	ahd->flags &= ~AHD_HAD_FIRST_SEL;
पूर्ण

अटल व्योम
ahd_iocell_first_selection(काष्ठा ahd_softc *ahd)
अणु
	ahd_mode_state	saved_modes;
	u_पूर्णांक		sblkctl;

	अगर ((ahd->flags & AHD_HAD_FIRST_SEL) != 0)
		वापस;
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	sblkctl = ahd_inb(ahd, SBLKCTL);
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_MISC) != 0)
		prपूर्णांकk("%s: iocell first selection\n", ahd_name(ahd));
#पूर्ण_अगर
	अगर ((sblkctl & ENAB40) != 0) अणु
		ahd_outb(ahd, DSPDATACTL,
			 ahd_inb(ahd, DSPDATACTL) & ~BYPASSENAB);
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MISC) != 0)
			prपूर्णांकk("%s: BYPASS now disabled\n", ahd_name(ahd));
#पूर्ण_अगर
	पूर्ण
	ahd_outb(ahd, SIMODE0, ahd_inb(ahd, SIMODE0) & ~(ENSELDO|ENSELDI));
	ahd_outb(ahd, CLRINT, CLRSCSIINT);
	ahd_restore_modes(ahd, saved_modes);
	ahd->flags |= AHD_HAD_FIRST_SEL;
पूर्ण

/*************************** SCB Management ***********************************/
अटल व्योम
ahd_add_col_list(काष्ठा ahd_softc *ahd, काष्ठा scb *scb, u_पूर्णांक col_idx)
अणु
	काष्ठा	scb_list *मुक्त_list;
	काष्ठा	scb_tailq *मुक्त_tailq;
	काष्ठा	scb *first_scb;

	scb->flags |= SCB_ON_COL_LIST;
	AHD_SET_SCB_COL_IDX(scb, col_idx);
	मुक्त_list = &ahd->scb_data.मुक्त_scb_lists[col_idx];
	मुक्त_tailq = &ahd->scb_data.मुक्त_scbs;
	first_scb = LIST_FIRST(मुक्त_list);
	अगर (first_scb != शून्य) अणु
		LIST_INSERT_AFTER(first_scb, scb, collision_links);
	पूर्ण अन्यथा अणु
		LIST_INSERT_HEAD(मुक्त_list, scb, collision_links);
		TAILQ_INSERT_TAIL(मुक्त_tailq, scb, links.tqe);
	पूर्ण
पूर्ण

अटल व्योम
ahd_rem_col_list(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	काष्ठा	scb_list *मुक्त_list;
	काष्ठा	scb_tailq *मुक्त_tailq;
	काष्ठा	scb *first_scb;
	u_पूर्णांक	col_idx;

	scb->flags &= ~SCB_ON_COL_LIST;
	col_idx = AHD_GET_SCB_COL_IDX(ahd, scb);
	मुक्त_list = &ahd->scb_data.मुक्त_scb_lists[col_idx];
	मुक्त_tailq = &ahd->scb_data.मुक्त_scbs;
	first_scb = LIST_FIRST(मुक्त_list);
	अगर (first_scb == scb) अणु
		काष्ठा scb *next_scb;

		/*
		 * Maपूर्णांकain order in the collision मुक्त
		 * lists क्रम fairness अगर this device has
		 * other colliding tags active.
		 */
		next_scb = LIST_NEXT(scb, collision_links);
		अगर (next_scb != शून्य) अणु
			TAILQ_INSERT_AFTER(मुक्त_tailq, scb,
					   next_scb, links.tqe);
		पूर्ण
		TAILQ_REMOVE(मुक्त_tailq, scb, links.tqe);
	पूर्ण
	LIST_REMOVE(scb, collision_links);
पूर्ण

/*
 * Get a मुक्त scb. If there are none, see अगर we can allocate a new SCB.
 */
काष्ठा scb *
ahd_get_scb(काष्ठा ahd_softc *ahd, u_पूर्णांक col_idx)
अणु
	काष्ठा scb *scb;
	पूर्णांक tries;

	tries = 0;
look_again:
	TAILQ_FOREACH(scb, &ahd->scb_data.मुक्त_scbs, links.tqe) अणु
		अगर (AHD_GET_SCB_COL_IDX(ahd, scb) != col_idx) अणु
			ahd_rem_col_list(ahd, scb);
			जाओ found;
		पूर्ण
	पूर्ण
	अगर ((scb = LIST_FIRST(&ahd->scb_data.any_dev_मुक्त_scb_list)) == शून्य) अणु

		अगर (tries++ != 0)
			वापस (शून्य);
		ahd_alloc_scbs(ahd);
		जाओ look_again;
	पूर्ण
	LIST_REMOVE(scb, links.le);
	अगर (col_idx != AHD_NEVER_COL_IDX
	 && (scb->col_scb != शून्य)
	 && (scb->col_scb->flags & SCB_ACTIVE) == 0) अणु
		LIST_REMOVE(scb->col_scb, links.le);
		ahd_add_col_list(ahd, scb->col_scb, col_idx);
	पूर्ण
found:
	scb->flags |= SCB_ACTIVE;
	वापस (scb);
पूर्ण

/*
 * Return an SCB resource to the मुक्त list.
 */
व्योम
ahd_मुक्त_scb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	/* Clean up क्रम the next user */
	scb->flags = SCB_FLAG_NONE;
	scb->hscb->control = 0;
	ahd->scb_data.scbindex[SCB_GET_TAG(scb)] = शून्य;

	अगर (scb->col_scb == शून्य) अणु

		/*
		 * No collision possible.  Just मुक्त normally.
		 */
		LIST_INSERT_HEAD(&ahd->scb_data.any_dev_मुक्त_scb_list,
				 scb, links.le);
	पूर्ण अन्यथा अगर ((scb->col_scb->flags & SCB_ON_COL_LIST) != 0) अणु

		/*
		 * The SCB we might have collided with is on
		 * a मुक्त collision list.  Put both SCBs on
		 * the generic list.
		 */
		ahd_rem_col_list(ahd, scb->col_scb);
		LIST_INSERT_HEAD(&ahd->scb_data.any_dev_मुक्त_scb_list,
				 scb, links.le);
		LIST_INSERT_HEAD(&ahd->scb_data.any_dev_मुक्त_scb_list,
				 scb->col_scb, links.le);
	पूर्ण अन्यथा अगर ((scb->col_scb->flags
		  & (SCB_PACKETIZED|SCB_ACTIVE)) == SCB_ACTIVE
		&& (scb->col_scb->hscb->control & TAG_ENB) != 0) अणु

		/*
		 * The SCB we might collide with on the next allocation
		 * is still active in a non-packetized, tagged, context.
		 * Put us on the SCB collision list.
		 */
		ahd_add_col_list(ahd, scb,
				 AHD_GET_SCB_COL_IDX(ahd, scb->col_scb));
	पूर्ण अन्यथा अणु
		/*
		 * The SCB we might collide with on the next allocation
		 * is either active in a packetized context, or मुक्त.
		 * Since we can't collide, put this SCB on the generic
		 * मुक्त list.
		 */
		LIST_INSERT_HEAD(&ahd->scb_data.any_dev_मुक्त_scb_list,
				 scb, links.le);
	पूर्ण

	ahd_platक्रमm_scb_मुक्त(ahd, scb);
पूर्ण

अटल व्योम
ahd_alloc_scbs(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा scb_data *scb_data;
	काष्ठा scb	*next_scb;
	काष्ठा hardware_scb *hscb;
	काष्ठा map_node *hscb_map;
	काष्ठा map_node *sg_map;
	काष्ठा map_node *sense_map;
	uपूर्णांक8_t		*segs;
	uपूर्णांक8_t		*sense_data;
	dma_addr_t	 hscb_busaddr;
	dma_addr_t	 sg_busaddr;
	dma_addr_t	 sense_busaddr;
	पूर्णांक		 newcount;
	पूर्णांक		 i;

	scb_data = &ahd->scb_data;
	अगर (scb_data->numscbs >= AHD_SCB_MAX_ALLOC)
		/* Can't allocate any more */
		वापस;

	अगर (scb_data->scbs_left != 0) अणु
		पूर्णांक offset;

		offset = (PAGE_SIZE / माप(*hscb)) - scb_data->scbs_left;
		hscb_map = SLIST_FIRST(&scb_data->hscb_maps);
		hscb = &((काष्ठा hardware_scb *)hscb_map->vaddr)[offset];
		hscb_busaddr = hscb_map->physaddr + (offset * माप(*hscb));
	पूर्ण अन्यथा अणु
		hscb_map = kदो_स्मृति(माप(*hscb_map), GFP_ATOMIC);

		अगर (hscb_map == शून्य)
			वापस;

		/* Allocate the next batch of hardware SCBs */
		अगर (ahd_dmamem_alloc(ahd, scb_data->hscb_dmat,
				     (व्योम **)&hscb_map->vaddr,
				     BUS_DMA_NOWAIT, &hscb_map->dmamap) != 0) अणु
			kमुक्त(hscb_map);
			वापस;
		पूर्ण

		SLIST_INSERT_HEAD(&scb_data->hscb_maps, hscb_map, links);

		ahd_dmamap_load(ahd, scb_data->hscb_dmat, hscb_map->dmamap,
				hscb_map->vaddr, PAGE_SIZE, ahd_dmamap_cb,
				&hscb_map->physaddr, /*flags*/0);

		hscb = (काष्ठा hardware_scb *)hscb_map->vaddr;
		hscb_busaddr = hscb_map->physaddr;
		scb_data->scbs_left = PAGE_SIZE / माप(*hscb);
	पूर्ण

	अगर (scb_data->sgs_left != 0) अणु
		पूर्णांक offset;

		offset = ((ahd_sglist_allocsize(ahd) / ahd_sglist_size(ahd))
		       - scb_data->sgs_left) * ahd_sglist_size(ahd);
		sg_map = SLIST_FIRST(&scb_data->sg_maps);
		segs = sg_map->vaddr + offset;
		sg_busaddr = sg_map->physaddr + offset;
	पूर्ण अन्यथा अणु
		sg_map = kदो_स्मृति(माप(*sg_map), GFP_ATOMIC);

		अगर (sg_map == शून्य)
			वापस;

		/* Allocate the next batch of S/G lists */
		अगर (ahd_dmamem_alloc(ahd, scb_data->sg_dmat,
				     (व्योम **)&sg_map->vaddr,
				     BUS_DMA_NOWAIT, &sg_map->dmamap) != 0) अणु
			kमुक्त(sg_map);
			वापस;
		पूर्ण

		SLIST_INSERT_HEAD(&scb_data->sg_maps, sg_map, links);

		ahd_dmamap_load(ahd, scb_data->sg_dmat, sg_map->dmamap,
				sg_map->vaddr, ahd_sglist_allocsize(ahd),
				ahd_dmamap_cb, &sg_map->physaddr, /*flags*/0);

		segs = sg_map->vaddr;
		sg_busaddr = sg_map->physaddr;
		scb_data->sgs_left =
		    ahd_sglist_allocsize(ahd) / ahd_sglist_size(ahd);
#अगर_घोषित AHD_DEBUG
		अगर (ahd_debug & AHD_SHOW_MEMORY)
			prपूर्णांकk("Mapped SG data\n");
#पूर्ण_अगर
	पूर्ण

	अगर (scb_data->sense_left != 0) अणु
		पूर्णांक offset;

		offset = PAGE_SIZE - (AHD_SENSE_बफ_मानE * scb_data->sense_left);
		sense_map = SLIST_FIRST(&scb_data->sense_maps);
		sense_data = sense_map->vaddr + offset;
		sense_busaddr = sense_map->physaddr + offset;
	पूर्ण अन्यथा अणु
		sense_map = kदो_स्मृति(माप(*sense_map), GFP_ATOMIC);

		अगर (sense_map == शून्य)
			वापस;

		/* Allocate the next batch of sense buffers */
		अगर (ahd_dmamem_alloc(ahd, scb_data->sense_dmat,
				     (व्योम **)&sense_map->vaddr,
				     BUS_DMA_NOWAIT, &sense_map->dmamap) != 0) अणु
			kमुक्त(sense_map);
			वापस;
		पूर्ण

		SLIST_INSERT_HEAD(&scb_data->sense_maps, sense_map, links);

		ahd_dmamap_load(ahd, scb_data->sense_dmat, sense_map->dmamap,
				sense_map->vaddr, PAGE_SIZE, ahd_dmamap_cb,
				&sense_map->physaddr, /*flags*/0);

		sense_data = sense_map->vaddr;
		sense_busaddr = sense_map->physaddr;
		scb_data->sense_left = PAGE_SIZE / AHD_SENSE_बफ_मानE;
#अगर_घोषित AHD_DEBUG
		अगर (ahd_debug & AHD_SHOW_MEMORY)
			prपूर्णांकk("Mapped sense data\n");
#पूर्ण_अगर
	पूर्ण

	newcount = min(scb_data->sense_left, scb_data->scbs_left);
	newcount = min(newcount, scb_data->sgs_left);
	newcount = min(newcount, (AHD_SCB_MAX_ALLOC - scb_data->numscbs));
	क्रम (i = 0; i < newcount; i++) अणु
		काष्ठा scb_platक्रमm_data *pdata;
		u_पूर्णांक col_tag;

		next_scb = kदो_स्मृति(माप(*next_scb), GFP_ATOMIC);
		अगर (next_scb == शून्य)
			अवरोध;

		pdata = kदो_स्मृति(माप(*pdata), GFP_ATOMIC);
		अगर (pdata == शून्य) अणु
			kमुक्त(next_scb);
			अवरोध;
		पूर्ण
		next_scb->platक्रमm_data = pdata;
		next_scb->hscb_map = hscb_map;
		next_scb->sg_map = sg_map;
		next_scb->sense_map = sense_map;
		next_scb->sg_list = segs;
		next_scb->sense_data = sense_data;
		next_scb->sense_busaddr = sense_busaddr;
		स_रखो(hscb, 0, माप(*hscb));
		next_scb->hscb = hscb;
		hscb->hscb_busaddr = ahd_htole32(hscb_busaddr);

		/*
		 * The sequencer always starts with the second entry.
		 * The first entry is embedded in the scb.
		 */
		next_scb->sg_list_busaddr = sg_busaddr;
		अगर ((ahd->flags & AHD_64BIT_ADDRESSING) != 0)
			next_scb->sg_list_busaddr
			    += माप(काष्ठा ahd_dma64_seg);
		अन्यथा
			next_scb->sg_list_busaddr += माप(काष्ठा ahd_dma_seg);
		next_scb->ahd_softc = ahd;
		next_scb->flags = SCB_FLAG_NONE;
		next_scb->hscb->tag = ahd_htole16(scb_data->numscbs);
		col_tag = scb_data->numscbs ^ 0x100;
		next_scb->col_scb = ahd_find_scb_by_tag(ahd, col_tag);
		अगर (next_scb->col_scb != शून्य)
			next_scb->col_scb->col_scb = next_scb;
		ahd_मुक्त_scb(ahd, next_scb);
		hscb++;
		hscb_busaddr += माप(*hscb);
		segs += ahd_sglist_size(ahd);
		sg_busaddr += ahd_sglist_size(ahd);
		sense_data += AHD_SENSE_बफ_मानE;
		sense_busaddr += AHD_SENSE_बफ_मानE;
		scb_data->numscbs++;
		scb_data->sense_left--;
		scb_data->scbs_left--;
		scb_data->sgs_left--;
	पूर्ण
पूर्ण

व्योम
ahd_controller_info(काष्ठा ahd_softc *ahd, अक्षर *buf)
अणु
	स्थिर अक्षर *speed;
	स्थिर अक्षर *type;
	पूर्णांक len;

	len = प्र_लिखो(buf, "%s: ", ahd_chip_names[ahd->chip & AHD_CHIPID_MASK]);
	buf += len;

	speed = "Ultra320 ";
	अगर ((ahd->features & AHD_WIDE) != 0) अणु
		type = "Wide ";
	पूर्ण अन्यथा अणु
		type = "Single ";
	पूर्ण
	len = प्र_लिखो(buf, "%s%sChannel %c, SCSI Id=%d, ",
		      speed, type, ahd->channel, ahd->our_id);
	buf += len;

	प्र_लिखो(buf, "%s, %d SCBs", ahd->bus_description,
		ahd->scb_data.maxhscbs);
पूर्ण

अटल स्थिर अक्षर *channel_strings[] = अणु
	"Primary Low",
	"Primary High",
	"Secondary Low",
	"Secondary High"
पूर्ण;

अटल स्थिर अक्षर *termstat_strings[] = अणु
	"Terminated Correctly",
	"Over Terminated",
	"Under Terminated",
	"Not Configured"
पूर्ण;

/***************************** Timer Facilities *******************************/
अटल व्योम
ahd_समयr_reset(काष्ठा समयr_list *समयr, पूर्णांक usec)
अणु
	del_समयr(समयr);
	समयr->expires = jअगरfies + (usec * HZ)/1000000;
	add_समयr(समयr);
पूर्ण

/*
 * Start the board, पढ़ोy क्रम normal operation
 */
पूर्णांक
ahd_init(काष्ठा ahd_softc *ahd)
अणु
	uपूर्णांक8_t		*next_vaddr;
	dma_addr_t	 next_baddr;
	माप_प्रकार		 driver_data_size;
	पूर्णांक		 i;
	पूर्णांक		 error;
	u_पूर्णांक		 warn_user;
	uपूर्णांक8_t		 current_sensing;
	uपूर्णांक8_t		 ख_स्थिति;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);

	ahd->stack_size = ahd_probe_stack_size(ahd);
	ahd->saved_stack = kदो_स्मृति_array(ahd->stack_size, माप(uपूर्णांक16_t),
					 GFP_ATOMIC);
	अगर (ahd->saved_stack == शून्य)
		वापस (ENOMEM);

	/*
	 * Verअगरy that the compiler hasn't over-aggressively
	 * padded important काष्ठाures.
	 */
	अगर (माप(काष्ठा hardware_scb) != 64)
		panic("Hardware SCB size is incorrect");

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_DEBUG_SEQUENCER) != 0)
		ahd->flags |= AHD_SEQUENCER_DEBUG;
#पूर्ण_अगर

	/*
	 * Default to allowing initiator operations.
	 */
	ahd->flags |= AHD_INITIATORROLE;

	/*
	 * Only allow target mode features अगर this unit has them enabled.
	 */
	अगर ((AHD_TMODE_ENABLE & (0x1 << ahd->unit)) == 0)
		ahd->features &= ~AHD_TARGETMODE;

	ahd->init_level++;

	/*
	 * DMA tag क्रम our command fअगरos and other data in प्रणाली memory
	 * the card's sequencer must be able to access.  For initiator
	 * roles, we need to allocate space क्रम the qoutfअगरo.  When providing
	 * क्रम the target mode role, we must additionally provide space क्रम
	 * the incoming target command fअगरo.
	 */
	driver_data_size = AHD_SCB_MAX * माप(*ahd->qoutfअगरo)
			 + माप(काष्ठा hardware_scb);
	अगर ((ahd->features & AHD_TARGETMODE) != 0)
		driver_data_size += AHD_TMODE_CMDS * माप(काष्ठा target_cmd);
	अगर ((ahd->bugs & AHD_PKT_BITBUCKET_BUG) != 0)
		driver_data_size += PKT_OVERRUN_बफ_मानE;
	अगर (ahd_dma_tag_create(ahd, ahd->parent_dmat, /*alignment*/1,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/शून्य, /*filterarg*/शून्य,
			       driver_data_size,
			       /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &ahd->shared_data_dmat) != 0) अणु
		वापस (ENOMEM);
	पूर्ण

	ahd->init_level++;

	/* Allocation of driver data */
	अगर (ahd_dmamem_alloc(ahd, ahd->shared_data_dmat,
			     (व्योम **)&ahd->shared_data_map.vaddr,
			     BUS_DMA_NOWAIT,
			     &ahd->shared_data_map.dmamap) != 0) अणु
		वापस (ENOMEM);
	पूर्ण

	ahd->init_level++;

	/* And permanently map it in */
	ahd_dmamap_load(ahd, ahd->shared_data_dmat, ahd->shared_data_map.dmamap,
			ahd->shared_data_map.vaddr, driver_data_size,
			ahd_dmamap_cb, &ahd->shared_data_map.physaddr,
			/*flags*/0);
	ahd->qoutfअगरo = (काष्ठा ahd_completion *)ahd->shared_data_map.vaddr;
	next_vaddr = (uपूर्णांक8_t *)&ahd->qoutfअगरo[AHD_QOUT_SIZE];
	next_baddr = ahd->shared_data_map.physaddr
		   + AHD_QOUT_SIZE*माप(काष्ठा ahd_completion);
	अगर ((ahd->features & AHD_TARGETMODE) != 0) अणु
		ahd->tarअ_लोmds = (काष्ठा target_cmd *)next_vaddr;
		next_vaddr += AHD_TMODE_CMDS * माप(काष्ठा target_cmd);
		next_baddr += AHD_TMODE_CMDS * माप(काष्ठा target_cmd);
	पूर्ण

	अगर ((ahd->bugs & AHD_PKT_BITBUCKET_BUG) != 0) अणु
		ahd->overrun_buf = next_vaddr;
		next_vaddr += PKT_OVERRUN_बफ_मानE;
		next_baddr += PKT_OVERRUN_बफ_मानE;
	पूर्ण

	/*
	 * We need one SCB to serve as the "next SCB".  Since the
	 * tag identअगरier in this SCB will never be used, there is
	 * no poपूर्णांक in using a valid HSCB tag from an SCB pulled from
	 * the standard मुक्त pool.  So, we allocate this "sentinel"
	 * specially from the DMA safe memory chunk used क्रम the QOUTFIFO.
	 */
	ahd->next_queued_hscb = (काष्ठा hardware_scb *)next_vaddr;
	ahd->next_queued_hscb_map = &ahd->shared_data_map;
	ahd->next_queued_hscb->hscb_busaddr = ahd_htole32(next_baddr);

	ahd->init_level++;

	/* Allocate SCB data now that buffer_dmat is initialized */
	अगर (ahd_init_scbdata(ahd) != 0)
		वापस (ENOMEM);

	अगर ((ahd->flags & AHD_INITIATORROLE) == 0)
		ahd->flags &= ~AHD_RESET_BUS_A;

	/*
	 * Beक्रमe committing these settings to the chip, give
	 * the OSM one last chance to modअगरy our configuration.
	 */
	ahd_platक्रमm_init(ahd);

	/* Bring up the chip. */
	ahd_chip_init(ahd);

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);

	अगर ((ahd->flags & AHD_CURRENT_SENSING) == 0)
		जाओ init_करोne;

	/*
	 * Verअगरy termination based on current draw and
	 * warn user अगर the bus is over/under terminated.
	 */
	error = ahd_ग_लिखो_flexport(ahd, FLXADDR_ROMSTAT_CURSENSECTL,
				   CURSENSE_ENB);
	अगर (error != 0) अणु
		prपूर्णांकk("%s: current sensing timeout 1\n", ahd_name(ahd));
		जाओ init_करोne;
	पूर्ण
	क्रम (i = 20, ख_स्थिति = FLX_FSTAT_BUSY;
	     (ख_स्थिति & FLX_FSTAT_BUSY) != 0 && i; i--) अणु
		error = ahd_पढ़ो_flexport(ahd, FLXADDR_FLEXSTAT, &ख_स्थिति);
		अगर (error != 0) अणु
			prपूर्णांकk("%s: current sensing timeout 2\n",
			       ahd_name(ahd));
			जाओ init_करोne;
		पूर्ण
	पूर्ण
	अगर (i == 0) अणु
		prपूर्णांकk("%s: Timedout during current-sensing test\n",
		       ahd_name(ahd));
		जाओ init_करोne;
	पूर्ण

	/* Latch Current Sensing status. */
	error = ahd_पढ़ो_flexport(ahd, FLXADDR_CURRENT_STAT, &current_sensing);
	अगर (error != 0) अणु
		prपूर्णांकk("%s: current sensing timeout 3\n", ahd_name(ahd));
		जाओ init_करोne;
	पूर्ण

	/* Diable current sensing. */
	ahd_ग_लिखो_flexport(ahd, FLXADDR_ROMSTAT_CURSENSECTL, 0);

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_TERMCTL) != 0) अणु
		prपूर्णांकk("%s: current_sensing == 0x%x\n",
		       ahd_name(ahd), current_sensing);
	पूर्ण
#पूर्ण_अगर
	warn_user = 0;
	क्रम (i = 0; i < 4; i++, current_sensing >>= FLX_CSTAT_SHIFT) अणु
		u_पूर्णांक term_stat;

		term_stat = (current_sensing & FLX_CSTAT_MASK);
		चयन (term_stat) अणु
		हाल FLX_CSTAT_OVER:
		हाल FLX_CSTAT_UNDER:
			warn_user++;
			fallthrough;
		हाल FLX_CSTAT_INVALID:
		हाल FLX_CSTAT_OKAY:
			अगर (warn_user == 0 && bootverbose == 0)
				अवरोध;
			prपूर्णांकk("%s: %s Channel %s\n", ahd_name(ahd),
			       channel_strings[i], termstat_strings[term_stat]);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (warn_user) अणु
		prपूर्णांकk("%s: WARNING. Termination is not configured correctly.\n"
		       "%s: WARNING. SCSI bus operations may FAIL.\n",
		       ahd_name(ahd), ahd_name(ahd));
	पूर्ण
init_करोne:
	ahd_restart(ahd);
	ahd_समयr_reset(&ahd->stat_समयr, AHD_STAT_UPDATE_US);
	वापस (0);
पूर्ण

/*
 * (Re)initialize chip state after a chip reset.
 */
अटल व्योम
ahd_chip_init(काष्ठा ahd_softc *ahd)
अणु
	uपूर्णांक32_t busaddr;
	u_पूर्णांक	 sxfrctl1;
	u_पूर्णांक	 scsiseq_ढाँचा;
	u_पूर्णांक	 रुको;
	u_पूर्णांक	 i;
	u_पूर्णांक	 target;

	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	/*
	 * Take the LED out of diagnostic mode
	 */
	ahd_outb(ahd, SBLKCTL, ahd_inb(ahd, SBLKCTL) & ~(DIAGLEDEN|DIAGLEDON));

	/*
	 * Return HS_MAILBOX to its शेष value.
	 */
	ahd->hs_mailbox = 0;
	ahd_outb(ahd, HS_MAILBOX, 0);

	/* Set the SCSI Id, SXFRCTL0, SXFRCTL1, and SIMODE1. */
	ahd_outb(ahd, IOWNID, ahd->our_id);
	ahd_outb(ahd, TOWNID, ahd->our_id);
	sxfrctl1 = (ahd->flags & AHD_TERM_ENB_A) != 0 ? STPWEN : 0;
	sxfrctl1 |= (ahd->flags & AHD_SPCHK_ENB_A) != 0 ? ENSPCHK : 0;
	अगर ((ahd->bugs & AHD_LONG_SETIMO_BUG)
	 && (ahd->selसमय != STIMESEL_MIN)) अणु
		/*
		 * The selection समयr duration is twice as दीर्घ
		 * as it should be.  Halve it by adding "1" to
		 * the user specअगरied setting.
		 */
		sxfrctl1 |= ahd->selसमय + STIMESEL_BUG_ADJ;
	पूर्ण अन्यथा अणु
		sxfrctl1 |= ahd->selसमय;
	पूर्ण

	ahd_outb(ahd, SXFRCTL0, DFON);
	ahd_outb(ahd, SXFRCTL1, sxfrctl1|ahd->selसमय|ENSTIMER|ACTNEGEN);
	ahd_outb(ahd, SIMODE1, ENSELTIMO|ENSCSIRST|ENSCSIPERR);

	/*
	 * Now that termination is set, रुको क्रम up
	 * to 500ms क्रम our transceivers to settle.  If
	 * the adapter करोes not have a cable attached,
	 * the transceivers may never settle, so करोn't
	 * complain अगर we fail here.
	 */
	क्रम (रुको = 10000;
	     (ahd_inb(ahd, SBLKCTL) & (ENAB40|ENAB20)) == 0 && रुको;
	     रुको--)
		ahd_delay(100);

	/* Clear any false bus resets due to the transceivers settling */
	ahd_outb(ahd, CLRSINT1, CLRSCSIRSTI);
	ahd_outb(ahd, CLRINT, CLRSCSIINT);

	/* Initialize mode specअगरic S/G state. */
	क्रम (i = 0; i < 2; i++) अणु
		ahd_set_modes(ahd, AHD_MODE_DFF0 + i, AHD_MODE_DFF0 + i);
		ahd_outb(ahd, LONGJMP_ADDR + 1, INVALID_ADDR);
		ahd_outb(ahd, SG_STATE, 0);
		ahd_outb(ahd, CLRSEQINTSRC, 0xFF);
		ahd_outb(ahd, SEQIMODE,
			 ENSAVEPTRS|ENCFG4DATA|ENCFG4ISTAT
			|ENCFG4TSTAT|ENCFG4ICMD|ENCFG4TCMD);
	पूर्ण

	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	ahd_outb(ahd, DSCOMMAND0, ahd_inb(ahd, DSCOMMAND0)|MPARCKEN|CACHETHEN);
	ahd_outb(ahd, DFF_THRSH, RD_DFTHRSH_75|WR_DFTHRSH_75);
	ahd_outb(ahd, SIMODE0, ENIOERR|ENOVERRUN);
	ahd_outb(ahd, SIMODE3, ENNTRAMPERR|ENOSRAMPERR);
	अगर ((ahd->bugs & AHD_BUSFREEREV_BUG) != 0) अणु
		ahd_outb(ahd, OPTIONMODE, AUTOACKEN|AUTO_MSGOUT_DE);
	पूर्ण अन्यथा अणु
		ahd_outb(ahd, OPTIONMODE, AUTOACKEN|BUSFREEREV|AUTO_MSGOUT_DE);
	पूर्ण
	ahd_outb(ahd, SCSCHKN, CURRFIFODEF|WIDERESEN|SHVALIDSTDIS);
	अगर ((ahd->chip & AHD_BUS_MASK) == AHD_PCIX)
		/*
		 * Do not issue a target पात when a split completion
		 * error occurs.  Let our PCIX पूर्णांकerrupt handler deal
		 * with it instead. H2A4 Razor #625
		 */
		ahd_outb(ahd, PCIXCTL, ahd_inb(ahd, PCIXCTL) | SPLTSTADIS);

	अगर ((ahd->bugs & AHD_LQOOVERRUN_BUG) != 0)
		ahd_outb(ahd, LQOSCSCTL, LQONOCHKOVER);

	/*
	 * Tweak IOCELL settings.
	 */
	अगर ((ahd->flags & AHD_HP_BOARD) != 0) अणु
		क्रम (i = 0; i < NUMDSPS; i++) अणु
			ahd_outb(ahd, DSPSELECT, i);
			ahd_outb(ahd, WRTBIASCTL, WRTBIASCTL_HP_DEFAULT);
		पूर्ण
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MISC) != 0)
			prपूर्णांकk("%s: WRTBIASCTL now 0x%x\n", ahd_name(ahd),
			       WRTBIASCTL_HP_DEFAULT);
#पूर्ण_अगर
	पूर्ण
	ahd_setup_iocell_workaround(ahd);

	/*
	 * Enable LQI Manager पूर्णांकerrupts.
	 */
	ahd_outb(ahd, LQIMODE1, ENLQIPHASE_LQ|ENLQIPHASE_NLQ|ENLIQABORT
			      | ENLQICRCI_LQ|ENLQICRCI_NLQ|ENLQIBADLQI
			      | ENLQIOVERI_LQ|ENLQIOVERI_NLQ);
	ahd_outb(ahd, LQOMODE0, ENLQOATNLQ|ENLQOATNPKT|ENLQOTCRC);
	/*
	 * We choose to have the sequencer catch LQOPHCHGINPKT errors
	 * manually क्रम the command phase at the start of a packetized
	 * selection हाल.  ENLQOBUSFREE should be made redundant by
	 * the BUSFREE पूर्णांकerrupt, but it seems that some LQOBUSFREE
	 * events fail to निश्चित the BUSFREE पूर्णांकerrupt so we must
	 * also enable LQOBUSFREE पूर्णांकerrupts.
	 */
	ahd_outb(ahd, LQOMODE1, ENLQOBUSFREE);

	/*
	 * Setup sequencer पूर्णांकerrupt handlers.
	 */
	ahd_outw(ahd, INTVEC1_ADDR, ahd_resolve_seqaddr(ahd, LABEL_seq_isr));
	ahd_outw(ahd, INTVEC2_ADDR, ahd_resolve_seqaddr(ahd, LABEL_समयr_isr));

	/*
	 * Setup SCB Offset रेजिस्टरs.
	 */
	अगर ((ahd->bugs & AHD_PKT_LUN_BUG) != 0) अणु
		ahd_outb(ahd, LUNPTR, दुरत्व(काष्ठा hardware_scb,
			 pkt_दीर्घ_lun));
	पूर्ण अन्यथा अणु
		ahd_outb(ahd, LUNPTR, दुरत्व(काष्ठा hardware_scb, lun));
	पूर्ण
	ahd_outb(ahd, CMDLENPTR, दुरत्व(काष्ठा hardware_scb, cdb_len));
	ahd_outb(ahd, ATTRPTR, दुरत्व(काष्ठा hardware_scb, task_attribute));
	ahd_outb(ahd, FLAGPTR, दुरत्व(काष्ठा hardware_scb, task_management));
	ahd_outb(ahd, CMDPTR, दुरत्व(काष्ठा hardware_scb,
				       shared_data.idata.cdb));
	ahd_outb(ahd, QNEXTPTR,
		 दुरत्व(काष्ठा hardware_scb, next_hscb_busaddr));
	ahd_outb(ahd, ABRTBITPTR, MK_MESSAGE_BIT_OFFSET);
	ahd_outb(ahd, ABRTBYTEPTR, दुरत्व(काष्ठा hardware_scb, control));
	अगर ((ahd->bugs & AHD_PKT_LUN_BUG) != 0) अणु
		ahd_outb(ahd, LUNLEN,
			 माप(ahd->next_queued_hscb->pkt_दीर्घ_lun) - 1);
	पूर्ण अन्यथा अणु
		ahd_outb(ahd, LUNLEN, LUNLEN_SINGLE_LEVEL_LUN);
	पूर्ण
	ahd_outb(ahd, CDBLIMIT, SCB_CDB_LEN_PTR - 1);
	ahd_outb(ahd, MAXCMD, 0xFF);
	ahd_outb(ahd, SCBAUTOPTR,
		 AUSCBPTR_EN | दुरत्व(काष्ठा hardware_scb, tag));

	/* We haven't been enabled क्रम target mode yet. */
	ahd_outb(ahd, MULTARGID, 0);
	ahd_outb(ahd, MULTARGID + 1, 0);

	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	/* Initialize the negotiation table. */
	अगर ((ahd->features & AHD_NEW_IOCELL_OPTS) == 0) अणु
		/*
		 * Clear the spare bytes in the neg table to aव्योम
		 * spurious parity errors.
		 */
		क्रम (target = 0; target < AHD_NUM_TARGETS; target++) अणु
			ahd_outb(ahd, NEGOADDR, target);
			ahd_outb(ahd, ANNEXCOL, AHD_ANNEXCOL_PER_DEV0);
			क्रम (i = 0; i < AHD_NUM_PER_DEV_ANNEXCOLS; i++)
				ahd_outb(ahd, ANNEXDAT, 0);
		पूर्ण
	पूर्ण
	क्रम (target = 0; target < AHD_NUM_TARGETS; target++) अणु
		काष्ठा	 ahd_devinfo devinfo;
		काष्ठा	 ahd_initiator_tinfo *tinfo;
		काष्ठा	 ahd_पंचांगode_tstate *tstate;

		tinfo = ahd_fetch_transinfo(ahd, 'A', ahd->our_id,
					    target, &tstate);
		ahd_compile_devinfo(&devinfo, ahd->our_id,
				    target, CAM_LUN_WILDCARD,
				    'A', ROLE_INITIATOR);
		ahd_update_neg_table(ahd, &devinfo, &tinfo->curr);
	पूर्ण

	ahd_outb(ahd, CLRSINT3, NTRAMPERR|OSRAMPERR);
	ahd_outb(ahd, CLRINT, CLRSCSIINT);

#अगर_घोषित NEEDS_MORE_TESTING
	/*
	 * Always enable पात on incoming L_Qs अगर this feature is
	 * supported.  We use this to catch invalid SCB references.
	 */
	अगर ((ahd->bugs & AHD_ABORT_LQI_BUG) == 0)
		ahd_outb(ahd, LQCTL1, ABORTPENDING);
	अन्यथा
#पूर्ण_अगर
		ahd_outb(ahd, LQCTL1, 0);

	/* All of our queues are empty */
	ahd->qoutfअगरonext = 0;
	ahd->qoutfअगरonext_valid_tag = QOUTFIFO_ENTRY_VALID;
	ahd_outb(ahd, QOUTFIFO_ENTRY_VALID_TAG, QOUTFIFO_ENTRY_VALID);
	क्रम (i = 0; i < AHD_QOUT_SIZE; i++)
		ahd->qoutfअगरo[i].valid_tag = 0;
	ahd_sync_qoutfअगरo(ahd, BUS_DMASYNC_PREREAD);

	ahd->qinfअगरonext = 0;
	क्रम (i = 0; i < AHD_QIN_SIZE; i++)
		ahd->qinfअगरo[i] = SCB_LIST_शून्य;

	अगर ((ahd->features & AHD_TARGETMODE) != 0) अणु
		/* All target command blocks start out invalid. */
		क्रम (i = 0; i < AHD_TMODE_CMDS; i++)
			ahd->tarअ_लोmds[i].cmd_valid = 0;
		ahd_sync_tqinfअगरo(ahd, BUS_DMASYNC_PREREAD);
		ahd->tqinfअगरonext = 1;
		ahd_outb(ahd, KERNEL_TQINPOS, ahd->tqinfअगरonext - 1);
		ahd_outb(ahd, TQINPOS, ahd->tqinfअगरonext);
	पूर्ण

	/* Initialize Scratch Ram. */
	ahd_outb(ahd, SEQ_FLAGS, 0);
	ahd_outb(ahd, SEQ_FLAGS2, 0);

	/* We करोn't have any रुकोing selections */
	ahd_outw(ahd, WAITING_TID_HEAD, SCB_LIST_शून्य);
	ahd_outw(ahd, WAITING_TID_TAIL, SCB_LIST_शून्य);
	ahd_outw(ahd, MK_MESSAGE_SCB, SCB_LIST_शून्य);
	ahd_outw(ahd, MK_MESSAGE_SCSIID, 0xFF);
	क्रम (i = 0; i < AHD_NUM_TARGETS; i++)
		ahd_outw(ahd, WAITING_SCB_TAILS + (2 * i), SCB_LIST_शून्य);

	/*
	 * Nobody is रुकोing to be DMAed पूर्णांकo the QOUTFIFO.
	 */
	ahd_outw(ahd, COMPLETE_SCB_HEAD, SCB_LIST_शून्य);
	ahd_outw(ahd, COMPLETE_SCB_DMAINPROG_HEAD, SCB_LIST_शून्य);
	ahd_outw(ahd, COMPLETE_DMA_SCB_HEAD, SCB_LIST_शून्य);
	ahd_outw(ahd, COMPLETE_DMA_SCB_TAIL, SCB_LIST_शून्य);
	ahd_outw(ahd, COMPLETE_ON_QFREEZE_HEAD, SCB_LIST_शून्य);

	/*
	 * The Freeze Count is 0.
	 */
	ahd->qमुक्तze_cnt = 0;
	ahd_outw(ahd, QFREEZE_COUNT, 0);
	ahd_outw(ahd, KERNEL_QFREEZE_COUNT, 0);

	/*
	 * Tell the sequencer where it can find our arrays in memory.
	 */
	busaddr = ahd->shared_data_map.physaddr;
	ahd_outl(ahd, SHARED_DATA_ADDR, busaddr);
	ahd_outl(ahd, QOUTFIFO_NEXT_ADDR, busaddr);

	/*
	 * Setup the allowed SCSI Sequences based on operational mode.
	 * If we are a target, we'll enable select in operations once
	 * we've had a lun enabled.
	 */
	scsiseq_ढाँचा = ENAUTOATNP;
	अगर ((ahd->flags & AHD_INITIATORROLE) != 0)
		scsiseq_ढाँचा |= ENRSELI;
	ahd_outb(ahd, SCSISEQ_TEMPLATE, scsiseq_ढाँचा);

	/* There are no busy SCBs yet. */
	क्रम (target = 0; target < AHD_NUM_TARGETS; target++) अणु
		पूर्णांक lun;

		क्रम (lun = 0; lun < AHD_NUM_LUNS_NONPKT; lun++)
			ahd_unbusy_tcl(ahd, BUILD_TCL_RAW(target, 'A', lun));
	पूर्ण

	/*
	 * Initialize the group code to command length table.
	 * Venकरोr Unique codes are set to 0 so we only capture
	 * the first byte of the cdb.  These can be overridden
	 * when target mode is enabled.
	 */
	ahd_outb(ahd, CMDSIZE_TABLE, 5);
	ahd_outb(ahd, CMDSIZE_TABLE + 1, 9);
	ahd_outb(ahd, CMDSIZE_TABLE + 2, 9);
	ahd_outb(ahd, CMDSIZE_TABLE + 3, 0);
	ahd_outb(ahd, CMDSIZE_TABLE + 4, 15);
	ahd_outb(ahd, CMDSIZE_TABLE + 5, 11);
	ahd_outb(ahd, CMDSIZE_TABLE + 6, 0);
	ahd_outb(ahd, CMDSIZE_TABLE + 7, 0);

	/* Tell the sequencer of our initial queue positions */
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);
	ahd_outb(ahd, QOFF_CTLSTA, SCB_QSIZE_512);
	ahd->qinfअगरonext = 0;
	ahd_set_hnscb_qoff(ahd, ahd->qinfअगरonext);
	ahd_set_hescb_qoff(ahd, 0);
	ahd_set_snscb_qoff(ahd, 0);
	ahd_set_sescb_qoff(ahd, 0);
	ahd_set_sdscb_qoff(ahd, 0);

	/*
	 * Tell the sequencer which SCB will be the next one it receives.
	 */
	busaddr = ahd_le32toh(ahd->next_queued_hscb->hscb_busaddr);
	ahd_outl(ahd, NEXT_QUEUED_SCB_ADDR, busaddr);

	/*
	 * Default to coalescing disabled.
	 */
	ahd_outw(ahd, INT_COALESCING_CMDCOUNT, 0);
	ahd_outw(ahd, CMDS_PENDING, 0);
	ahd_update_coalescing_values(ahd, ahd->पूर्णांक_coalescing_समयr,
				     ahd->पूर्णांक_coalescing_maxcmds,
				     ahd->पूर्णांक_coalescing_mincmds);
	ahd_enable_coalescing(ahd, FALSE);

	ahd_loadseq(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	अगर (ahd->features & AHD_AIC79XXB_SLOWCRC) अणु
		u_पूर्णांक negodat3 = ahd_inb(ahd, NEGCONOPTS);

		negodat3 |= ENSLOWCRC;
		ahd_outb(ahd, NEGCONOPTS, negodat3);
		negodat3 = ahd_inb(ahd, NEGCONOPTS);
		अगर (!(negodat3 & ENSLOWCRC))
			prपूर्णांकk("aic79xx: failed to set the SLOWCRC bit\n");
		अन्यथा
			prपूर्णांकk("aic79xx: SLOWCRC bit set\n");
	पूर्ण
पूर्ण

/*
 * Setup शेष device and controller settings.
 * This should only be called अगर our probe has
 * determined that no configuration data is available.
 */
पूर्णांक
ahd_शेष_config(काष्ठा ahd_softc *ahd)
अणु
	पूर्णांक	targ;

	ahd->our_id = 7;

	/*
	 * Allocate a tstate to house inक्रमmation क्रम our
	 * initiator presence on the bus as well as the user
	 * data क्रम any target mode initiator.
	 */
	अगर (ahd_alloc_tstate(ahd, ahd->our_id, 'A') == शून्य) अणु
		prपूर्णांकk("%s: unable to allocate ahd_tmode_tstate.  "
		       "Failing attach\n", ahd_name(ahd));
		वापस (ENOMEM);
	पूर्ण

	क्रम (targ = 0; targ < AHD_NUM_TARGETS; targ++) अणु
		काष्ठा	 ahd_devinfo devinfo;
		काष्ठा	 ahd_initiator_tinfo *tinfo;
		काष्ठा	 ahd_पंचांगode_tstate *tstate;
		uपूर्णांक16_t target_mask;

		tinfo = ahd_fetch_transinfo(ahd, 'A', ahd->our_id,
					    targ, &tstate);
		/*
		 * We support SPC2 and SPI4.
		 */
		tinfo->user.protocol_version = 4;
		tinfo->user.transport_version = 4;

		target_mask = 0x01 << targ;
		ahd->user_discenable |= target_mask;
		tstate->discenable |= target_mask;
		ahd->user_tagenable |= target_mask;
#अगर_घोषित AHD_FORCE_160
		tinfo->user.period = AHD_SYNCRATE_DT;
#अन्यथा
		tinfo->user.period = AHD_SYNCRATE_160;
#पूर्ण_अगर
		tinfo->user.offset = MAX_OFFSET;
		tinfo->user.ppr_options = MSG_EXT_PPR_RD_STRM
					| MSG_EXT_PPR_WR_FLOW
					| MSG_EXT_PPR_HOLD_MCS
					| MSG_EXT_PPR_IU_REQ
					| MSG_EXT_PPR_QAS_REQ
					| MSG_EXT_PPR_DT_REQ;
		अगर ((ahd->features & AHD_RTI) != 0)
			tinfo->user.ppr_options |= MSG_EXT_PPR_RTI;

		tinfo->user.width = MSG_EXT_WDTR_BUS_16_BIT;

		/*
		 * Start out Async/Narrow/Untagged and with
		 * conservative protocol support.
		 */
		tinfo->goal.protocol_version = 2;
		tinfo->goal.transport_version = 2;
		tinfo->curr.protocol_version = 2;
		tinfo->curr.transport_version = 2;
		ahd_compile_devinfo(&devinfo, ahd->our_id,
				    targ, CAM_LUN_WILDCARD,
				    'A', ROLE_INITIATOR);
		tstate->tagenable &= ~target_mask;
		ahd_set_width(ahd, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
			      AHD_TRANS_CUR|AHD_TRANS_GOAL, /*छोड़ोd*/TRUE);
		ahd_set_syncrate(ahd, &devinfo, /*period*/0, /*offset*/0,
				 /*ppr_options*/0, AHD_TRANS_CUR|AHD_TRANS_GOAL,
				 /*छोड़ोd*/TRUE);
	पूर्ण
	वापस (0);
पूर्ण

/*
 * Parse device configuration inक्रमmation.
 */
पूर्णांक
ahd_parse_cfgdata(काष्ठा ahd_softc *ahd, काष्ठा seeprom_config *sc)
अणु
	पूर्णांक targ;
	पूर्णांक max_targ;

	max_targ = sc->max_tarमाला_लो & CFMAXTARG;
	ahd->our_id = sc->brसमय_id & CFSCSIID;

	/*
	 * Allocate a tstate to house inक्रमmation क्रम our
	 * initiator presence on the bus as well as the user
	 * data क्रम any target mode initiator.
	 */
	अगर (ahd_alloc_tstate(ahd, ahd->our_id, 'A') == शून्य) अणु
		prपूर्णांकk("%s: unable to allocate ahd_tmode_tstate.  "
		       "Failing attach\n", ahd_name(ahd));
		वापस (ENOMEM);
	पूर्ण

	क्रम (targ = 0; targ < max_targ; targ++) अणु
		काष्ठा	 ahd_devinfo devinfo;
		काष्ठा	 ahd_initiator_tinfo *tinfo;
		काष्ठा	 ahd_transinfo *user_tinfo;
		काष्ठा	 ahd_पंचांगode_tstate *tstate;
		uपूर्णांक16_t target_mask;

		tinfo = ahd_fetch_transinfo(ahd, 'A', ahd->our_id,
					    targ, &tstate);
		user_tinfo = &tinfo->user;

		/*
		 * We support SPC2 and SPI4.
		 */
		tinfo->user.protocol_version = 4;
		tinfo->user.transport_version = 4;

		target_mask = 0x01 << targ;
		ahd->user_discenable &= ~target_mask;
		tstate->discenable &= ~target_mask;
		ahd->user_tagenable &= ~target_mask;
		अगर (sc->device_flags[targ] & CFDISC) अणु
			tstate->discenable |= target_mask;
			ahd->user_discenable |= target_mask;
			ahd->user_tagenable |= target_mask;
		पूर्ण अन्यथा अणु
			/*
			 * Cannot be packetized without disconnection.
			 */
			sc->device_flags[targ] &= ~CFPACKETIZED;
		पूर्ण

		user_tinfo->ppr_options = 0;
		user_tinfo->period = (sc->device_flags[targ] & CFXFER);
		अगर (user_tinfo->period < CFXFER_ASYNC) अणु
			अगर (user_tinfo->period <= AHD_PERIOD_10MHz)
				user_tinfo->ppr_options |= MSG_EXT_PPR_DT_REQ;
			user_tinfo->offset = MAX_OFFSET;
		पूर्ण अन्यथा  अणु
			user_tinfo->offset = 0;
			user_tinfo->period = AHD_ASYNC_XFER_PERIOD;
		पूर्ण
#अगर_घोषित AHD_FORCE_160
		अगर (user_tinfo->period <= AHD_SYNCRATE_160)
			user_tinfo->period = AHD_SYNCRATE_DT;
#पूर्ण_अगर

		अगर ((sc->device_flags[targ] & CFPACKETIZED) != 0) अणु
			user_tinfo->ppr_options |= MSG_EXT_PPR_RD_STRM
						|  MSG_EXT_PPR_WR_FLOW
						|  MSG_EXT_PPR_HOLD_MCS
						|  MSG_EXT_PPR_IU_REQ;
			अगर ((ahd->features & AHD_RTI) != 0)
				user_tinfo->ppr_options |= MSG_EXT_PPR_RTI;
		पूर्ण

		अगर ((sc->device_flags[targ] & CFQAS) != 0)
			user_tinfo->ppr_options |= MSG_EXT_PPR_QAS_REQ;

		अगर ((sc->device_flags[targ] & CFWIDEB) != 0)
			user_tinfo->width = MSG_EXT_WDTR_BUS_16_BIT;
		अन्यथा
			user_tinfo->width = MSG_EXT_WDTR_BUS_8_BIT;
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_MISC) != 0)
			prपूर्णांकk("(%d): %x:%x:%x:%x\n", targ, user_tinfo->width,
			       user_tinfo->period, user_tinfo->offset,
			       user_tinfo->ppr_options);
#पूर्ण_अगर
		/*
		 * Start out Async/Narrow/Untagged and with
		 * conservative protocol support.
		 */
		tstate->tagenable &= ~target_mask;
		tinfo->goal.protocol_version = 2;
		tinfo->goal.transport_version = 2;
		tinfo->curr.protocol_version = 2;
		tinfo->curr.transport_version = 2;
		ahd_compile_devinfo(&devinfo, ahd->our_id,
				    targ, CAM_LUN_WILDCARD,
				    'A', ROLE_INITIATOR);
		ahd_set_width(ahd, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
			      AHD_TRANS_CUR|AHD_TRANS_GOAL, /*छोड़ोd*/TRUE);
		ahd_set_syncrate(ahd, &devinfo, /*period*/0, /*offset*/0,
				 /*ppr_options*/0, AHD_TRANS_CUR|AHD_TRANS_GOAL,
				 /*छोड़ोd*/TRUE);
	पूर्ण

	ahd->flags &= ~AHD_SPCHK_ENB_A;
	अगर (sc->bios_control & CFSPARITY)
		ahd->flags |= AHD_SPCHK_ENB_A;

	ahd->flags &= ~AHD_RESET_BUS_A;
	अगर (sc->bios_control & CFRESETB)
		ahd->flags |= AHD_RESET_BUS_A;

	ahd->flags &= ~AHD_EXTENDED_TRANS_A;
	अगर (sc->bios_control & CFEXTEND)
		ahd->flags |= AHD_EXTENDED_TRANS_A;

	ahd->flags &= ~AHD_BIOS_ENABLED;
	अगर ((sc->bios_control & CFBIOSSTATE) == CFBS_ENABLED)
		ahd->flags |= AHD_BIOS_ENABLED;

	ahd->flags &= ~AHD_STPWLEVEL_A;
	अगर ((sc->adapter_control & CFSTPWLEVEL) != 0)
		ahd->flags |= AHD_STPWLEVEL_A;

	वापस (0);
पूर्ण

/*
 * Parse device configuration inक्रमmation.
 */
पूर्णांक
ahd_parse_vpddata(काष्ठा ahd_softc *ahd, काष्ठा vpd_config *vpd)
अणु
	पूर्णांक error;

	error = ahd_verअगरy_vpd_cksum(vpd);
	अगर (error == 0)
		वापस (EINVAL);
	अगर ((vpd->bios_flags & VPDBOOTHOST) != 0)
		ahd->flags |= AHD_BOOT_CHANNEL;
	वापस (0);
पूर्ण

व्योम
ahd_पूर्णांकr_enable(काष्ठा ahd_softc *ahd, पूर्णांक enable)
अणु
	u_पूर्णांक hcntrl;

	hcntrl = ahd_inb(ahd, HCNTRL);
	hcntrl &= ~INTEN;
	ahd->छोड़ो &= ~INTEN;
	ahd->unछोड़ो &= ~INTEN;
	अगर (enable) अणु
		hcntrl |= INTEN;
		ahd->छोड़ो |= INTEN;
		ahd->unछोड़ो |= INTEN;
	पूर्ण
	ahd_outb(ahd, HCNTRL, hcntrl);
पूर्ण

अटल व्योम
ahd_update_coalescing_values(काष्ठा ahd_softc *ahd, u_पूर्णांक समयr, u_पूर्णांक maxcmds,
			     u_पूर्णांक mincmds)
अणु
	अगर (समयr > AHD_TIMER_MAX_US)
		समयr = AHD_TIMER_MAX_US;
	ahd->पूर्णांक_coalescing_समयr = समयr;

	अगर (maxcmds > AHD_INT_COALESCING_MAXCMDS_MAX)
		maxcmds = AHD_INT_COALESCING_MAXCMDS_MAX;
	अगर (mincmds > AHD_INT_COALESCING_MINCMDS_MAX)
		mincmds = AHD_INT_COALESCING_MINCMDS_MAX;
	ahd->पूर्णांक_coalescing_maxcmds = maxcmds;
	ahd_outw(ahd, INT_COALESCING_TIMER, समयr / AHD_TIMER_US_PER_TICK);
	ahd_outb(ahd, INT_COALESCING_MAXCMDS, -maxcmds);
	ahd_outb(ahd, INT_COALESCING_MINCMDS, -mincmds);
पूर्ण

अटल व्योम
ahd_enable_coalescing(काष्ठा ahd_softc *ahd, पूर्णांक enable)
अणु

	ahd->hs_mailbox &= ~ENINT_COALESCE;
	अगर (enable)
		ahd->hs_mailbox |= ENINT_COALESCE;
	ahd_outb(ahd, HS_MAILBOX, ahd->hs_mailbox);
	ahd_flush_device_ग_लिखोs(ahd);
	ahd_run_qoutfअगरo(ahd);
पूर्ण

/*
 * Ensure that the card is छोड़ोd in a location
 * outside of all critical sections and that all
 * pending work is completed prior to वापसing.
 * This routine should only be called from outside
 * an पूर्णांकerrupt context.
 */
व्योम
ahd_छोड़ो_and_flushwork(काष्ठा ahd_softc *ahd)
अणु
	u_पूर्णांक पूर्णांकstat;
	u_पूर्णांक maxloops;

	maxloops = 1000;
	ahd->flags |= AHD_ALL_INTERRUPTS;
	ahd_छोड़ो(ahd);
	/*
	 * Freeze the outgoing selections.  We करो this only
	 * until we are safely छोड़ोd without further selections
	 * pending.
	 */
	ahd->qमुक्तze_cnt--;
	ahd_outw(ahd, KERNEL_QFREEZE_COUNT, ahd->qमुक्तze_cnt);
	ahd_outb(ahd, SEQ_FLAGS2, ahd_inb(ahd, SEQ_FLAGS2) | SELECTOUT_QFROZEN);
	करो अणु

		ahd_unछोड़ो(ahd);
		/*
		 * Give the sequencer some समय to service
		 * any active selections.
		 */
		ahd_delay(500);

		ahd_पूर्णांकr(ahd);
		ahd_छोड़ो(ahd);
		पूर्णांकstat = ahd_inb(ahd, INTSTAT);
		अगर ((पूर्णांकstat & INT_PEND) == 0) अणु
			ahd_clear_critical_section(ahd);
			पूर्णांकstat = ahd_inb(ahd, INTSTAT);
		पूर्ण
	पूर्ण जबतक (--maxloops
	      && (पूर्णांकstat != 0xFF || (ahd->features & AHD_REMOVABLE) == 0)
	      && ((पूर्णांकstat & INT_PEND) != 0
	       || (ahd_inb(ahd, SCSISEQ0) & ENSELO) != 0
	       || (ahd_inb(ahd, SSTAT0) & (SELDO|SELINGO)) != 0));

	अगर (maxloops == 0) अणु
		prपूर्णांकk("Infinite interrupt loop, INTSTAT = %x",
		      ahd_inb(ahd, INTSTAT));
	पूर्ण
	ahd->qमुक्तze_cnt++;
	ahd_outw(ahd, KERNEL_QFREEZE_COUNT, ahd->qमुक्तze_cnt);

	ahd_flush_qoutfअगरo(ahd);

	ahd->flags &= ~AHD_ALL_INTERRUPTS;
पूर्ण

पूर्णांक __maybe_unused
ahd_suspend(काष्ठा ahd_softc *ahd)
अणु
	ahd_छोड़ो_and_flushwork(ahd);

	अगर (LIST_FIRST(&ahd->pending_scbs) != शून्य) अणु
		ahd_unछोड़ो(ahd);
		वापस (EBUSY);
	पूर्ण
	ahd_shutकरोwn(ahd);
	वापस (0);
पूर्ण

व्योम __maybe_unused
ahd_resume(काष्ठा ahd_softc *ahd)
अणु
	ahd_reset(ahd, /*reinit*/TRUE);
	ahd_पूर्णांकr_enable(ahd, TRUE);
	ahd_restart(ahd);
पूर्ण

/************************** Busy Target Table *********************************/
/*
 * Set SCBPTR to the SCB that contains the busy
 * table entry क्रम TCL.  Return the offset पूर्णांकo
 * the SCB that contains the entry क्रम TCL.
 * saved_scbid is dereferenced and set to the
 * scbid that should be restored once manipualtion
 * of the TCL entry is complete.
 */
अटल अंतरभूत u_पूर्णांक
ahd_index_busy_tcl(काष्ठा ahd_softc *ahd, u_पूर्णांक *saved_scbid, u_पूर्णांक tcl)
अणु
	/*
	 * Index to the SCB that contains the busy entry.
	 */
	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	*saved_scbid = ahd_get_scbptr(ahd);
	ahd_set_scbptr(ahd, TCL_LUN(tcl)
		     | ((TCL_TARGET_OFFSET(tcl) & 0xC) << 4));

	/*
	 * And now calculate the SCB offset to the entry.
	 * Each entry is 2 bytes wide, hence the
	 * multiplication by 2.
	 */
	वापस (((TCL_TARGET_OFFSET(tcl) & 0x3) << 1) + SCB_DISCONNECTED_LISTS);
पूर्ण

/*
 * Return the untagged transaction id क्रम a given target/channel lun.
 */
अटल u_पूर्णांक
ahd_find_busy_tcl(काष्ठा ahd_softc *ahd, u_पूर्णांक tcl)
अणु
	u_पूर्णांक scbid;
	u_पूर्णांक scb_offset;
	u_पूर्णांक saved_scbptr;

	scb_offset = ahd_index_busy_tcl(ahd, &saved_scbptr, tcl);
	scbid = ahd_inw_scbram(ahd, scb_offset);
	ahd_set_scbptr(ahd, saved_scbptr);
	वापस (scbid);
पूर्ण

अटल व्योम
ahd_busy_tcl(काष्ठा ahd_softc *ahd, u_पूर्णांक tcl, u_पूर्णांक scbid)
अणु
	u_पूर्णांक scb_offset;
	u_पूर्णांक saved_scbptr;

	scb_offset = ahd_index_busy_tcl(ahd, &saved_scbptr, tcl);
	ahd_outw(ahd, scb_offset, scbid);
	ahd_set_scbptr(ahd, saved_scbptr);
पूर्ण

/************************** SCB and SCB queue management **********************/
अटल पूर्णांक
ahd_match_scb(काष्ठा ahd_softc *ahd, काष्ठा scb *scb, पूर्णांक target,
	      अक्षर channel, पूर्णांक lun, u_पूर्णांक tag, role_t role)
अणु
	पूर्णांक targ = SCB_GET_TARGET(ahd, scb);
	अक्षर chan = SCB_GET_CHANNEL(ahd, scb);
	पूर्णांक slun = SCB_GET_LUN(scb);
	पूर्णांक match;

	match = ((chan == channel) || (channel == ALL_CHANNELS));
	अगर (match != 0)
		match = ((targ == target) || (target == CAM_TARGET_WILDCARD));
	अगर (match != 0)
		match = ((lun == slun) || (lun == CAM_LUN_WILDCARD));
	अगर (match != 0) अणु
#अगर_घोषित AHD_TARGET_MODE
		पूर्णांक group;

		group = XPT_FC_GROUP(scb->io_ctx->ccb_h.func_code);
		अगर (role == ROLE_INITIATOR) अणु
			match = (group != XPT_FC_GROUP_TMODE)
			      && ((tag == SCB_GET_TAG(scb))
			       || (tag == SCB_LIST_शून्य));
		पूर्ण अन्यथा अगर (role == ROLE_TARGET) अणु
			match = (group == XPT_FC_GROUP_TMODE)
			      && ((tag == scb->io_ctx->csio.tag_id)
			       || (tag == SCB_LIST_शून्य));
		पूर्ण
#अन्यथा /* !AHD_TARGET_MODE */
		match = ((tag == SCB_GET_TAG(scb)) || (tag == SCB_LIST_शून्य));
#पूर्ण_अगर /* AHD_TARGET_MODE */
	पूर्ण

	वापस match;
पूर्ण

अटल व्योम
ahd_मुक्तze_devq(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	पूर्णांक	target;
	अक्षर	channel;
	पूर्णांक	lun;

	target = SCB_GET_TARGET(ahd, scb);
	lun = SCB_GET_LUN(scb);
	channel = SCB_GET_CHANNEL(ahd, scb);

	ahd_search_qinfअगरo(ahd, target, channel, lun,
			   /*tag*/SCB_LIST_शून्य, ROLE_UNKNOWN,
			   CAM_REQUEUE_REQ, SEARCH_COMPLETE);

	ahd_platक्रमm_मुक्तze_devq(ahd, scb);
पूर्ण

व्योम
ahd_qinfअगरo_requeue_tail(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	काष्ठा scb	*prev_scb;
	ahd_mode_state	 saved_modes;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);
	prev_scb = शून्य;
	अगर (ahd_qinfअगरo_count(ahd) != 0) अणु
		u_पूर्णांक prev_tag;
		u_पूर्णांक prev_pos;

		prev_pos = AHD_QIN_WRAP(ahd->qinfअगरonext - 1);
		prev_tag = ahd->qinfअगरo[prev_pos];
		prev_scb = ahd_lookup_scb(ahd, prev_tag);
	पूर्ण
	ahd_qinfअगरo_requeue(ahd, prev_scb, scb);
	ahd_set_hnscb_qoff(ahd, ahd->qinfअगरonext);
	ahd_restore_modes(ahd, saved_modes);
पूर्ण

अटल व्योम
ahd_qinfअगरo_requeue(काष्ठा ahd_softc *ahd, काष्ठा scb *prev_scb,
		    काष्ठा scb *scb)
अणु
	अगर (prev_scb == शून्य) अणु
		uपूर्णांक32_t busaddr;

		busaddr = ahd_le32toh(scb->hscb->hscb_busaddr);
		ahd_outl(ahd, NEXT_QUEUED_SCB_ADDR, busaddr);
	पूर्ण अन्यथा अणु
		prev_scb->hscb->next_hscb_busaddr = scb->hscb->hscb_busaddr;
		ahd_sync_scb(ahd, prev_scb,
			     BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);
	पूर्ण
	ahd->qinfअगरo[AHD_QIN_WRAP(ahd->qinfअगरonext)] = SCB_GET_TAG(scb);
	ahd->qinfअगरonext++;
	scb->hscb->next_hscb_busaddr = ahd->next_queued_hscb->hscb_busaddr;
	ahd_sync_scb(ahd, scb, BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);
पूर्ण

अटल पूर्णांक
ahd_qinfअगरo_count(काष्ठा ahd_softc *ahd)
अणु
	u_पूर्णांक qinpos;
	u_पूर्णांक wrap_qinpos;
	u_पूर्णांक wrap_qinfअगरonext;

	AHD_ASSERT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	qinpos = ahd_get_snscb_qoff(ahd);
	wrap_qinpos = AHD_QIN_WRAP(qinpos);
	wrap_qinfअगरonext = AHD_QIN_WRAP(ahd->qinfअगरonext);
	अगर (wrap_qinfअगरonext >= wrap_qinpos)
		वापस (wrap_qinfअगरonext - wrap_qinpos);
	अन्यथा
		वापस (wrap_qinfअगरonext
		      + ARRAY_SIZE(ahd->qinfअगरo) - wrap_qinpos);
पूर्ण

अटल व्योम
ahd_reset_cmds_pending(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा		scb *scb;
	ahd_mode_state	saved_modes;
	u_पूर्णांक		pending_cmds;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);

	/*
	 * Don't count any commands as outstanding that the
	 * sequencer has alपढ़ोy marked क्रम completion.
	 */
	ahd_flush_qoutfअगरo(ahd);

	pending_cmds = 0;
	LIST_FOREACH(scb, &ahd->pending_scbs, pending_links) अणु
		pending_cmds++;
	पूर्ण
	ahd_outw(ahd, CMDS_PENDING, pending_cmds - ahd_qinfअगरo_count(ahd));
	ahd_restore_modes(ahd, saved_modes);
	ahd->flags &= ~AHD_UPDATE_PEND_CMDS;
पूर्ण

अटल व्योम
ahd_करोne_with_status(काष्ठा ahd_softc *ahd, काष्ठा scb *scb, uपूर्णांक32_t status)
अणु
	cam_status ostat;
	cam_status cstat;

	ostat = ahd_get_transaction_status(scb);
	अगर (ostat == CAM_REQ_INPROG)
		ahd_set_transaction_status(scb, status);
	cstat = ahd_get_transaction_status(scb);
	अगर (cstat != CAM_REQ_CMP)
		ahd_मुक्तze_scb(scb);
	ahd_करोne(ahd, scb);
पूर्ण

पूर्णांक
ahd_search_qinfअगरo(काष्ठा ahd_softc *ahd, पूर्णांक target, अक्षर channel,
		   पूर्णांक lun, u_पूर्णांक tag, role_t role, uपूर्णांक32_t status,
		   ahd_search_action action)
अणु
	काष्ठा scb	*scb;
	काष्ठा scb	*mk_msg_scb;
	काष्ठा scb	*prev_scb;
	ahd_mode_state	 saved_modes;
	u_पूर्णांक		 qinstart;
	u_पूर्णांक		 qinpos;
	u_पूर्णांक		 qपूर्णांकail;
	u_पूर्णांक		 tid_next;
	u_पूर्णांक		 tid_prev;
	u_पूर्णांक		 scbid;
	u_पूर्णांक		 seq_flags2;
	u_पूर्णांक		 savedscbptr;
	uपूर्णांक32_t	 busaddr;
	पूर्णांक		 found;
	पूर्णांक		 tarमाला_लो;

	/* Must be in CCHAN mode */
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);

	/*
	 * Halt any pending SCB DMA.  The sequencer will reinitiate
	 * this dma अगर the qinfअगरo is not empty once we unछोड़ो.
	 */
	अगर ((ahd_inb(ahd, CCSCBCTL) & (CCARREN|CCSCBEN|CCSCBसूची))
	 == (CCARREN|CCSCBEN|CCSCBसूची)) अणु
		ahd_outb(ahd, CCSCBCTL,
			 ahd_inb(ahd, CCSCBCTL) & ~(CCARREN|CCSCBEN));
		जबतक ((ahd_inb(ahd, CCSCBCTL) & (CCARREN|CCSCBEN)) != 0)
			;
	पूर्ण
	/* Determine sequencer's position in the qinfअगरo. */
	qपूर्णांकail = AHD_QIN_WRAP(ahd->qinfअगरonext);
	qinstart = ahd_get_snscb_qoff(ahd);
	qinpos = AHD_QIN_WRAP(qinstart);
	found = 0;
	prev_scb = शून्य;

	अगर (action == SEARCH_PRINT) अणु
		prपूर्णांकk("qinstart = %d qinfifonext = %d\nQINFIFO:",
		       qinstart, ahd->qinfअगरonext);
	पूर्ण

	/*
	 * Start with an empty queue.  Entries that are not chosen
	 * क्रम removal will be re-added to the queue as we go.
	 */
	ahd->qinfअगरonext = qinstart;
	busaddr = ahd_le32toh(ahd->next_queued_hscb->hscb_busaddr);
	ahd_outl(ahd, NEXT_QUEUED_SCB_ADDR, busaddr);

	जबतक (qinpos != qपूर्णांकail) अणु
		scb = ahd_lookup_scb(ahd, ahd->qinfअगरo[qinpos]);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("qinpos = %d, SCB index = %d\n",
				qinpos, ahd->qinfअगरo[qinpos]);
			panic("Loop 1\n");
		पूर्ण

		अगर (ahd_match_scb(ahd, scb, target, channel, lun, tag, role)) अणु
			/*
			 * We found an scb that needs to be acted on.
			 */
			found++;
			चयन (action) अणु
			हाल SEARCH_COMPLETE:
				अगर ((scb->flags & SCB_ACTIVE) == 0)
					prपूर्णांकk("Inactive SCB in qinfifo\n");
				ahd_करोne_with_status(ahd, scb, status);
				fallthrough;
			हाल SEARCH_REMOVE:
				अवरोध;
			हाल SEARCH_PRINT:
				prपूर्णांकk(" 0x%x", ahd->qinfअगरo[qinpos]);
				fallthrough;
			हाल SEARCH_COUNT:
				ahd_qinfअगरo_requeue(ahd, prev_scb, scb);
				prev_scb = scb;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			ahd_qinfअगरo_requeue(ahd, prev_scb, scb);
			prev_scb = scb;
		पूर्ण
		qinpos = AHD_QIN_WRAP(qinpos+1);
	पूर्ण

	ahd_set_hnscb_qoff(ahd, ahd->qinfअगरonext);

	अगर (action == SEARCH_PRINT)
		prपूर्णांकk("\nWAITING_TID_QUEUES:\n");

	/*
	 * Search रुकोing क्रम selection lists.  We traverse the
	 * list of "their ids" रुकोing क्रम selection and, अगर
	 * appropriate, traverse the SCBs of each "their id"
	 * looking क्रम matches.
	 */
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	seq_flags2 = ahd_inb(ahd, SEQ_FLAGS2);
	अगर ((seq_flags2 & PENDING_MK_MESSAGE) != 0) अणु
		scbid = ahd_inw(ahd, MK_MESSAGE_SCB);
		mk_msg_scb = ahd_lookup_scb(ahd, scbid);
	पूर्ण अन्यथा
		mk_msg_scb = शून्य;
	savedscbptr = ahd_get_scbptr(ahd);
	tid_next = ahd_inw(ahd, WAITING_TID_HEAD);
	tid_prev = SCB_LIST_शून्य;
	tarमाला_लो = 0;
	क्रम (scbid = tid_next; !SCBID_IS_शून्य(scbid); scbid = tid_next) अणु
		u_पूर्णांक tid_head;
		u_पूर्णांक tid_tail;

		tarमाला_लो++;
		अगर (tarमाला_लो > AHD_NUM_TARGETS)
			panic("TID LIST LOOP");

		अगर (scbid >= ahd->scb_data.numscbs) अणु
			prपूर्णांकk("%s: Waiting TID List inconsistency. "
			       "SCB index == 0x%x, yet numscbs == 0x%x.",
			       ahd_name(ahd), scbid, ahd->scb_data.numscbs);
			ahd_dump_card_state(ahd);
			panic("for safety");
		पूर्ण
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("%s: SCB = 0x%x Not Active!\n",
			       ahd_name(ahd), scbid);
			panic("Waiting TID List traversal\n");
		पूर्ण
		ahd_set_scbptr(ahd, scbid);
		tid_next = ahd_inw_scbram(ahd, SCB_NEXT2);
		अगर (ahd_match_scb(ahd, scb, target, channel, CAM_LUN_WILDCARD,
				  SCB_LIST_शून्य, ROLE_UNKNOWN) == 0) अणु
			tid_prev = scbid;
			जारी;
		पूर्ण

		/*
		 * We found a list of scbs that needs to be searched.
		 */
		अगर (action == SEARCH_PRINT)
			prपूर्णांकk("       %d ( ", SCB_GET_TARGET(ahd, scb));
		tid_head = scbid;
		found += ahd_search_scb_list(ahd, target, channel,
					     lun, tag, role, status,
					     action, &tid_head, &tid_tail,
					     SCB_GET_TARGET(ahd, scb));
		/*
		 * Check any MK_MESSAGE SCB that is still रुकोing to
		 * enter this target's रुकोing क्रम selection queue.
		 */
		अगर (mk_msg_scb != शून्य
		 && ahd_match_scb(ahd, mk_msg_scb, target, channel,
				  lun, tag, role)) अणु

			/*
			 * We found an scb that needs to be acted on.
			 */
			found++;
			चयन (action) अणु
			हाल SEARCH_COMPLETE:
				अगर ((mk_msg_scb->flags & SCB_ACTIVE) == 0)
					prपूर्णांकk("Inactive SCB pending MK_MSG\n");
				ahd_करोne_with_status(ahd, mk_msg_scb, status);
				fallthrough;
			हाल SEARCH_REMOVE:
			अणु
				u_पूर्णांक tail_offset;

				prपूर्णांकk("Removing MK_MSG scb\n");

				/*
				 * Reset our tail to the tail of the
				 * मुख्य per-target list.
				 */
				tail_offset = WAITING_SCB_TAILS
				    + (2 * SCB_GET_TARGET(ahd, mk_msg_scb));
				ahd_outw(ahd, tail_offset, tid_tail);

				seq_flags2 &= ~PENDING_MK_MESSAGE;
				ahd_outb(ahd, SEQ_FLAGS2, seq_flags2);
				ahd_outw(ahd, CMDS_PENDING,
					 ahd_inw(ahd, CMDS_PENDING)-1);
				mk_msg_scb = शून्य;
				अवरोध;
			पूर्ण
			हाल SEARCH_PRINT:
				prपूर्णांकk(" 0x%x", SCB_GET_TAG(scb));
				fallthrough;
			हाल SEARCH_COUNT:
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (mk_msg_scb != शून्य
		 && SCBID_IS_शून्य(tid_head)
		 && ahd_match_scb(ahd, scb, target, channel, CAM_LUN_WILDCARD,
				  SCB_LIST_शून्य, ROLE_UNKNOWN)) अणु

			/*
			 * When removing the last SCB क्रम a target
			 * queue with a pending MK_MESSAGE scb, we
			 * must queue the MK_MESSAGE scb.
			 */
			prपूर्णांकk("Queueing mk_msg_scb\n");
			tid_head = ahd_inw(ahd, MK_MESSAGE_SCB);
			seq_flags2 &= ~PENDING_MK_MESSAGE;
			ahd_outb(ahd, SEQ_FLAGS2, seq_flags2);
			mk_msg_scb = शून्य;
		पूर्ण
		अगर (tid_head != scbid)
			ahd_stitch_tid_list(ahd, tid_prev, tid_head, tid_next);
		अगर (!SCBID_IS_शून्य(tid_head))
			tid_prev = tid_head;
		अगर (action == SEARCH_PRINT)
			prपूर्णांकk(")\n");
	पूर्ण

	/* Restore saved state. */
	ahd_set_scbptr(ahd, savedscbptr);
	ahd_restore_modes(ahd, saved_modes);
	वापस (found);
पूर्ण

अटल पूर्णांक
ahd_search_scb_list(काष्ठा ahd_softc *ahd, पूर्णांक target, अक्षर channel,
		    पूर्णांक lun, u_पूर्णांक tag, role_t role, uपूर्णांक32_t status,
		    ahd_search_action action, u_पूर्णांक *list_head,
		    u_पूर्णांक *list_tail, u_पूर्णांक tid)
अणु
	काष्ठा	scb *scb;
	u_पूर्णांक	scbid;
	u_पूर्णांक	next;
	u_पूर्णांक	prev;
	पूर्णांक	found;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	found = 0;
	prev = SCB_LIST_शून्य;
	next = *list_head;
	*list_tail = SCB_LIST_शून्य;
	क्रम (scbid = next; !SCBID_IS_शून्य(scbid); scbid = next) अणु
		अगर (scbid >= ahd->scb_data.numscbs) अणु
			prपूर्णांकk("%s:SCB List inconsistency. "
			       "SCB == 0x%x, yet numscbs == 0x%x.",
			       ahd_name(ahd), scbid, ahd->scb_data.numscbs);
			ahd_dump_card_state(ahd);
			panic("for safety");
		पूर्ण
		scb = ahd_lookup_scb(ahd, scbid);
		अगर (scb == शून्य) अणु
			prपूर्णांकk("%s: SCB = %d Not Active!\n",
			       ahd_name(ahd), scbid);
			panic("Waiting List traversal\n");
		पूर्ण
		ahd_set_scbptr(ahd, scbid);
		*list_tail = scbid;
		next = ahd_inw_scbram(ahd, SCB_NEXT);
		अगर (ahd_match_scb(ahd, scb, target, channel,
				  lun, SCB_LIST_शून्य, role) == 0) अणु
			prev = scbid;
			जारी;
		पूर्ण
		found++;
		चयन (action) अणु
		हाल SEARCH_COMPLETE:
			अगर ((scb->flags & SCB_ACTIVE) == 0)
				prपूर्णांकk("Inactive SCB in Waiting List\n");
			ahd_करोne_with_status(ahd, scb, status);
			fallthrough;
		हाल SEARCH_REMOVE:
			ahd_rem_wscb(ahd, scbid, prev, next, tid);
			*list_tail = prev;
			अगर (SCBID_IS_शून्य(prev))
				*list_head = next;
			अवरोध;
		हाल SEARCH_PRINT:
			prपूर्णांकk("0x%x ", scbid);
			fallthrough;
		हाल SEARCH_COUNT:
			prev = scbid;
			अवरोध;
		पूर्ण
		अगर (found > AHD_SCB_MAX)
			panic("SCB LIST LOOP");
	पूर्ण
	अगर (action == SEARCH_COMPLETE
	 || action == SEARCH_REMOVE)
		ahd_outw(ahd, CMDS_PENDING, ahd_inw(ahd, CMDS_PENDING) - found);
	वापस (found);
पूर्ण

अटल व्योम
ahd_stitch_tid_list(काष्ठा ahd_softc *ahd, u_पूर्णांक tid_prev,
		    u_पूर्णांक tid_cur, u_पूर्णांक tid_next)
अणु
	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);

	अगर (SCBID_IS_शून्य(tid_cur)) अणु

		/* Bypass current TID list */
		अगर (SCBID_IS_शून्य(tid_prev)) अणु
			ahd_outw(ahd, WAITING_TID_HEAD, tid_next);
		पूर्ण अन्यथा अणु
			ahd_set_scbptr(ahd, tid_prev);
			ahd_outw(ahd, SCB_NEXT2, tid_next);
		पूर्ण
		अगर (SCBID_IS_शून्य(tid_next))
			ahd_outw(ahd, WAITING_TID_TAIL, tid_prev);
	पूर्ण अन्यथा अणु

		/* Stitch through tid_cur */
		अगर (SCBID_IS_शून्य(tid_prev)) अणु
			ahd_outw(ahd, WAITING_TID_HEAD, tid_cur);
		पूर्ण अन्यथा अणु
			ahd_set_scbptr(ahd, tid_prev);
			ahd_outw(ahd, SCB_NEXT2, tid_cur);
		पूर्ण
		ahd_set_scbptr(ahd, tid_cur);
		ahd_outw(ahd, SCB_NEXT2, tid_next);

		अगर (SCBID_IS_शून्य(tid_next))
			ahd_outw(ahd, WAITING_TID_TAIL, tid_cur);
	पूर्ण
पूर्ण

/*
 * Manipulate the रुकोing क्रम selection list and वापस the
 * scb that follows the one that we हटाओ.
 */
अटल u_पूर्णांक
ahd_rem_wscb(काष्ठा ahd_softc *ahd, u_पूर्णांक scbid,
	     u_पूर्णांक prev, u_पूर्णांक next, u_पूर्णांक tid)
अणु
	u_पूर्णांक tail_offset;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	अगर (!SCBID_IS_शून्य(prev)) अणु
		ahd_set_scbptr(ahd, prev);
		ahd_outw(ahd, SCB_NEXT, next);
	पूर्ण

	/*
	 * SCBs that have MK_MESSAGE set in them may
	 * cause the tail poपूर्णांकer to be updated without
	 * setting the next poपूर्णांकer of the previous tail.
	 * Only clear the tail अगर the हटाओd SCB was
	 * the tail.
	 */
	tail_offset = WAITING_SCB_TAILS + (2 * tid);
	अगर (SCBID_IS_शून्य(next)
	 && ahd_inw(ahd, tail_offset) == scbid)
		ahd_outw(ahd, tail_offset, prev);

	ahd_add_scb_to_मुक्त_list(ahd, scbid);
	वापस (next);
पूर्ण

/*
 * Add the SCB as selected by SCBPTR onto the on chip list of
 * मुक्त hardware SCBs.  This list is empty/unused अगर we are not
 * perक्रमming SCB paging.
 */
अटल व्योम
ahd_add_scb_to_मुक्त_list(काष्ठा ahd_softc *ahd, u_पूर्णांक scbid)
अणु
/* XXX Need some other mechanism to designate "free". */
	/*
	 * Invalidate the tag so that our पात
	 * routines करोn't think it's active.
	ahd_outb(ahd, SCB_TAG, SCB_LIST_शून्य);
	 */
पूर्ण

/******************************** Error Handling ******************************/
/*
 * Abort all SCBs that match the given description (target/channel/lun/tag),
 * setting their status to the passed in status अगर the status has not alपढ़ोy
 * been modअगरied from CAM_REQ_INPROG.  This routine assumes that the sequencer
 * is छोड़ोd beक्रमe it is called.
 */
अटल पूर्णांक
ahd_पात_scbs(काष्ठा ahd_softc *ahd, पूर्णांक target, अक्षर channel,
	       पूर्णांक lun, u_पूर्णांक tag, role_t role, uपूर्णांक32_t status)
अणु
	काष्ठा		scb *scbp;
	काष्ठा		scb *scbp_next;
	u_पूर्णांक		i, j;
	u_पूर्णांक		maxtarget;
	u_पूर्णांक		minlun;
	u_पूर्णांक		maxlun;
	पूर्णांक		found;
	ahd_mode_state	saved_modes;

	/* restore this when we're करोne */
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	found = ahd_search_qinfअगरo(ahd, target, channel, lun, SCB_LIST_शून्य,
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
		minlun = 0;
		maxlun = AHD_NUM_LUNS_NONPKT;
	पूर्ण अन्यथा अगर (lun >= AHD_NUM_LUNS_NONPKT) अणु
		minlun = maxlun = 0;
	पूर्ण अन्यथा अणु
		minlun = lun;
		maxlun = lun + 1;
	पूर्ण

	अगर (role != ROLE_TARGET) अणु
		क्रम (;i < maxtarget; i++) अणु
			क्रम (j = minlun;j < maxlun; j++) अणु
				u_पूर्णांक scbid;
				u_पूर्णांक tcl;

				tcl = BUILD_TCL_RAW(i, 'A', j);
				scbid = ahd_find_busy_tcl(ahd, tcl);
				scbp = ahd_lookup_scb(ahd, scbid);
				अगर (scbp == शून्य
				 || ahd_match_scb(ahd, scbp, target, channel,
						  lun, tag, role) == 0)
					जारी;
				ahd_unbusy_tcl(ahd, BUILD_TCL_RAW(i, 'A', j));
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Don't पात commands that have alपढ़ोy completed,
	 * but haven't quite made it up to the host yet.
	 */
	ahd_flush_qoutfअगरo(ahd);

	/*
	 * Go through the pending CCB list and look क्रम
	 * commands क्रम this target that are still active.
	 * These are other tagged commands that were
	 * disconnected when the reset occurred.
	 */
	scbp_next = LIST_FIRST(&ahd->pending_scbs);
	जबतक (scbp_next != शून्य) अणु
		scbp = scbp_next;
		scbp_next = LIST_NEXT(scbp, pending_links);
		अगर (ahd_match_scb(ahd, scbp, target, channel, lun, tag, role)) अणु
			cam_status ostat;

			ostat = ahd_get_transaction_status(scbp);
			अगर (ostat == CAM_REQ_INPROG)
				ahd_set_transaction_status(scbp, status);
			अगर (ahd_get_transaction_status(scbp) != CAM_REQ_CMP)
				ahd_मुक्तze_scb(scbp);
			अगर ((scbp->flags & SCB_ACTIVE) == 0)
				prपूर्णांकk("Inactive SCB on pending list\n");
			ahd_करोne(ahd, scbp);
			found++;
		पूर्ण
	पूर्ण
	ahd_restore_modes(ahd, saved_modes);
	ahd_platक्रमm_पात_scbs(ahd, target, channel, lun, tag, role, status);
	ahd->flags |= AHD_UPDATE_PEND_CMDS;
	वापस found;
पूर्ण

अटल व्योम
ahd_reset_current_bus(काष्ठा ahd_softc *ahd)
अणु
	uपूर्णांक8_t scsiseq;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	ahd_outb(ahd, SIMODE1, ahd_inb(ahd, SIMODE1) & ~ENSCSIRST);
	scsiseq = ahd_inb(ahd, SCSISEQ0) & ~(ENSELO|ENARBO|SCSIRSTO);
	ahd_outb(ahd, SCSISEQ0, scsiseq | SCSIRSTO);
	ahd_flush_device_ग_लिखोs(ahd);
	ahd_delay(AHD_BUSRESET_DELAY);
	/* Turn off the bus reset */
	ahd_outb(ahd, SCSISEQ0, scsiseq);
	ahd_flush_device_ग_लिखोs(ahd);
	ahd_delay(AHD_BUSRESET_DELAY);
	अगर ((ahd->bugs & AHD_SCSIRST_BUG) != 0) अणु
		/*
		 * 2A Razor #474
		 * Certain chip state is not cleared क्रम
		 * SCSI bus resets that we initiate, so
		 * we must reset the chip.
		 */
		ahd_reset(ahd, /*reinit*/TRUE);
		ahd_पूर्णांकr_enable(ahd, /*enable*/TRUE);
		AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	पूर्ण

	ahd_clear_पूर्णांकstat(ahd);
पूर्ण

पूर्णांक
ahd_reset_channel(काष्ठा ahd_softc *ahd, अक्षर channel, पूर्णांक initiate_reset)
अणु
	काष्ठा	ahd_devinfo caminfo;
	u_पूर्णांक	initiator;
	u_पूर्णांक	target;
	u_पूर्णांक	max_scsiid;
	पूर्णांक	found;
	u_पूर्णांक	fअगरo;
	u_पूर्णांक	next_fअगरo;
	uपूर्णांक8_t scsiseq;

	/*
	 * Check अगर the last bus reset is cleared
	 */
	अगर (ahd->flags & AHD_BUS_RESET_ACTIVE) अणु
		prपूर्णांकk("%s: bus reset still active\n",
		       ahd_name(ahd));
		वापस 0;
	पूर्ण
	ahd->flags |= AHD_BUS_RESET_ACTIVE;

	ahd->pending_device = शून्य;

	ahd_compile_devinfo(&caminfo,
			    CAM_TARGET_WILDCARD,
			    CAM_TARGET_WILDCARD,
			    CAM_LUN_WILDCARD,
			    channel, ROLE_UNKNOWN);
	ahd_छोड़ो(ahd);

	/* Make sure the sequencer is in a safe location. */
	ahd_clear_critical_section(ahd);

	/*
	 * Run our command complete fअगरos to ensure that we perक्रमm
	 * completion processing on any commands that 'completed'
	 * beक्रमe the reset occurred.
	 */
	ahd_run_qoutfअगरo(ahd);
#अगर_घोषित AHD_TARGET_MODE
	अगर ((ahd->flags & AHD_TARGETROLE) != 0) अणु
		ahd_run_tqinfअगरo(ahd, /*छोड़ोd*/TRUE);
	पूर्ण
#पूर्ण_अगर
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	/*
	 * Disable selections so no स्वतःmatic hardware
	 * functions will modअगरy chip state.
	 */
	ahd_outb(ahd, SCSISEQ0, 0);
	ahd_outb(ahd, SCSISEQ1, 0);

	/*
	 * Safely shut करोwn our DMA engines.  Always start with
	 * the FIFO that is not currently active (अगर any are
	 * actively connected).
	 */
	next_fअगरo = fअगरo = ahd_inb(ahd, DFFSTAT) & CURRFIFO;
	अगर (next_fअगरo > CURRFIFO_1)
		/* If disconneced, arbitrarily start with FIFO1. */
		next_fअगरo = fअगरo = 0;
	करो अणु
		next_fअगरo ^= CURRFIFO_1;
		ahd_set_modes(ahd, next_fअगरo, next_fअगरo);
		ahd_outb(ahd, DFCNTRL,
			 ahd_inb(ahd, DFCNTRL) & ~(SCSIEN|HDMAEN));
		जबतक ((ahd_inb(ahd, DFCNTRL) & HDMAENACK) != 0)
			ahd_delay(10);
		/*
		 * Set CURRFIFO to the now inactive channel.
		 */
		ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
		ahd_outb(ahd, DFFSTAT, next_fअगरo);
	पूर्ण जबतक (next_fअगरo != fअगरo);

	/*
	 * Reset the bus अगर we are initiating this reset
	 */
	ahd_clear_msg_state(ahd);
	ahd_outb(ahd, SIMODE1,
		 ahd_inb(ahd, SIMODE1) & ~(ENBUSFREE|ENSCSIRST));

	अगर (initiate_reset)
		ahd_reset_current_bus(ahd);

	ahd_clear_पूर्णांकstat(ahd);

	/*
	 * Clean up all the state inक्रमmation क्रम the
	 * pending transactions on this bus.
	 */
	found = ahd_पात_scbs(ahd, CAM_TARGET_WILDCARD, channel,
			       CAM_LUN_WILDCARD, SCB_LIST_शून्य,
			       ROLE_UNKNOWN, CAM_SCSI_BUS_RESET);

	/*
	 * Cleanup anything left in the FIFOs.
	 */
	ahd_clear_fअगरo(ahd, 0);
	ahd_clear_fअगरo(ahd, 1);

	/*
	 * Clear SCSI पूर्णांकerrupt status
	 */
	ahd_outb(ahd, CLRSINT1, CLRSCSIRSTI);

	/*
	 * Reenable selections
	 */
	ahd_outb(ahd, SIMODE1, ahd_inb(ahd, SIMODE1) | ENSCSIRST);
	scsiseq = ahd_inb(ahd, SCSISEQ_TEMPLATE);
	ahd_outb(ahd, SCSISEQ1, scsiseq & (ENSELI|ENRSELI|ENAUTOATNP));

	max_scsiid = (ahd->features & AHD_WIDE) ? 15 : 7;
#अगर_घोषित AHD_TARGET_MODE
	/*
	 * Send an immediate notअगरy ccb to all target more peripheral
	 * drivers affected by this action.
	 */
	क्रम (target = 0; target <= max_scsiid; target++) अणु
		काष्ठा ahd_पंचांगode_tstate* tstate;
		u_पूर्णांक lun;

		tstate = ahd->enabled_tarमाला_लो[target];
		अगर (tstate == शून्य)
			जारी;
		क्रम (lun = 0; lun < AHD_NUM_LUNS; lun++) अणु
			काष्ठा ahd_पंचांगode_lstate* lstate;

			lstate = tstate->enabled_luns[lun];
			अगर (lstate == शून्य)
				जारी;

			ahd_queue_lstate_event(ahd, lstate, CAM_TARGET_WILDCARD,
					       EVENT_TYPE_BUS_RESET, /*arg*/0);
			ahd_send_lstate_events(ahd, lstate);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/*
	 * Revert to async/narrow transfers until we renegotiate.
	 */
	क्रम (target = 0; target <= max_scsiid; target++) अणु

		अगर (ahd->enabled_tarमाला_लो[target] == शून्य)
			जारी;
		क्रम (initiator = 0; initiator <= max_scsiid; initiator++) अणु
			काष्ठा ahd_devinfo devinfo;

			ahd_compile_devinfo(&devinfo, target, initiator,
					    CAM_LUN_WILDCARD,
					    'A', ROLE_UNKNOWN);
			ahd_set_width(ahd, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
				      AHD_TRANS_CUR, /*छोड़ोd*/TRUE);
			ahd_set_syncrate(ahd, &devinfo, /*period*/0,
					 /*offset*/0, /*ppr_options*/0,
					 AHD_TRANS_CUR, /*छोड़ोd*/TRUE);
		पूर्ण
	पूर्ण

	/* Notअगरy the XPT that a bus reset occurred */
	ahd_send_async(ahd, caminfo.channel, CAM_TARGET_WILDCARD,
		       CAM_LUN_WILDCARD, AC_BUS_RESET);

	ahd_restart(ahd);

	वापस (found);
पूर्ण

/**************************** Statistics Processing ***************************/
अटल व्योम
ahd_stat_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा	ahd_softc *ahd = from_समयr(ahd, t, stat_समयr);
	u_दीर्घ	s;
	पूर्णांक	enपूर्णांक_coal;

	ahd_lock(ahd, &s);

	enपूर्णांक_coal = ahd->hs_mailbox & ENINT_COALESCE;
	अगर (ahd->cmdcmplt_total > ahd->पूर्णांक_coalescing_threshold)
		enपूर्णांक_coal |= ENINT_COALESCE;
	अन्यथा अगर (ahd->cmdcmplt_total < ahd->पूर्णांक_coalescing_stop_threshold)
		enपूर्णांक_coal &= ~ENINT_COALESCE;

	अगर (enपूर्णांक_coal != (ahd->hs_mailbox & ENINT_COALESCE)) अणु
		ahd_enable_coalescing(ahd, enपूर्णांक_coal);
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_INT_COALESCING) != 0)
			prपूर्णांकk("%s: Interrupt coalescing "
			       "now %sabled. Cmds %d\n",
			       ahd_name(ahd),
			       (enपूर्णांक_coal & ENINT_COALESCE) ? "en" : "dis",
			       ahd->cmdcmplt_total);
#पूर्ण_अगर
	पूर्ण

	ahd->cmdcmplt_bucket = (ahd->cmdcmplt_bucket+1) & (AHD_STAT_BUCKETS-1);
	ahd->cmdcmplt_total -= ahd->cmdcmplt_counts[ahd->cmdcmplt_bucket];
	ahd->cmdcmplt_counts[ahd->cmdcmplt_bucket] = 0;
	ahd_समयr_reset(&ahd->stat_समयr, AHD_STAT_UPDATE_US);
	ahd_unlock(ahd, &s);
पूर्ण

/****************************** Status Processing *****************************/

अटल व्योम
ahd_handle_scsi_status(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	काष्ठा	hardware_scb *hscb;
	पूर्णांक	छोड़ोd;

	/*
	 * The sequencer मुक्तzes its select-out queue
	 * anyसमय a SCSI status error occurs.  We must
	 * handle the error and increment our qमुक्तze count
	 * to allow the sequencer to जारी.  We करोn't
	 * bother clearing critical sections here since all
	 * operations are on data काष्ठाures that the sequencer
	 * is not touching once the queue is frozen.
	 */
	hscb = scb->hscb;

	अगर (ahd_is_छोड़ोd(ahd)) अणु
		छोड़ोd = 1;
	पूर्ण अन्यथा अणु
		छोड़ोd = 0;
		ahd_छोड़ो(ahd);
	पूर्ण

	/* Freeze the queue until the client sees the error. */
	ahd_मुक्तze_devq(ahd, scb);
	ahd_मुक्तze_scb(scb);
	ahd->qमुक्तze_cnt++;
	ahd_outw(ahd, KERNEL_QFREEZE_COUNT, ahd->qमुक्तze_cnt);

	अगर (छोड़ोd == 0)
		ahd_unछोड़ो(ahd);

	/* Don't want to clobber the original sense code */
	अगर ((scb->flags & SCB_SENSE) != 0) अणु
		/*
		 * Clear the SCB_SENSE Flag and perक्रमm
		 * a normal command completion.
		 */
		scb->flags &= ~SCB_SENSE;
		ahd_set_transaction_status(scb, CAM_AUTOSENSE_FAIL);
		ahd_करोne(ahd, scb);
		वापस;
	पूर्ण
	ahd_set_transaction_status(scb, CAM_SCSI_STATUS_ERROR);
	ahd_set_scsi_status(scb, hscb->shared_data.istatus.scsi_status);
	चयन (hscb->shared_data.istatus.scsi_status) अणु
	हाल STATUS_PKT_SENSE:
	अणु
		काष्ठा scsi_status_iu_header *siu;

		ahd_sync_sense(ahd, scb, BUS_DMASYNC_POSTREAD);
		siu = (काष्ठा scsi_status_iu_header *)scb->sense_data;
		ahd_set_scsi_status(scb, siu->status);
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_SENSE) != 0) अणु
			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("SCB 0x%x Received PKT Status of 0x%x\n",
			       SCB_GET_TAG(scb), siu->status);
			prपूर्णांकk("\tflags = 0x%x, sense len = 0x%x, "
			       "pktfail = 0x%x\n",
			       siu->flags, scsi_4btoul(siu->sense_length),
			       scsi_4btoul(siu->pkt_failures_length));
		पूर्ण
#पूर्ण_अगर
		अगर ((siu->flags & SIU_RSPVALID) != 0) अणु
			ahd_prपूर्णांक_path(ahd, scb);
			अगर (scsi_4btoul(siu->pkt_failures_length) < 4) अणु
				prपूर्णांकk("Unable to parse pkt_failures\n");
			पूर्ण अन्यथा अणु

				चयन (SIU_PKTFAIL_CODE(siu)) अणु
				हाल SIU_PFC_NONE:
					prपूर्णांकk("No packet failure found\n");
					अवरोध;
				हाल SIU_PFC_CIU_FIELDS_INVALID:
					prपूर्णांकk("Invalid Command IU Field\n");
					अवरोध;
				हाल SIU_PFC_TMF_NOT_SUPPORTED:
					prपूर्णांकk("TMF not supported\n");
					अवरोध;
				हाल SIU_PFC_TMF_FAILED:
					prपूर्णांकk("TMF failed\n");
					अवरोध;
				हाल SIU_PFC_INVALID_TYPE_CODE:
					prपूर्णांकk("Invalid L_Q Type code\n");
					अवरोध;
				हाल SIU_PFC_ILLEGAL_REQUEST:
					prपूर्णांकk("Illegal request\n");
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (siu->status == SAM_STAT_GOOD)
				ahd_set_transaction_status(scb,
							   CAM_REQ_CMP_ERR);
		पूर्ण
		अगर ((siu->flags & SIU_SNSVALID) != 0) अणु
			scb->flags |= SCB_PKT_SENSE;
#अगर_घोषित AHD_DEBUG
			अगर ((ahd_debug & AHD_SHOW_SENSE) != 0)
				prपूर्णांकk("Sense data available\n");
#पूर्ण_अगर
		पूर्ण
		ahd_करोne(ahd, scb);
		अवरोध;
	पूर्ण
	हाल SAM_STAT_COMMAND_TERMINATED:
	हाल SAM_STAT_CHECK_CONDITION:
	अणु
		काष्ठा ahd_devinfo devinfo;
		काष्ठा ahd_dma_seg *sg;
		काष्ठा scsi_sense *sc;
		काष्ठा ahd_initiator_tinfo *targ_info;
		काष्ठा ahd_पंचांगode_tstate *tstate;
		काष्ठा ahd_transinfo *tinfo;
#अगर_घोषित AHD_DEBUG
		अगर (ahd_debug & AHD_SHOW_SENSE) अणु
			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("SCB %d: requests Check Status\n",
			       SCB_GET_TAG(scb));
		पूर्ण
#पूर्ण_अगर

		अगर (ahd_perक्रमm_स्वतःsense(scb) == 0)
			अवरोध;

		ahd_compile_devinfo(&devinfo, SCB_GET_OUR_ID(scb),
				    SCB_GET_TARGET(ahd, scb),
				    SCB_GET_LUN(scb),
				    SCB_GET_CHANNEL(ahd, scb),
				    ROLE_INITIATOR);
		targ_info = ahd_fetch_transinfo(ahd,
						devinfo.channel,
						devinfo.our_scsiid,
						devinfo.target,
						&tstate);
		tinfo = &targ_info->curr;
		sg = scb->sg_list;
		sc = (काष्ठा scsi_sense *)hscb->shared_data.idata.cdb;
		/*
		 * Save off the residual अगर there is one.
		 */
		ahd_update_residual(ahd, scb);
#अगर_घोषित AHD_DEBUG
		अगर (ahd_debug & AHD_SHOW_SENSE) अणु
			ahd_prपूर्णांक_path(ahd, scb);
			prपूर्णांकk("Sending Sense\n");
		पूर्ण
#पूर्ण_अगर
		scb->sg_count = 0;
		sg = ahd_sg_setup(ahd, scb, sg, ahd_get_sense_bufaddr(ahd, scb),
				  ahd_get_sense_bufsize(ahd, scb),
				  /*last*/TRUE);
		sc->opcode = REQUEST_SENSE;
		sc->byte2 = 0;
		अगर (tinfo->protocol_version <= SCSI_REV_2
		 && SCB_GET_LUN(scb) < 8)
			sc->byte2 = SCB_GET_LUN(scb) << 5;
		sc->unused[0] = 0;
		sc->unused[1] = 0;
		sc->length = ahd_get_sense_bufsize(ahd, scb);
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
		अगर (ahd_get_residual(scb) == ahd_get_transfer_length(scb)) अणु
			ahd_update_neg_request(ahd, &devinfo,
					       tstate, targ_info,
					       AHD_NEG_IF_NON_ASYNC);
		पूर्ण
		अगर (tstate->स्वतः_negotiate & devinfo.target_mask) अणु
			hscb->control |= MK_MESSAGE;
			scb->flags &=
			    ~(SCB_NEGOTIATE|SCB_ABORT|SCB_DEVICE_RESET);
			scb->flags |= SCB_AUTO_NEGOTIATE;
		पूर्ण
		hscb->cdb_len = माप(*sc);
		ahd_setup_data_scb(ahd, scb);
		scb->flags |= SCB_SENSE;
		ahd_queue_scb(ahd, scb);
		अवरोध;
	पूर्ण
	हाल SAM_STAT_GOOD:
		prपूर्णांकk("%s: Interrupted for status of 0???\n",
		       ahd_name(ahd));
		fallthrough;
	शेष:
		ahd_करोne(ahd, scb);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
ahd_handle_scb_status(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	अगर (scb->hscb->shared_data.istatus.scsi_status != 0) अणु
		ahd_handle_scsi_status(ahd, scb);
	पूर्ण अन्यथा अणु
		ahd_calc_residual(ahd, scb);
		ahd_करोne(ahd, scb);
	पूर्ण
पूर्ण

/*
 * Calculate the residual क्रम a just completed SCB.
 */
अटल व्योम
ahd_calc_residual(काष्ठा ahd_softc *ahd, काष्ठा scb *scb)
अणु
	काष्ठा hardware_scb *hscb;
	काष्ठा initiator_status *spkt;
	uपूर्णांक32_t sgptr;
	uपूर्णांक32_t resid_sgptr;
	uपूर्णांक32_t resid;

	/*
	 * 5 हालs.
	 * 1) No residual.
	 *    SG_STATUS_VALID clear in sgptr.
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
	sgptr = ahd_le32toh(hscb->sgptr);
	अगर ((sgptr & SG_STATUS_VALID) == 0)
		/* Case 1 */
		वापस;
	sgptr &= ~SG_STATUS_VALID;

	अगर ((sgptr & SG_LIST_शून्य) != 0)
		/* Case 2 */
		वापस;

	/*
	 * Residual fields are the same in both
	 * target and initiator status packets,
	 * so we can always use the initiator fields
	 * regardless of the role क्रम this SCB.
	 */
	spkt = &hscb->shared_data.istatus;
	resid_sgptr = ahd_le32toh(spkt->residual_sgptr);
	अगर ((sgptr & SG_FULL_RESID) != 0) अणु
		/* Case 3 */
		resid = ahd_get_transfer_length(scb);
	पूर्ण अन्यथा अगर ((resid_sgptr & SG_LIST_शून्य) != 0) अणु
		/* Case 4 */
		वापस;
	पूर्ण अन्यथा अगर ((resid_sgptr & SG_OVERRUN_RESID) != 0) अणु
		ahd_prपूर्णांक_path(ahd, scb);
		prपूर्णांकk("data overrun detected Tag == 0x%x.\n",
		       SCB_GET_TAG(scb));
		ahd_मुक्तze_devq(ahd, scb);
		ahd_set_transaction_status(scb, CAM_DATA_RUN_ERR);
		ahd_मुक्तze_scb(scb);
		वापस;
	पूर्ण अन्यथा अगर ((resid_sgptr & ~SG_PTR_MASK) != 0) अणु
		panic("Bogus resid sgptr value 0x%x\n", resid_sgptr);
		/* NOTREACHED */
	पूर्ण अन्यथा अणु
		काष्ठा ahd_dma_seg *sg;

		/*
		 * Reमुख्यder of the SG where the transfer
		 * stopped.
		 */
		resid = ahd_le32toh(spkt->residual_datacnt) & AHD_SG_LEN_MASK;
		sg = ahd_sg_bus_to_virt(ahd, scb, resid_sgptr & SG_PTR_MASK);

		/* The residual sg_ptr always poपूर्णांकs to the next sg */
		sg--;

		/*
		 * Add up the contents of all residual
		 * SG segments that are after the SG where
		 * the transfer stopped.
		 */
		जबतक ((ahd_le32toh(sg->len) & AHD_DMA_LAST_SEG) == 0) अणु
			sg++;
			resid += ahd_le32toh(sg->len) & AHD_SG_LEN_MASK;
		पूर्ण
	पूर्ण
	अगर ((scb->flags & SCB_SENSE) == 0)
		ahd_set_residual(scb, resid);
	अन्यथा
		ahd_set_sense_residual(scb, resid);

#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_MISC) != 0) अणु
		ahd_prपूर्णांक_path(ahd, scb);
		prपूर्णांकk("Handled %sResidual of %d bytes\n",
		       (scb->flags & SCB_SENSE) ? "Sense " : "", resid);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/******************************* Target Mode **********************************/
#अगर_घोषित AHD_TARGET_MODE
/*
 * Add a target mode event to this lun's queue
 */
अटल व्योम
ahd_queue_lstate_event(काष्ठा ahd_softc *ahd, काष्ठा ahd_पंचांगode_lstate *lstate,
		       u_पूर्णांक initiator_id, u_पूर्णांक event_type, u_पूर्णांक event_arg)
अणु
	काष्ठा ahd_पंचांगode_event *event;
	पूर्णांक pending;

	xpt_मुक्तze_devq(lstate->path, /*count*/1);
	अगर (lstate->event_w_idx >= lstate->event_r_idx)
		pending = lstate->event_w_idx - lstate->event_r_idx;
	अन्यथा
		pending = AHD_TMODE_EVENT_BUFFER_SIZE + 1
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

	अगर (pending == AHD_TMODE_EVENT_BUFFER_SIZE) अणु
		xpt_prपूर्णांक_path(lstate->path);
		prपूर्णांकk("immediate event %x:%x lost\n",
		       lstate->event_buffer[lstate->event_r_idx].event_type,
		       lstate->event_buffer[lstate->event_r_idx].event_arg);
		lstate->event_r_idx++;
		अगर (lstate->event_r_idx == AHD_TMODE_EVENT_BUFFER_SIZE)
			lstate->event_r_idx = 0;
		xpt_release_devq(lstate->path, /*count*/1, /*runqueue*/FALSE);
	पूर्ण

	event = &lstate->event_buffer[lstate->event_w_idx];
	event->initiator_id = initiator_id;
	event->event_type = event_type;
	event->event_arg = event_arg;
	lstate->event_w_idx++;
	अगर (lstate->event_w_idx == AHD_TMODE_EVENT_BUFFER_SIZE)
		lstate->event_w_idx = 0;
पूर्ण

/*
 * Send any target mode events queued up रुकोing
 * क्रम immediate notअगरy resources.
 */
व्योम
ahd_send_lstate_events(काष्ठा ahd_softc *ahd, काष्ठा ahd_पंचांगode_lstate *lstate)
अणु
	काष्ठा ccb_hdr *ccbh;
	काष्ठा ccb_immed_notअगरy *inot;

	जबतक (lstate->event_r_idx != lstate->event_w_idx
	    && (ccbh = SLIST_FIRST(&lstate->immed_notअगरies)) != शून्य) अणु
		काष्ठा ahd_पंचांगode_event *event;

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
		अगर (lstate->event_r_idx == AHD_TMODE_EVENT_BUFFER_SIZE)
			lstate->event_r_idx = 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/******************** Sequencer Program Patching/Download *********************/

#अगर_घोषित AHD_DUMP_SEQ
व्योम
ahd_dumpseq(काष्ठा ahd_softc* ahd)
अणु
	पूर्णांक i;
	पूर्णांक max_prog;

	max_prog = 2048;

	ahd_outb(ahd, SEQCTL0, PERRORDIS|FAILDIS|FASTMODE|LOADRAM);
	ahd_outw(ahd, PRGMCNT, 0);
	क्रम (i = 0; i < max_prog; i++) अणु
		uपूर्णांक8_t ins_bytes[4];

		ahd_insb(ahd, SEQRAM, ins_bytes, 4);
		prपूर्णांकk("0x%08x\n", ins_bytes[0] << 24
				 | ins_bytes[1] << 16
				 | ins_bytes[2] << 8
				 | ins_bytes[3]);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम
ahd_loadseq(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा	cs cs_table[NUM_CRITICAL_SECTIONS];
	u_पूर्णांक	begin_set[NUM_CRITICAL_SECTIONS];
	u_पूर्णांक	end_set[NUM_CRITICAL_SECTIONS];
	स्थिर काष्ठा patch *cur_patch;
	u_पूर्णांक	cs_count;
	u_पूर्णांक	cur_cs;
	u_पूर्णांक	i;
	पूर्णांक	करोwnloaded;
	u_पूर्णांक	skip_addr;
	u_पूर्णांक	sg_prefetch_cnt;
	u_पूर्णांक	sg_prefetch_cnt_limit;
	u_पूर्णांक	sg_prefetch_align;
	u_पूर्णांक	sg_size;
	u_पूर्णांक	cacheline_mask;
	uपूर्णांक8_t	करोwnload_स्थिरs[DOWNLOAD_CONST_COUNT];

	अगर (bootverbose)
		prपूर्णांकk("%s: Downloading Sequencer Program...",
		       ahd_name(ahd));

#अगर DOWNLOAD_CONST_COUNT != 8
#त्रुटि "Download Const Mismatch"
#पूर्ण_अगर
	/*
	 * Start out with 0 critical sections
	 * that apply to this firmware load.
	 */
	cs_count = 0;
	cur_cs = 0;
	स_रखो(begin_set, 0, माप(begin_set));
	स_रखो(end_set, 0, माप(end_set));

	/*
	 * Setup करोwnloadable स्थिरant table.
	 *
	 * The computation क्रम the S/G prefetch variables is
	 * a bit complicated.  We would like to always fetch
	 * in terms of cachelined sized increments.  However,
	 * अगर the cacheline is not an even multiple of the
	 * SG element size or is larger than our SG RAM, using
	 * just the cache size might leave us with only a portion
	 * of an SG element at the tail of a prefetch.  If the
	 * cacheline is larger than our S/G prefetch buffer less
	 * the size of an SG element, we may round करोwn to a cacheline
	 * that करोesn't contain any or all of the S/G of पूर्णांकerest
	 * within the bounds of our S/G ram.  Provide variables to
	 * the sequencer that will allow it to handle these edge
	 * हालs.
	 */
	/* Start by aligning to the nearest cacheline. */
	sg_prefetch_align = ahd->pci_cachesize;
	अगर (sg_prefetch_align == 0)
		sg_prefetch_align = 8;
	/* Round करोwn to the nearest घातer of 2. */
	जबतक (घातerof2(sg_prefetch_align) == 0)
		sg_prefetch_align--;

	cacheline_mask = sg_prefetch_align - 1;

	/*
	 * If the cacheline boundary is greater than half our prefetch RAM
	 * we risk not being able to fetch even a single complete S/G
	 * segment अगर we align to that boundary.
	 */
	अगर (sg_prefetch_align > CCSGADDR_MAX/2)
		sg_prefetch_align = CCSGADDR_MAX/2;
	/* Start by fetching a single cacheline. */
	sg_prefetch_cnt = sg_prefetch_align;
	/*
	 * Increment the prefetch count by cachelines until
	 * at least one S/G element will fit.
	 */
	sg_size = माप(काष्ठा ahd_dma_seg);
	अगर ((ahd->flags & AHD_64BIT_ADDRESSING) != 0)
		sg_size = माप(काष्ठा ahd_dma64_seg);
	जबतक (sg_prefetch_cnt < sg_size)
		sg_prefetch_cnt += sg_prefetch_align;
	/*
	 * If the cacheline is not an even multiple of
	 * the S/G size, we may only get a partial S/G when
	 * we align. Add a cacheline अगर this is the हाल.
	 */
	अगर ((sg_prefetch_align % sg_size) != 0
	 && (sg_prefetch_cnt < CCSGADDR_MAX))
		sg_prefetch_cnt += sg_prefetch_align;
	/*
	 * Lastly, compute a value that the sequencer can use
	 * to determine अगर the reमुख्यder of the CCSGRAM buffer
	 * has a full S/G element in it.
	 */
	sg_prefetch_cnt_limit = -(sg_prefetch_cnt - sg_size + 1);
	करोwnload_स्थिरs[SG_PREFETCH_CNT] = sg_prefetch_cnt;
	करोwnload_स्थिरs[SG_PREFETCH_CNT_LIMIT] = sg_prefetch_cnt_limit;
	करोwnload_स्थिरs[SG_PREFETCH_ALIGN_MASK] = ~(sg_prefetch_align - 1);
	करोwnload_स्थिरs[SG_PREFETCH_ADDR_MASK] = (sg_prefetch_align - 1);
	करोwnload_स्थिरs[SG_SIZखातापूर्ण] = sg_size;
	करोwnload_स्थिरs[PKT_OVERRUN_BUFOFFSET] =
		(ahd->overrun_buf - (uपूर्णांक8_t *)ahd->qoutfअगरo) / 256;
	करोwnload_स्थिरs[SCB_TRANSFER_SIZE] = SCB_TRANSFER_SIZE_1BYTE_LUN;
	करोwnload_स्थिरs[CACHELINE_MASK] = cacheline_mask;
	cur_patch = patches;
	करोwnloaded = 0;
	skip_addr = 0;
	ahd_outb(ahd, SEQCTL0, PERRORDIS|FAILDIS|FASTMODE|LOADRAM);
	ahd_outw(ahd, PRGMCNT, 0);

	क्रम (i = 0; i < माप(seqprog)/4; i++) अणु
		अगर (ahd_check_patch(ahd, &cur_patch, i, &skip_addr) == 0) अणु
			/*
			 * Don't करोwnload this inकाष्ठाion as it
			 * is in a patch that was हटाओd.
			 */
			जारी;
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
		ahd_करोwnload_instr(ahd, i, करोwnload_स्थिरs);
		करोwnloaded++;
	पूर्ण

	ahd->num_critical_sections = cs_count;
	अगर (cs_count != 0) अणु

		cs_count *= माप(काष्ठा cs);
		ahd->critical_sections = kmemdup(cs_table, cs_count, GFP_ATOMIC);
		अगर (ahd->critical_sections == शून्य)
			panic("ahd_loadseq: Could not malloc");
	पूर्ण
	ahd_outb(ahd, SEQCTL0, PERRORDIS|FAILDIS|FASTMODE);

	अगर (bootverbose) अणु
		prपूर्णांकk(" %d instructions downloaded\n", करोwnloaded);
		prपूर्णांकk("%s: Features 0x%x, Bugs 0x%x, Flags 0x%x\n",
		       ahd_name(ahd), ahd->features, ahd->bugs, ahd->flags);
	पूर्ण
पूर्ण

अटल पूर्णांक
ahd_check_patch(काष्ठा ahd_softc *ahd, स्थिर काष्ठा patch **start_patch,
		u_पूर्णांक start_instr, u_पूर्णांक *skip_addr)
अणु
	स्थिर काष्ठा patch *cur_patch;
	स्थिर काष्ठा patch *last_patch;
	u_पूर्णांक	num_patches;

	num_patches = ARRAY_SIZE(patches);
	last_patch = &patches[num_patches];
	cur_patch = *start_patch;

	जबतक (cur_patch < last_patch && start_instr == cur_patch->begin) अणु

		अगर (cur_patch->patch_func(ahd) == 0) अणु

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

अटल u_पूर्णांक
ahd_resolve_seqaddr(काष्ठा ahd_softc *ahd, u_पूर्णांक address)
अणु
	स्थिर काष्ठा patch *cur_patch;
	पूर्णांक address_offset;
	u_पूर्णांक skip_addr;
	u_पूर्णांक i;

	address_offset = 0;
	cur_patch = patches;
	skip_addr = 0;

	क्रम (i = 0; i < address;) अणु

		ahd_check_patch(ahd, &cur_patch, i, &skip_addr);

		अगर (skip_addr > i) अणु
			पूर्णांक end_addr;

			end_addr = min(address, skip_addr);
			address_offset += end_addr - i;
			i = skip_addr;
		पूर्ण अन्यथा अणु
			i++;
		पूर्ण
	पूर्ण
	वापस (address - address_offset);
पूर्ण

अटल व्योम
ahd_करोwnload_instr(काष्ठा ahd_softc *ahd, u_पूर्णांक instrptr, uपूर्णांक8_t *dस्थिरs)
अणु
	जोड़	ins_क्रमmats instr;
	काष्ठा	ins_क्रमmat1 *fmt1_ins;
	काष्ठा	ins_क्रमmat3 *fmt3_ins;
	u_पूर्णांक	opcode;

	/*
	 * The firmware is always compiled पूर्णांकo a little endian क्रमmat.
	 */
	instr.पूर्णांकeger = ahd_le32toh(*(uपूर्णांक32_t*)&seqprog[instrptr * 4]);

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
		fmt3_ins = &instr.क्रमmat3;
		fmt3_ins->address = ahd_resolve_seqaddr(ahd, fmt3_ins->address);
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
		fallthrough;
	हाल AIC_OP_ROL:
	अणु
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

		/* The sequencer is a little endian cpu */
		instr.पूर्णांकeger = ahd_htole32(instr.पूर्णांकeger);
		ahd_outsb(ahd, SEQRAM, instr.bytes, 4);
		अवरोध;
	पूर्ण
	शेष:
		panic("Unknown opcode encountered in seq program");
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
ahd_probe_stack_size(काष्ठा ahd_softc *ahd)
अणु
	पूर्णांक last_probe;

	last_probe = 0;
	जबतक (1) अणु
		पूर्णांक i;

		/*
		 * We aव्योम using 0 as a pattern to aव्योम
		 * confusion अगर the stack implementation
		 * "back-fills" with zeros when "poping'
		 * entries.
		 */
		क्रम (i = 1; i <= last_probe+1; i++) अणु
		       ahd_outb(ahd, STACK, i & 0xFF);
		       ahd_outb(ahd, STACK, (i >> 8) & 0xFF);
		पूर्ण

		/* Verअगरy */
		क्रम (i = last_probe+1; i > 0; i--) अणु
			u_पूर्णांक stack_entry;

			stack_entry = ahd_inb(ahd, STACK)
				    |(ahd_inb(ahd, STACK) << 8);
			अगर (stack_entry != i)
				जाओ sized;
		पूर्ण
		last_probe++;
	पूर्ण
sized:
	वापस (last_probe);
पूर्ण

पूर्णांक
ahd_prपूर्णांक_रेजिस्टर(स्थिर ahd_reg_parse_entry_t *table, u_पूर्णांक num_entries,
		   स्थिर अक्षर *name, u_पूर्णांक address, u_पूर्णांक value,
		   u_पूर्णांक *cur_column, u_पूर्णांक wrap_poपूर्णांक)
अणु
	पूर्णांक	prपूर्णांकed;
	u_पूर्णांक	prपूर्णांकed_mask;

	अगर (cur_column != शून्य && *cur_column >= wrap_poपूर्णांक) अणु
		prपूर्णांकk("\n");
		*cur_column = 0;
	पूर्ण
	prपूर्णांकed = prपूर्णांकk("%s[0x%x]", name, value);
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
ahd_dump_card_state(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा scb	*scb;
	ahd_mode_state	 saved_modes;
	u_पूर्णांक		 dfख_स्थिति;
	पूर्णांक		 छोड़ोd;
	u_पूर्णांक		 scb_index;
	u_पूर्णांक		 saved_scb_index;
	u_पूर्णांक		 cur_col;
	पूर्णांक		 i;

	अगर (ahd_is_छोड़ोd(ahd)) अणु
		छोड़ोd = 1;
	पूर्ण अन्यथा अणु
		छोड़ोd = 0;
		ahd_छोड़ो(ahd);
	पूर्ण
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	prपूर्णांकk(">>>>>>>>>>>>>>>>>> Dump Card State Begins <<<<<<<<<<<<<<<<<\n"
	       "%s: Dumping Card State at program address 0x%x Mode 0x%x\n",
	       ahd_name(ahd),
	       ahd_inw(ahd, CURADDR),
	       ahd_build_mode_state(ahd, ahd->saved_src_mode,
				    ahd->saved_dst_mode));
	अगर (छोड़ोd)
		prपूर्णांकk("Card was paused\n");

	अगर (ahd_check_cmdcmpltqueues(ahd))
		prपूर्णांकk("Completions are pending\n");

	/*
	 * Mode independent रेजिस्टरs.
	 */
	cur_col = 0;
	ahd_पूर्णांकstat_prपूर्णांक(ahd_inb(ahd, INTSTAT), &cur_col, 50);
	ahd_seloid_prपूर्णांक(ahd_inb(ahd, SELOID), &cur_col, 50);
	ahd_selid_prपूर्णांक(ahd_inb(ahd, SELID), &cur_col, 50);
	ahd_hs_mailbox_prपूर्णांक(ahd_inb(ahd, LOCAL_HS_MAILBOX), &cur_col, 50);
	ahd_पूर्णांकctl_prपूर्णांक(ahd_inb(ahd, INTCTL), &cur_col, 50);
	ahd_seqपूर्णांकstat_prपूर्णांक(ahd_inb(ahd, SEQINTSTAT), &cur_col, 50);
	ahd_saved_mode_prपूर्णांक(ahd_inb(ahd, SAVED_MODE), &cur_col, 50);
	ahd_dfख_स्थिति_prपूर्णांक(ahd_inb(ahd, DFFSTAT), &cur_col, 50);
	ahd_scsisigi_prपूर्णांक(ahd_inb(ahd, SCSISIGI), &cur_col, 50);
	ahd_scsiphase_prपूर्णांक(ahd_inb(ahd, SCSIPHASE), &cur_col, 50);
	ahd_scsibus_prपूर्णांक(ahd_inb(ahd, SCSIBUS), &cur_col, 50);
	ahd_lastphase_prपूर्णांक(ahd_inb(ahd, LASTPHASE), &cur_col, 50);
	ahd_scsiseq0_prपूर्णांक(ahd_inb(ahd, SCSISEQ0), &cur_col, 50);
	ahd_scsiseq1_prपूर्णांक(ahd_inb(ahd, SCSISEQ1), &cur_col, 50);
	ahd_seqctl0_prपूर्णांक(ahd_inb(ahd, SEQCTL0), &cur_col, 50);
	ahd_seqपूर्णांकctl_prपूर्णांक(ahd_inb(ahd, SEQINTCTL), &cur_col, 50);
	ahd_seq_flags_prपूर्णांक(ahd_inb(ahd, SEQ_FLAGS), &cur_col, 50);
	ahd_seq_flags2_prपूर्णांक(ahd_inb(ahd, SEQ_FLAGS2), &cur_col, 50);
	ahd_qमुक्तze_count_prपूर्णांक(ahd_inw(ahd, QFREEZE_COUNT), &cur_col, 50);
	ahd_kernel_qमुक्तze_count_prपूर्णांक(ahd_inw(ahd, KERNEL_QFREEZE_COUNT),
				       &cur_col, 50);
	ahd_mk_message_scb_prपूर्णांक(ahd_inw(ahd, MK_MESSAGE_SCB), &cur_col, 50);
	ahd_mk_message_scsiid_prपूर्णांक(ahd_inb(ahd, MK_MESSAGE_SCSIID),
				    &cur_col, 50);
	ahd_sstat0_prपूर्णांक(ahd_inb(ahd, SSTAT0), &cur_col, 50);
	ahd_sstat1_prपूर्णांक(ahd_inb(ahd, SSTAT1), &cur_col, 50);
	ahd_sstat2_prपूर्णांक(ahd_inb(ahd, SSTAT2), &cur_col, 50);
	ahd_sstat3_prपूर्णांक(ahd_inb(ahd, SSTAT3), &cur_col, 50);
	ahd_perrdiag_prपूर्णांक(ahd_inb(ahd, PERRDIAG), &cur_col, 50);
	ahd_simode1_prपूर्णांक(ahd_inb(ahd, SIMODE1), &cur_col, 50);
	ahd_lqistat0_prपूर्णांक(ahd_inb(ahd, LQISTAT0), &cur_col, 50);
	ahd_lqistat1_prपूर्णांक(ahd_inb(ahd, LQISTAT1), &cur_col, 50);
	ahd_lqistat2_prपूर्णांक(ahd_inb(ahd, LQISTAT2), &cur_col, 50);
	ahd_lqostat0_prपूर्णांक(ahd_inb(ahd, LQOSTAT0), &cur_col, 50);
	ahd_lqostat1_prपूर्णांक(ahd_inb(ahd, LQOSTAT1), &cur_col, 50);
	ahd_lqostat2_prपूर्णांक(ahd_inb(ahd, LQOSTAT2), &cur_col, 50);
	prपूर्णांकk("\n");
	prपूर्णांकk("\nSCB Count = %d CMDS_PENDING = %d LASTSCB 0x%x "
	       "CURRSCB 0x%x NEXTSCB 0x%x\n",
	       ahd->scb_data.numscbs, ahd_inw(ahd, CMDS_PENDING),
	       ahd_inw(ahd, LASTSCB), ahd_inw(ahd, CURRSCB),
	       ahd_inw(ahd, NEXTSCB));
	cur_col = 0;
	/* QINFIFO */
	ahd_search_qinfअगरo(ahd, CAM_TARGET_WILDCARD, ALL_CHANNELS,
			   CAM_LUN_WILDCARD, SCB_LIST_शून्य,
			   ROLE_UNKNOWN, /*status*/0, SEARCH_PRINT);
	saved_scb_index = ahd_get_scbptr(ahd);
	prपूर्णांकk("Pending list:");
	i = 0;
	LIST_FOREACH(scb, &ahd->pending_scbs, pending_links) अणु
		अगर (i++ > AHD_SCB_MAX)
			अवरोध;
		cur_col = prपूर्णांकk("\n%3d FIFO_USE[0x%x] ", SCB_GET_TAG(scb),
				 ahd_inb_scbram(ahd, SCB_FIFO_USE_COUNT));
		ahd_set_scbptr(ahd, SCB_GET_TAG(scb));
		ahd_scb_control_prपूर्णांक(ahd_inb_scbram(ahd, SCB_CONTROL),
				      &cur_col, 60);
		ahd_scb_scsiid_prपूर्णांक(ahd_inb_scbram(ahd, SCB_SCSIID),
				     &cur_col, 60);
	पूर्ण
	prपूर्णांकk("\nTotal %d\n", i);

	prपूर्णांकk("Kernel Free SCB list: ");
	i = 0;
	TAILQ_FOREACH(scb, &ahd->scb_data.मुक्त_scbs, links.tqe) अणु
		काष्ठा scb *list_scb;

		list_scb = scb;
		करो अणु
			prपूर्णांकk("%d ", SCB_GET_TAG(list_scb));
			list_scb = LIST_NEXT(list_scb, collision_links);
		पूर्ण जबतक (list_scb && i++ < AHD_SCB_MAX);
	पूर्ण

	LIST_FOREACH(scb, &ahd->scb_data.any_dev_मुक्त_scb_list, links.le) अणु
		अगर (i++ > AHD_SCB_MAX)
			अवरोध;
		prपूर्णांकk("%d ", SCB_GET_TAG(scb));
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("Sequencer Complete DMA-inprog list: ");
	scb_index = ahd_inw(ahd, COMPLETE_SCB_DMAINPROG_HEAD);
	i = 0;
	जबतक (!SCBID_IS_शून्य(scb_index) && i++ < AHD_SCB_MAX) अणु
		ahd_set_scbptr(ahd, scb_index);
		prपूर्णांकk("%d ", scb_index);
		scb_index = ahd_inw_scbram(ahd, SCB_NEXT_COMPLETE);
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("Sequencer Complete list: ");
	scb_index = ahd_inw(ahd, COMPLETE_SCB_HEAD);
	i = 0;
	जबतक (!SCBID_IS_शून्य(scb_index) && i++ < AHD_SCB_MAX) अणु
		ahd_set_scbptr(ahd, scb_index);
		prपूर्णांकk("%d ", scb_index);
		scb_index = ahd_inw_scbram(ahd, SCB_NEXT_COMPLETE);
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("Sequencer DMA-Up and Complete list: ");
	scb_index = ahd_inw(ahd, COMPLETE_DMA_SCB_HEAD);
	i = 0;
	जबतक (!SCBID_IS_शून्य(scb_index) && i++ < AHD_SCB_MAX) अणु
		ahd_set_scbptr(ahd, scb_index);
		prपूर्णांकk("%d ", scb_index);
		scb_index = ahd_inw_scbram(ahd, SCB_NEXT_COMPLETE);
	पूर्ण
	prपूर्णांकk("\n");
	prपूर्णांकk("Sequencer On QFreeze and Complete list: ");
	scb_index = ahd_inw(ahd, COMPLETE_ON_QFREEZE_HEAD);
	i = 0;
	जबतक (!SCBID_IS_शून्य(scb_index) && i++ < AHD_SCB_MAX) अणु
		ahd_set_scbptr(ahd, scb_index);
		prपूर्णांकk("%d ", scb_index);
		scb_index = ahd_inw_scbram(ahd, SCB_NEXT_COMPLETE);
	पूर्ण
	prपूर्णांकk("\n");
	ahd_set_scbptr(ahd, saved_scb_index);
	dfख_स्थिति = ahd_inb(ahd, DFFSTAT);
	क्रम (i = 0; i < 2; i++) अणु
#अगर_घोषित AHD_DEBUG
		काष्ठा scb *fअगरo_scb;
#पूर्ण_अगर
		u_पूर्णांक	    fअगरo_scbptr;

		ahd_set_modes(ahd, AHD_MODE_DFF0 + i, AHD_MODE_DFF0 + i);
		fअगरo_scbptr = ahd_get_scbptr(ahd);
		prपूर्णांकk("\n\n%s: FIFO%d %s, LONGJMP == 0x%x, SCB 0x%x\n",
		       ahd_name(ahd), i,
		       (dfख_स्थिति & (FIFO0FREE << i)) ? "Free" : "Active",
		       ahd_inw(ahd, LONGJMP_ADDR), fअगरo_scbptr);
		cur_col = 0;
		ahd_seqimode_prपूर्णांक(ahd_inb(ahd, SEQIMODE), &cur_col, 50);
		ahd_seqपूर्णांकsrc_prपूर्णांक(ahd_inb(ahd, SEQINTSRC), &cur_col, 50);
		ahd_dfcntrl_prपूर्णांक(ahd_inb(ahd, DFCNTRL), &cur_col, 50);
		ahd_dख_स्थितिus_prपूर्णांक(ahd_inb(ahd, DFSTATUS), &cur_col, 50);
		ahd_sg_cache_shaकरोw_prपूर्णांक(ahd_inb(ahd, SG_CACHE_SHADOW),
					  &cur_col, 50);
		ahd_sg_state_prपूर्णांक(ahd_inb(ahd, SG_STATE), &cur_col, 50);
		ahd_dffsxfrctl_prपूर्णांक(ahd_inb(ahd, DFFSXFRCTL), &cur_col, 50);
		ahd_soffcnt_prपूर्णांक(ahd_inb(ahd, SOFFCNT), &cur_col, 50);
		ahd_mdfख_स्थिति_prपूर्णांक(ahd_inb(ahd, MDFFSTAT), &cur_col, 50);
		अगर (cur_col > 50) अणु
			prपूर्णांकk("\n");
			cur_col = 0;
		पूर्ण
		cur_col += prपूर्णांकk("SHADDR = 0x%x%x, SHCNT = 0x%x ",
				  ahd_inl(ahd, SHADDR+4),
				  ahd_inl(ahd, SHADDR),
				  (ahd_inb(ahd, SHCNT)
				| (ahd_inb(ahd, SHCNT + 1) << 8)
				| (ahd_inb(ahd, SHCNT + 2) << 16)));
		अगर (cur_col > 50) अणु
			prपूर्णांकk("\n");
			cur_col = 0;
		पूर्ण
		cur_col += prपूर्णांकk("HADDR = 0x%x%x, HCNT = 0x%x ",
				  ahd_inl(ahd, HADDR+4),
				  ahd_inl(ahd, HADDR),
				  (ahd_inb(ahd, HCNT)
				| (ahd_inb(ahd, HCNT + 1) << 8)
				| (ahd_inb(ahd, HCNT + 2) << 16)));
		ahd_ccsgctl_prपूर्णांक(ahd_inb(ahd, CCSGCTL), &cur_col, 50);
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_SG) != 0) अणु
			fअगरo_scb = ahd_lookup_scb(ahd, fअगरo_scbptr);
			अगर (fअगरo_scb != शून्य)
				ahd_dump_sglist(fअगरo_scb);
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	prपूर्णांकk("\nLQIN: ");
	क्रम (i = 0; i < 20; i++)
		prपूर्णांकk("0x%x ", ahd_inb(ahd, LQIN + i));
	prपूर्णांकk("\n");
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	prपूर्णांकk("%s: LQISTATE = 0x%x, LQOSTATE = 0x%x, OPTIONMODE = 0x%x\n",
	       ahd_name(ahd), ahd_inb(ahd, LQISTATE), ahd_inb(ahd, LQOSTATE),
	       ahd_inb(ahd, OPTIONMODE));
	prपूर्णांकk("%s: OS_SPACE_CNT = 0x%x MAXCMDCNT = 0x%x\n",
	       ahd_name(ahd), ahd_inb(ahd, OS_SPACE_CNT),
	       ahd_inb(ahd, MAXCMDCNT));
	prपूर्णांकk("%s: SAVED_SCSIID = 0x%x SAVED_LUN = 0x%x\n",
	       ahd_name(ahd), ahd_inb(ahd, SAVED_SCSIID),
	       ahd_inb(ahd, SAVED_LUN));
	ahd_simode0_prपूर्णांक(ahd_inb(ahd, SIMODE0), &cur_col, 50);
	prपूर्णांकk("\n");
	ahd_set_modes(ahd, AHD_MODE_CCHAN, AHD_MODE_CCHAN);
	cur_col = 0;
	ahd_ccscbctl_prपूर्णांक(ahd_inb(ahd, CCSCBCTL), &cur_col, 50);
	prपूर्णांकk("\n");
	ahd_set_modes(ahd, ahd->saved_src_mode, ahd->saved_dst_mode);
	prपूर्णांकk("%s: REG0 == 0x%x, SINDEX = 0x%x, DINDEX = 0x%x\n",
	       ahd_name(ahd), ahd_inw(ahd, REG0), ahd_inw(ahd, SINDEX),
	       ahd_inw(ahd, DINDEX));
	prपूर्णांकk("%s: SCBPTR == 0x%x, SCB_NEXT == 0x%x, SCB_NEXT2 == 0x%x\n",
	       ahd_name(ahd), ahd_get_scbptr(ahd),
	       ahd_inw_scbram(ahd, SCB_NEXT),
	       ahd_inw_scbram(ahd, SCB_NEXT2));
	prपूर्णांकk("CDB %x %x %x %x %x %x\n",
	       ahd_inb_scbram(ahd, SCB_CDB_STORE),
	       ahd_inb_scbram(ahd, SCB_CDB_STORE+1),
	       ahd_inb_scbram(ahd, SCB_CDB_STORE+2),
	       ahd_inb_scbram(ahd, SCB_CDB_STORE+3),
	       ahd_inb_scbram(ahd, SCB_CDB_STORE+4),
	       ahd_inb_scbram(ahd, SCB_CDB_STORE+5));
	prपूर्णांकk("STACK:");
	क्रम (i = 0; i < ahd->stack_size; i++) अणु
		ahd->saved_stack[i] =
		    ahd_inb(ahd, STACK)|(ahd_inb(ahd, STACK) << 8);
		prपूर्णांकk(" 0x%x", ahd->saved_stack[i]);
	पूर्ण
	क्रम (i = ahd->stack_size-1; i >= 0; i--) अणु
		ahd_outb(ahd, STACK, ahd->saved_stack[i] & 0xFF);
		ahd_outb(ahd, STACK, (ahd->saved_stack[i] >> 8) & 0xFF);
	पूर्ण
	prपूर्णांकk("\n<<<<<<<<<<<<<<<<< Dump Card State Ends >>>>>>>>>>>>>>>>>>\n");
	ahd_restore_modes(ahd, saved_modes);
	अगर (छोड़ोd == 0)
		ahd_unछोड़ो(ahd);
पूर्ण

#अगर 0
व्योम
ahd_dump_scbs(काष्ठा ahd_softc *ahd)
अणु
	ahd_mode_state saved_modes;
	u_पूर्णांक	       saved_scb_index;
	पूर्णांक	       i;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	saved_scb_index = ahd_get_scbptr(ahd);
	क्रम (i = 0; i < AHD_SCB_MAX; i++) अणु
		ahd_set_scbptr(ahd, i);
		prपूर्णांकk("%3d", i);
		prपूर्णांकk("(CTRL 0x%x ID 0x%x N 0x%x N2 0x%x SG 0x%x, RSG 0x%x)\n",
		       ahd_inb_scbram(ahd, SCB_CONTROL),
		       ahd_inb_scbram(ahd, SCB_SCSIID),
		       ahd_inw_scbram(ahd, SCB_NEXT),
		       ahd_inw_scbram(ahd, SCB_NEXT2),
		       ahd_inl_scbram(ahd, SCB_SGPTR),
		       ahd_inl_scbram(ahd, SCB_RESIDUAL_SGPTR));
	पूर्ण
	prपूर्णांकk("\n");
	ahd_set_scbptr(ahd, saved_scb_index);
	ahd_restore_modes(ahd, saved_modes);
पूर्ण
#पूर्ण_अगर  /*  0  */

/**************************** Flexport Logic **********************************/
/*
 * Read count 16bit words from 16bit word address start_addr from the
 * SEEPROM attached to the controller, पूर्णांकo buf, using the controller's
 * SEEPROM पढ़ोing state machine.  Optionally treat the data as a byte
 * stream in terms of byte order.
 */
पूर्णांक
ahd_पढ़ो_seeprom(काष्ठा ahd_softc *ahd, uपूर्णांक16_t *buf,
		 u_पूर्णांक start_addr, u_पूर्णांक count, पूर्णांक bytestream)
अणु
	u_पूर्णांक cur_addr;
	u_पूर्णांक end_addr;
	पूर्णांक   error;

	/*
	 * If we never make it through the loop even once,
	 * we were passed invalid arguments.
	 */
	error = EINVAL;
	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	end_addr = start_addr + count;
	क्रम (cur_addr = start_addr; cur_addr < end_addr; cur_addr++) अणु

		ahd_outb(ahd, SEEADR, cur_addr);
		ahd_outb(ahd, SEECTL, SEEOP_READ | SEESTART);

		error = ahd_रुको_seeprom(ahd);
		अगर (error)
			अवरोध;
		अगर (bytestream != 0) अणु
			uपूर्णांक8_t *bytestream_ptr;

			bytestream_ptr = (uपूर्णांक8_t *)buf;
			*bytestream_ptr++ = ahd_inb(ahd, SEEDAT);
			*bytestream_ptr = ahd_inb(ahd, SEEDAT+1);
		पूर्ण अन्यथा अणु
			/*
			 * ahd_inw() alपढ़ोy handles machine byte order.
			 */
			*buf = ahd_inw(ahd, SEEDAT);
		पूर्ण
		buf++;
	पूर्ण
	वापस (error);
पूर्ण

/*
 * Write count 16bit words from buf, पूर्णांकo SEEPROM attache to the
 * controller starting at 16bit word address start_addr, using the
 * controller's SEEPROM writing state machine.
 */
पूर्णांक
ahd_ग_लिखो_seeprom(काष्ठा ahd_softc *ahd, uपूर्णांक16_t *buf,
		  u_पूर्णांक start_addr, u_पूर्णांक count)
अणु
	u_पूर्णांक cur_addr;
	u_पूर्णांक end_addr;
	पूर्णांक   error;
	पूर्णांक   retval;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	error = ENOENT;

	/* Place the chip पूर्णांकo ग_लिखो-enable mode */
	ahd_outb(ahd, SEEADR, SEEOP_EWEN_ADDR);
	ahd_outb(ahd, SEECTL, SEEOP_EWEN | SEESTART);
	error = ahd_रुको_seeprom(ahd);
	अगर (error)
		वापस (error);

	/*
	 * Write the data.  If we करोn't get through the loop at
	 * least once, the arguments were invalid.
	 */
	retval = EINVAL;
	end_addr = start_addr + count;
	क्रम (cur_addr = start_addr; cur_addr < end_addr; cur_addr++) अणु
		ahd_outw(ahd, SEEDAT, *buf++);
		ahd_outb(ahd, SEEADR, cur_addr);
		ahd_outb(ahd, SEECTL, SEEOP_WRITE | SEESTART);

		retval = ahd_रुको_seeprom(ahd);
		अगर (retval)
			अवरोध;
	पूर्ण

	/*
	 * Disable ग_लिखोs.
	 */
	ahd_outb(ahd, SEEADR, SEEOP_EWDS_ADDR);
	ahd_outb(ahd, SEECTL, SEEOP_EWDS | SEESTART);
	error = ahd_रुको_seeprom(ahd);
	अगर (error)
		वापस (error);
	वापस (retval);
पूर्ण

/*
 * Wait ~100us क्रम the serial eeprom to satisfy our request.
 */
अटल पूर्णांक
ahd_रुको_seeprom(काष्ठा ahd_softc *ahd)
अणु
	पूर्णांक cnt;

	cnt = 5000;
	जबतक ((ahd_inb(ahd, SEESTAT) & (SEEARBACK|SEEBUSY)) != 0 && --cnt)
		ahd_delay(5);

	अगर (cnt == 0)
		वापस (ETIMEDOUT);
	वापस (0);
पूर्ण

/*
 * Validate the two checksums in the per_channel
 * vital product data काष्ठा.
 */
अटल पूर्णांक
ahd_verअगरy_vpd_cksum(काष्ठा vpd_config *vpd)
अणु
	पूर्णांक i;
	पूर्णांक maxaddr;
	uपूर्णांक32_t checksum;
	uपूर्णांक8_t *vpdarray;

	vpdarray = (uपूर्णांक8_t *)vpd;
	maxaddr = दुरत्व(काष्ठा vpd_config, vpd_checksum);
	checksum = 0;
	क्रम (i = दुरत्व(काष्ठा vpd_config, resource_type); i < maxaddr; i++)
		checksum = checksum + vpdarray[i];
	अगर (checksum == 0
	 || (-checksum & 0xFF) != vpd->vpd_checksum)
		वापस (0);

	checksum = 0;
	maxaddr = दुरत्व(काष्ठा vpd_config, checksum);
	क्रम (i = दुरत्व(काष्ठा vpd_config, शेष_target_flags);
	     i < maxaddr; i++)
		checksum = checksum + vpdarray[i];
	अगर (checksum == 0
	 || (-checksum & 0xFF) != vpd->checksum)
		वापस (0);
	वापस (1);
पूर्ण

पूर्णांक
ahd_verअगरy_cksum(काष्ठा seeprom_config *sc)
अणु
	पूर्णांक i;
	पूर्णांक maxaddr;
	uपूर्णांक32_t checksum;
	uपूर्णांक16_t *scarray;

	maxaddr = (माप(*sc)/2) - 1;
	checksum = 0;
	scarray = (uपूर्णांक16_t *)sc;

	क्रम (i = 0; i < maxaddr; i++)
		checksum = checksum + scarray[i];
	अगर (checksum == 0
	 || (checksum & 0xFFFF) != sc->checksum) अणु
		वापस (0);
	पूर्ण अन्यथा अणु
		वापस (1);
	पूर्ण
पूर्ण

पूर्णांक
ahd_acquire_seeprom(काष्ठा ahd_softc *ahd)
अणु
	/*
	 * We should be able to determine the SEEPROM type
	 * from the flexport logic, but unक्रमtunately not
	 * all implementations have this logic and there is
	 * no programatic method क्रम determining अगर the logic
	 * is present.
	 */
	वापस (1);
#अगर 0
	uपूर्णांक8_t	seetype;
	पूर्णांक	error;

	error = ahd_पढ़ो_flexport(ahd, FLXADDR_ROMSTAT_CURSENSECTL, &seetype);
	अगर (error != 0
	    || ((seetype & FLX_ROMSTAT_SEECFG) == FLX_ROMSTAT_SEE_NONE))
		वापस (0);
	वापस (1);
#पूर्ण_अगर
पूर्ण

व्योम
ahd_release_seeprom(काष्ठा ahd_softc *ahd)
अणु
	/* Currently a no-op */
पूर्ण

/*
 * Wait at most 2 seconds क्रम flexport arbitration to succeed.
 */
अटल पूर्णांक
ahd_रुको_flexport(काष्ठा ahd_softc *ahd)
अणु
	पूर्णांक cnt;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	cnt = 1000000 * 2 / 5;
	जबतक ((ahd_inb(ahd, BRDCTL) & FLXARBACK) == 0 && --cnt)
		ahd_delay(5);

	अगर (cnt == 0)
		वापस (ETIMEDOUT);
	वापस (0);
पूर्ण

पूर्णांक
ahd_ग_लिखो_flexport(काष्ठा ahd_softc *ahd, u_पूर्णांक addr, u_पूर्णांक value)
अणु
	पूर्णांक error;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	अगर (addr > 7)
		panic("ahd_write_flexport: address out of range");
	ahd_outb(ahd, BRDCTL, BRDEN|(addr << 3));
	error = ahd_रुको_flexport(ahd);
	अगर (error != 0)
		वापस (error);
	ahd_outb(ahd, BRDDAT, value);
	ahd_flush_device_ग_लिखोs(ahd);
	ahd_outb(ahd, BRDCTL, BRDSTB|BRDEN|(addr << 3));
	ahd_flush_device_ग_लिखोs(ahd);
	ahd_outb(ahd, BRDCTL, BRDEN|(addr << 3));
	ahd_flush_device_ग_लिखोs(ahd);
	ahd_outb(ahd, BRDCTL, 0);
	ahd_flush_device_ग_लिखोs(ahd);
	वापस (0);
पूर्ण

पूर्णांक
ahd_पढ़ो_flexport(काष्ठा ahd_softc *ahd, u_पूर्णांक addr, uपूर्णांक8_t *value)
अणु
	पूर्णांक	error;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	अगर (addr > 7)
		panic("ahd_read_flexport: address out of range");
	ahd_outb(ahd, BRDCTL, BRDRW|BRDEN|(addr << 3));
	error = ahd_रुको_flexport(ahd);
	अगर (error != 0)
		वापस (error);
	*value = ahd_inb(ahd, BRDDAT);
	ahd_outb(ahd, BRDCTL, 0);
	ahd_flush_device_ग_लिखोs(ahd);
	वापस (0);
पूर्ण

/************************* Target Mode ****************************************/
#अगर_घोषित AHD_TARGET_MODE
cam_status
ahd_find_पंचांगode_devs(काष्ठा ahd_softc *ahd, काष्ठा cam_sim *sim, जोड़ ccb *ccb,
		    काष्ठा ahd_पंचांगode_tstate **tstate,
		    काष्ठा ahd_पंचांगode_lstate **lstate,
		    पूर्णांक notfound_failure)
अणु

	अगर ((ahd->features & AHD_TARGETMODE) == 0)
		वापस (CAM_REQ_INVALID);

	/*
	 * Handle the 'black hole' device that sucks up
	 * requests to unattached luns on enabled tarमाला_लो.
	 */
	अगर (ccb->ccb_h.target_id == CAM_TARGET_WILDCARD
	 && ccb->ccb_h.target_lun == CAM_LUN_WILDCARD) अणु
		*tstate = शून्य;
		*lstate = ahd->black_hole;
	पूर्ण अन्यथा अणु
		u_पूर्णांक max_id;

		max_id = (ahd->features & AHD_WIDE) ? 16 : 8;
		अगर (ccb->ccb_h.target_id >= max_id)
			वापस (CAM_TID_INVALID);

		अगर (ccb->ccb_h.target_lun >= AHD_NUM_LUNS)
			वापस (CAM_LUN_INVALID);

		*tstate = ahd->enabled_tarमाला_लो[ccb->ccb_h.target_id];
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
ahd_handle_en_lun(काष्ठा ahd_softc *ahd, काष्ठा cam_sim *sim, जोड़ ccb *ccb)
अणु
#अगर NOT_YET
	काष्ठा	   ahd_पंचांगode_tstate *tstate;
	काष्ठा	   ahd_पंचांगode_lstate *lstate;
	काष्ठा	   ccb_en_lun *cel;
	cam_status status;
	u_पूर्णांक	   target;
	u_पूर्णांक	   lun;
	u_पूर्णांक	   target_mask;
	u_दीर्घ	   s;
	अक्षर	   channel;

	status = ahd_find_पंचांगode_devs(ahd, sim, ccb, &tstate, &lstate,
				     /*notfound_failure*/FALSE);

	अगर (status != CAM_REQ_CMP) अणु
		ccb->ccb_h.status = status;
		वापस;
	पूर्ण

	अगर ((ahd->features & AHD_MULTIROLE) != 0) अणु
		u_पूर्णांक	   our_id;

		our_id = ahd->our_id;
		अगर (ccb->ccb_h.target_id != our_id) अणु
			अगर ((ahd->features & AHD_MULTI_TID) != 0
			 && (ahd->flags & AHD_INITIATORROLE) != 0) अणु
				/*
				 * Only allow additional tarमाला_लो अगर
				 * the initiator role is disabled.
				 * The hardware cannot handle a re-select-in
				 * on the initiator id during a re-select-out
				 * on a dअगरferent target id.
				 */
				status = CAM_TID_INVALID;
			पूर्ण अन्यथा अगर ((ahd->flags & AHD_INITIATORROLE) != 0
				|| ahd->enabled_luns > 0) अणु
				/*
				 * Only allow our target id to change
				 * अगर the initiator role is not configured
				 * and there are no enabled luns which
				 * are attached to the currently रेजिस्टरed
				 * scsi id.
				 */
				status = CAM_TID_INVALID;
			पूर्ण
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
	अगर ((ahd->flags & AHD_TARGETROLE) == 0
	 && ccb->ccb_h.target_id != CAM_TARGET_WILDCARD) अणु
		u_दीर्घ	s;

		prपूर्णांकk("Configuring Target Mode\n");
		ahd_lock(ahd, &s);
		अगर (LIST_FIRST(&ahd->pending_scbs) != शून्य) अणु
			ccb->ccb_h.status = CAM_BUSY;
			ahd_unlock(ahd, &s);
			वापस;
		पूर्ण
		ahd->flags |= AHD_TARGETROLE;
		अगर ((ahd->features & AHD_MULTIROLE) == 0)
			ahd->flags &= ~AHD_INITIATORROLE;
		ahd_छोड़ो(ahd);
		ahd_loadseq(ahd);
		ahd_restart(ahd);
		ahd_unlock(ahd, &s);
	पूर्ण
	cel = &ccb->cel;
	target = ccb->ccb_h.target_id;
	lun = ccb->ccb_h.target_lun;
	channel = SIM_CHANNEL(ahd, sim);
	target_mask = 0x01 << target;
	अगर (channel == 'B')
		target_mask <<= 8;

	अगर (cel->enable != 0) अणु
		u_पूर्णांक scsiseq1;

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
			tstate = ahd_alloc_tstate(ahd, target, channel);
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
		ahd_lock(ahd, &s);
		ahd_छोड़ो(ahd);
		अगर (target != CAM_TARGET_WILDCARD) अणु
			tstate->enabled_luns[lun] = lstate;
			ahd->enabled_luns++;

			अगर ((ahd->features & AHD_MULTI_TID) != 0) अणु
				u_पूर्णांक targid_mask;

				targid_mask = ahd_inw(ahd, TARGID);
				targid_mask |= target_mask;
				ahd_outw(ahd, TARGID, targid_mask);
				ahd_update_scsiid(ahd, targid_mask);
			पूर्ण अन्यथा अणु
				u_पूर्णांक our_id;
				अक्षर  channel;

				channel = SIM_CHANNEL(ahd, sim);
				our_id = SIM_SCSI_ID(ahd, sim);

				/*
				 * This can only happen अगर selections
				 * are not enabled
				 */
				अगर (target != our_id) अणु
					u_पूर्णांक sblkctl;
					अक्षर  cur_channel;
					पूर्णांक   swap;

					sblkctl = ahd_inb(ahd, SBLKCTL);
					cur_channel = (sblkctl & SELBUSB)
						    ? 'B' : 'A';
					अगर ((ahd->features & AHD_TWIN) == 0)
						cur_channel = 'A';
					swap = cur_channel != channel;
					ahd->our_id = target;

					अगर (swap)
						ahd_outb(ahd, SBLKCTL,
							 sblkctl ^ SELBUSB);

					ahd_outb(ahd, SCSIID, target);

					अगर (swap)
						ahd_outb(ahd, SBLKCTL, sblkctl);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			ahd->black_hole = lstate;
		/* Allow select-in operations */
		अगर (ahd->black_hole != शून्य && ahd->enabled_luns > 0) अणु
			scsiseq1 = ahd_inb(ahd, SCSISEQ_TEMPLATE);
			scsiseq1 |= ENSELI;
			ahd_outb(ahd, SCSISEQ_TEMPLATE, scsiseq1);
			scsiseq1 = ahd_inb(ahd, SCSISEQ1);
			scsiseq1 |= ENSELI;
			ahd_outb(ahd, SCSISEQ1, scsiseq1);
		पूर्ण
		ahd_unछोड़ो(ahd);
		ahd_unlock(ahd, &s);
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

		ahd_lock(ahd, &s);

		ccb->ccb_h.status = CAM_REQ_CMP;
		LIST_FOREACH(scb, &ahd->pending_scbs, pending_links) अणु
			काष्ठा ccb_hdr *ccbh;

			ccbh = &scb->io_ctx->ccb_h;
			अगर (ccbh->func_code == XPT_CONT_TARGET_IO
			 && !xpt_path_comp(ccbh->path, ccb->ccb_h.path))अणु
				prपूर्णांकk("CTIO pending\n");
				ccb->ccb_h.status = CAM_REQ_INVALID;
				ahd_unlock(ahd, &s);
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
			ahd_unlock(ahd, &s);
			वापस;
		पूर्ण

		xpt_prपूर्णांक_path(ccb->ccb_h.path);
		prपूर्णांकk("Target mode disabled\n");
		xpt_मुक्त_path(lstate->path);
		kमुक्त(lstate);

		ahd_छोड़ो(ahd);
		/* Can we clean up the target too? */
		अगर (target != CAM_TARGET_WILDCARD) अणु
			tstate->enabled_luns[lun] = शून्य;
			ahd->enabled_luns--;
			क्रम (empty = 1, i = 0; i < 8; i++)
				अगर (tstate->enabled_luns[i] != शून्य) अणु
					empty = 0;
					अवरोध;
				पूर्ण

			अगर (empty) अणु
				ahd_मुक्त_tstate(ahd, target, channel,
						/*क्रमce*/FALSE);
				अगर (ahd->features & AHD_MULTI_TID) अणु
					u_पूर्णांक targid_mask;

					targid_mask = ahd_inw(ahd, TARGID);
					targid_mask &= ~target_mask;
					ahd_outw(ahd, TARGID, targid_mask);
					ahd_update_scsiid(ahd, targid_mask);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु

			ahd->black_hole = शून्य;

			/*
			 * We can't allow selections without
			 * our black hole device.
			 */
			empty = TRUE;
		पूर्ण
		अगर (ahd->enabled_luns == 0) अणु
			/* Disallow select-in */
			u_पूर्णांक scsiseq1;

			scsiseq1 = ahd_inb(ahd, SCSISEQ_TEMPLATE);
			scsiseq1 &= ~ENSELI;
			ahd_outb(ahd, SCSISEQ_TEMPLATE, scsiseq1);
			scsiseq1 = ahd_inb(ahd, SCSISEQ1);
			scsiseq1 &= ~ENSELI;
			ahd_outb(ahd, SCSISEQ1, scsiseq1);

			अगर ((ahd->features & AHD_MULTIROLE) == 0) अणु
				prपूर्णांकk("Configuring Initiator Mode\n");
				ahd->flags &= ~AHD_TARGETROLE;
				ahd->flags |= AHD_INITIATORROLE;
				ahd_छोड़ो(ahd);
				ahd_loadseq(ahd);
				ahd_restart(ahd);
				/*
				 * Unछोड़ोd.  The extra unछोड़ो
				 * that follows is harmless.
				 */
			पूर्ण
		पूर्ण
		ahd_unछोड़ो(ahd);
		ahd_unlock(ahd, &s);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम
ahd_update_scsiid(काष्ठा ahd_softc *ahd, u_पूर्णांक targid_mask)
अणु
#अगर NOT_YET
	u_पूर्णांक scsiid_mask;
	u_पूर्णांक scsiid;

	अगर ((ahd->features & AHD_MULTI_TID) == 0)
		panic("ahd_update_scsiid called on non-multitid unit\n");

	/*
	 * Since we will rely on the TARGID mask
	 * क्रम selection enables, ensure that OID
	 * in SCSIID is not set to some other ID
	 * that we करोn't want to allow selections on.
	 */
	अगर ((ahd->features & AHD_ULTRA2) != 0)
		scsiid = ahd_inb(ahd, SCSIID_ULTRA2);
	अन्यथा
		scsiid = ahd_inb(ahd, SCSIID);
	scsiid_mask = 0x1 << (scsiid & OID);
	अगर ((targid_mask & scsiid_mask) == 0) अणु
		u_पूर्णांक our_id;

		/* ffs counts from 1 */
		our_id = ffs(targid_mask);
		अगर (our_id == 0)
			our_id = ahd->our_id;
		अन्यथा
			our_id--;
		scsiid &= TID;
		scsiid |= our_id;
	पूर्ण
	अगर ((ahd->features & AHD_ULTRA2) != 0)
		ahd_outb(ahd, SCSIID_ULTRA2, scsiid);
	अन्यथा
		ahd_outb(ahd, SCSIID, scsiid);
#पूर्ण_अगर
पूर्ण

अटल व्योम
ahd_run_tqinfअगरo(काष्ठा ahd_softc *ahd, पूर्णांक छोड़ोd)
अणु
	काष्ठा target_cmd *cmd;

	ahd_sync_tqinfअगरo(ahd, BUS_DMASYNC_POSTREAD);
	जबतक ((cmd = &ahd->tarअ_लोmds[ahd->tqinfअगरonext])->cmd_valid != 0) अणु

		/*
		 * Only advance through the queue अगर we
		 * have the resources to process the command.
		 */
		अगर (ahd_handle_target_cmd(ahd, cmd) != 0)
			अवरोध;

		cmd->cmd_valid = 0;
		ahd_dmamap_sync(ahd, ahd->shared_data_dmat,
				ahd->shared_data_map.dmamap,
				ahd_tarअ_लोmd_offset(ahd, ahd->tqinfअगरonext),
				माप(काष्ठा target_cmd),
				BUS_DMASYNC_PREREAD);
		ahd->tqinfअगरonext++;

		/*
		 * Lazily update our position in the target mode incoming
		 * command queue as seen by the sequencer.
		 */
		अगर ((ahd->tqinfअगरonext & (HOST_TQINPOS - 1)) == 1) अणु
			u_पूर्णांक hs_mailbox;

			hs_mailbox = ahd_inb(ahd, HS_MAILBOX);
			hs_mailbox &= ~HOST_TQINPOS;
			hs_mailbox |= ahd->tqinfअगरonext & HOST_TQINPOS;
			ahd_outb(ahd, HS_MAILBOX, hs_mailbox);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
ahd_handle_target_cmd(काष्ठा ahd_softc *ahd, काष्ठा target_cmd *cmd)
अणु
	काष्ठा	  ahd_पंचांगode_tstate *tstate;
	काष्ठा	  ahd_पंचांगode_lstate *lstate;
	काष्ठा	  ccb_accept_tio *atio;
	uपूर्णांक8_t *byte;
	पूर्णांक	  initiator;
	पूर्णांक	  target;
	पूर्णांक	  lun;

	initiator = SCSIID_TARGET(ahd, cmd->scsiid);
	target = SCSIID_OUR_ID(cmd->scsiid);
	lun    = (cmd->identअगरy & MSG_IDENTIFY_LUNMASK);

	byte = cmd->bytes;
	tstate = ahd->enabled_tarमाला_लो[target];
	lstate = शून्य;
	अगर (tstate != शून्य)
		lstate = tstate->enabled_luns[lun];

	/*
	 * Commands क्रम disabled luns go to the black hole driver.
	 */
	अगर (lstate == शून्य)
		lstate = ahd->black_hole;

	atio = (काष्ठा ccb_accept_tio*)SLIST_FIRST(&lstate->accept_tios);
	अगर (atio == शून्य) अणु
		ahd->flags |= AHD_TQINFIFO_BLOCKED;
		/*
		 * Wait क्रम more ATIOs from the peripheral driver क्रम this lun.
		 */
		वापस (1);
	पूर्ण अन्यथा
		ahd->flags &= ~AHD_TQINFIFO_BLOCKED;
#अगर_घोषित AHD_DEBUG
	अगर ((ahd_debug & AHD_SHOW_TQIN) != 0)
		prपूर्णांकk("Incoming command from %d for %d:%d%s\n",
		       initiator, target, lun,
		       lstate == ahd->black_hole ? "(Black Holed)" : "");
#पूर्ण_अगर
	SLIST_REMOVE_HEAD(&lstate->accept_tios, sim_links.sle);

	अगर (lstate == ahd->black_hole) अणु
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
#अगर_घोषित AHD_DEBUG
		अगर ((ahd_debug & AHD_SHOW_TQIN) != 0)
			prपूर्णांकk("Received Immediate Command %d:%d:%d - %p\n",
			       initiator, target, lun, ahd->pending_device);
#पूर्ण_अगर
		ahd->pending_device = lstate;
		ahd_मुक्तze_ccb((जोड़ ccb *)atio);
		atio->ccb_h.flags |= CAM_DIS_DISCONNECT;
	पूर्ण
	xpt_करोne((जोड़ ccb*)atio);
	वापस (0);
पूर्ण

#पूर्ण_अगर
