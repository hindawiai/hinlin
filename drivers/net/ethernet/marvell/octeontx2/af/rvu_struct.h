<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  Marvell OcteonTx2 RVU Admin Function driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित RVU_STRUCT_H
#घोषणा RVU_STRUCT_H

/* RVU Block revision IDs */
#घोषणा RVU_BLK_RVUM_REVID		0x01

#घोषणा RVU_MULTI_BLK_VER		0x7ULL

/* RVU Block Address Enumeration */
क्रमागत rvu_block_addr_e अणु
	BLKADDR_RVUM		= 0x0ULL,
	BLKADDR_LMT		= 0x1ULL,
	BLKADDR_MSIX		= 0x2ULL,
	BLKADDR_NPA		= 0x3ULL,
	BLKADDR_NIX0		= 0x4ULL,
	BLKADDR_NIX1		= 0x5ULL,
	BLKADDR_NPC		= 0x6ULL,
	BLKADDR_SSO		= 0x7ULL,
	BLKADDR_SSOW		= 0x8ULL,
	BLKADDR_TIM		= 0x9ULL,
	BLKADDR_CPT0		= 0xaULL,
	BLKADDR_CPT1		= 0xbULL,
	BLKADDR_NDC_NIX0_RX	= 0xcULL,
	BLKADDR_NDC_NIX0_TX	= 0xdULL,
	BLKADDR_NDC_NPA0	= 0xeULL,
	BLKADDR_NDC_NIX1_RX	= 0x10ULL,
	BLKADDR_NDC_NIX1_TX	= 0x11ULL,
	BLK_COUNT		= 0x12ULL,
पूर्ण;

/* RVU Block Type Enumeration */
क्रमागत rvu_block_type_e अणु
	BLKTYPE_RVUM = 0x0,
	BLKTYPE_MSIX = 0x1,
	BLKTYPE_LMT  = 0x2,
	BLKTYPE_NIX  = 0x3,
	BLKTYPE_NPA  = 0x4,
	BLKTYPE_NPC  = 0x5,
	BLKTYPE_SSO  = 0x6,
	BLKTYPE_SSOW = 0x7,
	BLKTYPE_TIM  = 0x8,
	BLKTYPE_CPT  = 0x9,
	BLKTYPE_NDC  = 0xa,
	BLKTYPE_MAX  = 0xa,
पूर्ण;

/* RVU Admin function Interrupt Vector Enumeration */
क्रमागत rvu_af_पूर्णांक_vec_e अणु
	RVU_AF_INT_VEC_POISON = 0x0,
	RVU_AF_INT_VEC_PFFLR  = 0x1,
	RVU_AF_INT_VEC_PFME   = 0x2,
	RVU_AF_INT_VEC_GEN    = 0x3,
	RVU_AF_INT_VEC_MBOX   = 0x4,
	RVU_AF_INT_VEC_CNT    = 0x5,
पूर्ण;

/* NPA Admin function Interrupt Vector Enumeration */
क्रमागत npa_af_पूर्णांक_vec_e अणु
	NPA_AF_INT_VEC_RVU	= 0x0,
	NPA_AF_INT_VEC_GEN	= 0x1,
	NPA_AF_INT_VEC_AQ_DONE	= 0x2,
	NPA_AF_INT_VEC_AF_ERR	= 0x3,
	NPA_AF_INT_VEC_POISON	= 0x4,
	NPA_AF_INT_VEC_CNT	= 0x5,
पूर्ण;

/* NIX Admin function Interrupt Vector Enumeration */
क्रमागत nix_af_पूर्णांक_vec_e अणु
	NIX_AF_INT_VEC_RVU	= 0x0,
	NIX_AF_INT_VEC_GEN	= 0x1,
	NIX_AF_INT_VEC_AQ_DONE	= 0x2,
	NIX_AF_INT_VEC_AF_ERR	= 0x3,
	NIX_AF_INT_VEC_POISON	= 0x4,
	NIX_AF_INT_VEC_CNT	= 0x5,
