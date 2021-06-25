<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __NX_842_H__
#घोषणा __NX_842_H__

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/crypto.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/ratelimit.h>

/* Restrictions on Data Descriptor List (DDL) and Entry (DDE) buffers
 *
 * From NX P8 workbook, sec 4.9.1 "842 details"
 *   Each DDE buffer is 128 byte aligned
 *   Each DDE buffer size is a multiple of 32 bytes (except the last)
 *   The last DDE buffer size is a multiple of 8 bytes
 */
#घोषणा DDE_BUFFER_ALIGN	(128)
#घोषणा DDE_BUFFER_SIZE_MULT	(32)
#घोषणा DDE_BUFFER_LAST_MULT	(8)

/* Arbitrary DDL length limit
 * Allows max buffer size of MAX-1 to MAX pages
 * (depending on alignment)
 */
#घोषणा DDL_LEN_MAX		(17)

/* CCW 842 CI/FC masks
 * NX P8 workbook, section 4.3.1, figure 4-6
 * "CI/FC Boundary by NX CT type"
 */
#घोषणा CCW_CI_842		(0x00003ff8)
#घोषणा CCW_FC_842		(0x00000007)

/* CCW Function Codes (FC) क्रम 842
 * NX P8 workbook, section 4.9, table 4-28
 * "Function Code Definitions for 842 Memory Compression"
 */
#घोषणा CCW_FC_842_COMP_NOCRC	(0)
#घोषणा CCW_FC_842_COMP_CRC	(1)
#घोषणा CCW_FC_842_DECOMP_NOCRC	(2)
#घोषणा CCW_FC_842_DECOMP_CRC	(3)
#घोषणा CCW_FC_842_MOVE		(4)

/* CSB CC Error Types क्रम 842
 * NX P8 workbook, section 4.10.3, table 4-30
 * "Reported Error Types Summary Table"
 */
/* These are all duplicates of existing codes defined in icswx.h. */
#घोषणा CSB_CC_TRANSLATION_DUP1	(80)
#घोषणा CSB_CC_TRANSLATION_DUP2	(82)
#घोषणा CSB_CC_TRANSLATION_DUP3	(84)
#घोषणा CSB_CC_TRANSLATION_DUP4	(86)
#घोषणा CSB_CC_TRANSLATION_DUP5	(92)
#घोषणा CSB_CC_TRANSLATION_DUP6	(94)
#घोषणा CSB_CC_PROTECTION_DUP1	(81)
#घोषणा CSB_CC_PROTECTION_DUP2	(83)
#घोषणा CSB_CC_PROTECTION_DUP3	(85)
#घोषणा CSB_CC_PROTECTION_DUP4	(87)
#घोषणा CSB_CC_PROTECTION_DUP5	(93)
#घोषणा CSB_CC_PROTECTION_DUP6	(95)
#घोषणा CSB_CC_RD_EXTERNAL_DUP1	(89)
#घोषणा CSB_CC_RD_EXTERNAL_DUP2	(90)
#घोषणा CSB_CC_RD_EXTERNAL_DUP3	(91)
/* These are specअगरic to NX */
/* 842 codes */
#घोषणा CSB_CC_TPBC_GT_SPBC	(64) /* no error, but >1 comp ratio */
#घोषणा CSB_CC_CRC_MISMATCH	(65) /* decomp crc mismatch */
#घोषणा CSB_CC_TEMPL_INVALID	(66) /* decomp invalid ढाँचा value */
#घोषणा CSB_CC_TEMPL_OVERFLOW	(67) /* decomp ढाँचा shows data after end */
/* sym crypt codes */
#घोषणा CSB_CC_DECRYPT_OVERFLOW	(64)
/* asym crypt codes */
#घोषणा CSB_CC_MINV_OVERFLOW	(128)
/*
 * HW error - Job did not finish in the maximum समय allowed.
 * Job terminated.
 */
#घोषणा CSB_CC_HW_EXPIRED_TIMER		(224)
/* These are reserved क्रम hypervisor use */
#घोषणा CSB_CC_HYP_RESERVE_START	(240)
#घोषणा CSB_CC_HYP_RESERVE_END		(253)
#घोषणा CSB_CC_HYP_RESERVE_P9_END	(251)
/* No valid पूर्णांकerrupt server (P9 or later). */
#घोषणा CSB_CC_HYP_RESERVE_NO_INTR_SERVER	(252)
#घोषणा CSB_CC_HYP_NO_HW		(254)
#घोषणा CSB_CC_HYP_HANG_ABORTED		(255)

/* CCB Completion Modes (CM) क्रम 842
 * NX P8 workbook, section 4.3, figure 4-5
 * "CRB Details - Normal Cop_Req (CL=00, C=1)"
 */
