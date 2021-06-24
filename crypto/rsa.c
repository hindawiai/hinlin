<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* RSA asymmetric खुला-key algorithm [RFC3447]
 *
 * Copyright (c) 2015, Intel Corporation
 * Authors: Tadeusz Struk <tadeusz.struk@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mpi.h>
#समावेश <crypto/पूर्णांकernal/rsa.h>
#समावेश <crypto/पूर्णांकernal/akcipher.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/algapi.h>

काष्ठा rsa_mpi_key अणु
	MPI n;
	MPI e;
	MPI d;
पूर्ण;

/*
 * RSAEP function [RFC3447 sec 5.1.1]
 * c = m^e mod n;
 */
अटल पूर्णांक _rsa_enc(स्थिर काष्ठा rsa_mpi_key *key, MPI c, MPI m)
अणु
	/* (1) Validate 0 <= m < n */
	अगर (mpi_cmp_ui(m, 0) < 0 || mpi_cmp(m, key->n) >= 0)
		वापस -EINVAL;

	/* (2) c = m^e mod n */
	वापस mpi_घातm(c, m, key->e, key->n);
पूर्ण

/*
 * RSADP function [RFC3447 sec 5.1.2]
 * m = c^d mod n;
 */
अटल पूर्णांक _rsa_dec(स्थिर काष्ठा rsa_mpi_key *key, MPI m, MPI c)
अणु
	/* (1) Validate 0 <= c < n */
	अगर (mpi_cmp_ui(c, 0) < 0 || mpi_cmp(c, key->n) >= 0)
		वापस -EINVAL;

	/* (2) m = c^d mod n */
	वापस mpi_घातm(m, c, key->d, key->n);
पूर्ण

अटल अंतरभूत काष्ठा rsa_mpi_key *rsa_get_key(काष्ठा crypto_akcipher *tfm)
अणु
	वापस akcipher_tfm_ctx(tfm);
पूर्ण

