<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Broadcom
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crypto.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/sched.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>

#समावेश <crypto/algapi.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/hmac.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha3.h>

#समावेश "util.h"
#समावेश "cipher.h"
#समावेश "spu.h"
#समावेश "spum.h"
#समावेश "spu2.h"

/* ================= Device Structure ================== */

काष्ठा bcm_device_निजी iproc_priv;

/* ==================== Parameters ===================== */

पूर्णांक flow_debug_logging;
module_param(flow_debug_logging, पूर्णांक, 0644);
MODULE_PARM_DESC(flow_debug_logging, "Enable Flow Debug Logging");

पूर्णांक packet_debug_logging;
module_param(packet_debug_logging, पूर्णांक, 0644);
MODULE_PARM_DESC(packet_debug_logging, "Enable Packet Debug Logging");

पूर्णांक debug_logging_sleep;
module_param(debug_logging_sleep, पूर्णांक, 0644);
MODULE_PARM_DESC(debug_logging_sleep, "Packet Debug Logging Sleep");

/*
 * The value of these module parameters is used to set the priority क्रम each
 * algo type when this driver रेजिस्टरs algos with the kernel crypto API.
 * To use a priority other than the शेष, set the priority in the insmod or
 * modprobe. Changing the module priority after init समय has no effect.
 *
 * The शेष priorities are chosen to be lower (less preferred) than ARMv8 CE
 * algos, but more preferred than generic software algos.
 */
अटल पूर्णांक cipher_pri = 150;
module_param(cipher_pri, पूर्णांक, 0644);
MODULE_PARM_DESC(cipher_pri, "Priority for cipher algos");

अटल पूर्णांक hash_pri = 100;
module_param(hash_pri, पूर्णांक, 0644);
MODULE_PARM_DESC(hash_pri, "Priority for hash algos");

अटल पूर्णांक aead_pri = 150;
module_param(aead_pri, पूर्णांक, 0644);
MODULE_PARM_DESC(aead_pri, "Priority for AEAD algos");

/* A type 3 BCM header, expected to precede the SPU header क्रम SPU-M.
 * Bits 3 and 4 in the first byte encode the channel number (the dma ringset).
 * 0x60 - ring 0
 * 0x68 - ring 1
 * 0x70 - ring 2
 * 0x78 - ring 3
 */
अटल अक्षर BCMHEADER[] = अणु 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28 पूर्ण;
/*
 * Some SPU hw करोes not use BCM header on SPU messages. So BCM_HDR_LEN
 * is set dynamically after पढ़ोing SPU type from device tree.
 */
#घोषणा BCM_HDR_LEN  iproc_priv.bcm_hdr_len

/* min and max समय to sleep beक्रमe retrying when mbox queue is full. usec */
#घोषणा MBOX_SLEEP_MIN  800
#घोषणा MBOX_SLEEP_MAX 1000

/**
 * select_channel() - Select a SPU channel to handle a crypto request. Selects
 * channel in round robin order.
 *
 * Return:  channel index
 */
अटल u8 select_channel(व्योम)
अणु
	u8 chan_idx = atomic_inc_वापस(&iproc_priv.next_chan);

	वापस chan_idx % iproc_priv.spu.num_chan;
पूर्ण

/**
 * spu_skcipher_rx_sg_create() - Build up the scatterlist of buffers used to
 * receive a SPU response message क्रम an skcipher request. Includes buffers to
 * catch SPU message headers and the response data.
 * @mssg:	mailbox message containing the receive sg
 * @rctx:	crypto request context
 * @rx_frag_num: number of scatterlist elements required to hold the
 *		SPU response message
 * @chunksize:	Number of bytes of response data expected
 * @stat_pad_len: Number of bytes required to pad the STAT field to
 *		a 4-byte boundary
 *
 * The scatterlist that माला_लो allocated here is मुक्तd in spu_chunk_cleanup()
 * when the request completes, whether the request is handled successfully or
 * there is an error.
 *
 * Returns:
 *   0 अगर successful
 *   < 0 अगर an error
 */
अटल पूर्णांक
spu_skcipher_rx_sg_create(काष्ठा brcm_message *mssg,
			    काष्ठा iproc_reqctx_s *rctx,
			    u8 rx_frag_num,
			    अचिन्हित पूर्णांक chunksize, u32 stat_pad_len)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा scatterlist *sg;	/* used to build sgs in mbox message */
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;
	u32 datalen;		/* Number of bytes of response data expected */

	mssg->spu.dst = kसुस्मृति(rx_frag_num, माप(काष्ठा scatterlist),
				rctx->gfp);
	अगर (!mssg->spu.dst)
		वापस -ENOMEM;

	sg = mssg->spu.dst;
	sg_init_table(sg, rx_frag_num);
	/* Space क्रम SPU message header */
	sg_set_buf(sg++, rctx->msg_buf.spu_resp_hdr, ctx->spu_resp_hdr_len);

	/* If XTS tweak in payload, add buffer to receive encrypted tweak */
	अगर ((ctx->cipher.mode == CIPHER_MODE_XTS) &&
	    spu->spu_xts_tweak_in_payload())
		sg_set_buf(sg++, rctx->msg_buf.c.supdt_tweak,
			   SPU_XTS_TWEAK_SIZE);

	/* Copy in each dst sg entry from request, up to chunksize */
	datalen = spu_msg_sg_add(&sg, &rctx->dst_sg, &rctx->dst_skip,
				 rctx->dst_nents, chunksize);
	अगर (datalen < chunksize) अणु
		pr_err("%s(): failed to copy dst sg to mbox msg. chunksize %u, datalen %u",
		       __func__, chunksize, datalen);
		वापस -EFAULT;
	पूर्ण

	अगर (stat_pad_len)
		sg_set_buf(sg++, rctx->msg_buf.rx_stat_pad, stat_pad_len);

	स_रखो(rctx->msg_buf.rx_stat, 0, SPU_RX_STATUS_LEN);
	sg_set_buf(sg, rctx->msg_buf.rx_stat, spu->spu_rx_status_len());

	वापस 0;
पूर्ण

/**
 * spu_skcipher_tx_sg_create() - Build up the scatterlist of buffers used to
 * send a SPU request message क्रम an skcipher request. Includes SPU message
 * headers and the request data.
 * @mssg:	mailbox message containing the transmit sg
 * @rctx:	crypto request context
 * @tx_frag_num: number of scatterlist elements required to स्थिरruct the
 *		SPU request message
 * @chunksize:	Number of bytes of request data
 * @pad_len:	Number of pad bytes
 *
 * The scatterlist that माला_लो allocated here is मुक्तd in spu_chunk_cleanup()
 * when the request completes, whether the request is handled successfully or
 * there is an error.
 *
 * Returns:
 *   0 अगर successful
 *   < 0 अगर an error
 */
अटल पूर्णांक
spu_skcipher_tx_sg_create(काष्ठा brcm_message *mssg,
			    काष्ठा iproc_reqctx_s *rctx,
			    u8 tx_frag_num, अचिन्हित पूर्णांक chunksize, u32 pad_len)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा scatterlist *sg;	/* used to build sgs in mbox message */
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;
	u32 datalen;		/* Number of bytes of response data expected */
	u32 stat_len;

	mssg->spu.src = kसुस्मृति(tx_frag_num, माप(काष्ठा scatterlist),
				rctx->gfp);
	अगर (unlikely(!mssg->spu.src))
		वापस -ENOMEM;

	sg = mssg->spu.src;
	sg_init_table(sg, tx_frag_num);

	sg_set_buf(sg++, rctx->msg_buf.bcm_spu_req_hdr,
		   BCM_HDR_LEN + ctx->spu_req_hdr_len);

	/* अगर XTS tweak in payload, copy from IV (where crypto API माला_दो it) */
	अगर ((ctx->cipher.mode == CIPHER_MODE_XTS) &&
	    spu->spu_xts_tweak_in_payload())
		sg_set_buf(sg++, rctx->msg_buf.iv_ctr, SPU_XTS_TWEAK_SIZE);

	/* Copy in each src sg entry from request, up to chunksize */
	datalen = spu_msg_sg_add(&sg, &rctx->src_sg, &rctx->src_skip,
				 rctx->src_nents, chunksize);
	अगर (unlikely(datalen < chunksize)) अणु
		pr_err("%s(): failed to copy src sg to mbox msg",
		       __func__);
		वापस -EFAULT;
	पूर्ण

	अगर (pad_len)
		sg_set_buf(sg++, rctx->msg_buf.spu_req_pad, pad_len);

	stat_len = spu->spu_tx_status_len();
	अगर (stat_len) अणु
		स_रखो(rctx->msg_buf.tx_stat, 0, stat_len);
		sg_set_buf(sg, rctx->msg_buf.tx_stat, stat_len);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mailbox_send_message(काष्ठा brcm_message *mssg, u32 flags,
				u8 chan_idx)
अणु
	पूर्णांक err;
	पूर्णांक retry_cnt = 0;
	काष्ठा device *dev = &(iproc_priv.pdev->dev);

	err = mbox_send_message(iproc_priv.mbox[chan_idx], mssg);
	अगर (flags & CRYPTO_TFM_REQ_MAY_SLEEP) अणु
		जबतक ((err == -ENOBUFS) && (retry_cnt < SPU_MB_RETRY_MAX)) अणु
			/*
			 * Mailbox queue is full. Since MAY_SLEEP is set, assume
			 * not in atomic context and we can रुको and try again.
			 */
			retry_cnt++;
			usleep_range(MBOX_SLEEP_MIN, MBOX_SLEEP_MAX);
			err = mbox_send_message(iproc_priv.mbox[chan_idx],
						mssg);
			atomic_inc(&iproc_priv.mb_no_spc);
		पूर्ण
	पूर्ण
	अगर (err < 0) अणु
		atomic_inc(&iproc_priv.mb_send_fail);
		वापस err;
	पूर्ण

	/* Check error वापसed by mailbox controller */
	err = mssg->error;
	अगर (unlikely(err < 0)) अणु
		dev_err(dev, "message error %d", err);
		/* Signal txकरोne क्रम mailbox channel */
	पूर्ण

	/* Signal txकरोne क्रम mailbox channel */
	mbox_client_txकरोne(iproc_priv.mbox[chan_idx], err);
	वापस err;
पूर्ण

/**
 * handle_skcipher_req() - Submit as much of a block cipher request as fits in
 * a single SPU request message, starting at the current position in the request
 * data.
 * @rctx:	Crypto request context
 *
 * This may be called on the crypto API thपढ़ो, or, when a request is so large
 * it must be broken पूर्णांकo multiple SPU messages, on the thपढ़ो used to invoke
 * the response callback. When requests are broken पूर्णांकo multiple SPU
 * messages, we assume subsequent messages depend on previous results, and
 * thus always रुको क्रम previous results beक्रमe submitting the next message.
 * Because requests are submitted in lock step like this, there is no need
 * to synchronize access to request data काष्ठाures.
 *
 * Return: -EINPROGRESS: request has been accepted and result will be वापसed
 *			 asynchronously
 *         Any other value indicates an error
 */
अटल पूर्णांक handle_skcipher_req(काष्ठा iproc_reqctx_s *rctx)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा crypto_async_request *areq = rctx->parent;
	काष्ठा skcipher_request *req =
	    container_of(areq, काष्ठा skcipher_request, base);
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;
	काष्ठा spu_cipher_parms cipher_parms;
	पूर्णांक err;
	अचिन्हित पूर्णांक chunksize;	/* Num bytes of request to submit */
	पूर्णांक reमुख्यing;	/* Bytes of request still to process */
	पूर्णांक chunk_start;	/* Beginning of data क्रम current SPU msg */

	/* IV or ctr value to use in this SPU msg */
	u8 local_iv_ctr[MAX_IV_SIZE];
	u32 stat_pad_len;	/* num bytes to align status field */
	u32 pad_len;		/* total length of all padding */
	काष्ठा brcm_message *mssg;	/* mailbox message */

	/* number of entries in src and dst sg in mailbox message. */
	u8 rx_frag_num = 2;	/* response header and STATUS */
	u8 tx_frag_num = 1;	/* request header */

	flow_log("%s\n", __func__);

	cipher_parms.alg = ctx->cipher.alg;
	cipher_parms.mode = ctx->cipher.mode;
	cipher_parms.type = ctx->cipher_type;
	cipher_parms.key_len = ctx->enckeylen;
	cipher_parms.key_buf = ctx->enckey;
	cipher_parms.iv_buf = local_iv_ctr;
	cipher_parms.iv_len = rctx->iv_ctr_len;

	mssg = &rctx->mb_mssg;
	chunk_start = rctx->src_sent;
	reमुख्यing = rctx->total_toकरो - chunk_start;

	/* determine the chunk we are अवरोधing off and update the indexes */
	अगर ((ctx->max_payload != SPU_MAX_PAYLOAD_INF) &&
	    (reमुख्यing > ctx->max_payload))
		chunksize = ctx->max_payload;
	अन्यथा
		chunksize = reमुख्यing;

	rctx->src_sent += chunksize;
	rctx->total_sent = rctx->src_sent;

	/* Count number of sg entries to be included in this request */
	rctx->src_nents = spu_sg_count(rctx->src_sg, rctx->src_skip, chunksize);
	rctx->dst_nents = spu_sg_count(rctx->dst_sg, rctx->dst_skip, chunksize);

	अगर ((ctx->cipher.mode == CIPHER_MODE_CBC) &&
	    rctx->is_encrypt && chunk_start)
		/*
		 * Encrypting non-first first chunk. Copy last block of
		 * previous result to IV क्रम this chunk.
		 */
		sg_copy_part_to_buf(req->dst, rctx->msg_buf.iv_ctr,
				    rctx->iv_ctr_len,
				    chunk_start - rctx->iv_ctr_len);

	अगर (rctx->iv_ctr_len) अणु
		/* get our local copy of the iv */
		__builtin_स_नकल(local_iv_ctr, rctx->msg_buf.iv_ctr,
				 rctx->iv_ctr_len);

		/* generate the next IV अगर possible */
		अगर ((ctx->cipher.mode == CIPHER_MODE_CBC) &&
		    !rctx->is_encrypt) अणु
			/*
			 * CBC Decrypt: next IV is the last ciphertext block in
			 * this chunk
			 */
			sg_copy_part_to_buf(req->src, rctx->msg_buf.iv_ctr,
					    rctx->iv_ctr_len,
					    rctx->src_sent - rctx->iv_ctr_len);
		पूर्ण अन्यथा अगर (ctx->cipher.mode == CIPHER_MODE_CTR) अणु
			/*
			 * The SPU hardware increments the counter once क्रम
			 * each AES block of 16 bytes. So update the counter
			 * क्रम the next chunk, अगर there is one. Note that क्रम
			 * this chunk, the counter has alपढ़ोy been copied to
			 * local_iv_ctr. We can assume a block size of 16,
			 * because we only support CTR mode क्रम AES, not क्रम
			 * any other cipher alg.
			 */
			add_to_ctr(rctx->msg_buf.iv_ctr, chunksize >> 4);
		पूर्ण
	पूर्ण

	अगर (ctx->max_payload == SPU_MAX_PAYLOAD_INF)
		flow_log("max_payload infinite\n");
	अन्यथा
		flow_log("max_payload %u\n", ctx->max_payload);

	flow_log("sent:%u start:%u remains:%u size:%u\n",
		 rctx->src_sent, chunk_start, reमुख्यing, chunksize);

	/* Copy SPU header ढाँचा created at setkey समय */
	स_नकल(rctx->msg_buf.bcm_spu_req_hdr, ctx->bcm_spu_req_hdr,
	       माप(rctx->msg_buf.bcm_spu_req_hdr));

	spu->spu_cipher_req_finish(rctx->msg_buf.bcm_spu_req_hdr + BCM_HDR_LEN,
				   ctx->spu_req_hdr_len, !(rctx->is_encrypt),
				   &cipher_parms, chunksize);

	atomic64_add(chunksize, &iproc_priv.bytes_out);

	stat_pad_len = spu->spu_wordalign_padlen(chunksize);
	अगर (stat_pad_len)
		rx_frag_num++;
	pad_len = stat_pad_len;
	अगर (pad_len) अणु
		tx_frag_num++;
		spu->spu_request_pad(rctx->msg_buf.spu_req_pad, 0,
				     0, ctx->auth.alg, ctx->auth.mode,
				     rctx->total_sent, stat_pad_len);
	पूर्ण

	spu->spu_dump_msg_hdr(rctx->msg_buf.bcm_spu_req_hdr + BCM_HDR_LEN,
			      ctx->spu_req_hdr_len);
	packet_log("payload:\n");
	dump_sg(rctx->src_sg, rctx->src_skip, chunksize);
	packet_dump("   pad: ", rctx->msg_buf.spu_req_pad, pad_len);

	/*
	 * Build mailbox message containing SPU request msg and rx buffers
	 * to catch response message
	 */
	स_रखो(mssg, 0, माप(*mssg));
	mssg->type = BRCM_MESSAGE_SPU;
	mssg->ctx = rctx;	/* Will be वापसed in response */

	/* Create rx scatterlist to catch result */
	rx_frag_num += rctx->dst_nents;

	अगर ((ctx->cipher.mode == CIPHER_MODE_XTS) &&
	    spu->spu_xts_tweak_in_payload())
		rx_frag_num++;	/* extra sg to insert tweak */

	err = spu_skcipher_rx_sg_create(mssg, rctx, rx_frag_num, chunksize,
					  stat_pad_len);
	अगर (err)
		वापस err;

	/* Create tx scatterlist containing SPU request message */
	tx_frag_num += rctx->src_nents;
	अगर (spu->spu_tx_status_len())
		tx_frag_num++;

	अगर ((ctx->cipher.mode == CIPHER_MODE_XTS) &&
	    spu->spu_xts_tweak_in_payload())
		tx_frag_num++;	/* extra sg to insert tweak */

	err = spu_skcipher_tx_sg_create(mssg, rctx, tx_frag_num, chunksize,
					  pad_len);
	अगर (err)
		वापस err;

	err = mailbox_send_message(mssg, req->base.flags, rctx->chan_idx);
	अगर (unlikely(err < 0))
		वापस err;

	वापस -EINPROGRESS;
पूर्ण

/**
 * handle_skcipher_resp() - Process a block cipher SPU response. Updates the
 * total received count क्रम the request and updates global stats.
 * @rctx:	Crypto request context
 */
अटल व्योम handle_skcipher_resp(काष्ठा iproc_reqctx_s *rctx)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा crypto_async_request *areq = rctx->parent;
	काष्ठा skcipher_request *req = skcipher_request_cast(areq);
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;
	u32 payload_len;

	/* See how much data was वापसed */
	payload_len = spu->spu_payload_length(rctx->msg_buf.spu_resp_hdr);

	/*
	 * In XTS mode, the first SPU_XTS_TWEAK_SIZE bytes may be the
	 * encrypted tweak ("i") value; we करोn't count those.
	 */
	अगर ((ctx->cipher.mode == CIPHER_MODE_XTS) &&
	    spu->spu_xts_tweak_in_payload() &&
	    (payload_len >= SPU_XTS_TWEAK_SIZE))
		payload_len -= SPU_XTS_TWEAK_SIZE;

	atomic64_add(payload_len, &iproc_priv.bytes_in);

	flow_log("%s() offset: %u, bd_len: %u BD:\n",
		 __func__, rctx->total_received, payload_len);

	dump_sg(req->dst, rctx->total_received, payload_len);

	rctx->total_received += payload_len;
	अगर (rctx->total_received == rctx->total_toकरो) अणु
		atomic_inc(&iproc_priv.op_counts[SPU_OP_CIPHER]);
		atomic_inc(
		   &iproc_priv.cipher_cnt[ctx->cipher.alg][ctx->cipher.mode]);
	पूर्ण
