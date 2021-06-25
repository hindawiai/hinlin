<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 *
 */

#अगर_अघोषित _MHI_INT_H
#घोषणा _MHI_INT_H

#समावेश <linux/mhi.h>

बाह्य काष्ठा bus_type mhi_bus_type;

#घोषणा MHIREGLEN (0x0)
#घोषणा MHIREGLEN_MHIREGLEN_MASK (0xFFFFFFFF)
#घोषणा MHIREGLEN_MHIREGLEN_SHIFT (0)

#घोषणा MHIVER (0x8)
#घोषणा MHIVER_MHIVER_MASK (0xFFFFFFFF)
#घोषणा MHIVER_MHIVER_SHIFT (0)

#घोषणा MHICFG (0x10)
#घोषणा MHICFG_NHWER_MASK (0xFF000000)
#घोषणा MHICFG_NHWER_SHIFT (24)
#घोषणा MHICFG_NER_MASK (0xFF0000)
#घोषणा MHICFG_NER_SHIFT (16)
#घोषणा MHICFG_NHWCH_MASK (0xFF00)
#घोषणा MHICFG_NHWCH_SHIFT (8)
#घोषणा MHICFG_NCH_MASK (0xFF)
#घोषणा MHICFG_NCH_SHIFT (0)

#घोषणा CHDBOFF (0x18)
#घोषणा CHDBOFF_CHDBOFF_MASK (0xFFFFFFFF)
#घोषणा CHDBOFF_CHDBOFF_SHIFT (0)

#घोषणा ERDBOFF (0x20)
#घोषणा ERDBOFF_ERDBOFF_MASK (0xFFFFFFFF)
#घोषणा ERDBOFF_ERDBOFF_SHIFT (0)

#घोषणा BHIOFF (0x28)
#घोषणा BHIOFF_BHIOFF_MASK (0xFFFFFFFF)
#घोषणा BHIOFF_BHIOFF_SHIFT (0)

#घोषणा BHIखातापूर्णF (0x2C)
#घोषणा BHIखातापूर्णF_BHIखातापूर्णF_MASK (0xFFFFFFFF)
#घोषणा BHIखातापूर्णF_BHIखातापूर्णF_SHIFT (0)

#घोषणा DEBUGOFF (0x30)
#घोषणा DEBUGOFF_DEBUGOFF_MASK (0xFFFFFFFF)
#घोषणा DEBUGOFF_DEBUGOFF_SHIFT (0)

#घोषणा MHICTRL (0x38)
#घोषणा MHICTRL_MHISTATE_MASK (0x0000FF00)
#घोषणा MHICTRL_MHISTATE_SHIFT (8)
#घोषणा MHICTRL_RESET_MASK (0x2)
#घोषणा MHICTRL_RESET_SHIFT (1)

#घोषणा MHISTATUS (0x48)
#घोषणा MHISTATUS_MHISTATE_MASK (0x0000FF00)
#घोषणा MHISTATUS_MHISTATE_SHIFT (8)
#घोषणा MHISTATUS_SYSERR_MASK (0x4)
#घोषणा MHISTATUS_SYSERR_SHIFT (2)
#घोषणा MHISTATUS_READY_MASK (0x1)
#घोषणा MHISTATUS_READY_SHIFT (0)

#घोषणा CCABAP_LOWER (0x58)
#घोषणा CCABAP_LOWER_CCABAP_LOWER_MASK (0xFFFFFFFF)
#घोषणा CCABAP_LOWER_CCABAP_LOWER_SHIFT (0)

#घोषणा CCABAP_HIGHER (0x5C)
#घोषणा CCABAP_HIGHER_CCABAP_HIGHER_MASK (0xFFFFFFFF)
#घोषणा CCABAP_HIGHER_CCABAP_HIGHER_SHIFT (0)

#घोषणा ECABAP_LOWER (0x60)
#घोषणा ECABAP_LOWER_ECABAP_LOWER_MASK (0xFFFFFFFF)
#घोषणा ECABAP_LOWER_ECABAP_LOWER_SHIFT (0)

#घोषणा ECABAP_HIGHER (0x64)
#घोषणा ECABAP_HIGHER_ECABAP_HIGHER_MASK (0xFFFFFFFF)
#घोषणा ECABAP_HIGHER_ECABAP_HIGHER_SHIFT (0)

#घोषणा CRCBAP_LOWER (0x68)
#घोषणा CRCBAP_LOWER_CRCBAP_LOWER_MASK (0xFFFFFFFF)
#घोषणा CRCBAP_LOWER_CRCBAP_LOWER_SHIFT (0)

#घोषणा CRCBAP_HIGHER (0x6C)
#घोषणा CRCBAP_HIGHER_CRCBAP_HIGHER_MASK (0xFFFFFFFF)
#घोषणा CRCBAP_HIGHER_CRCBAP_HIGHER_SHIFT (0)

#घोषणा CRDB_LOWER (0x70)
#घोषणा CRDB_LOWER_CRDB_LOWER_MASK (0xFFFFFFFF)
#घोषणा CRDB_LOWER_CRDB_LOWER_SHIFT (0)

#घोषणा CRDB_HIGHER (0x74)
#घोषणा CRDB_HIGHER_CRDB_HIGHER_MASK (0xFFFFFFFF)
#घोषणा CRDB_HIGHER_CRDB_HIGHER_SHIFT (0)

