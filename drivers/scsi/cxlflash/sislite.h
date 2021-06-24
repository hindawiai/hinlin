<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CXL Flash Device Driver
 *
 * Written by: Manoj N. Kumar <manoj@linux.vnet.ibm.com>, IBM Corporation
 *             Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2015 IBM Corporation
 */

#अगर_अघोषित _SISLITE_H
#घोषणा _SISLITE_H

#समावेश <linux/types.h>

प्रकार u16 ctx_hndl_t;
प्रकार u32 res_hndl_t;

#घोषणा SIZE_4K		4096
#घोषणा SIZE_64K	65536

/*
 * IOARCB: 64 bytes, min 16 byte alignment required, host native endianness
 * except क्रम SCSI CDB which reमुख्यs big endian per SCSI standards.
 */
काष्ठा sisl_ioarcb अणु
	u16 ctx_id;		/* ctx_hndl_t */
	u16 req_flags;
#घोषणा SISL_REQ_FLAGS_RES_HNDL       0x8000U	/* bit 0 (MSB) */
#घोषणा SISL_REQ_FLAGS_PORT_LUN_ID    0x0000U

#घोषणा SISL_REQ_FLAGS_SUP_UNDERRUN   0x4000U	/* bit 1 */

#घोषणा SISL_REQ_FLAGS_TIMEOUT_SECS   0x0000U	/* bits 8,9 */
#घोषणा SISL_REQ_FLAGS_TIMEOUT_MSECS  0x0040U
#घोषणा SISL_REQ_FLAGS_TIMEOUT_USECS  0x0080U
#घोषणा SISL_REQ_FLAGS_TIMEOUT_CYCLES 0x00C0U

#घोषणा SISL_REQ_FLAGS_TMF_CMD        0x0004u	/* bit 13 */

#घोषणा SISL_REQ_FLAGS_AFU_CMD        0x0002U	/* bit 14 */

#घोषणा SISL_REQ_FLAGS_HOST_WRITE     0x0001U	/* bit 15 (LSB) */
#घोषणा SISL_REQ_FLAGS_HOST_READ      0x0000U

	जोड़ अणु
		u32 res_hndl;	/* res_hndl_t */
		u32 port_sel;	/* this is a selection mask:
				 * 0x1 -> port#0 can be selected,
				 * 0x2 -> port#1 can be selected.
				 * Can be bitwise ORed.
				 */
	पूर्ण;
	u64 lun_id;
	u32 data_len;		/* 4K क्रम पढ़ो/ग_लिखो */
	u32 ioadl_len;
	जोड़ अणु
		u64 data_ea;	/* min 16 byte aligned */
		u64 ioadl_ea;
	पूर्ण;
	u8 msi;			/* LISN to send on RRQ ग_लिखो */
#घोषणा SISL_MSI_CXL_PFAULT        0	/* reserved क्रम CXL page faults */
#घोषणा SISL_MSI_SYNC_ERROR        1	/* recommended क्रम AFU sync error */
#घोषणा SISL_MSI_RRQ_UPDATED       2	/* recommended क्रम IO completion */
#घोषणा SISL_MSI_ASYNC_ERROR       3	/* master only - क्रम AFU async error */

	u8 rrq;			/* 0 क्रम a single RRQ */
	u16 समयout;		/* in units specअगरied by req_flags */
	u32 rsvd1;
	u8 cdb[16];		/* must be in big endian */
#घोषणा SISL_AFU_CMD_SYNC		0xC0	/* AFU sync command */
#घोषणा SISL_AFU_CMD_LUN_PROVISION	0xD0	/* AFU LUN provision command */
#घोषणा SISL_AFU_CMD_DEBUG		0xE0	/* AFU debug command */

#घोषणा SISL_AFU_LUN_PROVISION_CREATE	0x00	/* LUN provision create type */
#घोषणा SISL_AFU_LUN_PROVISION_DELETE	0x01	/* LUN provision delete type */

	जोड़ अणु
		u64 reserved;			/* Reserved क्रम IOARRIN mode */
		काष्ठा sisl_ioasa *ioasa;	/* IOASA EA क्रम SQ Mode */
	पूर्ण;
