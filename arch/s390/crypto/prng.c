<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2006, 2015
 * Author(s): Jan Glauber <jan.glauber@de.ibm.com>
 *	      Harald Freudenberger <freude@de.ibm.com>
 * Driver क्रम the s390 pseuकरो अक्रमom number generator
 */

#घोषणा KMSG_COMPONENT "prng"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/fips.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/debug.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/cpacf.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("s390 PRNG interface");


#घोषणा PRNG_MODE_AUTO	  0
#घोषणा PRNG_MODE_TDES	  1
#घोषणा PRNG_MODE_SHA512  2

अटल अचिन्हित पूर्णांक prng_mode = PRNG_MODE_AUTO;
module_param_named(mode, prng_mode, पूर्णांक, 0);
MODULE_PARM_DESC(prng_mode, "PRNG mode: 0 - auto, 1 - TDES, 2 - SHA512");


#घोषणा PRNG_CHUNKSIZE_TDES_MIN   8
#घोषणा PRNG_CHUNKSIZE_TDES_MAX   (64*1024)
#घोषणा PRNG_CHUNKSIZE_SHA512_MIN 64
#घोषणा PRNG_CHUNKSIZE_SHA512_MAX (64*1024)

अटल अचिन्हित पूर्णांक prng_chunk_size = 256;
module_param_named(chunksize, prng_chunk_size, पूर्णांक, 0);
MODULE_PARM_DESC(prng_chunk_size, "PRNG read chunk size in bytes");


#घोषणा PRNG_RESEED_LIMIT_TDES		 4096
#घोषणा PRNG_RESEED_LIMIT_TDES_LOWER	 4096
#घोषणा PRNG_RESEED_LIMIT_SHA512       100000
#घोषणा PRNG_RESEED_LIMIT_SHA512_LOWER	10000

अटल अचिन्हित पूर्णांक prng_reseed_limit;
module_param_named(reseed_limit, prng_reseed_limit, पूर्णांक, 0);
MODULE_PARM_DESC(prng_reseed_limit, "PRNG reseed limit");

अटल bool trng_available;

/*
 * Any one who considers arithmetical methods of producing अक्रमom digits is,
 * of course, in a state of sin. -- John von Neumann
 */

अटल पूर्णांक prng_errorflag;

#घोषणा PRNG_GEN_ENTROPY_FAILED  1
#घोषणा PRNG_SELFTEST_FAILED	 2
#घोषणा PRNG_INSTANTIATE_FAILED  3
#घोषणा PRNG_SEED_FAILED	 4
#घोषणा PRNG_RESEED_FAILED	 5
#घोषणा PRNG_GEN_FAILED		 6

काष्ठा prng_ws_s अणु
	u8  parm_block[32];
	u32 reseed_counter;
	u64 byte_counter;
पूर्ण;

काष्ठा prno_ws_s अणु
	u32 res;
	u32 reseed_counter;
	u64 stream_bytes;
	u8  V[112];
	u8  C[112];
पूर्ण;

काष्ठा prng_data_s अणु
	काष्ठा mutex mutex;
	जोड़ अणु
		काष्ठा prng_ws_s prngws;
		काष्ठा prno_ws_s prnows;
	पूर्ण;
	u8 *buf;
	u32 rest;
	u8 *prev;
पूर्ण;

अटल काष्ठा prng_data_s *prng_data;

/* initial parameter block क्रम tdes mode, copied from libica */
अटल स्थिर u8 initial_parm_block[32] __initस्थिर = अणु
	0x0F, 0x2B, 0x8E, 0x63, 0x8C, 0x8E, 0xD2, 0x52,
	0x64, 0xB7, 0xA0, 0x7B, 0x75, 0x28, 0xB8, 0xF4,
	0x75, 0x5F, 0xD2, 0xA6, 0x8D, 0x97, 0x11, 0xFF,
	0x49, 0xD8, 0x23, 0xF3, 0x7E, 0x21, 0xEC, 0xA0 पूर्ण;


/*** helper functions ***/

/*
 * generate_entropy:
 * This function fills a given buffer with अक्रमom bytes. The entropy within
 * the अक्रमom bytes given back is assumed to have at least 50% - meaning
 * a 64 bytes buffer has at least 64 * 8 / 2 = 256 bits of entropy.
 * Within the function the entropy generation is करोne in junks of 64 bytes.
 * So the caller should also ask क्रम buffer fill in multiples of 64 bytes.
 * The generation of the entropy is based on the assumption that every stckf()
 * invocation produces 0.5 bits of entropy. To accumulate 256 bits of entropy
 * at least 512 stckf() values are needed. The entropy relevant part of the
 * stckf value is bit 51 (counting starts at the left with bit nr 0) so
 * here we use the lower 4 bytes and exor the values पूर्णांकo 2k of bufferspace.
 * To be on the save side, अगर there is ever a problem with stckf() the
 * other half of the page buffer is filled with bytes from uअक्रमom via
 * get_अक्रमom_bytes(), so this function consumes 2k of uअक्रमom क्रम each
 * requested 64 bytes output data. Finally the buffer page is condensed पूर्णांकo
 * a 64 byte value by hashing with a SHA512 hash.
 */
