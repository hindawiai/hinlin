<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ATMEL_SHA_REGS_H__
#घोषणा __ATMEL_SHA_REGS_H__

#घोषणा SHA_REG_DIGEST(x)		(0x80 + ((x) * 0x04))
#घोषणा SHA_REG_DIN(x)			(0x40 + ((x) * 0x04))

#घोषणा SHA_CR				0x00
#घोषणा SHA_CR_START			(1 << 0)
#घोषणा SHA_CR_FIRST			(1 << 4)
#घोषणा SHA_CR_SWRST			(1 << 8)
#घोषणा SHA_CR_WUIHV			(1 << 12)
#घोषणा SHA_CR_WUIEHV			(1 << 13)

#घोषणा SHA_MR				0x04
#घोषणा SHA_MR_MODE_MASK		(0x3 << 0)
#घोषणा SHA_MR_MODE_MANUAL		0x0
#घोषणा SHA_MR_MODE_AUTO		0x1
#घोषणा SHA_MR_MODE_PDC			0x2
#घोषणा SHA_MR_MODE_IDATAR0		0x2
#घोषणा SHA_MR_PROCDLY			(1 << 4)
#घोषणा SHA_MR_UIHV			(1 << 5)
#घोषणा SHA_MR_UIEHV			(1 << 6)
#घोषणा SHA_MR_ALGO_MASK		GENMASK(10, 8)
#घोषणा SHA_MR_ALGO_SHA1		(0 << 8)
#घोषणा SHA_MR_ALGO_SHA256		(1 << 8)
#घोषणा SHA_MR_ALGO_SHA384		(2 << 8)
#घोषणा SHA_MR_ALGO_SHA512		(3 << 8)
#घोषणा SHA_MR_ALGO_SHA224		(4 << 8)
#घोषणा SHA_MR_HMAC			(1 << 11)
#घोषणा	SHA_MR_DUALBUFF			(1 << 16)

#घोषणा SHA_FLAGS_ALGO_MASK	SHA_MR_ALGO_MASK
#घोषणा SHA_FLAGS_SHA1		SHA_MR_ALGO_SHA1
#घोषणा SHA_FLAGS_SHA256	SHA_MR_ALGO_SHA256
#घोषणा SHA_FLAGS_SHA384	SHA_MR_ALGO_SHA384
#घोषणा SHA_FLAGS_SHA512	SHA_MR_ALGO_SHA512
#घोषणा SHA_FLAGS_SHA224	SHA_MR_ALGO_SHA224
#घोषणा SHA_FLAGS_HMAC		SHA_MR_HMAC
#घोषणा SHA_FLAGS_HMAC_SHA1	(SHA_FLAGS_HMAC | SHA_FLAGS_SHA1)
#घोषणा SHA_FLAGS_HMAC_SHA256	(SHA_FLAGS_HMAC | SHA_FLAGS_SHA256)
#घोषणा SHA_FLAGS_HMAC_SHA384	(SHA_FLAGS_HMAC | SHA_FLAGS_SHA384)
#घोषणा SHA_FLAGS_HMAC_SHA512	(SHA_FLAGS_HMAC | SHA_FLAGS_SHA512)
#घोषणा SHA_FLAGS_HMAC_SHA224	(SHA_FLAGS_HMAC | SHA_FLAGS_SHA224)
#घोषणा SHA_FLAGS_MODE_MASK	(SHA_FLAGS_HMAC | SHA_FLAGS_ALGO_MASK)

#घोषणा SHA_IER				0x10
#घोषणा SHA_IDR				0x14
#घोषणा SHA_IMR				0x18
#घोषणा SHA_ISR				0x1C
#घोषणा SHA_INT_DATARDY			(1 << 0)
#घोषणा SHA_INT_ENDTX			(1 << 1)
#घोषणा SHA_INT_TXBUFE			(1 << 2)
#घोषणा SHA_INT_URAD			(1 << 8)
#घोषणा SHA_ISR_URAT_MASK		(0x7 << 12)
#घोषणा SHA_ISR_URAT_IDR		(0x0 << 12)
#घोषणा SHA_ISR_URAT_ODR		(0x1 << 12)
#घोषणा SHA_ISR_URAT_MR			(0x2 << 12)
#घोषणा SHA_ISR_URAT_WO			(0x5 << 12)

#घोषणा SHA_MSR				0x20
#घोषणा SHA_BCR				0x30

#घोषणा	SHA_HW_VERSION		0xFC

#घोषणा SHA_TPR				0x108
#घोषणा SHA_TCR				0x10C
#घोषणा SHA_TNPR			0x118
#घोषणा SHA_TNCR			0x11C
#घोषणा SHA_PTCR			0x120
#घोषणा SHA_PTCR_TXTEN		(1 << 8)
#घोषणा SHA_PTCR_TXTDIS		(1 << 9)
#घोषणा SHA_PTSR			0x124
#घोषणा SHA_PTSR_TXTEN		(1 << 8)

#पूर्ण_अगर /* __ATMEL_SHA_REGS_H__ */
