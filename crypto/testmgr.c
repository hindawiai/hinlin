<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Algorithm testing framework and tests.
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2002 Jean-Francois Dive <jef@linuxbe.org>
 * Copyright (c) 2007 Nokia Siemens Networks
 * Copyright (c) 2008 Herbert Xu <herbert@gonकरोr.apana.org.au>
 * Copyright (c) 2019 Google LLC
 *
 * Updated RFC4106 AES-GCM testing.
 *    Authors: Aidan O'Mahony (aidan.o.mahony@पूर्णांकel.com)
 *             Adrian Hoban <adrian.hoban@पूर्णांकel.com>
 *             Gabriele Paoloni <gabriele.paoloni@पूर्णांकel.com>
 *             Tadeusz Struk (tadeusz.struk@पूर्णांकel.com)
 *    Copyright (c) 2010, Intel Corporation.
 */

#समावेश <crypto/aead.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/fips.h>
#समावेश <linux/module.h>
#समावेश <linux/once.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/uपन.स>
#समावेश <crypto/rng.h>
#समावेश <crypto/drbg.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/kpp.h>
#समावेश <crypto/acompress.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/simd.h>

#समावेश "internal.h"

MODULE_IMPORT_NS(CRYPTO_INTERNAL);

अटल bool notests;
module_param(notests, bool, 0644);
MODULE_PARM_DESC(notests, "disable crypto self-tests");

अटल bool panic_on_fail;
module_param(panic_on_fail, bool, 0444);

#अगर_घोषित CONFIG_CRYPTO_MANAGER_EXTRA_TESTS
अटल bool noextratests;
module_param(noextratests, bool, 0644);
MODULE_PARM_DESC(noextratests, "disable expensive crypto self-tests");

अटल अचिन्हित पूर्णांक fuzz_iterations = 100;
module_param(fuzz_iterations, uपूर्णांक, 0644);
MODULE_PARM_DESC(fuzz_iterations, "number of fuzz test iterations");

DEFINE_PER_CPU(bool, crypto_simd_disabled_क्रम_test);
EXPORT_PER_CPU_SYMBOL_GPL(crypto_simd_disabled_क्रम_test);
#पूर्ण_अगर

#अगर_घोषित CONFIG_CRYPTO_MANAGER_DISABLE_TESTS

/* a perfect nop */
पूर्णांक alg_test(स्थिर अक्षर *driver, स्थिर अक्षर *alg, u32 type, u32 mask)
अणु
	वापस 0;
पूर्ण

#अन्यथा

#समावेश "testmgr.h"

/*
 * Need slab memory क्रम testing (size in number of pages).
 */
#घोषणा Xबफ_मानE	8

/*
* Used by test_cipher()
*/
#घोषणा ENCRYPT 1
#घोषणा DECRYPT 0

काष्ठा aead_test_suite अणु
	स्थिर काष्ठा aead_testvec *vecs;
	अचिन्हित पूर्णांक count;

	/*
	 * Set अगर trying to decrypt an inauthentic ciphertext with this
	 * algorithm might result in EINVAL rather than EBADMSG, due to other
	 * validation the algorithm करोes on the inमाला_दो such as length checks.
	 */
	अचिन्हित पूर्णांक einval_allowed : 1;

	/*
	 * Set अगर this algorithm requires that the IV be located at the end of
	 * the AAD buffer, in addition to being given in the normal way.  The
	 * behavior when the two IV copies dअगरfer is implementation-defined.
	 */
	अचिन्हित पूर्णांक aad_iv : 1;
पूर्ण;

काष्ठा cipher_test_suite अणु
	स्थिर काष्ठा cipher_testvec *vecs;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा comp_test_suite अणु
	काष्ठा अणु
		स्थिर काष्ठा comp_testvec *vecs;
		अचिन्हित पूर्णांक count;
	पूर्ण comp, decomp;
पूर्ण;

काष्ठा hash_test_suite अणु
	स्थिर काष्ठा hash_testvec *vecs;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा cprng_test_suite अणु
	स्थिर काष्ठा cprng_testvec *vecs;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा drbg_test_suite अणु
	स्थिर काष्ठा drbg_testvec *vecs;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा akcipher_test_suite अणु
	स्थिर काष्ठा akcipher_testvec *vecs;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा kpp_test_suite अणु
	स्थिर काष्ठा kpp_testvec *vecs;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा alg_test_desc अणु
	स्थिर अक्षर *alg;
	स्थिर अक्षर *generic_driver;
	पूर्णांक (*test)(स्थिर काष्ठा alg_test_desc *desc, स्थिर अक्षर *driver,
		    u32 type, u32 mask);
	पूर्णांक fips_allowed;	/* set अगर alg is allowed in fips mode */

	जोड़ अणु
		काष्ठा aead_test_suite aead;
		काष्ठा cipher_test_suite cipher;
		काष्ठा comp_test_suite comp;
		काष्ठा hash_test_suite hash;
		काष्ठा cprng_test_suite cprng;
		काष्ठा drbg_test_suite drbg;
		काष्ठा akcipher_test_suite akcipher;
		काष्ठा kpp_test_suite kpp;
	पूर्ण suite;
पूर्ण;

अटल व्योम hexdump(अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	prपूर्णांक_hex_dump(KERN_CONT, "", DUMP_PREFIX_OFFSET,
			16, 1,
			buf, len, false);
पूर्ण

अटल पूर्णांक __tesपंचांगgr_alloc_buf(अक्षर *buf[Xबफ_मानE], पूर्णांक order)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < Xबफ_मानE; i++) अणु
		buf[i] = (अक्षर *)__get_मुक्त_pages(GFP_KERNEL, order);
		अगर (!buf[i])
			जाओ err_मुक्त_buf;
	पूर्ण

	वापस 0;

err_मुक्त_buf:
	जबतक (i-- > 0)
		मुक्त_pages((अचिन्हित दीर्घ)buf[i], order);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक tesपंचांगgr_alloc_buf(अक्षर *buf[Xबफ_मानE])
अणु
	वापस __tesपंचांगgr_alloc_buf(buf, 0);
पूर्ण

अटल व्योम __tesपंचांगgr_मुक्त_buf(अक्षर *buf[Xबफ_मानE], पूर्णांक order)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < Xबफ_मानE; i++)
		मुक्त_pages((अचिन्हित दीर्घ)buf[i], order);
पूर्ण

अटल व्योम tesपंचांगgr_मुक्त_buf(अक्षर *buf[Xबफ_मानE])
अणु
	__tesपंचांगgr_मुक्त_buf(buf, 0);
पूर्ण

#घोषणा TESTMGR_POISON_BYTE	0xfe
#घोषणा TESTMGR_POISON_LEN	16

अटल अंतरभूत व्योम tesपंचांगgr_poison(व्योम *addr, माप_प्रकार len)
अणु
	स_रखो(addr, TESTMGR_POISON_BYTE, len);
पूर्ण

/* Is the memory region still fully poisoned? */
अटल अंतरभूत bool tesपंचांगgr_is_poison(स्थिर व्योम *addr, माप_प्रकार len)
अणु
	वापस स_प्रथम_inv(addr, TESTMGR_POISON_BYTE, len) == शून्य;
पूर्ण

/* flush type क्रम hash algorithms */
क्रमागत flush_type अणु
	/* merge with update of previous buffer(s) */
	FLUSH_TYPE_NONE = 0,

	/* update with previous buffer(s) beक्रमe करोing this one */
	FLUSH_TYPE_FLUSH,

	/* likewise, but also export and re-import the पूर्णांकermediate state */
	FLUSH_TYPE_REIMPORT,
पूर्ण;

/* finalization function क्रम hash algorithms */
क्रमागत finalization_type अणु
	FINALIZATION_TYPE_FINAL,	/* use final() */
	FINALIZATION_TYPE_FINUP,	/* use finup() */
	FINALIZATION_TYPE_DIGEST,	/* use digest() */
पूर्ण;

#घोषणा TEST_SG_TOTAL	10000

/**
 * काष्ठा test_sg_भागision - description of a scatterlist entry
 *
 * This काष्ठा describes one entry of a scatterlist being स्थिरructed to check a
 * crypto test vector.
 *
 * @proportion_of_total: length of this chunk relative to the total length,
 *			 given as a proportion out of TEST_SG_TOTAL so that it
 *			 scales to fit any test vector
 * @offset: byte offset पूर्णांकo a 2-page buffer at which this chunk will start
 * @offset_relative_to_alignmask: अगर true, add the algorithm's alignmask to the
 *				  @offset
 * @flush_type: क्रम hashes, whether an update() should be करोne now vs.
 *		continuing to accumulate data
 * @nosimd: अगर करोing the pending update(), करो it with SIMD disabled?
 */
काष्ठा test_sg_भागision अणु
	अचिन्हित पूर्णांक proportion_of_total;
	अचिन्हित पूर्णांक offset;
	bool offset_relative_to_alignmask;
	क्रमागत flush_type flush_type;
	bool nosimd;
पूर्ण;

/**
 * काष्ठा testvec_config - configuration क्रम testing a crypto test vector
 *
 * This काष्ठा describes the data layout and other parameters with which each
 * crypto test vector can be tested.
 *
 * @name: name of this config, logged क्रम debugging purposes अगर a test fails
 * @inplace: operate on the data in-place, अगर applicable क्रम the algorithm type?
 * @req_flags: extra request_flags, e.g. CRYPTO_TFM_REQ_MAY_SLEEP
 * @src_भागs: description of how to arrange the source scatterlist
 * @dst_भागs: description of how to arrange the dst scatterlist, अगर applicable
 *	      क्रम the algorithm type.  Defaults to @src_भागs अगर unset.
 * @iv_offset: misalignment of the IV in the range [0..MAX_ALGAPI_ALIGNMASK+1],
 *	       where 0 is aligned to a 2*(MAX_ALGAPI_ALIGNMASK+1) byte boundary
 * @iv_offset_relative_to_alignmask: अगर true, add the algorithm's alignmask to
 *				     the @iv_offset
 * @key_offset: misalignment of the key, where 0 is शेष alignment
 * @key_offset_relative_to_alignmask: अगर true, add the algorithm's alignmask to
 *				      the @key_offset
 * @finalization_type: what finalization function to use क्रम hashes
 * @nosimd: execute with SIMD disabled?  Requires !CRYPTO_TFM_REQ_MAY_SLEEP.
 */
काष्ठा testvec_config अणु
	स्थिर अक्षर *name;
	bool inplace;
	u32 req_flags;
	काष्ठा test_sg_भागision src_भागs[Xबफ_मानE];
	काष्ठा test_sg_भागision dst_भागs[Xबफ_मानE];
	अचिन्हित पूर्णांक iv_offset;
	अचिन्हित पूर्णांक key_offset;
	bool iv_offset_relative_to_alignmask;
	bool key_offset_relative_to_alignmask;
	क्रमागत finalization_type finalization_type;
	bool nosimd;
पूर्ण;

#घोषणा TESTVEC_CONFIG_NAMELEN	192

/*
 * The following are the lists of testvec_configs to test क्रम each algorithm
 * type when the basic crypto self-tests are enabled, i.e. when
 * CONFIG_CRYPTO_MANAGER_DISABLE_TESTS is unset.  They aim to provide good test
 * coverage, जबतक keeping the test समय much लघुer than the full fuzz tests
 * so that the basic tests can be enabled in a wider range of circumstances.
 */

/* Configs क्रम skciphers and aeads */
अटल स्थिर काष्ठा testvec_config शेष_cipher_testvec_configs[] = अणु
	अणु
		.name = "in-place",
		.inplace = true,
		.src_भागs = अणु अणु .proportion_of_total = 10000 पूर्ण पूर्ण,
	पूर्ण, अणु
		.name = "out-of-place",
		.src_भागs = अणु अणु .proportion_of_total = 10000 पूर्ण पूर्ण,
	पूर्ण, अणु
		.name = "unaligned buffer, offset=1",
		.src_भागs = अणु अणु .proportion_of_total = 10000, .offset = 1 पूर्ण पूर्ण,
		.iv_offset = 1,
		.key_offset = 1,
	पूर्ण, अणु
		.name = "buffer aligned only to alignmask",
		.src_भागs = अणु
			अणु
				.proportion_of_total = 10000,
				.offset = 1,
				.offset_relative_to_alignmask = true,
			पूर्ण,
		पूर्ण,
		.iv_offset = 1,
		.iv_offset_relative_to_alignmask = true,
		.key_offset = 1,
		.key_offset_relative_to_alignmask = true,
	पूर्ण, अणु
		.name = "two even aligned splits",
		.src_भागs = अणु
			अणु .proportion_of_total = 5000 पूर्ण,
			अणु .proportion_of_total = 5000 पूर्ण,
		पूर्ण,
	पूर्ण, अणु
		.name = "uneven misaligned splits, may sleep",
		.req_flags = CRYPTO_TFM_REQ_MAY_SLEEP,
		.src_भागs = अणु
			अणु .proportion_of_total = 1900, .offset = 33 पूर्ण,
			अणु .proportion_of_total = 3300, .offset = 7  पूर्ण,
			अणु .proportion_of_total = 4800, .offset = 18 पूर्ण,
		पूर्ण,
		.iv_offset = 3,
		.key_offset = 3,
	पूर्ण, अणु
		.name = "misaligned splits crossing pages, inplace",
		.inplace = true,
		.src_भागs = अणु
			अणु
				.proportion_of_total = 7500,
				.offset = PAGE_SIZE - 32
			पूर्ण, अणु
				.proportion_of_total = 2500,
				.offset = PAGE_SIZE - 7
			पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा testvec_config शेष_hash_testvec_configs[] = अणु
	अणु
		.name = "init+update+final aligned buffer",
		.src_भागs = अणु अणु .proportion_of_total = 10000 पूर्ण पूर्ण,
		.finalization_type = FINALIZATION_TYPE_FINAL,
	पूर्ण, अणु
		.name = "init+finup aligned buffer",
		.src_भागs = अणु अणु .proportion_of_total = 10000 पूर्ण पूर्ण,
		.finalization_type = FINALIZATION_TYPE_FINUP,
	पूर्ण, अणु
		.name = "digest aligned buffer",
		.src_भागs = अणु अणु .proportion_of_total = 10000 पूर्ण पूर्ण,
		.finalization_type = FINALIZATION_TYPE_DIGEST,
	पूर्ण, अणु
		.name = "init+update+final misaligned buffer",
		.src_भागs = अणु अणु .proportion_of_total = 10000, .offset = 1 पूर्ण पूर्ण,
		.finalization_type = FINALIZATION_TYPE_FINAL,
		.key_offset = 1,
	पूर्ण, अणु
		.name = "digest buffer aligned only to alignmask",
		.src_भागs = अणु
			अणु
				.proportion_of_total = 10000,
				.offset = 1,
				.offset_relative_to_alignmask = true,
			पूर्ण,
		पूर्ण,
		.finalization_type = FINALIZATION_TYPE_DIGEST,
		.key_offset = 1,
		.key_offset_relative_to_alignmask = true,
	पूर्ण, अणु
		.name = "init+update+update+final two even splits",
		.src_भागs = अणु
			अणु .proportion_of_total = 5000 पूर्ण,
			अणु
				.proportion_of_total = 5000,
				.flush_type = FLUSH_TYPE_FLUSH,
			पूर्ण,
		पूर्ण,
		.finalization_type = FINALIZATION_TYPE_FINAL,
	पूर्ण, अणु
		.name = "digest uneven misaligned splits, may sleep",
		.req_flags = CRYPTO_TFM_REQ_MAY_SLEEP,
		.src_भागs = अणु
			अणु .proportion_of_total = 1900, .offset = 33 पूर्ण,
			अणु .proportion_of_total = 3300, .offset = 7  पूर्ण,
			अणु .proportion_of_total = 4800, .offset = 18 पूर्ण,
		पूर्ण,
		.finalization_type = FINALIZATION_TYPE_DIGEST,
	पूर्ण, अणु
		.name = "digest misaligned splits crossing pages",
		.src_भागs = अणु
			अणु
				.proportion_of_total = 7500,
				.offset = PAGE_SIZE - 32,
			पूर्ण, अणु
				.proportion_of_total = 2500,
				.offset = PAGE_SIZE - 7,
			पूर्ण,
		पूर्ण,
		.finalization_type = FINALIZATION_TYPE_DIGEST,
	पूर्ण, अणु
		.name = "import/export",
		.src_भागs = अणु
			अणु
				.proportion_of_total = 6500,
				.flush_type = FLUSH_TYPE_REIMPORT,
			पूर्ण, अणु
				.proportion_of_total = 3500,
				.flush_type = FLUSH_TYPE_REIMPORT,
			पूर्ण,
		पूर्ण,
		.finalization_type = FINALIZATION_TYPE_FINAL,
	पूर्ण
पूर्ण;

अटल अचिन्हित पूर्णांक count_test_sg_भागisions(स्थिर काष्ठा test_sg_भागision *भागs)
अणु
	अचिन्हित पूर्णांक reमुख्यing = TEST_SG_TOTAL;
	अचिन्हित पूर्णांक nभागs = 0;

	करो अणु
		reमुख्यing -= भागs[nभागs++].proportion_of_total;
	पूर्ण जबतक (reमुख्यing);

	वापस nभागs;
पूर्ण

#घोषणा SGDIVS_HAVE_FLUSHES	BIT(0)
#घोषणा SGDIVS_HAVE_NOSIMD	BIT(1)

अटल bool valid_sg_भागisions(स्थिर काष्ठा test_sg_भागision *भागs,
			       अचिन्हित पूर्णांक count, पूर्णांक *flags_ret)
अणु
	अचिन्हित पूर्णांक total = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count && total != TEST_SG_TOTAL; i++) अणु
		अगर (भागs[i].proportion_of_total <= 0 ||
		    भागs[i].proportion_of_total > TEST_SG_TOTAL - total)
			वापस false;
		total += भागs[i].proportion_of_total;
		अगर (भागs[i].flush_type != FLUSH_TYPE_NONE)
			*flags_ret |= SGDIVS_HAVE_FLUSHES;
		अगर (भागs[i].nosimd)
			*flags_ret |= SGDIVS_HAVE_NOSIMD;
	पूर्ण
	वापस total == TEST_SG_TOTAL &&
		स_प्रथम_inv(&भागs[i], 0, (count - i) * माप(भागs[0])) == शून्य;
पूर्ण

/*
 * Check whether the given testvec_config is valid.  This isn't strictly needed
 * since every testvec_config should be valid, but check anyway so that people
 * करोn't unknowingly add broken configs that don't करो what they wanted.
 */
अटल bool valid_testvec_config(स्थिर काष्ठा testvec_config *cfg)
अणु
	पूर्णांक flags = 0;

	अगर (cfg->name == शून्य)
		वापस false;

	अगर (!valid_sg_भागisions(cfg->src_भागs, ARRAY_SIZE(cfg->src_भागs),
				&flags))
		वापस false;

	अगर (cfg->dst_भागs[0].proportion_of_total) अणु
		अगर (!valid_sg_भागisions(cfg->dst_भागs,
					ARRAY_SIZE(cfg->dst_भागs), &flags))
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (स_प्रथम_inv(cfg->dst_भागs, 0, माप(cfg->dst_भागs)))
			वापस false;
		/* शेषs to dst_भागs=src_भागs */
	पूर्ण

	अगर (cfg->iv_offset +
	    (cfg->iv_offset_relative_to_alignmask ? MAX_ALGAPI_ALIGNMASK : 0) >
	    MAX_ALGAPI_ALIGNMASK + 1)
		वापस false;

	अगर ((flags & (SGDIVS_HAVE_FLUSHES | SGDIVS_HAVE_NOSIMD)) &&
	    cfg->finalization_type == FINALIZATION_TYPE_DIGEST)
		वापस false;

	अगर ((cfg->nosimd || (flags & SGDIVS_HAVE_NOSIMD)) &&
	    (cfg->req_flags & CRYPTO_TFM_REQ_MAY_SLEEP))
		वापस false;

	वापस true;
पूर्ण

काष्ठा test_sglist अणु
	अक्षर *bufs[Xबफ_मानE];
	काष्ठा scatterlist sgl[Xबफ_मानE];
	काष्ठा scatterlist sgl_saved[Xबफ_मानE];
	काष्ठा scatterlist *sgl_ptr;
	अचिन्हित पूर्णांक nents;
पूर्ण;

अटल पूर्णांक init_test_sglist(काष्ठा test_sglist *tsgl)
अणु
	वापस __tesपंचांगgr_alloc_buf(tsgl->bufs, 1 /* two pages per buffer */);
पूर्ण

अटल व्योम destroy_test_sglist(काष्ठा test_sglist *tsgl)
अणु
	वापस __tesपंचांगgr_मुक्त_buf(tsgl->bufs, 1 /* two pages per buffer */);
पूर्ण

/**
 * build_test_sglist() - build a scatterlist क्रम a crypto test
 *
 * @tsgl: the scatterlist to build.  @tsgl->bufs[] contains an array of 2-page
 *	  buffers which the scatterlist @tsgl->sgl[] will be made to poपूर्णांक पूर्णांकo.
 * @भागs: the layout specअगरication on which the scatterlist will be based
 * @alignmask: the algorithm's alignmask
 * @total_len: the total length of the scatterlist to build in bytes
 * @data: अगर non-शून्य, the buffers will be filled with this data until it ends.
 *	  Otherwise the buffers will be poisoned.  In both हालs, some bytes
 *	  past the end of each buffer will be poisoned to help detect overruns.
 * @out_भागs: अगर non-शून्य, the test_sg_भागision to which each scatterlist entry
 *	      corresponds will be वापसed here.  This will match @भागs except
 *	      that भागisions resolving to a length of 0 are omitted as they are
 *	      not included in the scatterlist.
 *
 * Return: 0 or a -त्रुटि_सं value
 */
अटल पूर्णांक build_test_sglist(काष्ठा test_sglist *tsgl,
			     स्थिर काष्ठा test_sg_भागision *भागs,
			     स्थिर अचिन्हित पूर्णांक alignmask,
			     स्थिर अचिन्हित पूर्णांक total_len,
			     काष्ठा iov_iter *data,
			     स्थिर काष्ठा test_sg_भागision *out_भागs[Xबफ_मानE])