पूर्ण;

/**
 * RVU PF Interrupt Vector Enumeration
 */
क्रमागत rvu_pf_पूर्णांक_vec_e अणु
	RVU_PF_INT_VEC_VFFLR0     = 0x0,
	RVU_PF_INT_VEC_VFFLR1     = 0x1,
	RVU_PF_INT_VEC_VFME0      = 0x2,
	RVU_PF_INT_VEC_VFME1      = 0x3,
	RVU_PF_INT_VEC_VFPF_MBOX0 = 0x4,
	RVU_PF_INT_VEC_VFPF_MBOX1 = 0x5,
	RVU_PF_INT_VEC_AFPF_MBOX  = 0x6,
	RVU_PF_INT_VEC_CNT	  = 0x7,
पूर्ण;

/* NPA admin queue completion क्रमागतeration */
क्रमागत npa_aq_comp अणु
	NPA_AQ_COMP_NOTDONE    = 0x0,
	NPA_AQ_COMP_GOOD       = 0x1,
	NPA_AQ_COMP_SWERR      = 0x2,
	NPA_AQ_COMP_CTX_POISON = 0x3,
	NPA_AQ_COMP_CTX_FAULT  = 0x4,
	NPA_AQ_COMP_LOCKERR    = 0x5,
पूर्ण;

/* NPA admin queue context types */
क्रमागत npa_aq_ctype अणु
	NPA_AQ_CTYPE_AURA = 0x0,
	NPA_AQ_CTYPE_POOL = 0x1,
पूर्ण;

/* NPA admin queue inकाष्ठाion opcodes */
क्रमागत npa_aq_instop अणु
	NPA_AQ_INSTOP_NOP    = 0x0,
	NPA_AQ_INSTOP_INIT   = 0x1,
	NPA_AQ_INSTOP_WRITE  = 0x2,
	NPA_AQ_INSTOP_READ   = 0x3,
	NPA_AQ_INSTOP_LOCK   = 0x4,
	NPA_AQ_INSTOP_UNLOCK = 0x5,
पूर्ण;

/* ALLOC/FREE input queues Enumeration from coprocessors */
क्रमागत npa_inpq अणु
	NPA_INPQ_NIX0_RX       = 0x0,
	NPA_INPQ_NIX0_TX       = 0x1,
	NPA_INPQ_NIX1_RX       = 0x2,
	NPA_INPQ_NIX1_TX       = 0x3,
	NPA_INPQ_SSO           = 0x4,
	NPA_INPQ_TIM           = 0x5,
	NPA_INPQ_DPI           = 0x6,
	NPA_INPQ_AURA_OP       = 0xe,
	NPA_INPQ_INTERNAL_RSV  = 0xf,
पूर्ण;

/* NPA admin queue inकाष्ठाion काष्ठाure */
काष्ठा npa_aq_inst_s अणु
	u64 op                    : 4; /* W0 */
	u64 ctype                 : 4;
	u64 lf                    : 9;
	u64 reserved_17_23        : 7;
	u64 cindex                : 20;
	u64 reserved_44_62        : 19;
	u64 करोneपूर्णांक               : 1;
	u64 res_addr;			/* W1 */
पूर्ण;

/* NPA admin queue result काष्ठाure */
काष्ठा npa_aq_res_s अणु
	u64 op                    : 4; /* W0 */
	u64 ctype                 : 4;
	u64 compcode              : 8;
	u64 करोneपूर्णांक               : 1;
	u64 reserved_17_63        : 47;
	u64 reserved_64_127;		/* W1 */
पूर्ण;

