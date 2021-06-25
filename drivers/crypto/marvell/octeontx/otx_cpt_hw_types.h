<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Marvell OcteonTX CPT driver
 *
 * Copyright (C) 2019 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित __OTX_CPT_HW_TYPES_H
#घोषणा __OTX_CPT_HW_TYPES_H

#समावेश <linux/types.h>

/* Device IDs */
#घोषणा OTX_CPT_PCI_PF_DEVICE_ID 0xa040
#घोषणा OTX_CPT_PCI_VF_DEVICE_ID 0xa041

#घोषणा OTX_CPT_PCI_PF_SUBSYS_ID 0xa340
#घोषणा OTX_CPT_PCI_VF_SUBSYS_ID 0xa341

/* Configuration and status रेजिस्टरs are in BAR0 on OcteonTX platक्रमm */
#घोषणा OTX_CPT_PF_PCI_CFG_BAR	0
#घोषणा OTX_CPT_VF_PCI_CFG_BAR	0

#घोषणा OTX_CPT_BAR_E_CPTX_VFX_BAR0_OFFSET(a, b) \
	(0x000020000000ll + 0x1000000000ll * (a) + 0x100000ll * (b))
#घोषणा OTX_CPT_BAR_E_CPTX_VFX_BAR0_SIZE	0x400000

/* Mailbox पूर्णांकerrupts offset */
#घोषणा OTX_CPT_PF_MBOX_INT	3
#घोषणा OTX_CPT_PF_INT_VEC_E_MBOXX(x, a) ((x) + (a))
/* Number of MSIX supported in PF */
#घोषणा OTX_CPT_PF_MSIX_VECTORS 4
/* Maximum supported microcode groups */
#घोषणा OTX_CPT_MAX_ENGINE_GROUPS 8

/* CPT inकाष्ठाion size in bytes */
#घोषणा OTX_CPT_INST_SIZE 64
/* CPT queue next chunk poपूर्णांकer size in bytes */
#घोषणा OTX_CPT_NEXT_CHUNK_PTR_SIZE 8

/* OcteonTX CPT VF MSIX vectors and their offsets */
#घोषणा OTX_CPT_VF_MSIX_VECTORS 2
#घोषणा OTX_CPT_VF_INTR_MBOX_MASK BIT(0)
#घोषणा OTX_CPT_VF_INTR_DOVF_MASK BIT(1)
#घोषणा OTX_CPT_VF_INTR_IRDE_MASK BIT(2)
#घोषणा OTX_CPT_VF_INTR_NWRP_MASK BIT(3)
#घोषणा OTX_CPT_VF_INTR_SERR_MASK BIT(4)

