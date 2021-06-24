<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 * Copyright (C) 2020 Marvell.
 */

#अगर_अघोषित __OTX2_CPT_HW_TYPES_H
#घोषणा __OTX2_CPT_HW_TYPES_H

#समावेश <linux/types.h>

/* Device IDs */
#घोषणा OTX2_CPT_PCI_PF_DEVICE_ID 0xA0FD
#घोषणा OTX2_CPT_PCI_VF_DEVICE_ID 0xA0FE

/* Mailbox पूर्णांकerrupts offset */
#घोषणा OTX2_CPT_PF_MBOX_INT	6
#घोषणा OTX2_CPT_PF_INT_VEC_E_MBOXX(x, a) ((x) + (a))

/* Maximum supported microcode groups */
#घोषणा OTX2_CPT_MAX_ENGINE_GROUPS 8

/* CPT inकाष्ठाion size in bytes */
#घोषणा OTX2_CPT_INST_SIZE	64
/*
 * CPT VF MSIX vectors and their offsets
 */
#घोषणा OTX2_CPT_VF_MSIX_VECTORS 1
#घोषणा OTX2_CPT_VF_INTR_MBOX_MASK BIT(0)

/* CPT LF MSIX vectors */
#घोषणा OTX2_CPT_LF_MSIX_VECTORS 2

/* OcteonTX2 CPT PF रेजिस्टरs */
#घोषणा OTX2_CPT_PF_CONSTANTS           (0x0)
#घोषणा OTX2_CPT_PF_RESET               (0x100)
#घोषणा OTX2_CPT_PF_DIAG                (0x120)
#घोषणा OTX2_CPT_PF_BIST_STATUS         (0x160)
#घोषणा OTX2_CPT_PF_ECC0_CTL            (0x200)
#घोषणा OTX2_CPT_PF_ECC0_FLIP           (0x210)
#घोषणा OTX2_CPT_PF_ECC0_INT            (0x220)
#घोषणा OTX2_CPT_PF_ECC0_INT_W1S        (0x230)
#घोषणा OTX2_CPT_PF_ECC0_ENA_W1S        (0x240)
#घोषणा OTX2_CPT_PF_ECC0_ENA_W1C        (0x250)
#घोषणा OTX2_CPT_PF_MBOX_INTX(b)        (0x400 | (b) << 3)
#घोषणा OTX2_CPT_PF_MBOX_INT_W1SX(b)    (0x420 | (b) << 3)
#घोषणा OTX2_CPT_PF_MBOX_ENA_W1CX(b)    (0x440 | (b) << 3)
#घोषणा OTX2_CPT_PF_MBOX_ENA_W1SX(b)    (0x460 | (b) << 3)
#घोषणा OTX2_CPT_PF_EXEC_INT            (0x500)
#घोषणा OTX2_CPT_PF_EXEC_INT_W1S        (0x520)
#घोषणा OTX2_CPT_PF_EXEC_ENA_W1C        (0x540)
#घोषणा OTX2_CPT_PF_EXEC_ENA_W1S        (0x560)
#घोषणा OTX2_CPT_PF_GX_EN(b)            (0x600 | (b) << 3)
#घोषणा OTX2_CPT_PF_EXEC_INFO           (0x700)
#घोषणा OTX2_CPT_PF_EXEC_BUSY           (0x800)
#घोषणा OTX2_CPT_PF_EXEC_INFO0          (0x900)
#घोषणा OTX2_CPT_PF_EXEC_INFO1          (0x910)
#घोषणा OTX2_CPT_PF_INST_REQ_PC         (0x10000)
#घोषणा OTX2_CPT_PF_INST_LATENCY_PC     (0x10020)
#घोषणा OTX2_CPT_PF_RD_REQ_PC           (0x10040)
#घोषणा OTX2_CPT_PF_RD_LATENCY_PC       (0x10060)
#घोषणा OTX2_CPT_PF_RD_UC_PC            (0x10080)
#घोषणा OTX2_CPT_PF_ACTIVE_CYCLES_PC    (0x10100)
#घोषणा OTX2_CPT_PF_EXE_CTL             (0x4000000)
#घोषणा OTX2_CPT_PF_EXE_STATUS          (0x4000008)
#घोषणा OTX2_CPT_PF_EXE_CLK             (0x4000010)
#घोषणा OTX2_CPT_PF_EXE_DBG_CTL         (0x4000018)
#घोषणा OTX2_CPT_PF_EXE_DBG_DATA        (0x4000020)
#घोषणा OTX2_CPT_PF_EXE_BIST_STATUS     (0x4000028)
#घोषणा OTX2_CPT_PF_EXE_REQ_TIMER       (0x4000030)
#घोषणा OTX2_CPT_PF_EXE_MEM_CTL         (0x4000038)
#घोषणा OTX2_CPT_PF_EXE_PERF_CTL        (0x4001000)
#घोषणा OTX2_CPT_PF_EXE_DBG_CNTX(b)     (0x4001100 | (b) << 3)
#घोषणा OTX2_CPT_PF_EXE_PERF_EVENT_CNT  (0x4001180)
#घोषणा OTX2_CPT_PF_EXE_EPCI_INBX_CNT(b)  (0x4001200 | (b) << 3)
#घोषणा OTX2_CPT_PF_EXE_EPCI_OUTBX_CNT(b) (0x4001240 | (b) << 3)
#घोषणा OTX2_CPT_PF_ENGX_UCODE_BASE(b)  (0x4002000 | (b) << 3)
#घोषणा OTX2_CPT_PF_QX_CTL(b)           (0x8000000 | (b) << 20)
#घोषणा OTX2_CPT_PF_QX_GMCTL(b)         (0x8000020 | (b) << 20)
#घोषणा OTX2_CPT_PF_QX_CTL2(b)          (0x8000100 | (b) << 20)
#घोषणा OTX2_CPT_PF_VFX_MBOXX(b, c)     (0x8001000 | (b) << 20 | \
					 (c) << 8)

