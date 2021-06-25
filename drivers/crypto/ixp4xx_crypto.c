<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel IXP4xx NPE-C crypto driver
 *
 * Copyright (C) 2008 Christian Hohnstaedt <chohnstaedt@innominate.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/crypto.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/gfp.h>
#समावेश <linux/module.h>

#समावेश <crypto/ctr.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/hmac.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/scatterwalk.h>

#समावेश <linux/soc/ixp4xx/npe.h>
#समावेश <linux/soc/ixp4xx/qmgr.h>

#घोषणा MAX_KEYLEN 32

/* hash: cfgword + 2 * digestlen; crypt: keylen + cfgword */
#घोषणा NPE_CTX_LEN 80
#घोषणा AES_BLOCK128 16

#घोषणा NPE_OP_HASH_VERIFY   0x01
#घोषणा NPE_OP_CCM_ENABLE    0x04
#घोषणा NPE_OP_CRYPT_ENABLE  0x08
#घोषणा NPE_OP_HASH_ENABLE   0x10
#घोषणा NPE_OP_NOT_IN_PLACE  0x20
#घोषणा NPE_OP_HMAC_DISABLE  0x40
#घोषणा NPE_OP_CRYPT_ENCRYPT 0x80

#घोषणा NPE_OP_CCM_GEN_MIC   0xcc
#घोषणा NPE_OP_HASH_GEN_ICV  0x50
#घोषणा NPE_OP_ENC_GEN_KEY   0xc9

#घोषणा MOD_ECB     0x0000
#घोषणा MOD_CTR     0x1000
#घोषणा MOD_CBC_ENC 0x2000
#घोषणा MOD_CBC_DEC 0x3000
#घोषणा MOD_CCM_ENC 0x4000
#घोषणा MOD_CCM_DEC 0x5000

#घोषणा KEYLEN_128  4
#घोषणा KEYLEN_192  6
#घोषणा KEYLEN_256  8

#घोषणा CIPH_DECR   0x0000
#घोषणा CIPH_ENCR   0x0400

#घोषणा MOD_DES     0x0000
#घोषणा MOD_TDEA2   0x0100
#घोषणा MOD_3DES   0x0200
#घोषणा MOD_AES     0x0800
#घोषणा MOD_AES128  (0x0800 | KEYLEN_128)
#घोषणा MOD_AES192  (0x0900 | KEYLEN_192)
#घोषणा MOD_AES256  (0x0a00 | KEYLEN_256)

#घोषणा MAX_IVLEN   16
#घोषणा NPE_ID      2  /* NPE C */
#घोषणा NPE_QLEN    16
/* Space क्रम रेजिस्टरing when the first
 * NPE_QLEN crypt_ctl are busy */
#घोषणा NPE_QLEN_TOTAL 64

#घोषणा SEND_QID    29
#घोषणा RECV_QID    30

#घोषणा CTL_FLAG_UNUSED		0x0000
#घोषणा CTL_FLAG_USED		0x1000
#घोषणा CTL_FLAG_PERFORM_ABLK	0x0001
#घोषणा CTL_FLAG_GEN_ICV	0x0002
#घोषणा CTL_FLAG_GEN_REVAES	0x0004
#घोषणा CTL_FLAG_PERFORM_AEAD	0x0008
#घोषणा CTL_FLAG_MASK		0x000f

#घोषणा HMAC_PAD_BLOCKLEN SHA1_BLOCK_SIZE

#घोषणा MD5_DIGEST_SIZE   16

काष्ठा buffer_desc अणु
	u32 phys_next;
#अगर_घोषित __ARMEB__
	u16 buf_len;
	u16 pkt_len;
#अन्यथा
	u16 pkt_len;
	u16 buf_len;
#पूर्ण_अगर
	dma_addr_t phys_addr;
	u32 __reserved[4];
	काष्ठा buffer_desc *next;
	क्रमागत dma_data_direction dir;
पूर्ण;

काष्ठा crypt_ctl अणु
#अगर_घोषित __ARMEB__
	u8 mode;		/* NPE_OP_*  operation mode */
	u8 init_len;
	u16 reserved;
#अन्यथा
	u16 reserved;
	u8 init_len;
	u8 mode;		/* NPE_OP_*  operation mode */
#पूर्ण_अगर
	u8 iv[MAX_IVLEN];	/* IV क्रम CBC mode or CTR IV क्रम CTR mode */
	dma_addr_t icv_rev_aes;	/* icv or rev aes */
	dma_addr_t src_buf;
	dma_addr_t dst_buf;
#अगर_घोषित __ARMEB__
	u16 auth_offs;		/* Authentication start offset */
	u16 auth_len;		/* Authentication data length */
	u16 crypt_offs;		/* Cryption start offset */
	u16 crypt_len;		/* Cryption data length */
#अन्यथा
	u16 auth_len;		/* Authentication data length */
	u16 auth_offs;		/* Authentication start offset */
	u16 crypt_len;		/* Cryption data length */
	u16 crypt_offs;		/* Cryption start offset */
#पूर्ण_अगर
	u32 aadAddr;		/* Additional Auth Data Addr क्रम CCM mode */
	u32 crypto_ctx;		/* NPE Crypto Param काष्ठाure address */

	/* Used by Host: 4*4 bytes*/
	अचिन्हित ctl_flags;
	जोड़ अणु
		काष्ठा skcipher_request *ablk_req;
		काष्ठा aead_request *aead_req;
		काष्ठा crypto_tfm *tfm;
	पूर्ण data;
	काष्ठा buffer_desc *regist_buf;
	u8 *regist_ptr;
पूर्ण;

काष्ठा ablk_ctx अणु
	काष्ठा buffer_desc *src;
	काष्ठा buffer_desc *dst;
पूर्ण;

काष्ठा aead_ctx अणु
	काष्ठा buffer_desc *src;
	काष्ठा buffer_desc *dst;
	काष्ठा scatterlist ivlist;
	/* used when the hmac is not on one sg entry */
	u8 *hmac_virt;
	पूर्णांक encrypt;
पूर्ण;

काष्ठा ix_hash_algo अणु
	u32 cfgword;
	अचिन्हित अक्षर *icv;
पूर्ण;

काष्ठा ix_sa_dir अणु
	अचिन्हित अक्षर *npe_ctx;
	dma_addr_t npe_ctx_phys;
	पूर्णांक npe_ctx_idx;
	u8 npe_mode;
पूर्ण;

काष्ठा ixp_ctx अणु
	काष्ठा ix_sa_dir encrypt;
	काष्ठा ix_sa_dir decrypt;
	पूर्णांक authkey_len;
	u8 authkey[MAX_KEYLEN];
	पूर्णांक enckey_len;
	u8 enckey[MAX_KEYLEN];
	u8 salt[MAX_IVLEN];
	u8 nonce[CTR_RFC3686_NONCE_SIZE];
	अचिन्हित salted;
	atomic_t configuring;
	काष्ठा completion completion;
पूर्ण;

काष्ठा ixp_alg अणु
	काष्ठा skcipher_alg crypto;
	स्थिर काष्ठा ix_hash_algo *hash;
	u32 cfg_enc;
	u32 cfg_dec;

	पूर्णांक रेजिस्टरed;
पूर्ण;

काष्ठा ixp_aead_alg अणु
	काष्ठा aead_alg crypto;
	स्थिर काष्ठा ix_hash_algo *hash;
	u32 cfg_enc;
	u32 cfg_dec;

	पूर्णांक रेजिस्टरed;