पूर्ण

/**
 * spu_ahash_rx_sg_create() - Build up the scatterlist of buffers used to
 * receive a SPU response message क्रम an ahash request.
 * @mssg:	mailbox message containing the receive sg
 * @rctx:	crypto request context
 * @rx_frag_num: number of scatterlist elements required to hold the
 *		SPU response message
 * @digestsize: length of hash digest, in bytes
 * @stat_pad_len: Number of bytes required to pad the STAT field to
 *		a 4-byte boundary
 *
 * The scatterlist that माला_लो allocated here is मुक्तd in spu_chunk_cleanup()
 * when the request completes, whether the request is handled successfully or
 * there is an error.
 *
 * Return:
 *   0 अगर successful
 *   < 0 अगर an error
 */
अटल पूर्णांक
spu_ahash_rx_sg_create(काष्ठा brcm_message *mssg,
		       काष्ठा iproc_reqctx_s *rctx,
		       u8 rx_frag_num, अचिन्हित पूर्णांक digestsize,
		       u32 stat_pad_len)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा scatterlist *sg;	/* used to build sgs in mbox message */
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;

	mssg->spu.dst = kसुस्मृति(rx_frag_num, माप(काष्ठा scatterlist),
				rctx->gfp);
	अगर (!mssg->spu.dst)
		वापस -ENOMEM;

	sg = mssg->spu.dst;
	sg_init_table(sg, rx_frag_num);
	/* Space क्रम SPU message header */
	sg_set_buf(sg++, rctx->msg_buf.spu_resp_hdr, ctx->spu_resp_hdr_len);

	/* Space क्रम digest */
	sg_set_buf(sg++, rctx->msg_buf.digest, digestsize);

	अगर (stat_pad_len)
		sg_set_buf(sg++, rctx->msg_buf.rx_stat_pad, stat_pad_len);

	स_रखो(rctx->msg_buf.rx_stat, 0, SPU_RX_STATUS_LEN);
	sg_set_buf(sg, rctx->msg_buf.rx_stat, spu->spu_rx_status_len());
	वापस 0;
पूर्ण

/**
 * spu_ahash_tx_sg_create() -  Build up the scatterlist of buffers used to send
 * a SPU request message क्रम an ahash request. Includes SPU message headers and
 * the request data.
 * @mssg:	mailbox message containing the transmit sg
 * @rctx:	crypto request context
 * @tx_frag_num: number of scatterlist elements required to स्थिरruct the
 *		SPU request message
 * @spu_hdr_len: length in bytes of SPU message header
 * @hash_carry_len: Number of bytes of data carried over from previous req
 * @new_data_len: Number of bytes of new request data
 * @pad_len:	Number of pad bytes
 *
 * The scatterlist that माला_लो allocated here is मुक्तd in spu_chunk_cleanup()
 * when the request completes, whether the request is handled successfully or
 * there is an error.
 *
 * Return:
 *   0 अगर successful
 *   < 0 अगर an error
 */
अटल पूर्णांक
spu_ahash_tx_sg_create(काष्ठा brcm_message *mssg,
		       काष्ठा iproc_reqctx_s *rctx,
		       u8 tx_frag_num,
		       u32 spu_hdr_len,
		       अचिन्हित पूर्णांक hash_carry_len,
		       अचिन्हित पूर्णांक new_data_len, u32 pad_len)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा scatterlist *sg;	/* used to build sgs in mbox message */
	u32 datalen;		/* Number of bytes of response data expected */
	u32 stat_len;

	mssg->spu.src = kसुस्मृति(tx_frag_num, माप(काष्ठा scatterlist),
				rctx->gfp);
	अगर (!mssg->spu.src)
		वापस -ENOMEM;

	sg = mssg->spu.src;
	sg_init_table(sg, tx_frag_num);

	sg_set_buf(sg++, rctx->msg_buf.bcm_spu_req_hdr,
		   BCM_HDR_LEN + spu_hdr_len);

	अगर (hash_carry_len)
		sg_set_buf(sg++, rctx->hash_carry, hash_carry_len);

	अगर (new_data_len) अणु
		/* Copy in each src sg entry from request, up to chunksize */
		datalen = spu_msg_sg_add(&sg, &rctx->src_sg, &rctx->src_skip,
					 rctx->src_nents, new_data_len);
		अगर (datalen < new_data_len) अणु
			pr_err("%s(): failed to copy src sg to mbox msg",
			       __func__);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (pad_len)
		sg_set_buf(sg++, rctx->msg_buf.spu_req_pad, pad_len);

	stat_len = spu->spu_tx_status_len();
	अगर (stat_len) अणु
		स_रखो(rctx->msg_buf.tx_stat, 0, stat_len);
		sg_set_buf(sg, rctx->msg_buf.tx_stat, stat_len);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * handle_ahash_req() - Process an asynchronous hash request from the crypto
 * API.
 * @rctx:  Crypto request context
 *
 * Builds a SPU request message embedded in a mailbox message and submits the
 * mailbox message on a selected mailbox channel. The SPU request message is
 * स्थिरructed as a scatterlist, including entries from the crypto API's
 * src scatterlist to aव्योम copying the data to be hashed. This function is
 * called either on the thपढ़ो from the crypto API, or, in the हाल that the
 * crypto API request is too large to fit in a single SPU request message,
 * on the thपढ़ो that invokes the receive callback with a response message.
 * Because some operations require the response from one chunk beक्रमe the next
 * chunk can be submitted, we always रुको क्रम the response क्रम the previous
 * chunk beक्रमe submitting the next chunk. Because requests are submitted in
 * lock step like this, there is no need to synchronize access to request data
 * काष्ठाures.
 *
 * Return:
 *   -EINPROGRESS: request has been submitted to SPU and response will be
 *		   वापसed asynchronously
 *   -EAGAIN:      non-final request included a small amount of data, which क्रम
 *		   efficiency we did not submit to the SPU, but instead stored
 *		   to be submitted to the SPU with the next part of the request
 *   other:        an error code
 */
अटल पूर्णांक handle_ahash_req(काष्ठा iproc_reqctx_s *rctx)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा crypto_async_request *areq = rctx->parent;
	काष्ठा ahash_request *req = ahash_request_cast(areq);
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	काष्ठा crypto_tfm *tfm = crypto_ahash_tfm(ahash);
	अचिन्हित पूर्णांक blocksize = crypto_tfm_alg_blocksize(tfm);
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;

	/* number of bytes still to be hashed in this req */
	अचिन्हित पूर्णांक nbytes_to_hash = 0;
	पूर्णांक err;
	अचिन्हित पूर्णांक chunksize = 0;	/* length of hash carry + new data */
	/*
	 * length of new data, not from hash carry, to be submitted in
	 * this hw request
	 */
	अचिन्हित पूर्णांक new_data_len;

	अचिन्हित पूर्णांक __maybe_unused chunk_start = 0;
	u32 db_size;	 /* Length of data field, incl gcm and hash padding */
	पूर्णांक pad_len = 0; /* total pad len, including gcm, hash, stat padding */
	u32 data_pad_len = 0;	/* length of GCM/CCM padding */
	u32 stat_pad_len = 0;	/* length of padding to align STATUS word */
	काष्ठा brcm_message *mssg;	/* mailbox message */
	काष्ठा spu_request_opts req_opts;
	काष्ठा spu_cipher_parms cipher_parms;
	काष्ठा spu_hash_parms hash_parms;
	काष्ठा spu_aead_parms aead_parms;
	अचिन्हित पूर्णांक local_nbuf;
	u32 spu_hdr_len;
	अचिन्हित पूर्णांक digestsize;
	u16 rem = 0;

	/*
	 * number of entries in src and dst sg. Always includes SPU msg header.
	 * rx always includes a buffer to catch digest and STATUS.
	 */
	u8 rx_frag_num = 3;
	u8 tx_frag_num = 1;

	flow_log("total_todo %u, total_sent %u\n",
		 rctx->total_toकरो, rctx->total_sent);

	स_रखो(&req_opts, 0, माप(req_opts));
	स_रखो(&cipher_parms, 0, माप(cipher_parms));
	स_रखो(&hash_parms, 0, माप(hash_parms));
	स_रखो(&aead_parms, 0, माप(aead_parms));

	req_opts.bd_suppress = true;
	hash_parms.alg = ctx->auth.alg;
	hash_parms.mode = ctx->auth.mode;
	hash_parms.type = HASH_TYPE_NONE;
	hash_parms.key_buf = (u8 *)ctx->authkey;
	hash_parms.key_len = ctx->authkeylen;

	/*
	 * For hash algorithms below assignment looks bit odd but
	 * it's needed क्रम AES-XCBC and AES-CMAC hash algorithms
	 * to dअगरferentiate between 128, 192, 256 bit key values.
	 * Based on the key values, hash algorithm is selected.
	 * For example क्रम 128 bit key, hash algorithm is AES-128.
	 */
	cipher_parms.type = ctx->cipher_type;

	mssg = &rctx->mb_mssg;
	chunk_start = rctx->src_sent;

	/*
	 * Compute the amount reमुख्यing to hash. This may include data
	 * carried over from previous requests.
	 */
	nbytes_to_hash = rctx->total_toकरो - rctx->total_sent;
	chunksize = nbytes_to_hash;
	अगर ((ctx->max_payload != SPU_MAX_PAYLOAD_INF) &&
	    (chunksize > ctx->max_payload))
		chunksize = ctx->max_payload;

	/*
	 * If this is not a final request and the request data is not a multiple
	 * of a full block, then simply park the extra data and prefix it to the
	 * data क्रम the next request.
	 */
	अगर (!rctx->is_final) अणु
		u8 *dest = rctx->hash_carry + rctx->hash_carry_len;
		u16 new_len;  /* len of data to add to hash carry */

		rem = chunksize % blocksize;   /* reमुख्यder */
		अगर (rem) अणु
			/* chunksize not a multiple of blocksize */
			chunksize -= rem;
			अगर (chunksize == 0) अणु
				/* Don't have a full block to submit to hw */
				new_len = rem - rctx->hash_carry_len;
				sg_copy_part_to_buf(req->src, dest, new_len,
						    rctx->src_sent);
				rctx->hash_carry_len = rem;
				flow_log("Exiting with hash carry len: %u\n",
					 rctx->hash_carry_len);
				packet_dump("  buf: ",
					    rctx->hash_carry,
					    rctx->hash_carry_len);
				वापस -EAGAIN;
			पूर्ण
		पूर्ण
	पूर्ण

	/* अगर we have hash carry, then prefix it to the data in this request */
	local_nbuf = rctx->hash_carry_len;
	rctx->hash_carry_len = 0;
	अगर (local_nbuf)
		tx_frag_num++;
	new_data_len = chunksize - local_nbuf;

	/* Count number of sg entries to be used in this request */
	rctx->src_nents = spu_sg_count(rctx->src_sg, rctx->src_skip,
				       new_data_len);

	/* AES hashing keeps key size in type field, so need to copy it here */
	अगर (hash_parms.alg == HASH_ALG_AES)
		hash_parms.type = (क्रमागत hash_type)cipher_parms.type;
	अन्यथा
		hash_parms.type = spu->spu_hash_type(rctx->total_sent);

	digestsize = spu->spu_digest_size(ctx->digestsize, ctx->auth.alg,
					  hash_parms.type);
	hash_parms.digestsize =	digestsize;

	/* update the indexes */
	rctx->total_sent += chunksize;
	/* अगर you sent a prebuf then that wasn't from this req->src */
	rctx->src_sent += new_data_len;

	अगर ((rctx->total_sent == rctx->total_toकरो) && rctx->is_final)
		hash_parms.pad_len = spu->spu_hash_pad_len(hash_parms.alg,
							   hash_parms.mode,
							   chunksize,
							   blocksize);

	/*
	 * If a non-first chunk, then include the digest वापसed from the
	 * previous chunk so that hw can add to it (except क्रम AES types).
	 */
	अगर ((hash_parms.type == HASH_TYPE_UPDT) &&
	    (hash_parms.alg != HASH_ALG_AES)) अणु
		hash_parms.key_buf = rctx->incr_hash;
		hash_parms.key_len = digestsize;
	पूर्ण

	atomic64_add(chunksize, &iproc_priv.bytes_out);

	flow_log("%s() final: %u nbuf: %u ",
		 __func__, rctx->is_final, local_nbuf);

	अगर (ctx->max_payload == SPU_MAX_PAYLOAD_INF)
		flow_log("max_payload infinite\n");
	अन्यथा
		flow_log("max_payload %u\n", ctx->max_payload);

	flow_log("chunk_start: %u chunk_size: %u\n", chunk_start, chunksize);

	/* Prepend SPU header with type 3 BCM header */
	स_नकल(rctx->msg_buf.bcm_spu_req_hdr, BCMHEADER, BCM_HDR_LEN);

	hash_parms.prebuf_len = local_nbuf;
	spu_hdr_len = spu->spu_create_request(rctx->msg_buf.bcm_spu_req_hdr +
					      BCM_HDR_LEN,
					      &req_opts, &cipher_parms,
					      &hash_parms, &aead_parms,
					      new_data_len);

	अगर (spu_hdr_len == 0) अणु
		pr_err("Failed to create SPU request header\n");
		वापस -EFAULT;
	पूर्ण

	/*
	 * Determine total length of padding required. Put all padding in one
	 * buffer.
	 */
	data_pad_len = spu->spu_gcm_ccm_pad_len(ctx->cipher.mode, chunksize);
	db_size = spu_real_db_size(0, 0, local_nbuf, new_data_len,
				   0, 0, hash_parms.pad_len);
	अगर (spu->spu_tx_status_len())
		stat_pad_len = spu->spu_wordalign_padlen(db_size);
	अगर (stat_pad_len)
		rx_frag_num++;
	pad_len = hash_parms.pad_len + data_pad_len + stat_pad_len;
	अगर (pad_len) अणु
		tx_frag_num++;
		spu->spu_request_pad(rctx->msg_buf.spu_req_pad, data_pad_len,
				     hash_parms.pad_len, ctx->auth.alg,
				     ctx->auth.mode, rctx->total_sent,
				     stat_pad_len);
	पूर्ण

	spu->spu_dump_msg_hdr(rctx->msg_buf.bcm_spu_req_hdr + BCM_HDR_LEN,
			      spu_hdr_len);
	packet_dump("    prebuf: ", rctx->hash_carry, local_nbuf);
	flow_log("Data:\n");
	dump_sg(rctx->src_sg, rctx->src_skip, new_data_len);
	packet_dump("   pad: ", rctx->msg_buf.spu_req_pad, pad_len);

	/*
	 * Build mailbox message containing SPU request msg and rx buffers
	 * to catch response message
	 */
	स_रखो(mssg, 0, माप(*mssg));
	mssg->type = BRCM_MESSAGE_SPU;
	mssg->ctx = rctx;	/* Will be वापसed in response */

	/* Create rx scatterlist to catch result */
	err = spu_ahash_rx_sg_create(mssg, rctx, rx_frag_num, digestsize,
				     stat_pad_len);
	अगर (err)
		वापस err;

	/* Create tx scatterlist containing SPU request message */
	tx_frag_num += rctx->src_nents;
	अगर (spu->spu_tx_status_len())
		tx_frag_num++;
	err = spu_ahash_tx_sg_create(mssg, rctx, tx_frag_num, spu_hdr_len,
				     local_nbuf, new_data_len, pad_len);
	अगर (err)
		वापस err;

	err = mailbox_send_message(mssg, req->base.flags, rctx->chan_idx);
	अगर (unlikely(err < 0))
		वापस err;

	वापस -EINPROGRESS;
पूर्ण

/**
 * spu_hmac_outer_hash() - Request synchonous software compute of the outer hash
 * क्रम an HMAC request.
 * @req:  The HMAC request from the crypto API
 * @ctx:  The session context
 *
 * Return: 0 अगर synchronous hash operation successful
 *         -EINVAL अगर the hash algo is unrecognized
 *         any other value indicates an error
 */
अटल पूर्णांक spu_hmac_outer_hash(काष्ठा ahash_request *req,
			       काष्ठा iproc_ctx_s *ctx)
अणु
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	अचिन्हित पूर्णांक blocksize =
		crypto_tfm_alg_blocksize(crypto_ahash_tfm(ahash));
	पूर्णांक rc;

	चयन (ctx->auth.alg) अणु
	हाल HASH_ALG_MD5:
		rc = करो_shash("md5", req->result, ctx->opad, blocksize,
			      req->result, ctx->digestsize, शून्य, 0);
		अवरोध;
	हाल HASH_ALG_SHA1:
		rc = करो_shash("sha1", req->result, ctx->opad, blocksize,
			      req->result, ctx->digestsize, शून्य, 0);
		अवरोध;
	हाल HASH_ALG_SHA224:
		rc = करो_shash("sha224", req->result, ctx->opad, blocksize,
			      req->result, ctx->digestsize, शून्य, 0);
		अवरोध;
	हाल HASH_ALG_SHA256:
		rc = करो_shash("sha256", req->result, ctx->opad, blocksize,
			      req->result, ctx->digestsize, शून्य, 0);
		अवरोध;
	हाल HASH_ALG_SHA384:
		rc = करो_shash("sha384", req->result, ctx->opad, blocksize,
			      req->result, ctx->digestsize, शून्य, 0);
		अवरोध;
	हाल HASH_ALG_SHA512:
		rc = करो_shash("sha512", req->result, ctx->opad, blocksize,
			      req->result, ctx->digestsize, शून्य, 0);
		अवरोध;
	शेष:
		pr_err("%s() Error : unknown hmac type\n", __func__);
		rc = -EINVAL;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * ahash_req_करोne() - Process a hash result from the SPU hardware.
 * @rctx: Crypto request context
 *
 * Return: 0 अगर successful
 *         < 0 अगर an error
 */
अटल पूर्णांक ahash_req_करोne(काष्ठा iproc_reqctx_s *rctx)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा crypto_async_request *areq = rctx->parent;
	काष्ठा ahash_request *req = ahash_request_cast(areq);
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;
	पूर्णांक err;

	स_नकल(req->result, rctx->msg_buf.digest, ctx->digestsize);

	अगर (spu->spu_type == SPU_TYPE_SPUM) अणु
		/* byte swap the output from the UPDT function to network byte
		 * order
		 */
		अगर (ctx->auth.alg == HASH_ALG_MD5) अणु
			__swab32s((u32 *)req->result);
			__swab32s(((u32 *)req->result) + 1);
			__swab32s(((u32 *)req->result) + 2);
			__swab32s(((u32 *)req->result) + 3);
			__swab32s(((u32 *)req->result) + 4);
		पूर्ण
	पूर्ण

	flow_dump("  digest ", req->result, ctx->digestsize);

	/* अगर this an HMAC then करो the outer hash */
	अगर (rctx->is_sw_hmac) अणु
		err = spu_hmac_outer_hash(req, ctx);
		अगर (err < 0)
			वापस err;
		flow_dump("  hmac: ", req->result, ctx->digestsize);
	पूर्ण

	अगर (rctx->is_sw_hmac || ctx->auth.mode == HASH_MODE_HMAC) अणु
		atomic_inc(&iproc_priv.op_counts[SPU_OP_HMAC]);
		atomic_inc(&iproc_priv.hmac_cnt[ctx->auth.alg]);
	पूर्ण अन्यथा अणु
		atomic_inc(&iproc_priv.op_counts[SPU_OP_HASH]);
		atomic_inc(&iproc_priv.hash_cnt[ctx->auth.alg]);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * handle_ahash_resp() - Process a SPU response message क्रम a hash request.
 * Checks अगर the entire crypto API request has been processed, and अगर so,
 * invokes post processing on the result.
 * @rctx: Crypto request context
 */