अणु
	काष्ठा अणु
		स्थिर काष्ठा test_sg_भागision *भाग;
		माप_प्रकार length;
	पूर्ण partitions[Xबफ_मानE];
	स्थिर अचिन्हित पूर्णांक nभागs = count_test_sg_भागisions(भागs);
	अचिन्हित पूर्णांक len_reमुख्यing = total_len;
	अचिन्हित पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(partitions) != ARRAY_SIZE(tsgl->sgl));
	अगर (WARN_ON(nभागs > ARRAY_SIZE(partitions)))
		वापस -EINVAL;

	/* Calculate the (भाग, length) pairs */
	tsgl->nents = 0;
	क्रम (i = 0; i < nभागs; i++) अणु
		अचिन्हित पूर्णांक len_this_sg =
			min(len_reमुख्यing,
			    (total_len * भागs[i].proportion_of_total +
			     TEST_SG_TOTAL / 2) / TEST_SG_TOTAL);

		अगर (len_this_sg != 0) अणु
			partitions[tsgl->nents].भाग = &भागs[i];
			partitions[tsgl->nents].length = len_this_sg;
			tsgl->nents++;
			len_reमुख्यing -= len_this_sg;
		पूर्ण
	पूर्ण
	अगर (tsgl->nents == 0) अणु
		partitions[tsgl->nents].भाग = &भागs[0];
		partitions[tsgl->nents].length = 0;
		tsgl->nents++;
	पूर्ण
	partitions[tsgl->nents - 1].length += len_reमुख्यing;

	/* Set up the sgl entries and fill the data or poison */
	sg_init_table(tsgl->sgl, tsgl->nents);
	क्रम (i = 0; i < tsgl->nents; i++) अणु
		अचिन्हित पूर्णांक offset = partitions[i].भाग->offset;
		व्योम *addr;

		अगर (partitions[i].भाग->offset_relative_to_alignmask)
			offset += alignmask;

		जबतक (offset + partitions[i].length + TESTMGR_POISON_LEN >
		       2 * PAGE_SIZE) अणु
			अगर (WARN_ON(offset <= 0))
				वापस -EINVAL;
			offset /= 2;
		पूर्ण

		addr = &tsgl->bufs[i][offset];
		sg_set_buf(&tsgl->sgl[i], addr, partitions[i].length);

		अगर (out_भागs)
			out_भागs[i] = partitions[i].भाग;

		अगर (data) अणु
			माप_प्रकार copy_len, copied;

			copy_len = min(partitions[i].length, data->count);
			copied = copy_from_iter(addr, copy_len, data);
			अगर (WARN_ON(copied != copy_len))
				वापस -EINVAL;
			tesपंचांगgr_poison(addr + copy_len, partitions[i].length +
				       TESTMGR_POISON_LEN - copy_len);
		पूर्ण अन्यथा अणु
			tesपंचांगgr_poison(addr, partitions[i].length +
				       TESTMGR_POISON_LEN);
		पूर्ण
	पूर्ण

	sg_mark_end(&tsgl->sgl[tsgl->nents - 1]);
	tsgl->sgl_ptr = tsgl->sgl;
	स_नकल(tsgl->sgl_saved, tsgl->sgl, tsgl->nents * माप(tsgl->sgl[0]));
	वापस 0;
पूर्ण

/*
 * Verअगरy that a scatterlist crypto operation produced the correct output.
 *
 * @tsgl: scatterlist containing the actual output
 * @expected_output: buffer containing the expected output
 * @len_to_check: length of @expected_output in bytes
 * @unchecked_prefix_len: number of ignored bytes in @tsgl prior to real result
 * @check_poison: verअगरy that the poison bytes after each chunk are पूर्णांकact?
 *
 * Return: 0 अगर correct, -EINVAL अगर incorrect, -EOVERFLOW अगर buffer overrun.
 */
अटल पूर्णांक verअगरy_correct_output(स्थिर काष्ठा test_sglist *tsgl,
				 स्थिर अक्षर *expected_output,
				 अचिन्हित पूर्णांक len_to_check,
				 अचिन्हित पूर्णांक unchecked_prefix_len,
				 bool check_poison)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < tsgl->nents; i++) अणु
		काष्ठा scatterlist *sg = &tsgl->sgl_ptr[i];
		अचिन्हित पूर्णांक len = sg->length;
		अचिन्हित पूर्णांक offset = sg->offset;
		स्थिर अक्षर *actual_output;

		अगर (unchecked_prefix_len) अणु
			अगर (unchecked_prefix_len >= len) अणु
				unchecked_prefix_len -= len;
				जारी;
			पूर्ण
			offset += unchecked_prefix_len;
			len -= unchecked_prefix_len;
			unchecked_prefix_len = 0;
		पूर्ण
		len = min(len, len_to_check);
		actual_output = page_address(sg_page(sg)) + offset;
		अगर (स_भेद(expected_output, actual_output, len) != 0)
			वापस -EINVAL;
		अगर (check_poison &&
		    !tesपंचांगgr_is_poison(actual_output + len, TESTMGR_POISON_LEN))
			वापस -EOVERFLOW;
		len_to_check -= len;
		expected_output += len;
	पूर्ण
	अगर (WARN_ON(len_to_check != 0))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल bool is_test_sglist_corrupted(स्थिर काष्ठा test_sglist *tsgl)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < tsgl->nents; i++) अणु
		अगर (tsgl->sgl[i].page_link != tsgl->sgl_saved[i].page_link)
			वापस true;
		अगर (tsgl->sgl[i].offset != tsgl->sgl_saved[i].offset)
			वापस true;
		अगर (tsgl->sgl[i].length != tsgl->sgl_saved[i].length)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

काष्ठा cipher_test_sglists अणु
	काष्ठा test_sglist src;
	काष्ठा test_sglist dst;
पूर्ण;

अटल काष्ठा cipher_test_sglists *alloc_cipher_test_sglists(व्योम)
अणु
	काष्ठा cipher_test_sglists *tsgls;

	tsgls = kदो_स्मृति(माप(*tsgls), GFP_KERNEL);
	अगर (!tsgls)
		वापस शून्य;

	अगर (init_test_sglist(&tsgls->src) != 0)
		जाओ fail_kमुक्त;
	अगर (init_test_sglist(&tsgls->dst) != 0)
		जाओ fail_destroy_src;

	वापस tsgls;

fail_destroy_src:
	destroy_test_sglist(&tsgls->src);
fail_kमुक्त:
	kमुक्त(tsgls);
	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_cipher_test_sglists(काष्ठा cipher_test_sglists *tsgls)
अणु
	अगर (tsgls) अणु
		destroy_test_sglist(&tsgls->src);
		destroy_test_sglist(&tsgls->dst);
		kमुक्त(tsgls);
	पूर्ण
पूर्ण

/* Build the src and dst scatterlists क्रम an skcipher or AEAD test */
अटल पूर्णांक build_cipher_test_sglists(काष्ठा cipher_test_sglists *tsgls,
				     स्थिर काष्ठा testvec_config *cfg,
				     अचिन्हित पूर्णांक alignmask,
				     अचिन्हित पूर्णांक src_total_len,
				     अचिन्हित पूर्णांक dst_total_len,
				     स्थिर काष्ठा kvec *inमाला_दो,
				     अचिन्हित पूर्णांक nr_inमाला_दो)
अणु
	काष्ठा iov_iter input;
	पूर्णांक err;

	iov_iter_kvec(&input, WRITE, inमाला_दो, nr_inमाला_दो, src_total_len);
	err = build_test_sglist(&tsgls->src, cfg->src_भागs, alignmask,
				cfg->inplace ?
					max(dst_total_len, src_total_len) :
					src_total_len,
				&input, शून्य);
	अगर (err)
		वापस err;

	अगर (cfg->inplace) अणु
		tsgls->dst.sgl_ptr = tsgls->src.sgl;
		tsgls->dst.nents = tsgls->src.nents;
		वापस 0;
	पूर्ण
	वापस build_test_sglist(&tsgls->dst,
				 cfg->dst_भागs[0].proportion_of_total ?
					cfg->dst_भागs : cfg->src_भागs,
				 alignmask, dst_total_len, शून्य, शून्य);
पूर्ण

/*
 * Support क्रम testing passing a misaligned key to setkey():
 *
 * If cfg->key_offset is set, copy the key पूर्णांकo a new buffer at that offset,
 * optionally adding alignmask.  Else, just use the key directly.
 */
अटल पूर्णांक prepare_keybuf(स्थिर u8 *key, अचिन्हित पूर्णांक ksize,
			  स्थिर काष्ठा testvec_config *cfg,
			  अचिन्हित पूर्णांक alignmask,
			  स्थिर u8 **keybuf_ret, स्थिर u8 **keyptr_ret)
अणु
	अचिन्हित पूर्णांक key_offset = cfg->key_offset;
	u8 *keybuf = शून्य, *keyptr = (u8 *)key;

	अगर (key_offset != 0) अणु
		अगर (cfg->key_offset_relative_to_alignmask)
			key_offset += alignmask;
		keybuf = kदो_स्मृति(key_offset + ksize, GFP_KERNEL);
		अगर (!keybuf)
			वापस -ENOMEM;
		keyptr = keybuf + key_offset;
		स_नकल(keyptr, key, ksize);
	पूर्ण
	*keybuf_ret = keybuf;
	*keyptr_ret = keyptr;
	वापस 0;
पूर्ण

/* Like setkey_f(tfm, key, ksize), but someबार misalign the key */
#घोषणा करो_setkey(setkey_f, tfm, key, ksize, cfg, alignmask)		\
(अणु									\
	स्थिर u8 *keybuf, *keyptr;					\
	पूर्णांक err;							\
									\
	err = prepare_keybuf((key), (ksize), (cfg), (alignmask),	\
			     &keybuf, &keyptr);				\
	अगर (err == 0) अणु							\
		err = setkey_f((tfm), keyptr, (ksize));			\
		kमुक्त(keybuf);						\
	पूर्ण								\
	err;								\
पूर्ण)

#अगर_घोषित CONFIG_CRYPTO_MANAGER_EXTRA_TESTS

/* Generate a अक्रमom length in range [0, max_len], but prefer smaller values */
अटल अचिन्हित पूर्णांक generate_अक्रमom_length(अचिन्हित पूर्णांक max_len)
अणु
	अचिन्हित पूर्णांक len = pअक्रमom_u32() % (max_len + 1);

	चयन (pअक्रमom_u32() % 4) अणु
	हाल 0:
		वापस len % 64;
	हाल 1:
		वापस len % 256;
	हाल 2:
		वापस len % 1024;
	शेष:
		वापस len;
	पूर्ण
पूर्ण

/* Flip a अक्रमom bit in the given nonempty data buffer */
अटल व्योम flip_अक्रमom_bit(u8 *buf, माप_प्रकार size)
अणु
	माप_प्रकार bitpos;

	bitpos = pअक्रमom_u32() % (size * 8);
	buf[bitpos / 8] ^= 1 << (bitpos % 8);
पूर्ण

/* Flip a अक्रमom byte in the given nonempty data buffer */
अटल व्योम flip_अक्रमom_byte(u8 *buf, माप_प्रकार size)
अणु
	buf[pअक्रमom_u32() % size] ^= 0xff;
पूर्ण

/* Someबार make some अक्रमom changes to the given nonempty data buffer */
अटल व्योम mutate_buffer(u8 *buf, माप_प्रकार size)
अणु
	माप_प्रकार num_flips;
	माप_प्रकार i;

	/* Someबार flip some bits */
	अगर (pअक्रमom_u32() % 4 == 0) अणु
		num_flips = min_t(माप_प्रकार, 1 << (pअक्रमom_u32() % 8), size * 8);
		क्रम (i = 0; i < num_flips; i++)
			flip_अक्रमom_bit(buf, size);
	पूर्ण

	/* Someबार flip some bytes */
	अगर (pअक्रमom_u32() % 4 == 0) अणु
		num_flips = min_t(माप_प्रकार, 1 << (pअक्रमom_u32() % 8), size);
		क्रम (i = 0; i < num_flips; i++)
			flip_अक्रमom_byte(buf, size);
	पूर्ण
पूर्ण

/* Ranकरोmly generate 'count' bytes, but someबार make them "interesting" */
अटल व्योम generate_अक्रमom_bytes(u8 *buf, माप_प्रकार count)
अणु
	u8 b;
	u8 increment;
	माप_प्रकार i;

	अगर (count == 0)
		वापस;

	चयन (pअक्रमom_u32() % 8) अणु /* Choose a generation strategy */
	हाल 0:
	हाल 1:
		/* All the same byte, plus optional mutations */
		चयन (pअक्रमom_u32() % 4) अणु
		हाल 0:
			b = 0x00;
			अवरोध;
		हाल 1:
			b = 0xff;
			अवरोध;
		शेष:
			b = (u8)pअक्रमom_u32();
			अवरोध;
		पूर्ण
		स_रखो(buf, b, count);
		mutate_buffer(buf, count);
		अवरोध;
	हाल 2:
		/* Ascending or descending bytes, plus optional mutations */
		increment = (u8)pअक्रमom_u32();
		b = (u8)pअक्रमom_u32();
		क्रम (i = 0; i < count; i++, b += increment)
			buf[i] = b;
		mutate_buffer(buf, count);
		अवरोध;
	शेष:
		/* Fully अक्रमom bytes */
		क्रम (i = 0; i < count; i++)
			buf[i] = (u8)pअक्रमom_u32();
	पूर्ण
पूर्ण

अटल अक्षर *generate_अक्रमom_sgl_भागisions(काष्ठा test_sg_भागision *भागs,
					   माप_प्रकार max_भागs, अक्षर *p, अक्षर *end,
					   bool gen_flushes, u32 req_flags)
अणु
	काष्ठा test_sg_भागision *भाग = भागs;
	अचिन्हित पूर्णांक reमुख्यing = TEST_SG_TOTAL;

	करो अणु
		अचिन्हित पूर्णांक this_len;
		स्थिर अक्षर *flushtype_str;

		अगर (भाग == &भागs[max_भागs - 1] || pअक्रमom_u32() % 2 == 0)
			this_len = reमुख्यing;
		अन्यथा
			this_len = 1 + (pअक्रमom_u32() % reमुख्यing);
		भाग->proportion_of_total = this_len;

		अगर (pअक्रमom_u32() % 4 == 0)
			भाग->offset = (PAGE_SIZE - 128) + (pअक्रमom_u32() % 128);
		अन्यथा अगर (pअक्रमom_u32() % 2 == 0)
			भाग->offset = pअक्रमom_u32() % 32;
		अन्यथा
			भाग->offset = pअक्रमom_u32() % PAGE_SIZE;
		अगर (pअक्रमom_u32() % 8 == 0)
			भाग->offset_relative_to_alignmask = true;

		भाग->flush_type = FLUSH_TYPE_NONE;
		अगर (gen_flushes) अणु
			चयन (pअक्रमom_u32() % 4) अणु
			हाल 0:
				भाग->flush_type = FLUSH_TYPE_REIMPORT;
				अवरोध;
			हाल 1:
				भाग->flush_type = FLUSH_TYPE_FLUSH;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (भाग->flush_type != FLUSH_TYPE_NONE &&
		    !(req_flags & CRYPTO_TFM_REQ_MAY_SLEEP) &&
		    pअक्रमom_u32() % 2 == 0)
			भाग->nosimd = true;

		चयन (भाग->flush_type) अणु
		हाल FLUSH_TYPE_FLUSH:
			अगर (भाग->nosimd)
				flushtype_str = "<flush,nosimd>";
			अन्यथा
				flushtype_str = "<flush>";
			अवरोध;
		हाल FLUSH_TYPE_REIMPORT:
			अगर (भाग->nosimd)
				flushtype_str = "<reimport,nosimd>";
			अन्यथा
				flushtype_str = "<reimport>";
			अवरोध;
		शेष:
			flushtype_str = "";
			अवरोध;
		पूर्ण

		BUILD_BUG_ON(TEST_SG_TOTAL != 10000); /* क्रम "%u.%u%%" */
		p += scnम_लिखो(p, end - p, "%s%u.%u%%@%s+%u%s", flushtype_str,
			       this_len / 100, this_len % 100,
			       भाग->offset_relative_to_alignmask ?
					"alignmask" : "",
			       भाग->offset, this_len == reमुख्यing ? "" : ", ");
		reमुख्यing -= this_len;
		भाग++;
	पूर्ण जबतक (reमुख्यing);

	वापस p;
पूर्ण

/* Generate a अक्रमom testvec_config क्रम fuzz testing */
अटल व्योम generate_अक्रमom_testvec_config(काष्ठा testvec_config *cfg,
					   अक्षर *name, माप_प्रकार max_namelen)
अणु
	अक्षर *p = name;
	अक्षर * स्थिर end = name + max_namelen;

	स_रखो(cfg, 0, माप(*cfg));

	cfg->name = name;

	p += scnम_लिखो(p, end - p, "random:");

	अगर (pअक्रमom_u32() % 2 == 0) अणु
		cfg->inplace = true;
		p += scnम_लिखो(p, end - p, " inplace");
	पूर्ण

	अगर (pअक्रमom_u32() % 2 == 0) अणु
		cfg->req_flags |= CRYPTO_TFM_REQ_MAY_SLEEP;
		p += scnम_लिखो(p, end - p, " may_sleep");
	पूर्ण

	चयन (pअक्रमom_u32() % 4) अणु
	हाल 0:
		cfg->finalization_type = FINALIZATION_TYPE_FINAL;
		p += scnम_लिखो(p, end - p, " use_final");
		अवरोध;
	हाल 1:
		cfg->finalization_type = FINALIZATION_TYPE_FINUP;
		p += scnम_लिखो(p, end - p, " use_finup");
		अवरोध;
	शेष:
		cfg->finalization_type = FINALIZATION_TYPE_DIGEST;
		p += scnम_लिखो(p, end - p, " use_digest");
		अवरोध;
	पूर्ण

	अगर (!(cfg->req_flags & CRYPTO_TFM_REQ_MAY_SLEEP) &&
	    pअक्रमom_u32() % 2 == 0) अणु
		cfg->nosimd = true;
		p += scnम_लिखो(p, end - p, " nosimd");
	पूर्ण

	p += scnम_लिखो(p, end - p, " src_divs=[");
	p = generate_अक्रमom_sgl_भागisions(cfg->src_भागs,
					  ARRAY_SIZE(cfg->src_भागs), p, end,
					  (cfg->finalization_type !=
					   FINALIZATION_TYPE_DIGEST),
					  cfg->req_flags);
	p += scnम_लिखो(p, end - p, "]");

	अगर (!cfg->inplace && pअक्रमom_u32() % 2 == 0) अणु
		p += scnम_लिखो(p, end - p, " dst_divs=[");
		p = generate_अक्रमom_sgl_भागisions(cfg->dst_भागs,
						  ARRAY_SIZE(cfg->dst_भागs),
						  p, end, false,
						  cfg->req_flags);
		p += scnम_लिखो(p, end - p, "]");
	पूर्ण

	अगर (pअक्रमom_u32() % 2 == 0) अणु
		cfg->iv_offset = 1 + (pअक्रमom_u32() % MAX_ALGAPI_ALIGNMASK);
		p += scnम_लिखो(p, end - p, " iv_offset=%u", cfg->iv_offset);
	पूर्ण

	अगर (pअक्रमom_u32() % 2 == 0) अणु
		cfg->key_offset = 1 + (pअक्रमom_u32() % MAX_ALGAPI_ALIGNMASK);
		p += scnम_लिखो(p, end - p, " key_offset=%u", cfg->key_offset);
	पूर्ण

	WARN_ON_ONCE(!valid_testvec_config(cfg));
पूर्ण

अटल व्योम crypto_disable_simd_क्रम_test(व्योम)
अणु
	preempt_disable();
	__this_cpu_ग_लिखो(crypto_simd_disabled_क्रम_test, true);
पूर्ण

अटल व्योम crypto_reenable_simd_क्रम_test(व्योम)
अणु
	__this_cpu_ग_लिखो(crypto_simd_disabled_क्रम_test, false);
	preempt_enable();
पूर्ण

/*
 * Given an algorithm name, build the name of the generic implementation of that
 * algorithm, assuming the usual naming convention.  Specअगरically, this appends
 * "-generic" to every part of the name that is not a ढाँचा name.  Examples:
 *
 *	aes => aes-generic
 *	cbc(aes) => cbc(aes-generic)
 *	cts(cbc(aes)) => cts(cbc(aes-generic))
 *	rfc7539(chacha20,poly1305) => rfc7539(chacha20-generic,poly1305-generic)
 *
 * Return: 0 on success, or -ENAMETOOLONG अगर the generic name would be too दीर्घ
 */
अटल पूर्णांक build_generic_driver_name(स्थिर अक्षर *algname,
				     अक्षर driver_name[CRYPTO_MAX_ALG_NAME])
अणु
	स्थिर अक्षर *in = algname;
	अक्षर *out = driver_name;
	माप_प्रकार len = म_माप(algname);

	अगर (len >= CRYPTO_MAX_ALG_NAME)
		जाओ too_दीर्घ;
	करो अणु
		स्थिर अक्षर *in_saved = in;

		जबतक (*in && *in != '(' && *in != ')' && *in != ',')
			*out++ = *in++;
		अगर (*in != '(' && in > in_saved) अणु
			len += 8;
			अगर (len >= CRYPTO_MAX_ALG_NAME)
				जाओ too_दीर्घ;
			स_नकल(out, "-generic", 8);
			out += 8;
		पूर्ण
	पूर्ण जबतक ((*out++ = *in++) != '\0');
	वापस 0;

too_दीर्घ:
	pr_err("alg: generic driver name for \"%s\" would be too long\n",
	       algname);
	वापस -ENAMETOOLONG;
पूर्ण
#अन्यथा /* !CONFIG_CRYPTO_MANAGER_EXTRA_TESTS */
अटल व्योम crypto_disable_simd_क्रम_test(व्योम)
अणु
पूर्ण

