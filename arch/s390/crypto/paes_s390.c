<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cryptographic API.
 *
 * s390 implementation of the AES Cipher Algorithm with रक्षित keys.
 *
 * s390 Version:
 *   Copyright IBM Corp. 2017,2020
 *   Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 *		Harald Freudenberger <freude@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "paes_s390"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/xts.h>
#समावेश <यंत्र/cpacf.h>
#समावेश <यंत्र/pkey.h>

/*
 * Key blobs smaller/bigger than these defines are rejected
 * by the common code even beक्रमe the inभागidual setkey function
 * is called. As paes can handle dअगरferent kinds of key blobs
 * and padding is also possible, the limits need to be generous.
 */
#घोषणा PAES_MIN_KEYSIZE 16
#घोषणा PAES_MAX_KEYSIZE 320

अटल u8 *ctrblk;
अटल DEFINE_MUTEX(ctrblk_lock);

अटल cpacf_mask_t km_functions, kmc_functions, kmctr_functions;

काष्ठा key_blob अणु
	/*
	 * Small keys will be stored in the keybuf. Larger keys are
	 * stored in extra allocated memory. In both हालs करोes
	 * key poपूर्णांक to the memory where the key is stored.
	 * The code distinguishes by checking keylen against
	 * माप(keybuf). See the two following helper functions.
	 */
	u8 *key;
	u8 keybuf[128];
	अचिन्हित पूर्णांक keylen;
पूर्ण;

अटल अंतरभूत पूर्णांक _key_to_kb(काष्ठा key_blob *kb,
			     स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा clearkey_header अणु
		u8  type;
		u8  res0[3];
		u8  version;
		u8  res1[3];
		u32 keytype;
		u32 len;
	पूर्ण __packed * h;

	चयन (keylen) अणु
	हाल 16:
	हाल 24:
	हाल 32:
		/* clear key value, prepare pkey clear key token in keybuf */
		स_रखो(kb->keybuf, 0, माप(kb->keybuf));
		h = (काष्ठा clearkey_header *) kb->keybuf;
		h->version = 0x02; /* TOKVER_CLEAR_KEY */
		h->keytype = (keylen - 8) >> 3;
		h->len = keylen;
		स_नकल(kb->keybuf + माप(*h), key, keylen);
		kb->keylen = माप(*h) + keylen;
		kb->key = kb->keybuf;
		अवरोध;
	शेष:
		/* other key material, let pkey handle this */
		अगर (keylen <= माप(kb->keybuf))
			kb->key = kb->keybuf;
		अन्यथा अणु
			kb->key = kदो_स्मृति(keylen, GFP_KERNEL);
			अगर (!kb->key)
				वापस -ENOMEM;
		पूर्ण
		स_नकल(kb->key, key, keylen);
		kb->keylen = keylen;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम _मुक्त_kb_keybuf(काष्ठा key_blob *kb)
अणु
	अगर (kb->key && kb->key != kb->keybuf
	    && kb->keylen > माप(kb->keybuf)) अणु
		kमुक्त(kb->key);
		kb->key = शून्य;
	पूर्ण
पूर्ण

काष्ठा s390_paes_ctx अणु
	काष्ठा key_blob kb;
	काष्ठा pkey_protkey pk;
	spinlock_t pk_lock;
	अचिन्हित दीर्घ fc;
पूर्ण;

काष्ठा s390_pxts_ctx अणु
	काष्ठा key_blob kb[2];
	काष्ठा pkey_protkey pk[2];
	spinlock_t pk_lock;
	अचिन्हित दीर्घ fc;
पूर्ण;

अटल अंतरभूत पूर्णांक __paes_keyblob2pkey(काष्ठा key_blob *kb,
				     काष्ठा pkey_protkey *pk)
अणु
	पूर्णांक i, ret;

	/* try three बार in हाल of failure */
	क्रम (i = 0; i < 3; i++) अणु
		अगर (i > 0 && ret == -EAGAIN && in_task())
			अगर (msleep_पूर्णांकerruptible(1000))
				वापस -EINTR;
		ret = pkey_keyblob2pkey(kb->key, kb->keylen, pk);
		अगर (ret == 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक __paes_convert_key(काष्ठा s390_paes_ctx *ctx)
अणु
	पूर्णांक ret;
	काष्ठा pkey_protkey pkey;

	ret = __paes_keyblob2pkey(&ctx->kb, &pkey);
	अगर (ret)
		वापस ret;

	spin_lock_bh(&ctx->pk_lock);
	स_नकल(&ctx->pk, &pkey, माप(pkey));
	spin_unlock_bh(&ctx->pk_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ecb_paes_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->kb.key = शून्य;
	spin_lock_init(&ctx->pk_lock);

	वापस 0;
पूर्ण

अटल व्योम ecb_paes_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);

	_मुक्त_kb_keybuf(&ctx->kb);
पूर्ण

अटल अंतरभूत पूर्णांक __ecb_paes_set_key(काष्ठा s390_paes_ctx *ctx)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ fc;

	rc = __paes_convert_key(ctx);
	अगर (rc)
		वापस rc;

	/* Pick the correct function code based on the रक्षित key type */
	fc = (ctx->pk.type == PKEY_KEYTYPE_AES_128) ? CPACF_KM_PAES_128 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_192) ? CPACF_KM_PAES_192 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_256) ? CPACF_KM_PAES_256 : 0;

	/* Check अगर the function code is available */
	ctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;

	वापस ctx->fc ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक ecb_paes_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			    अचिन्हित पूर्णांक key_len)