अटल व्योम handle_ahash_resp(काष्ठा iproc_reqctx_s *rctx)
अणु
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;
	काष्ठा crypto_async_request *areq = rctx->parent;
	काष्ठा ahash_request *req = ahash_request_cast(areq);
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	अचिन्हित पूर्णांक blocksize =
		crypto_tfm_alg_blocksize(crypto_ahash_tfm(ahash));
	/*
	 * Save hash to use as input to next op अगर incremental. Might be copying
	 * too much, but that's easier than figuring out actual digest size here
	 */
	स_नकल(rctx->incr_hash, rctx->msg_buf.digest, MAX_DIGEST_SIZE);

	flow_log("%s() blocksize:%u digestsize:%u\n",
		 __func__, blocksize, ctx->digestsize);

	atomic64_add(ctx->digestsize, &iproc_priv.bytes_in);

	अगर (rctx->is_final && (rctx->total_sent == rctx->total_toकरो))
		ahash_req_करोne(rctx);
पूर्ण

/**
 * spu_aead_rx_sg_create() - Build up the scatterlist of buffers used to receive
 * a SPU response message क्रम an AEAD request. Includes buffers to catch SPU
 * message headers and the response data.
 * @mssg:	mailbox message containing the receive sg
 * @req:	Crypto API request
 * @rctx:	crypto request context
 * @rx_frag_num: number of scatterlist elements required to hold the
 *		SPU response message
 * @assoc_len:	Length of associated data included in the crypto request
 * @ret_iv_len: Length of IV वापसed in response
 * @resp_len:	Number of bytes of response data expected to be written to
 *              dst buffer from crypto API
 * @digestsize: Length of hash digest, in bytes
 * @stat_pad_len: Number of bytes required to pad the STAT field to
 *		a 4-byte boundary
 *
 * The scatterlist that माला_लो allocated here is मुक्तd in spu_chunk_cleanup()
 * when the request completes, whether the request is handled successfully or
 * there is an error.
 *
 * Returns:
 *   0 अगर successful
 *   < 0 अगर an error
 */
अटल पूर्णांक spu_aead_rx_sg_create(काष्ठा brcm_message *mssg,
				 काष्ठा aead_request *req,
				 काष्ठा iproc_reqctx_s *rctx,
				 u8 rx_frag_num,
				 अचिन्हित पूर्णांक assoc_len,
				 u32 ret_iv_len, अचिन्हित पूर्णांक resp_len,
				 अचिन्हित पूर्णांक digestsize, u32 stat_pad_len)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा scatterlist *sg;	/* used to build sgs in mbox message */
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;
	u32 datalen;		/* Number of bytes of response data expected */
	u32 assoc_buf_len;
	u8 data_padlen = 0;

	अगर (ctx->is_rfc4543) अणु
		/* RFC4543: only pad after data, not after AAD */
		data_padlen = spu->spu_gcm_ccm_pad_len(ctx->cipher.mode,
							  assoc_len + resp_len);
		assoc_buf_len = assoc_len;
	पूर्ण अन्यथा अणु
		data_padlen = spu->spu_gcm_ccm_pad_len(ctx->cipher.mode,
							  resp_len);
		assoc_buf_len = spu->spu_assoc_resp_len(ctx->cipher.mode,
						assoc_len, ret_iv_len,
						rctx->is_encrypt);
	पूर्ण

	अगर (ctx->cipher.mode == CIPHER_MODE_CCM)
		/* ICV (after data) must be in the next 32-bit word क्रम CCM */
		data_padlen += spu->spu_wordalign_padlen(assoc_buf_len +
							 resp_len +
							 data_padlen);

	अगर (data_padlen)
		/* have to catch gcm pad in separate buffer */
		rx_frag_num++;

	mssg->spu.dst = kसुस्मृति(rx_frag_num, माप(काष्ठा scatterlist),
				rctx->gfp);
	अगर (!mssg->spu.dst)
		वापस -ENOMEM;

	sg = mssg->spu.dst;
	sg_init_table(sg, rx_frag_num);

	/* Space क्रम SPU message header */
	sg_set_buf(sg++, rctx->msg_buf.spu_resp_hdr, ctx->spu_resp_hdr_len);

	अगर (assoc_buf_len) अणु
		/*
		 * Don't ग_लिखो directly to req->dst, because SPU may pad the
		 * assoc data in the response
		 */
		स_रखो(rctx->msg_buf.a.resp_aad, 0, assoc_buf_len);
		sg_set_buf(sg++, rctx->msg_buf.a.resp_aad, assoc_buf_len);
	पूर्ण

	अगर (resp_len) अणु
		/*
		 * Copy in each dst sg entry from request, up to chunksize.
		 * dst sg catches just the data. digest caught in separate buf.
		 */
		datalen = spu_msg_sg_add(&sg, &rctx->dst_sg, &rctx->dst_skip,
					 rctx->dst_nents, resp_len);
		अगर (datalen < (resp_len)) अणु
			pr_err("%s(): failed to copy dst sg to mbox msg. expected len %u, datalen %u",
			       __func__, resp_len, datalen);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	/* If GCM/CCM data is padded, catch padding in separate buffer */
	अगर (data_padlen) अणु
		स_रखो(rctx->msg_buf.a.gcmpad, 0, data_padlen);
		sg_set_buf(sg++, rctx->msg_buf.a.gcmpad, data_padlen);
	पूर्ण

	/* Always catch ICV in separate buffer */
	sg_set_buf(sg++, rctx->msg_buf.digest, digestsize);

	flow_log("stat_pad_len %u\n", stat_pad_len);
	अगर (stat_pad_len) अणु
		स_रखो(rctx->msg_buf.rx_stat_pad, 0, stat_pad_len);
		sg_set_buf(sg++, rctx->msg_buf.rx_stat_pad, stat_pad_len);
	पूर्ण

	स_रखो(rctx->msg_buf.rx_stat, 0, SPU_RX_STATUS_LEN);
	sg_set_buf(sg, rctx->msg_buf.rx_stat, spu->spu_rx_status_len());

	वापस 0;
पूर्ण

/**
 * spu_aead_tx_sg_create() - Build up the scatterlist of buffers used to send a
 * SPU request message क्रम an AEAD request. Includes SPU message headers and the
 * request data.
 * @mssg:	mailbox message containing the transmit sg
 * @rctx:	crypto request context
 * @tx_frag_num: number of scatterlist elements required to स्थिरruct the
 *		SPU request message
 * @spu_hdr_len: length of SPU message header in bytes
 * @assoc:	crypto API associated data scatterlist
 * @assoc_len:	length of associated data
 * @assoc_nents: number of scatterlist entries containing assoc data
 * @aead_iv_len: length of AEAD IV, अगर included
 * @chunksize:	Number of bytes of request data
 * @aad_pad_len: Number of bytes of padding at end of AAD. For GCM/CCM.
 * @pad_len:	Number of pad bytes
 * @incl_icv:	If true, ग_लिखो separate ICV buffer after data and
 *              any padding
 *
 * The scatterlist that माला_लो allocated here is मुक्तd in spu_chunk_cleanup()
 * when the request completes, whether the request is handled successfully or
 * there is an error.
 *
 * Return:
 *   0 अगर successful
 *   < 0 अगर an error
 */
अटल पूर्णांक spu_aead_tx_sg_create(काष्ठा brcm_message *mssg,
				 काष्ठा iproc_reqctx_s *rctx,
				 u8 tx_frag_num,
				 u32 spu_hdr_len,
				 काष्ठा scatterlist *assoc,
				 अचिन्हित पूर्णांक assoc_len,
				 पूर्णांक assoc_nents,
				 अचिन्हित पूर्णांक aead_iv_len,
				 अचिन्हित पूर्णांक chunksize,
				 u32 aad_pad_len, u32 pad_len, bool incl_icv)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा scatterlist *sg;	/* used to build sgs in mbox message */
	काष्ठा scatterlist *assoc_sg = assoc;
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;
	u32 datalen;		/* Number of bytes of data to ग_लिखो */
	u32 written;		/* Number of bytes of data written */
	u32 assoc_offset = 0;
	u32 stat_len;

	mssg->spu.src = kसुस्मृति(tx_frag_num, माप(काष्ठा scatterlist),
				rctx->gfp);
	अगर (!mssg->spu.src)
		वापस -ENOMEM;

	sg = mssg->spu.src;
	sg_init_table(sg, tx_frag_num);

	sg_set_buf(sg++, rctx->msg_buf.bcm_spu_req_hdr,
		   BCM_HDR_LEN + spu_hdr_len);

	अगर (assoc_len) अणु
		/* Copy in each associated data sg entry from request */
		written = spu_msg_sg_add(&sg, &assoc_sg, &assoc_offset,
					 assoc_nents, assoc_len);
		अगर (written < assoc_len) अणु
			pr_err("%s(): failed to copy assoc sg to mbox msg",
			       __func__);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (aead_iv_len)
		sg_set_buf(sg++, rctx->msg_buf.iv_ctr, aead_iv_len);

	अगर (aad_pad_len) अणु
		स_रखो(rctx->msg_buf.a.req_aad_pad, 0, aad_pad_len);
		sg_set_buf(sg++, rctx->msg_buf.a.req_aad_pad, aad_pad_len);
	पूर्ण

	datalen = chunksize;
	अगर ((chunksize > ctx->digestsize) && incl_icv)
		datalen -= ctx->digestsize;
	अगर (datalen) अणु
		/* For aead, a single msg should consume the entire src sg */
		written = spu_msg_sg_add(&sg, &rctx->src_sg, &rctx->src_skip,
					 rctx->src_nents, datalen);
		अगर (written < datalen) अणु
			pr_err("%s(): failed to copy src sg to mbox msg",
			       __func__);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (pad_len) अणु
		स_रखो(rctx->msg_buf.spu_req_pad, 0, pad_len);
		sg_set_buf(sg++, rctx->msg_buf.spu_req_pad, pad_len);
	पूर्ण

	अगर (incl_icv)
		sg_set_buf(sg++, rctx->msg_buf.digest, ctx->digestsize);

	stat_len = spu->spu_tx_status_len();
	अगर (stat_len) अणु
		स_रखो(rctx->msg_buf.tx_stat, 0, stat_len);
		sg_set_buf(sg, rctx->msg_buf.tx_stat, stat_len);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * handle_aead_req() - Submit a SPU request message क्रम the next chunk of the
 * current AEAD request.
 * @rctx:  Crypto request context
 *
 * Unlike other operation types, we assume the length of the request fits in
 * a single SPU request message. aead_enqueue() makes sure this is true.
 * Comments क्रम other op types regarding thपढ़ोs applies here as well.
 *
 * Unlike incremental hash ops, where the spu वापसs the entire hash क्रम
 * truncated algs like sha-224, the SPU वापसs just the truncated hash in
 * response to aead requests. So digestsize is always ctx->digestsize here.
 *
 * Return: -EINPROGRESS: crypto request has been accepted and result will be
 *			 वापसed asynchronously
 *         Any other value indicates an error
 */
अटल पूर्णांक handle_aead_req(काष्ठा iproc_reqctx_s *rctx)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा crypto_async_request *areq = rctx->parent;
	काष्ठा aead_request *req = container_of(areq,
						काष्ठा aead_request, base);
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;
	पूर्णांक err;
	अचिन्हित पूर्णांक chunksize;
	अचिन्हित पूर्णांक resp_len;
	u32 spu_hdr_len;
	u32 db_size;
	u32 stat_pad_len;
	u32 pad_len;
	काष्ठा brcm_message *mssg;	/* mailbox message */
	काष्ठा spu_request_opts req_opts;
	काष्ठा spu_cipher_parms cipher_parms;
	काष्ठा spu_hash_parms hash_parms;
	काष्ठा spu_aead_parms aead_parms;
	पूर्णांक assoc_nents = 0;
	bool incl_icv = false;
	अचिन्हित पूर्णांक digestsize = ctx->digestsize;

	/* number of entries in src and dst sg. Always includes SPU msg header.
	 */
	u8 rx_frag_num = 2;	/* and STATUS */
	u8 tx_frag_num = 1;

	/* करोing the whole thing at once */
	chunksize = rctx->total_toकरो;

	flow_log("%s: chunksize %u\n", __func__, chunksize);

	स_रखो(&req_opts, 0, माप(req_opts));
	स_रखो(&hash_parms, 0, माप(hash_parms));
	स_रखो(&aead_parms, 0, माप(aead_parms));

	req_opts.is_inbound = !(rctx->is_encrypt);
	req_opts.auth_first = ctx->auth_first;
	req_opts.is_aead = true;
	req_opts.is_esp = ctx->is_esp;

	cipher_parms.alg = ctx->cipher.alg;
	cipher_parms.mode = ctx->cipher.mode;
	cipher_parms.type = ctx->cipher_type;
	cipher_parms.key_buf = ctx->enckey;
	cipher_parms.key_len = ctx->enckeylen;
	cipher_parms.iv_buf = rctx->msg_buf.iv_ctr;
	cipher_parms.iv_len = rctx->iv_ctr_len;

	hash_parms.alg = ctx->auth.alg;
	hash_parms.mode = ctx->auth.mode;
	hash_parms.type = HASH_TYPE_NONE;
	hash_parms.key_buf = (u8 *)ctx->authkey;
	hash_parms.key_len = ctx->authkeylen;
	hash_parms.digestsize = digestsize;

	अगर ((ctx->auth.alg == HASH_ALG_SHA224) &&
	    (ctx->authkeylen < SHA224_DIGEST_SIZE))
		hash_parms.key_len = SHA224_DIGEST_SIZE;

	aead_parms.assoc_size = req->assoclen;
	अगर (ctx->is_esp && !ctx->is_rfc4543) अणु
		/*
		 * 8-byte IV is included assoc data in request. SPU2
		 * expects AAD to include just SPI and seqno. So
		 * subtract off the IV len.
		 */
		aead_parms.assoc_size -= GCM_RFC4106_IV_SIZE;

		अगर (rctx->is_encrypt) अणु
			aead_parms.वापस_iv = true;
			aead_parms.ret_iv_len = GCM_RFC4106_IV_SIZE;
			aead_parms.ret_iv_off = GCM_ESP_SALT_SIZE;
		पूर्ण
	पूर्ण अन्यथा अणु
		aead_parms.ret_iv_len = 0;
	पूर्ण

	/*
	 * Count number of sg entries from the crypto API request that are to
	 * be included in this mailbox message. For dst sg, करोn't count space
	 * क्रम digest. Digest माला_लो caught in a separate buffer and copied back
	 * to dst sg when processing response.
	 */
	rctx->src_nents = spu_sg_count(rctx->src_sg, rctx->src_skip, chunksize);
	rctx->dst_nents = spu_sg_count(rctx->dst_sg, rctx->dst_skip, chunksize);
	अगर (aead_parms.assoc_size)
		assoc_nents = spu_sg_count(rctx->assoc, 0,
					   aead_parms.assoc_size);

	mssg = &rctx->mb_mssg;

	rctx->total_sent = chunksize;
	rctx->src_sent = chunksize;
	अगर (spu->spu_assoc_resp_len(ctx->cipher.mode,
				    aead_parms.assoc_size,
				    aead_parms.ret_iv_len,
				    rctx->is_encrypt))
		rx_frag_num++;

	aead_parms.iv_len = spu->spu_aead_ivlen(ctx->cipher.mode,
						rctx->iv_ctr_len);

	अगर (ctx->auth.alg == HASH_ALG_AES)
		hash_parms.type = (क्रमागत hash_type)ctx->cipher_type;

	/* General हाल AAD padding (CCM and RFC4543 special हालs below) */
	aead_parms.aad_pad_len = spu->spu_gcm_ccm_pad_len(ctx->cipher.mode,
						 aead_parms.assoc_size);

	/* General हाल data padding (CCM decrypt special हाल below) */
	aead_parms.data_pad_len = spu->spu_gcm_ccm_pad_len(ctx->cipher.mode,
							   chunksize);

	अगर (ctx->cipher.mode == CIPHER_MODE_CCM) अणु
		/*
		 * क्रम CCM, AAD len + 2 (rather than AAD len) needs to be
		 * 128-bit aligned
		 */
		aead_parms.aad_pad_len = spu->spu_gcm_ccm_pad_len(
					 ctx->cipher.mode,
					 aead_parms.assoc_size + 2);

		/*
		 * And when decrypting CCM, need to pad without including
		 * size of ICV which is tacked on to end of chunk
		 */
		अगर (!rctx->is_encrypt)
			aead_parms.data_pad_len =
				spu->spu_gcm_ccm_pad_len(ctx->cipher.mode,
							chunksize - digestsize);

		/* CCM also requires software to reग_लिखो portions of IV: */
		spu->spu_ccm_update_iv(digestsize, &cipher_parms, req->assoclen,
				       chunksize, rctx->is_encrypt,
				       ctx->is_esp);
	पूर्ण

	अगर (ctx->is_rfc4543) अणु
		/*
		 * RFC4543: data is included in AAD, so करोn't pad after AAD
		 * and pad data based on both AAD + data size
		 */
		aead_parms.aad_pad_len = 0;
		अगर (!rctx->is_encrypt)
			aead_parms.data_pad_len = spu->spu_gcm_ccm_pad_len(
					ctx->cipher.mode,
					aead_parms.assoc_size + chunksize -
					digestsize);
		अन्यथा
			aead_parms.data_pad_len = spu->spu_gcm_ccm_pad_len(
					ctx->cipher.mode,
					aead_parms.assoc_size + chunksize);

		req_opts.is_rfc4543 = true;
	पूर्ण

	अगर (spu_req_incl_icv(ctx->cipher.mode, rctx->is_encrypt)) अणु
		incl_icv = true;
		tx_frag_num++;
		/* Copy ICV from end of src scatterlist to digest buf */
		sg_copy_part_to_buf(req->src, rctx->msg_buf.digest, digestsize,
				    req->assoclen + rctx->total_sent -
				    digestsize);
	पूर्ण

	atomic64_add(chunksize, &iproc_priv.bytes_out);

	flow_log("%s()-sent chunksize:%u\n", __func__, chunksize);

	/* Prepend SPU header with type 3 BCM header */
	स_नकल(rctx->msg_buf.bcm_spu_req_hdr, BCMHEADER, BCM_HDR_LEN);

	spu_hdr_len = spu->spu_create_request(rctx->msg_buf.bcm_spu_req_hdr +
					      BCM_HDR_LEN, &req_opts,
					      &cipher_parms, &hash_parms,
					      &aead_parms, chunksize);

	/* Determine total length of padding. Put all padding in one buffer. */
	db_size = spu_real_db_size(aead_parms.assoc_size, aead_parms.iv_len, 0,
				   chunksize, aead_parms.aad_pad_len,
				   aead_parms.data_pad_len, 0);

	stat_pad_len = spu->spu_wordalign_padlen(db_size);

	अगर (stat_pad_len)
		rx_frag_num++;
	pad_len = aead_parms.data_pad_len + stat_pad_len;
	अगर (pad_len) अणु
		tx_frag_num++;
		spu->spu_request_pad(rctx->msg_buf.spu_req_pad,
				     aead_parms.data_pad_len, 0,
				     ctx->auth.alg, ctx->auth.mode,
				     rctx->total_sent, stat_pad_len);
	पूर्ण

	spu->spu_dump_msg_hdr(rctx->msg_buf.bcm_spu_req_hdr + BCM_HDR_LEN,
			      spu_hdr_len);
	dump_sg(rctx->assoc, 0, aead_parms.assoc_size);
	packet_dump("    aead iv: ", rctx->msg_buf.iv_ctr, aead_parms.iv_len);
	packet_log("BD:\n");
	dump_sg(rctx->src_sg, rctx->src_skip, chunksize);
	packet_dump("   pad: ", rctx->msg_buf.spu_req_pad, pad_len);

	/*
	 * Build mailbox message containing SPU request msg and rx buffers
	 * to catch response message
	 */
	स_रखो(mssg, 0, माप(*mssg));
	mssg->type = BRCM_MESSAGE_SPU;
	mssg->ctx = rctx;	/* Will be वापसed in response */

	/* Create rx scatterlist to catch result */
	rx_frag_num += rctx->dst_nents;
	resp_len = chunksize;

	/*
	 * Always catch ICV in separate buffer. Have to क्रम GCM/CCM because of
	 * padding. Have to क्रम SHA-224 and other truncated SHAs because SPU
	 * sends entire digest back.
	 */
	rx_frag_num++;

	अगर (((ctx->cipher.mode == CIPHER_MODE_GCM) ||
	     (ctx->cipher.mode == CIPHER_MODE_CCM)) && !rctx->is_encrypt) अणु
		/*
		 * Input is ciphertxt plus ICV, but ICV not incl
		 * in output.
		 */
		resp_len -= ctx->digestsize;
		अगर (resp_len == 0)
			/* no rx frags to catch output data */
			rx_frag_num -= rctx->dst_nents;
	पूर्ण

	err = spu_aead_rx_sg_create(mssg, req, rctx, rx_frag_num,
				    aead_parms.assoc_size,
				    aead_parms.ret_iv_len, resp_len, digestsize,
				    stat_pad_len);
	अगर (err)
		वापस err;

	/* Create tx scatterlist containing SPU request message */
	tx_frag_num += rctx->src_nents;
	tx_frag_num += assoc_nents;
	अगर (aead_parms.aad_pad_len)
		tx_frag_num++;
	अगर (aead_parms.iv_len)
		tx_frag_num++;
	अगर (spu->spu_tx_status_len())
		tx_frag_num++;
	err = spu_aead_tx_sg_create(mssg, rctx, tx_frag_num, spu_hdr_len,
				    rctx->assoc, aead_parms.assoc_size,
				    assoc_nents, aead_parms.iv_len, chunksize,
				    aead_parms.aad_pad_len, pad_len, incl_icv);
	अगर (err)
		वापस err;

	err = mailbox_send_message(mssg, req->base.flags, rctx->chan_idx);
	अगर (unlikely(err < 0))
		वापस err;

	वापस -EINPROGRESS;
