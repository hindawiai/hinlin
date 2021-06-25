<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * K3 SA2UL crypto accelerator driver
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com
 *
 * Authors:	Keerthy
 *		Vitaly Andrianov
 *		Tero Kristo
 */

#अगर_अघोषित _K3_SA2UL_
#घोषणा _K3_SA2UL_

#समावेश <crypto/aes.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>

#घोषणा SA_ENGINE_ENABLE_CONTROL	0x1000

काष्ठा sa_tfm_ctx;
/*
 * SA_ENGINE_ENABLE_CONTROL रेजिस्टर bits
 */
#घोषणा SA_EEC_ENCSS_EN			0x00000001
#घोषणा SA_EEC_AUTHSS_EN		0x00000002
#घोषणा SA_EEC_TRNG_EN			0x00000008
#घोषणा SA_EEC_PKA_EN			0x00000010
#घोषणा SA_EEC_CTXCACH_EN		0x00000080
#घोषणा SA_EEC_CPPI_PORT_IN_EN		0x00000200
#घोषणा SA_EEC_CPPI_PORT_OUT_EN		0x00000800

/*
 * Encoding used to identअगरy the typo of crypto operation
 * perक्रमmed on the packet when the packet is वापसed
 * by SA
 */
#घोषणा SA_REQ_SUBTYPE_ENC	0x0001
#घोषणा SA_REQ_SUBTYPE_DEC	0x0002
#घोषणा SA_REQ_SUBTYPE_SHIFT	16
#घोषणा SA_REQ_SUBTYPE_MASK	0xffff

/* Number of 32 bit words in EPIB  */
#घोषणा SA_DMA_NUM_EPIB_WORDS   4

/* Number of 32 bit words in PS data  */
#घोषणा SA_DMA_NUM_PS_WORDS     16
#घोषणा NKEY_SZ			3
#घोषणा MCI_SZ			27

/*
 * Maximum number of simultaeneous security contexts
 * supported by the driver
 */
#घोषणा SA_MAX_NUM_CTX	512

/*
 * Assumption: CTX size is multiple of 32
 */
#घोषणा SA_CTX_SIZE_TO_DMA_SIZE(ctx_sz) \
		((ctx_sz) ? ((ctx_sz) / 32 - 1) : 0)

#घोषणा SA_CTX_ENC_KEY_OFFSET   32
#घोषणा SA_CTX_ENC_AUX1_OFFSET  64
#घोषणा SA_CTX_ENC_AUX2_OFFSET  96
#घोषणा SA_CTX_ENC_AUX3_OFFSET  112
#घोषणा SA_CTX_ENC_AUX4_OFFSET  128

/* Next Engine Select code in CP_ACE */
#घोषणा SA_ENG_ID_EM1   2       /* Enc/Dec engine with AES/DEC core */
#घोषणा SA_ENG_ID_EM2   3       /* Encryption/Decryption engineक्रम pass 2 */
#घोषणा SA_ENG_ID_AM1   4       /* Auth. engine with SHA1/MD5/SHA2 core */
#घोषणा SA_ENG_ID_AM2   5       /*  Authentication engine क्रम pass 2 */
#घोषणा SA_ENG_ID_OUTPORT2 20   /*  Egress module 2  */

/*
 * Command Label Definitions
 */
#घोषणा SA_CMDL_OFFSET_NESC           0      /* Next Engine Select Code */
#घोषणा SA_CMDL_OFFSET_LABEL_LEN      1      /* Engine Command Label Length */
/* 16-bit Length of Data to be processed */
#घोषणा SA_CMDL_OFFSET_DATA_LEN       2
#घोषणा SA_CMDL_OFFSET_DATA_OFFSET    4      /* Stat Data Offset */
#घोषणा SA_CMDL_OFFSET_OPTION_CTRL1   5      /* Option Control Byte 1 */
#घोषणा SA_CMDL_OFFSET_OPTION_CTRL2   6      /* Option Control Byte 2 */
#घोषणा SA_CMDL_OFFSET_OPTION_CTRL3   7      /* Option Control Byte 3 */
#घोषणा SA_CMDL_OFFSET_OPTION_BYTE    8

