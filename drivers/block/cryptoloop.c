<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   Linux loop encryption enabling module

   Copyright (C)  2002 Herbert Valerio Riedel <hvr@gnu.org>
   Copyright (C)  2003 Fruhwirth Clemens <clemens@enकरोrphin.org>

 */

#समावेश <linux/module.h>

#समावेश <crypto/skcipher.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/uaccess.h>
#समावेश "loop.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("loop blockdevice transferfunction adaptor / CryptoAPI");
MODULE_AUTHOR("Herbert Valerio Riedel <hvr@gnu.org>");

#घोषणा LOOP_IV_SECTOR_BITS 9
#घोषणा LOOP_IV_SECTOR_SIZE (1 << LOOP_IV_SECTOR_BITS)

अटल पूर्णांक
cryptoloop_init(काष्ठा loop_device *lo, स्थिर काष्ठा loop_info64 *info)
अणु
	पूर्णांक err = -EINVAL;
	पूर्णांक cipher_len;
	पूर्णांक mode_len;
	अक्षर cms[LO_NAME_SIZE];			/* cipher-mode string */
	अक्षर *mode;
	अक्षर *cmsp = cms;			/* c-m string poपूर्णांकer */
	काष्ठा crypto_sync_skcipher *tfm;

	/* encryption अवरोधs क्रम non sector aligned offsets */

	अगर (info->lo_offset % LOOP_IV_SECTOR_SIZE)
		जाओ out;

	म_नकलन(cms, info->lo_crypt_name, LO_NAME_SIZE);
	cms[LO_NAME_SIZE - 1] = 0;

	cipher_len = म_खोज(cmsp, "-");

	mode = cmsp + cipher_len;
	mode_len = 0;
	अगर (*mode) अणु
		mode++;
		mode_len = म_खोज(mode, "-");
	पूर्ण

	अगर (!mode_len) अणु
		mode = "cbc";
		mode_len = 3;
	पूर्ण

	अगर (cipher_len + mode_len + 3 > LO_NAME_SIZE)
		वापस -EINVAL;

	स_हटाओ(cms, mode, mode_len);
	cmsp = cms + mode_len;
	*cmsp++ = '(';
	स_नकल(cmsp, info->lo_crypt_name, cipher_len);
	cmsp += cipher_len;
	*cmsp++ = ')';
	*cmsp = 0;

	tfm = crypto_alloc_sync_skcipher(cms, 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	err = crypto_sync_skcipher_setkey(tfm, info->lo_encrypt_key,
					  info->lo_encrypt_key_size);

	अगर (err != 0)
		जाओ out_मुक्त_tfm;

	lo->key_data = tfm;
	वापस 0;

 out_मुक्त_tfm:
	crypto_मुक्त_sync_skcipher(tfm);

 out:
	वापस err;
पूर्ण


प्रकार पूर्णांक (*encdec_cbc_t)(काष्ठा skcipher_request *req);

अटल पूर्णांक
cryptoloop_transfer(काष्ठा loop_device *lo, पूर्णांक cmd,
		    काष्ठा page *raw_page, अचिन्हित raw_off,
		    काष्ठा page *loop_page, अचिन्हित loop_off,
		    पूर्णांक size, sector_t IV)
अणु
	काष्ठा crypto_sync_skcipher *tfm = lo->key_data;
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, tfm);
	काष्ठा scatterlist sg_out;
	काष्ठा scatterlist sg_in;

	encdec_cbc_t encdecfunc;
	काष्ठा page *in_page, *out_page;
	अचिन्हित in_offs, out_offs;
	पूर्णांक err;

	skcipher_request_set_sync_tfm(req, tfm);
	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP,
				      शून्य, शून्य);

	sg_init_table(&sg_out, 1);
	sg_init_table(&sg_in, 1);

	अगर (cmd == READ) अणु
		in_page = raw_page;
		in_offs = raw_off;
		out_page = loop_page;
		out_offs = loop_off;
		encdecfunc = crypto_skcipher_decrypt;
	पूर्ण अन्यथा अणु
		in_page = loop_page;
		in_offs = loop_off;
		out_page = raw_page;
		out_offs = raw_off;
		encdecfunc = crypto_skcipher_encrypt;
	पूर्ण

	जबतक (size > 0) अणु
		स्थिर पूर्णांक sz = min(size, LOOP_IV_SECTOR_SIZE);
		u32 iv[4] = अणु 0, पूर्ण;
		iv[0] = cpu_to_le32(IV & 0xffffffff);

		sg_set_page(&sg_in, in_page, sz, in_offs);
		sg_set_page(&sg_out, out_page, sz, out_offs);

		skcipher_request_set_crypt(req, &sg_in, &sg_out, sz, iv);
		err = encdecfunc(req);
		अगर (err)
			जाओ out;

		IV++;
		size -= sz;
		in_offs += sz;
		out_offs += sz;
	पूर्ण

	err = 0;

out:
	skcipher_request_zero(req);
	वापस err;
पूर्ण

अटल पूर्णांक
cryptoloop_ioctl(काष्ठा loop_device *lo, पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
cryptoloop_release(काष्ठा loop_device *lo)
अणु
	काष्ठा crypto_sync_skcipher *tfm = lo->key_data;
	अगर (tfm != शून्य) अणु
		crypto_मुक्त_sync_skcipher(tfm);
		lo->key_data = शून्य;
		वापस 0;
	पूर्ण
	prपूर्णांकk(KERN_ERR "cryptoloop_release(): tfm == NULL?\n");
	वापस -EINVAL;
पूर्ण

अटल काष्ठा loop_func_table cryptoloop_funcs = अणु
	.number = LO_CRYPT_CRYPTOAPI,
	.init = cryptoloop_init,
	.ioctl = cryptoloop_ioctl,
	.transfer = cryptoloop_transfer,
	.release = cryptoloop_release,
	.owner = THIS_MODULE
पूर्ण;

अटल पूर्णांक __init
init_cryptoloop(व्योम)
अणु
	पूर्णांक rc = loop_रेजिस्टर_transfer(&cryptoloop_funcs);

	अगर (rc)
		prपूर्णांकk(KERN_ERR "cryptoloop: loop_register_transfer failed\n");
	वापस rc;
पूर्ण

अटल व्योम __निकास
cleanup_cryptoloop(व्योम)
अणु
	अगर (loop_unरेजिस्टर_transfer(LO_CRYPT_CRYPTOAPI))
		prपूर्णांकk(KERN_ERR
			"cryptoloop: loop_unregister_transfer failed\n");
पूर्ण

module_init(init_cryptoloop);
module_निकास(cleanup_cryptoloop);
