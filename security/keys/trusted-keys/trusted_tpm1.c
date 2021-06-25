<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 IBM Corporation
 * Copyright (c) 2019-2021, Linaro Limited
 *
 * See Documentation/security/keys/trusted-encrypted.rst
 */

#समावेश <crypto/hash_info.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/parser.h>
#समावेश <linux/माला.स>
#समावेश <linux/err.h>
#समावेश <keys/trusted-type.h>
#समावेश <linux/key-type.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <linux/tpm.h>
#समावेश <linux/tpm_command.h>

#समावेश <keys/trusted_tpm.h>

अटल स्थिर अक्षर hmac_alg[] = "hmac(sha1)";
अटल स्थिर अक्षर hash_alg[] = "sha1";
अटल काष्ठा tpm_chip *chip;
अटल काष्ठा tpm_digest *digests;

काष्ठा sdesc अणु
	काष्ठा shash_desc shash;
	अक्षर ctx[];
पूर्ण;

अटल काष्ठा crypto_shash *hashalg;
अटल काष्ठा crypto_shash *hmacalg;

अटल काष्ठा sdesc *init_sdesc(काष्ठा crypto_shash *alg)
अणु
	काष्ठा sdesc *sdesc;
	पूर्णांक size;

	size = माप(काष्ठा shash_desc) + crypto_shash_descsize(alg);
	sdesc = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!sdesc)
		वापस ERR_PTR(-ENOMEM);
	sdesc->shash.tfm = alg;
	वापस sdesc;
पूर्ण

अटल पूर्णांक TSS_sha1(स्थिर अचिन्हित अक्षर *data, अचिन्हित पूर्णांक datalen,
		    अचिन्हित अक्षर *digest)
अणु
	काष्ठा sdesc *sdesc;
	पूर्णांक ret;

	sdesc = init_sdesc(hashalg);
	अगर (IS_ERR(sdesc)) अणु
		pr_info("can't alloc %s\n", hash_alg);
		वापस PTR_ERR(sdesc);
	पूर्ण

	ret = crypto_shash_digest(&sdesc->shash, data, datalen, digest);
	kमुक्त_sensitive(sdesc);
	वापस ret;
पूर्ण

अटल पूर्णांक TSS_rawhmac(अचिन्हित अक्षर *digest, स्थिर अचिन्हित अक्षर *key,
		       अचिन्हित पूर्णांक keylen, ...)
अणु
	काष्ठा sdesc *sdesc;
	बहु_सूची argp;
	अचिन्हित पूर्णांक dlen;
	अचिन्हित अक्षर *data;
	पूर्णांक ret;

	sdesc = init_sdesc(hmacalg);
	अगर (IS_ERR(sdesc)) अणु
		pr_info("can't alloc %s\n", hmac_alg);
		वापस PTR_ERR(sdesc);
	पूर्ण

	ret = crypto_shash_setkey(hmacalg, key, keylen);
	अगर (ret < 0)
		जाओ out;
	ret = crypto_shash_init(&sdesc->shash);
	अगर (ret < 0)
		जाओ out;

	बहु_शुरू(argp, keylen);
	क्रम (;;) अणु
		dlen = बहु_तर्क(argp, अचिन्हित पूर्णांक);
		अगर (dlen == 0)
			अवरोध;
		data = बहु_तर्क(argp, अचिन्हित अक्षर *);
		अगर (data == शून्य) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = crypto_shash_update(&sdesc->shash, data, dlen);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	बहु_पूर्ण(argp);
	अगर (!ret)
		ret = crypto_shash_final(&sdesc->shash, digest);
out:
	kमुक्त_sensitive(sdesc);
	वापस ret;
पूर्ण

/*
 * calculate authorization info fields to send to TPM
 */
पूर्णांक TSS_authhmac(अचिन्हित अक्षर *digest, स्थिर अचिन्हित अक्षर *key,
			अचिन्हित पूर्णांक keylen, अचिन्हित अक्षर *h1,
			अचिन्हित अक्षर *h2, अचिन्हित पूर्णांक h3, ...)
अणु
	अचिन्हित अक्षर paramdigest[SHA1_DIGEST_SIZE];
	काष्ठा sdesc *sdesc;
	अचिन्हित पूर्णांक dlen;
	अचिन्हित अक्षर *data;
	अचिन्हित अक्षर c;
	पूर्णांक ret;
	बहु_सूची argp;

	अगर (!chip)
		वापस -ENODEV;

	sdesc = init_sdesc(hashalg);
	अगर (IS_ERR(sdesc)) अणु
		pr_info("can't alloc %s\n", hash_alg);
		वापस PTR_ERR(sdesc);
	पूर्ण

	c = !!h3;
	ret = crypto_shash_init(&sdesc->shash);
	अगर (ret < 0)
		जाओ out;
	बहु_शुरू(argp, h3);
	क्रम (;;) अणु
		dlen = बहु_तर्क(argp, अचिन्हित पूर्णांक);
		अगर (dlen == 0)
			अवरोध;
		data = बहु_तर्क(argp, अचिन्हित अक्षर *);
		अगर (!data) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = crypto_shash_update(&sdesc->shash, data, dlen);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	बहु_पूर्ण(argp);
	अगर (!ret)
		ret = crypto_shash_final(&sdesc->shash, paramdigest);
	अगर (!ret)
		ret = TSS_rawhmac(digest, key, keylen, SHA1_DIGEST_SIZE,
				  paramdigest, TPM_NONCE_SIZE, h1,
				  TPM_NONCE_SIZE, h2, 1, &c, 0, 0);