/* OcteonTX2 CPT LF रेजिस्टरs */
#घोषणा OTX2_CPT_LF_CTL                 (0x10)
#घोषणा OTX2_CPT_LF_DONE_WAIT           (0x30)
#घोषणा OTX2_CPT_LF_INPROG              (0x40)
#घोषणा OTX2_CPT_LF_DONE                (0x50)
#घोषणा OTX2_CPT_LF_DONE_ACK            (0x60)
#घोषणा OTX2_CPT_LF_DONE_INT_ENA_W1S    (0x90)
#घोषणा OTX2_CPT_LF_DONE_INT_ENA_W1C    (0xa0)
#घोषणा OTX2_CPT_LF_MISC_INT            (0xb0)
#घोषणा OTX2_CPT_LF_MISC_INT_W1S        (0xc0)
#घोषणा OTX2_CPT_LF_MISC_INT_ENA_W1S    (0xd0)
#घोषणा OTX2_CPT_LF_MISC_INT_ENA_W1C    (0xe0)
#घोषणा OTX2_CPT_LF_Q_BASE              (0xf0)
#घोषणा OTX2_CPT_LF_Q_SIZE              (0x100)
#घोषणा OTX2_CPT_LF_Q_INST_PTR          (0x110)
#घोषणा OTX2_CPT_LF_Q_GRP_PTR           (0x120)
#घोषणा OTX2_CPT_LF_NQX(a)              (0x400 | (a) << 3)
#घोषणा OTX2_CPT_RVU_FUNC_BLKADDR_SHIFT 20
/* LMT LF रेजिस्टरs */
#घोषणा OTX2_CPT_LMT_LFBASE             BIT_ULL(OTX2_CPT_RVU_FUNC_BLKADDR_SHIFT)
#घोषणा OTX2_CPT_LMT_LF_LMTLINEX(a)     (OTX2_CPT_LMT_LFBASE | 0x000 | \
					 (a) << 12)
/* RVU VF रेजिस्टरs */
#घोषणा OTX2_RVU_VF_INT                 (0x20)
#घोषणा OTX2_RVU_VF_INT_W1S             (0x28)
#घोषणा OTX2_RVU_VF_INT_ENA_W1S         (0x30)
#घोषणा OTX2_RVU_VF_INT_ENA_W1C         (0x38)

/*
 * Enumeration otx2_cpt_ucode_error_code_e
 *
 * Enumerates ucode errors
 */
क्रमागत otx2_cpt_ucode_comp_code_e अणु
	OTX2_CPT_UCC_SUCCESS = 0x00,
	OTX2_CPT_UCC_INVALID_OPCODE = 0x01,

	/* Scatter gather */
	OTX2_CPT_UCC_SG_WRITE_LENGTH = 0x02,
	OTX2_CPT_UCC_SG_LIST = 0x03,
	OTX2_CPT_UCC_SG_NOT_SUPPORTED = 0x04,

पूर्ण;

/*
 * Enumeration otx2_cpt_comp_e
 *
 * OcteonTX2 CPT Completion Enumeration
 * Enumerates the values of CPT_RES_S[COMPCODE].
 */