#घोषणा MHICTRLBASE_LOWER (0x80)
#घोषणा MHICTRLBASE_LOWER_MHICTRLBASE_LOWER_MASK (0xFFFFFFFF)
#घोषणा MHICTRLBASE_LOWER_MHICTRLBASE_LOWER_SHIFT (0)

#घोषणा MHICTRLBASE_HIGHER (0x84)
#घोषणा MHICTRLBASE_HIGHER_MHICTRLBASE_HIGHER_MASK (0xFFFFFFFF)
#घोषणा MHICTRLBASE_HIGHER_MHICTRLBASE_HIGHER_SHIFT (0)

#घोषणा MHICTRLLIMIT_LOWER (0x88)
#घोषणा MHICTRLLIMIT_LOWER_MHICTRLLIMIT_LOWER_MASK (0xFFFFFFFF)
#घोषणा MHICTRLLIMIT_LOWER_MHICTRLLIMIT_LOWER_SHIFT (0)

#घोषणा MHICTRLLIMIT_HIGHER (0x8C)
#घोषणा MHICTRLLIMIT_HIGHER_MHICTRLLIMIT_HIGHER_MASK (0xFFFFFFFF)
#घोषणा MHICTRLLIMIT_HIGHER_MHICTRLLIMIT_HIGHER_SHIFT (0)

#घोषणा MHIDATABASE_LOWER (0x98)
#घोषणा MHIDATABASE_LOWER_MHIDATABASE_LOWER_MASK (0xFFFFFFFF)
#घोषणा MHIDATABASE_LOWER_MHIDATABASE_LOWER_SHIFT (0)

#घोषणा MHIDATABASE_HIGHER (0x9C)
#घोषणा MHIDATABASE_HIGHER_MHIDATABASE_HIGHER_MASK (0xFFFFFFFF)
#घोषणा MHIDATABASE_HIGHER_MHIDATABASE_HIGHER_SHIFT (0)

#घोषणा MHIDATALIMIT_LOWER (0xA0)
#घोषणा MHIDATALIMIT_LOWER_MHIDATALIMIT_LOWER_MASK (0xFFFFFFFF)
#घोषणा MHIDATALIMIT_LOWER_MHIDATALIMIT_LOWER_SHIFT (0)

#घोषणा MHIDATALIMIT_HIGHER (0xA4)
#घोषणा MHIDATALIMIT_HIGHER_MHIDATALIMIT_HIGHER_MASK (0xFFFFFFFF)
#घोषणा MHIDATALIMIT_HIGHER_MHIDATALIMIT_HIGHER_SHIFT (0)

/* Host request रेजिस्टर */
#घोषणा MHI_SOC_RESET_REQ_OFFSET (0xB0)
#घोषणा MHI_SOC_RESET_REQ BIT(0)

/* MHI BHI offfsets */
#घोषणा BHI_BHIVERSION_MINOR (0x00)
#घोषणा BHI_BHIVERSION_MAJOR (0x04)
#घोषणा BHI_IMGADDR_LOW (0x08)
#घोषणा BHI_IMGADDR_HIGH (0x0C)
#घोषणा BHI_IMGSIZE (0x10)
#घोषणा BHI_RSVD1 (0x14)
#घोषणा BHI_IMGTXDB (0x18)
#घोषणा BHI_TXDB_SEQNUM_BMSK (0x3FFFFFFF)
#घोषणा BHI_TXDB_SEQNUM_SHFT (0)
#घोषणा BHI_RSVD2 (0x1C)
#घोषणा BHI_INTVEC (0x20)
#घोषणा BHI_RSVD3 (0x24)
#घोषणा BHI_EXECENV (0x28)
#घोषणा BHI_STATUS (0x2C)
#घोषणा BHI_ERRCODE (0x30)
#घोषणा BHI_ERRDBG1 (0x34)
#घोषणा BHI_ERRDBG2 (0x38)
#घोषणा BHI_ERRDBG3 (0x3C)
#घोषणा BHI_SERIALNU (0x40)
#घोषणा BHI_SBLANTIROLLVER (0x44)
#घोषणा BHI_NUMSEG (0x48)
#घोषणा BHI_MSMHWID(n) (0x4C + (0x4 * (n)))
#घोषणा BHI_OEMPKHASH(n) (0x64 + (0x4 * (n)))
#घोषणा BHI_RSVD5 (0xC4)
#घोषणा BHI_STATUS_MASK (0xC0000000)
#घोषणा BHI_STATUS_SHIFT (30)
#घोषणा BHI_STATUS_ERROR (3)
#घोषणा BHI_STATUS_SUCCESS (2)
#घोषणा BHI_STATUS_RESET (0)