काष्ठा npa_aura_s अणु
	u64 pool_addr;			/* W0 */
	u64 ena                   : 1;  /* W1 */
	u64 reserved_65           : 2;
	u64 pool_caching          : 1;
	u64 pool_way_mask         : 16;
	u64 avg_con               : 9;
	u64 reserved_93           : 1;
	u64 pool_drop_ena         : 1;
	u64 aura_drop_ena         : 1;
	u64 bp_ena                : 2;
	u64 reserved_98_103       : 6;
	u64 aura_drop             : 8;
	u64 shअगरt                 : 6;
	u64 reserved_118_119      : 2;
	u64 avg_level             : 8;
	u64 count                 : 36; /* W2 */
	u64 reserved_164_167      : 4;
	u64 nix0_bpid             : 9;
	u64 reserved_177_179      : 3;
	u64 nix1_bpid             : 9;
	u64 reserved_189_191      : 3;
	u64 limit                 : 36; /* W3 */
	u64 reserved_228_231      : 4;
	u64 bp                    : 8;
	u64 reserved_241_243      : 3;
	u64 fc_be                 : 1;
	u64 fc_ena                : 1;
	u64 fc_up_crossing        : 1;
	u64 fc_stype              : 2;
	u64 fc_hyst_bits          : 4;
	u64 reserved_252_255      : 4;
	u64 fc_addr;			/* W4 */
	u64 pool_drop             : 8;  /* W5 */
	u64 update_समय           : 16;
	u64 err_पूर्णांक               : 8;
	u64 err_पूर्णांक_ena           : 8;
	u64 thresh_पूर्णांक            : 1;
	u64 thresh_पूर्णांक_ena        : 1;
	u64 thresh_up             : 1;
	u64 reserved_363          : 1;
	u64 thresh_qपूर्णांक_idx       : 7;
	u64 reserved_371          : 1;
	u64 err_qपूर्णांक_idx          : 7;
	u64 reserved_379_383      : 5;
	u64 thresh                : 36; /* W6*/
	u64 rsvd_423_420          : 4;
	u64 fc_msh_dst            : 11;
	u64 reserved_435_447      : 13;
	u64 reserved_448_511;		/* W7 */
पूर्ण;

काष्ठा npa_pool_s अणु
	u64 stack_base;			/* W0 */
	u64 ena                   : 1;
	u64 nat_align             : 1;
	u64 reserved_66_67        : 2;
	u64 stack_caching         : 1;
	u64 reserved_70_71        : 3;
	u64 stack_way_mask        : 16;
	u64 buf_offset            : 12;
	u64 reserved_100_103      : 4;
	u64 buf_size              : 11;
	u64 reserved_115_127      : 13;
	u64 stack_max_pages       : 32;
	u64 stack_pages           : 32;
	u64 op_pc                 : 48;
	u64 reserved_240_255      : 16;
	u64 stack_offset          : 4;
	u64 reserved_260_263      : 4;
	u64 shअगरt                 : 6;
	u64 reserved_270_271      : 2;
	u64 avg_level             : 8;
	u64 avg_con               : 9;
	u64 fc_ena                : 1;
	u64 fc_stype              : 2;
	u64 fc_hyst_bits          : 4;
	u64 fc_up_crossing        : 1;
	u64 fc_be		  : 1;
	u64 reserved_298_299      : 2;
	u64 update_समय           : 16;
	u64 reserved_316_319      : 4;
	u64 fc_addr;			/* W5 */
	u64 ptr_start;			/* W6 */
	u64 ptr_end;			/* W7 */
	u64 reserved_512_535      : 24;
	u64 err_पूर्णांक               : 8;
	u64 err_पूर्णांक_ena           : 8;
	u64 thresh_पूर्णांक            : 1;
	u64 thresh_पूर्णांक_ena        : 1;
	u64 thresh_up             : 1;
	u64 reserved_555          : 1;
	u64 thresh_qपूर्णांक_idx       : 7;
	u64 reserved_563          : 1;
	u64 err_qपूर्णांक_idx          : 7;
	u64 reserved_571_575      : 5;
	u64 thresh                : 36;
	u64 rsvd_615_612	  : 4;
	u64 fc_msh_dst		  : 11;
	u64 reserved_627_639      : 13;
	u64 reserved_640_703;		/* W10 */
	u64 reserved_704_767;		/* W11 */
	u64 reserved_768_831;		/* W12 */
	u64 reserved_832_895;		/* W13 */
	u64 reserved_896_959;		/* W14 */
	u64 reserved_960_1023;		/* W15 */
