<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Copyright(c) 2016-20 Intel Corporation. */

#घोषणा _GNU_SOURCE
#समावेश <निश्चित.स>
#समावेश <getopt.h>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <खोलोssl/err.h>
#समावेश <खोलोssl/pem.h>
#समावेश "defines.h"
#समावेश "main.h"

काष्ठा q1q2_ctx अणु
	BN_CTX *bn_ctx;
	BIGNUM *m;
	BIGNUM *s;
	BIGNUM *q1;
	BIGNUM *qr;
	BIGNUM *q2;
पूर्ण;

अटल व्योम मुक्त_q1q2_ctx(काष्ठा q1q2_ctx *ctx)
अणु
	BN_CTX_मुक्त(ctx->bn_ctx);
	BN_मुक्त(ctx->m);
	BN_मुक्त(ctx->s);
	BN_मुक्त(ctx->q1);
	BN_मुक्त(ctx->qr);
	BN_मुक्त(ctx->q2);
पूर्ण

अटल bool alloc_q1q2_ctx(स्थिर uपूर्णांक8_t *s, स्थिर uपूर्णांक8_t *m,
			   काष्ठा q1q2_ctx *ctx)
अणु
	ctx->bn_ctx = BN_CTX_new();
	ctx->s = BN_bin2bn(s, SGX_MODULUS_SIZE, शून्य);
	ctx->m = BN_bin2bn(m, SGX_MODULUS_SIZE, शून्य);
	ctx->q1 = BN_new();
	ctx->qr = BN_new();
	ctx->q2 = BN_new();

	अगर (!ctx->bn_ctx || !ctx->s || !ctx->m || !ctx->q1 || !ctx->qr ||
	    !ctx->q2) अणु
		मुक्त_q1q2_ctx(ctx);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool calc_q1q2(स्थिर uपूर्णांक8_t *s, स्थिर uपूर्णांक8_t *m, uपूर्णांक8_t *q1,
		      uपूर्णांक8_t *q2)
अणु
	काष्ठा q1q2_ctx ctx;

	अगर (!alloc_q1q2_ctx(s, m, &ctx)) अणु
		ख_लिखो(मानक_त्रुटि, "Not enough memory for Q1Q2 calculation\n");
		वापस false;
	पूर्ण

	अगर (!BN_mul(ctx.q1, ctx.s, ctx.s, ctx.bn_ctx))
		जाओ out;

	अगर (!BN_भाग(ctx.q1, ctx.qr, ctx.q1, ctx.m, ctx.bn_ctx))
		जाओ out;

	अगर (BN_num_bytes(ctx.q1) > SGX_MODULUS_SIZE) अणु
		ख_लिखो(मानक_त्रुटि, "Too large Q1 %d bytes\n",
			BN_num_bytes(ctx.q1));
		जाओ out;
	पूर्ण

	अगर (!BN_mul(ctx.q2, ctx.s, ctx.qr, ctx.bn_ctx))
		जाओ out;

	अगर (!BN_भाग(ctx.q2, शून्य, ctx.q2, ctx.m, ctx.bn_ctx))
		जाओ out;

	अगर (BN_num_bytes(ctx.q2) > SGX_MODULUS_SIZE) अणु
		ख_लिखो(मानक_त्रुटि, "Too large Q2 %d bytes\n",
			BN_num_bytes(ctx.q2));
		जाओ out;
	पूर्ण

	BN_bn2bin(ctx.q1, q1);
	BN_bn2bin(ctx.q2, q2);

	मुक्त_q1q2_ctx(&ctx);
	वापस true;
out:
	मुक्त_q1q2_ctx(&ctx);
	वापस false;
पूर्ण

काष्ठा sgx_sigकाष्ठा_payload अणु
	काष्ठा sgx_sigकाष्ठा_header header;
	काष्ठा sgx_sigकाष्ठा_body body;
पूर्ण;

अटल bool check_crypto_errors(व्योम)
अणु
	पूर्णांक err;
	bool had_errors = false;
	स्थिर अक्षर *filename;
	पूर्णांक line;
	अक्षर str[256];

	क्रम ( ; ; ) अणु
		अगर (ERR_peek_error() == 0)
			अवरोध;

		had_errors = true;
		err = ERR_get_error_line(&filename, &line);
		ERR_error_string_n(err, str, माप(str));
		ख_लिखो(मानक_त्रुटि, "crypto: %s: %s:%d\n", str, filename, line);
	पूर्ण

	वापस had_errors;
पूर्ण