/* OcteonTX CPT PF रेजिस्टरs */
#घोषणा OTX_CPT_PF_CONSTANTS		(0x0ll)
#घोषणा OTX_CPT_PF_RESET		(0x100ll)
#घोषणा OTX_CPT_PF_DIAG			(0x120ll)
#घोषणा OTX_CPT_PF_BIST_STATUS		(0x160ll)
#घोषणा OTX_CPT_PF_ECC0_CTL		(0x200ll)
#घोषणा OTX_CPT_PF_ECC0_FLIP		(0x210ll)
#घोषणा OTX_CPT_PF_ECC0_INT		(0x220ll)
#घोषणा OTX_CPT_PF_ECC0_INT_W1S		(0x230ll)
#घोषणा OTX_CPT_PF_ECC0_ENA_W1S		(0x240ll)
#घोषणा OTX_CPT_PF_ECC0_ENA_W1C		(0x250ll)
#घोषणा OTX_CPT_PF_MBOX_INTX(b)		(0x400ll | (u64)(b) << 3)
#घोषणा OTX_CPT_PF_MBOX_INT_W1SX(b)	(0x420ll | (u64)(b) << 3)
#घोषणा OTX_CPT_PF_MBOX_ENA_W1CX(b)	(0x440ll | (u64)(b) << 3)
#घोषणा OTX_CPT_PF_MBOX_ENA_W1SX(b)	(0x460ll | (u64)(b) << 3)
#घोषणा OTX_CPT_PF_EXEC_INT		(0x500ll)
#घोषणा OTX_CPT_PF_EXEC_INT_W1S		(0x520ll)
#घोषणा OTX_CPT_PF_EXEC_ENA_W1C		(0x540ll)
#घोषणा OTX_CPT_PF_EXEC_ENA_W1S		(0x560ll)
#घोषणा OTX_CPT_PF_GX_EN(b)		(0x600ll | (u64)(b) << 3)
#घोषणा OTX_CPT_PF_EXEC_INFO		(0x700ll)
#घोषणा OTX_CPT_PF_EXEC_BUSY		(0x800ll)
#घोषणा OTX_CPT_PF_EXEC_INFO0		(0x900ll)
#घोषणा OTX_CPT_PF_EXEC_INFO1		(0x910ll)
#घोषणा OTX_CPT_PF_INST_REQ_PC		(0x10000ll)
#घोषणा OTX_CPT_PF_INST_LATENCY_PC	(0x10020ll)
#घोषणा OTX_CPT_PF_RD_REQ_PC		(0x10040ll)
#घोषणा OTX_CPT_PF_RD_LATENCY_PC	(0x10060ll)
#घोषणा OTX_CPT_PF_RD_UC_PC		(0x10080ll)
#घोषणा OTX_CPT_PF_ACTIVE_CYCLES_PC	(0x10100ll)
#घोषणा OTX_CPT_PF_EXE_CTL		(0x4000000ll)
#घोषणा OTX_CPT_PF_EXE_STATUS		(0x4000008ll)
#घोषणा OTX_CPT_PF_EXE_CLK		(0x4000010ll)
#घोषणा OTX_CPT_PF_EXE_DBG_CTL		(0x4000018ll)
#घोषणा OTX_CPT_PF_EXE_DBG_DATA		(0x4000020ll)
#घोषणा OTX_CPT_PF_EXE_BIST_STATUS	(0x4000028ll)
#घोषणा OTX_CPT_PF_EXE_REQ_TIMER	(0x4000030ll)
#घोषणा OTX_CPT_PF_EXE_MEM_CTL		(0x4000038ll)
#घोषणा OTX_CPT_PF_EXE_PERF_CTL		(0x4001000ll)
#घोषणा OTX_CPT_PF_EXE_DBG_CNTX(b)	(0x4001100ll | (u64)(b) << 3)
#घोषणा OTX_CPT_PF_EXE_PERF_EVENT_CNT	(0x4001180ll)
#घोषणा OTX_CPT_PF_EXE_EPCI_INBX_CNT(b)	(0x4001200ll | (u64)(b) << 3)
#घोषणा OTX_CPT_PF_EXE_EPCI_OUTBX_CNT(b) (0x4001240ll | (u64)(b) << 3)
#घोषणा OTX_CPT_PF_ENGX_UCODE_BASE(b)	(0x4002000ll | (u64)(b) << 3)
#घोषणा OTX_CPT_PF_QX_CTL(b)		(0x8000000ll | (u64)(b) << 20)
#घोषणा OTX_CPT_PF_QX_GMCTL(b)		(0x8000020ll | (u64)(b) << 20)
#घोषणा OTX_CPT_PF_QX_CTL2(b)		(0x8000100ll | (u64)(b) << 20)
#घोषणा OTX_CPT_PF_VFX_MBOXX(b, c)	(0x8001000ll | (u64)(b) << 20 | \
					 (u64)(c) << 8)

/* OcteonTX CPT VF रेजिस्टरs */
#घोषणा OTX_CPT_VQX_CTL(b)		(0x100ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_SADDR(b)		(0x200ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_DONE_WAIT(b)	(0x400ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_INPROG(b)		(0x410ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_DONE(b)		(0x420ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_DONE_ACK(b)		(0x440ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_DONE_INT_W1S(b)	(0x460ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_DONE_INT_W1C(b)	(0x468ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_DONE_ENA_W1S(b)	(0x470ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_DONE_ENA_W1C(b)	(0x478ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_MISC_INT(b)		(0x500ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_MISC_INT_W1S(b)	(0x508ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_MISC_ENA_W1S(b)	(0x510ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_MISC_ENA_W1C(b)	(0x518ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VQX_DOORBELL(b)		(0x600ll | (u64)(b) << 20)
#घोषणा OTX_CPT_VFX_PF_MBOXX(b, c)	(0x1000ll | ((b) << 20) | ((c) << 3))

/*
 * Enumeration otx_cpt_ucode_error_code_e
 *
 * Enumerates ucode errors
 */
