<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sun4i-ss-hash.c - hardware cryptographic accelerator क्रम Allwinner A20 SoC
 *
 * Copyright (C) 2013-2015 Corentin LABBE <clabbe.montjoie@gmail.com>
 *
 * This file add support क्रम MD5 and SHA1.
 *
 * You could find the datasheet in Documentation/arm/sunxi.rst
 */
#समावेश "sun4i-ss.h"
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/scatterlist.h>

/* This is a totally arbitrary value */
#घोषणा SS_TIMEOUT 100

पूर्णांक sun4i_hash_crainit(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun4i_tfm_ctx *op = crypto_tfm_ctx(tfm);
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->__crt_alg);
	काष्ठा sun4i_ss_alg_ढाँचा *algt;
	पूर्णांक err;

	स_रखो(op, 0, माप(काष्ठा sun4i_tfm_ctx));

	algt = container_of(alg, काष्ठा sun4i_ss_alg_ढाँचा, alg.hash);
	op->ss = algt->ss;

	err = pm_runसमय_resume_and_get(op->ss->dev);
	अगर (err < 0)
		वापस err;

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा sun4i_req_ctx));
	वापस 0;
पूर्ण

व्योम sun4i_hash_craनिकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sun4i_tfm_ctx *op = crypto_tfm_ctx(tfm);

	pm_runसमय_put(op->ss->dev);
पूर्ण

/* sun4i_hash_init: initialize request context */
पूर्णांक sun4i_hash_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun4i_req_ctx *op = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun4i_ss_alg_ढाँचा *algt;

	स_रखो(op, 0, माप(काष्ठा sun4i_req_ctx));

	algt = container_of(alg, काष्ठा sun4i_ss_alg_ढाँचा, alg.hash);
	op->mode = algt->mode;

	वापस 0;
पूर्ण

पूर्णांक sun4i_hash_export_md5(काष्ठा ahash_request *areq, व्योम *out)
अणु
	काष्ठा sun4i_req_ctx *op = ahash_request_ctx(areq);
	काष्ठा md5_state *octx = out;
	पूर्णांक i;

	octx->byte_count = op->byte_count + op->len;

	स_नकल(octx->block, op->buf, op->len);

	अगर (op->byte_count) अणु
		क्रम (i = 0; i < 4; i++)
			octx->hash[i] = op->hash[i];
	पूर्ण अन्यथा अणु
		octx->hash[0] = SHA1_H0;
		octx->hash[1] = SHA1_H1;
		octx->hash[2] = SHA1_H2;
		octx->hash[3] = SHA1_H3;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sun4i_hash_import_md5(काष्ठा ahash_request *areq, स्थिर व्योम *in)
अणु
	काष्ठा sun4i_req_ctx *op = ahash_request_ctx(areq);
	स्थिर काष्ठा md5_state *ictx = in;
	पूर्णांक i;

	sun4i_hash_init(areq);

	op->byte_count = ictx->byte_count & ~0x3F;
	op->len = ictx->byte_count & 0x3F;

	स_नकल(op->buf, ictx->block, op->len);

	क्रम (i = 0; i < 4; i++)
		op->hash[i] = ictx->hash[i];

	वापस 0;
पूर्ण

पूर्णांक sun4i_hash_export_sha1(काष्ठा ahash_request *areq, व्योम *out)
अणु
	काष्ठा sun4i_req_ctx *op = ahash_request_ctx(areq);
	काष्ठा sha1_state *octx = out;
	पूर्णांक i;

	octx->count = op->byte_count + op->len;

	स_नकल(octx->buffer, op->buf, op->len);

	अगर (op->byte_count) अणु
		क्रम (i = 0; i < 5; i++)
			octx->state[i] = op->hash[i];
	पूर्ण अन्यथा अणु
		octx->state[0] = SHA1_H0;
		octx->state[1] = SHA1_H1;
		octx->state[2] = SHA1_H2;
		octx->state[3] = SHA1_H3;
		octx->state[4] = SHA1_H4;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sun4i_hash_import_sha1(काष्ठा ahash_request *areq, स्थिर व्योम *in)