पूर्ण;

/* NIX admin queue completion status */
क्रमागत nix_aq_comp अणु
	NIX_AQ_COMP_NOTDONE        = 0x0,
	NIX_AQ_COMP_GOOD           = 0x1,
	NIX_AQ_COMP_SWERR          = 0x2,
	NIX_AQ_COMP_CTX_POISON     = 0x3,
	NIX_AQ_COMP_CTX_FAULT      = 0x4,
	NIX_AQ_COMP_LOCKERR        = 0x5,
	NIX_AQ_COMP_SQB_ALLOC_FAIL = 0x6,
पूर्ण;

/* NIX admin queue context types */
क्रमागत nix_aq_ctype अणु
	NIX_AQ_CTYPE_RQ   = 0x0,
	NIX_AQ_CTYPE_SQ   = 0x1,
	NIX_AQ_CTYPE_CQ   = 0x2,
	NIX_AQ_CTYPE_MCE  = 0x3,
	NIX_AQ_CTYPE_RSS  = 0x4,
	NIX_AQ_CTYPE_DYNO = 0x5,
	NIX_AQ_CTYPE_BAND_PROF = 0x6,
पूर्ण;

/* NIX admin queue inकाष्ठाion opcodes */
क्रमागत nix_aq_instop अणु
	NIX_AQ_INSTOP_NOP    = 0x0,
	NIX_AQ_INSTOP_INIT   = 0x1,
	NIX_AQ_INSTOP_WRITE  = 0x2,
	NIX_AQ_INSTOP_READ   = 0x3,
	NIX_AQ_INSTOP_LOCK   = 0x4,
	NIX_AQ_INSTOP_UNLOCK = 0x5,
पूर्ण;

/* NIX admin queue inकाष्ठाion काष्ठाure */
काष्ठा nix_aq_inst_s अणु
	u64 op			: 4;
	u64 ctype		: 4;
	u64 lf			: 9;
	u64 reserved_17_23	: 7;
	u64 cindex		: 20;
	u64 reserved_44_62	: 19;
	u64 करोneपूर्णांक		: 1;
	u64 res_addr;			/* W1 */
पूर्ण;

/* NIX admin queue result काष्ठाure */
काष्ठा nix_aq_res_s अणु
	u64 op			: 4;
	u64 ctype		: 4;
	u64 compcode		: 8;
	u64 करोneपूर्णांक		: 1;
	u64 reserved_17_63	: 47;
	u64 reserved_64_127;		/* W1 */
पूर्ण;

/* NIX Completion queue context काष्ठाure */
काष्ठा nix_cq_ctx_s अणु
	u64 base;
	u64 rsvd_64_67		: 4;
	u64 bp_ena		: 1;
	u64 rsvd_69_71		: 3;
	u64 bpid		: 9;
	u64 rsvd_81_83		: 3;
	u64 qपूर्णांक_idx		: 7;
	u64 cq_err		: 1;
	u64 cपूर्णांक_idx		: 7;
	u64 avg_con		: 9;
	u64 wrptr		: 20;
	u64 tail		: 20;
	u64 head		: 20;
	u64 avg_level		: 8;
	u64 update_समय		: 16;
	u64 bp			: 8;
	u64 drop		: 8;
	u64 drop_ena		: 1;
	u64 ena			: 1;
	u64 rsvd_210_211	: 2;
	u64 substream		: 20;
	u64 caching		: 1;
	u64 rsvd_233_235	: 3;
	u64 qsize		: 4;
	u64 cq_err_पूर्णांक		: 8;
	u64 cq_err_पूर्णांक_ena	: 8;
पूर्ण;

