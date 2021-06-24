<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * K3 SA2UL crypto accelerator driver
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com
 *
 * Authors:	Keerthy
 *		Vitaly Andrianov
 *		Tero Kristo
 */
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <crypto/aes.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/des.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>

#समावेश "sa2ul.h"

/* Byte offset क्रम key in encryption security context */
#घोषणा SC_ENC_KEY_OFFSET (1 + 27 + 4)
/* Byte offset क्रम Aux-1 in encryption security context */
#घोषणा SC_ENC_AUX1_OFFSET (1 + 27 + 4 + 32)

#घोषणा SA_CMDL_UPD_ENC         0x0001
#घोषणा SA_CMDL_UPD_AUTH        0x0002
#घोषणा SA_CMDL_UPD_ENC_IV      0x0004
#घोषणा SA_CMDL_UPD_AUTH_IV     0x0008
#घोषणा SA_CMDL_UPD_AUX_KEY     0x0010

#घोषणा SA_AUTH_SUBKEY_LEN	16
#घोषणा SA_CMDL_PAYLOAD_LENGTH_MASK	0xFFFF
#घोषणा SA_CMDL_SOP_BYPASS_LEN_MASK	0xFF000000

#घोषणा MODE_CONTROL_BYTES	27
#घोषणा SA_HASH_PROCESSING	0
#घोषणा SA_CRYPTO_PROCESSING	0
#घोषणा SA_UPLOAD_HASH_TO_TLR	BIT(6)

#घोषणा SA_SW0_FLAGS_MASK	0xF0000
#घोषणा SA_SW0_CMDL_INFO_MASK	0x1F00000
#घोषणा SA_SW0_CMDL_PRESENT	BIT(4)
#घोषणा SA_SW0_ENG_ID_MASK	0x3E000000
#घोषणा SA_SW0_DEST_INFO_PRESENT	BIT(30)
#घोषणा SA_SW2_EGRESS_LENGTH		0xFF000000
#घोषणा SA_BASIC_HASH		0x10

#घोषणा SHA256_DIGEST_WORDS    8
/* Make 32-bit word from 4 bytes */
#घोषणा SA_MK_U32(b0, b1, b2, b3) (((b0) << 24) | ((b1) << 16) | \
				   ((b2) << 8) | (b3))

/* size of SCCTL काष्ठाure in bytes */
#घोषणा SA_SCCTL_SZ 16

/* Max Authentication tag size */
#घोषणा SA_MAX_AUTH_TAG_SZ 64

क्रमागत sa_algo_id अणु
	SA_ALG_CBC_AES = 0,
	SA_ALG_EBC_AES,
	SA_ALG_CBC_DES3,
	SA_ALG_ECB_DES3,
	SA_ALG_SHA1,
	SA_ALG_SHA256,
	SA_ALG_SHA512,
	SA_ALG_AUTHENC_SHA1_AES,
	SA_ALG_AUTHENC_SHA256_AES,
पूर्ण;

काष्ठा sa_match_data अणु
	u8 priv;
	u8 priv_id;
	u32 supported_algos;
	bool skip_engine_control;
पूर्ण;

अटल काष्ठा device *sa_k3_dev;

/**
 * काष्ठा sa_cmdl_cfg - Command label configuration descriptor
 * @aalg: authentication algorithm ID
 * @enc_eng_id: Encryption Engine ID supported by the SA hardware
 * @auth_eng_id: Authentication Engine ID
 * @iv_size: Initialization Vector size
 * @akey: Authentication key
 * @akey_len: Authentication key length
 * @enc: True, अगर this is an encode request
 */
काष्ठा sa_cmdl_cfg अणु
	पूर्णांक aalg;
	u8 enc_eng_id;
	u8 auth_eng_id;
	u8 iv_size;
	स्थिर u8 *akey;
	u16 akey_len;
	bool enc;
पूर्ण;

/**
 * काष्ठा algo_data - Crypto algorithm specअगरic data
 * @enc_eng: Encryption engine info काष्ठाure
 * @auth_eng: Authentication engine info काष्ठाure
 * @auth_ctrl: Authentication control word
 * @hash_size: Size of digest
 * @iv_idx: iv index in psdata
 * @iv_out_size: iv out size
 * @ealg_id: Encryption Algorithm ID
 * @aalg_id: Authentication algorithm ID
 * @mci_enc: Mode Control Inकाष्ठाion क्रम Encryption algorithm
 * @mci_dec: Mode Control Inकाष्ठाion क्रम Decryption
 * @inv_key: Whether the encryption algorithm demands key inversion
 * @ctx: Poपूर्णांकer to the algorithm context
 * @keyed_mac: Whether the authentication algorithm has key
 * @prep_iopad: Function poपूर्णांकer to generate पूर्णांकermediate ipad/opad
 */
काष्ठा algo_data अणु
	काष्ठा sa_eng_info enc_eng;
	काष्ठा sa_eng_info auth_eng;
	u8 auth_ctrl;
	u8 hash_size;
	u8 iv_idx;
	u8 iv_out_size;
	u8 ealg_id;
	u8 aalg_id;
	u8 *mci_enc;
	u8 *mci_dec;
	bool inv_key;
	काष्ठा sa_tfm_ctx *ctx;
	bool keyed_mac;
	व्योम (*prep_iopad)(काष्ठा algo_data *algo, स्थिर u8 *key,
			   u16 key_sz, __be32 *ipad, __be32 *opad);
पूर्ण;

/**
 * काष्ठा sa_alg_पंचांगpl: A generic ढाँचा encompassing crypto/aead algorithms
 * @type: Type of the crypto algorithm.
 * @alg: Union of crypto algorithm definitions.
 * @रेजिस्टरed: Flag indicating अगर the crypto algorithm is alपढ़ोy रेजिस्टरed
 */
काष्ठा sa_alg_पंचांगpl अणु
	u32 type;		/* CRYPTO_ALG_TYPE from <linux/crypto.h> */
	जोड़ अणु
		काष्ठा skcipher_alg skcipher;
		काष्ठा ahash_alg ahash;
		काष्ठा aead_alg aead;
	पूर्ण alg;
	bool रेजिस्टरed;
पूर्ण;

/**
 * काष्ठा sa_mapped_sg: scatterlist inक्रमmation क्रम tx and rx
 * @mapped: Set to true अगर the @sgt is mapped
 * @dir: mapping direction used क्रम @sgt
 * @split_sg: Set अगर the sg is split and needs to be मुक्तd up
 * @अटल_sg: Static scatterlist entry क्रम overriding data
 * @sgt: scatterlist table क्रम DMA API use
 */
काष्ठा sa_mapped_sg अणु
	bool mapped;
	क्रमागत dma_data_direction dir;
	काष्ठा scatterlist अटल_sg;
	काष्ठा scatterlist *split_sg;
	काष्ठा sg_table sgt;
पूर्ण;
/**
 * काष्ठा sa_rx_data: RX Packet miscellaneous data place holder
 * @req: crypto request data poपूर्णांकer
 * @ddev: poपूर्णांकer to the DMA device
 * @tx_in: dma_async_tx_descriptor poपूर्णांकer क्रम rx channel
 * @mapped_sg: Inक्रमmation on tx (0) and rx (1) scatterlist DMA mapping
 * @enc: Flag indicating either encryption or decryption
 * @enc_iv_size: Initialisation vector size
 * @iv_idx: Initialisation vector index
 */
काष्ठा sa_rx_data अणु
	व्योम *req;
	काष्ठा device *ddev;
	काष्ठा dma_async_tx_descriptor *tx_in;
	काष्ठा sa_mapped_sg mapped_sg[2];
	u8 enc;
	u8 enc_iv_size;
	u8 iv_idx;
पूर्ण;

/**
 * काष्ठा sa_req: SA request definition
 * @dev: device क्रम the request
 * @size: total data to the xmitted via DMA
 * @enc_offset: offset of cipher data
 * @enc_size: data to be passed to cipher engine
 * @enc_iv: cipher IV
 * @auth_offset: offset of the authentication data
 * @auth_size: size of the authentication data
 * @auth_iv: authentication IV
 * @type: algorithm type क्रम the request
 * @cmdl: command label poपूर्णांकer
 * @base: poपूर्णांकer to the base request
 * @ctx: poपूर्णांकer to the algorithm context data
 * @enc: true अगर this is an encode request
 * @src: source data
 * @dst: destination data
 * @callback: DMA callback क्रम the request
 * @mdata_size: metadata size passed to DMA
 */
काष्ठा sa_req अणु
	काष्ठा device *dev;
	u16 size;
	u8 enc_offset;
	u16 enc_size;
	u8 *enc_iv;
	u8 auth_offset;
	u16 auth_size;
	u8 *auth_iv;
	u32 type;
	u32 *cmdl;
	काष्ठा crypto_async_request *base;
	काष्ठा sa_tfm_ctx *ctx;
	bool enc;
	काष्ठा scatterlist *src;
	काष्ठा scatterlist *dst;
	dma_async_tx_callback callback;
	u16 mdata_size;
पूर्ण;

/*
 * Mode Control Inकाष्ठाions क्रम various Key lengths 128, 192, 256
 * For CBC (Cipher Block Chaining) mode क्रम encryption
 */
अटल u8 mci_cbc_enc_array[3][MODE_CONTROL_BYTES] = अणु
	अणु	0x61, 0x00, 0x00, 0x18, 0x88, 0x0a, 0xaa, 0x4b, 0x7e, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x61, 0x00, 0x00, 0x18, 0x88, 0x4a, 0xaa, 0x4b, 0x7e, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x61, 0x00, 0x00, 0x18, 0x88, 0x8a, 0xaa, 0x4b, 0x7e, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
पूर्ण;

/*
 * Mode Control Inकाष्ठाions क्रम various Key lengths 128, 192, 256
 * For CBC (Cipher Block Chaining) mode क्रम decryption
 */
अटल u8 mci_cbc_dec_array[3][MODE_CONTROL_BYTES] = अणु
	अणु	0x71, 0x00, 0x00, 0x80, 0x8a, 0xca, 0x98, 0xf4, 0x40, 0xc0,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x71, 0x00, 0x00, 0x84, 0x8a, 0xca, 0x98, 0xf4, 0x40, 0xc0,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x71, 0x00, 0x00, 0x88, 0x8a, 0xca, 0x98, 0xf4, 0x40, 0xc0,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
पूर्ण;

/*
 * Mode Control Inकाष्ठाions क्रम various Key lengths 128, 192, 256
 * For CBC (Cipher Block Chaining) mode क्रम encryption
 */
अटल u8 mci_cbc_enc_no_iv_array[3][MODE_CONTROL_BYTES] = अणु
	अणु	0x21, 0x00, 0x00, 0x18, 0x88, 0x0a, 0xaa, 0x4b, 0x7e, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x21, 0x00, 0x00, 0x18, 0x88, 0x4a, 0xaa, 0x4b, 0x7e, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x21, 0x00, 0x00, 0x18, 0x88, 0x8a, 0xaa, 0x4b, 0x7e, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
पूर्ण;

/*
 * Mode Control Inकाष्ठाions क्रम various Key lengths 128, 192, 256
 * For CBC (Cipher Block Chaining) mode क्रम decryption
 */
अटल u8 mci_cbc_dec_no_iv_array[3][MODE_CONTROL_BYTES] = अणु
	अणु	0x31, 0x00, 0x00, 0x80, 0x8a, 0xca, 0x98, 0xf4, 0x40, 0xc0,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x31, 0x00, 0x00, 0x84, 0x8a, 0xca, 0x98, 0xf4, 0x40, 0xc0,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x31, 0x00, 0x00, 0x88, 0x8a, 0xca, 0x98, 0xf4, 0x40, 0xc0,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
पूर्ण;

/*
 * Mode Control Inकाष्ठाions क्रम various Key lengths 128, 192, 256
 * For ECB (Electronic Code Book) mode क्रम encryption
 */