/* MHI BHIE offsets */
#घोषणा BHIE_MSMSOCID_OFFS (0x0000)
#घोषणा BHIE_TXVECADDR_LOW_OFFS (0x002C)
#घोषणा BHIE_TXVECADDR_HIGH_OFFS (0x0030)
#घोषणा BHIE_TXVECSIZE_OFFS (0x0034)
#घोषणा BHIE_TXVECDB_OFFS (0x003C)
#घोषणा BHIE_TXVECDB_SEQNUM_BMSK (0x3FFFFFFF)
#घोषणा BHIE_TXVECDB_SEQNUM_SHFT (0)
#घोषणा BHIE_TXVECSTATUS_OFFS (0x0044)
#घोषणा BHIE_TXVECSTATUS_SEQNUM_BMSK (0x3FFFFFFF)
#घोषणा BHIE_TXVECSTATUS_SEQNUM_SHFT (0)
#घोषणा BHIE_TXVECSTATUS_STATUS_BMSK (0xC0000000)
#घोषणा BHIE_TXVECSTATUS_STATUS_SHFT (30)
#घोषणा BHIE_TXVECSTATUS_STATUS_RESET (0x00)
#घोषणा BHIE_TXVECSTATUS_STATUS_XFER_COMPL (0x02)
#घोषणा BHIE_TXVECSTATUS_STATUS_ERROR (0x03)
#घोषणा BHIE_RXVECADDR_LOW_OFFS (0x0060)
#घोषणा BHIE_RXVECADDR_HIGH_OFFS (0x0064)
#घोषणा BHIE_RXVECSIZE_OFFS (0x0068)
#घोषणा BHIE_RXVECDB_OFFS (0x0070)
#घोषणा BHIE_RXVECDB_SEQNUM_BMSK (0x3FFFFFFF)
#घोषणा BHIE_RXVECDB_SEQNUM_SHFT (0)
#घोषणा BHIE_RXVECSTATUS_OFFS (0x0078)
#घोषणा BHIE_RXVECSTATUS_SEQNUM_BMSK (0x3FFFFFFF)
#घोषणा BHIE_RXVECSTATUS_SEQNUM_SHFT (0)
#घोषणा BHIE_RXVECSTATUS_STATUS_BMSK (0xC0000000)
#घोषणा BHIE_RXVECSTATUS_STATUS_SHFT (30)
#घोषणा BHIE_RXVECSTATUS_STATUS_RESET (0x00)
#घोषणा BHIE_RXVECSTATUS_STATUS_XFER_COMPL (0x02)
#घोषणा BHIE_RXVECSTATUS_STATUS_ERROR (0x03)

#घोषणा SOC_HW_VERSION_OFFS (0x224)
#घोषणा SOC_HW_VERSION_FAM_NUM_BMSK (0xF0000000)
#घोषणा SOC_HW_VERSION_FAM_NUM_SHFT (28)
#घोषणा SOC_HW_VERSION_DEV_NUM_BMSK (0x0FFF0000)
#घोषणा SOC_HW_VERSION_DEV_NUM_SHFT (16)
#घोषणा SOC_HW_VERSION_MAJOR_VER_BMSK (0x0000FF00)
#घोषणा SOC_HW_VERSION_MAJOR_VER_SHFT (8)
#घोषणा SOC_HW_VERSION_MINOR_VER_BMSK (0x000000FF)
#घोषणा SOC_HW_VERSION_MINOR_VER_SHFT (0)

#घोषणा EV_CTX_RESERVED_MASK GENMASK(7, 0)
#घोषणा EV_CTX_INTMODC_MASK GENMASK(15, 8)
#घोषणा EV_CTX_INTMODC_SHIFT 8
#घोषणा EV_CTX_INTMODT_MASK GENMASK(31, 16)
#घोषणा EV_CTX_INTMODT_SHIFT 16
काष्ठा mhi_event_ctxt अणु
	__u32 पूर्णांकmod;
	__u32 ertype;
	__u32 msivec;

	__u64 rbase __packed __aligned(4);
	__u64 rlen __packed __aligned(4);
	__u64 rp __packed __aligned(4);
	__u64 wp __packed __aligned(4);
पूर्ण;

#घोषणा CHAN_CTX_CHSTATE_MASK GENMASK(7, 0)
#घोषणा CHAN_CTX_CHSTATE_SHIFT 0
#घोषणा CHAN_CTX_BRSTMODE_MASK GENMASK(9, 8)
#घोषणा CHAN_CTX_BRSTMODE_SHIFT 8
#घोषणा CHAN_CTX_POLLCFG_MASK GENMASK(15, 10)
#घोषणा CHAN_CTX_POLLCFG_SHIFT 10
#घोषणा CHAN_CTX_RESERVED_MASK GENMASK(31, 16)
काष्ठा mhi_chan_ctxt अणु
	__u32 chcfg;
	__u32 chtype;
	__u32 erindex;

	__u64 rbase __packed __aligned(4);
	__u64 rlen __packed __aligned(4);
	__u64 rp __packed __aligned(4);
	__u64 wp __packed __aligned(4);
पूर्ण;

काष्ठा mhi_cmd_ctxt अणु
	__u32 reserved0;
	__u32 reserved1;
	__u32 reserved2;

	__u64 rbase __packed __aligned(4);
	__u64 rlen __packed __aligned(4);
	__u64 rp __packed __aligned(4);
	__u64 wp __packed __aligned(4);
पूर्ण;

काष्ठा mhi_ctxt अणु
	काष्ठा mhi_event_ctxt *er_ctxt;
	काष्ठा mhi_chan_ctxt *chan_ctxt;
	काष्ठा mhi_cmd_ctxt *cmd_ctxt;
	dma_addr_t er_ctxt_addr;
	dma_addr_t chan_ctxt_addr;
	dma_addr_t cmd_ctxt_addr;
पूर्ण;

काष्ठा mhi_tre अणु
	u64 ptr;
	u32 dword[2];
पूर्ण;

काष्ठा bhi_vec_entry अणु
	u64 dma_addr;
	u64 size;
पूर्ण;

क्रमागत mhi_cmd_type अणु
	MHI_CMD_NOP = 1,
	MHI_CMD_RESET_CHAN = 16,
	MHI_CMD_STOP_CHAN = 17,
	MHI_CMD_START_CHAN = 18,