पूर्ण

/**
 * handle_aead_resp() - Process a SPU response message क्रम an AEAD request.
 * @rctx:  Crypto request context
 */
अटल व्योम handle_aead_resp(काष्ठा iproc_reqctx_s *rctx)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा crypto_async_request *areq = rctx->parent;
	काष्ठा aead_request *req = container_of(areq,
						काष्ठा aead_request, base);
	काष्ठा iproc_ctx_s *ctx = rctx->ctx;
	u32 payload_len;
	अचिन्हित पूर्णांक icv_offset;
	u32 result_len;

	/* See how much data was वापसed */
	payload_len = spu->spu_payload_length(rctx->msg_buf.spu_resp_hdr);
	flow_log("payload_len %u\n", payload_len);

	/* only count payload */
	atomic64_add(payload_len, &iproc_priv.bytes_in);

	अगर (req->assoclen)
		packet_dump("  assoc_data ", rctx->msg_buf.a.resp_aad,
			    req->assoclen);

	/*
	 * Copy the ICV back to the destination
	 * buffer. In decrypt हाल, SPU gives us back the digest, but crypto
	 * API करोesn't expect ICV in dst buffer.
	 */
	result_len = req->cryptlen;
	अगर (rctx->is_encrypt) अणु
		icv_offset = req->assoclen + rctx->total_sent;
		packet_dump("  ICV: ", rctx->msg_buf.digest, ctx->digestsize);
		flow_log("copying ICV to dst sg at offset %u\n", icv_offset);
		sg_copy_part_from_buf(req->dst, rctx->msg_buf.digest,
				      ctx->digestsize, icv_offset);
		result_len += ctx->digestsize;
	पूर्ण

	packet_log("response data:  ");
	dump_sg(req->dst, req->assoclen, result_len);

	atomic_inc(&iproc_priv.op_counts[SPU_OP_AEAD]);
	अगर (ctx->cipher.alg == CIPHER_ALG_AES) अणु
		अगर (ctx->cipher.mode == CIPHER_MODE_CCM)
			atomic_inc(&iproc_priv.aead_cnt[AES_CCM]);
		अन्यथा अगर (ctx->cipher.mode == CIPHER_MODE_GCM)
			atomic_inc(&iproc_priv.aead_cnt[AES_GCM]);
		अन्यथा
			atomic_inc(&iproc_priv.aead_cnt[AUTHENC]);
	पूर्ण अन्यथा अणु
		atomic_inc(&iproc_priv.aead_cnt[AUTHENC]);
	पूर्ण
पूर्ण

/**
 * spu_chunk_cleanup() - Do cleanup after processing one chunk of a request
 * @rctx:  request context
 *
 * Mailbox scatterlists are allocated क्रम each chunk. So मुक्त them after
 * processing each chunk.
 */
अटल व्योम spu_chunk_cleanup(काष्ठा iproc_reqctx_s *rctx)
अणु
	/* mailbox message used to tx request */
	काष्ठा brcm_message *mssg = &rctx->mb_mssg;

	kमुक्त(mssg->spu.src);
	kमुक्त(mssg->spu.dst);
	स_रखो(mssg, 0, माप(काष्ठा brcm_message));
पूर्ण

/**
 * finish_req() - Used to invoke the complete callback from the requester when
 * a request has been handled asynchronously.
 * @rctx:  Request context
 * @err:   Indicates whether the request was successful or not
 *
 * Ensures that cleanup has been करोne क्रम request
 */
अटल व्योम finish_req(काष्ठा iproc_reqctx_s *rctx, पूर्णांक err)
अणु
	काष्ठा crypto_async_request *areq = rctx->parent;

	flow_log("%s() err:%d\n\n", __func__, err);

	/* No harm करोne अगर alपढ़ोy called */
	spu_chunk_cleanup(rctx);

	अगर (areq)
		areq->complete(areq, err);
पूर्ण

/**
 * spu_rx_callback() - Callback from mailbox framework with a SPU response.
 * @cl:		mailbox client काष्ठाure क्रम SPU driver
 * @msg:	mailbox message containing SPU response
 */
अटल व्योम spu_rx_callback(काष्ठा mbox_client *cl, व्योम *msg)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा brcm_message *mssg = msg;
	काष्ठा iproc_reqctx_s *rctx;
	पूर्णांक err;

	rctx = mssg->ctx;
	अगर (unlikely(!rctx)) अणु
		/* This is fatal */
		pr_err("%s(): no request context", __func__);
		err = -EFAULT;
		जाओ cb_finish;
	पूर्ण

	/* process the SPU status */
	err = spu->spu_status_process(rctx->msg_buf.rx_stat);
	अगर (err != 0) अणु
		अगर (err == SPU_INVALID_ICV)
			atomic_inc(&iproc_priv.bad_icv);
		err = -EBADMSG;
		जाओ cb_finish;
	पूर्ण

	/* Process the SPU response message */
	चयन (rctx->ctx->alg->type) अणु
	हाल CRYPTO_ALG_TYPE_SKCIPHER:
		handle_skcipher_resp(rctx);
		अवरोध;
	हाल CRYPTO_ALG_TYPE_AHASH:
		handle_ahash_resp(rctx);
		अवरोध;
	हाल CRYPTO_ALG_TYPE_AEAD:
		handle_aead_resp(rctx);
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ cb_finish;
	पूर्ण

	/*
	 * If this response करोes not complete the request, then send the next
	 * request chunk.
	 */
	अगर (rctx->total_sent < rctx->total_toकरो) अणु
		/* Deallocate anything specअगरic to previous chunk */
		spu_chunk_cleanup(rctx);

		चयन (rctx->ctx->alg->type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			err = handle_skcipher_req(rctx);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			err = handle_ahash_req(rctx);
			अगर (err == -EAGAIN)
				/*
				 * we saved data in hash carry, but tell crypto
				 * API we successfully completed request.
				 */
				err = 0;
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AEAD:
			err = handle_aead_req(rctx);
			अवरोध;
		शेष:
			err = -EINVAL;
		पूर्ण

		अगर (err == -EINPROGRESS)
			/* Successfully submitted request क्रम next chunk */
			वापस;
	पूर्ण

cb_finish:
	finish_req(rctx, err);
पूर्ण

/* ==================== Kernel Cryptographic API ==================== */

/**
 * skcipher_enqueue() - Handle skcipher encrypt or decrypt request.
 * @req:	Crypto API request
 * @encrypt:	true अगर encrypting; false अगर decrypting
 *
 * Return: -EINPROGRESS अगर request accepted and result will be वापसed
 *			asynchronously
 *	   < 0 अगर an error
 */
अटल पूर्णांक skcipher_enqueue(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा iproc_reqctx_s *rctx = skcipher_request_ctx(req);
	काष्ठा iproc_ctx_s *ctx =
	    crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	पूर्णांक err;

	flow_log("%s() enc:%u\n", __func__, encrypt);

	rctx->gfp = (req->base.flags & (CRYPTO_TFM_REQ_MAY_BACKLOG |
		       CRYPTO_TFM_REQ_MAY_SLEEP)) ? GFP_KERNEL : GFP_ATOMIC;
	rctx->parent = &req->base;
	rctx->is_encrypt = encrypt;
	rctx->bd_suppress = false;
	rctx->total_toकरो = req->cryptlen;
	rctx->src_sent = 0;
	rctx->total_sent = 0;
	rctx->total_received = 0;
	rctx->ctx = ctx;

	/* Initialize current position in src and dst scatterlists */
	rctx->src_sg = req->src;
	rctx->src_nents = 0;
	rctx->src_skip = 0;
	rctx->dst_sg = req->dst;
	rctx->dst_nents = 0;
	rctx->dst_skip = 0;

	अगर (ctx->cipher.mode == CIPHER_MODE_CBC ||
	    ctx->cipher.mode == CIPHER_MODE_CTR ||
	    ctx->cipher.mode == CIPHER_MODE_OFB ||
	    ctx->cipher.mode == CIPHER_MODE_XTS ||
	    ctx->cipher.mode == CIPHER_MODE_GCM ||
	    ctx->cipher.mode == CIPHER_MODE_CCM) अणु
		rctx->iv_ctr_len =
		    crypto_skcipher_ivsize(crypto_skcipher_reqtfm(req));
		स_नकल(rctx->msg_buf.iv_ctr, req->iv, rctx->iv_ctr_len);
	पूर्ण अन्यथा अणु
		rctx->iv_ctr_len = 0;
	पूर्ण

	/* Choose a SPU to process this request */
	rctx->chan_idx = select_channel();
	err = handle_skcipher_req(rctx);
	अगर (err != -EINPROGRESS)
		/* synchronous result */
		spu_chunk_cleanup(rctx);

	वापस err;
पूर्ण

अटल पूर्णांक des_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
		      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा iproc_ctx_s *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक err;

	err = verअगरy_skcipher_des_key(cipher, key);
	अगर (err)
		वापस err;

	ctx->cipher_type = CIPHER_TYPE_DES;
	वापस 0;
पूर्ण

अटल पूर्णांक threedes_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा iproc_ctx_s *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक err;

	err = verअगरy_skcipher_des3_key(cipher, key);
	अगर (err)
		वापस err;

	ctx->cipher_type = CIPHER_TYPE_3DES;
	वापस 0;
पूर्ण

अटल पूर्णांक aes_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
		      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा iproc_ctx_s *ctx = crypto_skcipher_ctx(cipher);

	अगर (ctx->cipher.mode == CIPHER_MODE_XTS)
		/* XTS includes two keys of equal length */
		keylen = keylen / 2;

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
		ctx->cipher_type = CIPHER_TYPE_AES128;
		अवरोध;
	हाल AES_KEYSIZE_192:
		ctx->cipher_type = CIPHER_TYPE_AES192;
		अवरोध;
	हाल AES_KEYSIZE_256:
		ctx->cipher_type = CIPHER_TYPE_AES256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	WARN_ON((ctx->max_payload != SPU_MAX_PAYLOAD_INF) &&
		((ctx->max_payload % AES_BLOCK_SIZE) != 0));
	वापस 0;
पूर्ण

अटल पूर्णांक skcipher_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा iproc_ctx_s *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा spu_cipher_parms cipher_parms;
	u32 alloc_len = 0;
	पूर्णांक err;

	flow_log("skcipher_setkey() keylen: %d\n", keylen);
	flow_dump("  key: ", key, keylen);

	चयन (ctx->cipher.alg) अणु
	हाल CIPHER_ALG_DES:
		err = des_setkey(cipher, key, keylen);
		अवरोध;
	हाल CIPHER_ALG_3DES:
		err = threedes_setkey(cipher, key, keylen);
		अवरोध;
	हाल CIPHER_ALG_AES:
		err = aes_setkey(cipher, key, keylen);
		अवरोध;
	शेष:
		pr_err("%s() Error: unknown cipher alg\n", __func__);
		err = -EINVAL;
	पूर्ण
	अगर (err)
		वापस err;

	स_नकल(ctx->enckey, key, keylen);
	ctx->enckeylen = keylen;

	/* SPU needs XTS keys in the reverse order the crypto API presents */
	अगर ((ctx->cipher.alg == CIPHER_ALG_AES) &&
	    (ctx->cipher.mode == CIPHER_MODE_XTS)) अणु
		अचिन्हित पूर्णांक xts_keylen = keylen / 2;

		स_नकल(ctx->enckey, key + xts_keylen, xts_keylen);
		स_नकल(ctx->enckey + xts_keylen, key, xts_keylen);
	पूर्ण

	अगर (spu->spu_type == SPU_TYPE_SPUM)
		alloc_len = BCM_HDR_LEN + SPU_HEADER_ALLOC_LEN;
	अन्यथा अगर (spu->spu_type == SPU_TYPE_SPU2)
		alloc_len = BCM_HDR_LEN + SPU2_HEADER_ALLOC_LEN;
	स_रखो(ctx->bcm_spu_req_hdr, 0, alloc_len);
	cipher_parms.iv_buf = शून्य;
	cipher_parms.iv_len = crypto_skcipher_ivsize(cipher);
	flow_log("%s: iv_len %u\n", __func__, cipher_parms.iv_len);

	cipher_parms.alg = ctx->cipher.alg;
	cipher_parms.mode = ctx->cipher.mode;
	cipher_parms.type = ctx->cipher_type;
	cipher_parms.key_buf = ctx->enckey;
	cipher_parms.key_len = ctx->enckeylen;

	/* Prepend SPU request message with BCM header */
	स_नकल(ctx->bcm_spu_req_hdr, BCMHEADER, BCM_HDR_LEN);
	ctx->spu_req_hdr_len =
	    spu->spu_cipher_req_init(ctx->bcm_spu_req_hdr + BCM_HDR_LEN,
				     &cipher_parms);

	ctx->spu_resp_hdr_len = spu->spu_response_hdr_len(ctx->authkeylen,
							  ctx->enckeylen,
							  false);

	atomic_inc(&iproc_priv.setkey_cnt[SPU_OP_CIPHER]);

	वापस 0;
पूर्ण

अटल पूर्णांक skcipher_encrypt(काष्ठा skcipher_request *req)
अणु
	flow_log("skcipher_encrypt() nbytes:%u\n", req->cryptlen);

	वापस skcipher_enqueue(req, true);
पूर्ण

अटल पूर्णांक skcipher_decrypt(काष्ठा skcipher_request *req)
अणु
	flow_log("skcipher_decrypt() nbytes:%u\n", req->cryptlen);
	वापस skcipher_enqueue(req, false);
पूर्ण

अटल पूर्णांक ahash_enqueue(काष्ठा ahash_request *req)
अणु
	काष्ठा iproc_reqctx_s *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);
	पूर्णांक err;
	स्थिर अक्षर *alg_name;

	flow_log("ahash_enqueue() nbytes:%u\n", req->nbytes);

	rctx->gfp = (req->base.flags & (CRYPTO_TFM_REQ_MAY_BACKLOG |
		       CRYPTO_TFM_REQ_MAY_SLEEP)) ? GFP_KERNEL : GFP_ATOMIC;
	rctx->parent = &req->base;
	rctx->ctx = ctx;
	rctx->bd_suppress = true;
	स_रखो(&rctx->mb_mssg, 0, माप(काष्ठा brcm_message));

	/* Initialize position in src scatterlist */
	rctx->src_sg = req->src;
	rctx->src_skip = 0;
	rctx->src_nents = 0;
	rctx->dst_sg = शून्य;
	rctx->dst_skip = 0;
	rctx->dst_nents = 0;

	/* SPU2 hardware करोes not compute hash of zero length data */
	अगर ((rctx->is_final == 1) && (rctx->total_toकरो == 0) &&
	    (iproc_priv.spu.spu_type == SPU_TYPE_SPU2)) अणु
		alg_name = crypto_tfm_alg_name(crypto_ahash_tfm(tfm));
		flow_log("Doing %sfinal %s zero-len hash request in software\n",
			 rctx->is_final ? "" : "non-", alg_name);
		err = करो_shash((अचिन्हित अक्षर *)alg_name, req->result,
			       शून्य, 0, शून्य, 0, ctx->authkey,
			       ctx->authkeylen);
		अगर (err < 0)
			flow_log("Hash request failed with error %d\n", err);
		वापस err;
	पूर्ण
	/* Choose a SPU to process this request */
	rctx->chan_idx = select_channel();

	err = handle_ahash_req(rctx);
	अगर (err != -EINPROGRESS)
		/* synchronous result */
		spu_chunk_cleanup(rctx);

	अगर (err == -EAGAIN)
		/*
		 * we saved data in hash carry, but tell crypto API
		 * we successfully completed request.
		 */
		err = 0;

	वापस err;
पूर्ण

अटल पूर्णांक __ahash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा iproc_reqctx_s *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);

	flow_log("%s()\n", __func__);

	/* Initialize the context */
	rctx->hash_carry_len = 0;
	rctx->is_final = 0;

	rctx->total_toकरो = 0;
	rctx->src_sent = 0;
	rctx->total_sent = 0;
	rctx->total_received = 0;

	ctx->digestsize = crypto_ahash_digestsize(tfm);
	/* If we add a hash whose digest is larger, catch it here. */
	WARN_ON(ctx->digestsize > MAX_DIGEST_SIZE);

	rctx->is_sw_hmac = false;

	ctx->spu_resp_hdr_len = spu->spu_response_hdr_len(ctx->authkeylen, 0,
							  true);

	वापस 0;
पूर्ण