अटल व्योम crypto_reenable_simd_क्रम_test(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_CRYPTO_MANAGER_EXTRA_TESTS */

अटल पूर्णांक build_hash_sglist(काष्ठा test_sglist *tsgl,
			     स्थिर काष्ठा hash_testvec *vec,
			     स्थिर काष्ठा testvec_config *cfg,
			     अचिन्हित पूर्णांक alignmask,
			     स्थिर काष्ठा test_sg_भागision *भागs[Xबफ_मानE])
अणु
	काष्ठा kvec kv;
	काष्ठा iov_iter input;

	kv.iov_base = (व्योम *)vec->plaपूर्णांकext;
	kv.iov_len = vec->psize;
	iov_iter_kvec(&input, WRITE, &kv, 1, vec->psize);
	वापस build_test_sglist(tsgl, cfg->src_भागs, alignmask, vec->psize,
				 &input, भागs);
पूर्ण

अटल पूर्णांक check_hash_result(स्थिर अक्षर *type,
			     स्थिर u8 *result, अचिन्हित पूर्णांक digestsize,
			     स्थिर काष्ठा hash_testvec *vec,
			     स्थिर अक्षर *vec_name,
			     स्थिर अक्षर *driver,
			     स्थिर काष्ठा testvec_config *cfg)
अणु
	अगर (स_भेद(result, vec->digest, digestsize) != 0) अणु
		pr_err("alg: %s: %s test failed (wrong result) on test vector %s, cfg=\"%s\"\n",
		       type, driver, vec_name, cfg->name);
		वापस -EINVAL;
	पूर्ण
	अगर (!tesपंचांगgr_is_poison(&result[digestsize], TESTMGR_POISON_LEN)) अणु
		pr_err("alg: %s: %s overran result buffer on test vector %s, cfg=\"%s\"\n",
		       type, driver, vec_name, cfg->name);
		वापस -EOVERFLOW;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक check_shash_op(स्थिर अक्षर *op, पूर्णांक err,
				 स्थिर अक्षर *driver, स्थिर अक्षर *vec_name,
				 स्थिर काष्ठा testvec_config *cfg)
अणु
	अगर (err)
		pr_err("alg: shash: %s %s() failed with err %d on test vector %s, cfg=\"%s\"\n",
		       driver, op, err, vec_name, cfg->name);
	वापस err;
पूर्ण

/* Test one hash test vector in one configuration, using the shash API */
अटल पूर्णांक test_shash_vec_cfg(स्थिर काष्ठा hash_testvec *vec,
			      स्थिर अक्षर *vec_name,
			      स्थिर काष्ठा testvec_config *cfg,
			      काष्ठा shash_desc *desc,
			      काष्ठा test_sglist *tsgl,
			      u8 *hashstate)
अणु
	काष्ठा crypto_shash *tfm = desc->tfm;
	स्थिर अचिन्हित पूर्णांक alignmask = crypto_shash_alignmask(tfm);
	स्थिर अचिन्हित पूर्णांक digestsize = crypto_shash_digestsize(tfm);
	स्थिर अचिन्हित पूर्णांक statesize = crypto_shash_statesize(tfm);
	स्थिर अक्षर *driver = crypto_shash_driver_name(tfm);
	स्थिर काष्ठा test_sg_भागision *भागs[Xबफ_मानE];
	अचिन्हित पूर्णांक i;
	u8 result[HASH_MAX_DIGESTSIZE + TESTMGR_POISON_LEN];
	पूर्णांक err;

	/* Set the key, अगर specअगरied */
	अगर (vec->ksize) अणु
		err = करो_setkey(crypto_shash_setkey, tfm, vec->key, vec->ksize,
				cfg, alignmask);
		अगर (err) अणु
			अगर (err == vec->setkey_error)
				वापस 0;
			pr_err("alg: shash: %s setkey failed on test vector %s; expected_error=%d, actual_error=%d, flags=%#x\n",
			       driver, vec_name, vec->setkey_error, err,
			       crypto_shash_get_flags(tfm));
			वापस err;
		पूर्ण
		अगर (vec->setkey_error) अणु
			pr_err("alg: shash: %s setkey unexpectedly succeeded on test vector %s; expected_error=%d\n",
			       driver, vec_name, vec->setkey_error);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Build the scatterlist क्रम the source data */
	err = build_hash_sglist(tsgl, vec, cfg, alignmask, भागs);
	अगर (err) अणु
		pr_err("alg: shash: %s: error preparing scatterlist for test vector %s, cfg=\"%s\"\n",
		       driver, vec_name, cfg->name);
		वापस err;
	पूर्ण

	/* Do the actual hashing */

	tesपंचांगgr_poison(desc->__ctx, crypto_shash_descsize(tfm));
	tesपंचांगgr_poison(result, digestsize + TESTMGR_POISON_LEN);

	अगर (cfg->finalization_type == FINALIZATION_TYPE_DIGEST ||
	    vec->digest_error) अणु
		/* Just using digest() */
		अगर (tsgl->nents != 1)
			वापस 0;
		अगर (cfg->nosimd)
			crypto_disable_simd_क्रम_test();
		err = crypto_shash_digest(desc, sg_virt(&tsgl->sgl[0]),
					  tsgl->sgl[0].length, result);
		अगर (cfg->nosimd)
			crypto_reenable_simd_क्रम_test();
		अगर (err) अणु
			अगर (err == vec->digest_error)
				वापस 0;
			pr_err("alg: shash: %s digest() failed on test vector %s; expected_error=%d, actual_error=%d, cfg=\"%s\"\n",
			       driver, vec_name, vec->digest_error, err,
			       cfg->name);
			वापस err;
		पूर्ण
		अगर (vec->digest_error) अणु
			pr_err("alg: shash: %s digest() unexpectedly succeeded on test vector %s; expected_error=%d, cfg=\"%s\"\n",
			       driver, vec_name, vec->digest_error, cfg->name);
			वापस -EINVAL;
		पूर्ण
		जाओ result_पढ़ोy;
	पूर्ण

	/* Using init(), zero or more update(), then final() or finup() */

	अगर (cfg->nosimd)
		crypto_disable_simd_क्रम_test();
	err = crypto_shash_init(desc);
	अगर (cfg->nosimd)
		crypto_reenable_simd_क्रम_test();
	err = check_shash_op("init", err, driver, vec_name, cfg);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < tsgl->nents; i++) अणु
		अगर (i + 1 == tsgl->nents &&
		    cfg->finalization_type == FINALIZATION_TYPE_FINUP) अणु
			अगर (भागs[i]->nosimd)
				crypto_disable_simd_क्रम_test();
			err = crypto_shash_finup(desc, sg_virt(&tsgl->sgl[i]),
						 tsgl->sgl[i].length, result);
			अगर (भागs[i]->nosimd)
				crypto_reenable_simd_क्रम_test();
			err = check_shash_op("finup", err, driver, vec_name,
					     cfg);
			अगर (err)
				वापस err;
			जाओ result_पढ़ोy;
		पूर्ण
		अगर (भागs[i]->nosimd)
			crypto_disable_simd_क्रम_test();
		err = crypto_shash_update(desc, sg_virt(&tsgl->sgl[i]),
					  tsgl->sgl[i].length);
		अगर (भागs[i]->nosimd)
			crypto_reenable_simd_क्रम_test();
		err = check_shash_op("update", err, driver, vec_name, cfg);
		अगर (err)
			वापस err;
		अगर (भागs[i]->flush_type == FLUSH_TYPE_REIMPORT) अणु
			/* Test ->export() and ->import() */
			tesपंचांगgr_poison(hashstate + statesize,
				       TESTMGR_POISON_LEN);
			err = crypto_shash_export(desc, hashstate);
			err = check_shash_op("export", err, driver, vec_name,
					     cfg);
			अगर (err)
				वापस err;
			अगर (!tesपंचांगgr_is_poison(hashstate + statesize,
					       TESTMGR_POISON_LEN)) अणु
				pr_err("alg: shash: %s export() overran state buffer on test vector %s, cfg=\"%s\"\n",
				       driver, vec_name, cfg->name);
				वापस -EOVERFLOW;
			पूर्ण
			tesपंचांगgr_poison(desc->__ctx, crypto_shash_descsize(tfm));
			err = crypto_shash_import(desc, hashstate);
			err = check_shash_op("import", err, driver, vec_name,
					     cfg);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (cfg->nosimd)
		crypto_disable_simd_क्रम_test();
	err = crypto_shash_final(desc, result);
	अगर (cfg->nosimd)
		crypto_reenable_simd_क्रम_test();
	err = check_shash_op("final", err, driver, vec_name, cfg);
	अगर (err)
		वापस err;
result_पढ़ोy:
	वापस check_hash_result("shash", result, digestsize, vec, vec_name,
				 driver, cfg);
पूर्ण

अटल पूर्णांक करो_ahash_op(पूर्णांक (*op)(काष्ठा ahash_request *req),
		       काष्ठा ahash_request *req,
		       काष्ठा crypto_रुको *रुको, bool nosimd)
अणु
	पूर्णांक err;

	अगर (nosimd)
		crypto_disable_simd_क्रम_test();

	err = op(req);

	अगर (nosimd)
		crypto_reenable_simd_क्रम_test();

	वापस crypto_रुको_req(err, रुको);
पूर्ण

अटल पूर्णांक check_nonfinal_ahash_op(स्थिर अक्षर *op, पूर्णांक err,
				   u8 *result, अचिन्हित पूर्णांक digestsize,
				   स्थिर अक्षर *driver, स्थिर अक्षर *vec_name,
				   स्थिर काष्ठा testvec_config *cfg)
अणु
	अगर (err) अणु
		pr_err("alg: ahash: %s %s() failed with err %d on test vector %s, cfg=\"%s\"\n",
		       driver, op, err, vec_name, cfg->name);
		वापस err;
	पूर्ण
	अगर (!tesपंचांगgr_is_poison(result, digestsize)) अणु
		pr_err("alg: ahash: %s %s() used result buffer on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Test one hash test vector in one configuration, using the ahash API */
अटल पूर्णांक test_ahash_vec_cfg(स्थिर काष्ठा hash_testvec *vec,
			      स्थिर अक्षर *vec_name,
			      स्थिर काष्ठा testvec_config *cfg,
			      काष्ठा ahash_request *req,
			      काष्ठा test_sglist *tsgl,
			      u8 *hashstate)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	स्थिर अचिन्हित पूर्णांक alignmask = crypto_ahash_alignmask(tfm);
	स्थिर अचिन्हित पूर्णांक digestsize = crypto_ahash_digestsize(tfm);
	स्थिर अचिन्हित पूर्णांक statesize = crypto_ahash_statesize(tfm);
	स्थिर अक्षर *driver = crypto_ahash_driver_name(tfm);
	स्थिर u32 req_flags = CRYPTO_TFM_REQ_MAY_BACKLOG | cfg->req_flags;
	स्थिर काष्ठा test_sg_भागision *भागs[Xबफ_मानE];
	DECLARE_CRYPTO_WAIT(रुको);
	अचिन्हित पूर्णांक i;
	काष्ठा scatterlist *pending_sgl;
	अचिन्हित पूर्णांक pending_len;
	u8 result[HASH_MAX_DIGESTSIZE + TESTMGR_POISON_LEN];
	पूर्णांक err;

	/* Set the key, अगर specअगरied */
	अगर (vec->ksize) अणु
		err = करो_setkey(crypto_ahash_setkey, tfm, vec->key, vec->ksize,
				cfg, alignmask);
		अगर (err) अणु
			अगर (err == vec->setkey_error)
				वापस 0;
			pr_err("alg: ahash: %s setkey failed on test vector %s; expected_error=%d, actual_error=%d, flags=%#x\n",
			       driver, vec_name, vec->setkey_error, err,
			       crypto_ahash_get_flags(tfm));
			वापस err;
		पूर्ण
		अगर (vec->setkey_error) अणु
			pr_err("alg: ahash: %s setkey unexpectedly succeeded on test vector %s; expected_error=%d\n",
			       driver, vec_name, vec->setkey_error);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Build the scatterlist क्रम the source data */
	err = build_hash_sglist(tsgl, vec, cfg, alignmask, भागs);
	अगर (err) अणु
		pr_err("alg: ahash: %s: error preparing scatterlist for test vector %s, cfg=\"%s\"\n",
		       driver, vec_name, cfg->name);
		वापस err;
	पूर्ण

	/* Do the actual hashing */

	tesपंचांगgr_poison(req->__ctx, crypto_ahash_reqsize(tfm));
	tesपंचांगgr_poison(result, digestsize + TESTMGR_POISON_LEN);

	अगर (cfg->finalization_type == FINALIZATION_TYPE_DIGEST ||
	    vec->digest_error) अणु
		/* Just using digest() */
		ahash_request_set_callback(req, req_flags, crypto_req_करोne,
					   &रुको);
		ahash_request_set_crypt(req, tsgl->sgl, result, vec->psize);
		err = करो_ahash_op(crypto_ahash_digest, req, &रुको, cfg->nosimd);
		अगर (err) अणु
			अगर (err == vec->digest_error)
				वापस 0;
			pr_err("alg: ahash: %s digest() failed on test vector %s; expected_error=%d, actual_error=%d, cfg=\"%s\"\n",
			       driver, vec_name, vec->digest_error, err,
			       cfg->name);
			वापस err;
		पूर्ण
		अगर (vec->digest_error) अणु
			pr_err("alg: ahash: %s digest() unexpectedly succeeded on test vector %s; expected_error=%d, cfg=\"%s\"\n",
			       driver, vec_name, vec->digest_error, cfg->name);
			वापस -EINVAL;
		पूर्ण
		जाओ result_पढ़ोy;
	पूर्ण

	/* Using init(), zero or more update(), then final() or finup() */

	ahash_request_set_callback(req, req_flags, crypto_req_करोne, &रुको);
	ahash_request_set_crypt(req, शून्य, result, 0);
	err = करो_ahash_op(crypto_ahash_init, req, &रुको, cfg->nosimd);
	err = check_nonfinal_ahash_op("init", err, result, digestsize,
				      driver, vec_name, cfg);
	अगर (err)
		वापस err;

	pending_sgl = शून्य;
	pending_len = 0;
	क्रम (i = 0; i < tsgl->nents; i++) अणु
		अगर (भागs[i]->flush_type != FLUSH_TYPE_NONE &&
		    pending_sgl != शून्य) अणु
			/* update() with the pending data */
			ahash_request_set_callback(req, req_flags,
						   crypto_req_करोne, &रुको);
			ahash_request_set_crypt(req, pending_sgl, result,
						pending_len);
			err = करो_ahash_op(crypto_ahash_update, req, &रुको,
					  भागs[i]->nosimd);
			err = check_nonfinal_ahash_op("update", err,
						      result, digestsize,
						      driver, vec_name, cfg);
			अगर (err)
				वापस err;
			pending_sgl = शून्य;
			pending_len = 0;
		पूर्ण
		अगर (भागs[i]->flush_type == FLUSH_TYPE_REIMPORT) अणु
			/* Test ->export() and ->import() */
			tesपंचांगgr_poison(hashstate + statesize,
				       TESTMGR_POISON_LEN);
			err = crypto_ahash_export(req, hashstate);
			err = check_nonfinal_ahash_op("export", err,
						      result, digestsize,
						      driver, vec_name, cfg);
			अगर (err)
				वापस err;
			अगर (!tesपंचांगgr_is_poison(hashstate + statesize,
					       TESTMGR_POISON_LEN)) अणु
				pr_err("alg: ahash: %s export() overran state buffer on test vector %s, cfg=\"%s\"\n",
				       driver, vec_name, cfg->name);
				वापस -EOVERFLOW;
			पूर्ण

			tesपंचांगgr_poison(req->__ctx, crypto_ahash_reqsize(tfm));
			err = crypto_ahash_import(req, hashstate);
			err = check_nonfinal_ahash_op("import", err,
						      result, digestsize,
						      driver, vec_name, cfg);
			अगर (err)
				वापस err;
		पूर्ण
		अगर (pending_sgl == शून्य)
			pending_sgl = &tsgl->sgl[i];
		pending_len += tsgl->sgl[i].length;
	पूर्ण

	ahash_request_set_callback(req, req_flags, crypto_req_करोne, &रुको);
	ahash_request_set_crypt(req, pending_sgl, result, pending_len);
	अगर (cfg->finalization_type == FINALIZATION_TYPE_FINAL) अणु
		/* finish with update() and final() */
		err = करो_ahash_op(crypto_ahash_update, req, &रुको, cfg->nosimd);
		err = check_nonfinal_ahash_op("update", err, result, digestsize,
					      driver, vec_name, cfg);
		अगर (err)
			वापस err;
		err = करो_ahash_op(crypto_ahash_final, req, &रुको, cfg->nosimd);
		अगर (err) अणु
			pr_err("alg: ahash: %s final() failed with err %d on test vector %s, cfg=\"%s\"\n",
			       driver, err, vec_name, cfg->name);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* finish with finup() */
		err = करो_ahash_op(crypto_ahash_finup, req, &रुको, cfg->nosimd);
		अगर (err) अणु
			pr_err("alg: ahash: %s finup() failed with err %d on test vector %s, cfg=\"%s\"\n",
			       driver, err, vec_name, cfg->name);
			वापस err;
		पूर्ण
	पूर्ण

result_पढ़ोy:
	वापस check_hash_result("ahash", result, digestsize, vec, vec_name,
				 driver, cfg);
पूर्ण

अटल पूर्णांक test_hash_vec_cfg(स्थिर काष्ठा hash_testvec *vec,
			     स्थिर अक्षर *vec_name,
			     स्थिर काष्ठा testvec_config *cfg,
			     काष्ठा ahash_request *req,
			     काष्ठा shash_desc *desc,
			     काष्ठा test_sglist *tsgl,
			     u8 *hashstate)
अणु
	पूर्णांक err;

	/*
	 * For algorithms implemented as "shash", most bugs will be detected by
	 * both the shash and ahash tests.  Test the shash API first so that the
	 * failures involve less indirection, so are easier to debug.
	 */

	अगर (desc) अणु
		err = test_shash_vec_cfg(vec, vec_name, cfg, desc, tsgl,
					 hashstate);
		अगर (err)
			वापस err;
	पूर्ण

	वापस test_ahash_vec_cfg(vec, vec_name, cfg, req, tsgl, hashstate);
पूर्ण

अटल पूर्णांक test_hash_vec(स्थिर काष्ठा hash_testvec *vec, अचिन्हित पूर्णांक vec_num,
			 काष्ठा ahash_request *req, काष्ठा shash_desc *desc,
			 काष्ठा test_sglist *tsgl, u8 *hashstate)
अणु
	अक्षर vec_name[16];
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	प्र_लिखो(vec_name, "%u", vec_num);

	क्रम (i = 0; i < ARRAY_SIZE(शेष_hash_testvec_configs); i++) अणु
		err = test_hash_vec_cfg(vec, vec_name,
					&शेष_hash_testvec_configs[i],
					req, desc, tsgl, hashstate);
		अगर (err)
			वापस err;
	पूर्ण

#अगर_घोषित CONFIG_CRYPTO_MANAGER_EXTRA_TESTS
	अगर (!noextratests) अणु
		काष्ठा testvec_config cfg;
		अक्षर cfgname[TESTVEC_CONFIG_NAMELEN];

		क्रम (i = 0; i < fuzz_iterations; i++) अणु
			generate_अक्रमom_testvec_config(&cfg, cfgname,
						       माप(cfgname));
			err = test_hash_vec_cfg(vec, vec_name, &cfg,
						req, desc, tsgl, hashstate);
			अगर (err)
				वापस err;
			cond_resched();
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CRYPTO_MANAGER_EXTRA_TESTS
/*
 * Generate a hash test vector from the given implementation.
 * Assumes the buffers in 'vec' were alपढ़ोy allocated.
 */
अटल व्योम generate_अक्रमom_hash_testvec(काष्ठा shash_desc *desc,
					 काष्ठा hash_testvec *vec,
					 अचिन्हित पूर्णांक maxkeysize,
					 अचिन्हित पूर्णांक maxdatasize,
					 अक्षर *name, माप_प्रकार max_namelen)
अणु
	/* Data */
	vec->psize = generate_अक्रमom_length(maxdatasize);
	generate_अक्रमom_bytes((u8 *)vec->plaपूर्णांकext, vec->psize);

	/*
	 * Key: length in range [1, maxkeysize], but usually choose maxkeysize.
	 * If algorithm is unkeyed, then maxkeysize == 0 and set ksize = 0.
	 */
	vec->setkey_error = 0;
	vec->ksize = 0;
	अगर (maxkeysize) अणु
		vec->ksize = maxkeysize;
		अगर (pअक्रमom_u32() % 4 == 0)
			vec->ksize = 1 + (pअक्रमom_u32() % maxkeysize);
		generate_अक्रमom_bytes((u8 *)vec->key, vec->ksize);

		vec->setkey_error = crypto_shash_setkey(desc->tfm, vec->key,
							vec->ksize);
		/* If the key couldn't be set, no need to जारी to digest. */
		अगर (vec->setkey_error)
			जाओ करोne;
	पूर्ण

	/* Digest */
	vec->digest_error = crypto_shash_digest(desc, vec->plaपूर्णांकext,
						vec->psize, (u8 *)vec->digest);
करोne:
	snम_लिखो(name, max_namelen, "\"random: psize=%u ksize=%u\"",
		 vec->psize, vec->ksize);
पूर्ण

/*
 * Test the hash algorithm represented by @req against the corresponding generic
 * implementation, अगर one is available.
 */
अटल पूर्णांक test_hash_vs_generic_impl(स्थिर अक्षर *generic_driver,
				     अचिन्हित पूर्णांक maxkeysize,
				     काष्ठा ahash_request *req,
				     काष्ठा shash_desc *desc,
				     काष्ठा test_sglist *tsgl,
				     u8 *hashstate)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	स्थिर अचिन्हित पूर्णांक digestsize = crypto_ahash_digestsize(tfm);
	स्थिर अचिन्हित पूर्णांक blocksize = crypto_ahash_blocksize(tfm);
	स्थिर अचिन्हित पूर्णांक maxdatasize = (2 * PAGE_SIZE) - TESTMGR_POISON_LEN;
	स्थिर अक्षर *algname = crypto_hash_alg_common(tfm)->base.cra_name;
	स्थिर अक्षर *driver = crypto_ahash_driver_name(tfm);
	अक्षर _generic_driver[CRYPTO_MAX_ALG_NAME];
	काष्ठा crypto_shash *generic_tfm = शून्य;
	काष्ठा shash_desc *generic_desc = शून्य;
	अचिन्हित पूर्णांक i;
	काष्ठा hash_testvec vec = अणु 0 पूर्ण;
	अक्षर vec_name[64];
	काष्ठा testvec_config *cfg;
	अक्षर cfgname[TESTVEC_CONFIG_NAMELEN];
	पूर्णांक err;

	अगर (noextratests)
		वापस 0;

	अगर (!generic_driver) अणु /* Use शेष naming convention? */
		err = build_generic_driver_name(algname, _generic_driver);
		अगर (err)
			वापस err;
		generic_driver = _generic_driver;
	पूर्ण

	अगर (म_भेद(generic_driver, driver) == 0) /* Alपढ़ोy the generic impl? */
		वापस 0;

	generic_tfm = crypto_alloc_shash(generic_driver, 0, 0);
	अगर (IS_ERR(generic_tfm)) अणु
		err = PTR_ERR(generic_tfm);
		अगर (err == -ENOENT) अणु
			pr_warn("alg: hash: skipping comparison tests for %s because %s is unavailable\n",
				driver, generic_driver);
			वापस 0;
		पूर्ण
		pr_err("alg: hash: error allocating %s (generic impl of %s): %d\n",
		       generic_driver, algname, err);
		वापस err;
	पूर्ण

	cfg = kzalloc(माप(*cfg), GFP_KERNEL);
	अगर (!cfg) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	generic_desc = kzalloc(माप(*desc) +
			       crypto_shash_descsize(generic_tfm), GFP_KERNEL);
	अगर (!generic_desc) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	generic_desc->tfm = generic_tfm;

	/* Check the algorithm properties क्रम consistency. */

	अगर (digestsize != crypto_shash_digestsize(generic_tfm)) अणु
		pr_err("alg: hash: digestsize for %s (%u) doesn't match generic impl (%u)\n",
		       driver, digestsize,
		       crypto_shash_digestsize(generic_tfm));
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (blocksize != crypto_shash_blocksize(generic_tfm)) अणु
		pr_err("alg: hash: blocksize for %s (%u) doesn't match generic impl (%u)\n",
		       driver, blocksize, crypto_shash_blocksize(generic_tfm));
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Now generate test vectors using the generic implementation, and test
	 * the other implementation against them.
	 */

	vec.key = kदो_स्मृति(maxkeysize, GFP_KERNEL);
	vec.plaपूर्णांकext = kदो_स्मृति(maxdatasize, GFP_KERNEL);
	vec.digest = kदो_स्मृति(digestsize, GFP_KERNEL);
	अगर (!vec.key || !vec.plaपूर्णांकext || !vec.digest) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < fuzz_iterations * 8; i++) अणु
		generate_अक्रमom_hash_testvec(generic_desc, &vec,
					     maxkeysize, maxdatasize,
					     vec_name, माप(vec_name));
		generate_अक्रमom_testvec_config(cfg, cfgname, माप(cfgname));

		err = test_hash_vec_cfg(&vec, vec_name, cfg,
					req, desc, tsgl, hashstate);
		अगर (err)
			जाओ out;
		cond_resched();
	पूर्ण
	err = 0;
out:
	kमुक्त(cfg);
	kमुक्त(vec.key);
	kमुक्त(vec.plaपूर्णांकext);
	kमुक्त(vec.digest);
	crypto_मुक्त_shash(generic_tfm);
	kमुक्त_sensitive(generic_desc);
	वापस err;