पूर्ण;

अटल स्थिर काष्ठा ix_hash_algo hash_alg_md5 = अणु
	.cfgword	= 0xAA010004,
	.icv		= "\x01\x23\x45\x67\x89\xAB\xCD\xEF"
			  "\xFE\xDC\xBA\x98\x76\x54\x32\x10",
पूर्ण;
अटल स्थिर काष्ठा ix_hash_algo hash_alg_sha1 = अणु
	.cfgword	= 0x00000005,
	.icv		= "\x67\x45\x23\x01\xEF\xCD\xAB\x89\x98\xBA"
			  "\xDC\xFE\x10\x32\x54\x76\xC3\xD2\xE1\xF0",
पूर्ण;

अटल काष्ठा npe *npe_c;
अटल काष्ठा dma_pool *buffer_pool = शून्य;
अटल काष्ठा dma_pool *ctx_pool = शून्य;

अटल काष्ठा crypt_ctl *crypt_virt = शून्य;
अटल dma_addr_t crypt_phys;

अटल पूर्णांक support_aes = 1;

#घोषणा DRIVER_NAME "ixp4xx_crypto"

अटल काष्ठा platक्रमm_device *pdev;

अटल अंतरभूत dma_addr_t crypt_virt2phys(काष्ठा crypt_ctl *virt)
अणु
	वापस crypt_phys + (virt - crypt_virt) * माप(काष्ठा crypt_ctl);
पूर्ण

अटल अंतरभूत काष्ठा crypt_ctl *crypt_phys2virt(dma_addr_t phys)
अणु
	वापस crypt_virt + (phys - crypt_phys) / माप(काष्ठा crypt_ctl);
पूर्ण

अटल अंतरभूत u32 cipher_cfg_enc(काष्ठा crypto_tfm *tfm)
अणु
	वापस container_of(tfm->__crt_alg, काष्ठा ixp_alg,crypto.base)->cfg_enc;
पूर्ण

अटल अंतरभूत u32 cipher_cfg_dec(काष्ठा crypto_tfm *tfm)
अणु
	वापस container_of(tfm->__crt_alg, काष्ठा ixp_alg,crypto.base)->cfg_dec;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा ix_hash_algo *ix_hash(काष्ठा crypto_tfm *tfm)
अणु
	वापस container_of(tfm->__crt_alg, काष्ठा ixp_alg, crypto.base)->hash;
पूर्ण

अटल पूर्णांक setup_crypt_desc(व्योम)
अणु
	काष्ठा device *dev = &pdev->dev;
	BUILD_BUG_ON(माप(काष्ठा crypt_ctl) != 64);
	crypt_virt = dma_alloc_coherent(dev,
					NPE_QLEN * माप(काष्ठा crypt_ctl),
					&crypt_phys, GFP_ATOMIC);
	अगर (!crypt_virt)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल DEFINE_SPINLOCK(desc_lock);
अटल काष्ठा crypt_ctl *get_crypt_desc(व्योम)
अणु
	पूर्णांक i;
	अटल पूर्णांक idx = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&desc_lock, flags);

	अगर (unlikely(!crypt_virt))
		setup_crypt_desc();
	अगर (unlikely(!crypt_virt)) अणु
		spin_unlock_irqrestore(&desc_lock, flags);
		वापस शून्य;
	पूर्ण
	i = idx;
	अगर (crypt_virt[i].ctl_flags == CTL_FLAG_UNUSED) अणु
		अगर (++idx >= NPE_QLEN)
			idx = 0;
		crypt_virt[i].ctl_flags = CTL_FLAG_USED;
		spin_unlock_irqrestore(&desc_lock, flags);
		वापस crypt_virt +i;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&desc_lock, flags);
		वापस शून्य;
	पूर्ण
पूर्ण

अटल DEFINE_SPINLOCK(emerg_lock);
अटल काष्ठा crypt_ctl *get_crypt_desc_emerg(व्योम)
अणु
	पूर्णांक i;
	अटल पूर्णांक idx = NPE_QLEN;
	काष्ठा crypt_ctl *desc;
	अचिन्हित दीर्घ flags;

	desc = get_crypt_desc();
	अगर (desc)
		वापस desc;
	अगर (unlikely(!crypt_virt))
		वापस शून्य;

	spin_lock_irqsave(&emerg_lock, flags);
	i = idx;
	अगर (crypt_virt[i].ctl_flags == CTL_FLAG_UNUSED) अणु
		अगर (++idx >= NPE_QLEN_TOTAL)
			idx = NPE_QLEN;
		crypt_virt[i].ctl_flags = CTL_FLAG_USED;
		spin_unlock_irqrestore(&emerg_lock, flags);
		वापस crypt_virt +i;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&emerg_lock, flags);
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_buf_chain(काष्ठा device *dev, काष्ठा buffer_desc *buf,
			   dma_addr_t phys)
अणु
	जबतक (buf) अणु
		काष्ठा buffer_desc *buf1;
		u32 phys1;

		buf1 = buf->next;
		phys1 = buf->phys_next;
		dma_unmap_single(dev, buf->phys_next, buf->buf_len, buf->dir);
		dma_pool_मुक्त(buffer_pool, buf, phys);
		buf = buf1;
		phys = phys1;
	पूर्ण
पूर्ण

अटल काष्ठा tasklet_काष्ठा crypto_करोne_tasklet;

अटल व्योम finish_scattered_hmac(काष्ठा crypt_ctl *crypt)
अणु
	काष्ठा aead_request *req = crypt->data.aead_req;
	काष्ठा aead_ctx *req_ctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	पूर्णांक authsize = crypto_aead_authsize(tfm);
	पूर्णांक decryptlen = req->assoclen + req->cryptlen - authsize;

	अगर (req_ctx->encrypt) अणु
		scatterwalk_map_and_copy(req_ctx->hmac_virt,
			req->dst, decryptlen, authsize, 1);
	पूर्ण
	dma_pool_मुक्त(buffer_pool, req_ctx->hmac_virt, crypt->icv_rev_aes);
पूर्ण

अटल व्योम one_packet(dma_addr_t phys)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा crypt_ctl *crypt;
	काष्ठा ixp_ctx *ctx;
	पूर्णांक failed;

	failed = phys & 0x1 ? -EBADMSG : 0;
	phys &= ~0x3;
	crypt = crypt_phys2virt(phys);

	चयन (crypt->ctl_flags & CTL_FLAG_MASK) अणु
	हाल CTL_FLAG_PERFORM_AEAD: अणु
		काष्ठा aead_request *req = crypt->data.aead_req;
		काष्ठा aead_ctx *req_ctx = aead_request_ctx(req);

		मुक्त_buf_chain(dev, req_ctx->src, crypt->src_buf);
		मुक्त_buf_chain(dev, req_ctx->dst, crypt->dst_buf);
		अगर (req_ctx->hmac_virt) अणु
			finish_scattered_hmac(crypt);
		पूर्ण
		req->base.complete(&req->base, failed);
		अवरोध;
	पूर्ण
	हाल CTL_FLAG_PERFORM_ABLK: अणु
		काष्ठा skcipher_request *req = crypt->data.ablk_req;
		काष्ठा ablk_ctx *req_ctx = skcipher_request_ctx(req);

		अगर (req_ctx->dst) अणु
			मुक्त_buf_chain(dev, req_ctx->dst, crypt->dst_buf);
		पूर्ण
		मुक्त_buf_chain(dev, req_ctx->src, crypt->src_buf);
		req->base.complete(&req->base, failed);
		अवरोध;
	पूर्ण
	हाल CTL_FLAG_GEN_ICV:
		ctx = crypto_tfm_ctx(crypt->data.tfm);
		dma_pool_मुक्त(ctx_pool, crypt->regist_ptr,
				crypt->regist_buf->phys_addr);
		dma_pool_मुक्त(buffer_pool, crypt->regist_buf, crypt->src_buf);
		अगर (atomic_dec_and_test(&ctx->configuring))
			complete(&ctx->completion);
		अवरोध;
	हाल CTL_FLAG_GEN_REVAES:
		ctx = crypto_tfm_ctx(crypt->data.tfm);
		*(u32*)ctx->decrypt.npe_ctx &= cpu_to_be32(~CIPH_ENCR);
		अगर (atomic_dec_and_test(&ctx->configuring))
			complete(&ctx->completion);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	crypt->ctl_flags = CTL_FLAG_UNUSED;