क्रमागत otx_cpt_ucode_error_code_e अणु
	CPT_NO_UCODE_ERROR = 0x00,
	ERR_OPCODE_UNSUPPORTED = 0x01,

	/* Scatter gather */
	ERR_SCATTER_GATHER_WRITE_LENGTH = 0x02,
	ERR_SCATTER_GATHER_LIST = 0x03,
	ERR_SCATTER_GATHER_NOT_SUPPORTED = 0x04,

पूर्ण;

/*
 * Enumeration otx_cpt_comp_e
 *
 * CPT OcteonTX Completion Enumeration
 * Enumerates the values of CPT_RES_S[COMPCODE].
 */
क्रमागत otx_cpt_comp_e अणु
	CPT_COMP_E_NOTDONE = 0x00,
	CPT_COMP_E_GOOD = 0x01,
	CPT_COMP_E_FAULT = 0x02,
	CPT_COMP_E_SWERR = 0x03,
	CPT_COMP_E_HWERR = 0x04,
	CPT_COMP_E_LAST_ENTRY = 0x05
पूर्ण;

/*
 * Enumeration otx_cpt_vf_पूर्णांक_vec_e
 *
 * CPT OcteonTX VF MSI-X Vector Enumeration
 * Enumerates the MSI-X पूर्णांकerrupt vectors.
 */
क्रमागत otx_cpt_vf_पूर्णांक_vec_e अणु
	CPT_VF_INT_VEC_E_MISC = 0x00,
	CPT_VF_INT_VEC_E_DONE = 0x01
पूर्ण;

/*
 * Structure cpt_inst_s
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
जोड़ otx_cpt_inst_s अणु
	u64 u[8];

	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_17_63:47;
		u64 करोneपूर्णांक:1;
		u64 reserved_0_15:16;
#अन्यथा /* Word 0 - Little Endian */
		u64 reserved_0_15:16;
		u64 करोneपूर्णांक:1;
		u64 reserved_17_63:47;
#पूर्ण_अगर /* Word 0 - End */
		u64 res_addr;
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 2 - Big Endian */
		u64 reserved_172_191:20;
		u64 grp:10;
		u64 tt:2;
		u64 tag:32;
#अन्यथा /* Word 2 - Little Endian */
		u64 tag:32;
		u64 tt:2;
		u64 grp:10;
		u64 reserved_172_191:20;
#पूर्ण_अगर /* Word 2 - End */
		u64 wq_ptr;
		u64 ei0;
		u64 ei1;
		u64 ei2;
		u64 ei3;
	पूर्ण s;
पूर्ण;

/*
 * Structure cpt_res_s
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
जोड़ otx_cpt_res_s अणु
	u64 u[2];
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_17_63:47;
		u64 करोneपूर्णांक:1;
		u64 reserved_8_15:8;
		u64 compcode:8;
#अन्यथा /* Word 0 - Little Endian */
		u64 compcode:8;
		u64 reserved_8_15:8;
		u64 करोneपूर्णांक:1;
		u64 reserved_17_63:47;
#पूर्ण_अगर /* Word 0 - End */
		u64 reserved_64_127;
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_pf_bist_status
 *
 * CPT PF Control Bist Status Register
 * This रेजिस्टर has the BIST status of memories. Each bit is the BIST result
 * of an inभागidual memory (per bit, 0 = pass and 1 = fail).
 * otx_cptx_pf_bist_status_s
 * Word0
 *  bstatus [29:0](RO/H) BIST status. One bit per memory, क्रमागतerated by
 *	CPT_RAMS_E.
 */
जोड़ otx_cptx_pf_bist_status अणु
	u64 u;
	काष्ठा otx_cptx_pf_bist_status_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_30_63:34;
		u64 bstatus:30;
#अन्यथा /* Word 0 - Little Endian */
		u64 bstatus:30;
		u64 reserved_30_63:34;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_pf_स्थिरants
 *
 * CPT PF Constants Register
 * This रेजिस्टर contains implementation-related parameters of CPT in CNXXXX.
 * otx_cptx_pf_स्थिरants_s
 * Word 0
 *  reserved_40_63:24 [63:40] Reserved.
 *  epcis:8 [39:32](RO) Number of EPCI busses.
 *  grps:8 [31:24](RO) Number of engine groups implemented.
 *  ae:8 [23:16](RO/H) Number of AEs. In CNXXXX, क्रम CPT0 वापसs 0x0,
 *	क्रम CPT1 वापसs 0x18, or less अगर there are fuse-disables.
 *  se:8 [15:8](RO/H) Number of SEs. In CNXXXX, क्रम CPT0 वापसs 0x30,
 *	or less अगर there are fuse-disables, क्रम CPT1 वापसs 0x0.
 *  vq:8 [7:0](RO) Number of VQs.
 */
