<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2014-2016 Broadcom Corporation
 * Copyright (c) 2016-2018 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित BNXT_DCB_H
#घोषणा BNXT_DCB_H

#समावेश <net/dcbnl.h>

काष्ठा bnxt_dcb अणु
	u8			max_tc;
	काष्ठा ieee_pfc		*ieee_pfc;
	काष्ठा ieee_ets		*ieee_ets;
	u8			dcbx_cap;
	u8			शेष_pri;
पूर्ण;

काष्ठा bnxt_cos2bw_cfg अणु
	u8			pad[3];
	u8			queue_id;
	__le32			min_bw;
	__le32			max_bw;
#घोषणा BW_VALUE_UNIT_PERCENT1_100		(0x1UL << 29)
	u8			tsa;
	u8			pri_lvl;
	u8			bw_weight;
	u8			unused;
पूर्ण;

काष्ठा bnxt_dscp2pri_entry अणु
	u8	dscp;
	u8	mask;
	u8	pri;
पूर्ण;

#घोषणा BNXT_LLQ(q_profile)	\
	((q_profile) ==		\
	 QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_LOSSLESS_ROCE)

#घोषणा BNXT_CNPQ(q_profile)	\
	((q_profile) ==		\
	 QUEUE_QPORTCFG_RESP_QUEUE_ID0_SERVICE_PROखाता_LOSSY_ROCE_CNP)

#घोषणा HWRM_STRUCT_DATA_SUBTYPE_HOST_OPERATIONAL	0x0300

व्योम bnxt_dcb_init(काष्ठा bnxt *bp);
व्योम bnxt_dcb_मुक्त(काष्ठा bnxt *bp);
#पूर्ण_अगर