पूर्ण

अटल व्योम irqhandler(व्योम *_unused)
अणु
	tasklet_schedule(&crypto_करोne_tasklet);
पूर्ण

अटल व्योम crypto_करोne_action(अचिन्हित दीर्घ arg)
अणु
	पूर्णांक i;

	क्रम(i=0; i<4; i++) अणु
		dma_addr_t phys = qmgr_get_entry(RECV_QID);
		अगर (!phys)
			वापस;
		one_packet(phys);
	पूर्ण
	tasklet_schedule(&crypto_करोne_tasklet);
पूर्ण

अटल पूर्णांक init_ixp_crypto(काष्ठा device *dev)
अणु
	पूर्णांक ret = -ENODEV;
	u32 msg[2] = अणु 0, 0 पूर्ण;

	अगर (! ( ~(*IXP4XX_EXP_CFG2) & (IXP4XX_FEATURE_HASH |
				IXP4XX_FEATURE_AES | IXP4XX_FEATURE_DES))) अणु
		prपूर्णांकk(KERN_ERR "ixp_crypto: No HW crypto available\n");
		वापस ret;
	पूर्ण
	npe_c = npe_request(NPE_ID);
	अगर (!npe_c)
		वापस ret;

	अगर (!npe_running(npe_c)) अणु
		ret = npe_load_firmware(npe_c, npe_name(npe_c), dev);
		अगर (ret)
			जाओ npe_release;
		अगर (npe_recv_message(npe_c, msg, "STATUS_MSG"))
			जाओ npe_error;
	पूर्ण अन्यथा अणु
		अगर (npe_send_message(npe_c, msg, "STATUS_MSG"))
			जाओ npe_error;

		अगर (npe_recv_message(npe_c, msg, "STATUS_MSG"))
			जाओ npe_error;
	पूर्ण

	चयन ((msg[1]>>16) & 0xff) अणु
	हाल 3:
		prपूर्णांकk(KERN_WARNING "Firmware of %s lacks AES support\n",
				npe_name(npe_c));
		support_aes = 0;
		अवरोध;
	हाल 4:
	हाल 5:
		support_aes = 1;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Firmware of %s lacks crypto support\n",
			npe_name(npe_c));
		ret = -ENODEV;
		जाओ npe_release;
	पूर्ण
	/* buffer_pool will also be used to someबार store the hmac,
	 * so assure it is large enough
	 */
	BUILD_BUG_ON(SHA1_DIGEST_SIZE > माप(काष्ठा buffer_desc));
	buffer_pool = dma_pool_create("buffer", dev,
			माप(काष्ठा buffer_desc), 32, 0);
	ret = -ENOMEM;
	अगर (!buffer_pool) अणु
		जाओ err;
	पूर्ण
	ctx_pool = dma_pool_create("context", dev,
			NPE_CTX_LEN, 16, 0);
	अगर (!ctx_pool) अणु
		जाओ err;
	पूर्ण
	ret = qmgr_request_queue(SEND_QID, NPE_QLEN_TOTAL, 0, 0,
				 "ixp_crypto:out", शून्य);
	अगर (ret)
		जाओ err;
	ret = qmgr_request_queue(RECV_QID, NPE_QLEN, 0, 0,
				 "ixp_crypto:in", शून्य);
	अगर (ret) अणु
		qmgr_release_queue(SEND_QID);
		जाओ err;
	पूर्ण
	qmgr_set_irq(RECV_QID, QUEUE_IRQ_SRC_NOT_EMPTY, irqhandler, शून्य);
	tasklet_init(&crypto_करोne_tasklet, crypto_करोne_action, 0);

	qmgr_enable_irq(RECV_QID);
	वापस 0;

npe_error:
	prपूर्णांकk(KERN_ERR "%s not responding\n", npe_name(npe_c));
	ret = -EIO;
err:
	dma_pool_destroy(ctx_pool);
	dma_pool_destroy(buffer_pool);
npe_release:
	npe_release(npe_c);
	वापस ret;
पूर्ण

अटल व्योम release_ixp_crypto(काष्ठा device *dev)
अणु
	qmgr_disable_irq(RECV_QID);
	tasklet_समाप्त(&crypto_करोne_tasklet);

	qmgr_release_queue(SEND_QID);
	qmgr_release_queue(RECV_QID);

	dma_pool_destroy(ctx_pool);
	dma_pool_destroy(buffer_pool);

	npe_release(npe_c);

	अगर (crypt_virt) अणु
		dma_मुक्त_coherent(dev,
			NPE_QLEN * माप(काष्ठा crypt_ctl),
			crypt_virt, crypt_phys);
	पूर्ण
पूर्ण

अटल व्योम reset_sa_dir(काष्ठा ix_sa_dir *dir)
अणु
	स_रखो(dir->npe_ctx, 0, NPE_CTX_LEN);
	dir->npe_ctx_idx = 0;
	dir->npe_mode = 0;
पूर्ण

अटल पूर्णांक init_sa_dir(काष्ठा ix_sa_dir *dir)
अणु
	dir->npe_ctx = dma_pool_alloc(ctx_pool, GFP_KERNEL, &dir->npe_ctx_phys);
	अगर (!dir->npe_ctx) अणु
		वापस -ENOMEM;
	पूर्ण
	reset_sa_dir(dir);
	वापस 0;
पूर्ण

अटल व्योम मुक्त_sa_dir(काष्ठा ix_sa_dir *dir)
अणु
	स_रखो(dir->npe_ctx, 0, NPE_CTX_LEN);
	dma_pool_मुक्त(ctx_pool, dir->npe_ctx, dir->npe_ctx_phys);
पूर्ण

अटल पूर्णांक init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ixp_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक ret;

	atomic_set(&ctx->configuring, 0);
	ret = init_sa_dir(&ctx->encrypt);
	अगर (ret)
		वापस ret;
	ret = init_sa_dir(&ctx->decrypt);
	अगर (ret) अणु
		मुक्त_sa_dir(&ctx->encrypt);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक init_tfm_ablk(काष्ठा crypto_skcipher *tfm)
अणु
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा ablk_ctx));
	वापस init_tfm(crypto_skcipher_tfm(tfm));
पूर्ण