जोड़ otx_cptx_pf_स्थिरants अणु
	u64 u;
	काष्ठा otx_cptx_pf_स्थिरants_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_40_63:24;
		u64 epcis:8;
		u64 grps:8;
		u64 ae:8;
		u64 se:8;
		u64 vq:8;
#अन्यथा /* Word 0 - Little Endian */
		u64 vq:8;
		u64 se:8;
		u64 ae:8;
		u64 grps:8;
		u64 epcis:8;
		u64 reserved_40_63:24;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_pf_exe_bist_status
 *
 * CPT PF Engine Bist Status Register
 * This रेजिस्टर has the BIST status of each engine.  Each bit is the
 * BIST result of an inभागidual engine (per bit, 0 = pass and 1 = fail).
 * otx_cptx_pf_exe_bist_status_s
 * Word0
 *  reserved_48_63:16 [63:48] reserved
 *  bstatus:48 [47:0](RO/H) BIST status. One bit per engine.
 *
 */
जोड़ otx_cptx_pf_exe_bist_status अणु
	u64 u;
	काष्ठा otx_cptx_pf_exe_bist_status_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_48_63:16;
		u64 bstatus:48;
#अन्यथा /* Word 0 - Little Endian */
		u64 bstatus:48;
		u64 reserved_48_63:16;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_pf_q#_ctl
 *
 * CPT Queue Control Register
 * This रेजिस्टर configures queues. This रेजिस्टर should be changed only
 * when quiescent (see CPT()_VQ()_INPROG[INFLIGHT]).
 * otx_cptx_pf_qx_ctl_s
 * Word0
 *  reserved_60_63:4 [63:60] reserved.
 *  aura:12; [59:48](R/W) Guest-aura क्रम वापसing this queue's
 *	inकाष्ठाion-chunk buffers to FPA. Only used when [INST_FREE] is set.
 *	For the FPA to not discard the request, FPA_PF_MAP() must map
 *	[AURA] and CPT()_PF_Q()_GMCTL[GMID] as valid.
 *  reserved_45_47:3 [47:45] reserved.
 *  size:13 [44:32](R/W) Command-buffer size, in number of 64-bit words per
 *	command buffer segment. Must be 8*n + 1, where n is the number of
 *	inकाष्ठाions per buffer segment.
 *  reserved_11_31:21 [31:11] Reserved.
 *  cont_err:1 [10:10](R/W) Continue on error.
 *	0 = When CPT()_VQ()_MISC_INT[NWRP], CPT()_VQ()_MISC_INT[IRDE] or
 *	CPT()_VQ()_MISC_INT[DOVF] are set by hardware or software via
 *	CPT()_VQ()_MISC_INT_W1S, then CPT()_VQ()_CTL[ENA] is cleared.  Due to
 *	pipelining, additional inकाष्ठाions may have been processed between the
 *	inकाष्ठाion causing the error and the next inकाष्ठाion in the disabled
 *	queue (the inकाष्ठाion at CPT()_VQ()_SADDR).
 *	1 = Ignore errors and जारी processing inकाष्ठाions.
 *	For diagnostic use only.
 *  inst_मुक्त:1 [9:9](R/W) Inकाष्ठाion FPA मुक्त. When set, when CPT reaches the
 *	end of an inकाष्ठाion chunk, that chunk will be मुक्तd to the FPA.
 *  inst_be:1 [8:8](R/W) Inकाष्ठाion big-endian control. When set, inकाष्ठाions,
 *	inकाष्ठाion next chunk poपूर्णांकers, and result काष्ठाures are stored in
 *	big-endian क्रमmat in memory.
 *  iqb_ldwb:1 [7:7](R/W) Inकाष्ठाion load करोn't ग_लिखो back.
 *	0 = The hardware issues NCB transient load (LDT) towards the cache,
 *	which अगर the line hits and is is dirty will cause the line to be
 *	written back beक्रमe being replaced.
 *	1 = The hardware issues NCB LDWB पढ़ो-and-invalidate command towards
 *	the cache when fetching the last word of inकाष्ठाions; as a result the
 *	line will not be written back when replaced.  This improves
 *	perक्रमmance, but software must not पढ़ो the inकाष्ठाions after they are
 *	posted to the hardware.	Reads that करो not consume the last word of a
 *	cache line always use LDI.
 *  reserved_4_6:3 [6:4] Reserved.
 *  grp:3; [3:1](R/W) Engine group.
 *  pri:1; [0:0](R/W) Queue priority.
 *	1 = This queue has higher priority. Round-robin between higher
 *	priority queues.
 *	0 = This queue has lower priority. Round-robin between lower
 *	priority queues.
 */