/* CN10K NIX Receive queue context काष्ठाure */
काष्ठा nix_cn10k_rq_ctx_s अणु
	u64 ena			: 1;
	u64 sso_ena		: 1;
	u64 ipsech_ena		: 1;
	u64 ena_wqwd		: 1;
	u64 cq			: 20;
	u64 rsvd_36_24		: 13;
	u64 lenerr_dis		: 1;
	u64 csum_il4_dis	: 1;
	u64 csum_ol4_dis	: 1;
	u64 len_il4_dis		: 1;
	u64 len_il3_dis		: 1;
	u64 len_ol4_dis		: 1;
	u64 len_ol3_dis		: 1;
	u64 wqe_aura		: 20;
	u64 spb_aura		: 20;
	u64 lpb_aura		: 20;
	u64 sso_grp		: 10;
	u64 sso_tt		: 2;
	u64 pb_caching		: 2;
	u64 wqe_caching		: 1;
	u64 xqe_drop_ena	: 1;
	u64 spb_drop_ena	: 1;
	u64 lpb_drop_ena	: 1;
	u64 pb_stashing		: 1;
	u64 ipsecd_drop_ena	: 1;
	u64 chi_ena		: 1;
	u64 rsvd_127_125	: 3;
	u64 band_prof_id	: 10; /* W2 */
	u64 rsvd_138		: 1;
	u64 policer_ena		: 1;
	u64 spb_sizem1		: 6;
	u64 wqe_skip		: 2;
	u64 rsvd_150_148	: 3;
	u64 spb_ena		: 1;
	u64 lpb_sizem1		: 12;
	u64 first_skip		: 7;
	u64 rsvd_171		: 1;
	u64 later_skip		: 6;
	u64 xqe_imm_size	: 6;
	u64 rsvd_189_184	: 6;
	u64 xqe_imm_copy	: 1;
	u64 xqe_hdr_split	: 1;
	u64 xqe_drop		: 8; /* W3 */
	u64 xqe_pass		: 8;
	u64 wqe_pool_drop	: 8;
	u64 wqe_pool_pass	: 8;
	u64 spb_aura_drop	: 8;
	u64 spb_aura_pass	: 8;
	u64 spb_pool_drop	: 8;
	u64 spb_pool_pass	: 8;
	u64 lpb_aura_drop	: 8; /* W4 */
	u64 lpb_aura_pass	: 8;
	u64 lpb_pool_drop	: 8;
	u64 lpb_pool_pass	: 8;
	u64 rsvd_291_288	: 4;
	u64 rq_पूर्णांक		: 8;
	u64 rq_पूर्णांक_ena		: 8;
	u64 qपूर्णांक_idx		: 7;
	u64 rsvd_319_315	: 5;
	u64 ltag		: 24; /* W5 */
	u64 good_utag		: 8;
	u64 bad_utag		: 8;
	u64 flow_tagw		: 6;
	u64 ipsec_vwqe		: 1;
	u64 vwqe_ena		: 1;
	u64 vwqe_रुको		: 8;
	u64 max_vsize_exp	: 4;
	u64 vwqe_skip		: 2;
	u64 rsvd_383_382	: 2;
	u64 octs		: 48; /* W6 */
	u64 rsvd_447_432	: 16;
	u64 pkts		: 48; /* W7 */
	u64 rsvd_511_496	: 16;
	u64 drop_octs		: 48; /* W8 */
	u64 rsvd_575_560	: 16;
	u64 drop_pkts		: 48; /* W9 */
	u64 rsvd_639_624	: 16;
	u64 re_pkts		: 48; /* W10 */
	u64 rsvd_703_688	: 16;
	u64 rsvd_767_704;		/* W11 */
	u64 rsvd_831_768;		/* W12 */
	u64 rsvd_895_832;		/* W13 */
	u64 rsvd_959_896;		/* W14 */
	u64 rsvd_1023_960;		/* W15 */
पूर्ण;

