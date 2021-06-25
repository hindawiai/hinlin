<शैली गुरु>
/*
 * DRBG based on NIST SP800-90A
 *
 * Copyright Stephan Mueller <smueller@chronox.de>, 2014
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, and the entire permission notice in its entirety,
 *    including the disclaimer of warranties.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to enकरोrse or promote
 *    products derived from this software without specअगरic prior
 *    written permission.
 *
 * ALTERNATIVELY, this product may be distributed under the terms of
 * the GNU General Public License, in which हाल the provisions of the GPL are
 * required INSTEAD OF the above restrictions.  (This clause is
 * necessary due to a potential bad पूर्णांकeraction between the GPL and
 * the restrictions contained in a BSD-style copyright.)
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ALL OF
 * WHICH ARE HEREBY DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#अगर_अघोषित _DRBG_H
#घोषणा _DRBG_H


#समावेश <linux/अक्रमom.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/module.h>
#समावेश <linux/crypto.h>
#समावेश <linux/slab.h>
#समावेश <crypto/पूर्णांकernal/rng.h>
#समावेश <crypto/rng.h>
#समावेश <linux/fips.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>

/*
 * Concatenation Helper and string operation helper
 *
 * SP800-90A requires the concatenation of dअगरferent data. To aव्योम copying
 * buffers around or allocate additional memory, the following data काष्ठाure
 * is used to poपूर्णांक to the original memory with its size. In addition, it
 * is used to build a linked list. The linked list defines the concatenation
 * of inभागidual buffers. The order of memory block referenced in that
 * linked list determines the order of concatenation.
 */
काष्ठा drbg_string अणु
	स्थिर अचिन्हित अक्षर *buf;
	माप_प्रकार len;
	काष्ठा list_head list;
पूर्ण;

अटल अंतरभूत व्योम drbg_string_fill(काष्ठा drbg_string *string,
				    स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len)
अणु
	string->buf = buf;
	string->len = len;
	INIT_LIST_HEAD(&string->list);
पूर्ण

काष्ठा drbg_state;
प्रकार uपूर्णांक32_t drbg_flag_t;

काष्ठा drbg_core अणु
	drbg_flag_t flags;	/* flags क्रम the cipher */
	__u8 statelen;		/* maximum state length */
	__u8 blocklen_bytes;	/* block size of output in bytes */
	अक्षर cra_name[CRYPTO_MAX_ALG_NAME]; /* mapping to kernel crypto API */
	 /* kernel crypto API backend cipher name */
	अक्षर backend_cra_name[CRYPTO_MAX_ALG_NAME];
पूर्ण;

काष्ठा drbg_state_ops अणु
	पूर्णांक (*update)(काष्ठा drbg_state *drbg, काष्ठा list_head *seed,
		      पूर्णांक reseed);
	पूर्णांक (*generate)(काष्ठा drbg_state *drbg,
			अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen,
			काष्ठा list_head *addtl);
	पूर्णांक (*crypto_init)(काष्ठा drbg_state *drbg);
	पूर्णांक (*crypto_fini)(काष्ठा drbg_state *drbg);

पूर्ण;

काष्ठा drbg_test_data अणु
	काष्ठा drbg_string *testentropy; /* TEST PARAMETER: test entropy */
पूर्ण;

काष्ठा drbg_state अणु
	काष्ठा mutex drbg_mutex;	/* lock around DRBG */
	अचिन्हित अक्षर *V;	/* पूर्णांकernal state 10.1.1.1 1a) */
	अचिन्हित अक्षर *Vbuf;
	/* hash: अटल value 10.1.1.1 1b) hmac / ctr: key */
	अचिन्हित अक्षर *C;
	अचिन्हित अक्षर *Cbuf;
	/* Number of RNG requests since last reseed -- 10.1.1.1 1c) */
	माप_प्रकार reseed_ctr;
	माप_प्रकार reseed_threshold;
	 /* some memory the DRBG can use क्रम its operation */
	अचिन्हित अक्षर *scratchpad;
	अचिन्हित अक्षर *scratchpadbuf;
	व्योम *priv_data;	/* Cipher handle */

	काष्ठा crypto_skcipher *ctr_handle;	/* CTR mode cipher handle */
	काष्ठा skcipher_request *ctr_req;	/* CTR mode request handle */
	__u8 *outscratchpadbuf;			/* CTR mode output scratchpad */
        __u8 *outscratchpad;			/* CTR mode aligned outbuf */
	काष्ठा crypto_रुको ctr_रुको;		/* CTR mode async रुको obj */
	काष्ठा scatterlist sg_in, sg_out;	/* CTR mode SGLs */

	bool seeded;		/* DRBG fully seeded? */
	bool pr;		/* Prediction resistance enabled? */
	bool fips_primed;	/* Continuous test primed? */
	अचिन्हित अक्षर *prev;	/* FIPS 140-2 continuous test value */
	काष्ठा work_काष्ठा seed_work;	/* asynchronous seeding support */
	काष्ठा crypto_rng *jent;
	स्थिर काष्ठा drbg_state_ops *d_ops;
	स्थिर काष्ठा drbg_core *core;
	काष्ठा drbg_string test_data;
	काष्ठा अक्रमom_पढ़ोy_callback अक्रमom_पढ़ोy;
पूर्ण;

अटल अंतरभूत __u8 drbg_statelen(काष्ठा drbg_state *drbg)
अणु
	अगर (drbg && drbg->core)
		वापस drbg->core->statelen;
	वापस 0;
पूर्ण

