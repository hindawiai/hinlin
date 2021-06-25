<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Quick & dirty crypto testing module.
 *
 * This will only exist until we have a better testing mechanism
 * (e.g. a अक्षर device).
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2002 Jean-Francois Dive <jef@linuxbe.org>
 * Copyright (c) 2007 Nokia Siemens Networks
 *
 * Updated RFC4106 AES-GCM testing.
 *    Authors: Aidan O'Mahony (aidan.o.mahony@पूर्णांकel.com)
 *             Adrian Hoban <adrian.hoban@पूर्णांकel.com>
 *             Gabriele Paoloni <gabriele.paoloni@पूर्णांकel.com>
 *             Tadeusz Struk (tadeusz.struk@पूर्णांकel.com)
 *             Copyright (c) 2010, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <crypto/aead.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/fips.h>
#समावेश <linux/init.h>
#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/माला.स>
#समावेश <linux/moduleparam.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयx.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "tcrypt.h"

/*
 * Need slab memory क्रम testing (size in number of pages).
 */
#घोषणा TVMEMSIZE	4

/*
* Used by test_cipher_speed()
*/
#घोषणा ENCRYPT 1
#घोषणा DECRYPT 0

#घोषणा MAX_DIGEST_SIZE		64

/*
 * वापस a string with the driver name
 */
#घोषणा get_driver_name(tfm_type, tfm) crypto_tfm_alg_driver_name(tfm_type ## _tfm(tfm))

/*
 * Used by test_cipher_speed()
 */
अटल अचिन्हित पूर्णांक sec;

अटल अक्षर *alg = शून्य;
अटल u32 type;
अटल u32 mask;
अटल पूर्णांक mode;
अटल u32 num_mb = 8;
अटल अचिन्हित पूर्णांक klen;
अटल अक्षर *tvmem[TVMEMSIZE];

अटल स्थिर अक्षर *check[] = अणु
	"des", "md5", "des3_ede", "rot13", "sha1", "sha224", "sha256", "sm3",
	"blowfish", "twofish", "serpent", "sha384", "sha512", "md4", "aes",
	"cast6", "arc4", "michael_mic", "deflate", "crc32c", "tea", "xtea",
	"khazad", "wp512", "wp384", "wp256", "xeta",  "fcrypt",
	"camellia", "seed", "rmd160",
	"lzo", "lzo-rle", "cts", "sha3-224", "sha3-256", "sha3-384",
	"sha3-512", "streebog256", "streebog512",
	शून्य
पूर्ण;

अटल स्थिर पूर्णांक block_sizes[] = अणु 16, 64, 256, 1024, 1420, 4096, 0 पूर्ण;
अटल स्थिर पूर्णांक aead_sizes[] = अणु 16, 64, 256, 512, 1024, 1420, 4096, 8192, 0 पूर्ण;

#घोषणा Xबफ_मानE 8
#घोषणा MAX_IVLEN 32

अटल पूर्णांक tesपंचांगgr_alloc_buf(अक्षर *buf[Xबफ_मानE])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < Xबफ_मानE; i++) अणु
		buf[i] = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
		अगर (!buf[i])
			जाओ err_मुक्त_buf;
	पूर्ण

	वापस 0;

err_मुक्त_buf:
	जबतक (i-- > 0)
		मुक्त_page((अचिन्हित दीर्घ)buf[i]);

	वापस -ENOMEM;
पूर्ण

अटल व्योम tesपंचांगgr_मुक्त_buf(अक्षर *buf[Xबफ_मानE])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < Xबफ_मानE; i++)
		मुक्त_page((अचिन्हित दीर्घ)buf[i]);
पूर्ण

अटल व्योम sg_init_aead(काष्ठा scatterlist *sg, अक्षर *xbuf[Xबफ_मानE],
			 अचिन्हित पूर्णांक buflen, स्थिर व्योम *assoc,
			 अचिन्हित पूर्णांक aad_size)
अणु
	पूर्णांक np = (buflen + PAGE_SIZE - 1)/PAGE_SIZE;
	पूर्णांक k, rem;

	अगर (np > Xबफ_मानE) अणु
		rem = PAGE_SIZE;
		np = Xबफ_मानE;
	पूर्ण अन्यथा अणु
		rem = buflen % PAGE_SIZE;
	पूर्ण

	sg_init_table(sg, np + 1);

	sg_set_buf(&sg[0], assoc, aad_size);

	अगर (rem)
		np--;
	क्रम (k = 0; k < np; k++)
		sg_set_buf(&sg[k + 1], xbuf[k], PAGE_SIZE);

	अगर (rem)
		sg_set_buf(&sg[k + 1], xbuf[k], rem);
पूर्ण

अटल अंतरभूत पूर्णांक करो_one_aead_op(काष्ठा aead_request *req, पूर्णांक ret)
अणु
	काष्ठा crypto_रुको *रुको = req->base.data;

	वापस crypto_रुको_req(ret, रुको);
पूर्ण

काष्ठा test_mb_aead_data अणु
	काष्ठा scatterlist sg[Xबफ_मानE];
	काष्ठा scatterlist sgout[Xबफ_मानE];
	काष्ठा aead_request *req;
	काष्ठा crypto_रुको रुको;
	अक्षर *xbuf[Xबफ_मानE];
	अक्षर *xoutbuf[Xबफ_मानE];
	अक्षर *axbuf[Xबफ_मानE];
पूर्ण;

अटल पूर्णांक करो_mult_aead_op(काष्ठा test_mb_aead_data *data, पूर्णांक enc,
				u32 num_mb, पूर्णांक *rc)
