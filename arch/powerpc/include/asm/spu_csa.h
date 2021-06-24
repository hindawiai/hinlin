<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * spu_csa.h: Definitions क्रम SPU context save area (CSA).
 *
 * (C) Copyright IBM 2005
 *
 * Author: Mark Nutter <mnutter@us.ibm.com>
 */

#अगर_अघोषित _SPU_CSA_H_
#घोषणा _SPU_CSA_H_
#अगर_घोषित __KERNEL__

/*
 * Total number of 128-bit रेजिस्टरs.
 */
#घोषणा NR_SPU_GPRS         	128
#घोषणा NR_SPU_SPRS         	9
#घोषणा NR_SPU_REGS_PAD	    	7
#घोषणा NR_SPU_SPILL_REGS   	144	/* GPRS + SPRS + PAD */
#घोषणा SIZखातापूर्ण_SPU_SPILL_REGS	NR_SPU_SPILL_REGS * 16

#घोषणा SPU_SAVE_COMPLETE      	0x3FFB
#घोषणा SPU_RESTORE_COMPLETE   	0x3FFC

/*
 * Definitions क्रम various 'stopped' status conditions,
 * to be recreated during context restore.
 */
#घोषणा SPU_STOPPED_STATUS_P    1
#घोषणा SPU_STOPPED_STATUS_I    2
#घोषणा SPU_STOPPED_STATUS_H    3
#घोषणा SPU_STOPPED_STATUS_S    4
#घोषणा SPU_STOPPED_STATUS_S_I  5
#घोषणा SPU_STOPPED_STATUS_S_P  6
#घोषणा SPU_STOPPED_STATUS_P_H  7
#घोषणा SPU_STOPPED_STATUS_P_I  8
#घोषणा SPU_STOPPED_STATUS_R    9

/*
 * Definitions क्रम software decrementer status flag.
 */
#घोषणा SPU_DECR_STATUS_RUNNING 0x1
#घोषणा SPU_DECR_STATUS_WRAPPED 0x2

#अगर_अघोषित  __ASSEMBLY__
/**
 * spu_reg128 - generic 128-bit रेजिस्टर definition.
 */
काष्ठा spu_reg128 अणु
	u32 slot[4];
पूर्ण;

/**
 * काष्ठा spu_lscsa - Local Store Context Save Area.
 * @gprs: Array of saved रेजिस्टरs.
 * @fpcr: Saved भग्नing poपूर्णांक status control रेजिस्टर.
 * @decr: Saved decrementer value.
 * @decr_status: Indicates software decrementer status flags.
 * @ppu_mb: Saved PPU mailbox data.
 * @ppuपूर्णांक_mb: Saved PPU पूर्णांकerrupting mailbox data.
 * @tag_mask: Saved tag group mask.
 * @event_mask: Saved event mask.
 * @srr0: Saved SRR0.
 * @stopped_status: Conditions to be recreated by restore.
 * @ls: Saved contents of Local Storage Area.
 *
 * The LSCSA represents state that is primarily saved and
 * restored by SPU-side code.
 */
काष्ठा spu_lscsa अणु
	काष्ठा spu_reg128 gprs[128];
	काष्ठा spu_reg128 fpcr;
	काष्ठा spu_reg128 decr;
	काष्ठा spu_reg128 decr_status;
	काष्ठा spu_reg128 ppu_mb;
	काष्ठा spu_reg128 ppuपूर्णांक_mb;
	काष्ठा spu_reg128 tag_mask;
	काष्ठा spu_reg128 event_mask;
	काष्ठा spu_reg128 srr0;
	काष्ठा spu_reg128 stopped_status;

	/*
	 * 'ls' must be page-aligned on all configurations.
	 * Since we करोn't want to rely on having the spu-gcc
	 * installed to build the kernel and this काष्ठाure
	 * is used in the SPU-side code, make it 64k-page
	 * aligned क्रम now.
	 */
	अचिन्हित अक्षर ls[LS_SIZE] __attribute__((aligned(65536)));
पूर्ण;

#अगर_अघोषित __SPU__
/*
 * काष्ठा spu_problem_collapsed - condensed problem state area, w/o pads.
 */
काष्ठा spu_problem_collapsed अणु
	u64 spc_mssync_RW;
	u32 mfc_lsa_W;
	u32 unused_pad0;
	u64 mfc_ea_W;
	जोड़ mfc_tag_size_class_cmd mfc_जोड़_W;
	u32 dma_qstatus_R;
	u32 dma_querytype_RW;
	u32 dma_querymask_RW;
	u32 dma_tagstatus_R;
	u32 pu_mb_R;
	u32 spu_mb_W;
	u32 mb_stat_R;
	u32 spu_runcntl_RW;
	u32 spu_status_R;
	u32 spu_spc_R;
	u32 spu_npc_RW;
	u32 संकेत_notअगरy1;
	u32 संकेत_notअगरy2;
	u32 unused_pad1;
पूर्ण;

/*
 * काष्ठा spu_priv1_collapsed - condensed privileged 1 area, w/o pads.
 */