पूर्ण;

/* No operation command */
#घोषणा MHI_TRE_CMD_NOOP_PTR (0)
#घोषणा MHI_TRE_CMD_NOOP_DWORD0 (0)
#घोषणा MHI_TRE_CMD_NOOP_DWORD1 (MHI_CMD_NOP << 16)

/* Channel reset command */
#घोषणा MHI_TRE_CMD_RESET_PTR (0)
#घोषणा MHI_TRE_CMD_RESET_DWORD0 (0)
#घोषणा MHI_TRE_CMD_RESET_DWORD1(chid) ((chid << 24) | \
					(MHI_CMD_RESET_CHAN << 16))

/* Channel stop command */
#घोषणा MHI_TRE_CMD_STOP_PTR (0)
#घोषणा MHI_TRE_CMD_STOP_DWORD0 (0)
#घोषणा MHI_TRE_CMD_STOP_DWORD1(chid) ((chid << 24) | \
				       (MHI_CMD_STOP_CHAN << 16))

/* Channel start command */
#घोषणा MHI_TRE_CMD_START_PTR (0)
#घोषणा MHI_TRE_CMD_START_DWORD0 (0)
#घोषणा MHI_TRE_CMD_START_DWORD1(chid) ((chid << 24) | \
					(MHI_CMD_START_CHAN << 16))

#घोषणा MHI_TRE_GET_CMD_CHID(tre) (((tre)->dword[1] >> 24) & 0xFF)
#घोषणा MHI_TRE_GET_CMD_TYPE(tre) (((tre)->dword[1] >> 16) & 0xFF)

/* Event descriptor macros */
#घोषणा MHI_TRE_EV_PTR(ptr) (ptr)
#घोषणा MHI_TRE_EV_DWORD0(code, len) ((code << 24) | len)
#घोषणा MHI_TRE_EV_DWORD1(chid, type) ((chid << 24) | (type << 16))
#घोषणा MHI_TRE_GET_EV_PTR(tre) ((tre)->ptr)
#घोषणा MHI_TRE_GET_EV_CODE(tre) (((tre)->dword[0] >> 24) & 0xFF)
#घोषणा MHI_TRE_GET_EV_LEN(tre) ((tre)->dword[0] & 0xFFFF)
#घोषणा MHI_TRE_GET_EV_CHID(tre) (((tre)->dword[1] >> 24) & 0xFF)
#घोषणा MHI_TRE_GET_EV_TYPE(tre) (((tre)->dword[1] >> 16) & 0xFF)
#घोषणा MHI_TRE_GET_EV_STATE(tre) (((tre)->dword[0] >> 24) & 0xFF)
#घोषणा MHI_TRE_GET_EV_EXECENV(tre) (((tre)->dword[0] >> 24) & 0xFF)
#घोषणा MHI_TRE_GET_EV_SEQ(tre) ((tre)->dword[0])
#घोषणा MHI_TRE_GET_EV_TIME(tre) ((tre)->ptr)
#घोषणा MHI_TRE_GET_EV_COOKIE(tre) lower_32_bits((tre)->ptr)
#घोषणा MHI_TRE_GET_EV_VEID(tre) (((tre)->dword[0] >> 16) & 0xFF)
#घोषणा MHI_TRE_GET_EV_LINKSPEED(tre) (((tre)->dword[1] >> 24) & 0xFF)
#घोषणा MHI_TRE_GET_EV_LINKWIDTH(tre) ((tre)->dword[0] & 0xFF)

/* Transfer descriptor macros */
#घोषणा MHI_TRE_DATA_PTR(ptr) (ptr)
#घोषणा MHI_TRE_DATA_DWORD0(len) (len & MHI_MAX_MTU)
#घोषणा MHI_TRE_DATA_DWORD1(bei, ieot, ieob, chain) ((2 << 16) | (bei << 10) \
	| (ieot << 9) | (ieob << 8) | chain)

/* RSC transfer descriptor macros */
#घोषणा MHI_RSCTRE_DATA_PTR(ptr, len) (((u64)len << 48) | ptr)
#घोषणा MHI_RSCTRE_DATA_DWORD0(cookie) (cookie)
#घोषणा MHI_RSCTRE_DATA_DWORD1 (MHI_PKT_TYPE_COALESCING << 16)

क्रमागत mhi_pkt_type अणु
	MHI_PKT_TYPE_INVALID = 0x0,
	MHI_PKT_TYPE_NOOP_CMD = 0x1,
	MHI_PKT_TYPE_TRANSFER = 0x2,
	MHI_PKT_TYPE_COALESCING = 0x8,
	MHI_PKT_TYPE_RESET_CHAN_CMD = 0x10,
	MHI_PKT_TYPE_STOP_CHAN_CMD = 0x11,
	MHI_PKT_TYPE_START_CHAN_CMD = 0x12,
	MHI_PKT_TYPE_STATE_CHANGE_EVENT = 0x20,
	MHI_PKT_TYPE_CMD_COMPLETION_EVENT = 0x21,
	MHI_PKT_TYPE_TX_EVENT = 0x22,
	MHI_PKT_TYPE_RSC_TX_EVENT = 0x28,
	MHI_PKT_TYPE_EE_EVENT = 0x40,
	MHI_PKT_TYPE_TSYNC_EVENT = 0x48,
	MHI_PKT_TYPE_BW_REQ_EVENT = 0x50,
	MHI_PKT_TYPE_STALE_EVENT, /* पूर्णांकernal event */