पूर्ण __packed;

काष्ठा sisl_rc अणु
	u8 flags;
#घोषणा SISL_RC_FLAGS_SENSE_VALID         0x80U
#घोषणा SISL_RC_FLAGS_FCP_RSP_CODE_VALID  0x40U
#घोषणा SISL_RC_FLAGS_OVERRUN             0x20U
#घोषणा SISL_RC_FLAGS_UNDERRUN            0x10U

	u8 afu_rc;
#घोषणा SISL_AFU_RC_RHT_INVALID           0x01U	/* user error */
#घोषणा SISL_AFU_RC_RHT_UNALIGNED         0x02U	/* should never happen */
#घोषणा SISL_AFU_RC_RHT_OUT_OF_BOUNDS     0x03u	/* user error */
#घोषणा SISL_AFU_RC_RHT_DMA_ERR           0x04u	/* see afu_extra
						 * may retry अगर afu_retry is off
						 * possible on master निकास
						 */
#घोषणा SISL_AFU_RC_RHT_RW_PERM           0x05u	/* no RW perms, user error */
#घोषणा SISL_AFU_RC_LXT_UNALIGNED         0x12U	/* should never happen */
#घोषणा SISL_AFU_RC_LXT_OUT_OF_BOUNDS     0x13u	/* user error */
#घोषणा SISL_AFU_RC_LXT_DMA_ERR           0x14u	/* see afu_extra
						 * may retry अगर afu_retry is off
						 * possible on master निकास
						 */
#घोषणा SISL_AFU_RC_LXT_RW_PERM           0x15u	/* no RW perms, user error */

#घोषणा SISL_AFU_RC_NOT_XLATE_HOST        0x1au	/* possible अगर master निकासed */

	/* NO_CHANNELS means the FC ports selected by dest_port in
	 * IOARCB or in the LXT entry are करोwn when the AFU tried to select
	 * a FC port. If the port went करोwn on an active IO, it will set
	 * fc_rc to =0x54(NOLOGI) or 0x57(LINKDOWN) instead.
	 */
#घोषणा SISL_AFU_RC_NO_CHANNELS           0x20U	/* see afu_extra, may retry */
#घोषणा SISL_AFU_RC_CAP_VIOLATION         0x21U	/* either user error or
						 * afu reset/master restart
						 */
#घोषणा SISL_AFU_RC_OUT_OF_DATA_BUFS      0x30U	/* always retry */
#घोषणा SISL_AFU_RC_DATA_DMA_ERR          0x31U	/* see afu_extra
						 * may retry अगर afu_retry is off
						 */

	u8 scsi_rc;		/* SCSI status byte, retry as appropriate */
#घोषणा SISL_SCSI_RC_CHECK                0x02U
#घोषणा SISL_SCSI_RC_BUSY                 0x08u

	u8 fc_rc;		/* retry */
	/*
	 * We should only see fc_rc=0x57 (LINKDOWN) or 0x54(NOLOGI) क्रम
	 * commands that are in flight when a link goes करोwn or is logged out.
	 * If the link is करोwn or logged out beक्रमe AFU selects the port, either
	 * it will choose the other port or we will get afu_rc=0x20 (no_channel)
	 * अगर there is no valid port to use.
	 *
	 * ABORTPEND/ABORTOK/ABORTFAIL/TGTABORT can be retried, typically these
	 * would happen अगर a frame is dropped and something बार out.
	 * NOLOGI or LINKDOWN can be retried अगर the other port is up.
	 * RESIDERR can be retried as well.
	 *
	 * ABORTFAIL might indicate that lots of frames are getting CRC errors.
	 * So it maybe retried once and reset the link अगर it happens again.
	 * The link can also be reset on the CRC error threshold पूर्णांकerrupt.
	 */