अटल पूर्णांक init_tfm_aead(काष्ठा crypto_aead *tfm)
अणु
	crypto_aead_set_reqsize(tfm, माप(काष्ठा aead_ctx));
	वापस init_tfm(crypto_aead_tfm(tfm));
पूर्ण

अटल व्योम निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ixp_ctx *ctx = crypto_tfm_ctx(tfm);
	मुक्त_sa_dir(&ctx->encrypt);
	मुक्त_sa_dir(&ctx->decrypt);
पूर्ण

अटल व्योम निकास_tfm_ablk(काष्ठा crypto_skcipher *tfm)
अणु
	निकास_tfm(crypto_skcipher_tfm(tfm));
पूर्ण

अटल व्योम निकास_tfm_aead(काष्ठा crypto_aead *tfm)
अणु
	निकास_tfm(crypto_aead_tfm(tfm));
पूर्ण

अटल पूर्णांक रेजिस्टर_chain_var(काष्ठा crypto_tfm *tfm, u8 xpad, u32 target,
		पूर्णांक init_len, u32 ctx_addr, स्थिर u8 *key, पूर्णांक key_len)
अणु
	काष्ठा ixp_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा crypt_ctl *crypt;
	काष्ठा buffer_desc *buf;
	पूर्णांक i;
	u8 *pad;
	dma_addr_t pad_phys, buf_phys;

	BUILD_BUG_ON(NPE_CTX_LEN < HMAC_PAD_BLOCKLEN);
	pad = dma_pool_alloc(ctx_pool, GFP_KERNEL, &pad_phys);
	अगर (!pad)
		वापस -ENOMEM;
	buf = dma_pool_alloc(buffer_pool, GFP_KERNEL, &buf_phys);
	अगर (!buf) अणु
		dma_pool_मुक्त(ctx_pool, pad, pad_phys);
		वापस -ENOMEM;
	पूर्ण
	crypt = get_crypt_desc_emerg();
	अगर (!crypt) अणु
		dma_pool_मुक्त(ctx_pool, pad, pad_phys);
		dma_pool_मुक्त(buffer_pool, buf, buf_phys);
		वापस -EAGAIN;
	पूर्ण

	स_नकल(pad, key, key_len);
	स_रखो(pad + key_len, 0, HMAC_PAD_BLOCKLEN - key_len);
	क्रम (i = 0; i < HMAC_PAD_BLOCKLEN; i++) अणु
		pad[i] ^= xpad;
	पूर्ण

	crypt->data.tfm = tfm;
	crypt->regist_ptr = pad;
	crypt->regist_buf = buf;

	crypt->auth_offs = 0;
	crypt->auth_len = HMAC_PAD_BLOCKLEN;
	crypt->crypto_ctx = ctx_addr;
	crypt->src_buf = buf_phys;
	crypt->icv_rev_aes = target;
	crypt->mode = NPE_OP_HASH_GEN_ICV;
	crypt->init_len = init_len;
	crypt->ctl_flags |= CTL_FLAG_GEN_ICV;

	buf->next = 0;
	buf->buf_len = HMAC_PAD_BLOCKLEN;
	buf->pkt_len = 0;
	buf->phys_addr = pad_phys;

	atomic_inc(&ctx->configuring);
	qmgr_put_entry(SEND_QID, crypt_virt2phys(crypt));
	BUG_ON(qmgr_stat_overflow(SEND_QID));
	वापस 0;
पूर्ण

अटल पूर्णांक setup_auth(काष्ठा crypto_tfm *tfm, पूर्णांक encrypt, अचिन्हित authsize,
		स्थिर u8 *key, पूर्णांक key_len, अचिन्हित digest_len)
अणु
	u32 itarget, otarget, npe_ctx_addr;
	अचिन्हित अक्षर *cinfo;
	पूर्णांक init_len, ret = 0;
	u32 cfgword;
	काष्ठा ix_sa_dir *dir;
	काष्ठा ixp_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर काष्ठा ix_hash_algo *algo;

	dir = encrypt ? &ctx->encrypt : &ctx->decrypt;
	cinfo = dir->npe_ctx + dir->npe_ctx_idx;
	algo = ix_hash(tfm);

	/* ग_लिखो cfg word to cryptinfo */
	cfgword = algo->cfgword | ( authsize << 6); /* (authsize/4) << 8 */
#अगर_अघोषित __ARMEB__
	cfgword ^= 0xAA000000; /* change the "byte swap" flags */
#पूर्ण_अगर
	*(u32*)cinfo = cpu_to_be32(cfgword);
	cinfo += माप(cfgword);

	/* ग_लिखो ICV to cryptinfo */
	स_नकल(cinfo, algo->icv, digest_len);
	cinfo += digest_len;

	itarget = dir->npe_ctx_phys + dir->npe_ctx_idx
				+ माप(algo->cfgword);
	otarget = itarget + digest_len;
	init_len = cinfo - (dir->npe_ctx + dir->npe_ctx_idx);
	npe_ctx_addr = dir->npe_ctx_phys + dir->npe_ctx_idx;

	dir->npe_ctx_idx += init_len;
	dir->npe_mode |= NPE_OP_HASH_ENABLE;

	अगर (!encrypt)
		dir->npe_mode |= NPE_OP_HASH_VERIFY;

	ret = रेजिस्टर_chain_var(tfm, HMAC_OPAD_VALUE, otarget,
			init_len, npe_ctx_addr, key, key_len);
	अगर (ret)
		वापस ret;
	वापस रेजिस्टर_chain_var(tfm, HMAC_IPAD_VALUE, itarget,
			init_len, npe_ctx_addr, key, key_len);
पूर्ण