पूर्ण;

/* MHI transfer completion events */
क्रमागत mhi_ev_ccs अणु
	MHI_EV_CC_INVALID = 0x0,
	MHI_EV_CC_SUCCESS = 0x1,
	MHI_EV_CC_EOT = 0x2, /* End of transfer event */
	MHI_EV_CC_OVERFLOW = 0x3,
	MHI_EV_CC_EOB = 0x4, /* End of block event */
	MHI_EV_CC_OOB = 0x5, /* Out of block event */
	MHI_EV_CC_DB_MODE = 0x6,
	MHI_EV_CC_UNDEFINED_ERR = 0x10,
	MHI_EV_CC_BAD_TRE = 0x11,
पूर्ण;

क्रमागत mhi_ch_state अणु
	MHI_CH_STATE_DISABLED = 0x0,
	MHI_CH_STATE_ENABLED = 0x1,
	MHI_CH_STATE_RUNNING = 0x2,
	MHI_CH_STATE_SUSPENDED = 0x3,
	MHI_CH_STATE_STOP = 0x4,
	MHI_CH_STATE_ERROR = 0x5,
पूर्ण;

क्रमागत mhi_ch_state_type अणु
	MHI_CH_STATE_TYPE_RESET,
	MHI_CH_STATE_TYPE_STOP,
	MHI_CH_STATE_TYPE_START,
	MHI_CH_STATE_TYPE_MAX,
पूर्ण;

बाह्य स्थिर अक्षर * स्थिर mhi_ch_state_type_str[MHI_CH_STATE_TYPE_MAX];
#घोषणा TO_CH_STATE_TYPE_STR(state) (((state) >= MHI_CH_STATE_TYPE_MAX) ? \
				     "INVALID_STATE" : \
				     mhi_ch_state_type_str[(state)])

#घोषणा MHI_INVALID_BRSTMODE(mode) (mode != MHI_DB_BRST_DISABLE && \
				    mode != MHI_DB_BRST_ENABLE)

बाह्य स्थिर अक्षर * स्थिर mhi_ee_str[MHI_EE_MAX];
#घोषणा TO_MHI_EXEC_STR(ee) (((ee) >= MHI_EE_MAX) ? \
			     "INVALID_EE" : mhi_ee_str[ee])

#घोषणा MHI_IN_PBL(ee) (ee == MHI_EE_PBL || ee == MHI_EE_PTHRU || \
			ee == MHI_EE_EDL)

#घोषणा MHI_IN_MISSION_MODE(ee) (ee == MHI_EE_AMSS || ee == MHI_EE_WFW || \
				 ee == MHI_EE_FP)

क्रमागत dev_st_transition अणु
	DEV_ST_TRANSITION_PBL,
	DEV_ST_TRANSITION_READY,
	DEV_ST_TRANSITION_SBL,
	DEV_ST_TRANSITION_MISSION_MODE,
	DEV_ST_TRANSITION_FP,
	DEV_ST_TRANSITION_SYS_ERR,
	DEV_ST_TRANSITION_DISABLE,
	DEV_ST_TRANSITION_MAX,
पूर्ण;

बाह्य स्थिर अक्षर * स्थिर dev_state_tran_str[DEV_ST_TRANSITION_MAX];
#घोषणा TO_DEV_STATE_TRANS_STR(state) (((state) >= DEV_ST_TRANSITION_MAX) ? \
				"INVALID_STATE" : dev_state_tran_str[state])

बाह्य स्थिर अक्षर * स्थिर mhi_state_str[MHI_STATE_MAX];
#घोषणा TO_MHI_STATE_STR(state) ((state >= MHI_STATE_MAX || \
				  !mhi_state_str[state]) ? \
				"INVALID_STATE" : mhi_state_str[state])

/* पूर्णांकernal घातer states */
क्रमागत mhi_pm_state अणु
	MHI_PM_STATE_DISABLE,
	MHI_PM_STATE_POR,
	MHI_PM_STATE_M0,
	MHI_PM_STATE_M2,
	MHI_PM_STATE_M3_ENTER,
	MHI_PM_STATE_M3,
	MHI_PM_STATE_M3_EXIT,
	MHI_PM_STATE_FW_DL_ERR,
	MHI_PM_STATE_SYS_ERR_DETECT,
	MHI_PM_STATE_SYS_ERR_PROCESS,
	MHI_PM_STATE_SHUTDOWN_PROCESS,
	MHI_PM_STATE_LD_ERR_FATAL_DETECT,
	MHI_PM_STATE_MAX
पूर्ण;

#घोषणा MHI_PM_DISABLE			BIT(0)
#घोषणा MHI_PM_POR			BIT(1)
#घोषणा MHI_PM_M0			BIT(2)
#घोषणा MHI_PM_M2			BIT(3)
#घोषणा MHI_PM_M3_ENTER			BIT(4)
#घोषणा MHI_PM_M3			BIT(5)
#घोषणा MHI_PM_M3_EXIT			BIT(6)
/* firmware करोwnload failure state */
#घोषणा MHI_PM_FW_DL_ERR		BIT(7)
#घोषणा MHI_PM_SYS_ERR_DETECT		BIT(8)
#घोषणा MHI_PM_SYS_ERR_PROCESS		BIT(9)
#घोषणा MHI_PM_SHUTDOWN_PROCESS		BIT(10)
/* link not accessible */
#घोषणा MHI_PM_LD_ERR_FATAL_DETECT	BIT(11)