/**
 * spu_no_incr_hash() - Determine whether incremental hashing is supported.
 * @ctx:  Crypto session context
 *
 * SPU-2 करोes not support incremental hashing (we'll have to revisit and
 * condition based on chip revision or device tree entry अगर future versions करो
 * support incremental hash)
 *
 * SPU-M also करोesn't support incremental hashing of AES-XCBC
 *
 * Return: true अगर incremental hashing is not supported
 *         false otherwise
 */
अटल bool spu_no_incr_hash(काष्ठा iproc_ctx_s *ctx)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;

	अगर (spu->spu_type == SPU_TYPE_SPU2)
		वापस true;

	अगर ((ctx->auth.alg == HASH_ALG_AES) &&
	    (ctx->auth.mode == HASH_MODE_XCBC))
		वापस true;

	/* Otherwise, incremental hashing is supported */
	वापस false;
पूर्ण

अटल पूर्णांक ahash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);
	स्थिर अक्षर *alg_name;
	काष्ठा crypto_shash *hash;
	पूर्णांक ret;
	gfp_t gfp;

	अगर (spu_no_incr_hash(ctx)) अणु
		/*
		 * If we get an incremental hashing request and it's not
		 * supported by the hardware, we need to handle it in software
		 * by calling synchronous hash functions.
		 */
		alg_name = crypto_tfm_alg_name(crypto_ahash_tfm(tfm));
		hash = crypto_alloc_shash(alg_name, 0, 0);
		अगर (IS_ERR(hash)) अणु
			ret = PTR_ERR(hash);
			जाओ err;
		पूर्ण

		gfp = (req->base.flags & (CRYPTO_TFM_REQ_MAY_BACKLOG |
		       CRYPTO_TFM_REQ_MAY_SLEEP)) ? GFP_KERNEL : GFP_ATOMIC;
		ctx->shash = kदो_स्मृति(माप(*ctx->shash) +
				     crypto_shash_descsize(hash), gfp);
		अगर (!ctx->shash) अणु
			ret = -ENOMEM;
			जाओ err_hash;
		पूर्ण
		ctx->shash->tfm = hash;

		/* Set the key using data we alपढ़ोy have from setkey */
		अगर (ctx->authkeylen > 0) अणु
			ret = crypto_shash_setkey(hash, ctx->authkey,
						  ctx->authkeylen);
			अगर (ret)
				जाओ err_shash;
		पूर्ण

		/* Initialize hash w/ this key and other params */
		ret = crypto_shash_init(ctx->shash);
		अगर (ret)
			जाओ err_shash;
	पूर्ण अन्यथा अणु
		/* Otherwise call the पूर्णांकernal function which uses SPU hw */
		ret = __ahash_init(req);
	पूर्ण

	वापस ret;

err_shash:
	kमुक्त(ctx->shash);
err_hash:
	crypto_मुक्त_shash(hash);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक __ahash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा iproc_reqctx_s *rctx = ahash_request_ctx(req);

	flow_log("ahash_update() nbytes:%u\n", req->nbytes);

	अगर (!req->nbytes)
		वापस 0;
	rctx->total_toकरो += req->nbytes;
	rctx->src_sent = 0;

	वापस ahash_enqueue(req);
पूर्ण

अटल पूर्णांक ahash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);
	u8 *पंचांगpbuf;
	पूर्णांक ret;
	पूर्णांक nents;
	gfp_t gfp;

	अगर (spu_no_incr_hash(ctx)) अणु
		/*
		 * If we get an incremental hashing request and it's not
		 * supported by the hardware, we need to handle it in software
		 * by calling synchronous hash functions.
		 */
		अगर (req->src)
			nents = sg_nents(req->src);
		अन्यथा
			वापस -EINVAL;

		/* Copy data from req scatterlist to पंचांगp buffer */
		gfp = (req->base.flags & (CRYPTO_TFM_REQ_MAY_BACKLOG |
		       CRYPTO_TFM_REQ_MAY_SLEEP)) ? GFP_KERNEL : GFP_ATOMIC;
		पंचांगpbuf = kदो_स्मृति(req->nbytes, gfp);
		अगर (!पंचांगpbuf)
			वापस -ENOMEM;

		अगर (sg_copy_to_buffer(req->src, nents, पंचांगpbuf, req->nbytes) !=
				req->nbytes) अणु
			kमुक्त(पंचांगpbuf);
			वापस -EINVAL;
		पूर्ण

		/* Call synchronous update */
		ret = crypto_shash_update(ctx->shash, पंचांगpbuf, req->nbytes);
		kमुक्त(पंचांगpbuf);
	पूर्ण अन्यथा अणु
		/* Otherwise call the पूर्णांकernal function which uses SPU hw */
		ret = __ahash_update(req);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __ahash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा iproc_reqctx_s *rctx = ahash_request_ctx(req);

	flow_log("ahash_final() nbytes:%u\n", req->nbytes);

	rctx->is_final = 1;

	वापस ahash_enqueue(req);
पूर्ण

अटल पूर्णांक ahash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);
	पूर्णांक ret;

	अगर (spu_no_incr_hash(ctx)) अणु
		/*
		 * If we get an incremental hashing request and it's not
		 * supported by the hardware, we need to handle it in software
		 * by calling synchronous hash functions.
		 */
		ret = crypto_shash_final(ctx->shash, req->result);

		/* Done with hash, can deallocate it now */
		crypto_मुक्त_shash(ctx->shash->tfm);
		kमुक्त(ctx->shash);

	पूर्ण अन्यथा अणु
		/* Otherwise call the पूर्णांकernal function which uses SPU hw */
		ret = __ahash_final(req);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __ahash_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा iproc_reqctx_s *rctx = ahash_request_ctx(req);

	flow_log("ahash_finup() nbytes:%u\n", req->nbytes);

	rctx->total_toकरो += req->nbytes;
	rctx->src_sent = 0;
	rctx->is_final = 1;

	वापस ahash_enqueue(req);
पूर्ण

अटल पूर्णांक ahash_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);
	u8 *पंचांगpbuf;
	पूर्णांक ret;
	पूर्णांक nents;
	gfp_t gfp;

	अगर (spu_no_incr_hash(ctx)) अणु
		/*
		 * If we get an incremental hashing request and it's not
		 * supported by the hardware, we need to handle it in software
		 * by calling synchronous hash functions.
		 */
		अगर (req->src) अणु
			nents = sg_nents(req->src);
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			जाओ ahash_finup_निकास;
		पूर्ण

		/* Copy data from req scatterlist to पंचांगp buffer */
		gfp = (req->base.flags & (CRYPTO_TFM_REQ_MAY_BACKLOG |
		       CRYPTO_TFM_REQ_MAY_SLEEP)) ? GFP_KERNEL : GFP_ATOMIC;
		पंचांगpbuf = kदो_स्मृति(req->nbytes, gfp);
		अगर (!पंचांगpbuf) अणु
			ret = -ENOMEM;
			जाओ ahash_finup_निकास;
		पूर्ण

		अगर (sg_copy_to_buffer(req->src, nents, पंचांगpbuf, req->nbytes) !=
				req->nbytes) अणु
			ret = -EINVAL;
			जाओ ahash_finup_मुक्त;
		पूर्ण

		/* Call synchronous update */
		ret = crypto_shash_finup(ctx->shash, पंचांगpbuf, req->nbytes,
					 req->result);
	पूर्ण अन्यथा अणु
		/* Otherwise call the पूर्णांकernal function which uses SPU hw */
		वापस __ahash_finup(req);
	पूर्ण
ahash_finup_मुक्त:
	kमुक्त(पंचांगpbuf);

ahash_finup_निकास:
	/* Done with hash, can deallocate it now */
	crypto_मुक्त_shash(ctx->shash->tfm);
	kमुक्त(ctx->shash);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक err;

	flow_log("ahash_digest() nbytes:%u\n", req->nbytes);

	/* whole thing at once */
	err = __ahash_init(req);
	अगर (!err)
		err = __ahash_finup(req);

	वापस err;
पूर्ण