क्रमागत otx2_cpt_comp_e अणु
	OTX2_CPT_COMP_E_NOTDONE = 0x00,
	OTX2_CPT_COMP_E_GOOD = 0x01,
	OTX2_CPT_COMP_E_FAULT = 0x02,
	OTX2_CPT_COMP_E_HWERR = 0x04,
	OTX2_CPT_COMP_E_INSTERR = 0x05,
	OTX2_CPT_COMP_E_LAST_ENTRY = 0x06
पूर्ण;

/*
 * Enumeration otx2_cpt_vf_पूर्णांक_vec_e
 *
 * OcteonTX2 CPT VF MSI-X Vector Enumeration
 * Enumerates the MSI-X पूर्णांकerrupt vectors.
 */
क्रमागत otx2_cpt_vf_पूर्णांक_vec_e अणु
	OTX2_CPT_VF_INT_VEC_E_MBOX = 0x00
पूर्ण;

/*
 * Enumeration otx2_cpt_lf_पूर्णांक_vec_e
 *
 * OcteonTX2 CPT LF MSI-X Vector Enumeration
 * Enumerates the MSI-X पूर्णांकerrupt vectors.
 */
क्रमागत otx2_cpt_lf_पूर्णांक_vec_e अणु
	OTX2_CPT_LF_INT_VEC_E_MISC = 0x00,
	OTX2_CPT_LF_INT_VEC_E_DONE = 0x01
पूर्ण;

/*
 * Structure otx2_cpt_inst_s
 *
 * CPT Inकाष्ठाion Structure
 * This काष्ठाure specअगरies the inकाष्ठाion layout. Inकाष्ठाions are
 * stored in memory as little-endian unless CPT()_PF_Q()_CTL[INST_BE] is set.
 * cpt_inst_s_s
 * Word 0
 * करोneपूर्णांक:1 Done पूर्णांकerrupt.
 *	0 = No पूर्णांकerrupts related to this inकाष्ठाion.
 *	1 = When the inकाष्ठाion completes, CPT()_VQ()_DONE[DONE] will be
 *	incremented,and based on the rules described there an पूर्णांकerrupt may
 *	occur.
 * Word 1
 * res_addr [127: 64] Result IOVA.
 *	If nonzero, specअगरies where to ग_लिखो CPT_RES_S.
 *	If zero, no result काष्ठाure will be written.
 *	Address must be 16-byte aligned.
 *	Bits <63:49> are ignored by hardware; software should use a
 *	sign-extended bit <48> क्रम क्रमward compatibility.
 * Word 2
 *  grp:10 [171:162] If [WQ_PTR] is nonzero, the SSO guest-group to use when
 *	CPT submits work SSO.
 *	For the SSO to not discard the add-work request, FPA_PF_MAP() must map
 *	[GRP] and CPT()_PF_Q()_GMCTL[GMID] as valid.
 *  tt:2 [161:160] If [WQ_PTR] is nonzero, the SSO tag type to use when CPT
 *	submits work to SSO
 *  tag:32 [159:128] If [WQ_PTR] is nonzero, the SSO tag to use when CPT
 *	submits work to SSO.
 * Word 3
 *  wq_ptr [255:192] If [WQ_PTR] is nonzero, it is a poपूर्णांकer to a
 *	work-queue entry that CPT submits work to SSO after all context,
 *	output data, and result ग_लिखो operations are visible to other
 *	CNXXXX units and the cores. Bits <2:0> must be zero.
 *	Bits <63:49> are ignored by hardware; software should
 *	use a sign-extended bit <48> क्रम क्रमward compatibility.
 *	Internal:
 *	Bits <63:49>, <2:0> are ignored by hardware, treated as always 0x0.
 * Word 4
 *  ei0; [319:256] Engine inकाष्ठाion word 0. Passed to the AE/SE.
 * Word 5
 *  ei1; [383:320] Engine inकाष्ठाion word 1. Passed to the AE/SE.
 * Word 6
 *  ei2; [447:384] Engine inकाष्ठाion word 1. Passed to the AE/SE.
 * Word 7
 *  ei3; [511:448] Engine inकाष्ठाion word 1. Passed to the AE/SE.
 *
 */
जोड़ otx2_cpt_inst_s अणु
	u64 u[8];

	काष्ठा अणु
		/* Word 0 */
		u64 nixtxl:3;
		u64 करोneपूर्णांक:1;
		u64 nixtx_addr:60;
		/* Word 1 */
		u64 res_addr;
		/* Word 2 */
		u64 tag:32;
		u64 tt:2;
		u64 grp:10;
		u64 reserved_172_175:4;
		u64 rvu_pf_func:16;
		/* Word 3 */
		u64 qord:1;
		u64 reserved_194_193:2;
		u64 wq_ptr:61;
		/* Word 4 */
		u64 ei0;
		/* Word 5 */
		u64 ei1;
		/* Word 6 */
		u64 ei2;
		/* Word 7 */
		u64 ei3;
	पूर्ण s;