#घोषणा SISL_FC_RC_ABORTPEND	0x52	/* exchange समयout or पात request */
#घोषणा SISL_FC_RC_WRABORTPEND	0x53	/* due to ग_लिखो XFER_RDY invalid */
#घोषणा SISL_FC_RC_NOLOGI	0x54	/* port not logged in, in-flight cmds */
#घोषणा SISL_FC_RC_NOEXP	0x55	/* FC protocol error or HW bug */
#घोषणा SISL_FC_RC_INUSE	0x56	/* tag alपढ़ोy in use, HW bug */
#घोषणा SISL_FC_RC_LINKDOWN	0x57	/* link करोwn, in-flight cmds */
#घोषणा SISL_FC_RC_ABORTOK	0x58	/* pending पात completed w/success */
#घोषणा SISL_FC_RC_ABORTFAIL	0x59	/* pending पात completed w/fail */
#घोषणा SISL_FC_RC_RESID	0x5A	/* ioasa underrun/overrun flags set */
#घोषणा SISL_FC_RC_RESIDERR	0x5B	/* actual data len करोes not match SCSI
					 * reported len, possibly due to dropped
					 * frames
					 */
#घोषणा SISL_FC_RC_TGTABORT	0x5C	/* command पातed by target */
पूर्ण;

#घोषणा SISL_SENSE_DATA_LEN     20	/* Sense data length         */
#घोषणा SISL_WWID_DATA_LEN	16	/* WWID data length          */

/*
 * IOASA: 64 bytes & must follow IOARCB, min 16 byte alignment required,
 * host native endianness
 */
काष्ठा sisl_ioasa अणु
	जोड़ अणु
		काष्ठा sisl_rc rc;
		u32 ioasc;
#घोषणा SISL_IOASC_GOOD_COMPLETION        0x00000000U
	पूर्ण;

	जोड़ अणु
		u32 resid;
		u32 lunid_hi;
	पूर्ण;

	u8 port;
	u8 afu_extra;
	/* when afu_rc=0x04, 0x14, 0x31 (_xxx_DMA_ERR):
	 * afu_exta contains PSL response code. Useful codes are:
	 */
#घोषणा SISL_AFU_DMA_ERR_PAGE_IN	0x0A	/* AFU_retry_on_pagein Action
						 *  Enabled            N/A
						 *  Disabled           retry
						 */
#घोषणा SISL_AFU_DMA_ERR_INVALID_EA	0x0B	/* this is a hard error
						 * afu_rc	Implies
						 * 0x04, 0x14	master निकास.
						 * 0x31         user error.
						 */
	/* when afu rc=0x20 (no channels):
	 * afu_extra bits [4:5]: available porपंचांगask,  [6:7]: requested porपंचांगask.
	 */
#घोषणा SISL_AFU_NO_CLANNELS_AMASK(afu_extra) (((afu_extra) & 0x0C) >> 2)
#घोषणा SISL_AFU_NO_CLANNELS_RMASK(afu_extra) ((afu_extra) & 0x03)

	u8 scsi_extra;
	u8 fc_extra;

	जोड़ अणु
		u8 sense_data[SISL_SENSE_DATA_LEN];
		काष्ठा अणु
			u32 lunid_lo;
			u8 wwid[SISL_WWID_DATA_LEN];
		पूर्ण;
	पूर्ण;

	/* These fields are defined by the SISlite architecture क्रम the
	 * host to use as they see fit क्रम their implementation.
	 */
	जोड़ अणु
		u64 host_use[4];
		u8 host_use_b[32];
	पूर्ण;
पूर्ण __packed;

#घोषणा SISL_RESP_HANDLE_T_BIT        0x1ULL	/* Toggle bit */

/* MMIO space is required to support only 64-bit access */

