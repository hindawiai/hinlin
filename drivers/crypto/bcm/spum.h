<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2016 Broadcom
 */

/*
 * This file contains SPU message definitions specअगरic to SPU-M.
 */

#अगर_अघोषित _SPUM_H_
#घोषणा _SPUM_H_

#घोषणा SPU_CRYPTO_OPERATION_GENERIC	0x1

/* Length of STATUS field in tx and rx packets */
#घोषणा SPU_TX_STATUS_LEN  4

/* SPU-M error codes */
#घोषणा SPU_STATUS_MASK                 0x0000FF00
#घोषणा SPU_STATUS_SUCCESS              0x00000000
#घोषणा SPU_STATUS_INVALID_ICV          0x00000100

#घोषणा SPU_STATUS_ERROR_FLAG           0x00020000

/* Request message. MH + EMH + BDESC + BD header */
#घोषणा SPU_REQ_FIXED_LEN 24

/*
 * Max length of a SPU message header. Used to allocate a buffer where
 * the SPU message header is स्थिरructed. Can be used क्रम either a SPU-M
 * header or a SPU2 header.
 * For SPU-M, sum of the following:
 *    MH - 4 bytes
 *    EMH - 4
 *    SCTX - 3 +
 *      max auth key len - 64
 *      max cipher key len - 264 (RC4)
 *      max IV len - 16
 *    BDESC - 12
 *    BD header - 4
 * Total:  371
 *
 * For SPU2, FMD_SIZE (32) plus lengths of hash and cipher keys,
 * hash and cipher IVs. If SPU2 करोes not support RC4, then
 */
#घोषणा SPU_HEADER_ALLOC_LEN  (SPU_REQ_FIXED_LEN + MAX_KEY_SIZE + \
				MAX_KEY_SIZE + MAX_IV_SIZE)

/*
 * Response message header length. Normally MH, EMH, BD header, but when
 * BD_SUPPRESS is used क्रम hash requests, there is no BD header.
 */
#घोषणा SPU_RESP_HDR_LEN 12
#घोषणा SPU_HASH_RESP_HDR_LEN 8

/*
 * Max value that can be represented in the Payload Length field of the BD
 * header. This is a 16-bit field.
 */
#घोषणा SPUM_NS2_MAX_PAYLOAD  (BIT(16) - 1)

/*
 * NSP SPU is limited to ~9KB because of FA2 FIFO size limitations;
 * Set MAX_PAYLOAD to 8k to allow क्रम addition of header, digest, etc.
 * and stay within limitation.
 */

#घोषणा SPUM_NSP_MAX_PAYLOAD	8192

/* Buffer Descriptor Header [BDESC]. SPU in big-endian mode. */
काष्ठा BDESC_HEADER अणु
	__be16 offset_mac;		/* word 0 [31-16] */
	__be16 length_mac;		/* word 0 [15-0]  */
	__be16 offset_crypto;		/* word 1 [31-16] */
	__be16 length_crypto;		/* word 1 [15-0]  */
	__be16 offset_icv;		/* word 2 [31-16] */
	__be16 offset_iv;		/* word 2 [15-0]  */
पूर्ण;

/* Buffer Data Header [BD]. SPU in big-endian mode. */
काष्ठा BD_HEADER अणु
	__be16 size;
	__be16 prev_length;
पूर्ण;

/* Command Context Header. SPU-M in big endian mode. */
काष्ठा MHEADER अणु
	u8 flags;	/* [31:24] */
	u8 op_code;	/* [23:16] */
	u16 reserved;	/* [15:0] */
पूर्ण;

/* MH header flags bits */
#घोषणा MH_SUPDT_PRES   BIT(0)
#घोषणा MH_HASH_PRES    BIT(2)
#घोषणा MH_BD_PRES      BIT(3)
#घोषणा MH_MFM_PRES     BIT(4)
#घोषणा MH_BDESC_PRES   BIT(5)
#घोषणा MH_SCTX_PRES	BIT(7)

/* SCTX word 0 bit offsets and fields masks */
#घोषणा SCTX_SIZE               0x000000FF

/* SCTX word 1 bit shअगरts and field masks */
#घोषणा  UPDT_OFST              0x000000FF   /* offset of SCTX updateable fld */
#घोषणा  HASH_TYPE              0x00000300   /* hash alg operation type */
#घोषणा  HASH_TYPE_SHIFT                 8
#घोषणा  HASH_MODE              0x00001C00   /* one of spu2_hash_mode */
#घोषणा  HASH_MODE_SHIFT                10
#घोषणा  HASH_ALG               0x0000E000   /* hash algorithm */
#घोषणा  HASH_ALG_SHIFT                 13
#घोषणा  CIPHER_TYPE            0x00030000   /* encryption operation type */
#घोषणा  CIPHER_TYPE_SHIFT              16
#घोषणा  CIPHER_MODE            0x001C0000   /* encryption mode */
#घोषणा  CIPHER_MODE_SHIFT              18
#घोषणा  CIPHER_ALG             0x00E00000   /* encryption algo */
#घोषणा  CIPHER_ALG_SHIFT               21
#घोषणा  ICV_IS_512                BIT(27)
#घोषणा  ICV_IS_512_SHIFT		27
#घोषणा  CIPHER_ORDER               BIT(30)
#घोषणा  CIPHER_ORDER_SHIFT             30
#घोषणा  CIPHER_INBOUND             BIT(31)
#घोषणा  CIPHER_INBOUND_SHIFT           31

/* SCTX word 2 bit shअगरts and field masks */
#घोषणा  EXP_IV_SIZE                   0x7
#घोषणा  IV_OFFSET                   BIT(3)
#घोषणा  IV_OFFSET_SHIFT                 3
#घोषणा  GEN_IV                      BIT(5)
#घोषणा  GEN_IV_SHIFT                    5
#घोषणा  EXPLICIT_IV                 BIT(6)
#घोषणा  EXPLICIT_IV_SHIFT               6
#घोषणा  SCTX_IV                     BIT(7)
#घोषणा  SCTX_IV_SHIFT                   7
#घोषणा  ICV_SIZE                   0x0F00
#घोषणा  ICV_SIZE_SHIFT                  8
#घोषणा  CHECK_ICV                  BIT(12)
#घोषणा  CHECK_ICV_SHIFT                12
#घोषणा  INSERT_ICV                 BIT(13)
#घोषणा  INSERT_ICV_SHIFT               13
#घोषणा  BD_SUPPRESS                BIT(19)
#घोषणा  BD_SUPPRESS_SHIFT              19

/* Generic Mode Security Context Structure [SCTX] */
काष्ठा SCTX अणु
/* word 0: protocol flags */
	__be32 proto_flags;

/* word 1: cipher flags */
	__be32 cipher_flags;

/* word 2: Extended cipher flags */
	__be32 ecf;

पूर्ण;

काष्ठा SPUHEADER अणु
	काष्ठा MHEADER mh;
	u32 emh;
	काष्ठा SCTX sa;
पूर्ण;

#पूर्ण_अगर /* _SPUM_H_ */