जोड़ otx_cptx_pf_qx_ctl अणु
	u64 u;
	काष्ठा otx_cptx_pf_qx_ctl_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_60_63:4;
		u64 aura:12;
		u64 reserved_45_47:3;
		u64 size:13;
		u64 reserved_11_31:21;
		u64 cont_err:1;
		u64 inst_मुक्त:1;
		u64 inst_be:1;
		u64 iqb_ldwb:1;
		u64 reserved_4_6:3;
		u64 grp:3;
		u64 pri:1;
#अन्यथा /* Word 0 - Little Endian */
		u64 pri:1;
		u64 grp:3;
		u64 reserved_4_6:3;
		u64 iqb_ldwb:1;
		u64 inst_be:1;
		u64 inst_मुक्त:1;
		u64 cont_err:1;
		u64 reserved_11_31:21;
		u64 size:13;
		u64 reserved_45_47:3;
		u64 aura:12;
		u64 reserved_60_63:4;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_vq#_saddr
 *
 * CPT Queue Starting Buffer Address Registers
 * These रेजिस्टरs set the inकाष्ठाion buffer starting address.
 * otx_cptx_vqx_saddr_s
 * Word0
 *  reserved_49_63:15 [63:49] Reserved.
 *  ptr:43 [48:6](R/W/H) Inकाष्ठाion buffer IOVA <48:6> (64-byte aligned).
 *	When written, it is the initial buffer starting address; when पढ़ो,
 *	it is the next पढ़ो poपूर्णांकer to be requested from L2C. The PTR field
 *	is overwritten with the next poपूर्णांकer each समय that the command buffer
 *	segment is exhausted. New commands will then be पढ़ो from the newly
 *	specअगरied command buffer poपूर्णांकer.
 *  reserved_0_5:6 [5:0] Reserved.
 *
 */
जोड़ otx_cptx_vqx_saddr अणु
	u64 u;
	काष्ठा otx_cptx_vqx_saddr_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_49_63:15;
		u64 ptr:43;
		u64 reserved_0_5:6;
#अन्यथा /* Word 0 - Little Endian */
		u64 reserved_0_5:6;
		u64 ptr:43;
		u64 reserved_49_63:15;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_vq#_misc_ena_w1s
 *
 * CPT Queue Misc Interrupt Enable Set Register
 * This रेजिस्टर sets पूर्णांकerrupt enable bits.
 * otx_cptx_vqx_misc_ena_w1s_s
 * Word0
 * reserved_5_63:59 [63:5] Reserved.
 * swerr:1 [4:4](R/W1S/H) Reads or sets enable क्रम
 *	CPT(0..1)_VQ(0..63)_MISC_INT[SWERR].
 * nwrp:1 [3:3](R/W1S/H) Reads or sets enable क्रम
 *	CPT(0..1)_VQ(0..63)_MISC_INT[NWRP].
 * irde:1 [2:2](R/W1S/H) Reads or sets enable क्रम
 *	CPT(0..1)_VQ(0..63)_MISC_INT[IRDE].
 * करोvf:1 [1:1](R/W1S/H) Reads or sets enable क्रम
 *	CPT(0..1)_VQ(0..63)_MISC_INT[DOVF].
 * mbox:1 [0:0](R/W1S/H) Reads or sets enable क्रम
 *	CPT(0..1)_VQ(0..63)_MISC_INT[MBOX].
 *
 */
जोड़ otx_cptx_vqx_misc_ena_w1s अणु
	u64 u;
	काष्ठा otx_cptx_vqx_misc_ena_w1s_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_5_63:59;
		u64 swerr:1;
		u64 nwrp:1;
		u64 irde:1;
		u64 करोvf:1;
		u64 mbox:1;
