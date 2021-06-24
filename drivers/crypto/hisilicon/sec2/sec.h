<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019 HiSilicon Limited. */

#अगर_अघोषित __HISI_SEC_V2_H
#घोषणा __HISI_SEC_V2_H

#समावेश "../qm.h"
#समावेश "sec_crypto.h"

/* Algorithm resource per hardware SEC queue */
काष्ठा sec_alg_res अणु
	u8 *pbuf;
	dma_addr_t pbuf_dma;
	u8 *c_ivin;
	dma_addr_t c_ivin_dma;
	u8 *out_mac;
	dma_addr_t out_mac_dma;
पूर्ण;

/* Cipher request of SEC निजी */
काष्ठा sec_cipher_req अणु
	काष्ठा hisi_acc_hw_sgl *c_in;
	dma_addr_t c_in_dma;
	काष्ठा hisi_acc_hw_sgl *c_out;
	dma_addr_t c_out_dma;
	u8 *c_ivin;
	dma_addr_t c_ivin_dma;
	काष्ठा skcipher_request *sk_req;
	u32 c_len;
	bool encrypt;
पूर्ण;

काष्ठा sec_aead_req अणु
	u8 *out_mac;
	dma_addr_t out_mac_dma;
	काष्ठा aead_request *aead_req;
पूर्ण;

/* SEC request of Crypto */
काष्ठा sec_req अणु
	काष्ठा sec_sqe sec_sqe;
	काष्ठा sec_ctx *ctx;
	काष्ठा sec_qp_ctx *qp_ctx;

	काष्ठा sec_cipher_req c_req;
	काष्ठा sec_aead_req aead_req;
	काष्ठा list_head backlog_head;

	पूर्णांक err_type;
	पूर्णांक req_id;
	u32 flag;

	/* Status of the SEC request */
	bool fake_busy;
	bool use_pbuf;
पूर्ण;

/**
 * काष्ठा sec_req_op - Operations क्रम SEC request
 * @buf_map: DMA map the SGL buffers of the request
 * @buf_unmap: DMA unmap the SGL buffers of the request
 * @bd_fill: Fill the SEC queue BD
 * @bd_send: Send the SEC BD पूर्णांकo the hardware queue
 * @callback: Call back क्रम the request
 * @process: Main processing logic of Skcipher
 */
काष्ठा sec_req_op अणु
	पूर्णांक (*buf_map)(काष्ठा sec_ctx *ctx, काष्ठा sec_req *req);
	व्योम (*buf_unmap)(काष्ठा sec_ctx *ctx, काष्ठा sec_req *req);
	व्योम (*करो_transfer)(काष्ठा sec_ctx *ctx, काष्ठा sec_req *req);
	पूर्णांक (*bd_fill)(काष्ठा sec_ctx *ctx, काष्ठा sec_req *req);
	पूर्णांक (*bd_send)(काष्ठा sec_ctx *ctx, काष्ठा sec_req *req);
	व्योम (*callback)(काष्ठा sec_ctx *ctx, काष्ठा sec_req *req, पूर्णांक err);
	पूर्णांक (*process)(काष्ठा sec_ctx *ctx, काष्ठा sec_req *req);
पूर्ण;

/* SEC auth context */
काष्ठा sec_auth_ctx अणु
	dma_addr_t a_key_dma;
	u8 *a_key;
	u8 a_key_len;
	u8 mac_len;
	u8 a_alg;
	काष्ठा crypto_shash *hash_tfm;
पूर्ण;

/* SEC cipher context which cipher's relatives */
काष्ठा sec_cipher_ctx अणु
	u8 *c_key;
	dma_addr_t c_key_dma;
	sector_t iv_offset;
	u32 c_gran_size;
	u32 ivsize;
	u8 c_mode;
	u8 c_alg;
	u8 c_key_len;
पूर्ण;

/* SEC queue context which defines queue's relatives */
काष्ठा sec_qp_ctx अणु
	काष्ठा hisi_qp *qp;
	काष्ठा sec_req *req_list[QM_Q_DEPTH];
	काष्ठा idr req_idr;
	काष्ठा sec_alg_res res[QM_Q_DEPTH];
	काष्ठा sec_ctx *ctx;
	काष्ठा mutex req_lock;
	काष्ठा list_head backlog;
	काष्ठा hisi_acc_sgl_pool *c_in_pool;
	काष्ठा hisi_acc_sgl_pool *c_out_pool;
पूर्ण;

क्रमागत sec_alg_type अणु
	SEC_SKCIPHER,
	SEC_AEAD
पूर्ण;

/* SEC Crypto TFM context which defines queue and cipher .etc relatives */
काष्ठा sec_ctx अणु
	काष्ठा sec_qp_ctx *qp_ctx;
	काष्ठा sec_dev *sec;
	स्थिर काष्ठा sec_req_op *req_op;
	काष्ठा hisi_qp **qps;

	/* Half queues क्रम encipher, and half क्रम decipher */
	u32 hlf_q_num;

	/* Threshold क्रम fake busy, trigger to वापस -EBUSY to user */
	u32 fake_req_limit;

	/* Currrent cyclic index to select a queue क्रम encipher */
	atomic_t enc_qcyclic;

	 /* Currrent cyclic index to select a queue क्रम decipher */
	atomic_t dec_qcyclic;

	क्रमागत sec_alg_type alg_type;
	bool pbuf_supported;
	काष्ठा sec_cipher_ctx c_ctx;
	काष्ठा sec_auth_ctx a_ctx;
	काष्ठा device *dev;
पूर्ण;

क्रमागत sec_endian अणु
	SEC_LE = 0,
	SEC_32BE,
	SEC_64BE
पूर्ण;

क्रमागत sec_debug_file_index अणु
	SEC_CLEAR_ENABLE,
	SEC_DEBUG_खाता_NUM,
पूर्ण;

काष्ठा sec_debug_file अणु
	क्रमागत sec_debug_file_index index;
	spinlock_t lock;
	काष्ठा hisi_qm *qm;
पूर्ण;

काष्ठा sec_dfx अणु
	atomic64_t send_cnt;
	atomic64_t recv_cnt;
	atomic64_t send_busy_cnt;
	atomic64_t recv_busy_cnt;
	atomic64_t err_bd_cnt;
	atomic64_t invalid_req_cnt;
	atomic64_t करोne_flag_cnt;
पूर्ण;

काष्ठा sec_debug अणु
	काष्ठा sec_dfx dfx;
	काष्ठा sec_debug_file files[SEC_DEBUG_खाता_NUM];
पूर्ण;

काष्ठा sec_dev अणु
	काष्ठा hisi_qm qm;
	काष्ठा sec_debug debug;
	u32 ctx_q_num;
	bool iommu_used;
पूर्ण;

व्योम sec_destroy_qps(काष्ठा hisi_qp **qps, पूर्णांक qp_num);
काष्ठा hisi_qp **sec_create_qps(व्योम);
पूर्णांक sec_रेजिस्टर_to_crypto(काष्ठा hisi_qm *qm);
व्योम sec_unरेजिस्टर_from_crypto(काष्ठा hisi_qm *qm);
#पूर्ण_अगर