अटल पूर्णांक generate_entropy(u8 *ebuf, माप_प्रकार nbytes)
अणु
	पूर्णांक n, ret = 0;
	u8 *pg, pblock[80] = अणु
		/* 8 x 64 bit init values */
		0x6A, 0x09, 0xE6, 0x67, 0xF3, 0xBC, 0xC9, 0x08,
		0xBB, 0x67, 0xAE, 0x85, 0x84, 0xCA, 0xA7, 0x3B,
		0x3C, 0x6E, 0xF3, 0x72, 0xFE, 0x94, 0xF8, 0x2B,
		0xA5, 0x4F, 0xF5, 0x3A, 0x5F, 0x1D, 0x36, 0xF1,
		0x51, 0x0E, 0x52, 0x7F, 0xAD, 0xE6, 0x82, 0xD1,
		0x9B, 0x05, 0x68, 0x8C, 0x2B, 0x3E, 0x6C, 0x1F,
		0x1F, 0x83, 0xD9, 0xAB, 0xFB, 0x41, 0xBD, 0x6B,
		0x5B, 0xE0, 0xCD, 0x19, 0x13, 0x7E, 0x21, 0x79,
		/* 128 bit counter total message bit length */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00 पूर्ण;

	/* allocate one page stckf buffer */
	pg = (u8 *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!pg) अणु
		prng_errorflag = PRNG_GEN_ENTROPY_FAILED;
		वापस -ENOMEM;
	पूर्ण

	/* fill the ebuf in chunks of 64 byte each */
	जबतक (nbytes) अणु
		/* fill lower 2k with uअक्रमom bytes */
		get_अक्रमom_bytes(pg, PAGE_SIZE / 2);
		/* exor upper 2k with 512 stckf values, offset 4 bytes each */
		क्रम (n = 0; n < 512; n++) अणु
			पूर्णांक offset = (PAGE_SIZE / 2) + (n * 4) - 4;
			u64 *p = (u64 *)(pg + offset);
			*p ^= get_tod_घड़ी_fast();
		पूर्ण
		/* hash over the filled page */
		cpacf_klmd(CPACF_KLMD_SHA_512, pblock, pg, PAGE_SIZE);
		n = (nbytes < 64) ? nbytes : 64;
		स_नकल(ebuf, pblock, n);
		ret += n;
		ebuf += n;
		nbytes -= n;
	पूर्ण

	memzero_explicit(pblock, माप(pblock));
	memzero_explicit(pg, PAGE_SIZE);
	मुक्त_page((अचिन्हित दीर्घ)pg);
	वापस ret;
पूर्ण


/*** tdes functions ***/

अटल व्योम prng_tdes_add_entropy(व्योम)
अणु
	__u64 entropy[4];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		cpacf_kmc(CPACF_KMC_PRNG, prng_data->prngws.parm_block,
			  (अक्षर *) entropy, (अक्षर *) entropy,
			  माप(entropy));
		स_नकल(prng_data->prngws.parm_block, entropy, माप(entropy));
	पूर्ण
पूर्ण


अटल व्योम prng_tdes_seed(पूर्णांक nbytes)
अणु
	अक्षर buf[16];
	पूर्णांक i = 0;

	BUG_ON(nbytes > माप(buf));

	get_अक्रमom_bytes(buf, nbytes);

	/* Add the entropy */
	जबतक (nbytes >= 8) अणु
		*((__u64 *)prng_data->prngws.parm_block) ^= *((__u64 *)(buf+i));
		prng_tdes_add_entropy();
		i += 8;
		nbytes -= 8;
	पूर्ण
	prng_tdes_add_entropy();
	prng_data->prngws.reseed_counter = 0;
पूर्ण


अटल पूर्णांक __init prng_tdes_instantiate(व्योम)
अणु
	पूर्णांक datalen;

	pr_debug("prng runs in TDES mode with "
		 "chunksize=%d and reseed_limit=%u\n",
		 prng_chunk_size, prng_reseed_limit);

	/* memory allocation, prng_data काष्ठा init, mutex init */
	datalen = माप(काष्ठा prng_data_s) + prng_chunk_size;
	prng_data = kzalloc(datalen, GFP_KERNEL);
	अगर (!prng_data) अणु
		prng_errorflag = PRNG_INSTANTIATE_FAILED;
		वापस -ENOMEM;
	पूर्ण
	mutex_init(&prng_data->mutex);
	prng_data->buf = ((u8 *)prng_data) + माप(काष्ठा prng_data_s);
	स_नकल(prng_data->prngws.parm_block, initial_parm_block, 32);

	/* initialize the PRNG, add 128 bits of entropy */
	prng_tdes_seed(16);

	वापस 0;
