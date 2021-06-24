<शैली गुरु>
/*
 *  linux/net/sunrpc/gss_krb5_crypto.c
 *
 *  Copyright (c) 2000-2008 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Andy Adamson   <andros@umich.edu>
 *  Bruce Fields   <bfields@umich.edu>
 */

/*
 * Copyright (C) 1998 by the FundsXpress, INC.
 *
 * All rights reserved.
 *
 * Export of this software from the United States of America may require
 * a specअगरic license from the United States Government.  It is the
 * responsibility of any person or organization contemplating export to
 * obtain such a license beक्रमe exporting.
 *
 * WITHIN THAT CONSTRAINT, permission to use, copy, modअगरy, and
 * distribute this software and its करोcumentation क्रम any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting करोcumentation, and that
 * the name of FundsXpress. not be used in advertising or खुलाity pertaining
 * to distribution of the software without specअगरic, written prior
 * permission.  FundsXpress makes no representations about the suitability of
 * this software क्रम any purpose.  It is provided "as is" without express
 * or implied warranty.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sunrpc/gss_krb5.h>
#समावेश <linux/sunrpc/xdr.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY        RPCDBG_AUTH
#पूर्ण_अगर

u32
krb5_encrypt(
	काष्ठा crypto_sync_skcipher *tfm,
	व्योम * iv,
	व्योम * in,
	व्योम * out,
	पूर्णांक length)
अणु
	u32 ret = -EINVAL;
	काष्ठा scatterlist sg[1];
	u8 local_iv[GSS_KRB5_MAX_BLOCKSIZE] = अणु0पूर्ण;
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, tfm);

	अगर (length % crypto_sync_skcipher_blocksize(tfm) != 0)
		जाओ out;

	अगर (crypto_sync_skcipher_ivsize(tfm) > GSS_KRB5_MAX_BLOCKSIZE) अणु
		dprपूर्णांकk("RPC:       gss_k5encrypt: tfm iv size too large %d\n",
			crypto_sync_skcipher_ivsize(tfm));
		जाओ out;
	पूर्ण

	अगर (iv)
		स_नकल(local_iv, iv, crypto_sync_skcipher_ivsize(tfm));

	स_नकल(out, in, length);
	sg_init_one(sg, out, length);

	skcipher_request_set_sync_tfm(req, tfm);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, sg, sg, length, local_iv);

	ret = crypto_skcipher_encrypt(req);
	skcipher_request_zero(req);
out:
	dprपूर्णांकk("RPC:       krb5_encrypt returns %d\n", ret);
	वापस ret;
पूर्ण

u32
krb5_decrypt(
     काष्ठा crypto_sync_skcipher *tfm,
     व्योम * iv,
     व्योम * in,
     व्योम * out,
     पूर्णांक length)
अणु
	u32 ret = -EINVAL;
	काष्ठा scatterlist sg[1];
	u8 local_iv[GSS_KRB5_MAX_BLOCKSIZE] = अणु0पूर्ण;
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, tfm);

	अगर (length % crypto_sync_skcipher_blocksize(tfm) != 0)
		जाओ out;

	अगर (crypto_sync_skcipher_ivsize(tfm) > GSS_KRB5_MAX_BLOCKSIZE) अणु
		dprपूर्णांकk("RPC:       gss_k5decrypt: tfm iv size too large %d\n",
			crypto_sync_skcipher_ivsize(tfm));
		जाओ out;
	पूर्ण
	अगर (iv)
		स_नकल(local_iv, iv, crypto_sync_skcipher_ivsize(tfm));

	स_नकल(out, in, length);
	sg_init_one(sg, out, length);

	skcipher_request_set_sync_tfm(req, tfm);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, sg, sg, length, local_iv);

	ret = crypto_skcipher_decrypt(req);
	skcipher_request_zero(req);
out:
	dprपूर्णांकk("RPC:       gss_k5decrypt returns %d\n",ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
checksummer(काष्ठा scatterlist *sg, व्योम *data)
अणु
	काष्ठा ahash_request *req = data;

	ahash_request_set_crypt(req, sg, शून्य, sg->length);

	वापस crypto_ahash_update(req);
पूर्ण

/*
 * checksum the plaपूर्णांकext data and hdrlen bytes of the token header
 * The checksum is perक्रमmed over the first 8 bytes of the
 * gss token header and then over the data body
 */