पूर्ण
#अन्यथा /* !CONFIG_CRYPTO_MANAGER_EXTRA_TESTS */
अटल पूर्णांक test_hash_vs_generic_impl(स्थिर अक्षर *generic_driver,
				     अचिन्हित पूर्णांक maxkeysize,
				     काष्ठा ahash_request *req,
				     काष्ठा shash_desc *desc,
				     काष्ठा test_sglist *tsgl,
				     u8 *hashstate)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_CRYPTO_MANAGER_EXTRA_TESTS */

अटल पूर्णांक alloc_shash(स्थिर अक्षर *driver, u32 type, u32 mask,
		       काष्ठा crypto_shash **tfm_ret,
		       काष्ठा shash_desc **desc_ret)
अणु
	काष्ठा crypto_shash *tfm;
	काष्ठा shash_desc *desc;

	tfm = crypto_alloc_shash(driver, type, mask);
	अगर (IS_ERR(tfm)) अणु
		अगर (PTR_ERR(tfm) == -ENOENT) अणु
			/*
			 * This algorithm is only available through the ahash
			 * API, not the shash API, so skip the shash tests.
			 */
			वापस 0;
		पूर्ण
		pr_err("alg: hash: failed to allocate shash transform for %s: %ld\n",
		       driver, PTR_ERR(tfm));
		वापस PTR_ERR(tfm);
	पूर्ण

	desc = kदो_स्मृति(माप(*desc) + crypto_shash_descsize(tfm), GFP_KERNEL);
	अगर (!desc) अणु
		crypto_मुक्त_shash(tfm);
		वापस -ENOMEM;
	पूर्ण
	desc->tfm = tfm;

	*tfm_ret = tfm;
	*desc_ret = desc;
	वापस 0;
पूर्ण

अटल पूर्णांक __alg_test_hash(स्थिर काष्ठा hash_testvec *vecs,
			   अचिन्हित पूर्णांक num_vecs, स्थिर अक्षर *driver,
			   u32 type, u32 mask,
			   स्थिर अक्षर *generic_driver, अचिन्हित पूर्णांक maxkeysize)
अणु
	काष्ठा crypto_ahash *atfm = शून्य;
	काष्ठा ahash_request *req = शून्य;
	काष्ठा crypto_shash *stfm = शून्य;
	काष्ठा shash_desc *desc = शून्य;
	काष्ठा test_sglist *tsgl = शून्य;
	u8 *hashstate = शून्य;
	अचिन्हित पूर्णांक statesize;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/*
	 * Always test the ahash API.  This works regardless of whether the
	 * algorithm is implemented as ahash or shash.
	 */

	atfm = crypto_alloc_ahash(driver, type, mask);
	अगर (IS_ERR(atfm)) अणु
		pr_err("alg: hash: failed to allocate transform for %s: %ld\n",
		       driver, PTR_ERR(atfm));
		वापस PTR_ERR(atfm);
	पूर्ण
	driver = crypto_ahash_driver_name(atfm);

	req = ahash_request_alloc(atfm, GFP_KERNEL);
	अगर (!req) अणु
		pr_err("alg: hash: failed to allocate request for %s\n",
		       driver);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * If available also test the shash API, to cover corner हालs that may
	 * be missed by testing the ahash API only.
	 */
	err = alloc_shash(driver, type, mask, &stfm, &desc);
	अगर (err)
		जाओ out;

	tsgl = kदो_स्मृति(माप(*tsgl), GFP_KERNEL);
	अगर (!tsgl || init_test_sglist(tsgl) != 0) अणु
		pr_err("alg: hash: failed to allocate test buffers for %s\n",
		       driver);
		kमुक्त(tsgl);
		tsgl = शून्य;
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	statesize = crypto_ahash_statesize(atfm);
	अगर (stfm)
		statesize = max(statesize, crypto_shash_statesize(stfm));
	hashstate = kदो_स्मृति(statesize + TESTMGR_POISON_LEN, GFP_KERNEL);
	अगर (!hashstate) अणु
		pr_err("alg: hash: failed to allocate hash state buffer for %s\n",
		       driver);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_vecs; i++) अणु
		err = test_hash_vec(&vecs[i], i, req, desc, tsgl, hashstate);
		अगर (err)
			जाओ out;
		cond_resched();
	पूर्ण
	err = test_hash_vs_generic_impl(generic_driver, maxkeysize, req,
					desc, tsgl, hashstate);
out:
	kमुक्त(hashstate);
	अगर (tsgl) अणु
		destroy_test_sglist(tsgl);
		kमुक्त(tsgl);
	पूर्ण
	kमुक्त(desc);
	crypto_मुक्त_shash(stfm);
	ahash_request_मुक्त(req);
	crypto_मुक्त_ahash(atfm);
	वापस err;
पूर्ण

अटल पूर्णांक alg_test_hash(स्थिर काष्ठा alg_test_desc *desc, स्थिर अक्षर *driver,
			 u32 type, u32 mask)
अणु
	स्थिर काष्ठा hash_testvec *ढाँचा = desc->suite.hash.vecs;
	अचिन्हित पूर्णांक tcount = desc->suite.hash.count;
	अचिन्हित पूर्णांक nr_unkeyed, nr_keyed;
	अचिन्हित पूर्णांक maxkeysize = 0;
	पूर्णांक err;

	/*
	 * For OPTIONAL_KEY algorithms, we have to करो all the unkeyed tests
	 * first, beक्रमe setting a key on the tfm.  To make this easier, we
	 * require that the unkeyed test vectors (अगर any) are listed first.
	 */

	क्रम (nr_unkeyed = 0; nr_unkeyed < tcount; nr_unkeyed++) अणु
		अगर (ढाँचा[nr_unkeyed].ksize)
			अवरोध;
	पूर्ण
	क्रम (nr_keyed = 0; nr_unkeyed + nr_keyed < tcount; nr_keyed++) अणु
		अगर (!ढाँचा[nr_unkeyed + nr_keyed].ksize) अणु
			pr_err("alg: hash: test vectors for %s out of order, "
			       "unkeyed ones must come first\n", desc->alg);
			वापस -EINVAL;
		पूर्ण
		maxkeysize = max_t(अचिन्हित पूर्णांक, maxkeysize,
				   ढाँचा[nr_unkeyed + nr_keyed].ksize);
	पूर्ण

	err = 0;
	अगर (nr_unkeyed) अणु
		err = __alg_test_hash(ढाँचा, nr_unkeyed, driver, type, mask,
				      desc->generic_driver, maxkeysize);
		ढाँचा += nr_unkeyed;
	पूर्ण

	अगर (!err && nr_keyed)
		err = __alg_test_hash(ढाँचा, nr_keyed, driver, type, mask,
				      desc->generic_driver, maxkeysize);

	वापस err;
पूर्ण