पूर्ण


अटल व्योम prng_tdes_deinstantiate(व्योम)
अणु
	pr_debug("The prng module stopped "
		 "after running in triple DES mode\n");
	kमुक्त_sensitive(prng_data);
पूर्ण


/*** sha512 functions ***/

अटल पूर्णांक __init prng_sha512_selftest(व्योम)
अणु
	/* NIST DRBG testvector क्रम Hash Drbg, Sha-512, Count #0 */
	अटल स्थिर u8 seed[] __initस्थिर = अणु
		0x6b, 0x50, 0xa7, 0xd8, 0xf8, 0xa5, 0x5d, 0x7a,
		0x3d, 0xf8, 0xbb, 0x40, 0xbc, 0xc3, 0xb7, 0x22,
		0xd8, 0x70, 0x8d, 0xe6, 0x7f, 0xda, 0x01, 0x0b,
		0x03, 0xc4, 0xc8, 0x4d, 0x72, 0x09, 0x6f, 0x8c,
		0x3e, 0xc6, 0x49, 0xcc, 0x62, 0x56, 0xd9, 0xfa,
		0x31, 0xdb, 0x7a, 0x29, 0x04, 0xaa, 0xf0, 0x25 पूर्ण;
	अटल स्थिर u8 V0[] __initस्थिर = अणु
		0x00, 0xad, 0xe3, 0x6f, 0x9a, 0x01, 0xc7, 0x76,
		0x61, 0x34, 0x35, 0xf5, 0x4e, 0x24, 0x74, 0x22,
		0x21, 0x9a, 0x29, 0x89, 0xc7, 0x93, 0x2e, 0x60,
		0x1e, 0xe8, 0x14, 0x24, 0x8d, 0xd5, 0x03, 0xf1,
		0x65, 0x5d, 0x08, 0x22, 0x72, 0xd5, 0xad, 0x95,
		0xe1, 0x23, 0x1e, 0x8a, 0xa7, 0x13, 0xd9, 0x2b,
		0x5e, 0xbc, 0xbb, 0x80, 0xab, 0x8d, 0xe5, 0x79,
		0xab, 0x5b, 0x47, 0x4e, 0xdd, 0xee, 0x6b, 0x03,
		0x8f, 0x0f, 0x5c, 0x5e, 0xa9, 0x1a, 0x83, 0xdd,
		0xd3, 0x88, 0xb2, 0x75, 0x4b, 0xce, 0x83, 0x36,
		0x57, 0x4b, 0xf1, 0x5c, 0xca, 0x7e, 0x09, 0xc0,
		0xd3, 0x89, 0xc6, 0xe0, 0xda, 0xc4, 0x81, 0x7e,
		0x5b, 0xf9, 0xe1, 0x01, 0xc1, 0x92, 0x05, 0xea,
		0xf5, 0x2f, 0xc6, 0xc6, 0xc7, 0x8f, 0xbc, 0xf4 पूर्ण;
	अटल स्थिर u8 C0[] __initस्थिर = अणु
		0x00, 0xf4, 0xa3, 0xe5, 0xa0, 0x72, 0x63, 0x95,
		0xc6, 0x4f, 0x48, 0xd0, 0x8b, 0x5b, 0x5f, 0x8e,
		0x6b, 0x96, 0x1f, 0x16, 0xed, 0xbc, 0x66, 0x94,
		0x45, 0x31, 0xd7, 0x47, 0x73, 0x22, 0xa5, 0x86,
		0xce, 0xc0, 0x4c, 0xac, 0x63, 0xb8, 0x39, 0x50,
		0xbf, 0xe6, 0x59, 0x6c, 0x38, 0x58, 0x99, 0x1f,
		0x27, 0xa7, 0x9d, 0x71, 0x2a, 0xb3, 0x7b, 0xf9,
		0xfb, 0x17, 0x86, 0xaa, 0x99, 0x81, 0xaa, 0x43,
		0xe4, 0x37, 0xd3, 0x1e, 0x6e, 0xe5, 0xe6, 0xee,
		0xc2, 0xed, 0x95, 0x4f, 0x53, 0x0e, 0x46, 0x8a,
		0xcc, 0x45, 0xa5, 0xdb, 0x69, 0x0d, 0x81, 0xc9,
		0x32, 0x92, 0xbc, 0x8f, 0x33, 0xe6, 0xf6, 0x09,
		0x7c, 0x8e, 0x05, 0x19, 0x0d, 0xf1, 0xb6, 0xcc,
		0xf3, 0x02, 0x21, 0x90, 0x25, 0xec, 0xed, 0x0e पूर्ण;
	अटल स्थिर u8 अक्रमom[] __initस्थिर = अणु
		0x95, 0xb7, 0xf1, 0x7e, 0x98, 0x02, 0xd3, 0x57,
		0x73, 0x92, 0xc6, 0xa9, 0xc0, 0x80, 0x83, 0xb6,
		0x7d, 0xd1, 0x29, 0x22, 0x65, 0xb5, 0xf4, 0x2d,
		0x23, 0x7f, 0x1c, 0x55, 0xbb, 0x9b, 0x10, 0xbf,
		0xcf, 0xd8, 0x2c, 0x77, 0xa3, 0x78, 0xb8, 0x26,
		0x6a, 0x00, 0x99, 0x14, 0x3b, 0x3c, 0x2d, 0x64,
		0x61, 0x1e, 0xee, 0xb6, 0x9a, 0xcd, 0xc0, 0x55,
		0x95, 0x7c, 0x13, 0x9e, 0x8b, 0x19, 0x0c, 0x7a,
		0x06, 0x95, 0x5f, 0x2c, 0x79, 0x7c, 0x27, 0x78,
		0xde, 0x94, 0x03, 0x96, 0xa5, 0x01, 0xf4, 0x0e,
		0x91, 0x39, 0x6a, 0xcf, 0x8d, 0x7e, 0x45, 0xeb,
		0xdb, 0xb5, 0x3b, 0xbf, 0x8c, 0x97, 0x52, 0x30,
		0xd2, 0xf0, 0xff, 0x91, 0x06, 0xc7, 0x61, 0x19,
		0xae, 0x49, 0x8e, 0x7f, 0xbc, 0x03, 0xd9, 0x0f,
		0x8e, 0x4c, 0x51, 0x62, 0x7a, 0xed, 0x5c, 0x8d,
		0x42, 0x63, 0xd5, 0xd2, 0xb9, 0x78, 0x87, 0x3a,
		0x0d, 0xe5, 0x96, 0xee, 0x6d, 0xc7, 0xf7, 0xc2,
		0x9e, 0x37, 0xee, 0xe8, 0xb3, 0x4c, 0x90, 0xdd,
		0x1c, 0xf6, 0xa9, 0xdd, 0xb2, 0x2b, 0x4c, 0xbd,
		0x08, 0x6b, 0x14, 0xb3, 0x5d, 0xe9, 0x3d, 0xa2,
		0xd5, 0xcb, 0x18, 0x06, 0x69, 0x8c, 0xbd, 0x7b,
		0xbb, 0x67, 0xbf, 0xe3, 0xd3, 0x1f, 0xd2, 0xd1,
		0xdb, 0xd2, 0xa1, 0xe0, 0x58, 0xa3, 0xeb, 0x99,
		0xd7, 0xe5, 0x1f, 0x1a, 0x93, 0x8e, 0xed, 0x5e,
		0x1c, 0x1d, 0xe2, 0x3a, 0x6b, 0x43, 0x45, 0xd3,
		0x19, 0x14, 0x09, 0xf9, 0x2f, 0x39, 0xb3, 0x67,
		0x0d, 0x8d, 0xbf, 0xb6, 0x35, 0xd8, 0xe6, 0xa3,
		0x69, 0x32, 0xd8, 0x10, 0x33, 0xd1, 0x44, 0x8d,
		0x63, 0xb4, 0x03, 0xdd, 0xf8, 0x8e, 0x12, 0x1b,
		0x6e, 0x81, 0x9a, 0xc3, 0x81, 0x22, 0x6c, 0x13,
		0x21, 0xe4, 0xb0, 0x86, 0x44, 0xf6, 0x72, 0x7c,
		0x36, 0x8c, 0x5a, 0x9f, 0x7a, 0x4b, 0x3e, 0xe2 पूर्ण;

	u8 buf[माप(अक्रमom)];
	काष्ठा prno_ws_s ws;

	स_रखो(&ws, 0, माप(ws));

	/* initial seed */
	cpacf_prno(CPACF_PRNO_SHA512_DRNG_SEED,
		   &ws, शून्य, 0, seed, माप(seed));

	/* check working states V and C */
	अगर (स_भेद(ws.V, V0, माप(V0)) != 0
	    || स_भेद(ws.C, C0, माप(C0)) != 0) अणु
		pr_err("The prng self test state test "
		       "for the SHA-512 mode failed\n");
		prng_errorflag = PRNG_SELFTEST_FAILED;
		वापस -EIO;
	पूर्ण

	/* generate अक्रमom bytes */
	cpacf_prno(CPACF_PRNO_SHA512_DRNG_GEN,
		   &ws, buf, माप(buf), शून्य, 0);
	cpacf_prno(CPACF_PRNO_SHA512_DRNG_GEN,
		   &ws, buf, माप(buf), शून्य, 0);

	/* check against expected data */
	अगर (स_भेद(buf, अक्रमom, माप(अक्रमom)) != 0) अणु
		pr_err("The prng self test data test "
		       "for the SHA-512 mode failed\n");
		prng_errorflag = PRNG_SELFTEST_FAILED;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक __init prng_sha512_instantiate(व्योम)
