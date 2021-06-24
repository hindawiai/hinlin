<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /* Copyright (C) 2004-2006, Advanced Micro Devices, Inc.
  */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/crypto.h>
#समावेश <linux/spinlock.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>

#समावेश "geode-aes.h"

/* Static काष्ठाures */

अटल व्योम __iomem *_iobase;
अटल DEFINE_SPINLOCK(lock);

/* Write a 128 bit field (either a writable key or IV) */
अटल अंतरभूत व्योम
_ग_लिखोfield(u32 offset, स्थिर व्योम *value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		ioग_लिखो32(((स्थिर u32 *) value)[i], _iobase + offset + (i * 4));
पूर्ण

/* Read a 128 bit field (either a writable key or IV) */
अटल अंतरभूत व्योम
_पढ़ोfield(u32 offset, व्योम *value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		((u32 *) value)[i] = ioपढ़ो32(_iobase + offset + (i * 4));
पूर्ण

अटल पूर्णांक
करो_crypt(स्थिर व्योम *src, व्योम *dst, u32 len, u32 flags)
अणु
	u32 status;
	u32 counter = AES_OP_TIMEOUT;

	ioग_लिखो32(virt_to_phys((व्योम *)src), _iobase + AES_SOURCEA_REG);
	ioग_लिखो32(virt_to_phys(dst), _iobase + AES_DSTA_REG);
	ioग_लिखो32(len,  _iobase + AES_LENA_REG);

	/* Start the operation */
	ioग_लिखो32(AES_CTRL_START | flags, _iobase + AES_CTRLA_REG);

	करो अणु
		status = ioपढ़ो32(_iobase + AES_INTR_REG);
		cpu_relax();
	पूर्ण जबतक (!(status & AES_INTRA_PENDING) && --counter);

	/* Clear the event */
	ioग_लिखो32((status & 0xFF) | AES_INTRA_PENDING, _iobase + AES_INTR_REG);
	वापस counter ? 0 : 1;
पूर्ण

अटल व्योम
geode_aes_crypt(स्थिर काष्ठा geode_aes_tfm_ctx *tctx, स्थिर व्योम *src,
		व्योम *dst, u32 len, u8 *iv, पूर्णांक mode, पूर्णांक dir)
अणु
	u32 flags = 0;
	अचिन्हित दीर्घ अगरlags;
	पूर्णांक ret;

	/* If the source and destination is the same, then
	 * we need to turn on the coherent flags, otherwise
	 * we करोn't need to worry
	 */

	flags |= (AES_CTRL_DCA | AES_CTRL_SCA);

	अगर (dir == AES_सूची_ENCRYPT)
		flags |= AES_CTRL_ENCRYPT;

	/* Start the critical section */

	spin_lock_irqsave(&lock, अगरlags);

	अगर (mode == AES_MODE_CBC) अणु
		flags |= AES_CTRL_CBC;
		_ग_लिखोfield(AES_WRITEIV0_REG, iv);
	पूर्ण

	flags |= AES_CTRL_WRKEY;
	_ग_लिखोfield(AES_WRITEKEY0_REG, tctx->key);

	ret = करो_crypt(src, dst, len, flags);
	BUG_ON(ret);

	अगर (mode == AES_MODE_CBC)
		_पढ़ोfield(AES_WRITEIV0_REG, iv);

	spin_unlock_irqrestore(&lock, अगरlags);
पूर्ण

/* CRYPTO-API Functions */

अटल पूर्णांक geode_setkey_cip(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
		अचिन्हित पूर्णांक len)
अणु
	काष्ठा geode_aes_tfm_ctx *tctx = crypto_tfm_ctx(tfm);

	tctx->keylen = len;

	अगर (len == AES_KEYSIZE_128) अणु
		स_नकल(tctx->key, key, len);
		वापस 0;
	पूर्ण

	अगर (len != AES_KEYSIZE_192 && len != AES_KEYSIZE_256)
		/* not supported at all */
		वापस -EINVAL;

	/*
	 * The requested key size is not supported by HW, करो a fallback
	 */
	tctx->fallback.cip->base.crt_flags &= ~CRYPTO_TFM_REQ_MASK;
	tctx->fallback.cip->base.crt_flags |=
		(tfm->crt_flags & CRYPTO_TFM_REQ_MASK);

	वापस crypto_cipher_setkey(tctx->fallback.cip, key, len);
पूर्ण

अटल पूर्णांक geode_setkey_skcipher(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक len)
अणु
	काष्ठा geode_aes_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);

	tctx->keylen = len;

	अगर (len == AES_KEYSIZE_128) अणु
		स_नकल(tctx->key, key, len);
		वापस 0;
	पूर्ण

	अगर (len != AES_KEYSIZE_192 && len != AES_KEYSIZE_256)
		/* not supported at all */
		वापस -EINVAL;

	/*
	 * The requested key size is not supported by HW, करो a fallback
	 */
	crypto_skcipher_clear_flags(tctx->fallback.skcipher,
				    CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(tctx->fallback.skcipher,
				  crypto_skcipher_get_flags(tfm) &
				  CRYPTO_TFM_REQ_MASK);
	वापस crypto_skcipher_setkey(tctx->fallback.skcipher, key, len);
पूर्ण

अटल व्योम
geode_encrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	स्थिर काष्ठा geode_aes_tfm_ctx *tctx = crypto_tfm_ctx(tfm);

	अगर (unlikely(tctx->keylen != AES_KEYSIZE_128)) अणु
		crypto_cipher_encrypt_one(tctx->fallback.cip, out, in);
		वापस;
	पूर्ण

	geode_aes_crypt(tctx, in, out, AES_BLOCK_SIZE, शून्य,
			AES_MODE_ECB, AES_सूची_ENCRYPT);
पूर्ण


अटल व्योम
geode_decrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	स्थिर काष्ठा geode_aes_tfm_ctx *tctx = crypto_tfm_ctx(tfm);

	अगर (unlikely(tctx->keylen != AES_KEYSIZE_128)) अणु
		crypto_cipher_decrypt_one(tctx->fallback.cip, out, in);
		वापस;
	पूर्ण

	geode_aes_crypt(tctx, in, out, AES_BLOCK_SIZE, शून्य,
			AES_MODE_ECB, AES_सूची_DECRYPT);
पूर्ण

अटल पूर्णांक fallback_init_cip(काष्ठा crypto_tfm *tfm)
अणु
	स्थिर अक्षर *name = crypto_tfm_alg_name(tfm);
	काष्ठा geode_aes_tfm_ctx *tctx = crypto_tfm_ctx(tfm);

	tctx->fallback.cip = crypto_alloc_cipher(name, 0,
						 CRYPTO_ALG_NEED_FALLBACK);

	अगर (IS_ERR(tctx->fallback.cip)) अणु
		prपूर्णांकk(KERN_ERR "Error allocating fallback algo %s\n", name);
		वापस PTR_ERR(tctx->fallback.cip);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fallback_निकास_cip(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा geode_aes_tfm_ctx *tctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_cipher(tctx->fallback.cip);
पूर्ण

अटल काष्ठा crypto_alg geode_alg = अणु
	.cra_name			=	"aes",
	.cra_driver_name	=	"geode-aes",
	.cra_priority		=	300,
	.cra_alignmask		=	15,
	.cra_flags			=	CRYPTO_ALG_TYPE_CIPHER |
							CRYPTO_ALG_NEED_FALLBACK,
	.cra_init			=	fallback_init_cip,
	.cra_निकास			=	fallback_निकास_cip,
	.cra_blocksize		=	AES_BLOCK_SIZE,
	.cra_ctxsize		=	माप(काष्ठा geode_aes_tfm_ctx),
	.cra_module			=	THIS_MODULE,
	.cra_u				=	अणु
		.cipher	=	अणु
			.cia_min_keysize	=	AES_MIN_KEY_SIZE,
			.cia_max_keysize	=	AES_MAX_KEY_SIZE,
			.cia_setkey			=	geode_setkey_cip,
			.cia_encrypt		=	geode_encrypt,
			.cia_decrypt		=	geode_decrypt
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक geode_init_skcipher(काष्ठा crypto_skcipher *tfm)
अणु
	स्थिर अक्षर *name = crypto_tfm_alg_name(&tfm->base);
	काष्ठा geode_aes_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);

	tctx->fallback.skcipher =
		crypto_alloc_skcipher(name, 0, CRYPTO_ALG_NEED_FALLBACK |
				      CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tctx->fallback.skcipher)) अणु
		prपूर्णांकk(KERN_ERR "Error allocating fallback algo %s\n", name);
		वापस PTR_ERR(tctx->fallback.skcipher);
	पूर्ण

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा skcipher_request) +
				    crypto_skcipher_reqsize(tctx->fallback.skcipher));
	वापस 0;