#घोषणा SA_CMDL_HEADER_SIZE_BYTES	8

#घोषणा SA_CMDL_OPTION_BYTES_MAX_SIZE     72
#घोषणा SA_CMDL_MAX_SIZE_BYTES (SA_CMDL_HEADER_SIZE_BYTES + \
				SA_CMDL_OPTION_BYTES_MAX_SIZE)

/* SWINFO word-0 flags */
#घोषणा SA_SW_INFO_FLAG_EVICT   0x0001
#घोषणा SA_SW_INFO_FLAG_TEAR    0x0002
#घोषणा SA_SW_INFO_FLAG_NOPD    0x0004

/*
 * This type represents the various packet types to be processed
 * by the PHP engine in SA.
 * It is used to identअगरy the corresponding PHP processing function.
 */
#घोषणा SA_CTX_PE_PKT_TYPE_3GPP_AIR    0    /* 3GPP Air Cipher */
#घोषणा SA_CTX_PE_PKT_TYPE_SRTP        1    /* SRTP */
#घोषणा SA_CTX_PE_PKT_TYPE_IPSEC_AH    2    /* IPSec Authentication Header */
/* IPSec Encapsulating Security Payload */
#घोषणा SA_CTX_PE_PKT_TYPE_IPSEC_ESP   3
/* Indicates that it is in data mode, It may not be used by PHP */
#घोषणा SA_CTX_PE_PKT_TYPE_NONE        4
#घोषणा SA_CTX_ENC_TYPE1_SZ     64      /* Encryption SC with Key only */
#घोषणा SA_CTX_ENC_TYPE2_SZ     96      /* Encryption SC with Key and Aux1 */

#घोषणा SA_CTX_AUTH_TYPE1_SZ    64      /* Auth SC with Key only */
#घोषणा SA_CTX_AUTH_TYPE2_SZ    96      /* Auth SC with Key and Aux1 */
/* Size of security context क्रम PHP engine */
#घोषणा SA_CTX_PHP_PE_CTX_SZ    64

#घोषणा SA_CTX_MAX_SZ (64 + SA_CTX_ENC_TYPE2_SZ + SA_CTX_AUTH_TYPE2_SZ)

/*
 * Encoding of F/E control in SCCTL
 *  Bit 0-1: Fetch PHP Bytes
 *  Bit 2-3: Fetch Encryption/Air Ciphering Bytes
 *  Bit 4-5: Fetch Authentication Bytes or Encr pass 2
 *  Bit 6-7: Evict PHP Bytes
 *
 *  where   00 = 0 bytes
 *          01 = 64 bytes
 *          10 = 96 bytes
 *          11 = 128 bytes
 */
#घोषणा SA_CTX_DMA_SIZE_0       0
#घोषणा SA_CTX_DMA_SIZE_64      1
#घोषणा SA_CTX_DMA_SIZE_96      2
#घोषणा SA_CTX_DMA_SIZE_128     3

/*
 * Byte offset of the owner word in SCCTL
 * in the security context
 */
#घोषणा SA_CTX_SCCTL_OWNER_OFFSET 0

#घोषणा SA_CTX_ENC_KEY_OFFSET   32
#घोषणा SA_CTX_ENC_AUX1_OFFSET  64
#घोषणा SA_CTX_ENC_AUX2_OFFSET  96
#घोषणा SA_CTX_ENC_AUX3_OFFSET  112
#घोषणा SA_CTX_ENC_AUX4_OFFSET  128

#घोषणा SA_SCCTL_FE_AUTH_ENC	0x65
#घोषणा SA_SCCTL_FE_ENC		0x8D

#घोषणा SA_ALIGN_MASK		(माप(u32) - 1)
#घोषणा SA_ALIGNED		__aligned(32)