u32
make_checksum(काष्ठा krb5_ctx *kctx, अक्षर *header, पूर्णांक hdrlen,
	      काष्ठा xdr_buf *body, पूर्णांक body_offset, u8 *cksumkey,
	      अचिन्हित पूर्णांक usage, काष्ठा xdr_netobj *cksumout)
अणु
	काष्ठा crypto_ahash *tfm;
	काष्ठा ahash_request *req;
	काष्ठा scatterlist              sg[1];
	पूर्णांक err = -1;
	u8 *checksumdata;
	अचिन्हित पूर्णांक checksumlen;

	अगर (cksumout->len < kctx->gk5e->cksumlength) अणु
		dprपूर्णांकk("%s: checksum buffer length, %u, too small for %s\n",
			__func__, cksumout->len, kctx->gk5e->name);
		वापस GSS_S_FAILURE;
	पूर्ण

	checksumdata = kदो_स्मृति(GSS_KRB5_MAX_CKSUM_LEN, GFP_NOFS);
	अगर (checksumdata == शून्य)
		वापस GSS_S_FAILURE;

	tfm = crypto_alloc_ahash(kctx->gk5e->cksum_name, 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm))
		जाओ out_मुक्त_cksum;

	req = ahash_request_alloc(tfm, GFP_NOFS);
	अगर (!req)
		जाओ out_मुक्त_ahash;

	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP, शून्य, शून्य);

	checksumlen = crypto_ahash_digestsize(tfm);

	अगर (cksumkey != शून्य) अणु
		err = crypto_ahash_setkey(tfm, cksumkey,
					  kctx->gk5e->keylength);
		अगर (err)
			जाओ out;
	पूर्ण

	err = crypto_ahash_init(req);
	अगर (err)
		जाओ out;
	sg_init_one(sg, header, hdrlen);
	ahash_request_set_crypt(req, sg, शून्य, hdrlen);
	err = crypto_ahash_update(req);
	अगर (err)
		जाओ out;
	err = xdr_process_buf(body, body_offset, body->len - body_offset,
			      checksummer, req);
	अगर (err)
		जाओ out;
	ahash_request_set_crypt(req, शून्य, checksumdata, 0);
	err = crypto_ahash_final(req);
	अगर (err)
		जाओ out;

	चयन (kctx->gk5e->ctype) अणु
	हाल CKSUMTYPE_RSA_MD5:
		err = kctx->gk5e->encrypt(kctx->seq, शून्य, checksumdata,
					  checksumdata, checksumlen);
		अगर (err)
			जाओ out;
		स_नकल(cksumout->data,
		       checksumdata + checksumlen - kctx->gk5e->cksumlength,
		       kctx->gk5e->cksumlength);
		अवरोध;
	हाल CKSUMTYPE_HMAC_SHA1_DES3:
		स_नकल(cksumout->data, checksumdata, kctx->gk5e->cksumlength);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण
	cksumout->len = kctx->gk5e->cksumlength;
out:
	ahash_request_मुक्त(req);
out_मुक्त_ahash:
	crypto_मुक्त_ahash(tfm);
out_मुक्त_cksum:
	kमुक्त(checksumdata);
	वापस err ? GSS_S_FAILURE : 0;
पूर्ण

/*
 * checksum the plaपूर्णांकext data and hdrlen bytes of the token header
 * Per rfc4121, sec. 4.2.4, the checksum is perक्रमmed over the data
 * body then over the first 16 octets of the MIC token
 * Inclusion of the header data in the calculation of the
 * checksum is optional.
 */
u32
make_checksum_v2(काष्ठा krb5_ctx *kctx, अक्षर *header, पूर्णांक hdrlen,
		 काष्ठा xdr_buf *body, पूर्णांक body_offset, u8 *cksumkey,
		 अचिन्हित पूर्णांक usage, काष्ठा xdr_netobj *cksumout)