/* CN10K NIX Send queue context काष्ठाure */
काष्ठा nix_cn10k_sq_ctx_s अणु
	u64 ena                   : 1;
	u64 qपूर्णांक_idx              : 6;
	u64 substream             : 20;
	u64 sdp_mcast             : 1;
	u64 cq                    : 20;
	u64 sqe_way_mask          : 16;
	u64 smq                   : 10; /* W1 */
	u64 cq_ena                : 1;
	u64 xoff                  : 1;
	u64 sso_ena               : 1;
	u64 smq_rr_weight         : 14;
	u64 शेष_chan          : 12;
	u64 sqb_count             : 16;
	u64 rsvd_120_119          : 2;
	u64 smq_rr_count_lb       : 7;
	u64 smq_rr_count_ub       : 25; /* W2 */
	u64 sqb_aura              : 20;
	u64 sq_पूर्णांक                : 8;
	u64 sq_पूर्णांक_ena            : 8;
	u64 sqe_stype             : 2;
	u64 rsvd_191              : 1;
	u64 max_sqe_size          : 2; /* W3 */
	u64 cq_limit              : 8;
	u64 lmt_dis               : 1;
	u64 mnq_dis               : 1;
	u64 smq_next_sq           : 20;
	u64 smq_lso_segnum        : 8;
	u64 tail_offset           : 6;
	u64 smenq_offset          : 6;
	u64 head_offset           : 6;
	u64 smenq_next_sqb_vld    : 1;
	u64 smq_pend              : 1;
	u64 smq_next_sq_vld       : 1;
	u64 rsvd_255_253          : 3;
	u64 next_sqb              : 64; /* W4 */
	u64 tail_sqb              : 64; /* W5 */
	u64 smenq_sqb             : 64; /* W6 */
	u64 smenq_next_sqb        : 64; /* W7 */
	u64 head_sqb              : 64; /* W8 */
	u64 rsvd_583_576          : 8;  /* W9 */
	u64 vfi_lso_total         : 18;
	u64 vfi_lso_sizem1        : 3;
	u64 vfi_lso_sb            : 8;
	u64 vfi_lso_mps           : 14;
	u64 vfi_lso_vlan0_ins_ena : 1;
	u64 vfi_lso_vlan1_ins_ena : 1;
	u64 vfi_lso_vld           : 1;
	u64 rsvd_639_630          : 10;
	u64 scm_lso_rem           : 18; /* W10 */
	u64 rsvd_703_658          : 46;
	u64 octs                  : 48; /* W11 */
	u64 rsvd_767_752          : 16;
	u64 pkts                  : 48; /* W12 */
	u64 rsvd_831_816          : 16;
	u64 rsvd_895_832          : 64; /* W13 */
	u64 dropped_octs          : 48;
	u64 rsvd_959_944          : 16;
	u64 dropped_pkts          : 48;
	u64 rsvd_1023_1008        : 16;
पूर्ण;