#घोषणा SA_AUTH_SW_CTRL_MD5	1
#घोषणा SA_AUTH_SW_CTRL_SHA1	2
#घोषणा SA_AUTH_SW_CTRL_SHA224	3
#घोषणा SA_AUTH_SW_CTRL_SHA256	4
#घोषणा SA_AUTH_SW_CTRL_SHA384	5
#घोषणा SA_AUTH_SW_CTRL_SHA512	6

/* SA2UL can only handle maximum data size of 64KB */
#घोषणा SA_MAX_DATA_SZ		U16_MAX

/*
 * SA2UL can provide unpredictable results with packet sizes that fall
 * the following range, so aव्योम using it.
 */
#घोषणा SA_UNSAFE_DATA_SZ_MIN	240
#घोषणा SA_UNSAFE_DATA_SZ_MAX	256

काष्ठा sa_match_data;

/**
 * काष्ठा sa_crypto_data - Crypto driver instance data
 * @base: Base address of the रेजिस्टर space
 * @soc_data: Poपूर्णांकer to SoC specअगरic data
 * @pdev: Platक्रमm device poपूर्णांकer
 * @sc_pool: security context pool
 * @dev: Device poपूर्णांकer
 * @scid_lock: secure context ID lock
 * @sc_id_start: starting index क्रम SC ID
 * @sc_id_end: Ending index क्रम SC ID
 * @sc_id: Security Context ID
 * @ctx_bm: Biपंचांगap to keep track of Security context ID's
 * @ctx: SA tfm context poपूर्णांकer
 * @dma_rx1: Poपूर्णांकer to DMA rx channel क्रम sizes < 256 Bytes
 * @dma_rx2: Poपूर्णांकer to DMA rx channel क्रम sizes > 256 Bytes
 * @dma_tx: Poपूर्णांकer to DMA TX channel
 */
काष्ठा sa_crypto_data अणु
	व्योम __iomem *base;
	स्थिर काष्ठा sa_match_data *match_data;
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा dma_pool		*sc_pool;
	काष्ठा device *dev;
	spinlock_t	scid_lock; /* lock क्रम SC-ID allocation */
	/* Security context data */
	u16		sc_id_start;
	u16		sc_id_end;
	u16		sc_id;
	अचिन्हित दीर्घ	ctx_bm[DIV_ROUND_UP(SA_MAX_NUM_CTX,
				BITS_PER_LONG)];
	काष्ठा sa_tfm_ctx	*ctx;
	काष्ठा dma_chan		*dma_rx1;
	काष्ठा dma_chan		*dma_rx2;
	काष्ठा dma_chan		*dma_tx;
पूर्ण;

/**
 * काष्ठा sa_cmdl_param_info: Command label parameters info
 * @index: Index of the parameter in the command label क्रमmat
 * @offset: the offset of the parameter
 * @size: Size of the parameter
 */
काष्ठा sa_cmdl_param_info अणु
	u16	index;
	u16	offset;
	u16	size;
पूर्ण;

/* Maximum length of Auxiliary data in 32bit words */
#घोषणा SA_MAX_AUX_DATA_WORDS	8

/**
 * काष्ठा sa_cmdl_upd_info: Command label updation info
 * @flags: flags in command label
 * @submode: Encryption submodes
 * @enc_size: Size of first pass encryption size
 * @enc_size2: Size of second pass encryption size
 * @enc_offset: Encryption payload offset in the packet
 * @enc_iv: Encryption initialization vector क्रम pass2
 * @enc_iv2: Encryption initialization vector क्रम pass2
 * @aad: Associated data
 * @payload: Payload info
 * @auth_size: Authentication size क्रम pass 1
 * @auth_size2: Authentication size क्रम pass 2
 * @auth_offset: Authentication payload offset
 * @auth_iv: Authentication initialization vector
 * @aux_key_info: Authentication aux key inक्रमmation
 * @aux_key: Aux key क्रम authentication
 */
