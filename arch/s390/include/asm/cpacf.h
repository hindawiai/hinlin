<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * CP Assist क्रम Cryptographic Functions (CPACF)
 *
 * Copyright IBM Corp. 2003, 2017
 * Author(s): Thomas Spatzier
 *	      Jan Glauber
 *	      Harald Freudenberger (freude@de.ibm.com)
 *	      Martin Schwidefsky <schwidefsky@de.ibm.com>
 */
#अगर_अघोषित _ASM_S390_CPACF_H
#घोषणा _ASM_S390_CPACF_H

#समावेश <यंत्र/facility.h>

/*
 * Inकाष्ठाion opcodes क्रम the CPACF inकाष्ठाions
 */
#घोषणा CPACF_KMAC		0xb91e		/* MSA	*/
#घोषणा CPACF_KM		0xb92e		/* MSA	*/
#घोषणा CPACF_KMC		0xb92f		/* MSA	*/
#घोषणा CPACF_KIMD		0xb93e		/* MSA	*/
#घोषणा CPACF_KLMD		0xb93f		/* MSA	*/
#घोषणा CPACF_PCKMO		0xb928		/* MSA3 */
#घोषणा CPACF_KMF		0xb92a		/* MSA4 */
#घोषणा CPACF_KMO		0xb92b		/* MSA4 */
#घोषणा CPACF_PCC		0xb92c		/* MSA4 */
#घोषणा CPACF_KMCTR		0xb92d		/* MSA4 */
#घोषणा CPACF_PRNO		0xb93c		/* MSA5 */
#घोषणा CPACF_KMA		0xb929		/* MSA8 */
#घोषणा CPACF_KDSA		0xb93a		/* MSA9 */

/*
 * En/decryption modअगरier bits
 */
#घोषणा CPACF_ENCRYPT		0x00
#घोषणा CPACF_DECRYPT		0x80

/*
 * Function codes क्रम the KM (CIPHER MESSAGE) inकाष्ठाion
 */
#घोषणा CPACF_KM_QUERY		0x00
#घोषणा CPACF_KM_DEA		0x01
#घोषणा CPACF_KM_TDEA_128	0x02
#घोषणा CPACF_KM_TDEA_192	0x03
#घोषणा CPACF_KM_AES_128	0x12
#घोषणा CPACF_KM_AES_192	0x13
#घोषणा CPACF_KM_AES_256	0x14
#घोषणा CPACF_KM_PAES_128	0x1a
#घोषणा CPACF_KM_PAES_192	0x1b
#घोषणा CPACF_KM_PAES_256	0x1c
#घोषणा CPACF_KM_XTS_128	0x32
#घोषणा CPACF_KM_XTS_256	0x34
#घोषणा CPACF_KM_PXTS_128	0x3a
#घोषणा CPACF_KM_PXTS_256	0x3c

/*
 * Function codes क्रम the KMC (CIPHER MESSAGE WITH CHAINING)
 * inकाष्ठाion
 */
#घोषणा CPACF_KMC_QUERY		0x00
#घोषणा CPACF_KMC_DEA		0x01
#घोषणा CPACF_KMC_TDEA_128	0x02
#घोषणा CPACF_KMC_TDEA_192	0x03
#घोषणा CPACF_KMC_AES_128	0x12
#घोषणा CPACF_KMC_AES_192	0x13
#घोषणा CPACF_KMC_AES_256	0x14
#घोषणा CPACF_KMC_PAES_128	0x1a
#घोषणा CPACF_KMC_PAES_192	0x1b
#घोषणा CPACF_KMC_PAES_256	0x1c
#घोषणा CPACF_KMC_PRNG		0x43

/*
 * Function codes क्रम the KMCTR (CIPHER MESSAGE WITH COUNTER)
 * inकाष्ठाion
 */
#घोषणा CPACF_KMCTR_QUERY	0x00
#घोषणा CPACF_KMCTR_DEA		0x01
#घोषणा CPACF_KMCTR_TDEA_128	0x02
#घोषणा CPACF_KMCTR_TDEA_192	0x03
#घोषणा CPACF_KMCTR_AES_128	0x12
#घोषणा CPACF_KMCTR_AES_192	0x13
#घोषणा CPACF_KMCTR_AES_256	0x14
#घोषणा CPACF_KMCTR_PAES_128	0x1a
#घोषणा CPACF_KMCTR_PAES_192	0x1b
#घोषणा CPACF_KMCTR_PAES_256	0x1c