अटल अंतरभूत स्थिर BIGNUM *get_modulus(RSA *key)
अणु
	स्थिर BIGNUM *n;

	RSA_get0_key(key, &n, शून्य, शून्य);
	वापस n;
पूर्ण

अटल RSA *gen_sign_key(व्योम)
अणु
	अचिन्हित दीर्घ sign_key_length;
	BIO *bio;
	RSA *key;

	sign_key_length = (अचिन्हित दीर्घ)&sign_key_end -
			  (अचिन्हित दीर्घ)&sign_key;

	bio = BIO_new_mem_buf(&sign_key, sign_key_length);
	अगर (!bio)
		वापस शून्य;

	key = PEM_पढ़ो_bio_RSAPrivateKey(bio, शून्य, शून्य, शून्य);
	BIO_मुक्त(bio);

	वापस key;
पूर्ण

अटल व्योम reverse_bytes(व्योम *data, पूर्णांक length)
अणु
	पूर्णांक i = 0;
	पूर्णांक j = length - 1;
	uपूर्णांक8_t temp;
	uपूर्णांक8_t *ptr = data;

	जबतक (i < j) अणु
		temp = ptr[i];
		ptr[i] = ptr[j];
		ptr[j] = temp;
		i++;
		j--;
	पूर्ण
पूर्ण

क्रमागत mrtags अणु
	MRECREATE = 0x0045544145524345,
	MREADD = 0x0000000044444145,
	MREEXTEND = 0x00444E4554584545,
पूर्ण;