काष्ठा spu_priv1_collapsed अणु
	u64 mfc_sr1_RW;
	u64 mfc_lpid_RW;
	u64 spu_idr_RW;
	u64 mfc_vr_RO;
	u64 spu_vr_RO;
	u64 पूर्णांक_mask_class0_RW;
	u64 पूर्णांक_mask_class1_RW;
	u64 पूर्णांक_mask_class2_RW;
	u64 पूर्णांक_stat_class0_RW;
	u64 पूर्णांक_stat_class1_RW;
	u64 पूर्णांक_stat_class2_RW;
	u64 पूर्णांक_route_RW;
	u64 mfc_atomic_flush_RW;
	u64 resource_allocation_groupID_RW;
	u64 resource_allocation_enable_RW;
	u64 mfc_fir_R;
	u64 mfc_fir_status_or_W;
	u64 mfc_fir_status_and_W;
	u64 mfc_fir_mask_R;
	u64 mfc_fir_mask_or_W;
	u64 mfc_fir_mask_and_W;
	u64 mfc_fir_chkstp_enable_RW;
	u64 smf_sbi_संकेत_sel;
	u64 smf_ato_संकेत_sel;
	u64 tlb_index_hपूर्णांक_RO;
	u64 tlb_index_W;
	u64 tlb_vpn_RW;
	u64 tlb_rpn_RW;
	u64 tlb_invalidate_entry_W;
	u64 tlb_invalidate_all_W;
	u64 smm_hid;
	u64 mfc_accr_RW;
	u64 mfc_dsisr_RW;
	u64 mfc_dar_RW;
	u64 rmt_index_RW;
	u64 rmt_data1_RW;
	u64 mfc_dsir_R;
	u64 mfc_lsacr_RW;
	u64 mfc_lscrr_R;
	u64 mfc_tclass_id_RW;
	u64 mfc_rm_boundary;
	u64 smf_dma_संकेत_sel;
	u64 smm_संकेत_sel;
	u64 mfc_cer_R;
	u64 pu_ecc_cntl_RW;
	u64 pu_ecc_stat_RW;
	u64 spu_ecc_addr_RW;
	u64 spu_err_mask_RW;
	u64 spu_trig0_sel;
	u64 spu_trig1_sel;
	u64 spu_trig2_sel;
	u64 spu_trig3_sel;
	u64 spu_trace_sel;
	u64 spu_event0_sel;
	u64 spu_event1_sel;
	u64 spu_event2_sel;
	u64 spu_event3_sel;
	u64 spu_trace_cntl;
पूर्ण;

/*
 * काष्ठा spu_priv2_collapsed - condensed privileged 2 area, w/o pads.
 */
काष्ठा spu_priv2_collapsed अणु
	u64 slb_index_W;
	u64 slb_esid_RW;
	u64 slb_vsid_RW;
	u64 slb_invalidate_entry_W;
	u64 slb_invalidate_all_W;
	काष्ठा mfc_cq_sr spuq[16];
	काष्ठा mfc_cq_sr puq[8];
	u64 mfc_control_RW;
	u64 puपूर्णांक_mb_R;
	u64 spu_privcntl_RW;
	u64 spu_lslr_RW;
	u64 spu_chnlcntptr_RW;
	u64 spu_chnlcnt_RW;
	u64 spu_chnldata_RW;
	u64 spu_cfg_RW;
	u64 spu_tag_status_query_RW;
	u64 spu_cmd_buf1_RW;
	u64 spu_cmd_buf2_RW;
	u64 spu_atomic_status_RW;
पूर्ण;

/**
 * काष्ठा spu_state
 * @lscsa: Local Store Context Save Area.
 * @prob: Collapsed Problem State Area, w/o pads.
 * @priv1: Collapsed Privileged 1 Area, w/o pads.
 * @priv2: Collapsed Privileged 2 Area, w/o pads.
 * @spu_chnlcnt_RW: Array of saved channel counts.
 * @spu_chnldata_RW: Array of saved channel data.
 * @suspend_समय: Time stamp when decrementer disabled.
 *
 * Structure representing the whole of the SPU
 * context save area (CSA).  This काष्ठा contains
 * all of the state necessary to suspend and then
 * later optionally resume execution of an SPU
 * context.
 *
 * The @lscsa region is by far the largest, and is
 * allocated separately so that it may either be
 * pinned or mapped to/from application memory, as
 * appropriate क्रम the OS environment.
 */
काष्ठा spu_state अणु
	काष्ठा spu_lscsa *lscsa;
	काष्ठा spu_problem_collapsed prob;
	काष्ठा spu_priv1_collapsed priv1;
	काष्ठा spu_priv2_collapsed priv2;
	u64 spu_chnlcnt_RW[32];
	u64 spu_chnldata_RW[32];
	u32 spu_mailbox_data[4];
	u32 pu_mailbox_data[1];
	u64 class_0_dar, class_0_pending;
	u64 class_1_dar, class_1_dsisr;
	अचिन्हित दीर्घ suspend_समय;
	spinlock_t रेजिस्टर_lock;
पूर्ण;

#पूर्ण_अगर /* !__SPU__ */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _SPU_CSA_H_ */