पूर्ण;

/*
 * Structure otx2_cpt_res_s
 *
 * CPT Result Structure
 * The CPT coprocessor ग_लिखोs the result काष्ठाure after it completes a
 * CPT_INST_S inकाष्ठाion. The result काष्ठाure is exactly 16 bytes, and
 * each inकाष्ठाion completion produces exactly one result काष्ठाure.
 *
 * This काष्ठाure is stored in memory as little-endian unless
 * CPT()_PF_Q()_CTL[INST_BE] is set.
 * cpt_res_s_s
 * Word 0
 *  करोneपूर्णांक:1 [16:16] Done पूर्णांकerrupt. This bit is copied from the
 *	corresponding inकाष्ठाion's CPT_INST_S[DONEINT].
 *  compcode:8 [7:0] Indicates completion/error status of the CPT coprocessor
 *	क्रम the	associated inकाष्ठाion, as क्रमागतerated by CPT_COMP_E.
 *	Core software may ग_लिखो the memory location containing [COMPCODE] to
 *	0x0 beक्रमe ringing the करोorbell, and then poll क्रम completion by
 *	checking क्रम a nonzero value.
 *	Once the core observes a nonzero [COMPCODE] value in this हाल,the CPT
 *	coprocessor will have also completed L2/DRAM ग_लिखो operations.
 * Word 1
 *  reserved
 *
 */
जोड़ otx2_cpt_res_s अणु
	u64 u[2];

	काष्ठा अणु
		u64 compcode:8;
		u64 uc_compcode:8;
		u64 करोneपूर्णांक:1;
		u64 reserved_17_63:47;
		u64 reserved_64_127;
	पूर्ण s;
पूर्ण;

/*
 * Register (RVU_PF_BAR0) cpt#_af_स्थिरants1
 *
 * CPT AF Constants Register
 * This रेजिस्टर contains implementation-related parameters of CPT.
 */
जोड़ otx2_cptx_af_स्थिरants1 अणु
	u64 u;
	काष्ठा otx2_cptx_af_स्थिरants1_s अणु
		u64 se:16;
		u64 ie:16;
		u64 ae:16;
		u64 reserved_48_63:16;
	पूर्ण s;
पूर्ण;

/*
 * RVU_PFVF_BAR2 - cpt_lf_misc_पूर्णांक
 *
 * This रेजिस्टर contain the per-queue miscellaneous पूर्णांकerrupts.
 *
 */
जोड़ otx2_cptx_lf_misc_पूर्णांक अणु
	u64 u;
	काष्ठा otx2_cptx_lf_misc_पूर्णांक_s अणु
		u64 reserved_0:1;
		u64 nqerr:1;
		u64 irde:1;
		u64 nwrp:1;
		u64 reserved_4:1;
		u64 hwerr:1;
		u64 fault:1;
		u64 reserved_7_63:57;
	पूर्ण s;
पूर्ण;

/*
 * RVU_PFVF_BAR2 - cpt_lf_misc_पूर्णांक_ena_w1s
 *
 * This रेजिस्टर sets पूर्णांकerrupt enable bits.
 *
 */
जोड़ otx2_cptx_lf_misc_पूर्णांक_ena_w1s अणु
	u64 u;
	काष्ठा otx2_cptx_lf_misc_पूर्णांक_ena_w1s_s अणु
		u64 reserved_0:1;
		u64 nqerr:1;
		u64 irde:1;
		u64 nwrp:1;
		u64 reserved_4:1;
		u64 hwerr:1;
		u64 fault:1;
		u64 reserved_7_63:57;
	पूर्ण s;
पूर्ण;

/*
 * RVU_PFVF_BAR2 - cpt_lf_ctl
 *
 * This रेजिस्टर configures the queue.
 *
 * When the queue is not execution-quiescent (see CPT_LF_INPROG[EENA,INFLIGHT]),
 * software must only ग_लिखो this रेजिस्टर with [ENA]=0.
 */
जोड़ otx2_cptx_lf_ctl अणु
	u64 u;
	काष्ठा otx2_cptx_lf_ctl_s अणु
		u64 ena:1;
		u64 fc_ena:1;
		u64 fc_up_crossing:1;
		u64 reserved_3:1;
		u64 fc_hyst_bits:4;
		u64 reserved_8_63:56;
	पूर्ण s;