अणु
	पूर्णांक rc;
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);

	_मुक्त_kb_keybuf(&ctx->kb);
	rc = _key_to_kb(&ctx->kb, in_key, key_len);
	अगर (rc)
		वापस rc;

	वापस __ecb_paes_set_key(ctx);
पूर्ण

अटल पूर्णांक ecb_paes_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ modअगरier)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes, n, k;
	पूर्णांक ret;
	काष्ठा अणु
		u8 key[MAXPROTKEYSIZE];
	पूर्ण param;

	ret = skcipher_walk_virt(&walk, req, false);
	अगर (ret)
		वापस ret;

	spin_lock_bh(&ctx->pk_lock);
	स_नकल(param.key, ctx->pk.protkey, MAXPROTKEYSIZE);
	spin_unlock_bh(&ctx->pk_lock);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		/* only use complete blocks */
		n = nbytes & ~(AES_BLOCK_SIZE - 1);
		k = cpacf_km(ctx->fc | modअगरier, &param,
			     walk.dst.virt.addr, walk.src.virt.addr, n);
		अगर (k)
			ret = skcipher_walk_करोne(&walk, nbytes - k);
		अगर (k < n) अणु
			अगर (__paes_convert_key(ctx))
				वापस skcipher_walk_करोne(&walk, -EIO);
			spin_lock_bh(&ctx->pk_lock);
			स_नकल(param.key, ctx->pk.protkey, MAXPROTKEYSIZE);
			spin_unlock_bh(&ctx->pk_lock);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ecb_paes_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ecb_paes_crypt(req, 0);
पूर्ण

अटल पूर्णांक ecb_paes_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ecb_paes_crypt(req, CPACF_DECRYPT);
पूर्ण

अटल काष्ठा skcipher_alg ecb_paes_alg = अणु
	.base.cra_name		=	"ecb(paes)",
	.base.cra_driver_name	=	"ecb-paes-s390",
	.base.cra_priority	=	401,	/* combo: aes + ecb + 1 */
	.base.cra_blocksize	=	AES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा s390_paes_ctx),
	.base.cra_module	=	THIS_MODULE,
	.base.cra_list		=	LIST_HEAD_INIT(ecb_paes_alg.base.cra_list),
	.init			=	ecb_paes_init,
	.निकास			=	ecb_paes_निकास,
	.min_keysize		=	PAES_MIN_KEYSIZE,
	.max_keysize		=	PAES_MAX_KEYSIZE,
	.setkey			=	ecb_paes_set_key,
	.encrypt		=	ecb_paes_encrypt,
	.decrypt		=	ecb_paes_decrypt,
पूर्ण;

अटल पूर्णांक cbc_paes_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->kb.key = शून्य;
	spin_lock_init(&ctx->pk_lock);

	वापस 0;
