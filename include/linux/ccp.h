<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AMD Cryptographic Coprocessor (CCP) driver
 *
 * Copyright (C) 2013,2017 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#अगर_अघोषित __CCP_H__
#घोषणा __CCP_H__

#समावेश <linux/scatterlist.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/list.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>

काष्ठा ccp_device;
काष्ठा ccp_cmd;

#अगर defined(CONFIG_CRYPTO_DEV_SP_CCP)

/**
 * ccp_present - check अगर a CCP device is present
 *
 * Returns zero अगर a CCP device is present, -ENODEV otherwise.
 */
पूर्णांक ccp_present(व्योम);

#घोषणा	CCP_VSIZE 16
#घोषणा	CCP_VMASK		((अचिन्हित पूर्णांक)((1 << CCP_VSIZE) - 1))
#घोषणा	CCP_VERSION(v, r)	((अचिन्हित पूर्णांक)((v << CCP_VSIZE) \
					       | (r & CCP_VMASK)))

/**
 * ccp_version - get the version of the CCP
 *
 * Returns a positive version number, or zero अगर no CCP
 */
अचिन्हित पूर्णांक ccp_version(व्योम);

/**
 * ccp_enqueue_cmd - queue an operation क्रम processing by the CCP
 *
 * @cmd: ccp_cmd काष्ठा to be processed
 *
 * Refer to the ccp_cmd काष्ठा below क्रम required fields.
 *
 * Queue a cmd to be processed by the CCP. If queueing the cmd
 * would exceed the defined length of the cmd queue the cmd will
 * only be queued अगर the CCP_CMD_MAY_BACKLOG flag is set and will
 * result in a वापस code of -EBUSY.
 *
 * The callback routine specअगरied in the ccp_cmd काष्ठा will be
 * called to notअगरy the caller of completion (अगर the cmd was not
 * backlogged) or advancement out of the backlog. If the cmd has
 * advanced out of the backlog the "err" value of the callback
 * will be -EINPROGRESS. Any other "err" value during callback is
 * the result of the operation.
 *
 * The cmd has been successfully queued अगर:
 *   the वापस code is -EINPROGRESS or
 *   the वापस code is -EBUSY and CCP_CMD_MAY_BACKLOG flag is set
 */
पूर्णांक ccp_enqueue_cmd(काष्ठा ccp_cmd *cmd);

#अन्यथा /* CONFIG_CRYPTO_DEV_CCP_SP_DEV is not enabled */