पूर्ण

अटल व्योम geode_निकास_skcipher(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा geode_aes_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(tctx->fallback.skcipher);
पूर्ण

अटल पूर्णांक geode_skcipher_crypt(काष्ठा skcipher_request *req, पूर्णांक mode, पूर्णांक dir)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा geode_aes_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	अगर (unlikely(tctx->keylen != AES_KEYSIZE_128)) अणु
		काष्ठा skcipher_request *subreq = skcipher_request_ctx(req);

		*subreq = *req;
		skcipher_request_set_tfm(subreq, tctx->fallback.skcipher);
		अगर (dir == AES_सूची_DECRYPT)
			वापस crypto_skcipher_decrypt(subreq);
		अन्यथा
			वापस crypto_skcipher_encrypt(subreq);
	पूर्ण

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		geode_aes_crypt(tctx, walk.src.virt.addr, walk.dst.virt.addr,
				round_करोwn(nbytes, AES_BLOCK_SIZE),
				walk.iv, mode, dir);
		err = skcipher_walk_करोne(&walk, nbytes % AES_BLOCK_SIZE);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक geode_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस geode_skcipher_crypt(req, AES_MODE_CBC, AES_सूची_ENCRYPT);
पूर्ण

अटल पूर्णांक geode_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस geode_skcipher_crypt(req, AES_MODE_CBC, AES_सूची_DECRYPT);
पूर्ण

अटल पूर्णांक geode_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस geode_skcipher_crypt(req, AES_MODE_ECB, AES_सूची_ENCRYPT);
पूर्ण

अटल पूर्णांक geode_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस geode_skcipher_crypt(req, AES_MODE_ECB, AES_सूची_DECRYPT);
पूर्ण

अटल काष्ठा skcipher_alg geode_skcipher_algs[] = अणु
	अणु
		.base.cra_name		= "cbc(aes)",
		.base.cra_driver_name	= "cbc-aes-geode",
		.base.cra_priority	= 400,
		.base.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
					  CRYPTO_ALG_NEED_FALLBACK,
		.base.cra_blocksize	= AES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा geode_aes_tfm_ctx),
		.base.cra_alignmask	= 15,
		.base.cra_module	= THIS_MODULE,
		.init			= geode_init_skcipher,
		.निकास			= geode_निकास_skcipher,
		.setkey			= geode_setkey_skcipher,
		.encrypt		= geode_cbc_encrypt,
		.decrypt		= geode_cbc_decrypt,
		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BLOCK_SIZE,
	पूर्ण, अणु
		.base.cra_name		= "ecb(aes)",
		.base.cra_driver_name	= "ecb-aes-geode",
		.base.cra_priority	= 400,
		.base.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
					  CRYPTO_ALG_NEED_FALLBACK,
		.base.cra_blocksize	= AES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा geode_aes_tfm_ctx),
		.base.cra_alignmask	= 15,
		.base.cra_module	= THIS_MODULE,
		.init			= geode_init_skcipher,
		.निकास			= geode_निकास_skcipher,
		.setkey			= geode_setkey_skcipher,
		.encrypt		= geode_ecb_encrypt,
		.decrypt		= geode_ecb_decrypt,
		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
	पूर्ण,