अणु
	काष्ठा crypto_ahash *tfm;
	काष्ठा ahash_request *req;
	काष्ठा scatterlist sg[1];
	पूर्णांक err = -1;
	u8 *checksumdata;

	अगर (kctx->gk5e->keyed_cksum == 0) अणु
		dprपूर्णांकk("%s: expected keyed hash for %s\n",
			__func__, kctx->gk5e->name);
		वापस GSS_S_FAILURE;
	पूर्ण
	अगर (cksumkey == शून्य) अणु
		dprपूर्णांकk("%s: no key supplied for %s\n",
			__func__, kctx->gk5e->name);
		वापस GSS_S_FAILURE;
	पूर्ण

	checksumdata = kदो_स्मृति(GSS_KRB5_MAX_CKSUM_LEN, GFP_NOFS);
	अगर (!checksumdata)
		वापस GSS_S_FAILURE;

	tfm = crypto_alloc_ahash(kctx->gk5e->cksum_name, 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm))
		जाओ out_मुक्त_cksum;

	req = ahash_request_alloc(tfm, GFP_NOFS);
	अगर (!req)
		जाओ out_मुक्त_ahash;

	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP, शून्य, शून्य);

	err = crypto_ahash_setkey(tfm, cksumkey, kctx->gk5e->keylength);
	अगर (err)
		जाओ out;

	err = crypto_ahash_init(req);
	अगर (err)
		जाओ out;
	err = xdr_process_buf(body, body_offset, body->len - body_offset,
			      checksummer, req);
	अगर (err)
		जाओ out;
	अगर (header != शून्य) अणु
		sg_init_one(sg, header, hdrlen);
		ahash_request_set_crypt(req, sg, शून्य, hdrlen);
		err = crypto_ahash_update(req);
		अगर (err)
			जाओ out;
	पूर्ण
	ahash_request_set_crypt(req, शून्य, checksumdata, 0);
	err = crypto_ahash_final(req);
	अगर (err)
		जाओ out;

	cksumout->len = kctx->gk5e->cksumlength;

	चयन (kctx->gk5e->ctype) अणु
	हाल CKSUMTYPE_HMAC_SHA1_96_AES128:
	हाल CKSUMTYPE_HMAC_SHA1_96_AES256:
		/* note that this truncates the hash */
		स_नकल(cksumout->data, checksumdata, kctx->gk5e->cksumlength);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण
out:
	ahash_request_मुक्त(req);
out_मुक्त_ahash:
	crypto_मुक्त_ahash(tfm);
out_मुक्त_cksum:
	kमुक्त(checksumdata);
	वापस err ? GSS_S_FAILURE : 0;
पूर्ण

काष्ठा encryptor_desc अणु
	u8 iv[GSS_KRB5_MAX_BLOCKSIZE];
	काष्ठा skcipher_request *req;
	पूर्णांक pos;
	काष्ठा xdr_buf *outbuf;
	काष्ठा page **pages;
	काष्ठा scatterlist infrags[4];
	काष्ठा scatterlist outfrags[4];
	पूर्णांक fragno;
	पूर्णांक fraglen;
पूर्ण;

अटल पूर्णांक
encryptor(काष्ठा scatterlist *sg, व्योम *data)
अणु
	काष्ठा encryptor_desc *desc = data;
	काष्ठा xdr_buf *outbuf = desc->outbuf;
	काष्ठा crypto_sync_skcipher *tfm =
		crypto_sync_skcipher_reqtfm(desc->req);
	काष्ठा page *in_page;
	पूर्णांक thislen = desc->fraglen + sg->length;
	पूर्णांक fraglen, ret;
	पूर्णांक page_pos;

	/* Worst हाल is 4 fragments: head, end of page 1, start
	 * of page 2, tail.  Anything more is a bug. */
	BUG_ON(desc->fragno > 3);

	page_pos = desc->pos - outbuf->head[0].iov_len;
	अगर (page_pos >= 0 && page_pos < outbuf->page_len) अणु
		/* pages are not in place: */
		पूर्णांक i = (page_pos + outbuf->page_base) >> PAGE_SHIFT;
		in_page = desc->pages[i];
	पूर्ण अन्यथा अणु
		in_page = sg_page(sg);
	पूर्ण
	sg_set_page(&desc->infrags[desc->fragno], in_page, sg->length,
		    sg->offset);
	sg_set_page(&desc->outfrags[desc->fragno], sg_page(sg), sg->length,
		    sg->offset);
	desc->fragno++;
	desc->fraglen += sg->length;
	desc->pos += sg->length;

	fraglen = thislen & (crypto_sync_skcipher_blocksize(tfm) - 1);
	thislen -= fraglen;

	अगर (thislen == 0)
		वापस 0;

	sg_mark_end(&desc->infrags[desc->fragno - 1]);
	sg_mark_end(&desc->outfrags[desc->fragno - 1]);

	skcipher_request_set_crypt(desc->req, desc->infrags, desc->outfrags,
				   thislen, desc->iv);

	ret = crypto_skcipher_encrypt(desc->req);
	अगर (ret)
		वापस ret;

	sg_init_table(desc->infrags, 4);
	sg_init_table(desc->outfrags, 4);

	अगर (fraglen) अणु
		sg_set_page(&desc->outfrags[0], sg_page(sg), fraglen,
				sg->offset + sg->length - fraglen);
		desc->infrags[0] = desc->outfrags[0];
		sg_assign_page(&desc->infrags[0], in_page);
		desc->fragno = 1;
		desc->fraglen = fraglen;
	पूर्ण अन्यथा अणु
		desc->fragno = 0;
		desc->fraglen = 0;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