अटल अंतरभूत पूर्णांक ccp_present(व्योम)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ccp_version(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ccp_enqueue_cmd(काष्ठा ccp_cmd *cmd)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_SP_CCP */


/***** AES engine *****/
/**
 * ccp_aes_type - AES key size
 *
 * @CCP_AES_TYPE_128: 128-bit key
 * @CCP_AES_TYPE_192: 192-bit key
 * @CCP_AES_TYPE_256: 256-bit key
 */
क्रमागत ccp_aes_type अणु
	CCP_AES_TYPE_128 = 0,
	CCP_AES_TYPE_192,
	CCP_AES_TYPE_256,
	CCP_AES_TYPE__LAST,
पूर्ण;

/**
 * ccp_aes_mode - AES operation mode
 *
 * @CCP_AES_MODE_ECB: ECB mode
 * @CCP_AES_MODE_CBC: CBC mode
 * @CCP_AES_MODE_OFB: OFB mode
 * @CCP_AES_MODE_CFB: CFB mode
 * @CCP_AES_MODE_CTR: CTR mode
 * @CCP_AES_MODE_CMAC: CMAC mode
 */
क्रमागत ccp_aes_mode अणु
	CCP_AES_MODE_ECB = 0,
	CCP_AES_MODE_CBC,
	CCP_AES_MODE_OFB,
	CCP_AES_MODE_CFB,
	CCP_AES_MODE_CTR,
	CCP_AES_MODE_CMAC,
	CCP_AES_MODE_GHASH,
	CCP_AES_MODE_GCTR,
	CCP_AES_MODE_GCM,
	CCP_AES_MODE_GMAC,
	CCP_AES_MODE__LAST,
पूर्ण;

/**
 * ccp_aes_mode - AES operation mode
 *
 * @CCP_AES_ACTION_DECRYPT: AES decrypt operation
 * @CCP_AES_ACTION_ENCRYPT: AES encrypt operation
 */
क्रमागत ccp_aes_action अणु
	CCP_AES_ACTION_DECRYPT = 0,
	CCP_AES_ACTION_ENCRYPT,
	CCP_AES_ACTION__LAST,
पूर्ण;
/* Overloaded field */
#घोषणा	CCP_AES_GHASHAAD	CCP_AES_ACTION_DECRYPT
#घोषणा	CCP_AES_GHASHFINAL	CCP_AES_ACTION_ENCRYPT

/**
 * काष्ठा ccp_aes_engine - CCP AES operation
 * @type: AES operation key size
 * @mode: AES operation mode
 * @action: AES operation (decrypt/encrypt)
 * @key: key to be used क्रम this AES operation
 * @key_len: length in bytes of key
 * @iv: IV to be used क्रम this AES operation
 * @iv_len: length in bytes of iv
 * @src: data to be used क्रम this operation
 * @dst: data produced by this operation
 * @src_len: length in bytes of data used क्रम this operation
 * @cmac_final: indicates final operation when running in CMAC mode
 * @cmac_key: K1/K2 key used in final CMAC operation
 * @cmac_key_len: length in bytes of cmac_key
 *
 * Variables required to be set when calling ccp_enqueue_cmd():
 *   - type, mode, action, key, key_len, src, dst, src_len
 *   - iv, iv_len क्रम any mode other than ECB
 *   - cmac_final क्रम CMAC mode
 *   - cmac_key, cmac_key_len क्रम CMAC mode अगर cmac_final is non-zero
 *
 * The iv variable is used as both input and output. On completion of the
 * AES operation the new IV overग_लिखोs the old IV.
 */
काष्ठा ccp_aes_engine अणु
	क्रमागत ccp_aes_type type;
	क्रमागत ccp_aes_mode mode;
	क्रमागत ccp_aes_action action;

	u32 authsize;

	काष्ठा scatterlist *key;
	u32 key_len;		/* In bytes */

	काष्ठा scatterlist *iv;
	u32 iv_len;		/* In bytes */

	काष्ठा scatterlist *src, *dst;
	u64 src_len;		/* In bytes */

	u32 cmac_final;		/* Indicates final cmac cmd */
	काष्ठा scatterlist *cmac_key;	/* K1/K2 cmac key required क्रम
					 * final cmac cmd */
	u32 cmac_key_len;	/* In bytes */

	u32 aad_len;		/* In bytes */
पूर्ण;

/***** XTS-AES engine *****/
/**
 * ccp_xts_aes_unit_size - XTS unit size
 *
 * @CCP_XTS_AES_UNIT_SIZE_16: Unit size of 16 bytes
 * @CCP_XTS_AES_UNIT_SIZE_512: Unit size of 512 bytes
 * @CCP_XTS_AES_UNIT_SIZE_1024: Unit size of 1024 bytes
 * @CCP_XTS_AES_UNIT_SIZE_2048: Unit size of 2048 bytes
 * @CCP_XTS_AES_UNIT_SIZE_4096: Unit size of 4096 bytes
 */
क्रमागत ccp_xts_aes_unit_size अणु
	CCP_XTS_AES_UNIT_SIZE_16 = 0,
	CCP_XTS_AES_UNIT_SIZE_512,
	CCP_XTS_AES_UNIT_SIZE_1024,
	CCP_XTS_AES_UNIT_SIZE_2048,
	CCP_XTS_AES_UNIT_SIZE_4096,
	CCP_XTS_AES_UNIT_SIZE__LAST,
पूर्ण;

/**
 * काष्ठा ccp_xts_aes_engine - CCP XTS AES operation
 * @action: AES operation (decrypt/encrypt)
 * @unit_size: unit size of the XTS operation
 * @key: key to be used क्रम this XTS AES operation
 * @key_len: length in bytes of key
 * @iv: IV to be used क्रम this XTS AES operation
 * @iv_len: length in bytes of iv
 * @src: data to be used क्रम this operation
 * @dst: data produced by this operation
 * @src_len: length in bytes of data used क्रम this operation
 * @final: indicates final XTS operation
 *
 * Variables required to be set when calling ccp_enqueue_cmd():
 *   - action, unit_size, key, key_len, iv, iv_len, src, dst, src_len, final
 *
 * The iv variable is used as both input and output. On completion of the
 * AES operation the new IV overग_लिखोs the old IV.
 */
काष्ठा ccp_xts_aes_engine अणु
	क्रमागत ccp_aes_type type;
	क्रमागत ccp_aes_action action;
	क्रमागत ccp_xts_aes_unit_size unit_size;

	काष्ठा scatterlist *key;
	u32 key_len;		/* In bytes */

	काष्ठा scatterlist *iv;
	u32 iv_len;		/* In bytes */

	काष्ठा scatterlist *src, *dst;
	u64 src_len;		/* In bytes */

	u32 final;
पूर्ण;

/***** SHA engine *****/
/**
 * ccp_sha_type - type of SHA operation
 *
 * @CCP_SHA_TYPE_1: SHA-1 operation
 * @CCP_SHA_TYPE_224: SHA-224 operation
 * @CCP_SHA_TYPE_256: SHA-256 operation
 */
क्रमागत ccp_sha_type अणु
	CCP_SHA_TYPE_1 = 1,
	CCP_SHA_TYPE_224,
	CCP_SHA_TYPE_256,
	CCP_SHA_TYPE_384,
	CCP_SHA_TYPE_512,
	CCP_SHA_TYPE__LAST,
पूर्ण;

/**
 * काष्ठा ccp_sha_engine - CCP SHA operation
 * @type: Type of SHA operation
 * @ctx: current hash value
 * @ctx_len: length in bytes of hash value
 * @src: data to be used क्रम this operation
 * @src_len: length in bytes of data used क्रम this operation
 * @opad: data to be used क्रम final HMAC operation
 * @opad_len: length in bytes of data used क्रम final HMAC operation
 * @first: indicates first SHA operation
 * @final: indicates final SHA operation
 * @msg_bits: total length of the message in bits used in final SHA operation
 *
 * Variables required to be set when calling ccp_enqueue_cmd():
 *   - type, ctx, ctx_len, src, src_len, final
 *   - msg_bits अगर final is non-zero
 *
 * The ctx variable is used as both input and output. On completion of the
 * SHA operation the new hash value overग_लिखोs the old hash value.
 */
काष्ठा ccp_sha_engine अणु
	क्रमागत ccp_sha_type type;

	काष्ठा scatterlist *ctx;
	u32 ctx_len;		/* In bytes */

	काष्ठा scatterlist *src;
	u64 src_len;		/* In bytes */

	काष्ठा scatterlist *opad;
	u32 opad_len;		/* In bytes */

	u32 first;		/* Indicates first sha cmd */
	u32 final;		/* Indicates final sha cmd */
	u64 msg_bits;		/* Message length in bits required क्रम
				 * final sha cmd */
पूर्ण;

/***** 3DES engine *****/
क्रमागत ccp_des3_mode अणु
	CCP_DES3_MODE_ECB = 0,
	CCP_DES3_MODE_CBC,
	CCP_DES3_MODE_CFB,
	CCP_DES3_MODE__LAST,
पूर्ण;

क्रमागत ccp_des3_type अणु
	CCP_DES3_TYPE_168 = 1,
	CCP_DES3_TYPE__LAST,
	पूर्ण;

क्रमागत ccp_des3_action अणु
	CCP_DES3_ACTION_DECRYPT = 0,
	CCP_DES3_ACTION_ENCRYPT,
	CCP_DES3_ACTION__LAST,
पूर्ण;

/**
 * काष्ठा ccp_des3_engine - CCP SHA operation
 * @type: Type of 3DES operation
 * @mode: cipher mode
 * @action: 3DES operation (decrypt/encrypt)
 * @key: key to be used क्रम this 3DES operation
 * @key_len: length of key (in bytes)
 * @iv: IV to be used क्रम this AES operation
 * @iv_len: length in bytes of iv
 * @src: input data to be used क्रम this operation
 * @src_len: length of input data used क्रम this operation (in bytes)
 * @dst: output data produced by this operation
 *
 * Variables required to be set when calling ccp_enqueue_cmd():
 *   - type, mode, action, key, key_len, src, dst, src_len
 *   - iv, iv_len क्रम any mode other than ECB
 *
 * The iv variable is used as both input and output. On completion of the
 * 3DES operation the new IV overग_लिखोs the old IV.
 */
काष्ठा ccp_des3_engine अणु
	क्रमागत ccp_des3_type type;
	क्रमागत ccp_des3_mode mode;
	क्रमागत ccp_des3_action action;

	काष्ठा scatterlist *key;
	u32 key_len;	    /* In bytes */

	काष्ठा scatterlist *iv;
	u32 iv_len;	     /* In bytes */

	काष्ठा scatterlist *src, *dst;
	u64 src_len;	    /* In bytes */
पूर्ण;

/***** RSA engine *****/
/**
 * काष्ठा ccp_rsa_engine - CCP RSA operation
 * @key_size: length in bits of RSA key
 * @exp: RSA exponent
 * @exp_len: length in bytes of exponent
 * @mod: RSA modulus
 * @mod_len: length in bytes of modulus
 * @src: data to be used क्रम this operation
 * @dst: data produced by this operation
 * @src_len: length in bytes of data used क्रम this operation
 *
 * Variables required to be set when calling ccp_enqueue_cmd():
 *   - key_size, exp, exp_len, mod, mod_len, src, dst, src_len
 */
काष्ठा ccp_rsa_engine अणु
	u32 key_size;		/* In bits */

	काष्ठा scatterlist *exp;
	u32 exp_len;		/* In bytes */

	काष्ठा scatterlist *mod;
	u32 mod_len;		/* In bytes */

	काष्ठा scatterlist *src, *dst;
	u32 src_len;		/* In bytes */
पूर्ण;

/***** Passthru engine *****/
/**
 * ccp_passthru_bitwise - type of bitwise passthru operation
 *
 * @CCP_PASSTHRU_BITWISE_NOOP: no bitwise operation perक्रमmed
 * @CCP_PASSTHRU_BITWISE_AND: perक्रमm bitwise AND of src with mask
 * @CCP_PASSTHRU_BITWISE_OR: perक्रमm bitwise OR of src with mask
 * @CCP_PASSTHRU_BITWISE_XOR: perक्रमm bitwise XOR of src with mask
 * @CCP_PASSTHRU_BITWISE_MASK: overग_लिखो with mask
 */
क्रमागत ccp_passthru_bitwise अणु
	CCP_PASSTHRU_BITWISE_NOOP = 0,
	CCP_PASSTHRU_BITWISE_AND,
	CCP_PASSTHRU_BITWISE_OR,
	CCP_PASSTHRU_BITWISE_XOR,
	CCP_PASSTHRU_BITWISE_MASK,
	CCP_PASSTHRU_BITWISE__LAST,
पूर्ण;

/**
 * ccp_passthru_byteswap - type of byteswap passthru operation
 *
 * @CCP_PASSTHRU_BYTESWAP_NOOP: no byte swapping perक्रमmed
 * @CCP_PASSTHRU_BYTESWAP_32BIT: swap bytes within 32-bit words
 * @CCP_PASSTHRU_BYTESWAP_256BIT: swap bytes within 256-bit words
 */
क्रमागत ccp_passthru_byteswap अणु
	CCP_PASSTHRU_BYTESWAP_NOOP = 0,
	CCP_PASSTHRU_BYTESWAP_32BIT,
	CCP_PASSTHRU_BYTESWAP_256BIT,
	CCP_PASSTHRU_BYTESWAP__LAST,
पूर्ण;

/**
 * काष्ठा ccp_passthru_engine - CCP pass-through operation
 * @bit_mod: bitwise operation to perक्रमm
 * @byte_swap: byteswap operation to perक्रमm
 * @mask: mask to be applied to data
 * @mask_len: length in bytes of mask
 * @src: data to be used क्रम this operation
 * @dst: data produced by this operation
 * @src_len: length in bytes of data used क्रम this operation
 * @final: indicate final pass-through operation
 *
 * Variables required to be set when calling ccp_enqueue_cmd():
 *   - bit_mod, byte_swap, src, dst, src_len
 *   - mask, mask_len अगर bit_mod is not CCP_PASSTHRU_BITWISE_NOOP
 */
काष्ठा ccp_passthru_engine अणु
	क्रमागत ccp_passthru_bitwise bit_mod;
	क्रमागत ccp_passthru_byteswap byte_swap;

	काष्ठा scatterlist *mask;
	u32 mask_len;		/* In bytes */

	काष्ठा scatterlist *src, *dst;
	u64 src_len;		/* In bytes */

	u32 final;
पूर्ण;

/**
 * काष्ठा ccp_passthru_nomap_engine - CCP pass-through operation
 *   without perक्रमming DMA mapping
 * @bit_mod: bitwise operation to perक्रमm
 * @byte_swap: byteswap operation to perक्रमm
 * @mask: mask to be applied to data
 * @mask_len: length in bytes of mask
 * @src: data to be used क्रम this operation
 * @dst: data produced by this operation
 * @src_len: length in bytes of data used क्रम this operation
 * @final: indicate final pass-through operation
 *
 * Variables required to be set when calling ccp_enqueue_cmd():
 *   - bit_mod, byte_swap, src, dst, src_len
 *   - mask, mask_len अगर bit_mod is not CCP_PASSTHRU_BITWISE_NOOP
 */
काष्ठा ccp_passthru_nomap_engine अणु
	क्रमागत ccp_passthru_bitwise bit_mod;
	क्रमागत ccp_passthru_byteswap byte_swap;

	dma_addr_t mask;
	u32 mask_len;		/* In bytes */

	dma_addr_t src_dma, dst_dma;
	u64 src_len;		/* In bytes */

	u32 final;
पूर्ण;

/***** ECC engine *****/
#घोषणा CCP_ECC_MODULUS_BYTES	48	/* 384-bits */
#घोषणा CCP_ECC_MAX_OPERANDS	6
#घोषणा CCP_ECC_MAX_OUTPUTS	3

/**
 * ccp_ecc_function - type of ECC function
 *
 * @CCP_ECC_FUNCTION_MMUL_384BIT: 384-bit modular multiplication
 * @CCP_ECC_FUNCTION_MADD_384BIT: 384-bit modular addition
 * @CCP_ECC_FUNCTION_MINV_384BIT: 384-bit multiplicative inverse
 * @CCP_ECC_FUNCTION_PADD_384BIT: 384-bit poपूर्णांक addition
 * @CCP_ECC_FUNCTION_PMUL_384BIT: 384-bit poपूर्णांक multiplication
 * @CCP_ECC_FUNCTION_PDBL_384BIT: 384-bit poपूर्णांक करोubling
 */
क्रमागत ccp_ecc_function अणु
	CCP_ECC_FUNCTION_MMUL_384BIT = 0,
	CCP_ECC_FUNCTION_MADD_384BIT,
	CCP_ECC_FUNCTION_MINV_384BIT,
	CCP_ECC_FUNCTION_PADD_384BIT,
	CCP_ECC_FUNCTION_PMUL_384BIT,
	CCP_ECC_FUNCTION_PDBL_384BIT,
पूर्ण;

/**
 * काष्ठा ccp_ecc_modular_math - CCP ECC modular math parameters
 * @opeअक्रम_1: first opeअक्रम क्रम the modular math operation
 * @opeअक्रम_1_len: length of the first opeअक्रम
 * @opeअक्रम_2: second opeअक्रम क्रम the modular math operation
 *	       (not used क्रम CCP_ECC_FUNCTION_MINV_384BIT)
 * @opeअक्रम_2_len: length of the second opeअक्रम
 *	       (not used क्रम CCP_ECC_FUNCTION_MINV_384BIT)
 * @result: result of the modular math operation
 * @result_len: length of the supplied result buffer
 */
काष्ठा ccp_ecc_modular_math अणु
	काष्ठा scatterlist *opeअक्रम_1;
	अचिन्हित पूर्णांक opeअक्रम_1_len;	/* In bytes */

	काष्ठा scatterlist *opeअक्रम_2;
	अचिन्हित पूर्णांक opeअक्रम_2_len;	/* In bytes */

	काष्ठा scatterlist *result;
	अचिन्हित पूर्णांक result_len;	/* In bytes */
पूर्ण;

/**
 * काष्ठा ccp_ecc_poपूर्णांक - CCP ECC poपूर्णांक definition
 * @x: the x coordinate of the ECC poपूर्णांक
 * @x_len: the length of the x coordinate
 * @y: the y coordinate of the ECC poपूर्णांक
 * @y_len: the length of the y coordinate
 */
काष्ठा ccp_ecc_poपूर्णांक अणु
	काष्ठा scatterlist *x;
	अचिन्हित पूर्णांक x_len;	/* In bytes */

	काष्ठा scatterlist *y;
	अचिन्हित पूर्णांक y_len;	/* In bytes */
पूर्ण;

/**
 * काष्ठा ccp_ecc_poपूर्णांक_math - CCP ECC poपूर्णांक math parameters
 * @poपूर्णांक_1: the first poपूर्णांक of the ECC poपूर्णांक math operation
 * @poपूर्णांक_2: the second poपूर्णांक of the ECC poपूर्णांक math operation
 *	     (only used क्रम CCP_ECC_FUNCTION_PADD_384BIT)
 * @करोमुख्य_a: the a parameter of the ECC curve
 * @करोमुख्य_a_len: the length of the a parameter
 * @scalar: the scalar parameter क्रम the poपूर्णांक match operation
 *	    (only used क्रम CCP_ECC_FUNCTION_PMUL_384BIT)
 * @scalar_len: the length of the scalar parameter
 *		(only used क्रम CCP_ECC_FUNCTION_PMUL_384BIT)
 * @result: the poपूर्णांक resulting from the poपूर्णांक math operation
 */
काष्ठा ccp_ecc_poपूर्णांक_math अणु
	काष्ठा ccp_ecc_poपूर्णांक poपूर्णांक_1;
	काष्ठा ccp_ecc_poपूर्णांक poपूर्णांक_2;

	काष्ठा scatterlist *करोमुख्य_a;
	अचिन्हित पूर्णांक करोमुख्य_a_len;	/* In bytes */

	काष्ठा scatterlist *scalar;
	अचिन्हित पूर्णांक scalar_len;	/* In bytes */

	काष्ठा ccp_ecc_poपूर्णांक result;
पूर्ण;

/**
 * काष्ठा ccp_ecc_engine - CCP ECC operation
 * @function: ECC function to perक्रमm
 * @mod: ECC modulus
 * @mod_len: length in bytes of modulus
 * @mm: module math parameters
 * @pm: poपूर्णांक math parameters
 * @ecc_result: result of the ECC operation
 *
 * Variables required to be set when calling ccp_enqueue_cmd():
 *   - function, mod, mod_len
 *   - opeअक्रम, opeअक्रम_len, opeअक्रम_count, output, output_len, output_count
 *   - ecc_result
 */
काष्ठा ccp_ecc_engine अणु
	क्रमागत ccp_ecc_function function;

	काष्ठा scatterlist *mod;
	u32 mod_len;		/* In bytes */

	जोड़ अणु
		काष्ठा ccp_ecc_modular_math mm;
		काष्ठा ccp_ecc_poपूर्णांक_math pm;
	पूर्ण u;

	u16 ecc_result;
पूर्ण;


/**
 * ccp_engine - CCP operation identअगरiers
 *
 * @CCP_ENGINE_AES: AES operation
 * @CCP_ENGINE_XTS_AES: 128-bit XTS AES operation
 * @CCP_ENGINE_RSVD1: unused
 * @CCP_ENGINE_SHA: SHA operation
 * @CCP_ENGINE_RSA: RSA operation
 * @CCP_ENGINE_PASSTHRU: pass-through operation
 * @CCP_ENGINE_ZLIB_DECOMPRESS: unused
 * @CCP_ENGINE_ECC: ECC operation
 */
क्रमागत ccp_engine अणु
	CCP_ENGINE_AES = 0,
	CCP_ENGINE_XTS_AES_128,
	CCP_ENGINE_DES3,
	CCP_ENGINE_SHA,
	CCP_ENGINE_RSA,
	CCP_ENGINE_PASSTHRU,
	CCP_ENGINE_ZLIB_DECOMPRESS,
	CCP_ENGINE_ECC,
	CCP_ENGINE__LAST,
पूर्ण;

/* Flag values क्रम flags member of ccp_cmd */
#घोषणा CCP_CMD_MAY_BACKLOG		0x00000001
#घोषणा CCP_CMD_PASSTHRU_NO_DMA_MAP	0x00000002

/**
 * काष्ठा ccp_cmd - CCP operation request
 * @entry: list element (ccp driver use only)
 * @work: work element used क्रम callbacks (ccp driver use only)
 * @ccp: CCP device to be run on
 * @ret: operation वापस code (ccp driver use only)
 * @flags: cmd processing flags
 * @engine: CCP operation to perक्रमm
 * @engine_error: CCP engine वापस code
 * @u: engine specअगरic काष्ठाures, refer to specअगरic engine काष्ठा below
 * @callback: operation completion callback function
 * @data: parameter value to be supplied to the callback function
 *
 * Variables required to be set when calling ccp_enqueue_cmd():
 *   - engine, callback
 *   - See the operation काष्ठाures below क्रम what is required क्रम each
 *     operation.
 */
काष्ठा ccp_cmd अणु
	/* The list_head, work_काष्ठा, ccp and ret variables are क्रम use
	 * by the CCP driver only.
	 */
	काष्ठा list_head entry;
	काष्ठा work_काष्ठा work;
	काष्ठा ccp_device *ccp;
	पूर्णांक ret;

	u32 flags;

	क्रमागत ccp_engine engine;
	u32 engine_error;

	जोड़ अणु
		काष्ठा ccp_aes_engine aes;
		काष्ठा ccp_xts_aes_engine xts;
		काष्ठा ccp_des3_engine des3;
		काष्ठा ccp_sha_engine sha;
		काष्ठा ccp_rsa_engine rsa;
		काष्ठा ccp_passthru_engine passthru;
		काष्ठा ccp_passthru_nomap_engine passthru_nomap;
		काष्ठा ccp_ecc_engine ecc;
	पूर्ण u;

	/* Completion callback support */
	व्योम (*callback)(व्योम *data, पूर्णांक err);
	व्योम *data;
पूर्ण;

#पूर्ण_अगर
