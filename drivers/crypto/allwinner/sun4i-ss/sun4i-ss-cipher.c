<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sun4i-ss-cipher.c - hardware cryptographic accelerator क्रम Allwinner A20 SoC
 *
 * Copyright (C) 2013-2015 Corentin LABBE <clabbe.montjoie@gmail.com>
 *
 * This file add support क्रम AES cipher with 128,192,256 bits
 * keysize in CBC and ECB mode.
 * Add support also क्रम DES and 3DES in CBC and ECB mode.
 *
 * You could find the datasheet in Documentation/arm/sunxi.rst
 */
#समावेश "sun4i-ss.h"

अटल पूर्णांक noअंतरभूत_क्रम_stack sun4i_ss_opti_poll(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_ss_ctx *ss = op->ss;
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(tfm);
	काष्ठा sun4i_cipher_req_ctx *ctx = skcipher_request_ctx(areq);
	u32 mode = ctx->mode;
	व्योम *backup_iv = शून्य;
	/* when activating SS, the शेष FIFO space is SS_RX_DEFAULT(32) */
	u32 rx_cnt = SS_RX_DEFAULT;
	u32 tx_cnt = 0;
	u32 spaces;
	u32 v;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक ileft = areq->cryptlen;
	अचिन्हित पूर्णांक oleft = areq->cryptlen;
	अचिन्हित पूर्णांक toकरो;
	अचिन्हित दीर्घ pi = 0, po = 0; /* progress क्रम in and out */
	bool miter_err;
	काष्ठा sg_mapping_iter mi, mo;
	अचिन्हित पूर्णांक oi, oo; /* offset क्रम in and out */
	अचिन्हित दीर्घ flags;
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा sun4i_ss_alg_ढाँचा *algt;

	अगर (!areq->cryptlen)
		वापस 0;

	अगर (!areq->src || !areq->dst) अणु
		dev_err_ratelimited(ss->dev, "ERROR: Some SGs are NULL\n");
		वापस -EINVAL;
	पूर्ण

	अगर (areq->iv && ivsize > 0 && mode & SS_DECRYPTION) अणु
		backup_iv = kzalloc(ivsize, GFP_KERNEL);
		अगर (!backup_iv)
			वापस -ENOMEM;
		scatterwalk_map_and_copy(backup_iv, areq->src, areq->cryptlen - ivsize, ivsize, 0);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_CRYPTO_DEV_SUN4I_SS_DEBUG)) अणु
		algt = container_of(alg, काष्ठा sun4i_ss_alg_ढाँचा, alg.crypto);
		algt->stat_opti++;
		algt->stat_bytes += areq->cryptlen;
	पूर्ण

	spin_lock_irqsave(&ss->slock, flags);

	क्रम (i = 0; i < op->keylen / 4; i++)
		ग_लिखोsl(ss->base + SS_KEY0 + i * 4, &op->key[i], 1);

	अगर (areq->iv) अणु
		क्रम (i = 0; i < 4 && i < ivsize / 4; i++) अणु
			v = *(u32 *)(areq->iv + i * 4);
			ग_लिखोsl(ss->base + SS_IV0 + i * 4, &v, 1);
		पूर्ण
	पूर्ण
	ग_लिखोl(mode, ss->base + SS_CTL);


	ileft = areq->cryptlen / 4;
	oleft = areq->cryptlen / 4;
	oi = 0;
	oo = 0;
	करो अणु
		अगर (ileft) अणु
			sg_miter_start(&mi, areq->src, sg_nents(areq->src),
					SG_MITER_FROM_SG | SG_MITER_ATOMIC);
			अगर (pi)
				sg_miter_skip(&mi, pi);
			miter_err = sg_miter_next(&mi);
			अगर (!miter_err || !mi.addr) अणु
				dev_err_ratelimited(ss->dev, "ERROR: sg_miter return null\n");
				err = -EINVAL;
				जाओ release_ss;
			पूर्ण
			toकरो = min(rx_cnt, ileft);
			toकरो = min_t(माप_प्रकार, toकरो, (mi.length - oi) / 4);
			अगर (toकरो) अणु
				ileft -= toकरो;
				ग_लिखोsl(ss->base + SS_RXFIFO, mi.addr + oi, toकरो);
				oi += toकरो * 4;
			पूर्ण
			अगर (oi == mi.length) अणु
				pi += mi.length;
				oi = 0;
			पूर्ण
			sg_miter_stop(&mi);
		पूर्ण

		spaces = पढ़ोl(ss->base + SS_FCSR);
		rx_cnt = SS_RXFIFO_SPACES(spaces);
		tx_cnt = SS_TXFIFO_SPACES(spaces);

		sg_miter_start(&mo, areq->dst, sg_nents(areq->dst),
			       SG_MITER_TO_SG | SG_MITER_ATOMIC);
		अगर (po)
			sg_miter_skip(&mo, po);
		miter_err = sg_miter_next(&mo);
		अगर (!miter_err || !mo.addr) अणु
			dev_err_ratelimited(ss->dev, "ERROR: sg_miter return null\n");
			err = -EINVAL;
			जाओ release_ss;
		पूर्ण
		toकरो = min(tx_cnt, oleft);
		toकरो = min_t(माप_प्रकार, toकरो, (mo.length - oo) / 4);
		अगर (toकरो) अणु
			oleft -= toकरो;
			पढ़ोsl(ss->base + SS_TXFIFO, mo.addr + oo, toकरो);
			oo += toकरो * 4;
		पूर्ण
		अगर (oo == mo.length) अणु
			oo = 0;
			po += mo.length;
		पूर्ण
		sg_miter_stop(&mo);
	पूर्ण जबतक (oleft);

	अगर (areq->iv) अणु
		अगर (mode & SS_DECRYPTION) अणु
			स_नकल(areq->iv, backup_iv, ivsize);
			kमुक्त_sensitive(backup_iv);
		पूर्ण अन्यथा अणु
			scatterwalk_map_and_copy(areq->iv, areq->dst, areq->cryptlen - ivsize,
						 ivsize, 0);
		पूर्ण
	पूर्ण