अटल u8 mci_ecb_enc_array[3][27] = अणु
	अणु	0x21, 0x00, 0x00, 0x80, 0x8a, 0x04, 0xb7, 0x90, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x21, 0x00, 0x00, 0x84, 0x8a, 0x04, 0xb7, 0x90, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x21, 0x00, 0x00, 0x88, 0x8a, 0x04, 0xb7, 0x90, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
पूर्ण;

/*
 * Mode Control Inकाष्ठाions क्रम various Key lengths 128, 192, 256
 * For ECB (Electronic Code Book) mode क्रम decryption
 */
अटल u8 mci_ecb_dec_array[3][27] = अणु
	अणु	0x31, 0x00, 0x00, 0x80, 0x8a, 0x04, 0xb7, 0x90, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x31, 0x00, 0x00, 0x84, 0x8a, 0x04, 0xb7, 0x90, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
	अणु	0x31, 0x00, 0x00, 0x88, 0x8a, 0x04, 0xb7, 0x90, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	पूर्ण,
पूर्ण;

/*
 * Mode Control Inकाष्ठाions क्रम DES algorithm
 * For CBC (Cipher Block Chaining) mode and ECB mode
 * encryption and क्रम decryption respectively
 */
अटल u8 mci_cbc_3des_enc_array[MODE_CONTROL_BYTES] = अणु
	0x60, 0x00, 0x00, 0x18, 0x88, 0x52, 0xaa, 0x4b, 0x7e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
पूर्ण;

अटल u8 mci_cbc_3des_dec_array[MODE_CONTROL_BYTES] = अणु
	0x70, 0x00, 0x00, 0x85, 0x0a, 0xca, 0x98, 0xf4, 0x40, 0xc0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
पूर्ण;

अटल u8 mci_ecb_3des_enc_array[MODE_CONTROL_BYTES] = अणु
	0x20, 0x00, 0x00, 0x85, 0x0a, 0x04, 0xb7, 0x90, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
पूर्ण;

अटल u8 mci_ecb_3des_dec_array[MODE_CONTROL_BYTES] = अणु
	0x30, 0x00, 0x00, 0x85, 0x0a, 0x04, 0xb7, 0x90, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
पूर्ण;

/*
 * Perक्रमm 16 byte or 128 bit swizzling
 * The SA2UL Expects the security context to
 * be in little Endian and the bus width is 128 bits or 16 bytes
 * Hence swap 16 bytes at a समय from higher to lower address
 */
अटल व्योम sa_swiz_128(u8 *in, u16 len)
अणु
	u8 data[16];
	पूर्णांक i, j;

	क्रम (i = 0; i < len; i += 16) अणु
		स_नकल(data, &in[i], 16);
		क्रम (j = 0; j < 16; j++)
			in[i + j] = data[15 - j];
	पूर्ण
पूर्ण

/* Prepare the ipad and opad from key as per SHA algorithm step 1*/
अटल व्योम prepare_kipad(u8 *k_ipad, स्थिर u8 *key, u16 key_sz)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < key_sz; i++)
		k_ipad[i] = key[i] ^ 0x36;

	/* Instead of XOR with 0 */
	क्रम (; i < SHA1_BLOCK_SIZE; i++)
		k_ipad[i] = 0x36;
पूर्ण

अटल व्योम prepare_kopad(u8 *k_opad, स्थिर u8 *key, u16 key_sz)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < key_sz; i++)
		k_opad[i] = key[i] ^ 0x5c;

	/* Instead of XOR with 0 */
	क्रम (; i < SHA1_BLOCK_SIZE; i++)
		k_opad[i] = 0x5c;
पूर्ण

अटल व्योम sa_export_shash(व्योम *state, काष्ठा shash_desc *hash,
			    पूर्णांक digest_size, __be32 *out)
अणु
	काष्ठा sha1_state *sha1;
	काष्ठा sha256_state *sha256;
	u32 *result;

	चयन (digest_size) अणु
	हाल SHA1_DIGEST_SIZE:
		sha1 = state;
		result = sha1->state;
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		sha256 = state;
		result = sha256->state;
		अवरोध;
	शेष:
		dev_err(sa_k3_dev, "%s: bad digest_size=%d\n", __func__,
			digest_size);
		वापस;
	पूर्ण

	crypto_shash_export(hash, state);

	cpu_to_be32_array(out, result, digest_size / 4);
पूर्ण

अटल व्योम sa_prepare_iopads(काष्ठा algo_data *data, स्थिर u8 *key,
			      u16 key_sz, __be32 *ipad, __be32 *opad)
अणु
	SHASH_DESC_ON_STACK(shash, data->ctx->shash);
	पूर्णांक block_size = crypto_shash_blocksize(data->ctx->shash);
	पूर्णांक digest_size = crypto_shash_digestsize(data->ctx->shash);
	जोड़ अणु
		काष्ठा sha1_state sha1;
		काष्ठा sha256_state sha256;
		u8 k_pad[SHA1_BLOCK_SIZE];
	पूर्ण sha;

	shash->tfm = data->ctx->shash;

	prepare_kipad(sha.k_pad, key, key_sz);

	crypto_shash_init(shash);
	crypto_shash_update(shash, sha.k_pad, block_size);
	sa_export_shash(&sha, shash, digest_size, ipad);

	prepare_kopad(sha.k_pad, key, key_sz);

	crypto_shash_init(shash);
	crypto_shash_update(shash, sha.k_pad, block_size);

	sa_export_shash(&sha, shash, digest_size, opad);

	memzero_explicit(&sha, माप(sha));
पूर्ण

/* Derive the inverse key used in AES-CBC decryption operation */
अटल अंतरभूत पूर्णांक sa_aes_inv_key(u8 *inv_key, स्थिर u8 *key, u16 key_sz)
अणु
	काष्ठा crypto_aes_ctx ctx;
	पूर्णांक key_pos;

	अगर (aes_expandkey(&ctx, key, key_sz)) अणु
		dev_err(sa_k3_dev, "%s: bad key len(%d)\n", __func__, key_sz);
		वापस -EINVAL;
	पूर्ण

	/* work around to get the right inverse क्रम AES_KEYSIZE_192 size keys */
	अगर (key_sz == AES_KEYSIZE_192) अणु
		ctx.key_enc[52] = ctx.key_enc[51] ^ ctx.key_enc[46];
		ctx.key_enc[53] = ctx.key_enc[52] ^ ctx.key_enc[47];
	पूर्ण

	/* Based crypto_aes_expand_key logic */
	चयन (key_sz) अणु
	हाल AES_KEYSIZE_128:
	हाल AES_KEYSIZE_192:
		key_pos = key_sz + 24;
		अवरोध;

	हाल AES_KEYSIZE_256:
		key_pos = key_sz + 24 - 4;
		अवरोध;

	शेष:
		dev_err(sa_k3_dev, "%s: bad key len(%d)\n", __func__, key_sz);
		वापस -EINVAL;
	पूर्ण

	स_नकल(inv_key, &ctx.key_enc[key_pos], key_sz);
	वापस 0;
पूर्ण

/* Set Security context क्रम the encryption engine */
अटल पूर्णांक sa_set_sc_enc(काष्ठा algo_data *ad, स्थिर u8 *key, u16 key_sz,
			 u8 enc, u8 *sc_buf)
अणु
	स्थिर u8 *mci = शून्य;

	/* Set Encryption mode selector to crypto processing */
	sc_buf[0] = SA_CRYPTO_PROCESSING;

	अगर (enc)
		mci = ad->mci_enc;
	अन्यथा
		mci = ad->mci_dec;
	/* Set the mode control inकाष्ठाions in security context */
	अगर (mci)
		स_नकल(&sc_buf[1], mci, MODE_CONTROL_BYTES);

	/* For AES-CBC decryption get the inverse key */
	अगर (ad->inv_key && !enc) अणु
		अगर (sa_aes_inv_key(&sc_buf[SC_ENC_KEY_OFFSET], key, key_sz))
			वापस -EINVAL;
	/* For all other हालs: key is used */
	पूर्ण अन्यथा अणु
		स_नकल(&sc_buf[SC_ENC_KEY_OFFSET], key, key_sz);
	पूर्ण

	वापस 0;
पूर्ण

/* Set Security context क्रम the authentication engine */
अटल व्योम sa_set_sc_auth(काष्ठा algo_data *ad, स्थिर u8 *key, u16 key_sz,
			   u8 *sc_buf)
अणु
	__be32 *ipad = (व्योम *)(sc_buf + 32);
	__be32 *opad = (व्योम *)(sc_buf + 64);

	/* Set Authentication mode selector to hash processing */
	sc_buf[0] = SA_HASH_PROCESSING;
	/* Auth SW ctrl word: bit[6]=1 (upload computed hash to TLR section) */
	sc_buf[1] = SA_UPLOAD_HASH_TO_TLR;
	sc_buf[1] |= ad->auth_ctrl;

	/* Copy the keys or ipad/opad */
	अगर (ad->keyed_mac)
		ad->prep_iopad(ad, key, key_sz, ipad, opad);
	अन्यथा अणु
		/* basic hash */
		sc_buf[1] |= SA_BASIC_HASH;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sa_copy_iv(__be32 *out, स्थिर u8 *iv, bool size16)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < ((size16) ? 4 : 2); j++) अणु
		*out = cpu_to_be32(*((u32 *)iv));
		iv += 4;
		out++;
	पूर्ण
पूर्ण

/* Format general command label */
अटल पूर्णांक sa_क्रमmat_cmdl_gen(काष्ठा sa_cmdl_cfg *cfg, u8 *cmdl,
			      काष्ठा sa_cmdl_upd_info *upd_info)
अणु
	u8 enc_offset = 0, auth_offset = 0, total = 0;
	u8 enc_next_eng = SA_ENG_ID_OUTPORT2;
	u8 auth_next_eng = SA_ENG_ID_OUTPORT2;
	u32 *word_ptr = (u32 *)cmdl;
	पूर्णांक i;

	/* Clear the command label */
	memzero_explicit(cmdl, (SA_MAX_CMDL_WORDS * माप(u32)));

	/* Iniialize the command update काष्ठाure */
	memzero_explicit(upd_info, माप(*upd_info));

	अगर (cfg->enc_eng_id && cfg->auth_eng_id) अणु
		अगर (cfg->enc) अणु
			auth_offset = SA_CMDL_HEADER_SIZE_BYTES;
			enc_next_eng = cfg->auth_eng_id;

			अगर (cfg->iv_size)
				auth_offset += cfg->iv_size;
		पूर्ण अन्यथा अणु
			enc_offset = SA_CMDL_HEADER_SIZE_BYTES;
			auth_next_eng = cfg->enc_eng_id;
		पूर्ण
	पूर्ण

	अगर (cfg->enc_eng_id) अणु
		upd_info->flags |= SA_CMDL_UPD_ENC;
		upd_info->enc_size.index = enc_offset >> 2;
		upd_info->enc_offset.index = upd_info->enc_size.index + 1;
		/* Encryption command label */
		cmdl[enc_offset + SA_CMDL_OFFSET_NESC] = enc_next_eng;

		/* Encryption modes requiring IV */
		अगर (cfg->iv_size) अणु
			upd_info->flags |= SA_CMDL_UPD_ENC_IV;
			upd_info->enc_iv.index =
				(enc_offset + SA_CMDL_HEADER_SIZE_BYTES) >> 2;
			upd_info->enc_iv.size = cfg->iv_size;

			cmdl[enc_offset + SA_CMDL_OFFSET_LABEL_LEN] =
				SA_CMDL_HEADER_SIZE_BYTES + cfg->iv_size;

			cmdl[enc_offset + SA_CMDL_OFFSET_OPTION_CTRL1] =
				(SA_CTX_ENC_AUX2_OFFSET | (cfg->iv_size >> 3));
			total += SA_CMDL_HEADER_SIZE_BYTES + cfg->iv_size;
		पूर्ण अन्यथा अणु
			cmdl[enc_offset + SA_CMDL_OFFSET_LABEL_LEN] =
						SA_CMDL_HEADER_SIZE_BYTES;
			total += SA_CMDL_HEADER_SIZE_BYTES;
		पूर्ण
	पूर्ण

	अगर (cfg->auth_eng_id) अणु
		upd_info->flags |= SA_CMDL_UPD_AUTH;
		upd_info->auth_size.index = auth_offset >> 2;
		upd_info->auth_offset.index = upd_info->auth_size.index + 1;
		cmdl[auth_offset + SA_CMDL_OFFSET_NESC] = auth_next_eng;
		cmdl[auth_offset + SA_CMDL_OFFSET_LABEL_LEN] =
			SA_CMDL_HEADER_SIZE_BYTES;
		total += SA_CMDL_HEADER_SIZE_BYTES;
	पूर्ण

	total = roundup(total, 8);

	क्रम (i = 0; i < total / 4; i++)
		word_ptr[i] = swab32(word_ptr[i]);

	वापस total;