अणु
	काष्ठा sun4i_req_ctx *op = ahash_request_ctx(areq);
	स्थिर काष्ठा sha1_state *ictx = in;
	पूर्णांक i;

	sun4i_hash_init(areq);

	op->byte_count = ictx->count & ~0x3F;
	op->len = ictx->count & 0x3F;

	स_नकल(op->buf, ictx->buffer, op->len);

	क्रम (i = 0; i < 5; i++)
		op->hash[i] = ictx->state[i];

	वापस 0;
पूर्ण

#घोषणा SS_HASH_UPDATE 1
#घोषणा SS_HASH_FINAL 2

/*
 * sun4i_hash_update: update hash engine
 *
 * Could be used क्रम both SHA1 and MD5
 * Write data by step of 32bits and put then in the SS.
 *
 * Since we cannot leave partial data and hash state in the engine,
 * we need to get the hash state at the end of this function.
 * We can get the hash state every 64 bytes
 *
 * So the first work is to get the number of bytes to ग_लिखो to SS modulo 64
 * The extra bytes will go to a temporary buffer op->buf storing op->len bytes
 *
 * So at the begin of update()
 * अगर op->len + areq->nbytes < 64
 * => all data will be written to रुको buffer (op->buf) and end=0
 * अगर not, ग_लिखो all data from op->buf to the device and position end to
 * complete to 64bytes
 *
 * example 1:
 * update1 60o => op->len=60
 * update2 60o => need one more word to have 64 bytes
 * end=4
 * so ग_लिखो all data from op->buf and one word of SGs
 * ग_लिखो reमुख्यing data in op->buf
 * final state op->len=56
 */