काष्ठा sa_cmdl_upd_info अणु
	u16	flags;
	u16	submode;
	काष्ठा sa_cmdl_param_info	enc_size;
	काष्ठा sa_cmdl_param_info	enc_size2;
	काष्ठा sa_cmdl_param_info	enc_offset;
	काष्ठा sa_cmdl_param_info	enc_iv;
	काष्ठा sa_cmdl_param_info	enc_iv2;
	काष्ठा sa_cmdl_param_info	aad;
	काष्ठा sa_cmdl_param_info	payload;
	काष्ठा sa_cmdl_param_info	auth_size;
	काष्ठा sa_cmdl_param_info	auth_size2;
	काष्ठा sa_cmdl_param_info	auth_offset;
	काष्ठा sa_cmdl_param_info	auth_iv;
	काष्ठा sa_cmdl_param_info	aux_key_info;
	u32				aux_key[SA_MAX_AUX_DATA_WORDS];
पूर्ण;

/*
 * Number of 32bit words appended after the command label
 * in PSDATA to identअगरy the crypto request context.
 * word-0: Request type
 * word-1: poपूर्णांकer to request
 */
#घोषणा SA_PSDATA_CTX_WORDS 4

/* Maximum size of Command label in 32 words */
#घोषणा SA_MAX_CMDL_WORDS (SA_DMA_NUM_PS_WORDS - SA_PSDATA_CTX_WORDS)

/**
 * काष्ठा sa_ctx_info: SA context inक्रमmation
 * @sc: Poपूर्णांकer to security context
 * @sc_phys: Security context physical address that is passed on to SA2UL
 * @sc_id: Security context ID
 * @cmdl_size: Command label size
 * @cmdl: Command label क्रम a particular iteration
 * @cmdl_upd_info: काष्ठाure holding command label updation info
 * @epib: Extended protocol inक्रमmation block words
 */
काष्ठा sa_ctx_info अणु
	u8		*sc;
	dma_addr_t	sc_phys;
	u16		sc_id;
	u16		cmdl_size;
	u32		cmdl[SA_MAX_CMDL_WORDS];
	काष्ठा sa_cmdl_upd_info cmdl_upd_info;
	/* Store Auxiliary data such as K2/K3 subkeys in AES-XCBC */
	u32		epib[SA_DMA_NUM_EPIB_WORDS];
पूर्ण;

/**
 * काष्ठा sa_tfm_ctx: TFM context काष्ठाure
 * @dev_data: काष्ठा sa_crypto_data poपूर्णांकer
 * @enc: काष्ठा sa_ctx_info क्रम encryption
 * @dec: काष्ठा sa_ctx_info क्रम decryption
 * @keylen: encrption/decryption keylength
 * @iv_idx: Initialization vector index
 * @key: encryption key
 * @fallback: SW fallback algorithm
 */
काष्ठा sa_tfm_ctx अणु
	काष्ठा sa_crypto_data *dev_data;
	काष्ठा sa_ctx_info enc;
	काष्ठा sa_ctx_info dec;
	काष्ठा sa_ctx_info auth;
	पूर्णांक keylen;
	पूर्णांक iv_idx;
	u32 key[AES_KEYSIZE_256 / माप(u32)];
	u8 authkey[SHA512_BLOCK_SIZE];
	काष्ठा crypto_shash	*shash;
	/* क्रम fallback */
	जोड़ अणु
		काष्ठा crypto_skcipher		*skcipher;
		काष्ठा crypto_ahash		*ahash;
		काष्ठा crypto_aead		*aead;
	पूर्ण fallback;
पूर्ण;

/**
 * काष्ठा sa_sha_req_ctx: Structure used क्रम sha request
 * @dev_data: काष्ठा sa_crypto_data poपूर्णांकer
 * @cmdl: Complete command label with psdata and epib included
 * @fallback_req: SW fallback request container
 */