/* NIX Receive queue context काष्ठाure */
काष्ठा nix_rq_ctx_s अणु
	u64 ena           : 1;
	u64 sso_ena       : 1;
	u64 ipsech_ena    : 1;
	u64 ena_wqwd      : 1;
	u64 cq            : 20;
	u64 substream     : 20;
	u64 wqe_aura      : 20;
	u64 spb_aura      : 20;
	u64 lpb_aura      : 20;
	u64 sso_grp       : 10;
	u64 sso_tt        : 2;
	u64 pb_caching    : 2;
	u64 wqe_caching   : 1;
	u64 xqe_drop_ena  : 1;
	u64 spb_drop_ena  : 1;
	u64 lpb_drop_ena  : 1;
	u64 rsvd_127_122  : 6;
	u64 rsvd_139_128  : 12; /* W2 */
	u64 spb_sizem1    : 6;
	u64 wqe_skip      : 2;
	u64 rsvd_150_148  : 3;
	u64 spb_ena       : 1;
	u64 lpb_sizem1    : 12;
	u64 first_skip    : 7;
	u64 rsvd_171      : 1;
	u64 later_skip    : 6;
	u64 xqe_imm_size  : 6;
	u64 rsvd_189_184  : 6;
	u64 xqe_imm_copy  : 1;
	u64 xqe_hdr_split : 1;
	u64 xqe_drop      : 8; /* W3*/
	u64 xqe_pass      : 8;
	u64 wqe_pool_drop : 8;
	u64 wqe_pool_pass : 8;
	u64 spb_aura_drop : 8;
	u64 spb_aura_pass : 8;
	u64 spb_pool_drop : 8;
	u64 spb_pool_pass : 8;
	u64 lpb_aura_drop : 8; /* W4 */
	u64 lpb_aura_pass : 8;
	u64 lpb_pool_drop : 8;
	u64 lpb_pool_pass : 8;
	u64 rsvd_291_288  : 4;
	u64 rq_पूर्णांक        : 8;
	u64 rq_पूर्णांक_ena    : 8;
	u64 qपूर्णांक_idx      : 7;
	u64 rsvd_319_315  : 5;
	u64 ltag          : 24; /* W5 */
	u64 good_utag     : 8;
	u64 bad_utag      : 8;
	u64 flow_tagw     : 6;
	u64 rsvd_383_366  : 18;
	u64 octs          : 48; /* W6 */
	u64 rsvd_447_432  : 16;
	u64 pkts          : 48; /* W7 */
	u64 rsvd_511_496  : 16;
	u64 drop_octs     : 48; /* W8 */
	u64 rsvd_575_560  : 16;
	u64 drop_pkts     : 48; /* W9 */
	u64 rsvd_639_624  : 16;
	u64 re_pkts       : 48; /* W10 */
	u64 rsvd_703_688  : 16;
	u64 rsvd_767_704;		/* W11 */
	u64 rsvd_831_768;		/* W12 */
	u64 rsvd_895_832;		/* W13 */
	u64 rsvd_959_896;		/* W14 */
	u64 rsvd_1023_960;		/* W15 */
पूर्ण;

/* NIX sqe sizes */
क्रमागत nix_maxsqesz अणु
	NIX_MAXSQESZ_W16 = 0x0,
	NIX_MAXSQESZ_W8  = 0x1,
पूर्ण;

/* NIX SQB caching type */
क्रमागत nix_stype अणु
	NIX_STYPE_STF = 0x0,
	NIX_STYPE_STT = 0x1,
	NIX_STYPE_STP = 0x2,
पूर्ण;

/* NIX Send queue context काष्ठाure */
काष्ठा nix_sq_ctx_s अणु
	u64 ena                   : 1;
	u64 qपूर्णांक_idx              : 6;
	u64 substream             : 20;
	u64 sdp_mcast             : 1;
	u64 cq                    : 20;
	u64 sqe_way_mask          : 16;
	u64 smq                   : 9;
	u64 cq_ena                : 1;
	u64 xoff                  : 1;
	u64 sso_ena               : 1;
	u64 smq_rr_quantum        : 24;
	u64 शेष_chan          : 12;
	u64 sqb_count             : 16;
	u64 smq_rr_count          : 25;
	u64 sqb_aura              : 20;
	u64 sq_पूर्णांक                : 8;
	u64 sq_पूर्णांक_ena            : 8;
	u64 sqe_stype             : 2;
	u64 rsvd_191              : 1;
	u64 max_sqe_size          : 2;
	u64 cq_limit              : 8;
	u64 lmt_dis               : 1;
	u64 mnq_dis               : 1;
	u64 smq_next_sq           : 20;
	u64 smq_lso_segnum        : 8;
	u64 tail_offset           : 6;
	u64 smenq_offset          : 6;
	u64 head_offset           : 6;
	u64 smenq_next_sqb_vld    : 1;
	u64 smq_pend              : 1;
	u64 smq_next_sq_vld       : 1;
	u64 rsvd_255_253          : 3;
	u64 next_sqb              : 64;/* W4 */
	u64 tail_sqb              : 64;/* W5 */
	u64 smenq_sqb             : 64;/* W6 */
	u64 smenq_next_sqb        : 64;/* W7 */
	u64 head_sqb              : 64;/* W8 */
	u64 rsvd_583_576          : 8;
	u64 vfi_lso_total         : 18;
	u64 vfi_lso_sizem1        : 3;
	u64 vfi_lso_sb            : 8;
	u64 vfi_lso_mps           : 14;
	u64 vfi_lso_vlan0_ins_ena : 1;
	u64 vfi_lso_vlan1_ins_ena : 1;
	u64 vfi_lso_vld           : 1;
	u64 rsvd_639_630          : 10;
	u64 scm_lso_rem           : 18;
	u64 rsvd_703_658          : 46;
	u64 octs                  : 48;
	u64 rsvd_767_752          : 16;
	u64 pkts                  : 48;
	u64 rsvd_831_816          : 16;
	u64 rsvd_895_832          : 64;/* W13 */
	u64 dropped_octs          : 48;
	u64 rsvd_959_944          : 16;
	u64 dropped_pkts          : 48;
	u64 rsvd_1023_1008        : 16;