अटल पूर्णांक ahash_setkey(काष्ठा crypto_ahash *ahash, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा iproc_ctx_s *ctx = crypto_ahash_ctx(ahash);

	flow_log("%s() ahash:%p key:%p keylen:%u\n",
		 __func__, ahash, key, keylen);
	flow_dump("  key: ", key, keylen);

	अगर (ctx->auth.alg == HASH_ALG_AES) अणु
		चयन (keylen) अणु
		हाल AES_KEYSIZE_128:
			ctx->cipher_type = CIPHER_TYPE_AES128;
			अवरोध;
		हाल AES_KEYSIZE_192:
			ctx->cipher_type = CIPHER_TYPE_AES192;
			अवरोध;
		हाल AES_KEYSIZE_256:
			ctx->cipher_type = CIPHER_TYPE_AES256;
			अवरोध;
		शेष:
			pr_err("%s() Error: Invalid key length\n", __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("%s() Error: unknown hash alg\n", __func__);
		वापस -EINVAL;
	पूर्ण
	स_नकल(ctx->authkey, key, keylen);
	ctx->authkeylen = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	स्थिर काष्ठा iproc_reqctx_s *rctx = ahash_request_ctx(req);
	काष्ठा spu_hash_export_s *spu_exp = (काष्ठा spu_hash_export_s *)out;

	spu_exp->total_toकरो = rctx->total_toकरो;
	spu_exp->total_sent = rctx->total_sent;
	spu_exp->is_sw_hmac = rctx->is_sw_hmac;
	स_नकल(spu_exp->hash_carry, rctx->hash_carry, माप(rctx->hash_carry));
	spu_exp->hash_carry_len = rctx->hash_carry_len;
	स_नकल(spu_exp->incr_hash, rctx->incr_hash, माप(rctx->incr_hash));

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा iproc_reqctx_s *rctx = ahash_request_ctx(req);
	काष्ठा spu_hash_export_s *spu_exp = (काष्ठा spu_hash_export_s *)in;

	rctx->total_toकरो = spu_exp->total_toकरो;
	rctx->total_sent = spu_exp->total_sent;
	rctx->is_sw_hmac = spu_exp->is_sw_hmac;
	स_नकल(rctx->hash_carry, spu_exp->hash_carry, माप(rctx->hash_carry));
	rctx->hash_carry_len = spu_exp->hash_carry_len;
	स_नकल(rctx->incr_hash, spu_exp->incr_hash, माप(rctx->incr_hash));

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_hmac_setkey(काष्ठा crypto_ahash *ahash, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा iproc_ctx_s *ctx = crypto_ahash_ctx(ahash);
	अचिन्हित पूर्णांक blocksize =
		crypto_tfm_alg_blocksize(crypto_ahash_tfm(ahash));
	अचिन्हित पूर्णांक digestsize = crypto_ahash_digestsize(ahash);
	अचिन्हित पूर्णांक index;
	पूर्णांक rc;

	flow_log("%s() ahash:%p key:%p keylen:%u blksz:%u digestsz:%u\n",
		 __func__, ahash, key, keylen, blocksize, digestsize);
	flow_dump("  key: ", key, keylen);

	अगर (keylen > blocksize) अणु
		चयन (ctx->auth.alg) अणु
		हाल HASH_ALG_MD5:
			rc = करो_shash("md5", ctx->authkey, key, keylen, शून्य,
				      0, शून्य, 0);
			अवरोध;
		हाल HASH_ALG_SHA1:
			rc = करो_shash("sha1", ctx->authkey, key, keylen, शून्य,
				      0, शून्य, 0);
			अवरोध;
		हाल HASH_ALG_SHA224:
			rc = करो_shash("sha224", ctx->authkey, key, keylen, शून्य,
				      0, शून्य, 0);
			अवरोध;
		हाल HASH_ALG_SHA256:
			rc = करो_shash("sha256", ctx->authkey, key, keylen, शून्य,
				      0, शून्य, 0);
			अवरोध;
		हाल HASH_ALG_SHA384:
			rc = करो_shash("sha384", ctx->authkey, key, keylen, शून्य,
				      0, शून्य, 0);
			अवरोध;
		हाल HASH_ALG_SHA512:
			rc = करो_shash("sha512", ctx->authkey, key, keylen, शून्य,
				      0, शून्य, 0);
			अवरोध;
		हाल HASH_ALG_SHA3_224:
			rc = करो_shash("sha3-224", ctx->authkey, key, keylen,
				      शून्य, 0, शून्य, 0);
			अवरोध;
		हाल HASH_ALG_SHA3_256:
			rc = करो_shash("sha3-256", ctx->authkey, key, keylen,
				      शून्य, 0, शून्य, 0);
			अवरोध;
		हाल HASH_ALG_SHA3_384:
			rc = करो_shash("sha3-384", ctx->authkey, key, keylen,
				      शून्य, 0, शून्य, 0);
			अवरोध;
		हाल HASH_ALG_SHA3_512:
			rc = करो_shash("sha3-512", ctx->authkey, key, keylen,
				      शून्य, 0, शून्य, 0);
			अवरोध;
		शेष:
			pr_err("%s() Error: unknown hash alg\n", __func__);
			वापस -EINVAL;
		पूर्ण
		अगर (rc < 0) अणु
			pr_err("%s() Error %d computing shash for %s\n",
			       __func__, rc, hash_alg_name[ctx->auth.alg]);
			वापस rc;
		पूर्ण
		ctx->authkeylen = digestsize;

		flow_log("  keylen > digestsize... hashed\n");
		flow_dump("  newkey: ", ctx->authkey, ctx->authkeylen);
	पूर्ण अन्यथा अणु
		स_नकल(ctx->authkey, key, keylen);
		ctx->authkeylen = keylen;
	पूर्ण

	/*
	 * Full HMAC operation in SPUM is not verअगरied,
	 * So keeping the generation of IPAD, OPAD and
	 * outer hashing in software.
	 */
	अगर (iproc_priv.spu.spu_type == SPU_TYPE_SPUM) अणु
		स_नकल(ctx->ipad, ctx->authkey, ctx->authkeylen);
		स_रखो(ctx->ipad + ctx->authkeylen, 0,
		       blocksize - ctx->authkeylen);
		ctx->authkeylen = 0;
		स_नकल(ctx->opad, ctx->ipad, blocksize);

		क्रम (index = 0; index < blocksize; index++) अणु
			ctx->ipad[index] ^= HMAC_IPAD_VALUE;
			ctx->opad[index] ^= HMAC_OPAD_VALUE;
		पूर्ण

		flow_dump("  ipad: ", ctx->ipad, blocksize);
		flow_dump("  opad: ", ctx->opad, blocksize);
	पूर्ण
	ctx->digestsize = digestsize;
	atomic_inc(&iproc_priv.setkey_cnt[SPU_OP_HMAC]);

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_hmac_init(काष्ठा ahash_request *req)
अणु
	काष्ठा iproc_reqctx_s *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);
	अचिन्हित पूर्णांक blocksize =
			crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	flow_log("ahash_hmac_init()\n");

	/* init the context as a hash */
	ahash_init(req);

	अगर (!spu_no_incr_hash(ctx)) अणु
		/* SPU-M can करो incr hashing but needs sw क्रम outer HMAC */
		rctx->is_sw_hmac = true;
		ctx->auth.mode = HASH_MODE_HASH;
		/* start with a prepended ipad */
		स_नकल(rctx->hash_carry, ctx->ipad, blocksize);
		rctx->hash_carry_len = blocksize;
		rctx->total_toकरो += blocksize;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ahash_hmac_update(काष्ठा ahash_request *req)
अणु
	flow_log("ahash_hmac_update() nbytes:%u\n", req->nbytes);

	अगर (!req->nbytes)
		वापस 0;

	वापस ahash_update(req);
पूर्ण

अटल पूर्णांक ahash_hmac_final(काष्ठा ahash_request *req)
अणु
	flow_log("ahash_hmac_final() nbytes:%u\n", req->nbytes);

	वापस ahash_final(req);
पूर्ण

अटल पूर्णांक ahash_hmac_finup(काष्ठा ahash_request *req)
अणु
	flow_log("ahash_hmac_finupl() nbytes:%u\n", req->nbytes);

	वापस ahash_finup(req);
पूर्ण

अटल पूर्णांक ahash_hmac_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा iproc_reqctx_s *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा iproc_ctx_s *ctx = crypto_ahash_ctx(tfm);
	अचिन्हित पूर्णांक blocksize =
			crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	flow_log("ahash_hmac_digest() nbytes:%u\n", req->nbytes);

	/* Perक्रमm initialization and then call finup */
	__ahash_init(req);

	अगर (iproc_priv.spu.spu_type == SPU_TYPE_SPU2) अणु
		/*
		 * SPU2 supports full HMAC implementation in the
		 * hardware, need not to generate IPAD, OPAD and
		 * outer hash in software.
		 * Only क्रम hash key len > hash block size, SPU2
		 * expects to perक्रमm hashing on the key, लघुen
		 * it to digest size and feed it as hash key.
		 */
		rctx->is_sw_hmac = false;
		ctx->auth.mode = HASH_MODE_HMAC;
	पूर्ण अन्यथा अणु
		rctx->is_sw_hmac = true;
		ctx->auth.mode = HASH_MODE_HASH;
		/* start with a prepended ipad */
		स_नकल(rctx->hash_carry, ctx->ipad, blocksize);
		rctx->hash_carry_len = blocksize;
		rctx->total_toकरो += blocksize;
	पूर्ण

	वापस __ahash_finup(req);
पूर्ण

/* aead helpers */

अटल पूर्णांक aead_need_fallback(काष्ठा aead_request *req)
अणु
	काष्ठा iproc_reqctx_s *rctx = aead_request_ctx(req);
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा iproc_ctx_s *ctx = crypto_aead_ctx(aead);
	u32 payload_len;

	/*
	 * SPU hardware cannot handle the AES-GCM/CCM हाल where plaपूर्णांकext
	 * and AAD are both 0 bytes दीर्घ. So use fallback in this हाल.
	 */
	अगर (((ctx->cipher.mode == CIPHER_MODE_GCM) ||
	     (ctx->cipher.mode == CIPHER_MODE_CCM)) &&
	    (req->assoclen == 0)) अणु
		अगर ((rctx->is_encrypt && (req->cryptlen == 0)) ||
		    (!rctx->is_encrypt && (req->cryptlen == ctx->digestsize))) अणु
			flow_log("AES GCM/CCM needs fallback for 0 len req\n");
			वापस 1;
		पूर्ण
	पूर्ण

	/* SPU-M hardware only supports CCM digest size of 8, 12, or 16 bytes */
	अगर ((ctx->cipher.mode == CIPHER_MODE_CCM) &&
	    (spu->spu_type == SPU_TYPE_SPUM) &&
	    (ctx->digestsize != 8) && (ctx->digestsize != 12) &&
	    (ctx->digestsize != 16)) अणु
		flow_log("%s() AES CCM needs fallback for digest size %d\n",
			 __func__, ctx->digestsize);
		वापस 1;
	पूर्ण

	/*
	 * SPU-M on NSP has an issue where AES-CCM hash is not correct
	 * when AAD size is 0
	 */
	अगर ((ctx->cipher.mode == CIPHER_MODE_CCM) &&
	    (spu->spu_subtype == SPU_SUBTYPE_SPUM_NSP) &&
	    (req->assoclen == 0)) अणु
		flow_log("%s() AES_CCM needs fallback for 0 len AAD on NSP\n",
			 __func__);
		वापस 1;
	पूर्ण

	/*
	 * RFC4106 and RFC4543 cannot handle the हाल where AAD is other than
	 * 16 or 20 bytes दीर्घ. So use fallback in this हाल.
	 */
	अगर (ctx->cipher.mode == CIPHER_MODE_GCM &&
	    ctx->cipher.alg == CIPHER_ALG_AES &&
	    rctx->iv_ctr_len == GCM_RFC4106_IV_SIZE &&
	    req->assoclen != 16 && req->assoclen != 20) अणु
		flow_log("RFC4106/RFC4543 needs fallback for assoclen"
			 " other than 16 or 20 bytes\n");
		वापस 1;
	पूर्ण

	payload_len = req->cryptlen;
	अगर (spu->spu_type == SPU_TYPE_SPUM)
		payload_len += req->assoclen;

	flow_log("%s() payload len: %u\n", __func__, payload_len);

	अगर (ctx->max_payload == SPU_MAX_PAYLOAD_INF)
		वापस 0;
	अन्यथा
		वापस payload_len > ctx->max_payload;
पूर्ण

अटल व्योम aead_complete(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा aead_request *req =
	    container_of(areq, काष्ठा aead_request, base);
	काष्ठा iproc_reqctx_s *rctx = aead_request_ctx(req);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);

	flow_log("%s() err:%d\n", __func__, err);

	areq->tfm = crypto_aead_tfm(aead);

	areq->complete = rctx->old_complete;
	areq->data = rctx->old_data;

	areq->complete(areq, err);
पूर्ण

अटल पूर्णांक aead_करो_fallback(काष्ठा aead_request *req, bool is_encrypt)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(aead);
	काष्ठा iproc_reqctx_s *rctx = aead_request_ctx(req);
	काष्ठा iproc_ctx_s *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक err;
	u32 req_flags;

	flow_log("%s() enc:%u\n", __func__, is_encrypt);

	अगर (ctx->fallback_cipher) अणु
		/* Store the cipher tfm and then use the fallback tfm */
		rctx->old_tfm = tfm;
		aead_request_set_tfm(req, ctx->fallback_cipher);
		/*
		 * Save the callback and chain ourselves in, so we can restore
		 * the tfm
		 */
		rctx->old_complete = req->base.complete;
		rctx->old_data = req->base.data;
		req_flags = aead_request_flags(req);
		aead_request_set_callback(req, req_flags, aead_complete, req);
		err = is_encrypt ? crypto_aead_encrypt(req) :
		    crypto_aead_decrypt(req);

		अगर (err == 0) अणु
			/*
			 * fallback was synchronous (did not वापस
			 * -EINPROGRESS). So restore request state here.
			 */
			aead_request_set_callback(req, req_flags,
						  rctx->old_complete, req);
			req->base.data = rctx->old_data;
			aead_request_set_tfm(req, aead);
			flow_log("%s() fallback completed successfully\n\n",
				 __func__);
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक aead_enqueue(काष्ठा aead_request *req, bool is_encrypt)
अणु
	काष्ठा iproc_reqctx_s *rctx = aead_request_ctx(req);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा iproc_ctx_s *ctx = crypto_aead_ctx(aead);
	पूर्णांक err;

	flow_log("%s() enc:%u\n", __func__, is_encrypt);

	अगर (req->assoclen > MAX_ASSOC_SIZE) अणु
		pr_err
		    ("%s() Error: associated data too long. (%u > %u bytes)\n",
		     __func__, req->assoclen, MAX_ASSOC_SIZE);
		वापस -EINVAL;
	पूर्ण

	rctx->gfp = (req->base.flags & (CRYPTO_TFM_REQ_MAY_BACKLOG |
		       CRYPTO_TFM_REQ_MAY_SLEEP)) ? GFP_KERNEL : GFP_ATOMIC;
	rctx->parent = &req->base;
	rctx->is_encrypt = is_encrypt;
	rctx->bd_suppress = false;
	rctx->total_toकरो = req->cryptlen;
	rctx->src_sent = 0;
	rctx->total_sent = 0;
	rctx->total_received = 0;
	rctx->is_sw_hmac = false;
	rctx->ctx = ctx;
	स_रखो(&rctx->mb_mssg, 0, माप(काष्ठा brcm_message));

	/* assoc data is at start of src sg */
	rctx->assoc = req->src;

	/*
	 * Init current position in src scatterlist to be after assoc data.
	 * src_skip set to buffer offset where data begins. (Assoc data could
	 * end in the middle of a buffer.)
	 */
	अगर (spu_sg_at_offset(req->src, req->assoclen, &rctx->src_sg,
			     &rctx->src_skip) < 0) अणु
		pr_err("%s() Error: Unable to find start of src data\n",
		       __func__);
		वापस -EINVAL;
	पूर्ण

	rctx->src_nents = 0;
	rctx->dst_nents = 0;
	अगर (req->dst == req->src) अणु
		rctx->dst_sg = rctx->src_sg;
		rctx->dst_skip = rctx->src_skip;
	पूर्ण अन्यथा अणु
		/*
		 * Expect req->dst to have room क्रम assoc data followed by
		 * output data and ICV, अगर encrypt. So initialize dst_sg
		 * to poपूर्णांक beyond assoc len offset.
		 */
		अगर (spu_sg_at_offset(req->dst, req->assoclen, &rctx->dst_sg,
				     &rctx->dst_skip) < 0) अणु
			pr_err("%s() Error: Unable to find start of dst data\n",
			       __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (ctx->cipher.mode == CIPHER_MODE_CBC ||
	    ctx->cipher.mode == CIPHER_MODE_CTR ||
	    ctx->cipher.mode == CIPHER_MODE_OFB ||
	    ctx->cipher.mode == CIPHER_MODE_XTS ||
	    ctx->cipher.mode == CIPHER_MODE_GCM) अणु
		rctx->iv_ctr_len =
			ctx->salt_len +
			crypto_aead_ivsize(crypto_aead_reqtfm(req));
	पूर्ण अन्यथा अगर (ctx->cipher.mode == CIPHER_MODE_CCM) अणु
		rctx->iv_ctr_len = CCM_AES_IV_SIZE;
	पूर्ण अन्यथा अणु
		rctx->iv_ctr_len = 0;
	पूर्ण

	rctx->hash_carry_len = 0;

	flow_log("  src sg: %p\n", req->src);
	flow_log("  rctx->src_sg: %p, src_skip %u\n",
		 rctx->src_sg, rctx->src_skip);
	flow_log("  assoc:  %p, assoclen %u\n", rctx->assoc, req->assoclen);
	flow_log("  dst sg: %p\n", req->dst);
	flow_log("  rctx->dst_sg: %p, dst_skip %u\n",
		 rctx->dst_sg, rctx->dst_skip);
	flow_log("  iv_ctr_len:%u\n", rctx->iv_ctr_len);
	flow_dump("  iv: ", req->iv, rctx->iv_ctr_len);
	flow_log("  authkeylen:%u\n", ctx->authkeylen);
	flow_log("  is_esp: %s\n", ctx->is_esp ? "yes" : "no");

	अगर (ctx->max_payload == SPU_MAX_PAYLOAD_INF)
		flow_log("  max_payload infinite");
	अन्यथा
		flow_log("  max_payload: %u\n", ctx->max_payload);

	अगर (unlikely(aead_need_fallback(req)))
		वापस aead_करो_fallback(req, is_encrypt);

	/*
	 * Do memory allocations क्रम request after fallback check, because अगर we
	 * करो fallback, we won't call finish_req() to dealloc.
	 */
	अगर (rctx->iv_ctr_len) अणु
		अगर (ctx->salt_len)
			स_नकल(rctx->msg_buf.iv_ctr + ctx->salt_offset,
			       ctx->salt, ctx->salt_len);
		स_नकल(rctx->msg_buf.iv_ctr + ctx->salt_offset + ctx->salt_len,
		       req->iv,
		       rctx->iv_ctr_len - ctx->salt_len - ctx->salt_offset);
	पूर्ण

	rctx->chan_idx = select_channel();
	err = handle_aead_req(rctx);
	अगर (err != -EINPROGRESS)
		/* synchronous result */
		spu_chunk_cleanup(rctx);

	वापस err;
पूर्ण

अटल पूर्णांक aead_authenc_setkey(काष्ठा crypto_aead *cipher,
			       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा iproc_ctx_s *ctx = crypto_aead_ctx(cipher);
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(cipher);
	काष्ठा crypto_authenc_keys keys;
	पूर्णांक ret;

	flow_log("%s() aead:%p key:%p keylen:%u\n", __func__, cipher, key,
		 keylen);
	flow_dump("  key: ", key, keylen);

	ret = crypto_authenc_extractkeys(&keys, key, keylen);
	अगर (ret)
		जाओ badkey;

	अगर (keys.enckeylen > MAX_KEY_SIZE ||
	    keys.authkeylen > MAX_KEY_SIZE)
		जाओ badkey;

	ctx->enckeylen = keys.enckeylen;
	ctx->authkeylen = keys.authkeylen;

	स_नकल(ctx->enckey, keys.enckey, keys.enckeylen);
	/* May end up padding auth key. So make sure it's zeroed. */
	स_रखो(ctx->authkey, 0, माप(ctx->authkey));
	स_नकल(ctx->authkey, keys.authkey, keys.authkeylen);

	चयन (ctx->alg->cipher_info.alg) अणु
	हाल CIPHER_ALG_DES:
		अगर (verअगरy_aead_des_key(cipher, keys.enckey, keys.enckeylen))
			वापस -EINVAL;

		ctx->cipher_type = CIPHER_TYPE_DES;
		अवरोध;
	हाल CIPHER_ALG_3DES:
		अगर (verअगरy_aead_des3_key(cipher, keys.enckey, keys.enckeylen))
			वापस -EINVAL;

		ctx->cipher_type = CIPHER_TYPE_3DES;
		अवरोध;
	हाल CIPHER_ALG_AES:
		चयन (ctx->enckeylen) अणु
		हाल AES_KEYSIZE_128:
			ctx->cipher_type = CIPHER_TYPE_AES128;
			अवरोध;
		हाल AES_KEYSIZE_192:
			ctx->cipher_type = CIPHER_TYPE_AES192;
			अवरोध;
		हाल AES_KEYSIZE_256:
			ctx->cipher_type = CIPHER_TYPE_AES256;
			अवरोध;
		शेष:
			जाओ badkey;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("%s() Error: Unknown cipher alg\n", __func__);
		वापस -EINVAL;
	पूर्ण

	flow_log("  enckeylen:%u authkeylen:%u\n", ctx->enckeylen,
		 ctx->authkeylen);
	flow_dump("  enc: ", ctx->enckey, ctx->enckeylen);
	flow_dump("  auth: ", ctx->authkey, ctx->authkeylen);

	/* setkey the fallback just in हाल we needto use it */
	अगर (ctx->fallback_cipher) अणु
		flow_log("  running fallback setkey()\n");

		ctx->fallback_cipher->base.crt_flags &= ~CRYPTO_TFM_REQ_MASK;
		ctx->fallback_cipher->base.crt_flags |=
		    tfm->crt_flags & CRYPTO_TFM_REQ_MASK;
		ret = crypto_aead_setkey(ctx->fallback_cipher, key, keylen);
		अगर (ret)
			flow_log("  fallback setkey() returned:%d\n", ret);
	पूर्ण

	ctx->spu_resp_hdr_len = spu->spu_response_hdr_len(ctx->authkeylen,
							  ctx->enckeylen,
							  false);

	atomic_inc(&iproc_priv.setkey_cnt[SPU_OP_AEAD]);

	वापस ret;

badkey:
	ctx->enckeylen = 0;
	ctx->authkeylen = 0;
	ctx->digestsize = 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक aead_gcm_ccm_setkey(काष्ठा crypto_aead *cipher,
			       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा iproc_ctx_s *ctx = crypto_aead_ctx(cipher);
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(cipher);

	पूर्णांक ret = 0;

	flow_log("%s() keylen:%u\n", __func__, keylen);
	flow_dump("  key: ", key, keylen);

	अगर (!ctx->is_esp)
		ctx->digestsize = keylen;

	ctx->enckeylen = keylen;
	ctx->authkeylen = 0;

	चयन (ctx->enckeylen) अणु
	हाल AES_KEYSIZE_128:
		ctx->cipher_type = CIPHER_TYPE_AES128;
		अवरोध;
	हाल AES_KEYSIZE_192:
		ctx->cipher_type = CIPHER_TYPE_AES192;
		अवरोध;
	हाल AES_KEYSIZE_256:
		ctx->cipher_type = CIPHER_TYPE_AES256;
		अवरोध;
	शेष:
		जाओ badkey;
	पूर्ण

	स_नकल(ctx->enckey, key, ctx->enckeylen);

	flow_log("  enckeylen:%u authkeylen:%u\n", ctx->enckeylen,
		 ctx->authkeylen);
	flow_dump("  enc: ", ctx->enckey, ctx->enckeylen);
	flow_dump("  auth: ", ctx->authkey, ctx->authkeylen);

	/* setkey the fallback just in हाल we need to use it */
	अगर (ctx->fallback_cipher) अणु
		flow_log("  running fallback setkey()\n");

		ctx->fallback_cipher->base.crt_flags &= ~CRYPTO_TFM_REQ_MASK;
		ctx->fallback_cipher->base.crt_flags |=
		    tfm->crt_flags & CRYPTO_TFM_REQ_MASK;
		ret = crypto_aead_setkey(ctx->fallback_cipher, key,
					 keylen + ctx->salt_len);
		अगर (ret)
			flow_log("  fallback setkey() returned:%d\n", ret);
	पूर्ण

	ctx->spu_resp_hdr_len = spu->spu_response_hdr_len(ctx->authkeylen,
							  ctx->enckeylen,
							  false);

	atomic_inc(&iproc_priv.setkey_cnt[SPU_OP_AEAD]);

	flow_log("  enckeylen:%u authkeylen:%u\n", ctx->enckeylen,
		 ctx->authkeylen);

	वापस ret;

badkey:
	ctx->enckeylen = 0;
	ctx->authkeylen = 0;
	ctx->digestsize = 0;

	वापस -EINVAL;
पूर्ण

/**
 * aead_gcm_esp_setkey() - setkey() operation क्रम ESP variant of GCM AES.
 * @cipher: AEAD काष्ठाure
 * @key:    Key followed by 4 bytes of salt
 * @keylen: Length of key plus salt, in bytes
 *
 * Extracts salt from key and stores it to be prepended to IV on each request.
 * Digest is always 16 bytes
 *
 * Return: Value from generic gcm setkey.
 */
अटल पूर्णांक aead_gcm_esp_setkey(काष्ठा crypto_aead *cipher,
			       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा iproc_ctx_s *ctx = crypto_aead_ctx(cipher);

	flow_log("%s\n", __func__);

	अगर (keylen < GCM_ESP_SALT_SIZE)
		वापस -EINVAL;

	ctx->salt_len = GCM_ESP_SALT_SIZE;
	ctx->salt_offset = GCM_ESP_SALT_OFFSET;
	स_नकल(ctx->salt, key + keylen - GCM_ESP_SALT_SIZE, GCM_ESP_SALT_SIZE);
	keylen -= GCM_ESP_SALT_SIZE;
	ctx->digestsize = GCM_ESP_DIGESTSIZE;
	ctx->is_esp = true;
	flow_dump("salt: ", ctx->salt, GCM_ESP_SALT_SIZE);

	वापस aead_gcm_ccm_setkey(cipher, key, keylen);
पूर्ण

/**
 * rfc4543_gcm_esp_setkey() - setkey operation क्रम RFC4543 variant of GCM/GMAC.
 * @cipher: AEAD काष्ठाure
 * @key:    Key followed by 4 bytes of salt
 * @keylen: Length of key plus salt, in bytes
 *
 * Extracts salt from key and stores it to be prepended to IV on each request.
 * Digest is always 16 bytes
 *
 * Return: Value from generic gcm setkey.
 */
अटल पूर्णांक rfc4543_gcm_esp_setkey(काष्ठा crypto_aead *cipher,
				  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा iproc_ctx_s *ctx = crypto_aead_ctx(cipher);

	flow_log("%s\n", __func__);

	अगर (keylen < GCM_ESP_SALT_SIZE)
		वापस -EINVAL;

	ctx->salt_len = GCM_ESP_SALT_SIZE;
	ctx->salt_offset = GCM_ESP_SALT_OFFSET;
	स_नकल(ctx->salt, key + keylen - GCM_ESP_SALT_SIZE, GCM_ESP_SALT_SIZE);
	keylen -= GCM_ESP_SALT_SIZE;
	ctx->digestsize = GCM_ESP_DIGESTSIZE;
	ctx->is_esp = true;
	ctx->is_rfc4543 = true;
	flow_dump("salt: ", ctx->salt, GCM_ESP_SALT_SIZE);

	वापस aead_gcm_ccm_setkey(cipher, key, keylen);
पूर्ण

/**
 * aead_ccm_esp_setkey() - setkey() operation क्रम ESP variant of CCM AES.
 * @cipher: AEAD काष्ठाure
 * @key:    Key followed by 4 bytes of salt
 * @keylen: Length of key plus salt, in bytes
 *
 * Extracts salt from key and stores it to be prepended to IV on each request.
 * Digest is always 16 bytes
 *
 * Return: Value from generic ccm setkey.
 */
अटल पूर्णांक aead_ccm_esp_setkey(काष्ठा crypto_aead *cipher,
			       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा iproc_ctx_s *ctx = crypto_aead_ctx(cipher);

	flow_log("%s\n", __func__);

	अगर (keylen < CCM_ESP_SALT_SIZE)
		वापस -EINVAL;

	ctx->salt_len = CCM_ESP_SALT_SIZE;
	ctx->salt_offset = CCM_ESP_SALT_OFFSET;
	स_नकल(ctx->salt, key + keylen - CCM_ESP_SALT_SIZE, CCM_ESP_SALT_SIZE);
	keylen -= CCM_ESP_SALT_SIZE;
	ctx->is_esp = true;
	flow_dump("salt: ", ctx->salt, CCM_ESP_SALT_SIZE);

	वापस aead_gcm_ccm_setkey(cipher, key, keylen);
पूर्ण

अटल पूर्णांक aead_setauthsize(काष्ठा crypto_aead *cipher, अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा iproc_ctx_s *ctx = crypto_aead_ctx(cipher);
	पूर्णांक ret = 0;

	flow_log("%s() authkeylen:%u authsize:%u\n",
		 __func__, ctx->authkeylen, authsize);

	ctx->digestsize = authsize;

	/* setkey the fallback just in हाल we needto use it */
	अगर (ctx->fallback_cipher) अणु
		flow_log("  running fallback setauth()\n");

		ret = crypto_aead_setauthsize(ctx->fallback_cipher, authsize);
		अगर (ret)
			flow_log("  fallback setauth() returned:%d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aead_encrypt(काष्ठा aead_request *req)
अणु
	flow_log("%s() cryptlen:%u %08x\n", __func__, req->cryptlen,
		 req->cryptlen);
	dump_sg(req->src, 0, req->cryptlen + req->assoclen);
	flow_log("  assoc_len:%u\n", req->assoclen);

	वापस aead_enqueue(req, true);
पूर्ण

अटल पूर्णांक aead_decrypt(काष्ठा aead_request *req)
अणु
	flow_log("%s() cryptlen:%u\n", __func__, req->cryptlen);
	dump_sg(req->src, 0, req->cryptlen + req->assoclen);
	flow_log("  assoc_len:%u\n", req->assoclen);

	वापस aead_enqueue(req, false);
पूर्ण

/* ==================== Supported Cipher Algorithms ==================== */

अटल काष्ठा iproc_alg_s driver_algs[] = अणु
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "gcm(aes)",
			.cra_driver_name = "gcm-aes-iproc",
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK
		 पूर्ण,
		 .setkey = aead_gcm_ccm_setkey,
		 .ivsize = GCM_AES_IV_SIZE,
		.maxauthsize = AES_BLOCK_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_GCM,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_AES,
		       .mode = HASH_MODE_GCM,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "ccm(aes)",
			.cra_driver_name = "ccm-aes-iproc",
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK
		 पूर्ण,
		 .setkey = aead_gcm_ccm_setkey,
		 .ivsize = CCM_AES_IV_SIZE,
		.maxauthsize = AES_BLOCK_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_CCM,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_AES,
		       .mode = HASH_MODE_CCM,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "rfc4106(gcm(aes))",
			.cra_driver_name = "gcm-aes-esp-iproc",
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK
		 पूर्ण,
		 .setkey = aead_gcm_esp_setkey,
		 .ivsize = GCM_RFC4106_IV_SIZE,
		 .maxauthsize = AES_BLOCK_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_GCM,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_AES,
		       .mode = HASH_MODE_GCM,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "rfc4309(ccm(aes))",
			.cra_driver_name = "ccm-aes-esp-iproc",
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK
		 पूर्ण,
		 .setkey = aead_ccm_esp_setkey,
		 .ivsize = CCM_AES_IV_SIZE,
		 .maxauthsize = AES_BLOCK_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_CCM,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_AES,
		       .mode = HASH_MODE_CCM,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "rfc4543(gcm(aes))",
			.cra_driver_name = "gmac-aes-esp-iproc",
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK
		 पूर्ण,
		 .setkey = rfc4543_gcm_esp_setkey,
		 .ivsize = GCM_RFC4106_IV_SIZE,
		 .maxauthsize = AES_BLOCK_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_GCM,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_AES,
		       .mode = HASH_MODE_GCM,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(md5),cbc(aes))",
			.cra_driver_name = "authenc-hmac-md5-cbc-aes-iproc",
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		.ivsize = AES_BLOCK_SIZE,
		.maxauthsize = MD5_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_MD5,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha1),cbc(aes))",
			.cra_driver_name = "authenc-hmac-sha1-cbc-aes-iproc",
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = AES_BLOCK_SIZE,
		 .maxauthsize = SHA1_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA1,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha256),cbc(aes))",
			.cra_driver_name = "authenc-hmac-sha256-cbc-aes-iproc",
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = AES_BLOCK_SIZE,
		 .maxauthsize = SHA256_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA256,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(md5),cbc(des))",
			.cra_driver_name = "authenc-hmac-md5-cbc-des-iproc",
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BLOCK_SIZE,
		 .maxauthsize = MD5_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_MD5,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha1),cbc(des))",
			.cra_driver_name = "authenc-hmac-sha1-cbc-des-iproc",
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BLOCK_SIZE,
		 .maxauthsize = SHA1_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA1,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha224),cbc(des))",
			.cra_driver_name = "authenc-hmac-sha224-cbc-des-iproc",
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BLOCK_SIZE,
		 .maxauthsize = SHA224_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA224,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha256),cbc(des))",
			.cra_driver_name = "authenc-hmac-sha256-cbc-des-iproc",
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BLOCK_SIZE,
		 .maxauthsize = SHA256_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA256,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha384),cbc(des))",
			.cra_driver_name = "authenc-hmac-sha384-cbc-des-iproc",
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BLOCK_SIZE,
		 .maxauthsize = SHA384_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA384,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha512),cbc(des))",
			.cra_driver_name = "authenc-hmac-sha512-cbc-des-iproc",
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES_BLOCK_SIZE,
		 .maxauthsize = SHA512_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA512,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(md5),cbc(des3_ede))",
			.cra_driver_name = "authenc-hmac-md5-cbc-des3-iproc",
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BLOCK_SIZE,
		 .maxauthsize = MD5_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_3DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_MD5,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha1),cbc(des3_ede))",
			.cra_driver_name = "authenc-hmac-sha1-cbc-des3-iproc",
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BLOCK_SIZE,
		 .maxauthsize = SHA1_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_3DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA1,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha224),cbc(des3_ede))",
			.cra_driver_name = "authenc-hmac-sha224-cbc-des3-iproc",
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BLOCK_SIZE,
		 .maxauthsize = SHA224_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_3DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA224,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha256),cbc(des3_ede))",
			.cra_driver_name = "authenc-hmac-sha256-cbc-des3-iproc",
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BLOCK_SIZE,
		 .maxauthsize = SHA256_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_3DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA256,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha384),cbc(des3_ede))",
			.cra_driver_name = "authenc-hmac-sha384-cbc-des3-iproc",
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BLOCK_SIZE,
		 .maxauthsize = SHA384_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_3DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA384,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AEAD,
	 .alg.aead = अणु
		 .base = अणु
			.cra_name = "authenc(hmac(sha512),cbc(des3_ede))",
			.cra_driver_name = "authenc-hmac-sha512-cbc-des3-iproc",
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				     CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY
		 पूर्ण,
		 .setkey = aead_authenc_setkey,
		 .ivsize = DES3_EDE_BLOCK_SIZE,
		 .maxauthsize = SHA512_DIGEST_SIZE,
	 पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_3DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA512,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 .auth_first = 0,
	 पूर्ण,