काष्ठा sa_sha_req_ctx अणु
	काष्ठा sa_crypto_data	*dev_data;
	u32			cmdl[SA_MAX_CMDL_WORDS + SA_PSDATA_CTX_WORDS];
	काष्ठा ahash_request	fallback_req;
पूर्ण;

क्रमागत sa_submode अणु
	SA_MODE_GEN = 0,
	SA_MODE_CCM,
	SA_MODE_GCM,
	SA_MODE_GMAC
पूर्ण;

/* Encryption algorithms */
क्रमागत sa_ealg_id अणु
	SA_EALG_ID_NONE = 0,        /* No encryption */
	SA_EALG_ID_शून्य,            /* शून्य encryption */
	SA_EALG_ID_AES_CTR,         /* AES Counter mode */
	SA_EALG_ID_AES_F8,          /* AES F8 mode */
	SA_EALG_ID_AES_CBC,         /* AES CBC mode */
	SA_EALG_ID_DES_CBC,         /* DES CBC mode */
	SA_EALG_ID_3DES_CBC,        /* 3DES CBC mode */
	SA_EALG_ID_CCM,             /* Counter with CBC-MAC mode */
	SA_EALG_ID_GCM,             /* Galois Counter mode */
	SA_EALG_ID_AES_ECB,
	SA_EALG_ID_LAST
पूर्ण;

/* Authentication algorithms */
क्रमागत sa_aalg_id अणु
	SA_AALG_ID_NONE = 0,      /* No Authentication  */
	SA_AALG_ID_शून्य = SA_EALG_ID_LAST, /* शून्य Authentication  */
	SA_AALG_ID_MD5,           /* MD5 mode */
	SA_AALG_ID_SHA1,          /* SHA1 mode */
	SA_AALG_ID_SHA2_224,      /* 224-bit SHA2 mode */
	SA_AALG_ID_SHA2_256,      /* 256-bit SHA2 mode */
	SA_AALG_ID_SHA2_512,      /* 512-bit SHA2 mode */
	SA_AALG_ID_HMAC_MD5,      /* HMAC with MD5 mode */
	SA_AALG_ID_HMAC_SHA1,     /* HMAC with SHA1 mode */
	SA_AALG_ID_HMAC_SHA2_224, /* HMAC with 224-bit SHA2 mode */
	SA_AALG_ID_HMAC_SHA2_256, /* HMAC with 256-bit SHA2 mode */
	SA_AALG_ID_GMAC,          /* Galois Message Auth. Code mode */
	SA_AALG_ID_CMAC,          /* Cipher-based Mes. Auth. Code mode */
	SA_AALG_ID_CBC_MAC,       /* Cipher Block Chaining */
	SA_AALG_ID_AES_XCBC       /* AES Extended Cipher Block Chaining */
पूर्ण;

/*
 * Mode control engine algorithms used to index the
 * mode control inकाष्ठाion tables
 */
क्रमागत sa_eng_algo_id अणु
	SA_ENG_ALGO_ECB = 0,
	SA_ENG_ALGO_CBC,
	SA_ENG_ALGO_CFB,
	SA_ENG_ALGO_OFB,
	SA_ENG_ALGO_CTR,
	SA_ENG_ALGO_F8,
	SA_ENG_ALGO_F8F9,
	SA_ENG_ALGO_GCM,
	SA_ENG_ALGO_GMAC,
	SA_ENG_ALGO_CCM,
	SA_ENG_ALGO_CMAC,
	SA_ENG_ALGO_CBCMAC,
	SA_NUM_ENG_ALGOS
पूर्ण;

/**
 * काष्ठा sa_eng_info: Security accelerator engine info
 * @eng_id: Engine ID
 * @sc_size: security context size
 */
काष्ठा sa_eng_info अणु
	u8	eng_id;
	u16	sc_size;
पूर्ण;

#पूर्ण_अगर /* _K3_SA2UL_ */