अणु
	पूर्णांक ret, datalen, seedlen;
	u8 seed[128 + 16];

	pr_debug("prng runs in SHA-512 mode "
		 "with chunksize=%d and reseed_limit=%u\n",
		 prng_chunk_size, prng_reseed_limit);

	/* memory allocation, prng_data काष्ठा init, mutex init */
	datalen = माप(काष्ठा prng_data_s) + prng_chunk_size;
	अगर (fips_enabled)
		datalen += prng_chunk_size;
	prng_data = kzalloc(datalen, GFP_KERNEL);
	अगर (!prng_data) अणु
		prng_errorflag = PRNG_INSTANTIATE_FAILED;
		वापस -ENOMEM;
	पूर्ण
	mutex_init(&prng_data->mutex);
	prng_data->buf = ((u8 *)prng_data) + माप(काष्ठा prng_data_s);

	/* selftest */
	ret = prng_sha512_selftest();
	अगर (ret)
		जाओ outमुक्त;

	/* generate initial seed, we need at least  256 + 128 bits entropy. */
	अगर (trng_available) अणु
		/*
		 * Trng available, so use it. The trng works in chunks of
		 * 32 bytes and produces 100% entropy. So we pull 64 bytes
		 * which gives us 512 bits entropy.
		 */
		seedlen = 2 * 32;
		cpacf_trng(शून्य, 0, seed, seedlen);
	पूर्ण अन्यथा अणु
		/*
		 * No trng available, so use the generate_entropy() function.
		 * This function works in 64 byte junks and produces
		 * 50% entropy. So we pull 2*64 bytes which gives us 512 bits
		 * of entropy.
		 */
		seedlen = 2 * 64;
		ret = generate_entropy(seed, seedlen);
		अगर (ret != seedlen)
			जाओ outमुक्त;
	पूर्ण

	/* append the seed by 16 bytes of unique nonce */
	store_tod_घड़ी_ext((जोड़ tod_घड़ी *)(seed + seedlen));
	seedlen += 16;

	/* now initial seed of the prno drng */
	cpacf_prno(CPACF_PRNO_SHA512_DRNG_SEED,
		   &prng_data->prnows, शून्य, 0, seed, seedlen);
	memzero_explicit(seed, माप(seed));

	/* अगर fips mode is enabled, generate a first block of अक्रमom
	   bytes क्रम the FIPS 140-2 Conditional Self Test */
	अगर (fips_enabled) अणु
		prng_data->prev = prng_data->buf + prng_chunk_size;
		cpacf_prno(CPACF_PRNO_SHA512_DRNG_GEN,
			   &prng_data->prnows,
			   prng_data->prev, prng_chunk_size, शून्य, 0);
	पूर्ण

	वापस 0;