अटल पूर्णांक gen_rev_aes_key(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypt_ctl *crypt;
	काष्ठा ixp_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा ix_sa_dir *dir = &ctx->decrypt;

	crypt = get_crypt_desc_emerg();
	अगर (!crypt) अणु
		वापस -EAGAIN;
	पूर्ण
	*(u32*)dir->npe_ctx |= cpu_to_be32(CIPH_ENCR);

	crypt->data.tfm = tfm;
	crypt->crypt_offs = 0;
	crypt->crypt_len = AES_BLOCK128;
	crypt->src_buf = 0;
	crypt->crypto_ctx = dir->npe_ctx_phys;
	crypt->icv_rev_aes = dir->npe_ctx_phys + माप(u32);
	crypt->mode = NPE_OP_ENC_GEN_KEY;
	crypt->init_len = dir->npe_ctx_idx;
	crypt->ctl_flags |= CTL_FLAG_GEN_REVAES;

	atomic_inc(&ctx->configuring);
	qmgr_put_entry(SEND_QID, crypt_virt2phys(crypt));
	BUG_ON(qmgr_stat_overflow(SEND_QID));
	वापस 0;
पूर्ण

अटल पूर्णांक setup_cipher(काष्ठा crypto_tfm *tfm, पूर्णांक encrypt,
		स्थिर u8 *key, पूर्णांक key_len)
अणु
	u8 *cinfo;
	u32 cipher_cfg;
	u32 keylen_cfg = 0;
	काष्ठा ix_sa_dir *dir;
	काष्ठा ixp_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक err;

	dir = encrypt ? &ctx->encrypt : &ctx->decrypt;
	cinfo = dir->npe_ctx;

	अगर (encrypt) अणु
		cipher_cfg = cipher_cfg_enc(tfm);
		dir->npe_mode |= NPE_OP_CRYPT_ENCRYPT;
	पूर्ण अन्यथा अणु
		cipher_cfg = cipher_cfg_dec(tfm);
	पूर्ण
	अगर (cipher_cfg & MOD_AES) अणु
		चयन (key_len) अणु
		हाल 16: keylen_cfg = MOD_AES128; अवरोध;
		हाल 24: keylen_cfg = MOD_AES192; अवरोध;
		हाल 32: keylen_cfg = MOD_AES256; अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		cipher_cfg |= keylen_cfg;
	पूर्ण अन्यथा अणु
		err = crypto_des_verअगरy_key(tfm, key);
		अगर (err)
			वापस err;
	पूर्ण
	/* ग_लिखो cfg word to cryptinfo */
	*(u32*)cinfo = cpu_to_be32(cipher_cfg);
	cinfo += माप(cipher_cfg);

	/* ग_लिखो cipher key to cryptinfo */
	स_नकल(cinfo, key, key_len);
	/* NPE wants keylen set to DES3_EDE_KEY_SIZE even क्रम single DES */
	अगर (key_len < DES3_EDE_KEY_SIZE && !(cipher_cfg & MOD_AES)) अणु
		स_रखो(cinfo + key_len, 0, DES3_EDE_KEY_SIZE -key_len);
		key_len = DES3_EDE_KEY_SIZE;
	पूर्ण
	dir->npe_ctx_idx = माप(cipher_cfg) + key_len;
	dir->npe_mode |= NPE_OP_CRYPT_ENABLE;
	अगर ((cipher_cfg & MOD_AES) && !encrypt) अणु
		वापस gen_rev_aes_key(tfm);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा buffer_desc *chainup_buffers(काष्ठा device *dev,
		काष्ठा scatterlist *sg,	अचिन्हित nbytes,
		काष्ठा buffer_desc *buf, gfp_t flags,
		क्रमागत dma_data_direction dir)
अणु
	क्रम (; nbytes > 0; sg = sg_next(sg)) अणु
		अचिन्हित len = min(nbytes, sg->length);
		काष्ठा buffer_desc *next_buf;
		dma_addr_t next_buf_phys;
		व्योम *ptr;

		nbytes -= len;
		ptr = sg_virt(sg);
		next_buf = dma_pool_alloc(buffer_pool, flags, &next_buf_phys);
		अगर (!next_buf) अणु
			buf = शून्य;
			अवरोध;
		पूर्ण
		sg_dma_address(sg) = dma_map_single(dev, ptr, len, dir);
		buf->next = next_buf;
		buf->phys_next = next_buf_phys;
		buf = next_buf;

		buf->phys_addr = sg_dma_address(sg);
		buf->buf_len = len;
		buf->dir = dir;
	पूर्ण
	buf->next = शून्य;
	buf->phys_next = 0;
	वापस buf;
पूर्ण

अटल पूर्णांक ablk_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ixp_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक ret;

	init_completion(&ctx->completion);
	atomic_inc(&ctx->configuring);

	reset_sa_dir(&ctx->encrypt);
	reset_sa_dir(&ctx->decrypt);

	ctx->encrypt.npe_mode = NPE_OP_HMAC_DISABLE;
	ctx->decrypt.npe_mode = NPE_OP_HMAC_DISABLE;

	ret = setup_cipher(&tfm->base, 0, key, key_len);
	अगर (ret)
		जाओ out;
	ret = setup_cipher(&tfm->base, 1, key, key_len);
out:
	अगर (!atomic_dec_and_test(&ctx->configuring))
		रुको_क्रम_completion(&ctx->completion);
	वापस ret;
पूर्ण

अटल पूर्णांक ablk_des3_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक key_len)
अणु
	वापस verअगरy_skcipher_des3_key(tfm, key) ?:
	       ablk_setkey(tfm, key, key_len);
पूर्ण

अटल पूर्णांक ablk_rfc3686_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
		अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ixp_ctx *ctx = crypto_skcipher_ctx(tfm);

	/* the nonce is stored in bytes at end of key */
	अगर (key_len < CTR_RFC3686_NONCE_SIZE)
		वापस -EINVAL;

	स_नकल(ctx->nonce, key + (key_len - CTR_RFC3686_NONCE_SIZE),
			CTR_RFC3686_NONCE_SIZE);

	key_len -= CTR_RFC3686_NONCE_SIZE;
	वापस ablk_setkey(tfm, key, key_len);
पूर्ण