अटल पूर्णांक test_aead_vec_cfg(पूर्णांक enc, स्थिर काष्ठा aead_testvec *vec,
			     स्थिर अक्षर *vec_name,
			     स्थिर काष्ठा testvec_config *cfg,
			     काष्ठा aead_request *req,
			     काष्ठा cipher_test_sglists *tsgls)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	स्थिर अचिन्हित पूर्णांक alignmask = crypto_aead_alignmask(tfm);
	स्थिर अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(tfm);
	स्थिर अचिन्हित पूर्णांक authsize = vec->clen - vec->plen;
	स्थिर अक्षर *driver = crypto_aead_driver_name(tfm);
	स्थिर u32 req_flags = CRYPTO_TFM_REQ_MAY_BACKLOG | cfg->req_flags;
	स्थिर अक्षर *op = enc ? "encryption" : "decryption";
	DECLARE_CRYPTO_WAIT(रुको);
	u8 _iv[3 * (MAX_ALGAPI_ALIGNMASK + 1) + MAX_IVLEN];
	u8 *iv = PTR_ALIGN(&_iv[0], 2 * (MAX_ALGAPI_ALIGNMASK + 1)) +
		 cfg->iv_offset +
		 (cfg->iv_offset_relative_to_alignmask ? alignmask : 0);
	काष्ठा kvec input[2];
	पूर्णांक err;

	/* Set the key */
	अगर (vec->wk)
		crypto_aead_set_flags(tfm, CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	अन्यथा
		crypto_aead_clear_flags(tfm, CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);

	err = करो_setkey(crypto_aead_setkey, tfm, vec->key, vec->klen,
			cfg, alignmask);
	अगर (err && err != vec->setkey_error) अणु
		pr_err("alg: aead: %s setkey failed on test vector %s; expected_error=%d, actual_error=%d, flags=%#x\n",
		       driver, vec_name, vec->setkey_error, err,
		       crypto_aead_get_flags(tfm));
		वापस err;
	पूर्ण
	अगर (!err && vec->setkey_error) अणु
		pr_err("alg: aead: %s setkey unexpectedly succeeded on test vector %s; expected_error=%d\n",
		       driver, vec_name, vec->setkey_error);
		वापस -EINVAL;
	पूर्ण

	/* Set the authentication tag size */
	err = crypto_aead_setauthsize(tfm, authsize);
	अगर (err && err != vec->setauthsize_error) अणु
		pr_err("alg: aead: %s setauthsize failed on test vector %s; expected_error=%d, actual_error=%d\n",
		       driver, vec_name, vec->setauthsize_error, err);
		वापस err;
	पूर्ण
	अगर (!err && vec->setauthsize_error) अणु
		pr_err("alg: aead: %s setauthsize unexpectedly succeeded on test vector %s; expected_error=%d\n",
		       driver, vec_name, vec->setauthsize_error);
		वापस -EINVAL;
	पूर्ण

	अगर (vec->setkey_error || vec->setauthsize_error)
		वापस 0;

	/* The IV must be copied to a buffer, as the algorithm may modअगरy it */
	अगर (WARN_ON(ivsize > MAX_IVLEN))
		वापस -EINVAL;
	अगर (vec->iv)
		स_नकल(iv, vec->iv, ivsize);
	अन्यथा
		स_रखो(iv, 0, ivsize);

	/* Build the src/dst scatterlists */
	input[0].iov_base = (व्योम *)vec->assoc;
	input[0].iov_len = vec->alen;
	input[1].iov_base = enc ? (व्योम *)vec->ptext : (व्योम *)vec->ctext;
	input[1].iov_len = enc ? vec->plen : vec->clen;
	err = build_cipher_test_sglists(tsgls, cfg, alignmask,
					vec->alen + (enc ? vec->plen :
						     vec->clen),
					vec->alen + (enc ? vec->clen :
						     vec->plen),
					input, 2);
	अगर (err) अणु
		pr_err("alg: aead: %s %s: error preparing scatterlists for test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		वापस err;
	पूर्ण

	/* Do the actual encryption or decryption */
	tesपंचांगgr_poison(req->__ctx, crypto_aead_reqsize(tfm));
	aead_request_set_callback(req, req_flags, crypto_req_करोne, &रुको);
	aead_request_set_crypt(req, tsgls->src.sgl_ptr, tsgls->dst.sgl_ptr,
			       enc ? vec->plen : vec->clen, iv);
	aead_request_set_ad(req, vec->alen);
	अगर (cfg->nosimd)
		crypto_disable_simd_क्रम_test();
	err = enc ? crypto_aead_encrypt(req) : crypto_aead_decrypt(req);
	अगर (cfg->nosimd)
		crypto_reenable_simd_क्रम_test();
	err = crypto_रुको_req(err, &रुको);

	/* Check that the algorithm didn't overwrite things it shouldn't have */
	अगर (req->cryptlen != (enc ? vec->plen : vec->clen) ||
	    req->assoclen != vec->alen ||
	    req->iv != iv ||
	    req->src != tsgls->src.sgl_ptr ||
	    req->dst != tsgls->dst.sgl_ptr ||
	    crypto_aead_reqtfm(req) != tfm ||
	    req->base.complete != crypto_req_करोne ||
	    req->base.flags != req_flags ||
	    req->base.data != &रुको) अणु
		pr_err("alg: aead: %s %s corrupted request struct on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		अगर (req->cryptlen != (enc ? vec->plen : vec->clen))
			pr_err("alg: aead: changed 'req->cryptlen'\n");
		अगर (req->assoclen != vec->alen)
			pr_err("alg: aead: changed 'req->assoclen'\n");
		अगर (req->iv != iv)
			pr_err("alg: aead: changed 'req->iv'\n");
		अगर (req->src != tsgls->src.sgl_ptr)
			pr_err("alg: aead: changed 'req->src'\n");
		अगर (req->dst != tsgls->dst.sgl_ptr)
			pr_err("alg: aead: changed 'req->dst'\n");
		अगर (crypto_aead_reqtfm(req) != tfm)
			pr_err("alg: aead: changed 'req->base.tfm'\n");
		अगर (req->base.complete != crypto_req_करोne)
			pr_err("alg: aead: changed 'req->base.complete'\n");
		अगर (req->base.flags != req_flags)
			pr_err("alg: aead: changed 'req->base.flags'\n");
		अगर (req->base.data != &रुको)
			pr_err("alg: aead: changed 'req->base.data'\n");
		वापस -EINVAL;
	पूर्ण
	अगर (is_test_sglist_corrupted(&tsgls->src)) अणु
		pr_err("alg: aead: %s %s corrupted src sgl on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		वापस -EINVAL;
	पूर्ण
	अगर (tsgls->dst.sgl_ptr != tsgls->src.sgl &&
	    is_test_sglist_corrupted(&tsgls->dst)) अणु
		pr_err("alg: aead: %s %s corrupted dst sgl on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम unexpected success or failure, or wrong error code */
	अगर ((err == 0 && vec->novrfy) ||
	    (err != vec->crypt_error && !(err == -EBADMSG && vec->novrfy))) अणु
		अक्षर expected_error[32];

		अगर (vec->novrfy &&
		    vec->crypt_error != 0 && vec->crypt_error != -EBADMSG)
			प्र_लिखो(expected_error, "-EBADMSG or %d",
				vec->crypt_error);
		अन्यथा अगर (vec->novrfy)
			प्र_लिखो(expected_error, "-EBADMSG");
		अन्यथा
			प्र_लिखो(expected_error, "%d", vec->crypt_error);
		अगर (err) अणु
			pr_err("alg: aead: %s %s failed on test vector %s; expected_error=%s, actual_error=%d, cfg=\"%s\"\n",
			       driver, op, vec_name, expected_error, err,
			       cfg->name);
			वापस err;
		पूर्ण
		pr_err("alg: aead: %s %s unexpectedly succeeded on test vector %s; expected_error=%s, cfg=\"%s\"\n",
		       driver, op, vec_name, expected_error, cfg->name);
		वापस -EINVAL;
	पूर्ण
	अगर (err) /* Expectedly failed. */
		वापस 0;

	/* Check क्रम the correct output (ciphertext or plaपूर्णांकext) */
	err = verअगरy_correct_output(&tsgls->dst, enc ? vec->ctext : vec->ptext,
				    enc ? vec->clen : vec->plen,
				    vec->alen, enc || !cfg->inplace);
	अगर (err == -EOVERFLOW) अणु
		pr_err("alg: aead: %s %s overran dst buffer on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		वापस err;
	पूर्ण
	अगर (err) अणु
		pr_err("alg: aead: %s %s test failed (wrong result) on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक test_aead_vec(पूर्णांक enc, स्थिर काष्ठा aead_testvec *vec,
			 अचिन्हित पूर्णांक vec_num, काष्ठा aead_request *req,
			 काष्ठा cipher_test_sglists *tsgls)
अणु
	अक्षर vec_name[16];
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (enc && vec->novrfy)
		वापस 0;

	प्र_लिखो(vec_name, "%u", vec_num);

	क्रम (i = 0; i < ARRAY_SIZE(शेष_cipher_testvec_configs); i++) अणु
		err = test_aead_vec_cfg(enc, vec, vec_name,
					&शेष_cipher_testvec_configs[i],
					req, tsgls);
		अगर (err)
			वापस err;
	पूर्ण

#अगर_घोषित CONFIG_CRYPTO_MANAGER_EXTRA_TESTS
	अगर (!noextratests) अणु
		काष्ठा testvec_config cfg;
		अक्षर cfgname[TESTVEC_CONFIG_NAMELEN];

		क्रम (i = 0; i < fuzz_iterations; i++) अणु
			generate_अक्रमom_testvec_config(&cfg, cfgname,
						       माप(cfgname));
			err = test_aead_vec_cfg(enc, vec, vec_name,
						&cfg, req, tsgls);
			अगर (err)
				वापस err;
			cond_resched();
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CRYPTO_MANAGER_EXTRA_TESTS

काष्ठा aead_extra_tests_ctx अणु
	काष्ठा aead_request *req;
	काष्ठा crypto_aead *tfm;
	स्थिर काष्ठा alg_test_desc *test_desc;
	काष्ठा cipher_test_sglists *tsgls;
	अचिन्हित पूर्णांक maxdatasize;
	अचिन्हित पूर्णांक maxkeysize;

	काष्ठा aead_testvec vec;
	अक्षर vec_name[64];
	अक्षर cfgname[TESTVEC_CONFIG_NAMELEN];
	काष्ठा testvec_config cfg;
पूर्ण;

/*
 * Make at least one अक्रमom change to a (ciphertext, AAD) pair.  "Ciphertext"
 * here means the full ciphertext including the authentication tag.  The
 * authentication tag (and hence also the ciphertext) is assumed to be nonempty.
 */
अटल व्योम mutate_aead_message(काष्ठा aead_testvec *vec, bool aad_iv,
				अचिन्हित पूर्णांक ivsize)
अणु
	स्थिर अचिन्हित पूर्णांक aad_tail_size = aad_iv ? ivsize : 0;
	स्थिर अचिन्हित पूर्णांक authsize = vec->clen - vec->plen;

	अगर (pअक्रमom_u32() % 2 == 0 && vec->alen > aad_tail_size) अणु
		 /* Mutate the AAD */
		flip_अक्रमom_bit((u8 *)vec->assoc, vec->alen - aad_tail_size);
		अगर (pअक्रमom_u32() % 2 == 0)
			वापस;
	पूर्ण
	अगर (pअक्रमom_u32() % 2 == 0) अणु
		/* Mutate auth tag (assuming it's at the end of ciphertext) */
		flip_अक्रमom_bit((u8 *)vec->ctext + vec->plen, authsize);
	पूर्ण अन्यथा अणु
		/* Mutate any part of the ciphertext */
		flip_अक्रमom_bit((u8 *)vec->ctext, vec->clen);
	पूर्ण
पूर्ण

/*
 * Minimum authentication tag size in bytes at which we assume that we can
 * reliably generate inauthentic messages, i.e. not generate an authentic
 * message by chance.
 */
#घोषणा MIN_COLLISION_FREE_AUTHSIZE 8

अटल व्योम generate_aead_message(काष्ठा aead_request *req,
				  स्थिर काष्ठा aead_test_suite *suite,
				  काष्ठा aead_testvec *vec,
				  bool prefer_inauthentic)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	स्थिर अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(tfm);
	स्थिर अचिन्हित पूर्णांक authsize = vec->clen - vec->plen;
	स्थिर bool inauthentic = (authsize >= MIN_COLLISION_FREE_AUTHSIZE) &&
				 (prefer_inauthentic || pअक्रमom_u32() % 4 == 0);

	/* Generate the AAD. */
	generate_अक्रमom_bytes((u8 *)vec->assoc, vec->alen);
	अगर (suite->aad_iv && vec->alen >= ivsize)
		/* Aव्योम implementation-defined behavior. */
		स_नकल((u8 *)vec->assoc + vec->alen - ivsize, vec->iv, ivsize);

	अगर (inauthentic && pअक्रमom_u32() % 2 == 0) अणु
		/* Generate a अक्रमom ciphertext. */
		generate_अक्रमom_bytes((u8 *)vec->ctext, vec->clen);
	पूर्ण अन्यथा अणु
		पूर्णांक i = 0;
		काष्ठा scatterlist src[2], dst;
		u8 iv[MAX_IVLEN];
		DECLARE_CRYPTO_WAIT(रुको);

		/* Generate a अक्रमom plaपूर्णांकext and encrypt it. */
		sg_init_table(src, 2);
		अगर (vec->alen)
			sg_set_buf(&src[i++], vec->assoc, vec->alen);
		अगर (vec->plen) अणु
			generate_अक्रमom_bytes((u8 *)vec->ptext, vec->plen);
			sg_set_buf(&src[i++], vec->ptext, vec->plen);
		पूर्ण
		sg_init_one(&dst, vec->ctext, vec->alen + vec->clen);
		स_नकल(iv, vec->iv, ivsize);
		aead_request_set_callback(req, 0, crypto_req_करोne, &रुको);
		aead_request_set_crypt(req, src, &dst, vec->plen, iv);
		aead_request_set_ad(req, vec->alen);
		vec->crypt_error = crypto_रुको_req(crypto_aead_encrypt(req),
						   &रुको);
		/* If encryption failed, we're करोne. */
		अगर (vec->crypt_error != 0)
			वापस;
		स_हटाओ((u8 *)vec->ctext, vec->ctext + vec->alen, vec->clen);
		अगर (!inauthentic)
			वापस;
		/*
		 * Mutate the authentic (ciphertext, AAD) pair to get an
		 * inauthentic one.
		 */
		mutate_aead_message(vec, suite->aad_iv, ivsize);
	पूर्ण
	vec->novrfy = 1;
	अगर (suite->einval_allowed)
		vec->crypt_error = -EINVAL;
पूर्ण

/*
 * Generate an AEAD test vector 'vec' using the implementation specअगरied by
 * 'req'.  The buffers in 'vec' must alपढ़ोy be allocated.
 *
 * If 'prefer_inauthentic' is true, then this function will generate inauthentic
 * test vectors (i.e. vectors with 'vec->novrfy=1') more often.
 */
अटल व्योम generate_अक्रमom_aead_testvec(काष्ठा aead_request *req,
					 काष्ठा aead_testvec *vec,
					 स्थिर काष्ठा aead_test_suite *suite,
					 अचिन्हित पूर्णांक maxkeysize,
					 अचिन्हित पूर्णांक maxdatasize,
					 अक्षर *name, माप_प्रकार max_namelen,
					 bool prefer_inauthentic)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	स्थिर अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(tfm);
	स्थिर अचिन्हित पूर्णांक maxauthsize = crypto_aead_maxauthsize(tfm);
	अचिन्हित पूर्णांक authsize;
	अचिन्हित पूर्णांक total_len;

	/* Key: length in [0, maxkeysize], but usually choose maxkeysize */
	vec->klen = maxkeysize;
	अगर (pअक्रमom_u32() % 4 == 0)
		vec->klen = pअक्रमom_u32() % (maxkeysize + 1);
	generate_अक्रमom_bytes((u8 *)vec->key, vec->klen);
	vec->setkey_error = crypto_aead_setkey(tfm, vec->key, vec->klen);

	/* IV */
	generate_अक्रमom_bytes((u8 *)vec->iv, ivsize);

	/* Tag length: in [0, maxauthsize], but usually choose maxauthsize */
	authsize = maxauthsize;
	अगर (pअक्रमom_u32() % 4 == 0)
		authsize = pअक्रमom_u32() % (maxauthsize + 1);
	अगर (prefer_inauthentic && authsize < MIN_COLLISION_FREE_AUTHSIZE)
		authsize = MIN_COLLISION_FREE_AUTHSIZE;
	अगर (WARN_ON(authsize > maxdatasize))
		authsize = maxdatasize;
	maxdatasize -= authsize;
	vec->setauthsize_error = crypto_aead_setauthsize(tfm, authsize);

	/* AAD, plaपूर्णांकext, and ciphertext lengths */
	total_len = generate_अक्रमom_length(maxdatasize);
	अगर (pअक्रमom_u32() % 4 == 0)
		vec->alen = 0;
	अन्यथा
		vec->alen = generate_अक्रमom_length(total_len);
	vec->plen = total_len - vec->alen;
	vec->clen = vec->plen + authsize;

	/*
	 * Generate the AAD, plaपूर्णांकext, and ciphertext.  Not applicable अगर the
	 * key or the authentication tag size couldn't be set.
	 */
	vec->novrfy = 0;
	vec->crypt_error = 0;
	अगर (vec->setkey_error == 0 && vec->setauthsize_error == 0)
		generate_aead_message(req, suite, vec, prefer_inauthentic);
	snम_लिखो(name, max_namelen,
		 "\"random: alen=%u plen=%u authsize=%u klen=%u novrfy=%d\"",
		 vec->alen, vec->plen, authsize, vec->klen, vec->novrfy);
पूर्ण

अटल व्योम try_to_generate_inauthentic_testvec(
					काष्ठा aead_extra_tests_ctx *ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु
		generate_अक्रमom_aead_testvec(ctx->req, &ctx->vec,
					     &ctx->test_desc->suite.aead,
					     ctx->maxkeysize, ctx->maxdatasize,
					     ctx->vec_name,
					     माप(ctx->vec_name), true);
		अगर (ctx->vec.novrfy)
			वापस;
	पूर्ण
पूर्ण

/*
 * Generate inauthentic test vectors (i.e. ciphertext, AAD pairs that aren't the
 * result of an encryption with the key) and verअगरy that decryption fails.
 */
अटल पूर्णांक test_aead_inauthentic_inमाला_दो(काष्ठा aead_extra_tests_ctx *ctx)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < fuzz_iterations * 8; i++) अणु
		/*
		 * Since this part of the tests isn't comparing the
		 * implementation to another, there's no poपूर्णांक in testing any
		 * test vectors other than inauthentic ones (vec.novrfy=1) here.
		 *
		 * If we're having trouble generating such a test vector, e.g.
		 * अगर the algorithm keeps rejecting the generated keys, करोn't
		 * retry क्रमever; just जारी on.
		 */
		try_to_generate_inauthentic_testvec(ctx);
		अगर (ctx->vec.novrfy) अणु
			generate_अक्रमom_testvec_config(&ctx->cfg, ctx->cfgname,
						       माप(ctx->cfgname));
			err = test_aead_vec_cfg(DECRYPT, &ctx->vec,
						ctx->vec_name, &ctx->cfg,
						ctx->req, ctx->tsgls);
			अगर (err)
				वापस err;
		पूर्ण
		cond_resched();
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Test the AEAD algorithm against the corresponding generic implementation, अगर
 * one is available.
 */
अटल पूर्णांक test_aead_vs_generic_impl(काष्ठा aead_extra_tests_ctx *ctx)
अणु
	काष्ठा crypto_aead *tfm = ctx->tfm;
	स्थिर अक्षर *algname = crypto_aead_alg(tfm)->base.cra_name;
	स्थिर अक्षर *driver = crypto_aead_driver_name(tfm);
	स्थिर अक्षर *generic_driver = ctx->test_desc->generic_driver;
	अक्षर _generic_driver[CRYPTO_MAX_ALG_NAME];
	काष्ठा crypto_aead *generic_tfm = शून्य;
	काष्ठा aead_request *generic_req = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (!generic_driver) अणु /* Use शेष naming convention? */
		err = build_generic_driver_name(algname, _generic_driver);
		अगर (err)
			वापस err;
		generic_driver = _generic_driver;
	पूर्ण

	अगर (म_भेद(generic_driver, driver) == 0) /* Alपढ़ोy the generic impl? */
		वापस 0;

	generic_tfm = crypto_alloc_aead(generic_driver, 0, 0);
	अगर (IS_ERR(generic_tfm)) अणु
		err = PTR_ERR(generic_tfm);
		अगर (err == -ENOENT) अणु
			pr_warn("alg: aead: skipping comparison tests for %s because %s is unavailable\n",
				driver, generic_driver);
			वापस 0;
		पूर्ण
		pr_err("alg: aead: error allocating %s (generic impl of %s): %d\n",
		       generic_driver, algname, err);
		वापस err;
	पूर्ण

	generic_req = aead_request_alloc(generic_tfm, GFP_KERNEL);
	अगर (!generic_req) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Check the algorithm properties क्रम consistency. */

	अगर (crypto_aead_maxauthsize(tfm) !=
	    crypto_aead_maxauthsize(generic_tfm)) अणु
		pr_err("alg: aead: maxauthsize for %s (%u) doesn't match generic impl (%u)\n",
		       driver, crypto_aead_maxauthsize(tfm),
		       crypto_aead_maxauthsize(generic_tfm));
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (crypto_aead_ivsize(tfm) != crypto_aead_ivsize(generic_tfm)) अणु
		pr_err("alg: aead: ivsize for %s (%u) doesn't match generic impl (%u)\n",
		       driver, crypto_aead_ivsize(tfm),
		       crypto_aead_ivsize(generic_tfm));
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (crypto_aead_blocksize(tfm) != crypto_aead_blocksize(generic_tfm)) अणु
		pr_err("alg: aead: blocksize for %s (%u) doesn't match generic impl (%u)\n",
		       driver, crypto_aead_blocksize(tfm),
		       crypto_aead_blocksize(generic_tfm));
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Now generate test vectors using the generic implementation, and test
	 * the other implementation against them.
	 */
	क्रम (i = 0; i < fuzz_iterations * 8; i++) अणु
		generate_अक्रमom_aead_testvec(generic_req, &ctx->vec,
					     &ctx->test_desc->suite.aead,
					     ctx->maxkeysize, ctx->maxdatasize,
					     ctx->vec_name,
					     माप(ctx->vec_name), false);
		generate_अक्रमom_testvec_config(&ctx->cfg, ctx->cfgname,
					       माप(ctx->cfgname));
		अगर (!ctx->vec.novrfy) अणु
			err = test_aead_vec_cfg(ENCRYPT, &ctx->vec,
						ctx->vec_name, &ctx->cfg,
						ctx->req, ctx->tsgls);
			अगर (err)
				जाओ out;
		पूर्ण
		अगर (ctx->vec.crypt_error == 0 || ctx->vec.novrfy) अणु
			err = test_aead_vec_cfg(DECRYPT, &ctx->vec,
						ctx->vec_name, &ctx->cfg,
						ctx->req, ctx->tsgls);
			अगर (err)
				जाओ out;
		पूर्ण
		cond_resched();
	पूर्ण
	err = 0;
out:
	crypto_मुक्त_aead(generic_tfm);
	aead_request_मुक्त(generic_req);
	वापस err;
पूर्ण

अटल पूर्णांक test_aead_extra(स्थिर काष्ठा alg_test_desc *test_desc,
			   काष्ठा aead_request *req,
			   काष्ठा cipher_test_sglists *tsgls)
अणु
	काष्ठा aead_extra_tests_ctx *ctx;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (noextratests)
		वापस 0;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->req = req;
	ctx->tfm = crypto_aead_reqtfm(req);
	ctx->test_desc = test_desc;
	ctx->tsgls = tsgls;
	ctx->maxdatasize = (2 * PAGE_SIZE) - TESTMGR_POISON_LEN;
	ctx->maxkeysize = 0;
	क्रम (i = 0; i < test_desc->suite.aead.count; i++)
		ctx->maxkeysize = max_t(अचिन्हित पूर्णांक, ctx->maxkeysize,
					test_desc->suite.aead.vecs[i].klen);

	ctx->vec.key = kदो_स्मृति(ctx->maxkeysize, GFP_KERNEL);
	ctx->vec.iv = kदो_स्मृति(crypto_aead_ivsize(ctx->tfm), GFP_KERNEL);
	ctx->vec.assoc = kदो_स्मृति(ctx->maxdatasize, GFP_KERNEL);
	ctx->vec.ptext = kदो_स्मृति(ctx->maxdatasize, GFP_KERNEL);
	ctx->vec.ctext = kदो_स्मृति(ctx->maxdatasize, GFP_KERNEL);
	अगर (!ctx->vec.key || !ctx->vec.iv || !ctx->vec.assoc ||
	    !ctx->vec.ptext || !ctx->vec.ctext) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = test_aead_vs_generic_impl(ctx);
	अगर (err)
		जाओ out;

	err = test_aead_inauthentic_inमाला_दो(ctx);
out:
	kमुक्त(ctx->vec.key);
	kमुक्त(ctx->vec.iv);
	kमुक्त(ctx->vec.assoc);
	kमुक्त(ctx->vec.ptext);
	kमुक्त(ctx->vec.ctext);
	kमुक्त(ctx);
	वापस err;
पूर्ण
#अन्यथा /* !CONFIG_CRYPTO_MANAGER_EXTRA_TESTS */
अटल पूर्णांक test_aead_extra(स्थिर काष्ठा alg_test_desc *test_desc,
			   काष्ठा aead_request *req,
			   काष्ठा cipher_test_sglists *tsgls)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_CRYPTO_MANAGER_EXTRA_TESTS */

अटल पूर्णांक test_aead(पूर्णांक enc, स्थिर काष्ठा aead_test_suite *suite,
		     काष्ठा aead_request *req,
		     काष्ठा cipher_test_sglists *tsgls)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < suite->count; i++) अणु
		err = test_aead_vec(enc, &suite->vecs[i], i, req, tsgls);
		अगर (err)
			वापस err;
		cond_resched();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक alg_test_aead(स्थिर काष्ठा alg_test_desc *desc, स्थिर अक्षर *driver,
			 u32 type, u32 mask)
अणु
	स्थिर काष्ठा aead_test_suite *suite = &desc->suite.aead;
	काष्ठा crypto_aead *tfm;
	काष्ठा aead_request *req = शून्य;
	काष्ठा cipher_test_sglists *tsgls = शून्य;
	पूर्णांक err;

	अगर (suite->count <= 0) अणु
		pr_err("alg: aead: empty test suite for %s\n", driver);
		वापस -EINVAL;
	पूर्ण

	tfm = crypto_alloc_aead(driver, type, mask);
	अगर (IS_ERR(tfm)) अणु
		pr_err("alg: aead: failed to allocate transform for %s: %ld\n",
		       driver, PTR_ERR(tfm));
		वापस PTR_ERR(tfm);
	पूर्ण
	driver = crypto_aead_driver_name(tfm);

	req = aead_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		pr_err("alg: aead: failed to allocate request for %s\n",
		       driver);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	tsgls = alloc_cipher_test_sglists();
	अगर (!tsgls) अणु
		pr_err("alg: aead: failed to allocate test buffers for %s\n",
		       driver);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = test_aead(ENCRYPT, suite, req, tsgls);
	अगर (err)
		जाओ out;

	err = test_aead(DECRYPT, suite, req, tsgls);
	अगर (err)
		जाओ out;

	err = test_aead_extra(desc, req, tsgls);
out:
	मुक्त_cipher_test_sglists(tsgls);
	aead_request_मुक्त(req);
	crypto_मुक्त_aead(tfm);
	वापस err;
पूर्ण

अटल पूर्णांक test_cipher(काष्ठा crypto_cipher *tfm, पूर्णांक enc,
		       स्थिर काष्ठा cipher_testvec *ढाँचा,
		       अचिन्हित पूर्णांक tcount)
अणु
	स्थिर अक्षर *algo = crypto_tfm_alg_driver_name(crypto_cipher_tfm(tfm));
	अचिन्हित पूर्णांक i, j, k;
	अक्षर *q;
	स्थिर अक्षर *e;
	स्थिर अक्षर *input, *result;
	व्योम *data;
	अक्षर *xbuf[Xबफ_मानE];
	पूर्णांक ret = -ENOMEM;

	अगर (tesपंचांगgr_alloc_buf(xbuf))
		जाओ out_nobuf;

	अगर (enc == ENCRYPT)
	        e = "encryption";
	अन्यथा
		e = "decryption";

	j = 0;
	क्रम (i = 0; i < tcount; i++) अणु

		अगर (fips_enabled && ढाँचा[i].fips_skip)
			जारी;

		input  = enc ? ढाँचा[i].ptext : ढाँचा[i].ctext;
		result = enc ? ढाँचा[i].ctext : ढाँचा[i].ptext;
		j++;

		ret = -EINVAL;
		अगर (WARN_ON(ढाँचा[i].len > PAGE_SIZE))
			जाओ out;

		data = xbuf[0];
		स_नकल(data, input, ढाँचा[i].len);

		crypto_cipher_clear_flags(tfm, ~0);
		अगर (ढाँचा[i].wk)
			crypto_cipher_set_flags(tfm, CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);

		ret = crypto_cipher_setkey(tfm, ढाँचा[i].key,
					   ढाँचा[i].klen);
		अगर (ret) अणु
			अगर (ret == ढाँचा[i].setkey_error)
				जारी;
			pr_err("alg: cipher: %s setkey failed on test vector %u; expected_error=%d, actual_error=%d, flags=%#x\n",
			       algo, j, ढाँचा[i].setkey_error, ret,
			       crypto_cipher_get_flags(tfm));
			जाओ out;
		पूर्ण
		अगर (ढाँचा[i].setkey_error) अणु
			pr_err("alg: cipher: %s setkey unexpectedly succeeded on test vector %u; expected_error=%d\n",
			       algo, j, ढाँचा[i].setkey_error);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		क्रम (k = 0; k < ढाँचा[i].len;
		     k += crypto_cipher_blocksize(tfm)) अणु
			अगर (enc)
				crypto_cipher_encrypt_one(tfm, data + k,
							  data + k);
			अन्यथा
				crypto_cipher_decrypt_one(tfm, data + k,
							  data + k);
		पूर्ण

		q = data;
		अगर (स_भेद(q, result, ढाँचा[i].len)) अणु
			prपूर्णांकk(KERN_ERR "alg: cipher: Test %d failed "
			       "on %s for %s\n", j, e, algo);
			hexdump(q, ढाँचा[i].len);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = 0;

out:
	tesपंचांगgr_मुक्त_buf(xbuf);
out_nobuf:
	वापस ret;
पूर्ण

अटल पूर्णांक test_skcipher_vec_cfg(पूर्णांक enc, स्थिर काष्ठा cipher_testvec *vec,
				 स्थिर अक्षर *vec_name,
				 स्थिर काष्ठा testvec_config *cfg,
				 काष्ठा skcipher_request *req,
				 काष्ठा cipher_test_sglists *tsgls)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर अचिन्हित पूर्णांक alignmask = crypto_skcipher_alignmask(tfm);
	स्थिर अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(tfm);
	स्थिर अक्षर *driver = crypto_skcipher_driver_name(tfm);
	स्थिर u32 req_flags = CRYPTO_TFM_REQ_MAY_BACKLOG | cfg->req_flags;
	स्थिर अक्षर *op = enc ? "encryption" : "decryption";
	DECLARE_CRYPTO_WAIT(रुको);
	u8 _iv[3 * (MAX_ALGAPI_ALIGNMASK + 1) + MAX_IVLEN];
	u8 *iv = PTR_ALIGN(&_iv[0], 2 * (MAX_ALGAPI_ALIGNMASK + 1)) +
		 cfg->iv_offset +
		 (cfg->iv_offset_relative_to_alignmask ? alignmask : 0);
	काष्ठा kvec input;
	पूर्णांक err;

	/* Set the key */
	अगर (vec->wk)
		crypto_skcipher_set_flags(tfm, CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	अन्यथा
		crypto_skcipher_clear_flags(tfm,
					    CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	err = करो_setkey(crypto_skcipher_setkey, tfm, vec->key, vec->klen,
			cfg, alignmask);
	अगर (err) अणु
		अगर (err == vec->setkey_error)
			वापस 0;
		pr_err("alg: skcipher: %s setkey failed on test vector %s; expected_error=%d, actual_error=%d, flags=%#x\n",
		       driver, vec_name, vec->setkey_error, err,
		       crypto_skcipher_get_flags(tfm));
		वापस err;
	पूर्ण
	अगर (vec->setkey_error) अणु
		pr_err("alg: skcipher: %s setkey unexpectedly succeeded on test vector %s; expected_error=%d\n",
		       driver, vec_name, vec->setkey_error);
		वापस -EINVAL;
	पूर्ण

	/* The IV must be copied to a buffer, as the algorithm may modअगरy it */
	अगर (ivsize) अणु
		अगर (WARN_ON(ivsize > MAX_IVLEN))
			वापस -EINVAL;
		अगर (vec->generates_iv && !enc)
			स_नकल(iv, vec->iv_out, ivsize);
		अन्यथा अगर (vec->iv)
			स_नकल(iv, vec->iv, ivsize);
		अन्यथा
			स_रखो(iv, 0, ivsize);
	पूर्ण अन्यथा अणु
		अगर (vec->generates_iv) अणु
			pr_err("alg: skcipher: %s has ivsize=0 but test vector %s generates IV!\n",
			       driver, vec_name);
			वापस -EINVAL;
		पूर्ण
		iv = शून्य;
	पूर्ण

	/* Build the src/dst scatterlists */
	input.iov_base = enc ? (व्योम *)vec->ptext : (व्योम *)vec->ctext;
	input.iov_len = vec->len;
	err = build_cipher_test_sglists(tsgls, cfg, alignmask,
					vec->len, vec->len, &input, 1);
	अगर (err) अणु
		pr_err("alg: skcipher: %s %s: error preparing scatterlists for test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		वापस err;
	पूर्ण

	/* Do the actual encryption or decryption */
	tesपंचांगgr_poison(req->__ctx, crypto_skcipher_reqsize(tfm));
	skcipher_request_set_callback(req, req_flags, crypto_req_करोne, &रुको);
	skcipher_request_set_crypt(req, tsgls->src.sgl_ptr, tsgls->dst.sgl_ptr,
				   vec->len, iv);
	अगर (cfg->nosimd)
		crypto_disable_simd_क्रम_test();
	err = enc ? crypto_skcipher_encrypt(req) : crypto_skcipher_decrypt(req);
	अगर (cfg->nosimd)
		crypto_reenable_simd_क्रम_test();
	err = crypto_रुको_req(err, &रुको);

	/* Check that the algorithm didn't overwrite things it shouldn't have */
	अगर (req->cryptlen != vec->len ||
	    req->iv != iv ||
	    req->src != tsgls->src.sgl_ptr ||
	    req->dst != tsgls->dst.sgl_ptr ||
	    crypto_skcipher_reqtfm(req) != tfm ||
	    req->base.complete != crypto_req_करोne ||
	    req->base.flags != req_flags ||
	    req->base.data != &रुको) अणु
		pr_err("alg: skcipher: %s %s corrupted request struct on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		अगर (req->cryptlen != vec->len)
			pr_err("alg: skcipher: changed 'req->cryptlen'\n");
		अगर (req->iv != iv)
			pr_err("alg: skcipher: changed 'req->iv'\n");
		अगर (req->src != tsgls->src.sgl_ptr)
			pr_err("alg: skcipher: changed 'req->src'\n");
		अगर (req->dst != tsgls->dst.sgl_ptr)
			pr_err("alg: skcipher: changed 'req->dst'\n");
		अगर (crypto_skcipher_reqtfm(req) != tfm)
			pr_err("alg: skcipher: changed 'req->base.tfm'\n");
		अगर (req->base.complete != crypto_req_करोne)
			pr_err("alg: skcipher: changed 'req->base.complete'\n");
		अगर (req->base.flags != req_flags)
			pr_err("alg: skcipher: changed 'req->base.flags'\n");
		अगर (req->base.data != &रुको)
			pr_err("alg: skcipher: changed 'req->base.data'\n");
		वापस -EINVAL;
	पूर्ण
	अगर (is_test_sglist_corrupted(&tsgls->src)) अणु
		pr_err("alg: skcipher: %s %s corrupted src sgl on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		वापस -EINVAL;
	पूर्ण
	अगर (tsgls->dst.sgl_ptr != tsgls->src.sgl &&
	    is_test_sglist_corrupted(&tsgls->dst)) अणु
		pr_err("alg: skcipher: %s %s corrupted dst sgl on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम success or failure */
	अगर (err) अणु
		अगर (err == vec->crypt_error)
			वापस 0;
		pr_err("alg: skcipher: %s %s failed on test vector %s; expected_error=%d, actual_error=%d, cfg=\"%s\"\n",
		       driver, op, vec_name, vec->crypt_error, err, cfg->name);
		वापस err;
	पूर्ण
	अगर (vec->crypt_error) अणु
		pr_err("alg: skcipher: %s %s unexpectedly succeeded on test vector %s; expected_error=%d, cfg=\"%s\"\n",
		       driver, op, vec_name, vec->crypt_error, cfg->name);
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम the correct output (ciphertext or plaपूर्णांकext) */
	err = verअगरy_correct_output(&tsgls->dst, enc ? vec->ctext : vec->ptext,
				    vec->len, 0, true);
	अगर (err == -EOVERFLOW) अणु
		pr_err("alg: skcipher: %s %s overran dst buffer on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		वापस err;
	पूर्ण
	अगर (err) अणु
		pr_err("alg: skcipher: %s %s test failed (wrong result) on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		वापस err;
	पूर्ण

	/* If applicable, check that the algorithm generated the correct IV */
	अगर (vec->iv_out && स_भेद(iv, vec->iv_out, ivsize) != 0) अणु
		pr_err("alg: skcipher: %s %s test failed (wrong output IV) on test vector %s, cfg=\"%s\"\n",
		       driver, op, vec_name, cfg->name);
		hexdump(iv, ivsize);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक test_skcipher_vec(पूर्णांक enc, स्थिर काष्ठा cipher_testvec *vec,
			     अचिन्हित पूर्णांक vec_num,
			     काष्ठा skcipher_request *req,
			     काष्ठा cipher_test_sglists *tsgls)
अणु
	अक्षर vec_name[16];
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (fips_enabled && vec->fips_skip)
		वापस 0;

	प्र_लिखो(vec_name, "%u", vec_num);

	क्रम (i = 0; i < ARRAY_SIZE(शेष_cipher_testvec_configs); i++) अणु
		err = test_skcipher_vec_cfg(enc, vec, vec_name,
					    &शेष_cipher_testvec_configs[i],
					    req, tsgls);
		अगर (err)
			वापस err;
	पूर्ण

#अगर_घोषित CONFIG_CRYPTO_MANAGER_EXTRA_TESTS
	अगर (!noextratests) अणु
		काष्ठा testvec_config cfg;
		अक्षर cfgname[TESTVEC_CONFIG_NAMELEN];

		क्रम (i = 0; i < fuzz_iterations; i++) अणु
			generate_अक्रमom_testvec_config(&cfg, cfgname,
						       माप(cfgname));
			err = test_skcipher_vec_cfg(enc, vec, vec_name,
						    &cfg, req, tsgls);
			अगर (err)
				वापस err;
			cond_resched();
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CRYPTO_MANAGER_EXTRA_TESTS
/*
 * Generate a symmetric cipher test vector from the given implementation.
 * Assumes the buffers in 'vec' were alपढ़ोy allocated.
 */
अटल व्योम generate_अक्रमom_cipher_testvec(काष्ठा skcipher_request *req,
					   काष्ठा cipher_testvec *vec,
					   अचिन्हित पूर्णांक maxdatasize,
					   अक्षर *name, माप_प्रकार max_namelen)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर अचिन्हित पूर्णांक maxkeysize = crypto_skcipher_max_keysize(tfm);
	स्थिर अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(tfm);
	काष्ठा scatterlist src, dst;
	u8 iv[MAX_IVLEN];
	DECLARE_CRYPTO_WAIT(रुको);

	/* Key: length in [0, maxkeysize], but usually choose maxkeysize */
	vec->klen = maxkeysize;
	अगर (pअक्रमom_u32() % 4 == 0)
		vec->klen = pअक्रमom_u32() % (maxkeysize + 1);
	generate_अक्रमom_bytes((u8 *)vec->key, vec->klen);
	vec->setkey_error = crypto_skcipher_setkey(tfm, vec->key, vec->klen);

	/* IV */
	generate_अक्रमom_bytes((u8 *)vec->iv, ivsize);

	/* Plaपूर्णांकext */
	vec->len = generate_अक्रमom_length(maxdatasize);
	generate_अक्रमom_bytes((u8 *)vec->ptext, vec->len);

	/* If the key couldn't be set, no need to जारी to encrypt. */
	अगर (vec->setkey_error)
		जाओ करोne;

	/* Ciphertext */
	sg_init_one(&src, vec->ptext, vec->len);
	sg_init_one(&dst, vec->ctext, vec->len);
	स_नकल(iv, vec->iv, ivsize);
	skcipher_request_set_callback(req, 0, crypto_req_करोne, &रुको);
	skcipher_request_set_crypt(req, &src, &dst, vec->len, iv);
	vec->crypt_error = crypto_रुको_req(crypto_skcipher_encrypt(req), &रुको);
	अगर (vec->crypt_error != 0) अणु
		/*
		 * The only acceptable error here is क्रम an invalid length, so
		 * skcipher decryption should fail with the same error too.
		 * We'll test क्रम this.  But to keep the API usage well-defined,
		 * explicitly initialize the ciphertext buffer too.
		 */
		स_रखो((u8 *)vec->ctext, 0, vec->len);
	पूर्ण
करोne:
	snम_लिखो(name, max_namelen, "\"random: len=%u klen=%u\"",
		 vec->len, vec->klen);
पूर्ण

/*
 * Test the skcipher algorithm represented by @req against the corresponding
 * generic implementation, अगर one is available.
 */
अटल पूर्णांक test_skcipher_vs_generic_impl(स्थिर अक्षर *generic_driver,
					 काष्ठा skcipher_request *req,
					 काष्ठा cipher_test_sglists *tsgls)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर अचिन्हित पूर्णांक maxkeysize = crypto_skcipher_max_keysize(tfm);
	स्थिर अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(tfm);
	स्थिर अचिन्हित पूर्णांक blocksize = crypto_skcipher_blocksize(tfm);
	स्थिर अचिन्हित पूर्णांक maxdatasize = (2 * PAGE_SIZE) - TESTMGR_POISON_LEN;
	स्थिर अक्षर *algname = crypto_skcipher_alg(tfm)->base.cra_name;
	स्थिर अक्षर *driver = crypto_skcipher_driver_name(tfm);
	अक्षर _generic_driver[CRYPTO_MAX_ALG_NAME];
	काष्ठा crypto_skcipher *generic_tfm = शून्य;
	काष्ठा skcipher_request *generic_req = शून्य;
	अचिन्हित पूर्णांक i;
	काष्ठा cipher_testvec vec = अणु 0 पूर्ण;
	अक्षर vec_name[64];
	काष्ठा testvec_config *cfg;
	अक्षर cfgname[TESTVEC_CONFIG_NAMELEN];
	पूर्णांक err;

	अगर (noextratests)
		वापस 0;

	/* Keywrap isn't supported here yet as it handles its IV dअगरferently. */
	अगर (म_भेदन(algname, "kw(", 3) == 0)
		वापस 0;

	अगर (!generic_driver) अणु /* Use शेष naming convention? */
		err = build_generic_driver_name(algname, _generic_driver);
		अगर (err)
			वापस err;
		generic_driver = _generic_driver;
	पूर्ण

	अगर (म_भेद(generic_driver, driver) == 0) /* Alपढ़ोy the generic impl? */
		वापस 0;

	generic_tfm = crypto_alloc_skcipher(generic_driver, 0, 0);
	अगर (IS_ERR(generic_tfm)) अणु
		err = PTR_ERR(generic_tfm);
		अगर (err == -ENOENT) अणु
			pr_warn("alg: skcipher: skipping comparison tests for %s because %s is unavailable\n",
				driver, generic_driver);
			वापस 0;
		पूर्ण
		pr_err("alg: skcipher: error allocating %s (generic impl of %s): %d\n",
		       generic_driver, algname, err);
		वापस err;
	पूर्ण

	cfg = kzalloc(माप(*cfg), GFP_KERNEL);
	अगर (!cfg) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	generic_req = skcipher_request_alloc(generic_tfm, GFP_KERNEL);
	अगर (!generic_req) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Check the algorithm properties क्रम consistency. */

	अगर (crypto_skcipher_min_keysize(tfm) !=
	    crypto_skcipher_min_keysize(generic_tfm)) अणु
		pr_err("alg: skcipher: min keysize for %s (%u) doesn't match generic impl (%u)\n",
		       driver, crypto_skcipher_min_keysize(tfm),
		       crypto_skcipher_min_keysize(generic_tfm));
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (maxkeysize != crypto_skcipher_max_keysize(generic_tfm)) अणु
		pr_err("alg: skcipher: max keysize for %s (%u) doesn't match generic impl (%u)\n",
		       driver, maxkeysize,
		       crypto_skcipher_max_keysize(generic_tfm));
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (ivsize != crypto_skcipher_ivsize(generic_tfm)) अणु
		pr_err("alg: skcipher: ivsize for %s (%u) doesn't match generic impl (%u)\n",
		       driver, ivsize, crypto_skcipher_ivsize(generic_tfm));
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (blocksize != crypto_skcipher_blocksize(generic_tfm)) अणु
		pr_err("alg: skcipher: blocksize for %s (%u) doesn't match generic impl (%u)\n",
		       driver, blocksize,
		       crypto_skcipher_blocksize(generic_tfm));
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Now generate test vectors using the generic implementation, and test
	 * the other implementation against them.
	 */

	vec.key = kदो_स्मृति(maxkeysize, GFP_KERNEL);
	vec.iv = kदो_स्मृति(ivsize, GFP_KERNEL);
	vec.ptext = kदो_स्मृति(maxdatasize, GFP_KERNEL);
	vec.ctext = kदो_स्मृति(maxdatasize, GFP_KERNEL);
	अगर (!vec.key || !vec.iv || !vec.ptext || !vec.ctext) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < fuzz_iterations * 8; i++) अणु
		generate_अक्रमom_cipher_testvec(generic_req, &vec, maxdatasize,
					       vec_name, माप(vec_name));
		generate_अक्रमom_testvec_config(cfg, cfgname, माप(cfgname));

		err = test_skcipher_vec_cfg(ENCRYPT, &vec, vec_name,
					    cfg, req, tsgls);
		अगर (err)
			जाओ out;
		err = test_skcipher_vec_cfg(DECRYPT, &vec, vec_name,
					    cfg, req, tsgls);
		अगर (err)
			जाओ out;
		cond_resched();
	पूर्ण
	err = 0;
out:
	kमुक्त(cfg);
	kमुक्त(vec.key);
	kमुक्त(vec.iv);
	kमुक्त(vec.ptext);
	kमुक्त(vec.ctext);
	crypto_मुक्त_skcipher(generic_tfm);
	skcipher_request_मुक्त(generic_req);
	वापस err;
पूर्ण
#अन्यथा /* !CONFIG_CRYPTO_MANAGER_EXTRA_TESTS */
अटल पूर्णांक test_skcipher_vs_generic_impl(स्थिर अक्षर *generic_driver,
					 काष्ठा skcipher_request *req,
					 काष्ठा cipher_test_sglists *tsgls)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_CRYPTO_MANAGER_EXTRA_TESTS */

अटल पूर्णांक test_skcipher(पूर्णांक enc, स्थिर काष्ठा cipher_test_suite *suite,
			 काष्ठा skcipher_request *req,
			 काष्ठा cipher_test_sglists *tsgls)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < suite->count; i++) अणु
		err = test_skcipher_vec(enc, &suite->vecs[i], i, req, tsgls);
		अगर (err)
			वापस err;
		cond_resched();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक alg_test_skcipher(स्थिर काष्ठा alg_test_desc *desc,
			     स्थिर अक्षर *driver, u32 type, u32 mask)
अणु
	स्थिर काष्ठा cipher_test_suite *suite = &desc->suite.cipher;
	काष्ठा crypto_skcipher *tfm;
	काष्ठा skcipher_request *req = शून्य;
	काष्ठा cipher_test_sglists *tsgls = शून्य;
	पूर्णांक err;

	अगर (suite->count <= 0) अणु
		pr_err("alg: skcipher: empty test suite for %s\n", driver);
		वापस -EINVAL;
	पूर्ण

	tfm = crypto_alloc_skcipher(driver, type, mask);
	अगर (IS_ERR(tfm)) अणु
		pr_err("alg: skcipher: failed to allocate transform for %s: %ld\n",
		       driver, PTR_ERR(tfm));
		वापस PTR_ERR(tfm);
	पूर्ण
	driver = crypto_skcipher_driver_name(tfm);

	req = skcipher_request_alloc(tfm, GFP_KERNEL);
	अगर (!req) अणु
		pr_err("alg: skcipher: failed to allocate request for %s\n",
		       driver);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	tsgls = alloc_cipher_test_sglists();
	अगर (!tsgls) अणु
		pr_err("alg: skcipher: failed to allocate test buffers for %s\n",
		       driver);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = test_skcipher(ENCRYPT, suite, req, tsgls);
	अगर (err)
		जाओ out;

	err = test_skcipher(DECRYPT, suite, req, tsgls);
	अगर (err)
		जाओ out;

	err = test_skcipher_vs_generic_impl(desc->generic_driver, req, tsgls);
out:
	मुक्त_cipher_test_sglists(tsgls);
	skcipher_request_मुक्त(req);
	crypto_मुक्त_skcipher(tfm);
	वापस err;
पूर्ण

अटल पूर्णांक test_comp(काष्ठा crypto_comp *tfm,
		     स्थिर काष्ठा comp_testvec *cढाँचा,
		     स्थिर काष्ठा comp_testvec *dढाँचा,
		     पूर्णांक ctcount, पूर्णांक dtcount)
अणु
	स्थिर अक्षर *algo = crypto_tfm_alg_driver_name(crypto_comp_tfm(tfm));
	अक्षर *output, *decomp_output;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	output = kदो_स्मृति(COMP_BUF_SIZE, GFP_KERNEL);
	अगर (!output)
		वापस -ENOMEM;

	decomp_output = kदो_स्मृति(COMP_BUF_SIZE, GFP_KERNEL);
	अगर (!decomp_output) अणु
		kमुक्त(output);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < ctcount; i++) अणु
		पूर्णांक ilen;
		अचिन्हित पूर्णांक dlen = COMP_BUF_SIZE;

		स_रखो(output, 0, COMP_BUF_SIZE);
		स_रखो(decomp_output, 0, COMP_BUF_SIZE);

		ilen = cढाँचा[i].inlen;
		ret = crypto_comp_compress(tfm, cढाँचा[i].input,
					   ilen, output, &dlen);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "alg: comp: compression failed "
			       "on test %d for %s: ret=%d\n", i + 1, algo,
			       -ret);
			जाओ out;
		पूर्ण

		ilen = dlen;
		dlen = COMP_BUF_SIZE;
		ret = crypto_comp_decompress(tfm, output,
					     ilen, decomp_output, &dlen);
		अगर (ret) अणु
			pr_err("alg: comp: compression failed: decompress: on test %d for %s failed: ret=%d\n",
			       i + 1, algo, -ret);
			जाओ out;
		पूर्ण

		अगर (dlen != cढाँचा[i].inlen) अणु
			prपूर्णांकk(KERN_ERR "alg: comp: Compression test %d "
			       "failed for %s: output len = %d\n", i + 1, algo,
			       dlen);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (स_भेद(decomp_output, cढाँचा[i].input,
			   cढाँचा[i].inlen)) अणु
			pr_err("alg: comp: compression failed: output differs: on test %d for %s\n",
			       i + 1, algo);
			hexdump(decomp_output, dlen);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dtcount; i++) अणु
		पूर्णांक ilen;
		अचिन्हित पूर्णांक dlen = COMP_BUF_SIZE;

		स_रखो(decomp_output, 0, COMP_BUF_SIZE);

		ilen = dढाँचा[i].inlen;
		ret = crypto_comp_decompress(tfm, dढाँचा[i].input,
					     ilen, decomp_output, &dlen);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "alg: comp: decompression failed "
			       "on test %d for %s: ret=%d\n", i + 1, algo,
			       -ret);
			जाओ out;
		पूर्ण

		अगर (dlen != dढाँचा[i].outlen) अणु
			prपूर्णांकk(KERN_ERR "alg: comp: Decompression test %d "
			       "failed for %s: output len = %d\n", i + 1, algo,
			       dlen);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (स_भेद(decomp_output, dढाँचा[i].output, dlen)) अणु
			prपूर्णांकk(KERN_ERR "alg: comp: Decompression test %d "
			       "failed for %s\n", i + 1, algo);
			hexdump(decomp_output, dlen);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = 0;

out:
	kमुक्त(decomp_output);
	kमुक्त(output);
	वापस ret;
पूर्ण

अटल पूर्णांक test_acomp(काष्ठा crypto_acomp *tfm,
			      स्थिर काष्ठा comp_testvec *cढाँचा,
		      स्थिर काष्ठा comp_testvec *dढाँचा,
		      पूर्णांक ctcount, पूर्णांक dtcount)
अणु
	स्थिर अक्षर *algo = crypto_tfm_alg_driver_name(crypto_acomp_tfm(tfm));
	अचिन्हित पूर्णांक i;
	अक्षर *output, *decomp_out;
	पूर्णांक ret;
	काष्ठा scatterlist src, dst;
	काष्ठा acomp_req *req;
	काष्ठा crypto_रुको रुको;

	output = kदो_स्मृति(COMP_BUF_SIZE, GFP_KERNEL);
	अगर (!output)
		वापस -ENOMEM;

	decomp_out = kदो_स्मृति(COMP_BUF_SIZE, GFP_KERNEL);
	अगर (!decomp_out) अणु
		kमुक्त(output);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < ctcount; i++) अणु
		अचिन्हित पूर्णांक dlen = COMP_BUF_SIZE;
		पूर्णांक ilen = cढाँचा[i].inlen;
		व्योम *input_vec;

		input_vec = kmemdup(cढाँचा[i].input, ilen, GFP_KERNEL);
		अगर (!input_vec) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		स_रखो(output, 0, dlen);
		crypto_init_रुको(&रुको);
		sg_init_one(&src, input_vec, ilen);
		sg_init_one(&dst, output, dlen);

		req = acomp_request_alloc(tfm);
		अगर (!req) अणु
			pr_err("alg: acomp: request alloc failed for %s\n",
			       algo);
			kमुक्त(input_vec);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		acomp_request_set_params(req, &src, &dst, ilen, dlen);
		acomp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
					   crypto_req_करोne, &रुको);

		ret = crypto_रुको_req(crypto_acomp_compress(req), &रुको);
		अगर (ret) अणु
			pr_err("alg: acomp: compression failed on test %d for %s: ret=%d\n",
			       i + 1, algo, -ret);
			kमुक्त(input_vec);
			acomp_request_मुक्त(req);
			जाओ out;
		पूर्ण

		ilen = req->dlen;
		dlen = COMP_BUF_SIZE;
		sg_init_one(&src, output, ilen);
		sg_init_one(&dst, decomp_out, dlen);
		crypto_init_रुको(&रुको);
		acomp_request_set_params(req, &src, &dst, ilen, dlen);

		ret = crypto_रुको_req(crypto_acomp_decompress(req), &रुको);
		अगर (ret) अणु
			pr_err("alg: acomp: compression failed on test %d for %s: ret=%d\n",
			       i + 1, algo, -ret);
			kमुक्त(input_vec);
			acomp_request_मुक्त(req);
			जाओ out;
		पूर्ण

		अगर (req->dlen != cढाँचा[i].inlen) अणु
			pr_err("alg: acomp: Compression test %d failed for %s: output len = %d\n",
			       i + 1, algo, req->dlen);
			ret = -EINVAL;
			kमुक्त(input_vec);
			acomp_request_मुक्त(req);
			जाओ out;
		पूर्ण

		अगर (स_भेद(input_vec, decomp_out, req->dlen)) अणु
			pr_err("alg: acomp: Compression test %d failed for %s\n",
			       i + 1, algo);
			hexdump(output, req->dlen);
			ret = -EINVAL;
			kमुक्त(input_vec);
			acomp_request_मुक्त(req);
			जाओ out;
		पूर्ण

		kमुक्त(input_vec);
		acomp_request_मुक्त(req);
	पूर्ण

	क्रम (i = 0; i < dtcount; i++) अणु
		अचिन्हित पूर्णांक dlen = COMP_BUF_SIZE;
		पूर्णांक ilen = dढाँचा[i].inlen;
		व्योम *input_vec;

		input_vec = kmemdup(dढाँचा[i].input, ilen, GFP_KERNEL);
		अगर (!input_vec) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		स_रखो(output, 0, dlen);
		crypto_init_रुको(&रुको);
		sg_init_one(&src, input_vec, ilen);
		sg_init_one(&dst, output, dlen);

		req = acomp_request_alloc(tfm);
		अगर (!req) अणु
			pr_err("alg: acomp: request alloc failed for %s\n",
			       algo);
			kमुक्त(input_vec);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		acomp_request_set_params(req, &src, &dst, ilen, dlen);
		acomp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
					   crypto_req_करोne, &रुको);

		ret = crypto_रुको_req(crypto_acomp_decompress(req), &रुको);
		अगर (ret) अणु
			pr_err("alg: acomp: decompression failed on test %d for %s: ret=%d\n",
			       i + 1, algo, -ret);
			kमुक्त(input_vec);
			acomp_request_मुक्त(req);
			जाओ out;
		पूर्ण

		अगर (req->dlen != dढाँचा[i].outlen) अणु
			pr_err("alg: acomp: Decompression test %d failed for %s: output len = %d\n",
			       i + 1, algo, req->dlen);
			ret = -EINVAL;
			kमुक्त(input_vec);
			acomp_request_मुक्त(req);
			जाओ out;
		पूर्ण

		अगर (स_भेद(output, dढाँचा[i].output, req->dlen)) अणु
			pr_err("alg: acomp: Decompression test %d failed for %s\n",
			       i + 1, algo);
			hexdump(output, req->dlen);
			ret = -EINVAL;
			kमुक्त(input_vec);
			acomp_request_मुक्त(req);
			जाओ out;
		पूर्ण

		kमुक्त(input_vec);
		acomp_request_मुक्त(req);
	पूर्ण

	ret = 0;

out:
	kमुक्त(decomp_out);
	kमुक्त(output);
	वापस ret;
पूर्ण

अटल पूर्णांक test_cprng(काष्ठा crypto_rng *tfm,
		      स्थिर काष्ठा cprng_testvec *ढाँचा,
		      अचिन्हित पूर्णांक tcount)
अणु
	स्थिर अक्षर *algo = crypto_tfm_alg_driver_name(crypto_rng_tfm(tfm));
	पूर्णांक err = 0, i, j, seedsize;
	u8 *seed;
	अक्षर result[32];

	seedsize = crypto_rng_seedsize(tfm);

	seed = kदो_स्मृति(seedsize, GFP_KERNEL);
	अगर (!seed) अणु
		prपूर्णांकk(KERN_ERR "alg: cprng: Failed to allocate seed space "
		       "for %s\n", algo);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < tcount; i++) अणु
		स_रखो(result, 0, 32);

		स_नकल(seed, ढाँचा[i].v, ढाँचा[i].vlen);
		स_नकल(seed + ढाँचा[i].vlen, ढाँचा[i].key,
		       ढाँचा[i].klen);
		स_नकल(seed + ढाँचा[i].vlen + ढाँचा[i].klen,
		       ढाँचा[i].dt, ढाँचा[i].dtlen);

		err = crypto_rng_reset(tfm, seed, seedsize);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "alg: cprng: Failed to reset rng "
			       "for %s\n", algo);
			जाओ out;
		पूर्ण

		क्रम (j = 0; j < ढाँचा[i].loops; j++) अणु
			err = crypto_rng_get_bytes(tfm, result,
						   ढाँचा[i].rlen);
			अगर (err < 0) अणु
				prपूर्णांकk(KERN_ERR "alg: cprng: Failed to obtain "
				       "the correct amount of random data for "
				       "%s (requested %d)\n", algo,
				       ढाँचा[i].rlen);
				जाओ out;
			पूर्ण
		पूर्ण

		err = स_भेद(result, ढाँचा[i].result,
			     ढाँचा[i].rlen);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "alg: cprng: Test %d failed for %s\n",
			       i, algo);
			hexdump(result, ढाँचा[i].rlen);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	kमुक्त(seed);
	वापस err;
पूर्ण

अटल पूर्णांक alg_test_cipher(स्थिर काष्ठा alg_test_desc *desc,
			   स्थिर अक्षर *driver, u32 type, u32 mask)
अणु
	स्थिर काष्ठा cipher_test_suite *suite = &desc->suite.cipher;
	काष्ठा crypto_cipher *tfm;
	पूर्णांक err;

	tfm = crypto_alloc_cipher(driver, type, mask);
	अगर (IS_ERR(tfm)) अणु
		prपूर्णांकk(KERN_ERR "alg: cipher: Failed to load transform for "
		       "%s: %ld\n", driver, PTR_ERR(tfm));
		वापस PTR_ERR(tfm);
	पूर्ण

	err = test_cipher(tfm, ENCRYPT, suite->vecs, suite->count);
	अगर (!err)
		err = test_cipher(tfm, DECRYPT, suite->vecs, suite->count);

	crypto_मुक्त_cipher(tfm);
	वापस err;
पूर्ण

अटल पूर्णांक alg_test_comp(स्थिर काष्ठा alg_test_desc *desc, स्थिर अक्षर *driver,
			 u32 type, u32 mask)
अणु
	काष्ठा crypto_comp *comp;
	काष्ठा crypto_acomp *acomp;
	पूर्णांक err;
	u32 algo_type = type & CRYPTO_ALG_TYPE_ACOMPRESS_MASK;

	अगर (algo_type == CRYPTO_ALG_TYPE_ACOMPRESS) अणु
		acomp = crypto_alloc_acomp(driver, type, mask);
		अगर (IS_ERR(acomp)) अणु
			pr_err("alg: acomp: Failed to load transform for %s: %ld\n",
			       driver, PTR_ERR(acomp));
			वापस PTR_ERR(acomp);
		पूर्ण
		err = test_acomp(acomp, desc->suite.comp.comp.vecs,
				 desc->suite.comp.decomp.vecs,
				 desc->suite.comp.comp.count,
				 desc->suite.comp.decomp.count);
		crypto_मुक्त_acomp(acomp);
	पूर्ण अन्यथा अणु
		comp = crypto_alloc_comp(driver, type, mask);
		अगर (IS_ERR(comp)) अणु
			pr_err("alg: comp: Failed to load transform for %s: %ld\n",
			       driver, PTR_ERR(comp));
			वापस PTR_ERR(comp);
		पूर्ण

		err = test_comp(comp, desc->suite.comp.comp.vecs,
				desc->suite.comp.decomp.vecs,
				desc->suite.comp.comp.count,
				desc->suite.comp.decomp.count);

		crypto_मुक्त_comp(comp);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक alg_test_crc32c(स्थिर काष्ठा alg_test_desc *desc,
			   स्थिर अक्षर *driver, u32 type, u32 mask)
अणु
	काष्ठा crypto_shash *tfm;
	__le32 val;
	पूर्णांक err;

	err = alg_test_hash(desc, driver, type, mask);
	अगर (err)
		वापस err;

	tfm = crypto_alloc_shash(driver, type, mask);
	अगर (IS_ERR(tfm)) अणु
		अगर (PTR_ERR(tfm) == -ENOENT) अणु
			/*
			 * This crc32c implementation is only available through
			 * ahash API, not the shash API, so the reमुख्यing part
			 * of the test is not applicable to it.
			 */
			वापस 0;
		पूर्ण
		prपूर्णांकk(KERN_ERR "alg: crc32c: Failed to load transform for %s: "
		       "%ld\n", driver, PTR_ERR(tfm));
		वापस PTR_ERR(tfm);
	पूर्ण
	driver = crypto_shash_driver_name(tfm);

	करो अणु
		SHASH_DESC_ON_STACK(shash, tfm);
		u32 *ctx = (u32 *)shash_desc_ctx(shash);

		shash->tfm = tfm;

		*ctx = 420553207;
		err = crypto_shash_final(shash, (u8 *)&val);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "alg: crc32c: Operation failed for "
			       "%s: %d\n", driver, err);
			अवरोध;
		पूर्ण

		अगर (val != cpu_to_le32(~420553207)) अणु
			pr_err("alg: crc32c: Test failed for %s: %u\n",
			       driver, le32_to_cpu(val));
			err = -EINVAL;
		पूर्ण
	पूर्ण जबतक (0);

	crypto_मुक्त_shash(tfm);

	वापस err;