out:
	kमुक्त_sensitive(sdesc);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(TSS_authhmac);

/*
 * verअगरy the AUTH1_COMMAND (Seal) result from TPM
 */
पूर्णांक TSS_checkhmac1(अचिन्हित अक्षर *buffer,
			  स्थिर uपूर्णांक32_t command,
			  स्थिर अचिन्हित अक्षर *ononce,
			  स्थिर अचिन्हित अक्षर *key,
			  अचिन्हित पूर्णांक keylen, ...)
अणु
	uपूर्णांक32_t bufsize;
	uपूर्णांक16_t tag;
	uपूर्णांक32_t ordinal;
	uपूर्णांक32_t result;
	अचिन्हित अक्षर *enonce;
	अचिन्हित अक्षर *जारीflag;
	अचिन्हित अक्षर *authdata;
	अचिन्हित अक्षर testhmac[SHA1_DIGEST_SIZE];
	अचिन्हित अक्षर paramdigest[SHA1_DIGEST_SIZE];
	काष्ठा sdesc *sdesc;
	अचिन्हित पूर्णांक dlen;
	अचिन्हित पूर्णांक dpos;
	बहु_सूची argp;
	पूर्णांक ret;

	अगर (!chip)
		वापस -ENODEV;

	bufsize = LOAD32(buffer, TPM_SIZE_OFFSET);
	tag = LOAD16(buffer, 0);
	ordinal = command;
	result = LOAD32N(buffer, TPM_RETURN_OFFSET);
	अगर (tag == TPM_TAG_RSP_COMMAND)
		वापस 0;
	अगर (tag != TPM_TAG_RSP_AUTH1_COMMAND)
		वापस -EINVAL;
	authdata = buffer + bufsize - SHA1_DIGEST_SIZE;
	जारीflag = authdata - 1;
	enonce = जारीflag - TPM_NONCE_SIZE;

	sdesc = init_sdesc(hashalg);
	अगर (IS_ERR(sdesc)) अणु
		pr_info("can't alloc %s\n", hash_alg);
		वापस PTR_ERR(sdesc);
	पूर्ण
	ret = crypto_shash_init(&sdesc->shash);
	अगर (ret < 0)
		जाओ out;
	ret = crypto_shash_update(&sdesc->shash, (स्थिर u8 *)&result,
				  माप result);
	अगर (ret < 0)
		जाओ out;
	ret = crypto_shash_update(&sdesc->shash, (स्थिर u8 *)&ordinal,
				  माप ordinal);
	अगर (ret < 0)
		जाओ out;
	बहु_शुरू(argp, keylen);
	क्रम (;;) अणु
		dlen = बहु_तर्क(argp, अचिन्हित पूर्णांक);
		अगर (dlen == 0)
			अवरोध;
		dpos = बहु_तर्क(argp, अचिन्हित पूर्णांक);
		ret = crypto_shash_update(&sdesc->shash, buffer + dpos, dlen);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	बहु_पूर्ण(argp);
	अगर (!ret)
		ret = crypto_shash_final(&sdesc->shash, paramdigest);
	अगर (ret < 0)
		जाओ out;

	ret = TSS_rawhmac(testhmac, key, keylen, SHA1_DIGEST_SIZE, paramdigest,
			  TPM_NONCE_SIZE, enonce, TPM_NONCE_SIZE, ononce,
			  1, जारीflag, 0, 0);
	अगर (ret < 0)
		जाओ out;

	अगर (स_भेद(testhmac, authdata, SHA1_DIGEST_SIZE))
		ret = -EINVAL;
out:
	kमुक्त_sensitive(sdesc);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(TSS_checkhmac1);

/*
 * verअगरy the AUTH2_COMMAND (unseal) result from TPM
 */
अटल पूर्णांक TSS_checkhmac2(अचिन्हित अक्षर *buffer,
			  स्थिर uपूर्णांक32_t command,
			  स्थिर अचिन्हित अक्षर *ononce,
			  स्थिर अचिन्हित अक्षर *key1,
			  अचिन्हित पूर्णांक keylen1,
			  स्थिर अचिन्हित अक्षर *key2,
			  अचिन्हित पूर्णांक keylen2, ...)