/*
 * Function codes क्रम the KIMD (COMPUTE INTERMEDIATE MESSAGE DIGEST)
 * inकाष्ठाion
 */
#घोषणा CPACF_KIMD_QUERY	0x00
#घोषणा CPACF_KIMD_SHA_1	0x01
#घोषणा CPACF_KIMD_SHA_256	0x02
#घोषणा CPACF_KIMD_SHA_512	0x03
#घोषणा CPACF_KIMD_SHA3_224	0x20
#घोषणा CPACF_KIMD_SHA3_256	0x21
#घोषणा CPACF_KIMD_SHA3_384	0x22
#घोषणा CPACF_KIMD_SHA3_512	0x23
#घोषणा CPACF_KIMD_GHASH	0x41

/*
 * Function codes क्रम the KLMD (COMPUTE LAST MESSAGE DIGEST)
 * inकाष्ठाion
 */
#घोषणा CPACF_KLMD_QUERY	0x00
#घोषणा CPACF_KLMD_SHA_1	0x01
#घोषणा CPACF_KLMD_SHA_256	0x02
#घोषणा CPACF_KLMD_SHA_512	0x03
#घोषणा CPACF_KLMD_SHA3_224	0x20
#घोषणा CPACF_KLMD_SHA3_256	0x21
#घोषणा CPACF_KLMD_SHA3_384	0x22
#घोषणा CPACF_KLMD_SHA3_512	0x23

/*
 * function codes क्रम the KMAC (COMPUTE MESSAGE AUTHENTICATION CODE)
 * inकाष्ठाion
 */
#घोषणा CPACF_KMAC_QUERY	0x00
#घोषणा CPACF_KMAC_DEA		0x01
#घोषणा CPACF_KMAC_TDEA_128	0x02
#घोषणा CPACF_KMAC_TDEA_192	0x03

/*
 * Function codes क्रम the PCKMO (PERFORM CRYPTOGRAPHIC KEY MANAGEMENT)
 * inकाष्ठाion
 */
#घोषणा CPACF_PCKMO_QUERY		0x00
#घोषणा CPACF_PCKMO_ENC_DES_KEY		0x01
#घोषणा CPACF_PCKMO_ENC_TDES_128_KEY	0x02
#घोषणा CPACF_PCKMO_ENC_TDES_192_KEY	0x03
#घोषणा CPACF_PCKMO_ENC_AES_128_KEY	0x12
#घोषणा CPACF_PCKMO_ENC_AES_192_KEY	0x13
#घोषणा CPACF_PCKMO_ENC_AES_256_KEY	0x14

/*
 * Function codes क्रम the PRNO (PERFORM RANDOM NUMBER OPERATION)
 * inकाष्ठाion
 */
#घोषणा CPACF_PRNO_QUERY		0x00
#घोषणा CPACF_PRNO_SHA512_DRNG_GEN	0x03
#घोषणा CPACF_PRNO_SHA512_DRNG_SEED	0x83
#घोषणा CPACF_PRNO_TRNG_Q_R2C_RATIO	0x70
#घोषणा CPACF_PRNO_TRNG			0x72

/*
 * Function codes क्रम the KMA (CIPHER MESSAGE WITH AUTHENTICATION)
 * inकाष्ठाion
 */
#घोषणा CPACF_KMA_QUERY		0x00
#घोषणा CPACF_KMA_GCM_AES_128	0x12
#घोषणा CPACF_KMA_GCM_AES_192	0x13
#घोषणा CPACF_KMA_GCM_AES_256	0x14

/*
 * Flags क्रम the KMA (CIPHER MESSAGE WITH AUTHENTICATION) inकाष्ठाion
 */
#घोषणा CPACF_KMA_LPC	0x100	/* Last-Plaपूर्णांकext/Ciphertext */
#घोषणा CPACF_KMA_LAAD	0x200	/* Last-AAD */
#घोषणा CPACF_KMA_HS	0x400	/* Hash-subkey Supplied */

प्रकार काष्ठा अणु अचिन्हित अक्षर bytes[16]; पूर्ण cpacf_mask_t;