/*
 * This AFU has two mechanisms to deal with endian-ness.
 * One is a global configuration (in the afu_config) रेजिस्टर
 * below that specअगरies the endian-ness of the host.
 * The other is a per context (i.e. application) specअगरication
 * controlled by the endian_ctrl field here. Since the master
 * context is one such application the master context's
 * endian-ness is set to be the same as the host.
 *
 * As per the SISlite spec, the MMIO रेजिस्टरs are always
 * big endian.
 */
#घोषणा SISL_ENDIAN_CTRL_BE           0x8000000000000080ULL
#घोषणा SISL_ENDIAN_CTRL_LE           0x0000000000000000ULL

#अगर_घोषित __BIG_ENDIAN
#घोषणा SISL_ENDIAN_CTRL              SISL_ENDIAN_CTRL_BE
#अन्यथा
#घोषणा SISL_ENDIAN_CTRL              SISL_ENDIAN_CTRL_LE
#पूर्ण_अगर

/* per context host transport MMIO  */
काष्ठा sisl_host_map अणु
	__be64 endian_ctrl;	/* Per context Endian Control. The AFU will
				 * operate on whatever the context is of the
				 * host application.
				 */

	__be64 पूर्णांकr_status;	/* this sends LISN# programmed in ctx_ctrl.
				 * Only recovery in a PERM_ERR is a context
				 * निकास since there is no way to tell which
				 * command caused the error.
				 */
#घोषणा SISL_ISTATUS_PERM_ERR_LISN_3_EA		0x0400ULL /* b53, user error */
#घोषणा SISL_ISTATUS_PERM_ERR_LISN_2_EA		0x0200ULL /* b54, user error */
#घोषणा SISL_ISTATUS_PERM_ERR_LISN_1_EA		0x0100ULL /* b55, user error */
#घोषणा SISL_ISTATUS_PERM_ERR_LISN_3_PASID	0x0080ULL /* b56, user error */
#घोषणा SISL_ISTATUS_PERM_ERR_LISN_2_PASID	0x0040ULL /* b57, user error */
#घोषणा SISL_ISTATUS_PERM_ERR_LISN_1_PASID	0x0020ULL /* b58, user error */
#घोषणा SISL_ISTATUS_PERM_ERR_CMDROOM		0x0010ULL /* b59, user error */
#घोषणा SISL_ISTATUS_PERM_ERR_RCB_READ		0x0008ULL /* b60, user error */
#घोषणा SISL_ISTATUS_PERM_ERR_SA_WRITE		0x0004ULL /* b61, user error */
#घोषणा SISL_ISTATUS_PERM_ERR_RRQ_WRITE		0x0002ULL /* b62, user error */
	/* Page in रुको accessing RCB/IOASA/RRQ is reported in b63.
	 * Same error in data/LXT/RHT access is reported via IOASA.
	 */
#घोषणा SISL_ISTATUS_TEMP_ERR_PAGEIN		0x0001ULL /* b63, can only be
							   * generated when AFU
							   * स्वतः retry is
							   * disabled. If user
							   * can determine the
							   * command that caused
							   * the error, it can
							   * be retried.
							   */
#घोषणा SISL_ISTATUS_UNMASK	(0x07FFULL)		/* 1 means unmasked */
#घोषणा SISL_ISTATUS_MASK	~(SISL_ISTATUS_UNMASK)	/* 1 means masked */

	__be64 पूर्णांकr_clear;
	__be64 पूर्णांकr_mask;
	__be64 ioarrin;		/* only ग_लिखो what cmd_room permits */
	__be64 rrq_start;	/* start & end are both inclusive */
	__be64 rrq_end;		/* ग_लिखो sequence: start followed by end */
	__be64 cmd_room;
	__be64 ctx_ctrl;	/* least signअगरicant byte or b56:63 is LISN# */