gss_encrypt_xdr_buf(काष्ठा crypto_sync_skcipher *tfm, काष्ठा xdr_buf *buf,
		    पूर्णांक offset, काष्ठा page **pages)
अणु
	पूर्णांक ret;
	काष्ठा encryptor_desc desc;
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, tfm);

	BUG_ON((buf->len - offset) % crypto_sync_skcipher_blocksize(tfm) != 0);

	skcipher_request_set_sync_tfm(req, tfm);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);

	स_रखो(desc.iv, 0, माप(desc.iv));
	desc.req = req;
	desc.pos = offset;
	desc.outbuf = buf;
	desc.pages = pages;
	desc.fragno = 0;
	desc.fraglen = 0;

	sg_init_table(desc.infrags, 4);
	sg_init_table(desc.outfrags, 4);

	ret = xdr_process_buf(buf, offset, buf->len - offset, encryptor, &desc);
	skcipher_request_zero(req);
	वापस ret;
पूर्ण

काष्ठा decryptor_desc अणु
	u8 iv[GSS_KRB5_MAX_BLOCKSIZE];
	काष्ठा skcipher_request *req;
	काष्ठा scatterlist frags[4];
	पूर्णांक fragno;
	पूर्णांक fraglen;
पूर्ण;

अटल पूर्णांक
decryptor(काष्ठा scatterlist *sg, व्योम *data)
अणु
	काष्ठा decryptor_desc *desc = data;
	पूर्णांक thislen = desc->fraglen + sg->length;
	काष्ठा crypto_sync_skcipher *tfm =
		crypto_sync_skcipher_reqtfm(desc->req);
	पूर्णांक fraglen, ret;

	/* Worst हाल is 4 fragments: head, end of page 1, start
	 * of page 2, tail.  Anything more is a bug. */
	BUG_ON(desc->fragno > 3);
	sg_set_page(&desc->frags[desc->fragno], sg_page(sg), sg->length,
		    sg->offset);
	desc->fragno++;
	desc->fraglen += sg->length;

	fraglen = thislen & (crypto_sync_skcipher_blocksize(tfm) - 1);
	thislen -= fraglen;

	अगर (thislen == 0)
		वापस 0;

	sg_mark_end(&desc->frags[desc->fragno - 1]);

	skcipher_request_set_crypt(desc->req, desc->frags, desc->frags,
				   thislen, desc->iv);

	ret = crypto_skcipher_decrypt(desc->req);
	अगर (ret)
		वापस ret;

	sg_init_table(desc->frags, 4);

	अगर (fraglen) अणु
		sg_set_page(&desc->frags[0], sg_page(sg), fraglen,
				sg->offset + sg->length - fraglen);
		desc->fragno = 1;
		desc->fraglen = fraglen;
	पूर्ण अन्यथा अणु
		desc->fragno = 0;
		desc->fraglen = 0;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
gss_decrypt_xdr_buf(काष्ठा crypto_sync_skcipher *tfm, काष्ठा xdr_buf *buf,
		    पूर्णांक offset)