अटल अंतरभूत __u8 drbg_blocklen(काष्ठा drbg_state *drbg)
अणु
	अगर (drbg && drbg->core)
		वापस drbg->core->blocklen_bytes;
	वापस 0;
पूर्ण

अटल अंतरभूत __u8 drbg_keylen(काष्ठा drbg_state *drbg)
अणु
	अगर (drbg && drbg->core)
		वापस (drbg->core->statelen - drbg->core->blocklen_bytes);
	वापस 0;
पूर्ण

अटल अंतरभूत माप_प्रकार drbg_max_request_bytes(काष्ठा drbg_state *drbg)
अणु
	/* SP800-90A requires the limit 2**19 bits, but we वापस bytes */
	वापस (1 << 16);
पूर्ण

अटल अंतरभूत माप_प्रकार drbg_max_addtl(काष्ठा drbg_state *drbg)
अणु
	/* SP800-90A requires 2**35 bytes additional info str / pers str */
#अगर (__BITS_PER_LONG == 32)
	/*
	 * SP800-90A allows smaller maximum numbers to be वापसed -- we
	 * वापस SIZE_MAX - 1 to allow the verअगरication of the enक्रमcement
	 * of this value in drbg_healthcheck_sanity.
	 */
	वापस (SIZE_MAX - 1);
#अन्यथा
	वापस (1UL<<35);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत माप_प्रकार drbg_max_requests(काष्ठा drbg_state *drbg)
अणु
	/* SP800-90A requires 2**48 maximum requests beक्रमe reseeding */
	वापस (1<<20);
पूर्ण

/*
 * This is a wrapper to the kernel crypto API function of
 * crypto_rng_generate() to allow the caller to provide additional data.
 *
 * @drng DRBG handle -- see crypto_rng_get_bytes
 * @outbuf output buffer -- see crypto_rng_get_bytes
 * @outlen length of output buffer -- see crypto_rng_get_bytes
 * @addtl_input additional inक्रमmation string input buffer
 * @addtllen length of additional inक्रमmation string buffer
 *
 * वापस
 *	see crypto_rng_get_bytes
 */
अटल अंतरभूत पूर्णांक crypto_drbg_get_bytes_addtl(काष्ठा crypto_rng *drng,
			अचिन्हित अक्षर *outbuf, अचिन्हित पूर्णांक outlen,
			काष्ठा drbg_string *addtl)
अणु
	वापस crypto_rng_generate(drng, addtl->buf, addtl->len,
				   outbuf, outlen);
पूर्ण

/*
 * TEST code
 *
 * This is a wrapper to the kernel crypto API function of
 * crypto_rng_generate() to allow the caller to provide additional data and
 * allow furnishing of test_data
 *
 * @drng DRBG handle -- see crypto_rng_get_bytes
 * @outbuf output buffer -- see crypto_rng_get_bytes
 * @outlen length of output buffer -- see crypto_rng_get_bytes
 * @addtl_input additional inक्रमmation string input buffer
 * @addtllen length of additional inक्रमmation string buffer
 * @test_data filled test data
 *
 * वापस
 *	see crypto_rng_get_bytes
 */
अटल अंतरभूत पूर्णांक crypto_drbg_get_bytes_addtl_test(काष्ठा crypto_rng *drng,
			अचिन्हित अक्षर *outbuf, अचिन्हित पूर्णांक outlen,
			काष्ठा drbg_string *addtl,
			काष्ठा drbg_test_data *test_data)
अणु
	crypto_rng_set_entropy(drng, test_data->testentropy->buf,
			       test_data->testentropy->len);
	वापस crypto_rng_generate(drng, addtl->buf, addtl->len,
				   outbuf, outlen);
पूर्ण

/*
 * TEST code
 *
 * This is a wrapper to the kernel crypto API function of
 * crypto_rng_reset() to allow the caller to provide test_data
 *
 * @drng DRBG handle -- see crypto_rng_reset
 * @pers personalization string input buffer
 * @perslen length of additional inक्रमmation string buffer
 * @test_data filled test data
 *
 * वापस
 *	see crypto_rng_reset
 */
अटल अंतरभूत पूर्णांक crypto_drbg_reset_test(काष्ठा crypto_rng *drng,
					 काष्ठा drbg_string *pers,
					 काष्ठा drbg_test_data *test_data)
अणु
	crypto_rng_set_entropy(drng, test_data->testentropy->buf,
			       test_data->testentropy->len);
	वापस crypto_rng_reset(drng, pers->buf, pers->len);
पूर्ण

/* DRBG type flags */
#घोषणा DRBG_CTR	((drbg_flag_t)1<<0)
#घोषणा DRBG_HMAC	((drbg_flag_t)1<<1)
#घोषणा DRBG_HASH	((drbg_flag_t)1<<2)
#घोषणा DRBG_TYPE_MASK	(DRBG_CTR | DRBG_HMAC | DRBG_HASH)
/* DRBG strength flags */
#घोषणा DRBG_STRENGTH128	((drbg_flag_t)1<<3)
#घोषणा DRBG_STRENGTH192	((drbg_flag_t)1<<4)
#घोषणा DRBG_STRENGTH256	((drbg_flag_t)1<<5)
#घोषणा DRBG_STRENGTH_MASK	(DRBG_STRENGTH128 | DRBG_STRENGTH192 | \
				 DRBG_STRENGTH256)

क्रमागत drbg_prefixes अणु
	DRBG_PREFIX0 = 0x00,
	DRBG_PREFIX1,
	DRBG_PREFIX2,
	DRBG_PREFIX3
पूर्ण;

#पूर्ण_अगर /* _DRBG_H */