#घोषणा SISL_CTX_CTRL_UNMAP_SECTOR	0x8000000000000000ULL /* b0 */
#घोषणा SISL_CTX_CTRL_LISN_MASK		(0xFFULL)
	__be64 mbox_w;		/* restricted use */
	__be64 sq_start;	/* Submission Queue (R/W): ग_लिखो sequence and */
	__be64 sq_end;		/* inclusion semantics are the same as RRQ    */
	__be64 sq_head;		/* Submission Queue Head (R): क्रम debugging   */
	__be64 sq_tail;		/* Submission Queue TAIL (R/W): next IOARCB   */
	__be64 sq_ctx_reset;	/* Submission Queue Context Reset (R/W)	      */
पूर्ण;

/* per context provisioning & control MMIO */
काष्ठा sisl_ctrl_map अणु
	__be64 rht_start;
	__be64 rht_cnt_id;
	/* both cnt & ctx_id args must be ULL */
#घोषणा SISL_RHT_CNT_ID(cnt, ctx_id)  (((cnt) << 48) | ((ctx_id) << 32))

	__be64 ctx_cap;	/* afu_rc below is when the capability is violated */
#घोषणा SISL_CTX_CAP_PROXY_ISSUE       0x8000000000000000ULL /* afu_rc 0x21 */
#घोषणा SISL_CTX_CAP_REAL_MODE         0x4000000000000000ULL /* afu_rc 0x21 */
#घोषणा SISL_CTX_CAP_HOST_XLATE        0x2000000000000000ULL /* afu_rc 0x1a */
#घोषणा SISL_CTX_CAP_PROXY_TARGET      0x1000000000000000ULL /* afu_rc 0x21 */
#घोषणा SISL_CTX_CAP_AFU_CMD           0x0000000000000008ULL /* afu_rc 0x21 */
#घोषणा SISL_CTX_CAP_GSCSI_CMD         0x0000000000000004ULL /* afu_rc 0x21 */
#घोषणा SISL_CTX_CAP_WRITE_CMD         0x0000000000000002ULL /* afu_rc 0x21 */
#घोषणा SISL_CTX_CAP_READ_CMD          0x0000000000000001ULL /* afu_rc 0x21 */
	__be64 mbox_r;
	__be64 lisn_pasid[2];
	/* pasid _a arg must be ULL */
#घोषणा SISL_LISN_PASID(_a, _b)	(((_a) << 32) | (_b))
	__be64 lisn_ea[3];
पूर्ण;

/* single copy global regs */
काष्ठा sisl_global_regs अणु
	__be64 aपूर्णांकr_status;
	/*
	 * In cxlflash, FC port/link are arranged in port pairs, each
	 * माला_लो a byte of status:
	 *
	 *	*_OTHER:	other err, FC_ERRCAP[31:20]
	 *	*_LOGO:		target sent FLOGI/PLOGI/LOGO जबतक logged in
	 *	*_CRC_T:	CRC threshold exceeded
	 *	*_LOGI_R:	login state machine समयd out and retrying
	 *	*_LOGI_F:	login failed, FC_ERROR[19:0]
	 *	*_LOGI_S:	login succeeded
	 *	*_LINK_DN:	link online to offline
	 *	*_LINK_UP:	link offline to online
	 */
#घोषणा SISL_ASTATUS_FC2_OTHER	 0x80000000ULL /* b32 */
#घोषणा SISL_ASTATUS_FC2_LOGO    0x40000000ULL /* b33 */
#घोषणा SISL_ASTATUS_FC2_CRC_T   0x20000000ULL /* b34 */
#घोषणा SISL_ASTATUS_FC2_LOGI_R  0x10000000ULL /* b35 */
#घोषणा SISL_ASTATUS_FC2_LOGI_F  0x08000000ULL /* b36 */
#घोषणा SISL_ASTATUS_FC2_LOGI_S  0x04000000ULL /* b37 */
#घोषणा SISL_ASTATUS_FC2_LINK_DN 0x02000000ULL /* b38 */
#घोषणा SISL_ASTATUS_FC2_LINK_UP 0x01000000ULL /* b39 */