अणु
	पूर्णांक i, err = 0;

	/* Fire up a bunch of concurrent requests */
	क्रम (i = 0; i < num_mb; i++) अणु
		अगर (enc == ENCRYPT)
			rc[i] = crypto_aead_encrypt(data[i].req);
		अन्यथा
			rc[i] = crypto_aead_decrypt(data[i].req);
	पूर्ण

	/* Wait क्रम all requests to finish */
	क्रम (i = 0; i < num_mb; i++) अणु
		rc[i] = crypto_रुको_req(rc[i], &data[i].रुको);

		अगर (rc[i]) अणु
			pr_info("concurrent request %d error %d\n", i, rc[i]);
			err = rc[i];
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक test_mb_aead_jअगरfies(काष्ठा test_mb_aead_data *data, पूर्णांक enc,
				पूर्णांक blen, पूर्णांक secs, u32 num_mb)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक bcount;
	पूर्णांक ret = 0;
	पूर्णांक *rc;

	rc = kसुस्मृति(num_mb, माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस -ENOMEM;

	क्रम (start = jअगरfies, end = start + secs * HZ, bcount = 0;
	     समय_beक्रमe(jअगरfies, end); bcount++) अणु
		ret = करो_mult_aead_op(data, enc, num_mb, rc);
		अगर (ret)
			जाओ out;
	पूर्ण

	pr_cont("%d operations in %d seconds (%llu bytes)\n",
		bcount * num_mb, secs, (u64)bcount * blen * num_mb);

out:
	kमुक्त(rc);
	वापस ret;
पूर्ण

अटल पूर्णांक test_mb_aead_cycles(काष्ठा test_mb_aead_data *data, पूर्णांक enc,
			       पूर्णांक blen, u32 num_mb)
अणु
	अचिन्हित दीर्घ cycles = 0;
	पूर्णांक ret = 0;
	पूर्णांक i;
	पूर्णांक *rc;

	rc = kसुस्मृति(num_mb, माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस -ENOMEM;

	/* Warm-up run. */
	क्रम (i = 0; i < 4; i++) अणु
		ret = करो_mult_aead_op(data, enc, num_mb, rc);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* The real thing. */
	क्रम (i = 0; i < 8; i++) अणु
		cycles_t start, end;

		start = get_cycles();
		ret = करो_mult_aead_op(data, enc, num_mb, rc);
		end = get_cycles();

		अगर (ret)
			जाओ out;

		cycles += end - start;
	पूर्ण

	pr_cont("1 operation in %lu cycles (%d bytes)\n",
		(cycles + 4) / (8 * num_mb), blen);

out:
	kमुक्त(rc);
	वापस ret;
पूर्ण

अटल व्योम test_mb_aead_speed(स्थिर अक्षर *algo, पूर्णांक enc, पूर्णांक secs,
			       काष्ठा aead_speed_ढाँचा *ढाँचा,
			       अचिन्हित पूर्णांक tcount, u8 authsize,
			       अचिन्हित पूर्णांक aad_size, u8 *keysize, u32 num_mb)
अणु
	काष्ठा test_mb_aead_data *data;
	काष्ठा crypto_aead *tfm;
	अचिन्हित पूर्णांक i, j, iv_len;
	स्थिर पूर्णांक *b_size;
	स्थिर अक्षर *key;
	स्थिर अक्षर *e;
	व्योम *assoc;
	अक्षर *iv;
	पूर्णांक ret;


	अगर (aad_size >= PAGE_SIZE) अणु
		pr_err("associate data length (%u) too big\n", aad_size);
		वापस;
	पूर्ण

	iv = kzalloc(MAX_IVLEN, GFP_KERNEL);
	अगर (!iv)
		वापस;

	अगर (enc == ENCRYPT)
		e = "encryption";
	अन्यथा
		e = "decryption";

	data = kसुस्मृति(num_mb, माप(*data), GFP_KERNEL);
	अगर (!data)
		जाओ out_मुक्त_iv;

	tfm = crypto_alloc_aead(algo, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		pr_err("failed to load transform for %s: %ld\n",
			algo, PTR_ERR(tfm));
		जाओ out_मुक्त_data;
	पूर्ण

	ret = crypto_aead_setauthsize(tfm, authsize);

	क्रम (i = 0; i < num_mb; ++i)
		अगर (tesपंचांगgr_alloc_buf(data[i].xbuf)) अणु
			जबतक (i--)
				tesपंचांगgr_मुक्त_buf(data[i].xbuf);
			जाओ out_मुक्त_tfm;
		पूर्ण

	क्रम (i = 0; i < num_mb; ++i)
		अगर (tesपंचांगgr_alloc_buf(data[i].axbuf)) अणु
			जबतक (i--)
				tesपंचांगgr_मुक्त_buf(data[i].axbuf);
			जाओ out_मुक्त_xbuf;
		पूर्ण

	क्रम (i = 0; i < num_mb; ++i)
		अगर (tesपंचांगgr_alloc_buf(data[i].xoutbuf)) अणु
			जबतक (i--)
				tesपंचांगgr_मुक्त_buf(data[i].xoutbuf);
			जाओ out_मुक्त_axbuf;
		पूर्ण

	क्रम (i = 0; i < num_mb; ++i) अणु
		data[i].req = aead_request_alloc(tfm, GFP_KERNEL);
		अगर (!data[i].req) अणु
			pr_err("alg: skcipher: Failed to allocate request for %s\n",
			       algo);
			जबतक (i--)
				aead_request_मुक्त(data[i].req);
			जाओ out_मुक्त_xoutbuf;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_mb; ++i) अणु
		crypto_init_रुको(&data[i].रुको);
		aead_request_set_callback(data[i].req,
					  CRYPTO_TFM_REQ_MAY_BACKLOG,
					  crypto_req_करोne, &data[i].रुको);
	पूर्ण

	pr_info("\ntesting speed of multibuffer %s (%s) %s\n", algo,
		get_driver_name(crypto_aead, tfm), e);

	i = 0;
	करो अणु
		b_size = aead_sizes;
		करो अणु
			पूर्णांक bs = round_up(*b_size, crypto_aead_blocksize(tfm));

			अगर (bs + authsize > Xबफ_मानE * PAGE_SIZE) अणु
				pr_err("template (%u) too big for buffer (%lu)\n",
				       authsize + bs,
				       Xबफ_मानE * PAGE_SIZE);
				जाओ out;
			पूर्ण

			pr_info("test %u (%d bit key, %d byte blocks): ", i,
				*keysize * 8, bs);

			/* Set up tfm global state, i.e. the key */

			स_रखो(tvmem[0], 0xff, PAGE_SIZE);
			key = tvmem[0];
			क्रम (j = 0; j < tcount; j++) अणु
				अगर (ढाँचा[j].klen == *keysize) अणु
					key = ढाँचा[j].key;
					अवरोध;
				पूर्ण
			पूर्ण

			crypto_aead_clear_flags(tfm, ~0);

			ret = crypto_aead_setkey(tfm, key, *keysize);
			अगर (ret) अणु
				pr_err("setkey() failed flags=%x\n",
				       crypto_aead_get_flags(tfm));
				जाओ out;
			पूर्ण

			iv_len = crypto_aead_ivsize(tfm);
			अगर (iv_len)
				स_रखो(iv, 0xff, iv_len);

			/* Now setup per request stuff, i.e. buffers */

			क्रम (j = 0; j < num_mb; ++j) अणु
				काष्ठा test_mb_aead_data *cur = &data[j];

				assoc = cur->axbuf[0];
				स_रखो(assoc, 0xff, aad_size);

				sg_init_aead(cur->sg, cur->xbuf,
					     bs + (enc ? 0 : authsize),
					     assoc, aad_size);

				sg_init_aead(cur->sgout, cur->xoutbuf,
					     bs + (enc ? authsize : 0),
					     assoc, aad_size);

				aead_request_set_ad(cur->req, aad_size);

				अगर (!enc) अणु

					aead_request_set_crypt(cur->req,
							       cur->sgout,
							       cur->sg,
							       bs, iv);
					ret = crypto_aead_encrypt(cur->req);
					ret = करो_one_aead_op(cur->req, ret);

					अगर (ret) अणु
						pr_err("calculating auth failed (%d)\n",
						       ret);
						अवरोध;
					पूर्ण
				पूर्ण

				aead_request_set_crypt(cur->req, cur->sg,
						       cur->sgout, bs +
						       (enc ? 0 : authsize),
						       iv);

			पूर्ण

			अगर (secs) अणु
				ret = test_mb_aead_jअगरfies(data, enc, bs,
							   secs, num_mb);
				cond_resched();
			पूर्ण अन्यथा अणु
				ret = test_mb_aead_cycles(data, enc, bs,
							  num_mb);
			पूर्ण

			अगर (ret) अणु
				pr_err("%s() failed return code=%d\n", e, ret);
				अवरोध;
			पूर्ण
			b_size++;
			i++;
		पूर्ण जबतक (*b_size);
		keysize++;
	पूर्ण जबतक (*keysize);

out:
	क्रम (i = 0; i < num_mb; ++i)
		aead_request_मुक्त(data[i].req);
out_मुक्त_xoutbuf:
	क्रम (i = 0; i < num_mb; ++i)
		tesपंचांगgr_मुक्त_buf(data[i].xoutbuf);
out_मुक्त_axbuf:
	क्रम (i = 0; i < num_mb; ++i)
		tesपंचांगgr_मुक्त_buf(data[i].axbuf);
out_मुक्त_xbuf:
	क्रम (i = 0; i < num_mb; ++i)
		tesपंचांगgr_मुक्त_buf(data[i].xbuf);
out_मुक्त_tfm:
	crypto_मुक्त_aead(tfm);
out_मुक्त_data:
	kमुक्त(data);
out_मुक्त_iv:
	kमुक्त(iv);
पूर्ण

अटल पूर्णांक test_aead_jअगरfies(काष्ठा aead_request *req, पूर्णांक enc,
				पूर्णांक blen, पूर्णांक secs)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक bcount;
	पूर्णांक ret;

	क्रम (start = jअगरfies, end = start + secs * HZ, bcount = 0;
	     समय_beक्रमe(jअगरfies, end); bcount++) अणु
		अगर (enc)
			ret = करो_one_aead_op(req, crypto_aead_encrypt(req));
		अन्यथा
			ret = करो_one_aead_op(req, crypto_aead_decrypt(req));

		अगर (ret)
			वापस ret;
	पूर्ण

	pr_cont("%d operations in %d seconds (%llu bytes)\n",
	        bcount, secs, (u64)bcount * blen);
	वापस 0;
पूर्ण

अटल पूर्णांक test_aead_cycles(काष्ठा aead_request *req, पूर्णांक enc, पूर्णांक blen)
अणु
	अचिन्हित दीर्घ cycles = 0;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* Warm-up run. */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (enc)
			ret = करो_one_aead_op(req, crypto_aead_encrypt(req));
		अन्यथा
			ret = करो_one_aead_op(req, crypto_aead_decrypt(req));

		अगर (ret)
			जाओ out;
	पूर्ण

	/* The real thing. */
	क्रम (i = 0; i < 8; i++) अणु
		cycles_t start, end;

		start = get_cycles();
		अगर (enc)
			ret = करो_one_aead_op(req, crypto_aead_encrypt(req));
		अन्यथा
			ret = करो_one_aead_op(req, crypto_aead_decrypt(req));
		end = get_cycles();

		अगर (ret)
			जाओ out;

		cycles += end - start;
	पूर्ण

out:
	अगर (ret == 0)
		prपूर्णांकk("1 operation in %lu cycles (%d bytes)\n",
		       (cycles + 4) / 8, blen);

	वापस ret;
पूर्ण

अटल व्योम test_aead_speed(स्थिर अक्षर *algo, पूर्णांक enc, अचिन्हित पूर्णांक secs,
			    काष्ठा aead_speed_ढाँचा *ढाँचा,
			    अचिन्हित पूर्णांक tcount, u8 authsize,
			    अचिन्हित पूर्णांक aad_size, u8 *keysize)
अणु
	अचिन्हित पूर्णांक i, j;
	काष्ठा crypto_aead *tfm;
	पूर्णांक ret = -ENOMEM;
	स्थिर अक्षर *key;
	काष्ठा aead_request *req;
	काष्ठा scatterlist *sg;
	काष्ठा scatterlist *sgout;
	स्थिर अक्षर *e;
	व्योम *assoc;
	अक्षर *iv;
	अक्षर *xbuf[Xबफ_मानE];
	अक्षर *xoutbuf[Xबफ_मानE];
	अक्षर *axbuf[Xबफ_मानE];
	स्थिर पूर्णांक *b_size;
	अचिन्हित पूर्णांक iv_len;
	काष्ठा crypto_रुको रुको;

	iv = kzalloc(MAX_IVLEN, GFP_KERNEL);
	अगर (!iv)
		वापस;

	अगर (aad_size >= PAGE_SIZE) अणु
		pr_err("associate data length (%u) too big\n", aad_size);
		जाओ out_noxbuf;
	पूर्ण

	अगर (enc == ENCRYPT)
		e = "encryption";
	अन्यथा
		e = "decryption";

	अगर (tesपंचांगgr_alloc_buf(xbuf))
		जाओ out_noxbuf;
	अगर (tesपंचांगgr_alloc_buf(axbuf))
		जाओ out_noaxbuf;
	अगर (tesपंचांगgr_alloc_buf(xoutbuf))
		जाओ out_nooutbuf;

	sg = kदो_स्मृति(माप(*sg) * 9 * 2, GFP_KERNEL);
	अगर (!sg)
		जाओ out_nosg;
	sgout = &sg[9];

	tfm = crypto_alloc_aead(algo, 0, 0);

	अगर (IS_ERR(tfm)) अणु
		pr_err("alg: aead: Failed to load transform for %s: %ld\n", algo,
		       PTR_ERR(tfm));
		जाओ out_notfm;
	पूर्ण

	crypto_init_रुको(&रुको);
	prपूर्णांकk(KERN_INFO "\ntesting speed of %s (%s) %s\n", algo,
			get_driver_name(crypto_aead, tfm), e);

	req = aead_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		pr_err("alg: aead: Failed to allocate request for %s\n",
		       algo);
		जाओ out_noreq;
	पूर्ण

	aead_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				  crypto_req_करोne, &रुको);

	i = 0;
	करो अणु
		b_size = aead_sizes;
		करो अणु
			u32 bs = round_up(*b_size, crypto_aead_blocksize(tfm));

			assoc = axbuf[0];
			स_रखो(assoc, 0xff, aad_size);

			अगर ((*keysize + bs) > TVMEMSIZE * PAGE_SIZE) अणु
				pr_err("template (%u) too big for tvmem (%lu)\n",
				       *keysize + bs,
					TVMEMSIZE * PAGE_SIZE);
				जाओ out;
			पूर्ण

			key = tvmem[0];
			क्रम (j = 0; j < tcount; j++) अणु
				अगर (ढाँचा[j].klen == *keysize) अणु
					key = ढाँचा[j].key;
					अवरोध;
				पूर्ण
			पूर्ण
			ret = crypto_aead_setkey(tfm, key, *keysize);
			ret = crypto_aead_setauthsize(tfm, authsize);

			iv_len = crypto_aead_ivsize(tfm);
			अगर (iv_len)
				स_रखो(iv, 0xff, iv_len);

			crypto_aead_clear_flags(tfm, ~0);
			prपूर्णांकk(KERN_INFO "test %u (%d bit key, %d byte blocks): ",
					i, *keysize * 8, bs);


			स_रखो(tvmem[0], 0xff, PAGE_SIZE);

			अगर (ret) अणु
				pr_err("setkey() failed flags=%x\n",
						crypto_aead_get_flags(tfm));
				जाओ out;
			पूर्ण

			sg_init_aead(sg, xbuf, bs + (enc ? 0 : authsize),
				     assoc, aad_size);

			sg_init_aead(sgout, xoutbuf,
				     bs + (enc ? authsize : 0), assoc,
				     aad_size);

			aead_request_set_ad(req, aad_size);

			अगर (!enc) अणु

				/*
				 * For decryption we need a proper auth so
				 * we करो the encryption path once with buffers
				 * reversed (input <-> output) to calculate it
				 */
				aead_request_set_crypt(req, sgout, sg,
						       bs, iv);
				ret = करो_one_aead_op(req,
						     crypto_aead_encrypt(req));

				अगर (ret) अणु
					pr_err("calculating auth failed (%d)\n",
					       ret);
					अवरोध;
				पूर्ण
			पूर्ण

			aead_request_set_crypt(req, sg, sgout,
					       bs + (enc ? 0 : authsize),
					       iv);

			अगर (secs) अणु
				ret = test_aead_jअगरfies(req, enc, bs,
							secs);
				cond_resched();
			पूर्ण अन्यथा अणु
				ret = test_aead_cycles(req, enc, bs);
			पूर्ण

			अगर (ret) अणु
				pr_err("%s() failed return code=%d\n", e, ret);
				अवरोध;
			पूर्ण
			b_size++;
			i++;
		पूर्ण जबतक (*b_size);
		keysize++;
	पूर्ण जबतक (*keysize);

out:
	aead_request_मुक्त(req);
out_noreq:
	crypto_मुक्त_aead(tfm);
out_notfm:
	kमुक्त(sg);
out_nosg:
	tesपंचांगgr_मुक्त_buf(xoutbuf);
out_nooutbuf:
	tesपंचांगgr_मुक्त_buf(axbuf);
out_noaxbuf:
	tesपंचांगgr_मुक्त_buf(xbuf);
out_noxbuf:
	kमुक्त(iv);
पूर्ण

अटल व्योम test_hash_sg_init(काष्ठा scatterlist *sg)
अणु
	पूर्णांक i;

	sg_init_table(sg, TVMEMSIZE);
	क्रम (i = 0; i < TVMEMSIZE; i++) अणु
		sg_set_buf(sg + i, tvmem[i], PAGE_SIZE);
		स_रखो(tvmem[i], 0xff, PAGE_SIZE);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक करो_one_ahash_op(काष्ठा ahash_request *req, पूर्णांक ret)
अणु
	काष्ठा crypto_रुको *रुको = req->base.data;

	वापस crypto_रुको_req(ret, रुको);
पूर्ण

काष्ठा test_mb_ahash_data अणु
	काष्ठा scatterlist sg[Xबफ_मानE];
	अक्षर result[64];
	काष्ठा ahash_request *req;
	काष्ठा crypto_रुको रुको;
	अक्षर *xbuf[Xबफ_मानE];
पूर्ण;

अटल अंतरभूत पूर्णांक करो_mult_ahash_op(काष्ठा test_mb_ahash_data *data, u32 num_mb,
				   पूर्णांक *rc)
अणु
	पूर्णांक i, err = 0;

	/* Fire up a bunch of concurrent requests */
	क्रम (i = 0; i < num_mb; i++)
		rc[i] = crypto_ahash_digest(data[i].req);

	/* Wait क्रम all requests to finish */
	क्रम (i = 0; i < num_mb; i++) अणु
		rc[i] = crypto_रुको_req(rc[i], &data[i].रुको);

		अगर (rc[i]) अणु
			pr_info("concurrent request %d error %d\n", i, rc[i]);
			err = rc[i];
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक test_mb_ahash_jअगरfies(काष्ठा test_mb_ahash_data *data, पूर्णांक blen,
				 पूर्णांक secs, u32 num_mb)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक bcount;
	पूर्णांक ret = 0;
	पूर्णांक *rc;

	rc = kसुस्मृति(num_mb, माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस -ENOMEM;

	क्रम (start = jअगरfies, end = start + secs * HZ, bcount = 0;
	     समय_beक्रमe(jअगरfies, end); bcount++) अणु
		ret = करो_mult_ahash_op(data, num_mb, rc);
		अगर (ret)
			जाओ out;
	पूर्ण

	pr_cont("%d operations in %d seconds (%llu bytes)\n",
		bcount * num_mb, secs, (u64)bcount * blen * num_mb);

out:
	kमुक्त(rc);
	वापस ret;
पूर्ण

अटल पूर्णांक test_mb_ahash_cycles(काष्ठा test_mb_ahash_data *data, पूर्णांक blen,
				u32 num_mb)
अणु
	अचिन्हित दीर्घ cycles = 0;
	पूर्णांक ret = 0;
	पूर्णांक i;
	पूर्णांक *rc;

	rc = kसुस्मृति(num_mb, माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस -ENOMEM;

	/* Warm-up run. */
	क्रम (i = 0; i < 4; i++) अणु
		ret = करो_mult_ahash_op(data, num_mb, rc);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* The real thing. */
	क्रम (i = 0; i < 8; i++) अणु
		cycles_t start, end;

		start = get_cycles();
		ret = करो_mult_ahash_op(data, num_mb, rc);
		end = get_cycles();

		अगर (ret)
			जाओ out;

		cycles += end - start;
	पूर्ण

	pr_cont("1 operation in %lu cycles (%d bytes)\n",
		(cycles + 4) / (8 * num_mb), blen);

out:
	kमुक्त(rc);
	वापस ret;
पूर्ण

अटल व्योम test_mb_ahash_speed(स्थिर अक्षर *algo, अचिन्हित पूर्णांक secs,
				काष्ठा hash_speed *speed, u32 num_mb)
अणु
	काष्ठा test_mb_ahash_data *data;
	काष्ठा crypto_ahash *tfm;
	अचिन्हित पूर्णांक i, j, k;
	पूर्णांक ret;

	data = kसुस्मृति(num_mb, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस;

	tfm = crypto_alloc_ahash(algo, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		pr_err("failed to load transform for %s: %ld\n",
			algo, PTR_ERR(tfm));
		जाओ मुक्त_data;
	पूर्ण

	क्रम (i = 0; i < num_mb; ++i) अणु
		अगर (tesपंचांगgr_alloc_buf(data[i].xbuf))
			जाओ out;

		crypto_init_रुको(&data[i].रुको);

		data[i].req = ahash_request_alloc(tfm, GFP_KERNEL);
		अगर (!data[i].req) अणु
			pr_err("alg: hash: Failed to allocate request for %s\n",
			       algo);
			जाओ out;
		पूर्ण

		ahash_request_set_callback(data[i].req, 0, crypto_req_करोne,
					   &data[i].रुको);

		sg_init_table(data[i].sg, Xबफ_मानE);
		क्रम (j = 0; j < Xबफ_मानE; j++) अणु
			sg_set_buf(data[i].sg + j, data[i].xbuf[j], PAGE_SIZE);
			स_रखो(data[i].xbuf[j], 0xff, PAGE_SIZE);
		पूर्ण
	पूर्ण

	pr_info("\ntesting speed of multibuffer %s (%s)\n", algo,
		get_driver_name(crypto_ahash, tfm));

	क्रम (i = 0; speed[i].blen != 0; i++) अणु
		/* For some reason this only tests digests. */
		अगर (speed[i].blen != speed[i].plen)
			जारी;

		अगर (speed[i].blen > Xबफ_मानE * PAGE_SIZE) अणु
			pr_err("template (%u) too big for tvmem (%lu)\n",
			       speed[i].blen, Xबफ_मानE * PAGE_SIZE);
			जाओ out;
		पूर्ण

		अगर (klen)
			crypto_ahash_setkey(tfm, tvmem[0], klen);

		क्रम (k = 0; k < num_mb; k++)
			ahash_request_set_crypt(data[k].req, data[k].sg,
						data[k].result, speed[i].blen);

		pr_info("test%3u "
			"(%5u byte blocks,%5u bytes per update,%4u updates): ",
			i, speed[i].blen, speed[i].plen,
			speed[i].blen / speed[i].plen);

		अगर (secs) अणु
			ret = test_mb_ahash_jअगरfies(data, speed[i].blen, secs,
						    num_mb);
			cond_resched();
		पूर्ण अन्यथा अणु
			ret = test_mb_ahash_cycles(data, speed[i].blen, num_mb);
		पूर्ण


		अगर (ret) अणु
			pr_err("At least one hashing failed ret=%d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण

out:
	क्रम (k = 0; k < num_mb; ++k)
		ahash_request_मुक्त(data[k].req);

	क्रम (k = 0; k < num_mb; ++k)
		tesपंचांगgr_मुक्त_buf(data[k].xbuf);

	crypto_मुक्त_ahash(tfm);

मुक्त_data:
	kमुक्त(data);
पूर्ण

अटल पूर्णांक test_ahash_jअगरfies_digest(काष्ठा ahash_request *req, पूर्णांक blen,
				     अक्षर *out, पूर्णांक secs)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक bcount;
	पूर्णांक ret;

	क्रम (start = jअगरfies, end = start + secs * HZ, bcount = 0;
	     समय_beक्रमe(jअगरfies, end); bcount++) अणु
		ret = करो_one_ahash_op(req, crypto_ahash_digest(req));
		अगर (ret)
			वापस ret;
	पूर्ण

	prपूर्णांकk("%6u opers/sec, %9lu bytes/sec\n",
	       bcount / secs, ((दीर्घ)bcount * blen) / secs);

	वापस 0;
पूर्ण

अटल पूर्णांक test_ahash_jअगरfies(काष्ठा ahash_request *req, पूर्णांक blen,
			      पूर्णांक plen, अक्षर *out, पूर्णांक secs)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक bcount, pcount;
	पूर्णांक ret;

	अगर (plen == blen)
		वापस test_ahash_jअगरfies_digest(req, blen, out, secs);

	क्रम (start = jअगरfies, end = start + secs * HZ, bcount = 0;
	     समय_beक्रमe(jअगरfies, end); bcount++) अणु
		ret = करो_one_ahash_op(req, crypto_ahash_init(req));
		अगर (ret)
			वापस ret;
		क्रम (pcount = 0; pcount < blen; pcount += plen) अणु
			ret = करो_one_ahash_op(req, crypto_ahash_update(req));
			अगर (ret)
				वापस ret;
		पूर्ण
		/* we assume there is enough space in 'out' क्रम the result */
		ret = करो_one_ahash_op(req, crypto_ahash_final(req));
		अगर (ret)
			वापस ret;
	पूर्ण

	pr_cont("%6u opers/sec, %9lu bytes/sec\n",
		bcount / secs, ((दीर्घ)bcount * blen) / secs);

	वापस 0;
पूर्ण

अटल पूर्णांक test_ahash_cycles_digest(काष्ठा ahash_request *req, पूर्णांक blen,
				    अक्षर *out)
अणु
	अचिन्हित दीर्घ cycles = 0;
	पूर्णांक ret, i;

	/* Warm-up run. */
	क्रम (i = 0; i < 4; i++) अणु
		ret = करो_one_ahash_op(req, crypto_ahash_digest(req));
		अगर (ret)
			जाओ out;
	पूर्ण

	/* The real thing. */
	क्रम (i = 0; i < 8; i++) अणु
		cycles_t start, end;

		start = get_cycles();

		ret = करो_one_ahash_op(req, crypto_ahash_digest(req));
		अगर (ret)
			जाओ out;

		end = get_cycles();

		cycles += end - start;
	पूर्ण

out:
	अगर (ret)
		वापस ret;

	pr_cont("%6lu cycles/operation, %4lu cycles/byte\n",
		cycles / 8, cycles / (8 * blen));

	वापस 0;
पूर्ण

अटल पूर्णांक test_ahash_cycles(काष्ठा ahash_request *req, पूर्णांक blen,
			     पूर्णांक plen, अक्षर *out)
अणु
	अचिन्हित दीर्घ cycles = 0;
	पूर्णांक i, pcount, ret;

	अगर (plen == blen)
		वापस test_ahash_cycles_digest(req, blen, out);

	/* Warm-up run. */
	क्रम (i = 0; i < 4; i++) अणु
		ret = करो_one_ahash_op(req, crypto_ahash_init(req));
		अगर (ret)
			जाओ out;
		क्रम (pcount = 0; pcount < blen; pcount += plen) अणु
			ret = करो_one_ahash_op(req, crypto_ahash_update(req));
			अगर (ret)
				जाओ out;
		पूर्ण
		ret = करो_one_ahash_op(req, crypto_ahash_final(req));
		अगर (ret)
			जाओ out;
	पूर्ण

	/* The real thing. */
	क्रम (i = 0; i < 8; i++) अणु
		cycles_t start, end;

		start = get_cycles();

		ret = करो_one_ahash_op(req, crypto_ahash_init(req));
		अगर (ret)
			जाओ out;
		क्रम (pcount = 0; pcount < blen; pcount += plen) अणु
			ret = करो_one_ahash_op(req, crypto_ahash_update(req));
			अगर (ret)
				जाओ out;
		पूर्ण
		ret = करो_one_ahash_op(req, crypto_ahash_final(req));
		अगर (ret)
			जाओ out;

		end = get_cycles();

		cycles += end - start;
	पूर्ण

out:
	अगर (ret)
		वापस ret;

	pr_cont("%6lu cycles/operation, %4lu cycles/byte\n",
		cycles / 8, cycles / (8 * blen));

	वापस 0;
पूर्ण

अटल व्योम test_ahash_speed_common(स्थिर अक्षर *algo, अचिन्हित पूर्णांक secs,
				    काष्ठा hash_speed *speed, अचिन्हित mask)
अणु
	काष्ठा scatterlist sg[TVMEMSIZE];
	काष्ठा crypto_रुको रुको;
	काष्ठा ahash_request *req;
	काष्ठा crypto_ahash *tfm;
	अक्षर *output;
	पूर्णांक i, ret;

	tfm = crypto_alloc_ahash(algo, 0, mask);
	अगर (IS_ERR(tfm)) अणु
		pr_err("failed to load transform for %s: %ld\n",
		       algo, PTR_ERR(tfm));
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_INFO "\ntesting speed of async %s (%s)\n", algo,
			get_driver_name(crypto_ahash, tfm));

	अगर (crypto_ahash_digestsize(tfm) > MAX_DIGEST_SIZE) अणु
		pr_err("digestsize(%u) > %d\n", crypto_ahash_digestsize(tfm),
		       MAX_DIGEST_SIZE);
		जाओ out;
	पूर्ण

	test_hash_sg_init(sg);
	req = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		pr_err("ahash request allocation failure\n");
		जाओ out;
	पूर्ण

	crypto_init_रुको(&रुको);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_करोne, &रुको);

	output = kदो_स्मृति(MAX_DIGEST_SIZE, GFP_KERNEL);
	अगर (!output)
		जाओ out_nomem;

	क्रम (i = 0; speed[i].blen != 0; i++) अणु
		अगर (speed[i].blen > TVMEMSIZE * PAGE_SIZE) अणु
			pr_err("template (%u) too big for tvmem (%lu)\n",
			       speed[i].blen, TVMEMSIZE * PAGE_SIZE);
			अवरोध;
		पूर्ण

		अगर (klen)
			crypto_ahash_setkey(tfm, tvmem[0], klen);

		pr_info("test%3u "
			"(%5u byte blocks,%5u bytes per update,%4u updates): ",
			i, speed[i].blen, speed[i].plen, speed[i].blen / speed[i].plen);

		ahash_request_set_crypt(req, sg, output, speed[i].plen);

		अगर (secs) अणु
			ret = test_ahash_jअगरfies(req, speed[i].blen,
						 speed[i].plen, output, secs);
			cond_resched();
		पूर्ण अन्यथा अणु
			ret = test_ahash_cycles(req, speed[i].blen,
						speed[i].plen, output);
		पूर्ण

		अगर (ret) अणु
			pr_err("hashing failed ret=%d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(output);

out_nomem:
	ahash_request_मुक्त(req);

out:
	crypto_मुक्त_ahash(tfm);
पूर्ण

अटल व्योम test_ahash_speed(स्थिर अक्षर *algo, अचिन्हित पूर्णांक secs,
			     काष्ठा hash_speed *speed)
अणु
	वापस test_ahash_speed_common(algo, secs, speed, 0);
पूर्ण

अटल व्योम test_hash_speed(स्थिर अक्षर *algo, अचिन्हित पूर्णांक secs,
			    काष्ठा hash_speed *speed)
अणु
	वापस test_ahash_speed_common(algo, secs, speed, CRYPTO_ALG_ASYNC);
पूर्ण

काष्ठा test_mb_skcipher_data अणु
	काष्ठा scatterlist sg[Xबफ_मानE];
	काष्ठा skcipher_request *req;
	काष्ठा crypto_रुको रुको;
	अक्षर *xbuf[Xबफ_मानE];
पूर्ण;

अटल पूर्णांक करो_mult_acipher_op(काष्ठा test_mb_skcipher_data *data, पूर्णांक enc,
				u32 num_mb, पूर्णांक *rc)
अणु
	पूर्णांक i, err = 0;

	/* Fire up a bunch of concurrent requests */
	क्रम (i = 0; i < num_mb; i++) अणु
		अगर (enc == ENCRYPT)
			rc[i] = crypto_skcipher_encrypt(data[i].req);
		अन्यथा
			rc[i] = crypto_skcipher_decrypt(data[i].req);
	पूर्ण

	/* Wait क्रम all requests to finish */
	क्रम (i = 0; i < num_mb; i++) अणु
		rc[i] = crypto_रुको_req(rc[i], &data[i].रुको);

		अगर (rc[i]) अणु
			pr_info("concurrent request %d error %d\n", i, rc[i]);
			err = rc[i];
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक test_mb_acipher_jअगरfies(काष्ठा test_mb_skcipher_data *data, पूर्णांक enc,
				पूर्णांक blen, पूर्णांक secs, u32 num_mb)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक bcount;
	पूर्णांक ret = 0;
	पूर्णांक *rc;

	rc = kसुस्मृति(num_mb, माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस -ENOMEM;

	क्रम (start = jअगरfies, end = start + secs * HZ, bcount = 0;
	     समय_beक्रमe(jअगरfies, end); bcount++) अणु
		ret = करो_mult_acipher_op(data, enc, num_mb, rc);
		अगर (ret)
			जाओ out;
	पूर्ण

	pr_cont("%d operations in %d seconds (%llu bytes)\n",
		bcount * num_mb, secs, (u64)bcount * blen * num_mb);

out:
	kमुक्त(rc);
	वापस ret;
पूर्ण

अटल पूर्णांक test_mb_acipher_cycles(काष्ठा test_mb_skcipher_data *data, पूर्णांक enc,
			       पूर्णांक blen, u32 num_mb)
अणु
	अचिन्हित दीर्घ cycles = 0;
	पूर्णांक ret = 0;
	पूर्णांक i;
	पूर्णांक *rc;

	rc = kसुस्मृति(num_mb, माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस -ENOMEM;

	/* Warm-up run. */
	क्रम (i = 0; i < 4; i++) अणु
		ret = करो_mult_acipher_op(data, enc, num_mb, rc);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* The real thing. */
	क्रम (i = 0; i < 8; i++) अणु
		cycles_t start, end;

		start = get_cycles();
		ret = करो_mult_acipher_op(data, enc, num_mb, rc);
		end = get_cycles();

		अगर (ret)
			जाओ out;

		cycles += end - start;
	पूर्ण

	pr_cont("1 operation in %lu cycles (%d bytes)\n",
		(cycles + 4) / (8 * num_mb), blen);

out:
	kमुक्त(rc);
	वापस ret;
पूर्ण

अटल व्योम test_mb_skcipher_speed(स्थिर अक्षर *algo, पूर्णांक enc, पूर्णांक secs,
				   काष्ठा cipher_speed_ढाँचा *ढाँचा,
				   अचिन्हित पूर्णांक tcount, u8 *keysize, u32 num_mb)
अणु
	काष्ठा test_mb_skcipher_data *data;
	काष्ठा crypto_skcipher *tfm;
	अचिन्हित पूर्णांक i, j, iv_len;
	स्थिर पूर्णांक *b_size;
	स्थिर अक्षर *key;
	स्थिर अक्षर *e;
	अक्षर iv[128];
	पूर्णांक ret;

	अगर (enc == ENCRYPT)
		e = "encryption";
	अन्यथा
		e = "decryption";

	data = kसुस्मृति(num_mb, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस;

	tfm = crypto_alloc_skcipher(algo, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		pr_err("failed to load transform for %s: %ld\n",
			algo, PTR_ERR(tfm));
		जाओ out_मुक्त_data;
	पूर्ण

	क्रम (i = 0; i < num_mb; ++i)
		अगर (tesपंचांगgr_alloc_buf(data[i].xbuf)) अणु
			जबतक (i--)
				tesपंचांगgr_मुक्त_buf(data[i].xbuf);
			जाओ out_मुक्त_tfm;
		पूर्ण


	क्रम (i = 0; i < num_mb; ++i)
		अगर (tesपंचांगgr_alloc_buf(data[i].xbuf)) अणु
			जबतक (i--)
				tesपंचांगgr_मुक्त_buf(data[i].xbuf);
			जाओ out_मुक्त_tfm;
		पूर्ण


	क्रम (i = 0; i < num_mb; ++i) अणु
		data[i].req = skcipher_request_alloc(tfm, GFP_KERNEL);
		अगर (!data[i].req) अणु
			pr_err("alg: skcipher: Failed to allocate request for %s\n",
			       algo);
			जबतक (i--)
				skcipher_request_मुक्त(data[i].req);
			जाओ out_मुक्त_xbuf;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_mb; ++i) अणु
		skcipher_request_set_callback(data[i].req,
					      CRYPTO_TFM_REQ_MAY_BACKLOG,
					      crypto_req_करोne, &data[i].रुको);
		crypto_init_रुको(&data[i].रुको);
	पूर्ण

	pr_info("\ntesting speed of multibuffer %s (%s) %s\n", algo,
		get_driver_name(crypto_skcipher, tfm), e);

	i = 0;
	करो अणु
		b_size = block_sizes;
		करो अणु
			u32 bs = round_up(*b_size, crypto_skcipher_blocksize(tfm));

			अगर (bs > Xबफ_मानE * PAGE_SIZE) अणु
				pr_err("template (%u) too big for buffer (%lu)\n",
				       *b_size, Xबफ_मानE * PAGE_SIZE);
				जाओ out;
			पूर्ण

			pr_info("test %u (%d bit key, %d byte blocks): ", i,
				*keysize * 8, bs);

			/* Set up tfm global state, i.e. the key */

			स_रखो(tvmem[0], 0xff, PAGE_SIZE);
			key = tvmem[0];
			क्रम (j = 0; j < tcount; j++) अणु
				अगर (ढाँचा[j].klen == *keysize) अणु
					key = ढाँचा[j].key;
					अवरोध;
				पूर्ण
			पूर्ण

			crypto_skcipher_clear_flags(tfm, ~0);

			ret = crypto_skcipher_setkey(tfm, key, *keysize);
			अगर (ret) अणु
				pr_err("setkey() failed flags=%x\n",
				       crypto_skcipher_get_flags(tfm));
				जाओ out;
			पूर्ण

			iv_len = crypto_skcipher_ivsize(tfm);
			अगर (iv_len)
				स_रखो(&iv, 0xff, iv_len);

			/* Now setup per request stuff, i.e. buffers */

			क्रम (j = 0; j < num_mb; ++j) अणु
				काष्ठा test_mb_skcipher_data *cur = &data[j];
				अचिन्हित पूर्णांक k = bs;
				अचिन्हित पूर्णांक pages = DIV_ROUND_UP(k, PAGE_SIZE);
				अचिन्हित पूर्णांक p = 0;

				sg_init_table(cur->sg, pages);

				जबतक (k > PAGE_SIZE) अणु
					sg_set_buf(cur->sg + p, cur->xbuf[p],
						   PAGE_SIZE);
					स_रखो(cur->xbuf[p], 0xff, PAGE_SIZE);
					p++;
					k -= PAGE_SIZE;
				पूर्ण

				sg_set_buf(cur->sg + p, cur->xbuf[p], k);
				स_रखो(cur->xbuf[p], 0xff, k);

				skcipher_request_set_crypt(cur->req, cur->sg,
							   cur->sg, *b_size,
							   iv);
			पूर्ण

			अगर (secs) अणु
				ret = test_mb_acipher_jअगरfies(data, enc,
							      bs, secs,
							      num_mb);
				cond_resched();
			पूर्ण अन्यथा अणु
				ret = test_mb_acipher_cycles(data, enc,
							     bs, num_mb);
			पूर्ण

			अगर (ret) अणु
				pr_err("%s() failed flags=%x\n", e,
				       crypto_skcipher_get_flags(tfm));
				अवरोध;
			पूर्ण
			b_size++;
			i++;
		पूर्ण जबतक (*b_size);
		keysize++;
	पूर्ण जबतक (*keysize);

out:
	क्रम (i = 0; i < num_mb; ++i)
		skcipher_request_मुक्त(data[i].req);
out_मुक्त_xbuf:
	क्रम (i = 0; i < num_mb; ++i)
		tesपंचांगgr_मुक्त_buf(data[i].xbuf);
out_मुक्त_tfm:
	crypto_मुक्त_skcipher(tfm);
out_मुक्त_data:
	kमुक्त(data);
पूर्ण

अटल अंतरभूत पूर्णांक करो_one_acipher_op(काष्ठा skcipher_request *req, पूर्णांक ret)
अणु
	काष्ठा crypto_रुको *रुको = req->base.data;

	वापस crypto_रुको_req(ret, रुको);
पूर्ण

अटल पूर्णांक test_acipher_jअगरfies(काष्ठा skcipher_request *req, पूर्णांक enc,
				पूर्णांक blen, पूर्णांक secs)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक bcount;
	पूर्णांक ret;

	क्रम (start = jअगरfies, end = start + secs * HZ, bcount = 0;
	     समय_beक्रमe(jअगरfies, end); bcount++) अणु
		अगर (enc)
			ret = करो_one_acipher_op(req,
						crypto_skcipher_encrypt(req));
		अन्यथा
			ret = करो_one_acipher_op(req,
						crypto_skcipher_decrypt(req));

		अगर (ret)
			वापस ret;
	पूर्ण

	pr_cont("%d operations in %d seconds (%llu bytes)\n",
		bcount, secs, (u64)bcount * blen);
	वापस 0;
पूर्ण

अटल पूर्णांक test_acipher_cycles(काष्ठा skcipher_request *req, पूर्णांक enc,
			       पूर्णांक blen)
अणु
	अचिन्हित दीर्घ cycles = 0;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* Warm-up run. */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (enc)
			ret = करो_one_acipher_op(req,
						crypto_skcipher_encrypt(req));
		अन्यथा
			ret = करो_one_acipher_op(req,
						crypto_skcipher_decrypt(req));

		अगर (ret)
			जाओ out;
	पूर्ण

	/* The real thing. */
	क्रम (i = 0; i < 8; i++) अणु
		cycles_t start, end;

		start = get_cycles();
		अगर (enc)
			ret = करो_one_acipher_op(req,
						crypto_skcipher_encrypt(req));
		अन्यथा
			ret = करो_one_acipher_op(req,
						crypto_skcipher_decrypt(req));
		end = get_cycles();

		अगर (ret)
			जाओ out;

		cycles += end - start;
	पूर्ण

out:
	अगर (ret == 0)
		pr_cont("1 operation in %lu cycles (%d bytes)\n",
			(cycles + 4) / 8, blen);

	वापस ret;
पूर्ण

अटल व्योम test_skcipher_speed(स्थिर अक्षर *algo, पूर्णांक enc, अचिन्हित पूर्णांक secs,
				काष्ठा cipher_speed_ढाँचा *ढाँचा,
				अचिन्हित पूर्णांक tcount, u8 *keysize, bool async)
अणु
	अचिन्हित पूर्णांक ret, i, j, k, iv_len;
	काष्ठा crypto_रुको रुको;
	स्थिर अक्षर *key;
	अक्षर iv[128];
	काष्ठा skcipher_request *req;
	काष्ठा crypto_skcipher *tfm;
	स्थिर पूर्णांक *b_size;
	स्थिर अक्षर *e;

	अगर (enc == ENCRYPT)
		e = "encryption";
	अन्यथा
		e = "decryption";

	crypto_init_रुको(&रुको);

	tfm = crypto_alloc_skcipher(algo, 0, async ? 0 : CRYPTO_ALG_ASYNC);

	अगर (IS_ERR(tfm)) अणु
		pr_err("failed to load transform for %s: %ld\n", algo,
		       PTR_ERR(tfm));
		वापस;
	पूर्ण

	pr_info("\ntesting speed of %s %s (%s) %s\n", async ? "async" : "sync",
		algo, get_driver_name(crypto_skcipher, tfm), e);

	req = skcipher_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		pr_err("tcrypt: skcipher: Failed to allocate request for %s\n",
		       algo);
		जाओ out;
	पूर्ण

	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				      crypto_req_करोne, &रुको);

	i = 0;
	करो अणु
		b_size = block_sizes;

		करो अणु
			u32 bs = round_up(*b_size, crypto_skcipher_blocksize(tfm));
			काष्ठा scatterlist sg[TVMEMSIZE];

			अगर ((*keysize + bs) > TVMEMSIZE * PAGE_SIZE) अणु
				pr_err("template (%u) too big for "
				       "tvmem (%lu)\n", *keysize + bs,
				       TVMEMSIZE * PAGE_SIZE);
				जाओ out_मुक्त_req;
			पूर्ण

			pr_info("test %u (%d bit key, %d byte blocks): ", i,
				*keysize * 8, bs);

			स_रखो(tvmem[0], 0xff, PAGE_SIZE);

			/* set key, plain text and IV */
			key = tvmem[0];
			क्रम (j = 0; j < tcount; j++) अणु
				अगर (ढाँचा[j].klen == *keysize) अणु
					key = ढाँचा[j].key;
					अवरोध;
				पूर्ण
			पूर्ण

			crypto_skcipher_clear_flags(tfm, ~0);

			ret = crypto_skcipher_setkey(tfm, key, *keysize);
			अगर (ret) अणु
				pr_err("setkey() failed flags=%x\n",
					crypto_skcipher_get_flags(tfm));
				जाओ out_मुक्त_req;
			पूर्ण

			k = *keysize + bs;
			sg_init_table(sg, DIV_ROUND_UP(k, PAGE_SIZE));

			अगर (k > PAGE_SIZE) अणु
				sg_set_buf(sg, tvmem[0] + *keysize,
				   PAGE_SIZE - *keysize);
				k -= PAGE_SIZE;
				j = 1;
				जबतक (k > PAGE_SIZE) अणु
					sg_set_buf(sg + j, tvmem[j], PAGE_SIZE);
					स_रखो(tvmem[j], 0xff, PAGE_SIZE);
					j++;
					k -= PAGE_SIZE;
				पूर्ण
				sg_set_buf(sg + j, tvmem[j], k);
				स_रखो(tvmem[j], 0xff, k);
			पूर्ण अन्यथा अणु
				sg_set_buf(sg, tvmem[0] + *keysize, bs);
			पूर्ण

			iv_len = crypto_skcipher_ivsize(tfm);
			अगर (iv_len)
				स_रखो(&iv, 0xff, iv_len);

			skcipher_request_set_crypt(req, sg, sg, bs, iv);

			अगर (secs) अणु
				ret = test_acipher_jअगरfies(req, enc,
							   bs, secs);
				cond_resched();
			पूर्ण अन्यथा अणु
				ret = test_acipher_cycles(req, enc,
							  bs);
			पूर्ण

			अगर (ret) अणु
				pr_err("%s() failed flags=%x\n", e,
				       crypto_skcipher_get_flags(tfm));
				अवरोध;
			पूर्ण
			b_size++;
			i++;
		पूर्ण जबतक (*b_size);
		keysize++;
	पूर्ण जबतक (*keysize);

out_मुक्त_req:
	skcipher_request_मुक्त(req);
out:
	crypto_मुक्त_skcipher(tfm);
पूर्ण

अटल व्योम test_acipher_speed(स्थिर अक्षर *algo, पूर्णांक enc, अचिन्हित पूर्णांक secs,
			       काष्ठा cipher_speed_ढाँचा *ढाँचा,
			       अचिन्हित पूर्णांक tcount, u8 *keysize)
अणु
	वापस test_skcipher_speed(algo, enc, secs, ढाँचा, tcount, keysize,
				   true);
पूर्ण

अटल व्योम test_cipher_speed(स्थिर अक्षर *algo, पूर्णांक enc, अचिन्हित पूर्णांक secs,
			      काष्ठा cipher_speed_ढाँचा *ढाँचा,
			      अचिन्हित पूर्णांक tcount, u8 *keysize)
अणु
	वापस test_skcipher_speed(algo, enc, secs, ढाँचा, tcount, keysize,
				   false);
पूर्ण

अटल व्योम test_available(व्योम)
अणु
	स्थिर अक्षर **name = check;

	जबतक (*name) अणु
		prपूर्णांकk("alg %s ", *name);
		prपूर्णांकk(crypto_has_alg(*name, 0, 0) ?
		       "found\n" : "not found\n");
		name++;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक tcrypt_test(स्थिर अक्षर *alg)
अणु
	पूर्णांक ret;

	pr_debug("testing %s\n", alg);

	ret = alg_test(alg, alg, 0, 0);
	/* non-fips algs वापस -EINVAL in fips mode */
	अगर (fips_enabled && ret == -EINVAL)
		ret = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक करो_test(स्थिर अक्षर *alg, u32 type, u32 mask, पूर्णांक m, u32 num_mb)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;

	चयन (m) अणु
	हाल 0:
		अगर (alg) अणु
			अगर (!crypto_has_alg(alg, type,
					    mask ?: CRYPTO_ALG_TYPE_MASK))
				ret = -ENOENT;
			अवरोध;
		पूर्ण

		क्रम (i = 1; i < 200; i++)
			ret += करो_test(शून्य, 0, 0, i, num_mb);
		अवरोध;

	हाल 1:
		ret += tcrypt_test("md5");
		अवरोध;

	हाल 2:
		ret += tcrypt_test("sha1");
		अवरोध;

	हाल 3:
		ret += tcrypt_test("ecb(des)");
		ret += tcrypt_test("cbc(des)");
		ret += tcrypt_test("ctr(des)");
		अवरोध;

	हाल 4:
		ret += tcrypt_test("ecb(des3_ede)");
		ret += tcrypt_test("cbc(des3_ede)");
		ret += tcrypt_test("ctr(des3_ede)");
		अवरोध;

	हाल 5:
		ret += tcrypt_test("md4");
		अवरोध;

	हाल 6:
		ret += tcrypt_test("sha256");
		अवरोध;

	हाल 7:
		ret += tcrypt_test("ecb(blowfish)");
		ret += tcrypt_test("cbc(blowfish)");
		ret += tcrypt_test("ctr(blowfish)");
		अवरोध;

	हाल 8:
		ret += tcrypt_test("ecb(twofish)");
		ret += tcrypt_test("cbc(twofish)");
		ret += tcrypt_test("ctr(twofish)");
		ret += tcrypt_test("lrw(twofish)");
		ret += tcrypt_test("xts(twofish)");
		अवरोध;

	हाल 9:
		ret += tcrypt_test("ecb(serpent)");
		ret += tcrypt_test("cbc(serpent)");
		ret += tcrypt_test("ctr(serpent)");
		ret += tcrypt_test("lrw(serpent)");
		ret += tcrypt_test("xts(serpent)");
		अवरोध;

	हाल 10:
		ret += tcrypt_test("ecb(aes)");
		ret += tcrypt_test("cbc(aes)");
		ret += tcrypt_test("lrw(aes)");
		ret += tcrypt_test("xts(aes)");
		ret += tcrypt_test("ctr(aes)");
		ret += tcrypt_test("rfc3686(ctr(aes))");
		ret += tcrypt_test("ofb(aes)");
		ret += tcrypt_test("cfb(aes)");
		अवरोध;

	हाल 11:
		ret += tcrypt_test("sha384");
		अवरोध;

	हाल 12:
		ret += tcrypt_test("sha512");
		अवरोध;

	हाल 13:
		ret += tcrypt_test("deflate");
		अवरोध;

	हाल 14:
		ret += tcrypt_test("ecb(cast5)");
		ret += tcrypt_test("cbc(cast5)");
		ret += tcrypt_test("ctr(cast5)");
		अवरोध;

	हाल 15:
		ret += tcrypt_test("ecb(cast6)");
		ret += tcrypt_test("cbc(cast6)");
		ret += tcrypt_test("ctr(cast6)");
		ret += tcrypt_test("lrw(cast6)");
		ret += tcrypt_test("xts(cast6)");
		अवरोध;

	हाल 16:
		ret += tcrypt_test("ecb(arc4)");
		अवरोध;

	हाल 17:
		ret += tcrypt_test("michael_mic");
		अवरोध;

	हाल 18:
		ret += tcrypt_test("crc32c");
		अवरोध;

	हाल 19:
		ret += tcrypt_test("ecb(tea)");
		अवरोध;

	हाल 20:
		ret += tcrypt_test("ecb(xtea)");
		अवरोध;

	हाल 21:
		ret += tcrypt_test("ecb(khazad)");
		अवरोध;

	हाल 22:
		ret += tcrypt_test("wp512");
		अवरोध;

	हाल 23:
		ret += tcrypt_test("wp384");
		अवरोध;

	हाल 24:
		ret += tcrypt_test("wp256");
		अवरोध;

	हाल 26:
		ret += tcrypt_test("ecb(anubis)");
		ret += tcrypt_test("cbc(anubis)");
		अवरोध;

	हाल 30:
		ret += tcrypt_test("ecb(xeta)");
		अवरोध;

	हाल 31:
		ret += tcrypt_test("pcbc(fcrypt)");
		अवरोध;

	हाल 32:
		ret += tcrypt_test("ecb(camellia)");
		ret += tcrypt_test("cbc(camellia)");
		ret += tcrypt_test("ctr(camellia)");
		ret += tcrypt_test("lrw(camellia)");
		ret += tcrypt_test("xts(camellia)");
		अवरोध;

	हाल 33:
		ret += tcrypt_test("sha224");
		अवरोध;

	हाल 35:
		ret += tcrypt_test("gcm(aes)");
		अवरोध;

	हाल 36:
		ret += tcrypt_test("lzo");
		अवरोध;

	हाल 37:
		ret += tcrypt_test("ccm(aes)");
		अवरोध;

	हाल 38:
		ret += tcrypt_test("cts(cbc(aes))");
		अवरोध;

        हाल 40:
		ret += tcrypt_test("rmd160");
		अवरोध;

	हाल 43:
		ret += tcrypt_test("ecb(seed)");
		अवरोध;

	हाल 45:
		ret += tcrypt_test("rfc4309(ccm(aes))");
		अवरोध;

	हाल 46:
		ret += tcrypt_test("ghash");
		अवरोध;

	हाल 47:
		ret += tcrypt_test("crct10dif");
		अवरोध;

	हाल 48:
		ret += tcrypt_test("sha3-224");
		अवरोध;

	हाल 49:
		ret += tcrypt_test("sha3-256");
		अवरोध;

	हाल 50:
		ret += tcrypt_test("sha3-384");
		अवरोध;

	हाल 51:
		ret += tcrypt_test("sha3-512");
		अवरोध;

	हाल 52:
		ret += tcrypt_test("sm3");
		अवरोध;

	हाल 53:
		ret += tcrypt_test("streebog256");
		अवरोध;

	हाल 54:
		ret += tcrypt_test("streebog512");
		अवरोध;

	हाल 100:
		ret += tcrypt_test("hmac(md5)");
		अवरोध;

	हाल 101:
		ret += tcrypt_test("hmac(sha1)");
		अवरोध;

	हाल 102:
		ret += tcrypt_test("hmac(sha256)");
		अवरोध;

	हाल 103:
		ret += tcrypt_test("hmac(sha384)");
		अवरोध;

	हाल 104:
		ret += tcrypt_test("hmac(sha512)");
		अवरोध;

	हाल 105:
		ret += tcrypt_test("hmac(sha224)");
		अवरोध;

	हाल 106:
		ret += tcrypt_test("xcbc(aes)");
		अवरोध;

	हाल 108:
		ret += tcrypt_test("hmac(rmd160)");
		अवरोध;

	हाल 109:
		ret += tcrypt_test("vmac64(aes)");
		अवरोध;

	हाल 111:
		ret += tcrypt_test("hmac(sha3-224)");
		अवरोध;

	हाल 112:
		ret += tcrypt_test("hmac(sha3-256)");
		अवरोध;

	हाल 113:
		ret += tcrypt_test("hmac(sha3-384)");
		अवरोध;

	हाल 114:
		ret += tcrypt_test("hmac(sha3-512)");
		अवरोध;

	हाल 115:
		ret += tcrypt_test("hmac(streebog256)");
		अवरोध;

	हाल 116:
		ret += tcrypt_test("hmac(streebog512)");
		अवरोध;

	हाल 150:
		ret += tcrypt_test("ansi_cprng");
		अवरोध;

	हाल 151:
		ret += tcrypt_test("rfc4106(gcm(aes))");
		अवरोध;

	हाल 152:
		ret += tcrypt_test("rfc4543(gcm(aes))");
		अवरोध;

	हाल 153:
		ret += tcrypt_test("cmac(aes)");
		अवरोध;

	हाल 154:
		ret += tcrypt_test("cmac(des3_ede)");
		अवरोध;

	हाल 155:
		ret += tcrypt_test("authenc(hmac(sha1),cbc(aes))");
		अवरोध;

	हाल 156:
		ret += tcrypt_test("authenc(hmac(md5),ecb(cipher_null))");
		अवरोध;

	हाल 157:
		ret += tcrypt_test("authenc(hmac(sha1),ecb(cipher_null))");
		अवरोध;
	हाल 181:
		ret += tcrypt_test("authenc(hmac(sha1),cbc(des))");
		अवरोध;
	हाल 182:
		ret += tcrypt_test("authenc(hmac(sha1),cbc(des3_ede))");
		अवरोध;
	हाल 183:
		ret += tcrypt_test("authenc(hmac(sha224),cbc(des))");
		अवरोध;
	हाल 184:
		ret += tcrypt_test("authenc(hmac(sha224),cbc(des3_ede))");
		अवरोध;
	हाल 185:
		ret += tcrypt_test("authenc(hmac(sha256),cbc(des))");
		अवरोध;
	हाल 186:
		ret += tcrypt_test("authenc(hmac(sha256),cbc(des3_ede))");
		अवरोध;
	हाल 187:
		ret += tcrypt_test("authenc(hmac(sha384),cbc(des))");
		अवरोध;
	हाल 188:
		ret += tcrypt_test("authenc(hmac(sha384),cbc(des3_ede))");
		अवरोध;
	हाल 189:
		ret += tcrypt_test("authenc(hmac(sha512),cbc(des))");
		अवरोध;
	हाल 190:
		ret += tcrypt_test("authenc(hmac(sha512),cbc(des3_ede))");
		अवरोध;
	हाल 191:
		ret += tcrypt_test("ecb(sm4)");
		ret += tcrypt_test("cbc(sm4)");
		ret += tcrypt_test("ctr(sm4)");
		अवरोध;
	हाल 200:
		test_cipher_speed("ecb(aes)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("ecb(aes)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("cbc(aes)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("cbc(aes)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("lrw(aes)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_40_48);
		test_cipher_speed("lrw(aes)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_40_48);
		test_cipher_speed("xts(aes)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_64);
		test_cipher_speed("xts(aes)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_64);
		test_cipher_speed("cts(cbc(aes))", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("cts(cbc(aes))", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("ctr(aes)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("ctr(aes)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("cfb(aes)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("cfb(aes)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		अवरोध;

	हाल 201:
		test_cipher_speed("ecb(des3_ede)", ENCRYPT, sec,
				des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				speed_ढाँचा_24);
		test_cipher_speed("ecb(des3_ede)", DECRYPT, sec,
				des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				speed_ढाँचा_24);
		test_cipher_speed("cbc(des3_ede)", ENCRYPT, sec,
				des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				speed_ढाँचा_24);
		test_cipher_speed("cbc(des3_ede)", DECRYPT, sec,
				des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				speed_ढाँचा_24);
		test_cipher_speed("ctr(des3_ede)", ENCRYPT, sec,
				des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				speed_ढाँचा_24);
		test_cipher_speed("ctr(des3_ede)", DECRYPT, sec,
				des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				speed_ढाँचा_24);
		अवरोध;

	हाल 202:
		test_cipher_speed("ecb(twofish)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("ecb(twofish)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("cbc(twofish)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("cbc(twofish)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("ctr(twofish)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("ctr(twofish)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("lrw(twofish)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_40_48);
		test_cipher_speed("lrw(twofish)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_40_48);
		test_cipher_speed("xts(twofish)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_48_64);
		test_cipher_speed("xts(twofish)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_48_64);
		अवरोध;

	हाल 203:
		test_cipher_speed("ecb(blowfish)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_32);
		test_cipher_speed("ecb(blowfish)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_32);
		test_cipher_speed("cbc(blowfish)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_32);
		test_cipher_speed("cbc(blowfish)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_32);
		test_cipher_speed("ctr(blowfish)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_32);
		test_cipher_speed("ctr(blowfish)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_32);
		अवरोध;

	हाल 204:
		test_cipher_speed("ecb(des)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8);
		test_cipher_speed("ecb(des)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8);
		test_cipher_speed("cbc(des)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8);
		test_cipher_speed("cbc(des)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8);
		अवरोध;

	हाल 205:
		test_cipher_speed("ecb(camellia)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("ecb(camellia)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("cbc(camellia)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("cbc(camellia)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("ctr(camellia)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("ctr(camellia)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16_24_32);
		test_cipher_speed("lrw(camellia)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_40_48);
		test_cipher_speed("lrw(camellia)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_40_48);
		test_cipher_speed("xts(camellia)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_48_64);
		test_cipher_speed("xts(camellia)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_32_48_64);
		अवरोध;

	हाल 207:
		test_cipher_speed("ecb(serpent)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("ecb(serpent)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("cbc(serpent)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("cbc(serpent)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("ctr(serpent)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("ctr(serpent)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("lrw(serpent)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_32_48);
		test_cipher_speed("lrw(serpent)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_32_48);
		test_cipher_speed("xts(serpent)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_32_64);
		test_cipher_speed("xts(serpent)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_32_64);
		अवरोध;

	हाल 208:
		test_cipher_speed("ecb(arc4)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8);
		अवरोध;

	हाल 209:
		test_cipher_speed("ecb(cast5)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_16);
		test_cipher_speed("ecb(cast5)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_16);
		test_cipher_speed("cbc(cast5)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_16);
		test_cipher_speed("cbc(cast5)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_16);
		test_cipher_speed("ctr(cast5)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_16);
		test_cipher_speed("ctr(cast5)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_8_16);
		अवरोध;

	हाल 210:
		test_cipher_speed("ecb(cast6)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("ecb(cast6)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("cbc(cast6)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("cbc(cast6)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("ctr(cast6)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("ctr(cast6)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_32);
		test_cipher_speed("lrw(cast6)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_32_48);
		test_cipher_speed("lrw(cast6)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_32_48);
		test_cipher_speed("xts(cast6)", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_32_64);
		test_cipher_speed("xts(cast6)", DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_32_64);
		अवरोध;

	हाल 211:
		test_aead_speed("rfc4106(gcm(aes))", ENCRYPT, sec,
				शून्य, 0, 16, 16, aead_speed_ढाँचा_20);
		test_aead_speed("gcm(aes)", ENCRYPT, sec,
				शून्य, 0, 16, 8, speed_ढाँचा_16_24_32);
		test_aead_speed("rfc4106(gcm(aes))", DECRYPT, sec,
				शून्य, 0, 16, 16, aead_speed_ढाँचा_20);
		test_aead_speed("gcm(aes)", DECRYPT, sec,
				शून्य, 0, 16, 8, speed_ढाँचा_16_24_32);
		अवरोध;

	हाल 212:
		test_aead_speed("rfc4309(ccm(aes))", ENCRYPT, sec,
				शून्य, 0, 16, 16, aead_speed_ढाँचा_19);
		test_aead_speed("rfc4309(ccm(aes))", DECRYPT, sec,
				शून्य, 0, 16, 16, aead_speed_ढाँचा_19);
		अवरोध;

	हाल 213:
		test_aead_speed("rfc7539esp(chacha20,poly1305)", ENCRYPT, sec,
				शून्य, 0, 16, 8, aead_speed_ढाँचा_36);
		test_aead_speed("rfc7539esp(chacha20,poly1305)", DECRYPT, sec,
				शून्य, 0, 16, 8, aead_speed_ढाँचा_36);
		अवरोध;

	हाल 214:
		test_cipher_speed("chacha20", ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_32);
		अवरोध;

	हाल 215:
		test_mb_aead_speed("rfc4106(gcm(aes))", ENCRYPT, sec, शून्य,
				   0, 16, 16, aead_speed_ढाँचा_20, num_mb);
		test_mb_aead_speed("gcm(aes)", ENCRYPT, sec, शून्य, 0, 16, 8,
				   speed_ढाँचा_16_24_32, num_mb);
		test_mb_aead_speed("rfc4106(gcm(aes))", DECRYPT, sec, शून्य,
				   0, 16, 16, aead_speed_ढाँचा_20, num_mb);
		test_mb_aead_speed("gcm(aes)", DECRYPT, sec, शून्य, 0, 16, 8,
				   speed_ढाँचा_16_24_32, num_mb);
		अवरोध;

	हाल 216:
		test_mb_aead_speed("rfc4309(ccm(aes))", ENCRYPT, sec, शून्य, 0,
				   16, 16, aead_speed_ढाँचा_19, num_mb);
		test_mb_aead_speed("rfc4309(ccm(aes))", DECRYPT, sec, शून्य, 0,
				   16, 16, aead_speed_ढाँचा_19, num_mb);
		अवरोध;

	हाल 217:
		test_mb_aead_speed("rfc7539esp(chacha20,poly1305)", ENCRYPT,
				   sec, शून्य, 0, 16, 8, aead_speed_ढाँचा_36,
				   num_mb);
		test_mb_aead_speed("rfc7539esp(chacha20,poly1305)", DECRYPT,
				   sec, शून्य, 0, 16, 8, aead_speed_ढाँचा_36,
				   num_mb);
		अवरोध;

	हाल 218:
		test_cipher_speed("ecb(sm4)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16);
		test_cipher_speed("ecb(sm4)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16);
		test_cipher_speed("cbc(sm4)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16);
		test_cipher_speed("cbc(sm4)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16);
		test_cipher_speed("ctr(sm4)", ENCRYPT, sec, शून्य, 0,
				speed_ढाँचा_16);
		test_cipher_speed("ctr(sm4)", DECRYPT, sec, शून्य, 0,
				speed_ढाँचा_16);
		अवरोध;

	हाल 219:
		test_cipher_speed("adiantum(xchacha12,aes)", ENCRYPT, sec, शून्य,
				  0, speed_ढाँचा_32);
		test_cipher_speed("adiantum(xchacha12,aes)", DECRYPT, sec, शून्य,
				  0, speed_ढाँचा_32);
		test_cipher_speed("adiantum(xchacha20,aes)", ENCRYPT, sec, शून्य,
				  0, speed_ढाँचा_32);
		test_cipher_speed("adiantum(xchacha20,aes)", DECRYPT, sec, शून्य,
				  0, speed_ढाँचा_32);
		अवरोध;

	हाल 220:
		test_acipher_speed("essiv(cbc(aes),sha256)",
				  ENCRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_24_32);
		test_acipher_speed("essiv(cbc(aes),sha256)",
				  DECRYPT, sec, शून्य, 0,
				  speed_ढाँचा_16_24_32);
		अवरोध;

	हाल 221:
		test_aead_speed("aegis128", ENCRYPT, sec,
				शून्य, 0, 16, 8, speed_ढाँचा_16);
		test_aead_speed("aegis128", DECRYPT, sec,
				शून्य, 0, 16, 8, speed_ढाँचा_16);
		अवरोध;

	हाल 300:
		अगर (alg) अणु
			test_hash_speed(alg, sec, generic_hash_speed_ढाँचा);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल 301:
		test_hash_speed("md4", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 302:
		test_hash_speed("md5", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 303:
		test_hash_speed("sha1", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 304:
		test_hash_speed("sha256", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 305:
		test_hash_speed("sha384", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 306:
		test_hash_speed("sha512", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 307:
		test_hash_speed("wp256", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 308:
		test_hash_speed("wp384", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 309:
		test_hash_speed("wp512", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 313:
		test_hash_speed("sha224", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 315:
		test_hash_speed("rmd160", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 318:
		klen = 16;
		test_hash_speed("ghash", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 319:
		test_hash_speed("crc32c", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 320:
		test_hash_speed("crct10dif", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 321:
		test_hash_speed("poly1305", sec, poly1305_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 322:
		test_hash_speed("sha3-224", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 323:
		test_hash_speed("sha3-256", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 324:
		test_hash_speed("sha3-384", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 325:
		test_hash_speed("sha3-512", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 326:
		test_hash_speed("sm3", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 327:
		test_hash_speed("streebog256", sec,
				generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 328:
		test_hash_speed("streebog512", sec,
				generic_hash_speed_ढाँचा);
		अगर (mode > 300 && mode < 400) अवरोध;
		fallthrough;
	हाल 399:
		अवरोध;

	हाल 400:
		अगर (alg) अणु
			test_ahash_speed(alg, sec, generic_hash_speed_ढाँचा);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल 401:
		test_ahash_speed("md4", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 402:
		test_ahash_speed("md5", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 403:
		test_ahash_speed("sha1", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 404:
		test_ahash_speed("sha256", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 405:
		test_ahash_speed("sha384", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 406:
		test_ahash_speed("sha512", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 407:
		test_ahash_speed("wp256", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 408:
		test_ahash_speed("wp384", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 409:
		test_ahash_speed("wp512", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 413:
		test_ahash_speed("sha224", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 415:
		test_ahash_speed("rmd160", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 418:
		test_ahash_speed("sha3-224", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 419:
		test_ahash_speed("sha3-256", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 420:
		test_ahash_speed("sha3-384", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 421:
		test_ahash_speed("sha3-512", sec, generic_hash_speed_ढाँचा);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 422:
		test_mb_ahash_speed("sha1", sec, generic_hash_speed_ढाँचा,
				    num_mb);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 423:
		test_mb_ahash_speed("sha256", sec, generic_hash_speed_ढाँचा,
				    num_mb);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 424:
		test_mb_ahash_speed("sha512", sec, generic_hash_speed_ढाँचा,
				    num_mb);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 425:
		test_mb_ahash_speed("sm3", sec, generic_hash_speed_ढाँचा,
				    num_mb);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 426:
		test_mb_ahash_speed("streebog256", sec,
				    generic_hash_speed_ढाँचा, num_mb);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 427:
		test_mb_ahash_speed("streebog512", sec,
				    generic_hash_speed_ढाँचा, num_mb);
		अगर (mode > 400 && mode < 500) अवरोध;
		fallthrough;
	हाल 499:
		अवरोध;

	हाल 500:
		test_acipher_speed("ecb(aes)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("ecb(aes)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("cbc(aes)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("cbc(aes)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("lrw(aes)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_40_48);
		test_acipher_speed("lrw(aes)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_40_48);
		test_acipher_speed("xts(aes)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_64);
		test_acipher_speed("xts(aes)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_64);
		test_acipher_speed("cts(cbc(aes))", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("cts(cbc(aes))", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("ctr(aes)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("ctr(aes)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("cfb(aes)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("cfb(aes)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("ofb(aes)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("ofb(aes)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("rfc3686(ctr(aes))", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_20_28_36);
		test_acipher_speed("rfc3686(ctr(aes))", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_20_28_36);
		अवरोध;

	हाल 501:
		test_acipher_speed("ecb(des3_ede)", ENCRYPT, sec,
				   des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				   speed_ढाँचा_24);
		test_acipher_speed("ecb(des3_ede)", DECRYPT, sec,
				   des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				   speed_ढाँचा_24);
		test_acipher_speed("cbc(des3_ede)", ENCRYPT, sec,
				   des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				   speed_ढाँचा_24);
		test_acipher_speed("cbc(des3_ede)", DECRYPT, sec,
				   des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				   speed_ढाँचा_24);
		test_acipher_speed("cfb(des3_ede)", ENCRYPT, sec,
				   des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				   speed_ढाँचा_24);
		test_acipher_speed("cfb(des3_ede)", DECRYPT, sec,
				   des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				   speed_ढाँचा_24);
		test_acipher_speed("ofb(des3_ede)", ENCRYPT, sec,
				   des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				   speed_ढाँचा_24);
		test_acipher_speed("ofb(des3_ede)", DECRYPT, sec,
				   des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				   speed_ढाँचा_24);
		अवरोध;

	हाल 502:
		test_acipher_speed("ecb(des)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8);
		test_acipher_speed("ecb(des)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8);
		test_acipher_speed("cbc(des)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8);
		test_acipher_speed("cbc(des)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8);
		test_acipher_speed("cfb(des)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8);
		test_acipher_speed("cfb(des)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8);
		test_acipher_speed("ofb(des)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8);
		test_acipher_speed("ofb(des)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8);
		अवरोध;

	हाल 503:
		test_acipher_speed("ecb(serpent)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("ecb(serpent)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("cbc(serpent)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("cbc(serpent)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("ctr(serpent)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("ctr(serpent)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("lrw(serpent)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_48);
		test_acipher_speed("lrw(serpent)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_48);
		test_acipher_speed("xts(serpent)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_64);
		test_acipher_speed("xts(serpent)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_64);
		अवरोध;

	हाल 504:
		test_acipher_speed("ecb(twofish)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("ecb(twofish)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("cbc(twofish)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("cbc(twofish)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("ctr(twofish)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("ctr(twofish)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_24_32);
		test_acipher_speed("lrw(twofish)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_40_48);
		test_acipher_speed("lrw(twofish)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_40_48);
		test_acipher_speed("xts(twofish)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_48_64);
		test_acipher_speed("xts(twofish)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_48_64);
		अवरोध;

	हाल 505:
		test_acipher_speed("ecb(arc4)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8);
		अवरोध;

	हाल 506:
		test_acipher_speed("ecb(cast5)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_16);
		test_acipher_speed("ecb(cast5)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_16);
		test_acipher_speed("cbc(cast5)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_16);
		test_acipher_speed("cbc(cast5)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_16);
		test_acipher_speed("ctr(cast5)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_16);
		test_acipher_speed("ctr(cast5)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_16);
		अवरोध;

	हाल 507:
		test_acipher_speed("ecb(cast6)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("ecb(cast6)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("cbc(cast6)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("cbc(cast6)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("ctr(cast6)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("ctr(cast6)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("lrw(cast6)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_48);
		test_acipher_speed("lrw(cast6)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_48);
		test_acipher_speed("xts(cast6)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_64);
		test_acipher_speed("xts(cast6)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_64);
		अवरोध;

	हाल 508:
		test_acipher_speed("ecb(camellia)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("ecb(camellia)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("cbc(camellia)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("cbc(camellia)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("ctr(camellia)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("ctr(camellia)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_16_32);
		test_acipher_speed("lrw(camellia)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_48);
		test_acipher_speed("lrw(camellia)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_48);
		test_acipher_speed("xts(camellia)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_64);
		test_acipher_speed("xts(camellia)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_32_64);
		अवरोध;

	हाल 509:
		test_acipher_speed("ecb(blowfish)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_32);
		test_acipher_speed("ecb(blowfish)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_32);
		test_acipher_speed("cbc(blowfish)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_32);
		test_acipher_speed("cbc(blowfish)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_32);
		test_acipher_speed("ctr(blowfish)", ENCRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_32);
		test_acipher_speed("ctr(blowfish)", DECRYPT, sec, शून्य, 0,
				   speed_ढाँचा_8_32);
		अवरोध;

	हाल 600:
		test_mb_skcipher_speed("ecb(aes)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("ecb(aes)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("cbc(aes)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("cbc(aes)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("lrw(aes)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_40_48, num_mb);
		test_mb_skcipher_speed("lrw(aes)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_40_48, num_mb);
		test_mb_skcipher_speed("xts(aes)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_64, num_mb);
		test_mb_skcipher_speed("xts(aes)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_64, num_mb);
		test_mb_skcipher_speed("cts(cbc(aes))", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("cts(cbc(aes))", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("ctr(aes)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("ctr(aes)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("cfb(aes)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("cfb(aes)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("ofb(aes)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("ofb(aes)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("rfc3686(ctr(aes))", ENCRYPT, sec, शून्य,
				       0, speed_ढाँचा_20_28_36, num_mb);
		test_mb_skcipher_speed("rfc3686(ctr(aes))", DECRYPT, sec, शून्य,
				       0, speed_ढाँचा_20_28_36, num_mb);
		अवरोध;

	हाल 601:
		test_mb_skcipher_speed("ecb(des3_ede)", ENCRYPT, sec,
				       des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				       speed_ढाँचा_24, num_mb);
		test_mb_skcipher_speed("ecb(des3_ede)", DECRYPT, sec,
				       des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				       speed_ढाँचा_24, num_mb);
		test_mb_skcipher_speed("cbc(des3_ede)", ENCRYPT, sec,
				       des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				       speed_ढाँचा_24, num_mb);
		test_mb_skcipher_speed("cbc(des3_ede)", DECRYPT, sec,
				       des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				       speed_ढाँचा_24, num_mb);
		test_mb_skcipher_speed("cfb(des3_ede)", ENCRYPT, sec,
				       des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				       speed_ढाँचा_24, num_mb);
		test_mb_skcipher_speed("cfb(des3_ede)", DECRYPT, sec,
				       des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				       speed_ढाँचा_24, num_mb);
		test_mb_skcipher_speed("ofb(des3_ede)", ENCRYPT, sec,
				       des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				       speed_ढाँचा_24, num_mb);
		test_mb_skcipher_speed("ofb(des3_ede)", DECRYPT, sec,
				       des3_speed_ढाँचा, DES3_SPEED_VECTORS,
				       speed_ढाँचा_24, num_mb);
		अवरोध;

	हाल 602:
		test_mb_skcipher_speed("ecb(des)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8, num_mb);
		test_mb_skcipher_speed("ecb(des)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8, num_mb);
		test_mb_skcipher_speed("cbc(des)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8, num_mb);
		test_mb_skcipher_speed("cbc(des)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8, num_mb);
		test_mb_skcipher_speed("cfb(des)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8, num_mb);
		test_mb_skcipher_speed("cfb(des)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8, num_mb);
		test_mb_skcipher_speed("ofb(des)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8, num_mb);
		test_mb_skcipher_speed("ofb(des)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8, num_mb);
		अवरोध;

	हाल 603:
		test_mb_skcipher_speed("ecb(serpent)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("ecb(serpent)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("cbc(serpent)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("cbc(serpent)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("ctr(serpent)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("ctr(serpent)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("lrw(serpent)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_48, num_mb);
		test_mb_skcipher_speed("lrw(serpent)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_48, num_mb);
		test_mb_skcipher_speed("xts(serpent)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_64, num_mb);
		test_mb_skcipher_speed("xts(serpent)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_64, num_mb);
		अवरोध;

	हाल 604:
		test_mb_skcipher_speed("ecb(twofish)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("ecb(twofish)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("cbc(twofish)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("cbc(twofish)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("ctr(twofish)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("ctr(twofish)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_24_32, num_mb);
		test_mb_skcipher_speed("lrw(twofish)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_40_48, num_mb);
		test_mb_skcipher_speed("lrw(twofish)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_40_48, num_mb);
		test_mb_skcipher_speed("xts(twofish)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_48_64, num_mb);
		test_mb_skcipher_speed("xts(twofish)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_48_64, num_mb);
		अवरोध;

	हाल 605:
		test_mb_skcipher_speed("ecb(arc4)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8, num_mb);
		अवरोध;

	हाल 606:
		test_mb_skcipher_speed("ecb(cast5)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_16, num_mb);
		test_mb_skcipher_speed("ecb(cast5)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_16, num_mb);
		test_mb_skcipher_speed("cbc(cast5)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_16, num_mb);
		test_mb_skcipher_speed("cbc(cast5)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_16, num_mb);
		test_mb_skcipher_speed("ctr(cast5)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_16, num_mb);
		test_mb_skcipher_speed("ctr(cast5)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_16, num_mb);
		अवरोध;

	हाल 607:
		test_mb_skcipher_speed("ecb(cast6)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("ecb(cast6)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("cbc(cast6)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("cbc(cast6)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("ctr(cast6)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("ctr(cast6)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("lrw(cast6)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_48, num_mb);
		test_mb_skcipher_speed("lrw(cast6)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_48, num_mb);
		test_mb_skcipher_speed("xts(cast6)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_64, num_mb);
		test_mb_skcipher_speed("xts(cast6)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_64, num_mb);
		अवरोध;

	हाल 608:
		test_mb_skcipher_speed("ecb(camellia)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("ecb(camellia)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("cbc(camellia)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("cbc(camellia)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("ctr(camellia)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("ctr(camellia)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_16_32, num_mb);
		test_mb_skcipher_speed("lrw(camellia)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_48, num_mb);
		test_mb_skcipher_speed("lrw(camellia)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_48, num_mb);
		test_mb_skcipher_speed("xts(camellia)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_64, num_mb);
		test_mb_skcipher_speed("xts(camellia)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_32_64, num_mb);
		अवरोध;

	हाल 609:
		test_mb_skcipher_speed("ecb(blowfish)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_32, num_mb);
		test_mb_skcipher_speed("ecb(blowfish)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_32, num_mb);
		test_mb_skcipher_speed("cbc(blowfish)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_32, num_mb);
		test_mb_skcipher_speed("cbc(blowfish)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_32, num_mb);
		test_mb_skcipher_speed("ctr(blowfish)", ENCRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_32, num_mb);
		test_mb_skcipher_speed("ctr(blowfish)", DECRYPT, sec, शून्य, 0,
				       speed_ढाँचा_8_32, num_mb);
		अवरोध;

	हाल 1000:
		test_available();
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init tcrypt_mod_init(व्योम)
अणु
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	क्रम (i = 0; i < TVMEMSIZE; i++) अणु
		tvmem[i] = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
		अगर (!tvmem[i])
			जाओ err_मुक्त_tv;
	पूर्ण

	err = करो_test(alg, type, mask, mode, num_mb);

	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "tcrypt: one or more tests failed!\n");
		जाओ err_मुक्त_tv;
	पूर्ण अन्यथा अणु
		pr_debug("all tests passed\n");
	पूर्ण

	/* We पूर्णांकentionaly वापस -EAGAIN to prevent keeping the module,
	 * unless we're running in fips mode. It करोes all its work from
	 * init() and करोesn't offer any runसमय functionality, but in
	 * the fips हाल, checking क्रम a successful load is helpful.
	 * => we करोn't need it in the memory, करो we?
	 *                                        -- mludvig
	 */
	अगर (!fips_enabled)
		err = -EAGAIN;

err_मुक्त_tv:
	क्रम (i = 0; i < TVMEMSIZE && tvmem[i]; i++)
		मुक्त_page((अचिन्हित दीर्घ)tvmem[i]);

	वापस err;
पूर्ण

/*
 * If an init function is provided, an निकास function must also be provided
 * to allow module unload.
 */
अटल व्योम __निकास tcrypt_mod_fini(व्योम) अणु पूर्ण

late_initcall(tcrypt_mod_init);
module_निकास(tcrypt_mod_fini);

module_param(alg, अक्षरp, 0);
module_param(type, uपूर्णांक, 0);
module_param(mask, uपूर्णांक, 0);
module_param(mode, पूर्णांक, 0);
module_param(sec, uपूर्णांक, 0);
MODULE_PARM_DESC(sec, "Length in seconds of speed tests "
		      "(defaults to zero which uses CPU cycles instead)");
module_param(num_mb, uपूर्णांक, 0000);
MODULE_PARM_DESC(num_mb, "Number of concurrent requests to be used in mb speed tests (defaults to 8)");
module_param(klen, uपूर्णांक, 0);
MODULE_PARM_DESC(klen, "Key length (defaults to 0)");

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Quick & dirty crypto testing module");
MODULE_AUTHOR("James Morris <jmorris@intercode.com.au>");