पूर्ण

अटल व्योम cbc_paes_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);

	_मुक्त_kb_keybuf(&ctx->kb);
पूर्ण

अटल अंतरभूत पूर्णांक __cbc_paes_set_key(काष्ठा s390_paes_ctx *ctx)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ fc;

	rc = __paes_convert_key(ctx);
	अगर (rc)
		वापस rc;

	/* Pick the correct function code based on the रक्षित key type */
	fc = (ctx->pk.type == PKEY_KEYTYPE_AES_128) ? CPACF_KMC_PAES_128 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_192) ? CPACF_KMC_PAES_192 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_256) ? CPACF_KMC_PAES_256 : 0;

	/* Check अगर the function code is available */
	ctx->fc = (fc && cpacf_test_func(&kmc_functions, fc)) ? fc : 0;

	वापस ctx->fc ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक cbc_paes_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			    अचिन्हित पूर्णांक key_len)
अणु
	पूर्णांक rc;
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);

	_मुक्त_kb_keybuf(&ctx->kb);
	rc = _key_to_kb(&ctx->kb, in_key, key_len);
	अगर (rc)
		वापस rc;

	वापस __cbc_paes_set_key(ctx);
पूर्ण

अटल पूर्णांक cbc_paes_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ modअगरier)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes, n, k;
	पूर्णांक ret;
	काष्ठा अणु
		u8 iv[AES_BLOCK_SIZE];
		u8 key[MAXPROTKEYSIZE];
	पूर्ण param;

	ret = skcipher_walk_virt(&walk, req, false);
	अगर (ret)
		वापस ret;

	स_नकल(param.iv, walk.iv, AES_BLOCK_SIZE);
	spin_lock_bh(&ctx->pk_lock);
	स_नकल(param.key, ctx->pk.protkey, MAXPROTKEYSIZE);
	spin_unlock_bh(&ctx->pk_lock);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		/* only use complete blocks */
		n = nbytes & ~(AES_BLOCK_SIZE - 1);
		k = cpacf_kmc(ctx->fc | modअगरier, &param,
			      walk.dst.virt.addr, walk.src.virt.addr, n);
		अगर (k) अणु
			स_नकल(walk.iv, param.iv, AES_BLOCK_SIZE);
			ret = skcipher_walk_करोne(&walk, nbytes - k);
		पूर्ण
		अगर (k < n) अणु
			अगर (__paes_convert_key(ctx))
				वापस skcipher_walk_करोne(&walk, -EIO);
			spin_lock_bh(&ctx->pk_lock);
			स_नकल(param.key, ctx->pk.protkey, MAXPROTKEYSIZE);
			spin_unlock_bh(&ctx->pk_lock);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cbc_paes_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस cbc_paes_crypt(req, 0);
पूर्ण

अटल पूर्णांक cbc_paes_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस cbc_paes_crypt(req, CPACF_DECRYPT);
पूर्ण

अटल काष्ठा skcipher_alg cbc_paes_alg = अणु
	.base.cra_name		=	"cbc(paes)",
	.base.cra_driver_name	=	"cbc-paes-s390",
	.base.cra_priority	=	402,	/* ecb-paes-s390 + 1 */
	.base.cra_blocksize	=	AES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा s390_paes_ctx),
	.base.cra_module	=	THIS_MODULE,
	.base.cra_list		=	LIST_HEAD_INIT(cbc_paes_alg.base.cra_list),
	.init			=	cbc_paes_init,
	.निकास			=	cbc_paes_निकास,
	.min_keysize		=	PAES_MIN_KEYSIZE,
	.max_keysize		=	PAES_MAX_KEYSIZE,
	.ivsize			=	AES_BLOCK_SIZE,
	.setkey			=	cbc_paes_set_key,
	.encrypt		=	cbc_paes_encrypt,
	.decrypt		=	cbc_paes_decrypt,
पूर्ण;

अटल पूर्णांक xts_paes_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा s390_pxts_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->kb[0].key = शून्य;
	ctx->kb[1].key = शून्य;
	spin_lock_init(&ctx->pk_lock);

	वापस 0;
पूर्ण