#घोषणा SISL_ASTATUS_FC3_OTHER   0x00800000ULL /* b40 */
#घोषणा SISL_ASTATUS_FC3_LOGO    0x00400000ULL /* b41 */
#घोषणा SISL_ASTATUS_FC3_CRC_T   0x00200000ULL /* b42 */
#घोषणा SISL_ASTATUS_FC3_LOGI_R  0x00100000ULL /* b43 */
#घोषणा SISL_ASTATUS_FC3_LOGI_F  0x00080000ULL /* b44 */
#घोषणा SISL_ASTATUS_FC3_LOGI_S  0x00040000ULL /* b45 */
#घोषणा SISL_ASTATUS_FC3_LINK_DN 0x00020000ULL /* b46 */
#घोषणा SISL_ASTATUS_FC3_LINK_UP 0x00010000ULL /* b47 */

#घोषणा SISL_ASTATUS_FC0_OTHER	 0x00008000ULL /* b48 */
#घोषणा SISL_ASTATUS_FC0_LOGO    0x00004000ULL /* b49 */
#घोषणा SISL_ASTATUS_FC0_CRC_T   0x00002000ULL /* b50 */
#घोषणा SISL_ASTATUS_FC0_LOGI_R  0x00001000ULL /* b51 */
#घोषणा SISL_ASTATUS_FC0_LOGI_F  0x00000800ULL /* b52 */
#घोषणा SISL_ASTATUS_FC0_LOGI_S  0x00000400ULL /* b53 */
#घोषणा SISL_ASTATUS_FC0_LINK_DN 0x00000200ULL /* b54 */
#घोषणा SISL_ASTATUS_FC0_LINK_UP 0x00000100ULL /* b55 */

#घोषणा SISL_ASTATUS_FC1_OTHER   0x00000080ULL /* b56 */
#घोषणा SISL_ASTATUS_FC1_LOGO    0x00000040ULL /* b57 */
#घोषणा SISL_ASTATUS_FC1_CRC_T   0x00000020ULL /* b58 */
#घोषणा SISL_ASTATUS_FC1_LOGI_R  0x00000010ULL /* b59 */
#घोषणा SISL_ASTATUS_FC1_LOGI_F  0x00000008ULL /* b60 */
#घोषणा SISL_ASTATUS_FC1_LOGI_S  0x00000004ULL /* b61 */
#घोषणा SISL_ASTATUS_FC1_LINK_DN 0x00000002ULL /* b62 */
#घोषणा SISL_ASTATUS_FC1_LINK_UP 0x00000001ULL /* b63 */

#घोषणा SISL_FC_INTERNAL_UNMASK	0x0000000300000000ULL	/* 1 means unmasked */
#घोषणा SISL_FC_INTERNAL_MASK	~(SISL_FC_INTERNAL_UNMASK)
#घोषणा SISL_FC_INTERNAL_SHIFT	32

#घोषणा SISL_FC_SHUTDOWN_NORMAL		0x0000000000000010ULL
#घोषणा SISL_FC_SHUTDOWN_ABRUPT		0x0000000000000020ULL

#घोषणा SISL_STATUS_SHUTDOWN_ACTIVE	0x0000000000000010ULL
#घोषणा SISL_STATUS_SHUTDOWN_COMPLETE	0x0000000000000020ULL

#घोषणा SISL_ASTATUS_UNMASK	0xFFFFFFFFULL		/* 1 means unmasked */
#घोषणा SISL_ASTATUS_MASK	~(SISL_ASTATUS_UNMASK)	/* 1 means masked */

	__be64 aपूर्णांकr_clear;
	__be64 aपूर्णांकr_mask;
	__be64 afu_ctrl;
	__be64 afu_hb;
	__be64 afu_scratch_pad;
	__be64 afu_port_sel;