अटल पूर्णांक sun4i_hash(काष्ठा ahash_request *areq)
अणु
	/*
	 * i is the total bytes पढ़ो from SGs, to be compared to areq->nbytes
	 * i is important because we cannot rely on SG length since the sum of
	 * SG->length could be greater than areq->nbytes
	 *
	 * end is the position when we need to stop writing to the device,
	 * to be compared to i
	 *
	 * in_i: advancement in the current SG
	 */
	अचिन्हित पूर्णांक i = 0, end, fill, min_fill, nरुको, nbw = 0, j = 0, toकरो;
	अचिन्हित पूर्णांक in_i = 0;
	u32 spaces, rx_cnt = SS_RX_DEFAULT, bf[32] = अणु0पूर्ण, v, ivmode = 0;
	काष्ठा sun4i_req_ctx *op = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा ahash_alg *alg = __crypto_ahash_alg(tfm->base.__crt_alg);
	काष्ठा sun4i_tfm_ctx *tfmctx = crypto_ahash_ctx(tfm);
	काष्ठा sun4i_ss_ctx *ss = tfmctx->ss;
	काष्ठा sun4i_ss_alg_ढाँचा *algt;
	काष्ठा scatterlist *in_sg = areq->src;
	काष्ठा sg_mapping_iter mi;
	पूर्णांक in_r, err = 0;
	माप_प्रकार copied = 0;
	u32 wb = 0;

	dev_dbg(ss->dev, "%s %s bc=%llu len=%u mode=%x wl=%u h0=%0x",
		__func__, crypto_tfm_alg_name(areq->base.tfm),
		op->byte_count, areq->nbytes, op->mode,
		op->len, op->hash[0]);

	अगर (unlikely(!areq->nbytes) && !(op->flags & SS_HASH_FINAL))
		वापस 0;

	/* protect against overflow */
	अगर (unlikely(areq->nbytes > अच_पूर्णांक_उच्च - op->len)) अणु
		dev_err(ss->dev, "Cannot process too large request\n");
		वापस -EINVAL;
	पूर्ण

	अगर (op->len + areq->nbytes < 64 && !(op->flags & SS_HASH_FINAL)) अणु
		/* linearize data to op->buf */
		copied = sg_pcopy_to_buffer(areq->src, sg_nents(areq->src),
					    op->buf + op->len, areq->nbytes, 0);
		op->len += copied;
		वापस 0;
	पूर्ण

	spin_lock_bh(&ss->slock);

	/*
	 * अगर some data have been processed beक्रमe,
	 * we need to restore the partial hash state
	 */
	अगर (op->byte_count) अणु
		ivmode = SS_IV_ARBITRARY;
		क्रम (i = 0; i < crypto_ahash_digestsize(tfm) / 4; i++)
			ग_लिखोl(op->hash[i], ss->base + SS_IV0 + i * 4);
	पूर्ण
	/* Enable the device */
	ग_लिखोl(op->mode | SS_ENABLED | ivmode, ss->base + SS_CTL);

	अगर (!(op->flags & SS_HASH_UPDATE))
		जाओ hash_final;

	/* start of handling data */
	अगर (!(op->flags & SS_HASH_FINAL)) अणु
		end = ((areq->nbytes + op->len) / 64) * 64 - op->len;

		अगर (end > areq->nbytes || areq->nbytes - end > 63) अणु
			dev_err(ss->dev, "ERROR: Bound error %u %u\n",
				end, areq->nbytes);
			err = -EINVAL;
			जाओ release_ss;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Since we have the flag final, we can go up to modulo 4 */
		अगर (areq->nbytes < 4)
			end = 0;
		अन्यथा
			end = ((areq->nbytes + op->len) / 4) * 4 - op->len;
	पूर्ण

	/* TODO अगर SGlen % 4 and !op->len then DMA */
	i = 1;
	जबतक (in_sg && i == 1) अणु
		अगर (in_sg->length % 4)
			i = 0;
		in_sg = sg_next(in_sg);
	पूर्ण
	अगर (i == 1 && !op->len && areq->nbytes)
		dev_dbg(ss->dev, "We can DMA\n");

	i = 0;
	sg_miter_start(&mi, areq->src, sg_nents(areq->src),
		       SG_MITER_FROM_SG | SG_MITER_ATOMIC);
	sg_miter_next(&mi);
	in_i = 0;

	करो अणु
		/*
		 * we need to linearize in two हाल:
		 * - the buffer is alपढ़ोy used
		 * - the SG करोes not have enough byte reमुख्यing ( < 4)
		 */
		अगर (op->len || (mi.length - in_i) < 4) अणु
			/*
			 * अगर we have entered here we have two reason to stop
			 * - the buffer is full
			 * - reach the end
			 */
			जबतक (op->len < 64 && i < end) अणु
				/* how many bytes we can पढ़ो from current SG */
				in_r = min(end - i, 64 - op->len);
				in_r = min_t(माप_प्रकार, mi.length - in_i, in_r);
				स_नकल(op->buf + op->len, mi.addr + in_i, in_r);
				op->len += in_r;
				i += in_r;
				in_i += in_r;
				अगर (in_i == mi.length) अणु
					sg_miter_next(&mi);
					in_i = 0;
				पूर्ण
			पूर्ण
			अगर (op->len > 3 && !(op->len % 4)) अणु
				/* ग_लिखो buf to the device */
				ग_लिखोsl(ss->base + SS_RXFIFO, op->buf,
					op->len / 4);
				op->byte_count += op->len;
				op->len = 0;
			पूर्ण
		पूर्ण
		अगर (mi.length - in_i > 3 && i < end) अणु
			/* how many bytes we can पढ़ो from current SG */
			in_r = min_t(माप_प्रकार, mi.length - in_i, areq->nbytes - i);
			in_r = min_t(माप_प्रकार, ((mi.length - in_i) / 4) * 4, in_r);
			/* how many bytes we can ग_लिखो in the device*/
			toकरो = min3((u32)(end - i) / 4, rx_cnt, (u32)in_r / 4);
			ग_लिखोsl(ss->base + SS_RXFIFO, mi.addr + in_i, toकरो);
			op->byte_count += toकरो * 4;
			i += toकरो * 4;
			in_i += toकरो * 4;
			rx_cnt -= toकरो;
			अगर (!rx_cnt) अणु
				spaces = पढ़ोl(ss->base + SS_FCSR);
				rx_cnt = SS_RXFIFO_SPACES(spaces);
			पूर्ण
			अगर (in_i == mi.length) अणु
				sg_miter_next(&mi);
				in_i = 0;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (i < end);

	/*
	 * Now we have written to the device all that we can,
	 * store the reमुख्यing bytes in op->buf
	 */
	अगर ((areq->nbytes - i) < 64) अणु
		जबतक (i < areq->nbytes && in_i < mi.length && op->len < 64) अणु
			/* how many bytes we can पढ़ो from current SG */
			in_r = min(areq->nbytes - i, 64 - op->len);
			in_r = min_t(माप_प्रकार, mi.length - in_i, in_r);
			स_नकल(op->buf + op->len, mi.addr + in_i, in_r);
			op->len += in_r;
			i += in_r;
			in_i += in_r;
			अगर (in_i == mi.length) अणु
				sg_miter_next(&mi);
				in_i = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	sg_miter_stop(&mi);

	/*
	 * End of data process
	 * Now अगर we have the flag final go to finalize part
	 * If not, store the partial hash
	 */
	अगर (op->flags & SS_HASH_FINAL)
		जाओ hash_final;

	ग_लिखोl(op->mode | SS_ENABLED | SS_DATA_END, ss->base + SS_CTL);
	i = 0;
	करो अणु
		v = पढ़ोl(ss->base + SS_CTL);
		i++;
	पूर्ण जबतक (i < SS_TIMEOUT && (v & SS_DATA_END));
	अगर (unlikely(i >= SS_TIMEOUT)) अणु
		dev_err_ratelimited(ss->dev,
				    "ERROR: hash end timeout %d>%d ctl=%x len=%u\n",
				    i, SS_TIMEOUT, v, areq->nbytes);
		err = -EIO;
		जाओ release_ss;
	पूर्ण

	/*
	 * The datasheet isn't very clear about when to retrieve the digest. The
	 * bit SS_DATA_END is cleared when the engine has processed the data and
	 * when the digest is computed *but* it करोesn't mean the digest is
	 * available in the digest रेजिस्टरs. Hence the delay to be sure we can
	 * पढ़ो it.
	 */
	ndelay(1);

	क्रम (i = 0; i < crypto_ahash_digestsize(tfm) / 4; i++)
		op->hash[i] = पढ़ोl(ss->base + SS_MD0 + i * 4);

	जाओ release_ss;