अटल पूर्णांक rsa_enc(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	स्थिर काष्ठा rsa_mpi_key *pkey = rsa_get_key(tfm);
	MPI m, c = mpi_alloc(0);
	पूर्णांक ret = 0;
	पूर्णांक sign;

	अगर (!c)
		वापस -ENOMEM;

	अगर (unlikely(!pkey->n || !pkey->e)) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_c;
	पूर्ण

	ret = -ENOMEM;
	m = mpi_पढ़ो_raw_from_sgl(req->src, req->src_len);
	अगर (!m)
		जाओ err_मुक्त_c;

	ret = _rsa_enc(pkey, c, m);
	अगर (ret)
		जाओ err_मुक्त_m;

	ret = mpi_ग_लिखो_to_sgl(c, req->dst, req->dst_len, &sign);
	अगर (ret)
		जाओ err_मुक्त_m;

	अगर (sign < 0)
		ret = -EBADMSG;

err_मुक्त_m:
	mpi_मुक्त(m);
err_मुक्त_c:
	mpi_मुक्त(c);
	वापस ret;
पूर्ण

अटल पूर्णांक rsa_dec(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	स्थिर काष्ठा rsa_mpi_key *pkey = rsa_get_key(tfm);
	MPI c, m = mpi_alloc(0);
	पूर्णांक ret = 0;
	पूर्णांक sign;

	अगर (!m)
		वापस -ENOMEM;

	अगर (unlikely(!pkey->n || !pkey->d)) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_m;
	पूर्ण

	ret = -ENOMEM;
	c = mpi_पढ़ो_raw_from_sgl(req->src, req->src_len);
	अगर (!c)
		जाओ err_मुक्त_m;

	ret = _rsa_dec(pkey, m, c);
	अगर (ret)
		जाओ err_मुक्त_c;

	ret = mpi_ग_लिखो_to_sgl(m, req->dst, req->dst_len, &sign);
	अगर (ret)
		जाओ err_मुक्त_c;

	अगर (sign < 0)
		ret = -EBADMSG;
err_मुक्त_c:
	mpi_मुक्त(c);
err_मुक्त_m:
	mpi_मुक्त(m);
	वापस ret;
पूर्ण

अटल व्योम rsa_मुक्त_mpi_key(काष्ठा rsa_mpi_key *key)
अणु
	mpi_मुक्त(key->d);
	mpi_मुक्त(key->e);
	mpi_मुक्त(key->n);
	key->d = शून्य;
	key->e = शून्य;
	key->n = शून्य;
पूर्ण

अटल पूर्णांक rsa_check_key_length(अचिन्हित पूर्णांक len)
अणु
	चयन (len) अणु
	हाल 512:
	हाल 1024:
	हाल 1536:
	हाल 2048:
	हाल 3072:
	हाल 4096:
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rsa_set_pub_key(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा rsa_mpi_key *mpi_key = akcipher_tfm_ctx(tfm);
	काष्ठा rsa_key raw_key = अणु0पूर्ण;
	पूर्णांक ret;

	/* Free the old MPI key अगर any */
	rsa_मुक्त_mpi_key(mpi_key);

	ret = rsa_parse_pub_key(&raw_key, key, keylen);
	अगर (ret)
		वापस ret;

	mpi_key->e = mpi_पढ़ो_raw_data(raw_key.e, raw_key.e_sz);
	अगर (!mpi_key->e)
		जाओ err;

	mpi_key->n = mpi_पढ़ो_raw_data(raw_key.n, raw_key.n_sz);
	अगर (!mpi_key->n)
		जाओ err;

	अगर (rsa_check_key_length(mpi_get_size(mpi_key->n) << 3)) अणु
		rsa_मुक्त_mpi_key(mpi_key);
		वापस -EINVAL;
	पूर्ण

	वापस 0;

err:
	rsa_मुक्त_mpi_key(mpi_key);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक rsa_set_priv_key(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा rsa_mpi_key *mpi_key = akcipher_tfm_ctx(tfm);
	काष्ठा rsa_key raw_key = अणु0पूर्ण;
	पूर्णांक ret;

	/* Free the old MPI key अगर any */
	rsa_मुक्त_mpi_key(mpi_key);

	ret = rsa_parse_priv_key(&raw_key, key, keylen);
	अगर (ret)
		वापस ret;

	mpi_key->d = mpi_पढ़ो_raw_data(raw_key.d, raw_key.d_sz);
	अगर (!mpi_key->d)
		जाओ err;

	mpi_key->e = mpi_पढ़ो_raw_data(raw_key.e, raw_key.e_sz);
	अगर (!mpi_key->e)
		जाओ err;

	mpi_key->n = mpi_पढ़ो_raw_data(raw_key.n, raw_key.n_sz);
	अगर (!mpi_key->n)
		जाओ err;

	अगर (rsa_check_key_length(mpi_get_size(mpi_key->n) << 3)) अणु
		rsa_मुक्त_mpi_key(mpi_key);
		वापस -EINVAL;
	पूर्ण

	वापस 0;

err:
	rsa_मुक्त_mpi_key(mpi_key);
	वापस -ENOMEM;
पूर्ण

अटल अचिन्हित पूर्णांक rsa_max_size(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा rsa_mpi_key *pkey = akcipher_tfm_ctx(tfm);

	वापस mpi_get_size(pkey->n);
पूर्ण

अटल व्योम rsa_निकास_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा rsa_mpi_key *pkey = akcipher_tfm_ctx(tfm);

	rsa_मुक्त_mpi_key(pkey);
पूर्ण

अटल काष्ठा akcipher_alg rsa = अणु
	.encrypt = rsa_enc,
	.decrypt = rsa_dec,
	.set_priv_key = rsa_set_priv_key,
	.set_pub_key = rsa_set_pub_key,
	.max_size = rsa_max_size,
	.निकास = rsa_निकास_tfm,
	.base = अणु
		.cra_name = "rsa",
		.cra_driver_name = "rsa-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = माप(काष्ठा rsa_mpi_key),
	पूर्ण,
पूर्ण;

अटल पूर्णांक rsa_init(व्योम)
अणु
	पूर्णांक err;

	err = crypto_रेजिस्टर_akcipher(&rsa);
	अगर (err)
		वापस err;

	err = crypto_रेजिस्टर_ढाँचा(&rsa_pkcs1pad_पंचांगpl);
	अगर (err) अणु
		crypto_unरेजिस्टर_akcipher(&rsa);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rsa_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&rsa_pkcs1pad_पंचांगpl);
	crypto_unरेजिस्टर_akcipher(&rsa);
पूर्ण

subsys_initcall(rsa_init);
module_निकास(rsa_निकास);
MODULE_ALIAS_CRYPTO("rsa");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("RSA generic algorithm");