#घोषणा MHI_REG_ACCESS_VALID(pm_state) ((pm_state & (MHI_PM_POR | MHI_PM_M0 | \
		MHI_PM_M2 | MHI_PM_M3_ENTER | MHI_PM_M3_EXIT | \
		MHI_PM_SYS_ERR_DETECT | MHI_PM_SYS_ERR_PROCESS | \
		MHI_PM_SHUTDOWN_PROCESS | MHI_PM_FW_DL_ERR)))
#घोषणा MHI_PM_IN_ERROR_STATE(pm_state) (pm_state >= MHI_PM_FW_DL_ERR)
#घोषणा MHI_PM_IN_FATAL_STATE(pm_state) (pm_state == MHI_PM_LD_ERR_FATAL_DETECT)
#घोषणा MHI_DB_ACCESS_VALID(mhi_cntrl) (mhi_cntrl->pm_state & \
					mhi_cntrl->db_access)
#घोषणा MHI_WAKE_DB_CLEAR_VALID(pm_state) (pm_state & (MHI_PM_M0 | \
						MHI_PM_M2 | MHI_PM_M3_EXIT))
#घोषणा MHI_WAKE_DB_SET_VALID(pm_state) (pm_state & MHI_PM_M2)
#घोषणा MHI_WAKE_DB_FORCE_SET_VALID(pm_state) MHI_WAKE_DB_CLEAR_VALID(pm_state)
#घोषणा MHI_EVENT_ACCESS_INVALID(pm_state) (pm_state == MHI_PM_DISABLE || \
					    MHI_PM_IN_ERROR_STATE(pm_state))
#घोषणा MHI_PM_IN_SUSPEND_STATE(pm_state) (pm_state & \
					   (MHI_PM_M3_ENTER | MHI_PM_M3))

#घोषणा NR_OF_CMD_RINGS			1
#घोषणा CMD_EL_PER_RING			128
#घोषणा PRIMARY_CMD_RING		0
#घोषणा MHI_DEV_WAKE_DB			127
#घोषणा MHI_MAX_MTU			0xffff
#घोषणा MHI_RANDOM_U32_NONZERO(bmsk)	(pअक्रमom_u32_max(bmsk) + 1)

क्रमागत mhi_er_type अणु
	MHI_ER_TYPE_INVALID = 0x0,
	MHI_ER_TYPE_VALID = 0x1,
पूर्ण;

काष्ठा db_cfg अणु
	bool reset_req;
	bool db_mode;
	u32 pollcfg;
	क्रमागत mhi_db_brst_mode brsपंचांगode;
	dma_addr_t db_val;
	व्योम (*process_db)(काष्ठा mhi_controller *mhi_cntrl,
			   काष्ठा db_cfg *db_cfg, व्योम __iomem *io_addr,
			   dma_addr_t db_val);
पूर्ण;

काष्ठा mhi_pm_transitions अणु
	क्रमागत mhi_pm_state from_state;
	u32 to_states;
पूर्ण;

काष्ठा state_transition अणु
	काष्ठा list_head node;
	क्रमागत dev_st_transition state;
पूर्ण;

काष्ठा mhi_ring अणु
	dma_addr_t dma_handle;
	dma_addr_t iommu_base;
	u64 *ctxt_wp; /* poपूर्णांक to ctxt wp */
	व्योम *pre_aligned;
	व्योम *base;
	व्योम *rp;
	व्योम *wp;
	माप_प्रकार el_size;
	माप_प्रकार len;
	माप_प्रकार elements;
	माप_प्रकार alloc_size;
	व्योम __iomem *db_addr;
पूर्ण;

काष्ठा mhi_cmd अणु
	काष्ठा mhi_ring ring;
	spinlock_t lock;
पूर्ण;

काष्ठा mhi_buf_info अणु
	व्योम *v_addr;
	व्योम *bb_addr;
	व्योम *wp;
	व्योम *cb_buf;
	dma_addr_t p_addr;
	माप_प्रकार len;
	क्रमागत dma_data_direction dir;
	bool used; /* Indicates whether the buffer is used or not */
	bool pre_mapped; /* Alपढ़ोy pre-mapped by client */
पूर्ण;

काष्ठा mhi_event अणु
	काष्ठा mhi_controller *mhi_cntrl;
	काष्ठा mhi_chan *mhi_chan; /* dedicated to channel */
	u32 er_index;
	u32 पूर्णांकmod;
	u32 irq;
	पूर्णांक chan; /* this event ring is dedicated to a channel (optional) */
	u32 priority;
	क्रमागत mhi_er_data_type data_type;
	काष्ठा mhi_ring ring;
	काष्ठा db_cfg db_cfg;
	काष्ठा tasklet_काष्ठा task;
	spinlock_t lock;
	पूर्णांक (*process_event)(काष्ठा mhi_controller *mhi_cntrl,
			     काष्ठा mhi_event *mhi_event,
			     u32 event_quota);
	bool hw_ring;
	bool cl_manage;
	bool offload_ev; /* managed by a device driver */
पूर्ण;