/**
 * cpacf_query() - check अगर a specअगरic CPACF function is available
 * @opcode: the opcode of the crypto inकाष्ठाion
 * @func: the function code to test क्रम
 *
 * Executes the query function क्रम the given crypto inकाष्ठाion @opcode
 * and checks अगर @func is available
 *
 * Returns 1 अगर @func is available क्रम @opcode, 0 otherwise
 */
अटल __always_अंतरभूत व्योम __cpacf_query(अचिन्हित पूर्णांक opcode, cpacf_mask_t *mask)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = 0;	/* query function */
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) mask;

	यंत्र अस्थिर(
		"	spm 0\n" /* pckmo करोesn't change the cc */
		/* Parameter regs are ignored, but must be nonzero and unique */
		"0:	.insn	rrf,%[opc] << 16,2,4,6,0\n"
		"	brc	1,0b\n"	/* handle partial completion */
		: "=m" (*mask)
		: [fc] "d" (r0), [pba] "a" (r1), [opc] "i" (opcode)
		: "cc");
पूर्ण

अटल __always_अंतरभूत पूर्णांक __cpacf_check_opcode(अचिन्हित पूर्णांक opcode)
अणु
	चयन (opcode) अणु
	हाल CPACF_KMAC:
	हाल CPACF_KM:
	हाल CPACF_KMC:
	हाल CPACF_KIMD:
	हाल CPACF_KLMD:
		वापस test_facility(17);	/* check क्रम MSA */
	हाल CPACF_PCKMO:
		वापस test_facility(76);	/* check क्रम MSA3 */
	हाल CPACF_KMF:
	हाल CPACF_KMO:
	हाल CPACF_PCC:
	हाल CPACF_KMCTR:
		वापस test_facility(77);	/* check क्रम MSA4 */
	हाल CPACF_PRNO:
		वापस test_facility(57);	/* check क्रम MSA5 */
	हाल CPACF_KMA:
		वापस test_facility(146);	/* check क्रम MSA8 */
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल __always_अंतरभूत पूर्णांक cpacf_query(अचिन्हित पूर्णांक opcode, cpacf_mask_t *mask)
अणु
	अगर (__cpacf_check_opcode(opcode)) अणु
		__cpacf_query(opcode, mask);
		वापस 1;
	पूर्ण
	स_रखो(mask, 0, माप(*mask));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpacf_test_func(cpacf_mask_t *mask, अचिन्हित पूर्णांक func)
अणु
	वापस (mask->bytes[func >> 3] & (0x80 >> (func & 7))) != 0;
पूर्ण

अटल __always_अंतरभूत पूर्णांक cpacf_query_func(अचिन्हित पूर्णांक opcode, अचिन्हित पूर्णांक func)
अणु
	cpacf_mask_t mask;

	अगर (cpacf_query(opcode, &mask))
		वापस cpacf_test_func(&mask, func);
	वापस 0;
पूर्ण

/**
 * cpacf_km() - executes the KM (CIPHER MESSAGE) inकाष्ठाion
 * @func: the function code passed to KM; see CPACF_KM_xxx defines
 * @param: address of parameter block; see POP क्रम details on each func
 * @dest: address of destination memory area
 * @src: address of source memory area
 * @src_len: length of src opeअक्रम in bytes
 *
 * Returns 0 क्रम the query func, number of processed bytes क्रम
 * encryption/decryption funcs
 */
अटल अंतरभूत पूर्णांक cpacf_km(अचिन्हित दीर्घ func, व्योम *param,
			   u8 *dest, स्थिर u8 *src, दीर्घ src_len)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) func;
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) param;
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2") = (अचिन्हित दीर्घ) src;
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("3") = (अचिन्हित दीर्घ) src_len;
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("4") = (अचिन्हित दीर्घ) dest;

	यंत्र अस्थिर(
		"0:	.insn	rre,%[opc] << 16,%[dst],%[src]\n"
		"	brc	1,0b\n" /* handle partial completion */
		: [src] "+a" (r2), [len] "+d" (r3), [dst] "+a" (r4)
		: [fc] "d" (r0), [pba] "a" (r1), [opc] "i" (CPACF_KM)
		: "cc", "memory");

	वापस src_len - r3;
पूर्ण