#अन्यथा /* Word 0 - Little Endian */
		u64 mbox:1;
		u64 करोvf:1;
		u64 irde:1;
		u64 nwrp:1;
		u64 swerr:1;
		u64 reserved_5_63:59;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_vq#_करोorbell
 *
 * CPT Queue Doorbell Registers
 * Doorbells क्रम the CPT inकाष्ठाion queues.
 * otx_cptx_vqx_करोorbell_s
 * Word0
 *  reserved_20_63:44 [63:20] Reserved.
 *  dbell_cnt:20 [19:0](R/W/H) Number of inकाष्ठाion queue 64-bit words to add
 *	to the CPT inकाष्ठाion करोorbell count. Readback value is the the
 *	current number of pending करोorbell requests. If counter overflows
 *	CPT()_VQ()_MISC_INT[DBELL_DOVF] is set. To reset the count back to
 *	zero, ग_लिखो one to clear CPT()_VQ()_MISC_INT_ENA_W1C[DBELL_DOVF],
 *	then ग_लिखो a value of 2^20 minus the पढ़ो [DBELL_CNT], then ग_लिखो one
 *	to CPT()_VQ()_MISC_INT_W1C[DBELL_DOVF] and
 *	CPT()_VQ()_MISC_INT_ENA_W1S[DBELL_DOVF]. Must be a multiple of 8.
 *	All CPT inकाष्ठाions are 8 words and require a करोorbell count of
 *	multiple of 8.
 */
जोड़ otx_cptx_vqx_करोorbell अणु
	u64 u;
	काष्ठा otx_cptx_vqx_करोorbell_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_20_63:44;
		u64 dbell_cnt:20;
#अन्यथा /* Word 0 - Little Endian */
		u64 dbell_cnt:20;
		u64 reserved_20_63:44;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_vq#_inprog
 *
 * CPT Queue In Progress Count Registers
 * These रेजिस्टरs contain the per-queue inकाष्ठाion in flight रेजिस्टरs.
 * otx_cptx_vqx_inprog_s
 * Word0
 *  reserved_8_63:56 [63:8] Reserved.
 *  inflight:8 [7:0](RO/H) Inflight count. Counts the number of inकाष्ठाions
 *	क्रम the VF क्रम which CPT is fetching, executing or responding to
 *	inकाष्ठाions. However this करोes not include any पूर्णांकerrupts that are
 *	aरुकोing software handling (CPT()_VQ()_DONE[DONE] != 0x0).
 *	A queue may not be reconfigured until:
 *	1. CPT()_VQ()_CTL[ENA] is cleared by software.
 *	2. [INFLIGHT] is polled until equals to zero.
 */
जोड़ otx_cptx_vqx_inprog अणु
	u64 u;
	काष्ठा otx_cptx_vqx_inprog_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_8_63:56;
		u64 inflight:8;
#अन्यथा /* Word 0 - Little Endian */
		u64 inflight:8;
		u64 reserved_8_63:56;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_vq#_misc_पूर्णांक
 *
 * CPT Queue Misc Interrupt Register
 * These रेजिस्टरs contain the per-queue miscellaneous पूर्णांकerrupts.
 * otx_cptx_vqx_misc_पूर्णांक_s
 * Word 0
 *  reserved_5_63:59 [63:5] Reserved.
 *  swerr:1 [4:4](R/W1C/H) Software error from engines.
 *  nwrp:1  [3:3](R/W1C/H) NCB result ग_लिखो response error.
 *  irde:1  [2:2](R/W1C/H) Inकाष्ठाion NCB पढ़ो response error.
 *  करोvf:1 [1:1](R/W1C/H) Doorbell overflow.
 *  mbox:1 [0:0](R/W1C/H) PF to VF mailbox पूर्णांकerrupt. Set when
 *	CPT()_VF()_PF_MBOX(0) is written.
 *
 */
जोड़ otx_cptx_vqx_misc_पूर्णांक अणु
	u64 u;
	काष्ठा otx_cptx_vqx_misc_पूर्णांक_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_5_63:59;
		u64 swerr:1;
		u64 nwrp:1;
		u64 irde:1;
		u64 करोvf:1;
		u64 mbox:1;