काष्ठा mhi_chan अणु
	स्थिर अक्षर *name;
	/*
	 * Important: When consuming, increment tre_ring first and when
	 * releasing, decrement buf_ring first. If tre_ring has space, buf_ring
	 * is guranteed to have space so we करो not need to check both rings.
	 */
	काष्ठा mhi_ring buf_ring;
	काष्ठा mhi_ring tre_ring;
	u32 chan;
	u32 er_index;
	u32 पूर्णांकmod;
	क्रमागत mhi_ch_type type;
	क्रमागत dma_data_direction dir;
	काष्ठा db_cfg db_cfg;
	क्रमागत mhi_ch_ee_mask ee_mask;
	क्रमागत mhi_ch_state ch_state;
	क्रमागत mhi_ev_ccs ccs;
	काष्ठा mhi_device *mhi_dev;
	व्योम (*xfer_cb)(काष्ठा mhi_device *mhi_dev, काष्ठा mhi_result *result);
	काष्ठा mutex mutex;
	काष्ठा completion completion;
	rwlock_t lock;
	काष्ठा list_head node;
	bool lpm_notअगरy;
	bool configured;
	bool offload_ch;
	bool pre_alloc;
	bool wake_capable;
पूर्ण;

/* Default MHI समयout */
#घोषणा MHI_TIMEOUT_MS (1000)

/* debugfs related functions */
#अगर_घोषित CONFIG_MHI_BUS_DEBUG
व्योम mhi_create_debugfs(काष्ठा mhi_controller *mhi_cntrl);
व्योम mhi_destroy_debugfs(काष्ठा mhi_controller *mhi_cntrl);
व्योम mhi_debugfs_init(व्योम);
व्योम mhi_debugfs_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम mhi_create_debugfs(काष्ठा mhi_controller *mhi_cntrl)
अणु
पूर्ण

अटल अंतरभूत व्योम mhi_destroy_debugfs(काष्ठा mhi_controller *mhi_cntrl)
अणु
पूर्ण

अटल अंतरभूत व्योम mhi_debugfs_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम mhi_debugfs_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा mhi_device *mhi_alloc_device(काष्ठा mhi_controller *mhi_cntrl);

पूर्णांक mhi_destroy_device(काष्ठा device *dev, व्योम *data);
व्योम mhi_create_devices(काष्ठा mhi_controller *mhi_cntrl);

पूर्णांक mhi_alloc_bhie_table(काष्ठा mhi_controller *mhi_cntrl,
			 काष्ठा image_info **image_info, माप_प्रकार alloc_size);
व्योम mhi_मुक्त_bhie_table(काष्ठा mhi_controller *mhi_cntrl,
			 काष्ठा image_info *image_info);

/* Power management APIs */
क्रमागत mhi_pm_state __must_check mhi_tryset_pm_state(
					काष्ठा mhi_controller *mhi_cntrl,
					क्रमागत mhi_pm_state state);
स्थिर अक्षर *to_mhi_pm_state_str(क्रमागत mhi_pm_state state);
पूर्णांक mhi_queue_state_transition(काष्ठा mhi_controller *mhi_cntrl,
			       क्रमागत dev_st_transition state);
व्योम mhi_pm_st_worker(काष्ठा work_काष्ठा *work);
व्योम mhi_pm_sys_err_handler(काष्ठा mhi_controller *mhi_cntrl);
पूर्णांक mhi_पढ़ोy_state_transition(काष्ठा mhi_controller *mhi_cntrl);
पूर्णांक mhi_pm_m0_transition(काष्ठा mhi_controller *mhi_cntrl);
व्योम mhi_pm_m1_transition(काष्ठा mhi_controller *mhi_cntrl);
पूर्णांक mhi_pm_m3_transition(काष्ठा mhi_controller *mhi_cntrl);
पूर्णांक __mhi_device_get_sync(काष्ठा mhi_controller *mhi_cntrl);
पूर्णांक mhi_send_cmd(काष्ठा mhi_controller *mhi_cntrl, काष्ठा mhi_chan *mhi_chan,
		 क्रमागत mhi_cmd_type cmd);
पूर्णांक mhi_करोwnload_amss_image(काष्ठा mhi_controller *mhi_cntrl);
अटल अंतरभूत bool mhi_is_active(काष्ठा mhi_controller *mhi_cntrl)
अणु
	वापस (mhi_cntrl->dev_state >= MHI_STATE_M0 &&
		mhi_cntrl->dev_state <= MHI_STATE_M3_FAST);
पूर्ण

अटल अंतरभूत व्योम mhi_trigger_resume(काष्ठा mhi_controller *mhi_cntrl)
अणु
	pm_wakeup_event(&mhi_cntrl->mhi_dev->dev, 0);
	mhi_cntrl->runसमय_get(mhi_cntrl);
	mhi_cntrl->runसमय_put(mhi_cntrl);
पूर्ण

/* Register access methods */
व्योम mhi_db_brsपंचांगode(काष्ठा mhi_controller *mhi_cntrl, काष्ठा db_cfg *db_cfg,
		     व्योम __iomem *db_addr, dma_addr_t db_val);
व्योम mhi_db_brsपंचांगode_disable(काष्ठा mhi_controller *mhi_cntrl,
			     काष्ठा db_cfg *db_mode, व्योम __iomem *db_addr,
			     dma_addr_t db_val);
पूर्णांक __must_check mhi_पढ़ो_reg(काष्ठा mhi_controller *mhi_cntrl,
			      व्योम __iomem *base, u32 offset, u32 *out);
पूर्णांक __must_check mhi_पढ़ो_reg_field(काष्ठा mhi_controller *mhi_cntrl,
				    व्योम __iomem *base, u32 offset, u32 mask,
				    u32 shअगरt, u32 *out);