पूर्ण

अटल पूर्णांक alg_test_cprng(स्थिर काष्ठा alg_test_desc *desc, स्थिर अक्षर *driver,
			  u32 type, u32 mask)
अणु
	काष्ठा crypto_rng *rng;
	पूर्णांक err;

	rng = crypto_alloc_rng(driver, type, mask);
	अगर (IS_ERR(rng)) अणु
		prपूर्णांकk(KERN_ERR "alg: cprng: Failed to load transform for %s: "
		       "%ld\n", driver, PTR_ERR(rng));
		वापस PTR_ERR(rng);
	पूर्ण

	err = test_cprng(rng, desc->suite.cprng.vecs, desc->suite.cprng.count);

	crypto_मुक्त_rng(rng);

	वापस err;
पूर्ण


अटल पूर्णांक drbg_cavs_test(स्थिर काष्ठा drbg_testvec *test, पूर्णांक pr,
			  स्थिर अक्षर *driver, u32 type, u32 mask)
अणु
	पूर्णांक ret = -EAGAIN;
	काष्ठा crypto_rng *drng;
	काष्ठा drbg_test_data test_data;
	काष्ठा drbg_string addtl, pers, testentropy;
	अचिन्हित अक्षर *buf = kzalloc(test->expectedlen, GFP_KERNEL);

	अगर (!buf)
		वापस -ENOMEM;

	drng = crypto_alloc_rng(driver, type, mask);
	अगर (IS_ERR(drng)) अणु
		prपूर्णांकk(KERN_ERR "alg: drbg: could not allocate DRNG handle for "
		       "%s\n", driver);
		kमुक्त_sensitive(buf);
		वापस -ENOMEM;
	पूर्ण

	test_data.testentropy = &testentropy;
	drbg_string_fill(&testentropy, test->entropy, test->entropylen);
	drbg_string_fill(&pers, test->pers, test->perslen);
	ret = crypto_drbg_reset_test(drng, &pers, &test_data);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "alg: drbg: Failed to reset rng\n");
		जाओ outbuf;
	पूर्ण

	drbg_string_fill(&addtl, test->addtla, test->addtllen);
	अगर (pr) अणु
		drbg_string_fill(&testentropy, test->entpra, test->entprlen);
		ret = crypto_drbg_get_bytes_addtl_test(drng,
			buf, test->expectedlen, &addtl,	&test_data);
	पूर्ण अन्यथा अणु
		ret = crypto_drbg_get_bytes_addtl(drng,
			buf, test->expectedlen, &addtl);
	पूर्ण
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "alg: drbg: could not obtain random data for "
		       "driver %s\n", driver);
		जाओ outbuf;
	पूर्ण

	drbg_string_fill(&addtl, test->addtlb, test->addtllen);
	अगर (pr) अणु
		drbg_string_fill(&testentropy, test->entprb, test->entprlen);
		ret = crypto_drbg_get_bytes_addtl_test(drng,
			buf, test->expectedlen, &addtl, &test_data);
	पूर्ण अन्यथा अणु
		ret = crypto_drbg_get_bytes_addtl(drng,
			buf, test->expectedlen, &addtl);
	पूर्ण
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "alg: drbg: could not obtain random data for "
		       "driver %s\n", driver);
		जाओ outbuf;
	पूर्ण

	ret = स_भेद(test->expected, buf, test->expectedlen);