outमुक्त:
	kमुक्त(prng_data);
	वापस ret;
पूर्ण


अटल व्योम prng_sha512_deinstantiate(व्योम)
अणु
	pr_debug("The prng module stopped after running in SHA-512 mode\n");
	kमुक्त_sensitive(prng_data);
पूर्ण


अटल पूर्णांक prng_sha512_reseed(व्योम)
अणु
	पूर्णांक ret, seedlen;
	u8 seed[64];

	/* We need at least 256 bits of fresh entropy क्रम reseeding */
	अगर (trng_available) अणु
		/* trng produces 256 bits entropy in 32 bytes */
		seedlen = 32;
		cpacf_trng(शून्य, 0, seed, seedlen);
	पूर्ण अन्यथा अणु
		/* generate_entropy() produces 256 bits entropy in 64 bytes */
		seedlen = 64;
		ret = generate_entropy(seed, seedlen);
		अगर (ret != माप(seed))
			वापस ret;
	पूर्ण

	/* करो a reseed of the prno drng with this bytestring */
	cpacf_prno(CPACF_PRNO_SHA512_DRNG_SEED,
		   &prng_data->prnows, शून्य, 0, seed, seedlen);
	memzero_explicit(seed, माप(seed));

	वापस 0;
पूर्ण


अटल पूर्णांक prng_sha512_generate(u8 *buf, माप_प्रकार nbytes)
अणु
	पूर्णांक ret;

	/* reseed needed ? */
	अगर (prng_data->prnows.reseed_counter > prng_reseed_limit) अणु
		ret = prng_sha512_reseed();
		अगर (ret)
			वापस ret;
	पूर्ण

	/* PRNO generate */
	cpacf_prno(CPACF_PRNO_SHA512_DRNG_GEN,
		   &prng_data->prnows, buf, nbytes, शून्य, 0);

	/* FIPS 140-2 Conditional Self Test */
	अगर (fips_enabled) अणु
		अगर (!स_भेद(prng_data->prev, buf, nbytes)) अणु
			prng_errorflag = PRNG_GEN_FAILED;
			वापस -EILSEQ;
		पूर्ण
		स_नकल(prng_data->prev, buf, nbytes);
	पूर्ण

	वापस nbytes;