#अन्यथा /* Word 0 - Little Endian */
		u64 mbox:1;
		u64 करोvf:1;
		u64 irde:1;
		u64 nwrp:1;
		u64 swerr:1;
		u64 reserved_5_63:59;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_vq#_करोne_ack
 *
 * CPT Queue Done Count Ack Registers
 * This रेजिस्टर is written by software to acknowledge पूर्णांकerrupts.
 * otx_cptx_vqx_करोne_ack_s
 * Word0
 *  reserved_20_63:44 [63:20] Reserved.
 *  करोne_ack:20 [19:0](R/W/H) Number of decrements to CPT()_VQ()_DONE[DONE].
 *	Reads CPT()_VQ()_DONE[DONE]. Written by software to acknowledge
 *	पूर्णांकerrupts. If CPT()_VQ()_DONE[DONE] is still nonzero the पूर्णांकerrupt
 *	will be re-sent अगर the conditions described in CPT()_VQ()_DONE[DONE]
 *	are satisfied.
 *
 */
जोड़ otx_cptx_vqx_करोne_ack अणु
	u64 u;
	काष्ठा otx_cptx_vqx_करोne_ack_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_20_63:44;
		u64 करोne_ack:20;
#अन्यथा /* Word 0 - Little Endian */
		u64 करोne_ack:20;
		u64 reserved_20_63:44;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_vq#_करोne
 *
 * CPT Queue Done Count Registers
 * These रेजिस्टरs contain the per-queue inकाष्ठाion करोne count.
 * cptx_vqx_करोne_s
 * Word0
 *  reserved_20_63:44 [63:20] Reserved.
 *  करोne:20 [19:0](R/W/H) Done count. When CPT_INST_S[DONEINT] set and that
 *	inकाष्ठाion completes, CPT()_VQ()_DONE[DONE] is incremented when the
 *	inकाष्ठाion finishes. Write to this field are क्रम diagnostic use only;
 *	instead software ग_लिखोs CPT()_VQ()_DONE_ACK with the number of
 *	decrements क्रम this field.
 *	Interrupts are sent as follows:
 *	* When CPT()_VQ()_DONE[DONE] = 0, then no results are pending, the
 *	पूर्णांकerrupt coalescing समयr is held to zero, and an पूर्णांकerrupt is not
 *	sent.
 *	* When CPT()_VQ()_DONE[DONE] != 0, then the पूर्णांकerrupt coalescing समयr
 *	counts. If the counter is >= CPT()_VQ()_DONE_WAIT[TIME_WAIT]*1024, or
 *	CPT()_VQ()_DONE[DONE] >= CPT()_VQ()_DONE_WAIT[NUM_WAIT], i.e. enough
 *	समय has passed or enough results have arrived, then the पूर्णांकerrupt is
 *	sent.
 *	* When CPT()_VQ()_DONE_ACK is written (or CPT()_VQ()_DONE is written
 *	but this is not typical), the पूर्णांकerrupt coalescing समयr restarts.
 *	Note after decrementing this पूर्णांकerrupt equation is recomputed,
 *	क्रम example अगर CPT()_VQ()_DONE[DONE] >= CPT()_VQ()_DONE_WAIT[NUM_WAIT]
 *	and because the समयr is zero, the पूर्णांकerrupt will be resent immediately.
 *	(This covers the race हाल between software acknowledging an पूर्णांकerrupt
 *	and a result वापसing.)
 *	* When CPT()_VQ()_DONE_ENA_W1S[DONE] = 0, पूर्णांकerrupts are not sent,
 *	but the counting described above still occurs.
 *	Since CPT inकाष्ठाions complete out-of-order, अगर software is using
 *	completion पूर्णांकerrupts the suggested scheme is to request a DONEINT on
 *	each request, and when an पूर्णांकerrupt arrives perक्रमm a "greedy" scan क्रम
 *	completions; even अगर a later command is acknowledged first this will
 *	not result in missing a completion.
 *	Software is responsible क्रम making sure [DONE] करोes not overflow;
 *	क्रम example by insuring there are not more than 2^20-1 inकाष्ठाions in
 *	flight that may request पूर्णांकerrupts.
 *
 */
जोड़ otx_cptx_vqx_करोne अणु
	u64 u;
	काष्ठा otx_cptx_vqx_करोne_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_20_63:44;
		u64 करोne:20;