outbuf:
	crypto_मुक्त_rng(drng);
	kमुक्त_sensitive(buf);
	वापस ret;
पूर्ण


अटल पूर्णांक alg_test_drbg(स्थिर काष्ठा alg_test_desc *desc, स्थिर अक्षर *driver,
			 u32 type, u32 mask)
अणु
	पूर्णांक err = 0;
	पूर्णांक pr = 0;
	पूर्णांक i = 0;
	स्थिर काष्ठा drbg_testvec *ढाँचा = desc->suite.drbg.vecs;
	अचिन्हित पूर्णांक tcount = desc->suite.drbg.count;

	अगर (0 == स_भेद(driver, "drbg_pr_", 8))
		pr = 1;

	क्रम (i = 0; i < tcount; i++) अणु
		err = drbg_cavs_test(&ढाँचा[i], pr, driver, type, mask);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "alg: drbg: Test %d failed for %s\n",
			       i, driver);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस err;

पूर्ण

अटल पूर्णांक करो_test_kpp(काष्ठा crypto_kpp *tfm, स्थिर काष्ठा kpp_testvec *vec,
		       स्थिर अक्षर *alg)
अणु
	काष्ठा kpp_request *req;
	व्योम *input_buf = शून्य;
	व्योम *output_buf = शून्य;
	व्योम *a_खुला = शून्य;
	व्योम *a_ss = शून्य;
	व्योम *shared_secret = शून्य;
	काष्ठा crypto_रुको रुको;
	अचिन्हित पूर्णांक out_len_max;
	पूर्णांक err = -ENOMEM;
	काष्ठा scatterlist src, dst;

	req = kpp_request_alloc(tfm, GFP_KERNEL);
	अगर (!req)
		वापस err;

	crypto_init_रुको(&रुको);

	err = crypto_kpp_set_secret(tfm, vec->secret, vec->secret_size);
	अगर (err < 0)
		जाओ मुक्त_req;

	out_len_max = crypto_kpp_maxsize(tfm);
	output_buf = kzalloc(out_len_max, GFP_KERNEL);
	अगर (!output_buf) अणु
		err = -ENOMEM;
		जाओ मुक्त_req;
	पूर्ण

	/* Use appropriate parameter as base */
	kpp_request_set_input(req, शून्य, 0);
	sg_init_one(&dst, output_buf, out_len_max);
	kpp_request_set_output(req, &dst, out_len_max);
	kpp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				 crypto_req_करोne, &रुको);

	/* Compute party A's खुला key */
	err = crypto_रुको_req(crypto_kpp_generate_खुला_key(req), &रुको);
	अगर (err) अणु
		pr_err("alg: %s: Party A: generate public key test failed. err %d\n",
		       alg, err);
		जाओ मुक्त_output;
	पूर्ण

	अगर (vec->genkey) अणु
		/* Save party A's खुला key */
		a_खुला = kmemdup(sg_virt(req->dst), out_len_max, GFP_KERNEL);
		अगर (!a_खुला) अणु
			err = -ENOMEM;
			जाओ मुक्त_output;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Verअगरy calculated खुला key */
		अगर (स_भेद(vec->expected_a_खुला, sg_virt(req->dst),
			   vec->expected_a_खुला_size)) अणु
			pr_err("alg: %s: Party A: generate public key test failed. Invalid output\n",
			       alg);
			err = -EINVAL;
			जाओ मुक्त_output;
		पूर्ण
	पूर्ण

	/* Calculate shared secret key by using counter part (b) खुला key. */
	input_buf = kmemdup(vec->b_खुला, vec->b_खुला_size, GFP_KERNEL);
	अगर (!input_buf) अणु
		err = -ENOMEM;
		जाओ मुक्त_output;
	पूर्ण

	sg_init_one(&src, input_buf, vec->b_खुला_size);
	sg_init_one(&dst, output_buf, out_len_max);
	kpp_request_set_input(req, &src, vec->b_खुला_size);
	kpp_request_set_output(req, &dst, out_len_max);
	kpp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				 crypto_req_करोne, &रुको);
	err = crypto_रुको_req(crypto_kpp_compute_shared_secret(req), &रुको);
	अगर (err) अणु
		pr_err("alg: %s: Party A: compute shared secret test failed. err %d\n",
		       alg, err);
		जाओ मुक्त_all;
	पूर्ण

	अगर (vec->genkey) अणु
		/* Save the shared secret obtained by party A */
		a_ss = kmemdup(sg_virt(req->dst), vec->expected_ss_size, GFP_KERNEL);
		अगर (!a_ss) अणु
			err = -ENOMEM;
			जाओ मुक्त_all;
		पूर्ण

		/*
		 * Calculate party B's shared secret by using party A's
		 * खुला key.
		 */
		err = crypto_kpp_set_secret(tfm, vec->b_secret,
					    vec->b_secret_size);
		अगर (err < 0)
			जाओ मुक्त_all;

		sg_init_one(&src, a_खुला, vec->expected_a_खुला_size);
		sg_init_one(&dst, output_buf, out_len_max);
		kpp_request_set_input(req, &src, vec->expected_a_खुला_size);
		kpp_request_set_output(req, &dst, out_len_max);
		kpp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
					 crypto_req_करोne, &रुको);
		err = crypto_रुको_req(crypto_kpp_compute_shared_secret(req),
				      &रुको);
		अगर (err) अणु
			pr_err("alg: %s: Party B: compute shared secret failed. err %d\n",
			       alg, err);
			जाओ मुक्त_all;
		पूर्ण

		shared_secret = a_ss;
	पूर्ण अन्यथा अणु
		shared_secret = (व्योम *)vec->expected_ss;
	पूर्ण

	/*
	 * verअगरy shared secret from which the user will derive
	 * secret key by executing whatever hash it has chosen
	 */
	अगर (स_भेद(shared_secret, sg_virt(req->dst),
		   vec->expected_ss_size)) अणु
		pr_err("alg: %s: compute shared secret test failed. Invalid output\n",
		       alg);
		err = -EINVAL;
	पूर्ण

मुक्त_all:
	kमुक्त(a_ss);
	kमुक्त(input_buf);
मुक्त_output:
	kमुक्त(a_खुला);
	kमुक्त(output_buf);
मुक्त_req:
	kpp_request_मुक्त(req);
	वापस err;
पूर्ण

अटल पूर्णांक test_kpp(काष्ठा crypto_kpp *tfm, स्थिर अक्षर *alg,
		    स्थिर काष्ठा kpp_testvec *vecs, अचिन्हित पूर्णांक tcount)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < tcount; i++) अणु
		ret = करो_test_kpp(tfm, vecs++, alg);
		अगर (ret) अणु
			pr_err("alg: %s: test failed on vector %d, err=%d\n",
			       alg, i + 1, ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक alg_test_kpp(स्थिर काष्ठा alg_test_desc *desc, स्थिर अक्षर *driver,
			u32 type, u32 mask)
अणु
	काष्ठा crypto_kpp *tfm;
	पूर्णांक err = 0;

	tfm = crypto_alloc_kpp(driver, type, mask);
	अगर (IS_ERR(tfm)) अणु
		pr_err("alg: kpp: Failed to load tfm for %s: %ld\n",
		       driver, PTR_ERR(tfm));
		वापस PTR_ERR(tfm);
	पूर्ण
	अगर (desc->suite.kpp.vecs)
		err = test_kpp(tfm, desc->alg, desc->suite.kpp.vecs,
			       desc->suite.kpp.count);

	crypto_मुक्त_kpp(tfm);
	वापस err;
पूर्ण

अटल u8 *test_pack_u32(u8 *dst, u32 val)
अणु
	स_नकल(dst, &val, माप(val));
	वापस dst + माप(val);
पूर्ण

अटल पूर्णांक test_akcipher_one(काष्ठा crypto_akcipher *tfm,
			     स्थिर काष्ठा akcipher_testvec *vecs)
अणु
	अक्षर *xbuf[Xबफ_मानE];
	काष्ठा akcipher_request *req;
	व्योम *outbuf_enc = शून्य;
	व्योम *outbuf_dec = शून्य;
	काष्ठा crypto_रुको रुको;
	अचिन्हित पूर्णांक out_len_max, out_len = 0;
	पूर्णांक err = -ENOMEM;
	काष्ठा scatterlist src, dst, src_tab[3];
	स्थिर अक्षर *m, *c;
	अचिन्हित पूर्णांक m_size, c_size;
	स्थिर अक्षर *op;
	u8 *key, *ptr;

	अगर (tesपंचांगgr_alloc_buf(xbuf))
		वापस err;

	req = akcipher_request_alloc(tfm, GFP_KERNEL);
	अगर (!req)
		जाओ मुक्त_xbuf;

	crypto_init_रुको(&रुको);

	key = kदो_स्मृति(vecs->key_len + माप(u32) * 2 + vecs->param_len,
		      GFP_KERNEL);
	अगर (!key)
		जाओ मुक्त_req;
	स_नकल(key, vecs->key, vecs->key_len);
	ptr = key + vecs->key_len;
	ptr = test_pack_u32(ptr, vecs->algo);
	ptr = test_pack_u32(ptr, vecs->param_len);
	स_नकल(ptr, vecs->params, vecs->param_len);

	अगर (vecs->खुला_key_vec)
		err = crypto_akcipher_set_pub_key(tfm, key, vecs->key_len);
	अन्यथा
		err = crypto_akcipher_set_priv_key(tfm, key, vecs->key_len);
	अगर (err)
		जाओ मुक्त_key;

	/*
	 * First run test which करो not require a निजी key, such as
	 * encrypt or verअगरy.
	 */
	err = -ENOMEM;
	out_len_max = crypto_akcipher_maxsize(tfm);
	outbuf_enc = kzalloc(out_len_max, GFP_KERNEL);
	अगर (!outbuf_enc)
		जाओ मुक्त_key;

	अगर (!vecs->siggen_sigver_test) अणु
		m = vecs->m;
		m_size = vecs->m_size;
		c = vecs->c;
		c_size = vecs->c_size;
		op = "encrypt";
	पूर्ण अन्यथा अणु
		/* Swap args so we could keep plaपूर्णांकext (digest)
		 * in vecs->m, and cooked signature in vecs->c.
		 */
		m = vecs->c; /* signature */
		m_size = vecs->c_size;
		c = vecs->m; /* digest */
		c_size = vecs->m_size;
		op = "verify";
	पूर्ण

	err = -E2BIG;
	अगर (WARN_ON(m_size > PAGE_SIZE))
		जाओ मुक्त_all;
	स_नकल(xbuf[0], m, m_size);

	sg_init_table(src_tab, 3);
	sg_set_buf(&src_tab[0], xbuf[0], 8);
	sg_set_buf(&src_tab[1], xbuf[0] + 8, m_size - 8);
	अगर (vecs->siggen_sigver_test) अणु
		अगर (WARN_ON(c_size > PAGE_SIZE))
			जाओ मुक्त_all;
		स_नकल(xbuf[1], c, c_size);
		sg_set_buf(&src_tab[2], xbuf[1], c_size);
		akcipher_request_set_crypt(req, src_tab, शून्य, m_size, c_size);
	पूर्ण अन्यथा अणु
		sg_init_one(&dst, outbuf_enc, out_len_max);
		akcipher_request_set_crypt(req, src_tab, &dst, m_size,
					   out_len_max);
	पूर्ण
	akcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				      crypto_req_करोne, &रुको);

	err = crypto_रुको_req(vecs->siggen_sigver_test ?
			      /* Run asymmetric signature verअगरication */
			      crypto_akcipher_verअगरy(req) :
			      /* Run asymmetric encrypt */
			      crypto_akcipher_encrypt(req), &रुको);
	अगर (err) अणु
		pr_err("alg: akcipher: %s test failed. err %d\n", op, err);
		जाओ मुक्त_all;
	पूर्ण
	अगर (!vecs->siggen_sigver_test && c) अणु
		अगर (req->dst_len != c_size) अणु
			pr_err("alg: akcipher: %s test failed. Invalid output len\n",
			       op);
			err = -EINVAL;
			जाओ मुक्त_all;
		पूर्ण
		/* verअगरy that encrypted message is equal to expected */
		अगर (स_भेद(c, outbuf_enc, c_size) != 0) अणु
			pr_err("alg: akcipher: %s test failed. Invalid output\n",
			       op);
			hexdump(outbuf_enc, c_size);
			err = -EINVAL;
			जाओ मुक्त_all;
		पूर्ण
	पूर्ण

	/*
	 * Don't invoke (decrypt or sign) test which require a निजी key
	 * क्रम vectors with only a खुला key.
	 */
	अगर (vecs->खुला_key_vec) अणु
		err = 0;
		जाओ मुक्त_all;
	पूर्ण
	outbuf_dec = kzalloc(out_len_max, GFP_KERNEL);
	अगर (!outbuf_dec) अणु
		err = -ENOMEM;
		जाओ मुक्त_all;
	पूर्ण

	अगर (!vecs->siggen_sigver_test && !c) अणु
		c = outbuf_enc;
		c_size = req->dst_len;
	पूर्ण

	err = -E2BIG;
	op = vecs->siggen_sigver_test ? "sign" : "decrypt";
	अगर (WARN_ON(c_size > PAGE_SIZE))
		जाओ मुक्त_all;
	स_नकल(xbuf[0], c, c_size);

	sg_init_one(&src, xbuf[0], c_size);
	sg_init_one(&dst, outbuf_dec, out_len_max);
	crypto_init_रुको(&रुको);
	akcipher_request_set_crypt(req, &src, &dst, c_size, out_len_max);

	err = crypto_रुको_req(vecs->siggen_sigver_test ?
			      /* Run asymmetric signature generation */
			      crypto_akcipher_sign(req) :
			      /* Run asymmetric decrypt */
			      crypto_akcipher_decrypt(req), &रुको);
	अगर (err) अणु
		pr_err("alg: akcipher: %s test failed. err %d\n", op, err);
		जाओ मुक्त_all;
	पूर्ण
	out_len = req->dst_len;
	अगर (out_len < m_size) अणु
		pr_err("alg: akcipher: %s test failed. Invalid output len %u\n",
		       op, out_len);
		err = -EINVAL;
		जाओ मुक्त_all;
	पूर्ण
	/* verअगरy that decrypted message is equal to the original msg */
	अगर (स_प्रथम_inv(outbuf_dec, 0, out_len - m_size) ||
	    स_भेद(m, outbuf_dec + out_len - m_size, m_size)) अणु
		pr_err("alg: akcipher: %s test failed. Invalid output\n", op);
		hexdump(outbuf_dec, out_len);
		err = -EINVAL;
	पूर्ण
मुक्त_all:
	kमुक्त(outbuf_dec);
	kमुक्त(outbuf_enc);
मुक्त_key:
	kमुक्त(key);
मुक्त_req:
	akcipher_request_मुक्त(req);
मुक्त_xbuf:
	tesपंचांगgr_मुक्त_buf(xbuf);
	वापस err;
पूर्ण

अटल पूर्णांक test_akcipher(काष्ठा crypto_akcipher *tfm, स्थिर अक्षर *alg,
			 स्थिर काष्ठा akcipher_testvec *vecs,
			 अचिन्हित पूर्णांक tcount)