पूर्ण

/* Update Command label */
अटल अंतरभूत व्योम sa_update_cmdl(काष्ठा sa_req *req, u32 *cmdl,
				  काष्ठा sa_cmdl_upd_info *upd_info)
अणु
	पूर्णांक i = 0, j;

	अगर (likely(upd_info->flags & SA_CMDL_UPD_ENC)) अणु
		cmdl[upd_info->enc_size.index] &= ~SA_CMDL_PAYLOAD_LENGTH_MASK;
		cmdl[upd_info->enc_size.index] |= req->enc_size;
		cmdl[upd_info->enc_offset.index] &=
						~SA_CMDL_SOP_BYPASS_LEN_MASK;
		cmdl[upd_info->enc_offset.index] |=
			((u32)req->enc_offset <<
			 __ffs(SA_CMDL_SOP_BYPASS_LEN_MASK));

		अगर (likely(upd_info->flags & SA_CMDL_UPD_ENC_IV)) अणु
			__be32 *data = (__be32 *)&cmdl[upd_info->enc_iv.index];
			u32 *enc_iv = (u32 *)req->enc_iv;

			क्रम (j = 0; i < upd_info->enc_iv.size; i += 4, j++) अणु
				data[j] = cpu_to_be32(*enc_iv);
				enc_iv++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (likely(upd_info->flags & SA_CMDL_UPD_AUTH)) अणु
		cmdl[upd_info->auth_size.index] &= ~SA_CMDL_PAYLOAD_LENGTH_MASK;
		cmdl[upd_info->auth_size.index] |= req->auth_size;
		cmdl[upd_info->auth_offset.index] &=
			~SA_CMDL_SOP_BYPASS_LEN_MASK;
		cmdl[upd_info->auth_offset.index] |=
			((u32)req->auth_offset <<
			 __ffs(SA_CMDL_SOP_BYPASS_LEN_MASK));
		अगर (upd_info->flags & SA_CMDL_UPD_AUTH_IV) अणु
			sa_copy_iv((व्योम *)&cmdl[upd_info->auth_iv.index],
				   req->auth_iv,
				   (upd_info->auth_iv.size > 8));
		पूर्ण
		अगर (upd_info->flags & SA_CMDL_UPD_AUX_KEY) अणु
			पूर्णांक offset = (req->auth_size & 0xF) ? 4 : 0;

			स_नकल(&cmdl[upd_info->aux_key_info.index],
			       &upd_info->aux_key[offset], 16);
		पूर्ण
	पूर्ण
पूर्ण

/* Format SWINFO words to be sent to SA */
अटल
व्योम sa_set_swinfo(u8 eng_id, u16 sc_id, dma_addr_t sc_phys,
		   u8 cmdl_present, u8 cmdl_offset, u8 flags,
		   u8 hash_size, u32 *swinfo)
अणु
	swinfo[0] = sc_id;
	swinfo[0] |= (flags << __ffs(SA_SW0_FLAGS_MASK));
	अगर (likely(cmdl_present))
		swinfo[0] |= ((cmdl_offset | SA_SW0_CMDL_PRESENT) <<
						__ffs(SA_SW0_CMDL_INFO_MASK));
	swinfo[0] |= (eng_id << __ffs(SA_SW0_ENG_ID_MASK));

	swinfo[0] |= SA_SW0_DEST_INFO_PRESENT;
	swinfo[1] = (u32)(sc_phys & 0xFFFFFFFFULL);
	swinfo[2] = (u32)((sc_phys & 0xFFFFFFFF00000000ULL) >> 32);
	swinfo[2] |= (hash_size << __ffs(SA_SW2_EGRESS_LENGTH));
पूर्ण

/* Dump the security context */
अटल व्योम sa_dump_sc(u8 *buf, dma_addr_t dma_addr)
अणु
#अगर_घोषित DEBUG
	dev_info(sa_k3_dev, "Security context dump:: 0x%pad\n", &dma_addr);
	prपूर्णांक_hex_dump(KERN_CONT, "", DUMP_PREFIX_OFFSET,
		       16, 1, buf, SA_CTX_MAX_SZ, false);
#पूर्ण_अगर
पूर्ण

अटल
पूर्णांक sa_init_sc(काष्ठा sa_ctx_info *ctx, स्थिर काष्ठा sa_match_data *match_data,
	       स्थिर u8 *enc_key, u16 enc_key_sz,
	       स्थिर u8 *auth_key, u16 auth_key_sz,
	       काष्ठा algo_data *ad, u8 enc, u32 *swinfo)
अणु
	पूर्णांक enc_sc_offset = 0;
	पूर्णांक auth_sc_offset = 0;
	u8 *sc_buf = ctx->sc;
	u16 sc_id = ctx->sc_id;
	u8 first_engine = 0;

	memzero_explicit(sc_buf, SA_CTX_MAX_SZ);

	अगर (ad->auth_eng.eng_id) अणु
		अगर (enc)
			first_engine = ad->enc_eng.eng_id;
		अन्यथा
			first_engine = ad->auth_eng.eng_id;

		enc_sc_offset = SA_CTX_PHP_PE_CTX_SZ;
		auth_sc_offset = enc_sc_offset + ad->enc_eng.sc_size;
		sc_buf[1] = SA_SCCTL_FE_AUTH_ENC;
		अगर (!ad->hash_size)
			वापस -EINVAL;
		ad->hash_size = roundup(ad->hash_size, 8);

	पूर्ण अन्यथा अगर (ad->enc_eng.eng_id && !ad->auth_eng.eng_id) अणु
		enc_sc_offset = SA_CTX_PHP_PE_CTX_SZ;
		first_engine = ad->enc_eng.eng_id;
		sc_buf[1] = SA_SCCTL_FE_ENC;
		ad->hash_size = ad->iv_out_size;
	पूर्ण

	/* SCCTL Owner info: 0=host, 1=CP_ACE */
	sc_buf[SA_CTX_SCCTL_OWNER_OFFSET] = 0;
	स_नकल(&sc_buf[2], &sc_id, 2);
	sc_buf[4] = 0x0;
	sc_buf[5] = match_data->priv_id;
	sc_buf[6] = match_data->priv;
	sc_buf[7] = 0x0;

	/* Prepare context क्रम encryption engine */
	अगर (ad->enc_eng.sc_size) अणु
		अगर (sa_set_sc_enc(ad, enc_key, enc_key_sz, enc,
				  &sc_buf[enc_sc_offset]))
			वापस -EINVAL;
	पूर्ण

	/* Prepare context क्रम authentication engine */
	अगर (ad->auth_eng.sc_size)
		sa_set_sc_auth(ad, auth_key, auth_key_sz,
			       &sc_buf[auth_sc_offset]);

	/* Set the ownership of context to CP_ACE */
	sc_buf[SA_CTX_SCCTL_OWNER_OFFSET] = 0x80;

	/* swizzle the security context */
	sa_swiz_128(sc_buf, SA_CTX_MAX_SZ);

	sa_set_swinfo(first_engine, ctx->sc_id, ctx->sc_phys, 1, 0,
		      SA_SW_INFO_FLAG_EVICT, ad->hash_size, swinfo);

	sa_dump_sc(sc_buf, ctx->sc_phys);

	वापस 0;
पूर्ण

/* Free the per direction context memory */
अटल व्योम sa_मुक्त_ctx_info(काष्ठा sa_ctx_info *ctx,
			     काष्ठा sa_crypto_data *data)
अणु
	अचिन्हित दीर्घ bn;

	bn = ctx->sc_id - data->sc_id_start;
	spin_lock(&data->scid_lock);
	__clear_bit(bn, data->ctx_bm);
	data->sc_id--;
	spin_unlock(&data->scid_lock);

	अगर (ctx->sc) अणु
		dma_pool_मुक्त(data->sc_pool, ctx->sc, ctx->sc_phys);
		ctx->sc = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक sa_init_ctx_info(काष्ठा sa_ctx_info *ctx,
			    काष्ठा sa_crypto_data *data)
अणु
	अचिन्हित दीर्घ bn;
	पूर्णांक err;

	spin_lock(&data->scid_lock);
	bn = find_first_zero_bit(data->ctx_bm, SA_MAX_NUM_CTX);
	__set_bit(bn, data->ctx_bm);
	data->sc_id++;
	spin_unlock(&data->scid_lock);

	ctx->sc_id = (u16)(data->sc_id_start + bn);

	ctx->sc = dma_pool_alloc(data->sc_pool, GFP_KERNEL, &ctx->sc_phys);
	अगर (!ctx->sc) अणु
		dev_err(&data->pdev->dev, "Failed to allocate SC memory\n");
		err = -ENOMEM;
		जाओ scid_rollback;
	पूर्ण

	वापस 0;

scid_rollback:
	spin_lock(&data->scid_lock);
	__clear_bit(bn, data->ctx_bm);
	data->sc_id--;
	spin_unlock(&data->scid_lock);

	वापस err;
पूर्ण

अटल व्योम sa_cipher_cra_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा sa_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा sa_crypto_data *data = dev_get_drvdata(sa_k3_dev);

	dev_dbg(sa_k3_dev, "%s(0x%p) sc-ids(0x%x(0x%pad), 0x%x(0x%pad))\n",
		__func__, tfm, ctx->enc.sc_id, &ctx->enc.sc_phys,
		ctx->dec.sc_id, &ctx->dec.sc_phys);

	sa_मुक्त_ctx_info(&ctx->enc, data);
	sa_मुक्त_ctx_info(&ctx->dec, data);

	crypto_मुक्त_skcipher(ctx->fallback.skcipher);
पूर्ण

अटल पूर्णांक sa_cipher_cra_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा sa_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा sa_crypto_data *data = dev_get_drvdata(sa_k3_dev);
	स्थिर अक्षर *name = crypto_tfm_alg_name(&tfm->base);
	काष्ठा crypto_skcipher *child;
	पूर्णांक ret;

	memzero_explicit(ctx, माप(*ctx));
	ctx->dev_data = data;

	ret = sa_init_ctx_info(&ctx->enc, data);
	अगर (ret)
		वापस ret;
	ret = sa_init_ctx_info(&ctx->dec, data);
	अगर (ret) अणु
		sa_मुक्त_ctx_info(&ctx->enc, data);
		वापस ret;
	पूर्ण

	child = crypto_alloc_skcipher(name, 0, CRYPTO_ALG_NEED_FALLBACK);

	अगर (IS_ERR(child)) अणु
		dev_err(sa_k3_dev, "Error allocating fallback algo %s\n", name);
		वापस PTR_ERR(child);
	पूर्ण

	ctx->fallback.skcipher = child;
	crypto_skcipher_set_reqsize(tfm, crypto_skcipher_reqsize(child) +
					 माप(काष्ठा skcipher_request));

	dev_dbg(sa_k3_dev, "%s(0x%p) sc-ids(0x%x(0x%pad), 0x%x(0x%pad))\n",
		__func__, tfm, ctx->enc.sc_id, &ctx->enc.sc_phys,
		ctx->dec.sc_id, &ctx->dec.sc_phys);
	वापस 0;
पूर्ण