#अन्यथा /* Word 0 - Little Endian */
		u64 करोne:20;
		u64 reserved_20_63:44;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_vq#_करोne_रुको
 *
 * CPT Queue Done Interrupt Coalescing Wait Registers
 * Specअगरies the per queue पूर्णांकerrupt coalescing settings.
 * cptx_vqx_करोne_रुको_s
 * Word0
 *  reserved_48_63:16 [63:48] Reserved.
 *  समय_रुको:16; [47:32](R/W) Time hold-off. When CPT()_VQ()_DONE[DONE] = 0
 *	or CPT()_VQ()_DONE_ACK is written a समयr is cleared. When the समयr
 *	reaches [TIME_WAIT]*1024 then पूर्णांकerrupt coalescing ends.
 *	see CPT()_VQ()_DONE[DONE]. If 0x0, समय coalescing is disabled.
 *  reserved_20_31:12 [31:20] Reserved.
 *  num_रुको:20 [19:0](R/W) Number of messages hold-off.
 *	When CPT()_VQ()_DONE[DONE] >= [NUM_WAIT] then पूर्णांकerrupt coalescing ends
 *	see CPT()_VQ()_DONE[DONE]. If 0x0, same behavior as 0x1.
 *
 */
जोड़ otx_cptx_vqx_करोne_रुको अणु
	u64 u;
	काष्ठा otx_cptx_vqx_करोne_रुको_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_48_63:16;
		u64 समय_रुको:16;
		u64 reserved_20_31:12;
		u64 num_रुको:20;
#अन्यथा /* Word 0 - Little Endian */
		u64 num_रुको:20;
		u64 reserved_20_31:12;
		u64 समय_रुको:16;
		u64 reserved_48_63:16;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_vq#_करोne_ena_w1s
 *
 * CPT Queue Done Interrupt Enable Set Registers
 * Write 1 to these रेजिस्टरs will enable the DONEINT पूर्णांकerrupt क्रम the queue.
 * cptx_vqx_करोne_ena_w1s_s
 * Word0
 *  reserved_1_63:63 [63:1] Reserved.
 *  करोne:1 [0:0](R/W1S/H) Write 1 will enable DONEINT क्रम this queue.
 *	Write 0 has no effect. Read will वापस the enable bit.
 */
जोड़ otx_cptx_vqx_करोne_ena_w1s अणु
	u64 u;
	काष्ठा otx_cptx_vqx_करोne_ena_w1s_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_1_63:63;
		u64 करोne:1;
#अन्यथा /* Word 0 - Little Endian */
		u64 करोne:1;
		u64 reserved_1_63:63;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Register (NCB) otx_cpt#_vq#_ctl
 *
 * CPT VF Queue Control Registers
 * This रेजिस्टर configures queues. This रेजिस्टर should be changed (other than
 * clearing [ENA]) only when quiescent (see CPT()_VQ()_INPROG[INFLIGHT]).
 * cptx_vqx_ctl_s
 * Word0
 *  reserved_1_63:63 [63:1] Reserved.
 *  ena:1 [0:0](R/W/H) Enables the logical inकाष्ठाion queue.
 *	See also CPT()_PF_Q()_CTL[CONT_ERR] and	CPT()_VQ()_INPROG[INFLIGHT].
 *	1 = Queue is enabled.
 *	0 = Queue is disabled.
 */
जोड़ otx_cptx_vqx_ctl अणु
	u64 u;
	काष्ठा otx_cptx_vqx_ctl_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		u64 reserved_1_63:63;
		u64 ena:1;
#अन्यथा /* Word 0 - Little Endian */
		u64 ena:1;
		u64 reserved_1_63:63;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

/*
 * Error Address/Error Codes
 *
 * In the event of a severe error, microcode ग_लिखोs an 8-byte Error Code
 * value (ECODE) to host memory at the Rptr address specअगरied by the host
 * प्रणाली (in the 64-byte request).
 *
 * Word0
 *  [63:56](R) 8-bit completion code
 *  [55:48](R) Number of the core that reported the severe error
 *  [47:0] Lower 6 bytes of M-Inst word2. Used to assist in uniquely
 *  identअगरying which specअगरic inकाष्ठाion caused the error. This assumes
 *  that each inकाष्ठाion has a unique result location (RPTR), at least
 *  क्रम a given period of समय.
 */
जोड़ otx_cpt_error_code अणु
	u64 u;
	काष्ठा otx_cpt_error_code_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD) /* Word 0 - Big Endian */
		uपूर्णांक64_t ccode:8;
		uपूर्णांक64_t coreid:8;
		uपूर्णांक64_t rptr6:48;
#अन्यथा /* Word 0 - Little Endian */
		uपूर्णांक64_t rptr6:48;
		uपूर्णांक64_t coreid:8;
		uपूर्णांक64_t ccode:8;
#पूर्ण_अगर /* Word 0 - End */
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर /*__OTX_CPT_HW_TYPES_H */