release_ss:
	ग_लिखोl(0, ss->base + SS_CTL);
	spin_unlock_irqrestore(&ss->slock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक noअंतरभूत_क्रम_stack sun4i_ss_cipher_poll_fallback(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *ctx = skcipher_request_ctx(areq);
	पूर्णांक err;
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा sun4i_ss_alg_ढाँचा *algt;

	अगर (IS_ENABLED(CONFIG_CRYPTO_DEV_SUN4I_SS_DEBUG)) अणु
		algt = container_of(alg, काष्ठा sun4i_ss_alg_ढाँचा, alg.crypto);
		algt->stat_fb++;
	पूर्ण

	skcipher_request_set_tfm(&ctx->fallback_req, op->fallback_tfm);
	skcipher_request_set_callback(&ctx->fallback_req, areq->base.flags,
				      areq->base.complete, areq->base.data);
	skcipher_request_set_crypt(&ctx->fallback_req, areq->src, areq->dst,
				   areq->cryptlen, areq->iv);
	अगर (ctx->mode & SS_DECRYPTION)
		err = crypto_skcipher_decrypt(&ctx->fallback_req);
	अन्यथा
		err = crypto_skcipher_encrypt(&ctx->fallback_req);

	वापस err;
पूर्ण

/* Generic function that support SG with size not multiple of 4 */
अटल पूर्णांक sun4i_ss_cipher_poll(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_ss_ctx *ss = op->ss;
	पूर्णांक no_chunk = 1;
	काष्ठा scatterlist *in_sg = areq->src;
	काष्ठा scatterlist *out_sg = areq->dst;
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(tfm);
	काष्ठा sun4i_cipher_req_ctx *ctx = skcipher_request_ctx(areq);
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा sun4i_ss_alg_ढाँचा *algt;
	u32 mode = ctx->mode;
	/* when activating SS, the शेष FIFO space is SS_RX_DEFAULT(32) */
	u32 rx_cnt = SS_RX_DEFAULT;
	u32 tx_cnt = 0;
	u32 v;
	u32 spaces;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक ileft = areq->cryptlen;
	अचिन्हित पूर्णांक oleft = areq->cryptlen;
	अचिन्हित पूर्णांक toकरो;
	व्योम *backup_iv = शून्य;
	काष्ठा sg_mapping_iter mi, mo;
	अचिन्हित दीर्घ pi = 0, po = 0; /* progress क्रम in and out */
	bool miter_err;
	अचिन्हित पूर्णांक oi, oo;	/* offset क्रम in and out */
	अचिन्हित पूर्णांक ob = 0;	/* offset in buf */
	अचिन्हित पूर्णांक obo = 0;	/* offset in bufo*/
	अचिन्हित पूर्णांक obl = 0;	/* length of data in bufo */
	अचिन्हित दीर्घ flags;
	bool need_fallback = false;

	अगर (!areq->cryptlen)
		वापस 0;

	अगर (!areq->src || !areq->dst) अणु
		dev_err_ratelimited(ss->dev, "ERROR: Some SGs are NULL\n");
		वापस -EINVAL;
	पूर्ण

	algt = container_of(alg, काष्ठा sun4i_ss_alg_ढाँचा, alg.crypto);
	अगर (areq->cryptlen % algt->alg.crypto.base.cra_blocksize)
		need_fallback = true;

	/*
	 * अगर we have only SGs with size multiple of 4,
	 * we can use the SS optimized function
	 */
	जबतक (in_sg && no_chunk == 1) अणु
		अगर ((in_sg->length | in_sg->offset) & 3u)
			no_chunk = 0;
		in_sg = sg_next(in_sg);
	पूर्ण
	जबतक (out_sg && no_chunk == 1) अणु
		अगर ((out_sg->length | out_sg->offset) & 3u)
			no_chunk = 0;
		out_sg = sg_next(out_sg);
	पूर्ण

	अगर (no_chunk == 1 && !need_fallback)
		वापस sun4i_ss_opti_poll(areq);

	अगर (need_fallback)
		वापस sun4i_ss_cipher_poll_fallback(areq);

	अगर (areq->iv && ivsize > 0 && mode & SS_DECRYPTION) अणु
		backup_iv = kzalloc(ivsize, GFP_KERNEL);
		अगर (!backup_iv)
			वापस -ENOMEM;
		scatterwalk_map_and_copy(backup_iv, areq->src, areq->cryptlen - ivsize, ivsize, 0);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_CRYPTO_DEV_SUN4I_SS_DEBUG)) अणु
		algt->stat_req++;
		algt->stat_bytes += areq->cryptlen;
	पूर्ण

	spin_lock_irqsave(&ss->slock, flags);

	क्रम (i = 0; i < op->keylen / 4; i++)
		ग_लिखोsl(ss->base + SS_KEY0 + i * 4, &op->key[i], 1);

	अगर (areq->iv) अणु
		क्रम (i = 0; i < 4 && i < ivsize / 4; i++) अणु
			v = *(u32 *)(areq->iv + i * 4);
			ग_लिखोsl(ss->base + SS_IV0 + i * 4, &v, 1);
		पूर्ण
	पूर्ण
	ग_लिखोl(mode, ss->base + SS_CTL);

	ileft = areq->cryptlen;
	oleft = areq->cryptlen;
	oi = 0;
	oo = 0;

	जबतक (oleft) अणु
		अगर (ileft) अणु
			sg_miter_start(&mi, areq->src, sg_nents(areq->src),
				       SG_MITER_FROM_SG | SG_MITER_ATOMIC);
			अगर (pi)
				sg_miter_skip(&mi, pi);
			miter_err = sg_miter_next(&mi);
			अगर (!miter_err || !mi.addr) अणु
				dev_err_ratelimited(ss->dev, "ERROR: sg_miter return null\n");
				err = -EINVAL;
				जाओ release_ss;
			पूर्ण
			/*
			 * toकरो is the number of consecutive 4byte word that we
			 * can पढ़ो from current SG
			 */
			toकरो = min(rx_cnt, ileft / 4);
			toकरो = min_t(माप_प्रकार, toकरो, (mi.length - oi) / 4);
			अगर (toकरो && !ob) अणु
				ग_लिखोsl(ss->base + SS_RXFIFO, mi.addr + oi,
					toकरो);
				ileft -= toकरो * 4;
				oi += toकरो * 4;
			पूर्ण अन्यथा अणु
				/*
				 * not enough consecutive bytes, so we need to
				 * linearize in buf. toकरो is in bytes
				 * After that copy, अगर we have a multiple of 4
				 * we need to be able to ग_लिखो all buf in one
				 * pass, so it is why we min() with rx_cnt
				 */
				toकरो = min(rx_cnt * 4 - ob, ileft);
				toकरो = min_t(माप_प्रकार, toकरो, mi.length - oi);
				स_नकल(ss->buf + ob, mi.addr + oi, toकरो);
				ileft -= toकरो;
				oi += toकरो;
				ob += toकरो;
				अगर (!(ob % 4)) अणु
					ग_लिखोsl(ss->base + SS_RXFIFO, ss->buf,
						ob / 4);
					ob = 0;
				पूर्ण
			पूर्ण
			अगर (oi == mi.length) अणु
				pi += mi.length;
				oi = 0;
			पूर्ण
			sg_miter_stop(&mi);
		पूर्ण

		spaces = पढ़ोl(ss->base + SS_FCSR);
		rx_cnt = SS_RXFIFO_SPACES(spaces);
		tx_cnt = SS_TXFIFO_SPACES(spaces);

		अगर (!tx_cnt)
			जारी;
		sg_miter_start(&mo, areq->dst, sg_nents(areq->dst),
			       SG_MITER_TO_SG | SG_MITER_ATOMIC);
		अगर (po)
			sg_miter_skip(&mo, po);
		miter_err = sg_miter_next(&mo);
		अगर (!miter_err || !mo.addr) अणु
			dev_err_ratelimited(ss->dev, "ERROR: sg_miter return null\n");
			err = -EINVAL;
			जाओ release_ss;
		पूर्ण
		/* toकरो in 4bytes word */
		toकरो = min(tx_cnt, oleft / 4);
		toकरो = min_t(माप_प्रकार, toकरो, (mo.length - oo) / 4);

		अगर (toकरो) अणु
			पढ़ोsl(ss->base + SS_TXFIFO, mo.addr + oo, toकरो);
			oleft -= toकरो * 4;
			oo += toकरो * 4;
			अगर (oo == mo.length) अणु
				po += mo.length;
				oo = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * पढ़ो obl bytes in bufo, we पढ़ो at maximum क्रम
			 * emptying the device
			 */
			पढ़ोsl(ss->base + SS_TXFIFO, ss->bufo, tx_cnt);
			obl = tx_cnt * 4;
			obo = 0;
			करो अणु
				/*
				 * how many bytes we can copy ?
				 * no more than reमुख्यing SG size
				 * no more than reमुख्यing buffer
				 * no need to test against oleft
				 */
				toकरो = min_t(माप_प्रकार,
					     mo.length - oo, obl - obo);
				स_नकल(mo.addr + oo, ss->bufo + obo, toकरो);
				oleft -= toकरो;
				obo += toकरो;
				oo += toकरो;
				अगर (oo == mo.length) अणु
					po += mo.length;
					sg_miter_next(&mo);
					oo = 0;
				पूर्ण
			पूर्ण जबतक (obo < obl);
			/* bufo must be fully used here */
		पूर्ण
		sg_miter_stop(&mo);
	पूर्ण
	अगर (areq->iv) अणु
		अगर (mode & SS_DECRYPTION) अणु
			स_नकल(areq->iv, backup_iv, ivsize);
			kमुक्त_sensitive(backup_iv);
		पूर्ण अन्यथा अणु
			scatterwalk_map_and_copy(areq->iv, areq->dst, areq->cryptlen - ivsize,
						 ivsize, 0);
		पूर्ण
	पूर्ण

release_ss:
	ग_लिखोl(0, ss->base + SS_CTL);
	spin_unlock_irqrestore(&ss->slock, flags);

	वापस err;
पूर्ण

/* CBC AES */
पूर्णांक sun4i_ss_cbc_aes_encrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_AES | SS_CBC | SS_ENABLED | SS_ENCRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

पूर्णांक sun4i_ss_cbc_aes_decrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_AES | SS_CBC | SS_ENABLED | SS_DECRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

/* ECB AES */
पूर्णांक sun4i_ss_ecb_aes_encrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_AES | SS_ECB | SS_ENABLED | SS_ENCRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

पूर्णांक sun4i_ss_ecb_aes_decrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_AES | SS_ECB | SS_ENABLED | SS_DECRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

/* CBC DES */
पूर्णांक sun4i_ss_cbc_des_encrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_DES | SS_CBC | SS_ENABLED | SS_ENCRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

पूर्णांक sun4i_ss_cbc_des_decrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_DES | SS_CBC | SS_ENABLED | SS_DECRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

/* ECB DES */
पूर्णांक sun4i_ss_ecb_des_encrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_DES | SS_ECB | SS_ENABLED | SS_ENCRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

पूर्णांक sun4i_ss_ecb_des_decrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_DES | SS_ECB | SS_ENABLED | SS_DECRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

/* CBC 3DES */
पूर्णांक sun4i_ss_cbc_des3_encrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_3DES | SS_CBC | SS_ENABLED | SS_ENCRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

पूर्णांक sun4i_ss_cbc_des3_decrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_3DES | SS_CBC | SS_ENABLED | SS_DECRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

/* ECB 3DES */
पूर्णांक sun4i_ss_ecb_des3_encrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_3DES | SS_ECB | SS_ENABLED | SS_ENCRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

पूर्णांक sun4i_ss_ecb_des3_decrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_3DES | SS_ECB | SS_ENABLED | SS_DECRYPTION |
		op->keymode;
	वापस sun4i_ss_cipher_poll(areq);
पूर्ण

पूर्णांक sun4i_ss_cipher_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun4i_tfm_ctx *op = crypto_tfm_ctx(tfm);
	काष्ठा sun4i_ss_alg_ढाँचा *algt;
	स्थिर अक्षर *name = crypto_tfm_alg_name(tfm);
	पूर्णांक err;

	स_रखो(op, 0, माप(काष्ठा sun4i_tfm_ctx));

	algt = container_of(tfm->__crt_alg, काष्ठा sun4i_ss_alg_ढाँचा,
			    alg.crypto.base);
	op->ss = algt->ss;

	op->fallback_tfm = crypto_alloc_skcipher(name, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(op->fallback_tfm)) अणु
		dev_err(op->ss->dev, "ERROR: Cannot allocate fallback for %s %ld\n",
			name, PTR_ERR(op->fallback_tfm));
		वापस PTR_ERR(op->fallback_tfm);
	पूर्ण

	crypto_skcipher_set_reqsize(__crypto_skcipher_cast(tfm),
				    माप(काष्ठा sun4i_cipher_req_ctx) +
				    crypto_skcipher_reqsize(op->fallback_tfm));

	err = pm_runसमय_resume_and_get(op->ss->dev);
	अगर (err < 0)
		जाओ error_pm;

	वापस 0;
error_pm:
	crypto_मुक्त_skcipher(op->fallback_tfm);
	वापस err;
पूर्ण

व्योम sun4i_ss_cipher_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun4i_tfm_ctx *op = crypto_tfm_ctx(tfm);

	crypto_मुक्त_skcipher(op->fallback_tfm);
	pm_runसमय_put(op->ss->dev);
पूर्ण

/* check and set the AES key, prepare the mode to be used */
पूर्णांक sun4i_ss_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	काष्ठा sun4i_ss_ctx *ss = op->ss;

	चयन (keylen) अणु
	हाल 128 / 8:
		op->keymode = SS_AES_128BITS;
		अवरोध;
	हाल 192 / 8:
		op->keymode = SS_AES_192BITS;
		अवरोध;
	हाल 256 / 8:
		op->keymode = SS_AES_256BITS;
		अवरोध;
	शेष:
		dev_dbg(ss->dev, "ERROR: Invalid keylen %u\n", keylen);
		वापस -EINVAL;
	पूर्ण
	op->keylen = keylen;
	स_नकल(op->key, key, keylen);

	crypto_skcipher_clear_flags(op->fallback_tfm, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(op->fallback_tfm, tfm->base.crt_flags & CRYPTO_TFM_REQ_MASK);

	वापस crypto_skcipher_setkey(op->fallback_tfm, key, keylen);
पूर्ण

/* check and set the DES key, prepare the mode to be used */
पूर्णांक sun4i_ss_des_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	पूर्णांक err;

	err = verअगरy_skcipher_des_key(tfm, key);
	अगर (err)
		वापस err;

	op->keylen = keylen;
	स_नकल(op->key, key, keylen);

	crypto_skcipher_clear_flags(op->fallback_tfm, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(op->fallback_tfm, tfm->base.crt_flags & CRYPTO_TFM_REQ_MASK);

	वापस crypto_skcipher_setkey(op->fallback_tfm, key, keylen);
पूर्ण

/* check and set the 3DES key, prepare the mode to be used */
पूर्णांक sun4i_ss_des3_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	पूर्णांक err;

	err = verअगरy_skcipher_des3_key(tfm, key);
	अगर (err)
		वापस err;

	op->keylen = keylen;
	स_नकल(op->key, key, keylen);

	crypto_skcipher_clear_flags(op->fallback_tfm, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(op->fallback_tfm, tfm->base.crt_flags & CRYPTO_TFM_REQ_MASK);

	वापस crypto_skcipher_setkey(op->fallback_tfm, key, keylen);
पूर्ण