अटल पूर्णांक ablk_perक्रमm(काष्ठा skcipher_request *req, पूर्णांक encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ixp_ctx *ctx = crypto_skcipher_ctx(tfm);
	अचिन्हित ivsize = crypto_skcipher_ivsize(tfm);
	काष्ठा ix_sa_dir *dir;
	काष्ठा crypt_ctl *crypt;
	अचिन्हित पूर्णांक nbytes = req->cryptlen;
	क्रमागत dma_data_direction src_direction = DMA_BIसूचीECTIONAL;
	काष्ठा ablk_ctx *req_ctx = skcipher_request_ctx(req);
	काष्ठा buffer_desc src_hook;
	काष्ठा device *dev = &pdev->dev;
	gfp_t flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ?
				GFP_KERNEL : GFP_ATOMIC;

	अगर (qmgr_stat_full(SEND_QID))
		वापस -EAGAIN;
	अगर (atomic_पढ़ो(&ctx->configuring))
		वापस -EAGAIN;

	dir = encrypt ? &ctx->encrypt : &ctx->decrypt;

	crypt = get_crypt_desc();
	अगर (!crypt)
		वापस -ENOMEM;

	crypt->data.ablk_req = req;
	crypt->crypto_ctx = dir->npe_ctx_phys;
	crypt->mode = dir->npe_mode;
	crypt->init_len = dir->npe_ctx_idx;

	crypt->crypt_offs = 0;
	crypt->crypt_len = nbytes;

	BUG_ON(ivsize && !req->iv);
	स_नकल(crypt->iv, req->iv, ivsize);
	अगर (req->src != req->dst) अणु
		काष्ठा buffer_desc dst_hook;
		crypt->mode |= NPE_OP_NOT_IN_PLACE;
		/* This was never tested by Intel
		 * क्रम more than one dst buffer, I think. */
		req_ctx->dst = शून्य;
		अगर (!chainup_buffers(dev, req->dst, nbytes, &dst_hook,
					flags, DMA_FROM_DEVICE))
			जाओ मुक्त_buf_dest;
		src_direction = DMA_TO_DEVICE;
		req_ctx->dst = dst_hook.next;
		crypt->dst_buf = dst_hook.phys_next;
	पूर्ण अन्यथा अणु
		req_ctx->dst = शून्य;
	पूर्ण
	req_ctx->src = शून्य;
	अगर (!chainup_buffers(dev, req->src, nbytes, &src_hook,
				flags, src_direction))
		जाओ मुक्त_buf_src;

	req_ctx->src = src_hook.next;
	crypt->src_buf = src_hook.phys_next;
	crypt->ctl_flags |= CTL_FLAG_PERFORM_ABLK;
	qmgr_put_entry(SEND_QID, crypt_virt2phys(crypt));
	BUG_ON(qmgr_stat_overflow(SEND_QID));
	वापस -EINPROGRESS;

मुक्त_buf_src:
	मुक्त_buf_chain(dev, req_ctx->src, crypt->src_buf);
मुक्त_buf_dest:
	अगर (req->src != req->dst) अणु
		मुक्त_buf_chain(dev, req_ctx->dst, crypt->dst_buf);
	पूर्ण
	crypt->ctl_flags = CTL_FLAG_UNUSED;
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक ablk_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ablk_perक्रमm(req, 1);
पूर्ण

अटल पूर्णांक ablk_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ablk_perक्रमm(req, 0);
पूर्ण

अटल पूर्णांक ablk_rfc3686_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ixp_ctx *ctx = crypto_skcipher_ctx(tfm);
	u8 iv[CTR_RFC3686_BLOCK_SIZE];
	u8 *info = req->iv;
	पूर्णांक ret;

	/* set up counter block */
        स_नकल(iv, ctx->nonce, CTR_RFC3686_NONCE_SIZE);
	स_नकल(iv + CTR_RFC3686_NONCE_SIZE, info, CTR_RFC3686_IV_SIZE);

	/* initialize counter portion of counter block */
	*(__be32 *)(iv + CTR_RFC3686_NONCE_SIZE + CTR_RFC3686_IV_SIZE) =
		cpu_to_be32(1);

	req->iv = iv;
	ret = ablk_perक्रमm(req, 1);
	req->iv = info;
	वापस ret;
पूर्ण

अटल पूर्णांक aead_perक्रमm(काष्ठा aead_request *req, पूर्णांक encrypt,
		पूर्णांक cryptoffset, पूर्णांक eff_cryptlen, u8 *iv)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा ixp_ctx *ctx = crypto_aead_ctx(tfm);
	अचिन्हित ivsize = crypto_aead_ivsize(tfm);
	अचिन्हित authsize = crypto_aead_authsize(tfm);
	काष्ठा ix_sa_dir *dir;
	काष्ठा crypt_ctl *crypt;
	अचिन्हित पूर्णांक cryptlen;
	काष्ठा buffer_desc *buf, src_hook;
	काष्ठा aead_ctx *req_ctx = aead_request_ctx(req);
	काष्ठा device *dev = &pdev->dev;
	gfp_t flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ?
				GFP_KERNEL : GFP_ATOMIC;
	क्रमागत dma_data_direction src_direction = DMA_BIसूचीECTIONAL;
	अचिन्हित पूर्णांक lastlen;

	अगर (qmgr_stat_full(SEND_QID))
		वापस -EAGAIN;
	अगर (atomic_पढ़ो(&ctx->configuring))
		वापस -EAGAIN;

	अगर (encrypt) अणु
		dir = &ctx->encrypt;
		cryptlen = req->cryptlen;
	पूर्ण अन्यथा अणु
		dir = &ctx->decrypt;
		/* req->cryptlen includes the authsize when decrypting */
		cryptlen = req->cryptlen -authsize;
		eff_cryptlen -= authsize;
	पूर्ण
	crypt = get_crypt_desc();
	अगर (!crypt)
		वापस -ENOMEM;

	crypt->data.aead_req = req;
	crypt->crypto_ctx = dir->npe_ctx_phys;
	crypt->mode = dir->npe_mode;
	crypt->init_len = dir->npe_ctx_idx;

	crypt->crypt_offs = cryptoffset;
	crypt->crypt_len = eff_cryptlen;

	crypt->auth_offs = 0;
	crypt->auth_len = req->assoclen + cryptlen;
	BUG_ON(ivsize && !req->iv);
	स_नकल(crypt->iv, req->iv, ivsize);

	buf = chainup_buffers(dev, req->src, crypt->auth_len,
			      &src_hook, flags, src_direction);
	req_ctx->src = src_hook.next;
	crypt->src_buf = src_hook.phys_next;
	अगर (!buf)
		जाओ मुक्त_buf_src;

	lastlen = buf->buf_len;
	अगर (lastlen >= authsize)
		crypt->icv_rev_aes = buf->phys_addr +
				     buf->buf_len - authsize;

	req_ctx->dst = शून्य;

	अगर (req->src != req->dst) अणु
		काष्ठा buffer_desc dst_hook;

		crypt->mode |= NPE_OP_NOT_IN_PLACE;
		src_direction = DMA_TO_DEVICE;

		buf = chainup_buffers(dev, req->dst, crypt->auth_len,
				      &dst_hook, flags, DMA_FROM_DEVICE);
		req_ctx->dst = dst_hook.next;
		crypt->dst_buf = dst_hook.phys_next;

		अगर (!buf)
			जाओ मुक्त_buf_dst;

		अगर (encrypt) अणु
			lastlen = buf->buf_len;
			अगर (lastlen >= authsize)
				crypt->icv_rev_aes = buf->phys_addr +
						     buf->buf_len - authsize;
		पूर्ण
	पूर्ण

	अगर (unlikely(lastlen < authsize)) अणु
		/* The 12 hmac bytes are scattered,
		 * we need to copy them पूर्णांकo a safe buffer */
		req_ctx->hmac_virt = dma_pool_alloc(buffer_pool, flags,
				&crypt->icv_rev_aes);
		अगर (unlikely(!req_ctx->hmac_virt))
			जाओ मुक्त_buf_dst;
		अगर (!encrypt) अणु
			scatterwalk_map_and_copy(req_ctx->hmac_virt,
				req->src, cryptlen, authsize, 0);
		पूर्ण
		req_ctx->encrypt = encrypt;
	पूर्ण अन्यथा अणु
		req_ctx->hmac_virt = शून्य;
	पूर्ण

	crypt->ctl_flags |= CTL_FLAG_PERFORM_AEAD;
	qmgr_put_entry(SEND_QID, crypt_virt2phys(crypt));
	BUG_ON(qmgr_stat_overflow(SEND_QID));
	वापस -EINPROGRESS;

मुक्त_buf_dst:
	मुक्त_buf_chain(dev, req_ctx->dst, crypt->dst_buf);
मुक्त_buf_src:
	मुक्त_buf_chain(dev, req_ctx->src, crypt->src_buf);
	crypt->ctl_flags = CTL_FLAG_UNUSED;
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक aead_setup(काष्ठा crypto_aead *tfm, अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा ixp_ctx *ctx = crypto_aead_ctx(tfm);
	अचिन्हित digest_len = crypto_aead_maxauthsize(tfm);
	पूर्णांक ret;

	अगर (!ctx->enckey_len && !ctx->authkey_len)
		वापस 0;
	init_completion(&ctx->completion);
	atomic_inc(&ctx->configuring);

	reset_sa_dir(&ctx->encrypt);
	reset_sa_dir(&ctx->decrypt);

	ret = setup_cipher(&tfm->base, 0, ctx->enckey, ctx->enckey_len);
	अगर (ret)
		जाओ out;
	ret = setup_cipher(&tfm->base, 1, ctx->enckey, ctx->enckey_len);
	अगर (ret)
		जाओ out;
	ret = setup_auth(&tfm->base, 0, authsize, ctx->authkey,
			ctx->authkey_len, digest_len);
	अगर (ret)
		जाओ out;
	ret = setup_auth(&tfm->base, 1, authsize,  ctx->authkey,
			ctx->authkey_len, digest_len);
out:
	अगर (!atomic_dec_and_test(&ctx->configuring))
		रुको_क्रम_completion(&ctx->completion);
	वापस ret;
पूर्ण

अटल पूर्णांक aead_setauthsize(काष्ठा crypto_aead *tfm, अचिन्हित पूर्णांक authsize)
अणु
	पूर्णांक max = crypto_aead_maxauthsize(tfm) >> 2;

	अगर ((authsize>>2) < 1 || (authsize>>2) > max || (authsize & 3))
		वापस -EINVAL;
	वापस aead_setup(tfm, authsize);
पूर्ण

अटल पूर्णांक aead_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ixp_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_authenc_keys keys;

	अगर (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		जाओ badkey;

	अगर (keys.authkeylen > माप(ctx->authkey))
		जाओ badkey;

	अगर (keys.enckeylen > माप(ctx->enckey))
		जाओ badkey;

	स_नकल(ctx->authkey, keys.authkey, keys.authkeylen);
	स_नकल(ctx->enckey, keys.enckey, keys.enckeylen);
	ctx->authkey_len = keys.authkeylen;
	ctx->enckey_len = keys.enckeylen;

	memzero_explicit(&keys, माप(keys));
	वापस aead_setup(tfm, crypto_aead_authsize(tfm));
badkey:
	memzero_explicit(&keys, माप(keys));
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक des3_aead_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ixp_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_authenc_keys keys;
	पूर्णांक err;

	err = crypto_authenc_extractkeys(&keys, key, keylen);
	अगर (unlikely(err))
		जाओ badkey;

	err = -EINVAL;
	अगर (keys.authkeylen > माप(ctx->authkey))
		जाओ badkey;

	err = verअगरy_aead_des3_key(tfm, keys.enckey, keys.enckeylen);
	अगर (err)
		जाओ badkey;

	स_नकल(ctx->authkey, keys.authkey, keys.authkeylen);
	स_नकल(ctx->enckey, keys.enckey, keys.enckeylen);
	ctx->authkey_len = keys.authkeylen;
	ctx->enckey_len = keys.enckeylen;

	memzero_explicit(&keys, माप(keys));
	वापस aead_setup(tfm, crypto_aead_authsize(tfm));
badkey:
	memzero_explicit(&keys, माप(keys));
	वापस err;
पूर्ण

अटल पूर्णांक aead_encrypt(काष्ठा aead_request *req)
अणु
	वापस aead_perक्रमm(req, 1, req->assoclen, req->cryptlen, req->iv);
पूर्ण

अटल पूर्णांक aead_decrypt(काष्ठा aead_request *req)
अणु
	वापस aead_perक्रमm(req, 0, req->assoclen, req->cryptlen, req->iv);
पूर्ण

अटल काष्ठा ixp_alg ixp4xx_algos[] = अणु
अणु
	.crypto	= अणु
		.base.cra_name		= "cbc(des)",
		.base.cra_blocksize	= DES_BLOCK_SIZE,

		.min_keysize		= DES_KEY_SIZE,
		.max_keysize		= DES_KEY_SIZE,
		.ivsize			= DES_BLOCK_SIZE,
	पूर्ण,
	.cfg_enc = CIPH_ENCR | MOD_DES | MOD_CBC_ENC | KEYLEN_192,
	.cfg_dec = CIPH_DECR | MOD_DES | MOD_CBC_DEC | KEYLEN_192,

पूर्ण, अणु
	.crypto	= अणु
		.base.cra_name		= "ecb(des)",
		.base.cra_blocksize	= DES_BLOCK_SIZE,
		.min_keysize		= DES_KEY_SIZE,
		.max_keysize		= DES_KEY_SIZE,
	पूर्ण,
	.cfg_enc = CIPH_ENCR | MOD_DES | MOD_ECB | KEYLEN_192,
	.cfg_dec = CIPH_DECR | MOD_DES | MOD_ECB | KEYLEN_192,
पूर्ण, अणु
	.crypto	= अणु
		.base.cra_name		= "cbc(des3_ede)",
		.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,

		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.ivsize			= DES3_EDE_BLOCK_SIZE,
		.setkey			= ablk_des3_setkey,
	पूर्ण,
	.cfg_enc = CIPH_ENCR | MOD_3DES | MOD_CBC_ENC | KEYLEN_192,
	.cfg_dec = CIPH_DECR | MOD_3DES | MOD_CBC_DEC | KEYLEN_192,
पूर्ण, अणु
	.crypto	= अणु
		.base.cra_name		= "ecb(des3_ede)",
		.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,

		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.setkey			= ablk_des3_setkey,
	पूर्ण,
	.cfg_enc = CIPH_ENCR | MOD_3DES | MOD_ECB | KEYLEN_192,
	.cfg_dec = CIPH_DECR | MOD_3DES | MOD_ECB | KEYLEN_192,
पूर्ण, अणु
	.crypto	= अणु
		.base.cra_name		= "cbc(aes)",
		.base.cra_blocksize	= AES_BLOCK_SIZE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BLOCK_SIZE,
	पूर्ण,
	.cfg_enc = CIPH_ENCR | MOD_AES | MOD_CBC_ENC,
	.cfg_dec = CIPH_DECR | MOD_AES | MOD_CBC_DEC,
पूर्ण, अणु
	.crypto	= अणु
		.base.cra_name		= "ecb(aes)",
		.base.cra_blocksize	= AES_BLOCK_SIZE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
	पूर्ण,
	.cfg_enc = CIPH_ENCR | MOD_AES | MOD_ECB,
	.cfg_dec = CIPH_DECR | MOD_AES | MOD_ECB,
पूर्ण, अणु
	.crypto	= अणु
		.base.cra_name		= "ctr(aes)",
		.base.cra_blocksize	= 1,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BLOCK_SIZE,
	पूर्ण,
	.cfg_enc = CIPH_ENCR | MOD_AES | MOD_CTR,
	.cfg_dec = CIPH_ENCR | MOD_AES | MOD_CTR,
पूर्ण, अणु
	.crypto	= अणु
		.base.cra_name		= "rfc3686(ctr(aes))",
		.base.cra_blocksize	= 1,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BLOCK_SIZE,
		.setkey			= ablk_rfc3686_setkey,
		.encrypt		= ablk_rfc3686_crypt,
		.decrypt		= ablk_rfc3686_crypt,
	पूर्ण,
	.cfg_enc = CIPH_ENCR | MOD_AES | MOD_CTR,
	.cfg_dec = CIPH_ENCR | MOD_AES | MOD_CTR,
पूर्ण पूर्ण;

अटल काष्ठा ixp_aead_alg ixp4xx_aeads[] = अणु
अणु
	.crypto	= अणु
		.base = अणु
			.cra_name	= "authenc(hmac(md5),cbc(des))",
			.cra_blocksize	= DES_BLOCK_SIZE,
		पूर्ण,
		.ivsize		= DES_BLOCK_SIZE,
		.maxauthsize	= MD5_DIGEST_SIZE,
	पूर्ण,
	.hash = &hash_alg_md5,
	.cfg_enc = CIPH_ENCR | MOD_DES | MOD_CBC_ENC | KEYLEN_192,
	.cfg_dec = CIPH_DECR | MOD_DES | MOD_CBC_DEC | KEYLEN_192,
पूर्ण, अणु
	.crypto	= अणु
		.base = अणु
			.cra_name	= "authenc(hmac(md5),cbc(des3_ede))",
			.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
		पूर्ण,
		.ivsize		= DES3_EDE_BLOCK_SIZE,
		.maxauthsize	= MD5_DIGEST_SIZE,
		.setkey		= des3_aead_setkey,
	पूर्ण,
	.hash = &hash_alg_md5,
	.cfg_enc = CIPH_ENCR | MOD_3DES | MOD_CBC_ENC | KEYLEN_192,
	.cfg_dec = CIPH_DECR | MOD_3DES | MOD_CBC_DEC | KEYLEN_192,
पूर्ण, अणु
	.crypto	= अणु
		.base = अणु
			.cra_name	= "authenc(hmac(sha1),cbc(des))",
			.cra_blocksize	= DES_BLOCK_SIZE,
		पूर्ण,
			.ivsize		= DES_BLOCK_SIZE,
			.maxauthsize	= SHA1_DIGEST_SIZE,
	पूर्ण,
	.hash = &hash_alg_sha1,
	.cfg_enc = CIPH_ENCR | MOD_DES | MOD_CBC_ENC | KEYLEN_192,
	.cfg_dec = CIPH_DECR | MOD_DES | MOD_CBC_DEC | KEYLEN_192,
पूर्ण, अणु
	.crypto	= अणु
		.base = अणु
			.cra_name	= "authenc(hmac(sha1),cbc(des3_ede))",
			.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
		पूर्ण,
		.ivsize		= DES3_EDE_BLOCK_SIZE,
		.maxauthsize	= SHA1_DIGEST_SIZE,
		.setkey		= des3_aead_setkey,
	पूर्ण,
	.hash = &hash_alg_sha1,
	.cfg_enc = CIPH_ENCR | MOD_3DES | MOD_CBC_ENC | KEYLEN_192,
	.cfg_dec = CIPH_DECR | MOD_3DES | MOD_CBC_DEC | KEYLEN_192,
पूर्ण, अणु
	.crypto	= अणु
		.base = अणु
			.cra_name	= "authenc(hmac(md5),cbc(aes))",
			.cra_blocksize	= AES_BLOCK_SIZE,
		पूर्ण,
		.ivsize		= AES_BLOCK_SIZE,
		.maxauthsize	= MD5_DIGEST_SIZE,
	पूर्ण,
	.hash = &hash_alg_md5,
	.cfg_enc = CIPH_ENCR | MOD_AES | MOD_CBC_ENC,
	.cfg_dec = CIPH_DECR | MOD_AES | MOD_CBC_DEC,
पूर्ण, अणु
	.crypto	= अणु
		.base = अणु
			.cra_name	= "authenc(hmac(sha1),cbc(aes))",
			.cra_blocksize	= AES_BLOCK_SIZE,
		पूर्ण,
		.ivsize		= AES_BLOCK_SIZE,
		.maxauthsize	= SHA1_DIGEST_SIZE,
	पूर्ण,
	.hash = &hash_alg_sha1,
	.cfg_enc = CIPH_ENCR | MOD_AES | MOD_CBC_ENC,
	.cfg_dec = CIPH_DECR | MOD_AES | MOD_CBC_DEC,
पूर्ण पूर्ण;

#घोषणा IXP_POSTFIX "-ixp4xx"

अटल स्थिर काष्ठा platक्रमm_device_info ixp_dev_info __initdata = अणु
	.name		= DRIVER_NAME,
	.id		= 0,
	.dma_mask	= DMA_BIT_MASK(32),
पूर्ण;

अटल पूर्णांक __init ixp_module_init(व्योम)
अणु
	पूर्णांक num = ARRAY_SIZE(ixp4xx_algos);
	पूर्णांक i, err;

	pdev = platक्रमm_device_रेजिस्टर_full(&ixp_dev_info);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	err = init_ixp_crypto(&pdev->dev);
	अगर (err) अणु
		platक्रमm_device_unरेजिस्टर(pdev);
		वापस err;
	पूर्ण
	क्रम (i=0; i< num; i++) अणु
		काष्ठा skcipher_alg *cra = &ixp4xx_algos[i].crypto;

		अगर (snम_लिखो(cra->base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
			"%s"IXP_POSTFIX, cra->base.cra_name) >=
			CRYPTO_MAX_ALG_NAME)
		अणु
			जारी;
		पूर्ण
		अगर (!support_aes && (ixp4xx_algos[i].cfg_enc & MOD_AES)) अणु
			जारी;
		पूर्ण

		/* block ciphers */
		cra->base.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY |
				      CRYPTO_ALG_ASYNC |
				      CRYPTO_ALG_ALLOCATES_MEMORY;
		अगर (!cra->setkey)
			cra->setkey = ablk_setkey;
		अगर (!cra->encrypt)
			cra->encrypt = ablk_encrypt;
		अगर (!cra->decrypt)
			cra->decrypt = ablk_decrypt;
		cra->init = init_tfm_ablk;
		cra->निकास = निकास_tfm_ablk;

		cra->base.cra_ctxsize = माप(काष्ठा ixp_ctx);
		cra->base.cra_module = THIS_MODULE;
		cra->base.cra_alignmask = 3;
		cra->base.cra_priority = 300;
		अगर (crypto_रेजिस्टर_skcipher(cra))
			prपूर्णांकk(KERN_ERR "Failed to register '%s'\n",
				cra->base.cra_name);
		अन्यथा
			ixp4xx_algos[i].रेजिस्टरed = 1;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ixp4xx_aeads); i++) अणु
		काष्ठा aead_alg *cra = &ixp4xx_aeads[i].crypto;

		अगर (snम_लिखो(cra->base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
			     "%s"IXP_POSTFIX, cra->base.cra_name) >=
		    CRYPTO_MAX_ALG_NAME)
			जारी;
		अगर (!support_aes && (ixp4xx_algos[i].cfg_enc & MOD_AES))
			जारी;

		/* authenc */
		cra->base.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY |
				      CRYPTO_ALG_ASYNC |
				      CRYPTO_ALG_ALLOCATES_MEMORY;
		cra->setkey = cra->setkey ?: aead_setkey;
		cra->setauthsize = aead_setauthsize;
		cra->encrypt = aead_encrypt;
		cra->decrypt = aead_decrypt;
		cra->init = init_tfm_aead;
		cra->निकास = निकास_tfm_aead;

		cra->base.cra_ctxsize = माप(काष्ठा ixp_ctx);
		cra->base.cra_module = THIS_MODULE;
		cra->base.cra_alignmask = 3;
		cra->base.cra_priority = 300;

		अगर (crypto_रेजिस्टर_aead(cra))
			prपूर्णांकk(KERN_ERR "Failed to register '%s'\n",
				cra->base.cra_driver_name);
		अन्यथा
			ixp4xx_aeads[i].रेजिस्टरed = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास ixp_module_निकास(व्योम)
अणु
	पूर्णांक num = ARRAY_SIZE(ixp4xx_algos);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ixp4xx_aeads); i++) अणु
		अगर (ixp4xx_aeads[i].रेजिस्टरed)
			crypto_unरेजिस्टर_aead(&ixp4xx_aeads[i].crypto);
	पूर्ण

	क्रम (i=0; i< num; i++) अणु
		अगर (ixp4xx_algos[i].रेजिस्टरed)
			crypto_unरेजिस्टर_skcipher(&ixp4xx_algos[i].crypto);
	पूर्ण
	release_ixp_crypto(&pdev->dev);
	platक्रमm_device_unरेजिस्टर(pdev);
पूर्ण

module_init(ixp_module_init);
module_निकास(ixp_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hohnstaedt <chohnstaedt@innominate.com>");
MODULE_DESCRIPTION("IXP4xx hardware crypto");