#घोषणा SISL_AFUCONF_AR_IOARCB	0x4000ULL
#घोषणा SISL_AFUCONF_AR_LXT	0x2000ULL
#घोषणा SISL_AFUCONF_AR_RHT	0x1000ULL
#घोषणा SISL_AFUCONF_AR_DATA	0x0800ULL
#घोषणा SISL_AFUCONF_AR_RSRC	0x0400ULL
#घोषणा SISL_AFUCONF_AR_IOASA	0x0200ULL
#घोषणा SISL_AFUCONF_AR_RRQ	0x0100ULL
/* Aggregate all Auto Retry Bits */
#घोषणा SISL_AFUCONF_AR_ALL	(SISL_AFUCONF_AR_IOARCB|SISL_AFUCONF_AR_LXT| \
				 SISL_AFUCONF_AR_RHT|SISL_AFUCONF_AR_DATA|   \
				 SISL_AFUCONF_AR_RSRC|SISL_AFUCONF_AR_IOASA| \
				 SISL_AFUCONF_AR_RRQ)
#अगर_घोषित __BIG_ENDIAN
#घोषणा SISL_AFUCONF_ENDIAN            0x0000ULL
#अन्यथा
#घोषणा SISL_AFUCONF_ENDIAN            0x0020ULL
#पूर्ण_अगर
#घोषणा SISL_AFUCONF_MBOX_CLR_READ     0x0010ULL
	__be64 afu_config;
	__be64 rsvd[0xf8];
	__le64 afu_version;
	__be64 पूर्णांकerface_version;
#घोषणा SISL_INTVER_CAP_SHIFT			16
#घोषणा SISL_INTVER_MAJ_SHIFT			8
#घोषणा SISL_INTVER_CAP_MASK			0xFFFFFFFF00000000ULL
#घोषणा SISL_INTVER_MAJ_MASK			0x00000000FFFF0000ULL
#घोषणा SISL_INTVER_MIN_MASK			0x000000000000FFFFULL
#घोषणा SISL_INTVER_CAP_IOARRIN_CMD_MODE	0x800000000000ULL
#घोषणा SISL_INTVER_CAP_SQ_CMD_MODE		0x400000000000ULL
#घोषणा SISL_INTVER_CAP_RESERVED_CMD_MODE_A	0x200000000000ULL
#घोषणा SISL_INTVER_CAP_RESERVED_CMD_MODE_B	0x100000000000ULL
#घोषणा SISL_INTVER_CAP_LUN_PROVISION		0x080000000000ULL
#घोषणा SISL_INTVER_CAP_AFU_DEBUG		0x040000000000ULL
#घोषणा SISL_INTVER_CAP_OCXL_LISN		0x020000000000ULL
पूर्ण;

#घोषणा CXLFLASH_NUM_FC_PORTS_PER_BANK	2	/* fixed # of ports per bank */
#घोषणा CXLFLASH_MAX_FC_BANKS		2	/* max # of banks supported */
#घोषणा CXLFLASH_MAX_FC_PORTS	(CXLFLASH_NUM_FC_PORTS_PER_BANK *	\
				 CXLFLASH_MAX_FC_BANKS)
#घोषणा CXLFLASH_MAX_CONTEXT	512	/* number of contexts per AFU */
#घोषणा CXLFLASH_NUM_VLUNS	512	/* number of vluns per AFU/port */
#घोषणा CXLFLASH_NUM_REGS	512	/* number of रेजिस्टरs per port */

काष्ठा fc_port_bank अणु
	__be64 fc_port_regs[CXLFLASH_NUM_FC_PORTS_PER_BANK][CXLFLASH_NUM_REGS];
	__be64 fc_port_luns[CXLFLASH_NUM_FC_PORTS_PER_BANK][CXLFLASH_NUM_VLUNS];
पूर्ण;

काष्ठा sisl_global_map अणु
	जोड़ अणु
		काष्ठा sisl_global_regs regs;
		अक्षर page0[SIZE_4K];	/* page 0 */
	पूर्ण;

	अक्षर page1[SIZE_4K];	/* page 1 */

	काष्ठा fc_port_bank bank[CXLFLASH_MAX_FC_BANKS]; /* pages 2 - 9 */

	/* pages 10 - 15 are reserved */

