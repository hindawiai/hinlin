<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (C) 2020 Chelsio Communications.  All rights reserved. */

#अगर_अघोषित __CHCR_COMMON_H__
#घोषणा __CHCR_COMMON_H__

#समावेश "cxgb4.h"

#घोषणा CHCR_MAX_SALT                      4
#घोषणा CHCR_KEYCTX_MAC_KEY_SIZE_128       0
#घोषणा CHCR_KEYCTX_CIPHER_KEY_SIZE_128    0
#घोषणा CHCR_SCMD_CIPHER_MODE_AES_GCM      2
#घोषणा CHCR_SCMD_CIPHER_MODE_AES_CTR      3
#घोषणा CHCR_CPL_TX_SEC_PDU_LEN_64BIT      2
#घोषणा CHCR_SCMD_SEQ_NO_CTRL_64BIT        3
#घोषणा CHCR_SCMD_PROTO_VERSION_TLS        0
#घोषणा CHCR_SCMD_PROTO_VERSION_GENERIC    4
#घोषणा CHCR_SCMD_AUTH_MODE_GHASH          4
#घोषणा AES_BLOCK_LEN                      16

काष्ठा ktls_key_ctx अणु
	__be32 ctx_hdr;
	u8 salt[CHCR_MAX_SALT];
	__be64 iv_to_auth;
	अचिन्हित अक्षर key[TLS_CIPHER_AES_GCM_128_KEY_SIZE +
			  TLS_CIPHER_AES_GCM_256_TAG_SIZE];
पूर्ण;

/* Crypto key context */
#घोषणा KEY_CONTEXT_CTX_LEN_S           24
#घोषणा KEY_CONTEXT_CTX_LEN_V(x)        ((x) << KEY_CONTEXT_CTX_LEN_S)

#घोषणा KEY_CONTEXT_SALT_PRESENT_S      10
#घोषणा KEY_CONTEXT_SALT_PRESENT_V(x)   ((x) << KEY_CONTEXT_SALT_PRESENT_S)
#घोषणा KEY_CONTEXT_SALT_PRESENT_F      KEY_CONTEXT_SALT_PRESENT_V(1U)

#घोषणा KEY_CONTEXT_VALID_S     0
#घोषणा KEY_CONTEXT_VALID_V(x)  ((x) << KEY_CONTEXT_VALID_S)
#घोषणा KEY_CONTEXT_VALID_F     KEY_CONTEXT_VALID_V(1U)

#घोषणा KEY_CONTEXT_CK_SIZE_S           6
#घोषणा KEY_CONTEXT_CK_SIZE_V(x)        ((x) << KEY_CONTEXT_CK_SIZE_S)

#घोषणा KEY_CONTEXT_MK_SIZE_S           2
#घोषणा KEY_CONTEXT_MK_SIZE_V(x)        ((x) << KEY_CONTEXT_MK_SIZE_S)

#घोषणा KEY_CONTEXT_OPAD_PRESENT_S      11
#घोषणा KEY_CONTEXT_OPAD_PRESENT_V(x)   ((x) << KEY_CONTEXT_OPAD_PRESENT_S)
#घोषणा KEY_CONTEXT_OPAD_PRESENT_F      KEY_CONTEXT_OPAD_PRESENT_V(1U)

#घोषणा FILL_KEY_CTX_HDR(ck_size, mk_size, ctx_len) \
		htonl(KEY_CONTEXT_MK_SIZE_V(mk_size) | \
		      KEY_CONTEXT_CK_SIZE_V(ck_size) | \
		      KEY_CONTEXT_VALID_F | \
		      KEY_CONTEXT_SALT_PRESENT_F | \
		      KEY_CONTEXT_CTX_LEN_V((ctx_len)))

अटल अंतरभूत व्योम *chcr_copy_to_txd(स्थिर व्योम *src, स्थिर काष्ठा sge_txq *q,
				     व्योम *pos, पूर्णांक length)
अणु
	पूर्णांक left = (व्योम *)q->stat - pos;
	u64 *p;

	अगर (likely(length <= left)) अणु
		स_नकल(pos, src, length);
		pos += length;
	पूर्ण अन्यथा अणु
		स_नकल(pos, src, left);
		स_नकल(q->desc, src + left, length - left);
		pos = (व्योम *)q->desc + (length - left);
	पूर्ण
	/* 0-pad to multiple of 16 */
	p = PTR_ALIGN(pos, 8);
	अगर ((uपूर्णांकptr_t)p & 8) अणु
		*p = 0;
		वापस p + 1;
	पूर्ण
	वापस p;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक chcr_txq_avail(स्थिर काष्ठा sge_txq *q)
अणु
	वापस q->size - 1 - q->in_use;
पूर्ण

अटल अंतरभूत व्योम chcr_txq_advance(काष्ठा sge_txq *q, अचिन्हित पूर्णांक n)
अणु
	q->in_use += n;
	q->pidx += n;
	अगर (q->pidx >= q->size)
		q->pidx -= q->size;
पूर्ण

अटल अंतरभूत व्योम chcr_eth_txq_stop(काष्ठा sge_eth_txq *q)
अणु
	netअगर_tx_stop_queue(q->txq);
	q->q.stops++;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक chcr_sgl_len(अचिन्हित पूर्णांक n)
अणु
	n--;
	वापस (3 * n) / 2 + (n & 1) + 2;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक chcr_flits_to_desc(अचिन्हित पूर्णांक n)
अणु
	WARN_ON(n > SGE_MAX_WR_LEN / 8);
	वापस DIV_ROUND_UP(n, 8);
पूर्ण
#पूर्ण_अगर /* __CHCR_COMMON_H__ */