अटल पूर्णांक sa_cipher_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen, काष्ठा algo_data *ad)
अणु
	काष्ठा sa_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *child = ctx->fallback.skcipher;
	पूर्णांक cmdl_len;
	काष्ठा sa_cmdl_cfg cfg;
	पूर्णांक ret;

	अगर (keylen != AES_KEYSIZE_128 && keylen != AES_KEYSIZE_192 &&
	    keylen != AES_KEYSIZE_256)
		वापस -EINVAL;

	ad->enc_eng.eng_id = SA_ENG_ID_EM1;
	ad->enc_eng.sc_size = SA_CTX_ENC_TYPE1_SZ;

	memzero_explicit(&cfg, माप(cfg));
	cfg.enc_eng_id = ad->enc_eng.eng_id;
	cfg.iv_size = crypto_skcipher_ivsize(tfm);

	crypto_skcipher_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(child, tfm->base.crt_flags &
					 CRYPTO_TFM_REQ_MASK);
	ret = crypto_skcipher_setkey(child, key, keylen);
	अगर (ret)
		वापस ret;

	/* Setup Encryption Security Context & Command label ढाँचा */
	अगर (sa_init_sc(&ctx->enc, ctx->dev_data->match_data, key, keylen, शून्य, 0,
		       ad, 1, &ctx->enc.epib[1]))
		जाओ badkey;

	cmdl_len = sa_क्रमmat_cmdl_gen(&cfg,
				      (u8 *)ctx->enc.cmdl,
				      &ctx->enc.cmdl_upd_info);
	अगर (cmdl_len <= 0 || (cmdl_len > SA_MAX_CMDL_WORDS * माप(u32)))
		जाओ badkey;

	ctx->enc.cmdl_size = cmdl_len;

	/* Setup Decryption Security Context & Command label ढाँचा */
	अगर (sa_init_sc(&ctx->dec, ctx->dev_data->match_data, key, keylen, शून्य, 0,
		       ad, 0, &ctx->dec.epib[1]))
		जाओ badkey;

	cfg.enc_eng_id = ad->enc_eng.eng_id;
	cmdl_len = sa_क्रमmat_cmdl_gen(&cfg, (u8 *)ctx->dec.cmdl,
				      &ctx->dec.cmdl_upd_info);

	अगर (cmdl_len <= 0 || (cmdl_len > SA_MAX_CMDL_WORDS * माप(u32)))
		जाओ badkey;

	ctx->dec.cmdl_size = cmdl_len;
	ctx->iv_idx = ad->iv_idx;

	वापस 0;

badkey:
	dev_err(sa_k3_dev, "%s: badkey\n", __func__);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sa_aes_cbc_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा algo_data ad = अणु 0 पूर्ण;
	/* Convert the key size (16/24/32) to the key size index (0/1/2) */
	पूर्णांक key_idx = (keylen >> 3) - 2;

	अगर (key_idx >= 3)
		वापस -EINVAL;

	ad.mci_enc = mci_cbc_enc_array[key_idx];
	ad.mci_dec = mci_cbc_dec_array[key_idx];
	ad.inv_key = true;
	ad.ealg_id = SA_EALG_ID_AES_CBC;
	ad.iv_idx = 4;
	ad.iv_out_size = 16;

	वापस sa_cipher_setkey(tfm, key, keylen, &ad);
पूर्ण

अटल पूर्णांक sa_aes_ecb_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा algo_data ad = अणु 0 पूर्ण;
	/* Convert the key size (16/24/32) to the key size index (0/1/2) */
	पूर्णांक key_idx = (keylen >> 3) - 2;

	अगर (key_idx >= 3)
		वापस -EINVAL;

	ad.mci_enc = mci_ecb_enc_array[key_idx];
	ad.mci_dec = mci_ecb_dec_array[key_idx];
	ad.inv_key = true;
	ad.ealg_id = SA_EALG_ID_AES_ECB;

	वापस sa_cipher_setkey(tfm, key, keylen, &ad);
पूर्ण

अटल पूर्णांक sa_3des_cbc_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा algo_data ad = अणु 0 पूर्ण;

	ad.mci_enc = mci_cbc_3des_enc_array;
	ad.mci_dec = mci_cbc_3des_dec_array;
	ad.ealg_id = SA_EALG_ID_3DES_CBC;
	ad.iv_idx = 6;
	ad.iv_out_size = 8;

	वापस sa_cipher_setkey(tfm, key, keylen, &ad);
पूर्ण

अटल पूर्णांक sa_3des_ecb_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा algo_data ad = अणु 0 पूर्ण;

	ad.mci_enc = mci_ecb_3des_enc_array;
	ad.mci_dec = mci_ecb_3des_dec_array;

	वापस sa_cipher_setkey(tfm, key, keylen, &ad);
पूर्ण

अटल व्योम sa_sync_from_device(काष्ठा sa_rx_data *rxd)
अणु
	काष्ठा sg_table *sgt;

	अगर (rxd->mapped_sg[0].dir == DMA_BIसूचीECTIONAL)
		sgt = &rxd->mapped_sg[0].sgt;
	अन्यथा
		sgt = &rxd->mapped_sg[1].sgt;

	dma_sync_sgtable_क्रम_cpu(rxd->ddev, sgt, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम sa_मुक्त_sa_rx_data(काष्ठा sa_rx_data *rxd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rxd->mapped_sg); i++) अणु
		काष्ठा sa_mapped_sg *mapped_sg = &rxd->mapped_sg[i];

		अगर (mapped_sg->mapped) अणु
			dma_unmap_sgtable(rxd->ddev, &mapped_sg->sgt,
					  mapped_sg->dir, 0);
			kमुक्त(mapped_sg->split_sg);
		पूर्ण
	पूर्ण

	kमुक्त(rxd);
पूर्ण

अटल व्योम sa_aes_dma_in_callback(व्योम *data)
अणु
	काष्ठा sa_rx_data *rxd = (काष्ठा sa_rx_data *)data;
	काष्ठा skcipher_request *req;
	u32 *result;
	__be32 *mdptr;
	माप_प्रकार ml, pl;
	पूर्णांक i;

	sa_sync_from_device(rxd);
	req = container_of(rxd->req, काष्ठा skcipher_request, base);

	अगर (req->iv) अणु
		mdptr = (__be32 *)dmaengine_desc_get_metadata_ptr(rxd->tx_in, &pl,
							       &ml);
		result = (u32 *)req->iv;

		क्रम (i = 0; i < (rxd->enc_iv_size / 4); i++)
			result[i] = be32_to_cpu(mdptr[i + rxd->iv_idx]);
	पूर्ण

	sa_मुक्त_sa_rx_data(rxd);

	skcipher_request_complete(req, 0);
पूर्ण

अटल व्योम
sa_prepare_tx_desc(u32 *mdptr, u32 pslen, u32 *psdata, u32 epiblen, u32 *epib)
अणु
	u32 *out, *in;
	पूर्णांक i;

	क्रम (out = mdptr, in = epib, i = 0; i < epiblen / माप(u32); i++)
		*out++ = *in++;

	mdptr[4] = (0xFFFF << 16);
	क्रम (out = &mdptr[5], in = psdata, i = 0;
	     i < pslen / माप(u32); i++)
		*out++ = *in++;
पूर्ण