पूर्ण;

/*
 * CXL Flash Memory Map
 *
 *	+-------------------------------+
 *	|    512 * 64 KB User MMIO      |
 *	|        (per context)          |
 *	|       User Accessible         |
 *	+-------------------------------+
 *	|    512 * 128 B per context    |
 *	|    Provisioning and Control   |
 *	|   Trusted Process accessible  |
 *	+-------------------------------+
 *	|         64 KB Global          |
 *	|   Trusted Process accessible  |
 *	+-------------------------------+
 */
काष्ठा cxlflash_afu_map अणु
	जोड़ अणु
		काष्ठा sisl_host_map host;
		अक्षर harea[SIZE_64K];	/* 64KB each */
	पूर्ण hosts[CXLFLASH_MAX_CONTEXT];

	जोड़ अणु
		काष्ठा sisl_ctrl_map ctrl;
		अक्षर carea[cache_line_size()];	/* 128B each */
	पूर्ण ctrls[CXLFLASH_MAX_CONTEXT];

	जोड़ अणु
		काष्ठा sisl_global_map global;
		अक्षर garea[SIZE_64K];	/* 64KB single block */
	पूर्ण;
पूर्ण;

/*
 * LXT - LBA Translation Table
 * LXT control blocks
 */
काष्ठा sisl_lxt_entry अणु
	u64 rlba_base;	/* bits 0:47 is base
			 * b48:55 is lun index
			 * b58:59 is ग_लिखो & पढ़ो perms
			 * (अगर no perm, afu_rc=0x15)
			 * b60:63 is port_sel mask
			 */
पूर्ण;

/*
 * RHT - Resource Handle Table
 * Per the SISlite spec, RHT entries are to be 16-byte aligned
 */
काष्ठा sisl_rht_entry अणु
	काष्ठा sisl_lxt_entry *lxt_start;
	u32 lxt_cnt;
	u16 rsvd;
	u8 fp;			/* क्रमmat & perm nibbles.
				 * (अगर no perm, afu_rc=0x05)
				 */
	u8 nmask;
पूर्ण __packed __aligned(16);

काष्ठा sisl_rht_entry_f1 अणु
	u64 lun_id;
	जोड़ अणु
		काष्ठा अणु
			u8 valid;
			u8 rsvd[5];
			u8 fp;
			u8 port_sel;
		पूर्ण;

		u64 dw;
	पूर्ण;
पूर्ण __packed __aligned(16);

/* make the fp byte */
#घोषणा SISL_RHT_FP(fmt, perm) (((fmt) << 4) | (perm))

/* make the fp byte क्रम a clone from a source fp and clone flags
 * flags must be only 2 LSB bits.
 */
#घोषणा SISL_RHT_FP_CLONE(src_fp, cln_flags) ((src_fp) & (0xFC | (cln_flags)))

#घोषणा RHT_PERM_READ  0x01U
#घोषणा RHT_PERM_WRITE 0x02U
#घोषणा RHT_PERM_RW    (RHT_PERM_READ | RHT_PERM_WRITE)

/* extract the perm bits from a fp */
#घोषणा SISL_RHT_PERM(fp) ((fp) & RHT_PERM_RW)

#घोषणा PORT0  0x01U
#घोषणा PORT1  0x02U
#घोषणा PORT2  0x04U
#घोषणा PORT3  0x08U
#घोषणा PORT_MASK(_n)	((1 << (_n)) - 1)

/* AFU Sync Mode byte */
#घोषणा AFU_LW_SYNC 0x0U
#घोषणा AFU_HW_SYNC 0x1U
#घोषणा AFU_GSYNC   0x2U

/* Special Task Management Function CDB */
#घोषणा TMF_LUN_RESET  0x1U
#घोषणा TMF_CLEAR_ACA  0x2U

#पूर्ण_अगर /* _SISLITE_H */