अणु
	पूर्णांक ret;
	काष्ठा decryptor_desc desc;
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, tfm);

	/* XXXJBF: */
	BUG_ON((buf->len - offset) % crypto_sync_skcipher_blocksize(tfm) != 0);

	skcipher_request_set_sync_tfm(req, tfm);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);

	स_रखो(desc.iv, 0, माप(desc.iv));
	desc.req = req;
	desc.fragno = 0;
	desc.fraglen = 0;

	sg_init_table(desc.frags, 4);

	ret = xdr_process_buf(buf, offset, buf->len - offset, decryptor, &desc);
	skcipher_request_zero(req);
	वापस ret;
पूर्ण

/*
 * This function makes the assumption that it was ultimately called
 * from gss_wrap().
 *
 * The client auth_gss code moves any existing tail data पूर्णांकo a
 * separate page beक्रमe calling gss_wrap.
 * The server svcauth_gss code ensures that both the head and the
 * tail have slack space of RPC_MAX_AUTH_SIZE beक्रमe calling gss_wrap.
 *
 * Even with that guarantee, this function may be called more than
 * once in the processing of gss_wrap().  The best we can करो is
 * verअगरy at compile-समय (see GSS_KRB5_SLACK_CHECK) that the
 * largest expected shअगरt will fit within RPC_MAX_AUTH_SIZE.
 * At run-समय we can verअगरy that a single invocation of this
 * function करोesn't attempt to use more the RPC_MAX_AUTH_SIZE.
 */

पूर्णांक
xdr_extend_head(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक shअगरtlen)
अणु
	u8 *p;

	अगर (shअगरtlen == 0)
		वापस 0;

	BUILD_BUG_ON(GSS_KRB5_MAX_SLACK_NEEDED > RPC_MAX_AUTH_SIZE);
	BUG_ON(shअगरtlen > RPC_MAX_AUTH_SIZE);

	p = buf->head[0].iov_base + base;

	स_हटाओ(p + shअगरtlen, p, buf->head[0].iov_len - base);

	buf->head[0].iov_len += shअगरtlen;
	buf->len += shअगरtlen;

	वापस 0;
पूर्ण

अटल u32
gss_krb5_cts_crypt(काष्ठा crypto_sync_skcipher *cipher, काष्ठा xdr_buf *buf,
		   u32 offset, u8 *iv, काष्ठा page **pages, पूर्णांक encrypt)
अणु
	u32 ret;
	काष्ठा scatterlist sg[1];
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, cipher);
	u8 *data;
	काष्ठा page **save_pages;
	u32 len = buf->len - offset;

	अगर (len > GSS_KRB5_MAX_BLOCKSIZE * 2) अणु
		WARN_ON(0);
		वापस -ENOMEM;
	पूर्ण
	data = kदो_स्मृति(GSS_KRB5_MAX_BLOCKSIZE * 2, GFP_NOFS);
	अगर (!data)
		वापस -ENOMEM;

	/*
	 * For encryption, we want to पढ़ो from the cleartext
	 * page cache pages, and ग_लिखो the encrypted data to
	 * the supplied xdr_buf pages.
	 */
	save_pages = buf->pages;
	अगर (encrypt)
		buf->pages = pages;

	ret = पढ़ो_bytes_from_xdr_buf(buf, offset, data, len);
	buf->pages = save_pages;
	अगर (ret)
		जाओ out;

	sg_init_one(sg, data, len);

	skcipher_request_set_sync_tfm(req, cipher);
	skcipher_request_set_callback(req, 0, शून्य, शून्य);
	skcipher_request_set_crypt(req, sg, sg, len, iv);

	अगर (encrypt)
		ret = crypto_skcipher_encrypt(req);
	अन्यथा
		ret = crypto_skcipher_decrypt(req);

	skcipher_request_zero(req);

	अगर (ret)
		जाओ out;

	ret = ग_लिखो_bytes_to_xdr_buf(buf, offset, data, len);

out:
	kमुक्त(data);
	वापस ret;
पूर्ण

u32
gss_krb5_aes_encrypt(काष्ठा krb5_ctx *kctx, u32 offset,
		     काष्ठा xdr_buf *buf, काष्ठा page **pages)