अटल पूर्णांक sa_run(काष्ठा sa_req *req)
अणु
	काष्ठा sa_rx_data *rxd;
	gfp_t gfp_flags;
	u32 cmdl[SA_MAX_CMDL_WORDS];
	काष्ठा sa_crypto_data *pdata = dev_get_drvdata(sa_k3_dev);
	काष्ठा device *ddev;
	काष्ठा dma_chan *dma_rx;
	पूर्णांक sg_nents, src_nents, dst_nents;
	काष्ठा scatterlist *src, *dst;
	माप_प्रकार pl, ml, split_size;
	काष्ठा sa_ctx_info *sa_ctx = req->enc ? &req->ctx->enc : &req->ctx->dec;
	पूर्णांक ret;
	काष्ठा dma_async_tx_descriptor *tx_out;
	u32 *mdptr;
	bool dअगरf_dst;
	क्रमागत dma_data_direction dir_src;
	काष्ठा sa_mapped_sg *mapped_sg;

	gfp_flags = req->base->flags & CRYPTO_TFM_REQ_MAY_SLEEP ?
		GFP_KERNEL : GFP_ATOMIC;

	rxd = kzalloc(माप(*rxd), gfp_flags);
	अगर (!rxd)
		वापस -ENOMEM;

	अगर (req->src != req->dst) अणु
		dअगरf_dst = true;
		dir_src = DMA_TO_DEVICE;
	पूर्ण अन्यथा अणु
		dअगरf_dst = false;
		dir_src = DMA_BIसूचीECTIONAL;
	पूर्ण

	/*
	 * SA2UL has an पूर्णांकeresting feature where the receive DMA channel
	 * is selected based on the data passed to the engine. Within the
	 * transition range, there is also a space where it is impossible
	 * to determine where the data will end up, and this should be
	 * aव्योमed. This will be handled by the SW fallback mechanism by
	 * the inभागidual algorithm implementations.
	 */
	अगर (req->size >= 256)
		dma_rx = pdata->dma_rx2;
	अन्यथा
		dma_rx = pdata->dma_rx1;

	ddev = dmaengine_get_dma_device(pdata->dma_tx);
	rxd->ddev = ddev;

	स_नकल(cmdl, sa_ctx->cmdl, sa_ctx->cmdl_size);

	sa_update_cmdl(req, cmdl, &sa_ctx->cmdl_upd_info);

	अगर (req->type != CRYPTO_ALG_TYPE_AHASH) अणु
		अगर (req->enc)
			req->type |=
				(SA_REQ_SUBTYPE_ENC << SA_REQ_SUBTYPE_SHIFT);
		अन्यथा
			req->type |=
				(SA_REQ_SUBTYPE_DEC << SA_REQ_SUBTYPE_SHIFT);
	पूर्ण

	cmdl[sa_ctx->cmdl_size / माप(u32)] = req->type;

	/*
	 * Map the packets, first we check अगर the data fits पूर्णांकo a single
	 * sg entry and use that अगर possible. If it करोes not fit, we check
	 * अगर we need to करो sg_split to align the scatterlist data on the
	 * actual data size being processed by the crypto engine.
	 */
	src = req->src;
	sg_nents = sg_nents_क्रम_len(src, req->size);

	split_size = req->size;

	mapped_sg = &rxd->mapped_sg[0];
	अगर (sg_nents == 1 && split_size <= req->src->length) अणु
		src = &mapped_sg->अटल_sg;
		src_nents = 1;
		sg_init_table(src, 1);
		sg_set_page(src, sg_page(req->src), split_size,
			    req->src->offset);

		mapped_sg->sgt.sgl = src;
		mapped_sg->sgt.orig_nents = src_nents;
		ret = dma_map_sgtable(ddev, &mapped_sg->sgt, dir_src, 0);
		अगर (ret) अणु
			kमुक्त(rxd);
			वापस ret;
		पूर्ण

		mapped_sg->dir = dir_src;
		mapped_sg->mapped = true;
	पूर्ण अन्यथा अणु
		mapped_sg->sgt.sgl = req->src;
		mapped_sg->sgt.orig_nents = sg_nents;
		ret = dma_map_sgtable(ddev, &mapped_sg->sgt, dir_src, 0);
		अगर (ret) अणु
			kमुक्त(rxd);
			वापस ret;
		पूर्ण

		mapped_sg->dir = dir_src;
		mapped_sg->mapped = true;

		ret = sg_split(mapped_sg->sgt.sgl, mapped_sg->sgt.nents, 0, 1,
			       &split_size, &src, &src_nents, gfp_flags);
		अगर (ret) अणु
			src_nents = mapped_sg->sgt.nents;
			src = mapped_sg->sgt.sgl;
		पूर्ण अन्यथा अणु
			mapped_sg->split_sg = src;
		पूर्ण
	पूर्ण

	dma_sync_sgtable_क्रम_device(ddev, &mapped_sg->sgt, DMA_TO_DEVICE);

	अगर (!dअगरf_dst) अणु
		dst_nents = src_nents;
		dst = src;
	पूर्ण अन्यथा अणु
		dst_nents = sg_nents_क्रम_len(req->dst, req->size);
		mapped_sg = &rxd->mapped_sg[1];

		अगर (dst_nents == 1 && split_size <= req->dst->length) अणु
			dst = &mapped_sg->अटल_sg;
			dst_nents = 1;
			sg_init_table(dst, 1);
			sg_set_page(dst, sg_page(req->dst), split_size,
				    req->dst->offset);

			mapped_sg->sgt.sgl = dst;
			mapped_sg->sgt.orig_nents = dst_nents;
			ret = dma_map_sgtable(ddev, &mapped_sg->sgt,
					      DMA_FROM_DEVICE, 0);
			अगर (ret)
				जाओ err_cleanup;

			mapped_sg->dir = DMA_FROM_DEVICE;
			mapped_sg->mapped = true;
		पूर्ण अन्यथा अणु
			mapped_sg->sgt.sgl = req->dst;
			mapped_sg->sgt.orig_nents = dst_nents;
			ret = dma_map_sgtable(ddev, &mapped_sg->sgt,
					      DMA_FROM_DEVICE, 0);
			अगर (ret)
				जाओ err_cleanup;

			mapped_sg->dir = DMA_FROM_DEVICE;
			mapped_sg->mapped = true;

			ret = sg_split(mapped_sg->sgt.sgl, mapped_sg->sgt.nents,
				       0, 1, &split_size, &dst, &dst_nents,
				       gfp_flags);
			अगर (ret) अणु
				dst_nents = mapped_sg->sgt.nents;
				dst = mapped_sg->sgt.sgl;
			पूर्ण अन्यथा अणु
				mapped_sg->split_sg = dst;
			पूर्ण
		पूर्ण
	पूर्ण

	rxd->tx_in = dmaengine_prep_slave_sg(dma_rx, dst, dst_nents,
					     DMA_DEV_TO_MEM,
					     DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!rxd->tx_in) अणु
		dev_err(pdata->dev, "IN prep_slave_sg() failed\n");
		ret = -EINVAL;
		जाओ err_cleanup;
	पूर्ण

	rxd->req = (व्योम *)req->base;
	rxd->enc = req->enc;
	rxd->iv_idx = req->ctx->iv_idx;
	rxd->enc_iv_size = sa_ctx->cmdl_upd_info.enc_iv.size;
	rxd->tx_in->callback = req->callback;
	rxd->tx_in->callback_param = rxd;

	tx_out = dmaengine_prep_slave_sg(pdata->dma_tx, src,
					 src_nents, DMA_MEM_TO_DEV,
					 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	अगर (!tx_out) अणु
		dev_err(pdata->dev, "OUT prep_slave_sg() failed\n");
		ret = -EINVAL;
		जाओ err_cleanup;
	पूर्ण

	/*
	 * Prepare metadata क्रम DMA engine. This essentially describes the
	 * crypto algorithm to be used, data sizes, dअगरferent keys etc.
	 */
	mdptr = (u32 *)dmaengine_desc_get_metadata_ptr(tx_out, &pl, &ml);

	sa_prepare_tx_desc(mdptr, (sa_ctx->cmdl_size + (SA_PSDATA_CTX_WORDS *
				   माप(u32))), cmdl, माप(sa_ctx->epib),
			   sa_ctx->epib);

	ml = sa_ctx->cmdl_size + (SA_PSDATA_CTX_WORDS * माप(u32));
	dmaengine_desc_set_metadata_len(tx_out, req->mdata_size);

	dmaengine_submit(tx_out);
	dmaengine_submit(rxd->tx_in);

	dma_async_issue_pending(dma_rx);
	dma_async_issue_pending(pdata->dma_tx);

	वापस -EINPROGRESS;

err_cleanup:
	sa_मुक्त_sa_rx_data(rxd);

	वापस ret;
पूर्ण

अटल पूर्णांक sa_cipher_run(काष्ठा skcipher_request *req, u8 *iv, पूर्णांक enc)
अणु
	काष्ठा sa_tfm_ctx *ctx =
	    crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	काष्ठा crypto_alg *alg = req->base.tfm->__crt_alg;
	काष्ठा sa_req sa_req = अणु 0 पूर्ण;

	अगर (!req->cryptlen)
		वापस 0;

	अगर (req->cryptlen % alg->cra_blocksize)
		वापस -EINVAL;

	/* Use SW fallback अगर the data size is not supported */
	अगर (req->cryptlen > SA_MAX_DATA_SZ ||
	    (req->cryptlen >= SA_UNSAFE_DATA_SZ_MIN &&
	     req->cryptlen <= SA_UNSAFE_DATA_SZ_MAX)) अणु
		काष्ठा skcipher_request *subreq = skcipher_request_ctx(req);

		skcipher_request_set_tfm(subreq, ctx->fallback.skcipher);
		skcipher_request_set_callback(subreq, req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(subreq, req->src, req->dst,
					   req->cryptlen, req->iv);
		अगर (enc)
			वापस crypto_skcipher_encrypt(subreq);
		अन्यथा
			वापस crypto_skcipher_decrypt(subreq);
	पूर्ण

	sa_req.size = req->cryptlen;
	sa_req.enc_size = req->cryptlen;
	sa_req.src = req->src;
	sa_req.dst = req->dst;
	sa_req.enc_iv = iv;
	sa_req.type = CRYPTO_ALG_TYPE_SKCIPHER;
	sa_req.enc = enc;
	sa_req.callback = sa_aes_dma_in_callback;
	sa_req.mdata_size = 44;
	sa_req.base = &req->base;
	sa_req.ctx = ctx;

	वापस sa_run(&sa_req);
पूर्ण

अटल पूर्णांक sa_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस sa_cipher_run(req, req->iv, 1);
पूर्ण

अटल पूर्णांक sa_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस sa_cipher_run(req, req->iv, 0);
पूर्ण

अटल व्योम sa_sha_dma_in_callback(व्योम *data)
अणु
	काष्ठा sa_rx_data *rxd = (काष्ठा sa_rx_data *)data;
	काष्ठा ahash_request *req;
	काष्ठा crypto_ahash *tfm;
	अचिन्हित पूर्णांक authsize;
	पूर्णांक i;
	माप_प्रकार ml, pl;
	u32 *result;
	__be32 *mdptr;

	sa_sync_from_device(rxd);
	req = container_of(rxd->req, काष्ठा ahash_request, base);
	tfm = crypto_ahash_reqtfm(req);
	authsize = crypto_ahash_digestsize(tfm);

	mdptr = (__be32 *)dmaengine_desc_get_metadata_ptr(rxd->tx_in, &pl, &ml);
	result = (u32 *)req->result;

	क्रम (i = 0; i < (authsize / 4); i++)
		result[i] = be32_to_cpu(mdptr[i + 4]);

	sa_मुक्त_sa_rx_data(rxd);

	ahash_request_complete(req, 0);
पूर्ण

अटल पूर्णांक zero_message_process(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	पूर्णांक sa_digest_size = crypto_ahash_digestsize(tfm);

	चयन (sa_digest_size) अणु
	हाल SHA1_DIGEST_SIZE:
		स_नकल(req->result, sha1_zero_message_hash, sa_digest_size);
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		स_नकल(req->result, sha256_zero_message_hash, sa_digest_size);
		अवरोध;
	हाल SHA512_DIGEST_SIZE:
		स_नकल(req->result, sha512_zero_message_hash, sa_digest_size);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sa_sha_run(काष्ठा ahash_request *req)
अणु
	काष्ठा sa_tfm_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा sa_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा sa_req sa_req = अणु 0 पूर्ण;
	माप_प्रकार auth_len;

	auth_len = req->nbytes;

	अगर (!auth_len)
		वापस zero_message_process(req);

	अगर (auth_len > SA_MAX_DATA_SZ ||
	    (auth_len >= SA_UNSAFE_DATA_SZ_MIN &&
	     auth_len <= SA_UNSAFE_DATA_SZ_MAX)) अणु
		काष्ठा ahash_request *subreq = &rctx->fallback_req;
		पूर्णांक ret = 0;

		ahash_request_set_tfm(subreq, ctx->fallback.ahash);
		subreq->base.flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;

		crypto_ahash_init(subreq);

		subreq->nbytes = auth_len;
		subreq->src = req->src;
		subreq->result = req->result;

		ret |= crypto_ahash_update(subreq);

		subreq->nbytes = 0;

		ret |= crypto_ahash_final(subreq);

		वापस ret;
	पूर्ण

	sa_req.size = auth_len;
	sa_req.auth_size = auth_len;
	sa_req.src = req->src;
	sa_req.dst = req->src;
	sa_req.enc = true;
	sa_req.type = CRYPTO_ALG_TYPE_AHASH;
	sa_req.callback = sa_sha_dma_in_callback;
	sa_req.mdata_size = 28;
	sa_req.ctx = ctx;
	sa_req.base = &req->base;

	वापस sa_run(&sa_req);
पूर्ण

अटल पूर्णांक sa_sha_setup(काष्ठा sa_tfm_ctx *ctx, काष्ठा  algo_data *ad)
अणु
	पूर्णांक bs = crypto_shash_blocksize(ctx->shash);
	पूर्णांक cmdl_len;
	काष्ठा sa_cmdl_cfg cfg;

	ad->enc_eng.sc_size = SA_CTX_ENC_TYPE1_SZ;
	ad->auth_eng.eng_id = SA_ENG_ID_AM1;
	ad->auth_eng.sc_size = SA_CTX_AUTH_TYPE2_SZ;

	स_रखो(ctx->authkey, 0, bs);
	स_रखो(&cfg, 0, माप(cfg));
	cfg.aalg = ad->aalg_id;
	cfg.enc_eng_id = ad->enc_eng.eng_id;
	cfg.auth_eng_id = ad->auth_eng.eng_id;
	cfg.iv_size = 0;
	cfg.akey = शून्य;
	cfg.akey_len = 0;

	ctx->dev_data = dev_get_drvdata(sa_k3_dev);
	/* Setup Encryption Security Context & Command label ढाँचा */
	अगर (sa_init_sc(&ctx->enc, ctx->dev_data->match_data, शून्य, 0, शून्य, 0,
		       ad, 0, &ctx->enc.epib[1]))
		जाओ badkey;

	cmdl_len = sa_क्रमmat_cmdl_gen(&cfg,
				      (u8 *)ctx->enc.cmdl,
				      &ctx->enc.cmdl_upd_info);
	अगर (cmdl_len <= 0 || (cmdl_len > SA_MAX_CMDL_WORDS * माप(u32)))
		जाओ badkey;

	ctx->enc.cmdl_size = cmdl_len;

	वापस 0;

badkey:
	dev_err(sa_k3_dev, "%s: badkey\n", __func__);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sa_sha_cra_init_alg(काष्ठा crypto_tfm *tfm, स्थिर अक्षर *alg_base)
अणु
	काष्ठा sa_tfm_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा sa_crypto_data *data = dev_get_drvdata(sa_k3_dev);
	पूर्णांक ret;

	स_रखो(ctx, 0, माप(*ctx));
	ctx->dev_data = data;
	ret = sa_init_ctx_info(&ctx->enc, data);
	अगर (ret)
		वापस ret;

	अगर (alg_base) अणु
		ctx->shash = crypto_alloc_shash(alg_base, 0,
						CRYPTO_ALG_NEED_FALLBACK);
		अगर (IS_ERR(ctx->shash)) अणु
			dev_err(sa_k3_dev, "base driver %s couldn't be loaded\n",
				alg_base);
			वापस PTR_ERR(ctx->shash);
		पूर्ण
		/* क्रम fallback */
		ctx->fallback.ahash =
			crypto_alloc_ahash(alg_base, 0,
					   CRYPTO_ALG_NEED_FALLBACK);
		अगर (IS_ERR(ctx->fallback.ahash)) अणु
			dev_err(ctx->dev_data->dev,
				"Could not load fallback driver\n");
			वापस PTR_ERR(ctx->fallback.ahash);
		पूर्ण
	पूर्ण

	dev_dbg(sa_k3_dev, "%s(0x%p) sc-ids(0x%x(0x%pad), 0x%x(0x%pad))\n",
		__func__, tfm, ctx->enc.sc_id, &ctx->enc.sc_phys,
		ctx->dec.sc_id, &ctx->dec.sc_phys);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा sa_sha_req_ctx) +
				 crypto_ahash_reqsize(ctx->fallback.ahash));

	वापस 0;
पूर्ण

अटल पूर्णांक sa_sha_digest(काष्ठा ahash_request *req)
अणु
	वापस sa_sha_run(req);
पूर्ण

अटल पूर्णांक sa_sha_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा sa_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा sa_tfm_ctx *ctx = crypto_ahash_ctx(tfm);

	dev_dbg(sa_k3_dev, "init: digest size: %u, rctx=%p\n",
		crypto_ahash_digestsize(tfm), rctx);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback.ahash);
	rctx->fallback_req.base.flags =
		req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_init(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक sa_sha_update(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा sa_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा sa_tfm_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback.ahash);
	rctx->fallback_req.base.flags =
		req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.nbytes = req->nbytes;
	rctx->fallback_req.src = req->src;

	वापस crypto_ahash_update(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक sa_sha_final(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा sa_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा sa_tfm_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback.ahash);
	rctx->fallback_req.base.flags =
		req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.result = req->result;

	वापस crypto_ahash_final(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक sa_sha_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा sa_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा sa_tfm_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback.ahash);
	rctx->fallback_req.base.flags =
		req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;

	rctx->fallback_req.nbytes = req->nbytes;
	rctx->fallback_req.src = req->src;
	rctx->fallback_req.result = req->result;

	वापस crypto_ahash_finup(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक sa_sha_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा sa_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा sa_tfm_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback.ahash);
	rctx->fallback_req.base.flags = req->base.flags &
		CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_import(&rctx->fallback_req, in);
पूर्ण

अटल पूर्णांक sa_sha_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा sa_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा sa_tfm_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ahash_request *subreq = &rctx->fallback_req;

	ahash_request_set_tfm(subreq, ctx->fallback.ahash);
	subreq->base.flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_export(subreq, out);
पूर्ण

अटल पूर्णांक sa_sha1_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा algo_data ad = अणु 0 पूर्ण;
	काष्ठा sa_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	sa_sha_cra_init_alg(tfm, "sha1");

	ad.aalg_id = SA_AALG_ID_SHA1;
	ad.hash_size = SHA1_DIGEST_SIZE;
	ad.auth_ctrl = SA_AUTH_SW_CTRL_SHA1;

	sa_sha_setup(ctx, &ad);

	वापस 0;
पूर्ण

अटल पूर्णांक sa_sha256_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा algo_data ad = अणु 0 पूर्ण;
	काष्ठा sa_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	sa_sha_cra_init_alg(tfm, "sha256");

	ad.aalg_id = SA_AALG_ID_SHA2_256;
	ad.hash_size = SHA256_DIGEST_SIZE;
	ad.auth_ctrl = SA_AUTH_SW_CTRL_SHA256;

	sa_sha_setup(ctx, &ad);

	वापस 0;
पूर्ण

अटल पूर्णांक sa_sha512_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा algo_data ad = अणु 0 पूर्ण;
	काष्ठा sa_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	sa_sha_cra_init_alg(tfm, "sha512");

	ad.aalg_id = SA_AALG_ID_SHA2_512;
	ad.hash_size = SHA512_DIGEST_SIZE;
	ad.auth_ctrl = SA_AUTH_SW_CTRL_SHA512;

	sa_sha_setup(ctx, &ad);

	वापस 0;
पूर्ण

अटल व्योम sa_sha_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा sa_tfm_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा sa_crypto_data *data = dev_get_drvdata(sa_k3_dev);

	dev_dbg(sa_k3_dev, "%s(0x%p) sc-ids(0x%x(0x%pad), 0x%x(0x%pad))\n",
		__func__, tfm, ctx->enc.sc_id, &ctx->enc.sc_phys,
		ctx->dec.sc_id, &ctx->dec.sc_phys);

	अगर (crypto_tfm_alg_type(tfm) == CRYPTO_ALG_TYPE_AHASH)
		sa_मुक्त_ctx_info(&ctx->enc, data);

	crypto_मुक्त_shash(ctx->shash);
	crypto_मुक्त_ahash(ctx->fallback.ahash);
पूर्ण

अटल व्योम sa_aead_dma_in_callback(व्योम *data)
अणु
	काष्ठा sa_rx_data *rxd = (काष्ठा sa_rx_data *)data;
	काष्ठा aead_request *req;
	काष्ठा crypto_aead *tfm;
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक authsize;
	u8 auth_tag[SA_MAX_AUTH_TAG_SZ];
	माप_प्रकार pl, ml;
	पूर्णांक i;
	पूर्णांक err = 0;
	u16 auth_len;
	u32 *mdptr;

	sa_sync_from_device(rxd);
	req = container_of(rxd->req, काष्ठा aead_request, base);
	tfm = crypto_aead_reqtfm(req);
	start = req->assoclen + req->cryptlen;
	authsize = crypto_aead_authsize(tfm);

	mdptr = (u32 *)dmaengine_desc_get_metadata_ptr(rxd->tx_in, &pl, &ml);
	क्रम (i = 0; i < (authsize / 4); i++)
		mdptr[i + 4] = swab32(mdptr[i + 4]);

	auth_len = req->assoclen + req->cryptlen;

	अगर (rxd->enc) अणु
		scatterwalk_map_and_copy(&mdptr[4], req->dst, start, authsize,
					 1);
	पूर्ण अन्यथा अणु
		auth_len -= authsize;
		start -= authsize;
		scatterwalk_map_and_copy(auth_tag, req->src, start, authsize,
					 0);

		err = स_भेद(&mdptr[4], auth_tag, authsize) ? -EBADMSG : 0;
	पूर्ण

	sa_मुक्त_sa_rx_data(rxd);

	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक sa_cra_init_aead(काष्ठा crypto_aead *tfm, स्थिर अक्षर *hash,
			    स्थिर अक्षर *fallback)
अणु
	काष्ठा sa_tfm_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा sa_crypto_data *data = dev_get_drvdata(sa_k3_dev);
	पूर्णांक ret;

	memzero_explicit(ctx, माप(*ctx));
	ctx->dev_data = data;

	ctx->shash = crypto_alloc_shash(hash, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(ctx->shash)) अणु
		dev_err(sa_k3_dev, "base driver %s couldn't be loaded\n", hash);
		वापस PTR_ERR(ctx->shash);
	पूर्ण

	ctx->fallback.aead = crypto_alloc_aead(fallback, 0,
					       CRYPTO_ALG_NEED_FALLBACK);

	अगर (IS_ERR(ctx->fallback.aead)) अणु
		dev_err(sa_k3_dev, "fallback driver %s couldn't be loaded\n",
			fallback);
		वापस PTR_ERR(ctx->fallback.aead);
	पूर्ण

	crypto_aead_set_reqsize(tfm, माप(काष्ठा aead_request) +
				crypto_aead_reqsize(ctx->fallback.aead));

	ret = sa_init_ctx_info(&ctx->enc, data);
	अगर (ret)
		वापस ret;

	ret = sa_init_ctx_info(&ctx->dec, data);
	अगर (ret) अणु
		sa_मुक्त_ctx_info(&ctx->enc, data);
		वापस ret;
	पूर्ण

	dev_dbg(sa_k3_dev, "%s(0x%p) sc-ids(0x%x(0x%pad), 0x%x(0x%pad))\n",
		__func__, tfm, ctx->enc.sc_id, &ctx->enc.sc_phys,
		ctx->dec.sc_id, &ctx->dec.sc_phys);

	वापस ret;
पूर्ण

अटल पूर्णांक sa_cra_init_aead_sha1(काष्ठा crypto_aead *tfm)
अणु
	वापस sa_cra_init_aead(tfm, "sha1",
				"authenc(hmac(sha1-ce),cbc(aes-ce))");
पूर्ण

अटल पूर्णांक sa_cra_init_aead_sha256(काष्ठा crypto_aead *tfm)
अणु
	वापस sa_cra_init_aead(tfm, "sha256",
				"authenc(hmac(sha256-ce),cbc(aes-ce))");
पूर्ण

अटल व्योम sa_निकास_tfm_aead(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा sa_tfm_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा sa_crypto_data *data = dev_get_drvdata(sa_k3_dev);

	crypto_मुक्त_shash(ctx->shash);
	crypto_मुक्त_aead(ctx->fallback.aead);

	sa_मुक्त_ctx_info(&ctx->enc, data);
	sa_मुक्त_ctx_info(&ctx->dec, data);
पूर्ण

/* AEAD algorithm configuration पूर्णांकerface function */
अटल पूर्णांक sa_aead_setkey(काष्ठा crypto_aead *authenc,
			  स्थिर u8 *key, अचिन्हित पूर्णांक keylen,
			  काष्ठा algo_data *ad)
अणु
	काष्ठा sa_tfm_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा crypto_authenc_keys keys;
	पूर्णांक cmdl_len;
	काष्ठा sa_cmdl_cfg cfg;
	पूर्णांक key_idx;

	अगर (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		वापस -EINVAL;

	/* Convert the key size (16/24/32) to the key size index (0/1/2) */
	key_idx = (keys.enckeylen >> 3) - 2;
	अगर (key_idx >= 3)
		वापस -EINVAL;

	ad->ctx = ctx;
	ad->enc_eng.eng_id = SA_ENG_ID_EM1;
	ad->enc_eng.sc_size = SA_CTX_ENC_TYPE1_SZ;
	ad->auth_eng.eng_id = SA_ENG_ID_AM1;
	ad->auth_eng.sc_size = SA_CTX_AUTH_TYPE2_SZ;
	ad->mci_enc = mci_cbc_enc_no_iv_array[key_idx];
	ad->mci_dec = mci_cbc_dec_no_iv_array[key_idx];
	ad->inv_key = true;
	ad->keyed_mac = true;
	ad->ealg_id = SA_EALG_ID_AES_CBC;
	ad->prep_iopad = sa_prepare_iopads;

	स_रखो(&cfg, 0, माप(cfg));
	cfg.enc = true;
	cfg.aalg = ad->aalg_id;
	cfg.enc_eng_id = ad->enc_eng.eng_id;
	cfg.auth_eng_id = ad->auth_eng.eng_id;
	cfg.iv_size = crypto_aead_ivsize(authenc);
	cfg.akey = keys.authkey;
	cfg.akey_len = keys.authkeylen;

	/* Setup Encryption Security Context & Command label ढाँचा */
	अगर (sa_init_sc(&ctx->enc, ctx->dev_data->match_data, keys.enckey,
		       keys.enckeylen, keys.authkey, keys.authkeylen,
		       ad, 1, &ctx->enc.epib[1]))
		वापस -EINVAL;

	cmdl_len = sa_क्रमmat_cmdl_gen(&cfg,
				      (u8 *)ctx->enc.cmdl,
				      &ctx->enc.cmdl_upd_info);
	अगर (cmdl_len <= 0 || (cmdl_len > SA_MAX_CMDL_WORDS * माप(u32)))
		वापस -EINVAL;

	ctx->enc.cmdl_size = cmdl_len;

	/* Setup Decryption Security Context & Command label ढाँचा */
	अगर (sa_init_sc(&ctx->dec, ctx->dev_data->match_data, keys.enckey,
		       keys.enckeylen, keys.authkey, keys.authkeylen,
		       ad, 0, &ctx->dec.epib[1]))
		वापस -EINVAL;

	cfg.enc = false;
	cmdl_len = sa_क्रमmat_cmdl_gen(&cfg, (u8 *)ctx->dec.cmdl,
				      &ctx->dec.cmdl_upd_info);

	अगर (cmdl_len <= 0 || (cmdl_len > SA_MAX_CMDL_WORDS * माप(u32)))
		वापस -EINVAL;

	ctx->dec.cmdl_size = cmdl_len;

	crypto_aead_clear_flags(ctx->fallback.aead, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(ctx->fallback.aead,
			      crypto_aead_get_flags(authenc) &
			      CRYPTO_TFM_REQ_MASK);
	crypto_aead_setkey(ctx->fallback.aead, key, keylen);

	वापस 0;
पूर्ण

अटल पूर्णांक sa_aead_setauthsize(काष्ठा crypto_aead *tfm, अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा sa_tfm_ctx *ctx = crypto_tfm_ctx(crypto_aead_tfm(tfm));

	वापस crypto_aead_setauthsize(ctx->fallback.aead, authsize);
पूर्ण

अटल पूर्णांक sa_aead_cbc_sha1_setkey(काष्ठा crypto_aead *authenc,
				   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा algo_data ad = अणु 0 पूर्ण;

	ad.ealg_id = SA_EALG_ID_AES_CBC;
	ad.aalg_id = SA_AALG_ID_HMAC_SHA1;
	ad.hash_size = SHA1_DIGEST_SIZE;
	ad.auth_ctrl = SA_AUTH_SW_CTRL_SHA1;

	वापस sa_aead_setkey(authenc, key, keylen, &ad);
पूर्ण

अटल पूर्णांक sa_aead_cbc_sha256_setkey(काष्ठा crypto_aead *authenc,
				     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा algo_data ad = अणु 0 पूर्ण;

	ad.ealg_id = SA_EALG_ID_AES_CBC;
	ad.aalg_id = SA_AALG_ID_HMAC_SHA2_256;
	ad.hash_size = SHA256_DIGEST_SIZE;
	ad.auth_ctrl = SA_AUTH_SW_CTRL_SHA256;

	वापस sa_aead_setkey(authenc, key, keylen, &ad);
पूर्ण

अटल पूर्णांक sa_aead_run(काष्ठा aead_request *req, u8 *iv, पूर्णांक enc)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा sa_tfm_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा sa_req sa_req = अणु 0 पूर्ण;
	माप_प्रकार auth_size, enc_size;

	enc_size = req->cryptlen;
	auth_size = req->assoclen + req->cryptlen;

	अगर (!enc) अणु
		enc_size -= crypto_aead_authsize(tfm);
		auth_size -= crypto_aead_authsize(tfm);
	पूर्ण

	अगर (auth_size > SA_MAX_DATA_SZ ||
	    (auth_size >= SA_UNSAFE_DATA_SZ_MIN &&
	     auth_size <= SA_UNSAFE_DATA_SZ_MAX)) अणु
		काष्ठा aead_request *subreq = aead_request_ctx(req);
		पूर्णांक ret;

		aead_request_set_tfm(subreq, ctx->fallback.aead);
		aead_request_set_callback(subreq, req->base.flags,
					  req->base.complete, req->base.data);
		aead_request_set_crypt(subreq, req->src, req->dst,
				       req->cryptlen, req->iv);
		aead_request_set_ad(subreq, req->assoclen);

		ret = enc ? crypto_aead_encrypt(subreq) :
			crypto_aead_decrypt(subreq);
		वापस ret;
	पूर्ण

	sa_req.enc_offset = req->assoclen;
	sa_req.enc_size = enc_size;
	sa_req.auth_size = auth_size;
	sa_req.size = auth_size;
	sa_req.enc_iv = iv;
	sa_req.type = CRYPTO_ALG_TYPE_AEAD;
	sa_req.enc = enc;
	sa_req.callback = sa_aead_dma_in_callback;
	sa_req.mdata_size = 52;
	sa_req.base = &req->base;
	sa_req.ctx = ctx;
	sa_req.src = req->src;
	sa_req.dst = req->dst;

	वापस sa_run(&sa_req);
पूर्ण

/* AEAD algorithm encrypt पूर्णांकerface function */
अटल पूर्णांक sa_aead_encrypt(काष्ठा aead_request *req)
अणु
	वापस sa_aead_run(req, req->iv, 1);
पूर्ण

/* AEAD algorithm decrypt पूर्णांकerface function */
अटल पूर्णांक sa_aead_decrypt(काष्ठा aead_request *req)
अणु
	वापस sa_aead_run(req, req->iv, 0);
पूर्ण

अटल काष्ठा sa_alg_पंचांगpl sa_algs[] = अणु
	[SA_ALG_CBC_AES] = अणु
		.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name		= "cbc(aes)",
			.base.cra_driver_name	= "cbc-aes-sa2ul",
			.base.cra_priority	= 30000,
			.base.cra_flags		= CRYPTO_ALG_TYPE_SKCIPHER |
						  CRYPTO_ALG_KERN_DRIVER_ONLY |
						  CRYPTO_ALG_ASYNC |
						  CRYPTO_ALG_NEED_FALLBACK,
			.base.cra_blocksize	= AES_BLOCK_SIZE,
			.base.cra_ctxsize	= माप(काष्ठा sa_tfm_ctx),
			.base.cra_module	= THIS_MODULE,
			.init			= sa_cipher_cra_init,
			.निकास			= sa_cipher_cra_निकास,
			.min_keysize		= AES_MIN_KEY_SIZE,
			.max_keysize		= AES_MAX_KEY_SIZE,
			.ivsize			= AES_BLOCK_SIZE,
			.setkey			= sa_aes_cbc_setkey,
			.encrypt		= sa_encrypt,
			.decrypt		= sa_decrypt,
		पूर्ण
	पूर्ण,
	[SA_ALG_EBC_AES] = अणु
		.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name		= "ecb(aes)",
			.base.cra_driver_name	= "ecb-aes-sa2ul",
			.base.cra_priority	= 30000,
			.base.cra_flags		= CRYPTO_ALG_TYPE_SKCIPHER |
						  CRYPTO_ALG_KERN_DRIVER_ONLY |
						  CRYPTO_ALG_ASYNC |
						  CRYPTO_ALG_NEED_FALLBACK,
			.base.cra_blocksize	= AES_BLOCK_SIZE,
			.base.cra_ctxsize	= माप(काष्ठा sa_tfm_ctx),
			.base.cra_module	= THIS_MODULE,
			.init			= sa_cipher_cra_init,
			.निकास			= sa_cipher_cra_निकास,
			.min_keysize		= AES_MIN_KEY_SIZE,
			.max_keysize		= AES_MAX_KEY_SIZE,
			.setkey			= sa_aes_ecb_setkey,
			.encrypt		= sa_encrypt,
			.decrypt		= sa_decrypt,
		पूर्ण
	पूर्ण,
	[SA_ALG_CBC_DES3] = अणु
		.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name		= "cbc(des3_ede)",
			.base.cra_driver_name	= "cbc-des3-sa2ul",
			.base.cra_priority	= 30000,
			.base.cra_flags		= CRYPTO_ALG_TYPE_SKCIPHER |
						  CRYPTO_ALG_KERN_DRIVER_ONLY |
						  CRYPTO_ALG_ASYNC |
						  CRYPTO_ALG_NEED_FALLBACK,
			.base.cra_blocksize	= DES_BLOCK_SIZE,
			.base.cra_ctxsize	= माप(काष्ठा sa_tfm_ctx),
			.base.cra_module	= THIS_MODULE,
			.init			= sa_cipher_cra_init,
			.निकास			= sa_cipher_cra_निकास,
			.min_keysize		= 3 * DES_KEY_SIZE,
			.max_keysize		= 3 * DES_KEY_SIZE,
			.ivsize			= DES_BLOCK_SIZE,
			.setkey			= sa_3des_cbc_setkey,
			.encrypt		= sa_encrypt,
			.decrypt		= sa_decrypt,
		पूर्ण
	पूर्ण,
	[SA_ALG_ECB_DES3] = अणु
		.type = CRYPTO_ALG_TYPE_SKCIPHER,
		.alg.skcipher = अणु
			.base.cra_name		= "ecb(des3_ede)",
			.base.cra_driver_name	= "ecb-des3-sa2ul",
			.base.cra_priority	= 30000,
			.base.cra_flags		= CRYPTO_ALG_TYPE_SKCIPHER |
						  CRYPTO_ALG_KERN_DRIVER_ONLY |
						  CRYPTO_ALG_ASYNC |
						  CRYPTO_ALG_NEED_FALLBACK,
			.base.cra_blocksize	= DES_BLOCK_SIZE,
			.base.cra_ctxsize	= माप(काष्ठा sa_tfm_ctx),
			.base.cra_module	= THIS_MODULE,
			.init			= sa_cipher_cra_init,
			.निकास			= sa_cipher_cra_निकास,
			.min_keysize		= 3 * DES_KEY_SIZE,
			.max_keysize		= 3 * DES_KEY_SIZE,
			.setkey			= sa_3des_ecb_setkey,
			.encrypt		= sa_encrypt,
			.decrypt		= sa_decrypt,
		पूर्ण
	पूर्ण,
	[SA_ALG_SHA1] = अणु
		.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.ahash = अणु
			.halg.base = अणु
				.cra_name	= "sha1",
				.cra_driver_name	= "sha1-sa2ul",
				.cra_priority	= 400,
				.cra_flags	= CRYPTO_ALG_TYPE_AHASH |
						  CRYPTO_ALG_ASYNC |
						  CRYPTO_ALG_KERN_DRIVER_ONLY |
						  CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize	= SHA1_BLOCK_SIZE,
				.cra_ctxsize	= माप(काष्ठा sa_tfm_ctx),
				.cra_module	= THIS_MODULE,
				.cra_init	= sa_sha1_cra_init,
				.cra_निकास	= sa_sha_cra_निकास,
			पूर्ण,
			.halg.digestsize	= SHA1_DIGEST_SIZE,
			.halg.statesize		= माप(काष्ठा sa_sha_req_ctx) +
						  माप(काष्ठा sha1_state),
			.init			= sa_sha_init,
			.update			= sa_sha_update,
			.final			= sa_sha_final,
			.finup			= sa_sha_finup,
			.digest			= sa_sha_digest,
			.export			= sa_sha_export,
			.import			= sa_sha_import,
		पूर्ण,
	पूर्ण,
	[SA_ALG_SHA256] = अणु
		.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.ahash = अणु
			.halg.base = अणु
				.cra_name	= "sha256",
				.cra_driver_name	= "sha256-sa2ul",
				.cra_priority	= 400,
				.cra_flags	= CRYPTO_ALG_TYPE_AHASH |
						  CRYPTO_ALG_ASYNC |
						  CRYPTO_ALG_KERN_DRIVER_ONLY |
						  CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize	= SHA256_BLOCK_SIZE,
				.cra_ctxsize	= माप(काष्ठा sa_tfm_ctx),
				.cra_module	= THIS_MODULE,
				.cra_init	= sa_sha256_cra_init,
				.cra_निकास	= sa_sha_cra_निकास,
			पूर्ण,
			.halg.digestsize	= SHA256_DIGEST_SIZE,
			.halg.statesize		= माप(काष्ठा sa_sha_req_ctx) +
						  माप(काष्ठा sha256_state),
			.init			= sa_sha_init,
			.update			= sa_sha_update,
			.final			= sa_sha_final,
			.finup			= sa_sha_finup,
			.digest			= sa_sha_digest,
			.export			= sa_sha_export,
			.import			= sa_sha_import,
		पूर्ण,
	पूर्ण,
	[SA_ALG_SHA512] = अणु
		.type = CRYPTO_ALG_TYPE_AHASH,
		.alg.ahash = अणु
			.halg.base = अणु
				.cra_name	= "sha512",
				.cra_driver_name	= "sha512-sa2ul",
				.cra_priority	= 400,
				.cra_flags	= CRYPTO_ALG_TYPE_AHASH |
						  CRYPTO_ALG_ASYNC |
						  CRYPTO_ALG_KERN_DRIVER_ONLY |
						  CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize	= SHA512_BLOCK_SIZE,
				.cra_ctxsize	= माप(काष्ठा sa_tfm_ctx),
				.cra_module	= THIS_MODULE,
				.cra_init	= sa_sha512_cra_init,
				.cra_निकास	= sa_sha_cra_निकास,
			पूर्ण,
			.halg.digestsize	= SHA512_DIGEST_SIZE,
			.halg.statesize		= माप(काष्ठा sa_sha_req_ctx) +
						  माप(काष्ठा sha512_state),
			.init			= sa_sha_init,
			.update			= sa_sha_update,
			.final			= sa_sha_final,
			.finup			= sa_sha_finup,
			.digest			= sa_sha_digest,
			.export			= sa_sha_export,
			.import			= sa_sha_import,
		पूर्ण,
	पूर्ण,
	[SA_ALG_AUTHENC_SHA1_AES] = अणु
		.type	= CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),cbc(aes))",
				.cra_driver_name =
					"authenc(hmac(sha1),cbc(aes))-sa2ul",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_TYPE_AEAD |
					CRYPTO_ALG_KERN_DRIVER_ONLY |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_ctxsize = माप(काष्ठा sa_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_priority = 3000,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,

			.init = sa_cra_init_aead_sha1,
			.निकास = sa_निकास_tfm_aead,
			.setkey = sa_aead_cbc_sha1_setkey,
			.setauthsize = sa_aead_setauthsize,
			.encrypt = sa_aead_encrypt,
			.decrypt = sa_aead_decrypt,
		पूर्ण,
	पूर्ण,
	[SA_ALG_AUTHENC_SHA256_AES] = अणु
		.type	= CRYPTO_ALG_TYPE_AEAD,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha256),cbc(aes))",
				.cra_driver_name =
					"authenc(hmac(sha256),cbc(aes))-sa2ul",
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_flags = CRYPTO_ALG_TYPE_AEAD |
					CRYPTO_ALG_KERN_DRIVER_ONLY |
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK,
				.cra_ctxsize = माप(काष्ठा sa_tfm_ctx),
				.cra_module = THIS_MODULE,
				.cra_alignmask = 0,
				.cra_priority = 3000,
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA256_DIGEST_SIZE,

			.init = sa_cra_init_aead_sha256,
			.निकास = sa_निकास_tfm_aead,
			.setkey = sa_aead_cbc_sha256_setkey,
			.setauthsize = sa_aead_setauthsize,
			.encrypt = sa_aead_encrypt,
			.decrypt = sa_aead_decrypt,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* Register the algorithms in crypto framework */
अटल व्योम sa_रेजिस्टर_algos(काष्ठा sa_crypto_data *dev_data)
अणु
	स्थिर काष्ठा sa_match_data *match_data = dev_data->match_data;
	काष्ठा device *dev = dev_data->dev;
	अक्षर *alg_name;
	u32 type;
	पूर्णांक i, err;

	क्रम (i = 0; i < ARRAY_SIZE(sa_algs); i++) अणु
		/* Skip unsupported algos */
		अगर (!(match_data->supported_algos & BIT(i)))
			जारी;

		type = sa_algs[i].type;
		अगर (type == CRYPTO_ALG_TYPE_SKCIPHER) अणु
			alg_name = sa_algs[i].alg.skcipher.base.cra_name;
			err = crypto_रेजिस्टर_skcipher(&sa_algs[i].alg.skcipher);
		पूर्ण अन्यथा अगर (type == CRYPTO_ALG_TYPE_AHASH) अणु
			alg_name = sa_algs[i].alg.ahash.halg.base.cra_name;
			err = crypto_रेजिस्टर_ahash(&sa_algs[i].alg.ahash);
		पूर्ण अन्यथा अगर (type == CRYPTO_ALG_TYPE_AEAD) अणु
			alg_name = sa_algs[i].alg.aead.base.cra_name;
			err = crypto_रेजिस्टर_aead(&sa_algs[i].alg.aead);
		पूर्ण अन्यथा अणु
			dev_err(dev,
				"un-supported crypto algorithm (%d)",
				sa_algs[i].type);
			जारी;
		पूर्ण

		अगर (err)
			dev_err(dev, "Failed to register '%s'\n", alg_name);
		अन्यथा
			sa_algs[i].रेजिस्टरed = true;
	पूर्ण
पूर्ण

/* Unरेजिस्टर the algorithms in crypto framework */
अटल व्योम sa_unरेजिस्टर_algos(स्थिर काष्ठा device *dev)
अणु
	u32 type;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sa_algs); i++) अणु
		type = sa_algs[i].type;
		अगर (!sa_algs[i].रेजिस्टरed)
			जारी;
		अगर (type == CRYPTO_ALG_TYPE_SKCIPHER)
			crypto_unरेजिस्टर_skcipher(&sa_algs[i].alg.skcipher);
		अन्यथा अगर (type == CRYPTO_ALG_TYPE_AHASH)
			crypto_unरेजिस्टर_ahash(&sa_algs[i].alg.ahash);
		अन्यथा अगर (type == CRYPTO_ALG_TYPE_AEAD)
			crypto_unरेजिस्टर_aead(&sa_algs[i].alg.aead);

		sa_algs[i].रेजिस्टरed = false;
	पूर्ण
पूर्ण

अटल पूर्णांक sa_init_mem(काष्ठा sa_crypto_data *dev_data)
अणु
	काष्ठा device *dev = &dev_data->pdev->dev;
	/* Setup dma pool क्रम security context buffers */
	dev_data->sc_pool = dma_pool_create("keystone-sc", dev,
					    SA_CTX_MAX_SZ, 64, 0);
	अगर (!dev_data->sc_pool) अणु
		dev_err(dev, "Failed to create dma pool");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sa_dma_init(काष्ठा sa_crypto_data *dd)
अणु
	पूर्णांक ret;
	काष्ठा dma_slave_config cfg;

	dd->dma_rx1 = शून्य;
	dd->dma_tx = शून्य;
	dd->dma_rx2 = शून्य;

	ret = dma_coerce_mask_and_coherent(dd->dev, DMA_BIT_MASK(48));
	अगर (ret)
		वापस ret;

	dd->dma_rx1 = dma_request_chan(dd->dev, "rx1");
	अगर (IS_ERR(dd->dma_rx1))
		वापस dev_err_probe(dd->dev, PTR_ERR(dd->dma_rx1),
				     "Unable to request rx1 DMA channel\n");

	dd->dma_rx2 = dma_request_chan(dd->dev, "rx2");
	अगर (IS_ERR(dd->dma_rx2)) अणु
		dma_release_channel(dd->dma_rx1);
		वापस dev_err_probe(dd->dev, PTR_ERR(dd->dma_rx2),
				     "Unable to request rx2 DMA channel\n");
	पूर्ण

	dd->dma_tx = dma_request_chan(dd->dev, "tx");
	अगर (IS_ERR(dd->dma_tx)) अणु
		ret = dev_err_probe(dd->dev, PTR_ERR(dd->dma_tx),
				    "Unable to request tx DMA channel\n");
		जाओ err_dma_tx;
	पूर्ण

	memzero_explicit(&cfg, माप(cfg));

	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.src_maxburst = 4;
	cfg.dst_maxburst = 4;

	ret = dmaengine_slave_config(dd->dma_rx1, &cfg);
	अगर (ret) अणु
		dev_err(dd->dev, "can't configure IN dmaengine slave: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = dmaengine_slave_config(dd->dma_rx2, &cfg);
	अगर (ret) अणु
		dev_err(dd->dev, "can't configure IN dmaengine slave: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = dmaengine_slave_config(dd->dma_tx, &cfg);
	अगर (ret) अणु
		dev_err(dd->dev, "can't configure OUT dmaengine slave: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;

err_dma_tx:
	dma_release_channel(dd->dma_rx1);
	dma_release_channel(dd->dma_rx2);

	वापस ret;
पूर्ण

अटल पूर्णांक sa_link_child(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा device *parent = data;

	device_link_add(dev, parent, DL_FLAG_AUTOPROBE_CONSUMER);

	वापस 0;
पूर्ण

अटल काष्ठा sa_match_data am654_match_data = अणु
	.priv = 1,
	.priv_id = 1,
	.supported_algos = GENMASK(SA_ALG_AUTHENC_SHA256_AES, 0),
पूर्ण;

अटल काष्ठा sa_match_data am64_match_data = अणु
	.priv = 0,
	.priv_id = 0,
	.supported_algos = BIT(SA_ALG_CBC_AES) |
			   BIT(SA_ALG_EBC_AES) |
			   BIT(SA_ALG_SHA256) |
			   BIT(SA_ALG_SHA512) |
			   BIT(SA_ALG_AUTHENC_SHA256_AES),
	.skip_engine_control = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match[] = अणु
	अणु .compatible = "ti,j721e-sa2ul", .data = &am654_match_data, पूर्ण,
	अणु .compatible = "ti,am654-sa2ul", .data = &am654_match_data, पूर्ण,
	अणु .compatible = "ti,am64-sa2ul", .data = &am64_match_data, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_match);

अटल पूर्णांक sa_ul_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा resource *res;
	अटल व्योम __iomem *saul_base;
	काष्ठा sa_crypto_data *dev_data;
	पूर्णांक ret;

	dev_data = devm_kzalloc(dev, माप(*dev_data), GFP_KERNEL);
	अगर (!dev_data)
		वापस -ENOMEM;

	sa_k3_dev = dev;
	dev_data->dev = dev;
	dev_data->pdev = pdev;
	platक्रमm_set_drvdata(pdev, dev_data);
	dev_set_drvdata(sa_k3_dev, dev_data);

	pm_runसमय_enable(dev);
	ret = pm_runसमय_resume_and_get(dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "%s: failed to get sync: %d\n", __func__,
			ret);
		वापस ret;
	पूर्ण

	sa_init_mem(dev_data);
	ret = sa_dma_init(dev_data);
	अगर (ret)
		जाओ disable_pm_runसमय;

	match = of_match_node(of_match, dev->of_node);
	अगर (!match) अणु
		dev_err(dev, "No compatible match found\n");
		वापस -ENODEV;
	पूर्ण
	dev_data->match_data = match->data;

	spin_lock_init(&dev_data->scid_lock);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	saul_base = devm_ioremap_resource(dev, res);

	dev_data->base = saul_base;

	अगर (!dev_data->match_data->skip_engine_control) अणु
		u32 val = SA_EEC_ENCSS_EN | SA_EEC_AUTHSS_EN | SA_EEC_CTXCACH_EN |
			  SA_EEC_CPPI_PORT_IN_EN | SA_EEC_CPPI_PORT_OUT_EN |
			  SA_EEC_TRNG_EN;

		ग_लिखोl_relaxed(val, saul_base + SA_ENGINE_ENABLE_CONTROL);
	पूर्ण

	sa_रेजिस्टर_algos(dev_data);

	ret = of_platक्रमm_populate(node, शून्य, शून्य, &pdev->dev);
	अगर (ret)
		जाओ release_dma;

	device_क्रम_each_child(&pdev->dev, &pdev->dev, sa_link_child);

	वापस 0;

release_dma:
	sa_unरेजिस्टर_algos(&pdev->dev);

	dma_release_channel(dev_data->dma_rx2);
	dma_release_channel(dev_data->dma_rx1);
	dma_release_channel(dev_data->dma_tx);

	dma_pool_destroy(dev_data->sc_pool);

disable_pm_runसमय:
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sa_ul_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sa_crypto_data *dev_data = platक्रमm_get_drvdata(pdev);

	sa_unरेजिस्टर_algos(&pdev->dev);

	dma_release_channel(dev_data->dma_rx2);
	dma_release_channel(dev_data->dma_rx1);
	dma_release_channel(dev_data->dma_tx);

	dma_pool_destroy(dev_data->sc_pool);

	platक्रमm_set_drvdata(pdev, शून्य);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sa_ul_driver = अणु
	.probe = sa_ul_probe,
	.हटाओ = sa_ul_हटाओ,
	.driver = अणु
		   .name = "saul-crypto",
		   .of_match_table = of_match,
		   पूर्ण,
पूर्ण;
module_platक्रमm_driver(sa_ul_driver);
MODULE_LICENSE("GPL v2");