/*
 * hash_final: finalize hashing operation
 *
 * If we have some reमुख्यing bytes, we ग_लिखो them.
 * Then ask the SS क्रम finalizing the hashing operation
 *
 * I करो not check RX FIFO size in this function since the size is 32
 * after each enabling and this function neither ग_लिखो more than 32 words.
 * If we come from the update part, we cannot have more than
 * 3 reमुख्यing bytes to ग_लिखो and SS is fast enough to not care about it.
 */

hash_final:
	अगर (IS_ENABLED(CONFIG_CRYPTO_DEV_SUN4I_SS_DEBUG)) अणु
		algt = container_of(alg, काष्ठा sun4i_ss_alg_ढाँचा, alg.hash);
		algt->stat_req++;
	पूर्ण

	/* ग_लिखो the reमुख्यing words of the रुको buffer */
	अगर (op->len) अणु
		nरुको = op->len / 4;
		अगर (nरुको) अणु
			ग_लिखोsl(ss->base + SS_RXFIFO, op->buf, nरुको);
			op->byte_count += 4 * nरुको;
		पूर्ण

		nbw = op->len - 4 * nरुको;
		अगर (nbw) अणु
			wb = le32_to_cpup((__le32 *)(op->buf + nरुको * 4));
			wb &= GENMASK((nbw * 8) - 1, 0);

			op->byte_count += nbw;
		पूर्ण
	पूर्ण

	/* ग_लिखो the reमुख्यing bytes of the nbw buffer */
	wb |= ((1 << 7) << (nbw * 8));
	((__le32 *)bf)[j++] = cpu_to_le32(wb);

	/*
	 * number of space to pad to obtain 64o minus 8(size) minus 4 (final 1)
	 * I take the operations from other MD5/SHA1 implementations
	 */

	/* last block size */
	fill = 64 - (op->byte_count % 64);
	min_fill = 2 * माप(u32) + (nbw ? 0 : माप(u32));

	/* अगर we can't fill all data, jump to the next 64 block */
	अगर (fill < min_fill)
		fill += 64;

	j += (fill - min_fill) / माप(u32);

	/* ग_लिखो the length of data */
	अगर (op->mode == SS_OP_SHA1) अणु
		__be64 *bits = (__be64 *)&bf[j];
		*bits = cpu_to_be64(op->byte_count << 3);
		j += 2;
	पूर्ण अन्यथा अणु
		__le64 *bits = (__le64 *)&bf[j];
		*bits = cpu_to_le64(op->byte_count << 3);
		j += 2;
	पूर्ण
	ग_लिखोsl(ss->base + SS_RXFIFO, bf, j);

	/* Tell the SS to stop the hashing */
	ग_लिखोl(op->mode | SS_ENABLED | SS_DATA_END, ss->base + SS_CTL);

	/*
	 * Wait क्रम SS to finish the hash.
	 * The समयout could happen only in हाल of bad overघड़ीing
	 * or driver bug.
	 */
	i = 0;
	करो अणु
		v = पढ़ोl(ss->base + SS_CTL);
		i++;
	पूर्ण जबतक (i < SS_TIMEOUT && (v & SS_DATA_END));
	अगर (unlikely(i >= SS_TIMEOUT)) अणु
		dev_err_ratelimited(ss->dev,
				    "ERROR: hash end timeout %d>%d ctl=%x len=%u\n",
				    i, SS_TIMEOUT, v, areq->nbytes);
		err = -EIO;
		जाओ release_ss;
	पूर्ण

	/*
	 * The datasheet isn't very clear about when to retrieve the digest. The
	 * bit SS_DATA_END is cleared when the engine has processed the data and
	 * when the digest is computed *but* it करोesn't mean the digest is
	 * available in the digest रेजिस्टरs. Hence the delay to be sure we can
	 * पढ़ो it.
	 */
	ndelay(1);

	/* Get the hash from the device */
	अगर (op->mode == SS_OP_SHA1) अणु
		क्रम (i = 0; i < 5; i++) अणु
			v = पढ़ोl(ss->base + SS_MD0 + i * 4);
			अगर (ss->variant->sha1_in_be)
				put_unaligned_le32(v, areq->result + i * 4);
			अन्यथा
				put_unaligned_be32(v, areq->result + i * 4);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 4; i++) अणु
			v = पढ़ोl(ss->base + SS_MD0 + i * 4);
			put_unaligned_le32(v, areq->result + i * 4);
		पूर्ण
	पूर्ण