अणु
	u32 err;
	काष्ठा xdr_netobj hmac;
	u8 *cksumkey;
	u8 *ecptr;
	काष्ठा crypto_sync_skcipher *cipher, *aux_cipher;
	पूर्णांक blocksize;
	काष्ठा page **save_pages;
	पूर्णांक nblocks, nbytes;
	काष्ठा encryptor_desc desc;
	u32 cbcbytes;
	अचिन्हित पूर्णांक usage;

	अगर (kctx->initiate) अणु
		cipher = kctx->initiator_enc;
		aux_cipher = kctx->initiator_enc_aux;
		cksumkey = kctx->initiator_पूर्णांकeg;
		usage = KG_USAGE_INITIATOR_SEAL;
	पूर्ण अन्यथा अणु
		cipher = kctx->acceptor_enc;
		aux_cipher = kctx->acceptor_enc_aux;
		cksumkey = kctx->acceptor_पूर्णांकeg;
		usage = KG_USAGE_ACCEPTOR_SEAL;
	पूर्ण
	blocksize = crypto_sync_skcipher_blocksize(cipher);

	/* hide the gss token header and insert the confounder */
	offset += GSS_KRB5_TOK_HDR_LEN;
	अगर (xdr_extend_head(buf, offset, kctx->gk5e->conflen))
		वापस GSS_S_FAILURE;
	gss_krb5_make_confounder(buf->head[0].iov_base + offset, kctx->gk5e->conflen);
	offset -= GSS_KRB5_TOK_HDR_LEN;

	अगर (buf->tail[0].iov_base != शून्य) अणु
		ecptr = buf->tail[0].iov_base + buf->tail[0].iov_len;
	पूर्ण अन्यथा अणु
		buf->tail[0].iov_base = buf->head[0].iov_base
							+ buf->head[0].iov_len;
		buf->tail[0].iov_len = 0;
		ecptr = buf->tail[0].iov_base;
	पूर्ण

	/* copy plaपूर्णांकext gss token header after filler (अगर any) */
	स_नकल(ecptr, buf->head[0].iov_base + offset, GSS_KRB5_TOK_HDR_LEN);
	buf->tail[0].iov_len += GSS_KRB5_TOK_HDR_LEN;
	buf->len += GSS_KRB5_TOK_HDR_LEN;

	/* Do the HMAC */
	hmac.len = GSS_KRB5_MAX_CKSUM_LEN;
	hmac.data = buf->tail[0].iov_base + buf->tail[0].iov_len;

	/*
	 * When we are called, pages poपूर्णांकs to the real page cache
	 * data -- which we can't go and encrypt!  buf->pages poपूर्णांकs
	 * to scratch pages which we are going to send off to the
	 * client/server.  Swap in the plaपूर्णांकext pages to calculate
	 * the hmac.
	 */
	save_pages = buf->pages;
	buf->pages = pages;

	err = make_checksum_v2(kctx, शून्य, 0, buf,
			       offset + GSS_KRB5_TOK_HDR_LEN,
			       cksumkey, usage, &hmac);
	buf->pages = save_pages;
	अगर (err)
		वापस GSS_S_FAILURE;

	nbytes = buf->len - offset - GSS_KRB5_TOK_HDR_LEN;
	nblocks = (nbytes + blocksize - 1) / blocksize;
	cbcbytes = 0;
	अगर (nblocks > 2)
		cbcbytes = (nblocks - 2) * blocksize;

	स_रखो(desc.iv, 0, माप(desc.iv));

	अगर (cbcbytes) अणु
		SYNC_SKCIPHER_REQUEST_ON_STACK(req, aux_cipher);

		desc.pos = offset + GSS_KRB5_TOK_HDR_LEN;
		desc.fragno = 0;
		desc.fraglen = 0;
		desc.pages = pages;
		desc.outbuf = buf;
		desc.req = req;

		skcipher_request_set_sync_tfm(req, aux_cipher);
		skcipher_request_set_callback(req, 0, शून्य, शून्य);

		sg_init_table(desc.infrags, 4);
		sg_init_table(desc.outfrags, 4);

		err = xdr_process_buf(buf, offset + GSS_KRB5_TOK_HDR_LEN,
				      cbcbytes, encryptor, &desc);
		skcipher_request_zero(req);
		अगर (err)
			जाओ out_err;
	पूर्ण

	/* Make sure IV carries क्रमward from any CBC results. */
	err = gss_krb5_cts_crypt(cipher, buf,
				 offset + GSS_KRB5_TOK_HDR_LEN + cbcbytes,
				 desc.iv, pages, 1);
	अगर (err) अणु
		err = GSS_S_FAILURE;
		जाओ out_err;
	पूर्ण

	/* Now update buf to account क्रम HMAC */
	buf->tail[0].iov_len += kctx->gk5e->cksumlength;
	buf->len += kctx->gk5e->cksumlength;