/* SKCIPHER algorithms. */
	अणु
	 .type = CRYPTO_ALG_TYPE_SKCIPHER,
	 .alg.skcipher = अणु
			.base.cra_name = "ofb(des)",
			.base.cra_driver_name = "ofb-des-iproc",
			.base.cra_blocksize = DES_BLOCK_SIZE,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = DES_BLOCK_SIZE,
			पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_DES,
			 .mode = CIPHER_MODE_OFB,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_NONE,
		       .mode = HASH_MODE_NONE,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_SKCIPHER,
	 .alg.skcipher = अणु
			.base.cra_name = "cbc(des)",
			.base.cra_driver_name = "cbc-des-iproc",
			.base.cra_blocksize = DES_BLOCK_SIZE,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = DES_BLOCK_SIZE,
			पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_NONE,
		       .mode = HASH_MODE_NONE,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_SKCIPHER,
	 .alg.skcipher = अणु
			.base.cra_name = "ecb(des)",
			.base.cra_driver_name = "ecb-des-iproc",
			.base.cra_blocksize = DES_BLOCK_SIZE,
			.min_keysize = DES_KEY_SIZE,
			.max_keysize = DES_KEY_SIZE,
			.ivsize = 0,
			पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_DES,
			 .mode = CIPHER_MODE_ECB,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_NONE,
		       .mode = HASH_MODE_NONE,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_SKCIPHER,
	 .alg.skcipher = अणु
			.base.cra_name = "ofb(des3_ede)",
			.base.cra_driver_name = "ofb-des3-iproc",
			.base.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_3DES,
			 .mode = CIPHER_MODE_OFB,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_NONE,
		       .mode = HASH_MODE_NONE,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_SKCIPHER,
	 .alg.skcipher = अणु
			.base.cra_name = "cbc(des3_ede)",
			.base.cra_driver_name = "cbc-des3-iproc",
			.base.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = DES3_EDE_BLOCK_SIZE,
			पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_3DES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_NONE,
		       .mode = HASH_MODE_NONE,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_SKCIPHER,
	 .alg.skcipher = अणु
			.base.cra_name = "ecb(des3_ede)",
			.base.cra_driver_name = "ecb-des3-iproc",
			.base.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.min_keysize = DES3_EDE_KEY_SIZE,
			.max_keysize = DES3_EDE_KEY_SIZE,
			.ivsize = 0,
			पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_3DES,
			 .mode = CIPHER_MODE_ECB,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_NONE,
		       .mode = HASH_MODE_NONE,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_SKCIPHER,
	 .alg.skcipher = अणु
			.base.cra_name = "ofb(aes)",
			.base.cra_driver_name = "ofb-aes-iproc",
			.base.cra_blocksize = AES_BLOCK_SIZE,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_OFB,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_NONE,
		       .mode = HASH_MODE_NONE,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_SKCIPHER,
	 .alg.skcipher = अणु
			.base.cra_name = "cbc(aes)",
			.base.cra_driver_name = "cbc-aes-iproc",
			.base.cra_blocksize = AES_BLOCK_SIZE,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_CBC,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_NONE,
		       .mode = HASH_MODE_NONE,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_SKCIPHER,
	 .alg.skcipher = अणु
			.base.cra_name = "ecb(aes)",
			.base.cra_driver_name = "ecb-aes-iproc",
			.base.cra_blocksize = AES_BLOCK_SIZE,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = 0,
			पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_ECB,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_NONE,
		       .mode = HASH_MODE_NONE,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_SKCIPHER,
	 .alg.skcipher = अणु
			.base.cra_name = "ctr(aes)",
			.base.cra_driver_name = "ctr-aes-iproc",
			.base.cra_blocksize = AES_BLOCK_SIZE,
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_CTR,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_NONE,
		       .mode = HASH_MODE_NONE,
		       पूर्ण,
	 पूर्ण,
अणु
	 .type = CRYPTO_ALG_TYPE_SKCIPHER,
	 .alg.skcipher = अणु
			.base.cra_name = "xts(aes)",
			.base.cra_driver_name = "xts-aes-iproc",
			.base.cra_blocksize = AES_BLOCK_SIZE,
			.min_keysize = 2 * AES_MIN_KEY_SIZE,
			.max_keysize = 2 * AES_MAX_KEY_SIZE,
			.ivsize = AES_BLOCK_SIZE,
			पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_AES,
			 .mode = CIPHER_MODE_XTS,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_NONE,
		       .mode = HASH_MODE_NONE,
		       पूर्ण,
	 पूर्ण,

/* AHASH algorithms. */
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = MD5_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "md5",
				    .cra_driver_name = "md5-iproc",
				    .cra_blocksize = MD5_BLOCK_WORDS * 4,
				    .cra_flags = CRYPTO_ALG_ASYNC |
						 CRYPTO_ALG_ALLOCATES_MEMORY,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_MD5,
		       .mode = HASH_MODE_HASH,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = MD5_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "hmac(md5)",
				    .cra_driver_name = "hmac-md5-iproc",
				    .cra_blocksize = MD5_BLOCK_WORDS * 4,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_MD5,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 पूर्ण,
	अणु.type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA1_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "sha1",
				    .cra_driver_name = "sha1-iproc",
				    .cra_blocksize = SHA1_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA1,
		       .mode = HASH_MODE_HASH,
		       पूर्ण,
	 पूर्ण,
	अणु.type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA1_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "hmac(sha1)",
				    .cra_driver_name = "hmac-sha1-iproc",
				    .cra_blocksize = SHA1_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA1,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 पूर्ण,
	अणु.type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
			.halg.digestsize = SHA224_DIGEST_SIZE,
			.halg.base = अणु
				    .cra_name = "sha224",
				    .cra_driver_name = "sha224-iproc",
				    .cra_blocksize = SHA224_BLOCK_SIZE,
			पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA224,
		       .mode = HASH_MODE_HASH,
		       पूर्ण,
	 पूर्ण,
	अणु.type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA224_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "hmac(sha224)",
				    .cra_driver_name = "hmac-sha224-iproc",
				    .cra_blocksize = SHA224_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA224,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 पूर्ण,
	अणु.type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA256_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "sha256",
				    .cra_driver_name = "sha256-iproc",
				    .cra_blocksize = SHA256_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA256,
		       .mode = HASH_MODE_HASH,
		       पूर्ण,
	 पूर्ण,
	अणु.type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA256_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "hmac(sha256)",
				    .cra_driver_name = "hmac-sha256-iproc",
				    .cra_blocksize = SHA256_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA256,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 पूर्ण,
	अणु
	.type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA384_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "sha384",
				    .cra_driver_name = "sha384-iproc",
				    .cra_blocksize = SHA384_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA384,
		       .mode = HASH_MODE_HASH,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA384_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "hmac(sha384)",
				    .cra_driver_name = "hmac-sha384-iproc",
				    .cra_blocksize = SHA384_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA384,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA512_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "sha512",
				    .cra_driver_name = "sha512-iproc",
				    .cra_blocksize = SHA512_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA512,
		       .mode = HASH_MODE_HASH,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA512_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "hmac(sha512)",
				    .cra_driver_name = "hmac-sha512-iproc",
				    .cra_blocksize = SHA512_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA512,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA3_224_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "sha3-224",
				    .cra_driver_name = "sha3-224-iproc",
				    .cra_blocksize = SHA3_224_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA3_224,
		       .mode = HASH_MODE_HASH,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA3_224_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "hmac(sha3-224)",
				    .cra_driver_name = "hmac-sha3-224-iproc",
				    .cra_blocksize = SHA3_224_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA3_224,
		       .mode = HASH_MODE_HMAC
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA3_256_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "sha3-256",
				    .cra_driver_name = "sha3-256-iproc",
				    .cra_blocksize = SHA3_256_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA3_256,
		       .mode = HASH_MODE_HASH,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA3_256_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "hmac(sha3-256)",
				    .cra_driver_name = "hmac-sha3-256-iproc",
				    .cra_blocksize = SHA3_256_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA3_256,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA3_384_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "sha3-384",
				    .cra_driver_name = "sha3-384-iproc",
				    .cra_blocksize = SHA3_224_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA3_384,
		       .mode = HASH_MODE_HASH,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA3_384_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "hmac(sha3-384)",
				    .cra_driver_name = "hmac-sha3-384-iproc",
				    .cra_blocksize = SHA3_384_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA3_384,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA3_512_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "sha3-512",
				    .cra_driver_name = "sha3-512-iproc",
				    .cra_blocksize = SHA3_512_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA3_512,
		       .mode = HASH_MODE_HASH,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = SHA3_512_DIGEST_SIZE,
		      .halg.base = अणु
				    .cra_name = "hmac(sha3-512)",
				    .cra_driver_name = "hmac-sha3-512-iproc",
				    .cra_blocksize = SHA3_512_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_SHA3_512,
		       .mode = HASH_MODE_HMAC,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = AES_BLOCK_SIZE,
		      .halg.base = अणु
				    .cra_name = "xcbc(aes)",
				    .cra_driver_name = "xcbc-aes-iproc",
				    .cra_blocksize = AES_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_AES,
		       .mode = HASH_MODE_XCBC,
		       पूर्ण,
	 पूर्ण,
	अणु
	 .type = CRYPTO_ALG_TYPE_AHASH,
	 .alg.hash = अणु
		      .halg.digestsize = AES_BLOCK_SIZE,
		      .halg.base = अणु
				    .cra_name = "cmac(aes)",
				    .cra_driver_name = "cmac-aes-iproc",
				    .cra_blocksize = AES_BLOCK_SIZE,
				पूर्ण
		      पूर्ण,
	 .cipher_info = अणु
			 .alg = CIPHER_ALG_NONE,
			 .mode = CIPHER_MODE_NONE,
			 पूर्ण,
	 .auth_info = अणु
		       .alg = HASH_ALG_AES,
		       .mode = HASH_MODE_CMAC,
		       पूर्ण,
	 पूर्ण,
पूर्ण;

अटल पूर्णांक generic_cra_init(काष्ठा crypto_tfm *tfm,
			    काष्ठा iproc_alg_s *cipher_alg)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा iproc_ctx_s *ctx = crypto_tfm_ctx(tfm);
	अचिन्हित पूर्णांक blocksize = crypto_tfm_alg_blocksize(tfm);

	flow_log("%s()\n", __func__);

	ctx->alg = cipher_alg;
	ctx->cipher = cipher_alg->cipher_info;
	ctx->auth = cipher_alg->auth_info;
	ctx->auth_first = cipher_alg->auth_first;
	ctx->max_payload = spu->spu_ctx_max_payload(ctx->cipher.alg,
						    ctx->cipher.mode,
						    blocksize);
	ctx->fallback_cipher = शून्य;

	ctx->enckeylen = 0;
	ctx->authkeylen = 0;

	atomic_inc(&iproc_priv.stream_count);
	atomic_inc(&iproc_priv.session_count);

	वापस 0;
पूर्ण

अटल पूर्णांक skcipher_init_tfm(काष्ठा crypto_skcipher *skcipher)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(skcipher);
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(skcipher);
	काष्ठा iproc_alg_s *cipher_alg;

	flow_log("%s()\n", __func__);

	crypto_skcipher_set_reqsize(skcipher, माप(काष्ठा iproc_reqctx_s));

	cipher_alg = container_of(alg, काष्ठा iproc_alg_s, alg.skcipher);
	वापस generic_cra_init(tfm, cipher_alg);
पूर्ण

अटल पूर्णांक ahash_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	पूर्णांक err;
	काष्ठा crypto_alg *alg = tfm->__crt_alg;
	काष्ठा iproc_alg_s *cipher_alg;

	cipher_alg = container_of(__crypto_ahash_alg(alg), काष्ठा iproc_alg_s,
				  alg.hash);

	err = generic_cra_init(tfm, cipher_alg);
	flow_log("%s()\n", __func__);

	/*
	 * export state size has to be < 512 bytes. So करोn't include msg bufs
	 * in state size.
	 */
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा iproc_reqctx_s));

	वापस err;
पूर्ण

अटल पूर्णांक aead_cra_init(काष्ठा crypto_aead *aead)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(aead);
	काष्ठा iproc_ctx_s *ctx = crypto_tfm_ctx(tfm);
	काष्ठा crypto_alg *alg = tfm->__crt_alg;
	काष्ठा aead_alg *aalg = container_of(alg, काष्ठा aead_alg, base);
	काष्ठा iproc_alg_s *cipher_alg = container_of(aalg, काष्ठा iproc_alg_s,
						      alg.aead);

	पूर्णांक err = generic_cra_init(tfm, cipher_alg);

	flow_log("%s()\n", __func__);

	crypto_aead_set_reqsize(aead, माप(काष्ठा iproc_reqctx_s));
	ctx->is_esp = false;
	ctx->salt_len = 0;
	ctx->salt_offset = 0;

	/* अक्रमom first IV */
	get_अक्रमom_bytes(ctx->iv, MAX_IV_SIZE);
	flow_dump("  iv: ", ctx->iv, MAX_IV_SIZE);

	अगर (!err) अणु
		अगर (alg->cra_flags & CRYPTO_ALG_NEED_FALLBACK) अणु
			flow_log("%s() creating fallback cipher\n", __func__);

			ctx->fallback_cipher =
			    crypto_alloc_aead(alg->cra_name, 0,
					      CRYPTO_ALG_ASYNC |
					      CRYPTO_ALG_NEED_FALLBACK);
			अगर (IS_ERR(ctx->fallback_cipher)) अणु
				pr_err("%s() Error: failed to allocate fallback for %s\n",
				       __func__, alg->cra_name);
				वापस PTR_ERR(ctx->fallback_cipher);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम generic_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	atomic_dec(&iproc_priv.session_count);
पूर्ण

अटल व्योम skcipher_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	generic_cra_निकास(crypto_skcipher_tfm(tfm));
पूर्ण

अटल व्योम aead_cra_निकास(काष्ठा crypto_aead *aead)
अणु
	काष्ठा crypto_tfm *tfm = crypto_aead_tfm(aead);
	काष्ठा iproc_ctx_s *ctx = crypto_tfm_ctx(tfm);

	generic_cra_निकास(tfm);

	अगर (ctx->fallback_cipher) अणु
		crypto_मुक्त_aead(ctx->fallback_cipher);
		ctx->fallback_cipher = शून्य;
	पूर्ण