पूर्ण


/*** file io functions ***/

अटल पूर्णांक prng_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस nonseekable_खोलो(inode, file);
पूर्ण


अटल sमाप_प्रकार prng_tdes_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
			      माप_प्रकार nbytes, loff_t *ppos)
अणु
	पूर्णांक chunk, n, ret = 0;

	/* lock prng_data काष्ठा */
	अगर (mutex_lock_पूर्णांकerruptible(&prng_data->mutex))
		वापस -ERESTARTSYS;

	जबतक (nbytes) अणु
		अगर (need_resched()) अणु
			अगर (संकेत_pending(current)) अणु
				अगर (ret == 0)
					ret = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			/* give mutex मुक्त beक्रमe calling schedule() */
			mutex_unlock(&prng_data->mutex);
			schedule();
			/* occopy mutex again */
			अगर (mutex_lock_पूर्णांकerruptible(&prng_data->mutex)) अणु
				अगर (ret == 0)
					ret = -ERESTARTSYS;
				वापस ret;
			पूर्ण
		पूर्ण

		/*
		 * we lose some अक्रमom bytes अगर an attacker issues
		 * पढ़ोs < 8 bytes, but we करोn't care
		 */
		chunk = min_t(पूर्णांक, nbytes, prng_chunk_size);

		/* PRNG only likes multiples of 8 bytes */
		n = (chunk + 7) & -8;

		अगर (prng_data->prngws.reseed_counter > prng_reseed_limit)
			prng_tdes_seed(8);

		/* अगर the CPU supports PRNG stckf is present too */
		*((अचिन्हित दीर्घ दीर्घ *)prng_data->buf) = get_tod_घड़ी_fast();

		/*
		 * Beside the STCKF the input क्रम the TDES-EDE is the output
		 * of the last operation. We dअगरfer here from X9.17 since we
		 * only store one बारtamp पूर्णांकo the buffer. Padding the whole
		 * buffer with बारtamps करोes not improve security, since
		 * successive stckf have nearly स्थिरant offsets.
		 * If an attacker knows the first बारtamp it would be
		 * trivial to guess the additional values. One बारtamp
		 * is thereक्रमe enough and still guarantees unique input values.
		 *
		 * Note: you can still get strict X9.17 conक्रमmity by setting
		 * prng_chunk_size to 8 bytes.
		 */
		cpacf_kmc(CPACF_KMC_PRNG, prng_data->prngws.parm_block,
			  prng_data->buf, prng_data->buf, n);

		prng_data->prngws.byte_counter += n;
		prng_data->prngws.reseed_counter += n;

		अगर (copy_to_user(ubuf, prng_data->buf, chunk)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		nbytes -= chunk;
		ret += chunk;
		ubuf += chunk;
	पूर्ण

	/* unlock prng_data काष्ठा */
	mutex_unlock(&prng_data->mutex);

	वापस ret;
पूर्ण


अटल sमाप_प्रकार prng_sha512_पढ़ो(काष्ठा file *file, अक्षर __user *ubuf,
				माप_प्रकार nbytes, loff_t *ppos)
अणु
	पूर्णांक n, ret = 0;
	u8 *p;

	/* अगर errorflag is set करो nothing and वापस 'broken pipe' */
	अगर (prng_errorflag)
		वापस -EPIPE;

	/* lock prng_data काष्ठा */
	अगर (mutex_lock_पूर्णांकerruptible(&prng_data->mutex))
		वापस -ERESTARTSYS;

	जबतक (nbytes) अणु
		अगर (need_resched()) अणु
			अगर (संकेत_pending(current)) अणु
				अगर (ret == 0)
					ret = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			/* give mutex मुक्त beक्रमe calling schedule() */
			mutex_unlock(&prng_data->mutex);
			schedule();
			/* occopy mutex again */
			अगर (mutex_lock_पूर्णांकerruptible(&prng_data->mutex)) अणु
				अगर (ret == 0)
					ret = -ERESTARTSYS;
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (prng_data->rest) अणु
			/* push left over अक्रमom bytes from the previous पढ़ो */
			p = prng_data->buf + prng_chunk_size - prng_data->rest;
			n = (nbytes < prng_data->rest) ?
				nbytes : prng_data->rest;
			prng_data->rest -= n;
		पूर्ण अन्यथा अणु
			/* generate one chunk of अक्रमom bytes पूर्णांकo पढ़ो buf */
			p = prng_data->buf;
			n = prng_sha512_generate(p, prng_chunk_size);
			अगर (n < 0) अणु
				ret = n;
				अवरोध;
			पूर्ण
			अगर (nbytes < prng_chunk_size) अणु
				n = nbytes;
				prng_data->rest = prng_chunk_size - n;
			पूर्ण अन्यथा अणु
				n = prng_chunk_size;
				prng_data->rest = 0;
			पूर्ण
		पूर्ण
		अगर (copy_to_user(ubuf, p, n)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		memzero_explicit(p, n);
		ubuf += n;
		nbytes -= n;
		ret += n;
	पूर्ण

	/* unlock prng_data काष्ठा */
	mutex_unlock(&prng_data->mutex);

	वापस ret;
पूर्ण


/*** sysfs stuff ***/

अटल स्थिर काष्ठा file_operations prng_sha512_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= &prng_खोलो,
	.release	= शून्य,
	.पढ़ो		= &prng_sha512_पढ़ो,
	.llseek		= noop_llseek,
पूर्ण;
अटल स्थिर काष्ठा file_operations prng_tdes_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= &prng_खोलो,
	.release	= शून्य,
	.पढ़ो		= &prng_tdes_पढ़ो,
	.llseek		= noop_llseek,
पूर्ण;

/* chunksize attribute (ro) */
अटल sमाप_प्रकार prng_chunksize_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", prng_chunk_size);
पूर्ण
अटल DEVICE_ATTR(chunksize, 0444, prng_chunksize_show, शून्य);

/* counter attribute (ro) */
अटल sमाप_प्रकार prng_counter_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	u64 counter;

	अगर (mutex_lock_पूर्णांकerruptible(&prng_data->mutex))
		वापस -ERESTARTSYS;
	अगर (prng_mode == PRNG_MODE_SHA512)
		counter = prng_data->prnows.stream_bytes;
	अन्यथा
		counter = prng_data->prngws.byte_counter;
	mutex_unlock(&prng_data->mutex);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", counter);
पूर्ण
अटल DEVICE_ATTR(byte_counter, 0444, prng_counter_show, शून्य);

/* errorflag attribute (ro) */
अटल sमाप_प्रकार prng_errorflag_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", prng_errorflag);
पूर्ण
अटल DEVICE_ATTR(errorflag, 0444, prng_errorflag_show, शून्य);

/* mode attribute (ro) */
अटल sमाप_प्रकार prng_mode_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	अगर (prng_mode == PRNG_MODE_TDES)
		वापस scnम_लिखो(buf, PAGE_SIZE, "TDES\n");
	अन्यथा
		वापस scnम_लिखो(buf, PAGE_SIZE, "SHA512\n");
पूर्ण
अटल DEVICE_ATTR(mode, 0444, prng_mode_show, शून्य);

/* reseed attribute (w) */
अटल sमाप_प्रकार prng_reseed_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (mutex_lock_पूर्णांकerruptible(&prng_data->mutex))
		वापस -ERESTARTSYS;
	prng_sha512_reseed();
	mutex_unlock(&prng_data->mutex);

	वापस count;
पूर्ण
अटल DEVICE_ATTR(reseed, 0200, शून्य, prng_reseed_store);

/* reseed limit attribute (rw) */
अटल sमाप_प्रकार prng_reseed_limit_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", prng_reseed_limit);
पूर्ण
अटल sमाप_प्रकार prng_reseed_limit_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित limit;

	अगर (माला_पूछो(buf, "%u\n", &limit) != 1)
		वापस -EINVAL;

	अगर (prng_mode == PRNG_MODE_SHA512) अणु
		अगर (limit < PRNG_RESEED_LIMIT_SHA512_LOWER)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (limit < PRNG_RESEED_LIMIT_TDES_LOWER)
			वापस -EINVAL;
	पूर्ण

	prng_reseed_limit = limit;

	वापस count;
पूर्ण
अटल DEVICE_ATTR(reseed_limit, 0644,
		   prng_reseed_limit_show, prng_reseed_limit_store);

/* strength attribute (ro) */
अटल sमाप_प्रकार prng_strength_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "256\n");
पूर्ण
अटल DEVICE_ATTR(strength, 0444, prng_strength_show, शून्य);

अटल काष्ठा attribute *prng_sha512_dev_attrs[] = अणु
	&dev_attr_errorflag.attr,
	&dev_attr_chunksize.attr,
	&dev_attr_byte_counter.attr,
	&dev_attr_mode.attr,
	&dev_attr_reseed.attr,
	&dev_attr_reseed_limit.attr,
	&dev_attr_strength.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(prng_sha512_dev);

अटल काष्ठा attribute *prng_tdes_dev_attrs[] = अणु
	&dev_attr_chunksize.attr,
	&dev_attr_byte_counter.attr,
	&dev_attr_mode.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(prng_tdes_dev);

अटल काष्ठा miscdevice prng_sha512_dev = अणु
	.name	= "prandom",
	.minor	= MISC_DYNAMIC_MINOR,
	.mode	= 0644,
	.fops	= &prng_sha512_fops,
	.groups = prng_sha512_dev_groups,
पूर्ण;

अटल काष्ठा miscdevice prng_tdes_dev = अणु
	.name	= "prandom",
	.minor	= MISC_DYNAMIC_MINOR,
	.mode	= 0644,
	.fops	= &prng_tdes_fops,
	.groups = prng_tdes_dev_groups,
पूर्ण;


/*** module init and निकास ***/

अटल पूर्णांक __init prng_init(व्योम)
अणु
	पूर्णांक ret;

	/* check अगर the CPU has a PRNG */
	अगर (!cpacf_query_func(CPACF_KMC, CPACF_KMC_PRNG))
		वापस -ENODEV;

	/* check अगर TRNG subfunction is available */
	अगर (cpacf_query_func(CPACF_PRNO, CPACF_PRNO_TRNG))
		trng_available = true;

	/* choose prng mode */
	अगर (prng_mode != PRNG_MODE_TDES) अणु
		/* check क्रम MSA5 support क्रम PRNO operations */
		अगर (!cpacf_query_func(CPACF_PRNO, CPACF_PRNO_SHA512_DRNG_GEN)) अणु
			अगर (prng_mode == PRNG_MODE_SHA512) अणु
				pr_err("The prng module cannot "
				       "start in SHA-512 mode\n");
				वापस -ENODEV;
			पूर्ण
			prng_mode = PRNG_MODE_TDES;
		पूर्ण अन्यथा
			prng_mode = PRNG_MODE_SHA512;
	पूर्ण

	अगर (prng_mode == PRNG_MODE_SHA512) अणु

		/* SHA512 mode */

		अगर (prng_chunk_size < PRNG_CHUNKSIZE_SHA512_MIN
		    || prng_chunk_size > PRNG_CHUNKSIZE_SHA512_MAX)
			वापस -EINVAL;
		prng_chunk_size = (prng_chunk_size + 0x3f) & ~0x3f;

		अगर (prng_reseed_limit == 0)
			prng_reseed_limit = PRNG_RESEED_LIMIT_SHA512;
		अन्यथा अगर (prng_reseed_limit < PRNG_RESEED_LIMIT_SHA512_LOWER)
			वापस -EINVAL;

		ret = prng_sha512_instantiate();
		अगर (ret)
			जाओ out;

		ret = misc_रेजिस्टर(&prng_sha512_dev);
		अगर (ret) अणु
			prng_sha512_deinstantiate();
			जाओ out;
		पूर्ण

	पूर्ण अन्यथा अणु

		/* TDES mode */

		अगर (prng_chunk_size < PRNG_CHUNKSIZE_TDES_MIN
		    || prng_chunk_size > PRNG_CHUNKSIZE_TDES_MAX)
			वापस -EINVAL;
		prng_chunk_size = (prng_chunk_size + 0x07) & ~0x07;

		अगर (prng_reseed_limit == 0)
			prng_reseed_limit = PRNG_RESEED_LIMIT_TDES;
		अन्यथा अगर (prng_reseed_limit < PRNG_RESEED_LIMIT_TDES_LOWER)
			वापस -EINVAL;

		ret = prng_tdes_instantiate();
		अगर (ret)
			जाओ out;

		ret = misc_रेजिस्टर(&prng_tdes_dev);
		अगर (ret) अणु
			prng_tdes_deinstantiate();
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण


अटल व्योम __निकास prng_निकास(व्योम)
अणु
	अगर (prng_mode == PRNG_MODE_SHA512) अणु
		misc_deरेजिस्टर(&prng_sha512_dev);
		prng_sha512_deinstantiate();
	पूर्ण अन्यथा अणु
		misc_deरेजिस्टर(&prng_tdes_dev);
		prng_tdes_deinstantiate();
	पूर्ण
पूर्ण

module_cpu_feature_match(MSA, prng_init);
module_निकास(prng_निकास);