अटल bool mrenclave_update(EVP_MD_CTX *ctx, स्थिर व्योम *data)
अणु
	अगर (!EVP_DigestUpdate(ctx, data, 64)) अणु
		ख_लिखो(मानक_त्रुटि, "digest update failed\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool mrenclave_commit(EVP_MD_CTX *ctx, uपूर्णांक8_t *mrenclave)
अणु
	अचिन्हित पूर्णांक size;

	अगर (!EVP_DigestFinal_ex(ctx, (अचिन्हित अक्षर *)mrenclave, &size)) अणु
		ख_लिखो(मानक_त्रुटि, "digest commit failed\n");
		वापस false;
	पूर्ण

	अगर (size != 32) अणु
		ख_लिखो(मानक_त्रुटि, "invalid digest size = %u\n", size);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

काष्ठा mrecreate अणु
	uपूर्णांक64_t tag;
	uपूर्णांक32_t ssaframesize;
	uपूर्णांक64_t size;
	uपूर्णांक8_t reserved[44];
पूर्ण __attribute__((__packed__));


अटल bool mrenclave_ecreate(EVP_MD_CTX *ctx, uपूर्णांक64_t blob_size)
अणु
	काष्ठा mrecreate mrecreate;
	uपूर्णांक64_t encl_size;

	क्रम (encl_size = 0x1000; encl_size < blob_size; )
		encl_size <<= 1;

	स_रखो(&mrecreate, 0, माप(mrecreate));
	mrecreate.tag = MRECREATE;
	mrecreate.ssaframesize = 1;
	mrecreate.size = encl_size;

	अगर (!EVP_DigestInit_ex(ctx, EVP_sha256(), शून्य))
		वापस false;

	वापस mrenclave_update(ctx, &mrecreate);
पूर्ण

काष्ठा mपढ़ोd अणु
	uपूर्णांक64_t tag;
	uपूर्णांक64_t offset;
	uपूर्णांक64_t flags; /* SECINFO flags */
	uपूर्णांक8_t reserved[40];
पूर्ण __attribute__((__packed__));

अटल bool mrenclave_eadd(EVP_MD_CTX *ctx, uपूर्णांक64_t offset, uपूर्णांक64_t flags)
अणु
	काष्ठा mपढ़ोd mपढ़ोd;

	स_रखो(&mपढ़ोd, 0, माप(mपढ़ोd));
	mपढ़ोd.tag = MREADD;
	mपढ़ोd.offset = offset;
	mपढ़ोd.flags = flags;

	वापस mrenclave_update(ctx, &mपढ़ोd);
पूर्ण

काष्ठा mreextend अणु
	uपूर्णांक64_t tag;
	uपूर्णांक64_t offset;
	uपूर्णांक8_t reserved[48];
पूर्ण __attribute__((__packed__));

अटल bool mrenclave_eextend(EVP_MD_CTX *ctx, uपूर्णांक64_t offset,
			      स्थिर uपूर्णांक8_t *data)
अणु
	काष्ठा mreextend mreextend;
	पूर्णांक i;

	क्रम (i = 0; i < 0x1000; i += 0x100) अणु
		स_रखो(&mreextend, 0, माप(mreextend));
		mreextend.tag = MREEXTEND;
		mreextend.offset = offset + i;

		अगर (!mrenclave_update(ctx, &mreextend))
			वापस false;

		अगर (!mrenclave_update(ctx, &data[i + 0x00]))
			वापस false;

		अगर (!mrenclave_update(ctx, &data[i + 0x40]))
			वापस false;

		अगर (!mrenclave_update(ctx, &data[i + 0x80]))
			वापस false;

		अगर (!mrenclave_update(ctx, &data[i + 0xC0]))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool mrenclave_segment(EVP_MD_CTX *ctx, काष्ठा encl *encl,
			      काष्ठा encl_segment *seg)
अणु
	uपूर्णांक64_t end = seg->offset + seg->size;
	uपूर्णांक64_t offset;

	क्रम (offset = seg->offset; offset < end; offset += PAGE_SIZE) अणु
		अगर (!mrenclave_eadd(ctx, offset, seg->flags))
			वापस false;

		अगर (!mrenclave_eextend(ctx, offset, encl->src + offset))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool encl_measure(काष्ठा encl *encl)
अणु
	uपूर्णांक64_t header1[2] = अणु0x000000E100000006, 0x0000000000010000पूर्ण;
	uपूर्णांक64_t header2[2] = अणु0x0000006000000101, 0x0000000100000060पूर्ण;
	काष्ठा sgx_sigकाष्ठा *sigकाष्ठा = &encl->sigकाष्ठा;
	काष्ठा sgx_sigकाष्ठा_payload payload;
	uपूर्णांक8_t digest[SHA256_DIGEST_LENGTH];
	अचिन्हित पूर्णांक siglen;
	RSA *key = शून्य;
	EVP_MD_CTX *ctx;
	पूर्णांक i;

	स_रखो(sigकाष्ठा, 0, माप(*sigकाष्ठा));

	sigकाष्ठा->header.header1[0] = header1[0];
	sigकाष्ठा->header.header1[1] = header1[1];
	sigकाष्ठा->header.header2[0] = header2[0];
	sigकाष्ठा->header.header2[1] = header2[1];
	sigकाष्ठा->exponent = 3;
	sigकाष्ठा->body.attributes = SGX_ATTR_MODE64BIT;
	sigकाष्ठा->body.xfrm = 3;

	/* sanity check */
	अगर (check_crypto_errors())
		जाओ err;

	key = gen_sign_key();
	अगर (!key) अणु
		ERR_prपूर्णांक_errors_fp(मानक_निकास);
		जाओ err;
	पूर्ण

	BN_bn2bin(get_modulus(key), sigकाष्ठा->modulus);

	ctx = EVP_MD_CTX_create();
	अगर (!ctx)
		जाओ err;

	अगर (!mrenclave_ecreate(ctx, encl->src_size))
		जाओ err;

	क्रम (i = 0; i < encl->nr_segments; i++) अणु
		काष्ठा encl_segment *seg = &encl->segment_tbl[i];

		अगर (!mrenclave_segment(ctx, encl, seg))
			जाओ err;
	पूर्ण

	अगर (!mrenclave_commit(ctx, sigकाष्ठा->body.mrenclave))
		जाओ err;

	स_नकल(&payload.header, &sigकाष्ठा->header, माप(sigकाष्ठा->header));
	स_नकल(&payload.body, &sigकाष्ठा->body, माप(sigकाष्ठा->body));

	SHA256((अचिन्हित अक्षर *)&payload, माप(payload), digest);

	अगर (!RSA_sign(NID_sha256, digest, SHA256_DIGEST_LENGTH,
		      sigकाष्ठा->signature, &siglen, key))
		जाओ err;

	अगर (!calc_q1q2(sigकाष्ठा->signature, sigकाष्ठा->modulus, sigकाष्ठा->q1,
		       sigकाष्ठा->q2))
		जाओ err;

	/* BE -> LE */
	reverse_bytes(sigकाष्ठा->signature, SGX_MODULUS_SIZE);
	reverse_bytes(sigकाष्ठा->modulus, SGX_MODULUS_SIZE);
	reverse_bytes(sigकाष्ठा->q1, SGX_MODULUS_SIZE);
	reverse_bytes(sigकाष्ठा->q2, SGX_MODULUS_SIZE);

	EVP_MD_CTX_destroy(ctx);
	RSA_मुक्त(key);
	वापस true;

err:
	EVP_MD_CTX_destroy(ctx);
	RSA_मुक्त(key);
	वापस false;
पूर्ण