पूर्ण

/**
 * spu_functions_रेजिस्टर() - Specअगरy hardware-specअगरic SPU functions based on
 * SPU type पढ़ो from device tree.
 * @dev:	device काष्ठाure
 * @spu_type:	SPU hardware generation
 * @spu_subtype: SPU hardware version
 */
अटल व्योम spu_functions_रेजिस्टर(काष्ठा device *dev,
				   क्रमागत spu_spu_type spu_type,
				   क्रमागत spu_spu_subtype spu_subtype)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;

	अगर (spu_type == SPU_TYPE_SPUM) अणु
		dev_dbg(dev, "Registering SPUM functions");
		spu->spu_dump_msg_hdr = spum_dump_msg_hdr;
		spu->spu_payload_length = spum_payload_length;
		spu->spu_response_hdr_len = spum_response_hdr_len;
		spu->spu_hash_pad_len = spum_hash_pad_len;
		spu->spu_gcm_ccm_pad_len = spum_gcm_ccm_pad_len;
		spu->spu_assoc_resp_len = spum_assoc_resp_len;
		spu->spu_aead_ivlen = spum_aead_ivlen;
		spu->spu_hash_type = spum_hash_type;
		spu->spu_digest_size = spum_digest_size;
		spu->spu_create_request = spum_create_request;
		spu->spu_cipher_req_init = spum_cipher_req_init;
		spu->spu_cipher_req_finish = spum_cipher_req_finish;
		spu->spu_request_pad = spum_request_pad;
		spu->spu_tx_status_len = spum_tx_status_len;
		spu->spu_rx_status_len = spum_rx_status_len;
		spu->spu_status_process = spum_status_process;
		spu->spu_xts_tweak_in_payload = spum_xts_tweak_in_payload;
		spu->spu_ccm_update_iv = spum_ccm_update_iv;
		spu->spu_wordalign_padlen = spum_wordalign_padlen;
		अगर (spu_subtype == SPU_SUBTYPE_SPUM_NS2)
			spu->spu_ctx_max_payload = spum_ns2_ctx_max_payload;
		अन्यथा
			spu->spu_ctx_max_payload = spum_nsp_ctx_max_payload;
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "Registering SPU2 functions");
		spu->spu_dump_msg_hdr = spu2_dump_msg_hdr;
		spu->spu_ctx_max_payload = spu2_ctx_max_payload;
		spu->spu_payload_length = spu2_payload_length;
		spu->spu_response_hdr_len = spu2_response_hdr_len;
		spu->spu_hash_pad_len = spu2_hash_pad_len;
		spu->spu_gcm_ccm_pad_len = spu2_gcm_ccm_pad_len;
		spu->spu_assoc_resp_len = spu2_assoc_resp_len;
		spu->spu_aead_ivlen = spu2_aead_ivlen;
		spu->spu_hash_type = spu2_hash_type;
		spu->spu_digest_size = spu2_digest_size;
		spu->spu_create_request = spu2_create_request;
		spu->spu_cipher_req_init = spu2_cipher_req_init;
		spu->spu_cipher_req_finish = spu2_cipher_req_finish;
		spu->spu_request_pad = spu2_request_pad;
		spu->spu_tx_status_len = spu2_tx_status_len;
		spu->spu_rx_status_len = spu2_rx_status_len;
		spu->spu_status_process = spu2_status_process;
		spu->spu_xts_tweak_in_payload = spu2_xts_tweak_in_payload;
		spu->spu_ccm_update_iv = spu2_ccm_update_iv;
		spu->spu_wordalign_padlen = spu2_wordalign_padlen;
	पूर्ण
पूर्ण

/**
 * spu_mb_init() - Initialize mailbox client. Request ownership of a mailbox
 * channel क्रम the SPU being probed.
 * @dev:  SPU driver device काष्ठाure
 *
 * Return: 0 अगर successful
 *	   < 0 otherwise
 */
अटल पूर्णांक spu_mb_init(काष्ठा device *dev)
अणु
	काष्ठा mbox_client *mcl = &iproc_priv.mcl;
	पूर्णांक err, i;

	iproc_priv.mbox = devm_kसुस्मृति(dev, iproc_priv.spu.num_chan,
				  माप(काष्ठा mbox_chan *), GFP_KERNEL);
	अगर (!iproc_priv.mbox)
		वापस -ENOMEM;

	mcl->dev = dev;
	mcl->tx_block = false;
	mcl->tx_tout = 0;
	mcl->knows_txकरोne = true;
	mcl->rx_callback = spu_rx_callback;
	mcl->tx_करोne = शून्य;

	क्रम (i = 0; i < iproc_priv.spu.num_chan; i++) अणु
		iproc_priv.mbox[i] = mbox_request_channel(mcl, i);
		अगर (IS_ERR(iproc_priv.mbox[i])) अणु
			err = PTR_ERR(iproc_priv.mbox[i]);
			dev_err(dev,
				"Mbox channel %d request failed with err %d",
				i, err);
			iproc_priv.mbox[i] = शून्य;
			जाओ मुक्त_channels;
		पूर्ण
	पूर्ण

	वापस 0;
मुक्त_channels:
	क्रम (i = 0; i < iproc_priv.spu.num_chan; i++) अणु
		अगर (iproc_priv.mbox[i])
			mbox_मुक्त_channel(iproc_priv.mbox[i]);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम spu_mb_release(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < iproc_priv.spu.num_chan; i++)
		mbox_मुक्त_channel(iproc_priv.mbox[i]);
पूर्ण

अटल व्योम spu_counters_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक j;

	atomic_set(&iproc_priv.session_count, 0);
	atomic_set(&iproc_priv.stream_count, 0);
	atomic_set(&iproc_priv.next_chan, (पूर्णांक)iproc_priv.spu.num_chan);
	atomic64_set(&iproc_priv.bytes_in, 0);
	atomic64_set(&iproc_priv.bytes_out, 0);
	क्रम (i = 0; i < SPU_OP_NUM; i++) अणु
		atomic_set(&iproc_priv.op_counts[i], 0);
		atomic_set(&iproc_priv.setkey_cnt[i], 0);
	पूर्ण
	क्रम (i = 0; i < CIPHER_ALG_LAST; i++)
		क्रम (j = 0; j < CIPHER_MODE_LAST; j++)
			atomic_set(&iproc_priv.cipher_cnt[i][j], 0);

	क्रम (i = 0; i < HASH_ALG_LAST; i++) अणु
		atomic_set(&iproc_priv.hash_cnt[i], 0);
		atomic_set(&iproc_priv.hmac_cnt[i], 0);
	पूर्ण
	क्रम (i = 0; i < AEAD_TYPE_LAST; i++)
		atomic_set(&iproc_priv.aead_cnt[i], 0);

	atomic_set(&iproc_priv.mb_no_spc, 0);
	atomic_set(&iproc_priv.mb_send_fail, 0);
	atomic_set(&iproc_priv.bad_icv, 0);
पूर्ण

अटल पूर्णांक spu_रेजिस्टर_skcipher(काष्ठा iproc_alg_s *driver_alg)
अणु
	काष्ठा skcipher_alg *crypto = &driver_alg->alg.skcipher;
	पूर्णांक err;

	crypto->base.cra_module = THIS_MODULE;
	crypto->base.cra_priority = cipher_pri;
	crypto->base.cra_alignmask = 0;
	crypto->base.cra_ctxsize = माप(काष्ठा iproc_ctx_s);
	crypto->base.cra_flags = CRYPTO_ALG_ASYNC |
				 CRYPTO_ALG_ALLOCATES_MEMORY |
				 CRYPTO_ALG_KERN_DRIVER_ONLY;

	crypto->init = skcipher_init_tfm;
	crypto->निकास = skcipher_निकास_tfm;
	crypto->setkey = skcipher_setkey;
	crypto->encrypt = skcipher_encrypt;
	crypto->decrypt = skcipher_decrypt;

	err = crypto_रेजिस्टर_skcipher(crypto);
	/* Mark alg as having been रेजिस्टरed, अगर successful */
	अगर (err == 0)
		driver_alg->रेजिस्टरed = true;
	pr_debug("  registered skcipher %s\n", crypto->base.cra_driver_name);
	वापस err;
पूर्ण

अटल पूर्णांक spu_रेजिस्टर_ahash(काष्ठा iproc_alg_s *driver_alg)
अणु
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा ahash_alg *hash = &driver_alg->alg.hash;
	पूर्णांक err;

	/* AES-XCBC is the only AES hash type currently supported on SPU-M */
	अगर ((driver_alg->auth_info.alg == HASH_ALG_AES) &&
	    (driver_alg->auth_info.mode != HASH_MODE_XCBC) &&
	    (spu->spu_type == SPU_TYPE_SPUM))
		वापस 0;

	/* SHA3 algorithm variants are not रेजिस्टरed क्रम SPU-M or SPU2. */
	अगर ((driver_alg->auth_info.alg >= HASH_ALG_SHA3_224) &&
	    (spu->spu_subtype != SPU_SUBTYPE_SPU2_V2))
		वापस 0;

	hash->halg.base.cra_module = THIS_MODULE;
	hash->halg.base.cra_priority = hash_pri;
	hash->halg.base.cra_alignmask = 0;
	hash->halg.base.cra_ctxsize = माप(काष्ठा iproc_ctx_s);
	hash->halg.base.cra_init = ahash_cra_init;
	hash->halg.base.cra_निकास = generic_cra_निकास;
	hash->halg.base.cra_flags = CRYPTO_ALG_ASYNC |
				    CRYPTO_ALG_ALLOCATES_MEMORY;
	hash->halg.statesize = माप(काष्ठा spu_hash_export_s);

	अगर (driver_alg->auth_info.mode != HASH_MODE_HMAC) अणु
		hash->init = ahash_init;
		hash->update = ahash_update;
		hash->final = ahash_final;
		hash->finup = ahash_finup;
		hash->digest = ahash_digest;
		अगर ((driver_alg->auth_info.alg == HASH_ALG_AES) &&
		    ((driver_alg->auth_info.mode == HASH_MODE_XCBC) ||
		    (driver_alg->auth_info.mode == HASH_MODE_CMAC))) अणु
			hash->setkey = ahash_setkey;
		पूर्ण
	पूर्ण अन्यथा अणु
		hash->setkey = ahash_hmac_setkey;
		hash->init = ahash_hmac_init;
		hash->update = ahash_hmac_update;
		hash->final = ahash_hmac_final;
		hash->finup = ahash_hmac_finup;
		hash->digest = ahash_hmac_digest;
	पूर्ण
	hash->export = ahash_export;
	hash->import = ahash_import;

	err = crypto_रेजिस्टर_ahash(hash);
	/* Mark alg as having been रेजिस्टरed, अगर successful */
	अगर (err == 0)
		driver_alg->रेजिस्टरed = true;
	pr_debug("  registered ahash %s\n",
		 hash->halg.base.cra_driver_name);
	वापस err;
पूर्ण

अटल पूर्णांक spu_रेजिस्टर_aead(काष्ठा iproc_alg_s *driver_alg)
अणु
	काष्ठा aead_alg *aead = &driver_alg->alg.aead;
	पूर्णांक err;

	aead->base.cra_module = THIS_MODULE;
	aead->base.cra_priority = aead_pri;
	aead->base.cra_alignmask = 0;
	aead->base.cra_ctxsize = माप(काष्ठा iproc_ctx_s);

	aead->base.cra_flags |= CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY;
	/* setkey set in alg initialization */
	aead->setauthsize = aead_setauthsize;
	aead->encrypt = aead_encrypt;
	aead->decrypt = aead_decrypt;
	aead->init = aead_cra_init;
	aead->निकास = aead_cra_निकास;

	err = crypto_रेजिस्टर_aead(aead);
	/* Mark alg as having been रेजिस्टरed, अगर successful */
	अगर (err == 0)
		driver_alg->रेजिस्टरed = true;
	pr_debug("  registered aead %s\n", aead->base.cra_driver_name);
	वापस err;
पूर्ण

/* रेजिस्टर crypto algorithms the device supports */
अटल पूर्णांक spu_algs_रेजिस्टर(काष्ठा device *dev)
अणु
	पूर्णांक i, j;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(driver_algs); i++) अणु
		चयन (driver_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			err = spu_रेजिस्टर_skcipher(&driver_algs[i]);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			err = spu_रेजिस्टर_ahash(&driver_algs[i]);
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AEAD:
			err = spu_रेजिस्टर_aead(&driver_algs[i]);
			अवरोध;
		शेष:
			dev_err(dev,
				"iproc-crypto: unknown alg type: %d",
				driver_algs[i].type);
			err = -EINVAL;
		पूर्ण

		अगर (err) अणु
			dev_err(dev, "alg registration failed with error %d\n",
				err);
			जाओ err_algs;
		पूर्ण
	पूर्ण

	वापस 0;

err_algs:
	क्रम (j = 0; j < i; j++) अणु
		/* Skip any algorithm not रेजिस्टरed */
		अगर (!driver_algs[j].रेजिस्टरed)
			जारी;
		चयन (driver_algs[j].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			crypto_unरेजिस्टर_skcipher(&driver_algs[j].alg.skcipher);
			driver_algs[j].रेजिस्टरed = false;
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			crypto_unरेजिस्टर_ahash(&driver_algs[j].alg.hash);
			driver_algs[j].रेजिस्टरed = false;
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AEAD:
			crypto_unरेजिस्टर_aead(&driver_algs[j].alg.aead);
			driver_algs[j].रेजिस्टरed = false;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* ==================== Kernel Platक्रमm API ==================== */

अटल काष्ठा spu_type_subtype spum_ns2_types = अणु
	SPU_TYPE_SPUM, SPU_SUBTYPE_SPUM_NS2
पूर्ण;

अटल काष्ठा spu_type_subtype spum_nsp_types = अणु
	SPU_TYPE_SPUM, SPU_SUBTYPE_SPUM_NSP
पूर्ण;

अटल काष्ठा spu_type_subtype spu2_types = अणु
	SPU_TYPE_SPU2, SPU_SUBTYPE_SPU2_V1
पूर्ण;

अटल काष्ठा spu_type_subtype spu2_v2_types = अणु
	SPU_TYPE_SPU2, SPU_SUBTYPE_SPU2_V2
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm_spu_dt_ids[] = अणु
	अणु
		.compatible = "brcm,spum-crypto",
		.data = &spum_ns2_types,
	पूर्ण,
	अणु
		.compatible = "brcm,spum-nsp-crypto",
		.data = &spum_nsp_types,
	पूर्ण,
	अणु
		.compatible = "brcm,spu2-crypto",
		.data = &spu2_types,
	पूर्ण,
	अणु
		.compatible = "brcm,spu2-v2-crypto",
		.data = &spu2_v2_types,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, bcm_spu_dt_ids);

अटल पूर्णांक spu_dt_पढ़ो(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	काष्ठा resource *spu_ctrl_regs;
	स्थिर काष्ठा spu_type_subtype *matched_spu_type;
	काष्ठा device_node *dn = pdev->dev.of_node;
	पूर्णांक err, i;

	/* Count number of mailbox channels */
	spu->num_chan = of_count_phandle_with_args(dn, "mboxes", "#mbox-cells");

	matched_spu_type = of_device_get_match_data(dev);
	अगर (!matched_spu_type) अणु
		dev_err(dev, "Failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	spu->spu_type = matched_spu_type->type;
	spu->spu_subtype = matched_spu_type->subtype;

	क्रम (i = 0; (i < MAX_SPUS) && ((spu_ctrl_regs =
		platक्रमm_get_resource(pdev, IORESOURCE_MEM, i)) != शून्य); i++) अणु

		spu->reg_vbase[i] = devm_ioremap_resource(dev, spu_ctrl_regs);
		अगर (IS_ERR(spu->reg_vbase[i])) अणु
			err = PTR_ERR(spu->reg_vbase[i]);
			dev_err(dev, "Failed to map registers: %d\n",
				err);
			spu->reg_vbase[i] = शून्य;
			वापस err;
		पूर्ण
	पूर्ण
	spu->num_spu = i;
	dev_dbg(dev, "Device has %d SPUs", spu->num_spu);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_spu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spu_hw *spu = &iproc_priv.spu;
	पूर्णांक err;

	iproc_priv.pdev  = pdev;
	platक्रमm_set_drvdata(iproc_priv.pdev,
			     &iproc_priv);

	err = spu_dt_पढ़ो(pdev);
	अगर (err < 0)
		जाओ failure;

	err = spu_mb_init(dev);
	अगर (err < 0)
		जाओ failure;

	अगर (spu->spu_type == SPU_TYPE_SPUM)
		iproc_priv.bcm_hdr_len = 8;
	अन्यथा अगर (spu->spu_type == SPU_TYPE_SPU2)
		iproc_priv.bcm_hdr_len = 0;

	spu_functions_रेजिस्टर(dev, spu->spu_type, spu->spu_subtype);

	spu_counters_init();

	spu_setup_debugfs();

	err = spu_algs_रेजिस्टर(dev);
	अगर (err < 0)
		जाओ fail_reg;

	वापस 0;

fail_reg:
	spu_मुक्त_debugfs();
failure:
	spu_mb_release(pdev);
	dev_err(dev, "%s failed with error %d.\n", __func__, err);

	वापस err;
पूर्ण

अटल पूर्णांक bcm_spu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा device *dev = &pdev->dev;
	अक्षर *cdn;

	क्रम (i = 0; i < ARRAY_SIZE(driver_algs); i++) अणु
		/*
		 * Not all algorithms were रेजिस्टरed, depending on whether
		 * hardware is SPU or SPU2.  So here we make sure to skip
		 * those algorithms that were not previously रेजिस्टरed.
		 */
		अगर (!driver_algs[i].रेजिस्टरed)
			जारी;

		चयन (driver_algs[i].type) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			crypto_unरेजिस्टर_skcipher(&driver_algs[i].alg.skcipher);
			dev_dbg(dev, "  unregistered cipher %s\n",
				driver_algs[i].alg.skcipher.base.cra_driver_name);
			driver_algs[i].रेजिस्टरed = false;
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			crypto_unरेजिस्टर_ahash(&driver_algs[i].alg.hash);
			cdn = driver_algs[i].alg.hash.halg.base.cra_driver_name;
			dev_dbg(dev, "  unregistered hash %s\n", cdn);
			driver_algs[i].रेजिस्टरed = false;
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AEAD:
			crypto_unरेजिस्टर_aead(&driver_algs[i].alg.aead);
			dev_dbg(dev, "  unregistered aead %s\n",
				driver_algs[i].alg.aead.base.cra_driver_name);
			driver_algs[i].रेजिस्टरed = false;
			अवरोध;
		पूर्ण
	पूर्ण
	spu_मुक्त_debugfs();
	spu_mb_release(pdev);
	वापस 0;
पूर्ण

/* ===== Kernel Module API ===== */

अटल काष्ठा platक्रमm_driver bcm_spu_pdriver = अणु
	.driver = अणु
		   .name = "brcm-spu-crypto",
		   .of_match_table = of_match_ptr(bcm_spu_dt_ids),
		   पूर्ण,
	.probe = bcm_spu_probe,
	.हटाओ = bcm_spu_हटाओ,
पूर्ण;
module_platक्रमm_driver(bcm_spu_pdriver);

MODULE_AUTHOR("Rob Rice <rob.rice@broadcom.com>");
MODULE_DESCRIPTION("Broadcom symmetric crypto offload driver");
MODULE_LICENSE("GPL v2");