अटल व्योम xts_paes_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा s390_pxts_ctx *ctx = crypto_skcipher_ctx(tfm);

	_मुक्त_kb_keybuf(&ctx->kb[0]);
	_मुक्त_kb_keybuf(&ctx->kb[1]);
पूर्ण

अटल अंतरभूत पूर्णांक __xts_paes_convert_key(काष्ठा s390_pxts_ctx *ctx)
अणु
	काष्ठा pkey_protkey pkey0, pkey1;

	अगर (__paes_keyblob2pkey(&ctx->kb[0], &pkey0) ||
	    __paes_keyblob2pkey(&ctx->kb[1], &pkey1))
		वापस -EINVAL;

	spin_lock_bh(&ctx->pk_lock);
	स_नकल(&ctx->pk[0], &pkey0, माप(pkey0));
	स_नकल(&ctx->pk[1], &pkey1, माप(pkey1));
	spin_unlock_bh(&ctx->pk_lock);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __xts_paes_set_key(काष्ठा s390_pxts_ctx *ctx)
अणु
	अचिन्हित दीर्घ fc;

	अगर (__xts_paes_convert_key(ctx))
		वापस -EINVAL;

	अगर (ctx->pk[0].type != ctx->pk[1].type)
		वापस -EINVAL;

	/* Pick the correct function code based on the रक्षित key type */
	fc = (ctx->pk[0].type == PKEY_KEYTYPE_AES_128) ? CPACF_KM_PXTS_128 :
		(ctx->pk[0].type == PKEY_KEYTYPE_AES_256) ?
		CPACF_KM_PXTS_256 : 0;

	/* Check अगर the function code is available */
	ctx->fc = (fc && cpacf_test_func(&km_functions, fc)) ? fc : 0;

	वापस ctx->fc ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक xts_paes_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			    अचिन्हित पूर्णांक xts_key_len)
अणु
	पूर्णांक rc;
	काष्ठा s390_pxts_ctx *ctx = crypto_skcipher_ctx(tfm);
	u8 ckey[2 * AES_MAX_KEY_SIZE];
	अचिन्हित पूर्णांक ckey_len, key_len;

	अगर (xts_key_len % 2)
		वापस -EINVAL;

	key_len = xts_key_len / 2;

	_मुक्त_kb_keybuf(&ctx->kb[0]);
	_मुक्त_kb_keybuf(&ctx->kb[1]);
	rc = _key_to_kb(&ctx->kb[0], in_key, key_len);
	अगर (rc)
		वापस rc;
	rc = _key_to_kb(&ctx->kb[1], in_key + key_len, key_len);
	अगर (rc)
		वापस rc;

	rc = __xts_paes_set_key(ctx);
	अगर (rc)
		वापस rc;

	/*
	 * xts_check_key verअगरies the key length is not odd and makes
	 * sure that the two keys are not the same. This can be करोne
	 * on the two रक्षित keys as well
	 */
	ckey_len = (ctx->pk[0].type == PKEY_KEYTYPE_AES_128) ?
		AES_KEYSIZE_128 : AES_KEYSIZE_256;
	स_नकल(ckey, ctx->pk[0].protkey, ckey_len);
	स_नकल(ckey + ckey_len, ctx->pk[1].protkey, ckey_len);
	वापस xts_verअगरy_key(tfm, ckey, 2*ckey_len);
पूर्ण