पूर्ण;

अटल व्योम geode_aes_हटाओ(काष्ठा pci_dev *dev)
अणु
	crypto_unरेजिस्टर_alg(&geode_alg);
	crypto_unरेजिस्टर_skciphers(geode_skcipher_algs,
				    ARRAY_SIZE(geode_skcipher_algs));

	pci_iounmap(dev, _iobase);
	_iobase = शून्य;

	pci_release_regions(dev);
	pci_disable_device(dev);
पूर्ण


अटल पूर्णांक geode_aes_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक ret;

	ret = pci_enable_device(dev);
	अगर (ret)
		वापस ret;

	ret = pci_request_regions(dev, "geode-aes");
	अगर (ret)
		जाओ eenable;

	_iobase = pci_iomap(dev, 0, 0);

	अगर (_iobase == शून्य) अणु
		ret = -ENOMEM;
		जाओ erequest;
	पूर्ण

	/* Clear any pending activity */
	ioग_लिखो32(AES_INTR_PENDING | AES_INTR_MASK, _iobase + AES_INTR_REG);

	ret = crypto_रेजिस्टर_alg(&geode_alg);
	अगर (ret)
		जाओ eiomap;

	ret = crypto_रेजिस्टर_skciphers(geode_skcipher_algs,
					ARRAY_SIZE(geode_skcipher_algs));
	अगर (ret)
		जाओ ealg;

	dev_notice(&dev->dev, "GEODE AES engine enabled.\n");
	वापस 0;

 ealg:
	crypto_unरेजिस्टर_alg(&geode_alg);

 eiomap:
	pci_iounmap(dev, _iobase);

 erequest:
	pci_release_regions(dev);

 eenable:
	pci_disable_device(dev);

	dev_err(&dev->dev, "GEODE AES initialization failed.\n");
	वापस ret;
पूर्ण

अटल काष्ठा pci_device_id geode_aes_tbl[] = अणु
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_LX_AES), पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, geode_aes_tbl);

अटल काष्ठा pci_driver geode_aes_driver = अणु
	.name = "Geode LX AES",
	.id_table = geode_aes_tbl,
	.probe = geode_aes_probe,
	.हटाओ = geode_aes_हटाओ,
पूर्ण;

module_pci_driver(geode_aes_driver);

MODULE_AUTHOR("Advanced Micro Devices, Inc.");
MODULE_DESCRIPTION("Geode LX Hardware AES driver");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