release_ss:
	ग_लिखोl(0, ss->base + SS_CTL);
	spin_unlock_bh(&ss->slock);
	वापस err;
पूर्ण

पूर्णांक sun4i_hash_final(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun4i_req_ctx *op = ahash_request_ctx(areq);

	op->flags = SS_HASH_FINAL;
	वापस sun4i_hash(areq);
पूर्ण

पूर्णांक sun4i_hash_update(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun4i_req_ctx *op = ahash_request_ctx(areq);

	op->flags = SS_HASH_UPDATE;
	वापस sun4i_hash(areq);
पूर्ण

/* sun4i_hash_finup: finalize hashing operation after an update */
पूर्णांक sun4i_hash_finup(काष्ठा ahash_request *areq)
अणु
	काष्ठा sun4i_req_ctx *op = ahash_request_ctx(areq);

	op->flags = SS_HASH_UPDATE | SS_HASH_FINAL;
	वापस sun4i_hash(areq);
पूर्ण

/* combo of init/update/final functions */
पूर्णांक sun4i_hash_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक err;
	काष्ठा sun4i_req_ctx *op = ahash_request_ctx(areq);

	err = sun4i_hash_init(areq);
	अगर (err)
		वापस err;

	op->flags = SS_HASH_UPDATE | SS_HASH_FINAL;
	वापस sun4i_hash(areq);
पूर्ण