अटल पूर्णांक xts_paes_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ modअगरier)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s390_pxts_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक keylen, offset, nbytes, n, k;
	पूर्णांक ret;
	काष्ठा अणु
		u8 key[MAXPROTKEYSIZE];	/* key + verअगरication pattern */
		u8 tweak[16];
		u8 block[16];
		u8 bit[16];
		u8 xts[16];
	पूर्ण pcc_param;
	काष्ठा अणु
		u8 key[MAXPROTKEYSIZE];	/* key + verअगरication pattern */
		u8 init[16];
	पूर्ण xts_param;

	ret = skcipher_walk_virt(&walk, req, false);
	अगर (ret)
		वापस ret;

	keylen = (ctx->pk[0].type == PKEY_KEYTYPE_AES_128) ? 48 : 64;
	offset = (ctx->pk[0].type == PKEY_KEYTYPE_AES_128) ? 16 : 0;

	स_रखो(&pcc_param, 0, माप(pcc_param));
	स_नकल(pcc_param.tweak, walk.iv, माप(pcc_param.tweak));
	spin_lock_bh(&ctx->pk_lock);
	स_नकल(pcc_param.key + offset, ctx->pk[1].protkey, keylen);
	स_नकल(xts_param.key + offset, ctx->pk[0].protkey, keylen);
	spin_unlock_bh(&ctx->pk_lock);
	cpacf_pcc(ctx->fc, pcc_param.key + offset);
	स_नकल(xts_param.init, pcc_param.xts, 16);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		/* only use complete blocks */
		n = nbytes & ~(AES_BLOCK_SIZE - 1);
		k = cpacf_km(ctx->fc | modअगरier, xts_param.key + offset,
			     walk.dst.virt.addr, walk.src.virt.addr, n);
		अगर (k)
			ret = skcipher_walk_करोne(&walk, nbytes - k);
		अगर (k < n) अणु
			अगर (__xts_paes_convert_key(ctx))
				वापस skcipher_walk_करोne(&walk, -EIO);
			spin_lock_bh(&ctx->pk_lock);
			स_नकल(xts_param.key + offset,
			       ctx->pk[0].protkey, keylen);
			spin_unlock_bh(&ctx->pk_lock);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक xts_paes_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस xts_paes_crypt(req, 0);
पूर्ण

अटल पूर्णांक xts_paes_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस xts_paes_crypt(req, CPACF_DECRYPT);
पूर्ण

अटल काष्ठा skcipher_alg xts_paes_alg = अणु
	.base.cra_name		=	"xts(paes)",
	.base.cra_driver_name	=	"xts-paes-s390",
	.base.cra_priority	=	402,	/* ecb-paes-s390 + 1 */
	.base.cra_blocksize	=	AES_BLOCK_SIZE,
	.base.cra_ctxsize	=	माप(काष्ठा s390_pxts_ctx),
	.base.cra_module	=	THIS_MODULE,
	.base.cra_list		=	LIST_HEAD_INIT(xts_paes_alg.base.cra_list),
	.init			=	xts_paes_init,
	.निकास			=	xts_paes_निकास,
	.min_keysize		=	2 * PAES_MIN_KEYSIZE,
	.max_keysize		=	2 * PAES_MAX_KEYSIZE,
	.ivsize			=	AES_BLOCK_SIZE,
	.setkey			=	xts_paes_set_key,
	.encrypt		=	xts_paes_encrypt,
	.decrypt		=	xts_paes_decrypt,
पूर्ण;

अटल पूर्णांक ctr_paes_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->kb.key = शून्य;
	spin_lock_init(&ctx->pk_lock);

	वापस 0;
पूर्ण

अटल व्योम ctr_paes_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);

	_मुक्त_kb_keybuf(&ctx->kb);
पूर्ण

अटल अंतरभूत पूर्णांक __ctr_paes_set_key(काष्ठा s390_paes_ctx *ctx)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ fc;

	rc = __paes_convert_key(ctx);
	अगर (rc)
		वापस rc;

	/* Pick the correct function code based on the रक्षित key type */
	fc = (ctx->pk.type == PKEY_KEYTYPE_AES_128) ? CPACF_KMCTR_PAES_128 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_192) ? CPACF_KMCTR_PAES_192 :
		(ctx->pk.type == PKEY_KEYTYPE_AES_256) ?
		CPACF_KMCTR_PAES_256 : 0;

	/* Check अगर the function code is available */
	ctx->fc = (fc && cpacf_test_func(&kmctr_functions, fc)) ? fc : 0;

	वापस ctx->fc ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक ctr_paes_set_key(काष्ठा crypto_skcipher *tfm, स्थिर u8 *in_key,
			    अचिन्हित पूर्णांक key_len)
अणु
	पूर्णांक rc;
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);

	_मुक्त_kb_keybuf(&ctx->kb);
	rc = _key_to_kb(&ctx->kb, in_key, key_len);
	अगर (rc)
		वापस rc;

	वापस __ctr_paes_set_key(ctx);
