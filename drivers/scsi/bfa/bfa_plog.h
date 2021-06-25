<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */
#अगर_अघोषित __BFA_PORTLOG_H__
#घोषणा __BFA_PORTLOG_H__

#समावेश "bfa_fc.h"
#समावेश "bfa_defs.h"

#घोषणा BFA_PL_NLOG_ENTS 256
#घोषणा BFA_PL_LOG_REC_INCR(_x) ((_x)++, (_x) %= BFA_PL_NLOG_ENTS)

#घोषणा BFA_PL_STRING_LOG_SZ   32   /* number of अक्षरs in string log */
#घोषणा BFA_PL_INT_LOG_SZ      8    /* number of पूर्णांकegers in the पूर्णांकeger log */

क्रमागत bfa_plog_log_type अणु
	BFA_PL_LOG_TYPE_INVALID	= 0,
	BFA_PL_LOG_TYPE_INT	= 1,
	BFA_PL_LOG_TYPE_STRING	= 2,
पूर्ण;

/*
 * the (fixed size) record क्रमmat क्रम each entry in the portlog
 */
काष्ठा bfa_plog_rec_s अणु
	u64	tv;	/* बारtamp */
	u8	 port;	/* Source port that logged this entry */
	u8	 mid;	/* module id */
	u8	 eid;	/* indicates Rx, Tx, IOCTL, etc.  bfa_plog_eid */
	u8	 log_type; /* string/पूर्णांकeger log, bfa_plog_log_type_t */
	u8	 log_num_पूर्णांकs;
	/*
	 * पूर्णांकerpreted only अगर log_type is INT_LOG. indicates number of
	 * पूर्णांकegers in the पूर्णांक_log[] (0-PL_INT_LOG_SZ).
	 */
	u8	 rsvd;
	u16	misc;	/* can be used to indicate fc frame length */
	जोड़ अणु
		अक्षर	    string_log[BFA_PL_STRING_LOG_SZ];
		u32	पूर्णांक_log[BFA_PL_INT_LOG_SZ];
	पूर्ण log_entry;

पूर्ण;

/*
 * the following #घोषणाs will be used by the logging entities to indicate
 * their module id. BFAL will convert the पूर्णांकeger value to string क्रमmat
 *
* process to be used जबतक changing the following #घोषणाs:
 *  - Always add new entries at the end
 *  - define corresponding string in BFAL
 *  - Do not हटाओ any entry or rearrange the order.
 */
क्रमागत bfa_plog_mid अणु
	BFA_PL_MID_INVALID	= 0,
	BFA_PL_MID_DEBUG	= 1,
	BFA_PL_MID_DRVR		= 2,
	BFA_PL_MID_HAL		= 3,
	BFA_PL_MID_HAL_FCXP	= 4,
	BFA_PL_MID_HAL_UF	= 5,
	BFA_PL_MID_FCS		= 6,
	BFA_PL_MID_LPS		= 7,
	BFA_PL_MID_MAX		= 8
पूर्ण;

#घोषणा BFA_PL_MID_STRLEN    8
काष्ठा bfa_plog_mid_strings_s अणु
	अक्षर	    m_str[BFA_PL_MID_STRLEN];
पूर्ण;

/*
 * the following #घोषणाs will be used by the logging entities to indicate
 * their event type. BFAL will convert the पूर्णांकeger value to string क्रमmat
 *
* process to be used जबतक changing the following #घोषणाs:
 *  - Always add new entries at the end
 *  - define corresponding string in BFAL
 *  - Do not हटाओ any entry or rearrange the order.
 */
क्रमागत bfa_plog_eid अणु
	BFA_PL_EID_INVALID		= 0,
	BFA_PL_EID_IOC_DISABLE		= 1,
	BFA_PL_EID_IOC_ENABLE		= 2,
	BFA_PL_EID_PORT_DISABLE		= 3,
	BFA_PL_EID_PORT_ENABLE		= 4,
	BFA_PL_EID_PORT_ST_CHANGE	= 5,
	BFA_PL_EID_TX			= 6,
	BFA_PL_EID_TX_ACK1		= 7,
	BFA_PL_EID_TX_RJT		= 8,
	BFA_PL_EID_TX_BSY		= 9,
	BFA_PL_EID_RX			= 10,
	BFA_PL_EID_RX_ACK1		= 11,
	BFA_PL_EID_RX_RJT		= 12,
	BFA_PL_EID_RX_BSY		= 13,
	BFA_PL_EID_CT_IN		= 14,
	BFA_PL_EID_CT_OUT		= 15,
	BFA_PL_EID_DRIVER_START		= 16,
	BFA_PL_EID_RSCN			= 17,
	BFA_PL_EID_DEBUG		= 18,
	BFA_PL_EID_MISC			= 19,
	BFA_PL_EID_FIP_FCF_DISC		= 20,
	BFA_PL_EID_FIP_FCF_CVL		= 21,
	BFA_PL_EID_LOGIN		= 22,
	BFA_PL_EID_LOGO			= 23,
	BFA_PL_EID_TRUNK_SCN		= 24,
	BFA_PL_EID_MAX
पूर्ण;

#घोषणा BFA_PL_ENAME_STRLEN	8
काष्ठा bfa_plog_eid_strings_s अणु
	अक्षर	    e_str[BFA_PL_ENAME_STRLEN];
पूर्ण;

#घोषणा BFA_PL_SIG_LEN	8
#घोषणा BFA_PL_SIG_STR  "12pl123"

/*
 * per port circular log buffer
 */
काष्ठा bfa_plog_s अणु
	अक्षर	    plog_sig[BFA_PL_SIG_LEN];	/* Start signature */
	u8	 plog_enabled;
	u8	 rsvd[7];
	u32	ticks;
	u16	head;
	u16	tail;
	काष्ठा bfa_plog_rec_s  plog_recs[BFA_PL_NLOG_ENTS];
पूर्ण;

व्योम bfa_plog_init(काष्ठा bfa_plog_s *plog);
व्योम bfa_plog_str(काष्ठा bfa_plog_s *plog, क्रमागत bfa_plog_mid mid,
			क्रमागत bfa_plog_eid event, u16 misc, अक्षर *log_str);
व्योम bfa_plog_पूर्णांकarr(काष्ठा bfa_plog_s *plog, क्रमागत bfa_plog_mid mid,
			क्रमागत bfa_plog_eid event, u16 misc,
			u32 *पूर्णांकarr, u32 num_पूर्णांकs);
व्योम bfa_plog_fchdr(काष्ठा bfa_plog_s *plog, क्रमागत bfa_plog_mid mid,
		क्रमागत bfa_plog_eid event, u16 misc, काष्ठा fchs_s *fchdr);
व्योम bfa_plog_fchdr_and_pl(काष्ठा bfa_plog_s *plog, क्रमागत bfa_plog_mid mid,
			क्रमागत bfa_plog_eid event, u16 misc,
			काष्ठा fchs_s *fchdr, u32 pld_w0);

#पूर्ण_अगर /* __BFA_PORTLOG_H__ */