पूर्णांक __must_check mhi_poll_reg_field(काष्ठा mhi_controller *mhi_cntrl,
				    व्योम __iomem *base, u32 offset, u32 mask,
				    u32 shअगरt, u32 val, u32 delayus);
व्योम mhi_ग_लिखो_reg(काष्ठा mhi_controller *mhi_cntrl, व्योम __iomem *base,
		   u32 offset, u32 val);
व्योम mhi_ग_लिखो_reg_field(काष्ठा mhi_controller *mhi_cntrl, व्योम __iomem *base,
			 u32 offset, u32 mask, u32 shअगरt, u32 val);
व्योम mhi_ring_er_db(काष्ठा mhi_event *mhi_event);
व्योम mhi_ग_लिखो_db(काष्ठा mhi_controller *mhi_cntrl, व्योम __iomem *db_addr,
		  dma_addr_t db_val);
व्योम mhi_ring_cmd_db(काष्ठा mhi_controller *mhi_cntrl, काष्ठा mhi_cmd *mhi_cmd);
व्योम mhi_ring_chan_db(काष्ठा mhi_controller *mhi_cntrl,
		      काष्ठा mhi_chan *mhi_chan);

/* Initialization methods */
पूर्णांक mhi_init_mmio(काष्ठा mhi_controller *mhi_cntrl);
पूर्णांक mhi_init_dev_ctxt(काष्ठा mhi_controller *mhi_cntrl);
व्योम mhi_deinit_dev_ctxt(काष्ठा mhi_controller *mhi_cntrl);
पूर्णांक mhi_init_irq_setup(काष्ठा mhi_controller *mhi_cntrl);
व्योम mhi_deinit_मुक्त_irq(काष्ठा mhi_controller *mhi_cntrl);
व्योम mhi_rddm_prepare(काष्ठा mhi_controller *mhi_cntrl,
		      काष्ठा image_info *img_info);
व्योम mhi_fw_load_handler(काष्ठा mhi_controller *mhi_cntrl);
पूर्णांक mhi_prepare_channel(काष्ठा mhi_controller *mhi_cntrl,
			काष्ठा mhi_chan *mhi_chan);
पूर्णांक mhi_init_chan_ctxt(काष्ठा mhi_controller *mhi_cntrl,
		       काष्ठा mhi_chan *mhi_chan);
व्योम mhi_deinit_chan_ctxt(काष्ठा mhi_controller *mhi_cntrl,
			  काष्ठा mhi_chan *mhi_chan);
व्योम mhi_reset_chan(काष्ठा mhi_controller *mhi_cntrl,
		    काष्ठा mhi_chan *mhi_chan);

/* Memory allocation methods */
अटल अंतरभूत व्योम *mhi_alloc_coherent(काष्ठा mhi_controller *mhi_cntrl,
				       माप_प्रकार size,
				       dma_addr_t *dma_handle,
				       gfp_t gfp)
अणु
	व्योम *buf = dma_alloc_coherent(mhi_cntrl->cntrl_dev, size, dma_handle,
				       gfp);

	वापस buf;
पूर्ण

अटल अंतरभूत व्योम mhi_मुक्त_coherent(काष्ठा mhi_controller *mhi_cntrl,
				     माप_प्रकार size,
				     व्योम *vaddr,
				     dma_addr_t dma_handle)
अणु
	dma_मुक्त_coherent(mhi_cntrl->cntrl_dev, size, vaddr, dma_handle);
पूर्ण

/* Event processing methods */
व्योम mhi_ctrl_ev_task(अचिन्हित दीर्घ data);
व्योम mhi_ev_task(अचिन्हित दीर्घ data);
पूर्णांक mhi_process_data_event_ring(काष्ठा mhi_controller *mhi_cntrl,
				काष्ठा mhi_event *mhi_event, u32 event_quota);
पूर्णांक mhi_process_ctrl_ev_ring(काष्ठा mhi_controller *mhi_cntrl,
			     काष्ठा mhi_event *mhi_event, u32 event_quota);

/* ISR handlers */
irqवापस_t mhi_irq_handler(पूर्णांक irq_number, व्योम *dev);
irqवापस_t mhi_पूर्णांकvec_thपढ़ोed_handler(पूर्णांक irq_number, व्योम *dev);
irqवापस_t mhi_पूर्णांकvec_handler(पूर्णांक irq_number, व्योम *dev);

पूर्णांक mhi_gen_tre(काष्ठा mhi_controller *mhi_cntrl, काष्ठा mhi_chan *mhi_chan,
		काष्ठा mhi_buf_info *info, क्रमागत mhi_flags flags);
पूर्णांक mhi_map_single_no_bb(काष्ठा mhi_controller *mhi_cntrl,
			 काष्ठा mhi_buf_info *buf_info);
पूर्णांक mhi_map_single_use_bb(काष्ठा mhi_controller *mhi_cntrl,
			  काष्ठा mhi_buf_info *buf_info);
व्योम mhi_unmap_single_no_bb(काष्ठा mhi_controller *mhi_cntrl,
			    काष्ठा mhi_buf_info *buf_info);
व्योम mhi_unmap_single_use_bb(काष्ठा mhi_controller *mhi_cntrl,
			     काष्ठा mhi_buf_info *buf_info);

#पूर्ण_अगर /* _MHI_INT_H */