पूर्ण

अटल अचिन्हित पूर्णांक __ctrblk_init(u8 *ctrptr, u8 *iv, अचिन्हित पूर्णांक nbytes)
अणु
	अचिन्हित पूर्णांक i, n;

	/* only use complete blocks, max. PAGE_SIZE */
	स_नकल(ctrptr, iv, AES_BLOCK_SIZE);
	n = (nbytes > PAGE_SIZE) ? PAGE_SIZE : nbytes & ~(AES_BLOCK_SIZE - 1);
	क्रम (i = (n / AES_BLOCK_SIZE) - 1; i > 0; i--) अणु
		स_नकल(ctrptr + AES_BLOCK_SIZE, ctrptr, AES_BLOCK_SIZE);
		crypto_inc(ctrptr + AES_BLOCK_SIZE, AES_BLOCK_SIZE);
		ctrptr += AES_BLOCK_SIZE;
	पूर्ण
	वापस n;
पूर्ण

अटल पूर्णांक ctr_paes_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s390_paes_ctx *ctx = crypto_skcipher_ctx(tfm);
	u8 buf[AES_BLOCK_SIZE], *ctrptr;
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes, n, k;
	पूर्णांक ret, locked;
	काष्ठा अणु
		u8 key[MAXPROTKEYSIZE];
	पूर्ण param;

	ret = skcipher_walk_virt(&walk, req, false);
	अगर (ret)
		वापस ret;

	spin_lock_bh(&ctx->pk_lock);
	स_नकल(param.key, ctx->pk.protkey, MAXPROTKEYSIZE);
	spin_unlock_bh(&ctx->pk_lock);

	locked = mutex_trylock(&ctrblk_lock);

	जबतक ((nbytes = walk.nbytes) >= AES_BLOCK_SIZE) अणु
		n = AES_BLOCK_SIZE;
		अगर (nbytes >= 2*AES_BLOCK_SIZE && locked)
			n = __ctrblk_init(ctrblk, walk.iv, nbytes);
		ctrptr = (n > AES_BLOCK_SIZE) ? ctrblk : walk.iv;
		k = cpacf_kmctr(ctx->fc, &param, walk.dst.virt.addr,
				walk.src.virt.addr, n, ctrptr);
		अगर (k) अणु
			अगर (ctrptr == ctrblk)
				स_नकल(walk.iv, ctrptr + k - AES_BLOCK_SIZE,
				       AES_BLOCK_SIZE);
			crypto_inc(walk.iv, AES_BLOCK_SIZE);
			ret = skcipher_walk_करोne(&walk, nbytes - k);
		पूर्ण
		अगर (k < n) अणु
			अगर (__paes_convert_key(ctx)) अणु
				अगर (locked)
					mutex_unlock(&ctrblk_lock);
				वापस skcipher_walk_करोne(&walk, -EIO);
			पूर्ण
			spin_lock_bh(&ctx->pk_lock);
			स_नकल(param.key, ctx->pk.protkey, MAXPROTKEYSIZE);
			spin_unlock_bh(&ctx->pk_lock);
		पूर्ण
	पूर्ण
	अगर (locked)
		mutex_unlock(&ctrblk_lock);
	/*
	 * final block may be < AES_BLOCK_SIZE, copy only nbytes
	 */
	अगर (nbytes) अणु
		जबतक (1) अणु
			अगर (cpacf_kmctr(ctx->fc, &param, buf,
					walk.src.virt.addr, AES_BLOCK_SIZE,
					walk.iv) == AES_BLOCK_SIZE)
				अवरोध;
			अगर (__paes_convert_key(ctx))
				वापस skcipher_walk_करोne(&walk, -EIO);
			spin_lock_bh(&ctx->pk_lock);
			स_नकल(param.key, ctx->pk.protkey, MAXPROTKEYSIZE);
			spin_unlock_bh(&ctx->pk_lock);
		पूर्ण
		स_नकल(walk.dst.virt.addr, buf, nbytes);
		crypto_inc(walk.iv, AES_BLOCK_SIZE);
		ret = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा skcipher_alg ctr_paes_alg = अणु
	.base.cra_name		=	"ctr(paes)",
	.base.cra_driver_name	=	"ctr-paes-s390",
	.base.cra_priority	=	402,	/* ecb-paes-s390 + 1 */
	.base.cra_blocksize	=	1,
	.base.cra_ctxsize	=	माप(काष्ठा s390_paes_ctx),
	.base.cra_module	=	THIS_MODULE,
	.base.cra_list		=	LIST_HEAD_INIT(ctr_paes_alg.base.cra_list),
	.init			=	ctr_paes_init,
	.निकास			=	ctr_paes_निकास,
	.min_keysize		=	PAES_MIN_KEYSIZE,
	.max_keysize		=	PAES_MAX_KEYSIZE,
	.ivsize			=	AES_BLOCK_SIZE,
	.setkey			=	ctr_paes_set_key,
	.encrypt		=	ctr_paes_crypt,
	.decrypt		=	ctr_paes_crypt,
	.chunksize		=	AES_BLOCK_SIZE,