/**
 * cpacf_kmc() - executes the KMC (CIPHER MESSAGE WITH CHAINING) inकाष्ठाion
 * @func: the function code passed to KM; see CPACF_KMC_xxx defines
 * @param: address of parameter block; see POP क्रम details on each func
 * @dest: address of destination memory area
 * @src: address of source memory area
 * @src_len: length of src opeअक्रम in bytes
 *
 * Returns 0 क्रम the query func, number of processed bytes क्रम
 * encryption/decryption funcs
 */
अटल अंतरभूत पूर्णांक cpacf_kmc(अचिन्हित दीर्घ func, व्योम *param,
			    u8 *dest, स्थिर u8 *src, दीर्घ src_len)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) func;
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) param;
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2") = (अचिन्हित दीर्घ) src;
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("3") = (अचिन्हित दीर्घ) src_len;
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("4") = (अचिन्हित दीर्घ) dest;

	यंत्र अस्थिर(
		"0:	.insn	rre,%[opc] << 16,%[dst],%[src]\n"
		"	brc	1,0b\n" /* handle partial completion */
		: [src] "+a" (r2), [len] "+d" (r3), [dst] "+a" (r4)
		: [fc] "d" (r0), [pba] "a" (r1), [opc] "i" (CPACF_KMC)
		: "cc", "memory");

	वापस src_len - r3;
पूर्ण

/**
 * cpacf_kimd() - executes the KIMD (COMPUTE INTERMEDIATE MESSAGE DIGEST)
 *		  inकाष्ठाion
 * @func: the function code passed to KM; see CPACF_KIMD_xxx defines
 * @param: address of parameter block; see POP क्रम details on each func
 * @src: address of source memory area
 * @src_len: length of src opeअक्रम in bytes
 */
अटल अंतरभूत व्योम cpacf_kimd(अचिन्हित दीर्घ func, व्योम *param,
			      स्थिर u8 *src, दीर्घ src_len)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) func;
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) param;
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2") = (अचिन्हित दीर्घ) src;
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("3") = (अचिन्हित दीर्घ) src_len;

	यंत्र अस्थिर(
		"0:	.insn	rre,%[opc] << 16,0,%[src]\n"
		"	brc	1,0b\n" /* handle partial completion */
		: [src] "+a" (r2), [len] "+d" (r3)
		: [fc] "d" (r0), [pba] "a" (r1), [opc] "i" (CPACF_KIMD)
		: "cc", "memory");
पूर्ण

/**
 * cpacf_klmd() - executes the KLMD (COMPUTE LAST MESSAGE DIGEST) inकाष्ठाion
 * @func: the function code passed to KM; see CPACF_KLMD_xxx defines
 * @param: address of parameter block; see POP क्रम details on each func
 * @src: address of source memory area
 * @src_len: length of src opeअक्रम in bytes
 */
अटल अंतरभूत व्योम cpacf_klmd(अचिन्हित दीर्घ func, व्योम *param,
			      स्थिर u8 *src, दीर्घ src_len)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) func;
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) param;
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2") = (अचिन्हित दीर्घ) src;
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("3") = (अचिन्हित दीर्घ) src_len;

	यंत्र अस्थिर(
		"0:	.insn	rre,%[opc] << 16,0,%[src]\n"
		"	brc	1,0b\n" /* handle partial completion */
		: [src] "+a" (r2), [len] "+d" (r3)
		: [fc] "d" (r0), [pba] "a" (r1), [opc] "i" (CPACF_KLMD)
		: "cc", "memory");
पूर्ण

/**
 * cpacf_kmac() - executes the KMAC (COMPUTE MESSAGE AUTHENTICATION CODE)
 *		  inकाष्ठाion
 * @func: the function code passed to KM; see CPACF_KMAC_xxx defines
 * @param: address of parameter block; see POP क्रम details on each func
 * @src: address of source memory area
 * @src_len: length of src opeअक्रम in bytes
 *
 * Returns 0 क्रम the query func, number of processed bytes क्रम digest funcs
 */
अटल अंतरभूत पूर्णांक cpacf_kmac(अचिन्हित दीर्घ func, व्योम *param,
			     स्थिर u8 *src, दीर्घ src_len)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) func;
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) param;
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2") = (अचिन्हित दीर्घ) src;
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("3") = (अचिन्हित दीर्घ) src_len;

	यंत्र अस्थिर(
		"0:	.insn	rre,%[opc] << 16,0,%[src]\n"
		"	brc	1,0b\n" /* handle partial completion */
		: [src] "+a" (r2), [len] "+d" (r3)
		: [fc] "d" (r0), [pba] "a" (r1), [opc] "i" (CPACF_KMAC)
		: "cc", "memory");

	वापस src_len - r3;