out_err:
	अगर (err)
		err = GSS_S_FAILURE;
	वापस err;
पूर्ण

u32
gss_krb5_aes_decrypt(काष्ठा krb5_ctx *kctx, u32 offset, u32 len,
		     काष्ठा xdr_buf *buf, u32 *headskip, u32 *tailskip)
अणु
	काष्ठा xdr_buf subbuf;
	u32 ret = 0;
	u8 *cksum_key;
	काष्ठा crypto_sync_skcipher *cipher, *aux_cipher;
	काष्ठा xdr_netobj our_hmac_obj;
	u8 our_hmac[GSS_KRB5_MAX_CKSUM_LEN];
	u8 pkt_hmac[GSS_KRB5_MAX_CKSUM_LEN];
	पूर्णांक nblocks, blocksize, cbcbytes;
	काष्ठा decryptor_desc desc;
	अचिन्हित पूर्णांक usage;

	अगर (kctx->initiate) अणु
		cipher = kctx->acceptor_enc;
		aux_cipher = kctx->acceptor_enc_aux;
		cksum_key = kctx->acceptor_पूर्णांकeg;
		usage = KG_USAGE_ACCEPTOR_SEAL;
	पूर्ण अन्यथा अणु
		cipher = kctx->initiator_enc;
		aux_cipher = kctx->initiator_enc_aux;
		cksum_key = kctx->initiator_पूर्णांकeg;
		usage = KG_USAGE_INITIATOR_SEAL;
	पूर्ण
	blocksize = crypto_sync_skcipher_blocksize(cipher);


	/* create a segment skipping the header and leaving out the checksum */
	xdr_buf_subsegment(buf, &subbuf, offset + GSS_KRB5_TOK_HDR_LEN,
				    (len - offset - GSS_KRB5_TOK_HDR_LEN -
				     kctx->gk5e->cksumlength));

	nblocks = (subbuf.len + blocksize - 1) / blocksize;

	cbcbytes = 0;
	अगर (nblocks > 2)
		cbcbytes = (nblocks - 2) * blocksize;

	स_रखो(desc.iv, 0, माप(desc.iv));

	अगर (cbcbytes) अणु
		SYNC_SKCIPHER_REQUEST_ON_STACK(req, aux_cipher);

		desc.fragno = 0;
		desc.fraglen = 0;
		desc.req = req;

		skcipher_request_set_sync_tfm(req, aux_cipher);
		skcipher_request_set_callback(req, 0, शून्य, शून्य);

		sg_init_table(desc.frags, 4);

		ret = xdr_process_buf(&subbuf, 0, cbcbytes, decryptor, &desc);
		skcipher_request_zero(req);
		अगर (ret)
			जाओ out_err;
	पूर्ण

	/* Make sure IV carries क्रमward from any CBC results. */
	ret = gss_krb5_cts_crypt(cipher, &subbuf, cbcbytes, desc.iv, शून्य, 0);
	अगर (ret)
		जाओ out_err;


	/* Calculate our hmac over the plaपूर्णांकext data */
	our_hmac_obj.len = माप(our_hmac);
	our_hmac_obj.data = our_hmac;

	ret = make_checksum_v2(kctx, शून्य, 0, &subbuf, 0,
			       cksum_key, usage, &our_hmac_obj);
	अगर (ret)
		जाओ out_err;

	/* Get the packet's hmac value */
	ret = पढ़ो_bytes_from_xdr_buf(buf, len - kctx->gk5e->cksumlength,
				      pkt_hmac, kctx->gk5e->cksumlength);
	अगर (ret)
		जाओ out_err;

	अगर (crypto_memneq(pkt_hmac, our_hmac, kctx->gk5e->cksumlength) != 0) अणु
		ret = GSS_S_BAD_SIG;
		जाओ out_err;
	पूर्ण
	*headskip = kctx->gk5e->conflen;
	*tailskip = kctx->gk5e->cksumlength;
out_err:
	अगर (ret && ret != GSS_S_BAD_SIG)
		ret = GSS_S_FAILURE;
	वापस ret;
पूर्ण