पूर्ण;

अटल अंतरभूत व्योम __crypto_unरेजिस्टर_skcipher(काष्ठा skcipher_alg *alg)
अणु
	अगर (!list_empty(&alg->base.cra_list))
		crypto_unरेजिस्टर_skcipher(alg);
पूर्ण

अटल व्योम paes_s390_fini(व्योम)
अणु
	__crypto_unरेजिस्टर_skcipher(&ctr_paes_alg);
	__crypto_unरेजिस्टर_skcipher(&xts_paes_alg);
	__crypto_unरेजिस्टर_skcipher(&cbc_paes_alg);
	__crypto_unरेजिस्टर_skcipher(&ecb_paes_alg);
	अगर (ctrblk)
		मुक्त_page((अचिन्हित दीर्घ) ctrblk);
पूर्ण

अटल पूर्णांक __init paes_s390_init(व्योम)
अणु
	पूर्णांक ret;

	/* Query available functions क्रम KM, KMC and KMCTR */
	cpacf_query(CPACF_KM, &km_functions);
	cpacf_query(CPACF_KMC, &kmc_functions);
	cpacf_query(CPACF_KMCTR, &kmctr_functions);

	अगर (cpacf_test_func(&km_functions, CPACF_KM_PAES_128) ||
	    cpacf_test_func(&km_functions, CPACF_KM_PAES_192) ||
	    cpacf_test_func(&km_functions, CPACF_KM_PAES_256)) अणु
		ret = crypto_रेजिस्टर_skcipher(&ecb_paes_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	अगर (cpacf_test_func(&kmc_functions, CPACF_KMC_PAES_128) ||
	    cpacf_test_func(&kmc_functions, CPACF_KMC_PAES_192) ||
	    cpacf_test_func(&kmc_functions, CPACF_KMC_PAES_256)) अणु
		ret = crypto_रेजिस्टर_skcipher(&cbc_paes_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	अगर (cpacf_test_func(&km_functions, CPACF_KM_PXTS_128) ||
	    cpacf_test_func(&km_functions, CPACF_KM_PXTS_256)) अणु
		ret = crypto_रेजिस्टर_skcipher(&xts_paes_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	अगर (cpacf_test_func(&kmctr_functions, CPACF_KMCTR_PAES_128) ||
	    cpacf_test_func(&kmctr_functions, CPACF_KMCTR_PAES_192) ||
	    cpacf_test_func(&kmctr_functions, CPACF_KMCTR_PAES_256)) अणु
		ctrblk = (u8 *) __get_मुक्त_page(GFP_KERNEL);
		अगर (!ctrblk) अणु
			ret = -ENOMEM;
			जाओ out_err;
		पूर्ण
		ret = crypto_रेजिस्टर_skcipher(&ctr_paes_alg);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	वापस 0;
out_err:
	paes_s390_fini();
	वापस ret;
पूर्ण

module_init(paes_s390_init);
module_निकास(paes_s390_fini);

MODULE_ALIAS_CRYPTO("paes");

MODULE_DESCRIPTION("Rijndael (AES) Cipher Algorithm with protected keys");
MODULE_LICENSE("GPL");