पूर्ण

/**
 * cpacf_kmctr() - executes the KMCTR (CIPHER MESSAGE WITH COUNTER) inकाष्ठाion
 * @func: the function code passed to KMCTR; see CPACF_KMCTR_xxx defines
 * @param: address of parameter block; see POP क्रम details on each func
 * @dest: address of destination memory area
 * @src: address of source memory area
 * @src_len: length of src opeअक्रम in bytes
 * @counter: address of counter value
 *
 * Returns 0 क्रम the query func, number of processed bytes क्रम
 * encryption/decryption funcs
 */
अटल अंतरभूत पूर्णांक cpacf_kmctr(अचिन्हित दीर्घ func, व्योम *param, u8 *dest,
			      स्थिर u8 *src, दीर्घ src_len, u8 *counter)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) func;
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) param;
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2") = (अचिन्हित दीर्घ) src;
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("3") = (अचिन्हित दीर्घ) src_len;
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("4") = (अचिन्हित दीर्घ) dest;
	रेजिस्टर अचिन्हित दीर्घ r6 यंत्र("6") = (अचिन्हित दीर्घ) counter;

	यंत्र अस्थिर(
		"0:	.insn	rrf,%[opc] << 16,%[dst],%[src],%[ctr],0\n"
		"	brc	1,0b\n" /* handle partial completion */
		: [src] "+a" (r2), [len] "+d" (r3),
		  [dst] "+a" (r4), [ctr] "+a" (r6)
		: [fc] "d" (r0), [pba] "a" (r1), [opc] "i" (CPACF_KMCTR)
		: "cc", "memory");

	वापस src_len - r3;
पूर्ण

/**
 * cpacf_prno() - executes the PRNO (PERFORM RANDOM NUMBER OPERATION)
 *		  inकाष्ठाion
 * @func: the function code passed to PRNO; see CPACF_PRNO_xxx defines
 * @param: address of parameter block; see POP क्रम details on each func
 * @dest: address of destination memory area
 * @dest_len: size of destination memory area in bytes
 * @seed: address of seed data
 * @seed_len: size of seed data in bytes
 */
अटल अंतरभूत व्योम cpacf_prno(अचिन्हित दीर्घ func, व्योम *param,
			      u8 *dest, अचिन्हित दीर्घ dest_len,
			      स्थिर u8 *seed, अचिन्हित दीर्घ seed_len)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) func;
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) param;
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2") = (अचिन्हित दीर्घ) dest;
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("3") = (अचिन्हित दीर्घ) dest_len;
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("4") = (अचिन्हित दीर्घ) seed;
	रेजिस्टर अचिन्हित दीर्घ r5 यंत्र("5") = (अचिन्हित दीर्घ) seed_len;

	यंत्र अस्थिर (
		"0:	.insn	rre,%[opc] << 16,%[dst],%[seed]\n"
		"	brc	1,0b\n"	  /* handle partial completion */
		: [dst] "+a" (r2), [dlen] "+d" (r3)
		: [fc] "d" (r0), [pba] "a" (r1),
		  [seed] "a" (r4), [slen] "d" (r5), [opc] "i" (CPACF_PRNO)
		: "cc", "memory");
पूर्ण

/**
 * cpacf_trng() - executes the TRNG subfunction of the PRNO inकाष्ठाion
 * @ucbuf: buffer क्रम unconditioned data
 * @ucbuf_len: amount of unconditioned data to fetch in bytes
 * @cbuf: buffer क्रम conditioned data
 * @cbuf_len: amount of conditioned data to fetch in bytes
 */