अणु
	स्थिर अक्षर *algo =
		crypto_tfm_alg_driver_name(crypto_akcipher_tfm(tfm));
	पूर्णांक ret, i;

	क्रम (i = 0; i < tcount; i++) अणु
		ret = test_akcipher_one(tfm, vecs++);
		अगर (!ret)
			जारी;

		pr_err("alg: akcipher: test %d failed for %s, err=%d\n",
		       i + 1, algo, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक alg_test_akcipher(स्थिर काष्ठा alg_test_desc *desc,
			     स्थिर अक्षर *driver, u32 type, u32 mask)
अणु
	काष्ठा crypto_akcipher *tfm;
	पूर्णांक err = 0;

	tfm = crypto_alloc_akcipher(driver, type, mask);
	अगर (IS_ERR(tfm)) अणु
		pr_err("alg: akcipher: Failed to load tfm for %s: %ld\n",
		       driver, PTR_ERR(tfm));
		वापस PTR_ERR(tfm);
	पूर्ण
	अगर (desc->suite.akcipher.vecs)
		err = test_akcipher(tfm, desc->alg, desc->suite.akcipher.vecs,
				    desc->suite.akcipher.count);

	crypto_मुक्त_akcipher(tfm);
	वापस err;
पूर्ण

अटल पूर्णांक alg_test_null(स्थिर काष्ठा alg_test_desc *desc,
			     स्थिर अक्षर *driver, u32 type, u32 mask)
अणु
	वापस 0;
पूर्ण

#घोषणा ____VECS(tv)	.vecs = tv, .count = ARRAY_SIZE(tv)
#घोषणा __VECS(tv)	अणु ____VECS(tv) पूर्ण

/* Please keep this list sorted by algorithm name. */
अटल स्थिर काष्ठा alg_test_desc alg_test_descs[] = अणु
	अणु
		.alg = "adiantum(xchacha12,aes)",
		.generic_driver = "adiantum(xchacha12-generic,aes-generic,nhpoly1305-generic)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(adiantum_xchacha12_aes_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "adiantum(xchacha20,aes)",
		.generic_driver = "adiantum(xchacha20-generic,aes-generic,nhpoly1305-generic)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(adiantum_xchacha20_aes_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "aegis128",
		.test = alg_test_aead,
		.suite = अणु
			.aead = __VECS(aegis128_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ansi_cprng",
		.test = alg_test_cprng,
		.suite = अणु
			.cprng = __VECS(ansi_cprng_aes_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(md5),ecb(cipher_null))",
		.test = alg_test_aead,
		.suite = अणु
			.aead = __VECS(hmac_md5_ecb_cipher_null_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha1),cbc(aes))",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = __VECS(hmac_sha1_aes_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha1),cbc(des))",
		.test = alg_test_aead,
		.suite = अणु
			.aead = __VECS(hmac_sha1_des_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha1),cbc(des3_ede))",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = __VECS(hmac_sha1_des3_ede_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha1),ctr(aes))",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "authenc(hmac(sha1),ecb(cipher_null))",
		.test = alg_test_aead,
		.suite = अणु
			.aead = __VECS(hmac_sha1_ecb_cipher_null_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha1),rfc3686(ctr(aes)))",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "authenc(hmac(sha224),cbc(des))",
		.test = alg_test_aead,
		.suite = अणु
			.aead = __VECS(hmac_sha224_des_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha224),cbc(des3_ede))",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = __VECS(hmac_sha224_des3_ede_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha256),cbc(aes))",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = __VECS(hmac_sha256_aes_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha256),cbc(des))",
		.test = alg_test_aead,
		.suite = अणु
			.aead = __VECS(hmac_sha256_des_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha256),cbc(des3_ede))",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = __VECS(hmac_sha256_des3_ede_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha256),ctr(aes))",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "authenc(hmac(sha256),rfc3686(ctr(aes)))",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "authenc(hmac(sha384),cbc(des))",
		.test = alg_test_aead,
		.suite = अणु
			.aead = __VECS(hmac_sha384_des_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha384),cbc(des3_ede))",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = __VECS(hmac_sha384_des3_ede_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha384),ctr(aes))",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "authenc(hmac(sha384),rfc3686(ctr(aes)))",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "authenc(hmac(sha512),cbc(aes))",
		.fips_allowed = 1,
		.test = alg_test_aead,
		.suite = अणु
			.aead = __VECS(hmac_sha512_aes_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha512),cbc(des))",
		.test = alg_test_aead,
		.suite = अणु
			.aead = __VECS(hmac_sha512_des_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha512),cbc(des3_ede))",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = __VECS(hmac_sha512_des3_ede_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "authenc(hmac(sha512),ctr(aes))",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "authenc(hmac(sha512),rfc3686(ctr(aes)))",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "blake2b-160",
		.test = alg_test_hash,
		.fips_allowed = 0,
		.suite = अणु
			.hash = __VECS(blake2b_160_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "blake2b-256",
		.test = alg_test_hash,
		.fips_allowed = 0,
		.suite = अणु
			.hash = __VECS(blake2b_256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "blake2b-384",
		.test = alg_test_hash,
		.fips_allowed = 0,
		.suite = अणु
			.hash = __VECS(blake2b_384_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "blake2b-512",
		.test = alg_test_hash,
		.fips_allowed = 0,
		.suite = अणु
			.hash = __VECS(blake2b_512_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "blake2s-128",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(blakes2s_128_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "blake2s-160",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(blakes2s_160_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "blake2s-224",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(blakes2s_224_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "blake2s-256",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(blakes2s_256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "cbc(aes)",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(aes_cbc_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "cbc(anubis)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(anubis_cbc_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "cbc(blowfish)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(bf_cbc_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "cbc(camellia)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(camellia_cbc_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "cbc(cast5)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(cast5_cbc_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "cbc(cast6)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(cast6_cbc_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "cbc(des)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(des_cbc_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "cbc(des3_ede)",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(des3_ede_cbc_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		/* Same as cbc(aes) except the key is stored in
		 * hardware secure memory which we reference by index
		 */
		.alg = "cbc(paes)",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		/* Same as cbc(sm4) except the key is stored in
		 * hardware secure memory which we reference by index
		 */
		.alg = "cbc(psm4)",
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "cbc(serpent)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(serpent_cbc_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "cbc(sm4)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(sm4_cbc_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "cbc(twofish)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(tf_cbc_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
#अगर IS_ENABLED(CONFIG_CRYPTO_PAES_S390)
		.alg = "cbc-paes-s390",
		.fips_allowed = 1,
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(aes_cbc_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
#पूर्ण_अगर
		.alg = "cbcmac(aes)",
		.fips_allowed = 1,
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(aes_cbcmac_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ccm(aes)",
		.generic_driver = "ccm_base(ctr(aes-generic),cbcmac(aes-generic))",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = अणु
				____VECS(aes_ccm_tv_ढाँचा),
				.einval_allowed = 1,
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "cfb(aes)",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(aes_cfb_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "cfb(sm4)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(sm4_cfb_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "chacha20",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(chacha20_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "cmac(aes)",
		.fips_allowed = 1,
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(aes_cmac128_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "cmac(des3_ede)",
		.fips_allowed = 1,
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(des3_ede_cmac64_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "compress_null",
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "crc32",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(crc32_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "crc32c",
		.test = alg_test_crc32c,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(crc32c_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "crct10dif",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(crct10dअगर_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ctr(aes)",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(aes_ctr_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ctr(blowfish)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(bf_ctr_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ctr(camellia)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(camellia_ctr_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ctr(cast5)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(cast5_ctr_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ctr(cast6)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(cast6_ctr_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ctr(des)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(des_ctr_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ctr(des3_ede)",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(des3_ede_ctr_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		/* Same as ctr(aes) except the key is stored in
		 * hardware secure memory which we reference by index
		 */
		.alg = "ctr(paes)",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु

		/* Same as ctr(sm4) except the key is stored in
		 * hardware secure memory which we reference by index
		 */
		.alg = "ctr(psm4)",
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "ctr(serpent)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(serpent_ctr_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ctr(sm4)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(sm4_ctr_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ctr(twofish)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(tf_ctr_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
#अगर IS_ENABLED(CONFIG_CRYPTO_PAES_S390)
		.alg = "ctr-paes-s390",
		.fips_allowed = 1,
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(aes_ctr_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
#पूर्ण_अगर
		.alg = "cts(cbc(aes))",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(cts_mode_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		/* Same as cts(cbc((aes)) except the key is stored in
		 * hardware secure memory which we reference by index
		 */
		.alg = "cts(cbc(paes))",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "curve25519",
		.test = alg_test_kpp,
		.suite = अणु
			.kpp = __VECS(curve25519_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "deflate",
		.test = alg_test_comp,
		.fips_allowed = 1,
		.suite = अणु
			.comp = अणु
				.comp = __VECS(deflate_comp_tv_ढाँचा),
				.decomp = __VECS(deflate_decomp_tv_ढाँचा)
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "dh",
		.test = alg_test_kpp,
		.fips_allowed = 1,
		.suite = अणु
			.kpp = __VECS(dh_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "digest_null",
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_nopr_ctr_aes128",
		.test = alg_test_drbg,
		.fips_allowed = 1,
		.suite = अणु
			.drbg = __VECS(drbg_nopr_ctr_aes128_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "drbg_nopr_ctr_aes192",
		.test = alg_test_drbg,
		.fips_allowed = 1,
		.suite = अणु
			.drbg = __VECS(drbg_nopr_ctr_aes192_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "drbg_nopr_ctr_aes256",
		.test = alg_test_drbg,
		.fips_allowed = 1,
		.suite = अणु
			.drbg = __VECS(drbg_nopr_ctr_aes256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		/*
		 * There is no need to specअगरically test the DRBG with every
		 * backend cipher -- covered by drbg_nopr_hmac_sha256 test
		 */
		.alg = "drbg_nopr_hmac_sha1",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_nopr_hmac_sha256",
		.test = alg_test_drbg,
		.fips_allowed = 1,
		.suite = अणु
			.drbg = __VECS(drbg_nopr_hmac_sha256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		/* covered by drbg_nopr_hmac_sha256 test */
		.alg = "drbg_nopr_hmac_sha384",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_nopr_hmac_sha512",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "drbg_nopr_sha1",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_nopr_sha256",
		.test = alg_test_drbg,
		.fips_allowed = 1,
		.suite = अणु
			.drbg = __VECS(drbg_nopr_sha256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		/* covered by drbg_nopr_sha256 test */
		.alg = "drbg_nopr_sha384",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_nopr_sha512",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_pr_ctr_aes128",
		.test = alg_test_drbg,
		.fips_allowed = 1,
		.suite = अणु
			.drbg = __VECS(drbg_pr_ctr_aes128_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		/* covered by drbg_pr_ctr_aes128 test */
		.alg = "drbg_pr_ctr_aes192",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_pr_ctr_aes256",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_pr_hmac_sha1",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_pr_hmac_sha256",
		.test = alg_test_drbg,
		.fips_allowed = 1,
		.suite = अणु
			.drbg = __VECS(drbg_pr_hmac_sha256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		/* covered by drbg_pr_hmac_sha256 test */
		.alg = "drbg_pr_hmac_sha384",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_pr_hmac_sha512",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "drbg_pr_sha1",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_pr_sha256",
		.test = alg_test_drbg,
		.fips_allowed = 1,
		.suite = अणु
			.drbg = __VECS(drbg_pr_sha256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		/* covered by drbg_pr_sha256 test */
		.alg = "drbg_pr_sha384",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "drbg_pr_sha512",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "ecb(aes)",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(aes_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(anubis)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(anubis_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(arc4)",
		.generic_driver = "ecb(arc4)-generic",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(arc4_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(blowfish)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(bf_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(camellia)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(camellia_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(cast5)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(cast5_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(cast6)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(cast6_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(cipher_null)",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "ecb(des)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(des_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(des3_ede)",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(des3_ede_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(fcrypt)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = अणु
				.vecs = fcrypt_pcbc_tv_ढाँचा,
				.count = 1
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(khazad)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(khazad_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		/* Same as ecb(aes) except the key is stored in
		 * hardware secure memory which we reference by index
		 */
		.alg = "ecb(paes)",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "ecb(seed)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(seed_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(serpent)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(serpent_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(sm4)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(sm4_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(tea)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(tea_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(twofish)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(tf_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(xeta)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(xeta_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecb(xtea)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(xtea_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
#अगर IS_ENABLED(CONFIG_CRYPTO_PAES_S390)
		.alg = "ecb-paes-s390",
		.fips_allowed = 1,
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(aes_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
#पूर्ण_अगर
#अगर_अघोषित CONFIG_CRYPTO_FIPS
		.alg = "ecdh-nist-p192",
		.test = alg_test_kpp,
		.fips_allowed = 1,
		.suite = अणु
			.kpp = __VECS(ecdh_p192_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
#पूर्ण_अगर
		.alg = "ecdh-nist-p256",
		.test = alg_test_kpp,
		.fips_allowed = 1,
		.suite = अणु
			.kpp = __VECS(ecdh_p256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecdsa-nist-p192",
		.test = alg_test_akcipher,
		.suite = अणु
			.akcipher = __VECS(ecdsa_nist_p192_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecdsa-nist-p256",
		.test = alg_test_akcipher,
		.suite = अणु
			.akcipher = __VECS(ecdsa_nist_p256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecdsa-nist-p384",
		.test = alg_test_akcipher,
		.suite = अणु
			.akcipher = __VECS(ecdsa_nist_p384_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ecrdsa",
		.test = alg_test_akcipher,
		.suite = अणु
			.akcipher = __VECS(ecrdsa_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "essiv(authenc(hmac(sha256),cbc(aes)),sha256)",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = __VECS(essiv_hmac_sha256_aes_cbc_tv_temp)
		पूर्ण
	पूर्ण, अणु
		.alg = "essiv(cbc(aes),sha256)",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(essiv_aes_cbc_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "gcm(aes)",
		.generic_driver = "gcm_base(ctr(aes-generic),ghash-generic)",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = __VECS(aes_gcm_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ghash",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(ghash_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(md5)",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(hmac_md5_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(rmd160)",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(hmac_rmd160_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(sha1)",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(hmac_sha1_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(sha224)",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(hmac_sha224_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(sha256)",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(hmac_sha256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(sha3-224)",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(hmac_sha3_224_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(sha3-256)",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(hmac_sha3_256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(sha3-384)",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(hmac_sha3_384_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(sha3-512)",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(hmac_sha3_512_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(sha384)",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(hmac_sha384_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(sha512)",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(hmac_sha512_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(sm3)",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(hmac_sm3_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(streebog256)",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(hmac_streebog256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "hmac(streebog512)",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(hmac_streebog512_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "jitterentropy_rng",
		.fips_allowed = 1,
		.test = alg_test_null,
	पूर्ण, अणु
		.alg = "kw(aes)",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(aes_kw_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "lrw(aes)",
		.generic_driver = "lrw(ecb(aes-generic))",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(aes_lrw_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "lrw(camellia)",
		.generic_driver = "lrw(ecb(camellia-generic))",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(camellia_lrw_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "lrw(cast6)",
		.generic_driver = "lrw(ecb(cast6-generic))",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(cast6_lrw_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "lrw(serpent)",
		.generic_driver = "lrw(ecb(serpent-generic))",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(serpent_lrw_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "lrw(twofish)",
		.generic_driver = "lrw(ecb(twofish-generic))",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(tf_lrw_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "lz4",
		.test = alg_test_comp,
		.fips_allowed = 1,
		.suite = अणु
			.comp = अणु
				.comp = __VECS(lz4_comp_tv_ढाँचा),
				.decomp = __VECS(lz4_decomp_tv_ढाँचा)
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "lz4hc",
		.test = alg_test_comp,
		.fips_allowed = 1,
		.suite = अणु
			.comp = अणु
				.comp = __VECS(lz4hc_comp_tv_ढाँचा),
				.decomp = __VECS(lz4hc_decomp_tv_ढाँचा)
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "lzo",
		.test = alg_test_comp,
		.fips_allowed = 1,
		.suite = अणु
			.comp = अणु
				.comp = __VECS(lzo_comp_tv_ढाँचा),
				.decomp = __VECS(lzo_decomp_tv_ढाँचा)
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "lzo-rle",
		.test = alg_test_comp,
		.fips_allowed = 1,
		.suite = अणु
			.comp = अणु
				.comp = __VECS(lzorle_comp_tv_ढाँचा),
				.decomp = __VECS(lzorle_decomp_tv_ढाँचा)
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "md4",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(md4_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "md5",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(md5_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "michael_mic",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(michael_mic_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "nhpoly1305",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(nhpoly1305_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "ofb(aes)",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(aes_ofb_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		/* Same as ofb(aes) except the key is stored in
		 * hardware secure memory which we reference by index
		 */
		.alg = "ofb(paes)",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "ofb(sm4)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(sm4_ofb_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "pcbc(fcrypt)",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(fcrypt_pcbc_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "pkcs1pad(rsa,sha224)",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "pkcs1pad(rsa,sha256)",
		.test = alg_test_akcipher,
		.fips_allowed = 1,
		.suite = अणु
			.akcipher = __VECS(pkcs1pad_rsa_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "pkcs1pad(rsa,sha384)",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "pkcs1pad(rsa,sha512)",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "poly1305",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(poly1305_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "rfc3686(ctr(aes))",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(aes_ctr_rfc3686_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "rfc3686(ctr(sm4))",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(sm4_ctr_rfc3686_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "rfc4106(gcm(aes))",
		.generic_driver = "rfc4106(gcm_base(ctr(aes-generic),ghash-generic))",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = अणु
				____VECS(aes_gcm_rfc4106_tv_ढाँचा),
				.einval_allowed = 1,
				.aad_iv = 1,
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "rfc4309(ccm(aes))",
		.generic_driver = "rfc4309(ccm_base(ctr(aes-generic),cbcmac(aes-generic)))",
		.test = alg_test_aead,
		.fips_allowed = 1,
		.suite = अणु
			.aead = अणु
				____VECS(aes_ccm_rfc4309_tv_ढाँचा),
				.einval_allowed = 1,
				.aad_iv = 1,
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "rfc4543(gcm(aes))",
		.generic_driver = "rfc4543(gcm_base(ctr(aes-generic),ghash-generic))",
		.test = alg_test_aead,
		.suite = अणु
			.aead = अणु
				____VECS(aes_gcm_rfc4543_tv_ढाँचा),
				.einval_allowed = 1,
				.aad_iv = 1,
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "rfc7539(chacha20,poly1305)",
		.test = alg_test_aead,
		.suite = अणु
			.aead = __VECS(rfc7539_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "rfc7539esp(chacha20,poly1305)",
		.test = alg_test_aead,
		.suite = अणु
			.aead = अणु
				____VECS(rfc7539esp_tv_ढाँचा),
				.einval_allowed = 1,
				.aad_iv = 1,
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "rmd160",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(rmd160_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "rsa",
		.test = alg_test_akcipher,
		.fips_allowed = 1,
		.suite = अणु
			.akcipher = __VECS(rsa_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "sha1",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(sha1_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "sha224",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(sha224_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "sha256",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(sha256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "sha3-224",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(sha3_224_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "sha3-256",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(sha3_256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "sha3-384",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(sha3_384_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "sha3-512",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(sha3_512_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "sha384",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(sha384_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "sha512",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(sha512_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "sm2",
		.test = alg_test_akcipher,
		.suite = अणु
			.akcipher = __VECS(sm2_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "sm3",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(sm3_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "streebog256",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(streebog256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "streebog512",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(streebog512_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "vmac64(aes)",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(vmac64_aes_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "wp256",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(wp256_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "wp384",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(wp384_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "wp512",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(wp512_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "xcbc(aes)",
		.test = alg_test_hash,
		.suite = अणु
			.hash = __VECS(aes_xcbc128_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "xchacha12",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(xchacha12_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "xchacha20",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(xchacha20_tv_ढाँचा)
		पूर्ण,
	पूर्ण, अणु
		.alg = "xts(aes)",
		.generic_driver = "xts(ecb(aes-generic))",
		.test = alg_test_skcipher,
		.fips_allowed = 1,
		.suite = अणु
			.cipher = __VECS(aes_xts_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "xts(camellia)",
		.generic_driver = "xts(ecb(camellia-generic))",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(camellia_xts_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "xts(cast6)",
		.generic_driver = "xts(ecb(cast6-generic))",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(cast6_xts_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		/* Same as xts(aes) except the key is stored in
		 * hardware secure memory which we reference by index
		 */
		.alg = "xts(paes)",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "xts(serpent)",
		.generic_driver = "xts(ecb(serpent-generic))",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(serpent_xts_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "xts(twofish)",
		.generic_driver = "xts(ecb(twofish-generic))",
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(tf_xts_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
#अगर IS_ENABLED(CONFIG_CRYPTO_PAES_S390)
		.alg = "xts-paes-s390",
		.fips_allowed = 1,
		.test = alg_test_skcipher,
		.suite = अणु
			.cipher = __VECS(aes_xts_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
#पूर्ण_अगर
		.alg = "xts4096(paes)",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "xts512(paes)",
		.test = alg_test_null,
		.fips_allowed = 1,
	पूर्ण, अणु
		.alg = "xxhash64",
		.test = alg_test_hash,
		.fips_allowed = 1,
		.suite = अणु
			.hash = __VECS(xxhash64_tv_ढाँचा)
		पूर्ण
	पूर्ण, अणु
		.alg = "zlib-deflate",
		.test = alg_test_comp,
		.fips_allowed = 1,
		.suite = अणु
			.comp = अणु
				.comp = __VECS(zlib_deflate_comp_tv_ढाँचा),
				.decomp = __VECS(zlib_deflate_decomp_tv_ढाँचा)
			पूर्ण
		पूर्ण
	पूर्ण, अणु
		.alg = "zstd",
		.test = alg_test_comp,
		.fips_allowed = 1,
		.suite = अणु
			.comp = अणु
				.comp = __VECS(zstd_comp_tv_ढाँचा),
				.decomp = __VECS(zstd_decomp_tv_ढाँचा)
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण;

अटल व्योम alg_check_test_descs_order(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < ARRAY_SIZE(alg_test_descs); i++) अणु
		पूर्णांक dअगरf = म_भेद(alg_test_descs[i - 1].alg,
				  alg_test_descs[i].alg);

		अगर (WARN_ON(dअगरf > 0)) अणु
			pr_warn("testmgr: alg_test_descs entries in wrong order: '%s' before '%s'\n",
				alg_test_descs[i - 1].alg,
				alg_test_descs[i].alg);
		पूर्ण

		अगर (WARN_ON(dअगरf == 0)) अणु
			pr_warn("testmgr: duplicate alg_test_descs entry: '%s'\n",
				alg_test_descs[i].alg);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम alg_check_testvec_configs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(शेष_cipher_testvec_configs); i++)
		WARN_ON(!valid_testvec_config(
				&शेष_cipher_testvec_configs[i]));

	क्रम (i = 0; i < ARRAY_SIZE(शेष_hash_testvec_configs); i++)
		WARN_ON(!valid_testvec_config(
				&शेष_hash_testvec_configs[i]));
पूर्ण

अटल व्योम tesपंचांगgr_oneसमय_init(व्योम)
अणु
	alg_check_test_descs_order();
	alg_check_testvec_configs();

#अगर_घोषित CONFIG_CRYPTO_MANAGER_EXTRA_TESTS
	pr_warn("alg: extra crypto tests enabled.  This is intended for developer use only.\n");
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक alg_find_test(स्थिर अक्षर *alg)
अणु
	पूर्णांक start = 0;
	पूर्णांक end = ARRAY_SIZE(alg_test_descs);

	जबतक (start < end) अणु
		पूर्णांक i = (start + end) / 2;
		पूर्णांक dअगरf = म_भेद(alg_test_descs[i].alg, alg);

		अगर (dअगरf > 0) अणु
			end = i;
			जारी;
		पूर्ण

		अगर (dअगरf < 0) अणु
			start = i + 1;
			जारी;
		पूर्ण

		वापस i;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक alg_test(स्थिर अक्षर *driver, स्थिर अक्षर *alg, u32 type, u32 mask)
अणु
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक rc;

	अगर (!fips_enabled && notests) अणु
		prपूर्णांकk_once(KERN_INFO "alg: self-tests disabled\n");
		वापस 0;
	पूर्ण

	DO_ONCE(tesपंचांगgr_oneसमय_init);

	अगर ((type & CRYPTO_ALG_TYPE_MASK) == CRYPTO_ALG_TYPE_CIPHER) अणु
		अक्षर nalg[CRYPTO_MAX_ALG_NAME];

		अगर (snम_लिखो(nalg, माप(nalg), "ecb(%s)", alg) >=
		    माप(nalg))
			वापस -ENAMETOOLONG;

		i = alg_find_test(nalg);
		अगर (i < 0)
			जाओ notest;

		अगर (fips_enabled && !alg_test_descs[i].fips_allowed)
			जाओ non_fips_alg;

		rc = alg_test_cipher(alg_test_descs + i, driver, type, mask);
		जाओ test_करोne;
	पूर्ण

	i = alg_find_test(alg);
	j = alg_find_test(driver);
	अगर (i < 0 && j < 0)
		जाओ notest;

	अगर (fips_enabled && ((i >= 0 && !alg_test_descs[i].fips_allowed) ||
			     (j >= 0 && !alg_test_descs[j].fips_allowed)))
		जाओ non_fips_alg;

	rc = 0;
	अगर (i >= 0)
		rc |= alg_test_descs[i].test(alg_test_descs + i, driver,
					     type, mask);
	अगर (j >= 0 && j != i)
		rc |= alg_test_descs[j].test(alg_test_descs + j, driver,
					     type, mask);

test_करोne:
	अगर (rc) अणु
		अगर (fips_enabled || panic_on_fail) अणु
			fips_fail_notअगरy();
			panic("alg: self-tests for %s (%s) failed in %s mode!\n",
			      driver, alg,
			      fips_enabled ? "fips" : "panic_on_fail");
		पूर्ण
		WARN(1, "alg: self-tests for %s (%s) failed (rc=%d)",
		     driver, alg, rc);
	पूर्ण अन्यथा अणु
		अगर (fips_enabled)
			pr_info("alg: self-tests for %s (%s) passed\n",
				driver, alg);
	पूर्ण

	वापस rc;

notest:
	prपूर्णांकk(KERN_INFO "alg: No test for %s (%s)\n", alg, driver);
	वापस 0;
non_fips_alg:
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर /* CONFIG_CRYPTO_MANAGER_DISABLE_TESTS */

EXPORT_SYMBOL_GPL(alg_test);