अणु
	uपूर्णांक32_t bufsize;
	uपूर्णांक16_t tag;
	uपूर्णांक32_t ordinal;
	uपूर्णांक32_t result;
	अचिन्हित अक्षर *enonce1;
	अचिन्हित अक्षर *जारीflag1;
	अचिन्हित अक्षर *authdata1;
	अचिन्हित अक्षर *enonce2;
	अचिन्हित अक्षर *जारीflag2;
	अचिन्हित अक्षर *authdata2;
	अचिन्हित अक्षर testhmac1[SHA1_DIGEST_SIZE];
	अचिन्हित अक्षर testhmac2[SHA1_DIGEST_SIZE];
	अचिन्हित अक्षर paramdigest[SHA1_DIGEST_SIZE];
	काष्ठा sdesc *sdesc;
	अचिन्हित पूर्णांक dlen;
	अचिन्हित पूर्णांक dpos;
	बहु_सूची argp;
	पूर्णांक ret;

	bufsize = LOAD32(buffer, TPM_SIZE_OFFSET);
	tag = LOAD16(buffer, 0);
	ordinal = command;
	result = LOAD32N(buffer, TPM_RETURN_OFFSET);

	अगर (tag == TPM_TAG_RSP_COMMAND)
		वापस 0;
	अगर (tag != TPM_TAG_RSP_AUTH2_COMMAND)
		वापस -EINVAL;
	authdata1 = buffer + bufsize - (SHA1_DIGEST_SIZE + 1
			+ SHA1_DIGEST_SIZE + SHA1_DIGEST_SIZE);
	authdata2 = buffer + bufsize - (SHA1_DIGEST_SIZE);
	जारीflag1 = authdata1 - 1;
	जारीflag2 = authdata2 - 1;
	enonce1 = जारीflag1 - TPM_NONCE_SIZE;
	enonce2 = जारीflag2 - TPM_NONCE_SIZE;

	sdesc = init_sdesc(hashalg);
	अगर (IS_ERR(sdesc)) अणु
		pr_info("can't alloc %s\n", hash_alg);
		वापस PTR_ERR(sdesc);
	पूर्ण
	ret = crypto_shash_init(&sdesc->shash);
	अगर (ret < 0)
		जाओ out;
	ret = crypto_shash_update(&sdesc->shash, (स्थिर u8 *)&result,
				  माप result);
	अगर (ret < 0)
		जाओ out;
	ret = crypto_shash_update(&sdesc->shash, (स्थिर u8 *)&ordinal,
				  माप ordinal);
	अगर (ret < 0)
		जाओ out;

	बहु_शुरू(argp, keylen2);
	क्रम (;;) अणु
		dlen = बहु_तर्क(argp, अचिन्हित पूर्णांक);
		अगर (dlen == 0)
			अवरोध;
		dpos = बहु_तर्क(argp, अचिन्हित पूर्णांक);
		ret = crypto_shash_update(&sdesc->shash, buffer + dpos, dlen);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	बहु_पूर्ण(argp);
	अगर (!ret)
		ret = crypto_shash_final(&sdesc->shash, paramdigest);
	अगर (ret < 0)
		जाओ out;

	ret = TSS_rawhmac(testhmac1, key1, keylen1, SHA1_DIGEST_SIZE,
			  paramdigest, TPM_NONCE_SIZE, enonce1,
			  TPM_NONCE_SIZE, ononce, 1, जारीflag1, 0, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (स_भेद(testhmac1, authdata1, SHA1_DIGEST_SIZE)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = TSS_rawhmac(testhmac2, key2, keylen2, SHA1_DIGEST_SIZE,
			  paramdigest, TPM_NONCE_SIZE, enonce2,
			  TPM_NONCE_SIZE, ononce, 1, जारीflag2, 0, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (स_भेद(testhmac2, authdata2, SHA1_DIGEST_SIZE))
		ret = -EINVAL;
out:
	kमुक्त_sensitive(sdesc);
	वापस ret;
पूर्ण

/*
 * For key specअगरic tpm requests, we will generate and send our
 * own TPM command packets using the drivers send function.
 */
पूर्णांक trusted_tpm_send(अचिन्हित अक्षर *cmd, माप_प्रकार buflen)
अणु
	पूर्णांक rc;

	अगर (!chip)
		वापस -ENODEV;

	dump_tpm_buf(cmd);
	rc = tpm_send(chip, cmd, buflen);
	dump_tpm_buf(cmd);
	अगर (rc > 0)
		/* Can't वापस positive वापस codes values to keyctl */
		rc = -EPERM;
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(trusted_tpm_send);

/*
 * Lock a trusted key, by extending a selected PCR.
 *
 * Prevents a trusted key that is sealed to PCRs from being accessed.
 * This uses the tpm driver's extend function.
 */
अटल पूर्णांक pcrlock(स्थिर पूर्णांक pcrnum)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	वापस tpm_pcr_extend(chip, pcrnum, digests) ? -EINVAL : 0;
पूर्ण

/*
 * Create an object specअगरic authorisation protocol (OSAP) session
 */
अटल पूर्णांक osap(काष्ठा tpm_buf *tb, काष्ठा osapsess *s,
		स्थिर अचिन्हित अक्षर *key, uपूर्णांक16_t type, uपूर्णांक32_t handle)
अणु
	अचिन्हित अक्षर enonce[TPM_NONCE_SIZE];
	अचिन्हित अक्षर ononce[TPM_NONCE_SIZE];
	पूर्णांक ret;

	ret = tpm_get_अक्रमom(chip, ononce, TPM_NONCE_SIZE);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != TPM_NONCE_SIZE)
		वापस -EIO;

	tpm_buf_reset(tb, TPM_TAG_RQU_COMMAND, TPM_ORD_OSAP);
	tpm_buf_append_u16(tb, type);
	tpm_buf_append_u32(tb, handle);
	tpm_buf_append(tb, ononce, TPM_NONCE_SIZE);

	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	अगर (ret < 0)
		वापस ret;

	s->handle = LOAD32(tb->data, TPM_DATA_OFFSET);
	स_नकल(s->enonce, &(tb->data[TPM_DATA_OFFSET + माप(uपूर्णांक32_t)]),
	       TPM_NONCE_SIZE);
	स_नकल(enonce, &(tb->data[TPM_DATA_OFFSET + माप(uपूर्णांक32_t) +
				  TPM_NONCE_SIZE]), TPM_NONCE_SIZE);
	वापस TSS_rawhmac(s->secret, key, SHA1_DIGEST_SIZE, TPM_NONCE_SIZE,
			   enonce, TPM_NONCE_SIZE, ononce, 0, 0);
पूर्ण

/*
 * Create an object independent authorisation protocol (oiap) session
 */
पूर्णांक oiap(काष्ठा tpm_buf *tb, uपूर्णांक32_t *handle, अचिन्हित अक्षर *nonce)
अणु
	पूर्णांक ret;

	अगर (!chip)
		वापस -ENODEV;

	tpm_buf_reset(tb, TPM_TAG_RQU_COMMAND, TPM_ORD_OIAP);
	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	अगर (ret < 0)
		वापस ret;

	*handle = LOAD32(tb->data, TPM_DATA_OFFSET);
	स_नकल(nonce, &tb->data[TPM_DATA_OFFSET + माप(uपूर्णांक32_t)],
	       TPM_NONCE_SIZE);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(oiap);

काष्ठा tpm_digests अणु
	अचिन्हित अक्षर encauth[SHA1_DIGEST_SIZE];
	अचिन्हित अक्षर pubauth[SHA1_DIGEST_SIZE];
	अचिन्हित अक्षर xorwork[SHA1_DIGEST_SIZE * 2];
	अचिन्हित अक्षर xorhash[SHA1_DIGEST_SIZE];
	अचिन्हित अक्षर nonceodd[TPM_NONCE_SIZE];
पूर्ण;

/*
 * Have the TPM seal(encrypt) the trusted key, possibly based on
 * Platक्रमm Configuration Registers (PCRs). AUTH1 क्रम sealing key.
 */
अटल पूर्णांक tpm_seal(काष्ठा tpm_buf *tb, uपूर्णांक16_t keytype,
		    uपूर्णांक32_t keyhandle, स्थिर अचिन्हित अक्षर *keyauth,
		    स्थिर अचिन्हित अक्षर *data, uपूर्णांक32_t datalen,
		    अचिन्हित अक्षर *blob, uपूर्णांक32_t *bloblen,
		    स्थिर अचिन्हित अक्षर *blobauth,
		    स्थिर अचिन्हित अक्षर *pcrinfo, uपूर्णांक32_t pcrinfosize)
अणु
	काष्ठा osapsess sess;
	काष्ठा tpm_digests *td;
	अचिन्हित अक्षर cont;
	uपूर्णांक32_t ordinal;
	uपूर्णांक32_t pcrsize;
	uपूर्णांक32_t datsize;
	पूर्णांक sealinfosize;
	पूर्णांक encdatasize;
	पूर्णांक storedsize;
	पूर्णांक ret;
	पूर्णांक i;

	/* alloc some work space क्रम all the hashes */
	td = kदो_स्मृति(माप *td, GFP_KERNEL);
	अगर (!td)
		वापस -ENOMEM;

	/* get session क्रम sealing key */
	ret = osap(tb, &sess, keyauth, keytype, keyhandle);
	अगर (ret < 0)
		जाओ out;
	dump_sess(&sess);

	/* calculate encrypted authorization value */
	स_नकल(td->xorwork, sess.secret, SHA1_DIGEST_SIZE);
	स_नकल(td->xorwork + SHA1_DIGEST_SIZE, sess.enonce, SHA1_DIGEST_SIZE);
	ret = TSS_sha1(td->xorwork, SHA1_DIGEST_SIZE * 2, td->xorhash);
	अगर (ret < 0)
		जाओ out;

	ret = tpm_get_अक्रमom(chip, td->nonceodd, TPM_NONCE_SIZE);
	अगर (ret < 0)
		जाओ out;

	अगर (ret != TPM_NONCE_SIZE) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	ordinal = htonl(TPM_ORD_SEAL);
	datsize = htonl(datalen);
	pcrsize = htonl(pcrinfosize);
	cont = 0;

	/* encrypt data authorization key */
	क्रम (i = 0; i < SHA1_DIGEST_SIZE; ++i)
		td->encauth[i] = td->xorhash[i] ^ blobauth[i];

	/* calculate authorization HMAC value */
	अगर (pcrinfosize == 0) अणु
		/* no pcr info specअगरied */
		ret = TSS_authhmac(td->pubauth, sess.secret, SHA1_DIGEST_SIZE,
				   sess.enonce, td->nonceodd, cont,
				   माप(uपूर्णांक32_t), &ordinal, SHA1_DIGEST_SIZE,
				   td->encauth, माप(uपूर्णांक32_t), &pcrsize,
				   माप(uपूर्णांक32_t), &datsize, datalen, data, 0,
				   0);
	पूर्ण अन्यथा अणु
		/* pcr info specअगरied */
		ret = TSS_authhmac(td->pubauth, sess.secret, SHA1_DIGEST_SIZE,
				   sess.enonce, td->nonceodd, cont,
				   माप(uपूर्णांक32_t), &ordinal, SHA1_DIGEST_SIZE,
				   td->encauth, माप(uपूर्णांक32_t), &pcrsize,
				   pcrinfosize, pcrinfo, माप(uपूर्णांक32_t),
				   &datsize, datalen, data, 0, 0);
	पूर्ण
	अगर (ret < 0)
		जाओ out;

	/* build and send the TPM request packet */
	tpm_buf_reset(tb, TPM_TAG_RQU_AUTH1_COMMAND, TPM_ORD_SEAL);
	tpm_buf_append_u32(tb, keyhandle);
	tpm_buf_append(tb, td->encauth, SHA1_DIGEST_SIZE);
	tpm_buf_append_u32(tb, pcrinfosize);
	tpm_buf_append(tb, pcrinfo, pcrinfosize);
	tpm_buf_append_u32(tb, datalen);
	tpm_buf_append(tb, data, datalen);
	tpm_buf_append_u32(tb, sess.handle);
	tpm_buf_append(tb, td->nonceodd, TPM_NONCE_SIZE);
	tpm_buf_append_u8(tb, cont);
	tpm_buf_append(tb, td->pubauth, SHA1_DIGEST_SIZE);

	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	अगर (ret < 0)
		जाओ out;

	/* calculate the size of the वापसed Blob */
	sealinfosize = LOAD32(tb->data, TPM_DATA_OFFSET + माप(uपूर्णांक32_t));
	encdatasize = LOAD32(tb->data, TPM_DATA_OFFSET + माप(uपूर्णांक32_t) +
			     माप(uपूर्णांक32_t) + sealinfosize);
	storedsize = माप(uपूर्णांक32_t) + माप(uपूर्णांक32_t) + sealinfosize +
	    माप(uपूर्णांक32_t) + encdatasize;

	/* check the HMAC in the response */
	ret = TSS_checkhmac1(tb->data, ordinal, td->nonceodd, sess.secret,
			     SHA1_DIGEST_SIZE, storedsize, TPM_DATA_OFFSET, 0,
			     0);

	/* copy the वापसed blob to caller */
	अगर (!ret) अणु
		स_नकल(blob, tb->data + TPM_DATA_OFFSET, storedsize);
		*bloblen = storedsize;
	पूर्ण
out:
	kमुक्त_sensitive(td);
	वापस ret;
पूर्ण

/*
 * use the AUTH2_COMMAND क्रमm of unseal, to authorize both key and blob
 */
अटल पूर्णांक tpm_unseal(काष्ठा tpm_buf *tb,
		      uपूर्णांक32_t keyhandle, स्थिर अचिन्हित अक्षर *keyauth,
		      स्थिर अचिन्हित अक्षर *blob, पूर्णांक bloblen,
		      स्थिर अचिन्हित अक्षर *blobauth,
		      अचिन्हित अक्षर *data, अचिन्हित पूर्णांक *datalen)
अणु
	अचिन्हित अक्षर nonceodd[TPM_NONCE_SIZE];
	अचिन्हित अक्षर enonce1[TPM_NONCE_SIZE];
	अचिन्हित अक्षर enonce2[TPM_NONCE_SIZE];
	अचिन्हित अक्षर authdata1[SHA1_DIGEST_SIZE];
	अचिन्हित अक्षर authdata2[SHA1_DIGEST_SIZE];
	uपूर्णांक32_t authhandle1 = 0;
	uपूर्णांक32_t authhandle2 = 0;
	अचिन्हित अक्षर cont = 0;
	uपूर्णांक32_t ordinal;
	पूर्णांक ret;

	/* sessions क्रम unsealing key and data */
	ret = oiap(tb, &authhandle1, enonce1);
	अगर (ret < 0) अणु
		pr_info("oiap failed (%d)\n", ret);
		वापस ret;
	पूर्ण
	ret = oiap(tb, &authhandle2, enonce2);
	अगर (ret < 0) अणु
		pr_info("oiap failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	ordinal = htonl(TPM_ORD_UNSEAL);
	ret = tpm_get_अक्रमom(chip, nonceodd, TPM_NONCE_SIZE);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != TPM_NONCE_SIZE) अणु
		pr_info("tpm_get_random failed (%d)\n", ret);
		वापस -EIO;
	पूर्ण
	ret = TSS_authhmac(authdata1, keyauth, TPM_NONCE_SIZE,
			   enonce1, nonceodd, cont, माप(uपूर्णांक32_t),
			   &ordinal, bloblen, blob, 0, 0);
	अगर (ret < 0)
		वापस ret;
	ret = TSS_authhmac(authdata2, blobauth, TPM_NONCE_SIZE,
			   enonce2, nonceodd, cont, माप(uपूर्णांक32_t),
			   &ordinal, bloblen, blob, 0, 0);
	अगर (ret < 0)
		वापस ret;

	/* build and send TPM request packet */
	tpm_buf_reset(tb, TPM_TAG_RQU_AUTH2_COMMAND, TPM_ORD_UNSEAL);
	tpm_buf_append_u32(tb, keyhandle);
	tpm_buf_append(tb, blob, bloblen);
	tpm_buf_append_u32(tb, authhandle1);
	tpm_buf_append(tb, nonceodd, TPM_NONCE_SIZE);
	tpm_buf_append_u8(tb, cont);
	tpm_buf_append(tb, authdata1, SHA1_DIGEST_SIZE);
	tpm_buf_append_u32(tb, authhandle2);
	tpm_buf_append(tb, nonceodd, TPM_NONCE_SIZE);
	tpm_buf_append_u8(tb, cont);
	tpm_buf_append(tb, authdata2, SHA1_DIGEST_SIZE);

	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	अगर (ret < 0) अणु
		pr_info("authhmac failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	*datalen = LOAD32(tb->data, TPM_DATA_OFFSET);
	ret = TSS_checkhmac2(tb->data, ordinal, nonceodd,
			     keyauth, SHA1_DIGEST_SIZE,
			     blobauth, SHA1_DIGEST_SIZE,
			     माप(uपूर्णांक32_t), TPM_DATA_OFFSET,
			     *datalen, TPM_DATA_OFFSET + माप(uपूर्णांक32_t), 0,
			     0);
	अगर (ret < 0) अणु
		pr_info("TSS_checkhmac2 failed (%d)\n", ret);
		वापस ret;
	पूर्ण
	स_नकल(data, tb->data + TPM_DATA_OFFSET + माप(uपूर्णांक32_t), *datalen);
	वापस 0;
पूर्ण

/*
 * Have the TPM seal(encrypt) the symmetric key
 */
अटल पूर्णांक key_seal(काष्ठा trusted_key_payload *p,
		    काष्ठा trusted_key_options *o)
अणु
	काष्ठा tpm_buf tb;
	पूर्णांक ret;

	ret = tpm_buf_init(&tb, 0, 0);
	अगर (ret)
		वापस ret;

	/* include migratable flag at end of sealed key */
	p->key[p->key_len] = p->migratable;

	ret = tpm_seal(&tb, o->keytype, o->keyhandle, o->keyauth,
		       p->key, p->key_len + 1, p->blob, &p->blob_len,
		       o->blobauth, o->pcrinfo, o->pcrinfo_len);
	अगर (ret < 0)
		pr_info("srkseal failed (%d)\n", ret);

	tpm_buf_destroy(&tb);
	वापस ret;
पूर्ण

/*
 * Have the TPM unseal(decrypt) the symmetric key
 */
अटल पूर्णांक key_unseal(काष्ठा trusted_key_payload *p,
		      काष्ठा trusted_key_options *o)
अणु
	काष्ठा tpm_buf tb;
	पूर्णांक ret;

	ret = tpm_buf_init(&tb, 0, 0);
	अगर (ret)
		वापस ret;

	ret = tpm_unseal(&tb, o->keyhandle, o->keyauth, p->blob, p->blob_len,
			 o->blobauth, p->key, &p->key_len);
	अगर (ret < 0)
		pr_info("srkunseal failed (%d)\n", ret);
	अन्यथा
		/* pull migratable flag out of sealed key */
		p->migratable = p->key[--p->key_len];

	tpm_buf_destroy(&tb);
	वापस ret;
पूर्ण

क्रमागत अणु
	Opt_err,
	Opt_keyhandle, Opt_keyauth, Opt_blobauth,
	Opt_pcrinfo, Opt_pcrlock, Opt_migratable,
	Opt_hash,
	Opt_policydigest,
	Opt_policyhandle,
पूर्ण;

अटल स्थिर match_table_t key_tokens = अणु
	अणुOpt_keyhandle, "keyhandle=%s"पूर्ण,
	अणुOpt_keyauth, "keyauth=%s"पूर्ण,
	अणुOpt_blobauth, "blobauth=%s"पूर्ण,
	अणुOpt_pcrinfo, "pcrinfo=%s"पूर्ण,
	अणुOpt_pcrlock, "pcrlock=%s"पूर्ण,
	अणुOpt_migratable, "migratable=%s"पूर्ण,
	अणुOpt_hash, "hash=%s"पूर्ण,
	अणुOpt_policydigest, "policydigest=%s"पूर्ण,
	अणुOpt_policyhandle, "policyhandle=%s"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

/* can have zero or more token= options */
अटल पूर्णांक getoptions(अक्षर *c, काष्ठा trusted_key_payload *pay,
		      काष्ठा trusted_key_options *opt)
अणु
	substring_t args[MAX_OPT_ARGS];
	अक्षर *p = c;
	पूर्णांक token;
	पूर्णांक res;
	अचिन्हित दीर्घ handle;
	अचिन्हित दीर्घ lock;
	अचिन्हित दीर्घ token_mask = 0;
	अचिन्हित पूर्णांक digest_len;
	पूर्णांक i;
	पूर्णांक tpm2;

	tpm2 = tpm_is_tpm2(chip);
	अगर (tpm2 < 0)
		वापस tpm2;

	opt->hash = tpm2 ? HASH_ALGO_SHA256 : HASH_ALGO_SHA1;

	अगर (!c)
		वापस 0;

	जबतक ((p = strsep(&c, " \t"))) अणु
		अगर (*p == '\0' || *p == ' ' || *p == '\t')
			जारी;
		token = match_token(p, key_tokens, args);
		अगर (test_and_set_bit(token, &token_mask))
			वापस -EINVAL;

		चयन (token) अणु
		हाल Opt_pcrinfo:
			opt->pcrinfo_len = म_माप(args[0].from) / 2;
			अगर (opt->pcrinfo_len > MAX_PCRINFO_SIZE)
				वापस -EINVAL;
			res = hex2bin(opt->pcrinfo, args[0].from,
				      opt->pcrinfo_len);
			अगर (res < 0)
				वापस -EINVAL;
			अवरोध;
		हाल Opt_keyhandle:
			res = kम_से_अदीर्घ(args[0].from, 16, &handle);
			अगर (res < 0)
				वापस -EINVAL;
			opt->keytype = SEAL_keytype;
			opt->keyhandle = handle;
			अवरोध;
		हाल Opt_keyauth:
			अगर (म_माप(args[0].from) != 2 * SHA1_DIGEST_SIZE)
				वापस -EINVAL;
			res = hex2bin(opt->keyauth, args[0].from,
				      SHA1_DIGEST_SIZE);
			अगर (res < 0)
				वापस -EINVAL;
			अवरोध;
		हाल Opt_blobauth:
			/*
			 * TPM 1.2 authorizations are sha1 hashes passed in as
			 * hex strings.  TPM 2.0 authorizations are simple
			 * passwords (although it can take a hash as well)
			 */
			opt->blobauth_len = म_माप(args[0].from);

			अगर (opt->blobauth_len == 2 * TPM_DIGEST_SIZE) अणु
				res = hex2bin(opt->blobauth, args[0].from,
					      TPM_DIGEST_SIZE);
				अगर (res < 0)
					वापस -EINVAL;

				opt->blobauth_len = TPM_DIGEST_SIZE;
				अवरोध;
			पूर्ण

			अगर (tpm2 && opt->blobauth_len <= माप(opt->blobauth)) अणु
				स_नकल(opt->blobauth, args[0].from,
				       opt->blobauth_len);
				अवरोध;
			पूर्ण

			वापस -EINVAL;

			अवरोध;

		हाल Opt_migratable:
			अगर (*args[0].from == '0')
				pay->migratable = 0;
			अन्यथा अगर (*args[0].from != '1')
				वापस -EINVAL;
			अवरोध;
		हाल Opt_pcrlock:
			res = kम_से_अदीर्घ(args[0].from, 10, &lock);
			अगर (res < 0)
				वापस -EINVAL;
			opt->pcrlock = lock;
			अवरोध;
		हाल Opt_hash:
			अगर (test_bit(Opt_policydigest, &token_mask))
				वापस -EINVAL;
			क्रम (i = 0; i < HASH_ALGO__LAST; i++) अणु
				अगर (!म_भेद(args[0].from, hash_algo_name[i])) अणु
					opt->hash = i;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (i == HASH_ALGO__LAST)
				वापस -EINVAL;
			अगर  (!tpm2 && i != HASH_ALGO_SHA1) अणु
				pr_info("TPM 1.x only supports SHA-1.\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल Opt_policydigest:
			digest_len = hash_digest_size[opt->hash];
			अगर (!tpm2 || म_माप(args[0].from) != (2 * digest_len))
				वापस -EINVAL;
			res = hex2bin(opt->policydigest, args[0].from,
				      digest_len);
			अगर (res < 0)
				वापस -EINVAL;
			opt->policydigest_len = digest_len;
			अवरोध;
		हाल Opt_policyhandle:
			अगर (!tpm2)
				वापस -EINVAL;
			res = kम_से_अदीर्घ(args[0].from, 16, &handle);
			अगर (res < 0)
				वापस -EINVAL;
			opt->policyhandle = handle;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा trusted_key_options *trusted_options_alloc(व्योम)
अणु
	काष्ठा trusted_key_options *options;
	पूर्णांक tpm2;

	tpm2 = tpm_is_tpm2(chip);
	अगर (tpm2 < 0)
		वापस शून्य;

	options = kzalloc(माप *options, GFP_KERNEL);
	अगर (options) अणु
		/* set any non-zero शेषs */
		options->keytype = SRK_keytype;

		अगर (!tpm2)
			options->keyhandle = SRKHANDLE;
	पूर्ण
	वापस options;
पूर्ण

अटल पूर्णांक trusted_tpm_seal(काष्ठा trusted_key_payload *p, अक्षर *datablob)
अणु
	काष्ठा trusted_key_options *options = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक tpm2;

	tpm2 = tpm_is_tpm2(chip);
	अगर (tpm2 < 0)
		वापस tpm2;

	options = trusted_options_alloc();
	अगर (!options)
		वापस -ENOMEM;

	ret = getoptions(datablob, p, options);
	अगर (ret < 0)
		जाओ out;
	dump_options(options);

	अगर (!options->keyhandle && !tpm2) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (tpm2)
		ret = tpm2_seal_trusted(chip, p, options);
	अन्यथा
		ret = key_seal(p, options);
	अगर (ret < 0) अणु
		pr_info("key_seal failed (%d)\n", ret);
		जाओ out;
	पूर्ण

	अगर (options->pcrlock) अणु
		ret = pcrlock(options->pcrlock);
		अगर (ret < 0) अणु
			pr_info("pcrlock failed (%d)\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	kमुक्त_sensitive(options);
	वापस ret;
पूर्ण

अटल पूर्णांक trusted_tpm_unseal(काष्ठा trusted_key_payload *p, अक्षर *datablob)
अणु
	काष्ठा trusted_key_options *options = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक tpm2;

	tpm2 = tpm_is_tpm2(chip);
	अगर (tpm2 < 0)
		वापस tpm2;

	options = trusted_options_alloc();
	अगर (!options)
		वापस -ENOMEM;

	ret = getoptions(datablob, p, options);
	अगर (ret < 0)
		जाओ out;
	dump_options(options);

	अगर (!options->keyhandle && !tpm2) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (tpm2)
		ret = tpm2_unseal_trusted(chip, p, options);
	अन्यथा
		ret = key_unseal(p, options);
	अगर (ret < 0)
		pr_info("key_unseal failed (%d)\n", ret);

	अगर (options->pcrlock) अणु
		ret = pcrlock(options->pcrlock);
		अगर (ret < 0) अणु
			pr_info("pcrlock failed (%d)\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	kमुक्त_sensitive(options);
	वापस ret;
पूर्ण

अटल पूर्णांक trusted_tpm_get_अक्रमom(अचिन्हित अक्षर *key, माप_प्रकार key_len)
अणु
	वापस tpm_get_अक्रमom(chip, key, key_len);
पूर्ण

अटल व्योम trusted_shash_release(व्योम)
अणु
	अगर (hashalg)
		crypto_मुक्त_shash(hashalg);
	अगर (hmacalg)
		crypto_मुक्त_shash(hmacalg);
पूर्ण

अटल पूर्णांक __init trusted_shash_alloc(व्योम)
अणु
	पूर्णांक ret;

	hmacalg = crypto_alloc_shash(hmac_alg, 0, 0);
	अगर (IS_ERR(hmacalg)) अणु
		pr_info("could not allocate crypto %s\n",
			hmac_alg);
		वापस PTR_ERR(hmacalg);
	पूर्ण

	hashalg = crypto_alloc_shash(hash_alg, 0, 0);
	अगर (IS_ERR(hashalg)) अणु
		pr_info("could not allocate crypto %s\n",
			hash_alg);
		ret = PTR_ERR(hashalg);
		जाओ hashalg_fail;
	पूर्ण

	वापस 0;

hashalg_fail:
	crypto_मुक्त_shash(hmacalg);
	वापस ret;
पूर्ण

अटल पूर्णांक __init init_digests(व्योम)
अणु
	पूर्णांक i;

	digests = kसुस्मृति(chip->nr_allocated_banks, माप(*digests),
			  GFP_KERNEL);
	अगर (!digests)
		वापस -ENOMEM;

	क्रम (i = 0; i < chip->nr_allocated_banks; i++)
		digests[i].alg_id = chip->allocated_banks[i].alg_id;

	वापस 0;
पूर्ण

अटल पूर्णांक __init trusted_tpm_init(व्योम)
अणु
	पूर्णांक ret;

	chip = tpm_शेष_chip();
	अगर (!chip)
		वापस -ENODEV;

	ret = init_digests();
	अगर (ret < 0)
		जाओ err_put;
	ret = trusted_shash_alloc();
	अगर (ret < 0)
		जाओ err_मुक्त;
	ret = रेजिस्टर_key_type(&key_type_trusted);
	अगर (ret < 0)
		जाओ err_release;
	वापस 0;
err_release:
	trusted_shash_release();
err_मुक्त:
	kमुक्त(digests);
err_put:
	put_device(&chip->dev);
	वापस ret;
पूर्ण

अटल व्योम trusted_tpm_निकास(व्योम)
अणु
	अगर (chip) अणु
		put_device(&chip->dev);
		kमुक्त(digests);
		trusted_shash_release();
		unरेजिस्टर_key_type(&key_type_trusted);
	पूर्ण
पूर्ण

काष्ठा trusted_key_ops trusted_key_tpm_ops = अणु
	.migratable = 1, /* migratable by शेष */
	.init = trusted_tpm_init,
	.seal = trusted_tpm_seal,
	.unseal = trusted_tpm_unseal,
	.get_अक्रमom = trusted_tpm_get_अक्रमom,
	.निकास = trusted_tpm_निकास,
पूर्ण;