पूर्ण;

/* NIX Receive side scaling entry काष्ठाure*/
काष्ठा nix_rsse_s अणु
	uपूर्णांक32_t rq			: 20;
	uपूर्णांक32_t reserved_20_31		: 12;

पूर्ण;

/* NIX receive multicast/mirror entry काष्ठाure */
काष्ठा nix_rx_mce_s अणु
	uपूर्णांक64_t op         : 2;
	uपूर्णांक64_t rsvd_2     : 1;
	uपूर्णांक64_t eol        : 1;
	uपूर्णांक64_t index      : 20;
	uपूर्णांक64_t rsvd_31_24 : 8;
	uपूर्णांक64_t pf_func    : 16;
	uपूर्णांक64_t next       : 16;
पूर्ण;

क्रमागत nix_lsoalg अणु
	NIX_LSOALG_NOP,
	NIX_LSOALG_ADD_SEGNUM,
	NIX_LSOALG_ADD_PAYLEN,
	NIX_LSOALG_ADD_OFFSET,
	NIX_LSOALG_TCP_FLAGS,
पूर्ण;

क्रमागत nix_txlayer अणु
	NIX_TXLAYER_OL3,
	NIX_TXLAYER_OL4,
	NIX_TXLAYER_IL3,
	NIX_TXLAYER_IL4,
पूर्ण;

काष्ठा nix_lso_क्रमmat अणु
	u64 offset		: 8;
	u64 layer		: 2;
	u64 rsvd_10_11		: 2;
	u64 sizem1		: 2;
	u64 rsvd_14_15		: 2;
	u64 alg			: 3;
	u64 rsvd_19_63		: 45;
पूर्ण;

काष्ठा nix_rx_flowkey_alg अणु
	u64 key_offset		:6;
	u64 ln_mask		:1;
	u64 fn_mask		:1;
	u64 hdr_offset		:8;
	u64 bytesm1		:5;
	u64 lid			:3;
	u64 reserved_24_24	:1;
	u64 ena			:1;
	u64 sel_chan		:1;
	u64 ltype_mask		:4;
	u64 ltype_match		:4;
	u64 reserved_35_63	:29;
पूर्ण;

/* NIX VTAG size */
क्रमागत nix_vtag_size अणु
	VTAGSIZE_T4   = 0x0,
	VTAGSIZE_T8   = 0x1,
पूर्ण;

क्रमागत nix_tx_vtag_op अणु
	NOP		= 0x0,
	VTAG_INSERT	= 0x1,
	VTAG_REPLACE	= 0x2,
पूर्ण;

/* NIX RX VTAG actions */
#घोषणा VTAG_STRIP	BIT_ULL(4)
#घोषणा VTAG_CAPTURE	BIT_ULL(5)

#पूर्ण_अगर /* RVU_STRUCT_H */
