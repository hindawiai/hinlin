<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2018 Chelsio Communications, Inc. */

#अगर_अघोषित __CHCR_IPSEC_H__
#घोषणा __CHCR_IPSEC_H__

#समावेश <crypto/algapi.h>
#समावेश "t4_hw.h"
#समावेश "cxgb4.h"
#समावेश "t4_msg.h"
#समावेश "cxgb4_uld.h"

#समावेश "chcr_core.h"
#समावेश "chcr_algo.h"
#समावेश "chcr_crypto.h"

#घोषणा CHIPSEC_DRV_MODULE_NAME "ch_ipsec"
#घोषणा CHIPSEC_DRV_VERSION "1.0.0.0-ko"
#घोषणा CHIPSEC_DRV_DESC "Chelsio T6 Crypto Ipsec offload Driver"

काष्ठा ipsec_uld_ctx अणु
	काष्ठा list_head entry;
	काष्ठा cxgb4_lld_info lldi;
पूर्ण;

काष्ठा chcr_ipsec_req अणु
	काष्ठा ulp_txpkt ulptx;
	काष्ठा ulptx_idata sc_imm;
	काष्ठा cpl_tx_sec_pdu sec_cpl;
	काष्ठा _key_ctx key_ctx;
पूर्ण;

काष्ठा chcr_ipsec_wr अणु
	काष्ठा fw_ulptx_wr wreq;
	काष्ठा chcr_ipsec_req req;
पूर्ण;

#घोषणा ESN_IV_INSERT_OFFSET 12
काष्ठा chcr_ipsec_aaभाग अणु
	__be32 spi;
	u8 seq_no[8];
	u8 iv[8];
पूर्ण;

काष्ठा ipsec_sa_entry अणु
	पूर्णांक hmac_ctrl;
	u16 esn;
	u16 resv;
	अचिन्हित पूर्णांक enckey_len;
	अचिन्हित पूर्णांक kctx_len;
	अचिन्हित पूर्णांक authsize;
	__be32 key_ctx_hdr;
	अक्षर salt[MAX_SALT];
	अक्षर key[2 * AES_MAX_KEY_SIZE];
पूर्ण;

#पूर्ण_अगर /* __CHCR_IPSEC_H__ */