अटल अंतरभूत व्योम cpacf_trng(u8 *ucbuf, अचिन्हित दीर्घ ucbuf_len,
			      u8 *cbuf, अचिन्हित दीर्घ cbuf_len)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) CPACF_PRNO_TRNG;
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2") = (अचिन्हित दीर्घ) ucbuf;
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("3") = (अचिन्हित दीर्घ) ucbuf_len;
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("4") = (अचिन्हित दीर्घ) cbuf;
	रेजिस्टर अचिन्हित दीर्घ r5 यंत्र("5") = (अचिन्हित दीर्घ) cbuf_len;

	यंत्र अस्थिर (
		"0:	.insn	rre,%[opc] << 16,%[ucbuf],%[cbuf]\n"
		"	brc	1,0b\n"	  /* handle partial completion */
		: [ucbuf] "+a" (r2), [ucbuflen] "+d" (r3),
		  [cbuf] "+a" (r4), [cbuflen] "+d" (r5)
		: [fc] "d" (r0), [opc] "i" (CPACF_PRNO)
		: "cc", "memory");
पूर्ण

/**
 * cpacf_pcc() - executes the PCC (PERFORM CRYPTOGRAPHIC COMPUTATION)
 *		 inकाष्ठाion
 * @func: the function code passed to PCC; see CPACF_KM_xxx defines
 * @param: address of parameter block; see POP क्रम details on each func
 */
अटल अंतरभूत व्योम cpacf_pcc(अचिन्हित दीर्घ func, व्योम *param)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) func;
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) param;

	यंत्र अस्थिर(
		"0:	.insn	rre,%[opc] << 16,0,0\n" /* PCC opcode */
		"	brc	1,0b\n" /* handle partial completion */
		:
		: [fc] "d" (r0), [pba] "a" (r1), [opc] "i" (CPACF_PCC)
		: "cc", "memory");
पूर्ण

/**
 * cpacf_pckmo() - executes the PCKMO (PERFORM CRYPTOGRAPHIC KEY
 *		  MANAGEMENT) inकाष्ठाion
 * @func: the function code passed to PCKMO; see CPACF_PCKMO_xxx defines
 * @param: address of parameter block; see POP क्रम details on each func
 *
 * Returns 0.
 */
अटल अंतरभूत व्योम cpacf_pckmo(दीर्घ func, व्योम *param)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) func;
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) param;

	यंत्र अस्थिर(
		"       .insn   rre,%[opc] << 16,0,0\n" /* PCKMO opcode */
		:
		: [fc] "d" (r0), [pba] "a" (r1), [opc] "i" (CPACF_PCKMO)
		: "cc", "memory");
पूर्ण

/**
 * cpacf_kma() - executes the KMA (CIPHER MESSAGE WITH AUTHENTICATION)
 *		 inकाष्ठाion
 * @func: the function code passed to KMA; see CPACF_KMA_xxx defines
 * @param: address of parameter block; see POP क्रम details on each func
 * @dest: address of destination memory area
 * @src: address of source memory area
 * @src_len: length of src opeअक्रम in bytes
 * @aad: address of additional authenticated data memory area
 * @aad_len: length of aad opeअक्रम in bytes
 */
अटल अंतरभूत व्योम cpacf_kma(अचिन्हित दीर्घ func, व्योम *param, u8 *dest,
			     स्थिर u8 *src, अचिन्हित दीर्घ src_len,
			     स्थिर u8 *aad, अचिन्हित दीर्घ aad_len)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = (अचिन्हित दीर्घ) func;
	रेजिस्टर अचिन्हित दीर्घ r1 यंत्र("1") = (अचिन्हित दीर्घ) param;
	रेजिस्टर अचिन्हित दीर्घ r2 यंत्र("2") = (अचिन्हित दीर्घ) src;
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("3") = (अचिन्हित दीर्घ) src_len;
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("4") = (अचिन्हित दीर्घ) aad;
	रेजिस्टर अचिन्हित दीर्घ r5 यंत्र("5") = (अचिन्हित दीर्घ) aad_len;
	रेजिस्टर अचिन्हित दीर्घ r6 यंत्र("6") = (अचिन्हित दीर्घ) dest;

	यंत्र अस्थिर(
		"0:	.insn	rrf,%[opc] << 16,%[dst],%[src],%[aad],0\n"
		"	brc	1,0b\n"	/* handle partial completion */
		: [dst] "+a" (r6), [src] "+a" (r2), [slen] "+d" (r3),
		  [aad] "+a" (r4), [alen] "+d" (r5)
		: [fc] "d" (r0), [pba] "a" (r1), [opc] "i" (CPACF_KMA)
		: "cc", "memory");
पूर्ण

#पूर्ण_अगर	/* _ASM_S390_CPACF_H */