पूर्ण;

/*
 * RVU_PFVF_BAR2 - cpt_lf_करोne_रुको
 *
 * This रेजिस्टर specअगरies the per-queue पूर्णांकerrupt coalescing settings.
 */
जोड़ otx2_cptx_lf_करोne_रुको अणु
	u64 u;
	काष्ठा otx2_cptx_lf_करोne_रुको_s अणु
		u64 num_रुको:20;
		u64 reserved_20_31:12;
		u64 समय_रुको:16;
		u64 reserved_48_63:16;
	पूर्ण s;
पूर्ण;

/*
 * RVU_PFVF_BAR2 - cpt_lf_करोne
 *
 * This रेजिस्टर contain the per-queue inकाष्ठाion करोne count.
 */
जोड़ otx2_cptx_lf_करोne अणु
	u64 u;
	काष्ठा otx2_cptx_lf_करोne_s अणु
		u64 करोne:20;
		u64 reserved_20_63:44;
	पूर्ण s;
पूर्ण;

/*
 * RVU_PFVF_BAR2 - cpt_lf_inprog
 *
 * These रेजिस्टरs contain the per-queue inकाष्ठाion in flight रेजिस्टरs.
 *
 */
जोड़ otx2_cptx_lf_inprog अणु
	u64 u;
	काष्ठा otx2_cptx_lf_inprog_s अणु
		u64 inflight:9;
		u64 reserved_9_15:7;
		u64 eena:1;
		u64 grp_drp:1;
		u64 reserved_18_30:13;
		u64 grb_partial:1;
		u64 grb_cnt:8;
		u64 gwb_cnt:8;
		u64 reserved_48_63:16;
	पूर्ण s;
पूर्ण;

/*
 * RVU_PFVF_BAR2 - cpt_lf_q_base
 *
 * CPT initializes these CSR fields to these values on any CPT_LF_Q_BASE ग_लिखो:
 * _ CPT_LF_Q_INST_PTR[XQ_XOR]=0.
 * _ CPT_LF_Q_INST_PTR[NQ_PTR]=2.
 * _ CPT_LF_Q_INST_PTR[DQ_PTR]=2.
 * _ CPT_LF_Q_GRP_PTR[XQ_XOR]=0.
 * _ CPT_LF_Q_GRP_PTR[NQ_PTR]=1.
 * _ CPT_LF_Q_GRP_PTR[DQ_PTR]=1.
 */
जोड़ otx2_cptx_lf_q_base अणु
	u64 u;
	काष्ठा otx2_cptx_lf_q_base_s अणु
		u64 fault:1;
		u64 reserved_1_6:6;
		u64 addr:46;
		u64 reserved_53_63:11;
	पूर्ण s;
पूर्ण;

/*
 * RVU_PFVF_BAR2 - cpt_lf_q_size
 *
 * CPT initializes these CSR fields to these values on any CPT_LF_Q_SIZE ग_लिखो:
 * _ CPT_LF_Q_INST_PTR[XQ_XOR]=0.
 * _ CPT_LF_Q_INST_PTR[NQ_PTR]=2.
 * _ CPT_LF_Q_INST_PTR[DQ_PTR]=2.
 * _ CPT_LF_Q_GRP_PTR[XQ_XOR]=0.
 * _ CPT_LF_Q_GRP_PTR[NQ_PTR]=1.
 * _ CPT_LF_Q_GRP_PTR[DQ_PTR]=1.
 */
जोड़ otx2_cptx_lf_q_size अणु
	u64 u;
	काष्ठा otx2_cptx_lf_q_size_s अणु
		u64 size_भाग40:15;
		u64 reserved_15_63:49;
	पूर्ण s;
पूर्ण;

/*
 * RVU_PF_BAR0 - cpt_af_lf_ctl
 *
 * This रेजिस्टर configures queues. This रेजिस्टर should be written only
 * when the queue is execution-quiescent (see CPT_LF_INPROG[INFLIGHT]).
 */
जोड़ otx2_cptx_af_lf_ctrl अणु
	u64 u;
	काष्ठा otx2_cptx_af_lf_ctrl_s अणु
		u64 pri:1;
		u64 reserved_1_8:8;
		u64 pf_func_inst:1;
		u64 cont_err:1;
		u64 reserved_11_15:5;
		u64 nixtx_en:1;
		u64 reserved_17_47:31;
		u64 grp:8;
		u64 reserved_56_63:8;
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर /* __OTX2_CPT_HW_TYPES_H */