#घोषणा CCB_CM_EXTRA_WRITE	(CCB_CM0_ALL_COMPLETIONS & CCB_CM12_STORE)
#घोषणा CCB_CM_INTERRUPT	(CCB_CM0_ALL_COMPLETIONS & CCB_CM12_INTERRUPT)

#घोषणा LEN_ON_SIZE(pa, size)	((size) - ((pa) & ((size) - 1)))
#घोषणा LEN_ON_PAGE(pa)		LEN_ON_SIZE(pa, PAGE_SIZE)

अटल अंतरभूत अचिन्हित दीर्घ nx842_get_pa(व्योम *addr)
अणु
	अगर (!is_vदो_स्मृति_addr(addr))
		वापस __pa(addr);

	वापस page_to_phys(vदो_स्मृति_to_page(addr)) + offset_in_page(addr);
पूर्ण

/**
 * This provides the driver's स्थिरraपूर्णांकs.  Dअगरferent nx842 implementations
 * may have varying requirements.  The स्थिरraपूर्णांकs are:
 *   @alignment:	All buffers should be aligned to this
 *   @multiple:		All buffer lengths should be a multiple of this
 *   @minimum:		Buffer lengths must not be less than this amount
 *   @maximum:		Buffer lengths must not be more than this amount
 *
 * The स्थिरraपूर्णांकs apply to all buffers and lengths, both input and output,
 * क्रम both compression and decompression, except क्रम the minimum which
 * only applies to compression input and decompression output; the
 * compressed data can be less than the minimum स्थिरraपूर्णांक.  It can be
 * assumed that compressed data will always adhere to the multiple
 * स्थिरraपूर्णांक.
 *
 * The driver may succeed even अगर these स्थिरraपूर्णांकs are violated;
 * however the driver can वापस failure or suffer reduced perक्रमmance
 * अगर any स्थिरraपूर्णांक is not met.
 */
काष्ठा nx842_स्थिरraपूर्णांकs अणु
	पूर्णांक alignment;
	पूर्णांक multiple;
	पूर्णांक minimum;
	पूर्णांक maximum;
पूर्ण;

काष्ठा nx842_driver अणु
	अक्षर *name;
	काष्ठा module *owner;
	माप_प्रकार workmem_size;

	काष्ठा nx842_स्थिरraपूर्णांकs *स्थिरraपूर्णांकs;

	पूर्णांक (*compress)(स्थिर अचिन्हित अक्षर *in, अचिन्हित पूर्णांक in_len,
			अचिन्हित अक्षर *out, अचिन्हित पूर्णांक *out_len,
			व्योम *wrkmem);
	पूर्णांक (*decompress)(स्थिर अचिन्हित अक्षर *in, अचिन्हित पूर्णांक in_len,
			  अचिन्हित अक्षर *out, अचिन्हित पूर्णांक *out_len,
			  व्योम *wrkmem);
पूर्ण;

काष्ठा nx842_crypto_header_group अणु
	__be16 padding;			/* unused bytes at start of group */
	__be32 compressed_length;	/* compressed bytes in group */
	__be32 uncompressed_length;	/* bytes after decompression */
पूर्ण __packed;

काष्ठा nx842_crypto_header अणु
	__be16 magic;		/* NX842_CRYPTO_MAGIC */
	__be16 ignore;		/* decompressed end bytes to ignore */
	u8 groups;		/* total groups in this header */
	काष्ठा nx842_crypto_header_group group[];
पूर्ण __packed;

#घोषणा NX842_CRYPTO_GROUP_MAX	(0x20)

काष्ठा nx842_crypto_ctx अणु
	spinlock_t lock;

	u8 *wmem;
	u8 *sbounce, *dbounce;

	काष्ठा nx842_crypto_header header;
	काष्ठा nx842_crypto_header_group group[NX842_CRYPTO_GROUP_MAX];

	काष्ठा nx842_driver *driver;
पूर्ण;

पूर्णांक nx842_crypto_init(काष्ठा crypto_tfm *tfm, काष्ठा nx842_driver *driver);
व्योम nx842_crypto_निकास(काष्ठा crypto_tfm *tfm);
पूर्णांक nx842_crypto_compress(काष्ठा crypto_tfm *tfm,
			  स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			  u8 *dst, अचिन्हित पूर्णांक *dlen);
पूर्णांक nx842_crypto_decompress(काष्ठा crypto_tfm *tfm,
			    स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			    u8 *dst, अचिन्हित पूर्णांक *dlen);

#पूर्ण_अगर /* __NX_842_H__ */
